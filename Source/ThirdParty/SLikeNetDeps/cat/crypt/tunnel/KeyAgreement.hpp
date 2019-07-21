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

#ifndef CAT_KEY_AGREEMENT_HPP
#define CAT_KEY_AGREEMENT_HPP

#include <cat/math/BigTwistedEdwards.hpp>
#include <cat/crypt/rand/Fortuna.hpp>

namespace cat {


/*
	Tunnel Key Agreement "Tabby" protocol:
	An unauthenticated Diffie-Hellman key agreement protocol with forward secrecy
	Immune to active attacks (man-in-the-middle) if server key is known ahead of time

    Using Elliptic Curve Cryptography over finite field Fp, p = 2^n - c, c small
	Shape of curve: a' * x^2 + y^2 = 1 + d' * x^2 * y^2, a' = -1 (square in Fp)
	d' (non square in Fp) -> order of curve = q * cofactor h, order of generator point = q
	Curves satisfy MOV conditions and are not anomalous
	Point operations performed with Extended Twisted Edwards group laws
	See BigTwistedEdwards.hpp for more information

	H: Skein-Key, either 256-bit or 512-bit based on security level
	MAC: Skein-MAC, keyed from output of H()

    Here the protocol initiator is the (c)lient, and the responder is the (s)erver:

        s: long-term private key 1 < b < q, long-term public key B = b * G

        256-bit security: B = 64 bytes for public key,  b = 32 bytes for private key
        384-bit security: B = 96 bytes for public key,  b = 48 bytes for private key
        512-bit security: B = 128 bytes for public key, b = 64 bytes for private key

        c: Client already knows the server's public key B before Key Agreement
        c: ephemeral private key 1 < a < q, ephemeral public key A = a * G

    Initiator Challenge: c2s A

        256-bit security: A = 64 bytes
        384-bit security: A = 96 bytes
        512-bit security: A = 128 bytes

        s: validate A, ignore invalid
		Invalid A(x,y) would be the additive identity x=0 or any point not on the curve

        s: ephemeral private key 1 < y < q, ephemeral public key Y = y * G
		Ephemeral key is re-used for several connections before being regenerated

		s: hA = h * A
		s: random n-bit number r
		s: d = H(A,B,Y,r)
		Repeat the previous two steps until d >= 1000

		s: e = b + d*y (mod q)
        s: T = AffineX(e * hA)
        s: k = H(d,T)

    Responder Answer: s2c Y || r || MAC(k) {"responder proof"}

        256-bit security: Y(64by)  r(32by) MAC(32by) = 128 bytes
        384-bit security: Y(96by)  r(48by) MAC(48by) = 192 bytes
        512-bit security: Y(128by) r(64by) MAC(64by) = 256 bytes

        c: validate Y, ignore invalid
		Invalid Y(x,y) would be the additive identity x=0 or any point not on the curve

		c: hY = h * Y
		c: d = H(A,B,Y,r)
		c: Verify d >= 1000
        c: T = AffineX(a * hB + d*a * hY)
        c: k = H(d,T)

        c: validate MAC, ignore invalid

    Initiator Proof: c2s MAC(k) {"initiator proof"}

        This packet can also include the client's first encrypted message

        256-bit security: MAC(32by) = 32 bytes
        384-bit security: MAC(48by) = 48 bytes
        512-bit security: MAC(64by) = 64 bytes

        s: validate MAC, ignore invalid

	Notes:

		The strategy of this protocol is to perform two EC Diffie-Hellman exchanges,
		one with the long-term server key and the second with an ephemeral key that
		should be much harder to obtain by an attacker.  The resulting two shared
		secret points are added together into one point that is used for the key.

		It is perfectly acceptable to re-use an ephemeral key for several runs of
		the protocol.  This means that most of the processing done by the server is
		just one point multiplication.
*/


/*
	Schnorr signatures:

	For signing, the signer reuses its Key Agreement key pair (b,B)

	H: Skein-Key, either 256-bit or 512-bit based on security level

	To sign a message M, signer computes:

		ephemeral secret random 1 < k < q, ephemeral point K = k * G
		e = H(M || K)
		s = k - b*e (mod q)

		This process is repeated until e and s are non-zero

	Signature: s2c e || s

		256-bit security: e(32by) s(32by) = 64 bytes
		384-bit security: e(48by) s(48by) = 96 bytes
		512-bit security: e(64by) s(64by) = 128 bytes

	To verify a signature:

		Check e, s are in the range [1,q-1]

		K' = s*G + e*B
		e' = H(M || K')

		The signature is verified if e == e'

	Notes:

		K ?= K'
		   = s*G + e*B
		   = (k - b*e)*G + e*(b*G)
		   = k*G - b*e*G + e*b*G
		   = K
*/


// If CAT_DETERMINISTIC_KEY_GENERATION is undefined, the time to generate a
// key is unbounded, but tends to be 1 try.  I think this is a good thing
// because it randomizes the runtime and helps avoid timing attacks
//#define CAT_DETERMINISTIC_KEY_GENERATION

// If CAT_USER_ERROR_CHECKING is defined, the key agreement objects will
// check to make sure that the input parameters are all the right length
// and that the math and prng objects are not null
#define CAT_USER_ERROR_CHECKING

class CAT_EXPORT KeyAgreementCommon
{
public:
	static BigTwistedEdwards *InstantiateMath(int bits);

	// Math library register usage
    static const int ECC_REG_OVERHEAD = 21;

    // c: field prime modulus p = 2^bits - C, p = 5 mod 8 s.t. a=-1 is a square in Fp
    // d: curve coefficient (yy-xx=1+Dxxyy), not a square in Fp
    static const int EDWARD_C_256 = 435;
    static const int EDWARD_D_256 = 31720;
    static const int EDWARD_C_384 = 2147;
    static const int EDWARD_D_384 = 13036;
    static const int EDWARD_C_512 = 875;
    static const int EDWARD_D_512 = 32;

    // Limits on field prime
    static const int MAX_BITS = 512;
    static const int MAX_BYTES = MAX_BITS / 8;
    static const int MAX_LEGS = MAX_BYTES / sizeof(Leg);

protected:
    int KeyBits, KeyBytes, KeyLegs;

    bool Initialize(int bits);

public:
	// Generates an unbiased random key in the range 1 < key < q
	void GenerateKey(BigTwistedEdwards *math, IRandom *prng, Leg *key);
};


} // namespace cat

#endif // CAT_KEY_AGREEMENT_HPP
