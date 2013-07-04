/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

// Modified by Lasse Oorni for Urho3D

#include "SDL_config.h"

/* This file contains portable string manipulation functions for SDL */

#include "SDL_stdinc.h"

/* these are always #defined, make them real symbol in the library, too... */
#undef SDL_itoa
#undef SDL_uitoa
#undef SDL_atoi
#undef SDL_atof
char *SDL_itoa(int value, char *str, int radix) { return SDL_itoa_inline(value, str, radix); }
char *SDL_uitoa(unsigned int value, char *str, int radix) { return SDL_uitoa_inline(value, str, radix); }
int SDL_atoi(const char *str) { return SDL_atoi_inline(str); }
double SDL_atof(const char *str) { return SDL_atof_inline(str); }



#define SDL_isupperhex(X)   (((X) >= 'A') && ((X) <= 'F'))
#define SDL_islowerhex(X)   (((X) >= 'a') && ((X) <= 'f'))

#define UTF8_IsLeadByte(c) ((c) >= 0xC0 && (c) <= 0xF4)
#define UTF8_IsTrailingByte(c) ((c) >= 0x80 && (c) <= 0xBF)

static int UTF8_TrailingBytes(unsigned char c)
{
    if (c >= 0xC0 && c <= 0xDF)
        return 1;
    else if (c >= 0xE0 && c <= 0xEF)
        return 2;
    else if (c >= 0xF0 && c <= 0xF4)
        return 3;
    else
        return 0;
}

#if !defined(SDL_sscanf) || !defined(SDL_strtol)
static size_t
SDL_ScanLong(const char *text, int radix, long *valuep)
{
    const char *textstart = text;
    long value = 0;
    SDL_bool negative = SDL_FALSE;

    if (*text == '-') {
        negative = SDL_TRUE;
        ++text;
    }
    if (radix == 16 && SDL_strncmp(text, "0x", 2) == 0) {
        text += 2;
    }
    for (;;) {
        int v;
        if (SDL_isdigit((unsigned char) *text)) {
            v = *text - '0';
        } else if (radix == 16 && SDL_isupperhex(*text)) {
            v = 10 + (*text - 'A');
        } else if (radix == 16 && SDL_islowerhex(*text)) {
            v = 10 + (*text - 'a');
        } else {
            break;
        }
        value *= radix;
        value += v;
        ++text;
    }
    if (valuep) {
        if (negative && value) {
            *valuep = -value;
        } else {
            *valuep = value;
        }
    }
    return (text - textstart);
}
#endif

#if !defined(SDL_sscanf) || !defined(SDL_strtoul) || !defined(SDL_strtod)
static size_t
SDL_ScanUnsignedLong(const char *text, int radix, unsigned long *valuep)
{
    const char *textstart = text;
    unsigned long value = 0;

    if (radix == 16 && SDL_strncmp(text, "0x", 2) == 0) {
        text += 2;
    }
    for (;;) {
        int v;
        if (SDL_isdigit((unsigned char) *text)) {
            v = *text - '0';
        } else if (radix == 16 && SDL_isupperhex(*text)) {
            v = 10 + (*text - 'A');
        } else if (radix == 16 && SDL_islowerhex(*text)) {
            v = 10 + (*text - 'a');
        } else {
            break;
        }
        value *= radix;
        value += v;
        ++text;
    }
    if (valuep) {
        *valuep = value;
    }
    return (text - textstart);
}
#endif

#ifndef SDL_sscanf
static size_t
SDL_ScanUintPtrT(const char *text, int radix, uintptr_t * valuep)
{
    const char *textstart = text;
    uintptr_t value = 0;

    if (radix == 16 && SDL_strncmp(text, "0x", 2) == 0) {
        text += 2;
    }
    for (;;) {
        int v;
        if (SDL_isdigit((unsigned char) *text)) {
            v = *text - '0';
        } else if (radix == 16 && SDL_isupperhex(*text)) {
            v = 10 + (*text - 'A');
        } else if (radix == 16 && SDL_islowerhex(*text)) {
            v = 10 + (*text - 'a');
        } else {
            break;
        }
        value *= radix;
        value += v;
        ++text;
    }
    if (valuep) {
        *valuep = value;
    }
    return (text - textstart);
}
#endif

#if !defined(SDL_sscanf) || !defined(SDL_strtoll)
static size_t
SDL_ScanLongLong(const char *text, int radix, Sint64 * valuep)
{
    const char *textstart = text;
    Sint64 value = 0;
    SDL_bool negative = SDL_FALSE;

    if (*text == '-') {
        negative = SDL_TRUE;
        ++text;
    }
    if (radix == 16 && SDL_strncmp(text, "0x", 2) == 0) {
        text += 2;
    }
    for (;;) {
        int v;
        if (SDL_isdigit((unsigned char) *text)) {
            v = *text - '0';
        } else if (radix == 16 && SDL_isupperhex(*text)) {
            v = 10 + (*text - 'A');
        } else if (radix == 16 && SDL_islowerhex(*text)) {
            v = 10 + (*text - 'a');
        } else {
            break;
        }
        value *= radix;
        value += v;
        ++text;
    }
    if (valuep) {
        if (negative && value) {
            *valuep = -value;
        } else {
            *valuep = value;
        }
    }
    return (text - textstart);
}
#endif

#if !defined(SDL_sscanf) || !defined(SDL_strtoull)
static size_t
SDL_ScanUnsignedLongLong(const char *text, int radix, Uint64 * valuep)
{
    const char *textstart = text;
    Uint64 value = 0;

    if (radix == 16 && SDL_strncmp(text, "0x", 2) == 0) {
        text += 2;
    }
    for (;;) {
        int v;
        if (SDL_isdigit((unsigned char) *text)) {
            v = *text - '0';
        } else if (radix == 16 && SDL_isupperhex(*text)) {
            v = 10 + (*text - 'A');
        } else if (radix == 16 && SDL_islowerhex(*text)) {
            v = 10 + (*text - 'a');
        } else {
            break;
        }
        value *= radix;
        value += v;
        ++text;
    }
    if (valuep) {
        *valuep = value;
    }
    return (text - textstart);
}
#endif

#if !defined(SDL_sscanf) || !defined(SDL_strtod)
static size_t
SDL_ScanFloat(const char *text, double *valuep)
{
    const char *textstart = text;
    unsigned long lvalue = 0;
    double value = 0.0;
    SDL_bool negative = SDL_FALSE;

    if (*text == '-') {
        negative = SDL_TRUE;
        ++text;
    }
    text += SDL_ScanUnsignedLong(text, 10, &lvalue);
    value += lvalue;
    if (*text == '.') {
        int mult = 10;
        ++text;
        while (SDL_isdigit((unsigned char) *text)) {
            lvalue = *text - '0';
            value += (double) lvalue / mult;
            mult *= 10;
            ++text;
        }
    }
    if (valuep) {
        if (negative && value) {
            *valuep = -value;
        } else {
            *valuep = value;
        }
    }
    return (text - textstart);
}
#endif


#ifdef SDL_memset
#undef SDL_memset
void *SDL_memset(void *dst, int c, size_t len) { return SDL_memset_inline(dst, c, len); }
#else
void *
SDL_memset(void *dst, int c, size_t len)
{
    size_t left = (len % 4);
    Uint32 *dstp4;
    Uint8 *dstp1;
    Uint32 value4 = (c | (c << 8) | (c << 16) | (c << 24));
    Uint8 value1 = (Uint8) c;

    dstp4 = (Uint32 *) dst;
    len /= 4;
    while (len--) {
        *dstp4++ = value4;
    }

    dstp1 = (Uint8 *) dstp4;
    switch (left) {
    case 3:
        *dstp1++ = value1;
    case 2:
        *dstp1++ = value1;
    case 1:
        *dstp1++ = value1;
    }

    return dst;
}
#endif


#ifdef SDL_memcpy
#undef SDL_memcpy
void *SDL_memcpy(void *dst, const void *src, size_t len) { return SDL_memcpy_inline(dst, src, len); }
#else
void *
SDL_memcpy(void *dst, const void *src, size_t len)
{
#ifdef __GNUC__
    /* Presumably this is well tuned for speed.
       On my machine this is twice as fast as the C code below.
     */
    return __builtin_memcpy(dst, src, len);
#else
    /* GCC 4.9.0 with -O3 will generate movaps instructions with the loop
       using Uint32* pointers, so we need to make sure the pointers are
       aligned before we loop using them.
     */
    if (((intptr_t)src & 0x3) || ((intptr_t)dst & 0x3)) {
        /* Do an unaligned byte copy */
        Uint8 *srcp1 = (Uint8 *)src;
        Uint8 *dstp1 = (Uint8 *)dst;

        while (len--) {
            *dstp1++ = *srcp1++;
        }
    } else {
        size_t left = (len % 4);
        Uint32 *srcp4, *dstp4;
        Uint8 *srcp1, *dstp1;

        srcp4 = (Uint32 *) src;
        dstp4 = (Uint32 *) dst;
        len /= 4;
        while (len--) {
            *dstp4++ = *srcp4++;
        }

        srcp1 = (Uint8 *) srcp4;
        dstp1 = (Uint8 *) dstp4;
        switch (left) {
        case 3:
            *dstp1++ = *srcp1++;
        case 2:
            *dstp1++ = *srcp1++;
        case 1:
            *dstp1++ = *srcp1++;
        }
    }
    return dst;
#endif /* __GNUC__ */
}
#endif


#ifdef SDL_memmove
#undef SDL_memmove
void *SDL_memmove(void *dst, const void *src, size_t len) { return SDL_memmove_inline(dst, src, len); }
#else
void *
SDL_memmove(void *dst, const void *src, size_t len)
{
    char *srcp = (char *) src;
    char *dstp = (char *) dst;

    if (src < dst) {
        srcp += len - 1;
        dstp += len - 1;
        while (len--) {
            *dstp-- = *srcp--;
        }
    } else {
        while (len--) {
            *dstp++ = *srcp++;
        }
    }
    return dst;
}
#endif

#ifdef SDL_memcmp
#undef SDL_memcmp
int SDL_memcmp(const void *s1, const void *s2, size_t len) { return SDL_memcmp_inline(s1, s2, len); }
#else
int
SDL_memcmp(const void *s1, const void *s2, size_t len)
{
    char *s1p = (char *) s1;
    char *s2p = (char *) s2;
    while (len--) {
        if (*s1p != *s2p) {
            return (*s1p - *s2p);
        }
        ++s1p;
        ++s2p;
    }
    return 0;
}
#endif

#ifdef SDL_strlen
#undef SDL_strlen
size_t SDL_strlen(const char *string) { return SDL_strlen_inline(string); }
#else
size_t
SDL_strlen(const char *string)
{
    size_t len = 0;
    while (*string++) {
        ++len;
    }
    return len;
}
#endif

#ifdef SDL_wcslen
#undef SDL_wcslen
size_t SDL_wcslen(const wchar_t * string) { return SDL_wcslen_inline(string); }
#else
size_t
SDL_wcslen(const wchar_t * string)
{
    size_t len = 0;
    while (*string++) {
        ++len;
    }
    return len;
}
#endif

#ifdef SDL_wcslcpy
#undef SDL_wcslcpy
size_t SDL_wcslcpy(wchar_t *dst, const wchar_t *src, size_t maxlen) { return SDL_wcslcpy_inline(dst, src, maxlen); }
#else
size_t
SDL_wcslcpy(wchar_t *dst, const wchar_t *src, size_t maxlen)
{
    size_t srclen = SDL_wcslen(src);
    if (maxlen > 0) {
        size_t len = SDL_min(srclen, maxlen - 1);
        SDL_memcpy(dst, src, len * sizeof(wchar_t));
        dst[len] = '\0';
    }
    return srclen;
}
#endif

#ifdef SDL_wcslcat
#undef SDL_wcslcat
size_t SDL_wcslcat(wchar_t *dst, const wchar_t *src, size_t maxlen) { return SDL_wcslcat_inline(dst, src, maxlen); }
#else
size_t
SDL_wcslcat(wchar_t *dst, const wchar_t *src, size_t maxlen)
{
    size_t dstlen = SDL_wcslen(dst);
    size_t srclen = SDL_wcslen(src);
    if (dstlen < maxlen) {
        SDL_wcslcpy(dst + dstlen, src, maxlen - dstlen);
    }
    return dstlen + srclen;
}
#endif

#ifdef SDL_strlcpy
#undef SDL_strlcpy
size_t SDL_strlcpy(char *dst, const char *src, size_t maxlen) { return SDL_strlcpy_inline(dst, src, maxlen); }
#else
size_t
SDL_strlcpy(char *dst, const char *src, size_t maxlen)
{
    size_t srclen = SDL_strlen(src);
    if (maxlen > 0) {
        size_t len = SDL_min(srclen, maxlen - 1);
        SDL_memcpy(dst, src, len);
        dst[len] = '\0';
    }
    return srclen;
}
#endif

size_t SDL_utf8strlcpy(char *dst, const char *src, size_t dst_bytes)
{
    size_t src_bytes = SDL_strlen(src);
    size_t bytes = SDL_min(src_bytes, dst_bytes - 1);
    size_t i = 0;
    char trailing_bytes = 0;
    if (bytes)
    {
        unsigned char c = (unsigned char)src[bytes - 1];
        if (UTF8_IsLeadByte(c))
            --bytes;
        else if (UTF8_IsTrailingByte(c))
        {
            for (i = bytes - 1; i != 0; --i)
            {
                c = (unsigned char)src[i];
                trailing_bytes = UTF8_TrailingBytes(c);
                if (trailing_bytes)
                {
                    if (bytes - i != trailing_bytes + 1)
                        bytes = i;

                    break;
                }
            }
        }
        SDL_memcpy(dst, src, bytes);
    }
    dst[bytes] = '\0';
    return bytes;
}

#ifdef SDL_strlcat
#undef SDL_strlcat
size_t SDL_strlcat(char *dst, const char *src, size_t maxlen) { return SDL_strlcat_inline(dst, src, maxlen); }
#else
size_t
SDL_strlcat(char *dst, const char *src, size_t maxlen)
{
    size_t dstlen = SDL_strlen(dst);
    size_t srclen = SDL_strlen(src);
    if (dstlen < maxlen) {
        SDL_strlcpy(dst + dstlen, src, maxlen - dstlen);
    }
    return dstlen + srclen;
}
#endif

#ifdef SDL_strdup
#undef SDL_strdup
char *SDL_strdup(const char *string) { return SDL_strdup_inline(string); }
#else
char *
SDL_strdup(const char *string)
{
    size_t len = SDL_strlen(string) + 1;
    char *newstr = SDL_malloc(len);
    if (newstr) {
        SDL_strlcpy(newstr, string, len);
    }
    return newstr;
}
#endif

#ifdef SDL_strrev
#undef SDL_strrev
char *SDL_strrev(char *string) { return SDL_strrev_inline(string); }
#else
char *
SDL_strrev(char *string)
{
    size_t len = SDL_strlen(string);
    char *a = &string[0];
    char *b = &string[len - 1];
    len /= 2;
    while (len--) {
        char c = *a;
        *a++ = *b;
        *b-- = c;
    }
    return string;
}
#endif

#ifdef SDL_strupr
#undef SDL_strupr
char *SDL_strupr(char *string) { return SDL_strupr_inline(string); }
#else
char *
SDL_strupr(char *string)
{
    char *bufp = string;
    while (*bufp) {
        *bufp = SDL_toupper((unsigned char) *bufp);
        ++bufp;
    }
    return string;
}
#endif

#ifdef SDL_strlwr
#undef SDL_strlwr
char *SDL_strlwr(char *string) { return SDL_strlwr_inline(string); }
#else
char *
SDL_strlwr(char *string)
{
    char *bufp = string;
    while (*bufp) {
        *bufp = SDL_tolower((unsigned char) *bufp);
        ++bufp;
    }
    return string;
}
#endif

#ifdef SDL_strchr
#undef SDL_strchr
char *SDL_strchr(const char *string, int c) { return SDL_strchr_inline(string, c); }
#else
char *
SDL_strchr(const char *string, int c)
{
    while (*string) {
        if (*string == c) {
            return (char *) string;
        }
        ++string;
    }
    return NULL;
}
#endif

#ifdef SDL_strrchr
#undef SDL_strrchr
char *SDL_strrchr(const char *string, int c) { return SDL_strrchr_inline(string, c); }
#else
char *
SDL_strrchr(const char *string, int c)
{
    const char *bufp = string + SDL_strlen(string) - 1;
    while (bufp >= string) {
        if (*bufp == c) {
            return (char *) bufp;
        }
        --bufp;
    }
    return NULL;
}
#endif

#ifdef SDL_strstr
#undef SDL_strstr
char *SDL_strstr(const char *haystack, const char *needle) { return SDL_strstr_inline(haystack, needle); }
#else
char *
SDL_strstr(const char *haystack, const char *needle)
{
    size_t length = SDL_strlen(needle);
    while (*haystack) {
        if (SDL_strncmp(haystack, needle, length) == 0) {
            return (char *) haystack;
        }
        ++haystack;
    }
    return NULL;
}
#endif

#if !defined(SDL_ltoa) || !defined(SDL_lltoa) || \
    !defined(SDL_ultoa) || !defined(SDL_ulltoa)
static const char ntoa_table[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z'
};
#endif /* ntoa() conversion table */

#ifdef SDL_ltoa
#undef SDL_ltoa
char *SDL_ltoa(long value, char *string, int radix) { return SDL_ltoa_inline(value, string, radix); }
#else
char *
SDL_ltoa(long value, char *string, int radix)
{
    char *bufp = string;

    if (value < 0) {
        *bufp++ = '-';
        value = -value;
    }
    if (value) {
        while (value > 0) {
            *bufp++ = ntoa_table[value % radix];
            value /= radix;
        }
    } else {
        *bufp++ = '0';
    }
    *bufp = '\0';

    /* The numbers went into the string backwards. :) */
    if (*string == '-') {
        SDL_strrev(string + 1);
    } else {
        SDL_strrev(string);
    }

    return string;
}
#endif

#ifdef SDL_ultoa
#undef SDL_ultoa
char *SDL_ultoa(unsigned long value, char *string, int radix) { return SDL_ultoa_inline(value, string, radix); }
#else
char *
SDL_ultoa(unsigned long value, char *string, int radix)
{
    char *bufp = string;

    if (value) {
        while (value > 0) {
            *bufp++ = ntoa_table[value % radix];
            value /= radix;
        }
    } else {
        *bufp++ = '0';
    }
    *bufp = '\0';

    /* The numbers went into the string backwards. :) */
    SDL_strrev(string);

    return string;
}
#endif

#ifdef SDL_strtol
#undef SDL_strtol
long SDL_strtol(const char *string, char **endp, int base) { return SDL_strtol_inline(string, endp, base); }
#else
long
SDL_strtol(const char *string, char **endp, int base)
{
    size_t len;
    long value;

    if (!base) {
        if ((SDL_strlen(string) > 2) && (SDL_strncmp(string, "0x", 2) == 0)) {
            base = 16;
        } else {
            base = 10;
        }
    }

    len = SDL_ScanLong(string, base, &value);
    if (endp) {
        *endp = (char *) string + len;
    }
    return value;
}
#endif

#ifdef SDL_strtoul
#undef SDL_strtoul
unsigned long SDL_strtoul(const char *string, char **endp, int base) { return SDL_strtoul_inline(string, endp, base); }
#else
unsigned long
SDL_strtoul(const char *string, char **endp, int base)
{
    size_t len;
    unsigned long value;

    if (!base) {
        if ((SDL_strlen(string) > 2) && (SDL_strncmp(string, "0x", 2) == 0)) {
            base = 16;
        } else {
            base = 10;
        }
    }

    len = SDL_ScanUnsignedLong(string, base, &value);
    if (endp) {
        *endp = (char *) string + len;
    }
    return value;
}
#endif

#ifdef SDL_lltoa
#undef SDL_lltoa
char *SDL_lltoa(Sint64 value, char *string, int radix) { return SDL_lltoa_inline(value, string, radix); }
#else
char *
SDL_lltoa(Sint64 value, char *string, int radix)
{
    char *bufp = string;

    if (value < 0) {
        *bufp++ = '-';
        value = -value;
    }
    if (value) {
        while (value > 0) {
            *bufp++ = ntoa_table[value % radix];
            value /= radix;
        }
    } else {
        *bufp++ = '0';
    }
    *bufp = '\0';

    /* The numbers went into the string backwards. :) */
    if (*string == '-') {
        SDL_strrev(string + 1);
    } else {
        SDL_strrev(string);
    }

    return string;
}
#endif

#ifdef SDL_ulltoa
#undef SDL_ulltoa
char *SDL_ulltoa(Uint64 value, char *string, int radix) { return SDL_ulltoa_inline(value, string, radix); }
#else
char *
SDL_ulltoa(Uint64 value, char *string, int radix)
{
    char *bufp = string;

    if (value) {
        while (value > 0) {
            *bufp++ = ntoa_table[value % radix];
            value /= radix;
        }
    } else {
        *bufp++ = '0';
    }
    *bufp = '\0';

    /* The numbers went into the string backwards. :) */
    SDL_strrev(string);

    return string;
}
#endif

#ifdef SDL_strtoll
#undef SDL_strtoll
Sint64 SDL_strtoll(const char *string, char **endp, int base) { return SDL_strtoll_inline(string, endp, base); }
#else
Sint64
SDL_strtoll(const char *string, char **endp, int base)
{
    size_t len;
    Sint64 value;

    if (!base) {
        if ((SDL_strlen(string) > 2) && (SDL_strncmp(string, "0x", 2) == 0)) {
            base = 16;
        } else {
            base = 10;
        }
    }

    len = SDL_ScanLongLong(string, base, &value);
    if (endp) {
        *endp = (char *) string + len;
    }
    return value;
}
#endif

#ifdef SDL_strtoull
#undef SDL_strtoull
Uint64 SDL_strtoull(const char *string, char **endp, int base) { return SDL_strtoull_inline(string, endp, base); }
#else
Uint64
SDL_strtoull(const char *string, char **endp, int base)
{
    size_t len;
    Uint64 value;

    if (!base) {
        if ((SDL_strlen(string) > 2) && (SDL_strncmp(string, "0x", 2) == 0)) {
            base = 16;
        } else {
            base = 10;
        }
    }

    len = SDL_ScanUnsignedLongLong(string, base, &value);
    if (endp) {
        *endp = (char *) string + len;
    }
    return value;
}
#endif

#ifdef SDL_strtod
#undef SDL_strtod
double SDL_strtod(const char *string, char **endp) { return SDL_strtod_inline(string, endp); }
#else
double
SDL_strtod(const char *string, char **endp)
{
    size_t len;
    double value;

    len = SDL_ScanFloat(string, &value);
    if (endp) {
        *endp = (char *) string + len;
    }
    return value;
}
#endif

#ifdef SDL_strcmp
#undef SDL_strcmp
int SDL_strcmp(const char *str1, const char *str2) { return SDL_strcmp_inline(str1, str2); }
#else
int
SDL_strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str2) {
        if (*str1 != *str2)
            break;
        ++str1;
        ++str2;
    }
    return (int) ((unsigned char) *str1 - (unsigned char) *str2);
}
#endif

#ifdef SDL_strncmp
#undef SDL_strncmp
int SDL_strncmp(const char *str1, const char *str2, size_t maxlen) { return SDL_strncmp_inline(str1, str2, maxlen); }
#else
int
SDL_strncmp(const char *str1, const char *str2, size_t maxlen)
{
    while (*str1 && *str2 && maxlen) {
        if (*str1 != *str2)
            break;
        ++str1;
        ++str2;
        --maxlen;
    }
    if (!maxlen) {
        return 0;
    }
    return (int) ((unsigned char) *str1 - (unsigned char) *str2);
}
#endif

#ifdef SDL_strcasecmp
#undef SDL_strcasecmp
int SDL_strcasecmp(const char *str1, const char *str2) { return SDL_strcasecmp_inline(str1, str2); }
#else
int
SDL_strcasecmp(const char *str1, const char *str2)
{
    char a = 0;
    char b = 0;
    while (*str1 && *str2) {
        a = SDL_tolower((unsigned char) *str1);
        b = SDL_tolower((unsigned char) *str2);
        if (a != b)
            break;
        ++str1;
        ++str2;
    }
    a = SDL_tolower(*str1);
    b = SDL_tolower(*str2);
    return (int) ((unsigned char) a - (unsigned char) b);
}
#endif

#ifdef SDL_strncasecmp
#undef SDL_strncasecmp
int SDL_strncasecmp(const char *str1, const char *str2, size_t maxlen) { return SDL_strncasecmp_inline(str1, str2, maxlen); }
#else
int
SDL_strncasecmp(const char *str1, const char *str2, size_t maxlen)
{
    char a = 0;
    char b = 0;
    while (*str1 && *str2 && maxlen) {
        a = SDL_tolower((unsigned char) *str1);
        b = SDL_tolower((unsigned char) *str2);
        if (a != b)
            break;
        ++str1;
        ++str2;
        --maxlen;
    }
    if (maxlen == 0) {
        return 0;
    } else {
        a = SDL_tolower((unsigned char) *str1);
        b = SDL_tolower((unsigned char) *str2);
        return (int) ((unsigned char) a - (unsigned char) b);
    }
}
#endif

#ifdef SDL_sscanf
#undef SDL_sscanf
// Urho3D: removed function, as vsscanf is not available on Visual Studio
/*
SDL_sscanf(const char *text, const char *fmt, ...)
{
    int rc;
    va_list ap;
    va_start(ap, fmt);
    rc = vsscanf(text, fmt, ap);
    va_end(ap);
    return rc;
}
*/
#else
int
SDL_sscanf(const char *text, const char *fmt, ...)
{
    va_list ap;
    int retval = 0;

    va_start(ap, fmt);
    while (*fmt) {
        if (*fmt == ' ') {
            while (SDL_isspace((unsigned char) *text)) {
                ++text;
            }
            ++fmt;
            continue;
        }
        if (*fmt == '%') {
            SDL_bool done = SDL_FALSE;
            long count = 0;
            int radix = 10;
            enum
            {
                DO_SHORT,
                DO_INT,
                DO_LONG,
                DO_LONGLONG
            } inttype = DO_INT;
            SDL_bool suppress = SDL_FALSE;

            ++fmt;
            if (*fmt == '%') {
                if (*text == '%') {
                    ++text;
                    ++fmt;
                    continue;
                }
                break;
            }
            if (*fmt == '*') {
                suppress = SDL_TRUE;
                ++fmt;
            }
            fmt += SDL_ScanLong(fmt, 10, &count);

            if (*fmt == 'c') {
                if (!count) {
                    count = 1;
                }
                if (suppress) {
                    while (count--) {
                        ++text;
                    }
                } else {
                    char *valuep = va_arg(ap, char *);
                    while (count--) {
                        *valuep++ = *text++;
                    }
                    ++retval;
                }
                continue;
            }

            while (SDL_isspace((unsigned char) *text)) {
                ++text;
            }

            /* FIXME: implement more of the format specifiers */
            while (!done) {
                switch (*fmt) {
                case '*':
                    suppress = SDL_TRUE;
                    break;
                case 'h':
                    if (inttype > DO_SHORT) {
                        ++inttype;
                    }
                    break;
                case 'l':
                    if (inttype < DO_LONGLONG) {
                        ++inttype;
                    }
                    break;
                case 'I':
                    if (SDL_strncmp(fmt, "I64", 3) == 0) {
                        fmt += 2;
                        inttype = DO_LONGLONG;
                    }
                    break;
                case 'i':
                    {
                        int index = 0;
                        if (text[index] == '-') {
                            ++index;
                        }
                        if (text[index] == '0') {
                            if (SDL_tolower((unsigned char) text[index + 1]) == 'x') {
                                radix = 16;
                            } else {
                                radix = 8;
                            }
                        }
                    }
                    /* Fall through to %d handling */
                case 'd':
                    if (inttype == DO_LONGLONG) {
                        Sint64 value;
                        text += SDL_ScanLongLong(text, radix, &value);
                        if (!suppress) {
                            Sint64 *valuep = va_arg(ap, Sint64 *);
                            *valuep = value;
                            ++retval;
                        }
                    } else {
                        long value;
                        text += SDL_ScanLong(text, radix, &value);
                        if (!suppress) {
                            switch (inttype) {
                            case DO_SHORT:
                                {
                                    short *valuep = va_arg(ap, short *);
                                    *valuep = (short) value;
                                }
                                break;
                            case DO_INT:
                                {
                                    int *valuep = va_arg(ap, int *);
                                    *valuep = (int) value;
                                }
                                break;
                            case DO_LONG:
                                {
                                    long *valuep = va_arg(ap, long *);
                                    *valuep = value;
                                }
                                break;
                            case DO_LONGLONG:
                                /* Handled above */
                                break;
                            }
                            ++retval;
                        }
                    }
                    done = SDL_TRUE;
                    break;
                case 'o':
                    if (radix == 10) {
                        radix = 8;
                    }
                    /* Fall through to unsigned handling */
                case 'x':
                case 'X':
                    if (radix == 10) {
                        radix = 16;
                    }
                    /* Fall through to unsigned handling */
                case 'u':
                    if (inttype == DO_LONGLONG) {
                        Uint64 value;
                        text += SDL_ScanUnsignedLongLong(text, radix, &value);
                        if (!suppress) {
                            Uint64 *valuep = va_arg(ap, Uint64 *);
                            *valuep = value;
                            ++retval;
                        }
                    } else {
                        unsigned long value;
                        text += SDL_ScanUnsignedLong(text, radix, &value);
                        if (!suppress) {
                            switch (inttype) {
                            case DO_SHORT:
                                {
                                    short *valuep = va_arg(ap, short *);
                                    *valuep = (short) value;
                                }
                                break;
                            case DO_INT:
                                {
                                    int *valuep = va_arg(ap, int *);
                                    *valuep = (int) value;
                                }
                                break;
                            case DO_LONG:
                                {
                                    long *valuep = va_arg(ap, long *);
                                    *valuep = value;
                                }
                                break;
                            case DO_LONGLONG:
                                /* Handled above */
                                break;
                            }
                            ++retval;
                        }
                    }
                    done = SDL_TRUE;
                    break;
                case 'p':
                    {
                        uintptr_t value;
                        text += SDL_ScanUintPtrT(text, 16, &value);
                        if (!suppress) {
                            void **valuep = va_arg(ap, void **);
                            *valuep = (void *) value;
                            ++retval;
                        }
                    }
                    done = SDL_TRUE;
                    break;
                case 'f':
                    {
                        double value;
                        text += SDL_ScanFloat(text, &value);
                        if (!suppress) {
                            float *valuep = va_arg(ap, float *);
                            *valuep = (float) value;
                            ++retval;
                        }
                    }
                    done = SDL_TRUE;
                    break;
                case 's':
                    if (suppress) {
                        while (!SDL_isspace((unsigned char) *text)) {
                            ++text;
                            if (count) {
                                if (--count == 0) {
                                    break;
                                }
                            }
                        }
                    } else {
                        char *valuep = va_arg(ap, char *);
                        while (!SDL_isspace((unsigned char) *text)) {
                            *valuep++ = *text++;
                            if (count) {
                                if (--count == 0) {
                                    break;
                                }
                            }
                        }
                        *valuep = '\0';
                        ++retval;
                    }
                    done = SDL_TRUE;
                    break;
                default:
                    done = SDL_TRUE;
                    break;
                }
                ++fmt;
            }
            continue;
        }
        if (*text == *fmt) {
            ++text;
            ++fmt;
            continue;
        }
        /* Text didn't match format specifier */
        break;
    }
    va_end(ap);

    return retval;
}
#endif

/* just undef; the headers only define this to snprintf because of varargs. */
#ifdef SDL_snprintf
#undef SDL_snprintf
#endif
int
SDL_snprintf(char *text, size_t maxlen, const char *fmt, ...)
{
    va_list ap;
    int retval;

    va_start(ap, fmt);
    retval = SDL_vsnprintf(text, maxlen, fmt, ap);
    va_end(ap);

    return retval;
}

#ifdef SDL_vsnprintf
#undef SDL_vsnprintf
int SDL_vsnprintf(char *text, size_t maxlen, const char *fmt, va_list ap) { return SDL_vsnprintf_inline(text, maxlen, fmt, ap); }
#else
 /* FIXME: implement more of the format specifiers */
typedef struct
{
    SDL_bool left_justify;
    SDL_bool force_sign;
    SDL_bool force_type;
    SDL_bool pad_zeroes;
    SDL_bool do_lowercase;
    int width;
    int radix;
    int precision;
} SDL_FormatInfo;

static size_t
SDL_PrintString(char *text, size_t maxlen, SDL_FormatInfo *info, const char *string)
{
    return SDL_strlcpy(text, string, maxlen);
}

static size_t
SDL_PrintLong(char *text, size_t maxlen, SDL_FormatInfo *info, long value)
{
    char num[130];

    SDL_ltoa(value, num, info ? info->radix : 10);
    return SDL_PrintString(text, maxlen, info, num);
}

static size_t
SDL_PrintUnsignedLong(char *text, size_t maxlen, SDL_FormatInfo *info, unsigned long value)
{
    char num[130];

    SDL_ultoa(value, num, info ? info->radix : 10);
    return SDL_PrintString(text, maxlen, info, num);
}

static size_t
SDL_PrintLongLong(char *text, size_t maxlen, SDL_FormatInfo *info, Sint64 value)
{
    char num[130];

    SDL_lltoa(value, num, info ? info->radix : 10);
    return SDL_PrintString(text, maxlen, info, num);
}

static size_t
SDL_PrintUnsignedLongLong(char *text, size_t maxlen, SDL_FormatInfo *info, Uint64 value)
{
    char num[130];

    SDL_ulltoa(value, num, info ? info->radix : 10);
    return SDL_PrintString(text, maxlen, info, num);
}

static size_t
SDL_PrintFloat(char *text, size_t maxlen, SDL_FormatInfo *info, double arg)
{
    int i, width;
    size_t len;
    size_t left = maxlen;
    char *textstart = text;

    if (arg) {
        /* This isn't especially accurate, but hey, it's easy. :) */
        double precision = 1.0;
        unsigned long value;

        if (arg < 0) {
            if (left > 1) {
                *text = '-';
                --left;
            }
            ++text;
            arg = -arg;
        } else if (info->force_sign) {
            if (left > 1) {
                *text = '+';
                --left;
            }
            ++text;
        }
        value = (unsigned long) arg;
        len = SDL_PrintUnsignedLong(text, left, NULL, value);
        text += len;
        if (len >= left) {
            left = SDL_min(left, 1);
        } else {
            left -= len;
        }
        arg -= value;
        if (info->precision < 0) {
            info->precision = 6;
        }
        for (i = 0; i < info->precision; ++i) {
            precision *= 0.1;
        }
        if (info->force_type || info->precision > 0) {
            int mult = 10;
            if (left > 1) {
                *text = '.';
                --left;
            }
            ++text;
            while (info->precision-- > 0) {
                value = (unsigned long) (arg * mult);
                len = SDL_PrintUnsignedLong(text, left, NULL, value);
                text += len;
                if (len >= left) {
                    left = SDL_min(left, 1);
                } else {
                    left -= len;
                }
                arg -= (double) value / mult;
                mult *= 10;
            }
        }
    } else {
        if (left > 1) {
            *text = '0';
            --left;
        }
        ++text;
        if (info->force_type) {
            if (left > 1) {
                *text = '.';
                --left;
            }
            ++text;
        }
    }

    width = info->width - (int)(text - textstart);
    if (width > 0) {
        char fill = info->pad_zeroes ? '0' : ' ';
        char *end = text+left-1;
        len = (text - textstart);
        for (len = (text - textstart); len--; ) {
            if ((textstart+len+width) < end) {
                *(textstart+len+width) = *(textstart+len);
            }
        }
        len = (size_t)width;
        text += len;
        if (len >= left) {
            left = SDL_min(left, 1);
        } else {
            left -= len;
        }
        while (len--) {
            if (textstart+len < end) {
                textstart[len] = fill;
            }
        }
    }

    return (text - textstart);
}

int
SDL_vsnprintf(char *text, size_t maxlen, const char *fmt, va_list ap)
{
    size_t left = maxlen;
    char *textstart = text;

    while (*fmt) {
        if (*fmt == '%') {
            SDL_bool done = SDL_FALSE;
            size_t len = 0;
            SDL_bool check_flag;
            SDL_FormatInfo info;
            enum
            {
                DO_INT,
                DO_LONG,
                DO_LONGLONG
            } inttype = DO_INT;

            SDL_zero(info);
            info.radix = 10;
            info.precision = -1;

            check_flag = SDL_TRUE;
            while (check_flag) {
                ++fmt;
                switch (*fmt) {
                case '-':
                    info.left_justify = SDL_TRUE;
                    break;
                case '+':
                    info.force_sign = SDL_TRUE;
                    break;
                case '#':
                    info.force_type = SDL_TRUE;
                    break;
                case '0':
                    info.pad_zeroes = SDL_TRUE;
                    break;
                default:
                    check_flag = SDL_FALSE;
                    break;
                }
            }

            if (*fmt >= '0' && *fmt <= '9') {
                info.width = SDL_strtol(fmt, (char **)&fmt, 0);
            }

            if (*fmt == '.') {
                ++fmt;
                if (*fmt >= '0' && *fmt <= '9') {
                    info.precision = SDL_strtol(fmt, (char **)&fmt, 0);
                } else {
                    info.precision = 0;
                }
            }

            while (!done) {
                switch (*fmt) {
                case '%':
                    if (left > 1) {
                        *text = '%';
                    }
                    len = 1;
                    done = SDL_TRUE;
                    break;
                case 'c':
                    /* char is promoted to int when passed through (...) */
                    if (left > 1) {
                        *text = (char) va_arg(ap, int);
                    }
                    len = 1;
                    done = SDL_TRUE;
                    break;
                case 'h':
                    /* short is promoted to int when passed through (...) */
                    break;
                case 'l':
                    if (inttype < DO_LONGLONG) {
                        ++inttype;
                    }
                    break;
                case 'I':
                    if (SDL_strncmp(fmt, "I64", 3) == 0) {
                        fmt += 2;
                        inttype = DO_LONGLONG;
                    }
                    break;
                case 'i':
                case 'd':
                    switch (inttype) {
                    case DO_INT:
                        len = SDL_PrintLong(text, left, &info,
                                            (long) va_arg(ap, int));
                        break;
                    case DO_LONG:
                        len = SDL_PrintLong(text, left, &info,
                                            va_arg(ap, long));
                        break;
                    case DO_LONGLONG:
                        len = SDL_PrintLongLong(text, left, &info,
                                                va_arg(ap, Sint64));
                        break;
                    }
                    done = SDL_TRUE;
                    break;
                case 'p':
                case 'x':
                    info.do_lowercase = SDL_TRUE;
                    /* Fall through to 'X' handling */
                case 'X':
                    if (info.radix == 10) {
                        info.radix = 16;
                    }
                    if (*fmt == 'p') {
                        inttype = DO_LONG;
                    }
                    /* Fall through to unsigned handling */
                case 'o':
                    if (info.radix == 10) {
                        info.radix = 8;
                    }
                    /* Fall through to unsigned handling */
                case 'u':
                    switch (inttype) {
                    case DO_INT:
                        len = SDL_PrintUnsignedLong(text, left, &info,
                                                    (unsigned long)
                                                    va_arg(ap, unsigned int));
                        break;
                    case DO_LONG:
                        len = SDL_PrintUnsignedLong(text, left, &info,
                                                    va_arg(ap, unsigned long));
                        break;
                    case DO_LONGLONG:
                        len = SDL_PrintUnsignedLongLong(text, left, &info,
                                                        va_arg(ap, Uint64));
                        break;
                    }
                    if (info.do_lowercase) {
                        size_t i;
                        for (i = 0; i < len && i < left; ++i) {
                            text[i] = SDL_tolower((unsigned char)text[i]);
                        }
                    }
                    done = SDL_TRUE;
                    break;
                case 'f':
                    len = SDL_PrintFloat(text, left, &info, va_arg(ap, double));
                    done = SDL_TRUE;
                    break;
                case 's':
                    len = SDL_PrintString(text, left, &info, va_arg(ap, char *));
                    done = SDL_TRUE;
                    break;
                default:
                    done = SDL_TRUE;
                    break;
                }
                ++fmt;
            }
            text += len;
            if (len >= left) {
                left = SDL_min(left, 1);
            } else {
                left -= len;
            }
        } else {
            if (left > 1) {
                *text = *fmt;
                --left;
            }
            ++fmt;
            ++text;
        }
    }
    if (left > 0) {
        *text = '\0';
    }
    return (int)(text - textstart);
}
#endif

/* vi: set ts=4 sw=4 expandtab: */
