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
set (DOC_STRING "Choose the build configuration, possible options are: ${URHO3D_BUILD_CONFIGURATIONS}")
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
cmake_dependent_option (IOS "Setup build for iOS platform" FALSE "XCODE" FALSE)
if (NOT MSVC AND NOT DEFINED URHO3D_DEFAULT_64BIT)  # Only do this once in the initial configure step
    # On non-MSVC compiler, default to build 64-bit when the host system has a 64-bit build environment
    execute_process (COMMAND echo COMMAND ${CMAKE_C_COMPILER} -E -dM - OUTPUT_VARIABLE PREDEFINED_MACROS ERROR_QUIET)
    string (REGEX MATCH "#define +__(x86_64|aarch64)__ +1" matched "${PREDEFINED_MACROS}")
    if (matched)
        set (URHO3D_DEFAULT_64BIT TRUE)
    else ()
        set (URHO3D_DEFAULT_64BIT FALSE)
    endif ()
    set (URHO3D_DEFAULT_64BIT ${URHO3D_DEFAULT_64BIT} CACHE INTERNAL "Default value for URHO3D_64BIT build option")
    # The 'ANDROID' CMake variable is already set by android.toolchain.cmake when it is being used for cross-compiling Android
    # The other arm platform that Urho3D supports that is not Android is Raspberry Pi at the moment
    if (NOT ANDROID)
        string (REGEX MATCH "#define +__arm__ +1" matched "${PREDEFINED_MACROS}")
        if (matched)
            # Set the CMake variable here instead of in raspberrypi.toolchain.cmake because Raspberry Pi can be built natively too on the Raspberry-Pi device itself
            set (RPI TRUE CACHE INTERNAL "Setup build for Raspberry Pi platform")
        endif ()
    endif ()
endif ()
if (ANDROID OR RPI)
    # This build option is not available on Android and Raspberry-Pi platforms as its value is preset by the chosen toolchain in the build tree
    set (URHO3D_64BIT ${URHO3D_DEFAULT_64BIT})
else ()
    option (URHO3D_64BIT "Enable 64-bit build" ${URHO3D_DEFAULT_64BIT})
endif ()
option (URHO3D_ANGELSCRIPT "Enable AngelScript scripting support" TRUE)
option (URHO3D_LUA "Enable additional Lua scripting support")
option (URHO3D_LUAJIT "Enable Lua scripting support using LuaJIT (check LuaJIT's CMakeLists.txt for more options)")
option (URHO3D_NAVIGATION "Enable navigation support" TRUE)
option (URHO3D_NETWORK "Enable networking support" TRUE)
option (URHO3D_PHYSICS "Enable physics support" TRUE)
option (URHO3D_URHO2D "Enable 2D graphics and physics support" TRUE)
if (MINGW AND NOT DEFINED URHO3D_SSE)
    # Certain MinGW versions fail to compile SSE code. This is the initial guess for known "bad" version range, and can be tightened later
    execute_process (COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION ERROR_QUIET)
    if (GCC_VERSION VERSION_LESS 4.9.1)
        message (WARNING "Disabling SSE by default due to MinGW version. It is recommended to upgrade to MinGW with GCC >= 4.9.1. You can also try to re-enable SSE with CMake option -DURHO3D_SSE=1, but this may result in compile errors.")
    else ()
        set (URHO3D_DEFAULT_SSE TRUE)
    endif ()
else ()
    set (URHO3D_DEFAULT_SSE TRUE)
endif ()
option (URHO3D_SSE "Enable SSE instruction set" ${URHO3D_DEFAULT_SSE})
if (CMAKE_PROJECT_NAME STREQUAL Urho3D)
    cmake_dependent_option (URHO3D_LUAJIT_AMALG "Enable LuaJIT amalgamated build (LuaJIT only)" FALSE "URHO3D_LUAJIT" FALSE)
    cmake_dependent_option (URHO3D_SAFE_LUA "Enable Lua C++ wrapper safety checks (Lua scripting only)" FALSE "URHO3D_LUA OR URHO3D_LUAJIT" FALSE)
    option (URHO3D_SAMPLES "Build sample applications")
    cmake_dependent_option (URHO3D_TOOLS "Build tools (native and RPI only)" TRUE "NOT IOS AND NOT ANDROID" FALSE)
    cmake_dependent_option (URHO3D_EXTRAS "Build extras (native and RPI only)" FALSE "NOT IOS AND NOT ANDROID" FALSE)
    option (URHO3D_DOCS "Generate documentation as part of normal build")
    option (URHO3D_DOCS_QUIET "Generate documentation as part of normal build, suppress generation process from sending anything to stdout")
    cmake_dependent_option (URHO3D_MINIDUMPS "Enable minidumps on crash (VS only)" TRUE "MSVC" FALSE)
    option (URHO3D_FILEWATCHER "Enable filewatcher support" TRUE)
    if (CPACK_SYSTEM_NAME STREQUAL Linux)
        cmake_dependent_option (URHO3D_USE_LIB64_RPM "Enable 64-bit RPM CPack generator using /usr/lib64 and disable all other generators (Debian-based host only)" FALSE "URHO3D_64BIT AND NOT HAS_LIB64" FALSE)
        cmake_dependent_option (URHO3D_USE_LIB_DEB "Enable 64-bit DEB CPack generator using /usr/lib and disable all other generators (Redhat-based host only)" FALSE "URHO3D_64BIT AND HAS_LIB64" FALSE)
    endif ()
else ()
    set (URHO3D_HOME "" CACHE PATH "Path to Urho3D build tree or SDK installation location (external project only)")
endif ()
option (URHO3D_PROFILING "Enable profiling support" TRUE)
option (URHO3D_LOGGING "Enable logging support" TRUE)
option (URHO3D_TESTING "Enable testing support")
if (URHO3D_TESTING)
    set (URHO3D_TEST_TIME_OUT 5 CACHE STRING "Number of seconds to test run the executables")
else ()
    unset (URHO3D_TEST_TIME_OUT CACHE)
endif ()
# The URHO3D_OPENGL option is not defined on non-Windows platforms as they should always use OpenGL
if (MSVC)
    # On MSVC compiler, default to false (i.e. prefers Direct3D)
    # OpenGL can be manually enabled with -DURHO3D_OPENGL=1, but Windows graphics card drivers are usually better optimized for Direct3D
    option (URHO3D_OPENGL "Use OpenGL instead of Direct3D (Windows platform only)")
elseif (WIN32)
    # On non-MSVC compiler on Windows platform, default to true to enable use of OpenGL instead of Direct3D
    # Direct3D can be manually enabled with -DURHO3D_OPENGL=0, but it is likely to fail unless the MinGW-w64 distribution is used due to dependency to Direct3D headers and libs
    option (URHO3D_OPENGL "Use OpenGL instead of Direct3D (Windows platform only)" TRUE)
endif ()
if (CMAKE_HOST_WIN32 AND NOT DEFINED URHO3D_MKLINK)
    # Test whether the host system is capable of setting up symbolic link
    execute_process (COMMAND cmd /C mklink test-link CMakeCache.txt RESULT_VARIABLE MKLINK_EXIT_CODE OUTPUT_QUIET ERROR_QUIET)
    if (MKLINK_EXIT_CODE EQUAL 0)
        set (URHO3D_MKLINK TRUE)
        file (REMOVE ${CMAKE_BINARY_DIR}/test-link)
    else ()
        set (URHO3D_MKLINK FALSE)
    endif ()
    set (URHO3D_MKLINK ${URHO3D_MKLINK} CACHE INTERNAL "MKLINK capability on the Windows host system")
endif ()
cmake_dependent_option (URHO3D_STATIC_RUNTIME "Use static C/C++ runtime libraries and eliminate the need for runtime DLLs installation (VS only)" FALSE "MSVC" FALSE)
cmake_dependent_option (URHO3D_WIN32_CONSOLE "Use console main() as entry point when setting up Windows executable targets (Windows platform only)" FALSE "WIN32" FALSE)
cmake_dependent_option (URHO3D_MACOSX_BUNDLE "Use MACOSX_BUNDLE when setting up Mac OS X executable targets (Xcode native build only)" FALSE "XCODE AND NOT IOS" FALSE)
set (URHO3D_LIB_TYPE STATIC CACHE STRING "Specify Urho3D library type, possible values are STATIC (default) and SHARED")
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
endif ()
if (RPI AND CMAKE_CROSSCOMPILING)
    set (RPI_PREFIX "" CACHE STRING "Prefix path to Raspberry Pi cross-compiler tools (RPI cross-compiling build only)")
    set (RPI_SYSROOT "" CACHE PATH "Path to Raspberry Pi system root (RPI cross-compiling build only)")
endif ()
# Constrain the build option values in cmake-gui, if applicable
if (CMAKE_VERSION VERSION_GREATER 2.8 OR CMAKE_VERSION VERSION_EQUAL 2.8)
    set_property (CACHE URHO3D_LIB_TYPE PROPERTY STRINGS STATIC SHARED)
    if (NOT CMAKE_CONFIGURATION_TYPES)
        set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${URHO3D_BUILD_CONFIGURATIONS})
    endif ()
endif()

# Enable testing
if (URHO3D_TESTING)
    enable_testing ()
    add_definitions (-DURHO3D_TESTING)
endif ()

# Enable SSE instruction set. Requires Pentium III or Athlon XP processor at minimum.
if (URHO3D_SSE)
    add_definitions (-DURHO3D_SSE)
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

# If not on Windows platform, enable Unix mode for kNet library and OpenGL graphic back-end
if (NOT WIN32)
    add_definitions (-DKNET_UNIX)
    set (URHO3D_OPENGL 1)
endif ()

# Add definition for OpenGL
if (URHO3D_OPENGL)
    add_definitions (-DURHO3D_OPENGL)
endif ()

# Add definitions for GLEW
if (NOT IOS AND NOT ANDROID AND NOT RPI AND URHO3D_OPENGL)
    add_definitions (-DGLEW_STATIC -DGLEW_NO_GLU)
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

# Default library type is STATIC
if (URHO3D_LIB_TYPE)
    string (TOUPPER ${URHO3D_LIB_TYPE} URHO3D_LIB_TYPE)
endif ()
if (NOT URHO3D_LIB_TYPE STREQUAL SHARED)
    set (URHO3D_LIB_TYPE STATIC)
    add_definitions (-DURHO3D_STATIC_DEFINE)
endif ()

# Find DirectX SDK include & library directories for Visual Studio. It is also possible to compile
# without if a recent Windows SDK is installed. The SDK is not searched for with MinGW as it is
# incompatible; rather, it is assumed that MinGW itself comes with the necessary headers & libraries.
if (WIN32 AND NOT URHO3D_OPENGL)
    find_package (Direct3D)
    if (DIRECT3D_FOUND)
        include_directories (${DIRECT3D_INCLUDE_DIRS})
    endif ()
endif ()

# For Raspbery Pi, find Broadcom VideoCore IV firmware
if (RPI)
    find_package (BCM_VC REQUIRED)
    include_directories (${BCM_VC_INCLUDE_DIRS})
endif ()

# Platform and compiler specific options
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
    # SSE flag is redundant if already compiling as 64bit
    if (URHO3D_SSE AND NOT URHO3D_64BIT)
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /arch:SSE")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE")
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
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -Wno-psabi")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -Wno-psabi")
        else ()
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffast-math")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")
            if (URHO3D_64BIT)
                set (DASH_MBIT -m64)    # This variable is intentionally not defined on Android and RPI platform
            else ()
                set (DASH_MBIT -m32)
                if (URHO3D_SSE)
                    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse")
                    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse")
                endif ()
            endif ()
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DASH_MBIT}")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DASH_MBIT}")
            set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${DASH_MBIT}")
        endif ()
        # MinGW-specific setup
        if (MINGW)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static -static-libgcc -fno-keep-inline-dllexport")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libstdc++ -static-libgcc -fno-keep-inline-dllexport")
            set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static")
            # Additional compiler flags for Windows ports of GCC
            set (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")
            set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")
            # Reduce GCC optimization level from -O3 to -O2 for stability in RELEASE build configuration
            set (CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
            set (CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
        endif ()
        set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG -D_DEBUG")
        set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -D_DEBUG")
    endif ()
    if (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
        if (CMAKE_GENERATOR STREQUAL Ninja)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
        endif ()
        # Temporary workaround for Travis CI VM as Ubuntu 12.04 LTS still uses old glibc header files that do not have the necessary patch for Clang to work correctly
        # TODO: Remove this workaround when Travis CI VM has been migrated to Ubuntu 14.04 LTS (or hopefully it will be CentOS :)
        if (DEFINED ENV{CI} AND "$ENV{LINUX}" STREQUAL 1)
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

# Set common binary output directory for all platforms
set_output_directories (${CMAKE_BINARY_DIR}/bin RUNTIME PDB)

# Macro for setting symbolic link on platform that supports it
macro (create_symlink SOURCE DESTINATION)
    if (CMAKE_HOST_WIN32)
        if (IS_DIRECTORY ${SOURCE})
            set (SLASH_D /D)
        else ()
            unset (SLASH_D)
        endif ()
        if (URHO3D_MKLINK)
            if (NOT EXISTS ${DESTINATION})
                # Have to use string-REPLACE as file-TO_NATIVE_PATH does not work as expected with MinGW on "backward host" system
                string (REPLACE / \\ BACKWARD_DESTINATION ${DESTINATION})
                string (REPLACE / \\ BACKWARD_SOURCE ${SOURCE})
                execute_process (COMMAND cmd /C mklink ${SLASH_D} ${BACKWARD_DESTINATION} ${BACKWARD_SOURCE} OUTPUT_QUIET ERROR_QUIET)
            endif ()
        elseif (${ARGN} STREQUAL FALLBACK_TO_COPY)
            if (NOT IS_ABSOLUTE ${SOURCE})
                get_filename_component (PATH ${DESTINATION} PATH)
                set (SOURCE ${PATH}/${SOURCE})
            endif ()
            if (SLASH_D)
                set (COMMAND COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE} ${DESTINATION})
            else ()
                set (COMMAND COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SOURCE} ${DESTINATION})
            endif ()
            if (TARGET ${TARGET_NAME})
                # Fallback to copy everytime the target is built
                add_custom_command (TARGET ${TARGET_NAME} POST_BUILD ${COMMAND} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
            else ()
                # Fallback to copy only one time
                execute_process (${COMMAND})
            endif ()
        else ()
            message (WARNING "Unable to create symbolic link on this host system, you may need to manually copy file/dir from \"${SOURCE}\" to \"${DESTINATION}\"")
        endif ()
    else ()
        execute_process (COMMAND ${CMAKE_COMMAND} -E create_symlink ${SOURCE} ${DESTINATION})
    endif ()
endmacro ()

include (GenerateExportHeader)

# Macro for precompiling header (On MSVC, the dummy C++ implementation file for precompiling the header file would be generated if not already exists)
# This macro should be called before the CMake target has been added
# Typically, user should indirectly call this macro by using the 'PCH' option when calling define_source_file() macro
macro (enable_pch HEADER_PATHNAME)
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
                if (FILE MATCHES \\.cpp$)
                    if (FILE MATCHES ${NAME_WE}\\.cpp$)
                        # Precompiling header file
                        set_property (SOURCE ${FILE} APPEND_STRING PROPERTY COMPILE_FLAGS "/Fp$(IntDir)${PCH_FILENAME} /Yc${HEADER_FILENAME}")
                    else ()
                        # Use the precompiled header file
                        get_property (NO_PCH SOURCE ${FILE} PROPERTY NO_PCH)
                        if (NOT NO_PCH)
                            set_property (SOURCE ${FILE} APPEND_STRING PROPERTY COMPILE_FLAGS "/Fp$(IntDir)${PCH_FILENAME} /Yu${HEADER_FILENAME} /FI${HEADER_FILENAME}")
                        endif ()
                    endif ()
                endif ()
            endforeach ()
            unset (${TARGET_NAME}_HEADER_PATHNAME)
        else ()
            # The target has not been created yet, so set an internal variable to come back here again later
            set (${TARGET_NAME}_HEADER_PATHNAME ${HEADER_PATHNAME})
            # But proceed to add the dummy C++ implementation file if necessary
            set (CXX_FILENAME ${NAME_WE}.cpp)
            get_filename_component (PATH ${HEADER_PATHNAME} PATH)
            if (PATH)
                set (PATH ${PATH}/)
            endif ()
            list (FIND SOURCE_FILES ${PATH}${CXX_FILENAME} CXX_FILENAME_FOUND)
            if (CXX_FILENAME_FOUND STREQUAL -1)
                file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/${CXX_FILENAME} "// This is a generated file. DO NOT EDIT!\n\n#include \"${HEADER_FILENAME}\"")
                list (APPEND SOURCE_FILES ${CXX_FILENAME})
            endif ()
        endif ()
    else ()
        # GCC or Clang
        if (TARGET ${TARGET_NAME})
            # Cache the compiler flags setup for the current scope so far
            get_directory_property (COMPILE_DEFINITIONS COMPILE_DEFINITIONS)
            get_directory_property (INCLUDE_DIRECTORIES INCLUDE_DIRECTORIES)
            get_target_property (TYPE ${TARGET_NAME} TYPE)
            if (TYPE MATCHES SHARED)
                list (APPEND COMPILE_DEFINITIONS ${TARGET_NAME}_EXPORTS)
                # todo: Reevaluate the replacement of this deprecated function (since CMake 2.8.12) when the CMake minimum required version is set to 2.8.12
                # At the moment it seems using the function is the "only way" to get the export flags into a CMake variable
                # Additionally, CMake implementation of 'VISIBILITY_INLINES_HIDDEN' has a bug (tested in 2.8.12.2) that it erroneously sets the flag for C compiler too
                add_compiler_export_flags (COMPILER_EXPORT_FLAGS)
                if (NOT ANDROID)    # To cater for Android/CMake toolchain which already adds -fPIC flags into the CMake C and CXX compiler flags
                    set (COMPILER_EXPORT_FLAGS "${COMPILER_EXPORT_FLAGS} -fPIC")
                endif ()
            endif ()
            string (REPLACE ";" " -D" COMPILE_DEFINITIONS "-D${COMPILE_DEFINITIONS}")
            string (REPLACE ";" " -I" INCLUDE_DIRECTORIES "-I${INCLUDE_DIRECTORIES}")
            # Make sure the precompiled headers are not stale by creating custom rules to re-compile the header as necessary
            file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${PCH_FILENAME})
            foreach (CONFIG ${CMAKE_CONFIGURATION_TYPES} ${CMAKE_BUILD_TYPE})   # These two vars are mutually exclusive
                # Generate *.rsp containing configuration specific compiler flags
                string (TOUPPER ${CONFIG} UPPERCASE_CONFIG)
                file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.rsp.new "${COMPILE_DEFINITIONS} ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${UPPERCASE_CONFIG}} ${COMPILER_EXPORT_FLAGS} ${INCLUDE_DIRECTORIES} -c -x c++-header")
                execute_process (COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.rsp.new ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.rsp)
                file (REMOVE ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.rsp.new)
                # Determine the dependency list
                execute_process (COMMAND ${CMAKE_CXX_COMPILER} @${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.rsp -MTdeps -MM -o ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.deps ${CMAKE_CURRENT_SOURCE_DIR}/${HEADER_PATHNAME} RESULT_VARIABLE CXX_COMPILER_EXIT_CODE)
                if (NOT CXX_COMPILER_EXIT_CODE EQUAL 0)
                    message (FATAL_ERROR "The configured compiler toolchain in the build tree is not able to handle all the compiler flags required to build the project. "
                        "Please kindly update your compiler toolchain to its latest version. If you are using MinGW then make sure it is MinGW-W64 instead of MinGW-W32 or TDM-GCC (Code::Blocks default). "
                        "However, if you think there is something wrong with the compiler flags being used then please file a bug report to the project devs.")
                endif ()
                file (STRINGS ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.deps DEPS)
                string (REGEX REPLACE "^deps: *| *\\; +" ";" DEPS ${DEPS})
                # Create the rule that depends on the included headers
                add_custom_command (OUTPUT ${HEADER_FILENAME}.${CONFIG}.pch.trigger
                    COMMAND ${CMAKE_CXX_COMPILER} @${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.rsp -o ${PCH_FILENAME}/${PCH_FILENAME}.${CONFIG} ${CMAKE_CURRENT_SOURCE_DIR}/${HEADER_PATHNAME}
                    COMMAND ${CMAKE_COMMAND} -E touch ${HEADER_FILENAME}.${CONFIG}.pch.trigger
                    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${HEADER_FILENAME}.${CONFIG}.pch.rsp ${DEPS}
                    COMMENT "Precompiling header file '${HEADER_FILENAME}' for ${CONFIG} configuration")
            endforeach ()
            # Use the precompiled header file
            foreach (FILE ${SOURCE_FILES})
                if (FILE MATCHES \\.cpp$)
                    get_property (NO_PCH SOURCE ${FILE} PROPERTY NO_PCH)
                    if (NOT NO_PCH)
                        set_property (SOURCE ${FILE} APPEND_STRING PROPERTY COMPILE_FLAGS "-include ${HEADER_FILENAME}")
                    endif ()
                endif ()
            endforeach ()
            unset (${TARGET_NAME}_HEADER_PATHNAME)
        else ()
            # The target has not been created yet, so set an internal variable to come back here again later
            set (${TARGET_NAME}_HEADER_PATHNAME ${HEADER_PATHNAME})
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
            # Ninja-build specific
            if (CMAKE_GENERATOR STREQUAL Ninja)
                # The precompiled header is always generated in the current binary dir,
                # but Ninja project is not able to find it without adding the binary dir to the include search path
                list (APPEND INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR})
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

    # CMake does not support IPHONEOS_DEPLOYMENT_TARGET the same manner as it supports CMAKE_OSX_DEPLOYMENT_TARGET
    # The iOS deployment target is set using the corresponding Xcode attribute as target property instead
    if (IOS AND IPHONEOS_DEPLOYMENT_TARGET)
        set_target_properties (${TARGET_NAME} PROPERTIES XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET ${IPHONEOS_DEPLOYMENT_TARGET})
    endif ()

    # Workaround CMake/Xcode generator bug where it always appends '/build' path element to SYMROOT attribute and as such the items in Products are always rendered as red as if they are not yet built
    if (XCODE)
        file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/build)
        get_target_property (LOCATION ${TARGET_NAME} LOCATION)
        string (REGEX REPLACE "^.*\\$\\(CONFIGURATION\\)" $(CONFIGURATION) SYMLINK ${LOCATION})
        get_filename_component (DIRECTORY ${SYMLINK} PATH)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
            COMMAND mkdir -p ${DIRECTORY} && ln -s -f $<TARGET_FILE:${TARGET_NAME}> ${DIRECTORY}/$<TARGET_FILE_NAME:${TARGET_NAME}>
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/build)
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
#  STATIC/SHARED/MODULE/EXCLUDE_FROM_ALL - see CMake help on add_library() command
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

    if (CMAKE_PROJECT_NAME STREQUAL Urho3D)
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
#  NODEPS - setup executable target without defining Urho3D dependency libraries
#  WIN32/MACOSX_BUNDLE/EXCLUDE_FROM_ALL - see CMake help on add_executable() command
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
    if (DEST_RUNTIME_DIR)
        # Need to check if the destination variable is defined first because this macro could be called by external project that does not wish to install anything
        install (TARGETS ${TARGET_NAME} RUNTIME DESTINATION ${DEST_RUNTIME_DIR} BUNDLE DESTINATION ${DEST_BUNDLE_DIR})
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

# Macro for setting up an executable target with resources to copy
#  NODEPS - setup executable target without defining Urho3D dependency libraries
#  NOBUNDLE - do not use MACOSX_BUNDLE even when URHO3D_MACOSX_BUNDLE build option is enabled
#  WIN32/MACOSX_BUNDLE/EXCLUDE_FROM_ALL - see CMake help on add_executable() command
macro (setup_main_executable)
    # Parse extra arguments
    cmake_parse_arguments (ARG "NOBUNDLE;MACOSX_BUNDLE;WIN32" "" "" ${ARGN})

    # Define resource files
    if (XCODE)
        set (RESOURCE_FILES ${CMAKE_SOURCE_DIR}/bin/CoreData ${CMAKE_SOURCE_DIR}/bin/Data ${CMAKE_SOURCE_DIR}/bin/Data/Textures/UrhoIcon.icns)
        if (IOS)
            list (APPEND RESOURCE_FILES ${CMAKE_SOURCE_DIR}/bin/Data/Textures/UrhoIcon.png)
        endif ()
        source_group (Resources FILES ${RESOURCE_FILES})
        set_source_files_properties (${RESOURCE_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
        list (APPEND SOURCE_FILES ${RESOURCE_FILES})
    endif ()

    if (ANDROID)
        # Add SDL native init function, SDL_Main() entry point must be defined by one of the source files in ${SOURCE_FILES}
        find_file (ANDROID_MAIN_C_PATH SDL_android_main.c
            HINTS ${URHO3D_HOME}/include/${PATH_SUFFIX}/ThirdParty/SDL/android ${CMAKE_SOURCE_DIR}/Source/ThirdParty/SDL/src/main/android
            DOC "Path to SDL_android_main.c" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        mark_as_advanced (ANDROID_MAIN_C_PATH)  # Hide it from cmake-gui in non-advanced mode
        if (ANDROID_MAIN_C_PATH)
            list (APPEND SOURCE_FILES ${ANDROID_MAIN_C_PATH})
        else ()
            message (FATAL_ERROR
                "Could not find SDL_android_main.c source file in the Urho3D build tree or SDK installation. "
                "Please reconfigure and rebuild your Urho3D build tree; or reinstall the SDK.")
        endif ()
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
        unset (TARGET_PROPERTIES)
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
        endif ()
        setup_executable (${EXE_TYPE} ${ARG_UNPARSED_ARGUMENTS})
        if (TARGET_PROPERTIES)
            set_target_properties (${TARGET_NAME} PROPERTIES ${TARGET_PROPERTIES})
        endif ()
    endif ()

    if (IOS)
        # Define a custom target to check for resource modification
        get_target_property (TARGET_LOC ${TARGET_NAME} LOCATION)
        string (REGEX REPLACE /Contents/MacOS "" TARGET_LOC ${TARGET_LOC})    # The regex replacement is temporary workaround to correct the wrong location caused by CMake/Xcode generator bug
        add_custom_target (RESOURCE_CHECK_${TARGET_NAME} ALL
            \(\( `find ${RESOURCE_FILES} -newer ${TARGET_LOC} 2>/dev/null |wc -l` \)\) && touch -cm ${SOURCE_FILES} || exit 0
            COMMENT "Checking for changes in the Resource folders")
        add_dependencies (${TARGET_NAME} RESOURCE_CHECK_${TARGET_NAME})
    endif ()
endmacro ()

# Macro for adjusting target output name by dropping _suffix from the target name
macro (adjust_target_name)
    string (REGEX REPLACE _.*$ "" OUTPUT_NAME ${TARGET_NAME})
    set_target_properties (${TARGET_NAME} PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})
endmacro ()

# Macro for defining external library dependencies
# The purpose of this macro is emulate CMake to set the external library dependencies transitively
# It works for both targets setup within Urho3D project and outside Urho3D project that uses Urho3D as external static/shared library
macro (define_dependency_libs TARGET)
    # ThirdParty/SDL external dependency
    if (${TARGET} MATCHES SDL|Urho3D)
        if (WIN32)
            list (APPEND LIBS user32 gdi32 winmm imm32 ole32 oleaut32 version uuid)
        elseif (APPLE)
            list (APPEND LIBS dl pthread)
        elseif (ANDROID)
            list (APPEND LIBS dl log android)
        else ()
            # Linux
            list (APPEND LIBS dl pthread rt)
            if (RPI)
                list (APPEND ABSOLUTE_PATH_LIBS ${BCM_VC_LIBRARIES})
            endif ()
        endif ()
    endif ()

    # ThirdParty/kNet & ThirdParty/Civetweb external dependency
    if (${TARGET} MATCHES Civetweb|kNet|Urho3D)
        if (WIN32)
            list (APPEND LIBS ws2_32)
        elseif (NOT ANDROID)
            list (APPEND LIBS pthread)
        endif ()
    endif ()

    # Urho3D/LuaJIT external dependency
    if (URHO3D_LUAJIT AND ${TARGET} MATCHES LuaJIT|Urho3D)
        if (NOT WIN32)
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
        elseif (NOT ANDROID)
            list (APPEND LIBS pthread)
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
        else ()
            if (DIRECT3D_FOUND)
                list (APPEND ABSOLUTE_PATH_LIBS ${DIRECT3D_LIBRARIES})
            else ()
                # If SDK not found, assume the libraries are found from default directories
                list (APPEND LIBS ${DIRECT3D_LIBRARIES})
            endif ()
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
#  PCH <value> - Enable precompiled header support on the defined source files using the specified header file
#  PARENT_SCOPE - Glob source files in current directory but set the result in parent-scope's variable ${DIR}_CPP_FILES and ${DIR}_H_FILES instead
#  RECURSE - Option to glob recursively
#  GROUP - Option to group source files based on its relative path to the corresponding parent directory (only works when PARENT_SCOPE option is not in use)
macro (define_source_files)
    # Parse the arguments
    cmake_parse_arguments (ARG "PARENT_SCOPE;RECURSE;GROUP" "PCH" "EXTRA_CPP_FILES;EXTRA_H_FILES;GLOB_CPP_PATTERNS;GLOB_H_PATTERNS;EXCLUDE_PATTERNS" ${ARGN})

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
    # Parse the arguments for the underlying install command for the SDK
    cmake_parse_arguments (ARG "FILES_MATCHING;USE_FILE_SYMLINK;BUILD_TREE_ONLY" "BASE;DESTINATION" "FILES;DIRECTORY;PATTERN" ${ARGN})
    unset (INSTALL_MATCHING)
    if (ARG_FILES)
        set (INSTALL_TYPE FILES)
        set (INSTALL_SOURCES ${ARG_FILES})
        unset (INSTALL_PERMISSIONS)
    elseif (ARG_DIRECTORY)
        set (INSTALL_TYPE DIRECTORY)
        set (INSTALL_SOURCES ${ARG_DIRECTORY})
        set (INSTALL_PERMISSIONS ${DEST_PERMISSIONS})
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
    if (NOT ARG_BUILD_TREE_ONLY AND DEST_INCLUDE_DIR)
        # Need to check if the destination variable is defined first because this macro could be called by external project that does not wish to install anything
        install (${INSTALL_TYPE} ${INSTALL_SOURCES} DESTINATION ${ARG_DESTINATION} ${INSTALL_PERMISSIONS} ${INSTALL_MATCHING})
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
endmacro ()

# Set common project structure for Android platform
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
    foreach (I CoreData Data)
        if (NOT EXISTS ${CMAKE_SOURCE_DIR}/Android/assets/${I})
            create_symlink (${CMAKE_SOURCE_DIR}/bin/${I} ${CMAKE_SOURCE_DIR}/Android/assets/${I} FALLBACK_TO_COPY)
        endif ()
    endforeach ()
    foreach (I AndroidManifest.xml build.xml src res assets jni)
        if (EXISTS ${CMAKE_SOURCE_DIR}/Android/${I} AND NOT EXISTS ${CMAKE_BINARY_DIR}/${I})    # No-ops when 'Android' is used as build tree
            create_symlink (${CMAKE_SOURCE_DIR}/Android/${I} ${CMAKE_BINARY_DIR}/${I} FALLBACK_TO_COPY)
        endif ()
    endforeach ()
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
