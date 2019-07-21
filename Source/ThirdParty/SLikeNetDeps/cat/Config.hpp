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

#ifndef CAT_CONFIG_HPP
#define CAT_CONFIG_HPP

namespace cat {


// This definition overrides CAT_BUILD_DLL below.  Neuters CAT_EXPORT macro so symbols are
// neither exported or imported.
//#define CAT_NEUTER_EXPORT

// This definition changes the meaning of the CAT_EXPORT macro on Windows.  When defined,
// the CAT_EXPORT macro will export the associated symbol.  When undefined, it will import it.
//#define CAT_BUILD_DLL

// If you want to remove server-side code from a binary distribution of a client program:
//#define CAT_OMIT_SERVER_CODE

// If you know the endianness of your target, uncomment one of these for better performance.
//#define __LITTLE_ENDIAN__
//#define __BIG_ENDIAN__

// If you want to use faster 384-bit or 512-bit math, define this:
//#define CAT_UNROLL_OVER_256_BITS

// Adjust if your architecture uses larger than 128-byte cache line
#define CAT_DEFAULT_CACHE_LINE_SIZE 128


} // namespace cat

#endif // CAT_CONFIG_HPP
