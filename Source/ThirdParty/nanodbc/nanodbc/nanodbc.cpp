/// \file nanodbc.cpp Implementation details.
#ifndef DOXYGEN

// ASCII art banners are helpful for code editors with a minimap display.
// Generated with http://patorjk.com/software/taag/#p=display&v=0&f=Colossal

#if defined(_MSC_VER)
#if _MSC_VER <= 1800
// silence spurious Visual C++ warnings
#pragma warning(disable : 4244) // warning about integer conversion issues.
#pragma warning(disable : 4312) // warning about 64-bit portability issues.
#endif
#pragma warning(disable : 4996) // warning about deprecated declaration
#endif

#include <nanodbc/nanodbc.h>

#include <algorithm>
#include <clocale>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <map>
#include <type_traits>

#ifndef __clang__
#include <cstdint>
#endif

// User may redefine NANODBC_ASSERT macro in nanodbc/nanodbc.h
#ifndef NANODBC_ASSERT
#include <cassert>
#define NANODBC_ASSERT(expr) assert(expr)
#endif

#ifdef NANODBC_ENABLE_BOOST
#include <boost/locale/encoding_utf.hpp>
#elif defined(__GNUC__) && (__GNUC__ < 5)
#include <cwchar>
#else
#include <codecvt>
#endif

#ifdef __APPLE__
// silence spurious OS X deprecation warnings
#define MAC_OS_X_VERSION_MIN_REQUIRED MAC_OS_X_VERSION_10_6
#endif

#ifdef _WIN32
// needs to be included above sql.h for windows
#ifndef __MINGW32__
#define NOMINMAX
#endif
#include <windows.h>
#endif

#include <sql.h>
#include <sqlext.h>

// Driver specific SQL data type defines.
// Microsoft has -150 thru -199 reserved for Microsoft SQL Server Native Client driver usage.
// Originally, defined in sqlncli.h (old SQL Server Native Client driver)
// and msodbcsql.h (new Microsoft ODBC Driver for SQL Server)
// See https://github.com/lexicalunit/nanodbc/issues/226
#ifndef SQL_SS_VARIANT
#define SQL_SS_VARIANT (-150)
#endif
#ifndef SQL_SS_XML
#define SQL_SS_XML (-152)
#endif
#ifndef SQL_SS_TABLE
#define SQL_SS_TABLE (-153)
#endif
#ifndef SQL_SS_TIME2
#define SQL_SS_TIME2 (-154)
#endif
#ifndef SQL_SS_TIMESTAMPOFFSET
#define SQL_SS_TIMESTAMPOFFSET (-155)
#endif
// Large CLR User-Defined Types (ODBC)
// https://msdn.microsoft.com/en-us/library/bb677316.aspx
// Essentially, UDT is a varbinary type with additional metadata.
// Memory layout: SQLCHAR *(unsigned char *)
// C data type:   SQL_C_BINARY
// Value:         SQL_BINARY (-2)
#ifndef SQL_SS_UDT
#define SQL_SS_UDT (-151) // from sqlncli.h
#endif

#ifndef SQL_NVARCHAR
#define SQL_NVARCHAR (-10)
#endif

// Default to ODBC version defined by NANODBC_ODBC_VERSION if provided.
#ifndef NANODBC_ODBC_VERSION
#ifdef SQL_OV_ODBC3_80
// Otherwise, use ODBC v3.8 if it's available...
#define NANODBC_ODBC_VERSION SQL_OV_ODBC3_80
#else
// or fallback to ODBC v3.x.
#define NANODBC_ODBC_VERSION SQL_OV_ODBC3
#endif
#endif

// clang-format off
// 888     888          d8b                       888
// 888     888          Y8P                       888
// 888     888                                    888
// 888     888 88888b.  888  .d8888b .d88b.   .d88888  .d88b.
// 888     888 888 "88b 888 d88P"   d88""88b d88" 888 d8P  Y8b
// 888     888 888  888 888 888     888  888 888  888 88888888
// Y88b. .d88P 888  888 888 Y88b.   Y88..88P Y88b 888 Y8b.
//  "Y88888P"  888  888 888  "Y8888P "Y88P"   "Y88888  "Y8888
// MARK: Unicode -
// clang-format on

#ifdef NANODBC_ENABLE_UNICODE
#define NANODBC_FUNC(f) f##W
#define NANODBC_SQLCHAR SQLWCHAR
#else
#define NANODBC_FUNC(f) f
#define NANODBC_SQLCHAR SQLCHAR
#endif

#ifdef NANODBC_USE_IODBC_WIDE_STRINGS
typedef std::u32string wide_string;
#define NANODBC_CODECVT_TYPE std::codecvt_utf8
#else
#ifdef _MSC_VER
typedef std::wstring wide_string;
#define NANODBC_CODECVT_TYPE std::codecvt_utf8_utf16
#else
typedef std::u16string wide_string;
#define NANODBC_CODECVT_TYPE std::codecvt_utf8_utf16
#endif
#endif
typedef wide_string::value_type wide_char_t;

#if defined(_MSC_VER)
#ifndef NANODBC_ENABLE_UNICODE
// Disable unicode in sqlucode.h on Windows when NANODBC_ENABLE_UNICODE
// is not defined. This is required because unicode is enabled by
// default on many Windows systems.
#define SQL_NOUNICODEMAP
#endif
#endif

// clang-format off
//  .d88888b.  8888888b.  888888b.    .d8888b.       888b     d888
// d88P" "Y88b 888  "Y88b 888  "88b  d88P  Y88b      8888b   d8888
// 888     888 888    888 888  .88P  888    888      88888b.d88888
// 888     888 888    888 8888888K.  888             888Y88888P888  8888b.   .d8888b 888d888 .d88b.  .d8888b
// 888     888 888    888 888  "Y88b 888             888 Y888P 888     "88b d88P"    888P"  d88""88b 88K
// 888     888 888    888 888    888 888    888      888  Y8P  888 .d888888 888      888    888  888 "Y8888b.
// Y88b. .d88P 888  .d88P 888   d88P Y88b  d88P      888   "   888 888  888 Y88b.    888    Y88..88P      X88
//  "Y88888P"  8888888P"  8888888P"   "Y8888P"       888       888 "Y888888  "Y8888P 888     "Y88P"   88888P'
// MARK: ODBC Macros -
// clang-format on

#define NANODBC_STRINGIZE_I(text) #text
#define NANODBC_STRINGIZE(text) NANODBC_STRINGIZE_I(text)

// By making all calls to ODBC functions through this macro, we can easily get
// runtime debugging information of which ODBC functions are being called,
// in what order, and with what parameters by defining NANODBC_ODBC_API_DEBUG.
#ifdef NANODBC_ODBC_API_DEBUG
#include <iostream>
#define NANODBC_CALL_RC(FUNC, RC, ...)                                                             \
    do                                                                                             \
    {                                                                                              \
        std::cerr << __FILE__                                                                      \
            ":" NANODBC_STRINGIZE(__LINE__) " " NANODBC_STRINGIZE(FUNC) "(" #__VA_ARGS__ ")"       \
                  << std::endl;                                                                    \
        RC = FUNC(__VA_ARGS__);                                                                    \
    } while (false) /**/
#define NANODBC_CALL(FUNC, ...)                                                                    \
    do                                                                                             \
    {                                                                                              \
        std::cerr << __FILE__                                                                      \
            ":" NANODBC_STRINGIZE(__LINE__) " " NANODBC_STRINGIZE(FUNC) "(" #__VA_ARGS__ ")"       \
                  << std::endl;                                                                    \
        FUNC(__VA_ARGS__);                                                                         \
    } while (false) /**/
#else
#define NANODBC_CALL_RC(FUNC, RC, ...) RC = FUNC(__VA_ARGS__)
#define NANODBC_CALL(FUNC, ...) FUNC(__VA_ARGS__)
#endif

// clang-format off
// 8888888888                                      888    888                        888 888 d8b
// 888                                             888    888                        888 888 Y8P
// 888                                             888    888                        888 888
// 8888888    888d888 888d888 .d88b.  888d888      8888888888  8888b.  88888b.   .d88888 888 888 88888b.   .d88b.
// 888        888P"   888P"  d88""88b 888P"        888    888     "88b 888 "88b d88" 888 888 888 888 "88b d88P"88b
// 888        888     888    888  888 888          888    888 .d888888 888  888 888  888 888 888 888  888 888  888
// 888        888     888    Y88..88P 888          888    888 888  888 888  888 Y88b 888 888 888 888  888 Y88b 888
// 8888888888 888     888     "Y88P"  888          888    888 "Y888888 888  888  "Y88888 888 888 888  888  "Y88888
//                                                                                                             888
//                                                                                                        Y8b d88P
//                                                                                                         "Y88P"
// MARK: Error Handling -
// clang-format on

namespace
{
#ifdef NANODBC_ODBC_API_DEBUG
inline std::string return_code(RETCODE rc)
{
    switch (rc)
    {
    case SQL_SUCCESS:
        return "SQL_SUCCESS";
    case SQL_SUCCESS_WITH_INFO:
        return "SQL_SUCCESS_WITH_INFO";
    case SQL_ERROR:
        return "SQL_ERROR";
    case SQL_INVALID_HANDLE:
        return "SQL_INVALID_HANDLE";
    case SQL_NO_DATA:
        return "SQL_NO_DATA";
    case SQL_NEED_DATA:
        return "SQL_NEED_DATA";
    case SQL_STILL_EXECUTING:
        return "SQL_STILL_EXECUTING";
    }
    NANODBC_ASSERT(0);
    return "unknown"; // should never make it here
}
#endif

// Easy way to check if a return code signifies success.
inline bool success(RETCODE rc)
{
#ifdef NANODBC_ODBC_API_DEBUG
    std::cerr << "<-- rc: " << return_code(rc) << " | " << std::endl;
#endif
    return rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO;
}

// Returns the array size.
template <typename T, std::size_t N>
inline std::size_t arrlen(T (&)[N])
{
    return N;
}

// Operates like strlen() on a character array.
template <typename T, std::size_t N>
inline std::size_t strarrlen(T (&a)[N])
{
    const T* s = &a[0];
    std::size_t i = 0;
    while (*s++ && i < N)
        i++;
    return i;
}

inline void convert(const wide_string& in, std::string& out)
{
#ifdef NANODBC_ENABLE_BOOST
    using boost::locale::conv::utf_to_utf;
    out = utf_to_utf<char>(in.c_str(), in.c_str() + in.size());
#elif defined(__GNUC__) && (__GNUC__ < 5)
    std::vector<wchar_t> characters(in.begin(), in.end());
    const wchar_t * source = characters.data();
    size_t size = wcsnrtombs(nullptr, &source, characters.size(), 0, nullptr);
    if (size == std::string::npos)
        throw std::range_error("UTF-16 -> UTF-8 conversion error");
    out.resize(size);
    wcsnrtombs(&out[0], &source, characters.size(), out.length(), nullptr);
#elif defined(_MSC_VER) && (_MSC_VER >= 1900)
    // Workaround for confirmed bug in VS2015 and VS2017 too
    // See: https://connect.microsoft.com/VisualStudio/Feedback/Details/1403302
    auto p = reinterpret_cast<unsigned short const*>(in.data());
    out = std::wstring_convert<NANODBC_CODECVT_TYPE<unsigned short>, unsigned short>().to_bytes(
        p, p + in.size());
#else
    out = std::wstring_convert<NANODBC_CODECVT_TYPE<wide_char_t>, wide_char_t>().to_bytes(in);
#endif
}

#ifdef NANODBC_ENABLE_UNICODE
inline void convert(const std::string& in, wide_string& out)
{
#ifdef NANODBC_ENABLE_BOOST
    using boost::locale::conv::utf_to_utf;
    out = utf_to_utf<wide_char_t>(in.c_str(), in.c_str() + in.size());
#elif defined(__GNUC__) && (__GNUC__ < 5)
    size_t size = mbsnrtowcs(nullptr, in.data(), in.length(), 0, nullptr);
    if (size == std::string::npos)
        throw std::range_error("UTF-8 -> UTF-16 conversion error");
    std::vector<wchar_t> characters(size);
    const char * source = in.data();
    mbsnrtowcs(&characters[0], &source, in.length(), characters.size(), nullptr);
    out = std::string(characters.begin(), characters.end());
#elif defined(_MSC_VER) && (_MSC_VER >= 1900)
    // Workaround for confirmed bug in VS2015 and VS2017 too
    // See: https://connect.microsoft.com/VisualStudio/Feedback/Details/1403302
    auto s =
        std::wstring_convert<NANODBC_CODECVT_TYPE<unsigned short>, unsigned short>().from_bytes(in);
    auto p = reinterpret_cast<wide_char_t const*>(s.data());
    out.assign(p, p + s.size());
#else
    out = std::wstring_convert<NANODBC_CODECVT_TYPE<wide_char_t>, wide_char_t>().from_bytes(in);
#endif
}

inline void convert(const wide_string& in, wide_string& out)
{
    out = in;
}
#else
inline void convert(const std::string& in, std::string& out)
{
    out = in;
}
#endif

// Attempts to get the most recent ODBC error as a string.
// Always returns std::string, even in unicode mode.
inline std::string
recent_error(SQLHANDLE handle, SQLSMALLINT handle_type, long& native, std::string& state)
{
    nanodbc::string result;
    std::string rvalue;
    std::vector<NANODBC_SQLCHAR> sql_message(SQL_MAX_MESSAGE_LENGTH);
    sql_message[0] = '\0';

    SQLINTEGER i = 1;
    SQLINTEGER native_error;
    SQLSMALLINT total_bytes;
    NANODBC_SQLCHAR sql_state[6];
    RETCODE rc;

    do
    {
        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLGetDiagRec),
            rc,
            handle_type,
            handle,
            (SQLSMALLINT)i,
            sql_state,
            &native_error,
            0,
            0,
            &total_bytes);

        if (success(rc) && total_bytes > 0)
            sql_message.resize(static_cast<std::size_t>(total_bytes) + 1);

        if (rc == SQL_NO_DATA)
            break;

        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLGetDiagRec),
            rc,
            handle_type,
            handle,
            (SQLSMALLINT)i,
            sql_state,
            &native_error,
            sql_message.data(),
            (SQLSMALLINT)sql_message.size(),
            &total_bytes);

        if (!success(rc))
        {
            convert(result, rvalue);
            return rvalue;
        }

        if (!result.empty())
            result += ' ';

        result += nanodbc::string(sql_message.begin(), sql_message.end());
        i++;

// NOTE: unixODBC using PostgreSQL and SQLite drivers crash if you call SQLGetDiagRec()
// more than once. So as a (terrible but the best possible) workaround just exit
// this loop early on non-Windows systems.
#ifndef _MSC_VER
        break;
#endif
    } while (rc != SQL_NO_DATA);

    convert(result, rvalue);
    state = std::string(&sql_state[0], &sql_state[arrlen(sql_state) - 1]);
    native = native_error;
    std::string status = state;
    status += ": ";
    status += rvalue;

    // some drivers insert \0 into error messages for unknown reasons
    using std::replace;
    replace(status.begin(), status.end(), '\0', ' ');

    return status;
}

} // namespace

namespace nanodbc
{

type_incompatible_error::type_incompatible_error()
    : std::runtime_error("type incompatible")
{
}

const char* type_incompatible_error::what() const NANODBC_NOEXCEPT
{
    return std::runtime_error::what();
}

null_access_error::null_access_error()
    : std::runtime_error("null access")
{
}

const char* null_access_error::what() const NANODBC_NOEXCEPT
{
    return std::runtime_error::what();
}

index_range_error::index_range_error()
    : std::runtime_error("index out of range")
{
}

const char* index_range_error::what() const NANODBC_NOEXCEPT
{
    return std::runtime_error::what();
}

programming_error::programming_error(const std::string& info)
    : std::runtime_error(info.c_str())
{
}

const char* programming_error::what() const NANODBC_NOEXCEPT
{
    return std::runtime_error::what();
}

database_error::database_error(void* handle, short handle_type, const std::string& info)
    : std::runtime_error(info)
    , native_error(0)
    , sql_state("00000")
{
    message = std::string(std::runtime_error::what()) +
              recent_error(handle, handle_type, native_error, sql_state);
}

const char* database_error::what() const NANODBC_NOEXCEPT
{
    return message.c_str();
}

const long database_error::native() const NANODBC_NOEXCEPT
{
    return native_error;
}

const std::string database_error::state() const NANODBC_NOEXCEPT
{
    return sql_state;
}

} // namespace nanodbc

// Throwing exceptions using NANODBC_THROW_DATABASE_ERROR enables file name
// and line numbers to be inserted into the error message. Useful for debugging.
#define NANODBC_THROW_DATABASE_ERROR(handle, handle_type)                                          \
    throw nanodbc::database_error(                                                                 \
        handle, handle_type, __FILE__ ":" NANODBC_STRINGIZE(__LINE__) ": ") /**/

// clang-format off
// 8888888b.           888             d8b 888
// 888  "Y88b          888             Y8P 888
// 888    888          888                 888
// 888    888  .d88b.  888888  8888b.  888 888 .d8888b
// 888    888 d8P  Y8b 888        "88b 888 888 88K
// 888    888 88888888 888    .d888888 888 888 "Y8888b.
// 888  .d88P Y8b.     Y88b.  888  888 888 888      X88
// 8888888P"   "Y8888   "Y888 "Y888888 888 888  88888P'
// MARK: Details -
// clang-format on

#if !defined(NANODBC_DISABLE_ASYNC) && defined(SQL_ATTR_ASYNC_STMT_EVENT) &&                       \
    defined(SQL_API_SQLCOMPLETEASYNC)
#define NANODBC_DO_ASYNC_IMPL
#endif

namespace
{

using namespace std; // if int64_t is in std namespace (in c++11)

template <typename T>
using is_integral8 = std::integral_constant<
    bool,
    std::is_integral<T>::value && sizeof(T) == 1 && !std::is_same<T, char>::value>;

template <typename T>
using is_integral16 = std::integral_constant<
    bool,
    std::is_integral<T>::value && sizeof(T) == 2 && !std::is_same<T, wchar_t>::value>;

template <typename T>
using is_integral32 = std::integral_constant<
    bool,
    std::is_integral<T>::value && sizeof(T) == 4 && !std::is_same<T, wchar_t>::value>;

template <typename T>
using is_integral64 = std::integral_constant<bool, std::is_integral<T>::value && sizeof(T) == 8>;

// A utility for calculating the ctype from the given type T.
// I essentially create a lookup table based on the MSDN ODBC documentation.
// See http://msdn.microsoft.com/en-us/library/windows/desktop/ms714556(v=vs.85).aspx
template <class T, typename Enable = void>
struct sql_ctype
{
};

template <>
struct sql_ctype<uint8_t>
{
    static const SQLSMALLINT value = SQL_C_BINARY;
};

template <typename T>
struct sql_ctype<
    T,
    typename std::enable_if<is_integral16<T>::value && std::is_signed<T>::value>::type>
{
    static const SQLSMALLINT value = SQL_C_SSHORT;
};

template <typename T>
struct sql_ctype<
    T,
    typename std::enable_if<is_integral16<T>::value && std::is_unsigned<T>::value>::type>
{
    static const SQLSMALLINT value = SQL_C_USHORT;
};

template <typename T>
struct sql_ctype<
    T,
    typename std::enable_if<is_integral32<T>::value && std::is_signed<T>::value>::type>
{
    static const SQLSMALLINT value = SQL_C_SLONG;
};

template <typename T>
struct sql_ctype<
    T,
    typename std::enable_if<is_integral32<T>::value && std::is_unsigned<T>::value>::type>
{
    static const SQLSMALLINT value = SQL_C_ULONG;
};

template <typename T>
struct sql_ctype<
    T,
    typename std::enable_if<is_integral64<T>::value && std::is_signed<T>::value>::type>
{
    static const SQLSMALLINT value = SQL_C_SBIGINT;
};

template <typename T>
struct sql_ctype<
    T,
    typename std::enable_if<is_integral64<T>::value && std::is_unsigned<T>::value>::type>
{
    static const SQLSMALLINT value = SQL_C_UBIGINT;
};

template <>
struct sql_ctype<float>
{
    static const SQLSMALLINT value = SQL_C_FLOAT;
};

template <>
struct sql_ctype<double>
{
    static const SQLSMALLINT value = SQL_C_DOUBLE;
};

template <>
struct sql_ctype<nanodbc::string::value_type>
{
#ifdef NANODBC_ENABLE_UNICODE
    static const SQLSMALLINT value = SQL_C_WCHAR;
#else
    static const SQLSMALLINT value = SQL_C_CHAR;
#endif
};

template <>
struct sql_ctype<nanodbc::string>
{
#ifdef NANODBC_ENABLE_UNICODE
    static const SQLSMALLINT value = SQL_C_WCHAR;
#else
    static const SQLSMALLINT value = SQL_C_CHAR;
#endif
};

template <>
struct sql_ctype<nanodbc::date>
{
    static const SQLSMALLINT value = SQL_C_DATE;
};

template <>
struct sql_ctype<nanodbc::time>
{
    static const SQLSMALLINT value = SQL_C_TIME;
};

template <>
struct sql_ctype<nanodbc::timestamp>
{
    static const SQLSMALLINT value = SQL_C_TIMESTAMP;
};

// Encapsulates resources needed for column binding.
class bound_column
{
public:
    bound_column(const bound_column& rhs) = delete;
    bound_column& operator=(bound_column rhs) = delete;

    bound_column()
        : name_()
        , column_(0)
        , sqltype_(0)
        , sqlsize_(0)
        , scale_(0)
        , ctype_(0)
        , clen_(0)
        , blob_(false)
        , cbdata_(0)
        , pdata_(0)
    {
    }

    ~bound_column()
    {
        delete[] cbdata_;
        delete[] pdata_;
    }

public:
    nanodbc::string name_;
    short column_;
    SQLSMALLINT sqltype_;
    SQLULEN sqlsize_;
    SQLSMALLINT scale_;
    SQLSMALLINT ctype_;
    SQLULEN clen_;
    bool blob_;
    nanodbc::null_type* cbdata_;
    char* pdata_;
};

// Encapsulates properties of statement parameter.
// Parameter corresponds to parameter marker associated with a prepared SQL statement.
struct bound_parameter
{
    bound_parameter() = default;

    SQLULEN size_ = 0;       // SQL data size of column or expression inbytes or characters
    SQLUSMALLINT index_ = 0; // Zero-based index of parameter marker
    SQLSMALLINT iotype_ = 0; // Input/Output type of parameter
    SQLSMALLINT type_ = 0;   // SQL data type of parameter
    SQLSMALLINT scale_ = 0;  // decimal digits of column or expression
};

// Encapsulates properties of buffer with data values bound to statement parameter.
template <typename T>
struct bound_buffer
{
    bound_buffer() = default;
    bound_buffer(T const* values, std::size_t size, std::size_t value_size = 0)
        : values_(values)
        , size_(size)
        , value_size_(value_size)
    {
    }

    T const* values_ = nullptr;  // Pointer to buffer for parameter's data
    std::size_t size_ = 0;       // Number of values (1 or length of array)
    std::size_t value_size_ = 0; // Size of single value (max size). Zero, if ignored.
};

// Allocates the native ODBC handles.
inline void allocate_environment_handle(SQLHENV& env)
{
    RETCODE rc;
    NANODBC_CALL_RC(SQLAllocHandle, rc, SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    if (!success(rc))
        NANODBC_THROW_DATABASE_ERROR(env, SQL_HANDLE_ENV);

    try
    {
        NANODBC_CALL_RC(
            SQLSetEnvAttr,
            rc,
            env,
            SQL_ATTR_ODBC_VERSION,
            (SQLPOINTER)NANODBC_ODBC_VERSION,
            SQL_IS_UINTEGER);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(env, SQL_HANDLE_ENV);
    }
    catch (...)
    {
        NANODBC_CALL(SQLFreeHandle, SQL_HANDLE_ENV, env);
        throw;
    }
}

inline void allocate_handle(SQLHENV& env, SQLHDBC& conn)
{
    allocate_environment_handle(env);

    try
    {
        NANODBC_ASSERT(env);
        RETCODE rc;
        NANODBC_CALL_RC(SQLAllocHandle, rc, SQL_HANDLE_DBC, env, &conn);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(env, SQL_HANDLE_ENV);
    }
    catch (...)
    {
        NANODBC_CALL(SQLFreeHandle, SQL_HANDLE_ENV, env);
        throw;
    }
}

} // namespace

// clang-format off
//  .d8888b.                                               888    d8b                             8888888                        888
// d88P  Y88b                                              888    Y8P                               888                          888
// 888    888                                              888                                      888                          888
// 888         .d88b.  88888b.  88888b.   .d88b.   .d8888b 888888 888  .d88b.  88888b.              888   88888b.d88b.  88888b.  888
// 888        d88""88b 888 "88b 888 "88b d8P  Y8b d88P"    888    888 d88""88b 888 "88b             888   888 "888 "88b 888 "88b 888
// 888    888 888  888 888  888 888  888 88888888 888      888    888 888  888 888  888             888   888  888  888 888  888 888
// Y88b  d88P Y88..88P 888  888 888  888 Y8b.     Y88b.    Y88b.  888 Y88..88P 888  888             888   888  888  888 888 d88P 888
//  "Y8888P"   "Y88P"  888  888 888  888  "Y8888   "Y8888P  "Y888 888  "Y88P"  888  888           8888888 888  888  888 88888P"  888
//                                                                                                                      888
//                                                                                                                      888
//                                                                                                                      888
// MARK: Connection Impl -
// clang-format on

namespace nanodbc
{

class connection::connection_impl
{
public:
    connection_impl(const connection_impl&) = delete;
    connection_impl& operator=(const connection_impl&) = delete;

    connection_impl()
        : env_(0)
        , conn_(0)
        , connected_(false)
        , transactions_(0)
        , rollback_(false)
    {
        allocate_handle(env_, conn_);
    }

    connection_impl(const string& dsn, const string& user, const string& pass, long timeout)
        : env_(0)
        , conn_(0)
        , connected_(false)
        , transactions_(0)
        , rollback_(false)
    {
        allocate_handle(env_, conn_);
        try
        {
            connect(dsn, user, pass, timeout);
        }
        catch (...)
        {
            NANODBC_CALL(SQLFreeHandle, SQL_HANDLE_DBC, conn_);
            NANODBC_CALL(SQLFreeHandle, SQL_HANDLE_ENV, env_);
            throw;
        }
    }

    connection_impl(const string& connection_string, long timeout)
        : env_(0)
        , conn_(0)
        , connected_(false)
        , transactions_(0)
        , rollback_(false)
    {
        allocate_handle(env_, conn_);
        try
        {
            connect(connection_string, timeout);
        }
        catch (...)
        {
            NANODBC_CALL(SQLFreeHandle, SQL_HANDLE_DBC, conn_);
            NANODBC_CALL(SQLFreeHandle, SQL_HANDLE_ENV, env_);
            throw;
        }
    }

    ~connection_impl() NANODBC_NOEXCEPT
    {
        try
        {
            disconnect();
        }
        catch (...)
        {
            // ignore exceptions thrown during disconnect
        }
        NANODBC_CALL(SQLFreeHandle, SQL_HANDLE_DBC, conn_);
        NANODBC_CALL(SQLFreeHandle, SQL_HANDLE_ENV, env_);
    }

#if !defined(NANODBC_DISABLE_ASYNC) && defined(SQL_ATTR_ASYNC_DBC_EVENT)
    void enable_async(void* event_handle)
    {
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLSetConnectAttr,
            rc,
            conn_,
            SQL_ATTR_ASYNC_DBC_FUNCTIONS_ENABLE,
            (SQLPOINTER)SQL_ASYNC_DBC_ENABLE_ON,
            SQL_IS_INTEGER);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        NANODBC_CALL_RC(
            SQLSetConnectAttr, rc, conn_, SQL_ATTR_ASYNC_DBC_EVENT, event_handle, SQL_IS_POINTER);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);
    }

    void async_complete()
    {
        RETCODE rc, arc;
        NANODBC_CALL_RC(SQLCompleteAsync, rc, SQL_HANDLE_DBC, conn_, &arc);
        if (!success(rc) || !success(arc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        connected_ = true;

        NANODBC_CALL_RC(
            SQLSetConnectAttr,
            rc,
            conn_,
            SQL_ATTR_ASYNC_DBC_FUNCTIONS_ENABLE,
            (SQLPOINTER)SQL_ASYNC_DBC_ENABLE_OFF,
            SQL_IS_INTEGER);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);
    }
#endif // !NANODBC_DISABLE_ASYNC && SQL_ATTR_ASYNC_DBC_EVENT

    RETCODE connect(
        const string& dsn,
        const string& user,
        const string& pass,
        long timeout,
        void* event_handle = nullptr)
    {
        disconnect();

        RETCODE rc;
        NANODBC_CALL_RC(SQLFreeHandle, rc, SQL_HANDLE_DBC, conn_);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        NANODBC_CALL_RC(SQLAllocHandle, rc, SQL_HANDLE_DBC, env_, &conn_);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(env_, SQL_HANDLE_ENV);

        NANODBC_CALL_RC(
            SQLSetConnectAttr, rc, conn_, SQL_LOGIN_TIMEOUT, (SQLPOINTER)(std::intptr_t)timeout, 0);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

#if !defined(NANODBC_DISABLE_ASYNC) && defined(SQL_ATTR_ASYNC_DBC_EVENT)
        if (event_handle != nullptr)
            enable_async(event_handle);
#endif

        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLConnect),
            rc,
            conn_,
            (NANODBC_SQLCHAR*)dsn.c_str(),
            SQL_NTS,
            !user.empty() ? (NANODBC_SQLCHAR*)user.c_str() : 0,
            SQL_NTS,
            !pass.empty() ? (NANODBC_SQLCHAR*)pass.c_str() : 0,
            SQL_NTS);
        if (!success(rc) && (event_handle == nullptr || rc != SQL_STILL_EXECUTING))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        connected_ = success(rc);

        return rc;
    }

    RETCODE
    connect(const string& connection_string, long timeout, void* event_handle = nullptr)
    {
        disconnect();

        RETCODE rc;
        NANODBC_CALL_RC(SQLFreeHandle, rc, SQL_HANDLE_DBC, conn_);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        NANODBC_CALL_RC(SQLAllocHandle, rc, SQL_HANDLE_DBC, env_, &conn_);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(env_, SQL_HANDLE_ENV);

        NANODBC_CALL_RC(
            SQLSetConnectAttr, rc, conn_, SQL_LOGIN_TIMEOUT, (SQLPOINTER)(std::intptr_t)timeout, 0);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

#if !defined(NANODBC_DISABLE_ASYNC) && defined(SQL_ATTR_ASYNC_DBC_EVENT)
        if (event_handle != nullptr)
            enable_async(event_handle);
#endif

        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLDriverConnect),
            rc,
            conn_,
            0,
            (NANODBC_SQLCHAR*)connection_string.c_str(),
            SQL_NTS,
            nullptr,
            0,
            nullptr,
            SQL_DRIVER_NOPROMPT);
        if (!success(rc) && (event_handle == nullptr || rc != SQL_STILL_EXECUTING))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        connected_ = success(rc);

        return rc;
    }

    bool connected() const { return connected_; }

    void disconnect()
    {
        if (connected())
        {
            RETCODE rc;
            NANODBC_CALL_RC(SQLDisconnect, rc, conn_);
            if (!success(rc))
                NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);
        }
        connected_ = false;
    }

    std::size_t transactions() const { return transactions_; }

    void* native_dbc_handle() const { return conn_; }

    void* native_env_handle() const { return env_; }

    template <class T>
    T get_info(short info_type) const
    {
        return get_info_impl<T>(info_type);
    }
    string dbms_name() const;

    string dbms_version() const;

    string driver_name() const;

    string database_name() const;

    string catalog_name() const
    {
        NANODBC_SQLCHAR name[SQL_MAX_OPTION_STRING_LENGTH] = {0};
        SQLINTEGER length(0);
        RETCODE rc;
        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLGetConnectAttr),
            rc,
            conn_,
            SQL_ATTR_CURRENT_CATALOG,
            name,
            sizeof(name) / sizeof(NANODBC_SQLCHAR),
            &length);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);
        return string(&name[0], &name[strarrlen(name)]);
    }

    std::size_t ref_transaction() { return ++transactions_; }

    std::size_t unref_transaction()
    {
        if (transactions_ > 0)
            --transactions_;
        return transactions_;
    }

    bool rollback() const { return rollback_; }

    void rollback(bool onoff) { rollback_ = onoff; }

private:
    template <class T>
    T get_info_impl(short info_type) const;

    HENV env_;
    HDBC conn_;
    bool connected_;
    std::size_t transactions_;
    bool rollback_; // if true, this connection is marked for eventual transaction rollback
};

template <class T>
T connection::connection_impl::get_info_impl(short info_type) const
{
    T value;
    RETCODE rc;
    NANODBC_CALL_RC(NANODBC_FUNC(SQLGetInfo), rc, conn_, info_type, &value, 0, nullptr);
    if (!success(rc))
        NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);
    return value;
}

template <>
string connection::connection_impl::get_info_impl<string>(short info_type) const
{
    NANODBC_SQLCHAR value[1024] = {0};
    SQLSMALLINT length(0);
    RETCODE rc;
    NANODBC_CALL_RC(
        NANODBC_FUNC(SQLGetInfo),
        rc,
        conn_,
        info_type,
        value,
        sizeof(value) / sizeof(NANODBC_SQLCHAR),
        &length);
    if (!success(rc))
        NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);
    return string(&value[0], &value[strarrlen(value)]);
}

string connection::connection_impl::dbms_name() const
{
    return get_info<string>(SQL_DBMS_NAME);
}

string connection::connection_impl::dbms_version() const
{
    return get_info<string>(SQL_DBMS_VER);
}

string connection::connection_impl::driver_name() const
{
    return get_info<string>(SQL_DRIVER_NAME);
}

string connection::connection_impl::database_name() const
{
    return get_info<string>(SQL_DATABASE_NAME);
}

template string connection::get_info(short info_type) const;
template unsigned short connection::get_info(short info_type) const;
template uint32_t connection::get_info(short info_type) const;
template uint64_t connection::get_info(short info_type) const;

} // namespace nanodbc

// clang-format off
// 88888888888                                                  888    d8b                             8888888                        888
//     888                                                      888    Y8P                               888                          888
//     888                                                      888                                      888                          888
//     888  888d888 8888b.  88888b.  .d8888b   8888b.   .d8888b 888888 888  .d88b.  88888b.              888   88888b.d88b.  88888b.  888
//     888  888P"      "88b 888 "88b 88K          "88b d88P"    888    888 d88""88b 888 "88b             888   888 "888 "88b 888 "88b 888
//     888  888    .d888888 888  888 "Y8888b. .d888888 888      888    888 888  888 888  888             888   888  888  888 888  888 888
//     888  888    888  888 888  888      X88 888  888 Y88b.    Y88b.  888 Y88..88P 888  888             888   888  888  888 888 d88P 888
//     888  888    "Y888888 888  888  88888P' "Y888888  "Y8888P  "Y888 888  "Y88P"  888  888           8888888 888  888  888 88888P"  888
//                                                                                                                           888
//                                                                                                                           888
//                                                                                                                           888
// MARK: Transaction Impl -
// clang-format on

namespace nanodbc
{

class transaction::transaction_impl
{
public:
    transaction_impl(const transaction_impl&) = delete;
    transaction_impl& operator=(const transaction_impl&) = delete;

    transaction_impl(const class connection& conn)
        : conn_(conn)
        , committed_(false)
    {
        if (conn_.transactions() == 0 && conn_.connected())
        {
            RETCODE rc;
            NANODBC_CALL_RC(
                SQLSetConnectAttr,
                rc,
                conn_.native_dbc_handle(),
                SQL_ATTR_AUTOCOMMIT,
                (SQLPOINTER)SQL_AUTOCOMMIT_OFF,
                SQL_IS_UINTEGER);
            if (!success(rc))
                NANODBC_THROW_DATABASE_ERROR(conn_.native_dbc_handle(), SQL_HANDLE_DBC);
        }
        conn_.ref_transaction();
    }

    ~transaction_impl() NANODBC_NOEXCEPT
    {
        if (!committed_)
        {
            conn_.rollback(true);
            conn_.unref_transaction();
        }

        if (conn_.transactions() == 0 && conn_.connected())
        {
            if (conn_.rollback())
            {
                NANODBC_CALL(SQLEndTran, SQL_HANDLE_DBC, conn_.native_dbc_handle(), SQL_ROLLBACK);
                conn_.rollback(false);
            }

            NANODBC_CALL(
                SQLSetConnectAttr,
                conn_.native_dbc_handle(),
                SQL_ATTR_AUTOCOMMIT,
                (SQLPOINTER)SQL_AUTOCOMMIT_ON,
                SQL_IS_UINTEGER);
        }
    }

    void commit()
    {
        if (committed_)
            return;
        committed_ = true;
        if (conn_.unref_transaction() == 0 && conn_.connected())
        {
            RETCODE rc;
            NANODBC_CALL_RC(SQLEndTran, rc, SQL_HANDLE_DBC, conn_.native_dbc_handle(), SQL_COMMIT);
            if (!success(rc))
                NANODBC_THROW_DATABASE_ERROR(conn_.native_dbc_handle(), SQL_HANDLE_DBC);
        }
    }

    void rollback() NANODBC_NOEXCEPT
    {
        if (committed_)
            return;
        conn_.rollback(true);
    }

    class connection& connection() { return conn_; }

    const class connection& connection() const { return conn_; }

private:
    class connection conn_;
    bool committed_;
};

} // namespace nanodbc

// clang-format off
//  .d8888b.  888             888                                            888              8888888                        888
// d88P  Y88b 888             888                                            888                888                          888
// Y88b.      888             888                                            888                888                          888
//  "Y888b.   888888  8888b.  888888 .d88b.  88888b.d88b.   .d88b.  88888b.  888888             888   88888b.d88b.  88888b.  888
//     "Y88b. 888        "88b 888   d8P  Y8b 888 "888 "88b d8P  Y8b 888 "88b 888                888   888 "888 "88b 888 "88b 888
//       "888 888    .d888888 888   88888888 888  888  888 88888888 888  888 888                888   888  888  888 888  888 888
// Y88b  d88P Y88b.  888  888 Y88b. Y8b.     888  888  888 Y8b.     888  888 Y88b.              888   888  888  888 888 d88P 888
//  "Y8888P"   "Y888 "Y888888  "Y888 "Y8888  888  888  888  "Y8888  888  888  "Y888           8888888 888  888  888 88888P"  888
//                                                                                                                  888
//                                                                                                                  888
//                                                                                                                  888
// MARK: Statement Impl -
// clang-format on

namespace nanodbc
{

class statement::statement_impl
{
public:
    statement_impl(const statement_impl&) = delete;
    statement_impl& operator=(const statement_impl&) = delete;

    statement_impl()
        : stmt_(0)
        , open_(false)
        , conn_()
        , bind_len_or_null_()
#if defined(NANODBC_DO_ASYNC_IMPL)
        , async_(false)
        , async_enabled_(false)
        , async_event_(nullptr)
#endif
    {
    }

    statement_impl(class connection& conn)
        : stmt_(0)
        , open_(false)
        , conn_()
        , bind_len_or_null_()
        , string_data_()
        , binary_data_()
#if defined(NANODBC_DO_ASYNC_IMPL)
        , async_(false)
        , async_enabled_(false)
        , async_event_(nullptr)
#endif
    {
        open(conn);
    }

    statement_impl(class connection& conn, const string& query, long timeout)
        : stmt_(0)
        , open_(false)
        , conn_()
        , bind_len_or_null_()
        , string_data_()
        , binary_data_()
#if defined(NANODBC_DO_ASYNC_IMPL)
        , async_(false)
        , async_enabled_(false)
        , async_event_(nullptr)
#endif
    {
        prepare(conn, query, timeout);
    }

    ~statement_impl() NANODBC_NOEXCEPT
    {
        if (open() && connected())
        {
            NANODBC_CALL(SQLCancel, stmt_);
            reset_parameters();
            NANODBC_CALL(SQLFreeHandle, SQL_HANDLE_STMT, stmt_);
        }
    }

    void open(class connection& conn)
    {
        close();
        RETCODE rc;
        NANODBC_CALL_RC(SQLAllocHandle, rc, SQL_HANDLE_STMT, conn.native_dbc_handle(), &stmt_);
        open_ = success(rc);
        if (!open_)
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        conn_ = conn;
    }

    bool open() const { return open_; }

    bool connected() const { return conn_.connected(); }

    const class connection& connection() const { return conn_; }

    class connection& connection() { return conn_; }

    void* native_statement_handle() const { return stmt_; }

    void close()
    {
        if (open() && connected())
        {
            RETCODE rc;
            NANODBC_CALL_RC(SQLCancel, rc, stmt_);
            if (!success(rc))
                NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

            reset_parameters();

            NANODBC_CALL_RC(SQLFreeHandle, rc, SQL_HANDLE_STMT, stmt_);
            if (!success(rc))
                NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        }

        open_ = false;
        stmt_ = 0;
    }

    void cancel()
    {
        RETCODE rc;
        NANODBC_CALL_RC(SQLCancel, rc, stmt_);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
    }

    void prepare(class connection& conn, const string& query, long timeout)
    {
        open(conn);
        prepare(query, timeout);
    }

    RETCODE prepare(const string& query, long timeout, void* event_handle = nullptr)
    {
        if (!open())
            throw programming_error("statement has no associated open connection");

#if defined(NANODBC_DO_ASYNC_IMPL)
        if (event_handle == nullptr)
            disable_async();
        else
            enable_async(event_handle);
#endif

        RETCODE rc;
        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLPrepare),
            rc,
            stmt_,
            (NANODBC_SQLCHAR*)query.c_str(),
            (SQLINTEGER)query.size());
        if (!success(rc) && rc != SQL_STILL_EXECUTING)
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        this->timeout(timeout);

        return rc;
    }

    void timeout(long timeout)
    {
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLSetStmtAttr,
            rc,
            stmt_,
            SQL_ATTR_QUERY_TIMEOUT,
            (SQLPOINTER)(std::intptr_t)timeout,
            0);

        // some drivers don't support timeout for statements,
        // so only raise the error if a non-default timeout was requested.
        if (!success(rc) && (timeout != 0))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
    }

#if defined(NANODBC_DO_ASYNC_IMPL)
    void enable_async(void* event_handle)
    {
        RETCODE rc;
        if (!async_enabled_)
        {
            NANODBC_CALL_RC(
                SQLSetStmtAttr,
                rc,
                stmt_,
                SQL_ATTR_ASYNC_ENABLE,
                (SQLPOINTER)SQL_ASYNC_ENABLE_ON,
                SQL_IS_INTEGER);
            if (!success(rc))
                NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
            async_enabled_ = true;
        }

        if (async_event_ != event_handle)
        {
            NANODBC_CALL_RC(
                SQLSetStmtAttr, rc, stmt_, SQL_ATTR_ASYNC_STMT_EVENT, event_handle, SQL_IS_POINTER);
            if (!success(rc))
                NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
            async_event_ = event_handle;
        }
    }

    void disable_async() const
    {
        if (async_enabled_)
        {
            RETCODE rc;
            NANODBC_CALL_RC(
                SQLSetStmtAttr,
                rc,
                stmt_,
                SQL_ATTR_ASYNC_ENABLE,
                (SQLPOINTER)SQL_ASYNC_ENABLE_OFF,
                SQL_IS_INTEGER);
            if (!success(rc))
                NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
            async_enabled_ = false;
        }
    }

    bool async_helper(RETCODE rc)
    {
        if (rc == SQL_STILL_EXECUTING)
        {
            async_ = true;
            return true;
        }
        else if (success(rc))
        {
            async_ = false;
            return false;
        }
        else
        {
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        }
    }

    bool async_prepare(const string& query, void* event_handle, long timeout)
    {
        return async_helper(prepare(query, timeout, event_handle));
    }

    bool async_execute_direct(
        class connection& conn,
        void* event_handle,
        const string& query,
        long batch_operations,
        long timeout,
        statement& statement)
    {
        return async_helper(
            just_execute_direct(conn, query, batch_operations, timeout, statement, event_handle));
    }

    bool
    async_execute(void* event_handle, long batch_operations, long timeout, statement& statement)
    {
        return async_helper(just_execute(batch_operations, timeout, statement, event_handle));
    }

    void call_complete_async()
    {
        if (async_)
        {
            RETCODE rc, arc;
            NANODBC_CALL_RC(SQLCompleteAsync, rc, SQL_HANDLE_STMT, stmt_, &arc);
            if (!success(rc) || !success(arc))
                NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        }
    }

    result complete_execute(long batch_operations, statement& statement)
    {
        call_complete_async();

        return result(statement, batch_operations);
    }

    void complete_prepare() { call_complete_async(); }

#endif
    result execute_direct(
        class connection& conn,
        const string& query,
        long batch_operations,
        long timeout,
        statement& statement)
    {
#ifdef NANODBC_ENABLE_WORKAROUND_NODATA
        const RETCODE rc = just_execute_direct(conn, query, batch_operations, timeout, statement);
        if (rc == SQL_NO_DATA)
            return result();
#else
        just_execute_direct(conn, query, batch_operations, timeout, statement);
#endif
        return result(statement, batch_operations);
    }

    RETCODE just_execute_direct(
        class connection& conn,
        const string& query,
        long batch_operations,
        long timeout,
        statement&, // statement
        void* event_handle = nullptr)
    {
        open(conn);

#if defined(NANODBC_DO_ASYNC_IMPL)
        if (event_handle == nullptr)
            disable_async();
        else
            enable_async(event_handle);
#endif

        RETCODE rc;
        NANODBC_CALL_RC(
            SQLSetStmtAttr,
            rc,
            stmt_,
            SQL_ATTR_PARAMSET_SIZE,
            (SQLPOINTER)(std::intptr_t)batch_operations,
            0);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        this->timeout(timeout);

        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLExecDirect), rc, stmt_, (NANODBC_SQLCHAR*)query.c_str(), SQL_NTS);
        if (!success(rc) && rc != SQL_NO_DATA && rc != SQL_STILL_EXECUTING)
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        return rc;
    }

    result execute(long batch_operations, long timeout, statement& statement)
    {
#ifdef NANODBC_ENABLE_WORKAROUND_NODATA
        const RETCODE rc = just_execute(batch_operations, timeout, statement);
        if (rc == SQL_NO_DATA)
            return result();
#else
        just_execute(batch_operations, timeout, statement);
#endif
        return result(statement, batch_operations);
    }

    RETCODE just_execute(
        long batch_operations,
        long timeout,
        statement& /*statement*/,
        void* event_handle = nullptr)
    {
        RETCODE rc;

        if (open())
        {
            // The ODBC cursor must be closed before subsequent executions, as described
            // here
            // http://msdn.microsoft.com/en-us/library/windows/desktop/ms713584%28v=vs.85%29.aspx
            //
            // However, we don't necessarily want to call SQLCloseCursor() because that
            // will cause an invalid cursor state in the case that no cursor is currently open.
            // A better solution is to use SQLFreeStmt() with the SQL_CLOSE option, which has
            // the same effect without the undesired limitations.
            NANODBC_CALL_RC(SQLFreeStmt, rc, stmt_, SQL_CLOSE);
            if (!success(rc))
                NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        }

#if defined(NANODBC_DO_ASYNC_IMPL)
        if (event_handle == nullptr)
            disable_async();
        else
            enable_async(event_handle);
#endif

        NANODBC_CALL_RC(
            SQLSetStmtAttr,
            rc,
            stmt_,
            SQL_ATTR_PARAMSET_SIZE,
            (SQLPOINTER)(std::intptr_t)batch_operations,
            0);
        if (!success(rc) && rc != SQL_NO_DATA)
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        this->timeout(timeout);

        NANODBC_CALL_RC(SQLExecute, rc, stmt_);
        if (!success(rc) && rc != SQL_NO_DATA && rc != SQL_STILL_EXECUTING)
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        return rc;
    }

    result procedure_columns(
        const string& catalog,
        const string& schema,
        const string& procedure,
        const string& column,
        statement& statement)
    {
        if (!open())
            throw programming_error("statement has no associated open connection");

#if defined(NANODBC_DO_ASYNC_IMPL)
        disable_async();
#endif

        RETCODE rc;
        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLProcedureColumns),
            rc,
            stmt_,
            (NANODBC_SQLCHAR*)(catalog.empty() ? nullptr : catalog.c_str()),
            (catalog.empty() ? 0 : SQL_NTS),
            (NANODBC_SQLCHAR*)(schema.empty() ? nullptr : schema.c_str()),
            (schema.empty() ? 0 : SQL_NTS),
            (NANODBC_SQLCHAR*)procedure.c_str(),
            SQL_NTS,
            (NANODBC_SQLCHAR*)(column.empty() ? nullptr : column.c_str()),
            (column.empty() ? 0 : SQL_NTS));

        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        return result(statement, 1);
    }

    long affected_rows() const
    {
        SQLLEN rows;
        RETCODE rc;
        NANODBC_CALL_RC(SQLRowCount, rc, stmt_, &rows);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        NANODBC_ASSERT(rows <= static_cast<SQLLEN>(std::numeric_limits<long>::max()));
        return static_cast<long>(rows);
    }

    short columns() const
    {
        SQLSMALLINT cols;
        RETCODE rc;

#if defined(NANODBC_DO_ASYNC_IMPL)
        disable_async();
#endif

        NANODBC_CALL_RC(SQLNumResultCols, rc, stmt_, &cols);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        return cols;
    }

    void reset_parameters() NANODBC_NOEXCEPT { NANODBC_CALL(SQLFreeStmt, stmt_, SQL_RESET_PARAMS); }

    short parameters() const
    {
        SQLSMALLINT params;
        RETCODE rc;

#if defined(NANODBC_DO_ASYNC_IMPL)
        disable_async();
#endif

        NANODBC_CALL_RC(SQLNumParams, rc, stmt_, &params);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        return params;
    }

    unsigned long parameter_size(short param_index) const
    {
        RETCODE rc;
        SQLSMALLINT data_type;
        SQLSMALLINT nullable;
        SQLULEN parameter_size;

#if defined(NANODBC_DO_ASYNC_IMPL)
        disable_async();
#endif

        NANODBC_CALL_RC(
            SQLDescribeParam,
            rc,
            stmt_,
            param_index + 1,
            &data_type,
            &parameter_size,
            0,
            &nullable);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        NANODBC_ASSERT(
            parameter_size < static_cast<SQLULEN>(std::numeric_limits<unsigned long>::max()));
        return static_cast<unsigned long>(parameter_size);
    }

    static SQLSMALLINT param_type_from_direction(param_direction direction)
    {
        switch (direction)
        {
        case PARAM_IN:
            return SQL_PARAM_INPUT;
            break;
        case PARAM_OUT:
            return SQL_PARAM_OUTPUT;
            break;
        case PARAM_INOUT:
            return SQL_PARAM_INPUT_OUTPUT;
            break;
        case PARAM_RETURN:
            return SQL_PARAM_OUTPUT;
            break;
        default:
            NANODBC_ASSERT(false);
            throw programming_error("unrecognized param_direction value");
        }
    }

    // initializes bind_len_or_null_ and gets information for bind
    void prepare_bind(
        short param_index,
        std::size_t batch_size,
        param_direction direction,
        bound_parameter& param)
    {
        NANODBC_ASSERT(param_index >= 0);

#if defined(NANODBC_DO_ASYNC_IMPL)
        disable_async();
#endif

        RETCODE rc;
        SQLSMALLINT nullable; // unused
        NANODBC_CALL_RC(
            SQLDescribeParam,
            rc,
            stmt_,
            param_index + 1,
            &param.type_,
            &param.size_,
            &param.scale_,
            &nullable);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        param.index_ = param_index;
        param.iotype_ = param_type_from_direction(direction);

        if (!bind_len_or_null_.count(param_index))
            bind_len_or_null_[param_index] = std::vector<null_type>();
        std::vector<null_type>().swap(bind_len_or_null_[param_index]);

        // ODBC weirdness: this must be at least 8 elements in size
        const std::size_t indicator_size = batch_size > 8 ? batch_size : 8;
        bind_len_or_null_[param_index].reserve(indicator_size);
        bind_len_or_null_[param_index].assign(indicator_size, SQL_NULL_DATA);

        NANODBC_ASSERT(param.index_ == param_index);
        NANODBC_ASSERT(param.iotype_ > 0);
    }

    // calls actual ODBC bind parameter function
    template <class T>
    void bind_parameter(bound_parameter const& param, bound_buffer<T>& buffer)
    {
        auto const buffer_size = buffer.value_size_ > 0 ? buffer.value_size_ : param.size_;

        RETCODE rc;
        NANODBC_CALL_RC(
            SQLBindParameter,
            rc,
            stmt_,               // handle
            param.index_ + 1,    // parameter number
            param.iotype_,       // input or output type
            sql_ctype<T>::value, // value type
            param.type_,         // parameter type
            param.size_,         // column size ignored for many types, but needed for strings
            param.scale_,        // decimal digits
            (SQLPOINTER)buffer.values_, // parameter value
            buffer_size,                // buffer length
            bind_len_or_null_[param.index_].data());

        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
    }

    template <class T>
    void bind(
        param_direction direction,
        short param_index,
        T const* values,
        std::size_t batch_size,
        bool const* nulls = nullptr,
        T const* null_sentry = nullptr);

    // handles multiple binary values
    void bind(
        param_direction direction,
        short param_index,
        std::vector<std::vector<uint8_t>> const& values,
        bool const* nulls = nullptr,
        uint8_t const* null_sentry = nullptr)
    {
        std::size_t batch_size = values.size();
        bound_parameter param;
        prepare_bind(param_index, batch_size, direction, param);

        size_t max_length = 0;
        for (std::size_t i = 0; i < batch_size; ++i)
        {
            max_length = std::max(values[i].size(), max_length);
        }
        binary_data_[param_index] = std::vector<uint8_t>(batch_size * max_length, 0);
        for (std::size_t i = 0; i < batch_size; ++i)
        {
            std::copy(
                values[i].begin(),
                values[i].end(),
                binary_data_[param_index].data() + (i * max_length));
        }

        if (null_sentry)
        {
            for (std::size_t i = 0; i < batch_size; ++i)
                if (!std::equal(values[i].begin(), values[i].end(), null_sentry))
                {
                    bind_len_or_null_[param_index][i] = values[i].size();
                }
        }
        else if (nulls)
        {
            for (std::size_t i = 0; i < batch_size; ++i)
            {
                if (!nulls[i])
                    bind_len_or_null_[param_index][i] = values[i].size(); // null terminated
            }
        }
        else
        {
            for (std::size_t i = 0; i < batch_size; ++i)
            {
                bind_len_or_null_[param_index][i] = values[i].size();
            }
        }
        bound_buffer<uint8_t> buffer(binary_data_[param_index].data(), batch_size, max_length);
        bind_parameter(param, buffer);
    }

    void bind_strings(
        param_direction direction,
        short param_index,
        string::value_type const* values,
        std::size_t value_size,
        std::size_t batch_size,
        bool const* nulls = nullptr,
        string::value_type const* null_sentry = nullptr);

    void bind_strings(
        param_direction direction,
        short param_index,
        std::vector<string> const& values,
        bool const* nulls = nullptr,
        string::value_type const* null_sentry = nullptr);

    // handles multiple null values
    void bind_null(short param_index, std::size_t batch_size)
    {
        bound_parameter param;
        prepare_bind(param_index, batch_size, PARAM_IN, param);

        RETCODE rc;
        NANODBC_CALL_RC(
            SQLBindParameter,
            rc,
            stmt_,
            param.index_ + 1, // parameter number
            param.iotype_,    // input or output typ,
            SQL_C_CHAR,
            param.type_, // parameter type
            param.size_, // column size ignored for many types, but needed for string,
            0,           // decimal digits
            nullptr,     // null value
            0,           // buffe length
            bind_len_or_null_[param.index_].data());
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
    }

    // comparator for null sentry values
    template <class T>
    bool equals(const T& lhs, const T& rhs)
    {
        return lhs == rhs;
    }

private:
    HSTMT stmt_;
    bool open_;
    class connection conn_;
    std::map<short, std::vector<null_type>> bind_len_or_null_;
    std::map<short, std::vector<string::value_type>> string_data_;
    std::map<short, std::vector<uint8_t>> binary_data_;

#if defined(NANODBC_DO_ASYNC_IMPL)
    bool async_;                 // true if statement is currently in SQL_STILL_EXECUTING mode
    mutable bool async_enabled_; // true if statement currently has SQL_ATTR_ASYNC_ENABLE =
                                 // SQL_ASYNC_ENABLE_ON
    void* async_event_;          // currently active event handle for async notifications
#endif
};

// Supports code like: query.bind(0, std_string.c_str())
// In this case, we need to pass nullptr to the final parameter of SQLBindParameter().
template <>
void statement::statement_impl::bind_parameter<string::value_type>(
    bound_parameter const& param,
    bound_buffer<string::value_type>& buffer)
{
    auto const buffer_size = buffer.value_size_ > 0 ? buffer.value_size_ : param.size_;

    RETCODE rc;
    NANODBC_CALL_RC(
        SQLBindParameter,
        rc,
        stmt_,                                // handle
        param.index_ + 1,                     // parameter number
        param.iotype_,                        // input or output type
        sql_ctype<string::value_type>::value, // value type
        param.type_,                          // parameter type
        param.size_,                // column size ignored for many types, but needed for strings
        param.scale_,               // decimal digits
        (SQLPOINTER)buffer.values_, // parameter value
        buffer_size,                // buffer length
        (buffer.size_ <= 1 ? nullptr : bind_len_or_null_[param.index_].data()));

    if (!success(rc))
        NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
}

template <class T>
void statement::statement_impl::bind(
    param_direction direction,
    short param_index,
    T const* values,
    std::size_t batch_size,
    bool const* nulls /*= nullptr*/,
    T const* null_sentry /*= nullptr*/)
{
    bound_parameter param;
    prepare_bind(param_index, batch_size, direction, param);

    if (nulls || null_sentry)
    {
        for (std::size_t i = 0; i < batch_size; ++i)
            if ((null_sentry && !equals(values[i], *null_sentry)) || (nulls && !nulls[i]) || !nulls)
                bind_len_or_null_[param_index][i] = param.size_;
    }
    else
    {
        for (std::size_t i = 0; i < batch_size; ++i)
            bind_len_or_null_[param_index][i] = param.size_;
    }

    bound_buffer<T> buffer(values, batch_size);
    bind_parameter(param, buffer);
}

void statement::statement_impl::bind_strings(
    param_direction direction,
    short param_index,
    std::vector<string> const& values,
    bool const* nulls /*= nullptr*/,
    string::value_type const* null_sentry /*= nullptr*/)
{

    size_t const batch_size = values.size();
    bound_parameter param;
    prepare_bind(param_index, batch_size, direction, param);

    size_t max_length = 0;
    for (std::size_t i = 0; i < batch_size; ++i)
    {
        max_length = std::max(values[i].length(), max_length);
    }
    // add space for null terminator
    ++max_length;

    string_data_[param_index] = std::vector<string::value_type>(batch_size * max_length, 0);
    for (std::size_t i = 0; i < batch_size; ++i)
    {
        std::copy(
            values[i].begin(),
            values[i].end(),
            string_data_[param_index].data() + (i * max_length));
    }
    bind_strings(
        direction,
        param_index,
        string_data_[param_index].data(),
        max_length,
        batch_size,
        nulls,
        null_sentry);
}

void statement::statement_impl::bind_strings(
    param_direction direction,
    short param_index,
    string::value_type const* values,
    std::size_t value_size,
    std::size_t batch_size,
    bool const* nulls /*= nullptr*/,
    string::value_type const* null_sentry /*= nullptr*/)
{
    bound_parameter param;
    prepare_bind(param_index, batch_size, direction, param);

    if (null_sentry)
    {
        for (std::size_t i = 0; i < batch_size; ++i)
        {
            const string s_lhs(values + i * value_size, values + (i + 1) * value_size);
            const string s_rhs(null_sentry);
#if NANODBC_ENABLE_UNICODE
            std::string narrow_lhs;
            narrow_lhs.reserve(s_lhs.size());
            convert(s_lhs, narrow_lhs);
            std::string narrow_rhs;
            narrow_rhs.reserve(s_rhs.size());
            convert(s_rhs, narrow_rhs);
            if (std::strncmp(narrow_lhs.c_str(), narrow_rhs.c_str(), value_size) != 0)
                bind_len_or_null_[param_index][i] = SQL_NTS;
#else
            if (std::strncmp(s_lhs.c_str(), s_rhs.c_str(), value_size) != 0)
                bind_len_or_null_[param_index][i] = SQL_NTS;
#endif
        }
    }
    else if (nulls)
    {
        for (std::size_t i = 0; i < batch_size; ++i)
        {
            if (!nulls[i])
                bind_len_or_null_[param_index][i] = SQL_NTS; // null terminated
        }
    }
    else
    {
        for (std::size_t i = 0; i < batch_size; ++i)
        {
            bind_len_or_null_[param_index][i] = SQL_NTS;
        }
    }

    auto const buffer_length = value_size * sizeof(string::value_type);
    bound_buffer<string::value_type> buffer(values, batch_size, buffer_length);
    bind_parameter(param, buffer);
}

template <>
bool statement::statement_impl::equals(const date& lhs, const date& rhs)
{
    return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

template <>
bool statement::statement_impl::equals(const time& lhs, const time& rhs)
{
    return lhs.hour == rhs.hour && lhs.min == rhs.min && lhs.sec == rhs.sec;
}

template <>
bool statement::statement_impl::equals(const timestamp& lhs, const timestamp& rhs)
{
    return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day &&
           lhs.hour == rhs.hour && lhs.min == rhs.min && lhs.sec == rhs.sec &&
           lhs.fract == rhs.fract;
}

} // namespace nanodbc

// clang-format off
// 8888888b.                            888 888              8888888                        888
// 888   Y88b                           888 888                888                          888
// 888    888                           888 888                888                          888
// 888   d88P .d88b.  .d8888b  888  888 888 888888             888   88888b.d88b.  88888b.  888
// 8888888P" d8P  Y8b 88K      888  888 888 888                888   888 "888 "88b 888 "88b 888
// 888 T88b  88888888 "Y8888b. 888  888 888 888                888   888  888  888 888  888 888
// 888  T88b Y8b.          X88 Y88b 888 888 Y88b.              888   888  888  888 888 d88P 888
// 888   T88b "Y8888   88888P'  "Y88888 888  "Y888           8888888 888  888  888 88888P"  888
//                                                                                 888
//                                                                                 888
//                                                                                 888
// MARK: Result Impl -
// clang-format on

namespace nanodbc
{

class result::result_impl
{
public:
    result_impl(const result_impl&) = delete;
    result_impl& operator=(const result_impl&) = delete;

    result_impl(statement stmt, long rowset_size)
        : stmt_(stmt)
        , rowset_size_(rowset_size)
        , row_count_(0)
        , bound_columns_(0)
        , bound_columns_size_(0)
        , rowset_position_(0)
        , bound_columns_by_name_()
        , at_end_(false)
#if defined(NANODBC_DO_ASYNC_IMPL)
        , async_(false)
#endif
    {
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLSetStmtAttr,
            rc,
            stmt_.native_statement_handle(),
            SQL_ATTR_ROW_ARRAY_SIZE,
            (SQLPOINTER)(std::intptr_t)rowset_size_,
            0);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);

        NANODBC_CALL_RC(
            SQLSetStmtAttr,
            rc,
            stmt_.native_statement_handle(),
            SQL_ATTR_ROWS_FETCHED_PTR,
            &row_count_,
            0);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);

        auto_bind();
    }

    ~result_impl() NANODBC_NOEXCEPT { cleanup_bound_columns(); }

    void* native_statement_handle() const { return stmt_.native_statement_handle(); }

    long rowset_size() const { return rowset_size_; }

    long affected_rows() const { return stmt_.affected_rows(); }

    long rows() const NANODBC_NOEXCEPT
    {
        NANODBC_ASSERT(row_count_ <= static_cast<SQLULEN>(std::numeric_limits<long>::max()));
        return static_cast<long>(row_count_);
    }

    short columns() const { return stmt_.columns(); }

    bool first()
    {
        rowset_position_ = 0;
        return fetch(0, SQL_FETCH_FIRST);
    }

    bool last()
    {
        rowset_position_ = 0;
        return fetch(0, SQL_FETCH_LAST);
    }

    bool next(void* event_handle = nullptr)
    {
        if (rows() && ++rowset_position_ < rowset_size_)
            return rowset_position_ < rows();
        rowset_position_ = 0;
        return fetch(0, SQL_FETCH_NEXT, event_handle);
    }

#if defined(NANODBC_DO_ASYNC_IMPL)
    bool async_next(void* event_handle)
    {
        async_ = next(event_handle);
        return async_;
    }

    bool complete_next()
    {
        if (async_)
        {
            RETCODE rc, arc;
            NANODBC_CALL_RC(
                SQLCompleteAsync, rc, SQL_HANDLE_STMT, stmt_.native_statement_handle(), &arc);
            if (arc == SQL_NO_DATA)
            {
                at_end_ = true;
                return false;
            }
            if (!success(rc) || !success(arc))
                NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);
            async_ = false;
        }
        return !at_end_;
    }
#endif

    bool prior()
    {
        if (rows() && --rowset_position_ >= 0)
            return true;
        rowset_position_ = 0;
        return fetch(0, SQL_FETCH_PRIOR);
    }

    bool move(long row)
    {
        rowset_position_ = 0;
        return fetch(row, SQL_FETCH_ABSOLUTE);
    }

    bool skip(long rows)
    {
        rowset_position_ += rows;
        if (this->rows() && rowset_position_ < rowset_size_)
            return rowset_position_ < this->rows();
        rowset_position_ = 0;
        return fetch(rows, SQL_FETCH_RELATIVE);
    }

    unsigned long position() const
    {
        SQLULEN pos = 0; // necessary to initialize to 0
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLGetStmtAttr,
            rc,
            stmt_.native_statement_handle(),
            SQL_ATTR_ROW_NUMBER,
            &pos,
            SQL_IS_UINTEGER,
            0);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);

        // MSDN (https://msdn.microsoft.com/en-us/library/ms712631.aspx):
        // If the number of the current row cannot be determined or
        // there is no current row, the driver returns 0.
        // Otherwise, valid row number is returned, starting at 1.
        //
        // NOTE: We try to address incorrect implementation in some drivers (e.g. SQLite ODBC)
        // which instead of 0 return SQL_ROW_NUMBER_UNKNOWN(-2) .
        if (pos == 0 || pos == static_cast<SQLULEN>(SQL_ROW_NUMBER_UNKNOWN))
            return 0;

        NANODBC_ASSERT(pos < static_cast<SQLULEN>(std::numeric_limits<unsigned long>::max()));
        return static_cast<unsigned long>(pos) + rowset_position_;
    }

    bool at_end() const NANODBC_NOEXCEPT
    {
        if (at_end_)
            return true;
        SQLULEN pos = 0; // necessary to initialize to 0
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLGetStmtAttr,
            rc,
            stmt_.native_statement_handle(),
            SQL_ATTR_ROW_NUMBER,
            &pos,
            SQL_IS_UINTEGER,
            0);
        return (!success(rc) || rows() < 0 || pos - 1 > static_cast<unsigned long>(rows()));
    }

    bool is_null(short column) const
    {
        if (column >= bound_columns_size_)
            throw index_range_error();
        bound_column& col = bound_columns_[column];
        if (rowset_position_ >= rows())
            throw index_range_error();
        return col.cbdata_[static_cast<size_t>(rowset_position_)] == SQL_NULL_DATA;
    }

    bool is_null(const string& column_name) const
    {
        const short column = this->column(column_name);
        return is_null(column);
    }

    short column(const string& column_name) const
    {
        typedef std::map<string, bound_column*>::const_iterator iter;
        iter i = bound_columns_by_name_.find(column_name);
        if (i == bound_columns_by_name_.end())
            throw index_range_error();
        return i->second->column_;
    }

    string column_name(short column) const
    {
        if (column >= bound_columns_size_)
            throw index_range_error();
        return bound_columns_[column].name_;
    }

    long column_size(short column) const
    {
        if (column >= bound_columns_size_)
            throw index_range_error();
        bound_column& col = bound_columns_[column];
        NANODBC_ASSERT(col.sqlsize_ <= static_cast<SQLULEN>(std::numeric_limits<long>::max()));
        return static_cast<long>(col.sqlsize_);
    }

    int column_size(const string& column_name) const
    {
        const short column = this->column(column_name);
        return column_size(column);
    }

    int column_decimal_digits(short column) const
    {
        if (column >= bound_columns_size_)
            throw index_range_error();
        bound_column& col = bound_columns_[column];
        return col.scale_;
    }

    int column_decimal_digits(const string& column_name) const
    {
        const short column = this->column(column_name);
        bound_column& col = bound_columns_[column];
        return col.scale_;
    }

    int column_datatype(short column) const
    {
        if (column >= bound_columns_size_)
            throw index_range_error();
        bound_column& col = bound_columns_[column];
        return col.sqltype_;
    }

    int column_datatype(const string& column_name) const
    {
        const short column = this->column(column_name);
        bound_column& col = bound_columns_[column];
        return col.sqltype_;
    }

    string column_datatype_name(short column) const
    {
        if (column >= bound_columns_size_)
            throw index_range_error();

        NANODBC_SQLCHAR type_name[256] = {0};
        SQLSMALLINT len = 0; // total number of bytes
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLColAttribute,
            rc,
            stmt_.native_statement_handle(),
            column + 1,
            SQL_DESC_TYPE_NAME,
            type_name,
            sizeof(type_name) / sizeof(NANODBC_SQLCHAR),
            &len,
            nullptr);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);

        NANODBC_ASSERT(len % sizeof(NANODBC_SQLCHAR) == 0);
        len = len / sizeof(NANODBC_SQLCHAR);
        return string(type_name, type_name + len);
    }

    string column_datatype_name(const string& column_name) const
    {
        return column_datatype_name(this->column(column_name));
    }

    int column_c_datatype(short column) const
    {
        if (column >= bound_columns_size_)
            throw index_range_error();
        bound_column& col = bound_columns_[column];
        return col.ctype_;
    }

    int column_c_datatype(const string& column_name) const
    {
        const short column = this->column(column_name);
        bound_column& col = bound_columns_[column];
        return col.ctype_;
    }

    bool next_result()
    {
        RETCODE rc;

#if defined(NANODBC_DO_ASYNC_IMPL)
        stmt_.disable_async();
#endif

        NANODBC_CALL_RC(SQLMoreResults, rc, stmt_.native_statement_handle());
        if (rc == SQL_NO_DATA)
            return false;
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);
        auto_bind();
        return true;
    }

    template <class T>
    void get_ref(short column, T& result) const
    {
        if (column >= bound_columns_size_)
            throw index_range_error();
        if (is_null(column))
            throw null_access_error();
        get_ref_impl<T>(column, result);
    }

    template <class T>
    void get_ref(short column, const T& fallback, T& result) const
    {
        if (column >= bound_columns_size_)
            throw index_range_error();
        if (is_null(column))
        {
            result = fallback;
            return;
        }
        get_ref_impl<T>(column, result);
    }

    template <class T>
    void get_ref(const string& column_name, T& result) const
    {
        const short column = this->column(column_name);
        if (is_null(column))
            throw null_access_error();
        get_ref_impl<T>(column, result);
    }

    template <class T>
    void get_ref(const string& column_name, const T& fallback, T& result) const
    {
        const short column = this->column(column_name);
        if (is_null(column))
        {
            result = fallback;
            return;
        }
        get_ref_impl<T>(column, result);
    }

    template <class T>
    T get(short column) const
    {
        T result;
        get_ref(column, result);
        return result;
    }

    template <class T>
    T get(short column, const T& fallback) const
    {
        T result;
        get_ref(column, fallback, result);
        return result;
    }

    template <class T>
    T get(const string& column_name) const
    {
        T result;
        get_ref(column_name, result);
        return result;
    }

    template <class T>
    T get(const string& column_name, const T& fallback) const
    {
        T result;
        get_ref(column_name, fallback, result);
        return result;
    }

private:
    template <class T>
    void get_ref_impl(short column, T& result) const;

    void before_move() NANODBC_NOEXCEPT
    {
        for (short i = 0; i < bound_columns_size_; ++i)
        {
            bound_column& col = bound_columns_[i];
            for (std::size_t j = 0; j < static_cast<size_t>(rowset_size_); ++j)
                col.cbdata_[j] = 0;
            if (col.blob_ && col.pdata_)
                release_bound_resources(i);
        }
    }

    void release_bound_resources(short column) NANODBC_NOEXCEPT
    {
        NANODBC_ASSERT(column < bound_columns_size_);
        bound_column& col = bound_columns_[column];
        delete[] col.pdata_;
        col.pdata_ = 0;
        col.clen_ = 0;
    }

    void cleanup_bound_columns() NANODBC_NOEXCEPT
    {
        before_move();
        delete[] bound_columns_;
        bound_columns_ = nullptr;
        bound_columns_size_ = 0;
        bound_columns_by_name_.clear();
    }

    // If event_handle is specified, fetch returns true iff the statement is still executing
    bool fetch(long rows, SQLUSMALLINT orientation, void* event_handle = nullptr)
    {
        before_move();

#if defined(NANODBC_DO_ASYNC_IMPL)
        if (event_handle == nullptr)
            stmt_.disable_async();
        else
            stmt_.enable_async(event_handle);
#endif // !NANODBC_DISABLE_ASYNC && SQL_ATTR_ASYNC_STMT_EVENT && SQL_API_SQLCOMPLETEASYNC

        RETCODE rc;
        NANODBC_CALL_RC(SQLFetchScroll, rc, stmt_.native_statement_handle(), orientation, rows);
        if (rc == SQL_NO_DATA)
        {
            at_end_ = true;
            return false;
        }
#if defined(NANODBC_DO_ASYNC_IMPL)
        if (event_handle != nullptr)
            return rc == SQL_STILL_EXECUTING;
#endif
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);
        return true;
    }

    void auto_bind()
    {
        cleanup_bound_columns();

        const short n_columns = columns();
        if (n_columns < 1)
            return;

        NANODBC_ASSERT(!bound_columns_);
        NANODBC_ASSERT(!bound_columns_size_);
        bound_columns_ = new bound_column[n_columns];
        bound_columns_size_ = n_columns;

        RETCODE rc;
        NANODBC_SQLCHAR column_name[1024];
        SQLSMALLINT sqltype = 0, scale = 0, nullable = 0, len = 0;
        SQLULEN sqlsize = 0;

#if defined(NANODBC_DO_ASYNC_IMPL)
        stmt_.disable_async();
#endif

        for (SQLSMALLINT i = 0; i < n_columns; ++i)
        {
            NANODBC_CALL_RC(
                NANODBC_FUNC(SQLDescribeCol),
                rc,
                stmt_.native_statement_handle(),
                i + 1,
                (NANODBC_SQLCHAR*)column_name,
                sizeof(column_name) / sizeof(NANODBC_SQLCHAR),
                &len,
                &sqltype,
                &sqlsize,
                &scale,
                &nullable);
            if (!success(rc))
                NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);

            // Adjust the sqlsize parameter in case of "unlimited" data (varchar(max),
            // nvarchar(max)).
            bool is_blob = false;

            if (sqlsize == 0)
            {
                switch (sqltype)
                {
                case SQL_VARCHAR:
                case SQL_WVARCHAR:
                {
                    // Divide in half, due to sqlsize being 32-bit in Win32 (and 64-bit in x64)
                    // sqlsize = std::numeric_limits<int32_t>::max() / 2 - 1;
                    is_blob = true;
                }
                }
            }

            bound_column& col = bound_columns_[i];
            col.name_ = reinterpret_cast<string::value_type*>(column_name);
            col.column_ = i;
            col.sqltype_ = sqltype;
            col.sqlsize_ = sqlsize;
            col.scale_ = scale;
            bound_columns_by_name_[col.name_] = &col;

            using namespace std; // if int64_t is in std namespace (in c++11)
            switch (col.sqltype_)
            {
            case SQL_BIT:
            case SQL_TINYINT:
            case SQL_SMALLINT:
            case SQL_INTEGER:
            case SQL_BIGINT:
                col.ctype_ = SQL_C_SBIGINT;
                col.clen_ = sizeof(int64_t);
                break;
            case SQL_DOUBLE:
            case SQL_FLOAT:
            case SQL_REAL:
                col.ctype_ = SQL_C_DOUBLE;
                col.clen_ = sizeof(double);
                break;
            case SQL_DECIMAL:
            case SQL_NUMERIC:
                col.ctype_ = SQL_C_CHAR;
                // SQL column size defines number of digits without the decimal mark
                // and without minus sign which may also occur.
                // We need to adjust buffer length allow space for null-termination character
                // as well as the fractional part separator and the minus sign.
                col.clen_ = (col.sqlsize_ + 1 + 1 + 1) * sizeof(SQLCHAR);
                break;
            case SQL_DATE:
            case SQL_TYPE_DATE:
                col.ctype_ = SQL_C_DATE;
                col.clen_ = sizeof(date);
                break;
            case SQL_TIME:
            case SQL_TYPE_TIME:
            case SQL_SS_TIME2:
                col.ctype_ = SQL_C_TIME;
                col.clen_ = sizeof(time);
                break;
            case SQL_TIMESTAMP:
            case SQL_TYPE_TIMESTAMP:
            case SQL_SS_TIMESTAMPOFFSET:
                col.ctype_ = SQL_C_TIMESTAMP;
                col.clen_ = sizeof(timestamp);
                break;
            case SQL_CHAR:
            case SQL_VARCHAR:
            case SQL_NVARCHAR:
                col.ctype_ = SQL_C_CHAR;
                col.clen_ = (col.sqlsize_ + 1) * sizeof(SQLCHAR);
                if (is_blob)
                {
                    col.clen_ = 0;
                    col.blob_ = true;
                }
                break;
            case SQL_WCHAR:
            case SQL_WVARCHAR:
                col.ctype_ = SQL_C_WCHAR;
                col.clen_ = (col.sqlsize_ + 1) * sizeof(SQLWCHAR);
                if (is_blob)
                {
                    col.clen_ = 0;
                    col.blob_ = true;
                }
                break;
            case SQL_LONGVARCHAR:
                col.ctype_ = SQL_C_CHAR;
                col.blob_ = true;
                col.clen_ = 0;
                break;
            case SQL_BINARY:
            case SQL_VARBINARY:
            case SQL_LONGVARBINARY:
            case SQL_SS_UDT: // MSDN: Essentially, UDT is a varbinary type with additional metadata.
                col.ctype_ = SQL_C_BINARY;
                col.blob_ = true;
                col.clen_ = 0;
                break;
            default:
                col.ctype_ = sql_ctype<string>::value;
                col.clen_ = 128;
                break;
            }
        }

        for (SQLSMALLINT i = 0; i < n_columns; ++i)
        {
            bound_column& col = bound_columns_[i];
            col.cbdata_ = new null_type[static_cast<size_t>(rowset_size_)];
            if (col.blob_)
            {
                NANODBC_CALL_RC(
                    SQLBindCol,
                    rc,
                    stmt_.native_statement_handle(),
                    i + 1,
                    col.ctype_,
                    0,
                    0,
                    col.cbdata_);
                if (!success(rc))
                    NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);
            }
            else
            {
                col.pdata_ = new char[rowset_size_ * col.clen_];
                NANODBC_CALL_RC(
                    SQLBindCol,
                    rc,
                    stmt_.native_statement_handle(),
                    i + 1,        // ColumnNumber
                    col.ctype_,   // TargetType
                    col.pdata_,   // TargetValuePtr
                    col.clen_,    // BufferLength
                    col.cbdata_); // StrLen_or_Ind
                if (!success(rc))
                    NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);
            }
        }
    }

private:
    statement stmt_;
    const long rowset_size_;
    SQLULEN row_count_;
    bound_column* bound_columns_;
    short bound_columns_size_;
    long rowset_position_;
    std::map<string, bound_column*> bound_columns_by_name_;
    bool at_end_;
#if defined(NANODBC_DO_ASYNC_IMPL)
    bool async_; // true if statement is currently in SQL_STILL_EXECUTING mode
#endif
};

template <>
inline void result::result_impl::get_ref_impl<date>(short column, date& result) const
{
    bound_column& col = bound_columns_[column];
    switch (col.ctype_)
    {
    case SQL_C_DATE:
        result = *reinterpret_cast<date*>(col.pdata_ + rowset_position_ * col.clen_);
        return;
    case SQL_C_TIMESTAMP:
    {
        timestamp stamp = *reinterpret_cast<timestamp*>(col.pdata_ + rowset_position_ * col.clen_);
        date d = {stamp.year, stamp.month, stamp.day};
        result = d;
        return;
    }
    }
    throw type_incompatible_error();
}

template <>
inline void result::result_impl::get_ref_impl<time>(short column, time& result) const
{
    bound_column& col = bound_columns_[column];
    switch (col.ctype_)
    {
    case SQL_C_TIME:
        result = *reinterpret_cast<time*>(col.pdata_ + rowset_position_ * col.clen_);
        return;
    case SQL_C_TIMESTAMP:
    {
        timestamp stamp = *reinterpret_cast<timestamp*>(col.pdata_ + rowset_position_ * col.clen_);
        time t = {stamp.hour, stamp.min, stamp.sec};
        result = t;
        return;
    }
    }
    throw type_incompatible_error();
}

template <>
inline void result::result_impl::get_ref_impl<timestamp>(short column, timestamp& result) const
{
    bound_column& col = bound_columns_[column];
    switch (col.ctype_)
    {
    case SQL_C_DATE:
    {
        date d = *reinterpret_cast<date*>(col.pdata_ + rowset_position_ * col.clen_);
        timestamp stamp = {d.year, d.month, d.day, 0, 0, 0, 0};
        result = stamp;
        return;
    }
    case SQL_C_TIMESTAMP:
        result = *reinterpret_cast<timestamp*>(col.pdata_ + rowset_position_ * col.clen_);
        return;
    }
    throw type_incompatible_error();
}

template <>
inline void result::result_impl::get_ref_impl<string>(short column, string& result) const
{
    bound_column& col = bound_columns_[column];
    const SQLULEN column_size = col.sqlsize_;

    switch (col.ctype_)
    {
    case SQL_C_CHAR:
    case SQL_C_BINARY:
    {
        if (col.blob_)
        {
            // Input is always std::string, while output may be std::string or wide_string
            std::string out;
            // The length of the data available to return, decreasing with subsequent SQLGetData
            // calls.
            // But, NOT the length of data returned into the buffer (apart from the final call).
            SQLLEN ValueLenOrInd;
            SQLRETURN rc;

#if defined(NANODBC_DO_ASYNC_IMPL)
            stmt_.disable_async();
#endif

            void* handle = native_statement_handle();
            do
            {
                char buffer[1024] = {0};
                const std::size_t buffer_size = sizeof(buffer);
                NANODBC_CALL_RC(
                    SQLGetData,
                    rc,
                    handle,          // StatementHandle
                    column + 1,      // Col_or_Param_Num
                    col.ctype_,      // TargetType
                    buffer,          // TargetValuePtr
                    buffer_size,     // BufferLength
                    &ValueLenOrInd); // StrLen_or_IndPtr
                if (ValueLenOrInd > 0)
                    out.append(
                        buffer,
                        std::min<std::size_t>(
                            ValueLenOrInd,
                            col.ctype_ == SQL_C_BINARY ? buffer_size : buffer_size - 1));
                else if (ValueLenOrInd == SQL_NULL_DATA)
                    col.cbdata_[static_cast<size_t>(rowset_position_)] = (SQLINTEGER)SQL_NULL_DATA;
                // Sequence of successful calls is:
                // SQL_NO_DATA or SQL_SUCCESS_WITH_INFO followed by SQL_SUCCESS.
            } while (rc == SQL_SUCCESS_WITH_INFO);
            if (rc == SQL_SUCCESS || rc == SQL_NO_DATA)
                convert(out, result);
            else if (!success(rc))
                NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);
        }
        else
        {
            const char* s = col.pdata_ + rowset_position_ * col.clen_;
            const std::string::size_type str_size = std::strlen(s);
            result.assign(s, s + str_size);
        }
        return;
    }

    case SQL_C_WCHAR:
    {
        if (col.blob_)
        {
            // Input is always wide_string, output might be std::string or wide_string.
            // Use a string builder to build the output string.
            wide_string out;
            // The length of the data available to return, decreasing with subsequent SQLGetData
            // calls.
            // But, NOT the length of data returned into the buffer (apart from the final call).
            SQLLEN ValueLenOrInd;
            SQLRETURN rc;

#if defined(NANODBC_DO_ASYNC_IMPL)
            stmt_.disable_async();
#endif

            void* handle = native_statement_handle();
            do
            {
                wide_char_t buffer[512] = {0};
                const std::size_t buffer_size = sizeof(buffer);
                NANODBC_CALL_RC(
                    SQLGetData,
                    rc,
                    handle,          // StatementHandle
                    column + 1,      // Col_or_Param_Num
                    col.ctype_,      // TargetType
                    buffer,          // TargetValuePtr
                    buffer_size,     // BufferLength
                    &ValueLenOrInd); // StrLen_or_IndPtr
                if (ValueLenOrInd > 0)
                    out.append(
                        buffer,
                        std::min<std::size_t>(
                            ValueLenOrInd / sizeof(wide_char_t),
                            (buffer_size / sizeof(wide_char_t)) - 1));
                else if (ValueLenOrInd == SQL_NULL_DATA)
                    col.cbdata_[static_cast<std::size_t>(rowset_position_)] = (SQLINTEGER)SQL_NULL_DATA;
                // Sequence of successful calls is:
                // SQL_NO_DATA or SQL_SUCCESS_WITH_INFO followed by SQL_SUCCESS.
            } while (rc == SQL_SUCCESS_WITH_INFO);
            if (rc == SQL_SUCCESS || rc == SQL_NO_DATA)
                convert(out, result);
            else if (!success(rc))
                NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);
            ;
        }
        else
        {
            // Type is unicode in the database, convert if necessary
            const SQLWCHAR* s =
                reinterpret_cast<SQLWCHAR*>(col.pdata_ + rowset_position_ * col.clen_);
            const string::size_type str_size = col.cbdata_[static_cast<size_t>(rowset_position_)] / sizeof(SQLWCHAR);
            wide_string temp(s, s + str_size);
            convert(temp, result);
        }
        return;
    }

    case SQL_C_GUID:
    {
        const char* s = col.pdata_ + rowset_position_ * col.clen_;
        result.assign(s, s + column_size);
        return;
    }

    case SQL_C_LONG:
    {
        std::string buffer;
        buffer.reserve(column_size + 1); // ensure terminating null
        buffer.resize(buffer.capacity());
        using std::fill;
        fill(buffer.begin(), buffer.end(), '\0');
        const int32_t data = *reinterpret_cast<int32_t*>(col.pdata_ + rowset_position_ * col.clen_);
        const int bytes =
            std::snprintf(const_cast<char*>(buffer.data()), column_size + 1, "%d", data);
        if (bytes == -1)
            throw type_incompatible_error();
        else if ((SQLULEN)bytes < column_size)
            buffer.resize(static_cast<size_t>(bytes));
        buffer.resize(std::strlen(buffer.data())); // drop any trailing nulls
        result.reserve(buffer.size() * sizeof(string::value_type));
        convert(buffer, result);
        return;
    }

    case SQL_C_SBIGINT:
    {
        using namespace std; // in case intmax_t is in namespace std
        std::string buffer;
        buffer.reserve(column_size + 1); // ensure terminating null
        buffer.resize(buffer.capacity());
        using std::fill;
        fill(buffer.begin(), buffer.end(), '\0');
        const intmax_t data =
            (intmax_t) * reinterpret_cast<int64_t*>(col.pdata_ + rowset_position_ * col.clen_);
        const int bytes =
            std::snprintf(const_cast<char*>(buffer.data()), column_size + 1, "%jd", data);
        if (bytes == -1)
            throw type_incompatible_error();
        else if ((SQLULEN)bytes < column_size)
            buffer.resize(static_cast<size_t>(bytes));
        buffer.resize(std::strlen(buffer.data())); // drop any trailing nulls
        result.reserve(buffer.size() * sizeof(string::value_type));
        convert(buffer, result);
        return;
    }

    case SQL_C_FLOAT:
    {
        std::string buffer;
        buffer.reserve(column_size + 1); // ensure terminating null
        buffer.resize(buffer.capacity());
        using std::fill;
        fill(buffer.begin(), buffer.end(), '\0');
        const float data = *reinterpret_cast<float*>(col.pdata_ + rowset_position_ * col.clen_);
        const int bytes =
            std::snprintf(const_cast<char*>(buffer.data()), column_size + 1, "%f", data);
        if (bytes == -1)
            throw type_incompatible_error();
        else if ((SQLULEN)bytes < column_size)
            buffer.resize(static_cast<std::size_t>(bytes));
        buffer.resize(std::strlen(buffer.data())); // drop any trailing nulls
        result.reserve(buffer.size() * sizeof(string::value_type));
        convert(buffer, result);
        return;
    }

    case SQL_C_DOUBLE:
    {
        std::string buffer;
        const SQLULEN width = column_size + 2; // account for decimal mark and sign
        buffer.reserve(width + 1);             // ensure terminating null
        buffer.resize(buffer.capacity());
        using std::fill;
        fill(buffer.begin(), buffer.end(), '\0');
        const double data = *reinterpret_cast<double*>(col.pdata_ + rowset_position_ * col.clen_);
        const int bytes = std::snprintf(
            const_cast<char*>(buffer.data()),
            width + 1,
            "%.*lf",    // restrict the number of digits
            col.scale_, // number of digits after the decimal point
            data);
        if (bytes == -1)
            throw type_incompatible_error();
        else if ((SQLULEN)bytes < column_size)
            buffer.resize(static_cast<size_t>(bytes));
        buffer.resize(std::strlen(buffer.data())); // drop any trailing nulls
        result.reserve(buffer.size() * sizeof(string::value_type));
        convert(buffer, result);
        return;
    }

    case SQL_C_DATE:
    {
        const date d = *reinterpret_cast<date*>(col.pdata_ + rowset_position_ * col.clen_);
        std::tm st = {0};
        st.tm_year = d.year - 1900;
        st.tm_mon = d.month - 1;
        st.tm_mday = d.day;
        char* old_lc_time = std::setlocale(LC_TIME, nullptr);
        std::setlocale(LC_TIME, "");
        char date_str[512];
        std::strftime(date_str, sizeof(date_str), "%Y-%m-%d", &st);
        std::setlocale(LC_TIME, old_lc_time);
        convert(date_str, result);
        return;
    }

    case SQL_C_TIME:
    {
        const time t = *reinterpret_cast<time*>(col.pdata_ + rowset_position_ * col.clen_);
        std::tm st = {0};
        st.tm_hour = t.hour;
        st.tm_min = t.min;
        st.tm_sec = t.sec;
        char* old_lc_time = std::setlocale(LC_TIME, nullptr);
        std::setlocale(LC_TIME, "");
        char date_str[512];
        std::strftime(date_str, sizeof(date_str), "%H:%M:%S", &st);
        std::setlocale(LC_TIME, old_lc_time);
        convert(date_str, result);
        return;
    }

    case SQL_C_TIMESTAMP:
    {
        const timestamp stamp =
            *reinterpret_cast<timestamp*>(col.pdata_ + rowset_position_ * col.clen_);
        std::tm st = {0};
        st.tm_year = stamp.year - 1900;
        st.tm_mon = stamp.month - 1;
        st.tm_mday = stamp.day;
        st.tm_hour = stamp.hour;
        st.tm_min = stamp.min;
        st.tm_sec = stamp.sec;
        char* old_lc_time = std::setlocale(LC_TIME, nullptr);
        std::setlocale(LC_TIME, "");
        char date_str[512];
        std::strftime(date_str, sizeof(date_str), "%Y-%m-%d %H:%M:%S %z", &st);
        std::setlocale(LC_TIME, old_lc_time);
        convert(date_str, result);
        return;
    }
    }
    throw type_incompatible_error();
}

template <>
inline void result::result_impl::get_ref_impl<std::vector<std::uint8_t>>(
    short column,
    std::vector<std::uint8_t>& result) const
{
    bound_column& col = bound_columns_[column];
    const SQLULEN column_size = col.sqlsize_;

    switch (col.ctype_)
    {
    case SQL_C_BINARY:
    {
        if (col.blob_)
        {
            // Input and output is always array of bytes.
            std::vector<std::uint8_t> out;
            std::uint8_t buffer[1024] = {0};
            std::size_t const buffer_size = sizeof(buffer);
            // The length of the data available to return, decreasing with subsequent SQLGetData
            // calls.
            // But, NOT the length of data returned into the buffer (apart from the final call).
            SQLLEN ValueLenOrInd;
            SQLRETURN rc;

#if defined(NANODBC_DO_ASYNC_IMPL)
            stmt_.disable_async();
#endif

            void* handle = native_statement_handle();
            do
            {
                NANODBC_CALL_RC(
                    SQLGetData,
                    rc,
                    handle,          // StatementHandle
                    column + 1,      // Col_or_Param_Num
                    SQL_C_BINARY,    // TargetType
                    buffer,          // TargetValuePtr
                    buffer_size,     // BufferLength
                    &ValueLenOrInd); // StrLen_or_IndPtr
                if (ValueLenOrInd > 0)
                {
                    auto const buffer_size_filled =
                        std::min<std::size_t>(ValueLenOrInd, buffer_size);
                    NANODBC_ASSERT(buffer_size_filled <= buffer_size);
                    out.insert(std::end(out), buffer, buffer + buffer_size_filled);
                }
                else if (ValueLenOrInd == SQL_NULL_DATA)
                    col.cbdata_[static_cast<size_t>(rowset_position_)] = (SQLINTEGER)SQL_NULL_DATA;
                // Sequence of successful calls is:
                // SQL_NO_DATA or SQL_SUCCESS_WITH_INFO followed by SQL_SUCCESS.
            } while (rc == SQL_SUCCESS_WITH_INFO);
            if (rc == SQL_SUCCESS || rc == SQL_NO_DATA)
                result = std::move(out);
            else if (!success(rc))
                NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);
        }
        else
        {
            // Read fixed-length binary data
            const char* s = col.pdata_ + rowset_position_ * col.clen_;
            result.assign(s, s + column_size);
        }
        return;
    }
    }
    throw type_incompatible_error();
}

template <class T>
void result::result_impl::get_ref_impl(short column, T& result) const
{
    bound_column& col = bound_columns_[column];
    using namespace std; // if int64_t is in std namespace (in c++11)
    const char* s = col.pdata_ + rowset_position_ * col.clen_;
    switch (col.ctype_)
    {
    case SQL_C_CHAR:
        result = (T) * (char*)(s);
        return;
    case SQL_C_SSHORT:
        result = (T) * (short*)(s);
        return;
    case SQL_C_USHORT:
        result = (T) * (unsigned short*)(s);
        return;
    case SQL_C_LONG:
        result = (T) * (int32_t*)(s);
        return;
    case SQL_C_SLONG:
        result = (T) * (int32_t*)(s);
        return;
    case SQL_C_ULONG:
        result = (T) * (uint32_t*)(s);
        return;
    case SQL_C_FLOAT:
        result = (T) * (float*)(s);
        return;
    case SQL_C_DOUBLE:
        result = (T) * (double*)(s);
        return;
    case SQL_C_SBIGINT:
        result = (T) * (int64_t*)(s);
        return;
    case SQL_C_UBIGINT:
        result = (T) * (uint64_t*)(s);
        return;
    }
    throw type_incompatible_error();
}

} // namespace nanodbc

// clang-format off
// 8888888888                            8888888888                         888    d8b
// 888                                   888                                888    Y8P
// 888                                   888                                888
// 8888888 888d888 .d88b.   .d88b.       8888888 888  888 88888b.   .d8888b 888888 888  .d88b.  88888b.  .d8888b
// 888     888P"  d8P  Y8b d8P  Y8b      888     888  888 888 "88b d88P"    888    888 d88""88b 888 "88b 88K
// 888     888    88888888 88888888      888     888  888 888  888 888      888    888 888  888 888  888 "Y8888b.
// 888     888    Y8b.     Y8b.          888     Y88b 888 888  888 Y88b.    Y88b.  888 Y88..88P 888  888      X88
// 888     888     "Y8888   "Y8888       888      "Y88888 888  888  "Y8888P  "Y888 888  "Y88P"  888  888  88888P'
// MARK: Free Functions -
// clang-format on

namespace nanodbc
{

std::list<driver> list_drivers()
{
    NANODBC_SQLCHAR descr[1024] = {0};
    NANODBC_SQLCHAR attrs[1024] = {0};
    SQLSMALLINT descr_len_ret{0};
    SQLSMALLINT attrs_len_ret{0};
    SQLUSMALLINT direction{SQL_FETCH_FIRST};

    HENV env{0};
    allocate_environment_handle(env);

    std::list<driver> drivers;
    RETCODE rc{SQL_SUCCESS};
    do
    {
        NANODBC_ASSERT(env);
        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLDrivers),
            rc,
            env,
            direction,                               // EnvironmentHandle
            descr,                                   // DriverDescription
            sizeof(descr) / sizeof(NANODBC_SQLCHAR), // BufferLength1
            &descr_len_ret,                          // DescriptionLengthPtr
            attrs,                                   // DriverAttributes
            sizeof(attrs) / sizeof(NANODBC_SQLCHAR), // BufferLength2
            &attrs_len_ret);                         // AttributesLengthPtr

        if (rc == SQL_SUCCESS)
        {
            using char_type = string::value_type;
            static_assert(
                sizeof(NANODBC_SQLCHAR) == sizeof(char_type),
                "incompatible SQLCHAR and string::value_type");

            driver drv;
            drv.name = string(&descr[0], &descr[strarrlen(descr)]);

            // Split "Key1=Value1\0Key2=Value2\0\0" into list of key-value pairs
            auto beg = &attrs[0];
            auto const end = &attrs[attrs_len_ret];
            auto pair_end = end;
            while ((pair_end = std::find(beg, end, NANODBC_TEXT('\0'))) != end)
            {
                auto const eq_pos = std::find(beg, pair_end, NANODBC_TEXT('='));
                if (eq_pos == end)
                    break;

                driver::attribute attr{{beg, eq_pos}, {eq_pos + 1, pair_end}};
                drv.attributes.push_back(std::move(attr));
                beg = pair_end + 1;
            }

            drivers.push_back(std::move(drv));

            direction = SQL_FETCH_NEXT;
        }
        else
        {
            if (rc != SQL_NO_DATA)
                NANODBC_THROW_DATABASE_ERROR(env, SQL_HANDLE_ENV);
        }
    } while (success(rc));

    return drivers;
}

result execute(connection& conn, const string& query, long batch_operations, long timeout)
{
    class statement statement;
    return statement.execute_direct(conn, query, batch_operations, timeout);
}

void just_execute(connection& conn, const string& query, long batch_operations, long timeout)
{
    class statement statement;
    statement.just_execute_direct(conn, query, batch_operations, timeout);
}

result execute(statement& stmt, long batch_operations)
{
    return stmt.execute(batch_operations);
}

void just_execute(statement& stmt, long batch_operations)
{
    return stmt.just_execute(batch_operations);
}

result transact(statement& stmt, long batch_operations)
{
    class transaction transaction(stmt.connection());
    result rvalue = stmt.execute(batch_operations);
    transaction.commit();
    return rvalue;
}

void just_transact(statement& stmt, long batch_operations)
{
    class transaction transaction(stmt.connection());
    stmt.just_execute(batch_operations);
    transaction.commit();
}

void prepare(statement& stmt, const string& query, long timeout)
{
    stmt.prepare(stmt.connection(), query, timeout);
}

} // namespace nanodbc

// clang-format off
//  .d8888b.                                               888    d8b                             8888888888                 888
// d88P  Y88b                                              888    Y8P                             888                        888
// 888    888                                              888                                    888                        888
// 888         .d88b.  88888b.  88888b.   .d88b.   .d8888b 888888 888  .d88b.  88888b.            8888888 888  888  888  .d88888
// 888        d88""88b 888 "88b 888 "88b d8P  Y8b d88P"    888    888 d88""88b 888 "88b           888     888  888  888 d88" 888
// 888    888 888  888 888  888 888  888 88888888 888      888    888 888  888 888  888           888     888  888  888 888  888
// Y88b  d88P Y88..88P 888  888 888  888 Y8b.     Y88b.    Y88b.  888 Y88..88P 888  888           888     Y88b 888 d88P Y88b 888
//  "Y8888P"   "Y88P"  888  888 888  888  "Y8888   "Y8888P  "Y888 888  "Y88P"  888  888           888      "Y8888888P"   "Y88888
// MARK: Connection Fwd -
// clang-format on

namespace nanodbc
{

connection::connection()
    : impl_(new connection_impl())
{
}

connection::connection(const connection& rhs)
    : impl_(rhs.impl_)
{
}

#ifndef NANODBC_NO_MOVE_CTOR
connection::connection(connection&& rhs) NANODBC_NOEXCEPT : impl_(std::move(rhs.impl_))
{
}
#endif

connection& connection::operator=(connection rhs)
{
    swap(rhs);
    return *this;
}

void connection::swap(connection& rhs) NANODBC_NOEXCEPT
{
    using std::swap;
    swap(impl_, rhs.impl_);
}

connection::connection(const string& dsn, const string& user, const string& pass, long timeout)
    : impl_(new connection_impl(dsn, user, pass, timeout))
{
}

connection::connection(const string& connection_string, long timeout)
    : impl_(new connection_impl(connection_string, timeout))
{
}

connection::~connection() NANODBC_NOEXCEPT
{
}

void connection::connect(const string& dsn, const string& user, const string& pass, long timeout)
{
    impl_->connect(dsn, user, pass, timeout);
}

void connection::connect(const string& connection_string, long timeout)
{
    impl_->connect(connection_string, timeout);
}

#if !defined(NANODBC_DISABLE_ASYNC) && defined(SQL_ATTR_ASYNC_DBC_EVENT)
bool connection::async_connect(
    const string& dsn,
    const string& user,
    const string& pass,
    void* event_handle,
    long timeout)
{
    return impl_->connect(dsn, user, pass, timeout, event_handle) == SQL_STILL_EXECUTING;
}

bool connection::async_connect(const string& connection_string, void* event_handle, long timeout)
{
    return impl_->connect(connection_string, timeout, event_handle) == SQL_STILL_EXECUTING;
}

void connection::async_complete()
{
    impl_->async_complete();
}
#endif // !NANODBC_DISABLE_ASYNC && SQL_ATTR_ASYNC_DBC_EVENT

bool connection::connected() const
{
    return impl_->connected();
}

void connection::disconnect()
{
    impl_->disconnect();
}

std::size_t connection::transactions() const
{
    return impl_->transactions();
}

template <class T>
T connection::get_info(short info_type) const
{
    return impl_->get_info<T>(info_type);
}

void* connection::native_dbc_handle() const
{
    return impl_->native_dbc_handle();
}

void* connection::native_env_handle() const
{
    return impl_->native_env_handle();
}

string connection::dbms_name() const
{
    return impl_->dbms_name();
}

string connection::dbms_version() const
{
    return impl_->dbms_version();
}

string connection::driver_name() const
{
    return impl_->driver_name();
}

string connection::database_name() const
{
    return impl_->database_name();
}

string connection::catalog_name() const
{
    return impl_->catalog_name();
}

std::size_t connection::ref_transaction()
{
    return impl_->ref_transaction();
}

std::size_t connection::unref_transaction()
{
    return impl_->unref_transaction();
}

bool connection::rollback() const
{
    return impl_->rollback();
}

void connection::rollback(bool onoff)
{
    impl_->rollback(onoff);
}

} // namespace nanodbc

// clang-format off
// 88888888888                                                  888    d8b                             8888888888                 888
//     888                                                      888    Y8P                             888                        888
//     888                                                      888                                    888                        888
//     888  888d888 8888b.  88888b.  .d8888b   8888b.   .d8888b 888888 888  .d88b.  88888b.            8888888 888  888  888  .d88888 .d8888b
//     888  888P"      "88b 888 "88b 88K          "88b d88P"    888    888 d88""88b 888 "88b           888     888  888  888 d88" 888 88K
//     888  888    .d888888 888  888 "Y8888b. .d888888 888      888    888 888  888 888  888           888     888  888  888 888  888 "Y8888b.
//     888  888    888  888 888  888      X88 888  888 Y88b.    Y88b.  888 Y88..88P 888  888           888     Y88b 888 d88P Y88b 888      X88
//     888  888    "Y888888 888  888  88888P' "Y888888  "Y8888P  "Y888 888  "Y88P"  888  888           888      "Y8888888P"   "Y88888  88888P'
// MARK: Transaction Fwd -
// clang-format on

namespace nanodbc
{

transaction::transaction(const class connection& conn)
    : impl_(new transaction_impl(conn))
{
}

transaction::transaction(const transaction& rhs)
    : impl_(rhs.impl_)
{
}

#ifndef NANODBC_NO_MOVE_CTOR
transaction::transaction(transaction&& rhs) NANODBC_NOEXCEPT : impl_(std::move(rhs.impl_))
{
}
#endif

transaction& transaction::operator=(transaction rhs)
{
    swap(rhs);
    return *this;
}

void transaction::swap(transaction& rhs) NANODBC_NOEXCEPT
{
    using std::swap;
    swap(impl_, rhs.impl_);
}

transaction::~transaction() NANODBC_NOEXCEPT
{
}

void transaction::commit()
{
    impl_->commit();
}

void transaction::rollback() NANODBC_NOEXCEPT
{
    impl_->rollback();
}

class connection& transaction::connection()
{
    return impl_->connection();
}

const class connection& transaction::connection() const
{
    return impl_->connection();
}

transaction::operator class connection&()
{
    return impl_->connection();
}

transaction::operator const class connection&() const
{
    return impl_->connection();
}

} // namespace nanodbc

// clang-format off
//  .d8888b.  888             888                                            888              8888888888                 888
// d88P  Y88b 888             888                                            888              888                        888
// Y88b.      888             888                                            888              888                        888
//  "Y888b.   888888  8888b.  888888 .d88b.  88888b.d88b.   .d88b.  88888b.  888888           8888888 888  888  888  .d88888
//     "Y88b. 888        "88b 888   d8P  Y8b 888 "888 "88b d8P  Y8b 888 "88b 888              888     888  888  888 d88" 888
//       "888 888    .d888888 888   88888888 888  888  888 88888888 888  888 888              888     888  888  888 888  888
// Y88b  d88P Y88b.  888  888 Y88b. Y8b.     888  888  888 Y8b.     888  888 Y88b.            888     Y88b 888 d88P Y88b 888
//  "Y8888P"   "Y888 "Y888888  "Y888 "Y8888  888  888  888  "Y8888  888  888  "Y888           888      "Y8888888P"   "Y88888
// MARK: Statement Fwd -
// clang-format on

namespace nanodbc
{

statement::statement()
    : impl_(new statement_impl())
{
}

statement::statement(class connection& conn)
    : impl_(new statement_impl(conn))
{
}

#ifndef NANODBC_NO_MOVE_CTOR
statement::statement(statement&& rhs) NANODBC_NOEXCEPT : impl_(std::move(rhs.impl_))
{
}
#endif

statement::statement(class connection& conn, const string& query, long timeout)
    : impl_(new statement_impl(conn, query, timeout))
{
}

statement::statement(const statement& rhs)
    : impl_(rhs.impl_)
{
}

statement& statement::operator=(statement rhs)
{
    swap(rhs);
    return *this;
}

void statement::swap(statement& rhs) NANODBC_NOEXCEPT
{
    using std::swap;
    swap(impl_, rhs.impl_);
}

statement::~statement() NANODBC_NOEXCEPT
{
}

void statement::open(class connection& conn)
{
    impl_->open(conn);
}

bool statement::open() const
{
    return impl_->open();
}

bool statement::connected() const
{
    return impl_->connected();
}

const class connection& statement::connection() const
{
    return impl_->connection();
}

class connection& statement::connection()
{
    return impl_->connection();
}

void* statement::native_statement_handle() const
{
    return impl_->native_statement_handle();
}

void statement::close()
{
    impl_->close();
}

void statement::cancel()
{
    impl_->cancel();
}

void statement::prepare(class connection& conn, const string& query, long timeout)
{
    impl_->prepare(conn, query, timeout);
}

void statement::prepare(const string& query, long timeout)
{
    impl_->prepare(query, timeout);
}

void statement::timeout(long timeout)
{
    impl_->timeout(timeout);
}

result statement::execute_direct(
    class connection& conn,
    const string& query,
    long batch_operations,
    long timeout)
{
    return impl_->execute_direct(conn, query, batch_operations, timeout, *this);
}

#if defined(NANODBC_DO_ASYNC_IMPL)
bool statement::async_prepare(const string& query, void* event_handle, long timeout)
{
    return impl_->async_prepare(query, event_handle, timeout);
}

bool statement::async_execute_direct(
    class connection& conn,
    void* event_handle,
    const string& query,
    long batch_operations,
    long timeout)
{
    return impl_->async_execute_direct(conn, event_handle, query, batch_operations, timeout, *this);
}

bool statement::async_execute(void* event_handle, long batch_operations, long timeout)
{
    return impl_->async_execute(event_handle, batch_operations, timeout, *this);
}

void statement::complete_prepare()
{
    return impl_->complete_prepare();
}

result statement::complete_execute(long batch_operations)
{
    return impl_->complete_execute(batch_operations, *this);
}

result statement::async_complete(long batch_operations)
{
    return impl_->complete_execute(batch_operations, *this);
}

void statement::enable_async(void* event_handle)
{
    impl_->enable_async(event_handle);
}

void statement::disable_async() const
{
    impl_->disable_async();
}
#endif

void statement::just_execute_direct(
    class connection& conn,
    const string& query,
    long batch_operations,
    long timeout)
{
    impl_->just_execute_direct(conn, query, batch_operations, timeout, *this);
}

result statement::execute(long batch_operations, long timeout)
{
    return impl_->execute(batch_operations, timeout, *this);
}

void statement::just_execute(long batch_operations, long timeout)
{
    impl_->just_execute(batch_operations, timeout, *this);
}

result statement::procedure_columns(
    const string& catalog,
    const string& schema,
    const string& procedure,
    const string& column)
{
    return impl_->procedure_columns(catalog, schema, procedure, column, *this);
}

long statement::affected_rows() const
{
    return impl_->affected_rows();
}

short statement::columns() const
{
    return impl_->columns();
}

short statement::parameters() const
{
    return impl_->parameters();
}

void statement::reset_parameters() NANODBC_NOEXCEPT
{
    impl_->reset_parameters();
}

unsigned long statement::parameter_size(short param_index) const
{
    return impl_->parameter_size(param_index);
}

// We need to instantiate each form of bind() for each of our supported data types.
#define NANODBC_INSTANTIATE_BINDS(type)                                                            \
    template void statement::bind(short, const type*, param_direction);              /* 1-ary */   \
    template void statement::bind(short, const type*, std::size_t, param_direction); /* n-ary */   \
    template void statement::bind(                                                                 \
        short, const type*, std::size_t, const type*, param_direction); /* n-ary, sentry */        \
    template void statement::bind(                                                                 \
        short, const type*, std::size_t, const bool*, param_direction) /* n-ary, flags */

// The following are the only supported instantiations of statement::bind().
NANODBC_INSTANTIATE_BINDS(string::value_type);
NANODBC_INSTANTIATE_BINDS(short);
NANODBC_INSTANTIATE_BINDS(unsigned short);
NANODBC_INSTANTIATE_BINDS(int);
NANODBC_INSTANTIATE_BINDS(unsigned int);
NANODBC_INSTANTIATE_BINDS(long int);
NANODBC_INSTANTIATE_BINDS(unsigned long int);
NANODBC_INSTANTIATE_BINDS(long long);
NANODBC_INSTANTIATE_BINDS(unsigned long long);
NANODBC_INSTANTIATE_BINDS(float);
NANODBC_INSTANTIATE_BINDS(double);
NANODBC_INSTANTIATE_BINDS(date);
NANODBC_INSTANTIATE_BINDS(time);
NANODBC_INSTANTIATE_BINDS(timestamp);

#undef NANODBC_INSTANTIATE_BINDS

template <class T>
void statement::bind(short param_index, const T* value, param_direction direction)
{
    impl_->bind(direction, param_index, value, 1);
}

template <class T>
void statement::bind(
    short param_index,
    T const* values,
    std::size_t batch_size,
    param_direction direction)
{
    impl_->bind(direction, param_index, values, batch_size);
}

template <class T>
void statement::bind(
    short param_index,
    T const* values,
    std::size_t batch_size,
    T const* null_sentry,
    param_direction direction)
{
    impl_->bind(direction, param_index, values, batch_size, nullptr, null_sentry);
}

template <class T>
void statement::bind(
    short param_index,
    T const* values,
    std::size_t batch_size,
    bool const* nulls,
    param_direction direction)
{
    impl_->bind(direction, param_index, values, batch_size, nulls);
}

void statement::bind(
    short param_index,
    std::vector<std::vector<uint8_t>> const& values,
    param_direction direction)
{
    impl_->bind(direction, param_index, values);
}

void statement::bind(
    short param_index,
    std::vector<std::vector<uint8_t>> const& values,
    bool const* nulls,
    param_direction direction)
{
    impl_->bind(direction, param_index, values, nulls);
}

void statement::bind(
    short param_index,
    std::vector<std::vector<uint8_t>> const& values,
    uint8_t const* null_sentry,
    param_direction direction)
{
    impl_->bind(direction, param_index, values, nullptr, null_sentry);
}

void statement::bind_strings(
    short param_index,
    std::vector<string> const& values,
    param_direction direction)
{
    impl_->bind_strings(direction, param_index, values);
}

void statement::bind_strings(
    short param_index,
    string::value_type const* values,
    std::size_t value_size,
    std::size_t batch_size,
    param_direction direction)
{
    impl_->bind_strings(direction, param_index, values, value_size, batch_size);
}

void statement::bind_strings(
    short param_index,
    string::value_type const* values,
    std::size_t value_size,
    std::size_t batch_size,
    string::value_type const* null_sentry,
    param_direction direction)
{
    impl_->bind_strings(
        direction, param_index, values, value_size, batch_size, nullptr, null_sentry);
}

void statement::bind_strings(
    short param_index,
    string::value_type const* values,
    std::size_t value_size,
    std::size_t batch_size,
    bool const* nulls,
    param_direction direction)
{
    impl_->bind_strings(direction, param_index, values, value_size, batch_size, nulls);
}

void statement::bind_strings(
    short param_index,
    std::vector<string> const& values,
    string::value_type const* null_sentry,
    param_direction direction)
{
    impl_->bind_strings(direction, param_index, values, nullptr, null_sentry);
}

void statement::bind_strings(
    short param_index,
    std::vector<string> const& values,
    bool const* nulls,
    param_direction direction)
{
    impl_->bind_strings(direction, param_index, values, nulls);
}

void statement::bind_null(short param_index, std::size_t batch_size)
{
    impl_->bind_null(param_index, batch_size);
}

} // namespace nanodbc

namespace nanodbc
{

catalog::tables::tables(result& find_result)
    : result_(find_result)
{
}

bool catalog::tables::next()
{
    return result_.next();
}

string catalog::tables::table_catalog() const
{
    // TABLE_CAT might be NULL
    return result_.get<string>(0, string());
}

string catalog::tables::table_schema() const
{
    // TABLE_SCHEM might be NULL
    return result_.get<string>(1, string());
}

string catalog::tables::table_name() const
{
    // TABLE_NAME column is never NULL
    return result_.get<string>(2);
}

string catalog::tables::table_type() const
{
    // TABLE_TYPE column is never NULL
    return result_.get<string>(3);
}

string catalog::tables::table_remarks() const
{
    // REMARKS might be NULL
    return result_.get<string>(4, string());
}

catalog::table_privileges::table_privileges(result& find_result)
    : result_(find_result)
{
}

bool catalog::table_privileges::next()
{
    return result_.next();
}

string catalog::table_privileges::table_catalog() const
{
    // TABLE_CAT might be NULL
    return result_.get<string>(0, string());
}

string catalog::table_privileges::table_schema() const
{
    // TABLE_SCHEM might be NULL
    return result_.get<string>(1, string());
}

string catalog::table_privileges::table_name() const
{
    // TABLE_NAME column is never NULL
    return result_.get<string>(2);
}

string catalog::table_privileges::grantor() const
{
    // GRANTOR might be NULL
    return result_.get<string>(3, string());
}

string catalog::table_privileges::grantee() const
{
    // GRANTEE column is never NULL
    return result_.get<string>(4);
}

string catalog::table_privileges::privilege() const
{
    // PRIVILEGE column is never NULL
    return result_.get<string>(5);
}

string catalog::table_privileges::is_grantable() const
{
    // IS_GRANTABLE might be NULL
    return result_.get<string>(6, string());
}

catalog::primary_keys::primary_keys(result& find_result)
    : result_(find_result)
{
}

bool catalog::primary_keys::next()
{
    return result_.next();
}

string catalog::primary_keys::table_catalog() const
{
    // TABLE_CAT might be NULL
    return result_.get<string>(0, string());
}

string catalog::primary_keys::table_schema() const
{
    // TABLE_SCHEM might be NULL
    return result_.get<string>(1, string());
}

string catalog::primary_keys::table_name() const
{
    // TABLE_NAME is never NULL
    return result_.get<string>(2);
}

string catalog::primary_keys::column_name() const
{
    // COLUMN_NAME is never NULL
    return result_.get<string>(3);
}

short catalog::primary_keys::column_number() const
{
    // KEY_SEQ is never NULL
    return result_.get<short>(4);
}

string catalog::primary_keys::primary_key_name() const
{
    // PK_NAME might be NULL
    return result_.get<string>(5);
}

catalog::columns::columns(result& find_result)
    : result_(find_result)
{
}

bool catalog::columns::next()
{
    return result_.next();
}

string catalog::columns::table_catalog() const
{
    // TABLE_CAT might be NULL
    return result_.get<string>(0, string());
}

string catalog::columns::table_schema() const
{
    // TABLE_SCHEM might be NULL
    return result_.get<string>(1, string());
}

string catalog::columns::table_name() const
{
    // TABLE_NAME is never NULL
    return result_.get<string>(2);
}

string catalog::columns::column_name() const
{
    // COLUMN_NAME is never NULL
    return result_.get<string>(3);
}

short catalog::columns::data_type() const
{
    // DATA_TYPE is never NULL
    return result_.get<short>(4);
}

string catalog::columns::type_name() const
{
    // TYPE_NAME is never NULL
    return result_.get<string>(5);
}

long catalog::columns::column_size() const
{
    // COLUMN_SIZE
    return result_.get<long>(6);
}

long catalog::columns::buffer_length() const
{
    // BUFFER_LENGTH
    return result_.get<long>(7);
}

short catalog::columns::decimal_digits() const
{
    // DECIMAL_DIGITS might be NULL
    return result_.get<short>(8, 0);
}

short catalog::columns::numeric_precision_radix() const
{
    // NUM_PREC_RADIX might be NULL
    return result_.get<short>(9, 0);
}

short catalog::columns::nullable() const
{
    // NULLABLE is never NULL
    return result_.get<short>(10);
}

string catalog::columns::remarks() const
{
    // REMARKS might be NULL
    return result_.get<string>(11, string());
}

string catalog::columns::column_default() const
{
    // COLUMN_DEF might be NULL, if no default value is specified
    return result_.get<string>(12, string());
}

short catalog::columns::sql_data_type() const
{
    // SQL_DATA_TYPE is never NULL
    return result_.get<short>(13);
}

short catalog::columns::sql_datetime_subtype() const
{
    // SQL_DATETIME_SUB might be NULL
    return result_.get<short>(14, 0);
}

long catalog::columns::char_octet_length() const
{
    // CHAR_OCTET_LENGTH might be NULL
    return result_.get<long>(15, 0);
}

long catalog::columns::ordinal_position() const
{
    // ORDINAL_POSITION is never NULL
    return result_.get<long>(16);
}

string catalog::columns::is_nullable() const
{
    // IS_NULLABLE might be NULL.
    return result_.get<string>(17, string());
}

catalog::catalog(connection& conn)
    : conn_(conn)
{
}

catalog::tables catalog::find_tables(
    const string& table,
    const string& type,
    const string& schema,
    const string& catalog)
{
    // Passing a null pointer to a search pattern argument does not
    // constrain the search for that argument; that is, a null pointer and
    // the search pattern % (any characters) are equivalent.
    // However, a zero-length search pattern - that is, a valid pointer to
    // a string of length zero - matches only the empty string ("").
    // See https://msdn.microsoft.com/en-us/library/ms710171.aspx

    statement stmt(conn_);
    RETCODE rc;
    NANODBC_CALL_RC(
        NANODBC_FUNC(SQLTables),
        rc,
        stmt.native_statement_handle(),
        (NANODBC_SQLCHAR*)(catalog.empty() ? nullptr : catalog.c_str()),
        (catalog.empty() ? 0 : SQL_NTS),
        (NANODBC_SQLCHAR*)(schema.empty() ? nullptr : schema.c_str()),
        (schema.empty() ? 0 : SQL_NTS),
        (NANODBC_SQLCHAR*)(table.empty() ? nullptr : table.c_str()),
        (table.empty() ? 0 : SQL_NTS),
        (NANODBC_SQLCHAR*)(type.empty() ? nullptr : type.c_str()),
        (type.empty() ? 0 : SQL_NTS));
    if (!success(rc))
        NANODBC_THROW_DATABASE_ERROR(stmt.native_statement_handle(), SQL_HANDLE_STMT);

    result find_result(stmt, 1);
    return catalog::tables(find_result);
}

catalog::table_privileges
catalog::find_table_privileges(const string& catalog, const string& table, const string& schema)
{
    // Passing a null pointer to a search pattern argument does not
    // constrain the search for that argument; that is, a null pointer and
    // the search pattern % (any characters) are equivalent.
    // However, a zero-length search pattern - that is, a valid pointer to
    // a string of length zero - matches only the empty string ("").
    // See https://msdn.microsoft.com/en-us/library/ms710171.aspx

    statement stmt(conn_);
    RETCODE rc;
    NANODBC_CALL_RC(
        NANODBC_FUNC(SQLTablePrivileges),
        rc,
        stmt.native_statement_handle(),
        (NANODBC_SQLCHAR*)(catalog.empty() ? nullptr : catalog.c_str()),
        (catalog.empty() ? 0 : SQL_NTS),
        (NANODBC_SQLCHAR*)(schema.empty() ? nullptr : schema.c_str()),
        (schema.empty() ? 0 : SQL_NTS),
        (NANODBC_SQLCHAR*)(table.empty() ? nullptr : table.c_str()),
        (table.empty() ? 0 : SQL_NTS));
    if (!success(rc))
        NANODBC_THROW_DATABASE_ERROR(stmt.native_statement_handle(), SQL_HANDLE_STMT);

    result find_result(stmt, 1);
    return catalog::table_privileges(find_result);
}

catalog::columns catalog::find_columns(
    const string& column,
    const string& table,
    const string& schema,
    const string& catalog)
{
    statement stmt(conn_);
    RETCODE rc;
    NANODBC_CALL_RC(
        NANODBC_FUNC(SQLColumns),
        rc,
        stmt.native_statement_handle(),
        (NANODBC_SQLCHAR*)(catalog.empty() ? nullptr : catalog.c_str()),
        (catalog.empty() ? 0 : SQL_NTS),
        (NANODBC_SQLCHAR*)(schema.empty() ? nullptr : schema.c_str()),
        (schema.empty() ? 0 : SQL_NTS),
        (NANODBC_SQLCHAR*)(table.empty() ? nullptr : table.c_str()),
        (table.empty() ? 0 : SQL_NTS),
        (NANODBC_SQLCHAR*)(column.empty() ? nullptr : column.c_str()),
        (column.empty() ? 0 : SQL_NTS));
    if (!success(rc))
        NANODBC_THROW_DATABASE_ERROR(stmt.native_statement_handle(), SQL_HANDLE_STMT);

    result find_result(stmt, 1);
    return catalog::columns(find_result);
}

catalog::primary_keys
catalog::find_primary_keys(const string& table, const string& schema, const string& catalog)
{
    statement stmt(conn_);
    RETCODE rc;
    NANODBC_CALL_RC(
        NANODBC_FUNC(SQLPrimaryKeys),
        rc,
        stmt.native_statement_handle(),
        (NANODBC_SQLCHAR*)(catalog.empty() ? nullptr : catalog.c_str()),
        (catalog.empty() ? 0 : SQL_NTS),
        (NANODBC_SQLCHAR*)(schema.empty() ? nullptr : schema.c_str()),
        (schema.empty() ? 0 : SQL_NTS),
        (NANODBC_SQLCHAR*)(table.empty() ? nullptr : table.c_str()),
        (table.empty() ? 0 : SQL_NTS));
    if (!success(rc))
        NANODBC_THROW_DATABASE_ERROR(stmt.native_statement_handle(), SQL_HANDLE_STMT);

    result find_result(stmt, 1);
    return catalog::primary_keys(find_result);
}

std::list<string> catalog::list_catalogs()
{
    // Special case for list of catalogs only:
    // all the other arguments must match empty string (""),
    // otherwise pattern-based lookup is performed returning
    // Cartesian product of catalogs, tables and schemas.
    statement stmt(conn_);
    RETCODE rc;
    NANODBC_CALL_RC(
        NANODBC_FUNC(SQLTables),
        rc,
        stmt.native_statement_handle(),
        (NANODBC_SQLCHAR*)SQL_ALL_CATALOGS,
        1,
        (NANODBC_SQLCHAR*)NANODBC_TEXT(""),
        0,
        (NANODBC_SQLCHAR*)NANODBC_TEXT(""),
        0,
        (NANODBC_SQLCHAR*)NANODBC_TEXT(""),
        0);
    if (!success(rc))
        NANODBC_THROW_DATABASE_ERROR(stmt.native_statement_handle(), SQL_HANDLE_STMT);

    result find_result(stmt, 1);
    catalog::tables catalogs(find_result);

    std::list<string> names;
    while (catalogs.next())
        names.push_back(catalogs.table_catalog());
    return names;
}

std::list<string> catalog::list_schemas()
{
    // Special case for list of schemas:
    // all the other arguments must match empty string (""),
    // otherwise pattern-based lookup is performed returning
    // Cartesian product of catalogs, tables and schemas.
    statement stmt(conn_);
    RETCODE rc;
    NANODBC_CALL_RC(
        NANODBC_FUNC(SQLTables),
        rc,
        stmt.native_statement_handle(),
        (NANODBC_SQLCHAR*)NANODBC_TEXT(""),
        0,
        (NANODBC_SQLCHAR*)SQL_ALL_SCHEMAS,
        1,
        (NANODBC_SQLCHAR*)NANODBC_TEXT(""),
        0,
        (NANODBC_SQLCHAR*)NANODBC_TEXT(""),
        0);
    if (!success(rc))
        NANODBC_THROW_DATABASE_ERROR(stmt.native_statement_handle(), SQL_HANDLE_STMT);

    result find_result(stmt, 1);
    catalog::tables schemas(find_result);

    std::list<string> names;
    while (schemas.next())
        names.push_back(schemas.table_schema());
    return names;
}

} // namespace nanodbc

// clang-format off
// 8888888b.                            888 888              8888888888                 888
// 888   Y88b                           888 888              888                        888
// 888    888                           888 888              888                        888
// 888   d88P .d88b.  .d8888b  888  888 888 888888           8888888 888  888  888  .d88888
// 8888888P" d8P  Y8b 88K      888  888 888 888              888     888  888  888 d88" 888
// 888 T88b  88888888 "Y8888b. 888  888 888 888              888     888  888  888 888  888
// 888  T88b Y8b.          X88 Y88b 888 888 Y88b.            888     Y88b 888 d88P Y88b 888
// 888   T88b "Y8888   88888P'  "Y88888 888  "Y888           888      "Y8888888P"   "Y88888
// MARK: Result Fwd -
// clang-format on

namespace nanodbc
{

result::result()
    : impl_()
{
}

result::~result() NANODBC_NOEXCEPT
{
}

result::result(statement stmt, long rowset_size)
    : impl_(new result_impl(stmt, rowset_size))
{
}

#ifndef NANODBC_NO_MOVE_CTOR
result::result(result&& rhs) NANODBC_NOEXCEPT : impl_(std::move(rhs.impl_))
{
}
#endif

result::result(const result& rhs)
    : impl_(rhs.impl_)
{
}

result& result::operator=(result rhs)
{
    swap(rhs);
    return *this;
}

void result::swap(result& rhs) NANODBC_NOEXCEPT
{
    using std::swap;
    swap(impl_, rhs.impl_);
}

void* result::native_statement_handle() const
{
    return impl_->native_statement_handle();
}

long result::rowset_size() const NANODBC_NOEXCEPT
{
    return impl_->rowset_size();
}

long result::affected_rows() const
{
    return impl_->affected_rows();
}

long result::rows() const NANODBC_NOEXCEPT
{
    return impl_->rows();
}

short result::columns() const
{
    return impl_->columns();
}

bool result::first()
{
    return impl_->first();
}

bool result::last()
{
    return impl_->last();
}

bool result::next()
{
    return impl_->next();
}

#if defined(NANODBC_DO_ASYNC_IMPL)
bool result::async_next(void* event_handle)
{
    return impl_->async_next(event_handle);
}

bool result::complete_next()
{
    return impl_->complete_next();
}
#endif

bool result::prior()
{
    return impl_->prior();
}

bool result::move(long row)
{
    return impl_->move(row);
}

bool result::skip(long rows)
{
    return impl_->skip(rows);
}

unsigned long result::position() const
{
    return impl_->position();
}

bool result::at_end() const NANODBC_NOEXCEPT
{
    return impl_->at_end();
}

bool result::is_null(short column) const
{
    return impl_->is_null(column);
}

bool result::is_null(const string& column_name) const
{
    return impl_->is_null(column_name);
}

short result::column(const string& column_name) const
{
    return impl_->column(column_name);
}

string result::column_name(short column) const
{
    return impl_->column_name(column);
}

long result::column_size(short column) const
{
    return impl_->column_size(column);
}

long result::column_size(const string& column_name) const
{
    return impl_->column_size(column_name);
}

int result::column_decimal_digits(short column) const
{
    return impl_->column_decimal_digits(column);
}

int result::column_decimal_digits(const string& column_name) const
{
    return impl_->column_decimal_digits(column_name);
}

int result::column_datatype(short column) const
{
    return impl_->column_datatype(column);
}

int result::column_datatype(const string& column_name) const
{
    return impl_->column_datatype(column_name);
}

string result::column_datatype_name(short column) const
{
    return impl_->column_datatype_name(column);
}

string result::column_datatype_name(const string& column_name) const
{
    return impl_->column_datatype_name(column_name);
}

int result::column_c_datatype(short column) const
{
    return impl_->column_c_datatype(column);
}

int result::column_c_datatype(const string& column_name) const
{
    return impl_->column_c_datatype(column_name);
}

bool result::next_result()
{
    return impl_->next_result();
}

template <class T>
void result::get_ref(short column, T& result) const
{
    return impl_->get_ref<T>(column, result);
}

template <class T>
void result::get_ref(short column, const T& fallback, T& result) const
{
    return impl_->get_ref<T>(column, fallback, result);
}

template <class T>
void result::get_ref(const string& column_name, T& result) const
{
    return impl_->get_ref<T>(column_name, result);
}

template <class T>
void result::get_ref(const string& column_name, const T& fallback, T& result) const
{
    return impl_->get_ref<T>(column_name, fallback, result);
}

template <class T>
T result::get(short column) const
{
    return impl_->get<T>(column);
}

template <class T>
T result::get(short column, const T& fallback) const
{
    return impl_->get<T>(column, fallback);
}

template <class T>
T result::get(const string& column_name) const
{
    return impl_->get<T>(column_name);
}

template <class T>
T result::get(const string& column_name, const T& fallback) const
{
    return impl_->get<T>(column_name, fallback);
}

result::operator bool() const
{
    return static_cast<bool>(impl_);
}

// The following are the only supported instantiations of result::get_ref().
template void result::get_ref(short, string::value_type&) const;
template void result::get_ref(short, short&) const;
template void result::get_ref(short, unsigned short&) const;
template void result::get_ref(short, int&) const;
template void result::get_ref(short, unsigned int&) const;
template void result::get_ref(short, long int&) const;
template void result::get_ref(short, unsigned long int&) const;
template void result::get_ref(short, long long int&) const;
template void result::get_ref(short, unsigned long long int&) const;
template void result::get_ref(short, float&) const;
template void result::get_ref(short, double&) const;
template void result::get_ref(short, string&) const;
template void result::get_ref(short, date&) const;
template void result::get_ref(short, time&) const;
template void result::get_ref(short, timestamp&) const;
template void result::get_ref(short, std::vector<std::uint8_t>&) const;

template void result::get_ref(const string&, string::value_type&) const;
template void result::get_ref(const string&, short&) const;
template void result::get_ref(const string&, unsigned short&) const;
template void result::get_ref(const string&, int&) const;
template void result::get_ref(const string&, unsigned int&) const;
template void result::get_ref(const string&, long int&) const;
template void result::get_ref(const string&, unsigned long int&) const;
template void result::get_ref(const string&, long long int&) const;
template void result::get_ref(const string&, unsigned long long int&) const;
template void result::get_ref(const string&, float&) const;
template void result::get_ref(const string&, double&) const;
template void result::get_ref(const string&, string&) const;
template void result::get_ref(const string&, date&) const;
template void result::get_ref(const string&, time&) const;
template void result::get_ref(const string&, timestamp&) const;
template void result::get_ref(const string&, std::vector<std::uint8_t>&) const;

// The following are the only supported instantiations of result::get_ref() with fallback.
template void result::get_ref(short, const string::value_type&, string::value_type&) const;
template void result::get_ref(short, const short&, short&) const;
template void result::get_ref(short, const unsigned short&, unsigned short&) const;
template void result::get_ref(short, const int&, int&) const;
template void result::get_ref(short, const unsigned int&, unsigned int&) const;
template void result::get_ref(short, const long int&, long int&) const;
template void result::get_ref(short, const unsigned long int&, unsigned long int&) const;
template void result::get_ref(short, const long long int&, long long int&) const;
template void result::get_ref(short, const unsigned long long int&, unsigned long long int&) const;
template void result::get_ref(short, const float&, float&) const;
template void result::get_ref(short, const double&, double&) const;
template void result::get_ref(short, const string&, string&) const;
template void result::get_ref(short, const date&, date&) const;
template void result::get_ref(short, const time&, time&) const;
template void result::get_ref(short, const timestamp&, timestamp&) const;
template void
result::get_ref(short, const std::vector<std::uint8_t>&, std::vector<std::uint8_t>&) const;

template void result::get_ref(const string&, const string::value_type&, string::value_type&) const;
template void result::get_ref(const string&, const short&, short&) const;
template void result::get_ref(const string&, const unsigned short&, unsigned short&) const;
template void result::get_ref(const string&, const int&, int&) const;
template void result::get_ref(const string&, const unsigned int&, unsigned int&) const;
template void result::get_ref(const string&, const long int&, long int&) const;
template void result::get_ref(const string&, const unsigned long int&, unsigned long int&) const;
template void result::get_ref(const string&, const long long int&, long long int&) const;
template void
result::get_ref(const string&, const unsigned long long int&, unsigned long long int&) const;
template void result::get_ref(const string&, const float&, float&) const;
template void result::get_ref(const string&, const double&, double&) const;
template void result::get_ref(const string&, const string&, string&) const;
template void result::get_ref(const string&, const date&, date&) const;
template void result::get_ref(const string&, const time&, time&) const;
template void result::get_ref(const string&, const timestamp&, timestamp&) const;
template void
result::get_ref(const string&, const std::vector<std::uint8_t>&, std::vector<std::uint8_t>&) const;

// The following are the only supported instantiations of result::get().
template string::value_type result::get(short) const;
template short result::get(short) const;
template unsigned short result::get(short) const;
template int result::get(short) const;
template unsigned int result::get(short) const;
template long int result::get(short) const;
template unsigned long int result::get(short) const;
template long long int result::get(short) const;
template unsigned long long int result::get(short) const;
template float result::get(short) const;
template double result::get(short) const;
template string result::get(short) const;
template date result::get(short) const;
template time result::get(short) const;
template timestamp result::get(short) const;
template std::vector<std::uint8_t> result::get(short) const;

template string::value_type result::get(const string&) const;
template short result::get(const string&) const;
template unsigned short result::get(const string&) const;
template int result::get(const string&) const;
template unsigned int result::get(const string&) const;
template long int result::get(const string&) const;
template unsigned long int result::get(const string&) const;
template long long int result::get(const string&) const;
template unsigned long long int result::get(const string&) const;
template float result::get(const string&) const;
template double result::get(const string&) const;
template string result::get(const string&) const;
template date result::get(const string&) const;
template time result::get(const string&) const;
template timestamp result::get(const string&) const;
template std::vector<std::uint8_t> result::get(const string&) const;

// The following are the only supported instantiations of result::get() with fallback.
template string::value_type result::get(short, const string::value_type&) const;
template short result::get(short, const short&) const;
template unsigned short result::get(short, const unsigned short&) const;
template int result::get(short, const int&) const;
template unsigned int result::get(short, const unsigned int&) const;
template long int result::get(short, const long int&) const;
template unsigned long int result::get(short, const unsigned long int&) const;
template long long int result::get(short, const long long int&) const;
template unsigned long long int result::get(short, const unsigned long long int&) const;
template float result::get(short, const float&) const;
template double result::get(short, const double&) const;
template string result::get(short, const string&) const;
template date result::get(short, const date&) const;
template time result::get(short, const time&) const;
template timestamp result::get(short, const timestamp&) const;
template std::vector<std::uint8_t> result::get(short, const std::vector<std::uint8_t>&) const;

template string::value_type result::get(const string&, const string::value_type&) const;
template short result::get(const string&, const short&) const;
template unsigned short result::get(const string&, const unsigned short&) const;
template int result::get(const string&, const int&) const;
template unsigned int result::get(const string&, const unsigned int&) const;
template long int result::get(const string&, const long int&) const;
template unsigned long int result::get(const string&, const unsigned long int&) const;
template long long int result::get(const string&, const long long int&) const;
template unsigned long long int result::get(const string&, const unsigned long long int&) const;
template float result::get(const string&, const float&) const;
template double result::get(const string&, const double&) const;
template string result::get(const string&, const string&) const;
template date result::get(const string&, const date&) const;
template time result::get(const string&, const time&) const;
template timestamp result::get(const string&, const timestamp&) const;
template std::vector<std::uint8_t>
result::get(const string&, const std::vector<std::uint8_t>&) const;

} // namespace nanodbc

#undef NANODBC_THROW_DATABASE_ERROR
#undef NANODBC_STRINGIZE
#undef NANODBC_STRINGIZE_I
#undef NANODBC_CALL_RC
#undef NANODBC_CALL

#endif // DOXYGEN
