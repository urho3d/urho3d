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
#include "image.h"

// Remove warnings for unsafe functions such as strcpy
#pragma warning(disable : 4996)
// Remove warnings for conversions between different time variables
#pragma warning(disable : 4244)

// Removes comments in a .ppm file
// (i.e., lines starting with #)
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void removeComments(FILE *f1)
{
	int c;

	while((c = getc(f1)) == '#')
	{
		char line[1024];
		fgets(line, 1024, f1);
	}
	ungetc(c, f1);
}


// Removes white spaces in a .ppm file
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
void removeSpaces(FILE *f1)
{
	int c;

	c = getc(f1);
	while(c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r')
	{
		c = getc(f1);
	}
	ungetc(c, f1);
}

// fReadPPM
//
// reads a ppm file with P6 header (meaning binary, as opposed to P5, which is ascII)
// and returns the image in pixels.
//
// The header must look like this:
// 
// P6
// # Comments (not necessary)
// width height
// 255
//
// after that follows RGBRGBRGB...
// 
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
bool fReadPPM(char *filename, int &width, int &height, unsigned char *&pixels, int targetbitrate)
{
	FILE *f1;
	int maximum;
	f1 = fopen(filename, "rb");

	if(f1)
	{
		char line[255];

		removeSpaces(f1);
		removeComments(f1);
		removeSpaces(f1);

		fscanf(f1, "%s", line);

		if(strcmp(line, "P6")!=0)
		{
			printf("Error: %s is not binary\n");
			printf("(Binary .ppm files start with P6).\n");
			fclose(f1);
			return false;
		}
		removeSpaces(f1);
		removeComments(f1);
		removeSpaces(f1);
		
		fscanf(f1, "%d %d", &width, &height);
		if( width<=0 || height <=0)
		{
			printf("Error: width or height negative. File: %s\n",filename);
			fclose(f1);
			return false;
		}

		removeSpaces(f1);
		removeComments(f1);
		removeSpaces(f1);

		fscanf(f1, "%d", &maximum);
		if( maximum!= 255&&maximum!=(1<<16)-1)
		{
			printf("Error: Color resolution must be 255. File: %s\n",filename);
			fclose(f1);
			return false;
		}

		//printf("maximum is %d\n",maximum);
		int bitrate=8;
		if(maximum!=255)
			bitrate=16;

		// We need to remove the newline.
		char c = 0;
		while(c != '\n')
			fscanf(f1, "%c", &c);
		
		unsigned char* readbuffer = (unsigned char*) malloc(3*width*height*bitrate/8);
		if(!readbuffer)
		{
			printf("Error: Could not allocate memory for image. File: %s\n", filename);
			fclose(f1);
			return false;
		}

		if(fread(readbuffer, 3*width*height*bitrate/8, 1, f1) != 1)
		{
			printf("Error: Could not read all pixels. File: %s\n", filename);
			free(pixels);
			fclose(f1);
			return false;
		}

		// If we have reached this point, we have successfully loaded the image.

		//now, convert it to the target bitrate
		if(targetbitrate==bitrate)
			pixels=readbuffer;
		else 
		{
			pixels = (unsigned char*) malloc(3*width*height*targetbitrate/8);
			if(targetbitrate<bitrate) 
			{
				//cut least significant bits to go from 16 -> 8 bits..
				printf("converting 16 bit input to 8 bits\n");
				for(int x=0; x<width; x++) 
				{
					for(int y=0; y<height; y++) 
					{
						for(int c=0; c<3; c++) 
						{
							pixels[3*(x+y*width)+c]=readbuffer[6*(x+y*width)+2*c];
						}
					}
				}
			}
			else 
			{
				//replicate 8 bits to go from 8 -> 16 bits...
				printf("converting 8 bit input to 16 bits\n");
				for(int x=0; x<width; x++) 
				{
					for(int y=0; y<height; y++) 
					{
						for(int c=0; c<3; c++) 
						{
							pixels[6*(x+y*width)+2*c]=readbuffer[3*(x+y*width)+c];
							pixels[6*(x+y*width)+2*c+1]=readbuffer[3*(x+y*width)+c];
						}
					}
				}
			}
			free(readbuffer);
		}
		fclose(f1);
		return true;
	}
	else
	{
		printf("Error: Coult not open file %s\n", filename);
		return false;
	}
}

// Write PPM 
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
bool fWritePPM(char *filename, int width, int height, unsigned char *pixels, int bitrate, bool reverse_y)
{
	FILE *fsave;
	fsave = fopen(filename, "wb");
	int max = (1<<bitrate)-1;
	int fac = bitrate/8;
	if(fsave)
	{
		int q;
		fprintf(fsave, "P6\n%d %d\n%d\n", width, height,max);
		for(q = 0; q< height; q++)
		{
			unsigned char *adr;
			if(reverse_y) 
				adr = pixels+3*width*(height-1-q)*fac;
			else
				adr = pixels+3*width*q*fac;
			fwrite(adr, 3*width*fac, 1, fsave);
		}
		fclose(fsave);
		return true;
	}
	else
	{
		printf("Error: Could not open the file %s.\n",filename);
		return(false);
	}
}

// WritePGM
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
bool fWritePGM(char *filename, int width, int height, unsigned char *pixels,bool reverse_y, int bitdepth)
{
   FILE *f;
   f=fopen(filename,"wb");
   if(f)
   {
      int q;
	  int max = (1<<bitdepth)-1;
      fprintf(f,"P5\n%d %d\n%d\n",width,height,max);
	  if(bitdepth==16)
		  width*=2; //ugly way of doubling the number of bytes to write, since we write one line at a time..
      for(q=0;q<height;q++)
      {
		 unsigned char *adr;	 
		 if(reverse_y) adr=pixels+width*(height-1-q);
		 else adr=pixels+width*q;
		 fwrite(adr,width,1,f);
      }
      fclose(f);
      return true;
   }
   else
   {
      printf("Error: could not open file <%s>.\n",filename);
      return false;
   }
}

/* reads a ppm file with the P6 header (means raw RGB), puts data into pixel pointer and returns bit depth (8 or 16 bpp) */
/* the header looks like this:
 *---------
 * P5
 * # comments if you want to
 * width height
 * 255
 *---------
 * then follows RGBRGBRGBRGBRGB...
 */
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2005-2013. All Rights Reserved.
int fReadPGM(char *filename, int &width, int &height, unsigned char *&pixels, int wantedBitDepth)
{
	FILE *f;
	int colres;
	int bitdepth=8;
	f=fopen(filename,"rb");
	if(f)
	{
		char str[100];
		removeSpaces(f);
		removeComments(f);
		removeSpaces(f);
		fscanf(f,"%s",str);
		if(strcmp(str,"P5")!=0)
		{
			printf("Error: the alpha image file must be of raw color PGM format,\n");
			printf("i.e., it must have P5 in the header. File: %s\n",filename);
			fclose(f);
			return 0;
		}
		removeSpaces(f);
		removeComments(f);
		removeSpaces(f);
		fscanf(f,"%d %d",&width,&height);
		if(width<=0 || height<=0)
		{
			printf("Error: width and height of the image must be greater than zero. File: %s\n",filename);
			fclose(f);
			return 0;
		}
		removeSpaces(f);
		removeComments(f);
		removeSpaces(f);
		fscanf(f,"%d",&colres);
		if(colres!=255&&colres!=65535)
		{
			printf("Error: color resolution must be 255 or 65535.File: %s\n",filename);
			fclose(f);
			return 0;
		}
		if(colres==65535)
			bitdepth=16;

		/* gotta eat the newline too */
		char ch=0;
		while(ch!='\n') fscanf(f,"%c",&ch);

		pixels=(unsigned char*)malloc(width*height*bitdepth/8);
		if(!pixels)
		{
			printf("Error: could not allocate memory for the pixels of the texture. File: %s\n",filename);
			fclose(f);
			return 0;	 
		}
      
		if(fread(pixels,width*height*bitdepth/8,1,f)!=1)
		{
			printf("Error: could not read %d bytes of pixel info. File: %s\n",width*height*bitdepth/8,filename);
			free(pixels);
			fclose(f);
			return 0;
		}
		fclose(f);
		printf("read %d-bit alpha channel",bitdepth);
		if(bitdepth!=wantedBitDepth) 
		{
			printf(", converting to %d-bit!",wantedBitDepth);
			unsigned char* newpixels = (unsigned char*)malloc(width*height*wantedBitDepth/8);
			for(int x=0; x<width; x++) 
			{
				for(int y=0; y<height; y++) 
				{
					if(bitdepth<wantedBitDepth) 
					{
						//do bit-replication to get 2-bytes per pixel
						newpixels[2*(x+y*width)]=pixels[x+y*width];
						newpixels[2*(x+y*width)+1]=pixels[x+y*width];
					}
					else 
					{
						//simply truncate the extra data..
						newpixels[(x+y*width)]=pixels[2*(x+y*width)];
					}
				}
			}
			free(pixels);
			pixels=newpixels;
		}
		printf("\n");
		return bitdepth;
	}
	else
	{
		printf("Error: could not open %s.\n",filename);
		return 0;
	}   
}
/* writes a .tga file from two arrays --- one RGB array and one alpha-array */
/* */
// NO WARRANTY --- SEE STATEMENT IN TOP OF FILE (C) Ericsson AB 2012. All Rights Reserved.
bool fWriteTGAfromRGBandA(char *filename, int width, int height, unsigned char *pixelsRGB, unsigned char *pixelsA, bool reverse_y)
{
	FILE *f1;

	if( (f1 = fopen(filename,"wb")) == NULL)
	{
		return false;
	}

	// First write header
    unsigned char myByteVal;
    short myShortVal;
    myByteVal = 0;
    fwrite(&myByteVal, 1, 1, f1); // ID field (0)
    fwrite(&myByteVal, 1, 1, f1); // Palette? (no=0)
    myByteVal = 2; 
    fwrite(&myByteVal, 1, 1, f1); // Image type (rgb=2)
    myShortVal = 0;
    fwrite(&myShortVal, 2, 1, f1); // Palette stuff... 0
    fwrite(&myShortVal, 2, 1, f1); // Palette stuff... 0
    myByteVal = 0;
    fwrite(&myByteVal, 1, 1, f1); // Palette stuff... 0
    myShortVal = 0;
    fwrite(&myShortVal, 2, 1, f1); // x-origin
    myShortVal = 0;
    fwrite(&myShortVal, 2, 1, f1); // y-origin
    myShortVal = width;
    fwrite(&myShortVal, 2, 1, f1); // width
    myShortVal = height;
    fwrite(&myShortVal, 2, 1, f1); // height
    myByteVal = 32;
    fwrite(&myByteVal, 1, 1, f1); // Bits per pixel = 32
    myByteVal = 8;
    fwrite(&myByteVal, 1, 1, f1); // flip bits = 8
   
	// Write pixels in BGRA format
	if(reverse_y)
	{
		int xx, yy;
		for(yy = height-1; yy>=0; yy--)
		{
			for(xx = 0; xx<width; xx++)
			{
				fwrite(&pixelsRGB[3*(yy*width+xx)+2], sizeof(unsigned char), 1, f1); // B
				fwrite(&pixelsRGB[3*(yy*width+xx)+1], sizeof(unsigned char), 1, f1); // G
				fwrite(&pixelsRGB[3*(yy*width+xx)+0], sizeof(unsigned char), 1, f1); // R
				fwrite(&pixelsA[(yy*width+xx)], sizeof(unsigned char), 1, f1); // A
			}
		}
	}
	else
	{
		for(int q = 0; q< width * height; q++)
		{
			fwrite(&pixelsRGB[3*q+2], sizeof(unsigned char), 1, f1); // B
			fwrite(&pixelsRGB[3*q+1], sizeof(unsigned char), 1, f1); // G
			fwrite(&pixelsRGB[3*q+0], sizeof(unsigned char), 1, f1); // R
			fwrite(&pixelsA[1*q], sizeof(unsigned char), 1, f1); // A
		}
	}
	fclose(f1);
	return true;
}
