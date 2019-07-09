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

#include "slikenet/string.h"
#include "slikenet/assert.h"
#include "slikenet/memoryoverride.h"
#include "slikenet/BitStream.h"
#include <stdarg.h>
#include <string.h>
#include "slikenet/LinuxStrings.h"
#include "slikenet/StringCompressor.h"
#include "slikenet/SimpleMutex.h"
#include <stdlib.h>
#include "slikenet/Itoa.h"
#include <limits>
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

using namespace SLNet;

//DataStructures::MemoryPool<RakString::SharedString> RakString::pool;
RakString::SharedString RakString::emptyString={0,0,0,(char*) "",(char*) ""};
//RakString::SharedString *RakString::sharedStringFreeList=0;
//unsigned int RakString::sharedStringFreeListAllocationCount=0;
DataStructures::List<RakString::SharedString*> RakString::freeList;

class RakStringCleanup
{
public:
	~RakStringCleanup()
	{
		SLNet::RakString::FreeMemoryNoMutex();
	}
};

static RakStringCleanup cleanup;

SimpleMutex& GetPoolMutex(void)
{
	static SimpleMutex poolMutex;
	return poolMutex;
}

int SLNet::RakString::RakStringComp( RakString const &key, RakString const &data )
{
	return key.StrCmp(data);
}

RakString::RakString()
{
	sharedString=&emptyString;
}
RakString::RakString( RakString::SharedString *_sharedString )
{
	sharedString=_sharedString;
}
RakString::RakString(char input)
{
	char str[2];
	str[0]=input;
	str[1]=0;
	Assign(str);
}
RakString::RakString(unsigned char input)
{
	char str[2];
	str[0]=(char) input;
	str[1]=0;
	Assign(str);
}
RakString::RakString(const unsigned char *format, ...){
	va_list ap;
	va_start(ap, format);
	Assign((const char*) format,ap);
	va_end(ap);
}
RakString::RakString(const char *format, ...){
	va_list ap;
	va_start(ap, format);
	Assign(format,ap);
	va_end(ap);
}
RakString::RakString( const RakString & rhs)
{
	if (rhs.sharedString==&emptyString)
	{
		sharedString=&emptyString;
		return;
	}

	rhs.sharedString->refCountMutex->Lock();
	if (rhs.sharedString->refCount==0)
	{
		sharedString=&emptyString;
	}
	else
	{
		rhs.sharedString->refCount++;
		sharedString=rhs.sharedString;
	}
	rhs.sharedString->refCountMutex->Unlock();
}
RakString::~RakString()
{
	Free();
}
RakString& RakString::operator = ( const RakString& rhs )
{
	Free();
	if (rhs.sharedString==&emptyString)
		return *this;

	rhs.sharedString->refCountMutex->Lock();
	if (rhs.sharedString->refCount==0)
	{
		sharedString=&emptyString;
	}
	else
	{
		sharedString=rhs.sharedString;
		sharedString->refCount++;
	}
	rhs.sharedString->refCountMutex->Unlock();
	return *this;
}
RakString& RakString::operator = ( const char *str )
{
	Free();
	Assign(str);
	return *this;
}
RakString& RakString::operator = ( char *str )
{
	return operator = ((const char*)str);
}
RakString& RakString::operator = ( const unsigned char *str )
{
	return operator = ((const char*)str);
}
RakString& RakString::operator = ( char unsigned *str )
{
	return operator = ((const char*)str);
}
RakString& RakString::operator = ( const char c )
{
	char buff[2];
	buff[0]=c;
	buff[1]=0;
	return operator = ((const char*)buff);
}
void RakString::Realloc(SharedString *inSharedString, size_t bytes)
{
	if (bytes<= inSharedString->bytesUsed)
		return;

	RakAssert(bytes>0);
	size_t oldBytes = inSharedString->bytesUsed;
	size_t newBytes;
	const size_t smallStringSize = 128-sizeof(unsigned int)-sizeof(size_t)-sizeof(char*)*2;
	newBytes = GetSizeToAllocate(bytes);
	if (oldBytes <=(size_t) smallStringSize && newBytes > (size_t) smallStringSize)
	{
		inSharedString->bigString=(char*) rakMalloc_Ex(newBytes, _FILE_AND_LINE_);
		strcpy_s(inSharedString->bigString, newBytes, inSharedString->smallString);
		inSharedString->c_str= inSharedString->bigString;
	}
	else if (oldBytes > smallStringSize)
	{
		inSharedString->bigString=(char*) rakRealloc_Ex(inSharedString->bigString,newBytes, _FILE_AND_LINE_);
		inSharedString->c_str= inSharedString->bigString;
	}
	inSharedString->bytesUsed=newBytes;
}
RakString& RakString::operator +=( const RakString& rhs)
{
	if (rhs.IsEmpty())
		return *this;

	if (IsEmpty())
	{
		return operator=(rhs);
	}
	else
	{
		Clone();
		size_t strLen=rhs.GetLength()+GetLength()+1;
		Realloc(sharedString, strLen+GetLength());
		strcat_s(sharedString->c_str,sharedString->bytesUsed,rhs.C_String());
	}
	return *this;
}
RakString& RakString::operator +=( const char *str )
{
	if (str==0 || str[0]==0)
		return *this;

	if (IsEmpty())
	{
		Assign(str);
	}
	else
	{
		Clone();
		size_t strLen=strlen(str)+GetLength()+1;
		Realloc(sharedString, strLen);
		strcat_s(sharedString->c_str,sharedString->bytesUsed,str);
	}
	return *this;
}
RakString& RakString::operator +=( char *str )
{
	return operator += ((const char*)str);
}
RakString& RakString::operator +=( const unsigned char *str )
{
	return operator += ((const char*)str);
}
RakString& RakString::operator +=( unsigned char *str )
{
	return operator += ((const char*)str);
}
RakString& RakString::operator +=( const char c )
{
	char buff[2];
	buff[0]=c;
	buff[1]=0;
	return operator += ((const char*)buff);
}
unsigned char RakString::operator[] ( const unsigned int position ) const
{
	RakAssert(position<GetLength());
	return sharedString->c_str[position];
}
bool RakString::operator==(const RakString &rhs) const
{
	return strcmp(sharedString->c_str,rhs.sharedString->c_str)==0;
}
bool RakString::operator==(const char *str) const
{
	return strcmp(sharedString->c_str,str)==0;
}
bool RakString::operator==(char *str) const
{
	return strcmp(sharedString->c_str,str)==0;
}
bool RakString::operator < ( const RakString& right ) const
{
	return strcmp(sharedString->c_str,right.C_String()) < 0;
}
bool RakString::operator <= ( const RakString& right ) const
{
	return strcmp(sharedString->c_str,right.C_String()) <= 0;
}
bool RakString::operator > ( const RakString& right ) const
{
	return strcmp(sharedString->c_str,right.C_String()) > 0;
}
bool RakString::operator >= ( const RakString& right ) const
{
	return strcmp(sharedString->c_str,right.C_String()) >= 0;
}
bool RakString::operator!=(const RakString &rhs) const
{
	return strcmp(sharedString->c_str,rhs.sharedString->c_str)!=0;
}
bool RakString::operator!=(const char *str) const
{
	return strcmp(sharedString->c_str,str)!=0;
}
bool RakString::operator!=(char *str) const
{
	return strcmp(sharedString->c_str,str)!=0;
}
const SLNet::RakString operator+(const SLNet::RakString &lhs, const SLNet::RakString &rhs)
{
	if (lhs.IsEmpty() && rhs.IsEmpty())
	{
		return RakString(&RakString::emptyString);
	}
	if (lhs.IsEmpty())
	{
		rhs.sharedString->refCountMutex->Lock();
		if (rhs.sharedString->refCount==0)
		{
			rhs.sharedString->refCountMutex->Unlock();
			lhs.sharedString->refCountMutex->Lock();
			lhs.sharedString->refCount++;
			lhs.sharedString->refCountMutex->Unlock();
			return RakString(lhs.sharedString);
		}
		else
		{
			rhs.sharedString->refCount++;
			rhs.sharedString->refCountMutex->Unlock();
			return RakString(rhs.sharedString);
		}
		// rhs.sharedString->refCountMutex->Unlock();
	}
	if (rhs.IsEmpty())
	{
		lhs.sharedString->refCountMutex->Lock();
		lhs.sharedString->refCount++;
		lhs.sharedString->refCountMutex->Unlock();
		return RakString(lhs.sharedString);
	}

	size_t len1 = lhs.GetLength();
	size_t len2 = rhs.GetLength();
	size_t allocatedBytes = len1 + len2 + 1;
	allocatedBytes = RakString::GetSizeToAllocate(allocatedBytes);
	RakString::SharedString *sharedString;

	RakString::LockMutex();
	// sharedString = RakString::pool.Allocate( _FILE_AND_LINE_ );
	if (RakString::freeList.Size()==0)
	{
		//RakString::sharedStringFreeList=(RakString::SharedString*) rakRealloc_Ex(RakString::sharedStringFreeList,(RakString::sharedStringFreeListAllocationCount+1024)*sizeof(RakString::SharedString), _FILE_AND_LINE_);
		unsigned i;
		for (i=0; i < 128; i++)
		{
		//	RakString::freeList.Insert(RakString::sharedStringFreeList+i+RakString::sharedStringFreeListAllocationCount);
			RakString::SharedString *ss;
			ss = (RakString::SharedString*) rakMalloc_Ex(sizeof(RakString::SharedString), _FILE_AND_LINE_);
			ss->refCountMutex= SLNet::OP_NEW<SimpleMutex>(_FILE_AND_LINE_);
			RakString::freeList.Insert(ss, _FILE_AND_LINE_);

		}
		//RakString::sharedStringFreeListAllocationCount+=1024;
	}
	sharedString = RakString::freeList[RakString::freeList.Size()-1];
	RakString::freeList.RemoveAtIndex(RakString::freeList.Size()-1);
	RakString::UnlockMutex();

	const int smallStringSize = 128-sizeof(unsigned int)-sizeof(size_t)-sizeof(char*)*2;
	sharedString->bytesUsed=allocatedBytes;
	sharedString->refCount=1;
	if (allocatedBytes <= (size_t) smallStringSize)
	{
		sharedString->c_str=sharedString->smallString;
	}
	else
	{
		sharedString->bigString=(char*)rakMalloc_Ex(sharedString->bytesUsed, _FILE_AND_LINE_);
		sharedString->c_str=sharedString->bigString;
	}

	strcpy_s(sharedString->c_str, sharedString->bytesUsed, lhs);
	strcat_s(sharedString->c_str, sharedString->bytesUsed, rhs);

	return RakString(sharedString);
}
const char * RakString::ToLower(void)
{
	Clone();

	size_t strLen = strlen(sharedString->c_str);
	unsigned i;
	for (i=0; i < strLen; i++)
		sharedString->c_str[i]=ToLower(sharedString->c_str[i]);
	return sharedString->c_str;
}
const char * RakString::ToUpper(void)
{
	Clone();

	size_t strLen = strlen(sharedString->c_str);
	unsigned i;
	for (i=0; i < strLen; i++)
		sharedString->c_str[i]=ToUpper(sharedString->c_str[i]);
	return sharedString->c_str;
}
void RakString::Set(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	Clear();
	Assign(format,ap);
	va_end(ap);
}
bool RakString::IsEmpty(void) const
{
	return sharedString==&emptyString;
}
size_t RakString::GetLength(void) const
{
	return strlen(sharedString->c_str);
}
// http://porg.es/blog/counting-characters-in-utf-8-strings-is-faster
int porges_strlen2(char *s)
{
	int i = 0;
	int iBefore = 0;
	int count = 0;

	while (s[i] > 0)
ascii:  i++;

	count += i-iBefore;
	while (s[i])
	{
		if (s[i] > 0)
		{
			iBefore = i;
			goto ascii;
		}
		else
			switch (0xF0 & s[i])
		{
			case 0xE0: i += 3; break;
			case 0xF0: i += 4; break;
			default:   i += 2; break;
		}
		++count;
	}
	return count;
}
size_t RakString::GetLengthUTF8(void) const
{
	return porges_strlen2(sharedString->c_str);
}
void RakString::Replace(unsigned index, unsigned count, unsigned char c)
{
	RakAssert(index+count < GetLength());
	Clone();
	unsigned countIndex=0;
	while (countIndex<count)
	{
		sharedString->c_str[index]=c;
		index++;
		countIndex++;
	}

}
void RakString::SetChar( unsigned index, unsigned char c )
{
	RakAssert(index < GetLength());
	Clone();
	sharedString->c_str[index]=c;
}
void RakString::SetChar( unsigned index, SLNet::RakString s )
{
	RakAssert(index < GetLength());
	Clone();
	SLNet::RakString firstHalf = SubStr(0, index);
	SLNet::RakString secondHalf = SubStr(index+1, (unsigned int)-1);
	*this = firstHalf;
	*this += s;
	*this += secondHalf;
}

#ifdef _WIN32
WCHAR * RakString::ToWideChar(void)
{
	//
	// Special case of NULL or empty input string
	//
	if ( (sharedString->c_str == NULL) || (*sharedString->c_str == '\0') )
	{
		// Return empty string
		WCHAR* buf = SLNet::OP_NEW_ARRAY<WCHAR>(1, __FILE__, __LINE__);
		buf[0] = L'\0';
		return buf;
	}

	//
	// Get size of destination UTF-16 buffer, in WCHAR's
	//
	int cchUTF16 = ::MultiByteToWideChar(
		CP_UTF8,                // convert from UTF-8
		0,						// Flags
		sharedString->c_str,    // source UTF-8 string
		-1,                     // -1 means string is zero-terminated
		NULL,                   // unused - no conversion done in this step
		0                       // request size of destination buffer, in WCHAR's
		);

	if ( cchUTF16 == 0 )
	{
		RakAssert("RakString::ToWideChar exception from cchUTF16==0" && 0);
		return 0;
	}

	//
	// Allocate destination buffer to store UTF-16 string
	//
	WCHAR * pszUTF16 = SLNet::OP_NEW_ARRAY<WCHAR>(cchUTF16,__FILE__,__LINE__);

	//
	// Do the conversion from UTF-8 to UTF-16
	//
	int result = ::MultiByteToWideChar(
		CP_UTF8,                // convert from UTF-8
		0,						// Buffer
		sharedString->c_str,    // source UTF-8 string
		-1,                     // -1 means string is zero-terminated
		pszUTF16,               // destination buffer
		cchUTF16                // size of destination buffer, in WCHAR's
		);

	if ( result == 0 )
	{
		RakAssert("RakString::ToWideChar exception from MultiByteToWideChar" && 0);
		return 0;
	}

	return pszUTF16;
}
void RakString::DeallocWideChar(WCHAR * w)
{
	SLNet::OP_DELETE_ARRAY(w,__FILE__,__LINE__);
}
void RakString::FromWideChar(const wchar_t *source)
{
	Clear();
	size_t bufSize = wcslen(source)*4;

	// #low - add return value indicating to the caller whether we succeeded (and then handle error case / or thrown an exception)
	if (bufSize > static_cast<size_t>(std::numeric_limits<int>::max())) {
		RakAssert("RakString::FromWideChar given string is too long and cannot be converted");
		return;
	}

	Allocate(bufSize);
	WideCharToMultiByte ( CP_ACP,                // ANSI code page



                          WC_COMPOSITECHECK,     // Check for accented characters

                          source,         // Source Unicode string
                          -1,                    // -1 means string is zero-terminated
                          sharedString->c_str,          // Destination char string
                          static_cast<int>(bufSize),  // Size of buffer
                          NULL,                  // No default character
                          NULL );                // Don't care about this flag


}
SLNet::RakString RakString::FromWideChar_S(const wchar_t *source)
{
	SLNet::RakString rs;
	rs.FromWideChar(source);
	return rs;
}
#endif
size_t RakString::Find(const char *stringToFind,size_t pos)
{
	size_t len=GetLength();
	if (pos>=len || stringToFind==0 || stringToFind[0]==0)
	{
		return (size_t) -1;
	}
	size_t matchLen= strlen(stringToFind);
	size_t matchPos=0;
	size_t iStart=0;

	for (size_t i=pos;i<len;i++)
	{
		if (stringToFind[matchPos]==sharedString->c_str[i])
		{
			if(matchPos==0)
			{
				iStart=i;
			}
			matchPos++;
		}
		else
		{
			matchPos=0;
		}

		if (matchPos>=matchLen)
		{
			return iStart;
		}
	}

	return (size_t) -1;
}

void RakString::TruncateUTF8(unsigned int length)
{
	int i = 0;
	unsigned int count = 0;

	while (sharedString->c_str[i]!=0)
	{
		if (count==length)
		{
			sharedString->c_str[i]=0;
			return;
		}
		else if (sharedString->c_str[i]>0)
		{
			i++;
		}
		else
		{
			switch (0xF0 & sharedString->c_str[i])
			{
			case 0xE0: i += 3; break;
			case 0xF0: i += 4; break;
			default:   i += 2; break;
			}
		}

		count++;
	}
}

void RakString::Truncate(unsigned int length)
{
	if (length < GetLength())
	{
		SetChar(length, 0);
	}
}

RakString RakString::SubStr(unsigned int index, size_t count) const
{
	size_t length = GetLength();
	if (index >= length || count==0)
		return RakString();
	RakString copy;
	size_t numBytes = length-index;
	if (count < numBytes)
		numBytes=count;
	copy.Allocate(numBytes+1);
	size_t i;
	for (i=0; i < numBytes; i++)
		copy.sharedString->c_str[i]=sharedString->c_str[index+i];
	copy.sharedString->c_str[i]=0;
	return copy;
}
void RakString::Erase(unsigned int index, unsigned int count)
{
	size_t len = GetLength();
	RakAssert(index+count <= len);
        
	Clone();
	unsigned i;
	for (i=index; i < len-count; i++)
	{
		sharedString->c_str[i]=sharedString->c_str[i+count];
	}
	sharedString->c_str[i]=0;
}
void RakString::TerminateAtLastCharacter(char c)
{
	int i, len=(int) GetLength();
	for (i=len-1; i >= 0; i--)
	{
		if (sharedString->c_str[i]==c)
		{
			Clone();
			sharedString->c_str[i]=0;
			return;
		}
	}
}
void RakString::StartAfterLastCharacter(char c)
{
	int i, len=(int) GetLength();
	for (i=len-1; i >= 0; i--)
	{
		if (sharedString->c_str[i]==c)
		{
			++i;
			if (i < len)
			{
				*this = SubStr(i,GetLength()-i);
			}
			return;
		}
	}
}
void RakString::TerminateAtFirstCharacter(char c)
{
	unsigned int i, len=(unsigned int) GetLength();
	for (i=0; i < len; i++)
	{
		if (sharedString->c_str[i]==c)
		{
			if (i > 0)
			{
				Clone();
				sharedString->c_str[i]=0;
			}
		}
	}
}
void RakString::StartAfterFirstCharacter(char c)
{
	unsigned int i, len=(unsigned int) GetLength();
	for (i=0; i < len; i++)
	{
		if (sharedString->c_str[i]==c)
		{
			++i;
			if (i < len)
			{
				*this = SubStr(i,GetLength()-i);
			}
			return;
		}
	}
}
int RakString::GetCharacterCount(char c)
{
	int count=0;
	unsigned int i, len=(unsigned int) GetLength();
	for (i=0; i < len; i++)
	{
		if (sharedString->c_str[i]==c)
		{
			++count;
		}
	}
	return count;
}
void RakString::RemoveCharacter(char c)
{
	if (c==0)
		return;

	unsigned int readIndex, writeIndex=0;
	for (readIndex=0; sharedString->c_str[readIndex]; readIndex++)
	{
		if (sharedString->c_str[readIndex]!=c)
			sharedString->c_str[writeIndex++]=sharedString->c_str[readIndex];
		else
			Clone();
	}
	sharedString->c_str[writeIndex]=0;
	if (writeIndex==0)
		Clear();
}
int RakString::StrCmp(const RakString &rhs) const
{
	return strcmp(sharedString->c_str, rhs.C_String());
}
int RakString::StrNCmp(const RakString &rhs, size_t num) const
{
	return strncmp(sharedString->c_str, rhs.C_String(), num);
}
int RakString::StrICmp(const RakString &rhs) const
{
	return _stricmp(sharedString->c_str, rhs.C_String());
}
void RakString::Printf(void)
{
	RAKNET_DEBUG_PRINTF("%s", sharedString->c_str);
}
void RakString::FPrintf(FILE *fp)
{
	fprintf(fp,"%s", sharedString->c_str);
}
bool RakString::IPAddressMatch(const char *IP)
{
	unsigned characterIndex;

	if ( IP == 0 || IP[ 0 ] == 0 || strlen( IP ) > 15 )
		return false;

	characterIndex = 0;

	for(;;)
	{
		if (sharedString->c_str[ characterIndex ] == IP[ characterIndex ] )
		{
			// Equal characters
			if ( IP[ characterIndex ] == 0 )
			{
				// End of the string and the strings match

				return true;
			}

			characterIndex++;
		}

		else
		{
			if ( sharedString->c_str[ characterIndex ] == 0 || IP[ characterIndex ] == 0 )
			{
				// End of one of the strings
				break;
			}

			// Characters do not match
			if ( sharedString->c_str[ characterIndex ] == '*' )
			{
				// Domain is banned.
				return true;
			}

			// Characters do not match and it is not a *
			break;
		}
	}


	// No match found.
	return false;
}
bool RakString::ContainsNonprintableExceptSpaces(void) const
{
	size_t strLen = strlen(sharedString->c_str);
	unsigned i;
	for (i=0; i < strLen; i++)
	{
		if (sharedString->c_str[i] < ' ' || sharedString->c_str[i] >126)
			return true;
	}
	return false;
}
bool RakString::IsEmailAddress(void) const
{
	if (IsEmpty())
		return false;
	size_t strLen = strlen(sharedString->c_str);
	if (strLen < 6) // a@b.de
		return false;
	if (sharedString->c_str[strLen-4]!='.' && sharedString->c_str[strLen-3]!='.') // .com, .net., .org, .de
		return false;
	unsigned i;
	// Has non-printable?
	for (i=0; i < strLen; i++)
	{
		if (sharedString->c_str[i] <= ' ' || sharedString->c_str[i] >126)
			return false;
	}
	int atCount=0;
	for (i=0; i < strLen; i++)
	{
		if (sharedString->c_str[i]=='@')
		{
			atCount++;
		}
	}
	if (atCount!=1)
		return false;
	int dotCount=0;
	for (i=0; i < strLen; i++)
	{
		if (sharedString->c_str[i]=='.')
		{
			dotCount++;
		}
	}
	if (dotCount==0)
		return false;

	// There's more I could check, but this is good enough
	return true;
}
SLNet::RakString& RakString::URLEncode(void)
{
	RakString result;
	size_t strLen = strlen(sharedString->c_str);
	result.Allocate(strLen*3);
	char *output=result.sharedString->c_str;
	unsigned int outputIndex=0;
	unsigned i;
	unsigned char c;
	for (i=0; i < strLen; i++)
	{
		c=sharedString->c_str[i];
		if (
			(c<=47) ||
			(c>=58 && c<=64) ||
			(c>=91 && c<=96) ||
			(c>=123)
			)
		{
			char buff[3];
			Itoa(c, buff, 16);
			output[outputIndex++]='%';
			output[outputIndex++]=buff[0];
			output[outputIndex++]=buff[1];
		}
		else
		{
			output[outputIndex++]=c;
		}
	}

	output[outputIndex]=0;

	*this = result;
	return *this;
}
SLNet::RakString& RakString::URLDecode(void)
{
	RakString result;
	size_t strLen = strlen(sharedString->c_str);
	result.Allocate(strLen);
	char *output=result.sharedString->c_str;
	unsigned int outputIndex=0;
	char c;
	char hexDigits[2];
	char hexValues[2];
	unsigned int i;
	for (i=0; i < strLen; i++)
	{
		c=sharedString->c_str[i];
		if (c=='%')
		{
			hexDigits[0]=sharedString->c_str[++i];
			hexDigits[1]=sharedString->c_str[++i];
			
			if (hexDigits[0]==' ')
				hexValues[0]=0;
			
			if (hexDigits[0]>='A' && hexDigits[0]<='F')
				hexValues[0]=hexDigits[0]-'A'+10;
			if (hexDigits[0]>='a' && hexDigits[0]<='f')
				hexValues[0]=hexDigits[0]-'a'+10;
			else
				hexValues[0]=hexDigits[0]-'0';

			if (hexDigits[1]>='A' && hexDigits[1]<='F')
				hexValues[1]=hexDigits[1]-'A'+10;
			if (hexDigits[1]>='a' && hexDigits[1]<='f')
				hexValues[1]=hexDigits[1]-'a'+10;
			else
				hexValues[1]=hexDigits[1]-'0';

			output[outputIndex++]=hexValues[0]*16+hexValues[1];
		}
		else
		{
			output[outputIndex++]=c;
		}
	}

	output[outputIndex]=0;

	*this = result;
	return *this;
}
void RakString::SplitURI(SLNet::RakString &header, SLNet::RakString &domain, SLNet::RakString &path)
{
	header.Clear();
	domain.Clear();
	path.Clear();

	size_t strLen = strlen(sharedString->c_str);

	char c;
	unsigned int i=0;
	if (strncmp(sharedString->c_str, "http://", 7)==0)
		i+=(unsigned int) strlen("http://");
	else if (strncmp(sharedString->c_str, "https://", 8)==0)
		i+=(unsigned int) strlen("https://");
	
	if (strncmp(sharedString->c_str, "www.", 4)==0)
		i+=(unsigned int) strlen("www.");

	if (i!=0)
	{
		header.Allocate(i+1);
		strncpy_s(header.sharedString->c_str, header.sharedString->bytesUsed, sharedString->c_str, i);
		header.sharedString->c_str[i]=0;
	}


	domain.Allocate(strLen-i+1);
	char *domainOutput=domain.sharedString->c_str;
	unsigned int outputIndex=0;
	for (; i < strLen; i++)
	{
		c=sharedString->c_str[i];
		if (c=='/')
		{
			break;
		}
		else
		{
			domainOutput[outputIndex++]=sharedString->c_str[i];
		}
	}

	domainOutput[outputIndex]=0;

	path.Allocate(strLen-header.GetLength()-outputIndex+1);
	outputIndex=0;
	char *pathOutput=path.sharedString->c_str;
	for (; i < strLen; i++)
	{
		pathOutput[outputIndex++]=sharedString->c_str[i];
	}
	pathOutput[outputIndex]=0;
}
SLNet::RakString& RakString::SQLEscape(void)
{
	int strLen=(int)GetLength();
	int escapedCharacterCount=0;
	int index;
	for (index=0; index < strLen; index++)
	{
		if (sharedString->c_str[index]=='\'' ||
			sharedString->c_str[index]=='"' ||
			sharedString->c_str[index]=='\\')
			escapedCharacterCount++;
	}
	if (escapedCharacterCount==0)
		return *this;

	Clone();
	Realloc(sharedString, strLen+escapedCharacterCount);
	int writeIndex, readIndex;
	writeIndex = strLen+escapedCharacterCount;
	readIndex=strLen;
	while (readIndex>=0)
	{
		if (sharedString->c_str[readIndex]=='\'' ||
			sharedString->c_str[readIndex]=='"' ||
			sharedString->c_str[readIndex]=='\\')
		{
			sharedString->c_str[writeIndex--]=sharedString->c_str[readIndex--];
			sharedString->c_str[writeIndex--]='\\';
		}
		else
		{
			sharedString->c_str[writeIndex--]=sharedString->c_str[readIndex--];
		}
	}
	return *this;
}
SLNet::RakString RakString::FormatForPUTOrPost(const char* type, const char* uri, const char* contentType, const char* body, const char* extraHeaders)
{
	RakString out;
	RakString host;
	RakString remotePath;
	SLNet::RakString header;
	RakString uriRs;
	uriRs = uri;
	uriRs.SplitURI(header, host, remotePath);

	if (host.IsEmpty() || remotePath.IsEmpty())
		return out;

//	RakString bodyEncoded = body;
//	bodyEncoded.URLEncode();

	if (extraHeaders!=0 && extraHeaders[0])
	{
		out.Set("%s %s HTTP/1.1\r\n"
			"%s\r\n"
			"Host: %s\r\n"
			"Content-Type: %s\r\n"
			"Content-Length: %u\r\n"
			"\r\n"
			"%s",
			type,
			remotePath.C_String(),
			extraHeaders,
			host.C_String(),
			contentType,
			//bodyEncoded.GetLength(),
			//bodyEncoded.C_String());
			strlen(body),
			body);
	}
	else
	{
		out.Set("%s %s HTTP/1.1\r\n"
			"Host: %s\r\n"
			"Content-Type: %s\r\n"
			"Content-Length: %u\r\n"
			"\r\n"
			"%s",
			type,
			remotePath.C_String(),
			host.C_String(),
			contentType,
			//bodyEncoded.GetLength(),
			//bodyEncoded.C_String());
			strlen(body),
			body);
	}

	return out;
}
RakString RakString::FormatForPOST(const char* uri, const char* contentType, const char* body, const char* extraHeaders)
{
	return FormatForPUTOrPost("POST", uri, contentType, body, extraHeaders);
}
RakString RakString::FormatForPUT(const char* uri, const char* contentType, const char* body, const char* extraHeaders)
{
	return FormatForPUTOrPost("PUT", uri, contentType, body, extraHeaders);
}
RakString RakString::FormatForGET(const char* uri, const char* extraHeaders)
{
	RakString out;
	RakString host;
	RakString remotePath;
	SLNet::RakString header;
	SLNet::RakString uriRs;
	uriRs = uri;

	uriRs.SplitURI(header, host, remotePath);
	if (host.IsEmpty() || remotePath.IsEmpty())
		return out;

	if (extraHeaders && extraHeaders[0])
	{
		out.Set("GET %s HTTP/1.1\r\n"
			"%s\r\n"
			"Host: %s\r\n"
			"\r\n",
			remotePath.C_String(),
			extraHeaders,
			host.C_String());
	}
	else
	{
		out.Set("GET %s HTTP/1.1\r\n"
			"Host: %s\r\n"
			"\r\n",
			remotePath.C_String(),
			host.C_String());

	}


	return out;
}
RakString RakString::FormatForDELETE(const char* uri, const char* extraHeaders)
{
	RakString out;
	RakString host;
	RakString remotePath;
	SLNet::RakString header;
	SLNet::RakString uriRs;
	uriRs = uri;

	uriRs.SplitURI(header, host, remotePath);
	if (host.IsEmpty() || remotePath.IsEmpty())
		return out;

	if (extraHeaders && extraHeaders[0])
	{
		out.Set("DELETE %s HTTP/1.1\r\n"
			"%s\r\n"
			"Content-Length: 0\r\n"
			"Host: %s\r\n"
			"Connection: close\r\n"
			"\r\n",
			remotePath.C_String(),
			extraHeaders,
			host.C_String());
	}
	else
	{
		out.Set("DELETE %s HTTP/1.1\r\n"
			"Content-Length: 0\r\n"
			"Host: %s\r\n"
			"Connection: close\r\n"
			"\r\n",
			remotePath.C_String(),
			host.C_String());
	}

	return out;
}
SLNet::RakString& RakString::MakeFilePath(void)
{
	if (IsEmpty())
		return *this;

	SLNet::RakString fixedString = *this;
	fixedString.Clone();
	for (int i=0; fixedString.sharedString->c_str[i]; i++)
	{
#ifdef _WIN32
		if (fixedString.sharedString->c_str[i]=='/')
			fixedString.sharedString->c_str[i]='\\';
#else
		if (fixedString.sharedString->c_str[i]=='\\')
			fixedString.sharedString->c_str[i]='/';
#endif
	}

#ifdef _WIN32
	if (fixedString.sharedString->c_str[strlen(fixedString.sharedString->c_str)-1]!='\\')
	{
		fixedString+='\\';
	}
#else
	if (fixedString.sharedString->c_str[strlen(fixedString.sharedString->c_str)-1]!='/')
	{
		fixedString+='/';
	}
#endif

	if (fixedString!=*this)
		*this = fixedString;
	return *this;
}
void RakString::FreeMemory(void)
{
	LockMutex();
	FreeMemoryNoMutex();
	UnlockMutex();
}
void RakString::FreeMemoryNoMutex(void)
{
	for (unsigned int i=0; i < freeList.Size(); i++)
	{
		SLNet::OP_DELETE(freeList[i]->refCountMutex,_FILE_AND_LINE_);
		rakFree_Ex(freeList[i], _FILE_AND_LINE_ );
	}
	freeList.Clear(false, _FILE_AND_LINE_);
}
void RakString::Serialize(BitStream *bs) const
{
	Serialize(sharedString->c_str, bs);
}
void RakString::Serialize(const char *str, BitStream *bs)
{
	unsigned short l = (unsigned short) strlen(str);
	bs->Write(l);
	bs->WriteAlignedBytes((const unsigned char*) str, (const unsigned int) l);
}
void RakString::SerializeCompressed(BitStream *bs, uint8_t languageId, bool writeLanguageId) const
{
	SerializeCompressed(C_String(), bs, languageId, writeLanguageId);
}
void RakString::SerializeCompressed(const char *str, BitStream *bs, uint8_t languageId, bool writeLanguageId)
{
	if (writeLanguageId)
		bs->WriteCompressed(languageId);
	StringCompressor::Instance()->EncodeString(str,0xFFFF,bs,languageId);
}
bool RakString::Deserialize(BitStream *bs)
{
	Clear();

	bool b;
	unsigned short l;
	b=bs->Read(l);
	if (l>0)
	{
		Allocate(((unsigned int) l)+1);
		b=bs->ReadAlignedBytes((unsigned char*) sharedString->c_str, l);
		if (b)
			sharedString->c_str[l]=0;
		else
			Clear();
	}
	else
		bs->AlignReadToByteBoundary();
	return b;
}
bool RakString::Deserialize(char *str, BitStream *bs)
{
	bool b;
	unsigned short l;
	b=bs->Read(l);
	if (b && l>0)
		b=bs->ReadAlignedBytes((unsigned char*) str, l);

	if (b==false)
		str[0]=0;
	
	str[l]=0;
	return b;
}
bool RakString::DeserializeCompressed(BitStream *bs, bool readLanguageId)
{
	uint8_t languageId;
	if (readLanguageId)
		bs->ReadCompressed(languageId);
	else
		languageId=0;
	return StringCompressor::Instance()->DecodeString(this,0xFFFF,bs,languageId);
}
bool RakString::DeserializeCompressed(char *str, BitStream *bs, bool readLanguageId)
{
	uint8_t languageId;
	if (readLanguageId)
		bs->ReadCompressed(languageId);
	else
		languageId=0;
	return StringCompressor::Instance()->DecodeString(str,0xFFFF,bs,languageId);
}
const char *RakString::ToString(int64_t i)
{
	static int index=0;
	static char buff[64][64];
#if defined(_WIN32)
	sprintf(buff[index], "%I64d", i);
#else
	sprintf(buff[index], "%lld", (long long unsigned int) i);
#endif
	int lastIndex=index;
	if (++index==64)
		index=0;
	return buff[lastIndex];
}
const char *RakString::ToString(uint64_t i)
{
	static int index=0;
	static char buff[64][64];
#if defined(_WIN32)
	sprintf(buff[index], "%I64u", i);
#else
	sprintf(buff[index], "%llu", (long long unsigned int) i);
#endif
	int lastIndex=index;
	if (++index==64)
		index=0;
	return buff[lastIndex];
}
void RakString::Clear(void)
{
	Free();
}
void RakString::Allocate(size_t len)
{
	RakString::LockMutex();
	// sharedString = RakString::pool.Allocate( _FILE_AND_LINE_ );
	if (RakString::freeList.Size()==0)
	{
		//RakString::sharedStringFreeList=(RakString::SharedString*) rakRealloc_Ex(RakString::sharedStringFreeList,(RakString::sharedStringFreeListAllocationCount+1024)*sizeof(RakString::SharedString), _FILE_AND_LINE_);
		unsigned i;
		for (i=0; i < 128; i++)
		{
			//	RakString::freeList.Insert(RakString::sharedStringFreeList+i+RakString::sharedStringFreeListAllocationCount);
	//		RakString::freeList.Insert((RakString::SharedString*)rakMalloc_Ex(sizeof(RakString::SharedString), _FILE_AND_LINE_), _FILE_AND_LINE_);

			RakString::SharedString *ss;
			ss = (RakString::SharedString*) rakMalloc_Ex(sizeof(RakString::SharedString), _FILE_AND_LINE_);
			ss->refCountMutex= SLNet::OP_NEW<SimpleMutex>(_FILE_AND_LINE_);
			RakString::freeList.Insert(ss, _FILE_AND_LINE_);
		}
		//RakString::sharedStringFreeListAllocationCount+=1024;
	}
	sharedString = RakString::freeList[RakString::freeList.Size()-1];
	RakString::freeList.RemoveAtIndex(RakString::freeList.Size()-1);
	RakString::UnlockMutex();

	const size_t smallStringSize = 128-sizeof(unsigned int)-sizeof(size_t)-sizeof(char*)*2;
	sharedString->refCount=1;
	if (len <= smallStringSize)
	{
		sharedString->bytesUsed=smallStringSize;
		sharedString->c_str=sharedString->smallString;
	}
	else
	{
		sharedString->bytesUsed=len<<1;
		sharedString->bigString=(char*)rakMalloc_Ex(sharedString->bytesUsed, _FILE_AND_LINE_);
		sharedString->c_str=sharedString->bigString;
	}
}
void RakString::Assign(const char *str)
{
	if (str==0 || str[0]==0)
	{
		sharedString=&emptyString;
		return;
	}

	size_t len = strlen(str)+1;
	Allocate(len);
	memcpy(sharedString->c_str, str, len);
}
void RakString::Assign(const char *str, va_list ap)
{
	if (str==0 || str[0]==0)
	{
		sharedString=&emptyString;
		return;
	}

	char stackBuff[512];
	int numChars = vsnprintf_s(stackBuff, 511, str, ap);
	if (numChars != -1)
	{
		Assign(stackBuff);
		return;
	}
	char *buff=0, *newBuff;
	size_t buffSize=8096;
	for(;;)
	{
		newBuff = (char*) rakRealloc_Ex(buff, buffSize,__FILE__,__LINE__);
		if (newBuff==0)
		{
			notifyOutOfMemory(_FILE_AND_LINE_);
			if (buff!=0)
			{
				Assign(buff);
				rakFree_Ex(buff,__FILE__,__LINE__);
			}
			else
			{
				Assign(stackBuff);
			}
			return;
		}
		buff=newBuff;
		if (vsnprintf_s(buff, buffSize, buffSize-1, str, ap)!=-1)
		{
			Assign(buff);
			rakFree_Ex(buff,__FILE__,__LINE__);
			return;
		}
		buffSize*=2;
	}
}
SLNet::RakString RakString::Assign(const char *str,size_t pos, size_t n )
{
	size_t incomingLen=strlen(str);

	Clone();

	if (str==0 || str[0]==0||pos>=incomingLen)
	{
		sharedString=&emptyString;
		return (*this);
	}

	if (pos+n>=incomingLen)
	{
	n=incomingLen-pos;
	
	}
	const char * tmpStr=&(str[pos]); 

	size_t len = n+1;
	Allocate(len);
	memcpy(sharedString->c_str, tmpStr, len);
	sharedString->c_str[n]=0;

	return (*this);
}

SLNet::RakString RakString::NonVariadic(const char *str)
{
	SLNet::RakString rs;
	rs=str;
	return rs;
}
unsigned long RakString::ToInteger(const char *str)
{
	unsigned long hash = 0;
	int c = *str;

	while (c) {
		hash = c + (hash << 6) + (hash << 16) - hash;
		c = *(++str);
	}

	return hash;
}
unsigned long RakString::ToInteger(const RakString &rs)
{
	return RakString::ToInteger(rs.C_String());
}
int RakString::ReadIntFromSubstring(const char *str, size_t pos, size_t n)
{
	char tmp[32];
	if (n >= 32)
		return 0;
	for (size_t i=0; i < n; i++)
		tmp[i]=str[i+pos];
	return atoi(tmp);
}
void RakString::AppendBytes(const char *bytes, size_t count)
{
	if (IsEmpty())
	{
		Allocate(count);
		memcpy(sharedString->c_str, bytes, count+1);
		sharedString->c_str[count]=0;
	}
	else
	{
		Clone();
		unsigned int length=(unsigned int) GetLength();
		Realloc(sharedString, count+length+1);
		memcpy(sharedString->c_str+length, bytes, count);
		sharedString->c_str[length+count]=0;
	}

	
}
void RakString::Clone(void)
{
	RakAssert(sharedString!=&emptyString);
	if (sharedString==&emptyString)
	{
		return;
	}

	// Empty or solo then no point to cloning
	sharedString->refCountMutex->Lock();
	if (sharedString->refCount==1)
	{
		sharedString->refCountMutex->Unlock();
		return;
	}

	sharedString->refCount--;
	sharedString->refCountMutex->Unlock();
	Assign(sharedString->c_str);
}
void RakString::Free(void)
{
	if (sharedString==&emptyString)
		return;
	sharedString->refCountMutex->Lock();
	sharedString->refCount--;
	if (sharedString->refCount==0)
	{
		sharedString->refCountMutex->Unlock();
		const size_t smallStringSize = 128-sizeof(unsigned int)-sizeof(size_t)-sizeof(char*)*2;
		if (sharedString->bytesUsed>smallStringSize)
			rakFree_Ex(sharedString->bigString, _FILE_AND_LINE_ );
		/*
		poolMutex->Lock();
		pool.Release(sharedString);
		poolMutex->Unlock();
		*/

		RakString::LockMutex();
		RakString::freeList.Insert(sharedString, _FILE_AND_LINE_);
		RakString::UnlockMutex();

		sharedString=&emptyString;
	}
	else
	{
		sharedString->refCountMutex->Unlock();
	}
	sharedString=&emptyString;
}
unsigned char RakString::ToLower(unsigned char c)
{
	if (c >= 'A' && c <= 'Z')
		return c-'A'+'a';
	return c;
}
unsigned char RakString::ToUpper(unsigned char c)
{
	if (c >= 'a' && c <= 'z')
		return c-'a'+'A';
	return c;
}
void RakString::LockMutex(void)
{
	GetPoolMutex().Lock();
}
void RakString::UnlockMutex(void)
{
	GetPoolMutex().Unlock();
}

/*
#include "slikenet/string.h"
#include <string>
#include "slikenet/GetTime.h"

using namespace SLNet;

int main(void)
{
	RakString s3("Hello world");
	RakString s5=s3;

	RakString s1;
	RakString s2('a');

	RakString s4("%i %f", 5, 6.0);

	RakString s6=s3;
	RakString s7=s6;
	RakString s8=s6;
	RakString s9;
	s9=s9;
	RakString s10(s3);
	RakString s11=s10 + s4 + s9 + s2;
	s11+=RakString("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	RakString s12("Test");
	s12+=s11;
	bool b1 = s12==s12;
	s11=s5;
	s12.ToUpper();
	s12.ToLower();
	RakString s13;
	bool b3 = s13.IsEmpty();
	s13.Set("blah %s", s12.C_String());
	bool b4 = s13.IsEmpty();
	size_t i1=s13.GetLength();
	s3.Clear(_FILE_AND_LINE_);
	s4.Clear(_FILE_AND_LINE_);
	s5.Clear(_FILE_AND_LINE_);
	s5.Clear(_FILE_AND_LINE_);
	s6.Printf();
	s7.Printf();
	RAKNET_DEBUG_PRINTF("\n");

	static const int repeatCount=750;
	DataStructures::List<RakString> rakStringList;
	DataStructures::List<std::string> stdStringList;
	DataStructures::List<char*> referenceStringList;
	char *c;
	unsigned i;
	SLNet::TimeMS beforeReferenceList, beforeRakString, beforeStdString, afterStdString;

	unsigned loop;
	for (loop=0; loop<2; loop++)
	{
		beforeReferenceList=SLNet::GetTimeMS();
		for (i=0; i < repeatCount; i++)
		{
			c = SLNet::OP_NEW_ARRAY<char >(56,_FILE_AND_LINE_ );
			strcpy_s(c, 56, "Aalsdkj alsdjf laksdjf ;lasdfj ;lasjfd");
			referenceStringList.Insert(c);
		}
		beforeRakString=SLNet::GetTimeMS();
		for (i=0; i < repeatCount; i++)
			rakStringList.Insert("Aalsdkj alsdjf laksdjf ;lasdfj ;lasjfd");
		beforeStdString=SLNet::GetTimeMS();

		for (i=0; i < repeatCount; i++)
			stdStringList.Insert("Aalsdkj alsdjf laksdjf ;lasdfj ;lasjfd");
		afterStdString=SLNet::GetTimeMS();
		RAKNET_DEBUG_PRINTF("Insertion 1 Ref=%i Rak=%i, Std=%i\n", beforeRakString-beforeReferenceList, beforeStdString-beforeRakString, afterStdString-beforeStdString);

		beforeReferenceList=SLNet::GetTimeMS();
		for (i=0; i < repeatCount; i++)
		{
			SLNet::OP_DELETE_ARRAY(referenceStringList[0], _FILE_AND_LINE_);
			referenceStringList.RemoveAtIndex(0);
		}
		beforeRakString=SLNet::GetTimeMS();
		for (i=0; i < repeatCount; i++)
			rakStringList.RemoveAtIndex(0);
		beforeStdString=SLNet::GetTimeMS();
		for (i=0; i < repeatCount; i++)
			stdStringList.RemoveAtIndex(0);
		afterStdString=SLNet::GetTimeMS();
		RAKNET_DEBUG_PRINTF("RemoveHead Ref=%i Rak=%i, Std=%i\n", beforeRakString-beforeReferenceList, beforeStdString-beforeRakString, afterStdString-beforeStdString);

		beforeReferenceList=SLNet::GetTimeMS();
		for (i=0; i < repeatCount; i++)
		{
			c = SLNet::OP_NEW_ARRAY<char >(56, _FILE_AND_LINE_ );
			strcpy_s(c, 56, "Aalsdkj alsdjf laksdjf ;lasdfj ;lasjfd");
			referenceStringList.Insert(0);
		}
		beforeRakString=SLNet::GetTimeMS();
		for (i=0; i < repeatCount; i++)
			rakStringList.Insert("Aalsdkj alsdjf laksdjf ;lasdfj ;lasjfd");
		beforeStdString=SLNet::GetTimeMS();
		for (i=0; i < repeatCount; i++)
			stdStringList.Insert("Aalsdkj alsdjf laksdjf ;lasdfj ;lasjfd");
		afterStdString=SLNet::GetTimeMS();
		RAKNET_DEBUG_PRINTF("Insertion 2 Ref=%i Rak=%i, Std=%i\n", beforeRakString-beforeReferenceList, beforeStdString-beforeRakString, afterStdString-beforeStdString);

		beforeReferenceList=SLNet::GetTimeMS();
		for (i=0; i < repeatCount; i++)
		{
			SLNet::OP_DELETE_ARRAY(referenceStringList[referenceStringList.Size()-1], _FILE_AND_LINE_);
			referenceStringList.RemoveAtIndex(referenceStringList.Size()-1);
		}
		beforeRakString=SLNet::GetTimeMS();
		for (i=0; i < repeatCount; i++)
			rakStringList.RemoveAtIndex(rakStringList.Size()-1);
		beforeStdString=SLNet::GetTimeMS();
		for (i=0; i < repeatCount; i++)
			stdStringList.RemoveAtIndex(stdStringList.Size()-1);
		afterStdString=SLNet::GetTimeMS();
		RAKNET_DEBUG_PRINTF("RemoveTail Ref=%i Rak=%i, Std=%i\n", beforeRakString-beforeReferenceList, beforeStdString-beforeRakString, afterStdString-beforeStdString);

	}

	printf("Done.");
	char str[128];
	Gets(str, sizeof(str));
	return 1;
}
*/
