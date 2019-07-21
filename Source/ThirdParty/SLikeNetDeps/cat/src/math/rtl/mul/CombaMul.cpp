/*
	Copyright (c) 2009 Christopher A. Taylor.  All rights reserved.

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

#include <cat/math/Legs.hpp>
using namespace cat;

// Comba Multiplication in template meta-programming

template<int Index> class CombaT {};


//// Inner loop

template<int I, int J, int Count> CAT_INLINE void Comba2(const Leg *a, const Leg *b, Leg &c0, Leg &c1, Leg &c2, CombaT<I>, CombaT<J>, CombaT<Count>)
{
	CAT_LEG_COMBA3(a[I], b[J], c0, c1, c2);
	Comba2(a, b, c0, c1, c2, CombaT<I-1>(), CombaT<J+1>(), CombaT<Count-1>());
}

template<int I, int J> CAT_INLINE void Comba2(const Leg * /*a*/, const Leg * /*b*/, Leg &/*c0*/, Leg &/*c1*/, Leg &/*c2*/, CombaT<I>, CombaT<J>, CombaT<-1>)
{
}


//// Outer loop: Second Half

template<int L, int Count> CAT_INLINE void Comba3(const Leg *a, const Leg *b, Leg *out, Leg &c0, Leg &c1, Leg &c2, CombaT<L>, CombaT<Count>)
{
	CAT_LEG_COMBA2(a[L-1], b[L-1 - Count], c0, c1, c2);
	Comba2(a, b, c0, c1, c2, CombaT<L-2>(), CombaT<L - Count>(), CombaT<Count-1>());
	out[2*L - Count - 2] = c0;
	Comba3(a, b, out, c1, c2, c0, CombaT<L>(), CombaT<Count-1>());
}

template<int L> CAT_INLINE void Comba3(const Leg * /*a*/, const Leg * /*b*/, Leg *out, Leg &c0, Leg &/*c1*/, Leg &/*c2*/, CombaT<L>, CombaT<-1>)
{
	out[2*L - 1] = c0;
}


//// Outer loop: First Half

template<int L, int Count> CAT_INLINE void Comba1(const Leg *a, const Leg *b, Leg *out, Leg &c0, Leg &c1, Leg &c2, CombaT<L>, CombaT<Count>)
{
	CAT_LEG_COMBA2(a[Count], b[0], c0, c1, c2);
	Comba2(a, b, c0, c1, c2, CombaT<Count-1>(), CombaT<1>(), CombaT<Count-1>());
	out[Count] = c0;
	Comba1(a, b, out, c1, c2, c0, CombaT<L>(), CombaT<Count+1>());
}

template<int L> CAT_INLINE void Comba1(const Leg *a, const Leg *b, Leg *out, Leg &c0, Leg &c1, Leg &c2, CombaT<L>, CombaT<L>)
{
	Comba3(a, b, out, c0, c1, c2, CombaT<L>(), CombaT<L-2>());
}


//// Entrypoint

template<int L> void CombaMul(const Leg *a, const Leg *b, Leg *out)
{
	Leg c0, c1 = 0, c2;
	CAT_LEG_MUL(a[0], b[0], c0, out[0]);
	Comba1(a, b, out, c0, c1, c2, CombaT<L>(), CombaT<1>());
}
