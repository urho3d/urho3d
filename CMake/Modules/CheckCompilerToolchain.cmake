#
# Copyright (c) 2008-2016 the Urho3D project.
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
#  RPI
#  POWERPC
#
# Compiler version in major.minor.patch format:
#  COMPILER_VERSION
#
# CPU SIMD instruction extensions support:
#  HAVE_MMX
#  HAVE_3DNOW
#  HAVE_SSE
#  HAVE_SSE2
#  HAVE_ALTIVEC
#

if (NOT MSVC AND NOT DEFINED NATIVE_PREDEFINED_MACROS)
    execute_process (COMMAND ${CMAKE_COMMAND} -E echo COMMAND ${CMAKE_C_COMPILER} -E -dM - OUTPUT_VARIABLE NATIVE_PREDEFINED_MACROS ERROR_QUIET)
    string (REPLACE \n ";" NATIVE_PREDEFINED_MACROS "${NATIVE_PREDEFINED_MACROS}")    # Stringify for string replacement
    set (NATIVE_PREDEFINED_MACROS ${NATIVE_PREDEFINED_MACROS} CACHE INTERNAL "Compiler toolchain native predefined macros")
endif ()

macro (check_native_define REGEX OUTPUT_VAR)
    if (NOT DEFINED ${OUTPUT_VAR})
        string (REGEX MATCH "#define +${REGEX} +1" matched "${NATIVE_PREDEFINED_MACROS}")
        if (matched)
            set (${OUTPUT_VAR} 1)
        else ()
            set (${OUTPUT_VAR} 0)
        endif ()
        set (${OUTPUT_VAR} ${${OUTPUT_VAR}} CACHE INTERNAL "Compiler toolchain has predefined macros matching ${REGEX}")
    endif ()
endmacro ()

if (MSVC)
    # On MSVC compiler, use the chosen CMake/VS generator to determine the ABI
    # TODO: revisit this later because VS may use Clang as compiler in the future
    if (CMAKE_GENERATOR MATCHES Win64)
        set (NATIVE_64BIT 1)
    else ()
        set (NATIVE_64BIT 0)
    endif ()
    # Determine MSVC compiler version based on CMake informational variables
    if (NOT DEFINED COMPILER_VERSION)
        # TODO: fix this ugly hardcoding that needs to be constantly maintained
        if (MSVC_VERSION EQUAL 1200)
            set (COMPILER_VERSION 6.0)
        elseif (MSVC_VERSION EQUAL 1300)
            set (COMPILER_VERSION 7.0)
        elseif (MSVC_VERSION EQUAL 1310)
            set (COMPILER_VERSION 7.1)
        elseif (MSVC_VERSION EQUAL 1400)
            set (COMPILER_VERSION 8.0)
        elseif (MSVC_VERSION EQUAL 1500)
            set (COMPILER_VERSION 9.0)
        elseif (MSVC_VERSION EQUAL 1600)
            set (COMPILER_VERSION 10.0)
        elseif (MSVC_VERSION EQUAL 1700)
            set (COMPILER_VERSION 11.0)
        elseif (MSVC_VERSION EQUAL 1800)
            set (COMPILER_VERSION 12.0)
        elseif (MSVC_VERSION EQUAL 1900)
            set (COMPILER_VERSION 14.0)
        elseif (MSVC_VERSION GREATER 1900)
            set (COMPILER_VERSION 14.0+)
        else ()
            set (COMPILER_VERSION 6.0-)
        endif ()
        set (COMPILER_VERSION ${COMPILER_VERSION} CACHE INTERNAL "MSVC Compiler version")
    endif ()
else ()
    # On non-MSVC compiler, default to build using native ABI of the chosen compiler toolchain in the build tree
    check_native_define ("__(x86_|aarch|ppc|PPC|powerpc|POWERPC)64__" NATIVE_64BIT)
    # Android arm64 compiler only emits __aarch64__ while iOS arm64 emits __aarch64__, __arm64__, and __arm__; for armv7a all emit __arm__
    check_native_define ("__(arm|aarch64)__" ARM)
    # For completeness sake as currently we do not support PowerPC (yet)
    check_native_define ("__(ppc|PPC|powerpc|POWERPC)(64)*__" POWERPC)
    # Check if the target arm platform is currently supported
    if (ARM AND NOT ANDROID AND NOT RPI AND NOT IOS AND NOT TVOS)
        # TODO: check the uname of the host system for the telltale sign of RPI, just in case this is a native build on the device itself
        message (FATAL_ERROR "Unsupported arm target architecture")
    endif ()
    # GCC/Clang and all their derivatives should understand this command line option to get the compiler version
    if (NOT DEFINED COMPILER_VERSION)
        execute_process (COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE COMPILER_VERSION ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
        set (COMPILER_VERSION ${COMPILER_VERSION} CACHE INTERNAL "GCC/Clang Compiler version")
    endif ()
endif ()

macro (check_extension CPU_INSTRUCTION_EXTENSION)
    string (TOUPPER "${CPU_INSTRUCTION_EXTENSION}" UCASE_EXT_NAME)   # Stringify to guard against empty variable
    if (NOT DEFINED HAVE_${UCASE_EXT_NAME})
        execute_process (COMMAND ${CMAKE_COMMAND} -E echo COMMAND ${CMAKE_C_COMPILER} -m${CPU_INSTRUCTION_EXTENSION} -E -dM - OUTPUT_VARIABLE PREDEFINED_MACROS ERROR_QUIET)
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
        set (HAVE_${UCASE_EXT_NAME} ${matched} CACHE INTERNAL "Compiler toolchain supports ${UCASE_EXT_NAME} CPU instruction extension")
    endif ()
endmacro ()

if (NOT ARM)
    if (MSVC)
        # In our documentation we have already declared that we only support CPU with SSE2 extension on Windows platform, so we can safely hard-code these for MSVC compiler
        foreach (VAR HAVE_MMX HAVE_SSE HAVE_SSE2)
            set (${VAR} 1)
        endforeach ()
    else ()
        check_extension (mmx)
        check_extension (sse)
        check_extension (sse2)
     endif ()
    # As newer CPUs from AMD do not support 3DNow! anymore, we cannot make any assumption for 3DNow! extension check
    # Don't bother with this check on AppleClang and MSVC compiler toolchains (Urho3D only supports CPU with SSE2 on the asscoiated platforms anyway)
    if (NOT APPLE AND NOT MSVC)
        check_extension (3dnow __3dNOW__)
    endif ()
    # For completeness sake as currently we do not support PowerPC (yet)
    if (POWERPC)
        check_extension (altivec)
    endif ()
endif ()

# Explicitly set the variable to 1 when it is defined and truthy or 0 when it is not defined or falsy
foreach (VAR HAVE_MMX HAVE_3DNOW HAVE_SSE HAVE_SSE2 HAVE_ALTIVEC)
    if (${VAR})
        set (${VAR} 1)
    else ()
        set (${VAR} 0)
    endif ()
endforeach ()
