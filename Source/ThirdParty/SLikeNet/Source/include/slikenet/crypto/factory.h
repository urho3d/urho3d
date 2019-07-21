/*
 *  Copyright (c) 2018, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code is  licensed under the MIT-style license found in the license.txt
 *  file in the root directory of this source tree.
 */
#pragma once

#include "securestring.h"   // used for SLNet::Crypto::CSecureString
#include "ifileencrypter.h" // used for SLNet::Crypto::IFileEncrypter

namespace SLNet
{
	namespace Experimental
	{
		namespace Crypto
		{
			class Factory
			{
			public:
				static IFileEncrypter* ConstructFileEncrypter(const CSecureString& privateKey, const char *publicKey, size_t publicKeyLength);
			};
		}
	}
}