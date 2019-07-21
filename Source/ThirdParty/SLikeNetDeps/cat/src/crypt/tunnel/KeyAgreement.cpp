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

#include <cat/crypt/tunnel/KeyAgreement.hpp>
using namespace cat;

bool KeyAgreementCommon::Initialize(int bits)
{
    // Restrict the bits to pre-defined security levels
    switch (bits)
    {
    case 256:
    case 384:
    case 512:
        KeyBits = bits;
        KeyBytes = KeyBits / 8;
        KeyLegs = KeyBytes / sizeof(Leg);
        return true;
    }

    return false;
}

static u8 Q_256[32] = {
	245,131,113,179,240,8,8,95,168,93,210,180,187,107,50,108,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64
};

static u8 GeneratorPoint_256[64] = {
	199,172,100,86,21,9,105,52,27,54,112,27,130,66,212,206,2,201,
	233,157,146,53,115,139,157,11,140,127,85,208,200,234,89,166,
	146,6,210,52,127,185,80,155,102,54,140,112,165,133,28,79,155,
	87,57,23,8,77,36,126,56,208,44,204,44,122
};

static u8 Q_384[48] = {
	167,49,135,1,253,184,43,116,11,231,6,199,63,186,43,6,212,2,
	195,225,178,24,119,115,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,64
};

static u8 GeneratorPoint_384[96] = {
	194,86,91,5,46,236,168,80,129,111,223,121,77,185,26,167,98,57,
	177,25,134,193,90,222,174,244,78,5,90,166,102,139,157,79,136,
	152,90,103,195,102,213,108,231,170,27,180,46,139,122,198,200,
	43,174,187,240,150,104,198,109,121,27,97,12,24,247,39,173,231,
	37,229,140,166,121,97,65,16,195,24,98,137,210,165,181,166,216,
	60,210,21,169,22,2,184,123,239,159,170
};

static u8 Q_512[64] = {
	7,136,153,241,166,33,123,142,62,77,254,231,156,219,24,171,220,
	146,88,148,11,12,153,176,182,120,137,227,1,235,197,30,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64
};

static u8 GeneratorPoint_512[128] = {
	34,181,62,219,167,17,152,185,106,113,24,141,78,124,179,108,16,
	48,126,37,104,196,116,5,113,214,124,250,203,234,112,49,212,165,
	39,68,243,53,190,108,48,157,70,80,175,7,192,46,248,115,204,239,
	167,212,174,129,140,89,190,85,8,34,104,88,250,79,0,135,145,37,
	62,237,70,162,67,180,82,32,36,152,68,69,190,222,107,234,15,25,
	163,135,191,127,173,153,143,102,64,84,233,112,34,9,153,176,215,
	157,50,59,31,184,235,134,116,241,238,177,3,109,59,251,125,45,
	228,99,172,83,95,26
};

BigTwistedEdwards *KeyAgreementCommon::InstantiateMath(int bits)
{
	switch (bits)
    {
    case 256: return new BigTwistedEdwards(ECC_REG_OVERHEAD, 256, EDWARD_C_256, EDWARD_D_256, Q_256, GeneratorPoint_256);
    case 384: return new BigTwistedEdwards(ECC_REG_OVERHEAD, 384, EDWARD_C_384, EDWARD_D_384, Q_384, GeneratorPoint_384);
    case 512: return new BigTwistedEdwards(ECC_REG_OVERHEAD, 512, EDWARD_C_512, EDWARD_D_512, Q_512, GeneratorPoint_512);
	default: return 0;
    }
}

// Generates an unbiased random key in the range 1 < key < q
void KeyAgreementCommon::GenerateKey(BigTwistedEdwards *math, IRandom *prng, Leg *key)
{
	do
	{
		prng->Generate(key, KeyBytes);

		// Turn off the high bit(s) to speed up unbiased key generation
		// NOTE: Only works for the values of q above
#if defined(CAT_DETERMINISTIC_KEY_GENERATION)
		key[KeyLegs-1] &= ~(CAT_LEG_MSB | (CAT_LEG_MSB >> 1));
#else
		key[KeyLegs-1] &= ~CAT_LEG_MSB;
#endif
	}
	while (!math->Less(key, math->GetCurveQ()) ||
		   !math->GreaterX(key, 1));
}
