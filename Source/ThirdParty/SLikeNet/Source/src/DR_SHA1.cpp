/*
  100% free public domain implementation of the SHA-1 algorithm
  by Dominik Reichl <dominik.reichl@t-online.de>
  Web: http://www.dominik-reichl.de/

  See header file for version history and test vectors.
*/

/*
 * Modified work : Copyright(c) 2016-2017, SLikeSoft UG(haftungsbeschränkt)
 *
 * This source code was modified by SLikeSoft. Modifications in this file are put under the public domain.
 * Alternatively you are permitted to license the modifications under the MIT license, if you so desire. The
 * license can be found in the license.txt file in the root directory of this source tree.
 */

// If compiling with MFC, you might want to add #include "StdAfx.h"

#define _CRT_SECURE_NO_WARNINGS
#include "slikenet/DR_SHA1.h"
#include <stdlib.h>

#define SHA1_MAX_FILE_BUFFER (32 * 20 * 820)

// Rotate p_val32 by p_nBits bits to the left
#ifndef ROL32
#ifdef _MSC_VER
#define ROL32(p_val32,p_nBits) _rotl(p_val32,p_nBits)
#else
#define ROL32(p_val32,p_nBits) (((p_val32)<<(p_nBits))|((p_val32)>>(32-(p_nBits))))
#endif
#endif

#ifdef SHA1_LITTLE_ENDIAN
#define SHABLK0(i) (m_block->l[i] = \
	(ROL32(m_block->l[i],24) & 0xFF00FF00) | (ROL32(m_block->l[i],8) & 0x00FF00FF))
#else
#define SHABLK0(i) (m_block->l[i])
#endif

#define SHABLK(i) (m_block->l[i&15] = ROL32(m_block->l[(i+13)&15] ^ \
	m_block->l[(i+8)&15] ^ m_block->l[(i+2)&15] ^ m_block->l[i&15],1))

// SHA-1 rounds
#define S_R0(v,w,x,y,z,i) {z+=((w&(x^y))^y)+SHABLK0(i)+0x5A827999+ROL32(v,5);w=ROL32(w,30);}
#define S_R1(v,w,x,y,z,i) {z+=((w&(x^y))^y)+SHABLK(i)+0x5A827999+ROL32(v,5);w=ROL32(w,30);}
#define S_R2(v,w,x,y,z,i) {z+=(w^x^y)+SHABLK(i)+0x6ED9EBA1+ROL32(v,5);w=ROL32(w,30);}
#define S_R3(v,w,x,y,z,i) {z+=(((w|x)&y)|(w&x))+SHABLK(i)+0x8F1BBCDC+ROL32(v,5);w=ROL32(w,30);}
#define S_R4(v,w,x,y,z,i) {z+=(w^x^y)+SHABLK(i)+0xCA62C1D6+ROL32(v,5);w=ROL32(w,30);}

CSHA1::CSHA1()
{
	m_block = (SHA1_WORKSPACE_BLOCK*)m_workspace;

	Reset();
}

#ifdef SHA1_WIPE_VARIABLES
CSHA1::~CSHA1()
{
	Reset();
}
#endif

void CSHA1::Reset()
{
	// SHA1 initialization constants
	m_state[0] = 0x67452301;
	m_state[1] = 0xEFCDAB89;
	m_state[2] = 0x98BADCFE;
	m_state[3] = 0x10325476;
	m_state[4] = 0xC3D2E1F0;

	m_count[0] = 0;
	m_count[1] = 0;
}

void CSHA1::Transform(UINT_32* pState, const UINT_8* pBuffer)
{
	UINT_32 a = pState[0], b = pState[1], c = pState[2], d = pState[3], e = pState[4];

	memcpy(m_block, pBuffer, 64);

	// 4 rounds of 20 operations each, loop unrolled
	S_R0(a,b,c,d,e, 0); S_R0(e,a,b,c,d, 1); S_R0(d,e,a,b,c, 2); S_R0(c,d,e,a,b, 3);
	S_R0(b,c,d,e,a, 4); S_R0(a,b,c,d,e, 5); S_R0(e,a,b,c,d, 6); S_R0(d,e,a,b,c, 7);
	S_R0(c,d,e,a,b, 8); S_R0(b,c,d,e,a, 9); S_R0(a,b,c,d,e,10); S_R0(e,a,b,c,d,11);
	S_R0(d,e,a,b,c,12); S_R0(c,d,e,a,b,13); S_R0(b,c,d,e,a,14); S_R0(a,b,c,d,e,15);
	S_R1(e,a,b,c,d,16); S_R1(d,e,a,b,c,17); S_R1(c,d,e,a,b,18); S_R1(b,c,d,e,a,19);
	S_R2(a,b,c,d,e,20); S_R2(e,a,b,c,d,21); S_R2(d,e,a,b,c,22); S_R2(c,d,e,a,b,23);
	S_R2(b,c,d,e,a,24); S_R2(a,b,c,d,e,25); S_R2(e,a,b,c,d,26); S_R2(d,e,a,b,c,27);
	S_R2(c,d,e,a,b,28); S_R2(b,c,d,e,a,29); S_R2(a,b,c,d,e,30); S_R2(e,a,b,c,d,31);
	S_R2(d,e,a,b,c,32); S_R2(c,d,e,a,b,33); S_R2(b,c,d,e,a,34); S_R2(a,b,c,d,e,35);
	S_R2(e,a,b,c,d,36); S_R2(d,e,a,b,c,37); S_R2(c,d,e,a,b,38); S_R2(b,c,d,e,a,39);
	S_R3(a,b,c,d,e,40); S_R3(e,a,b,c,d,41); S_R3(d,e,a,b,c,42); S_R3(c,d,e,a,b,43);
	S_R3(b,c,d,e,a,44); S_R3(a,b,c,d,e,45); S_R3(e,a,b,c,d,46); S_R3(d,e,a,b,c,47);
	S_R3(c,d,e,a,b,48); S_R3(b,c,d,e,a,49); S_R3(a,b,c,d,e,50); S_R3(e,a,b,c,d,51);
	S_R3(d,e,a,b,c,52); S_R3(c,d,e,a,b,53); S_R3(b,c,d,e,a,54); S_R3(a,b,c,d,e,55);
	S_R3(e,a,b,c,d,56); S_R3(d,e,a,b,c,57); S_R3(c,d,e,a,b,58); S_R3(b,c,d,e,a,59);
	S_R4(a,b,c,d,e,60); S_R4(e,a,b,c,d,61); S_R4(d,e,a,b,c,62); S_R4(c,d,e,a,b,63);
	S_R4(b,c,d,e,a,64); S_R4(a,b,c,d,e,65); S_R4(e,a,b,c,d,66); S_R4(d,e,a,b,c,67);
	S_R4(c,d,e,a,b,68); S_R4(b,c,d,e,a,69); S_R4(a,b,c,d,e,70); S_R4(e,a,b,c,d,71);
	S_R4(d,e,a,b,c,72); S_R4(c,d,e,a,b,73); S_R4(b,c,d,e,a,74); S_R4(a,b,c,d,e,75);
	S_R4(e,a,b,c,d,76); S_R4(d,e,a,b,c,77); S_R4(c,d,e,a,b,78); S_R4(b,c,d,e,a,79);

	// Add the working vars back into state
	pState[0] += a;
	pState[1] += b;
	pState[2] += c;
	pState[3] += d;
	pState[4] += e;

	// Wipe variables
#ifdef SHA1_WIPE_VARIABLES
	a = b = c = d = e = 0;
#endif
}

void CSHA1::Update(const UINT_8* pbData, UINT_32 uLen)
{
	UINT_32 j = ((m_count[0] >> 3) & 0x3F);

	if((m_count[0] += (uLen << 3)) < (uLen << 3))
		++m_count[1]; // Overflow

	m_count[1] += (uLen >> 29);

	UINT_32 i;
	if((j + uLen) > 63)
	{
		i = 64 - j;
		memcpy(&m_buffer[j], pbData, i);
		Transform(m_state, m_buffer);

		for( ; (i + 63) < uLen; i += 64)
			Transform(m_state, &pbData[i]);

		j = 0;
	}
	else i = 0;

	if((uLen - i) != 0)
		memcpy(&m_buffer[j], &pbData[i], uLen - i);
}

#ifdef SHA1_UTILITY_FUNCTIONS
bool CSHA1::HashFile(const TCHAR* tszFileName)
{
	if(tszFileName == NULL) return false;

	FILE* fpIn = _tfopen(tszFileName, _T("rb"));
	if(fpIn == NULL) return false;

	UINT_8* pbData = new UINT_8[SHA1_MAX_FILE_BUFFER];
	if(pbData == NULL) { fclose(fpIn); return false; }

	bool bSuccess = true;
	for(;;)
	{
		const size_t uRead = fread(pbData, 1, SHA1_MAX_FILE_BUFFER, fpIn);

		if(uRead > 0)
			Update(pbData, static_cast<UINT_32>(uRead));

		if(uRead < SHA1_MAX_FILE_BUFFER)
		{
			if(feof(fpIn) == 0) bSuccess = false;
			break;
		}
	}

	fclose(fpIn);
	delete[] pbData;
	return bSuccess;
}
#endif

void CSHA1::Final()
{
	UINT_32 i;

	UINT_8 pbFinalCount[8];
	for(i = 0; i < 8; ++i)
		pbFinalCount[i] = static_cast<UINT_8>((m_count[((i >= 4) ? 0 : 1)] >>
			((3 - (i & 3)) * 8) ) & 0xFF); // Endian independent

	Update((UINT_8*)"\200", 1);

	while((m_count[0] & 504) != 448)
		Update((UINT_8*)"\0", 1);

	Update(pbFinalCount, 8); // Cause a Transform()

	for(i = 0; i < 20; ++i)
		m_digest[i] = static_cast<UINT_8>((m_state[i >> 2] >> ((3 -
			(i & 3)) * 8)) & 0xFF);

	// Wipe variables for security reasons
#ifdef SHA1_WIPE_VARIABLES
	memset(m_buffer, 0, 64);
	memset(m_state, 0, 20);
	memset(m_count, 0, 8);
	memset(pbFinalCount, 0, 8);
	Transform(m_state, m_buffer);
#endif
}

#ifdef SHA1_UTILITY_FUNCTIONS
bool CSHA1::ReportHash(TCHAR* tszReport, REPORT_TYPE rtReportType) const
{
	if(tszReport == NULL) return false;

	TCHAR tszTemp[16];

	if((rtReportType == REPORT_HEX) || (rtReportType == REPORT_HEX_SHORT))
	{
		_sntprintf(tszTemp, 15, _T("%02X"), m_digest[0]);
		_tcscpy(tszReport, tszTemp);

		const TCHAR* lpFmt = ((rtReportType == REPORT_HEX) ? _T(" %02X") : _T("%02X"));
		for(size_t i = 1; i < 20; ++i)
		{
			_sntprintf(tszTemp, 15, lpFmt, m_digest[i]);
			_tcscat(tszReport, tszTemp);
		}
	}
	else if(rtReportType == REPORT_DIGIT)
	{
		_sntprintf(tszTemp, 15, _T("%u"), m_digest[0]);
		_tcscpy(tszReport, tszTemp);

		for(size_t i = 1; i < 20; ++i)
		{
			_sntprintf(tszTemp, 15, _T(" %u"), m_digest[i]);
			_tcscat(tszReport, tszTemp);
		}
	}
	else return false;

	return true;
}
#endif

#ifdef SHA1_STL_FUNCTIONS
bool CSHA1::ReportHashStl(std::basic_string<TCHAR>& strOut, REPORT_TYPE rtReportType) const
{
	TCHAR tszOut[84];
	const bool bResult = ReportHash(tszOut, rtReportType);
	if(bResult) strOut = tszOut;
	return bResult;
}
#endif

bool CSHA1::GetHash(UINT_8* pbDest20) const
{
	if(pbDest20 == NULL) return false;
	memcpy(pbDest20, m_digest, 20);
	return true;
}

// Get the raw message digest
// Added by Kevin to be quicker
unsigned char * CSHA1::GetHash( void ) const
{
	return ( unsigned char * ) m_digest;
}

// http://cseweb.ucsd.edu/~mihir/papers/hmac-cb.pdf
// Sample code: http://www.opensource.apple.com/source/freeradius/freeradius-11/freeradius/src/lib/hmac.c
void CSHA1::HMAC(unsigned char *sharedKey, int sharedKeyLength, unsigned char *data, int dataLength, unsigned char output[SHA1_LENGTH])
{
	// 1. Append zeros to the end of K to create a 64 byte string
	static const int sha1BlockLength=64;

	if (sharedKeyLength > sha1BlockLength)
		sharedKeyLength = sha1BlockLength;

	// ipad = the byte 0x36 repeated 64 times
	// opad = the byte 0x5C repeated 64 times
	unsigned char keyWithIpad[sha1BlockLength];
	unsigned char keyWithOpad[sha1BlockLength];

	memset( keyWithIpad, 0, sizeof(keyWithIpad));
	memset( keyWithOpad, 0, sizeof(keyWithOpad));
	memcpy( keyWithIpad, sharedKey, sharedKeyLength);
	memcpy( keyWithOpad, sharedKey, sharedKeyLength);

	for (int i = 0; i < sha1BlockLength; i++) {
		keyWithIpad[i] ^= 0x36;
		keyWithOpad[i] ^= 0x5c;
	}

	// 3. Append the data stream Text to the 64 byte string resulting from step (2)
	// 4. Apply H to the stream generated in step (3)
	CSHA1 firstHash;
	firstHash.Reset();
	firstHash.Update( keyWithIpad, sha1BlockLength );
	firstHash.Update( data, dataLength );
	firstHash.Final();

	// 6. Append the H (hash) result from step (4) to the 64 byte string resulting from step (5)
	// 7. Apply H to the stream generated in step (6) and output the result
	CSHA1 secondHash;
	secondHash.Reset();
	secondHash.Update( keyWithOpad, sha1BlockLength );
	secondHash.Update( firstHash.GetHash(), SHA1_LENGTH );
	secondHash.Final();

	memcpy(output, secondHash.GetHash(), SHA1_LENGTH);

	// 	char report[128];
	// 	memset(report,0,128);
	// 	secondHash.ReportHash( report, 0 );
}
