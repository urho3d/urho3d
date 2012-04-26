/* -----------------------------------------------------------------------------

	Copyright (c) 2006 Simon Brown                          si@sjbrown.co.uk

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the 
	"Software"), to	deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to 
	permit persons to whom the Software is furnished to do so, subject to 
	the following conditions:

	The above copyright notice and this permission notice shall be included
	in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
	OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
	CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
	
   -------------------------------------------------------------------------- */

// Modified by Lasse Öörni for Urho3D to include only DXT decompression

#include <squish.h>

namespace squish {

static int FixFlags( int flags )
{
	// grab the flag bits
	int method = flags & ( kDxt1 | kDxt3 | kDxt5 );
	int fit = flags & ( kColourIterativeClusterFit | kColourClusterFit | kColourRangeFit );
	int metric = flags & ( kColourMetricPerceptual | kColourMetricUniform );
	int extra = flags & kWeightColourByAlpha;
	
	// set defaults
	if( method != kDxt3 && method != kDxt5 )
		method = kDxt1;
	if( fit != kColourRangeFit )
		fit = kColourClusterFit;
	if( metric != kColourMetricUniform )
		metric = kColourMetricPerceptual;

	// done
	return method | fit | metric | extra;
}

static int Unpack565( u8 const* packed, u8* colour )
{
	// build the packed value
	int value = ( int )packed[0] | ( ( int )packed[1] << 8 );
	
	// get the components in the stored range
	u8 red = ( u8 )( ( value >> 11 ) & 0x1f );
	u8 green = ( u8 )( ( value >> 5 ) & 0x3f );
	u8 blue = ( u8 )( value & 0x1f );

	// scale up to 8 bits
	colour[0] = ( red << 3 ) | ( red >> 2 );
	colour[1] = ( green << 2 ) | ( green >> 4 );
	colour[2] = ( blue << 3 ) | ( blue >> 2 );
	colour[3] = 255;
	
	// return the value
	return value;
}

void DecompressColour( u8* rgba, void const* block, bool isDxt1 )
{
	// get the block bytes
	u8 const* bytes = reinterpret_cast< u8 const* >( block );
	
	// unpack the endpoints
	u8 codes[16];
	int a = Unpack565( bytes, codes );
	int b = Unpack565( bytes + 2, codes + 4 );
	
	// generate the midpoints
	for( int i = 0; i < 3; ++i )
	{
		int c = codes[i];
		int d = codes[4 + i];

		if( isDxt1 && a <= b )
		{
			codes[8 + i] = ( u8 )( ( c + d )/2 );
			codes[12 + i] = 0;
		}
		else
		{
			codes[8 + i] = ( u8 )( ( 2*c + d )/3 );
			codes[12 + i] = ( u8 )( ( c + 2*d )/3 );
		}
	}
	
	// fill in alpha for the intermediate values
	codes[8 + 3] = 255;
	codes[12 + 3] = ( isDxt1 && a <= b ) ? 0 : 255;
	
	// unpack the indices
	u8 indices[16];
	for( int i = 0; i < 4; ++i )
	{
		u8* ind = indices + 4*i;
		u8 packed = bytes[4 + i];
		
		ind[0] = packed & 0x3;
		ind[1] = ( packed >> 2 ) & 0x3;
		ind[2] = ( packed >> 4 ) & 0x3;
		ind[3] = ( packed >> 6 ) & 0x3;
	}

	// store out the colours
	for( int i = 0; i < 16; ++i )
	{
		u8 offset = 4*indices[i];
		for( int j = 0; j < 4; ++j )
			rgba[4*i + j] = codes[offset + j];
	}
}

void DecompressAlphaDxt3( u8* rgba, void const* block )
{
	u8 const* bytes = reinterpret_cast< u8 const* >( block );
	
	// unpack the alpha values pairwise
	for( int i = 0; i < 8; ++i )
	{
		// quantise down to 4 bits
		u8 quant = bytes[i];
		
		// unpack the values
		u8 lo = quant & 0x0f;
		u8 hi = quant & 0xf0;

		// convert back up to bytes
		rgba[8*i + 3] = lo | ( lo << 4 );
		rgba[8*i + 7] = hi | ( hi >> 4 );
	}
}

void DecompressAlphaDxt5( u8* rgba, void const* block )
{
	// get the two alpha values
	u8 const* bytes = reinterpret_cast< u8 const* >( block );
	int alpha0 = bytes[0];
	int alpha1 = bytes[1];
	
	// compare the values to build the codebook
	u8 codes[8];
	codes[0] = ( u8 )alpha0;
	codes[1] = ( u8 )alpha1;
	if( alpha0 <= alpha1 )
	{
		// use 5-alpha codebook
		for( int i = 1; i < 5; ++i )
			codes[1 + i] = ( u8 )( ( ( 5 - i )*alpha0 + i*alpha1 )/5 );
		codes[6] = 0;
		codes[7] = 255;
	}
	else
	{
		// use 7-alpha codebook
		for( int i = 1; i < 7; ++i )
			codes[1 + i] = ( u8 )( ( ( 7 - i )*alpha0 + i*alpha1 )/7 );
	}
	
	// decode the indices
	u8 indices[16];
	u8 const* src = bytes + 2;
	u8* dest = indices;
	for( int i = 0; i < 2; ++i )
	{
		// grab 3 bytes
		int value = 0;
		for( int j = 0; j < 3; ++j )
		{
			int byte = *src++;
			value |= ( byte << 8*j );
		}
		
		// unpack 8 3-bit values from it
		for( int j = 0; j < 8; ++j )
		{
			int index = ( value >> 3*j ) & 0x7;
			*dest++ = ( u8 )index;
		}
	}
	
	// write out the indexed codebook values
	for( int i = 0; i < 16; ++i )
		rgba[4*i + 3] = codes[indices[i]];
}

void Decompress( u8* rgba, void const* block, int flags )
{
	// fix any bad flags
	flags = FixFlags( flags );

	// get the block locations
	void const* colourBlock = block;
	void const* alphaBock = block;
	if( ( flags & ( kDxt3 | kDxt5 ) ) != 0 )
		colourBlock = reinterpret_cast< u8 const* >( block ) + 8;

	// decompress colour
	DecompressColour( rgba, colourBlock, ( flags & kDxt1 ) != 0 );

	// decompress alpha separately if necessary
	if( ( flags & kDxt3 ) != 0 )
		DecompressAlphaDxt3( rgba, alphaBock );
	else if( ( flags & kDxt5 ) != 0 )
		DecompressAlphaDxt5( rgba, alphaBock );
}

void DecompressImage( u8* rgba, int width, int height, void const* blocks, int flags )
{
	// fix any bad flags
	flags = FixFlags( flags );

	// initialise the block input
	u8 const* sourceBlock = reinterpret_cast< u8 const* >( blocks );
	int bytesPerBlock = ( ( flags & kDxt1 ) != 0 ) ? 8 : 16;

	// loop over blocks
	for( int y = 0; y < height; y += 4 )
	{
		for( int x = 0; x < width; x += 4 )
		{
			// decompress the block
			u8 targetRgba[4*16];
			Decompress( targetRgba, sourceBlock, flags );
			
			// write the decompressed pixels to the correct image locations
			u8 const* sourcePixel = targetRgba;
			for( int py = 0; py < 4; ++py )
			{
				for( int px = 0; px < 4; ++px )
				{
					// get the target location
					int sx = x + px;
					int sy = y + py;
					if( sx < width && sy < height )
					{
						u8* targetPixel = rgba + 4*( width*sy + sx );
						
						// copy the rgba value
						for( int i = 0; i < 4; ++i )
							*targetPixel++ = *sourcePixel++;
					}
					else
					{
						// skip this pixel as its outside the image
						sourcePixel += 4;
					}
				}
			}
			
			// advance
			sourceBlock += bytesPerBlock;
		}
	}
}

} // namespace squish

