/* Copyright (c) 2013-2015 the Civetweb developers
 * Copyright (c) 2004-2013 Sergey Lyubka
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// Modified by cosmy1 for Urho3D

#if defined(_WIN32)
#if !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS /* Disable deprecation warning in VS2005 */
#endif
#ifndef _WIN32_WINNT /* defined for tdm-gcc so we can use getnameinfo */
#define _WIN32_WINNT 0x0501
#endif
#else
#if defined(__GNUC__) && !defined(_GNU_SOURCE)
#define _GNU_SOURCE /* for setgroups() */
#endif
#ifdef __linux__
#define _XOPEN_SOURCE 600 /* For flockfile() on Linux */
#endif
#ifndef _LARGEFILE_SOURCE
#define _LARGEFILE_SOURCE /* For fseeko(), ftello() */
#endif
#ifndef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS 64 /* Use 64-bit file offsets by default */
#endif
#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS /* <inttypes.h> wants this for C++ */
#endif
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS /* C++ wants that for INT64_MAX */
#endif
#ifdef __sun
#define __EXTENSIONS__  /* to expose flockfile and friends in stdio.h */
#define __inline inline /* not recognized on older compiler versions */
#endif
#endif

#if defined(USE_LUA) && defined(USE_WEBSOCKET)
#define USE_TIMERS
#endif

#if defined(_MSC_VER)
/* 'type cast' : conversion from 'int' to 'HANDLE' of greater size */
#pragma warning(disable : 4306)
/* conditional expression is constant: introduced by FD_SET(..) */
#pragma warning(disable : 4127)
/* non-constant aggregate initializer: issued due to missing C99 support */
#pragma warning(disable : 4204)
/* padding added after data member */
#pragma warning(disable : 4820)
/* not defined as a preprocessor macro, replacing with '0' for '#if/#elif' */
#pragma warning(disable : 4668)
/* no function prototype given: converting '()' to '(void)' */
#pragma warning(disable : 4255)
/* function has been selected for automatic inline expansion */
#pragma warning(disable : 4711)
#endif

/* This code uses static_assert to check some conditions.
 * Unfortunately some compilers still do not support it, so we have a
 * replacement function here. */
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#define mg_static_assert static_assert
#elif defined(__cplusplus) && (__cplusplus >= 201103L)
#define mg_static_assert static_assert
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#define mg_static_assert _Static_assert
#else
char static_assert_replacement[1];
#define mg_static_assert(cond, txt)                                            \
	extern char static_assert_replacement[(cond) ? 1 : -1]
#endif

mg_static_assert(sizeof(int) == 4 || sizeof(int) == 8,
                 "int data type size check");
mg_static_assert(sizeof(void *) == 4 || sizeof(void *) == 8,
                 "pointer data type size check");
mg_static_assert(sizeof(void *) >= sizeof(int), "data type size check");
/* mg_static_assert(sizeof(size_t) == 4 || sizeof(size_t) == 8, "size_t data
 * type size check"); */

/* DTL -- including winsock2.h works better if lean and mean */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#if defined(__SYMBIAN32__)
#define NO_SSL /* SSL is not supported */
#define NO_CGI /* CGI is not supported */
#define PATH_MAX FILENAME_MAX
#endif /* __SYMBIAN32__ */

#ifndef IGNORE_UNUSED_RESULT
#define IGNORE_UNUSED_RESULT(a) ((void)((a) && 1))
#endif

#ifndef _WIN32_WCE /* Some ANSI #includes are not available on Windows CE */
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#endif /* !_WIN32_WCE */

#ifdef __MACH__

#define CLOCK_MONOTONIC (1)
#define CLOCK_REALTIME (2)

#include <sys/time.h>
#include <mach/clock.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <assert.h>

/* clock_gettime is not implemented on OSX */
int clock_gettime(int clk_id, struct timespec *t);

int clock_gettime(int clk_id, struct timespec *t)
{
	if (clk_id == CLOCK_REALTIME) {
		struct timeval now;
		int rv = gettimeofday(&now, NULL);
		if (rv) {
			return rv;
		}
		t->tv_sec = now.tv_sec;
		t->tv_nsec = now.tv_usec * 1000;
		return 0;

	} else if (clk_id == CLOCK_MONOTONIC) {
		static uint64_t start_time = 0;
		static mach_timebase_info_data_t timebase_ifo = {0, 0};

		uint64_t now = mach_absolute_time();

		if (start_time == 0) {
			kern_return_t mach_status = mach_timebase_info(&timebase_ifo);
#if defined(DEBUG)
			assert(mach_status == KERN_SUCCESS);
#else
			/* appease "unused variable" warning for release builds */
			(void)mach_status;
#endif
			start_time = now;
		}

		now =
		    (uint64_t)((double)(now - start_time) * (double)timebase_ifo.numer /
		               (double)timebase_ifo.denom);

		t->tv_sec = now / 1000000000;
		t->tv_nsec = now % 1000000000;
		return 0;
	}
	return -1; /* EINVAL - Clock ID is unknown */
}
#endif

#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

#ifndef MAX_WORKER_THREADS
#define MAX_WORKER_THREADS (1024 * 64)
#endif
#ifndef SOCKET_TIMEOUT_QUANTUM
#define SOCKET_TIMEOUT_QUANTUM (10000)
#endif

mg_static_assert(MAX_WORKER_THREADS >= 1,
                 "worker threads must be a positive number");

#if defined(_WIN32) && !defined(__SYMBIAN32__) /* Windows specific */
#include <windows.h>
#include <winsock2.h> /* DTL add for SO_EXCLUSIVE */
#include <ws2tcpip.h>

typedef const char *SOCK_OPT_TYPE;

#if !defined(PATH_MAX)
#define PATH_MAX (MAX_PATH)
#endif

#if !defined(PATH_MAX)
#define PATH_MAX (4096)
#endif

mg_static_assert(PATH_MAX >= 1, "path length must be a positive number");

#ifndef _IN_PORT_T
#ifndef in_port_t
#define in_port_t u_short
#endif
#endif

#ifndef _WIN32_WCE
#include <process.h>
#include <direct.h>
#include <io.h>
#else          /* _WIN32_WCE */
#define NO_CGI /* WinCE has no pipes */

typedef long off_t;

#define errno ((int)(GetLastError()))
#define strerror(x) (_ultoa(x, (char *)_alloca(sizeof(x) * 3), 10))
#endif /* _WIN32_WCE */

#define MAKEUQUAD(lo, hi)                                                      \
	((uint64_t)(((uint32_t)(lo)) | ((uint64_t)((uint32_t)(hi))) << 32))
#define RATE_DIFF (10000000) /* 100 nsecs */
#define EPOCH_DIFF (MAKEUQUAD(0xd53e8000, 0x019db1de))
#define SYS2UNIX_TIME(lo, hi)                                                  \
	((time_t)((MAKEUQUAD((lo), (hi)) - EPOCH_DIFF) / RATE_DIFF))

/* Visual Studio 6 does not know __func__ or __FUNCTION__
 * The rest of MS compilers use __FUNCTION__, not C99 __func__
 * Also use _strtoui64 on modern M$ compilers */
#if defined(_MSC_VER)
#if (_MSC_VER < 1300)
#define STRX(x) #x
#define STR(x) STRX(x)
#define __func__ __FILE__ ":" STR(__LINE__)
#define strtoull(x, y, z) ((unsigned __int64)_atoi64(x))
#define strtoll(x, y, z) (_atoi64(x))
#else
#define __func__ __FUNCTION__
#define strtoull(x, y, z) (_strtoui64(x, y, z))
#define strtoll(x, y, z) (_strtoi64(x, y, z))
#endif
#endif /* _MSC_VER */

#define ERRNO ((int)(GetLastError()))
#define NO_SOCKLEN_T
#define SSL_LIB "ssleay32.dll"
#define CRYPTO_LIB "libeay32.dll"
#define O_NONBLOCK (0)
#ifndef W_OK
#define W_OK (2) /* http://msdn.microsoft.com/en-us/library/1w06ktdy.aspx */
#endif
#if !defined(EWOULDBLOCK)
#define EWOULDBLOCK WSAEWOULDBLOCK
#endif /* !EWOULDBLOCK */
#define _POSIX_
#define INT64_FMT "I64d"

#define WINCDECL __cdecl
#define SHUT_RD (0)
#define SHUT_WR (1)
#define SHUT_BOTH (2)
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#define access _access
#define mg_sleep(x) (Sleep(x))

#define pipe(x) _pipe(x, MG_BUF_LEN, _O_BINARY)
#ifndef popen
#define popen(x, y) (_popen(x, y))
#endif
#ifndef pclose
#define pclose(x) (_pclose(x))
#endif
#define close(x) (_close(x))
#define dlsym(x, y) (GetProcAddress((HINSTANCE)(x), (y)))
#define RTLD_LAZY (0)
#define fseeko(x, y, z) (_lseeki64(_fileno(x), (y), (z)))
#define fdopen(x, y) (_fdopen((x), (y)))
#define write(x, y, z) (_write((x), (y), (unsigned)z))
#define read(x, y, z) (_read((x), (y), (unsigned)z))
#define flockfile(x) (EnterCriticalSection(&global_log_file_lock))
#define funlockfile(x) (LeaveCriticalSection(&global_log_file_lock))
#define sleep(x) (Sleep((x)*1000))
#define rmdir(x) (_rmdir(x))

#if !defined(fileno)
#define fileno(x) (_fileno(x))
#endif /* !fileno MINGW #defines fileno */

typedef HANDLE pthread_mutex_t;
typedef DWORD pthread_key_t;
typedef HANDLE pthread_t;
typedef struct {
	CRITICAL_SECTION threadIdSec;
	int waitingthreadcount;       /* The number of threads queued. */
	pthread_t *waitingthreadhdls; /* The thread handles. */
} pthread_cond_t;

#ifndef __clockid_t_defined
typedef DWORD clockid_t;
#endif
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC (1)
#endif
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME (2)
#endif

// Urho3D: fix VC15 compilation issue
#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#define _TIMESPEC_DEFINED
#endif
#ifndef _TIMESPEC_DEFINED
struct timespec {
	time_t tv_sec; /* seconds */
	long tv_nsec;  /* nanoseconds */
};
#endif

#define pid_t HANDLE /* MINGW typedefs pid_t to int. Using #define here. */

static int pthread_mutex_lock(pthread_mutex_t *);
static int pthread_mutex_unlock(pthread_mutex_t *);
static void to_unicode(const char *path, wchar_t *wbuf, size_t wbuf_len);
struct file;
static char *mg_fgets(char *buf, size_t size, struct file *filep, char **p);

#if defined(HAVE_STDINT)
#include <stdint.h>
#else
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;
#define INT64_MAX (9223372036854775807)
#endif /* HAVE_STDINT */

/* POSIX dirent interface */
struct dirent {
	char d_name[PATH_MAX];
};

typedef struct DIR {
	HANDLE handle;
	WIN32_FIND_DATAW info;
	struct dirent result;
} DIR;

#if defined(_WIN32) && !defined(POLLIN)
#ifndef HAVE_POLL
struct pollfd {
	SOCKET fd;
	short events;
	short revents;
};
#define POLLIN (0x0300)
#endif
#endif

/* Mark required libraries */
#if defined(_MSC_VER)
#pragma comment(lib, "Ws2_32.lib")
#endif

#else /* UNIX  specific */
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/utsname.h>
#include <stdint.h>
#include <inttypes.h>
#include <netdb.h>
typedef const void *SOCK_OPT_TYPE;

#if defined(ANDROID)
typedef unsigned short int in_port_t;
#endif

#include <pwd.h>
#include <unistd.h>
#include <grp.h>
#include <dirent.h>
#if !defined(NO_SSL_DL) && !defined(NO_SSL)
#include <dlfcn.h>
#endif
#include <pthread.h>
#if defined(__MACH__)
#define SSL_LIB "libssl.dylib"
#define CRYPTO_LIB "libcrypto.dylib"
#else
#if !defined(SSL_LIB)
#define SSL_LIB "libssl.so"
#endif
#if !defined(CRYPTO_LIB)
#define CRYPTO_LIB "libcrypto.so"
#endif
#endif
#ifndef O_BINARY
#define O_BINARY (0)
#endif /* O_BINARY */
#define closesocket(a) (close(a))
#define mg_mkdir(x, y) (mkdir(x, y))
#define mg_remove(x) (remove(x))
#define mg_sleep(x) (usleep((x)*1000))
#define ERRNO (errno)
#define INVALID_SOCKET (-1)
#define INT64_FMT PRId64
typedef int SOCKET;
#define WINCDECL

#if defined(__hpux)
/* HPUX 11 does not have monotonic, fall back to realtime */
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC CLOCK_REALTIME
#endif

/* HPUX defines socklen_t incorrectly as size_t which is 64bit on
 * Itanium.  Without defining _XOPEN_SOURCE or _XOPEN_SOURCE_EXTENDED
 * the prototypes use int* rather than socklen_t* which matches the
 * actual library expectation.  When called with the wrong size arg
 * accept() returns a zero client inet addr and check_acl() always
 * fails.  Since socklen_t is widely used below, just force replace
 * their typedef with int. - DTL
 */
#define socklen_t int
#endif /* hpux */

#endif /* End of Windows and UNIX specific includes */

/* va_copy should always be a macro, C99 and C++11 - DTL */
#ifndef va_copy
#define va_copy(x, y) ((x) = (y))
#endif

#ifdef _WIN32
static CRITICAL_SECTION global_log_file_lock;
static DWORD pthread_self(void) { return GetCurrentThreadId(); }

static int pthread_key_create(
    pthread_key_t *key,
    void (*_must_be_zero)(
        void *) /* destructor function not supported for windows */)
{
	assert(_must_be_zero == NULL);
	if ((key != 0) && (_must_be_zero == NULL)) {
		*key = TlsAlloc();
		return (*key != TLS_OUT_OF_INDEXES) ? 0 : -1;
	}
	return -2;
}

static int pthread_key_delete(pthread_key_t key)
{
	return TlsFree(key) ? 0 : 1;
}

static int pthread_setspecific(pthread_key_t key, void *value)
{
	return TlsSetValue(key, value) ? 0 : 1;
}

#ifdef ENABLE_UNUSED_PTHREAD_FUNCTIONS
static void *pthread_getspecific(pthread_key_t key) { return TlsGetValue(key); }
#endif
#endif /* _WIN32 */

#include "civetweb.h"

#define PASSWORDS_FILE_NAME ".htpasswd"
#define CGI_ENVIRONMENT_SIZE (4096)
#define MAX_CGI_ENVIR_VARS (64)
#define MG_BUF_LEN (8192)

#ifndef MAX_REQUEST_SIZE
#define MAX_REQUEST_SIZE (16384)
#endif

mg_static_assert(MAX_REQUEST_SIZE >= 256,
                 "request size length must be a positive number");

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#if !defined(DEBUG_TRACE)
#if defined(DEBUG)

static void DEBUG_TRACE_FUNC(const char *func,
                             unsigned line,
                             PRINTF_FORMAT_STRING(const char *fmt),
                             ...) PRINTF_ARGS(3, 4);

static void
DEBUG_TRACE_FUNC(const char *func, unsigned line, const char *fmt, ...)
{
	va_list args;
	flockfile(stdout);
	printf("*** %lu.%p.%s.%u: ",
	       (unsigned long)time(NULL),
	       (void *)pthread_self(),
	       func,
	       line);
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	putchar('\n');
	fflush(stdout);
	funlockfile(stdout);
}

#define DEBUG_TRACE(fmt, ...)                                                  \
	DEBUG_TRACE_FUNC(__func__, __LINE__, fmt, __VA_ARGS__)

#else
#define DEBUG_TRACE(fmt, ...)                                                  \
	do {                                                                       \
	} while (0)
#endif /* DEBUG */
#endif /* DEBUG_TRACE */

#if defined(MEMORY_DEBUGGING)
unsigned long mg_memory_debug_blockCount = 0;
unsigned long mg_memory_debug_totalMemUsed = 0;

static void *mg_malloc_ex(size_t size, const char *file, unsigned line)
{
	void *data = malloc(size + sizeof(size_t));
	void *memory = 0;
	char mallocStr[256];

	if (data) {
		*(size_t *)data = size;
		mg_memory_debug_totalMemUsed += size;
		mg_memory_debug_blockCount++;
		memory = (void *)(((char *)data) + sizeof(size_t));
	}

	sprintf(mallocStr,
	        "MEM: %p %5lu alloc   %7lu %4lu --- %s:%u\n",
	        memory,
	        (unsigned long)size,
	        mg_memory_debug_totalMemUsed,
	        mg_memory_debug_blockCount,
	        file,
	        line);
#if defined(_WIN32)
	OutputDebugStringA(mallocStr);
#else
	DEBUG_TRACE("%s", mallocStr);
#endif

	return memory;
}

static void *
mg_calloc_ex(size_t count, size_t size, const char *file, unsigned line)
{
	void *data = mg_malloc_ex(size * count, file, line);
	if (data) {
		memset(data, 0, size);
	}
	return data;
}

static void mg_free_ex(void *memory, const char *file, unsigned line)
{
	char mallocStr[256];
	void *data = (void *)(((char *)memory) - sizeof(size_t));
	size_t size;

	if (memory) {
		size = *(size_t *)data;
		mg_memory_debug_totalMemUsed -= size;
		mg_memory_debug_blockCount--;
		sprintf(mallocStr,
		        "MEM: %p %5lu free    %7lu %4lu --- %s:%u\n",
		        memory,
		        (unsigned long)size,
		        mg_memory_debug_totalMemUsed,
		        mg_memory_debug_blockCount,
		        file,
		        line);
#if defined(_WIN32)
		OutputDebugStringA(mallocStr);
#else
		DEBUG_TRACE("%s", mallocStr);
#endif

		free(data);
	}
}

static void *
mg_realloc_ex(void *memory, size_t newsize, const char *file, unsigned line)
{
	char mallocStr[256];
	void *data;
	void *_realloc;
	size_t oldsize;

	if (newsize) {
		if (memory) {
			data = (void *)(((char *)memory) - sizeof(size_t));
			oldsize = *(size_t *)data;
			_realloc = realloc(data, newsize + sizeof(size_t));
			if (_realloc) {
				data = _realloc;
				mg_memory_debug_totalMemUsed -= oldsize;
				sprintf(mallocStr,
				        "MEM: %p %5lu r-free  %7lu %4lu --- %s:%u\n",
				        memory,
				        (unsigned long)oldsize,
				        mg_memory_debug_totalMemUsed,
				        mg_memory_debug_blockCount,
				        file,
				        line);
#if defined(_WIN32)
				OutputDebugStringA(mallocStr);
#else
				DEBUG_TRACE("%s", mallocStr);
#endif
				mg_memory_debug_totalMemUsed += newsize;
				sprintf(mallocStr,
				        "MEM: %p %5lu r-alloc %7lu %4lu --- %s:%u\n",
				        memory,
				        (unsigned long)newsize,
				        mg_memory_debug_totalMemUsed,
				        mg_memory_debug_blockCount,
				        file,
				        line);
#if defined(_WIN32)
				OutputDebugStringA(mallocStr);
#else
				DEBUG_TRACE("%s", mallocStr);
#endif
				*(size_t *)data = newsize;
				data = (void *)(((char *)data) + sizeof(size_t));
			} else {
#if defined(_WIN32)
				OutputDebugStringA("MEM: realloc failed\n");
#else
				DEBUG_TRACE("%s", "MEM: realloc failed\n");
#endif
				return _realloc;
			}
		} else {
			data = mg_malloc_ex(newsize, file, line);
		}
	} else {
		data = 0;
		mg_free_ex(memory, file, line);
	}

	return data;
}

#define mg_malloc(a) mg_malloc_ex(a, __FILE__, __LINE__)
#define mg_calloc(a, b) mg_calloc_ex(a, b, __FILE__, __LINE__)
#define mg_realloc(a, b) mg_realloc_ex(a, b, __FILE__, __LINE__)
#define mg_free(a) mg_free_ex(a, __FILE__, __LINE__)

#else

static __inline void *mg_malloc(size_t a) { return malloc(a); }
static __inline void *mg_calloc(size_t a, size_t b) { return calloc(a, b); }
static __inline void *mg_realloc(void *a, size_t b) { return realloc(a, b); }
static __inline void mg_free(void *a) { free(a); }

#endif

/* This following lines are just meant as a reminder to use the mg-functions
 * for memory management */
#ifdef malloc
#undef malloc
#endif
#ifdef calloc
#undef calloc
#endif
#ifdef realloc
#undef realloc
#endif
#ifdef free
#undef free
#endif
#define malloc DO_NOT_USE_THIS_FUNCTION__USE_mg_malloc
#define calloc DO_NOT_USE_THIS_FUNCTION__USE_mg_calloc
#define realloc DO_NOT_USE_THIS_FUNCTION__USE_mg_realloc
#define free DO_NOT_USE_THIS_FUNCTION__USE_mg_free

#define MD5_STATIC static
#include "md5.inl"

/* Darwin prior to 7.0 and Win32 do not have socklen_t */
#ifdef NO_SOCKLEN_T
typedef int socklen_t;
#endif /* NO_SOCKLEN_T */
#define _DARWIN_UNLIMITED_SELECT

#define IP_ADDR_STR_LEN (50) /* IPv6 hex string is 46 chars */

#if !defined(MSG_NOSIGNAL)
#define MSG_NOSIGNAL (0)
#endif

#if !defined(SOMAXCONN)
#define SOMAXCONN (100)
#endif

/* Size of the accepted socket queue */
#if !defined(MGSQLEN)
#define MGSQLEN (20)
#endif

#if defined(NO_SSL_DL)
#include <openssl/ssl.h>
#include <openssl/err.h>
#else
/* SSL loaded dynamically from DLL.
 * I put the prototypes here to be independent from OpenSSL source
 * installation. */

typedef struct ssl_st SSL;
typedef struct ssl_method_st SSL_METHOD;
typedef struct ssl_ctx_st SSL_CTX;

struct ssl_func {
	const char *name;  /* SSL function name */
	void (*ptr)(void); /* Function pointer */
};

#define SSL_free (*(void (*)(SSL *))ssl_sw[0].ptr)
#define SSL_accept (*(int (*)(SSL *))ssl_sw[1].ptr)
#define SSL_connect (*(int (*)(SSL *))ssl_sw[2].ptr)
#define SSL_read (*(int (*)(SSL *, void *, int))ssl_sw[3].ptr)
#define SSL_write (*(int (*)(SSL *, const void *, int))ssl_sw[4].ptr)
#define SSL_get_error (*(int (*)(SSL *, int))ssl_sw[5].ptr)
#define SSL_set_fd (*(int (*)(SSL *, SOCKET))ssl_sw[6].ptr)
#define SSL_new (*(SSL * (*)(SSL_CTX *))ssl_sw[7].ptr)
#define SSL_CTX_new (*(SSL_CTX * (*)(SSL_METHOD *))ssl_sw[8].ptr)
#define SSLv23_server_method (*(SSL_METHOD * (*)(void))ssl_sw[9].ptr)
#define SSL_library_init (*(int (*)(void))ssl_sw[10].ptr)
#define SSL_CTX_use_PrivateKey_file                                            \
	(*(int (*)(SSL_CTX *, const char *, int))ssl_sw[11].ptr)
#define SSL_CTX_use_certificate_file                                           \
	(*(int (*)(SSL_CTX *, const char *, int))ssl_sw[12].ptr)
#define SSL_CTX_set_default_passwd_cb                                          \
	(*(void (*)(SSL_CTX *, mg_callback_t))ssl_sw[13].ptr)
#define SSL_CTX_free (*(void (*)(SSL_CTX *))ssl_sw[14].ptr)
#define SSL_load_error_strings (*(void (*)(void))ssl_sw[15].ptr)
#define SSL_CTX_use_certificate_chain_file                                     \
	(*(int (*)(SSL_CTX *, const char *))ssl_sw[16].ptr)
#define SSLv23_client_method (*(SSL_METHOD * (*)(void))ssl_sw[17].ptr)
#define SSL_pending (*(int (*)(SSL *))ssl_sw[18].ptr)
#define SSL_CTX_set_verify (*(void (*)(SSL_CTX *, int, int))ssl_sw[19].ptr)
#define SSL_shutdown (*(int (*)(SSL *))ssl_sw[20].ptr)

#define CRYPTO_num_locks (*(int (*)(void))crypto_sw[0].ptr)
#define CRYPTO_set_locking_callback                                            \
	(*(void (*)(void (*)(int, int, const char *, int)))crypto_sw[1].ptr)
#define CRYPTO_set_id_callback                                                 \
	(*(void (*)(unsigned long (*)(void)))crypto_sw[2].ptr)
#define ERR_get_error (*(unsigned long (*)(void))crypto_sw[3].ptr)
#define ERR_error_string (*(char *(*)(unsigned long, char *))crypto_sw[4].ptr)

/* set_ssl_option() function updates this array.
 * It loads SSL library dynamically and changes NULLs to the actual addresses
 * of respective functions. The macros above (like SSL_connect()) are really
 * just calling these functions indirectly via the pointer. */
static struct ssl_func ssl_sw[] = {{"SSL_free", NULL},
                                   {"SSL_accept", NULL},
                                   {"SSL_connect", NULL},
                                   {"SSL_read", NULL},
                                   {"SSL_write", NULL},
                                   {"SSL_get_error", NULL},
                                   {"SSL_set_fd", NULL},
                                   {"SSL_new", NULL},
                                   {"SSL_CTX_new", NULL},
                                   {"SSLv23_server_method", NULL},
                                   {"SSL_library_init", NULL},
                                   {"SSL_CTX_use_PrivateKey_file", NULL},
                                   {"SSL_CTX_use_certificate_file", NULL},
                                   {"SSL_CTX_set_default_passwd_cb", NULL},
                                   {"SSL_CTX_free", NULL},
                                   {"SSL_load_error_strings", NULL},
                                   {"SSL_CTX_use_certificate_chain_file", NULL},
                                   {"SSLv23_client_method", NULL},
                                   {"SSL_pending", NULL},
                                   {"SSL_CTX_set_verify", NULL},
                                   {"SSL_shutdown", NULL},
                                   {NULL, NULL}};

/* Similar array as ssl_sw. These functions could be located in different
 * lib. */
#if !defined(NO_SSL)
static struct ssl_func crypto_sw[] = {{"CRYPTO_num_locks", NULL},
                                      {"CRYPTO_set_locking_callback", NULL},
                                      {"CRYPTO_set_id_callback", NULL},
                                      {"ERR_get_error", NULL},
                                      {"ERR_error_string", NULL},
                                      {NULL, NULL}};
#endif /* NO_SSL */
#endif /* NO_SSL_DL */

static const char *month_names[] = {"Jan",
                                    "Feb",
                                    "Mar",
                                    "Apr",
                                    "May",
                                    "Jun",
                                    "Jul",
                                    "Aug",
                                    "Sep",
                                    "Oct",
                                    "Nov",
                                    "Dec"};

/* Unified socket address. For IPv6 support, add IPv6 address structure in the
 * union u. */
union usa {
	struct sockaddr sa;
	struct sockaddr_in sin;
#if defined(USE_IPV6)
	struct sockaddr_in6 sin6;
#endif
};

/* Describes a string (chunk of memory). */
struct vec {
	const char *ptr;
	size_t len;
};

struct file {
	uint64_t size;
	time_t last_modified;
	FILE *fp;
	const char *membuf; /* Non-NULL if file data is in memory */
	int is_directory;
	int gzipped; /* set to 1 if the content is gzipped
	              * in which case we need a content-encoding: gzip header */
};
#define STRUCT_FILE_INITIALIZER                                                \
	{                                                                          \
		(uint64_t)0, (time_t)0, (FILE *)NULL, (const char *)NULL, 0, 0         \
	}

/* Describes listening socket, or socket which was accept()-ed by the master
 * thread and queued for future handling by the worker thread. */
struct socket {
	SOCKET sock;             /* Listening socket */
	union usa lsa;           /* Local socket address */
	union usa rsa;           /* Remote socket address */
	unsigned char is_ssl;    /* Is port SSL-ed */
	unsigned char ssl_redir; /* Is port supposed to redirect everything to SSL
	                          * port */
};

/* NOTE(lsm): this enum shoulds be in sync with the config_options below. */
enum {
	CGI_EXTENSIONS,
	CGI_ENVIRONMENT,
	PUT_DELETE_PASSWORDS_FILE,
	CGI_INTERPRETER,
	PROTECT_URI,
	AUTHENTICATION_DOMAIN,
	SSI_EXTENSIONS,
	THROTTLE,
	ACCESS_LOG_FILE,
	ENABLE_DIRECTORY_LISTING,
	ERROR_LOG_FILE,
	GLOBAL_PASSWORDS_FILE,
	INDEX_FILES,
	ENABLE_KEEP_ALIVE,
	ACCESS_CONTROL_LIST,
	EXTRA_MIME_TYPES,
	LISTENING_PORTS,
	DOCUMENT_ROOT,
	SSL_CERTIFICATE,
	NUM_THREADS,
	RUN_AS_USER,
	REWRITE,
	HIDE_FILES,
	REQUEST_TIMEOUT,
#if defined(USE_WEBSOCKET)
	WEBSOCKET_TIMEOUT,
#endif
	DECODE_URL,

#if defined(USE_LUA)
	LUA_PRELOAD_FILE,
	LUA_SCRIPT_EXTENSIONS,
	LUA_SERVER_PAGE_EXTENSIONS,
#endif
#if defined(USE_WEBSOCKET)
	WEBSOCKET_ROOT,
#endif
#if defined(USE_LUA) && defined(USE_WEBSOCKET)
	LUA_WEBSOCKET_EXTENSIONS,
#endif
	ACCESS_CONTROL_ALLOW_ORIGIN,
	ERROR_PAGES,

	NUM_OPTIONS
};

/* Config option name, config types, default value */
static struct mg_option config_options[] = {
    {"cgi_pattern", CONFIG_TYPE_EXT_PATTERN, "**.cgi$|**.pl$|**.php$"},
    {"cgi_environment", CONFIG_TYPE_STRING, NULL},
    {"put_delete_auth_file", CONFIG_TYPE_FILE, NULL},
    {"cgi_interpreter", CONFIG_TYPE_FILE, NULL},
    {"protect_uri", CONFIG_TYPE_STRING, NULL},
    {"authentication_domain", CONFIG_TYPE_STRING, "mydomain.com"},
    {"ssi_pattern", CONFIG_TYPE_EXT_PATTERN, "**.shtml$|**.shtm$"},
    {"throttle", CONFIG_TYPE_STRING, NULL},
    {"access_log_file", CONFIG_TYPE_FILE, NULL},
    {"enable_directory_listing", CONFIG_TYPE_BOOLEAN, "yes"},
    {"error_log_file", CONFIG_TYPE_FILE, NULL},
    {"global_auth_file", CONFIG_TYPE_FILE, NULL},
    {"index_files",
     CONFIG_TYPE_STRING,
#ifdef USE_LUA
     "index.xhtml,index.html,index.htm,index.lp,index.lsp,index.lua,index.cgi,"
     "index.shtml,index.php"},
#else
     "index.xhtml,index.html,index.htm,index.cgi,index.shtml,index.php"},
#endif
    {"enable_keep_alive", CONFIG_TYPE_BOOLEAN, "no"},
    {"access_control_list", CONFIG_TYPE_STRING, NULL},
    {"extra_mime_types", CONFIG_TYPE_STRING, NULL},
    {"listening_ports", CONFIG_TYPE_STRING, "8080"},
    {"document_root", CONFIG_TYPE_DIRECTORY, NULL},
    {"ssl_certificate", CONFIG_TYPE_FILE, NULL},
    {"num_threads", CONFIG_TYPE_NUMBER, "50"},
    {"run_as_user", CONFIG_TYPE_STRING, NULL},
    {"url_rewrite_patterns", CONFIG_TYPE_STRING, NULL},
    {"hide_files_patterns", CONFIG_TYPE_EXT_PATTERN, NULL},
    {"request_timeout_ms", CONFIG_TYPE_NUMBER, "30000"},
#if defined(USE_WEBSOCKET)
    {"websocket_timeout_ms", CONFIG_TYPE_NUMBER, "30000"},
#endif
    {"decode_url", CONFIG_TYPE_BOOLEAN, "yes"},

#if defined(USE_LUA)
    {"lua_preload_file", CONFIG_TYPE_FILE, NULL},
    {"lua_script_pattern", CONFIG_TYPE_EXT_PATTERN, "**.lua$"},
    {"lua_server_page_pattern", CONFIG_TYPE_EXT_PATTERN, "**.lp$|**.lsp$"},
#endif
#if defined(USE_WEBSOCKET)
    {"websocket_root", CONFIG_TYPE_DIRECTORY, NULL},
#endif
#if defined(USE_LUA) && defined(USE_WEBSOCKET)
    {"lua_websocket_pattern", CONFIG_TYPE_EXT_PATTERN, "**.lua$"},
#endif
    {"access_control_allow_origin", CONFIG_TYPE_STRING, "*"},
    {"error_pages", CONFIG_TYPE_DIRECTORY, NULL},

    {NULL, CONFIG_TYPE_UNKNOWN, NULL}};


/* Check if the config_options and the corresponding enum have compatible
 * sizes. */
mg_static_assert((sizeof(config_options) / sizeof(config_options[0])) ==
                     (NUM_OPTIONS + 1),
                 "config_options and enum not sync");


struct mg_request_handler_info {
	/* Name/Pattern of the URI. */
	char *uri;
	size_t uri_len;

	/* URI type: ws/wss (websocket) or http/https (web page). */
	int is_websocket_handler;

	/* Handler for http/https requests. */
	mg_request_handler handler;

	/* Handler for ws/wss (websocket) requests. */
	mg_websocket_connect_handler connect_handler;
	mg_websocket_ready_handler ready_handler;
	mg_websocket_data_handler data_handler;
	mg_websocket_close_handler close_handler;

	/* User supplied argument for the handler function. */
	void *cbdata;

	/* next request handler in a linked list */
	struct mg_request_handler_info *next;
};

struct mg_context {
	volatile int stop_flag;        /* Should we stop event loop */
	SSL_CTX *ssl_ctx;              /* SSL context */
	char *config[NUM_OPTIONS];     /* Civetweb configuration parameters */
	struct mg_callbacks callbacks; /* User-defined callback function */
	void *user_data;               /* User-defined data */
	int context_type;              /* 1 = server context, 2 = client context */

	struct socket *listening_sockets;
	in_port_t *listening_ports;
	unsigned int num_listening_sockets;

	volatile int num_threads;     /* Number of threads */
	pthread_mutex_t thread_mutex; /* Protects (max|num)_threads */
	pthread_cond_t thread_cond; /* Condvar for tracking workers terminations */

	struct socket queue[MGSQLEN];   /* Accepted sockets */
	volatile int sq_head;           /* Head of the socket queue */
	volatile int sq_tail;           /* Tail of the socket queue */
	pthread_cond_t sq_full;         /* Signaled when socket is produced */
	pthread_cond_t sq_empty;        /* Signaled when socket is consumed */
	pthread_t masterthreadid;       /* The master thread ID */
	unsigned int workerthreadcount; /* The amount of worker threads. */
	pthread_t *workerthreadids;     /* The worker thread IDs */

	unsigned long start_time; /* Server start time, used for authentication */
	pthread_mutex_t nonce_mutex; /* Protects nonce_count */
	unsigned long nonce_count;   /* Used nonces, used for authentication */

	char *systemName; /* What operating system is running */

	/* linked list of uri handlers */
	struct mg_request_handler_info *request_handlers;

#if defined(USE_LUA) && defined(USE_WEBSOCKET)
	/* linked list of shared lua websockets */
	struct mg_shared_lua_websocket_list *shared_lua_websockets;
#endif

#ifdef USE_TIMERS
	struct ttimers *timers;
#endif
};

struct mg_connection {
	struct mg_request_info request_info;
	struct mg_context *ctx;
	SSL *ssl;                    /* SSL descriptor */
	SSL_CTX *client_ssl_ctx;     /* SSL context for client connections */
	struct socket client;        /* Connected client */
	time_t conn_birth_time;      /* Time (wall clock) when connection was
	                              * established */
	struct timespec req_time;    /* Time (since system start) when the request
	                              * was received */
	int64_t num_bytes_sent;      /* Total bytes sent to client */
	int64_t content_len;         /* Content-Length header value */
	int64_t consumed_content;    /* How many bytes of content have been read */
	int is_chunked;              /* Transfer-encoding is chunked: 0=no, 1=yes:
	                              * data available, 2: all data read */
	size_t chunk_remainder;      /* Unread data from the last chunk */
	char *buf;                   /* Buffer for received data */
	char *path_info;             /* PATH_INFO part of the URL */
	int must_close;              /* 1 if connection must be closed */
	int in_error_handler;        /* 1 if in handler for user defined error
	                              * pages */
	int buf_size;                /* Buffer size */
	int request_len;             /* Size of the request + headers in a buffer */
	int data_len;                /* Total size of data in a buffer */
	int status_code;             /* HTTP reply status code, e.g. 200 */
	int throttle;                /* Throttling, bytes/sec. <= 0 means no
	                              * throttle */
	time_t last_throttle_time;   /* Last time throttled data was sent */
	int64_t last_throttle_bytes; /* Bytes sent this second */
	pthread_mutex_t mutex;       /* Used by mg_(un)lock_connection to ensure
	                              * atomic transmissions for websockets */
#if defined(USE_LUA) && defined(USE_WEBSOCKET)
	void *lua_websocket_state; /* Lua_State for a websocket connection */
#endif
};

static pthread_key_t sTlsKey; /* Thread local storage index */
static int sTlsInit = 0;

struct mg_workerTLS {
	int is_master;
#if defined(_WIN32) && !defined(__SYMBIAN32__)
	HANDLE pthread_cond_helper_mutex;
#endif
};

/* Directory entry */
struct de {
	struct mg_connection *conn;
	char *file_name;
	struct file file;
};

#if defined(USE_WEBSOCKET)
static int is_websocket_protocol(const struct mg_connection *conn);
#else
#define is_websocket_protocol(conn) (0)
#endif

static int mg_atomic_inc(volatile int *addr)
{
	int ret;
#if defined(_WIN32) && !defined(__SYMBIAN32__)
	/* Depending on the SDK, this function uses either
	 * (volatile unsigned int *) or (volatile LONG *),
	 * so whatever you use, the other SDK is likely to raise a warning. */
	ret = InterlockedIncrement((volatile long *)addr);
#elif defined(__GNUC__)
	ret = __sync_add_and_fetch(addr, 1);
#else
	ret = (++(*addr));
#endif
	return ret;
}

static int mg_atomic_dec(volatile int *addr)
{
	int ret;
#if defined(_WIN32) && !defined(__SYMBIAN32__)
	/* Depending on the SDK, this function uses either
	 * (volatile unsigned int *) or (volatile LONG *),
	 * so whatever you use, the other SDK is likely to raise a warning. */
	ret = InterlockedDecrement((volatile long *)addr);
#elif defined(__GNUC__)
	ret = __sync_sub_and_fetch(addr, 1);
#else
	ret = (--(*addr));
#endif
	return ret;
}

#if !defined(NO_THREAD_NAME)
#if defined(_WIN32) && defined(_MSC_VER)
/* Set the thread name for debugging purposes in Visual Studio
 * http://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx
 */
#pragma pack(push, 8)
typedef struct tagTHREADNAME_INFO {
	DWORD dwType;     /* Must be 0x1000. */
	LPCSTR szName;    /* Pointer to name (in user addr space). */
	DWORD dwThreadID; /* Thread ID (-1=caller thread). */
	DWORD dwFlags;    /* Reserved for future use, must be zero. */
} THREADNAME_INFO;
#pragma pack(pop)
#elif defined(__linux__)
#include <sys/prctl.h>
#include <sys/sendfile.h>
#endif

#if ((__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 12)))
#define GLIBC_CHK
#endif

static void mg_set_thread_name(const char *name)
{
	char threadName[16]; /* Max. thread length in Linux/OSX/.. */

	/* TODO (low): use strcpy and strcat instad of snprintf, use server name,
	 * don't
	 * return */
	if (snprintf(threadName, sizeof(threadName), "civetweb-%s", name) < 0) {
		return;
	}

	threadName[sizeof(threadName) - 1] = 0;

#if defined(_WIN32)
#if defined(_MSC_VER)
	/* Windows and Visual Studio Compiler */
	__try
	{
		THREADNAME_INFO info;
		info.dwType = 0x1000;
		info.szName = threadName;
		info.dwThreadID = ~0U;
		info.dwFlags = 0;

		RaiseException(0x406D1388,
		               0,
		               sizeof(info) / sizeof(ULONG_PTR),
		               (ULONG_PTR *)&info);
	}
	__except(EXCEPTION_EXECUTE_HANDLER) {}
#elif defined(__MINGW32__)
	/* No option known to set thread name for MinGW */
	;
#endif
#elif defined(__linux__)
/* Linux */
#if defined(GLIBC_CHK)
	(void)pthread_setname_np(pthread_self(), threadName);
#else
	(void)prctl(PR_SET_NAME, threadName, 0, 0, 0);
#endif
#elif defined(__APPLE__) || defined(__MACH__)
/* OS X */
#if defined(GLIBC_CHK)
	(void)pthread_setname_np(threadName);
#endif
#elif defined(BSD) || defined(__FreeBSD__) || defined(__OpenBSD__)
/* BSD (TODO: test) */
#if defined(GLIBC_CHK)
	pthread_set_name_np(pthread_self(), threadName);
#endif
#elif defined(__AIX__) || defined(_AIX) || defined(__hpux) || defined(__sun)
/* pthread_set_name_np seems to be missing on AIX, hpux, sun, ... */
#else
/* POSIX */
#if defined(GLIBC_CHK)
	(void)pthread_setname_np(pthread_self(), threadName);
#endif
#endif
}
#else /* !defined(NO_THREAD_NAME) */
void mg_set_thread_name(const char *threadName) {}
#endif

#if defined(MG_LEGACY_INTERFACE)
const char **mg_get_valid_option_names(void)
{
	static const char *
	    data[2 * sizeof(config_options) / sizeof(config_options[0])] = {0};
	int i;

	for (i = 0; config_options[i].name != NULL; i++) {
		data[i * 2] = config_options[i].name;
		data[i * 2 + 1] = config_options[i].default_value;
	}

	return data;
}
#endif

const struct mg_option *mg_get_valid_options(void) { return config_options; }

static int is_file_in_memory(struct mg_connection *conn,
                             const char *path,
                             struct file *filep)
{
	size_t size = 0;
	if (!conn || !filep) {
		return 0;
	}

	filep->last_modified = (time_t)0;

	if ((filep->membuf =
	         conn->ctx->callbacks.open_file == NULL
	             ? NULL
	             : conn->ctx->callbacks.open_file(conn, path, &size)) != NULL) {
		/* NOTE: override filep->size only on success. Otherwise, it might
		 * break constructs like if (!mg_stat() || !mg_fopen()) ... */
		filep->size = size;
	}
	return filep->membuf != NULL;
}

static int is_file_opened(const struct file *filep)
{
	if (!filep) {
		return 0;
	}

	return filep->membuf != NULL || filep->fp != NULL;
}

static int mg_fopen(struct mg_connection *conn,
                    const char *path,
                    const char *mode,
                    struct file *filep)
{
	if (!filep) {
		return 0;
	}

	if (!is_file_in_memory(conn, path, filep)) {
#ifdef _WIN32
		wchar_t wbuf[PATH_MAX], wmode[20];
		to_unicode(path, wbuf, ARRAY_SIZE(wbuf));
		MultiByteToWideChar(CP_UTF8, 0, mode, -1, wmode, ARRAY_SIZE(wmode));
		filep->fp = _wfopen(wbuf, wmode);
#else
		filep->fp = fopen(path, mode);
#endif
	}

	return is_file_opened(filep);
}

static void mg_fclose(struct file *filep)
{
	if (filep != NULL && filep->fp != NULL) {
		fclose(filep->fp);
	}
}

static void mg_strlcpy(register char *dst, register const char *src, size_t n)
{
	for (; *src != '\0' && n > 1; n--) {
		*dst++ = *src++;
	}
	*dst = '\0';
}

static int lowercase(const char *s)
{
	return tolower(*(const unsigned char *)s);
}

int mg_strncasecmp(const char *s1, const char *s2, size_t len)
{
	int diff = 0;

	if (len > 0) {
		do {
			diff = lowercase(s1++) - lowercase(s2++);
		} while (diff == 0 && s1[-1] != '\0' && --len > 0);
	}

	return diff;
}

static int mg_strcasecmp(const char *s1, const char *s2)
{
	int diff;

	do {
		diff = lowercase(s1++) - lowercase(s2++);
	} while (diff == 0 && s1[-1] != '\0');

	return diff;
}

static char *mg_strndup(const char *ptr, size_t len)
{
	char *p;

	if ((p = (char *)mg_malloc(len + 1)) != NULL) {
		mg_strlcpy(p, ptr, len + 1);
	}

	return p;
}

static char *mg_strdup(const char *str) { return mg_strndup(str, strlen(str)); }

static const char *mg_strcasestr(const char *big_str, const char *small_str)
{
	size_t i, big_len = strlen(big_str), small_len = strlen(small_str);

	if (big_len >= small_len) {
		for (i = 0; i <= (big_len - small_len); i++) {
			if (mg_strncasecmp(big_str + i, small_str, small_len) == 0) {
				return big_str + i;
			}
		}
	}

	return NULL;
}

/* Like snprintf(), but never returns negative value, or a value
 * that is larger than a supplied buffer.
 * Thanks to Adam Zeldis to pointing snprintf()-caused vulnerability
 * in his audit report. */
static int mg_vsnprintf(struct mg_connection *conn,
                        char *buf,
                        size_t buflen,
                        const char *fmt,
                        va_list ap)
{
	int n;

	if (buflen == 0) {
		return 0;
	}

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-nonliteral"
/* Using fmt as a non-literal is intended here, since it is mostly called
 * indirectly by mg_snprintf */
#endif

	n = vsnprintf(buf, buflen, fmt, ap);

#ifdef __clang__
#pragma clang diagnostic pop
#endif

	if (n < 0) {
		mg_cry(conn, "vsnprintf error");
		n = 0;
	} else if (n >= (int)buflen) {
		mg_cry(conn,
		       "truncating vsnprintf buffer: [%.*s]",
		       n > 200 ? 200 : n,
		       buf);
		n = (int)buflen - 1;
	}
	buf[n] = '\0';

	return n;
}

static int mg_snprintf(struct mg_connection *conn,
                       char *buf,
                       size_t buflen,
                       PRINTF_FORMAT_STRING(const char *fmt),
                       ...) PRINTF_ARGS(4, 5);

static int mg_snprintf(
    struct mg_connection *conn, char *buf, size_t buflen, const char *fmt, ...)
{
	va_list ap;
	int n;

	va_start(ap, fmt);
	n = mg_vsnprintf(conn, buf, buflen, fmt, ap);
	va_end(ap);

	return n;
}

static int get_option_index(const char *name)
{
	int i;

	for (i = 0; config_options[i].name != NULL; i++) {
		if (strcmp(config_options[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}

const char *mg_get_option(const struct mg_context *ctx, const char *name)
{
	int i;
	if ((i = get_option_index(name)) == -1) {
		return NULL;
	} else if (!ctx || ctx->config[i] == NULL) {
		return "";
	} else {
		return ctx->config[i];
	}
}

struct mg_context *mg_get_context(const struct mg_connection *conn)
{
	return (conn == NULL) ? (struct mg_context *)NULL : (conn->ctx);
}

void *mg_get_user_data(const struct mg_context *ctx)
{
	return (ctx == NULL) ? NULL : ctx->user_data;
}

void mg_set_user_connection_data(const struct mg_connection *conn, void *data)
{
	if (conn != NULL) {
		((struct mg_connection *)conn)->request_info.conn_data = data;
	}
}

void *mg_get_user_connection_data(const struct mg_connection *conn)
{
	if (conn != NULL) {
		return conn->request_info.conn_data;
	}
	return NULL;
}

size_t
mg_get_ports(const struct mg_context *ctx, size_t size, int *ports, int *ssl)
{
	size_t i;
	if (!ctx) {
		return 0;
	}
	for (i = 0; i < size && i < ctx->num_listening_sockets; i++) {
		ssl[i] = ctx->listening_sockets[i].is_ssl;
		ports[i] = ctx->listening_ports[i];
	}
	return i;
}

static void sockaddr_to_string(char *buf, size_t len, const union usa *usa)
{
	buf[0] = '\0';

	if (!usa) {
		return;
	}

	if (usa->sa.sa_family == AF_INET) {
		getnameinfo(&usa->sa,
		            sizeof(usa->sin),
		            buf,
		            (unsigned)len,
		            NULL,
		            0,
		            NI_NUMERICHOST);
	}
#if defined(USE_IPV6)
	else if (usa->sa.sa_family == AF_INET6) {
		getnameinfo(&usa->sa,
		            sizeof(usa->sin6),
		            buf,
		            (unsigned)len,
		            NULL,
		            0,
		            NI_NUMERICHOST);
	}
#endif
}

/* Convert time_t to a string. According to RFC2616, Sec 14.18, this must be
 * included in all responses other than 100, 101, 5xx. */
static void gmt_time_string(char *buf, size_t buf_len, time_t *t)
{
	struct tm *tm;

	tm = gmtime(t);
	if (tm != NULL) {
		strftime(buf, buf_len, "%a, %d %b %Y %H:%M:%S GMT", tm);
	} else {
		mg_strlcpy(buf, "Thu, 01 Jan 1970 00:00:00 GMT", buf_len);
		buf[buf_len - 1] = '\0';
	}
}

/* difftime for struct timespec. Return value is in seconds. */
static double mg_difftimespec(const struct timespec *ts_now,
                              const struct timespec *ts_before)
{
	return (double)(ts_now->tv_nsec - ts_before->tv_nsec) * 1.0E-9 +
	       (double)(ts_now->tv_sec - ts_before->tv_sec);
}

/* Print error message to the opened error log stream. */
void mg_cry(const struct mg_connection *conn, const char *fmt, ...)
{
	char buf[MG_BUF_LEN], src_addr[IP_ADDR_STR_LEN];
	va_list ap;
	FILE *fp;
	time_t timestamp;

	va_start(ap, fmt);
	IGNORE_UNUSED_RESULT(vsnprintf(buf, sizeof(buf), fmt, ap));
	va_end(ap);

	/* Do not lock when getting the callback value, here and below.
	 * I suppose this is fine, since function cannot disappear in the
	 * same way string option can. */
	if (conn && (conn->ctx->callbacks.log_message == NULL ||
	             conn->ctx->callbacks.log_message(conn, buf) == 0)) {
		fp = conn->ctx->config[ERROR_LOG_FILE] == NULL
		         ? NULL
		         : fopen(conn->ctx->config[ERROR_LOG_FILE], "a+");

		if (fp != NULL) {
			flockfile(fp);
			timestamp = time(NULL);

			sockaddr_to_string(src_addr, sizeof(src_addr), &conn->client.rsa);
			fprintf(fp,
			        "[%010lu] [error] [client %s] ",
			        (unsigned long)timestamp,
			        src_addr);

			if (conn->request_info.request_method != NULL) {
				fprintf(fp,
				        "%s %s: ",
				        conn->request_info.request_method,
				        conn->request_info.uri);
			}

			fprintf(fp, "%s", buf);
			fputc('\n', fp);
			funlockfile(fp);
			fclose(fp);
		}
	}
}

/* Return fake connection structure. Used for logging, if connection
 * is not applicable at the moment of logging. */
static struct mg_connection *fc(struct mg_context *ctx)
{
	static struct mg_connection fake_connection;
	fake_connection.ctx = ctx;
	return &fake_connection;
}

const char *mg_version(void) { return CIVETWEB_VERSION; }

const struct mg_request_info *
mg_get_request_info(const struct mg_connection *conn)
{
	if (!conn) {
		return NULL;
	}
	return &conn->request_info;
}

/* Skip the characters until one of the delimiters characters found.
 * 0-terminate resulting word. Skip the delimiter and following whitespaces.
 * Advance pointer to buffer to the next word. Return found 0-terminated word.
 * Delimiters can be quoted with quotechar. */
static char *skip_quoted(char **buf,
                         const char *delimiters,
                         const char *whitespace,
                         char quotechar)
{
	char *p, *begin_word, *end_word, *end_whitespace;

	begin_word = *buf;
	end_word = begin_word + strcspn(begin_word, delimiters);

	/* Check for quotechar */
	if (end_word > begin_word) {
		p = end_word - 1;
		while (*p == quotechar) {
			/* TODO (bel, low): it seems this code is never reached, so
			 * quotechar is actually not needed - check if this code may be
			 * droped */

			/* If there is anything beyond end_word, copy it */
			if (*end_word == '\0') {
				*p = '\0';
				break;
			} else {
				size_t end_off = strcspn(end_word + 1, delimiters);
				memmove(p, end_word, end_off + 1);
				p += end_off; /* p must correspond to end_word - 1 */
				end_word += end_off + 1;
			}
		}
		for (p++; p < end_word; p++) {
			*p = '\0';
		}
	}

	if (*end_word == '\0') {
		*buf = end_word;
	} else {
		end_whitespace = end_word + 1 + strspn(end_word + 1, whitespace);

		for (p = end_word; p < end_whitespace; p++) {
			*p = '\0';
		}

		*buf = end_whitespace;
	}

	return begin_word;
}

/* Simplified version of skip_quoted without quote char
 * and whitespace == delimiters */
static char *skip(char **buf, const char *delimiters)
{
	return skip_quoted(buf, delimiters, delimiters, 0);
}

/* Return HTTP header value, or NULL if not found. */
static const char *get_header(const struct mg_request_info *ri,
                              const char *name)
{
	int i;
	if (ri) {
		for (i = 0; i < ri->num_headers; i++) {
			if (!mg_strcasecmp(name, ri->http_headers[i].name)) {
				return ri->http_headers[i].value;
			}
		}
	}

	return NULL;
}

const char *mg_get_header(const struct mg_connection *conn, const char *name)
{
	if (!conn) {
		return NULL;
	}

	return get_header(&conn->request_info, name);
}

/* A helper function for traversing a comma separated list of values.
 * It returns a list pointer shifted to the next value, or NULL if the end
 * of the list found.
 * Value is stored in val vector. If value has form "x=y", then eq_val
 * vector is initialized to point to the "y" part, and val vector length
 * is adjusted to point only to "x". */
static const char *
next_option(const char *list, struct vec *val, struct vec *eq_val)
{
	if (val == NULL || list == NULL || *list == '\0') {
		/* End of the list */
		list = NULL;
	} else {
		val->ptr = list;
		if ((list = strchr(val->ptr, ',')) != NULL) {
			/* Comma found. Store length and shift the list ptr */
			val->len = ((size_t)(list - val->ptr));
			list++;
		} else {
			/* This value is the last one */
			list = val->ptr + strlen(val->ptr);
			val->len = ((size_t)(list - val->ptr));
		}

		if (eq_val != NULL) {
			/* Value has form "x=y", adjust pointers and lengths
			 * so that val points to "x", and eq_val points to "y". */
			eq_val->len = 0;
			eq_val->ptr = (const char *)memchr(val->ptr, '=', val->len);
			if (eq_val->ptr != NULL) {
				eq_val->ptr++; /* Skip over '=' character */
				eq_val->len = ((size_t)(val->ptr - eq_val->ptr)) + val->len;
				val->len = ((size_t)(eq_val->ptr - val->ptr)) - 1;
			}
		}
	}

	return list;
}

/* Perform case-insensitive match of string against pattern */
static int
match_prefix(const char *pattern, size_t pattern_len, const char *str)
{
	const char *or_str;
	size_t i;
	int j, len, res;

	if ((or_str = (const char *)memchr(pattern, '|', pattern_len)) != NULL) {
		res = match_prefix(pattern, (size_t)(or_str - pattern), str);
		return res > 0 ? res : match_prefix(or_str + 1,
		                                    (size_t)((pattern + pattern_len) -
		                                             (or_str + 1)),
		                                    str);
	}

	for (i = 0, j = 0; i < pattern_len; i++, j++) {
		if (pattern[i] == '?' && str[j] != '\0') {
			continue;
		} else if (pattern[i] == '$') {
			return str[j] == '\0' ? j : -1;
		} else if (pattern[i] == '*') {
			i++;
			if (pattern[i] == '*') {
				i++;
				len = (int)strlen(str + j);
			} else {
				len = (int)strcspn(str + j, "/");
			}
			if (i == pattern_len) {
				return j + len;
			}
			do {
				res = match_prefix(pattern + i, pattern_len - i, str + j + len);
			} while (res == -1 && len-- > 0);
			return res == -1 ? -1 : j + res + len;
		} else if (lowercase(&pattern[i]) != lowercase(&str[j])) {
			return -1;
		}
	}
	return j;
}

/* HTTP 1.1 assumes keep alive if "Connection:" header is not set
 * This function must tolerate situations when connection info is not
 * set up, for example if request parsing failed. */
static int should_keep_alive(const struct mg_connection *conn)
{
	if (conn != NULL) {
		const char *http_version = conn->request_info.http_version;
		const char *header = mg_get_header(conn, "Connection");
		if (conn->must_close || conn->status_code == 401 ||
		    mg_strcasecmp(conn->ctx->config[ENABLE_KEEP_ALIVE], "yes") != 0 ||
		    (header != NULL && mg_strcasecmp(header, "keep-alive") != 0) ||
		    (header == NULL && http_version &&
		     0 != strcmp(http_version, "1.1"))) {
			return 0;
		}
		return 1;
	}
	return 0;
}

static int should_decode_url(const struct mg_connection *conn)
{
	if (!conn || !conn->ctx) {
		return 0;
	}

	return (mg_strcasecmp(conn->ctx->config[DECODE_URL], "yes") == 0);
}

static const char *suggest_connection_header(const struct mg_connection *conn)
{
	return should_keep_alive(conn) ? "keep-alive" : "close";
}

static void handle_file_based_request(struct mg_connection *conn,
                                      const char *path,
                                      struct file *filep);
static int
mg_stat(struct mg_connection *conn, const char *path, struct file *filep);

static const char *mg_get_response_code_text(int response_code,
                                             struct mg_connection *conn)
{
	switch (response_code) {
	/* RFC2616 Section 10.1 - Informational 1xx */
	case 100:
		return "Continue"; /* RFC2616 Section 10.1.1 */
	case 101:
		return "Switching Protocols"; /* RFC2616 Section 10.1.2 */
	case 102:
		return "Processing"; /* RFC2518 Section 10.1 */

	/* RFC2616 Section 10.2 - Successful 2xx */
	case 200:
		return "OK"; /* RFC2616 Section 10.2.1 */
	case 201:
		return "Created"; /* RFC2616 Section 10.2.2 */
	case 202:
		return "Accepted"; /* RFC2616 Section 10.2.3 */
	case 203:
		return "Non-Authoritative Information"; /* RFC2616 Section 10.2.4 */
	case 204:
		return "No Content"; /* RFC2616 Section 10.2.5 */
	case 205:
		return "Reset Content"; /* RFC2616 Section 10.2.6 */
	case 206:
		return "Partial Content"; /* RFC2616 Section 10.2.7 */
	case 207:
		return "Multi-Status"; /* RFC2518 Section 10.2, RFC4918 Section 11.1 */

	/* RFC2616 Section 10.3 - Redirection 3xx */
	case 300:
		return "Multiple Choices"; /* RFC2616 Section 10.3.1 */
	case 301:
		return "Moved Permanently"; /* RFC2616 Section 10.3.2 */
	case 302:
		return "Found"; /* RFC2616 Section 10.3.3 */
	case 303:
		return "See Other"; /* RFC2616 Section 10.3.4 */
	case 304:
		return "Not Modified"; /* RFC2616 Section 10.3.5 */
	case 305:
		return "Use Proxy"; /* RFC2616 Section 10.3.6 */
	case 307:
		return "Temporary Redirect"; /* RFC2616 Section 10.3.8 */

	/* RFC2616 Section 10.4 - Client Error 4xx */
	case 400:
		return "Bad Request"; /* RFC2616 Section 10.4.1 */
	case 401:
		return "Unauthorized"; /* RFC2616 Section 10.4.2 */
	case 402:
		return "Payment Required"; /* RFC2616 Section 10.4.3 */
	case 403:
		return "Forbidden"; /* RFC2616 Section 10.4.4 */
	case 404:
		return "Not Found"; /* RFC2616 Section 10.4.5 */
	case 405:
		return "Method Not Allowed"; /* RFC2616 Section 10.4.6 */
	case 406:
		return "Not Acceptable"; /* RFC2616 Section 10.4.7 */
	case 407:
		return "Proxy Authentication Required"; /* RFC2616 Section 10.4.8 */
	case 408:
		return "Request Time-out"; /* RFC2616 Section 10.4.9 */
	case 409:
		return "Conflict"; /* RFC2616 Section 10.4.10 */
	case 410:
		return "Gone"; /* RFC2616 Section 10.4.11 */
	case 411:
		return "Length Required"; /* RFC2616 Section 10.4.12 */
	case 412:
		return "Precondition Failed"; /* RFC2616 Section 10.4.13 */
	case 413:
		return "Request Entity Too Large"; /* RFC2616 Section 10.4.14 */
	case 414:
		return "Request-URI Too Large"; /* RFC2616 Section 10.4.15 */
	case 415:
		return "Unsupported Media Type"; /* RFC2616 Section 10.4.16 */
	case 416:
		return "Requested range not satisfiable"; /* RFC2616 Section 10.4.17 */
	case 417:
		return "Expectation Failed"; /* RFC2616 Section 10.4.18 */
	case 422:
		return "Unproccessable entity"; /* RFC2518 Section 10.3, RFC4918
		                                 * Section 11.2 */
	case 423:
		return "Locked"; /* RFC2518 Section 10.4, RFC4918 Section 11.3 */
	case 424:
		return "Failed Dependency"; /* RFC2518 Section 10.5, RFC4918
		                             * Section 11.4 */
	case 428:
		return "Precondition Required"; /* RFC 6585, Section 3 */
	case 429:
		return "Too Many Requests"; /* RFC 6585, Section 4 */
	case 431:
		return "Request Header Fields Too Large"; /* RFC 6585, Section 5 */

	/* RFC2616 Section 10.5 - Server Error 5xx */
	case 500:
		return "Internal Server Error"; /* RFC2616 Section 10.5.1 */
	case 501:
		return "Not Implemented"; /* RFC2616 Section 10.5.2 */
	case 502:
		return "Bad Gateway"; /* RFC2616 Section 10.5.3 */
	case 503:
		return "Service Unavailable"; /* RFC2616 Section 10.5.4 */
	case 504:
		return "Gateway Time-out"; /* RFC2616 Section 10.5.5 */
	case 505:
		return "HTTP Version not supported"; /* RFC2616 Section 10.5.6 */
	case 507:
		return "Insufficient Storage"; /* RFC2518 Section 10.6, RFC4918
		                                * Section 11.5 */
	case 511:
		return "Network Authentication Required"; /* RFC 6585, Section 6 */

	/* Other RFCs */
	case 426:
		return "Upgrade Required"; /* RFC 2817 */

	/* Return codes from non normative RFCs: */
	/* Informative and experimental RFCs, "de facto" standards due to common
	 * use, ... */
	case 208:
		return "Already Reported"; /* RFC5842 Section 7.1 */
	case 226:
		return "IM used"; /* RFC3229 Section 10.4.1 */
	case 308:
		return "Permanent Redirect"; /* RFC7238 Section 3 */
	case 418:
		return "I am a teapot"; /* RFC2324 Section 2.3.2 */
	case 419:
		return "Authentication Timeout"; /* common use */
	case 451:
		return "Unavailable For Legal Reasons"; /* draft-tbray-http-legally-restricted-status-05,
		                                         * Section 3 */
	case 506:
		return "Variant Also Negotiates"; /* RFC 2295, Section 8.1 */
	case 508:
		return "Loop Detected"; /* RFC5842 Section 7.1 */
	case 510:
		return "Not Extended"; /* RFC 2774, Section 7 */

	default:
		/* This error code is unknown. This should not happen. */
		if (conn) {
			mg_cry(conn, "Unknown HTTP response code: %u", response_code);
		}

		/* Return at least a category according to RFC 2616 Section 10. */
		if (response_code >= 100 && response_code < 200) {
			/* Unknown informational status code */
			return "Information";
		}
		if (response_code >= 200 && response_code < 300) {
			/* Unknown success code */
			return "Success";
		}
		if (response_code >= 300 && response_code < 400) {
			/* Unknown redirection code */
			return "Redirection";
		}
		if (response_code >= 400 && response_code < 500) {
			/* Unknown request error code */
			return "Client Error";
		}
		if (response_code >= 500 && response_code < 600) {
			/* Unknown server error code */
			return "Server Error";
		}

		/* Response code not even within reasonable range */
		return "";
	}
}

static void send_http_error(struct mg_connection *,
                            int,
                            PRINTF_FORMAT_STRING(const char *fmt),
                            ...) PRINTF_ARGS(3, 4);

static void
send_http_error(struct mg_connection *conn, int status, const char *fmt, ...)
{
	char buf[MG_BUF_LEN];
	va_list ap;
	int len = 0, i, page_handler_found, scope;
	char date[64];
	time_t curtime = time(NULL);
	const char *error_handler = NULL;
	struct file error_page_file = STRUCT_FILE_INITIALIZER;
	const char *error_page_file_ext, *tstr;

	const char *status_text = mg_get_response_code_text(status, conn);

	if (conn == NULL) {
		return;
	}

	conn->status_code = status;
	if (conn->in_error_handler || conn->ctx->callbacks.http_error == NULL ||
	    conn->ctx->callbacks.http_error(conn, status)) {
		if (!conn->in_error_handler) {
			/* Send user defined error pages, if defined */
			error_handler = conn->ctx->config[ERROR_PAGES];
			error_page_file_ext = conn->ctx->config[INDEX_FILES];
			page_handler_found = 0;
			if (error_handler != NULL) {
				for (scope = 1; (scope <= 3) && !page_handler_found; scope++) {
					switch (scope) {
					case 1:
						len = mg_snprintf(conn,
						                  buf,
						                  sizeof(buf) - 32,
						                  "%serror%03u.",
						                  error_handler,
						                  status);
						break;
					case 2:
						len = mg_snprintf(conn,
						                  buf,
						                  sizeof(buf) - 32,
						                  "%serror%01uxx.",
						                  error_handler,
						                  status / 100);
						break;
					default:
						len = mg_snprintf(conn,
						                  buf,
						                  sizeof(buf) - 32,
						                  "%serror.",
						                  error_handler);
						break;
					}
					tstr = strchr(error_page_file_ext, '.');
					while (tstr) {
						for (i = 1; i < 32 && tstr[i] != 0 && tstr[i] != ',';
						     i++)
							buf[len + i - 1] = tstr[i];
						buf[len + i - 1] = 0;
						if (mg_stat(conn, buf, &error_page_file)) {
							page_handler_found = 1;
							break;
						}
						tstr = strchr(tstr + i, '.');
					}
				}
			}

			if (page_handler_found) {
				conn->in_error_handler = 1;
				handle_file_based_request(conn, buf, &error_page_file);
				conn->in_error_handler = 0;
				return;
			}
		}

		buf[0] = '\0';
		gmt_time_string(date, sizeof(date), &curtime);

		/* Errors 1xx, 204 and 304 MUST NOT send a body */
		if (status > 199 && status != 204 && status != 304) {
			len = mg_snprintf(conn,
			                  buf,
			                  sizeof(buf) - 1,
			                  "Error %d: %s",
			                  status,
			                  status_text);
			buf[len] = '\n';
			len++;
			buf[len] = 0;

			va_start(ap, fmt);
			len += mg_vsnprintf(
			    conn, buf + len, sizeof(buf) - (size_t)len, fmt, ap);
			va_end(ap);
		}
		DEBUG_TRACE("[%s]", buf);

		mg_printf(conn, "HTTP/1.1 %d %s\r\n", status, status_text);
		if (len > 0) {
			mg_printf(conn, "Content-Type: text/plain\r\n");
		}
		mg_printf(conn,
		          "Content-Length: %d\r\n"
		          "Date: %s\r\n"
		          "Connection: %s\r\n\r\n",
		          len,
		          date,
		          suggest_connection_header(conn));
		conn->num_bytes_sent += mg_printf(conn, "%s", buf);
	}
}

#if defined(_WIN32) && !defined(__SYMBIAN32__)
static int pthread_mutex_init(pthread_mutex_t *mutex, void *unused)
{
	(void)unused;
	*mutex = CreateMutex(NULL, FALSE, NULL);
	return *mutex == NULL ? -1 : 0;
}

static int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
	return CloseHandle(*mutex) == 0 ? -1 : 0;
}

static int pthread_mutex_lock(pthread_mutex_t *mutex)
{
	return WaitForSingleObject(*mutex, INFINITE) == WAIT_OBJECT_0 ? 0 : -1;
}

#ifdef ENABLE_UNUSED_PTHREAD_FUNCTIONS
static int pthread_mutex_trylock(pthread_mutex_t *mutex)
{
	switch (WaitForSingleObject(*mutex, 0)) {
	case WAIT_OBJECT_0:
		return 0;
	case WAIT_TIMEOUT:
		return -2; /* EBUSY */
	}
	return -1;
}
#endif

static int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
	return ReleaseMutex(*mutex) == 0 ? -1 : 0;
}

#ifndef WIN_PTHREADS_TIME_H
static int clock_gettime(clockid_t clk_id, struct timespec *tp)
{
	FILETIME ft;
	ULARGE_INTEGER li;
	BOOL ok = FALSE;
	double d;
	static double perfcnt_per_sec = 0.0;

	if (tp) {
		if (clk_id == CLOCK_REALTIME) {
			GetSystemTimeAsFileTime(&ft);
			li.LowPart = ft.dwLowDateTime;
			li.HighPart = ft.dwHighDateTime;
			li.QuadPart -= 116444736000000000; /* 1.1.1970 in filedate */
			tp->tv_sec = (time_t)(li.QuadPart / 10000000);
			tp->tv_nsec = (long)(li.QuadPart % 10000000) * 100;
			ok = TRUE;
		} else if (clk_id == CLOCK_MONOTONIC) {
			if (perfcnt_per_sec == 0.0) {
				QueryPerformanceFrequency((LARGE_INTEGER *)&li);
				perfcnt_per_sec = 1.0 / li.QuadPart;
			}
			if (perfcnt_per_sec != 0.0) {
				QueryPerformanceCounter((LARGE_INTEGER *)&li);
				d = li.QuadPart * perfcnt_per_sec;
				tp->tv_sec = (time_t)d;
				d -= tp->tv_sec;
				tp->tv_nsec = (long)(d * 1.0E9);
				ok = TRUE;
			}
		}
	}

	return ok ? 0 : -1;
}
#endif

static int pthread_cond_init(pthread_cond_t *cv, const void *unused)
{
	(void)unused;
	InitializeCriticalSection(&cv->threadIdSec);
	cv->waitingthreadcount = 0;
	cv->waitingthreadhdls =
	    (pthread_t *)mg_calloc(MAX_WORKER_THREADS, sizeof(pthread_t));
	return (cv->waitingthreadhdls != NULL) ? 0 : -1;
}

static int pthread_cond_timedwait(pthread_cond_t *cv,
                                  pthread_mutex_t *mutex,
                                  const struct timespec *abstime)
{
	struct mg_workerTLS *tls = (struct mg_workerTLS *)TlsGetValue(sTlsKey);
	int ok;
	struct timespec tsnow;
	int64_t nsnow, nswaitabs, nswaitrel;
	DWORD mswaitrel;

	EnterCriticalSection(&cv->threadIdSec);
	assert(cv->waitingthreadcount < MAX_WORKER_THREADS);
	cv->waitingthreadhdls[cv->waitingthreadcount] =
	    tls->pthread_cond_helper_mutex;
	cv->waitingthreadcount++;
	LeaveCriticalSection(&cv->threadIdSec);

	if (abstime) {
		clock_gettime(CLOCK_REALTIME, &tsnow);
		nsnow = (((int64_t)tsnow.tv_sec) * 1000000000) + tsnow.tv_nsec;
		nswaitabs =
		    (((int64_t)abstime->tv_sec) * 1000000000) + abstime->tv_nsec;
		nswaitrel = nswaitabs - nsnow;
		if (nswaitrel < 0) {
			nswaitrel = 0;
		}
		mswaitrel = (DWORD)(nswaitrel / 1000000);
	} else {
		mswaitrel = INFINITE;
	}

	pthread_mutex_unlock(mutex);
	ok = (WAIT_OBJECT_0 ==
	      WaitForSingleObject(tls->pthread_cond_helper_mutex, mswaitrel));
	pthread_mutex_lock(mutex);

	return ok ? 0 : -1;
}

static int pthread_cond_wait(pthread_cond_t *cv, pthread_mutex_t *mutex)
{
	return pthread_cond_timedwait(cv, mutex, NULL);
}

static int pthread_cond_signal(pthread_cond_t *cv)
{
	int i;
	HANDLE wkup = NULL;
	BOOL ok = FALSE;

	EnterCriticalSection(&cv->threadIdSec);
	if (cv->waitingthreadcount) {
		wkup = cv->waitingthreadhdls[0];
		ok = SetEvent(wkup);

		for (i = 1; i < cv->waitingthreadcount; i++) {
			cv->waitingthreadhdls[i - 1] = cv->waitingthreadhdls[i];
		}
		cv->waitingthreadcount--;

		assert(ok);
	}
	LeaveCriticalSection(&cv->threadIdSec);

	return ok ? 0 : 1;
}

static int pthread_cond_broadcast(pthread_cond_t *cv)
{
	EnterCriticalSection(&cv->threadIdSec);
	while (cv->waitingthreadcount) {
		pthread_cond_signal(cv);
	}
	LeaveCriticalSection(&cv->threadIdSec);

	return 0;
}

static int pthread_cond_destroy(pthread_cond_t *cv)
{
	EnterCriticalSection(&cv->threadIdSec);
	assert(cv->waitingthreadcount == 0);
	mg_free(cv->waitingthreadhdls);
	cv->waitingthreadhdls = 0;
	LeaveCriticalSection(&cv->threadIdSec);
	DeleteCriticalSection(&cv->threadIdSec);

	return 0;
}

/* For Windows, change all slashes to backslashes in path names. */
static void change_slashes_to_backslashes(char *path)
{
	int i;

	for (i = 0; path[i] != '\0'; i++) {
		if (path[i] == '/') {
			path[i] = '\\';
		}

		/* remove double backslash (check i > 0 to preserve UNC paths,
		 * like \\server\file.txt) */
		if ((path[i] == '\\') && (i > 0)) {
			while (path[i + 1] == '\\' || path[i + 1] == '/') {
				(void)memmove(path + i + 1, path + i + 2, strlen(path + i + 1));
			}
		}
	}
}

/* Encode 'path' which is assumed UTF-8 string, into UNICODE string.
 * wbuf and wbuf_len is a target buffer and its length. */
static void to_unicode(const char *path, wchar_t *wbuf, size_t wbuf_len)
{
	char buf[PATH_MAX], buf2[PATH_MAX];

	mg_strlcpy(buf, path, sizeof(buf));
	change_slashes_to_backslashes(buf);

	/* Convert to Unicode and back. If doubly-converted string does not
	 * match the original, something is fishy, reject. */
	memset(wbuf, 0, wbuf_len * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, buf, -1, wbuf, (int)wbuf_len);
	WideCharToMultiByte(
	    CP_UTF8, 0, wbuf, (int)wbuf_len, buf2, sizeof(buf2), NULL, NULL);
	if (strcmp(buf, buf2) != 0) {
		wbuf[0] = L'\0';
	}
}

#if defined(_WIN32_WCE)
static time_t time(time_t *ptime)
{
	time_t t;
	SYSTEMTIME st;
	FILETIME ft;

	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	t = SYS2UNIX_TIME(ft.dwLowDateTime, ft.dwHighDateTime);

	if (ptime != NULL) {
		*ptime = t;
	}

	return t;
}

static struct tm *localtime(const time_t *ptime, struct tm *ptm)
{
	int64_t t = ((int64_t)*ptime) * RATE_DIFF + EPOCH_DIFF;
	FILETIME ft, lft;
	SYSTEMTIME st;
	TIME_ZONE_INFORMATION tzinfo;

	if (ptm == NULL) {
		return NULL;
	}

	*(int64_t *)&ft = t;
	FileTimeToLocalFileTime(&ft, &lft);
	FileTimeToSystemTime(&lft, &st);
	ptm->tm_year = st.wYear - 1900;
	ptm->tm_mon = st.wMonth - 1;
	ptm->tm_wday = st.wDayOfWeek;
	ptm->tm_mday = st.wDay;
	ptm->tm_hour = st.wHour;
	ptm->tm_min = st.wMinute;
	ptm->tm_sec = st.wSecond;
	ptm->tm_yday = 0; /* hope nobody uses this */
	ptm->tm_isdst =
	    GetTimeZoneInformation(&tzinfo) == TIME_ZONE_ID_DAYLIGHT ? 1 : 0;

	return ptm;
}

static struct tm *gmtime(const time_t *ptime, struct tm *ptm)
{
	/* FIXME(lsm): fix this. */
	return localtime(ptime, ptm);
}

static size_t
strftime(char *dst, size_t dst_size, const char *fmt, const struct tm *tm)
{
	(void)snprintf(dst, dst_size, "implement strftime() for WinCE");
	return 0;
}
#endif

/* Windows happily opens files with some garbage at the end of file name.
 * For example, fopen("a.cgi    ", "r") on Windows successfully opens
 * "a.cgi", despite one would expect an error back.
 * This function returns non-0 if path ends with some garbage. */
static int path_cannot_disclose_cgi(const char *path)
{
	static const char *allowed_last_characters = "_-";
	int last = path[strlen(path) - 1];
	return isalnum(last) || strchr(allowed_last_characters, last) != NULL;
}

static int
mg_stat(struct mg_connection *conn, const char *path, struct file *filep)
{
	wchar_t wbuf[PATH_MAX];
	WIN32_FILE_ATTRIBUTE_DATA info;
	time_t creation_time;

	if (!filep) {
		return 0;
	}
	memset(filep, 0, sizeof(*filep));

	if (conn && is_file_in_memory(conn, path, filep)) {
		return 1;
	}

	to_unicode(path, wbuf, ARRAY_SIZE(wbuf));
	if (GetFileAttributesExW(wbuf, GetFileExInfoStandard, &info) != 0) {
		filep->size = MAKEUQUAD(info.nFileSizeLow, info.nFileSizeHigh);
		filep->last_modified =
		    SYS2UNIX_TIME(info.ftLastWriteTime.dwLowDateTime,
		                  info.ftLastWriteTime.dwHighDateTime);

		/* On Windows, the file creation time can be higher than the
		 * modification time, e.g. when a file is copied.
		 * Since the Last-Modified timestamp is used for caching
		 * it should be based on the most recent timestamp. */
		creation_time = SYS2UNIX_TIME(info.ftCreationTime.dwLowDateTime,
		                              info.ftCreationTime.dwHighDateTime);
		if (creation_time > filep->last_modified) {
			filep->last_modified = creation_time;
		}

		filep->is_directory = info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
		/* If file name is fishy, reset the file structure and return
		 * error.
		 * Note it is important to reset, not just return the error, cause
		 * functions like is_file_opened() check the struct. */
		if (!filep->is_directory && !path_cannot_disclose_cgi(path)) {
			memset(filep, 0, sizeof(*filep));
			return 0;
		}

		return 1;
	}

	return 0;
}

static int mg_remove(const char *path)
{
	wchar_t wbuf[PATH_MAX];
	to_unicode(path, wbuf, ARRAY_SIZE(wbuf));
	return DeleteFileW(wbuf) ? 0 : -1;
}

static int mg_mkdir(const char *path, int mode)
{
	char buf[PATH_MAX];
	wchar_t wbuf[PATH_MAX];

	(void)mode;
	mg_strlcpy(buf, path, sizeof(buf));
	change_slashes_to_backslashes(buf);

	(void)MultiByteToWideChar(CP_UTF8, 0, buf, -1, wbuf, ARRAY_SIZE(wbuf));

	return CreateDirectoryW(wbuf, NULL) ? 0 : -1;
}

/* Implementation of POSIX opendir/closedir/readdir for Windows. */
static DIR *opendir(const char *name)
{
	DIR *dir = NULL;
	wchar_t wpath[PATH_MAX];
	DWORD attrs;

	if (name == NULL) {
		SetLastError(ERROR_BAD_ARGUMENTS);
	} else if ((dir = (DIR *)mg_malloc(sizeof(*dir))) == NULL) {
		SetLastError(ERROR_NOT_ENOUGH_MEMORY);
	} else {
		to_unicode(name, wpath, ARRAY_SIZE(wpath));
		attrs = GetFileAttributesW(wpath);
		if (attrs != 0xFFFFFFFF &&
		    ((attrs & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)) {
			(void)wcscat(wpath, L"\\*");
			dir->handle = FindFirstFileW(wpath, &dir->info);
			dir->result.d_name[0] = '\0';
		} else {
			mg_free(dir);
			dir = NULL;
		}
	}

	return dir;
}

static int closedir(DIR *dir)
{
	int result = 0;

	if (dir != NULL) {
		if (dir->handle != INVALID_HANDLE_VALUE)
			result = FindClose(dir->handle) ? 0 : -1;

		mg_free(dir);
	} else {
		result = -1;
		SetLastError(ERROR_BAD_ARGUMENTS);
	}

	return result;
}

static struct dirent *readdir(DIR *dir)
{
	struct dirent *result = 0;

	if (dir) {
		if (dir->handle != INVALID_HANDLE_VALUE) {
			result = &dir->result;
			(void)WideCharToMultiByte(CP_UTF8,
			                          0,
			                          dir->info.cFileName,
			                          -1,
			                          result->d_name,
			                          sizeof(result->d_name),
			                          NULL,
			                          NULL);

			if (!FindNextFileW(dir->handle, &dir->info)) {
				(void)FindClose(dir->handle);
				dir->handle = INVALID_HANDLE_VALUE;
			}

		} else {
			SetLastError(ERROR_FILE_NOT_FOUND);
		}
	} else {
		SetLastError(ERROR_BAD_ARGUMENTS);
	}

	return result;
}

#ifndef HAVE_POLL
static int poll(struct pollfd *pfd, unsigned int n, int milliseconds)
{
	struct timeval tv;
	fd_set set;
	unsigned int i;
	int result;
	SOCKET maxfd = 0;

	tv.tv_sec = milliseconds / 1000;
	tv.tv_usec = (milliseconds % 1000) * 1000;
	FD_ZERO(&set);

	for (i = 0; i < n; i++) {
		FD_SET((SOCKET)pfd[i].fd, &set);
		pfd[i].revents = 0;

		if (pfd[i].fd > maxfd) {
			maxfd = pfd[i].fd;
		}
	}

	if ((result = select((int)maxfd + 1, &set, NULL, NULL, &tv)) > 0) {
		for (i = 0; i < n; i++) {
			if (FD_ISSET(pfd[i].fd, &set)) {
				pfd[i].revents = POLLIN;
			}
		}
	}

	return result;
}
#endif /* HAVE_POLL */

static void set_close_on_exec(SOCKET sock,
                              struct mg_connection *conn /* may be null */)
{
	(void)conn; /* Unused. */
	(void)SetHandleInformation((HANDLE)(intptr_t)sock, HANDLE_FLAG_INHERIT, 0);
}

int mg_start_thread(mg_thread_func_t f, void *p)
{
#if defined(USE_STACK_SIZE) && (USE_STACK_SIZE > 1)
	/* Compile-time option to control stack size, e.g. -DUSE_STACK_SIZE=16384
	 */
	return ((_beginthread((void(__cdecl *)(void *))f, USE_STACK_SIZE, p) ==
	         ((uintptr_t)(-1L)))
	            ? -1
	            : 0);
#else
	return (
	    (_beginthread((void(__cdecl *)(void *))f, 0, p) == ((uintptr_t)(-1L)))
	        ? -1
	        : 0);
#endif /* defined(USE_STACK_SIZE) && (USE_STACK_SIZE > 1) */
}

/* Start a thread storing the thread context. */

static int mg_start_thread_with_id(unsigned(__stdcall *f)(void *),
                                   void *p,
                                   pthread_t *threadidptr)
{
	uintptr_t uip;
	HANDLE threadhandle;
	int result = -1;

	uip = _beginthreadex(NULL, 0, (unsigned(__stdcall *)(void *))f, p, 0, NULL);
	threadhandle = (HANDLE)uip;
	if ((uip != (uintptr_t)(-1L)) && (threadidptr != NULL)) {
		*threadidptr = threadhandle;
		result = 0;
	}

	return result;
}

/* Wait for a thread to finish. */

static int mg_join_thread(pthread_t threadid)
{
	int result;
	DWORD dwevent;

	result = -1;
	dwevent = WaitForSingleObject(threadid, INFINITE);
	if (dwevent == WAIT_FAILED) {
		DEBUG_TRACE("WaitForSingleObject() failed, error %d", ERRNO);
	} else {
		if (dwevent == WAIT_OBJECT_0) {
			CloseHandle(threadid);
			result = 0;
		}
	}

	return result;
}

static HANDLE dlopen(const char *dll_name, int flags)
{
	wchar_t wbuf[PATH_MAX];
	(void)flags;
	to_unicode(dll_name, wbuf, ARRAY_SIZE(wbuf));
	return LoadLibraryW(wbuf);
}

static int dlclose(void *handle)
{
	int result;

	if (FreeLibrary((HMODULE)handle) != 0) {
		result = 0;
	} else {
		result = -1;
	}

	return result;
}

#if !defined(NO_CGI)
#define SIGKILL (0)
static int kill(pid_t pid, int sig_num)
{
	(void)TerminateProcess((HANDLE)pid, (UINT)sig_num);
	(void)CloseHandle((HANDLE)pid);
	return 0;
}

static void trim_trailing_whitespaces(char *s)
{
	char *e = s + strlen(s) - 1;
	while (e > s && isspace(*(unsigned char *)e)) {
		*e-- = '\0';
	}
}

static pid_t spawn_process(struct mg_connection *conn,
                           const char *prog,
                           char *envblk,
                           char *envp[],
                           int fdin,
                           int fdout,
                           const char *dir)
{
	HANDLE me;
	char *p, *interp, full_interp[PATH_MAX], full_dir[PATH_MAX],
	    cmdline[PATH_MAX], buf[PATH_MAX];
	struct file file = STRUCT_FILE_INITIALIZER;
	STARTUPINFOA si;
	PROCESS_INFORMATION pi = {0};

	(void)envp;

	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);

	/* TODO(lsm, mid): redirect CGI errors to the error log file */
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	me = GetCurrentProcess();
	DuplicateHandle(me,
	                (HANDLE)_get_osfhandle(fdin),
	                me,
	                &si.hStdInput,
	                0,
	                TRUE,
	                DUPLICATE_SAME_ACCESS);
	DuplicateHandle(me,
	                (HANDLE)_get_osfhandle(fdout),
	                me,
	                &si.hStdOutput,
	                0,
	                TRUE,
	                DUPLICATE_SAME_ACCESS);

	/* If CGI file is a script, try to read the interpreter line */
	interp = conn->ctx->config[CGI_INTERPRETER];
	if (interp == NULL) {
		buf[0] = buf[1] = '\0';

		/* Read the first line of the script into the buffer */
		snprintf(cmdline, sizeof(cmdline), "%s%c%s", dir, '/', prog);
		if (mg_fopen(conn, cmdline, "r", &file)) {
			p = (char *)file.membuf;
			mg_fgets(buf, sizeof(buf), &file, &p);
			mg_fclose(&file);
			buf[sizeof(buf) - 1] = '\0';
		}

		if (buf[0] == '#' && buf[1] == '!') {
			trim_trailing_whitespaces(buf + 2);
		} else {
			buf[2] = '\0';
		}
		interp = buf + 2;
	}

	if (interp[0] != '\0') {
		GetFullPathNameA(interp, sizeof(full_interp), full_interp, NULL);
		interp = full_interp;
	}
	GetFullPathNameA(dir, sizeof(full_dir), full_dir, NULL);

	if (interp[0] != '\0') {
		mg_snprintf(conn,
		            cmdline,
		            sizeof(cmdline),
		            "\"%s\" \"%s\\%s\"",
		            interp,
		            full_dir,
		            prog);
	} else {
		mg_snprintf(
		    conn, cmdline, sizeof(cmdline), "\"%s\\%s\"", full_dir, prog);
	}

	DEBUG_TRACE("Running [%s]", cmdline);
	if (CreateProcessA(NULL,
	                   cmdline,
	                   NULL,
	                   NULL,
	                   TRUE,
	                   CREATE_NEW_PROCESS_GROUP,
	                   envblk,
	                   NULL,
	                   &si,
	                   &pi) == 0) {
		mg_cry(
		    conn, "%s: CreateProcess(%s): %ld", __func__, cmdline, (long)ERRNO);
		pi.hProcess = (pid_t)-1;
	}

	(void)CloseHandle(si.hStdOutput);
	(void)CloseHandle(si.hStdInput);
	if (pi.hThread != NULL) {
		(void)CloseHandle(pi.hThread);
	}

	return (pid_t)pi.hProcess;
}
#endif /* !NO_CGI */

static int set_non_blocking_mode(SOCKET sock)
{
	unsigned long on = 1;
	return ioctlsocket(sock, (long)FIONBIO, &on);
}

#else
static int
mg_stat(struct mg_connection *conn, const char *path, struct file *filep)
{
	struct stat st;
	if (!filep) {
		return 0;
	}
	memset(filep, 0, sizeof(*filep));

	if (conn && is_file_in_memory(conn, path, filep)) {
		return 1;
	}

	if (0 == stat(path, &st)) {
		filep->size = (uint64_t)(st.st_size);
		filep->last_modified = st.st_mtime;
		filep->is_directory = S_ISDIR(st.st_mode);
		return 1;
	}

	return 0;
}

static void set_close_on_exec(SOCKET fd,
                              struct mg_connection *conn /* may be null */)
{
	if (fcntl(fd, F_SETFD, FD_CLOEXEC) != 0) {
		if (conn) {
			mg_cry(conn,
			       "%s: fcntl(F_SETFD FD_CLOEXEC) failed: %s",
			       __func__,
			       strerror(ERRNO));
		}
	}
}

int mg_start_thread(mg_thread_func_t func, void *param)
{
	pthread_t thread_id;
	pthread_attr_t attr;
	int result;

	(void)pthread_attr_init(&attr);
	(void)pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

#if defined(USE_STACK_SIZE) && (USE_STACK_SIZE > 1)
	/* Compile-time option to control stack size,
	 * e.g. -DUSE_STACK_SIZE=16384 */
	(void)pthread_attr_setstacksize(&attr, USE_STACK_SIZE);
#endif /* defined(USE_STACK_SIZE) && (USE_STACK_SIZE > 1) */

	result = pthread_create(&thread_id, &attr, func, param);
	pthread_attr_destroy(&attr);

	return result;
}

/* Start a thread storing the thread context. */

static int mg_start_thread_with_id(mg_thread_func_t func,
                                   void *param,
                                   pthread_t *threadidptr)
{
	pthread_t thread_id;
	pthread_attr_t attr;
	int result;

	(void)pthread_attr_init(&attr);

#if defined(USE_STACK_SIZE) && (USE_STACK_SIZE > 1)
	/* Compile-time option to control stack size,
	 * e.g. -DUSE_STACK_SIZE=16384 */
	(void)pthread_attr_setstacksize(&attr, USE_STACK_SIZE);
#endif /* defined(USE_STACK_SIZE) && USE_STACK_SIZE > 1 */

	result = pthread_create(&thread_id, &attr, func, param);
	pthread_attr_destroy(&attr);
	if ((result == 0) && (threadidptr != NULL)) {
		*threadidptr = thread_id;
	}
	return result;
}

/* Wait for a thread to finish. */

static int mg_join_thread(pthread_t threadid)
{
	int result;

	result = pthread_join(threadid, NULL);
	return result;
}

#ifndef NO_CGI
static pid_t spawn_process(struct mg_connection *conn,
                           const char *prog,
                           char *envblk,
                           char *envp[],
                           int fdin,
                           int fdout,
                           const char *dir)
{
	pid_t pid;
	const char *interp;

	(void)envblk;

	if (conn == NULL) {
		return 0;
	}

	if ((pid = fork()) == -1) {
		/* Parent */
		send_http_error(conn,
		                500,
		                "Error: Creating CGI process\nfork(): %s",
		                strerror(ERRNO));
	} else if (pid == 0) {
		/* Child */
		if (chdir(dir) != 0) {
			mg_cry(conn, "%s: chdir(%s): %s", __func__, dir, strerror(ERRNO));
		} else if (dup2(fdin, 0) == -1) {
			mg_cry(
			    conn, "%s: dup2(%d, 0): %s", __func__, fdin, strerror(ERRNO));
		} else if (dup2(fdout, 1) == -1) {
			mg_cry(
			    conn, "%s: dup2(%d, 1): %s", __func__, fdout, strerror(ERRNO));
		} else {
			/* Not redirecting stderr to stdout, to avoid output being littered
			 * with the error messages. */
			(void)close(fdin);
			(void)close(fdout);

			/* After exec, all signal handlers are restored to their default
			 * values, with one exception of SIGCHLD. According to
			 * POSIX.1-2001 and Linux's implementation, SIGCHLD's handler will
			 * leave unchanged after exec if it was set to be ignored. Restore
			 * it to default action. */
			signal(SIGCHLD, SIG_DFL);

			interp = conn->ctx->config[CGI_INTERPRETER];
			if (interp == NULL) {
				(void)execle(prog, prog, NULL, envp);
				mg_cry(conn,
				       "%s: execle(%s): %s",
				       __func__,
				       prog,
				       strerror(ERRNO));
			} else {
				(void)execle(interp, interp, prog, NULL, envp);
				mg_cry(conn,
				       "%s: execle(%s %s): %s",
				       __func__,
				       interp,
				       prog,
				       strerror(ERRNO));
			}
		}
		exit(EXIT_FAILURE);
	}

	return pid;
}
#endif /* !NO_CGI */

static int set_non_blocking_mode(SOCKET sock)
{
	int flags;

	flags = fcntl(sock, F_GETFL, 0);
	(void)fcntl(sock, F_SETFL, flags | O_NONBLOCK);

	return 0;
}
#endif /* _WIN32 */

/* Write data to the IO channel - opened file descriptor, socket or SSL
 * descriptor. Return number of bytes written. */
static int push(struct mg_context *ctx,
                FILE *fp,
                SOCKET sock,
                SSL *ssl,
                const char *buf,
                int len,
                double timeout)
{
	struct timespec start, now;
	int n;

#ifdef _WIN32
	typedef int len_t;
#else
	typedef size_t len_t;
#endif

	if (timeout > 0) {
		memset(&start, 0, sizeof(start));
		memset(&now, 0, sizeof(now));
		clock_gettime(CLOCK_MONOTONIC, &start);
	}

	if (ctx == NULL) {
		return -1;
	}

	do {

#ifndef NO_SSL
		if (ssl != NULL) {
			n = SSL_write(ssl, buf, len);
		} else
#endif
		    if (fp != NULL) {
			n = (int)fwrite(buf, 1, (size_t)len, fp);
			if (ferror(fp)) {
				n = -1;
			}
		} else {
			n = (int)send(sock, buf, (len_t)len, MSG_NOSIGNAL);
		}

		if (ctx->stop_flag) {
			return -1;
		}

		if ((n > 0) || (n == 0 && len == 0)) {
			/* some data has been read, or no data was requested */
			return n;
		}
		if (n == 0) {
			/* shutdown of the socket at client side */
			return -1;
		}
		if (n < 0) {
			/* socket error - check errno */
			int err = ERRNO;
			DEBUG_TRACE("send() failed, error %d", err);
			(void)err; /* TODO: error handling depending on the error code.
			            * These codes are different between Windows and Linux.
			            */
			return -1;
		}
		if (timeout > 0) {
			clock_gettime(CLOCK_MONOTONIC, &now);
		}
	} while ((timeout <= 0) || (mg_difftimespec(&now, &start) <= timeout));

	return -1;
}

static int64_t push_all(struct mg_context *ctx,
                        FILE *fp,
                        SOCKET sock,
                        SSL *ssl,
                        const char *buf,
                        int64_t len)
{
	double timeout = -1.0;
	int64_t n, nwritten = 0;

	if (ctx == NULL) {
		return -1;
	}

	if (ctx->config[REQUEST_TIMEOUT]) {
		timeout = atoi(ctx->config[REQUEST_TIMEOUT]) / 1000.0;
	}

	while (len > 0 && ctx->stop_flag == 0) {
		n = push(ctx, fp, sock, ssl, buf + nwritten, (int)len, timeout);
		if (n < 0) {
			nwritten = n; /* Propagate the error */
			break;
		} else if (n == 0) {
			break; /* No more data to write */
		} else {
			nwritten += n;
			len -= n;
		}
	}

	return nwritten;
}


/* Read from IO channel - opened file descriptor, socket, or SSL descriptor.
 * Return negative value on error, or number of bytes read on success. */
static int
pull(FILE *fp, struct mg_connection *conn, char *buf, int len, double timeout)
{
	int nread;
	struct timespec start, now;

#ifdef _WIN32
	typedef int len_t;
#else
	typedef size_t len_t;
#endif

	if (timeout > 0) {
		memset(&start, 0, sizeof(start));
		memset(&now, 0, sizeof(now));
		clock_gettime(CLOCK_MONOTONIC, &start);
	}

	do {
		if (fp != NULL) {
			/* Use read() instead of fread(), because if we're reading from the
			 * CGI pipe, fread() may block until IO buffer is filled up. We
			 * cannot afford to block and must pass all read bytes immediately
			 * to the client. */
			nread = (int)read(fileno(fp), buf, (size_t)len);
#ifndef NO_SSL
		} else if (conn->ssl != NULL) {
			nread = SSL_read(conn->ssl, buf, len);
#endif
		} else {
			nread = (int)recv(conn->client.sock, buf, (len_t)len, 0);
		}
		if (conn->ctx->stop_flag) {
			return -1;
		}

		if ((nread > 0) || (nread == 0 && len == 0)) {
			/* some data has been read, or no data was requested */
			return nread;
		}
		if (nread == 0) {
			/* shutdown of the socket at client side */
			return -1;
		}
		if (nread < 0) {
			/* socket error - check errno */
			int err = ERRNO;
#ifdef _WIN32
			if (err == WSAEWOULDBLOCK) {
				/* standard case if called from close_socket_gracefully */
				return -1;
			} else if (err == WSAETIMEDOUT) {
				/* timeout is handled by the while loop  */
			} else {
				DEBUG_TRACE("recv() failed, error %d", err);
				return -1;
			}
#else
			/* TODO: POSIX returns either EAGAIN or EWOULDBLOCK in both cases,
			 * if the timeout is reached and if the socket was set to non-
			 * blocking in close_socket_gracefully, so we can not distinguish
			 * here. We have to wait for the timeout in both cases for now.
			 */
			if (err == EAGAIN || err == EWOULDBLOCK) {
				/* standard case if called from close_socket_gracefully
				 * => should return -1 */
				/* or timeout occured
				 * => the code must stay in the while loop */
			} else {
				DEBUG_TRACE("recv() failed, error %d", err);
				return -1;
			}
#endif
		}
		if (timeout > 0) {
			clock_gettime(CLOCK_MONOTONIC, &now);
		}
	} while ((timeout <= 0) || (mg_difftimespec(&now, &start) <= timeout));

	/* Timeout occured, but no data available. */
	return -1;
}


static int pull_all(FILE *fp, struct mg_connection *conn, char *buf, int len)
{
	int n, nread = 0;
	double timeout = -1.0;

	if (conn->ctx->config[REQUEST_TIMEOUT]) {
		timeout = atoi(conn->ctx->config[REQUEST_TIMEOUT]) / 1000.0;
	}

	while (len > 0 && conn->ctx->stop_flag == 0) {
		n = pull(fp, conn, buf + nread, len, timeout);
		if (n < 0) {
			nread = n; /* Propagate the error */
			break;
		} else if (n == 0) {
			break; /* No more data to read */
		} else {
			conn->consumed_content += n;
			nread += n;
			len -= n;
		}
	}

	return nread;
}

static void discard_unread_request_data(struct mg_connection *conn)
{
	char buf[MG_BUF_LEN];
	size_t to_read;
	int nread;

	if (conn == NULL) {
		return;
	}

	to_read = sizeof(buf);

	if (conn->is_chunked) {
		/* Chunked encoding: 1=chunk not read completely, 2=chunk read
		 * completely */
		while (conn->is_chunked == 1) {
			nread = mg_read(conn, buf, to_read);
			if (nread <= 0) {
				break;
			}
		}

	} else {
		/* Not chunked: content length is known */
		while (conn->consumed_content < conn->content_len) {
			if (to_read >
			    (size_t)(conn->content_len - conn->consumed_content)) {
				to_read = (size_t)(conn->content_len - conn->consumed_content);
			}

			nread = mg_read(conn, buf, to_read);
			if (nread <= 0) {
				break;
			}
		}
	}
}

static int mg_read_inner(struct mg_connection *conn, void *buf, size_t len)
{
	int64_t n, buffered_len, nread;
	int64_t len64 =
	    (int64_t)(len > INT_MAX ? INT_MAX : len); /* since the return value is
	                                               * int, we may not read more
	                                               * bytes */
	const char *body;

	if (conn == NULL) {
		return 0;
	}

	/* If Content-Length is not set for a PUT or POST request, read until
	 * socket is closed */
	if (conn->consumed_content == 0 && conn->content_len == -1) {
		conn->content_len = INT64_MAX;
		conn->must_close = 1;
	}

	nread = 0;
	if (conn->consumed_content < conn->content_len) {
		/* Adjust number of bytes to read. */
		int64_t left_to_read = conn->content_len - conn->consumed_content;
		if (left_to_read < len64) {
			/* Do not reade more than the total content length of the request.
			 */
			len64 = left_to_read;
		}

		/* Return buffered data */
		buffered_len = (int64_t)(conn->data_len) - (int64_t)conn->request_len -
		               conn->consumed_content;
		if (buffered_len > 0) {
			if (len64 < buffered_len) {
				buffered_len = len64;
			}
			body = conn->buf + conn->request_len + conn->consumed_content;
			memcpy(buf, body, (size_t)buffered_len);
			len64 -= buffered_len;
			conn->consumed_content += buffered_len;
			nread += buffered_len;
			buf = (char *)buf + buffered_len;
		}

		/* We have returned all buffered data. Read new data from the remote
		 * socket.
		 */
		if ((n = pull_all(NULL, conn, (char *)buf, (int)len64)) >= 0) {
			nread += n;
		} else {
			nread = (nread > 0 ? nread : n);
		}
	}
	return (int)nread;
}

static char mg_getc(struct mg_connection *conn)
{
	char c;
	if (conn == NULL) {
		return 0;
	}
	conn->content_len++;
	if (mg_read_inner(conn, &c, 1) <= 0) {
		return (char)0;
	}
	return c;
}

int mg_read(struct mg_connection *conn, void *buf, size_t len)
{
	if (len > INT_MAX) {
		len = INT_MAX;
	}

	if (conn == NULL) {
		return 0;
	}

	if (conn->is_chunked) {
		size_t all_read = 0;
		while (len > 0) {
			if (conn->chunk_remainder) {
				/* copy from the remainder of the last received chunk */
				long read_ret;
				size_t read_now =
				    ((conn->chunk_remainder > len) ? (len)
				                                   : (conn->chunk_remainder));

				conn->content_len += (int)read_now;
				read_ret =
				    mg_read_inner(conn, (char *)buf + all_read, read_now);
				all_read += (size_t)read_ret;

				conn->chunk_remainder -= read_now;
				len -= read_now;

				if (conn->chunk_remainder == 0) {
					/* the rest of the data in the current chunk has been read
					 */
					if ((mg_getc(conn) != '\r') || (mg_getc(conn) != '\n')) {
						/* Protocol violation */
						return -1;
					}
				}

			} else {
				/* fetch a new chunk */
				int i = 0;
				char lenbuf[64];
				char *end = 0;
				unsigned long chunkSize = 0;

				for (i = 0; i < ((int)sizeof(lenbuf) - 1); i++) {
					lenbuf[i] = mg_getc(conn);
					if (i > 0 && lenbuf[i] == '\r' && lenbuf[i - 1] != '\r') {
						continue;
					}
					if (i > 1 && lenbuf[i] == '\n' && lenbuf[i - 1] == '\r') {
						lenbuf[i + 1] = 0;
						chunkSize = strtoul(lenbuf, &end, 16);
						break;
					}
					if (!isalnum(lenbuf[i])) {
						/* illegal character for chunk length */
						return -1;
					}
				}
				if ((end == NULL) || (*end != '\r')) {
					/* chunksize not set correctly */
					return -1;
				}

				conn->chunk_remainder = chunkSize;
				if (chunkSize == 0) {
					/* regular end of content */
					conn->is_chunked = 2;
					break;
				}
			}
		}

		return (int)all_read;
	}
	return mg_read_inner(conn, buf, len);
}

int mg_write(struct mg_connection *conn, const void *buf, size_t len)
{
	time_t now;
	int64_t n, total, allowed;

	if (conn == NULL) {
		return 0;
	}

	if (conn->throttle > 0) {
		if ((now = time(NULL)) != conn->last_throttle_time) {
			conn->last_throttle_time = now;
			conn->last_throttle_bytes = 0;
		}
		allowed = conn->throttle - conn->last_throttle_bytes;
		if (allowed > (int64_t)len) {
			allowed = (int64_t)len;
		}
		if ((total = push_all(conn->ctx,
		                      NULL,
		                      conn->client.sock,
		                      conn->ssl,
		                      (const char *)buf,
		                      (int64_t)allowed)) == allowed) {
			buf = (char *)buf + total;
			conn->last_throttle_bytes += total;
			while (total < (int64_t)len && conn->ctx->stop_flag == 0) {
				allowed = conn->throttle > (int64_t)len - total
				              ? (int64_t)len - total
				              : conn->throttle;
				if ((n = push_all(conn->ctx,
				                  NULL,
				                  conn->client.sock,
				                  conn->ssl,
				                  (const char *)buf,
				                  (int64_t)allowed)) != allowed) {
					break;
				}
				sleep(1);
				conn->last_throttle_bytes = allowed;
				conn->last_throttle_time = time(NULL);
				buf = (char *)buf + n;
				total += n;
			}
		}
	} else {
		total = push_all(conn->ctx,
		                 NULL,
		                 conn->client.sock,
		                 conn->ssl,
		                 (const char *)buf,
		                 (int64_t)len);
	}
	return (int)total;
}

/* Alternative alloc_vprintf() for non-compliant C runtimes */
static int alloc_vprintf2(char **buf, const char *fmt, va_list ap)
{
	va_list ap_copy;
	size_t size = MG_BUF_LEN;
	int len = -1;

	*buf = NULL;
	while (len == -1) {
		if (*buf) {
			mg_free(*buf);
		}
		*buf = (char *)mg_malloc(size *= 4);
		if (!*buf) {
			break;
		}
		va_copy(ap_copy, ap);
		len = vsnprintf(*buf, size, fmt, ap_copy);
		va_end(ap_copy);
	}

	return len;
}

/* Print message to buffer. If buffer is large enough to hold the message,
 * return buffer. If buffer is to small, allocate large enough buffer on heap,
 * and return allocated buffer. */
static int alloc_vprintf(char **buf, size_t size, const char *fmt, va_list ap)
{
	va_list ap_copy;
	int len;

	/* Windows is not standard-compliant, and vsnprintf() returns -1 if
	 * buffer is too small. Also, older versions of msvcrt.dll do not have
	 * _vscprintf().  However, if size is 0, vsnprintf() behaves correctly.
	 * Therefore, we make two passes: on first pass, get required message
	 * length.
	 * On second pass, actually print the message. */
	va_copy(ap_copy, ap);
	len = vsnprintf(NULL, 0, fmt, ap_copy);
	va_end(ap_copy);

	if (len < 0) {
		/* C runtime is not standard compliant, vsnprintf() returned -1.
		 * Switch to alternative code path that uses incremental allocations.
		*/
		va_copy(ap_copy, ap);
		len = alloc_vprintf2(buf, fmt, ap);
		va_end(ap_copy);
	} else if ((size_t)(len) > size && (size = (size_t)(len) + 1) > 0 &&
	           (*buf = (char *)mg_malloc(size)) == NULL) {
		len = -1; /* Allocation failed, mark failure */
	} else {
		va_copy(ap_copy, ap);
		IGNORE_UNUSED_RESULT(vsnprintf(*buf, size, fmt, ap_copy));
		va_end(ap_copy);
	}

	return len;
}

static int mg_vprintf(struct mg_connection *conn, const char *fmt, va_list ap)
{
	char mem[MG_BUF_LEN], *buf = mem;
	int len;

	if ((len = alloc_vprintf(&buf, sizeof(mem), fmt, ap)) > 0) {
		len = mg_write(conn, buf, (size_t)len);
	}
	if (buf != mem && buf != NULL) {
		mg_free(buf);
	}

	return len;
}

int mg_printf(struct mg_connection *conn, const char *fmt, ...)
{
	va_list ap;
	int result;

	va_start(ap, fmt);
	result = mg_vprintf(conn, fmt, ap);
	va_end(ap);

	return result;
}

int mg_url_decode(const char *src,
                  int src_len,
                  char *dst,
                  int dst_len,
                  int is_form_url_encoded)
{
	int i, j, a, b;
#define HEXTOI(x) (isdigit(x) ? x - '0' : x - 'W')

	for (i = j = 0; i < src_len && j < dst_len - 1; i++, j++) {
		if (i < src_len - 2 && src[i] == '%' &&
		    isxdigit(*(const unsigned char *)(src + i + 1)) &&
		    isxdigit(*(const unsigned char *)(src + i + 2))) {
			a = tolower(*(const unsigned char *)(src + i + 1));
			b = tolower(*(const unsigned char *)(src + i + 2));
			dst[j] = (char)((HEXTOI(a) << 4) | HEXTOI(b));
			i += 2;
		} else if (is_form_url_encoded && src[i] == '+') {
			dst[j] = ' ';
		} else {
			dst[j] = src[i];
		}
	}

	dst[j] = '\0'; /* Null-terminate the destination */

	return i >= src_len ? j : -1;
}

int mg_get_var(const char *data,
               size_t data_len,
               const char *name,
               char *dst,
               size_t dst_len)
{
	return mg_get_var2(data, data_len, name, dst, dst_len, 0);
}

int mg_get_var2(const char *data,
                size_t data_len,
                const char *name,
                char *dst,
                size_t dst_len,
                size_t occurrence)
{
	const char *p, *e, *s;
	size_t name_len;
	int len;

	if (dst == NULL || dst_len == 0) {
		len = -2;
	} else if (data == NULL || name == NULL || data_len == 0) {
		len = -1;
		dst[0] = '\0';
	} else {
		name_len = strlen(name);
		e = data + data_len;
		len = -1;
		dst[0] = '\0';

		/* data is "var1=val1&var2=val2...". Find variable first */
		for (p = data; p + name_len < e; p++) {
			if ((p == data || p[-1] == '&') && p[name_len] == '=' &&
			    !mg_strncasecmp(name, p, name_len) && 0 == occurrence--) {
				/* Point p to variable value */
				p += name_len + 1;

				/* Point s to the end of the value */
				s = (const char *)memchr(p, '&', (size_t)(e - p));
				if (s == NULL) {
					s = e;
				}
				/* assert(s >= p); */
				if (s < p) {
					return -3;
				}

				/* Decode variable into destination buffer */
				len = mg_url_decode(p, (int)(s - p), dst, (int)dst_len, 1);

				/* Redirect error code from -1 to -2 (destination buffer too
				 * small). */
				if (len == -1) {
					len = -2;
				}
				break;
			}
		}
	}

	return len;
}

int mg_get_cookie(const char *cookie_header,
                  const char *var_name,
                  char *dst,
                  size_t dst_size)
{
	const char *s, *p, *end;
	int name_len, len = -1;

	if (dst == NULL || dst_size == 0) {
		len = -2;
	} else if (var_name == NULL || (s = cookie_header) == NULL) {
		len = -1;
		dst[0] = '\0';
	} else {
		name_len = (int)strlen(var_name);
		end = s + strlen(s);
		dst[0] = '\0';

		for (; (s = mg_strcasestr(s, var_name)) != NULL; s += name_len) {
			if (s[name_len] == '=') {
				s += name_len + 1;
				if ((p = strchr(s, ' ')) == NULL) {
					p = end;
				}
				if (p[-1] == ';') {
					p--;
				}
				if (*s == '"' && p[-1] == '"' && p > s + 1) {
					s++;
					p--;
				}
				if ((size_t)(p - s) < dst_size) {
					len = (int)(p - s);
					mg_strlcpy(dst, s, (size_t)len + 1);
				} else {
					len = -3;
				}
				break;
			}
		}
	}
	return len;
}

#if defined(USE_WEBSOCKET) || defined(USE_LUA)
static void base64_encode(const unsigned char *src, int src_len, char *dst)
{
	static const char *b64 =
	    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int i, j, a, b, c;

	for (i = j = 0; i < src_len; i += 3) {
		a = src[i];
		b = i + 1 >= src_len ? 0 : src[i + 1];
		c = i + 2 >= src_len ? 0 : src[i + 2];

		dst[j++] = b64[a >> 2];
		dst[j++] = b64[((a & 3) << 4) | (b >> 4)];
		if (i + 1 < src_len) {
			dst[j++] = b64[(b & 15) << 2 | (c >> 6)];
		}
		if (i + 2 < src_len) {
			dst[j++] = b64[c & 63];
		}
	}
	while (j % 4 != 0) {
		dst[j++] = '=';
	}
	dst[j++] = '\0';
}
#endif

#if defined(USE_LUA)
static unsigned char b64reverse(char letter)
{
	if (letter >= 'A' && letter <= 'Z') {
		return letter - 'A';
	}
	if (letter >= 'a' && letter <= 'z') {
		return letter - 'a' + 26;
	}
	if (letter >= '0' && letter <= '9') {
		return letter - '0' + 52;
	}
	if (letter == '+') {
		return 62;
	}
	if (letter == '/') {
		return 63;
	}
	if (letter == '=') {
		return 255; /* normal end */
	}
	return 254; /* error */
}

static int
base64_decode(const unsigned char *src, int src_len, char *dst, size_t *dst_len)
{
	int i;
	unsigned char a, b, c, d;

	*dst_len = 0;

	for (i = 0; i < src_len; i += 4) {
		a = b64reverse(src[i]);
		if (a >= 254) {
			return i;
		}

		b = b64reverse(i + 1 >= src_len ? 0 : src[i + 1]);
		if (b >= 254) {
			return i + 1;
		}

		c = b64reverse(i + 2 >= src_len ? 0 : src[i + 2]);
		if (c == 254) {
			return i + 2;
		}

		d = b64reverse(i + 3 >= src_len ? 0 : src[i + 3]);
		if (c == 254) {
			return i + 3;
		}

		dst[(*dst_len)++] = (a << 2) + (b >> 4);
		if (c != 255) {
			dst[(*dst_len)++] = (b << 4) + (c >> 2);
			if (d != 255) {
				dst[(*dst_len)++] = (c << 6) + d;
			}
		}
	}
	return -1;
}
#endif

static int is_put_or_delete_method(const struct mg_connection *conn)
{
	if (conn) {
		const char *s = conn->request_info.request_method;
		return s != NULL && (!strcmp(s, "PUT") || !strcmp(s, "DELETE") ||
		                     !strcmp(s, "MKCOL"));
	}
	return 0;
}

static void
interpret_uri(struct mg_connection *conn,   /* in: request */
              char *filename,               /* out: filename */
              size_t filename_buf_len,      /* in: size of filename buffer */
              struct file *filep,           /* out: file structure */
              int *is_found,                /* out: file is found (directly) */
              int *is_script_ressource,     /* out: handled by a script? */
              int *is_websocket_request,    /* out: websocket connetion? */
              int *is_put_or_delete_request /* out: put/delete a file? */
              )
{
	if (conn && conn->ctx) {
		const char *uri = conn->request_info.uri;
		const char *root = conn->ctx->config[DOCUMENT_ROOT];

#if !defined(NO_FILES)
		const char *rewrite;
		struct vec a, b;
		char *p;
		int match_len;
		char gz_path[PATH_MAX];
		char const *accept_encoding;
#endif

		memset(filep, 0, sizeof(*filep));
		*filename = 0;
		*is_found = 0;
		*is_script_ressource = 0;
		*is_put_or_delete_request = is_put_or_delete_method(conn);

#if defined(USE_WEBSOCKET)
		*is_websocket_request = is_websocket_protocol(conn);
		if (*is_websocket_request && conn->ctx->config[WEBSOCKET_ROOT]) {
			root = conn->ctx->config[WEBSOCKET_ROOT];
		}
#else
		*is_websocket_request = 0;
#endif

#if !defined(NO_FILES)
		/* Note that root == NULL is a regular use case here. This occurs,
		 * if all requests are handled by callbacks, so the WEBSOCKET_ROOT
		 * config is not required. */
		if (root == NULL) {
			/* all file related outputs have already been set to 0, just return
			 */
			return;
		}

		/* Using buf_len - 1 because memmove() for PATH_INFO may shift part
		 * of the path one byte on the right.
		 * If document_root is NULL, leave the file empty. */
		mg_snprintf(conn, filename, filename_buf_len - 1, "%s%s", root, uri);

		rewrite = conn->ctx->config[REWRITE];
		while ((rewrite = next_option(rewrite, &a, &b)) != NULL) {
			if ((match_len = match_prefix(a.ptr, a.len, uri)) > 0) {
				mg_snprintf(conn,
				            filename,
				            filename_buf_len - 1,
				            "%.*s%s",
				            (int)b.len,
				            b.ptr,
				            uri + match_len);
				break;
			}
		}

		/* Local file path and name, corresponding to requested URI
		 * is now stored in "filename" variable. */
		if (mg_stat(conn, filename, filep)) {
			/* File exists. Check if it is a script type. */
			if (0
#if !defined(NO_CGI)
			    ||
			    match_prefix(conn->ctx->config[CGI_EXTENSIONS],
			                 strlen(conn->ctx->config[CGI_EXTENSIONS]),
			                 filename) > 0
#endif
#if defined(USE_LUA)
			    ||
			    match_prefix(conn->ctx->config[LUA_SCRIPT_EXTENSIONS],
			                 strlen(conn->ctx->config[LUA_SCRIPT_EXTENSIONS]),
			                 filename) > 0
#endif
			    ) {
				/* The request addresses a CGI script or a Lua script. The URI
				 * corresponds to the script itself (like /path/script.cgi),
				 * and there is no additional resource path
				 * (like /path/script.cgi/something).
				 * Requests that modify (replace or delete) a resource, like
				 * PUT and DELETE requests, should replace/delete the script
				 * file.
				 * Requests that read or write from/to a resource, like GET and
				 * POST requests, should call the script and return the
				 * generated response. */
				*is_script_ressource = !*is_put_or_delete_request;
			}
			*is_found = 1;
			return;
		}

		/* If we can't find the actual file, look for the file
		 * with the same name but a .gz extension. If we find it,
		 * use that and set the gzipped flag in the file struct
		 * to indicate that the response need to have the content-
		 * encoding: gzip header.
		 * We can only do this if the browser declares support. */
		if ((accept_encoding = mg_get_header(conn, "Accept-Encoding")) !=
		    NULL) {
			if (strstr(accept_encoding, "gzip") != NULL) {
				snprintf(gz_path, sizeof(gz_path), "%s.gz", filename);
				if (mg_stat(conn, gz_path, filep)) {
					if (filep) {
						filep->gzipped = 1;
					}
					/* Currently gz files can not be scripts. */
					return;
				}
			}
		}

		/* Support PATH_INFO for CGI scripts. */
		for (p = filename + strlen(filename); p > filename + 1; p--) {
			if (*p == '/') {
				*p = '\0';
				if ((0
#if !defined(NO_CGI)
				     ||
				     match_prefix(conn->ctx->config[CGI_EXTENSIONS],
				                  strlen(conn->ctx->config[CGI_EXTENSIONS]),
				                  filename) > 0
#endif
#if defined(USE_LUA)
				     ||
				     match_prefix(
				         conn->ctx->config[LUA_SCRIPT_EXTENSIONS],
				         strlen(conn->ctx->config[LUA_SCRIPT_EXTENSIONS]),
				         filename) > 0
#endif
				     ) &&
				    mg_stat(conn, filename, filep)) {
					/* Shift PATH_INFO block one character right, e.g.
					 * "/x.cgi/foo/bar\x00" => "/x.cgi\x00/foo/bar\x00"
					 * conn->path_info is pointing to the local variable "path"
					 * declared in handle_request(), so PATH_INFO is not valid
					 * after handle_request returns. */
					conn->path_info = p + 1;
					memmove(p + 2, p + 1, strlen(p + 1) + 1); /* +1 is for
					                                           * trailing \0 */
					p[1] = '/';
					*is_script_ressource = 1;
					break;
				} else {
					*p = '/';
				}
			}
		}
#endif
	}
}

/* Check whether full request is buffered. Return:
 * -1  if request is malformed
 *  0  if request is not yet fully buffered
 * >0  actual request length, including last \r\n\r\n */
static int get_request_len(const char *buf, int buflen)
{
	const char *s, *e;
	int len = 0;

	for (s = buf, e = s + buflen - 1; len <= 0 && s < e; s++)
		/* Control characters are not allowed but >=128 is. */
		if (!isprint(*(const unsigned char *)s) && *s != '\r' && *s != '\n' &&
		    *(const unsigned char *)s < 128) {
			len = -1;
			break; /* [i_a] abort scan as soon as one malformed character is
			        * found; */
			/* don't let subsequent \r\n\r\n win us over anyhow */
		} else if (s[0] == '\n' && s[1] == '\n') {
			len = (int)(s - buf) + 2;
		} else if (s[0] == '\n' && &s[1] < e && s[1] == '\r' && s[2] == '\n') {
			len = (int)(s - buf) + 3;
		}

	return len;
}

/* Convert month to the month number. Return -1 on error, or month number */
static int get_month_index(const char *s)
{
	size_t i;

	for (i = 0; i < ARRAY_SIZE(month_names); i++) {
		if (!strcmp(s, month_names[i])) {
			return (int)i;
		}
	}

	return -1;
}

static int num_leap_years(int year)
{
	return year / 4 - year / 100 + year / 400;
}

/* Parse UTC date-time string, and return the corresponding time_t value. */
static time_t parse_date_string(const char *datetime)
{
	static const unsigned short days_before_month[] = {
	    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
	char month_str[32] = {0};
	int second, minute, hour, day, month, year, leap_days, days;
	time_t result = (time_t)0;

	if ((sscanf(datetime,
	            "%d/%3s/%d %d:%d:%d",
	            &day,
	            month_str,
	            &year,
	            &hour,
	            &minute,
	            &second) == 6) ||
	    (sscanf(datetime,
	            "%d %3s %d %d:%d:%d",
	            &day,
	            month_str,
	            &year,
	            &hour,
	            &minute,
	            &second) == 6) ||
	    (sscanf(datetime,
	            "%*3s, %d %3s %d %d:%d:%d",
	            &day,
	            month_str,
	            &year,
	            &hour,
	            &minute,
	            &second) == 6) ||
	    (sscanf(datetime,
	            "%d-%3s-%d %d:%d:%d",
	            &day,
	            month_str,
	            &year,
	            &hour,
	            &minute,
	            &second) == 6)) {
		month = get_month_index(month_str);
		if ((month >= 0) && (year > 1970)) {
			leap_days = num_leap_years(year) - num_leap_years(1970);
			year -= 1970;
			days =
			    year * 365 + days_before_month[month] + (day - 1) + leap_days;
			result = (time_t)days * 24 * 3600 + (time_t)hour * 3600 +
			         minute * 60 + second;
		}
	}

	return result;
}

/* Protect against directory disclosure attack by removing '..',
 * excessive '/' and '\' characters */
static void remove_double_dots_and_double_slashes(char *s)
{
	char *p = s;

	while (*s != '\0') {
		*p++ = *s++;
		if (s[-1] == '/' || s[-1] == '\\') {
			/* Skip all following slashes, backslashes and double-dots */
			while (s[0] != '\0') {
				if (s[0] == '/' || s[0] == '\\') {
					s++;
				} else if (s[0] == '.' && s[1] == '.') {
					s += 2;
				} else {
					break;
				}
			}
		}
	}
	*p = '\0';
}

static const struct {
	const char *extension;
	size_t ext_len;
	const char *mime_type;
} builtin_mime_types[] = {
    /* IANA registered MIME types (http://www.iana.org/assignments/media-types)
     * application types */
    {".doc", 4, "application/msword"},
    {".eps", 4, "application/postscript"},
    {".exe", 4, "application/octet-stream"},
    {".js", 3, "application/javascript"},
    {".json", 5, "application/json"},
    {".pdf", 4, "application/pdf"},
    {".ps", 3, "application/postscript"},
    {".rtf", 4, "application/rtf"},
    {".xhtml", 6, "application/xhtml+xml"},
    {".xsl", 4, "application/xml"},
    {".xslt", 5, "application/xml"},

    /* audio */
    {".mp3", 4, "audio/mpeg"},
    {".oga", 4, "audio/ogg"},
    {".ogg", 4, "audio/ogg"},

    /* image */
    {".gif", 4, "image/gif"},
    {".ief", 4, "image/ief"},
    {".jpeg", 5, "image/jpeg"},
    {".jpg", 4, "image/jpeg"},
    {".jpm", 4, "image/jpm"},
    {".jpx", 4, "image/jpx"},
    {".png", 4, "image/png"},
    {".svg", 4, "image/svg+xml"},
    {".tif", 4, "image/tiff"},
    {".tiff", 5, "image/tiff"},

    /* model */
    {".wrl", 4, "model/vrml"},

    /* text */
    {".css", 4, "text/css"},
    {".csv", 4, "text/csv"},
    {".htm", 4, "text/html"},
    {".html", 5, "text/html"},
    {".sgm", 4, "text/sgml"},
    {".shtm", 5, "text/html"},
    {".shtml", 6, "text/html"},
    {".txt", 4, "text/plain"},
    {".xml", 4, "text/xml"},

    /* video */
    {".mov", 4, "video/quicktime"},
    {".mp4", 4, "video/mp4"},
    {".mpeg", 5, "video/mpeg"},
    {".mpg", 4, "video/mpeg"},
    {".ogv", 4, "video/ogg"},
    {".qt", 3, "video/quicktime"},

    /* not registered types
     * (http://reference.sitepoint.com/html/mime-types-full,
     * http://www.hansenb.pdx.edu/DMKB/dict/tutorials/mime_typ.php, ..) */
    {".arj", 4, "application/x-arj-compressed"},
    {".gz", 3, "application/x-gunzip"},
    {".rar", 4, "application/x-arj-compressed"},
    {".swf", 4, "application/x-shockwave-flash"},
    {".tar", 4, "application/x-tar"},
    {".tgz", 4, "application/x-tar-gz"},
    {".torrent", 8, "application/x-bittorrent"},
    {".ppt", 4, "application/x-mspowerpoint"},
    {".xls", 4, "application/x-msexcel"},
    {".zip", 4, "application/x-zip-compressed"},
    {".aac",
     4,
     "audio/aac"}, /* http://en.wikipedia.org/wiki/Advanced_Audio_Coding */
    {".aif", 4, "audio/x-aif"},
    {".m3u", 4, "audio/x-mpegurl"},
    {".mid", 4, "audio/x-midi"},
    {".ra", 3, "audio/x-pn-realaudio"},
    {".ram", 4, "audio/x-pn-realaudio"},
    {".wav", 4, "audio/x-wav"},
    {".bmp", 4, "image/bmp"},
    {".ico", 4, "image/x-icon"},
    {".pct", 4, "image/x-pct"},
    {".pict", 5, "image/pict"},
    {".rgb", 4, "image/x-rgb"},
    {".webm", 5, "video/webm"}, /* http://en.wikipedia.org/wiki/WebM */
    {".asf", 4, "video/x-ms-asf"},
    {".avi", 4, "video/x-msvideo"},
    {".m4v", 4, "video/x-m4v"},
    {NULL, 0, NULL}};

const char *mg_get_builtin_mime_type(const char *path)
{
	const char *ext;
	size_t i, path_len;

	path_len = strlen(path);

	for (i = 0; builtin_mime_types[i].extension != NULL; i++) {
		ext = path + (path_len - builtin_mime_types[i].ext_len);
		if (path_len > builtin_mime_types[i].ext_len &&
		    mg_strcasecmp(ext, builtin_mime_types[i].extension) == 0) {
			return builtin_mime_types[i].mime_type;
		}
	}

	return "text/plain";
}

/* Look at the "path" extension and figure what mime type it has.
 * Store mime type in the vector. */
static void
get_mime_type(struct mg_context *ctx, const char *path, struct vec *vec)
{
	struct vec ext_vec, mime_vec;
	const char *list, *ext;
	size_t path_len;

	path_len = strlen(path);

	if (ctx == NULL || vec == NULL) {
		return;
	}

	/* Scan user-defined mime types first, in case user wants to
	 * override default mime types. */
	list = ctx->config[EXTRA_MIME_TYPES];
	while ((list = next_option(list, &ext_vec, &mime_vec)) != NULL) {
		/* ext now points to the path suffix */
		ext = path + path_len - ext_vec.len;
		if (mg_strncasecmp(ext, ext_vec.ptr, ext_vec.len) == 0) {
			*vec = mime_vec;
			return;
		}
	}

	vec->ptr = mg_get_builtin_mime_type(path);
	vec->len = strlen(vec->ptr);
}

/* Stringify binary data. Output buffer must be twice as big as input,
 * because each byte takes 2 bytes in string representation */
static void bin2str(char *to, const unsigned char *p, size_t len)
{
	static const char *hex = "0123456789abcdef";

	for (; len--; p++) {
		*to++ = hex[p[0] >> 4];
		*to++ = hex[p[0] & 0x0f];
	}
	*to = '\0';
}

/* Return stringified MD5 hash for list of strings. Buffer must be 33 bytes. */
char *mg_md5(char buf[33], ...)
{
	md5_byte_t hash[16];
	const char *p;
	va_list ap;
	md5_state_t ctx;

	md5_init(&ctx);

	va_start(ap, buf);
	while ((p = va_arg(ap, const char *)) != NULL) {
		md5_append(&ctx, (const md5_byte_t *)p, strlen(p));
	}
	va_end(ap);

	md5_finish(&ctx, hash);
	bin2str(buf, hash, sizeof(hash));
	return buf;
}

/* Check the user's password, return 1 if OK */
static int check_password(const char *method,
                          const char *ha1,
                          const char *uri,
                          const char *nonce,
                          const char *nc,
                          const char *cnonce,
                          const char *qop,
                          const char *response)
{
	char ha2[32 + 1], expected_response[32 + 1];

	/* Some of the parameters may be NULL */
	if (method == NULL || nonce == NULL || nc == NULL || cnonce == NULL ||
	    qop == NULL || response == NULL) {
		return 0;
	}

	/* NOTE(lsm): due to a bug in MSIE, we do not compare the URI */
	/* TODO(lsm): check for authentication timeout */
	if (/* strcmp(dig->uri, c->ouri) != 0 || */
	    strlen(response) != 32
	    /* || now - strtoul(dig->nonce, NULL, 10) > 3600 */
	    ) {
		return 0;
	}

	mg_md5(ha2, method, ":", uri, NULL);
	mg_md5(expected_response,
	       ha1,
	       ":",
	       nonce,
	       ":",
	       nc,
	       ":",
	       cnonce,
	       ":",
	       qop,
	       ":",
	       ha2,
	       NULL);

	return mg_strcasecmp(response, expected_response) == 0;
}

/* Use the global passwords file, if specified by auth_gpass option,
 * or search for .htpasswd in the requested directory. */
static void
open_auth_file(struct mg_connection *conn, const char *path, struct file *filep)
{
	if (conn != NULL && conn->ctx != NULL) {
		char name[PATH_MAX];
		const char *p, *e, *gpass = conn->ctx->config[GLOBAL_PASSWORDS_FILE];
		struct file file = STRUCT_FILE_INITIALIZER;

		if (gpass != NULL) {
			/* Use global passwords file */
			if (!mg_fopen(conn, gpass, "r", filep)) {
#ifdef DEBUG
				mg_cry(conn, "fopen(%s): %s", gpass, strerror(ERRNO));
#endif
			}
			/* Important: using local struct file to test path for is_directory
			 * flag.
			 * If filep is used, mg_stat() makes it appear as if auth file was
			 * opened. */
		} else if (mg_stat(conn, path, &file) && file.is_directory) {
			mg_snprintf(conn,
			            name,
			            sizeof(name),
			            "%s%c%s",
			            path,
			            '/',
			            PASSWORDS_FILE_NAME);
			if (!mg_fopen(conn, name, "r", filep)) {
#ifdef DEBUG
				mg_cry(conn, "fopen(%s): %s", name, strerror(ERRNO));
#endif
			}
		} else {
			/* Try to find .htpasswd in requested directory. */
			for (p = path, e = p + strlen(p) - 1; e > p; e--) {
				if (e[0] == '/') {
					break;
				}
			}
			mg_snprintf(conn,
			            name,
			            sizeof(name),
			            "%.*s%c%s",
			            (int)(e - p),
			            p,
			            '/',
			            PASSWORDS_FILE_NAME);
			if (!mg_fopen(conn, name, "r", filep)) {
#ifdef DEBUG
				mg_cry(conn, "fopen(%s): %s", name, strerror(ERRNO));
#endif
			}
		}
	}
}

/* Parsed Authorization header */
struct ah {
	char *user, *uri, *cnonce, *response, *qop, *nc, *nonce;
};

/* Return 1 on success. Always initializes the ah structure. */
static int parse_auth_header(struct mg_connection *conn,
                             char *buf,
                             size_t buf_size,
                             struct ah *ah)
{
	char *name, *value, *s;
	const char *auth_header;
	unsigned long nonce;

	if (!ah || !conn) {
		return 0;
	}

	(void)memset(ah, 0, sizeof(*ah));
	if ((auth_header = mg_get_header(conn, "Authorization")) == NULL ||
	    mg_strncasecmp(auth_header, "Digest ", 7) != 0) {
		return 0;
	}

	/* Make modifiable copy of the auth header */
	(void)mg_strlcpy(buf, auth_header + 7, buf_size);
	s = buf;

	/* Parse authorization header */
	for (;;) {
		/* Gobble initial spaces */
		while (isspace(*(unsigned char *)s)) {
			s++;
		}
		name = skip_quoted(&s, "=", " ", 0);
		/* Value is either quote-delimited, or ends at first comma or space. */
		if (s[0] == '\"') {
			s++;
			value = skip_quoted(&s, "\"", " ", '\\');
			if (s[0] == ',') {
				s++;
			}
		} else {
			value = skip_quoted(&s, ", ", " ", 0); /* IE uses commas, FF uses
			                                        * spaces */
		}
		if (*name == '\0') {
			break;
		}

		if (!strcmp(name, "username")) {
			ah->user = value;
		} else if (!strcmp(name, "cnonce")) {
			ah->cnonce = value;
		} else if (!strcmp(name, "response")) {
			ah->response = value;
		} else if (!strcmp(name, "uri")) {
			ah->uri = value;
		} else if (!strcmp(name, "qop")) {
			ah->qop = value;
		} else if (!strcmp(name, "nc")) {
			ah->nc = value;
		} else if (!strcmp(name, "nonce")) {
			ah->nonce = value;
		}
	}

#ifndef NO_NONCE_CHECK
	/* Convert the nonce from the client to a number and check it. */
	/* Server side nonce check is valuable in all situations but one: if the
	 * server restarts frequently,
	 * but the client should not see that, so the server should accept nonces
	 * from
	 * previous starts. */
	if (ah->nonce == NULL) {
		return 0;
	}
	s = NULL;
	nonce = strtoul(ah->nonce, &s, 10);
	if ((s == NULL) || (*s != 0)) {
		return 0;
	}
	nonce ^= (uintptr_t)(conn->ctx);
	if (nonce < conn->ctx->start_time) {
		/* nonce is from a previous start of the server and no longer valid
		 * (replay attack?) */
		return 0;
	}
	if (nonce >= conn->ctx->start_time + conn->ctx->nonce_count) {
		return 0;
	}
#endif

	/* CGI needs it as REMOTE_USER */
	if (ah->user != NULL) {
		conn->request_info.remote_user = mg_strdup(ah->user);
	} else {
		return 0;
	}

	return 1;
}

static char *mg_fgets(char *buf, size_t size, struct file *filep, char **p)
{
	char *eof;
	size_t len;
	char *memend;

	if (!filep) {
		return NULL;
	}

	if (filep->membuf != NULL && *p != NULL) {
		memend = (char *)&filep->membuf[filep->size];
		/* Search for \n from p till the end of stream */
		eof = (char *)memchr(*p, '\n', (size_t)(memend - *p));
		if (eof != NULL) {
			eof += 1; /* Include \n */
		} else {
			eof = memend; /* Copy remaining data */
		}
		len = (size_t)(eof - *p) > size - 1 ? size - 1 : (size_t)(eof - *p);
		memcpy(buf, *p, len);
		buf[len] = '\0';
		*p += len;
		return len ? eof : NULL;
	} else if (filep->fp != NULL) {
		return fgets(buf, (int)size, filep->fp);
	} else {
		return NULL;
	}
}

struct read_auth_file_struct {
	struct mg_connection *conn;
	struct ah ah;
	char *domain;
	char buf[256 + 256 + 40];
	char *f_user;
	char *f_domain;
	char *f_ha1;
};

static int read_auth_file(struct file *filep,
                          struct read_auth_file_struct *workdata)
{
	char *p;
	int is_authorized = 0;
	struct file fp;
	size_t l;

	if (!filep || !workdata) {
		return 0;
	}

	/* Loop over passwords file */
	p = (char *)filep->membuf;
	while (mg_fgets(workdata->buf, sizeof(workdata->buf), filep, &p) != NULL) {
		l = strlen(workdata->buf);
		while (l > 0) {
			if (isspace(workdata->buf[l - 1]) ||
			    iscntrl(workdata->buf[l - 1])) {
				l--;
				workdata->buf[l] = 0;
			} else
				break;
		}
		if (l < 1) {
			continue;
		}

		workdata->f_user = workdata->buf;

		if (workdata->f_user[0] == ':') {
			/* user names may not contain a ':' and may not be empty,
			 * so lines starting with ':' may be used for a special purpose */
			if (workdata->f_user[1] == '#') {
				/* :# is a comment */
				continue;
			} else if (!strncmp(workdata->f_user + 1, "include=", 8)) {
				if (mg_fopen(workdata->conn, workdata->f_user + 9, "r", &fp)) {
					is_authorized = read_auth_file(&fp, workdata);
					mg_fclose(&fp);
				} else {
					mg_cry(workdata->conn,
					       "%s: cannot open authorization file: %s",
					       __func__,
					       workdata->buf);
				}
				continue;
			}
			/* everything is invalid for the moment (might change in the
			 * future) */
			mg_cry(workdata->conn,
			       "%s: syntax error in authorization file: %s",
			       __func__,
			       workdata->buf);
			continue;
		}

		workdata->f_domain = strchr(workdata->f_user, ':');
		if (workdata->f_domain == NULL) {
			mg_cry(workdata->conn,
			       "%s: syntax error in authorization file: %s",
			       __func__,
			       workdata->buf);
			continue;
		}
		*(workdata->f_domain) = 0;
		(workdata->f_domain)++;

		workdata->f_ha1 = strchr(workdata->f_domain, ':');
		if (workdata->f_ha1 == NULL) {
			mg_cry(workdata->conn,
			       "%s: syntax error in authorization file: %s",
			       __func__,
			       workdata->buf);
			continue;
		}
		*(workdata->f_ha1) = 0;
		(workdata->f_ha1)++;

		if (!strcmp(workdata->ah.user, workdata->f_user) &&
		    !strcmp(workdata->domain, workdata->f_domain)) {
			return check_password(workdata->conn->request_info.request_method,
			                      workdata->f_ha1,
			                      workdata->ah.uri,
			                      workdata->ah.nonce,
			                      workdata->ah.nc,
			                      workdata->ah.cnonce,
			                      workdata->ah.qop,
			                      workdata->ah.response);
		}
	}

	return is_authorized;
}

/* Authorize against the opened passwords file. Return 1 if authorized. */
static int authorize(struct mg_connection *conn, struct file *filep)
{
	struct read_auth_file_struct workdata;
	char buf[MG_BUF_LEN];

	if (!conn || !conn->ctx) {
		return 0;
	}

	memset(&workdata, 0, sizeof(workdata));
	workdata.conn = conn;

	if (!parse_auth_header(conn, buf, sizeof(buf), &workdata.ah)) {
		return 0;
	}
	workdata.domain = conn->ctx->config[AUTHENTICATION_DOMAIN];

	return read_auth_file(filep, &workdata);
}

/* Return 1 if request is authorised, 0 otherwise. */
static int check_authorization(struct mg_connection *conn, const char *path)
{
	char fname[PATH_MAX];
	struct vec uri_vec, filename_vec;
	const char *list;
	struct file file = STRUCT_FILE_INITIALIZER;
	int authorized = 1;

	if (!conn || !conn->ctx) {
		return 0;
	}

	list = conn->ctx->config[PROTECT_URI];
	while ((list = next_option(list, &uri_vec, &filename_vec)) != NULL) {
		if (!memcmp(conn->request_info.uri, uri_vec.ptr, uri_vec.len)) {
			mg_snprintf(conn,
			            fname,
			            sizeof(fname),
			            "%.*s",
			            (int)filename_vec.len,
			            filename_vec.ptr);
			if (!mg_fopen(conn, fname, "r", &file)) {
				mg_cry(conn,
				       "%s: cannot open %s: %s",
				       __func__,
				       fname,
				       strerror(errno));
			}
			break;
		}
	}

	if (!is_file_opened(&file)) {
		open_auth_file(conn, path, &file);
	}

	if (is_file_opened(&file)) {
		authorized = authorize(conn, &file);
		mg_fclose(&file);
	}

	return authorized;
}

static void send_authorization_request(struct mg_connection *conn)
{
	char date[64];
	time_t curtime = time(NULL);

	if (conn && conn->ctx) {
		unsigned long nonce = (unsigned long)(conn->ctx->start_time);

		(void)pthread_mutex_lock(&conn->ctx->nonce_mutex);
		nonce += conn->ctx->nonce_count;
		++conn->ctx->nonce_count;
		(void)pthread_mutex_unlock(&conn->ctx->nonce_mutex);

		nonce ^= (uintptr_t)(conn->ctx);
		conn->status_code = 401;
		conn->must_close = 1;

		gmt_time_string(date, sizeof(date), &curtime);

		mg_printf(conn,
		          "HTTP/1.1 401 Unauthorized\r\n"
		          "Date: %s\r\n"
		          "Connection: %s\r\n"
		          "Content-Length: 0\r\n"
		          "WWW-Authenticate: Digest qop=\"auth\", realm=\"%s\", "
		          "nonce=\"%lu\"\r\n\r\n",
		          date,
		          suggest_connection_header(conn),
		          conn->ctx->config[AUTHENTICATION_DOMAIN],
		          nonce);
	}
}

static int is_authorized_for_put(struct mg_connection *conn)
{
	if (conn) {
		struct file file = STRUCT_FILE_INITIALIZER;
		const char *passfile = conn->ctx->config[PUT_DELETE_PASSWORDS_FILE];
		int ret = 0;

		if (passfile != NULL && mg_fopen(conn, passfile, "r", &file)) {
			ret = authorize(conn, &file);
			mg_fclose(&file);
		}

		return ret;
	}
	return 0;
}

int mg_modify_passwords_file(const char *fname,
                             const char *domain,
                             const char *user,
                             const char *pass)
{
	int found, i;
	char line[512], u[512] = "", d[512] = "", ha1[33], tmp[PATH_MAX + 8];
	FILE *fp, *fp2;

	found = 0;
	fp = fp2 = NULL;

	/* Regard empty password as no password - remove user record. */
	if (pass != NULL && pass[0] == '\0') {
		pass = NULL;
	}

	/* Other arguments must not be empty */
	if (fname == NULL || domain == NULL || user == NULL) {
		return 0;
	}

	/* Using the given file format, user name and domain must not contain ':'
	 */
	if (strchr(user, ':') != NULL) {
		return 0;
	}
	if (strchr(domain, ':') != NULL) {
		return 0;
	}

	/* Do not allow control characters like newline in user name and domain.
	 * Do not allow excessively long names either. */
	for (i = 0; i < 255 && user[i] != 0; i++) {
		if (iscntrl(user[i])) {
			return 0;
		}
	}
	if (user[i]) {
		return 0;
	}
	for (i = 0; i < 255 && domain[i] != 0; i++) {
		if (iscntrl(domain[i])) {
			return 0;
		}
	}
	if (domain[i]) {
		return 0;
	}

	/* Create a temporary file name */
	(void)snprintf(tmp, sizeof(tmp) - 1, "%s.tmp", fname);
	tmp[sizeof(tmp) - 1] = 0;

	/* Create the file if does not exist */
	if ((fp = fopen(fname, "a+")) != NULL) {
		(void)fclose(fp);
	}

	/* Open the given file and temporary file */
	if ((fp = fopen(fname, "r")) == NULL) {
		return 0;
	} else if ((fp2 = fopen(tmp, "w+")) == NULL) {
		fclose(fp);
		return 0;
	}

	/* Copy the stuff to temporary file */
	while (fgets(line, sizeof(line), fp) != NULL) {
		if (sscanf(line, "%255[^:]:%255[^:]:%*s", u, d) != 2) {
			continue;
		}
		u[255] = 0;
		d[255] = 0;

		if (!strcmp(u, user) && !strcmp(d, domain)) {
			found++;
			if (pass != NULL) {
				mg_md5(ha1, user, ":", domain, ":", pass, NULL);
				fprintf(fp2, "%s:%s:%s\n", user, domain, ha1);
			}
		} else {
			fprintf(fp2, "%s", line);
		}
	}

	/* If new user, just add it */
	if (!found && pass != NULL) {
		mg_md5(ha1, user, ":", domain, ":", pass, NULL);
		fprintf(fp2, "%s:%s:%s\n", user, domain, ha1);
	}

	/* Close files */
	fclose(fp);
	fclose(fp2);

	/* Put the temp file in place of real file */
	IGNORE_UNUSED_RESULT(remove(fname));
	IGNORE_UNUSED_RESULT(rename(tmp, fname));

	return 1;
}


static int is_valid_port(unsigned int port) { return port < 0xffff; }


static int mg_inet_pton(int af, const char *src, void *dst, size_t dstlen)
{
	struct addrinfo hints, *res, *ressave;
	int ret = 0;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = af;

	if (getaddrinfo(src, NULL, &hints, &res) != 0) {
		/* bad src string or bad address family */
		return 0;
	}

	ressave = res;

	while (res) {
		if (dstlen >= res->ai_addrlen) {
			memcpy(dst, res->ai_addr, res->ai_addrlen);
			ret = 1;
		}
		res = res->ai_next;
	}

	freeaddrinfo(ressave);
	return ret;
}


static SOCKET conn2(struct mg_context *ctx /* may be null */,
                    const char *host,
                    int port,
                    int use_ssl,
                    char *ebuf,
                    size_t ebuf_len)
{
	union usa sa;
	SOCKET sock = INVALID_SOCKET;

	memset(&sa, 0, sizeof(sa));

	if (ebuf_len > 0) {
		*ebuf = 0;
	}

	if (host == NULL) {
		snprintf(ebuf, ebuf_len, "%s", "NULL host");
		return INVALID_SOCKET;
	}

	if (port < 0 || !is_valid_port((unsigned)port)) {
		snprintf(ebuf, ebuf_len, "%s", "invalid port");
		return INVALID_SOCKET;
	}

	if (use_ssl && (SSLv23_client_method == NULL)) {
		snprintf(ebuf, ebuf_len, "%s", "SSL is not initialized");
		return INVALID_SOCKET;
	}

	if (mg_inet_pton(AF_INET, host, &sa.sin, sizeof(sa.sin))) {
		sa.sin.sin_port = htons((uint16_t)port);
#ifdef USE_IPV6
	} else if (mg_inet_pton(AF_INET6, host, &sa.sin6, sizeof(sa.sin6))) {
		sa.sin6.sin6_port = htons((uint16_t)port);
#endif
	} else {
		snprintf(ebuf, ebuf_len, "%s", "host not found");
		return INVALID_SOCKET;
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET) {
		snprintf(ebuf, ebuf_len, "socket(): %s", strerror(ERRNO));
		return INVALID_SOCKET;
	}

	set_close_on_exec(sock, fc(ctx));

	/* TODO(mid): IPV6 */
	if (connect(sock, (struct sockaddr *)&sa.sin, sizeof(sa.sin)) != 0) {
		snprintf(
		    ebuf, ebuf_len, "connect(%s:%d): %s", host, port, strerror(ERRNO));
		closesocket(sock);
		sock = INVALID_SOCKET;
	}

	return sock;
}

int mg_url_encode(const char *src, char *dst, size_t dst_len)
{
	static const char *dont_escape = "._-$,;~()";
	static const char *hex = "0123456789abcdef";
	char *pos = dst;
	const char *end = dst + dst_len - 1;

	for (; *src != '\0' && pos < end; src++, pos++) {
		if (isalnum(*(const unsigned char *)src) ||
		    strchr(dont_escape, *(const unsigned char *)src) != NULL) {
			*pos = *src;
		} else if (pos + 2 < end) {
			pos[0] = '%';
			pos[1] = hex[(*(const unsigned char *)src) >> 4];
			pos[2] = hex[(*(const unsigned char *)src) & 0xf];
			pos += 2;
		} else {
			break;
		}
	}

	*pos = '\0';
	return (*src == '\0') ? (int)(pos - dst) : -1;
}

static void print_dir_entry(struct de *de)
{
	char size[64], mod[64], href[PATH_MAX];
	struct tm *tm;

	if (de->file.is_directory) {
		mg_snprintf(de->conn, size, sizeof(size), "%s", "[DIRECTORY]");
	} else {
		/* We use (signed) cast below because MSVC 6 compiler cannot
		 * convert unsigned __int64 to double. Sigh. */
		if (de->file.size < 1024) {
			mg_snprintf(de->conn, size, sizeof(size), "%d", (int)de->file.size);
		} else if (de->file.size < 0x100000) {
			mg_snprintf(de->conn,
			            size,
			            sizeof(size),
			            "%.1fk",
			            (double)de->file.size / 1024.0);
		} else if (de->file.size < 0x40000000) {
			mg_snprintf(de->conn,
			            size,
			            sizeof(size),
			            "%.1fM",
			            (double)de->file.size / 1048576);
		} else {
			mg_snprintf(de->conn,
			            size,
			            sizeof(size),
			            "%.1fG",
			            (double)de->file.size / 1073741824);
		}
	}
	tm = localtime(&de->file.last_modified);
	if (tm != NULL) {
		strftime(mod, sizeof(mod), "%d-%b-%Y %H:%M", tm);
	} else {
		mg_strlcpy(mod, "01-Jan-1970 00:00", sizeof(mod));
		mod[sizeof(mod) - 1] = '\0';
	}
	mg_url_encode(de->file_name, href, sizeof(href));
	de->conn->num_bytes_sent +=
	    mg_printf(de->conn,
	              "<tr><td><a href=\"%s%s%s\">%s%s</a></td>"
	              "<td>&nbsp;%s</td><td>&nbsp;&nbsp;%s</td></tr>\n",
	              de->conn->request_info.uri,
	              href,
	              de->file.is_directory ? "/" : "",
	              de->file_name,
	              de->file.is_directory ? "/" : "",
	              mod,
	              size);
}

/* This function is called from send_directory() and used for
 * sorting directory entries by size, or name, or modification time.
 * On windows, __cdecl specification is needed in case if project is built
 * with __stdcall convention. qsort always requires __cdels callback. */
static int WINCDECL compare_dir_entries(const void *p1, const void *p2)
{
	if (p1 && p2) {
		const struct de *a = (const struct de *)p1, *b = (const struct de *)p2;
		const char *query_string = a->conn->request_info.query_string;
		int cmp_result = 0;

		if (query_string == NULL) {
			query_string = "na";
		}

		if (a->file.is_directory && !b->file.is_directory) {
			return -1; /* Always put directories on top */
		} else if (!a->file.is_directory && b->file.is_directory) {
			return 1; /* Always put directories on top */
		} else if (*query_string == 'n') {
			cmp_result = strcmp(a->file_name, b->file_name);
		} else if (*query_string == 's') {
			cmp_result = a->file.size == b->file.size
			                 ? 0
			                 : a->file.size > b->file.size ? 1 : -1;
		} else if (*query_string == 'd') {
			cmp_result =
			    (a->file.last_modified == b->file.last_modified)
			        ? 0
			        : ((a->file.last_modified > b->file.last_modified) ? 1
			                                                           : -1);
		}

		return query_string[1] == 'd' ? -cmp_result : cmp_result;
	}
	return 0;
}

static int must_hide_file(struct mg_connection *conn, const char *path)
{
	if (conn && conn->ctx) {
		const char *pw_pattern = "**" PASSWORDS_FILE_NAME "$";
		const char *pattern = conn->ctx->config[HIDE_FILES];
		return match_prefix(pw_pattern, strlen(pw_pattern), path) > 0 ||
		       (pattern != NULL &&
		        match_prefix(pattern, strlen(pattern), path) > 0);
	}
	return 0;
}

static int scan_directory(struct mg_connection *conn,
                          const char *dir,
                          void *data,
                          void (*cb)(struct de *, void *))
{
	char path[PATH_MAX];
	struct dirent *dp;
	DIR *dirp;
	struct de de;

	if ((dirp = opendir(dir)) == NULL) {
		return 0;
	} else {
		de.conn = conn;

		while ((dp = readdir(dirp)) != NULL) {
			/* Do not show current dir and hidden files */
			if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..") ||
			    must_hide_file(conn, dp->d_name)) {
				continue;
			}

			mg_snprintf(
			    conn, path, sizeof(path), "%s%c%s", dir, '/', dp->d_name);

			/* If we don't memset stat structure to zero, mtime will have
			 * garbage and strftime() will segfault later on in
			 * print_dir_entry(). memset is required only if mg_stat()
			 * fails. For more details, see
			 * http://code.google.com/p/mongoose/issues/detail?id=79 */
			memset(&de.file, 0, sizeof(de.file));
			if (!mg_stat(conn, path, &de.file)) {
				mg_cry(conn,
				       "%s: mg_stat(%s) failed: %s",
				       __func__,
				       path,
				       strerror(ERRNO));
			}

			de.file_name = dp->d_name;
			cb(&de, data);
		}
		(void)closedir(dirp);
	}
	return 1;
}

static int remove_directory(struct mg_connection *conn, const char *dir)
{
	char path[PATH_MAX];
	struct dirent *dp;
	DIR *dirp;
	struct de de;

	if ((dirp = opendir(dir)) == NULL) {
		return 0;
	} else {
		de.conn = conn;

		while ((dp = readdir(dirp)) != NULL) {
			/* Do not show current dir (but show hidden files as they will
			 * also be removed) */
			if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) {
				continue;
			}

			mg_snprintf(
			    conn, path, sizeof(path), "%s%c%s", dir, '/', dp->d_name);

			/* If we don't memset stat structure to zero, mtime will have
			 * garbage and strftime() will segfault later on in
			 * print_dir_entry(). memset is required only if mg_stat()
			 * fails. For more details, see
			 * http://code.google.com/p/mongoose/issues/detail?id=79 */
			memset(&de.file, 0, sizeof(de.file));
			if (!mg_stat(conn, path, &de.file)) {
				mg_cry(conn,
				       "%s: mg_stat(%s) failed: %s",
				       __func__,
				       path,
				       strerror(ERRNO));
			}
			if (de.file.membuf == NULL) {
				/* file is not in memory */
				if (de.file.is_directory) {
					remove_directory(conn, path);
				} else {
					mg_remove(path);
				}
			}
		}
		(void)closedir(dirp);

		IGNORE_UNUSED_RESULT(rmdir(dir));
	}

	return 1;
}

struct dir_scan_data {
	struct de *entries;
	unsigned int num_entries;
	unsigned int arr_size;
};

/* Behaves like realloc(), but frees original pointer on failure */
static void *realloc2(void *ptr, size_t size)
{
	void *new_ptr = mg_realloc(ptr, size);
	if (new_ptr == NULL) {
		mg_free(ptr);
	}
	return new_ptr;
}

static void dir_scan_callback(struct de *de, void *data)
{
	struct dir_scan_data *dsd = (struct dir_scan_data *)data;

	if (dsd->entries == NULL || dsd->num_entries >= dsd->arr_size) {
		dsd->arr_size *= 2;
		dsd->entries = (struct de *)realloc2(
		    dsd->entries, dsd->arr_size * sizeof(dsd->entries[0]));
	}
	if (dsd->entries == NULL) {
		/* TODO(lsm, low): propagate an error to the caller */
		dsd->num_entries = 0;
	} else {
		dsd->entries[dsd->num_entries].file_name = mg_strdup(de->file_name);
		dsd->entries[dsd->num_entries].file = de->file;
		dsd->entries[dsd->num_entries].conn = de->conn;
		dsd->num_entries++;
	}
}

static void handle_directory_request(struct mg_connection *conn,
                                     const char *dir)
{
	unsigned int i;
	int sort_direction;
	struct dir_scan_data data = {NULL, 0, 128};
	char date[64];
	time_t curtime = time(NULL);

	if (!scan_directory(conn, dir, &data, dir_scan_callback)) {
		send_http_error(conn,
		                500,
		                "Error: Cannot open directory\nopendir(%s): %s",
		                dir,
		                strerror(ERRNO));
		return;
	}

	gmt_time_string(date, sizeof(date), &curtime);

	if (!conn) {
		return;
	}

	sort_direction = conn->request_info.query_string != NULL &&
	                         conn->request_info.query_string[1] == 'd'
	                     ? 'a'
	                     : 'd';

	conn->must_close = 1;
	mg_printf(conn,
	          "HTTP/1.1 200 OK\r\n"
	          "Date: %s\r\n"
	          "Connection: close\r\n"
	          "Content-Type: text/html; charset=utf-8\r\n\r\n",
	          date);

	conn->num_bytes_sent +=
	    mg_printf(conn,
	              "<html><head><title>Index of %s</title>"
	              "<style>th {text-align: left;}</style></head>"
	              "<body><h1>Index of %s</h1><pre><table cellpadding=\"0\">"
	              "<tr><th><a href=\"?n%c\">Name</a></th>"
	              "<th><a href=\"?d%c\">Modified</a></th>"
	              "<th><a href=\"?s%c\">Size</a></th></tr>"
	              "<tr><td colspan=\"3\"><hr></td></tr>",
	              conn->request_info.uri,
	              conn->request_info.uri,
	              sort_direction,
	              sort_direction,
	              sort_direction);

	/* Print first entry - link to a parent directory */
	conn->num_bytes_sent +=
	    mg_printf(conn,
	              "<tr><td><a href=\"%s%s\">%s</a></td>"
	              "<td>&nbsp;%s</td><td>&nbsp;&nbsp;%s</td></tr>\n",
	              conn->request_info.uri,
	              "..",
	              "Parent directory",
	              "-",
	              "-");

	/* Sort and print directory entries */
	if (data.entries != NULL) {
		qsort(data.entries,
		      (size_t)data.num_entries,
		      sizeof(data.entries[0]),
		      compare_dir_entries);
		for (i = 0; i < data.num_entries; i++) {
			print_dir_entry(&data.entries[i]);
			mg_free(data.entries[i].file_name);
		}
		mg_free(data.entries);
	}

	conn->num_bytes_sent += mg_printf(conn, "%s", "</table></body></html>");
	conn->status_code = 200;
}

/* Send len bytes from the opened file to the client. */
static void send_file_data(struct mg_connection *conn,
                           struct file *filep,
                           int64_t offset,
                           int64_t len)
{
	char buf[MG_BUF_LEN];
	int to_read, num_read, num_written;
	int64_t size;

	if (!filep || !conn) {
		return;
	}

	/* Sanity check the offset */
	size = filep->size > INT64_MAX ? INT64_MAX : (int64_t)(filep->size);
	offset = offset < 0 ? 0 : offset > size ? size : offset;

	if (len > 0 && filep->membuf != NULL && size > 0) {
		/* file stored in memory */
		if (len > size - offset) {
			len = size - offset;
		}
		mg_write(conn, filep->membuf + offset, (size_t)len);
	} else if (len > 0 && filep->fp != NULL) {
/* file stored on disk */
#if defined(__linux__)
		/* TODO (high): Test sendfile for Linux */
		if (conn->throttle == 0 && conn->ssl == 0) {
			off_t sf_offs = (off_t)offset;
			ssize_t sf_sent;
			int sf_file = fileno(filep->fp);

			do {
				/* 2147479552 (0x7FFFF000) is a limit found by experiment on 64
				 * bit Linux (2^31 minus one memory page of 4k?). */
				ssize_t sf_tosend =
				    (size_t)((len < 0x7FFFF000) ? len : 0x7FFFF000);
				sf_sent =
				    sendfile(conn->client.sock, sf_file, &sf_offs, sf_tosend);
				if (sf_sent > 0) {
					conn->num_bytes_sent += sf_sent;
					len -= sf_sent;
					offset += sf_sent;
				}

			} while ((len > 0) && (sf_sent >= 0));

			if (sf_sent > 0) {
				return; /* OK */
			}
			/* sf_sent<0 means error, thus fall back to the classic way */
			mg_cry(conn,
			       "%s: sendfile() failed: %s (now trying read+write)",
			       __func__,
			       strerror(ERRNO));
		}
#endif
		if (offset > 0 && fseeko(filep->fp, offset, SEEK_SET) != 0) {
			mg_cry(conn, "%s: fseeko() failed: %s", __func__, strerror(ERRNO));
		} else {
			while (len > 0) {
				/* Calculate how much to read from the file in the buffer */
				to_read = sizeof(buf);
				if ((int64_t)to_read > len) {
					to_read = (int)len;
				}

				/* Read from file, exit the loop on error */
				if ((num_read =
				         (int)fread(buf, 1, (size_t)to_read, filep->fp)) <= 0) {
					break;
				}

				/* Send read bytes to the client, exit the loop on error */
				if ((num_written = mg_write(conn, buf, (size_t)num_read)) !=
				    num_read) {
					break;
				}

				/* Both read and were successful, adjust counters */
				conn->num_bytes_sent += num_written;
				len -= num_written;
			}
		}
	}
}

static int parse_range_header(const char *header, int64_t *a, int64_t *b)
{
	return sscanf(header, "bytes=%" INT64_FMT "-%" INT64_FMT, a, b);
}

static void construct_etag(char *buf, size_t buf_len, const struct file *filep)
{
	if (filep != NULL && buf != NULL) {
		snprintf(buf,
		         buf_len,
		         "\"%lx.%" INT64_FMT "\"",
		         (unsigned long)filep->last_modified,
		         filep->size);
	}
}

static void fclose_on_exec(struct file *filep, struct mg_connection *conn)
{
	if (filep != NULL && filep->fp != NULL) {
#ifdef _WIN32
		(void)conn; /* Unused. */
#else
		if (fcntl(fileno(filep->fp), F_SETFD, FD_CLOEXEC) != 0) {
			mg_cry(conn,
			       "%s: fcntl(F_SETFD FD_CLOEXEC) failed: %s",
			       __func__,
			       strerror(ERRNO));
		}
#endif
	}
}

static void handle_static_file_request(struct mg_connection *conn,
                                       const char *path,
                                       struct file *filep)
{
	char date[64], lm[64], etag[64], range[64];
	const char *msg = "OK", *hdr;
	time_t curtime = time(NULL);
	int64_t cl, r1, r2;
	struct vec mime_vec;
	int n;
	char gz_path[PATH_MAX];
	const char *encoding = "";
	const char *cors1, *cors2, *cors3;

	if (conn == NULL || conn->ctx == NULL || filep == NULL) {
		return;
	}

	get_mime_type(conn->ctx, path, &mime_vec);
	if (filep->size > INT64_MAX) {
		send_http_error(conn,
		                500,
		                "Error: File size is too large to send\n%" INT64_FMT,
		                filep->size);
	}
	cl = (int64_t)filep->size;
	conn->status_code = 200;
	range[0] = '\0';

	/* if this file is in fact a pre-gzipped file, rewrite its filename
	 * it's important to rewrite the filename after resolving
	 * the mime type from it, to preserve the actual file's type */
	if (filep->gzipped) {
		snprintf(gz_path, sizeof(gz_path), "%s.gz", path);
		path = gz_path;
		encoding = "Content-Encoding: gzip\r\n";
	}

	if (!mg_fopen(conn, path, "rb", filep)) {
		send_http_error(conn,
		                500,
		                "Error: Cannot open file\nfopen(%s): %s",
		                path,
		                strerror(ERRNO));
		return;
	}

	fclose_on_exec(filep, conn);

	/* If Range: header specified, act accordingly */
	r1 = r2 = 0;
	hdr = mg_get_header(conn, "Range");
	if (hdr != NULL && (n = parse_range_header(hdr, &r1, &r2)) > 0 && r1 >= 0 &&
	    r2 >= 0) {
		/* actually, range requests don't play well with a pre-gzipped
		 * file (since the range is specified in the uncompressed space) */
		if (filep->gzipped) {
			send_http_error(
			    conn,
			    501,
			    "%s",
			    "Error: Range requests in gzipped files are not supported");
			mg_fclose(filep);
			return;
		}
		conn->status_code = 206;
		cl = n == 2 ? (r2 > cl ? cl : r2) - r1 + 1 : cl - r1;
		mg_snprintf(conn,
		            range,
		            sizeof(range),
		            "Content-Range: bytes "
		            "%" INT64_FMT "-%" INT64_FMT "/%" INT64_FMT "\r\n",
		            r1,
		            r1 + cl - 1,
		            filep->size);
		msg = "Partial Content";
	}

	hdr = mg_get_header(conn, "Origin");
	if (hdr) {
		/* Cross-origin resource sharing (CORS), see
		 * http://www.html5rocks.com/en/tutorials/cors/,
		 * http://www.html5rocks.com/static/images/cors_server_flowchart.png -
		 * preflight is not supported for files. */
		cors1 = "Access-Control-Allow-Origin: ";
		cors2 = conn->ctx->config[ACCESS_CONTROL_ALLOW_ORIGIN];
		cors3 = "\r\n";
	} else {
		cors1 = cors2 = cors3 = "";
	}

	/* Prepare Etag, Date, Last-Modified headers. Must be in UTC, according to
	 * http://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.3 */
	gmt_time_string(date, sizeof(date), &curtime);
	gmt_time_string(lm, sizeof(lm), &filep->last_modified);
	construct_etag(etag, sizeof(etag), filep);

	(void)mg_printf(conn,
	                "HTTP/1.1 %d %s\r\n"
	                "%s%s%s"
	                "Date: %s\r\n"
	                "Last-Modified: %s\r\n"
	                "Etag: %s\r\n"
	                "Content-Type: %.*s\r\n"
	                "Content-Length: %" INT64_FMT "\r\n"
	                "Connection: %s\r\n"
	                "Accept-Ranges: bytes\r\n"
	                "%s%s\r\n",
	                conn->status_code,
	                msg,
	                cors1,
	                cors2,
	                cors3,
	                date,
	                lm,
	                etag,
	                (int)mime_vec.len,
	                mime_vec.ptr,
	                cl,
	                suggest_connection_header(conn),
	                range,
	                encoding);

	if (strcmp(conn->request_info.request_method, "HEAD") != 0) {
		send_file_data(conn, filep, r1, cl);
	}
	mg_fclose(filep);
}

void mg_send_file(struct mg_connection *conn, const char *path)
{
	struct file file = STRUCT_FILE_INITIALIZER;
	if (mg_stat(conn, path, &file)) {
		if (file.is_directory) {
			if (!conn) {
				return;
			}
			if (!mg_strcasecmp(conn->ctx->config[ENABLE_DIRECTORY_LISTING],
			                   "yes")) {
				handle_directory_request(conn, path);
			} else {
				send_http_error(
				    conn, 403, "%s", "Error: Directory listing denied");
			}
		} else {
			handle_static_file_request(conn, path, &file);
		}
	} else {
		send_http_error(conn, 404, "%s", "Error: File not found");
	}
}

/* Parse HTTP headers from the given buffer, advance buffer to the point
 * where parsing stopped. */
static void parse_http_headers(char **buf, struct mg_request_info *ri)
{
	int i;

	if (!ri) {
		return;
	}

	ri->num_headers = 0;

	for (i = 0; i < (int)ARRAY_SIZE(ri->http_headers); i++) {
		ri->http_headers[i].name = skip_quoted(buf, ":", " ", 0);
		ri->http_headers[i].value = skip(buf, "\r\n");
		if (ri->http_headers[i].name[0] == '\0') {
			break;
		}
		ri->num_headers = i + 1;
	}
}

static int is_valid_http_method(const char *method)
{
	return !strcmp(method, "GET") || !strcmp(method, "POST") ||
	       !strcmp(method, "HEAD") || !strcmp(method, "CONNECT") ||
	       !strcmp(method, "PUT") || !strcmp(method, "DELETE") ||
	       !strcmp(method, "OPTIONS") || !strcmp(method, "PROPFIND") ||
	       !strcmp(method, "MKCOL");

	/* TRACE method is not supported for security reasons */
}

/* Parse HTTP request, fill in mg_request_info structure.
 * This function modifies the buffer by NUL-terminating
 * HTTP request components, header names and header values. */
static int parse_http_message(char *buf, int len, struct mg_request_info *ri)
{
	int is_request, request_length;

	if (!ri) {
		return 0;
	}

	request_length = get_request_len(buf, len);

	if (request_length > 0) {
		/* Reset attributes. DO NOT TOUCH is_ssl, remote_ip, remote_addr,
		 * remote_port */
		ri->remote_user = ri->request_method = ri->uri = ri->http_version =
		    NULL;
		ri->num_headers = 0;

		buf[request_length - 1] = '\0';

		/* RFC says that all initial whitespaces should be ingored */
		while (*buf != '\0' && isspace(*(unsigned char *)buf)) {
			buf++;
		}
		ri->request_method = skip(&buf, " ");
		ri->uri = skip(&buf, " ");
		ri->http_version = skip(&buf, "\r\n");

		/* HTTP message could be either HTTP request or HTTP response, e.g.
		 * "GET / HTTP/1.0 ...." or  "HTTP/1.0 200 OK ..." */
		is_request = is_valid_http_method(ri->request_method);
		if ((is_request && memcmp(ri->http_version, "HTTP/", 5) != 0) ||
		    (!is_request && memcmp(ri->request_method, "HTTP/", 5) != 0)) {
			request_length = -1;
		} else {
			if (is_request) {
				ri->http_version += 5;
			}
			parse_http_headers(&buf, ri);
		}
	}
	return request_length;
}

/* Keep reading the input (either opened file descriptor fd, or socket sock,
 * or SSL descriptor ssl) into buffer buf, until \r\n\r\n appears in the
 * buffer (which marks the end of HTTP request). Buffer buf may already
 * have some data. The length of the data is stored in nread.
 * Upon every read operation, increase nread by the number of bytes read. */
static int read_request(
    FILE *fp, struct mg_connection *conn, char *buf, int bufsiz, int *nread)
{
	int request_len, n = 0;
	struct timespec last_action_time = {0, 0};
	double request_timeout;

	if (!conn) {
		return 0;
	}

	if (conn->ctx->config[REQUEST_TIMEOUT]) {
		/* value of request_timeout is in seconds, config in milliseconds */
		request_timeout = atof(conn->ctx->config[REQUEST_TIMEOUT]) / 1000.0;
	} else {
		request_timeout = -1.0;
	}

	request_len = get_request_len(buf, *nread);
	while (
	    (conn->ctx->stop_flag == 0) && (*nread < bufsiz) &&
	    (request_len == 0) &&
	    ((mg_difftimespec(&last_action_time, &(conn->req_time)) <=
	      request_timeout) ||
	     (request_timeout < 0)) &&
	    ((n = pull(fp, conn, buf + *nread, bufsiz - *nread, request_timeout)) >
	     0)) {
		*nread += n;
		/* assert(*nread <= bufsiz); */
		if (*nread > bufsiz) {
			return -2;
		}
		request_len = get_request_len(buf, *nread);
		if (request_timeout > 0.0) {
			clock_gettime(CLOCK_MONOTONIC, &last_action_time);
		}
	}

	return (request_len <= 0 && n <= 0) ? -1 : request_len;
}

/* For given directory path, substitute it to valid index file.
 * Return 1 if index file has been found, 0 if not found.
 * If the file is found, it's stats is returned in stp. */
static int substitute_index_file(struct mg_connection *conn,
                                 char *path,
                                 size_t path_len,
                                 struct file *filep)
{
	if (conn && conn->ctx) {
		const char *list = conn->ctx->config[INDEX_FILES];
		struct file file = STRUCT_FILE_INITIALIZER;
		struct vec filename_vec;
		size_t n = strlen(path);
		int found = 0;

		/* The 'path' given to us points to the directory. Remove all trailing
		 * directory separator characters from the end of the path, and
		 * then append single directory separator character. */
		while (n > 0 && path[n - 1] == '/') {
			n--;
		}
		path[n] = '/';

		/* Traverse index files list. For each entry, append it to the given
		 * path and see if the file exists. If it exists, break the loop */
		while ((list = next_option(list, &filename_vec, NULL)) != NULL) {
			/* Ignore too long entries that may overflow path buffer */
			if (filename_vec.len > path_len - (n + 2)) {
				continue;
			}

			/* Prepare full path to the index file */
			mg_strlcpy(path + n + 1, filename_vec.ptr, filename_vec.len + 1);

			/* Does it exist? */
			if (mg_stat(conn, path, &file)) {
				/* Yes it does, break the loop */
				*filep = file;
				found = 1;
				break;
			}
		}

		/* If no index file exists, restore directory path */
		if (!found) {
			path[n] = '\0';
		}

		return found;
	}
	return 0;
}

/* Return True if we should reply 304 Not Modified. */
static int is_not_modified(const struct mg_connection *conn,
                           const struct file *filep)
{
	char etag[64];
	const char *ims = mg_get_header(conn, "If-Modified-Since");
	const char *inm = mg_get_header(conn, "If-None-Match");
	construct_etag(etag, sizeof(etag), filep);
	if (!filep) {
		return 0;
	}
	return (inm != NULL && !mg_strcasecmp(etag, inm)) ||
	       (ims != NULL && (filep->last_modified <= parse_date_string(ims)));
}

static int
forward_body_data(struct mg_connection *conn, FILE *fp, SOCKET sock, SSL *ssl)
{
	const char *expect, *body;
	char buf[MG_BUF_LEN];
	int to_read, nread, success = 0;
	int64_t buffered_len;
	double timeout = -1.0;

	if (!conn) {
		return 0;
	}
	if (conn->ctx->config[REQUEST_TIMEOUT]) {
		timeout = atoi(conn->ctx->config[REQUEST_TIMEOUT]) / 1000.0;
	}

	expect = mg_get_header(conn, "Expect");
	/* assert(fp != NULL); */
	if (!fp) {
		send_http_error(conn, 500, "%s", "Error: NULL File");
		return 0;
	}

	if (conn->content_len == -1 && !conn->is_chunked) {
		/* Content length is not specified by the client. */
		send_http_error(
		    conn, 411, "%s", "Error: Client did not specify content length");
	} else if ((expect != NULL) &&
	           (mg_strcasecmp(expect, "100-continue") != 0)) {
		/* Client sent an "Expect: xyz" header and xyz is not 100-continue. */
		send_http_error(
		    conn, 417, "Error: Can not fulfill expectation %s", expect);
	} else {
		if (expect != NULL) {
			(void)mg_printf(conn, "%s", "HTTP/1.1 100 Continue\r\n\r\n");
			conn->status_code = 100;
		} else {
			conn->status_code = 200;
		}

		buffered_len = (int64_t)(conn->data_len) - (int64_t)conn->request_len -
		               conn->consumed_content;

		/* assert(buffered_len >= 0); */
		/* assert(conn->consumed_content == 0); */

		if ((buffered_len < 0) || (conn->consumed_content != 0)) {
			send_http_error(conn, 500, "%s", "Error: Size mismatch");
			return 0;
		}

		if (buffered_len > 0) {
			if ((int64_t)buffered_len > conn->content_len) {
				buffered_len = (int)conn->content_len;
			}
			body = conn->buf + conn->request_len + conn->consumed_content;
			push_all(conn->ctx, fp, sock, ssl, body, (int64_t)buffered_len);
			conn->consumed_content += buffered_len;
		}

		nread = 0;
		while (conn->consumed_content < conn->content_len) {
			to_read = sizeof(buf);
			if ((int64_t)to_read > conn->content_len - conn->consumed_content) {
				to_read = (int)(conn->content_len - conn->consumed_content);
			}
			nread = pull(NULL, conn, buf, to_read, timeout);
			if (nread <= 0 ||
			    push_all(conn->ctx, fp, sock, ssl, buf, nread) != nread) {
				break;
			}
			conn->consumed_content += nread;
		}

		if (conn->consumed_content == conn->content_len) {
			success = nread >= 0;
		}

		/* Each error code path in this function must send an error */
		if (!success) {
			/* NOTE: Maybe some data has already been sent. */
			/* TODO (low): If some data has been sent, a correct error
			 * reply can no longer be sent, so just close the connection */
			send_http_error(conn, 500, "%s", "");
		}
	}

	return success;
}

#if !defined(NO_CGI)
/* This structure helps to create an environment for the spawned CGI program.
 * Environment is an array of "VARIABLE=VALUE\0" ASCIIZ strings,
 * last element must be NULL.
 * However, on Windows there is a requirement that all these VARIABLE=VALUE\0
 * strings must reside in a contiguous buffer. The end of the buffer is
 * marked by two '\0' characters.
 * We satisfy both worlds: we create an envp array (which is vars), all
 * entries are actually pointers inside buf. */
struct cgi_env_block {
	struct mg_connection *conn;
	char buf[CGI_ENVIRONMENT_SIZE]; /* Environment buffer */
	unsigned int len;               /* Space taken */
	char *vars[MAX_CGI_ENVIR_VARS]; /* char **envp */
	unsigned int nvars;             /* Number of variables */
};

static char *addenv(struct cgi_env_block *block,
                    PRINTF_FORMAT_STRING(const char *fmt),
                    ...) PRINTF_ARGS(2, 3);

/* Append VARIABLE=VALUE\0 string to the buffer, and add a respective
 * pointer into the vars array. */
static char *addenv(struct cgi_env_block *block, const char *fmt, ...)
{
	int n, space;
	char *added;
	va_list ap;

	if (block == NULL || fmt == NULL) {
		return NULL;
	}

	/* Calculate how much space is left in the buffer */
	space = (int)(sizeof(block->buf) - block->len) - 2;
	/* assert(space >= 0); */
	if (space < 0) {
		return NULL;
	}

	/* Make a pointer to the free space int the buffer */
	added = block->buf + block->len;

	/* Copy VARIABLE=VALUE\0 string into the free space */
	va_start(ap, fmt);
	n = mg_vsnprintf(block->conn, added, (size_t)space, fmt, ap);
	va_end(ap);

	/* Make sure we do not overflow buffer and the envp array */
	if (n > 0 && n + 1 < space && block->nvars + 2 < ARRAY_SIZE(block->vars)) {
		/* Append a pointer to the added string into the envp array */
		block->vars[block->nvars++] = added;
		/* Bump up used length counter. Include \0 terminator */
		block->len += (unsigned int)(n) + 1;
	} else {
		mg_cry(block->conn,
		       "%s: CGI env buffer truncated for [%s]",
		       __func__,
		       fmt);
	}

	return added;
}

static void prepare_cgi_environment(struct mg_connection *conn,
                                    const char *prog,
                                    struct cgi_env_block *blk)
{
	const char *s;
	struct vec var_vec;
	char *p, src_addr[IP_ADDR_STR_LEN];
	int i;

	if (conn == NULL || prog == NULL || blk == NULL) {
		return;
	}

	blk->len = blk->nvars = 0;
	blk->conn = conn;
	sockaddr_to_string(src_addr, sizeof(src_addr), &conn->client.rsa);

	addenv(blk, "SERVER_NAME=%s", conn->ctx->config[AUTHENTICATION_DOMAIN]);
	addenv(blk, "SERVER_ROOT=%s", conn->ctx->config[DOCUMENT_ROOT]);
	addenv(blk, "DOCUMENT_ROOT=%s", conn->ctx->config[DOCUMENT_ROOT]);
	addenv(blk, "SERVER_SOFTWARE=%s/%s", "Civetweb", mg_version());

	/* Prepare the environment block */
	addenv(blk, "%s", "GATEWAY_INTERFACE=CGI/1.1");
	addenv(blk, "%s", "SERVER_PROTOCOL=HTTP/1.1");
	addenv(blk, "%s", "REDIRECT_STATUS=200"); /* For PHP */

	/* TODO(lsm, high): fix this for IPv6 case */
	addenv(blk, "SERVER_PORT=%d", ntohs(conn->client.lsa.sin.sin_port));

	addenv(blk, "REQUEST_METHOD=%s", conn->request_info.request_method);
	addenv(blk, "REMOTE_ADDR=%s", src_addr);
	addenv(blk, "REMOTE_PORT=%d", conn->request_info.remote_port);
	addenv(blk, "REQUEST_URI=%s", conn->request_info.uri);

	/* SCRIPT_NAME */
	addenv(blk,
	       "SCRIPT_NAME=%.*s",
	       (int)strlen(conn->request_info.uri) -
	           ((conn->path_info == NULL) ? 0 : (int)strlen(conn->path_info)),
	       conn->request_info.uri);

	addenv(blk, "SCRIPT_FILENAME=%s", prog);
	if (conn->path_info == NULL) {
		addenv(blk, "PATH_TRANSLATED=%s", conn->ctx->config[DOCUMENT_ROOT]);
	} else {
		addenv(blk,
		       "PATH_TRANSLATED=%s%s",
		       conn->ctx->config[DOCUMENT_ROOT],
		       conn->path_info);
	}

	addenv(blk, "HTTPS=%s", conn->ssl == NULL ? "off" : "on");

	if ((s = mg_get_header(conn, "Content-Type")) != NULL) {
		addenv(blk, "CONTENT_TYPE=%s", s);
	}
	if (conn->request_info.query_string != NULL) {
		addenv(blk, "QUERY_STRING=%s", conn->request_info.query_string);
	}
	if ((s = mg_get_header(conn, "Content-Length")) != NULL) {
		addenv(blk, "CONTENT_LENGTH=%s", s);
	}
	if ((s = getenv("PATH")) != NULL) {
		addenv(blk, "PATH=%s", s);
	}
	if (conn->path_info != NULL) {
		addenv(blk, "PATH_INFO=%s", conn->path_info);
	}

	if (conn->status_code > 0) {
		/* CGI error handler should show the status code */
		addenv(blk, "STATUS=%d", conn->status_code);
	}

#if defined(_WIN32)
	if ((s = getenv("COMSPEC")) != NULL) {
		addenv(blk, "COMSPEC=%s", s);
	}
	if ((s = getenv("SYSTEMROOT")) != NULL) {
		addenv(blk, "SYSTEMROOT=%s", s);
	}
	if ((s = getenv("SystemDrive")) != NULL) {
		addenv(blk, "SystemDrive=%s", s);
	}
	if ((s = getenv("ProgramFiles")) != NULL) {
		addenv(blk, "ProgramFiles=%s", s);
	}
	if ((s = getenv("ProgramFiles(x86)")) != NULL) {
		addenv(blk, "ProgramFiles(x86)=%s", s);
	}
#else
	if ((s = getenv("LD_LIBRARY_PATH")) != NULL) {
		addenv(blk, "LD_LIBRARY_PATH=%s", s);
	}
#endif /* _WIN32 */

	if ((s = getenv("PERLLIB")) != NULL) {
		addenv(blk, "PERLLIB=%s", s);
	}

	if (conn->request_info.remote_user != NULL) {
		addenv(blk, "REMOTE_USER=%s", conn->request_info.remote_user);
		addenv(blk, "%s", "AUTH_TYPE=Digest");
	}

	/* Add all headers as HTTP_* variables */
	for (i = 0; i < conn->request_info.num_headers; i++) {
		p = addenv(blk,
		           "HTTP_%s=%s",
		           conn->request_info.http_headers[i].name,
		           conn->request_info.http_headers[i].value);

		/* Convert variable name into uppercase, and change - to _ */
		for (; *p != '=' && *p != '\0'; p++) {
			if (*p == '-') {
				*p = '_';
			}
			*p = (char)toupper(*(unsigned char *)p);
		}
	}

	/* Add user-specified variables */
	s = conn->ctx->config[CGI_ENVIRONMENT];
	while ((s = next_option(s, &var_vec, NULL)) != NULL) {
		addenv(blk, "%.*s", (int)var_vec.len, var_vec.ptr);
	}

	blk->vars[blk->nvars++] = NULL;
	blk->buf[blk->len++] = '\0';

	/* assert(blk->nvars < (int) ARRAY_SIZE(blk->vars)); */
	/* assert(blk->len > 0); */
	/* assert(blk->len < (int) sizeof(blk->buf)); */

	if ((blk->nvars >= (int)ARRAY_SIZE(blk->vars)) || (blk->len <= 0) ||
	    (blk->len >= (int)sizeof(blk->buf))) {
		/* TODO (mid): this statement is useless. Check original intention and
		 * proper replacement. */
		return;
	}
}

static void handle_cgi_request(struct mg_connection *conn, const char *prog)
{
	char *buf;
	size_t buflen;
	int headers_len, data_len, i, fdin[2] = {0, 0}, fdout[2] = {0, 0};
	const char *status, *status_text, *connection_state;
	char *pbuf, dir[PATH_MAX], *p;
	struct mg_request_info ri;
	struct cgi_env_block blk;
	FILE *in = NULL, *out = NULL;
	struct file fout = STRUCT_FILE_INITIALIZER;
	pid_t pid = (pid_t)-1;

	if (conn == NULL) {
		return;
	}

	buf = NULL;
	buflen = 16384;
	prepare_cgi_environment(conn, prog, &blk);

	/* CGI must be executed in its own directory. 'dir' must point to the
	 * directory containing executable program, 'p' must point to the
	 * executable program name relative to 'dir'. */
	(void)mg_snprintf(conn, dir, sizeof(dir), "%s", prog);
	if ((p = strrchr(dir, '/')) != NULL) {
		*p++ = '\0';
	} else {
		dir[0] = '.', dir[1] = '\0';
		p = (char *)prog;
	}

	if (pipe(fdin) != 0 || pipe(fdout) != 0) {
		send_http_error(
		    conn, 500, "Error: Cannot create CGI pipe: %s", strerror(ERRNO));
		goto done;
	}

	pid = spawn_process(conn, p, blk.buf, blk.vars, fdin[0], fdout[1], dir);
	if (pid == (pid_t)-1) {
		send_http_error(conn,
		                500,
		                "Error: Cannot spawn CGI process [%s]: %s",
		                prog,
		                strerror(ERRNO));
		goto done;
	}

	/* Make sure child closes all pipe descriptors. It must dup them to 0,1 */
	set_close_on_exec((SOCKET)fdin[0], conn);
	set_close_on_exec((SOCKET)fdin[1], conn);
	set_close_on_exec((SOCKET)fdout[0], conn);
	set_close_on_exec((SOCKET)fdout[1], conn);

	/* Parent closes only one side of the pipes.
	 * If we don't mark them as closed, close() attempt before
	 * return from this function throws an exception on Windows.
	 * Windows does not like when closed descriptor is closed again. */
	(void)close(fdin[0]);
	(void)close(fdout[1]);
	fdin[0] = fdout[1] = -1;

	if ((in = fdopen(fdin[1], "wb")) == NULL) {
		send_http_error(conn,
		                500,
		                "Error: CGI can not open fdin\nfopen: %s",
		                strerror(ERRNO));
		goto done;
	}
	if ((out = fdopen(fdout[0], "rb")) == NULL) {
		send_http_error(conn,
		                500,
		                "Error: CGI can not open fdout\nfopen: %s",
		                strerror(ERRNO));
		goto done;
	}

	setbuf(in, NULL);
	setbuf(out, NULL);
	fout.fp = out;

	/* Send POST or PUT data to the CGI process if needed */
	if (!mg_strcasecmp(conn->request_info.request_method, "POST") ||
	    !mg_strcasecmp(conn->request_info.request_method, "PUT")) {
		/* This is a POST/PUT request */
		if (!forward_body_data(conn, in, INVALID_SOCKET, NULL)) {
			/* Error sending the body data */
			goto done;
		}
	}

	/* Close so child gets an EOF. */
	fclose(in);
	in = NULL;
	fdin[1] = -1;

	/* Now read CGI reply into a buffer. We need to set correct
	 * status code, thus we need to see all HTTP headers first.
	 * Do not send anything back to client, until we buffer in all
	 * HTTP headers. */
	data_len = 0;
	buf = (char *)mg_malloc(buflen);
	if (buf == NULL) {
		send_http_error(conn,
		                500,
		                "Error: Not enough memory for CGI buffer (%u bytes)",
		                (unsigned int)buflen);
		goto done;
	}
	headers_len = read_request(out, conn, buf, (int)buflen, &data_len);
	if (headers_len <= 0) {
		send_http_error(conn,
		                500,
		                "Error: CGI program sent malformed or too big "
		                "(>%u bytes) HTTP headers: [%.*s]",
		                (unsigned)buflen,
		                data_len,
		                buf);
		goto done;
	}
	pbuf = buf;
	buf[headers_len - 1] = '\0';
	parse_http_headers(&pbuf, &ri);

	/* Make up and send the status line */
	status_text = "OK";
	if ((status = get_header(&ri, "Status")) != NULL) {
		conn->status_code = atoi(status);
		status_text = status;
		while (isdigit(*(unsigned char *)status_text) || *status_text == ' ') {
			status_text++;
		}
	} else if (get_header(&ri, "Location") != NULL) {
		conn->status_code = 302;
	} else {
		conn->status_code = 200;
	}
	connection_state = get_header(&ri, "Connection");
	if (connection_state == NULL ||
	    mg_strcasecmp(connection_state, "keep-alive")) {
		conn->must_close = 1;
	}
	(void)mg_printf(conn, "HTTP/1.1 %d %s\r\n", conn->status_code, status_text);

	/* Send headers */
	for (i = 0; i < ri.num_headers; i++) {
		mg_printf(conn,
		          "%s: %s\r\n",
		          ri.http_headers[i].name,
		          ri.http_headers[i].value);
	}
	mg_write(conn, "\r\n", 2);

	/* Send chunk of data that may have been read after the headers */
	conn->num_bytes_sent +=
	    mg_write(conn, buf + headers_len, (size_t)(data_len - headers_len));

	/* Read the rest of CGI output and send to the client */
	send_file_data(conn, &fout, 0, INT64_MAX);

done:
	if (pid != (pid_t)-1) {
		kill(pid, SIGKILL);
#if !defined(_WIN32)
		{
			int st;
			while (waitpid(pid, &st, 0) != -1)
				; /* clean zombies */
		}
#endif
	}
	if (fdin[0] != -1) {
		close(fdin[0]);
	}
	if (fdout[1] != -1) {
		close(fdout[1]);
	}

	if (in != NULL) {
		fclose(in);
	} else if (fdin[1] != -1) {
		close(fdin[1]);
	}

	if (out != NULL) {
		fclose(out);
	} else if (fdout[0] != -1) {
		close(fdout[0]);
	}
	if (buf != NULL) {
		mg_free(buf);
	}
}
#endif /* !NO_CGI */

/* For a given PUT path, create all intermediate subdirectories.
 * Return  0  if the path itself is a directory.
 * Return  1  if the path leads to a file.
 * Return -1  for if the path is too long.
 * Return -2  if path can not be created.
*/
static int put_dir(struct mg_connection *conn, const char *path)
{
	char buf[PATH_MAX];
	const char *s, *p;
	struct file file = STRUCT_FILE_INITIALIZER;
	size_t len;
	int res = 1;

	for (s = p = path + 2; (p = strchr(s, '/')) != NULL; s = ++p) {
		len = (size_t)(p - path);
		if (len >= sizeof(buf)) {
			/* path too long */
			res = -1;
			break;
		}
		memcpy(buf, path, len);
		buf[len] = '\0';

		/* Try to create intermediate directory */
		DEBUG_TRACE("mkdir(%s)", buf);
		if (!mg_stat(conn, buf, &file) && mg_mkdir(buf, 0755) != 0) {
			/* path does not exixt and can not be created */
			res = -2;
			break;
		}

		/* Is path itself a directory? */
		if (p[1] == '\0') {
			res = 0;
		}
	}

	return res;
}

static void mkcol(struct mg_connection *conn, const char *path)
{
	int rc, body_len;
	struct de de;
	char date[64];
	time_t curtime = time(NULL);

	if (conn == NULL) {
		return;
	}

	/* TODO (mid): Check the send_http_error situations in this function */

	memset(&de.file, 0, sizeof(de.file));
	if (!mg_stat(conn, path, &de.file)) {
		mg_cry(conn,
		       "%s: mg_stat(%s) failed: %s",
		       __func__,
		       path,
		       strerror(ERRNO));
	}

	if (de.file.last_modified) {
		/* TODO (high): This check does not seem to make any sense ! */
		send_http_error(
		    conn, 405, "Error: mkcol(%s): %s", path, strerror(ERRNO));
		return;
	}

	body_len = conn->data_len - conn->request_len;
	if (body_len > 0) {
		send_http_error(
		    conn, 415, "Error: mkcol(%s): %s", path, strerror(ERRNO));
		return;
	}

	rc = mg_mkdir(path, 0755);

	if (rc == 0) {
		conn->status_code = 201;
		gmt_time_string(date, sizeof(date), &curtime);
		mg_printf(conn,
		          "HTTP/1.1 %d Created\r\nDate: %s\r\nContent-Length: "
		          "0\r\nConnection: %s\r\n\r\n",
		          conn->status_code,
		          date,
		          suggest_connection_header(conn));
	} else if (rc == -1) {
		if (errno == EEXIST) {
			send_http_error(
			    conn, 405, "Error:mkcol(%s): %s", path, strerror(ERRNO));
		} else if (errno == EACCES) {
			send_http_error(
			    conn, 403, "Error: mkcol(%s): %s", path, strerror(ERRNO));
		} else if (errno == ENOENT) {
			send_http_error(
			    conn, 409, "Error: mkcol(%s): %s", path, strerror(ERRNO));
		} else {
			send_http_error(conn, 500, "fopen(%s): %s", path, strerror(ERRNO));
		}
	}
}

static void put_file(struct mg_connection *conn, const char *path)
{
	struct file file = STRUCT_FILE_INITIALIZER;
	const char *range;
	int64_t r1, r2;
	int rc;
	char date[64];
	time_t curtime = time(NULL);

	if (conn == NULL) {
		return;
	}

	if (mg_stat(conn, path, &file)) {
		/* File already exists */
		conn->status_code = 200;

		if (file.is_directory) {
			/* This is an already existing directory,
			 * so there is nothing to do for the server. */
			rc = 0;

		} else {
			/* File exists and is not a directory. */
			/* Can it be replaced? */

			if (file.membuf != NULL) {
				/* This is an "in-memory" file, that can not be replaced */
				send_http_error(
				    conn,
				    405,
				    "Error: Put not possible\nReplacing %s is not supported",
				    path);
				return;
			}

			/* Check if the server may write this file */
			if (access(path, W_OK) == 0) {
				/* Access granted */
				conn->status_code = 200;
				rc = 1;
			} else {
				send_http_error(
				    conn,
				    403,
				    "Error: Put not possible\nReplacing %s is not allowed",
				    path);
				return;
			}
		}
	} else {
		/* File should be created */
		conn->status_code = 201;
		rc = put_dir(conn, path);
	}

	if (rc == 0) {
		/* put_dir returns 0 if path is a directory */
		gmt_time_string(date, sizeof(date), &curtime);
		mg_printf(conn,
		          "HTTP/1.1 %d %s\r\n"
		          "Date: %s\r\n"
		          "Content-Length: 0\r\n"
		          "Connection: %s\r\n\r\n",
		          conn->status_code,
		          mg_get_response_code_text(conn->status_code, NULL),
		          date,
		          suggest_connection_header(conn));

		/* Request to create a directory has been fulfilled successfully.
		 * No need to put a file. */
		return;
	}

	if (rc == -1) {
		/* put_dir returns -1 if the path is too long */
		send_http_error(conn,
		                414,
		                "Error: Path too long\nput_dir(%s): %s",
		                path,
		                strerror(ERRNO));
		return;
	}

	if (rc == -2) {
		/* put_dir returns -2 if the directory can not be created */
		send_http_error(conn,
		                500,
		                "Error: Can not create directory\nput_dir(%s): %s",
		                path,
		                strerror(ERRNO));
		return;
	}

	/* A file should be created or overwritten. */
	if (!mg_fopen(conn, path, "wb+", &file) || file.fp == NULL) {
		mg_fclose(&file);
		send_http_error(conn,
		                500,
		                "Error: Can not create file\nfopen(%s): %s",
		                path,
		                strerror(ERRNO));
		return;
	}

	fclose_on_exec(&file, conn);
	range = mg_get_header(conn, "Content-Range");
	r1 = r2 = 0;
	if (range != NULL && parse_range_header(range, &r1, &r2) > 0) {
		conn->status_code = 206; /* Partial content */
		fseeko(file.fp, r1, SEEK_SET);
	}

	if (!forward_body_data(conn, file.fp, INVALID_SOCKET, NULL)) {
		/* forward_body_data failed.
		 * The error code has already been sent to the client,
		 * and conn->status_code is already set. */
		return;
	}

	gmt_time_string(date, sizeof(date), &curtime);
	mg_printf(conn,
	          "HTTP/1.1 %d %s\r\n"
	          "Date: %s\r\n"
	          "Content-Length: 0\r\n"
	          "Connection: %s\r\n\r\n",
	          conn->status_code,
	          mg_get_response_code_text(conn->status_code, NULL),
	          date,
	          suggest_connection_header(conn));

	mg_fclose(&file);
}

static void delete_file(struct mg_connection *conn, const char *path)
{
	struct de de;
	memset(&de.file, 0, sizeof(de.file));
	if (!mg_stat(conn, path, &de.file)) {
		/* mg_stat returns 0 if the file does not exist */
		send_http_error(
		    conn, 404, "Error: Cannot delete file\nFile %s not found", path);
		return;
	}

	if (de.file.membuf != NULL) {
		/* the file is cached in memory */
		send_http_error(
		    conn,
		    405,
		    "Error: Delete not possible\nDeleting %s is not supported",
		    path);
		return;
	}

	if (de.file.is_directory) {
		remove_directory(conn, path);
		/* TODO (mid): remove_dir does not return success of the operation */
		/* Assume delete is successful: Return 204 without content. */
		send_http_error(conn, 204, "%s", "");
		return;
	}

	/* This is an existing file (not a directory).
	 * Check if write permission is granted. */
	if (access(path, W_OK) != 0) {
		/* File is read only */
		send_http_error(
		    conn,
		    403,
		    "Error: Delete not possible\nDeleting %s is not allowed",
		    path);
		return;
	}

	/* Try to delete it. */
	if (mg_remove(path) == 0) {
		/* Delete was successful: Return 204 without content. */
		send_http_error(conn, 204, "%s", "");
	} else {
		/* Delete not successful (file locked). */
		send_http_error(conn,
		                423,
		                "Error: Cannot delete file\nremove(%s): %s",
		                path,
		                strerror(ERRNO));
	}
}

static void
send_ssi_file(struct mg_connection *, const char *, struct file *, int);

static void do_ssi_include(struct mg_connection *conn,
                           const char *ssi,
                           char *tag,
                           int include_level)
{
	char file_name[MG_BUF_LEN], path[512], *p;
	struct file file = STRUCT_FILE_INITIALIZER;
	size_t len;

	if (conn == NULL) {
		return;
	}

	/* sscanf() is safe here, since send_ssi_file() also uses buffer
	 * of size MG_BUF_LEN to get the tag. So strlen(tag) is
	 * always < MG_BUF_LEN. */
	if (sscanf(tag, " virtual=\"%511[^\"]\"", file_name) == 1) {
		/* File name is relative to the webserver root */
		file_name[511] = 0;
		(void)mg_snprintf(conn,
		                  path,
		                  sizeof(path),
		                  "%s%c%s",
		                  conn->ctx->config[DOCUMENT_ROOT],
		                  '/',
		                  file_name);
	} else if (sscanf(tag, " abspath=\"%511[^\"]\"", file_name) == 1) {
		/* File name is relative to the webserver working directory
		 * or it is absolute system path */
		file_name[511] = 0;
		(void)mg_snprintf(conn, path, sizeof(path), "%s", file_name);
	} else if (sscanf(tag, " file=\"%511[^\"]\"", file_name) == 1 ||
	           sscanf(tag, " \"%511[^\"]\"", file_name) == 1) {
		/* File name is relative to the currect document */
		file_name[511] = 0;
		(void)mg_snprintf(conn, path, sizeof(path), "%s", ssi);
		if ((p = strrchr(path, '/')) != NULL) {
			p[1] = '\0';
		}
		len = strlen(path);
		(void)mg_snprintf(
		    conn, path + len, sizeof(path) - len, "%s", file_name);
	} else {
		mg_cry(conn, "Bad SSI #include: [%s]", tag);
		return;
	}

	if (!mg_fopen(conn, path, "rb", &file)) {
		mg_cry(conn,
		       "Cannot open SSI #include: [%s]: fopen(%s): %s",
		       tag,
		       path,
		       strerror(ERRNO));
	} else {
		fclose_on_exec(&file, conn);
		if (match_prefix(conn->ctx->config[SSI_EXTENSIONS],
		                 strlen(conn->ctx->config[SSI_EXTENSIONS]),
		                 path) > 0) {
			send_ssi_file(conn, path, &file, include_level + 1);
		} else {
			send_file_data(conn, &file, 0, INT64_MAX);
		}
		mg_fclose(&file);
	}
}

#if !defined(NO_POPEN)
static void do_ssi_exec(struct mg_connection *conn, char *tag)
{
	char cmd[1024] = "";
	struct file file = STRUCT_FILE_INITIALIZER;

	if (sscanf(tag, " \"%1023[^\"]\"", cmd) != 1) {
		mg_cry(conn, "Bad SSI #exec: [%s]", tag);
	} else {
		cmd[1023] = 0;
		if ((file.fp = popen(cmd, "r")) == NULL) {
			mg_cry(conn, "Cannot SSI #exec: [%s]: %s", cmd, strerror(ERRNO));
		} else {
			send_file_data(conn, &file, 0, INT64_MAX);
			pclose(file.fp);
		}
	}
}
#endif /* !NO_POPEN */

static int mg_fgetc(struct file *filep, int offset)
{
	if (filep == NULL) {
		return EOF;
	}
	if (filep->membuf != NULL && offset >= 0 &&
	    ((unsigned int)(offset)) < filep->size) {
		return ((unsigned char *)filep->membuf)[offset];
	} else if (filep->fp != NULL) {
		return fgetc(filep->fp);
	} else {
		return EOF;
	}
}

static void send_ssi_file(struct mg_connection *conn,
                          const char *path,
                          struct file *filep,
                          int include_level)
{
	char buf[MG_BUF_LEN];
	int ch, offset, len, in_ssi_tag;

	if (include_level > 10) {
		mg_cry(conn, "SSI #include level is too deep (%s)", path);
		return;
	}

	in_ssi_tag = len = offset = 0;
	while ((ch = mg_fgetc(filep, offset)) != EOF) {
		if (in_ssi_tag && ch == '>') {
			in_ssi_tag = 0;
			buf[len++] = (char)ch;
			buf[len] = '\0';
			/* assert(len <= (int) sizeof(buf)); */
			if (len > (int)sizeof(buf)) {
				break;
			}
			if (len < 6 || memcmp(buf, "<!--#", 5) != 0) {
				/* Not an SSI tag, pass it */
				(void)mg_write(conn, buf, (size_t)len);
			} else {
				if (!memcmp(buf + 5, "include", 7)) {
					do_ssi_include(conn, path, buf + 12, include_level);
#if !defined(NO_POPEN)
				} else if (!memcmp(buf + 5, "exec", 4)) {
					do_ssi_exec(conn, buf + 9);
#endif /* !NO_POPEN */
				} else {
					mg_cry(conn,
					       "%s: unknown SSI "
					       "command: \"%s\"",
					       path,
					       buf);
				}
			}
			len = 0;
		} else if (in_ssi_tag) {
			if (len == 5 && memcmp(buf, "<!--#", 5) != 0) {
				/* Not an SSI tag */
				in_ssi_tag = 0;
			} else if (len == (int)sizeof(buf) - 2) {
				mg_cry(conn, "%s: SSI tag is too large", path);
				len = 0;
			}
			buf[len++] = (char)(ch & 0xff);
		} else if (ch == '<') {
			in_ssi_tag = 1;
			if (len > 0) {
				mg_write(conn, buf, (size_t)len);
			}
			len = 0;
			buf[len++] = (char)(ch & 0xff);
		} else {
			buf[len++] = (char)(ch & 0xff);
			if (len == (int)sizeof(buf)) {
				mg_write(conn, buf, (size_t)len);
				len = 0;
			}
		}
	}

	/* Send the rest of buffered data */
	if (len > 0) {
		mg_write(conn, buf, (size_t)len);
	}
}

static void handle_ssi_file_request(struct mg_connection *conn,
                                    const char *path,
                                    struct file *filep)
{
	char date[64];
	time_t curtime = time(NULL);
	const char *cors1, *cors2, *cors3;

	if (conn == NULL || path == NULL || filep == NULL) {
		return;
	}

	if (mg_get_header(conn, "Origin")) {
		/* Cross-origin resource sharing (CORS). */
		cors1 = "Access-Control-Allow-Origin: ";
		cors2 = conn->ctx->config[ACCESS_CONTROL_ALLOW_ORIGIN];
		cors3 = "\r\n";
	} else {
		cors1 = cors2 = cors3 = "";
	}

	if (!mg_fopen(conn, path, "rb", filep)) {
		/* File exists (precondition for calling this function),
		 * but can not be opened by the server. */
		send_http_error(conn,
		                500,
		                "Error: Cannot read file\nfopen(%s): %s",
		                path,
		                strerror(ERRNO));
	} else {
		conn->must_close = 1;
		gmt_time_string(date, sizeof(date), &curtime);
		fclose_on_exec(filep, conn);
		mg_printf(conn,
		          "HTTP/1.1 200 OK\r\n"
		          "%s%s%s"
		          "Date: %s\r\n"
		          "Content-Type: text/html\r\n"
		          "Connection: %s\r\n\r\n",
		          cors1,
		          cors2,
		          cors3,
		          date,
		          suggest_connection_header(conn));
		send_ssi_file(conn, path, filep, 0);
		mg_fclose(filep);
	}
}

static void send_options(struct mg_connection *conn)
{
	char date[64];
	time_t curtime = time(NULL);

	if (!conn) {
		return;
	}

	conn->status_code = 200;
	conn->must_close = 1;
	gmt_time_string(date, sizeof(date), &curtime);

	mg_printf(conn,
	          "HTTP/1.1 200 OK\r\n"
	          "Date: %s\r\n"
	          "Connection: %s\r\n"
	          "Allow: GET, POST, HEAD, CONNECT, PUT, DELETE, OPTIONS, "
	          "PROPFIND, MKCOL\r\n"
	          "DAV: 1\r\n\r\n",
	          date,
	          suggest_connection_header(conn));
}

/* Writes PROPFIND properties for a collection element */
static void
print_props(struct mg_connection *conn, const char *uri, struct file *filep)
{
	char mtime[64];

	if (conn == NULL || uri == NULL || filep == NULL) {
		return;
	}

	gmt_time_string(mtime, sizeof(mtime), &filep->last_modified);
	conn->num_bytes_sent +=
	    mg_printf(conn,
	              "<d:response>"
	              "<d:href>%s</d:href>"
	              "<d:propstat>"
	              "<d:prop>"
	              "<d:resourcetype>%s</d:resourcetype>"
	              "<d:getcontentlength>%" INT64_FMT "</d:getcontentlength>"
	              "<d:getlastmodified>%s</d:getlastmodified>"
	              "</d:prop>"
	              "<d:status>HTTP/1.1 200 OK</d:status>"
	              "</d:propstat>"
	              "</d:response>\n",
	              uri,
	              filep->is_directory ? "<d:collection/>" : "",
	              filep->size,
	              mtime);
}

static void print_dav_dir_entry(struct de *de, void *data)
{
	char href[PATH_MAX];
	char href_encoded[PATH_MAX];
	struct mg_connection *conn = (struct mg_connection *)data;
	if (!de || !conn) {
		return;
	}
	mg_snprintf(conn,
	            href,
	            sizeof(href),
	            "%s%s",
	            conn->request_info.uri,
	            de->file_name);
	mg_url_encode(href, href_encoded, PATH_MAX - 1);
	print_props(conn, href_encoded, &de->file);
}

static void handle_propfind(struct mg_connection *conn,
                            const char *path,
                            struct file *filep)
{
	const char *depth = mg_get_header(conn, "Depth");
	char date[64];
	time_t curtime = time(NULL);

	gmt_time_string(date, sizeof(date), &curtime);

	if (!conn || !path || !filep) {
		return;
	}

	conn->must_close = 1;
	conn->status_code = 207;
	mg_printf(conn,
	          "HTTP/1.1 207 Multi-Status\r\n"
	          "Date: %s\r\n"
	          "Connection: %s\r\n"
	          "Content-Type: text/xml; charset=utf-8\r\n\r\n",
	          date,
	          suggest_connection_header(conn));

	conn->num_bytes_sent +=
	    mg_printf(conn,
	              "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
	              "<d:multistatus xmlns:d='DAV:'>\n");

	/* Print properties for the requested resource itself */
	print_props(conn, conn->request_info.uri, filep);

	/* If it is a directory, print directory entries too if Depth is not 0 */
	if (filep && conn->ctx && filep->is_directory &&
	    !mg_strcasecmp(conn->ctx->config[ENABLE_DIRECTORY_LISTING], "yes") &&
	    (depth == NULL || strcmp(depth, "0") != 0)) {
		scan_directory(conn, path, conn, &print_dav_dir_entry);
	}

	conn->num_bytes_sent += mg_printf(conn, "%s\n", "</d:multistatus>");
}

void mg_lock_connection(struct mg_connection *conn)
{
	if (conn) {
		(void)pthread_mutex_lock(&conn->mutex);
	}
}

void mg_unlock_connection(struct mg_connection *conn)
{
	if (conn) {
		(void)pthread_mutex_unlock(&conn->mutex);
	}
}

void mg_lock_context(struct mg_context *ctx)
{
	if (ctx) {
		(void)pthread_mutex_lock(&ctx->nonce_mutex);
	}
}

void mg_unlock_context(struct mg_context *ctx)
{
	if (ctx) {
		(void)pthread_mutex_unlock(&ctx->nonce_mutex);
	}
}

#if defined(USE_TIMERS)
#include "timer.inl"
#endif /* USE_TIMERS */

#ifdef USE_LUA
#include "mod_lua.inl"
#endif /* USE_LUA */

#if defined(USE_WEBSOCKET)

/* START OF SHA-1 code
 * Copyright(c) By Steve Reid <steve@edmweb.com> */
#define SHA1HANDSOFF

/* According to current tests (May 2015), the <solarisfixes.h> is not required.
 *
 * #if defined(__sun)
 * #include "solarisfixes.h"
 * #endif
 */

static int is_big_endian(void)
{
	static const int n = 1;
	return ((char *)&n)[0] == 0;
}

union char64long16 {
	unsigned char c[64];
	uint32_t l[16];
};

#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

static uint32_t blk0(union char64long16 *block, int i)
{
	/* Forrest: SHA expect BIG_ENDIAN, swap if LITTLE_ENDIAN */
	if (!is_big_endian()) {
		block->l[i] = (rol(block->l[i], 24) & 0xFF00FF00) |
		              (rol(block->l[i], 8) & 0x00FF00FF);
	}
	return block->l[i];
}

#define blk(i)                                                                 \
	(block->l[i & 15] = rol(block->l[(i + 13) & 15] ^ block->l[(i + 8) & 15] ^ \
	                            block->l[(i + 2) & 15] ^ block->l[i & 15],     \
	                        1))
#define R0(v, w, x, y, z, i)                                                   \
	z += ((w & (x ^ y)) ^ y) + blk0(block, i) + 0x5A827999 + rol(v, 5);        \
	w = rol(w, 30);
#define R1(v, w, x, y, z, i)                                                   \
	z += ((w & (x ^ y)) ^ y) + blk(i) + 0x5A827999 + rol(v, 5);                \
	w = rol(w, 30);
#define R2(v, w, x, y, z, i)                                                   \
	z += (w ^ x ^ y) + blk(i) + 0x6ED9EBA1 + rol(v, 5);                        \
	w = rol(w, 30);
#define R3(v, w, x, y, z, i)                                                   \
	z += (((w | x) & y) | (w & x)) + blk(i) + 0x8F1BBCDC + rol(v, 5);          \
	w = rol(w, 30);
#define R4(v, w, x, y, z, i)                                                   \
	z += (w ^ x ^ y) + blk(i) + 0xCA62C1D6 + rol(v, 5);                        \
	w = rol(w, 30);

typedef struct {
	uint32_t state[5];
	uint32_t count[2];
	unsigned char buffer[64];
} SHA1_CTX;

static void SHA1Transform(uint32_t state[5], const unsigned char buffer[64])
{
	uint32_t a, b, c, d, e;
	union char64long16 block[1];

	memcpy(block, buffer, 64);
	a = state[0];
	b = state[1];
	c = state[2];
	d = state[3];
	e = state[4];
	R0(a, b, c, d, e, 0);
	R0(e, a, b, c, d, 1);
	R0(d, e, a, b, c, 2);
	R0(c, d, e, a, b, 3);
	R0(b, c, d, e, a, 4);
	R0(a, b, c, d, e, 5);
	R0(e, a, b, c, d, 6);
	R0(d, e, a, b, c, 7);
	R0(c, d, e, a, b, 8);
	R0(b, c, d, e, a, 9);
	R0(a, b, c, d, e, 10);
	R0(e, a, b, c, d, 11);
	R0(d, e, a, b, c, 12);
	R0(c, d, e, a, b, 13);
	R0(b, c, d, e, a, 14);
	R0(a, b, c, d, e, 15);
	R1(e, a, b, c, d, 16);
	R1(d, e, a, b, c, 17);
	R1(c, d, e, a, b, 18);
	R1(b, c, d, e, a, 19);
	R2(a, b, c, d, e, 20);
	R2(e, a, b, c, d, 21);
	R2(d, e, a, b, c, 22);
	R2(c, d, e, a, b, 23);
	R2(b, c, d, e, a, 24);
	R2(a, b, c, d, e, 25);
	R2(e, a, b, c, d, 26);
	R2(d, e, a, b, c, 27);
	R2(c, d, e, a, b, 28);
	R2(b, c, d, e, a, 29);
	R2(a, b, c, d, e, 30);
	R2(e, a, b, c, d, 31);
	R2(d, e, a, b, c, 32);
	R2(c, d, e, a, b, 33);
	R2(b, c, d, e, a, 34);
	R2(a, b, c, d, e, 35);
	R2(e, a, b, c, d, 36);
	R2(d, e, a, b, c, 37);
	R2(c, d, e, a, b, 38);
	R2(b, c, d, e, a, 39);
	R3(a, b, c, d, e, 40);
	R3(e, a, b, c, d, 41);
	R3(d, e, a, b, c, 42);
	R3(c, d, e, a, b, 43);
	R3(b, c, d, e, a, 44);
	R3(a, b, c, d, e, 45);
	R3(e, a, b, c, d, 46);
	R3(d, e, a, b, c, 47);
	R3(c, d, e, a, b, 48);
	R3(b, c, d, e, a, 49);
	R3(a, b, c, d, e, 50);
	R3(e, a, b, c, d, 51);
	R3(d, e, a, b, c, 52);
	R3(c, d, e, a, b, 53);
	R3(b, c, d, e, a, 54);
	R3(a, b, c, d, e, 55);
	R3(e, a, b, c, d, 56);
	R3(d, e, a, b, c, 57);
	R3(c, d, e, a, b, 58);
	R3(b, c, d, e, a, 59);
	R4(a, b, c, d, e, 60);
	R4(e, a, b, c, d, 61);
	R4(d, e, a, b, c, 62);
	R4(c, d, e, a, b, 63);
	R4(b, c, d, e, a, 64);
	R4(a, b, c, d, e, 65);
	R4(e, a, b, c, d, 66);
	R4(d, e, a, b, c, 67);
	R4(c, d, e, a, b, 68);
	R4(b, c, d, e, a, 69);
	R4(a, b, c, d, e, 70);
	R4(e, a, b, c, d, 71);
	R4(d, e, a, b, c, 72);
	R4(c, d, e, a, b, 73);
	R4(b, c, d, e, a, 74);
	R4(a, b, c, d, e, 75);
	R4(e, a, b, c, d, 76);
	R4(d, e, a, b, c, 77);
	R4(c, d, e, a, b, 78);
	R4(b, c, d, e, a, 79);
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	state[4] += e;
	a = b = c = d = e = 0;
	memset(block, '\0', sizeof(block));
}

static void SHA1Init(SHA1_CTX *context)
{
	context->state[0] = 0x67452301;
	context->state[1] = 0xEFCDAB89;
	context->state[2] = 0x98BADCFE;
	context->state[3] = 0x10325476;
	context->state[4] = 0xC3D2E1F0;
	context->count[0] = context->count[1] = 0;
}

static void
SHA1Update(SHA1_CTX *context, const unsigned char *data, uint32_t len)
{
	uint32_t i, j;

	j = context->count[0];
	if ((context->count[0] += len << 3) < j) {
		context->count[1]++;
	}
	context->count[1] += (len >> 29);
	j = (j >> 3) & 63;
	if ((j + len) > 63) {
		memcpy(&context->buffer[j], data, (i = 64 - j));
		SHA1Transform(context->state, context->buffer);
		for (; i + 63 < len; i += 64) {
			SHA1Transform(context->state, &data[i]);
		}
		j = 0;
	} else
		i = 0;
	memcpy(&context->buffer[j], &data[i], len - i);
}

static void SHA1Final(unsigned char digest[20], SHA1_CTX *context)
{
	unsigned i;
	unsigned char finalcount[8], c;

	for (i = 0; i < 8; i++) {
		finalcount[i] = (unsigned char)((context->count[(i >= 4 ? 0 : 1)] >>
		                                 ((3 - (i & 3)) * 8)) &
		                                255);
	}
	c = 0200;
	SHA1Update(context, &c, 1);
	while ((context->count[0] & 504) != 448) {
		c = 0000;
		SHA1Update(context, &c, 1);
	}
	SHA1Update(context, finalcount, 8);
	for (i = 0; i < 20; i++) {
		digest[i] =
		    (unsigned char)((context->state[i >> 2] >> ((3 - (i & 3)) * 8)) &
		                    255);
	}
	memset(context, '\0', sizeof(*context));
	memset(&finalcount, '\0', sizeof(finalcount));
}
/* END OF SHA1 CODE */

static void send_websocket_handshake(struct mg_connection *conn)
{
	static const char *magic = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
	char buf[100], sha[20], b64_sha[sizeof(sha) * 2];
	SHA1_CTX sha_ctx;

	mg_snprintf(conn,
	            buf,
	            sizeof(buf),
	            "%s%s",
	            mg_get_header(conn, "Sec-WebSocket-Key"),
	            magic);
	SHA1Init(&sha_ctx);
	SHA1Update(&sha_ctx, (unsigned char *)buf, (uint32_t)strlen(buf));
	SHA1Final((unsigned char *)sha, &sha_ctx);
	base64_encode((unsigned char *)sha, sizeof(sha), b64_sha);
	mg_printf(conn,
	          "%s%s%s",
	          "HTTP/1.1 101 Switching Protocols\r\n"
	          "Upgrade: websocket\r\n"
	          "Connection: Upgrade\r\n"
	          "Sec-WebSocket-Accept: ",
	          b64_sha,
	          "\r\n\r\n");
}

static void read_websocket(struct mg_connection *conn,
                           mg_websocket_data_handler ws_data_handler,
                           void *callback_data)
{
	/* Pointer to the beginning of the portion of the incoming websocket
	 * message queue.
	 * The original websocket upgrade request is never removed, so the queue
	 * begins after it. */
	unsigned char *buf = (unsigned char *)conn->buf + conn->request_len;
	int n, error, exit_by_callback;

	/* body_len is the length of the entire queue in bytes
	 * len is the length of the current message
	 * data_len is the length of the current message's data payload
	 * header_len is the length of the current message's header */
	size_t i, len, mask_len, data_len, header_len, body_len;

	/* "The masking key is a 32-bit value chosen at random by the client."
	 * http://tools.ietf.org/html/draft-ietf-hybi-thewebsocketprotocol-17#section-5
	*/
	unsigned char mask[4];

	/* data points to the place where the message is stored when passed to the
	 * websocket_data callback.  This is either mem on the stack, or a
	 * dynamically allocated buffer if it is too large. */
	char mem[4096];
	char *data = mem;
	unsigned char mop; /* mask flag and opcode */
	double timeout = -1.0;

	if (conn->ctx->config[WEBSOCKET_TIMEOUT]) {
		timeout = atoi(conn->ctx->config[WEBSOCKET_TIMEOUT]) / 1000.0;
	}
	if ((timeout <= 0.0) && (conn->ctx->config[REQUEST_TIMEOUT])) {
		timeout = atoi(conn->ctx->config[REQUEST_TIMEOUT]) / 1000.0;
	}

	mg_set_thread_name("wsock");

	/* Loop continuously, reading messages from the socket, invoking the
	 * callback, and waiting repeatedly until an error occurs. */
	while (!conn->ctx->stop_flag) {
		header_len = 0;
		assert(conn->data_len >= conn->request_len);
		if ((body_len = conn->data_len - conn->request_len) >= 2) {
			len = buf[1] & 127;
			mask_len = buf[1] & 128 ? 4 : 0;
			if (len < 126 && body_len >= mask_len) {
				data_len = len;
				header_len = 2 + mask_len;
			} else if (len == 126 && body_len >= 4 + mask_len) {
				header_len = 4 + mask_len;
				data_len = ((((int)buf[2]) << 8) + buf[3]);
			} else if (body_len >= 10 + mask_len) {
				header_len = 10 + mask_len;
				data_len = (((uint64_t)ntohl(*(uint32_t *)&buf[2])) << 32) +
				           ntohl(*(uint32_t *)&buf[6]);
			}
		}

		if (header_len > 0 && body_len >= header_len) {
			/* Allocate space to hold websocket payload */
			data = mem;
			if (data_len > sizeof(mem)) {
				data = (char *)mg_malloc(data_len);
				if (data == NULL) {
					/* Allocation failed, exit the loop and then close the
					 * connection */
					mg_cry(conn, "websocket out of memory; closing connection");
					break;
				}
			}

			/* Copy the mask before we shift the queue and destroy it */
			if (mask_len > 0) {
				memcpy(mask, buf + header_len - mask_len, sizeof(mask));
			} else {
				memset(mask, 0, sizeof(mask));
			}

			/* Read frame payload from the first message in the queue into
			 * data and advance the queue by moving the memory in place. */
			assert(body_len >= header_len);
			if (data_len + header_len > body_len) {
				mop = buf[0]; /* current mask and opcode */
				/* Overflow case */
				len = body_len - header_len;
				memcpy(data, buf + header_len, len);
				error = 0;
				while (len < data_len) {
					n = pull(
					    NULL, conn, data + len, (int)(data_len - len), timeout);
					if (n <= 0) {
						error = 1;
						break;
					}
					len += n;
				}
				if (error) {
					mg_cry(conn, "Websocket pull failed; closing connection");
					break;
				}
				conn->data_len = conn->request_len;
			} else {
				mop = buf[0]; /* current mask and opcode, overwritten by
				               * memmove() */
				/* Length of the message being read at the front of the
				 * queue */
				len = data_len + header_len;

				/* Copy the data payload into the data pointer for the
				 * callback */
				memcpy(data, buf + header_len, data_len);

				/* Move the queue forward len bytes */
				memmove(buf, buf + len, body_len - len);

				/* Mark the queue as advanced */
				conn->data_len -= (int)len;
			}

			/* Apply mask if necessary */
			if (mask_len > 0) {
				for (i = 0; i < data_len; ++i) {
					data[i] ^= mask[i & 3];
				}
			}

			/* Exit the loop if callback signals to exit (server side),
			 * or "connection close" opcode received (client side). */
			exit_by_callback = 0;
			if ((ws_data_handler != NULL) &&
			    !ws_data_handler(conn, mop, data, data_len, callback_data)) {
				exit_by_callback = 1;
			}

			if (data != mem) {
				mg_free(data);
			}

			if (exit_by_callback ||
			    ((mop & 0xf) == WEBSOCKET_OPCODE_CONNECTION_CLOSE)) {
				/* Opcode == 8, connection close */
				break;
			}

			/* Not breaking the loop, process next websocket frame. */
		} else {
			/* Read from the socket into the next available location in the
			 * message queue. */
			if ((n = pull(NULL,
			              conn,
			              conn->buf + conn->data_len,
			              conn->buf_size - conn->data_len,
			              timeout)) <= 0) {
				/* Error, no bytes read */
				break;
			}
			conn->data_len += n;
		}
	}

	mg_set_thread_name("worker");
}

int mg_websocket_write(struct mg_connection *conn,
                       int opcode,
                       const char *data,
                       size_t dataLen)
{
	unsigned char header[10];
	size_t headerLen = 1;

	int retval = -1;

	header[0] = 0x80 + (opcode & 0xF);

	/* Frame format: http://tools.ietf.org/html/rfc6455#section-5.2 */
	if (dataLen < 126) {
		/* inline 7-bit length field */
		header[1] = (unsigned char)dataLen;
		headerLen = 2;
	} else if (dataLen <= 0xFFFF) {
		/* 16-bit length field */
		header[1] = 126;
		*(uint16_t *)(header + 2) = htons((uint16_t)dataLen);
		headerLen = 4;
	} else {
		/* 64-bit length field */
		header[1] = 127;
		*(uint32_t *)(header + 2) = htonl((uint64_t)dataLen >> 32);
		*(uint32_t *)(header + 6) = htonl(dataLen & 0xFFFFFFFF);
		headerLen = 10;
	}

	/* Note that POSIX/Winsock's send() is threadsafe
	 * http://stackoverflow.com/questions/1981372/are-parallel-calls-to-send-recv-on-the-same-socket-valid
	 * but mongoose's mg_printf/mg_write is not (because of the loop in
	 * push(), although that is only a problem if the packet is large or
	 * outgoing buffer is full). */
	(void)mg_lock_connection(conn);
	retval = mg_write(conn, header, headerLen);
	retval = mg_write(conn, data, dataLen);
	mg_unlock_connection(conn);

	return retval;
}

static void
handle_websocket_request(struct mg_connection *conn,
                         const char *path,
                         int is_callback_resource,
                         mg_websocket_connect_handler ws_connect_handler,
                         mg_websocket_ready_handler ws_ready_handler,
                         mg_websocket_data_handler ws_data_handler,
                         mg_websocket_close_handler ws_close_handler,
                         void *cbData)
{
	const char *version = mg_get_header(conn, "Sec-WebSocket-Version");
	int lua_websock = 0;

#if !defined(USE_LUA)
	(void)path;
#endif

	/* Step 1: Check websocket protocol version. */
	if (version == NULL || strcmp(version, "13") != 0) {
		/* Reject wrong versions */
		send_http_error(conn, 426, "%s", "Protocol upgrade required");
		return;
	}

	/* Step 2: If a callback is responsible, call it. */
	if (is_callback_resource) {
		if (ws_connect_handler != NULL &&
		    ws_connect_handler(conn, cbData) != 0) {
			/* C callback has returned non-zero, do not proceed with handshake.
			 */
			/* Note that C callbacks are no longer called when Lua is
			 * responsible, so C can no longer filter callbacks for Lua. */
			return;
		}
	}
#if defined(USE_LUA)
	/* Step 3: No callback. Check if Lua is responsible. */
	else {
		/* Step 3.1: Check if Lua is responsible. */
		if (conn->ctx->config[LUA_WEBSOCKET_EXTENSIONS]) {
			lua_websock = match_prefix(
			    conn->ctx->config[LUA_WEBSOCKET_EXTENSIONS],
			    strlen(conn->ctx->config[LUA_WEBSOCKET_EXTENSIONS]),
			    path);
		}

		if (lua_websock) {
			/* Step 3.2: Lua is responsible: call it. */
			conn->lua_websocket_state = lua_websocket_new(path, conn);
			if (!conn->lua_websocket_state) {
				/* Lua rejected the new client */
				return;
			}
		}
	}
#endif

	/* Step 4: Check if there is a responsible websocket handler. */
	if (!is_callback_resource && !lua_websock) {
		/* There is no callback, an Lua is not responsible either. */
		/* Reply with a 404 Not Found or with nothing at all?
		 * TODO (mid): check the websocket standards, how to reply to
		 * requests to invalid websocket addresses. */
		send_http_error(conn, 404, "%s", "Not found");
		return;
	}

	/* Step 5: The websocket connection has been accepted */
	send_websocket_handshake(conn);

	/* Step 6: Call the ready handler */
	if (is_callback_resource) {
		if (ws_ready_handler != NULL) {
			ws_ready_handler(conn, cbData);
		}
#if defined(USE_LUA)
	} else if (lua_websock) {
		if (!lua_websocket_ready(conn, conn->lua_websocket_state)) {
			/* the ready handler returned false */
			return;
		}
#endif
	}

	/* Step 7: Enter the read loop */
	if (is_callback_resource) {
		read_websocket(conn, ws_data_handler, cbData);
#if defined(USE_LUA)
	} else if (lua_websock) {
		read_websocket(conn, lua_websocket_data, conn->lua_websocket_state);
#endif
	}

	/* Step 8: Call the close handler */
	if (ws_close_handler) {
		ws_close_handler(conn, cbData);
	}
}

static int is_websocket_protocol(const struct mg_connection *conn)
{
	const char *host, *upgrade, *connection, *version, *key;

	upgrade = mg_get_header(conn, "Upgrade");
	if (upgrade == NULL) {
		return 0; /* fail early, don't waste time checking other header fields
		             */
	}
	if (!mg_strcasestr(upgrade, "websocket")) {
		return 0;
	}

	connection = mg_get_header(conn, "Connection");
	if (connection == NULL) {
		return 0;
	}
	if (!mg_strcasestr(connection, "upgrade")) {
		return 0;
	}

	host = mg_get_header(conn, "Host");
	key = mg_get_header(conn, "Sec-WebSocket-Key");
	version = mg_get_header(conn, "Sec-WebSocket-Version");

	return (host != NULL && key != NULL && version != NULL);
}
#endif /* !USE_WEBSOCKET */

static int isbyte(int n) { return n >= 0 && n <= 255; }

static int parse_net(const char *spec, uint32_t *net, uint32_t *mask)
{
	int n, a, b, c, d, slash = 32, len = 0;

	if ((sscanf(spec, "%d.%d.%d.%d/%d%n", &a, &b, &c, &d, &slash, &n) == 5 ||
	     sscanf(spec, "%d.%d.%d.%d%n", &a, &b, &c, &d, &n) == 4) &&
	    isbyte(a) && isbyte(b) && isbyte(c) && isbyte(d) && slash >= 0 &&
	    slash < 33) {
		len = n;
		*net = ((uint32_t)a << 24) | ((uint32_t)b << 16) | ((uint32_t)c << 8) |
		       (uint32_t)d;
		*mask = slash ? 0xffffffffU << (32 - slash) : 0;
	}

	return len;
}

static int set_throttle(const char *spec, uint32_t remote_ip, const char *uri)
{
	int throttle = 0;
	struct vec vec, val;
	uint32_t net, mask;
	char mult;
	double v;

	while ((spec = next_option(spec, &vec, &val)) != NULL) {
		mult = ',';
		if (sscanf(val.ptr, "%lf%c", &v, &mult) < 1 || v < 0 ||
		    (lowercase(&mult) != 'k' && lowercase(&mult) != 'm' &&
		     mult != ',')) {
			continue;
		}
		v *= lowercase(&mult) == 'k' ? 1024 : lowercase(&mult) == 'm' ? 1048576
		                                                              : 1;
		if (vec.len == 1 && vec.ptr[0] == '*') {
			throttle = (int)v;
		} else if (parse_net(vec.ptr, &net, &mask) > 0) {
			if ((remote_ip & mask) == net) {
				throttle = (int)v;
			}
		} else if (match_prefix(vec.ptr, vec.len, uri) > 0) {
			throttle = (int)v;
		}
	}

	return throttle;
}

static uint32_t get_remote_ip(const struct mg_connection *conn)
{
	if (!conn) {
		return 0;
	}
	return ntohl(*(uint32_t *)&conn->client.rsa.sin.sin_addr);
}

int mg_upload(struct mg_connection *conn, const char *destination_dir)
{
	/* TODO (mid): set a timeout */
	const char *content_type_header, *boundary_start, *sc;
	char *s;
	char buf[MG_BUF_LEN], path[PATH_MAX], tmp_path[PATH_MAX], fname[1024],
	    boundary[100];
	FILE *fp;
	int bl, n, i, headers_len, boundary_len, eof, len = 0,
	                                              num_uploaded_files = 0;
	struct mg_request_info part_request_info;

	/* Request looks like this:
	 *
	 * POST /upload HTTP/1.1
	 * Host: 127.0.0.1:8080
	 * Content-Length: 244894
	 * Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryRVr
	 *
	 * ------WebKitFormBoundaryRVr
	 * Content-Disposition: form-data; name="file"; filename="accum.png"
	 * Content-Type: image/png
	 *
	 * <89>PNG
	 * <PNG DATA>
	 * ------WebKitFormBoundaryRVr */

	/* Extract boundary string from the Content-Type header */
	if ((content_type_header = mg_get_header(conn, "Content-Type")) == NULL ||
	    (boundary_start = mg_strcasestr(content_type_header, "boundary=")) ==
	        NULL ||
	    (sscanf(boundary_start, "boundary=\"%99[^\"]\"", boundary) == 0 &&
	     sscanf(boundary_start, "boundary=%99s", boundary) == 0) ||
	    boundary[0] == '\0') {
		return num_uploaded_files;
	}

	boundary[99] = 0;
	boundary_len = (int)strlen(boundary);
	bl = boundary_len + 4; /* \r\n--<boundary> */
	for (;;) {
		/* Pull in headers */
		/* assert(len >= 0 && len <= (int) sizeof(buf)); */
		if (len < 0 || len > (int)sizeof(buf)) {
			break;
		}
		while ((n = mg_read(conn, buf + len, sizeof(buf) - (size_t)len)) > 0) {
			len += n;
			/* assert(len <= (int) sizeof(buf)); */
			if (len > (int)sizeof(buf)) {
				break;
			}
		}
		if ((headers_len = get_request_len(buf, len)) <= 0) {
			break;
		}

		/* terminate header */
		buf[headers_len - 1] = 0;

		/* Scan for the boundary string and skip it */
		if (buf[0] == '-' && buf[1] == '-' &&
		    !memcmp(buf + 2, boundary, (size_t)boundary_len)) {
			s = &buf[bl];
		} else {
			s = &buf[2];
		}

		/* Get headers for this part of the multipart message */
		memset(&part_request_info, 0, sizeof(part_request_info));
		parse_http_headers(&s, &part_request_info);
		/* assert(&buf[headers_len-1] == s); */
		if (&buf[headers_len - 1] != s) {
			break;
		}

		/* Fetch file name. */
		sc = get_header(&part_request_info, "Content-Disposition");
		if (!sc) {
			/* invalid part of a multipart message */
			break;
		}

		sc = strstr(sc, "filename");
		if (!sc) {
			/* no filename set */
			break;
		}
		sc += 8; /* skip "filename" */
		fname[0] = '\0';
		IGNORE_UNUSED_RESULT(sscanf(sc, " = \"%1023[^\"]", fname));
		fname[1023] = 0;

		/* Give up if the headers are not what we expect */
		if (fname[0] == '\0') {
			break;
		}

		/* Construct destination file name. Do not allow paths to have
		 * slashes. */
		if ((s = strrchr(fname, '/')) == NULL &&
		    (s = strrchr(fname, '\\')) == NULL) {
			s = fname;
		} else {
			s++;
		}

		/* There data is written to a temporary file first. */
		/* Different users should use a different destination_dir. */
		snprintf(path, sizeof(path) - 1, "%s/%s", destination_dir, s);
		strcpy(tmp_path, path);
		strcat(tmp_path, "~");

		/* We open the file with exclusive lock held. This guarantee us
		 * there is no other thread can save into the same file
		 * simultaneously. */
		fp = NULL;
		/* Open file in binary mode. */
		if ((fp = fopen(tmp_path, "wb")) == NULL) {
			break;
		}

		/* Move data to the beginning of the buffer */
		/* part_request_info is no longer valid after this operation */
		/* assert(len >= headers_len); */
		if (len < headers_len) {
			break;
		}
		memmove(buf, &buf[headers_len], (size_t)(len - headers_len));
		len -= headers_len;

		/* Read POST data, write into file until boundary is found. */
		eof = n = 0;
		do {
			len += n;
			for (i = 0; i < len - bl; i++) {
				if (!memcmp(&buf[i], "\r\n--", 4) &&
				    !memcmp(&buf[i + 4], boundary, (size_t)boundary_len)) {
					/* Found boundary, that's the end of file data. */
					fwrite(buf, 1, (size_t)i, fp);
					eof = 1;
					memmove(buf, &buf[i + bl], (size_t)(len - (i + bl)));
					len -= i + bl;
					break;
				}
			}
			if (!eof && len > bl) {
				fwrite(buf, 1, (size_t)(len - bl), fp);
				memmove(buf, &buf[len - bl], (size_t)bl);
				len = bl;
			}
			n = mg_read(conn, buf + len, sizeof(buf) - ((size_t)(len)));
		} while (!eof && (n > 0));
		fclose(fp);
		if (eof) {
			remove(path);
			rename(tmp_path, path);
			num_uploaded_files++;
			if (conn && conn->ctx && conn->ctx->callbacks.upload != NULL) {
				conn->ctx->callbacks.upload(conn, path);
			}
		} else {
			remove(tmp_path);
		}
	}

	return num_uploaded_files;
}

static int get_first_ssl_listener_index(const struct mg_context *ctx)
{
	unsigned int i;
	int idx = -1;
	if (ctx) {
		for (i = 0; idx == -1 && i < ctx->num_listening_sockets; i++) {
			idx = ctx->listening_sockets[i].is_ssl ? ((int)(i)) : -1;
		}
	}
	return idx;
}

static void redirect_to_https_port(struct mg_connection *conn, int ssl_index)
{
	char host[1025];
	const char *host_header;
	size_t hostlen;

	host_header = mg_get_header(conn, "Host");
	hostlen = sizeof(host);
	if (host_header != NULL) {
		char *pos;

		mg_strlcpy(host, host_header, hostlen);
		host[hostlen - 1] = '\0';
		pos = strchr(host, ':');
		if (pos != NULL) {
			*pos = '\0';
		}
	} else {
		/* Cannot get host from the Host: header.
		 * Fallback to our IP address. */
		if (conn) {
			sockaddr_to_string(host, hostlen, &conn->client.lsa);
		}
	}

	/* Send host, port, uri and (if it exists) ?query_string */
	if (conn) {
		mg_printf(conn,
		          "HTTP/1.1 302 Found\r\nLocation: https://%s:%d%s%s%s\r\n\r\n",
		          host,
		          (int)ntohs(
		              conn->ctx->listening_sockets[ssl_index].lsa.sin.sin_port),
		          conn->request_info.uri,
		          (conn->request_info.query_string == NULL) ? "" : "?",
		          (conn->request_info.query_string == NULL)
		              ? ""
		              : conn->request_info.query_string);
	}
}

static void
mg_set_request_handler_type(struct mg_context *ctx,
                            const char *uri,
                            int is_websocket_handler,
                            int is_delete_request,
                            mg_request_handler handler,
                            mg_websocket_connect_handler connect_handler,
                            mg_websocket_ready_handler ready_handler,
                            mg_websocket_data_handler data_handler,
                            mg_websocket_close_handler close_handler,
                            void *cbdata)
{
	struct mg_request_handler_info *tmp_rh, **lastref;
	size_t urilen = strlen(uri);

	if (is_websocket_handler) {
		/* assert(handler == NULL); */
		/* assert(is_delete_request || connect_handler!=NULL ||
		 *        ready_handler!=NULL || data_handler!=NULL ||
		 *        close_handler!=NULL);
		 */
		if (handler != NULL) {
			return;
		}
		if (!is_delete_request && connect_handler == NULL &&
		    ready_handler == NULL && data_handler == NULL &&
		    close_handler == NULL) {
			return;
		}
	} else {
		/* assert(connect_handler==NULL && ready_handler==NULL &&
		 *        data_handler==NULL && close_handler==NULL); */
		/* assert(is_delete_request || (handler!=NULL));
		 */
		if (connect_handler != NULL || ready_handler != NULL ||
		    data_handler != NULL || close_handler != NULL) {
			return;
		}
		if (!is_delete_request && (handler == NULL)) {
			return;
		}
	}

	if (!ctx) {
		return;
	}

	mg_lock_context(ctx);

	/* first try to find an existing handler */
	lastref = &(ctx->request_handlers);
	for (tmp_rh = ctx->request_handlers; tmp_rh != NULL;
	     tmp_rh = tmp_rh->next) {
		if (tmp_rh->is_websocket_handler == is_websocket_handler) {
			if (urilen == tmp_rh->uri_len && !strcmp(tmp_rh->uri, uri)) {
				if (!is_delete_request) {
					/* update existing handler */
					if (!is_websocket_handler) {
						tmp_rh->handler = handler;
					} else {
						tmp_rh->connect_handler = connect_handler;
						tmp_rh->ready_handler = ready_handler;
						tmp_rh->data_handler = data_handler;
						tmp_rh->close_handler = close_handler;
					}
					tmp_rh->cbdata = cbdata;
				} else {
					/* remove existing handler */
					*lastref = tmp_rh->next;
					mg_free(tmp_rh->uri);
					mg_free(tmp_rh);
				}
				mg_unlock_context(ctx);
				return;
			}
		}
		lastref = &(tmp_rh->next);
	}

	if (is_delete_request) {
		/* no handler to set, this was a remove request to a non-existing
		 * handler */
		mg_unlock_context(ctx);
		return;
	}

	tmp_rh = (struct mg_request_handler_info *)mg_calloc(
	    sizeof(struct mg_request_handler_info), 1);
	if (tmp_rh == NULL) {
		mg_unlock_context(ctx);
		mg_cry(fc(ctx), "%s", "Cannot create new request handler struct, OOM");
		return;
	}
	tmp_rh->uri = mg_strdup(uri);
	if (!tmp_rh->uri) {
		mg_unlock_context(ctx);
		mg_free(tmp_rh);
		mg_cry(fc(ctx), "%s", "Cannot create new request handler struct, OOM");
		return;
	}
	tmp_rh->uri_len = urilen;
	if (!is_websocket_handler) {
		tmp_rh->handler = handler;
	} else {
		tmp_rh->connect_handler = connect_handler;
		tmp_rh->ready_handler = ready_handler;
		tmp_rh->data_handler = data_handler;
		tmp_rh->close_handler = close_handler;
	}
	tmp_rh->cbdata = cbdata;
	tmp_rh->is_websocket_handler = is_websocket_handler;
	tmp_rh->next = NULL;

	*lastref = tmp_rh;
	mg_unlock_context(ctx);
}

void mg_set_request_handler(struct mg_context *ctx,
                            const char *uri,
                            mg_request_handler handler,
                            void *cbdata)
{
	mg_set_request_handler_type(
	    ctx, uri, 0, handler == NULL, handler, NULL, NULL, NULL, NULL, cbdata);
}

void mg_set_websocket_handler(struct mg_context *ctx,
                              const char *uri,
                              mg_websocket_connect_handler connect_handler,
                              mg_websocket_ready_handler ready_handler,
                              mg_websocket_data_handler data_handler,
                              mg_websocket_close_handler close_handler,
                              void *cbdata)
{
	int is_delete_request = (connect_handler == NULL) &&
	                        (ready_handler == NULL) && (data_handler == NULL) &&
	                        (close_handler == NULL);
	mg_set_request_handler_type(ctx,
	                            uri,
	                            1,
	                            is_delete_request,
	                            NULL,
	                            connect_handler,
	                            ready_handler,
	                            data_handler,
	                            close_handler,
	                            cbdata);
}

static int get_request_handler(struct mg_connection *conn,
                               int is_websocket_request,
                               mg_request_handler *handler,
                               mg_websocket_connect_handler *connect_handler,
                               mg_websocket_ready_handler *ready_handler,
                               mg_websocket_data_handler *data_handler,
                               mg_websocket_close_handler *close_handler,
                               void **cbdata)
{
	const struct mg_request_info *request_info = mg_get_request_info(conn);
	if (request_info) {
		const char *uri = request_info->uri;
		size_t urilen = strlen(uri);
		struct mg_request_handler_info *tmp_rh;

		if (!conn || !conn->ctx) {
			return 0;
		}

		mg_lock_context(conn->ctx);

		/* first try for an exact match */
		for (tmp_rh = conn->ctx->request_handlers; tmp_rh != NULL;
		     tmp_rh = tmp_rh->next) {
			if (tmp_rh->is_websocket_handler == is_websocket_request) {
				if (urilen == tmp_rh->uri_len && !strcmp(tmp_rh->uri, uri)) {
					if (is_websocket_request) {
						*connect_handler = tmp_rh->connect_handler;
						*ready_handler = tmp_rh->ready_handler;
						*data_handler = tmp_rh->data_handler;
						*close_handler = tmp_rh->close_handler;
					} else {
						*handler = tmp_rh->handler;
					}
					*cbdata = tmp_rh->cbdata;
					mg_unlock_context(conn->ctx);
					return 1;
				}
			}
		}

		/* next try for a partial match, we will accept uri/something */
		for (tmp_rh = conn->ctx->request_handlers; tmp_rh != NULL;
		     tmp_rh = tmp_rh->next) {
			if (tmp_rh->is_websocket_handler == is_websocket_request) {
				if (tmp_rh->uri_len < urilen && uri[tmp_rh->uri_len] == '/' &&
				    memcmp(tmp_rh->uri, uri, tmp_rh->uri_len) == 0) {
					if (is_websocket_request) {
						*connect_handler = tmp_rh->connect_handler;
						*ready_handler = tmp_rh->ready_handler;
						*data_handler = tmp_rh->data_handler;
						*close_handler = tmp_rh->close_handler;
					} else {
						*handler = tmp_rh->handler;
					}
					*cbdata = tmp_rh->cbdata;
					mg_unlock_context(conn->ctx);
					return 1;
				}
			}
		}

		/* finally try for pattern match */
		for (tmp_rh = conn->ctx->request_handlers; tmp_rh != NULL;
		     tmp_rh = tmp_rh->next) {
			if (tmp_rh->is_websocket_handler == is_websocket_request) {
				if (match_prefix(tmp_rh->uri, tmp_rh->uri_len, uri) > 0) {
					if (is_websocket_request) {
						*connect_handler = tmp_rh->connect_handler;
						*ready_handler = tmp_rh->ready_handler;
						*data_handler = tmp_rh->data_handler;
						*close_handler = tmp_rh->close_handler;
					} else {
						*handler = tmp_rh->handler;
					}
					*cbdata = tmp_rh->cbdata;
					mg_unlock_context(conn->ctx);
					return 1;
				}
			}
		}

		mg_unlock_context(conn->ctx);
	}
	return 0; /* none found */
}

#if defined(USE_WEBSOCKET)
static int
deprecated_websocket_connect_wrapper(const struct mg_connection *conn,
                                     void *cbdata)
{
	struct mg_callbacks *pcallbacks = (struct mg_callbacks *)cbdata;
	if (pcallbacks->websocket_connect) {
		return pcallbacks->websocket_connect(conn);
	}
	/* No handler set - assume "OK" */
	return 0;
}

static void deprecated_websocket_ready_wrapper(struct mg_connection *conn,
                                               void *cbdata)
{
	struct mg_callbacks *pcallbacks = (struct mg_callbacks *)cbdata;
	if (pcallbacks->websocket_ready) {
		pcallbacks->websocket_ready(conn);
	}
}

static int deprecated_websocket_data_wrapper(
    struct mg_connection *conn, int bits, char *data, size_t len, void *cbdata)
{
	struct mg_callbacks *pcallbacks = (struct mg_callbacks *)cbdata;
	if (pcallbacks->websocket_data) {
		return pcallbacks->websocket_data(conn, bits, data, len);
	}
	/* No handler set - assume "OK" */
	return 1;
}
#endif

/* This is the heart of the Civetweb's logic.
 * This function is called when the request is read, parsed and validated,
 * and Civetweb must decide what action to take: serve a file, or
 * a directory, or call embedded function, etcetera. */
static void handle_request(struct mg_connection *conn)
{
	if (conn) {
		struct mg_request_info *ri = &conn->request_info;
		char path[PATH_MAX];
		int uri_len, ssl_index, is_found, is_script_resource,
		    is_websocket_request, is_put_or_delete_request,
		    is_callback_resource;
		int i;
		struct file file = STRUCT_FILE_INITIALIZER;
		time_t curtime = time(NULL);
		mg_request_handler callback_handler = NULL;
		mg_websocket_connect_handler ws_connect_handler = NULL;
		mg_websocket_ready_handler ws_ready_handler = NULL;
		mg_websocket_data_handler ws_data_handler = NULL;
		mg_websocket_close_handler ws_close_handler = NULL;
		void *callback_data = NULL;
#if !defined(NO_FILES)
		char date[64];
#endif

		path[0] = 0;

		if (!ri) {
			return;
		}

		/* 1. get the request url */
		/* 1.1. split into url and query string */
		if ((conn->request_info.query_string = strchr(ri->uri, '?')) != NULL) {
			*((char *)conn->request_info.query_string++) = '\0';
		}
		uri_len = (int)strlen(ri->uri);

		/* 1.2. decode url (if config says so) */
		if (should_decode_url(conn)) {
			mg_url_decode(ri->uri, uri_len, (char *)ri->uri, uri_len + 1, 0);
		}

		/* 1.3. clean URIs, so a path like allowed_dir/../forbidden_file is not
		 * possible */
		remove_double_dots_and_double_slashes((char *)ri->uri);

		/* step 1. completed, the url is known now */
		DEBUG_TRACE("URL: %s", ri->uri);

		/* 2. do a https redirect, if required */
		if (!conn->client.is_ssl && conn->client.ssl_redir) {
			ssl_index = get_first_ssl_listener_index(conn->ctx);
			if (ssl_index >= 0) {
				redirect_to_https_port(conn, ssl_index);
			} else {
				/* A http to https forward port has been specified,
				 * but no https port to forward to. */
				send_http_error(conn,
				                503,
				                "%s",
				                "Error: SSL forward not configured properly");
				mg_cry(conn, "Can not redirect to SSL, no SSL port available");
			}
			return;
		}

		/* 3. if this ip has limited speed, set it for this connection */
		conn->throttle = set_throttle(
		    conn->ctx->config[THROTTLE], get_remote_ip(conn), ri->uri);

		/* 4. call a "handle everything" callback, if registered */
		if (conn->ctx->callbacks.begin_request != NULL) {
			/* Note that since V1.7 the "begin_request" function is called
			 * before an authorization check. If an authorization check is
			 * required, use a request_handler instead. */
			i = conn->ctx->callbacks.begin_request(conn);
			switch (i) {
			case 1:
				/* callback already processed the request */
				return;
			case 0:
				/* civetweb should process the request */
				break;
			default:
				/* unspecified - may change with the next version */
				return;
			}
		}

		/* request not yet handled by a handler or redirect, so the request
		 * is processed here */

		/* 5. interpret the url to find out how the request must be handled */
		/* 5.1. first test, if the request targets the regular http(s)://
		 * protocol namespace or the websocket ws(s):// protocol namespace. */
		is_websocket_request = is_websocket_protocol(conn);

		/* 5.2. check if the request will be handled by a callback */
		if (get_request_handler(conn,
		                        is_websocket_request,
		                        &callback_handler,
		                        &ws_connect_handler,
		                        &ws_ready_handler,
		                        &ws_data_handler,
		                        &ws_close_handler,
		                        &callback_data)) {
			/* 5.2.1. A callback will handle this request. All requests handled
			 * by a callback have to be considered as requests to a script
			 * resource. */
			is_callback_resource = 1;
			is_script_resource = 1;
			is_put_or_delete_request = is_put_or_delete_method(conn);
		} else {
		no_callback_resource:
			/* 5.2.2. No callback is responsible for this request. The URI
			 * addresses a file based resource (static content or Lua/cgi
			 * scripts in the file system). */
			is_callback_resource = 0;
			interpret_uri(conn,
			              path,
			              sizeof(path),
			              &file,
			              &is_found,
			              &is_script_resource,
			              &is_websocket_request,
			              &is_put_or_delete_request);
		}

		/* 6. authorization check */
		if (is_put_or_delete_request && !is_script_resource &&
		    !is_callback_resource) {
/* 6.1. this request is a PUT/DELETE to a real file */
/* 6.1.1. thus, the server must have real files */
#if defined(NO_FILES)
			if (1) {
#else
			if (conn->ctx->config[DOCUMENT_ROOT] == NULL) {
#endif
				/* This server does not have any real files, thus the
				 * PUT/DELETE methods are not valid. */
				send_http_error(conn,
				                405,
				                "%s method not allowed",
				                conn->request_info.request_method);
				return;
			}

			/* 6.1.2. Check if put authorization for static files is available.
			 */
			if (!is_authorized_for_put(conn)) {
				send_authorization_request(conn);
				return;
			}

		} else {
			/* 6.2. This is either a OPTIONS, GET, HEAD or POST request,
			 * or it is a PUT or DELETE request to a resource that does not
			 * correspond to a file. Check authorization. */
			if (!check_authorization(conn, path)) {
				send_authorization_request(conn);
				return;
			}
		}

		/* request is authorized or does not need authorization */

		/* 7. check if there are request handlers for this uri */
		if (is_callback_resource) {
			if (!is_websocket_request) {
				if (callback_handler(conn, callback_data)) {
					/* Do nothing, callback has served the request */
					discard_unread_request_data(conn);
				} else {
					/* TODO (high): what if the handler did NOT handle the
					 * request */
					/* The last version did handle this as a file request, but
					 * since a file request is not always a script resource,
					 * the authorization check might be different */
					interpret_uri(conn,
					              path,
					              sizeof(path),
					              &file,
					              &is_found,
					              &is_script_resource,
					              &is_websocket_request,
					              &is_put_or_delete_request);
					callback_handler = NULL;

					/* TODO (very low): goto is deprecatedm but for the moment,
					 * a goto is
					 * simpler than some curious loop. */
					/* The situation "callback does not handle the request"
					 * needs to be reconsidered anyway. */
					goto no_callback_resource;
				}
			} else {
#if defined(USE_WEBSOCKET)
				handle_websocket_request(conn,
				                         path,
				                         is_callback_resource,
				                         ws_connect_handler,
				                         ws_ready_handler,
				                         ws_data_handler,
				                         ws_close_handler,
				                         callback_data);
#endif
			}
			return;
		}

/* 8. handle websocket requests */
#if defined(USE_WEBSOCKET)
		if (is_websocket_request) {
			handle_websocket_request(
			    conn,
			    path,
			    !is_script_resource /* could be deprecated global callback */,
			    deprecated_websocket_connect_wrapper,
			    deprecated_websocket_ready_wrapper,
			    deprecated_websocket_data_wrapper,
			    NULL,
			    &conn->ctx->callbacks);
			return;
		} else
#endif

#if defined(NO_FILES)
			/* 9a. In case the server uses only callbacks, this uri is unknown.
			 * Then, all request handling ends here. */
			send_http_error(conn, 404, "%s", "Not Found");

#else
		/* 9b. This request is either for a static file or resource handled
		 * by a script file. Thus, a DOCUMENT_ROOT must exist. */
		if (conn->ctx->config[DOCUMENT_ROOT] == NULL) {
			send_http_error(conn, 404, "%s", "Not Found");
			return;
		}

		/* 10. File is handled by a script. */
		if (is_script_resource) {
			handle_file_based_request(conn, path, &file);
			return;
		}

		/* 11. Handle put/delete/mkcol requests */
		if (is_put_or_delete_request) {
			/* 11.1. PUT method */
			if (!strcmp(ri->request_method, "PUT")) {
				put_file(conn, path);
				return;
			}
			/* 11.2. DELETE method */
			if (!strcmp(ri->request_method, "DELETE")) {
				delete_file(conn, path);
				return;
			}
			/* 11.3. MKCOL method */
			if (!strcmp(ri->request_method, "MKCOL")) {
				mkcol(conn, path);
				return;
			}
			/* 11.4. should never reach this point */
			send_http_error(conn,
			                405,
			                "%s method not allowed",
			                conn->request_info.request_method);
			return;
		}

		/* 11. File does not exist, or it was configured that it should be
		 * hidden */
		if (!is_found || (must_hide_file(conn, path))) {
			send_http_error(conn, 404, "%s", "Not found");
			return;
		}

		/* 12. Directories uris should end with a slash */
		if (file.is_directory && ri->uri[uri_len - 1] != '/') {
			gmt_time_string(date, sizeof(date), &curtime);
			mg_printf(conn,
			          "HTTP/1.1 301 Moved Permanently\r\n"
			          "Location: %s/\r\n"
			          "Date: %s\r\n"
			          "Content-Length: 0\r\n"
			          "Connection: %s\r\n\r\n",
			          ri->uri,
			          date,
			          suggest_connection_header(conn));
			return;
		}

		/* 13. Handle other methods than GET/HEAD */
		/* 13.1. Handle PROPFIND */
		if (!strcmp(ri->request_method, "PROPFIND")) {
			handle_propfind(conn, path, &file);
			return;
		}
		/* 13.2. Handle OPTIONS for files */
		if (!strcmp(ri->request_method, "OPTIONS")) {
			/* This standard handler is only used for real files.
			 * Scripts should support the OPTIONS method themselves, to allow a
			 * maximum flexibility.
			 * Lua and CGI scripts may fully support CORS this way (including
			 * preflights). */
			send_options(conn);
			return;
		}
		/* 13.3. everything but GET and HEAD (e.g. POST) */
		if (0 != strcmp(ri->request_method, "GET") &&
		    0 != strcmp(ri->request_method, "HEAD")) {
			send_http_error(conn,
			                405,
			                "%s method not allowed",
			                conn->request_info.request_method);
			return;
		}

		/* 14. directories */
		if (file.is_directory) {
			if (substitute_index_file(conn, path, sizeof(path), &file)) {
				/* 14.1. use a substitute file */
				/* TODO (high): substitute index may be a script resource.
				 * define what should be possible in this case. */
			} else {
				/* 14.2. no substitute file */
				if (!mg_strcasecmp(conn->ctx->config[ENABLE_DIRECTORY_LISTING],
				                   "yes")) {
					handle_directory_request(conn, path);
				} else {
					send_http_error(
					    conn, 403, "%s", "Error: Directory listing denied");
				}
				return;
			}
		}

		handle_file_based_request(conn, path, &file);
#endif /* !defined(NO_FILES) */

#if 0
            /* Perform redirect and auth checks before calling begin_request()
             * handler.
             * Otherwise, begin_request() would need to perform auth checks and
             * redirects. */
#endif
	}
	return;
}

static void handle_file_based_request(struct mg_connection *conn,
                                      const char *path,
                                      struct file *file)
{
	if (!conn || !conn->ctx) {
		return;
	}

	if (0) {
#ifdef USE_LUA
	} else if (match_prefix(
	               conn->ctx->config[LUA_SERVER_PAGE_EXTENSIONS],
	               strlen(conn->ctx->config[LUA_SERVER_PAGE_EXTENSIONS]),
	               path) > 0) {
		/* Lua server page: an SSI like page containing mostly plain html code
		 * plus some tags with server generated contents. */
		handle_lsp_request(conn, path, file, NULL);
	} else if (match_prefix(conn->ctx->config[LUA_SCRIPT_EXTENSIONS],
	                        strlen(conn->ctx->config[LUA_SCRIPT_EXTENSIONS]),
	                        path) > 0) {
		/* Lua in-server module script: a CGI like script used to generate the
		 * entire reply. */
		mg_exec_lua_script(conn, path, NULL);
#endif
#if !defined(NO_CGI)
	} else if (match_prefix(conn->ctx->config[CGI_EXTENSIONS],
	                        strlen(conn->ctx->config[CGI_EXTENSIONS]),
	                        path) > 0) {
		/* CGI scripts may support all HTTP methods */
		handle_cgi_request(conn, path);
#endif /* !NO_CGI */
	} else if (match_prefix(conn->ctx->config[SSI_EXTENSIONS],
	                        strlen(conn->ctx->config[SSI_EXTENSIONS]),
	                        path) > 0) {
		handle_ssi_file_request(conn, path, file);
	} else if ((!conn->in_error_handler) && is_not_modified(conn, file)) {
		/* Send 304 "Not Modified" - this must not send any body data */
		send_http_error(conn, 304, "%s", "");
	} else {
		handle_static_file_request(conn, path, file);
	}
}

static void close_all_listening_sockets(struct mg_context *ctx)
{
	unsigned int i;
	if (!ctx) {
		return;
	}

	for (i = 0; i < ctx->num_listening_sockets; i++) {
		closesocket(ctx->listening_sockets[i].sock);
		ctx->listening_sockets[i].sock = INVALID_SOCKET;
	}
	mg_free(ctx->listening_sockets);
	ctx->listening_sockets = NULL;
	mg_free(ctx->listening_ports);
	ctx->listening_ports = NULL;
}


/* Valid listening port specification is: [ip_address:]port[s]
 * Examples for IPv4: 80, 443s, 127.0.0.1:3128, 1.2.3.4:8080s
 * Examples for IPv6: [::]:80, [::1]:80,
 *   [FEDC:BA98:7654:3210:FEDC:BA98:7654:3210]:443s
 *   see https://tools.ietf.org/html/rfc3513#section-2.2 */
static int parse_port_string(const struct vec *vec, struct socket *so)
{
	unsigned int a, b, c, d, port;
	int ch, len;
#if defined(USE_IPV6)
	char buf[100] = {0};
#endif

	/* MacOS needs that. If we do not zero it, subsequent bind() will fail.
	 * Also, all-zeroes in the socket address means binding to all addresses
	 * for both IPv4 and IPv6 (INADDR_ANY and IN6ADDR_ANY_INIT). */
	memset(so, 0, sizeof(*so));
	so->lsa.sin.sin_family = AF_INET;

	if (sscanf(vec->ptr, "%u.%u.%u.%u:%u%n", &a, &b, &c, &d, &port, &len) ==
	    5) {
		/* Bind to a specific IPv4 address, e.g. 192.168.1.5:8080 */
		so->lsa.sin.sin_addr.s_addr =
		    htonl((a << 24) | (b << 16) | (c << 8) | d);
		so->lsa.sin.sin_port = htons((uint16_t)port);
#if defined(USE_IPV6)
	} else if (sscanf(vec->ptr, "[%49[^]]]:%u%n", buf, &port, &len) == 2 &&
	           mg_inet_pton(
	               AF_INET6, buf, &so->lsa.sin6, sizeof(so->lsa.sin6))) {
		/* IPv6 address, examples: see above */
		/* so->lsa.sin6.sin6_family = AF_INET6; already set by mg_inet_pton */
		so->lsa.sin6.sin6_port = htons((uint16_t)port);
#endif
	} else if (sscanf(vec->ptr, "%u%n", &port, &len) == 1) {
		/* If only port is specified, bind to IPv4, INADDR_ANY */
		so->lsa.sin.sin_port = htons((uint16_t)port);
	} else {
		/* Parsing failure. Make port invalid. */
		port = 0;
		len = 0;
	}

	/* sscanf and the option splitting code ensure the following condition */
	if ((len < 0) && ((unsigned)len > (unsigned)vec->len)) {
		return 0;
	}
	ch = vec->ptr[len]; /* Next character after the port number */
	so->is_ssl = (ch == 's');
	so->ssl_redir = (ch == 'r');

	/* Make sure the port is valid and vector ends with 's', 'r' or ',' */
	return is_valid_port(port) &&
	       (ch == '\0' || ch == 's' || ch == 'r' || ch == ',');
}

static int set_ports_option(struct mg_context *ctx)
{
	const char *list = ctx->config[LISTENING_PORTS];
	int on = 1;
#if defined(USE_IPV6)
	int off = 0;
#endif
	struct vec vec;
	struct socket so, *ptr;

	in_port_t *portPtr;
	union usa usa;
	socklen_t len;

	int portsTotal = 0;
	int portsOk = 0;

	if (!ctx) {
		return 0;
	}

	memset(&so, 0, sizeof(so));
	memset(&usa, 0, sizeof(usa));
	len = sizeof(usa);

	while ((list = next_option(list, &vec, NULL)) != NULL) {

		portsTotal++;

		if (!parse_port_string(&vec, &so)) {
			mg_cry(fc(ctx),
			       "%.*s: invalid port spec (entry %i). Expecting list of: %s",
			       (int)vec.len,
			       vec.ptr,
			       portsTotal,
			       "[IP_ADDRESS:]PORT[s|r]");
			continue;
		}

		if (so.is_ssl && ctx->ssl_ctx == NULL) {

			mg_cry(fc(ctx),
			       "Cannot add SSL socket (entry %i). Is -ssl_certificate "
			       "option set?",
			       portsTotal);
			continue;
		}

		if ((so.sock = socket(so.lsa.sa.sa_family, SOCK_STREAM, 6)) ==
		    INVALID_SOCKET) {

			mg_cry(fc(ctx), "cannot create socket (entry %i)", portsTotal);
			continue;
		}

#ifdef _WIN32
		/* Windows SO_REUSEADDR lets many procs binds to a
		 * socket, SO_EXCLUSIVEADDRUSE makes the bind fail
		 * if someone already has the socket -- DTL */
		/* NOTE: If SO_EXCLUSIVEADDRUSE is used,
		 * Windows might need a few seconds before
		 * the same port can be used again in the
		 * same process, so a short Sleep may be
		 * required between mg_stop and mg_start.
		 */
		if (setsockopt(so.sock,
		               SOL_SOCKET,
		               SO_EXCLUSIVEADDRUSE,
		               (SOCK_OPT_TYPE)&on,
		               sizeof(on)) != 0) {

			mg_cry(fc(ctx),
			       "cannot set socket option SO_EXCLUSIVEADDRUSE (entry %i)",
			       portsTotal);
		}
#else
		if (setsockopt(so.sock,
		               SOL_SOCKET,
		               SO_REUSEADDR,
		               (SOCK_OPT_TYPE)&on,
		               sizeof(on)) != 0) {

			mg_cry(fc(ctx),
			       "cannot set socket option SO_REUSEADDR (entry %i)",
			       portsTotal);
		}
#endif


#if defined(USE_IPV6)
		if (so.lsa.sa.sa_family == AF_INET6 &&
		    setsockopt(so.sock,
		               IPPROTO_IPV6,
		               IPV6_V6ONLY,
		               (void *)&off,
		               sizeof(off)) != 0) {

			mg_cry(fc(ctx),
			       "cannot set socket option IPV6_V6ONLY (entry %i)",
			       portsTotal);
		}
#endif

		if (so.lsa.sa.sa_family == AF_INET) {

			len = sizeof(so.lsa.sin);
			if (bind(so.sock, &so.lsa.sa, len) != 0) {
				mg_cry(fc(ctx),
				       "cannot bind to %.*s: %d (%s)",
				       (int)vec.len,
				       vec.ptr,
				       (int)ERRNO,
				       strerror(errno));
				closesocket(so.sock);
				so.sock = INVALID_SOCKET;
				continue;
			}
		}
#if defined(USE_IPV6)
		else if (so.lsa.sa.sa_family == AF_INET6) {

			len = sizeof(so.lsa.sin6);
			if (bind(so.sock, &so.lsa.sa, len) != 0) {
				mg_cry(fc(ctx),
				       "cannot bind to IPv6 %.*s: %d (%s)",
				       (int)vec.len,
				       vec.ptr,
				       (int)ERRNO,
				       strerror(errno));
				closesocket(so.sock);
				so.sock = INVALID_SOCKET;
				continue;
			}
		}
#endif
		else {
			mg_cry(fc(ctx),
			       "cannot bind: address family not supported (entry %i)",
			       portsTotal);
			continue;
		}

		if (listen(so.sock, SOMAXCONN) != 0) {

			mg_cry(fc(ctx),
			       "cannot listen to %.*s: %d (%s)",
			       (int)vec.len,
			       vec.ptr,
			       (int)ERRNO,
			       strerror(errno));
			closesocket(so.sock);
			so.sock = INVALID_SOCKET;
			continue;
		}


		if (getsockname(so.sock, &(usa.sa), &len) != 0) {

			int err = (int)ERRNO;
			mg_cry(fc(ctx),
			       "call to getsockname failed %.*s: %d (%s)",
			       (int)vec.len,
			       vec.ptr,
			       err,
			       strerror(errno));
			closesocket(so.sock);
			so.sock = INVALID_SOCKET;
			continue;
		}

		if ((ptr = (struct socket *)mg_realloc(
		         ctx->listening_sockets,
		         (ctx->num_listening_sockets + 1) *
		             sizeof(ctx->listening_sockets[0]))) == NULL) {

			mg_cry(fc(ctx), "%s", "Out of memory");
			closesocket(so.sock);
			so.sock = INVALID_SOCKET;
			continue;
		}

		if ((portPtr = (in_port_t *)mg_realloc(
		         ctx->listening_ports,
		         (ctx->num_listening_sockets + 1) *
		             sizeof(ctx->listening_ports[0]))) == NULL) {

			mg_cry(fc(ctx), "%s", "Out of memory");
			closesocket(so.sock);
			so.sock = INVALID_SOCKET;
			mg_free(ptr);
			continue;
		}

		set_close_on_exec(so.sock, fc(ctx));
		ctx->listening_sockets = ptr;
		ctx->listening_sockets[ctx->num_listening_sockets] = so;
		ctx->listening_ports = portPtr;
		ctx->listening_ports[ctx->num_listening_sockets] =
		    ntohs(usa.sin.sin_port);
		ctx->num_listening_sockets++;
		portsOk++;
	}

	if (portsOk != portsTotal) {
		close_all_listening_sockets(ctx);
		portsOk = 0;
	}

	return portsOk;
}

static const char *header_val(const struct mg_connection *conn,
                              const char *header)
{
	const char *header_value;

	if ((header_value = mg_get_header(conn, header)) == NULL) {
		return "-";
	} else {
		return header_value;
	}
}

static void log_access(const struct mg_connection *conn)
{
	const struct mg_request_info *ri;
	FILE *fp;
	char date[64], src_addr[IP_ADDR_STR_LEN];
	struct tm *tm;

	const char *referer;
	const char *user_agent;

	char buf[4096];

	if (!conn || !conn->ctx) {
		return;
	}

	fp = conn->ctx->config[ACCESS_LOG_FILE] == NULL
	         ? NULL
	         : fopen(conn->ctx->config[ACCESS_LOG_FILE], "a+");

	if (fp == NULL && conn->ctx->callbacks.log_message == NULL) {
		return;
	}

	tm = localtime(&conn->conn_birth_time);
	if (tm != NULL) {
		strftime(date, sizeof(date), "%d/%b/%Y:%H:%M:%S %z", tm);
	} else {
		mg_strlcpy(date, "01/Jan/1970:00:00:00 +0000", sizeof(date));
		date[sizeof(date) - 1] = '\0';
	}

	ri = &conn->request_info;

	sockaddr_to_string(src_addr, sizeof(src_addr), &conn->client.rsa);
	referer = header_val(conn, "Referer");
	user_agent = header_val(conn, "User-Agent");

	snprintf(buf,
	         sizeof(buf),
	         "%s - %s [%s] \"%s %s HTTP/%s\" %d %" INT64_FMT " %s %s",
	         src_addr,
	         ri->remote_user == NULL ? "-" : ri->remote_user,
	         date,
	         ri->request_method ? ri->request_method : "-",
	         ri->uri ? ri->uri : "-",
	         ri->http_version,
	         conn->status_code,
	         conn->num_bytes_sent,
	         referer,
	         user_agent);

	if (conn->ctx->callbacks.log_access) {
		conn->ctx->callbacks.log_access(conn, buf);
	}

	if (fp) {
		flockfile(fp);
		fprintf(fp, "%s", buf);
		fputc('\n', fp);
		fflush(fp);
		funlockfile(fp);
		fclose(fp);
	}
}

/* Verify given socket address against the ACL.
 * Return -1 if ACL is malformed, 0 if address is disallowed, 1 if allowed. */
static int check_acl(struct mg_context *ctx, uint32_t remote_ip)
{
	int allowed, flag;
	uint32_t net, mask;
	struct vec vec;

	if (ctx) {
		const char *list = ctx->config[ACCESS_CONTROL_LIST];

		/* If any ACL is set, deny by default */
		allowed = list == NULL ? '+' : '-';

		while ((list = next_option(list, &vec, NULL)) != NULL) {
			flag = vec.ptr[0];
			if ((flag != '+' && flag != '-') ||
			    parse_net(&vec.ptr[1], &net, &mask) == 0) {
				mg_cry(
				    fc(ctx), "%s: subnet must be [+|-]x.x.x.x[/x]", __func__);
				return -1;
			}

			if (net == (remote_ip & mask)) {
				allowed = flag;
			}
		}

		return allowed == '+';
	}
	return -1;
}

#if !defined(_WIN32)
static int set_uid_option(struct mg_context *ctx)
{
	struct passwd *pw;
	if (ctx) {
		const char *uid = ctx->config[RUN_AS_USER];
		int success = 0;

		if (uid == NULL) {
			success = 1;
		} else {
			if ((pw = getpwnam(uid)) == NULL) {
				mg_cry(fc(ctx), "%s: unknown user [%s]", __func__, uid);
			} else if (setgid(pw->pw_gid) == -1) {
				mg_cry(fc(ctx),
				       "%s: setgid(%s): %s",
				       __func__,
				       uid,
				       strerror(errno));
			} else if (setgroups(0, NULL)) {
				mg_cry(
				    fc(ctx), "%s: setgroups(): %s", __func__, strerror(errno));
			} else if (setuid(pw->pw_uid) == -1) {
				mg_cry(fc(ctx),
				       "%s: setuid(%s): %s",
				       __func__,
				       uid,
				       strerror(errno));
			} else {
				success = 1;
			}
		}

		return success;
	}
	return 0;
}
#endif /* !_WIN32 */

#if !defined(NO_SSL)
static pthread_mutex_t *ssl_mutexes;

static int sslize(struct mg_connection *conn, SSL_CTX *s, int (*func)(SSL *))
{
	if (!conn) {
		return 0;
	}

	return (conn->ssl = SSL_new(s)) != NULL &&
	       SSL_set_fd(conn->ssl, conn->client.sock) == 1 &&
	       func(conn->ssl) == 1;
}

/* Return OpenSSL error message (from CRYPTO lib) */
static const char *ssl_error(void)
{
	unsigned long err;
	err = ERR_get_error();
	return err == 0 ? "" : ERR_error_string(err, NULL);
}

static void
ssl_locking_callback(int mode, int mutex_num, const char *file, int line)
{
	(void)line;
	(void)file;

	if (mode & 1) {
		/* 1 is CRYPTO_LOCK */
		(void)pthread_mutex_lock(&ssl_mutexes[mutex_num]);
	} else {
		(void)pthread_mutex_unlock(&ssl_mutexes[mutex_num]);
	}
}

static unsigned long ssl_id_callback(void)
{
	return (unsigned long)pthread_self();
}

#if !defined(NO_SSL_DL)
static void *
load_dll(struct mg_context *ctx, const char *dll_name, struct ssl_func *sw)
{
	union {
		void *p;
		void (*fp)(void);
	} u;
	void *dll_handle;
	struct ssl_func *fp;

	if ((dll_handle = dlopen(dll_name, RTLD_LAZY)) == NULL) {
		mg_cry(fc(ctx), "%s: cannot load %s", __func__, dll_name);
		return NULL;
	}

	for (fp = sw; fp->name != NULL; fp++) {
#ifdef _WIN32
		/* GetProcAddress() returns pointer to function */
		u.fp = (void (*)(void))dlsym(dll_handle, fp->name);
#else
		/* dlsym() on UNIX returns void *. ISO C forbids casts of data
		 * pointers to function pointers. We need to use a union to make a
		 * cast. */
		u.p = dlsym(dll_handle, fp->name);
#endif /* _WIN32 */
		if (u.fp == NULL) {
			mg_cry(fc(ctx),
			       "%s: %s: cannot find %s",
			       __func__,
			       dll_name,
			       fp->name);
			dlclose(dll_handle);
			return NULL;
		} else {
			fp->ptr = u.fp;
		}
	}

	return dll_handle;
}

static void *ssllib_dll_handle;    /* Store the ssl library handle. */
static void *cryptolib_dll_handle; /* Store the crypto library handle. */

#endif /* NO_SSL_DL */

#if defined(SSL_ALREADY_INITIALIZED)
static int cryptolib_users = 1; /* Reference counter for crypto library. */
#else
static int cryptolib_users = 0; /* Reference counter for crypto library. */
#endif

static int initialize_ssl(struct mg_context *ctx)
{
	int i;
	size_t size;

#if !defined(NO_SSL_DL)
	if (!cryptolib_dll_handle) {
		cryptolib_dll_handle = load_dll(ctx, CRYPTO_LIB, crypto_sw);
		if (!cryptolib_dll_handle) {
			return 0;
		}
	}
#endif /* NO_SSL_DL */

	if (mg_atomic_inc(&cryptolib_users) > 1) {
		return 1;
	}

	/* Initialize locking callbacks, needed for thread safety.
	 * http://www.openssl.org/support/faq.html#PROG1
	 */
	i = CRYPTO_num_locks();
	if (i < 0) {
		i = 0;
	}
	size = sizeof(pthread_mutex_t) * ((size_t)(i));
	if ((ssl_mutexes = (pthread_mutex_t *)mg_malloc(size)) == NULL) {
		mg_cry(
		    fc(ctx), "%s: cannot allocate mutexes: %s", __func__, ssl_error());
		return 0;
	}

	for (i = 0; i < CRYPTO_num_locks(); i++) {
		pthread_mutex_init(&ssl_mutexes[i], NULL);
	}

	CRYPTO_set_locking_callback(&ssl_locking_callback);
	CRYPTO_set_id_callback(&ssl_id_callback);

	return 1;
}

/* Dynamically load SSL library. Set up ctx->ssl_ctx pointer. */
static int set_ssl_option(struct mg_context *ctx)
{
	const char *pem;
	int callback_ret;

	/* If PEM file is not specified and the init_ssl callback
	 * is not specified, skip SSL initialization. */
	if (!ctx) {
		return 0;
	}
	if ((pem = ctx->config[SSL_CERTIFICATE]) == NULL &&
	    ctx->callbacks.init_ssl == NULL) {
		return 1;
	}

	if (!initialize_ssl(ctx)) {
		return 0;
	}

#if !defined(NO_SSL_DL)
	if (!ssllib_dll_handle) {
		ssllib_dll_handle = load_dll(ctx, SSL_LIB, ssl_sw);
		if (!ssllib_dll_handle) {
			return 0;
		}
	}
#endif /* NO_SSL_DL */

	/* Initialize SSL library */
	SSL_library_init();
	SSL_load_error_strings();

	if ((ctx->ssl_ctx = SSL_CTX_new(SSLv23_server_method())) == NULL) {
		mg_cry(fc(ctx), "SSL_CTX_new (server) error: %s", ssl_error());
		return 0;
	}

	/* If a callback has been specified, call it. */
	callback_ret =
	    (ctx->callbacks.init_ssl == NULL)
	        ? 0
	        : (ctx->callbacks.init_ssl(ctx->ssl_ctx, ctx->user_data));

	/* If callback returns 0, civetweb sets up the SSL certificate.
	 * If it returns 1, civetweb assumes the calback already did this.
	 * If it returns -1, initializing ssl fails. */
	if (callback_ret < 0) {
		mg_cry(fc(ctx), "SSL callback returned error: %i", callback_ret);
		return 0;
	}
	if (callback_ret == 0) {
		if (pem != NULL) {
			if ((SSL_CTX_use_certificate_file(ctx->ssl_ctx, pem, 1) == 0) ||
			    (SSL_CTX_use_PrivateKey_file(ctx->ssl_ctx, pem, 1) == 0)) {
				mg_cry(fc(ctx),
				       "%s: cannot open %s: %s",
				       __func__,
				       pem,
				       ssl_error());
				return 0;
			}
		}
	}

	if (pem != NULL) {
		(void)SSL_CTX_use_certificate_chain_file(ctx->ssl_ctx, pem);
	}

	return 1;
}

static void uninitialize_ssl(struct mg_context *ctx)
{
	int i;
	(void)ctx;

	if (mg_atomic_dec(&cryptolib_users) == 0) {
		CRYPTO_set_locking_callback(NULL);
		for (i = 0; i < CRYPTO_num_locks(); i++) {
			pthread_mutex_destroy(&ssl_mutexes[i]);
		}
		CRYPTO_set_locking_callback(NULL);
		CRYPTO_set_id_callback(NULL);
	}
}
#endif /* !NO_SSL */

static int set_gpass_option(struct mg_context *ctx)
{
	if (ctx) {
		struct file file = STRUCT_FILE_INITIALIZER;
		const char *path = ctx->config[GLOBAL_PASSWORDS_FILE];
		if (path != NULL && !mg_stat(fc(ctx), path, &file)) {
			mg_cry(fc(ctx), "Cannot open %s: %s", path, strerror(ERRNO));
			return 0;
		}
		return 1;
	}
	return 0;
}

static int set_acl_option(struct mg_context *ctx)
{
	return check_acl(ctx, (uint32_t)0x7f000001UL) != -1;
}

static void reset_per_request_attributes(struct mg_connection *conn)
{
	if (!conn) {
		return;
	}
	conn->path_info = NULL;
	conn->num_bytes_sent = conn->consumed_content = 0;
	conn->status_code = -1;
	conn->is_chunked = 0;
	conn->must_close = conn->request_len = conn->throttle = 0;
	conn->request_info.content_length = -1;
	conn->request_info.remote_user = NULL;
	conn->request_info.request_method = NULL;
	conn->request_info.uri = NULL;
	conn->request_info.http_version = NULL;
	conn->request_info.num_headers = 0;
	conn->data_len = 0;
	conn->chunk_remainder = 0;
}

static int set_sock_timeout(SOCKET sock, int milliseconds)
{
	int r1, r2;
#ifdef _WIN32
	DWORD t = (DWORD)milliseconds;
#else
#if defined(TCP_USER_TIMEOUT)
	unsigned int uto = (unsigned int)milliseconds;
#endif
	struct timeval t;
	t.tv_sec = milliseconds / 1000;
	t.tv_usec = (milliseconds * 1000) % 1000000;

/* TCP_USER_TIMEOUT/RFC5482 (http://tools.ietf.org/html/rfc5482):
 * max. time waiting for the acknowledged of TCP data before the connection
 * will be forcefully closed and ETIMEDOUT is returned to the application.
 * If this option is not set, the default timeout of 20-30 minutes is used.
*/
/* #define TCP_USER_TIMEOUT (18) */

#if defined(TCP_USER_TIMEOUT)
	setsockopt(sock, 6, TCP_USER_TIMEOUT, (const void *)&uto, sizeof(uto));
#endif

#endif

	r1 =
	    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (SOCK_OPT_TYPE)&t, sizeof(t));
	r2 =
	    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (SOCK_OPT_TYPE)&t, sizeof(t));

	return r1 || r2;
}

static void close_socket_gracefully(struct mg_connection *conn)
{
#if defined(_WIN32)
	char buf[MG_BUF_LEN];
	int n;
#endif
	struct linger linger;

	if (!conn) {
		return;
	}

	/* Set linger option to avoid socket hanging out after close. This prevent
	 * ephemeral port exhaust problem under high QPS. */
	linger.l_onoff = 1;
	linger.l_linger = 1;

	if (setsockopt(conn->client.sock,
	               SOL_SOCKET,
	               SO_LINGER,
	               (char *)&linger,
	               sizeof(linger)) != 0) {
		mg_cry(conn,
		       "%s: setsockopt(SOL_SOCKET SO_LINGER) failed: %s",
		       __func__,
		       strerror(ERRNO));
	}

	/* Send FIN to the client */
	shutdown(conn->client.sock, SHUT_WR);
	set_non_blocking_mode(conn->client.sock);

#if defined(_WIN32)
	/* Read and discard pending incoming data. If we do not do that and close
	 * the socket, the data in the send buffer may be discarded. This
	 * behaviour is seen on Windows, when client keeps sending data
	 * when server decides to close the connection; then when client
	 * does recv() it gets no data back. */
	do {
		n = pull(
		    NULL, conn, buf, sizeof(buf), 1E-10 /* TODO: allow 0 as timeout */);
	} while (n > 0);
#endif

	/* Now we know that our FIN is ACK-ed, safe to close */
	closesocket(conn->client.sock);
	conn->client.sock = INVALID_SOCKET;
}

static void close_connection(struct mg_connection *conn)
{
	if (!conn || !conn->ctx) {
		return;
	}

#if defined(USE_LUA) && defined(USE_WEBSOCKET)
	if (conn->lua_websocket_state) {
		lua_websocket_close(conn, conn->lua_websocket_state);
		conn->lua_websocket_state = NULL;
	}
#endif

	/* call the connection_close callback if assigned */
	if ((conn->ctx->callbacks.connection_close != NULL) &&
	    (conn->ctx->context_type == 1)) {
		conn->ctx->callbacks.connection_close(conn);
	}

	mg_lock_connection(conn);

	conn->must_close = 1;

#ifndef NO_SSL
	if (conn->ssl != NULL) {
		/* Run SSL_shutdown twice to ensure completly close SSL connection */
		SSL_shutdown(conn->ssl);
		SSL_free(conn->ssl);
		conn->ssl = NULL;
	}
#endif
	if (conn->client.sock != INVALID_SOCKET) {
		close_socket_gracefully(conn);
		conn->client.sock = INVALID_SOCKET;
	}

	mg_unlock_connection(conn);
}

void mg_close_connection(struct mg_connection *conn)
{
	struct mg_context *client_ctx = NULL;
	unsigned int i;

	if (conn == NULL) {
		return;
	}

	if (conn->ctx->context_type == 2) {
		client_ctx = conn->ctx;
		/* client context: loops must end */
		conn->ctx->stop_flag = 1;
	}

#ifndef NO_SSL
	if (conn->client_ssl_ctx != NULL) {
		SSL_CTX_free((SSL_CTX *)conn->client_ssl_ctx);
	}
#endif
	close_connection(conn);
	if (client_ctx != NULL) {
		/* join worker thread and free context */
		for (i = 0; i < client_ctx->workerthreadcount; i++) {
			mg_join_thread(client_ctx->workerthreadids[i]);
		}
		mg_free(client_ctx->workerthreadids);
		mg_free(client_ctx);
	}
	(void)pthread_mutex_destroy(&conn->mutex);
	mg_free(conn);
}

struct mg_connection *mg_connect_client(
    const char *host, int port, int use_ssl, char *ebuf, size_t ebuf_len)
{
	static struct mg_context fake_ctx;
	struct mg_connection *conn = NULL;
	SOCKET sock;

	if ((sock = conn2(&fake_ctx, host, port, use_ssl, ebuf, ebuf_len)) ==
	    INVALID_SOCKET) {
	} else if ((conn = (struct mg_connection *)mg_calloc(
	                1, sizeof(*conn) + MAX_REQUEST_SIZE)) == NULL) {
		snprintf(ebuf, ebuf_len, "calloc(): %s", strerror(ERRNO));
		closesocket(sock);
#ifndef NO_SSL
	} else if (use_ssl &&
	           (conn->client_ssl_ctx = SSL_CTX_new(SSLv23_client_method())) ==
	               NULL) {
		snprintf(ebuf, ebuf_len, "SSL_CTX_new error");
		closesocket(sock);
		mg_free(conn);
		conn = NULL;
#endif /* NO_SSL */
	} else {
		socklen_t len = sizeof(struct sockaddr);
		conn->buf_size = MAX_REQUEST_SIZE;
		conn->buf = (char *)(conn + 1);
		conn->ctx = &fake_ctx;
		conn->client.sock = sock;
		if (getsockname(sock, &conn->client.rsa.sa, &len) != 0) {
			mg_cry(conn,
			       "%s: getsockname() failed: %s",
			       __func__,
			       strerror(ERRNO));
		}
		conn->client.is_ssl = use_ssl ? 1 : 0;
		(void)pthread_mutex_init(&conn->mutex, NULL);
#ifndef NO_SSL
		if (use_ssl) {
			/* SSL_CTX_set_verify call is needed to switch off server
			 * certificate checking, which is off by default in OpenSSL and on
			 * in yaSSL. */
			SSL_CTX_set_verify(conn->client_ssl_ctx, 0, 0);
			sslize(conn, conn->client_ssl_ctx, SSL_connect);
		}
#endif
	}

	return conn;
}

static int is_valid_uri(const char *uri)
{
	/* Conform to
	 * http://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html#sec5.1.2
	 * URI can be an asterisk (*) or should start with slash. */
	return uri[0] == '/' || (uri[0] == '*' && uri[1] == '\0');
}

static int
getreq(struct mg_connection *conn, char *ebuf, size_t ebuf_len, int *err)
{
	const char *cl;

	if (ebuf_len > 0) {
		ebuf[0] = '\0';
	}
	*err = 0;

	reset_per_request_attributes(conn);

	if (!conn) {
		snprintf(ebuf, ebuf_len, "%s", "Internal error");
		*err = 500;
		return 0;
	}
	/* Set the time the request was received. This value should be used for
	 * timeouts. */
	clock_gettime(CLOCK_MONOTONIC, &(conn->req_time));

	conn->request_len =
	    read_request(NULL, conn, conn->buf, conn->buf_size, &conn->data_len);
	/* assert(conn->request_len < 0 || conn->data_len >= conn->request_len); */
	if (conn->request_len >= 0 && conn->data_len < conn->request_len) {
		snprintf(ebuf, ebuf_len, "%s", "Invalid request size");
		*err = 500;
		return 0;
	}

	if (conn->request_len == 0 && conn->data_len == conn->buf_size) {
		snprintf(ebuf, ebuf_len, "%s", "Request Too Large");
		*err = 413;
		return 0;
	} else if (conn->request_len <= 0) {
		if (conn->data_len > 0) {
			snprintf(ebuf, ebuf_len, "%s", "Client sent malformed request");
			*err = 400;
		} else {
			/* Server did not send anything -> just close the connection */
			conn->must_close = 1;
			snprintf(ebuf, ebuf_len, "%s", "Client did not send a request");
			*err = 0;
		}
		return 0;
	} else if (parse_http_message(
	               conn->buf, conn->buf_size, &conn->request_info) <= 0) {
		snprintf(ebuf, ebuf_len, "%s", "Bad Request");
		*err = 400;
		return 0;
	} else {
		/* Message is a valid request or response */
		if ((cl = get_header(&conn->request_info, "Content-Length")) != NULL) {
			/* Request/response has content length set */
			char *endptr = NULL;
			conn->content_len = strtoll(cl, &endptr, 10);
			if (endptr == cl) {
				snprintf(ebuf, ebuf_len, "%s", "Bad Request");
				*err = 411;
				return 0;
			}
			/* Publish the content length back to the request info. */
			conn->request_info.content_length = conn->content_len;
		} else if ((cl = get_header(&conn->request_info,
		                            "Transfer-encoding")) != NULL &&
		           strcmp(cl, "chunked") == 0) {
			conn->is_chunked = 1;
		} else if (!mg_strcasecmp(conn->request_info.request_method, "POST") ||
		           !mg_strcasecmp(conn->request_info.request_method, "PUT")) {
			/* POST or PUT request without content length set */
			conn->content_len = -1;
		} else if (!mg_strncasecmp(
		               conn->request_info.request_method, "HTTP/", 5)) {
			/* Response without content length set */
			conn->content_len = -1;
		} else {
			/* Other request */
			conn->content_len = 0;
		}
	}
	return 1;
}

int mg_get_response(struct mg_connection *conn,
                    char *ebuf,
                    size_t ebuf_len,
                    int timeout)
{
	if (conn) {
		/* Implementation of API function for HTTP clients */
		int err, ret;
		struct mg_context *octx = conn->ctx;
		struct mg_context rctx = *(conn->ctx);
		char txt[32];

		if (timeout >= 0) {
			snprintf(txt, sizeof(txt), "%i", timeout);
			rctx.config[REQUEST_TIMEOUT] = txt;
			set_sock_timeout(conn->client.sock, timeout);
		} else {
			rctx.config[REQUEST_TIMEOUT] = NULL;
		}

		conn->ctx = &rctx;
		ret = getreq(conn, ebuf, ebuf_len, &err);
		conn->ctx = octx;

		/* TODO (mid): Define proper return values - maybe return length?
		 * For the first test use <0 for error and >0 for OK */
		return (ret == 0) ? -1 : +1;
	}
	return -1;
}

struct mg_connection *mg_download(const char *host,
                                  int port,
                                  int use_ssl,
                                  char *ebuf,
                                  size_t ebuf_len,
                                  const char *fmt,
                                  ...)
{
	struct mg_connection *conn;
	va_list ap;
	int i;
	int reqerr;

	va_start(ap, fmt);
	ebuf[0] = '\0';

	/* open a connection */
	conn = mg_connect_client(host, port, use_ssl, ebuf, ebuf_len);

	if (conn != NULL) {
		i = mg_vprintf(conn, fmt, ap);
		if (i <= 0) {
			snprintf(ebuf, ebuf_len, "%s", "Error sending request");
		} else {
			getreq(conn, ebuf, ebuf_len, &reqerr);
		}
	}

	/* if an error occured, close the connection */
	if (ebuf[0] != '\0' && conn != NULL) {
		mg_close_connection(conn);
		conn = NULL;
	}

	va_end(ap);
	return conn;
}

struct websocket_client_thread_data {
	struct mg_connection *conn;
	mg_websocket_data_handler data_handler;
	mg_websocket_close_handler close_handler;
	void *callback_data;
};

#if defined(USE_WEBSOCKET)
#ifdef _WIN32
static unsigned __stdcall websocket_client_thread(void *data)
#else
static void *websocket_client_thread(void *data)
#endif
{
	struct websocket_client_thread_data *cdata =
	    (struct websocket_client_thread_data *)data;
	read_websocket(cdata->conn, cdata->data_handler, cdata->callback_data);

	DEBUG_TRACE("%s", "Websocket client thread exited\n");

	if (cdata->close_handler != NULL) {
		cdata->close_handler(cdata->conn, cdata->callback_data);
	}

	mg_free((void *)cdata);

#ifdef _WIN32
	return 0;
#else
	return NULL;
#endif
}
#endif

struct mg_connection *
mg_connect_websocket_client(const char *host,
                            int port,
                            int use_ssl,
                            char *error_buffer,
                            size_t error_buffer_size,
                            const char *path,
                            const char *origin,
                            mg_websocket_data_handler data_func,
                            mg_websocket_close_handler close_func,
                            void *user_data)
{
	struct mg_connection *conn = NULL;

#if defined(USE_WEBSOCKET)
	struct mg_context *newctx = NULL;
	struct websocket_client_thread_data *thread_data;
	static const char *magic = "x3JJHMbDL1EzLkh9GBhXDw==";
	static const char *handshake_req;

	if (origin != NULL) {
		handshake_req = "GET %s HTTP/1.1\r\n"
		                "Host: %s\r\n"
		                "Upgrade: websocket\r\n"
		                "Connection: Upgrade\r\n"
		                "Sec-WebSocket-Key: %s\r\n"
		                "Sec-WebSocket-Version: 13\r\n"
		                "Origin: %s\r\n"
		                "\r\n";
	} else {
		handshake_req = "GET %s HTTP/1.1\r\n"
		                "Host: %s\r\n"
		                "Upgrade: websocket\r\n"
		                "Connection: Upgrade\r\n"
		                "Sec-WebSocket-Key: %s\r\n"
		                "Sec-WebSocket-Version: 13\r\n"
		                "\r\n";
	}

	/* Establish the client connection and request upgrade */
	conn = mg_download(host,
	                   port,
	                   use_ssl,
	                   error_buffer,
	                   error_buffer_size,
	                   handshake_req,
	                   path,
	                   host,
	                   magic,
	                   origin);

	/* Connection object will be null if something goes wrong */
	if (conn == NULL || (strcmp(conn->request_info.uri, "101") != 0)) {
		if (!*error_buffer) {
			/* if there is a connection, but it did not return 101,
			 * error_buffer is not yet set */
			mg_snprintf(conn,
			            error_buffer,
			            error_buffer_size,
			            "Unexpected server reply");
		}
		DEBUG_TRACE("Websocket client connect error: %s\r\n", error_buffer);
		if (conn != NULL) {
			mg_free(conn);
			conn = NULL;
		}
		return conn;
	}

	/* For client connections, mg_context is fake. Since we need to set a
	 * callback function, we need to create a copy and modify it. */
	newctx = (struct mg_context *)mg_malloc(sizeof(struct mg_context));
	memcpy(newctx, conn->ctx, sizeof(struct mg_context));
	newctx->user_data = user_data;
	newctx->context_type = 2;      /* client context type */
	newctx->workerthreadcount = 1; /* one worker thread will be created */
	newctx->workerthreadids =
	    (pthread_t *)mg_calloc(newctx->workerthreadcount, sizeof(pthread_t));
	conn->ctx = newctx;
	thread_data = (struct websocket_client_thread_data *)mg_calloc(
	    sizeof(struct websocket_client_thread_data), 1);
	thread_data->conn = conn;
	thread_data->data_handler = data_func;
	thread_data->close_handler = close_func;
	thread_data->callback_data = NULL;

	/* Start a thread to read the websocket client connection
	 * This thread will automatically stop when mg_disconnect is
	 * called on the client connection */
	if (mg_start_thread_with_id(websocket_client_thread,
	                            (void *)thread_data,
	                            newctx->workerthreadids) != 0) {
		mg_free((void *)thread_data);
		mg_free((void *)newctx->workerthreadids);
		mg_free((void *)newctx);
		mg_free((void *)conn);
		conn = NULL;
		DEBUG_TRACE("%s",
		            "Websocket client connect thread could not be started\r\n");
	}
#else
	/* Appease "unused parameter" warnings */
	(void)host;
	(void)port;
	(void)use_ssl;
	(void)error_buffer;
	(void)error_buffer_size;
	(void)path;
	(void)origin;
	(void)user_data;
	(void)data_func;
	(void)close_func;
#endif

	return conn;
}

static void process_new_connection(struct mg_connection *conn)
{
	if (conn && conn->ctx) {
		struct mg_request_info *ri = &conn->request_info;
		int keep_alive_enabled, keep_alive, discard_len;
		char ebuf[100];
		int reqerr;

		keep_alive_enabled =
		    !strcmp(conn->ctx->config[ENABLE_KEEP_ALIVE], "yes");

		/* Important: on new connection, reset the receiving buffer. Credit
		 * goes to crule42. */
		conn->data_len = 0;
		do {
			if (!getreq(conn, ebuf, sizeof(ebuf), &reqerr)) {
				/* The request sent by the client could not be understood by
				 * the server, or it was incomplete or a timeout. Send an
				 * error message and close the connection. */
				if (reqerr > 0) {
					/*assert(ebuf[0] != '\0');*/
					send_http_error(conn, reqerr, "%s", ebuf);
				}
			} else if (!is_valid_uri(conn->request_info.uri)) {
				snprintf(ebuf, sizeof(ebuf), "Invalid URI: [%s]", ri->uri);
				send_http_error(conn, 400, "%s", ebuf);
			} else if (strcmp(ri->http_version, "1.0") &&
			           strcmp(ri->http_version, "1.1")) {
				snprintf(ebuf,
				         sizeof(ebuf),
				         "Bad HTTP version: [%s]",
				         ri->http_version);
				send_http_error(conn, 505, "%s", ebuf);
			}

			if (ebuf[0] == '\0') {
				handle_request(conn);
				if (conn->ctx->callbacks.end_request != NULL) {
					conn->ctx->callbacks.end_request(conn, conn->status_code);
				}
				log_access(conn);
			} else {
				conn->must_close = 1;
			}

			if (ri->remote_user != NULL) {
				mg_free((void *)ri->remote_user);
				/* Important! When having connections with and without auth
				 * would cause double free and then crash */
				ri->remote_user = NULL;
			}

			/* NOTE(lsm): order is important here. should_keep_alive() call is
			 * using parsed request, which will be invalid after memmove's
			 * below.
			 * Therefore, memorize should_keep_alive() result now for later use
			 * in loop exit condition. */
			keep_alive = conn->ctx->stop_flag == 0 && keep_alive_enabled &&
			             conn->content_len >= 0 && should_keep_alive(conn);

			/* Discard all buffered data for this request */
			discard_len = conn->content_len >= 0 && conn->request_len > 0 &&
			                      conn->request_len + conn->content_len <
			                          (int64_t)conn->data_len
			                  ? (int)(conn->request_len + conn->content_len)
			                  : conn->data_len;
			/*assert(discard_len >= 0);*/
			if (discard_len < 0)
				break;
			conn->data_len -= discard_len;
			if (conn->data_len > 0) {
				memmove(
				    conn->buf, conn->buf + discard_len, (size_t)conn->data_len);
			}

			/* assert(conn->data_len >= 0); */
			/* assert(conn->data_len <= conn->buf_size); */

			if ((conn->data_len < 0) || (conn->data_len > conn->buf_size)) {
				break;
			}

		} while (keep_alive);
	}
}

/* Worker threads take accepted socket from the queue */
static int consume_socket(struct mg_context *ctx, struct socket *sp)
{
#define QUEUE_SIZE(ctx) ((int)(ARRAY_SIZE(ctx->queue)))
	if (!ctx) {
		return 0;
	}

	(void)pthread_mutex_lock(&ctx->thread_mutex);
	DEBUG_TRACE("%s", "going idle");

	/* If the queue is empty, wait. We're idle at this point. */
	while (ctx->sq_head == ctx->sq_tail && ctx->stop_flag == 0) {
		pthread_cond_wait(&ctx->sq_full, &ctx->thread_mutex);
	}

	/* If we're stopping, sq_head may be equal to sq_tail. */
	if (ctx->sq_head > ctx->sq_tail) {
		/* Copy socket from the queue and increment tail */
		*sp = ctx->queue[ctx->sq_tail % QUEUE_SIZE(ctx)];
		ctx->sq_tail++;

		DEBUG_TRACE("grabbed socket %d, going busy", sp ? sp->sock : -1);


		/* Wrap pointers if needed */
		while (ctx->sq_tail > QUEUE_SIZE(ctx)) {
			ctx->sq_tail -= QUEUE_SIZE(ctx);
			ctx->sq_head -= QUEUE_SIZE(ctx);
		}
	}

	(void)pthread_cond_signal(&ctx->sq_empty);
	(void)pthread_mutex_unlock(&ctx->thread_mutex);

	return !ctx->stop_flag;
#undef QUEUE_SIZE
}

static void *worker_thread_run(void *thread_func_param)
{
	struct mg_context *ctx = (struct mg_context *)thread_func_param;
	struct mg_connection *conn;
	struct mg_workerTLS tls;
	uint32_t addr;

	mg_set_thread_name("worker");

	tls.is_master = 0;
#if defined(_WIN32) && !defined(__SYMBIAN32__)
	tls.pthread_cond_helper_mutex = CreateEvent(NULL, FALSE, FALSE, NULL);
#endif

	conn =
	    (struct mg_connection *)mg_calloc(1, sizeof(*conn) + MAX_REQUEST_SIZE);
	if (conn == NULL) {
		mg_cry(fc(ctx), "%s", "Cannot create new connection struct, OOM");
	} else {
		pthread_setspecific(sTlsKey, &tls);
		conn->buf_size = MAX_REQUEST_SIZE;
		conn->buf = (char *)(conn + 1);
		conn->ctx = ctx;
		conn->request_info.user_data = ctx->user_data;
		/* Allocate a mutex for this connection to allow communication both
		 * within the request handler and from elsewhere in the application */
		(void)pthread_mutex_init(&conn->mutex, NULL);

		/* Call consume_socket() even when ctx->stop_flag > 0, to let it
		 * signal sq_empty condvar to wake up the master waiting in
		 * produce_socket() */
		while (consume_socket(ctx, &conn->client)) {
			conn->conn_birth_time = time(NULL);

			/* Fill in IP, port info early so even if SSL setup below fails,
			 * error handler would have the corresponding info.
			 * Thanks to Johannes Winkelmann for the patch.
			 * TODO(lsm, high): Fix IPv6 case */
			conn->request_info.remote_port =
			    ntohs(conn->client.rsa.sin.sin_port);
			sockaddr_to_string(conn->request_info.remote_addr,
			                   sizeof(conn->request_info.remote_addr),
			                   &conn->client.rsa);
			/* TODO: #if defined(MG_LEGACY_INTERFACE) */
			addr = ntohl(conn->client.rsa.sin.sin_addr.s_addr);
			memcpy(&conn->request_info.remote_ip, &addr, 4);
			/* #endif */
			conn->request_info.is_ssl = conn->client.is_ssl;

			if (!conn->client.is_ssl
#ifndef NO_SSL
			    ||
			    sslize(conn, conn->ctx->ssl_ctx, SSL_accept)
#endif
			        ) {
				process_new_connection(conn);
			}

			close_connection(conn);
		}
	}

	/* Signal master that we're done with connection and exiting */
	(void)pthread_mutex_lock(&ctx->thread_mutex);
	ctx->num_threads--;
	(void)pthread_cond_signal(&ctx->thread_cond);
	/* assert(ctx->num_threads >= 0); */
	if (ctx->num_threads < 0) {
		return NULL;
	}
	(void)pthread_mutex_unlock(&ctx->thread_mutex);

	pthread_setspecific(sTlsKey, NULL);
#if defined(_WIN32) && !defined(__SYMBIAN32__)
	CloseHandle(tls.pthread_cond_helper_mutex);
#endif
	mg_free(conn);

	DEBUG_TRACE("%s", "exiting");
	return NULL;
}

/* Threads have different return types on Windows and Unix. */

#ifdef _WIN32
static unsigned __stdcall worker_thread(void *thread_func_param)
{
	worker_thread_run(thread_func_param);
	return 0;
}
#else
static void *worker_thread(void *thread_func_param)
{
	worker_thread_run(thread_func_param);
	return NULL;
}
#endif /* _WIN32 */

/* Master thread adds accepted socket to a queue */
static void produce_socket(struct mg_context *ctx, const struct socket *sp)
{
#define QUEUE_SIZE(ctx) ((int)(ARRAY_SIZE(ctx->queue)))
	if (!ctx) {
		return;
	}
	(void)pthread_mutex_lock(&ctx->thread_mutex);

	/* If the queue is full, wait */
	while (ctx->stop_flag == 0 &&
	       ctx->sq_head - ctx->sq_tail >= QUEUE_SIZE(ctx)) {
		(void)pthread_cond_wait(&ctx->sq_empty, &ctx->thread_mutex);
	}

	if (ctx->sq_head - ctx->sq_tail < QUEUE_SIZE(ctx)) {
		/* Copy socket to the queue and increment head */
		ctx->queue[ctx->sq_head % QUEUE_SIZE(ctx)] = *sp;
		ctx->sq_head++;
		DEBUG_TRACE("queued socket %d", sp ? sp->sock : -1);
	}

	(void)pthread_cond_signal(&ctx->sq_full);
	(void)pthread_mutex_unlock(&ctx->thread_mutex);
#undef QUEUE_SIZE
}

static void accept_new_connection(const struct socket *listener,
                                  struct mg_context *ctx)
{
	struct socket so;
	char src_addr[IP_ADDR_STR_LEN];
	socklen_t len = sizeof(so.rsa);
	int on = 1;
	int timeout;

	if (!listener) {
		return;
	}

	if ((so.sock = accept(listener->sock, &so.rsa.sa, &len)) ==
	    INVALID_SOCKET) {
	} else if (!check_acl(ctx, ntohl(*(uint32_t *)&so.rsa.sin.sin_addr))) {
		sockaddr_to_string(src_addr, sizeof(src_addr), &so.rsa);
		mg_cry(fc(ctx), "%s: %s is not allowed to connect", __func__, src_addr);
		closesocket(so.sock);
		so.sock = INVALID_SOCKET;
	} else {
		/* Put so socket structure into the queue */
		DEBUG_TRACE("Accepted socket %d", (int)so.sock);
		set_close_on_exec(so.sock, fc(ctx));
		so.is_ssl = listener->is_ssl;
		so.ssl_redir = listener->ssl_redir;
		if (getsockname(so.sock, &so.lsa.sa, &len) != 0) {
			mg_cry(fc(ctx),
			       "%s: getsockname() failed: %s",
			       __func__,
			       strerror(ERRNO));
		}

		/* Set TCP keep-alive. This is needed because if HTTP-level keep-alive
		 * is enabled, and client resets the connection, server won't get
		 * TCP FIN or RST and will keep the connection open forever. With TCP
		 * keep-alive, next keep-alive handshake will figure out that the
		 * client is down and will close the server end.
		 * Thanks to Igor Klopov who suggested the patch. */
		if (setsockopt(so.sock,
		               SOL_SOCKET,
		               SO_KEEPALIVE,
		               (SOCK_OPT_TYPE)&on,
		               sizeof(on)) != 0) {
			mg_cry(fc(ctx),
			       "%s: setsockopt(SOL_SOCKET SO_KEEPALIVE) failed: %s",
			       __func__,
			       strerror(ERRNO));
		}

		if (ctx && ctx->config[REQUEST_TIMEOUT]) {
			timeout = atoi(ctx->config[REQUEST_TIMEOUT]);
		} else {
			timeout = -1;
		}

		/* Set socket timeout to the given value, but not more than a
		 * a certain limit (SOCKET_TIMEOUT_QUANTUM, default 10 seconds),
		 * so the server can exit after that time if requested. */
		if ((timeout > 0) && (timeout < SOCKET_TIMEOUT_QUANTUM)) {
			set_sock_timeout(so.sock, timeout);
		} else {
			set_sock_timeout(so.sock, SOCKET_TIMEOUT_QUANTUM);
		}

		produce_socket(ctx, &so);
	}
}

static void master_thread_run(void *thread_func_param)
{
	struct mg_context *ctx = (struct mg_context *)thread_func_param;
	struct mg_workerTLS tls;
	struct pollfd *pfd;
	unsigned int i;
	unsigned int workerthreadcount;

	if (!ctx) {
		return;
	}

	mg_set_thread_name("master");

/* Increase priority of the master thread */
#if defined(_WIN32)
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
#elif defined(USE_MASTER_THREAD_PRIORITY)
	int min_prio = sched_get_priority_min(SCHED_RR);
	int max_prio = sched_get_priority_max(SCHED_RR);
	if ((min_prio >= 0) && (max_prio >= 0) &&
	    ((USE_MASTER_THREAD_PRIORITY) <= max_prio) &&
	    ((USE_MASTER_THREAD_PRIORITY) >= min_prio)) {
		struct sched_param sched_param = {0};
		sched_param.sched_priority = (USE_MASTER_THREAD_PRIORITY);
		pthread_setschedparam(pthread_self(), SCHED_RR, &sched_param);
	}
#endif

/* Initialize thread local storage */
#if defined(_WIN32) && !defined(__SYMBIAN32__)
	tls.pthread_cond_helper_mutex = CreateEvent(NULL, FALSE, FALSE, NULL);
#endif
	tls.is_master = 1;
	pthread_setspecific(sTlsKey, &tls);

	/* Server starts *now* */
	ctx->start_time = (unsigned long)time(NULL);

	/* Allocate memory for the listening sockets, and start the server */
	pfd =
	    (struct pollfd *)mg_calloc(ctx->num_listening_sockets, sizeof(pfd[0]));
	while (pfd != NULL && ctx->stop_flag == 0) {
		for (i = 0; i < ctx->num_listening_sockets; i++) {
			pfd[i].fd = ctx->listening_sockets[i].sock;
			pfd[i].events = POLLIN;
		}

		if (poll(pfd, ctx->num_listening_sockets, 200) > 0) {
			for (i = 0; i < ctx->num_listening_sockets; i++) {
				/* NOTE(lsm): on QNX, poll() returns POLLRDNORM after the
				 * successful poll, and POLLIN is defined as
				 * (POLLRDNORM | POLLRDBAND)
				 * Therefore, we're checking pfd[i].revents & POLLIN, not
				 * pfd[i].revents == POLLIN. */
				if (ctx->stop_flag == 0 && (pfd[i].revents & POLLIN)) {
					accept_new_connection(&ctx->listening_sockets[i], ctx);
				}
			}
		}
	}
	mg_free(pfd);
	DEBUG_TRACE("%s", "stopping workers");

	/* Stop signal received: somebody called mg_stop. Quit. */
	close_all_listening_sockets(ctx);

	/* Wakeup workers that are waiting for connections to handle. */
	pthread_cond_broadcast(&ctx->sq_full);

	/* Wait until all threads finish */
	(void)pthread_mutex_lock(&ctx->thread_mutex);
	while (ctx->num_threads > 0) {
		(void)pthread_cond_wait(&ctx->thread_cond, &ctx->thread_mutex);
	}
	(void)pthread_mutex_unlock(&ctx->thread_mutex);

	/* Join all worker threads to avoid leaking threads. */
	workerthreadcount = ctx->workerthreadcount;
	for (i = 0; i < workerthreadcount; i++) {
		mg_join_thread(ctx->workerthreadids[i]);
	}

#if !defined(NO_SSL)
	if (ctx->ssl_ctx != NULL) {
		uninitialize_ssl(ctx);
	}
#endif
	DEBUG_TRACE("%s", "exiting");

#if defined(_WIN32) && !defined(__SYMBIAN32__)
	CloseHandle(tls.pthread_cond_helper_mutex);
#endif
	pthread_setspecific(sTlsKey, NULL);

	/* Signal mg_stop() that we're done.
	 * WARNING: This must be the very last thing this
	 * thread does, as ctx becomes invalid after this line. */
	ctx->stop_flag = 2;
}

/* Threads have different return types on Windows and Unix. */
#ifdef _WIN32
static unsigned __stdcall master_thread(void *thread_func_param)
{
	master_thread_run(thread_func_param);
	return 0;
}
#else
static void *master_thread(void *thread_func_param)
{
	master_thread_run(thread_func_param);
	return NULL;
}
#endif /* _WIN32 */

static void free_context(struct mg_context *ctx)
{
	int i;
	struct mg_request_handler_info *tmp_rh;

	if (ctx == NULL) {
		return;
	}

	if (ctx->callbacks.exit_context) {
		ctx->callbacks.exit_context(ctx);
	}

	/* All threads exited, no sync is needed. Destroy thread mutex and condvars
	 */
	(void)pthread_mutex_destroy(&ctx->thread_mutex);
	(void)pthread_cond_destroy(&ctx->thread_cond);
	(void)pthread_cond_destroy(&ctx->sq_empty);
	(void)pthread_cond_destroy(&ctx->sq_full);

	/* Destroy other context global data structures mutex */
	(void)pthread_mutex_destroy(&ctx->nonce_mutex);

#if defined(USE_TIMERS)
	timers_exit(ctx);
#endif

	/* Deallocate config parameters */
	for (i = 0; i < NUM_OPTIONS; i++) {
		if (ctx->config[i] != NULL) {
#if defined(_MSC_VER)
#pragma warning(suppress : 6001)
#endif
			mg_free(ctx->config[i]);
		}
	}

	/* Deallocate request handlers */
	while (ctx->request_handlers) {
		tmp_rh = ctx->request_handlers;
		ctx->request_handlers = tmp_rh->next;
		mg_free(tmp_rh->uri);
		mg_free(tmp_rh);
	}

#ifndef NO_SSL
	/* Deallocate SSL context */
	if (ctx->ssl_ctx != NULL) {
		SSL_CTX_free(ctx->ssl_ctx);
	}
	if (ssl_mutexes != NULL) {
		mg_free(ssl_mutexes);
		ssl_mutexes = NULL;
	}
#endif /* !NO_SSL */

	/* Deallocate worker thread ID array */
	if (ctx->workerthreadids != NULL) {
		mg_free(ctx->workerthreadids);
	}

	/* Deallocate the tls variable */
	if (mg_atomic_dec(&sTlsInit) == 0) {
		pthread_key_delete(sTlsKey);
	}

	/* deallocate system name string */
	mg_free(ctx->systemName);

	/* Deallocate context itself */
	mg_free(ctx);
}

void mg_stop(struct mg_context *ctx)
{
	if (!ctx) {
		return;
	}

	ctx->stop_flag = 1;

	/* Wait until mg_fini() stops */
	while (ctx->stop_flag != 2) {
		(void)mg_sleep(10);
	}
	mg_join_thread(ctx->masterthreadid);
	free_context(ctx);

#if defined(_WIN32) && !defined(__SYMBIAN32__)
	(void)WSACleanup();
#endif /* _WIN32 && !__SYMBIAN32__ */
}

static void get_system_name(char **sysName)
{
#if defined(_WIN32)
#if !defined(__SYMBIAN32__)
	char name[128];
	DWORD dwVersion = 0;
	DWORD dwMajorVersion = 0;
	DWORD dwMinorVersion = 0;
	DWORD dwBuild = 0;

#ifdef _MSC_VER
#pragma warning(push)
// GetVersion was declared deprecated
#pragma warning(disable : 4996)
#endif
	dwVersion = GetVersion();
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
	dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
	dwBuild = ((dwVersion < 0x80000000) ? (DWORD)(HIWORD(dwVersion)) : 0);
	(void)dwBuild;

	sprintf(name,
	        "Windows %u.%u",
	        (unsigned)dwMajorVersion,
	        (unsigned)dwMinorVersion);
	*sysName = mg_strdup(name);
#else
	*sysName = mg_strdup("Symbian");
#endif
#else
	struct utsname name;
	memset(&name, 0, sizeof(name));
	uname(&name);
	*sysName = mg_strdup(name.sysname);
#endif
}

struct mg_context *mg_start(const struct mg_callbacks *callbacks,
                            void *user_data,
                            const char **options)
{
	struct mg_context *ctx;
	const char *name, *value, *default_value;
	int idx, ok, workerthreadcount;
	unsigned int i;
	void (*exit_callback)(const struct mg_context *ctx) = 0;

#if defined(_WIN32) && !defined(__SYMBIAN32__)
	WSADATA data;
	WSAStartup(MAKEWORD(2, 2), &data);
#if defined(_MSC_VER)
#pragma warning(suppress : 28125)
#endif
	if (!sTlsInit) {
		InitializeCriticalSection(&global_log_file_lock);
	}
#endif /* _WIN32 && !__SYMBIAN32__ */

	/* Allocate context and initialize reasonable general case defaults. */
	if ((ctx = (struct mg_context *)mg_calloc(1, sizeof(*ctx))) == NULL) {
		return NULL;
	}

	if (mg_atomic_inc(&sTlsInit) == 1) {
		if (0 != pthread_key_create(&sTlsKey, NULL)) {
			/* Fatal error - abort start. However, this situation should never
			 * occur in practice. */
			mg_atomic_dec(&sTlsInit);
			mg_cry(fc(ctx), "Cannot initialize thread local storage");
			mg_free(ctx);
			return NULL;
		}
	} else {
		/* TODO (low): istead of sleeping, check if sTlsKey is already
		 * initialized. */
		mg_sleep(1);
	}

	ok = 0 == pthread_mutex_init(&ctx->thread_mutex, NULL);
	ok &= 0 == pthread_cond_init(&ctx->thread_cond, NULL);
	ok &= 0 == pthread_cond_init(&ctx->sq_empty, NULL);
	ok &= 0 == pthread_cond_init(&ctx->sq_full, NULL);
	ok &= 0 == pthread_mutex_init(&ctx->nonce_mutex, NULL);
	if (!ok) {
		/* Fatal error - abort start. However, this situation should never
		 * occur in practice. */
		mg_cry(fc(ctx), "Cannot initialize thread synchronization objects");
		mg_free(ctx);
		return NULL;
	}

	if (callbacks) {
		ctx->callbacks = *callbacks;
		exit_callback = callbacks->exit_context;
		ctx->callbacks.exit_context = 0;
	}
	ctx->user_data = user_data;
	ctx->request_handlers = NULL;

#if defined(USE_LUA) && defined(USE_WEBSOCKET)
	ctx->shared_lua_websockets = 0;
#endif

	while (options && (name = *options++) != NULL) {
		if ((idx = get_option_index(name)) == -1) {
			mg_cry(fc(ctx), "Invalid option: %s", name);
			free_context(ctx);
			return NULL;
		} else if ((value = *options++) == NULL) {
			mg_cry(fc(ctx), "%s: option value cannot be NULL", name);
			free_context(ctx);
			return NULL;
		}
		if (ctx->config[idx] != NULL) {
			mg_cry(fc(ctx), "warning: %s: duplicate option", name);
			mg_free(ctx->config[idx]);
		}
		ctx->config[idx] = mg_strdup(value);
		DEBUG_TRACE("[%s] -> [%s]", name, value);
	}

	/* Set default value if needed */
	for (i = 0; config_options[i].name != NULL; i++) {
		default_value = config_options[i].default_value;
		if (ctx->config[i] == NULL && default_value != NULL) {
			ctx->config[i] = mg_strdup(default_value);
		}
	}

#if defined(NO_FILES)
	if (ctx->config[DOCUMENT_ROOT] != NULL) {
		mg_cry(fc(ctx), "%s", "Document root must not be set");
		free_context(ctx);
		return NULL;
	}
#endif

	get_system_name(&ctx->systemName);

	/* NOTE(lsm): order is important here. SSL certificates must
	 * be initialized before listening ports. UID must be set last. */
	if (!set_gpass_option(ctx) ||
#if !defined(NO_SSL)
	    !set_ssl_option(ctx) ||
#endif
	    !set_ports_option(ctx) ||
#if !defined(_WIN32)
	    !set_uid_option(ctx) ||
#endif
	    !set_acl_option(ctx)) {
		free_context(ctx);
		return NULL;
	}

#if !defined(_WIN32) && !defined(__SYMBIAN32__)
	/* Ignore SIGPIPE signal, so if browser cancels the request, it
	 * won't kill the whole process. */
	(void)signal(SIGPIPE, SIG_IGN);
#endif /* !_WIN32 && !__SYMBIAN32__ */

	workerthreadcount = atoi(ctx->config[NUM_THREADS]);

	if (workerthreadcount > MAX_WORKER_THREADS) {
		mg_cry(fc(ctx), "Too many worker threads");
		free_context(ctx);
		return NULL;
	}

	if (workerthreadcount > 0) {
		ctx->workerthreadcount = ((unsigned int)(workerthreadcount));
		ctx->workerthreadids =
		    (pthread_t *)mg_calloc(ctx->workerthreadcount, sizeof(pthread_t));
		if (ctx->workerthreadids == NULL) {
			mg_cry(fc(ctx), "Not enough memory for worker thread ID array");
			free_context(ctx);
			return NULL;
		}
	}

#if defined(USE_TIMERS)
	if (timers_init(ctx) != 0) {
		mg_cry(fc(ctx), "Error creating timers");
		free_context(ctx);
		return NULL;
	}
#endif

	/* Context has been created - init user libraries */
	if (ctx->callbacks.init_context) {
		ctx->callbacks.init_context(ctx);
	}
	ctx->callbacks.exit_context = exit_callback;
	ctx->context_type = 1; /* server context */

	/* Start master (listening) thread */
	mg_start_thread_with_id(master_thread, ctx, &ctx->masterthreadid);

	/* Start worker threads */
	for (i = 0; i < ctx->workerthreadcount; i++) {
		(void)pthread_mutex_lock(&ctx->thread_mutex);
		ctx->num_threads++;
		(void)pthread_mutex_unlock(&ctx->thread_mutex);
		if (mg_start_thread_with_id(
		        worker_thread, ctx, &ctx->workerthreadids[i]) != 0) {
			(void)pthread_mutex_lock(&ctx->thread_mutex);
			ctx->num_threads--;
			(void)pthread_mutex_unlock(&ctx->thread_mutex);
			if (i > 0) {
				mg_cry(fc(ctx),
				       "Cannot start worker thread %i: error %ld",
				       i + 1,
				       (long)ERRNO);
			} else {
				mg_cry(
				    fc(ctx), "Cannot create threads: error %ld", (long)ERRNO);
				free_context(ctx);
				return NULL;
			}
			break;
		}
	}

	return ctx;
}
