/*
 * This file was taken from RakNet 4.082.
 * Please see licenses/RakNet license.txt for the underlying license and related copyright.
 *
 * Modified work: Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 * This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 * license found in the license.txt file in the root directory of this source tree.
 */

/**
* Original file by the_viking, fixed by Rv¥mulo Fernandes, fixed by Emmanuel Nars
* Should emulate windows finddata structure
*/
#if (defined(__GNUC__)  || defined(__GCCXML__)) && !defined(_WIN32)
#include "slikenet/_FindFirst.h"
#include "slikenet/DS_List.h"

#include <sys/stat.h>

#include <fnmatch.h>
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"


static DataStructures::List< _findinfo_t* > fileInfo;
	
#include "slikenet/memoryoverride.h"
#include "slikenet/assert.h"

/**
* _findfirst - equivalent
*/
long _findfirst(const char *name, _finddata_t *f)
{
	SLNet::RakString nameCopy = name;
	SLNet::RakString filter;

        // This is linux only, so don't bother with '\'
	const char* lastSep = strrchr(name,'/');
	if(!lastSep)
	{
            // filter pattern only is given, search current directory.
            filter = nameCopy;
            nameCopy = ".";
	} else
	{
            // strip filter pattern from directory name, leave
            // trailing '/' intact.
            filter = lastSep+1;
            unsigned sepIndex = lastSep - name;
            nameCopy.Erase(sepIndex+1, nameCopy.GetLength() - sepIndex-1);
	}

	DIR* dir = opendir(nameCopy);
        
	if(!dir) return -1;

	_findinfo_t* fi = SLNet::OP_NEW<_findinfo_t>( _FILE_AND_LINE_ );
	fi->filter    = filter;
	fi->dirName   = nameCopy;  // we need to remember this for stat()
	fi->openedDir = dir;
	fileInfo.Insert(fi, _FILE_AND_LINE_);

        long ret = fileInfo.Size()-1;

        // Retrieve the first file. We cannot rely on the first item
        // being '.'
        if (_findnext(ret, f) == -1) return -1;
        else return ret;
}































int _findnext(long h, _finddata_t *f)
{
	RakAssert(h >= 0 && h < (long)fileInfo.Size());
	if (h < 0 || h >= (long)fileInfo.Size()) return -1;
        
	_findinfo_t* fi = fileInfo[h];

	while(true)
	{
		dirent* entry = readdir(fi->openedDir);
		if(entry == 0) return -1;

                // Only report stuff matching our filter
                if (fnmatch(fi->filter, entry->d_name, FNM_PATHNAME) != 0) continue;

                // To reliably determine the entry's type, we must do
                // a stat...  don't rely on entry->d_type, as this
                // might be unavailable!
                struct stat filestat;
				SLNet::RakString fullPath = fi->dirName + entry->d_name;
                if (stat(fullPath, &filestat) != 0)
                {
                    RAKNET_DEBUG_PRINTF("Cannot stat %s\n", fullPath.C_String());
                    continue;
                }

                if (S_ISREG(filestat.st_mode))
                {
                    f->attrib = _A_NORMAL;
                } else if (S_ISDIR(filestat.st_mode))
                {
                    f->attrib = _A_SUBDIR;                    
                } else continue; // We are interested in files and
                                 // directories only. Links currently
                                 // are not supported.

                f->size = filestat.st_size;
                strncpy_s(f->name, entry->d_name, STRING_BUFFER_SIZE);
                
                return 0;
	}

	return -1;
}





/**
 * _findclose - equivalent
 */
int _findclose(long h)
{
    if (h==-1) return 0;
   
    if (h < 0 || h >= (long)fileInfo.Size())
    {
        RakAssert(false);
        return -1;
    }

    _findinfo_t* fi = fileInfo[h];
    closedir(fi->openedDir);
    fileInfo.RemoveAtIndex(h);
	SLNet::OP_DELETE(fi, _FILE_AND_LINE_);
    return 0;   
}
#endif
