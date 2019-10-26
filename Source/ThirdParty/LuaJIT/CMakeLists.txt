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

# Based on src/Makefile from http://luajit.org
# The cross-compiling logic is ported to CMake as faithful as possible although currently Urho3D does not support all target archs supported by LuaJIT

if (NOT CMAKE_PROJECT_NAME STREQUAL Urho3D)
    # Set CMake minimum version and CMake policy required by UrhoCommon module
    if (APPLE)
        cmake_minimum_required (VERSION 3.4.1)
    else ()
        cmake_minimum_required (VERSION 3.14.5)
    endif ()
    if (COMMAND cmake_policy)
        # Libraries linked via full path no longer produce linker search paths
        cmake_policy (SET CMP0003 NEW)
        # INTERFACE_LINK_LIBRARIES defines the link interface
        cmake_policy (SET CMP0022 NEW)
        # Disallow use of the LOCATION target property - so we set to OLD as we still need it
        cmake_policy (SET CMP0026 OLD)
        # MACOSX_RPATH is enabled by default
        cmake_policy (SET CMP0042 NEW)
        # Honor the visibility properties for SHARED target types only
        cmake_policy (SET CMP0063 OLD)
    endif ()

    # Set project name
    project (Urho3D-ExternalProject-LuaJIT-${ARCH})

    # Set CMake modules search path
    set (CMAKE_MODULE_PATH ${BAKED_CMAKE_SOURCE_DIR}/CMake/Modules)

    # Include UrhoCommon.cmake module after setting project name
    include (UrhoCommon)

    # When performing Xcode CI build suppress all the warnings for 3rd party libraries because there are just too many of them
    if (XCODE AND DEFINED ENV{CI})
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
    endif ()
elseif (NOT BAKED_CMAKE_SOURCE_DIR)
    set (BAKED_CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR})
endif ()

# Makefile: Compiler options
if (NOT MSVC)
    # Since the assembler part does NOT maintain a frame pointer, it's pointless
    # to slow down the C part by not omitting it. Debugging, tracebacks and
    # unwinding are not affected -- the assembler part has frame unwind
    # information and GCC emits it where needed (x64) or with -g (see CCDEBUG).
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fomit-frame-pointer")
endif ()

# Makefile: Build mode
# When LuaJIT is enabled for Urho3D, always build as static library to be linked against in main Urho3D executable or library CMake target
# Use -DURHO3D_LUAJIT_AMALG=1 to compile LuaJIT core as one huge C file and allows GCC to generate faster and shorter code
# Use -Dxxxxx=0/1/2 as CMake build option to turn off/on the features and debugging support below

# Makefile: Features
#
# Undocumented in the original Makefile yet, but it seems to be a new option which is only used when targeting Xbox One
if (LUAJIT_ENABLE_GC64)
    add_definitions (-DLUAJIT_ENABLE_GC64)
endif ()

# Permanently disable the FFI extension to reduce the size of the LuaJIT
# executable. But please consider that the FFI library is compiled-in,
# but NOT loaded by default. It only allocates any memory, if you actually
# make use of it.
if (LUAJIT_DISABLE_FFI)
    add_definitions (-DLUAJIT_DISABLE_FFI)
endif ()

# Features from Lua 5.2 that are unlikely to break existing code are
# enabled by default. Some other features that *might* break some existing
# code (e.g. __pairs or os.execute() return values) can be enabled here.
# Note: this does not provide full compatibility with Lua 5.2 at this time.
if (LUAJIT_ENABLE_LUA52COMPAT)
    add_definitions (-DLUAJIT_ENABLE_LUA52COMPAT)
endif ()

# Disable the JIT compiler, i.e. turn LuaJIT into a pure interpreter.
if (LUAJIT_DISABLE_JIT)
    add_definitions (-DLUAJIT_DISABLE_JIT)
endif ()

# Some architectures (e.g. PPC) can use either single-number (1) or
# dual-number (2) mode. Uncomment one of these lines to override the
# default mode. Please see LJ_ARCH_NUMMODE in lj_arch.h for details.
if (DEFINED LUAJIT_NUMMODE)
    add_definitions (-DLUAJIT_NUMMODE=${LUAJIT_NUMMODE})
endif ()

# Makefile: Debugging support
# Note that most of these are NOT suitable for benchmarking or release mode!
#
# Use the system provided memory allocator (realloc) instead of the
# bundled memory allocator. This is slower, but sometimes helpful for
# debugging. This option cannot be enabled on x64, since realloc usually
# doesn't return addresses in the right address range.
# OTOH this option is mandatory for Valgrind's memcheck tool on x64 and
# the only way to get useful results from it for all other architectures.
if (LUAJIT_USE_SYSMALLOC)
    add_definitions (-DLUAJIT_USE_SYSMALLOC)
endif ()

# This define is required to run LuaJIT under Valgrind. The Valgrind
# header files must be installed. You should enable debug information, too.
# Use --suppressions=lj.supp to avoid some false positives.
if (LUAJIT_USE_VALGRIND)
    add_definitions (-DLUAJIT_USE_VALGRIND)
endif ()

# This is the client for the GDB JIT API. GDB 7.0 or higher is required
# to make use of it. See lj_gdbjit.c for details. Enabling this causes
# a non-negligible overhead, even when not running under GDB.
if (LUAJIT_USE_GDBJIT)
    add_definitions (-DLUAJIT_USE_GDBJIT)
endif ()

# Turn on assertions for the Lua/C API to debug problems with lua_* calls.
# This is rather slow -- use only while developing C libraries/embeddings.
if (LUA_USE_APICHECK)
    add_definitions (-DLUA_USE_APICHECK)
endif ()

# Turn on assertions for the whole LuaJIT VM. This significantly slows down
# everything. Use only if you suspect a problem with LuaJIT itself.
if (LUA_USE_ASSERT)
    add_definitions (-DLUA_USE_ASSERT)
endif ()

# Makefile: Host system detection.
if (CMAKE_HOST_WIN32)
    set (HOST_SYS Windows)
else ()
    execute_process (COMMAND uname -s OUTPUT_VARIABLE HOST_SYS ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
endif ()

# Macro for finding a substring in TARGET_TESTARCH variable
macro (find_string find_regex output_var)
    message (STATUS "Detecting LuaJIT ${output_var}")
    string (REGEX MATCH ${find_regex} matched "${TARGET_TESTARCH}")     # Stringify to guard against empty string
    if (matched)
        string (REGEX MATCH "\\(.*\\)" captured "${find_regex}")
        if (captured)
            string (REGEX REPLACE ${find_regex} \\1 matched "${matched}")
        endif ()
        set (${output_var} ${matched})
        message (STATUS "Detecting LuaJIT ${output_var} - found (${matched})")
    else ()
        message (STATUS "Detecting LuaJIT ${output_var} - not found")
    endif ()
endmacro ()

# Makefile: Flags and options for host and target
if (NOT LUAJIT_CACHE STREQUAL "${URHO3D_64BIT}-${LUAJIT_DISABLE_FFI}-${LUAJIT_DISABLE_JIT}-${LUAJIT_ENABLE_GC64}-${LUAJIT_NUMMODE}")
    if (MSVC)
        if (URHO3D_64BIT)
            set (MSVC_ARCH_BITS 64)
            set (MSVC_TARGET_ARCH X64)
        else ()
            set (MSVC_ARCH_BITS 32)
            set (MSVC_TARGET_ARCH X86)
        endif ()
        if (LUAJIT_DISABLE_FFI)
            set (MSVC_HASFFI 0)
        else ()
            set (MSVC_HASFFI 1)
        endif ()
        if (LUAJIT_DISABLE_JIT)
            set (MSVC_HASJIT 0)
        else ()
            set (MSVC_HASJIT 1)
        endif ()
        set (TARGET_TESTARCH
            "LJ_TARGET_${MSVC_TARGET_ARCH} 1\n"
            "LJ_ARCH_BITS ${MSVC_ARCH_BITS}\n"
            "LJ_HASFFI ${MSVC_HASFFI}\n"
            "LJ_HASJIT ${MSVC_HASJIT}\n"
            "LJ_ARCH_HASFPU 1\n"
            "LJ_ABI_SOFTFP 0\n")
    else ()
        string (REPLACE " " ";" TARGET_TCFLAGS "${CMAKE_C_FLAGS}")   # Convert string of flags to list of flags
        get_directory_property (COMPILE_DEFINITIONS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMPILE_DEFINITIONS)
        string (REPLACE ";" ";-D" COMPILE_DEFINITIONS "-D${COMPILE_DEFINITIONS}")    # Prefix defines with -D
        if (XCODE)
            if (ARCH)    # The ARCH variable is defined only when we are building LuaJIT for non-native archs using external project
                set (ARCH_FLAGS -arch ${ARCH})
            elseif (ARM)
                if (URHO3D_64BIT)
                    set (ARCH_FLAGS -arch arm64)
                else ()
                    set (ARCH_FLAGS -arch armv7)
                endif ()
            elseif (NOT URHO3D_64BIT)
                set (ARCH_FLAGS -arch i386)
            endif ()
        endif ()
        execute_process (COMMAND egrep -V RESULT_VARIABLE EGREP_EXIT_CODE OUTPUT_QUIET ERROR_QUIET)
        if (EGREP_EXIT_CODE EQUAL 0)
            set (FILTER COMMAND egrep "LJ_|MIPSEL")
        endif ()
        execute_process (COMMAND ${CMAKE_C_COMPILER} ${COMPILE_DEFINITIONS} ${TARGET_TCFLAGS} ${ARCH_FLAGS} ${CMAKE_CURRENT_SOURCE_DIR}/src/lj_arch.h -E -dM
            ${FILTER} OUTPUT_VARIABLE TARGET_TESTARCH ERROR_QUIET)
    endif ()
    find_string ("LJ_TARGET_(X64|X86|ARM|ARM64|PS3|PPC|MIPS) 1" TARGET_LJARCH)
    if (NOT TARGET_LJARCH)
        message (FATAL_ERROR "Unsupported target architecture")
    endif ()
    string (TOLOWER ${TARGET_LJARCH} TARGET_LJARCH)
    if (TARGET_LJARCH STREQUAL ppc)
        find_string ("LJ_LE (1)" LUAJIT_LE)
        if (LUAJIT_LE)
            set (TARGET_ARCH ${TARGET_ARCH} -DLJ_ARCH_ENDIAN=LUAJIT_LE)
        else ()
            set (TARGET_ARCH ${TARGET_ARCH} -DLJ_ARCH_ENDIAN=LUAJIT_BE)
        endif ()
    elseif (TARGET_LJARCH STREQUAL mips)
        find_string ("MIPSEL (1)" MIPSEL)
        if (MIPSEL)
            set (TARGET_ARCH ${TARGET_ARCH} -D__MIPSEL__=1)
        endif ()
    elseif (TARGET_LJARCH STREQUAL ps3)
        set (TARGET_SYS PS3)
        set (TARGET_ARCH ${TARGET_ARCH} -D__CELLOS_LV2__)
        add_definitions (-DLUAJIT_USE_SYSMALLOC)
    endif ()
    set (TARGET_ARCH ${TARGET_ARCH} -DLUAJIT_TARGET=LUAJIT_ARCH_${TARGET_LJARCH})

    # Makefile: Target system detection
    if (IOS OR TVOS)
        set (TARGET_SYS iOS)
    elseif (CMAKE_SYSTEM_NAME STREQUAL Linux)
        set (TARGET_SYS Linux)
    elseif (MINGW)
        set (TARGET_SYS Windows)
    elseif (NOT TARGET_SYS)
        set (TARGET_SYS ${HOST_SYS})
    endif ()
    if (NOT HOST_SYS STREQUAL TARGET_SYS)
        if (TARGET_SYS STREQUAL Windows)
            set (HOST_XCFLAGS ${HOST_XCFLAGS} -malign-double -DLUAJIT_OS=LUAJIT_OS_WINDOWS)
        elseif (TARGET_SYS STREQUAL Linux)
            set (HOST_XCFLAGS ${HOST_XCFLAGS} -DLUAJIT_OS=LUAJIT_OS_LINUX)
        elseif (TARGET_SYS MATCHES Darwin|iOS)
            set (HOST_XCFLAGS ${HOST_XCFLAGS} -DLUAJIT_OS=LUAJIT_OS_OSX)
        else ()
            set (HOST_XCFLAGS ${HOST_XCFLAGS} -DLUAJIT_OS=LUAJIT_OS_OTHER)
        endif ()
    endif ()

    # Makefile: Files and pathnames
    set (DASM_ARCH ${TARGET_LJARCH})
    find_string ("LJ_LE (1)" LITTLE_ENDIAN)
    if (LITTLE_ENDIAN)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D ENDIAN_LE)
    else ()
        set (DASM_AFLAGS ${DASM_AFLAGS} -D ENDIAN_BE)
    endif ()
    find_string ("LJ_ARCH_BITS ([^\\n]*)" ARCH_BITS)    # Workaround for "LJ_ARCH_BITS (.*?)\\n" as CMake does not understand non-greedy quantifier
    if (ARCH_BITS EQUAL 64)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D P64)
    endif ()
    find_string ("LJ_HASJIT (1)" HASJIT)
    if (HASJIT)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D JIT)
    endif ()
    find_string ("LJ_HASFFI (1)" HASFFI)
    if (HASFFI)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D FFI)
    endif ()
    find_string ("LJ_DUALNUM (1)" DUALNUM)
    if (DUALNUM)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D DUALNUM)
    endif ()
    find_string ("LJ_ARCH_HASFPU ([^\\n]*)" ARCH_HASFPU)
    if (ARCH_HASFPU)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D FPU)
    endif ()
    set (TARGET_ARCH ${TARGET_ARCH} -DLJ_ARCH_HASFPU=${ARCH_HASFPU})
    find_string ("LJ_ABI_SOFTFP ([^\\n]*)" ABI_SOFTFP)
    if (NOT ABI_SOFTFP)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D HFABI)
    endif ()
    set (TARGET_ARCH ${TARGET_ARCH} -DLJ_ABI_SOFTFP=${ABI_SOFTFP})
    find_string ("LJ_NO_UNWIND (1)" NO_UNWIND)
    if (NO_UNWIND)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D NO_UNWIND)
        set (TARGET_ARCH ${TARGET_ARCH} -DLUAJIT_NO_UNWIND)
    endif ()
    find_string ("LJ_ARCH_VERSION ([^\\n]*)" ARCH_VERSION)
    set (DASM_AFLAGS ${DASM_AFLAGS} -D VER=${ARCH_VERSION})
    if (TARGET_SYS STREQUAL Windows)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D WIN)
    endif ()
    if (TARGET_LJARCH STREQUAL x64)
        find_string ("LJ_FR2 (1)" TWO_SLOT_FRAME)
        if (NOT TWO_SLOT_FRAME)
            set (DASM_ARCH x86)
        endif ()
    elseif (TARGET_LJARCH STREQUAL arm)
        if (TARGET_SYS STREQUAL iOS)
            set (DASM_AFLAGS ${DASM_AFLAGS} -D IOS)
        endif ()
    elseif (TARGET_LJARCH STREQUAL ppc)
        find_string ("LJ_ARCH_SQRT (1)" ARCH_SQRT)
        if (ARCH_SQRT)
            set (DASM_AFLAGS ${DASM_AFLAGS} -D SQRT)
        endif ()
        find_string ("LJ_ARCH_ROUND (1)" ARCH_ROUND)
        if (ARCH_ROUND)
            set (DASM_AFLAGS ${DASM_AFLAGS} -D ROUND)
        endif ()
        find_string ("LJ_ARCH_PPC32ON64 (1)" ARCH_PPC32ON64)
        if (ARCH_PPC32ON64)
            set (DASM_AFLAGS ${DASM_AFLAGS} -D GPR64)
        endif ()
        if (TARGET_SYS STREQUAL PS3)
            set (DASM_AFLAGS ${DASM_AFLAGS} -D PPE -D TOC)
        endif ()
        find_string ("LJ_ARCH_PPC64 (1)" ARCH_PPC64)
        if (ARCH_PPC64)
            set (DASM_ARCH ppc64)
        endif ()
    endif ()

    set (LUAJIT_CACHE "${URHO3D_64BIT}-${LUAJIT_DISABLE_FFI}-${LUAJIT_DISABLE_JIT}-${LUAJIT_ENABLE_GC64}-${LUAJIT_NUMMODE}" CACHE INTERNAL "LuaJIT - cache invalidator")
    set (TARGET_LJARCH ${TARGET_LJARCH} CACHE INTERNAL "LuaJIT - target architecture")
    set (TARGET_ARCH ${TARGET_ARCH} CACHE INTERNAL "LuaJIT - flags and options for target architecture")
    set (DASM_ARCH ${DASM_ARCH} CACHE INTERNAL "LuaJIT - dynasm architecture")
    set (DASM_FLAGS ${DASM_XFLAGS} ${DASM_AFLAGS} CACHE INTERNAL "LuaJIT - flags for dynasm")
    set (HOST_XCFLAGS ${HOST_XCFLAGS} CACHE INTERNAL "LuaJIT - host compiler flags")
endif ()

# Note that we have intentionally deviated from original Makefile for the following cases
if (NOT MSVC)
    if (LUAJIT_NO_STACK_PROTECTION)
        # Original Makefile attempts to set -fno-stack-protector for non-MSVC compiler whenever it supports this flag, but we decided not to use this flag by default (use LUAJIT_NO_STACK_PROTECTION build option to override)
        execute_process (COMMAND ${CMAKE_COMMAND} -E echo COMMAND ${CMAKE_C_COMPILER} -fno-stack-protector -E - RESULT_VARIABLE EXIT_CODE OUTPUT_QUIET ERROR_QUIET)
        if (EXIT_CODE STREQUAL 0)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-stack-protector")
        endif ()
    endif ()
    if (TARGET_LJARCH STREQUAL x86)
        # Original Makefile enables the SSE when targeting x86 regardless, but we only enable it when URHO3D_SSE build option is also set
        if (URHO3D_SSE)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpmath=sse")     # When URHO3D_SSE is set then -msse -msse2 should be already configured at the global scope
        endif ()
    elseif (TARGET_LJARCH STREQUAL arm64)
        # Original Makefile only sets this flags for 64-bit iOS, but we set it for arm64 in general instead
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-omit-frame-pointer")
    endif ()
endif ()

# Makefile: Build mode handling
# Urho3D only builds static LuaJIT library

# Makefile: Make targets
# The host tool must be built natively
if (CMAKE_CROSSCOMPILING)
    check_native_compiler_exist ()
    # Escape the variables
    foreach (ESCAPED_VAR HOST_XCFLAGS TARGET_ARCH DASM_FLAGS DASM_ARCH)
        string (REPLACE -D +D ${ESCAPED_VAR} "${${ESCAPED_VAR}}")
        string (REPLACE ";" , ${ESCAPED_VAR} "${${ESCAPED_VAR}}")
    endforeach ()
    # When cross-compiling, build the host tool as external project
    include (ExternalProject)
    if (ANDROID AND DEFINED ENV{TRAVIS})
        set (TRAVIS_ANDROID_FIX -DURHO3D_DEPLOYMENT_TARGET=generic)
    endif ()
    if (IOS OR TVOS)
        # When cross-compiling for iOS/tvOS the host environment has been altered by xcodebuild for the said platform, the following fix is required to reset the host environment before spawning another process to configure/generate project file for external project
        # Also workaround a known CMake/Xcode generator bug which prevents it from installing native tool binaries correctly
        set (ALTERNATE_COMMAND CMAKE_COMMAND /usr/bin/env -i PATH=$ENV{PATH} CC=${SAVED_CC} CXX=${SAVED_CXX} CI=$ENV{CI} ${CMAKE_COMMAND} BUILD_COMMAND bash -c "sed -i '' 's/\$$\(EFFECTIVE_PLATFORM_NAME\)//g' CMakeScripts/install_postBuildPhase.make*")
    else ()
        set (ALTERNATE_COMMAND CMAKE_COMMAND ${CMAKE_COMMAND} -E env CC=${SAVED_CC} CXX=${SAVED_CXX} CI=$ENV{CI} ${CMAKE_COMMAND})
    endif ()
    set (TOOL_PATH ${CMAKE_CURRENT_BINARY_DIR}/tool/)
    ExternalProject_Add (buildvm
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/host
        CMAKE_ARGS -DURHO3D_64BIT=${URHO3D_64BIT} -DDEST_RUNTIME_DIR=${TOOL_PATH} -DBAKED_CMAKE_SOURCE_DIR=${BAKED_CMAKE_SOURCE_DIR} -DHOST_XCFLAGS=${HOST_XCFLAGS} -DTARGET_ARCH=${TARGET_ARCH} -DDASM_FLAGS=${DASM_FLAGS} -DDASM_ARCH=${DASM_ARCH} -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}
        ${TRAVIS_ANDROID_FIX}
        ${ALTERNATE_COMMAND})
else ()
    # Otherwise, build it internally as per normal
    set (PRIVATE PRIVATE)
    add_subdirectory (src/host)
endif ()

# Add definitions specific for target C Compiler
if (NOT MSVC)
    # Large file support
    add_definitions (-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE)
    # Buffer overflows check
    add_definitions (-U_FORTIFY_SOURCE)
endif ()

# Define target name for LuaJIT library
set (TARGET_NAME LuaJIT)

# Macro for generating source file
macro (generate_source name mode)
    set (GEN_SRC ${CMAKE_CURRENT_BINARY_DIR}/generated/${name})
    set (GEN_SRCS ${GEN_SRCS} ${GEN_SRC})
    add_custom_command (OUTPUT ${GEN_SRC}
        COMMAND ${TOOL_PATH}buildvm -m ${mode} -o ${GEN_SRC} ${ARGN}
        DEPENDS buildvm ${ARGN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating buildvm output: ${name}")
endmacro ()

# Define generated source files
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated)
if (WIN32)
    set (LJVM_MODE peobj)
    set (LJVM_BOUT lj_vm.obj)
else ()
    set (LJVM_BOUT lj_vm.S)
    enable_language (ASM)
    if (NATIVE_64BIT AND NOT URHO3D_64BIT)  # Not the compiler native ABI, this could only happen on multilib-capable compilers
        set (CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -m32")
    endif ()
    if (APPLE)
        set (LJVM_MODE machasm)
    else ()
        set (LJVM_MODE elfasm)
    endif ()
endif ()
set (LJLIB_C src/lib_base.c src/lib_math.c src/lib_bit.c src/lib_string.c src/lib_table.c
    src/lib_io.c src/lib_os.c src/lib_package.c src/lib_debug.c src/lib_jit.c src/lib_ffi.c)
generate_source (${LJVM_BOUT} ${LJVM_MODE})
foreach (MODE bcdef ffdef libdef recdef)
    generate_source (lj_${MODE}.h ${MODE} ${LJLIB_C})
endforeach ()
generate_source (vmdef.lua vmdef ${LJLIB_C})
generate_source (lj_folddef.h folddef src/lj_opt_fold.c)

# Define source files
if (URHO3D_LUAJIT_AMALG)
    set (LJCORE_C src/ljamalg.c)
else ()
    set (LJCORE_C src/lj_gc.c src/lj_err.c src/lj_char.c src/lj_bc.c src/lj_obj.c src/lj_buf.c
        src/lj_str.c src/lj_tab.c src/lj_func.c src/lj_udata.c src/lj_meta.c src/lj_debug.c
        src/lj_state.c src/lj_dispatch.c src/lj_vmevent.c src/lj_vmmath.c src/lj_strscan.c
        src/lj_strfmt.c src/lj_strfmt_num.c src/lj_api.c src/lj_profile.c
        src/lj_lex.c src/lj_parse.c src/lj_bcread.c src/lj_bcwrite.c src/lj_load.c
        src/lj_ir.c src/lj_opt_mem.c src/lj_opt_fold.c src/lj_opt_narrow.c
        src/lj_opt_dce.c src/lj_opt_loop.c src/lj_opt_split.c src/lj_opt_sink.c
        src/lj_mcode.c src/lj_snap.c src/lj_record.c src/lj_crecord.c src/lj_ffrecord.c
        src/lj_asm.c src/lj_trace.c src/lj_gdbjit.c
        src/lj_ctype.c src/lj_cdata.c src/lj_cconv.c src/lj_ccall.c src/lj_ccallback.c
        src/lj_carith.c src/lj_clib.c src/lj_cparse.c
        src/lj_lib.c src/lj_alloc.c src/lib_aux.c
        ${LJLIB_C} src/lib_init.c)
endif ()
set (SOURCE_FILES ${LJCORE_C} ${GEN_SRCS})

# Define dependency libs
set (INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/generated)

# Setup target
if (XCODE)
    if (ARCH)
        list (APPEND TARGET_PROPERTIES XCODE_ATTRIBUTE_ARCHS ${ARCH})
    elseif (URHO3D_64BIT OR ARM)
        set (EXCLUDE_FROM_ALL EXCLUDE_FROM_ALL)
        list (APPEND TARGET_PROPERTIES XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH YES)
        if (URHO3D_64BIT AND ARM)
            list (APPEND TARGET_PROPERTIES XCODE_ATTRIBUTE_ARCHS arm64)     # The ARCHS_STANDARD builds armv7 first, but we have setup LuaJIT target detection to detect arm64 as the default arch so we override Xcode to build arm64 first
        endif ()
    endif ()
endif ()
setup_library (${EXCLUDE_FROM_ALL})
if (XCODE AND NOT ARCH)    # These variables are used to control the recursion as this script is recursive in nature on Xcode
    # Add external and custom targets to build Mach-O universal binary LuaJIT sub-library
    include (ExternalProject)
    foreach (LUAJIT_OPT LUAJIT_ENABLE_GC64 LUAJIT_DISABLE_FFI LUAJIT_ENABLE_LUA52COMPAT LUAJIT_DISABLE_JIT LUAJIT_NUMMODE LUAJIT_USE_SYSMALLOC LUAJIT_USE_VALGRIND LUAJIT_USE_GDBJIT LUA_USE_APICHECK LUA_USE_ASSERT LUAJIT_NO_STACK_PROTECTION IOS IPHONEOS_DEPLOYMENT_TARGET TVOS APPLETVOS_DEPLOYMENT_TARGET URHO3D_LUAJIT_AMALG BAKED_CMAKE_SOURCE_DIR)
        if (DEFINED ${LUAJIT_OPT})
            list (APPEND LUAJIT_PASSTHRU_OPTS -D${LUAJIT_OPT}=${${LUAJIT_OPT}})
        endif ()
    endforeach ()
    if (IOS OR TVOS)
        set (ALTERNATE_COMMAND CMAKE_COMMAND /usr/bin/env -i PATH=$ENV{PATH} CI=$ENV{CI} ${CMAKE_COMMAND})
    else ()
        set (ALTERNATE_COMMAND CMAKE_COMMAND ${CMAKE_COMMAND} -E env CI=$ENV{CI} ${CMAKE_COMMAND})
    endif ()
    # There is a CMake bug where a mere reference to a target using generator-expression would cause it to be added as dependency, we have to use a hack to workaround this bug
    if (IOS)
        if (NOT IPHONEOS_DEPLOYMENT_TARGET STREQUAL "" AND IPHONEOS_DEPLOYMENT_TARGET VERSION_LESS 11.0)
            ExternalProject_Add (${TARGET_NAME}_i386
                SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
                CMAKE_ARGS -DARCH=i386 -DINSTALL_ARCHIVE_DIR=${CMAKE_CURRENT_BINARY_DIR} -DURHO3D_64BIT=0 ${LUAJIT_PASSTHRU_OPTS} ${ALTERNATE_COMMAND} BUILD_COMMAND "" INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install --config $<CONFIG> -- -sdk iphonesimulator)
            if (URHO3D_64BIT)
                # 64-bit iOS universal binaries: for iPhoneOS SDK contains arm64 and armv7 archs, and for iPhoneSimulator SDK contains x86_64 and i386 archs
                ExternalProject_Add (${TARGET_NAME}_x86_64
                    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
                    CMAKE_ARGS -DARCH=x86_64 -DINSTALL_ARCHIVE_DIR=${CMAKE_CURRENT_BINARY_DIR} ${LUAJIT_PASSTHRU_OPTS} ${ALTERNATE_COMMAND} BUILD_COMMAND "" INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install --config $<CONFIG> -- -sdk iphonesimulator)
                add_custom_target (${TARGET_NAME}_universal-iphonesimulator
                    COMMAND if [ '$(CONFIGURATION)' == 'Debug' ]\; then if [ '$(ARCHS)' == 'x86_64' ]\; then rm -f ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>-iphonesimulator/lib${TARGET_NAME}.a && arch=x86_64\; else arch=i386\; fi && xcodebuild -target ${TARGET_NAME}_$$arch -configuration $(CONFIGURATION) && cp -p ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>-iphonesimulator/lib${TARGET_NAME}.a{.$$arch,}\; elif lipo -info ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>-iphonesimulator/lib${TARGET_NAME}.a 2>/dev/null |egrep -cq 'i386.*x86_64|x86_64.*i386'\; then echo Already a Mach-O universal binary library\; else for arch in _x86_64 _i386\; do xcodebuild -target ${TARGET_NAME}$$arch -configuration $(CONFIGURATION)\; done && lipo -create -output ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>-iphonesimulator/lib${TARGET_NAME}.a{,.x86_64,.i386}\; fi
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
                ExternalProject_Add (${TARGET_NAME}_armv7
                    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
                    CMAKE_ARGS -DARCH=armv7 -DINSTALL_ARCHIVE_DIR=${CMAKE_CURRENT_BINARY_DIR} -DURHO3D_64BIT=0 ${LUAJIT_PASSTHRU_OPTS} ${ALTERNATE_COMMAND} BUILD_COMMAND "" INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install --config $<CONFIG>)
                add_custom_target (${TARGET_NAME}_universal-iphoneos
                    COMMAND if [ '$(CONFIGURATION)' == 'Debug' ]\; then if [ '$(ARCHS)' == 'arm64' ]\; then rm -f ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>-iphoneos/lib${TARGET_NAME}.a && arch=\; else arch=_armv7\; fi && xcodebuild -target ${TARGET_NAME}$$arch -configuration $(CONFIGURATION) && if [ $$arch ]\; then cp -p ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>-iphoneos/lib${TARGET_NAME}.a{.armv7,}\; fi\; elif lipo -info ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>-iphoneos/lib${TARGET_NAME}.a 2>/dev/null |egrep -cq 'armv7.*arm64|arm64.*armv7'\; then echo Already a Mach-O universal binary library\; else for arch in \"\" _armv7\; do xcodebuild -target ${TARGET_NAME}$$arch -configuration $(CONFIGURATION)\; done && mv ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>-iphoneos/lib${TARGET_NAME}.a{,.arm64} && lipo -create -output ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>-iphoneos/lib${TARGET_NAME}.a{,.arm64,.armv7}\; fi
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
            else ()
                # 32-bit iOS universal binary contains both armv7 (iPhoneOS) and i386 (iPhoneSimulator) archs
                add_custom_target (${TARGET_NAME}_universal-iphonesimulator
                    COMMAND xcodebuild -target ${TARGET_NAME}_i386 -configuration $(CONFIGURATION) && cp -p ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>-iphonesimulator/lib${TARGET_NAME}.a{.i386,}
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
                add_custom_target (${TARGET_NAME}_universal-iphoneos
                    COMMAND xcodebuild -target ${TARGET_NAME} -configuration $(CONFIGURATION)
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
            endif ()
            add_custom_target (${TARGET_NAME}_universal ALL
                COMMAND if [ '$(CONFIGURATION)' != 'Debug' ] || echo '$(ARCHS)' |grep -cq arm\; then xcodebuild ARCHS="$(ARCHS)" -target ${TARGET_NAME}_universal-iphoneos -configuration $(CONFIGURATION)\; fi
                COMMAND if [ '$(CONFIGURATION)' != 'Debug' ] || echo '$(ARCHS)' |grep -cq 86\; then xcodebuild ARCHS="$(ARCHS)" -target ${TARGET_NAME}_universal-iphonesimulator -configuration $(CONFIGURATION)\; fi
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                COMMENT "Creating Mach-O universal binary LuaJIT library")
        else ()
            # Since version 11.x iOS does not support 32-bit archs anymore
            ExternalProject_Add (${TARGET_NAME}_x86_64
                SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
                CMAKE_ARGS -DARCH=x86_64 -DINSTALL_ARCHIVE_DIR=${CMAKE_CURRENT_BINARY_DIR} ${LUAJIT_PASSTHRU_OPTS} ${ALTERNATE_COMMAND} BUILD_COMMAND "" INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install --config $<CONFIG> -- -sdk iphonesimulator)
            add_custom_target (${TARGET_NAME}_universal-iphonesimulator
                COMMAND xcodebuild -target ${TARGET_NAME}_x86_64 -configuration $(CONFIGURATION) && cp -p ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>-iphonesimulator/lib${TARGET_NAME}.a{.x86_64,}
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
            add_custom_target (${TARGET_NAME}_universal-iphoneos
                COMMAND xcodebuild -target ${TARGET_NAME} -configuration $(CONFIGURATION)
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
            add_custom_target (${TARGET_NAME}_universal ALL
                COMMAND if [ '$(CONFIGURATION)' != 'Debug' ] || echo '$(ARCHS)' |grep -cq arm\; then xcodebuild ARCHS="$(ARCHS)" -target ${TARGET_NAME}_universal-iphoneos -configuration $(CONFIGURATION)\; fi
                COMMAND if [ '$(CONFIGURATION)' != 'Debug' ] || echo '$(ARCHS)' |grep -cq 86\; then xcodebuild ARCHS="$(ARCHS)" -target ${TARGET_NAME}_universal-iphonesimulator -configuration $(CONFIGURATION)\; fi
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                COMMENT "Creating Mach-O universal binary LuaJIT library")
        endif ()
    elseif (TVOS)
        # 64-bit tvOS universal binary contains both arm64 (AppleTVOS) and x86_64 (AppleTVSimulator) archs
        ExternalProject_Add (${TARGET_NAME}_x86_64
            SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
            CMAKE_ARGS -DARCH=x86_64 -DINSTALL_ARCHIVE_DIR=${CMAKE_CURRENT_BINARY_DIR} ${LUAJIT_PASSTHRU_OPTS} ${ALTERNATE_COMMAND} BUILD_COMMAND "" INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install --config $<CONFIG> -- -sdk appletvsimulator)
        add_custom_target (${TARGET_NAME}_universal-appletvsimulator
            COMMAND xcodebuild -target ${TARGET_NAME}_x86_64 -configuration $(CONFIGURATION) && cp -p ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>-appletvsimulator/lib${TARGET_NAME}.a{.x86_64,}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
        add_custom_target (${TARGET_NAME}_universal-appletvos
            COMMAND xcodebuild -target ${TARGET_NAME} -configuration $(CONFIGURATION)
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
        add_custom_target (${TARGET_NAME}_universal ALL
            COMMAND if [ '$(CONFIGURATION)' != 'Debug' ] || echo '$(ARCHS)' |grep -cq arm\; then xcodebuild ARCHS="$(ARCHS)" -target ${TARGET_NAME}_universal-appletvos -configuration $(CONFIGURATION)\; fi
            COMMAND if [ '$(CONFIGURATION)' != 'Debug' ] || echo '$(ARCHS)' |grep -cq 86\; then xcodebuild ARCHS="$(ARCHS)" -target ${TARGET_NAME}_universal-appletvsimulator -configuration $(CONFIGURATION)\; fi
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Creating Mach-O universal binary LuaJIT library")
    elseif (URHO3D_UNIVERSAL)
        # macOS universal binary contains both x86_86 and i386 archs
        ExternalProject_Add (${TARGET_NAME}_i386
            SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
            CMAKE_ARGS -DARCH=i386 -DINSTALL_ARCHIVE_DIR=${CMAKE_CURRENT_BINARY_DIR} -DURHO3D_64BIT=0 ${LUAJIT_PASSTHRU_OPTS} ${ALTERNATE_COMMAND})
        add_custom_target (${TARGET_NAME}_universal ALL
            COMMAND if [ '$(CONFIGURATION)' == 'Debug' ]\; then if [ '$(ARCHS)' == 'x86_64' ]\; then rm -f ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>/lib${TARGET_NAME}.a && arch=\; else arch=_i386\; fi && xcodebuild -target ${TARGET_NAME}$$arch -configuration $(CONFIGURATION) && if [ $$arch ]\; then cp -p ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>/lib${TARGET_NAME}.a{.i386,}\; fi\; elif lipo -info ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>/lib${TARGET_NAME}.a 2>/dev/null |egrep -cq 'i386.*x86_64|x86_64.*i386'\; then echo Already a Mach-O universal binary library\; else for arch in \"\" _i386\; do xcodebuild -target ${TARGET_NAME}$$arch -configuration $(CONFIGURATION)\; done && mv ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>/lib${TARGET_NAME}.a{,.x86_64} && lipo -create -output ${CMAKE_BINARY_DIR}/Source/ThirdParty/${TARGET_NAME}/$<CONFIG>/lib${TARGET_NAME}.a{,.x86_64,.i386}\; fi
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Creating Mach-O universal binary LuaJIT library")
    endif ()
elseif (INSTALL_ARCHIVE_DIR)
    # This is a hack as it relies on CMake internal implementation
    install (FILES $<TARGET_FILE:${TARGET_NAME}> DESTINATION ${INSTALL_ARCHIVE_DIR}/$<CONFIG>\${EFFECTIVE_PLATFORM_NAME} RENAME lib${TARGET_NAME}.a.${ARCH})
endif ()

# Install headers for building and using the Urho3D library (no direct dependencies but library user may need them)
install_header_files (DIRECTORY src/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/LuaJIT FILES_MATCHING PATTERN *.h *.hpp)  # Note: the trailing slash is significant

# Setup additional Lua standalone target (this target can be transfered and executed on an embedded device, such as Raspberry Pi and Android)
if (NOT CMAKE_PROJECT_NAME MATCHES ^Urho3D-ExternalProject-LuaJIT AND NOT IOS AND NOT TVOS AND NOT WEB)
    # Define target name for LuaJIT interpreter cum compiler
    set (TARGET_NAME luajit_interpreter)   # Note: intended target name is 'luajit' which clashes with 'LuaJIT' library target above for case-insensitive platform

    # Define source files
    set (SOURCE_FILES src/luajit.c)

    # Define dependency libs
    if (NOT TARGET LuaJIT_universal)
        set (LIBS LuaJIT)
    endif ()
    if (NOT MSVC)
        list (APPEND LIBS m)
    endif ()

    # Setup target
    setup_executable (NODEPS)
    adjust_target_name ()   # Adjust to intended target output name
    if (TARGET LuaJIT_universal)
        add_dependencies (${TARGET_NAME} LuaJIT_universal)
        target_link_libraries (${TARGET_NAME} ${CMAKE_BINARY_DIR}/Source/ThirdParty/LuaJIT/$<CONFIG>/libLuaJIT.a)   # This is a hack as CMake does not allow custom target in generator-expression, like $<TARGET_FILE:LuaJIT_universal>
    endif ()

    # Define post build steps
    set (LUAJIT_DEP_DIR ${CMAKE_BINARY_DIR}/bin/jit)
    add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/src/jit ${LUAJIT_DEP_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/generated/vmdef.lua ${LUAJIT_DEP_DIR}
        COMMENT "Copying dependency files for luajit standalone executable")
    add_make_clean_files (${LUAJIT_DEP_DIR})

    # Install dependency files required by luajit
    if (DEST_RUNTIME_DIR)
        install (DIRECTORY ${LUAJIT_DEP_DIR} DESTINATION ${DEST_RUNTIME_DIR})
    endif ()
endif ()

# Add directory containing the dependency files into the LuaJIT module search path
set (LUA_RDIR ./)     # Relative directory
set (LUA_IDIR ${CMAKE_INSTALL_PREFIX}/${DEST_RUNTIME_DIR}/)     # Installation directory
add_definitions (-DLUA_RDIR="${LUA_RDIR}" -DLUA_IDIR="${LUA_IDIR}")
