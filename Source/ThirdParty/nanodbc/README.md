![nanodbc-banner][nanodbc-banner]

A small C++ wrapper for the native C ODBC API. Please see the [online documentation][nanodbc] for
user information, example usage, propaganda, and detailed source level documentation.

[![GitHub release](https://img.shields.io/github/tag/lexicalunit/nanodbc.svg)](https://github.com/lexicalunit/nanodbc/releases)
[![GitHub commits](https://img.shields.io/github/commits-since/lexicalunit/nanodbc/v2.12.4.svg?style=flat-square)](https://github.com/lexicalunit/nanodbc/releases/tag/v2.12.4)
[![License](https://img.shields.io/github/license/lexicalunit/nanodbc.svg?style=flat-square)](https://github.com/lexicalunit/nanodbc/blob/master/LICENSE)

[![Gitter](https://img.shields.io/gitter/room/lexicalunit/nanodbc.svg?style=flat-square)](https://gitter.im/nanodbc-help/Lobby)

## Build Status

| Branch |  Linux/OSX | Windows | Coverity |
|:--- |:--- |:--- |:--- |
| `master`  | [![master][travis-badge-master]][travis] | [![master][appveyor-badge]][appveyor] | [![coverity_scan][coverity-badge]][coverity] |
| `latest` | [![latest][travis-badge-latest]][travis] | &nbsp; | &nbsp; |
| `release` | [![release][travis-badge-release]][travis] | &nbsp; | &nbsp; |

> **Note:** The Coverity status uses the [coverity_scan][nanodbc-coverity] branch. When `master`
            has had a significant amount of work pushed to it, merge those changes into
            `coverity_scan` as well to keep the status up to date.

## Philosophy

The native C API for working with ODBC is exorbitantly verbose, ridiculously complicated, and
fantastically brittle. nanodbc addresses these frustrations! The goal for nanodbc is to make
developers happy. Common tasks should be easy, requiring concise and simple code.

The [latest C++ standards][cpp-std] and [best practices][cpp-core] are
_enthusiastically_ incorporated to make the library as future-proof as possible. To accommodate
users who can not use the latest and greatest, [semantic versioning][semver] and
release notes will clarify required C++ features and/or standards for particular versions.

### Design Decisions

All complex objects in nanodbc follow the [pimpl (Pointer to IMPLementation)][pimpl] idiom to
provide separation between interface and implementation, value semantics, and a clean `nanodbc.h` header file that includes nothing but standard C++ headers.

nanodbc wraps ODBC code, providing a simpler way to do the same thing. We try to be as featureful
as possible, but I can't guarantee you'll never have to write supporting ODBC code. Personally, I
have never had to do so.

Major features beyond what's already supported by ODBC are not within the scope of nanodbc. This is
where the *nano* part of nanodbc becomes relevant: This library is _as minimal as possible_. That
means no dependencies beyond standard C++ and typical ODBC headers. No features unsupported by
existing ODBC API calls.

## Branches

| Version | Description |
|:--- |:--- |
| `release` | Most recent published version that's deemed "stable". Review the [changelog notes](CHANGELOG.md) to see if this version is right for you. |
| `latest`  | Latest published version; please use this version if CI tests are all passing. **[See all available versions.][nanodbc-releases]** |
| `master`  | Contains the latest development code, not yet ready for a published version. |
| `v2.x.x`  | Targets C++14+. All future development will build upon this version. |
| `v1.x.x`  | Supports C++03 and optionally C++11. *There is no longer any support for this version.* |

# Building

nanodbc is intentionally small enough that you can drag and drop the header and implementation
files into your project and run with it. For those that want it, I have also provided
[CMake][cmake] files which build a library object, or build and run the included tests. The CMake
files will also support out of source builds.

Tests use the [Catch][catch] test framework, and CMake will automatically fetch the latest version
of Catch for you at build time. To build the tests you will also need to have either unixODBC or
iODBC installed and discoverable by CMake. This is easy on OS X where you can use [Homebrew][brew]
to install unixODBC with `brew install unixodbc`, or use the system provided iODBC if you have OS X
10.9 or earlier.

The tests attempt to connect to a [SQLite][sqlite] database, so you will have to have that and a
SQLite ODBC driver installed. At the time of this writing, there happens to be a nice
[SQLite ODBC driver][sqliteodbc] available from Christian Werner's website, also available via
Homebrew as `sqliteobdc`! The tests expect to find a data source named `sqlite` on *nix systems and
`SQLite3 ODBC Driver` on Windows systems. For example, your `odbcinst.ini` file on OS X must have a
section like the following.

```
[sqlite]
Description             = SQLite3 ODBC Driver
Setup                   = /usr/lib/libsqlite3odbc-0.93.dylib
Driver                  = /usr/lib/libsqlite3odbc-0.93.dylib
Threading               = 2
```

## Example Build Process

It's most convenient to create a build directory for an out of source build, but this isn't
required. After you've used cmake to generate your Makefiles, `make nanodbc` will build your shared
object. `make check` will build and run the tests. You can also install nanodbc to your system
using `make install`.

If the tests fail, please don't hesitate to [**report it**][nanodbc-new-issue] by creating an issue
with your detailed test log (prepend your `make` command with `env CTEST_OUTPUT_ON_FAILURE=1 ` to
enable verbose output please).

```shell
cd path/to/nanodbc/repository
mkdir build
cd build
cmake [Build Options] ..
make # creates shared library
make nanodbc # creates shared library
make tests # builds the tests
make test # runs the tests
make check # builds and then runs tests
make examples # builds all the example programs
make install # installs nanodbc.h and shared library
```

## Build Options

The following build options are available via [CMake command-line option][cmake-docs] `-D`. If you
are not using CMake to build nanodbc, you will need to set the corresponding `-D` compile define
flags yourself.

All boolean options follow the CMake [OPTION][cmake-option] default value convention: if no initial value is provided, `OFF` is used.

Use the standard CMake option `-DBUILD_SHARED_LIBS=ON` to build nanodbc as shared library.

If you need to use the `NANODBC_ENABLE_BOOST=ON` option, you will have to configure your environment to use [Boost][boost].

| CMake&nbsp;Option                  | Possible&nbsp;Values | Details |
| -----------------------------------| ---------------------| ------- |
| `NANODBC_DISABLE_ASYNC`            | `OFF` or `ON`        | Disable all async features. May resolve build issues in older ODBC versions. |
| `NANODBC_DISABLE_EXAMPLES`         | `OFF` or `ON`        | Do not build examples. |
| `NANODBC_DISABLE_INSTALL`          | `OFF` or `ON`        | Do not generate install target. |
| `NANODBC_DISABLE_LIBCXX`           | `OFF` or `ON`        | Do not use libc++, if available on the system. |
| `NANODBC_DISABLE_TESTS`            | `OFF` or `ON`        | Do not build tests. |
| `NANODBC_ENABLE_BOOST`             | `OFF` or `ON`        | Use Boost for Unicode string convertions (requires [Boost.Locale][boost-locale]). Workaround to issue [#44](https://github.com/lexicalunit/nanodbc/issues/44). |
| `NANODBC_ENABLE_UNICODE`           | `OFF` or `ON`        | Enable Unicode support. `nanodbc::string` becomes `std::u16string` or `std::u32string`. |
| `NANODBC_ENABLE_WORKAROUND_NODATA` | `OFF` or `ON`        | Enable `SQL_NO_DATA` workaround to issue [#33](https://github.com/lexicalunit/nanodbc/issues/33). |
| `NANODBC_ODBC_VERSION`             | `SQL_OV_ODBC3[...]`  | Forces ODBC version to use. Default is `SQL_OV_ODBC3_80` if available, otherwise `SQL_OV_ODBC3`. |

## Note About iODBC

Under Windows `sizeof(wchar_t) == sizeof(SQLWCHAR) == 2`, yet on Unix systems
`sizeof(wchar_t) == 4`. On unixODBC, `sizeof(SQLWCHAR) == 2` while on iODBC,
`sizeof(SQLWCHAR) == sizeof(wchar_t) == 4`. This leads to incompatible ABIs between applications
and drivers. If building against iODBC and the build option `NANODBC_USE_UNICODE` is `ON`, then
`nanodbc::string` will be `std::u32string`. In **ALL** other cases it will be `std::u16string`.

Continuous integration tests run on [Travis-CI][travis]. The build platform does not make available
a Unicode-enabled iODBC driver. As such there is no guarantee that tests will pass in entirety on a
system using iODBC. My recommendation is to use unixODBC. If you must use iODBC, consider
_disabling_ unicode mode to avoid `wchar_t` issues.

---

# Contributing

## Code Style

[`clang-format`][clang-format] handles all C++ code formatting for nanodbc. This utility is
[brew-installable][brew] on OS X (`brew install clang-format`) and is available on all major
platforms. See our `.clang-format` configuration file for details on the style. The script
`utility/style.sh` formats all code in the repository automatically. To run `clang-format` on a
single file use the following.

```shell
$ clang-format -i /path/to/file
```

**Please auto-format all code submitted in Pull Requests.**

## Source Level Documentation

Source level documentation provided via [GitHub's gh-pages][gh-pages] is available at
[nanodbc.lexicalunit.com][nanodbc]. To re-build and update it, preform the following steps from the
root directory of the repository:

1. `git clone -b gh-pages git@github.com:lexicalunit/nanodbc.git doc` Necessary the first time,
   not subsequently.
2. `cd doc`
3. `make` Generates updated documentation locally.
4. `make commit` Adds and commits any updated documentation.
5. `git push origin gh-pages` Deploys the changes to github.

Building documentation and gh-pages requires the use of [Doxygen][doxygen] and
[jekyll][jekyll]. See the [`Makefile` on the `gh-pages` branch][nanodbc-makefile] for more details.

## Quick Setup for Testing or Development Environments

To get up and running with nanodbc as fast as possible consider using the provided
[Dockerfile](Dockerfile) or [Vagrantfile](Vagrantfile). For example, to spin up a [docker][docker]
container suitable for testing and development of nanodbc:

```shell
$ cd /path/to/nanodbc
$ docker build -t nanodbc .
$ docker run -v "$(pwd)":"/opt/$(basename $(pwd))" -it nanodbc /bin/bash
root@hash:/# mkdir -p /opt/nanodbc/build && cd /opt/nanodbc/build
root@hash:/opt/nanodbc/build# cmake ..
root@hash:/opt/nanodbc/build# make nanodbc
```

Or, to build and ssh into a [vagrant][vagrant] VM (using VirtualBox for example) use:

```shell
$ cd /path/to/nanodbc
$ vagrant up
$ vagrant ssh
vagrant@vagrant-ubuntu-precise-64:~$ git clone https://github.com/lexicalunit/nanodbc.git
vagrant@vagrant-ubuntu-precise-64:~$ mkdir -p nanodbc/build && cd nanodbc/build
vagrant@vagrant-ubuntu-precise-64:~$ CXX=g++-5 cmake ..
vagrant@vagrant-ubuntu-precise-64:~$ make nanodbc
```

## Tests

One of important objectives is to maintain nanodbc covered with tests. New contributions
submitted via Pull Requests must include corresponding tests. This is important to ensure
the quality of new features.

The good news is that adding tests is easy!

The tests structure:

- `tests/base_test_fixture.h` includes a set of common test cases.
- `tests/<database>_test.cpp` is a source code for an independent test program that includes both,
  common and database-specific test cases.

To add new test case:

1. In `tests/base_test_fixture.h` file, add a new test case method to `base_test_fixture`
   class (e.g. `void my_feature_test()`).
2. In each `tests/<database>_test.cpp` file, copy and paste the `TEST_CASE_METHOD` boilerplate,
   updating name, tags, etc.

If a feature requires a database-specific test case for each database, then skip the
`tests/base_test_fixture.h` step and write a dedicated test case directly in
`tests/<database>_test.cpp` file.

## Publish and Release Process

Once your local `master` branch is ready for publishing
(i.e. [semantic versioning][semver]), use the `utility/publish.sh` script. This script
bumps the major, minor, or patch version, then updates the repository's `VERSION` file, adds a
"Preparing" commit, and creates git tags appropriately. For example to make a minor update you
would run `./utility/publish.sh minor`.

> **Important:** Always update [`CHANGELOG.md`](CHANGELOG.md) with information about new changes,
                 bug fixes, and features when making a new release. Use the `./utility/changes.sh`
                 script to aid in your composition of this document. The publish script itself will
                 attempt to verify that the changelog file has been properly updated.

To do this manually instead, use the following steps &mdash; for example a minor update from
`2.9.x` to `2.10.0`:

1. `echo "2.10.0" > VERSION`
2. `git add VERSION`
3. `git commit -m "Preparing 2.10.0 release."`
4. `git tag -f "v2.10.0"`
5. `git push -f origin "v2.10.0"`
6. `git push -f origin master:latest`

### Release Process

Release nanodbc with the `utility/release.sh` script. All this script does is push out the `master`
branch to the `release` branch, indicating that a new "stable" published version of nanodbc exists.
To do so manually, execute `git push -f origin master:release`. **Caution: Do this for versions
deemed "stable" based on suitable criteria.**

## Future work

### Good to Have / Want Someday

- Refactor tests to follow BDD pattern.
- Update codebase to use more C++14 idioms and patterns.
- Write more tests with the goal to have much higher code coverage.
- More tests for a large variety of drivers. Include performance tests.
- Clean up `bind_*` family of functions, reduce any duplication.
- Improve documentation: The main website and API docs should be more responsive.
- Provide more examples in documentation, more details, and point out any gotchas.
- Versioned generated source level API documentation for `release` and `latest`.
  For each major and minor published versions too?
- Add "HOWTO Build" documentation for Windows, OS X, and Linux.

---

[MIT][mit] &copy; [lexicalunit][author] and [contributors][contributors].

[mit]:              http://opensource.org/licenses/MIT
[author]:           http://github.com/lexicalunit
[contributors]:     https://github.com/lexicalunit/nanodbc/graphs/contributors

[nanodbc]:              http://lexicalunit.github.com/nanodbc/
[nanodbc-banner]:       https://cloud.githubusercontent.com/assets/1903876/11858632/cc0e21e6-a428-11e5-9a84-39fa27984914.png
[nanodbc-coverity]:     https://github.com/lexicalunit/nanodbc/tree/coverity_scan
[nanodbc-makefile]:     https://github.com/lexicalunit/nanodbc/blob/gh-pages/Makefile
[nanodbc-new-issue]:    https://github.com/lexicalunit/nanodbc/issues/new
[nanodbc-releases]:     https://github.com/lexicalunit/nanodbc/releases

[boost]:        http://www.boost.org/
[boost-locale]: http://www.boost.org/doc/libs/release/libs/locale/
[brew]:         http://brew.sh/
[catch]:        https://github.com/philsquared/Catch
[clang-format]: http://clang.llvm.org/docs/ClangFormat.html
[cmake-docs]:   https://cmake.org/cmake/help/latest/manual/cmake.1.html
[cmake]:        http://www.cmake.org/
[cmake-option]: http://cmake.org/cmake/help/latest/command/option.html
[cpp-core]:     https://github.com/isocpp/CppCoreGuidelines
[cpp-std]:      https://isocpp.org/std/status
[docker]:       https://www.docker.com/
[doxygen]:      http://www.doxygen.org
[gh-pages]:     https://help.github.com/articles/what-are-github-pages/
[jekyll]:       https://jekyllrb.com/
[pimpl]:        http://c2.com/cgi/wiki?PimplIdiom
[semver]:       http://semver.org/
[sqlite]:       https://www.sqlite.org/
[sqliteodbc]:   http://www.ch-werner.de/sqliteodbc/
[vagrant]:      https://www.vagrantup.com/

[travis]:               https://travis-ci.org/lexicalunit/nanodbc
[travis-badge-latest]:  https://travis-ci.org/lexicalunit/nanodbc.svg?branch=latest
[travis-badge-master]:  https://travis-ci.org/lexicalunit/nanodbc.svg?branch=master
[travis-badge-release]: https://travis-ci.org/lexicalunit/nanodbc.svg?branch=release

[appveyor]:         https://ci.appveyor.com/project/lexicalunit/nanodbc?branch=master
[appveyor-badge]:   https://ci.appveyor.com/api/projects/status/71nb7l794n3i8vdj/branch/master?svg=true

[coverity]:         https://scan.coverity.com/projects/lexicalunit-nanodbc
[coverity-badge]:   https://scan.coverity.com/projects/7437/badge.svg
