#
# Copyright (c) 2008-2015 the Urho3D project.
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

# Find Urho3D include directories and libraries in the Urho3D SDK installation or build tree
# This module should be able to find Urho3D automatically when the SDK is installed in a system-wide default location
# If the SDK installation location is non-default or the Urho3D library is not installed at all (i.e. still in its build tree) then
#   use URHO3D_HOME environment variable or build option to specify the location of the non-default SDK installation or build tree
# When setting URHO3D_HOME variable, it should be set to a parent directory containing both the "include" and "lib" subdirectories
#   e.g. set URHO3D_HOME=/home/john/usr/local, if the SDK is installed using DESTDIR=/home/john and CMAKE_INSTALL_PREFIX=/usr/local

#
#  URHO3D_FOUND
#  URHO3D_INCLUDE_DIRS
#  URHO3D_LIBRARIES
#  URHO3D_VERSION
#  URHO3D_LIB_TYPE (use as input variable if specified; or as output variable if it is set based on module's search result)
#
# WIN32 only:
#  URHO3D_LIBRARIES_REL
#  URHO3D_LIBRARIES_DBG
#  URHO3D_DLL
#  URHO3D_DLL_REL
#  URHO3D_DLL_DBG
#

set (PATH_SUFFIX Urho3D)
set (COMPILE_RESULT TRUE)
if (CMAKE_PROJECT_NAME STREQUAL Urho3D AND TARGET Urho3D)
    # A special case where library location is already known to be in the build tree of Urho3D project
    set (URHO3D_HOME ${CMAKE_BINARY_DIR})
    set (URHO3D_INCLUDE_DIRS ${URHO3D_HOME}/include ${URHO3D_HOME}/include/Urho3D/ThirdParty)
    if (URHO3D_PHYSICS)
        # Bullet library depends on its own include dir to be added in the header search path
        # This is more practical than patching its header files in many places to make them work with relative path
        list (APPEND URHO3D_INCLUDE_DIRS ${URHO3D_HOME}/include/Urho3D/ThirdParty/Bullet)
    endif ()
    if (URHO3D_LUA)
        # ditto for Lua/LuaJIT
        list (APPEND URHO3D_INCLUDE_DIRS ${URHO3D_HOME}/include/Urho3D/ThirdParty/Lua${JIT})
    endif ()
    set (URHO3D_LIBRARIES Urho3D)
    set (FOUND_MESSAGE "Found Urho3D: as CMake target")
else ()
    # Library location would be searched (based on URHO3D_HOME variable if provided and in system-wide default location)
    if (NOT URHO3D_HOME AND DEFINED ENV{URHO3D_HOME})
        file (TO_CMAKE_PATH "$ENV{URHO3D_HOME}" URHO3D_HOME)
    endif ()
    # If either of the URHO3D_LIB_TYPE or URHO3D_HOME build options changes then invalidate all the caches
    if ((URHO3D_LIB_TYPE AND NOT URHO3D_LIB_TYPE STREQUAL URHO3D_FOUND_LIB_TYPE) OR NOT URHO3D_BASE_INCLUDE_DIR MATCHES "^${URHO3D_HOME}/include/Urho3D$")
        unset (URHO3D_BASE_INCLUDE_DIR CACHE)
        unset (URHO3D_LIBRARIES CACHE)
        if (WIN32)
            unset (URHO3D_LIBRARIES_DBG CACHE)
            unset (URHO3D_DLL_REL CACHE)
            unset (URHO3D_DLL_DBG CACHE)
        endif ()
        # Urho3D prefers static library type by default while CMake prefers shared one, so we need to change CMake preference to agree with Urho3D
        set (CMAKE_FIND_LIBRARY_SUFFIXES_SAVED ${CMAKE_FIND_LIBRARY_SUFFIXES})
        if (NOT CMAKE_FIND_LIBRARY_SUFFIXES MATCHES ^\\.\(a|lib\))
            list (REVERSE CMAKE_FIND_LIBRARY_SUFFIXES)
        endif ()
        # If library type is specified then only search for the requested library type
        if (NOT MSVC AND URHO3D_LIB_TYPE)      # MSVC static lib and import lib have a same extension, so cannot use it for searches
            if (URHO3D_LIB_TYPE STREQUAL STATIC)
                set (CMAKE_FIND_LIBRARY_SUFFIXES .a)
            elseif (URHO3D_LIB_TYPE STREQUAL SHARED)
                if (MINGW)
                    set (CMAKE_FIND_LIBRARY_SUFFIXES .dll.a)
                elseif (APPLE)
                    set (CMAKE_FIND_LIBRARY_SUFFIXES .dylib)
                else ()
                    set (CMAKE_FIND_LIBRARY_SUFFIXES .so)
                endif ()
            else ()
                message (FATAL_ERROR "Library type: '${URHO3D_LIB_TYPE}' is not supported")
            endif ()
        endif ()
        # Cater for the shared library extension in Emscripten build which is ".bc" instead of ".so"
        if (EMSCRIPTEN)
            string (REPLACE .so .bc CMAKE_FIND_LIBRARY_SUFFIXES "${CMAKE_FIND_LIBRARY_SUFFIXES}")   # Stringify for string replacement
        endif ()
        # The PATH_SUFFIX does not work for CMake on Windows host system, it actually needs a prefix instead
        if (CMAKE_HOST_WIN32)
            set (CMAKE_SYSTEM_PREFIX_PATH_SAVED ${CMAKE_SYSTEM_PREFIX_PATH})
            string (REPLACE ";" "\\Urho3D;" CMAKE_SYSTEM_PREFIX_PATH "${CMAKE_SYSTEM_PREFIX_PATH_SAVED};")    # Stringify for string replacement
            if (NOT URHO3D_64BIT)
                list (REVERSE CMAKE_SYSTEM_PREFIX_PATH)
            endif ()
        endif ()
    endif ()
    # URHO3D_HOME variable should be an absolute path, so use a non-rooted search even when we are cross-compiling
    if (URHO3D_HOME)
        list (APPEND CMAKE_PREFIX_PATH ${URHO3D_HOME})
        set (SEARCH_OPT NO_CMAKE_FIND_ROOT_PATH)
    endif ()
    # For Android platform, search in path similar to ANDROID_LIBRARY_OUTPUT_PATH variable
    if (ANDROID)
        if (URHO3D_HOME)
            set (URHO3D_LIB_SEARCH_HINT HINTS ${URHO3D_HOME}/libs/${ANDROID_NDK_ABI_NAME})
        else ()
            set (URHO3D_LIB_SEARCH_HINT HINTS /usr/local/libs/${ANDROID_NDK_ABI_NAME})
        endif ()
    endif ()
    if (NOT URHO3D_64BIT)
        # For 32-bit, force to search in 'lib' path even when the host system defaulted to use 'lib64'
        set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS FALSE)
    elseif (MINGW AND CMAKE_CROSSCOMPILING)
        # For 64-bit MinGW on Linux host system, force to search in 'lib64' path even when the Windows platform is not defaulted to use it
        set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS TRUE)
    endif ()
    find_path (URHO3D_BASE_INCLUDE_DIR Urho3D.h PATH_SUFFIXES ${PATH_SUFFIX} ${SEARCH_OPT} DOC "Urho3D include directory")
    if (URHO3D_BASE_INCLUDE_DIR)
        get_filename_component (URHO3D_INCLUDE_DIRS ${URHO3D_BASE_INCLUDE_DIR} PATH)
        if (NOT URHO3D_HOME)
            # URHO3D_HOME is not set when using SDK installed on system-wide default location, so set it now
            get_filename_component (URHO3D_HOME ${URHO3D_INCLUDE_DIRS} PATH)
        endif ()
        list (APPEND URHO3D_INCLUDE_DIRS ${URHO3D_BASE_INCLUDE_DIR}/ThirdParty)
        if (URHO3D_PHYSICS)
            list (APPEND URHO3D_INCLUDE_DIRS ${URHO3D_BASE_INCLUDE_DIR}/ThirdParty/Bullet)
        endif ()
        if (URHO3D_LUA)
            list (APPEND URHO3D_INCLUDE_DIRS ${URHO3D_BASE_INCLUDE_DIR}/ThirdParty/Lua${JIT})
        endif ()
        # Intentionally do no cache the URHO3D_VERSION as it has potential to change frequently
        file (STRINGS ${URHO3D_BASE_INCLUDE_DIR}/librevision.h URHO3D_VERSION REGEX "^const char\\* revision=\"[^\"]*\".*$")
        string (REGEX REPLACE "^const char\\* revision=\"([^\"]*)\".*$" \\1 URHO3D_VERSION "${URHO3D_VERSION}")      # Stringify to guard against empty variable
        # The library type is baked into export header only for MSVC as it has no other way to differentiate them, fortunately both types cannot coexist for MSVC anyway unlike other compilers
        if (MSVC)
            file (STRINGS ${URHO3D_BASE_INCLUDE_DIR}/Urho3D.h MSVC_STATIC_LIB REGEX "^#define URHO3D_STATIC_DEFINE$")
        endif ()
    endif ()
    find_library (URHO3D_LIBRARIES NAMES Urho3D ${URHO3D_LIB_SEARCH_HINT} PATH_SUFFIXES ${PATH_SUFFIX} ${SEARCH_OPT} DOC "Urho3D library directory")
    if (WIN32)
        # For Windows platform, give a second chance to search for a debug version of the library
        find_library (URHO3D_LIBRARIES_DBG NAMES Urho3D_d ${URHO3D_LIB_SEARCH_HINT} PATH_SUFFIXES ${PATH_SUFFIX} ${SEARCH_OPT})
        # If both the non-debug and debug version of the libraries are found then use them both
        set (URHO3D_LIBRARIES_REL ${URHO3D_LIBRARIES})
        # Otherwise, URHO3D_LIBRARIES variable should have the path to either one of the version
        if (URHO3D_LIBRARIES)
            if (URHO3D_LIBRARIES_DBG)
                list (APPEND URHO3D_LIBRARIES ${URHO3D_LIBRARIES_DBG})
            endif ()
        else ()
            set (URHO3D_LIBRARIES ${URHO3D_LIBRARIES_DBG})
        endif ()
    endif ()
    # Ensure the module has found the right one if the library type is specified
    if (MSVC)
        if (URHO3D_LIB_TYPE)
            if (NOT ((URHO3D_LIB_TYPE STREQUAL STATIC AND MSVC_STATIC_LIB) OR (URHO3D_LIB_TYPE STREQUAL SHARED AND NOT MSVC_STATIC_LIB)))
                unset (URHO3D_LIB_TYPE)
            endif ()
        else ()
            if (MSVC_STATIC_LIB)
                set (URHO3D_LIB_TYPE STATIC)
            else ()
                set (URHO3D_LIB_TYPE SHARED)
            endif ()
        endif ()
    elseif (URHO3D_LIBRARIES)
        get_filename_component (EXT ${URHO3D_LIBRARIES} EXT)
        if (EXT STREQUAL .a)
            set (URHO3D_LIB_TYPE STATIC)
            # For Non-MSVC compiler the static define is not baked into the export header file so we need to define it for the try_compile below
            set (COMPILER_STATIC_FLAG COMPILE_DEFINITIONS -DURHO3D_STATIC_DEFINE)
        else ()
            set (URHO3D_LIB_TYPE SHARED)
        endif ()
    endif ()
    # Ensure the module has found the library with the right ABI for the chosen compiler and URHO3D_64BIT build option
    if (URHO3D_LIBRARIES AND NOT IOS AND NOT ANDROID)
        if (NOT URHO3D_64BIT AND NOT MSVC AND NOT MINGW AND NOT ANDROID AND NOT RPI AND NOT EMSCRIPTEN)
            set (COMPILER_32BIT_FLAG -DCOMPILE_DEFINITIONS:STRING=-m32)
        endif ()
        # BCM_VC_LIBRARIES variable is only populated when targeting RPI and empty otherwise, so it is safe to always append the variable
        try_compile (COMPILE_RESULT ${CMAKE_BINARY_DIR}/generated/FindUrho3D ${CMAKE_CURRENT_LIST_DIR}/CheckUrho3DLibrary.cpp
            CMAKE_FLAGS -DLINK_LIBRARIES:STRING=${URHO3D_LIBRARIES}\;${BCM_VC_LIBRARIES} -DINCLUDE_DIRECTORIES:STRING=${URHO3D_INCLUDE_DIRS} ${COMPILER_32BIT_FLAG} ${COMPILER_STATIC_FLAG}
            OUTPUT_VARIABLE TRY_COMPILE_OUT)
    endif ()
    # For shared library type, also initialize the URHO3D_DLL variable for later use
    if (WIN32)
        if (URHO3D_LIB_TYPE STREQUAL SHARED AND URHO3D_HOME)
            find_file (URHO3D_DLL_REL Urho3D.dll HINTS ${URHO3D_HOME}/bin NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH DOC "Urho3D release DLL")
            if (URHO3D_DLL_REL)
                list (APPEND URHO3D_DLL ${URHO3D_DLL_REL})
            endif ()
            find_file (URHO3D_DLL_DBG Urho3D_d.dll HINTS ${URHO3D_HOME}/bin NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH DOC "Urho3D debug DLL")
            if (URHO3D_DLL_DBG)
                list (APPEND URHO3D_DLL ${URHO3D_DLL_DBG})
            endif ()
        endif ()
    endif ()
    # Restore CMake global settings
    if (CMAKE_FIND_LIBRARY_SUFFIXES_SAVED)
        set (CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES_SAVED})
    endif ()
    if (CMAKE_SYSTEM_PREFIX_PATH_SAVED)
        set (CMAKE_SYSTEM_PREFIX_PATH ${CMAKE_SYSTEM_PREFIX_PATH_SAVED})
    endif ()
endif ()

if (URHO3D_INCLUDE_DIRS AND URHO3D_LIBRARIES AND URHO3D_LIB_TYPE AND COMPILE_RESULT)
    set (URHO3D_FOUND 1)
    if (NOT FOUND_MESSAGE)
        set (FOUND_MESSAGE "Found Urho3D: ${URHO3D_LIBRARIES}")
        if (URHO3D_VERSION)
            set (FOUND_MESSAGE "${FOUND_MESSAGE} (found version \"${URHO3D_VERSION}\")")
        endif ()
    endif ()
    include (FindPackageMessage)
    find_package_message (Urho3D ${FOUND_MESSAGE} "[${URHO3D_LIBRARIES}][${URHO3D_INCLUDE_DIRS}]")
    set (URHO3D_HOME ${URHO3D_HOME} CACHE PATH "Path to Urho3D build tree or SDK installation location" FORCE)
    set (URHO3D_FOUND_LIB_TYPE ${URHO3D_LIB_TYPE} CACHE INTERNAL "Lib type (if specified) when Urho3D library was last found")
elseif (Urho3D_FIND_REQUIRED)
    if (ANDROID)
        set (NOT_FOUND_MESSAGE "For Android platform, double check if you have specified to use the same ANDROID_ABI as the Urho3D library in the build tree or SDK.")
    endif ()
    if (URHO3D_LIB_TYPE)
        set (NOT_FOUND_MESSAGE "Ensure the specified location contains the Urho3D library of the requested library type. ${NOT_FOUND_MESSAGE}")
    endif ()
    message (FATAL_ERROR
        "Could NOT find compatible Urho3D library in Urho3D SDK installation or build tree. "
        "Use URHO3D_HOME environment variable or build option to specify the location of the non-default SDK installation or build tree. ${NOT_FOUND_MESSAGE} ${TRY_COMPILE_OUT}")
endif ()

mark_as_advanced (URHO3D_BASE_INCLUDE_DIR URHO3D_LIBRARIES URHO3D_LIBRARIES_DBG URHO3D_DLL_REL URHO3D_DLL_DBG URHO3D_HOME)
