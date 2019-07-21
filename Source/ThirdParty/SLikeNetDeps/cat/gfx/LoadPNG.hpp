/*
	Copyright (c) 2009 Christopher A. Taylor.  All rights reserved.

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

#ifndef LOAD_PNG_HPP
#define LOAD_PNG_HPP

#include <cat/AllFramework.hpp>
#include <string>
using namespace std;
#include "zlib-1.2.4/zlib.h"

namespace cat {

#include "CRC32.hpp"

#ifdef CAT_PRAGMA_PACK
#pragma pack(push)
#pragma pack(1)
#endif

	typedef struct
	{
		u32 length;
		char type[4];
	} CAT_PACKED SectionHeader;

	typedef struct
	{
		u32 length;
		char type[4];
		u32 crc;
	} CAT_PACKED EmptySection;

	typedef struct
	{
		u32 width, height;
		u8 bitDepth, colorType, compressionMethod, filterMethod, interlaceMethod;
	} CAT_PACKED PNG_IHDR;

	typedef struct
	{
		u8 r, g, b;
	} CAT_PACKED PLTE_Entry8;

	typedef struct
	{
		PLTE_Entry8 table[256];
	} CAT_PACKED PNG_PLTE;

#ifdef CAT_PRAGMA_PACK
#pragma pack(pop)
#endif


	class PNGSkeletonTokenizer
	{
	protected:
		MMapFile mmf;
		CRC32Calculator calculator;
		string path;

		// Split this from the ctor, so virtual overloads are in place by the time we start reading
		bool read(const u8 signature[8]); // Returns false on failure

	public:
		PNGSkeletonTokenizer(const string &path, u32 CRC32polynomial);
		virtual ~PNGSkeletonTokenizer() {}

	protected:
		// return true only if section is valid (no exceptions please)
		virtual bool onSection(char type[4], u8 data[], u32 len) = 0;
	};


	class PNGTokenizer : public PNGSkeletonTokenizer
	{
	protected:
		z_stream zstream;
		u8 *obuf;
		u32 olen;
		int lastZlibResult;

		bool requirePOTS;

		PNG_IHDR header;
		u16 bpp;
		u32 palette[256];
		u8 trans_red, trans_green, trans_blue;

		void rasterizeImage(u8 *image);

	public:
		PNGTokenizer(const string &path, bool requirePOTS);
		virtual ~PNGTokenizer();

	protected:
		bool onSection(char type[4], u8 data[], u32 len);

	protected:
		// Rasterized image in R8G8B8A8 format, new dimensions are powers of two
		virtual void onImage(u32 *image, u32 newWidth, u32 newHeight);

	protected:
		// Important sections
		void onIHDR(PNG_IHDR *infohdr);
		void onPLTE(PNG_PLTE *c_palette);
		void onIDAT(u8 *data, u32 len);
		void onIEND();

		// Transparency info
		void onTRNS_Color2(u16 red, u16 green, u16 blue);
		void onTRNS_Color3(u8 trans[256], u16 len);

		// Color space information (all unimplemented)
		void onGAMA();
		void onCHRM();
		void onSRGB();
		void onICCP();

		// Textual information (all unimplemented)
		void onTEXT();
		void onZTXT();
		void onITXT();

		// Other non-essential info (all unimplemented)
		void onBKGD();
		void onPHYS();
		void onSBIT();
		void onSPLT();
		void onHIST();
		void onTIME();
	};


} // namespace cat

#endif // LOAD_PNG_HPP
