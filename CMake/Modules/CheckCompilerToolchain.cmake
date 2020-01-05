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

# Check the chosen compiler toolchain in the build tree
#
# Native ABI:
#  NATIVE_64BIT
#
# Target architecture:
#  ARM
#  MIPS
#  POWERPC
#  WEB
#  X86
#
# CPU SIMD instruction extensions support for x86/x86_64 archs:
#  HAVE_MMX
#  HAVE_3DNOW
#  HAVE_SSE
#  HAVE_SSE2
#  HAVE_SSE3
#  HAVE_SSE4
#  HAVE_AVX
#  HAVE_AVX2
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
# C++11 type traits standard:
#  IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE
#  IS_TRIVIALLY_DESTRUCTIBLE
#  IS_TRIVIALLY_COPY_ASSIGNABLE
#  IS_TRIVIALLY_COPY_CONSTRUCTIBLE
#  CLANG_PRE_STANDARD (Clang with pre-standard type trait templates)

if (EMSCRIPTEN AND CMAKE_HOST_WIN32)
    set (EMCC_FIX EMCC_FIX)
    set (NULL_DEVICE${EMCC_FIX} ${CMAKE_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/null.c)
    execute_process (COMMAND ${CMAKE_COMMAND} -E touch ${NULL_DEVICE${EMCC_FIX}})
endif ()

# Macro for checking if a predefined macro is emitted by the chosen compiler toolchain natively
macro (check_native_define REGEX OUTPUT_VAR)
    if (INVALIDATE_CCT OR NOT DEFINED ${OUTPUT_VAR})
        string (REGEX MATCH "#define +${REGEX} +([^;]+)" matched "${NATIVE_PREDEFINED_MACROS}")
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
        set (${OUTPUT_VAR} ${${OUTPUT_VAR}} CACHE INTERNAL "Compiler toolchain has predefined macros matching ${REGEX}")
    endif ()
endmacro ()

# Macro for checking if a CPU instruction extension is supported by the chosen compiler toolchain
macro (check_extension EXTENSION)
    string (TOUPPER "${EXTENSION}" UCASE_EXT_NAME)   # Stringify to guard against empty variable
    string (REGEX REPLACE [^=]+= "" UCASE_EXT_NAME "${UCASE_EXT_NAME}")
    if (INVALIDATE_CCT OR NOT DEFINED HAVE_${UCASE_EXT_NAME})
        execute_process (COMMAND ${CMAKE_C_COMPILER} ${ARCH_FLAGS} -m${EXTENSION} -E -dM -xc ${NULL_DEVICE${EMCC_FIX}} RESULT_VARIABLE CC_EXIT_STATUS OUTPUT_VARIABLE PREDEFINED_MACROS ERROR_QUIET)
        if (NOT CC_EXIT_STATUS EQUAL 0)
            message (FATAL_ERROR "Could not check compiler toolchain CPU instruction extension as it does not handle '-E -dM' compiler flags correctly")
        endif ()
        if (NOT ${ARGN} STREQUAL "")
            set (EXPECTED_MACRO ${ARGN})
        else ()
            set (EXPECTED_MACRO __${UCASE_EXT_NAME}__)
        endif ()
        if (PREDEFINED_MACROS MATCHES "#define +${EXPECTED_MACRO} +1")
            set (matched 1)
        else ()
            set (matched 0)
        endif ()
        set (HAVE_${UCASE_EXT_NAME} ${matched} CACHE INTERNAL "Compiler toolchain supports ${UCASE_EXT_NAME} CPU instruction extension")
    endif ()
endmacro ()

# Macro for checking if a C++ feature is enabled by the configured CXX compiler flags
macro (check_feature_enabled FEATURE)
    if (INVALIDATE_CCT OR NOT DEFINED ${FEATURE})
        set (COMPILER_FLAGS ${CMAKE_CXX_FLAGS})
        separate_arguments (COMPILER_FLAGS)
        execute_process (COMMAND ${CMAKE_CXX_COMPILER} ${ARCH_FLAGS} ${COMPILER_FLAGS} -E -dM -xc++ ${NULL_DEVICE${EMCC_FIX}} RESULT_VARIABLE CXX_EXIT_STATUS OUTPUT_VARIABLE PREDEFINED_MACROS ERROR_QUIET)
        if (NOT CXX_EXIT_STATUS EQUAL 0)
            message (FATAL_ERROR "Could not check compiler toolchain CPU instruction extension as it does not handle '-E -dM' compiler flags correctly")
        endif ()
        if (NOT ${ARGN} STREQUAL "")
            set (EXPECTED_MACRO ${ARGN})
        else ()
            set (EXPECTED_MACRO __${FEATURE})
        endif ()
        if (PREDEFINED_MACROS MATCHES "#define +${EXPECTED_MACRO} +1")
            set (matched 1)
        else ()
            set (matched 0)
        endif ()
        set (${FEATURE} ${matched} CACHE INTERNAL "Is ${FEATURE} enabled")
    endif ()
endmacro ()

include (CheckCXXSourceCompiles)

# Macro for checking if the type trait template is matching the C++11 standard
macro (check_type_trait TYPE_TRAIT)
    string (TOUPPER ${TYPE_TRAIT} UPPERCASE_${TYPE_TRAIT})
    if (INVALIDATE_CCT)
        unset (${UPPERCASE_${TYPE_TRAIT}} CACHE)
    endif ()
    if (CMAKE_CXX_COMPILER_ID MATCHES GNU|Clang)
        set (ORIG_CMAKE_REQUIRED_FLAGS ${CMAKE_REQUIRED_FLAGS})
        set (CMAKE_REQUIRED_FLAGS "-std=c++11 ${CMAKE_REQUIRED_FLAGS}")
    endif ()
    check_cxx_source_compiles ("#include <type_traits>\nint main() { return std::${TYPE_TRAIT}<bool>::value; }" ${UPPERCASE_${TYPE_TRAIT}})
    if (CMAKE_CXX_COMPILER_ID MATCHES GNU|Clang)
        set (CMAKE_REQUIRED_FLAGS ${ORIG_CMAKE_REQUIRED_FLAGS})
    endif ()
endmacro ()

# Macro for checking if a native compiler toolchain exists for building the host tool targets
# This macro is designed to be used in cross-compiling build
macro (check_native_compiler_exist)
    if (NOT HAVE_NATIVE_COMPILER)
        message (STATUS "Performing Test HAVE_NATIVE_COMPILER")
        file (WRITE ${CMAKE_BINARY_DIR}/generated/CMakeLists.txt "message (\"Probing native compiler toolchain...\")\n")
        execute_process (COMMAND ${CMAKE_COMMAND} -E env CC=${SAVED_CC} CXX=${SAVED_CXX} ${CMAKE_COMMAND} -G${CMAKE_GENERATOR} -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM} .
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

if (MSVC)
    # TODO: revisit this later because VS may use Clang as compiler in the future
    # On MSVC compiler, use the chosen CMake/VS generator to determine the ABI
    set (NATIVE_64BIT ${CMAKE_CL_64})
    # We only support one target arch when using MSVC for now and make certain assumptions as per documentation instead of querying the compiler
    foreach (VAR X86 HAVE_MMX HAVE_SSE HAVE_SSE2 RTTI EXCEPTIONS IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE IS_TRIVIALLY_DESTRUCTIBLE IS_TRIVIALLY_COPY_ASSIGNABLE IS_TRIVIALLY_COPY_CONSTRUCTIBLE)
        set (${VAR} 1)
    endforeach ()
else ()
    # The 'invalidate event' will be sent by toolchain file when it reconfigures the cross-compiler or compiler flags
    if (INVALIDATE_CCT OR NOT DEFINED NATIVE_PREDEFINED_MACROS)
        if (IOS OR TVOS)
            # Assume arm64 is the native arch (this does not prevent our build system to target armv7 later in universal binary build)
            set (ARCH_FLAGS -arch arm64)
        elseif (CMAKE_CXX_COMPILER_ID MATCHES Clang)
            # Use the same target flag as configured by CMake toolchain file, if any
            if (ANDROID)
                set (ARCH_FLAGS -target ${ANDROID_LLVM_TRIPLE})
            elseif (CMAKE_CXX_FLAGS MATCHES -target)
                string (REGEX REPLACE "^.*-target ([^ ]+).*$" "-target;\\1" ARCH_FLAGS "${CMAKE_CXX_FLAGS}")
            endif ()
        endif ()
        execute_process (COMMAND ${CMAKE_C_COMPILER} ${ARCH_FLAGS} -E -dM -xc ${NULL_DEVICE${EMCC_FIX}} RESULT_VARIABLE CC_EXIT_STATUS OUTPUT_VARIABLE NATIVE_PREDEFINED_MACROS ERROR_QUIET)
        if (NOT CC_EXIT_STATUS EQUAL 0)
            message (FATAL_ERROR "Could not check compiler toolchain as it does not handle '-E -dM' compiler flags correctly")
        endif ()
        string (REPLACE \n ";" NATIVE_PREDEFINED_MACROS "${NATIVE_PREDEFINED_MACROS}")    # Stringify for string replacement
        set (NATIVE_PREDEFINED_MACROS ${NATIVE_PREDEFINED_MACROS} CACHE INTERNAL "Compiler toolchain native predefined macros")
    endif ()

    # Determine the native ABI based on the size of pointer
    check_native_define (__SIZEOF_POINTER__ SIZEOF_POINTER)
    if (SIZEOF_POINTER EQUAL 8)
        set (NATIVE_64BIT 1)
    endif ()
    # Android arm64 compiler only emits __aarch64__ while iOS/tvOS arm64 emits __aarch64__ and __arm64__; for armv7a all emit __arm__
    check_native_define ("__(arm|aarch64)__" ARM)
    # For completeness sake as currently we do not support MIPS and PowerPC (yet)
    check_native_define (__MIPSEL__ MIPS)
    check_native_define ("__(ppc|PPC|powerpc|POWERPC)(64)*__" POWERPC)
    # For now we only support Emscripten compiler toolchain when targeting Web platform
    check_native_define (__EMSCRIPTEN__ WEB)
    # Compiler should emit __x86_64__, __i686__, or __i386__, etc when targeting archs using Intel or AMD processors
    check_native_define ("__(i.86|x86_64)__" X86)
    if (ARM)
        check_feature_enabled (NEON __ARM_NEON)
        if (NEON)
            # NEON is enabled by default on aarch64 arch so its compiler emits __ARM_NEON by default even though it does not support '-mfpu' compiler flag
            set (HAVE_NEON 1)
        else ()
            check_extension (fpu=neon __ARM_NEON)
        endif ()
    elseif (POWERPC)
        check_extension (altivec)
    elseif (X86)
        foreach (ext sse sse2 sse3 sse4 avx avx2)
            check_extension (${ext})
        endforeach ()
        if (CMAKE_SYSTEM_NAME STREQUAL Linux)
            check_native_define (__MMX__ HAVE_MMX)
            check_native_define (__3dNOW__ HAVE_3DNOW)
        endif ()
    endif ()
    # Check if C++ feature is being turned on/off in the configured compiler flags
    check_feature_enabled (RTTI __GXX_RTTI)
    check_feature_enabled (EXCEPTIONS)
    # Check if C++11 type trait standard is being followed
    check_type_trait (is_trivially_default_constructible)
    check_type_trait (is_trivially_destructible)
    check_type_trait (is_trivially_copy_assignable)
    check_type_trait (is_trivially_copy_constructible)
    if (CMAKE_CXX_COMPILER_ID MATCHES Clang AND NOT IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE AND IS_TRIVIALLY_DESTRUCTIBLE)
        set (CLANG_PRE_STANDARD 1)
    endif ()
endif ()
