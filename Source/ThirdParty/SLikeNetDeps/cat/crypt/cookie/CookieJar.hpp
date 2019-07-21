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

#ifndef CAT_COOKIE_JAR_HPP
#define CAT_COOKIE_JAR_HPP

#include <cat/crypt/rand/Fortuna.hpp>

namespace cat {


class CookieJar
{
    static const int EXPIRE_TIME = 4000; // ms
    static const int BIN_COUNT = 16; // power of 2
    static const int BIN_TIME = EXPIRE_TIME / BIN_COUNT;
    static const int BIN_MASK = BIN_COUNT - 1;

    u32 key[16];

    u32 Salsa6(u32 *x);

    u32 Hash(u32 ip, u16 port, u32 epoch);
    u32 Hash(const void *address_info, int bytes, u32 epoch);

    u32 GetEpoch();
    u32 ReconstructEpoch(u32 cookie);

public:
    // Initialize to a random 512-bit key on startup
    void Initialize(FortunaOutput *csprng);

    // Thread-safe and lock-free
    u32 Generate(u32 ip, u16 port);
    u32 Generate(const void *address_info, int bytes); // bytes <= 48

    // Thread-safe and lock-free
    bool Verify(u32 ip, u16 port, u32 cookie);
    bool Verify(const void *address_info, int bytes, u32 cookie); // bytes <= 48
};


} // namespace cat

#endif // CAT_COOKIE_JAR_HPP
