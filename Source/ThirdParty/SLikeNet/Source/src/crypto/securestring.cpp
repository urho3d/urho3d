/*
 *  Copyright (c) 2018, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code is  licensed under the MIT-style license found in the license.txt
 *  file in the root directory of this source tree.
 */
#include "slikenet/crypto/securestring.h"

// #med - review the include order - defines.h defines SLNET_VERIFY but doesn't enforce including assert.h which it honestly should
#include "slikenet/assert.h"			// used for assert() (via SLNET_VERIFY)
#include "slikenet/memoryoverride.h"	// used for OP_NEW_ARRAY
#include "slikenet/WindowsIncludes.h"	// used for CryptProtectMemory, CryptUnprotectMemory, CRYPTPROTECTMEMORY_BLOCK_SIZE

#include <limits>	// used for std::numeric_limits

namespace SLNet
{
	namespace Experimental
	{
		namespace Crypto
		{
			// #high - review UTF-8 mode handling --- quick and dirty addition atm - should use distinct UTF8 char-class?
			CSecureString::CSecureString(const size_t maxBufferSize, const bool utf8Mode) :
				m_UTF8Mode(utf8Mode),
				m_wasFlushed(false),
				m_numBufferUsed(0),
				m_UnencryptedBufferSize(maxBufferSize + 1) // +1 for trailing '\0'-char
			{
				// #high - add Linux/OSX handling
				// allocate and encrypt buffer
				size_t padding = maxBufferSize % CRYPTPROTECTMEMORY_BLOCK_SIZE;
				m_EncryptedBufferSize = maxBufferSize - padding + (padding > 0 ? CRYPTPROTECTMEMORY_BLOCK_SIZE : 0);
				if (m_EncryptedBufferSize > std::numeric_limits<DWORD>::max()) {
					// #high - exception/error logging
					m_EncryptedBufferSize = std::numeric_limits<DWORD>::max();
					padding = m_EncryptedBufferSize % CRYPTPROTECTMEMORY_BLOCK_SIZE;
					if (padding > 0) {
						m_EncryptedBufferSize -= CRYPTPROTECTMEMORY_BLOCK_SIZE + padding;
					}
					if (m_UnencryptedBufferSize > m_EncryptedBufferSize) {
						m_UnencryptedBufferSize = m_EncryptedBufferSize + 1; // +1 for trailing '\0' char
					}
				}
				// #high - add proper handling for char sizes ~= 1 byte!
				// #high - root through memory manager (aka: OP_NEW_ARRAY)
				// #high - raise exception upon failure to allocate
				m_EncryptedMemory = static_cast<char*>(LocalAlloc(LPTR, m_EncryptedBufferSize));
				// #high - change OP_NEW_ARRAY() count parameter to size_t
				m_UnencryptedBuffer = OP_NEW_ARRAY<char>(static_cast<int>(m_UnencryptedBufferSize), _FILE_AND_LINE_);

				// note: we must flush the data, so it's properly zeroed (for trailing null-terminator behavior in Decrypt() which otherwise would be broken)
				FlushUnencryptedData();
			}

			CSecureString::~CSecureString()
			{
				// calling reset so to ensure that the data is flushed and no trace to the data is left behind and also the encrypted memory got removed
				// (to not leave it behind after the lifetime of the buffer ended)
				Reset();

				LocalFree(m_EncryptedMemory);
				m_EncryptedMemory = nullptr;

				OP_DELETE_ARRAY(m_UnencryptedBuffer, _FILE_AND_LINE_);
				m_UnencryptedBuffer = nullptr;
			}

			bool CSecureString::AddChar(char* character)
			{
				if (character == nullptr) {
					// #high - add error output
					return false;
				}

				size_t charSize = 1;
				if (m_UTF8Mode) {
					// calculate char size
					if (static_cast<unsigned char>(character[0]) > 0xF0) {
						charSize = 4;
					}
					else if(static_cast<unsigned char>(character[0]) > 0xE0) {
						charSize = 3;
					}
					else if (static_cast<unsigned char>(character[0]) > 0xC0) {
						charSize = 2;
					}
					else if (static_cast<unsigned char>(character[0]) > 0x80) {
						// invalid encoding
						// #high - add error output
						// note: not nulling, since obviously the input data is wrong (not a UTF8-char)
						return false;
					}
					// else single byte char

					// validate the 10-prefixes for bytes 2ff.
					for (int i = 1; i < charSize; ++i) {
						if (static_cast<unsigned char>(character[i]) < 0x80) {
							// #high - add error output
							// note: not nulling, since obviously the input data is wrong (not a UTF8-char)
							return false;
						}
					}
				}

				if (m_numBufferUsed + charSize > m_UnencryptedBufferSize) {
					// out of memory / ensure source data was cleared regardless
					// #high - add error output
					// #high - Linux/OSX handling
					SecureZeroMemory(character, charSize);
					return false;
				}

				// decrypt, add, and re-encrypt the data
				// note: do not decrypting the memory if it wasn't encrypted yet
				if (m_numBufferUsed > 0) {
					// note: static cast to DWORD is fine here - m_EncryptedBufferSize ensured not to exceed DWORD::max()
					SLNET_VERIFY(CryptUnprotectMemory(m_EncryptedMemory, static_cast<DWORD>(m_EncryptedBufferSize), CRYPTPROTECTMEMORY_SAME_PROCESS));
				}
				// #high - add error handling
				memcpy_s(m_EncryptedMemory + m_numBufferUsed, m_EncryptedBufferSize - m_numBufferUsed, character, charSize);
				m_numBufferUsed += charSize;
				// #high - add error handling
				// note: static cast to DWORD is fine here - m_EncryptedBufferSize ensured not to exceed DWORD::max()
				SLNET_VERIFY(CryptProtectMemory(m_EncryptedMemory, static_cast<DWORD>(m_EncryptedBufferSize), CRYPTPROTECTMEMORY_SAME_PROCESS));

				// clear the source data
				SecureZeroMemory(character, charSize);
				return true;
			}

			bool CSecureString::RemoveLastChar()
			{
				if (m_numBufferUsed == 0) {
					return false; // empty buffer - nothing to remove
				}

				size_t numCharsToRemove = 0;
				if (m_UTF8Mode) {
					// note: static cast to DWORD is fine here - m_EncryptedBufferSize ensured not to exceed DWORD::max()
					SLNET_VERIFY(CryptUnprotectMemory(m_EncryptedMemory, static_cast<DWORD>(m_EncryptedBufferSize), CRYPTPROTECTMEMORY_SAME_PROCESS));

					// iterate backwards over the UTF-8 encoded chars, to find the starting char (which will have a different encoding than 10xxxxxx)
					while ((static_cast<unsigned char>(m_EncryptedMemory[m_numBufferUsed - numCharsToRemove]) & 0xC0) == 0x80) {
						++numCharsToRemove;
						RakAssert(m_numBufferUsed >= numCharsToRemove);
					}

					// note: static cast to DWORD is fine here - m_EncryptedBufferSize ensured not to exceed DWORD::max()
					SLNET_VERIFY(CryptProtectMemory(m_EncryptedMemory, static_cast<DWORD>(m_EncryptedBufferSize), CRYPTPROTECTMEMORY_SAME_PROCESS));
				}
				++numCharsToRemove;
				RakAssert(numCharsToRemove <= 4);
				RakAssert(m_numBufferUsed >= numCharsToRemove);

				// note: no need to remove the character from the encrypted string - just act as if it was removed and clear the data the next time we decrypt the data
				m_numBufferUsed -= numCharsToRemove;
				// #high - add this handling
				//m_numCharsToClear += numCharsToClear;
				return true;
			}

			void CSecureString::Reset()
			{
				// resetting the memory buffer also explicitly resets any not-yet flushed unencrypted buffer
				FlushUnencryptedData();

				SecureZeroMemory(m_EncryptedMemory, m_EncryptedBufferSize);

				m_numBufferUsed = 0;
			}

			const char* CSecureString::Decrypt()
			{
				// #high - add mutex to prevent threading issues

				if (m_numBufferUsed == 0) {
					return ""; // no encrypted data (prevent decrypting non-encrypted data - i.e. if never any data was added)
				}

				// flushing the data here to safeguard against the user having forgotten to flush existing unencrypted data of some old encrypted data
				// (which then would remain in memory if the new data's length is smaller than the old ones)
				// note: since we flush the data, we don't need to write a trailing null-terminator lateron (i.e. entire memory is zeroed here)
				// #med - consider adding the trailing null-terminator to the encrypted memory already (and then drop the note above and -1 below in memcpy_s())
				FlushUnencryptedData();

				// #high - add error handling
				// note: static cast to DWORD is fine here - m_EncryptedBufferSize ensured not to exceed DWORD::max()
				SLNET_VERIFY(CryptUnprotectMemory(m_EncryptedMemory, static_cast<DWORD>(m_EncryptedBufferSize), CRYPTPROTECTMEMORY_SAME_PROCESS));
				// #high - add error handling
				// -1 due to reserved space for trailing null-terminated
				memcpy_s(m_UnencryptedBuffer, m_UnencryptedBufferSize - 1, m_EncryptedMemory, m_numBufferUsed);
				// #high - add error handling
				SLNET_VERIFY(CryptProtectMemory(m_EncryptedMemory, static_cast<DWORD>(m_EncryptedBufferSize), CRYPTPROTECTMEMORY_SAME_PROCESS));

				m_wasFlushed = false;
				return m_UnencryptedBuffer;
			}

			void CSecureString::FlushUnencryptedData()
			{
				if (!m_wasFlushed) {
					SecureZeroMemory(m_UnencryptedBuffer, m_UnencryptedBufferSize);
					m_wasFlushed = true;
				}
			}
		}
	}
}