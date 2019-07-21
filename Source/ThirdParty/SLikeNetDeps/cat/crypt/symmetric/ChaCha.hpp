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

/*
    The ChaCha cipher is a symmetric stream cipher based on Salsa20.
    http://cr.yp.to/chacha.html
*/

#ifndef CAT_CHACHA_HPP
#define CAT_CHACHA_HPP

#include <cat/Platform.hpp>

namespace cat {

/*
    To initialize the ChaCha cipher, you must specify a 256-bit key.

    Code example:

        ChaChaKey cck;
        char key[32]; // fill key here

        cck.Key(key, sizeof(key));

    Before each encryption or decryption with the ChaCha cipher,
    a 64-bit Initialization Vector (IV) must be specified.  Every
    time a message is encrypted, the IV must be incremented by 1.
    The IV is then sent along with the encrypted message.

    Encryption code example:

        char message[19], ciphertext[19]; // message filled here
        u64 iv = 125125;
        u64 message_iv = iv;
        iv = iv + 1;

		ChaChaOutput cco(cck, message_iv);
        cco.Crypt(message, ciphertext, sizeof(ciphertext));

    Decryption code example:

        char ciphertext[19], decrypted[19]; // ciphertext filled here

		ChaChaOutput cco(cck, message_iv);
        cco.Crypt(ciphertext, decrypted, sizeof(decrypted));

    Sending all 8 bytes of the IV in every packet is not necessary.
    Instead, only a few of the low bits of the IV need to be sent,
    if the IV is incremented by 1 each time.

    How many?  It depends on how many messages can get lost.
    If < 32768 messages can get lost in a row, then CAT_IV_BITS = 16 (default)

    I have provided a function to handle rollover/rollunder of the IV,
    which also works if the same IV is sent twice for some reason.
    It needs to know how many of the low bits are sent across, so be sure
    to change CAT_IV_BITS in this header if you send more or less than 16.

    Code example:

        u64 last_accepted_iv;
        u32 new_iv_low_bits;

        u64 new_iv = ChaCha::ReconstructIV(last_accepted_iv, new_iv_low_bits);

    -------------------------READ THIS BEFORE USING--------------------------

    Never use the same IV twice.
        Otherwise: An attacker can recover the plaintext without the key.

    Never use the same key twice.
        Otherwise: An attacker can recover the plaintext without the key.

    If you have two hosts talking to eachother securely with ChaCha encryption,
    then be sure that each host is encrypting with a DIFFERENT key.
        Otherwise: An attacker can recover the plaintext without the key.

    Remember that an attacker can impersonate the remote computer, so be
    sure not to accept the new IV until the message authentication code has
	been verified if your protocol uses a message authentication code (MAC).
        Otherwise: An attacker could desynchronize the IVs.
*/


//// ChaChaKey

class CAT_EXPORT ChaChaKey
{
	friend class ChaChaOutput;
	u32 state[16];

public:
    ~ChaChaKey();

    // Key up to 384 bits
    void Set(const void *key, int bytes);
};


//// ChaChaOutput

class CAT_EXPORT ChaChaOutput
{
	u32 state[16];

	void GenerateKeyStream(u32 *out);

public:
	ChaChaOutput(const ChaChaKey &key, u64 iv);
	~ChaChaOutput();

	// Message with any number of bytes
	void Crypt(const void *in, void *out, int bytes);
};


} // namespace cat

#endif // CAT_CHACHA_HPP
