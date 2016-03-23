# v2.12.4

Resolves a possible crash with `SQLDescribeParam()`. In Progress OpenEdge 11 driver setting the
nullableptr argument to null causes a crash. This does not affect SQLite or MySQL drivers.

Thanks to [@AndrewJD79](https://github.com/AndrewJD79) for finding and diagnosing the issue!

# v2.12.3

Unicode: Resolves a major issue with BLOB datatype handling for BINARY and TEXT columns.

# v2.12.2

Resolves a major issue with BLOB datatype handling for BINARY and TEXT columns.

# v2.12.1

Resolves a Travis-CI build issue.

# v2.12.0

Major work undertaken by Mateusz Łoskot provides new features and a host of bug fixes throughout.
Refactoring work moves nanodbc away from platform dependent `wchar_t` in favor of `char16_t` or in the
case of iODBC with unicode build enabled, `char32_t`. Boost.Test dropped in this version, in favor of Catch.

## New Features

- Converts usages of `wstring` and `wchar_t` to `u16string` and `char16_t`.
- Enable iODBC + Unicode support with `u32string` types.
- Add example program `table_schema.cpp`.
- Add `dbms_name()` and `dbms_version()` methods to `connection` class.

## Testing

- Migrates tests from Boost.Test to Catch framework.
- Enables unicode tests on travis-ci.
- Syncs `Dockerfile` and `Vagrantfile`; adds quick usage docs for vagrant.
- Switch Dockerfile over to `ubuntu:precise` (default).
- Improve `odbc_test.cpp` to cope with DBMS variations.

## Bug Fixes

- Fix compiler warnings while building with VS2015.
- Add missing optional `schema_name` parameter to usage info.
- Workaround for VS2015 bug in `std::codecvt` for `char16_t`.
- Fix retrieval of variable-length data in parts.
- Fix `catalog::columns::is_nullable()` to handle valid `NULL`.
- Fix check of total of characters required to display `SQL_DATE`.
- Fix `SELECT` result sorting with `NULL` values involved.

# v2.11.3

- Fixes segmentation fault issue with unixODBC on Linux systems.
- Adds support for `while(!results.end())` style iteration.

# v2.11.2

- Adds this CHANGELOG.md file. Future releases should update it accordingly!
- Adds CHANGELOG.md helper script.

# v2.11.1

## New Features

- Major thanks again to Mateusz Łoskot for all the new features!
- Adds convenient access to catalog objects (tables, columns, primary keys).
- Adds `database_name` and `catalog_name `methods to connection class.
- Adds CMake option `NANODBC_ENABLE_LIBCXX` to enable/disable libc++ builds.
- Adds CMake option `NANODBC_EXAMPLES` to enable/disable the example target.
- Adds a `latest` release branch to track most recent release.

## Testing

- Massive updates to Travis CI continuous integration.
- Adds general `odbc_test` to target variety of ODBC drivers.
- Adds specific MySQL tests.
- Updates test target organization.
    - The way the targets were designed is such that:
        - test: runs all tests, but will not build them
        - tests: builds all tests, but does not run them
        - check: builds all tests and then runs all tests
    - For individual tests then, it makes sense to use:
        - ${name}_test: runs ${name}_test, but will not build it
        - ${name}_tests: builds ${name}_test, but does not run it
        - ${name}_check: builds ${name}_test and then runs it

## Bug Fixes

- Fix test check of `result::affected_rows` for `SELECT` statement.
- Fix `result::position` to make it consistent with `SQL_ATTR_ROW_NUMBER`.
- Fix string object construction syntax.
- Adds missing `#include <cstring>`.

## Other Changes

- More robust and friendly publish and release scripts.
- Updates to README and documentation.
- Adds `-DUNICODE` and `-D_UNICODE` for Visual Studio projects.
- Adds examples based on the documentation.
- Adds `rowset_iteration` example.

# v2.10.0

## New Features

- Major thanks to Mateusz Łoskot for all the effort!
- Adds Dockerfile to support testing and development.
- Adds build.bat convenience script for Visual Studio users.
- Adds CMake options `NANODBC_INSTALL` and `NANODBC_TEST` to control generation of those targets.

## Bug Fixes

- Fixes cmake build on OS X El Capitan.
- Refine assert in `result_impl::position` with `SQL_ROW_NUMBER_UNKNOWN`.
- MSBuild Platform property for 32-bit is Win32.
- Reset null indicator before move for all columns, not just bound columns.
- Fixes doxygen generation of macro docs.

# v2.9.1

## New Features

- Adds Vagrantfile to support testing and development.
- Adds customizable `NANODBC_ASSERT` macro.
- Adds CMake option `NANODBC_STATIC` (default OFF).
- Clean up Visual C++ 64-bit warnings.

## Bug Fixes

- CMake: Fixes ODBC linking on Unix.
- Adds documentation on is_null() limitation.
- Write null indicator to `cbdata_` if indicated by `SQLGetData`.

## Testing

- Initial configuration of Travis CI build matrix.

## Other Changes

- Added a Contributing section to readme.
- Updates to SQLite tests.
- Disable MSVC warning C4244 in tests.

# v2.8.1

- Update CMakeLists.txt to enable builds with Visual Studio. Thanks Mateusz Łoskot!
- Add async connection support, plus extended database_error info. Thanks Yao Wei Tjong!
- Add linking against ODBC libraries on Windows.
- Change `param_type_from_direction` to throw `programming_error`.
- Define `NANODBC_SNPRINTF` in terms of `_snprintf_s` for MSVC.
- Setting CMake `-DNANODBC_ODBC_VERSION` option now works.

# v2.7.0

- Adds move constructors.
- Fixes Xcode MARK comments.
- Adds section comment banners to header file.
- Removes `throw()` from header files, uses `noexcept` instead.
- Adds basic and sqlite `std::move` test case.

# v2.6.0

- Resolves issue with decimal digits/scale and rounding. Thanks dedomilo!
- Resolve issue with `DECIMAL` to string conversion. Thanks dedomilo!

# v2.5.1

- Disable default unicode on windows.
- Override ODBC version with `NANODBC_ODBC_VERSION`.

# v2.4.0

- Add `statement::async_execute_direct` and `statement::async_complete`. Thanks Jon Valvatne!
- Add NOEXCEPT define to allow compilation under Visual Studio 2013.

# v2.3.0

- Provides optional Boost workaround for missing codecvt support in libstdc++.

# v2.2.3

- Adds minimap banners for code navigation.
- Adds `column_c_datatype()`.
- Converts line endings to unix.
- Adds `just_execute` class of functions that don't create result objects.

# v2.1.0

- Adds publish script.
- Fixes broken links in readme.
- Use C++11's `=delete` where appropriate.

# v2.0.1

- Fixes many documentation issues.
- Adds more todo info about updating docs.
- Adds notes about different versions.
- Cleans up style; removes CPP11 macros and C++03 support cruft.
- Silence warnings and untabify.
- Works with Unicode (std::wstring as nanodbc::string_type)
- Using Nanodbc with SQL Server Native Client works with nvarchar(max) and varchar(max) fields in Win32 and Win64.

# v1.0.0

Version 1.0.0 and all commits prior are now completely unsupported.
