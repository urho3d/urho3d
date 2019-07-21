/*
	Copyright (c) 2009-2010 Christopher A. Taylor.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	* Neither the name of LibCat nor the names of its contributors may be used
	  to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

#include <cat/net/SphynxClient.hpp>
#include <cat/port/AlignedAlloc.hpp>
#include <cat/io/Logging.hpp>
#include <cat/io/MMapFile.hpp>
#include <cat/net/DNSClient.hpp>
#include <cat/io/Settings.hpp>
#include <cat/parse/BufferStream.hpp>
#include <cat/time/Clock.hpp>
#include <cat/crypt/SecureCompare.hpp>
#include <fstream>
using namespace std;
using namespace cat;
using namespace sphynx;


//// Client

Client::Client()
	: UDPEndpoint(REFOBJ_PRIO_0+4)
{
	_connected = false;
	_last_send_mstsc = 0;
}

Client::~Client()
{
	_kill_flag.Set();

	if (!WaitForThread(CLIENT_THREAD_KILL_TIMEOUT))
		AbortThread();
}

void Client::OnWrite(u32 bytes)
{

}

bool Client::SetServerKey(ThreadPoolLocalStorage *tls, const void *server_key, int key_bytes, const char *session_key)
{
	// Verify the key bytes are correct
	if (key_bytes != sizeof(_server_public_key))
	{
		WARN("Client") << "Failed to connect: Invalid server public key length provided";
		return false;
	}

	// Verify TLS is valid
	if (!tls->Valid())
	{
		WARN("Client") << "Failed to connect: Unable to create thread local storage";
		return false;
	}

	// Verify public key and initialize crypto library with it
	if (!_key_agreement_initiator.Initialize(tls->math, reinterpret_cast<const u8*>( server_key ), key_bytes))
	{
		WARN("Client") << "Failed to connect: Invalid server public key provided";
		return false;
	}

	// Generate a challenge for the server
	if (!_key_agreement_initiator.GenerateChallenge(tls->math, tls->csprng, _cached_challenge, CHALLENGE_BYTES))
	{
		WARN("Client") << "Failed to connect: Cannot generate challenge message";
		return false;
	}

	// Copy session key
	CAT_STRNCPY(_session_key, session_key, SESSION_KEY_BYTES);

	memcpy(_server_public_key, server_key, sizeof(_server_public_key));

	return true;
}

bool Client::Connect(const char *hostname, Port port)
{
	// Set port
	_server_addr.SetPort(port);

	// If DNS resolution fails,
	if (!DNSClient::ii->Resolve(hostname, fastdelegate::MakeDelegate(this, &Client::OnResolve), this))
	{
		WARN("Client") << "Failed to connect: Unable to resolve server hostname";
		return false;
	}

	return true;
}

bool Client::Connect(const NetAddr &addr)
{
	// Validate port
	if (addr.GetPort() == 0)
	{
		WARN("Client") << "Failed to connect: Invalid server port specified";
		return false;
	}

	_server_addr = addr;

	// Get SupportIPv6 flag from settings
	bool only_ipv4 = Settings::ii->getInt("Sphynx.Client.SupportIPv6", 0) == 0;

	// Get kernel receive buffer size
	int kernelReceiveBufferBytes = Settings::ii->getInt("Sphynx.Client.KernelReceiveBuffer", 1000000);

	// Attempt to bind to any port and accept ICMP errors initially
	if (!Bind(only_ipv4, 0, false, kernelReceiveBufferBytes))
	{
		WARN("Client") << "Failed to connect: Unable to bind to any port";
		return false;
	}

	// Convert server address if needed
	if (!_server_addr.Convert(Is6()))
	{
		WARN("Client") << "Failed to connect: Invalid address specified";
		Close();
		return false;
	}

	// Initialize max payload bytes
	InitializePayloadBytes(Is6());

	// Attempt to post hello message
	if (!PostHello())
	{
		WARN("Client") << "Failed to connect: Post failure";
		Close();
		return false;
	}

	// Attempt to start the timer thread
	if (!StartThread())
	{
		WARN("Client") << "Failed to connect: Unable to start timer thread";
		Close();
		return false;
	}

	return true;
}

bool Client::OnResolve(const char *hostname, const NetAddr *array, int array_length)
{
	// If resolve failed,
	if (array_length <= 0)
	{
		WARN("Client") << "Failed to connect: Server hostname resolve failed";

		Close();
	}
	else
	{
		NetAddr addr = array[0];
		addr.SetPort(_server_addr.GetPort());

		INANE("Client") << "Connecting: Resolved '" << hostname << "' to " << addr.IPToString();

		if (!Connect(addr))
			Close();
	}

	return true;
}

void Client::OnUnreachable(const NetAddr &src)
{
	// If IP matches the server and we're not connected yet,
	if (!_connected && _server_addr.EqualsIPOnly(src))
	{
		WARN("Client") << "Failed to connect: ICMP error received from server address";

		// ICMP error from server means it is down
		Close();
	}
}

void Client::OnRead(ThreadPoolLocalStorage *tls, const NetAddr &src, u8 *data, u32 bytes)
{
	// If packet source is not the server, ignore this packet
	if (_server_addr != src)
		return;

	// If connection has completed
	if (_connected)
	{
		u32 buf_bytes = bytes;

		// If the data could not be decrypted, ignore this packet
		if (_auth_enc.Decrypt(data, buf_bytes))
		{
			_last_recv_tsc = Clock::msec_fast();

			// Pass the packet to the transport layer
			OnDatagram(tls, data, buf_bytes);
		}
		else
		{
			WARN("Client") << "Ignored invalid encrypted data";
		}
	}
	// s2c 01 (cookie[4]) (public key[64])
	else if (bytes == 1+4+PUBLIC_KEY_BYTES && data[0] == S2C_COOKIE)
	{
		u32 *in_cookie = reinterpret_cast<u32*>( data + 1 );
		u8 *in_public_key = data + 1+4;

		// Verify public key
		if (!SecureEqual(in_public_key, _server_public_key, PUBLIC_KEY_BYTES))
		{
			WARN("Client") << "Unable to connect: Server public key does not match expected key";
			Close();
			return;
		}

		// Allocate a post buffer
		static const int response_len = 1+4+CHALLENGE_BYTES;
		u8 *response = AsyncBuffer::Acquire(response_len);

		if (!response)
		{
			WARN("Client") << "Unable to connect: Cannot allocate buffer for challenge message";
			Close();
			return;
		}

		// Construct challenge packet
		u32 *out_cookie = reinterpret_cast<u32*>( response + 1 );
		u8 *out_challenge = response + 1+4;

		response[0] = C2S_CHALLENGE;
		*out_cookie = *in_cookie;
		memcpy(out_challenge, _cached_challenge, CHALLENGE_BYTES);

		// Start ignoring ICMP unreachable messages now that we've seen a response from the server
		if (!IgnoreUnreachable())
		{
			WARN("Client") << "ICMP ignore unreachable failed";
		}

		// Attempt to post a response
		if (!Post(_server_addr, response, response_len))
		{
			WARN("Client") << "Unable to connect: Cannot post response to cookie";
			Close();
		}
		else
		{
			INANE("Client") << "Accepted cookie and posted challenge";
		}
	}
	// s2c 03 (server session port[2]) (answer[128])
	else if (bytes == 1+2+ANSWER_BYTES && data[0] == S2C_ANSWER)
	{
		Port *port = reinterpret_cast<Port*>( data + 1 );
		u8 *answer = data + 3;

		Port server_session_port = getLE(*port);

		// Ignore packet if the port doesn't make sense
		if (server_session_port > _server_addr.GetPort())
		{
			Skein key_hash;

			// Process answer from server, ignore invalid
			if (_key_agreement_initiator.ProcessAnswer(tls->math, answer, ANSWER_BYTES, &key_hash) &&
				_key_agreement_initiator.KeyEncryption(&key_hash, &_auth_enc, _session_key))
			{
				_connected = true;

				// Note: Will now only listen to packets from the session port
				_server_addr.SetPort(server_session_port);

				OnConnect(tls);
			}
			else
			{
				INANE("Client") << "Ignored invalid server answer";
			}
		}
		else
		{
			INANE("Client") << "Ignored server answer with insane port";
		}
	}
}

bool Client::PostHello()
{
	if (_connected)
	{
		WARN("Client") << "Refusing to post hello after connected";
		return false;
	}

	// Allocate space for a post buffer
	static const int hello_len = 1+4;
	u8 *hello = AsyncBuffer::Acquire(hello_len);

	// If unable to allocate,
	if (!hello)
	{
		WARN("Client") << "Cannot allocate a post buffer for hello packet";
		return false;
	}

	BufferStream(hello) << (u8)C2S_HELLO << PROTOCOL_MAGIC;

	// Attempt to post packet
	if (!Post(_server_addr, hello, hello_len))
	{
		WARN("Client") << "Unable to post hello packet";
		return false;
	}

	INANE("Client") << "Posted hello packet";

	return true;
}

bool Client::ThreadFunction(void *)
{
	ThreadPoolLocalStorage tls;

	if (!tls.Valid())
	{
		WARN("Client") << "Unable to create thread pool local storage";
		return false;
	}

	u32 start_time = Clock::msec_fast();
	u32 first_hello_post = start_time;
	u32 last_hello_post = start_time;
	u32 hello_post_interval = INITIAL_HELLO_POST_INTERVAL;

	// While still not connected,
	while (!_connected)
	{
		// Wait for quit signal
		if (_kill_flag.Wait(HANDSHAKE_TICK_RATE))
			return false;

		// If now connected, break out
		if (_connected)
			break;

		u32 now = Clock::msec_fast();

		// If connection timed out,
		if (now - first_hello_post >= CONNECT_TIMEOUT)
		{
			// NOTE: Connection can complete before or after OnConnectFail()
			WARN("Client") << "Unable to connect: Timeout";
			Close();
			return false;
		}

		// If time to repost hello packet,
		if (now - last_hello_post >= hello_post_interval)
		{
			if (!PostHello())
			{
				WARN("Client") << "Unable to connect: Post failure";
				Close();
				return false;
			}

			last_hello_post = now;
			hello_post_interval *= 2;
		}

		OnTick(&tls, now);
	}

	// Begin MTU probing after connection completes
	u32 overhead = (Is6() ? IPV6_HEADER_BYTES : IPV4_HEADER_BYTES) + UDP_HEADER_BYTES + AuthenticatedEncryption::OVERHEAD_BYTES;
	u32 mtu_discovery_time = Clock::msec();
	int mtu_discovery_attempts = 2;

	if (!DontFragment())
	{
		WARN("Client") << "Unable to detect MTU: Unable to set DF bit";
		mtu_discovery_attempts = 0;
	}
	else if (!PostMTUProbe(&tls, MAXIMUM_MTU - overhead) ||
			 !PostMTUProbe(&tls, MEDIUM_MTU - overhead))
	{
		WARN("Client") << "Unable to detect MTU: First probe post failure";
	}

	// Time synchronization begins right away
	u32 next_sync_time = Clock::msec();
	u32 sync_attempts = 0;

	// Set last receive time to avoid disconnecting due to timeout too soon
	_last_recv_tsc = next_sync_time;

	// While waiting for quit signal,
	while (!_kill_flag.Wait(Transport::TICK_RATE))
	{
		u32 now = Clock::msec();

		TickTransport(&tls, now);

		// If it is time for time synch,
		if ((s32)(now - next_sync_time) >= 0)
		{
			PostTimePing();

			// Increase synch interval after the first 8 data points
			if (sync_attempts >= 8)
				next_sync_time = now + 20000; // 20 seconds from now
			else
			{
				next_sync_time = now + 5000; // 5 seconds from now
				++sync_attempts;
			}
		}

		// If MTU discovery attempts continue,
		if (mtu_discovery_attempts > 0)
		{
			// If it is time to reprobe the MTU,
			if (now - mtu_discovery_time >= MTU_PROBE_INTERVAL)
			{
				// If payload bytes already maxed out,
				if (_max_payload_bytes >= MAXIMUM_MTU - overhead)
				{
					// Stop posting probes
					mtu_discovery_attempts = 0;

					// On final attempt set DF=0
					DontFragment(false);
				}
				else
				{
					// If not on final attempt,
					if (mtu_discovery_attempts > 1)
					{
						// Post probes
						if (!PostMTUProbe(&tls, MAXIMUM_MTU - overhead) ||
							!PostMTUProbe(&tls, MEDIUM_MTU - overhead))
						{
							WARN("Client") << "Unable to detect MTU: Probe post failure";
						}

						mtu_discovery_time = now;
						--mtu_discovery_attempts;
					}
					else
					{
						// Stop posting probes
						mtu_discovery_attempts = 0;

						// On final attempt set DF=0
						DontFragment(false);
					}
				}
			}
		}

		// If no packets have been received,
		if ((s32)(now - _last_recv_tsc) >= TIMEOUT_DISCONNECT)
		{
			Disconnect();
			return true;
		}

		// Tick subclass
		OnTick(&tls, now);

		// Send a keep-alive after the silence limit expires
		if ((s32)(now - _last_send_mstsc) >= SILENCE_LIMIT)
		{
			PostTimePing();
			next_sync_time = now + 20000; // 20 seconds from now
		}
	}

	return true;
}

bool Client::PostPacket(u8 *buffer, u32 buf_bytes, u32 msg_bytes, u32 skip_bytes)
{
	buf_bytes -= skip_bytes;
	msg_bytes -= skip_bytes;

	if (!_auth_enc.Encrypt(buffer + skip_bytes, buf_bytes, msg_bytes))
	{
		WARN("Client") << "Encryption failure while sending packet";
		AsyncBuffer::Release(buffer);
		return false;
	}

	if (Post(_server_addr, buffer, msg_bytes, skip_bytes))
	{
		_last_send_mstsc = Clock::msec_fast();
		return true;
	}

	return false;
}

void Client::Disconnect()
{
	PostDisconnect();
	TransportDisconnected();

	Close();
}
