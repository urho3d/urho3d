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

#include <cat/math/BigTwistedEdwards.hpp>
using namespace cat;

BigTwistedEdwards::BigTwistedEdwards(int regs, int bits, int modulusC, int paramD, const u8 *Q, const u8 *GenPt)
    : BigPseudoMersenne(regs + TE_OVERHEAD, bits, modulusC)
{
    te_regs = regs + TE_OVERHEAD;
    curve_d = paramD;

    YOFF = library_legs;
    TOFF = library_legs * 2;
    ZOFF = library_legs * 3;
    POINT_STRIDE = library_legs * POINT_REGS;

    A = Get(te_regs - 1);
    B = Get(te_regs - 2);
    C = Get(te_regs - 3);
    D = Get(te_regs - 4);
    E = Get(te_regs - 5);
    F = Get(te_regs - 6);
    G = Get(te_regs - 7);
    H = Get(te_regs - 8);
	CurveQ = Get(te_regs - 9);
    TempPt = Get(te_regs - 13);
    Generator = Get(te_regs - 17);

	Load(GenPt, RegBytes(), Generator);
	Load(GenPt + RegBytes(), RegBytes(), Generator + library_legs);
	PtUnpack(Generator);

	Load(Q, RegBytes(), CurveQ);
}

// Unpack an Extended Projective point (X,Y,T,Z) from affine point (x,y)
void BigTwistedEdwards::PtUnpack(Leg *inout)
{
    MrMultiply(inout+XOFF, inout+YOFF, inout+TOFF);
    CopyX(1, inout+ZOFF);
}

// Set a point to the identity
void BigTwistedEdwards::PtIdentity(Leg *inout)
{
    CopyX(0, inout+XOFF);
    CopyX(1, inout+YOFF);
    CopyX(0, inout+TOFF);
    CopyX(1, inout+ZOFF);
}

void BigTwistedEdwards::PtCopy(const Leg *in, Leg *out)
{
    Copy(in+XOFF, out+XOFF);
    Copy(in+YOFF, out+YOFF);
    Copy(in+TOFF, out+TOFF);
    Copy(in+ZOFF, out+ZOFF);
}

// out(X,Y) = (X,Y) without attempting to convert to affine from projective
void BigTwistedEdwards::SaveProjectiveXY(const Leg *in, void *out_x, void *out_y)
{
    Save(in+XOFF, out_x, RegBytes());
    Save(in+YOFF, out_y, RegBytes());
}

// out(X,Y,Z,T) = (in_x,in_y), returns false if the coordinates are invalid
bool BigTwistedEdwards::LoadVerifyAffineXY(const void *in_x, const void *in_y, Leg *out)
{
    Load(in_x, RegBytes(), out+XOFF);
    Load(in_y, RegBytes(), out+YOFF);

    return PtValidAffine(out);
}

// Strangely enough, including these all in the same source file improves performance
// in Visual Studio by almost 50%, which is odd because MSVC was one of the first
// compilers to support "link time optimization."

#include "edward/io/PtFillRandomX.cpp"
#include "edward/io/PtGenerate.cpp"
#include "edward/io/PtNormalize.cpp"
#include "edward/io/PtSolveAffineY.cpp"
#include "edward/io/PtValidAffine.cpp"
#include "edward/io/SaveAffineX.cpp"
#include "edward/io/SaveAffineXY.cpp"
#include "edward/addsub/PtAdd.cpp"
#include "edward/addsub/PtNegate.cpp"
#include "edward/addsub/PtSubtract.cpp"
#include "edward/addsub/PtDouble.cpp"
#include "edward/addsub/PtDoubleZ1.cpp"
#include "edward/mul/PtMultiplyPrecomp.cpp"
#include "edward/mul/PtPrecompAddSub.cpp"
#include "edward/mul/PtMultiply.cpp"
#include "edward/mul/RefMul.cpp"
