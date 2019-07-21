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
#include <cat/time/Clock.hpp>
#include <cat/threads/Atomic.hpp>
using namespace cat;

u32 FortunaFactory::MasterSeedRevision = 0;
Skein FortunaFactory::MasterSeed;



//// FortunaOutput

FortunaOutput::FortunaOutput()
{
    Reseed();
}

FortunaOutput::~FortunaOutput()
{
    CAT_OBJCLR(CachedRandomBytes);
    used_bytes = 0;
    SeedRevision = 0;
    thread_id = 0;
}

void FortunaOutput::Reseed()
{
	FortunaFactory::ii->GetNextKey(this);

    OutputHash.Generate(CachedRandomBytes, OUTPUT_CACHE_BYTES);
    used_bytes = 0;
}

// Generate a 32-bit random number
u32 FortunaOutput::Generate()
{
    u32 x;
    Generate(&x, sizeof(x));
    return x;
}

// Generate a variable number of random bytes
void FortunaOutput::Generate(void *buffer, int bytes)
{
    if (SeedRevision != FortunaFactory::MasterSeedRevision)
        Reseed();

    int remaining = OUTPUT_CACHE_BYTES - used_bytes;

    // If the cache can fill this request, just copy it out
    if (bytes < remaining)
    {
        memcpy(buffer, CachedRandomBytes + used_bytes, bytes);
        used_bytes += bytes;
        return;
    }

    // Copy as much as we can from what remains
    memcpy(buffer, CachedRandomBytes + used_bytes, remaining);
    bytes -= remaining;
    u8 *output = (u8*)buffer + remaining;

    // Copy whole new blocks at a time
    while (bytes >= OUTPUT_CACHE_BYTES)
    {
        OutputHash.Generate(output, OUTPUT_CACHE_BYTES);
        bytes -= OUTPUT_CACHE_BYTES;
        output += OUTPUT_CACHE_BYTES;
    }

    // Generate a new cached block
    OutputHash.Generate(CachedRandomBytes, OUTPUT_CACHE_BYTES);

    // Copy any remaining needed bytes
    memcpy(output, CachedRandomBytes, bytes);
    used_bytes = bytes;
}


//// FortunaFactory

void FortunaFactory::GetNextKey(FortunaOutput *output)
{
	u8 key_material[POOL_BYTES];

	AutoMutex lock(_lock);

		MasterSeed.Generate(key_material, sizeof(key_material));

		output->SeedRevision = MasterSeedRevision;

	lock.Release();

	output->OutputHash.BeginKey(FortunaFactory::POOL_BITS);
	output->OutputHash.BeginPRNG();
	output->OutputHash.Crunch(key_material, sizeof(key_material));
	output->OutputHash.End();
}

bool FortunaFactory::Reseed()
{
    Skein NextSeed;

    // Feed back previous output into next output after the first seeding
    if (reseed_counter == 0)
        NextSeed.BeginKey(POOL_BITS);
    else
        NextSeed.SetKey(&MasterSeed);

    NextSeed.BeginPRNG();

    u8 PoolOutput[POOL_BYTES];

    // Pool 0 is always used for re-seeding
    Pool[0].End();
    Pool[0].Generate(PoolOutput, POOL_BYTES);
    NextSeed.Crunch(PoolOutput, POOL_BYTES);
    Pool[0].BeginKey(POOL_BITS);

    // Pool 1 is used every other time, and so on
    for (int i = 1; i < ENTROPY_POOLS; ++i)
    {
        if (reseed_counter & (1 << (i-1)))
        {
            Pool[i].End();
            Pool[i].Generate(PoolOutput, POOL_BYTES);
            NextSeed.Crunch(PoolOutput, POOL_BYTES);
            Pool[i].BeginKey(POOL_BITS);
        }
    }

    // Initialize the master seed with the new seed
    NextSeed.End();

	AutoMutex lock(_lock);

	MasterSeed.SetKey(&NextSeed);
	MasterSeed.BeginPRNG();

	u32 material_revision = ++MasterSeedRevision;
	u32 material_reseed_count = ++reseed_counter;

	MasterSeed.Crunch(&material_revision, sizeof(material_revision));
	MasterSeed.Crunch(&material_reseed_count, sizeof(material_reseed_count));

	MasterSeed.End();

	// MasterSeed is now ready to generate!

    return true;
}

// Start the entropy generator
bool FortunaFactory::Initialize()
{
	if (_initialized)
		return true;

    MasterSeedRevision = 0;
    reseed_counter = 0;

    // Initialize all the pools
    for (int i = 0; i < ENTROPY_POOLS; ++i)
        Pool[i].BeginKey(POOL_BITS);

    // Initialize the various OS-dependent entropy sources
    if (!InitializeEntropySources())
        return false;

    // Reseed the pools from the entropy sources
    if (!Reseed())
        return false;

	_initialized = true;

    return true;
}

// Stop the entropy generator
void FortunaFactory::Shutdown()
{
	if (_initialized)
	{
		// Block and wait for entropy collection thread to end
		ShutdownEntropySources();

		_initialized = false;
	}
}

// Create a new Fortuna object
FortunaOutput *FortunaFactory::Create()
{
    return new FortunaOutput;
}
