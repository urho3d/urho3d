/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#include "slikenet/IncrementalReadInterface.h"
#include <stdio.h>
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

using namespace SLNet;

unsigned int IncrementalReadInterface::GetFilePart( const char *filename, unsigned int startReadBytes, unsigned int numBytesToRead, void *preallocatedDestination, FileListNodeContext context)
{
	FILE *fp;
	if (fopen_s(&fp, filename, "rb")!=0)
		return 0;
	fseek(fp,startReadBytes,SEEK_SET);
	unsigned int numRead = (unsigned int) fread(preallocatedDestination,1,numBytesToRead, fp);
	fclose(fp);
	return numRead;
}
