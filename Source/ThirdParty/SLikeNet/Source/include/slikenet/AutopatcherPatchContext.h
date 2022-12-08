/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 */

#ifndef __AUTOPATCHER_PATCH_CONTEXT_H
#define __AUTOPATCHER_PATCH_CONTEXT_H

enum PatchContext
{
	PC_HASH_1_WITH_PATCH,
	PC_HASH_2_WITH_PATCH,
	PC_WRITE_FILE,
	PC_ERROR_FILE_WRITE_FAILURE,
	PC_ERROR_PATCH_TARGET_MISSING,
	PC_ERROR_PATCH_APPLICATION_FAILURE,
	PC_ERROR_PATCH_RESULT_CHECKSUM_FAILURE,
	PC_NOTICE_WILL_COPY_ON_RESTART,
	PC_NOTICE_FILE_DOWNLOADED,
	PC_NOTICE_FILE_DOWNLOADED_PATCH,
};

#endif
