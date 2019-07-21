/*
 *  Copyright (c) 2018, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code is  licensed under the MIT-style license found in the license.txt
 *  file in the root directory of this source tree.
 */
#include "slikenet/crypto/factory.h"

// includes for concrete classes
#include "slikenet/crypto/fileencrypter.h" // used for CFileEncrypter

namespace SLNet
{
	namespace Experimental
	{
		namespace Crypto
		{
			// #high - change interface --- use RakString?
			IFileEncrypter* Factory::ConstructFileEncrypter(const CSecureString& privateKey, const char *publicKey, size_t publicKeyLength)
			{
				return new CFileEncrypter(privateKey, publicKey, publicKeyLength);
			}
		}
	}
}