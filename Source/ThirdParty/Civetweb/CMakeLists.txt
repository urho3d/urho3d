#
# Copyright (c) 2008-2020 the Urho3D project.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

# Define target name
set (TARGET_NAME Civetweb)

# Define preprocessor macros
# Always disable Common Gateway Interface
add_definitions(-DNO_CGI -DNO_FILES -DNO_CACHING)

# Allow debug output to console
# add_definitions(-DDEBUG)

if (WIN32)
    include (CheckStructHasMember)
    check_struct_has_member (struct\ timespec tv_sec time.h HAVE_STRUCT_TIMESPEC_TV_SEC)
    if (HAVE_STRUCT_TIMESPEC_TV_SEC)
        include (CheckSymbolExists)
        check_symbol_exists (_TIMESPEC_DEFINED time.h HAVE__TIMESPEC_DEFINED)
        if (NOT HAVE__TIMESPEC_DEFINED)
            add_definitions (-D_TIMESPEC_DEFINED)
        endif ()
    endif ()
elseif (APPLE AND (NOT IOS OR IPHONEOS_DEPLOYMENT_TARGET STREQUAL "" OR NOT IPHONEOS_DEPLOYMENT_TARGET VERSION_LESS 10.0))    # We cheat a little bit here with a hard-coded check because iOS 10.3 SDK when targeting 9.3 has strong symbol for iPhoneOS archs but weak symbol for iPhoneSimulator archs
    include (CheckLibraryExists)
    check_library_exists (c clock_gettime "" FOUND_CLOCK_GETTIME_IN_C)
    if (FOUND_CLOCK_GETTIME_IN_C)
        add_definitions (-DHAVE_CLOCK_GETTIME)
    endif ()
endif ()

if (NOT URHO3D_SSL)
    add_definitions(-DNO_SSL)
elseif (NOT URHO3D_SSL_DYNAMIC)
    add_definitions(-DNO_SSL_DL)
endif ()

# Define source files
define_source_files (GLOB_CPP_PATTERNS src/*.c GLOB_H_PATTERNS include/*.h)

# Define include directory
set (INCLUDE_DIRS include)

# Setup target
setup_library ()

# Link OpenSSL libraries
if (URHO3D_SSL)
    if (URHO3D_SSL_DYNAMIC)
        # Unix systems can define the dynamic library names to load
        if (UNIX AND NOT DARWIN)
            add_definitions(-DCRYPTO_LIB="libcrypto.so")
            add_definitions(-DSSL_LIB="libssl.so")
        endif ()
        find_library(LIBDL_LIBRARIES dl)
        include(FindPackageHandleStandardArgs)
        find_package_handle_standard_args(LibDl DEFAULT_MSG LIBDL_LIBRARIES LIBDL_INCLUDE_DIRS)
        mark_as_advanced(LIBDL_INCLUDE_DIRS LIBDL_LIBRARIES)
        find_path(LIBDL_INCLUDE_DIRS
            NAMES dlfcn.h
            PATHS ${LIBDL_ROOT}/include/
        )
        if (LIBDL_FOUND)
            if (NOT TARGET LIBDL::LIBDL)
                add_library(LIBDL::LIBDL UNKNOWN IMPORTED)
                set_target_properties(LIBDL::LIBDL PROPERTIES
                    IMPORTED_LOCATION "${LIBDL_LIBRARIES}"
                    INTERFACE_INCLUDE_DIRECTORIES "${LIBDL_INCLUDE_DIRS}"
                )
            endif ()
        endif ()
        if (LIBDL_FOUND)
            target_link_libraries(Civetweb -ldl)
        endif ()
    else ()
        if (APPLE)
            set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
        endif ()
        find_package(OpenSSL REQUIRED)
        include_directories(${OPENSSL_INCLUDE_DIR})
        message(STATUS "OpenSSL include directory: ${OPENSSL_INCLUDE_DIR}")
        add_definitions(-DOPENSSL_API_1_1)
    endif ()
endif ()

# Install headers for building the Urho3D library
install_header_files (DIRECTORY include/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/Civetweb FILES_MATCHING PATTERN *.h BUILD_TREE_ONLY)  # Note: the trailing slash is significant
