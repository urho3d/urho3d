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

#ifndef CAT_MMAPFILE_HPP
#define CAT_MMAPFILE_HPP

#include <cat/Platform.hpp>

#if defined(CAT_OS_WINDOWS)
# include <cat/port/WindowsInclude.hpp>
#endif

namespace cat {


class MMapFile
{
    char *data;
    u32 len;
    s32 offset;

#if defined(CAT_OS_LINUX)
    int fd;
#elif defined(CAT_OS_WINDOWS)
    HANDLE hFile, hMapping;
#endif

public:
    MMapFile(const char *path);
    ~MMapFile();

    inline bool good() { return data != 0; }
    inline bool inside() { return offset >= 0 && offset < (s32)len; }

    inline u32 size() { return len; }

    inline void seek(s32 poffset) { offset = poffset; }
    inline bool underrun(s32 requested) { return (u32)(offset + requested) > len; }
    inline char *look() { return data + offset; }
    inline char *look(s32 offset) { return data + offset; }
    inline char *read(s32 requested) { offset += requested; return data + (offset - requested); }
    inline void skip(s32 requested) { offset += requested; }
    inline u32 remaining() { return len - offset; }
    inline u32 getOffset() { return offset; }
};


} // namespace cat

#endif // CAT_MMAPFILE_HPP
