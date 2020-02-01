/*
 *  Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code is licensed under the MIT-style license found in the
 *  license.txt file in the root directory of this source tree.
 *
 *
 *  This file defines adapters for all MS-specific functions used throughout SLikeNet.
 */

#include "slikenet/linux_adapter.h"

#ifdef SPRINTFS_FUNCTION_MISSING

#include <algorithm>	// for std::max, std::min
#include <cerrno>		// for errno
#include <cstdio>		// for FILE, fopen, vsnprintf
#include <cstdlib>		// for mbstowcs
#include <cstring>		// for strcat, strcpy, strncat, strncpy
#include <cstdarg>		// for va_start, va_end, va_list
#include <ctime>		// for localtime, time_t
#include <cwchar>		// for wcscat, wcscpy, wcslen

errno_t fopen_s(FILE **pfile, const char *filename, const char *mode)
{
	if ((pfile == nullptr) || (filename == nullptr) || (mode == nullptr)) {
		return 22; // error: EINVAL
	}

	FILE *file = fopen(filename, mode);
	if (file == nullptr) {
		return errno;
	}

	*pfile = file;
	return 0;
}

errno_t localtime_s(struct tm *_tm, const time_t *time)
{
	// #med - should actually also check for _*time > _MAX_TIME64_T according to MSDN, but can't seem to find the
	// definition of _MAX_TIME64_T
	if ((_tm == nullptr) || (time == nullptr) || (*time == 0)) {
		if (_tm != nullptr) {
			_tm->tm_hour  = -1;
			_tm->tm_isdst = -1;
			_tm->tm_mday  = -1;
			_tm->tm_min   = -1;
			_tm->tm_mon   = -1;
			_tm->tm_sec   = -1;
			_tm->tm_wday  = -1;
			_tm->tm_yday  = -1;
			_tm->tm_year  = -1;
		}
		return 22; // error: EINVAL
	}

	struct tm *curTime = localtime(time);
	*_tm = *curTime;

	return 0;
}

errno_t mbstowcs_s(size_t *pReturnValue, wchar_t *wcstr, size_t sizeInWords, const char *mbstr, size_t count)
{
	if ((mbstr == nullptr) || ((wcstr == nullptr) && (sizeInWords > 0)) || ((wcstr != nullptr) && (sizeInWords != 0))) {
		if (wcstr != nullptr) {
			wcstr[0] = L'\0'; // ensure 0-termination
		}
		return 22; // error: EINVAL
	}

	size_t numMaxChars = sizeInWords;
	if (count != _TRUNCATE) {
		numMaxChars = std::min(numMaxChars, count);
	}

	size_t numCharsWritten = mbstowcs(wcstr, mbstr, numMaxChars);
	if (numCharsWritten == (size_t)-1) {
		// invalid multibyte character encountered
		if (pReturnValue != nullptr) {
			*pReturnValue = 0;
		}
		if (wcstr != nullptr) {
			wcstr[0] = L'\0'; // ensure 0-termination
		}
		return 42; // error: EILSEQ
	}

	if (numCharsWritten == numMaxChars) {
		if (wcstr != nullptr) {
			wcstr[0] = L'\0'; // ensure 0-termination
		}
		return 34; // error: ERANGE
	}

	if (pReturnValue != nullptr) {
		*pReturnValue = numCharsWritten + 1; // chars written, including terminating null character
	}

	// ensure we write a terminating null character (in case there was none in the original converted string)
	if (wcstr != nullptr) {
		wcstr[numCharsWritten] = L'\0'; // ensure 0-termination
	}

	return 0;
}

int sprintf_s(char *buffer, size_t sizeOfBuffer, const char *format, ...)
{
	if ((buffer == nullptr) || (sizeOfBuffer == 0) || (format == nullptr)) {
		return -1;
	}

	va_list arglist;
	va_start(arglist, format);
	int numCharsWritten = vsnprintf(buffer, sizeOfBuffer, format, arglist);
	va_end(arglist);

	if (numCharsWritten == -1) {
		buffer[0] = '\0'; // error occurred ensure terminating \0-character
		return -1;
	}

	if (numCharsWritten >= sizeOfBuffer) {
		buffer[0] = '\0'; // buffer too small, write empty string to ensure terminating \0-char
	}

	return numCharsWritten;
}

errno_t strcat_s(char *strDestination, size_t numberOfElements, const char *strSource)
{
	if ((strDestination == nullptr) || (strSource == nullptr)) {
		if (strDestination != nullptr) {
			strDestination[0] = '\0'; // ensure trailing \0 is written
		}
		return 22; // error: EINVAL
	}

	if (numberOfElements == 0) {
		strDestination[0] = '\0'; // ensure trailing \0 is written
		return 34; // error: ERANGE
	}

	const size_t destLen = strlen(strDestination);
	const size_t sourceLen = strlen(strSource);
	if ((destLen > numberOfElements - 1) || ((sourceLen > 0) && (destLen == numberOfElements - 1)) || (sourceLen > numberOfElements - destLen - 1)) {
		strDestination[0] = '\0'; // ensure trailing \0 is written
		return 34; // error: ERANGE
	}

	(void)strcat(strDestination, strSource);
	return 0;
}

errno_t strcpy_s(char* strDestination, size_t numberOfElements, const char *strSource)
{
	if ((strDestination == nullptr) || (strSource == nullptr)) {
		if (strDestination != nullptr) {
			strDestination[0] = '\0'; // ensure trailing \0 is written
		}
		return 22; // error: EINVAL
	}

	if ((numberOfElements == 0) || (strlen(strSource) >= numberOfElements)) {
		strDestination[0] = '\0'; // ensure trailing \0 is written
		return 34; // error: ERANGE
	}

	(void)strcpy(strDestination, strSource);
	return 0;
}

errno_t strncat_s(char *strDest, size_t numberOfElements, const char *strSource, size_t count)
{
	// check valid parameters
	if ((strDest == nullptr) || (strSource == nullptr)) {
		return 22; // error: EINVAL
	}

	if (numberOfElements == 0) {
		return 34; // error: ERANGE
	}

	size_t charsToWrite;
	const size_t sourceLen = strlen(strSource);
	if (count == _TRUNCATE) {
		charsToWrite = sourceLen;
	}
	else {
		charsToWrite = std::min(count, sourceLen);
	}

	const size_t destLen = strlen(strDest);
	const size_t sizeLeft = numberOfElements - destLen;

	if (((count != _TRUNCATE) && (charsToWrite > sizeLeft - 1)) || ((sourceLen > 0) && (destLen == numberOfElements - 1))) {
		strDest[0] = '\0'; // ensure trailing \0 is written
		return 34; // error: ERANGE
	}

	(void)strncat(strDest, strSource, charsToWrite);
	return 0;
}

errno_t strncpy_s(char *strDest, size_t numberOfElements, const char *strSource, size_t count)
{
	// check valid parameters
	if ((numberOfElements == 0) || (strDest == nullptr) || (strSource == nullptr)) {
		if (strDest != nullptr) {
			strDest[0] = '\0'; // ensure trailing \0 is written
		}
		return 22; // error: EINVAL
	}

	size_t numChars;
	bool truncated = false;
	if (count == _TRUNCATE) {
		// if count == _TRUNCATE use the length of the source string
		numChars = strlen(strSource);

		// ensure we are not exceeding numberOfElements
		if (numChars >= numberOfElements) {
			numChars = numberOfElements - 1;
			truncated = true; // we are going to truncate the copied string
		}
	}
	else {
		// otherwise we use count, but have to check that the destination buffer is of sufficient size
		if ((count > numberOfElements) || ((count == numberOfElements) && (strSource[count] != '\0'))) {
			strDest[0] = '\0'; // ensure trailing \0 is written
			return 34; // error: ERANGE
		}
		numChars = count;
	}

	(void)strncpy(strDest, strSource, numChars);

	// enforce the trailing \0
	strDest[numChars] = '\0';

	return truncated ? 80 : 0; // STRUNCATE, if we truncated the string, 0 otherwise
}

errno_t wcscat_s(wchar_t *strDestination, size_t numberOfElements, const wchar_t *strSource)
{
	if ((strDestination == nullptr) || (strSource == nullptr)) {
		if (strDestination != nullptr) {
			strDestination[0] = L'\0'; // ensure trailing \0 is written
		}
		return 22; // error: EINVAL
	}

	if (numberOfElements == 0) {
		strDestination[0] = L'\0'; // ensure trailing \0 is written
		return 34; // error: ERANGE
	}

	const size_t destLen = wcslen(strDestination);
	const size_t sourceLen = wcslen(strSource);
	if ((destLen > numberOfElements - 1) || ((sourceLen > 0) && (destLen == numberOfElements)) || (sourceLen > numberOfElements - destLen - 1)) {
		strDestination[0] = L'\0'; // ensure trailing \0 is written
		return 34; // error: ERANGE
	}

	(void)wcscat(strDestination, strSource);
	return 0;
}

errno_t wcscpy_s(wchar_t* strDestination, size_t numberOfElements, const wchar_t *strSource)
{
	if ((strDestination == nullptr) || (strSource == nullptr)) {
		if (strDestination != nullptr) {
			strDestination[0] = L'\0'; // ensure trailing \0 is written
		}
		return 22; // error: EINVAL
	}

	if ((numberOfElements == 0) || (wcslen(strSource) >= numberOfElements)) {
		strDestination[0] = L'\0'; // ensure trailing \0 is written
		return 34; // error: ERANGE
	}

	(void)wcscpy(strDestination, strSource);
	return 0;
}

#endif

#ifdef VSNPRINTFS_FUNCTION_MISSING
int vsnprintf_s(char *buffer, size_t sizeOfBuffer, size_t count, const char *format, va_list argptr)
{
	if ((buffer == nullptr) || (format == nullptr) || (sizeOfBuffer == 0)) {
		return -1;
	}

	size_t maxChars = sizeOfBuffer;
	if (count != _TRUNCATE) {
		if (count >= sizeOfBuffer) {
			buffer[0] = '\0'; // ensure trailing \0 is written
			return -1;
		}
		maxChars = count;
	}

	int numCharsWritten = vsnprintf(buffer, maxChars, format, argptr);
	if (numCharsWritten >= maxChars) {
		if (count != _TRUNCATE) {
			buffer[0] = '\0'; // buffer set to empty string
			return -1;
		}

		// truncation occurred, add terminating \0
		buffer[sizeOfBuffer] = '\0';
	}

	return numCharsWritten;
}
#endif

#ifdef INET_FUNCTIONS_MISSING
#include <cstdarg>  // for va_start, va_end, va_list
#include <cstdio>   // for FILE
#include <ctime>    // for time_t
#include <stdint.h>
#include "winsock2.h"
#include "ws2tcpip.h"


#define NS_INADDRSZ  4
#define NS_IN6ADDRSZ 16
#define NS_INT16SZ   2
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size)
{
  struct sockaddr_storage ss;
  unsigned long s = size;

  ZeroMemory(&ss, sizeof(ss));
  ss.ss_family = af;

  switch(af) {
    case AF_INET:
      ((struct sockaddr_in *)&ss)->sin_addr = *(struct in_addr *)src;
      break;
    case AF_INET6:
      ((struct sockaddr_in6 *)&ss)->sin6_addr = *(struct in6_addr *)src;
      break;
    default:
      return NULL;
  }
  /* cannot direclty use &size because of strict aliasing rules */
  return (WSAAddressToString((struct sockaddr *)&ss, sizeof(ss), NULL, dst, &s) == 0)?
          dst : NULL;
}

int inet_pton4(const char *src, char *dst)
{
    uint8_t tmp[NS_INADDRSZ], *tp;

    int saw_digit = 0;
    int octets = 0;
    *(tp = tmp) = 0;

    int ch;
    while ((ch = *src++) != '\0')
    {
        if (ch >= '0' && ch <= '9')
        {
            uint32_t n = *tp * 10 + (ch - '0');

            if (saw_digit && *tp == 0)
                return 0;

            if (n > 255)
                return 0;

            *tp = n;
            if (!saw_digit)
            {
                if (++octets > 4)
                    return 0;
                saw_digit = 1;
            }
        }
        else if (ch == '.' && saw_digit)
        {
            if (octets == 4)
                return 0;
            *++tp = 0;
            saw_digit = 0;
        }
        else
            return 0;
    }
    if (octets < 4)
        return 0;

    memcpy(dst, tmp, NS_INADDRSZ);

    return 1;
}

int inet_pton6(const char *src, char *dst)
{
    static const char xdigits[] = "0123456789abcdef";
    uint8_t tmp[NS_IN6ADDRSZ];

    uint8_t *tp = (uint8_t*) memset(tmp, '\0', NS_IN6ADDRSZ);
    uint8_t *endp = tp + NS_IN6ADDRSZ;
    uint8_t *colonp = NULL;

    /* Leading :: requires some special handling. */
    if (*src == ':')
    {
        if (*++src != ':')
            return 0;
    }

    const char *curtok = src;
    int saw_xdigit = 0;
    uint32_t val = 0;
    int ch;
    while ((ch = tolower(*src++)) != '\0')
    {
        const char *pch = strchr(xdigits, ch);
        if (pch != NULL)
        {
            val <<= 4;
            val |= (pch - xdigits);
            if (val > 0xffff)
                return 0;
            saw_xdigit = 1;
            continue;
        }
        if (ch == ':')
        {
            curtok = src;
            if (!saw_xdigit)
            {
                if (colonp)
                    return 0;
                colonp = tp;
                continue;
            }
            else if (*src == '\0')
            {
                return 0;
            }
            if (tp + NS_INT16SZ > endp)
                return 0;
            *tp++ = (uint8_t) (val >> 8) & 0xff;
            *tp++ = (uint8_t) val & 0xff;
            saw_xdigit = 0;
            val = 0;
            continue;
        }
        if (ch == '.' && ((tp + NS_INADDRSZ) <= endp) &&
                inet_pton4(curtok, (char*) tp) > 0)
        {
            tp += NS_INADDRSZ;
            saw_xdigit = 0;
            break; /* '\0' was seen by inet_pton4(). */
        }
        return 0;
    }
    if (saw_xdigit)
    {
        if (tp + NS_INT16SZ > endp)
            return 0;
        *tp++ = (uint8_t) (val >> 8) & 0xff;
        *tp++ = (uint8_t) val & 0xff;
    }
    if (colonp != NULL)
    {
        /*
         * Since some memmove()'s erroneously fail to handle
         * overlapping regions, we'll do the shift by hand.
         */
        const int n = tp - colonp;

        if (tp == endp)
            return 0;

        for (int i = 1; i <= n; i++)
        {
            endp[-i] = colonp[n - i];
            colonp[n - i] = 0;
        }
        tp = endp;
    }
    if (tp != endp)
        return 0;

    memcpy(dst, tmp, NS_IN6ADDRSZ);

    return 1;
}

int inet_pton(int af, const char *src, unsigned long *dst)
{
 if (af == AF_INET) {
     char tmp[NS_INADDRSZ];
     int returnValue = inet_pton4(src, tmp);
        memcpy(dst, tmp, NS_INADDRSZ);
        return returnValue;
 } else if (af == AF_INET6) {
     char tmp[NS_IN6ADDRSZ];
     int returnValue = inet_pton6(src, tmp);
        memcpy(dst, tmp, NS_IN6ADDRSZ);
        return returnValue;
 }

 return -1;
}
#endif

#ifdef __ANDROID__
/*
Copyright (c) 2013, Kenneth MacKay
All rights reserved.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <net/if_arp.h>
#include <netinet/in.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

typedef struct NetlinkList
{
	struct NetlinkList *m_next;
	struct nlmsghdr *m_data;
	unsigned int m_size;
} NetlinkList;

static int netlink_socket(void)
{
	int l_socket = socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	if(l_socket < 0)
	{
		return -1;
	}

	struct sockaddr_nl l_addr;
	memset(&l_addr, 0, sizeof(l_addr));
	l_addr.nl_family = AF_NETLINK;
	if(bind(l_socket, (struct sockaddr *)&l_addr, sizeof(l_addr)) < 0)
	{
		close(l_socket);
		return -1;
	}

	return l_socket;
}

static int netlink_send(int p_socket, int p_request)
{
	char l_buffer[NLMSG_ALIGN(sizeof(struct nlmsghdr)) + NLMSG_ALIGN(sizeof(struct rtgenmsg))];
	memset(l_buffer, 0, sizeof(l_buffer));
	struct nlmsghdr *l_hdr = (struct nlmsghdr *)l_buffer;
	struct rtgenmsg *l_msg = (struct rtgenmsg *)NLMSG_DATA(l_hdr);

	l_hdr->nlmsg_len = NLMSG_LENGTH(sizeof(*l_msg));
	l_hdr->nlmsg_type = p_request;
	l_hdr->nlmsg_flags = NLM_F_ROOT | NLM_F_MATCH | NLM_F_REQUEST;
	l_hdr->nlmsg_pid = 0;
	l_hdr->nlmsg_seq = p_socket;
	l_msg->rtgen_family = AF_UNSPEC;

	struct sockaddr_nl l_addr;
	memset(&l_addr, 0, sizeof(l_addr));
	l_addr.nl_family = AF_NETLINK;
	return (sendto(p_socket, l_hdr, l_hdr->nlmsg_len, 0, (struct sockaddr *)&l_addr, sizeof(l_addr)));
}

static int netlink_recv(int p_socket, void *p_buffer, size_t p_len)
{
	struct msghdr l_msg;
	struct iovec l_iov = { p_buffer, p_len };
	struct sockaddr_nl l_addr;
	int l_result;

	for(;;)
	{
		l_msg.msg_name = (void *)&l_addr;
		l_msg.msg_namelen = sizeof(l_addr);
		l_msg.msg_iov = &l_iov;
		l_msg.msg_iovlen = 1;
		l_msg.msg_control = NULL;
		l_msg.msg_controllen = 0;
		l_msg.msg_flags = 0;
		int l_result = recvmsg(p_socket, &l_msg, 0);

		if(l_result < 0)
		{
			if(errno == EINTR)
			{
				continue;
			}
			return -2;
		}

		if(l_msg.msg_flags & MSG_TRUNC)
		{ // buffer was too small
			return -1;
		}
		return l_result;
	}
}

static struct nlmsghdr *getNetlinkResponse(int p_socket, int *p_size, int *p_done)
{
	size_t l_size = 4096;
	void *l_buffer = NULL;

	for(;;)
	{
		free(l_buffer);
		l_buffer = malloc(l_size);

		int l_read = netlink_recv(p_socket, l_buffer, l_size);
		*p_size = l_read;
		if(l_read == -2)
		{
			free(l_buffer);
			return NULL;
		}
		if(l_read >= 0)
		{
			pid_t l_pid = getpid();
			struct nlmsghdr *l_hdr;
			for(l_hdr = (struct nlmsghdr *)l_buffer; NLMSG_OK(l_hdr, (unsigned int)l_read); l_hdr = (struct nlmsghdr *)NLMSG_NEXT(l_hdr, l_read))
			{
				if((pid_t)l_hdr->nlmsg_pid != l_pid || (int)l_hdr->nlmsg_seq != p_socket)
				{
					continue;
				}

				if(l_hdr->nlmsg_type == NLMSG_DONE)
				{
					*p_done = 1;
					break;
				}

				if(l_hdr->nlmsg_type == NLMSG_ERROR)
				{
					free(l_buffer);
					return NULL;
				}
			}
			return (nlmsghdr*)l_buffer;
		}

		l_size *= 2;
	}
}

static NetlinkList *newListItem(struct nlmsghdr *p_data, unsigned int p_size)
{
	NetlinkList *l_item = (NetlinkList*)malloc(sizeof(NetlinkList));
	l_item->m_next = NULL;
	l_item->m_data = p_data;
	l_item->m_size = p_size;
	return l_item;
}

static void freeResultList(NetlinkList *p_list)
{
	NetlinkList *l_cur;
	while(p_list)
	{
		l_cur = p_list;
		p_list = p_list->m_next;
		free(l_cur->m_data);
		free(l_cur);
	}
}

static NetlinkList *getResultList(int p_socket, int p_request)
{
	if(netlink_send(p_socket, p_request) < 0)
	{
		return NULL;
	}

	NetlinkList *l_list = NULL;
	NetlinkList *l_end = NULL;
	int l_size;
	int l_done = 0;
	while(!l_done)
	{
		struct nlmsghdr *l_hdr = getNetlinkResponse(p_socket, &l_size, &l_done);
		if(!l_hdr)
		{ // error
			freeResultList(l_list);
			return NULL;
		}

		NetlinkList *l_item = newListItem(l_hdr, l_size);
		if(!l_list)
		{
			l_list = l_item;
		}
		else
		{
			l_end->m_next = l_item;
		}
		l_end = l_item;
	}
	return l_list;
}

static size_t maxSize(size_t a, size_t b)
{
	return (a > b ? a : b);
}

static size_t calcAddrLen(sa_family_t p_family, int p_dataSize)
{
	switch(p_family)
	{
		case AF_INET:
			return sizeof(struct sockaddr_in);
		case AF_INET6:
			return sizeof(struct sockaddr_in6);
		case AF_PACKET:
			return maxSize(sizeof(struct sockaddr_ll), offsetof(struct sockaddr_ll, sll_addr) + p_dataSize);
		default:
			return maxSize(sizeof(struct sockaddr), offsetof(struct sockaddr, sa_data) + p_dataSize);
	}
}

static void makeSockaddr(sa_family_t p_family, struct sockaddr *p_dest, void *p_data, size_t p_size)
{
	switch(p_family)
	{
		case AF_INET:
			memcpy(&((struct sockaddr_in*)p_dest)->sin_addr, p_data, p_size);
			break;
		case AF_INET6:
			memcpy(&((struct sockaddr_in6*)p_dest)->sin6_addr, p_data, p_size);
			break;
		case AF_PACKET:
			memcpy(((struct sockaddr_ll*)p_dest)->sll_addr, p_data, p_size);
			((struct sockaddr_ll*)p_dest)->sll_halen = p_size;
			break;
		default:
			memcpy(p_dest->sa_data, p_data, p_size);
			break;
	}
	p_dest->sa_family = p_family;
}

static void addToEnd(struct ifaddrs **p_resultList, struct ifaddrs *p_entry)
{
	if(!*p_resultList)
	{
		*p_resultList = p_entry;
	}
	else
	{
		struct ifaddrs *l_cur = *p_resultList;
		while(l_cur->ifa_next)
		{
			l_cur = l_cur->ifa_next;
		}
		l_cur->ifa_next = p_entry;
	}
}

static void interpretLink(struct nlmsghdr *p_hdr, struct ifaddrs **p_links, struct ifaddrs **p_resultList)
{
	struct ifinfomsg *l_info = (struct ifinfomsg *)NLMSG_DATA(p_hdr);

	size_t l_nameSize = 0;
	size_t l_addrSize = 0;
	size_t l_dataSize = 0;

	size_t l_rtaSize = NLMSG_PAYLOAD(p_hdr, sizeof(struct ifinfomsg));
	struct rtattr *l_rta;
	for(l_rta = (struct rtattr *)(((char *)l_info) + NLMSG_ALIGN(sizeof(struct ifinfomsg))); RTA_OK(l_rta, l_rtaSize); l_rta = RTA_NEXT(l_rta, l_rtaSize))
	{
		void *l_rtaData = RTA_DATA(l_rta);
		size_t l_rtaDataSize = RTA_PAYLOAD(l_rta);
		switch(l_rta->rta_type)
		{
			case IFLA_ADDRESS:
			case IFLA_BROADCAST:
				l_addrSize += NLMSG_ALIGN(calcAddrLen(AF_PACKET, l_rtaDataSize));
				break;
			case IFLA_IFNAME:
				l_nameSize += NLMSG_ALIGN(l_rtaSize + 1);
				break;
			case IFLA_STATS:
				l_dataSize += NLMSG_ALIGN(l_rtaSize);
				break;
			default:
				break;
		}
	}

	struct ifaddrs *l_entry = (ifaddrs*)malloc(sizeof(struct ifaddrs) + l_nameSize + l_addrSize + l_dataSize);
	memset(l_entry, 0, sizeof(struct ifaddrs));
	l_entry->ifa_name = nullptr;

	char *l_name = ((char *)l_entry) + sizeof(struct ifaddrs);
	char *l_addr = l_name + l_nameSize;
	char *l_data = l_addr + l_addrSize;

	l_entry->ifa_flags = l_info->ifi_flags;

	l_rtaSize = NLMSG_PAYLOAD(p_hdr, sizeof(struct ifinfomsg));
	for(l_rta = (struct rtattr *)(((char *)l_info) + NLMSG_ALIGN(sizeof(struct ifinfomsg))); RTA_OK(l_rta, l_rtaSize); l_rta = RTA_NEXT(l_rta, l_rtaSize))
	{
		void *l_rtaData = RTA_DATA(l_rta);
		size_t l_rtaDataSize = RTA_PAYLOAD(l_rta);
		switch(l_rta->rta_type)
		{
			case IFLA_ADDRESS:
			case IFLA_BROADCAST:
			{
				size_t l_addrLen = calcAddrLen(AF_PACKET, l_rtaDataSize);
				makeSockaddr(AF_PACKET, (struct sockaddr *)l_addr, l_rtaData, l_rtaDataSize);
				((struct sockaddr_ll *)l_addr)->sll_ifindex = l_info->ifi_index;
				((struct sockaddr_ll *)l_addr)->sll_hatype = l_info->ifi_type;
				if(l_rta->rta_type == IFLA_ADDRESS)
				{
					l_entry->ifa_addr = (struct sockaddr *)l_addr;
				}
				else
				{
					l_entry->ifa_broadaddr = (struct sockaddr *)l_addr;
				}
				l_addr += NLMSG_ALIGN(l_addrLen);
				break;
			}
			case IFLA_IFNAME:
				strncpy(l_name, (char*)l_rtaData, l_rtaDataSize);
				l_name[l_rtaDataSize] = '\0';
				l_entry->ifa_name = l_name;
				break;
			case IFLA_STATS:
				memcpy(l_data, l_rtaData, l_rtaDataSize);
				l_entry->ifa_data = l_data;
				break;
			default:
				break;
		}
	}

	addToEnd(p_resultList, l_entry);
	p_links[l_info->ifi_index - 1] = l_entry;
}

static void interpretAddr(struct nlmsghdr *p_hdr, struct ifaddrs **p_links, struct ifaddrs **p_resultList)
{
	struct ifaddrmsg *l_info = (struct ifaddrmsg *)NLMSG_DATA(p_hdr);

	size_t l_nameSize = 0;
	size_t l_addrSize = 0;

	int l_addedNetmask = 0;

	size_t l_rtaSize = NLMSG_PAYLOAD(p_hdr, sizeof(struct ifaddrmsg));
	struct rtattr *l_rta;
	for(l_rta = (struct rtattr *)(((char *)l_info) + NLMSG_ALIGN(sizeof(struct ifaddrmsg))); RTA_OK(l_rta, l_rtaSize); l_rta = RTA_NEXT(l_rta, l_rtaSize))
	{
		void *l_rtaData = RTA_DATA(l_rta);
		size_t l_rtaDataSize = RTA_PAYLOAD(l_rta);
		if(l_info->ifa_family == AF_PACKET)
		{
			continue;
		}

		switch(l_rta->rta_type)
		{
			case IFA_ADDRESS:
			case IFA_LOCAL:
				if((l_info->ifa_family == AF_INET || l_info->ifa_family == AF_INET6) && !l_addedNetmask)
				{ // make room for netmask
					l_addrSize += NLMSG_ALIGN(calcAddrLen(l_info->ifa_family, l_rtaDataSize));
					l_addedNetmask = 1;
				}
			case IFA_BROADCAST:
				l_addrSize += NLMSG_ALIGN(calcAddrLen(l_info->ifa_family, l_rtaDataSize));
				break;
			case IFA_LABEL:
				l_nameSize += NLMSG_ALIGN(l_rtaSize + 1);
				break;
			default:
				break;
		}
	}

	struct ifaddrs *l_entry = (ifaddrs*)malloc(sizeof(struct ifaddrs) + l_nameSize + l_addrSize);
	memset(l_entry, 0, sizeof(struct ifaddrs));
	l_entry->ifa_name = p_links[l_info->ifa_index - 1]->ifa_name;

	char *l_name = ((char *)l_entry) + sizeof(struct ifaddrs);
	char *l_addr = l_name + l_nameSize;

	l_entry->ifa_flags = l_info->ifa_flags | p_links[l_info->ifa_index - 1]->ifa_flags;

	l_rtaSize = NLMSG_PAYLOAD(p_hdr, sizeof(struct ifaddrmsg));
	for(l_rta = (struct rtattr *)(((char *)l_info) + NLMSG_ALIGN(sizeof(struct ifaddrmsg))); RTA_OK(l_rta, l_rtaSize); l_rta = RTA_NEXT(l_rta, l_rtaSize))
	{
		void *l_rtaData = RTA_DATA(l_rta);
		size_t l_rtaDataSize = RTA_PAYLOAD(l_rta);
		switch(l_rta->rta_type)
		{
			case IFA_ADDRESS:
			case IFA_BROADCAST:
			case IFA_LOCAL:
			{
				size_t l_addrLen = calcAddrLen(l_info->ifa_family, l_rtaDataSize);
				makeSockaddr(l_info->ifa_family, (struct sockaddr *)l_addr, l_rtaData, l_rtaDataSize);
				if(l_info->ifa_family == AF_INET6)
				{
					if(IN6_IS_ADDR_LINKLOCAL((struct in6_addr *)l_rtaData) || IN6_IS_ADDR_MC_LINKLOCAL((struct in6_addr *)l_rtaData))
					{
						((struct sockaddr_in6 *)l_addr)->sin6_scope_id = l_info->ifa_index;
					}
				}

				if(l_rta->rta_type == IFA_ADDRESS)
				{ // apparently in a point-to-point network IFA_ADDRESS contains the dest address and IFA_LOCAL contains the local address
					if(l_entry->ifa_addr)
					{
						l_entry->ifa_dstaddr = (struct sockaddr *)l_addr;
					}
					else
					{
						l_entry->ifa_addr = (struct sockaddr *)l_addr;
					}
				}
				else if(l_rta->rta_type == IFA_LOCAL)
				{
					if(l_entry->ifa_addr)
					{
						l_entry->ifa_dstaddr = l_entry->ifa_addr;
					}
					l_entry->ifa_addr = (struct sockaddr *)l_addr;
				}
				else
				{
					l_entry->ifa_broadaddr = (struct sockaddr *)l_addr;
				}
				l_addr += NLMSG_ALIGN(l_addrLen);
				break;
			}
			case IFA_LABEL:
				strncpy(l_name, (char*)l_rtaData, l_rtaDataSize);
				l_name[l_rtaDataSize] = '\0';
				l_entry->ifa_name = l_name;
				break;
			default:
				break;
		}
	}

	if(l_entry->ifa_addr && (l_entry->ifa_addr->sa_family == AF_INET || l_entry->ifa_addr->sa_family == AF_INET6))
	{
		unsigned l_maxPrefix = (l_entry->ifa_addr->sa_family == AF_INET ? 32 : 128);
		unsigned l_prefix = (l_info->ifa_prefixlen > l_maxPrefix ? l_maxPrefix : l_info->ifa_prefixlen);
		char l_mask[16] = {0};
		unsigned i;
		for(i=0; i<(l_prefix/8); ++i)
		{
			l_mask[i] = 0xff;
		}

		// Avoid stack check fail on android device, reference https://github.com/libuv/libuv/blob/e4087dedf837f415056a45a838f639a3d9dc3ced/src/unix/android-ifaddrs.c
		if (l_prefix % 8)
		{
			l_mask[i] = 0xff << (8 - (l_prefix % 8));
		}

		makeSockaddr(l_entry->ifa_addr->sa_family, (struct sockaddr *)l_addr, l_mask, l_maxPrefix / 8);
		l_entry->ifa_netmask = (struct sockaddr *)l_addr;
	}

	addToEnd(p_resultList, l_entry);
}

static void interpret(int p_socket, NetlinkList *p_netlinkList, struct ifaddrs **p_links, struct ifaddrs **p_resultList)
{
	pid_t l_pid = getpid();
	for(; p_netlinkList; p_netlinkList = p_netlinkList->m_next)
	{
		unsigned int l_nlsize = p_netlinkList->m_size;
		struct nlmsghdr *l_hdr;
		for(l_hdr = p_netlinkList->m_data; NLMSG_OK(l_hdr, l_nlsize); l_hdr = NLMSG_NEXT(l_hdr, l_nlsize))
		{
			if((pid_t)l_hdr->nlmsg_pid != l_pid || (int)l_hdr->nlmsg_seq != p_socket)
			{
				continue;
			}

			if(l_hdr->nlmsg_type == NLMSG_DONE)
			{
				break;
			}

			if(l_hdr->nlmsg_type == RTM_NEWLINK)
			{
				interpretLink(l_hdr, p_links, p_resultList);
			}
			else if(l_hdr->nlmsg_type == RTM_NEWADDR)
			{
				interpretAddr(l_hdr, p_links, p_resultList);
			}
		}
	}
}

static unsigned countLinks(int p_socket, NetlinkList *p_netlinkList)
{
	unsigned l_links = 0;
	pid_t l_pid = getpid();
	for(; p_netlinkList; p_netlinkList = p_netlinkList->m_next)
	{
		unsigned int l_nlsize = p_netlinkList->m_size;
		struct nlmsghdr *l_hdr;
		for(l_hdr = p_netlinkList->m_data; NLMSG_OK(l_hdr, l_nlsize); l_hdr = NLMSG_NEXT(l_hdr, l_nlsize))
		{
			if((pid_t)l_hdr->nlmsg_pid != l_pid || (int)l_hdr->nlmsg_seq != p_socket)
			{
				continue;
			}

			if(l_hdr->nlmsg_type == NLMSG_DONE)
			{
				break;
			}

			if(l_hdr->nlmsg_type == RTM_NEWLINK)
			{
				++l_links;
			}
		}
	}

	return l_links;
}

int getifaddrs(struct ifaddrs **ifap)
{
	if(!ifap)
	{
		return -1;
	}
	*ifap = NULL;

	int l_socket = netlink_socket();
	if(l_socket < 0)
	{
		return -1;
	}

	NetlinkList *l_linkResults = getResultList(l_socket, RTM_GETLINK);
	if(!l_linkResults)
	{
		close(l_socket);
		return -1;
	}

	NetlinkList *l_addrResults = getResultList(l_socket, RTM_GETADDR);
	if(!l_addrResults)
	{
		close(l_socket);
		freeResultList(l_linkResults);
		return -1;
	}

	unsigned l_numLinks = countLinks(l_socket, l_linkResults) + countLinks(l_socket, l_addrResults);
	struct ifaddrs *l_links[l_numLinks];
	memset(l_links, 0, l_numLinks * sizeof(struct ifaddrs *));

	interpret(l_socket, l_linkResults, l_links, ifap);
	interpret(l_socket, l_addrResults, l_links, ifap);

	freeResultList(l_linkResults);
	freeResultList(l_addrResults);
	close(l_socket);
	return 0;
}

void freeifaddrs(struct ifaddrs *ifa)
{
	struct ifaddrs *l_cur;
	while(ifa)
	{
		l_cur = ifa;
		ifa = ifa->ifa_next;
		free(l_cur);
	}
}

#endif
