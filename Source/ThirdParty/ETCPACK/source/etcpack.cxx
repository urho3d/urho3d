//// etcpack v2.74
//// 
//// NO WARRANTY 
//// 
//// BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE THE PROGRAM IS PROVIDED
//// "AS IS". ERICSSON MAKES NO REPRESENTATIONS OF ANY KIND, EXTENDS NO
//// WARRANTIES OR CONDITIONS OF ANY KIND; EITHER EXPRESS, IMPLIED OR
//// STATUTORY; INCLUDING, BUT NOT LIMITED TO, EXPRESS, IMPLIED OR
//// STATUTORY WARRANTIES OR CONDITIONS OF TITLE, MERCHANTABILITY,
//// SATISFACTORY QUALITY, SUITABILITY AND FITNESS FOR A PARTICULAR
//// PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
//// PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME
//// THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION. ERICSSON
//// MAKES NO WARRANTY THAT THE MANUFACTURE, SALE, OFFERING FOR SALE,
//// DISTRIBUTION, LEASE, USE OR IMPORTATION UNDER THE LICENSE WILL BE FREE
//// FROM INFRINGEMENT OF PATENTS, COPYRIGHTS OR OTHER INTELLECTUAL
//// PROPERTY RIGHTS OF OTHERS, AND THE VALIDITY OF THE LICENSE IS SUBJECT
//// TO YOUR SOLE RESPONSIBILITY TO MAKE SUCH DETERMINATION AND ACQUIRE
//// SUCH LICENSES AS MAY BE NECESSARY WITH RESPECT TO PATENTS, COPYRIGHT
//// AND OTHER INTELLECTUAL PROPERTY OF THIRD PARTIES.
//// 
//// FOR THE AVOIDANCE OF DOUBT THE PROGRAM (I) IS NOT LICENSED FOR; (II)
//// IS NOT DESIGNED FOR OR INTENDED FOR; AND (III) MAY NOT BE USED FOR;
//// ANY MISSION CRITICAL APPLICATIONS SUCH AS, BUT NOT LIMITED TO
//// OPERATION OF NUCLEAR OR HEALTHCARE COMPUTER SYSTEMS AND/OR NETWORKS,
//// AIRCRAFT OR TRAIN CONTROL AND/OR COMMUNICATION SYSTEMS OR ANY OTHER
//// COMPUTER SYSTEMS AND/OR NETWORKS OR CONTROL AND/OR COMMUNICATION
//// SYSTEMS ALL IN WHICH CASE THE FAILURE OF THE PROGRAM COULD LEAD TO
//// DEATH, PERSONAL INJURY, OR SEVERE PHYSICAL, MATERIAL OR ENVIRONMENTAL
//// DAMAGE. YOUR RIGHTS UNDER THIS LICENSE WILL TERMINATE AUTOMATICALLY
//// AND IMMEDIATELY WITHOUT NOTICE IF YOU FAIL TO COMPLY WITH THIS
//// PARAGRAPH.
//// 
//// IN NO EVENT WILL ERICSSON, BE LIABLE FOR ANY DAMAGES WHATSOEVER,
//// INCLUDING BUT NOT LIMITED TO PERSONAL INJURY, ANY GENERAL, SPECIAL,
//// INDIRECT, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF OR IN
//// CONNECTION WITH THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT
//// NOT LIMITED TO LOSS OF PROFITS, BUSINESS INTERUPTIONS, OR ANY OTHER
//// COMMERCIAL DAMAGES OR LOSSES, LOSS OF DATA OR DATA BEING RENDERED
//// INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A FAILURE OF
//// THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS) REGARDLESS OF THE
//// THEORY OF LIABILITY (CONTRACT, TORT OR OTHERWISE), EVEN IF SUCH HOLDER
//// OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//// 
//// (C) Ericsson AB 2005-2013. All Rights Reserved.
//// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <time.h>
#include <sys/timeb.h>
#include "image.h"

// Typedefs
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef short int16;

// Functions needed for decrompession ---- in etcdec.cxx
void read_big_endian_2byte_word(unsigned short *blockadr, FILE *f);
void read_big_endian_4byte_word(unsigned int *blockadr, FILE *f);
void unstuff57bits(unsigned int planar_word1, unsigned int planar_word2, unsigned int &planar57_word1, unsigned int &planar57_word2);
void unstuff59bits(unsigned int thumbT_word1, unsigned int thumbT_word2, unsigned int &thumbT59_word1, unsigned int &thumbT59_word2);
void unstuff58bits(unsigned int thumbH_word1, unsigned int thumbH_word2, unsigned int &thumbH58_word1, unsigned int &thumbH58_word2);
void decompressColor(int R_B, int G_B, int B_B, uint8 (colors_RGB444)[2][3], uint8 (colors)[2][3]);
void calculatePaintColors59T(uint8 d, uint8 p, uint8 (colors)[2][3], uint8 (possible_colors)[4][3]);
void calculatePaintColors58H(uint8 d, uint8 p, uint8 (colors)[2][3], uint8 (possible_colors)[4][3]);
void decompressBlockTHUMB59T(unsigned int block_part1, unsigned int block_part2, uint8 *img,int width,int height,int startx,int starty);
void decompressBlockTHUMB58H(unsigned int block_part1, unsigned int block_part2, uint8 *img,int width,int height,int startx,int starty);
void decompressBlockPlanar57(unsigned int compressed57_1, unsigned int compressed57_2, uint8 *img,int width,int height,int startx,int starty);
void decompressBlockDiffFlip(unsigned int block_part1, unsigned int block_part2, uint8 *img,int width,int height,int startx,int starty);
void decompressBlockETC2(unsigned int block_part1, unsigned int block_part2, uint8 *img,int width,int height,int startx,int starty);
void decompressBlockDifferentialWithAlpha(unsigned int block_part1,unsigned int block_part2, uint8* img, uint8* alpha, int width, int height, int startx, int starty);
void decompressBlockETC21BitAlpha(unsigned int block_part1, unsigned int block_part2, uint8 *img, uint8* alphaimg, int width,int height,int startx,int starty);
void decompressBlockTHUMB58HAlpha(unsigned int block_part1, unsigned int block_part2, uint8 *img, uint8* alpha,int width,int height,int startx,int starty);
void decompressBlockTHUMB59TAlpha(unsigned int block_part1, unsigned int block_part2, uint8 *img, uint8* alpha,int width,int height,int startx,int starty);
uint8 getbit(uint8 input, int frompos, int topos);
int clamp(int val);
void decompressBlockAlpha(uint8* data,uint8* img,int width,int height,int ix,int iy);
uint16 get16bits11bits(int base, int table, int mul, int index);
void decompressBlockAlpha16bit(uint8* data,uint8* img,int width,int height,int ix,int iy); 
int16 get16bits11signed(int base, int table, int mul, int index);
void setupAlphaTable();


// This source code is quite long. You can make it shorter by not including the
// code doing the exhaustive code. Then the -slow modes will not work, but the
// code will be approximately half the number of lines of code.
// Then the lines between "exhaustive code starts here" and "exhaustive code ends here"
// can then be removed.
#define EXHAUSTIVE_CODE_ACTIVE 1

// Remove warnings for unsafe functions such as strcpy
#pragma warning(disable : 4996)
// Remove warnings for conversions between different time variables
#pragma warning(disable : 4244)
// Remove warnings for negative or too big shifts
//#pragma warning(disable : 4293)
 
#define CLAMP(ll,x,ul) (((x)<(ll)) ? (ll) : (((x)>(ul)) ? (ul) : (x)))
// The below code works as CLAMP(0, x, 255) if x < 255
#define CLAMP_LEFT_ZERO(x) ((~(((int)(x))>>31))&(x))
// The below code works as CLAMP(0, x, 255) if x is in [0,511]
#define CLAMP_RIGHT_255(x) (((( ((((int)(x))<<23)>>31)  ))|(x))&0x000000ff)   

#define SQUARE(x) ((x)*(x))
#define JAS_ROUND(x) (((x) < 0.0 ) ? ((int)((x)-0.5)) : ((int)((x)+0.5)))
#define JAS_MIN(a,b) ((a) < (b) ? (a) : (b))
#define JAS_MAX(a,b) ((a) > (b) ? (a) : (b))

// The error metric Wr Wg Wb should be definied so that Wr^2 + Wg^2 + Wb^2 = 1.
// Hence it is easier to first define the squared values and derive the weights
// as their square-roots.

#define PERCEPTUAL_WEIGHT_R_SQUARED 0.299
#define PERCEPTUAL_WEIGHT_G_SQUARED 0.587
#define PERCEPTUAL_WEIGHT_B_SQUARED 0.114

#define PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000 299
#define PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000 587
#define PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000 114

#define RED(img,width,x,y)   img[3*(y*width+x)+0]
#define GREEN(img,width,x,y) img[3*(y*width+x)+1]
#define BLUE(img,width,x,y)  img[3*(y*width+x)+2]

#define SHIFT(size,startpos) ((startpos)-(size)+1)
#define MASK(size, startpos) (((2<<(size-1))-1) << SHIFT(size,startpos))
#define PUTBITS( dest, data, size, startpos) dest = ((dest & ~MASK(size, startpos)) | ((data << SHIFT(size, startpos)) & MASK(size,startpos)))
#define SHIFTHIGH(size, startpos) (((startpos)-32)-(size)+1)
#define MASKHIGH(size, startpos) (((1<<(size))-1) << SHIFTHIGH(size,startpos))
#define PUTBITSHIGH(dest, data, size, startpos) dest = ((dest & ~MASKHIGH(size, startpos)) | ((data << SHIFTHIGH(size, startpos)) & MASKHIGH(size,startpos)))
#define GETBITS(source, size, startpos)  (( (source) >> ((startpos)-(size)+1) ) & ((1<<(size)) -1))
#define GETBITSHIGH(source, size, startpos)  (( (source) >> (((startpos)-32)-(size)+1) ) & ((1<<(size)) -1))

// Thumb macros and definitions
#define	R_BITS59T 4
#define G_BITS59T 4
#define	B_BITS59T 4
#define	R_BITS58H 4
#define G_BITS58H 4
#define	B_BITS58H 4
#define	MAXIMUM_ERROR (255*255*16*1000)
#define R 0
#define G 1
#define B 2
#define BLOCKHEIGHT 4
#define BLOCKWIDTH 4
#define BINPOW(power) (1<<(power))
//#define RADIUS 2
#define	TABLE_BITS_59T 3
#define	TABLE_BITS_58H 3

// Global tables
static uint8 table59T[8] = {3,6,11,16,23,32,41,64};  // 3-bit table for the 59 bit T-mode
static uint8 table58H[8] = {3,6,11,16,23,32,41,64};  // 3-bit table for the 58 bit H-mode
uint8 weight[3] = {1,1,1};			// Color weight

// Enums
static enum{PATTERN_H = 0, 
			PATTERN_T = 1};

static enum{MODE_ETC1, MODE_THUMB_T, MODE_THUMB_H, MODE_PLANAR};
// The ETC2 package of codecs includes the following codecs:
//
// codec                                             enum
// --------------------------------------------------------
// GL_COMPRESSED_R11_EAC                            0x9270
// GL_COMPRESSED_SIGNED_R11_EAC                     0x9271
// GL_COMPRESSED_RG11_EAC                           0x9272
// GL_COMPRESSED_SIGNED_RG11_EAC                    0x9273
// GL_COMPRESSED_RGB8_ETC2                          0x9274
// GL_COMPRESSED_SRGB8_ETC2                         0x9275
// GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2      0x9276
// GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2     0x9277
// GL_COMPRESSED_RGBA8_ETC2_EAC                     0x9278
// GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC              0x9279
// 
// The older codec ETC1 is not included in the package 
// GL_ETC1_RGB8_OES                                 0x8d64
// but since ETC2 is backwards compatible an ETC1 texture can
// be decoded using the RGB8_ETC2 enum (0x9274)
// 
// In a PKM-file, the codecs are stored using the following identifiers
// 
// identifier                         value               codec
// --------------------------------------------------------------------
// ETC1_RGB_NO_MIPMAPS                  0                 GL_ETC1_RGB8_OES
// ETC2PACKAGE_RGB_NO_MIPMAPS           1                 GL_COMPRESSED_RGB8_ETC2
// ETC2PACKAGE_RGBA_NO_MIPMAPS_OLD      2, not used       -
// ETC2PACKAGE_RGBA_NO_MIPMAPS          3                 GL_COMPRESSED_RGBA8_ETC2_EAC
// ETC2PACKAGE_RGBA1_NO_MIPMAPS         4                 GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2
// ETC2PACKAGE_R_NO_MIPMAPS             5                 GL_COMPRESSED_R11_EAC
// ETC2PACKAGE_RG_NO_MIPMAPS            6                 GL_COMPRESSED_RG11_EAC
// ETC2PACKAGE_R_SIGNED_NO_MIPMAPS      7                 GL_COMPRESSED_SIGNED_R11_EAC
// ETC2PACKAGE_RG_SIGNED_NO_MIPMAPS     8                 GL_COMPRESSED_SIGNED_RG11_EAC
//
// In the code, the identifiers are not always used strictly. For instance, the
// identifier ETC2PACKAGE_R_NO_MIPMAPS is sometimes used for both the unsigned
// (GL_COMPRESSED_R11_EAC) and signed (GL_COMPRESSED_SIGNED_R11_EAC) version of 
// the codec.
// 
static enum{ETC1_RGB_NO_MIPMAPS,ETC2PACKAGE_RGB_NO_MIPMAPS,ETC2PACKAGE_RGBA_NO_MIPMAPS_OLD,ETC2PACKAGE_RGBA_NO_MIPMAPS,ETC2PACKAGE_RGBA1_NO_MIPMAPS,ETC2PACKAGE_R_NO_MIPMAPS,ETC2PACKAGE_RG_NO_MIPMAPS,ETC2PACKAGE_R_SIGNED_NO_MIPMAPS,ETC2PACKAGE_RG_SIGNED_NO_MIPMAPS,ETC2PACKAGE_sRGB_NO_MIPMAPS,ETC2PACKAGE_sRGBA_NO_MIPMAPS,ETC2PACKAGE_sRGBA1_NO_MIPMAPS};
static enum {MODE_COMPRESS, MODE_UNCOMPRESS, MODE_PSNR};
static enum {SPEED_SLOW, SPEED_FAST, SPEED_MEDIUM};
static enum {METRIC_PERCEPTUAL, METRIC_NONPERCEPTUAL};
static enum {CODEC_ETC, CODEC_ETC2};

int mode = MODE_COMPRESS;
int speed = SPEED_FAST;
int metric = METRIC_PERCEPTUAL;
int codec = CODEC_ETC2;
int format = ETC2PACKAGE_RGB_NO_MIPMAPS;
int verbose = true;
extern int formatSigned;
int ktxFile=0;
bool first_time_message = true;

static int scramble[4] = {3, 2, 0, 1};
static int unscramble[4] = {2, 3, 1, 0};

typedef struct KTX_header_t
{
	uint8  identifier[12];
	unsigned int endianness;
	unsigned int glType;
	unsigned int glTypeSize;
	unsigned int glFormat;
	unsigned int glInternalFormat;
	unsigned int glBaseInternalFormat;
	unsigned int pixelWidth;
	unsigned int pixelHeight;
	unsigned int pixelDepth;
	unsigned int numberOfArrayElements;
	unsigned int numberOfFaces;
	unsigned int numberOfMipmapLevels;
	unsigned int bytesOfKeyValueData;
} 
KTX_header;
#define KTX_IDENTIFIER_REF  { 0xAB, 0x4B, 0x54, 0x58, 0x20, 0x31, 0x31, 0xBB, 0x0D, 0x0A, 0x1A, 0x0A }

#define KTX_ENDIAN_REF      (0x04030201)
#define KTX_ENDIAN_REF_REV  (0x01020304)

static enum {GL_R=0x1903,GL_RG=0x8227,GL_RGB=0x1907,GL_RGBA=0x1908};
#define GL_SRGB                                          0x8C40
#define GL_SRGB8                                         0x8C41
#define GL_SRGB8_ALPHA8                                  0x8C43
#define GL_ETC1_RGB8_OES                                 0x8d64
#define GL_COMPRESSED_R11_EAC                            0x9270
#define GL_COMPRESSED_SIGNED_R11_EAC                     0x9271
#define GL_COMPRESSED_RG11_EAC                           0x9272
#define GL_COMPRESSED_SIGNED_RG11_EAC                    0x9273
#define GL_COMPRESSED_RGB8_ETC2                          0x9274
#define GL_COMPRESSED_SRGB8_ETC2                         0x9275
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2      0x9276
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2     0x9277
#define GL_COMPRESSED_RGBA8_ETC2_EAC                     0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC              0x9279


int ktx_identifier[] = KTX_IDENTIFIER_REF;


//converts indices from  |a0|a1|e0|e1|i0|i1|m0|m1|b0|b1|f0|f1|j0|j1|n0|n1|c0|c1|g0|g1|k0|k1|o0|o1|d0|d1|h0|h1|l0|l1|p0|p1| previously used by T- and H-modes 
//				         into  |p0|o0|n0|m0|l0|k0|j0|i0|h0|g0|f0|e0|d0|c0|b0|a0|p1|o1|n1|m1|l1|k1|j1|i1|h1|g1|f1|e1|d1|c1|b1|a1| which should be used for all modes.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
int indexConversion(int pixelIndices) 
{
	int correctIndices = 0;
	int LSB[4][4];
	int MSB[4][4];
	int shift=0;
	for(int y=3; y>=0; y--) 
	{
		for(int x=3; x>=0; x--) 
		{
			LSB[x][y] = (pixelIndices>>shift)&1;
			shift++;
			MSB[x][y] = (pixelIndices>>shift)&1;
			shift++;
		}
	}
	shift=0;
	for(int x=0; x<4; x++) 
	{
		for(int y=0; y<4; y++) 
		{
			correctIndices|=(LSB[x][y]<<shift);
			correctIndices|=(MSB[x][y]<<(16+shift));
			shift++;
		}
	}
	return correctIndices;
}

// Tests if a file exists.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
bool fileExist(char *filename)
{
	FILE *f=NULL;
	if((f=fopen(filename,"rb"))!=NULL)
	{
		fclose(f);
		return true;
	}
	return false;
}

// Expand source image so that it is divisible by a factor of four in the x-dimension.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
bool expandToWidthDivByFour(uint8 *&img, int width, int height, int &expandedwidth, int &expandedheight, int bitrate)
{
	int wdiv4;
	int xx, yy;
	uint8 *newimg;

	wdiv4 = width /4;
	if( !(wdiv4 *4 == width) )
	{
     	expandedwidth = (wdiv4 + 1)*4;
		expandedheight = height;
	    newimg=(uint8*) malloc(3*expandedwidth*expandedheight*bitrate/8);
		if(!newimg)
		{
			printf("Could not allocate memory to expand width\n");
			return false;
		}

		// First copy image
		for(yy = 0; yy<height; yy++)
		{
			for(xx = 0; xx < width; xx++)
			{
				//we have 3*bitrate/8 bytes for each pixel..
				for(int i=0; i<3*bitrate/8; i++) 
				{
					newimg[(yy * expandedwidth+ xx)*3*bitrate/8 + i] = img[(yy * width+xx)*3*bitrate/8 + i];

				}
			}
		}

		// Then make the last column of pixels the same as the previous column.

		for(yy = 0; yy< height; yy++)
		{
			for(xx = width; xx < expandedwidth; xx++)
			{
				for(int i=0; i<3*bitrate/8; i++) 
				{
					newimg[(yy * expandedwidth+xx)*3*bitrate/8 + i] = img[(yy * width+(width-1))*3*bitrate/8 + i];
				}
			}
		}

		// Now free the old image
		free(img);

		// Use the new image
		img = newimg;

		return true;
	}
	else
	{
		printf("Image already of even width\n");
		expandedwidth = width;
		expandedheight = height;
		return false;
	}
}

// Expand source image so that it is divisible by a factor of four in the y-dimension.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
bool expandToHeightDivByFour(uint8 *&img, int width, int height, int &expandedwidth, int &expandedheight, int bitrate)
{
	int hdiv4;
	int xx, yy;
	int numlinesmissing;
	uint8 *newimg;

	hdiv4 = height/4;

	if( !(hdiv4 * 4 == height) )
	{
		expandedwidth = width;
		expandedheight = (hdiv4 + 1) * 4;
		numlinesmissing = expandedheight - height;
		newimg=(uint8*)malloc(3*expandedwidth*expandedheight*bitrate/8);
		if(!newimg)
		{
			printf("Could not allocate memory to expand height\n");
			return false;
		}
		
		// First copy image. No need to reformat data.

		for(xx = 0; xx<3*width*height*bitrate/8; xx++)
			newimg[xx] = img[xx];

		// Then copy up to three lines.

		for(yy = height; yy < height + numlinesmissing; yy++)
		{
			for(xx = 0; xx<width; xx++)
			{
				for(int i=0; i<3*bitrate/8; i++) 
				{
					newimg[(yy*width+xx)*3*bitrate/8 + i] = img[((height-1)*width+xx)*3*bitrate/8 + i];
				}
			}
		}

		// Now free the old image;
		free(img);

		// Use the new image:
		img = newimg;

		return true;

	}
	else
	{
		printf("Image height already divisible by four.\n");
		expandedwidth = width;
		expandedheight = height;
		return true;
	}
}

// Find the position of a file extension such as .ppm or .pkm
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
int find_pos_of_extension(char *src)
{
	int q=strlen(src);
	while(q>=0)		// find file name extension
	{
		if(src[q]=='.') break;
		q--;
	}
	if(q<0) 
		return -1;
	else
		return q;
}

// Read source file. Does conversion if file format is not .ppm.
// Will expand file to be divisible by four in the x- and y- dimension.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
bool readSrcFile(char *filename,uint8 *&img,int &width,int &height, int &expandedwidth, int &expandedheight)
{
	int w1,h1;
	int wdiv4, hdiv4;
	char str[255];


	// Delete temp file if it exists.
	if(fileExist("tmp.ppm"))
	{
		sprintf(str, "del tmp.ppm\n");
		system(str);
	}

	int q = find_pos_of_extension(filename);
	if(!strcmp(&filename[q],".ppm")) 
	{
		// Already a .ppm file. Just copy. 
		sprintf(str,"copy %s tmp.ppm \n", filename);
		printf("Copying source file to tmp.ppm\n", filename);
	}
	else
	{
		// Converting from other format to .ppm 
		// 
		// Use your favorite command line image converter program,
		// for instance Image Magick. Just make sure the syntax can
		// be written as below:
		// 
		// C:\magick convert source.jpg dest.ppm
		//
		sprintf(str,"magick convert %s tmp.ppm\n", filename);
		printf("Converting source file from %s to .ppm\n", filename);
	}
	// Execute system call
	system(str);

	int bitrate=8;
	if(format==ETC2PACKAGE_RG_NO_MIPMAPS)
		bitrate=16;
	if(fReadPPM("tmp.ppm",w1,h1,img,bitrate))
	{
		width=w1;
		height=h1;
		system("del tmp.ppm");

		// Width must be divisible by 4 and height must be
		// divisible by 4. Otherwise, we will expand the image

		wdiv4 = width / 4;
		hdiv4 = height / 4;

		expandedwidth = width;
		expandedheight = height;

		if( !(wdiv4 * 4 == width) )
		{
			printf(" Width = %d is not divisible by four... ", width);
			printf(" expanding image in x-dir... ");
			if(expandToWidthDivByFour(img, width, height, expandedwidth, expandedheight,bitrate))
			{
				printf("OK.\n");
			}
			else
			{
				printf("\n Error: could not expand image\n");
				return false;
			}
		}
		if( !(hdiv4 * 4 == height))
		{
			printf(" Height = %d is not divisible by four... ", height);
			printf(" expanding image in y-dir...");
			if(expandToHeightDivByFour(img, expandedwidth, height, expandedwidth, expandedheight,bitrate))
			{
				printf("OK.\n");
			}
			else
			{
				printf("\n Error: could not expand image\n");
				return false;
			}
		}
		if(!(expandedwidth == width && expandedheight == height))
		   printf("Active pixels: %dx%d. Expanded image: %dx%d\n",width,height,expandedwidth,expandedheight);
		return true;
	}
	else
	{
		printf("Could not read tmp.ppm file\n");
		exit(1);	
	}
	return false;

}

// Reads a file without expanding it to be divisible by 4.
// Is used when doing PSNR calculation between two files.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
bool readSrcFileNoExpand(char *filename,uint8 *&img,int &width,int &height)
{
	int w1,h1;
	char str[255];


	// Delete temp file if it exists.
	if(fileExist("tmp.ppm"))
	{
		sprintf(str, "del tmp.ppm\n");
		system(str);
	}


	int q = find_pos_of_extension(filename);
	if(!strcmp(&filename[q],".ppm")) 
	{
		// Already a .ppm file. Just copy. 
		sprintf(str,"copy %s tmp.ppm \n", filename);
		printf("Copying source file to tmp.ppm\n", filename);
	}
	else
	{
		// Converting from other format to .ppm 
		// 
		// Use your favorite command line image converter program,
		// for instance Image Magick. Just make sure the syntax can
		// be written as below:
		// 
		// C:\magick convert source.jpg dest.ppm
		//
		sprintf(str,"magick convert %s tmp.ppm\n", filename);
//		printf("Converting source file from %s to .ppm\n", filename);
	}
	// Execute system call
	system(str);

	if(fReadPPM("tmp.ppm",w1,h1,img,8))
	{
		width=w1;
		height=h1;
		system("del tmp.ppm");

		return true;
	}
	return false;
}

// Parses the arguments from the command line.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void readArguments(int argc,char *argv[],char* src,char *dst)
{
	int q;

	//new code!! do this in a more nicer way!
	bool srcfound=false,dstfound=false;
	for(int i=1; i<argc; i++) 
	{
		//loop through the arguments!
		//first check for flags..
		if(argv[i][0]=='-') 
		{
			if(i==argc-1) 
			{
				printf("flag missing argument: %s!\n");
				exit(1);
			}
			//handle speed flag
			if(!strcmp(argv[i],"-s"))  
			{
				// We have argument -s. Now check for slow, medium or fast.
				if(!strcmp(argv[i+1],"slow")) 
					speed = SPEED_SLOW;
				else if(!strcmp(argv[i+1],"medium")) 
					speed = SPEED_MEDIUM;
				else if(!strcmp(argv[i+1],"fast")) 
					speed = SPEED_FAST;
				else 
				{
					printf("Error: %s not part of flag %s\n",argv[i+1], argv[i]);
					exit(1);
				}
			}
			//handle verbose flag
			else if(!strcmp(argv[i],"-v"))  
			{
				// We have argument -s. Now check for slow, medium or fast.
				if(!strcmp(argv[i+1],"off")) 
					verbose = false;
				else if(!strcmp(argv[i+1],"on")) 
					verbose = true;
				else 
				{
					printf("Error: %s not part of flag %s\n",argv[i+1], argv[i]);
					exit(1);
				}
			}
			//error metric flag
			else if(!strcmp(argv[i],"-e")) 	
			{
				// We have argument -e. Now check for perceptual or nonperceptual
				if(!strcmp(argv[i+1],"perceptual")) 
					metric = METRIC_PERCEPTUAL;
				else if(!strcmp(argv[i+1],"nonperceptual")) 
					metric = METRIC_NONPERCEPTUAL;
				else 
				{
					printf("Error: %s not part of flag %s\n",argv[i+1], argv[i]);
					exit(1);
				}
			}
			//codec flag
			else if(!strcmp(argv[i],"-c")) 
			{
				// We have argument -c. Now check for perceptual or nonperceptual
				if(!strcmp(argv[i+1],"etc") || !strcmp(argv[i+1],"etc1"))
					codec = CODEC_ETC;
				else if(!strcmp(argv[i+1],"etc2")) 
					codec = CODEC_ETC2;
				else 
				{
					printf("Error: %s not part of flag %s\n",argv[i+1], argv[i]);
					exit(1);
				}
			}
			//format flag
			else if(!strcmp(argv[i],"-f")) 
			{
				if(!strcmp(argv[i+1],"R"))
					format=ETC2PACKAGE_R_NO_MIPMAPS;
				else if(!strcmp(argv[i+1],"RG"))
					format=ETC2PACKAGE_RG_NO_MIPMAPS;
				else if(!strcmp(argv[i+1],"R_signed")) 
				{
					format=ETC2PACKAGE_R_NO_MIPMAPS;
					formatSigned=1;
				}
				else if(!strcmp(argv[i+1],"RG_signed")) 
				{
					format=ETC2PACKAGE_RG_NO_MIPMAPS;
					formatSigned=1;
				}
				else if(!strcmp(argv[i+1],"RGB"))
					format=ETC2PACKAGE_RGB_NO_MIPMAPS;
				else if(!strcmp(argv[i+1],"sRGB"))
					format=ETC2PACKAGE_sRGB_NO_MIPMAPS;
				else if(!strcmp(argv[i+1],"RGBA")||!strcmp(argv[i+1],"RGBA8"))
					format=ETC2PACKAGE_RGBA_NO_MIPMAPS;
				else if(!strcmp(argv[i+1],"sRGBA")||!strcmp(argv[i+1],"sRGBA8"))
					format=ETC2PACKAGE_sRGBA_NO_MIPMAPS;
				else if(!strcmp(argv[i+1],"RGBA1"))
					format=ETC2PACKAGE_RGBA1_NO_MIPMAPS;
				else if(!strcmp(argv[i+1],"sRGBA1"))
					format=ETC2PACKAGE_sRGBA1_NO_MIPMAPS;
				else 
				{
					printf("Error: %s not part of flag %s\n",argv[i+1], argv[i]);
					exit(1);
				}
			}
			else if(!strcmp(argv[i],"-p")) 
			{
				mode=MODE_PSNR;
				i--; //ugly way of negating the increment of i done later because -p doesn't have an argument.
			}
			else 
			{
				printf("Error: cannot interpret flag %s %s\n",argv[i], argv[i+1]);
				exit(1);
			}
			//don't read the flag argument next iteration..
			i++;
		}
		//this isn't a flag, so must be src or dst
		else 
		{
			if(srcfound&&dstfound) 
			{
				printf("too many arguments! expecting src, dst; found %s, %s, %s\n",src,dst,argv[i]);
				exit(1);
			}
			else if(srcfound) 
			{
				strcpy(dst,argv[i]);
				dstfound=true;
			}
			else 
			{
				strcpy(src,argv[i]);
				srcfound=true;
			}
		}
	}
	if(!srcfound&&dstfound) 
	{
		printf("too few arguments! expecting src, dst\n");
		exit(1);
	}
	if(mode==MODE_PSNR)
		return;
	//check source/destination.. is this compression or decompression?
	q = find_pos_of_extension(src);
	if(q<0) 
	{
		printf("invalid source file: %s\n",src);
		exit(1);
	}

	// If we have etcpack img.pkm img.any

	if(!strncmp(&src[q],".pkm",4)) 
	{
		// First argument is .pkm. Decompress. 
		mode = MODE_UNCOMPRESS;			// uncompress from binary file format .pkm
	}
	else if(!strncmp(&src[q],".ktx",4)) 
	{
		// First argument is .ktx. Decompress. 
		mode = MODE_UNCOMPRESS;			// uncompress from binary file format .pkm
		ktxFile=true;
		printf("decompressing ktx\n");
	}
	else
	{
		// The first argument was not .pkm. The second argument must then be .pkm.
		q = find_pos_of_extension(dst);
		if(q<0) 
		{
			printf("invalid destination file: %s\n",src);
			exit(1);
		}
		if(!strncmp(&dst[q],".pkm",4)) 
		{
			// Second argument is .pkm. Compress. 
			mode = MODE_COMPRESS;			// compress to binary file format .pkm
		}
		else if(!strncmp(&dst[q],".ktx",4)) 
		{
			// Second argument is .ktx. Compress. 
			ktxFile=true;
			mode = MODE_COMPRESS;			// compress to binary file format .pkm
			printf("compressing to ktx\n");
		}
		else 
		{
			printf("source or destination must be a .pkm or .ktx file\n");
			exit(1);
		}
	}
	//do some sanity check stuff..
	if(codec==CODEC_ETC&&format!=ETC2PACKAGE_RGB_NO_MIPMAPS) 
	{
		printf("ETC1 codec only supports RGB format\n");
		exit(1);
	}
	else if(codec==CODEC_ETC)
		format=ETC1_RGB_NO_MIPMAPS;
}

static int compressParams[16][4];
const int compressParamsFast[32] = {  -8,  -2,  2,   8,
									 -17,  -5,  5,  17,
									 -29,  -9,  9,  29,
									 -42, -13, 13,  42,
 									 -60, -18, 18,  60,
									 -80, -24, 24,  80,
									-106, -33, 33, 106,
									-183, -47, 47, 183};

bool readCompressParams(void)
{
	compressParams[0][0]  =  -8; compressParams[0][1]  =  -2; compressParams[0][2]  =  2; compressParams[0][3]  =   8;
	compressParams[1][0]  =  -8; compressParams[1][1]  =  -2; compressParams[1][2]  =  2; compressParams[1][3]  =   8;
	compressParams[2][0]  = -17; compressParams[2][1]  =  -5; compressParams[2][2]  =  5; compressParams[2][3]  =  17;
	compressParams[3][0]  = -17; compressParams[3][1]  =  -5; compressParams[3][2]  =  5; compressParams[3][3]  =  17;
	compressParams[4][0]  = -29; compressParams[4][1]  =  -9; compressParams[4][2]  =  9; compressParams[4][3]  =  29;
	compressParams[5][0]  = -29; compressParams[5][1]  =  -9; compressParams[5][2]  =  9; compressParams[5][3]  =  29;
	compressParams[6][0]  = -42; compressParams[6][1]  = -13; compressParams[6][2]  = 13; compressParams[6][3]  =  42;
	compressParams[7][0]  = -42; compressParams[7][1]  = -13; compressParams[7][2]  = 13; compressParams[7][3]  =  42;
 	compressParams[8][0]  = -60; compressParams[8][1]  = -18; compressParams[8][2]  = 18; compressParams[8][3]  =  60;
 	compressParams[9][0]  = -60; compressParams[9][1]  = -18; compressParams[9][2]  = 18; compressParams[9][3]  =  60;
	compressParams[10][0] = -80; compressParams[10][1] = -24; compressParams[10][2] = 24; compressParams[10][3] =  80;
	compressParams[11][0] = -80; compressParams[11][1] = -24; compressParams[11][2] = 24; compressParams[11][3] =  80;
	compressParams[12][0] =-106; compressParams[12][1] = -33; compressParams[12][2] = 33; compressParams[12][3] = 106;
	compressParams[13][0] =-106; compressParams[13][1] = -33; compressParams[13][2] = 33; compressParams[13][3] = 106;
	compressParams[14][0] =-183; compressParams[14][1] = -47; compressParams[14][2] = 47; compressParams[14][3] = 183;
	compressParams[15][0] =-183; compressParams[15][1] = -47; compressParams[15][2] = 47; compressParams[15][3] = 183;
	
	return true;
}

// Computes the average color in a 2x4 area and returns the average color as a float.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void computeAverageColor2x4noQuantFloat(uint8 *img,int width,int height,int startx,int starty,float *avg_color)
{
	int r=0,g=0,b=0;
	for(int y=starty; y<starty+4; y++)
	{
		for(int x=startx; x<startx+2; x++)
		{
			r+=RED(img,width,x,y);
			g+=GREEN(img,width,x,y);
			b+=BLUE(img,width,x,y);
		}
	}

	avg_color[0]=(float)(r/8.0);
	avg_color[1]=(float)(g/8.0);
	avg_color[2]=(float)(b/8.0);

}

// Computes the average color in a 4x2 area and returns the average color as a float.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void computeAverageColor4x2noQuantFloat(uint8 *img,int width,int height,int startx,int starty,float *avg_color)
{
	int r=0,g=0,b=0;
	for(int y=starty; y<starty+2; y++)
	{
		for(int x=startx; x<startx+4; x++)
		{
			r+=RED(img,width,x,y);
			g+=GREEN(img,width,x,y);
			b+=BLUE(img,width,x,y);
		}
	}

	avg_color[0]=(float)(r/8.0);
	avg_color[1]=(float)(g/8.0);
	avg_color[2]=(float)(b/8.0);
}

// Finds all pixel indices for a 2x4 block.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
int compressBlockWithTable2x4(uint8 *img,int width,int height,int startx,int starty,uint8 *avg_color,int table,unsigned int *pixel_indices_MSBp, unsigned int *pixel_indices_LSBp)
{
	uint8 orig[3],approx[3];
	unsigned int pixel_indices_MSB=0, pixel_indices_LSB=0, pixel_indices = 0;
	int sum_error=0;
	int q, i;


	i = 0;
	for(int x=startx; x<startx+2; x++)
	{
		for(int y=starty; y<starty+4; y++)
		{
			int err;
			int best=0;
			int min_error=255*255*3*16;
			orig[0]=RED(img,width,x,y);
			orig[1]=GREEN(img,width,x,y);
			orig[2]=BLUE(img,width,x,y);

			for(q=0;q<4;q++)
			{
				approx[0]=CLAMP(0, avg_color[0]+compressParams[table][q],255);
				approx[1]=CLAMP(0, avg_color[1]+compressParams[table][q],255);
				approx[2]=CLAMP(0, avg_color[2]+compressParams[table][q],255);

				// Here we just use equal weights to R, G and B. Although this will
				// give visually worse results, it will give a better PSNR score. 
				err=SQUARE(approx[0]-orig[0]) + SQUARE(approx[1]-orig[1]) + SQUARE(approx[2]-orig[2]);
				if(err<min_error)
				{
					min_error=err;
					best=q;
				}

			}
			pixel_indices = scramble[best];

			PUTBITS( pixel_indices_MSB, (pixel_indices >> 1), 1, i);
			PUTBITS( pixel_indices_LSB, (pixel_indices & 1) , 1, i);

			i++;

			// In order to simplify hardware, the table {-12, -4, 4, 12} is indexed {11, 10, 00, 01}
			// so that first bit is sign bit and the other bit is size bit (4 or 12). 
			// This means that we have to scramble the bits before storing them. 
			sum_error+=min_error;
		}
	}

	*pixel_indices_MSBp = pixel_indices_MSB;
	*pixel_indices_LSBp = pixel_indices_LSB;
	return sum_error;
}

#define MAXERR1000 1000*255*255*16

// Finds all pixel indices for a 2x4 block using perceptual weighting of error.
// Done using fixed poinit arithmetics where weights are multiplied by 1000.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int compressBlockWithTable2x4percep1000(uint8 *img,int width,int height,int startx,int starty,uint8 *avg_color,int table,unsigned int *pixel_indices_MSBp, unsigned int *pixel_indices_LSBp)
{
	uint8 orig[3],approx[3];
	unsigned int pixel_indices_MSB=0, pixel_indices_LSB=0, pixel_indices = 0;
	unsigned int sum_error=0;
	int q, i;

	i = 0;
	for(int x=startx; x<startx+2; x++)
	{
		for(int y=starty; y<starty+4; y++)
		{
			unsigned int err;
			int best=0;
			unsigned int min_error=MAXERR1000;
			orig[0]=RED(img,width,x,y);
			orig[1]=GREEN(img,width,x,y);
			orig[2]=BLUE(img,width,x,y);

			for(q=0;q<4;q++)
			{
				approx[0]=CLAMP(0, avg_color[0]+compressParams[table][q],255);
				approx[1]=CLAMP(0, avg_color[1]+compressParams[table][q],255);
				approx[2]=CLAMP(0, avg_color[2]+compressParams[table][q],255);

				// Here we just use equal weights to R, G and B. Although this will
				// give visually worse results, it will give a better PSNR score. 
  				err = (PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE((approx[0]-orig[0])) 
					 + PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*SQUARE((approx[1]-orig[1])) 
					 + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*SQUARE((approx[2]-orig[2])));
				if(err<min_error)
				{
					min_error=err;
					best=q;
				}

			}

			pixel_indices = scramble[best];

			PUTBITS( pixel_indices_MSB, (pixel_indices >> 1), 1, i);
			PUTBITS( pixel_indices_LSB, (pixel_indices & 1) , 1, i);

			i++;

			// In order to simplify hardware, the table {-12, -4, 4, 12} is indexed {11, 10, 00, 01}
			// so that first bit is sign bit and the other bit is size bit (4 or 12). 
			// This means that we have to scramble the bits before storing them. 

			
			sum_error+=min_error;
		}

	}

	*pixel_indices_MSBp = pixel_indices_MSB;
	*pixel_indices_LSBp = pixel_indices_LSB;

	return sum_error;
}

// Finds all pixel indices for a 2x4 block using perceptual weighting of error.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
float compressBlockWithTable2x4percep(uint8 *img,int width,int height,int startx,int starty,uint8 *avg_color,int table,unsigned int *pixel_indices_MSBp, unsigned int *pixel_indices_LSBp)
{
	uint8 orig[3],approx[3];
	unsigned int pixel_indices_MSB=0, pixel_indices_LSB=0, pixel_indices = 0;
	float sum_error=0;
	int q, i;

	double wR2 = PERCEPTUAL_WEIGHT_R_SQUARED;
	double wG2 = PERCEPTUAL_WEIGHT_G_SQUARED;
	double wB2 = PERCEPTUAL_WEIGHT_B_SQUARED;

	i = 0;
	for(int x=startx; x<startx+2; x++)
	{
		for(int y=starty; y<starty+4; y++)
		{
			float err;
			int best=0;
			float min_error=255*255*3*16;
			orig[0]=RED(img,width,x,y);
			orig[1]=GREEN(img,width,x,y);
			orig[2]=BLUE(img,width,x,y);

			for(q=0;q<4;q++)
			{
				approx[0]=CLAMP(0, avg_color[0]+compressParams[table][q],255);
				approx[1]=CLAMP(0, avg_color[1]+compressParams[table][q],255);
				approx[2]=CLAMP(0, avg_color[2]+compressParams[table][q],255);

				// Here we just use equal weights to R, G and B. Although this will
				// give visually worse results, it will give a better PSNR score. 
  				err=(float)(wR2*SQUARE((approx[0]-orig[0])) + (float)wG2*SQUARE((approx[1]-orig[1])) + (float)wB2*SQUARE((approx[2]-orig[2])));
				if(err<min_error)
				{
					min_error=err;
					best=q;
				}
			}

			pixel_indices = scramble[best];

			PUTBITS( pixel_indices_MSB, (pixel_indices >> 1), 1, i);
			PUTBITS( pixel_indices_LSB, (pixel_indices & 1) , 1, i);

			i++;

			// In order to simplify hardware, the table {-12, -4, 4, 12} is indexed {11, 10, 00, 01}
			// so that first bit is sign bit and the other bit is size bit (4 or 12). 
			// This means that we have to scramble the bits before storing them. 
		
			sum_error+=min_error;
		}
	}

	*pixel_indices_MSBp = pixel_indices_MSB;
	*pixel_indices_LSBp = pixel_indices_LSB;

	return sum_error;
}

// Finds all pixel indices for a 4x2 block.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
int compressBlockWithTable4x2(uint8 *img,int width,int height,int startx,int starty,uint8 *avg_color,int table,unsigned int *pixel_indices_MSBp, unsigned int *pixel_indices_LSBp)
{
	uint8 orig[3],approx[3];
	unsigned int pixel_indices_MSB=0, pixel_indices_LSB=0, pixel_indices = 0;
	int sum_error=0;
	int q;
	int i;

	i = 0;
	for(int x=startx; x<startx+4; x++)
	{
		for(int y=starty; y<starty+2; y++)
		{
			int err;
			int best=0;
			int min_error=255*255*3*16;
			orig[0]=RED(img,width,x,y);
			orig[1]=GREEN(img,width,x,y);
			orig[2]=BLUE(img,width,x,y);

			for(q=0;q<4;q++)
			{
				approx[0]=CLAMP(0, avg_color[0]+compressParams[table][q],255);
				approx[1]=CLAMP(0, avg_color[1]+compressParams[table][q],255);
				approx[2]=CLAMP(0, avg_color[2]+compressParams[table][q],255);

				// Here we just use equal weights to R, G and B. Although this will
				// give visually worse results, it will give a better PSNR score. 
				err=SQUARE(approx[0]-orig[0]) + SQUARE(approx[1]-orig[1]) + SQUARE(approx[2]-orig[2]);
				if(err<min_error)
				{
					min_error=err;
					best=q;
				}
			}
			pixel_indices = scramble[best];

			PUTBITS( pixel_indices_MSB, (pixel_indices >> 1), 1, i);
			PUTBITS( pixel_indices_LSB, (pixel_indices & 1) , 1, i);
			i++;

			// In order to simplify hardware, the table {-12, -4, 4, 12} is indexed {11, 10, 00, 01}
			// so that first bit is sign bit and the other bit is size bit (4 or 12). 
			// This means that we have to scramble the bits before storing them. 

			sum_error+=min_error;
		}
		i+=2;
	}

	*pixel_indices_MSBp = pixel_indices_MSB;
	*pixel_indices_LSBp = pixel_indices_LSB;

	return sum_error;
}

// Finds all pixel indices for a 4x2 block using perceptual weighting of error.
// Done using fixed point arithmetics where 1000 corresponds to 1.0.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int compressBlockWithTable4x2percep1000(uint8 *img,int width,int height,int startx,int starty,uint8 *avg_color,int table,unsigned int *pixel_indices_MSBp, unsigned int *pixel_indices_LSBp)
{
	uint8 orig[3],approx[3];
	unsigned int pixel_indices_MSB=0, pixel_indices_LSB=0, pixel_indices = 0;
	unsigned int sum_error=0;
	int q;
	int i;

	i = 0;
	for(int x=startx; x<startx+4; x++)
	{
		for(int y=starty; y<starty+2; y++)
		{
			unsigned int err;
			int best=0;
			unsigned int min_error=MAXERR1000;
			orig[0]=RED(img,width,x,y);
			orig[1]=GREEN(img,width,x,y);
			orig[2]=BLUE(img,width,x,y);

			for(q=0;q<4;q++)
			{
				approx[0]=CLAMP(0, avg_color[0]+compressParams[table][q],255);
				approx[1]=CLAMP(0, avg_color[1]+compressParams[table][q],255);
				approx[2]=CLAMP(0, avg_color[2]+compressParams[table][q],255);

				// Here we just use equal weights to R, G and B. Although this will
				// give visually worse results, it will give a better PSNR score. 
				err = PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(approx[0]-orig[0]) 
					+ PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*SQUARE(approx[1]-orig[1]) 
					+ PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*SQUARE(approx[2]-orig[2]);
				if(err<min_error)
				{
					min_error=err;
					best=q;
				}
			}
			pixel_indices = scramble[best];

			PUTBITS( pixel_indices_MSB, (pixel_indices >> 1), 1, i);
			PUTBITS( pixel_indices_LSB, (pixel_indices & 1) , 1, i);
			i++;

			// In order to simplify hardware, the table {-12, -4, 4, 12} is indexed {11, 10, 00, 01}
			// so that first bit is sign bit and the other bit is size bit (4 or 12). 
			// This means that we have to scramble the bits before storing them. 

			sum_error+=min_error;
		}
		i+=2;

	}

	*pixel_indices_MSBp = pixel_indices_MSB;
	*pixel_indices_LSBp = pixel_indices_LSB;

	return sum_error;
}

// Finds all pixel indices for a 4x2 block using perceptual weighting of error.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
float compressBlockWithTable4x2percep(uint8 *img,int width,int height,int startx,int starty,uint8 *avg_color,int table,unsigned int *pixel_indices_MSBp, unsigned int *pixel_indices_LSBp)
{
	uint8 orig[3],approx[3];
	unsigned int pixel_indices_MSB=0, pixel_indices_LSB=0, pixel_indices = 0;
	float sum_error=0;
	int q;
	int i;
	float wR2 = (float) PERCEPTUAL_WEIGHT_R_SQUARED;
	float wG2 = (float) PERCEPTUAL_WEIGHT_G_SQUARED;
	float wB2 = (float) PERCEPTUAL_WEIGHT_B_SQUARED;

	i = 0;
	for(int x=startx; x<startx+4; x++)
	{
		for(int y=starty; y<starty+2; y++)
		{
			float err;
			int best=0;
			float min_error=255*255*3*16;
			orig[0]=RED(img,width,x,y);
			orig[1]=GREEN(img,width,x,y);
			orig[2]=BLUE(img,width,x,y);

			for(q=0;q<4;q++)
			{
				approx[0]=CLAMP(0, avg_color[0]+compressParams[table][q],255);
				approx[1]=CLAMP(0, avg_color[1]+compressParams[table][q],255);
				approx[2]=CLAMP(0, avg_color[2]+compressParams[table][q],255);

				// Here we just use equal weights to R, G and B. Although this will
				// give visually worse results, it will give a better PSNR score. 
				err=(float) wR2*SQUARE(approx[0]-orig[0]) + (float)wG2*SQUARE(approx[1]-orig[1]) + (float)wB2*SQUARE(approx[2]-orig[2]);
				if(err<min_error)
				{
					min_error=err;
					best=q;
				}
			}
			pixel_indices = scramble[best];

			PUTBITS( pixel_indices_MSB, (pixel_indices >> 1), 1, i);
			PUTBITS( pixel_indices_LSB, (pixel_indices & 1) , 1, i);
			i++;

			// In order to simplify hardware, the table {-12, -4, 4, 12} is indexed {11, 10, 00, 01}
			// so that first bit is sign bit and the other bit is size bit (4 or 12). 
			// This means that we have to scramble the bits before storing them. 

			sum_error+=min_error;
		}
		i+=2;
	}

	*pixel_indices_MSBp = pixel_indices_MSB;
	*pixel_indices_LSBp = pixel_indices_LSB;

	return sum_error;
}

// Table for fast implementation of clamping to the interval [0,255] followed by addition of 255.
const int clamp_table_plus_255[768] = {0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 0+255, 
                        0+255, 1+255, 2+255, 3+255, 4+255, 5+255, 6+255, 7+255, 8+255, 9+255, 10+255, 11+255, 12+255, 13+255, 14+255, 15+255, 16+255, 17+255, 18+255, 19+255, 20+255, 21+255, 22+255, 23+255, 24+255, 25+255, 26+255, 27+255, 28+255, 29+255, 30+255, 31+255, 32+255, 33+255, 34+255, 35+255, 36+255, 37+255, 38+255, 39+255, 40+255, 41+255, 42+255, 43+255, 44+255, 45+255, 46+255, 47+255, 48+255, 49+255, 50+255, 51+255, 52+255, 53+255, 54+255, 55+255, 56+255, 57+255, 58+255, 59+255, 60+255, 61+255, 62+255, 63+255, 64+255, 65+255, 66+255, 67+255, 68+255, 69+255, 70+255, 71+255, 72+255, 73+255, 74+255, 75+255, 76+255, 77+255, 78+255, 79+255, 80+255, 81+255, 82+255, 83+255, 84+255, 85+255, 86+255, 87+255, 88+255, 89+255, 90+255, 91+255, 92+255, 93+255, 94+255, 95+255, 96+255, 97+255, 98+255, 99+255, 100+255, 101+255, 102+255, 103+255, 104+255, 105+255, 106+255, 107+255, 108+255, 109+255, 110+255, 111+255, 112+255, 113+255, 114+255, 115+255, 116+255, 117+255, 118+255, 119+255, 120+255, 121+255, 122+255, 123+255, 124+255, 125+255, 126+255, 127+255, 128+255, 129+255, 130+255, 131+255, 132+255, 133+255, 134+255, 135+255, 136+255, 137+255, 138+255, 139+255, 140+255, 141+255, 142+255, 143+255, 144+255, 145+255, 146+255, 147+255, 148+255, 149+255, 150+255, 151+255, 152+255, 153+255, 154+255, 155+255, 156+255, 157+255, 158+255, 159+255, 160+255, 161+255, 162+255, 163+255, 164+255, 165+255, 166+255, 167+255, 168+255, 169+255, 170+255, 171+255, 172+255, 173+255, 174+255, 175+255, 176+255, 177+255, 178+255, 179+255, 180+255, 181+255, 182+255, 183+255, 184+255, 185+255, 186+255, 187+255, 188+255, 189+255, 190+255, 191+255, 192+255, 193+255, 194+255, 195+255, 196+255, 197+255, 198+255, 199+255, 200+255, 201+255, 202+255, 203+255, 204+255, 205+255, 206+255, 207+255, 208+255, 209+255, 210+255, 211+255, 
						212+255, 213+255, 214+255, 215+255, 216+255, 217+255, 218+255, 219+255, 220+255, 221+255, 222+255, 223+255, 224+255, 225+255, 226+255, 227+255, 228+255, 229+255, 230+255, 231+255, 232+255, 233+255, 234+255, 235+255, 236+255, 237+255, 238+255, 239+255, 240+255, 241+255, 242+255, 243+255, 244+255, 245+255, 246+255, 247+255, 248+255, 249+255, 250+255, 251+255, 252+255, 253+255, 254+255, 255+255,
						255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 
						255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255, 255+255};

// Table for fast implementationi of clamping to the interval [0,255]
const int clamp_table[768] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
						255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

// Table for fast implementation of squaring for numbers in the interval [-255, 255]
const unsigned int square_table[511] = {65025, 64516, 64009, 63504, 63001, 62500, 62001, 61504, 61009, 60516, 60025, 59536, 59049, 58564, 58081, 57600, 
						 57121, 56644, 56169, 55696, 55225, 54756, 54289, 53824, 53361, 52900, 52441, 51984, 51529, 51076, 50625, 50176, 
						 49729, 49284, 48841, 48400, 47961, 47524, 47089, 46656, 46225, 45796, 45369, 44944, 44521, 44100, 43681, 43264, 
						 42849, 42436, 42025, 41616, 41209, 40804, 40401, 40000, 39601, 39204, 38809, 38416, 38025, 37636, 37249, 36864, 
						 36481, 36100, 35721, 35344, 34969, 34596, 34225, 33856, 33489, 33124, 32761, 32400, 32041, 31684, 31329, 30976, 
						 30625, 30276, 29929, 29584, 29241, 28900, 28561, 28224, 27889, 27556, 27225, 26896, 26569, 26244, 25921, 25600, 
						 25281, 24964, 24649, 24336, 24025, 23716, 23409, 23104, 22801, 22500, 22201, 21904, 21609, 21316, 21025, 20736, 
						 20449, 20164, 19881, 19600, 19321, 19044, 18769, 18496, 18225, 17956, 17689, 17424, 17161, 16900, 16641, 16384, 
						 16129, 15876, 15625, 15376, 15129, 14884, 14641, 14400, 14161, 13924, 13689, 13456, 13225, 12996, 12769, 12544, 
						 12321, 12100, 11881, 11664, 11449, 11236, 11025, 10816, 10609, 10404, 10201, 10000, 9801, 9604, 9409, 9216, 
						 9025, 8836, 8649, 8464, 8281, 8100, 7921, 7744, 7569, 7396, 7225, 7056, 6889, 6724, 6561, 6400, 
						 6241, 6084, 5929, 5776, 5625, 5476, 5329, 5184, 5041, 4900, 4761, 4624, 4489, 4356, 4225, 4096, 
						 3969, 3844, 3721, 3600, 3481, 3364, 3249, 3136, 3025, 2916, 2809, 2704, 2601, 2500, 2401, 2304, 
						 2209, 2116, 2025, 1936, 1849, 1764, 1681, 1600, 1521, 1444, 1369, 1296, 1225, 1156, 1089, 1024, 
						 961, 900, 841, 784, 729, 676, 625, 576, 529, 484, 441, 400, 361, 324, 289, 256,
						 225, 196, 169, 144, 121, 100, 81, 64, 49, 36, 25, 16, 9, 4, 1, 
					     0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 
                         256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 
						 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 
						 2304, 2401, 2500, 2601, 2704, 2809, 2916, 3025, 3136, 3249, 3364, 3481, 3600, 3721, 3844, 3969, 
						 4096, 4225, 4356, 4489, 4624, 4761, 4900, 5041, 5184, 5329, 5476, 5625, 5776, 5929, 6084, 6241, 
						 6400, 6561, 6724, 6889, 7056, 7225, 7396, 7569, 7744, 7921, 8100, 8281, 8464, 8649, 8836, 9025, 
						 9216, 9409, 9604, 9801, 10000, 10201, 10404, 10609, 10816, 11025, 11236, 11449, 11664, 11881, 12100, 12321,
						 12544, 12769, 12996, 13225, 13456, 13689, 13924, 14161, 14400, 14641, 14884, 15129, 15376, 15625, 15876, 16129,
						 16384, 16641, 16900, 17161, 17424, 17689, 17956, 18225, 18496, 18769, 19044, 19321, 19600, 19881, 20164, 20449, 
						 20736, 21025, 21316, 21609, 21904, 22201, 22500, 22801, 23104, 23409, 23716, 24025, 24336, 24649, 24964, 25281, 
						 25600, 25921, 26244, 26569, 26896, 27225, 27556, 27889, 28224, 28561, 28900, 29241, 29584, 29929, 30276, 30625, 
						 30976, 31329, 31684, 32041, 32400, 32761, 33124, 33489, 33856, 34225, 34596, 34969, 35344, 35721, 36100, 36481, 
						 36864, 37249, 37636, 38025, 38416, 38809, 39204, 39601, 40000, 40401, 40804, 41209, 41616, 42025, 42436, 42849, 
						 43264, 43681, 44100, 44521, 44944, 45369, 45796, 46225, 46656, 47089, 47524, 47961, 48400, 48841, 49284, 49729, 
						 50176, 50625, 51076, 51529, 51984, 52441, 52900, 53361, 53824, 54289, 54756, 55225, 55696, 56169, 56644, 57121, 
						 57600, 58081, 58564, 59049, 59536, 60025, 60516, 61009, 61504, 62001, 62500, 63001, 63504, 64009, 64516, 65025}; 

// Abbreviated variable names to make below tables smaller in source code size
#define KR PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000
#define KG PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000
#define KB PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000

// Table for fast implementation of squaring for numbers in the interval [-255, 255] multiplied by the perceptual weight for red.
const unsigned int square_table_percep_red[511] = {
                         65025*KR, 64516*KR, 64009*KR, 63504*KR, 63001*KR, 62500*KR, 62001*KR, 61504*KR, 61009*KR, 60516*KR, 60025*KR, 59536*KR, 59049*KR, 58564*KR, 58081*KR, 57600*KR, 
						 57121*KR, 56644*KR, 56169*KR, 55696*KR, 55225*KR, 54756*KR, 54289*KR, 53824*KR, 53361*KR, 52900*KR, 52441*KR, 51984*KR, 51529*KR, 51076*KR, 50625*KR, 50176*KR, 
						 49729*KR, 49284*KR, 48841*KR, 48400*KR, 47961*KR, 47524*KR, 47089*KR, 46656*KR, 46225*KR, 45796*KR, 45369*KR, 44944*KR, 44521*KR, 44100*KR, 43681*KR, 43264*KR, 
						 42849*KR, 42436*KR, 42025*KR, 41616*KR, 41209*KR, 40804*KR, 40401*KR, 40000*KR, 39601*KR, 39204*KR, 38809*KR, 38416*KR, 38025*KR, 37636*KR, 37249*KR, 36864*KR, 
						 36481*KR, 36100*KR, 35721*KR, 35344*KR, 34969*KR, 34596*KR, 34225*KR, 33856*KR, 33489*KR, 33124*KR, 32761*KR, 32400*KR, 32041*KR, 31684*KR, 31329*KR, 30976*KR, 
						 30625*KR, 30276*KR, 29929*KR, 29584*KR, 29241*KR, 28900*KR, 28561*KR, 28224*KR, 27889*KR, 27556*KR, 27225*KR, 26896*KR, 26569*KR, 26244*KR, 25921*KR, 25600*KR, 
						 25281*KR, 24964*KR, 24649*KR, 24336*KR, 24025*KR, 23716*KR, 23409*KR, 23104*KR, 22801*KR, 22500*KR, 22201*KR, 21904*KR, 21609*KR, 21316*KR, 21025*KR, 20736*KR, 
						 20449*KR, 20164*KR, 19881*KR, 19600*KR, 19321*KR, 19044*KR, 18769*KR, 18496*KR, 18225*KR, 17956*KR, 17689*KR, 17424*KR, 17161*KR, 16900*KR, 16641*KR, 16384*KR, 
						 16129*KR, 15876*KR, 15625*KR, 15376*KR, 15129*KR, 14884*KR, 14641*KR, 14400*KR, 14161*KR, 13924*KR, 13689*KR, 13456*KR, 13225*KR, 12996*KR, 12769*KR, 12544*KR, 
						 12321*KR, 12100*KR, 11881*KR, 11664*KR, 11449*KR, 11236*KR, 11025*KR, 10816*KR, 10609*KR, 10404*KR, 10201*KR, 10000*KR, 9801*KR, 9604*KR, 9409*KR, 9216*KR, 
						 9025*KR, 8836*KR, 8649*KR, 8464*KR, 8281*KR, 8100*KR, 7921*KR, 7744*KR, 7569*KR, 7396*KR, 7225*KR, 7056*KR, 6889*KR, 6724*KR, 6561*KR, 6400*KR, 
						 6241*KR, 6084*KR, 5929*KR, 5776*KR, 5625*KR, 5476*KR, 5329*KR, 5184*KR, 5041*KR, 4900*KR, 4761*KR, 4624*KR, 4489*KR, 4356*KR, 4225*KR, 4096*KR, 
						 3969*KR, 3844*KR, 3721*KR, 3600*KR, 3481*KR, 3364*KR, 3249*KR, 3136*KR, 3025*KR, 2916*KR, 2809*KR, 2704*KR, 2601*KR, 2500*KR, 2401*KR, 2304*KR, 
						 2209*KR, 2116*KR, 2025*KR, 1936*KR, 1849*KR, 1764*KR, 1681*KR, 1600*KR, 1521*KR, 1444*KR, 1369*KR, 1296*KR, 1225*KR, 1156*KR, 1089*KR, 1024*KR, 
						 961*KR, 900*KR, 841*KR, 784*KR, 729*KR, 676*KR, 625*KR, 576*KR, 529*KR, 484*KR, 441*KR, 400*KR, 361*KR, 324*KR, 289*KR, 256*KR,
						 225*KR, 196*KR, 169*KR, 144*KR, 121*KR, 100*KR, 81*KR, 64*KR, 49*KR, 36*KR, 25*KR, 16*KR, 9*KR, 4*KR, 1*KR, 
						 0*KR, 1*KR, 4*KR, 9*KR, 16*KR, 25*KR, 36*KR, 49*KR, 64*KR, 81*KR, 100*KR, 121*KR, 144*KR, 169*KR, 196*KR, 225*KR, 
						 256*KR, 289*KR, 324*KR, 361*KR, 400*KR, 441*KR, 484*KR, 529*KR, 576*KR, 625*KR, 676*KR, 729*KR, 784*KR, 841*KR, 900*KR, 961*KR, 
						 1024*KR, 1089*KR, 1156*KR, 1225*KR, 1296*KR, 1369*KR, 1444*KR, 1521*KR, 1600*KR, 1681*KR, 1764*KR, 1849*KR, 1936*KR, 2025*KR, 2116*KR, 2209*KR, 
						 2304*KR, 2401*KR, 2500*KR, 2601*KR, 2704*KR, 2809*KR, 2916*KR, 3025*KR, 3136*KR, 3249*KR, 3364*KR, 3481*KR, 3600*KR, 3721*KR, 3844*KR, 3969*KR, 
						 4096*KR, 4225*KR, 4356*KR, 4489*KR, 4624*KR, 4761*KR, 4900*KR, 5041*KR, 5184*KR, 5329*KR, 5476*KR, 5625*KR, 5776*KR, 5929*KR, 6084*KR, 6241*KR, 
						 6400*KR, 6561*KR, 6724*KR, 6889*KR, 7056*KR, 7225*KR, 7396*KR, 7569*KR, 7744*KR, 7921*KR, 8100*KR, 8281*KR, 8464*KR, 8649*KR, 8836*KR, 9025*KR, 
						 9216*KR, 9409*KR, 9604*KR, 9801*KR, 10000*KR, 10201*KR, 10404*KR, 10609*KR, 10816*KR, 11025*KR, 11236*KR, 11449*KR, 11664*KR, 11881*KR, 12100*KR, 12321*KR,
						 12544*KR, 12769*KR, 12996*KR, 13225*KR, 13456*KR, 13689*KR, 13924*KR, 14161*KR, 14400*KR, 14641*KR, 14884*KR, 15129*KR, 15376*KR, 15625*KR, 15876*KR, 16129*KR,
						 16384*KR, 16641*KR, 16900*KR, 17161*KR, 17424*KR, 17689*KR, 17956*KR, 18225*KR, 18496*KR, 18769*KR, 19044*KR, 19321*KR, 19600*KR, 19881*KR, 20164*KR, 20449*KR, 
						 20736*KR, 21025*KR, 21316*KR, 21609*KR, 21904*KR, 22201*KR, 22500*KR, 22801*KR, 23104*KR, 23409*KR, 23716*KR, 24025*KR, 24336*KR, 24649*KR, 24964*KR, 25281*KR, 
						 25600*KR, 25921*KR, 26244*KR, 26569*KR, 26896*KR, 27225*KR, 27556*KR, 27889*KR, 28224*KR, 28561*KR, 28900*KR, 29241*KR, 29584*KR, 29929*KR, 30276*KR, 30625*KR, 
						 30976*KR, 31329*KR, 31684*KR, 32041*KR, 32400*KR, 32761*KR, 33124*KR, 33489*KR, 33856*KR, 34225*KR, 34596*KR, 34969*KR, 35344*KR, 35721*KR, 36100*KR, 36481*KR, 
						 36864*KR, 37249*KR, 37636*KR, 38025*KR, 38416*KR, 38809*KR, 39204*KR, 39601*KR, 40000*KR, 40401*KR, 40804*KR, 41209*KR, 41616*KR, 42025*KR, 42436*KR, 42849*KR, 
						 43264*KR, 43681*KR, 44100*KR, 44521*KR, 44944*KR, 45369*KR, 45796*KR, 46225*KR, 46656*KR, 47089*KR, 47524*KR, 47961*KR, 48400*KR, 48841*KR, 49284*KR, 49729*KR, 
						 50176*KR, 50625*KR, 51076*KR, 51529*KR, 51984*KR, 52441*KR, 52900*KR, 53361*KR, 53824*KR, 54289*KR, 54756*KR, 55225*KR, 55696*KR, 56169*KR, 56644*KR, 57121*KR, 
						 57600*KR, 58081*KR, 58564*KR, 59049*KR, 59536*KR, 60025*KR, 60516*KR, 61009*KR, 61504*KR, 62001*KR, 62500*KR, 63001*KR, 63504*KR, 64009*KR, 64516*KR, 65025*KR}; 

// Table for fast implementation of squaring for numbers in the interval [-255, 255] multiplied by the perceptual weight for green.
const unsigned int square_table_percep_green[511] = {
                         65025*KG, 64516*KG, 64009*KG, 63504*KG, 63001*KG, 62500*KG, 62001*KG, 61504*KG, 61009*KG, 60516*KG, 60025*KG, 59536*KG, 59049*KG, 58564*KG, 58081*KG, 57600*KG, 
						 57121*KG, 56644*KG, 56169*KG, 55696*KG, 55225*KG, 54756*KG, 54289*KG, 53824*KG, 53361*KG, 52900*KG, 52441*KG, 51984*KG, 51529*KG, 51076*KG, 50625*KG, 50176*KG, 
						 49729*KG, 49284*KG, 48841*KG, 48400*KG, 47961*KG, 47524*KG, 47089*KG, 46656*KG, 46225*KG, 45796*KG, 45369*KG, 44944*KG, 44521*KG, 44100*KG, 43681*KG, 43264*KG, 
						 42849*KG, 42436*KG, 42025*KG, 41616*KG, 41209*KG, 40804*KG, 40401*KG, 40000*KG, 39601*KG, 39204*KG, 38809*KG, 38416*KG, 38025*KG, 37636*KG, 37249*KG, 36864*KG, 
						 36481*KG, 36100*KG, 35721*KG, 35344*KG, 34969*KG, 34596*KG, 34225*KG, 33856*KG, 33489*KG, 33124*KG, 32761*KG, 32400*KG, 32041*KG, 31684*KG, 31329*KG, 30976*KG, 
						 30625*KG, 30276*KG, 29929*KG, 29584*KG, 29241*KG, 28900*KG, 28561*KG, 28224*KG, 27889*KG, 27556*KG, 27225*KG, 26896*KG, 26569*KG, 26244*KG, 25921*KG, 25600*KG, 
						 25281*KG, 24964*KG, 24649*KG, 24336*KG, 24025*KG, 23716*KG, 23409*KG, 23104*KG, 22801*KG, 22500*KG, 22201*KG, 21904*KG, 21609*KG, 21316*KG, 21025*KG, 20736*KG, 
						 20449*KG, 20164*KG, 19881*KG, 19600*KG, 19321*KG, 19044*KG, 18769*KG, 18496*KG, 18225*KG, 17956*KG, 17689*KG, 17424*KG, 17161*KG, 16900*KG, 16641*KG, 16384*KG, 
						 16129*KG, 15876*KG, 15625*KG, 15376*KG, 15129*KG, 14884*KG, 14641*KG, 14400*KG, 14161*KG, 13924*KG, 13689*KG, 13456*KG, 13225*KG, 12996*KG, 12769*KG, 12544*KG, 
						 12321*KG, 12100*KG, 11881*KG, 11664*KG, 11449*KG, 11236*KG, 11025*KG, 10816*KG, 10609*KG, 10404*KG, 10201*KG, 10000*KG, 9801*KG, 9604*KG, 9409*KG, 9216*KG, 
						 9025*KG, 8836*KG, 8649*KG, 8464*KG, 8281*KG, 8100*KG, 7921*KG, 7744*KG, 7569*KG, 7396*KG, 7225*KG, 7056*KG, 6889*KG, 6724*KG, 6561*KG, 6400*KG, 
						 6241*KG, 6084*KG, 5929*KG, 5776*KG, 5625*KG, 5476*KG, 5329*KG, 5184*KG, 5041*KG, 4900*KG, 4761*KG, 4624*KG, 4489*KG, 4356*KG, 4225*KG, 4096*KG, 
						 3969*KG, 3844*KG, 3721*KG, 3600*KG, 3481*KG, 3364*KG, 3249*KG, 3136*KG, 3025*KG, 2916*KG, 2809*KG, 2704*KG, 2601*KG, 2500*KG, 2401*KG, 2304*KG, 
						 2209*KG, 2116*KG, 2025*KG, 1936*KG, 1849*KG, 1764*KG, 1681*KG, 1600*KG, 1521*KG, 1444*KG, 1369*KG, 1296*KG, 1225*KG, 1156*KG, 1089*KG, 1024*KG, 
						 961*KG, 900*KG, 841*KG, 784*KG, 729*KG, 676*KG, 625*KG, 576*KG, 529*KG, 484*KG, 441*KG, 400*KG, 361*KG, 324*KG, 289*KG, 256*KG,
						 225*KG, 196*KG, 169*KG, 144*KG, 121*KG, 100*KG, 81*KG, 64*KG, 49*KG, 36*KG, 25*KG, 16*KG, 9*KG, 4*KG, 1*KG, 
						 0*KG, 1*KG, 4*KG, 9*KG, 16*KG, 25*KG, 36*KG, 49*KG, 64*KG, 81*KG, 100*KG, 121*KG, 144*KG, 169*KG, 196*KG, 225*KG, 
						 256*KG, 289*KG, 324*KG, 361*KG, 400*KG, 441*KG, 484*KG, 529*KG, 576*KG, 625*KG, 676*KG, 729*KG, 784*KG, 841*KG, 900*KG, 961*KG, 
						 1024*KG, 1089*KG, 1156*KG, 1225*KG, 1296*KG, 1369*KG, 1444*KG, 1521*KG, 1600*KG, 1681*KG, 1764*KG, 1849*KG, 1936*KG, 2025*KG, 2116*KG, 2209*KG, 
						 2304*KG, 2401*KG, 2500*KG, 2601*KG, 2704*KG, 2809*KG, 2916*KG, 3025*KG, 3136*KG, 3249*KG, 3364*KG, 3481*KG, 3600*KG, 3721*KG, 3844*KG, 3969*KG, 
						 4096*KG, 4225*KG, 4356*KG, 4489*KG, 4624*KG, 4761*KG, 4900*KG, 5041*KG, 5184*KG, 5329*KG, 5476*KG, 5625*KG, 5776*KG, 5929*KG, 6084*KG, 6241*KG, 
						 6400*KG, 6561*KG, 6724*KG, 6889*KG, 7056*KG, 7225*KG, 7396*KG, 7569*KG, 7744*KG, 7921*KG, 8100*KG, 8281*KG, 8464*KG, 8649*KG, 8836*KG, 9025*KG, 
						 9216*KG, 9409*KG, 9604*KG, 9801*KG, 10000*KG, 10201*KG, 10404*KG, 10609*KG, 10816*KG, 11025*KG, 11236*KG, 11449*KG, 11664*KG, 11881*KG, 12100*KG, 12321*KG,
						 12544*KG, 12769*KG, 12996*KG, 13225*KG, 13456*KG, 13689*KG, 13924*KG, 14161*KG, 14400*KG, 14641*KG, 14884*KG, 15129*KG, 15376*KG, 15625*KG, 15876*KG, 16129*KG,
						 16384*KG, 16641*KG, 16900*KG, 17161*KG, 17424*KG, 17689*KG, 17956*KG, 18225*KG, 18496*KG, 18769*KG, 19044*KG, 19321*KG, 19600*KG, 19881*KG, 20164*KG, 20449*KG, 
						 20736*KG, 21025*KG, 21316*KG, 21609*KG, 21904*KG, 22201*KG, 22500*KG, 22801*KG, 23104*KG, 23409*KG, 23716*KG, 24025*KG, 24336*KG, 24649*KG, 24964*KG, 25281*KG, 
						 25600*KG, 25921*KG, 26244*KG, 26569*KG, 26896*KG, 27225*KG, 27556*KG, 27889*KG, 28224*KG, 28561*KG, 28900*KG, 29241*KG, 29584*KG, 29929*KG, 30276*KG, 30625*KG, 
						 30976*KG, 31329*KG, 31684*KG, 32041*KG, 32400*KG, 32761*KG, 33124*KG, 33489*KG, 33856*KG, 34225*KG, 34596*KG, 34969*KG, 35344*KG, 35721*KG, 36100*KG, 36481*KG, 
						 36864*KG, 37249*KG, 37636*KG, 38025*KG, 38416*KG, 38809*KG, 39204*KG, 39601*KG, 40000*KG, 40401*KG, 40804*KG, 41209*KG, 41616*KG, 42025*KG, 42436*KG, 42849*KG, 
						 43264*KG, 43681*KG, 44100*KG, 44521*KG, 44944*KG, 45369*KG, 45796*KG, 46225*KG, 46656*KG, 47089*KG, 47524*KG, 47961*KG, 48400*KG, 48841*KG, 49284*KG, 49729*KG, 
						 50176*KG, 50625*KG, 51076*KG, 51529*KG, 51984*KG, 52441*KG, 52900*KG, 53361*KG, 53824*KG, 54289*KG, 54756*KG, 55225*KG, 55696*KG, 56169*KG, 56644*KG, 57121*KG, 
						 57600*KG, 58081*KG, 58564*KG, 59049*KG, 59536*KG, 60025*KG, 60516*KG, 61009*KG, 61504*KG, 62001*KG, 62500*KG, 63001*KG, 63504*KG, 64009*KG, 64516*KG, 65025*KG}; 

// Table for fast implementation of squaring for numbers in the interval [-255, 255] multiplied by the perceptual weight for blue.
const unsigned int square_table_percep_blue[511] = {
                         65025*KB, 64516*KB, 64009*KB, 63504*KB, 63001*KB, 62500*KB, 62001*KB, 61504*KB, 61009*KB, 60516*KB, 60025*KB, 59536*KB, 59049*KB, 58564*KB, 58081*KB, 57600*KB, 
						 57121*KB, 56644*KB, 56169*KB, 55696*KB, 55225*KB, 54756*KB, 54289*KB, 53824*KB, 53361*KB, 52900*KB, 52441*KB, 51984*KB, 51529*KB, 51076*KB, 50625*KB, 50176*KB, 
						 49729*KB, 49284*KB, 48841*KB, 48400*KB, 47961*KB, 47524*KB, 47089*KB, 46656*KB, 46225*KB, 45796*KB, 45369*KB, 44944*KB, 44521*KB, 44100*KB, 43681*KB, 43264*KB, 
						 42849*KB, 42436*KB, 42025*KB, 41616*KB, 41209*KB, 40804*KB, 40401*KB, 40000*KB, 39601*KB, 39204*KB, 38809*KB, 38416*KB, 38025*KB, 37636*KB, 37249*KB, 36864*KB, 
						 36481*KB, 36100*KB, 35721*KB, 35344*KB, 34969*KB, 34596*KB, 34225*KB, 33856*KB, 33489*KB, 33124*KB, 32761*KB, 32400*KB, 32041*KB, 31684*KB, 31329*KB, 30976*KB, 
						 30625*KB, 30276*KB, 29929*KB, 29584*KB, 29241*KB, 28900*KB, 28561*KB, 28224*KB, 27889*KB, 27556*KB, 27225*KB, 26896*KB, 26569*KB, 26244*KB, 25921*KB, 25600*KB, 
						 25281*KB, 24964*KB, 24649*KB, 24336*KB, 24025*KB, 23716*KB, 23409*KB, 23104*KB, 22801*KB, 22500*KB, 22201*KB, 21904*KB, 21609*KB, 21316*KB, 21025*KB, 20736*KB, 
						 20449*KB, 20164*KB, 19881*KB, 19600*KB, 19321*KB, 19044*KB, 18769*KB, 18496*KB, 18225*KB, 17956*KB, 17689*KB, 17424*KB, 17161*KB, 16900*KB, 16641*KB, 16384*KB, 
						 16129*KB, 15876*KB, 15625*KB, 15376*KB, 15129*KB, 14884*KB, 14641*KB, 14400*KB, 14161*KB, 13924*KB, 13689*KB, 13456*KB, 13225*KB, 12996*KB, 12769*KB, 12544*KB, 
						 12321*KB, 12100*KB, 11881*KB, 11664*KB, 11449*KB, 11236*KB, 11025*KB, 10816*KB, 10609*KB, 10404*KB, 10201*KB, 10000*KB, 9801*KB, 9604*KB, 9409*KB, 9216*KB, 
						 9025*KB, 8836*KB, 8649*KB, 8464*KB, 8281*KB, 8100*KB, 7921*KB, 7744*KB, 7569*KB, 7396*KB, 7225*KB, 7056*KB, 6889*KB, 6724*KB, 6561*KB, 6400*KB, 
						 6241*KB, 6084*KB, 5929*KB, 5776*KB, 5625*KB, 5476*KB, 5329*KB, 5184*KB, 5041*KB, 4900*KB, 4761*KB, 4624*KB, 4489*KB, 4356*KB, 4225*KB, 4096*KB, 
						 3969*KB, 3844*KB, 3721*KB, 3600*KB, 3481*KB, 3364*KB, 3249*KB, 3136*KB, 3025*KB, 2916*KB, 2809*KB, 2704*KB, 2601*KB, 2500*KB, 2401*KB, 2304*KB, 
						 2209*KB, 2116*KB, 2025*KB, 1936*KB, 1849*KB, 1764*KB, 1681*KB, 1600*KB, 1521*KB, 1444*KB, 1369*KB, 1296*KB, 1225*KB, 1156*KB, 1089*KB, 1024*KB, 
						 961*KB, 900*KB, 841*KB, 784*KB, 729*KB, 676*KB, 625*KB, 576*KB, 529*KB, 484*KB, 441*KB, 400*KB, 361*KB, 324*KB, 289*KB, 256*KB,
						 225*KB, 196*KB, 169*KB, 144*KB, 121*KB, 100*KB, 81*KB, 64*KB, 49*KB, 36*KB, 25*KB, 16*KB, 9*KB, 4*KB, 1*KB, 
						 0*KB, 1*KB, 4*KB, 9*KB, 16*KB, 25*KB, 36*KB, 49*KB, 64*KB, 81*KB, 100*KB, 121*KB, 144*KB, 169*KB, 196*KB, 225*KB, 
						 256*KB, 289*KB, 324*KB, 361*KB, 400*KB, 441*KB, 484*KB, 529*KB, 576*KB, 625*KB, 676*KB, 729*KB, 784*KB, 841*KB, 900*KB, 961*KB, 
						 1024*KB, 1089*KB, 1156*KB, 1225*KB, 1296*KB, 1369*KB, 1444*KB, 1521*KB, 1600*KB, 1681*KB, 1764*KB, 1849*KB, 1936*KB, 2025*KB, 2116*KB, 2209*KB, 
						 2304*KB, 2401*KB, 2500*KB, 2601*KB, 2704*KB, 2809*KB, 2916*KB, 3025*KB, 3136*KB, 3249*KB, 3364*KB, 3481*KB, 3600*KB, 3721*KB, 3844*KB, 3969*KB, 
						 4096*KB, 4225*KB, 4356*KB, 4489*KB, 4624*KB, 4761*KB, 4900*KB, 5041*KB, 5184*KB, 5329*KB, 5476*KB, 5625*KB, 5776*KB, 5929*KB, 6084*KB, 6241*KB, 
						 6400*KB, 6561*KB, 6724*KB, 6889*KB, 7056*KB, 7225*KB, 7396*KB, 7569*KB, 7744*KB, 7921*KB, 8100*KB, 8281*KB, 8464*KB, 8649*KB, 8836*KB, 9025*KB, 
						 9216*KB, 9409*KB, 9604*KB, 9801*KB, 10000*KB, 10201*KB, 10404*KB, 10609*KB, 10816*KB, 11025*KB, 11236*KB, 11449*KB, 11664*KB, 11881*KB, 12100*KB, 12321*KB,
						 12544*KB, 12769*KB, 12996*KB, 13225*KB, 13456*KB, 13689*KB, 13924*KB, 14161*KB, 14400*KB, 14641*KB, 14884*KB, 15129*KB, 15376*KB, 15625*KB, 15876*KB, 16129*KB,
						 16384*KB, 16641*KB, 16900*KB, 17161*KB, 17424*KB, 17689*KB, 17956*KB, 18225*KB, 18496*KB, 18769*KB, 19044*KB, 19321*KB, 19600*KB, 19881*KB, 20164*KB, 20449*KB, 
						 20736*KB, 21025*KB, 21316*KB, 21609*KB, 21904*KB, 22201*KB, 22500*KB, 22801*KB, 23104*KB, 23409*KB, 23716*KB, 24025*KB, 24336*KB, 24649*KB, 24964*KB, 25281*KB, 
						 25600*KB, 25921*KB, 26244*KB, 26569*KB, 26896*KB, 27225*KB, 27556*KB, 27889*KB, 28224*KB, 28561*KB, 28900*KB, 29241*KB, 29584*KB, 29929*KB, 30276*KB, 30625*KB, 
						 30976*KB, 31329*KB, 31684*KB, 32041*KB, 32400*KB, 32761*KB, 33124*KB, 33489*KB, 33856*KB, 34225*KB, 34596*KB, 34969*KB, 35344*KB, 35721*KB, 36100*KB, 36481*KB, 
						 36864*KB, 37249*KB, 37636*KB, 38025*KB, 38416*KB, 38809*KB, 39204*KB, 39601*KB, 40000*KB, 40401*KB, 40804*KB, 41209*KB, 41616*KB, 42025*KB, 42436*KB, 42849*KB, 
						 43264*KB, 43681*KB, 44100*KB, 44521*KB, 44944*KB, 45369*KB, 45796*KB, 46225*KB, 46656*KB, 47089*KB, 47524*KB, 47961*KB, 48400*KB, 48841*KB, 49284*KB, 49729*KB, 
						 50176*KB, 50625*KB, 51076*KB, 51529*KB, 51984*KB, 52441*KB, 52900*KB, 53361*KB, 53824*KB, 54289*KB, 54756*KB, 55225*KB, 55696*KB, 56169*KB, 56644*KB, 57121*KB, 
						 57600*KB, 58081*KB, 58564*KB, 59049*KB, 59536*KB, 60025*KB, 60516*KB, 61009*KB, 61504*KB, 62001*KB, 62500*KB, 63001*KB, 63504*KB, 64009*KB, 64516*KB, 65025*KB}; 

// Find the best table to use for a 2x4 area by testing all.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
int tryalltables_3bittable2x4(uint8 *img,int width,int height,int startx,int starty,uint8 *avg_color, unsigned int &best_table,unsigned int &best_pixel_indices_MSB, unsigned int &best_pixel_indices_LSB)
{
	int min_error = 3*255*255*16;
	int q;
	int err;
	unsigned int pixel_indices_MSB, pixel_indices_LSB;

	for(q=0;q<16;q+=2)		// try all the 8 tables. 
	{
		err=compressBlockWithTable2x4(img,width,height,startx,starty,avg_color,q,&pixel_indices_MSB, &pixel_indices_LSB);

		if(err<min_error)
		{
			min_error=err;
			best_pixel_indices_MSB = pixel_indices_MSB;
			best_pixel_indices_LSB = pixel_indices_LSB;
			best_table=q >> 1;
		}
	}
	return min_error;
}

// Find the best table to use for a 2x4 area by testing all.
// Uses perceptual weighting. 
// Uses fixed point implementation where 1000 equals 1.0
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int tryalltables_3bittable2x4percep1000(uint8 *img,int width,int height,int startx,int starty,uint8 *avg_color, unsigned int &best_table,unsigned int &best_pixel_indices_MSB, unsigned int &best_pixel_indices_LSB)
{
	unsigned int min_error = MAXERR1000;
	int q;
	unsigned int err;
	unsigned int pixel_indices_MSB, pixel_indices_LSB;

	for(q=0;q<16;q+=2)		// try all the 8 tables. 
	{

		err=compressBlockWithTable2x4percep1000(img,width,height,startx,starty,avg_color,q,&pixel_indices_MSB, &pixel_indices_LSB);

		if(err<min_error)
		{

			min_error=err;
			best_pixel_indices_MSB = pixel_indices_MSB;
			best_pixel_indices_LSB = pixel_indices_LSB;
			best_table=q >> 1;

		}
	}
	return min_error;
}

// Find the best table to use for a 2x4 area by testing all.
// Uses perceptual weighting. 
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
int tryalltables_3bittable2x4percep(uint8 *img,int width,int height,int startx,int starty,uint8 *avg_color, unsigned int &best_table,unsigned int &best_pixel_indices_MSB, unsigned int &best_pixel_indices_LSB)
{
	float min_error = 3*255*255*16;
	int q;
	float err;
	unsigned int pixel_indices_MSB, pixel_indices_LSB;

	for(q=0;q<16;q+=2)		// try all the 8 tables. 
	{
		err=compressBlockWithTable2x4percep(img,width,height,startx,starty,avg_color,q,&pixel_indices_MSB, &pixel_indices_LSB);

		if(err<min_error)
		{

			min_error=err;
			best_pixel_indices_MSB = pixel_indices_MSB;
			best_pixel_indices_LSB = pixel_indices_LSB;
			best_table=q >> 1;
		}
	}
	return (int) min_error;
}

// Find the best table to use for a 4x2 area by testing all.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
int tryalltables_3bittable4x2(uint8 *img,int width,int height,int startx,int starty,uint8 *avg_color, unsigned int &best_table,unsigned int &best_pixel_indices_MSB, unsigned int &best_pixel_indices_LSB)
{
	int min_error = 3*255*255*16;
	int q;
	int err;
	unsigned int pixel_indices_MSB, pixel_indices_LSB;

	for(q=0;q<16;q+=2)		// try all the 8 tables. 
	{
		err=compressBlockWithTable4x2(img,width,height,startx,starty,avg_color,q,&pixel_indices_MSB, &pixel_indices_LSB);

		if(err<min_error)
		{

			min_error=err;
			best_pixel_indices_MSB = pixel_indices_MSB;
			best_pixel_indices_LSB = pixel_indices_LSB;
			best_table=q >> 1;
		}
	}
	return min_error;
}

// Find the best table to use for a 4x2 area by testing all.
// Uses perceptual weighting. 
// Uses fixed point implementation where 1000 equals 1.0
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int tryalltables_3bittable4x2percep1000(uint8 *img,int width,int height,int startx,int starty,uint8 *avg_color, unsigned int &best_table,unsigned int &best_pixel_indices_MSB, unsigned int &best_pixel_indices_LSB)
{
	unsigned int min_error = MAXERR1000;
	int q;
	unsigned int err;
	unsigned int pixel_indices_MSB, pixel_indices_LSB;

	for(q=0;q<16;q+=2)		// try all the 8 tables. 
	{
		err=compressBlockWithTable4x2percep1000(img,width,height,startx,starty,avg_color,q,&pixel_indices_MSB, &pixel_indices_LSB);

		if(err<min_error)
		{
			min_error=err;
			best_pixel_indices_MSB = pixel_indices_MSB;
			best_pixel_indices_LSB = pixel_indices_LSB;
			best_table=q >> 1;
		}
	}
	return min_error;
}

// Find the best table to use for a 4x2 area by testing all.
// Uses perceptual weighting. 
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
int tryalltables_3bittable4x2percep(uint8 *img,int width,int height,int startx,int starty,uint8 *avg_color, unsigned int &best_table,unsigned int &best_pixel_indices_MSB, unsigned int &best_pixel_indices_LSB)
{
	float min_error = 3*255*255*16;
	int q;
	float err;
	unsigned int pixel_indices_MSB, pixel_indices_LSB;

	for(q=0;q<16;q+=2)		// try all the 8 tables. 
	{
		err=compressBlockWithTable4x2percep(img,width,height,startx,starty,avg_color,q,&pixel_indices_MSB, &pixel_indices_LSB);

		if(err<min_error)
		{
			min_error=err;
			best_pixel_indices_MSB = pixel_indices_MSB;
			best_pixel_indices_LSB = pixel_indices_LSB;
			best_table=q >> 1;
		}
	}
	return (int) min_error;
}

// The below code quantizes a float RGB value to RGB444. 
//
// The format often allows a pixel to completely compensate an intensity error of the base
// color. Hence the closest RGB444 point may not be the best, and the code below uses
// this fact to find a better RGB444 color as the base color.
//
// (See the presentation http://www.jacobstrom.com/publications/PACKMAN.ppt for more info.) 
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void quantize444ColorCombined(float *avg_col_in, int *enc_color, uint8 *avg_color)
{
	float dr, dg, db;
	float kr, kg, kb;
	float wR2, wG2, wB2;
	uint8 low_color[3];
	uint8 high_color[3];
	float min_error=255*255*8*3;
	float lowhightable[8];
	unsigned int best_table=0;
	unsigned int best_index=0;
	int q;
	float kval = (float) (255.0/15.0);

	// These are the values that we want to have:
	float red_average, green_average, blue_average;

	int red_4bit_low, green_4bit_low, blue_4bit_low;
	int red_4bit_high, green_4bit_high, blue_4bit_high;
	
	// These are the values that we approximate with:
	int red_low, green_low, blue_low;
	int red_high, green_high, blue_high;

	red_average = avg_col_in[0];
	green_average = avg_col_in[1];
	blue_average = avg_col_in[2];

	// Find the 5-bit reconstruction levels red_low, red_high
	// so that red_average is in interval [red_low, red_high].
	// (The same with green and blue.)

	red_4bit_low = (int) (red_average/kval);
	green_4bit_low = (int) (green_average/kval);
	blue_4bit_low = (int) (blue_average/kval);

	red_4bit_high = CLAMP(0, red_4bit_low + 1, 15);
	green_4bit_high  = CLAMP(0, green_4bit_low + 1, 15);
	blue_4bit_high = CLAMP(0, blue_4bit_low + 1, 15);

	red_low   = (red_4bit_low << 4) | (red_4bit_low >> 0);
	green_low = (green_4bit_low << 4) | (green_4bit_low >> 0);
	blue_low = (blue_4bit_low << 4) | (blue_4bit_low >> 0);

	red_high   = (red_4bit_high << 4) | (red_4bit_high >> 0);
	green_high = (green_4bit_high << 4) | (green_4bit_high >> 0);
	blue_high = (blue_4bit_high << 4) | (blue_4bit_high >> 0);

	kr = (float)red_high - (float)red_low;
	kg = (float)green_high - (float)green_low;
	kb = (float)blue_high - (float)blue_low;

	// Note that dr, dg, and db are all negative.
	dr = red_low - red_average;
	dg = green_low - green_average;
	db = blue_low - blue_average;

	// Use straight (nonperceptive) weights.
	wR2 = (float) 1.0;
	wG2 = (float) 1.0;
	wB2 = (float) 1.0;

	lowhightable[0] = wR2*wG2*SQUARE( (dr+ 0) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+ 0) );
	lowhightable[1] = wR2*wG2*SQUARE( (dr+kr) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+kr) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+ 0) );
	lowhightable[2] = wR2*wG2*SQUARE( (dr+ 0) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+kg) - (db+ 0) );
	lowhightable[3] = wR2*wG2*SQUARE( (dr+ 0) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+kb) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+kb) );
	lowhightable[4] = wR2*wG2*SQUARE( (dr+kr) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+kr) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+kg) - (db+ 0) );
	lowhightable[5] = wR2*wG2*SQUARE( (dr+kr) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+kr) - (db+kb) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+kb) );
	lowhightable[6] = wR2*wG2*SQUARE( (dr+ 0) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+kb) ) + wG2*wB2*SQUARE( (dg+kg) - (db+kb) );
	lowhightable[7] = wR2*wG2*SQUARE( (dr+kr) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+kr) - (db+kb) ) + wG2*wB2*SQUARE( (dg+kg) - (db+kb) );

	float min_value = lowhightable[0];
	int min_index = 0;

	for(q = 1; q<8; q++)
	{
		if(lowhightable[q] < min_value)
		{
			min_value = lowhightable[q];
			min_index = q;
		}
	}

  float drh = red_high-red_average;
	float dgh = green_high-green_average;
	float dbh = blue_high-blue_average;

	low_color[0] = red_4bit_low;
	low_color[1] = green_4bit_low;
	low_color[2] = blue_4bit_low;

	high_color[0] = red_4bit_high;
	high_color[1] = green_4bit_high;
	high_color[2] = blue_4bit_high;

	switch(min_index)
	{
	case 0:
		// Since the step size is always 17 in RGB444 format (15*17=255),
		// kr = kg = kb = 17, which means that case 0 and case 7 will
		// always have equal projected error. Choose the one that is
		// closer to the desired color. 
		if(dr*dr + dg*dg + db*db > 3*8*8)
		{
			enc_color[0] = high_color[0];
			enc_color[1] = high_color[1];
			enc_color[2] = high_color[2];
		}
		else
		{
			enc_color[0] = low_color[0];
			enc_color[1] = low_color[1];
			enc_color[2] = low_color[2];
		}
		break;
	case 1:
		enc_color[0] = high_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = low_color[2];
		break;
	case 2:	
		enc_color[0] = low_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = low_color[2];
		break;
	case 3:	
		enc_color[0] = low_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = high_color[2];
		break;
	case 4:	
		enc_color[0] = high_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = low_color[2];
		break;
	case 5:	
		enc_color[0] = high_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = high_color[2];
		break;
	case 6:	
		enc_color[0] = low_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = high_color[2];
		break;
	case 7:	
		if(dr*dr + dg*dg + db*db > 3*8*8)
		{
			enc_color[0] = high_color[0];
			enc_color[1] = high_color[1];
			enc_color[2] = high_color[2];
		}
		else
		{
			enc_color[0] = low_color[0];
			enc_color[1] = low_color[1];
			enc_color[2] = low_color[2];
		}
		break;
	}
	// Expand 5-bit encoded color to 8-bit color
	avg_color[0] = (enc_color[0] << 3) | (enc_color[0] >> 2);
	avg_color[1] = (enc_color[1] << 3) | (enc_color[1] >> 2);
	avg_color[2] = (enc_color[2] << 3) | (enc_color[2] >> 2);	
}

// The below code quantizes a float RGB value to RGB555. 
//
// The format often allows a pixel to completely compensate an intensity error of the base
// color. Hence the closest RGB555 point may not be the best, and the code below uses
// this fact to find a better RGB555 color as the base color.
//
// (See the presentation http://www.jacobstrom.com/publications/PACKMAN.ppt for more info.) 
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void quantize555ColorCombined(float *avg_col_in, int *enc_color, uint8 *avg_color)
{
	float dr, dg, db;
	float kr, kg, kb;
	float wR2, wG2, wB2;
	uint8 low_color[3];
	uint8 high_color[3];
	float min_error=255*255*8*3;
	float lowhightable[8];
	unsigned int best_table=0;
	unsigned int best_index=0;
	int q;
	float kval = (float) (255.0/31.0);

	// These are the values that we want to have:
	float red_average, green_average, blue_average;

	int red_5bit_low, green_5bit_low, blue_5bit_low;
	int red_5bit_high, green_5bit_high, blue_5bit_high;
	
	// These are the values that we approximate with:
	int red_low, green_low, blue_low;
	int red_high, green_high, blue_high;

	red_average = avg_col_in[0];
	green_average = avg_col_in[1];
	blue_average = avg_col_in[2];

	// Find the 5-bit reconstruction levels red_low, red_high
	// so that red_average is in interval [red_low, red_high].
	// (The same with green and blue.)

	red_5bit_low = (int) (red_average/kval);
	green_5bit_low = (int) (green_average/kval);
	blue_5bit_low = (int) (blue_average/kval);

	red_5bit_high = CLAMP(0, red_5bit_low + 1, 31);
	green_5bit_high  = CLAMP(0, green_5bit_low + 1, 31);
	blue_5bit_high = CLAMP(0, blue_5bit_low + 1, 31);

	red_low   = (red_5bit_low << 3) | (red_5bit_low >> 2);
	green_low = (green_5bit_low << 3) | (green_5bit_low >> 2);
	blue_low = (blue_5bit_low << 3) | (blue_5bit_low >> 2);

	red_high   = (red_5bit_high << 3) | (red_5bit_high >> 2);
	green_high = (green_5bit_high << 3) | (green_5bit_high >> 2);
	blue_high = (blue_5bit_high << 3) | (blue_5bit_high >> 2);

	kr = (float)red_high - (float)red_low;
	kg = (float)green_high - (float)green_low;
	kb = (float)blue_high - (float)blue_low;

	// Note that dr, dg, and db are all negative.
	dr = red_low - red_average;
	dg = green_low - green_average;
	db = blue_low - blue_average;

	// Use straight (nonperceptive) weights.
	wR2 = (float) 1.0;
	wG2 = (float) 1.0;
	wB2 = (float) 1.0;

	lowhightable[0] = wR2*wG2*SQUARE( (dr+ 0) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+ 0) );
	lowhightable[1] = wR2*wG2*SQUARE( (dr+kr) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+kr) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+ 0) );
	lowhightable[2] = wR2*wG2*SQUARE( (dr+ 0) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+kg) - (db+ 0) );
	lowhightable[3] = wR2*wG2*SQUARE( (dr+ 0) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+kb) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+kb) );
	lowhightable[4] = wR2*wG2*SQUARE( (dr+kr) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+kr) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+kg) - (db+ 0) );
	lowhightable[5] = wR2*wG2*SQUARE( (dr+kr) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+kr) - (db+kb) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+kb) );
	lowhightable[6] = wR2*wG2*SQUARE( (dr+ 0) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+kb) ) + wG2*wB2*SQUARE( (dg+kg) - (db+kb) );
	lowhightable[7] = wR2*wG2*SQUARE( (dr+kr) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+kr) - (db+kb) ) + wG2*wB2*SQUARE( (dg+kg) - (db+kb) );

	float	min_value = lowhightable[0];
	int min_index = 0;

	for(q = 1; q<8; q++)
	{
		if(lowhightable[q] < min_value)
		{
			min_value = lowhightable[q];
			min_index = q;
		}
	}

  float drh = red_high-red_average;
	float dgh = green_high-green_average;
	float dbh = blue_high-blue_average;

	low_color[0] = red_5bit_low;
	low_color[1] = green_5bit_low;
	low_color[2] = blue_5bit_low;

	high_color[0] = red_5bit_high;
	high_color[1] = green_5bit_high;
	high_color[2] = blue_5bit_high;

	switch(min_index)
	{
	case 0:
		enc_color[0] = low_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = low_color[2];
		break;
	case 1:
		enc_color[0] = high_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = low_color[2];
		break;
	case 2:	
		enc_color[0] = low_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = low_color[2];
		break;
	case 3:	
		enc_color[0] = low_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = high_color[2];
		break;
	case 4:	
		enc_color[0] = high_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = low_color[2];
		break;
	case 5:	
		enc_color[0] = high_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = high_color[2];
		break;
	case 6:	
		enc_color[0] = low_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = high_color[2];
		break;
	case 7:	
		enc_color[0] = high_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = high_color[2];
		break;
	}

	// Expand 5-bit encoded color to 8-bit color
	avg_color[0] = (enc_color[0] << 3) | (enc_color[0] >> 2);
	avg_color[1] = (enc_color[1] << 3) | (enc_color[1] >> 2);
	avg_color[2] = (enc_color[2] << 3) | (enc_color[2] >> 2);
	
}

// The below code quantizes a float RGB value to RGB444. 
//
// The format often allows a pixel to completely compensate an intensity error of the base
// color. Hence the closest RGB444 point may not be the best, and the code below uses
// this fact to find a better RGB444 color as the base color.
//
// (See the presentation http://www.jacobstrom.com/publications/PACKMAN.ppt for more info.) 
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void quantize444ColorCombinedPerceptual(float *avg_col_in, int *enc_color, uint8 *avg_color)
{
	float dr, dg, db;
	float kr, kg, kb;
	float wR2, wG2, wB2;
	uint8 low_color[3];
	uint8 high_color[3];
	float min_error=255*255*8*3;
	float lowhightable[8];
	unsigned int best_table=0;
	unsigned int best_index=0;
	int q;
	float kval = (float) (255.0/15.0);

	// These are the values that we want to have:
	float red_average, green_average, blue_average;

	int red_4bit_low, green_4bit_low, blue_4bit_low;
	int red_4bit_high, green_4bit_high, blue_4bit_high;
	
	// These are the values that we approximate with:
	int red_low, green_low, blue_low;
	int red_high, green_high, blue_high;

	red_average = avg_col_in[0];
	green_average = avg_col_in[1];
	blue_average = avg_col_in[2];

	// Find the 5-bit reconstruction levels red_low, red_high
	// so that red_average is in interval [red_low, red_high].
	// (The same with green and blue.)

	red_4bit_low = (int) (red_average/kval);
	green_4bit_low = (int) (green_average/kval);
	blue_4bit_low = (int) (blue_average/kval);

	red_4bit_high = CLAMP(0, red_4bit_low + 1, 15);
	green_4bit_high  = CLAMP(0, green_4bit_low + 1, 15);
	blue_4bit_high = CLAMP(0, blue_4bit_low + 1, 15);

	red_low   = (red_4bit_low << 4) | (red_4bit_low >> 0);
	green_low = (green_4bit_low << 4) | (green_4bit_low >> 0);
	blue_low = (blue_4bit_low << 4) | (blue_4bit_low >> 0);

	red_high   = (red_4bit_high << 4) | (red_4bit_high >> 0);
	green_high = (green_4bit_high << 4) | (green_4bit_high >> 0);
	blue_high = (blue_4bit_high << 4) | (blue_4bit_high >> 0);

	low_color[0] = red_4bit_low;
	low_color[1] = green_4bit_low;
	low_color[2] = blue_4bit_low;

	high_color[0] = red_4bit_high;
	high_color[1] = green_4bit_high;
	high_color[2] = blue_4bit_high;

	kr = (float)red_high - (float)red_low;
	kg = (float)green_high - (float)green_low;
	kb = (float)blue_high- (float)blue_low;

	// Note that dr, dg, and db are all negative.
	dr = red_low - red_average;
	dg = green_low - green_average;
	db = blue_low - blue_average;

	// Perceptual weights to use
	wR2 = (float) PERCEPTUAL_WEIGHT_R_SQUARED; 
	wG2 = (float) PERCEPTUAL_WEIGHT_G_SQUARED; 
	wB2 = (float) PERCEPTUAL_WEIGHT_B_SQUARED;

	lowhightable[0] = wR2*wG2*SQUARE( (dr+ 0) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+ 0) );
	lowhightable[1] = wR2*wG2*SQUARE( (dr+kr) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+kr) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+ 0) );
	lowhightable[2] = wR2*wG2*SQUARE( (dr+ 0) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+kg) - (db+ 0) );
	lowhightable[3] = wR2*wG2*SQUARE( (dr+ 0) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+kb) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+kb) );
	lowhightable[4] = wR2*wG2*SQUARE( (dr+kr) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+kr) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+kg) - (db+ 0) );
	lowhightable[5] = wR2*wG2*SQUARE( (dr+kr) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+kr) - (db+kb) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+kb) );
	lowhightable[6] = wR2*wG2*SQUARE( (dr+ 0) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+kb) ) + wG2*wB2*SQUARE( (dg+kg) - (db+kb) );
	lowhightable[7] = wR2*wG2*SQUARE( (dr+kr) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+kr) - (db+kb) ) + wG2*wB2*SQUARE( (dg+kg) - (db+kb) );

	float min_value = lowhightable[0];
	int min_index = 0;

	for(q = 1; q<8; q++)
	{
		if(lowhightable[q] < min_value)
		{
			min_value = lowhightable[q];
			min_index = q;
		}
	}

  float drh = red_high-red_average;
	float dgh = green_high-green_average;
	float dbh = blue_high-blue_average;

	switch(min_index)
	{
	case 0:
		enc_color[0] = low_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = low_color[2];
		break;
	case 1:
		enc_color[0] = high_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = low_color[2];
		break;
	case 2:	
		enc_color[0] = low_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = low_color[2];
		break;
	case 3:	
		enc_color[0] = low_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = high_color[2];
		break;
	case 4:	
		enc_color[0] = high_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = low_color[2];
		break;
	case 5:	
		enc_color[0] = high_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = high_color[2];
		break;
	case 6:	
		enc_color[0] = low_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = high_color[2];
		break;
	case 7:	
		enc_color[0] = high_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = high_color[2];
		break;
	}

	// Expand encoded color to eight bits
	avg_color[0] = (enc_color[0] << 4) | enc_color[0];
	avg_color[1] = (enc_color[1] << 4) | enc_color[1];
	avg_color[2] = (enc_color[2] << 4) | enc_color[2];
}

// The below code quantizes a float RGB value to RGB555. 
//
// The format often allows a pixel to completely compensate an intensity error of the base
// color. Hence the closest RGB555 point may not be the best, and the code below uses
// this fact to find a better RGB555 color as the base color.
//
// (See the presentation http://www.jacobstrom.com/publications/PACKMAN.ppt for more info.) 
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void quantize555ColorCombinedPerceptual(float *avg_col_in, int *enc_color, uint8 *avg_color)
{
	float dr, dg, db;
	float kr, kg, kb;
	float wR2, wG2, wB2;
	uint8 low_color[3];
	uint8 high_color[3];
	float min_error=255*255*8*3;
	float lowhightable[8];
	unsigned int best_table=0;
	unsigned int best_index=0;
	int q;
	float kval = (float) (255.0/31.0);

	// These are the values that we want to have:
	float red_average, green_average, blue_average;

	int red_5bit_low, green_5bit_low, blue_5bit_low;
	int red_5bit_high, green_5bit_high, blue_5bit_high;
	
	// These are the values that we approximate with:
	int red_low, green_low, blue_low;
	int red_high, green_high, blue_high;

	red_average = avg_col_in[0];
	green_average = avg_col_in[1];
	blue_average = avg_col_in[2];

	// Find the 5-bit reconstruction levels red_low, red_high
	// so that red_average is in interval [red_low, red_high].
	// (The same with green and blue.)

	red_5bit_low = (int) (red_average/kval);
	green_5bit_low = (int) (green_average/kval);
	blue_5bit_low = (int) (blue_average/kval);

	red_5bit_high = CLAMP(0, red_5bit_low + 1, 31);
	green_5bit_high  = CLAMP(0, green_5bit_low + 1, 31);
	blue_5bit_high = CLAMP(0, blue_5bit_low + 1, 31);

	red_low   = (red_5bit_low << 3) | (red_5bit_low >> 2);
	green_low = (green_5bit_low << 3) | (green_5bit_low >> 2);
	blue_low = (blue_5bit_low << 3) | (blue_5bit_low >> 2);

	red_high   = (red_5bit_high << 3) | (red_5bit_high >> 2);
	green_high = (green_5bit_high << 3) | (green_5bit_high >> 2);
	blue_high = (blue_5bit_high << 3) | (blue_5bit_high >> 2);

	low_color[0] = red_5bit_low;
	low_color[1] = green_5bit_low;
	low_color[2] = blue_5bit_low;

	high_color[0] = red_5bit_high;
	high_color[1] = green_5bit_high;
	high_color[2] = blue_5bit_high;

	kr = (float)red_high - (float)red_low;
	kg = (float)green_high - (float)green_low;
	kb = (float)blue_high - (float)blue_low;

	// Note that dr, dg, and db are all negative.
	dr = red_low - red_average;
	dg = green_low - green_average;
	db = blue_low - blue_average;

	// Perceptual weights to use
	wR2 = (float) PERCEPTUAL_WEIGHT_R_SQUARED; 
	wG2 = (float) PERCEPTUAL_WEIGHT_G_SQUARED; 
	wB2 = (float) PERCEPTUAL_WEIGHT_B_SQUARED;

	lowhightable[0] = wR2*wG2*SQUARE( (dr+ 0) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+ 0) );
	lowhightable[1] = wR2*wG2*SQUARE( (dr+kr) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+kr) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+ 0) );
	lowhightable[2] = wR2*wG2*SQUARE( (dr+ 0) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+kg) - (db+ 0) );
	lowhightable[3] = wR2*wG2*SQUARE( (dr+ 0) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+kb) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+kb) );
	lowhightable[4] = wR2*wG2*SQUARE( (dr+kr) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+kr) - (db+ 0) ) + wG2*wB2*SQUARE( (dg+kg) - (db+ 0) );
	lowhightable[5] = wR2*wG2*SQUARE( (dr+kr) - (dg+ 0) ) + wR2*wB2*SQUARE( (dr+kr) - (db+kb) ) + wG2*wB2*SQUARE( (dg+ 0) - (db+kb) );
	lowhightable[6] = wR2*wG2*SQUARE( (dr+ 0) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+ 0) - (db+kb) ) + wG2*wB2*SQUARE( (dg+kg) - (db+kb) );
	lowhightable[7] = wR2*wG2*SQUARE( (dr+kr) - (dg+kg) ) + wR2*wB2*SQUARE( (dr+kr) - (db+kb) ) + wG2*wB2*SQUARE( (dg+kg) - (db+kb) );

	float min_value = lowhightable[0];
	int min_index = 0;

	for(q = 1; q<8; q++)
	{
		if(lowhightable[q] < min_value)
		{
			min_value = lowhightable[q];
			min_index = q;
		}
	}

  float drh = red_high-red_average;
	float dgh = green_high-green_average;
	float dbh = blue_high-blue_average;

	switch(min_index)
	{
	case 0:
		enc_color[0] = low_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = low_color[2];
		break;
	case 1:
		enc_color[0] = high_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = low_color[2];
		break;
	case 2:	
		enc_color[0] = low_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = low_color[2];
		break;
	case 3:	
		enc_color[0] = low_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = high_color[2];
		break;
	case 4:	
		enc_color[0] = high_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = low_color[2];
		break;
	case 5:	
		enc_color[0] = high_color[0];
		enc_color[1] = low_color[1];
		enc_color[2] = high_color[2];
		break;
	case 6:	
		enc_color[0] = low_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = high_color[2];
		break;
	case 7:	
		enc_color[0] = high_color[0];
		enc_color[1] = high_color[1];
		enc_color[2] = high_color[2];
		break;
	}

	// Expand 5-bit encoded color to 8-bit color
	avg_color[0] = (enc_color[0] << 3) | (enc_color[0] >> 2);
	avg_color[1] = (enc_color[1] << 3) | (enc_color[1] >> 2);
	avg_color[2] = (enc_color[2] << 3) | (enc_color[2] >> 2);
}

// Compresses the block using only the individual mode in ETC1/ETC2 using the average color as the base color.
// Uses a perceptual error metric.
// Uses fixed point arithmetics where 1000 equals 1.0
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int compressBlockOnlyIndividualAveragePerceptual1000(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2, int *best_enc_color1, int*best_enc_color2, int &best_flip, unsigned int &best_err_upper, unsigned int &best_err_lower, unsigned int &best_err_left, unsigned int &best_err_right, int *best_color_upper, int *best_color_lower, int *best_color_left, int *best_color_right)
{
	unsigned int compressed1_norm, compressed2_norm;
	unsigned int compressed1_flip, compressed2_flip;
	uint8 avg_color_quant1[3], avg_color_quant2[3];

	float avg_color_float1[3],avg_color_float2[3];
	int enc_color1[3], enc_color2[3];
	unsigned int best_table_indices1=0, best_table_indices2=0;
	unsigned int best_table1=0, best_table2=0;
	int diffbit;

	unsigned int norm_err=0;
	unsigned int flip_err=0;
	unsigned int best_err;

	// First try normal blocks 2x4:

	computeAverageColor2x4noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor2x4noQuantFloat(img,width,height,startx+2,starty,avg_color_float2);

	enc_color1[0] = int( JAS_ROUND(15.0*avg_color_float1[0]/255.0) );
	enc_color1[1] = int( JAS_ROUND(15.0*avg_color_float1[1]/255.0) );
	enc_color1[2] = int( JAS_ROUND(15.0*avg_color_float1[2]/255.0) );
	enc_color2[0] = int( JAS_ROUND(15.0*avg_color_float2[0]/255.0) );
	enc_color2[1] = int( JAS_ROUND(15.0*avg_color_float2[1]/255.0) );
	enc_color2[2] = int( JAS_ROUND(15.0*avg_color_float2[2]/255.0) );

	diffbit = 0;

	avg_color_quant1[0] = enc_color1[0] << 4 | (enc_color1[0] );
	avg_color_quant1[1] = enc_color1[1] << 4 | (enc_color1[1] );
	avg_color_quant1[2] = enc_color1[2] << 4 | (enc_color1[2] );
	avg_color_quant2[0] = enc_color2[0] << 4 | (enc_color2[0] );
	avg_color_quant2[1] = enc_color2[1] << 4 | (enc_color2[1] );
	avg_color_quant2[2] = enc_color2[2] << 4 | (enc_color2[2] );

	// Pack bits into the first word. 

	//     ETC1_RGB8_OES:
	// 
	//     a) bit layout in bits 63 through 32 if diffbit = 0
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
	//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------
	//     
	//     b) bit layout in bits 63 through 32 if diffbit = 1
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |diff|flip|
	//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------
	// 
	//     c) bit layout in bits 31 through 0 (in both cases)
	// 
	//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3   2   1  0
	//      --------------------------------------------------------------------------------------------------
	//     |       most significant pixel index bits       |         least significant pixel index bits       |  
	//     | p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a| p| o| n| m| l| k| j| i| h| g| f| e| d| c | b | a |
	//      --------------------------------------------------------------------------------------------------      

	compressed1_norm = 0;
	PUTBITSHIGH( compressed1_norm, diffbit,       1, 33);
 	PUTBITSHIGH( compressed1_norm, enc_color1[0], 4, 63);
 	PUTBITSHIGH( compressed1_norm, enc_color1[1], 4, 55);
 	PUTBITSHIGH( compressed1_norm, enc_color1[2], 4, 47);
 	PUTBITSHIGH( compressed1_norm, enc_color2[0], 4, 59);
 	PUTBITSHIGH( compressed1_norm, enc_color2[1], 4, 51);
 	PUTBITSHIGH( compressed1_norm, enc_color2[1], 4, 43);

	unsigned int best_pixel_indices1_MSB;
	unsigned int best_pixel_indices1_LSB;
	unsigned int best_pixel_indices2_MSB;
	unsigned int best_pixel_indices2_LSB;

	best_enc_color1[0] = enc_color1[0];
	best_enc_color1[1] = enc_color1[1];
	best_enc_color1[2] = enc_color1[2];
	best_enc_color2[0] = enc_color2[0];
	best_enc_color2[1] = enc_color2[1];
	best_enc_color2[2] = enc_color2[2];
	
	best_color_left[0] = enc_color1[0];
	best_color_left[1] = enc_color1[1];
	best_color_left[2] = enc_color1[2];
	best_color_right[0] = enc_color2[0];
	best_color_right[1] = enc_color2[1];
	best_color_right[2] = enc_color2[2];

	norm_err = 0;

	// left part of block
	best_err_left = tryalltables_3bittable2x4percep1000(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
	norm_err = best_err_left;

	// right part of block
	best_err_right = tryalltables_3bittable2x4percep1000(img,width,height,startx+2,starty,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);
	norm_err += best_err_right;

 	PUTBITSHIGH( compressed1_norm, best_table1,   3, 39);
 	PUTBITSHIGH( compressed1_norm, best_table2,   3, 36);
 	PUTBITSHIGH( compressed1_norm,           0,   1, 32);

	compressed2_norm = 0;
	PUTBITS( compressed2_norm, (best_pixel_indices1_MSB     ), 8, 23);
	PUTBITS( compressed2_norm, (best_pixel_indices2_MSB     ), 8, 31);
	PUTBITS( compressed2_norm, (best_pixel_indices1_LSB     ), 8, 7);
	PUTBITS( compressed2_norm, (best_pixel_indices2_LSB     ), 8, 15);

	// Now try flipped blocks 4x2:

	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty+2,avg_color_float2);

	// First test if avg_color1 is similar enough to avg_color2 so that
	// we can use differential coding of colors. 

	enc_color1[0] = int( JAS_ROUND(15.0*avg_color_float1[0]/255.0) );
	enc_color1[1] = int( JAS_ROUND(15.0*avg_color_float1[1]/255.0) );
	enc_color1[2] = int( JAS_ROUND(15.0*avg_color_float1[2]/255.0) );
	enc_color2[0] = int( JAS_ROUND(15.0*avg_color_float2[0]/255.0) );
	enc_color2[1] = int( JAS_ROUND(15.0*avg_color_float2[1]/255.0) );
	enc_color2[2] = int( JAS_ROUND(15.0*avg_color_float2[2]/255.0) );

	best_color_upper[0] = enc_color1[0];
	best_color_upper[1] = enc_color1[1];
	best_color_upper[2] = enc_color1[2];
	best_color_lower[0] = enc_color2[0];
	best_color_lower[1] = enc_color2[1];
	best_color_lower[2] = enc_color2[2];

	diffbit = 0;

	avg_color_quant1[0] = enc_color1[0] << 4 | (enc_color1[0] );
	avg_color_quant1[1] = enc_color1[1] << 4 | (enc_color1[1] );
	avg_color_quant1[2] = enc_color1[2] << 4 | (enc_color1[2] );
	avg_color_quant2[0] = enc_color2[0] << 4 | (enc_color2[0] );
	avg_color_quant2[1] = enc_color2[1] << 4 | (enc_color2[1] );
	avg_color_quant2[2] = enc_color2[2] << 4 | (enc_color2[2] );

	// Pack bits into the first word. 

	compressed1_flip = 0;
	PUTBITSHIGH( compressed1_flip, diffbit,       1, 33);
 	PUTBITSHIGH( compressed1_flip, enc_color1[0], 4, 63);
 	PUTBITSHIGH( compressed1_flip, enc_color1[1], 4, 55);
 	PUTBITSHIGH( compressed1_flip, enc_color1[2], 4, 47);
 	PUTBITSHIGH( compressed1_flip, enc_color2[0], 4, 49);
 	PUTBITSHIGH( compressed1_flip, enc_color2[1], 4, 51);
 	PUTBITSHIGH( compressed1_flip, enc_color2[2], 4, 43);

	// upper part of block
	best_err_upper = tryalltables_3bittable4x2percep1000(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
	flip_err = best_err_upper;
	// lower part of block
	best_err_lower = tryalltables_3bittable4x2percep1000(img,width,height,startx,starty+2,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);
	flip_err += best_err_lower;

 	PUTBITSHIGH( compressed1_flip, best_table1,   3, 39);
 	PUTBITSHIGH( compressed1_flip, best_table2,   3, 36);
 	PUTBITSHIGH( compressed1_flip,           1,   1, 32);

	best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
	best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);
	
	compressed2_flip = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);

	// Now lets see which is the best table to use. Only 8 tables are possible. 

	if(norm_err <= flip_err)
	{
		compressed1 = compressed1_norm | 0;
		compressed2 = compressed2_norm;
		best_err = norm_err;
		best_flip = 0;
	}
	else
	{
		compressed1 = compressed1_flip | 1;
		compressed2 = compressed2_flip;
		best_err = flip_err;
		best_enc_color1[0] = enc_color1[0];
		best_enc_color1[1] = enc_color1[1];
		best_enc_color1[2] = enc_color1[2];
		best_enc_color2[0] = enc_color2[0];
		best_enc_color2[1] = enc_color2[1];
		best_enc_color2[2] = enc_color2[2];
		best_flip = 1;
	}
	return best_err;
}

// Compresses the block using only the individual mode in ETC1/ETC2 using the average color as the base color.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
int compressBlockOnlyIndividualAverage(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2, int *best_enc_color1, int*best_enc_color2, int &best_flip, unsigned int &best_err_upper, unsigned int &best_err_lower, unsigned int &best_err_left, unsigned int &best_err_right, int *best_color_upper, int *best_color_lower, int *best_color_left, int *best_color_right)
{
	unsigned int compressed1_norm, compressed2_norm;
	unsigned int compressed1_flip, compressed2_flip;
	uint8 avg_color_quant1[3], avg_color_quant2[3];

	float avg_color_float1[3],avg_color_float2[3];
	int enc_color1[3], enc_color2[3];
	int min_error=255*255*8*3;
	unsigned int best_table_indices1=0, best_table_indices2=0;
	unsigned int best_table1=0, best_table2=0;
	int diffbit;

	int norm_err=0;
	int flip_err=0;
	int best_err;

	// First try normal blocks 2x4:

	computeAverageColor2x4noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor2x4noQuantFloat(img,width,height,startx+2,starty,avg_color_float2);

	enc_color1[0] = int( JAS_ROUND(15.0*avg_color_float1[0]/255.0) );
	enc_color1[1] = int( JAS_ROUND(15.0*avg_color_float1[1]/255.0) );
	enc_color1[2] = int( JAS_ROUND(15.0*avg_color_float1[2]/255.0) );
	enc_color2[0] = int( JAS_ROUND(15.0*avg_color_float2[0]/255.0) );
	enc_color2[1] = int( JAS_ROUND(15.0*avg_color_float2[1]/255.0) );
	enc_color2[2] = int( JAS_ROUND(15.0*avg_color_float2[2]/255.0) );

	diffbit = 0;

	avg_color_quant1[0] = enc_color1[0] << 4 | (enc_color1[0] );
	avg_color_quant1[1] = enc_color1[1] << 4 | (enc_color1[1] );
	avg_color_quant1[2] = enc_color1[2] << 4 | (enc_color1[2] );
	avg_color_quant2[0] = enc_color2[0] << 4 | (enc_color2[0] );
	avg_color_quant2[1] = enc_color2[1] << 4 | (enc_color2[1] );
	avg_color_quant2[2] = enc_color2[2] << 4 | (enc_color2[2] );

	// Pack bits into the first word. 

	//     ETC1_RGB8_OES:
	// 
	//     a) bit layout in bits 63 through 32 if diffbit = 0
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
	//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------
	//     
	//     b) bit layout in bits 63 through 32 if diffbit = 1
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |diff|flip|
	//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------
	// 
	//     c) bit layout in bits 31 through 0 (in both cases)
	// 
	//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3   2   1  0
	//      --------------------------------------------------------------------------------------------------
	//     |       most significant pixel index bits       |         least significant pixel index bits       |  
	//     | p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a| p| o| n| m| l| k| j| i| h| g| f| e| d| c | b | a |
	//      --------------------------------------------------------------------------------------------------      

	compressed1_norm = 0;
	PUTBITSHIGH( compressed1_norm, diffbit,       1, 33);
 	PUTBITSHIGH( compressed1_norm, enc_color1[0], 4, 63);
 	PUTBITSHIGH( compressed1_norm, enc_color1[1], 4, 55);
 	PUTBITSHIGH( compressed1_norm, enc_color1[2], 4, 47);
 	PUTBITSHIGH( compressed1_norm, enc_color2[0], 4, 59);
 	PUTBITSHIGH( compressed1_norm, enc_color2[1], 4, 51);
 	PUTBITSHIGH( compressed1_norm, enc_color2[1], 4, 43);

	unsigned int best_pixel_indices1_MSB;
	unsigned int best_pixel_indices1_LSB;
	unsigned int best_pixel_indices2_MSB;
	unsigned int best_pixel_indices2_LSB;

	best_enc_color1[0] = enc_color1[0];
	best_enc_color1[1] = enc_color1[1];
	best_enc_color1[2] = enc_color1[2];
	best_enc_color2[0] = enc_color2[0];
	best_enc_color2[1] = enc_color2[1];
	best_enc_color2[2] = enc_color2[2];
	best_color_left[0] = enc_color1[0];
	best_color_left[1] = enc_color1[1];
	best_color_left[2] = enc_color1[2];
	best_color_right[0] = enc_color2[0];
	best_color_right[1] = enc_color2[1];
	best_color_right[2] = enc_color2[2];

	norm_err = 0;

	// left part of block
	best_err_left = tryalltables_3bittable2x4(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
	norm_err = best_err_left;

	// right part of block
	best_err_right = tryalltables_3bittable2x4(img,width,height,startx+2,starty,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);
	norm_err += best_err_right;

 	PUTBITSHIGH( compressed1_norm, best_table1,   3, 39);
 	PUTBITSHIGH( compressed1_norm, best_table2,   3, 36);
 	PUTBITSHIGH( compressed1_norm,           0,   1, 32);

	compressed2_norm = 0;
	PUTBITS( compressed2_norm, (best_pixel_indices1_MSB     ), 8, 23);
	PUTBITS( compressed2_norm, (best_pixel_indices2_MSB     ), 8, 31);
	PUTBITS( compressed2_norm, (best_pixel_indices1_LSB     ), 8, 7);
	PUTBITS( compressed2_norm, (best_pixel_indices2_LSB     ), 8, 15);


	// Now try flipped blocks 4x2:

	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty+2,avg_color_float2);

	// First test if avg_color1 is similar enough to avg_color2 so that
	// we can use differential coding of colors. 

	enc_color1[0] = int( JAS_ROUND(15.0*avg_color_float1[0]/255.0) );
	enc_color1[1] = int( JAS_ROUND(15.0*avg_color_float1[1]/255.0) );
	enc_color1[2] = int( JAS_ROUND(15.0*avg_color_float1[2]/255.0) );
	enc_color2[0] = int( JAS_ROUND(15.0*avg_color_float2[0]/255.0) );
	enc_color2[1] = int( JAS_ROUND(15.0*avg_color_float2[1]/255.0) );
	enc_color2[2] = int( JAS_ROUND(15.0*avg_color_float2[2]/255.0) );

	best_color_upper[0] = enc_color1[0];
	best_color_upper[1] = enc_color1[1];
	best_color_upper[2] = enc_color1[2];
	best_color_lower[0] = enc_color2[0];
	best_color_lower[1] = enc_color2[1];
	best_color_lower[2] = enc_color2[2];

	diffbit = 0;

	avg_color_quant1[0] = enc_color1[0] << 4 | (enc_color1[0] );
	avg_color_quant1[1] = enc_color1[1] << 4 | (enc_color1[1] );
	avg_color_quant1[2] = enc_color1[2] << 4 | (enc_color1[2] );
	avg_color_quant2[0] = enc_color2[0] << 4 | (enc_color2[0] );
	avg_color_quant2[1] = enc_color2[1] << 4 | (enc_color2[1] );
	avg_color_quant2[2] = enc_color2[2] << 4 | (enc_color2[2] );

	// Pack bits into the first word. 

	compressed1_flip = 0;
	PUTBITSHIGH( compressed1_flip, diffbit,       1, 33);
 	PUTBITSHIGH( compressed1_flip, enc_color1[0], 4, 63);
 	PUTBITSHIGH( compressed1_flip, enc_color1[1], 4, 55);
 	PUTBITSHIGH( compressed1_flip, enc_color1[2], 4, 47);
 	PUTBITSHIGH( compressed1_flip, enc_color2[0], 4, 49);
 	PUTBITSHIGH( compressed1_flip, enc_color2[1], 4, 51);
 	PUTBITSHIGH( compressed1_flip, enc_color2[2], 4, 43);

	// upper part of block
	best_err_upper = tryalltables_3bittable4x2(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
	flip_err = best_err_upper;
	// lower part of block
	best_err_lower = tryalltables_3bittable4x2(img,width,height,startx,starty+2,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);
	flip_err += best_err_lower;

 	PUTBITSHIGH( compressed1_flip, best_table1,   3, 39);
 	PUTBITSHIGH( compressed1_flip, best_table2,   3, 36);
 	PUTBITSHIGH( compressed1_flip,           1,   1, 32);

	best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
	best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);
	
	compressed2_flip = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);

	// Now lets see which is the best table to use. Only 8 tables are possible. 

	if(norm_err <= flip_err)
	{
		compressed1 = compressed1_norm | 0;
		compressed2 = compressed2_norm;
		best_err = norm_err;
		best_flip = 0;
	}
	else
	{
		compressed1 = compressed1_flip | 1;
		compressed2 = compressed2_flip;
		best_err = flip_err;
		best_enc_color1[0] = enc_color1[0];
		best_enc_color1[1] = enc_color1[1];
		best_enc_color1[2] = enc_color1[2];
		best_enc_color2[0] = enc_color2[0];
		best_enc_color2[1] = enc_color2[1];
		best_enc_color2[2] = enc_color2[2];
		best_flip = 1;
	}
	return best_err;
}

// Compresses the block using either the individual or differential mode in ETC1/ETC2
// Uses the average color as the base color in each half-block.
// Tries both flipped and unflipped.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockDiffFlipAverage(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2)
{
	unsigned int compressed1_norm, compressed2_norm;
	unsigned int compressed1_flip, compressed2_flip;
	uint8 avg_color_quant1[3], avg_color_quant2[3];

	float avg_color_float1[3],avg_color_float2[3];
	int enc_color1[3], enc_color2[3], diff[3];
	int min_error=255*255*8*3;
	unsigned int best_table_indices1=0, best_table_indices2=0;
	unsigned int best_table1=0, best_table2=0;
	int diffbit;

	int norm_err=0;
	int flip_err=0;

	// First try normal blocks 2x4:
	computeAverageColor2x4noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor2x4noQuantFloat(img,width,height,startx+2,starty,avg_color_float2);

	// First test if avg_color1 is similar enough to avg_color2 so that
	// we can use differential coding of colors. 

	float eps;

	enc_color1[0] = int( JAS_ROUND(31.0*avg_color_float1[0]/255.0) );
	enc_color1[1] = int( JAS_ROUND(31.0*avg_color_float1[1]/255.0) );
	enc_color1[2] = int( JAS_ROUND(31.0*avg_color_float1[2]/255.0) );
	enc_color2[0] = int( JAS_ROUND(31.0*avg_color_float2[0]/255.0) );
	enc_color2[1] = int( JAS_ROUND(31.0*avg_color_float2[1]/255.0) );
	enc_color2[2] = int( JAS_ROUND(31.0*avg_color_float2[2]/255.0) );

	diff[0] = enc_color2[0]-enc_color1[0];	
	diff[1] = enc_color2[1]-enc_color1[1];	
	diff[2] = enc_color2[2]-enc_color1[2];

	if( (diff[0] >= -4) && (diff[0] <= 3) && (diff[1] >= -4) && (diff[1] <= 3) && (diff[2] >= -4) && (diff[2] <= 3) )
	{
		diffbit = 1;

		// The difference to be coded:

		diff[0] = enc_color2[0]-enc_color1[0];	
		diff[1] = enc_color2[1]-enc_color1[1];	
		diff[2] = enc_color2[2]-enc_color1[2];

		avg_color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
		avg_color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
		avg_color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
		avg_color_quant2[0] = enc_color2[0] << 3 | (enc_color2[0] >> 2);
		avg_color_quant2[1] = enc_color2[1] << 3 | (enc_color2[1] >> 2);
		avg_color_quant2[2] = enc_color2[2] << 3 | (enc_color2[2] >> 2);

		// Pack bits into the first word. 

		//     ETC1_RGB8_OES:
		// 
		//     a) bit layout in bits 63 through 32 if diffbit = 0
		// 
		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
		//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------
		//     
		//     b) bit layout in bits 63 through 32 if diffbit = 1
		// 
		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |diff|flip|
		//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------
		// 
		//     c) bit layout in bits 31 through 0 (in both cases)
		// 
		//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3   2   1  0
		//      --------------------------------------------------------------------------------------------------
		//     |       most significant pixel index bits       |         least significant pixel index bits       |  
		//     | p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a| p| o| n| m| l| k| j| i| h| g| f| e| d| c | b | a |
		//      --------------------------------------------------------------------------------------------------      

		compressed1_norm = 0;
		PUTBITSHIGH( compressed1_norm, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_norm, enc_color1[0], 5, 63);
 		PUTBITSHIGH( compressed1_norm, enc_color1[1], 5, 55);
 		PUTBITSHIGH( compressed1_norm, enc_color1[2], 5, 47);
 		PUTBITSHIGH( compressed1_norm, diff[0],       3, 58);
 		PUTBITSHIGH( compressed1_norm, diff[1],       3, 50);
 		PUTBITSHIGH( compressed1_norm, diff[2],       3, 42);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		norm_err = 0;

		// left part of block
		norm_err = tryalltables_3bittable2x4(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);

		// right part of block
		norm_err += tryalltables_3bittable2x4(img,width,height,startx+2,starty,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_norm, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_norm, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_norm,           0,   1, 32);

		compressed2_norm = 0;
		PUTBITS( compressed2_norm, (best_pixel_indices1_MSB     ), 8, 23);
		PUTBITS( compressed2_norm, (best_pixel_indices2_MSB     ), 8, 31);
		PUTBITS( compressed2_norm, (best_pixel_indices1_LSB     ), 8, 7);
		PUTBITS( compressed2_norm, (best_pixel_indices2_LSB     ), 8, 15);
	}
	else
	{
		diffbit = 0;
		// The difference is bigger than what fits in 555 plus delta-333, so we will have
		// to deal with 444 444.

		eps = (float) 0.0001;

		enc_color1[0] = int( ((float) avg_color_float1[0] / (17.0)) +0.5 + eps);
		enc_color1[1] = int( ((float) avg_color_float1[1] / (17.0)) +0.5 + eps);
		enc_color1[2] = int( ((float) avg_color_float1[2] / (17.0)) +0.5 + eps);
		enc_color2[0] = int( ((float) avg_color_float2[0] / (17.0)) +0.5 + eps);
		enc_color2[1] = int( ((float) avg_color_float2[1] / (17.0)) +0.5 + eps);
		enc_color2[2] = int( ((float) avg_color_float2[2] / (17.0)) +0.5 + eps);
		avg_color_quant1[0] = enc_color1[0] << 4 | enc_color1[0]; 
		avg_color_quant1[1] = enc_color1[1] << 4 | enc_color1[1]; 
		avg_color_quant1[2] = enc_color1[2] << 4 | enc_color1[2];
		avg_color_quant2[0] = enc_color2[0] << 4 | enc_color2[0]; 
		avg_color_quant2[1] = enc_color2[1] << 4 | enc_color2[1]; 
		avg_color_quant2[2] = enc_color2[2] << 4 | enc_color2[2];

		// Pack bits into the first word. 

		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
		//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------

		compressed1_norm = 0;
		PUTBITSHIGH( compressed1_norm, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_norm, enc_color1[0], 4, 63);
 		PUTBITSHIGH( compressed1_norm, enc_color1[1], 4, 55);
 		PUTBITSHIGH( compressed1_norm, enc_color1[2], 4, 47);
 		PUTBITSHIGH( compressed1_norm, enc_color2[0], 4, 59);
 		PUTBITSHIGH( compressed1_norm, enc_color2[1], 4, 51);
 		PUTBITSHIGH( compressed1_norm, enc_color2[2], 4, 43);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;
		
		// left part of block
		norm_err = tryalltables_3bittable2x4(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);

		// right part of block
		norm_err += tryalltables_3bittable2x4(img,width,height,startx+2,starty,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_norm, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_norm, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_norm,           0,   1, 32);

		compressed2_norm = 0;
		PUTBITS( compressed2_norm, (best_pixel_indices1_MSB     ), 8, 23);
		PUTBITS( compressed2_norm, (best_pixel_indices2_MSB     ), 8, 31);
		PUTBITS( compressed2_norm, (best_pixel_indices1_LSB     ), 8, 7);
		PUTBITS( compressed2_norm, (best_pixel_indices2_LSB     ), 8, 15);
	}

	// Now try flipped blocks 4x2:

	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty+2,avg_color_float2);

	// First test if avg_color1 is similar enough to avg_color2 so that
	// we can use differential coding of colors. 

	enc_color1[0] = int( JAS_ROUND(31.0*avg_color_float1[0]/255.0) );
	enc_color1[1] = int( JAS_ROUND(31.0*avg_color_float1[1]/255.0) );
	enc_color1[2] = int( JAS_ROUND(31.0*avg_color_float1[2]/255.0) );
	enc_color2[0] = int( JAS_ROUND(31.0*avg_color_float2[0]/255.0) );
	enc_color2[1] = int( JAS_ROUND(31.0*avg_color_float2[1]/255.0) );
	enc_color2[2] = int( JAS_ROUND(31.0*avg_color_float2[2]/255.0) );

	diff[0] = enc_color2[0]-enc_color1[0];	
	diff[1] = enc_color2[1]-enc_color1[1];	
	diff[2] = enc_color2[2]-enc_color1[2];

	if( (diff[0] >= -4) && (diff[0] <= 3) && (diff[1] >= -4) && (diff[1] <= 3) && (diff[2] >= -4) && (diff[2] <= 3) )
	{
		diffbit = 1;

		// The difference to be coded:

		diff[0] = enc_color2[0]-enc_color1[0];	
		diff[1] = enc_color2[1]-enc_color1[1];	
		diff[2] = enc_color2[2]-enc_color1[2];

		avg_color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
		avg_color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
		avg_color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
		avg_color_quant2[0] = enc_color2[0] << 3 | (enc_color2[0] >> 2);
		avg_color_quant2[1] = enc_color2[1] << 3 | (enc_color2[1] >> 2);
		avg_color_quant2[2] = enc_color2[2] << 3 | (enc_color2[2] >> 2);

		// Pack bits into the first word. 

		compressed1_flip = 0;
		PUTBITSHIGH( compressed1_flip, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_flip, enc_color1[0], 5, 63);
 		PUTBITSHIGH( compressed1_flip, enc_color1[1], 5, 55);
 		PUTBITSHIGH( compressed1_flip, enc_color1[2], 5, 47);
 		PUTBITSHIGH( compressed1_flip, diff[0],       3, 58);
 		PUTBITSHIGH( compressed1_flip, diff[1],       3, 50);
 		PUTBITSHIGH( compressed1_flip, diff[2],       3, 42);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		// upper part of block
		flip_err = tryalltables_3bittable4x2(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
		// lower part of block
		flip_err += tryalltables_3bittable4x2(img,width,height,startx,starty+2,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_flip, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_flip, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_flip,           1,   1, 32);

		best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
		best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);
		
		compressed2_flip = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);
	}
	else
	{
		diffbit = 0;
		// The difference is bigger than what fits in 555 plus delta-333, so we will have
		// to deal with 444 444.
		eps = (float) 0.0001;

		enc_color1[0] = int( ((float) avg_color_float1[0] / (17.0)) +0.5 + eps);
		enc_color1[1] = int( ((float) avg_color_float1[1] / (17.0)) +0.5 + eps);
		enc_color1[2] = int( ((float) avg_color_float1[2] / (17.0)) +0.5 + eps);
		enc_color2[0] = int( ((float) avg_color_float2[0] / (17.0)) +0.5 + eps);
		enc_color2[1] = int( ((float) avg_color_float2[1] / (17.0)) +0.5 + eps);
		enc_color2[2] = int( ((float) avg_color_float2[2] / (17.0)) +0.5 + eps);

		avg_color_quant1[0] = enc_color1[0] << 4 | enc_color1[0]; 
		avg_color_quant1[1] = enc_color1[1] << 4 | enc_color1[1]; 
		avg_color_quant1[2] = enc_color1[2] << 4 | enc_color1[2];
		avg_color_quant2[0] = enc_color2[0] << 4 | enc_color2[0]; 
		avg_color_quant2[1] = enc_color2[1] << 4 | enc_color2[1]; 
		avg_color_quant2[2] = enc_color2[2] << 4 | enc_color2[2];

		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
		//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------


		// Pack bits into the first word. 

		compressed1_flip = 0;
		PUTBITSHIGH( compressed1_flip, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_flip, enc_color1[0], 4, 63);
 		PUTBITSHIGH( compressed1_flip, enc_color1[1], 4, 55);
 		PUTBITSHIGH( compressed1_flip, enc_color1[2], 4, 47);
 		PUTBITSHIGH( compressed1_flip, enc_color2[0], 4, 59);
 		PUTBITSHIGH( compressed1_flip, enc_color2[1], 4, 51);
 		PUTBITSHIGH( compressed1_flip, enc_color2[2], 4, 43);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		// upper part of block
		flip_err = tryalltables_3bittable4x2(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
		// lower part of block
		flip_err += tryalltables_3bittable4x2(img,width,height,startx,starty+2,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_flip, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_flip, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_flip,           1,   1, 32);

		best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
		best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);
		
		compressed2_flip = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);
	}

	// Now lets see which is the best table to use. Only 8 tables are possible. 

	if(norm_err <= flip_err)
	{
		compressed1 = compressed1_norm | 0;
		compressed2 = compressed2_norm;
	}
	else
	{
		compressed1 = compressed1_flip | 1;
		compressed2 = compressed2_flip;
	}
}

// Compresses the block using only the differential mode in ETC1/ETC2
// Uses the average color as the base color in each half-block.
// If average colors are too different, use the average color of the entire block in both half-blocks.
// Tries both flipped and unflipped.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
int compressBlockOnlyDiffFlipAverage(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2, int *best_enc_color1, int*best_enc_color2, int &best_flip)
{
	unsigned int compressed1_norm, compressed2_norm;
	unsigned int compressed1_flip, compressed2_flip;
	uint8 avg_color_quant1[3], avg_color_quant2[3];

	float avg_color_float1[3],avg_color_float2[3];
	int enc_color1[3], enc_color2[3], diff[3];
	int min_error=255*255*8*3;
	unsigned int best_table_indices1=0, best_table_indices2=0;
	unsigned int best_table1=0, best_table2=0;
	int diffbit;

	int norm_err=0;
	int flip_err=0;
	int best_err;

	// First try normal blocks 2x4:

	computeAverageColor2x4noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor2x4noQuantFloat(img,width,height,startx+2,starty,avg_color_float2);

	// First test if avg_color1 is similar enough to avg_color2 so that
	// we can use differential coding of colors. 

	enc_color1[0] = int( JAS_ROUND(31.0*avg_color_float1[0]/255.0) );
	enc_color1[1] = int( JAS_ROUND(31.0*avg_color_float1[1]/255.0) );
	enc_color1[2] = int( JAS_ROUND(31.0*avg_color_float1[2]/255.0) );
	enc_color2[0] = int( JAS_ROUND(31.0*avg_color_float2[0]/255.0) );
	enc_color2[1] = int( JAS_ROUND(31.0*avg_color_float2[1]/255.0) );
	enc_color2[2] = int( JAS_ROUND(31.0*avg_color_float2[2]/255.0) );

	diff[0] = enc_color2[0]-enc_color1[0];	
	diff[1] = enc_color2[1]-enc_color1[1];	
	diff[2] = enc_color2[2]-enc_color1[2];

	if( !((diff[0] >= -4) && (diff[0] <= 3) && (diff[1] >= -4) && (diff[1] <= 3) && (diff[2] >= -4) && (diff[2] <= 3)) )
	{
		// The colors are too different. Use the same color in both blocks.
		enc_color1[0] = int( JAS_ROUND(31.0*((avg_color_float1[0]+avg_color_float2[0])/2.0)/255.0) );
		enc_color1[1] = int( JAS_ROUND(31.0*((avg_color_float1[1]+avg_color_float2[1])/2.0)/255.0) );
		enc_color1[2] = int( JAS_ROUND(31.0*((avg_color_float1[2]+avg_color_float2[2])/2.0)/255.0) );
		enc_color2[0] = enc_color1[0];
		enc_color2[1] = enc_color1[1];
		enc_color2[2] = enc_color1[2];
		diff[0] = enc_color2[0]-enc_color1[0];	
		diff[1] = enc_color2[1]-enc_color1[1];	
		diff[2] = enc_color2[2]-enc_color1[2];
	}

	diffbit = 1;

	// The difference to be coded:

	diff[0] = enc_color2[0]-enc_color1[0];	
	diff[1] = enc_color2[1]-enc_color1[1];	
	diff[2] = enc_color2[2]-enc_color1[2];

	avg_color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
	avg_color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
	avg_color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
	avg_color_quant2[0] = enc_color2[0] << 3 | (enc_color2[0] >> 2);
	avg_color_quant2[1] = enc_color2[1] << 3 | (enc_color2[1] >> 2);
	avg_color_quant2[2] = enc_color2[2] << 3 | (enc_color2[2] >> 2);

	// Pack bits into the first word. 

	//     ETC1_RGB8_OES:
	// 
	//     a) bit layout in bits 63 through 32 if diffbit = 0
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
	//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------
	//     
	//     b) bit layout in bits 63 through 32 if diffbit = 1
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |diff|flip|
	//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------
	// 
	//     c) bit layout in bits 31 through 0 (in both cases)
	// 
	//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3   2   1  0
	//      --------------------------------------------------------------------------------------------------
	//     |       most significant pixel index bits       |         least significant pixel index bits       |  
	//     | p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a| p| o| n| m| l| k| j| i| h| g| f| e| d| c | b | a |
	//      --------------------------------------------------------------------------------------------------      

	compressed1_norm = 0;
	PUTBITSHIGH( compressed1_norm, diffbit,       1, 33);
 	PUTBITSHIGH( compressed1_norm, enc_color1[0], 5, 63);
 	PUTBITSHIGH( compressed1_norm, enc_color1[1], 5, 55);
 	PUTBITSHIGH( compressed1_norm, enc_color1[2], 5, 47);
 	PUTBITSHIGH( compressed1_norm, diff[0],       3, 58);
 	PUTBITSHIGH( compressed1_norm, diff[1],       3, 50);
 	PUTBITSHIGH( compressed1_norm, diff[2],       3, 42);

	unsigned int best_pixel_indices1_MSB;
	unsigned int best_pixel_indices1_LSB;
	unsigned int best_pixel_indices2_MSB;
	unsigned int best_pixel_indices2_LSB;

	best_enc_color1[0] = enc_color1[0];
	best_enc_color1[1] = enc_color1[1];
	best_enc_color1[2] = enc_color1[2];
	best_enc_color2[0] = enc_color2[0];
	best_enc_color2[1] = enc_color2[1];
	best_enc_color2[2] = enc_color2[2];

	norm_err = 0;

	// left part of block
	norm_err = tryalltables_3bittable2x4(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);

	// right part of block
	norm_err += tryalltables_3bittable2x4(img,width,height,startx+2,starty,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 	PUTBITSHIGH( compressed1_norm, best_table1,   3, 39);
 	PUTBITSHIGH( compressed1_norm, best_table2,   3, 36);
 	PUTBITSHIGH( compressed1_norm,           0,   1, 32);

	compressed2_norm = 0;
	PUTBITS( compressed2_norm, (best_pixel_indices1_MSB     ), 8, 23);
	PUTBITS( compressed2_norm, (best_pixel_indices2_MSB     ), 8, 31);
	PUTBITS( compressed2_norm, (best_pixel_indices1_LSB     ), 8, 7);
	PUTBITS( compressed2_norm, (best_pixel_indices2_LSB     ), 8, 15);

	// Now try flipped blocks 4x2:

	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty+2,avg_color_float2);

	// First test if avg_color1 is similar enough to avg_color2 so that
	// we can use differential coding of colors. 

	enc_color1[0] = int( JAS_ROUND(31.0*avg_color_float1[0]/255.0) );
	enc_color1[1] = int( JAS_ROUND(31.0*avg_color_float1[1]/255.0) );
	enc_color1[2] = int( JAS_ROUND(31.0*avg_color_float1[2]/255.0) );
	enc_color2[0] = int( JAS_ROUND(31.0*avg_color_float2[0]/255.0) );
	enc_color2[1] = int( JAS_ROUND(31.0*avg_color_float2[1]/255.0) );
	enc_color2[2] = int( JAS_ROUND(31.0*avg_color_float2[2]/255.0) );

	diff[0] = enc_color2[0]-enc_color1[0];	
	diff[1] = enc_color2[1]-enc_color1[1];	
	diff[2] = enc_color2[2]-enc_color1[2];

	if( !((diff[0] >= -4) && (diff[0] <= 3) && (diff[1] >= -4) && (diff[1] <= 3) && (diff[2] >= -4) && (diff[2] <= 3)) )
	{
		// The colors are too different. Use the same color in both blocks.
		enc_color1[0] = int( JAS_ROUND(31.0*((avg_color_float1[0]+avg_color_float2[0])/2.0)/255.0) );
		enc_color1[1] = int( JAS_ROUND(31.0*((avg_color_float1[1]+avg_color_float2[1])/2.0)/255.0) );
		enc_color1[2] = int( JAS_ROUND(31.0*((avg_color_float1[2]+avg_color_float2[2])/2.0)/255.0) );
		enc_color2[0] = enc_color1[0];
		enc_color2[1] = enc_color1[1];
		enc_color2[2] = enc_color1[2];
		diff[0] = enc_color2[0]-enc_color1[0];	
		diff[1] = enc_color2[1]-enc_color1[1];	
		diff[2] = enc_color2[2]-enc_color1[2];
	}
	diffbit = 1;

	// The difference to be coded:

	diff[0] = enc_color2[0]-enc_color1[0];	
	diff[1] = enc_color2[1]-enc_color1[1];	
	diff[2] = enc_color2[2]-enc_color1[2];

	avg_color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
	avg_color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
	avg_color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
	avg_color_quant2[0] = enc_color2[0] << 3 | (enc_color2[0] >> 2);
	avg_color_quant2[1] = enc_color2[1] << 3 | (enc_color2[1] >> 2);
	avg_color_quant2[2] = enc_color2[2] << 3 | (enc_color2[2] >> 2);

	// Pack bits into the first word. 

	compressed1_flip = 0;
	PUTBITSHIGH( compressed1_flip, diffbit,       1, 33);
 	PUTBITSHIGH( compressed1_flip, enc_color1[0], 5, 63);
 	PUTBITSHIGH( compressed1_flip, enc_color1[1], 5, 55);
 	PUTBITSHIGH( compressed1_flip, enc_color1[2], 5, 47);
 	PUTBITSHIGH( compressed1_flip, diff[0],       3, 58);
 	PUTBITSHIGH( compressed1_flip, diff[1],       3, 50);
 	PUTBITSHIGH( compressed1_flip, diff[2],       3, 42);

	// upper part of block
	flip_err = tryalltables_3bittable4x2(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
	// lower part of block
	flip_err += tryalltables_3bittable4x2(img,width,height,startx,starty+2,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 	PUTBITSHIGH( compressed1_flip, best_table1,   3, 39);
 	PUTBITSHIGH( compressed1_flip, best_table2,   3, 36);
 	PUTBITSHIGH( compressed1_flip,           1,   1, 32);

	best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
	best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);
	
	compressed2_flip = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);

	// Now lets see which is the best table to use. Only 8 tables are possible. 

	if(norm_err <= flip_err)
	{
		compressed1 = compressed1_norm | 0;
		compressed2 = compressed2_norm;
		best_err = norm_err;
		best_flip = 0;
	}
	else
	{
		compressed1 = compressed1_flip | 1;
		compressed2 = compressed2_flip;
		best_err = flip_err;
		best_enc_color1[0] = enc_color1[0];
		best_enc_color1[1] = enc_color1[1];
		best_enc_color1[2] = enc_color1[2];
		best_enc_color2[0] = enc_color2[0];
		best_enc_color2[1] = enc_color2[1];
		best_enc_color2[2] = enc_color2[2];
		best_flip = 1;
	}
	return best_err;
}

// Compresses the block using only the differential mode in ETC1/ETC2
// Uses the average color as the base color in each half-block.
// If average colors are too different, use the average color of the entire block in both half-blocks.
// Tries both flipped and unflipped.
// Uses fixed point arithmetics where 1000 represents 1.0.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int compressBlockOnlyDiffFlipAveragePerceptual1000(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2)
{
	unsigned int compressed1_norm, compressed2_norm;
	unsigned int compressed1_flip, compressed2_flip;
	uint8 avg_color_quant1[3], avg_color_quant2[3];

	float avg_color_float1[3],avg_color_float2[3];
	int enc_color1[3], enc_color2[3], diff[3];
	unsigned int min_error=MAXERR1000;
	unsigned int best_table_indices1=0, best_table_indices2=0;
	unsigned int best_table1=0, best_table2=0;
	int diffbit;

	int norm_err=0;
	int flip_err=0;

	// First try normal blocks 2x4:

	computeAverageColor2x4noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor2x4noQuantFloat(img,width,height,startx+2,starty,avg_color_float2);

	// First test if avg_color1 is similar enough to avg_color2 so that
	// we can use differential coding of colors. 

	enc_color1[0] = int( JAS_ROUND(31.0*avg_color_float1[0]/255.0) );
	enc_color1[1] = int( JAS_ROUND(31.0*avg_color_float1[1]/255.0) );
	enc_color1[2] = int( JAS_ROUND(31.0*avg_color_float1[2]/255.0) );
	enc_color2[0] = int( JAS_ROUND(31.0*avg_color_float2[0]/255.0) );
	enc_color2[1] = int( JAS_ROUND(31.0*avg_color_float2[1]/255.0) );
	enc_color2[2] = int( JAS_ROUND(31.0*avg_color_float2[2]/255.0) );

	diff[0] = enc_color2[0]-enc_color1[0];	
	diff[1] = enc_color2[1]-enc_color1[1];	
	diff[2] = enc_color2[2]-enc_color1[2];

	if( !((diff[0] >= -4) && (diff[0] <= 3) && (diff[1] >= -4) && (diff[1] <= 3) && (diff[2] >= -4) && (diff[2] <= 3)) )
	{
		enc_color1[0] = (enc_color1[0] + enc_color2[0]) >> 1;
		enc_color1[1] = (enc_color1[1] + enc_color2[1]) >> 1;
		enc_color1[2] = (enc_color1[2] + enc_color2[2]) >> 1;

		enc_color2[0] = enc_color1[0];
		enc_color2[1] = enc_color1[1];
		enc_color2[2] = enc_color1[2];

	}

	{
		diffbit = 1;

		// The difference to be coded:

		diff[0] = enc_color2[0]-enc_color1[0];	
		diff[1] = enc_color2[1]-enc_color1[1];	
		diff[2] = enc_color2[2]-enc_color1[2];

		avg_color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
		avg_color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
		avg_color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
		avg_color_quant2[0] = enc_color2[0] << 3 | (enc_color2[0] >> 2);
		avg_color_quant2[1] = enc_color2[1] << 3 | (enc_color2[1] >> 2);
		avg_color_quant2[2] = enc_color2[2] << 3 | (enc_color2[2] >> 2);

		// Pack bits into the first word. 

		//     ETC1_RGB8_OES:
		// 
		//     a) bit layout in bits 63 through 32 if diffbit = 0
		// 
		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
		//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------
		//     
		//     b) bit layout in bits 63 through 32 if diffbit = 1
		// 
		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |diff|flip|
		//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------
		// 
		//     c) bit layout in bits 31 through 0 (in both cases)
		// 
		//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3   2   1  0
		//      --------------------------------------------------------------------------------------------------
		//     |       most significant pixel index bits       |         least significant pixel index bits       |  
		//     | p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a| p| o| n| m| l| k| j| i| h| g| f| e| d| c | b | a |
		//      --------------------------------------------------------------------------------------------------      

		compressed1_norm = 0;
		PUTBITSHIGH( compressed1_norm, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_norm, enc_color1[0], 5, 63);
 		PUTBITSHIGH( compressed1_norm, enc_color1[1], 5, 55);
 		PUTBITSHIGH( compressed1_norm, enc_color1[2], 5, 47);
 		PUTBITSHIGH( compressed1_norm, diff[0],       3, 58);
 		PUTBITSHIGH( compressed1_norm, diff[1],       3, 50);
 		PUTBITSHIGH( compressed1_norm, diff[2],       3, 42);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		norm_err = 0;

		// left part of block 
		norm_err = tryalltables_3bittable2x4percep1000(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);

		// right part of block
		norm_err += tryalltables_3bittable2x4percep1000(img,width,height,startx+2,starty,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_norm, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_norm, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_norm,           0,   1, 32);

		compressed2_norm = 0;
		PUTBITS( compressed2_norm, (best_pixel_indices1_MSB     ), 8, 23);
		PUTBITS( compressed2_norm, (best_pixel_indices2_MSB     ), 8, 31);
		PUTBITS( compressed2_norm, (best_pixel_indices1_LSB     ), 8, 7);
		PUTBITS( compressed2_norm, (best_pixel_indices2_LSB     ), 8, 15);

	}
	// Now try flipped blocks 4x2:

	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty+2,avg_color_float2);

	// First test if avg_color1 is similar enough to avg_color2 so that
	// we can use differential coding of colors. 

	enc_color1[0] = int( JAS_ROUND(31.0*avg_color_float1[0]/255.0) );
	enc_color1[1] = int( JAS_ROUND(31.0*avg_color_float1[1]/255.0) );
	enc_color1[2] = int( JAS_ROUND(31.0*avg_color_float1[2]/255.0) );
	enc_color2[0] = int( JAS_ROUND(31.0*avg_color_float2[0]/255.0) );
	enc_color2[1] = int( JAS_ROUND(31.0*avg_color_float2[1]/255.0) );
	enc_color2[2] = int( JAS_ROUND(31.0*avg_color_float2[2]/255.0) );

	diff[0] = enc_color2[0]-enc_color1[0];	
	diff[1] = enc_color2[1]-enc_color1[1];	
	diff[2] = enc_color2[2]-enc_color1[2];

	if( !((diff[0] >= -4) && (diff[0] <= 3) && (diff[1] >= -4) && (diff[1] <= 3) && (diff[2] >= -4) && (diff[2] <= 3)) )
	{
		enc_color1[0] = (enc_color1[0] + enc_color2[0]) >> 1;
		enc_color1[1] = (enc_color1[1] + enc_color2[1]) >> 1;
		enc_color1[2] = (enc_color1[2] + enc_color2[2]) >> 1;

		enc_color2[0] = enc_color1[0];
		enc_color2[1] = enc_color1[1];
		enc_color2[2] = enc_color1[2];
	}

	{
		diffbit = 1;

		// The difference to be coded:

		diff[0] = enc_color2[0]-enc_color1[0];	
		diff[1] = enc_color2[1]-enc_color1[1];	
		diff[2] = enc_color2[2]-enc_color1[2];

		avg_color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
		avg_color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
		avg_color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
		avg_color_quant2[0] = enc_color2[0] << 3 | (enc_color2[0] >> 2);
		avg_color_quant2[1] = enc_color2[1] << 3 | (enc_color2[1] >> 2);
		avg_color_quant2[2] = enc_color2[2] << 3 | (enc_color2[2] >> 2);

		// Pack bits into the first word. 

		compressed1_flip = 0;
		PUTBITSHIGH( compressed1_flip, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_flip, enc_color1[0], 5, 63);
 		PUTBITSHIGH( compressed1_flip, enc_color1[1], 5, 55);
 		PUTBITSHIGH( compressed1_flip, enc_color1[2], 5, 47);
 		PUTBITSHIGH( compressed1_flip, diff[0],       3, 58);
 		PUTBITSHIGH( compressed1_flip, diff[1],       3, 50);
 		PUTBITSHIGH( compressed1_flip, diff[2],       3, 42);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		// upper part of block
		flip_err = tryalltables_3bittable4x2percep1000(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
		// lower part of block
		flip_err += tryalltables_3bittable4x2percep1000(img,width,height,startx,starty+2,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_flip, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_flip, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_flip,           1,   1, 32);

		best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
		best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);
		
		compressed2_flip = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);
	}
	unsigned int best_err;

	if(norm_err <= flip_err)
	{
		compressed1 = compressed1_norm | 0;
		compressed2 = compressed2_norm;
		best_err = norm_err;
	}
	else
	{
		compressed1 = compressed1_flip | 1;
		compressed2 = compressed2_flip;
		best_err = flip_err;
	}
	return best_err;
}

// Compresses the block using both the individual and the differential mode in ETC1/ETC2
// Uses the average color as the base color in each half-block.
// Uses a perceptual error metric.
// Tries both flipped and unflipped.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double compressBlockDiffFlipAveragePerceptual(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2)
{
	unsigned int compressed1_norm, compressed2_norm;
	unsigned int compressed1_flip, compressed2_flip;
	uint8 avg_color_quant1[3], avg_color_quant2[3];

	float avg_color_float1[3],avg_color_float2[3];
	int enc_color1[3], enc_color2[3], diff[3];
	int min_error=255*255*8*3;
	unsigned int best_table_indices1=0, best_table_indices2=0;
	unsigned int best_table1=0, best_table2=0;
	int diffbit;

	int norm_err=0;
	int flip_err=0;

	// First try normal blocks 2x4:

	computeAverageColor2x4noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor2x4noQuantFloat(img,width,height,startx+2,starty,avg_color_float2);

	// First test if avg_color1 is similar enough to avg_color2 so that
	// we can use differential coding of colors. 

	float eps;

	enc_color1[0] = int( JAS_ROUND(31.0*avg_color_float1[0]/255.0) );
	enc_color1[1] = int( JAS_ROUND(31.0*avg_color_float1[1]/255.0) );
	enc_color1[2] = int( JAS_ROUND(31.0*avg_color_float1[2]/255.0) );
	enc_color2[0] = int( JAS_ROUND(31.0*avg_color_float2[0]/255.0) );
	enc_color2[1] = int( JAS_ROUND(31.0*avg_color_float2[1]/255.0) );
	enc_color2[2] = int( JAS_ROUND(31.0*avg_color_float2[2]/255.0) );

	diff[0] = enc_color2[0]-enc_color1[0];	
	diff[1] = enc_color2[1]-enc_color1[1];	
	diff[2] = enc_color2[2]-enc_color1[2];

	if( (diff[0] >= -4) && (diff[0] <= 3) && (diff[1] >= -4) && (diff[1] <= 3) && (diff[2] >= -4) && (diff[2] <= 3) )
	{
		diffbit = 1;

		// The difference to be coded:
		diff[0] = enc_color2[0]-enc_color1[0];	
		diff[1] = enc_color2[1]-enc_color1[1];	
		diff[2] = enc_color2[2]-enc_color1[2];

		avg_color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
		avg_color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
		avg_color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
		avg_color_quant2[0] = enc_color2[0] << 3 | (enc_color2[0] >> 2);
		avg_color_quant2[1] = enc_color2[1] << 3 | (enc_color2[1] >> 2);
		avg_color_quant2[2] = enc_color2[2] << 3 | (enc_color2[2] >> 2);

		// Pack bits into the first word. 

		//     ETC1_RGB8_OES:
		// 
		//     a) bit layout in bits 63 through 32 if diffbit = 0
		// 
		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
		//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------
		//     
		//     b) bit layout in bits 63 through 32 if diffbit = 1
		// 
		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |diff|flip|
		//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------
		// 
		//     c) bit layout in bits 31 through 0 (in both cases)
		// 
		//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3   2   1  0
		//      --------------------------------------------------------------------------------------------------
		//     |       most significant pixel index bits       |         least significant pixel index bits       |  
		//     | p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a| p| o| n| m| l| k| j| i| h| g| f| e| d| c | b | a |
		//      --------------------------------------------------------------------------------------------------      

		compressed1_norm = 0;
		PUTBITSHIGH( compressed1_norm, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_norm, enc_color1[0], 5, 63);
 		PUTBITSHIGH( compressed1_norm, enc_color1[1], 5, 55);
 		PUTBITSHIGH( compressed1_norm, enc_color1[2], 5, 47);
 		PUTBITSHIGH( compressed1_norm, diff[0],       3, 58);
 		PUTBITSHIGH( compressed1_norm, diff[1],       3, 50);
 		PUTBITSHIGH( compressed1_norm, diff[2],       3, 42);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		norm_err = 0;

		// left part of block 
		norm_err = tryalltables_3bittable2x4percep(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);

		// right part of block
		norm_err += tryalltables_3bittable2x4percep(img,width,height,startx+2,starty,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_norm, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_norm, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_norm,           0,   1, 32);

		compressed2_norm = 0;
		PUTBITS( compressed2_norm, (best_pixel_indices1_MSB     ), 8, 23);
		PUTBITS( compressed2_norm, (best_pixel_indices2_MSB     ), 8, 31);
		PUTBITS( compressed2_norm, (best_pixel_indices1_LSB     ), 8, 7);
		PUTBITS( compressed2_norm, (best_pixel_indices2_LSB     ), 8, 15);
	}
	else
	{
		diffbit = 0;
		// The difference is bigger than what fits in 555 plus delta-333, so we will have
		// to deal with 444 444.

		eps = (float) 0.0001;

		enc_color1[0] = int( ((float) avg_color_float1[0] / (17.0)) +0.5 + eps);
		enc_color1[1] = int( ((float) avg_color_float1[1] / (17.0)) +0.5 + eps);
		enc_color1[2] = int( ((float) avg_color_float1[2] / (17.0)) +0.5 + eps);
		enc_color2[0] = int( ((float) avg_color_float2[0] / (17.0)) +0.5 + eps);
		enc_color2[1] = int( ((float) avg_color_float2[1] / (17.0)) +0.5 + eps);
		enc_color2[2] = int( ((float) avg_color_float2[2] / (17.0)) +0.5 + eps);
		avg_color_quant1[0] = enc_color1[0] << 4 | enc_color1[0]; 
		avg_color_quant1[1] = enc_color1[1] << 4 | enc_color1[1]; 
		avg_color_quant1[2] = enc_color1[2] << 4 | enc_color1[2];
		avg_color_quant2[0] = enc_color2[0] << 4 | enc_color2[0]; 
		avg_color_quant2[1] = enc_color2[1] << 4 | enc_color2[1]; 
		avg_color_quant2[2] = enc_color2[2] << 4 | enc_color2[2];
	
		// Pack bits into the first word. 

		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
		//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------

		compressed1_norm = 0;
		PUTBITSHIGH( compressed1_norm, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_norm, enc_color1[0], 4, 63);
 		PUTBITSHIGH( compressed1_norm, enc_color1[1], 4, 55);
 		PUTBITSHIGH( compressed1_norm, enc_color1[2], 4, 47);
 		PUTBITSHIGH( compressed1_norm, enc_color2[0], 4, 59);
 		PUTBITSHIGH( compressed1_norm, enc_color2[1], 4, 51);
 		PUTBITSHIGH( compressed1_norm, enc_color2[2], 4, 43);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;
		
		// left part of block
		norm_err = tryalltables_3bittable2x4percep(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);

		// right part of block
		norm_err += tryalltables_3bittable2x4percep(img,width,height,startx+2,starty,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_norm, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_norm, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_norm,           0,   1, 32);

		compressed2_norm = 0;
		PUTBITS( compressed2_norm, (best_pixel_indices1_MSB     ), 8, 23);
		PUTBITS( compressed2_norm, (best_pixel_indices2_MSB     ), 8, 31);
		PUTBITS( compressed2_norm, (best_pixel_indices1_LSB     ), 8, 7);
		PUTBITS( compressed2_norm, (best_pixel_indices2_LSB     ), 8, 15);
	}

	// Now try flipped blocks 4x2:

	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty+2,avg_color_float2);

	// First test if avg_color1 is similar enough to avg_color2 so that
	// we can use differential coding of colors. 

	enc_color1[0] = int( JAS_ROUND(31.0*avg_color_float1[0]/255.0) );
	enc_color1[1] = int( JAS_ROUND(31.0*avg_color_float1[1]/255.0) );
	enc_color1[2] = int( JAS_ROUND(31.0*avg_color_float1[2]/255.0) );
	enc_color2[0] = int( JAS_ROUND(31.0*avg_color_float2[0]/255.0) );
	enc_color2[1] = int( JAS_ROUND(31.0*avg_color_float2[1]/255.0) );
	enc_color2[2] = int( JAS_ROUND(31.0*avg_color_float2[2]/255.0) );

	diff[0] = enc_color2[0]-enc_color1[0];	
	diff[1] = enc_color2[1]-enc_color1[1];	
	diff[2] = enc_color2[2]-enc_color1[2];

	if( (diff[0] >= -4) && (diff[0] <= 3) && (diff[1] >= -4) && (diff[1] <= 3) && (diff[2] >= -4) && (diff[2] <= 3) )
	{
		diffbit = 1;

		// The difference to be coded:

		diff[0] = enc_color2[0]-enc_color1[0];	
		diff[1] = enc_color2[1]-enc_color1[1];	
		diff[2] = enc_color2[2]-enc_color1[2];

		avg_color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
		avg_color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
		avg_color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
		avg_color_quant2[0] = enc_color2[0] << 3 | (enc_color2[0] >> 2);
		avg_color_quant2[1] = enc_color2[1] << 3 | (enc_color2[1] >> 2);
		avg_color_quant2[2] = enc_color2[2] << 3 | (enc_color2[2] >> 2);

		// Pack bits into the first word. 

		compressed1_flip = 0;
		PUTBITSHIGH( compressed1_flip, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_flip, enc_color1[0], 5, 63);
 		PUTBITSHIGH( compressed1_flip, enc_color1[1], 5, 55);
 		PUTBITSHIGH( compressed1_flip, enc_color1[2], 5, 47);
 		PUTBITSHIGH( compressed1_flip, diff[0],       3, 58);
 		PUTBITSHIGH( compressed1_flip, diff[1],       3, 50);
 		PUTBITSHIGH( compressed1_flip, diff[2],       3, 42);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		// upper part of block
		flip_err = tryalltables_3bittable4x2percep(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
		// lower part of block
		flip_err += tryalltables_3bittable4x2percep(img,width,height,startx,starty+2,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_flip, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_flip, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_flip,           1,   1, 32);

		best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
		best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);
		
		compressed2_flip = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);
	}
	else
	{
		diffbit = 0;
		// The difference is bigger than what fits in 555 plus delta-333, so we will have
		// to deal with 444 444.
		eps = (float) 0.0001;

		enc_color1[0] = int( ((float) avg_color_float1[0] / (17.0)) +0.5 + eps);
		enc_color1[1] = int( ((float) avg_color_float1[1] / (17.0)) +0.5 + eps);
		enc_color1[2] = int( ((float) avg_color_float1[2] / (17.0)) +0.5 + eps);
		enc_color2[0] = int( ((float) avg_color_float2[0] / (17.0)) +0.5 + eps);
		enc_color2[1] = int( ((float) avg_color_float2[1] / (17.0)) +0.5 + eps);
		enc_color2[2] = int( ((float) avg_color_float2[2] / (17.0)) +0.5 + eps);

		avg_color_quant1[0] = enc_color1[0] << 4 | enc_color1[0]; 
		avg_color_quant1[1] = enc_color1[1] << 4 | enc_color1[1]; 
		avg_color_quant1[2] = enc_color1[2] << 4 | enc_color1[2];
		avg_color_quant2[0] = enc_color2[0] << 4 | enc_color2[0]; 
		avg_color_quant2[1] = enc_color2[1] << 4 | enc_color2[1]; 
		avg_color_quant2[2] = enc_color2[2] << 4 | enc_color2[2];

		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
		//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------

		// Pack bits into the first word. 

		compressed1_flip = 0;
		PUTBITSHIGH( compressed1_flip, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_flip, enc_color1[0], 4, 63);
 		PUTBITSHIGH( compressed1_flip, enc_color1[1], 4, 55);
 		PUTBITSHIGH( compressed1_flip, enc_color1[2], 4, 47);
 		PUTBITSHIGH( compressed1_flip, enc_color2[0], 4, 59);
 		PUTBITSHIGH( compressed1_flip, enc_color2[1], 4, 51);
 		PUTBITSHIGH( compressed1_flip, enc_color2[2], 4, 43);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		// upper part of block
		flip_err = tryalltables_3bittable4x2percep(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
		// lower part of block
		flip_err += tryalltables_3bittable4x2percep(img,width,height,startx,starty+2,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_flip, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_flip, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_flip,           1,   1, 32);

		best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
		best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);
		
		compressed2_flip = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);
	}

	// Now lets see which is the best table to use. Only 8 tables are possible. 
	
	double best_err;

	if(norm_err <= flip_err)
	{
		compressed1 = compressed1_norm | 0;
		compressed2 = compressed2_norm;
		best_err = norm_err;
	}
	else
	{
		compressed1 = compressed1_flip | 1;
		compressed2 = compressed2_flip;
		best_err = flip_err;
	}
	return best_err;
}

// This is our structure for matrix data
struct dMatrix
{
	int width;			// The number of coloumns in the matrix
	int height;			// The number of rows in the matrix
	double *data;		// The matrix data in row order
};

// Multiplies two matrices
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
dMatrix *multiplyMatrices( dMatrix *Amat, dMatrix *Bmat)
{
	int xx,yy, q;
	dMatrix *resmatrix;

	if(Amat->width != Bmat->height)
	{
		printf("Cannot multiply matrices -- dimensions do not agree.\n");
		exit(1);
	}

	// Allocate space for result
	resmatrix = (dMatrix*) malloc(sizeof(dMatrix));
	resmatrix->width = Bmat->width;
	resmatrix->height = Amat->height;
	resmatrix->data = (double*) malloc(sizeof(double)*(resmatrix->width)*(resmatrix->height));

	for(yy = 0; yy<resmatrix->height; yy++)
		for(xx = 0; xx<resmatrix->width; xx++)
			for(q=0, resmatrix->data[yy*resmatrix->width+xx] = 0.0; q<Amat->width; q++)
				resmatrix->data[yy*resmatrix->width+xx] += Amat->data[yy*Amat->width + q] * Bmat->data[q*Bmat->width+xx];

	return(resmatrix);

}

// Transposes a matrix
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void transposeMatrix( dMatrix *mat)
{
	int xx, yy, zz;
	double *temp;
	int newwidth, newheight;

	temp = (double*) malloc (sizeof(double)*(mat->width)*(mat->height));

	for(zz = 0; zz<((mat->width)*(mat->height)); zz++)
		temp[zz] = mat->data[zz];

	newwidth = mat->height;
	newheight= mat->width;

	for(yy = 0; yy<newheight; yy++)
 		for(xx = 0; xx<newwidth; xx++)
 			mat->data[yy*newwidth+xx] = temp[xx*(mat->width)+yy];

	mat->height = newheight;
	mat->width = newwidth;
	free(temp);
}

// In the planar mode in ETC2, the block can be partitioned as follows:
// 
// O A  A  A  H
// B D1 D3 C3
// B D2 C2 D5
// B C1 D4 D6
// V
// Here A-pixels, B-pixels and C-pixels only depend on two values. For instance, B-pixels only depend on O and V.
// This can be used to quickly rule out combinations of colors.
// Here we calculate the minimum error for the block if we know the red component for O and V.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcBBBred(uint8 *block, int colorO, int colorV)
{
	colorO = (colorO << 2) | (colorO >> 4);
	colorV = (colorV << 2) | (colorV >> 4);

	unsigned int error = 0;
	
	// Now first column: B B B 
	/* unroll loop for( yy=0; (yy<4) && (error <= best_error_sofar); yy++)*/
	{
		error = error + square_table[(block[4*4 + 0] - clamp_table[ ((((colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table[(block[4*4*2 + 0] - clamp_table[ (((((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table[(block[4*4*3 + 0] - clamp_table[ (((3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
	}

	return error;
}

// Calculating the minimum error for the block if we know the red component for H and V.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcCCCred(uint8 *block, int colorH, int colorV)
{
    colorH = (colorH << 2) | (colorH >> 4);
    colorV = (colorV << 2) | (colorV >> 4);

	unsigned int error=0;

	error = error + square_table[(block[4*4*3 + 4 + 0] - clamp_table[ (((colorH + 3*colorV)+2)>>2) + 255])+255];
	error = error + square_table[(block[4*4*2 + 4*2 + 0] - clamp_table[ (((2*colorH + 2*colorV)+2)>>2) + 255])+255];
	error = error + square_table[(block[4*4 + 4*3 + 0] - clamp_table[ (((3*colorH + colorV)+2)>>2) + 255])+255];
	
	return error;
}

// Calculating the minimum error for the block if we know the red component for O and H.
// Uses perceptual error metric.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcLowestPossibleRedOHperceptual(uint8 *block, int colorO, int colorH, unsigned int best_error_sofar)
{
	colorO = (colorO << 2) | (colorO >> 4);
	colorH = (colorH << 2) | (colorH >> 4);

	unsigned int error;

	error = square_table_percep_red[(block[0] - colorO) + 255];
	error = error + square_table_percep_red[(block[4] - clamp_table[ (((   (colorH-colorO) + 4*colorO)+2)>>2) + 255])+255];
	if(error <= best_error_sofar)
	{
		error = error + square_table_percep_red[(block[4*2] - clamp_table[ (((  ((colorH-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table_percep_red[(block[4*3] - clamp_table[ ((( 3*(colorH-colorO) + 4*colorO)+2)>>2) + 255])+255];
	}
	
	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the red component for O and H.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcLowestPossibleRedOH(uint8 *block, int colorO, int colorH, unsigned int best_error_sofar)
{
	colorO = (colorO << 2) | (colorO >> 4);
	colorH = (colorH << 2) | (colorH >> 4);

	unsigned int error;

	error = square_table[(block[0] - colorO) + 255];
	error = error + square_table[(block[4] - clamp_table[ (((   (colorH-colorO) + 4*colorO)+2)>>2) + 255])+255];
	if(error <= best_error_sofar)
	{
		error = error + square_table[(block[4*2] - clamp_table[ (((  ((colorH-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table[(block[4*3] - clamp_table[ ((( 3*(colorH-colorO) + 4*colorO)+2)>>2) + 255])+255];
	}
	
	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the red component for O and H and V.
// Uses perceptual error metric. 
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcErrorPlanarOnlyRedPerceptual(uint8 *block, int colorO, int colorH, int colorV, unsigned int lowest_possible_error, unsigned int BBBvalue, unsigned int CCCvalue, unsigned int best_error_sofar)
{
	colorO = (colorO << 2) | (colorO >> 4);
	colorH = (colorH << 2) | (colorH >> 4);
	colorV = (colorV << 2) | (colorV >> 4);

	unsigned int error;

	// The block can be partitioned into: O A  A  A
	//                                    B D1 D3 C3
	//                                    B D2 C2 D5
	//                                    B C1 D4 D6
	int xpart_times_4;

	// The first part: O A A A. It equals lowest_possible_error previously calculated. 
	// lowest_possible_error is OAAA, BBBvalue is BBB and CCCvalue is C1C2C3.
	error = lowest_possible_error + BBBvalue + CCCvalue;

	// The remaining pixels to cover are D1 through D6.
	if(error <= best_error_sofar)
	{
		// Second column: D1 D2  but not C1
		xpart_times_4 = (colorH-colorO);
		error = error + square_table_percep_red[(block[4*4 + 4 + 0] - clamp_table[ (((xpart_times_4 + (colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table_percep_red[(block[4*4*2 + 4 + 0] - clamp_table[ (((xpart_times_4 + ((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		// Third column: D3 notC2 D4
		xpart_times_4 = (colorH-colorO) << 1;
		error = error + square_table_percep_red[(block[4*4 + 4*2 + 0] - clamp_table[ (((xpart_times_4 + (colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		if(error <= best_error_sofar)
		{
			error = error + square_table_percep_red[(block[4*4*3 + 4*2 + 0] - clamp_table[ (((xpart_times_4 + 3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
			// Forth column: notC3 D5 D6
			xpart_times_4 = 3*(colorH-colorO);
			error = error + square_table_percep_red[(block[4*4*2 + 4*3 + 0] - clamp_table[ (((xpart_times_4 + ((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
			error = error + square_table_percep_red[(block[4*4*3 + 4*3 + 0] - clamp_table[ (((xpart_times_4 + 3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		}
	}
	return error;
} 

// Calculating the minimum error for the block (in planar mode) if we know the red component for O and H and V.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcErrorPlanarOnlyRed(uint8 *block, int colorO, int colorH, int colorV, unsigned int lowest_possible_error, unsigned int BBBvalue, unsigned int CCCvalue, unsigned int best_error_sofar)
{
	colorO = (colorO << 2) | (colorO >> 4);
	colorH = (colorH << 2) | (colorH >> 4);
	colorV = (colorV << 2) | (colorV >> 4);

	unsigned int error;

	// The block can be partitioned into: O A  A  A
	//                                    B D1 D3 C3
	//                                    B D2 C2 D5
	//                                    B C1 D4 D6
	int xpart_times_4;

	// The first part: O A A A. It equals lowest_possible_error previously calculated. 
	// lowest_possible_error is OAAA, BBBvalue is BBB and CCCvalue is C1C2C3.
	error = lowest_possible_error + BBBvalue + CCCvalue;

	// The remaining pixels to cover are D1 through D6.
	if(error <= best_error_sofar)
	{
		// Second column: D1 D2  but not C1
		xpart_times_4 = (colorH-colorO);
		error = error + square_table[(block[4*4 + 4 + 0] - clamp_table[ (((xpart_times_4 + (colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table[(block[4*4*2 + 4 + 0] - clamp_table[ (((xpart_times_4 + ((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		// Third column: D3 notC2 D4
		xpart_times_4 = (colorH-colorO) << 1;
		error = error + square_table[(block[4*4 + 4*2 + 0] - clamp_table[ (((xpart_times_4 + (colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		if(error <= best_error_sofar)
		{
			error = error + square_table[(block[4*4*3 + 4*2 + 0] - clamp_table[ (((xpart_times_4 + 3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
			// Forth column: notC3 D5 D6
			xpart_times_4 = 3*(colorH-colorO);
			error = error + square_table[(block[4*4*2 + 4*3 + 0] - clamp_table[ (((xpart_times_4 + ((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
			error = error + square_table[(block[4*4*3 + 4*3 + 0] - clamp_table[ (((xpart_times_4 + 3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		}
	}
	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the red component for O and H.
// Uses perceptual error metrics.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcLowestPossibleGreenOHperceptual(uint8 *block, int colorO, int colorH, unsigned int best_error_sofar)
{
	colorO = (colorO << 1) | (colorO >> 6);
	colorH = (colorH << 1) | (colorH >> 6);

	unsigned int error;

	error = square_table_percep_green[(block[1] - colorO) + 255];
	error = error + square_table_percep_green[(block[4 + 1] - clamp_table[ (((   (colorH-colorO) + 4*colorO)+2)>>2) + 255])+255];
	if(error <= best_error_sofar)
	{
		error = error + square_table_percep_green[(block[4*2 + 1] - clamp_table[ (((  ((colorH-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table_percep_green[(block[4*3 + 1] - clamp_table[ ((( 3*(colorH-colorO) + 4*colorO)+2)>>2) + 255])+255];
	}
	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the red component for O and H.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcLowestPossibleGreenOH(uint8 *block, int colorO, int colorH, unsigned int best_error_sofar)
{
	colorO = (colorO << 1) | (colorO >> 6);
	colorH = (colorH << 1) | (colorH >> 6);

	unsigned int error;

	error = square_table[(block[1] - colorO) + 255];
	error = error + square_table[(block[4 + 1] - clamp_table[ (((   (colorH-colorO) + 4*colorO)+2)>>2) + 255])+255];
	if(error <= best_error_sofar)
	{
		error = error + square_table[(block[4*2 + 1] - clamp_table[ (((  ((colorH-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table[(block[4*3 + 1] - clamp_table[ ((( 3*(colorH-colorO) + 4*colorO)+2)>>2) + 255])+255];
	}
	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the green component for O and V.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcBBBgreen(uint8 *block, int colorO, int colorV)
{
	colorO = (colorO << 1) | (colorO >> 6);
	colorV = (colorV << 1) | (colorV >> 6);

	unsigned int error = 0;
	
	// Now first column: B B B 
	/* unroll loop for( yy=0; (yy<4) && (error <= best_error_sofar); yy++)*/
	{
		error = error + square_table[(block[4*4 + 1] - clamp_table[ ((((colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table[(block[4*4*2 + 1] - clamp_table[ (((((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table[(block[4*4*3 + 1] - clamp_table[ (((3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
	}

	return error;

}

// Calculating the minimum error for the block (in planar mode) if we know the green component for H and V.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcCCCgreen(uint8 *block, int colorH, int colorV)
{
	colorH = (colorH << 1) | (colorH >> 6);
	colorV = (colorV << 1) | (colorV >> 6);

	unsigned int error=0;

	error = error + square_table[(block[4*4*3 + 4 + 1] - clamp_table[ (((colorH + 3*colorV)+2)>>2) + 255])+255];
	error = error + square_table[(block[4*4*2 + 4*2 + 1] - clamp_table[ (((2*colorH + 2*colorV)+2)>>2) + 255])+255];
	error = error + square_table[(block[4*4 + 4*3 + 1] - clamp_table[ (((3*colorH + colorV)+2)>>2) + 255])+255];
	
	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the green component for H V and O.
// Uses perceptual error metric.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcErrorPlanarOnlyGreenPerceptual(uint8 *block, int colorO, int colorH, int colorV, unsigned int lowest_possible_error, unsigned int BBBvalue, unsigned int CCCvalue, unsigned int best_error_sofar)
{
	colorO = (colorO << 1) | (colorO >> 6);
	colorH = (colorH << 1) | (colorH >> 6);
	colorV = (colorV << 1) | (colorV >> 6);

	unsigned int error;

	// The block can be partitioned into: O A  A  A
	//                                    B D1 D3 C3
	//                                    B D2 C2 D5
	//                                    B C1 D4 D6

	int xpart_times_4;

	// The first part: O A A A. It equals lowest_possible_error previously calculated. 
	// lowest_possible_error is OAAA, BBBvalue is BBB and CCCvalue is C1C2C3.
	error = lowest_possible_error + BBBvalue + CCCvalue;

	// The remaining pixels to cover are D1 through D6.
	if(error <= best_error_sofar)
	{
		// Second column: D1 D2  but not C1
		xpart_times_4 = (colorH-colorO);
		error = error + square_table_percep_green[(block[4*4 + 4 + 1] - clamp_table[ (((xpart_times_4 + (colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table_percep_green[(block[4*4*2 + 4 + 1] - clamp_table[ (((xpart_times_4 + ((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		// Third column: D3 notC2 D4
		xpart_times_4 = (colorH-colorO) << 1;
		error = error + square_table_percep_green[(block[4*4 + 4*2 + 1] - clamp_table[ (((xpart_times_4 + (colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		if(error <= best_error_sofar)
		{
			error = error + square_table_percep_green[(block[4*4*3 + 4*2 + 1] - clamp_table[ (((xpart_times_4 + 3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
			// Forth column: notC3 D5 D6
			xpart_times_4 = 3*(colorH-colorO);
			error = error + square_table_percep_green[(block[4*4*2 + 4*3 + 1] - clamp_table[ (((xpart_times_4 + ((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
			error = error + square_table_percep_green[(block[4*4*3 + 4*3 + 1] - clamp_table[ (((xpart_times_4 + 3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		}
	}
	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the green component for H V and O.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcErrorPlanarOnlyGreen(uint8 *block, int colorO, int colorH, int colorV, unsigned int lowest_possible_error, unsigned int BBBvalue, unsigned int CCCvalue, unsigned int best_error_sofar)
{
	colorO = (colorO << 1) | (colorO >> 6);
	colorH = (colorH << 1) | (colorH >> 6);
	colorV = (colorV << 1) | (colorV >> 6);

	unsigned int error;

	// The block can be partitioned into: O A  A  A
	//                                    B D1 D3 C3
	//                                    B D2 C2 D5
	//                                    B C1 D4 D6
	int xpart_times_4;

	// The first part: O A A A. It equals lowest_possible_error previously calculated. 
	// lowest_possible_error is OAAA, BBBvalue is BBB and CCCvalue is C1C2C3.
	error = lowest_possible_error + BBBvalue + CCCvalue;

	// The remaining pixels to cover are D1 through D6.
	if(error <= best_error_sofar)
	{
		// Second column: D1 D2  but not C1
		xpart_times_4 = (colorH-colorO);
		error = error + square_table[(block[4*4 + 4 + 1] - clamp_table[ (((xpart_times_4 + (colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table[(block[4*4*2 + 4 + 1] - clamp_table[ (((xpart_times_4 + ((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		// Third column: D3 notC2 D4
		xpart_times_4 = (colorH-colorO) << 1;
		error = error + square_table[(block[4*4 + 4*2 + 1] - clamp_table[ (((xpart_times_4 + (colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		if(error <= best_error_sofar)
		{
			error = error + square_table[(block[4*4*3 + 4*2 + 1] - clamp_table[ (((xpart_times_4 + 3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
			// Forth column: notC3 D5 D6
			xpart_times_4 = 3*(colorH-colorO);
			error = error + square_table[(block[4*4*2 + 4*3 + 1] - clamp_table[ (((xpart_times_4 + ((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
			error = error + square_table[(block[4*4*3 + 4*3 + 1] - clamp_table[ (((xpart_times_4 + 3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		}
	}
	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the blue component for O and V.
// Uses perceptual error metric.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcBBBbluePerceptual(uint8 *block, int colorO, int colorV)
{
	colorO = (colorO << 2) | (colorO >> 4);
	colorV = (colorV << 2) | (colorV >> 4);

	unsigned int error = 0;
	
	// Now first column: B B B 
	/* unroll loop for( yy=0; (yy<4) && (error <= best_error_sofar); yy++)*/
	{
		error = error + square_table_percep_blue[(block[4*4 + 2] - clamp_table[ ((((colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table_percep_blue[(block[4*4*2 + 2] - clamp_table[ (((((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table_percep_blue[(block[4*4*3 + 2] - clamp_table[ (((3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
	}

	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the blue component for O and V.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcBBBblue(uint8 *block, int colorO, int colorV)
{
	colorO = (colorO << 2) | (colorO >> 4);
	colorV = (colorV << 2) | (colorV >> 4);

	unsigned int error = 0;
	
	// Now first column: B B B 
	/* unroll loop for( yy=0; (yy<4) && (error <= best_error_sofar); yy++)*/
	{
		error = error + square_table[(block[4*4 + 2] - clamp_table[ ((((colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table[(block[4*4*2 + 2] - clamp_table[ (((((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table[(block[4*4*3 + 2] - clamp_table[ (((3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
	}

	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the blue component for H and V.
// Uses perceptual error metric.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcCCCbluePerceptual(uint8 *block, int colorH, int colorV)
{
	colorH = (colorH << 2) | (colorH >> 4);
	colorV = (colorV << 2) | (colorV >> 4);

	unsigned int error=0;

	error = error + square_table_percep_blue[(block[4*4*3 + 4 + 2] - clamp_table[ (((colorH + 3*colorV)+2)>>2) + 255])+255];
	error = error + square_table_percep_blue[(block[4*4*2 + 4*2 + 2] - clamp_table[ (((2*colorH + 2*colorV)+2)>>2) + 255])+255];
	error = error + square_table_percep_blue[(block[4*4 + 4*3 + 2] - clamp_table[ (((3*colorH + colorV)+2)>>2) + 255])+255];
	
	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the blue component for O and V.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcCCCblue(uint8 *block, int colorH, int colorV)
{
	colorH = (colorH << 2) | (colorH >> 4);
	colorV = (colorV << 2) | (colorV >> 4);

	unsigned int error=0;

	error = error + square_table[(block[4*4*3 + 4 + 2] - clamp_table[ (((colorH + 3*colorV)+2)>>2) + 255])+255];
	error = error + square_table[(block[4*4*2 + 4*2 + 2] - clamp_table[ (((2*colorH + 2*colorV)+2)>>2) + 255])+255];
	error = error + square_table[(block[4*4 + 4*3 + 2] - clamp_table[ (((3*colorH + colorV)+2)>>2) + 255])+255];
	
	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the blue component for O and H.
// Uses perceptual error metric.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcLowestPossibleBlueOHperceptual(uint8 *block, int colorO, int colorH, unsigned int best_error_sofar)
{
	colorO = (colorO << 2) | (colorO >> 4);
	colorH = (colorH << 2) | (colorH >> 4);

	unsigned int error;

	error = square_table_percep_blue[(block[2] - colorO) + 255];
	error = error + square_table_percep_blue[(block[4+2] - clamp_table[ (((   (colorH-colorO) + 4*colorO)+2)>>2) + 255])+255];
	if(error <= best_error_sofar)
	{
		error = error + square_table_percep_blue[(block[4*2+2] - clamp_table[ (((  ((colorH-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table_percep_blue[(block[4*3+2] - clamp_table[ ((( 3*(colorH-colorO) + 4*colorO)+2)>>2) + 255])+255];
	}
	
	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the blue component for O and H.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcLowestPossibleBlueOH(uint8 *block, int colorO, int colorH, unsigned int best_error_sofar)
{
	colorO = (colorO << 2) | (colorO >> 4);
	colorH = (colorH << 2) | (colorH >> 4);

	unsigned int error;

	error = square_table[(block[2] - colorO) + 255];
	error = error + square_table[(block[4+2] - clamp_table[ (((   (colorH-colorO) + 4*colorO)+2)>>2) + 255])+255];
	if(error <= best_error_sofar)
	{
		error = error + square_table[(block[4*2+2] - clamp_table[ (((  ((colorH-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table[(block[4*3+2] - clamp_table[ ((( 3*(colorH-colorO) + 4*colorO)+2)>>2) + 255])+255];
	}
	
	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the blue component for O, V and H.
// Uses perceptual error metric.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcErrorPlanarOnlyBluePerceptual(uint8 *block, int colorO, int colorH, int colorV, unsigned int lowest_possible_error, unsigned int BBBvalue, unsigned int CCCvalue, unsigned int best_error_sofar)
{
	colorO = (colorO << 2) | (colorO >> 4);
	colorH = (colorH << 2) | (colorH >> 4);
	colorV = (colorV << 2) | (colorV >> 4);

	unsigned int error;

	// The block can be partitioned into: O A  A  A
	//                                    B D1 D3 C3
	//                                    B D2 C2 D5
	//                                    B C1 D4 D6
	int xpart_times_4;

	// The first part: O A A A. It equals lowest_possible_error previously calculated. 
	// lowest_possible_error is OAAA, BBBvalue is BBB and CCCvalue is C1C2C3.
	error = lowest_possible_error + BBBvalue + CCCvalue;

	// The remaining pixels to cover are D1 through D6.
	if(error <= best_error_sofar)
	{
		// Second column: D1 D2  but not C1
		xpart_times_4 = (colorH-colorO);
		error = error + square_table_percep_blue[(block[4*4 + 4 + 2] - clamp_table[ (((xpart_times_4 + (colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table_percep_blue[(block[4*4*2 + 4 + 2] - clamp_table[ (((xpart_times_4 + ((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		// Third column: D3 notC2 D4
		xpart_times_4 = (colorH-colorO) << 1;
		error = error + square_table_percep_blue[(block[4*4 + 4*2 + 2] - clamp_table[ (((xpart_times_4 + (colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		if(error <= best_error_sofar)
		{
			error = error + square_table_percep_blue[(block[4*4*3 + 4*2 + 2] - clamp_table[ (((xpart_times_4 + 3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
			// Forth column: notC3 D5 D6
			xpart_times_4 = 3*(colorH-colorO);
			error = error + square_table_percep_blue[(block[4*4*2 + 4*3 + 2] - clamp_table[ (((xpart_times_4 + ((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
			error = error + square_table_percep_blue[(block[4*4*3 + 4*3 + 2] - clamp_table[ (((xpart_times_4 + 3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		}
	}
	
	return error;
}

// Calculating the minimum error for the block (in planar mode) if we know the blue component for O, V and H.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calcErrorPlanarOnlyBlue(uint8 *block, int colorO, int colorH, int colorV, unsigned int lowest_possible_error, unsigned int BBBvalue, unsigned int CCCvalue, unsigned int best_error_sofar)
{
	colorO = (colorO << 2) | (colorO >> 4);
	colorH = (colorH << 2) | (colorH >> 4);
	colorV = (colorV << 2) | (colorV >> 4);

	unsigned int error;

	// The block can be partitioned into: O A  A  A
	//                                    B D1 D3 C3
	//                                    B D2 C2 D5
	//                                    B C1 D4 D6
	int xpart_times_4;

	// The first part: O A A A. It equals lowest_possible_error previously calculated. 
	// lowest_possible_error is OAAA, BBBvalue is BBB and CCCvalue is C1C2C3.
	error = lowest_possible_error + BBBvalue + CCCvalue;

	// The remaining pixels to cover are D1 through D6.
	if(error <= best_error_sofar)
	{
		// Second column: D1 D2  but not C1
		xpart_times_4 = (colorH-colorO);
		error = error + square_table[(block[4*4 + 4 + 2] - clamp_table[ (((xpart_times_4 + (colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		error = error + square_table[(block[4*4*2 + 4 + 2] - clamp_table[ (((xpart_times_4 + ((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
		// Third column: D3 notC2 D4
		xpart_times_4 = (colorH-colorO) << 1;
		error = error + square_table[(block[4*4 + 4*2 + 2] - clamp_table[ (((xpart_times_4 + (colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		if(error <= best_error_sofar)
		{
			error = error + square_table[(block[4*4*3 + 4*2 + 2] - clamp_table[ (((xpart_times_4 + 3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
			// Forth column: notC3 D5 D6
			xpart_times_4 = 3*(colorH-colorO);
			error = error + square_table[(block[4*4*2 + 4*3 + 2] - clamp_table[ (((xpart_times_4 + ((colorV-colorO)<<1) + 4*colorO)+2)>>2) + 255])+255];
			error = error + square_table[(block[4*4*3 + 4*3 + 2] - clamp_table[ (((xpart_times_4 + 3*(colorV-colorO) + 4*colorO)+2)>>2) + 255])+255];
		}
	}

	return error;
}



// This function uses least squares in order to determine the best values of the plane. 
// This is close to optimal, but not quite, due to nonlinearities in the expantion from 6 and 7 bits to 8, and
// in the clamping to a number between 0 and the maximum. 
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockPlanar57(uint8 *img, int width,int height,int startx,int starty, unsigned int &compressed57_1, unsigned int &compressed57_2)
{
	// Use least squares to find the solution with the smallest error.
	// That is, find the vector x so that |Ax-b|^2 is minimized, where
	// x = [Ro Rr Rv]';
	// A = [1 3/4 2/4 1/4 3/4 2/4 1/4  0  2/4 1/4  0  -1/4  1/4  0  -1/4 -2/4 ; 
    //      0 1/4 2/4 3/4  0  1/4 2/4 3/4  0  1/4 2/4  3/4   0  1/4  2/4  3/4 ;
	//      0  0   0   0  1/4 1/4 1/4 1/4 2/4 2/4 2/4  2/4; 3/4 3/4  3/4  3/4]';
	// b = [r11 r12 r13 r14 r21 r22 r23 r24 r31 r32 r33 r34 r41 r42 r43 r44];
	//
	// That is, find solution x = inv(A' * A) * A' * b
	//                          = C * A' * b;
	// C is always the same, so we have calculated it off-line here.
	//                          = C * D
	int xx,yy, cc;
	double coeffsA[48]= { 1.00, 0.00, 0.00, 
		                  0.75, 0.25, 0.00,
						  0.50, 0.50, 0.00, 
						  0.25, 0.75, 0.00, 
		                  0.75, 0.00, 0.25, 
		                  0.50, 0.25, 0.25,
						  0.25, 0.50, 0.25, 
						  0.00, 0.75, 0.25,
						  0.50, 0.00, 0.50, 
		                  0.25, 0.25, 0.50,
						  0.00, 0.50, 0.50, 
						 -0.25, 0.75, 0.50, 
						  0.25, 0.00, 0.75, 
		                  0.00, 0.25, 0.75,
						 -0.25, 0.50, 0.75, 
						 -0.50, 0.75, 0.75};

	double coeffsC[9] = {0.2875, -0.0125, -0.0125, -0.0125, 0.4875, -0.3125, -0.0125, -0.3125, 0.4875};
	double colorO[3], colorH[3], colorV[3];
	uint8 colorO8[3], colorH8[3], colorV8[3];
	
	dMatrix *D_matrix;
	dMatrix *x_vector;

	dMatrix A_matrix; A_matrix.width = 3; A_matrix.height = 16; 
	A_matrix.data = coeffsA;
	dMatrix C_matrix; C_matrix.width = 3; C_matrix.height = 3; 
	C_matrix.data = coeffsC;
	dMatrix b_vector; b_vector.width = 1; b_vector.height = 16; 
    b_vector.data = (double*) malloc(sizeof(double)*b_vector.width*b_vector.height);
	transposeMatrix(&A_matrix);

	// Red component

	// Load color data into vector b:
	for(cc = 0, yy = 0; yy<4; yy++)
	   for(xx = 0; xx<4; xx++)
		   b_vector.data[cc++] = img[3*width*(starty+yy) + 3*(startx+xx) + 0];

	D_matrix = multiplyMatrices(&A_matrix, &b_vector);
	x_vector = multiplyMatrices(&C_matrix, D_matrix);

	colorO[0] = CLAMP(0.0, x_vector->data[0], 255.0);
	colorH[0] = CLAMP(0.0, x_vector->data[1], 255.0);
	colorV[0] = CLAMP(0.0, x_vector->data[2], 255.0);

	free(D_matrix->data); free(D_matrix);
	free(x_vector->data); free(x_vector);

	// Green component

	// Load color data into vector b:
	for(cc = 0, yy = 0; yy<4; yy++)
	   for(xx = 0; xx<4; xx++)
		   b_vector.data[cc++] = img[3*width*(starty+yy) + 3*(startx+xx) + 1];

	D_matrix = multiplyMatrices(&A_matrix, &b_vector);
	x_vector = multiplyMatrices(&C_matrix, D_matrix);

	colorO[1] = CLAMP(0.0, x_vector->data[0], 255.0);
	colorH[1] = CLAMP(0.0, x_vector->data[1], 255.0);
	colorV[1] = CLAMP(0.0, x_vector->data[2], 255.0);

	free(D_matrix->data); free(D_matrix);
	free(x_vector->data); free(x_vector);

	// Blue component

	// Load color data into vector b:
	for(cc = 0, yy = 0; yy<4; yy++)
	   for(xx = 0; xx<4; xx++)
		   b_vector.data[cc++] = img[3*width*(starty+yy) + 3*(startx+xx) + 2];

	D_matrix = multiplyMatrices(&A_matrix, &b_vector);
	x_vector = multiplyMatrices(&C_matrix, D_matrix);

	colorO[2] = CLAMP(0.0, x_vector->data[0], 255.0);
	colorH[2] = CLAMP(0.0, x_vector->data[1], 255.0);
	colorV[2] = CLAMP(0.0, x_vector->data[2], 255.0);

	free(D_matrix->data); free(D_matrix);
	free(x_vector->data); free(x_vector);

	// Quantize to 6 bits
	double D = 255*(1.0/((1<<6)-1.0) );
	colorO8[0] = JAS_ROUND((1.0*colorO[0])/D);
	colorO8[2] = JAS_ROUND((1.0*colorO[2])/D);
	colorH8[0] = JAS_ROUND((1.0*colorH[0])/D);
	colorH8[2] = JAS_ROUND((1.0*colorH[2])/D);
	colorV8[0] = JAS_ROUND((1.0*colorV[0])/D);
	colorV8[2] = JAS_ROUND((1.0*colorV[2])/D);

	// Quantize to 7 bits
	D = 255*(1.0/((1<<7)-1.0) );
	colorO8[1] = JAS_ROUND((1.0*colorO[1])/D);
	colorH8[1] = JAS_ROUND((1.0*colorH[1])/D);
	colorV8[1] = JAS_ROUND((1.0*colorV[1])/D);

	// Pack bits in 57 bits

	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 
	//      ------------------------------------------------------------------------------------------------
	//     | R0              | G0                 | B0              | RH              | GH                  |
	//      ------------------------------------------------------------------------------------------------
	//
	//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
	//      ------------------------------------------------------------------------------------------------
	//     | BH              | RV              |  GV                | BV               | not used           |   
	//      ------------------------------------------------------------------------------------------------

	compressed57_1 = 0;
	compressed57_2 = 0;
	PUTBITSHIGH( compressed57_1, colorO8[0], 6, 63);
	PUTBITSHIGH( compressed57_1, colorO8[1], 7, 57);
	PUTBITSHIGH( compressed57_1, colorO8[2], 6, 50);
	PUTBITSHIGH( compressed57_1, colorH8[0], 6, 44);
	PUTBITSHIGH( compressed57_1, colorH8[1], 7, 38);
	PUTBITS(     compressed57_2, colorH8[2], 6, 31);
	PUTBITS(     compressed57_2, colorV8[0], 6, 25);
	PUTBITS(     compressed57_2, colorV8[1], 7, 19);
	PUTBITS(     compressed57_2, colorV8[2], 6, 12);
}

// During search it is not convenient to store the bits the way they are stored in the 
// file format. Hence, after search, it is converted to this format.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void stuff57bits(unsigned int planar57_word1, unsigned int planar57_word2, unsigned int &planar_word1, unsigned int &planar_word2)
{
	// Put bits in twotimer configuration for 57 bits (red and green dont overflow, green does)
	// 
	// Go from this bit layout:
	//
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 
	//      -----------------------------------------------------------------------------------------------
	//     |R0               |G01G02              |B01B02  ;B03     |RH1           |RH2|GH                 |
	//      -----------------------------------------------------------------------------------------------
	//
	//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
	//      -----------------------------------------------------------------------------------------------
	//     |BH               |RV               |GV                  |BV                | not used          |   
	//      -----------------------------------------------------------------------------------------------
	//
	//  To this:
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 
	//      ------------------------------------------------------------------------------------------------
	//     |//|R0               |G01|/|G02              |B01|/ // //|B02  |//|B03     |RH1           |df|RH2|
	//      ------------------------------------------------------------------------------------------------
	//
	//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
	//      -----------------------------------------------------------------------------------------------
	//     |GH                  |BH               |RV               |GV                   |BV              |
	//      -----------------------------------------------------------------------------------------------
	//
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |diff|flip|
	//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------

	uint8 RO, GO1, GO2, BO1, BO2, BO3, RH1, RH2, GH, BH, RV, GV, BV;
	uint8 bit, a, b, c, d, bits;

	RO = GETBITSHIGH( planar57_word1, 6, 63);
	GO1= GETBITSHIGH( planar57_word1, 1, 57);
	GO2= GETBITSHIGH( planar57_word1, 6, 56);
	BO1= GETBITSHIGH( planar57_word1, 1, 50);
	BO2= GETBITSHIGH( planar57_word1, 2, 49);
	BO3= GETBITSHIGH( planar57_word1, 3, 47);
	RH1= GETBITSHIGH( planar57_word1, 5, 44);
	RH2= GETBITSHIGH( planar57_word1, 1, 39);
	GH = GETBITSHIGH( planar57_word1, 7, 38);
	BH = GETBITS(     planar57_word2, 6, 31);
	RV = GETBITS(     planar57_word2, 6, 25);
	GV = GETBITS(     planar57_word2, 7, 19);
	BV = GETBITS(     planar57_word2, 6, 12);

	planar_word1 = 0; planar_word2 = 0;
	PUTBITSHIGH( planar_word1, RO,  6, 62);
	PUTBITSHIGH( planar_word1, GO1, 1, 56);
	PUTBITSHIGH( planar_word1, GO2, 6, 54);
	PUTBITSHIGH( planar_word1, BO1, 1, 48);
	PUTBITSHIGH( planar_word1, BO2, 2, 44);
	PUTBITSHIGH( planar_word1, BO3, 3, 41);
	PUTBITSHIGH( planar_word1, RH1, 5, 38);
	PUTBITSHIGH( planar_word1, RH2, 1, 32);
	PUTBITS(     planar_word2, GH,  7, 31);
	PUTBITS(     planar_word2, BH,  6, 24);
	PUTBITS(     planar_word2, RV,  6, 18);
	PUTBITS(     planar_word2, GV,  7, 12);
	PUTBITS(     planar_word2, BV,  6,  5);

	// Make sure that red does not overflow:
	bit = GETBITSHIGH( planar_word1, 1, 62);
	PUTBITSHIGH( planar_word1, !bit,  1, 63);

	// Make sure that green does not overflow:
	bit = GETBITSHIGH( planar_word1, 1, 54);
	PUTBITSHIGH( planar_word1, !bit,  1, 55);

	// Make sure that blue overflows:
	a = GETBITSHIGH( planar_word1, 1, 44);
	b = GETBITSHIGH( planar_word1, 1, 43);
	c = GETBITSHIGH( planar_word1, 1, 41);
	d = GETBITSHIGH( planar_word1, 1, 40);
	// The following bit abcd bit sequences should be padded with ones: 0111, 1010, 1011, 1101, 1110, 1111
	// The following logical expression checks for the presence of any of those:
	bit = (a & c) | (!a & b & c & d) | (a & b & !c & d);
	bits = 0xf*bit;
	PUTBITSHIGH( planar_word1, bits,  3, 47);
	PUTBITSHIGH( planar_word1, !bit,  1, 42);

	// Set diffbit
	PUTBITSHIGH( planar_word1, 1,  1, 33);
}

// During search it is not convenient to store the bits the way they are stored in the 
// file format. Hence, after search, it is converted to this format.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void stuff58bits(unsigned int thumbH58_word1, unsigned int thumbH58_word2, unsigned int &thumbH_word1, unsigned int &thumbH_word2)
{
	// Put bits in twotimer configuration for 58 (red doesn't overflow, green does)
	// 
	// Go from this bit layout:
	//
	//
	//     |63 62 61 60 59 58|57 56 55 54|53 52 51 50|49 48 47 46|45 44 43 42|41 40 39 38|37 36 35 34|33 32|
	//     |-------empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|d2 d1|
	//
	//     |31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
	//     |---------------------------------------index bits----------------------------------------------|
	//
	//  To this:
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 
	//      -----------------------------------------------------------------------------------------------
	//     |//|R0         |G0      |// // //|G0|B0|//|B0b     |R1         |G1         |B0         |d2|df|d1|
	//      -----------------------------------------------------------------------------------------------
	//
	//     |31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
	//     |---------------------------------------index bits----------------------------------------------|
	//
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 
	//      -----------------------------------------------------------------------------------------------
	//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |df|fp|
	//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bt|bt|
	//      -----------------------------------------------------------------------------------------------
	//
	//
	// Thus, what we are really doing is going from this bit layout:
	//
	//
	//     |63 62 61 60 59 58|57 56 55 54 53 52 51|50 49|48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33|32   |
	//     |-------empty-----|part0---------------|part1|part2------------------------------------------|part3|
	//
	//  To this:
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 
	//      --------------------------------------------------------------------------------------------------|
	//     |//|part0               |// // //|part1|//|part2                                          |df|part3|
	//      --------------------------------------------------------------------------------------------------|

	unsigned int part0, part1, part2, part3;
	uint8 bit, a, b, c, d, bits;

	// move parts
	part0 = GETBITSHIGH( thumbH58_word1, 7, 57);
	part1 = GETBITSHIGH( thumbH58_word1, 2, 50);
	part2 = GETBITSHIGH( thumbH58_word1,16, 48);
	part3 = GETBITSHIGH( thumbH58_word1, 1, 32);
	thumbH_word1 = 0;
	PUTBITSHIGH( thumbH_word1, part0,  7, 62);
	PUTBITSHIGH( thumbH_word1, part1,  2, 52);
	PUTBITSHIGH( thumbH_word1, part2, 16, 49);
	PUTBITSHIGH( thumbH_word1, part3,  1, 32);

	// Make sure that red does not overflow:
	bit = GETBITSHIGH( thumbH_word1, 1, 62);
	PUTBITSHIGH( thumbH_word1, !bit,  1, 63);

	// Make sure that green overflows:
	a = GETBITSHIGH( thumbH_word1, 1, 52);
	b = GETBITSHIGH( thumbH_word1, 1, 51);
	c = GETBITSHIGH( thumbH_word1, 1, 49);
	d = GETBITSHIGH( thumbH_word1, 1, 48);
	// The following bit abcd bit sequences should be padded with ones: 0111, 1010, 1011, 1101, 1110, 1111
	// The following logical expression checks for the presence of any of those:
	bit = (a & c) | (!a & b & c & d) | (a & b & !c & d);
	bits = 0xf*bit;
	PUTBITSHIGH( thumbH_word1, bits,  3, 55);
	PUTBITSHIGH( thumbH_word1, !bit,  1, 50);

	// Set diffbit
	PUTBITSHIGH( thumbH_word1, 1,  1, 33);
	thumbH_word2 = thumbH58_word2;

}

// copy of above, but diffbit is 0
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void stuff58bitsDiffFalse(unsigned int thumbH58_word1, unsigned int thumbH58_word2, unsigned int &thumbH_word1, unsigned int &thumbH_word2)
{
	unsigned int part0, part1, part2, part3;
	uint8 bit, a, b, c, d, bits;

	// move parts
	part0 = GETBITSHIGH( thumbH58_word1, 7, 57);
	part1 = GETBITSHIGH( thumbH58_word1, 2, 50);
	part2 = GETBITSHIGH( thumbH58_word1,16, 48);
	part3 = GETBITSHIGH( thumbH58_word1, 1, 32);
	thumbH_word1 = 0;
	PUTBITSHIGH( thumbH_word1, part0,  7, 62);
	PUTBITSHIGH( thumbH_word1, part1,  2, 52);
	PUTBITSHIGH( thumbH_word1, part2, 16, 49);
	PUTBITSHIGH( thumbH_word1, part3,  1, 32);

	// Make sure that red does not overflow:
	bit = GETBITSHIGH( thumbH_word1, 1, 62);
	PUTBITSHIGH( thumbH_word1, !bit,  1, 63);

	// Make sure that green overflows:
	a = GETBITSHIGH( thumbH_word1, 1, 52);
	b = GETBITSHIGH( thumbH_word1, 1, 51);
	c = GETBITSHIGH( thumbH_word1, 1, 49);
	d = GETBITSHIGH( thumbH_word1, 1, 48);
	// The following bit abcd bit sequences should be padded with ones: 0111, 1010, 1011, 1101, 1110, 1111
	// The following logical expression checks for the presence of any of those:
	bit = (a & c) | (!a & b & c & d) | (a & b & !c & d);
	bits = 0xf*bit;
	PUTBITSHIGH( thumbH_word1, bits,  3, 55);
	PUTBITSHIGH( thumbH_word1, !bit,  1, 50);

	// Set diffbit
	PUTBITSHIGH( thumbH_word1, 0,  1, 33);
	thumbH_word2 = thumbH58_word2;

}

// During search it is not convenient to store the bits the way they are stored in the 
// file format. Hence, after search, it is converted to this format.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void stuff59bits(unsigned int thumbT59_word1, unsigned int thumbT59_word2, unsigned int &thumbT_word1, unsigned int &thumbT_word2)
{
	// Put bits in twotimer configuration for 59 (red overflows)
	// 
	// Go from this bit layout:
	//
	//     |63 62 61 60 59|58 57 56 55|54 53 52 51|50 49 48 47|46 45 44 43|42 41 40 39|38 37 36 35|34 33 32|
	//     |----empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|--dist--|
	//
	//     |31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
	//     |----------------------------------------index bits---------------------------------------------|
	//
	//
	//  To this:
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 
	//      -----------------------------------------------------------------------------------------------
	//     |// // //|R0a  |//|R0b  |G0         |B0         |R1         |G1         |B1          |da  |df|db|
	//      -----------------------------------------------------------------------------------------------
	//
	//     |31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
	//     |----------------------------------------index bits---------------------------------------------|
	//
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 
	//      -----------------------------------------------------------------------------------------------
	//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |df|fp|
	//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bt|bt|
	//      ------------------------------------------------------------------------------------------------

	uint8 R0a;
	uint8 bit, a, b, c, d, bits;

	R0a = GETBITSHIGH( thumbT59_word1, 2, 58);

	// Fix middle part
	thumbT_word1 = thumbT59_word1 << 1;
	// Fix R0a (top two bits of R0)
	PUTBITSHIGH( thumbT_word1, R0a,  2, 60);
	// Fix db (lowest bit of d)
	PUTBITSHIGH( thumbT_word1, thumbT59_word1,  1, 32);
	// 
	// Make sure that red overflows:
	a = GETBITSHIGH( thumbT_word1, 1, 60);
	b = GETBITSHIGH( thumbT_word1, 1, 59);
	c = GETBITSHIGH( thumbT_word1, 1, 57);
	d = GETBITSHIGH( thumbT_word1, 1, 56);
	// The following bit abcd bit sequences should be padded with ones: 0111, 1010, 1011, 1101, 1110, 1111
	// The following logical expression checks for the presence of any of those:
	bit = (a & c) | (!a & b & c & d) | (a & b & !c & d);
	bits = 0xf*bit;
	PUTBITSHIGH( thumbT_word1, bits,  3, 63);
	PUTBITSHIGH( thumbT_word1, !bit,  1, 58);

	// Set diffbit
	PUTBITSHIGH( thumbT_word1, 1,  1, 33);
	thumbT_word2 = thumbT59_word2;
}


// Decompress the planar mode and calculate the error per component compared to original image.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void decompressBlockPlanar57errorPerComponent(unsigned int compressed57_1, unsigned int compressed57_2, uint8 *img,int width,int height,int startx,int starty, uint8 *srcimg, unsigned int &error_red, unsigned int &error_green, unsigned int &error_blue)
{
	uint8 colorO[3], colorH[3], colorV[3];

	colorO[0] = GETBITSHIGH( compressed57_1, 6, 63);
	colorO[1] = GETBITSHIGH( compressed57_1, 7, 57);
	colorO[2] = GETBITSHIGH( compressed57_1, 6, 50);
	colorH[0] = GETBITSHIGH( compressed57_1, 6, 44);
	colorH[1] = GETBITSHIGH( compressed57_1, 7, 38);
	colorH[2] = GETBITS(     compressed57_2, 6, 31);
	colorV[0] = GETBITS(     compressed57_2, 6, 25);
	colorV[1] = GETBITS(     compressed57_2, 7, 19);
	colorV[2] = GETBITS(     compressed57_2, 6, 12);

	colorO[0] = (colorO[0] << 2) | (colorO[0] >> 4);
	colorO[1] = (colorO[1] << 1) | (colorO[1] >> 6);
	colorO[2] = (colorO[2] << 2) | (colorO[2] >> 4);

	colorH[0] = (colorH[0] << 2) | (colorH[0] >> 4);
	colorH[1] = (colorH[1] << 1) | (colorH[1] >> 6);
	colorH[2] = (colorH[2] << 2) | (colorH[2] >> 4);

	colorV[0] = (colorV[0] << 2) | (colorV[0] >> 4);
	colorV[1] = (colorV[1] << 1) | (colorV[1] >> 6);
	colorV[2] = (colorV[2] << 2) | (colorV[2] >> 4);
	
	int xx, yy;

	for( xx=0; xx<4; xx++)
	{
		for( yy=0; yy<4; yy++)
		{
			img[3*width*(starty+yy) + 3*(startx+xx) + 0] = (int)CLAMP(0, JAS_ROUND((xx*(colorH[0]-colorO[0])/4.0 + yy*(colorV[0]-colorO[0])/4.0 + colorO[0])), 255);
			img[3*width*(starty+yy) + 3*(startx+xx) + 1] = (int)CLAMP(0, JAS_ROUND((xx*(colorH[1]-colorO[1])/4.0 + yy*(colorV[1]-colorO[1])/4.0 + colorO[1])), 255);
			img[3*width*(starty+yy) + 3*(startx+xx) + 2] = (int)CLAMP(0, JAS_ROUND((xx*(colorH[2]-colorO[2])/4.0 + yy*(colorV[2]-colorO[2])/4.0 + colorO[2])), 255);
		}
	}

	error_red = 0;
	error_green= 0;
	error_blue = 0;
	for( xx=0; xx<4; xx++)
	{
		for( yy=0; yy<4; yy++)
		{
			error_red = error_red + SQUARE(srcimg[3*width*(starty+yy) + 3*(startx+xx) + 0] - img[3*width*(starty+yy) + 3*(startx+xx) + 0]); 
			error_green = error_green + SQUARE(srcimg[3*width*(starty+yy) + 3*(startx+xx) + 1] - img[3*width*(starty+yy) + 3*(startx+xx) + 1]);
			error_blue = error_blue + SQUARE(srcimg[3*width*(starty+yy) + 3*(startx+xx) + 2] - img[3*width*(starty+yy) + 3*(startx+xx) + 2]);

		}
	}
}

// Compress using both individual and differential mode in ETC1/ETC2 using combined color 
// quantization. Both flip modes are tried. 
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockDiffFlipCombined(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2)
{
	unsigned int compressed1_norm, compressed2_norm;
	unsigned int compressed1_flip, compressed2_flip;
	uint8 avg_color_quant1[3], avg_color_quant2[3];

	float avg_color_float1[3],avg_color_float2[3];
	int enc_color1[3], enc_color2[3], diff[3];
	int min_error=255*255*8*3;
	unsigned int best_table_indices1=0, best_table_indices2=0;
	unsigned int best_table1=0, best_table2=0;
	int diffbit;

	int norm_err=0;
	int flip_err=0;

	// First try normal blocks 2x4:

	computeAverageColor2x4noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor2x4noQuantFloat(img,width,height,startx+2,starty,avg_color_float2);

	// First test if avg_color1 is similar enough to avg_color2 so that
	// we can use differential coding of colors. 

	float eps;

	uint8 dummy[3];

	quantize555ColorCombined(avg_color_float1, enc_color1, dummy);
	quantize555ColorCombined(avg_color_float2, enc_color2, dummy);

	diff[0] = enc_color2[0]-enc_color1[0];	
	diff[1] = enc_color2[1]-enc_color1[1];	
	diff[2] = enc_color2[2]-enc_color1[2];

	if( (diff[0] >= -4) && (diff[0] <= 3) && (diff[1] >= -4) && (diff[1] <= 3) && (diff[2] >= -4) && (diff[2] <= 3) )
	{
		diffbit = 1;

		// The difference to be coded:

		diff[0] = enc_color2[0]-enc_color1[0];	
		diff[1] = enc_color2[1]-enc_color1[1];	
		diff[2] = enc_color2[2]-enc_color1[2];

		avg_color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
		avg_color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
		avg_color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
		avg_color_quant2[0] = enc_color2[0] << 3 | (enc_color2[0] >> 2);
		avg_color_quant2[1] = enc_color2[1] << 3 | (enc_color2[1] >> 2);
		avg_color_quant2[2] = enc_color2[2] << 3 | (enc_color2[2] >> 2);

		// Pack bits into the first word. 

		//     ETC1_RGB8_OES:
		// 
		//     a) bit layout in bits 63 through 32 if diffbit = 0
		// 
		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
		//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------
		//     
		//     b) bit layout in bits 63 through 32 if diffbit = 1
		// 
		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |diff|flip|
		//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------
		// 
		//     c) bit layout in bits 31 through 0 (in both cases)
		// 
		//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3   2   1  0
		//      --------------------------------------------------------------------------------------------------
		//     |       most significant pixel index bits       |         least significant pixel index bits       |  
		//     | p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a| p| o| n| m| l| k| j| i| h| g| f| e| d| c | b | a |
		//      --------------------------------------------------------------------------------------------------      

		compressed1_norm = 0;
		PUTBITSHIGH( compressed1_norm, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_norm, enc_color1[0], 5, 63);
 		PUTBITSHIGH( compressed1_norm, enc_color1[1], 5, 55);
 		PUTBITSHIGH( compressed1_norm, enc_color1[2], 5, 47);
 		PUTBITSHIGH( compressed1_norm, diff[0],       3, 58);
 		PUTBITSHIGH( compressed1_norm, diff[1],       3, 50);
 		PUTBITSHIGH( compressed1_norm, diff[2],       3, 42);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		norm_err = 0;

		// left part of block
		norm_err = tryalltables_3bittable2x4(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);

		// right part of block
		norm_err += tryalltables_3bittable2x4(img,width,height,startx+2,starty,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_norm, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_norm, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_norm,           0,   1, 32);

		compressed2_norm = 0;
		PUTBITS( compressed2_norm, (best_pixel_indices1_MSB     ), 8, 23);
		PUTBITS( compressed2_norm, (best_pixel_indices2_MSB     ), 8, 31);
		PUTBITS( compressed2_norm, (best_pixel_indices1_LSB     ), 8, 7);
		PUTBITS( compressed2_norm, (best_pixel_indices2_LSB     ), 8, 15);

	}
	else
	{
		diffbit = 0;
		// The difference is bigger than what fits in 555 plus delta-333, so we will have
		// to deal with 444 444.

		eps = (float) 0.0001;

		uint8 dummy[3];
		quantize444ColorCombined(avg_color_float1, enc_color1, dummy);
		quantize444ColorCombined(avg_color_float2, enc_color2, dummy);

		avg_color_quant1[0] = enc_color1[0] << 4 | enc_color1[0]; 
		avg_color_quant1[1] = enc_color1[1] << 4 | enc_color1[1]; 
		avg_color_quant1[2] = enc_color1[2] << 4 | enc_color1[2];
		avg_color_quant2[0] = enc_color2[0] << 4 | enc_color2[0]; 
		avg_color_quant2[1] = enc_color2[1] << 4 | enc_color2[1]; 
		avg_color_quant2[2] = enc_color2[2] << 4 | enc_color2[2];
	

		// Pack bits into the first word. 

		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
		//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------

		compressed1_norm = 0;
		PUTBITSHIGH( compressed1_norm, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_norm, enc_color1[0], 4, 63);
 		PUTBITSHIGH( compressed1_norm, enc_color1[1], 4, 55);
 		PUTBITSHIGH( compressed1_norm, enc_color1[2], 4, 47);
 		PUTBITSHIGH( compressed1_norm, enc_color2[0], 4, 59);
 		PUTBITSHIGH( compressed1_norm, enc_color2[1], 4, 51);
 		PUTBITSHIGH( compressed1_norm, enc_color2[2], 4, 43);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		// left part of block
		norm_err = tryalltables_3bittable2x4(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);

		// right part of block
		norm_err += tryalltables_3bittable2x4(img,width,height,startx+2,starty,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_norm, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_norm, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_norm,           0,   1, 32);

		compressed2_norm = 0;
		PUTBITS( compressed2_norm, (best_pixel_indices1_MSB     ), 8, 23);
		PUTBITS( compressed2_norm, (best_pixel_indices2_MSB     ), 8, 31);
		PUTBITS( compressed2_norm, (best_pixel_indices1_LSB     ), 8, 7);
		PUTBITS( compressed2_norm, (best_pixel_indices2_LSB     ), 8, 15);
	}

	// Now try flipped blocks 4x2:

	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty+2,avg_color_float2);

	// First test if avg_color1 is similar enough to avg_color2 so that
	// we can use differential coding of colors. 

	quantize555ColorCombined(avg_color_float1, enc_color1, dummy);
	quantize555ColorCombined(avg_color_float2, enc_color2, dummy);

	diff[0] = enc_color2[0]-enc_color1[0];	
	diff[1] = enc_color2[1]-enc_color1[1];	
	diff[2] = enc_color2[2]-enc_color1[2];

	if( (diff[0] >= -4) && (diff[0] <= 3) && (diff[1] >= -4) && (diff[1] <= 3) && (diff[2] >= -4) && (diff[2] <= 3) )
	{
		diffbit = 1;

		// The difference to be coded:

		diff[0] = enc_color2[0]-enc_color1[0];	
		diff[1] = enc_color2[1]-enc_color1[1];	
		diff[2] = enc_color2[2]-enc_color1[2];

		avg_color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
		avg_color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
		avg_color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
		avg_color_quant2[0] = enc_color2[0] << 3 | (enc_color2[0] >> 2);
		avg_color_quant2[1] = enc_color2[1] << 3 | (enc_color2[1] >> 2);
		avg_color_quant2[2] = enc_color2[2] << 3 | (enc_color2[2] >> 2);

		// Pack bits into the first word. 

		compressed1_flip = 0;
		PUTBITSHIGH( compressed1_flip, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_flip, enc_color1[0], 5, 63);
 		PUTBITSHIGH( compressed1_flip, enc_color1[1], 5, 55);
 		PUTBITSHIGH( compressed1_flip, enc_color1[2], 5, 47);
 		PUTBITSHIGH( compressed1_flip, diff[0],       3, 58);
 		PUTBITSHIGH( compressed1_flip, diff[1],       3, 50);
 		PUTBITSHIGH( compressed1_flip, diff[2],       3, 42);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		// upper part of block
		flip_err = tryalltables_3bittable4x2(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
		// lower part of block
		flip_err += tryalltables_3bittable4x2(img,width,height,startx,starty+2,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_flip, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_flip, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_flip,           1,   1, 32);

		best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
		best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);
		
		compressed2_flip = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);
	}
	else
	{
		diffbit = 0;
		// The difference is bigger than what fits in 555 plus delta-333, so we will have
		// to deal with 444 444.
		eps = (float) 0.0001;

		uint8 dummy[3];
		quantize444ColorCombined(avg_color_float1, enc_color1, dummy);
		quantize444ColorCombined(avg_color_float2, enc_color2, dummy);

		avg_color_quant1[0] = enc_color1[0] << 4 | enc_color1[0]; 
		avg_color_quant1[1] = enc_color1[1] << 4 | enc_color1[1]; 
		avg_color_quant1[2] = enc_color1[2] << 4 | enc_color1[2];
		avg_color_quant2[0] = enc_color2[0] << 4 | enc_color2[0]; 
		avg_color_quant2[1] = enc_color2[1] << 4 | enc_color2[1]; 
		avg_color_quant2[2] = enc_color2[2] << 4 | enc_color2[2];

		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
		//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------


		// Pack bits into the first word. 
		compressed1_flip = 0;
		PUTBITSHIGH( compressed1_flip, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_flip, enc_color1[0], 4, 63);
 		PUTBITSHIGH( compressed1_flip, enc_color1[1], 4, 55);
 		PUTBITSHIGH( compressed1_flip, enc_color1[2], 4, 47);
 		PUTBITSHIGH( compressed1_flip, enc_color2[0], 4, 59);
 		PUTBITSHIGH( compressed1_flip, enc_color2[1], 4, 51);
 		PUTBITSHIGH( compressed1_flip, enc_color2[2], 4, 43);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		// upper part of block
		flip_err = tryalltables_3bittable4x2(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
		// lower part of block
		flip_err += tryalltables_3bittable4x2(img,width,height,startx,starty+2,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_flip, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_flip, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_flip,           1,   1, 32);

		best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
		best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);
		
		compressed2_flip = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);
	}

	// Now lets see which is the best table to use. Only 8 tables are possible. 

	if(norm_err <= flip_err)
	{
		compressed1 = compressed1_norm | 0;
		compressed2 = compressed2_norm;
	}
	else
	{
		compressed1 = compressed1_flip | 1;
		compressed2 = compressed2_flip;
	}
}

// Calculation of the two block colors using the LBG-algorithm
// The following method scales down the intensity, since this can be compensated for anyway by both the H and T mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void computeColorLBGHalfIntensityFast(uint8 *img,int width,int startx,int starty, uint8 (LBG_colors)[2][3]) 
{
	uint8 block_mask[4][4];

	// reset rand so that we get predictable output per block
	srand(10000);
	//LBG-algorithm
	double D = 0, oldD, bestD = MAXIMUM_ERROR, eps = 0.0000000001;
	double error_a, error_b;
	int number_of_iterations = 10;
	double t_color[2][3];
	double original_colors[4][4][3];
	double current_colors[2][3];
	double best_colors[2][3];
	double max_v[3];
	double min_v[3];
	int x,y,i;
	double red, green, blue;
	bool continue_seeding;
	int maximum_number_of_seedings = 10;
	int seeding;
	bool continue_iterate;

	max_v[R] = -512.0;   max_v[G] = -512.0;   max_v[B] = -512.0; 
	min_v[R] =  512.0;   min_v[G] =  512.0;   min_v[B] =  512.0;

	// resolve trainingdata
	for (y = 0; y < BLOCKHEIGHT; ++y) 
	{
		for (x = 0; x < BLOCKWIDTH; ++x) 
		{
			red = img[3*((starty+y)*width+startx+x)+R];
			green = img[3*((starty+y)*width+startx+x)+G];
			blue = img[3*((starty+y)*width+startx+x)+B];

			// Use qrs representation instead of rgb
			// qrs = Q * rgb where Q = [a a a ; b -b 0 ; c c -2c]; a = 1/sqrt(3), b= 1/sqrt(2), c = 1/sqrt(6);
			// rgb = inv(Q)*qrs  = Q' * qrs where ' denotes transpose.
			// The q variable holds intensity. r and s hold chrominance.
			// q = [0, sqrt(3)*255], r = [-255/sqrt(2), 255/sqrt(2)], s = [-2*255/sqrt(6), 2*255/sqrt(6)];
			//
			// The LGB algorithm will only act on the r and s variables and not on q.
			// 
			original_colors[x][y][R] = (1.0/sqrt(1.0*3))*red + (1.0/sqrt(1.0*3))*green + (1.0/sqrt(1.0*3))*blue;
			original_colors[x][y][G] = (1.0/sqrt(1.0*2))*red - (1.0/sqrt(1.0*2))*green;
			original_colors[x][y][B] = (1.0/sqrt(1.0*6))*red + (1.0/sqrt(1.0*6))*green - (2.0/sqrt(1.0*6))*blue;
		
			// find max
			if (original_colors[x][y][R] > max_v[R]) max_v[R] = original_colors[x][y][R];
			if (original_colors[x][y][G] > max_v[G]) max_v[G] = original_colors[x][y][G];
			if (original_colors[x][y][B] > max_v[B]) max_v[B] = original_colors[x][y][B];
			// find min
			if (original_colors[x][y][R] < min_v[R]) min_v[R] = original_colors[x][y][R];
			if (original_colors[x][y][G] < min_v[G]) min_v[G] = original_colors[x][y][G];
			if (original_colors[x][y][B] < min_v[B]) min_v[B] = original_colors[x][y][B];
		}
	}

	D = 512*512*3*16.0; 
	bestD = 512*512*3*16.0; 

	continue_seeding = true;

	// loop seeds
	for (seeding = 0; (seeding < maximum_number_of_seedings) && continue_seeding; seeding++)
	{
		// hopefully we will not need more seedings:
		continue_seeding = false;

		// calculate seeds
		for (uint8 s = 0; s < 2; ++s) 
		{
			for (uint8 c = 0; c < 3; ++c) 
			{ 
				current_colors[s][c] = double((double(rand())/RAND_MAX)*(max_v[c]-min_v[c])) + min_v[c];
			}
		}
		
		// divide into two quantization sets and calculate distortion

		continue_iterate = true;
		for(i = 0; (i < number_of_iterations) && continue_iterate; i++)
		{
			oldD = D;
			D = 0;
			int n = 0;
			for (y = 0; y < BLOCKHEIGHT; ++y) 
			{
				for (int x = 0; x < BLOCKWIDTH; ++x) 
				{
					error_a = 0.5*SQUARE(original_colors[x][y][R] - current_colors[0][R]) + 
							  SQUARE(original_colors[x][y][G] - current_colors[0][G]) +
							  SQUARE(original_colors[x][y][B] - current_colors[0][B]);
					error_b = 0.5*SQUARE(original_colors[x][y][R] - current_colors[1][R]) + 
							  SQUARE(original_colors[x][y][G] - current_colors[1][G]) +
							  SQUARE(original_colors[x][y][B] - current_colors[1][B]);
					if (error_a < error_b) 
					{
						block_mask[x][y] = 0;
						D += error_a; 
						++n;
					} 
					else 
					{
						block_mask[x][y] = 1;
						D += error_b;
					}
				}
			}

			// compare with old distortion
			if (D == 0) 
			{
				// Perfect score -- we dont need to go further iterations.
				continue_iterate = false;
				continue_seeding = false;
			}
			if (D == oldD)
			{
				// Same score as last round -- no need to go for further iterations.
				continue_iterate = false;
				continue_seeding = false;
			}
			if (D < bestD) 
			{
				bestD = D;
				for(uint8 s = 0; s < 2; ++s) 
				{
					for(uint8 c = 0; c < 3; ++c) 
					{
						best_colors[s][c] = current_colors[s][c];
					}
				}
			}
			if (n == 0 || n == BLOCKWIDTH*BLOCKHEIGHT) 
			{
				// All colors end up in the same voroni region. We need to reseed.
				continue_iterate = false;
				continue_seeding = true;
			}
			else
			{
				// Calculate new reconstruction points using the centroids

				// Find new construction values from average
				t_color[0][R] = 0;
				t_color[0][G] = 0;
				t_color[0][B] = 0;
				t_color[1][R] = 0;
				t_color[1][G] = 0;
				t_color[1][B] = 0;

				for (y = 0; y < BLOCKHEIGHT; ++y) 
				{
					for (int x = 0; x < BLOCKWIDTH; ++x) 
					{
						// use dummy value for q-parameter
						t_color[block_mask[x][y]][R] += original_colors[x][y][R];
						t_color[block_mask[x][y]][G] += original_colors[x][y][G];
						t_color[block_mask[x][y]][B] += original_colors[x][y][B];
					}
				}
				current_colors[0][R] = t_color[0][R] / n;
				current_colors[1][R] = t_color[1][R] / (BLOCKWIDTH*BLOCKHEIGHT - n);
				current_colors[0][G] = t_color[0][G] / n;
				current_colors[1][G] = t_color[1][G] / (BLOCKWIDTH*BLOCKHEIGHT - n);
				current_colors[0][B] = t_color[0][B] / n;
				current_colors[1][B] = t_color[1][B] / (BLOCKWIDTH*BLOCKHEIGHT - n);
			}
		}
	}

	for(x=0;x<2;x++)
	{
		double qq, rr, ss;

		qq = best_colors[x][0];
		rr = best_colors[x][1];
		ss = best_colors[x][2];

		current_colors[x][0] = CLAMP(0, (1.0/sqrt(1.0*3))*qq + (1.0/sqrt(1.0*2))*rr + (1.0/sqrt(1.0*6))*ss, 255);
		current_colors[x][1] = CLAMP(0, (1.0/sqrt(1.0*3))*qq - (1.0/sqrt(1.0*2))*rr + (1.0/sqrt(1.0*6))*ss, 255);
		current_colors[x][2] = CLAMP(0, (1.0/sqrt(1.0*3))*qq + (0.0        )*rr - (2.0/sqrt(1.0*6))*ss, 255);
	}

	for(x=0;x<2;x++)
		for(y=0;y<3;y++)
			LBG_colors[x][y] = JAS_ROUND(current_colors[x][y]);
}

// Calculation of the two block colors using the LBG-algorithm
// The following method scales down the intensity, since this can be compensated for anyway by both the H and T mode.
// Faster version
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void computeColorLBGNotIntensityFast(uint8 *img,int width,int startx,int starty, uint8 (LBG_colors)[2][3]) 
{
	uint8 block_mask[4][4];

	// reset rand so that we get predictable output per block
	srand(10000);
	//LBG-algorithm
	double D = 0, oldD, bestD = MAXIMUM_ERROR, eps = 0.0000000001;
	double error_a, error_b;
	int number_of_iterations = 10;
	double t_color[2][3];
	double original_colors[4][4][3];
	double current_colors[2][3];
	double best_colors[2][3];
	double max_v[3];
	double min_v[3];
	int x,y,i;
	double red, green, blue;
	bool continue_seeding;
	int maximum_number_of_seedings = 10;
	int seeding;
	bool continue_iterate;

	max_v[R] = -512.0;   max_v[G] = -512.0;   max_v[B] = -512.0; 
	min_v[R] =  512.0;   min_v[G] =  512.0;   min_v[B] =  512.0;

	// resolve trainingdata
	for (y = 0; y < BLOCKHEIGHT; ++y) 
	{
		for (x = 0; x < BLOCKWIDTH; ++x) 
		{
			red = img[3*((starty+y)*width+startx+x)+R];
			green = img[3*((starty+y)*width+startx+x)+G];
			blue = img[3*((starty+y)*width+startx+x)+B];

			// Use qrs representation instead of rgb
			// qrs = Q * rgb where Q = [a a a ; b -b 0 ; c c -2c]; a = 1/sqrt(1.0*3), b= 1/sqrt(1.0*2), c = 1/sqrt(1.0*6);
			// rgb = inv(Q)*qrs  = Q' * qrs where ' denotes transpose.
			// The q variable holds intensity. r and s hold chrominance.
			// q = [0, sqrt(1.0*3)*255], r = [-255/sqrt(1.0*2), 255/sqrt(1.0*2)], s = [-2*255/sqrt(1.0*6), 2*255/sqrt(1.0*6)];
			//
			// The LGB algorithm will only act on the r and s variables and not on q.
			// 
			original_colors[x][y][R] = (1.0/sqrt(1.0*3))*red + (1.0/sqrt(1.0*3))*green + (1.0/sqrt(1.0*3))*blue;
			original_colors[x][y][G] = (1.0/sqrt(1.0*2))*red - (1.0/sqrt(1.0*2))*green;
			original_colors[x][y][B] = (1.0/sqrt(1.0*6))*red + (1.0/sqrt(1.0*6))*green - (2.0/sqrt(1.0*6))*blue;
		
			// find max
			if (original_colors[x][y][R] > max_v[R]) max_v[R] = original_colors[x][y][R];
			if (original_colors[x][y][G] > max_v[G]) max_v[G] = original_colors[x][y][G];
			if (original_colors[x][y][B] > max_v[B]) max_v[B] = original_colors[x][y][B];
			// find min
			if (original_colors[x][y][R] < min_v[R]) min_v[R] = original_colors[x][y][R];
			if (original_colors[x][y][G] < min_v[G]) min_v[G] = original_colors[x][y][G];
			if (original_colors[x][y][B] < min_v[B]) min_v[B] = original_colors[x][y][B];
		}
	}

	D = 512*512*3*16.0; 
	bestD = 512*512*3*16.0; 

	continue_seeding = true;

	// loop seeds
	for (seeding = 0; (seeding < maximum_number_of_seedings) && continue_seeding; seeding++)
	{
		// hopefully we will not need more seedings:
		continue_seeding = false;

		// calculate seeds
		for (uint8 s = 0; s < 2; ++s) 
		{
			for (uint8 c = 0; c < 3; ++c) 
			{ 
				current_colors[s][c] = double((double(rand())/RAND_MAX)*(max_v[c]-min_v[c])) + min_v[c];
			}
		}
		// divide into two quantization sets and calculate distortion

		continue_iterate = true;
		for(i = 0; (i < number_of_iterations) && continue_iterate; i++)
		{
			oldD = D;
			D = 0;
			int n = 0;
			for (y = 0; y < BLOCKHEIGHT; ++y) 
			{
				for (int x = 0; x < BLOCKWIDTH; ++x) 
				{
					error_a = 0.0*SQUARE(original_colors[x][y][R] - current_colors[0][R]) + 
							  SQUARE(original_colors[x][y][G] - current_colors[0][G]) +
							  SQUARE(original_colors[x][y][B] - current_colors[0][B]);
					error_b = 0.0*SQUARE(original_colors[x][y][R] - current_colors[1][R]) + 
							  SQUARE(original_colors[x][y][G] - current_colors[1][G]) +
							  SQUARE(original_colors[x][y][B] - current_colors[1][B]);
					if (error_a < error_b) 
					{
						block_mask[x][y] = 0;
						D += error_a; 
						++n;
					} 
					else 
					{
						block_mask[x][y] = 1;
						D += error_b;
					}
				}
			}

			// compare with old distortion
			if (D == 0) 
			{
				// Perfect score -- we dont need to go further iterations.
				continue_iterate = false;
				continue_seeding = false;
			}
			if (D == oldD)
			{
				// Same score as last round -- no need to go for further iterations.
				continue_iterate = false;
				continue_seeding = false;
			}
			if (D < bestD) 
			{
				bestD = D;
				for(uint8 s = 0; s < 2; ++s) 
				{
					for(uint8 c = 0; c < 3; ++c) 
					{
						best_colors[s][c] = current_colors[s][c];
					}
				}
			}
			if (n == 0 || n == BLOCKWIDTH*BLOCKHEIGHT) 
			{
				// All colors end up in the same voroni region. We need to reseed.
				continue_iterate = false;
				continue_seeding = true;
			}
			else
			{
				// Calculate new reconstruction points using the centroids

				// Find new construction values from average
				t_color[0][R] = 0;
				t_color[0][G] = 0;
				t_color[0][B] = 0;
				t_color[1][R] = 0;
				t_color[1][G] = 0;
				t_color[1][B] = 0;

				for (y = 0; y < BLOCKHEIGHT; ++y) 
				{
					for (int x = 0; x < BLOCKWIDTH; ++x) 
					{
						// use dummy value for q-parameter
						t_color[block_mask[x][y]][R] += original_colors[x][y][R];
						t_color[block_mask[x][y]][G] += original_colors[x][y][G];
						t_color[block_mask[x][y]][B] += original_colors[x][y][B];
					}
				}
				current_colors[0][R] = t_color[0][R] / n;
				current_colors[1][R] = t_color[1][R] / (BLOCKWIDTH*BLOCKHEIGHT - n);
				current_colors[0][G] = t_color[0][G] / n;
				current_colors[1][G] = t_color[1][G] / (BLOCKWIDTH*BLOCKHEIGHT - n);
				current_colors[0][B] = t_color[0][B] / n;
				current_colors[1][B] = t_color[1][B] / (BLOCKWIDTH*BLOCKHEIGHT - n);
			}
		}
	}

	for(x=0;x<2;x++)
	{
		double qq, rr, ss;

		qq = best_colors[x][0];
		rr = best_colors[x][1];
		ss = best_colors[x][2];

		current_colors[x][0] = CLAMP(0, (1.0/sqrt(1.0*3))*qq + (1.0/sqrt(1.0*2))*rr + (1.0/sqrt(1.0*6))*ss, 255);
		current_colors[x][1] = CLAMP(0, (1.0/sqrt(1.0*3))*qq - (1.0/sqrt(1.0*2))*rr + (1.0/sqrt(1.0*6))*ss, 255);
		current_colors[x][2] = CLAMP(0, (1.0/sqrt(1.0*3))*qq + (0.0        )*rr - (2.0/sqrt(1.0*6))*ss, 255);
	}

	for(x=0;x<2;x++)
		for(y=0;y<3;y++)
			LBG_colors[x][y] = JAS_ROUND(current_colors[x][y]);
}

// Calculation of the two block colors using the LBG-algorithm
// The following method completely ignores the intensity, since this can be compensated for anyway by both the H and T mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void computeColorLBGNotIntensity(uint8 *img,int width,int startx,int starty, uint8 (LBG_colors)[2][3]) 
{
	uint8 block_mask[4][4];

	// reset rand so that we get predictable output per block
	srand(10000);
	//LBG-algorithm
	double D = 0, oldD, bestD = MAXIMUM_ERROR, eps = 0.0000000001;
	double error_a, error_b;
	int number_of_iterations = 10;
	double t_color[2][3];
	double original_colors[4][4][3];
	double current_colors[2][3];
	double best_colors[2][3];
	double max_v[3];
	double min_v[3];
	int x,y,i;
	double red, green, blue;
	bool continue_seeding;
	int maximum_number_of_seedings = 10;
	int seeding;
	bool continue_iterate;

	max_v[R] = -512.0;   max_v[G] = -512.0;   max_v[B] = -512.0; 
	min_v[R] =  512.0;   min_v[G] =  512.0;   min_v[B] =  512.0;

	// resolve trainingdata
	for (y = 0; y < BLOCKHEIGHT; ++y) 
	{
		for (x = 0; x < BLOCKWIDTH; ++x) 
		{
			red = img[3*((starty+y)*width+startx+x)+R];
			green = img[3*((starty+y)*width+startx+x)+G];
			blue = img[3*((starty+y)*width+startx+x)+B];

			// Use qrs representation instead of rgb
			// qrs = Q * rgb where Q = [a a a ; b -b 0 ; c c -2c]; a = 1/sqrt(1.0*3), b= 1/sqrt(1.0*2), c = 1/sqrt(1.0*6);
			// rgb = inv(Q)*qrs  = Q' * qrs where ' denotes transpose.
			// The q variable holds intensity. r and s hold chrominance.
			// q = [0, sqrt(1.0*3)*255], r = [-255/sqrt(1.0*2), 255/sqrt(1.0*2)], s = [-2*255/sqrt(1.0*6), 2*255/sqrt(1.0*6)];
			//
			// The LGB algorithm will only act on the r and s variables and not on q.
			// 
			original_colors[x][y][R] = (1.0/sqrt(1.0*3))*red + (1.0/sqrt(1.0*3))*green + (1.0/sqrt(1.0*3))*blue;
			original_colors[x][y][G] = (1.0/sqrt(1.0*2))*red - (1.0/sqrt(1.0*2))*green;
			original_colors[x][y][B] = (1.0/sqrt(1.0*6))*red + (1.0/sqrt(1.0*6))*green - (2.0/sqrt(1.0*6))*blue;

			// find max
			if (original_colors[x][y][R] > max_v[R]) max_v[R] = original_colors[x][y][R];
			if (original_colors[x][y][G] > max_v[G]) max_v[G] = original_colors[x][y][G];
			if (original_colors[x][y][B] > max_v[B]) max_v[B] = original_colors[x][y][B];
			// find min
			if (original_colors[x][y][R] < min_v[R]) min_v[R] = original_colors[x][y][R];
			if (original_colors[x][y][G] < min_v[G]) min_v[G] = original_colors[x][y][G];
			if (original_colors[x][y][B] < min_v[B]) min_v[B] = original_colors[x][y][B];
		}
	}

	D = 512*512*3*16.0; 
	bestD = 512*512*3*16.0; 

	continue_seeding = true;

	// loop seeds
	for (seeding = 0; (seeding < maximum_number_of_seedings) && continue_seeding; seeding++)
	{
		// hopefully we will not need more seedings:
		continue_seeding = false;

		// calculate seeds
		for (uint8 s = 0; s < 2; ++s) 
		{
			for (uint8 c = 0; c < 3; ++c) 
			{ 
				current_colors[s][c] = double((double(rand())/RAND_MAX)*(max_v[c]-min_v[c])) + min_v[c];
			}
		}
		
		// divide into two quantization sets and calculate distortion

		continue_iterate = true;
		for(i = 0; (i < number_of_iterations) && continue_iterate; i++)
		{
			oldD = D;
			D = 0;
			int n = 0;
			for (y = 0; y < BLOCKHEIGHT; ++y) 
			{
				for (int x = 0; x < BLOCKWIDTH; ++x) 
				{
					error_a = 0.0*SQUARE(original_colors[x][y][R] - current_colors[0][R]) + 
							  SQUARE(original_colors[x][y][G] - current_colors[0][G]) +
							  SQUARE(original_colors[x][y][B] - current_colors[0][B]);
					error_b = 0.0*SQUARE(original_colors[x][y][R] - current_colors[1][R]) + 
							  SQUARE(original_colors[x][y][G] - current_colors[1][G]) +
							  SQUARE(original_colors[x][y][B] - current_colors[1][B]);
					if (error_a < error_b) 
					{
						block_mask[x][y] = 0;
						D += error_a; 
						++n;
					} 
					else 
					{
						block_mask[x][y] = 1;
						D += error_b;
					}
				}
			}

			// compare with old distortion
			if (D == 0) 
			{
				// Perfect score -- we dont need to go further iterations.
				continue_iterate = false;
				continue_seeding = false;
			}
			if (D == oldD)
			{
				// Same score as last round -- no need to go for further iterations.
				continue_iterate = false;
				continue_seeding = true;
			}
			if (D < bestD) 
			{
				bestD = D;
				for(uint8 s = 0; s < 2; ++s) 
				{
					for(uint8 c = 0; c < 3; ++c) 
					{
						best_colors[s][c] = current_colors[s][c];
					}
				}
			}
			if (n == 0 || n == BLOCKWIDTH*BLOCKHEIGHT) 
			{
				// All colors end up in the same voroni region. We need to reseed.
				continue_iterate = false;
				continue_seeding = true;
			}
			else
			{
				// Calculate new reconstruction points using the centroids

				// Find new construction values from average
				t_color[0][R] = 0;
				t_color[0][G] = 0;
				t_color[0][B] = 0;
				t_color[1][R] = 0;
				t_color[1][G] = 0;
				t_color[1][B] = 0;

				for (y = 0; y < BLOCKHEIGHT; ++y) 
				{
					for (int x = 0; x < BLOCKWIDTH; ++x) 
					{
						// use dummy value for q-parameter
						t_color[block_mask[x][y]][R] += original_colors[x][y][R];
						t_color[block_mask[x][y]][G] += original_colors[x][y][G];
						t_color[block_mask[x][y]][B] += original_colors[x][y][B];
					}
				}
				current_colors[0][R] = t_color[0][R] / n;
				current_colors[1][R] = t_color[1][R] / (BLOCKWIDTH*BLOCKHEIGHT - n);
				current_colors[0][G] = t_color[0][G] / n;
				current_colors[1][G] = t_color[1][G] / (BLOCKWIDTH*BLOCKHEIGHT - n);
				current_colors[0][B] = t_color[0][B] / n;
				current_colors[1][B] = t_color[1][B] / (BLOCKWIDTH*BLOCKHEIGHT - n);
			}
		}
	}

	for(x=0;x<2;x++)
	{
		double qq, rr, ss;

		qq = best_colors[x][0];
		rr = best_colors[x][1];
		ss = best_colors[x][2];

		current_colors[x][0] = CLAMP(0, (1.0/sqrt(1.0*3))*qq + (1.0/sqrt(1.0*2))*rr + (1.0/sqrt(1.0*6))*ss, 255);
		current_colors[x][1] = CLAMP(0, (1.0/sqrt(1.0*3))*qq - (1.0/sqrt(1.0*2))*rr + (1.0/sqrt(1.0*6))*ss, 255);
		current_colors[x][2] = CLAMP(0, (1.0/sqrt(1.0*3))*qq + (0.0        )*rr - (2.0/sqrt(1.0*6))*ss, 255);
	}

	for(x=0;x<2;x++)
		for(y=0;y<3;y++)
			LBG_colors[x][y] = JAS_ROUND(current_colors[x][y]);
}

// Calculation of the two block colors using the LBG-algorithm
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void computeColorLBG(uint8 *img,int width,int startx,int starty, uint8 (LBG_colors)[2][3]) 
{
	uint8 block_mask[4][4];

	// reset rand so that we get predictable output per block
	srand(10000);
	//LBG-algorithm
	double D = 0, oldD, bestD = MAXIMUM_ERROR, eps = 0.0000000001;
	double error_a, error_b;
	int number_of_iterations = 10;
	double t_color[2][3];
	double original_colors[4][4][3];
	double current_colors[2][3];
	double best_colors[2][3];
	double max_v[3];
	double min_v[3];
	int x,y,i;
	double red, green, blue;
	bool continue_seeding;
	int maximum_number_of_seedings = 10;
	int seeding;
	bool continue_iterate;

	max_v[R] = -512.0;   max_v[G] = -512.0;   max_v[B] = -512.0; 
	min_v[R] =  512.0;   min_v[G] =  512.0;   min_v[B] =  512.0;

	// resolve trainingdata
	for (y = 0; y < BLOCKHEIGHT; ++y) 
	{
		for (x = 0; x < BLOCKWIDTH; ++x) 
		{
			red = img[3*((starty+y)*width+startx+x)+R];
			green = img[3*((starty+y)*width+startx+x)+G];
			blue = img[3*((starty+y)*width+startx+x)+B];

			original_colors[x][y][R] = red;
			original_colors[x][y][G] = green;
			original_colors[x][y][B] = blue;

			// find max
			if (original_colors[x][y][R] > max_v[R]) max_v[R] = original_colors[x][y][R];
			if (original_colors[x][y][G] > max_v[G]) max_v[G] = original_colors[x][y][G];
			if (original_colors[x][y][B] > max_v[B]) max_v[B] = original_colors[x][y][B];
			// find min
			if (original_colors[x][y][R] < min_v[R]) min_v[R] = original_colors[x][y][R];
			if (original_colors[x][y][G] < min_v[G]) min_v[G] = original_colors[x][y][G];
			if (original_colors[x][y][B] < min_v[B]) min_v[B] = original_colors[x][y][B];
		}
	}

	D = 512*512*3*16.0; 
	bestD = 512*512*3*16.0; 

	continue_seeding = true;

	// loop seeds
	for (seeding = 0; (seeding < maximum_number_of_seedings) && continue_seeding; seeding++)
	{
		// hopefully we will not need more seedings:
		continue_seeding = false;

		// calculate seeds
		for (uint8 s = 0; s < 2; ++s) 
		{
			for (uint8 c = 0; c < 3; ++c) 
			{ 
				current_colors[s][c] = double((double(rand())/RAND_MAX)*(max_v[c]-min_v[c])) + min_v[c];
			}
		}
		
		// divide into two quantization sets and calculate distortion

		continue_iterate = true;
		for(i = 0; (i < number_of_iterations) && continue_iterate; i++)
		{
			oldD = D;
			D = 0;
			int n = 0;
			for (y = 0; y < BLOCKHEIGHT; ++y) 
			{
				for (int x = 0; x < BLOCKWIDTH; ++x) 
				{
					error_a = SQUARE(original_colors[x][y][R] - JAS_ROUND(current_colors[0][R])) + 
							  SQUARE(original_colors[x][y][G] - JAS_ROUND(current_colors[0][G])) +
							  SQUARE(original_colors[x][y][B] - JAS_ROUND(current_colors[0][B]));
					error_b = SQUARE(original_colors[x][y][R] - JAS_ROUND(current_colors[1][R])) + 
							  SQUARE(original_colors[x][y][G] - JAS_ROUND(current_colors[1][G])) +
							  SQUARE(original_colors[x][y][B] - JAS_ROUND(current_colors[1][B]));
					if (error_a < error_b) 
					{
						block_mask[x][y] = 0;
						D += error_a; 
						++n;
					} 
					else 
					{
						block_mask[x][y] = 1;
						D += error_b;
					}
				}
			}

			// compare with old distortion
			if (D == 0) 
			{
				// Perfect score -- we dont need to go further iterations.
				continue_iterate = false;
				continue_seeding = false;
			}
			if (D == oldD)
			{
				// Same score as last round -- no need to go for further iterations.
				continue_iterate = false;
				continue_seeding = true;
			}
			if (D < bestD) 
			{
				bestD = D;
				for(uint8 s = 0; s < 2; ++s) 
				{
					for(uint8 c = 0; c < 3; ++c) 
					{
						best_colors[s][c] = current_colors[s][c];
					}
				}
			}
			if (n == 0 || n == BLOCKWIDTH*BLOCKHEIGHT) 
			{
				// All colors end up in the same voroni region. We need to reseed.
				continue_iterate = false;
				continue_seeding = true;
			}
			else
			{
				// Calculate new reconstruction points using the centroids

				// Find new construction values from average
				t_color[0][R] = 0;
				t_color[0][G] = 0;
				t_color[0][B] = 0;
				t_color[1][R] = 0;
				t_color[1][G] = 0;
				t_color[1][B] = 0;

				for (y = 0; y < BLOCKHEIGHT; ++y) 
				{
					for (int x = 0; x < BLOCKWIDTH; ++x) 
					{
						// use dummy value for q-parameter
						t_color[block_mask[x][y]][R] += original_colors[x][y][R];
						t_color[block_mask[x][y]][G] += original_colors[x][y][G];
						t_color[block_mask[x][y]][B] += original_colors[x][y][B];
					}
				}
				current_colors[0][R] = t_color[0][R] / n;
				current_colors[1][R] = t_color[1][R] / (BLOCKWIDTH*BLOCKHEIGHT - n);
				current_colors[0][G] = t_color[0][G] / n;
				current_colors[1][G] = t_color[1][G] / (BLOCKWIDTH*BLOCKHEIGHT - n);
				current_colors[0][B] = t_color[0][B] / n;
				current_colors[1][B] = t_color[1][B] / (BLOCKWIDTH*BLOCKHEIGHT - n);
			}
		}
	}

	// Set the best colors as the final block colors
	for(int s = 0; s < 2; ++s) 
	{
		for(uint8 c = 0; c < 3; ++c) 
		{
			current_colors[s][c] = best_colors[s][c];
		}
	}		

	for(x=0;x<2;x++)
		for(y=0;y<3;y++)
			LBG_colors[x][y] = JAS_ROUND(current_colors[x][y]);
}

// Calculation of the two block colors using the LBG-algorithm
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void computeColorLBGfast(uint8 *img,int width,int startx,int starty, uint8 (LBG_colors)[2][3]) 
{
	uint8 block_mask[4][4];

	// reset rand so that we get predictable output per block
	srand(10000);
	//LBG-algorithm
	double D = 0, oldD, bestD = MAXIMUM_ERROR, eps = 0.0000000001;
	double error_a, error_b;
	int number_of_iterations = 10;
	double t_color[2][3];
	uint8 original_colors[4][4][3];
	double current_colors[2][3];
	double best_colors[2][3];
	double max_v[3];
	double min_v[3];
	int x,y,i;
	bool continue_seeding;
	int maximum_number_of_seedings = 10;
	int seeding;
	bool continue_iterate;

	max_v[R] = -512.0;   max_v[G] = -512.0;   max_v[B] = -512.0; 
	min_v[R] =  512.0;   min_v[G] =  512.0;   min_v[B] =  512.0;

	// resolve trainingdata
	for (y = 0; y < BLOCKHEIGHT; ++y) 
	{
		for (x = 0; x < BLOCKWIDTH; ++x) 
		{
			original_colors[x][y][R] = img[3*((starty+y)*width+startx+x)+R];
			original_colors[x][y][G] = img[3*((starty+y)*width+startx+x)+G];
			original_colors[x][y][B] = img[3*((starty+y)*width+startx+x)+B];
		
			// find max
			if (original_colors[x][y][R] > max_v[R]) max_v[R] = original_colors[x][y][R];
			if (original_colors[x][y][G] > max_v[G]) max_v[G] = original_colors[x][y][G];
			if (original_colors[x][y][B] > max_v[B]) max_v[B] = original_colors[x][y][B];
			// find min
			if (original_colors[x][y][R] < min_v[R]) min_v[R] = original_colors[x][y][R];
			if (original_colors[x][y][G] < min_v[G]) min_v[G] = original_colors[x][y][G];
			if (original_colors[x][y][B] < min_v[B]) min_v[B] = original_colors[x][y][B];
		}
	}

	D = 512*512*3*16.0; 
	bestD = 512*512*3*16.0; 

	continue_seeding = true;

	// loop seeds
	for (seeding = 0; (seeding < maximum_number_of_seedings) && continue_seeding; seeding++)
	{
		// hopefully we will not need more seedings:
		continue_seeding = false;

		// calculate seeds
		for (uint8 s = 0; s < 2; ++s) 
		{
			for (uint8 c = 0; c < 3; ++c) 
			{ 
				current_colors[s][c] = double((double(rand())/RAND_MAX)*(max_v[c]-min_v[c])) + min_v[c];
			}
		}
		
		// divide into two quantization sets and calculate distortion
		continue_iterate = true;
		for(i = 0; (i < number_of_iterations) && continue_iterate; i++)
		{
			oldD = D;
			D = 0;
			int n = 0;
			for (y = 0; y < BLOCKHEIGHT; ++y) 
			{
				for (int x = 0; x < BLOCKWIDTH; ++x) 
				{
					error_a = SQUARE(original_colors[x][y][R] - JAS_ROUND(current_colors[0][R])) + 
							  SQUARE(original_colors[x][y][G] - JAS_ROUND(current_colors[0][G])) +
							  SQUARE(original_colors[x][y][B] - JAS_ROUND(current_colors[0][B]));
					error_b = SQUARE(original_colors[x][y][R] - JAS_ROUND(current_colors[1][R])) + 
							  SQUARE(original_colors[x][y][G] - JAS_ROUND(current_colors[1][G])) +
							  SQUARE(original_colors[x][y][B] - JAS_ROUND(current_colors[1][B]));
					if (error_a < error_b) 
					{
						block_mask[x][y] = 0;
						D += error_a; 
						++n;
					} 
					else 
					{
						block_mask[x][y] = 1;
						D += error_b;
					}
				}
			}

			// compare with old distortion
			if (D == 0) 
			{
				// Perfect score -- we dont need to go further iterations.
				continue_iterate = false;
				continue_seeding = false;
			}
			if (D == oldD)
			{
				// Same score as last round -- no need to go for further iterations.
				continue_iterate = false;
				continue_seeding = false;
			}
			if (D < bestD) 
			{
				bestD = D;
				for(uint8 s = 0; s < 2; ++s) 
				{
					for(uint8 c = 0; c < 3; ++c) 
					{
						best_colors[s][c] = current_colors[s][c];
					}
				}
			}
			if (n == 0 || n == BLOCKWIDTH*BLOCKHEIGHT) 
			{
				// All colors end up in the same voroni region. We need to reseed.
				continue_iterate = false;
				continue_seeding = true;
			}
			else
			{
				// Calculate new reconstruction points using the centroids

				// Find new construction values from average
				t_color[0][R] = 0;
				t_color[0][G] = 0;
				t_color[0][B] = 0;
				t_color[1][R] = 0;
				t_color[1][G] = 0;
				t_color[1][B] = 0;

				for (y = 0; y < BLOCKHEIGHT; ++y) 
				{
					for (int x = 0; x < BLOCKWIDTH; ++x) 
					{
						// use dummy value for q-parameter
						t_color[block_mask[x][y]][R] += original_colors[x][y][R];
						t_color[block_mask[x][y]][G] += original_colors[x][y][G];
						t_color[block_mask[x][y]][B] += original_colors[x][y][B];
					}
				}
				current_colors[0][R] = t_color[0][R] / n;
				current_colors[1][R] = t_color[1][R] / (BLOCKWIDTH*BLOCKHEIGHT - n);
				current_colors[0][G] = t_color[0][G] / n;
				current_colors[1][G] = t_color[1][G] / (BLOCKWIDTH*BLOCKHEIGHT - n);
				current_colors[0][B] = t_color[0][B] / n;
				current_colors[1][B] = t_color[1][B] / (BLOCKWIDTH*BLOCKHEIGHT - n);
			}
		}
	}

	// Set the best colors as the final block colors
	for(int s = 0; s < 2; ++s) 
	{
		for(uint8 c = 0; c < 3; ++c) 
		{
			current_colors[s][c] = best_colors[s][c];
		}
	}		

	for(x=0;x<2;x++)
		for(y=0;y<3;y++)
			LBG_colors[x][y] = JAS_ROUND(current_colors[x][y]);
}

// Each color component is compressed to fit in its specified number of bits
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressColor(int R_B, int G_B, int B_B, uint8 (current_color)[2][3], uint8 (quantized_color)[2][3]) 
{
	//
	//	The color is calculated as:
	//
	//  c = (c + (2^(8-b))/2) / (255 / (2^b - 1)) where b is the number of bits
	//                                            to code color c with
	//  For instance, if b = 3:
	//
	//  c = (c + 16) / (255 / 7) = 7 * (c + 16) / 255
	//

	quantized_color[0][R] = CLAMP(0,(BINPOW(R_B)-1) * (current_color[0][R] + BINPOW(8-R_B-1)) / 255,255);
	quantized_color[0][G] = CLAMP(0,(BINPOW(G_B)-1) * (current_color[0][G] + BINPOW(8-G_B-1)) / 255,255);
	quantized_color[0][B] = CLAMP(0,(BINPOW(B_B)-1) * (current_color[0][B] + BINPOW(8-B_B-1)) / 255,255);

	quantized_color[1][R] = CLAMP(0,(BINPOW(R_B)-1) * (current_color[1][R] + BINPOW(8-R_B-1)) / 255,255);
	quantized_color[1][G] = CLAMP(0,(BINPOW(G_B)-1) * (current_color[1][G] + BINPOW(8-G_B-1)) / 255,255);
	quantized_color[1][B] = CLAMP(0,(BINPOW(B_B)-1) * (current_color[1][B] + BINPOW(8-B_B-1)) / 255,255);
}

// Swapping two RGB-colors
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void swapColors(uint8 (colors)[2][3]) 
{
	uint8 temp = colors[0][R];
	colors[0][R] = colors[1][R];
	colors[1][R] = temp;

	temp = colors[0][G];
	colors[0][G] = colors[1][G];
	colors[1][G] = temp;

	temp = colors[0][B];
	colors[0][B] = colors[1][B];
	colors[1][B] = temp;
}


// Calculate the paint colors from the block colors 
// using a distance d and one of the H- or T-patterns.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.

// Calculate the error for the block at position (startx,starty)
// The parameters needed for reconstruction are calculated as well
// 
// Please note that the function can change the order between the two colors in colorsRGB444
//
// In the 59T bit mode, we only have pattern T.
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateError59Tperceptual1000(uint8* srcimg, int width, int startx, int starty, uint8 (colorsRGB444)[2][3], uint8 &distance, unsigned int &pixel_indices) 
{

	unsigned int block_error = 0, 
		   best_block_error = MAXERR1000,
		   pixel_error, 
		   best_pixel_error;
	int diff[3];
	uint8 best_sw;
	unsigned int pixel_colors;
	uint8 colors[2][3];
	uint8 possible_colors[4][3];

	// First use the colors as they are, then swap them
	for (uint8 sw = 0; sw <2; ++sw) 
	{ 
		if (sw == 1) 
		{
			swapColors(colorsRGB444);
		}
		decompressColor(R_BITS59T, G_BITS59T, B_BITS59T, colorsRGB444, colors);

		// Test all distances
		for (uint8 d = 0; d < BINPOW(TABLE_BITS_59T); ++d) 
		{
			calculatePaintColors59T(d,PATTERN_T, colors, possible_colors);
			
			block_error = 0;	
			pixel_colors = 0;

			// Loop block
			for (size_t y = 0; y < BLOCKHEIGHT; ++y) 
			{
				for (size_t x = 0; x < BLOCKWIDTH; ++x) 
				{
					best_pixel_error = MAXERR1000;
					pixel_colors <<=2; // Make room for next value

					// Loop possible block colors
					for (uint8 c = 0; c < 4; ++c) 
					{
					
						diff[R] = srcimg[3*((starty+y)*width+startx+x)+R] - CLAMP(0,possible_colors[c][R],255);
						diff[G] = srcimg[3*((starty+y)*width+startx+x)+G] - CLAMP(0,possible_colors[c][G],255);
						diff[B] = srcimg[3*((starty+y)*width+startx+x)+B] - CLAMP(0,possible_colors[c][B],255);

						pixel_error =	PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(diff[R]) +
										PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*SQUARE(diff[G]) +
										PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*SQUARE(diff[B]);

						// Choose best error
						if (pixel_error < best_pixel_error) 
						{
							best_pixel_error = pixel_error;
							pixel_colors ^= (pixel_colors & 3); // Reset the two first bits
							pixel_colors |= c;
						} 
					}
					block_error += best_pixel_error;
				}
			}
			if (block_error < best_block_error) 
			{
				best_block_error = block_error;
				distance = d;
				pixel_indices = pixel_colors;
				best_sw = sw;
			}
		}
		
		if (sw == 1 && best_sw == 0) 
		{
			swapColors(colorsRGB444);
		}
		decompressColor(R_BITS59T, G_BITS59T, B_BITS59T, colorsRGB444, colors);
	}
	return best_block_error;
}

// Calculate the error for the block at position (startx,starty)
// The parameters needed for reconstruction is calculated as well
// 
// Please note that the function can change the order between the two colors in colorsRGB444
//
// In the 59T bit mode, we only have pattern T.
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double calculateError59T(uint8* srcimg, int width, int startx, int starty, uint8 (colorsRGB444)[2][3], uint8 &distance, unsigned int &pixel_indices) 
{
	double block_error = 0, 
		     best_block_error = MAXIMUM_ERROR, 
				 pixel_error, 
				 best_pixel_error;
	int diff[3];
	uint8 best_sw;
	unsigned int pixel_colors;
	uint8 colors[2][3];
	uint8 possible_colors[4][3];

	// First use the colors as they are, then swap them
	for (uint8 sw = 0; sw <2; ++sw) 
	{ 
		if (sw == 1) 
		{
			swapColors(colorsRGB444);
		}
		decompressColor(R_BITS59T, G_BITS59T, B_BITS59T, colorsRGB444, colors);

		// Test all distances
		for (uint8 d = 0; d < BINPOW(TABLE_BITS_59T); ++d) 
		{
			calculatePaintColors59T(d,PATTERN_T, colors, possible_colors);
			
			block_error = 0;	
			pixel_colors = 0;

			// Loop block
			for (size_t y = 0; y < BLOCKHEIGHT; ++y) 
			{
				for (size_t x = 0; x < BLOCKWIDTH; ++x) 
				{
					best_pixel_error = MAXIMUM_ERROR;
					pixel_colors <<=2; // Make room for next value

					// Loop possible block colors
					for (uint8 c = 0; c < 4; ++c) 
					{
					
						diff[R] = srcimg[3*((starty+y)*width+startx+x)+R] - CLAMP(0,possible_colors[c][R],255);
						diff[G] = srcimg[3*((starty+y)*width+startx+x)+G] - CLAMP(0,possible_colors[c][G],255);
						diff[B] = srcimg[3*((starty+y)*width+startx+x)+B] - CLAMP(0,possible_colors[c][B],255);

						pixel_error =	weight[R]*SQUARE(diff[R]) +
										weight[G]*SQUARE(diff[G]) +
										weight[B]*SQUARE(diff[B]);

						// Choose best error
						if (pixel_error < best_pixel_error) 
						{
							best_pixel_error = pixel_error;
							pixel_colors ^= (pixel_colors & 3); // Reset the two first bits
							pixel_colors |= c;
						} 
					}
					block_error += best_pixel_error;
				}
			}
			if (block_error < best_block_error) 
			{
				best_block_error = block_error;
				distance = d;
				pixel_indices = pixel_colors;
				best_sw = sw;
			}
		}
		
		if (sw == 1 && best_sw == 0) 
		{
			swapColors(colorsRGB444);
		}
		decompressColor(R_BITS59T, G_BITS59T, B_BITS59T, colorsRGB444, colors);
	}
	return best_block_error;
}

// Calculate the error for the block at position (startx,starty)
// The parameters needed for reconstruction is calculated as well
//
// In the 59T bit mode, we only have pattern T.
// 
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateError59TnoSwapPerceptual1000(uint8* srcimg, int width, int startx, int starty, uint8 (colorsRGB444)[2][3], uint8 &distance, unsigned int &pixel_indices) 
{

	unsigned int block_error = 0, 
		   best_block_error = MAXERR1000,
		   pixel_error, 
		   best_pixel_error;
	int diff[3];
	unsigned int pixel_colors;
	uint8 colors[2][3];
	uint8 possible_colors[4][3];
	int thebestintheworld;

	// First use the colors as they are, then swap them
		decompressColor(R_BITS59T, G_BITS59T, B_BITS59T, colorsRGB444, colors);

		// Test all distances
		for (uint8 d = 0; d < BINPOW(TABLE_BITS_59T); ++d) 
		{
			calculatePaintColors59T(d,PATTERN_T, colors, possible_colors);
			
			block_error = 0;	
			pixel_colors = 0;

			// Loop block
			for (size_t y = 0; y < BLOCKHEIGHT; ++y) 
			{
				for (size_t x = 0; x < BLOCKWIDTH; ++x) 
				{
					best_pixel_error = MAXERR1000;
					pixel_colors <<=2; // Make room for next value

					// Loop possible block colors
					for (uint8 c = 0; c < 4; ++c) 
					{
					
						diff[R] = srcimg[3*((starty+y)*width+startx+x)+R] - CLAMP(0,possible_colors[c][R],255);
						diff[G] = srcimg[3*((starty+y)*width+startx+x)+G] - CLAMP(0,possible_colors[c][G],255);
						diff[B] = srcimg[3*((starty+y)*width+startx+x)+B] - CLAMP(0,possible_colors[c][B],255);

						pixel_error =	PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(diff[R]) +
										PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*SQUARE(diff[G]) +
										PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*SQUARE(diff[B]);

						// Choose best error
						if (pixel_error < best_pixel_error) 
						{
							best_pixel_error = pixel_error;
							pixel_colors ^= (pixel_colors & 3); // Reset the two first bits
							pixel_colors |= c;
							thebestintheworld = c;
						} 
					}
					block_error += best_pixel_error;
				}
			}
			if (block_error < best_block_error) 
			{
				best_block_error = block_error;
				distance = d;
				pixel_indices = pixel_colors;
			}
		}
		
	decompressColor(R_BITS59T, G_BITS59T, B_BITS59T, colorsRGB444, colors);
	return best_block_error;
}

// Calculate the error for the block at position (startx,starty)
// The parameters needed for reconstruction is calculated as well
//
// In the 59T bit mode, we only have pattern T.
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double calculateError59TnoSwap(uint8* srcimg, int width, int startx, int starty, uint8 (colorsRGB444)[2][3], uint8 &distance, unsigned int &pixel_indices) 
{
	double block_error = 0, 
		     best_block_error = MAXIMUM_ERROR, 
				 pixel_error, 
				 best_pixel_error;
	int diff[3];
	unsigned int pixel_colors;
	uint8 colors[2][3];
	uint8 possible_colors[4][3];
	int thebestintheworld;

	// First use the colors as they are, then swap them
	decompressColor(R_BITS59T, G_BITS59T, B_BITS59T, colorsRGB444, colors);

	// Test all distances
	for (uint8 d = 0; d < BINPOW(TABLE_BITS_59T); ++d) 
	{
		calculatePaintColors59T(d,PATTERN_T, colors, possible_colors);
			
		block_error = 0;	
		pixel_colors = 0;

		// Loop block
		for (size_t y = 0; y < BLOCKHEIGHT; ++y) 
		{
			for (size_t x = 0; x < BLOCKWIDTH; ++x) 
			{
				best_pixel_error = MAXIMUM_ERROR;
				pixel_colors <<=2; // Make room for next value

				// Loop possible block colors
				for (uint8 c = 0; c < 4; ++c) 
				{
					diff[R] = srcimg[3*((starty+y)*width+startx+x)+R] - CLAMP(0,possible_colors[c][R],255);
					diff[G] = srcimg[3*((starty+y)*width+startx+x)+G] - CLAMP(0,possible_colors[c][G],255);
					diff[B] = srcimg[3*((starty+y)*width+startx+x)+B] - CLAMP(0,possible_colors[c][B],255);

					pixel_error =	weight[R]*SQUARE(diff[R]) +
						            weight[G]*SQUARE(diff[G]) +
												weight[B]*SQUARE(diff[B]);

					// Choose best error
					if (pixel_error < best_pixel_error) 
					{
						best_pixel_error = pixel_error;
						pixel_colors ^= (pixel_colors & 3); // Reset the two first bits
						pixel_colors |= c;
						thebestintheworld = c;
					} 
				}
				block_error += best_pixel_error;
			}
		}
		if (block_error < best_block_error) 
		{
			best_block_error = block_error;
			distance = d;
			pixel_indices = pixel_colors;
		}
	}
		
	decompressColor(R_BITS59T, G_BITS59T, B_BITS59T, colorsRGB444, colors);
	return best_block_error;
}

// Put the compress params into the compression block 
//
//
//|63 62 61 60 59|58 57 56 55|54 53 52 51|50 49 48 47|46 45 44 43|42 41 40 39|38 37 36 35|34 33 32|
//|----empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|--dist--|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void packBlock59T(uint8 (colors)[2][3], uint8 d, unsigned int pixel_indices, unsigned int &compressed1, unsigned int &compressed2) 
{ 
	
	compressed1 = 0;

	PUTBITSHIGH( compressed1, colors[0][R], 4, 58);
 	PUTBITSHIGH( compressed1, colors[0][G], 4, 54);
 	PUTBITSHIGH( compressed1, colors[0][B], 4, 50);
 	PUTBITSHIGH( compressed1, colors[1][R], 4, 46);
 	PUTBITSHIGH( compressed1, colors[1][G], 4, 42);
 	PUTBITSHIGH( compressed1, colors[1][B], 4, 38);	
	PUTBITSHIGH( compressed1, d, TABLE_BITS_59T, 34);
	pixel_indices=indexConversion(pixel_indices);
	compressed2 = 0;
	PUTBITS( compressed2, pixel_indices, 32, 31);
}

// Copy colors from source to dest
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void copyColors(uint8 (source)[2][3], uint8 (dest)[2][3])
{
	int x,y;

	for (x=0; x<2; x++)
		for (y=0; y<3; y++)
			dest[x][y] = source[x][y];
}

// The below code should compress the block to 59 bits. 
//
//|63 62 61 60 59|58 57 56 55|54 53 52 51|50 49 48 47|46 45 44 43|42 41 40 39|38 37 36 35|34 33 32|
//|----empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|--dist--|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int compressBlockTHUMB59TFastestOnlyColorPerceptual1000(uint8 *img,int width,int height,int startx,int starty, int (best_colorsRGB444_packed)[2])
{
	unsigned int best_error = MAXERR1000;
	unsigned int best_pixel_indices;
	uint8 best_distance;

	unsigned int error_no_i;
	uint8 colorsRGB444_no_i[2][3];
	unsigned int pixel_indices_no_i;
	uint8 distance_no_i;

	uint8 colors[2][3];

	// Calculate average color using the LBG-algorithm
	computeColorLBGHalfIntensityFast(img,width,startx,starty, colors);
	compressColor(R_BITS59T, G_BITS59T, B_BITS59T, colors, colorsRGB444_no_i);

	// Determine the parameters for the lowest error
	error_no_i = calculateError59Tperceptual1000(img, width, startx, starty, colorsRGB444_no_i, distance_no_i, pixel_indices_no_i);			

	best_error = error_no_i;
	best_distance = distance_no_i;
	best_pixel_indices = pixel_indices_no_i;

	best_colorsRGB444_packed[0] = (colorsRGB444_no_i[0][0] << 8) + (colorsRGB444_no_i[0][1] << 4) + (colorsRGB444_no_i[0][2] << 0);
	best_colorsRGB444_packed[1] = (colorsRGB444_no_i[1][0] << 8) + (colorsRGB444_no_i[1][1] << 4) + (colorsRGB444_no_i[1][2] << 0);

	return best_error;
}


// The below code should compress the block to 59 bits. 
// This is supposed to match the first of the three modes in TWOTIMER.
//
//|63 62 61 60 59|58 57 56 55|54 53 52 51|50 49 48 47|46 45 44 43|42 41 40 39|38 37 36 35|34 33 32|
//|----empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|--dist--|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double compressBlockTHUMB59TFastestOnlyColor(uint8 *img,int width,int height,int startx,int starty, int (best_colorsRGB444_packed)[2])
{
	double best_error = MAXIMUM_ERROR;
	unsigned int best_pixel_indices;
	uint8 best_distance;

	double error_no_i;
	uint8 colorsRGB444_no_i[2][3];
	unsigned int pixel_indices_no_i;
	uint8 distance_no_i;

	uint8 colors[2][3];

	// Calculate average color using the LBG-algorithm
	computeColorLBGHalfIntensityFast(img,width,startx,starty, colors);
	compressColor(R_BITS59T, G_BITS59T, B_BITS59T, colors, colorsRGB444_no_i);

	// Determine the parameters for the lowest error
	error_no_i = calculateError59T(img, width, startx, starty, colorsRGB444_no_i, distance_no_i, pixel_indices_no_i);			

	best_error = error_no_i;
	best_distance = distance_no_i;
	best_pixel_indices = pixel_indices_no_i;

	best_colorsRGB444_packed[0] = (colorsRGB444_no_i[0][0] << 8) + (colorsRGB444_no_i[0][1] << 4) + (colorsRGB444_no_i[0][2] << 0);
	best_colorsRGB444_packed[1] = (colorsRGB444_no_i[1][0] << 8) + (colorsRGB444_no_i[1][1] << 4) + (colorsRGB444_no_i[1][2] << 0);

	return best_error;
}

// The below code should compress the block to 59 bits. 
// This is supposed to match the first of the three modes in TWOTIMER.
//
//|63 62 61 60 59|58 57 56 55|54 53 52 51|50 49 48 47|46 45 44 43|42 41 40 39|38 37 36 35|34 33 32|
//|----empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|--dist--|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double compressBlockTHUMB59TFastestPerceptual1000(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2) 
{
	double best_error = MAXIMUM_ERROR;
	uint8 best_colorsRGB444[2][3];
	unsigned int best_pixel_indices;
	uint8 best_distance;

	double error_no_i;
	uint8 colorsRGB444_no_i[2][3];
	unsigned int pixel_indices_no_i;
	uint8 distance_no_i;

	uint8 colors[2][3];

	// Calculate average color using the LBG-algorithm
	computeColorLBGHalfIntensityFast(img,width,startx,starty, colors);
	compressColor(R_BITS59T, G_BITS59T, B_BITS59T, colors, colorsRGB444_no_i);

	// Determine the parameters for the lowest error
	error_no_i = calculateError59Tperceptual1000(img, width, startx, starty, colorsRGB444_no_i, distance_no_i, pixel_indices_no_i);			

	best_error = error_no_i;
	best_distance = distance_no_i;
	best_pixel_indices = pixel_indices_no_i;
	copyColors(colorsRGB444_no_i, best_colorsRGB444);

	// Put the compress params into the compression block 
	packBlock59T(best_colorsRGB444, best_distance, best_pixel_indices, compressed1, compressed2);

	return best_error;
}

// The below code should compress the block to 59 bits. 
// This is supposed to match the first of the three modes in TWOTIMER.
//
//|63 62 61 60 59|58 57 56 55|54 53 52 51|50 49 48 47|46 45 44 43|42 41 40 39|38 37 36 35|34 33 32|
//|----empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|--dist--|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double compressBlockTHUMB59TFastest(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2) 
{
	double best_error = MAXIMUM_ERROR;
	uint8 best_colorsRGB444[2][3];
	unsigned int best_pixel_indices;
	uint8 best_distance;

	double error_no_i;
	uint8 colorsRGB444_no_i[2][3];
	unsigned int pixel_indices_no_i;
	uint8 distance_no_i;

	uint8 colors[2][3];

	// Calculate average color using the LBG-algorithm
	computeColorLBGHalfIntensityFast(img,width,startx,starty, colors);
	compressColor(R_BITS59T, G_BITS59T, B_BITS59T, colors, colorsRGB444_no_i);

	// Determine the parameters for the lowest error
	error_no_i = calculateError59T(img, width, startx, starty, colorsRGB444_no_i, distance_no_i, pixel_indices_no_i);			

	best_error = error_no_i;
	best_distance = distance_no_i;
	best_pixel_indices = pixel_indices_no_i;
	copyColors(colorsRGB444_no_i, best_colorsRGB444);

	// Put the compress params into the compression block 
	packBlock59T(best_colorsRGB444, best_distance, best_pixel_indices, compressed1, compressed2);

	return best_error;
}

// The below code should compress the block to 59 bits. 
// This is supposed to match the first of the three modes in TWOTIMER.
//
//|63 62 61 60 59|58 57 56 55|54 53 52 51|50 49 48 47|46 45 44 43|42 41 40 39|38 37 36 35|34 33 32|
//|----empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|--dist--|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double compressBlockTHUMB59TFast(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2) 
{
	double best_error = MAXIMUM_ERROR;
	uint8 best_colorsRGB444[2][3];
	unsigned int best_pixel_indices;
	uint8 best_distance;

	double error_no_i;
	uint8 colorsRGB444_no_i[2][3];
	unsigned int pixel_indices_no_i;
	uint8 distance_no_i;

	double error_half_i;
	uint8 colorsRGB444_half_i[2][3];
	unsigned int pixel_indices_half_i;
	uint8 distance_half_i;
	
	double error;
	uint8 colorsRGB444[2][3];
	unsigned int pixel_indices;
	uint8 distance;

	uint8 colors[2][3];

	// Calculate average color using the LBG-algorithm
	computeColorLBGNotIntensityFast(img,width,startx,starty, colors);
	compressColor(R_BITS59T, G_BITS59T, B_BITS59T, colors, colorsRGB444_no_i);
	// Determine the parameters for the lowest error
	error_no_i = calculateError59T(img, width, startx, starty, colorsRGB444_no_i, distance_no_i, pixel_indices_no_i);			

	// Calculate average color using the LBG-algorithm
	computeColorLBGHalfIntensityFast(img,width,startx,starty, colors);
	compressColor(R_BITS59T, G_BITS59T, B_BITS59T, colors, colorsRGB444_half_i);
	// Determine the parameters for the lowest error
	error_half_i = calculateError59T(img, width, startx, starty, colorsRGB444_half_i, distance_half_i, pixel_indices_half_i);			

	// Calculate average color using the LBG-algorithm
	computeColorLBGfast(img,width,startx,starty, colors);
	compressColor(R_BITS59T, G_BITS59T, B_BITS59T, colors, colorsRGB444);
	// Determine the parameters for the lowest error
	error = calculateError59T(img, width, startx, starty, colorsRGB444, distance, pixel_indices);			
	
	best_error = error_no_i;
	best_distance = distance_no_i;
	best_pixel_indices = pixel_indices_no_i;
	copyColors(colorsRGB444_no_i, best_colorsRGB444);

	if(error_half_i < best_error)
	{
		best_error = error_half_i;
		best_distance = distance_half_i;
		best_pixel_indices = pixel_indices_half_i;
		copyColors (colorsRGB444_half_i, best_colorsRGB444);
	}
	if(error < best_error)
	{
		best_error = error;
		best_distance = distance;
		best_pixel_indices = pixel_indices;
		copyColors (colorsRGB444, best_colorsRGB444);
	}

	// Put the compress params into the compression block 
	packBlock59T(best_colorsRGB444, best_distance, best_pixel_indices, compressed1, compressed2);

	return best_error;
}

// Calculate the error for the block at position (startx,starty)
// The parameters needed for reconstruction is calculated as well
// 
// In the 58H bit mode, we only have pattern H.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateErrorAndCompress58Hperceptual1000(uint8* srcimg, int width, int startx, int starty, uint8 (colorsRGB444)[2][3], uint8 &distance, unsigned int &pixel_indices) 
{
	unsigned int block_error = 0, 
		           best_block_error = MAXERR1000, 
							 pixel_error, 
							 best_pixel_error;
	int diff[3];
	unsigned int pixel_colors;
	uint8 possible_colors[4][3];
	uint8 colors[2][3];

	decompressColor(R_BITS58H, G_BITS58H, B_BITS58H, colorsRGB444, colors);

	// Test all distances
	for (uint8 d = 0; d < BINPOW(TABLE_BITS_58H); ++d) 
	{
		calculatePaintColors58H(d, PATTERN_H, colors, possible_colors);

		block_error = 0;	
		pixel_colors = 0;

		// Loop block
		for (size_t y = 0; y < BLOCKHEIGHT; ++y) 
		{
			for (size_t x = 0; x < BLOCKWIDTH; ++x) 
			{
				best_pixel_error = MAXERR1000;
				pixel_colors <<=2; // Make room for next value

				// Loop possible block colors
				for (uint8 c = 0; c < 4; ++c) 
				{
					diff[R] = srcimg[3*((starty+y)*width+startx+x)+R] - CLAMP(0,possible_colors[c][R],255);
					diff[G] = srcimg[3*((starty+y)*width+startx+x)+G] - CLAMP(0,possible_colors[c][G],255);
					diff[B] = srcimg[3*((starty+y)*width+startx+x)+B] - CLAMP(0,possible_colors[c][B],255);

					pixel_error =	PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(diff[R]) +
									PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*SQUARE(diff[G]) +
									PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*SQUARE(diff[B]);

					// Choose best error
					if (pixel_error < best_pixel_error) 
					{
						best_pixel_error = pixel_error;
						pixel_colors ^= (pixel_colors & 3); // Reset the two first bits
						pixel_colors |= c;
					} 
				}
				block_error += best_pixel_error;
			}
		}
		
		if (block_error < best_block_error) 
		{
			best_block_error = block_error;
			distance = d;
			pixel_indices = pixel_colors;
		}
	}
	return best_block_error;
}

// The H-mode but with punchthrough alpha
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double calculateErrorAndCompress58HAlpha(uint8* srcimg, uint8* alphaimg,int width, int startx, int starty, uint8 (colorsRGB444)[2][3], uint8 &distance, unsigned int &pixel_indices) 
{
	double block_error = 0, 
		   best_block_error = MAXIMUM_ERROR, 
		   pixel_error, 
		   best_pixel_error;
	int diff[3];
	unsigned int pixel_colors;
	uint8 possible_colors[4][3];
	uint8 colors[2][3];
	int alphaindex;
	int colorsRGB444_packed[2];
	colorsRGB444_packed[0] = (colorsRGB444[0][R] << 8) + (colorsRGB444[0][G] << 4) + colorsRGB444[0][B];
	colorsRGB444_packed[1] = (colorsRGB444[1][R] << 8) + (colorsRGB444[1][G] << 4) + colorsRGB444[1][B];
	
	decompressColor(R_BITS58H, G_BITS58H, B_BITS58H, colorsRGB444, colors);
	
	// Test all distances
	for (uint8 d = 0; d < BINPOW(TABLE_BITS_58H); ++d) 
	{
		alphaindex=2;
		if( (colorsRGB444_packed[0] >= colorsRGB444_packed[1]) ^ ((d & 1)==1) )
		{
			//we're going to have to swap the colors to be able to choose this distance.. that means
			//that the indices will be swapped as well, so C1 will be the one with alpha instead of C3..
			alphaindex=0;
		}

		calculatePaintColors58H(d, PATTERN_H, colors, possible_colors);

		block_error = 0;	
		pixel_colors = 0;

		// Loop block
		for (size_t y = 0; y < BLOCKHEIGHT; ++y) 
		{
			for (size_t x = 0; x < BLOCKWIDTH; ++x) 
			{
				int alpha=0;
				if(alphaimg[((starty+y)*width+startx+x)]>0)
					alpha=1;
				if(alphaimg[((starty+y)*width+startx+x)]>0&&alphaimg[((starty+y)*width+startx+x)]<255)
					printf("INVALID ALPHA DATA!!\n");
				best_pixel_error = MAXIMUM_ERROR;
				pixel_colors <<=2; // Make room for next value

				// Loop possible block colors
				for (uint8 c = 0; c < 4; ++c) 
				{
					if(c==alphaindex&&alpha) 
					{
						pixel_error=0;
					}
					else if(c==alphaindex||alpha) 
					{
						pixel_error=MAXIMUM_ERROR;
					}
					else 
					{
						diff[R] = srcimg[3*((starty+y)*width+startx+x)+R] - CLAMP(0,possible_colors[c][R],255);
						diff[G] = srcimg[3*((starty+y)*width+startx+x)+G] - CLAMP(0,possible_colors[c][G],255);
						diff[B] = srcimg[3*((starty+y)*width+startx+x)+B] - CLAMP(0,possible_colors[c][B],255);

						pixel_error =	weight[R]*SQUARE(diff[R]) +
										weight[G]*SQUARE(diff[G]) +
										weight[B]*SQUARE(diff[B]);
					}

					// Choose best error
					if (pixel_error < best_pixel_error) 
					{
						best_pixel_error = pixel_error;
						pixel_colors ^= (pixel_colors & 3); // Reset the two first bits
						pixel_colors |= c;
					} 
				}
				block_error += best_pixel_error;
			}
		}
		if (block_error < best_block_error) 
		{
			best_block_error = block_error;
			distance = d;
			pixel_indices = pixel_colors;
		}
	}
	return best_block_error;
}

// Calculate the error for the block at position (startx,starty)
// The parameters needed for reconstruction is calculated as well
// 
// In the 58H bit mode, we only have pattern H.
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double calculateErrorAndCompress58H(uint8* srcimg, int width, int startx, int starty, uint8 (colorsRGB444)[2][3], uint8 &distance, unsigned int &pixel_indices) 
{
	double block_error = 0, 
	       best_block_error = MAXIMUM_ERROR, 
				 pixel_error, 
				 best_pixel_error;
	int diff[3];
	unsigned int pixel_colors;
	uint8 possible_colors[4][3];
	uint8 colors[2][3];

	
	decompressColor(R_BITS58H, G_BITS58H, B_BITS58H, colorsRGB444, colors);

	// Test all distances
	for (uint8 d = 0; d < BINPOW(TABLE_BITS_58H); ++d) 
	{
		calculatePaintColors58H(d, PATTERN_H, colors, possible_colors);

		block_error = 0;	
		pixel_colors = 0;

		// Loop block
		for (size_t y = 0; y < BLOCKHEIGHT; ++y) 
		{
			for (size_t x = 0; x < BLOCKWIDTH; ++x) 
			{
				best_pixel_error = MAXIMUM_ERROR;
				pixel_colors <<=2; // Make room for next value

				// Loop possible block colors
				for (uint8 c = 0; c < 4; ++c) 
				{
					diff[R] = srcimg[3*((starty+y)*width+startx+x)+R] - CLAMP(0,possible_colors[c][R],255);
					diff[G] = srcimg[3*((starty+y)*width+startx+x)+G] - CLAMP(0,possible_colors[c][G],255);
					diff[B] = srcimg[3*((starty+y)*width+startx+x)+B] - CLAMP(0,possible_colors[c][B],255);

					pixel_error =	weight[R]*SQUARE(diff[R]) +
									weight[G]*SQUARE(diff[G]) +
									weight[B]*SQUARE(diff[B]);

					// Choose best error
					if (pixel_error < best_pixel_error) 
					{
						best_pixel_error = pixel_error;
						pixel_colors ^= (pixel_colors & 3); // Reset the two first bits
						pixel_colors |= c;
					} 
				}
				block_error += best_pixel_error;
			}
		}
		
		if (block_error < best_block_error) 
		{
			best_block_error = block_error;
			distance = d;
			pixel_indices = pixel_colors;
		}
	}
		
	return best_block_error;
}

// Makes sure that col0 < col1;
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void sortColorsRGB444(uint8 (colorsRGB444)[2][3])
{
	unsigned int col0, col1, tcol;

	// sort colors
	col0 = 16*16*colorsRGB444[0][R] + 16*colorsRGB444[0][G] + colorsRGB444[0][B];
	col1 = 16*16*colorsRGB444[1][R] + 16*colorsRGB444[1][G] + colorsRGB444[1][B];

	// After this, col0 should be smaller than col1 (col0 < col1)
	if( col0 > col1)
	{
		tcol = col0;
		col0 = col1;
		col1 = tcol;
	}
	else
	{
		if(col0 == col1)
		{	
			// Both colors are the same. That is useless. If they are both black,
			// col1 can just as well be (0,0,1). Else, col0 can be col1 - 1.
			if(col0 == 0)
				col1 = col0+1;
			else
				col0 = col1-1;
		}
	}
	
	colorsRGB444[0][R] = GETBITS(col0, 4, 11);
	colorsRGB444[0][G] = GETBITS(col0, 4, 7);
	colorsRGB444[0][B] = GETBITS(col0, 4, 3);
	colorsRGB444[1][R] = GETBITS(col1, 4, 11);
	colorsRGB444[1][G] = GETBITS(col1, 4, 7);
	colorsRGB444[1][B] = GETBITS(col1, 4, 3);
}

// The below code should compress the block to 58 bits. 
// The bit layout is thought to be:
//
//|63 62 61 60 59 58|57 56 55 54|53 52 51 50|49 48 47 46|45 44 43 42|41 40 39 38|37 36 35 34|33 32|
//|-------empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|d2 d1|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
//
// The distance d is three bits, d2 (MSB), d1 and d0 (LSB). d0 is not stored explicitly. 
// Instead if the 12-bit word red0,green0,blue0 < red1,green1,blue1, d0 is assumed to be 0.
// Else, it is assumed to be 1.
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int compressBlockTHUMB58HFastestPerceptual1000(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2) 
{
	unsigned int best_error = MAXERR1000;
	uint8 best_colorsRGB444[2][3];
	unsigned int best_pixel_indices;
	uint8 best_distance;

	unsigned int error_no_i;
	uint8 colorsRGB444_no_i[2][3];
	unsigned int pixel_indices_no_i;
	uint8 distance_no_i;
	uint8 colors[2][3];
	
	// Calculate average color using the LBG-algorithm but discarding the intensity in the error function
	computeColorLBGHalfIntensityFast(img, width, startx, starty, colors);
	compressColor(R_BITS58H, G_BITS58H, B_BITS58H, colors, colorsRGB444_no_i);
	sortColorsRGB444(colorsRGB444_no_i);

	error_no_i = calculateErrorAndCompress58Hperceptual1000(img, width, startx, starty, colorsRGB444_no_i, distance_no_i, pixel_indices_no_i);

	best_error = error_no_i;	
	best_distance = distance_no_i; 
	best_pixel_indices = pixel_indices_no_i;
	copyColors(colorsRGB444_no_i, best_colorsRGB444);

	//                   | col0 >= col1      col0 < col1
	//------------------------------------------------------
	// (dist & 1) = 1    | no need to swap | need to swap
	//                   |-----------------+----------------
	// (dist & 1) = 0    | need to swap    | no need to swap
	//
	// This can be done with an xor test.

	int best_colorsRGB444_packed[2];
	best_colorsRGB444_packed[0] = (best_colorsRGB444[0][R] << 8) + (best_colorsRGB444[0][G] << 4) + best_colorsRGB444[0][B];
	best_colorsRGB444_packed[1] = (best_colorsRGB444[1][R] << 8) + (best_colorsRGB444[1][G] << 4) + best_colorsRGB444[1][B];
	if( (best_colorsRGB444_packed[0] >= best_colorsRGB444_packed[1]) ^ ((best_distance & 1)==1) )
	{
		swapColors(best_colorsRGB444);

		// Reshuffle pixel indices to to exchange C1 with C3, and C2 with C4
		best_pixel_indices = (0x55555555 & best_pixel_indices) | (0xaaaaaaaa & (~best_pixel_indices));
	}
	
	// Put the compress params into the compression block 

	compressed1 = 0;

	PUTBITSHIGH( compressed1, best_colorsRGB444[0][R], 4, 57);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[0][G], 4, 53);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[0][B], 4, 49);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][R], 4, 45);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][G], 4, 41);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][B], 4, 37);
	PUTBITSHIGH( compressed1, (best_distance >> 1), 2, 33);

	compressed2 = 0;
	best_pixel_indices=indexConversion(best_pixel_indices);
	PUTBITS( compressed2, best_pixel_indices, 32, 31);

	return best_error;
}

// The below code should compress the block to 58 bits. 
// This is supposed to match the first of the three modes in TWOTIMER.
// The bit layout is thought to be:
//
//|63 62 61 60 59 58|57 56 55 54|53 52 51 50|49 48 47 46|45 44 43 42|41 40 39 38|37 36 35 34|33 32|
//|-------empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|d2 d1|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
//
// The distance d is three bits, d2 (MSB), d1 and d0 (LSB). d0 is not stored explicitly. 
// Instead if the 12-bit word red0,green0,blue0 < red1,green1,blue1, d0 is assumed to be 0.
// Else, it is assumed to be 1.
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double compressBlockTHUMB58HFastest(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2) 
{
	double best_error = MAXIMUM_ERROR;
	uint8 best_colorsRGB444[2][3];
	unsigned int best_pixel_indices;
	uint8 best_distance;

	double error_no_i;
	uint8 colorsRGB444_no_i[2][3];
	unsigned int pixel_indices_no_i;
	uint8 distance_no_i;
	uint8 colors[2][3];
	
	// Calculate average color using the LBG-algorithm but discarding the intensity in the error function
	computeColorLBGHalfIntensityFast(img, width, startx, starty, colors);
	compressColor(R_BITS58H, G_BITS58H, B_BITS58H, colors, colorsRGB444_no_i);
	sortColorsRGB444(colorsRGB444_no_i);

	error_no_i = calculateErrorAndCompress58H(img, width, startx, starty, colorsRGB444_no_i, distance_no_i, pixel_indices_no_i);

	best_error = error_no_i;	
	best_distance = distance_no_i; 
	best_pixel_indices = pixel_indices_no_i;
	copyColors(colorsRGB444_no_i, best_colorsRGB444);

	//                   | col0 >= col1      col0 < col1
	//------------------------------------------------------
	// (dist & 1) = 1    | no need to swap | need to swap
	//                   |-----------------+----------------
	// (dist & 1) = 0    | need to swap    | no need to swap
	//
	// This can be done with an xor test.

	int best_colorsRGB444_packed[2];
	best_colorsRGB444_packed[0] = (best_colorsRGB444[0][R] << 8) + (best_colorsRGB444[0][G] << 4) + best_colorsRGB444[0][B];
	best_colorsRGB444_packed[1] = (best_colorsRGB444[1][R] << 8) + (best_colorsRGB444[1][G] << 4) + best_colorsRGB444[1][B];
	if( (best_colorsRGB444_packed[0] >= best_colorsRGB444_packed[1]) ^ ((best_distance & 1)==1) )
	{
		swapColors(best_colorsRGB444);

		// Reshuffle pixel indices to to exchange C1 with C3, and C2 with C4
		best_pixel_indices = (0x55555555 & best_pixel_indices) | (0xaaaaaaaa & (~best_pixel_indices));
	}

	// Put the compress params into the compression block 

	compressed1 = 0;

	PUTBITSHIGH( compressed1, best_colorsRGB444[0][R], 4, 57);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[0][G], 4, 53);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[0][B], 4, 49);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][R], 4, 45);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][G], 4, 41);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][B], 4, 37);
	PUTBITSHIGH( compressed1, (best_distance >> 1), 2, 33);
	best_pixel_indices=indexConversion(best_pixel_indices);
	compressed2 = 0;
	PUTBITS( compressed2, best_pixel_indices, 32, 31);

	return best_error;
}

//same as above, but with 1-bit alpha
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double compressBlockTHUMB58HAlpha(uint8 *img, uint8* alphaimg, int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2) 
{
	double best_error = MAXIMUM_ERROR;
	uint8 best_colorsRGB444[2][3];
	unsigned int best_pixel_indices;
	uint8 best_distance;

	double error_no_i;
	uint8 colorsRGB444_no_i[2][3];
	unsigned int pixel_indices_no_i;
	uint8 distance_no_i;
	uint8 colors[2][3];
	
	// Calculate average color using the LBG-algorithm but discarding the intensity in the error function
	computeColorLBGHalfIntensityFast(img, width, startx, starty, colors);
	compressColor(R_BITS58H, G_BITS58H, B_BITS58H, colors, colorsRGB444_no_i);
	sortColorsRGB444(colorsRGB444_no_i);

	error_no_i = calculateErrorAndCompress58HAlpha(img, alphaimg,width, startx, starty, colorsRGB444_no_i, distance_no_i, pixel_indices_no_i);

	best_error = error_no_i;	
	best_distance = distance_no_i; 
	best_pixel_indices = pixel_indices_no_i;
	copyColors(colorsRGB444_no_i, best_colorsRGB444);

	//                   | col0 >= col1      col0 < col1
	//------------------------------------------------------
	// (dist & 1) = 1    | no need to swap | need to swap
	//                   |-----------------+----------------
	// (dist & 1) = 0    | need to swap    | no need to swap
	//
	// This can be done with an xor test.

	int best_colorsRGB444_packed[2];
	best_colorsRGB444_packed[0] = (best_colorsRGB444[0][R] << 8) + (best_colorsRGB444[0][G] << 4) + best_colorsRGB444[0][B];
	best_colorsRGB444_packed[1] = (best_colorsRGB444[1][R] << 8) + (best_colorsRGB444[1][G] << 4) + best_colorsRGB444[1][B];
	if( (best_colorsRGB444_packed[0] >= best_colorsRGB444_packed[1]) ^ ((best_distance & 1)==1) )
	{
		swapColors(best_colorsRGB444);

		// Reshuffle pixel indices to to exchange C1 with C3, and C2 with C4
		best_pixel_indices = (0x55555555 & best_pixel_indices) | (0xaaaaaaaa & (~best_pixel_indices));
	}

	// Put the compress params into the compression block 

	compressed1 = 0;

	PUTBITSHIGH( compressed1, best_colorsRGB444[0][R], 4, 57);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[0][G], 4, 53);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[0][B], 4, 49);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][R], 4, 45);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][G], 4, 41);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][B], 4, 37);
	PUTBITSHIGH( compressed1, (best_distance >> 1), 2, 33);
	best_pixel_indices=indexConversion(best_pixel_indices);
	compressed2 = 0;
	PUTBITS( compressed2, best_pixel_indices, 32, 31);

	return best_error;
}

// The below code should compress the block to 58 bits. 
// This is supposed to match the first of the three modes in TWOTIMER.
// The bit layout is thought to be:
//
//|63 62 61 60 59 58|57 56 55 54|53 52 51 50|49 48 47 46|45 44 43 42|41 40 39 38|37 36 35 34|33 32|
//|-------empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|d2 d1|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
//
// The distance d is three bits, d2 (MSB), d1 and d0 (LSB). d0 is not stored explicitly. 
// Instead if the 12-bit word red0,green0,blue0 < red1,green1,blue1, d0 is assumed to be 0.
// Else, it is assumed to be 1.
//
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double compressBlockTHUMB58HFast(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2) 
{
	double best_error = MAXIMUM_ERROR;
	uint8 best_colorsRGB444[2][3];
	unsigned int best_pixel_indices;
	uint8 best_distance;

	double error_no_i;
	uint8 colorsRGB444_no_i[2][3];
	unsigned int pixel_indices_no_i;
	uint8 distance_no_i;

	double error_half_i;
	uint8 colorsRGB444_half_i[2][3];
	unsigned int pixel_indices_half_i;
	uint8 distance_half_i;

	double error;
	uint8 colorsRGB444[2][3];
	unsigned int pixel_indices;
	uint8 distance;

	uint8 colors[2][3];
	
	// Calculate average color using the LBG-algorithm but discarding the intensity in the error function
	computeColorLBGNotIntensity(img, width, startx, starty, colors);
	compressColor(R_BITS58H, G_BITS58H, B_BITS58H, colors, colorsRGB444_no_i);
	sortColorsRGB444(colorsRGB444_no_i);
	error_no_i = calculateErrorAndCompress58H(img, width, startx, starty, colorsRGB444_no_i, distance_no_i, pixel_indices_no_i);

	// Calculate average color using the LBG-algorithm but halfing the influence of the intensity in the error function
	computeColorLBGNotIntensity(img, width, startx, starty, colors);
	compressColor(R_BITS58H, G_BITS58H, B_BITS58H, colors, colorsRGB444_half_i);
	sortColorsRGB444(colorsRGB444_half_i);
	error_half_i = calculateErrorAndCompress58H(img, width, startx, starty, colorsRGB444_half_i, distance_half_i, pixel_indices_half_i);

	// Calculate average color using the LBG-algorithm
	computeColorLBG(img, width, startx, starty, colors);
	compressColor(R_BITS58H, G_BITS58H, B_BITS58H, colors, colorsRGB444);
	sortColorsRGB444(colorsRGB444);
	error = calculateErrorAndCompress58H(img, width, startx, starty, colorsRGB444, distance, pixel_indices);

	best_error = error_no_i;	
	best_distance = distance_no_i; 
	best_pixel_indices = pixel_indices_no_i;
	copyColors(colorsRGB444_no_i, best_colorsRGB444);

	if(error_half_i < best_error)
	{
		best_error = error_half_i;
		best_distance = distance_half_i;
		best_pixel_indices = pixel_indices_half_i;
		copyColors(colorsRGB444_half_i, best_colorsRGB444);
	}

	if(error < best_error)
	{
		best_error = error;	
		best_distance = distance; 
		best_pixel_indices = pixel_indices;
		copyColors(colorsRGB444, best_colorsRGB444);
	}

	//                   | col0 >= col1      col0 < col1
	//------------------------------------------------------
	// (dist & 1) = 1    | no need to swap | need to swap
	//                   |-----------------+----------------
	// (dist & 1) = 0    | need to swap    | no need to swap
	//
	// This can be done with an xor test.

	int best_colorsRGB444_packed[2];
	best_colorsRGB444_packed[0] = (best_colorsRGB444[0][R] << 8) + (best_colorsRGB444[0][G] << 4) + best_colorsRGB444[0][B];
	best_colorsRGB444_packed[1] = (best_colorsRGB444[1][R] << 8) + (best_colorsRGB444[1][G] << 4) + best_colorsRGB444[1][B];
	if( (best_colorsRGB444_packed[0] >= best_colorsRGB444_packed[1]) ^ ((best_distance & 1)==1) )
	{
		swapColors(best_colorsRGB444);

		// Reshuffle pixel indices to to exchange C1 with C3, and C2 with C4
		best_pixel_indices = (0x55555555 & best_pixel_indices) | (0xaaaaaaaa & (~best_pixel_indices));
	}

	// Put the compress params into the compression block 
	compressed1 = 0;

	PUTBITSHIGH( compressed1, best_colorsRGB444[0][R], 4, 57);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[0][G], 4, 53);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[0][B], 4, 49);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][R], 4, 45);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][G], 4, 41);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][B], 4, 37);
	PUTBITSHIGH( compressed1, (best_distance >> 1), 2, 33);
	best_pixel_indices=indexConversion(best_pixel_indices);
	compressed2 = 0;
	PUTBITS( compressed2, best_pixel_indices, 32, 31);

	return best_error;
}

// Compress block testing both individual and differential mode.
// Perceptual error metric.
// Combined quantization for colors.
// Both flipped and unflipped tested.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockDiffFlipCombinedPerceptual(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2)
{

	unsigned int compressed1_norm, compressed2_norm;
	unsigned int compressed1_flip, compressed2_flip;
	uint8 avg_color_quant1[3], avg_color_quant2[3];

	float avg_color_float1[3],avg_color_float2[3];
	int enc_color1[3], enc_color2[3], diff[3];
	int min_error=255*255*8*3;
	unsigned int best_table_indices1=0, best_table_indices2=0;
	unsigned int best_table1=0, best_table2=0;
	int diffbit;

	int norm_err=0;
	int flip_err=0;

	// First try normal blocks 2x4:

	computeAverageColor2x4noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor2x4noQuantFloat(img,width,height,startx+2,starty,avg_color_float2);

	// First test if avg_color1 is similar enough to avg_color2 so that
	// we can use differential coding of colors. 

	float eps;

	uint8 dummy[3];

	quantize555ColorCombinedPerceptual(avg_color_float1, enc_color1, dummy);
	quantize555ColorCombinedPerceptual(avg_color_float2, enc_color2, dummy);

	diff[0] = enc_color2[0]-enc_color1[0];	
	diff[1] = enc_color2[1]-enc_color1[1];	
	diff[2] = enc_color2[2]-enc_color1[2];

	if( (diff[0] >= -4) && (diff[0] <= 3) && (diff[1] >= -4) && (diff[1] <= 3) && (diff[2] >= -4) && (diff[2] <= 3) )
	{
		diffbit = 1;

		// The difference to be coded:

		diff[0] = enc_color2[0]-enc_color1[0];	
		diff[1] = enc_color2[1]-enc_color1[1];	
		diff[2] = enc_color2[2]-enc_color1[2];

		avg_color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
		avg_color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
		avg_color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
		avg_color_quant2[0] = enc_color2[0] << 3 | (enc_color2[0] >> 2);
		avg_color_quant2[1] = enc_color2[1] << 3 | (enc_color2[1] >> 2);
		avg_color_quant2[2] = enc_color2[2] << 3 | (enc_color2[2] >> 2);

		// Pack bits into the first word. 

		//     ETC1_RGB8_OES:
		// 
		//     a) bit layout in bits 63 through 32 if diffbit = 0
		// 
		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
		//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------
		//     
		//     b) bit layout in bits 63 through 32 if diffbit = 1
		// 
		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |diff|flip|
		//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------
		// 
		//     c) bit layout in bits 31 through 0 (in both cases)
		// 
		//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3   2   1  0
		//      --------------------------------------------------------------------------------------------------
		//     |       most significant pixel index bits       |         least significant pixel index bits       |  
		//     | p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a| p| o| n| m| l| k| j| i| h| g| f| e| d| c | b | a |
		//      --------------------------------------------------------------------------------------------------      

		compressed1_norm = 0;
		PUTBITSHIGH( compressed1_norm, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_norm, enc_color1[0], 5, 63);
 		PUTBITSHIGH( compressed1_norm, enc_color1[1], 5, 55);
 		PUTBITSHIGH( compressed1_norm, enc_color1[2], 5, 47);
 		PUTBITSHIGH( compressed1_norm, diff[0],       3, 58);
 		PUTBITSHIGH( compressed1_norm, diff[1],       3, 50);
 		PUTBITSHIGH( compressed1_norm, diff[2],       3, 42);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		norm_err = 0;

		// left part of block
		norm_err = tryalltables_3bittable2x4percep(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);

		// right part of block
		norm_err += tryalltables_3bittable2x4percep(img,width,height,startx+2,starty,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_norm, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_norm, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_norm,           0,   1, 32);

		compressed2_norm = 0;
		PUTBITS( compressed2_norm, (best_pixel_indices1_MSB     ), 8, 23);
		PUTBITS( compressed2_norm, (best_pixel_indices2_MSB     ), 8, 31);
		PUTBITS( compressed2_norm, (best_pixel_indices1_LSB     ), 8, 7);
		PUTBITS( compressed2_norm, (best_pixel_indices2_LSB     ), 8, 15);
	}
	else
	{
		diffbit = 0;
		// The difference is bigger than what fits in 555 plus delta-333, so we will have
		// to deal with 444 444.

		eps = (float) 0.0001;

		quantize444ColorCombinedPerceptual(avg_color_float1, enc_color1, dummy);
		quantize444ColorCombinedPerceptual(avg_color_float2, enc_color2, dummy);

		avg_color_quant1[0] = enc_color1[0] << 4 | enc_color1[0]; 
		avg_color_quant1[1] = enc_color1[1] << 4 | enc_color1[1]; 
		avg_color_quant1[2] = enc_color1[2] << 4 | enc_color1[2];
		avg_color_quant2[0] = enc_color2[0] << 4 | enc_color2[0]; 
		avg_color_quant2[1] = enc_color2[1] << 4 | enc_color2[1]; 
		avg_color_quant2[2] = enc_color2[2] << 4 | enc_color2[2];

		// Pack bits into the first word. 

		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
		//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------

		compressed1_norm = 0;
		PUTBITSHIGH( compressed1_norm, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_norm, enc_color1[0], 4, 63);
 		PUTBITSHIGH( compressed1_norm, enc_color1[1], 4, 55);
 		PUTBITSHIGH( compressed1_norm, enc_color1[2], 4, 47);
 		PUTBITSHIGH( compressed1_norm, enc_color2[0], 4, 59);
 		PUTBITSHIGH( compressed1_norm, enc_color2[1], 4, 51);
 		PUTBITSHIGH( compressed1_norm, enc_color2[2], 4, 43);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;
		
		// left part of block
		norm_err = tryalltables_3bittable2x4percep(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);

		// right part of block
		norm_err += tryalltables_3bittable2x4percep(img,width,height,startx+2,starty,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_norm, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_norm, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_norm,           0,   1, 32);

		compressed2_norm = 0;
		PUTBITS( compressed2_norm, (best_pixel_indices1_MSB     ), 8, 23);
		PUTBITS( compressed2_norm, (best_pixel_indices2_MSB     ), 8, 31);
		PUTBITS( compressed2_norm, (best_pixel_indices1_LSB     ), 8, 7);
		PUTBITS( compressed2_norm, (best_pixel_indices2_LSB     ), 8, 15);
	}

	// Now try flipped blocks 4x2:
	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty,avg_color_float1);
	computeAverageColor4x2noQuantFloat(img,width,height,startx,starty+2,avg_color_float2);

	// First test if avg_color1 is similar enough to avg_color2 so that
	// we can use differential coding of colors. 
	quantize555ColorCombinedPerceptual(avg_color_float1, enc_color1, dummy);
	quantize555ColorCombinedPerceptual(avg_color_float2, enc_color2, dummy);

	diff[0] = enc_color2[0]-enc_color1[0];	
	diff[1] = enc_color2[1]-enc_color1[1];	
	diff[2] = enc_color2[2]-enc_color1[2];

	if( (diff[0] >= -4) && (diff[0] <= 3) && (diff[1] >= -4) && (diff[1] <= 3) && (diff[2] >= -4) && (diff[2] <= 3) )
	{
		diffbit = 1;

		// The difference to be coded:
		diff[0] = enc_color2[0]-enc_color1[0];	
		diff[1] = enc_color2[1]-enc_color1[1];	
		diff[2] = enc_color2[2]-enc_color1[2];

		avg_color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
		avg_color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
		avg_color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
		avg_color_quant2[0] = enc_color2[0] << 3 | (enc_color2[0] >> 2);
		avg_color_quant2[1] = enc_color2[1] << 3 | (enc_color2[1] >> 2);
		avg_color_quant2[2] = enc_color2[2] << 3 | (enc_color2[2] >> 2);

		// Pack bits into the first word. 
		compressed1_flip = 0;
		PUTBITSHIGH( compressed1_flip, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_flip, enc_color1[0], 5, 63);
 		PUTBITSHIGH( compressed1_flip, enc_color1[1], 5, 55);
 		PUTBITSHIGH( compressed1_flip, enc_color1[2], 5, 47);
 		PUTBITSHIGH( compressed1_flip, diff[0],       3, 58);
 		PUTBITSHIGH( compressed1_flip, diff[1],       3, 50);
 		PUTBITSHIGH( compressed1_flip, diff[2],       3, 42);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		// upper part of block
		flip_err = tryalltables_3bittable4x2percep(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
		// lower part of block
		flip_err += tryalltables_3bittable4x2percep(img,width,height,startx,starty+2,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_flip, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_flip, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_flip,           1,   1, 32);

		best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
		best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);
		
		compressed2_flip = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);
	}
	else
	{
		diffbit = 0;
		// The difference is bigger than what fits in 555 plus delta-333, so we will have
		// to deal with 444 444.
		eps = (float) 0.0001;

		quantize444ColorCombinedPerceptual(avg_color_float1, enc_color1, dummy);
		quantize444ColorCombinedPerceptual(avg_color_float2, enc_color2, dummy);

		avg_color_quant1[0] = enc_color1[0] << 4 | enc_color1[0]; 
		avg_color_quant1[1] = enc_color1[1] << 4 | enc_color1[1]; 
		avg_color_quant1[2] = enc_color1[2] << 4 | enc_color1[2];
		avg_color_quant2[0] = enc_color2[0] << 4 | enc_color2[0]; 
		avg_color_quant2[1] = enc_color2[1] << 4 | enc_color2[1]; 
		avg_color_quant2[2] = enc_color2[2] << 4 | enc_color2[2];

		//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
		//      ---------------------------------------------------------------------------------------------------
		//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
		//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
		//      ---------------------------------------------------------------------------------------------------

		// Pack bits into the first word. 
		compressed1_flip = 0;
		PUTBITSHIGH( compressed1_flip, diffbit,       1, 33);
 		PUTBITSHIGH( compressed1_flip, enc_color1[0], 4, 63);
 		PUTBITSHIGH( compressed1_flip, enc_color1[1], 4, 55);
 		PUTBITSHIGH( compressed1_flip, enc_color1[2], 4, 47);
 		PUTBITSHIGH( compressed1_flip, enc_color2[0], 4, 59);
 		PUTBITSHIGH( compressed1_flip, enc_color2[1], 4, 51);
 		PUTBITSHIGH( compressed1_flip, enc_color2[2], 4, 43);

		unsigned int best_pixel_indices1_MSB;
		unsigned int best_pixel_indices1_LSB;
		unsigned int best_pixel_indices2_MSB;
		unsigned int best_pixel_indices2_LSB;

		// upper part of block
		flip_err = tryalltables_3bittable4x2percep(img,width,height,startx,starty,avg_color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
		// lower part of block
		flip_err += tryalltables_3bittable4x2percep(img,width,height,startx,starty+2,avg_color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

 		PUTBITSHIGH( compressed1_flip, best_table1,   3, 39);
 		PUTBITSHIGH( compressed1_flip, best_table2,   3, 36);
 		PUTBITSHIGH( compressed1_flip,           1,   1, 32);

		best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
		best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);
		
		compressed2_flip = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);
	}

	// Now lets see which is the best table to use. Only 8 tables are possible. 
	if(norm_err <= flip_err)
	{
		compressed1 = compressed1_norm | 0;
		compressed2 = compressed2_norm;
	}
	else
	{
		compressed1 = compressed1_flip | 1;
		compressed2 = compressed2_flip;
	}
}

// Calculate the error of a block
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double calcBlockErrorRGB(uint8 *img, uint8 *imgdec, int width, int height, int startx, int starty)
{
	int xx,yy;
	double err;

	err = 0;

	for(xx = startx; xx< startx+4; xx++)
	{
		for(yy = starty; yy<starty+4; yy++)
		{
 			err += SQUARE(1.0*RED(img,width,xx,yy)  - 1.0*RED(imgdec, width, xx,yy));
 			err += SQUARE(1.0*GREEN(img,width,xx,yy)- 1.0*GREEN(imgdec, width, xx,yy));
 			err += SQUARE(1.0*BLUE(img,width,xx,yy) - 1.0*BLUE(imgdec, width, xx,yy));
		}
	}

	return err;
}

// Calculate the perceptually weighted error of a block
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double calcBlockPerceptualErrorRGB(uint8 *img, uint8 *imgdec, int width, int height, int startx, int starty)
{
	int xx,yy;
	double err;

	err = 0;

	for(xx = startx; xx< startx+4; xx++)
	{
		for(yy = starty; yy<starty+4; yy++)
		{
 			err += PERCEPTUAL_WEIGHT_R_SQUARED*SQUARE(1.0*RED(img,width,xx,yy)  - 1.0*RED(imgdec, width, xx,yy));
 			err += PERCEPTUAL_WEIGHT_G_SQUARED*SQUARE(1.0*GREEN(img,width,xx,yy)- 1.0*GREEN(imgdec, width, xx,yy));
 			err += PERCEPTUAL_WEIGHT_B_SQUARED*SQUARE(1.0*BLUE(img,width,xx,yy) - 1.0*BLUE(imgdec, width, xx,yy));
		}
	}

	return err;
}

// Compress an ETC1 block (or the individual and differential modes of an ETC2 block)
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double compressBlockDiffFlipFast(uint8 *img, uint8 *imgdec,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2)
{
	unsigned int average_block1;
	unsigned int average_block2;
	double error_average;

	unsigned int combined_block1;
	unsigned int combined_block2;
	double error_combined;

	double best_error;

	// First quantize the average color to the nearest neighbor.
	compressBlockDiffFlipAverage(img, width, height, startx, starty, average_block1, average_block2);
	decompressBlockDiffFlip(average_block1, average_block2, imgdec, width, height, startx, starty);
	error_average = calcBlockErrorRGB(img, imgdec, width, height, startx, starty);

	// Then quantize the average color taking into consideration that intensity can change
	compressBlockDiffFlipCombined(img, width, height, startx, starty, combined_block1, combined_block2);
	decompressBlockDiffFlip(combined_block1, combined_block2, imgdec, width, height, startx, starty);
	error_combined = calcBlockErrorRGB(img, imgdec, width, height, startx, starty);

	if(error_combined < error_average)
	{
		compressed1 = combined_block1;
		compressed2 = combined_block2;
		best_error = error_combined;
	}
	else
	{
		compressed1 = average_block1;
		compressed2 = average_block2;
		best_error = error_average;
	}
	return best_error;
}

// Compress an ETC1 block (or the individual and differential modes of an ETC2 block)
// Uses perceptual error metric.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockDiffFlipFastPerceptual(uint8 *img, uint8 *imgdec,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2)
{
	unsigned int average_block1;
	unsigned int average_block2;
	double error_average;

	unsigned int combined_block1;
	unsigned int combined_block2;
	double error_combined;

	// First quantize the average color to the nearest neighbor.
	compressBlockDiffFlipAveragePerceptual(img, width, height, startx, starty, average_block1, average_block2);
	decompressBlockDiffFlip(average_block1, average_block2, imgdec, width, height, startx, starty);
	error_average = calcBlockPerceptualErrorRGB(img, imgdec, width, height, startx, starty);

	// Then quantize the average color taking into consideration that intensity can change 
	compressBlockDiffFlipCombinedPerceptual(img, width, height, startx, starty, combined_block1, combined_block2);
	decompressBlockDiffFlip(combined_block1, combined_block2, imgdec, width, height, startx, starty);
	error_combined = calcBlockPerceptualErrorRGB(img, imgdec, width, height, startx, starty);

	if(error_combined < error_average)
	{
		compressed1 = combined_block1;
		compressed2 = combined_block2;
	}
	else
	{
		compressed1 = average_block1;
		compressed2 = average_block2;
	}
}

// Compresses the differential mode of an ETC2 block with punchthrough alpha
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
int compressBlockDifferentialWithAlpha(bool isTransparent, uint8* img, uint8* alphaimg, uint8* imgdec, int width, int height, int startx, int starty, unsigned int &etc1_word1, unsigned int &etc1_word2) 
{
	unsigned int compressed1_norm, compressed2_norm;
	unsigned int compressed1_flip, compressed2_flip;
	unsigned int compressed1_temp, compressed2_temp;
	uint8 avg_color_quant1[3], avg_color_quant2[3];

	float avg_color_float1[3],avg_color_float2[3];
	int enc_color1[3], enc_color2[3], diff[3];
	int min_error=255*255*8*3;
	
	int norm_err=0;
	int flip_err=0;
	int temp_err=0;
	for(int flipbit=0; flipbit<2; flipbit++) 
	{
		//compute average color for each half.
		for(int c=0; c<3; c++) 
		{
			avg_color_float1[c]=0;
			avg_color_float2[c]=0;
			float sum1=0;
			float sum2=0;
			for(int x=0; x<4; x++) 
			{
				for(int y=0; y<4; y++) 
				{
					float fac=1;
					int index = x+startx+(y+starty)*width;
					//transparent pixels are only barely figured into the average. This ensures that they DO matter if we have only
					//transparent pixels in one half of the block, and not otherwise. A bit ugly perhaps.
					if(alphaimg[index]<128)
						fac=0.0001f;
					float col = fac*img[index*3+c];
					if( (flipbit==0&&x<2) || (flipbit==1&&y<2) ) 
					{
						sum1+=fac;
						avg_color_float1[c]+=col;
					}
					else 
					{
						sum2+=fac;
						avg_color_float2[c]+=col;
					}
				}
			}
			avg_color_float1[c]/=sum1;
			avg_color_float2[c]/=sum2;
		}
		uint8 dummy[3];
		quantize555ColorCombined(avg_color_float1, enc_color1, dummy);
		quantize555ColorCombined(avg_color_float2, enc_color2, dummy);

		diff[0] = enc_color2[0]-enc_color1[0];	
		diff[1] = enc_color2[1]-enc_color1[1];	
		diff[2] = enc_color2[2]-enc_color1[2];

		//make sure diff is small enough for diff-coding
		for(int c=0; c<3; c++) 
		{
				if(diff[c]<-4)
					diff[c]=-4;
				if(diff[c]>3)
					diff[c]=3;
				enc_color2[c]=enc_color1[c]+diff[c];
		}

		avg_color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
		avg_color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
		avg_color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
		avg_color_quant2[0] = enc_color2[0] << 3 | (enc_color2[0] >> 2);
		avg_color_quant2[1] = enc_color2[1] << 3 | (enc_color2[1] >> 2);
		avg_color_quant2[2] = enc_color2[2] << 3 | (enc_color2[2] >> 2);

		// Pack bits into the first word. 
		// see regular compressblockdiffflipfast for details

		compressed1_temp = 0;
		PUTBITSHIGH( compressed1_temp, !isTransparent,       1, 33);
		PUTBITSHIGH( compressed1_temp, enc_color1[0], 5, 63);
		PUTBITSHIGH( compressed1_temp, enc_color1[1], 5, 55);
		PUTBITSHIGH( compressed1_temp, enc_color1[2], 5, 47);
		PUTBITSHIGH( compressed1_temp, diff[0],       3, 58);
		PUTBITSHIGH( compressed1_temp, diff[1],       3, 50);
		PUTBITSHIGH( compressed1_temp, diff[2],       3, 42);

		temp_err = 0;
		
		int besterror[2];
		besterror[0]=255*255*3*16;
		besterror[1]=255*255*3*16;
		int besttable[2];
		int best_indices_LSB[16];
		int	best_indices_MSB[16];
		//for each table, we're going to compute the indices required to get minimum error in each half.
		//then we'll check if this was the best table for either half, and set besterror/besttable accordingly.
		for(int table=0; table<8; table++) 
		{
			int taberror[2];//count will be sort of an index of each pixel within a half, determining where the index will be placed in the bitstream.
			
			int pixel_indices_LSB[16],pixel_indices_MSB[16];
			
			for(int i=0; i<2; i++) 
			{
				taberror[i]=0;
			}
			for(int x=0; x<4; x++) 
			{
				for(int y=0; y<4; y++) 
				{
					int index = x+startx+(y+starty)*width;
					uint8 basecol[3];
					bool transparentPixel=alphaimg[index]<128;
					//determine which half of the block this pixel is in, based on the flipbit.
					int half=0;
					if( (flipbit==0&&x<2) || (flipbit&&y<2) ) 
					{
						basecol[0]=avg_color_quant1[0];
						basecol[1]=avg_color_quant1[1];
						basecol[2]=avg_color_quant1[2];
					}
					else 
					{
						half=1;
						basecol[0]=avg_color_quant2[0];
						basecol[1]=avg_color_quant2[1];
						basecol[2]=avg_color_quant2[2];
					}
					int besterri=255*255*3*2;
					int besti=0;
					int erri;
					for(int i=0; i<4; i++) 
					{
						if(i==1&&isTransparent)
							continue;
						erri=0;
						for(int c=0; c<3; c++) 
						{
							int col=CLAMP(0,((int)basecol[c])+compressParams[table*2][i],255);
							if(i==2&&isTransparent) 
							{
								 col=(int)basecol[c];
							}
							int errcol=col-((int)(img[index*3+c]));
							erri=erri+(errcol*errcol);
						}
						if(erri<besterri) 
						{
							besterri=erri;
							besti=i;
						}
					}
					if(transparentPixel) 
					{
						besterri=0;
						besti=1;
					}
					//the best index for this pixel using this table for its half is known.
					//add its error to error for this table and half.
					taberror[half]+=besterri;
					//store the index! we might toss it later though if this was a bad table.

					int pixel_index = scramble[besti];

					pixel_indices_MSB[x*4+y]=(pixel_index >> 1);
					pixel_indices_LSB[x*4+y]=(pixel_index & 1);
				}
			}
			for(int half=0; half<2; half++) 
			{
				if(taberror[half]<besterror[half]) 
				{
					besterror[half]=taberror[half];
					besttable[half]=table;
					for(int i=0; i<16; i++) 
					{
						int thishalf=0;
						int y=i%4;
						int x=i/4;
						if( !(flipbit==0&&x<2) && !(flipbit&&y<2) )
							thishalf=1;
						if(half!=thishalf) //this pixel is not in given half, don't update best index!
							continue;
						best_indices_MSB[i]=pixel_indices_MSB[i];
						best_indices_LSB[i]=pixel_indices_LSB[i];
					}
				}
			}
		}
		PUTBITSHIGH( compressed1_temp, besttable[0],   3, 39);
		PUTBITSHIGH( compressed1_temp, besttable[1],   3, 36);
		PUTBITSHIGH( compressed1_temp,      0,   1, 32);

		compressed2_temp = 0;
		for(int i=0; i<16; i++) 
		{
			PUTBITS( compressed2_temp, (best_indices_MSB[i]  ), 1, 16+i);
			PUTBITS( compressed2_temp, (best_indices_LSB[i]  ), 1, i);
		}
		
		if(flipbit) 
		{
			flip_err=besterror[0]+besterror[1];
			compressed1_flip=compressed1_temp;
			compressed2_flip=compressed2_temp;
		}
		else 
		{
			norm_err=besterror[0]+besterror[1];
			compressed1_norm=compressed1_temp;
			compressed2_norm=compressed2_temp;
		}
	}
	// Now to find out if flipping was a good idea or not

	if(norm_err <= flip_err)
	{
		etc1_word1 = compressed1_norm | 0;
		etc1_word2 = compressed2_norm;
		return norm_err;
	}
	else
	{
		etc1_word1 = compressed1_flip | 1;
		etc1_word2 = compressed2_flip;
		return flip_err;
	}
}


// Calculate RGBA error --- only count non-transparent pixels (alpha > 128)
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double calcBlockErrorRGBA(uint8 *img, uint8 *imgdec, uint8* alpha, int width, int height, int startx, int starty)
{
	int xx,yy;
	double err;

	err = 0;

	for(xx = startx; xx< startx+4; xx++)
	{
		for(yy = starty; yy<starty+4; yy++)
		{
			//only count non-transparent pixels.
			if(alpha[yy*width+xx]>128)	
			{
 				err += SQUARE(1.0*RED(img,width,xx,yy)  - 1.0*RED(imgdec, width, xx,yy));
 				err += SQUARE(1.0*GREEN(img,width,xx,yy)- 1.0*GREEN(imgdec, width, xx,yy));
 				err += SQUARE(1.0*BLUE(img,width,xx,yy) - 1.0*BLUE(imgdec, width, xx,yy));
			}
		}
	}
	return err;
}

//calculates the error for a block using the given colors, and the paremeters required to obtain the error. This version uses 1-bit punch-through alpha.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double calculateError59TAlpha(uint8* srcimg, uint8* alpha,int width, int startx, int starty, uint8 (colorsRGB444)[2][3], uint8 &distance, unsigned int &pixel_indices) 
{

	double block_error = 0, 
		   best_block_error = MAXIMUM_ERROR, 
		   pixel_error, 
		   best_pixel_error;
	int diff[3];
	uint8 best_sw;
	unsigned int pixel_colors;
	uint8 colors[2][3];
	uint8 possible_colors[4][3];

	// First use the colors as they are, then swap them
	for (uint8 sw = 0; sw <2; ++sw) 
	{ 
		if (sw == 1) 
		{
			swapColors(colorsRGB444);
		}
		decompressColor(R_BITS59T, G_BITS59T, B_BITS59T, colorsRGB444, colors);

		// Test all distances
		for (uint8 d = 0; d < BINPOW(TABLE_BITS_59T); ++d) 
		{
			calculatePaintColors59T(d,PATTERN_T, colors, possible_colors);
			
			block_error = 0;	
			pixel_colors = 0;

			// Loop block
			for (size_t y = 0; y < BLOCKHEIGHT; ++y) 
			{
				for (size_t x = 0; x < BLOCKWIDTH; ++x) 
				{
					best_pixel_error = MAXIMUM_ERROR;
					pixel_colors <<=2; // Make room for next value

					// Loop possible block colors
					if(alpha[x+startx+(y+starty)*width]==0) 
					{
						best_pixel_error=0;
						pixel_colors ^= (pixel_colors & 3); // Reset the two first bits
						pixel_colors |= 2; //insert the index for this pixel, two meaning transparent.
					}
					else 
					{
						for (uint8 c = 0; c < 4; ++c) 
						{
							
							if(c==2) 
								continue; //don't use this, because we don't have alpha here and index 2 means transparent.
							diff[R] = srcimg[3*((starty+y)*width+startx+x)+R] - CLAMP(0,possible_colors[c][R],255);
							diff[G] = srcimg[3*((starty+y)*width+startx+x)+G] - CLAMP(0,possible_colors[c][G],255);
							diff[B] = srcimg[3*((starty+y)*width+startx+x)+B] - CLAMP(0,possible_colors[c][B],255);

							pixel_error =	weight[R]*SQUARE(diff[R]) +
											weight[G]*SQUARE(diff[G]) +
											weight[B]*SQUARE(diff[B]);

							// Choose best error
							if (pixel_error < best_pixel_error) 
							{
								best_pixel_error = pixel_error;
								pixel_colors ^= (pixel_colors & 3); // Reset the two first bits
								pixel_colors |= c; //insert the index for this pixel
							} 
						}
					}
					block_error += best_pixel_error;
				}
			}
			if (block_error < best_block_error) 
			{
				best_block_error = block_error;
				distance = d;
				pixel_indices = pixel_colors;
				best_sw = sw;
			}
		}
		
		if (sw == 1 && best_sw == 0) 
		{
			swapColors(colorsRGB444);
		}
		decompressColor(R_BITS59T, G_BITS59T, B_BITS59T, colorsRGB444, colors);
	}
	return best_block_error;
}

// same as fastest t-mode compressor above, but here one of the colors (the central one in the T) is used to also signal that the pixel is transparent.
// the only difference is that calculateError has been swapped out to one that considers alpha.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double compressBlockTHUMB59TAlpha(uint8 *img, uint8* alpha, int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2) 
{
	double best_error = MAXIMUM_ERROR;
	uint8 best_colorsRGB444[2][3];
	unsigned int best_pixel_indices;
	uint8 best_distance;

	double error_no_i;
	uint8 colorsRGB444_no_i[2][3];
	unsigned int pixel_indices_no_i;
	uint8 distance_no_i;

	uint8 colors[2][3];

	// Calculate average color using the LBG-algorithm
  computeColorLBGHalfIntensityFast(img,width,startx,starty, colors);
	compressColor(R_BITS59T, G_BITS59T, B_BITS59T, colors, colorsRGB444_no_i);

	// Determine the parameters for the lowest error
	error_no_i = calculateError59TAlpha(img, alpha, width, startx, starty, colorsRGB444_no_i, distance_no_i, pixel_indices_no_i);			

	best_error = error_no_i;
	best_distance = distance_no_i;
	best_pixel_indices = pixel_indices_no_i;
	copyColors(colorsRGB444_no_i, best_colorsRGB444);

	// Put the compress params into the compression block 
	packBlock59T(best_colorsRGB444, best_distance, best_pixel_indices, compressed1, compressed2);

	return best_error;
}

// Put bits in order for the format.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void stuff59bitsDiffFalse(unsigned int thumbT59_word1, unsigned int thumbT59_word2, unsigned int &thumbT_word1, unsigned int &thumbT_word2)
{
	// Put bits in twotimer configuration for 59 (red overflows)
	// 
	// Go from this bit layout:
	//
	//     |63 62 61 60 59|58 57 56 55|54 53 52 51|50 49 48 47|46 45 44 43|42 41 40 39|38 37 36 35|34 33 32|
	//     |----empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|--dist--|
	//
	//     |31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
	//     |----------------------------------------index bits---------------------------------------------|
	//
	//
	//  To this:
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 
	//      -----------------------------------------------------------------------------------------------
	//     |// // //|R0a  |//|R0b  |G0         |B0         |R1         |G1         |B1          |da  |df|db|
	//      -----------------------------------------------------------------------------------------------
	//
	//     |31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
	//     |----------------------------------------index bits---------------------------------------------|
	//
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 
	//      -----------------------------------------------------------------------------------------------
	//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |df|fp|
	//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bt|bt|
	//      ------------------------------------------------------------------------------------------------

	uint8 R0a;
	uint8 bit, a, b, c, d, bits;

	R0a = GETBITSHIGH( thumbT59_word1, 2, 58);

	// Fix middle part
	thumbT_word1 = thumbT59_word1 << 1;
	// Fix R0a (top two bits of R0)
	PUTBITSHIGH( thumbT_word1, R0a,  2, 60);
	// Fix db (lowest bit of d)
	PUTBITSHIGH( thumbT_word1, thumbT59_word1,  1, 32);
	// 
	// Make sure that red overflows:
	a = GETBITSHIGH( thumbT_word1, 1, 60);
	b = GETBITSHIGH( thumbT_word1, 1, 59);
	c = GETBITSHIGH( thumbT_word1, 1, 57);
	d = GETBITSHIGH( thumbT_word1, 1, 56);
	// The following bit abcd bit sequences should be padded with ones: 0111, 1010, 1011, 1101, 1110, 1111
	// The following logical expression checks for the presence of any of those:
	bit = (a & c) | (!a & b & c & d) | (a & b & !c & d);
	bits = 0xf*bit;
	PUTBITSHIGH( thumbT_word1, bits,  3, 63);
	PUTBITSHIGH( thumbT_word1, !bit,  1, 58);

	// Set diffbit
	PUTBITSHIGH( thumbT_word1, 0,  1, 33);
	thumbT_word2 = thumbT59_word2;
}

// Tests if there is at least one pixel in the image which would get alpha = 0 in punchtrough mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
bool hasAlpha(uint8* alphaimg, int ix, int iy, int width) 
{
	for(int x=ix; x<ix+4; x++) 
	{
		for(int y=iy; y<iy+4; y++) 
		{
			int index = x+y*width;
			if(alphaimg[index]<128) 
			{
				return true;
			}
		}
	}
	return false;
}

// Compress a block with ETC2 RGB
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockETC2Fast(uint8 *img, uint8* alphaimg, uint8 *imgdec,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2)
{
	unsigned int etc1_word1;
	unsigned int etc1_word2;
	double error_etc1;

	unsigned int planar57_word1;
	unsigned int planar57_word2;
	unsigned int planar_word1;
	unsigned int planar_word2;
	double error_planar;

	unsigned int thumbT59_word1;
	unsigned int thumbT59_word2;
	unsigned int thumbT_word1;
	unsigned int thumbT_word2;
	double error_thumbT;
	
	unsigned int thumbH58_word1;
	unsigned int thumbH58_word2;
	unsigned int thumbH_word1;
	unsigned int thumbH_word2;
	double error_thumbH;

	double error_best;
	signed char best_char;
	int best_mode;
	
	if(format==ETC2PACKAGE_RGBA1_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA1_NO_MIPMAPS)
	{
		/*                if we have one-bit alpha, we never use the individual mode,
		                  instead that bit flags that one of our four offsets will instead
						          mean transparent (with 0 offset for color channels) */

		/*                the regular ETC individual mode is disabled, but the old T, H and planar modes
						          are kept unchanged and may be used for blocks without transparency.
						          Introduced are old ETC with only differential coding,
						          ETC differential but with 3 offsets and transparent,
						          and T-mode with 3 colors plus transparent.*/

		/*                in a fairly hackish manner, error_etc1, etc1_word1 and etc1_word2 will
		                  represent the best out of the three introduced modes, to be compared
						          with the three kept modes in the old code*/

		unsigned int tempword1, tempword2;
		double temperror;
		//try regular differential transparent mode

		int testerr= compressBlockDifferentialWithAlpha(true,img,alphaimg, imgdec,width,height,startx,starty,etc1_word1,etc1_word2);

		uint8* alphadec = new uint8[width*height];
		decompressBlockDifferentialWithAlpha(etc1_word1, etc1_word2, imgdec, alphadec,width, height, startx, starty);
		error_etc1 = calcBlockErrorRGBA(img, imgdec, alphaimg,width, height, startx, starty);
		if(error_etc1!=testerr) 
		{
			printf("testerr: %d, etcerr: %lf\n",testerr,error_etc1);
		}
		//try T-mode with transparencies
		//for now, skip this...
		compressBlockTHUMB59TAlpha(img,alphaimg,width,height,startx,starty,tempword1,tempword2);
		decompressBlockTHUMB59TAlpha(tempword1,tempword2,imgdec, alphadec, width,height,startx,starty);
		temperror=calcBlockErrorRGBA(img, imgdec, alphaimg, width, height, startx, starty);
		if(temperror<error_etc1) 
		{
			error_etc1=temperror;
			stuff59bitsDiffFalse(tempword1,tempword2,etc1_word1,etc1_word2);
		}
		compressBlockTHUMB58HAlpha(img,alphaimg,width,height,startx,starty,tempword1,tempword2);
		decompressBlockTHUMB58HAlpha(tempword1,tempword2,imgdec, alphadec, width,height,startx,starty);
		temperror=calcBlockErrorRGBA(img, imgdec, alphaimg, width, height, startx, starty);
		if(temperror<error_etc1) 
		{
			error_etc1=temperror;
			stuff58bitsDiffFalse(tempword1,tempword2,etc1_word1,etc1_word2);
		}
		//if we have transparency in this pixel, we know that one of these two modes was best..
		if(hasAlpha(alphaimg,startx,starty,width)) 
		{
			compressed1=etc1_word1;
			compressed2=etc1_word2;
			delete[] alphadec;
			return;
		}
		//error_etc1=255*255*1000;
		//otherwise, they MIGHT have been the best, although that's unlikely.. anyway, try old differential mode now
		
		compressBlockDifferentialWithAlpha(false,img,alphaimg,imgdec,width,height,startx,starty,tempword1,tempword2);
		decompressBlockDiffFlip(tempword1, tempword2, imgdec, width, height, startx, starty);
		temperror = calcBlockErrorRGB(img, imgdec, width, height, startx, starty);
		decompressBlockDifferentialWithAlpha(tempword1,tempword2,imgdec,alphadec,width,height,startx,starty);
		if(temperror<error_etc1) 
		{
			error_etc1=temperror;
			etc1_word1=tempword1;
			etc1_word2=tempword2;
		}
		delete[] alphadec;
		//drop out of this if, and test old T, H and planar modes (we have already returned if there are transparent pixels in this block)
	}
	else 
	{
		//this includes individual mode, and therefore doesn't apply in case of punch-through alpha.
		compressBlockDiffFlipFast(img, imgdec, width, height, startx, starty, etc1_word1, etc1_word2);
		decompressBlockDiffFlip(etc1_word1, etc1_word2, imgdec, width, height, startx, starty);
		error_etc1 = calcBlockErrorRGB(img, imgdec, width, height, startx, starty);
	}
	//these modes apply regardless of whether we want punch-through alpha or not.
	//error etc_1 and etc1_word1/etc1_word2 contain previous best candidate.
	compressBlockPlanar57(img, width, height, startx, starty, planar57_word1, planar57_word2);
	decompressBlockPlanar57(planar57_word1, planar57_word2, imgdec, width, height, startx, starty);
	error_planar = calcBlockErrorRGB(img, imgdec, width, height, startx, starty);
	stuff57bits(planar57_word1, planar57_word2, planar_word1, planar_word2);

	compressBlockTHUMB59TFastest(img,width, height, startx, starty, thumbT59_word1, thumbT59_word2);
	decompressBlockTHUMB59T(thumbT59_word1, thumbT59_word2, imgdec, width, height, startx, starty);			
	error_thumbT = calcBlockErrorRGB(img, imgdec, width, height, startx, starty);
	stuff59bits(thumbT59_word1, thumbT59_word2, thumbT_word1, thumbT_word2);

	compressBlockTHUMB58HFastest(img,width,height,startx, starty, thumbH58_word1, thumbH58_word2);
	decompressBlockTHUMB58H(thumbH58_word1, thumbH58_word2, imgdec, width, height, startx, starty);			
	error_thumbH = calcBlockErrorRGB(img, imgdec, width, height, startx, starty);
	stuff58bits(thumbH58_word1, thumbH58_word2, thumbH_word1, thumbH_word2);

	error_best = error_etc1;
	compressed1 = etc1_word1;
	compressed2 = etc1_word2;
	best_char = '.';
	best_mode = MODE_ETC1;

	if(error_planar < error_best)
	{
		compressed1 = planar_word1;
        compressed2 = planar_word2;
		best_char = 'p';
		error_best = error_planar;	
		best_mode = MODE_PLANAR;
	}
	if(error_thumbT < error_best)
	{
		compressed1 = thumbT_word1;
        compressed2 = thumbT_word2;
		best_char = 'T';
		error_best = error_thumbT;
		best_mode = MODE_THUMB_T;
	}
	if(error_thumbH < error_best)
	{
		compressed1 = thumbH_word1;
        compressed2 = thumbH_word2;
		best_char = 'H';
		error_best = error_thumbH;
		best_mode = MODE_THUMB_H;
	}
	
	switch(best_mode)
	{
		// Now see which mode won and compress that a little bit harder
	case MODE_THUMB_T:
		compressBlockTHUMB59TFast(img,width, height, startx, starty, thumbT59_word1, thumbT59_word2);
		decompressBlockTHUMB59T(thumbT59_word1, thumbT59_word2, imgdec, width, height, startx, starty);			
		error_thumbT = calcBlockErrorRGB(img, imgdec, width, height, startx, starty);
		stuff59bits(thumbT59_word1, thumbT59_word2, thumbT_word1, thumbT_word2);
		if(error_thumbT < error_best)
		{
			compressed1 = thumbT_word1;
			compressed2 = thumbT_word2;
		}
		break;
	case MODE_THUMB_H:
		compressBlockTHUMB58HFast(img,width,height,startx, starty, thumbH58_word1, thumbH58_word2);
		decompressBlockTHUMB58H(thumbH58_word1, thumbH58_word2, imgdec, width, height, startx, starty);			
		error_thumbH = calcBlockErrorRGB(img, imgdec, width, height, startx, starty);
		stuff58bits(thumbH58_word1, thumbH58_word2, thumbH_word1, thumbH_word2);
		if(error_thumbH < error_best)
		{
			compressed1 = thumbH_word1;
			compressed2 = thumbH_word2;
		}
		break;
	default:
		break;
	}
}

// Compress an ETC2 RGB block using perceptual error metric
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockETC2FastPerceptual(uint8 *img, uint8 *imgdec,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2)
{
	unsigned int etc1_word1;
	unsigned int etc1_word2;
	double error_etc1;

	unsigned int planar57_word1;
	unsigned int planar57_word2;
	unsigned int planar_word1;
	unsigned int planar_word2;
	double error_planar;

	unsigned int thumbT59_word1;
	unsigned int thumbT59_word2;
	unsigned int thumbT_word1;
	unsigned int thumbT_word2;
	double error_thumbT;
	
	unsigned int thumbH58_word1;
	unsigned int thumbH58_word2;
	unsigned int thumbH_word1;
	unsigned int thumbH_word2;
	double error_thumbH;

	double error_best;
	signed char best_char;
	int best_mode;

	compressBlockDiffFlipFastPerceptual(img, imgdec, width, height, startx, starty, etc1_word1, etc1_word2);
	decompressBlockDiffFlip(etc1_word1, etc1_word2, imgdec, width, height, startx, starty);
	error_etc1 = 1000*calcBlockPerceptualErrorRGB(img, imgdec, width, height, startx, starty);

	compressBlockPlanar57(img, width, height, startx, starty, planar57_word1, planar57_word2);
	decompressBlockPlanar57(planar57_word1, planar57_word2, imgdec, width, height, startx, starty);
	error_planar = 1000*calcBlockPerceptualErrorRGB(img, imgdec, width, height, startx, starty);
	stuff57bits(planar57_word1, planar57_word2, planar_word1, planar_word2);

	compressBlockTHUMB59TFastestPerceptual1000(img,width, height, startx, starty, thumbT59_word1, thumbT59_word2);
	decompressBlockTHUMB59T(thumbT59_word1, thumbT59_word2, imgdec, width, height, startx, starty);			
	error_thumbT = 1000*calcBlockPerceptualErrorRGB(img, imgdec, width, height, startx, starty);
	stuff59bits(thumbT59_word1, thumbT59_word2, thumbT_word1, thumbT_word2);

	compressBlockTHUMB58HFastestPerceptual1000(img,width,height,startx, starty, thumbH58_word1, thumbH58_word2);
	decompressBlockTHUMB58H(thumbH58_word1, thumbH58_word2, imgdec, width, height, startx, starty);			
	error_thumbH = 1000*calcBlockPerceptualErrorRGB(img, imgdec, width, height, startx, starty);
	stuff58bits(thumbH58_word1, thumbH58_word2, thumbH_word1, thumbH_word2);

	error_best = error_etc1;
	compressed1 = etc1_word1;
	compressed2 = etc1_word2;
	best_char = '.';
	best_mode = MODE_ETC1;

	if(error_planar < error_best)
	{
		compressed1 = planar_word1;
		compressed2 = planar_word2;
		best_char = 'p';
		error_best = error_planar;	
		best_mode = MODE_PLANAR;
	}
	if(error_thumbT < error_best)
	{
		compressed1 = thumbT_word1;
		compressed2 = thumbT_word2;
		best_char = 'T';
		error_best = error_thumbT;
		best_mode = MODE_THUMB_T;
	}
	if(error_thumbH < error_best)
	{
		compressed1 = thumbH_word1;
		compressed2 = thumbH_word2;
		best_char = 'H';
		error_best = error_thumbH;
		best_mode = MODE_THUMB_H;
	}
	
	switch(best_mode)
	{
		// Now see which mode won and compress that a little bit harder
	case MODE_THUMB_T:
		compressBlockTHUMB59TFast(img,width, height, startx, starty, thumbT59_word1, thumbT59_word2);
		decompressBlockTHUMB59T(thumbT59_word1, thumbT59_word2, imgdec, width, height, startx, starty);			
		error_thumbT = calcBlockErrorRGB(img, imgdec, width, height, startx, starty);
		stuff59bits(thumbT59_word1, thumbT59_word2, thumbT_word1, thumbT_word2);
		if(error_thumbT < error_best)
		{
			compressed1 = thumbT_word1;
			compressed2 = thumbT_word2;
		}
		break;
	case MODE_THUMB_H:
		compressBlockTHUMB58HFast(img,width,height,startx, starty, thumbH58_word1, thumbH58_word2);
		decompressBlockTHUMB58H(thumbH58_word1, thumbH58_word2, imgdec, width, height, startx, starty);			
		error_thumbH = calcBlockErrorRGB(img, imgdec, width, height, startx, starty);
		stuff58bits(thumbH58_word1, thumbH58_word2, thumbH_word1, thumbH_word2);
		if(error_thumbH < error_best)
		{
			compressed1 = thumbH_word1;
			compressed2 = thumbH_word2;
		}
		break;
	default:
		break;
	}
}

// Write a word in big endian style
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void write_big_endian_2byte_word(unsigned short *blockadr, FILE *f)
{
	uint8 bytes[2];
	unsigned short block;

	block = blockadr[0];

	bytes[0] = (block >> 8) & 0xff;
	bytes[1] = (block >> 0) & 0xff;

	fwrite(&bytes[0],1,1,f);
	fwrite(&bytes[1],1,1,f);
}


// Write a word in big endian style
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void write_big_endian_4byte_word(unsigned int *blockadr, FILE *f)
{
	uint8 bytes[4];
	unsigned int block;

	block = blockadr[0];

	bytes[0] = (block >> 24) & 0xff;
	bytes[1] = (block >> 16) & 0xff;
	bytes[2] = (block >> 8) & 0xff;
	bytes[3] = (block >> 0) & 0xff;

	fwrite(&bytes[0],1,1,f);
	fwrite(&bytes[1],1,1,f);
	fwrite(&bytes[2],1,1,f);
	fwrite(&bytes[3],1,1,f);
}

extern int alphaTable[256][8];
extern int alphaBase[16][4];

// valtab holds precalculated data used for compressing using EAC2.
// Note that valtab is constructed using get16bits11bits, which means
// that it already is expanded to 16 bits.
// Note also that it its contents will depend on the value of formatSigned.
int *valtab;

void setupAlphaTableAndValtab()
{
  setupAlphaTable();

	//fix precomputation table..!
	valtab = new int[1024*512];
    int16 val16;
	int count=0;
	for(int base=0; base<256; base++) 
	{
		for(int tab=0; tab<16; tab++) 
		{
			for(int mul=0; mul<16; mul++) 
			{
				for(int index=0; index<8; index++) 
				{
					if(formatSigned)
					{
						val16=get16bits11signed(base,tab,mul,index);
						valtab[count] = val16 + 256*128;
					}
					else
						valtab[count]=get16bits11bits(base,tab,mul,index);
					count++;
				}
			}
		}
	}
}

// Reads alpha data
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void readAlpha(uint8* &data, int &width, int &height, int &extendedwidth, int &extendedheight) 
{
	//width and height are already known..?
	uint8* tempdata;
	int wantedBitDepth;
	if(format==ETC2PACKAGE_RGBA_NO_MIPMAPS||format==ETC2PACKAGE_RGBA1_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA1_NO_MIPMAPS) 
	{
		wantedBitDepth=8;
	}
	else if(format==ETC2PACKAGE_R_NO_MIPMAPS) 
	{
		wantedBitDepth=16;
	}
	else 
	{
		printf("invalid format for alpha reading!\n");
		exit(1);
	}
	fReadPGM("alpha.pgm",width,height,tempdata,wantedBitDepth);
	extendedwidth=4*((width+3)/4);
	extendedheight=4*((height+3)/4);

	if(width==extendedwidth&&height==extendedheight) 
	{
		data=tempdata;
	}
	else 
	{
		data = (uint8*)malloc(extendedwidth*extendedheight*wantedBitDepth/8);
		uint8 last=0;
		uint8 lastlast=0;
		for(int x=0; x<extendedwidth; x++) 
		{
			for(int y=0; y<extendedheight; y++) 
			{
				if(wantedBitDepth==8) 
				{
					if(x<width&&y<height) 
					{
						last = tempdata[x+y*width];
					}
					data[x+y*extendedwidth]=last;
				}
				else 
				{
					if(x<width&&y<height) 
					{
						last = tempdata[(x+y*width)*2];
						lastlast = tempdata[(x+y*width)*2+1];						
					}
					data[(x+y*extendedwidth)*2]=last;
					data[(x+y*extendedwidth)*2+1]=lastlast;
				}
			}
		}
	}
	if(format==ETC2PACKAGE_RGBA1_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA1_NO_MIPMAPS) 
	{
		for(int x=0; x<extendedwidth; x++) 
		{
			for(int y=0; y<extendedheight; y++) 
			{
				if(data[x+y*extendedwidth]<128)
					data[x+y*extendedwidth]=0;
				else
					data[x+y*extendedwidth]=255;
			}
		}
	}
}


// Compresses the alpha part of a GL_COMPRESSED_RGBA8_ETC2_EAC block.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockAlphaFast(uint8 * data, int ix, int iy, int width, int height, uint8* returnData) 
{
	int alphasum=0;
	int maxdist=-2;
	for(int x=0; x<4; x++) 
	{
		for(int y=0; y<4; y++) 
		{
			alphasum+=data[ix+x+(iy+y)*width];
		}
	}
	int alpha = (int)( ((float)alphasum)/16.0f+0.5f); //average pixel value, used as guess for base value.
	for(int x=0; x<4; x++) 
	{
		for(int y=0; y<4; y++) 
		{
			if(abs(alpha-data[ix+x+(iy+y)*width])>maxdist)
				maxdist=abs(alpha-data[ix+x+(iy+y)*width]); //maximum distance from average
		}
	}
	int approxPos = (maxdist*255)/160-4;  //experimentally derived formula for calculating approximate table position given a max distance from average
	if(approxPos>255)
		approxPos=255;
	int startTable=approxPos-15; //first table to be tested
	if(startTable<0)
		startTable=0;
	int endTable=clamp(approxPos+15);  //last table to be tested

	int bestsum=1000000000;
	int besttable=-3; 
	int bestalpha=128;
	int prevalpha=alpha;

	//main loop: determine best base alpha value and offset table to use for compression
	//try some different alpha tables.
	for(int table = startTable; table<endTable&&bestsum>0; table++)
	{
		int tablealpha=prevalpha;
		int tablebestsum=1000000000;
		//test some different alpha values, trying to find the best one for the given table.	
		for(int alphascale=16; alphascale>0; alphascale/=4) 
		{
			int startalpha;
			int endalpha;
			if(alphascale==16) 
			{
				startalpha = clamp(tablealpha-alphascale*4);
				endalpha = clamp(tablealpha+alphascale*4);
			}
			else 
			{
				startalpha = clamp(tablealpha-alphascale*2);
				endalpha = clamp(tablealpha+alphascale*2);
			}
			for(alpha=startalpha; alpha<=endalpha; alpha+=alphascale) 
			{
				int sum=0;
				int val,diff,bestdiff=10000000,index;
				for(int x=0; x<4; x++) 
				{
					for(int y=0; y<4; y++) 
					{
						//compute best offset here, add square difference to sum..
						val=data[ix+x+(iy+y)*width];
						bestdiff=1000000000;
						//the values are always ordered from small to large, with the first 4 being negative and the last 4 positive
						//search is therefore made in the order 0-1-2-3 or 7-6-5-4, stopping when error increases compared to the previous entry tested.
						if(val>alpha) 
						{ 
							for(index=7; index>3; index--) 
							{
								diff=clamp_table[alpha+(int)(alphaTable[table][index])+255]-val;
								diff*=diff;
								if(diff<=bestdiff) 
								{
									bestdiff=diff;
								}
								else
									break;
							}
						}
						else 
						{
							for(index=0; index<4; index++) 
							{
								diff=clamp_table[alpha+(int)(alphaTable[table][index])+255]-val;
								diff*=diff;
								if(diff<bestdiff) 
								{
									bestdiff=diff;
								}
								else
									break;
							}
						}

						//best diff here is bestdiff, add it to sum!
						sum+=bestdiff;
						//if the sum here is worse than previously best already, there's no use in continuing the count..
						//note that tablebestsum could be used for more precise estimation, but the speedup gained here is deemed more important.
						if(sum>bestsum) 
						{ 
							x=9999; //just to make it large and get out of the x<4 loop
							break;
						}
					}
				}
				if(sum<tablebestsum) 
				{
					tablebestsum=sum;
					tablealpha=alpha;
				}
				if(sum<bestsum) 
				{
					bestsum=sum;
					besttable=table;
					bestalpha=alpha;
			}
		}
		if(alphascale<=2)
			alphascale=0;
		}
	}

	alpha=bestalpha;	

	//"good" alpha value and table are known!
	//store them, then loop through the pixels again and print indices.

	returnData[0]=alpha;
	returnData[1]=besttable;
	for(int pos=2; pos<8; pos++) 
	{
		returnData[pos]=0;
	}
	int byte=2;
	int bit=0;
	for(int x=0; x<4; x++) 
	{
		for(int y=0; y<4; y++) 
		{
			//find correct index
			int besterror=1000000;
			int bestindex=99;
			for(int index=0; index<8; index++) //no clever ordering this time, as this loop is only run once per block anyway
			{ 
				int error= (clamp(alpha +(int)(alphaTable[besttable][index]))-data[ix+x+(iy+y)*width])*(clamp(alpha +(int)(alphaTable[besttable][index]))-data[ix+x+(iy+y)*width]);
				if(error<besterror) 
				{
					besterror=error;
					bestindex=index;
				}
			}
			//best table index has been determined.
			//pack 3-bit index into compressed data, one bit at a time
			for(int numbit=0; numbit<3; numbit++) 
			{
				returnData[byte]|=getbit(bestindex,2-numbit,7-bit);

				bit++;
				if(bit>7) 
				{
					bit=0;
					byte++;
				}
			}
		}
	}
}

// Helper function for the below function
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
int getPremulIndex(int base, int tab, int mul, int index) 
{
	return (base<<11)+(tab<<7)+(mul<<3)+index;
}

// Calculates the error used in compressBlockAlpha16()
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double calcError(uint8* data, int ix, int iy, int width, int height, int base, int tab, int mul, double prevbest) 
{
	int offset = getPremulIndex(base,tab,mul,0);
	double error=0;
	for (int y=0; y<4; y++) 
	{
		for(int x=0; x<4; x++) 
		{
			double besthere = (1<<20);
			besthere*=besthere;
			uint8 byte1 = data[2*(x+ix+(y+iy)*width)];
			uint8 byte2 = data[2*(x+ix+(y+iy)*width)+1];
			int alpha = (byte1<<8)+byte2;
			for(int index=0; index<8; index++) 
			{
				double indexError;
				indexError = alpha-valtab[offset+index];
				indexError*=indexError;
				if(indexError<besthere)
					besthere=indexError;
			}
			error+=besthere;
			if(error>=prevbest)
				return prevbest+(1<<30);
		}
	}
	return error;
}

// compressBlockAlpha16
// 
// Compresses a block using the 11-bit EAC formats.
// Depends on the global variable formatSigned.
// 
// COMPRESSED_R11_EAC (if formatSigned = 0)
// This is an 11-bit unsigned format. Since we do not have a good 11-bit file format, we use 16-bit pgm instead.
// Here we assume that, in the input 16-bit pgm file, 0 represents 0.0 and 65535 represents 1.0. The function compressBlockAlpha16 
// will find the compressed block which best matches the data. In detail, it will find the compressed block, which 
// if decompressed, will generate an 11-bit block that after bit replication to 16-bits will generate the closest 
// block to the original 16-bit pgm block.
// 
// COMPRESSED_SIGNED_R11_EAC (if formatSigned = 1)
// This is an 11-bit signed format. Since we do not have any signed file formats, we use unsigned 16-bit pgm instead.
// Hence we assume that, in the input 16-bit pgm file, 1 represents -1.0, 32768 represents 0.0 and 65535 represents 1.0. 
// The function compresseBlockAlpha16 will find the compressed block, which if decompressed, will generate a signed
// 11-bit block that after bit replication to 16-bits and conversion to unsigned (1 equals -1.0, 32768 equals 0.0 and 
// 65535 equals 1.0) will generate the closest block to the original 16-bit pgm block. 
//
// COMPRESSED_RG11_EAC is compressed by calling the function twice, dito for COMPRESSED_SIGNED_RG11_EAC.
// 
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockAlpha16(uint8* data, int ix, int iy, int width, int height, uint8* returnData) 
{
	unsigned int bestbase, besttable, bestmul;
	double besterror;
	besterror=1<<20;
	besterror*=besterror;
	for(int base=0; base<256; base++) 
	{
		for(int table=0; table<16; table++) 
		{
			for(int mul=0; mul<16; mul++) 
			{
				double e = calcError(data, ix, iy, width, height,base,table,mul,besterror);
				if(e<besterror) 
				{
					bestbase=base;
					besttable=table;
					bestmul=mul;
					besterror=e;
				}
			}
		}
	}
	returnData[0]=bestbase;
	returnData[1]=(bestmul<<4)+besttable;
	if(formatSigned) 
	{
		//if we have a signed format, the base value should be given as a signed byte. 
		signed char signedbase = bestbase-128;
		returnData[0]=*((uint8*)(&signedbase));
	}
	
	for(int i=2; i<8; i++) 
	{
		returnData[i]=0;
	}

	int byte=2;
	int bit=0;
	for (int x=0; x<4; x++) 
	{
		for(int y=0; y<4; y++) 
		{
			double besterror=255*255;
			besterror*=besterror;
			int bestindex=99;
			uint8 byte1 = data[2*(x+ix+(y+iy)*width)];
			uint8 byte2 = data[2*(x+ix+(y+iy)*width)+1];
			int alpha = (byte1<<8)+byte2;
			for(unsigned int index=0; index<8; index++) 
			{
				double indexError;
				if(formatSigned)
				{
					int16 val16;
					int val;
                    val16 = get16bits11signed(bestbase,besttable,bestmul,index);
                    val = val16 + 256*128;
					indexError = alpha-val;
				}
				else
					indexError = alpha-get16bits11bits(bestbase,besttable,bestmul,index);

				indexError*=indexError;
				if(indexError<besterror) 
				{
					besterror=indexError;
					bestindex=index;
				}
			}
			
			for(int numbit=0; numbit<3; numbit++) 
			{
				returnData[byte]|=getbit(bestindex,2-numbit,7-bit);
				bit++;
				if(bit>7) 
				{
					bit=0;
					byte++;
				}
			}
		}
	}
}

// Exhaustive compression of alpha compression in a GL_COMPRESSED_RGB8_ETC2 block
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockAlphaSlow(uint8* data, int ix, int iy, int width, int height, uint8* returnData) 
{
	//determine the best table and base alpha value for this block using MSE
	int alphasum=0;
	int maxdist=-2;
	for(int x=0; x<4; x++) 
	{
		for(int y=0; y<4; y++) 
		{
			alphasum+=data[ix+x+(iy+y)*width];
		}
	}
	int alpha = (int)( ((float)alphasum)/16.0f+0.5f); //average pixel value, used as guess for base value.

	int bestsum=1000000000;
	int besttable=-3; 
	int bestalpha=128;
	int prevalpha=alpha;

	//main loop: determine best base alpha value and offset table to use for compression
	//try some different alpha tables.
	for(int table = 0; table<256&&bestsum>0; table++)
	{
		int tablealpha=prevalpha;
		int tablebestsum=1000000000;
		//test some different alpha values, trying to find the best one for the given table.
		for(int alphascale=32; alphascale>0; alphascale/=8) 
		{
			
			int startalpha = clamp(tablealpha-alphascale*4);
			int endalpha = clamp(tablealpha+alphascale*4);
			
			for(alpha=startalpha; alpha<=endalpha; alpha+=alphascale) {
				int sum=0;
				int val,diff,bestdiff=10000000,index;
				for(int x=0; x<4; x++) 
				{
					for(int y=0; y<4; y++) 
					{
						//compute best offset here, add square difference to sum..
						val=data[ix+x+(iy+y)*width];
						bestdiff=1000000000;
						//the values are always ordered from small to large, with the first 4 being negative and the last 4 positive
						//search is therefore made in the order 0-1-2-3 or 7-6-5-4, stopping when error increases compared to the previous entry tested.
						if(val>alpha) 
						{ 
							for(index=7; index>3; index--) 
							{
								diff=clamp_table[alpha+(alphaTable[table][index])+255]-val;
								diff*=diff;
								if(diff<=bestdiff) 
								{
									bestdiff=diff;
								}
								else
									break;
							}
						}
						else 
						{
							for(index=0; index<5; index++) 
							{
								diff=clamp_table[alpha+(alphaTable[table][index])+255]-val;
								diff*=diff;
								if(diff<bestdiff) 
								{
									bestdiff=diff;
								}
								else
									break;
							}
						}

						//best diff here is bestdiff, add it to sum!
						sum+=bestdiff;
						//if the sum here is worse than previously best already, there's no use in continuing the count..
						if(sum>tablebestsum) 
						{ 
							x=9999; //just to make it large and get out of the x<4 loop
							break;
						}
					}
				}
				if(sum<tablebestsum) 
				{
					tablebestsum=sum;
					tablealpha=alpha;
				}
				if(sum<bestsum) 
				{
					bestsum=sum;
					besttable=table;
					bestalpha=alpha;
				}
			}
			if(alphascale==4)
				alphascale=8;
		}
	}

	alpha=bestalpha;	
	//the best alpha value and table are known!
	//store them, then loop through the pixels again and print indices.
	returnData[0]=alpha;
	returnData[1]=besttable;
	for(int pos=2; pos<8; pos++) 
	{
		returnData[pos]=0;
	}
	int byte=2;
	int bit=0;
	for(int x=0; x<4; x++) 
	{
		for(int y=0; y<4; y++) 
		{
			//find correct index
			int besterror=1000000;
			int bestindex=99;
			for(int index=0; index<8; index++) //no clever ordering this time, as this loop is only run once per block anyway
			{ 
				int error= (clamp(alpha +(int)(alphaTable[besttable][index]))-data[ix+x+(iy+y)*width])*(clamp(alpha +(int)(alphaTable[besttable][index]))-data[ix+x+(iy+y)*width]);
				if(error<besterror) 
				{
					besterror=error;
					bestindex=index;
				}
			}
			//best table index has been determined.
			//pack 3-bit index into compressed data, one bit at a time
			for(int numbit=0; numbit<3; numbit++) 
			{
				returnData[byte]|=getbit(bestindex,2-numbit,7-bit);

				bit++;
				if(bit>7) 
				{
					bit=0;
					byte++;
				}
			}
		}
	}
}

// Calculate weighted PSNR
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double calculateWeightedPSNR(uint8 *lossyimg, uint8 *origimg, int width, int height, double w1, double w2, double w3)
{
	// Note: This calculation of PSNR uses the formula
	//
	// PSNR = 10 * log_10 ( 255^2 / wMSE ) 
	// 
	// where the wMSE is calculated as
	//
	// 1/(N*M) * sum ( ( w1*(R' - R)^2 + w2*(G' - G)^2 + w3*(B' - B)^2) ) 
	//
	// typical weights are  0.299,   0.587,   0.114  for perceptually weighted PSNR and
  //                     1.0/3.0, 1.0/3.0, 1.0/3.0 for nonweighted PSNR

	int x,y;
	double wMSE;
	double PSNR;
	double err;
	wMSE = 0;

	for(y=0;y<height;y++)
	{
		for(x=0;x<width;x++)
		{
			err = lossyimg[y*width*3+x*3+0] - origimg[y*width*3+x*3+0];
		    wMSE = wMSE + (w1*(err * err));
			err = lossyimg[y*width*3+x*3+1] - origimg[y*width*3+x*3+1];
		    wMSE = wMSE + (w2*(err * err));
			err = lossyimg[y*width*3+x*3+2] - origimg[y*width*3+x*3+2];
		    wMSE = wMSE + (w3*(err * err));
		}
	}
	wMSE = wMSE / (width * height);
	if(wMSE == 0)
	{
		printf("********************************************************************\n");
		printf("There is no difference at all between image files --- infinite PSNR.\n");
		printf("********************************************************************\n");
	}
	PSNR = 10*log((1.0*255*255)/wMSE)/log(10.0);
	return PSNR;
}

// Calculate unweighted PSNR (weights are (1,1,1))
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double calculatePSNR(uint8 *lossyimg, uint8 *origimg, int width, int height)
{
	// Note: This calculation of PSNR uses the formula
	//
	// PSNR = 10 * log_10 ( 255^2 / MSE ) 
	// 
	// where the MSE is calculated as
	//
	// 1/(N*M) * sum ( 1/3 * ((R' - R)^2 + (G' - G)^2 + (B' - B)^2) ) 
	//
	// The reason for having the 1/3 factor is the following:
	// Presume we have a grayscale image, that is acutally just the red component 
	// of a color image.. The squared error is then (R' - R)^2.
	// Assume that we have a certain signal to noise ratio, say 30 dB. If we add
	// another two components (say green and blue) with the same signal to noise 
	// ratio, we want the total signal to noise ratio be the same. For the
	// squared error to remain constant we must divide by three after adding
	// together the squared errors of the components. 

  return calculateWeightedPSNR(lossyimg, origimg, width, height, (1.0/3.0), (1.0/3.0), (1.0/3.0));
}

// Decompresses a file
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void uncompressFile(char *srcfile, uint8* &img, uint8 *&alphaimg, int& active_width, int& active_height)
{
	FILE *f;
	int width,height;
	unsigned int block_part1, block_part2;
	uint8 *newimg, *newalphaimg, *alphaimg2;
	unsigned short w, h;
	int xx, yy;
	unsigned char magic[4];
	unsigned char version[2];
	unsigned short texture_type;
	if(f=fopen(srcfile,"rb"))
	{
		// Load table
		readCompressParams();
		if(ktxFile) 
		{
			//read ktx header..
			KTX_header header;
			fread(&header,sizeof(KTX_header),1,f);
			//read size parameter, which we don't actually need..
			unsigned int bitsize;
			fread(&bitsize,sizeof(unsigned int),1,f);
	
			active_width=header.pixelWidth;
			active_height = header.pixelHeight;
			w = ((active_width+3)/4)*4;
			h = ((active_height+3)/4)*4;
			width=w;
			height=h;

			if(header.glInternalFormat==GL_COMPRESSED_SIGNED_R11_EAC) 
			{
				format=ETC2PACKAGE_R_NO_MIPMAPS;
				formatSigned=1;
			}
			else if(header.glInternalFormat==GL_COMPRESSED_R11_EAC) 
			{
				format=ETC2PACKAGE_R_NO_MIPMAPS;
			}
			else if(header.glInternalFormat==GL_COMPRESSED_SIGNED_RG11_EAC) 
			{
				format=ETC2PACKAGE_RG_NO_MIPMAPS;
				formatSigned=1;
			}
			else if(header.glInternalFormat==GL_COMPRESSED_RG11_EAC) 
			{
				format=ETC2PACKAGE_RG_NO_MIPMAPS;
			}
			else if(header.glInternalFormat==GL_COMPRESSED_RGB8_ETC2) 
			{
				format=ETC2PACKAGE_RGB_NO_MIPMAPS;
			}
			else if(header.glInternalFormat==GL_COMPRESSED_SRGB8_ETC2) 
			{
				format=ETC2PACKAGE_sRGB_NO_MIPMAPS;
			}
			else if(header.glInternalFormat==GL_COMPRESSED_RGBA8_ETC2_EAC) 
			{
				format=ETC2PACKAGE_RGBA_NO_MIPMAPS;
			}
			else if(header.glInternalFormat==GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC) 
			{
				format=ETC2PACKAGE_sRGBA_NO_MIPMAPS;
			}
			else if(header.glInternalFormat==GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2) 
			{
				format=ETC2PACKAGE_RGBA1_NO_MIPMAPS;
			}
			else if(header.glInternalFormat==GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2) 
			{
				format=ETC2PACKAGE_sRGBA1_NO_MIPMAPS;
			}
			else if(header.glInternalFormat==GL_ETC1_RGB8_OES) 
			{
				format=ETC1_RGB_NO_MIPMAPS;
				codec=CODEC_ETC;
			}
			else 
			{
				printf("ktx file has unknown glInternalFormat (not etc compressed)!\n");
				exit(1);
			}
		}
		else 
		{
			// Read magic nunmber
			fread(&magic[0], sizeof(unsigned char), 1, f);
			fread(&magic[1], sizeof(unsigned char), 1, f);
			fread(&magic[2], sizeof(unsigned char), 1, f);
			fread(&magic[3], sizeof(unsigned char), 1, f);
			if(!(magic[0] == 'P' && magic[1] == 'K' && magic[2] == 'M' && magic[3] == ' '))
			{
				printf("\n\n The file %s is not a .pkm file.\n",srcfile);
				exit(1);
			}
		
			// Read version
			fread(&version[0], sizeof(unsigned char), 1, f);
			fread(&version[1], sizeof(unsigned char), 1, f);
			if( version[0] == '1' && version[1] == '0' )
			{

				// Read texture type
				read_big_endian_2byte_word(&texture_type, f);
				if(!(texture_type == ETC1_RGB_NO_MIPMAPS))
				{
					printf("\n\n The file %s (of version %c.%c) does not contain a texture of known format.\n", srcfile, version[0],version[1]);
					printf("Known formats: ETC1_RGB_NO_MIPMAPS.\n", srcfile);
					exit(1);
				}
			}
			else if( version[0] == '2' && version[1] == '0' )
			{
				// Read texture type
				read_big_endian_2byte_word(&texture_type, f);
				if(texture_type==ETC2PACKAGE_RG_SIGNED_NO_MIPMAPS) 
				{
					texture_type=ETC2PACKAGE_RG_NO_MIPMAPS;
					formatSigned=1;
					//printf("Decompressing 2-channel signed data\n");
				}
				if(texture_type==ETC2PACKAGE_R_SIGNED_NO_MIPMAPS) 
				{
					texture_type=ETC2PACKAGE_R_NO_MIPMAPS;
					formatSigned=1;
					//printf("Decompressing 1-channel signed data\n");
				}
        if(texture_type==ETC2PACKAGE_sRGB_NO_MIPMAPS)
        {
          // The SRGB formats are decoded just as RGB formats -- use RGB format for decompression.
          texture_type=ETC2PACKAGE_RGB_NO_MIPMAPS;
        }
        if(texture_type==ETC2PACKAGE_sRGBA_NO_MIPMAPS)
        {
          // The SRGB formats are decoded just as RGB formats -- use RGB format for decompression.
          texture_type=ETC2PACKAGE_RGBA_NO_MIPMAPS;
        }
        if(texture_type==ETC2PACKAGE_sRGBA1_NO_MIPMAPS)
        {
          // The SRGB formats are decoded just as RGB formats -- use RGB format for decompression.
          texture_type=ETC2PACKAGE_sRGBA1_NO_MIPMAPS;
        }
				if(texture_type==ETC2PACKAGE_RGBA_NO_MIPMAPS_OLD) 
				{
					printf("\n\nThe file %s contains a compressed texture created using an old version of ETCPACK.\n",srcfile);
					printf("decompression is not supported in this version.\n");
					exit(1);
				}
				if(!(texture_type==ETC2PACKAGE_RGB_NO_MIPMAPS||texture_type==ETC2PACKAGE_sRGB_NO_MIPMAPS||texture_type==ETC2PACKAGE_RGBA_NO_MIPMAPS||texture_type==ETC2PACKAGE_sRGBA_NO_MIPMAPS||texture_type==ETC2PACKAGE_R_NO_MIPMAPS||texture_type==ETC2PACKAGE_RG_NO_MIPMAPS||texture_type==ETC2PACKAGE_RGBA1_NO_MIPMAPS||texture_type==ETC2PACKAGE_sRGBA1_NO_MIPMAPS))
				{
					printf("\n\n The file %s does not contain a texture of known format.\n", srcfile);
					printf("Known formats: ETC2PACKAGE_RGB_NO_MIPMAPS.\n", srcfile);
					exit(1);
				}
			}
			else
			{
				printf("\n\n The file %s is not of version 1.0 or 2.0 but of version %c.%c.\n",srcfile, version[0], version[1]);
				printf("Aborting.\n");
				exit(1);
			}
			format=texture_type;
			printf("textype: %d\n",texture_type);
			// ETC2 is backwards compatible, which means that an ETC2-capable decompressor can also handle
			// old ETC1 textures without any problems. Thus a version 1.0 file with ETC1_RGB_NO_MIPMAPS and a 
			// version 2.0 file with ETC2PACKAGE_RGB_NO_MIPMAPS can be handled by the same ETC2-capable decompressor

			// Read how many pixels the blocks make up

			read_big_endian_2byte_word(&w, f);
			read_big_endian_2byte_word(&h, f);
			width = w;
			height = h;

			// Read how many pixels contain active data (the rest are just
			// for making sure we have a 4*a x 4*b size).

			read_big_endian_2byte_word(&w, f);
			read_big_endian_2byte_word(&h, f);
			active_width = w;
			active_height = h;
		}
		printf("Width = %d, Height = %d\n",width, height);
		printf("active pixel area: top left %d x %d area.\n",active_width, active_height);

		if(format==ETC2PACKAGE_RG_NO_MIPMAPS)
			img=(uint8*)malloc(3*width*height*2);
		else
			img=(uint8*)malloc(3*width*height);
		if(!img)
		{
			printf("Error: could not allocate memory\n");
			exit(0);
		}
		if(format==ETC2PACKAGE_RGBA_NO_MIPMAPS||format==ETC2PACKAGE_R_NO_MIPMAPS||format==ETC2PACKAGE_RG_NO_MIPMAPS||format==ETC2PACKAGE_RGBA1_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA1_NO_MIPMAPS)
		{
			//printf("alpha channel decompression\n");
			alphaimg=(uint8*)malloc(width*height*2);
			setupAlphaTableAndValtab();
			if(!alphaimg)
			{
				printf("Error: could not allocate memory for alpha\n");
				exit(0);
			}
		}
		if(format==ETC2PACKAGE_RG_NO_MIPMAPS) 
		{
			alphaimg2=(uint8*)malloc(width*height*2);
			if(!alphaimg2)
			{
				printf("Error: could not allocate memory\n");
				exit(0);
			}
		}

		for(int y=0;y<height/4;y++)
		{
			for(int x=0;x<width/4;x++)
			{
				//decode alpha channel for RGBA
				if(format==ETC2PACKAGE_RGBA_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA_NO_MIPMAPS) 
				{
					uint8 alphablock[8];
					fread(alphablock,1,8,f);
					decompressBlockAlpha(alphablock,alphaimg,width,height,4*x,4*y);
				}
				//color channels for most normal modes
				if(format!=ETC2PACKAGE_R_NO_MIPMAPS&&format!=ETC2PACKAGE_RG_NO_MIPMAPS) 
				{
					//we have normal ETC2 color channels, decompress these
					read_big_endian_4byte_word(&block_part1,f);
					read_big_endian_4byte_word(&block_part2,f);
					if(format==ETC2PACKAGE_RGBA1_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA1_NO_MIPMAPS)
						decompressBlockETC21BitAlpha(block_part1, block_part2,img,alphaimg,width,height,4*x,4*y);
					else
						decompressBlockETC2(block_part1, block_part2,img,width,height,4*x,4*y);		
				}
				//one or two 11-bit alpha channels for R or RG.
				if(format==ETC2PACKAGE_R_NO_MIPMAPS||format==ETC2PACKAGE_RG_NO_MIPMAPS) 
				{
					uint8 alphablock[8];
					fread(alphablock,1,8,f);
					decompressBlockAlpha16bit(alphablock,alphaimg,width,height,4*x,4*y);
				}
				if(format==ETC2PACKAGE_RG_NO_MIPMAPS) 
				{
					uint8 alphablock[8];
					fread(alphablock,1,8,f);
					decompressBlockAlpha16bit(alphablock,alphaimg2,width,height,4*x,4*y);
				}
			}
		}
		if(format==ETC2PACKAGE_RG_NO_MIPMAPS) 
		{
			for(int y=0;y<height;y++)
			{
				for(int x=0;x<width;x++)
				{
					img[6*(y*width+x)]=alphaimg[2*(y*width+x)];
					img[6*(y*width+x)+1]=alphaimg[2*(y*width+x)+1];
					img[6*(y*width+x)+2]=alphaimg2[2*(y*width+x)];
					img[6*(y*width+x)+3]=alphaimg2[2*(y*width+x)+1];
					img[6*(y*width+x)+4]=0;
					img[6*(y*width+x)+5]=0;
				}
			}
		}

		// Ok, and now only write out the active pixels to the .ppm file.
		// (But only if the active pixels differ from the total pixels)

		if( !(height == active_height && width == active_width) )
		{
			if(format==ETC2PACKAGE_RG_NO_MIPMAPS)
				newimg=(uint8*)malloc(3*active_width*active_height*2);
			else
				newimg=(uint8*)malloc(3*active_width*active_height);
			
			if(format==ETC2PACKAGE_RGBA_NO_MIPMAPS||format==ETC2PACKAGE_RGBA1_NO_MIPMAPS||format==ETC2PACKAGE_R_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA1_NO_MIPMAPS)
			{
				newalphaimg = (uint8*)malloc(active_width*active_height*2);
			}

			if(!newimg)
			{
				printf("Error: could not allocate memory\n");
				exit(0);
			}
			
			// Convert from total area to active area:

			for(yy = 0; yy<active_height; yy++)
			{
				for(xx = 0; xx< active_width; xx++)
				{
					if(format!=ETC2PACKAGE_R_NO_MIPMAPS&&format!=ETC2PACKAGE_RG_NO_MIPMAPS) 
					{
						newimg[ (yy*active_width)*3 + xx*3 + 0 ] = img[ (yy*width)*3 + xx*3 + 0];
						newimg[ (yy*active_width)*3 + xx*3 + 1 ] = img[ (yy*width)*3 + xx*3 + 1];
						newimg[ (yy*active_width)*3 + xx*3 + 2 ] = img[ (yy*width)*3 + xx*3 + 2];
					}
					else if(format==ETC2PACKAGE_RG_NO_MIPMAPS) 
					{
						newimg[ (yy*active_width)*6 + xx*6 + 0 ] = img[ (yy*width)*6 + xx*6 + 0];
						newimg[ (yy*active_width)*6 + xx*6 + 1 ] = img[ (yy*width)*6 + xx*6 + 1];
						newimg[ (yy*active_width)*6 + xx*6 + 2 ] = img[ (yy*width)*6 + xx*6 + 2];
						newimg[ (yy*active_width)*6 + xx*6 + 3 ] = img[ (yy*width)*6 + xx*6 + 3];
						newimg[ (yy*active_width)*6 + xx*6 + 4 ] = img[ (yy*width)*6 + xx*6 + 4];
						newimg[ (yy*active_width)*6 + xx*6 + 5 ] = img[ (yy*width)*6 + xx*6 + 5];
					}
					if(format==ETC2PACKAGE_R_NO_MIPMAPS) 
					{
						newalphaimg[ ((yy*active_width) + xx)*2]   = alphaimg[2*((yy*width) + xx)];
						newalphaimg[ ((yy*active_width) + xx)*2+1] = alphaimg[2*((yy*width) + xx)+1];
					}
					if(format==ETC2PACKAGE_RGBA_NO_MIPMAPS||format==ETC2PACKAGE_RGBA1_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA1_NO_MIPMAPS) 
					{
						newalphaimg[ ((yy*active_width) + xx)]   = alphaimg[((yy*width) + xx)];
					}
				}
			}

			free(img);
			img = newimg;
			if(format==ETC2PACKAGE_RGBA_NO_MIPMAPS||format==ETC2PACKAGE_RGBA1_NO_MIPMAPS||format==ETC2PACKAGE_R_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA1_NO_MIPMAPS)
			{
				free(alphaimg);
				alphaimg=newalphaimg;
			}
			if(format==ETC2PACKAGE_RG_NO_MIPMAPS) 
			{
				free(alphaimg);
				free(alphaimg2);
        alphaimg = NULL;
        alphaimg2 = NULL;
			}
		}
	}
	else
  {
		printf("Error: could not open <%s>.\n",srcfile);
    exit(1);
  }
	height=active_height;
	width=active_width;
	fclose(f);
}

// Writes output file 
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void writeOutputFile(char *dstfile, uint8* img, uint8* alphaimg, int width, int height) 
{
	char str[300];

	if(format!=ETC2PACKAGE_R_NO_MIPMAPS&&format!=ETC2PACKAGE_RG_NO_MIPMAPS) 
	{
		fWritePPM("tmp.ppm",width,height,img,8,false);
		printf("Saved file tmp.ppm \n\n");
	}
	else if(format==ETC2PACKAGE_RG_NO_MIPMAPS) 
	{
		fWritePPM("tmp.ppm",width,height,img,16,false);
	}
	if(format==ETC2PACKAGE_RGBA_NO_MIPMAPS||format==ETC2PACKAGE_RGBA1_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA1_NO_MIPMAPS)
		fWritePGM("alphaout.pgm",width,height,alphaimg,false,8);
	if(format==ETC2PACKAGE_R_NO_MIPMAPS)
		fWritePGM("alphaout.pgm",width,height,alphaimg,false,16);

	// Delete destination file if it exists
	if(fileExist(dstfile))
	{
		sprintf(str, "del %s\n",dstfile);	
		system(str);
	}

	int q = find_pos_of_extension(dstfile);
	if(!strcmp(&dstfile[q],".ppm")&&format!=ETC2PACKAGE_R_NO_MIPMAPS) 
	{
		// Already a .ppm file. Just rename. 
		sprintf(str,"move tmp.ppm %s\n",dstfile);
		printf("Renaming destination file to %s\n",dstfile);
	}
	else
	{
		// Converting from .ppm to other file format
		// 
		// Use your favorite command line image converter program,
		// for instance Image Magick. Just make sure the syntax can
		// be written as below:
		// 
		// C:\magick convert source.ppm dest.jpg
		//
		if(format==ETC2PACKAGE_RGBA_NO_MIPMAPS||format==ETC2PACKAGE_RGBA1_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA1_NO_MIPMAPS) 
		{
            // Somewhere after version 6.7.1-2 of ImageMagick the following command gives the wrong result due to a bug. 
			// sprintf(str,"composite -compose CopyOpacity alphaout.pgm tmp.ppm %s\n",dstfile);
            // Instead we read the file and write a tga.

			printf("Converting destination file from .ppm/.pgm to %s with alpha\n",dstfile);
            int rw, rh;
            unsigned char *pixelsRGB;
            unsigned char *pixelsA;
			fReadPPM("tmp.ppm", rw, rh, pixelsRGB, 8);
            fReadPGM("alphaout.pgm", rw, rh, pixelsA, 8);
			fWriteTGAfromRGBandA(dstfile, rw, rh, pixelsRGB, pixelsA, true);
            free(pixelsRGB);
            free(pixelsA);
            sprintf(str,""); // Nothing to execute.
		}
		else if(format==ETC2PACKAGE_R_NO_MIPMAPS) 
		{
			sprintf(str,"magick convert alphaout.pgm %s\n",dstfile);
			printf("Converting destination file from .pgm to %s\n",dstfile);
		}
		else 
		{
			sprintf(str,"magick convert tmp.ppm %s\n",dstfile);
			printf("Converting destination file from .ppm to %s\n",dstfile);
		}
	}
	// Execute system call
	system(str);
	
	free(img);
	if(alphaimg!=NULL)
		free(alphaimg);
}

// Calculates the PSNR between two files
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double calculatePSNRfile(char *srcfile, uint8 *origimg, uint8* origalpha)
{
	uint8 *alphaimg, *img;
	int active_width, active_height;
	uncompressFile(srcfile,img,alphaimg,active_width,active_height);

	// calculate Mean Square Error (MSE)
	double MSER=0,MSEG=0,MSEB=0,MSEA, PSNRR,PSNRG,PSNRA;
	double MSE;
	double wMSE;
	double PSNR=0;
	double wPSNR;
	double err;
	MSE = 0;
	MSEA=0;
	wMSE = 0;
	int width=((active_width+3)/4)*4;
	int height=((active_height+3)/4)*4;
	int numpixels = 0;
	for(int y=0;y<active_height;y++)
	{
		for(int x=0;x<active_width;x++)
		{
			if(format!=ETC2PACKAGE_R_NO_MIPMAPS&&format!=ETC2PACKAGE_RG_NO_MIPMAPS) 
			{
				//we have regular color channels..
				if((format != ETC2PACKAGE_RGBA1_NO_MIPMAPS && format != ETC2PACKAGE_sRGBA1_NO_MIPMAPS) || alphaimg[y*width + x] > 0)
				{
					err = img[y*active_width*3+x*3+0] - origimg[y*width*3+x*3+0];
					MSE  += ((err * err)/3.0);
					wMSE += PERCEPTUAL_WEIGHT_R_SQUARED * (err*err);
					err = img[y*active_width*3+x*3+1] - origimg[y*width*3+x*3+1];
					MSE  += ((err * err)/3.0);
					wMSE += PERCEPTUAL_WEIGHT_G_SQUARED * (err*err);
					err = img[y*active_width*3+x*3+2] - origimg[y*width*3+x*3+2];
					MSE  += ((err * err)/3.0);
					wMSE += PERCEPTUAL_WEIGHT_B_SQUARED * (err*err);
					numpixels++;
				}
			}
			else if(format==ETC2PACKAGE_RG_NO_MIPMAPS) 
			{
				int rorig = (origimg[6*(y*width+x)+0]<<8)+origimg[6*(y*width+x)+1];
				int rnew =  (    img[6*(y*active_width+x)+0]<<8)+    img[6*(y*active_width+x)+1];
				int gorig = (origimg[6*(y*width+x)+2]<<8)+origimg[6*(y*width+x)+3];
				int gnew =  (    img[6*(y*active_width+x)+2]<<8)+    img[6*(y*active_width+x)+3];
				err=rorig-rnew;
				MSER+=(err*err);
				err=gorig-gnew;
				MSEG+=(err*err);
			}
			else if(format==ETC2PACKAGE_R_NO_MIPMAPS) 
			{
				int aorig = (((int)origalpha[2*(y*width+x)+0])<<8)+origalpha[2*(y*width+x)+1];
				int anew =  (((int)alphaimg[2*(y*active_width+x)+0])<<8)+alphaimg[2*(y*active_width+x)+1];
				err=aorig-anew;
				MSEA+=(err*err);
			}
		}
	}
	if(format == ETC2PACKAGE_RGBA1_NO_MIPMAPS || format == ETC2PACKAGE_sRGBA1_NO_MIPMAPS)
	{
		MSE = MSE / (1.0 * numpixels);
		wMSE = wMSE / (1.0 * numpixels);
		PSNR = 10*log((1.0*255*255)/MSE)/log(10.0);
		wPSNR = 10*log((1.0*255*255)/wMSE)/log(10.0);
		printf("PSNR only calculated on pixels where compressed alpha > 0\n");
		printf("color PSNR: %lf\nweighted PSNR: %lf\n",PSNR,wPSNR);
	}
	else if(format!=ETC2PACKAGE_R_NO_MIPMAPS&&format!=ETC2PACKAGE_RG_NO_MIPMAPS) 
	{
		MSE = MSE / (active_width * active_height);
		wMSE = wMSE / (active_width * active_height);
		PSNR = 10*log((1.0*255*255)/MSE)/log(10.0);
		wPSNR = 10*log((1.0*255*255)/wMSE)/log(10.0);
		if(format == ETC2PACKAGE_RGBA_NO_MIPMAPS || format == ETC2PACKAGE_sRGBA_NO_MIPMAPS)
			printf("PSNR only calculated on RGB, not on alpha\n");
		printf("color PSNR: %lf\nweighted PSNR: %lf\n",PSNR,wPSNR);
	}
	else if(format==ETC2PACKAGE_RG_NO_MIPMAPS) 
	{
		MSER = MSER / (active_width * active_height);
		MSEG = MSEG / (active_width * active_height);
		PSNRR = 10*log((1.0*65535*65535)/MSER)/log(10.0);
		PSNRG = 10*log((1.0*65535*65535)/MSEG)/log(10.0);
		printf("red PSNR: %lf\ngreen PSNR: %lf\n",PSNRR,PSNRG);
	}
	else if(format==ETC2PACKAGE_R_NO_MIPMAPS) 
	{
		MSEA = MSEA / (active_width * active_height);
		PSNRA = 10*log((1.0*65535.0*65535.0)/MSEA)/log(10.0);
		printf("PSNR: %lf\n",PSNRA);
	}
	free(img);
	return PSNR;
}

//// Exhaustive code starts here.

#if EXHAUSTIVE_CODE_ACTIVE
// Precomutes a table that is used when compressing a block exhaustively
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
inline unsigned int precompute_3bittable_all_subblocksRG_withtest_perceptual1000(uint8 *block,uint8 *avg_color, unsigned int *precalc_err_UL_R, unsigned int *precalc_err_UR_R, unsigned int *precalc_err_LL_R, unsigned int *precalc_err_LR_R,unsigned int *precalc_err_UL_RG, unsigned int *precalc_err_UR_RG, unsigned int *precalc_err_LL_RG, unsigned int *precalc_err_LR_RG, unsigned int best_err)
{
	int table;
	int index;
	int orig[3],approx[3][4];
	int x;
	int intensity_modifier;
	const int *table_indices;

	int good_enough_to_test;
	unsigned int err[4];
	unsigned int err_this_table_upper;
	unsigned int err_this_table_lower;
	unsigned int err_this_table_left;
	unsigned int err_this_table_right;

	// If the error in the red and green component is already larger than best_err for all 8 tables in 
	// all of upper, lower, left and right, this combination of red and green will never be used in 
	// the optimal color configuration. Therefore we can avoid testing all the blue colors for this 
	// combination. 
	good_enough_to_test = false;	

	for(table=0;table<8;table++)		// try all the 8 tables. 
	{
		table_indices = &compressParamsFast[table*4];

		intensity_modifier = table_indices[0];
		approx[1][0]=CLAMP(0, avg_color[1]+intensity_modifier,255);
		intensity_modifier = table_indices[1];
		approx[1][1]=CLAMP(0, avg_color[1]+intensity_modifier,255);
		intensity_modifier = table_indices[2];
		approx[1][2]=CLAMP(0, avg_color[1]+intensity_modifier,255);
		intensity_modifier = table_indices[3];
		approx[1][3]=CLAMP(0, avg_color[1]+intensity_modifier,255);

		err_this_table_upper = 0;
		err_this_table_lower = 0;
		err_this_table_left = 0;
		err_this_table_right = 0;
		for(x=0; x<4; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];
			for(index=0;index<4;index++)
			{
				err[index] = precalc_err_UL_R[table*4*4+x*4+index] 
					+ PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000 * SQUARE(approx[1][index]-orig[1]);
				precalc_err_UL_RG[table*4*4+x*4+index] = err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_upper+=err[0];
			err_this_table_left+=err[0];
		}
		for(x=4; x<8; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];
			for(index=0;index<4;index++)
			{
				err[index] = precalc_err_UR_R[table*4*4+(x-4)*4+index] 
				  + PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000 * SQUARE(approx[1][index]-orig[1]);
				precalc_err_UR_RG[table*4*4+(x-4)*4+index] = err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_upper+=err[0];
			err_this_table_right+=err[0];
		}
		for(x=8; x<12; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];

			for(index=0;index<4;index++)
			{
				err[index] = precalc_err_LL_R[table*4*4+(x-8)*4+index]
					+ PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000 * SQUARE(approx[1][index]-orig[1]);
				precalc_err_LL_RG[table*4*4+(x-8)*4+index] = err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_lower+=err[0];
			err_this_table_left+=err[0];
		}
		for(x=12; x<16; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];

			for(index=0;index<4;index++)
			{
				err[index] = precalc_err_LR_R[table*4*4+(x-12)*4+index]
					+ PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000 * SQUARE(approx[1][index]-orig[1]);
				precalc_err_LR_RG[table*4*4+(x-12)*4+index] = err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_lower+=err[0];
			err_this_table_right+=err[0];
		}
		if(err_this_table_upper < best_err)
			good_enough_to_test = true;
		if(err_this_table_lower < best_err)
			good_enough_to_test = true;
		if(err_this_table_left < best_err)
			good_enough_to_test = true;
		if(err_this_table_right < best_err)
			good_enough_to_test = true;
	}
	return good_enough_to_test;
} 
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precomutes a table that is used when compressing a block exhaustively
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
inline int precompute_3bittable_all_subblocksRG_withtest(uint8 *block,uint8 *avg_color, unsigned int *precalc_err_UL_R, unsigned int *precalc_err_UR_R, unsigned int *precalc_err_LL_R, unsigned int *precalc_err_LR_R,unsigned int *precalc_err_UL_RG, unsigned int *precalc_err_UR_RG, unsigned int *precalc_err_LL_RG, unsigned int *precalc_err_LR_RG, unsigned int best_err)
{
	int table;
	int index;
	int orig[3],approx[3][4];
	int x;
	int intensity_modifier;
	const int *table_indices;

	int good_enough_to_test;
	unsigned int err[4];
	unsigned int err_this_table_upper;
	unsigned int err_this_table_lower;
	unsigned int err_this_table_left;
	unsigned int err_this_table_right;

	// If the error in the red and green component is already larger than best_err for all 8 tables in 
	// all of upper, lower, left and right, this combination of red and green will never be used in 
	// the optimal color configuration. Therefore we can avoid testing all the blue colors for this 
	// combination. 
	good_enough_to_test = false;	

	for(table=0;table<8;table++)		// try all the 8 tables. 
	{
		table_indices = &compressParamsFast[table*4];

		intensity_modifier = table_indices[0];
		approx[1][0]=CLAMP(0, avg_color[1]+intensity_modifier,255);
		intensity_modifier = table_indices[1];
		approx[1][1]=CLAMP(0, avg_color[1]+intensity_modifier,255);
		intensity_modifier = table_indices[2];
		approx[1][2]=CLAMP(0, avg_color[1]+intensity_modifier,255);
		intensity_modifier = table_indices[3];
		approx[1][3]=CLAMP(0, avg_color[1]+intensity_modifier,255);

		err_this_table_upper = 0;
		err_this_table_lower = 0;
		err_this_table_left = 0;
		err_this_table_right = 0;
		for(x=0; x<4; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];
			for(index=0;index<4;index++)
			{
				err[index] = precalc_err_UL_R[table*4*4+x*4+index]+SQUARE(approx[1][index]-orig[1]);
				precalc_err_UL_RG[table*4*4+x*4+index] = err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_upper+=err[0];
			err_this_table_left+=err[0];
		}
		for(x=4; x<8; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];
			for(index=0;index<4;index++)
			{
				err[index] = precalc_err_UR_R[table*4*4+(x-4)*4+index]+SQUARE(approx[1][index]-orig[1]);
				precalc_err_UR_RG[table*4*4+(x-4)*4+index] = err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_upper+=err[0];
			err_this_table_right+=err[0];
		}
		for(x=8; x<12; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];

			for(index=0;index<4;index++)
			{
				err[index] = precalc_err_LL_R[table*4*4+(x-8)*4+index]+SQUARE(approx[1][index]-orig[1]);
				precalc_err_LL_RG[table*4*4+(x-8)*4+index] = err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_lower+=err[0];
			err_this_table_left+=err[0];
		}
		for(x=12; x<16; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];

			for(index=0;index<4;index++)
			{
				err[index] = precalc_err_LR_R[table*4*4+(x-12)*4+index]+SQUARE(approx[1][index]-orig[1]);
				precalc_err_LR_RG[table*4*4+(x-12)*4+index] = err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_lower+=err[0];
			err_this_table_right+=err[0];
		}
		if(err_this_table_upper < best_err)
			good_enough_to_test = true;
		if(err_this_table_lower < best_err)
			good_enough_to_test = true;
		if(err_this_table_left < best_err)
			good_enough_to_test = true;
		if(err_this_table_right < best_err)
			good_enough_to_test = true;
	}
	return good_enough_to_test;
} 
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precomutes a table that is used when compressing a block exhaustively
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
inline unsigned int precompute_3bittable_all_subblocksR_with_test_perceptual1000(uint8 *block,uint8 *avg_color, unsigned int *precalc_err_UL_R, unsigned int *precalc_err_UR_R, unsigned int *precalc_err_LL_R, unsigned int *precalc_err_LR_R, unsigned int best_err)
{
	int table;
	int index;
	int orig[3],approx[3][4];
	int x;
	int intensity_modifier;
	const int *table_indices;

	unsigned int err[4];
	unsigned int err_this_table_upper;
	unsigned int err_this_table_lower;
	unsigned int err_this_table_left;
	unsigned int err_this_table_right;

	int good_enough_to_test;

	good_enough_to_test = false;

	for(table=0;table<8;table++)		// try all the 8 tables. 
	{
		err_this_table_upper = 0;
		err_this_table_lower = 0;
		err_this_table_left = 0;
		err_this_table_right = 0;

		table_indices = &compressParamsFast[table*4];

		intensity_modifier = table_indices[0];
		approx[0][0]=CLAMP(0, avg_color[0]+intensity_modifier,255);
		intensity_modifier = table_indices[1];
		approx[0][1]=CLAMP(0, avg_color[0]+intensity_modifier,255);
		intensity_modifier = table_indices[2];
		approx[0][2]=CLAMP(0, avg_color[0]+intensity_modifier,255);
		intensity_modifier = table_indices[3];
		approx[0][3]=CLAMP(0, avg_color[0]+intensity_modifier,255);

		for(x=0; x<4; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];
			for(index=0;index<4;index++)
			{
				err[index]=PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(approx[0][index]-orig[0]);
				precalc_err_UL_R[table*4*4+x*4+index]=err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_upper+=err[0];
			err_this_table_left+=err[0];
		}
		for(x=4; x<8; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];
			for(index=0;index<4;index++)
			{
				err[index]=PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(approx[0][index]-orig[0]);
				precalc_err_UR_R[table*4*4+(x-4)*4+index]=err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_upper+=err[0];
			err_this_table_right+=err[0];
		}
		for(x=8; x<12; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];

			for(index=0;index<4;index++)
			{
				err[index]=PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(approx[0][index]-orig[0]);
				precalc_err_LL_R[table*4*4+(x-8)*4+index]=err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_lower+=err[0];
			err_this_table_left+=err[0];
			 
		}
		for(x=12; x<16; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];

			for(index=0;index<4;index++)
			{
				err[index]=PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(approx[0][index]-orig[0]);
				precalc_err_LR_R[table*4*4+(x-12)*4+index]=err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_lower+=err[0];
			err_this_table_right+=err[0];
		}
		if(err_this_table_upper < best_err)
			good_enough_to_test = true;
		if(err_this_table_lower < best_err)
			good_enough_to_test = true;
		if(err_this_table_left < best_err)
			good_enough_to_test = true;
		if(err_this_table_right < best_err)
			good_enough_to_test = true;
	}
	return good_enough_to_test;
} 
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precomutes a table that is used when compressing a block exhaustively
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
inline int precompute_3bittable_all_subblocksR_with_test(uint8 *block,uint8 *avg_color, unsigned int *precalc_err_UL_R, unsigned int *precalc_err_UR_R, unsigned int *precalc_err_LL_R, unsigned int *precalc_err_LR_R, unsigned int best_err)
{
	int table;
	int index;
	int orig[3],approx[3][4];
	int x;
	int intensity_modifier;
	const int *table_indices;

	unsigned int err[4];
	unsigned int err_this_table_upper;
	unsigned int err_this_table_lower;
	unsigned int err_this_table_left;
	unsigned int err_this_table_right;

	int good_enough_to_test;

	good_enough_to_test = false;

	for(table=0;table<8;table++)		// try all the 8 tables. 
	{
		err_this_table_upper = 0;
		err_this_table_lower = 0;
		err_this_table_left = 0;
		err_this_table_right = 0;

		table_indices = &compressParamsFast[table*4];

		intensity_modifier = table_indices[0];
		approx[0][0]=CLAMP(0, avg_color[0]+intensity_modifier,255);
		intensity_modifier = table_indices[1];
		approx[0][1]=CLAMP(0, avg_color[0]+intensity_modifier,255);
		intensity_modifier = table_indices[2];
		approx[0][2]=CLAMP(0, avg_color[0]+intensity_modifier,255);
		intensity_modifier = table_indices[3];
		approx[0][3]=CLAMP(0, avg_color[0]+intensity_modifier,255);

		for(x=0; x<4; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];
			for(index=0;index<4;index++)
			{
				err[index]=SQUARE(approx[0][index]-orig[0]);
				precalc_err_UL_R[table*4*4+x*4+index]=err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_upper+=err[0];
			err_this_table_left+=err[0];
		}
		for(x=4; x<8; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];
			for(index=0;index<4;index++)
			{
				err[index]=SQUARE(approx[0][index]-orig[0]);
				precalc_err_UR_R[table*4*4+(x-4)*4+index]=err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_upper+=err[0];
			err_this_table_right+=err[0];
		}
		for(x=8; x<12; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];

			for(index=0;index<4;index++)
			{
				err[index]=SQUARE(approx[0][index]-orig[0]);
				precalc_err_LL_R[table*4*4+(x-8)*4+index]=err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_lower+=err[0];
			err_this_table_left+=err[0];
			 
		}
		for(x=12; x<16; x++)
		{
			orig[0]=block[x*4];
			orig[1]=block[x*4+1];
			orig[2]=block[x*4+2];

			for(index=0;index<4;index++)
			{
				err[index]=SQUARE(approx[0][index]-orig[0]);
				precalc_err_LR_R[table*4*4+(x-12)*4+index]=err[index];
			}
			if(err[0] > err[1])
				err[0] = err[1];
			if(err[2] > err[3])
				err[2] = err[3];
			if(err[0] > err[2])
				err[0] = err[2];
			err_this_table_lower+=err[0];
			err_this_table_right+=err[0];
		}
		if(err_this_table_upper < best_err)
			good_enough_to_test = true;
		if(err_this_table_lower < best_err)
			good_enough_to_test = true;
		if(err_this_table_left < best_err)
			good_enough_to_test = true;
		if(err_this_table_right < best_err)
			good_enough_to_test = true;
	}
	return good_enough_to_test;
} 
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Tries all index-tables, used when compressing a block exhaustively
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
inline void tryalltables_3bittable_all_subblocks_using_precalc(uint8 *block_2x2,uint8 *color_quant1, unsigned int *precalc_err_UL_RG, unsigned int *precalc_err_UR_RG, unsigned int *precalc_err_LL_RG, unsigned int *precalc_err_LR_RG, unsigned int &err_upper, unsigned int &err_lower, unsigned int &err_left, unsigned int &err_right, unsigned int best_err)
{
	unsigned int err_this_table_upper;
	unsigned int err_this_table_lower;
	unsigned int err_this_table_left;
	unsigned int err_this_table_right;
	int orig[3],approx[4];
	int err[4];
	err_upper = 3*255*255*16;	
	err_lower = 3*255*255*16;	
	err_left = 3*255*255*16;	
	err_right = 3*255*255*16;	

#define ONE_PIXEL_UL(table_nbr,xx)\
			orig[0]=block_2x2[xx*4];\
			orig[1]=block_2x2[xx*4+1];\
			orig[2]=block_2x2[xx*4+2];\
			/* unrolled loop for(index=0;index<4;index++)*/\
				err[0]=precalc_err_UL_RG[table_nbr*4*4+xx*4+0] + square_table[approx[0]-orig[2]];\
				err[1]=precalc_err_UL_RG[table_nbr*4*4+xx*4+1] + square_table[approx[1]-orig[2]];\
				err[2]=precalc_err_UL_RG[table_nbr*4*4+xx*4+2] + square_table[approx[2]-orig[2]];\
				err[3]=precalc_err_UL_RG[table_nbr*4*4+xx*4+3] + square_table[approx[3]-orig[2]];\
			/* end unrolled loop*/\
			if(err[0] > err[1])\
				err[0] = err[1];\
			if(err[2] > err[3])\
				err[2] = err[3];\
			if(err[0] > err[2])\
				err[0] = err[2];\
			err_this_table_upper+=err[0];\
			err_this_table_left+=err[0];\

#define ONE_PIXEL_UR(table_nbr,xx)\
			orig[0]=block_2x2[xx*4];\
			orig[1]=block_2x2[xx*4+1];\
			orig[2]=block_2x2[xx*4+2];\
			/* unrolled loop for(index=0;index<4;index++)*/\
				err[0]=precalc_err_UR_RG[table_nbr*4*4+(xx-4)*4+0] + square_table[approx[0]-orig[2]];\
 				err[1]=precalc_err_UR_RG[table_nbr*4*4+(xx-4)*4+1] + square_table[approx[1]-orig[2]];\
 				err[2]=precalc_err_UR_RG[table_nbr*4*4+(xx-4)*4+2] + square_table[approx[2]-orig[2]];\
 				err[3]=precalc_err_UR_RG[table_nbr*4*4+(xx-4)*4+3] + square_table[approx[3]-orig[2]];\
			/* end unrolled loop */\
 			if(err[0] > err[1])\
 				err[0] = err[1];\
 			if(err[2] > err[3])\
 				err[2] = err[3];\
 			if(err[0] > err[2])\
 				err[0] = err[2];\
 			err_this_table_upper+=err[0];\
 			err_this_table_right+=err[0];

#define ONE_PIXEL_LL(table_nbr,xx)\
			orig[0]=block_2x2[xx*4];\
			orig[1]=block_2x2[xx*4+1];\
			orig[2]=block_2x2[xx*4+2];\
			/* unrolled loop for(index=0;index<4;index++)*/\
				err[0]=precalc_err_LL_RG[table_nbr*4*4+(xx-8)*4+0] + square_table[approx[0]-orig[2]];\
				err[1]=precalc_err_LL_RG[table_nbr*4*4+(xx-8)*4+1] + square_table[approx[1]-orig[2]];\
				err[2]=precalc_err_LL_RG[table_nbr*4*4+(xx-8)*4+2] + square_table[approx[2]-orig[2]];\
				err[3]=precalc_err_LL_RG[table_nbr*4*4+(xx-8)*4+3] + square_table[approx[3]-orig[2]];\
			/* end unrolled loop*/\
		 	if(err[0] > err[1])\
				err[0] = err[1];\
			if(err[2] > err[3])\
				err[2] = err[3];\
			if(err[0] > err[2])\
				err[0] = err[2];\
			err_this_table_lower+=err[0];\
			err_this_table_left+=err[0];\

#define ONE_PIXEL_LR(table_nbr,xx)\
			orig[0]=block_2x2[xx*4];\
			orig[1]=block_2x2[xx*4+1];\
			orig[2]=block_2x2[xx*4+2];\
			/* unrolled loop for(index=0;index<4;index++)*/\
				err[0]=precalc_err_LR_RG[table_nbr*4*4+(xx-12)*4+0] + square_table[approx[0]-orig[2]];\
				err[1]=precalc_err_LR_RG[table_nbr*4*4+(xx-12)*4+1] + square_table[approx[1]-orig[2]];\
				err[2]=precalc_err_LR_RG[table_nbr*4*4+(xx-12)*4+2] + square_table[approx[2]-orig[2]];\
				err[3]=precalc_err_LR_RG[table_nbr*4*4+(xx-12)*4+3] + square_table[approx[3]-orig[2]];\
			/* end unrolled loop*/\
			if(err[0] > err[1])\
				err[0] = err[1];\
			if(err[2] > err[3])\
				err[2] = err[3];\
			if(err[0] > err[2])\
				err[0] = err[2];\
			err_this_table_lower+=err[0];\
			err_this_table_right+=err[0];\

#define ONE_TABLE_3(table_nbr)\
		err_this_table_upper = 0;\
		err_this_table_lower = 0;\
		err_this_table_left = 0;\
		err_this_table_right = 0;\
		approx[0]=clamp_table_plus_255[color_quant1[2]+compressParamsFast[table_nbr*4+0]+255];\
		approx[1]=clamp_table_plus_255[color_quant1[2]+compressParamsFast[table_nbr*4+1]+255];\
		approx[2]=clamp_table_plus_255[color_quant1[2]+compressParamsFast[table_nbr*4+2]+255];\
		approx[3]=clamp_table_plus_255[color_quant1[2]+compressParamsFast[table_nbr*4+3]+255];\
		/* unroll loop for(xx=0; xx<4; xx++) */\
			ONE_PIXEL_UL(table_nbr,0)\
			ONE_PIXEL_UL(table_nbr,1)\
			ONE_PIXEL_UL(table_nbr,2)\
			ONE_PIXEL_UL(table_nbr,3)\
		/* end unroll loop */\
		/* unroll loop for(xx=4; xx<8; xx++) */\
			ONE_PIXEL_LR(table_nbr,12)\
			ONE_PIXEL_LR(table_nbr,13)\
			ONE_PIXEL_LR(table_nbr,14)\
			ONE_PIXEL_LR(table_nbr,15)\
		/* end unroll loop */\
		/* If error in the top left 2x2 pixel area is already larger than the best error, and */\
		/* The same is true for the bottom right 2x2 pixel area, this combination of table and color */\
		/* can never be part of an optimal solution and therefore we do not need to test the other */\
		/* two 2x2 pixel areas */\
		if((err_this_table_upper<best_err)||(err_this_table_lower<best_err))\
		{\
			/* unroll loop for(xx=4; xx<8; xx++) */\
 				ONE_PIXEL_UR(table_nbr,4)\
 				ONE_PIXEL_UR(table_nbr,5)\
 				ONE_PIXEL_UR(table_nbr,6)\
 				ONE_PIXEL_UR(table_nbr,7)\
			/* end unroll loop */\
			/* unroll loop for(xx=4; xx<8; xx++) */\
				ONE_PIXEL_LL(table_nbr,8)\
				ONE_PIXEL_LL(table_nbr,9)\
				ONE_PIXEL_LL(table_nbr,10)\
				ONE_PIXEL_LL(table_nbr,11)\
			/* end unroll loop */\
			if(err_this_table_upper<err_upper)\
				err_upper = err_this_table_upper;\
			if(err_this_table_lower<err_lower)\
				err_lower = err_this_table_lower;\
			if(err_this_table_left<err_left)\
				err_left = err_this_table_left;\
			if(err_this_table_right<err_right)\
				err_right = err_this_table_right;\
		}\

	/*unroll loop for(table_nbr=0;table_nbr<8;table_nbr++)*/
		ONE_TABLE_3(0);
		ONE_TABLE_3(1);
		ONE_TABLE_3(2);
		ONE_TABLE_3(3);
		ONE_TABLE_3(4);
		ONE_TABLE_3(5);
		ONE_TABLE_3(6);
		ONE_TABLE_3(7);
	/*end unroll loop*/
} 
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Tries all index-tables, used when compressing a block exhaustively using perceptual error measure
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
inline void tryalltables_3bittable_all_subblocks_using_precalc_perceptual1000(uint8 *block_2x2,uint8 *color_quant1, unsigned int *precalc_err_UL_RG, unsigned int *precalc_err_UR_RG, unsigned int *precalc_err_LL_RG, unsigned int *precalc_err_LR_RG, unsigned int &err_upper, unsigned int &err_lower, unsigned int &err_left, unsigned int &err_right, unsigned int best_err)
{
	unsigned int err_this_table_upper;
	unsigned int err_this_table_lower;
	unsigned int err_this_table_left;
	unsigned int err_this_table_right;
	int orig[3],approx[4];
	int err[4];
	err_upper = MAXERR1000;	
	err_lower = MAXERR1000;	
	err_left = MAXERR1000;	
	err_right =MAXERR1000;	

#define ONE_PIXEL_UL_PERCEP(table_nbr,xx)\
			orig[0]=block_2x2[xx*4];\
			orig[1]=block_2x2[xx*4+1];\
			orig[2]=block_2x2[xx*4+2];\
			/* unrolled loop for(index=0;index<4;index++)*/\
				err[0]=precalc_err_UL_RG[table_nbr*4*4+xx*4+0] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[0]-orig[2]];\
				err[1]=precalc_err_UL_RG[table_nbr*4*4+xx*4+1] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[1]-orig[2]];\
				err[2]=precalc_err_UL_RG[table_nbr*4*4+xx*4+2] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[2]-orig[2]];\
				err[3]=precalc_err_UL_RG[table_nbr*4*4+xx*4+3] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[3]-orig[2]];\
			/* end unrolled loop*/\
			if(err[0] > err[1])\
				err[0] = err[1];\
			if(err[2] > err[3])\
				err[2] = err[3];\
			if(err[0] > err[2])\
				err[0] = err[2];\
			err_this_table_upper+=err[0];\
			err_this_table_left+=err[0];\

#define ONE_PIXEL_UR_PERCEP(table_nbr,xx)\
			orig[0]=block_2x2[xx*4];\
			orig[1]=block_2x2[xx*4+1];\
			orig[2]=block_2x2[xx*4+2];\
			/* unrolled loop for(index=0;index<4;index++)*/\
				err[0]=precalc_err_UR_RG[table_nbr*4*4+(xx-4)*4+0] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[0]-orig[2]];\
 				err[1]=precalc_err_UR_RG[table_nbr*4*4+(xx-4)*4+1] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[1]-orig[2]];\
 				err[2]=precalc_err_UR_RG[table_nbr*4*4+(xx-4)*4+2] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[2]-orig[2]];\
 				err[3]=precalc_err_UR_RG[table_nbr*4*4+(xx-4)*4+3] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[3]-orig[2]];\
			/* end unrolled loop */\
 			if(err[0] > err[1])\
 				err[0] = err[1];\
 			if(err[2] > err[3])\
 				err[2] = err[3];\
 			if(err[0] > err[2])\
 				err[0] = err[2];\
 			err_this_table_upper+=err[0];\
 			err_this_table_right+=err[0];

#define ONE_PIXEL_LL_PERCEP(table_nbr,xx)\
			orig[0]=block_2x2[xx*4];\
			orig[1]=block_2x2[xx*4+1];\
			orig[2]=block_2x2[xx*4+2];\
			/* unrolled loop for(index=0;index<4;index++)*/\
				err[0]=precalc_err_LL_RG[table_nbr*4*4+(xx-8)*4+0] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[0]-orig[2]];\
				err[1]=precalc_err_LL_RG[table_nbr*4*4+(xx-8)*4+1] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[1]-orig[2]];\
				err[2]=precalc_err_LL_RG[table_nbr*4*4+(xx-8)*4+2] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[2]-orig[2]];\
				err[3]=precalc_err_LL_RG[table_nbr*4*4+(xx-8)*4+3] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[3]-orig[2]];\
			/* end unrolled loop*/\
		 	if(err[0] > err[1])\
				err[0] = err[1];\
			if(err[2] > err[3])\
				err[2] = err[3];\
			if(err[0] > err[2])\
				err[0] = err[2];\
			err_this_table_lower+=err[0];\
			err_this_table_left+=err[0];\

#define ONE_PIXEL_LR_PERCEP(table_nbr,xx)\
			orig[0]=block_2x2[xx*4];\
			orig[1]=block_2x2[xx*4+1];\
			orig[2]=block_2x2[xx*4+2];\
			/* unrolled loop for(index=0;index<4;index++)*/\
				err[0]=precalc_err_LR_RG[table_nbr*4*4+(xx-12)*4+0] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[0]-orig[2]];\
				err[1]=precalc_err_LR_RG[table_nbr*4*4+(xx-12)*4+1] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[1]-orig[2]];\
				err[2]=precalc_err_LR_RG[table_nbr*4*4+(xx-12)*4+2] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[2]-orig[2]];\
				err[3]=precalc_err_LR_RG[table_nbr*4*4+(xx-12)*4+3] + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[approx[3]-orig[2]];\
			/* end unrolled loop*/\
			if(err[0] > err[1])\
				err[0] = err[1];\
			if(err[2] > err[3])\
				err[2] = err[3];\
			if(err[0] > err[2])\
				err[0] = err[2];\
			err_this_table_lower+=err[0];\
			err_this_table_right+=err[0];\

#define ONE_TABLE_3_PERCEP(table_nbr)\
		err_this_table_upper = 0;\
		err_this_table_lower = 0;\
		err_this_table_left = 0;\
		err_this_table_right = 0;\
		approx[0]=clamp_table_plus_255[color_quant1[2]+compressParamsFast[table_nbr*4+0]+255];\
		approx[1]=clamp_table_plus_255[color_quant1[2]+compressParamsFast[table_nbr*4+1]+255];\
		approx[2]=clamp_table_plus_255[color_quant1[2]+compressParamsFast[table_nbr*4+2]+255];\
		approx[3]=clamp_table_plus_255[color_quant1[2]+compressParamsFast[table_nbr*4+3]+255];\
		/* unroll loop for(xx=0; xx<4; xx++) */\
			ONE_PIXEL_UL_PERCEP(table_nbr,0)\
			ONE_PIXEL_UL_PERCEP(table_nbr,1)\
			ONE_PIXEL_UL_PERCEP(table_nbr,2)\
			ONE_PIXEL_UL_PERCEP(table_nbr,3)\
		/* end unroll loop */\
		/* unroll loop for(xx=4; xx<8; xx++) */\
			ONE_PIXEL_LR_PERCEP(table_nbr,12)\
			ONE_PIXEL_LR_PERCEP(table_nbr,13)\
			ONE_PIXEL_LR_PERCEP(table_nbr,14)\
			ONE_PIXEL_LR_PERCEP(table_nbr,15)\
		/* end unroll loop */\
		/* If error in the top left 2x2 pixel area is already larger than the best error, and */\
		/* The same is true for the bottom right 2x2 pixel area, this combination of table and color */\
		/* can never be part of an optimal solution and therefore we do not need to test the other */\
		/* two 2x2 pixel areas */\
		if((err_this_table_upper<best_err)||(err_this_table_lower<best_err))\
		{\
			/* unroll loop for(xx=4; xx<8; xx++) */\
 				ONE_PIXEL_UR_PERCEP(table_nbr,4)\
 				ONE_PIXEL_UR_PERCEP(table_nbr,5)\
 				ONE_PIXEL_UR_PERCEP(table_nbr,6)\
 				ONE_PIXEL_UR_PERCEP(table_nbr,7)\
			/* end unroll loop */\
			/* unroll loop for(xx=4; xx<8; xx++) */\
				ONE_PIXEL_LL_PERCEP(table_nbr,8)\
				ONE_PIXEL_LL_PERCEP(table_nbr,9)\
				ONE_PIXEL_LL_PERCEP(table_nbr,10)\
				ONE_PIXEL_LL_PERCEP(table_nbr,11)\
			/* end unroll loop */\
			if(err_this_table_upper<err_upper)\
				err_upper = err_this_table_upper;\
			if(err_this_table_lower<err_lower)\
				err_lower = err_this_table_lower;\
			if(err_this_table_left<err_left)\
				err_left = err_this_table_left;\
			if(err_this_table_right<err_right)\
				err_right = err_this_table_right;\
		}\

	/*unroll loop for(table_nbr=0;table_nbr<8;table_nbr++)*/
		ONE_TABLE_3_PERCEP(0);
		ONE_TABLE_3_PERCEP(1);
		ONE_TABLE_3_PERCEP(2);
		ONE_TABLE_3_PERCEP(3);
		ONE_TABLE_3_PERCEP(4);
		ONE_TABLE_3_PERCEP(5);
		ONE_TABLE_3_PERCEP(6);
		ONE_TABLE_3_PERCEP(7);
	/*end unroll loop*/
} 
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Compresses the individual mode exhaustively (perecptual error metric).
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int compressBlockIndividualExhaustivePerceptual(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2, unsigned int total_best_err)
{
	unsigned int best_err_norm_diff = MAXERR1000; 
	unsigned int best_err_norm_444 = MAXERR1000; 
	unsigned int best_err_flip_diff = MAXERR1000; 
	unsigned int best_err_flip_444 = MAXERR1000; 
	uint8 color_quant1[3], color_quant2[3];

	int enc_color1[3];
	int best_enc_color1[3], best_enc_color2[3];
	
	int min_error=MAXERR1000; 
	unsigned int best_pixel_indices1_MSB=0;
	unsigned int best_pixel_indices1_LSB=0;
	unsigned int best_pixel_indices2_MSB=0;
	unsigned int best_pixel_indices2_LSB=0;
	unsigned int pixel_indices1_MSB=0;
	unsigned int pixel_indices1_LSB=0;
	unsigned int pixel_indices2_MSB=0;

	unsigned int err_upper, err_lower;
	unsigned int err_left, err_right;

	unsigned int pixel_indices2_LSB=0;

	unsigned int best_err_upper = MAXERR1000; 
	unsigned int best_err_lower = MAXERR1000; 
	unsigned int best_err_left = MAXERR1000; 
	unsigned int best_err_right = MAXERR1000; 

	int best_upper_col[3];
	int best_lower_col[3];
	int best_left_col[3];
	int best_right_col[3];


	unsigned int table1=0, table2=0;
	unsigned int best_table1=0, best_table2=0;

	unsigned int precalc_err_UL_R[8*4*4];
	unsigned int precalc_err_UR_R[8*4*4];
	unsigned int precalc_err_LL_R[8*4*4];
	unsigned int precalc_err_LR_R[8*4*4];

	unsigned int precalc_err_UL_RG[8*4*4];
	unsigned int precalc_err_UR_RG[8*4*4];
	unsigned int precalc_err_LL_RG[8*4*4];
	unsigned int precalc_err_LR_RG[8*4*4];

	int diffbit;
	uint8 block_2x2[4*4*4];

	unsigned int best_err;
	int best_flip;

	int xx,yy,count = 0;
	// Reshuffle pixels so that the top left 2x2 pixels arrive first, then the top right 2x2 pixels etc. Also put use 4 bytes per pixel to make it 32-word aligned.
	for(xx = 0; xx<2; xx++)
	{
		for(yy=0; yy<2; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}
	for(xx = 2; xx<4; xx++)
	{
		for(yy=0; yy<2; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}
	for(xx = 0; xx<2; xx++)
	{
		for(yy=2; yy<4; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}
	for(xx = 2; xx<4; xx++)
	{
		for(yy=2; yy<4; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}

	unsigned int test1, test2;
	best_err = (unsigned int)compressBlockOnlyIndividualAveragePerceptual1000(img, width, height, startx, starty, test1, test2, best_enc_color1, best_enc_color2, best_flip, best_err_upper, best_err_lower, best_err_left, best_err_right, best_upper_col, best_lower_col, best_left_col, best_right_col);
	if(best_err < total_best_err)
		total_best_err = best_err;

	unsigned int tryblocks = 0;
	unsigned int allblocks = 0;
	int needtest;


	for(enc_color1[0]=0; enc_color1[0]<16; enc_color1[0]++)
	{
		color_quant1[0] = enc_color1[0] << 4 | (enc_color1[0]);
		if(precompute_3bittable_all_subblocksR_with_test_perceptual1000(block_2x2, color_quant1, precalc_err_UL_R, precalc_err_UR_R, precalc_err_LL_R, precalc_err_LR_R, total_best_err))
		{
			for(enc_color1[1]=0; enc_color1[1]<16; enc_color1[1]++)
			{
				color_quant1[1] = enc_color1[1] << 4 | (enc_color1[1]);
				if(precompute_3bittable_all_subblocksRG_withtest_perceptual1000(block_2x2, color_quant1, precalc_err_UL_R, precalc_err_UR_R, precalc_err_LL_R, precalc_err_LR_R, precalc_err_UL_RG, precalc_err_UR_RG, precalc_err_LL_RG, precalc_err_LR_RG, total_best_err))
				{
					needtest = false;
					for(enc_color1[2]=0; enc_color1[2]<16; enc_color1[2]++)
					{
 						color_quant1[2] = enc_color1[2] << 4 | (enc_color1[2]);
						tryalltables_3bittable_all_subblocks_using_precalc_perceptual1000(block_2x2, color_quant1, precalc_err_UL_RG, precalc_err_UR_RG, precalc_err_LL_RG, precalc_err_LR_RG, err_upper, err_lower, err_left, err_right, total_best_err);
						if(err_upper<best_err_upper)
						{
							best_err_upper = err_upper;
							best_upper_col[0] = enc_color1[0];
							best_upper_col[1] = enc_color1[1];
							best_upper_col[2] = enc_color1[2];
							needtest = true;
						}
						if(err_lower<best_err_lower)
						{
							best_err_lower = err_lower;
							best_lower_col[0] = enc_color1[0];
							best_lower_col[1] = enc_color1[1];
							best_lower_col[2] = enc_color1[2];
							needtest=true;
						}
						if(err_left<best_err_left)
						{
							best_err_left = err_left;
							best_left_col[0] = enc_color1[0];
							best_left_col[1] = enc_color1[1];
							best_left_col[2] = enc_color1[2];
							needtest=true;
						}
						if(err_right<best_err_right)
						{
							best_err_right = err_right;
							best_right_col[0] = enc_color1[0];
							best_right_col[1] = enc_color1[1];
							best_right_col[2] = enc_color1[2];
							needtest = true;
						}
					}
					if(needtest)
					{
						if(best_err_upper+best_err_lower < best_err_left+best_err_right)
						{
							best_err = best_err_upper+best_err_lower;
							if(best_err < total_best_err)
								total_best_err = best_err;
						}
						else
						{
							best_err = best_err_left+best_err_right;
							if(best_err < total_best_err)
								total_best_err = best_err;
						}
					}
				}
			}
		}
	}
	
	if(best_err_upper+best_err_lower < best_err_left+best_err_right)
	{
		best_flip = 1;
		best_enc_color1[0] = best_upper_col[0];
		best_enc_color1[1] = best_upper_col[1];
		best_enc_color1[2] = best_upper_col[2];
		best_enc_color2[0] = best_lower_col[0];
		best_enc_color2[1] = best_lower_col[1];
		best_enc_color2[2] = best_lower_col[2];
		best_err = best_err_upper+best_err_lower;
		if(best_err < total_best_err)
			total_best_err = best_err;
	}
	else
	{
		best_flip = 0;
		best_enc_color1[0] = best_left_col[0];
		best_enc_color1[1] = best_left_col[1];
		best_enc_color1[2] = best_left_col[2];
		best_enc_color2[0] = best_right_col[0];
		best_enc_color2[1] = best_right_col[1];
		best_enc_color2[2] = best_right_col[2];
		best_err = best_err_left+best_err_right;
		if(best_err < total_best_err)
			total_best_err = best_err;
	}

	color_quant1[0] = best_enc_color1[0] << 4 | (best_enc_color1[0]);
	color_quant1[1] = best_enc_color1[1] << 4 | (best_enc_color1[1]);
	color_quant1[2] = best_enc_color1[2] << 4 | (best_enc_color1[2]);
	if(best_flip == 0)
		tryalltables_3bittable2x4percep1000(img,width,height,startx,starty,color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
	else
		tryalltables_3bittable4x2percep1000(img,width,height,startx,starty,color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);

	color_quant2[0] = best_enc_color2[0] << 4 | (best_enc_color2[0]);
	color_quant2[1] = best_enc_color2[1] << 4 | (best_enc_color2[1]);
	color_quant2[2] = best_enc_color2[2] << 4 | (best_enc_color2[2]);
	if(best_flip == 0)
		tryalltables_3bittable2x4percep1000(img,width,height,startx+2,starty,color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);
	else
		tryalltables_3bittable4x2percep1000(img,width,height,startx,starty+2,color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

	//     ETC1_RGB8_OES:
	// 
	//     a) bit layout in bits 63 through 32 if diffbit = 0
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
	//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------
	//     
	//     b) bit layout in bits 63 through 32 if diffbit = 1
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |diff|flip|
	//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------
	// 
	//     c) bit layout in bits 31 through 0 (in both cases)
	// 
	//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3   2   1  0
	//      --------------------------------------------------------------------------------------------------
	//     |       most significant pixel index bits       |         least significant pixel index bits       |  
	//     | p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a| p| o| n| m| l| k| j| i| h| g| f| e| d| c | b | a |
	//      --------------------------------------------------------------------------------------------------      


	diffbit = 1;
	compressed1 = 0;
	PUTBITSHIGH( compressed1, diffbit,		      0, 33);
 	PUTBITSHIGH( compressed1, best_enc_color1[0], 4, 63);
 	PUTBITSHIGH( compressed1, best_enc_color1[1], 4, 55);
 	PUTBITSHIGH( compressed1, best_enc_color1[2], 4, 47);
 	PUTBITSHIGH( compressed1, best_enc_color2[0], 4, 59);
 	PUTBITSHIGH( compressed1, best_enc_color2[1], 4, 51);
 	PUTBITSHIGH( compressed1, best_enc_color2[2], 4, 43);
 	PUTBITSHIGH( compressed1, best_table1,	      3, 39);
 	PUTBITSHIGH( compressed1, best_table2,	      3, 36);
 	PUTBITSHIGH( compressed1, best_flip,		  1, 32);

	if(best_flip == 0)
	{
		compressed2 = 0;
		PUTBITS( compressed2, (best_pixel_indices1_MSB     ), 8, 23);
		PUTBITS( compressed2, (best_pixel_indices2_MSB     ), 8, 31);
		PUTBITS( compressed2, (best_pixel_indices1_LSB     ), 8, 7);
		PUTBITS( compressed2, (best_pixel_indices2_LSB     ), 8, 15);
	}
	else
	{
		best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
		best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);		
		compressed2 = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);
	}

	return best_err;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Compresses the individual mode exhaustively.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int compressBlockIndividualExhaustive(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2, unsigned int total_best_err)
{
	unsigned int best_err_norm_diff = 255*255*16*3;
	unsigned int best_err_norm_444 = 255*255*16*3;
	unsigned int best_err_flip_diff = 255*255*16*3;
	unsigned int best_err_flip_444 = 255*255*16*3;
	uint8 color_quant1[3], color_quant2[3];

	int enc_color1[3];
	int best_enc_color1[3], best_enc_color2[3];
	
	int min_error=255*255*8*3;
	unsigned int best_pixel_indices1_MSB=0;
	unsigned int best_pixel_indices1_LSB=0;
	unsigned int best_pixel_indices2_MSB=0;
	unsigned int best_pixel_indices2_LSB=0;
	unsigned int pixel_indices1_MSB=0;
	unsigned int pixel_indices1_LSB=0;
	unsigned int pixel_indices2_MSB=0;

	unsigned int err_upper, err_lower;
	unsigned int err_left, err_right;

	unsigned int pixel_indices2_LSB=0;

	unsigned int best_err_upper = 255*255*16*3;
	unsigned int best_err_lower = 255*255*16*3;
	unsigned int best_err_left = 255*255*16*3;
	unsigned int best_err_right = 255*255*16*3;

	int best_upper_col[3];
	int best_lower_col[3];
	int best_left_col[3];
	int best_right_col[3];


	unsigned int table1=0, table2=0;
	unsigned int best_table1=0, best_table2=0;

	unsigned int precalc_err_UL_R[8*4*4];
	unsigned int precalc_err_UR_R[8*4*4];
	unsigned int precalc_err_LL_R[8*4*4];
	unsigned int precalc_err_LR_R[8*4*4];

	unsigned int precalc_err_UL_RG[8*4*4];
	unsigned int precalc_err_UR_RG[8*4*4];
	unsigned int precalc_err_LL_RG[8*4*4];
	unsigned int precalc_err_LR_RG[8*4*4];

	int diffbit;
	uint8 block_2x2[4*4*4];

	unsigned int best_err;
	int best_flip;

	int xx,yy,count = 0;
	// Reshuffle pixels so that the top left 2x2 pixels arrive first, then the top right 2x2 pixels etc. Also put use 4 bytes per pixel to make it 32-word aligned.
	for(xx = 0; xx<2; xx++)
	{
		for(yy=0; yy<2; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}
	for(xx = 2; xx<4; xx++)
	{
		for(yy=0; yy<2; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}
	for(xx = 0; xx<2; xx++)
	{
		for(yy=2; yy<4; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}
	for(xx = 2; xx<4; xx++)
	{
		for(yy=2; yy<4; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}

 	unsigned int test1, test2;
	best_err = (unsigned int)compressBlockOnlyIndividualAverage(img, width, height, startx, starty, test1, test2, best_enc_color1, best_enc_color2, best_flip, best_err_upper, best_err_lower, best_err_left, best_err_right, best_upper_col, best_lower_col, best_left_col, best_right_col);

	if(best_err < total_best_err)
		total_best_err = best_err;


	unsigned int tryblocks = 0;
	unsigned int allblocks = 0;
	int needtest;

	for(enc_color1[0]=0; enc_color1[0]<16; enc_color1[0]++)
	{
		color_quant1[0] = enc_color1[0] << 4 | (enc_color1[0]);
		if(precompute_3bittable_all_subblocksR_with_test(block_2x2, color_quant1, precalc_err_UL_R, precalc_err_UR_R, precalc_err_LL_R, precalc_err_LR_R, total_best_err))
		{
			for(enc_color1[1]=0; enc_color1[1]<16; enc_color1[1]++)
			{
				color_quant1[1] = enc_color1[1] << 4 | (enc_color1[1]);
				if(precompute_3bittable_all_subblocksRG_withtest(block_2x2, color_quant1, precalc_err_UL_R, precalc_err_UR_R, precalc_err_LL_R, precalc_err_LR_R, precalc_err_UL_RG, precalc_err_UR_RG, precalc_err_LL_RG, precalc_err_LR_RG, total_best_err))
				{
					needtest = false;
					for(enc_color1[2]=0; enc_color1[2]<16; enc_color1[2]++)
					{
 						color_quant1[2] = enc_color1[2] << 4 | (enc_color1[2]);
						tryalltables_3bittable_all_subblocks_using_precalc(block_2x2, color_quant1, precalc_err_UL_RG, precalc_err_UR_RG, precalc_err_LL_RG, precalc_err_LR_RG, err_upper, err_lower, err_left, err_right, total_best_err);
						if(err_upper<best_err_upper)
						{
							best_err_upper = err_upper;
							best_upper_col[0] = enc_color1[0];
							best_upper_col[1] = enc_color1[1];
							best_upper_col[2] = enc_color1[2];
							needtest = true;
						}
						if(err_lower<best_err_lower)
						{
							best_err_lower = err_lower;
							best_lower_col[0] = enc_color1[0];
							best_lower_col[1] = enc_color1[1];
							best_lower_col[2] = enc_color1[2];
							needtest=true;
						}
						if(err_left<best_err_left)
						{
							best_err_left = err_left;
							best_left_col[0] = enc_color1[0];
							best_left_col[1] = enc_color1[1];
							best_left_col[2] = enc_color1[2];
							needtest=true;
						}
						if(err_right<best_err_right)
						{
							best_err_right = err_right;
							best_right_col[0] = enc_color1[0];
							best_right_col[1] = enc_color1[1];
							best_right_col[2] = enc_color1[2];
							needtest = true;
						}
					}
					if(needtest)
					{
						if(best_err_upper+best_err_lower < best_err_left+best_err_right)
						{
							best_err = best_err_upper+best_err_lower;
							if(best_err < total_best_err)
								total_best_err = best_err;
						}
						else
						{
							best_err = best_err_left+best_err_right;
							if(best_err < total_best_err)
								total_best_err = best_err;
						}
					}
				}
			}
		}
	}
	if(best_err_upper+best_err_lower < best_err_left+best_err_right)
	{
		best_flip = 1;
		best_enc_color1[0] = best_upper_col[0];
		best_enc_color1[1] = best_upper_col[1];
		best_enc_color1[2] = best_upper_col[2];
		best_enc_color2[0] = best_lower_col[0];
		best_enc_color2[1] = best_lower_col[1];
		best_enc_color2[2] = best_lower_col[2];
		best_err = best_err_upper+best_err_lower;
		if(best_err < total_best_err)
			total_best_err = best_err;
	}
	else
	{
		best_flip = 0;
		best_enc_color1[0] = best_left_col[0];
		best_enc_color1[1] = best_left_col[1];
		best_enc_color1[2] = best_left_col[2];
		best_enc_color2[0] = best_right_col[0];
		best_enc_color2[1] = best_right_col[1];
		best_enc_color2[2] = best_right_col[2];
		best_err = best_err_left+best_err_right;
		if(best_err < total_best_err)
			total_best_err = best_err;
	}
	color_quant1[0] = best_enc_color1[0] << 4 | (best_enc_color1[0]);
	color_quant1[1] = best_enc_color1[1] << 4 | (best_enc_color1[1]);
	color_quant1[2] = best_enc_color1[2] << 4 | (best_enc_color1[2]);
	if(best_flip == 0)
		tryalltables_3bittable2x4(img,width,height,startx,starty,color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
	else
		tryalltables_3bittable4x2(img,width,height,startx,starty,color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);

	color_quant2[0] = best_enc_color2[0] << 4 | (best_enc_color2[0]);
	color_quant2[1] = best_enc_color2[1] << 4 | (best_enc_color2[1]);
	color_quant2[2] = best_enc_color2[2] << 4 | (best_enc_color2[2]);
	if(best_flip == 0)
		tryalltables_3bittable2x4(img,width,height,startx+2,starty,color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);
	else
		tryalltables_3bittable4x2(img,width,height,startx,starty+2,color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

	//     ETC1_RGB8_OES:
	// 
	//     a) bit layout in bits 63 through 32 if diffbit = 0
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
	//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------
	//     
	//     b) bit layout in bits 63 through 32 if diffbit = 1
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |diff|flip|
	//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------
	// 
	//     c) bit layout in bits 31 through 0 (in both cases)
	// 
	//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3   2   1  0
	//      --------------------------------------------------------------------------------------------------
	//     |       most significant pixel index bits       |         least significant pixel index bits       |  
	//     | p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a| p| o| n| m| l| k| j| i| h| g| f| e| d| c | b | a |
	//      --------------------------------------------------------------------------------------------------      

	diffbit = 1;
	compressed1 = 0;
	PUTBITSHIGH( compressed1, diffbit,		      0, 33);
 	PUTBITSHIGH( compressed1, best_enc_color1[0], 4, 63);
 	PUTBITSHIGH( compressed1, best_enc_color1[1], 4, 55);
 	PUTBITSHIGH( compressed1, best_enc_color1[2], 4, 47);
 	PUTBITSHIGH( compressed1, best_enc_color2[0], 4, 59);
 	PUTBITSHIGH( compressed1, best_enc_color2[1], 4, 51);
 	PUTBITSHIGH( compressed1, best_enc_color2[2], 4, 43);
 	PUTBITSHIGH( compressed1, best_table1,	      3, 39);
 	PUTBITSHIGH( compressed1, best_table2,	      3, 36);
 	PUTBITSHIGH( compressed1, best_flip,		  1, 32);

	if(best_flip == 0)
	{
		compressed2 = 0;
		PUTBITS( compressed2, (best_pixel_indices1_MSB     ), 8, 23);
		PUTBITS( compressed2, (best_pixel_indices2_MSB     ), 8, 31);
		PUTBITS( compressed2, (best_pixel_indices1_LSB     ), 8, 7);
		PUTBITS( compressed2, (best_pixel_indices2_LSB     ), 8, 15);
	}
	else
	{
		best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
		best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);		
		compressed2 = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);
	}

	return best_err;
}
#endif
 
#if EXHAUSTIVE_CODE_ACTIVE
// Compresses the differential mode exhaustively (perecptual error metric).
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int compressBlockDifferentialExhaustivePerceptual(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2, unsigned int best_error_so_far)
{
	unsigned int best_err_norm_diff = MAXERR1000;
	unsigned int best_err_norm_444 = MAXERR1000;
	unsigned int best_err_flip_diff = MAXERR1000;
	unsigned int best_err_flip_444 = MAXERR1000;
	uint8 color_quant1[3], color_quant2[3];

	int enc_color1[3], enc_color2[3], diff[3];
	int best_enc_color1[3], best_enc_color2[3];
	signed char bytediff[3];
	
	unsigned int best_pixel_indices1_MSB=0;
	unsigned int best_pixel_indices1_LSB=0;
	unsigned int best_pixel_indices2_MSB=0;
	unsigned int best_pixel_indices2_LSB=0;
	unsigned int pixel_indices1_MSB=0;
	unsigned int pixel_indices1_LSB=0;
	unsigned int pixel_indices2_MSB=0;

	unsigned int *err_upper, *err_lower;
	unsigned int *err_left, *err_right;

	unsigned int pixel_indices2_LSB=0;

	unsigned int table1=0, table2=0;
	unsigned int best_table1=0, best_table2=0;

	unsigned int precalc_err_UL_R[8*4*4];
	unsigned int precalc_err_UR_R[8*4*4];
	unsigned int precalc_err_LL_R[8*4*4];
	unsigned int precalc_err_LR_R[8*4*4];

	unsigned int precalc_err_UL_RG[8*4*4];
	unsigned int precalc_err_UR_RG[8*4*4];
	unsigned int precalc_err_LL_RG[8*4*4];
	unsigned int precalc_err_LR_RG[8*4*4];

	unsigned int best_error_using_diff_mode;

	int diffbit;
	uint8 block_2x2[4*4*4];

	unsigned int error, error_lying, error_standing;
	unsigned int *err_lower_adr;
	int best_flip;
	unsigned int *err_right_adr;

	int xx,yy,count = 0;

	// Reshuffle pixels so that the top left 2x2 pixels arrive first, then the top right 2x2 pixels etc. Also put use 4 bytes per pixel to make it 32-word aligned.
	for(xx = 0; xx<2; xx++)
	{
		for(yy=0; yy<2; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}
	for(xx = 2; xx<4; xx++)
	{
		for(yy=0; yy<2; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}
	for(xx = 0; xx<2; xx++)
	{
		for(yy=2; yy<4; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}
	for(xx = 2; xx<4; xx++)
	{
		for(yy=2; yy<4; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}

 	unsigned int test1, test2;
	best_error_using_diff_mode = compressBlockOnlyDiffFlipAveragePerceptual1000(img, width, height, startx, starty, test1, test2);
	if(best_error_using_diff_mode < best_error_so_far)
		best_error_so_far = best_error_using_diff_mode;

	// Decode the parameters so that we have a worst case color pair and a flip status
	best_flip = test1 & 1;
	best_enc_color1[0] = GETBITSHIGH( test1, 5, 63);
	best_enc_color1[1] = GETBITSHIGH( test1, 5, 55);
	best_enc_color1[2] = GETBITSHIGH( test1, 5, 47);
	bytediff[0] = GETBITSHIGH( test1, 3, 58);
	bytediff[1] = GETBITSHIGH( test1, 3, 50);
	bytediff[2] = GETBITSHIGH( test1, 3, 42);
	bytediff[0] = (bytediff[0] << 5);
	bytediff[1] = (bytediff[1] << 5);
	bytediff[2] = (bytediff[2] << 5);
	bytediff[0] = bytediff[0] >> 5;
	bytediff[1] = bytediff[1] >> 5;
	bytediff[2] = bytediff[2] >> 5;
	best_enc_color2[0]= best_enc_color1[0] + bytediff[0];
	best_enc_color2[1]= best_enc_color1[1] + bytediff[1];
	best_enc_color2[2]= best_enc_color1[2] + bytediff[2];

	// allocate memory for errors:
	err_upper = (unsigned int*) malloc(32*32*32*sizeof(unsigned int));
	if(!err_upper){printf("Out of memory allocating \n");exit(1);}
	err_lower = (unsigned int*) malloc(32*32*32*sizeof(unsigned int));
	if(!err_lower){printf("Out of memory allocating \n");exit(1);}
	err_left = (unsigned int*) malloc(32*32*32*sizeof(unsigned int));
	if(!err_left){printf("Out of memory allocating \n");exit(1);}
	err_right = (unsigned int*) malloc(32*32*32*sizeof(unsigned int));
	if(!err_right){printf("Out of memory allocating \n");exit(1);}

	int q;
	// Calculate all errors
	for(enc_color1[0]=0; enc_color1[0]<32; enc_color1[0]++)
	{
		color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
		if(precompute_3bittable_all_subblocksR_with_test_perceptual1000(block_2x2, color_quant1, precalc_err_UL_R, precalc_err_UR_R, precalc_err_LL_R, precalc_err_LR_R, best_error_so_far))
		{
			for(enc_color1[1]=0; enc_color1[1]<32; enc_color1[1]++)
			{
				color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
				if(precompute_3bittable_all_subblocksRG_withtest_perceptual1000(block_2x2, color_quant1, precalc_err_UL_R, precalc_err_UR_R, precalc_err_LL_R, precalc_err_LR_R, precalc_err_UL_RG, precalc_err_UR_RG, precalc_err_LL_RG, precalc_err_LR_RG, best_error_so_far))
				{
					for(enc_color1[2]=0; enc_color1[2]<32; enc_color1[2]++)
					{
 						color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
						tryalltables_3bittable_all_subblocks_using_precalc_perceptual1000(block_2x2, color_quant1, precalc_err_UL_RG, precalc_err_UR_RG, precalc_err_LL_RG, precalc_err_LR_RG, err_upper[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]], err_lower[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]], err_left[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]], err_right[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]], best_error_so_far);
					}
				}
				else
				{
					for(q=0;q<32;q++)
					{
						err_upper[32*32*enc_color1[0]+32*enc_color1[1]+q] = MAXERR1000;
						err_lower[32*32*enc_color1[0]+32*enc_color1[1]+q] = MAXERR1000;
						err_left[32*32*enc_color1[0]+32*enc_color1[1]+q] = MAXERR1000;
						err_right[32*32*enc_color1[0]+32*enc_color1[1]+q] = MAXERR1000;
					}
				}
			}
		}
		else
		{
			for(q=0;q<32*32;q++)
			{
				err_upper[32*32*enc_color1[0]+q] = MAXERR1000;
				err_lower[32*32*enc_color1[0]+q] = MAXERR1000;
				err_left[32*32*enc_color1[0]+q] = MAXERR1000;
				err_right[32*32*enc_color1[0]+q] = MAXERR1000;
			}
		}
	}
	for(enc_color1[0]=0; enc_color1[0]<32; enc_color1[0]++)
	{
		for(enc_color1[1]=0; enc_color1[1]<32; enc_color1[1]++)
		{
			for(enc_color1[2]=0; enc_color1[2]<4; enc_color1[2]++)
			{
				error_lying = err_upper[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]];
				error_standing = err_left[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]];
				if(error_lying < best_error_so_far || error_standing < best_error_so_far)
				{
					for(enc_color2[0]=JAS_MAX(0,enc_color1[0]-4); enc_color2[0]<JAS_MIN(enc_color1[0]+4,32); enc_color2[0]++)
					{
						for(enc_color2[1]=JAS_MAX(0,enc_color1[1]-4); enc_color2[1]<JAS_MIN(enc_color1[1]+4,32); enc_color2[1]++)
						{
							err_lower_adr = &err_lower[32*32*enc_color2[0]+32*enc_color2[1]];
							err_right_adr = &err_right[32*32*enc_color2[0]+32*enc_color2[1]];
							for(enc_color2[2]=JAS_MAX(0,enc_color1[2]-4); enc_color2[2]<JAS_MIN(enc_color1[2]+4,32); enc_color2[2]++)
							{
								error = error_lying+err_lower_adr[enc_color2[2]];
								if(error<best_error_so_far)
								{
									best_flip = 1;
									best_error_so_far = error;
									best_error_using_diff_mode = error;
									best_enc_color1[0] = enc_color1[0];
									best_enc_color1[1] = enc_color1[1];
									best_enc_color1[2] = enc_color1[2];
									best_enc_color2[0] = enc_color2[0];
									best_enc_color2[1] = enc_color2[1];
									best_enc_color2[2] = enc_color2[2];
								}
								error = error_standing+err_right_adr[enc_color2[2]];
								if(error<best_error_so_far)
								{
									best_flip = 0;
									best_error_so_far = error;
									best_error_using_diff_mode = error;
									best_enc_color1[0] = enc_color1[0];
									best_enc_color1[1] = enc_color1[1];
									best_enc_color1[2] = enc_color1[2];
									best_enc_color2[0] = enc_color2[0];
									best_enc_color2[1] = enc_color2[1];
									best_enc_color2[2] = enc_color2[2];
								}
							}
						}
					}
				}
			}
			for(enc_color1[2]=4; enc_color1[2]<28; enc_color1[2]++)
			{
				error_lying = err_upper[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]];
				error_standing = err_left[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]];
				if(error_lying < best_error_so_far || error_standing < best_error_so_far)
				{
					for(enc_color2[0]=JAS_MAX(0,enc_color1[0]-4); enc_color2[0]<JAS_MIN(enc_color1[0]+4,32); enc_color2[0]++)
					{
						for(enc_color2[1]=JAS_MAX(0,enc_color1[1]-4); enc_color2[1]<JAS_MIN(enc_color1[1]+4,32); enc_color2[1]++)
						{
							err_lower_adr = &err_lower[32*32*enc_color2[0]+32*enc_color2[1]];
							err_right_adr = &err_right[32*32*enc_color2[0]+32*enc_color2[1]];
							// since enc_color[2] is between 4 and 29 we do not need to clamp the loop on the next line 
							for(enc_color2[2]=enc_color1[2]-4; enc_color2[2]<enc_color1[2]+4; enc_color2[2]++)
							{
								error = error_lying+err_lower_adr[enc_color2[2]];
								if(error<best_error_so_far)
								{
									best_flip = 1;
									best_error_so_far = error;
									best_error_using_diff_mode = error;
									best_enc_color1[0] = enc_color1[0];
									best_enc_color1[1] = enc_color1[1];
									best_enc_color1[2] = enc_color1[2];
									best_enc_color2[0] = enc_color2[0];
									best_enc_color2[1] = enc_color2[1];
									best_enc_color2[2] = enc_color2[2];
								}
								error = error_standing+err_right_adr[enc_color2[2]];
								if(error<best_error_so_far)
								{
									best_flip = 0;
									best_error_so_far = error;
									best_error_using_diff_mode = error;
									best_enc_color1[0] = enc_color1[0];
									best_enc_color1[1] = enc_color1[1];
									best_enc_color1[2] = enc_color1[2];
									best_enc_color2[0] = enc_color2[0];
									best_enc_color2[1] = enc_color2[1];
									best_enc_color2[2] = enc_color2[2];
								}
							}
						}
					}
				}
			}
			for(enc_color1[2]=28; enc_color1[2]<32; enc_color1[2]++)
			{
				error_lying = err_upper[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]];
				error_standing = err_left[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]];
				if(error_lying < best_error_so_far || error_standing < best_error_so_far)
				{
					for(enc_color2[0]=JAS_MAX(0,enc_color1[0]-4); enc_color2[0]<JAS_MIN(enc_color1[0]+4,32); enc_color2[0]++)
					{
						for(enc_color2[1]=JAS_MAX(0,enc_color1[1]-4); enc_color2[1]<JAS_MIN(enc_color1[1]+4,32); enc_color2[1]++)
						{
							err_lower_adr = &err_lower[32*32*enc_color2[0]+32*enc_color2[1]];
							err_right_adr = &err_right[32*32*enc_color2[0]+32*enc_color2[1]];
							for(enc_color2[2]=JAS_MAX(0,enc_color1[2]-4); enc_color2[2]<JAS_MIN(enc_color1[2]+4,32); enc_color2[2]++)
							{
								error = error_lying+err_lower_adr[enc_color2[2]];
								if(error<best_error_so_far)
								{
									best_flip = 1;
									best_error_so_far = error;
									best_error_using_diff_mode = error;
									best_enc_color1[0] = enc_color1[0];
									best_enc_color1[1] = enc_color1[1];
									best_enc_color1[2] = enc_color1[2];
									best_enc_color2[0] = enc_color2[0];
									best_enc_color2[1] = enc_color2[1];
									best_enc_color2[2] = enc_color2[2];
								}
								error = error_standing+err_right_adr[enc_color2[2]];
								if(error<best_error_so_far)
								{
									best_flip = 0;
									best_error_so_far = error;
									best_error_using_diff_mode = error;
									best_enc_color1[0] = enc_color1[0];
									best_enc_color1[1] = enc_color1[1];
									best_enc_color1[2] = enc_color1[2];
									best_enc_color2[0] = enc_color2[0];
									best_enc_color2[1] = enc_color2[1];
									best_enc_color2[2] = enc_color2[2];
								}
							}
						}
					}
				}
			}
		}
 	}

 	free(err_upper);
 	free(err_lower);
 	free(err_left);
 	free(err_right);

	color_quant1[0] = best_enc_color1[0] << 3 | (best_enc_color1[0] >> 2);
	color_quant1[1] = best_enc_color1[1] << 3 | (best_enc_color1[1] >> 2);
	color_quant1[2] = best_enc_color1[2] << 3 | (best_enc_color1[2] >> 2);
	if(best_flip == 0)
		tryalltables_3bittable2x4percep1000(img,width,height,startx,starty,color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
	else
		tryalltables_3bittable4x2percep1000(img,width,height,startx,starty,color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);

	color_quant2[0] = best_enc_color2[0] << 3 | (best_enc_color2[0] >> 2);
	color_quant2[1] = best_enc_color2[1] << 3 | (best_enc_color2[1] >> 2);
	color_quant2[2] = best_enc_color2[2] << 3 | (best_enc_color2[2] >> 2);
	if(best_flip == 0)
		tryalltables_3bittable2x4percep1000(img,width,height,startx+2,starty,color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);
	else
		tryalltables_3bittable4x2percep1000(img,width,height,startx,starty+2,color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

	diff[0] = best_enc_color2[0]-best_enc_color1[0];	
	diff[1] = best_enc_color2[1]-best_enc_color1[1];	
	diff[2] = best_enc_color2[2]-best_enc_color1[2];

	//     ETC1_RGB8_OES:
	// 
	//     a) bit layout in bits 63 through 32 if diffbit = 0
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
	//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------
	//     
	//     b) bit layout in bits 63 through 32 if diffbit = 1
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |diff|flip|
	//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------
	// 
	//     c) bit layout in bits 31 through 0 (in both cases)
	// 
	//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3   2   1  0
	//      --------------------------------------------------------------------------------------------------
	//     |       most significant pixel index bits       |         least significant pixel index bits       |  
	//     | p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a| p| o| n| m| l| k| j| i| h| g| f| e| d| c | b | a |
	//      --------------------------------------------------------------------------------------------------      

	diffbit = 1;
	compressed1 = 0;
	PUTBITSHIGH( compressed1, diffbit,		      1, 33);
 	PUTBITSHIGH( compressed1, best_enc_color1[0], 5, 63);
 	PUTBITSHIGH( compressed1, best_enc_color1[1], 5, 55);
 	PUTBITSHIGH( compressed1, best_enc_color1[2], 5, 47);
 	PUTBITSHIGH( compressed1, diff[0],            3, 58);
 	PUTBITSHIGH( compressed1, diff[1],            3, 50);
 	PUTBITSHIGH( compressed1, diff[2],            3, 42);
 	PUTBITSHIGH( compressed1, best_table1,	      3, 39);
 	PUTBITSHIGH( compressed1, best_table2,	      3, 36);
 	PUTBITSHIGH( compressed1, best_flip,		  1, 32);

	if(best_flip == 0)
	{
		compressed2 = 0;
		PUTBITS( compressed2, (best_pixel_indices1_MSB     ), 8, 23);
		PUTBITS( compressed2, (best_pixel_indices2_MSB     ), 8, 31);
		PUTBITS( compressed2, (best_pixel_indices1_LSB     ), 8, 7);
		PUTBITS( compressed2, (best_pixel_indices2_LSB     ), 8, 15);
	}
	else
	{
		best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
		best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);		
		compressed2 = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);
	}
	return best_error_using_diff_mode;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Compresses the differential mode exhaustively.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int compressBlockDifferentialExhaustive(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2, unsigned int previous_best_err)
{
	unsigned int best_err_norm_diff = 255*255*16*3;
	unsigned int best_err_norm_444 = 255*255*16*3;
	unsigned int best_err_flip_diff = 255*255*16*3;
	unsigned int best_err_flip_444 = 255*255*16*3;
	uint8 color_quant1[3], color_quant2[3];

	int enc_color1[3], enc_color2[3], diff[3];
	int best_enc_color1[3], best_enc_color2[3];
	
	int min_error=255*255*8*3;
	unsigned int best_pixel_indices1_MSB=0;
	unsigned int best_pixel_indices1_LSB=0;
	unsigned int best_pixel_indices2_MSB=0;
	unsigned int best_pixel_indices2_LSB=0;
	unsigned int pixel_indices1_MSB=0;
	unsigned int pixel_indices1_LSB=0;
	unsigned int pixel_indices2_MSB=0;

	unsigned int *err_upper, *err_lower;
	unsigned int *err_left, *err_right;

	unsigned int pixel_indices2_LSB=0;

	unsigned int table1=0, table2=0;
	unsigned int best_table1=0, best_table2=0;

	unsigned int precalc_err_UL_R[8*4*4];
	unsigned int precalc_err_UR_R[8*4*4];
	unsigned int precalc_err_LL_R[8*4*4];
	unsigned int precalc_err_LR_R[8*4*4];

	unsigned int precalc_err_UL_RG[8*4*4];
	unsigned int precalc_err_UR_RG[8*4*4];
	unsigned int precalc_err_LL_RG[8*4*4];
	unsigned int precalc_err_LR_RG[8*4*4];

	int diffbit;
	uint8 block_2x2[4*4*4];

	unsigned int error, error_lying, error_standing, best_err, total_best_err;
	unsigned int *err_lower_adr;
	int best_flip;
	unsigned int *err_right_adr;

	int xx,yy,count = 0;

	// Reshuffle pixels so that the top left 2x2 pixels arrive first, then the top right 2x2 pixels etc. Also put use 4 bytes per pixel to make it 32-word aligned.
	for(xx = 0; xx<2; xx++)
	{
		for(yy=0; yy<2; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}
	for(xx = 2; xx<4; xx++)
	{
		for(yy=0; yy<2; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}
	for(xx = 0; xx<2; xx++)
	{
		for(yy=2; yy<4; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}
	for(xx = 2; xx<4; xx++)
	{
		for(yy=2; yy<4; yy++)
		{
			block_2x2[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block_2x2[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block_2x2[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block_2x2[(count)*4+3] = 0;
			count++;
		}
	}


	unsigned int test1, test2;
	best_err = (unsigned int)compressBlockOnlyDiffFlipAverage(img, width, height, startx, starty, test1, test2, best_enc_color1, best_enc_color2, best_flip);
	if(previous_best_err < best_err)
		total_best_err = previous_best_err;
	else
		total_best_err = best_err;

	// allocate memory for errors:
	err_upper = (unsigned int*) malloc(32*32*32*sizeof(unsigned int));
	if(!err_upper){printf("Out of memory allocating \n");exit(1);}
	err_lower = (unsigned int*) malloc(32*32*32*sizeof(unsigned int));
	if(!err_lower){printf("Out of memory allocating \n");exit(1);}
	err_left = (unsigned int*) malloc(32*32*32*sizeof(unsigned int));
	if(!err_left){printf("Out of memory allocating \n");exit(1);}
	err_right = (unsigned int*) malloc(32*32*32*sizeof(unsigned int));
	if(!err_right){printf("Out of memory allocating \n");exit(1);}

	int q;
	// Calculate all errors
	for(enc_color1[0]=0; enc_color1[0]<32; enc_color1[0]++)
	{
		color_quant1[0] = enc_color1[0] << 3 | (enc_color1[0] >> 2);
		if(precompute_3bittable_all_subblocksR_with_test(block_2x2, color_quant1, precalc_err_UL_R, precalc_err_UR_R, precalc_err_LL_R, precalc_err_LR_R, total_best_err))
		{
			for(enc_color1[1]=0; enc_color1[1]<32; enc_color1[1]++)
			{
				color_quant1[1] = enc_color1[1] << 3 | (enc_color1[1] >> 2);
				if(precompute_3bittable_all_subblocksRG_withtest(block_2x2, color_quant1, precalc_err_UL_R, precalc_err_UR_R, precalc_err_LL_R, precalc_err_LR_R, precalc_err_UL_RG, precalc_err_UR_RG, precalc_err_LL_RG, precalc_err_LR_RG, total_best_err))
				{
					for(enc_color1[2]=0; enc_color1[2]<32; enc_color1[2]++)
					{
 						color_quant1[2] = enc_color1[2] << 3 | (enc_color1[2] >> 2);
						tryalltables_3bittable_all_subblocks_using_precalc(block_2x2, color_quant1, precalc_err_UL_RG, precalc_err_UR_RG, precalc_err_LL_RG, precalc_err_LR_RG, err_upper[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]], err_lower[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]], err_left[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]], err_right[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]], total_best_err);
					}
				}
				else
				{
					for(q=0;q<32;q++)
					{
						err_upper[32*32*enc_color1[0]+32*enc_color1[1]+q] = 255*255*16*3;
						err_lower[32*32*enc_color1[0]+32*enc_color1[1]+q] = 255*255*16*3;
						err_left[32*32*enc_color1[0]+32*enc_color1[1]+q] = 255*255*16*3;
						err_right[32*32*enc_color1[0]+32*enc_color1[1]+q] = 255*255*16*3;
					}
				}
			}
		}
		else
		{
			for(q=0;q<32*32;q++)
			{
				err_upper[32*32*enc_color1[0]+q] = 255*255*16*3;
				err_lower[32*32*enc_color1[0]+q] = 255*255*16*3;
				err_left[32*32*enc_color1[0]+q] = 255*255*16*3;
				err_right[32*32*enc_color1[0]+q] = 255*255*16*3;
			}
		}
	}

	for(enc_color1[0]=0; enc_color1[0]<32; enc_color1[0]++)
	{
		for(enc_color1[1]=0; enc_color1[1]<32; enc_color1[1]++)
		{
			for(enc_color1[2]=0; enc_color1[2]<4; enc_color1[2]++)
			{
				error_lying = err_upper[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]];
				error_standing = err_left[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]];
				if(error_lying < total_best_err || error_standing < total_best_err)
				{
					for(enc_color2[0]=JAS_MAX(0,enc_color1[0]-4); enc_color2[0]<JAS_MIN(enc_color1[0]+4,32); enc_color2[0]++)
					{
						for(enc_color2[1]=JAS_MAX(0,enc_color1[1]-4); enc_color2[1]<JAS_MIN(enc_color1[1]+4,32); enc_color2[1]++)
						{
							err_lower_adr = &err_lower[32*32*enc_color2[0]+32*enc_color2[1]];
							err_right_adr = &err_right[32*32*enc_color2[0]+32*enc_color2[1]];
							for(enc_color2[2]=JAS_MAX(0,enc_color1[2]-4); enc_color2[2]<JAS_MIN(enc_color1[2]+4,32); enc_color2[2]++)
							{
								error = error_lying+err_lower_adr[enc_color2[2]];
								if(error<best_err)
								{
									best_flip = 1;
									best_err = error;
									best_enc_color1[0] = enc_color1[0];
									best_enc_color1[1] = enc_color1[1];
									best_enc_color1[2] = enc_color1[2];
									best_enc_color2[0] = enc_color2[0];
									best_enc_color2[1] = enc_color2[1];
									best_enc_color2[2] = enc_color2[2];
								}
								error = error_standing+err_right_adr[enc_color2[2]];
								if(error<best_err)
								{
									best_flip = 0;
									best_err = error;
									best_enc_color1[0] = enc_color1[0];
									best_enc_color1[1] = enc_color1[1];
									best_enc_color1[2] = enc_color1[2];
									best_enc_color2[0] = enc_color2[0];
									best_enc_color2[1] = enc_color2[1];
									best_enc_color2[2] = enc_color2[2];
								}
							}
						}
					}
					if(best_err < total_best_err)
						total_best_err = best_err;
				}
			}
			for(enc_color1[2]=4; enc_color1[2]<28; enc_color1[2]++)
			{
				error_lying = err_upper[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]];
				error_standing = err_left[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]];
				if(error_lying < total_best_err || error_standing < total_best_err)
				{
					for(enc_color2[0]=JAS_MAX(0,enc_color1[0]-4); enc_color2[0]<JAS_MIN(enc_color1[0]+4,32); enc_color2[0]++)
					{
						for(enc_color2[1]=JAS_MAX(0,enc_color1[1]-4); enc_color2[1]<JAS_MIN(enc_color1[1]+4,32); enc_color2[1]++)
						{
							err_lower_adr = &err_lower[32*32*enc_color2[0]+32*enc_color2[1]];
							err_right_adr = &err_right[32*32*enc_color2[0]+32*enc_color2[1]];
							// since enc_color[2] is between 4 and 29 we do not need to clamp the loop on the next line 
							for(enc_color2[2]=enc_color1[2]-4; enc_color2[2]<enc_color1[2]+4; enc_color2[2]++)
							{
								error = error_lying+err_lower_adr[enc_color2[2]];
								if(error<best_err)
								{
									best_flip = 1;
									best_err = error;
									best_enc_color1[0] = enc_color1[0];
									best_enc_color1[1] = enc_color1[1];
									best_enc_color1[2] = enc_color1[2];
									best_enc_color2[0] = enc_color2[0];
									best_enc_color2[1] = enc_color2[1];
									best_enc_color2[2] = enc_color2[2];
								}
								error = error_standing+err_right_adr[enc_color2[2]];
								if(error<best_err)
								{
									best_flip = 0;
									best_err = error;
									best_enc_color1[0] = enc_color1[0];
									best_enc_color1[1] = enc_color1[1];
									best_enc_color1[2] = enc_color1[2];
									best_enc_color2[0] = enc_color2[0];
									best_enc_color2[1] = enc_color2[1];
									best_enc_color2[2] = enc_color2[2];
								}
							}
						}
					}
					if(best_err < total_best_err)
						total_best_err = best_err;

				}
			}
			for(enc_color1[2]=28; enc_color1[2]<32; enc_color1[2]++)
			{
				error_lying = err_upper[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]];
				error_standing = err_left[32*32*enc_color1[0]+32*enc_color1[1]+enc_color1[2]];
				if(error_lying < total_best_err || error_standing < total_best_err)
				{
					for(enc_color2[0]=JAS_MAX(0,enc_color1[0]-4); enc_color2[0]<JAS_MIN(enc_color1[0]+4,32); enc_color2[0]++)
					{
						for(enc_color2[1]=JAS_MAX(0,enc_color1[1]-4); enc_color2[1]<JAS_MIN(enc_color1[1]+4,32); enc_color2[1]++)
						{
							err_lower_adr = &err_lower[32*32*enc_color2[0]+32*enc_color2[1]];
							err_right_adr = &err_right[32*32*enc_color2[0]+32*enc_color2[1]];
							for(enc_color2[2]=JAS_MAX(0,enc_color1[2]-4); enc_color2[2]<JAS_MIN(enc_color1[2]+4,32); enc_color2[2]++)
							{
								error = error_lying+err_lower_adr[enc_color2[2]];
								if(error<best_err)
								{
									best_flip = 1;
									best_err = error;
									best_enc_color1[0] = enc_color1[0];
									best_enc_color1[1] = enc_color1[1];
									best_enc_color1[2] = enc_color1[2];
									best_enc_color2[0] = enc_color2[0];
									best_enc_color2[1] = enc_color2[1];
									best_enc_color2[2] = enc_color2[2];
								}
								error = error_standing+err_right_adr[enc_color2[2]];
								if(error<best_err)
								{
									best_flip = 0;
									best_err = error;
									best_enc_color1[0] = enc_color1[0];
									best_enc_color1[1] = enc_color1[1];
									best_enc_color1[2] = enc_color1[2];
									best_enc_color2[0] = enc_color2[0];
									best_enc_color2[1] = enc_color2[1];
									best_enc_color2[2] = enc_color2[2];
								}
							}
						}
					}
					if(best_err < total_best_err)
						total_best_err = best_err;
				}
			}
		}
 	}

	free(err_upper);
	free(err_lower);
	free(err_left);
	free(err_right);


	color_quant1[0] = best_enc_color1[0] << 3 | (best_enc_color1[0] >> 2);
	color_quant1[1] = best_enc_color1[1] << 3 | (best_enc_color1[1] >> 2);
	color_quant1[2] = best_enc_color1[2] << 3 | (best_enc_color1[2] >> 2);
	if(best_flip == 0)
		tryalltables_3bittable2x4(img,width,height,startx,starty,color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);
	else
		tryalltables_3bittable4x2(img,width,height,startx,starty,color_quant1,best_table1,best_pixel_indices1_MSB, best_pixel_indices1_LSB);

	color_quant2[0] = best_enc_color2[0] << 3 | (best_enc_color2[0] >> 2);
	color_quant2[1] = best_enc_color2[1] << 3 | (best_enc_color2[1] >> 2);
	color_quant2[2] = best_enc_color2[2] << 3 | (best_enc_color2[2] >> 2);
	if(best_flip == 0)
		tryalltables_3bittable2x4(img,width,height,startx+2,starty,color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);
	else
		tryalltables_3bittable4x2(img,width,height,startx,starty+2,color_quant2,best_table2,best_pixel_indices2_MSB, best_pixel_indices2_LSB);

	diff[0] = best_enc_color2[0]-best_enc_color1[0];	
	diff[1] = best_enc_color2[1]-best_enc_color1[1];	
	diff[2] = best_enc_color2[2]-best_enc_color1[2];

	//     ETC1_RGB8_OES:
	// 
	//     a) bit layout in bits 63 through 32 if diffbit = 0
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1 | base col2 | base col1 | base col2 | base col1 | base col2 | table  | table  |diff|flip|
	//     | R1 (4bits)| R2 (4bits)| G1 (4bits)| G2 (4bits)| B1 (4bits)| B2 (4bits)| cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------
	//     
	//     b) bit layout in bits 63 through 32 if diffbit = 1
	// 
	//      63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34  33  32 
	//      ---------------------------------------------------------------------------------------------------
	//     | base col1    | dcol 2 | base col1    | dcol 2 | base col 1   | dcol 2 | table  | table  |diff|flip|
	//     | R1' (5 bits) | dR2    | G1' (5 bits) | dG2    | B1' (5 bits) | dB2    | cw 1   | cw 2   |bit |bit |
	//      ---------------------------------------------------------------------------------------------------
	// 
	//     c) bit layout in bits 31 through 0 (in both cases)
	// 
	//      31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3   2   1  0
	//      --------------------------------------------------------------------------------------------------
	//     |       most significant pixel index bits       |         least significant pixel index bits       |  
	//     | p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a| p| o| n| m| l| k| j| i| h| g| f| e| d| c | b | a |
	//      --------------------------------------------------------------------------------------------------      

	diffbit = 1;
	compressed1 = 0;
	PUTBITSHIGH( compressed1, diffbit,		      1, 33);
 	PUTBITSHIGH( compressed1, best_enc_color1[0], 5, 63);
 	PUTBITSHIGH( compressed1, best_enc_color1[1], 5, 55);
 	PUTBITSHIGH( compressed1, best_enc_color1[2], 5, 47);
 	PUTBITSHIGH( compressed1, diff[0],            3, 58);
 	PUTBITSHIGH( compressed1, diff[1],            3, 50);
 	PUTBITSHIGH( compressed1, diff[2],            3, 42);
 	PUTBITSHIGH( compressed1, best_table1,	      3, 39);
 	PUTBITSHIGH( compressed1, best_table2,	      3, 36);
 	PUTBITSHIGH( compressed1, best_flip,		  1, 32);

	if(best_flip == 0)
	{
		compressed2 = 0;
		PUTBITS( compressed2, (best_pixel_indices1_MSB     ), 8, 23);
		PUTBITS( compressed2, (best_pixel_indices2_MSB     ), 8, 31);
		PUTBITS( compressed2, (best_pixel_indices1_LSB     ), 8, 7);
		PUTBITS( compressed2, (best_pixel_indices2_LSB     ), 8, 15);
	}
	else
	{
		best_pixel_indices1_MSB |= (best_pixel_indices2_MSB << 2);
		best_pixel_indices1_LSB |= (best_pixel_indices2_LSB << 2);		
		compressed2 = ((best_pixel_indices1_MSB & 0xffff) << 16) | (best_pixel_indices1_LSB & 0xffff);
	}
	return best_err;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// This function uses real exhaustive search for the planar mode. 
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockPlanar57ExhaustivePerceptual(uint8 *img, int width,int height,int startx,int starty, unsigned int &compressed57_1, unsigned int &compressed57_2, unsigned int best_error_sofar, unsigned int best_error_planar_red, unsigned int best_error_planar_green, unsigned int best_error_planar_blue)
{
	int colorO_enc[3], colorH_enc[3], colorV_enc[3];
	int best_colorO_enc[3], best_colorH_enc[3], best_colorV_enc[3];

	unsigned int error;
	unsigned int best_error;
	unsigned int lowest_possible_error;
	unsigned int best_error_red_sofar;
	unsigned int best_error_green_sofar;
	unsigned int best_error_blue_sofar;
	unsigned int BBBtable[128*128];
	unsigned int CCCtable[128*128];

	uint8 block[4*4*4];

	// Use 4 bytes per pixel to make it 32-word aligned.
	int count = 0;
	int xx, yy;
	for(yy=0; yy<4; yy++)
	{
		for(xx = 0; xx<4; xx++)
		{
			block[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block[(count)*4+3] = 0;
			count++;
		}
	}

	// The task is to calculate the sum of the error over the entire area of the block.
	//
	// The block can be partitioned into: O A A A
	//                                    B D D C
	//                                    B D C D
	//                                    B C D D
	// where the error in 
	// O only depends on colorO
	// A only depends on colorO and colorH
	// B only depends on colorO and colorV
	// C only depends on colorH and colorV
	// D depends on all three (colorO, colorH and colorV)
	//
	// Note that B can be precalculated for all combinations of colorO and colorV
	// and the precalculated values can be used instead of calculating it in the inner loop.
	// The same applies to C.
	//
	// In the code below, the squared error over O A A A is calculated and stored in lowest_possible_error

	// Precalc BBB errors
	for(colorO_enc[0] = 0; colorO_enc[0]<64; colorO_enc[0]++)
	{
		for(colorV_enc[0] = 0; colorV_enc[0]<64; colorV_enc[0]++)
		{
			BBBtable[colorO_enc[0]*64+colorV_enc[0]] = PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*calcBBBred(block, colorO_enc[0], colorV_enc[0]);
		}
	}
	// Precalc CCC errors
	for(colorH_enc[0] = 0; colorH_enc[0]<64; colorH_enc[0]++)
	{
		for(colorV_enc[0] = 0; colorV_enc[0]<64; colorV_enc[0]++)
		{
			CCCtable[colorH_enc[0]*64+colorV_enc[0]] = PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*calcCCCred(block, colorH_enc[0], colorV_enc[0]);
		}
	}
	best_error = MAXERR1000;

	best_error_red_sofar = JAS_MIN(best_error_planar_red, best_error_sofar);
	for(colorO_enc[0] = 0; colorO_enc[0]<64; colorO_enc[0]++)
	{
		for(colorH_enc[0] = 0; colorH_enc[0]<64; colorH_enc[0]++)
		{
			lowest_possible_error = calcLowestPossibleRedOHperceptual(block, colorO_enc[0], colorH_enc[0], best_error_red_sofar);
			if(lowest_possible_error <= best_error_red_sofar)
			{
				for(colorV_enc[0] = 0; colorV_enc[0]<64; colorV_enc[0]++)
				{
					error = calcErrorPlanarOnlyRedPerceptual(block, colorO_enc[0], colorH_enc[0], colorV_enc[0], lowest_possible_error, BBBtable[colorO_enc[0]*64+colorV_enc[0]], CCCtable[colorH_enc[0]*64+colorV_enc[0]], best_error_red_sofar);
					if(error < best_error)
					{
						best_error = error;
						best_colorO_enc[0] = colorO_enc[0];
						best_colorH_enc[0] = colorH_enc[0];
						best_colorV_enc[0] = colorV_enc[0];
					}
				}
			}
		}
	}

    if(best_error < best_error_planar_red)
        best_error_planar_red = best_error;

    if(best_error_planar_red > best_error_sofar)
	{
       // The red component in itself is already bigger than the previously best value ---- we can give up.
       // use the dummy color black for all colors and report that the errors for the different color components are infinite
       best_error_planar_green = MAXERR1000;
       best_error_planar_blue = MAXERR1000;
       compressed57_1 = 0;
       compressed57_2 = 0;
       return;
	}

	// The task is to calculate the sum of the error over the entire area of the block.
	//
	// The block can be partitioned into: O A A A
	//                                    B D D C
	//                                    B D C D
	//                                    B C D D
	// where the error in 
	// O only depends on colorO
	// A only depends on colorO and colorH
	// B only depends on colorO and colorV
	// C only depends on colorH and colorV
	// D depends on all three (colorO, colorH and colorV)
	//
	// Note that B can be precalculated for all combinations of colorO and colorV
	// and the precalculated values can be used instead of calculating it in the inner loop.
	// The same applies to C.
	//
	// In the code below, the squared error over O A A A is calculated and store in lowest_possible_error

	// Precalc BBB errors
	for(colorO_enc[1] = 0; colorO_enc[1]<128; colorO_enc[1]++)
	{
		for(colorV_enc[1] = 0; colorV_enc[1]<128; colorV_enc[1]++)
		{
			BBBtable[colorO_enc[1]*128+colorV_enc[1]] = PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*calcBBBgreen(block, colorO_enc[1], colorV_enc[1]);
		}
	}
	// Precalc CCC errors
	for(colorH_enc[1] = 0; colorH_enc[1]<128; colorH_enc[1]++)
	{
		for(colorV_enc[1] = 0; colorV_enc[1]<128; colorV_enc[1]++)
		{
			CCCtable[colorH_enc[1]*128+colorV_enc[1]] = PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*calcCCCgreen(block, colorH_enc[1], colorV_enc[1]);
		}
	}
	best_error = MAXERR1000;
	best_error_green_sofar = JAS_MIN(best_error_planar_green, best_error_sofar);
	for(colorO_enc[1] = 0; colorO_enc[1]<128; colorO_enc[1]++)
	{
		for(colorH_enc[1] = 0; colorH_enc[1]<128; colorH_enc[1]++)
		{
			lowest_possible_error = calcLowestPossibleGreenOHperceptual(block, colorO_enc[1], colorH_enc[1], best_error_green_sofar);
			if(lowest_possible_error <= best_error_green_sofar)
			{
				for(colorV_enc[1] = 0; colorV_enc[1]<128; colorV_enc[1]++)
				{
					error = calcErrorPlanarOnlyGreenPerceptual(block, colorO_enc[1], colorH_enc[1], colorV_enc[1], lowest_possible_error, BBBtable[colorO_enc[1]*128+colorV_enc[1]], CCCtable[colorH_enc[1]*128+colorV_enc[1]], best_error_green_sofar);
					if(error < best_error)
					{
						best_error = error;
						best_colorO_enc[1] = colorO_enc[1];
						best_colorH_enc[1] = colorH_enc[1];
						best_colorV_enc[1] = colorV_enc[1];
					}
				}
			}
		}
	}

    if(best_error < best_error_planar_green)
        best_error_planar_green = best_error;

    if(best_error_planar_red + best_error_planar_green > best_error_sofar)
	{
       // The red component in itself is already bigger than the previously best value ---- we can give up.
       // use the dummy color black for all colors and report that the errors for the different color components are infinite
       best_error_planar_blue = MAXERR1000;
       compressed57_1 = 0;
       compressed57_2 = 0;
       return;
	}

	// The task is to calculate the sum of the error over the entire area of the block.
	//
	// The block can be partitioned into: O A A A
	//                                    B D D C
	//                                    B D C D
	//                                    B C D D
	// where the error in 
	// O only depends on colorO
	// A only depends on colorO and colorH
	// B only depends on colorO and colorV
	// C only depends on colorH and colorV
	// D depends on all three (colorO, colorH and colorV)
	//
	// Note that B can be precalculated for all combinations of colorO and colorV
	// and the precalculated values can be used instead of calculating it in the inner loop.
	// The same applies to C.
	//
	// In the code below, the squared error over O A A A is calculated and store in lowest_possible_error

	// Precalc BBB errors
	for(colorO_enc[2] = 0; colorO_enc[2]<64; colorO_enc[2]++)
	{
		for(colorV_enc[2] = 0; colorV_enc[2]<64; colorV_enc[2]++)
		{
			BBBtable[colorO_enc[2]*64+colorV_enc[2]] = calcBBBbluePerceptual(block, colorO_enc[2], colorV_enc[2]);
		}
	}
	// Precalc CCC errors
	for(colorH_enc[2] = 0; colorH_enc[2]<64; colorH_enc[2]++)
	{
		for(colorV_enc[2] = 0; colorV_enc[2]<64; colorV_enc[2]++)
		{
			CCCtable[colorH_enc[2]*64+colorV_enc[2]] = calcCCCbluePerceptual(block, colorH_enc[2], colorV_enc[2]);
		}
	}
	best_error = MAXERR1000;
	best_error_blue_sofar = JAS_MIN(best_error_planar_blue, best_error_sofar);
	for(colorO_enc[2] = 0; colorO_enc[2]<64; colorO_enc[2]++)
	{
		for(colorH_enc[2] = 0; colorH_enc[2]<64; colorH_enc[2]++)
		{
			lowest_possible_error = calcLowestPossibleBlueOHperceptual(block, colorO_enc[2], colorH_enc[2], best_error_blue_sofar);
			if(lowest_possible_error <= best_error_blue_sofar)
			{
				for(colorV_enc[2] = 0; colorV_enc[2]<64; colorV_enc[2]++)
				{
					error = calcErrorPlanarOnlyBluePerceptual(block, colorO_enc[2], colorH_enc[2], colorV_enc[2], lowest_possible_error, BBBtable[colorO_enc[2]*64+colorV_enc[2]], CCCtable[colorH_enc[2]*64+colorV_enc[2]], best_error_blue_sofar);
					if(error < best_error)
					{
						best_error = error;
						best_colorO_enc[2] = colorO_enc[2];
						best_colorH_enc[2] = colorH_enc[2];
						best_colorV_enc[2] = colorV_enc[2];
					}
				}
			}
		}
	}

	if(best_error < best_error_planar_blue)
		best_error_planar_blue = best_error;

	compressed57_1 = 0;
	compressed57_2 = 0;
	PUTBITSHIGH( compressed57_1, best_colorO_enc[0], 6, 63);
	PUTBITSHIGH( compressed57_1, best_colorO_enc[1], 7, 57);
	PUTBITSHIGH( compressed57_1, best_colorO_enc[2], 6, 50);
	PUTBITSHIGH( compressed57_1, best_colorH_enc[0], 6, 44);
	PUTBITSHIGH( compressed57_1, best_colorH_enc[1], 7, 38);
	PUTBITS(     compressed57_2, best_colorH_enc[2], 6, 31);
	PUTBITS(     compressed57_2, best_colorV_enc[0], 6, 25);
	PUTBITS(     compressed57_2, best_colorV_enc[1], 7, 19);
	PUTBITS(     compressed57_2, best_colorV_enc[2], 6, 12);
	
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// This function uses real exhaustive search for the planar mode. 
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockPlanar57Exhaustive(uint8 *img, int width,int height,int startx,int starty, unsigned int &compressed57_1, unsigned int &compressed57_2, unsigned int best_error_sofar, unsigned int best_error_red, unsigned int best_error_green, unsigned int best_error_blue)
{
	int colorO_enc[3], colorH_enc[3], colorV_enc[3];
	int best_colorO_enc[3], best_colorH_enc[3], best_colorV_enc[3];

	unsigned int error;
	unsigned int best_error;
	unsigned int lowest_possible_error;
	unsigned int best_error_red_sofar;
	unsigned int best_error_green_sofar;
	unsigned int best_error_blue_sofar;
	unsigned int BBBtable[128*128];
	unsigned int CCCtable[128*128];

	uint8 block[4*4*4];

	// Use 4 bytes per pixel to make it 32-word aligned.
	int count = 0;
	int xx, yy;
	for(yy=0; yy<4; yy++)
	{
		for(xx = 0; xx<4; xx++)
		{
			block[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block[(count)*4+3] = 0;
			count++;
		}
	}

	// The task is to calculate the sum of the error over the entire area of the block.
	//
	// The block can be partitioned into: O A A A
	//                                    B D D C
	//                                    B D C D
	//                                    B C D D
	// where the error in 
	// O only depends on colorO
	// A only depends on colorO and colorH
	// B only depends on colorO and colorV
	// C only depends on colorH and colorV
	// D depends on all three (colorO, colorH and colorV)
	//
	// Note that B can be precalculated for all combinations of colorO and colorV
	// and the precalculated values can be used instead of calculating it in the inner loop.
	// The same applies to C.
	//
	// In the code below, the squared error over O A A A is calculated and store in lowest_possible_error

	// Precalc BBB errors
	for(colorO_enc[0] = 0; colorO_enc[0]<64; colorO_enc[0]++)
	{
		for(colorV_enc[0] = 0; colorV_enc[0]<64; colorV_enc[0]++)
		{
			BBBtable[colorO_enc[0]*64+colorV_enc[0]] = calcBBBred(block, colorO_enc[0], colorV_enc[0]);
		}
	}
	// Precalc CCC errors
	for(colorH_enc[0] = 0; colorH_enc[0]<64; colorH_enc[0]++)
	{
		for(colorV_enc[0] = 0; colorV_enc[0]<64; colorV_enc[0]++)
		{
			CCCtable[colorH_enc[0]*64+colorV_enc[0]] = calcCCCred(block, colorH_enc[0], colorV_enc[0]);
		}
	}
	best_error = MAXERR1000;
	best_error_red_sofar = JAS_MIN(best_error_red, best_error_sofar);
	for(colorO_enc[0] = 0; colorO_enc[0]<64; colorO_enc[0]++)
	{
		for(colorH_enc[0] = 0; colorH_enc[0]<64; colorH_enc[0]++)
		{
			lowest_possible_error = calcLowestPossibleRedOH(block, colorO_enc[0], colorH_enc[0], best_error_red_sofar);
			if(lowest_possible_error <= best_error_red_sofar)
			{
				for(colorV_enc[0] = 0; colorV_enc[0]<64; colorV_enc[0]++)
				{
					error = calcErrorPlanarOnlyRed(block, colorO_enc[0], colorH_enc[0], colorV_enc[0], lowest_possible_error, BBBtable[colorO_enc[0]*64+colorV_enc[0]], CCCtable[colorH_enc[0]*64+colorV_enc[0]], best_error_red_sofar);
					if(error < best_error)
					{
						best_error = error;
						best_colorO_enc[0] = colorO_enc[0];
						best_colorH_enc[0] = colorH_enc[0];
						best_colorV_enc[0] = colorV_enc[0];
					}
				}
			}
		}
	}

	// The task is to calculate the sum of the error over the entire area of the block.
	//
	// The block can be partitioned into: O A A A
	//                                    B D D C
	//                                    B D C D
	//                                    B C D D
	// where the error in 
	// O only depends on colorO
	// A only depends on colorO and colorH
	// B only depends on colorO and colorV
	// C only depends on colorH and colorV
	// D depends on all three (colorO, colorH and colorV)
	//
	// Note that B can be precalculated for all combinations of colorO and colorV
	// and the precalculated values can be used instead of calculating it in the inner loop.
	// The same applies to C.
	//
	// In the code below, the squared error over O A A A is calculated and store in lowest_possible_error

	// Precalc BBB errors
	for(colorO_enc[1] = 0; colorO_enc[1]<128; colorO_enc[1]++)
	{
		for(colorV_enc[1] = 0; colorV_enc[1]<128; colorV_enc[1]++)
		{
			BBBtable[colorO_enc[1]*128+colorV_enc[1]] = calcBBBgreen(block, colorO_enc[1], colorV_enc[1]);
		}
	}
	// Precalc CCC errors
	for(colorH_enc[1] = 0; colorH_enc[1]<128; colorH_enc[1]++)
	{
		for(colorV_enc[1] = 0; colorV_enc[1]<128; colorV_enc[1]++)
		{
			CCCtable[colorH_enc[1]*128+colorV_enc[1]] = calcCCCgreen(block, colorH_enc[1], colorV_enc[1]);
		}
	}
	best_error = MAXERR1000;
	best_error_green_sofar = JAS_MIN(best_error_green, best_error_sofar);
	for(colorO_enc[1] = 0; colorO_enc[1]<128; colorO_enc[1]++)
	{
		for(colorH_enc[1] = 0; colorH_enc[1]<128; colorH_enc[1]++)
		{
			lowest_possible_error = calcLowestPossibleGreenOH(block, colorO_enc[1], colorH_enc[1], best_error_green_sofar);
			if(lowest_possible_error <= best_error_green_sofar)
			{
				for(colorV_enc[1] = 0; colorV_enc[1]<128; colorV_enc[1]++)
				{
					error = calcErrorPlanarOnlyGreen(block, colorO_enc[1], colorH_enc[1], colorV_enc[1], lowest_possible_error, BBBtable[colorO_enc[1]*128+colorV_enc[1]], CCCtable[colorH_enc[1]*128+colorV_enc[1]], best_error_green_sofar);
					if(error < best_error)
					{
						best_error = error;
						best_colorO_enc[1] = colorO_enc[1];
						best_colorH_enc[1] = colorH_enc[1];
						best_colorV_enc[1] = colorV_enc[1];
					}
				}
			}
		}
	}

	// The task is to calculate the sum of the error over the entire area of the block.
	//
	// The block can be partitioned into: O A A A
	//                                    B D D C
	//                                    B D C D
	//                                    B C D D
	// where the error in 
	// O only depends on colorO
	// A only depends on colorO and colorH
	// B only depends on colorO and colorV
	// C only depends on colorH and colorV
	// D depends on all three (colorO, colorH and colorV)
	//
	// Note that B can be precalculated for all combinations of colorO and colorV
	// and the precalculated values can be used instead of calculating it in the inner loop.
	// The same applies to C.
	//
	// In the code below, the squared error over O A A A is calculated and store in lowest_possible_error

	// Precalc BBB errors
	for(colorO_enc[2] = 0; colorO_enc[2]<64; colorO_enc[2]++)
	{
		for(colorV_enc[2] = 0; colorV_enc[2]<64; colorV_enc[2]++)
		{
			BBBtable[colorO_enc[2]*64+colorV_enc[2]] = calcBBBblue(block, colorO_enc[2], colorV_enc[2]);
		}
	}
	// Precalc CCC errors
	for(colorH_enc[2] = 0; colorH_enc[2]<64; colorH_enc[2]++)
	{
		for(colorV_enc[2] = 0; colorV_enc[2]<64; colorV_enc[2]++)
		{
			CCCtable[colorH_enc[2]*64+colorV_enc[2]] = calcCCCblue(block, colorH_enc[2], colorV_enc[2]);
		}
	}
	best_error = MAXERR1000;
	best_error_blue_sofar = JAS_MIN(best_error_blue, best_error_sofar);
	for(colorO_enc[2] = 0; colorO_enc[2]<64; colorO_enc[2]++)
	{
		for(colorH_enc[2] = 0; colorH_enc[2]<64; colorH_enc[2]++)
		{
			lowest_possible_error = calcLowestPossibleBlueOH(block, colorO_enc[2], colorH_enc[2], best_error_blue_sofar);
			if(lowest_possible_error <= best_error_blue_sofar)
			{
				for(colorV_enc[2] = 0; colorV_enc[2]<64; colorV_enc[2]++)
				{
					error = calcErrorPlanarOnlyBlue(block, colorO_enc[2], colorH_enc[2], colorV_enc[2], lowest_possible_error, BBBtable[colorO_enc[2]*64+colorV_enc[2]], CCCtable[colorH_enc[2]*64+colorV_enc[2]], best_error_blue_sofar);
					if(error < best_error)
					{
						best_error = error;
						best_colorO_enc[2] = colorO_enc[2];
						best_colorH_enc[2] = colorH_enc[2];
						best_colorV_enc[2] = colorV_enc[2];
					}
				}
			}
		}
	}

	compressed57_1 = 0;
	compressed57_2 = 0;
	PUTBITSHIGH( compressed57_1, best_colorO_enc[0], 6, 63);
	PUTBITSHIGH( compressed57_1, best_colorO_enc[1], 7, 57);
	PUTBITSHIGH( compressed57_1, best_colorO_enc[2], 6, 50);
	PUTBITSHIGH( compressed57_1, best_colorH_enc[0], 6, 44);
	PUTBITSHIGH( compressed57_1, best_colorH_enc[1], 7, 38);
	PUTBITS(     compressed57_2, best_colorH_enc[2], 6, 31);
	PUTBITS(     compressed57_2, best_colorV_enc[0], 6, 25);
	PUTBITS(     compressed57_2, best_colorV_enc[1], 7, 19);
	PUTBITS(     compressed57_2, best_colorV_enc[2], 6, 12);
	
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates a table used in exhaustive compression of the T-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcError59T_col0_Rpercep1000(uint8* block, int colorRGB444_packed, unsigned int *precalc_err_col0_R)
{
	unsigned int block_error = 0, 
	  	     	 best_block_error = MAXERR1000,
			     pixel_error, 
		         best_pixel_error;
	int diff;
	uint8 color;
	uint8 possible_colors[3];

	color = ((colorRGB444_packed >> 8) & 0xf)*17;

	// Test all distances
	for (uint8 d = 0; d < 8; d++)
	{

		possible_colors[0] = CLAMP(0,color - table59T[d],255);
		possible_colors[1] = CLAMP(0,color,255);
		possible_colors[2] = CLAMP(0,color + table59T[d],255);

		// Loop block
		for (int x = 0; x < 16; x++)
		{
			best_pixel_error = MAXERR1000;

			// Loop possible block colors
			for (uint8 c = 0; c < 3; c++) 
			{
			
				diff = block[4*x + R] - CLAMP(0,possible_colors[c],255);

				pixel_error = PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(diff);

				// Choose best error
				if (pixel_error < best_pixel_error) 
					best_pixel_error = pixel_error;
			}

			precalc_err_col0_R[((colorRGB444_packed>>8)*8 + d)*16 + x] = (unsigned int) best_pixel_error;
		}

	}
		
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates a table used in exhaustive compression of the T-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcError59T_col0_R(uint8* block, int colorRGB444_packed, unsigned int *precalc_err_col0_R)
{
	unsigned int block_error = 0, 
	  	     	   best_block_error = MAXIMUM_ERROR, 
							 pixel_error, 
							 best_pixel_error;
	int diff;
	uint8 color;
	uint8 possible_colors[3];

	color = ((colorRGB444_packed >> 8) & 0xf)*17;

	// Test all distances
	for (uint8 d = 0; d < 8; d++)
	{

		possible_colors[0] = CLAMP(0,color - table59T[d],255);
		possible_colors[1] = CLAMP(0,color,255);
		possible_colors[2] = CLAMP(0,color + table59T[d],255);

		// Loop block
		for (int x = 0; x < 16; x++)
		{
			best_pixel_error = MAXIMUM_ERROR;

			// Loop possible block colors
			for (uint8 c = 0; c < 3; c++) 
			{
			
				diff = block[4*x + R] - CLAMP(0,possible_colors[c],255);

				pixel_error = SQUARE(diff);

				// Choose best error
				if (pixel_error < best_pixel_error) 
					best_pixel_error = pixel_error;
			}
			precalc_err_col0_R[((colorRGB444_packed>>8)*8 + d)*16 + x] = (unsigned int) best_pixel_error;
		}
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates a table used in exhaustive compression of the T-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcError59T_col0_RGpercep1000(uint8* block, int colorRGB444_packed, unsigned int *precalc_err_col0_RG)
{
	unsigned int block_error = 0, 
	  	     	 best_block_error = MAXERR1000,
			     pixel_error, 
		         best_pixel_error;
	int diff[3];
	uint8 color[3];
	uint8 possible_colors[3][2];

	color[R] = ((colorRGB444_packed >> 8) & 0xf)*17;
	color[G] = ((colorRGB444_packed >> 4) & 0xf)*17;

	// Test all distances
	for (uint8 d = 0; d < 8; d++)
	{

		possible_colors[0][R] = CLAMP(0,color[R] - table59T[d],255);
		possible_colors[0][G] = CLAMP(0,color[G] - table59T[d],255);

		possible_colors[1][R] = CLAMP(0,color[R],255);
		possible_colors[1][G] = CLAMP(0,color[G],255);

		possible_colors[2][R] = CLAMP(0,color[R] + table59T[d],255);
		possible_colors[2][G] = CLAMP(0,color[G] + table59T[d],255);

		

		// Loop block
		for (int x = 0; x < 16; x++)
		{
			best_pixel_error = MAXERR1000;

			// Loop possible block colors
			for (uint8 c = 0; c < 3; c++) 
			{
			
				diff[R] = block[4*x + R] - CLAMP(0,possible_colors[c][R],255);
				diff[G] = block[4*x + G] - CLAMP(0,possible_colors[c][G],255);

				pixel_error = PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(diff[R]) + PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*SQUARE(diff[G]);

				// Choose best error
				if (pixel_error < best_pixel_error) 
					best_pixel_error = pixel_error;
			}
			precalc_err_col0_RG[((colorRGB444_packed>>4)*8 + d)*16 + x] = (unsigned int) best_pixel_error;
		}
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates a table used in exhaustive compression of the T-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcError59T_col0_RG(uint8* block, int colorRGB444_packed, unsigned int *precalc_err_col0_RG)
{
	unsigned int block_error = 0, 
	  	     	 best_block_error = MAXIMUM_ERROR, 
			     pixel_error, 
		         best_pixel_error;
	int diff[3];
	uint8 color[3];
	uint8 possible_colors[3][2];

	color[R] = ((colorRGB444_packed >> 8) & 0xf)*17;
	color[G] = ((colorRGB444_packed >> 4) & 0xf)*17;

	// Test all distances
	for (uint8 d = 0; d < 8; d++)
	{

		possible_colors[0][R] = CLAMP(0,color[R] - table59T[d],255);
		possible_colors[0][G] = CLAMP(0,color[G] - table59T[d],255);

		possible_colors[1][R] = CLAMP(0,color[R],255);
		possible_colors[1][G] = CLAMP(0,color[G],255);

		possible_colors[2][R] = CLAMP(0,color[R] + table59T[d],255);
		possible_colors[2][G] = CLAMP(0,color[G] + table59T[d],255);

		// Loop block
		for (int x = 0; x < 16; x++)
		{
			best_pixel_error = MAXIMUM_ERROR;

			// Loop possible block colors
			for (uint8 c = 0; c < 3; c++) 
			{
				diff[R] = block[4*x + R] - CLAMP(0,possible_colors[c][R],255);
				diff[G] = block[4*x + G] - CLAMP(0,possible_colors[c][G],255);

				pixel_error = SQUARE(diff[R]) + SQUARE(diff[G]);

				// Choose best error
				if (pixel_error < best_pixel_error) 
					best_pixel_error = pixel_error;
			}
			precalc_err_col0_RG[((colorRGB444_packed>>4)*8 + d)*16 + x] = (unsigned int) best_pixel_error;
		}
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates a table used in exhaustive compression of the T-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcError59T_col1_Rpercep1000(uint8* block, int colorRGB444_packed, unsigned int *precalc_err_col1_R)
{
	unsigned int pixel_error; 
	int diff;
	uint8 color;

	color = ((colorRGB444_packed >> 8) & 0xf)*17;

	// Loop block
	for (int x = 0; x < 16; x++)
	{
		diff = block[4*x + R] - color;
		pixel_error = PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(diff);
		precalc_err_col1_R[((colorRGB444_packed>>8))*16 + x] = (unsigned int) pixel_error;
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
/**
 * Calculate the error for the block at position (startx,starty)
 * The parameters needed for reconstruction is calculated as well
 *
 * In the 59T bit mode, we only have pattern T.
 */
void precalcError59T_col1_R(uint8* block, int colorRGB444_packed, unsigned int *precalc_err_col1_R)
{
	unsigned int pixel_error; 
	int diff;
	uint8 color;

	color = ((colorRGB444_packed >> 8) & 0xf)*17;

	// Loop block
	for (int x = 0; x < 16; x++)
	{
		diff = block[4*x + R] - color;
		pixel_error = SQUARE(diff);
		precalc_err_col1_R[((colorRGB444_packed>>8))*16 + x] = (unsigned int) pixel_error;
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates a table used in exhaustive compression of the T-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcError59T_col1_RGpercep1000(uint8* block, int colorRGB444_packed, unsigned int *precalc_err_col1_RG)
{
	unsigned int pixel_error; 
	int diff[3];
	uint8 color[2];

	color[R] = ((colorRGB444_packed >> 8) & 0xf)*17;
	color[G] = ((colorRGB444_packed >> 4) & 0xf)*17;

	// Loop block
	for (int x = 0; x < 16; x++)
	{
		diff[R] = block[4*x + R] - color[R];
		diff[G] = block[4*x + G] - color[G];
		pixel_error = PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(diff[R]) + PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*SQUARE(diff[G]);
		precalc_err_col1_RG[((colorRGB444_packed>>4))*16 + x] = (unsigned int) pixel_error;
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates a table used in exhaustive compression of the T-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcError59T_col1_RG(uint8* block, int colorRGB444_packed, unsigned int *precalc_err_col1_RG)
{
	unsigned int pixel_error; 
	int diff[3];
	uint8 color[2];

	color[R] = ((colorRGB444_packed >> 8) & 0xf)*17;
	color[G] = ((colorRGB444_packed >> 4) & 0xf)*17;

	// Loop block
	for (int x = 0; x < 16; x++)
	{
		diff[R] = block[4*x + R] - color[R];
		diff[G] = block[4*x + G] - color[G];
		pixel_error = SQUARE(diff[R]) + SQUARE(diff[G]);
		precalc_err_col1_RG[((colorRGB444_packed>>4))*16 + x] = (unsigned int) pixel_error;
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates a table used in exhaustive compression of the T-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcError59T_col0_RGBpercep1000(uint8* block, int colorRGB444_packed, unsigned int *precalc_err_col0_RGB)
{
	unsigned int block_error = 0, 
	  	     	 best_block_error = MAXERR1000,
			     pixel_error, 
		         best_pixel_error;
	uint8 color[3];
	int possible_colors[3][3];
	unsigned int *precalc_err_col0_RGB_adr;

#define ONEPOINT59RGB_PERCEP(xval) \
			/* Loop possible block colors */\
			/* unroll loop for (uint8 c = 0; c < 3; c++) */\
			{\
				best_pixel_error = PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*square_table[block[4*xval + R] - possible_colors[0][R]]\
                            + PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*square_table[block[4*xval + G] - possible_colors[0][G]] \
							+ PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[block[4*xval + B] - possible_colors[0][B]];\
				pixel_error = PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*square_table[block[4*xval + R] - possible_colors[1][R]]\
                            + PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*square_table[block[4*xval + G] - possible_colors[1][G]]\
							+ PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[block[4*xval + B] - possible_colors[1][B]];\
				if (pixel_error < best_pixel_error)\
					best_pixel_error = pixel_error;\
				pixel_error = PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*square_table[block[4*xval + R] - possible_colors[2][R]]\
                            + PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*square_table[block[4*xval + G] - possible_colors[2][G]]\
							+ PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[block[4*xval + B] - possible_colors[2][B]];\
				if (pixel_error < best_pixel_error)\
					best_pixel_error = pixel_error;\
			}\
			precalc_err_col0_RGB_adr[xval] = (unsigned int) best_pixel_error;\

#define ONETABLE59RGB_PERCEP(dval) \
		possible_colors[0][R] = clamp_table[color[R] - table59T[dval]+255]-255;\
		possible_colors[0][G] = clamp_table[color[G] - table59T[dval]+255]-255;\
		possible_colors[0][B] = clamp_table[color[B] - table59T[dval]+255]-255;\
		possible_colors[1][R] = color[R]-255;\
		possible_colors[1][G] = color[G]-255;\
		possible_colors[1][B] = color[B]-255;\
		possible_colors[2][R] = clamp_table[color[R] + table59T[dval]+255]-255;\
		possible_colors[2][G] = clamp_table[color[G] + table59T[dval]+255]-255;\
		possible_colors[2][B] = clamp_table[color[B] + table59T[dval]+255]-255;\
		precalc_err_col0_RGB_adr = &precalc_err_col0_RGB[(colorRGB444_packed*8 + dval)*16];\
		/* Loop block */\
		/* unroll loop for (int x = 0; x < 16; x++) */\
		{\
			ONEPOINT59RGB_PERCEP(0)\
			ONEPOINT59RGB_PERCEP(1)\
			ONEPOINT59RGB_PERCEP(2)\
			ONEPOINT59RGB_PERCEP(3)\
			ONEPOINT59RGB_PERCEP(4)\
			ONEPOINT59RGB_PERCEP(5)\
			ONEPOINT59RGB_PERCEP(6)\
			ONEPOINT59RGB_PERCEP(7)\
			ONEPOINT59RGB_PERCEP(8)\
			ONEPOINT59RGB_PERCEP(9)\
			ONEPOINT59RGB_PERCEP(10)\
			ONEPOINT59RGB_PERCEP(11)\
			ONEPOINT59RGB_PERCEP(12)\
			ONEPOINT59RGB_PERCEP(13)\
			ONEPOINT59RGB_PERCEP(14)\
			ONEPOINT59RGB_PERCEP(15)\
		}\

	color[R] = (((colorRGB444_packed >> 8) ) << 4) | ((colorRGB444_packed >> 8) ) ;
	color[G] = (((colorRGB444_packed >> 4) & 0xf) << 4) | ((colorRGB444_packed >> 4) & 0xf) ;
	color[B] = (((colorRGB444_packed) & 0xf) << 4) | ((colorRGB444_packed) & 0xf) ;
	
	/* Test all distances */
	/* unroll loop for (uint8 d = 0; d < 8; ++d) */
	{
		ONETABLE59RGB_PERCEP(0)
		ONETABLE59RGB_PERCEP(1)
		ONETABLE59RGB_PERCEP(2)
		ONETABLE59RGB_PERCEP(3)
		ONETABLE59RGB_PERCEP(4)
		ONETABLE59RGB_PERCEP(5)
		ONETABLE59RGB_PERCEP(6)
		ONETABLE59RGB_PERCEP(7)
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates a table used in exhaustive compression of the T-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcError59T_col0_RGB(uint8* block, int colorRGB444_packed, unsigned int *precalc_err_col0_RGB)
{
	unsigned int block_error = 0, 
	  	     	 best_block_error = MAXIMUM_ERROR, 
			     pixel_error, 
		         best_pixel_error;
	uint8 color[3];
	int possible_colors[3][3];
	unsigned int *precalc_err_col0_RGB_adr;

#define ONEPOINT59RGB(xval) \
			/* Loop possible block colors */\
			/* unroll loop for (uint8 c = 0; c < 3; c++) */\
			{\
				best_pixel_error = square_table[block[4*xval + R] - possible_colors[0][R]]\
                            + square_table[block[4*xval + G] - possible_colors[0][G]] \
							+ square_table[block[4*xval + B] - possible_colors[0][B]];\
				pixel_error = square_table[block[4*xval + R] - possible_colors[1][R]]\
                            + square_table[block[4*xval + G] - possible_colors[1][G]]\
							+ square_table[block[4*xval + B] - possible_colors[1][B]];\
				if (pixel_error < best_pixel_error)\
					best_pixel_error = pixel_error;\
				pixel_error = square_table[block[4*xval + R] - possible_colors[2][R]]\
                            + square_table[block[4*xval + G] - possible_colors[2][G]]\
							+ square_table[block[4*xval + B] - possible_colors[2][B]];\
				if (pixel_error < best_pixel_error)\
					best_pixel_error = pixel_error;\
			}\
			precalc_err_col0_RGB_adr[xval] = (unsigned int) best_pixel_error;\

#define ONETABLE59RGB(dval) \
		possible_colors[0][R] = clamp_table[color[R] - table59T[dval]+255]-255;\
		possible_colors[0][G] = clamp_table[color[G] - table59T[dval]+255]-255;\
		possible_colors[0][B] = clamp_table[color[B] - table59T[dval]+255]-255;\
		possible_colors[1][R] = color[R]-255;\
		possible_colors[1][G] = color[G]-255;\
		possible_colors[1][B] = color[B]-255;\
		possible_colors[2][R] = clamp_table[color[R] + table59T[dval]+255]-255;\
		possible_colors[2][G] = clamp_table[color[G] + table59T[dval]+255]-255;\
		possible_colors[2][B] = clamp_table[color[B] + table59T[dval]+255]-255;\
		precalc_err_col0_RGB_adr = &precalc_err_col0_RGB[(colorRGB444_packed*8 + dval)*16];\
		/* Loop block */\
		/* unroll loop for (int x = 0; x < 16; x++) */\
		{\
			ONEPOINT59RGB(0)\
			ONEPOINT59RGB(1)\
			ONEPOINT59RGB(2)\
			ONEPOINT59RGB(3)\
			ONEPOINT59RGB(4)\
			ONEPOINT59RGB(5)\
			ONEPOINT59RGB(6)\
			ONEPOINT59RGB(7)\
			ONEPOINT59RGB(8)\
			ONEPOINT59RGB(9)\
			ONEPOINT59RGB(10)\
			ONEPOINT59RGB(11)\
			ONEPOINT59RGB(12)\
			ONEPOINT59RGB(13)\
			ONEPOINT59RGB(14)\
			ONEPOINT59RGB(15)\
		}\

	color[R] = (((colorRGB444_packed >> 8) ) << 4) | ((colorRGB444_packed >> 8) ) ;
	color[G] = (((colorRGB444_packed >> 4) & 0xf) << 4) | ((colorRGB444_packed >> 4) & 0xf) ;
	color[B] = (((colorRGB444_packed) & 0xf) << 4) | ((colorRGB444_packed) & 0xf) ;

	/* Test all distances */
	/* unroll loop for (uint8 d = 0; d < 8; ++d) */
	{
		ONETABLE59RGB(0)
		ONETABLE59RGB(1)
		ONETABLE59RGB(2)
		ONETABLE59RGB(3)
		ONETABLE59RGB(4)
		ONETABLE59RGB(5)
		ONETABLE59RGB(6)
		ONETABLE59RGB(7)
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates a table used in exhaustive compression of the T-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcError59T_col1_RGBpercep1000(uint8* block, int colorRGB444_packed, unsigned int *precalc_err_col1_RGB)
{
	unsigned int pixel_error;
	int diff[3];
	uint8 colorRGB[3];

	colorRGB[0] = ((colorRGB444_packed >> 8) & 0xf)*17;
	colorRGB[1] = ((colorRGB444_packed >> 4) & 0xf)*17;
	colorRGB[2] = ((colorRGB444_packed >> 0) & 0xf)*17;

	// Loop block
	for (int x = 0; x < 16; x++)
	{
		diff[R] = block[4*x + R] - colorRGB[R];
		diff[G] = block[4*x + G] - colorRGB[G];
		diff[B] = block[4*x + B] - colorRGB[B];

		pixel_error = PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(diff[R]) + PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*SQUARE(diff[G]) + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*SQUARE(diff[B]);
		
		precalc_err_col1_RGB[(colorRGB444_packed)*16 + x] = (unsigned int) pixel_error;
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates a table used in exhaustive compression of the T-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcError59T_col1_RGB(uint8* block, int colorRGB444_packed, unsigned int *precalc_err_col1_RGB)
{
	unsigned int pixel_error;
	int diff[3];
	uint8 colorRGB[3];

	colorRGB[0] = ((colorRGB444_packed >> 8) & 0xf)*17;
	colorRGB[1] = ((colorRGB444_packed >> 4) & 0xf)*17;
	colorRGB[2] = ((colorRGB444_packed >> 0) & 0xf)*17;

	// Loop block
	for (int x = 0; x < 16; x++)
	{
		diff[R] = block[4*x + R] - colorRGB[R];
		diff[G] = block[4*x + G] - colorRGB[G];
		diff[B] = block[4*x + B] - colorRGB[B];

		pixel_error = SQUARE(diff[R]) + SQUARE(diff[G]) + SQUARE(diff[B]);
		precalc_err_col1_RGB[(colorRGB444_packed)*16 + x] = (unsigned int) pixel_error;
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Calculate a minimal error for the T-mode when compressing exhaustively.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateError59TusingPrecalcRperceptual1000(uint8* block, int *colorsRGB444_packed, unsigned int *precalc_err_col0_R, unsigned int *precalc_err_col1_R, unsigned int best_error_so_far) 
{
	unsigned int	block_error = 0, 
					best_block_error = MAXERR1000;

	unsigned int *pixel_error_col0_base_adr;
	unsigned int *pixel_error_col0_adr, *pixel_error_col1_adr;

#define FIRSTCHOICE59R_PERCEP\
			if(*pixel_error_col0_adr < *pixel_error_col1_adr)\
				block_error = *pixel_error_col0_adr;\
			else\
				block_error = *pixel_error_col1_adr;\

#define CHOICE59R_PERCEP(xval)\
			if(pixel_error_col0_adr[xval] < pixel_error_col1_adr[xval])\
				block_error += pixel_error_col0_adr[xval];\
			else\
				block_error += pixel_error_col1_adr[xval];\

#define ONETABLE59R_PERCEP(dval) \
		pixel_error_col0_adr = &pixel_error_col0_base_adr[dval*16];\
		/* unroll loop for(int x = 0; block_error < best_error_so_far && x<16; x++) */\
		{\
			FIRSTCHOICE59R_PERCEP\
			if( block_error < best_error_so_far)\
			{\
				CHOICE59R_PERCEP(1)\
				if( block_error < best_error_so_far)\
				{\
					CHOICE59R_PERCEP(2)\
					CHOICE59R_PERCEP(3)\
					if( block_error < best_error_so_far)\
					{\
						CHOICE59R_PERCEP(4)\
						CHOICE59R_PERCEP(5)\
						if( block_error < best_error_so_far)\
						{\
							CHOICE59R_PERCEP(6)\
							CHOICE59R_PERCEP(7)\
							if( block_error < best_error_so_far)\
							{\
								CHOICE59R_PERCEP(8)\
								CHOICE59R_PERCEP(9)\
								if( block_error < best_error_so_far)\
								{\
									CHOICE59R_PERCEP(10)\
									CHOICE59R_PERCEP(11)\
									if( block_error < best_error_so_far)\
									{\
										CHOICE59R_PERCEP(12)\
										CHOICE59R_PERCEP(13)\
										if( block_error < best_error_so_far)\
										{\
											CHOICE59R_PERCEP(14)\
											CHOICE59R_PERCEP(15)\
										}\
									}\
								}\
							}\
						}\
					}\
				}\
			}\
		}\
		if (block_error < best_block_error)\
			best_block_error = block_error;\
	
	pixel_error_col0_base_adr = &precalc_err_col0_R[((colorsRGB444_packed[0]>>8)*8)*16];
	pixel_error_col1_adr = &precalc_err_col1_R[((colorsRGB444_packed[1]>>8))*16];

	// Test all distances
	/* unroll loop for (uint8 d = 0; d < 8; d++) */
	{
		ONETABLE59R_PERCEP(0)
		ONETABLE59R_PERCEP(1)
		ONETABLE59R_PERCEP(2)
		ONETABLE59R_PERCEP(3)
		ONETABLE59R_PERCEP(4)
		ONETABLE59R_PERCEP(5)
		ONETABLE59R_PERCEP(6)
		ONETABLE59R_PERCEP(7)
	}
	return best_block_error;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Calculate a minimal error for the T-mode when compressing exhaustively.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateError59TusingPrecalcR(uint8* block, int *colorsRGB444_packed, unsigned int *precalc_err_col0_R, unsigned int *precalc_err_col1_R, unsigned int best_error_so_far) 
{
	unsigned int	block_error = 0, 
					best_block_error = MAXIMUM_ERROR;

	unsigned int *pixel_error_col0_base_adr;
	unsigned int *pixel_error_col0_adr, *pixel_error_col1_adr;

#define FIRSTCHOICE59R\
			if(*pixel_error_col0_adr < *pixel_error_col1_adr)\
				block_error = *pixel_error_col0_adr;\
			else\
				block_error = *pixel_error_col1_adr;\

#define CHOICE59R(xval)\
			if(pixel_error_col0_adr[xval] < pixel_error_col1_adr[xval])\
				block_error += pixel_error_col0_adr[xval];\
			else\
				block_error += pixel_error_col1_adr[xval];\

#define ONETABLE59R(dval) \
		pixel_error_col0_adr = &pixel_error_col0_base_adr[dval*16];\
		/* unroll loop for(int x = 0; block_error < best_error_so_far && x<16; x++) */\
		{\
			FIRSTCHOICE59R\
			if( block_error < best_error_so_far)\
			{\
				CHOICE59R(1)\
				if( block_error < best_error_so_far)\
				{\
					CHOICE59R(2)\
					CHOICE59R(3)\
					if( block_error < best_error_so_far)\
					{\
						CHOICE59R(4)\
						CHOICE59R(5)\
						if( block_error < best_error_so_far)\
						{\
							CHOICE59R(6)\
							CHOICE59R(7)\
							if( block_error < best_error_so_far)\
							{\
								CHOICE59R(8)\
								CHOICE59R(9)\
								if( block_error < best_error_so_far)\
								{\
									CHOICE59R(10)\
									CHOICE59R(11)\
									if( block_error < best_error_so_far)\
									{\
										CHOICE59R(12)\
										CHOICE59R(13)\
										if( block_error < best_error_so_far)\
										{\
											CHOICE59R(14)\
											CHOICE59R(15)\
										}\
									}\
								}\
							}\
						}\
					}\
				}\
			}\
		}\
		if (block_error < best_block_error)\
			best_block_error = block_error;\
	
	pixel_error_col0_base_adr = &precalc_err_col0_R[((colorsRGB444_packed[0]>>8)*8)*16];
	pixel_error_col1_adr = &precalc_err_col1_R[((colorsRGB444_packed[1]>>8))*16];


	// Test all distances
	/* unroll loop for (uint8 d = 0; d < 8; d++) */
	{
		ONETABLE59R(0)
		ONETABLE59R(1)
		ONETABLE59R(2)
		ONETABLE59R(3)
		ONETABLE59R(4)
		ONETABLE59R(5)
		ONETABLE59R(6)
		ONETABLE59R(7)
	}
	
	return best_block_error;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Calculate a minimal error for the T-mode when compressing exhaustively.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateError59TusingPrecalcRGperceptual1000(uint8* block, int *colorsRGB444_packed, unsigned int *precalc_err_col0_RG, unsigned int *precalc_err_col1_RG, unsigned int best_error_so_far) 
{
	unsigned int	block_error = 0, 
					best_block_error = MAXERR1000;

	unsigned int *pixel_error_col0_adr, *pixel_error_col1_adr;
	unsigned int *pixel_error_col0_base_adr;

#define FIRSTCHOICE59RG_PERCEP \
		if(*pixel_error_col0_adr < *pixel_error_col1_adr)\
			block_error = *pixel_error_col0_adr;\
		else\
			block_error = *pixel_error_col1_adr;\


#define CHOICE59RG_PERCEP(xval) \
		if(pixel_error_col0_adr[xval] < pixel_error_col1_adr[xval])\
			block_error += pixel_error_col0_adr[xval];\
		else\
			block_error += pixel_error_col1_adr[xval];\

#define ONETABLE59RG_PERCEP(dval)\
		pixel_error_col0_adr = &pixel_error_col0_base_adr[dval*16];\
		/* unroll loop for(int x = 0; block_error < best_error_so_far && x<16; x++) */\
		{\
			FIRSTCHOICE59RG_PERCEP\
			if( block_error < best_error_so_far)\
			{\
				CHOICE59RG_PERCEP(1)\
				if( block_error < best_error_so_far)\
				{\
					CHOICE59RG_PERCEP(2)\
					CHOICE59RG_PERCEP(3)\
					if( block_error < best_error_so_far)\
					{\
						CHOICE59RG_PERCEP(4)\
						CHOICE59RG_PERCEP(5)\
						if( block_error < best_error_so_far)\
						{\
							CHOICE59RG_PERCEP(6)\
							CHOICE59RG_PERCEP(7)\
							if( block_error < best_error_so_far)\
							{\
								CHOICE59RG_PERCEP(8)\
								CHOICE59RG_PERCEP(9)\
								if( block_error < best_error_so_far)\
								{\
									CHOICE59RG_PERCEP(10)\
									CHOICE59RG_PERCEP(11)\
									if( block_error < best_error_so_far)\
									{\
										CHOICE59RG_PERCEP(12)\
										CHOICE59RG_PERCEP(13)\
										if( block_error < best_error_so_far)\
										{\
											CHOICE59RG_PERCEP(14)\
											CHOICE59RG_PERCEP(15)\
										}\
									}\
								}\
							}\
						}\
					}\
				}\
			}\
		}\
		if (block_error < best_block_error)\
			best_block_error = block_error;\


	pixel_error_col0_base_adr = &precalc_err_col0_RG[((colorsRGB444_packed[0]>>4)*8)*16];
	pixel_error_col1_adr = &precalc_err_col1_RG[((colorsRGB444_packed[1]>>4))*16];

	// Test all distances
	/* unroll loop for (uint8 d = 0; d < 8; d++) */
	{

		ONETABLE59RG_PERCEP(0)
		ONETABLE59RG_PERCEP(1)
		ONETABLE59RG_PERCEP(2)
		ONETABLE59RG_PERCEP(3)
		ONETABLE59RG_PERCEP(4)
		ONETABLE59RG_PERCEP(5)
		ONETABLE59RG_PERCEP(6)
		ONETABLE59RG_PERCEP(7)
	}
	return best_block_error;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Calculate a minimal error for the T-mode when compressing exhaustively.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateError59TusingPrecalcRG(uint8* block, int *colorsRGB444_packed, unsigned int *precalc_err_col0_RG, unsigned int *precalc_err_col1_RG, unsigned int best_error_so_far) 
{
	unsigned int	block_error = 0, 
					best_block_error = MAXIMUM_ERROR;

	unsigned int *pixel_error_col0_adr, *pixel_error_col1_adr;
	unsigned int *pixel_error_col0_base_adr;

#define FIRSTCHOICE59RG \
		if(*pixel_error_col0_adr < *pixel_error_col1_adr)\
			block_error = *pixel_error_col0_adr;\
		else\
			block_error = *pixel_error_col1_adr;\

#define CHOICE59RG(xval) \
		if(pixel_error_col0_adr[xval] < pixel_error_col1_adr[xval])\
			block_error += pixel_error_col0_adr[xval];\
		else\
			block_error += pixel_error_col1_adr[xval];\

#define ONETABLE59RG(dval)\
		pixel_error_col0_adr = &pixel_error_col0_base_adr[dval*16];\
		/* unroll loop for(int x = 0; block_error < best_error_so_far && x<16; x++) */\
		{\
			FIRSTCHOICE59RG\
			if( block_error < best_error_so_far)\
			{\
				CHOICE59RG(1)\
				if( block_error < best_error_so_far)\
				{\
					CHOICE59RG(2)\
					CHOICE59RG(3)\
					if( block_error < best_error_so_far)\
					{\
						CHOICE59RG(4)\
						CHOICE59RG(5)\
						if( block_error < best_error_so_far)\
						{\
							CHOICE59RG(6)\
							CHOICE59RG(7)\
							if( block_error < best_error_so_far)\
							{\
								CHOICE59RG(8)\
								CHOICE59RG(9)\
								if( block_error < best_error_so_far)\
								{\
									CHOICE59RG(10)\
									CHOICE59RG(11)\
									if( block_error < best_error_so_far)\
									{\
										CHOICE59RG(12)\
										CHOICE59RG(13)\
										if( block_error < best_error_so_far)\
										{\
											CHOICE59RG(14)\
											CHOICE59RG(15)\
										}\
									}\
								}\
							}\
						}\
					}\
				}\
			}\
		}\
		if (block_error < best_block_error)\
			best_block_error = block_error;\

	pixel_error_col0_base_adr = &precalc_err_col0_RG[((colorsRGB444_packed[0]>>4)*8)*16];
	pixel_error_col1_adr = &precalc_err_col1_RG[((colorsRGB444_packed[1]>>4))*16];

	// Test all distances
	/* unroll loop for (uint8 d = 0; d < 8; d++) */
	{
		ONETABLE59RG(0)
		ONETABLE59RG(1)
		ONETABLE59RG(2)
		ONETABLE59RG(3)
		ONETABLE59RG(4)
		ONETABLE59RG(5)
		ONETABLE59RG(6)
		ONETABLE59RG(7)
	}
	return best_block_error;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Calculate a minimal error for the T-mode when compressing exhaustively.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateError59TusingPrecalcRGBperceptual1000(uint8* block, int *colorsRGB444_packed, unsigned int *precalc_err_col0_RGB, unsigned int *precalc_err_col1_RGB, unsigned int best_error_so_far) 
{
	unsigned int	block_error = 0, 
					      best_block_error = MAXERR1000;
	unsigned int *pixel_error_col0_adr, *pixel_error_col1_adr;
	unsigned int *pixel_error_col0_base_adr;

#define FIRSTCHOICE59_PERCEP \
	if(*pixel_error_col0_adr < *pixel_error_col1_adr)\
		block_error = *pixel_error_col0_adr;\
	else\
		block_error = *pixel_error_col1_adr;\

#define CHOICE59_PERCEP(xval) \
	if(pixel_error_col0_adr[xval] < pixel_error_col1_adr[xval])\
		block_error += pixel_error_col0_adr[xval];\
	else\
		block_error += pixel_error_col1_adr[xval];\

#define ONETABLE59T_PERCEP(dval)\
		pixel_error_col0_adr = &pixel_error_col0_base_adr[dval*16];\
		/* unroll for(int x = 0; block_error < best_error_so_far && x<16; x++) */\
		{\
			FIRSTCHOICE59_PERCEP\
			if( block_error < best_error_so_far)\
			{\
				CHOICE59_PERCEP(1)\
				if( block_error < best_error_so_far)\
				{\
					CHOICE59_PERCEP(2)\
					CHOICE59_PERCEP(3)\
					if( block_error < best_error_so_far)\
					{\
						CHOICE59_PERCEP(4)\
						CHOICE59_PERCEP(5)\
						if( block_error < best_error_so_far)\
						{\
							CHOICE59_PERCEP(6)\
							CHOICE59_PERCEP(7)\
							if( block_error < best_error_so_far)\
							{\
								CHOICE59_PERCEP(8)\
								CHOICE59_PERCEP(9)\
								if( block_error < best_error_so_far)\
								{\
									CHOICE59_PERCEP(10)\
									CHOICE59_PERCEP(11)\
									if( block_error < best_error_so_far)\
									{\
										CHOICE59_PERCEP(12)\
										CHOICE59_PERCEP(13)\
										if( block_error < best_error_so_far)\
										{\
											CHOICE59_PERCEP(14)\
											CHOICE59_PERCEP(15)\
										}\
									}\
								}\
							}\
						}\
					}\
				}\
			}\
		}\
		if (block_error < best_block_error)\
			best_block_error = block_error;\

	pixel_error_col1_adr = &precalc_err_col1_RGB[(colorsRGB444_packed[1])*16];
	pixel_error_col0_base_adr = &precalc_err_col0_RGB[(colorsRGB444_packed[0]*8)*16];

	// Test all distances
	/* unroll loop for (uint8 d = 0; d < 8; d++)*/
	{
		ONETABLE59T_PERCEP(0)
		ONETABLE59T_PERCEP(1)
		ONETABLE59T_PERCEP(2)
		ONETABLE59T_PERCEP(3)
		ONETABLE59T_PERCEP(4)
		ONETABLE59T_PERCEP(5)
		ONETABLE59T_PERCEP(6)
		ONETABLE59T_PERCEP(7)
	}
	return best_block_error;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Calculate a minimal error for the T-mode when compressing exhaustively.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateError59TusingPrecalcRGB(uint8* block, int *colorsRGB444_packed, unsigned int *precalc_err_col0_RGB, unsigned int *precalc_err_col1_RGB, unsigned int best_error_so_far) 
{
	unsigned int	block_error = 0, 
					      best_block_error = MAXIMUM_ERROR;
	unsigned int *pixel_error_col0_adr, *pixel_error_col1_adr;
	unsigned int *pixel_error_col0_base_adr;

#define FIRSTCHOICE59 \
	if(*pixel_error_col0_adr < *pixel_error_col1_adr)\
		block_error = *pixel_error_col0_adr;\
	else\
		block_error = *pixel_error_col1_adr;\

#define CHOICE59(xval) \
	if(pixel_error_col0_adr[xval] < pixel_error_col1_adr[xval])\
		block_error += pixel_error_col0_adr[xval];\
	else\
		block_error += pixel_error_col1_adr[xval];\

#define ONETABLE59T(dval)\
		pixel_error_col0_adr = &pixel_error_col0_base_adr[dval*16];\
		/* unroll for(int x = 0; block_error < best_error_so_far && x<16; x++) */\
		{\
			FIRSTCHOICE59\
			if( block_error < best_error_so_far)\
			{\
				CHOICE59(1)\
				if( block_error < best_error_so_far)\
				{\
					CHOICE59(2)\
					CHOICE59(3)\
					if( block_error < best_error_so_far)\
					{\
						CHOICE59(4)\
						CHOICE59(5)\
						if( block_error < best_error_so_far)\
						{\
							CHOICE59(6)\
							CHOICE59(7)\
							if( block_error < best_error_so_far)\
							{\
								CHOICE59(8)\
								CHOICE59(9)\
								if( block_error < best_error_so_far)\
								{\
									CHOICE59(10)\
									CHOICE59(11)\
									if( block_error < best_error_so_far)\
									{\
										CHOICE59(12)\
										CHOICE59(13)\
										if( block_error < best_error_so_far)\
										{\
											CHOICE59(14)\
											CHOICE59(15)\
										}\
									}\
								}\
							}\
						}\
					}\
				}\
			}\
		}\
		if (block_error < best_block_error)\
			best_block_error = block_error;\

	pixel_error_col1_adr = &precalc_err_col1_RGB[(colorsRGB444_packed[1])*16];
	pixel_error_col0_base_adr = &precalc_err_col0_RGB[(colorsRGB444_packed[0]*8)*16];

	// Test all distances
	/* unroll loop for (uint8 d = 0; d < 8; d++)*/
	{
		ONETABLE59T(0)
		ONETABLE59T(1)
		ONETABLE59T(2)
		ONETABLE59T(3)
		ONETABLE59T(4)
		ONETABLE59T(5)
		ONETABLE59T(6)
		ONETABLE59T(7)
	}
	return best_block_error;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// The below code should compress the block to 59 bits. 
// This is supposed to match the first of the three modes in TWOTIMER.
//
//|63 62 61 60 59|58 57 56 55|54 53 52 51|50 49 48 47|46 45 44 43|42 41 40 39|38 37 36 35|34 33 32|
//|----empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|--dist--|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
//
// Note that this method might not return the best possible compression for the T-mode. It will only do so if the best possible T-representation
// is less than best_error_so_far. To guarantee that the best possible T-representation is found, the function should be called using
// best_error_so_far = 255*255*3*16, which is the maximum error for a block. 
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int compressBlockTHUMB59TExhaustivePerceptual(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2, unsigned int best_error_so_far) 
{
	uint8 colorsRGB444[2][3];
	unsigned int pixel_indices;
	uint8 distance;

	uint8 block[4*4*4];

	unsigned int *precalc_err_col0_RGB;
	unsigned int *precalc_err_col1_RGB;
	unsigned int *precalc_err_col0_RG;
	unsigned int *precalc_err_col1_RG;
	unsigned int *precalc_err_col0_R;
	unsigned int *precalc_err_col1_R;

	int colorRGB444_packed;

	int colorsRGB444_packed[2];
	int best_colorsRGB444_packed[2];

	unsigned int best_error_using_Tmode;

	// First compress block quickly to a resonable quality so that we can
	// rule out all blocks that are of worse quality than that. 
	best_error_using_Tmode = (unsigned int) compressBlockTHUMB59TFastestOnlyColorPerceptual1000(img, width, height, startx, starty, best_colorsRGB444_packed);
	if(best_error_using_Tmode < best_error_so_far)
		best_error_so_far = best_error_using_Tmode;

	// Color numbering is reversed between the above function and the precalc functions below; swap colors.
	int temp = best_colorsRGB444_packed[0];
	best_colorsRGB444_packed[0] = best_colorsRGB444_packed[1];
	best_colorsRGB444_packed[1] = temp;

	int xx,yy,count = 0;

	// Use 4 bytes per pixel to make it 32-word aligned.
	for(xx = 0; xx<4; xx++)
	{
		for(yy=0; yy<4; yy++)
		{
			block[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block[(count)*4+3] = 0;
			count++;
		}
	}

	// Precalculate error for color 0 (which produces the upper half of the T)
	precalc_err_col0_RGB = (unsigned int*) malloc(4096*8*16*sizeof(unsigned int));
	if(!precalc_err_col0_RGB){printf("Out of memory allocating \n");exit(1);}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed++)
	{
		precalcError59T_col0_RGBpercep1000(block, colorRGB444_packed, precalc_err_col0_RGB);
	}

	// Precalculate error for color 1 (which produces the lower half of the T -- the lone color)
	precalc_err_col1_RGB = (unsigned int*) malloc(4096*16*sizeof(unsigned int));
	if(!precalc_err_col1_RGB){printf("Out of memory allocating \n");exit(1);}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed++)
	{
		precalcError59T_col1_RGBpercep1000(block, colorRGB444_packed, precalc_err_col1_RGB);
	}

	precalc_err_col0_RG = (unsigned int*) malloc(16*16*8*16*sizeof(unsigned int));
	if(!precalc_err_col0_RG){printf("Out of memory allocating \n");exit(1);}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed+=16)
	{
		precalcError59T_col0_RGpercep1000(block, colorRGB444_packed, precalc_err_col0_RG);
	}

	precalc_err_col1_RG = (unsigned int*) malloc(16*16*16*sizeof(unsigned int));
	if(!precalc_err_col1_RG){printf("Out of memory allocating \n");exit(1);}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed+=16)
	{
		precalcError59T_col1_RGpercep1000(block, colorRGB444_packed, precalc_err_col1_RG);
	}

	precalc_err_col0_R = (unsigned int*) malloc(16*8*16*sizeof(unsigned int));
	if(!precalc_err_col0_R){printf("Out of memory allocating \n");exit(1);}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed+=16*16)
	{
		precalcError59T_col0_Rpercep1000(block, colorRGB444_packed, precalc_err_col0_R);
	}

	precalc_err_col1_R = (unsigned int*) malloc(16*16*sizeof(unsigned int));
	if(!precalc_err_col1_R){printf("Out of memory allocating \n");exit(1);}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed+=16*16)
	{
		precalcError59T_col1_Rpercep1000(block, colorRGB444_packed, precalc_err_col1_R);
	}

	unsigned int error;
	unsigned int avoided = 0;
	unsigned int notavoided = 0;

	for(colorsRGB444[0][0] = 0; colorsRGB444[0][0] < 16; colorsRGB444[0][0]++)
	{
		for(colorsRGB444[1][0] = 0; colorsRGB444[1][0] < 16; colorsRGB444[1][0]++)
		{
			colorsRGB444_packed[0] = (colorsRGB444[0][0] << 8);
			colorsRGB444_packed[1] = (colorsRGB444[1][0] << 8);
			error = calculateError59TusingPrecalcRperceptual1000(block, colorsRGB444_packed, precalc_err_col0_R, precalc_err_col1_R, best_error_so_far);
			if(error < best_error_so_far)
			{
				notavoided = notavoided + 1;
				for(colorsRGB444[0][1] = 0; colorsRGB444[0][1] < 16; colorsRGB444[0][1]++)
				{
					colorsRGB444_packed[0] = (colorsRGB444[0][0] << 8) + (colorsRGB444[0][1] <<4);
					for(colorsRGB444[1][1] = 0; colorsRGB444[1][1] < 16; colorsRGB444[1][1]++)
					{
						colorsRGB444_packed[1] = (colorsRGB444[1][0] << 8) + (colorsRGB444[1][1] <<4);
						error = calculateError59TusingPrecalcRGperceptual1000(block, colorsRGB444_packed, precalc_err_col0_RG, precalc_err_col1_RG, best_error_so_far);
						if(error < best_error_so_far)
						{
							for(colorsRGB444[0][2] = 0; colorsRGB444[0][2] < 16; colorsRGB444[0][2]++)
							{
								colorsRGB444_packed[0] = (colorsRGB444[0][0] << 8) + (colorsRGB444[0][1] <<4) + colorsRGB444[0][2];
								for(colorsRGB444[1][2] = 0; colorsRGB444[1][2] < 16; colorsRGB444[1][2]++)
								{
									colorsRGB444_packed[1] = (colorsRGB444[1][0] << 8) + (colorsRGB444[1][1] <<4) + colorsRGB444[1][2];
									error = calculateError59TusingPrecalcRGBperceptual1000(block, colorsRGB444_packed, precalc_err_col0_RGB, precalc_err_col1_RGB, best_error_so_far);

									if(error < best_error_so_far)
									{
										best_error_so_far = error;
										best_error_using_Tmode = error;
										best_colorsRGB444_packed[0] = colorsRGB444_packed[0];
										best_colorsRGB444_packed[1] = colorsRGB444_packed[1];
									}
								}
							}
						}
					}
				}
			}
		}
	}

	free(precalc_err_col0_RGB);
	free(precalc_err_col1_RGB);
	free(precalc_err_col0_RG);
	free(precalc_err_col1_RG);
	free(precalc_err_col0_R);
	free(precalc_err_col1_R);

	// We have got the two best colors. Now find the best distance and pixel indices. 

	// Color numbering are reversed between precalc and noSwap
	colorsRGB444[0][0] = (best_colorsRGB444_packed[1] >> 8) & 0xf;
	colorsRGB444[0][1] = (best_colorsRGB444_packed[1] >> 4) & 0xf;
	colorsRGB444[0][2] = (best_colorsRGB444_packed[1] >> 0) & 0xf;
	
	colorsRGB444[1][0] = (best_colorsRGB444_packed[0] >> 8) & 0xf;
	colorsRGB444[1][1] = (best_colorsRGB444_packed[0] >> 4) & 0xf;
	colorsRGB444[1][2] = (best_colorsRGB444_packed[0] >> 0) & 0xf;

	calculateError59TnoSwapPerceptual1000(img, width, startx, starty, colorsRGB444, distance, pixel_indices);			

	// Put the compress params into the compression block 
	packBlock59T(colorsRGB444, distance, pixel_indices, compressed1, compressed2);

	return best_error_using_Tmode;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// The below code should compress the block to 59 bits. 
// This is supposed to match the first of the three modes in TWOTIMER.
//
//|63 62 61 60 59|58 57 56 55|54 53 52 51|50 49 48 47|46 45 44 43|42 41 40 39|38 37 36 35|34 33 32|
//|----empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|--dist--|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
//
// Note that this method might not return the best possible compression for the T-mode. It will only do so if the best possible T-representation
// is less than best_error_so_far. To guarantee that the best possible T-representation is found, the function should be called using
// best_error_so_far = 255*255*3*16, which is the maximum error for a block. 
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int compressBlockTHUMB59TExhaustive(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2, unsigned int best_error_so_far) 
{
	uint8 colorsRGB444[2][3];
	unsigned int pixel_indices;
	uint8 distance;

	uint8 block[4*4*4];

	unsigned int *precalc_err_col0_RGB;
	unsigned int *precalc_err_col1_RGB;
	unsigned int *precalc_err_col0_RG;
	unsigned int *precalc_err_col1_RG;
	unsigned int *precalc_err_col0_R;
	unsigned int *precalc_err_col1_R;

	int colorRGB444_packed;

	int colorsRGB444_packed[2];
	int best_colorsRGB444_packed[2];

	unsigned int best_error_using_Tmode;

	// First compress block quickly to a resonable quality so that we can
	// rule out all blocks that are of worse quality than that. 
	best_error_using_Tmode = (unsigned int) compressBlockTHUMB59TFastestOnlyColor(img, width, height, startx, starty, best_colorsRGB444_packed);
	if(best_error_using_Tmode < best_error_so_far)
		best_error_so_far = best_error_using_Tmode;


	// Colors numbering is reversed between the above function and the precalc below:
	int temp = best_colorsRGB444_packed[0];
	best_colorsRGB444_packed[0] = best_colorsRGB444_packed[1];
	best_colorsRGB444_packed[1] = temp;

	int xx,yy,count = 0;

	// Use 4 bytes per pixel to make it 32-word aligned.
	for(xx = 0; xx<4; xx++)
	{
		for(yy=0; yy<4; yy++)
		{
			block[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block[(count)*4+3] = 0;
			count++;
		}
	}

	// Precalculate error for color 0 (which produces the upper half of the T)
	precalc_err_col0_RGB = (unsigned int*) malloc(4096*8*16*sizeof(unsigned int));
	if(!precalc_err_col0_RGB){printf("Out of memory allocating \n");exit(1);}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed++)
	{
		precalcError59T_col0_RGB(block, colorRGB444_packed, precalc_err_col0_RGB);
	}

	// Precalculate error for color 1 (which produces the lower half of the T -- the lone color)
	precalc_err_col1_RGB = (unsigned int*) malloc(4096*16*sizeof(unsigned int));
	if(!precalc_err_col1_RGB){printf("Out of memory allocating \n");exit(1);}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed++)
	{
		precalcError59T_col1_RGB(block, colorRGB444_packed, precalc_err_col1_RGB);
	}

	precalc_err_col0_RG = (unsigned int*) malloc(16*16*8*16*sizeof(unsigned int));
	if(!precalc_err_col0_RG){printf("Out of memory allocating \n");exit(1);}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed+=16)
	{
		precalcError59T_col0_RG(block, colorRGB444_packed, precalc_err_col0_RG);
	}

	precalc_err_col1_RG = (unsigned int*) malloc(16*16*16*sizeof(unsigned int));
	if(!precalc_err_col1_RG){printf("Out of memory allocating \n");exit(1);}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed+=16)
	{
		precalcError59T_col1_RG(block, colorRGB444_packed, precalc_err_col1_RG);
	}

	precalc_err_col0_R = (unsigned int*) malloc(16*8*16*sizeof(unsigned int));
	if(!precalc_err_col0_R){printf("Out of memory allocating \n");exit(1);}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed+=16*16)
	{
		precalcError59T_col0_R(block, colorRGB444_packed, precalc_err_col0_R);
	}

	precalc_err_col1_R = (unsigned int*) malloc(16*16*sizeof(unsigned int));
	if(!precalc_err_col1_R){printf("Out of memory allocating \n");exit(1);}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed+=16*16)
	{
		precalcError59T_col1_R(block, colorRGB444_packed, precalc_err_col1_R);
	}

	unsigned int error;
	unsigned int avoided = 0;
	unsigned int notavoided = 0;

	for(colorsRGB444[0][0] = 0; colorsRGB444[0][0] < 16; colorsRGB444[0][0]++)
	{
		for(colorsRGB444[1][0] = 0; colorsRGB444[1][0] < 16; colorsRGB444[1][0]++)
		{
			colorsRGB444_packed[0] = (colorsRGB444[0][0] << 8);
			colorsRGB444_packed[1] = (colorsRGB444[1][0] << 8);
			error = calculateError59TusingPrecalcR(block, colorsRGB444_packed, precalc_err_col0_R, precalc_err_col1_R, best_error_so_far);
			if(error < best_error_so_far)
			{
				notavoided = notavoided + 1;
				for(colorsRGB444[0][1] = 0; colorsRGB444[0][1] < 16; colorsRGB444[0][1]++)
				{
					colorsRGB444_packed[0] = (colorsRGB444[0][0] << 8) + (colorsRGB444[0][1] <<4);
					for(colorsRGB444[1][1] = 0; colorsRGB444[1][1] < 16; colorsRGB444[1][1]++)
					{
						colorsRGB444_packed[1] = (colorsRGB444[1][0] << 8) + (colorsRGB444[1][1] <<4);
						error = calculateError59TusingPrecalcRG(block, colorsRGB444_packed, precalc_err_col0_RG, precalc_err_col1_RG, best_error_so_far);
						if(error < best_error_so_far)
						{
							for(colorsRGB444[0][2] = 0; colorsRGB444[0][2] < 16; colorsRGB444[0][2]++)
							{
								colorsRGB444_packed[0] = (colorsRGB444[0][0] << 8) + (colorsRGB444[0][1] <<4) + colorsRGB444[0][2];
								for(colorsRGB444[1][2] = 0; colorsRGB444[1][2] < 16; colorsRGB444[1][2]++)
								{
									colorsRGB444_packed[1] = (colorsRGB444[1][0] << 8) + (colorsRGB444[1][1] <<4) + colorsRGB444[1][2];
									error = calculateError59TusingPrecalcRGB(block, colorsRGB444_packed, precalc_err_col0_RGB, precalc_err_col1_RGB, best_error_so_far);

									if(error < best_error_so_far)
									{
										best_error_so_far = error;
										best_error_using_Tmode = error;
										best_colorsRGB444_packed[0] = colorsRGB444_packed[0];
										best_colorsRGB444_packed[1] = colorsRGB444_packed[1];
									}
								}
							}
						}
					}
				}
			}
		}
	}

	free(precalc_err_col0_RGB);
	free(precalc_err_col1_RGB);
	free(precalc_err_col0_RG);
	free(precalc_err_col1_RG);
	free(precalc_err_col0_R);
	free(precalc_err_col1_R);

	// We have got the two best colors. Now find the best distance and pixel indices. 

	// Color numbering are reversed between precalc and noSwap
	colorsRGB444[0][0] = (best_colorsRGB444_packed[1] >> 8) & 0xf;
	colorsRGB444[0][1] = (best_colorsRGB444_packed[1] >> 4) & 0xf;
	colorsRGB444[0][2] = (best_colorsRGB444_packed[1] >> 0) & 0xf;
	
	colorsRGB444[1][0] = (best_colorsRGB444_packed[0] >> 8) & 0xf;
	colorsRGB444[1][1] = (best_colorsRGB444_packed[0] >> 4) & 0xf;
	colorsRGB444[1][2] = (best_colorsRGB444_packed[0] >> 0) & 0xf;

	calculateError59TnoSwap(img, width, startx, starty, colorsRGB444, distance, pixel_indices);			

	// Put the compress params into the compression block 
	packBlock59T(colorsRGB444, distance, pixel_indices, compressed1, compressed2);

	return best_error_using_Tmode;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates tables used in the exhaustive compression of the H-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcErrorR_58Hperceptual1000(uint8* srcimg, int width, int startx, int starty, uint8 (colorsRGB444)[2][3],int colorRGB444_packed, unsigned int *precalc_errR) 
{
	unsigned int block_error = 0, 
		   best_block_error = MAXERR1000, 
		   pixel_error, 
		   best_pixel_error;
	int diff[3];
	unsigned int pixel_colors;
	uint8 possible_colors[2][3];
	uint8 colors[2][3];
	
	decompressColor(R_BITS58H, G_BITS58H, B_BITS58H, colorsRGB444, colors);

	// Test all distances
	for (uint8 d = 0; d < BINPOW(TABLE_BITS_58H); ++d) 
	{
		possible_colors[0][R] = CLAMP(0,colors[0][R] - table58H[d],255);
		possible_colors[1][R] = CLAMP(0,colors[0][R] + table58H[d],255);

		block_error = 0;	
		pixel_colors = 0;

		// Loop block
		for (size_t y = 0; y < BLOCKHEIGHT; ++y) 
		{
			for (size_t x = 0; x < BLOCKWIDTH; ++x) 
			{
				best_pixel_error = MAXERR1000;

				// Loop possible block colors
				for (uint8 c = 0; c < 2; ++c) 
				{
					diff[R] = srcimg[3*((starty+y)*width+startx+x)+R] - CLAMP(0,possible_colors[c][R],255);

					pixel_error =	PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(diff[R]);

					// Choose best error
					if (pixel_error < best_pixel_error) 
					{
						best_pixel_error = pixel_error;
					} 
				}
				precalc_errR[((colorRGB444_packed>>8)*8 + d)*16 + (y*4)+x] = (unsigned int) best_pixel_error;
			}
		}
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates tables used in the exhaustive compression of the H-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcErrorR_58H(uint8* srcimg, int width, int startx, int starty, uint8 (colorsRGB444)[2][3],int colorRGB444_packed, unsigned int *precalc_errR) 
{
	double block_error = 0, 
		   best_block_error = MAXIMUM_ERROR, 
		   pixel_error, 
		   best_pixel_error;
	int diff[3];
	unsigned int pixel_colors;
	uint8 possible_colors[2][3];
	uint8 colors[2][3];
	
	decompressColor(R_BITS58H, G_BITS58H, B_BITS58H, colorsRGB444, colors);

	// Test all distances
	for (uint8 d = 0; d < BINPOW(TABLE_BITS_58H); ++d) 
	{
		possible_colors[0][R] = CLAMP(0,colors[0][R] - table58H[d],255);
		possible_colors[1][R] = CLAMP(0,colors[0][R] + table58H[d],255);

		block_error = 0;	
		pixel_colors = 0;

		// Loop block
		for (size_t y = 0; y < BLOCKHEIGHT; ++y) 
		{
			for (size_t x = 0; x < BLOCKWIDTH; ++x) 
			{
				best_pixel_error = MAXIMUM_ERROR;

				// Loop possible block colors
				for (uint8 c = 0; c < 2; ++c) 
				{
					diff[R] = srcimg[3*((starty+y)*width+startx+x)+R] - CLAMP(0,possible_colors[c][R],255);

					pixel_error =	weight[R]*SQUARE(diff[R]);

					// Choose best error
					if (pixel_error < best_pixel_error) 
					{
						best_pixel_error = pixel_error;
					} 
				}
				precalc_errR[((colorRGB444_packed>>8)*8 + d)*16 + (y*4)+x] = (unsigned int) best_pixel_error;
			}
		}
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates tables used in the exhaustive compression of the H-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcErrorRG_58Hperceptual1000(uint8* srcimg, int width, int startx, int starty, uint8 (colorsRGB444)[2][3],int colorRGB444_packed, unsigned int *precalc_errRG) 
{
	unsigned int block_error = 0, 
		   best_block_error = MAXERR1000,
		   pixel_error, 
		   best_pixel_error;
	int diff[3];
	unsigned int pixel_colors;
	uint8 possible_colors[2][3];
	uint8 colors[2][3];
	
	decompressColor(R_BITS58H, G_BITS58H, B_BITS58H, colorsRGB444, colors);

	// Test all distances
	for (uint8 d = 0; d < BINPOW(TABLE_BITS_58H); ++d) 
	{
		possible_colors[0][R] = CLAMP(0,colors[0][R] - table58H[d],255);
		possible_colors[0][G] = CLAMP(0,colors[0][G] - table58H[d],255);
		possible_colors[1][R] = CLAMP(0,colors[0][R] + table58H[d],255);
		possible_colors[1][G] = CLAMP(0,colors[0][G] + table58H[d],255);

		block_error = 0;	
		pixel_colors = 0;

		// Loop block
		for (size_t y = 0; y < BLOCKHEIGHT; ++y) 
		{
			for (size_t x = 0; x < BLOCKWIDTH; ++x) 
			{
				best_pixel_error = MAXERR1000;

				// Loop possible block colors
				for (uint8 c = 0; c < 2; ++c) 
				{
					diff[R] = srcimg[3*((starty+y)*width+startx+x)+R] - CLAMP(0,possible_colors[c][R],255);
					diff[G] = srcimg[3*((starty+y)*width+startx+x)+G] - CLAMP(0,possible_colors[c][G],255);

					pixel_error =	PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*SQUARE(diff[R]) +
									PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*SQUARE(diff[G]);

					// Choose best error
					if (pixel_error < best_pixel_error) 
					{
						best_pixel_error = pixel_error;
					} 
				}
				precalc_errRG[((colorRGB444_packed>>4)*8 + d)*16 + (y*4)+x] = (unsigned int) best_pixel_error;
			}
		}
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates tables used in the exhaustive compression of the H-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcErrorRG_58H(uint8* srcimg, int width, int startx, int starty, uint8 (colorsRGB444)[2][3],int colorRGB444_packed, unsigned int *precalc_errRG) 
{
	double block_error = 0, 
		   best_block_error = MAXIMUM_ERROR, 
		   pixel_error, 
		   best_pixel_error;
	int diff[3];
	unsigned int pixel_colors;
	uint8 possible_colors[2][3];
	uint8 colors[2][3];
	
	decompressColor(R_BITS58H, G_BITS58H, B_BITS58H, colorsRGB444, colors);

	// Test all distances
	for (uint8 d = 0; d < BINPOW(TABLE_BITS_58H); ++d) 
	{
		possible_colors[0][R] = CLAMP(0,colors[0][R] - table58H[d],255);
		possible_colors[0][G] = CLAMP(0,colors[0][G] - table58H[d],255);
		possible_colors[1][R] = CLAMP(0,colors[0][R] + table58H[d],255);
		possible_colors[1][G] = CLAMP(0,colors[0][G] + table58H[d],255);

		block_error = 0;	
		pixel_colors = 0;

		// Loop block
		for (size_t y = 0; y < BLOCKHEIGHT; ++y) 
		{
			for (size_t x = 0; x < BLOCKWIDTH; ++x) 
			{
				best_pixel_error = MAXIMUM_ERROR;

				// Loop possible block colors
				for (uint8 c = 0; c < 2; ++c) 
				{
					diff[R] = srcimg[3*((starty+y)*width+startx+x)+R] - CLAMP(0,possible_colors[c][R],255);
					diff[G] = srcimg[3*((starty+y)*width+startx+x)+G] - CLAMP(0,possible_colors[c][G],255);

					pixel_error =	weight[R]*SQUARE(diff[R]) +
									weight[G]*SQUARE(diff[G]);

					// Choose best error
					if (pixel_error < best_pixel_error) 
					{
						best_pixel_error = pixel_error;
					} 
				}
				precalc_errRG[((colorRGB444_packed>>4)*8 + d)*16 + (y*4)+x] = (unsigned int) best_pixel_error;
			}
		}
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates a table used in the exhaustive compression of the H-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcError58Hperceptual1000(uint8* block, uint8 (colorsRGB444)[2][3],int colorRGB444_packed, unsigned int *precalc_err) 
{
	unsigned int pixel_error, 
		   best_pixel_error;
	int possible_colors[2][3];
	uint8 colors[2][3];
	unsigned int *precalc_err_tab;
 	int red_original;
 	int green_original;
    int	blue_original;

#define PRECALC_ONE_58H_PERCEP(qvalue)\
  			red_original = block[qvalue*4];\
  			green_original = block[qvalue*4+1];\
  			blue_original = block[qvalue*4+2];\
			/* unroll loop for (color = 0; color< 2; color++) */\
 	 			best_pixel_error = PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*square_table[(possible_colors[0][R] - red_original)] \
				                 + PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*square_table[(possible_colors[0][G] - green_original)]\
								 + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[(possible_colors[0][B] - blue_original)];\
 	 			pixel_error = PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000*square_table[(possible_colors[1][R] - red_original)]\
	                        + PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000*square_table[(possible_colors[1][G] - green_original)]\
						    + PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000*square_table[(possible_colors[1][B] - blue_original)];\
				if (pixel_error < best_pixel_error)\
					best_pixel_error = pixel_error;\
			/* end unroll loop */\
			precalc_err_tab[qvalue] = best_pixel_error;\

#define PRECALC_ONE_TABLE_58H_PERCEP(dvalue)\
		precalc_err_tab = &precalc_err[((colorRGB444_packed*8)+dvalue)*16];\
		possible_colors[0][R] = CLAMP_LEFT_ZERO(colors[0][R] - table58H[dvalue])+255;\
		possible_colors[0][G] = CLAMP_LEFT_ZERO(colors[0][G] - table58H[dvalue])+255;\
		possible_colors[0][B] = CLAMP_LEFT_ZERO(colors[0][B] - table58H[dvalue])+255;\
		possible_colors[1][R] = CLAMP_RIGHT_255(colors[0][R] + table58H[dvalue])+255;\
		possible_colors[1][G] = CLAMP_RIGHT_255(colors[0][G] + table58H[dvalue])+255;\
 		possible_colors[1][B] = CLAMP_RIGHT_255(colors[0][B] + table58H[dvalue])+255;\
		/* unrolled loop for(q = 0; q<16; q++)*/\
			PRECALC_ONE_58H_PERCEP(0)\
			PRECALC_ONE_58H_PERCEP(1)\
			PRECALC_ONE_58H_PERCEP(2)\
			PRECALC_ONE_58H_PERCEP(3)\
			PRECALC_ONE_58H_PERCEP(4)\
			PRECALC_ONE_58H_PERCEP(5)\
			PRECALC_ONE_58H_PERCEP(6)\
			PRECALC_ONE_58H_PERCEP(7)\
			PRECALC_ONE_58H_PERCEP(8)\
			PRECALC_ONE_58H_PERCEP(9)\
			PRECALC_ONE_58H_PERCEP(10)\
			PRECALC_ONE_58H_PERCEP(11)\
			PRECALC_ONE_58H_PERCEP(12)\
			PRECALC_ONE_58H_PERCEP(13)\
			PRECALC_ONE_58H_PERCEP(14)\
			PRECALC_ONE_58H_PERCEP(15)\
		/* end unroll loop */\

 	colors[0][R] = (colorsRGB444[0][R] << 4) | colorsRGB444[0][R];
 	colors[0][G] = (colorsRGB444[0][G] << 4) | colorsRGB444[0][G];
 	colors[0][B] = (colorsRGB444[0][B] << 4) | colorsRGB444[0][B];

	// Test all distances
	/* unroll loop for (uint8 d = 0; d < 8; ++d) */

		PRECALC_ONE_TABLE_58H_PERCEP(0)
		PRECALC_ONE_TABLE_58H_PERCEP(1)
		PRECALC_ONE_TABLE_58H_PERCEP(2)
		PRECALC_ONE_TABLE_58H_PERCEP(3)
		PRECALC_ONE_TABLE_58H_PERCEP(4)
		PRECALC_ONE_TABLE_58H_PERCEP(5)
		PRECALC_ONE_TABLE_58H_PERCEP(6)
		PRECALC_ONE_TABLE_58H_PERCEP(7)

	/* end unroll loop */
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Precalculates a table used in the exhaustive compression of the H-mode.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void precalcError58H(uint8* block, uint8 (colorsRGB444)[2][3],int colorRGB444_packed, unsigned int *precalc_err) 
{
	unsigned int pixel_error, 
		   best_pixel_error;
	int possible_colors[2][3];
	uint8 colors[2][3];
	unsigned int *precalc_err_tab;
 	int red_original;
 	int green_original;
    int	blue_original;

#define PRECALC_ONE_58H(qvalue)\
  			red_original = block[qvalue*4];\
  			green_original = block[qvalue*4+1];\
  			blue_original = block[qvalue*4+2];\
			/* unroll loop for (color = 0; color< 2; color++) */\
 	 			best_pixel_error = square_table[(possible_colors[0][R] - red_original)] + square_table[(possible_colors[0][G] - green_original)] + square_table[(possible_colors[0][B] - blue_original)];\
 	 			pixel_error = square_table[(possible_colors[1][R] - red_original)] + square_table[(possible_colors[1][G] - green_original)] + square_table[(possible_colors[1][B] - blue_original)];\
				if (pixel_error < best_pixel_error)\
					best_pixel_error = pixel_error;\
			/* end unroll loop */\
			precalc_err_tab[qvalue] = best_pixel_error;\

#define PRECALC_ONE_TABLE_58H(dvalue)\
		precalc_err_tab = &precalc_err[((colorRGB444_packed*8)+dvalue)*16];\
		possible_colors[0][R] = CLAMP_LEFT_ZERO(colors[0][R] - table58H[dvalue])+255;\
		possible_colors[0][G] = CLAMP_LEFT_ZERO(colors[0][G] - table58H[dvalue])+255;\
		possible_colors[0][B] = CLAMP_LEFT_ZERO(colors[0][B] - table58H[dvalue])+255;\
		possible_colors[1][R] = CLAMP_RIGHT_255(colors[0][R] + table58H[dvalue])+255;\
		possible_colors[1][G] = CLAMP_RIGHT_255(colors[0][G] + table58H[dvalue])+255;\
 		possible_colors[1][B] = CLAMP_RIGHT_255(colors[0][B] + table58H[dvalue])+255;\
		/* unrolled loop for(q = 0; q<16; q++)*/\
			PRECALC_ONE_58H(0)\
			PRECALC_ONE_58H(1)\
			PRECALC_ONE_58H(2)\
			PRECALC_ONE_58H(3)\
			PRECALC_ONE_58H(4)\
			PRECALC_ONE_58H(5)\
			PRECALC_ONE_58H(6)\
			PRECALC_ONE_58H(7)\
			PRECALC_ONE_58H(8)\
			PRECALC_ONE_58H(9)\
			PRECALC_ONE_58H(10)\
			PRECALC_ONE_58H(11)\
			PRECALC_ONE_58H(12)\
			PRECALC_ONE_58H(13)\
			PRECALC_ONE_58H(14)\
			PRECALC_ONE_58H(15)\
		/* end unroll loop */\

 	colors[0][R] = (colorsRGB444[0][R] << 4) | colorsRGB444[0][R];
 	colors[0][G] = (colorsRGB444[0][G] << 4) | colorsRGB444[0][G];
 	colors[0][B] = (colorsRGB444[0][B] << 4) | colorsRGB444[0][B];

	// Test all distances
	/* unroll loop for (uint8 d = 0; d < 8; ++d) */

		PRECALC_ONE_TABLE_58H(0)
		PRECALC_ONE_TABLE_58H(1)
		PRECALC_ONE_TABLE_58H(2)
		PRECALC_ONE_TABLE_58H(3)
		PRECALC_ONE_TABLE_58H(4)
		PRECALC_ONE_TABLE_58H(5)
		PRECALC_ONE_TABLE_58H(6)
		PRECALC_ONE_TABLE_58H(7)

	/* end unroll loop */
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Calculate a minimum error for the H-mode when doing exhaustive compression.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateErrorFromPrecalcR58Hperceptual1000(int *colorsRGB444_packed, unsigned int *precalc_errR, unsigned int best_err_so_far) 
{
	unsigned int block_error = 0;
	unsigned int best_block_error = MAXERR1000;
	unsigned int *precalc_col1, *precalc_col2;
	unsigned int *precalc_col1tab, *precalc_col2tab;

	precalc_col1 = &precalc_errR[(colorsRGB444_packed[0]>>8)*8*16];
	precalc_col2 = &precalc_errR[(colorsRGB444_packed[1]>>8)*8*16];

#define CHOICE_R58H_PERCEP(value)\
	if(precalc_col1tab[value] < precalc_col2tab[value])\
		block_error += precalc_col1tab[value];\
	else\
		block_error += precalc_col2tab[value];\

	// Test all distances
	for (uint8 d = 0; d < 8; ++d) 
	{
		block_error = 0;	
		precalc_col1tab = &precalc_col1[d*16];
		precalc_col2tab = &precalc_col2[d*16];
		// Loop block

		/* unroll loop for(q = 0; q<16 && block_error < best_err_so_far; q++) */
		CHOICE_R58H_PERCEP(0)
		if( block_error < best_err_so_far )
		{
			CHOICE_R58H_PERCEP(1)
			if( block_error < best_err_so_far )
			{
				CHOICE_R58H_PERCEP(2)
				if( block_error < best_err_so_far )
				{
					CHOICE_R58H_PERCEP(3)
					if( block_error < best_err_so_far )
					{
						CHOICE_R58H_PERCEP(4)
						if( block_error < best_err_so_far )
						{
							CHOICE_R58H_PERCEP(5)
							if( block_error < best_err_so_far )
							{
								CHOICE_R58H_PERCEP(6)
								if( block_error < best_err_so_far )
								{
									CHOICE_R58H_PERCEP(7)
									if( block_error < best_err_so_far )
									{
										CHOICE_R58H_PERCEP(8)
										if( block_error < best_err_so_far )
										{
											CHOICE_R58H_PERCEP(9)
											if( block_error < best_err_so_far )
											{
												CHOICE_R58H_PERCEP(10)
												if( block_error < best_err_so_far )
												{
													CHOICE_R58H_PERCEP(11)
													if( block_error < best_err_so_far )
													{
														CHOICE_R58H_PERCEP(12)
														if( block_error < best_err_so_far )
														{
															CHOICE_R58H_PERCEP(13)
															if( block_error < best_err_so_far )
															{
																CHOICE_R58H_PERCEP(14)
																if( block_error < best_err_so_far )
																{
																	CHOICE_R58H_PERCEP(15)
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		/* end unroll loop */

		if (block_error < best_block_error) 
			best_block_error = block_error;
	}
	return best_block_error;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Calculate a minimum error for the H-mode when doing exhaustive compression.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateErrorFromPrecalcR58H(int *colorsRGB444_packed, unsigned int *precalc_errR, unsigned int best_err_so_far) 
{
	unsigned int block_error = 0;
	unsigned int best_block_error = MAXIMUM_ERROR;
	unsigned int *precalc_col1, *precalc_col2;
	unsigned int *precalc_col1tab, *precalc_col2tab;

	precalc_col1 = &precalc_errR[(colorsRGB444_packed[0]>>8)*8*16];
	precalc_col2 = &precalc_errR[(colorsRGB444_packed[1]>>8)*8*16];

#define CHOICE_R58H(value)\
	if(precalc_col1tab[value] < precalc_col2tab[value])\
		block_error += precalc_col1tab[value];\
	else\
		block_error += precalc_col2tab[value];\

	// Test all distances
	for (uint8 d = 0; d < 8; ++d) 
	{
		block_error = 0;	
		precalc_col1tab = &precalc_col1[d*16];
		precalc_col2tab = &precalc_col2[d*16];
		// Loop block

		/* unroll loop for(q = 0; q<16 && block_error < best_err_so_far; q++) */
		CHOICE_R58H(0)
		if( block_error < best_err_so_far )
		{
			CHOICE_R58H(1)
			if( block_error < best_err_so_far )
			{
				CHOICE_R58H(2)
				if( block_error < best_err_so_far )
				{
					CHOICE_R58H(3)
					if( block_error < best_err_so_far )
					{
						CHOICE_R58H(4)
						if( block_error < best_err_so_far )
						{
							CHOICE_R58H(5)
							if( block_error < best_err_so_far )
							{
								CHOICE_R58H(6)
								if( block_error < best_err_so_far )
								{
									CHOICE_R58H(7)
									if( block_error < best_err_so_far )
									{
										CHOICE_R58H(8)
										if( block_error < best_err_so_far )
										{
											CHOICE_R58H(9)
											if( block_error < best_err_so_far )
											{
												CHOICE_R58H(10)
												if( block_error < best_err_so_far )
												{
													CHOICE_R58H(11)
													if( block_error < best_err_so_far )
													{
														CHOICE_R58H(12)
														if( block_error < best_err_so_far )
														{
															CHOICE_R58H(13)
															if( block_error < best_err_so_far )
															{
																CHOICE_R58H(14)
																if( block_error < best_err_so_far )
																{
																	CHOICE_R58H(15)
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		/* end unroll loop */

		if (block_error < best_block_error) 
			best_block_error = block_error;

	}
	return best_block_error;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Calculate a minimum error for the H-mode when doing exhaustive compression.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateErrorFromPrecalcRG58Hperceptual1000(int *colorsRGB444_packed, unsigned int *precalc_errRG, unsigned int best_err_so_far) 
{
	unsigned int block_error = 0;
	unsigned int best_block_error = MAXIMUM_ERROR;
	unsigned int *precalc_col1, *precalc_col2;
	unsigned int *precalc_col1tab, *precalc_col2tab;

	precalc_col1 = &precalc_errRG[(colorsRGB444_packed[0]>>4)*8*16];
	precalc_col2 = &precalc_errRG[(colorsRGB444_packed[1]>>4)*8*16];

#define CHOICE_RG58H_PERCEP(value)\
	if(precalc_col1tab[value] < precalc_col2tab[value])\
		block_error += precalc_col1tab[value];\
	else\
		block_error += precalc_col2tab[value];\

	// Test all distances
	for (uint8 d = 0; d < 8; ++d) 
	{
		block_error = 0;	
		precalc_col1tab = &precalc_col1[d*16];
		precalc_col2tab = &precalc_col2[d*16];
		// Loop block

		/* unroll loop for(q = 0; q<16 && block_error < best_err_so_far; q++) */
		CHOICE_RG58H_PERCEP(0)
		if( block_error < best_err_so_far )
		{
			CHOICE_RG58H_PERCEP(1)
			if( block_error < best_err_so_far )
			{
				CHOICE_RG58H_PERCEP(2)
				if( block_error < best_err_so_far )
				{
					CHOICE_RG58H_PERCEP(3)
					if( block_error < best_err_so_far )
					{
						CHOICE_RG58H_PERCEP(4)
						if( block_error < best_err_so_far )
						{
							CHOICE_RG58H_PERCEP(5)
							if( block_error < best_err_so_far )
							{
								CHOICE_RG58H_PERCEP(6)
								if( block_error < best_err_so_far )
								{
									CHOICE_RG58H_PERCEP(7)
									if( block_error < best_err_so_far )
									{
										CHOICE_RG58H_PERCEP(8)
										if( block_error < best_err_so_far )
										{
											CHOICE_RG58H_PERCEP(9)
											if( block_error < best_err_so_far )
											{
												CHOICE_RG58H_PERCEP(10)
												if( block_error < best_err_so_far )
												{
													CHOICE_RG58H_PERCEP(11)
													if( block_error < best_err_so_far )
													{
														CHOICE_RG58H_PERCEP(12)
														if( block_error < best_err_so_far )
														{
															CHOICE_RG58H_PERCEP(13)
															if( block_error < best_err_so_far )
															{
																CHOICE_RG58H_PERCEP(14)
																if( block_error < best_err_so_far )
																{
																	CHOICE_RG58H_PERCEP(15)
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		/* end unroll loop */

		if (block_error < best_block_error) 
			best_block_error = block_error;
	}
	return best_block_error;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Calculate a minimum error for the H-mode when doing exhaustive compression.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateErrorFromPrecalcRG58H(int *colorsRGB444_packed, unsigned int *precalc_errRG, unsigned int best_err_so_far) 
{
	unsigned int block_error = 0;
	unsigned int best_block_error = MAXIMUM_ERROR;
	unsigned int *precalc_col1, *precalc_col2;
	unsigned int *precalc_col1tab, *precalc_col2tab;

	precalc_col1 = &precalc_errRG[(colorsRGB444_packed[0]>>4)*8*16];
	precalc_col2 = &precalc_errRG[(colorsRGB444_packed[1]>>4)*8*16];

#define CHOICE_RG58H(value)\
	if(precalc_col1tab[value] < precalc_col2tab[value])\
		block_error += precalc_col1tab[value];\
	else\
		block_error += precalc_col2tab[value];\

	// Test all distances
	for (uint8 d = 0; d < 8; ++d) 
	{
		block_error = 0;	
		precalc_col1tab = &precalc_col1[d*16];
		precalc_col2tab = &precalc_col2[d*16];
		// Loop block

		/* unroll loop for(q = 0; q<16 && block_error < best_err_so_far; q++) */
		CHOICE_RG58H(0)
		if( block_error < best_err_so_far )
		{
			CHOICE_RG58H(1)
			if( block_error < best_err_so_far )
			{
				CHOICE_RG58H(2)
				if( block_error < best_err_so_far )
				{
					CHOICE_RG58H(3)
					if( block_error < best_err_so_far )
					{
						CHOICE_RG58H(4)
						if( block_error < best_err_so_far )
						{
							CHOICE_RG58H(5)
							if( block_error < best_err_so_far )
							{
								CHOICE_RG58H(6)
								if( block_error < best_err_so_far )
								{
									CHOICE_RG58H(7)
									if( block_error < best_err_so_far )
									{
										CHOICE_RG58H(8)
										if( block_error < best_err_so_far )
										{
											CHOICE_RG58H(9)
											if( block_error < best_err_so_far )
											{
												CHOICE_RG58H(10)
												if( block_error < best_err_so_far )
												{
													CHOICE_RG58H(11)
													if( block_error < best_err_so_far )
													{
														CHOICE_RG58H(12)
														if( block_error < best_err_so_far )
														{
															CHOICE_RG58H(13)
															if( block_error < best_err_so_far )
															{
																CHOICE_RG58H(14)
																if( block_error < best_err_so_far )
																{
																	CHOICE_RG58H(15)
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		/* end unroll loop */

		if (block_error < best_block_error) 
			best_block_error = block_error;
	}
	return best_block_error;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Calculate a minimum error for the H-mode when doing exhaustive compression.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateErrorFromPrecalc58Hperceptual1000(int *colorsRGB444_packed, unsigned int *precalc_err, unsigned int total_best_err) 
{
	unsigned int block_error;\
	unsigned int *precalc_col1, *precalc_col2;\
	unsigned int *precalc_col1tab, *precalc_col2tab;\

	unsigned int error;

#define FIRSTCHOICE_RGB58H_PERCEP(value)\
	if(precalc_col1tab[value] < precalc_col2tab[value])\
		block_error = precalc_col1tab[value];\
	else\
		block_error = precalc_col2tab[value];\

#define CHOICE_RGB58H_PERCEP(value)\
	if(precalc_col1tab[value] < precalc_col2tab[value])\
		block_error += precalc_col1tab[value];\
	else\
		block_error += precalc_col2tab[value];\

#define ONETABLE_RGB58H_PERCEP(distance)\
		precalc_col1tab = &precalc_col1[distance*16];\
		precalc_col2tab = &precalc_col2[distance*16];\
		/* unroll loop for(q = 0; q<16 && block_error < total_best_err; q++) */\
		FIRSTCHOICE_RGB58H_PERCEP(0)\
		if( block_error < total_best_err)\
		{\
			CHOICE_RGB58H_PERCEP(1)\
			if( block_error < total_best_err)\
			{\
				CHOICE_RGB58H_PERCEP(2)\
				CHOICE_RGB58H_PERCEP(3)\
				if( block_error < total_best_err)\
				{\
					CHOICE_RGB58H_PERCEP(4)\
					CHOICE_RGB58H_PERCEP(5)\
					if( block_error < total_best_err)\
					{\
						CHOICE_RGB58H_PERCEP(6)\
						CHOICE_RGB58H_PERCEP(7)\
						if( block_error < total_best_err)\
						{\
							CHOICE_RGB58H_PERCEP(8)\
							CHOICE_RGB58H_PERCEP(9)\
							if( block_error < total_best_err)\
							{\
								CHOICE_RGB58H_PERCEP(10)\
								CHOICE_RGB58H_PERCEP(11)\
								if( block_error < total_best_err)\
								{\
									CHOICE_RGB58H_PERCEP(12)\
									CHOICE_RGB58H_PERCEP(13)\
									if( block_error < total_best_err)\
									{\
										CHOICE_RGB58H_PERCEP(14)\
										CHOICE_RGB58H_PERCEP(15)\
									}\
								}\
							}\
						}\
					}\
				}\
			}\
		}\
		/* end unroll loop */\
		if (block_error < error)\
			error = block_error;\

#define CALCULATE_ERROR_FROM_PRECALC_RGB58H_PERCEP\
	error = MAXERR1000;\
	precalc_col1 = &precalc_err[colorsRGB444_packed[0]*8*16];\
	precalc_col2 = &precalc_err[colorsRGB444_packed[1]*8*16];\
	/* Test all distances*/\
	/* unroll loop for (uint8 d = 0; d < 8; ++d) */\
		ONETABLE_RGB58H_PERCEP(0)\
		ONETABLE_RGB58H_PERCEP(1)\
		ONETABLE_RGB58H_PERCEP(2)\
		ONETABLE_RGB58H_PERCEP(3)\
		ONETABLE_RGB58H_PERCEP(4)\
		ONETABLE_RGB58H_PERCEP(5)\
		ONETABLE_RGB58H_PERCEP(6)\
		ONETABLE_RGB58H_PERCEP(7)\
	/* end unroll loop */\

	CALCULATE_ERROR_FROM_PRECALC_RGB58H_PERCEP
	return error;\
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Calculate a minimum error for the H-mode when doing exhaustive compression.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int calculateErrorFromPrecalc58H(int *colorsRGB444_packed, unsigned int *precalc_err, unsigned int total_best_err) 
{
	unsigned int block_error;\
	unsigned int *precalc_col1, *precalc_col2;\
	unsigned int *precalc_col1tab, *precalc_col2tab;\

	unsigned int error;

#define FIRSTCHOICE_RGB58H(value)\
	if(precalc_col1tab[value] < precalc_col2tab[value])\
		block_error = precalc_col1tab[value];\
	else\
		block_error = precalc_col2tab[value];\

#define CHOICE_RGB58H(value)\
	if(precalc_col1tab[value] < precalc_col2tab[value])\
		block_error += precalc_col1tab[value];\
	else\
		block_error += precalc_col2tab[value];\

#define ONETABLE_RGB58H(distance)\
		precalc_col1tab = &precalc_col1[distance*16];\
		precalc_col2tab = &precalc_col2[distance*16];\
		/* unroll loop for(q = 0; q<16 && block_error < total_best_err; q++) */\
		FIRSTCHOICE_RGB58H(0)\
		if( block_error < total_best_err)\
		{\
			CHOICE_RGB58H(1)\
			if( block_error < total_best_err)\
			{\
				CHOICE_RGB58H(2)\
				CHOICE_RGB58H(3)\
				if( block_error < total_best_err)\
				{\
					CHOICE_RGB58H(4)\
					CHOICE_RGB58H(5)\
					if( block_error < total_best_err)\
					{\
						CHOICE_RGB58H(6)\
						CHOICE_RGB58H(7)\
						if( block_error < total_best_err)\
						{\
							CHOICE_RGB58H(8)\
							CHOICE_RGB58H(9)\
							if( block_error < total_best_err)\
							{\
								CHOICE_RGB58H(10)\
								CHOICE_RGB58H(11)\
								if( block_error < total_best_err)\
								{\
									CHOICE_RGB58H(12)\
									CHOICE_RGB58H(13)\
									if( block_error < total_best_err)\
									{\
										CHOICE_RGB58H(14)\
										CHOICE_RGB58H(15)\
									}\
								}\
							}\
						}\
					}\
				}\
			}\
		}\
		/* end unroll loop */\
		if (block_error < error)\
			error = block_error;\

#define CALCULATE_ERROR_FROM_PRECALC_RGB58H\
	error = MAXIMUM_ERROR;\
	precalc_col1 = &precalc_err[colorsRGB444_packed[0]*8*16];\
	precalc_col2 = &precalc_err[colorsRGB444_packed[1]*8*16];\
	/* Test all distances*/\
	/* unroll loop for (uint8 d = 0; d < 8; ++d) */\
		ONETABLE_RGB58H(0)\
		ONETABLE_RGB58H(1)\
		ONETABLE_RGB58H(2)\
		ONETABLE_RGB58H(3)\
		ONETABLE_RGB58H(4)\
		ONETABLE_RGB58H(5)\
		ONETABLE_RGB58H(6)\
		ONETABLE_RGB58H(7)\
	/* end unroll loop */\

	CALCULATE_ERROR_FROM_PRECALC_RGB58H
	return error;\
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// The below code should compress the block to 58 bits. 
// This is supposed to match the first of the three modes in TWOTIMER.
// The bit layout is thought to be:
//
//|63 62 61 60 59 58|57 56 55 54|53 52 51 50|49 48 47 46|45 44 43 42|41 40 39 38|37 36 35 34|33 32|
//|-------empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|d2 d1|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
//
// The distance d is three bits, d2 (MSB), d1 and d0 (LSB). d0 is not stored explicitly. 
// Instead if the 12-bit word red0,green0,blue0 < red1,green1,blue1, d0 is assumed to be 0.
// Else, it is assumed to be 1.

// The below code should compress the block to 58 bits. 
// This is supposed to match the first of the three modes in TWOTIMER.
// The bit layout is thought to be:
//
//|63 62 61 60 59 58|57 56 55 54|53 52 51 50|49 48 47 46|45 44 43 42|41 40 39 38|37 36 35 34|33 32|
//|-------empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|d2 d1|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
//
// The distance d is three bits, d2 (MSB), d1 and d0 (LSB). d0 is not stored explicitly. 
// Instead if the 12-bit word red0,green0,blue0 < red1,green1,blue1, d0 is assumed to be 0.
// Else, it is assumed to be 1.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int compressBlockTHUMB58HExhaustivePerceptual(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2, unsigned int best_error_so_far) 
{
	unsigned int best_error_using_Hmode;
	uint8 best_colorsRGB444[2][3];
	unsigned int best_pixel_indices;
	uint8 best_distance;

	unsigned int error;
	uint8 colorsRGB444[2][3];
	int colorsRGB444_packed[2];
	int best_colorsRGB444_packed[2];
	int colorRGB444_packed;
	unsigned int pixel_indices;
	uint8 distance;
	unsigned int *precalc_err;		    // smallest error per color, table and pixel
	unsigned int *precalc_err_RG;		// smallest pixel error for an entire table
	unsigned int *precalc_err_R;		// smallest pixel error for an entire table
	uint8 block[4*4*4];

	best_error_using_Hmode = MAXERR1000;	

	precalc_err = (unsigned int*) malloc(4096*8*16*sizeof(unsigned int));
	if(!precalc_err){printf("Out of memory allocating \n");exit(1);}

	precalc_err_RG = (unsigned int*) malloc(16*16*8*16*sizeof(unsigned int));
	if(!precalc_err_RG){printf("Out of memory allocating \n");exit(1);}

	precalc_err_R = (unsigned int*) malloc(16*8*16*sizeof(unsigned int));
	if(!precalc_err_R){printf("Out of memory allocating \n");exit(1);}

 	unsigned int test1, test2;
	best_error_using_Hmode = (unsigned int)compressBlockTHUMB58HFastestPerceptual1000(img,width, height, startx, starty, test1, test2);
    best_colorsRGB444_packed[0] = 0;
	best_colorsRGB444_packed[0] = GETBITSHIGH(test1, 12, 57);
    best_colorsRGB444_packed[1] = 0;
	best_colorsRGB444_packed[1] = GETBITSHIGH(test1, 12, 45);

	if(best_error_using_Hmode < best_error_so_far)
		best_error_so_far = best_error_using_Hmode;

	int xx,yy,count = 0;

	// Use 4 bytes per pixel to make it 32-word aligned.
	for(xx = 0; xx<4; xx++)
	{
		for(yy=0; yy<4; yy++)
		{
			block[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block[(count)*4+3] = 0;
			count++;
		}
	}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed++)
	{
		colorsRGB444[0][0] = (colorRGB444_packed >> 8) & 0xf;
		colorsRGB444[0][1] = (colorRGB444_packed >> 4) & 0xf;
		colorsRGB444[0][2] = (colorRGB444_packed) & 0xf;

		precalcError58Hperceptual1000(block, colorsRGB444, colorRGB444_packed, precalc_err);
	}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed+=16)
	{
		colorsRGB444[0][0] = (colorRGB444_packed >> 8) & 0xf;
		colorsRGB444[0][1] = (colorRGB444_packed >> 4) & 0xf;
		colorsRGB444[0][2] = (colorRGB444_packed) & 0xf;
		precalcErrorRG_58Hperceptual1000(img, width, startx, starty, colorsRGB444, colorRGB444_packed, precalc_err_RG);
	}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed+=16*16)
	{
		colorsRGB444[0][0] = (colorRGB444_packed >> 8) & 0xf;
		colorsRGB444[0][1] = (colorRGB444_packed >> 4) & 0xf;
		colorsRGB444[0][2] = (colorRGB444_packed) & 0xf;
		precalcErrorR_58Hperceptual1000(img, width, startx, starty, colorsRGB444, colorRGB444_packed, precalc_err_R);
	}

	int trycols = 0;
	int allcols = 0;

	for( colorsRGB444[0][0] = 0; colorsRGB444[0][0] <16; colorsRGB444[0][0]++)
	{
		colorsRGB444_packed[0] = colorsRGB444[0][0]*256;
		for( colorsRGB444[1][0] = 0; colorsRGB444[1][0] <16; colorsRGB444[1][0]++)
		{
			colorsRGB444_packed[1] = colorsRGB444[1][0]*256;
			if(colorsRGB444_packed[0] <= colorsRGB444_packed[1])
			{
				error = calculateErrorFromPrecalcR58Hperceptual1000(colorsRGB444_packed, precalc_err_R, best_error_so_far);
				if(error < best_error_so_far)
				{
					for( colorsRGB444[0][1] = 0; colorsRGB444[0][1] <16; colorsRGB444[0][1]++)
					{
						colorsRGB444_packed[0] = colorsRGB444[0][0]*256 + colorsRGB444[0][1]*16;
						for( colorsRGB444[1][1] = 0; colorsRGB444[1][1] <16; colorsRGB444[1][1]++)
						{
							colorsRGB444_packed[1] = colorsRGB444[1][0]*256 + colorsRGB444[1][1]*16;
							if(colorsRGB444_packed[0] <= colorsRGB444_packed[1])
							{
								error = calculateErrorFromPrecalcRG58Hperceptual1000(colorsRGB444_packed, precalc_err_RG, best_error_so_far);
								if(error < best_error_so_far)
								{
									for( colorsRGB444[0][2] = 0; colorsRGB444[0][2] <16; colorsRGB444[0][2]++)
									{
										colorsRGB444_packed[0] = colorsRGB444[0][0]*256 + colorsRGB444[0][1]*16 + colorsRGB444[0][2];
										for( colorsRGB444[1][2] = 0; colorsRGB444[1][2] <16; colorsRGB444[1][2]++)
										{
											colorsRGB444_packed[1] = colorsRGB444[1][0]*256 + colorsRGB444[1][1]*16 + colorsRGB444[1][2];
											if(colorsRGB444_packed[0] < colorsRGB444_packed[1])
											{
												error = calculateErrorFromPrecalc58Hperceptual1000(colorsRGB444_packed, precalc_err, best_error_so_far);
												if(error < best_error_so_far)
												{
													best_error_so_far = error;	
													best_error_using_Hmode = error;
													best_colorsRGB444_packed[0] = colorsRGB444_packed[0];
													best_colorsRGB444_packed[1] = colorsRGB444_packed[1];
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	best_colorsRGB444[0][0] = (best_colorsRGB444_packed[0] >> 8) & 0xf;
	best_colorsRGB444[0][1] = (best_colorsRGB444_packed[0] >> 4) & 0xf;
	best_colorsRGB444[0][2] = (best_colorsRGB444_packed[0]) & 0xf;
	best_colorsRGB444[1][0] = (best_colorsRGB444_packed[1] >> 8) & 0xf;
	best_colorsRGB444[1][1] = (best_colorsRGB444_packed[1] >> 4) & 0xf;
	best_colorsRGB444[1][2] = (best_colorsRGB444_packed[1]) & 0xf;

	free(precalc_err);
	free(precalc_err_RG);
	free(precalc_err_R);

	error = (unsigned int) calculateErrorAndCompress58Hperceptual1000(img, width, startx, starty, best_colorsRGB444, distance, pixel_indices);
	best_distance = distance; 
	best_pixel_indices = pixel_indices;

	//                   | col0 >= col1      col0 < col1
	//------------------------------------------------------
	// (dist & 1) = 1    | no need to swap | need to swap
	//                   |-----------------+----------------
	// (dist & 1) = 0    | need to swap    | no need to swap
	//
	// This can be done with an xor test.

	best_colorsRGB444_packed[0] = (best_colorsRGB444[0][R] << 8) + (best_colorsRGB444[0][G] << 4) + best_colorsRGB444[0][B];
	best_colorsRGB444_packed[1] = (best_colorsRGB444[1][R] << 8) + (best_colorsRGB444[1][G] << 4) + best_colorsRGB444[1][B];
	if( (best_colorsRGB444_packed[0] >= best_colorsRGB444_packed[1]) ^ ((best_distance & 1)==1) )
	{
		swapColors(best_colorsRGB444);

		// Reshuffle pixel indices to to exchange C1 with C3, and C2 with C4
		best_pixel_indices = (0x55555555 & best_pixel_indices) | (0xaaaaaaaa & (~best_pixel_indices));
	}

	// Put the compress params into the compression block 
	compressed1 = 0;

	PUTBITSHIGH( compressed1, best_colorsRGB444[0][R], 4, 57);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[0][G], 4, 53);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[0][B], 4, 49);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][R], 4, 45);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][G], 4, 41);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][B], 4, 37);
	PUTBITSHIGH( compressed1, (best_distance >> 1), 2, 33);
	best_pixel_indices=indexConversion(best_pixel_indices);
	compressed2 = 0;
	PUTBITS( compressed2, best_pixel_indices, 32, 31);

	return best_error_using_Hmode;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// The below code should compress the block to 58 bits. 
// This is supposed to match the first of the three modes in TWOTIMER.
// The bit layout is thought to be:
//
//|63 62 61 60 59 58|57 56 55 54|53 52 51 50|49 48 47 46|45 44 43 42|41 40 39 38|37 36 35 34|33 32|
//|-------empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|d2 d1|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
//
// The distance d is three bits, d2 (MSB), d1 and d0 (LSB). d0 is not stored explicitly. 
// Instead if the 12-bit word red0,green0,blue0 < red1,green1,blue1, d0 is assumed to be 0.
// Else, it is assumed to be 1.

// The below code should compress the block to 58 bits. 
// This is supposed to match the first of the three modes in TWOTIMER.
// The bit layout is thought to be:
//
//|63 62 61 60 59 58|57 56 55 54|53 52 51 50|49 48 47 46|45 44 43 42|41 40 39 38|37 36 35 34|33 32|
//|-------empty-----|---red 0---|--green 0--|--blue 0---|---red 1---|--green 1--|--blue 1---|d2 d1|
//
//|31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00|
//|----------------------------------------index bits---------------------------------------------|
//
// The distance d is three bits, d2 (MSB), d1 and d0 (LSB). d0 is not stored explicitly. 
// Instead if the 12-bit word red0,green0,blue0 < red1,green1,blue1, d0 is assumed to be 0.
// Else, it is assumed to be 1.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
unsigned int compressBlockTHUMB58HExhaustive(uint8 *img,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2, unsigned int best_error_so_far) 
{
	unsigned int best_error_using_Hmode;
	uint8 best_colorsRGB444[2][3];
	unsigned int best_pixel_indices;
	uint8 best_distance;

	unsigned int error;
	uint8 colorsRGB444[2][3];
	int colorsRGB444_packed[2];
	int best_colorsRGB444_packed[2];
	int colorRGB444_packed;
	unsigned int pixel_indices;
	uint8 distance;
	unsigned int *precalc_err;		    // smallest error per color, table and pixel
	unsigned int *precalc_err_RG;		// smallest pixel error for an entire table
	unsigned int *precalc_err_R;		// smallest pixel error for an entire table
	uint8 block[4*4*4];

	best_error_using_Hmode = MAXIMUM_ERROR;	

	precalc_err = (unsigned int*) malloc(4096*8*16*sizeof(unsigned int));
	if(!precalc_err){printf("Out of memory allocating \n");exit(1);}

	precalc_err_RG = (unsigned int*) malloc(16*16*8*16*sizeof(unsigned int));
	if(!precalc_err_RG){printf("Out of memory allocating \n");exit(1);}

	precalc_err_R = (unsigned int*) malloc(16*8*16*sizeof(unsigned int));
	if(!precalc_err_R){printf("Out of memory allocating \n");exit(1);}

 	unsigned int test1, test2;
	best_error_using_Hmode = (unsigned int)compressBlockTHUMB58HFastest(img,width, height, startx, starty, test1, test2);
    best_colorsRGB444_packed[0] = 0;
	best_colorsRGB444_packed[0] = GETBITSHIGH(test1, 12, 57);
    best_colorsRGB444_packed[1] = 0;
	best_colorsRGB444_packed[1] = GETBITSHIGH(test1, 12, 45);

	if(best_error_using_Hmode < best_error_so_far)
		best_error_so_far = best_error_using_Hmode;

	int xx,yy,count = 0;

	// Reshuffle pixels so that the top left 2x2 pixels arrive first, then the top right 2x2 pixels etc. Also put use 4 bytes per pixel to make it 32-word aligned.
	for(xx = 0; xx<4; xx++)
	{
		for(yy=0; yy<4; yy++)
		{
			block[(count)*4] = img[((starty+yy)*width+(startx+xx))*3];
			block[(count)*4+1] = img[((starty+yy)*width+(startx+xx))*3+1];
			block[(count)*4+2] = img[((starty+yy)*width+(startx+xx))*3+2];
			block[(count)*4+3] = 0;
			count++;
		}
	}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed++)
	{
		colorsRGB444[0][0] = (colorRGB444_packed >> 8) & 0xf;
		colorsRGB444[0][1] = (colorRGB444_packed >> 4) & 0xf;
		colorsRGB444[0][2] = (colorRGB444_packed) & 0xf;
		precalcError58H(block, colorsRGB444, colorRGB444_packed, precalc_err);
	}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed+=16)
	{
		colorsRGB444[0][0] = (colorRGB444_packed >> 8) & 0xf;
		colorsRGB444[0][1] = (colorRGB444_packed >> 4) & 0xf;
		colorsRGB444[0][2] = (colorRGB444_packed) & 0xf;
		precalcErrorRG_58H(img, width, startx, starty, colorsRGB444, colorRGB444_packed, precalc_err_RG);
	}

	for( colorRGB444_packed = 0; colorRGB444_packed<16*16*16; colorRGB444_packed+=16*16)
	{
		colorsRGB444[0][0] = (colorRGB444_packed >> 8) & 0xf;
		colorsRGB444[0][1] = (colorRGB444_packed >> 4) & 0xf;
		colorsRGB444[0][2] = (colorRGB444_packed) & 0xf;
		precalcErrorR_58H(img, width, startx, starty, colorsRGB444, colorRGB444_packed, precalc_err_R);
	}

	int trycols = 0;
	int allcols = 0;

	for( colorsRGB444[0][0] = 0; colorsRGB444[0][0] <16; colorsRGB444[0][0]++)
	{
		colorsRGB444_packed[0] = colorsRGB444[0][0]*256;
		for( colorsRGB444[1][0] = 0; colorsRGB444[1][0] <16; colorsRGB444[1][0]++)
		{
			colorsRGB444_packed[1] = colorsRGB444[1][0]*256;
			if(colorsRGB444_packed[0] <= colorsRGB444_packed[1])
			{
				error = calculateErrorFromPrecalcR58H(colorsRGB444_packed, precalc_err_R, best_error_so_far);
				if(error < best_error_so_far)
				{
					for( colorsRGB444[0][1] = 0; colorsRGB444[0][1] <16; colorsRGB444[0][1]++)
					{
						colorsRGB444_packed[0] = colorsRGB444[0][0]*256 + colorsRGB444[0][1]*16;
						for( colorsRGB444[1][1] = 0; colorsRGB444[1][1] <16; colorsRGB444[1][1]++)
						{
							colorsRGB444_packed[1] = colorsRGB444[1][0]*256 + colorsRGB444[1][1]*16;
							if(colorsRGB444_packed[0] <= colorsRGB444_packed[1])
							{
								error = calculateErrorFromPrecalcRG58H(colorsRGB444_packed, precalc_err_RG, best_error_so_far);
								if(error < best_error_so_far)
								{
									for( colorsRGB444[0][2] = 0; colorsRGB444[0][2] <16; colorsRGB444[0][2]++)
									{
										colorsRGB444_packed[0] = colorsRGB444[0][0]*256 + colorsRGB444[0][1]*16 + colorsRGB444[0][2];
										for( colorsRGB444[1][2] = 0; colorsRGB444[1][2] <16; colorsRGB444[1][2]++)
										{
											colorsRGB444_packed[1] = colorsRGB444[1][0]*256 + colorsRGB444[1][1]*16 + colorsRGB444[1][2];
											if(colorsRGB444_packed[0] < colorsRGB444_packed[1])
											{
												error = calculateErrorFromPrecalc58H(colorsRGB444_packed, precalc_err, best_error_so_far);
												if(error < best_error_so_far)
												{
													best_error_so_far = error;	
													best_error_using_Hmode = error;
													best_colorsRGB444_packed[0] = colorsRGB444_packed[0];
													best_colorsRGB444_packed[1] = colorsRGB444_packed[1];
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	best_colorsRGB444[0][0] = (best_colorsRGB444_packed[0] >> 8) & 0xf;
	best_colorsRGB444[0][1] = (best_colorsRGB444_packed[0] >> 4) & 0xf;
	best_colorsRGB444[0][2] = (best_colorsRGB444_packed[0]) & 0xf;
	best_colorsRGB444[1][0] = (best_colorsRGB444_packed[1] >> 8) & 0xf;
	best_colorsRGB444[1][1] = (best_colorsRGB444_packed[1] >> 4) & 0xf;
	best_colorsRGB444[1][2] = (best_colorsRGB444_packed[1]) & 0xf;

	free(precalc_err);
	free(precalc_err_RG);
	free(precalc_err_R);

	error = (unsigned int) calculateErrorAndCompress58H(img, width, startx, starty, best_colorsRGB444, distance, pixel_indices);
	best_distance = distance; 
	best_pixel_indices = pixel_indices;

	//                   | col0 >= col1      col0 < col1
	//------------------------------------------------------
	// (dist & 1) = 1    | no need to swap | need to swap
	//                   |-----------------+----------------
	// (dist & 1) = 0    | need to swap    | no need to swap
    //
	// This can be done with an xor test.

	best_colorsRGB444_packed[0] = (best_colorsRGB444[0][R] << 8) + (best_colorsRGB444[0][G] << 4) + best_colorsRGB444[0][B];
	best_colorsRGB444_packed[1] = (best_colorsRGB444[1][R] << 8) + (best_colorsRGB444[1][G] << 4) + best_colorsRGB444[1][B];
	if( (best_colorsRGB444_packed[0] >= best_colorsRGB444_packed[1]) ^ ((best_distance & 1)==1) )
	{
		swapColors(best_colorsRGB444);

		// Reshuffle pixel indices to to exchange C1 with C3, and C2 with C4
		best_pixel_indices = (0x55555555 & best_pixel_indices) | (0xaaaaaaaa & (~best_pixel_indices));
	}

	// Put the compress params into the compression block 
	compressed1 = 0;

	PUTBITSHIGH( compressed1, best_colorsRGB444[0][R], 4, 57);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[0][G], 4, 53);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[0][B], 4, 49);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][R], 4, 45);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][G], 4, 41);
 	PUTBITSHIGH( compressed1, best_colorsRGB444[1][B], 4, 37);
	PUTBITSHIGH( compressed1, (best_distance >> 1), 2, 33);
	best_pixel_indices=indexConversion(best_pixel_indices);
	compressed2 = 0;
	PUTBITS( compressed2, best_pixel_indices, 32, 31);

	return best_error_using_Hmode;
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Compress a block exhaustively for the ETC1 codec.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockETC1Exhaustive(uint8 *img, uint8 *imgdec,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2)
{
	unsigned int error_currently_best;

	unsigned int etc1_differential_word1;
	unsigned int etc1_differential_word2;
	unsigned int error_etc1_differential;

	unsigned int etc1_individual_word1;
	unsigned int etc1_individual_word2;
	unsigned int error_etc1_individual;
	
	unsigned int error_best;
	signed char best_char;
	int best_mode;

	error_currently_best = 255*255*16*3;

	// First pass -- quickly find a low error so that we can later cull away a lot of 
	// calculations later that are guaranteed to be higher than that error.
	unsigned int error_etc1;
	unsigned int etc1_word1;
	unsigned int etc1_word2;

	error_etc1 = (unsigned int) compressBlockDiffFlipFast(img, imgdec, width, height, startx, starty, etc1_word1, etc1_word2);
	if(error_etc1 < error_currently_best)
		error_currently_best = error_etc1;

 	error_etc1_individual = compressBlockIndividualExhaustive(img, width, height, startx, starty, etc1_individual_word1, etc1_individual_word2, error_currently_best);
	if(error_etc1_individual < error_currently_best)
		error_currently_best = error_etc1_individual;

  	error_etc1_differential = compressBlockDifferentialExhaustive(img, width, height, startx, starty, etc1_differential_word1, etc1_differential_word2, error_currently_best);
	if(error_etc1_differential < error_currently_best)
		error_currently_best = error_etc1_differential;

 	error_best = error_etc1_differential;
 	compressed1 = etc1_differential_word1;
 	compressed2 = etc1_differential_word2;
 	best_char = '.';
 	best_mode = MODE_ETC1;

	if(error_etc1_individual < error_best)
	{
		compressed1 = etc1_individual_word1;
		compressed2 = etc1_individual_word2;
		best_char = ',';
		error_best = error_etc1_individual;
		best_mode = MODE_ETC1;
	}

	if(error_etc1 < error_best)
	{
		compressed1 = etc1_word1;
		compressed2 = etc1_word2;
		best_char = '.';
		error_best = error_etc1;
		best_mode = MODE_ETC1;
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Compress a block exhaustively for the ETC1 codec using perceptual error measure.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockETC1ExhaustivePerceptual(uint8 *img, uint8 *imgdec,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2)
{
	unsigned int error_currently_best;
	
	unsigned int etc1_differential_word1;
	unsigned int etc1_differential_word2;
	unsigned int error_etc1_differential;

	unsigned int etc1_individual_word1;
	unsigned int etc1_individual_word2;
	unsigned int error_etc1_individual;

	unsigned int error_best;
	signed char best_char;
	int best_mode;


	error_currently_best = 255*255*16*1000;

	// First pass -- quickly find a low error so that we can later cull away a lot of 
	// calculations later that are guaranteed to be higher than that error.
	unsigned int error_etc1;
	unsigned int etc1_word1;
	unsigned int etc1_word2;

	compressBlockDiffFlipFastPerceptual(img, imgdec, width, height, startx, starty, etc1_word1, etc1_word2);
	decompressBlockDiffFlip(etc1_word1, etc1_word2, imgdec, width, height, startx, starty);
	error_etc1 = 1000*calcBlockPerceptualErrorRGB(img, imgdec, width, height, startx, starty);
	if(error_etc1 < error_currently_best)
		error_currently_best = error_etc1;

	// Second pass --- now find the lowest error, but only if it is lower than error_currently_best

	error_etc1_differential = compressBlockDifferentialExhaustivePerceptual(img, width, height, startx, starty, etc1_differential_word1, etc1_differential_word2, error_currently_best);
 	if(error_etc1_differential < error_currently_best)
 		error_currently_best = error_etc1_differential;

  	error_etc1_individual = compressBlockIndividualExhaustivePerceptual(img, width, height, startx, starty, etc1_individual_word1, etc1_individual_word2, error_currently_best);
  	if(error_etc1_individual < error_currently_best)
 		error_currently_best = error_etc1_individual;

	// Now find the best error.
	error_best = error_etc1;
	compressed1 = etc1_word1;
	compressed2 = etc1_word2;
	best_char = '.';
	best_mode = MODE_ETC1;

	if(error_etc1_differential < error_best)
	{
		error_best = error_etc1_differential;
		compressed1 = etc1_differential_word1;
		compressed2 = etc1_differential_word2;
		best_char = '.';
		best_mode = MODE_ETC1;
	}

	if(error_etc1_individual < error_best)
	{
		compressed1 = etc1_individual_word1;
		compressed2 = etc1_individual_word2;
		best_char = ',';
		error_best = error_etc1_individual;
		best_mode = MODE_ETC1;
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Compress a block exhaustively for the ETC2 RGB codec using perceptual error measure.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockETC2ExhaustivePerceptual(uint8 *img, uint8 *imgdec,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2)
{
	unsigned int error_currently_best;
	
	unsigned int etc1_differential_word1;
	unsigned int etc1_differential_word2;
	unsigned int error_etc1_differential;

	unsigned int etc1_individual_word1;
	unsigned int etc1_individual_word2;
	unsigned int error_etc1_individual;

 	unsigned int planar57_word1;
 	unsigned int planar57_word2;
 	unsigned int planar_word1;
 	unsigned int planar_word2;
 	double error_planar;
	unsigned int error_planar_red, error_planar_green, error_planar_blue;

	unsigned int thumbH58_word1;
	unsigned int thumbH58_word2;
	unsigned int thumbH_word1;
	unsigned int thumbH_word2;
	unsigned int error_thumbH;
	
	unsigned int thumbT59_word1;
	unsigned int thumbT59_word2;
	unsigned int thumbT_word1;
	unsigned int thumbT_word2;
	unsigned int error_thumbT;
	
	unsigned int error_best;
	signed char best_char;
	int best_mode;

	error_currently_best = 255*255*16*1000;

	// First pass -- quickly find a low error so that we can later cull away a lot of 
	// calculations later that are guaranteed to be higher than that error.
	unsigned int error_etc1;
	unsigned int etc1_word1;
	unsigned int etc1_word2;

	compressBlockDiffFlipFastPerceptual(img, imgdec, width, height, startx, starty, etc1_word1, etc1_word2);
	decompressBlockDiffFlip(etc1_word1, etc1_word2, imgdec, width, height, startx, starty);
	error_etc1 = 1000*calcBlockPerceptualErrorRGB(img, imgdec, width, height, startx, starty);
	if(error_etc1 < error_currently_best)
		error_currently_best = error_etc1;

	// The planar mode treats every channel independently and should not be affected by the weights in the error measure. 
	// We can hence use the nonperceptual version of the encoder also to find the best perceptual description of the block.
	compressBlockPlanar57(img, width, height, startx, starty, planar57_word1, planar57_word2);
	decompressBlockPlanar57errorPerComponent(planar57_word1, planar57_word2, imgdec, width, height, startx, starty, img, error_planar_red, error_planar_green, error_planar_blue);
 	error_planar = 1000*calcBlockPerceptualErrorRGB(img, imgdec, width, height, startx, starty);
	stuff57bits(planar57_word1, planar57_word2, planar_word1, planar_word2);
	if(error_planar < error_currently_best)
		error_currently_best = (unsigned int) error_planar;

	error_thumbT = (unsigned int) compressBlockTHUMB59TFastestPerceptual1000(img,width, height, startx, starty, thumbT59_word1, thumbT59_word2);
	stuff59bits(thumbT59_word1, thumbT59_word2, thumbT_word1, thumbT_word2);
	if(error_thumbT < error_currently_best)
		error_currently_best = error_thumbT;

	error_thumbH = (unsigned int) compressBlockTHUMB58HFastestPerceptual1000(img,width,height,startx, starty, thumbH58_word1, thumbH58_word2);
	stuff58bits(thumbH58_word1, thumbH58_word2, thumbH_word1, thumbH_word2);
	if(error_thumbH < error_currently_best)
		error_currently_best = error_thumbH;
	
	// Second pass --- now find the lowest error, but only if it is lower than error_currently_best

	// Correct the individual errors for the different planes so that they sum to 1000 instead of 1.
	error_planar_red *=PERCEPTUAL_WEIGHT_R_SQUARED_TIMES1000;
	error_planar_green *=PERCEPTUAL_WEIGHT_G_SQUARED_TIMES1000;
	error_planar_blue *=PERCEPTUAL_WEIGHT_B_SQUARED_TIMES1000;
	compressBlockPlanar57ExhaustivePerceptual(img, width, height, startx, starty, planar57_word1, planar57_word2, error_currently_best, error_planar_red, error_planar_green, error_planar_blue);	
	decompressBlockPlanar57(planar57_word1, planar57_word2, imgdec, width, height, startx, starty);
	error_planar = 1000*calcBlockPerceptualErrorRGB(img, imgdec, width, height, startx, starty);
	stuff57bits(planar57_word1, planar57_word2, planar_word1, planar_word2);
	if(error_planar < error_currently_best)
		error_currently_best = (unsigned int) error_planar;
	
	error_etc1_differential = compressBlockDifferentialExhaustivePerceptual(img, width, height, startx, starty, etc1_differential_word1, etc1_differential_word2, error_currently_best);
	if(error_etc1_differential < error_currently_best)
		error_currently_best = error_etc1_differential;

	error_etc1_individual = compressBlockIndividualExhaustivePerceptual(img, width, height, startx, starty, etc1_individual_word1, etc1_individual_word2, error_currently_best);
	if(error_etc1_individual < error_currently_best)
		error_currently_best = error_etc1_individual;

	error_thumbH = compressBlockTHUMB58HExhaustivePerceptual(img,width,height,startx, starty, thumbH58_word1, thumbH58_word2, error_currently_best);
	stuff58bits(thumbH58_word1, thumbH58_word2, thumbH_word1, thumbH_word2);
	if( error_thumbH < error_currently_best)
		error_currently_best = error_thumbH;

	error_thumbT = compressBlockTHUMB59TExhaustivePerceptual(img,width, height, startx, starty, thumbT59_word1, thumbT59_word2, error_currently_best);
	stuff59bits(thumbT59_word1, thumbT59_word2, thumbT_word1, thumbT_word2);
	if(error_thumbT < error_currently_best)
		error_currently_best = error_thumbT;

	// Now find the best error.
	error_best = error_etc1;
	compressed1 = etc1_word1;
	compressed2 = etc1_word2;
	best_char = '.';
	best_mode = MODE_ETC1;

	if(error_etc1_differential < error_best)
	{
		error_best = error_etc1_differential;
		compressed1 = etc1_differential_word1;
		compressed2 = etc1_differential_word2;
		best_char = '.';
		best_mode = MODE_ETC1;
	}

	if(error_etc1_individual < error_best)
	{
		compressed1 = etc1_individual_word1;
		compressed2 = etc1_individual_word2;
		best_char = ',';
		error_best = error_etc1_individual;
		best_mode = MODE_ETC1;
	}
	if(error_planar < error_best)
	{
		compressed1 = planar_word1;
		compressed2 = planar_word2;
		best_char = 'p';
		error_best = (unsigned int) error_planar;
		best_mode = MODE_PLANAR;
 	}
	if(error_thumbH < error_best)
	{
		compressed1 = thumbH_word1;
		compressed2 = thumbH_word2;
		best_char = 'H';
		error_best = error_thumbH;
		best_mode = MODE_THUMB_H;
	}
	if(error_thumbT < error_best)
	{
		compressed1 = thumbT_word1;
		compressed2 = thumbT_word2;
		best_char = 'T';
		error_best = error_thumbT;
		best_mode = MODE_THUMB_T;
	}
}
#endif

#if EXHAUSTIVE_CODE_ACTIVE
// Compress a block exhaustively for the ETC2 RGB codec.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressBlockETC2Exhaustive(uint8 *img, uint8 *imgdec,int width,int height,int startx,int starty, unsigned int &compressed1, unsigned int &compressed2)
{
	unsigned int error_currently_best;

	unsigned int etc1_differential_word1;
	unsigned int etc1_differential_word2;
	unsigned int error_etc1_differential;

	unsigned int etc1_individual_word1;
	unsigned int etc1_individual_word2;
	unsigned int error_etc1_individual;

	unsigned int planar57_word1;
	unsigned int planar57_word2;
	unsigned int planar_word1;
	unsigned int planar_word2;
	double error_planar;
	unsigned int error_planar_red;
	unsigned int error_planar_green;
	unsigned int error_planar_blue;

	unsigned int thumbH58_word1;
	unsigned int thumbH58_word2;
	unsigned int thumbH_word1;
	unsigned int thumbH_word2;
	unsigned int error_thumbH;
	
	unsigned int thumbT59_word1;
	unsigned int thumbT59_word2;
	unsigned int thumbT_word1;
	unsigned int thumbT_word2;
	unsigned int error_thumbT;
	
	unsigned int error_best;
	signed char best_char;
	int best_mode;

	error_currently_best = 255*255*16*3;

	// First pass -- quickly find a low error so that we can later cull away a lot of 
	// calculations later that are guaranteed to be higher than that error.
	unsigned int error_etc1;
	unsigned int etc1_word1;
	unsigned int etc1_word2;

	error_etc1 = (unsigned int) compressBlockDiffFlipFast(img, imgdec, width, height, startx, starty, etc1_word1, etc1_word2);
	if(error_etc1 < error_currently_best)
		error_currently_best = error_etc1;

	compressBlockPlanar57(img, width, height, startx, starty, planar57_word1, planar57_word2);
	decompressBlockPlanar57errorPerComponent(planar57_word1, planar57_word2, imgdec, width, height, startx, starty, img, error_planar_red, error_planar_green, error_planar_blue);
	error_planar = calcBlockErrorRGB(img, imgdec, width, height, startx, starty);
	stuff57bits(planar57_word1, planar57_word2, planar_word1, planar_word2);
	if(error_planar < error_currently_best)
		error_currently_best = (unsigned int) error_planar;

	error_thumbT = (unsigned int) compressBlockTHUMB59TFastest(img,width, height, startx, starty, thumbT59_word1, thumbT59_word2);
	stuff59bits(thumbT59_word1, thumbT59_word2, thumbT_word1, thumbT_word2);
	if(error_thumbT < error_currently_best)
		error_currently_best = error_thumbT;

	error_thumbH = (unsigned int) compressBlockTHUMB58HFastest(img,width,height,startx, starty, thumbH58_word1, thumbH58_word2);
	stuff58bits(thumbH58_word1, thumbH58_word2, thumbH_word1, thumbH_word2);
	if(error_thumbH < error_currently_best)
		error_currently_best = error_thumbH;

	// Second pass --- now find the lowest error, but only if it is lower than error_currently_best
	error_etc1_differential = compressBlockDifferentialExhaustive(img, width, height, startx, starty, etc1_differential_word1, etc1_differential_word2, error_currently_best);
	if(error_etc1_differential < error_currently_best)
		error_currently_best = error_etc1_differential;

	compressBlockPlanar57Exhaustive(img, width, height, startx, starty, planar57_word1, planar57_word2, error_currently_best, error_planar_red, error_planar_green, error_planar_blue);
	decompressBlockPlanar57(planar57_word1, planar57_word2, imgdec, width, height, startx, starty);
	error_planar = calcBlockErrorRGB(img, imgdec, width, height, startx, starty);
	stuff57bits(planar57_word1, planar57_word2, planar_word1, planar_word2);
	if(error_planar < error_currently_best)
		error_currently_best = (unsigned int) error_planar;
	
	error_etc1_individual = compressBlockIndividualExhaustive(img, width, height, startx, starty, etc1_individual_word1, etc1_individual_word2, error_currently_best);
	if(error_etc1_individual < error_currently_best)
		error_currently_best = error_etc1_individual;

	error_thumbH = compressBlockTHUMB58HExhaustive(img,width,height,startx, starty, thumbH58_word1, thumbH58_word2, error_currently_best);
	if( error_thumbH < error_currently_best)
		error_currently_best = error_thumbH;
	stuff58bits(thumbH58_word1, thumbH58_word2, thumbH_word1, thumbH_word2);

	error_thumbT = compressBlockTHUMB59TExhaustive(img,width, height, startx, starty, thumbT59_word1, thumbT59_word2, error_currently_best);
	if(error_thumbT < error_currently_best)
		error_currently_best = error_thumbT;
	stuff59bits(thumbT59_word1, thumbT59_word2, thumbT_word1, thumbT_word2);

	error_best = 255*255*3*16;
	// Now find the best error.
	error_best = error_etc1;
	compressed1 = etc1_word1;
	compressed2 = etc1_word2;
	best_char = '.';
	best_mode = MODE_ETC1;

	if(error_etc1_differential < error_best)
	{
		error_best = error_etc1_differential;
		compressed1 = etc1_differential_word1;
		compressed2 = etc1_differential_word2;
		best_char = '.';
		best_mode = MODE_ETC1;
	}
	if(error_etc1_individual < error_best)
	{
		compressed1 = etc1_individual_word1;
		compressed2 = etc1_individual_word2;
		best_char = ',';
		error_best = error_etc1_individual;
		best_mode = MODE_ETC1;
	}
	if(error_planar < error_best)
	{
		compressed1 = planar_word1;
		compressed2 = planar_word2;
		best_char = 'p';
		error_best = (unsigned int) error_planar;
		best_mode = MODE_PLANAR;
	}
	if(error_thumbH < error_best)
	{
		compressed1 = thumbH_word1;
		compressed2 = thumbH_word2;
		best_char = 'H';
		error_best = error_thumbH;
		best_mode = MODE_THUMB_H;
	}
	if(error_thumbT < error_best)
	{
		compressed1 = thumbT_word1;
		compressed2 = thumbT_word2;
		best_char = 'T';
		error_best = error_thumbT;
		best_mode = MODE_THUMB_T;
	}
}
#endif

//// Exhaustive code ends here.


// Compress an image file.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressImageFile(uint8 *img, uint8 *alphaimg,int width,int height,char *dstfile, int expandedwidth, int expandedheight)
{
	FILE *f;
	int x,y,w,h;
	unsigned int block1, block2;
	unsigned short wi, hi;
	unsigned char magic[4];
	unsigned char version[2];
	unsigned short texture_type=format;
	uint8 *imgdec;
	uint8* alphaimg2;
	imgdec = (unsigned char*) malloc(expandedwidth*expandedheight*3);
	if(!imgdec)
	{
		printf("Could not allocate decompression buffer --- exiting\n");
	}

	magic[0]   = 'P'; magic[1]   = 'K'; magic[2] = 'M'; magic[3] = ' '; 

	if(codec==CODEC_ETC2)
	{
		version[0] = '2'; version[1] = '0';
	}
	else
	{
		version[0] = '1'; version[1] = '0';
	}

	if(f=fopen(dstfile,"wb"))
	{
		w=expandedwidth/4;  w*=4;
		h=expandedheight/4; h*=4;
		wi = w;
		hi = h;
		if(ktxFile) 
		{
			//.ktx file: KTX header followed by compressed binary data.
			KTX_header header;
			//identifier
			for(int i=0; i<12; i++) 
			{
				header.identifier[i]=ktx_identifier[i];
			}
			//endianess int.. if this comes out reversed, all of the other ints will too.
			header.endianness=KTX_ENDIAN_REF;
			
			//these values are always 0/1 for compressed textures.
			header.glType=0;
			header.glTypeSize=1;
			header.glFormat=0;

			header.pixelWidth=width;
			header.pixelHeight=height;
			header.pixelDepth=0;

			//we only support single non-mipmapped non-cubemap textures..
			header.numberOfArrayElements=0;
			header.numberOfFaces=1;
			header.numberOfMipmapLevels=1;

			//and no metadata..
			header.bytesOfKeyValueData=0;
			
			int halfbytes=1;
			//header.glInternalFormat=?
			//header.glBaseInternalFormat=?
			if(format==ETC2PACKAGE_R_NO_MIPMAPS) 
			{
				header.glBaseInternalFormat=GL_R;
				if(formatSigned)
					header.glInternalFormat=GL_COMPRESSED_SIGNED_R11_EAC;
				else
					header.glInternalFormat=GL_COMPRESSED_R11_EAC;
			}
			else if(format==ETC2PACKAGE_RG_NO_MIPMAPS) 
			{
				halfbytes=2;
				header.glBaseInternalFormat=GL_RG;
				if(formatSigned)
					header.glInternalFormat=GL_COMPRESSED_SIGNED_RG11_EAC;
				else
					header.glInternalFormat=GL_COMPRESSED_RG11_EAC;
			}
			else if(format==ETC2PACKAGE_RGB_NO_MIPMAPS) 
			{
				header.glBaseInternalFormat=GL_RGB;
				header.glInternalFormat=GL_COMPRESSED_RGB8_ETC2;
			}
			else if(format==ETC2PACKAGE_sRGB_NO_MIPMAPS) 
			{
				header.glBaseInternalFormat=GL_SRGB;
				header.glInternalFormat=GL_COMPRESSED_SRGB8_ETC2;
			}
			else if(format==ETC2PACKAGE_RGBA_NO_MIPMAPS) 
			{
				halfbytes=2;
				header.glBaseInternalFormat=GL_RGBA;
				header.glInternalFormat=GL_COMPRESSED_RGBA8_ETC2_EAC;
			}
			else if(format==ETC2PACKAGE_sRGBA_NO_MIPMAPS) 
			{
				halfbytes=2;
				header.glBaseInternalFormat=GL_SRGB8_ALPHA8;
				header.glInternalFormat=GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC;
			}
			else if(format==ETC2PACKAGE_RGBA1_NO_MIPMAPS) 
			{
				header.glBaseInternalFormat=GL_RGBA;
				header.glInternalFormat=GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2;
			}
			else if(format==ETC2PACKAGE_sRGBA1_NO_MIPMAPS) 
			{
				header.glBaseInternalFormat=GL_SRGB8_ALPHA8;
				header.glInternalFormat=GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2;
			}
			else if(format==ETC1_RGB_NO_MIPMAPS) 
			{
				header.glBaseInternalFormat=GL_RGB;
				header.glInternalFormat=GL_ETC1_RGB8_OES;
			}
			else 
			{
				printf("internal error: bad format!\n");
				exit(1);
			}
			//write header
			fwrite(&header,sizeof(KTX_header),1,f);
			
			//write size of compressed data.. which depend on the expanded size..
			unsigned int imagesize=(w*h*halfbytes)/2;
			fwrite(&imagesize,sizeof(int),1,f);
		}
		else 
		{
			//.pkm file, contains small header..

			// Write magic number
			fwrite(&magic[0], sizeof(unsigned char), 1, f);
			fwrite(&magic[1], sizeof(unsigned char), 1, f);
			fwrite(&magic[2], sizeof(unsigned char), 1, f);
			fwrite(&magic[3], sizeof(unsigned char), 1, f);
		
			// Write version
			fwrite(&version[0], sizeof(unsigned char), 1, f);
			fwrite(&version[1], sizeof(unsigned char), 1, f);

			// Write texture type
			if(texture_type==ETC2PACKAGE_RG_NO_MIPMAPS&&formatSigned) 
			{
				unsigned short temp = ETC2PACKAGE_RG_SIGNED_NO_MIPMAPS;
				write_big_endian_2byte_word(&temp,f);
			}
			else if(texture_type==ETC2PACKAGE_R_NO_MIPMAPS&&formatSigned) 
			{
				unsigned short temp = ETC2PACKAGE_R_SIGNED_NO_MIPMAPS;
				write_big_endian_2byte_word(&temp,f);
			}
			else
				write_big_endian_2byte_word(&texture_type, f);

			// Write binary header: the width and height as unsigned 16-bit words
			write_big_endian_2byte_word(&wi, f);
			write_big_endian_2byte_word(&hi, f);

			// Also write the active pixels. For instance, if we want to compress
			// a 128 x 129 image, we have to extend it to 128 x 132 pixels.
			// Then the wi and hi written above will be 128 and 132, but the
			// additional information that we write below will be 128 and 129,
			// to indicate that it is only the top 129 lines of data in the 
			// decompressed image that will be valid data, and the rest will
			// be just garbage. 

			unsigned short activew, activeh;
			activew = width;
			activeh = height;

			write_big_endian_2byte_word(&activew, f);
			write_big_endian_2byte_word(&activeh, f);
		}
		int totblocks = expandedheight/4 * expandedwidth/4;
		int countblocks = 0;
		double percentageblocks=-1.0;
		double oldpercentageblocks;
		
		if(format==ETC2PACKAGE_RG_NO_MIPMAPS) 
		{
			//extract data from red and green channel into two alpha channels.
			//note that the image will be 16-bit per channel in this case.
			alphaimg= (unsigned char*)malloc(expandedwidth*expandedheight*2);
			alphaimg2=(unsigned char*)malloc(expandedwidth*expandedheight*2);
			setupAlphaTableAndValtab();
			if(!alphaimg||!alphaimg2) 
			{
				printf("failed allocating space for alpha buffers!\n");
				exit(1);
			}
			for(y=0;y<expandedheight;y++)
			{
				for(x=0;x<expandedwidth;x++)
				{
					alphaimg[2*(y*expandedwidth+x)]=img[6*(y*expandedwidth+x)];
					alphaimg[2*(y*expandedwidth+x)+1]=img[6*(y*expandedwidth+x)+1];
					alphaimg2[2*(y*expandedwidth+x)]=img[6*(y*expandedwidth+x)+2];
					alphaimg2[2*(y*expandedwidth+x)+1]=img[6*(y*expandedwidth+x)+3];
				}
			}
		}
		for(y=0;y<expandedheight/4;y++)
		{
			for(x=0;x<expandedwidth/4;x++)
			{
				countblocks++;
				oldpercentageblocks = percentageblocks;
				percentageblocks = 100.0*countblocks/(1.0*totblocks);
				//compress color channels
				if(codec==CODEC_ETC) 
				{
					if(metric==METRIC_NONPERCEPTUAL) 
					{
						if(speed==SPEED_FAST)
							compressBlockDiffFlipFast(img, imgdec, expandedwidth, expandedheight, 4*x, 4*y, block1, block2);
						else
#if EXHAUSTIVE_CODE_ACTIVE
							compressBlockETC1Exhaustive(img, imgdec, expandedwidth, expandedheight, 4*x, 4*y, block1, block2);		
#else
							printf("Not implemented in this version\n");
#endif
					}
					else 
					{
						if(speed==SPEED_FAST)
							compressBlockDiffFlipFastPerceptual(img, imgdec, expandedwidth, expandedheight, 4*x, 4*y, block1, block2);
						else
#if EXHAUSTIVE_CODE_ACTIVE
							compressBlockETC1ExhaustivePerceptual(img, imgdec, expandedwidth, expandedheight, 4*x, 4*y, block1, block2);	
#else
							printf("Not implemented in this version\n");
#endif
					}
				}
				else 
				{
					if(format==ETC2PACKAGE_R_NO_MIPMAPS||format==ETC2PACKAGE_RG_NO_MIPMAPS) 
					{
						//don't compress color
					}
					else if(format==ETC2PACKAGE_RGBA1_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA1_NO_MIPMAPS) 
					{
						//this is only available for fast/nonperceptual
						if(speed == SPEED_SLOW && first_time_message)
						{
							printf("Slow codec not implemented for RGBA1 --- using fast codec instead.\n");
							first_time_message = false;
						}
						compressBlockETC2Fast(img, alphaimg,imgdec, expandedwidth, expandedheight, 4*x, 4*y, block1, block2);
					}
					else if(metric==METRIC_NONPERCEPTUAL) 
					{
						if(speed==SPEED_FAST)
							compressBlockETC2Fast(img, alphaimg,imgdec, expandedwidth, expandedheight, 4*x, 4*y, block1, block2);
						else
#if EXHAUSTIVE_CODE_ACTIVE
							compressBlockETC2Exhaustive(img, imgdec, expandedwidth, expandedheight, 4*x, 4*y, block1, block2);		
#else
							printf("Not implemented in this version\n");
#endif
					}
					else 
					{
						if(speed==SPEED_FAST)
							compressBlockETC2FastPerceptual(img, imgdec, expandedwidth, expandedheight, 4*x, 4*y, block1, block2);
						else
#if EXHAUSTIVE_CODE_ACTIVE
							compressBlockETC2ExhaustivePerceptual(img, imgdec, expandedwidth, expandedheight, 4*x, 4*y, block1, block2);	
#else
							printf("Not implemented in this version\n");
#endif
					}
				}
				
				//compression of alpha channel in case of 4-bit alpha. Uses 8-bit alpha channel as input, and has 8-bit precision.
				if(format==ETC2PACKAGE_RGBA_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA_NO_MIPMAPS) 
				{
					uint8 alphadata[8];
					if(speed==SPEED_SLOW)
						compressBlockAlphaSlow(alphaimg,4*x,4*y,expandedwidth,expandedheight,alphadata);
					else
						compressBlockAlphaFast(alphaimg,4*x,4*y,expandedwidth,expandedheight,alphadata);
					//write the 8 bytes of alphadata into f.
					fwrite(alphadata,1,8,f);
				}

				//store compressed color channels
				if(format!=ETC2PACKAGE_R_NO_MIPMAPS&&format!=ETC2PACKAGE_RG_NO_MIPMAPS) 
				{
					write_big_endian_4byte_word(&block1, f);
					write_big_endian_4byte_word(&block2, f);
				}

				//1-channel or 2-channel alpha compression: uses 16-bit data as input, and has 11-bit precision
				if(format==ETC2PACKAGE_R_NO_MIPMAPS||format==ETC2PACKAGE_RG_NO_MIPMAPS) 
				{ 
					uint8 alphadata[8];
					compressBlockAlpha16(alphaimg,4*x,4*y,expandedwidth,expandedheight,alphadata);
					fwrite(alphadata,1,8,f);
				}
				//compression of second alpha channel in RG-compression
				if(format==ETC2PACKAGE_RG_NO_MIPMAPS) 
				{
					uint8 alphadata[8];
					compressBlockAlpha16(alphaimg2,4*x,4*y,expandedwidth,expandedheight,alphadata);
					fwrite(alphadata,1,8,f);
				}
#if 1
				if(verbose)
				{
					if(speed==SPEED_FAST) 
					{
						if( ((int)(percentageblocks) != (int)(oldpercentageblocks) ) || percentageblocks == 100.0)
							printf("Compressed %d of %d blocks, %.0f%% finished.\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", countblocks, totblocks, 100.0*countblocks/(1.0*totblocks));
					}
					else
						printf("Compressed %d of %d blocks, %.0f%% finished.\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", countblocks, totblocks, 100.0*countblocks/(1.0*totblocks));
				}
#endif
			}
		}
		printf("\n");
		fclose(f);
		printf("Saved file <%s>.\n",dstfile);
	}
}

// Compress an file.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void compressFile(char *srcfile,char *dstfile)
{
	uint8 *srcimg;
	int width,height;
	int extendedwidth, extendedheight;
	struct _timeb tstruct;
	int tstart;
	int tstop;
	// 0: compress from .any to .pkm with SPEED_FAST, METRIC_NONPERCEPTUAL, ETC 
	// 1: compress from .any to .pkm with SPEED_MEDIUM, METRIC_NONPERCEPTUAL, ETC
	// 2: compress from .any to .pkm with SPEED_SLOW, METRIC_NONPERCEPTUAL, ETC
	// 3: compress from .any to .pkm with SPEED_FAST, METRIC_PERCEPTUAL, ETC
	// 4: compress from .any to .pkm with SPEED_MEDIUM, METRIC_PERCEPTUAL, ETC
	// 5: compress from .any to .pkm with SPEED_SLOW, METRIC_PERCEPTUAL, ETC
	// 6: decompress from .pkm to .any
	// 7: calculate PSNR between .any and .any
	// 8: compress from .any to .pkm with SPEED_FAST, METRIC_NONPERCEPTUAL, ETC2 
	// 9: compress from .any to .pkm with SPEED_MEDIUM, METRIC_NONPERCEPTUAL, ETC2
	//10: compress from .any to .pkm with SPEED_SLOW, METRIC_NONPERCEPTUAL, ETC2
	//11: compress from .any to .pkm with SPEED_FAST, METRIC_PERCEPTUAL, ETC2
	//12: compress from .any to .pkm with SPEED_MEDIUM, METRIC_PERCEPTUAL, ETC2
	//13: compress from .any to .pkm with SPEED_SLOW, METRIC_PERCEPTUAL, ETC2

	printf("\n");
	if(codec==CODEC_ETC)
		printf("ETC codec, ");
	else
		printf("ETC2 codec, ");
	if(speed==SPEED_FAST)
		printf("using FAST compression mode and ");
	else if(speed==SPEED_MEDIUM)
		printf("using MEDIUM compression mode and ");
	else
		printf("using SLOW compression mode and ");
	if(metric==METRIC_PERCEPTUAL)
		printf("PERCEPTUAL error metric, ");
	else
		printf("NONPERCEPTUAL error metric, ");
	if(format==ETC2PACKAGE_RGBA_NO_MIPMAPS)
		printf("in RGBA format");
	else if(format==ETC2PACKAGE_sRGBA_NO_MIPMAPS)
		printf("in sRGBA format");
	else if(format==ETC2PACKAGE_RGBA1_NO_MIPMAPS)
		printf("in RGB + punch-through alpha format");
	else if(format==ETC2PACKAGE_sRGBA1_NO_MIPMAPS)
		printf("in sRGB + punch-through alpha format");
	else if(format==ETC2PACKAGE_R_NO_MIPMAPS)
		printf("in R format");
	else if(format==ETC2PACKAGE_RGB_NO_MIPMAPS||format==ETC1_RGB_NO_MIPMAPS)
		printf("in RGB format");
	else if(format==ETC2PACKAGE_RG_NO_MIPMAPS)
		printf("in RG format");
	else
		printf("in OTHER format");
	printf("\n");
	if(readCompressParams())
	{
		if(format==ETC2PACKAGE_R_NO_MIPMAPS||readSrcFile(srcfile,srcimg,width,height,extendedwidth, extendedheight))
		{
			//make sure that alphasrcimg contains the alpha channel or is null here, and pass it to compressimagefile
			uint8* alphaimg=NULL;
			if(format==ETC2PACKAGE_RGBA_NO_MIPMAPS||format==ETC2PACKAGE_RGBA1_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA_NO_MIPMAPS||format==ETC2PACKAGE_sRGBA1_NO_MIPMAPS) 
			{
				char str[300];
				//printf("reading alpha channel....");
				sprintf(str,"magick convert %s -alpha extract alpha.pgm\n",srcfile);
				system(str);
				readAlpha(alphaimg,width,height,extendedwidth,extendedheight);
				printf("ok!\n");
				setupAlphaTableAndValtab();
			}
			else if(format==ETC2PACKAGE_R_NO_MIPMAPS) 
			{
				char str[300];
				sprintf(str,"magick convert %s alpha.pgm\n",srcfile);
				system(str);
				readAlpha(alphaimg,width,height,extendedwidth,extendedheight);
				printf("read alpha ok, size is %d,%d (%d,%d)",width,height,extendedwidth,extendedheight);
				setupAlphaTableAndValtab();
			}
			printf("Compressing...\n");

			tstart=time(NULL);
			_ftime( &tstruct );
			tstart=tstart*1000+tstruct.millitm;
			compressImageFile(srcimg,alphaimg,width,height,dstfile,extendedwidth, extendedheight);			
			tstop = time(NULL);
			_ftime( &tstruct );
			tstop = tstop*1000+tstruct.millitm;
			printf( "It took %u milliseconds to compress:\n", tstop - tstart);
			calculatePSNRfile(dstfile,srcimg,alphaimg);
		}
	}
}

// Calculates the PSNR between two files.
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
double calculatePSNRTwoFiles(char *srcfile1,char *srcfile2)
{
	uint8 *srcimg1;
	uint8 *srcimg2;
	int width1, height1;
	int width2, height2;
	double PSNR;
	double perceptually_weighted_PSNR;

	if(readSrcFileNoExpand(srcfile1,srcimg1,width1,height1))
	{
		if(readSrcFileNoExpand(srcfile2,srcimg2,width2,height2))
		{
			if((width1 == width2) && (height1 == height2))
			{
				PSNR = calculatePSNR(srcimg1, srcimg2, width1, height1);
				printf("%f\n",PSNR);
				perceptually_weighted_PSNR = calculateWeightedPSNR(srcimg1, srcimg2, width1, height1, 0.299, 0.587, 0.114);
			}
			else
			{
				printf("\n Width and height do no not match for image: width, height = (%d, %d) and (%d, %d)\n",width1,height1, width2, height2);
			}
		}
		else
		{
			printf("Couldn't open file %s.\n",srcfile2);
		}
	}
	else
	{
		printf("Couldn't open file %s.\n",srcfile1);
	}

	return PSNR;
}

// Main function
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
int main(int argc,char *argv[])
{
	if(argc==3 || argc==4 || argc == 5 || argc == 7 || argc == 9 || argc == 11 || argc == 13)
	{
		// The source file is always the second last one. 
		char srcfile[200];
		char dstfile[200];
		readArguments(argc,argv,srcfile,dstfile);
		
		int q = find_pos_of_extension(srcfile);
		int q2 = find_pos_of_extension(dstfile);
		
		if(!fileExist(srcfile))
		{
			printf("Error: file <%s> does not exist.\n",srcfile);
			exit(0);
		}
		
		if(mode==MODE_UNCOMPRESS)
		{
			printf("Decompressing .pkm/.ktx file ...\n");
			uint8* alphaimg=NULL, *img;
			int w, h;
			uncompressFile(srcfile,img,alphaimg,w,h);
			writeOutputFile(dstfile,img,alphaimg,w,h);
		}
		else if(mode==MODE_PSNR)
		{
			calculatePSNRTwoFiles(srcfile,dstfile);
		}
		else
		{
			compressFile(srcfile, dstfile);
		}
	}
	else
	{
		printf("ETCPACK v2.74 For ETC and ETC2\n");
		printf("Compresses and decompresses images using the Ericsson Texture Compression (ETC) version 1.0 and 2.0.\n\nUsage: etcpack srcfile dstfile\n\n");
		printf("      -s {fast|slow}                     Compression speed. Slow = exhaustive \n");
		printf("                                         search for optimal quality\n");
		printf("                                         (default: fast)\n");
		printf("      -e {perceptual|nonperceptual}      Error metric: Perceptual (nicest) or \n");
		printf("                                         nonperceptual (highest PSNR)\n");
		printf("                                         (default: perceptual)\n");
		printf("      -c {etc1|etc2}                     Codec: etc1 (most compatible) or \n");
		printf("                                         etc2 (highest quality)\n");
		printf("                                         (default: etc2)\n");
		printf("      -f {R|R_signed|RG|RG_signed|       Format: one, two, three or four \n");
		printf("          RGB|RGBA1|RGBA8|               channels, and 1 or 8 bits for alpha\n");
        printf("          sRGB|sRGBA1|sRGBA8|}           RGB or sRGB.\n");
		printf("                                         (1 equals punchthrough)\n");
		printf("                                         (default: RGB)\n");
		printf("      -v {on|off}                        Detailed progress info. (default on)\n");
		printf("                                                            \n");
		printf("Examples: \n");
		printf("  etcpack img.ppm img.pkm                Compresses img.ppm to img.pkm in\n"); 
		printf("                                         ETC2 RGB format\n");
		printf("  etcpack img.ppm img.ktx                Compresses img.ppm to img.ktx in\n"); 
		printf("                                         ETC2 RGB format\n");
		printf("  etcpack img.pkm img_copy.ppm           Decompresses img.pkm to img_copy.ppm\n");
		printf("  etcpack -s slow img.ppm img.pkm        Compress using the slow mode.\n");
		printf("  etcpack -p orig.ppm copy.ppm           Calculate PSNR between orig and copy\n");
		printf("  etcpack -f RGBA8 img.tga img.pkm       Compresses img.tga to img.pkm, using \n");
		printf("                                         etc2 + alpha.\n");
		printf("  etcpack -f RG img.ppm img.pkm          Compresses red and green channels of\n");
		printf("                                         img.ppm\n");
	}
 	return 0;
}
