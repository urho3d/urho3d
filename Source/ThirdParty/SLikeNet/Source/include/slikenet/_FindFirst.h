/*
 * This file was taken from RakNet 4.082.
 * Please see licenses/RakNet license.txt for the underlying license and related copyright.
 *
 * Modified work: Copyright (c) 2017, SLikeSoft UG (haftungsbeschränkt)
 *
 * This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 * license found in the license.txt file in the root directory of this source tree.
 */

///
/// Original file by the_viking, fixed by Rômulo Fernandes
/// Should emulate windows finddata structure
///

#ifndef GCC_FINDFIRST_H
#define GCC_FINDFIRST_H

#if (defined(__GNUC__) || defined(__ARMCC_VERSION) || defined(__GCCXML__) || defined(__S3E__) ) && !defined(__WIN32)

#include <dirent.h>

#include "string.h"

#define _A_NORMAL 		0x00 		// Normal file
#define _A_RDONLY 		0x01 		// Read-only file
#define _A_HIDDEN 		0x02 		// Hidden file
#define _A_SYSTEM 		0x04 		// System file
#define _A_VOLID 			0x08 		// Volume ID
#define _A_SUBDIR 		0x10 		// Subdirectory
#define _A_ARCH 			0x20 		// File changed since last archive
#define FA_NORMAL 		0x00 		// Synonym of _A_NORMAL
#define FA_RDONLY 		0x01 		// Synonym of _A_RDONLY
#define FA_HIDDEN 		0x02 		// Synonym of _A_HIDDEN
#define FA_SYSTEM 		0x04 		// Synonym of _A_SYSTEM
#define FA_LABEL 			0x08 		// Synonym of _A_VOLID
#define FA_DIREC 			0x10 		// Synonym of _A_SUBDIR
#define FA_ARCH 			0x20 		// Synonym of _A_ARCH


const unsigned STRING_BUFFER_SIZE = 512;

typedef struct _finddata_t
{
	char            name[STRING_BUFFER_SIZE];
	int            attrib;
	unsigned long   size;
} _finddata;

/** 
 *  Hold information about the current search
 */
typedef struct _findinfo_t
{
	DIR*	openedDir;
	SLNet::RakString filter;    
	SLNet::RakString dirName;
} _findinfo;

long _findfirst(const char *name, _finddata_t *f);
int _findnext(long h, _finddata_t *f);
int _findclose(long h);

#endif
#endif

