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

#ifndef CAT_SPHYNX_SERVER_HPP
#define CAT_SPHYNX_SERVER_HPP

#include <cat/net/SphynxTransport.hpp>
#include <cat/threads/RWLock.hpp>
#include <cat/threads/Thread.hpp>
#include <cat/threads/WaitableFlag.hpp>
#include <cat/net/SphynxCollexion.hpp>
#include <cat/crypt/cookie/CookieJar.hpp>
#include <cat/crypt/tunnel/KeyAgreementResponder.hpp>

namespace cat {


namespace sphynx {


/*
	Designed for server hardware with many processors.

	In order to handle many users, the Sphynx server opens up a single UDP port
	to accept new connections, and several other UDP data ports for data.

	For retransmissions and detecting link loss due to timeout, the server runs
	several additional threads that wake up periodically to perform timed tasks.

	Server uses thread pool to receive packets on connect and worker ports,
	meaning that packets are processed by any free CPU as soon as they arrive.

	Sphynx Server
		UDP Hello Port [1]
			+ In case this thread spins constantly, only use one CPU for new
			  connections since in-game experience is more important than login
		    + Assigns users to a data port after handshake completes

		UDP Data Ports [4 * (CPU Count)]
			+ Spread users evenly across several ports since
			  only one packet can be processed from a single port at a time
		    + Any free CPU will process incoming packets as fast as possible

		ServerTimer threads [(CPU Count) / 2]
			+ In case these threads spin constantly, they only consume
			  half of the CPU resources available
			+ Wake up every X milliseconds according to Transport::TICK_RATE
			+ Detect link loss due to silence timeout
			+ Update transport layer
				+ Retransmit lost messages
				+ Re-evaluate bandwidth and transmit queued messages
*/


//// sphynx::Connexion

// Derive from sphynx::Connexion and sphynx::Server to define server behavior
class Connexion : public Transport, public ThreadRefObject
{
	friend class Server;
	friend class Map;
	friend class ServerWorker;
	friend class ServerTimer;

public:
	Connexion();
	virtual ~Connexion() {}

private:
	volatile u32 _destroyed;

	u32 _key; // Map hash table index, unique for each active connection
	Connexion *_next_delete;
	ServerWorker *_server_worker;

	u8 _first_challenge[64]; // First challenge seen from this client address
	u8 _cached_answer[128]; // Cached answer to this first challenge, to avoid eating server CPU time

private:
	// Return false to destroy this object
	bool Tick(ThreadPoolLocalStorage *tls, u32 now);

	void OnRawData(ThreadPoolLocalStorage *tls, u8 *data, u32 bytes);

	virtual bool PostPacket(u8 *buffer, u32 buf_bytes, u32 msg_bytes, u32 skip_bytes);

public:
	CAT_INLINE bool IsValid() { return _destroyed == 0; }
	CAT_INLINE u32 GetKey() { return _key; }

	void Destroy();

protected:
	NetAddr _client_addr;

	// Last time a packet was received from this user -- for disconnect timeouts
	u32 _last_recv_tsc;

	bool _seen_encrypted;
	AuthenticatedEncryption _auth_enc;

protected:
	virtual void OnConnect(ThreadPoolLocalStorage *tls) = 0;
	virtual void OnDestroy() = 0;
	virtual void OnTick(ThreadPoolLocalStorage *tls, u32 now) = 0;
};


//// sphynx::Map

class Map
{
protected:
	CAT_INLINE u32 hash_addr(const NetAddr &addr, u32 salt);

public:
	struct Slot
	{
		Connexion *connection;
		bool collision;
		Slot *next;
	};

protected:
	u32 _hash_salt;
	CAT_ALIGNED(16) Slot _table[HASH_TABLE_SIZE];
	RWLock _table_lock;

public:
	Map();
	virtual ~Map();

	// Lookup client by address
	Connexion *Lookup(const NetAddr &addr);

	// Lookup client by key
	Connexion *Lookup(u32 key);

	// May return false if network address in Connexion is already in the map.
	// This averts a potential race condition but should never happen during
	// normal operation, so the Connexion allocation by caller won't be wasted.
	bool Insert(Connexion *conn);

	// Destroy a list described by the 'next' member of Slot
	void DestroyList(Map::Slot *kill_list);

	void Tick(ThreadPoolLocalStorage *tls);
};


//// sphynx::ServerWorker

class ServerWorker : public UDPEndpoint
{
	friend class Map;

protected:
	Map *_conn_map;
	ServerTimer *_server_timer;

protected:
	volatile u32 _session_count;

public:
	ServerWorker(Map *conn_map, ServerTimer *server_timer);
	virtual ~ServerWorker();

	void IncrementPopulation();
	void DecrementPopulation();
	u32 GetPopulation() { return _session_count; }

protected:
	void OnRead(ThreadPoolLocalStorage *tls, const NetAddr &src, u8 *data, u32 bytes);
	void OnWrite(u32 bytes) {}
	void OnClose();
};


//// sphynx::ServerTimer

class ServerTimer : Thread
{
protected:
	Map *_conn_map;

protected:
	ServerWorker **_workers;
	int _worker_count;

protected:
	Map::Slot *_insert_head;
	Mutex _insert_lock;

protected:
	Map::Slot *_active_head;

public:
	ServerTimer(Map *conn_map, ServerWorker **workers, int worker_count);
	virtual ~ServerTimer();

	CAT_INLINE bool Valid() { return _worker_count > 0; }

public:
	void InsertSlot(Map::Slot *slot);

protected:
	CAT_INLINE void Tick(ThreadPoolLocalStorage *tls);
	bool ThreadFunction(void *param);

protected:
	static const int TIMER_THREAD_KILL_TIMEOUT = 10000;

	WaitableFlag _kill_flag;
};


//// sphynx::Server

class Server : public UDPEndpoint
{
public:
	Server();
	virtual ~Server();

	bool StartServer(ThreadPoolLocalStorage *tls, Port port, u8 *public_key, int public_bytes, u8 *private_key, int private_bytes, const char *session_key);

	u32 GetTotalPopulation();

	static bool GenerateKeyPair(ThreadPoolLocalStorage *tls, const char *public_key_file,
		const char *private_key_file, u8 *public_key,
		int public_bytes, u8 *private_key, int private_bytes);

private:
	static const int SESSION_KEY_BYTES = 32;
	char _session_key[SESSION_KEY_BYTES];

	Port _server_port;
	Map _conn_map;

	CookieJar _cookie_jar;
	KeyAgreementResponder _key_agreement_responder;
	u8 _public_key[PUBLIC_KEY_BYTES];

	static const int WORKER_LIMIT = 32; // Maximum number of workers
	ServerWorker **_workers;
	int _worker_count;

	ServerTimer **_timers;
	int _timer_count;

private:
	ServerWorker *FindLeastPopulatedPort();

	void OnRead(ThreadPoolLocalStorage *tls, const NetAddr &src, u8 *data, u32 bytes);
	void OnWrite(u32 bytes);
	void OnClose();

protected:
	// Must return a new instance of your Connexion derivation
	virtual Connexion *NewConnexion() = 0;

	// IP address filter: Return true to allow the connection to be made
	virtual bool AcceptNewConnexion(const NetAddr &src) = 0;

	// Lookup client by key
	Connexion *Lookup(u32 key);
};


} // namespace sphynx


} // namespace cat

#endif // CAT_SPHYNX_SERVER_HPP
