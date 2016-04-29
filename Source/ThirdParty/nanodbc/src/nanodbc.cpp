//! \file nanodbc.cpp Implementation details.
#ifndef DOXYGEN

// ASCII art banners are helpful for code editors with a minimap display.
// Generated with http://patorjk.com/software/taag/#p=display&v=0&f=Colossal

#include "nanodbc.h"

#include <algorithm>
#include <clocale>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <map>

#ifndef __clang__
    #include <cstdint>
#endif

// User may redefine NANODBC_ASSERT macro in nanodbc.h
#ifndef NANODBC_ASSERT
    #include <cassert>
    #define NANODBC_ASSERT(expr) assert(expr)
#endif

#ifdef NANODBC_USE_BOOST_CONVERT
    #include <boost/locale/encoding_utf.hpp>
#else
    #include <codecvt>
#endif

#if defined(_MSC_VER) && _MSC_VER <= 1800
    // silence spurious Visual C++ warnings
    #pragma warning(disable:4244) // warning about integer conversion issues.
    #pragma warning(disable:4312) // warning about 64-bit portability issues.
    #pragma warning(disable:4996) // warning about snprintf() deprecated.
#endif

#ifdef __APPLE__
    // silence spurious OS X deprecation warnings
    #define MAC_OS_X_VERSION_MIN_REQUIRED MAC_OS_X_VERSION_10_6
#endif

#ifdef _WIN32
    // needs to be included above sql.h for windows
    #define NOMINMAX
    #include <windows.h>
#endif

#include <sql.h>
#include <sqlext.h>

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

// 888     888          d8b                       888
// 888     888          Y8P                       888
// 888     888                                    888
// 888     888 88888b.  888  .d8888b .d88b.   .d88888  .d88b.
// 888     888 888 "88b 888 d88P"   d88""88b d88" 888 d8P  Y8b
// 888     888 888  888 888 888     888  888 888  888 88888888
// Y88b. .d88P 888  888 888 Y88b.   Y88..88P Y88b 888 Y8b.
//  "Y88888P"  888  888 888  "Y8888P "Y88P"   "Y88888  "Y8888
// MARK: Unicode -

#ifdef NANODBC_USE_UNICODE
    #ifdef NANODBC_USE_IODBC_WIDE_STRINGS
        #define NANODBC_TEXT(s) U ## s
    #else
        #define NANODBC_TEXT(s) u ## s
    #endif
    #define NANODBC_FUNC(f) f ## W
    #define NANODBC_SQLCHAR SQLWCHAR
#else
    #define NANODBC_TEXT(s) s
    #define NANODBC_FUNC(f) f
    #define NANODBC_SQLCHAR SQLCHAR
#endif

#ifdef NANODBC_USE_IODBC_WIDE_STRINGS
    typedef std::u32string wide_string_type;
    #define NANODBC_CODECVT_TYPE std::codecvt_utf8
#else
    typedef std::u16string wide_string_type;
    #define NANODBC_CODECVT_TYPE std::codecvt_utf8_utf16
#endif
typedef wide_string_type::value_type wide_char_t;

#if defined(_MSC_VER)
    #ifndef NANODBC_USE_UNICODE
        // Disable unicode in sqlucode.h on Windows when NANODBC_USE_UNICODE
        // is not defined. This is required because unicode is enabled by
        // default on many Windows systems.
        #define SQL_NOUNICODEMAP
    #endif
#endif

//  .d88888b.  8888888b.  888888b.    .d8888b.       888b     d888
// d88P" "Y88b 888  "Y88b 888  "88b  d88P  Y88b      8888b   d8888
// 888     888 888    888 888  .88P  888    888      88888b.d88888
// 888     888 888    888 8888888K.  888             888Y88888P888  8888b.   .d8888b 888d888 .d88b.  .d8888b
// 888     888 888    888 888  "Y88b 888             888 Y888P 888     "88b d88P"    888P"  d88""88b 88K
// 888     888 888    888 888    888 888    888      888  Y8P  888 .d888888 888      888    888  888 "Y8888b.
// Y88b. .d88P 888  .d88P 888   d88P Y88b  d88P      888   "   888 888  888 Y88b.    888    Y88..88P      X88
//  "Y88888P"  8888888P"  8888888P"   "Y8888P"       888       888 "Y888888  "Y8888P 888     "Y88P"   88888P'
// MARK: ODBC Macros -

#define NANODBC_STRINGIZE_I(text) #text
#define NANODBC_STRINGIZE(text) NANODBC_STRINGIZE_I(text)

// By making all calls to ODBC functions through this macro, we can easily get
// runtime debugging information of which ODBC functions are being called,
// in what order, and with what parameters by defining NANODBC_ODBC_API_DEBUG.
#ifdef NANODBC_ODBC_API_DEBUG
    #include <iostream>
    #define NANODBC_CALL_RC(FUNC, RC, ...)                                    \
        do                                                                    \
        {                                                                     \
            std::cerr << __FILE__ ":" NANODBC_STRINGIZE(__LINE__) " "         \
                NANODBC_STRINGIZE(FUNC) "(" #__VA_ARGS__ ")" << std::endl;    \
            RC = FUNC(__VA_ARGS__);                                           \
        } while(false)                                                        \
        /**/
    #define NANODBC_CALL(FUNC, ...)                                           \
        do                                                                    \
        {                                                                     \
            std::cerr << __FILE__ ":" NANODBC_STRINGIZE(__LINE__) " "         \
                NANODBC_STRINGIZE(FUNC) "(" #__VA_ARGS__ ")" << std::endl;    \
            FUNC(__VA_ARGS__);                                                \
        } while(false)                                                        \
        /**/
#else
    #define NANODBC_CALL_RC(FUNC, RC, ...) RC = FUNC(__VA_ARGS__)
    #define NANODBC_CALL(FUNC, ...) FUNC(__VA_ARGS__)
#endif

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

namespace
{
    #ifdef NANODBC_ODBC_API_DEBUG
        inline nanodbc::string_type return_code(RETCODE rc)
        {
            switch(rc)
            {
                case SQL_SUCCESS: return NANODBC_TEXT("SQL_SUCCESS");
                case SQL_SUCCESS_WITH_INFO: return NANODBC_TEXT("SQL_SUCCESS_WITH_INFO");
                case SQL_ERROR: return NANODBC_TEXT("SQL_ERROR");
                case SQL_INVALID_HANDLE: return NANODBC_TEXT("SQL_INVALID_HANDLE");
                case SQL_NO_DATA: return NANODBC_TEXT("SQL_NO_DATA");
                case SQL_NEED_DATA: return NANODBC_TEXT("SQL_NEED_DATA");
                case SQL_STILL_EXECUTING: return NANODBC_TEXT("SQL_STILL_EXECUTING");
            }
            NANODBC_ASSERT(0);
            return "unknown"; // should never make it here
        }
    #endif

    // Easy way to check if a return code signifies success.
    inline bool success(RETCODE rc)
    {
        #ifdef NANODBC_ODBC_API_DEBUG
            std::cerr << "<-- rc: " << return_code(rc) << " | ";
        #endif
        return rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO;
    }

    // Returns the array size.
    template<typename T, std::size_t N>
    inline std::size_t arrlen(T(&)[N])
    {
        return N;
    }

    // Operates like strlen() on a character array.
    template<typename T, std::size_t N>
    inline std::size_t strarrlen(T(&a)[N])
    {
        const T* s = &a[0];
        std::size_t i = 0;
        while(*s++ && i < N) i++;
        return i;
    }

    inline void convert(const wide_string_type& in, std::string& out)
    {
        #ifdef NANODBC_USE_BOOST_CONVERT
            using boost::locale::conv::utf_to_utf;
            out = utf_to_utf<char>(in.c_str(), in.c_str() + in.size());
        #else
            #if defined(_MSC_VER) && (_MSC_VER == 1900)
                // Workaround for confirmed bug in VS2015.
                // See: https://social.msdn.microsoft.com/Forums/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error
                #ifdef NANODBC_USE_IODBC_WIDE_STRINGS
                    auto p = reinterpret_cast<int32_t const*>(in.data());
                    out = std::wstring_convert<NANODBC_CODECVT_TYPE<int32_t>, int32_t>().to_bytes(p, p + in.size());
                #else
                    auto p = reinterpret_cast<int16_t const*>(in.data());
                    out = std::wstring_convert<NANODBC_CODECVT_TYPE<int16_t>, int16_t>().to_bytes(p, p + in.size());
                #endif
            #else
                out = std::wstring_convert<NANODBC_CODECVT_TYPE<wide_char_t>, wide_char_t>().to_bytes(in);
            #endif
        #endif
    }

    #ifdef NANODBC_USE_UNICODE
        inline void convert(const std::string& in, wide_string_type& out)
        {
            #ifdef NANODBC_USE_BOOST_CONVERT
                using boost::locale::conv::utf_to_utf;
                out = utf_to_utf<wide_char_t>(in.c_str(), in.c_str() + in.size());
            #elif defined(_MSC_VER) && (_MSC_VER == 1900)
                // Workaround for confirmed bug in VS2015.
                // See: https://social.msdn.microsoft.com/Forums/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error
                #ifdef NANODBC_USE_IODBC_WIDE_STRINGS
                    auto s = std::wstring_convert<NANODBC_CODECVT_TYPE<int32_t>, int32_t>().from_bytes(in);
                    auto p = reinterpret_cast<int32_t const*>(s.data());
                #else
                    auto s = std::wstring_convert<NANODBC_CODECVT_TYPE<int16_t>, int16_t>().from_bytes(in);
                    auto p = reinterpret_cast<int16_t const*>(s.data());
                #endif
                out.assign(p, p + s.size());
            #else
                out = std::wstring_convert<NANODBC_CODECVT_TYPE<wide_char_t>, wide_char_t>().from_bytes(in);
            #endif
        }

        inline void convert(const wide_string_type& in, wide_string_type& out)
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
    inline std::string recent_error(
        SQLHANDLE handle
        , SQLSMALLINT handle_type
        , long &native
        , std::string &state)
    {
        nanodbc::string_type result;
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
                NANODBC_FUNC(SQLGetDiagRec)
                , rc
                , handle_type
                , handle
                , (SQLSMALLINT)i
                , sql_state
                , &native_error
                , 0
                , 0
                , &total_bytes);

            if(success(rc) && total_bytes > 0)
                sql_message.resize(total_bytes + 1);

            if(rc == SQL_NO_DATA)
                break;

            NANODBC_CALL_RC(
                NANODBC_FUNC(SQLGetDiagRec)
                , rc
                , handle_type
                , handle
                , (SQLSMALLINT)i
                , sql_state
                , &native_error
                , sql_message.data()
                , (SQLSMALLINT)sql_message.size()
                , &total_bytes);

            if(!success(rc))
            {
                convert(result, rvalue);
                return rvalue;
            }

            if(!result.empty())
                result += ' ';

            result += nanodbc::string_type(sql_message.begin(), sql_message.end());
            i++;

            // NOTE: unixODBC using PostgreSQL and SQLite drivers crash if you call SQLGetDiagRec()
            // more than once. So as a (terrible but the best possible) workaround just exit
            // this loop early on non-Windows systems.
            #ifndef _MSC_VER
                break;
            #endif
        } while(rc != SQL_NO_DATA);

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
    : std::runtime_error("type incompatible") { }

    const char* type_incompatible_error::what() const NANODBC_NOEXCEPT
    {
        return std::runtime_error::what();
    }

    null_access_error::null_access_error()
    : std::runtime_error("null access") { }

    const char* null_access_error::what() const NANODBC_NOEXCEPT
    {
        return std::runtime_error::what();
    }

    index_range_error::index_range_error()
    : std::runtime_error("index out of range") { }

    const char* index_range_error::what() const NANODBC_NOEXCEPT
    {
        return std::runtime_error::what();
    }

    programming_error::programming_error(const std::string& info)
    : std::runtime_error(info.c_str()) { }

    const char* programming_error::what() const NANODBC_NOEXCEPT
    {
        return std::runtime_error::what();
    }

    database_error::database_error(void* handle, short handle_type, const std::string& info)
    : std::runtime_error(info), native_error(0), sql_state("00000")
    {
        message = std::string(std::runtime_error::what()) + recent_error(handle, handle_type, native_error, sql_state);
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
#define NANODBC_THROW_DATABASE_ERROR(handle, handle_type)                     \
    throw nanodbc::database_error(                                            \
        handle                                                                \
        , handle_type                                                         \
        , __FILE__ ":" NANODBC_STRINGIZE(__LINE__) ": ")                      \
    /**/

// 8888888b.           888             d8b 888
// 888  "Y88b          888             Y8P 888
// 888    888          888                 888
// 888    888  .d88b.  888888  8888b.  888 888 .d8888b
// 888    888 d8P  Y8b 888        "88b 888 888 88K
// 888    888 88888888 888    .d888888 888 888 "Y8888b.
// 888  .d88P Y8b.     Y88b.  888  888 888 888      X88
// 8888888P"   "Y8888   "Y888 "Y888888 888 888  88888P'
// MARK: Details -

namespace
{
    using namespace std; // if int64_t is in std namespace (in c++11)

    // A utility for calculating the ctype from the given type T.
    // I essentially create a lookup table based on the MSDN ODBC documentation.
    // See http://msdn.microsoft.com/en-us/library/windows/desktop/ms714556(v=vs.85).aspx
    template<class T>
    struct sql_ctype { };

    template<>
    struct sql_ctype<nanodbc::string_type::value_type>
    {
        #ifdef NANODBC_USE_UNICODE
            static const SQLSMALLINT value = SQL_C_WCHAR;
        #else
            static const SQLSMALLINT value = SQL_C_CHAR;
        #endif
    };

    template<>
    struct sql_ctype<short>
    {
        static const SQLSMALLINT value = SQL_C_SSHORT;
    };

    template<>
    struct sql_ctype<unsigned short>
    {
        static const SQLSMALLINT value = SQL_C_USHORT;
    };

    template<>
    struct sql_ctype<int32_t>
    {
        static const SQLSMALLINT value = SQL_C_SLONG;
    };

    template<>
    struct sql_ctype<uint32_t>
    {
        static const SQLSMALLINT value = SQL_C_ULONG;
    };

    template<>
    struct sql_ctype<int64_t>
    {
        static const SQLSMALLINT value = SQL_C_SBIGINT;
    };

    template<>
    struct sql_ctype<uint64_t>
    {
        static const SQLSMALLINT value = SQL_C_UBIGINT;
    };

    template<>
    struct sql_ctype<float>
    {
        static const SQLSMALLINT value = SQL_C_FLOAT;
    };

    template<>
    struct sql_ctype<double>
    {
        static const SQLSMALLINT value = SQL_C_DOUBLE;
    };

    template<>
    struct sql_ctype<nanodbc::string_type>
    {
        #ifdef NANODBC_USE_UNICODE
            static const SQLSMALLINT value = SQL_C_WCHAR;
        #else
            static const SQLSMALLINT value = SQL_C_CHAR;
        #endif
    };

    template<>
    struct sql_ctype<nanodbc::date>
    {
        static const SQLSMALLINT value = SQL_C_DATE;
    };

    template<>
    struct sql_ctype<nanodbc::timestamp>
    {
        static const SQLSMALLINT value = SQL_C_TIMESTAMP;
    };

    // Encapsulates resources needed for column binding.
    class bound_column
    {
    public:
        bound_column(const bound_column& rhs) =delete;
        bound_column& operator=(bound_column rhs) =delete;

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
        nanodbc::string_type name_;
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

    // Allocates the native ODBC handles.
    inline void allocate_handle(SQLHENV& env, SQLHDBC& conn)
    {
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLAllocHandle
            , rc
            , SQL_HANDLE_ENV
            , SQL_NULL_HANDLE
            , &env);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(env, SQL_HANDLE_ENV);

        try
        {
            NANODBC_CALL_RC(
                SQLSetEnvAttr
                , rc
                , env
                , SQL_ATTR_ODBC_VERSION
                , (SQLPOINTER)NANODBC_ODBC_VERSION
                , SQL_IS_UINTEGER);
            if(!success(rc))
                NANODBC_THROW_DATABASE_ERROR(env, SQL_HANDLE_ENV);

            NANODBC_CALL_RC(
                SQLAllocHandle
                , rc
                , SQL_HANDLE_DBC
                , env
                , &conn);
            if(!success(rc))
                NANODBC_THROW_DATABASE_ERROR(env, SQL_HANDLE_ENV);
        }
        catch(...)
        {
            NANODBC_CALL(
                SQLFreeHandle
                , SQL_HANDLE_ENV
                , env);
            throw;
        }
    }
} // namespace

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

namespace nanodbc
{

class connection::connection_impl
{
public:
    connection_impl(const connection_impl&) =delete;
    connection_impl& operator=(const connection_impl&) =delete;

    connection_impl()
    : env_(0)
    , conn_(0)
    , connected_(false)
    , transactions_(0)
    , rollback_(false)
    {
        allocate_handle(env_, conn_);
    }

    connection_impl(
        const string_type& dsn
        , const string_type& user
        , const string_type& pass
        , long timeout)
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
        catch(...)
        {
            NANODBC_CALL(
                SQLFreeHandle
                , SQL_HANDLE_DBC
                , conn_);
            NANODBC_CALL(
                SQLFreeHandle
                , SQL_HANDLE_ENV
                , env_);
            throw;
        }
    }

    connection_impl(const string_type& connection_string, long timeout)
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
        catch(...)
        {
            NANODBC_CALL(
                SQLFreeHandle
                , SQL_HANDLE_DBC
                , conn_);
            NANODBC_CALL(
                SQLFreeHandle
                , SQL_HANDLE_ENV
                , env_);
            throw;
        }
    }

    ~connection_impl() NANODBC_NOEXCEPT
    {
        try
        {
            disconnect();
        }
        catch(...)
        {
            // ignore exceptions thrown during disconnect
        }
        NANODBC_CALL(
            SQLFreeHandle
            , SQL_HANDLE_DBC
            , conn_);
        NANODBC_CALL(
            SQLFreeHandle
            , SQL_HANDLE_ENV
            , env_);
    }

#ifdef SQL_ATTR_ASYNC_DBC_EVENT
    void enable_async(void* event_handle)
    {
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLSetConnectAttr
            , rc
            , conn_
            , SQL_ATTR_ASYNC_DBC_FUNCTIONS_ENABLE
            , (SQLPOINTER)SQL_ASYNC_DBC_ENABLE_ON
            , SQL_IS_INTEGER);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        NANODBC_CALL_RC(
            SQLSetConnectAttr
            , rc
            , conn_
            , SQL_ATTR_ASYNC_DBC_EVENT
            , event_handle
            , SQL_IS_POINTER);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);
    }

    void async_complete()
    {
        RETCODE rc, arc;
        NANODBC_CALL_RC(
            SQLCompleteAsync
            , rc
            , SQL_HANDLE_DBC
            , conn_
            , &arc);
        if(!success(rc) || !success(arc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        NANODBC_CALL_RC(
            SQLSetConnectAttr
            , rc
            , conn_
            , SQL_ATTR_ASYNC_ENABLE
            , (SQLPOINTER)SQL_ASYNC_ENABLE_OFF
            , SQL_IS_INTEGER);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        connected_ = success(rc);
    }
#endif // SQL_ATTR_ASYNC_DBC_EVENT

    void connect(
        const string_type& dsn
        , const string_type& user
        , const string_type& pass
        , long timeout
        , void* event_handle = NULL)
    {
        disconnect();

        RETCODE rc;
        NANODBC_CALL_RC(
            SQLFreeHandle
            , rc
            , SQL_HANDLE_DBC
            , conn_);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        NANODBC_CALL_RC(
            SQLAllocHandle
            , rc
            , SQL_HANDLE_DBC
            , env_
            , &conn_);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(env_, SQL_HANDLE_ENV);

        NANODBC_CALL_RC(
            SQLSetConnectAttr
            , rc
            , conn_
            , SQL_LOGIN_TIMEOUT
            , (SQLPOINTER)(std::intptr_t)timeout
            , 0);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        #ifdef SQL_ATTR_ASYNC_DBC_EVENT
            if(event_handle != NULL)
                enable_async(event_handle);
        #endif

        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLConnect)
            , rc
            , conn_
            , (NANODBC_SQLCHAR*)dsn.c_str(), SQL_NTS
            , !user.empty() ? (NANODBC_SQLCHAR*)user.c_str() : 0, SQL_NTS
            , !pass.empty() ? (NANODBC_SQLCHAR*)pass.c_str() : 0, SQL_NTS);
        if(!success(rc) && (event_handle == NULL || rc != SQL_STILL_EXECUTING))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        connected_ = success(rc);
    }

    void connect(const string_type& connection_string, long timeout, void* event_handle = NULL)
    {
        disconnect();

        RETCODE rc;
        NANODBC_CALL_RC(
            SQLFreeHandle
            , rc
            , SQL_HANDLE_DBC
            , conn_);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        NANODBC_CALL_RC(
            SQLAllocHandle
            , rc
            , SQL_HANDLE_DBC
            , env_
            , &conn_);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(env_, SQL_HANDLE_ENV);

        NANODBC_CALL_RC(
            SQLSetConnectAttr
            , rc
            , conn_
            , SQL_LOGIN_TIMEOUT
            , (SQLPOINTER)(std::intptr_t)timeout
            , 0);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        #ifdef SQL_ATTR_ASYNC_DBC_EVENT
            if(event_handle != NULL)
                enable_async(event_handle);
        #endif

        NANODBC_SQLCHAR dsn[1024];
        SQLSMALLINT dsn_size = 0;
        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLDriverConnect)
            , rc
            , conn_
            , 0
            , (NANODBC_SQLCHAR*)connection_string.c_str(), SQL_NTS
            , dsn
            , sizeof(dsn) / sizeof(NANODBC_SQLCHAR)
            , &dsn_size
            , SQL_DRIVER_NOPROMPT);
        if(!success(rc) && (event_handle == NULL || rc != SQL_STILL_EXECUTING))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);

        connected_ = success(rc);
    }

    bool connected() const
    {
        return connected_;
    }

    void disconnect()
    {
        if(connected())
        {
            RETCODE rc;
            NANODBC_CALL_RC(
                SQLDisconnect
                , rc
                , conn_);
            if(!success(rc))
                NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);
        }
        connected_ = false;
    }

    std::size_t transactions() const
    {
        return transactions_;
    }

    void* native_dbc_handle() const
    {
        return conn_;
    }

    void* native_env_handle() const
    {
        return env_;
    }

    string_type dbms_name() const
    {
        NANODBC_SQLCHAR name[255] = { 0 };
        SQLSMALLINT length(0);
        RETCODE rc;
        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLGetInfo)
            , rc
            , conn_
            , SQL_DBMS_NAME
            , name
            , sizeof(name) / sizeof(NANODBC_SQLCHAR)
            , &length);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);
        return string_type(&name[0], &name[strarrlen(name)]);
    }

    string_type dbms_version() const
    {
        NANODBC_SQLCHAR version[255] = { 0 };
        SQLSMALLINT length(0);
        RETCODE rc;
        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLGetInfo)
            , rc
            , conn_
            , SQL_DBMS_VER
            , version
            , sizeof(version) / sizeof(NANODBC_SQLCHAR)
            , &length);
        if (!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);
        return string_type(&version[0], &version[strarrlen(version)]);
    }

    string_type driver_name() const
    {
        NANODBC_SQLCHAR name[1024];
        SQLSMALLINT length;
        RETCODE rc;
        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLGetInfo)
            , rc
            , conn_
            , SQL_DRIVER_NAME
            , name
            , sizeof(name) / sizeof(NANODBC_SQLCHAR)
            , &length);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);
        return string_type(&name[0], &name[strarrlen(name)]);
    }

    string_type database_name() const
    {
        // FIXME: Allocate buffer of dynamic size as drivers do not agree on universal size
        // MySQL driver limits MAX_NAME_LEN=255
        // PostgreSQL driver MAX_INFO_STIRNG=128
        // MFC CDatabase allocates buffer dynamically.
        NANODBC_SQLCHAR name[255] = { 0 };
        SQLSMALLINT length(0);
        RETCODE rc;
        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLGetInfo)
            , rc
            , conn_
            , SQL_DATABASE_NAME
            , name
            , sizeof(name) / sizeof(NANODBC_SQLCHAR)
            , &length);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);
        return string_type(&name[0], &name[strarrlen(name)]);
    }

    string_type catalog_name() const
    {
        NANODBC_SQLCHAR name[SQL_MAX_OPTION_STRING_LENGTH] = { 0 };
        SQLINTEGER length(0);
        RETCODE rc;
        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLGetConnectAttr)
            , rc
            , conn_
            , SQL_ATTR_CURRENT_CATALOG
            , name
            , sizeof(name) / sizeof(NANODBC_SQLCHAR)
            , &length);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(conn_, SQL_HANDLE_DBC);
        return string_type(&name[0], &name[strarrlen(name)]);
    }


    std::size_t ref_transaction()
    {
        return --transactions_;
    }

    std::size_t unref_transaction()
    {
        return ++transactions_;
    }

    bool rollback() const
    {
        return rollback_;
    }

    void rollback(bool onoff)
    {
        rollback_ = onoff;
    }

private:
    HENV env_;
    HDBC conn_;
    bool connected_;
    std::size_t transactions_;
    bool rollback_; // if true, this connection is marked for eventual transaction rollback
};

} // namespace nanodbc

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

namespace nanodbc
{

class transaction::transaction_impl
{
public:
    transaction_impl(const transaction_impl&) =delete;
    transaction_impl& operator=(const transaction_impl&) =delete;

    transaction_impl(const class connection& conn)
    : conn_(conn)
    , committed_(false)
    {
        if(conn_.transactions() == 0 && conn_.connected())
        {
            RETCODE rc;
            NANODBC_CALL_RC(
                SQLSetConnectAttr
                , rc
                , conn_.native_dbc_handle()
                , SQL_ATTR_AUTOCOMMIT
                , (SQLPOINTER)SQL_AUTOCOMMIT_OFF
                , SQL_IS_UINTEGER);
            if(!success(rc))
                NANODBC_THROW_DATABASE_ERROR(conn_.native_dbc_handle(), SQL_HANDLE_DBC);
        }
        conn_.ref_transaction();
    }

    ~transaction_impl() NANODBC_NOEXCEPT
    {
        if(!committed_)
        {
            conn_.rollback(true);
            conn_.unref_transaction();
        }

        if(conn_.transactions() == 0 && conn_.connected())
        {
            if(conn_.rollback())
            {
                NANODBC_CALL(
                    SQLEndTran
                    , SQL_HANDLE_DBC
                    , conn_.native_dbc_handle()
                    , SQL_ROLLBACK);
                conn_.rollback(false);
            }

            NANODBC_CALL(
                SQLSetConnectAttr
                , conn_.native_dbc_handle()
                , SQL_ATTR_AUTOCOMMIT
                , (SQLPOINTER)SQL_AUTOCOMMIT_ON
                , SQL_IS_UINTEGER);
        }
    }

    void commit()
    {
        if(committed_)
            return;
        committed_ = true;
        if(conn_.unref_transaction() == 0 && conn_.connected())
        {
            RETCODE rc;
            NANODBC_CALL_RC(
                SQLEndTran
                , rc
                , SQL_HANDLE_DBC
                , conn_.native_dbc_handle()
                , SQL_COMMIT);
            if(!success(rc))
                NANODBC_THROW_DATABASE_ERROR(conn_.native_dbc_handle(), SQL_HANDLE_DBC);
        }
    }

    void rollback() NANODBC_NOEXCEPT
    {
        if(committed_)
            return;
        conn_.rollback(true);
    }

    class connection& connection()
    {
        return conn_;
    }

    const class connection& connection() const
    {
        return conn_;
    }

private:
    class connection conn_;
    bool committed_;
};

} // namespace nanodbc

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

namespace nanodbc
{

class statement::statement_impl
{
public:
    statement_impl(const statement_impl&) =delete;
    statement_impl& operator=(const statement_impl&) =delete;

    statement_impl()
    : stmt_(0)
    , open_(false)
    , conn_()
    , bind_len_or_null_()
    {

    }

    statement_impl(class connection& conn)
    : stmt_(0)
    , open_(false)
    , conn_()
    , bind_len_or_null_()
    {
        open(conn);
    }

    statement_impl(class connection& conn, const string_type& query, long timeout)
    : stmt_(0)
    , open_(false)
    , conn_()
    , bind_len_or_null_()
    {
        prepare(conn, query, timeout);
    }

    ~statement_impl() NANODBC_NOEXCEPT
    {
        if(open() && connected())
        {
            NANODBC_CALL(
                SQLCancel
                , stmt_);
            reset_parameters();
            NANODBC_CALL(
                SQLFreeHandle
                , SQL_HANDLE_STMT
                , stmt_);
        }
    }

    void open(class connection& conn)
    {
        close();
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLAllocHandle
            , rc
            , SQL_HANDLE_STMT
            , conn.native_dbc_handle()
            , &stmt_);
        open_ = success(rc);
        if(!open_)
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        conn_ = conn;
    }

    bool open() const
    {
        return open_;
    }

    bool connected() const
    {
        return conn_.connected();
    }

    const class connection& connection() const
    {
        return conn_;
    }

    class connection& connection()
    {
        return conn_;
    }

    void* native_statement_handle() const
    {
        return stmt_;
    }

    void close()
    {
        if(open() && connected())
        {
            RETCODE rc;
            NANODBC_CALL_RC(
                SQLCancel
                , rc
                , stmt_);
            if(!success(rc))
                NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

            reset_parameters();

            NANODBC_CALL_RC(
                SQLFreeHandle
                , rc
                , SQL_HANDLE_STMT
                , stmt_);
            if(!success(rc))
                NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        }

        open_ = false;
        stmt_ = 0;
    }

    void cancel()
    {
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLCancel
            , rc
            , stmt_);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
    }

    void prepare(class connection& conn, const string_type& query, long timeout)
    {
        open(conn);
        prepare(query, timeout);
    }

    void prepare(const string_type& query, long timeout)
    {
        if(!open())
            throw programming_error("statement has no associated open connection");

        RETCODE rc;
        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLPrepare)
            , rc
            , stmt_
            , (NANODBC_SQLCHAR*)query.c_str()
            , (SQLINTEGER)query.size());
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        this->timeout(timeout);
    }

    void timeout(long timeout)
    {
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLSetStmtAttr
            , rc
            , stmt_
            , SQL_ATTR_QUERY_TIMEOUT
            , (SQLPOINTER)(std::intptr_t)timeout,
             0);

        // some drivers don't support timeout for statements,
        // so only raise the error if a non-default timeout was requested.
        if(!success(rc) && (timeout != 0))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
    }

#if defined(SQL_ATTR_ASYNC_STMT_EVENT) && defined(SQL_API_SQLCOMPLETEASYNC)
    void enable_async(void* event_handle)
    {
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLSetStmtAttr
            , rc
            , stmt_
            , SQL_ATTR_ASYNC_ENABLE
            , (SQLPOINTER)SQL_ASYNC_ENABLE_ON
            , SQL_IS_INTEGER);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        NANODBC_CALL_RC(
            SQLSetStmtAttr
            , rc
            , stmt_
            , SQL_ATTR_ASYNC_STMT_EVENT
            , event_handle
            , SQL_IS_POINTER);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
    }

    void async_execute_direct(
        class connection& conn
        , void* event_handle
        , const string_type& query
        , long batch_operations
        , long timeout
        , statement& statement)
    {
        RETCODE rc = just_execute_direct(
            conn
            , query
            , batch_operations
            , timeout
            , statement
            , event_handle);

        if(rc != SQL_STILL_EXECUTING)
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
    }

    result async_complete(long batch_operations, statement& statement)
    {
        RETCODE rc, arc;
        NANODBC_CALL_RC(
            SQLCompleteAsync
            , rc
            , SQL_HANDLE_STMT
            , stmt_
            , &arc);
        if(!success(rc) || !success(arc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        NANODBC_CALL_RC(
            SQLSetStmtAttr
            , rc
            , stmt_
            , SQL_ATTR_ASYNC_ENABLE
            , (SQLPOINTER)SQL_ASYNC_ENABLE_OFF
            , SQL_IS_INTEGER);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        return result(statement, batch_operations);
    }
#endif // SQL_ATTR_ASYNC_STMT_EVENT && SQL_API_SQLCOMPLETEASYNC

    result execute_direct(
        class connection& conn
        , const string_type& query
        , long batch_operations
        , long timeout
        , statement& statement)
    {
        #ifdef NANODBC_HANDLE_NODATA_BUG
            const RETCODE rc = just_execute_direct(conn, query, batch_operations, timeout, statement);
            if(rc == SQL_NO_DATA)
                return result();
        #else
            just_execute_direct(conn, query, batch_operations, timeout, statement);
        #endif
        return result(statement, batch_operations);
    }

    RETCODE just_execute_direct(
        class connection& conn
        , const string_type& query
        , long batch_operations
        , long timeout
        , statement& /*statement*/
        , void* event_handle = NULL)
    {
        open(conn);

        #if defined(SQL_ATTR_ASYNC_STMT_EVENT) && defined(SQL_API_SQLCOMPLETEASYNC)
            if(event_handle != NULL)
                enable_async(event_handle);
        #endif

        RETCODE rc;
        NANODBC_CALL_RC(
            SQLSetStmtAttr
            , rc
            , stmt_
            , SQL_ATTR_PARAMSET_SIZE
            , (SQLPOINTER)(std::intptr_t)batch_operations
            , 0);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        this->timeout(timeout);

        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLExecDirect)
            , rc
            , stmt_
            , (NANODBC_SQLCHAR*)query.c_str()
            , SQL_NTS);
        if(!success(rc) && rc != SQL_NO_DATA && rc != SQL_STILL_EXECUTING)
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        return rc;
    }

    result execute(long batch_operations, long timeout, statement& statement)
    {
        #ifdef NANODBC_HANDLE_NODATA_BUG
            const RETCODE rc = just_execute(batch_operations, timeout, statement);
            if(rc == SQL_NO_DATA)
                return result();
        #else
            just_execute(batch_operations, timeout, statement);
        #endif
        return result(statement, batch_operations);
    }

    RETCODE just_execute(long batch_operations, long timeout, statement& /*statement*/)
    {
        RETCODE rc;

        if(open())
        {
            // The ODBC cursor must be closed before subsequent executions, as described
            // here http://msdn.microsoft.com/en-us/library/windows/desktop/ms713584%28v=vs.85%29.aspx
            //
            // However, we don't necessarily want to call SQLCloseCursor() because that
            // will cause an invalid cursor state in the case that no cursor is currently open.
            // A better solution is to use SQLFreeStmt() with the SQL_CLOSE option, which has
            // the same effect without the undesired limitations.
            NANODBC_CALL_RC(
                SQLFreeStmt
                , rc
                , stmt_
                , SQL_CLOSE);
            if(!success(rc))
                NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        }

        NANODBC_CALL_RC(
            SQLSetStmtAttr
            , rc
            , stmt_
            , SQL_ATTR_PARAMSET_SIZE
            , (SQLPOINTER)(std::intptr_t)batch_operations
            , 0);
        if(!success(rc) && rc != SQL_NO_DATA)
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        this->timeout(timeout);

        NANODBC_CALL_RC(
            SQLExecute
            , rc
            , stmt_);
        if(!success(rc) && rc != SQL_NO_DATA)
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        return rc;
    }

    result procedure_columns(
        const string_type& catalog
        , const string_type& schema
        , const string_type& procedure
        , const string_type& column
        , statement& statement)
    {
        if(!open())
            throw programming_error("statement has no associated open connection");

        RETCODE rc;
        NANODBC_CALL_RC(
            NANODBC_FUNC(SQLProcedureColumns)
            , rc
            , stmt_
            , (NANODBC_SQLCHAR*)(catalog.empty() ? NULL : catalog.c_str())
            , (catalog.empty() ? 0 : SQL_NTS)
            , (NANODBC_SQLCHAR*)(schema.empty() ? NULL : schema.c_str())
            , (schema.empty() ? 0 : SQL_NTS)
            , (NANODBC_SQLCHAR*)procedure.c_str()
            , SQL_NTS
            , (NANODBC_SQLCHAR*)(column.empty() ? NULL : column.c_str())
            , (column.empty() ? 0 : SQL_NTS));

        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        return result(statement, 1);
    }

    long affected_rows() const
    {
        SQLLEN rows;
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLRowCount
            , rc
            , stmt_
            , &rows);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        NANODBC_ASSERT(rows <= static_cast<SQLLEN>(std::numeric_limits<long>::max()));
        return static_cast<long>(rows);
    }

    short columns() const
    {
        SQLSMALLINT cols;
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLNumResultCols
            , rc
            , stmt_
            , &cols);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        return cols;
    }

    void reset_parameters() NANODBC_NOEXCEPT
    {
        NANODBC_CALL(
            SQLFreeStmt
            , stmt_
            , SQL_RESET_PARAMS);
    }

    unsigned long parameter_size(short param) const
    {
        RETCODE rc;
        SQLSMALLINT data_type;
        SQLSMALLINT nullable;
        SQLULEN parameter_size;
        NANODBC_CALL_RC(
            SQLDescribeParam
            , rc
            , stmt_
            , param + 1
            , &data_type
            , &parameter_size
            , 0
            , &nullable);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
        NANODBC_ASSERT(parameter_size <= static_cast<SQLULEN>(std::numeric_limits<unsigned long>::max()));
        return static_cast<unsigned long>(parameter_size);
    }

    static SQLSMALLINT param_type_from_direction(param_direction direction)
    {
        switch(direction)
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
        short param
        , std::size_t elements
        , param_direction direction
        , SQLSMALLINT& data_type
        , SQLSMALLINT& param_type
        , SQLULEN& parameter_size
        , SQLSMALLINT& scale)
    {
        RETCODE rc;
        SQLSMALLINT nullable;
        NANODBC_CALL_RC(
            SQLDescribeParam
            , rc
            , stmt_
            , param + 1
            , &data_type
            , &parameter_size
            , &scale
            , &nullable);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);

        param_type = param_type_from_direction(direction);

        if(!bind_len_or_null_.count(param))
            bind_len_or_null_[param] = std::vector<null_type>();
        std::vector<null_type>().swap(bind_len_or_null_[param]);

        // ODBC weirdness: this must be at least 8 elements in size
        const std::size_t indicator_size = elements > 8 ? elements : 8;

        bind_len_or_null_[param].reserve(indicator_size);
        bind_len_or_null_[param].assign(indicator_size, SQL_NULL_DATA);
    }

    // calls actual ODBC bind parameter function
    template<class T>
    void bind_parameter(
        short param
        , const T* data
        , std::size_t /*elements*/
        , SQLSMALLINT data_type
        , SQLSMALLINT param_type
        , SQLULEN parameter_size
        , SQLSMALLINT scale)
    {
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLBindParameter
            , rc
            , stmt_ // handle
            , param + 1 // parameter number
            , param_type // input or output type
            , sql_ctype<T>::value // value type
            , data_type // parameter type
            , parameter_size // column size ignored for many types, but needed for strings
            , scale // decimal digits
            , (SQLPOINTER)data // parameter value
            , parameter_size // buffer length
            , bind_len_or_null_[param].data());

        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
    }

    // handles a single value (possibly a single string value), or multiple non-string values
    template<class T>
    void bind(short param, const T* values, std::size_t elements, param_direction direction);

    // handles multiple string values
    void bind_strings(
        short param
        , const string_type::value_type* values
        , std::size_t /*length*/
        , std::size_t elements
        , param_direction direction)
    {
        bind(param, values, elements, direction);
    }

    // handles multiple null values
    void bind_null(short param, std::size_t elements)
    {
        SQLSMALLINT data_type;
        SQLSMALLINT param_type;
        SQLULEN parameter_size;
        SQLSMALLINT scale;
        prepare_bind(param, elements, PARAM_IN, data_type, param_type, parameter_size, scale);

        RETCODE rc;
        NANODBC_CALL_RC(
            SQLBindParameter
            , rc
            , stmt_
            , param + 1
            , param_type
            , SQL_C_CHAR
            , data_type
            , parameter_size // column size ignored for many types, but needed for strings
            , 0
            , (SQLPOINTER)0 // null value
            , 0 // parameter_size
            , bind_len_or_null_[param].data());
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
    }

    // comparator for null sentry values
    template<class T>
    bool equals(const T& lhs, const T& rhs)
    {
        return lhs == rhs;
    }

    // handles multiple non-string values with a null sentry
    template<class T>
    void bind(
        short param
        , const T* values
        , std::size_t elements
        , const bool* nulls
        , const T* null_sentry
        , param_direction direction);

    // handles multiple string values
    void bind_strings(
        short param
        , const string_type::value_type* values
        , std::size_t length
        , std::size_t elements
        , const bool* nulls
        , const string_type::value_type* null_sentry
        , param_direction direction);

private:
    HSTMT stmt_;
    bool open_;
    class connection conn_;
    std::map<short, std::vector<null_type> > bind_len_or_null_;
};

// Supports code like: query.bind(0, std_string.c_str())
// In this case, we need to pass NULL to the final parameter of SQLBindParameter().
template<>
void statement::statement_impl::bind_parameter<string_type::value_type>(
    short param
    , const string_type::value_type* data
    , std::size_t elements
    , SQLSMALLINT data_type
    , SQLSMALLINT param_type
    , SQLULEN parameter_size
    , SQLSMALLINT scale)
{
    RETCODE rc;
    NANODBC_CALL_RC(
        SQLBindParameter
        , rc
        , stmt_ // handle
        , param + 1 // parameter number
        , param_type // input or output type
        , sql_ctype<string_type::value_type>::value // value type
        , data_type // parameter type
        , parameter_size // column size ignored for many types, but needed for strings
        , scale // decimal digits
        , (SQLPOINTER)data // parameter value
        , parameter_size // buffer length
        , (elements <= 1 ? NULL : bind_len_or_null_[param].data()));

    if(!success(rc))
        NANODBC_THROW_DATABASE_ERROR(stmt_, SQL_HANDLE_STMT);
}

template<class T>
void statement::statement_impl::bind(
    short param
    , const T* values
    , std::size_t elements
    , param_direction direction)
{
    SQLSMALLINT data_type;
    SQLSMALLINT param_type;
    SQLULEN parameter_size;
    SQLSMALLINT scale;
    prepare_bind(param, elements, direction, data_type, param_type, parameter_size, scale);

    for(std::size_t i = 0; i < elements; ++i)
        bind_len_or_null_[param][i] = parameter_size;

    bind_parameter(param, values, elements, data_type, param_type, parameter_size, scale);
}

template<class T>
void statement::statement_impl::bind(
    short param
    , const T* values
    , std::size_t elements
    , const bool* nulls
    , const T* null_sentry
    , param_direction direction)
{
    SQLSMALLINT data_type;
    SQLSMALLINT param_type;
    SQLULEN parameter_size;
    SQLSMALLINT scale;
    prepare_bind(param, elements, direction, data_type, param_type, parameter_size, scale);

    for(std::size_t i = 0; i < elements; ++i)
        if((null_sentry && !equals(values[i], *null_sentry)) || (nulls && !nulls[i]))
            bind_len_or_null_[param][i] = parameter_size;

    bind_parameter(param, values, elements, data_type, param_type, parameter_size, scale);
}

void statement::statement_impl::bind_strings(
    short param
    , const string_type::value_type* values
    , std::size_t length
    , std::size_t elements
    , const bool* nulls
    , const string_type::value_type* null_sentry
    , param_direction direction)
{
    SQLSMALLINT data_type;
    SQLSMALLINT param_type;
    SQLULEN parameter_size;
    SQLSMALLINT scale;
    prepare_bind(param, elements, direction, data_type, param_type, parameter_size, scale);

    if(null_sentry)
    {
        for(std::size_t i = 0; i < elements; ++i)
        {
            const string_type s_lhs(values + i * length, values + (i + 1) * length);
            const string_type s_rhs(null_sentry);
            #if NANODBC_USE_UNICODE
                std::string narrow_lhs;
                narrow_lhs.reserve(s_lhs.size());
                convert(s_lhs, narrow_lhs);
                std::string narrow_rhs;
                narrow_rhs.reserve(s_rhs.size());
                convert(s_rhs, narrow_lhs);
                if(std::strncmp(narrow_lhs.c_str(), narrow_rhs.c_str(), length))
                    bind_len_or_null_[param][i] = parameter_size;
            #else
                if(std::strncmp(s_lhs.c_str(), s_rhs.c_str(), length))
                    bind_len_or_null_[param][i] = parameter_size;
            #endif
        }
    }
    else if(nulls)
    {
        for(std::size_t i = 0; i < elements; ++i)
        {
            if(!nulls[i])
                bind_len_or_null_[param][i] = SQL_NTS; // null terminated
        }
    }

    bind_parameter(param, values, elements, data_type, param_type, parameter_size, scale);
}

template<>
bool statement::statement_impl::equals(const date& lhs, const date& rhs)
{
    return lhs.year == rhs.year
        && lhs.month == rhs.month
        && lhs.day == rhs.day;
}

template<>
bool statement::statement_impl::equals(const timestamp& lhs, const timestamp& rhs)
{
    return lhs.year == rhs.year
        && lhs.month == rhs.month
        && lhs.day == rhs.day
        && lhs.hour == rhs.hour
        && lhs.min == rhs.min
        && lhs.sec == rhs.sec
        && lhs.fract == rhs.fract;
}

} // namespace nanodbc

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

namespace nanodbc
{

class result::result_impl
{
public:
    result_impl(const result_impl&) =delete;
    result_impl& operator=(const result_impl&) =delete;

    result_impl(statement stmt, long rowset_size)
    : stmt_(stmt)
    , rowset_size_(rowset_size)
    , row_count_(0)
    , bound_columns_(0)
    , bound_columns_size_(0)
    , rowset_position_(0)
    , bound_columns_by_name_()
    , at_end_(false)
    {
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLSetStmtAttr
            , rc
            , stmt_.native_statement_handle()
            , SQL_ATTR_ROW_ARRAY_SIZE
            , (SQLPOINTER)(std::intptr_t)rowset_size_
            , 0);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);

        NANODBC_CALL_RC(
            SQLSetStmtAttr
            , rc
            , stmt_.native_statement_handle()
            , SQL_ATTR_ROWS_FETCHED_PTR
            , &row_count_
            , 0);
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);

        auto_bind();
    }

    ~result_impl() NANODBC_NOEXCEPT
    {
        cleanup_bound_columns();
    }

    void* native_statement_handle() const
    {
        return stmt_.native_statement_handle();
    }

    long rowset_size() const
    {
        return rowset_size_;
    }

    long affected_rows() const
    {
        return stmt_.affected_rows();
    }

    long rows() const NANODBC_NOEXCEPT
    {
        NANODBC_ASSERT(row_count_ <= static_cast<SQLULEN>(std::numeric_limits<long>::max()));
        return static_cast<long>(row_count_);
    }

    short columns() const
    {
        return stmt_.columns();
    }

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

    bool next()
    {
        if(rows() && ++rowset_position_ < rowset_size_)
            return rowset_position_ < rows();
        rowset_position_ = 0;
        return fetch(0, SQL_FETCH_NEXT);
    }

    bool prior()
    {
        if(rows() && --rowset_position_ >= 0)
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
        if(this->rows() && rowset_position_ < rowset_size_)
            return rowset_position_ < this->rows();
        rowset_position_ = 0;
        return fetch(rows, SQL_FETCH_RELATIVE);
    }

    unsigned long position() const
    {
        SQLULEN pos = 0; // necessary to initialize to 0
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLGetStmtAttr
            , rc
            , stmt_.native_statement_handle()
            , SQL_ATTR_ROW_NUMBER
            , &pos
            , SQL_IS_UINTEGER
            , 0);
        if(!success(rc))
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

        NANODBC_ASSERT(pos <= static_cast<SQLULEN>(std::numeric_limits<unsigned long>::max()));
        return static_cast<unsigned long>(pos) + rowset_position_;
    }

    bool end() const NANODBC_NOEXCEPT
    {
        if(at_end_)
            return true;
        SQLULEN pos = 0; // necessary to initialize to 0
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLGetStmtAttr
            , rc
            , stmt_.native_statement_handle()
            , SQL_ATTR_ROW_NUMBER
            , &pos
            , SQL_IS_UINTEGER
            , 0);
        return (!success(rc) || rows() < 0 || pos - 1 > static_cast<unsigned long>(rows()));
    }

    bool is_null(short column) const
    {
        if(column >= bound_columns_size_)
            throw index_range_error();
        bound_column& col = bound_columns_[column];
        if(rowset_position_ >= rows())
            throw index_range_error();
        return col.cbdata_[rowset_position_] == SQL_NULL_DATA;
    }

    bool is_null(const string_type& column_name) const
    {
        const short column = this->column(column_name);
        return is_null(column);
    }

    string_type column_name(short column) const
    {
        if(column >= bound_columns_size_)
            throw index_range_error();
        return bound_columns_[column].name_;
    }

    long column_size(short column) const
    {
        if(column >= bound_columns_size_)
            throw index_range_error();
        bound_column& col = bound_columns_[column];
        NANODBC_ASSERT(col.sqlsize_ <= static_cast<SQLULEN>(std::numeric_limits<long>::max()));
        return static_cast<long>(col.sqlsize_);
    }

    short column(const string_type& column_name) const
    {
        typedef std::map<string_type, bound_column*>::const_iterator iter;
        iter i = bound_columns_by_name_.find(column_name);
        if(i == bound_columns_by_name_.end())
            throw index_range_error();
        return i->second->column_;
    }

    int column_datatype(short column) const
    {
        if(column >= bound_columns_size_)
            throw index_range_error();
        bound_column& col = bound_columns_[column];
        return col.sqltype_;
    }

    int column_datatype(const string_type& column_name) const
    {
        const short column = this->column(column_name);
        bound_column& col = bound_columns_[column];
        return col.sqltype_;
    }

    int column_c_datatype(short column) const
    {
        if(column >= bound_columns_size_)
            throw index_range_error();
        bound_column& col = bound_columns_[column];
        return col.ctype_;
    }

    int column_c_datatype(const string_type& column_name) const
    {
        const short column = this->column(column_name);
        bound_column& col = bound_columns_[column];
        return col.ctype_;
    }

    bool next_result()
    {
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLMoreResults
            , rc
            , stmt_.native_statement_handle());
        if(rc == SQL_NO_DATA)
            return false;
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);
        auto_bind();
        return true;
    }

    template<class T>
    void get_ref(short column, T& result) const
    {
        if(column >= bound_columns_size_)
            throw index_range_error();
        if(is_null(column))
            throw null_access_error();
        get_ref_impl<T>(column, result);
    }

    template<class T>
    void get_ref(short column, const T& fallback, T& result) const
    {
        if(column >= bound_columns_size_)
            throw index_range_error();
        if(is_null(column))
        {
            result = fallback;
            return;
        }
        get_ref_impl<T>(column, result);
    }

    template<class T>
    void get_ref(const string_type& column_name, T& result) const
    {
        const short column = this->column(column_name);
        if(is_null(column))
            throw null_access_error();
        get_ref_impl<T>(column, result);
    }

    template<class T>
    void get_ref(const string_type& column_name, const T& fallback, T& result) const
    {
        const short column = this->column(column_name);
        if(is_null(column))
        {
            result = fallback;
            return;
        }
        get_ref_impl<T>(column, result);
    }

    template<class T>
    T get(short column) const
    {
        T result;
        get_ref(column, result);
        return result;
    }

    template<class T>
    T get(short column, const T& fallback) const
    {
        T result;
        get_ref(column, fallback, result);
        return result;
    }

    template<class T>
    T get(const string_type& column_name) const
    {
        T result;
        get_ref(column_name, result);
        return result;
    }

    template<class T>
    T get(const string_type& column_name, const T& fallback) const
    {
        T result;
        get_ref(column_name, fallback, result);
        return result;
    }

private:
    template<class T>
    void get_ref_impl(short column, T& result) const;

    void before_move() NANODBC_NOEXCEPT
    {
        for(short i = 0; i < bound_columns_size_; ++i)
        {
            bound_column& col = bound_columns_[i];
            for(long j = 0; j < rowset_size_; ++j)
                col.cbdata_[j] = 0;
            if(col.blob_ && col.pdata_)
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
        bound_columns_ = NULL;
        bound_columns_size_ = 0;
        bound_columns_by_name_.clear();
    }

    bool fetch(long rows, SQLUSMALLINT orientation)
    {
        before_move();
        RETCODE rc;
        NANODBC_CALL_RC(
            SQLFetchScroll
            , rc
            , stmt_.native_statement_handle()
            , orientation
            , rows);
        if(rc == SQL_NO_DATA)
        {
            at_end_ = true;
            return false;
        }
        if(!success(rc))
            NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);
        return true;
    }

    void auto_bind()
    {
        cleanup_bound_columns();

        const short n_columns = columns();
        if(n_columns < 1)
            return;

        NANODBC_ASSERT(!bound_columns_);
        NANODBC_ASSERT(!bound_columns_size_);
        bound_columns_ = new bound_column[n_columns];
        bound_columns_size_ = n_columns;

        RETCODE rc;
        NANODBC_SQLCHAR column_name[1024];
        SQLSMALLINT sqltype, scale, nullable, len;
        SQLULEN sqlsize;

        for(SQLSMALLINT i = 0; i < n_columns; ++i)
        {
            NANODBC_CALL_RC(
                NANODBC_FUNC(SQLDescribeCol)
                , rc
                , stmt_.native_statement_handle()
                , i + 1
                , (NANODBC_SQLCHAR*)column_name
                , sizeof(column_name)/sizeof(NANODBC_SQLCHAR)
                , &len
                , &sqltype
                , &sqlsize
                , &scale
                , &nullable);
            if(!success(rc))
                NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);

            // Adjust the sqlsize parameter in case of "unlimited" data (varchar(max), nvarchar(max)).
            bool is_blob = false;

            if(sqlsize == 0)
            {
                switch (sqltype)
                {
                    case SQL_VARCHAR:
                    case SQL_WVARCHAR:
                    {
                        // Divide in half, due to sqlsize being 32-bit in Win32 (and 64-bit in x64)
                        //sqlsize = std::numeric_limits<int32_t>::max() / 2 - 1;
                        is_blob = true;
                    }
                }
            }

            bound_column& col = bound_columns_[i];
            col.name_ = reinterpret_cast<string_type::value_type*>(column_name);
            col.column_ = i;
            col.sqltype_ = sqltype;
            col.sqlsize_ = sqlsize;
            col.scale_ = scale;
            bound_columns_by_name_[col.name_] = &col;

            using namespace std; // if int64_t is in std namespace (in c++11)
            switch(col.sqltype_)
            {
                case SQL_BIT:
                case SQL_TINYINT:
                case SQL_SMALLINT:
                case SQL_INTEGER:
                    col.ctype_ = SQL_C_LONG;
                    col.clen_ = sizeof(int32_t);
                    break;
                case SQL_BIGINT:
                    col.ctype_ = SQL_C_SBIGINT;
                    col.clen_ = sizeof(int64_t);
                    break;
                case SQL_DOUBLE:
                case SQL_FLOAT:
                case SQL_DECIMAL:
                case SQL_REAL:
                case SQL_NUMERIC:
                    col.ctype_ = SQL_C_DOUBLE;
                    col.clen_ = sizeof(double);
                    break;
                case SQL_DATE:
                case SQL_TYPE_DATE:
                    col.ctype_ = SQL_C_DATE;
                    col.clen_ = sizeof(date);
                    break;
                case SQL_TIMESTAMP:
                case SQL_TYPE_TIMESTAMP:
                    col.ctype_ = SQL_C_TIMESTAMP;
                    col.clen_ = sizeof(timestamp);
                    break;
                case SQL_CHAR:
                case SQL_VARCHAR:
                    col.ctype_ = SQL_C_CHAR;
                    col.clen_ = (col.sqlsize_ + 1) * sizeof(SQLCHAR);
                    if(is_blob)
                    {
                        col.clen_ = 0;
                        col.blob_ = true;
                    }
                    break;
                case SQL_WCHAR:
                case SQL_WVARCHAR:
                    col.ctype_ = SQL_C_WCHAR;
                    col.clen_ = (col.sqlsize_ + 1) * sizeof(SQLWCHAR);
                    if(is_blob)
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
                    col.ctype_ = SQL_C_BINARY;
                    col.blob_ = true;
                    col.clen_ = 0;
                    break;
                default:
                    col.ctype_ = sql_ctype<string_type>::value;
                    col.clen_ = 128;
                    break;
            }
        }

        for(SQLSMALLINT i = 0; i < n_columns; ++i)
        {
            bound_column& col = bound_columns_[i];
            col.cbdata_ = new null_type[rowset_size_];
            if(col.blob_)
            {
                NANODBC_CALL_RC(
                    SQLBindCol
                    , rc
                    , stmt_.native_statement_handle()
                    , i + 1
                    , col.ctype_
                    , 0
                    , 0
                    , col.cbdata_);
                if(!success(rc))
                    NANODBC_THROW_DATABASE_ERROR(stmt_.native_statement_handle(), SQL_HANDLE_STMT);
            }
            else
            {
                col.pdata_ = new char[rowset_size_ * col.clen_];
                NANODBC_CALL_RC(
                    SQLBindCol
                    , rc
                    , stmt_.native_statement_handle()
                    , i + 1         // ColumnNumber
                    , col.ctype_    // TargetType
                    , col.pdata_    // TargetValuePtr
                    , col.clen_     // BufferLength
                    , col.cbdata_); // StrLen_or_Ind
                if(!success(rc))
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
    std::map<string_type, bound_column*> bound_columns_by_name_;
    bool at_end_;
};

template<>
inline void result::result_impl::get_ref_impl<date>(short column, date& result) const
{
    bound_column& col = bound_columns_[column];
    switch(col.ctype_)
    {
        case SQL_C_DATE:
            result = *reinterpret_cast<date*>(col.pdata_ + rowset_position_ * col.clen_);
            return;
        case SQL_C_TIMESTAMP:
        {
            timestamp stamp = *reinterpret_cast<timestamp*>(col.pdata_ + rowset_position_ * col.clen_ );
            date d = { stamp.year, stamp.month, stamp.day };
            result = d;
            return;
        }
    }
    throw type_incompatible_error();
}

template<>
inline void result::result_impl::get_ref_impl<timestamp>(short column, timestamp& result) const
{
    bound_column& col = bound_columns_[column];
    switch(col.ctype_)
    {
        case SQL_C_DATE:
        {
            date d = *reinterpret_cast<date*>(col.pdata_ + rowset_position_ * col.clen_);
            timestamp stamp = { d.year, d.month, d.day, 0, 0, 0, 0 };
            result = stamp;
            return;
        }
        case SQL_C_TIMESTAMP:
            result = *reinterpret_cast<timestamp*>(col.pdata_ + rowset_position_ * col.clen_);
            return;
    }
    throw type_incompatible_error();
}

template<>
inline void result::result_impl::get_ref_impl<string_type>(short column, string_type& result) const
{
    bound_column& col = bound_columns_[column];
    const SQLULEN column_size = col.sqlsize_;

    switch(col.ctype_)
    {
        case SQL_C_CHAR:
        case SQL_C_BINARY:
        {
            if(col.blob_)
            {
                // Input is always std::string, while output may be std::string or wide_string_type
                std::string out;
                SQLLEN ValueLenOrInd;
                SQLRETURN rc;
                void* handle = native_statement_handle();
                do
                {
                    char buffer[1024] = {0};
                    const std::size_t buffer_size = sizeof(buffer);
                    NANODBC_CALL_RC(
                        SQLGetData
                        , rc
                        , handle            // StatementHandle
                        , column + 1        // Col_or_Param_Num
                        , col.ctype_        // TargetType
                        , buffer            // TargetValuePtr
                        , buffer_size - 1   // BufferLength
                        , &ValueLenOrInd);  // StrLen_or_IndPtr
                    if(ValueLenOrInd > 0)
                        out.append(buffer);
                    else if(ValueLenOrInd == SQL_NULL_DATA)
                        *col.cbdata_ = (SQLINTEGER) SQL_NULL_DATA;
                    // Sequence of successful calls is:
                    // SQL_NO_DATA or SQL_SUCCESS_WITH_INFO followed by SQL_SUCCESS.
                } while(rc == SQL_SUCCESS_WITH_INFO);
                if (rc == SQL_SUCCESS || rc == SQL_NO_DATA)
                    convert(out, result);
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
            if(col.blob_)
            {
                // Input is always wide_string_type, output might be std::string or wide_string_type.
                // Use a string builder to build the output string.
                wide_string_type out;
                SQLLEN ValueLenOrInd;
                SQLRETURN rc;
                void* handle = native_statement_handle();
                do
                {
                    wide_char_t buffer[512] = {0};
                    const std::size_t buffer_size = sizeof(buffer);
                    NANODBC_CALL_RC(
                        SQLGetData
                        , rc
                        , handle            // StatementHandle
                        , column + 1        // Col_or_Param_Num
                        , col.ctype_        // TargetType
                        , buffer            // TargetValuePtr
                        , buffer_size - 1   // BufferLength
                        , &ValueLenOrInd);  // StrLen_or_IndPtr
                    if(ValueLenOrInd > 0)
                        out.append(buffer);
                    else if(ValueLenOrInd == SQL_NULL_DATA)
                        *col.cbdata_ = (SQLINTEGER) SQL_NULL_DATA;
                    // Sequence of successful calls is:
                    // SQL_NO_DATA or SQL_SUCCESS_WITH_INFO followed by SQL_SUCCESS.
                } while(rc == SQL_SUCCESS_WITH_INFO);
                if (rc == SQL_SUCCESS || rc == SQL_NO_DATA)
                    convert(out, result);
            }
            else
            {
                // Type is unicode in the database, convert if necessary
                const SQLWCHAR* s = reinterpret_cast<SQLWCHAR*>(col.pdata_ + rowset_position_ * col.clen_);
                const string_type::size_type str_size = *col.cbdata_ / sizeof(SQLWCHAR);
                wide_string_type temp(s, s + str_size);
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
            const wide_char_t data = *reinterpret_cast<wide_char_t*>(col.pdata_ + rowset_position_ * col.clen_);
            const int bytes = std::snprintf(const_cast<char*>(buffer.data()), column_size, "%d", data);
            if(bytes == -1)
                throw type_incompatible_error();
            else if((SQLULEN)bytes < column_size)
                buffer.resize(bytes);
            buffer.resize(std::strlen(buffer.data())); // drop any trailing nulls
            result.reserve(buffer.size() * sizeof(string_type::value_type));
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
            const intmax_t data = (intmax_t)*reinterpret_cast<int64_t*>(col.pdata_ + rowset_position_ * col.clen_);
            const int bytes = std::snprintf(const_cast<char*>(buffer.data()), column_size, "%jd", data);
            if(bytes == -1)
                throw type_incompatible_error();
            else if((SQLULEN)bytes < column_size)
                buffer.resize(bytes);
            buffer.resize(std::strlen(buffer.data())); // drop any trailing nulls
            result.reserve(buffer.size() * sizeof(string_type::value_type));
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
            const int bytes = std::snprintf(const_cast<char*>(buffer.data()), column_size, "%f", data);
            if(bytes == -1)
                throw type_incompatible_error();
            else if((SQLULEN)bytes < column_size)
                buffer.resize(bytes);
            buffer.resize(std::strlen(buffer.data())); // drop any trailing nulls
            result.reserve(buffer.size() * sizeof(string_type::value_type));
            convert(buffer, result);
            return;
        }

        case SQL_C_DOUBLE:
        {
            std::string buffer;
            const SQLULEN width = column_size + 2; // account for decimal mark and sign
            buffer.reserve(width + 1); // ensure terminating null
            buffer.resize(buffer.capacity());
            using std::fill;
            fill(buffer.begin(), buffer.end(), '\0');
            const double data = *reinterpret_cast<double*>(col.pdata_ + rowset_position_ * col.clen_);
            const int bytes = std::snprintf(
                const_cast<char*>(buffer.data())
                , width
                , "%.*lf"                       // restrict the number of digits
                , col.scale_                    // number of digits after the decimal point
                , data);
            if(bytes == -1)
                throw type_incompatible_error();
            else if((SQLULEN)bytes < column_size)
                buffer.resize(bytes);
            buffer.resize(std::strlen(buffer.data())); // drop any trailing nulls
            result.reserve(buffer.size() * sizeof(string_type::value_type));
            convert(buffer, result);
            return;
        }

        case SQL_C_DATE:
        {
            const date d = *reinterpret_cast<date*>(col.pdata_ + rowset_position_ * col.clen_);
            std::tm st = { 0 };
            st.tm_year = d.year - 1900;
            st.tm_mon = d.month - 1;
            st.tm_mday = d.day;
            char* old_lc_time = std::setlocale(LC_TIME, NULL);
            std::setlocale(LC_TIME, "");
            char date_str[512];
            std::strftime(date_str, sizeof(date_str), "%Y-%m-%d", &st);
            std::setlocale(LC_TIME, old_lc_time);
            convert(date_str, result);
            return;
        }

        case SQL_C_TIMESTAMP:
        {
            const timestamp stamp = *reinterpret_cast<timestamp*>(col.pdata_ + rowset_position_ * col.clen_);
            std::tm st = { 0 };
            st.tm_year = stamp.year - 1900;
            st.tm_mon = stamp.month - 1;
            st.tm_mday = stamp.day;
            st.tm_hour = stamp.hour;
            st.tm_min = stamp.min;
            st.tm_sec = stamp.sec;
            char* old_lc_time = std::setlocale(LC_TIME, NULL);
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

template<class T>
void result::result_impl::get_ref_impl(short column, T& result) const
{
    bound_column& col = bound_columns_[column];
    using namespace std; // if int64_t is in std namespace (in c++11)
    const char* s = col.pdata_ + rowset_position_ * col.clen_;
    switch(col.ctype_)
    {
        case SQL_C_CHAR: result = (T)*(char*)(s); return;
        case SQL_C_SSHORT: result = (T)*(short*)(s); return;
        case SQL_C_USHORT: result = (T)*(unsigned short*)(s); return;
        case SQL_C_LONG: result = (T)*(int32_t*)(s); return;
        case SQL_C_SLONG: result = (T)*(int32_t*)(s); return;
        case SQL_C_ULONG: result = (T)*(uint32_t*)(s); return;
        case SQL_C_FLOAT: result = (T)*(float*)(s); return;
        case SQL_C_DOUBLE: result = (T)*(double*)(s); return;
        case SQL_C_SBIGINT: result = (T)*(int64_t*)(s); return;
        case SQL_C_UBIGINT: result = (T)*(uint64_t*)(s); return;
    }
    throw type_incompatible_error();
}

} // namespace nanodbc

// 8888888888                            8888888888                         888    d8b
// 888                                   888                                888    Y8P
// 888                                   888                                888
// 8888888 888d888 .d88b.   .d88b.       8888888 888  888 88888b.   .d8888b 888888 888  .d88b.  88888b.  .d8888b
// 888     888P"  d8P  Y8b d8P  Y8b      888     888  888 888 "88b d88P"    888    888 d88""88b 888 "88b 88K
// 888     888    88888888 88888888      888     888  888 888  888 888      888    888 888  888 888  888 "Y8888b.
// 888     888    Y8b.     Y8b.          888     Y88b 888 888  888 Y88b.    Y88b.  888 Y88..88P 888  888      X88
// 888     888     "Y8888   "Y8888       888      "Y88888 888  888  "Y8888P  "Y888 888  "Y88P"  888  888  88888P'
// MARK: Free Functions -

namespace nanodbc
{

result execute(connection& conn, const string_type& query, long batch_operations, long timeout)
{
    class statement statement;
    return statement.execute_direct(conn, query, batch_operations, timeout);
}

void just_execute(connection& conn, const string_type& query, long batch_operations, long timeout) {
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

void prepare(statement& stmt, const string_type& query, long timeout)
{
    stmt.prepare(stmt.connection(), query, timeout);
}

} // namespace nanodbc

//  .d8888b.                                               888    d8b                             8888888888                 888
// d88P  Y88b                                              888    Y8P                             888                        888
// 888    888                                              888                                    888                        888
// 888         .d88b.  88888b.  88888b.   .d88b.   .d8888b 888888 888  .d88b.  88888b.            8888888 888  888  888  .d88888
// 888        d88""88b 888 "88b 888 "88b d8P  Y8b d88P"    888    888 d88""88b 888 "88b           888     888  888  888 d88" 888
// 888    888 888  888 888  888 888  888 88888888 888      888    888 888  888 888  888           888     888  888  888 888  888
// Y88b  d88P Y88..88P 888  888 888  888 Y8b.     Y88b.    Y88b.  888 Y88..88P 888  888           888     Y88b 888 d88P Y88b 888
//  "Y8888P"   "Y88P"  888  888 888  888  "Y8888   "Y8888P  "Y888 888  "Y88P"  888  888           888      "Y8888888P"   "Y88888
// MARK: Connection Fwd -

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
    connection::connection(connection&& rhs) NANODBC_NOEXCEPT
    : impl_(std::move(rhs.impl_))
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

connection::connection(
    const string_type& dsn
    , const string_type& user
    , const string_type& pass
    , long timeout)
: impl_(new connection_impl(dsn, user, pass, timeout))
{

}

connection::connection(const string_type& connection_string, long timeout)
: impl_(new connection_impl(connection_string, timeout))
{

}

connection::~connection() NANODBC_NOEXCEPT
{

}

void connection::connect(
    const string_type& dsn
    , const string_type& user
    , const string_type& pass
    , long timeout)
{
    impl_->connect(dsn, user, pass, timeout);
}

void connection::connect(const string_type& connection_string, long timeout)
{
    impl_->connect(connection_string, timeout);
}

#ifdef SQL_ATTR_ASYNC_DBC_EVENT
void connection::async_connect(
    const string_type& dsn
    , const string_type& user
    , const string_type& pass
    , void* event_handle
    , long timeout)
{
    impl_->connect(dsn, user, pass, timeout, event_handle);
}

void connection::async_connect(const string_type& connection_string, void* event_handle, long timeout)
{
    impl_->connect(connection_string, timeout, event_handle);
}

void connection::async_complete()
{
    impl_->async_complete();
}
#endif // SQL_ATTR_ASYNC_DBC_EVENT

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

void* connection::native_dbc_handle() const
{
    return impl_->native_dbc_handle();
}

void* connection::native_env_handle() const
{
    return impl_->native_env_handle();
}

string_type connection::dbms_name() const
{
    return impl_->dbms_name();
}

string_type connection::dbms_version() const
{
    return impl_->dbms_version();
}

string_type connection::driver_name() const
{
    return impl_->driver_name();
}

string_type connection::database_name() const
{
    return impl_->database_name();
}

string_type connection::catalog_name() const
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

// 88888888888                                                  888    d8b                             8888888888                 888
//     888                                                      888    Y8P                             888                        888
//     888                                                      888                                    888                        888
//     888  888d888 8888b.  88888b.  .d8888b   8888b.   .d8888b 888888 888  .d88b.  88888b.            8888888 888  888  888  .d88888 .d8888b
//     888  888P"      "88b 888 "88b 88K          "88b d88P"    888    888 d88""88b 888 "88b           888     888  888  888 d88" 888 88K
//     888  888    .d888888 888  888 "Y8888b. .d888888 888      888    888 888  888 888  888           888     888  888  888 888  888 "Y8888b.
//     888  888    888  888 888  888      X88 888  888 Y88b.    Y88b.  888 Y88..88P 888  888           888     Y88b 888 d88P Y88b 888      X88
//     888  888    "Y888888 888  888  88888P' "Y888888  "Y8888P  "Y888 888  "Y88P"  888  888           888      "Y8888888P"   "Y88888  88888P'
// MARK: Transaction Fwd -

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
    transaction::transaction(transaction&& rhs) NANODBC_NOEXCEPT
    : impl_(std::move(rhs.impl_))
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

//  .d8888b.  888             888                                            888              8888888888                 888
// d88P  Y88b 888             888                                            888              888                        888
// Y88b.      888             888                                            888              888                        888
//  "Y888b.   888888  8888b.  888888 .d88b.  88888b.d88b.   .d88b.  88888b.  888888           8888888 888  888  888  .d88888
//     "Y88b. 888        "88b 888   d8P  Y8b 888 "888 "88b d8P  Y8b 888 "88b 888              888     888  888  888 d88" 888
//       "888 888    .d888888 888   88888888 888  888  888 88888888 888  888 888              888     888  888  888 888  888
// Y88b  d88P Y88b.  888  888 Y88b. Y8b.     888  888  888 Y8b.     888  888 Y88b.            888     Y88b 888 d88P Y88b 888
//  "Y8888P"   "Y888 "Y888888  "Y888 "Y8888  888  888  888  "Y8888  888  888  "Y888           888      "Y8888888P"   "Y88888
// MARK: Statement Fwd -

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
    statement::statement(statement&& rhs) NANODBC_NOEXCEPT
    : impl_(std::move(rhs.impl_))
    {

    }
#endif

statement::statement(class connection& conn, const string_type& query, long timeout)
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

void statement::prepare(class connection& conn, const string_type& query, long timeout)
{
    impl_->prepare(conn, query, timeout);
}

void statement::prepare(const string_type& query, long timeout)
{
    impl_->prepare(query, timeout);
}

void statement::timeout(long timeout)
{
    impl_->timeout(timeout);
}

result statement::execute_direct(
    class connection& conn
    , const string_type& query
    , long batch_operations
    , long timeout)
{
    return impl_->execute_direct(conn, query, batch_operations, timeout, *this);
}

#if defined(SQL_ATTR_ASYNC_STMT_EVENT) && defined(SQL_API_SQLCOMPLETEASYNC)
    void statement::async_execute_direct(
        class connection& conn
        , void* event_handle
        , const string_type& query
        , long batch_operations
        , long timeout)
    {
        impl_->async_execute_direct(conn, event_handle, query, batch_operations, timeout, *this);
    }

    result statement::async_complete(long batch_operations)
    {
        return impl_->async_complete(batch_operations, *this);
    }
#endif

void statement::just_execute_direct(
    class connection& conn
    , const string_type& query
    , long batch_operations
    , long timeout)
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
    const string_type& catalog
    , const string_type& schema
    , const string_type& procedure
    , const string_type& column)
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

void statement::reset_parameters() NANODBC_NOEXCEPT
{
    impl_->reset_parameters();
}

unsigned long statement::parameter_size(short param) const
{
    return impl_->parameter_size(param);
}

// We need to instantiate each form of bind() for each of our supported data types.
#define NANODBC_INSTANTIATE_BINDS(type)                                                                                 \
    template void statement::bind(short, const type*, param_direction); /* 1-ary */                                     \
    template void statement::bind(short, const type*, std::size_t, param_direction); /* n-ary */                        \
    template void statement::bind(short, const type*, std::size_t, const type*, param_direction); /* n-ary, sentry */   \
    template void statement::bind(short, const type*, std::size_t, const bool*, param_direction) /* n-ary, flags */     \
    /**/

// The following are the only supported instantiations of statement::bind().
NANODBC_INSTANTIATE_BINDS(string_type::value_type);
NANODBC_INSTANTIATE_BINDS(short);
NANODBC_INSTANTIATE_BINDS(unsigned short);
NANODBC_INSTANTIATE_BINDS(int32_t);
NANODBC_INSTANTIATE_BINDS(uint32_t);
NANODBC_INSTANTIATE_BINDS(int64_t);
NANODBC_INSTANTIATE_BINDS(uint64_t);
NANODBC_INSTANTIATE_BINDS(float);
NANODBC_INSTANTIATE_BINDS(double);
NANODBC_INSTANTIATE_BINDS(date);
NANODBC_INSTANTIATE_BINDS(timestamp);

#undef NANODBC_INSTANTIATE_BINDS

template<class T>
void statement::bind(short param, const T* value, param_direction direction)
{
    impl_->bind(param, value, 1, direction);
}

template<class T>
void statement::bind(short param, const T* values, std::size_t elements, param_direction direction)
{
    impl_->bind(param, values, elements, direction);
}

template<class T>
void statement::bind(
    short param
    , const T* values
    , std::size_t elements
    , const T* null_sentry
    , param_direction direction)
{
    impl_->bind(param, values, elements, 0, null_sentry, direction);
}

template<class T>
void statement::bind(
    short param
    , const T* values
    , std::size_t elements
    , const bool* nulls
    , param_direction direction)
{
    impl_->bind(param, values, elements, nulls, (T*)0, direction);
}

void statement::bind_strings(
    short param
    , const string_type::value_type* values
    , std::size_t length
    , std::size_t elements
    , param_direction direction)
{
    impl_->bind_strings(param, values, length, elements, direction);
}

void statement::bind_strings(
    short param
    , const string_type::value_type* values
    , std::size_t length
    , std::size_t elements
    , const string_type::value_type* null_sentry
    , param_direction direction)
{
    impl_->bind_strings(param, values, length, elements, (bool*)0, null_sentry, direction);
}

void statement::bind_strings(
    short param
    , const string_type::value_type* values
    , std::size_t length
    , std::size_t elements
    , const bool* nulls
    , param_direction direction)
{
    impl_->bind_strings(
        param
        , values
        , length
        , elements
        , nulls
        , (string_type::value_type*)0
        , direction);
}

void statement::bind_null(short param, std::size_t elements)
{
    impl_->bind_null(param, elements);
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

string_type catalog::tables::table_catalog() const
{
    // TABLE_CAT might be NULL
    return result_.get<string_type>(0, string_type());
}

string_type catalog::tables::table_schema() const
{
    // TABLE_SCHEM might be NULL
    return result_.get<string_type>(1, string_type());
}

string_type catalog::tables::table_name() const
{
    // TABLE_NAME column is never NULL
    return result_.get<string_type>(2);
}

string_type catalog::tables::table_type() const
{
    // TABLE_TYPE column is never NULL
    return result_.get<string_type>(3);
}

string_type catalog::tables::table_remarks() const
{
    // REMARKS might be NULL
    return result_.get<string_type>(4, string_type());
}

catalog::primary_keys::primary_keys(result& find_result)
: result_(find_result)
{
}

bool catalog::primary_keys::next()
{
    return result_.next();
}

string_type catalog::primary_keys::table_catalog() const
{
    // TABLE_CAT might be NULL
    return result_.get<string_type>(0, string_type());
}

string_type catalog::primary_keys::table_schema() const
{
    // TABLE_SCHEM might be NULL
    return result_.get<string_type>(1, string_type());
}

string_type catalog::primary_keys::table_name() const
{
    // TABLE_NAME is never NULL
    return result_.get<string_type>(2);
}

string_type catalog::primary_keys::column_name() const
{
    // COLUMN_NAME is never NULL
    return result_.get<string_type>(3);
}

short catalog::primary_keys::column_number() const
{
    // KEY_SEQ is never NULL
    return result_.get<short>(4);
}

string_type catalog::primary_keys::primary_key_name() const
{
    // PK_NAME might be NULL
    return result_.get<string_type>(5);
}

catalog::columns::columns(result& find_result)
: result_(find_result)
{
}

bool catalog::columns::next()
{
    return result_.next();
}

string_type catalog::columns::table_catalog() const
{
    // TABLE_CAT might be NULL
    return result_.get<string_type>(0, string_type());
}

string_type catalog::columns::table_schema() const
{
    // TABLE_SCHEM might be NULL
    return result_.get<string_type>(1, string_type());
}

string_type catalog::columns::table_name() const
{
    // TABLE_NAME is never NULL
    return result_.get<string_type>(2);
}

string_type catalog::columns::column_name() const
{
    // COLUMN_NAME is never NULL
    return result_.get<string_type>(3);
}

short catalog::columns::data_type() const
{
    // DATA_TYPE is never NULL
    return result_.get<short>(4);
}

string_type catalog::columns::type_name() const
{
    // TYPE_NAME is never NULL
    return result_.get<string_type>(5);
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

string_type catalog::columns::remarks() const
{
    // REMARKS might be NULL
    return result_.get<string_type>(11, string_type());
}

string_type catalog::columns::column_default() const
{
    // COLUMN_DEF might be NULL, if no default value is specified.
    return result_.get<string_type>(12, string_type());
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

long catalog::columns::char_octed_length() const
{
    // CHAR_OCTET_LENGTH might be nULL
    return result_.get<long>(15, 0);
}

long catalog::columns::ordinal_position() const
{
    // ORDINAL_POSITION is never NULL
    return result_.get<long>(16);
}

string_type catalog::columns::is_nullable() const
{
    // IS_NULLABLE might be NULL

    // MSDN: This column returns a zero-length string if nullability is unknown.
    //       ISO rules are followed to determine nullability.
    //       An ISO SQL-compliant DBMS cannot return an empty string.
    return result_.get<string_type>(17, string_type());
}

catalog::catalog(connection& conn)
: conn_(conn)
{
}

catalog::tables catalog::find_tables(
    const string_type& table
  , const string_type& type
  , const string_type& schema
  , const string_type& catalog)
{
    statement stmt(conn_);
    RETCODE rc;
    NANODBC_CALL_RC(
        NANODBC_FUNC(SQLTables)
        , rc
        , stmt.native_statement_handle()
        , (NANODBC_SQLCHAR*)(catalog.empty() ? NULL : catalog.c_str())
        , (catalog.empty() ? 0 : SQL_NTS)
        , (NANODBC_SQLCHAR*)(schema.empty() ? NULL : schema.c_str())
        , (schema.empty() ? 0 : SQL_NTS)
        , (NANODBC_SQLCHAR*)(table.empty() ? NULL : table.c_str())
        , (table.empty() ? 0 : SQL_NTS)
        , (NANODBC_SQLCHAR*)(type.empty() ? NULL : type.c_str())
        , (type.empty() ? 0 : SQL_NTS));
    if(!success(rc))
        NANODBC_THROW_DATABASE_ERROR(stmt.native_statement_handle(), SQL_HANDLE_STMT);

    result find_result(stmt, 1);
    return catalog::tables(find_result);
}

catalog::columns catalog::find_columns(
        const string_type& column
      , const string_type& table
      , const string_type& schema
      , const string_type& catalog)
{
    statement stmt(conn_);
    RETCODE rc;
    NANODBC_CALL_RC(
        NANODBC_FUNC(SQLColumns)
        , rc
        , stmt.native_statement_handle()
        , (NANODBC_SQLCHAR*)(catalog.empty() ? NULL : catalog.c_str())
        , (catalog.empty() ? 0 : SQL_NTS)
        , (NANODBC_SQLCHAR*)(schema.empty() ? NULL : schema.c_str())
        , (schema.empty() ? 0 : SQL_NTS)
        , (NANODBC_SQLCHAR*)(table.empty() ? NULL : table.c_str())
        , (table.empty() ? 0 : SQL_NTS)
        , (NANODBC_SQLCHAR*)(column.empty() ? NULL : column.c_str())
        , (column.empty() ? 0 : SQL_NTS));
    if(!success(rc))
        NANODBC_THROW_DATABASE_ERROR(stmt.native_statement_handle(), SQL_HANDLE_STMT);

    result find_result(stmt, 1);
    return catalog::columns(find_result);
}

catalog::primary_keys catalog::find_primary_keys(
      const string_type& table
    , const string_type& schema
    , const string_type& catalog)
{
    statement stmt(conn_);
    RETCODE rc;
    NANODBC_CALL_RC(
        NANODBC_FUNC(SQLPrimaryKeys)
        , rc
        , stmt.native_statement_handle()
        , (NANODBC_SQLCHAR*)(catalog.empty() ? NULL : catalog.c_str())
        , (catalog.empty() ? 0 : SQL_NTS)
        , (NANODBC_SQLCHAR*)(schema.empty() ? NULL : schema.c_str())
        , (schema.empty() ? 0 : SQL_NTS)
        , (NANODBC_SQLCHAR*)(table.empty() ? NULL : table.c_str())
        , (table.empty() ? 0 : SQL_NTS));
    if(!success(rc))
        NANODBC_THROW_DATABASE_ERROR(stmt.native_statement_handle(), SQL_HANDLE_STMT);

    result find_result(stmt, 1);
    return catalog::primary_keys(find_result);
}

} // namespace nanodbc

// 8888888b.                            888 888              8888888888                 888
// 888   Y88b                           888 888              888                        888
// 888    888                           888 888              888                        888
// 888   d88P .d88b.  .d8888b  888  888 888 888888           8888888 888  888  888  .d88888
// 8888888P" d8P  Y8b 88K      888  888 888 888              888     888  888  888 d88" 888
// 888 T88b  88888888 "Y8888b. 888  888 888 888              888     888  888  888 888  888
// 888  T88b Y8b.          X88 Y88b 888 888 Y88b.            888     Y88b 888 d88P Y88b 888
// 888   T88b "Y8888   88888P'  "Y88888 888  "Y888           888      "Y8888888P"   "Y88888
// MARK: Result Fwd -

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
    result::result(result&& rhs) NANODBC_NOEXCEPT
    : impl_(std::move(rhs.impl_))
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

bool result::end() const NANODBC_NOEXCEPT
{
    return impl_->end();
}

bool result::is_null(short column) const
{
    return impl_->is_null(column);
}

bool result::is_null(const string_type& column_name) const
{
    return impl_->is_null(column_name);
}

string_type result::column_name(short column) const
{
    return impl_->column_name(column);
}

long result::column_size(short column) const
{
    return impl_->column_size(column);
}

short result::column(const string_type& column_name) const
{
    return impl_->column(column_name);
}

int result::column_datatype(short column) const
{
    return impl_->column_datatype(column);
}

int result::column_datatype(const string_type& column_name) const
{
    return impl_->column_datatype(column_name);
}

int result::column_c_datatype(short column) const
{
    return impl_->column_c_datatype(column);
}

int result::column_c_datatype(const string_type& column_name) const
{
    return impl_->column_c_datatype(column_name);
}

bool result::next_result()
{
    return impl_->next_result();
}

template<class T>
void result::get_ref(short column, T& result) const
{
    return impl_->get_ref<T>(column, result);
}

template<class T>
void result::get_ref(short column, const T& fallback, T& result) const
{
    return impl_->get_ref<T>(column, fallback, result);
}

template<class T>
void result::get_ref(const string_type& column_name, T& result) const
{
    return impl_->get_ref<T>(column_name, result);
}

template<class T>
void result::get_ref(const string_type& column_name, const T& fallback, T& result) const
{
    return impl_->get_ref<T>(column_name, fallback, result);
}

template<class T>
T result::get(short column) const
{
    return impl_->get<T>(column);
}

template<class T>
T result::get(short column, const T& fallback) const
{
    return impl_->get<T>(column, fallback);
}

template<class T>
T result::get(const string_type& column_name) const
{
    return impl_->get<T>(column_name);
}

template<class T>
T result::get(const string_type& column_name, const T& fallback) const
{
    return impl_->get<T>(column_name, fallback);
}

result::operator bool() const
{
    return static_cast<bool>(impl_);
}

// The following are the only supported instantiations of result::get_ref().
template void result::get_ref(short, string_type::value_type&) const;
template void result::get_ref(short, short&) const;
template void result::get_ref(short, unsigned short&) const;
template void result::get_ref(short, int32_t&) const;
template void result::get_ref(short, uint32_t&) const;
template void result::get_ref(short, int64_t&) const;
template void result::get_ref(short, uint64_t&) const;
template void result::get_ref(short, float&) const;
template void result::get_ref(short, double&) const;
template void result::get_ref(short, string_type&) const;
template void result::get_ref(short, date&) const;
template void result::get_ref(short, timestamp&) const;

template void result::get_ref(const string_type&, string_type::value_type&) const;
template void result::get_ref(const string_type&, short&) const;
template void result::get_ref(const string_type&, unsigned short&) const;
template void result::get_ref(const string_type&, int32_t&) const;
template void result::get_ref(const string_type&, uint32_t&) const;
template void result::get_ref(const string_type&, int64_t&) const;
template void result::get_ref(const string_type&, uint64_t&) const;
template void result::get_ref(const string_type&, float&) const;
template void result::get_ref(const string_type&, double&) const;
template void result::get_ref(const string_type&, string_type&) const;
template void result::get_ref(const string_type&, date&) const;
template void result::get_ref(const string_type&, timestamp&) const;

// The following are the only supported instantiations of result::get_ref() with fallback.
template void result::get_ref(short, const string_type::value_type&, string_type::value_type&) const;
template void result::get_ref(short, const short&, short&) const;
template void result::get_ref(short, const unsigned short&, unsigned short&) const;
template void result::get_ref(short, const int32_t&, int32_t&) const;
template void result::get_ref(short, const uint32_t&, uint32_t&) const;
template void result::get_ref(short, const int64_t&, int64_t&) const;
template void result::get_ref(short, const uint64_t&, uint64_t&) const;
template void result::get_ref(short, const float&, float&) const;
template void result::get_ref(short, const double&, double&) const;
template void result::get_ref(short, const string_type&, string_type&) const;
template void result::get_ref(short, const date&, date&) const;
template void result::get_ref(short, const timestamp&, timestamp&) const;

template void result::get_ref(const string_type&, const string_type::value_type&, string_type::value_type&) const;
template void result::get_ref(const string_type&, const short&, short&) const;
template void result::get_ref(const string_type&, const unsigned short&, unsigned short&) const;
template void result::get_ref(const string_type&, const int32_t&, int32_t&) const;
template void result::get_ref(const string_type&, const uint32_t&, uint32_t&) const;
template void result::get_ref(const string_type&, const int64_t&, int64_t&) const;
template void result::get_ref(const string_type&, const uint64_t&, uint64_t&) const;
template void result::get_ref(const string_type&, const float&, float&) const;
template void result::get_ref(const string_type&, const double&, double&) const;
template void result::get_ref(const string_type&, const string_type&, string_type&) const;
template void result::get_ref(const string_type&, const date&, date&) const;
template void result::get_ref(const string_type&, const timestamp&, timestamp&) const;

// The following are the only supported instantiations of result::get().
template string_type::value_type result::get(short) const;
template short result::get(short) const;
template unsigned short result::get(short) const;
template int32_t result::get(short) const;
template uint32_t result::get(short) const;
template int64_t result::get(short) const;
template uint64_t result::get(short) const;
template float result::get(short) const;
template double result::get(short) const;
template string_type result::get(short) const;
template date result::get(short) const;
template timestamp result::get(short) const;

template string_type::value_type result::get(const string_type&) const;
template short result::get(const string_type&) const;
template unsigned short result::get(const string_type&) const;
template int32_t result::get(const string_type&) const;
template uint32_t result::get(const string_type&) const;
template int64_t result::get(const string_type&) const;
template uint64_t result::get(const string_type&) const;
template float result::get(const string_type&) const;
template double result::get(const string_type&) const;
template string_type result::get(const string_type&) const;
template date result::get(const string_type&) const;
template timestamp result::get(const string_type&) const;

// The following are the only supported instantiations of result::get() with fallback.
template string_type::value_type result::get(short, const string_type::value_type&) const;
template short result::get(short, const short&) const;
template unsigned short result::get(short, const unsigned short&) const;
template int32_t result::get(short, const int32_t&) const;
template uint32_t result::get(short, const uint32_t&) const;
template int64_t result::get(short, const int64_t&) const;
template uint64_t result::get(short, const uint64_t&) const;
template float result::get(short, const float&) const;
template double result::get(short, const double&) const;
template string_type result::get(short, const string_type&) const;
template date result::get(short, const date&) const;
template timestamp result::get(short, const timestamp&) const;

template string_type::value_type result::get(const string_type&, const string_type::value_type&) const;
template short result::get(const string_type&, const short&) const;
template unsigned short result::get(const string_type&, const unsigned short&) const;
template int32_t result::get(const string_type&, const int32_t&) const;
template uint32_t result::get(const string_type&, const uint32_t&) const;
template int64_t result::get(const string_type&, const int64_t&) const;
template uint64_t result::get(const string_type&, const uint64_t&) const;
template float result::get(const string_type&, const float&) const;
template double result::get(const string_type&, const double&) const;
template string_type result::get(const string_type&, const string_type&) const;
template date result::get(const string_type&, const date&) const;
template timestamp result::get(const string_type&, const timestamp&) const;

} // namespace nanodbc

#undef NANODBC_THROW_DATABASE_ERROR
#undef NANODBC_STRINGIZE
#undef NANODBC_STRINGIZE_I
#undef NANODBC_CALL_RC
#undef NANODBC_CALL

#endif // DOXYGEN
