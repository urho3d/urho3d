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

#if defined(CAT_OS_WINDOWS) && !defined(CAT_OS_WINDOWS_CE)

/*
    Windows entropy sources inspired by the Fortuna implementation from
    http://www.citadelsoftware.ca/fortuna/Fortuna.htm
*/

#include <cat/math/BitMath.hpp>
#include <cat/time/Clock.hpp>

// Include and link to various Windows libraries needed to collect system info
#include <Psapi.h>
#include <Lmcons.h>   // LAN-MAN constants for "UNLEN" username max length
#include <Iphlpapi.h> // GetAdaptersInfo()
#include <Process.h>  // _beginthreadex()

#pragma comment(lib, "iphlpapi")
#pragma comment(lib, "advapi32")

#if !defined(CAT_NO_ENTROPY_THREAD)

bool FortunaFactory::ThreadFunction(void *)
{
    // Assume ~16 bits of entropy per fast poll, so it takes 16 fast polls to get 256 bits of entropy
    // This means there will be 4 slow polls in pool 0 for each reseed, which is 256 bits from CryptoAPI
    const int POOL0_RESEED_RATE = 16;

    // Milliseconds between fast polls
    // Indicates 512 seconds between reseeds
    const int COLLECTION_PERIOD = 1000;

    int fast_pool = 0, slow_pool = 0, pool0_entropy = 0;

    // Loop while the wait is timing out; will break on error or signaled termination
    while (!_kill_flag.Wait(COLLECTION_PERIOD))
    {
        // Poll fast entropy sources once every COLLECTION_PERIOD
        PollFastEntropySources(fast_pool);

        // Poll slow entropy sources 4 times slower
        if ((fast_pool & 3) == 0)
        {
            PollSlowEntropySources(slow_pool);

            // Keep track of entropy in pool 0 and reseed when it is ready
            if (fast_pool == 0 && ++pool0_entropy >= POOL0_RESEED_RATE)
            {
                FortunaFactory::ii->Reseed();
                pool0_entropy = 0;
            }
        }

        slow_pool = (slow_pool + 1) % 32;
        fast_pool = (fast_pool + 1) % 32;
    }

	return true;
}

#endif // !defined(CAT_NO_ENTROPY_THREAD)


bool FortunaFactory::InitializeEntropySources()
{
	NtQuerySystemInformation = 0;
	NTDLL = 0;

    // Initialize a session with the CryptoAPI using newer cryptoprimitives (AES)
    CurrentProcess = GetCurrentProcess();
    if (!CryptAcquireContext(&hCryptProv, 0, 0, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
        return false;

	NTDLL = LoadLibraryA("NtDll.dll");
	if (NTDLL)
		NtQuerySystemInformation = (PtNtQuerySystemInformation)GetProcAddress(NTDLL, "NtQuerySystemInformation");

    // Fire poll for entropy all goes into pool 0
    PollInvariantSources(0);
    PollSlowEntropySources(0);
    PollFastEntropySources(0);

#if defined(CAT_NO_ENTROPY_THREAD)
	return true;
#else
	return StartThread();
#endif
}

void FortunaFactory::ShutdownEntropySources()
{
#if !defined(CAT_NO_ENTROPY_THREAD)
	_kill_flag.Set();

	if (!WaitForThread(ENTROPY_THREAD_KILL_TIMEOUT))
		AbortThread();
#endif

    if (hCryptProv) CryptReleaseContext(hCryptProv, 0);
	if (NTDLL) FreeLibrary(NTDLL);
}

void FortunaFactory::PollInvariantSources(int pool_index)
{
    Skein &pool = Pool[pool_index];

	struct {
		u32 cycles_start;
	    u8 system_prng[32];
	    SYSTEM_INFO sys_info;
	    TCHAR computer_name[MAX_COMPUTERNAME_LENGTH + 1];
	    HW_PROFILE_INFO hw_profile;
		DWORD win_ver;
	    DWORD reg_quota[2];
	    STARTUPINFO startup_info;
	    MEMORYSTATUS mem_status;
		u32 cycles_end;
	} Sources;

    // Cycles at the start
    Sources.cycles_start = Clock::cycles();

	// System information
	if (NtQuerySystemInformation)
	{
		u8 sysbuf[640];
		for (int i = 0; i < 128; ++i)
		{
			ULONG retlen = 0;
			if (NtQuerySystemInformation(i, sysbuf, sizeof(sysbuf), &retlen) == 0 && retlen > 0)
				pool.Crunch(sysbuf, retlen);
		}
	}

    // CryptoAPI PRNG: Large request
    CryptGenRandom(hCryptProv, sizeof(Sources.system_prng), (BYTE*)Sources.system_prng);

    // System info
    GetSystemInfo(&Sources.sys_info);

    // NetBIOS name
    DWORD name_len = sizeof(Sources.computer_name) / sizeof(TCHAR);
    GetComputerName(Sources.computer_name, &name_len);

    // User name
    TCHAR user_name[UNLEN + 1];
    DWORD user_len = sizeof(user_name) / sizeof(TCHAR);
    if (GetUserName(user_name, &user_len))
		pool.Crunch(user_name, user_len * sizeof(TCHAR));

    // Hardware profile
    GetCurrentHwProfile(&Sources.hw_profile);

    // Windows version
	#pragma warning(push)
	// allow using deprecated function - we cannot switch the code to use the suggested VerifyVersionInfo() function
	// since that would require an API/ABI breakage here
	#pragma warning(disable:4996)
	Sources.win_ver = GetVersion();
	#pragma warning (pop)

    // Registry quota
    GetSystemRegistryQuota(&Sources.reg_quota[0], &Sources.reg_quota[1]);

    // Network adapter info
    IP_ADAPTER_INFO adapter_info[16];
    DWORD adapter_len = sizeof(adapter_info);
    if (ERROR_SUCCESS == GetAdaptersInfo(adapter_info, &adapter_len))
        for (IP_ADAPTER_INFO *adapter = adapter_info; adapter; adapter = adapter->Next)
            pool.Crunch(adapter, sizeof(*adapter));

    // Startup info
    GetStartupInfo(&Sources.startup_info);

    // Global memory status
    GlobalMemoryStatus(&Sources.mem_status);

    // Current process handle
    pool.Crunch(&CurrentProcess, sizeof(CurrentProcess));

    // Cycles at the end
    Sources.cycles_end = Clock::cycles();

	pool.Crunch(&Sources, sizeof(Sources));
}

void FortunaFactory::PollSlowEntropySources(int pool_index)
{
    Skein &pool = Pool[pool_index];

	struct {
		u32 cycles_start;
		POINT cursor_pos;
		u8 system_prng[8];
		double this_request;
		double request_diff;
	    FILETIME ft_creation, ft_exit, ft_kernel, ft_user;
	    FILETIME ft_idle, ft_sys_kernel, ft_sys_user;
	    MEMORYSTATUSEX mem_stats;
		u32 cycles_end;
	} Sources;

	ULONG retlen;
	u8 sysbuf[640];

    // Cycles at the start
    Sources.cycles_start = Clock::cycles();

	if (NtQuerySystemInformation)
	{
		// System performance info
		retlen = 0;
		if (NtQuerySystemInformation(2, sysbuf, sizeof(sysbuf), &retlen) == 0 && retlen > 0)
			pool.Crunch(sysbuf, retlen);

		// System interrupt info
		retlen = 0;
		if (NtQuerySystemInformation(23, sysbuf, sizeof(sysbuf), &retlen) == 0 && retlen > 0)
			pool.Crunch(sysbuf, retlen);
	}

    // Cursor position
    GetCursorPos(&Sources.cursor_pos);

    // CryptoAPI PRNG: Small request
    CryptGenRandom(hCryptProv, sizeof(Sources.system_prng), (BYTE*)Sources.system_prng);

    // Poll time in microseconds
    Sources.this_request = Clock::usec();

    // Time since last poll in microseconds
    static double last_request = 0;
    Sources.request_diff = Sources.this_request - last_request;
    last_request = Sources.this_request;

    // Process times
    GetProcessTimes(CurrentProcess, &Sources.ft_creation, &Sources.ft_exit, &Sources.ft_kernel, &Sources.ft_user);

	// System times
	GetSystemTimes(&Sources.ft_idle, &Sources.ft_sys_kernel, &Sources.ft_sys_user);

    // Global memory status
	GlobalMemoryStatusEx(&Sources.mem_stats);

    // Cycles at the end
    Sources.cycles_end = Clock::cycles();

    pool.Crunch(&Sources, sizeof(Sources));
}

void FortunaFactory::PollFastEntropySources(int pool_index)
{
    Skein &pool = Pool[pool_index];

	struct {
		u32 cycles_start;
		double this_request;
		double request_diff;
		u32 cycles_end;
	} Sources;

    // Cycles at the start
    Sources.cycles_start = Clock::cycles();

    // Poll time in microseconds
    Sources.this_request = Clock::usec();

    // Time since last poll in microseconds
    static double last_request = 0;
    Sources.request_diff = Sources.this_request - last_request;
    last_request = Sources.this_request;

    // Cycles at the end
    Sources.cycles_end = Clock::cycles();

    pool.Crunch(&Sources, sizeof(Sources));
}

#endif // CAT_OS_WINDOWS
