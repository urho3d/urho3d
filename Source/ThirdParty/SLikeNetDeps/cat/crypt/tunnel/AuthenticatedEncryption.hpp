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

#ifndef CAT_AUTHENTICATED_ENCRYPTION_HPP
#define CAT_AUTHENTICATED_ENCRYPTION_HPP

#include <cat/crypt/symmetric/ChaCha.hpp>
#include <cat/crypt/hash/Skein.hpp>
#include <cat/crypt/hash/HMAC_MD5.hpp>

namespace cat {


/*
    Tunnel Authenticated Encryption "Calico" protocol:

    Run after the Key Agreement protocol completes.
    Uses a 1024-bit anti-replay sliding window, suitable for Internet file transfer over UDP.

	Cipher: 12-round ChaCha with 256-bit or 384-bit keys
	KDF: Key derivation function (Skein)
	MAC: 64-bit truncated HMAC-MD5
	IV: Initialization vector incrementing by 1 each time

    c2sMKey = KDF(k) { "upstream-MAC" }
    s2cMKey = KDF(k) { "downstream-MAC" }
    c2sEKey = KDF(k) { "upstream-ENC" }
    s2cEKey = KDF(k) { "downstream-ENC" }
	c2sIV = KDF(k) { "upstream-IV" }
	s2cIV = KDF(k) { "downstream-IV" }

	To transmit a message, the client calculates a MAC with the c2sMKey of the IV concatenated with
	the plaintext message and then appends the 8-byte MAC and low 3 bytes of the IV to the message,
	which is encrypted using the c2sEKey and the IV.

    c2s Encrypt(c2sEKey) { message || MAC(c2sMKey) { full-iv-us||message } } || Obfuscated { trunc-iv-us }

        encrypted { MESSAGE(X) MAC(8by) } IV(3by) = 11 bytes overhead at end of packet

	To transmit a message, the server calculates a MAC with the s2cMKey of the IV concatenated with
	the plaintext message and then appends the 8-byte MAC and low 3 bytes of the IV to the message,
	which is encrypted using the s2cEKey and the IV.

    s2c Encrypt(s2cEKey) { message || MAC(s2cMKey) { full-iv-ds||message } } || Obfuscated { trunc-iv-ds }

        encrypted { MESSAGE(X) MAC(8by) } IV(3by) = 11 bytes overhead at end of packet

	The full 64-bit IVs are initialized to c2sIV and s2cIV, and the first one sent is IV+1.
*/


class KeyAgreementResponder;
class KeyAgreementInitiator;


// This class is NOT THREAD-SAFE.
class CAT_EXPORT AuthenticatedEncryption
{
    friend class KeyAgreementResponder;
    friend class KeyAgreementInitiator;

    bool _is_initiator, _accept_out_of_order;
    Skein key_hash;

    HMAC_MD5 local_mac_key, remote_mac_key;
    ChaChaKey local_cipher_key, remote_cipher_key;
    u64 local_iv, remote_iv;

    // 1024-bit anti-replay sliding window
    static const int BITMAP_BITS = 1024;
    static const int BITMAP_WORDS = BITMAP_BITS / 64;
    u64 iv_bitmap[BITMAP_WORDS];

public:
	CAT_INLINE AuthenticatedEncryption() {}
	CAT_INLINE ~AuthenticatedEncryption() {}

    // Tunnel overhead bytes
    static const int MAC_BYTES = 8;
    static const int IV_BYTES = 3;
    static const u32 OVERHEAD_BYTES = IV_BYTES + MAC_BYTES;

    // IV constants
    static const int IV_BITS = IV_BYTES * 8;
    static const u32 IV_MSB = (1 << IV_BITS);
    static const u32 IV_MASK = (IV_MSB - 1);
    static const u32 IV_FUZZ = 0xCA7DCA7D;

protected:
    bool SetKey(int KeyBytes, Skein *key, bool is_initiator, const char *key_name);

    bool IsValidIV(u64 iv);
    void AcceptIV(u64 iv);

public:
    // Generate a proof that the local host has the key
    bool GenerateProof(u8 *local_proof, int proof_bytes);

    // Validate a proof that the remote host has the key
    bool ValidateProof(const u8 *remote_proof, int proof_bytes);

public:
	void AllowOutOfOrder(bool allowed = true) { _accept_out_of_order = allowed; }

public:
    // Overhead is OVERHEAD_BYTES bytes at the end of the packet
    // Returns false if the message is invalid.  Invalid messages should just be ignored as if they were never received
    // buf_bytes: Number of bytes in the buffer, including the overhead
	// If Decrypt() returns true, buf_bytes is set to the size of the decrypted message
    bool Decrypt(u8 *buffer, u32 &buf_bytes);

    // Overhead is OVERHEAD_BYTES bytes at the end of the packet
	// buffer_bytes: Number of bytes in the buffer; will return false if buffer size too small
    // msg_bytes: Number of bytes in the message, excluding the overhead
	// If Encrypt() returns true, msg_bytes is set to the size of the encrypted message
    bool Encrypt(u8 *buffer, u32 buffer_bytes, u32 &msg_bytes);
};



} // namespace cat

#endif // CAT_AUTHENTICATED_ENCRYPTION_HPP
