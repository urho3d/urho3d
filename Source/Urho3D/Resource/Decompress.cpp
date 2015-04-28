//
// Copyright (c) 2008-2015 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../Resource/Decompress.h"

// DXT decompression based on the Squish library, modified for Urho3D

namespace Urho3D
{

/* -----------------------------------------------------------------------------

    Copyright (c) 2006 Simon Brown                          si@sjbrown.co.uk

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the 
    "Software"), to    deal in the Software without restriction, including
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

static int Unpack565( unsigned char const* packed, unsigned char* colour )
{
    // build the packed value
    int value = ( int )packed[0] | ( ( int )packed[1] << 8 );
    
    // get the components in the stored range
    unsigned char red = ( unsigned char )( ( value >> 11 ) & 0x1f );
    unsigned char green = ( unsigned char )( ( value >> 5 ) & 0x3f );
    unsigned char blue = ( unsigned char )( value & 0x1f );
    
    // scale up to 8 bits
    colour[0] = ( red << 3 ) | ( red >> 2 );
    colour[1] = ( green << 2 ) | ( green >> 4 );
    colour[2] = ( blue << 3 ) | ( blue >> 2 );
    colour[3] = 255;
    
    // return the value
    return value;
}

static void DecompressColourDXT( unsigned char* rgba, void const* block, bool isDxt1 )
{
    // get the block bytes
    unsigned char const* bytes = reinterpret_cast< unsigned char const* >( block );
    
    // unpack the endpoints
    unsigned char codes[16];
    int a = Unpack565( bytes, codes );
    int b = Unpack565( bytes + 2, codes + 4 );
    
    // generate the midpoints
    for( int i = 0; i < 3; ++i )
    {
        int c = codes[i];
        int d = codes[4 + i];

        if( isDxt1 && a <= b )
        {
            codes[8 + i] = ( unsigned char )( ( c + d )/2 );
            codes[12 + i] = 0;
        }
        else
        {
            codes[8 + i] = ( unsigned char )( ( 2*c + d )/3 );
            codes[12 + i] = ( unsigned char )( ( c + 2*d )/3 );
        }
    }
    
    // fill in alpha for the intermediate values
    codes[8 + 3] = 255;
    codes[12 + 3] = ( isDxt1 && a <= b ) ? 0 : 255;
    
    // unpack the indices
    unsigned char indices[16];
    for( int i = 0; i < 4; ++i )
    {
        unsigned char* ind = indices + 4*i;
        unsigned char packed = bytes[4 + i];
        
        ind[0] = packed & 0x3;
        ind[1] = ( packed >> 2 ) & 0x3;
        ind[2] = ( packed >> 4 ) & 0x3;
        ind[3] = ( packed >> 6 ) & 0x3;
    }
    
    // store out the colours
    for( int i = 0; i < 16; ++i )
    {
        unsigned char offset = 4*indices[i];
        for( int j = 0; j < 4; ++j )
            rgba[4*i + j] = codes[offset + j];
    }
}

static void DecompressAlphaDXT3( unsigned char* rgba, void const* block )
{
    unsigned char const* bytes = reinterpret_cast< unsigned char const* >( block );
    
    // unpack the alpha values pairwise
    for( int i = 0; i < 8; ++i )
    {
        // quantise down to 4 bits
        unsigned char quant = bytes[i];
        
        // unpack the values
        unsigned char lo = quant & 0x0f;
        unsigned char hi = quant & 0xf0;
        
        // convert back up to bytes
        rgba[8*i + 3] = lo | ( lo << 4 );
        rgba[8*i + 7] = hi | ( hi >> 4 );
    }
}

static void DecompressAlphaDXT5( unsigned char* rgba, void const* block )
{
    // get the two alpha values
    unsigned char const* bytes = reinterpret_cast< unsigned char const* >( block );
    int alpha0 = bytes[0];
    int alpha1 = bytes[1];
    
    // compare the values to build the codebook
    unsigned char codes[8];
    codes[0] = ( unsigned char )alpha0;
    codes[1] = ( unsigned char )alpha1;
    if( alpha0 <= alpha1 )
    {
        // use 5-alpha codebook
        for( int i = 1; i < 5; ++i )
            codes[1 + i] = ( unsigned char )( ( ( 5 - i )*alpha0 + i*alpha1 )/5 );
        codes[6] = 0;
        codes[7] = 255;
    }
    else
    {
        // use 7-alpha codebook
        for( int i = 1; i < 7; ++i )
            codes[1 + i] = ( unsigned char )( ( ( 7 - i )*alpha0 + i*alpha1 )/7 );
    }
    
    // decode the indices
    unsigned char indices[16];
    unsigned char const* src = bytes + 2;
    unsigned char* dest = indices;
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
            *dest++ = ( unsigned char )index;
        }
    }
    
    // write out the indexed codebook values
    for( int i = 0; i < 16; ++i )
        rgba[4*i + 3] = codes[indices[i]];
}

static void DecompressDXT( unsigned char* rgba, const void* block, CompressedFormat format)
{
    // get the block locations
    void const* colourBlock = block;
    void const* alphaBock = block;
    if( format == CF_DXT3 || format == CF_DXT5)
        colourBlock = reinterpret_cast< unsigned char const* >( block ) + 8;
    
    // decompress colour
    DecompressColourDXT( rgba, colourBlock, format == CF_DXT1 );
    
    // decompress alpha separately if necessary
    if( format == CF_DXT3 )
        DecompressAlphaDXT3( rgba, alphaBock );
    else if ( format == CF_DXT5 )
        DecompressAlphaDXT5( rgba, alphaBock );
}

void DecompressImageDXT( unsigned char* rgba, const void* blocks, int width, int height, int depth, CompressedFormat format )
{
    // initialise the block input
    unsigned char const* sourceBlock = reinterpret_cast< unsigned char const* >( blocks );
    int bytesPerBlock = format == CF_DXT1 ? 8 : 16;
    
    // loop over blocks
    for( int z = 0; z < depth; ++z )
    {
        int sz = width*height*4*z;
        for( int y = 0; y < height; y += 4 )
        {
            for( int x = 0; x < width; x += 4 )
            {
                // decompress the block
                unsigned char targetRgba[4*16];
                DecompressDXT( targetRgba, sourceBlock, format );
                
                // write the decompressed pixels to the correct image locations
                unsigned char const* sourcePixel = targetRgba;
                for( int py = 0; py < 4; ++py )
                {
                    for( int px = 0; px < 4; ++px )
                    {
                        // get the target location
                        int sx = x + px;
                        int sy = y + py;
                        if( sx < width && sy < height )
                        {
                            unsigned char* targetPixel = rgba + sz + 4*( width*sy + sx );
                            
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
}

// ETC and PVRTC decompression based on the Oolong Engine, modified for Urho3D

/*
Oolong Engine for the iPhone / iPod touch
Copyright (c) 2007-2008 Wolfgang Engel  http://code.google.com/p/oolongengine/

This software is provided 'as-is', without any express or implied warranty
In no event will the authors be held liable for any damages arising from the
use of this software. Permission is granted to anyone to use this software for
any purpose,  including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim
that you wrote the original software. If you use this software in a product, an
acknowledgment in the product documentation would be appreciated but is not 
required.
2. Altered source versions must be plainly marked as such, and must not be 
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#define _CLAMP_(X,Xmin,Xmax) ( (X)<(Xmax) ? ( (X)<(Xmin)?(Xmin):(X) ) : (Xmax) )

unsigned ETC_FLIP =  0x01000000;
unsigned ETC_DIFF = 0x02000000;
const int mod[8][4]={{2, 8,-2,-8},
                    {5, 17, -5, -17},
                    {9, 29, -9, -29},
                    {13, 42, -13, -42},
                    {18, 60, -18, -60},
                    {24, 80, -24, -80},
                    {33, 106, -33, -106},
                    {47, 183, -47, -183}};

// lsb: hgfedcba ponmlkji msb: hgfedcba ponmlkji due to endianness
static unsigned long ModifyPixel(int red, int green, int blue, int x, int y, unsigned long modBlock, int modTable)
{
    int index = x*4+y, pixelMod;
    unsigned long mostSig = modBlock<<1;
    if (index<8)    //hgfedcba
        pixelMod = mod[modTable][((modBlock>>(index+24))&0x1)+((mostSig>>(index+8))&0x2)];
    else    // ponmlkj
        pixelMod = mod[modTable][((modBlock>>(index+8))&0x1)+((mostSig>>(index-8))&0x2)];
    
    red = _CLAMP_(red+pixelMod,0,255);
    green = _CLAMP_(green+pixelMod,0,255);
    blue = _CLAMP_(blue+pixelMod,0,255);
    
    return ((blue<<16) + (green<<8) + red)|0xff000000;
}

static void DecompressETC(unsigned char* pDestData, const void* pSrcData)
{
    unsigned long blockTop, blockBot, *input = (unsigned long*)pSrcData, *output;
    unsigned char red1, green1, blue1, red2, green2, blue2;
    bool bFlip, bDiff;
    int modtable1,modtable2;
    
    blockTop = *(input++);
    blockBot = *(input++);
    
    output = (unsigned long*)pDestData;
    // check flipbit
    bFlip = (blockTop & ETC_FLIP) != 0;
    bDiff = (blockTop & ETC_DIFF) != 0;
    
    if(bDiff)
    {    // differential mode 5 colour bits + 3 difference bits
        // get base colour for subblock 1
        blue1 = (unsigned char)((blockTop&0xf80000)>>16);
        green1 = (unsigned char)((blockTop&0xf800)>>8);
        red1 = (unsigned char)(blockTop&0xf8);
        
        // get differential colour for subblock 2
        signed char blues = (signed char)(blue1>>3) + ((signed char) ((blockTop & 0x70000) >> 11)>>5);
        signed char greens = (signed char)(green1>>3) + ((signed char)((blockTop & 0x700) >>3)>>5);
        signed char reds = (signed char)(red1>>3) + ((signed char)((blockTop & 0x7)<<5)>>5);
        
        blue2 = (unsigned char)blues;
        green2 = (unsigned char)greens;
        red2 = (unsigned char)reds;
        
        red1 = red1 +(red1>>5);    // copy bits to lower sig
        green1 = green1 + (green1>>5);    // copy bits to lower sig
        blue1 = blue1 + (blue1>>5);    // copy bits to lower sig
        
        red2 = (red2<<3) +(red2>>2);    // copy bits to lower sig
        green2 = (green2<<3) + (green2>>2);    // copy bits to lower sig
        blue2 = (blue2<<3) + (blue2>>2);    // copy bits to lower sig
    }
    else
    {    // individual mode 4 + 4 colour bits
        // get base colour for subblock 1
        blue1 = (unsigned char)((blockTop&0xf00000)>>16);
        blue1 = blue1 +(blue1>>4);    // copy bits to lower sig
        green1 = (unsigned char)((blockTop&0xf000)>>8);
        green1 = green1 + (green1>>4);    // copy bits to lower sig
        red1 = (unsigned char)(blockTop&0xf0);
        red1 = red1 + (red1>>4);    // copy bits to lower sig
        
        // get base colour for subblock 2
        blue2 = (unsigned char)((blockTop&0xf0000)>>12);
        blue2 = blue2 +(blue2>>4);    // copy bits to lower sig
        green2 = (unsigned char)((blockTop&0xf00)>>4);
        green2 = green2 + (green2>>4);    // copy bits to lower sig
        red2 = (unsigned char)((blockTop&0xf)<<4);
        red2 = red2 + (red2>>4);    // copy bits to lower sig
    }
    // get the modtables for each subblock
    modtable1 = (blockTop>>29)&0x7; 
    modtable2 = (blockTop>>26)&0x7; 
    
    if(!bFlip)
    {   // 2 2x4 blocks side by side
        for(int j=0;j<4;j++)    // vertical
        {
            for(int k=0;k<2;k++)    // horizontal
            {
                *(output+j*4+k) = ModifyPixel(red1,green1,blue1,k,j,blockBot,modtable1);
                *(output+j*4+k+2) = ModifyPixel(red2,green2,blue2,k+2,j,blockBot,modtable2);
            }
        }
    }
    else
    {   // 2 4x2 blocks on top of each other
        for(int j=0;j<2;j++)
        {
            for(int k=0;k<4;k++)
            {
                *(output+j*4+k) = ModifyPixel(red1,green1,blue1,k,j,blockBot,modtable1);
                *(output+(j+2)*4+k) = ModifyPixel(red2,green2,blue2,k,j+2,blockBot,modtable2);
            }
        }
    }
}

void DecompressImageETC( unsigned char* rgba, const void* blocks, int width, int height )
{
    // initialise the block input
    unsigned char const* sourceBlock = reinterpret_cast< unsigned char const* >( blocks );
    int bytesPerBlock = 8;
    
    // loop over blocks
    for( int y = 0; y < height; y += 4 )
    {
        for( int x = 0; x < width; x += 4 )
        {
            // decompress the block
            unsigned char targetRgba[4*16];
            DecompressETC( targetRgba, sourceBlock );
            
            // write the decompressed pixels to the correct image locations
            unsigned char const* sourcePixel = targetRgba;
            for( int py = 0; py < 4; ++py )
            {
                for( int px = 0; px < 4; ++px )
                {
                    // get the target location
                    int sx = x + px;
                    int sy = y + py;
                    if( sx < width && sy < height )
                    {
                        unsigned char* targetPixel = rgba + 4*( width*sy + sx );
                        
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

#define PT_INDEX    (2) /*The Punch-through index*/
#define BLK_Y_SIZE  (4) /*always 4 for all 2D block types*/
#define BLK_X_MAX   (8) /*Max X dimension for blocks*/
#define BLK_X_2BPP  (8) /*dimensions for the two formats*/
#define BLK_X_4BPP  (4)

#define _MIN(X,Y) (((X)<(Y))? (X):(Y))
#define _MAX(X,Y) (((X)>(Y))? (X):(Y))
#define WRAP_COORD(Val, Size) ((Val) & ((Size)-1))
#define CLAMP(X, lower, upper) (_MIN(_MAX((X),(lower)), (upper)))
#define LIMIT_COORD(Val, Size, AssumeImageTiles) ((AssumeImageTiles)? WRAP_COORD((Val), (Size)): CLAMP((Val), 0, (Size)-1))

typedef struct
{
    // Uses 64 bits pre block
    unsigned PackedData[2];
} AMTC_BLOCK_STRUCT;

static void Unpack5554Colour(const AMTC_BLOCK_STRUCT *pBlock, int ABColours[2][4])
{
    unsigned RawBits[2];
    int i;
    
    // Extract A and B
    RawBits[0] = pBlock->PackedData[1] & (0xFFFE); /*15 bits (shifted up by one)*/
    RawBits[1] = pBlock->PackedData[1] >> 16;       /*16 bits*/
    
    // Step through both colours
    for(i = 0; i < 2; i++)
    {
        // If completely opaque
        if(RawBits[i] & (1<<15))
        {
            // Extract R and G (both 5 bit)
            ABColours[i][0] = (RawBits[i] >> 10) & 0x1F;
            ABColours[i][1] = (RawBits[i] >>  5) & 0x1F;
            
            // The precision of Blue depends on  A or B. If A then we need to
            // replicate the top bit to get 5 bits in total
            ABColours[i][2] = RawBits[i] & 0x1F;
            if(i==0)
            {
                ABColours[0][2] |= ABColours[0][2] >> 4;
            }
            
            // Set 4bit alpha fully on...
            ABColours[i][3] = 0xF;
        }
        // Else if colour has variable translucency
        else
        {
            // Extract R and G (both 4 bit).
            // (Leave a space on the end for the replication of bits
            ABColours[i][0] = (RawBits[i] >>  (8-1)) & 0x1E;
            ABColours[i][1] = (RawBits[i] >>  (4-1)) & 0x1E;
            
            // Replicate bits to truly expand to 5 bits
            ABColours[i][0] |= ABColours[i][0] >> 4;
            ABColours[i][1] |= ABColours[i][1] >> 4;
            
            // Grab the 3(+padding) or 4 bits of blue and add an extra padding bit
            ABColours[i][2] = (RawBits[i] & 0xF) << 1;
            
            // Expand from 3 to 5 bits if this is from colour A, or 4 to 5 bits if from
            // colour B
            if(i==0)
            {
                ABColours[0][2] |= ABColours[0][2] >> 3;
            }
            else
            {
                ABColours[0][2] |= ABColours[0][2] >> 4;
            }
            
            // Set the alpha bits to be 3 + a zero on the end
            ABColours[i][3] = (RawBits[i] >> 11) & 0xE;
        }
    }
}

static void UnpackModulations(const AMTC_BLOCK_STRUCT *pBlock, const int Do2bitMode, int ModulationVals[8][16], int ModulationModes[8][16], int StartX, int StartY)
{
    int BlockModMode;
    unsigned ModulationBits;
    
    int x, y;
    
    BlockModMode= pBlock->PackedData[1] & 1;
    ModulationBits    = pBlock->PackedData[0];
    
    // If it's in an interpolated mode
    if(Do2bitMode && BlockModMode)
    {
        // Run through all the pixels in the block. Note we can now treat all the
        // "stored" values as if they have 2bits (even when they didn't!)
        for(y = 0; y < BLK_Y_SIZE; y++)
        {
            for(x = 0; x < BLK_X_2BPP; x++)
            {
                ModulationModes[y+StartY][x+StartX] = BlockModMode;
                
                // If this is a stored value...
                if(((x^y)&1) == 0)
                {
                    ModulationVals[y+StartY][x+StartX] = ModulationBits & 3;
                    ModulationBits >>= 2;
                }
            }
        }
    }
    // Else if direct encoded 2bit mode - i.e. 1 mode bit per pixel
    else if(Do2bitMode)
    {
        for(y = 0; y < BLK_Y_SIZE; y++)
        {
            for(x = 0; x < BLK_X_2BPP; x++)
            {
                ModulationModes[y+StartY][x+StartX] = BlockModMode;
                
                // Double the bits so 0=> 00, and 1=>11
                if(ModulationBits & 1)
                {
                    ModulationVals[y+StartY][x+StartX] = 0x3;
                }
                else
                {
                    ModulationVals[y+StartY][x+StartX] = 0x0;
                }
                ModulationBits >>= 1;
            }
        }
    }
    // Else its the 4bpp mode so each value has 2 bits
    else
    {
        for(y = 0; y < BLK_Y_SIZE; y++)
        {
            for(x = 0; x < BLK_X_4BPP; x++)
            {
                ModulationModes[y+StartY][x+StartX] = BlockModMode;
                
                ModulationVals[y+StartY][x+StartX] = ModulationBits & 3;
                ModulationBits >>= 2;
            }
        }
    }
}

static void InterpolateColours(const int ColourP[4], const int ColourQ[4], const int ColourR[4], const int ColourS[4], const int Do2bitMode, const int x, const int y, int Result[4])
{
    int u, v, uscale;
    int k;
    int tmp1, tmp2;
    int P[4], Q[4], R[4], S[4];
    
    // Copy the colours
    for(k = 0; k < 4; k++)
    {
        P[k] = ColourP[k];
        Q[k] = ColourQ[k];
        R[k] = ColourR[k];
        S[k] = ColourS[k];
    }
    
    // Put the x and y values into the right range
    v = (y & 0x3) | ((~y & 0x2) << 1);
    if(Do2bitMode)
    {
        u = (x & 0x7) | ((~x & 0x4) << 1);
    }
    else
    {
        u = (x & 0x3) | ((~x & 0x2) << 1);
    }
    
    // Get the u and v scale amounts
    v  = v - BLK_Y_SIZE/2;
    
    if(Do2bitMode)
    {
        u = u - BLK_X_2BPP/2;
        uscale = 8;
    }
    else
    {
        u = u - BLK_X_4BPP/2;
        uscale = 4;
    }
    
    for(k = 0; k < 4; k++)
    {
        tmp1 = P[k] * uscale + u * (Q[k] - P[k]);
        tmp2 = R[k] * uscale + u * (S[k] - R[k]);
        
        tmp1 = tmp1 * 4 + v * (tmp2 - tmp1);
        
        Result[k] = tmp1;
    }
    
    // Lop off the appropriate number of bits to get us to 8 bit precision
    if(Do2bitMode)
    {
        // Do RGB
        for(k = 0; k < 3; k++)
        {
            Result[k] >>= 2;
        }
        
        Result[3] >>= 1;
    }
    else
    {
        // Do RGB  (A is ok)
        for(k = 0; k < 3; k++)
        {
            Result[k] >>= 1;
        }
    }
    
    // Convert from 5554 to 8888
    //
    // do RGB 5.3 => 8
    for(k = 0; k < 3; k++)
    {
        Result[k] += Result[k] >> 5;
    }
    Result[3] += Result[3] >> 4;
}

static void GetModulationValue(int x, int y, const int Do2bitMode, const int ModulationVals[8][16], const int ModulationModes[8][16], int *Mod, int *DoPT)
{
    static const int RepVals0[4] = {0, 3, 5, 8};
    static const int RepVals1[4] = {0, 4, 4, 8};
    
    int ModVal;
    
    // Map X and Y into the local 2x2 block
    y = (y & 0x3) | ((~y & 0x2) << 1);
    if(Do2bitMode)
    {
        x = (x & 0x7) | ((~x & 0x4) << 1);
    }
    else
    {
        x = (x & 0x3) | ((~x & 0x2) << 1);
    }
    
    // Assume no PT for now
    *DoPT = 0;
    
    // Extract the modulation value. If a simple encoding
    if(ModulationModes[y][x]==0)
    {
        ModVal = RepVals0[ModulationVals[y][x]];
    }
    else if(Do2bitMode)
    {
        // If this is a stored value
        if(((x^y)&1)==0)
        {
            ModVal = RepVals0[ModulationVals[y][x]];
        }
        // Else average from the neighbours
        //
        // If H&V interpolation...
        else if(ModulationModes[y][x] == 1)
        {
            ModVal = (RepVals0[ModulationVals[y-1][x]] +
                      RepVals0[ModulationVals[y+1][x]] +
                      RepVals0[ModulationVals[y][x-1]] +
                      RepVals0[ModulationVals[y][x+1]] + 2) / 4;
        }
        // Else if H-Only
        else if(ModulationModes[y][x] == 2)
        {
            ModVal = (RepVals0[ModulationVals[y][x-1]] +
                      RepVals0[ModulationVals[y][x+1]] + 1) / 2;
        }
        // Else it's V-Only
        else
        {
            ModVal = (RepVals0[ModulationVals[y-1][x]] +
                      RepVals0[ModulationVals[y+1][x]] + 1) / 2;
        }
    }
    // Else it's 4BPP and PT encoding
    else
    {
        ModVal = RepVals1[ModulationVals[y][x]];
        
        *DoPT = ModulationVals[y][x] == PT_INDEX;
    }
    
    *Mod = ModVal;
}

static unsigned TwiddleUV(unsigned YSize, unsigned XSize, unsigned YPos, unsigned XPos)
{
    unsigned Twiddled;
    unsigned MinDimension;
    unsigned MaxValue;
    unsigned SrcBitPos;
    unsigned DstBitPos;
    int ShiftCount;
    
    if (YSize < XSize)
    {
        MinDimension = YSize;
        MaxValue     = XPos;
    }
    else
    {
        MinDimension = XSize;
        MaxValue     = YPos;
    }
    
    // Step through all the bits in the "minimum" dimension
    SrcBitPos = 1;
    DstBitPos = 1;
    Twiddled  = 0;
    ShiftCount = 0;
    
    while(SrcBitPos < MinDimension)
    {
        if(YPos & SrcBitPos)
        {
            Twiddled |= DstBitPos;
        }
        
        if(XPos & SrcBitPos)
        {
            Twiddled |= (DstBitPos << 1);
        }
        
        SrcBitPos <<= 1;
        DstBitPos <<= 2;
        ShiftCount += 1;
        
    }
    
    // Prepend any unused bits
    MaxValue >>= ShiftCount;
    
    Twiddled |=  (MaxValue << (2*ShiftCount));
    
    return Twiddled;
}

void DecompressImagePVRTC(unsigned char* dest, const void *blocks, int width, int height, CompressedFormat format)
{
    AMTC_BLOCK_STRUCT* pCompressedData = (AMTC_BLOCK_STRUCT*)blocks;
    int AssumeImageTiles = 1;
    int Do2bitMode = format == CF_PVRTC_RGB_2BPP || format == CF_PVRTC_RGBA_2BPP;
    
    int x, y;
    int i, j;
    
    int BlkX, BlkY;
    int BlkXp1, BlkYp1;
    int XBlockSize;
    int BlkXDim, BlkYDim;
    
    int StartX, StartY;
    
    int ModulationVals[8][16];
    int ModulationModes[8][16];
    
    int Mod, DoPT;
    
    unsigned uPosition;
    
    // Local neighbourhood of blocks
    AMTC_BLOCK_STRUCT *pBlocks[2][2];
    
    AMTC_BLOCK_STRUCT *pPrevious[2][2] = {{NULL, NULL}, {NULL, NULL}};
    
    // Low precision colours extracted from the blocks
    struct
    {
        int Reps[2][4];
    } Colours5554[2][2];
    
    // Interpolated A and B colours for the pixel
    int ASig[4], BSig[4];
    int Result[4];
    
    if(Do2bitMode)
    {
        XBlockSize = BLK_X_2BPP;
    }
    else
    {
        XBlockSize = BLK_X_4BPP;
    }
    
    // For MBX don't allow the sizes to get too small
    BlkXDim = _MAX(2, width / XBlockSize);
    BlkYDim = _MAX(2, height / BLK_Y_SIZE);
    
    // Step through the pixels of the image decompressing each one in turn
    //
    // Note that this is a hideously inefficient way to do this!
    for(y = 0; y < height; y++)
    {
        for(x = 0; x < width; x++)
        {
            // Map this pixel to the top left neighbourhood of blocks
            BlkX = (x - XBlockSize/2);
            BlkY = (y - BLK_Y_SIZE/2);
            
            BlkX = LIMIT_COORD(BlkX, width, AssumeImageTiles);
            BlkY = LIMIT_COORD(BlkY, height, AssumeImageTiles);
            
            BlkX /= XBlockSize;
            BlkY /= BLK_Y_SIZE;
            
            // Compute the positions of the other 3 blocks
            BlkXp1 = LIMIT_COORD(BlkX+1, BlkXDim, AssumeImageTiles);
            BlkYp1 = LIMIT_COORD(BlkY+1, BlkYDim, AssumeImageTiles);
            
            // Map to block memory locations
            pBlocks[0][0] = pCompressedData + TwiddleUV(BlkYDim, BlkXDim, BlkY, BlkX);
            pBlocks[0][1] = pCompressedData + TwiddleUV(BlkYDim, BlkXDim, BlkY, BlkXp1);
            pBlocks[1][0] = pCompressedData + TwiddleUV(BlkYDim, BlkXDim, BlkYp1, BlkX);
            pBlocks[1][1] = pCompressedData + TwiddleUV(BlkYDim, BlkXDim, BlkYp1, BlkXp1);
            
            // Extract the colours and the modulation information IF the previous values
            // have changed.
            if(memcmp(pPrevious, pBlocks, 4*sizeof(void*)) != 0)
            {
                StartY = 0;
                for(i = 0; i < 2; i++)
                {
                    StartX = 0;
                    for(j = 0; j < 2; j++)
                    {
                        Unpack5554Colour(pBlocks[i][j], Colours5554[i][j].Reps);
                        
                        UnpackModulations(pBlocks[i][j],
                                          Do2bitMode,
                                          ModulationVals,
                                          ModulationModes,
                                          StartX, StartY);
                        
                        StartX += XBlockSize;
                    }
                    
                    StartY += BLK_Y_SIZE;
                }
                
                // Make a copy of the new pointers
                memcpy(pPrevious, pBlocks, 4*sizeof(void*));
            }
            
            // Decompress the pixel.  First compute the interpolated A and B signals
            InterpolateColours(Colours5554[0][0].Reps[0],
                               Colours5554[0][1].Reps[0],
                               Colours5554[1][0].Reps[0],
                               Colours5554[1][1].Reps[0],
                               Do2bitMode, x, y,
                               ASig);
            
            InterpolateColours(Colours5554[0][0].Reps[1],
                               Colours5554[0][1].Reps[1],
                               Colours5554[1][0].Reps[1],
                               Colours5554[1][1].Reps[1],
                               Do2bitMode, x, y,
                               BSig);
            
            GetModulationValue(x,y, Do2bitMode, (const int (*)[16])ModulationVals, (const int (*)[16])ModulationModes,
                               &Mod, &DoPT);
            
            // Compute the modulated colour
            for(i = 0; i < 4; i++)
            {
                Result[i] = ASig[i] * 8 + Mod * (BSig[i] - ASig[i]);
                Result[i] >>= 3;
            }
            if(DoPT)
            {
                Result[3] = 0;
            }
            
            // Store the result in the output image
            uPosition = (x+y*width)<<2;
            dest[uPosition+0] = (unsigned char)Result[0];
            dest[uPosition+1] = (unsigned char)Result[1];
            dest[uPosition+2] = (unsigned char)Result[2];
            dest[uPosition+3] = (unsigned char)Result[3];
        }
    }
}

void FlipBlockVertical(unsigned char* dest, unsigned char* src, CompressedFormat format)
{
    switch (format)
    {
    case CF_RGBA:
        for (unsigned i = 0; i < 4; ++i)
            dest[i] = src[i];
        break;
        
    case CF_DXT1:
        for (unsigned i = 0; i < 4; ++i)
        {
            dest[i] = src[i];
            dest[i + 4] = src[7 - i];
        }
        break;
        
    case CF_DXT3:
        for (unsigned i = 0; i < 8; i += 2)
        {
            dest[i] = src[6 - i];
            dest[i + 1] = src[6 - i + 1];
        }
        for (unsigned i = 0; i < 4; ++i)
        {
            dest[i + 8] = src[i + 8];
            dest[i + 12] = src[15 - i];
        }
        break;
        
    case CF_DXT5:
        dest[0] = src[0];
        dest[1] = src[1];
        {
            unsigned a1 = src[2] | ((unsigned)src[3] << 8) | ((unsigned)src[4] << 16);
            unsigned a2 = src[5] | ((unsigned)src[6] << 8) | ((unsigned)src[7] << 16);
            unsigned b1 = ((a1 & 0x000fff) << 12) | (a1 & 0xfff000) >> 12;
            unsigned b2 = ((a2 & 0x000fff) << 12) | (a2 & 0xfff000) >> 12;
            dest[2] = b2 & 0xff;
            dest[3] = (b2 >> 8) & 0xff;
            dest[4] = (b2 >> 16) & 0xff;
            dest[5] = b1 & 0xff;
            dest[6] = (b1 >> 8) & 0xff;
            dest[7] = (b1 >> 16) & 0xff;
        }
        for (unsigned i = 0; i < 4; ++i)
        {
            dest[i + 8] = src[i + 8];
            dest[i + 12] = src[15 - i];
        }
        break;
        
    default:
        /// ETC1 & PVRTC not yet implemented
        break;
    }
}

static unsigned char FlipDXT1Horizontal(unsigned char src)
{
    return ((src & 0x3) << 6) | ((src & 0xc) << 2) | ((src & 0x30) >> 2) | ((src & 0xc0) >> 6);
}

static unsigned FlipDXT5AlphaHorizontal(unsigned src)
{
    // Works on 2 lines at a time
    return ((src & 0x7) << 9) | ((src & 0x38) << 3) | ((src & 0x1c0) >> 3) | ((src & 0xe00) >> 9) |
        ((src & 0x7000) << 9) | ((src & 0x38000) << 3) | ((src & 0x1c0000) >> 3) | ((src & 0xe00000) >> 9);
}

void FlipBlockHorizontal(unsigned char* dest, unsigned char* src, CompressedFormat format)
{
    switch (format)
    {
    case CF_DXT1:
        for (unsigned i = 0; i < 4; ++i)
        {
            dest[i] = src[i];
            dest[i + 4] = FlipDXT1Horizontal(src[i + 4]);
        }
        break;
        
    case CF_DXT3:
        for (unsigned i = 0; i < 8; i += 2)
        {
            dest[i] = ((src[i+1] & 0xf0) >> 4) | ((src[i+1] & 0xf) << 4);
            dest[i+1] = ((src[i] & 0xf0) >> 4) | ((src[i] & 0xf) << 4);
        }
        for (unsigned i = 0; i < 4; ++i)
        {
            dest[i + 8] = src[i + 8];
            dest[i + 12] = FlipDXT1Horizontal(src[i + 12]);
        }
        break;
        
    case CF_DXT5:
        dest[0] = src[0];
        dest[1] = src[1];
        {
            unsigned a1 = src[2] | ((unsigned)src[3] << 8) | ((unsigned)src[4] << 16);
            unsigned a2 = src[5] | ((unsigned)src[6] << 8) | ((unsigned)src[7] << 16);
            unsigned b1 = FlipDXT5AlphaHorizontal(a1);
            unsigned b2 = FlipDXT5AlphaHorizontal(a2);
            dest[2] = b1 & 0xff;
            dest[3] = (b1 >> 8) & 0xff;
            dest[4] = (b1 >> 16) & 0xff;
            dest[5] = b2 & 0xff;
            dest[6] = (b2 >> 8) & 0xff;
            dest[7] = (b2 >> 16) & 0xff;
        }
        for (unsigned i = 0; i < 4; ++i)
        {
            dest[i + 8] = src[i + 8];
            dest[i + 12] = FlipDXT1Horizontal(src[i + 12]);
        }
        break;
        
    default:
        /// ETC1 & PVRTC not yet implemented
        break;
    }
}

}
