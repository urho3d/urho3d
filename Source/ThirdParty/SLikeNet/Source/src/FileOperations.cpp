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

#include "slikenet/FileOperations.h"
#if _RAKNET_SUPPORT_FileOperations==1
#include "slikenet/memoryoverride.h"
#include "slikenet/_FindFirst.h" // For linux
#include <stdio.h>
#include <string.h>
#ifdef _WIN32 
// For mkdir
#include <direct.h>
#include <io.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#include "slikenet/_FindFirst.h"
#endif
#include "errno.h"
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

bool WriteFileWithDirectories( const char *path, char *data, unsigned dataLength )
{
	int index;
	FILE *fp;
	char pathCopy[MAX_PATH];
	int res;

	if ( path == 0 || path[ 0 ] == 0 )
		return false;

	strcpy_s( pathCopy, path );

	// Ignore first / if there is one
	if (pathCopy[0])
	{
		index = 1;
		while ( pathCopy[ index ] )
		{
			if ( pathCopy[ index ] == '/' || pathCopy[ index ] == '\\')
			{
				pathCopy[ index ] = 0;
	
	#ifdef _WIN32
				res = _mkdir( pathCopy );
	#else
	
				res = mkdir( pathCopy, 0744 );
	#endif
				if (res<0 && errno!=EEXIST && errno!=EACCES)
				{
					return false;
				}
	
				pathCopy[ index ] = '/';
			}
	
			index++;
		}
	}

	if (data)
	{
		if ( fopen_s( &fp, path, "wb" ) != 0 )
		{
			return false;
		}

		fwrite( data, 1, dataLength, fp );

		fclose( fp );
	}
	else
	{
#ifdef _WIN32
		res = _mkdir( pathCopy );
#else
		res = mkdir( pathCopy, 0744 );
#endif

		if (res<0 && errno!=EEXIST)
		{
			return false;
		}
	}

	return true;
}
bool IsSlash(unsigned char c)
{
	return c=='/' || c=='\\';
}

void AddSlash( char *input )
{
	if (input==0 || input[0]==0)
		return;

	int lastCharIndex=(int) strlen(input)-1;
	if (input[lastCharIndex]=='\\')
		input[lastCharIndex]='/';
	else if (input[lastCharIndex]!='/')
	{
		input[lastCharIndex+1]='/';
		input[lastCharIndex+2]=0;
	}
}
bool DirectoryExists(const char *directory)
{
	_finddata_t fileInfo;
	intptr_t dir;
	char baseDirWithStars[560];
	strcpy_s(baseDirWithStars, directory);
	AddSlash(baseDirWithStars);
	strcat_s(baseDirWithStars, "*.*");
	dir=_findfirst(baseDirWithStars, &fileInfo );
	if (dir==-1)
		return false;
	_findclose(dir);
	return true;
}
void QuoteIfSpaces(char *str)
{
	unsigned i;
	bool hasSpace=false;
	for (i=0; str[i]; i++)
	{
		if (str[i]==' ')
		{
			hasSpace=true;
			break;
		}
	}
	if (hasSpace)
	{
		int len=(int)strlen(str);
		memmove(str+1, str, len);
		str[0]='\"';
		str[len]='\"';
		str[len+1]=0;
	}
}
unsigned int GetFileLength(const char *path)
{
	FILE *fp;
	if (fopen_s(&fp, path, "rb")!=0) return 0;
	fseek(fp, 0, SEEK_END);
	unsigned int fileLength = ftell(fp);
	fclose(fp);
	return fileLength;

}

#endif // _RAKNET_SUPPORT_FileOperations
