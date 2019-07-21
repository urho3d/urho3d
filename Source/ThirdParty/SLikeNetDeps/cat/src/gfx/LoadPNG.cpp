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

#include <cat/gfx/LoadPNG.hpp>
#include <cat/AllFramework.hpp>
using namespace cat;



//// CRC32Calculator

CRC32Calculator::CRC32Calculator(u32 polynomial)
{
	for (u32 n = 0; n < 256; ++n)
	{
		u32 c = n;

		for (u16 k = 0; k < 8; ++k)
		{
			if (c & 1)	c = polynomial ^ (c >> 1);
			else		c >>= 1;
		}

		table[n] = c;
	}
}

void CRC32Calculator::perform(const void *vbuf, u32 len)
{
	const u8 *buf = (const u8*)vbuf;

	while (len--) reg = table[(reg ^ *buf++) & 0xff] ^ (reg >> 8);
}
const u32 PNG_CRC32_POLYNOMIAL = 0xEDB88320;
const u8 PNG_SIGNATURE[8] = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1a, '\n'};

// Critical sections
const char *PNG_SECTION_IHDR = "IHDR";	// Image header
const char *PNG_SECTION_PLTE = "PLTE";	// Palette
const char *PNG_SECTION_IDAT = "IDAT";	// Image data
const char *PNG_SECTION_IEND = "IEND";	// Image data trailer

// Transparency info
const char *PNG_SECTION_TRNS = "tRNS";	// Transparency info

// Color space information
const char *PNG_SECTION_GAMA = "gAMA";	// Image gamma
const char *PNG_SECTION_CHRM = "cHRM";	// Primary chromaticities
const char *PNG_SECTION_SRGB = "sRGB";	// Standard RGB color space
const char *PNG_SECTION_ICCP = "iCCP";	// Embedded ICC profile

// Textual information
const char *PNG_SECTION_TEXT = "tEXt";	// Textual data
const char *PNG_SECTION_ZTXT = "zTXt";	// Compressed textual data
const char *PNG_SECTION_ITXT = "iTXt";	// International-encoded textual data

// Other non-essential info
const char *PNG_SECTION_BKGD = "bKGD";	// Background color
const char *PNG_SECTION_PHYS = "pHYs";	// Physical pixel dimensions
const char *PNG_SECTION_SBIT = "sBIT";	// Significant bits
const char *PNG_SECTION_SPLT = "sPLT";	// Suggested palette
const char *PNG_SECTION_HIST = "hIST";	// Palette histogram
const char *PNG_SECTION_TIME = "tIME";	// Last modification time


PNGSkeletonTokenizer::PNGSkeletonTokenizer(const string &ppath, u32 CRC32polynomial)
	: mmf(ppath.c_str()), calculator(CRC32polynomial), path(ppath)
{
	ENFORCE(mmf.good()) << "Unable to read file: " << ppath;
}


bool PNGSkeletonTokenizer::read(const u8 signature[8])
{
	if (mmf.underrun(8) || memcmp(mmf.read(8), signature, 8)) return false;

	while (!mmf.underrun(sizeof(SectionHeader)))
	{
		SectionHeader *hdr = (SectionHeader *)mmf.read(sizeof(SectionHeader));
		u32 len = getBE(hdr->length);

		if (mmf.underrun(len + 4)) return false;
		u8 *data = (u8*)mmf.read(len + 4);
		u32 crc = getBE(*(u32*)(data + len));

		calculator.begin();
		calculator.perform(hdr->type, 4);
		calculator.perform(data, len);
		if (calculator.finish() != crc) return false;

		if (!onSection(hdr->type, data, len)) break;
	}

	return true;
}

PNGTokenizer::PNGTokenizer(const string &path, bool prequirePOTS)
	: PNGSkeletonTokenizer(path, PNG_CRC32_POLYNOMIAL)
{
	requirePOTS = prequirePOTS;

	CAT_OBJCLR(zstream);
	ENFORCE(inflateInit(&zstream) == Z_OK) << "Unable to start zlib decompression";

	obuf = 0;
	olen = 0;
	lastZlibResult = Z_OK;

	ENFORCE(PNGSkeletonTokenizer::read(PNG_SIGNATURE)) << "File is not a valid PNG image: " << path;

	INANE("PNGTokenizer") << "Successfully tokenized " << path;
}

PNGTokenizer::~PNGTokenizer()
{
	inflateEnd(&zstream);
}

static s16 paethPredictor(s16 left, s16 above, s16 upper_left)
{
	s16 pa = above - upper_left;
	s16 pb = left - upper_left;
	s16 pc = pa + pb;

	pa = abs(pa);
	pb = abs(pb);
	pc = abs(pc);

	if ((pa <= pb) && (pa <= pc))
		return left;
	if (pb <= pc)
		return above;
	else
		return upper_left;
}

static void unfilterImage(u8 *scanline, u16 height, u16 bytes_per_scanline, u16 bpp)
{
	// Unrolled first loop
	switch (*scanline)
	{
	case 1:	// sub
	case 4:	// paeth
		{
			for (u16 j = bpp + 1; j < bytes_per_scanline; ++j)
				scanline[j] += scanline[j - bpp];
		}
		break;
	case 3:	// average
		{
			for (u16 j = bpp + 1; j < bytes_per_scanline; ++j)
				scanline[j] += scanline[j - bpp] / 2;
		}
	}

	u8 *lastline = scanline;
	scanline += bytes_per_scanline;

	for (u16 i = 1; i < height; ++i)
	{
		switch (*scanline)
		{
		case 1:	// sub
			{
				for (u16 j = bpp + 1; j < bytes_per_scanline; ++j)
					scanline[j] += scanline[j - bpp];
			}
			break;
		case 2:	// up
			{
				u8 *to = scanline + 1, *from = lastline + 1;
				u16 ctr = bytes_per_scanline - 1;

				u16 ctr16 = ctr / 16;

				while (ctr16--)
				{
					to[0] += from[0]; to[1] += from[1]; to[2] += from[2]; to[3] += from[3];
					to[4] += from[4]; to[5] += from[5]; to[6] += from[6]; to[7] += from[7];
					to[8] += from[8]; to[9] += from[9]; to[10] += from[10]; to[11] += from[11];
					to[12] += from[12]; to[13] += from[13]; to[14] += from[14]; to[15] += from[15];

					to += 16;
					from += 16;
				}

				ctr %= 16;
				while (ctr--)
					*to++ += *from++;
			}
			break;
		case 3:	// average
			{
				for (u16 j = 1; j < bpp + 1; ++j)
					scanline[j] += lastline[j] / 2;
				for (u16 k = bpp + 1; k < bytes_per_scanline; ++k)
					scanline[k] += (scanline[k - bpp] + lastline[k]) / 2;
			}
			break;
		case 4:	// paeth
			{
				for (u16 j = 1; j < bpp + 1; ++j)
					scanline[j] += lastline[j];
				for (u16 k = bpp + 1; k < bytes_per_scanline; ++k)
					scanline[k] += paethPredictor(scanline[k - bpp], lastline[k], lastline[k - bpp]);
			}
		}

		lastline = scanline;
		scanline += bytes_per_scanline;
	}
}

static u32 nextHighestPOT(u32 n)
{
	u32 b = 2;
	while (n >>= 1) b <<= 1;
	return b;
}

void PNGTokenizer::rasterizeImage(u8 *image)
{
	u32 newWidth, newHeight;

	if (requirePOTS)
	{
		newWidth = CAT_IS_POWER_OF_2(header.width) ? header.width : nextHighestPOT(header.width);
		newHeight = CAT_IS_POWER_OF_2(header.height) ? header.height : nextHighestPOT(header.height);
	}
	else
	{
		newWidth = header.width;
		newHeight = header.height;
	}

	switch (header.colorType)
	{
	case 2:	// RGB (3 entries)
		{
			auto_ptr<u8> final(new u8[newWidth * newHeight * 4]);
			ENFORCE(final.get()) << "Out of memory: Unable to allocate texture data";

			u8 *rgba_ptr = final.get();
			u32 hctr = header.height;
			while (hctr--)
			{
				++image;

				u32 wctr = header.width;
				while (wctr--)
				{
					u8 r, g, b;
					*rgba_ptr++ = r = *image++;
					*rgba_ptr++ = g = *image++;
					*rgba_ptr++ = b = *image++;

					if ((r == trans_red) && (g == trans_green) && (b == trans_blue))
						*rgba_ptr++ = 0;
					else
						*rgba_ptr++ = 0xff;
				}

				rgba_ptr += (newWidth - header.width) * 4;
			}

			onImage((u32*)final.get(), newWidth, newHeight);
		}
		break;

	case 3:	// Paletted (1 entry)
		{
			auto_ptr<u32> final(new u32[newWidth * newHeight]);
			ENFORCE(final.get()) << "Out of memory: Unable to allocate texture data";

			u32 *rgba_ptr = final.get();
			u32 hctr = header.height;
			while (hctr--)
			{
				++image;

				u32 wctr = header.width;

				u32 ctr16 = wctr / 16;
				while (ctr16--)
				{
					rgba_ptr[0] = palette[image[0]]; rgba_ptr[1] = palette[image[1]]; rgba_ptr[2] = palette[image[2]]; rgba_ptr[3] = palette[image[3]];
					rgba_ptr[4] = palette[image[4]]; rgba_ptr[5] = palette[image[5]]; rgba_ptr[6] = palette[image[6]]; rgba_ptr[7] = palette[image[7]];
					rgba_ptr[8] = palette[image[8]]; rgba_ptr[9] = palette[image[9]]; rgba_ptr[10] = palette[image[10]]; rgba_ptr[11] = palette[image[11]];
					rgba_ptr[12] = palette[image[12]]; rgba_ptr[13] = palette[image[13]]; rgba_ptr[14] = palette[image[14]]; rgba_ptr[15] = palette[image[15]];

					rgba_ptr += 16;
					image += 16;
				}

				wctr %= 16;
				while (wctr--)
					*rgba_ptr++ = palette[*image++];

				rgba_ptr += newWidth - header.width;
			}

			onImage(final.get(), newWidth, newHeight);
		}
		break;

	case 6:	// RGBA (4 entries)
		{
			auto_ptr<u32> final(new u32[newWidth * newHeight]);
			ENFORCE(final.get()) << "Out of memory: Unable to allocate texture data";

			u32 *rgba_ptr = final.get();
			u32 hctr = header.height;
			while (hctr--)
			{
				++image;

				u32 wctr = header.width;
				while (wctr--)
				{
					*rgba_ptr++ = *(u32*)image;
					image += 4;
				}

				rgba_ptr += newWidth - header.width;
			}

			onImage(final.get(), newWidth, newHeight);
		}
	}
}

bool PNGTokenizer::onSection(char type[4], u8 data[], u32 len)
{
	if (!memcmp(type, PNG_SECTION_IHDR, 4))
		onIHDR((PNG_IHDR *)data);
	else if (!memcmp(type, PNG_SECTION_PLTE, 4))
		onPLTE((PNG_PLTE *)data);
	else if (!memcmp(type, PNG_SECTION_IDAT, 4))
		onIDAT(data, len);
	else if (!memcmp(type, PNG_SECTION_TRNS, 4))
	{
		switch (header.colorType)
		{
		case 2:	// R16G16B16 color specification
			if (len == 6)
			onTRNS_Color2(getBE(*(u16*)data),
						  getBE(*(u16*)(data + 2)),
						  getBE(*(u16*)(data + 4)));
			break;
		case 3:	// Indexed color (1by x palette)
			onTRNS_Color3(data, len);
		}
	}
	else if (!memcmp(type, PNG_SECTION_IEND, 4))
		onIEND();

	return true;
}

#include "charls/interface.h"

void PNGTokenizer::onImage(u32 *image, u32 newWidth, u32 newHeight)
{
	INFO("Test") << "Read file";

	u8 *src = (u8*)image;
	size_t srcLen = (newWidth*newHeight) * 4;

	double t0, t1;
	int result;

	JLS_ERROR res;
	JlsParamaters params;
	CAT_OBJCLR(params);
	params.bitspersample = 8;
	params.bytesperline = newWidth * 4;
	params.width = newWidth;
	params.height = newHeight;
	params.components = 4;
	params.allowedlossyerror = 0;
	params.ilv = ILV_LINE;
	params.colorTransform = 2; // 0..3
	params.outputBgr = 0;
	//params.custom.T1 = 3;
	//params.custom.T2 = 7;
	//params.custom.T3 = 21;

	u8 *dest2 = new u8[srcLen];
	size_t dest2Len = srcLen;

	t0 = Clock::usec();
	res = JpegLsEncode(dest2, dest2Len, &dest2Len, src, srcLen, &params);
	t1 = Clock::usec();

	if (OK == res)
	{
		INFO("Test") << "JPEG-LS Compression: Size = " << dest2Len << " Original size = " << srcLen << " Compression ratio = " << dest2Len / (float)srcLen * 100.f << "% Took " << t1 - t0 << " usec";
	}
	else
	{
		INFO("Test") << "JPEG-LS Compression failed with error " << res;
	}

	ofstream file("jpegls.out", ios::binary);

	if (!file)
	{
		INFO("test") << "Unable to open file";
	}
	else
	{
		file.write((char*)dest2, dest2Len);
		file.close();
	}

	u8 *test2 = new u8[srcLen];
	size_t test2Len = srcLen;

	CAT_OBJCLR(params);
	JpegLsReadHeader(dest2, test2Len, &params);

	t0 = Clock::usec();
	res = JpegLsDecode(test2, test2Len, dest2, dest2Len);
	t1 = Clock::usec();

	if (OK == res)
	{
		INFO("Test") << "JPEG-LS Decompression: Took " << t1 - t0 << " usec";
	}

	/*
	for (int ii = 0; ii < newHeight; ++ii)
	{
		u32 left = 0, ul = 0;

		for (int jj = 0; jj < newWidth; ++jj)
		{
			u32 x = image[ii * newWidth + jj];

			u32 above;

			if (ii > 0)
				above = image[(ii - 1) * newWidth + jj];
			else
				above = 0;

			image[ii * newWidth + jj] = x;

			left = x;
			ul = above;
		}
	}
	*/


	u8 *cdest = new u8[srcLen];
	uLongf cdest_len = srcLen;

	t0 = Clock::usec();
	result = compress(cdest, &cdest_len, src, srcLen);
	t1 = Clock::usec();

	if (Z_OK == result)
	{
		INFO("Test") << "ZLIB Compression: Size = " << cdest_len << " Original size = " << srcLen << " Compression ratio = " << cdest_len / (float)srcLen * 100.f << "% Took " << t1 - t0 << " usec";
	}

	u8 *udest = new u8[srcLen];
	uLongf udest_len = srcLen;

	t0 = Clock::usec();
	result = uncompress(udest, &udest_len, cdest, cdest_len);
	t1 = Clock::usec();

	if (Z_OK == result)
	{
		INFO("Test") << "ZLIB Decompression: Took " << t1 - t0 << " usec";
	}
}

void PNGTokenizer::onIHDR(PNG_IHDR *infohdr)
{
	ENFORCE(!obuf) << "Dupe IHDR in " << path;

	memcpy(&header, infohdr, sizeof(PNG_IHDR));

	header.width = getBE(header.width);
	header.height = getBE(header.height);

	trans_blue = 0;
	trans_green = 0;
	trans_red = 0;

	switch (header.colorType)
	{
	default: EXCEPTION() << "Invalid image format for " << path << ": Must be RGB, RGBA or paletted";
	case 2:	// RGB (3 entries)
		bpp = 3;
		break;
	case 3:	// Paletted (1 entry)
		bpp = 1;
		break;
	case 6:	// RGBA (4 entries)
		bpp = 4;
	}

	olen = (header.width * bpp + 1) * header.height;
	ENFORCE(obuf = new u8[olen]) << "Out of memory: Unable to allocate texture data";

	zstream.avail_out = olen;
	zstream.next_out = obuf;
}

void PNGTokenizer::onPLTE(PNG_PLTE *c_palette)
{
	for (u16 i = 0; i < 255; ++i)
		palette[i] = (c_palette->table[i].r) | (c_palette->table[i].g << 8) | (c_palette->table[i].b << 16) | 0xff000000;

	palette[255] = (c_palette->table[255].r) | (c_palette->table[255].g << 8) | (c_palette->table[255].b << 16);
}

void PNGTokenizer::onIDAT(u8 *data, u32 len)
{
	zstream.next_in = data;
	zstream.avail_in = len;

	lastZlibResult = inflate(&zstream, Z_NO_FLUSH);
	ENFORCE(lastZlibResult == Z_OK || lastZlibResult == Z_STREAM_END) << "Corrupted IDAT in " << path;
}

void PNGTokenizer::onIEND()
{
	ENFORCE(lastZlibResult == Z_STREAM_END) << "Incomplete image data from " << path;
	if (zstream.avail_out) WARN("PNGTokenizer") << "Overallocated " << zstream.avail_out << " bytes for " << path;

	unfilterImage(obuf, (u16)header.height, (u16)header.width * bpp + 1, bpp);

	rasterizeImage(obuf);
}


//// Transparency info ////

void PNGTokenizer::onTRNS_Color2(u16 red, u16 green, u16 blue)
{
	trans_red = (u8)red;
	trans_green = (u8)green;
	trans_blue = (u8)blue;
}

void PNGTokenizer::onTRNS_Color3(u8 trans[256], u16 len)
{
	for (u16 i = 0; i < len; ++i)
		palette[i] = (palette[i] & 0x00ffffff) | (trans[i] << 24);
}
