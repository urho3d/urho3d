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

#include "slikenet/wstring.h"
#include "slikenet/BitStream.h"
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

using namespace SLNet;

// From http://www.joelonsoftware.com/articles/Unicode.html
// Only code points 128 and above are stored using 2, 3, in fact, up to 6 bytes.
#define MAX_BYTES_PER_UNICODE_CHAR sizeof(wchar_t)

RakWString::RakWString()
{
	c_str=0;
	c_strCharLength=0;
}
RakWString::RakWString( const RakString &right )
{
	c_str=0;
	c_strCharLength=0;
	*this=right;
}
RakWString::RakWString( const char *input )
{
	c_str=0;
	c_strCharLength=0;
	*this = input;
}
RakWString::RakWString( const wchar_t *input )
{
	c_str=0;
	c_strCharLength=0;
	*this = input;
}
RakWString::RakWString( const RakWString & right)
{
	c_str=0;
	c_strCharLength=0;
	*this = right;
}
RakWString::~RakWString()
{
	rakFree_Ex(c_str,_FILE_AND_LINE_);
}
RakWString& RakWString::operator = ( const RakWString& right )
{
	Clear();
	if (right.IsEmpty())
		return *this;
	c_str = (wchar_t *) rakMalloc_Ex( (right.GetLength() + 1) * MAX_BYTES_PER_UNICODE_CHAR, _FILE_AND_LINE_);
	if (!c_str)
	{
		c_strCharLength=0;
		notifyOutOfMemory(_FILE_AND_LINE_);
		return *this;
	}
	c_strCharLength = right.GetLength();
	memcpy(c_str,right.C_String(),(right.GetLength() + 1) * MAX_BYTES_PER_UNICODE_CHAR);

	return *this;
}
RakWString& RakWString::operator = ( const RakString& right )
{
	return *this = right.C_String();
}
RakWString& RakWString::operator = ( const wchar_t * const str )
{
	Clear();
	if (str==0)
		return *this;
	c_strCharLength = wcslen(str);
	if (c_strCharLength==0)
		return *this;
	c_str = (wchar_t *) rakMalloc_Ex( (c_strCharLength + 1) * MAX_BYTES_PER_UNICODE_CHAR, _FILE_AND_LINE_);
	if (!c_str)
	{
		c_strCharLength=0;
		notifyOutOfMemory(_FILE_AND_LINE_);
		return *this;
	}
	wcscpy_s(c_str,c_strCharLength+1,str);

	return *this;
}
RakWString& RakWString::operator = ( wchar_t *str )
{
	*this = ( const wchar_t * const) str;
	return *this;
}
RakWString& RakWString::operator = ( const char * const str )
{
	Clear();

// Not supported on android
#if !defined(__ANDROID__)
	if (str==0)
		return *this;
	if (str[0]==0)
		return *this;

	mbstowcs_s(&c_strCharLength, NULL, 0, str, 0);
	c_str = (wchar_t *) rakMalloc_Ex( (c_strCharLength + 1) * MAX_BYTES_PER_UNICODE_CHAR, _FILE_AND_LINE_);
	if (!c_str)
	{
		c_strCharLength=0;
		notifyOutOfMemory(_FILE_AND_LINE_);
		return *this;
	}

	mbstowcs_s(&c_strCharLength, c_str, c_strCharLength + 1, str, c_strCharLength);
	if (c_strCharLength == (size_t) (-1))
	{
		RAKNET_DEBUG_PRINTF("Couldn't convert string--invalid multibyte character.\n");
		Clear();
		return *this;
	}
#else
	// mbstowcs not supported on android
	RakAssert("mbstowcs not supported on Android" && 0);
#endif // defined(__ANDROID__)

	return *this;
}
RakWString& RakWString::operator = ( char *str )
{
	*this = ( const char * const) str;
	return *this;
}
RakWString& RakWString::operator +=( const RakWString& right)
{
	if (right.IsEmpty())
		return *this;
	size_t newCharLength = c_strCharLength + right.GetLength();
	wchar_t *newCStr;
	bool isEmpty = IsEmpty();
	if (isEmpty)
		newCStr = (wchar_t *) rakMalloc_Ex( (newCharLength + 1) * MAX_BYTES_PER_UNICODE_CHAR, _FILE_AND_LINE_);
	else
		newCStr = (wchar_t *) rakRealloc_Ex( c_str, (newCharLength + 1) * MAX_BYTES_PER_UNICODE_CHAR, _FILE_AND_LINE_);
	if (!newCStr)
	{
		notifyOutOfMemory(_FILE_AND_LINE_);
		return *this;
	}
	c_str = newCStr;
	c_strCharLength = newCharLength;
	if (isEmpty)
	{
		memcpy(newCStr,right.C_String(),(right.GetLength() + 1) * MAX_BYTES_PER_UNICODE_CHAR);
	}
	else
	{
		wcscat_s(c_str, newCharLength + 1, right.C_String());
	}

	return *this;
}
RakWString& RakWString::operator += ( const wchar_t * const right )
{
	if (right==0)
		return *this;
	size_t rightLength = wcslen(right);
	size_t newCharLength = c_strCharLength + rightLength;
	wchar_t *newCStr;
	bool isEmpty = IsEmpty();
	if (isEmpty)
		newCStr = (wchar_t *) rakMalloc_Ex( (newCharLength + 1) * MAX_BYTES_PER_UNICODE_CHAR, _FILE_AND_LINE_);
	else
		newCStr = (wchar_t *) rakRealloc_Ex( c_str, (newCharLength + 1) * MAX_BYTES_PER_UNICODE_CHAR, _FILE_AND_LINE_);
	if (!newCStr)
	{
		notifyOutOfMemory(_FILE_AND_LINE_);
		return *this;
	}
	c_str = newCStr;
	c_strCharLength = newCharLength;
	if (isEmpty)
	{
		memcpy(newCStr,right,(rightLength + 1) * MAX_BYTES_PER_UNICODE_CHAR);
	}
	else
	{
		wcscat_s(c_str, newCharLength + 1, right);
	}

	return *this;
}
RakWString& RakWString::operator += ( wchar_t *right )
{
	return *this += (const wchar_t * const) right;
}
bool RakWString::operator==(const RakWString &right) const
{
	if (GetLength()!=right.GetLength())
		return false;
	return wcscmp(C_String(),right.C_String())==0;
}
bool RakWString::operator < ( const RakWString& right ) const
{
	return wcscmp(C_String(),right.C_String())<0;
}
bool RakWString::operator <= ( const RakWString& right ) const
{
	return wcscmp(C_String(),right.C_String())<=0;
}
bool RakWString::operator > ( const RakWString& right ) const
{
	return wcscmp(C_String(),right.C_String())>0;
}
bool RakWString::operator >= ( const RakWString& right ) const
{
	return wcscmp(C_String(),right.C_String())>=0;
}
bool RakWString::operator!=(const RakWString &right) const
{
	if (GetLength()!=right.GetLength())
		return true;
	return wcscmp(C_String(),right.C_String())!=0;
}
void RakWString::Set( wchar_t *str )
{
	*this = str;
}
bool RakWString::IsEmpty(void) const
{
	return GetLength()==0;
}
size_t RakWString::GetLength(void) const
{
	return c_strCharLength;
}
unsigned long RakWString::ToInteger(const RakWString &rs)
{
	unsigned long hash = 0;
	int c;

	const char *str = (const char *)rs.C_String();
	size_t i;
	for (i=0; i < rs.GetLength()*MAX_BYTES_PER_UNICODE_CHAR*sizeof(wchar_t); i++)
	{
		c = *str++;
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}
int RakWString::StrCmp(const RakWString &right) const
{
	return wcscmp(C_String(), right.C_String());
}
int RakWString::StrICmp(const RakWString &right) const
{
#ifdef _WIN32
	return _wcsicmp(C_String(), right.C_String());
#else
	// Not supported
	return wcscmp(C_String(), right.C_String());
#endif
}
void RakWString::Clear(void)
{
	rakFree_Ex(c_str,_FILE_AND_LINE_);
	c_str=0;
	c_strCharLength=0;
}
void RakWString::Printf(void)
{
	printf("%ls", C_String());
}
void RakWString::FPrintf(FILE *fp)
{
	fprintf(fp,"%ls", C_String());
}
void RakWString::Serialize(BitStream *bs) const
{
	Serialize(C_String(), bs);
}
void RakWString::Serialize(const wchar_t * const str, BitStream *bs)
{
#if 0
	char *multiByteBuffer;
	size_t allocated = wcslen(str)*MAX_BYTES_PER_UNICODE_CHAR;
	multiByteBuffer = (char*) rakMalloc_Ex(allocated, _FILE_AND_LINE_);
	size_t used = wcstombs(multiByteBuffer, str, allocated);
	bs->WriteCasted<unsigned short>(used);
	bs->WriteAlignedBytes((const unsigned char*) multiByteBuffer,(const unsigned int) used);
	rakFree_Ex(multiByteBuffer, _FILE_AND_LINE_);
#else
	size_t mbByteLength = wcslen(str);
	bs->WriteCasted<unsigned short>(mbByteLength);
	for (unsigned int i=0; i < mbByteLength; i++)
	{
		uint16_t t;
		t = (uint16_t) str[i];
		// Force endian swapping, and write to 16 bits
		bs->Write(t);
	}
#endif
}
bool RakWString::Deserialize(BitStream *bs)
{
	Clear();

	size_t mbByteLength;
	bs->ReadCasted<unsigned short>(mbByteLength);
	if (mbByteLength>0)
	{
#if 0
		char *multiByteBuffer;
		multiByteBuffer = (char*) rakMalloc_Ex(mbByteLength+1, _FILE_AND_LINE_);
		bool result = bs->ReadAlignedBytes((unsigned char*) multiByteBuffer,(const unsigned int) mbByteLength);
		if (result==false)
		{
			rakFree_Ex(multiByteBuffer, _FILE_AND_LINE_);
			return false;
		}
		multiByteBuffer[mbByteLength]=0;
		c_str = (wchar_t *) rakMalloc_Ex( (mbByteLength + 1) * MAX_BYTES_PER_UNICODE_CHAR, _FILE_AND_LINE_);
		mbstowcs_s(&c_strCharLength, c_str, mbByteLength + 1, multiByteBuffer, mbByteLength);
		rakFree_Ex(multiByteBuffer, _FILE_AND_LINE_);
		c_str[c_strCharLength]=0;
#else
		c_str = (wchar_t*) rakMalloc_Ex((mbByteLength+1) * MAX_BYTES_PER_UNICODE_CHAR, _FILE_AND_LINE_);
		c_strCharLength = mbByteLength;
		for (unsigned int i=0; i < mbByteLength; i++)
		{
			uint16_t t;
			// Force endian swapping, and read 16 bits
			bs->Read(t);
			c_str[i]=t;
		}
		c_str[mbByteLength]=0;
#endif
		return true;
	}
	else
	{
		return true;
	}
}
bool RakWString::Deserialize(wchar_t *str, BitStream *bs)
{
	size_t mbByteLength;
	bs->ReadCasted<unsigned short>(mbByteLength);
	if (mbByteLength > 0)
	{
#if 0
		char *multiByteBuffer;
		multiByteBuffer = (char*)rakMalloc_Ex(mbByteLength + 1, _FILE_AND_LINE_);
		bool result = bs->ReadAlignedBytes((unsigned char*)multiByteBuffer, (const unsigned int)mbByteLength);
		if (result == false)
		{
			rakFree_Ex(multiByteBuffer, _FILE_AND_LINE_);
			return false;
		}
		multiByteBuffer[mbByteLength] = 0;
		size_t c_strCharLength;
		mbstowcs(&c_strCharLength, str, multiByteBuffer, mbByteLength);
		rakFree_Ex(multiByteBuffer, _FILE_AND_LINE_);
		str[c_strCharLength] = 0;
#else
		for (unsigned int i = 0; i < mbByteLength; i++)
		{
			uint16_t t;
			// Force endian swapping, and read 16 bits
			bs->Read(t);
			str[i] = t;
		}
		str[mbByteLength] = 0;
#endif
		return true;
	}
	else
	{
#pragma warning(push)
#pragma warning(disable:4996)
		wcscpy(str, L"");
#pragma warning(pop)
	}
	return true;
}
bool RakWString::Deserialize(wchar_t *str, size_t strLength, BitStream *bs)
{
	size_t mbByteLength;
	bs->ReadCasted<unsigned short>(mbByteLength);
	if (mbByteLength>0)
	{
#if 0
		char *multiByteBuffer;
		multiByteBuffer = (char*) rakMalloc_Ex(mbByteLength+1, _FILE_AND_LINE_);
		bool result = bs->ReadAlignedBytes((unsigned char*) multiByteBuffer,(const unsigned int) mbByteLength);
		if (result==false)
		{
			rakFree_Ex(multiByteBuffer, _FILE_AND_LINE_);
			return false;
		}
		multiByteBuffer[mbByteLength]=0;
		size_t c_strCharLength;
		mbstowcs_s(&c_strCharLength, str, strLength, multiByteBuffer, mbByteLength);
		rakFree_Ex(multiByteBuffer, _FILE_AND_LINE_);
		str[c_strCharLength]=0;
#else
		for (unsigned int i=0; i < mbByteLength; i++)
		{
			uint16_t t;
			// Force endian swapping, and read 16 bits
			bs->Read(t);
			str[i]=t;
		}
		str[mbByteLength]=0;
#endif
		return true;
	}
	else
	{
		wcscpy_s(str,strLength,L"");
	}
	return true;
}

/*
SLNet::BitStream bsTest;
SLNet::RakWString testString("cat"), testString2;
testString = "Hllo";
testString = L"Hello";
testString += L" world";
testString2 += testString2;
SLNet::RakWString ts3(L" from here");
testString2+=ts3;
SLNet::RakWString ts4(L" 222");
testString2=ts4;
SLNet::RakString rs("rakstring");
testString2+=rs;
testString2=rs;
bsTest.Write(L"one");
bsTest.Write(testString2);
bsTest.SetReadOffset(0);
SLNet::RakWString ts5, ts6;
wchar_t buff[99];
wchar_t *wptr = (wchar_t*)buff;
bsTest.Read(wptr);
bsTest.Read(ts5);
*/
