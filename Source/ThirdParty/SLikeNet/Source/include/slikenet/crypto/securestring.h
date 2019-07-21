/*
*  Copyright (c) 2018, SLikeSoft UG (haftungsbeschränkt)
*
*  This source code is  licensed under the MIT-style license found in the license.txt
*  file in the root directory of this source tree.
*/

#pragma once

namespace SLNet
{
	namespace Experimental
	{
		namespace Crypto
		{
			// #med - consider CSecureMemoryBuffer and derive CSecureString from that class
			//        difference would be implicit null-terminated buffer in string buffer (upon Decrypt calls)
			// document: document Decrypt/FlushUnencryptedData() requirements for most secure handling
			//           i.e. emphasize that FlushUnencryptedData() must be called after having called Decrypt() ASAP once access to the unencrypted data
			//           data is no longer required
			class CSecureString
			{
				// member variables
			private:
				bool m_UTF8Mode;
				bool m_wasFlushed;
				size_t m_EncryptedBufferSize;
				size_t m_numBufferUsed;
				size_t m_UnencryptedBufferSize;
				char* m_EncryptedMemory;
				char* m_UnencryptedBuffer;

				// constructor / destructor
			public:
				CSecureString(const size_t maxBufferSize, const bool utf8Mode = false);
				~CSecureString();

				// container methods
			public:
				bool AddChar(char* character);
				bool RemoveLastChar();
				void Reset();

				// decryption methods
			public:
				const char* Decrypt();
				void FlushUnencryptedData();
			};
		}
	}
}