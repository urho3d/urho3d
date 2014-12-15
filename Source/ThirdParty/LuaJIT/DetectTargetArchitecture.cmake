#
# Copyright (c) 2008-2013 the Urho3D project.
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

# Macro for finding a substring
macro (find_string find_regex input_string output_string)
    if (NOT DEFINED ${output_string})
        message (STATUS "Finding value for LuaJIT:${output_string}")
        string (REGEX MATCH ${find_regex} matched ${input_string})
        if (matched)
            string (REGEX MATCH "\\(.*\\)" captured ${find_regex})
            if (captured) 
                string (REGEX REPLACE ${find_regex} \\1 matched ${matched})
            endif ()
            set (${output_string} ${matched} CACHE INTERNAL "LUAJIT INTERNAL - ${output_string}")
            message (STATUS "Finding value for LuaJIT:${output_string} - found (${matched})")
        else ()
            set (${output_string} 0 CACHE INTERNAL "LUAJIT INTERNAL - ${output_string}")
        endif ()
    endif ()
endmacro ()

# Makefile: Architecture detection
find_string ("LJ_TARGET_(X64|X86|ARM|PPC|PPCSPE|MIPS) 1" "${TARGET_TESTARCH}" TARGET_LJARCH)
if (TARGET_LJARCH)
    string (TOLOWER ${TARGET_LJARCH} TARGET_LJARCH)
    if (TARGET_LJARCH STREQUAL x64 AND NOT URHO3D_64BIT)
        set (TARGET_LJARCH x86)
    endif ()
else ()
    message (FATAL_ERROR "Unsupported target architecture") 
endif () 
if (TARGET_LJARCH STREQUAL mips)
    find_string ("MIPSEL (1)" "${TARGET_TESTARCH}" MIPSEL)
    if (MIPSEL)
        set (TARGET_ARCH ${TARGET_ARCH} -D__MIPSEL__=1)
    endif ()
endif ()

find_string ("LJ_TARGET_PS3 (1)" "${TARGET_TESTARCH}" PS3)
if (PS3)
    set (TARGET_SYS PS3)
    set (TARGET_ARCH ${TARGET_ARCH} -D__CELLOS_LV2__)
    add_definitions (-DLUAJIT_USE_SYSMALLOC)
endif ()

find_string ("LJ_NO_UNWIND (1)" "${TARGET_TESTARCH}" NO_UNWIND)
if (NO_UNWIND)
    set (TARGET_ARCH ${TARGET_ARCH} -DLUAJIT_NO_UNWIND)
endif ()

set (TARGET_ARCH ${TARGET_ARCH} -DLUAJIT_TARGET=LUAJIT_ARCH_${TARGET_LJARCH})

# Makefile: System detection
if (WIN32)
    set (HOST_SYS Windows)
else ()
    execute_process (COMMAND uname -s OUTPUT_VARIABLE HOST_SYS ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
endif ()
if (TARGET_SYS)
    # Makefile: ifneq ($(HOST_SYS),$(TARGET_SYS))
    if (TARGET_SYS STREQUAL Windows)
        set (HOST_XCFLAGS ${HOST_XCFLAGS} -malign-double -DLUAJIT_OS=LUAJIT_OS_WINDOWS)
    elseif (TARGET_SYS STREQUAL Linux)
        set (HOST_XCFLAGS ${HOST_XCFLAGS} -DLUAJIT_OS=LUAJIT_OS_LINUX)
    elseif (TARGET_SYS MATCHES Darwin|iOS)
        set (HOST_XCFLAGS ${HOST_XCFLAGS} -DLUAJIT_OS=LUAJIT_OS_OSX)
    else ()
        set (HOST_XCFLAGS ${HOST_XCFLAGS} -DLUAJIT_OS=LUAJIT_OS_OTHER)
    endif ()
else ()
    set (TARGET_SYS ${HOST_SYS})
endif ()

# Makefile: Files and pathnames
set (DASM_DIR ${BAKED_CMAKE_SOURCE_DIR}/Source/ThirdParty/LuaJIT/dynasm)
set (DASM_ARCH ${TARGET_LJARCH})

# Below regex is a workaround for "LJ_ARCH_BITS (.*?)\\n" as CMake does not understand non-greedy quantifier
find_string ("LJ_ARCH_BITS ([^\\n]*)" "${TARGET_TESTARCH}" ARCH_BITS)
if (ARCH_BITS EQUAL 64)
    if (URHO3D_64BIT)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D P64)
    else ()
        set (ARCH_BITS 32)
    endif ()
endif ()
if (TARGET_SYS)
    if (MSVC)
        message (FATAL_ERROR "MSVC is not able to cross-compile 'buildvm' target at this moment, please use GCC or LLVM/Clang instead.")
    else ()
        string (REGEX REPLACE "-m(32|64) *" "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m${ARCH_BITS}")
    endif ()
endif ()

find_string ("LJ_HASJIT (1)" "${TARGET_TESTARCH}" HASJIT)
if (HASJIT)
    set (DASM_AFLAGS ${DASM_AFLAGS} -D JIT)
endif ()

find_string ("LJ_HASFFI (1)" "${TARGET_TESTARCH}" HASFFI)
if (HASFFI)
    set (DASM_AFLAGS ${DASM_AFLAGS} -D FFI)
endif ()

find_string ("LJ_DUALNUM (1)" "${TARGET_TESTARCH}" DUALNUM)
if (DUALNUM)
    set (DASM_AFLAGS ${DASM_AFLAGS} -D DUALNUM)
endif ()

find_string ("LJ_ARCH_HASFPU (1)" "${TARGET_TESTARCH}" ARCH_HASFPU)
if (ARCH_HASFPU)
    set (DASM_AFLAGS ${DASM_AFLAGS} -D FPU)
endif ()
set (TARGET_ARCH ${TARGET_ARCH} -DLJ_ARCH_HASFPU=${ARCH_HASFPU})

find_string ("LJ_ABI_SOFTFP (1)" "${TARGET_TESTARCH}" ABI_SOFTFP)
if (NOT ABI_SOFTFP)
    set (DASM_AFLAGS ${DASM_AFLAGS} -D HFABI)
endif ()
set (TARGET_ARCH ${TARGET_ARCH} -DLJ_ABI_SOFTFP=${ABI_SOFTFP})

# Below regex is a workaround for "LJ_ARCH_VERSION (.*?)\\n" as CMake does not understand non-greedy quantifier
find_string ("LJ_ARCH_VERSION ([^\\n]*)" "${TARGET_TESTARCH}" ARCH_VERSION)
if (ARCH_VERSION)
    set (DASM_AFLAGS ${DASM_AFLAGS} -D VER=${ARCH_VERSION})
else ()
    set (DASM_AFLAGS ${DASM_AFLAGS} -D VER=)
endif ()

if (TARGET_SYS STREQUAL Windows)
    set (DASM_AFLAGS ${DASM_AFLAGS} -D WIN)
endif ()

if (TARGET_LJARCH STREQUAL x86)
    find_string ("__SSE2__ (1)" "${TARGET_TESTARCH}" SSE2)
    if (SSE2)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D SSE)
    endif ()
elseif (TARGET_LJARCH STREQUAL x64)
    set (DASM_ARCH x86)
elseif (TARGET_LJARCH STREQUAL arm)
    if (TARGET_SYS STREQUAL iOS)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D IOS)
    endif ()
elseif (TARGET_LJARCH STREQUAL ppc)
    find_string ("LJ_ARCH_SQRT (1)" "${TARGET_TESTARCH}" ARCH_SQRT)
    if (ARCH_SQRT)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D SQRT)
    endif ()
    find_string ("LJ_ARCH_ROUND (1)" "${TARGET_TESTARCH}" ARCH_ROUND)
    if (ARCH_ROUND)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D ROUND)
    endif ()
    find_string ("LJ_ARCH_PPC64 (1)" "${TARGET_TESTARCH}" ARCH_PPC64)
    if (ARCH_PPC64)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D GPR64)
    endif ()
    if (TARGET_SYS STREQUAL PS3)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D PPE -D TOC)
    endif ()
endif ()

set (DASM_FLAGS ${DASM_XFLAGS} ${DASM_AFLAGS})
set (DASM_DASC ${BAKED_CMAKE_SOURCE_DIR}/Source/ThirdParty/LuaJIT/src/vm_${DASM_ARCH}.dasc)
