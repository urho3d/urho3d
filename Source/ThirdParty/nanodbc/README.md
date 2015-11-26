# Synopsis

A very small C++ wrapper for the native C ODBC API. Please see the [online documentation](http://lexicalunit.github.com/nanodbc/) for user information, example usage, propaganda, and detailed source level documentation.

# Versions

| Tag or Branch | Description |
| --------------| ----------- |
| `master`      | This branch contains the latest development code, possibly not ready for release yet. |
| `release`     | This branch is always tagged to the most recent stable release. |
| `v2.0.0`      | Supports C++11 only. All future development will build upon this version. |
| `v1.0.0`      | Supports C++03 and optionally C++11. *There is no longer any support for this version.* |

# Building

You don't necessarily need to build nanodbc, as you can just drop the header and implementation files into your project. However I have provided [CMake](http://www.cmake.org/) files which can be used to build a shared library object, or build and run the included unit tests. The CMake files will also support out of source builds.

Unit tests are built using [Boost.Test](http://www.boost.org/doc/libs/release/libs/test/) and therefore require Boost be installed. In order to build the tests you will also need to have either unixODBC or iODBC installed and discoverable by CMake. This is easy on OS X (for example) where you can just use [Homebrew](http://brew.sh/) to install unixODBC with `brew install unixodbc`, or simply use the system provided iODBC if you have OS X prior to 10.9. Also note that you can install Boost via Homebrew as well, which is very convenient!

Finally, the unit tests attempt to connect to a [SQLite](https://www.sqlite.org/) database, so you will have to have that and a SQLite ODBC driver installed. At the time of this writing, there happens to be a nice [SQLite ODBC driver](http://www.ch-werner.de/sqliteodbc/) available from Christian Werner's website. The tests expect to find a data source named `sqlite`. So for example, your `odbcinst.ini` file on OS X might have a section similar to the following.

```
[sqlite]
Description             = SQLite ODBC Driver
Driver                  = /usr/lib/libsqlite3odbc-0.93.dylib
Setup                   = /usr/lib/libsqlite3odbc-0.93.dylib
Threading               = 2
```

## Example Build Process

It's most convenient to create a build directory for an out of source build, but this isn't required. After you've used cmake to generate your Makefiles, you probably only really need to be aware of `make nanodbc` which will build your shared object, or `make check` which will build and run the unit tests. If the unit tests fail, please don't hesitate to report it by creating an issue [with your detailed test log](http://stackoverflow.com/questions/5709914/using-cmake-how-do-i-get-verbose-output-from-ctest)! You may also want to install nanodbc to your system using `make install`.

```shell
cd path/to/nanodbc/repository
mkdir build
cd build
cmake .. [-DNANODBC_USE_UNICODE=ON]
make # creates shared library
make nanodbc # creates shared library
make tests # only builds the unit tests
make test # only runs the unit tests
make check # builds and then runs unit tests
make install # installs nanodbc.h and shared library
```

## Future work

### NANODBC_HANDLE_NODATA_BUG

A macro `NANODBC_HANDLE_NODATA_BUG` was introduced to handle drivers like vertica's which return `SQL_NO_DATA` where they probably shouldn't. It would be nice to have the library *just work* instead of having to rely on users compiling with this flag set properly for their driver.

### C++11

Moving forward, nanodbc will target C++11. Since it was originally developed for C++03, it would probably be a good idea to go through it and see what places it can be updated. This shouldn't be too bad because nanodbc has had optional C++11 support for a long time.

### Todo

- More tests for a large variety of drivers. Include performance tests.
- Clean up `bind_*` family of functions, reduce any duplication.
- Improve documentation: The main website and API docs should be more responsive.
