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

#if defined(CAT_OS_LINUX)

#include <cat/time/Clock.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#if !defined(CAT_NO_ENTROPY_THREAD)

bool FortunaFactory::ThreadFunction(void *)
{
    // Assume ~16 bits of entropy per fast poll, so it takes 16 fast polls to get 256 bits of entropy
    // This means there will be 4 slow polls in pool 0 for each reseed, which is 256 bits from /dev/urandom
    const int POOL0_RESEED_RATE = 16;

    // Milliseconds between fast polls
    // Indicates 512 seconds between reseeds
    const int COLLECTION_PERIOD = 1000;

    int fast_pool = 0, slow_pool = 0, pool0_entropy = 0;

    // Loop while the flag is set
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
    urandom_fd = open("/dev/urandom", O_RDONLY);

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

    if (urandom_fd >= 0)
        close(urandom_fd);
}

static void PollVMStat(Skein &pool)
{
	const char *PATH = "vmstat -s";

	fd_set fds;
	FD_ZERO(&fds);

	if (!access(PATH, F_OK)) return;

	FILE *fp = popen(PATH, "r");
	if (!fp) return;

	int fd = fileno(fp);
	if (fd < 0) return;

	FD_SET(fd, &fds);

	timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;

	int r;
	while ((r = select(1 + fd, &fds, 0, 0, &tv)))
	{
		if (r == -1 || !FD_ISSET(fd, &fds)) break;

		static u8 buffer[4096];
		int count = read(fd, buffer, sizeof(buffer));

		if (count > 0) pool.Crunch(buffer, count);
		else break;
	}

	pclose(fp);
	FD_CLR(fd, &fds);
}

void FortunaFactory::PollInvariantSources(int pool_index)
{
    Skein &pool = Pool[pool_index];

    struct {
        u32 cycles_start;
        u8 system_prng[32];
        u32 pid;
        u32 cycles_end;
    } Sources;

    // Cycles at the start
    Sources.cycles_start = Clock::cycles();

    // /dev/urandom large request
    if (urandom_fd >= 0)
        read(urandom_fd, Sources.system_prng, sizeof(Sources.system_prng));

    // pid
    Sources.pid = (u32)getpid();

	// Poll vmstat -s
	PollVMStat(pool);

    // Cycles at the end
    Sources.cycles_end = Clock::cycles();

    pool.Crunch(&Sources, sizeof(Sources));
}

void FortunaFactory::PollSlowEntropySources(int pool_index)
{
    Skein &pool = Pool[pool_index];

    struct {
        u32 cycles_start;
        u8 system_prng[8];
        double this_request;
        double request_diff;
        u32 cycles_end;
    } Sources;

    // Cycles at the start
    Sources.cycles_start = Clock::cycles();

    // /dev/urandom small request
    if (urandom_fd >= 0)
        read(urandom_fd, Sources.system_prng, sizeof(Sources.system_prng));

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

#endif // CAT_OS_LINUX
