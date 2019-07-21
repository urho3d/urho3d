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

#ifndef CAT_PACKAGE_MANAGER_HPP
#define CAT_PACKAGE_MANAGER_HPP

#include <cat/Platform.hpp>
#include <cat/port/FastDelegate.h>

namespace cat {


// Package resource identifier macro
#define CAT_UNCAGE(packagePath, offset, size) offset, size

/*
	All file resources are packed into one large file and each is
	assigned a unique identifying number, starting from 0.

	The client source code is preprocessed by a tool that replaces the
	arguments of the CAT_UNPACK() macro with the correct ID number based
	on the string given as the first argument.

	CAT_UNPACK("world1/lightmap3.png")
	-> CAT_UNPACK("world1/lightmap3.png", 15241, 256, 0xdecryptionkey)

	At runtime the client application will not be aware of the string
	name of a resource in the package, only where to go to get it.

	Resources that are used together during tuning will have identifiers
	that are close together so that disk seek time is minimized.
*/


/*
	Kennel files are simple concatenations of all of the game resources.

	The goal is to reduce access time to data by cutting the operating
	system's file-system out completely.  Furthermore, data that are
	accessed together are stored together on disk and in the same order
	that they are accessed.

	Textures are compressed with modified JPEG-LS, providing the fastest
	possible access time.
	Sounds compression hasn't been investigated yet.

	Each resource (sound/texture) is obfuscated with a 64-bit key, making
	it necessary to reverse-engineer the game client to decode in-game
	resources outside of the game.

	The KennelFile object implements optimized algorithms for performing
	in-place modification to a large datafile (>4 GB).
*/

class KennelPatchFile : AsyncFile
{
public:
	KennelPatchFile();
	~KennelPatchFile();

public:
	void Insert
};


// Kennel Patch Callback (param=bool: true on successful patch, false on error)
typedef fastdelegate::FastDelegate1<bool, void> KennelPatchCallback;

class KennelFile : AsyncFile
{
public:
	KennelFile();
	virtual ~KennelFile();

public:
	bool Move(u64 dest, u32 region_size, u64 src, KennelPatchCallback OnComplete);
};


} // namespace cat

#endif // CAT_PACKAGE_MANAGER_HPP
