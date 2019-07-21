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

#include <cat/crypt/cookie/CookieJar.hpp>
#include <cat/time/Clock.hpp>
#include <cat/math/BitMath.hpp>
using namespace cat;

// Initialize to a random 512-bit key on startup
void CookieJar::Initialize(FortunaOutput *csprng)
{
    csprng->Generate(key, sizeof(key));
}

u32 CookieJar::Salsa6(u32 *x)
{
    // 6 rounds of Salsa20
    for (int ii = 6; ii > 0; ii -= 2)
    {
        x[4] ^= CAT_ROL32(x[0] + x[12], 7);
        x[8] ^= CAT_ROL32(x[4] + x[0], 9);
        x[12] ^= CAT_ROL32(x[8] + x[4], 13);
        x[0] ^= CAT_ROL32(x[12] + x[8], 18);
        x[9] ^= CAT_ROL32(x[5] + x[1], 7);
        x[13] ^= CAT_ROL32(x[9] + x[5], 9);
        x[1] ^= CAT_ROL32(x[13] + x[9], 13);
        x[5] ^= CAT_ROL32(x[1] + x[13], 18);
        x[14] ^= CAT_ROL32(x[10] + x[6], 7);
        x[2] ^= CAT_ROL32(x[14] + x[10], 9);
        x[6] ^= CAT_ROL32(x[2] + x[14], 13);
        x[10] ^= CAT_ROL32(x[6] + x[2], 18);
        x[3] ^= CAT_ROL32(x[15] + x[11], 7);
        x[7] ^= CAT_ROL32(x[3] + x[15], 9);
        x[11] ^= CAT_ROL32(x[7] + x[3], 13);
        x[15] ^= CAT_ROL32(x[11] + x[7], 18);
        x[1] ^= CAT_ROL32(x[0] + x[3], 7);
        x[2] ^= CAT_ROL32(x[1] + x[0], 9);
        x[3] ^= CAT_ROL32(x[2] + x[1], 13);
        x[0] ^= CAT_ROL32(x[3] + x[2], 18);
        x[6] ^= CAT_ROL32(x[5] + x[4], 7);
        x[7] ^= CAT_ROL32(x[6] + x[5], 9);
        x[4] ^= CAT_ROL32(x[7] + x[6], 13);
        x[5] ^= CAT_ROL32(x[4] + x[7], 18);
        x[11] ^= CAT_ROL32(x[10] + x[9], 7);
        x[8] ^= CAT_ROL32(x[11] + x[10], 9);
        x[9] ^= CAT_ROL32(x[8] + x[11], 13);
        x[10] ^= CAT_ROL32(x[9] + x[8], 18);
        x[12] ^= CAT_ROL32(x[15] + x[14], 7);
        x[13] ^= CAT_ROL32(x[12] + x[15], 9);
        x[14] ^= CAT_ROL32(x[13] + x[12], 13);
        x[15] ^= CAT_ROL32(x[14] + x[13], 18);
    }

    return x[0] ^ x[5] ^ x[10] ^ x[15];
}

u32 CookieJar::Hash(u32 ip, u16 port, u32 epoch)
{
    u32 x[16];

    memcpy(x, key, sizeof(x));

    x[4] += ip;
    x[6] += epoch;
    x[8] += port;
    x[10] += epoch;

    return Salsa6(x);
}

u32 CookieJar::Hash(const void *address_info, int bytes, u32 epoch)
{
    u32 x[16];

    memcpy(x, key, sizeof(x));

    // Add address info to the key one word at a time
    const u32 *info32 = (const u32 *)address_info;
    u32 *y = &x[4];
    while (bytes >= 4)
    {
        *y++ += *info32++;
        bytes -= 4;
    }

    // Add final 1..3 address info bytes to the key
    const u8 *info8 = (const u8 *)info32;
    switch (bytes)
    {
    case 3: *y += ((u32)info8[2] << 16) | *(const u16*)info8; break;
    case 2: *y += *(const u16*)info8; break;
    case 1: *y += info8[0]; break;
    }

    x[6] += epoch;
    x[10] += epoch;

    return Salsa6(x);
}

u32 CookieJar::GetEpoch()
{
    return Clock::msec_fast() / BIN_TIME;
}

u32 CookieJar::ReconstructEpoch(u32 cookie)
{
    u32 epoch = GetEpoch();

    u32 cookie_bin = cookie & BIN_MASK;

    // Attempt to reconstruct the epoch used to generate this cookie
    u32 cookie_epoch = (epoch & ~BIN_MASK) | cookie_bin;

    // If the cookie's bin is ahead of the bin in this interval, then
    // this cookie must be from the previous interval to be valid.
    if (cookie_bin > (epoch & BIN_MASK)) cookie_epoch -= BIN_COUNT;

    return cookie_epoch;
}

u32 CookieJar::Generate(u32 ip, u16 port)
{
    u32 epoch = GetEpoch();

    return (Hash(ip, port, epoch) << 4) | (epoch & BIN_MASK);
}

bool CookieJar::Verify(u32 ip, u16 port, u32 cookie)
{
    return (Hash(ip, port, ReconstructEpoch(cookie)) << 4) == (cookie & ~BIN_MASK);
}

u32 CookieJar::Generate(const void *address_info, int bytes)
{
    u32 epoch = GetEpoch();

    return (Hash(address_info, bytes, epoch) << 4) | (epoch & BIN_MASK);
}

bool CookieJar::Verify(const void *address_info, int bytes, u32 cookie)
{
    return (Hash(address_info, bytes, ReconstructEpoch(cookie)) << 4) == (cookie & ~BIN_MASK);
}
