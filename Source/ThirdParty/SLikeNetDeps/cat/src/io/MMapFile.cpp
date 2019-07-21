/*
	Copyright (c) 2009-2010 Christopher A. Taylor.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	* Neither the name of LibCat nor the names of its contributors may be used
	  to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

#include <cat/io/MMapFile.hpp>
#include <cat/io/Logging.hpp>
using namespace cat;

#if defined(CAT_OS_LINUX)
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
#endif


MMapFile::MMapFile(const char *path)
{
    data = 0;
    offset = 0;
    len = 0;

#if defined(CAT_OS_LINUX)

    fd = open(path, O_RDONLY);
    if (fd == -1) { INANE("MMapFile") << "Unable to open file: " << path; return; }

    struct stat st;
    if (fstat(fd, &st) < 0) { INANE("MMapFile") << "Unable to stat file: " << path; return; }
    len = st.st_size;
    if (len == 0) return;

    data = (char *)mmap(0, len, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) { INANE("MMapFile") << "Unable to mmap file: " << path; return; }

    close(fd);
    fd = -1;

#elif defined(CAT_OS_WINDOWS)

    hMapping = hFile = 0;

    hFile = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_RANDOM_ACCESS, 0);
    if (hFile == INVALID_HANDLE_VALUE) { INANE("MMapFile") << "Unable to open file: " << path; return; }

    len = GetFileSize(hFile, 0);
    if (len == -1) { INANE("MMapFile") << "Unable to stat file: " << path; return; }
    if (len == 0) return;

    hMapping = CreateFileMapping(hFile, 0, PAGE_READONLY, 0, 0, 0);
    if (!hMapping) { INANE("MMapFile") << "Unable to CreateFileMapping[" << GetLastError() << "]: " << path; return; }

    data = (char *)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
    if (!data) { INANE("MMapFile") << "Unable to MapViewOfFile[" << GetLastError() << "]: " << path; return; }

#endif
}

MMapFile::~MMapFile()
{
#if defined(CAT_OS_LINUX)

    if (fd != -1) close(fd);
    if (data) munmap(data, len);

#elif defined(CAT_OS_WINDOWS)

    if (data) UnmapViewOfFile(data);
    if (hMapping) CloseHandle(hMapping);
    if (hFile) CloseHandle(hFile);

#endif
}
