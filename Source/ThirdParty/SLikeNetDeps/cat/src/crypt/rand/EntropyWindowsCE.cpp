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

#include <cat/crypt/rand/Fortuna.hpp>
using namespace cat;

#if defined(CAT_OS_WINDOWS_CE)

// Include and link to various Windows libraries needed to collect system info
#pragma comment(lib, "coredll")

#if !defined(CAT_NO_ENTROPY_THREAD)

bool FortunaFactory::ThreadFunction(void *)
{
	// No entropy collection thread for Windows CE
	// For this platform we just query the CryptoAPI and some other sources
	// on startup and let the PRNG run forever without any new data
	return true;
}

#endif // !defined(CAT_NO_ENTROPY_THREAD)


bool FortunaFactory::InitializeEntropySources()
{
    // Initialize a session with the CryptoAPI using newer cryptoprimitives (AES)
    if (!CryptAcquireContext(&hCryptProv, 0, 0, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
        return false;

    // Fire poll for entropy all goes into pool 0
    PollInvariantSources(0);

    return true;
}

void FortunaFactory::ShutdownEntropySources()
{
    if (hCryptProv) CryptReleaseContext(hCryptProv, 0);
}

void FortunaFactory::PollInvariantSources(int pool_index)
{
    Skein &pool = Pool[pool_index];

	struct {
		u32 cycles_start;
	    u8 system_prng[32];
	    SYSTEM_INFO sys_info;
		DWORD win_ver;
		u32 cycles_end;
	} Sources;

    // Cycles at the start
    Sources.cycles_start = Clock::cycles();

    // CryptoAPI PRNG: Large request
    CryptGenRandom(hCryptProv, sizeof(Sources.system_prng), (BYTE*)Sources.system_prng);

    // System info
    GetSystemInfo(&Sources.sys_info);

    // Windows version
    Sources.win_ver = GetVersion();

    // Cycles at the end
    Sources.cycles_end = Clock::cycles();

	pool.Crunch(&Sources, sizeof(Sources));
}

void FortunaFactory::PollSlowEntropySources(int pool_index)
{
	// Not used
}

void FortunaFactory::PollFastEntropySources(int pool_index)
{
	// Not used
}

#endif
