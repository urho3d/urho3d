/*
 *  Copyright (c) 2018, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code is  licensed under the MIT-style license found in the license.txt
 *  file in the root directory of this source tree.
 */
#pragma once

#include "ifileencrypter.h"   // used for Crypto::IFileEncrypter
#include "securestring.h"     // used for Crypto::CSecureString
#include "../RakString.h"     // used for RakString
 #include <openssl/ossl_typ.h> // used for RSA

//struct RSA;

namespace SLNet
{
	namespace Experimental
	{
		namespace Crypto
		{
			class CFileEncrypter : public IFileEncrypter
			{
				// member variables
				RSA* m_privateKey;
				RSA* m_publicKey;

				// constructor
			public:
				// #high - drop the default ctor again (provide load from file instead incl. routing through customized file open handlers)
				CFileEncrypter() = default;
				CFileEncrypter(const CSecureString &privateKey, const char *publicKey, size_t publicKeyLength);
				~CFileEncrypter();
			
				// signing methods
			public:
				const char* SignData(const char *data);
				// #med reconsider/review interface here (char / unsigned char)
				bool VerifyData(const char *data, const size_t dataLength, const unsigned char *signature, const size_t signatureLength);

				// internal helpers
			private:
				const char* SetPublicKey(const char *publicKey, size_t publicKeyLength);
			};
		}
	}
}