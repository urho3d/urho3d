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

# Find Urho3D include directories and libraries in the Urho3D SDK installation or build tree or in Android library
# This module should be able to find Urho3D automatically when the SDK is installed in a system-wide default location or
# when the Urho3D Android library has been correctly declared as project dependency
# If the SDK installation location is non-default or the Urho3D library is not installed at all (i.e. still in its build tree) then
#   use URHO3D_HOME environment variable or build option to specify the location of the non-default SDK installation or build tree
# When setting URHO3D_HOME variable, it should be set to a parent directory containing both the "include" and "lib" subdirectories
#   e.g. set URHO3D_HOME=/home/john/usr/local, if the SDK is installed using DESTDIR=/home/john and CMAKE_INSTALL_PREFIX=/usr/local

#
#  URHO3D_FOUND
#  URHO3D_INCLUDE_DIRS
#  URHO3D_LIBRARIES
#  URHO3D_VERSION
#  URHO3D_64BIT (may be used as input variable for multilib-capable compilers; must always be specified as input variable for MSVC due to CMake/VS generator limitation)
#  URHO3D_LIB_TYPE (may be used as input variable as well to limit the search of library type)
#  URHO3D_OPENGL
#  URHO3D_SSE
#  URHO3D_DATABASE_ODBC
#  URHO3D_DATABASE_SQLITE
#  URHO3D_LUAJIT
#  URHO3D_TESTING
#
# WIN32 only:
#  URHO3D_LIBRARIES_REL
#  URHO3D_LIBRARIES_DBG
#  URHO3D_DLL
#  URHO3D_DLL_REL
#  URHO3D_DLL_DBG
#  URHO3D_D3D11
#
# MSVC only:
#  URHO3D_STATIC_RUNTIME
#

set (AUTO_DISCOVER_VARS URHO3D_OPENGL URHO3D_D3D11 URHO3D_SSE URHO3D_DATABASE_ODBC URHO3D_DATABASE_SQLITE URHO3D_LUAJIT URHO3D_TESTING URHO3D_STATIC_RUNTIME)
set (PATH_SUFFIX Urho3D)
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
    set (URHO3D_COMPILE_RESULT TRUE)
else ()
    if (ANDROID AND GRADLE_BUILD_DIR)
        # Urho3D AAR is a universal library
        set (URHO3D_HOME ${GRADLE_BUILD_DIR}/tree/${CMAKE_BUILD_TYPE}/${ANDROID_ABI})
    elseif (NOT URHO3D_HOME AND DEFINED ENV{URHO3D_HOME})
        # Library location would be searched (based on URHO3D_HOME variable if provided and in system-wide default location)
        file (TO_CMAKE_PATH "$ENV{URHO3D_HOME}" URHO3D_HOME)
    endif ()
    # Convert to integer literal to match it with our internal cache representation; it also will be used as foreach loop control variable
    if (URHO3D_64BIT)
        set (URHO3D_64BIT 1)
    else ()
        set (URHO3D_64BIT 0)
    endif ()
    # If either of the URHO3D_64BIT or URHO3D_LIB_TYPE or URHO3D_HOME build options changes then invalidate all the caches
    if (NOT URHO3D_64BIT EQUAL URHO3D_FOUND_64BIT OR NOT URHO3D_LIB_TYPE STREQUAL URHO3D_FOUND_LIB_TYPE OR NOT URHO3D_BASE_INCLUDE_DIR MATCHES "^${URHO3D_HOME}/include/Urho3D$")
        unset (URHO3D_BASE_INCLUDE_DIR CACHE)
        unset (URHO3D_LIBRARIES CACHE)
        unset (URHO3D_FOUND_64BIT CACHE)
        unset (URHO3D_FOUND_LIB_TYPE CACHE)
        unset (URHO3D_COMPILE_RESULT CACHE)
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
        # Intentionally do not cache the URHO3D_VERSION as it has potential to change frequently
        file (STRINGS ${URHO3D_BASE_INCLUDE_DIR}/librevision.h URHO3D_VERSION REGEX "^const char\\* revision=\"[^\"]*\".*$")
        string (REGEX REPLACE "^const char\\* revision=\"([^\"]*)\".*$" \\1 URHO3D_VERSION "${URHO3D_VERSION}")      # Stringify to guard against empty variable
        # The library type is baked into export header only for MSVC as it has no other way to differentiate them, fortunately both types cannot coexist for MSVC anyway unlike other compilers
        if (MSVC)
            file (STRINGS ${URHO3D_BASE_INCLUDE_DIR}/Urho3D.h MSVC_STATIC_LIB REGEX "^#define URHO3D_STATIC_DEFINE$")
        endif ()
    endif ()
    if (URHO3D_64BIT AND MINGW AND CMAKE_CROSSCOMPILING)
        # For 64-bit MinGW on Linux host system, force to search in 'lib64' path even when the Windows platform is not defaulted to use it
        set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS TRUE)
    endif ()
    set (URHO3D_LIB_TYPE_SAVED ${URHO3D_LIB_TYPE})  # We need this to reset the auto-discovered URHO3D_LIB_TYPE variable before looping
    foreach (ABI_64BIT RANGE ${URHO3D_64BIT} 0)
        # Set to search in 'lib' or 'lib64' based on the ABI being tested
        set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ${ABI_64BIT})    # Leave this global property setting afterwards, do not restore it to its previous value
        find_library (URHO3D_LIBRARIES NAMES Urho3D PATH_SUFFIXES ${PATH_SUFFIX} ${SEARCH_OPT} DOC "Urho3D library directory")
        if (WIN32)
            # For Windows platform, give a second chance to search for a debug version of the library
            find_library (URHO3D_LIBRARIES_DBG NAMES Urho3D_d PATH_SUFFIXES ${PATH_SUFFIX} ${SEARCH_OPT})
            set (URHO3D_LIBRARIES_REL ${URHO3D_LIBRARIES})
            if (NOT URHO3D_LIBRARIES)
                set (URHO3D_LIBRARIES ${URHO3D_LIBRARIES_DBG})
            endif ()
        endif ()
        # Ensure the module has found the right one if the library type is specified
        if (MSVC)
            if (URHO3D_LIB_TYPE)
                if (NOT ((URHO3D_LIB_TYPE STREQUAL STATIC AND MSVC_STATIC_LIB) OR (URHO3D_LIB_TYPE STREQUAL SHARED AND NOT MSVC_STATIC_LIB)))
                    unset (URHO3D_LIBRARIES)    # Not a right type, so nullify the search result
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
                set (COMPILER_STATIC_DEFINE COMPILE_DEFINITIONS -DURHO3D_STATIC_DEFINE)
            else ()
                set (URHO3D_LIB_TYPE SHARED)
                unset (COMPILER_STATIC_DEFINE)
            endif ()
        endif ()
        # For shared library type, also initialize the URHO3D_DLL variable for later use
        if (WIN32 AND URHO3D_LIB_TYPE STREQUAL SHARED AND URHO3D_HOME)
            find_file (URHO3D_DLL_REL Urho3D.dll HINTS ${URHO3D_HOME}/bin NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH DOC "Urho3D release DLL")
            if (URHO3D_DLL_REL)
                list (APPEND URHO3D_DLL ${URHO3D_DLL_REL})
            endif ()
            find_file (URHO3D_DLL_DBG Urho3D_d.dll HINTS ${URHO3D_HOME}/bin NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH DOC "Urho3D debug DLL")
            if (URHO3D_DLL_DBG)
                list (APPEND URHO3D_DLL ${URHO3D_DLL_DBG})
            endif ()
        endif ()
        # Ensure the module has found the library with the right ABI for the chosen compiler and URHO3D_64BIT build option (if specified)
        if (URHO3D_COMPILE_RESULT)
            break ()    # Use the cached result instead of redoing try_compile() each time
        elseif (URHO3D_LIBRARIES)
            if (NOT (MSVC OR ANDROID OR ARM OR WEB OR XCODE) AND NOT ABI_64BIT)
                set (COMPILER_32BIT_FLAG -m32)
            endif ()
            # Below variables are loop invariant but there is no harm to keep them here
            if (WIN32)
                set (CMAKE_TRY_COMPILE_CONFIGURATION_SAVED ${CMAKE_TRY_COMPILE_CONFIGURATION})
                if (URHO3D_LIBRARIES_REL)
                    set (CMAKE_TRY_COMPILE_CONFIGURATION Release)
                else ()
                    set (CMAKE_TRY_COMPILE_CONFIGURATION Debug)
                endif ()
            elseif (APPLE AND ARM)
                # Debug build does not produce universal binary library, so we could not test compile against the library
                execute_process (COMMAND lipo -info ${URHO3D_LIBRARIES} COMMAND grep -cq arm RESULT_VARIABLE SKIP_COMPILE_TEST OUTPUT_QUIET ERROR_QUIET)
            endif ()
            set (COMPILER_FLAGS "${COMPILER_32BIT_FLAG} ${CMAKE_REQUIRED_FLAGS}")
            if (SKIP_COMPILE_TEST
                OR CMAKE_PROJECT_NAME STREQUAL Urho3D-Launcher)     # Workaround initial IDE "gradle sync" error due to library has not been built yet
                set (URHO3D_COMPILE_RESULT 1)
            else ()
                while (NOT URHO3D_COMPILE_RESULT)
                    try_compile (URHO3D_COMPILE_RESULT ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_LIST_DIR}/CheckUrhoLibrary.cpp
                        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${COMPILER_FLAGS} -DLINK_LIBRARIES:STRING=${URHO3D_LIBRARIES} -DINCLUDE_DIRECTORIES:STRING=${URHO3D_INCLUDE_DIRS} ${COMPILER_STATIC_DEFINE} ${COMPILER_STATIC_RUNTIME_FLAGS}
                        OUTPUT_VARIABLE TRY_COMPILE_OUT)
                    if (MSVC AND NOT URHO3D_COMPILE_RESULT AND NOT COMPILER_STATIC_RUNTIME_FLAGS)
                        # Give a second chance for MSVC to use static runtime flag
                        if (URHO3D_LIBRARIES_REL)
                            set (COMPILER_STATIC_RUNTIME_FLAGS COMPILE_DEFINITIONS /MT)
                        else ()
                            set (COMPILER_STATIC_RUNTIME_FLAGS COMPILE_DEFINITIONS /MTd)
                        endif ()
                    else ()
                        break ()    # Other compilers break immediately rendering the while-loop a no-ops
                    endif ()
                endwhile ()
            endif ()
            set (URHO3D_COMPILE_RESULT ${URHO3D_COMPILE_RESULT} CACHE INTERNAL "FindUrho3D module's compile result")
            if (URHO3D_COMPILE_RESULT)
                # Auto-discover build options used by the found library and export header
                file (READ ${URHO3D_BASE_INCLUDE_DIR}/Urho3D.h EXPORT_HEADER)
                if (APPLE AND ARM)
                    # Since Urho3D library for Apple/ARM platforms is a universal binary (except when it was a Debug build), we need another way to find out the compiler ABI the library was built for
                    execute_process (COMMAND lipo -info ${URHO3D_LIBRARIES} COMMAND grep -c x86_64 OUTPUT_VARIABLE ABI_64BIT ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
                elseif (MSVC)
                    if (COMPILER_STATIC_RUNTIME_FLAGS)
                        set (EXPORT_HEADER "${EXPORT_HEADER}#define URHO3D_STATIC_RUNTIME\n")
                    endif ()
                endif ()
                set (URHO3D_64BIT ${ABI_64BIT} CACHE BOOL "Enable 64-bit build, the value is auto-discovered based on the found Urho3D library" FORCE) # Force it as it is more authoritative than user-specified option
                set (URHO3D_LIB_TYPE ${URHO3D_LIB_TYPE} CACHE STRING "Urho3D library type, the value is auto-discovered based on the found Urho3D library" FORCE) # Use the Force, Luke
                foreach (VAR ${AUTO_DISCOVER_VARS})
                    if (EXPORT_HEADER MATCHES "#define ${VAR}")
                        set (AUTO_DISCOVERED_${VAR} 1)
                    else ()
                        set (AUTO_DISCOVERED_${VAR} 0)
                    endif ()
                    set (AUTO_DISCOVERED_${VAR} ${AUTO_DISCOVERED_${VAR}} CACHE INTERNAL "Auto-discovered ${VAR} build option")
                endforeach ()
                break ()
            else ()
                # Prepare for the second attempt by resetting the variables as necessary
                set (URHO3D_LIB_TYPE ${URHO3D_LIB_TYPE_SAVED})
                unset (URHO3D_LIBRARIES CACHE)
            endif ()
        endif ()
        # Break if the compiler is not multilib-capable
        if (MSVC OR ANDROID OR ARM OR WEB)
            break ()
        endif ()
    endforeach ()
    # If both the non-debug and debug version of the libraries are found on Windows platform then use them both
    if (URHO3D_LIBRARIES_REL AND URHO3D_LIBRARIES_DBG)
        set (URHO3D_LIBRARIES ${URHO3D_LIBRARIES_REL} ${URHO3D_LIBRARIES_DBG})
    endif ()
    # Ensure auto-discovered variables always prevail over user settings in all the subsequent cmake rerun (even without redoing try_compile)
    foreach (VAR ${AUTO_DISCOVER_VARS})
        if (DEFINED ${VAR} AND DEFINED AUTO_DISCOVERED_${VAR})  # Cannot combine these two ifs due to variable expansion error when it is not defined
            if ((${VAR} AND NOT ${AUTO_DISCOVERED_${VAR}}) OR (NOT ${VAR} AND ${AUTO_DISCOVERED_${VAR}}))
                message (WARNING "Conflicting ${VAR} build option is ignored.")
                unset (${VAR} CACHE)
            endif ()
        endif ()
        set (${VAR} ${AUTO_DISCOVERED_${VAR}})
    endforeach ()
    # Restore CMake global settings
    if (CMAKE_FIND_LIBRARY_SUFFIXES_SAVED)
        set (CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES_SAVED})
    endif ()
    if (CMAKE_SYSTEM_PREFIX_PATH_SAVED)
        set (CMAKE_SYSTEM_PREFIX_PATH ${CMAKE_SYSTEM_PREFIX_PATH_SAVED})
    endif ()
    if (CMAKE_TRY_COMPILE_CONFIGURATION_SAVED)
        set (CMAKE_TRY_COMPILE_CONFIGURATION ${CMAKE_TRY_COMPILE_CONFIGURATION_SAVED})
    endif ()
endif ()

if (URHO3D_INCLUDE_DIRS AND URHO3D_LIBRARIES AND URHO3D_LIB_TYPE AND URHO3D_COMPILE_RESULT)
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
    set (URHO3D_FOUND_64BIT ${URHO3D_64BIT} CACHE INTERNAL "True when 64-bit ABI was being used when test compiling Urho3D library")
    set (URHO3D_FOUND_LIB_TYPE ${URHO3D_LIB_TYPE} CACHE INTERNAL "Lib type (if specified) when Urho3D library was last found")
elseif (Urho3D_FIND_REQUIRED)
    if (ANDROID)
        set (NOT_FOUND_MESSAGE "For Android platform, double check if you have specified to use the same ANDROID_ABI as the Urho3D Android Library, especially when you are not using universal AAR.")
    endif ()
    if (URHO3D_LIB_TYPE)
        set (NOT_FOUND_MESSAGE "Ensure the specified location contains the Urho3D library of the requested library type. ${NOT_FOUND_MESSAGE}")
    endif ()
    message (FATAL_ERROR
        "Could NOT find compatible Urho3D library in Urho3D SDK installation or build tree or in Android library. "
        "Use URHO3D_HOME environment variable or build option to specify the location of the non-default SDK installation or build tree. ${NOT_FOUND_MESSAGE} ${TRY_COMPILE_OUT}")
endif ()

mark_as_advanced (URHO3D_BASE_INCLUDE_DIR URHO3D_LIBRARIES URHO3D_LIBRARIES_DBG URHO3D_DLL_REL URHO3D_DLL_DBG)
