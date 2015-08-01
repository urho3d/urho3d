//! \file nanodbc.h The entirety of nanodbc can be found within this file and nanodbc.cpp.

//! \mainpage
//!
//! \section synopsis Synopsis
//! This library provides a wrapper API for the native ODBC API. It aims to do everything ODBC does, but with a \b much nicer interface.
//! Anything it doesn't (yet) do can be done by retrieving the native ODBC handles and dropping down to straight ODBC C API code.
//! For more propaganda, please see the <a href="http://lexicalunit.github.com/nanodbc/">project homepage</a>.
//!
//! \section toc Table of Contents
//! - \ref license "License"
//! - \ref credits "Credits"
//! - Source level documentation:
//!     - \ref nanodbc "nanodbc namespace"
//!     - \ref exceptions
//!     - \ref utility
//!     - \ref mainc
//!     - \ref mainf
//!     - \ref binding
//!     - \ref bind_multi
//!     - \ref bind_strings
//!
//! \section license License
//! <div class="license">
//! Copyright (C) 2013 lexicalunit <lexicalunit@lexicalunit.com>
//!
//! The MIT License
//!
//! Permission is hereby granted, free of charge, to any person obtaining a copy
//! of this software and associated documentation files (the "Software"), to deal
//! in the Software without restriction, including without limitation the rights
//! to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//! copies of the Software, and to permit persons to whom the Software is
//! furnished to do so, subject to the following conditions:
//!
//! The above copyright notice and this permission notice shall be included in
//! all copies or substantial portions of the Software.
//!
//! THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//! IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//! FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//! AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//! LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//! OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//! THE SOFTWARE.
//! </div>
//!
//! \section credits Credits
//! <div class="license">
//! Much of the code in this file was originally derived from TinyODBC.
//! TinyODBC is hosted at http://code.google.com/p/tiodbc/
//! Copyright (C) 2008 SqUe squarious@gmail.com
//! License: The MIT License
//!
//! The idea for using RAII for transactions was inspired by SimpleDB: C++ ODBC database API,
//! however the code in nanodbc is original and not derived from SimpleDB. Therefore
//! the LGPL license under which SimpleDB is distributed does NOT apply to nanodbc.
//! SimpleDB is hosted at http://simpledb.sourceforge.net
//! Copyright (C) 2006 Eminence Technology Pty Ltd
//! Copyright (C) 2008-2010,2012 Russell Kliese russell@kliese.id.au
//! License: GNU Lesser General Public version 2.1
//!
//! Some improvements and features are based on The Python ODBC Library.
//! The Python ODBC Library is hosted at http://code.google.com/p/pyodbc/
//! License: The MIT License
//!
//! Implementation of column binding inspired by Nick E. Geht's source code posted to on CodeGuru.
//! GSODBC hosted at http://www.codeguru.com/mfc_database/gsodbc.html
//! Copyright (C) 2002 Nick E. Geht
//! License: Perpetual license to reproduce, distribute, adapt, perform, display, and sublicense.
//! See http://www.codeguru.com/submission-guidelines.php for details.
//! </div>

#ifndef NANODBC_H
#define NANODBC_H

#include <cstdint>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

//! \brief The entirety of nanodbc can be found within this one namespace.
//! \note This library does not make any exception safety guarantees, but should work just fine with a threading enabled ODBC driver. If you want to use nanodbc objects in threads I recommend each thread keep their own connection to the database. Otherwise you must synchronize any access to nanodbc objects.
namespace nanodbc
{

// You must explicitly request Unicode support by defining NANODBC_USE_UNICODE at compile time.
#ifndef DOXYGEN
    #ifdef NANODBC_USE_UNICODE
        typedef std::wstring string_type;
    #else
        typedef std::string string_type;
    #endif // NANODBC_USE_UNICODE

    #if defined(_WIN64)
        // LLP64 machine, Windows
        typedef std::int64_t null_type;
    #elif !defined(_WIN64) && defined(__LP64__)
        // LP64 machine, OS X or Linux
        typedef long null_type;
    #else
        // 32-bit machine
        typedef long null_type;
    #endif
#else
    //! string_type will be std::wstring if NANODBC_USE_UNICODE is defined, otherwise std::string.
    typedef unspecified-type string_type;
    //! null_type will be int64_t for 64-bit compilations, otherwise long.
    typedef unspecified-type null_type;
#endif // DOXYGEN

//! \addtogroup exceptions Exception types
//! \brief Possible error conditions.
//!
//! Specific errors such as type_incompatible_error, null_access_error, and index_range_error can arise
//! from improper use of the nanodbc library. The general database_error is for all other situations
//! in which the ODBC driver or C API reports an error condition. The explanatory string for database_error
//! will, if possible, contain a diagnostic message obtained from SQLGetDiagRec().
//! @{

//! \brief Type incompatible.
//! \see exceptions
class type_incompatible_error : public std::runtime_error
{
public:
    type_incompatible_error();
    const char* what() const throw();
};

//! \brief Accessed null data.
//! \see exceptions
class null_access_error : public std::runtime_error
{
public:
    null_access_error();
    const char* what() const throw();
};

//! \brief Index out of range.
//! \see exceptions
class index_range_error : public std::runtime_error
{
public:
    index_range_error();
    const char* what() const throw();
};

//! \brief Programming logic error.
//! \see exceptions
class programming_error : public std::runtime_error
{
public:
    explicit programming_error(const std::string& info);
    const char* what() const throw();
};

//! \brief General database error.
//! \see exceptions
class database_error : public std::runtime_error
{
public:
    //! \brief Creates a runtime_error with a message describing the last ODBC error generated for the given handle and handle_type.
    //! \param handle The native ODBC statement or connection handle.
    //! \param handle_type The native ODBC handle type code for the given handle.
    //! \param info Additional information that will be appended to the beginning of the error message.
    database_error(void* handle, short handle_type, const std::string& info = "");
    const char* what() const throw();
};

//! @}

//! \addtogroup utility Utilities
//! \brief Additional nanodbc utility classes and functions.
//!
//! \{

//! \brief A type for representing date data.
struct date
{
    std::int16_t year; //!< Year [0-inf).
    std::int16_t month; //!< Month of the year [1-12].
    std::int16_t day; //!< Day of the month [1-31].
};

//! \brief A type for representing timestamp data.
struct timestamp
{
    std::int16_t year;   //!< Year [0-inf).
    std::int16_t month;  //!< Month of the year [1-12].
    std::int16_t day;    //!< Day of the month [1-31].
    std::int16_t hour;   //!< Hours since midnight [0-23].
    std::int16_t min;    //!< Minutes after the hour [0-59].
    std::int16_t sec;    //!< Seconds after the minute.
    std::int32_t fract;  //!< Fractional seconds.
};

//! \}

//! \addtogroup mainc Main classes
//! \brief Main nanodbc classes.
//!
//! @{

//! \brief A resource for managing transaction commits and rollbacks.
//!
//! \attention You will want to use transactions if you are doing batch operations because it will prevent auto commits from occurring after each individual operation is executed.
class transaction
{
public:
    //! \brief Begin a transaction on the given connection object.
    //! \post Operations that modify the database must now be committed before taking effect.
    //! \throws database_error
    explicit transaction(const class connection& conn);

    //! Copy constructor.
    transaction(const transaction& rhs);

    //! Assignment.
    transaction& operator=(transaction rhs);

    //! Member swap.
    void swap(transaction& rhs) throw();

    //! \brief If this transaction has not been committed, will will rollback any modifying operations.
    ~transaction() throw();

    //! \brief Marks this transaction for commit.
    //! \throws database_error
    void commit();

    //! \brief Marks this transaction for rollback.
    void rollback() throw();

    //! Returns the connection object.
    class connection& connection();

    //! Returns the connection object.
    const class connection& connection() const;

    //! Returns the connection object.
    operator class connection&();

    //! Returns the connection object.
    operator const class connection&() const;

private:
    class transaction_impl;
    friend class nanodbc::connection;

private:
    std::shared_ptr<transaction_impl> impl_;
};

//! \brief Represents a statement on the database.
class statement
{
public:
    //! \brief Provides support for retrieving output/return parameters.
    //! \see binding
    enum param_direction
    {
        PARAM_IN //!< Binding an input parameter.
        , PARAM_OUT //!< Binding an output parameter.
        , PARAM_INOUT //!< Binding an input/output parameter.
        , PARAM_RETURN //!< Binding a return parameter.
    };

public:
    //! \brief Creates a new un-prepared statement.
    //! \see execute(), just_execute(), execute_direct(), just_execute_direct(), open(), prepare()
    statement();

    //! \brief Constructs a statement object and associates it to the given connection.
    //! \param conn The connection to use.
    //! \see open(), prepare()
    explicit statement(class connection& conn);

    //! \brief Constructs and prepares a statement using the given connection and query.
    //! \param conn The connection to use.
    //! \param query The SQL query statement.
    //! \param timeout The number in seconds before query timeout. Default is 0 indicating no timeout.
    //! \see execute(), just_execute(), execute_direct(), just_execute_direct(), open(), prepare()
    statement(class connection& conn, const string_type& query, long timeout = 0);

    //! Copy constructor.
    statement(const statement& rhs);

    //! Assignment.
    statement& operator=(statement rhs);

    //! Member swap.
    void swap(statement& rhs) throw();

    //! \brief Closes the statement.
    //! \see close()
    ~statement() throw();

    //! \brief Creates a statement for the given connection.
    //! \param conn The connection where the statement will be executed.
    //! \throws database_error
    void open(class connection& conn);

    //! \brief Returns true if connection is open.
    bool open() const;

    //! \brief Returns true if connected to the database.
    bool connected() const;

    //! \brief Returns the associated connection object if any.
    class connection& connection();

    //! \brief Returns the associated connection object if any.
    const class connection& connection() const;

    //! \brief Returns the native ODBC statement handle.
    void* native_statement_handle() const;

    //! \brief Closes the statement and frees all associated resources.
    void close();

    //! \brief Cancels execution of the statement.
    //! \throws database_error
    void cancel();

    //! \brief Opens and prepares the given statement to execute on the given connection.
    //! \param conn The connection where the statement will be executed.
    //! \param query The SQL query that will be executed.
    //! \param timeout The number in seconds before query timeout. Default is 0 indicating no timeout.
    //! \see open()
    //! \throws database_error
    void prepare(class connection& conn, const string_type& query, long timeout = 0);

    //! \brief Prepares the given statement to execute its associated connection.
    //! If the statement is not open throws programming_error.
    //! \param query The SQL query that will be executed.
    //! \param timeout The number in seconds before query timeout. Default is 0 indicating no timeout.
    //! \see open()
    //! \throws database_error, programming_error
    void prepare(const string_type& query, long timeout = 0);

    //! \brief Sets the number in seconds before query timeout. Default is 0 indicating no timeout.
    //! \throws database_error
    void timeout(long timeout = 0);

    //! \brief Immediately opens, prepares, and executes the given query directly on the given connection.
    //! \param conn The connection where the statement will be executed.
    //! \param query The SQL query that will be executed.
    //! \param batch_operations Numbers of rows to fetch per rowset, or the number of batch parameters to process.
    //! \param timeout The number in seconds before query timeout. Default is 0 indicating no timeout.
    //! \return A result set object.
    //! \attention You will want to use transactions if you are doing batch operations because it will prevent auto commits from occurring after each individual operation is executed.
    //! \see open(), prepare(), execute(), result, transaction
    class result execute_direct(class connection& conn, const string_type& query, long batch_operations = 1, long timeout = 0);

    //! \brief Execute the previously prepared query now without constructing result object.
    //! \param conn The connection where the statement will be executed.
    //! \param query The SQL query that will be executed.
    //! \param batch_operations Numbers of rows to fetch per rowset, or the number of batch parameters to process.
    //! \param timeout The number in seconds before query timeout. Default is 0 indicating no timeout.
    //! \throws database_error
    //! \return A result set object.
    //! \attention You will want to use transactions if you are doing batch operations because it will prevent auto commits from occurring after each individual operation is executed.
    //! \see open(), prepare(), execute(), execute_direct(), result, transaction
    void just_execute_direct(class connection& conn, const string_type& query, long batch_operations = 1, long timeout = 0);

    //! \brief Execute the previously prepared query now.
    //! \param batch_operations Numbers of rows to fetch per rowset, or the number of batch parameters to process.
    //! \param timeout The number in seconds before query timeout. Default is 0 indicating no timeout.
    //! \throws database_error
    //! \return A result set object.
    //! \attention You will want to use transactions if you are doing batch operations because it will prevent auto commits from occurring after each individual operation is executed.
    //! \see open(), prepare(), result, transaction
    class result execute(long batch_operations = 1, long timeout = 0);

    //! \brief Execute the previously prepared query now without constructing result object.
    //! \param batch_operations Numbers of rows to fetch per rowset, or the number of batch parameters to process.
    //! \param timeout The number in seconds before query timeout. Default is 0 indicating no timeout.
    //! \throws database_error
    //! \return A result set object.
    //! \attention You will want to use transactions if you are doing batch operations because it will prevent auto commits from occurring after each individual operation is executed.
    //! \see open(), prepare(), execute(), result, transaction
    void just_execute(long batch_operations = 1, long timeout = 0);

    //! \brief Returns the input and output paramters of the specified stored procedure.
    //! \param catalog The catalog name of the procedure.
    //! \param schema Pattern to use for schema names.
    //! \param procedure The name of the procedure.
    //! \param column Pattern to use for column names.
    //! \throws database_error
    //! \return A result set object.
    class result procedure_columns(const string_type& catalog, const string_type& schema, const string_type& procedure, const string_type& column);

    //! \brief Returns the number of rows affected by the request or -1 if the number of affected rows is not available.
    //! \throws database_error
    long affected_rows() const;

    //! \brief Returns the number of columns in a result set.
    //! \throws database_error
    short columns() const;

    //! \brief Resets all currently bound parameters.
    void reset_parameters() throw();

    //! \brief Returns the parameter size for the indicated parameter placeholder within a prepared statement.
    unsigned long parameter_size(short param) const;

    //! \addtogroup binding Binding parameters
    //! \brief These functions are used to bind values to ODBC parameters.
    //!
    //! @{

    //! \brief Binds the given value to the given parameter placeholder number in the prepared statement.
    //!
    //! If your prepared SQL query has any ? placeholders, this is how you bind values to them.
    //! Placeholder numbers count from left to right and are 0-indexed.
    //!
    //! It is NOT possible to use these functions for bulk operations as number of elements is not specified here.
    //!
    //! \param param Placeholder position.
    //! \param value Value to substitute into placeholder.
    //! \param direction ODBC parameter direction.
    //! \throws database_error
    template<class T>
    void bind(short param, const T* value, param_direction direction = PARAM_IN);

    //! \addtogroup bind_multi Binding multiple non-string values
    //! \brief Binds the given values to the given parameter placeholder number in the prepared statement.
    //!
    //! If your prepared SQL query has any ? placeholders, this is how you bind values to them.
    //! Placeholder numbers count from left to right and are 0-indexed.
    //!
    //! It is possible to use these functions for bulk operations.
    //!
    //! \param param Placeholder position.
    //! \param values Values to substitute into placeholder.
    //! \param elements The number of elements being bound.
    //! \param null_sentry Value which should represent a null value.
    //! \param nulls Flags for values that should be set to a null value.
    //! \param param_direciton ODBC parameter direction.
    //! \throws database_error
    //!
    //! @{

    //! \brief Binds multiple values.
    //! \see bind_multi
    template<class T>
    void bind(short param, const T* values, std::size_t elements, param_direction direction = PARAM_IN);

    //! \brief Binds multiple values.
    //! \see bind_multi
    template<class T>
    void bind(short param, const T* values, std::size_t elements, const T* null_sentry, param_direction direction = PARAM_IN);

    //! \brief Binds multiple values.
    //! \see bind_multi
    template<class T>
    void bind(short param, const T* values, std::size_t elements, const bool* nulls, param_direction direction = PARAM_IN);

    //! @}

    //! \addtogroup bind_strings Binding multiple string values
    //! \brief Binds the given string values to the given parameter placeholder number in the prepared statement.
    //!
    //! If your prepared SQL query has any ? placeholders, this is how you bind values to them.
    //! Placeholder numbers count from left to right and are 0-indexed.
    //!
    //! It is possible to use these functions for bulk operations.
    //!
    //! \param param Placeholder position.
    //! \param values Values to substitute into placeholder.
    //! \param length Maximum length of string elements.
    //! \param elements The number of elements being bound. Otherwise the value N is taken as the number of elements.
    //! \param null_sentry Value which should represent a null value.
    //! \param nulls Flags for values that should be set to a null value.
    //! \param param_direciton ODBC parameter direction.
    //! \throws database_error
    //!
    //! @{

    //! \brief Binds multiple string values.
    //! \see bind_strings
    void bind_strings(
        short param
        , const string_type::value_type* values
        , std::size_t length
        , std::size_t elements
        , param_direction direction = PARAM_IN);

    //! \brief Binds multiple string values.
    //! \see bind_strings
    template<std::size_t N, std::size_t M>
    void bind_strings(
        short param
        , const string_type::value_type(&values)[N][M]
        , param_direction direction = PARAM_IN)
    {
        bind_strings(
            param
            , reinterpret_cast<const string_type::value_type*>(values)
            , M
            , N
            , direction);
    }

    //! \brief Binds multiple string values.
    //! \see bind_strings
    void bind_strings(
        short param
        , const string_type::value_type* values
        , std::size_t length
        , std::size_t elements
        , const string_type::value_type* null_sentry
        , param_direction direction = PARAM_IN);

    //! \brief Binds multiple string values.
    //! \see bind_strings
    template<std::size_t N, std::size_t M>
    void bind_strings(
        short param
        , const string_type::value_type(&values)[N][M]
        , const string_type::value_type* null_sentry
        , param_direction direction = PARAM_IN)
    {
        bind_strings(
            param
            , reinterpret_cast<const string_type::value_type*>(values)
            , M
            , N
            , null_sentry
            , direction);
    }

    //! \brief Binds multiple string values.
    //! \see bind_strings
    void bind_strings(
        short param
        , const string_type::value_type* values
        , std::size_t length
        , std::size_t elements
        , const bool* nulls
        , param_direction direction = PARAM_IN);

    //! \brief Binds multiple string values.
    //! \see bind_strings
    template<std::size_t N, std::size_t M>
    void bind_strings(
        short param
        , const string_type::value_type(&values)[N][M]
        , const bool* nulls
        , param_direction direction = PARAM_IN)
    {
        bind_strings(
            param
            , reinterpret_cast<const string_type::value_type*>(values)
            , M
            , N
            , nulls
            , direction);
    }

    //! @}

    //! \brief Binds null values to the given parameter placeholder number in the prepared statement.
    //!
    //! If your prepared SQL query has any ? placeholders, this is how you bind values to them.
    //! Placeholder numbers count from left to right and are 0-indexed.
    //!
    //! It is possible to use this function for bulk operations.
    //!
    //! \param param Placeholder position.
    //! \param elements The number of elements being bound.
    //! \throws database_error
    void bind_null(short param, std::size_t elements = 1);

    //! @}

private:
    typedef std::function<bool (std::size_t)> null_predicate_type;

private:
    class statement_impl;
    friend class nanodbc::result;

private:
    std::shared_ptr<statement_impl> impl_;
};

//! \brief Manages and encapsulates ODBC resources such as the connection and environment handles.
class connection
{
public:
    //! \brief Create new connection object, initially not connected.
    connection();

    //! Copy constructor.
    connection(const connection& rhs);

    //! Assignment.
    connection& operator=(connection rhs);

    //! Member swap.
    void swap(connection&) throw();

    //! \brief Create new connection object and immediately connect to the given data source.
    //! \param dsn The name of the data source.
    //! \param user The username for authenticating to the data source.
    //! \param pass The password for authenticating to the data source.
    //! \param timeout The number in seconds before connection timeout. Default is 0 indicating no timeout.
    //! \throws database_error
    //! \see connected(), connect()
    connection(
        const string_type& dsn
        , const string_type& user
        , const string_type& pass
        , long timeout = 0);

    //! \brief Create new connection object and immediately connect using the given connection string.
    //! \param connection_string The connection string for establishing a connection.
    //! \param timeout The number in seconds before connection timeout. Default is 0 indicating no timeout.
    //! \throws database_error
    //! \see connected(), connect()
    connection(const string_type& connection_string, long timeout = 0);

    //! \brief Automatically disconnects from the database and frees all associated resources.
    //!
    //! Will not throw even if disconnecting causes some kind of error and raises an exception.
    //! If you explicitly need to know if disconnect() succeeds, call it directly.
    ~connection() throw();

    //! \brief Create new connection object and immediately connect to the given data source.
    //! \param dsn The name of the data source.
    //! \param user The username for authenticating to the data source.
    //! \param pass The password for authenticating to the data source.
    //! \param timeout The number in seconds before connection timeout. Default is 0 indicating no timeout.
    //! \throws database_error
    //! \see connected()
    void connect(
        const string_type& dsn
        , const string_type& user
        , const string_type& pass
        , long timeout = 0);

    //! \brief Create new connection object and immediately connect using the given connection string.
    //! \param connection_string The connection string for establishing a connection.
    //! \param timeout The number in seconds before connection timeout. Default is 0 indicating no timeout.
    //! \throws database_error
    //! \see connected()
    void connect(const string_type& connection_string, long timeout = 0);

    //! \brief Returns true if connected to the database.
    bool connected() const;

    //! \brief Disconnects from the database, but maintains environment and handle resources.
    void disconnect();

    //! \brief Returns the number of transactions currently held for this connection.
    std::size_t transactions() const;

    //! \brief Returns the native ODBC database connection handle.
    void* native_dbc_handle() const;

    //! \brief Returns the native ODBC environment handle.
    void* native_env_handle() const;

    //! \brief Returns the name of the ODBC driver.
    //! \throws database_error
    string_type driver_name() const;

private:
    std::size_t ref_transaction();
    std::size_t unref_transaction();
    bool rollback() const;
    void rollback(bool onoff);

private:
    class connection_impl;
    friend class nanodbc::transaction::transaction_impl;

private:
    std::shared_ptr<connection_impl> impl_;
};

//! \brief A resource for managing result sets from statement execution.
//!
//! \see statement::execute(), statement::execute_direct()
//! \note result objects may be copied, however all copies will refer to the same underlying ODBC result set.
class result
{
public:
    //! Empty result set.
    result();

    //! Free result set.
    ~result() throw();

    //! Copy constructor.
    result(const result& rhs);

    //! Assignment.
    result& operator=(result rhs);

    //! Member swap.
    void swap(result& rhs) throw();

    //! \brief Returns the native ODBC statement handle.
    void* native_statement_handle() const;

    //! \brief The rowset size for this result set.
    long rowset_size() const throw();

    //! \brief Returns the number of rows affected by the request or -1 if the number of affected rows is not available.
    //! \throws database_error
    long affected_rows() const;

    //! \brief Returns the number of rows in the current rowset or 0 if the number of rows is not available.
    long rows() const throw();

    //! \brief Returns the number of columns in a result set.
    //! \throws database_error
    short columns() const;

    //! \brief Fetches the first row in the current result set.
    //! \return true if there are more results or false otherwise.
    //! \throws database_error
    bool first();

    //! \brief Fetches the last row in the current result set.
    //! \return true if there are more results or false otherwise.
    //! \throws database_error
    bool last();

    //! \brief Fetches the next row in the current result set.
    //! \return true if there are more results or false otherwise.
    //! \throws database_error
    bool next();

    //! \brief Fetches the prior row in the current result set.
    //! \return true if there are more results or false otherwise.
    //! \throws database_error
    bool prior();

    //! \brief Moves to and fetches the specified row in the current result set.
    //! \return true if there are results or false otherwise.
    //! \throws database_error
    bool move(long row);

    //! \brief Skips a number of rows and then fetches the resulting row in the current result set.
    //! \return true if there are results or false otherwise.
    //! \throws database_error
    bool skip(long rows);

    //! \brief Returns the row position in the current result set.
    unsigned long position() const;

    //! \brief Returns true if there are no more results in the current result set.
    bool end() const throw();

    //! \brief Gets data from the given column of the current rowset.
    //!
    //! Columns are numbered from left to right and 0-indexed.
    //! \param column position.
    //! \param result The column's value will be written to this parameter.
    //! \throws database_error, index_range_error, type_incompatible_error, null_access_error
    template<class T>
    void get_ref(short column, T& result) const;

    //! \brief Gets data from the given column of the current rowset.
    //! If the data is null, fallback is returned instead.
    //!
    //! Columns are numbered from left to right and 0-indexed.
    //! \param column position.
    //! \param fallback if value is null, return fallback instead.
    //! \param result The column's value will be written to this parameter.
    //! \throws database_error, index_range_error, type_incompatible_error
    template<class T>
    void get_ref(short column, const T& fallback, T& result) const;

    //! \brief Gets data from the given column by name of the current rowset.
    //!
    //! \param column_name column's name.
    //! \param result The column's value will be written to this parameter.
    //! \throws database_error, index_range_error, type_incompatible_error, null_access_error
    template<class T>
    void get_ref(const string_type& column_name, T& result) const;

    //! \brief Gets data from the given column by name of the current rowset.
    //! If the data is null, fallback is returned instead.
    //!
    //! \param column_name column's name.
    //! \param fallback if value is null, return fallback instead.
    //! \param result The column's value will be written to this parameter.
    //! \throws database_error, index_range_error, type_incompatible_error
    template<class T>
    void get_ref(const string_type& column_name, const T& fallback, T& result) const;

    //! \brief Gets data from the given column of the current rowset.
    //!
    //! Columns are numbered from left to right and 0-indexed.
    //! \param column position.
    //! \throws database_error, index_range_error, type_incompatible_error, null_access_error
    template<class T>
    T get(short column) const;

    //! \brief Gets data from the given column of the current rowset.
    //! If the data is null, fallback is returned instead.
    //!
    //! Columns are numbered from left to right and 0-indexed.
    //! \param column position.
    //! \param fallback if value is null, return fallback instead.
    //! \throws database_error, index_range_error, type_incompatible_error
    template<class T>
    T get(short column, const T& fallback) const;

    //! \brief Gets data from the given column by name of the current rowset.
    //!
    //! \param column_name column's name.
    //! \throws database_error, index_range_error, type_incompatible_error, null_access_error
    template<class T>
    T get(const string_type& column_name) const;

    //! \brief Gets data from the given column by name of the current rowset.
    //! If the data is null, fallback is returned instead.
    //!
    //! \param column_name column's name.
    //! \param fallback if value is null, return fallback instead.
    //! \throws database_error, index_range_error, type_incompatible_error
    template<class T>
    T get(const string_type& column_name, const T& fallback) const;

    //! \brief Returns true if and only if the given column of the current rowset is null.
    //!
    //! Columns are numbered from left to right and 0-indexed.
    //! \param column position.
    //! \throws database_error, index_range_error
    bool is_null(short column) const;

    //! \brief Returns true if and only if the given column by name of the current rowset is null.
    //!
    //! \param column_name column's name.
    //! \throws database_error, index_range_error
    bool is_null(const string_type& column_name) const;

    //! \brief Returns the name of the specified column.
    //!
    //! Columns are numbered from left to right and 0-indexed.
    //! \param column position.
    //! \throws index_range_error
    string_type column_name(short column) const;

    //! \brief Returns the size of the specified column.
    //!
    //! Columns are numbered from left to right and 0-indexed.
    //! \param column position.
    //! \throws index_range_error
    long column_size(short column) const;

    //! \brief Returns the column number of the specified column name.
    //!
    //! Columns are numbered from left to right and 0-indexed.
    //! \param column_name column's name.
    //! \throws index_range_error
    short column(const string_type& column_name) const;

    //! Returns a identifying integer value representing the SQL type of this column.
    int column_datatype(short column) const;

    //! Returns a identifying integer value representing the SQL type of this column by name.
    int column_datatype(const string_type& column_name) const;

    //! Returns a identifying integer value representing the C type of this column.
    int column_c_datatype(short column) const;

    //! Returns a identifying integer value representing the C type of this column by name.
    int column_c_datatype(const string_type& column_name) const;

    //! Returns the next result, for example when stored procedure returns multiple result sets.
    bool next_result();

    //! If and only if result object is valid, returns true.
    explicit operator bool() const;

private:
    result(statement statement, long rowset_size);

private:
    class result_impl;
    friend class nanodbc::statement::statement_impl;

private:
    std::shared_ptr<result_impl> impl_;
};

//! @}

//! \addtogroup mainf Free Functions
//! \brief Convenience functions.
//!
//! @{

//! \brief Immediately opens, prepares, and executes the given query directly on the given connection.
//! \param conn The connection where the statement will be executed.
//! \param query The SQL query that will be executed.
//! \param batch_operations Numbers of rows to fetch per rowset, or the number of batch parameters to process.
//! \param timeout The number in seconds before query timeout. Default is 0 indicating no timeout.
//! \return A result set object.
//! \attention You will want to use transactions if you are doing batch operations because it will prevent auto commits from occurring after each individual operation is executed.
//! \see open(), prepare(), execute(), result, transaction
result execute(
    connection& conn
    , const string_type& query
    , long batch_operations = 1
    , long timeout = 0);

//! \brief Immediately opens, prepares, and executes the given query directly on the given connection without creating result object.
//! \param conn The connection where the statement will be executed.
//! \param query The SQL query that will be executed.
//! \param batch_operations Numbers of rows to fetch per rowset, or the number of batch parameters to process.
//! \param timeout The number in seconds before query timeout. Default is 0 indicating no timeout.
//! \return A result set object.
//! \attention You will want to use transactions if you are doing batch operations because it will prevent auto commits from occurring after each individual operation is executed.
//! \see open(), prepare(), execute(), result, transaction
void just_execute(
    connection& conn
    , const string_type& query
    , long batch_operations = 1
    , long timeout = 0);

//! \brief Execute the previously prepared query now.
//! \param stmt The prepared statement that will be executed.
//! \param batch_operations Numbers of rows to fetch per rowset, or the number of batch parameters to process.
//! \throws database_error
//! \return A result set object.
//! \attention You will want to use transactions if you are doing batch operations because it will prevent auto commits from occurring after each individual operation is executed.
//! \see open(), prepare(), execute(), result
result execute(statement& stmt, long batch_operations = 1);

//! \brief Execute the previously prepared query now and without creating result object.
//! \param stmt The prepared statement that will be executed.
//! \param batch_operations Numbers of rows to fetch per rowset, or the number of batch parameters to process.
//! \throws database_error
//! \return A result set object.
//! \attention You will want to use transactions if you are doing batch operations because it will prevent auto commits from occurring after each individual operation is executed.
//! \see open(), prepare(), execute(), result
void just_execute(statement& stmt, long batch_operations = 1);

//! \brief Execute the previously prepared query now.
//! Executes within the context of a transaction object and commits the transaction directly after execution.
//! \param stmt The prepared statement that will be executed in batch.
//! \param batch_operations Numbers of rows to fetch per rowset, or the number of batch parameters to process.
//! \throws database_error
//! \return A result set object.
//! \see open(), prepare(), execute(), result, transaction
result transact(statement& stmt, long batch_operations);

//! \brief Execute the previously prepared query now and without creating result object.
//! Executes within the context of a transaction object and commits the transaction directly after execution.
//! \param stmt The prepared statement that will be executed in batch.
//! \param batch_operations Numbers of rows to fetch per rowset, or the number of batch parameters to process.
//! \throws database_error
//! \return A result set object.
//! \see open(), prepare(), execute(), result, transaction
void just_transact(statement& stmt, long batch_operations);

//! \brief Prepares the given statement to execute on it associated connection.
//! If the statement is not open throws programming_error.
//! \param stmt The prepared statement that will be executed in batch.
//! \param query The SQL query that will be executed.
//! \param timeout The number in seconds before query timeout. Default is 0 indicating no timeout.
//! \see open()
//! \throws database_error, programming_error
void prepare(statement& stmt, const string_type& query, long timeout = 0);

//! @}

} // namespace nanodbc

#endif // NANODBC_H
