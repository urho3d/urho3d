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
			class IFileEncrypter
			{
				// constructor / destructor
			protected:
				IFileEncrypter() = default;
			public:
				virtual ~IFileEncrypter() = default;

				// signing methods
			public:
				virtual const char* SignData(const char* data) = 0;
				virtual bool VerifyData(const char *data, const size_t dataLength, const unsigned char *signature, const size_t signatureLength) = 0;
			};
		}
	}
}