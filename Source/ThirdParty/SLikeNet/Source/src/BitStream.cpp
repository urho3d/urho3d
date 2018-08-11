/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2018, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/// \file
///

#include "slikenet/BitStream.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "slikenet/SocketIncludes.h"
#include "slikenet/defines.h"



#if   defined(_WIN32)
#include "slikenet/WindowsIncludes.h"
#include <memory.h>
#include <cmath>
#include <float.h>




#else
#include <arpa/inet.h>
#include <memory.h>
#if defined(__ANDROID__)
#include <math.h>
#else
#include <cmath>
#endif
#include <float.h>
#endif
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

// MSWin uses _copysign, others use copysign...
#ifndef _WIN32
#define _copysign copysign
#endif

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(BitStream,BitStream)

BitStream::BitStream()
{
	numberOfBitsUsed = 0;
	//numberOfBitsAllocated = 32 * 8;
	numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE * 8;
	readOffset = 0;
	//data = ( unsigned char* ) rakMalloc_Ex( 32, _FILE_AND_LINE_ );
	data = ( unsigned char* ) stackData;

#ifdef _DEBUG	
	//	RakAssert( data );
#endif
	//memset(data, 0, 32);
	copyData = true;
}

BitStream::BitStream( const unsigned int initialBytesToAllocate )
{
	numberOfBitsUsed = 0;
	readOffset = 0;
	if (initialBytesToAllocate <= BITSTREAM_STACK_ALLOCATION_SIZE)
	{
		data = ( unsigned char* ) stackData;
		numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE * 8;
	}
	else
	{
		data = ( unsigned char* ) rakMalloc_Ex( (size_t) initialBytesToAllocate, _FILE_AND_LINE_ );
		numberOfBitsAllocated = initialBytesToAllocate << 3;
	}
#ifdef _DEBUG
	RakAssert( data );
#endif
	// memset(data, 0, initialBytesToAllocate);
	copyData = true;
}

BitStream::BitStream( unsigned char* _data, const unsigned int lengthInBytes, bool _copyData )
{
	numberOfBitsUsed = lengthInBytes << 3;
	readOffset = 0;
	copyData = _copyData;
	numberOfBitsAllocated = lengthInBytes << 3;

	if ( copyData )
	{
		if ( lengthInBytes > 0 )
		{
			if (lengthInBytes < BITSTREAM_STACK_ALLOCATION_SIZE)
			{
				data = ( unsigned char* ) stackData;
				numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE << 3;
			}
			else
			{
				data = ( unsigned char* ) rakMalloc_Ex( (size_t) lengthInBytes, _FILE_AND_LINE_ );
			}
#ifdef _DEBUG
			RakAssert( data );
#endif
			memcpy( data, _data, (size_t) lengthInBytes );
		}
		else
			data = 0;
	}
	else
		data = ( unsigned char* ) _data;
}

// Use this if you pass a pointer copy to the constructor (_copyData==false) and want to overallocate to prevent reallocation
void BitStream::SetNumberOfBitsAllocated( const BitSize_t lengthInBits )
{
#ifdef _DEBUG
	RakAssert( lengthInBits >= ( BitSize_t ) numberOfBitsAllocated );
#endif	
	numberOfBitsAllocated = lengthInBits;
}

BitStream::~BitStream()
{
	if ( copyData && numberOfBitsAllocated > (BITSTREAM_STACK_ALLOCATION_SIZE << 3))
		rakFree_Ex( data , _FILE_AND_LINE_ );  // Use realloc and free so we are more efficient than delete and new for resizing
}

void BitStream::Reset( void )
{
	// Note:  Do NOT reallocate memory because BitStream is used
	// in places to serialize/deserialize a buffer. Reallocation
	// is a dangerous operation (may result in leaks).

	if ( numberOfBitsUsed > 0 )
	{
		//  memset(data, 0, BITS_TO_BYTES(numberOfBitsUsed));
	}

	// Don't free memory here for speed efficiency
	//free(data);  // Use realloc and free so we are more efficient than delete and new for resizing
	numberOfBitsUsed = 0;

	//numberOfBitsAllocated=8;
	readOffset = 0;

	//data=(unsigned char*)rakMalloc_Ex(1, _FILE_AND_LINE_);
	// if (numberOfBitsAllocated>0)
	//  memset(data, 0, BITS_TO_BYTES(numberOfBitsAllocated));
}

// Write an array or casted stream
void BitStream::Write( const char* inputByteArray, const unsigned int numberOfBytes )
{
	if (numberOfBytes==0)
		return;

	// Optimization:
	if ((numberOfBitsUsed & 7) == 0)
	{
		AddBitsAndReallocate( BYTES_TO_BITS(numberOfBytes) );
		memcpy(data+BITS_TO_BYTES(numberOfBitsUsed), inputByteArray, (size_t) numberOfBytes);
		numberOfBitsUsed+=BYTES_TO_BITS(numberOfBytes);
	}
	else
	{
		WriteBits( ( unsigned char* ) inputByteArray, numberOfBytes * 8, true );
	}

}
void BitStream::Write( BitStream *bitStream)
{
	Write(bitStream, bitStream->GetNumberOfBitsUsed()-bitStream->GetReadOffset());
}
void BitStream::Write( BitStream *bitStream, BitSize_t numberOfBits )
{
	AddBitsAndReallocate( numberOfBits );
	BitSize_t numberOfBitsMod8;

	if ((bitStream->GetReadOffset()&7)==0 && (numberOfBitsUsed&7)==0)
	{
		int readOffsetBytes=bitStream->GetReadOffset()/8;
		int numBytes=numberOfBits/8;
		memcpy(data + (numberOfBitsUsed >> 3), bitStream->GetData()+readOffsetBytes, numBytes);
		numberOfBits-=BYTES_TO_BITS(numBytes);
		bitStream->SetReadOffset(BYTES_TO_BITS(numBytes+readOffsetBytes));
		numberOfBitsUsed+=BYTES_TO_BITS(numBytes);
	}

	while (numberOfBits-->0 && bitStream->readOffset + 1 <= bitStream->numberOfBitsUsed)
	{
		numberOfBitsMod8 = numberOfBitsUsed & 7;
		if ( numberOfBitsMod8 == 0 )
		{
			// New byte
			if (bitStream->data[ bitStream->readOffset >> 3 ] & ( 0x80 >> ( bitStream->readOffset & 7 ) ) )
			{
				// Write 1
				data[ numberOfBitsUsed >> 3 ] = 0x80;
			}
			else
			{
				// Write 0
				data[ numberOfBitsUsed >> 3 ] = 0;
			}

		}
		else
		{
			// Existing byte
			if (bitStream->data[ bitStream->readOffset >> 3 ] & ( 0x80 >> ( bitStream->readOffset & 7 ) ) )
				data[ numberOfBitsUsed >> 3 ] |= 0x80 >> ( numberOfBitsMod8 ); // Set the bit to 1
			// else 0, do nothing
		}

		bitStream->readOffset++;
		numberOfBitsUsed++;
	}
}
void BitStream::Write( BitStream &bitStream, BitSize_t numberOfBits )
{
	Write(&bitStream, numberOfBits);
}
void BitStream::Write( BitStream &bitStream )
{
	Write(&bitStream);
}
bool BitStream::Read( BitStream *bitStream, BitSize_t numberOfBits )
{
	if (GetNumberOfUnreadBits() < numberOfBits)
		return false;
	bitStream->Write(this, numberOfBits);
	return true;
}
bool BitStream::Read( BitStream *bitStream )
{
	bitStream->Write(this);
	return true;
}
bool BitStream::Read( BitStream &bitStream, BitSize_t numberOfBits )
{
	if (GetNumberOfUnreadBits() < numberOfBits)
		return false;
	bitStream.Write(this, numberOfBits);
	return true;
}
bool BitStream::Read( BitStream &bitStream )
{
	bitStream.Write(this);
	return true;
}

// Read an array or casted stream
bool BitStream::Read( char* outByteArray, const unsigned int numberOfBytes )
{
	// Optimization:
	if ((readOffset & 7) == 0)
	{
		if ( readOffset + ( numberOfBytes << 3 ) > numberOfBitsUsed )
			return false;

		// Write the data
		memcpy( outByteArray, data + ( readOffset >> 3 ), (size_t) numberOfBytes );

		readOffset += numberOfBytes << 3;
		return true;
	}
	else
	{
		return ReadBits( ( unsigned char* ) outByteArray, numberOfBytes * 8 );
	}
}

// Sets the read pointer back to the beginning of your data.
void BitStream::ResetReadPointer( void )
{
	readOffset = 0;
}

// Sets the write pointer back to the beginning of your data.
void BitStream::ResetWritePointer( void )
{
	numberOfBitsUsed = 0;
}

// Write a 0
void BitStream::Write0( void )
{
	AddBitsAndReallocate( 1 );

	// New bytes need to be zeroed
	if ( ( numberOfBitsUsed & 7 ) == 0 )
		data[ numberOfBitsUsed >> 3 ] = 0;

	numberOfBitsUsed++;
}

// Write a 1
void BitStream::Write1( void )
{
	AddBitsAndReallocate( 1 );

	BitSize_t numberOfBitsMod8 = numberOfBitsUsed & 7;

	if ( numberOfBitsMod8 == 0 )
		data[ numberOfBitsUsed >> 3 ] = 0x80;
	else
		data[ numberOfBitsUsed >> 3 ] |= 0x80 >> ( numberOfBitsMod8 ); // Set the bit to 1

	numberOfBitsUsed++;
}

// Returns true if the next data read is a 1, false if it is a 0
bool BitStream::ReadBit( void )
{
	bool result = ( data[ readOffset >> 3 ] & ( 0x80 >> ( readOffset & 7 ) ) ) !=0;
	readOffset++;
	return result;
}

// Align the bitstream to the byte boundary and then write the specified number of bits.
// This is faster than WriteBits but wastes the bits to do the alignment and requires you to call
// SetReadToByteAlignment at the corresponding read position
void BitStream::WriteAlignedBytes( const unsigned char* inByteArray, const unsigned int numberOfBytesToWrite )
{
	AlignWriteToByteBoundary();
	Write((const char*) inByteArray, numberOfBytesToWrite);
}
void BitStream::EndianSwapBytes( int byteOffset, int length )
{
	if (DoEndianSwap())
	{
		ReverseBytesInPlace(data+byteOffset, length);
	}
}
/// Aligns the bitstream, writes inputLength, and writes input. Won't write beyond maxBytesToWrite
void BitStream::WriteAlignedBytesSafe( const char *inByteArray, const unsigned int inputLength, const unsigned int maxBytesToWrite )
{
	if (inByteArray==0 || inputLength==0)
	{
		WriteCompressed((unsigned int)0);
		return;
	}
	WriteCompressed(inputLength);
	WriteAlignedBytes((const unsigned char*) inByteArray, inputLength < maxBytesToWrite ? inputLength : maxBytesToWrite);
}

// Read bits, starting at the next aligned bits. Note that the modulus 8 starting offset of the
// sequence must be the same as was used with WriteBits. This will be a problem with packet coalescence
// unless you byte align the coalesced packets.
bool BitStream::ReadAlignedBytes( unsigned char* inOutByteArray, const unsigned int numberOfBytesToRead )
{
#ifdef _DEBUG
	RakAssert( numberOfBytesToRead > 0 );
#endif

	if ( numberOfBytesToRead <= 0 )
		return false;

	// Byte align
	AlignReadToByteBoundary();

	if ( readOffset + ( numberOfBytesToRead << 3 ) > numberOfBitsUsed )
		return false;

	// Write the data
	memcpy( inOutByteArray, data + ( readOffset >> 3 ), (size_t) numberOfBytesToRead );

	readOffset += numberOfBytesToRead << 3;

	return true;
}
bool BitStream::ReadAlignedBytesSafe( char *inOutByteArray, int &inputLength, const int maxBytesToRead )
{
	return ReadAlignedBytesSafe(inOutByteArray,(unsigned int&) inputLength,(unsigned int)maxBytesToRead);
}
bool BitStream::ReadAlignedBytesSafe( char *inOutByteArray, unsigned int &inputLength, const unsigned int maxBytesToRead )
{
	if (ReadCompressed(inputLength)==false)
		return false;
	if (inputLength > maxBytesToRead)
		inputLength=maxBytesToRead;
	if (inputLength==0)
		return true;
	return ReadAlignedBytes((unsigned char*) inOutByteArray, inputLength);
}
bool BitStream::ReadAlignedBytesSafeAlloc( char **outByteArray, int &inputLength, const unsigned int maxBytesToRead )
{
	return ReadAlignedBytesSafeAlloc(outByteArray,(unsigned int&) inputLength, maxBytesToRead);
}
bool BitStream::ReadAlignedBytesSafeAlloc( char ** outByteArray, unsigned int &inputLength, const unsigned int maxBytesToRead )
{
	rakFree_Ex(*outByteArray, _FILE_AND_LINE_ );
	*outByteArray=0;
	if (ReadCompressed(inputLength)==false)
		return false;
	if (inputLength > maxBytesToRead)
		inputLength=maxBytesToRead;
	if (inputLength==0)
		return true;
	*outByteArray = (char*) rakMalloc_Ex( (size_t) inputLength, _FILE_AND_LINE_ );
	return ReadAlignedBytes((unsigned char*) *outByteArray, inputLength);
}

// Write numberToWrite bits from the input source
void BitStream::WriteBits( const unsigned char* inByteArray, BitSize_t numberOfBitsToWrite, const bool rightAlignedBits )
{
//	if (numberOfBitsToWrite<=0)
//		return;

	AddBitsAndReallocate( numberOfBitsToWrite );

	const BitSize_t numberOfBitsUsedMod8 = numberOfBitsUsed & 7;

	// If currently aligned and numberOfBits is a multiple of 8, just memcpy for speed
	if (numberOfBitsUsedMod8==0 && (numberOfBitsToWrite&7)==0)
	{
		memcpy( data + ( numberOfBitsUsed >> 3 ), inByteArray, numberOfBitsToWrite>>3);
		numberOfBitsUsed+=numberOfBitsToWrite;
		return;
	}

	unsigned char dataByte;
	const unsigned char* inputPtr=inByteArray;

	// Faster to put the while at the top surprisingly enough
	while ( numberOfBitsToWrite > 0 )
		//do
	{
		dataByte = *( inputPtr++ );

		if ( numberOfBitsToWrite < 8 && rightAlignedBits )   // rightAlignedBits means in the case of a partial byte, the bits are aligned from the right (bit 0) rather than the left (as in the normal internal representation)
			dataByte <<= 8 - numberOfBitsToWrite;  // shift left to get the bits on the left, as in our internal representation

		// Writing to a new byte each time
		if ( numberOfBitsUsedMod8 == 0 )
			* ( data + ( numberOfBitsUsed >> 3 ) ) = dataByte;
		else
		{
			// Copy over the new data.
			*( data + ( numberOfBitsUsed >> 3 ) ) |= dataByte >> ( numberOfBitsUsedMod8 ); // First half

			if ( 8 - ( numberOfBitsUsedMod8 ) < 8 && 8 - ( numberOfBitsUsedMod8 ) < numberOfBitsToWrite )   // If we didn't write it all out in the first half (8 - (numberOfBitsUsed%8) is the number we wrote in the first half)
			{
				*( data + ( numberOfBitsUsed >> 3 ) + 1 ) = (unsigned char) ( dataByte << ( 8 - ( numberOfBitsUsedMod8 ) ) ); // Second half (overlaps byte boundary)
			}
		}

		if ( numberOfBitsToWrite >= 8 )
		{
			numberOfBitsUsed += 8;
			numberOfBitsToWrite -= 8;
		}
		else
		{
			numberOfBitsUsed += numberOfBitsToWrite;
			numberOfBitsToWrite=0;
		}
	}
	// } while(numberOfBitsToWrite>0);
}

// Set the stream to some initial data.  For internal use
void BitStream::SetData( unsigned char *inByteArray )
{
	data=inByteArray;
	copyData=false;
}

// Assume the input source points to a native type, compress and write it
void BitStream::WriteCompressed( const unsigned char* inByteArray,
								const unsigned int size, const bool unsignedData )
{
	BitSize_t currentByte = ( size >> 3 ) - 1; // PCs

	unsigned char byteMatch;

	if ( unsignedData )
	{
		byteMatch = 0;
	}

	else
	{
		byteMatch = 0xFF;
	}

	// Write upper bytes with a single 1
	// From high byte to low byte, if high byte is a byteMatch then write a 1 bit. Otherwise write a 0 bit and then write the remaining bytes
	while ( currentByte > 0 )
	{
		if ( inByteArray[ currentByte ] == byteMatch )   // If high byte is byteMatch (0 of 0xff) then it would have the same value shifted
		{
			bool b = true;
			Write( b );
		}
		else
		{
			// Write the remainder of the data after writing 0
			bool b = false;
			Write( b );

			WriteBits( inByteArray, ( currentByte + 1 ) << 3, true );
			//  currentByte--;


			return ;
		}

		currentByte--;
	}

	// If the upper half of the last byte is a 0 (positive) or 16 (negative) then write a 1 and the remaining 4 bits.  Otherwise write a 0 and the 8 bites.
	if ( ( unsignedData && ( ( *( inByteArray + currentByte ) ) & 0xF0 ) == 0x00 ) ||
		( unsignedData == false && ( ( *( inByteArray + currentByte ) ) & 0xF0 ) == 0xF0 ) )
	{
		bool b = true;
		Write( b );
		WriteBits( inByteArray + currentByte, 4, true );
	}

	else
	{
		bool b = false;
		Write( b );
		WriteBits( inByteArray + currentByte, 8, true );
	}
}

// Read numberOfBitsToRead bits to the output source
// alignBitsToRight should be set to true to convert internal bitstream data to userdata
// It should be false if you used WriteBits with rightAlignedBits false
bool BitStream::ReadBits( unsigned char *inOutByteArray, BitSize_t numberOfBitsToRead, const bool alignBitsToRight )
{
#ifdef _DEBUG
	//	RakAssert( numberOfBitsToRead > 0 );
#endif
	if (numberOfBitsToRead<=0)
		return false;

	if ( readOffset + numberOfBitsToRead > numberOfBitsUsed )
		return false;


	const BitSize_t readOffsetMod8 = readOffset & 7;

	// If currently aligned and numberOfBits is a multiple of 8, just memcpy for speed
	if (readOffsetMod8==0 && (numberOfBitsToRead&7)==0)
	{
		memcpy( inOutByteArray, data + ( readOffset >> 3 ), numberOfBitsToRead>>3);
		readOffset+=numberOfBitsToRead;
		return true;
	}



	BitSize_t offset = 0;

	memset( inOutByteArray, 0, (size_t) BITS_TO_BYTES( numberOfBitsToRead ) );

	while ( numberOfBitsToRead > 0 )
	{
		*( inOutByteArray + offset ) |= *( data + ( readOffset >> 3 ) ) << ( readOffsetMod8 ); // First half

		if ( readOffsetMod8 > 0 && numberOfBitsToRead > 8 - ( readOffsetMod8 ) )   // If we have a second half, we didn't read enough bytes in the first half
			*( inOutByteArray + offset ) |= *( data + ( readOffset >> 3 ) + 1 ) >> ( 8 - ( readOffsetMod8 ) ); // Second half (overlaps byte boundary)

		if (numberOfBitsToRead>=8)
		{
			numberOfBitsToRead -= 8;
			readOffset += 8;
			offset++;
		}
		else
		{
			int neg = (int) numberOfBitsToRead - 8;

			if ( neg < 0 )   // Reading a partial byte for the last byte, shift right so the data is aligned on the right
			{

				if ( alignBitsToRight )
					* ( inOutByteArray + offset ) >>= -neg;

				readOffset += 8 + neg;
			}
			else
				readOffset += 8;

			offset++;

			numberOfBitsToRead=0;
		}		
	}

	return true;
}

// Assume the input source points to a compressed native type. Decompress and read it
bool BitStream::ReadCompressed( unsigned char* inOutByteArray,
							   const unsigned int size, const bool unsignedData )
{
	unsigned int currentByte = ( size >> 3 ) - 1;


	unsigned char byteMatch, halfByteMatch;

	if ( unsignedData )
	{
		byteMatch = 0;
		halfByteMatch = 0;
	}

	else
	{
		byteMatch = 0xFF;
		halfByteMatch = 0xF0;
	}

	// Upper bytes are specified with a single 1 if they match byteMatch
	// From high byte to low byte, if high byte is a byteMatch then write a 1 bit. Otherwise write a 0 bit and then write the remaining bytes
	while ( currentByte > 0 )
	{
		// If we read a 1 then the data is byteMatch.

		bool b;

		if ( Read( b ) == false )
			return false;

		if ( b )   // Check that bit
		{
			inOutByteArray[ currentByte ] = byteMatch;
			currentByte--;
		}
		else
		{
			// Read the rest of the bytes

			if ( ReadBits( inOutByteArray, ( currentByte + 1 ) << 3 ) == false )
				return false;

			return true;
		}
	}

	// All but the first bytes are byteMatch.  If the upper half of the last byte is a 0 (positive) or 16 (negative) then what we read will be a 1 and the remaining 4 bits.
	// Otherwise we read a 0 and the 8 bytes
	//RakAssert(readOffset+1 <=numberOfBitsUsed); // If this assert is hit the stream wasn't long enough to read from
	if ( readOffset + 1 > numberOfBitsUsed )
		return false;

	bool b=false;

	if ( Read( b ) == false )
		return false;

	if ( b )   // Check that bit
	{

		if ( ReadBits( inOutByteArray + currentByte, 4 ) == false )
			return false;

		inOutByteArray[ currentByte ] |= halfByteMatch; // We have to set the high 4 bits since these are set to 0 by ReadBits
	}
	else
	{
		if ( ReadBits( inOutByteArray + currentByte, 8 ) == false )
			return false;
	}

	return true;
}

// Reallocates (if necessary) in preparation of writing numberOfBitsToWrite
void BitStream::AddBitsAndReallocate( const BitSize_t numberOfBitsToWrite )
{
	BitSize_t newNumberOfBitsAllocated = numberOfBitsToWrite + numberOfBitsUsed;

	if ( numberOfBitsToWrite + numberOfBitsUsed > 0 && ( ( numberOfBitsAllocated - 1 ) >> 3 ) < ( ( newNumberOfBitsAllocated - 1 ) >> 3 ) )   // If we need to allocate 1 or more new bytes
	{
#ifdef _DEBUG
		// If this assert hits then we need to specify true for the third parameter in the constructor
		// It needs to reallocate to hold all the data and can't do it unless we allocated to begin with
		// Often hits if you call Write or Serialize on a read-only bitstream
		RakAssert( copyData == true );
#endif

		// Less memory efficient but saves on news and deletes
		/// Cap to 1 meg buffer to save on huge allocations
		newNumberOfBitsAllocated = ( numberOfBitsToWrite + numberOfBitsUsed ) * 2;
		if (newNumberOfBitsAllocated - ( numberOfBitsToWrite + numberOfBitsUsed ) > 1048576 )
			newNumberOfBitsAllocated = numberOfBitsToWrite + numberOfBitsUsed + 1048576;

		//		BitSize_t newByteOffset = BITS_TO_BYTES( numberOfBitsAllocated );
		// Use realloc and free so we are more efficient than delete and new for resizing
		BitSize_t amountToAllocate = BITS_TO_BYTES( newNumberOfBitsAllocated );
		if (data==(unsigned char*)stackData)
		{
			if (amountToAllocate > BITSTREAM_STACK_ALLOCATION_SIZE)
			{
				data = ( unsigned char* ) rakMalloc_Ex( (size_t) amountToAllocate, _FILE_AND_LINE_ );
				RakAssert(data);

				// need to copy the stack data over to our new memory area too
				memcpy ((void *)data, (void *)stackData, (size_t) BITS_TO_BYTES( numberOfBitsAllocated )); 
			}
		}
		else
		{
			data = ( unsigned char* ) rakRealloc_Ex( data, (size_t) amountToAllocate, _FILE_AND_LINE_ );
		}

#ifdef _DEBUG
		RakAssert( data ); // Make sure realloc succeeded
#endif
		//  memset(data+newByteOffset, 0,  ((newNumberOfBitsAllocated-1)>>3) - ((numberOfBitsAllocated-1)>>3)); // Set the new data block to 0
	}

	if ( newNumberOfBitsAllocated > numberOfBitsAllocated )
		numberOfBitsAllocated = newNumberOfBitsAllocated;
}
BitSize_t BitStream::GetNumberOfBitsAllocated(void) const
{
	return numberOfBitsAllocated;
}
void BitStream::PadWithZeroToByteLength( unsigned int bytes )
{
	if (GetNumberOfBytesUsed() < bytes)
	{
		AlignWriteToByteBoundary();
		unsigned int numToWrite = bytes - GetNumberOfBytesUsed();
		AddBitsAndReallocate( BYTES_TO_BITS(numToWrite) );
		memset(data+BITS_TO_BYTES(numberOfBitsUsed), 0, (size_t) numToWrite);
		numberOfBitsUsed+=BYTES_TO_BITS(numToWrite);
	}
}

/* 
// Julius Goryavsky's version of Harley's algorithm.
// 17 elementary ops plus an indexed load, if the machine
// has "and not."

int nlz10b(unsigned x) {

   static char table[64] =
     {32,20,19, u, u,18, u, 7,  10,17, u, u,14, u, 6, u,
       u, 9, u,16, u, u, 1,26,   u,13, u, u,24, 5, u, u,
       u,21, u, 8,11, u,15, u,   u, u, u, 2,27, 0,25, u,
      22, u,12, u, u, 3,28, u,  23, u, 4,29, u, u,30,31};

   x = x | (x >> 1);    // Propagate leftmost
   x = x | (x >> 2);    // 1-bit to the right.
   x = x | (x >> 4);
   x = x | (x >> 8);
   x = x & ~(x >> 16);
   x = x*0xFD7049FF;    // Activate this line or the following 3.
// x = (x << 9) - x;    // Multiply by 511.
// x = (x << 11) - x;   // Multiply by 2047.
// x = (x << 14) - x;   // Multiply by 16383.
   return table[x >> 26];
}
*/
int BitStream::NumberOfLeadingZeroes( int8_t x ) {return NumberOfLeadingZeroes((uint8_t)x);}
int BitStream::NumberOfLeadingZeroes( uint8_t x )
{
	uint8_t y;
	int n;

	n = 8;
	y = x >> 4;  if (y != 0) {n = n - 4;  x = y;}
	y = x >> 2;  if (y != 0) {n = n - 2;  x = y;}
	y = x >> 1;  if (y != 0) return n - 2;
	return (int)(n - x);
}
int BitStream::NumberOfLeadingZeroes( int16_t x ) {return NumberOfLeadingZeroes((uint16_t)x);}
int BitStream::NumberOfLeadingZeroes( uint16_t x )
{
	uint16_t y;
	int n;

	n = 16;
	y = x >> 8;  if (y != 0) {n = n - 8;  x = y;}
	y = x >> 4;  if (y != 0) {n = n - 4;  x = y;}
	y = x >> 2;  if (y != 0) {n = n - 2;  x = y;}
	y = x >> 1;  if (y != 0) return n - 2;
	return (int)(n - x);
}
int BitStream::NumberOfLeadingZeroes( int32_t x ) {return NumberOfLeadingZeroes((uint32_t)x);}
int BitStream::NumberOfLeadingZeroes( uint32_t x )
{
	uint32_t y;
	int n;

	n = 32;
	y = x >>16;  if (y != 0) {n = n -16;  x = y;}
	y = x >> 8;  if (y != 0) {n = n - 8;  x = y;}
	y = x >> 4;  if (y != 0) {n = n - 4;  x = y;}
	y = x >> 2;  if (y != 0) {n = n - 2;  x = y;}
	y = x >> 1;  if (y != 0) return n - 2;
	return (int)(n - x);
}
int BitStream::NumberOfLeadingZeroes( int64_t x ) {return NumberOfLeadingZeroes((uint64_t)x);}
int BitStream::NumberOfLeadingZeroes( uint64_t x )
{
	uint64_t y;
	int n;

	n = 64;
	y = x >>32;  if (y != 0) {n = n -32;  x = y;}
	y = x >>16;  if (y != 0) {n = n -16;  x = y;}
	y = x >> 8;  if (y != 0) {n = n - 8;  x = y;}
	y = x >> 4;  if (y != 0) {n = n - 4;  x = y;}
	y = x >> 2;  if (y != 0) {n = n - 2;  x = y;}
	y = x >> 1;  if (y != 0) return n - 2;
	return (int)(n - x);
}

// Should hit if reads didn't match writes
void BitStream::AssertStreamEmpty( void )
{
	RakAssert( readOffset == numberOfBitsUsed );
}

void BitStream::PrintBits( char *out ) const
{
	if (numberOfBitsUsed <= 0)
	{
#pragma warning(push)
#pragma warning(disable:4996)
		strcpy(out, "No bits\n");
#pragma warning(pop)
		return;
	}

	unsigned int strIndex = 0;
	for (BitSize_t counter = 0; counter < BITS_TO_BYTES(numberOfBitsUsed) && strIndex < 2000; counter++)
	{
		BitSize_t stop;

		if (counter == (numberOfBitsUsed - 1) >> 3)
			stop = 8 - (((numberOfBitsUsed - 1) & 7) + 1);
		else
			stop = 0;

		for (BitSize_t counter2 = 7; counter2 >= stop; counter2--)
		{
			if ((data[counter] >> counter2) & 1)
				out[strIndex++] = '1';
			else
				out[strIndex++] = '0';

			if (counter2 == 0)
				break;
		}

		out[strIndex++] = ' ';
	}

	out[strIndex++] = '\n';

	out[strIndex++] = 0;
}

void BitStream::PrintBits( char *out, size_t outLength ) const
{
	if ( numberOfBitsUsed <= 0 )
	{
		strcpy_s(out, outLength, "No bits\n" );
		return;
	}

	unsigned int strIndex=0;
	for ( BitSize_t counter = 0; counter < BITS_TO_BYTES( numberOfBitsUsed ) && strIndex < 2000 ; counter++ )
	{
		BitSize_t stop;

		if ( counter == ( numberOfBitsUsed - 1 ) >> 3 )
			stop = 8 - ( ( ( numberOfBitsUsed - 1 ) & 7 ) + 1 );
		else
			stop = 0;

		for ( BitSize_t counter2 = 7; counter2 >= stop; counter2-- )
		{
			if ( ( data[ counter ] >> counter2 ) & 1 )
				out[strIndex++]='1';
			else
				out[strIndex++]='0';

			if (counter2==0)
				break;
		}

		out[strIndex++]=' ';
	}

	out[strIndex++]='\n';

	out[strIndex++]=0;
}
void BitStream::PrintBits( void ) const
{
	char out[2048];
	PrintBits(out, 2048);
	RAKNET_DEBUG_PRINTF("%s", out);
}

void BitStream::PrintHex( char *out, size_t outLength ) const
{
	BitSize_t i;
	for ( i=0; i < GetNumberOfBytesUsed(); i++)
	{
		sprintf_s(out+i*3, outLength-i*3, "%02x ", data[i]);
	}
}

void BitStream::PrintHex( char *out ) const
{
	BitSize_t i;
	for (i = 0; i < GetNumberOfBytesUsed(); i++)
	{
#pragma warning(push)
#pragma warning(disable:4996)
		sprintf(out + i * 3, "%02x ", data[i]);
#pragma warning(pop)
	}
}

void BitStream::PrintHex( void ) const
{
	char out[2048];
	PrintHex(out, 2048);
	RAKNET_DEBUG_PRINTF("%s", out);
}

// Exposes the data for you to look at, like PrintBits does.
// Data will point to the stream.  Returns the length in bits of the stream.
BitSize_t BitStream::CopyData( unsigned char** _data ) const
{
#ifdef _DEBUG
	RakAssert( numberOfBitsUsed > 0 );
#endif

	*_data = (unsigned char*) rakMalloc_Ex( (size_t) BITS_TO_BYTES( numberOfBitsUsed ), _FILE_AND_LINE_ );
	memcpy( *_data, data, sizeof(unsigned char) * (size_t) ( BITS_TO_BYTES( numberOfBitsUsed ) ) );
	return numberOfBitsUsed;
}

// Ignore data we don't intend to read
void BitStream::IgnoreBits( const BitSize_t numberOfBits )
{
	readOffset += numberOfBits;
}

void BitStream::IgnoreBytes( const unsigned int numberOfBytes )
{
	IgnoreBits(BYTES_TO_BITS(numberOfBytes));
}

// Move the write pointer to a position on the array.  Dangerous if you don't know what you are doing!
// Doesn't work with non-aligned data!
void BitStream::SetWriteOffset( const BitSize_t offset )
{
	numberOfBitsUsed = offset;
}

/*
BitSize_t BitStream::GetWriteOffset( void ) const
{
return numberOfBitsUsed;
}

// Returns the length in bits of the stream
BitSize_t BitStream::GetNumberOfBitsUsed( void ) const
{
return GetWriteOffset();
}

// Returns the length in bytes of the stream
BitSize_t BitStream::GetNumberOfBytesUsed( void ) const
{
return BITS_TO_BYTES( numberOfBitsUsed );
}

// Returns the number of bits into the stream that we have read
BitSize_t BitStream::GetReadOffset( void ) const
{
return readOffset;
}


// Sets the read bit index
void BitStream::SetReadOffset( const BitSize_t newReadOffset )
{
readOffset=newReadOffset;
}

// Returns the number of bits left in the stream that haven't been read
BitSize_t BitStream::GetNumberOfUnreadBits( void ) const
{
return numberOfBitsUsed - readOffset;
}
// Exposes the internal data
unsigned char* BitStream::GetData( void ) const
{
return data;
}

*/
// If we used the constructor version with copy data off, this makes sure it is set to on and the data pointed to is copied.
void BitStream::AssertCopyData( void )
{
	if ( copyData == false )
	{
		copyData = true;

		if ( numberOfBitsAllocated > 0 )
		{
			unsigned char * newdata = ( unsigned char* ) rakMalloc_Ex( (size_t) BITS_TO_BYTES( numberOfBitsAllocated ), _FILE_AND_LINE_ );
#ifdef _DEBUG

			RakAssert( data );
#endif

			memcpy( newdata, data, (size_t) BITS_TO_BYTES( numberOfBitsAllocated ) );
			data = newdata;
		}

		else
			data = 0;
	}
}
bool BitStream::IsNetworkOrderInternal(void)
{





	static unsigned long htonlValue = htonl(12345);
	return htonlValue == 12345;

}
void BitStream::ReverseBytes(unsigned char *inByteArray, unsigned char *inOutByteArray, const unsigned int length)
{
	for (BitSize_t i=0; i < length; i++)
		inOutByteArray[i]=inByteArray[length-i-1];
}
void BitStream::ReverseBytesInPlace(unsigned char *inOutData,const unsigned int length)
{
	unsigned char temp;
	BitSize_t i;
	for (i=0; i < (length>>1); i++)
	{
		temp = inOutData[i];
		inOutData[i]=inOutData[length-i-1];
		inOutData[length-i-1]=temp;
	}
}

bool BitStream::Read(char *varString)
{
	return RakString::Deserialize(varString,this);
}
bool BitStream::Read(unsigned char *varString)
{
	return RakString::Deserialize((char*) varString,this);
}
void BitStream::WriteAlignedVar8(const char *inByteArray)
{
	RakAssert((numberOfBitsUsed&7)==0);
	AddBitsAndReallocate(1*8);
	data[( numberOfBitsUsed >> 3 ) + 0] = inByteArray[0];
	numberOfBitsUsed+=1*8;
}
bool BitStream::ReadAlignedVar8(char *inOutByteArray)
{
	RakAssert((readOffset&7)==0);
	if ( readOffset + 1*8 > numberOfBitsUsed )
		return false;

	inOutByteArray[0] = data[( readOffset >> 3 ) + 0];
	readOffset+=1*8;
	return true;
}
void BitStream::WriteAlignedVar16(const char *inByteArray)
{
	RakAssert((numberOfBitsUsed&7)==0);
	AddBitsAndReallocate(2*8);
#ifndef __BITSTREAM_NATIVE_END
	if (DoEndianSwap())
	{
		data[( numberOfBitsUsed >> 3 ) + 0] = inByteArray[1];
		data[( numberOfBitsUsed >> 3 ) + 1] = inByteArray[0];
	}
	else
#endif
	{
		data[( numberOfBitsUsed >> 3 ) + 0] = inByteArray[0];
		data[( numberOfBitsUsed >> 3 ) + 1] = inByteArray[1];
	}

	numberOfBitsUsed+=2*8;
}
bool BitStream::ReadAlignedVar16(char *inOutByteArray)
{
	RakAssert((readOffset&7)==0);
	if ( readOffset + 2*8 > numberOfBitsUsed )
		return false;
#ifndef __BITSTREAM_NATIVE_END
	if (DoEndianSwap())
	{
		inOutByteArray[0] = data[( readOffset >> 3 ) + 1];
		inOutByteArray[1] = data[( readOffset >> 3 ) + 0];
	}
	else
#endif
	{
		inOutByteArray[0] = data[( readOffset >> 3 ) + 0];
		inOutByteArray[1] = data[( readOffset >> 3 ) + 1];
	}

	readOffset+=2*8;
	return true;
}
void BitStream::WriteAlignedVar32(const char *inByteArray)
{
	RakAssert((numberOfBitsUsed&7)==0);
	AddBitsAndReallocate(4*8);
#ifndef __BITSTREAM_NATIVE_END
	if (DoEndianSwap())
	{
		data[( numberOfBitsUsed >> 3 ) + 0] = inByteArray[3];
		data[( numberOfBitsUsed >> 3 ) + 1] = inByteArray[2];
		data[( numberOfBitsUsed >> 3 ) + 2] = inByteArray[1];
		data[( numberOfBitsUsed >> 3 ) + 3] = inByteArray[0];
	}
	else
#endif
	{
		data[( numberOfBitsUsed >> 3 ) + 0] = inByteArray[0];
		data[( numberOfBitsUsed >> 3 ) + 1] = inByteArray[1];
		data[( numberOfBitsUsed >> 3 ) + 2] = inByteArray[2];
		data[( numberOfBitsUsed >> 3 ) + 3] = inByteArray[3];
	}

	numberOfBitsUsed+=4*8;
}
bool BitStream::ReadAlignedVar32(char *inOutByteArray)
{
	RakAssert((readOffset&7)==0);
	if ( readOffset + 4*8 > numberOfBitsUsed )
		return false;
#ifndef __BITSTREAM_NATIVE_END
	if (DoEndianSwap())
	{
		inOutByteArray[0] = data[( readOffset >> 3 ) + 3];
		inOutByteArray[1] = data[( readOffset >> 3 ) + 2];
		inOutByteArray[2] = data[( readOffset >> 3 ) + 1];
		inOutByteArray[3] = data[( readOffset >> 3 ) + 0];
	}
	else
#endif
	{
		inOutByteArray[0] = data[( readOffset >> 3 ) + 0];
		inOutByteArray[1] = data[( readOffset >> 3 ) + 1];
		inOutByteArray[2] = data[( readOffset >> 3 ) + 2];
		inOutByteArray[3] = data[( readOffset >> 3 ) + 3];
	}

	readOffset+=4*8;
	return true;
}
bool BitStream::ReadFloat16( float &outFloat, float floatMin, float floatMax )
{
	unsigned short percentile;
	if (Read(percentile))
	{
		RakAssert(floatMax>floatMin);
		outFloat = floatMin + ((float) percentile / 65535.0f) * (floatMax-floatMin);
		if (outFloat<floatMin)
			outFloat=floatMin;
		else if (outFloat>floatMax)
			outFloat=floatMax;
		return true;
	}
	return false;
}
bool BitStream::SerializeFloat16(bool writeToBitstream, float &inOutFloat, float floatMin, float floatMax)
{
	if (writeToBitstream)
		WriteFloat16(inOutFloat, floatMin, floatMax);
	else
		return ReadFloat16(inOutFloat, floatMin, floatMax);
	return true;
}
void BitStream::WriteFloat16( float inOutFloat, float floatMin, float floatMax )
{
	RakAssert(floatMax>floatMin);
	if (inOutFloat>floatMax+.001)
	{
		RakAssert(inOutFloat<=floatMax+.001);
	}
	if (inOutFloat<floatMin-.001)
	{
		RakAssert(inOutFloat>=floatMin-.001);
	}
	float percentile=65535.0f * (inOutFloat-floatMin)/(floatMax-floatMin);
	if (percentile<0.0)
		percentile=0.0;
	if (percentile>65535.0f)
		percentile=65535.0f;
	Write((unsigned short)percentile);
}
