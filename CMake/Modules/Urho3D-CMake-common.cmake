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

# Limit the supported build configurations
set (URHO3D_BUILD_CONFIGURATIONS Release RelWithDebInfo Debug)
set (DOC_STRING "Specify CMake build configuration (single-configuration generator only), possible values are Release (default), RelWithDebInfo, and Debug")
if (CMAKE_CONFIGURATION_TYPES)
    # For multi-configurations generator, such as VS and Xcode
    set (CMAKE_CONFIGURATION_TYPES ${URHO3D_BUILD_CONFIGURATIONS} CACHE STRING "${DOC_STRING}" FORCE)
    unset (CMAKE_BUILD_TYPE)
else ()
    # For single-configuration generator, such as Unix Makefile generator
    if (CMAKE_BUILD_TYPE STREQUAL "")
        # If not specified then default to Release
        set (CMAKE_BUILD_TYPE Release)
    endif ()
    set (CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "${DOC_STRING}" FORCE)
endif ()

# Define other useful variables not defined by CMake
if (CMAKE_GENERATOR STREQUAL Xcode)
    set (XCODE TRUE)
endif ()

# Define all supported build options
include (CMakeDependentOption)
option (URHO3D_C++11 "Enable C++11 standard")
mark_as_advanced (URHO3D_C++11)
cmake_dependent_option (IOS "Setup build for iOS platform" FALSE "XCODE" FALSE)
if (NOT DEFINED URHO3D_DEFAULT_64BIT)  # Only do this once in the initial configure step
    if (MSVC)
        # On MSVC compiler, use the chosen CMake/VS generator to determine the ABI
        if (CMAKE_GENERATOR MATCHES Win64)
            set (URHO3D_DEFAULT_64BIT TRUE)
        else ()
            set (URHO3D_DEFAULT_64BIT FALSE)
        endif ()
    else ()
        # On non-MSVC compiler, default to build 64-bit when the chosen compiler toolchain in the build tree has a 64-bit build environment
        execute_process (COMMAND ${CMAKE_COMMAND} -E echo COMMAND ${CMAKE_C_COMPILER} -E -dM - OUTPUT_VARIABLE PREDEFINED_MACROS ERROR_QUIET)
        string (REGEX MATCH "#define +__(x86_64|aarch64)__ +1" matched "${PREDEFINED_MACROS}")
        if (matched)
            set (URHO3D_DEFAULT_64BIT TRUE)
        else ()
            set (URHO3D_DEFAULT_64BIT FALSE)
        endif ()
        # The 'ANDROID' CMake variable is already set by android.toolchain.cmake when it is being used for cross-compiling Android
        # When ANDROID is true and ARM is not then we are targeting Android on Intel Atom
        string (REGEX MATCH "#define +__(arm|aarch64)__ +1" matched "${PREDEFINED_MACROS}")
        if (matched OR IOS)     # Assume iOS is always on ARM for now
            set (ARM TRUE)
        else ()
            set (ARM FALSE)
        endif ()
        set (ARM ${ARM} CACHE INTERNAL "Targeting ARM platform")
        # The other arm platform that Urho3D supports that is not Android/iOS is Raspberry Pi at the moment
        if (ARM AND NOT ANDROID AND NOT IOS)
            # Set the CMake variable here instead of in raspberrypi.toolchain.cmake because Raspberry Pi can be built natively too on the Raspberry-Pi device itself
            set (RPI TRUE CACHE INTERNAL "Setup build for Raspberry Pi platform")
        endif ()
    endif ()
    set (URHO3D_DEFAULT_64BIT ${URHO3D_DEFAULT_64BIT} CACHE INTERNAL "Default value for URHO3D_64BIT build option")
endif ()
cmake_dependent_option (URHO3D_64BIT "Enable 64-bit build, the default is set based on the native ABI of the chosen compiler toolchain" ${URHO3D_DEFAULT_64BIT} "NOT MSVC AND NOT MINGW AND NOT ANDROID AND NOT RPI AND NOT EMSCRIPTEN" ${URHO3D_DEFAULT_64BIT})
cmake_dependent_option (URHO3D_ANGELSCRIPT "Enable AngelScript scripting support" TRUE "NOT EMSCRIPTEN" FALSE)
option (URHO3D_LUA "Enable additional Lua scripting support" TRUE)
cmake_dependent_option (URHO3D_LUAJIT "Enable Lua scripting support using LuaJIT (check LuaJIT's CMakeLists.txt for more options)" FALSE "NOT EMSCRIPTEN" FALSE)
option (URHO3D_NAVIGATION "Enable navigation support" TRUE)
cmake_dependent_option (URHO3D_NETWORK "Enable networking support" TRUE "NOT EMSCRIPTEN" FALSE)
cmake_dependent_option (URHO3D_DATABASE_ODBC "Enable Database support with ODBC, requires vendor-specific ODBC driver" FALSE "NOT IOS AND NOT ANDROID AND NOT EMSCRIPTEN" FALSE)
option (URHO3D_PHYSICS "Enable physics support" TRUE)
option (URHO3D_URHO2D "Enable 2D graphics and physics support" TRUE)
if (NOT DEFINED URHO3D_DEFAULT_SSE)
    # Set the default to true for all the platforms that support SSE except the following
    set (URHO3D_DEFAULT_SSE TRUE)
    if (MINGW)
        # Certain MinGW versions fail to compile SSE code. This is the initial guess for known "bad" version range, and can be tightened later
        execute_process (COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION ERROR_QUIET)
        if (GCC_VERSION VERSION_LESS 4.9.1)
            message (WARNING "Disabling SSE by default due to MinGW version. It is recommended to upgrade to MinGW with GCC >= 4.9.1. You can also try to re-enable SSE with CMake option -DURHO3D_SSE=1, but this may result in compile errors.")
            set (URHO3D_DEFAULT_SSE FALSE)
        endif ()
    elseif (EMSCRIPTEN)
        # In Emscripten, default to false for targeting SSE2, since the SIMD.js specification is not yet widely adopted in browsers
        set (URHO3D_DEFAULT_SSE FALSE)
    endif ()
    set (URHO3D_DEFAULT_SSE ${URHO3D_DEFAULT_SSE} CACHE INTERNAL "Default value for URHO3D_SSE build option")
endif ()
cmake_dependent_option (URHO3D_SSE "Enable SSE2 instruction set (HTML5 and Intel platforms only including Android on Intel Atom); default to true on Intel and false on HTML5; the effective SSE level could be higher, see also URHO3D_DEPLOYMENT_TARGET and CMAKE_OSX_DEPLOYMENT_TARGET build options" ${URHO3D_DEFAULT_SSE} "NOT ARM" FALSE)
if (IOS OR (RPI AND "${RPI_ABI}" MATCHES NEON))    # Stringify in case RPI_ABI is not set explicitly
    # The 'NEON' CMake variable is already set by android.toolchain.cmake when the chosen ANDROID_ABI uses NEON
    set (NEON TRUE)
endif ()
cmake_dependent_option (URHO3D_NEON "Enable NEON instruction set (ARM platforms with NEON only)" TRUE "NEON" FALSE)
# The URHO3D_OPENGL option is not defined on non-Windows platforms as they should always use OpenGL
if (MSVC)
    # On MSVC compiler, default to false (i.e. prefers Direct3D)
    # OpenGL can be manually enabled with -DURHO3D_OPENGL=1, but Windows graphics card drivers are usually better optimized for Direct3D
    set (DEFAULT_OPENGL FALSE)
else ()
    # On non-MSVC compiler on Windows platform, default to true to enable use of OpenGL instead of Direct3D
    # Direct3D can be manually enabled with -DURHO3D_OPENGL=0, but it is likely to fail unless the MinGW-w64 distribution is used due to dependency to Direct3D headers and libs
    set (DEFAULT_OPENGL TRUE)
endif ()
cmake_dependent_option (URHO3D_OPENGL "Use OpenGL instead of Direct3D (Windows platform only)" ${DEFAULT_OPENGL} "WIN32" TRUE)      # Force the variable to TRUE when not WIN32
# On Windows platform Direct3D11 can be optionally chosen
# Using Direct3D11 on non-MSVC compiler may require copying and renaming Microsoft official libraries (.lib to .a), else link failures or non-functioning graphics may result
cmake_dependent_option (URHO3D_D3D11 "Use Direct3D11 instead of Direct3D9 (Windows platform only); overrides URHO3D_OPENGL option" FALSE "WIN32" FALSE)
if (CMAKE_HOST_WIN32)
    if (NOT DEFINED URHO3D_MKLINK)
        # Test whether the host system is capable of setting up symbolic link
        execute_process (COMMAND cmd /C mklink test-link CMakeCache.txt RESULT_VARIABLE MKLINK_EXIT_CODE OUTPUT_QUIET ERROR_QUIET)
        if (MKLINK_EXIT_CODE EQUAL 0)
            set (URHO3D_MKLINK TRUE)
            file (REMOVE ${CMAKE_BINARY_DIR}/test-link)
        else ()
            set (URHO3D_MKLINK FALSE)
            message (WARNING "Could not use MKLINK to setup symbolic links as this Windows user account does not have the privilege to do so. "
                "When MKLINK is not available then the build system will fallback to use file/directory copy of the library headers from source tree to build tree. "
                "In order to prevent stale headers being used in the build, this file/directory copy will be redone also as a post-build step for each library targets. "
                "This may slow down the build unnecessarily or even cause other unforseen issues due to incomplete or stale headers in the build tree. "
                "Request your Windows Administrator to grant your user account to have privilege to create symlink via MKLINK command. "
                "You are NOT advised to use the Administrator account directly to generate build tree in all cases.")
        endif ()
        set (URHO3D_MKLINK ${URHO3D_MKLINK} CACHE INTERNAL "MKLINK capability on the Windows host system")
    endif ()
    set (NULL_DEVICE nul)
else ()
    set (NULL_DEVICE /dev/null)
endif ()
# Find Direct3D include & library directories in MS Windows SDK or DirectX SDK when not using OpenGL.
if (WIN32 AND NOT URHO3D_OPENGL)
    find_package (Direct3D REQUIRED)
    if (DIRECT3D_INCLUDE_DIRS)
        include_directories (${DIRECT3D_INCLUDE_DIRS})
    endif ()
endif ()
# For Raspbery Pi, find Broadcom VideoCore IV firmware
if (RPI)
    find_package (BCM_VC REQUIRED)
    include_directories (${BCM_VC_INCLUDE_DIRS})
endif ()
if (CMAKE_PROJECT_NAME STREQUAL Urho3D)
    set (URHO3D_LIB_TYPE STATIC CACHE STRING "Specify Urho3D library type, possible values are STATIC (default) and SHARED")
    cmake_dependent_option (URHO3D_LUAJIT_AMALG "Enable LuaJIT amalgamated build (LuaJIT only)" FALSE "URHO3D_LUAJIT" FALSE)
    cmake_dependent_option (URHO3D_SAFE_LUA "Enable Lua C++ wrapper safety checks (Lua/LuaJIT only)" FALSE "URHO3D_LUA OR URHO3D_LUAJIT" FALSE)
    if (CMAKE_BUILD_TYPE STREQUAL Release OR CMAKE_CONFIGURATION_TYPES)
        set (URHO3D_DEFAULT_LUA_RAW FALSE)
    else ()
        set (URHO3D_DEFAULT_LUA_RAW TRUE)
    endif ()
    cmake_dependent_option (URHO3D_LUA_RAW_SCRIPT_LOADER "Prefer loading raw script files from the file system before falling back on Urho3D resource cache. Useful for debugging (e.g. breakpoints), but less performant (Lua/LuaJIT only)" ${URHO3D_DEFAULT_LUA_RAW} "URHO3D_LUA OR URHO3D_LUAJIT" FALSE)
    option (URHO3D_SAMPLES "Build sample applications" TRUE)
    option (URHO3D_UPDATE_SOURCE_TREE "Enable commands to copy back some of the generated build artifacts from build tree to source tree to facilitate devs to push them as part of a commit (for library devs with push right only)")
    option (URHO3D_BINDINGS "Enable API binding generation support for script subystems")
    cmake_dependent_option (URHO3D_CLANG_TOOLS "Build Clang tools (native only)" FALSE "NOT RPI AND NOT IOS AND NOT ANDROID AND NOT EMSCRIPTEN" FALSE)
    mark_as_advanced (URHO3D_UPDATE_SOURCE_TREE URHO3D_BINDINGS URHO3D_CLANG_TOOLS)
    cmake_dependent_option (URHO3D_TOOLS "Build tools (native and RPI only)" TRUE "NOT IOS AND NOT ANDROID AND NOT EMSCRIPTEN" FALSE)
    cmake_dependent_option (URHO3D_EXTRAS "Build extras (native and RPI only)" FALSE "NOT IOS AND NOT ANDROID AND NOT EMSCRIPTEN" FALSE)
    option (URHO3D_DOCS "Generate documentation as part of normal build")
    option (URHO3D_DOCS_QUIET "Generate documentation as part of normal build, suppress generation process from sending anything to stdout")
    option (URHO3D_PCH "Enable PCH support" TRUE)
    option (URHO3D_DATABASE_SQLITE "Enable Database support with SQLite embedded")
    cmake_dependent_option (URHO3D_MINIDUMPS "Enable minidumps on crash (VS only)" TRUE "MSVC" FALSE)
    option (URHO3D_FILEWATCHER "Enable filewatcher support" TRUE)
    if (CPACK_SYSTEM_NAME STREQUAL Linux)
        cmake_dependent_option (URHO3D_USE_LIB64_RPM "Enable 64-bit RPM CPack generator using /usr/lib64 and disable all other generators (Debian-based host only)" FALSE "URHO3D_64BIT AND NOT HAS_LIB64" FALSE)
        cmake_dependent_option (URHO3D_USE_LIB_DEB "Enable 64-bit DEB CPack generator using /usr/lib and disable all other generators (Redhat-based host only)" FALSE "URHO3D_64BIT AND HAS_LIB64" FALSE)
    endif ()
else ()
    set (URHO3D_LIB_TYPE "" CACHE STRING "Specify Urho3D library type, possible values are STATIC and SHARED")
    set (URHO3D_HOME "" CACHE PATH "Path to Urho3D build tree or SDK installation location (downstream project only)")
    if (URHO3D_PCH OR URHO3D_UPDATE_SOURCE_TREE OR URHO3D_TOOLS OR URHO3D_EXTRAS)
        # Just reference it to suppress "unused variable" CMake warning on downstream projects using this CMake module
    endif ()
    # All Urho3D downstream projects require Urho3D library, so find Urho3D library here now
    if (NOT CMAKE_PROJECT_NAME MATCHES ^Urho3D-ExternalProject-)
        find_package (Urho3D REQUIRED)
        include_directories (${URHO3D_INCLUDE_DIRS})
    endif ()
endif ()
option (URHO3D_PACKAGING "Enable resources packaging support, on Emscripten default to 1, on other platforms default to 0" ${EMSCRIPTEN})
option (URHO3D_PROFILING "Enable profiling support" TRUE)
option (URHO3D_LOGGING "Enable logging support" TRUE)
# Emscripten thread support is yet experimental; default false
if (NOT EMSCRIPTEN)
    option (URHO3D_THREADING "Enable threading support" TRUE)
else ()
    option (URHO3D_THREADING "Enable threading support" FALSE)
endif ()
option (URHO3D_TESTING "Enable testing support")
if (URHO3D_TESTING)
    if (EMSCRIPTEN)
        set (DEFAULT_TIMEOUT 10)
        set (EMSCRIPTEN_EMRUN_BROWSER firefox CACHE STRING "Specify the particular browser to be spawned by emrun during testing (Emscripten cross-compiling build only), use 'emrun --list_browsers' command to get the list of possible values")
    else ()
        set (DEFAULT_TIMEOUT 5)
    endif ()
    set (URHO3D_TEST_TIMEOUT ${DEFAULT_TIMEOUT} CACHE STRING "Number of seconds to test run the executables (when testing support is enabled only), default to 10 on Emscripten platform and 5 on other platforms")
else ()
    unset (URHO3D_TEST_TIMEOUT CACHE)
    if (EMSCRIPTEN_EMRUN_BROWSER)   # Suppress unused variable warning at the same time
        unset (EMSCRIPTEN_EMRUN_BROWSER CACHE)
    endif ()
endif ()
cmake_dependent_option (URHO3D_STATIC_RUNTIME "Use static C/C++ runtime libraries and eliminate the need for runtime DLLs installation (VS only)" FALSE "MSVC" FALSE)
cmake_dependent_option (URHO3D_WIN32_CONSOLE "Use console main() as entry point when setting up Windows executable targets (Windows platform only)" FALSE "WIN32" FALSE)
cmake_dependent_option (URHO3D_MACOSX_BUNDLE "Use MACOSX_BUNDLE when setting up Mac OS X executable targets (Xcode native build only)" FALSE "XCODE AND NOT IOS" FALSE)
if (CMAKE_CROSSCOMPILING AND NOT ANDROID)
    set (URHO3D_SCP_TO_TARGET "" CACHE STRING "Use scp to transfer executables to target system (non-Android cross-compiling build only), SSH digital key must be setup first for this to work, typical value has a pattern of usr@tgt:remote-loc")
else ()
    unset (URHO3D_SCP_TO_TARGET CACHE)
endif ()
if (ANDROID)
    set (ANDROID TRUE CACHE INTERNAL "Setup build for Android platform")
    cmake_dependent_option (ANDROID_NDK_GDB "Enable ndk-gdb for debugging (Android build only)" FALSE "CMAKE_BUILD_TYPE STREQUAL Debug" FALSE)
else ()
    unset (ANDROID_NDK_GDB CACHE)
endif ()
if (MINGW AND CMAKE_CROSSCOMPILING)
    set (MINGW_PREFIX "" CACHE STRING "Prefix path to MinGW cross-compiler tools (MinGW cross-compiling build only)")
    set (MINGW_SYSROOT "" CACHE PATH "Path to MinGW system root (MinGW cross-compiling build only)")
    # When cross-compiling then we are most probably in Unix-alike host environment which should not have problem to handle long include dirs
    # This change is required to keep ccache happy because it does not like the CMake generated include response file
    foreach (lang C CXX)
        foreach (cat OBJECTS INCLUDES)
            unset (CMAKE_${lang}_USE_RESPONSE_FILE_FOR_${cat})
        endforeach ()
    endforeach ()
endif ()
if (RPI)
    if (NOT RPI_SUPPORTED_ABIS)
        set (RPI_SUPPORTED_ABIS armeabi-v6)
        if (CMAKE_CROSSCOMPILING)
            # We have no way to know for sure so just give all the available options to user
            list (APPEND RPI_SUPPORTED_ABIS armeabi-v7a "armeabi-v7a with NEON" "armeabi-v7a with VFPV4")
        else ()
            # If not cross-compiling then we should be on the host system (device) itself, so below command is safe to be executed
            execute_process (COMMAND uname -m OUTPUT_VARIABLE HOST_MACHINE ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
            if (HOST_MACHINE MATCHES ^armv7)
                list (APPEND RPI_SUPPORTED_ABIS armeabi-v7a "armeabi-v7a with NEON" "armeabi-v7a with VFPV4")
                if (NOT RPI_ABI)
                    set (RPI_ABI armeabi-v7a)   # Set default to this specific target device
                endif ()
            endif ()
        endif ()
        set (RPI_SUPPORTED_ABIS ${RPI_SUPPORTED_ABIS} CACHE INTERNAL "Supported target ABIs for RPI build")
    endif ()
    if (CMAKE_CROSSCOMPILING)
        set (RPI_PREFIX "" CACHE STRING "Prefix path to Raspberry Pi cross-compiler tools (RPI cross-compiling build only)")
        set (RPI_SYSROOT "" CACHE PATH "Path to Raspberry Pi system root (RPI cross-compiling build only)")
    endif ()
    if (RPI_ABI)
        list (FIND RPI_SUPPORTED_ABIS ${RPI_ABI} RPI_ABI_FOUND_INDEX)
        if (RPI_ABI_FOUND_INDEX EQUAL -1)
            string (REPLACE ";" "\", \"" PRINTABLE_RPI_SUPPORTED_ABIS "${RPI_SUPPORTED_ABIS}")  # Stringify for string replace to work
            if (NOT CMAKE_CROSSCOMPILING)
                set (MSG_STR " by this Raspberry Pi device")
            endif ()
            message (FATAL_ERROR "Specified RPI_ABI = \"${RPI_ABI}\" is not supported${MSG_STR}. Supported values are: \"${PRINTABLE_RPI_SUPPORTED_ABIS}\".")
        endif()
    else ()
        set (RPI_ABI armeabi-v6)
    endif ()
    set (RPI_ABI ${RPI_ABI} CACHE STRING "Specify target ABI (RPI build only), possible values are armeabi-v6 (default for RPI 1), armeabi-v7a (default for RPI 2), armeabi-v7a with NEON, and armeabi-v7a with VFPV4" FORCE)
endif ()
if (EMSCRIPTEN)     # CMAKE_CROSSCOMPILING is always true for Emscripten
    set (EMSCRIPTEN_ROOT_PATH "" CACHE PATH "Root path to Emscripten cross-compiler tools (Emscripten cross-compiling build only)")
    set (EMSCRIPTEN_SYSROOT "" CACHE PATH "Path to Emscripten system root (Emscripten cross-compiling build only)")
    option (EMSCRIPTEN_ALLOW_MEMORY_GROWTH "Enable memory growing based on application demand (Emscripten cross-compiling build only)")
    math (EXPR EMSCRIPTEN_TOTAL_MEMORY "32 * 1024 * 1024")     # This option is ignored when EMSCRIPTEN_ALLOW_MEMORY_GROWTH option is set
    set (EMSCRIPTEN_TOTAL_MEMORY ${EMSCRIPTEN_TOTAL_MEMORY} CACHE STRING "Specify the total size of memory to be used (Emscripten cross-compiling build only); default to 33554432 (32MB), this option is ignored when EMSCRIPTEN_ALLOW_MEMORY_GROWTH=1")
    cmake_dependent_option (EMSCRIPTEN_SHARE_DATA "Enable sharing data file support (Emscripten cross-compiling build only)" FALSE "EMSCRIPTEN" FALSE)
endif ()
# Constrain the build option values in cmake-gui, if applicable
if (CMAKE_VERSION VERSION_GREATER 2.8 OR CMAKE_VERSION VERSION_EQUAL 2.8)
    set_property (CACHE URHO3D_LIB_TYPE PROPERTY STRINGS STATIC SHARED)
    if (NOT CMAKE_CONFIGURATION_TYPES)
        set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${URHO3D_BUILD_CONFIGURATIONS})
    endif ()
    if (RPI)
        set_property (CACHE RPI_ABI PROPERTY STRINGS ${RPI_SUPPORTED_ABIS})
    endif ()
endif()

# Clang tools building
if (URHO3D_CLANG_TOOLS OR URHO3D_BINDINGS)
    # Ensure LLVM/Clang is installed
    find_program (LLVM_CONFIG NAMES llvm-config llvm-config-64 llvm-config-32 HINTS $ENV{LLVM_CLANG_ROOT}/bin DOC "LLVM config tool" NO_CMAKE_FIND_ROOT_PATH)
    if (NOT LLVM_CONFIG)
        message (FATAL_ERROR "Could not find LLVM/Clang installation")
    endif ()
endif ()
if (URHO3D_CLANG_TOOLS)
    # Require C++11 standard and no precompiled-header
    set (URHO3D_C++11 1)
    set (URHO3D_PCH 0)
    set (URHO3D_LIB_TYPE SHARED)
    # Set build options that would maximise the AST of Urho3D library
    foreach (OPT URHO3D_ANGELSCRIPT URHO3D_LUA URHO3D_FILEWATCHER URHO3D_PROFILING URHO3D_LOGGING URHO3D_NAVIGATION URHO3D_NETWORK URHO3D_PHYSICS URHO3D_URHO2D URHO3D_DATABASE_SQLITE)
        set (${OPT} 1)
    endforeach()
    foreach (OPT URHO3D_TESTING URHO3D_LUAJIT URHO3D_DATABASE_ODBC)
        set (${OPT} 0)
    endforeach()
endif ()

# Enable testing
if (URHO3D_TESTING)
    enable_testing ()
    add_definitions (-DURHO3D_TESTING)
endif ()

# Enable coverity scan modeling
if ($ENV{COVERITY_SCAN_BRANCH})
    add_definitions (-DCOVERITY_SCAN_MODEL)
endif ()

# Enable SSE instruction set. Requires Pentium III or Athlon XP processor at minimum.
if (URHO3D_SSE)
    add_definitions (-DURHO3D_SSE)
endif ()

# Enable NEON instruction set.
if (URHO3D_NEON)
    add_definitions (-DURHO3D_NEON -DSTBI_NEON)     # BT_USE_NEON is already being self-defined by Bullet library as appropriate
endif ()

# Enable structured exception handling and minidumps on MSVC only.
if (MSVC AND URHO3D_MINIDUMPS)
    add_definitions (-DURHO3D_MINIDUMPS)
endif ()

# By default use the MSVC dynamic runtime. To eliminate the need to distribute the runtime installer,
# this can be switched off if not using Urho3D as a shared library.
if (MSVC)
    if (URHO3D_STATIC_RUNTIME)
        set (RELEASE_RUNTIME /MT)
        set (DEBUG_RUNTIME /MTd)
    else ()
        set (RELEASE_RUNTIME "")
        set (DEBUG_RUNTIME "")
    endif ()
endif ()

# By default Windows platform setups main executable as Windows application with WinMain() as entry point
# this build option overrides the default to set the main executable as console application with main() as entry point instead
if (URHO3D_WIN32_CONSOLE)
    add_definitions (-DURHO3D_WIN32_CONSOLE)
endif ()

# Enable file watcher support for automatic resource reloads by default.
if (URHO3D_FILEWATCHER)
    add_definitions (-DURHO3D_FILEWATCHER)
endif ()

# Enable profiling by default. If disabled, autoprofileblocks become no-ops and the Profiler subsystem is not instantiated.
if (URHO3D_PROFILING)
    add_definitions (-DURHO3D_PROFILING)
endif ()

# Enable logging by default. If disabled, LOGXXXX macros become no-ops and the Log subsystem is not instantiated.
if (URHO3D_LOGGING)
    add_definitions (-DURHO3D_LOGGING)
endif ()

# Enable threading by default, except for Emscripten.
if (URHO3D_THREADING)
    add_definitions (-DURHO3D_THREADING)
endif ()

# Add definitions for Emscripten
if (EMSCRIPTEN)
    add_definitions (-DNO_POPEN)
endif ()

# Add definition for Direct3D11
if (URHO3D_D3D11)
    set (URHO3D_OPENGL 0)
    add_definitions (-DURHO3D_D3D11)
endif ()

# Add definition for OpenGL
if (URHO3D_OPENGL)
    add_definitions (-DURHO3D_OPENGL)
endif ()

# Add definitions for GLEW
if (NOT IOS AND NOT ANDROID AND NOT RPI AND URHO3D_OPENGL)
    add_definitions (-DGLEW_STATIC -DGLEW_NO_GLU)
endif ()

# Default library type is STATIC
if (URHO3D_LIB_TYPE)
    string (TOUPPER ${URHO3D_LIB_TYPE} URHO3D_LIB_TYPE)
endif ()
if (NOT URHO3D_LIB_TYPE STREQUAL SHARED)
    set (URHO3D_LIB_TYPE STATIC)
    if (NOT MSVC)   # This define will be baked into the export header for MSVC compiler
        add_definitions (-DURHO3D_STATIC_DEFINE)
    endif ()
endif ()

# Add definition for AngelScript
if (URHO3D_ANGELSCRIPT)
    add_definitions (-DURHO3D_ANGELSCRIPT)
endif ()

# Add definition for Lua and LuaJIT
if (URHO3D_LUAJIT)
    add_definitions (-DURHO3D_LUAJIT)
    set (JIT JIT)
    # Implied URHO3D_LUA
    set (URHO3D_LUA 1)
endif ()
if (URHO3D_LUA)
    add_definitions (-DURHO3D_LUA)
    # Optionally enable Lua / C++ wrapper safety checks
    if (NOT URHO3D_SAFE_LUA)
        add_definitions (-DTOLUA_RELEASE)
    endif ()
endif ()
if (URHO3D_LUA_RAW_SCRIPT_LOADER)
    add_definitions (-DURHO3D_LUA_RAW_SCRIPT_LOADER)
endif ()

# Add definition for Navigation
if (URHO3D_NAVIGATION)
    add_definitions (-DURHO3D_NAVIGATION)
endif ()

# Add definition for Network
if (URHO3D_NETWORK)
    add_definitions (-DURHO3D_NETWORK)
endif ()

# Add definition for Physics
if (URHO3D_PHYSICS)
    add_definitions (-DURHO3D_PHYSICS)
endif ()

# Add definition for Urho2D
if (URHO3D_URHO2D)
    add_definitions (-DURHO3D_URHO2D)
endif ()

# Add definition for Database
if (URHO3D_DATABASE_ODBC)
    set (URHO3D_DATABASE_SQLITE 0)
    find_package (ODBC REQUIRED)
    set (URHO3D_C++11 1)
    set (URHO3D_DATABASE 1)
    add_definitions (-DURHO3D_DATABASE -DURHO3D_DATABASE_ODBC)
endif ()
if (URHO3D_DATABASE_SQLITE)
    set (URHO3D_DATABASE 1)
    add_definitions (-DURHO3D_DATABASE -DURHO3D_DATABASE_SQLITE)
endif ()

# Platform and compiler specific options
if (URHO3D_C++11)
    add_definitions (-DURHO3D_CPP11)   # Note the define is NOT 'URHO3D_C++11'!
    if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
        # Use gnu++11/gnu++0x instead of c++11/c++0x as the latter does not work as expected when cross compiling
        foreach (STANDARD gnu++11 gnu++0x)  # Fallback to gnu++0x on older GCC version
            execute_process (COMMAND echo COMMAND ${CMAKE_CXX_COMPILER} -std=${STANDARD} -E - RESULT_VARIABLE GCC_EXIT_CODE OUTPUT_QUIET ERROR_QUIET)
            if (GCC_EXIT_CODE EQUAL 0)
                set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${STANDARD}")
                break ()
            endif ()
        endforeach ()
        if (NOT GCC_EXIT_CODE EQUAL 0)
            execute_process (COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION ERROR_QUIET)
            message (FATAL_ERROR "Your GCC version ${GCC_VERSION} is too old to enable C++11 standard")
        endif ()
    elseif (CMAKE_CXX_COMPILER_ID MATCHES Clang)
        # Cannot set CMAKE_CXX_FLAGS here directly because CMake uses the same flags for both C++ and Object-C languages, the latter does not support c++11 standard
        # Workaround the problem by setting the compiler flags in the source properties for C++ language only in the setup_target() macro
        set (CLANG_CXX_FLAGS -std=c++11)
    elseif (MSVC80)
        message (FATAL_ERROR "Your MSVC version is too told to enable C++11 standard")
    endif ()
endif ()
if (IOS)
    # IOS-specific setup
    add_definitions (-DIOS)
    if (URHO3D_64BIT)
        set (CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_INCLUDING_64_BIT))
    else ()
        set (CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_32_BIT))
    endif ()
    set (CMAKE_XCODE_EFFECTIVE_PLATFORMS -iphoneos -iphonesimulator)
    set (CMAKE_OSX_SYSROOT iphoneos)    # Set Base SDK to "Latest iOS"
    execute_process (COMMAND xcodebuild -version -sdk ${CMAKE_OSX_SYSROOT} Path OUTPUT_VARIABLE IOS_SYSROOT OUTPUT_STRIP_TRAILING_WHITESPACE)   # Obtain iOS sysroot path
    set (CMAKE_FIND_ROOT_PATH ${IOS_SYSROOT})
    # Ensure the CMAKE_OSX_DEPLOYMENT_TARGET is set to empty
    unset (CMAKE_OSX_DEPLOYMENT_TARGET CACHE)
elseif (XCODE)
    # MacOSX-Xcode-specific setup
    if (NOT URHO3D_64BIT)
        set (CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_32_BIT))
    endif ()
    set (CMAKE_OSX_SYSROOT macosx)    # Set Base SDK to "Latest OS X"
    if (NOT CMAKE_OSX_DEPLOYMENT_TARGET)
        # If not set, set to current running build system OS version by default
        execute_process (COMMAND sw_vers -productVersion OUTPUT_VARIABLE CURRENT_OSX_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
        string (REGEX REPLACE ^\([^.]+\\.[^.]+\).* \\1 CMAKE_OSX_DEPLOYMENT_TARGET ${CURRENT_OSX_VERSION})
    endif ()
endif ()
if (IOS OR URHO3D_MACOSX_BUNDLE)
    # Common MacOSX and iOS bundle setup
    if (NOT MACOSX_BUNDLE_GUI_IDENTIFIER)
        set (MACOSX_BUNDLE_GUI_IDENTIFIER com.github.urho3d.\${PRODUCT_NAME:bundleIdentifier:lower})
    endif ()
    if (NOT MACOSX_BUNDLE_BUNDLE_NAME)
        set (MACOSX_BUNDLE_BUNDLE_NAME \${PRODUCT_NAME})
    endif ()
endif ()
if (MSVC)
    # Visual Studio-specific setup
    add_definitions (-D_CRT_SECURE_NO_WARNINGS)
    # Note: All CMAKE_xxx_FLAGS variables are not in list context (although they should be)
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${DEBUG_RUNTIME}")
    set (CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE} ${RELEASE_RUNTIME} /fp:fast /Zi /GS-")
    set (CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELWITHDEBINFO})
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEBUG_RUNTIME}")
    set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} ${RELEASE_RUNTIME} /fp:fast /Zi /GS- /D _SECURE_SCL=0")
    set (CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
    # In Visual Studio, SSE2 flag is redundant if already compiling as 64bit; it is already the default for VS2012 (onward) on 32bit
    if (URHO3D_SSE AND NOT URHO3D_64BIT AND MSVC_VERSION LESS 1700)
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /arch:SSE2")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")
    endif ()
    set (CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF /DEBUG")
    set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF")
else ()
    # GCC/Clang-specific setup
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof")
    if (ANDROID)
        # Most of the flags are already setup in android.toolchain.cmake module
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstack-protector")
    else ()
        if (RPI)
            add_definitions (-DRPI)
            set (RPI_CFLAGS "-pipe -mfloat-abi=hard -Wno-psabi")    # We only support armhf distros, so turn on hard-float by default
            if (RPI_ABI MATCHES ^armeabi-v7a)
                set (RPI_CFLAGS "${RPI_CFLAGS} -mcpu=cortex-a7")
                if (RPI_ABI MATCHES NEON)
                    set (RPI_CFLAGS "${RPI_CFLAGS} -mfpu=neon-vfpv4")
                elseif (RPI_ABI MATCHES VFPV4)
                    set (RPI_CFLAGS "${RPI_CFLAGS} -mfpu=vfpv4")
                else ()
                    set (RPI_CFLAGS "${RPI_CFLAGS} -mfpu=vfpv4-d16")
                endif ()
            else ()
                set (RPI_CFLAGS "${RPI_CFLAGS} -mcpu=arm1176jzf-s -mfpu=vfp")
            endif ()
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${RPI_CFLAGS}")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${RPI_CFLAGS}")
        else ()
            if (NOT XCODE AND NOT EMSCRIPTEN)
                # This may influence the effective SSE level when URHO3D_SSE is on as well
                set (URHO3D_DEPLOYMENT_TARGET native CACHE STRING "Specify the minimum CPU type on which the target binaries are to be deployed (Linux, MinGW, and non-Xcode OSX native build only), see GCC/Clang's -march option for possible values; Use 'generic' for targeting a wide range of generic processors")
                if (NOT URHO3D_DEPLOYMENT_TARGET STREQUAL generic)
                    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=${URHO3D_DEPLOYMENT_TARGET}")
                    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=${URHO3D_DEPLOYMENT_TARGET}")
                endif ()
            endif ()
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffast-math")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")
            if (URHO3D_64BIT)
                set (DASH_MBIT -m64)    # This variable is intentionally not defined on Android and RPI platform, it is used again in LuaJIT library build
            else ()
                set (DASH_MBIT -m32)
                if (URHO3D_SSE)
                    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse2")
                    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
                endif ()
            endif ()
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DASH_MBIT}")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DASH_MBIT}")
        endif ()
        if (EMSCRIPTEN)
            # Emscripten-specific setup
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-warn-absolute-paths -Wno-unknown-warning-option")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-warn-absolute-paths -Wno-unknown-warning-option")
            if (URHO3D_THREADING)
                set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_PTHREADS=1")
                set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_PTHREADS=1")
            endif ()
            # Prior to version 1.31.3 emcc does not consistently add the cpp standard and remove Emscripten-specific compiler flags
            # before passing on the work to the underlying LLVM/Clang compiler, this has resulted in preprocessing error when enabling the PCH and ccache
            # (See https://github.com/kripken/emscripten/issues/3365 for more detail)
            if (EMCC_VERSION VERSION_LESS 1.31.3)
                set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")
            endif ()
            set (CMAKE_C_FLAGS_RELEASE "-Oz -DNDEBUG")
            set (CMAKE_CXX_FLAGS_RELEASE "-Oz -DNDEBUG")
            # CMake does not treat Emscripten as a valid platform yet, certain platform-specific variables cannot be set in the
            # toolchain file as they get overwritten by CMake internally as per Linux platform default, so set them here for now
            set (CMAKE_EXECUTABLE_SUFFIX .html)
        elseif (MINGW)
            # MinGW-specific setup
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static -static-libgcc -fno-keep-inline-dllexport")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libstdc++ -static-libgcc -fno-keep-inline-dllexport")
            set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static")
            if (NOT URHO3D_64BIT)
                # Prevent auto-vectorize optimization when using -O3, unless stack realign is being enforced globally
                if (URHO3D_SSE)
                    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mstackrealign")
                    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mstackrealign")
                else ()
                    if (DEFINED ENV{TRAVIS})
                        # TODO: Remove this workaround when Travis CI VM has been migrated to Ubuntu 14.04 LTS
                        set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-tree-slp-vectorize -fno-tree-vectorize")
                        set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-tree-slp-vectorize -fno-tree-vectorize")
                    else ()
                        set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-tree-loop-vectorize -fno-tree-slp-vectorize -fno-tree-vectorize")
                        set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-tree-loop-vectorize -fno-tree-slp-vectorize -fno-tree-vectorize")
                    endif ()
                endif ()
            endif ()
        else ()
            # Not Android and not Emscripten and not MinGW derivative
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")     # This will emit '-DREENTRANT' to compiler and '-lpthread' to linker on Linux and Mac OSX platform
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread") # However, it may emit other equivalent compiler define and/or linker flag on other *nix platforms
        endif ()
        set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG -D_DEBUG")
        set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -D_DEBUG")
    endif ()
    if (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
        if (CMAKE_GENERATOR STREQUAL Ninja OR "$ENV{USE_CCACHE}")
            # When ccache support is on, these flags keep the color diagnostics pipe through ccache output and suppress Clang warning due ccache internal preprocessing step
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics -Qunused-arguments")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics -Qunused-arguments")
        endif ()
        # Temporary workaround for Travis CI VM as Ubuntu 12.04 LTS still uses old glibc header files that do not have the necessary patch for Clang to work correctly
        # TODO: Remove this workaround when Travis CI VM has been migrated to Ubuntu 14.04 LTS
        if (DEFINED ENV{TRAVIS} AND "$ENV{LINUX}")
            add_definitions (-D__extern_always_inline=inline)
        endif ()
    endif ()
endif ()

# Macro for setting common output directories
macro (set_output_directories OUTPUT_PATH)
    foreach (TYPE ${ARGN})
        set (CMAKE_${TYPE}_OUTPUT_DIRECTORY ${OUTPUT_PATH})
        foreach (CONFIG ${CMAKE_CONFIGURATION_TYPES})
            string (TOUPPER ${CONFIG} CONFIG)
            set (CMAKE_${TYPE}_OUTPUT_DIRECTORY_${CONFIG} ${OUTPUT_PATH})
        endforeach ()
    endforeach ()
endmacro ()

# Macro for setting runtime output directories for tools
macro (set_tool_output_directories)
    set_output_directories (${CMAKE_BINARY_DIR}/bin/tool/${ARGN} RUNTIME PDB)
    if (DEST_RUNTIME_DIR STREQUAL bin)
        set (DEST_RUNTIME_DIR bin/tool/${ARGN})
    endif ()
endmacro ()

# Set common binary output directory for all platforms
set_output_directories (${CMAKE_BINARY_DIR}/bin RUNTIME PDB)

# Macro for setting symbolic link on platform that supports it
macro (create_symlink SOURCE DESTINATION)
    # Make absolute paths so they work more reliably on cmake-gui
    if (IS_ABSOLUTE ${SOURCE})
        set (ABS_SOURCE ${SOURCE})
    else ()
        set (ABS_SOURCE ${CMAKE_SOURCE_DIR}/${SOURCE})
    endif ()
    if (IS_ABSOLUTE ${DESTINATION})
        set (ABS_DESTINATION ${DESTINATION})
    else ()
        set (ABS_DESTINATION ${CMAKE_BINARY_DIR}/${DESTINATION})
    endif ()
    if (CMAKE_HOST_WIN32)
        if (IS_DIRECTORY ${ABS_SOURCE})
            set (SLASH_D /D)
        else ()
            unset (SLASH_D)
        endif ()
        if (URHO3D_MKLINK)
            if (NOT EXISTS ${ABS_DESTINATION})
                # Have to use string-REPLACE as file-TO_NATIVE_PATH does not work as expected with MinGW on "backward slash" host system
                string (REPLACE / \\ BACKWARD_ABS_DESTINATION ${ABS_DESTINATION})
                string (REPLACE / \\ BACKWARD_ABS_SOURCE ${ABS_SOURCE})
                execute_process (COMMAND cmd /C mklink ${SLASH_D} ${BACKWARD_ABS_DESTINATION} ${BACKWARD_ABS_SOURCE} OUTPUT_QUIET ERROR_QUIET)
            endif ()
        elseif (${ARGN} STREQUAL FALLBACK_TO_COPY)
            if (SLASH_D)
                set (COMMAND COMMAND ${CMAKE_COMMAND} -E copy_directory ${ABS_SOURCE} ${ABS_DESTINATION})
            else ()
                set (COMMAND COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ABS_SOURCE} ${ABS_DESTINATION})
            endif ()
            # Fallback to copy only one time
            execute_process (${COMMAND})
            if (TARGET ${TARGET_NAME})
                # Fallback to copy everytime the target is built
                add_custom_command (TARGET ${TARGET_NAME} POST_BUILD ${COMMAND})
            endif ()
        else ()
            message (WARNING "Unable to create symbolic link on this host system, you may need to manually copy file/dir from \"${SOURCE}\" to \"${DESTINATION}\"")
        endif ()
    else ()
        execute_process (COMMAND ${CMAKE_COMMAND} -E create_symlink ${ABS_SOURCE} ${ABS_DESTINATION})
    endif ()
endmacro ()

include (GenerateExportHeader)

# Macro for precompiling header (On MSVC, the dummy C++ or C implementation file for precompiling the header file would be generated if not already exists)
# This macro should be called before the CMake target has been added
# Typically, user should indirectly call this macro by using the 'PCH' option when calling define_source_files() macro
macro (enable_pch HEADER_PATHNAME)
    # No op when PCH support is not enabled
    if (URHO3D_PCH)
        # Get the optional LANG parameter to indicate whether the header should be treated as C or C++ header, default to C++
        if ("${ARGN}" STREQUAL C)   # Stringigy as the LANG paramater could be empty
            set (EXT c)
            set (LANG C)
            set (LANG_H c-header)
        else ()
            # This is the default
            set (EXT cpp)
            set (LANG CXX)
            set (LANG_H c++-header)
        endif ()
        # Relative path is resolved using CMAKE_CURRENT_SOURCE_DIR
        if (IS_ABSOLUTE ${HEADER_PATHNAME})
            set (ABS_HEADER_PATHNAME ${HEADER_PATHNAME})
        else ()
            set (ABS_HEADER_PATHNAME ${CMAKE_CURRENT_SOURCE_DIR}/${HEADER_PATHNAME})
        endif ()
        # Determine the precompiled header output filename
        get_filename_component (HEADER_FILENAME ${HEADER_PATHNAME} NAME)
        if (CMAKE_COMPILER_IS_GNUCXX)
            # GNU g++
            set (PCH_FILENAME ${HEADER_FILENAME}.gch)
        else ()
            # Clang or MSVC
            set (PCH_FILENAME ${HEADER_FILENAME}.pch)
        endif ()

        if (MSVC)
            get_filename_component (NAME_WE ${HEADER_FILENAME} NAME_WE)
            if (TARGET ${TARGET_NAME})
                foreach (FILE ${SOURCE_FILES})
                    if (FILE MATCHES \\.${EXT}$)
                        if (FILE MATCHES ${NAME_WE}\\.${EXT}$)
                            # Precompiling header file
                            set_property (SOURCE ${FILE} APPEND_STRING PROPERTY COMPILE_FLAGS " /Fp$(IntDir)${PCH_FILENAME} /Yc${HEADER_FILENAME}")     # Need a leading space for appending
                        else ()
                            # Using precompiled header file
                            get_property (NO_PCH SOURCE ${FILE} PROPERTY NO_PCH)
                            if (NOT NO_PCH)
                                set_property (SOURCE ${FILE} APPEND_STRING PROPERTY COMPILE_FLAGS " /Fp$(IntDir)${PCH_FILENAME} /Yu${HEADER_FILENAME} /FI${HEADER_FILENAME}")
                            endif ()
                        endif ()
                    endif ()
                endforeach ()
                unset (${TARGET_NAME}_HEADER_PATHNAME)
            else ()
                # The target has not been created yet, so set an internal variable to come back here again later
                set (${TARGET_NAME}_HEADER_PATHNAME ${ARGV})
                # But proceed to add the dummy C++ or C implementation file if necessary
                set (${LANG}_FILENAME ${NAME_WE}.${EXT})
                get_filename_component (PATH ${HEADER_PATHNAME} PATH)
                if (PATH)
                    set (PATH ${PATH}/)
                endif ()
                list (FIND SOURCE_FILES ${PATH}${${LANG}_FILENAME} ${LANG}_FILENAME_FOUND)
                if (${LANG}_FILENAME_FOUND STREQUAL -1)
                    file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/${${LANG}_FILENAME} "// This is a generated file. DO NOT EDIT!\n\n#include \"${HEADER_FILENAME}\"")
                    list (APPEND SOURCE_FILES ${${LANG}_FILENAME})
                endif ()
            endif ()
        elseif (XCODE)
            if (TARGET ${TARGET_NAME})
                # Precompiling and using precompiled header file
                set_target_properties (${TARGET_NAME} PROPERTIES XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER YES XCODE_ATTRIBUTE_GCC_PREFIX_HEADER ${ABS_HEADER_PATHNAME})
                unset (${TARGET_NAME}_HEADER_PATHNAME)
            else ()
                # The target has not been created yet, so set an internal variable to come back here again later
                set (${TARGET_NAME}_HEADER_PATHNAME ${ARGV})
            endif ()
        else ()
            # GCC or Clang
            if (TARGET ${TARGET_NAME})
                # Precompiling header file
                get_directory_property (COMPILE_DEFINITIONS COMPILE_DEFINITIONS)
                get_directory_property (INCLUDE_DIRECTORIES INCLUDE_DIRECTORIES)
                get_target_property (TYPE ${TARGET_NAME} TYPE)
                if (TYPE MATCHES SHARED)
                    list (APPEND COMPILE_DEFINITIONS ${TARGET_NAME}_EXPORTS)
                    # todo: Reevaluate the replacement of this deprecated function (since CMake 2.8.12) when the CMake minimum required version is set to 2.8.12
                    # At the moment it seems using the function is the "only way" to get the export flags into a CMake variable
                    # Additionally, CMake implementation of 'VISIBILITY_INLINES_HIDDEN' has a bug (tested in 2.8.12.2) that it erroneously sets the flag for C compiler too
                    add_compiler_export_flags (COMPILER_EXPORT_FLAGS)
                    # To cater for Android/CMake toolchain which already adds -fPIC flags into the CMake C and CXX compiler flags and MinGW which already uses PIC for all codes
                    if (NOT ANDROID AND NOT MINGW)
                        set (COMPILER_EXPORT_FLAGS "${COMPILER_EXPORT_FLAGS} -fPIC")
                    endif ()
                elseif (PROJECT_NAME STREQUAL Urho3D AND NOT ${TARGET_NAME} STREQUAL Urho3D AND URHO3D_LIB_TYPE STREQUAL SHARED)
                    # If it is one of the Urho3D library dependency then use the same PIC flag as Urho3D library
                    if (NOT ANDROID AND NOT MINGW)
                        set (COMPILER_EXPORT_FLAGS -fPIC)
                    endif ()
                endif ()
                string (REPLACE ";" " -D" COMPILE_DEFINITIONS "-D${COMPILE_DEFINITIONS}")
                string (REPLACE "\"" "\\\"" COMPILE_DEFINITIONS ${COMPILE_DEFINITIONS})
                string (REPLACE ";" "\" -I\"" INCLUDE_DIRECTORIES "-I\"${INCLUDE_DIRECTORIES}\"")
                # Make sure the precompiled headers are not stale by creating custom rules to re-compile the header as necessary
                file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${PCH_FILENAME})
                foreach (CONFIG ${CMAKE_CONFIGURATION_TYPES} ${CMAKE_BUILD_TYPE})   # These two vars are mutually exclusive
                    # Generate *.rsp containing configuration specific compiler flags
                    string (TOUPPER ${CONFIG} UPPERCASE_CONFIG)
                    file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.rsp.new "${COMPILE_DEFINITIONS} ${CLANG_${LANG}_FLAGS} ${CMAKE_${LANG}_FLAGS} ${CMAKE_${LANG}_FLAGS_${UPPERCASE_CONFIG}} ${COMPILER_EXPORT_FLAGS} ${INCLUDE_DIRECTORIES} -c -x ${LANG_H}")
                    execute_process (COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.rsp.new ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.rsp)
                    file (REMOVE ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.rsp.new)
                    # Determine the dependency list
                    execute_process (COMMAND ${CMAKE_${LANG}_COMPILER} @${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.rsp -MTdeps -MM -o ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.deps ${ABS_HEADER_PATHNAME} RESULT_VARIABLE ${LANG}_COMPILER_EXIT_CODE)
                    if (NOT ${LANG}_COMPILER_EXIT_CODE EQUAL 0)
                        message (FATAL_ERROR
                            "The configured compiler toolchain in the build tree is not able to handle all the compiler flags required to build the project with PCH enabled. "
                            "Please kindly update your compiler toolchain to its latest version. "
                            "If you are using MinGW then make sure it is MinGW-W64 instead of MinGW-W32 or TDM-GCC (Code::Blocks default). "
                            "Or disable the PCH build support by passing the '-DURHO3D_PCH=0' when retrying to configure/generate the build tree. "
                            "However, if you think there is something wrong with our build system then kindly file a bug report to the project devs.")
                    endif ()
                    file (STRINGS ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.deps DEPS)
                    string (REGEX REPLACE "^deps: *| *\\; *" ";" DEPS ${DEPS})
                    string (REGEX REPLACE "\\\\ " "\ " DEPS "${DEPS}")  # Need to stringify the second time to preserve the semicolons
                    # Create the rule that depends on the included headers
                    add_custom_command (OUTPUT ${HEADER_FILENAME}.${CONFIG}.pch.trigger
                        COMMAND ${CMAKE_${LANG}_COMPILER} @${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.rsp -o ${PCH_FILENAME}/${PCH_FILENAME}.${CONFIG} ${ABS_HEADER_PATHNAME}
                        COMMAND ${CMAKE_COMMAND} -E touch ${HEADER_FILENAME}.${CONFIG}.pch.trigger
                        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.rsp ${DEPS}
                        COMMENT "Precompiling header file '${HEADER_FILENAME}' for ${CONFIG} configuration")
                endforeach ()
                # Using precompiled header file
                if ($ENV{COVERITY_SCAN_BRANCH})
                    # Coverity scan does not support PCH so workaround by including the actual header file
                    set (ABS_PATH_PCH ${ABS_HEADER_PATHNAME})
                else ()
                    set (ABS_PATH_PCH ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME})
                endif ()
                foreach (FILE ${SOURCE_FILES})
                    if (FILE MATCHES \\.${EXT}$)
                        get_property (NO_PCH SOURCE ${FILE} PROPERTY NO_PCH)
                        if (NOT NO_PCH)
                            set_property (SOURCE ${FILE} APPEND_STRING PROPERTY COMPILE_FLAGS " -include \"${ABS_PATH_PCH}\"")
                        endif ()
                    endif ()
                endforeach ()
                unset (${TARGET_NAME}_HEADER_PATHNAME)
            else ()
                # The target has not been created yet, so set an internal variable to come back here again later
                set (${TARGET_NAME}_HEADER_PATHNAME ${ARGV})
                # But proceed to add the dummy source file(s) to trigger the custom command output rule
                if (CMAKE_CONFIGURATION_TYPES)
                    # Multi-config, trigger all rules and let the compiler to choose which precompiled header is suitable to use
                    foreach (CONFIG ${CMAKE_CONFIGURATION_TYPES})
                        list (APPEND TRIGGERS ${HEADER_FILENAME}.${CONFIG}.pch.trigger)
                    endforeach ()
                else ()
                    # Single-config, just trigger the corresponding rule matching the current build configuration
                    set (TRIGGERS ${HEADER_FILENAME}.${CMAKE_BUILD_TYPE}.pch.trigger)
                endif ()
                list (APPEND SOURCE_FILES ${TRIGGERS})
            endif ()
        endif ()
    endif ()
endmacro ()

# Macro for setting up dependency lib for compilation and linking of a target
macro (setup_target)
    # Include directories
    include_directories (${INCLUDE_DIRS})
    # Link libraries
    define_dependency_libs (${TARGET_NAME})
    target_link_libraries (${TARGET_NAME} ${ABSOLUTE_PATH_LIBS} ${LIBS})
    # Enable PCH if requested
    if (${TARGET_NAME}_HEADER_PATHNAME)
        enable_pch (${${TARGET_NAME}_HEADER_PATHNAME})
    endif ()
    # Set additional linker dependencies (only work for Makefile-based generator according to CMake documentation)
    if (LINK_DEPENDS)
        string (REPLACE ";" "\;" LINK_DEPENDS "${LINK_DEPENDS}")        # Stringify for string replacement
        list (APPEND TARGET_PROPERTIES LINK_DEPENDS "${LINK_DEPENDS}")  # Stringify with semicolons already escaped
        unset (LINK_DEPENDS)
    endif ()
    # CMake does not support IPHONEOS_DEPLOYMENT_TARGET the same manner as it supports CMAKE_OSX_DEPLOYMENT_TARGET
    # The iOS deployment target is set using the corresponding Xcode attribute as target property instead
    if (IOS AND IPHONEOS_DEPLOYMENT_TARGET)
        list (APPEND TARGET_PROPERTIES XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET ${IPHONEOS_DEPLOYMENT_TARGET})
    endif ()
    if (TARGET_PROPERTIES)
        set_target_properties (${TARGET_NAME} PROPERTIES ${TARGET_PROPERTIES})
        unset (TARGET_PROPERTIES)
    endif ()

    # Workaround CMake/Xcode generator bug where it always appends '/build' path element to SYMROOT attribute and as such the items in Products are always rendered as red as if they are not yet built
    if (XCODE AND NOT CMAKE_PROJECT_NAME MATCHES ^ExternalProject-)
        file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/build)
        get_target_property (LOCATION ${TARGET_NAME} LOCATION)
        string (REGEX REPLACE "^.*\\$\\(CONFIGURATION\\)" $(CONFIGURATION) SYMLINK ${LOCATION})
        get_filename_component (DIRECTORY ${SYMLINK} PATH)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
            COMMAND mkdir -p ${DIRECTORY} && ln -sf $<TARGET_FILE:${TARGET_NAME}> ${DIRECTORY}/$<TARGET_FILE_NAME:${TARGET_NAME}>
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/build)
    endif ()

    # Workaround CMake problem of sharing CMAKE_CXX_FLAGS for both C++ and Objective-C languages
    if (CLANG_CXX_FLAGS)
        foreach (FILE ${SOURCE_FILES})
            if (FILE MATCHES \\.cpp$|\\.cc$)
                set_property (SOURCE ${FILE} APPEND_STRING PROPERTY COMPILE_FLAGS " ${CLANG_CXX_FLAGS}")
            endif ()
        endforeach ()
    endif ()
endmacro ()

# Macro for checking the SOURCE_FILES variable is properly initialized
macro (check_source_files)
    if (NOT SOURCE_FILES)
        message (FATAL_ERROR "Could not configure and generate the project file because no source files have been defined yet. "
            "You can define the source files explicitly by setting the SOURCE_FILES variable in your CMakeLists.txt; or "
            "by calling the define_source_files() macro which would by default glob all the C++ source files found in the same scope of "
            "CMakeLists.txt where the macro is being called and the macro would set the SOURCE_FILES variable automatically. "
            "If your source files are not located in the same directory as the CMakeLists.txt or your source files are "
            "more than just C++ language then you probably have to pass in extra arguments when calling the macro in order to make it works. "
            "See the define_source_files() macro definition in the CMake/Modules/Urho3D-CMake-common.cmake for more detail.")
    endif ()
endmacro ()

# Macro for setting up a library target
# Macro arguments:
#  STATIC/SHARED/MODULE/EXCLUDE_FROM_ALL - see CMake help on add_library() command
# CMake variables:
#  SOURCE_FILES - list of source files
#  INCLUDE_DIRS - list of directories for include search path
#  LIBS - list of dependent libraries that are built internally in the project
#  ABSOLUTE_PATH_LIBS - list of dependent libraries that are external to the project
#  LINK_DEPENDS - list of additional files on which a target binary depends for linking (Makefile-based generator only)
#  TARGET_PROPERTIES - list of target properties
macro (setup_library)
    check_source_files ()
    add_library (${TARGET_NAME} ${ARGN} ${SOURCE_FILES})
    setup_target ()

    # Setup the compiler flags for building shared library
    get_target_property (LIB_TYPE ${TARGET_NAME} TYPE)
    if (LIB_TYPE MATCHES SHARED)
        # Hide the symbols that are not explicitly marked for export
        add_compiler_export_flags ()
    endif ()

    if (PROJECT_NAME STREQUAL Urho3D)
        if (NOT ${TARGET_NAME} STREQUAL Urho3D)
            # Only interested in static library type, i.e. exclude shared and module library types
            if (LIB_TYPE MATCHES STATIC)
                set (STATIC_LIBRARY_TARGETS ${STATIC_LIBRARY_TARGETS} ${TARGET_NAME} PARENT_SCOPE)
            endif ()
        endif ()
    elseif (URHO3D_SCP_TO_TARGET)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND scp $<TARGET_FILE:${TARGET_NAME}> ${URHO3D_SCP_TO_TARGET} || exit 0
            COMMENT "Scp-ing ${TARGET_NAME} library to target system")
    endif ()
endmacro ()

# Macro for setting up an executable target
# Macro arguments:
#  NODEPS - setup executable target without defining Urho3D dependency libraries
#  WIN32/MACOSX_BUNDLE/EXCLUDE_FROM_ALL - see CMake help on add_executable() command
# CMake variables:
#  SOURCE_FILES - list of source files
#  INCLUDE_DIRS - list of directories for include search path
#  LIBS - list of dependent libraries that are built internally in the project
#  ABSOLUTE_PATH_LIBS - list of dependent libraries that are external to the project
#  LINK_DEPENDS - list of additional files on which a target binary depends for linking (Makefile-based generator only)
#  TARGET_PROPERTIES - list of target properties
macro (setup_executable)
    # Parse extra arguments
    cmake_parse_arguments (ARG "NODEPS" "" "" ${ARGN})

    check_source_files ()
    add_executable (${TARGET_NAME} ${ARG_UNPARSED_ARGUMENTS} ${SOURCE_FILES})
    if (ARG_NODEPS)
        define_dependency_libs (Urho3D-nodeps)
    else ()
        define_dependency_libs (Urho3D)
    endif ()
    setup_target ()

    if (URHO3D_SCP_TO_TARGET)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND scp $<TARGET_FILE:${TARGET_NAME}> ${URHO3D_SCP_TO_TARGET} || exit 0
            COMMENT "Scp-ing ${TARGET_NAME} executable to target system")
    endif ()
    if (DIRECT3D_DLL)
        # Make a copy of the D3D DLL to the runtime directory in the build tree
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${DIRECT3D_DLL} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endif ()
    if (WIN32 AND NOT ARG_NODEPS AND URHO3D_LIB_TYPE STREQUAL SHARED)
        # Make a copy of the Urho3D DLL to the runtime directory in the build tree
        if (TARGET Urho3D)
            add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Urho3D> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        else ()
            foreach (DLL ${URHO3D_DLL})
                add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${DLL} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
            endforeach ()
        endif ()
    endif ()
    # Need to check if the destination variable is defined first because this macro could be called by downstream project that does not wish to install anything
    if (DEST_RUNTIME_DIR)
        if (EMSCRIPTEN)
            # todo: Just use generator-expression when CMake minimum version is 3.0
            if (CMAKE_VERSION VERSION_LESS 3.0)
                get_target_property (LOCATION ${TARGET_NAME} LOCATION)
                get_filename_component (LOCATION ${LOCATION} DIRECTORY)
            else ()
                set (LOCATION $<TARGET_FILE_DIR:${TARGET_NAME}>)
            endif ()
            unset (FILES)
            foreach (EXT data html html.map html.mem js)
                list (APPEND FILES ${LOCATION}/${TARGET_NAME}.${EXT})
            endforeach ()
            install (FILES ${FILES} DESTINATION ${DEST_BUNDLE_DIR} OPTIONAL)    # We get html.map or html.mem depend on the build configuration
        else ()
            install (TARGETS ${TARGET_NAME} RUNTIME DESTINATION ${DEST_RUNTIME_DIR} BUNDLE DESTINATION ${DEST_BUNDLE_DIR})
            if (WIN32 AND NOT ARG_NODEPS AND URHO3D_LIB_TYPE STREQUAL SHARED AND NOT URHO3D_DLL_INSTALLED)
                if (TARGET Urho3D)
                    if (CMAKE_VERSION VERSION_LESS 3.0)
                        get_target_property (LOCATION Urho3D LOCATION)
                        get_filename_component (LOCATION ${LOCATION} PATH)
                        if (CMAKE_GENERATOR MATCHES 2008)
                            string (REPLACE /$(OutDir) "" LOCATION ${LOCATION})
                        elseif (MSVC)
                            string (REPLACE /$(Configuration) "" LOCATION ${LOCATION})
                        endif ()
                        install (FILES ${LOCATION}/Urho3D.dll ${LOCATION}/Urho3D_d.dll DESTINATION ${DEST_RUNTIME_DIR} OPTIONAL)
                    else ()
                        install (FILES $<TARGET_FILE:Urho3D> DESTINATION ${DEST_RUNTIME_DIR})
                    endif ()
                else ()
                    install (FILES ${URHO3D_DLL} DESTINATION ${DEST_RUNTIME_DIR})
                endif ()
                set (URHO3D_DLL_INSTALLED TRUE)
            endif ()
            if (DIRECT3D_DLL AND NOT DIRECT3D_DLL_INSTALLED)
                # Make a copy of the D3D DLL to the runtime directory in the installed location
                install (FILES ${DIRECT3D_DLL} DESTINATION ${DEST_RUNTIME_DIR})
                set (DIRECT3D_DLL_INSTALLED TRUE)
            endif ()
        endif ()
    endif ()
endmacro ()

# Macro for setting up linker flags for Mac OS X desktop build
macro (setup_macosx_linker_flags LINKER_FLAGS)
    set (${LINKER_FLAGS} "${${LINKER_FLAGS}} -framework AudioUnit -framework Carbon -framework Cocoa -framework CoreAudio -framework ForceFeedback -framework IOKit -framework OpenGL -framework CoreServices")
endmacro ()

# Macro for setting up linker flags for IOS build
macro (setup_ios_linker_flags LINKER_FLAGS)
    set (${LINKER_FLAGS} "${${LINKER_FLAGS}} -framework AudioToolbox -framework CoreAudio -framework CoreGraphics -framework Foundation -framework OpenGLES -framework QuartzCore -framework UIKit")
endmacro ()

# Macro for setting up linker flags for Emscripten build
macro (setup_emscripten_linker_flags LINKER_FLAGS)
    if (EMSCRIPTEN_ALLOW_MEMORY_GROWTH)
        set (MEMORY_LINKER_FLAGS "-s ALLOW_MEMORY_GROWTH=1")
    else ()
        set (MEMORY_LINKER_FLAGS "-s TOTAL_MEMORY=${EMSCRIPTEN_TOTAL_MEMORY}")
    endif ()
    set (${LINKER_FLAGS} "${${LINKER_FLAGS}} ${MEMORY_LINKER_FLAGS} -s USE_SDL=2 -s NO_EXIT_RUNTIME=1 -s ERROR_ON_UNDEFINED_SYMBOLS=1")
    set (${LINKER_FLAGS}_RELEASE "${${LINKER_FLAGS}_RELEASE} -O3 -s AGGRESSIVE_VARIABLE_ELIMINATION=1")     # Remove variables to make the -O3 regalloc easier
    set (${LINKER_FLAGS}_DEBUG "${${LINKER_FLAGS}_DEBUG} -g4")     # Preserve LLVM debug information, show line number debug comments, and generate source maps
    if (URHO3D_TESTING)
        set (${LINKER_FLAGS} "${${LINKER_FLAGS}} --emrun")  # Inject code into the generated Module object to enable capture of stdout, stderr and exit()
    endif ()
    # Pass additional source files to linker with the supported flags, such as: js-library, pre-js, post-js, embed-file, preload-file, shell-file
    foreach (FILE ${SOURCE_FILES})
        get_property (EMCC_OPTION SOURCE ${FILE} PROPERTY EMCC_OPTION)
        if (EMCC_OPTION)
            list (APPEND LINK_DEPENDS ${FILE})
            unset (EMCC_FILE_ALIAS)
            unset (EMCC_EXCLUDE_FILE)
            if (EMCC_OPTION STREQUAL embed-file OR EMCC_OPTION STREQUAL preload-file)
                get_property (EMCC_FILE_ALIAS SOURCE ${FILE} PROPERTY EMCC_FILE_ALIAS)
                get_property (EMCC_EXCLUDE_FILE SOURCE ${FILE} PROPERTY EMCC_EXCLUDE_FILE)
                if (EMCC_EXCLUDE_FILE)
                    set (EMCC_EXCLUDE_FILE " --exclude-file ${EMCC_EXCLUDE_FILE}")
                endif ()
            endif ()
            set (${LINKER_FLAGS} "${${LINKER_FLAGS}} --${EMCC_OPTION} ${FILE}${EMCC_FILE_ALIAS}${EMCC_EXCLUDE_FILE}")
        endif ()
    endforeach ()
endmacro ()

# Macro for finding file in Urho3D build tree or Urho3D SDK
macro (find_Urho3D_file VAR NAME)
    # Parse extra arguments
    cmake_parse_arguments (ARG "" "DOC;MSG_MODE" "HINTS;PATHS;PATH_SUFFIXES" ${ARGN})
    # Pass the arguments to the actual find command
    find_file (${VAR} ${NAME} HINTS ${ARG_HINTS} PATHS ${ARG_PATHS} PATH_SUFFIXES ${ARG_PATH_SUFFIXES} DOC ${ARG_DOC} NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
    mark_as_advanced (${VAR})  # Hide it from cmake-gui in non-advanced mode
    if (NOT ${VAR} AND ARG_MSG_MODE)
        message (${ARG_MSG_MODE}
            "Could not find ${VAR} file in the Urho3D build tree or Urho3D SDK. "
            "Please reconfigure and rebuild your Urho3D build tree or reinstall the SDK for the correct target platform.")
    endif ()
endmacro ()

# Macro for finding tool in Urho3D build tree or Urho3D SDK
macro (find_Urho3D_tool VAR NAME)
    # Parse extra arguments
    cmake_parse_arguments (ARG "" "DOC;MSG_MODE" "HINTS;PATHS;PATH_SUFFIXES" ${ARGN})
    # Pass the arguments to the actual find command
    find_program (${VAR} ${NAME} HINTS ${ARG_HINTS} PATHS ${ARG_PATHS} PATH_SUFFIXES ${ARG_PATH_SUFFIXES} DOC ${ARG_DOC} NO_DEFAULT_PATH)
    mark_as_advanced (${VAR})  # Hide it from cmake-gui in non-advanced mode
    if (NOT ${VAR})
        set (${VAR} ${CMAKE_BINARY_DIR}/bin/tool/${NAME})
        if (ARG_MSG_MODE AND NOT CMAKE_PROJECT_NAME STREQUAL Urho3D)
            message (${ARG_MSG_MODE}
                "Could not find ${VAR} tool in the Urho3D build tree or Urho3D SDK. Your project may not build successfully without this tool. "
                "You may have to first rebuild the Urho3D in its build tree or reinstall Urho3D SDK to get this tool built or installed properly. "
                "Alternatively, copy the ${VAR} executable manually into bin/tool subdirectory in your own project build tree.")
        endif ()
    endif ()
endmacro ()

# Macro for setting up an executable target with resources to copy/package/bundle/preload
# Macro arguments:
#  NODEPS - setup executable target without defining Urho3D dependency libraries
#  NOBUNDLE - do not use MACOSX_BUNDLE even when URHO3D_MACOSX_BUNDLE build option is enabled
#  WIN32/MACOSX_BUNDLE/EXCLUDE_FROM_ALL - see CMake help on add_executable() command
# CMake variables:
#  RESOURCE_DIRS - list of resource directories (will be packaged into *.pak when URHO3D_PACKAGING build option is set)
#  RESOURCE_FILES - list of additional resource files (will not be packaged into *.pak in any case)
#  SOURCE_FILES - list of source files
#  INCLUDE_DIRS - list of directories for include search path
#  LIBS - list of dependent libraries that are built internally in the project
#  ABSOLUTE_PATH_LIBS - list of dependent libraries that are external to the project
#  LINK_DEPENDS - list of additional files on which a target binary depends for linking (Makefile-based generator only)
#  TARGET_PROPERTIES - list of target properties
macro (setup_main_executable)
    # Parse extra arguments
    cmake_parse_arguments (ARG "NOBUNDLE;MACOSX_BUNDLE;WIN32" "" "" ${ARGN})

    # Define resources
    if (NOT RESOURCE_DIRS)
        # If the macro caller has not defined the resource dirs then set them based on Urho3D project convention
        foreach (DIR ${CMAKE_SOURCE_DIR}/bin/CoreData ${CMAKE_SOURCE_DIR}/bin/Data)
            # Do not assume downstream project always follows Urho3D project convention, so double check if this directory exists before using it
            if (IS_DIRECTORY ${DIR})
                list (APPEND RESOURCE_DIRS ${DIR})
            endif ()
        endforeach ()
    endif ()
    if (URHO3D_PACKAGING AND RESOURCE_DIRS)
        # Populate all the variables required by resource packaging
        foreach (DIR ${RESOURCE_DIRS})
            get_filename_component (NAME ${DIR} NAME)
            set (RESOURCE_${DIR}_PATHNAME ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${NAME}.pak)
            list (APPEND RESOURCE_PAKS ${RESOURCE_${DIR}_PATHNAME})
            if (EMSCRIPTEN AND NOT EMSCRIPTEN_SHARE_DATA)
                # Set the custom EMCC_OPTION property to preload the *.pak individually
                set_source_files_properties (${RESOURCE_${DIR}_PATHNAME} PROPERTIES EMCC_OPTION preload-file EMCC_FILE_ALIAS "@/${NAME}.pak --use-preload-cache")
            endif ()
        endforeach ()
        # Urho3D project builds the PackageTool as required; downstream project uses PackageTool found in the Urho3D build tree or Urho3D SDK
        find_Urho3d_tool (PACKAGE_TOOL PackageTool
            HINTS ${CMAKE_BINARY_DIR}/bin/tool ${URHO3D_HOME}/bin/tool
            DOC "Path to PackageTool" MSG_MODE WARNING)
        if (CMAKE_PROJECT_NAME STREQUAL Urho3D)
            set (PACKAGING_DEP DEPENDS PackageTool)
        endif ()
        set (PACKAGING_COMMENT " and packaging")
        set_property (SOURCE ${RESOURCE_PAKS} PROPERTY GENERATED TRUE)
        if (EMSCRIPTEN)
            # Check if shell-file is already added in source files list by downstream project
            if (NOT CMAKE_PROJECT_NAME STREQUAL Urho3D)
                foreach (FILE ${SOURCE_FILES})
                    get_property (EMCC_OPTION SOURCE ${FILE} PROPERTY EMCC_OPTION)
                    if (EMCC_OPTION STREQUAL shell-file)
                        set (SHELL_HTML_FOUND TRUE)
                        break ()
                    endif ()
                endforeach ()
            endif ()
            if (NOT SHELL_HTML_FOUND)
                # Use custom Urho3D shell.html
                set (SHELL_HTML ${CMAKE_BINARY_DIR}/Source/shell.html)
                list (APPEND SOURCE_FILES ${SHELL_HTML})
                set_source_files_properties (${SHELL_HTML} PROPERTIES EMCC_OPTION shell-file)
            endif ()
            # Set the custom EMCC_OPTION property to peload the generated shared data file
            if (EMSCRIPTEN_SHARE_DATA)
                set (SHARED_RESOURCE_JS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.js)
                list (APPEND SOURCE_FILES ${SHARED_RESOURCE_JS} ${SHARED_RESOURCE_JS}.data)
                set_source_files_properties (${SHARED_RESOURCE_JS} PROPERTIES GENERATED TRUE EMCC_OPTION pre-js)
                # Need to check if the destination variable is defined first because this macro could be called by downstream project that does not wish to install anything
                if (DEST_BUNDLE_DIR)
                    install (FILES ${SHARED_RESOURCE_JS} ${SHARED_RESOURCE_JS}.data DESTINATION ${DEST_BUNDLE_DIR})
                endif ()
            endif ()
        endif ()
    endif ()
    if (XCODE)
        if (NOT RESOURCE_FILES)
            # Default app bundle icon
            set (RESOURCE_FILES ${CMAKE_SOURCE_DIR}/bin/Data/Textures/UrhoIcon.icns)
            if (IOS)
                # Default app icon on the iOS home screen
                list (APPEND RESOURCE_FILES ${CMAKE_SOURCE_DIR}/bin/Data/Textures/UrhoIcon.png)
            endif ()
        endif ()
        # Group them together under 'Resources' in Xcode IDE
        source_group (Resources FILES ${RESOURCE_DIRS} ${RESOURCE_PAKS} ${RESOURCE_FILES})
        # But only use either paks or dirs
        if (RESOURCE_PAKS)
            set_source_files_properties (${RESOURCE_PAKS} ${RESOURCE_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
        else ()
            set_source_files_properties (${RESOURCE_DIRS} ${RESOURCE_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
        endif ()
    endif ()
    list (APPEND SOURCE_FILES ${RESOURCE_DIRS} ${RESOURCE_PAKS} ${RESOURCE_FILES})

    if (ANDROID)
        # todo: Fix this later - Android build tree has a hard-coded resource dirs symlinks
        if (URHO3D_PACKAGING)
            message (WARNING "Resource packaging is not fully supported for Android build currently.")
        endif ()
        # Add SDL native init function, SDL_Main() entry point must be defined by one of the source files in ${SOURCE_FILES}
        find_Urho3D_file (ANDROID_MAIN_C_PATH SDL_android_main.c
            HINTS ${URHO3D_HOME}/include/Urho3D/ThirdParty/SDL/android ${CMAKE_SOURCE_DIR}/Source/ThirdParty/SDL/src/main/android
            DOC "Path to SDL_android_main.c" MSG_MODE FATAL_ERROR)
        list (APPEND SOURCE_FILES ${ANDROID_MAIN_C_PATH})
        # Setup shared library output path
        set_output_directories (${ANDROID_LIBRARY_OUTPUT_PATH} LIBRARY)
        # Setup target as main shared library
        define_dependency_libs (Urho3D)
        setup_library (SHARED)
        if (DEST_LIBRARY_DIR)
            install (TARGETS ${TARGET_NAME} LIBRARY DESTINATION ${DEST_LIBRARY_DIR} ARCHIVE DESTINATION ${DEST_LIBRARY_DIR})
        endif ()
        # Copy other dependent shared libraries to Android library output path
        foreach (FILE ${ABSOLUTE_PATH_LIBS})
            get_filename_component (EXT ${FILE} EXT)
            if (EXT STREQUAL .so)
                get_filename_component (NAME ${FILE} NAME)
                add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${FILE} ${ANDROID_LIBRARY_OUTPUT_PATH}
                    COMMENT "Copying ${NAME} to library output directory")
            endif ()
        endforeach ()
        if (ANDROID_NDK_GDB)
            # Copy the library while it still has debug symbols for ndk-gdb
            add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${TARGET_NAME}> ${NDK_GDB_SOLIB_PATH}
                COMMENT "Copying lib${TARGET_NAME}.so with debug symbols to ${NDK_GDB_SOLIB_PATH} directory")
        endif ()
        # Strip target main shared library
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${TARGET_NAME}>
            COMMENT "Stripping lib${TARGET_NAME}.so in library output directory")
        # When performing packaging, include the final apk file
        if (CMAKE_PROJECT_NAME STREQUAL Urho3D AND NOT APK_INCLUDED)
            install (FILES ${LIBRARY_OUTPUT_PATH_ROOT}/bin/Urho3D-debug.apk DESTINATION ${DEST_RUNTIME_DIR} OPTIONAL)
            set (APK_INCLUDED 1)
        endif ()
    else ()
        # Setup target as executable
        if (WIN32)
            if (NOT URHO3D_WIN32_CONSOLE OR ARG_WIN32)
                set (EXE_TYPE WIN32)
            endif ()
            list (APPEND TARGET_PROPERTIES DEBUG_POSTFIX _d)
        elseif (IOS)
            set (EXE_TYPE MACOSX_BUNDLE)
            list (APPEND TARGET_PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY 1,2 MACOSX_BUNDLE_INFO_PLIST iOSBundleInfo.plist.template)
            setup_ios_linker_flags (CMAKE_EXE_LINKER_FLAGS)
        elseif (APPLE)
            if ((URHO3D_MACOSX_BUNDLE OR ARG_MACOSX_BUNDLE) AND NOT ARG_NOBUNDLE)
                set (EXE_TYPE MACOSX_BUNDLE)
                list (APPEND TARGET_PROPERTIES MACOSX_BUNDLE_INFO_PLIST MacOSXBundleInfo.plist.template)
            endif ()
            setup_macosx_linker_flags (CMAKE_EXE_LINKER_FLAGS)
        elseif (EMSCRIPTEN)
            setup_emscripten_linker_flags (CMAKE_EXE_LINKER_FLAGS)
        endif ()
        setup_executable (${EXE_TYPE} ${ARG_UNPARSED_ARGUMENTS})
    endif ()

    # Define a custom target for resource modification checking and resource packaging (if enabled)
    if ((EXE_TYPE STREQUAL MACOSX_BUNDLE OR URHO3D_PACKAGING) AND RESOURCE_DIRS)
        # Share a same custom target that checks for a same resource dirs list
        foreach (DIR ${RESOURCE_DIRS})
            string (MD5 MD5 ${DIR})
            set (MD5ALL ${MD5ALL}${MD5})
            if (CMAKE_HOST_WIN32)
                # On Windows host, always assumes there are changes so resource dirs would be repackaged in each build, however, still make sure the *.pak timestamp is not altered unnecessarily
                if (URHO3D_PACKAGING)
                    set (PACKAGING_COMMAND && echo Packaging ${DIR}... && ${PACKAGE_TOOL} ${DIR} ${RESOURCE_${DIR}_PATHNAME}.new -c -q && ${CMAKE_COMMAND} -E copy_if_different ${RESOURCE_${DIR}_PATHNAME}.new ${RESOURCE_${DIR}_PATHNAME} && ${CMAKE_COMMAND} -E remove ${RESOURCE_${DIR}_PATHNAME}.new)
                endif ()
                list (APPEND COMMANDS COMMAND ${CMAKE_COMMAND} -E touch ${DIR} ${PACKAGING_COMMAND})
            else ()
                # On Unix-like hosts, detect the changes in the resource directory recursively so they are only repackaged and/or rebundled (Xcode only) as necessary
                if (URHO3D_PACKAGING)
                    set (PACKAGING_COMMAND && echo Packaging ${DIR}... && ${PACKAGE_TOOL} ${DIR} ${RESOURCE_${DIR}_PATHNAME} -c -q)
                    set (OUTPUT_COMMAND test -e ${RESOURCE_${DIR}_PATHNAME} || \( true ${PACKAGING_COMMAND} \))
                else ()
                    set (OUTPUT_COMMAND true)   # Nothing to output
                endif ()
                list (APPEND COMMANDS COMMAND echo Checking ${DIR}... && bash -c \"\(\( `find ${DIR} -newer ${DIR} |wc -l` \)\)\" && touch -cm ${DIR} ${PACKAGING_COMMAND} || ${OUTPUT_COMMAND})
            endif ()
        endforeach ()
        string (MD5 MD5ALL ${MD5ALL})
        # Ensure the resource check is done before building the main executable target
        if (NOT RESOURCE_CHECK_${MD5ALL})
            set (RESOURCE_CHECK RESOURCE_CHECK)
            while (TARGET ${RESOURCE_CHECK})
                string (RANDOM RANDOM)
                set (RESOURCE_CHECK RESOURCE_CHECK_${RANDOM})
            endwhile ()
            set (RESOURCE_CHECK_${MD5ALL} ${RESOURCE_CHECK} CACHE INTERNAL "Resource check hash map")
        endif ()
        if (NOT TARGET ${RESOURCE_CHECK_${MD5ALL}})
            add_custom_target (${RESOURCE_CHECK_${MD5ALL}} ALL ${COMMANDS} ${PACKAGING_DEP} COMMENT "Checking${PACKAGING_COMMENT} resource directories")
        endif ()
        add_dependencies (${TARGET_NAME} ${RESOURCE_CHECK_${MD5ALL}})
    endif ()

    # Define a custom command for generating a shared data file (if enabled)
    if (EMSCRIPTEN_SHARE_DATA AND RESOURCE_PAKS)
        # When sharing a single data file, all main targets are assumed to use a same set of resource paks
        foreach (FILE ${RESOURCE_PAKS})
            get_filename_component (NAME ${FILE} NAME)
            list (APPEND PAK_NAMES ${NAME})
        endforeach ()
        if (CMAKE_BUILD_TYPE STREQUAL Debug AND EMCC_VERSION VERSION_GREATER 1.32.2)
            set (SEPARATE_METADATA --separate-metadata)
        endif ()
        add_custom_command (OUTPUT ${SHARED_RESOURCE_JS}.data
            COMMAND ${EMPACKAGER} ${SHARED_RESOURCE_JS}.data --preload ${PAK_NAMES} --js-output=${SHARED_RESOURCE_JS} --use-preload-cache ${SEPARATE_METADATA}
            DEPENDS RESOURCE_CHECK ${RESOURCE_PAKS}
            WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            COMMENT "Generating shared data file")
    endif ()
endmacro ()

# Macro for adjusting target output name by dropping _suffix from the target name
macro (adjust_target_name)
    if (TARGET_NAME MATCHES _.*$)
        string (REGEX REPLACE _.*$ "" OUTPUT_NAME ${TARGET_NAME})
        set_target_properties (${TARGET_NAME} PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})
    endif ()
endmacro ()

# Macro for setting up a test case
macro (setup_test)
    if (URHO3D_TESTING)
        cmake_parse_arguments (ARG "" "NAME" "OPTIONS" ${ARGN})
        if (NOT ARG_NAME)
            set (ARG_NAME ${TARGET_NAME})
        endif ()
        list (APPEND ARG_OPTIONS -timeout ${URHO3D_TEST_TIMEOUT})
        if (EMSCRIPTEN)
            if (DEFINED ENV{CI})
                # The latency on CI server could be very high at time, so add some adjustment
                # If it is not enough causing a test case failure then so be it because it is better that than wait for it and still ends up in build error due to time limit
                set (EMRUN_TIMEOUT_ADJUSTMENT + 8 * \\${URHO3D_TEST_TIMEOUT})
                set (EMRUN_TIMEOUT_RETURNCODE --timeout_returncode 0)
            endif ()
            math (EXPR EMRUN_TIMEOUT "2 * ${URHO3D_TEST_TIMEOUT} ${EMRUN_TIMEOUT_ADJUSTMENT}")
            add_test (NAME ${ARG_NAME} COMMAND ${EMRUN} --browser ${EMSCRIPTEN_EMRUN_BROWSER} --timeout ${EMRUN_TIMEOUT} ${EMRUN_TIMEOUT_RETURNCODE} --kill_exit ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}.html ${ARG_OPTIONS})
        else ()
            add_test (NAME ${ARG_NAME} COMMAND ${TARGET_NAME} ${ARG_OPTIONS})
        endif ()
    endif ()
endmacro ()

# Macro for defining external library dependencies
# The purpose of this macro is emulate CMake to set the external library dependencies transitively
# It works for both targets setup within Urho3D project and downstream projects that uses Urho3D as external static/shared library
macro (define_dependency_libs TARGET)
    # ThirdParty/SDL external dependency
    if (${TARGET} MATCHES SDL|Urho3D)
        if (WIN32)
            list (APPEND LIBS user32 gdi32 winmm imm32 ole32 oleaut32 version uuid)
        elseif (APPLE)
            list (APPEND LIBS dl)
        elseif (ANDROID)
            list (APPEND LIBS dl log android)
        else ()
            # Linux
            if (NOT EMSCRIPTEN)
                list (APPEND LIBS dl rt)
            endif ()
            if (RPI)
                list (APPEND ABSOLUTE_PATH_LIBS ${BCM_VC_LIBRARIES})
            endif ()
        endif ()
    endif ()

    # ThirdParty/kNet & ThirdParty/Civetweb external dependency
    if (${TARGET} MATCHES Civetweb|kNet|Urho3D)
        if (WIN32)
            list (APPEND LIBS ws2_32)
        endif ()
    endif ()

    # Urho3D/LuaJIT external dependency
    if (URHO3D_LUAJIT AND ${TARGET} MATCHES LuaJIT|Urho3D)
        if (NOT WIN32 AND NOT EMSCRIPTEN)
            list (APPEND LIBS dl m)
        endif ()
    endif ()

    # Urho3D external dependency
    if (${TARGET} STREQUAL Urho3D)
        # Core
        if (WIN32)
            list (APPEND LIBS winmm)
            if (URHO3D_MINIDUMPS)
                list (APPEND LIBS dbghelp)
            endif ()
        endif ()

        # Graphics
        if (URHO3D_OPENGL)
            if (WIN32)
                list (APPEND LIBS opengl32)
            elseif (ANDROID)
                list (APPEND LIBS GLESv1_CM GLESv2)
            elseif (NOT APPLE AND NOT RPI)
                list (APPEND LIBS GL)
            endif ()
        elseif (DIRECT3D_LIBRARIES)
            # Check if the libs are using absolute path
            list (GET DIRECT3D_LIBRARIES 0 FIRST_LIB)
            if (IS_ABSOLUTE ${FIRST_LIB})
                list (APPEND ABSOLUTE_PATH_LIBS ${DIRECT3D_LIBRARIES})
            else ()
                # Assume the libraries are found from default directories
                list (APPEND LIBS ${DIRECT3D_LIBRARIES})
            endif ()
        endif ()

        # Database
        if (URHO3D_DATABASE_ODBC)
            list (APPEND LIBS ${ODBC_LIBRARIES})
        endif ()

        # This variable value can either be 'Urho3D' target or an absolute path to an actual static/shared Urho3D library or empty (if we are building the library itself)
        # The former would cause CMake not only to link against the Urho3D library but also to add a dependency to Urho3D target
        if (URHO3D_LIBRARIES)
            if (WIN32 AND URHO3D_LIBRARIES_DBG AND URHO3D_LIBRARIES_REL AND TARGET ${TARGET_NAME})
                # Special handling when both debug and release libraries are found
                target_link_libraries (${TARGET_NAME} debug ${URHO3D_LIBRARIES_DBG} optimized ${URHO3D_LIBRARIES_REL})
            else ()
                list (APPEND ABSOLUTE_PATH_LIBS ${URHO3D_LIBRARIES})
            endif ()
        endif ()
    endif ()

    # LuaJIT specific - extra linker flags for linking against LuaJIT (adapted from LuaJIT's original Makefile)
    if (URHO3D_LUAJIT AND ${TARGET} MATCHES Urho3D)
        # 64-bit Mac OS X
        if (URHO3D_64BIT AND APPLE AND NOT IOS)
            set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pagezero_size 10000 -image_base 100000000")
        endif ()
        # GCC-specific
        if (NOT WIN32 AND NOT APPLE AND NOT ANDROID)
            set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-E")
        endif ()
    endif ()
endmacro ()

# Macro for sorting and removing duplicate values
macro (remove_duplicate LIST_NAME)
    if (${LIST_NAME})
        list (SORT ${LIST_NAME})
        list (REMOVE_DUPLICATES ${LIST_NAME})
    endif ()
endmacro ()

# Macro for setting a list from another with option to sort and remove duplicate values
macro (set_list TO_LIST FROM_LIST)
    set (${TO_LIST} ${${FROM_LIST}})
    if (${ARGN} STREQUAL REMOVE_DUPLICATE)
        remove_duplicate (${TO_LIST})
    endif ()
endmacro ()

# Macro for defining source files with optional arguments as follows:
#  GLOB_CPP_PATTERNS <list> - Use the provided globbing patterns for CPP_FILES instead of the default *.cpp
#  GLOB_H_PATTERNS <list> - Use the provided globbing patterns for H_FILES instead of the default *.h
#  EXCLUDE_PATTERNS <list> - Use the provided patterns for excluding matched source files
#  EXTRA_CPP_FILES <list> - Include the provided list of files into CPP_FILES result
#  EXTRA_H_FILES <list> - Include the provided list of files into H_FILES result
#  PCH <list> - Enable precompiled header support on the defined source files using the specified header file, the list is "<path/to/header> [C++|C]"
#  PARENT_SCOPE - Glob source files in current directory but set the result in parent-scope's variable ${DIR}_CPP_FILES and ${DIR}_H_FILES instead
#  RECURSE - Option to glob recursively
#  GROUP - Option to group source files based on its relative path to the corresponding parent directory (only works when PARENT_SCOPE option is not in use)
macro (define_source_files)
    # Parse the arguments
    cmake_parse_arguments (ARG "PARENT_SCOPE;RECURSE;GROUP" "" "PCH;EXTRA_CPP_FILES;EXTRA_H_FILES;GLOB_CPP_PATTERNS;GLOB_H_PATTERNS;EXCLUDE_PATTERNS" ${ARGN})

    # Source files are defined by globbing source files in current source directory and also by including the extra source files if provided
    if (NOT ARG_GLOB_CPP_PATTERNS)
        set (ARG_GLOB_CPP_PATTERNS *.cpp)    # Default glob pattern
    endif ()
    if (NOT ARG_GLOB_H_PATTERNS)
        set (ARG_GLOB_H_PATTERNS *.h)
    endif ()
    if (ARG_RECURSE)
        set (ARG_RECURSE _RECURSE)
    else ()
        unset (ARG_RECURSE)
    endif ()
    file (GLOB${ARG_RECURSE} CPP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${ARG_GLOB_CPP_PATTERNS})
    file (GLOB${ARG_RECURSE} H_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${ARG_GLOB_H_PATTERNS})
    if (ARG_EXCLUDE_PATTERNS)
        set (CPP_FILES_WITH_SENTINEL ";${CPP_FILES};")  # Stringify the lists
        set (H_FILES_WITH_SENTINEL ";${H_FILES};")
        foreach (PATTERN ${ARG_EXCLUDE_PATTERNS})
            foreach (LOOP RANGE 1)
                string (REGEX REPLACE ";${PATTERN};" ";;" CPP_FILES_WITH_SENTINEL "${CPP_FILES_WITH_SENTINEL}")
                string (REGEX REPLACE ";${PATTERN};" ";;" H_FILES_WITH_SENTINEL "${H_FILES_WITH_SENTINEL}")
            endforeach ()
        endforeach ()
        set (CPP_FILES ${CPP_FILES_WITH_SENTINEL})      # Convert strings back to lists, extra sentinels are harmless
        set (H_FILES ${H_FILES_WITH_SENTINEL})
    endif ()
    list (APPEND CPP_FILES ${ARG_EXTRA_CPP_FILES})
    list (APPEND H_FILES ${ARG_EXTRA_H_FILES})
    set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

    # Optionally enable PCH
    if (ARG_PCH)
        enable_pch (${ARG_PCH})
    endif ()

    # Optionally accumulate source files at parent scope
    if (ARG_PARENT_SCOPE)
        get_filename_component (NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
        set (${NAME}_CPP_FILES ${CPP_FILES} PARENT_SCOPE)
        set (${NAME}_H_FILES ${H_FILES} PARENT_SCOPE)
    # Optionally put source files into further sub-group (only works when PARENT_SCOPE option is not in use)
    elseif (ARG_GROUP)
        foreach (CPP_FILE ${CPP_FILES})
            get_filename_component (PATH ${CPP_FILE} PATH)
            if (PATH)
                string (REPLACE / \\ PATH ${PATH})
                source_group ("Source Files\\${PATH}" FILES ${CPP_FILE})
            endif ()
        endforeach ()
        foreach (H_FILE ${H_FILES})
            get_filename_component (PATH ${H_FILE} PATH)
            if (PATH)
                string (REPLACE / \\ PATH ${PATH})
                source_group ("Header Files\\${PATH}" FILES ${H_FILE})
            endif ()
        endforeach ()
    endif ()
endmacro ()

# Macro for setting up header files installation for the SDK and the build tree (only support subset of install command arguments)
#  FILES <list> - File list to be installed
#  DIRECTORY <list> - Directory list to be installed
#  FILES_MATCHING - Option to perform file pattern matching on DIRECTORY list
#  USE_FILE_SYMLINK - Option to use file symlinks on the matched files found in the DIRECTORY list
#  BUILD_TREE_ONLY - Option to install the header files into the build tree only
#  PATTERN <list> - Pattern list to be used in file pattern matching option
#  BASE <value> - An absolute base path to be prepended to the destination path when installing to build tree, default to build tree
#  DESTINATION <value> - A relative destination path to be installed to
macro (install_header_files)
    # Need to check if the destination variable is defined first because this macro could be called by downstream project that does not wish to install anything
    if (DEST_INCLUDE_DIR)
        # Parse the arguments for the underlying install command for the SDK
        cmake_parse_arguments (ARG "FILES_MATCHING;USE_FILE_SYMLINK;BUILD_TREE_ONLY" "BASE;DESTINATION" "FILES;DIRECTORY;PATTERN" ${ARGN})
        unset (INSTALL_MATCHING)
        if (ARG_FILES)
            set (INSTALL_TYPE FILES)
            set (INSTALL_SOURCES ${ARG_FILES})
        elseif (ARG_DIRECTORY)
            set (INSTALL_TYPE DIRECTORY)
            set (INSTALL_SOURCES ${ARG_DIRECTORY})
            if (ARG_FILES_MATCHING)
                set (INSTALL_MATCHING FILES_MATCHING)
                # Our macro supports PATTERN <list> but CMake's install command does not, so convert the list to: PATTERN <value1> PATTERN <value2> ...
                foreach (PATTERN ${ARG_PATTERN})
                    list (APPEND INSTALL_MATCHING PATTERN ${PATTERN})
                endforeach ()
            endif ()
        else ()
            message (FATAL_ERROR "Couldn't setup install command because the install type is not specified.")
        endif ()
        if (NOT ARG_DESTINATION)
            message (FATAL_ERROR "Couldn't setup install command because the install destination is not specified.")
        endif ()
        if (NOT ARG_BUILD_TREE_ONLY AND NOT CMAKE_PROJECT_NAME MATCHES ^ExternalProject-)
            install (${INSTALL_TYPE} ${INSTALL_SOURCES} DESTINATION ${ARG_DESTINATION} ${INSTALL_MATCHING})
        endif ()

        # Reparse the arguments for the create_symlink macro to "install" the header files in the build tree
        if (NOT ARG_BASE)
            set (ARG_BASE ${CMAKE_BINARY_DIR})  # Use build tree as base path
        endif ()
        foreach (INSTALL_SOURCE ${INSTALL_SOURCES})
            if (NOT IS_ABSOLUTE ${INSTALL_SOURCE})
                set (INSTALL_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/${INSTALL_SOURCE})
            endif ()
            if (INSTALL_SOURCE MATCHES /$)
                # Source is a directory
                if (ARG_USE_FILE_SYMLINK)
                    # Use file symlink for each individual files in the source directory
                    set (GLOBBING_EXPRESSION RELATIVE ${INSTALL_SOURCE})
                    if (ARG_FILES_MATCHING)
                        foreach (PATTERN ${ARG_PATTERN})
                            list (APPEND GLOBBING_EXPRESSION ${INSTALL_SOURCE}${PATTERN})
                        endforeach ()
                    else ()
                        list (APPEND GLOBBING_EXPRESSION ${INSTALL_SOURCE}*)
                    endif ()
                    file (GLOB_RECURSE NAMES ${GLOBBING_EXPRESSION})
                    foreach (NAME ${NAMES})
                        get_filename_component (PATH ${ARG_DESTINATION}/${NAME} PATH)
                        # Recreate the source directory structure in the destination path
                        if (NOT EXISTS ${ARG_BASE}/${PATH})
                            file (MAKE_DIRECTORY ${ARG_BASE}/${PATH})
                        endif ()
                        create_symlink (${INSTALL_SOURCE}${NAME} ${ARG_DESTINATION}/${NAME} FALLBACK_TO_COPY)
                    endforeach ()
                else ()
                    # Use a single symlink pointing to the source directory
                    create_symlink (${INSTALL_SOURCE} ${ARG_DESTINATION} FALLBACK_TO_COPY)
                endif ()
            else ()
                # Source is a file (it could also be actually a directory to be treated as a "file", i.e. for creating symlink pointing to the directory)
                get_filename_component (NAME ${INSTALL_SOURCE} NAME)
                create_symlink (${INSTALL_SOURCE} ${ARG_DESTINATION}/${NAME} FALLBACK_TO_COPY)
            endif ()
        endforeach ()
    endif ()
endmacro ()

# Set common project structure for some platforms
if (ANDROID)
    # Enable Android ndk-gdb
    if (ANDROID_NDK_GDB)
        set (NDK_GDB_SOLIB_PATH ${CMAKE_BINARY_DIR}/obj/local/${ANDROID_NDK_ABI_NAME}/)
        file (MAKE_DIRECTORY ${NDK_GDB_SOLIB_PATH})
        set (NDK_GDB_JNI ${CMAKE_BINARY_DIR}/jni)
        set (NDK_GDB_MK "# This is a generated file. DO NOT EDIT!\n\nAPP_ABI := ${ANDROID_NDK_ABI_NAME}\n")
        foreach (MK Android.mk Application.mk)
            if (NOT EXISTS ${NDK_GDB_JNI}/${MK})
                file (WRITE ${NDK_GDB_JNI}/${MK} ${NDK_GDB_MK})
            endif ()
        endforeach ()
        get_directory_property (INCLUDE_DIRECTORIES DIRECTORY ${PROJECT_SOURCE_DIR} INCLUDE_DIRECTORIES)
        string (REPLACE ";" " " INCLUDE_DIRECTORIES "${INCLUDE_DIRECTORIES}")   # Note: need to always "stringify" a variable in list context for replace to work correctly
        set (NDK_GDB_SETUP "# This is a generated file. DO NOT EDIT!\n\nset solib-search-path ${NDK_GDB_SOLIB_PATH}\ndirectory ${INCLUDE_DIRECTORIES}\n")
        file (WRITE ${ANDROID_LIBRARY_OUTPUT_PATH}/gdb.setup ${NDK_GDB_SETUP})
        file (COPY ${ANDROID_NDK}/prebuilt/android-${ANDROID_ARCH_NAME}/gdbserver/gdbserver DESTINATION ${ANDROID_LIBRARY_OUTPUT_PATH})
    else ()
        file (REMOVE ${ANDROID_LIBRARY_OUTPUT_PATH}/gdbserver)
    endif ()
    # Create symbolic links in the build tree
    file (MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/Android/assets)
    foreach (I CoreData Data)
        if (NOT EXISTS ${CMAKE_SOURCE_DIR}/Android/assets/${I})
            create_symlink (${CMAKE_SOURCE_DIR}/bin/${I} ${CMAKE_SOURCE_DIR}/Android/assets/${I} FALLBACK_TO_COPY)
        endif ()
    endforeach ()
    foreach (I AndroidManifest.xml build.xml custom_rules.xml src res assets jni)
        if (EXISTS ${CMAKE_SOURCE_DIR}/Android/${I} AND NOT EXISTS ${CMAKE_BINARY_DIR}/${I})    # No-ops when 'Android' is used as build tree
            create_symlink (${CMAKE_SOURCE_DIR}/Android/${I} ${CMAKE_BINARY_DIR}/${I} FALLBACK_TO_COPY)
        endif ()
    endforeach ()
elseif (EMSCRIPTEN)
    # Create Urho3D custom HTML shell that also embeds our own project logo
    if (NOT EXISTS ${CMAKE_BINARY_DIR}/Source/shell.html)
        file (READ ${EMSCRIPTEN_ROOT_PATH}/src/shell.html SHELL_HTML)
        string (REPLACE "<!doctype html>" "<!-- This is a generated file. DO NOT EDIT!-->\n\n<!doctype html>" SHELL_HTML "${SHELL_HTML}")     # Stringify to preserve semicolons
        string (REPLACE "<body>" "<body>\n\n<a href=\"http://urho3d.github.io\" title=\"Urho3D Homepage\"><img src=\"http://urho3d.github.io/assets/images/logo.png\" alt=\"link to http://urho3d.github.io\" height=\"80\" width=\"320\" /></a>\n" SHELL_HTML "${SHELL_HTML}")
        file (WRITE ${CMAKE_BINARY_DIR}/Source/shell.html "${SHELL_HTML}")
    endif ()
else ()
    # Ensure the output directory exist before creating the symlinks
    file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    # Create symbolic links in the build tree
    foreach (I CoreData Data)
        if (NOT EXISTS ${CMAKE_BINARY_DIR}/bin/${I})
            create_symlink (${CMAKE_SOURCE_DIR}/bin/${I} ${CMAKE_BINARY_DIR}/bin/${I} FALLBACK_TO_COPY)
        endif ()
    endforeach ()
    # Warn user if PATH environment variable has not been correctly set for using ccache
    if (NOT CMAKE_CROSSCOMPILING AND NOT CMAKE_HOST_WIN32 AND "$ENV{USE_CCACHE}")
        if (APPLE)
            set (WHEREIS brew info ccache)
        else ()
            set (WHEREIS whereis -b ccache)
        endif ()
        execute_process (COMMAND ${WHEREIS} COMMAND grep -o \\S*lib\\S* RESULT_VARIABLE EXIT_CODE OUTPUT_VARIABLE CCACHE_SYMLINK ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
        if (EXIT_CODE EQUAL 0 AND NOT $ENV{PATH} MATCHES "${CCACHE_SYMLINK}")  # Need to stringify because CCACHE_SYMLINK variable could be empty when the command failed
            message (WARNING "The lib directory containing the ccache symlinks (${CCACHE_SYMLINK}) has not been added in the PATH environment variable. "
                "This is required to enable ccache support for native compiler toolchain. CMake has been configured to use the actual compiler toolchain instead of ccache. "
                "In order to rectify this, the build tree must be regenerated after the PATH environment variable has been adjusted accordingly.")
        endif ()
    endif ()
endif ()

# Post-CMake fixes
if (IOS)
    # TODO: can be removed when CMake minimum required has reached 2.8.12
    if (CMAKE_VERSION VERSION_LESS 2.8.12)
        # Due to a bug in the CMake/Xcode generator (prior to version 2.8.12) where it has wrongly assumed the IOS bundle structure to be the same as MacOSX bundle structure,
        # below temporary fix is required in order to solve the auto-linking issue when dependent libraries are changed
        list (APPEND POST_CMAKE_FIXES COMMAND sed -i '' 's/\/Contents\/MacOS//g' ${CMAKE_BINARY_DIR}/CMakeScripts/XCODE_DEPEND_HELPER.make || exit 0)
    endif ()

    # Due to a bug in the CMake/Xcode generator (still exists in 3.1) that prevents iOS targets (library and bundle) to be installed correctly
    # (see http://public.kitware.com/Bug/bug_relationship_graph.php?bug_id=12506&graph=dependency),
    # below temporary fix is required to work around the bug
    list (APPEND POST_CMAKE_FIXES COMMAND sed -i '' 's/EFFECTIVE_PLATFORM_NAME//g' ${CMAKE_BINARY_DIR}/CMakeScripts/install_postBuildPhase.make* || exit 0)
endif ()
if (POST_CMAKE_FIXES)
    add_custom_target (POST_CMAKE_FIXES ALL ${POST_CMAKE_FIXES} COMMENT "Applying post-cmake fixes")
endif ()
