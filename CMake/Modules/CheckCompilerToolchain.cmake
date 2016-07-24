#
# Copyright (c) 2008-2017 the Urho3D project.
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

# Check the chosen compiler toolchain in the build tree
#
# Native ABI:
#  NATIVE_64BIT
#
# Target architecture:
#  ARM
#  MIPS
#  POWERPC
#  X86
#
# Compiler version in major.minor.patch format, except MSVC where it follows its own format:
#  COMPILER_VERSION
#
# CPU SIMD instruction extensions support for x86/x86_64 archs:
#  HAVE_MMX
#  HAVE_3DNOW
#  HAVE_SSE
#  HAVE_SSE2
#  HAVE_ALTIVEC
#
# CPU SIMD instruction extension support for arm/arm64 archs:
#  HAVE_NEON
#  NEON
#
# C++ features:
#  RTTI
#  EXCEPTIONS
#

if (EMSCRIPTEN AND CMAKE_HOST_WIN32)
    set (EMCC_FIX EMCC_FIX)
    set (NULL_DEVICE${EMCC_FIX} ${CMAKE_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/null.c)
    execute_process (COMMAND ${CMAKE_COMMAND} -E touch ${NULL_DEVICE${EMCC_FIX}})
endif ()

macro (check_native_define REGEX OUTPUT_VAR)
    if (NOT DEFINED CCT_${OUTPUT_VAR})
        string (REGEX MATCH "#define +${REGEX} +([^;]+)" matched "${CCT_NATIVE_PREDEFINED_MACROS}")
        if (matched)
            string (REGEX MATCH "\\(.*\\)" captured "${REGEX}")
            if (captured)
                set (GROUP 2)
            else ()
                set (GROUP 1)
            endif ()
            string (REGEX REPLACE "#define +${REGEX} +([^;]+)" \\${GROUP} matched "${matched}")
            set (${OUTPUT_VAR} ${matched})
        else ()
            set (${OUTPUT_VAR} 0)
        endif ()
        set (CCT_${OUTPUT_VAR} ${${OUTPUT_VAR}} CACHE INTERNAL "Compiler toolchain has predefined macros matching ${REGEX}")
    endif ()
    set (${OUTPUT_VAR} ${CCT_${OUTPUT_VAR}})
endmacro ()

macro (check_extension EXTENSION)
    string (TOUPPER "${EXTENSION}" UCASE_EXT_NAME)   # Stringify to guard against empty variable
    string (REGEX REPLACE [^=]+= "" UCASE_EXT_NAME "${UCASE_EXT_NAME}")
    if (NOT DEFINED CCT_HAVE_${UCASE_EXT_NAME})
        execute_process (COMMAND ${CMAKE_C_COMPILER} ${ARCH_FLAGS} -m${EXTENSION} -E -dM -xc ${NULL_DEVICE${EMCC_FIX}} RESULT_VARIABLE CC_EXIT_STATUS OUTPUT_VARIABLE PREDEFINED_MACROS ERROR_QUIET)
        if (NOT CC_EXIT_STATUS EQUAL 0)
            message (FATAL_ERROR "Could not check compiler toolchain CPU instruction extension as it does not handle '-E -dM' compiler flags correctly")
        endif ()
        if (NOT ${ARGN} STREQUAL "")
            set (EXPECTED_MACRO ${ARGN})
        else ()
            set (EXPECTED_MACRO __${UCASE_EXT_NAME}__)
        endif ()
        string (REGEX MATCH "#define +${EXPECTED_MACRO} +1" matched "${PREDEFINED_MACROS}")
        if (matched)
            set (matched 1)
        else ()
            set (matched 0)
        endif ()
        set (CCT_HAVE_${UCASE_EXT_NAME} ${matched} CACHE INTERNAL "Compiler toolchain supports ${UCASE_EXT_NAME} CPU instruction extension")
    endif ()
    set (HAVE_${UCASE_EXT_NAME} ${CCT_HAVE_${UCASE_EXT_NAME}})
endmacro ()

macro (check_feature_enabled FEATURE)
    if (NOT DEFINED CCT_${FEATURE})
        set (COMPILER_FLAGS ${CMAKE_CXX_FLAGS})
        separate_arguments (COMPILER_FLAGS)
        execute_process (COMMAND ${CMAKE_CXX_COMPILER} ${COMPILER_FLAGS} -E -dM -xc++ ${NULL_DEVICE} RESULT_VARIABLE CXX_EXIT_STATUS OUTPUT_VARIABLE PREDEFINED_MACROS ERROR_QUIET)
        if (NOT CXX_EXIT_STATUS EQUAL 0)
            message (FATAL_ERROR "Could not check compiler toolchain CPU instruction extension as it does not handle '-E -dM' compiler flags correctly")
        endif ()
        if (NOT ${ARGN} STREQUAL "")
            set (EXPECTED_MACRO ${ARGN})
        else ()
            set (EXPECTED_MACRO __${FEATURE})
        endif ()
        string (REGEX MATCH "#define +${EXPECTED_MACRO} +1" matched "${PREDEFINED_MACROS}")
        if (matched)
            set (matched 1)
        else ()
            set (matched 0)
        endif ()
        set (CCT_${FEATURE} ${matched} CACHE INTERNAL "Is ${FEATURE} enabled")
    endif ()
    set (${FEATURE} ${CCT_${FEATURE}})
endmacro ()

if (INVALIDATE_CCT)
    get_cmake_property (CACHE_VARIABLES CACHE_VARIABLES)
    foreach (VAR ${CACHE_VARIABLES})
        if (VAR MATCHES ^CCT_)
            unset (${VAR} CACHE)
        endif ()
    endforeach ()
endif ()

if (NOT MSVC AND NOT DEFINED CCT_NATIVE_PREDEFINED_MACROS)
    if (IOS OR TVOS)
        # Assume arm64 is the native arch (this does not prevent our build system to target armv7 later in universal binary build)
        set (ARCH_FLAGS -arch arm64)
    elseif (ANDROID AND CMAKE_CXX_COMPILER_ID MATCHES Clang)
        # Use the same target flag as configured by Android/CMake toolchain file
        string (REGEX REPLACE "^.*-target ([^ ]+).*$" "-target;\\1" ARCH_FLAGS "${CMAKE_CXX_FLAGS}")
    endif ()
    execute_process (COMMAND ${CMAKE_C_COMPILER} ${ARCH_FLAGS} -E -dM -xc ${NULL_DEVICE} RESULT_VARIABLE CC_EXIT_STATUS OUTPUT_VARIABLE CCT_NATIVE_PREDEFINED_MACROS ERROR_QUIET)
    if (NOT CC_EXIT_STATUS EQUAL 0)
        message (FATAL_ERROR "Could not check compiler toolchain as it does not handle '-E -dM' compiler flags correctly")
    endif ()
    string (REPLACE \n ";" CCT_NATIVE_PREDEFINED_MACROS "${CCT_NATIVE_PREDEFINED_MACROS}")    # Stringify for string replacement
    set (CCT_NATIVE_PREDEFINED_MACROS ${CCT_NATIVE_PREDEFINED_MACROS} CACHE INTERNAL "Compiler toolchain native predefined macros")
endif ()

if (MSVC)
    # TODO: revisit this later because VS may use Clang as compiler in the future
    # On MSVC compiler, use the chosen CMake/VS generator to determine the ABI
    set (NATIVE_64BIT ${CMAKE_CL_64})
    # We only support one target arch when using MSVC for now
    set (X86 1)
    # Determine MSVC compiler version based on CMake informational variables
    set (COMPILER_VERSION ${MSVC_VERSION})
    # Assume all C++ features are ON
    set (RTTI 1)
    set (EXCEPTIONS 1)
else ()
    # Determine the native ABI based on the size of pointer
    check_native_define (__SIZEOF_POINTER__ SIZEOF_POINTER)
    if (SIZEOF_POINTER EQUAL 8)
        set (NATIVE_64BIT 1)
    endif ()
    # Android arm64 compiler only emits __aarch64__ while iOS arm64 emits __aarch64__, __arm64__, and __arm__; for armv7a all emit __arm__
    check_native_define ("__(arm|aarch64)__" ARM)
    # Compiler should emit __x86_64__, __i686__, or __i386__, etc when targeting archs using Intel or AMD processors
    check_native_define ("__(i.86|x86_64)__" X86)
    # For completeness sake as currently we do not support MIPS and PowerPC (yet)
    check_native_define ("__MIPSEL__" MIPS)
    check_native_define ("__(ppc|PPC|powerpc|POWERPC)(64)*__" POWERPC)
    # GCC/Clang and all their derivatives should understand this command line option to get the compiler version
    if (NOT DEFINED COMPILER_VERSION)
        if (EMSCRIPTEN)
            set (COMPILER_VERSION ${EMSCRIPTEN_EMCC_VERSION})
        else ()
            execute_process (COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE COMPILER_VERSION ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
        endif ()
        set (COMPILER_VERSION ${COMPILER_VERSION} CACHE INTERNAL "GCC/Clang Compiler version")
    endif ()
    check_feature_enabled (RTTI __GXX_RTTI)
    check_feature_enabled (EXCEPTIONS)
endif ()

if (ARM)
    if (MSVC)
        message (FATAL_ERROR "This build system does not support ARM build using MSVC compiler toolchain yet. Contribution is welcome.")
    else ()
        check_feature_enabled (NEON __ARM_NEON)
        if (NEON)
            set (HAVE_NEON 1)
        else ()
            check_extension (fpu=neon __ARM_NEON)
        endif ()
    endif ()
else ()
    if (MSVC)
        # In our documentation we have already declared that we only support CPU with SSE2 extension on Windows platform, so we can safely hard-code these for MSVC compiler
        foreach (VAR HAVE_MMX HAVE_SSE HAVE_SSE2)
            set (${VAR} 1)
        endforeach ()
    else ()
        if (MINGW AND COMPILER_VERSION VERSION_LESS 4.9.1)
            if (NOT DEFINED URHO3D_SSE)     # Only give the warning once during initial configuration
                # Certain MinGW versions fail to compile SSE code. This is the initial guess for known "bad" version range, and can be tightened later
                message (WARNING "Disabling SSE by default due to MinGW version. It is recommended to upgrade to MinGW with GCC >= 4.9.1. You can also try to re-enable SSE with CMake option -DURHO3D_SSE=1, but this may result in compile errors.")
            endif ()
        elseif (NOT EMSCRIPTEN)     # Emscripten does not support SSE/SSE2 (yet) now but erroneously responding positively to our probe, so skip them for Emscripten for now
            check_extension (sse)
            check_extension (sse2)
        endif ()
        if (NOT APPLE AND NOT WIN32)    # Linux only
            check_extension (mmx)
            check_extension (3dnow __3dNOW__)
        endif ()
    endif ()
    # For completeness sake as currently we do not support PowerPC (yet)
    if (POWERPC)
        check_extension (altivec)
    endif ()
endif ()

# Explicitly set the variable to 1 when it is defined and truthy or 0 when it is not defined or falsy
foreach (VAR NATIVE_64BIT HAVE_MMX HAVE_3DNOW HAVE_SSE HAVE_SSE2 HAVE_ALTIVEC HAVE_NEON NEON)
    if (${VAR})
        set (${VAR} 1)
    else ()
        set (${VAR} 0)
    endif ()
endforeach ()

# When cross-compiling, this macro ensures that a native compiler toolchain also exists for building the host tool targets
macro (check_native_compiler_exist)
    if (NOT HAVE_NATIVE_COMPILER)
        message (STATUS "Performing Test HAVE_NATIVE_COMPILER")
        file (WRITE ${CMAKE_BINARY_DIR}/generated/CMakeLists.txt "message (\"Probing native compiler toolchain...\")\n")
        execute_process (COMMAND ${CMAKE_COMMAND} -E env CC=${SAVED_CC} CXX=${SAVED_CXX} ${CMAKE_COMMAND} -G${CMAKE_GENERATOR} .
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/generated RESULT_VARIABLE EXIT_CODE ERROR_VARIABLE ERR_VAR OUTPUT_QUIET)
        if (NOT EXIT_CODE EQUAL 0)
            message (STATUS "Performing Test HAVE_NATIVE_COMPILER - Failed")
            execute_process (COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/generated/CMakeCache.txt)
            message (FATAL_ERROR "Could not find native compiler toolchain. This is usually caused by wrong PATH env-var value.\n${ERR_VAR}")
        endif ()
        message (STATUS "Performing Test HAVE_NATIVE_COMPILER - Success")
        set (HAVE_NATIVE_COMPILER 1 CACHE INTERNAL "Check native compiler exist")
    endif ()
endmacro ()
