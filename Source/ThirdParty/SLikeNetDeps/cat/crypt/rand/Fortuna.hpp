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

/*
    Based on Fortuna algorithm from "Practical Cryptography" section 10.3
    Published 2003 by Niels Ferguson and Bruce Schneier

    Fortuna supplements the operating system (OS) pseudo-random number generator (PRNG)
    by incorporating additional entropy into the seeds that the OS provides.

    Modified for use with Skein in PRNG mode, sharing the strengths of both algorithms.

    My implementation of Fortuna (call it Cat For Tuna) has the following components:

    + Entropy Pools
        + 32 pools numbered 0..31
        + Implemented as 32 instances of the 256-bit Skein hash
        + Entropy hashed into pools in a round-robin fashion
        + Scheme allows for recovery against attacker with knowledge of some sources

    + Entropy Sources
        + Uses best OS random number generator
        + And a variable number of OS-dependent entropy sources
        + Mainly cycle counts and other timing information

    + Output Generator
        + Implemented as a 512-bit Skein hash of some combination of the entropy pools
            + The output is produced by the PRNG mode of Skein keyed by the pools
        + Hashing all of these pools together and keying the output is called "seeding"
        + Reseeded after sufficient entropy has been collected in pool 0
        + Pool 0 is always used for reseeding
        + Reseed X uses pools numbered by the 1-bits in X (except MSB)
        + Previous seed keys the next seed
        + Diverges from normal Fortuna due to use of Skein instead of a block cipher
            + Reseeds only once every ~512 seconds
            + Does not have a limit of 2^16 output blocks
            + Skein-PRNG is guaranteed sufficient security properties anyway

    The Fortuna algorithm is broken up into two objects for efficient thread-safety:

    + FortunaFactory
        + Must be initialized on startup and shut down on shutdown
        + Spawns a thread to periodically collect additional entropy
        + Can create FortunaOutput objects

    + FortunaOutput
        + Reseeds based on master seed in the FortunaFactory
            + Reseeds after master seed is updated
        + Provides a unique random stream for each thread that uses Fortuna
*/

#ifndef CAT_FOR_TUNA_HPP
#define CAT_FOR_TUNA_HPP

#include <cat/rand/IRandom.hpp>
#include <cat/crypt/hash/Skein.hpp>
#include <cat/Singleton.hpp>
#include <cat/threads/Mutex.hpp>


// Defining CAT_NO_ENTROPY_THREAD will remove dependencies on pthreads and not
// run a thread to collect more entropy.  This is recommended for low-power targets
// and other systems where no thread library is available
#if defined(CAT_OS_WINDOWS_CE)
# define CAT_NO_ENTROPY_THREAD
#endif


#if defined(CAT_OS_WINDOWS)
# include <cat/port/WindowsInclude.hpp>
# include <wincrypt.h>
#endif

#if !defined(CAT_NO_ENTROPY_THREAD)
# include <cat/threads/Thread.hpp>
# include <cat/threads/WaitableFlag.hpp>
#endif


namespace cat {

class FortunaOutput;
class FortunaFactory;


// Factory for constructing FortunaOutput objects
class FortunaFactory : public Singleton<FortunaFactory>
#if !defined(CAT_NO_ENTROPY_THREAD)
	, public Thread
#endif
{
    CAT_SINGLETON(FortunaFactory)
    {
		_initialized = false;
    }

	Mutex _lock;

    friend class FortunaOutput;

#if defined(CAT_OS_WINDOWS) && !defined(CAT_OS_WINDOWS_CE)

	typedef LONG (WINAPI *PtNtQuerySystemInformation)(
		int SystemInformationClass,
		PVOID SystemInformation,
		ULONG SystemInformationLength,
		PULONG ReturnLength
	);

    HANDLE CurrentProcess;
    HMODULE NTDLL;
    PtNtQuerySystemInformation NtQuerySystemInformation;
    HCRYPTPROV hCryptProv;

#elif defined(CAT_OS_WINDOWS_CE)

	HCRYPTPROV hCryptProv;

#elif defined(CAT_OS_LINUX)

    int urandom_fd;

#endif

#if !defined(CAT_NO_ENTROPY_THREAD)
	static const int ENTROPY_THREAD_KILL_TIMEOUT = 10000; // 10 seconds

	WaitableFlag _kill_flag;

	bool ThreadFunction(void *param);
#endif

protected:
    static const int ENTROPY_POOLS = 32; // Setting this higher would break something
    static const int POOL_BITS = 512;
    static const int POOL_BYTES = POOL_BITS / 8;
    static const int POOL_QWORDS = POOL_BYTES / sizeof(u64);

    static u32 MasterSeedRevision; // Should not roll over for 13 years if incremented once every RESEED_MIN_TIME
    static Skein MasterSeed;

	bool _initialized;
    u32 reseed_counter;
    Skein Pool[ENTROPY_POOLS];

    bool Reseed();
	void GetNextKey(FortunaOutput *output);
    bool InitializeEntropySources();
    void PollInvariantSources(int pool);
    void PollSlowEntropySources(int pool);
    void PollFastEntropySources(int pool);
    void ShutdownEntropySources();

public:
    // Start the entropy generator
    bool Initialize();

    // Stop the entropy generator
    void Shutdown();

    // Create a new Fortuna object
    static FortunaOutput *Create();
};


// LoopThread-safe output object for Fortuna
class FortunaOutput : public IRandom
{
    friend class FortunaFactory;

    static const int OUTPUT_CACHE_BYTES = FortunaFactory::POOL_BYTES * 8; // Arbitrary

    u32 thread_id, SeedRevision;
    Skein OutputHash;
    u8 CachedRandomBytes[OUTPUT_CACHE_BYTES];
    int used_bytes;

    void Reseed();

    FortunaOutput();
    FortunaOutput(FortunaOutput&) {}
    FortunaOutput &operator=(FortunaOutput &) { return *this; }

public:
    ~FortunaOutput();

    // Generate a 32-bit random number
    u32 Generate();

    // Generate a variable number of random bytes
    void Generate(void *buffer, int bytes);
};


} // namespace cat

#endif // CAT_FOR_TUNA_HPP
