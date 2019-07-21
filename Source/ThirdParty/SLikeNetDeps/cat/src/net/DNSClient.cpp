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

#include <cat/net/DNSClient.hpp>
#include <cat/io/Logging.hpp>
#include <cat/time/Clock.hpp>
#include <cat/lang/Strings.hpp>
#include <cat/port/EndianNeutral.hpp>
#include <cat/io/Settings.hpp>
#include <cstdio>
#include <fstream>
using namespace cat;

/*
	DNS protocol:

	Big-endian of course.

	Header
		ID(16)
		QR(1) OPCODE(4) AA(1) TC(1) RD(1) RA(1) Z(3) RCODE(4) [=16]
		QDCOUNT(16)
		ANCOUNT(16)
		NSCOUNT(16)
		ARCOUNT(16)
	Question
		QNAME(x)
		QTYPE(16)
		QCLASS(16)
	Answer, Authority, Additional
		NAME(x)
		TYPE(16)
		CLASS(16)
		TTL(32)
		RDLENGTH(16)
		RDATA(x)
*/

enum HeaderBits
{
	DNSHDR_QR = 15,
	DNSHDR_OPCODE = 11,
	DNSHDR_AA = 10,
	DNSHDR_TC = 9,
	DNSHDR_RD = 8,
	DNSHDR_RA = 7,
	DNSHDR_Z = 4,
	DNSHDR_RCODE = 0
};

enum SectionWordOffsets
{
	DNS_ID,
	DNS_HDR,
	DNS_QDCOUNT,
	DNS_ANCOUNT,
	DNS_NSCOUNT,
	DNS_ARCOUNT,
};

enum QuestionFooterWordOffsets
{
	DNS_FOOT_QTYPE,
	DNS_FOOT_QCLASS
};

enum SectionSizes
{
	DNS_HDRLEN = 12,
	DNS_QUESTION_FOOTER = 4,
	DNS_ANS_HDRLEN = 12
};

enum QTypes
{
	QTYPE_ADDR_IPV4 = 1,
	QTYPE_ADDR_IPV6 = 28
};

enum QClasses
{
	QCLASS_INTERNET = 1
};


//// DNSClient

bool DNSClient::GetServerAddr()
{
	// Mark server address as invalid
	_server_addr.Invalidate();

#if defined(CAT_OS_WINDOWS) || defined(CAT_OS_WINDOWS_CE)

	// Based on approach used in Tiny Asynchronous DNS project by
	// Sergey Lyubka <valenok@gmail.com>.  I owe you a beer! =)
	const int SUBKEY_NAME_MAXLEN = 512;
	const int SUBKEY_DATA_MAXLEN = 512;

	// Open Tcpip Interfaces key
	HKEY key;
	LSTATUS err = RegOpenKey(HKEY_LOCAL_MACHINE,
		"SYSTEM\\ControlSet001\\Services\\Tcpip\\Parameters\\Interfaces", &key);

	// Handle errors opening the key
	if (err != ERROR_SUCCESS)
	{
		WARN("DNS") << "Initialization: Unable to open registry key for Tcpip interfaces: " << err;
		return false;
	}

	// For each subkey,
	char subkey_name[SUBKEY_NAME_MAXLEN];
	for (int ii = 0; ERROR_SUCCESS == RegEnumKey(key, ii, subkey_name, sizeof(subkey_name)); ++ii)
	{
		HKEY subkey;

		// Open interface subkey
		if (ERROR_SUCCESS == RegOpenKey(key, subkey_name, &subkey))
		{
			BYTE data[SUBKEY_DATA_MAXLEN];
			DWORD type, data_len = sizeof(data);

			// Get subkey's DhcpNameServer value
			if (ERROR_SUCCESS == RegQueryValueEx(subkey, "DhcpNameServer", 0, &type, data, &data_len))
			{
				// If type is a string,
				if (type == REG_EXPAND_SZ || type == REG_SZ)
				{
					// Insure it is nul-terminated
					data[sizeof(data) - 1] = '\0';

					// Replace the first non-number/dot with nul
					for (int ii = 0; ii < sizeof(data); ++ii)
					{
						char ch = data[ii];

						if ((ch < '0' || ch > '9') && ch != '.')
						{
							data[ii] = '\0';
							break;
						}
					}

					// Convert address string to binary address
					NetAddr addr((const char*)data, 53);

					// If address is routable,
					if (addr.IsRoutable())
					{
						// Set server address to the last valid one in the enumeration
						_server_addr = addr;
					}
				}
			}
		}
	}

	RegCloseKey(key);

#else // Unix version:

	const char *DNS_ADDRESS_FILE = "/etc/resolv.conf";
	std::ifstream file(DNS_ADDRESS_FILE);

	if (!!file)
	{
		const int LINE_MAXCHARS = 512;
		char line[LINE_MAXCHARS];

		// For each line in the address file,
		while (file.getline(line, sizeof(line)))
		{
			// Insure the line is nul-terminated
			line[sizeof(line)-1] = '\0';

			int a, b, c, d;

			// If the line contains a nameserver addrses in dot-decimal format,
			if (std::sscanf(line, "nameserver %d.%d.%d.%d", &a, &b, &c, &d) == 4)
			{
				NetAddr addr(a, b, c, d, 53);

				// If address is routable,
				if (addr.IsRoutable())
				{
					// Set server address to the last valid one in the enumeration
					_server_addr = addr;
				}
			}
		}
	}

#endif

	// Return success if server address is now valid
	if (_server_addr.Valid() &&
		_server_addr.Convert(Is6()))
	{
		INANE("DNS") << "Using nameserver at " << _server_addr.IPToString();
	}
	else
	{
		const char *ANYCAST_DNS_SERVER = "4.2.2.1"; // Level 3 / Verizon

		WARN("DNS") << "Unable to determine nameserver from OS.  Using anycast address " << ANYCAST_DNS_SERVER;

		// Attempt to get server address from anycast DNS server string
		if (!_server_addr.SetFromString(ANYCAST_DNS_SERVER, 53) ||
			!_server_addr.Convert(Is6()))
		{
			FATAL("DNS") << "Unable to resolve anycast address " << ANYCAST_DNS_SERVER;
			return false;
		}
	}

	return true;
}

bool DNSClient::PostDNSPacket(DNSRequest *req, u32 now)
{
	// Allocate post buffer
	int str_len = (int)strlen(req->hostname);
	int bytes = DNS_HDRLEN + 1 + str_len + 1 + DNS_QUESTION_FOOTER;

	// Write header
	u8 *dns_packet = AsyncBuffer::Acquire(bytes);
	if (!dns_packet) return false;
	u16 *dns_hdr = reinterpret_cast<u16*>( dns_packet );

	dns_hdr[DNS_ID] = req->id; // Endianness doesn't matter
	dns_hdr[DNS_HDR] = getBE16(1 << DNSHDR_RD);
	dns_hdr[DNS_QDCOUNT] = getBE16(1); // One question
	dns_hdr[DNS_ANCOUNT] = 0;
	dns_hdr[DNS_NSCOUNT] = 0;
	dns_hdr[DNS_ARCOUNT] = 0;

	// Copy hostname over
	int last_dot = str_len-1;

	dns_packet[DNS_HDRLEN + 1 + str_len] = '\0';

	for (int ii = last_dot; ii >= 0; --ii)
	{
		u8 byte = req->hostname[ii];

		// Replace dots with label lengths
		if (byte == '.')
		{
			byte = (u8)(last_dot - ii);
			last_dot = ii-1;
		}

		dns_packet[DNS_HDRLEN + ii + 1] = byte;
	}

	dns_packet[DNS_HDRLEN] = (u8)(last_dot + 1);

	// Write request footer
	u16 *foot = reinterpret_cast<u16*>( dns_packet + DNS_HDRLEN + 1 + str_len + 1 );

	foot[DNS_FOOT_QTYPE] = getBE16(QTYPE_ADDR_IPV4);
	foot[DNS_FOOT_QCLASS] = getBE16(QCLASS_INTERNET);

	// Post DNS request
	req->last_post_time = now;

	return Post(_server_addr, dns_packet, bytes);
}

bool DNSClient::PerformLookup(DNSRequest *req)
{
	u32 now = Clock::msec_fast();

	if (!PostDNSPacket(req, now))
		return false;

	req->first_post_time = now;

	// Insert at end of list
	req->next = 0;
	req->last = _request_tail;
	if (_request_tail) _request_tail->next = req;
	else _request_head = req;
	_request_tail = req;

	++_request_queue_size;

	return true;
}

void DNSClient::CacheAdd(DNSRequest *req)
{
	// If still growing cache,
	if (_cache_size < DNSCACHE_MAX_REQS)
		_cache_size++;
	else
	{
		// Remove oldest one from cache
		DNSRequest *tokill = _cache_tail;

		if (tokill)
		{
			DNSRequest *last = tokill->last;

			_cache_tail = last;
			if (last) last->next = 0;
			else _cache_head = 0;

			delete tokill;
		}
	}

	// Insert at head
	req->next = _cache_head;
	req->last = 0;
	if (_cache_head) _cache_head->last = req;
	else _cache_tail = req;
	_cache_head = req;

	// Set update time
	req->last_post_time = Clock::msec_fast();
}

DNSRequest *DNSClient::CacheGet(const char *hostname)
{
	u32 now = Clock::msec_fast();

	// For each cache entry,
	for (DNSRequest *req = _cache_head; req; req = req->next)
	{
		// If the cache has not expired,
		if (now - req->last_post_time < DNSCACHE_TIMEOUT)
		{
			// If hostname of cached request equals the new request,
			if (iStrEqual(req->hostname, hostname))
				return req;
		}
		else
		{
			// Unlink remainder of list (they will all be old)
			DNSRequest *last = req->last;

			_cache_tail = last;
			if (last) last->next = 0;
			else _cache_head = 0;

			// For each item that was unlinked,
			for (DNSRequest *next, *tokill = req; tokill; tokill = next)
			{
				next = tokill->next;

				// Delete each item
				delete tokill;

				// Reduce the cache size
				--_cache_size;
			}

			// Return indicating that the cache did not contain the hostname
			return 0;
		}
	}

	return 0;
}

void DNSClient::CacheKill(DNSRequest *req)
{
	// Unlink from doubly-linked list
	DNSRequest *last = req->last;
	DNSRequest *next = req->next;

	if (last) last->next = next;
	else _cache_head = next;
	if (next) next->last = last;
	else _cache_tail = last;

	--_cache_size;

	// Free memory
	delete req;
}

bool DNSClient::ThreadFunction(void *param)
{
	// Check for timeouts
	while (!_kill_flag.Wait(TICK_RATE))
	{
		AutoMutex lock(_request_lock);

		// Cache current time
		u32 now = Clock::msec_fast();

		// For each pending request,
		for (DNSRequest *req_next, *req = _request_head; req; req = req_next)
		{
			req_next = req->next; // cached for deletion

			// If the request has timed out or reposting failed,
			if ((now - req->first_post_time >= DNSREQ_TIMEOUT) ||
				(now - req->last_post_time >= DNSREQ_REPOST_TIME && !PostDNSPacket(req, now)))
			{
				// Unlink from doubly-linked list
				DNSRequest *next = req->next;
				DNSRequest *last = req->last;

				if (next) next->last = last;
				else _request_tail = last;
				if (last) last->next = next;
				else _request_head = next;

				NotifyRequesters(req);
			}
		}
	}

	return true;
}

DNSClient::~DNSClient()
{
	_kill_flag.Set();

	if (!WaitForThread(DNS_THREAD_KILL_TIMEOUT))
		AbortThread();
}

bool DNSClient::BindToRandomPort(bool ignoreUnreachable)
{
	// NOTE: Ignores ICMP unreachable errors from DNS server; prefers timeouts

	// Attempt to bind to a more random port.
	// This is the standard fix for Dan Kaminsky's DNS exploit
	const int RANDOM_BIND_ATTEMPTS_MAX = 16;

	// Get SupportIPv6 flag from settings
	bool only_ipv4 = Settings::ii->getInt("DNS.Client.SupportIPv6", 0) == 0;

	// Try to use a more random port
	int tries = RANDOM_BIND_ATTEMPTS_MAX;
	while (tries--)
	{
		// Generate a random port
		Port port = (u16)_csprng->Generate();

		// If bind succeeded,
		if (port >= 1024 && Bind(only_ipv4, port, ignoreUnreachable))
			return true;
	}

	// Fall back to OS-chosen port
	return Bind(only_ipv4, 0, ignoreUnreachable);
}

bool DNSClient::Initialize()
{
	_dns_unavailable = true;

	// Create a CSPRNG
	_csprng = FortunaFactory::ii->Create();
	if (!_csprng)
	{
		WARN("DNS") << "Initialization failure: Unable create CSPRNG";
		return false;
	}

	// Attempt to bind to any port; ignore ICMP unreachable messages
	if (!BindToRandomPort(true))
	{
		WARN("DNS") << "Initialization failure: Unable to bind to any port";
		return false;
	}

	// Attempt to get server address from operating system
	if (!GetServerAddr())
	{
		WARN("DNS") << "Initialization failure: Unable to discover DNS server address";
		Close();
		return false;
	}

	// Attempt to start the timer thread
	if (!StartThread())
	{
		WARN("DNS") << "Initialization failure: Unable to start timer thread";
		Close();
		return false;
	}

	_dns_unavailable = false;

	return true;
}

void DNSClient::Shutdown()
{
	// NOTE: Does not remove artificial reference added on Initialize(), so
	// the object is not actually destroyed.  We allow the ThreadPool to
	// destroy this object after all the worker threads are dead.

	Close();
}

bool DNSClient::GetUnusedID(u16 &unused_id)
{
	// If too many requests already pending,
	if (_request_queue_size >= DNSREQ_MAX_SIMUL)
		return false;

	// Attempt to generate an unused ID
	const int INCREMENT_THRESHOLD = 32;
	bool already_used;
	int tries = 0;
	u16 id;
	do 
	{
		// If we have been sitting here trying for a long time,
		if (++tries >= INCREMENT_THRESHOLD)
			++id; // Just use incrementing IDs to insure we exit eventually
		else
			id = (u16)_csprng->Generate(); // Generate a random ID

		// For each pending request,
		already_used = false;
		for (DNSRequest *req = _request_head; req; req = req->next)
		{
			// If the ID is already used,
			if (req->id == id)
			{
				// Try again
				already_used = true;
				break;
			}
		}
	} while (already_used);

	unused_id = id;

	return true;
}

bool DNSClient::IsValidHostname(const char *hostname)
{
	int str_len = (int)strlen(hostname);

	// Name can be up to 63 characters
	if (str_len > HOSTNAME_MAXLEN)
		return false;

	// Initialize state
	char last_char = '\0';
	bool seen_alphabetic = false;

	// For each symbol in the hostname,
	++str_len;
	for (int ii = 0; ii < str_len; ++ii)
	{
		char symbol = hostname[ii];

		// Switch based on symbol type:
		if ((symbol >= 'A' && symbol <= 'Z') ||
			(symbol >= 'a' && symbol <= 'z')) // Alphabetic
		{
			seen_alphabetic = true;
			// Don't react to alphabetic until label end
		}
		else if (symbol >= '0' && symbol <= '9') // Numeric
		{
			// Don't react to numeric until label end
		}
		else if (symbol == '-') // Dash
		{
			// Don't allow strings of - or start with -
			if (last_char == '-' || last_char == '\0') return false;
		}
		else if (symbol == '.' || symbol == '\0') // End of a label
		{
			// If we didn't see an alphabetic character in this label,
			if (!seen_alphabetic) return false;

			// If last character in label was not alphanumeric,
			if ((last_char < 'A' || last_char > 'Z') &&
				(last_char < 'a' || last_char > 'z') &&
				(last_char < '0' || last_char > '9'))
			{
				return false;
			}

			// Reset state for next label
			seen_alphabetic = false;
			last_char = '\0';

			continue;
		}
		else
		{
			return false;
		}

		last_char = symbol;
	}

	return true;
}

bool DNSClient::Resolve(const char *hostname, DNSResultCallback callback, ThreadRefObject *holdRef)
{
	// Initialize if needed
	if (_dns_unavailable && !Initialize())
		return false;

	// Try to interpret hostname as numeric
	NetAddr addr(hostname);

	// If it was numeric,
	if (addr.Valid())
	{
		// Immediately invoke callback
		callback(hostname, &addr, 1);

		return true;
	}

	// If hostname is invalid,
	if (!IsValidHostname(hostname))
		return false;

	AutoMutex cache_lock(_cache_lock);

	// Check cache
	DNSRequest *cached_request = CacheGet(hostname);

	// If it was in the cache,
	if (cached_request)
	{
		// Immediately invoke callback
		if (!callback(hostname, cached_request->responses, cached_request->num_responses))
		{
			// Kill cached request when asked
			CacheKill(cached_request);
		}

		return true;
	}

	cache_lock.Release();

	// If DNS lookup is unavailable,
	if (_dns_unavailable)
		return false;

	AutoMutex req_lock(_request_lock);

	for (DNSRequest *req = _request_head; req; req = req->next)
	{
		if (iStrEqual(req->hostname, hostname))
		{
			DNSCallback *cb = new DNSCallback;
			if (!cb) return false;

			if (holdRef) holdRef->AddRef();

			cb->cb = callback;
			cb->ref = holdRef;
			cb->next = req->callback_head.next;
			req->callback_head.next = cb;

			return true;
		}
	}

	// Get an unused ID
	u16 id;
	if (!GetUnusedID(id))
	{
		WARN("DNS") << "Too many DNS requests pending";
		return false;
	}

	// Create a new request
	DNSRequest *request = new DNSRequest;
	if (!request) return false;

	// Fill request
	CAT_STRNCPY(request->hostname, hostname, sizeof(request->hostname));
	request->callback_head.ref = holdRef;
	request->callback_head.cb = callback;
	request->callback_head.next = 0;
	request->id = id;

	if (holdRef) holdRef->AddRef();

	// Attempt to perform lookup
	if (!PerformLookup(request))
	{
		ThreadRefObject::SafeRelease(holdRef);
		return false;
	}

	return true;
}

void DNSClient::OnUnreachable(const NetAddr &src)
{
	// TODO: Recover from server failure by re-detecting servers

	// If IP matches the server and we're not connected yet,
	if (_server_addr.EqualsIPOnly(src))
	{
		WARN("DNS") << "Failed to contact DNS server: ICMP error received from server address";

		// Close socket so that DNS resolves will be squelched
		Close();
	}
}

DNSRequest *DNSClient::PullRequest(u16 id)
{
	// For each pending request,
	for (DNSRequest *req = _request_head; req; req = req->next)
	{
		// If ID matches,
		if (req->id == id)
		{
			// Remove from doubly-linked list
			DNSRequest *last = req->last;
			DNSRequest *next = req->next;

			if (last) last->next = next;
			else _request_head = next;
			if (next) next->last = last;
			else _request_tail = last;

			return req;
		}
	}

	return 0;
}

void DNSClient::NotifyRequesters(DNSRequest *req)
{
	bool add_to_cache = false;

	// Invoke the callback
	add_to_cache |= req->callback_head.cb(req->hostname, req->responses, req->num_responses);

	// Release ref if requested
	ThreadRefObject::SafeRelease(req->callback_head.ref);

	// For each requester,
	for (DNSCallback *cbnext, *cb = req->callback_head.next; cb; cb = cbnext)
	{
		cbnext = cb->next; // cache for deletion

		// Invoke the callback
		add_to_cache |= cb->cb(req->hostname, req->responses, req->num_responses);

		// Release ref if requested
		ThreadRefObject::SafeRelease(cb->ref);

		delete cb;
	}

	// If any of the callbacks requested us to add it to the cache,
	if (add_to_cache)
	{
		AutoMutex lock(_cache_lock);
		CacheAdd(req);
	}
	else
	{
		delete req;
	}
}

void DNSClient::ProcessDNSResponse(DNSRequest *req, int qdcount, int ancount, u8 *data, u32 bytes)
{
	u32 offset = DNS_HDRLEN;

	// Get past question part
	while (qdcount-- > 0)
	{
		while (offset < bytes)
		{
			u8 byte = data[offset++];
			if (!byte) break;

			offset += byte;
		}

		offset += 4;

		// On overflow,
		if (offset >= bytes)
		{
			return;
		}
	}

	// Crunch answers
	while (ancount-- > 0)
	{
		while (offset < bytes)
		{
			u16 *words = reinterpret_cast<u16*>( data + offset );

			//u16 name_offset = getBE(words[0]);
			u16 name_type = getBE(words[1]);
			u16 name_class = getBE(words[2]);
			//u32 name_ttl = getBE(words[3] | words[4]);
			u16 addr_len = getBE(words[5]);
			u8 *addr_data = data + offset + DNS_ANS_HDRLEN;

			offset += DNS_ANS_HDRLEN + addr_len;

			// 32-bit IPv4
			if (name_type == QTYPE_ADDR_IPV4 &&
				name_class == QCLASS_INTERNET &&
				addr_len == NetAddr::IP4_BYTES && offset <= bytes &&
				req->responses[req->num_responses].SetFromRawIP(addr_data, NetAddr::IP4_BYTES))
			{
				if (++req->num_responses >= DNSCACHE_MAX_RESP)
				{
					return;
				}
			}

			// 128-bit IPv6
			if (name_type == QTYPE_ADDR_IPV6 &&
				name_class == QCLASS_INTERNET &&
				addr_len == NetAddr::IP6_BYTES && offset <= bytes &&
				req->responses[req->num_responses].SetFromRawIP(addr_data, NetAddr::IP6_BYTES))
			{
				if (++req->num_responses >= DNSCACHE_MAX_RESP)
				{
					return;
				}
			}
		}

		// On overflow,
		if (offset >= bytes)
		{
			return;
		}
	}
}

void DNSClient::OnRead(ThreadPoolLocalStorage *tls, const NetAddr &src, u8 *data, u32 bytes)
{
	// If packet source is not the server, ignore this packet
	if (_server_addr != src)
		return;

	// If packet is truncated, ignore this packet
	if (bytes < DNS_HDRLEN)
		return;

	u16 *hdr_words = reinterpret_cast<u16*>( data );

	// QR(1) OPCODE(4) AA(1) TC(1) RD(1) RA(1) Z(3) RCODE(4) [=16]
	u16 hdr = getBE(hdr_words[DNS_HDR]);

	// Header bits
	u16 qr = (hdr >> DNSHDR_QR) & 1; // Response
	u16 opcode = (hdr >> DNSHDR_OPCODE) & 0x000F; // Opcode

	// If header is invalid, ignore this packet
	if (!qr || opcode != 0) return;

	// Extract ID; endian agnostic
	u16 id = hdr_words[DNS_ID];

	AutoMutex lock(_request_lock);

	// Pull request from pending queue
	DNSRequest *req = PullRequest(id);

	// If request was not found to match ID,
	if (!req) return;

	// Initialize number of responses to zero
	req->num_responses = 0;

	//u16 aa = (hdr >> DNSHDR_AA) & 1; // Authoritative
	//u16 tc = (hdr >> DNSHDR_TC) & 1; // Truncated
	//u16 rd = (hdr >> DNSHDR_RD) & 1; // Recursion desired
	//u16 ra = (hdr >> DNSHDR_RA) & 1; // Recursion available
	//u16 z = (hdr >> DNSHDR_Z) & 0x0007; // Reserved
	u16 rcode = hdr & 0x000F; // Reply code

	// If non-error result,
	if (rcode == 0)
	{
		int qdcount = getBE(hdr_words[DNS_QDCOUNT]); // Question count
		int ancount = getBE(hdr_words[DNS_ANCOUNT]); // Answer RRs
		//int nscount = getBE(hdr_words[DNS_NSCOUNT]); // Authority RRs
		//int arcount = getBE(hdr_words[DNS_ARCOUNT]); // Additional RRs

		ProcessDNSResponse(req, qdcount, ancount, data, bytes);
	}

	NotifyRequesters(req);
}

void DNSClient::OnClose()
{
	// Marks DNS as unavailable OnClose() so that further resolve requests are squelched.
	_dns_unavailable = true;
}
