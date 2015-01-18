#
# Copyright (c) 2008-2014 the Urho3D project.
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
# debugging. It's helpful for Valgrind's memcheck tool, too. This option
# cannot be enabled on x64, since the built-in allocator is mandatory.
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

# Makefile: Flags and options for host and target
if (MSVC)
    if (LUAJIT_DISABLE_FFI)
        set (MSVC_HASFFI 0)
    else ()
        set (MSVC_HASFFI 1)
    endif ()
    set (TARGET_TESTARCH "LJ_HASFFI ${MSVC_HASFFI}\n")
    
    if (LUAJIT_DISABLE_JIT)
        set (MSVC_HASJIT 0)
    else ()
        set (MSVC_HASJIT 1)
    endif ()
    set (TARGET_TESTARCH "${TARGET_TESTARCH} LJ_HASJIT ${MSVC_HASJIT}\n")
    
    if (URHO3D_64BIT)
        set (MSVC_ARCH_BITS 64)
        set (MSVC_TARGET_ARCH X64)
    else ()
        set (MSVC_ARCH_BITS 32)
        set (MSVC_TARGET_ARCH X86)
    endif ()
    set (TARGET_TESTARCH "${TARGET_TESTARCH} LJ_ARCH_BITS ${MSVC_ARCH_BITS}\n")
    set (TARGET_TESTARCH "${TARGET_TESTARCH} LJ_TARGET_${MSVC_TARGET_ARCH} 1\n")

	# More assumptions
    set (TARGET_TESTARCH "${TARGET_TESTARCH} LJ_ARCH_HASFPU 1\n")
    set (TARGET_TESTARCH "${TARGET_TESTARCH} LJ_ABI_SOFTFP 0\n")
else ()
    get_directory_property (TARGET_TCFLAGS COMPILE_DEFINITIONS)
    string (REPLACE ";" ";-D" TARGET_TCFLAGS ";${TARGET_TCFLAGS}")
    execute_process (COMMAND egrep -V RESULT_VARIABLE EGREP_EXIT_CODE OUTPUT_QUIET ERROR_QUIET)    
    if (EGREP_EXIT_CODE EQUAL 0)
        execute_process (COMMAND ${CMAKE_C_COMPILER} ${TARGET_TCFLAGS} -E ${CMAKE_CURRENT_SOURCE_DIR}/src/lj_arch.h -dM
            COMMAND egrep "LJ_|MIPSEL|__SSE2__" OUTPUT_VARIABLE TARGET_TESTARCH ERROR_QUIET)
    else ()
        execute_process (COMMAND ${CMAKE_C_COMPILER} ${TARGET_TCFLAGS} -E ${CMAKE_CURRENT_SOURCE_DIR}/src/lj_arch.h -dM OUTPUT_VARIABLE TARGET_TESTARCH ERROR_QUIET)
    endif ()
endif ()

# Macro for finding a substring in TARGET_TESTARCH variable
macro (find_string find_regex output_var)
    if (NOT DEFINED ${output_var})
        message (STATUS "Finding value for LuaJIT:${output_var}")
        string (REGEX MATCH ${find_regex} matched ${TARGET_TESTARCH})
        if (matched)
            string (REGEX MATCH "\\(.*\\)" captured ${find_regex})
            if (captured) 
                string (REGEX REPLACE ${find_regex} \\1 matched ${matched})
            endif ()

            # Special case handling to cater for URHO3D_64BIT build option
            if (${output_var} STREQUAL TARGET_LJARCH)
                string (TOLOWER ${matched} matched)
                if (matched STREQUAL x64 AND NOT URHO3D_64BIT)
                    set (matched x86)
                endif ()
            elseif (${output_var} STREQUAL ARCH_BITS)
                if (matched EQUAL 64 AND NOT URHO3D_64BIT)
                    set (matched 32)
                endif ()
            endif ()

            set (${output_var} ${matched} CACHE INTERNAL "LUAJIT INTERNAL - ${output_var}")
            message (STATUS "Finding value for LuaJIT:${output_var} - found (${matched})")
        else ()
            set (${output_var} 0 CACHE INTERNAL "LUAJIT INTERNAL - ${output_var}")
            message (STATUS "Finding value for LuaJIT:${output_var} - not found")
        endif ()
    endif ()
endmacro ()

find_string ("LJ_TARGET_(X64|X86|ARM|PPC|PPCSPE|MIPS) 1" TARGET_LJARCH)
if (NOT TARGET_LJARCH)
    message (FATAL_ERROR "Unsupported target architecture")
endif ()
if (TARGET_LJARCH STREQUAL mips)
    find_string ("MIPSEL (1)" MIPSEL)
    if (MIPSEL)
        set (TARGET_ARCH ${TARGET_ARCH} -D__MIPSEL__=1)
    endif ()
endif ()

find_string ("LJ_TARGET_PS3 (1)" PS3)
if (PS3)
    set (TARGET_SYS PS3)
    set (TARGET_ARCH ${TARGET_ARCH} -D__CELLOS_LV2__)
    add_definitions (-DLUAJIT_USE_SYSMALLOC)
endif ()

find_string ("LJ_NO_UNWIND (1)" NO_UNWIND)
if (NO_UNWIND)
    set (TARGET_ARCH ${TARGET_ARCH} -DLUAJIT_NO_UNWIND)
endif ()

set (TARGET_ARCH ${TARGET_ARCH} -DLUAJIT_TARGET=LUAJIT_ARCH_${TARGET_LJARCH})

# Makefile: System detection
if (CMAKE_HOST_WIN32)
    set (HOST_SYS Windows)
else ()
    execute_process (COMMAND uname -s OUTPUT_VARIABLE HOST_SYS ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
endif ()
if (IOS)
    set (TARGET_SYS iOS)
elseif (ANDROID OR RPI)
    set (TARGET_SYS Linux)
elseif (MINGW)
    set (TARGET_SYS Windows)
elseif (NOT TARGET_SYS)
    set (TARGET_SYS ${HOST_SYS})
endif ()
if (NOT HOST_SYST STREQUAL TARGET_SYS)
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
if (NOT BAKED_CMAKE_SOURCE_DIR)
    set (BAKED_CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR})
endif ()
set (DASM_ARCH ${TARGET_LJARCH})

# Below regex is a workaround for "LJ_ARCH_BITS (.*?)\\n" as CMake does not understand non-greedy quantifier
find_string ("LJ_ARCH_BITS ([^\\n]*)" ARCH_BITS)
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

find_string ("LJ_ARCH_HASFPU (1)" ARCH_HASFPU)
if (ARCH_HASFPU)
    set (DASM_AFLAGS ${DASM_AFLAGS} -D FPU)
endif ()
set (TARGET_ARCH ${TARGET_ARCH} -DLJ_ARCH_HASFPU=${ARCH_HASFPU})

find_string ("LJ_ABI_SOFTFP (1)" ABI_SOFTFP)
if (NOT ABI_SOFTFP)
    set (DASM_AFLAGS ${DASM_AFLAGS} -D HFABI)
endif ()
set (TARGET_ARCH ${TARGET_ARCH} -DLJ_ABI_SOFTFP=${ABI_SOFTFP})

# Below regex is a workaround for "LJ_ARCH_VERSION (.*?)\\n" as CMake does not understand non-greedy quantifier
find_string ("LJ_ARCH_VERSION ([^\\n]*)" ARCH_VERSION)
set (DASM_AFLAGS ${DASM_AFLAGS} -D VER=${ARCH_VERSION})

if (TARGET_SYS STREQUAL Windows)
    set (DASM_AFLAGS ${DASM_AFLAGS} -D WIN)
endif ()

if (TARGET_LJARCH STREQUAL x86)
    find_string ("__SSE2__ (1)" SSE2)
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
    find_string ("LJ_ARCH_SQRT (1)" ARCH_SQRT)
    if (ARCH_SQRT)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D SQRT)
    endif ()
    find_string ("LJ_ARCH_ROUND (1)" ARCH_ROUND)
    if (ARCH_ROUND)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D ROUND)
    endif ()
    find_string ("LJ_ARCH_PPC64 (1)" ARCH_PPC64)
    if (ARCH_PPC64)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D GPR64)
    endif ()
    if (TARGET_SYS STREQUAL PS3)
        set (DASM_AFLAGS ${DASM_AFLAGS} -D PPE -D TOC)
    endif ()
endif ()

set (DASM_FLAGS ${DASM_XFLAGS} ${DASM_AFLAGS})

# Makefile: Build mode handling
# Urho3D only builds static LuaJIT library

# Makefile: Make targets
# The host tool must be built natively
if (CMAKE_CROSSCOMPILING OR IOS)
    # Escape the variables
    foreach (ESCAPED_VAR HOST_XCFLAGS TARGET_ARCH DASM_FLAGS DASM_ARCH)
        string (REPLACE -D +D ${ESCAPED_VAR} "${${ESCAPED_VAR}}")
        string (REPLACE ";" , ${ESCAPED_VAR} "${${ESCAPED_VAR}}")
    endforeach ()
    # When cross-compiling, build the host tool as external project
    include (ExternalProject)
    ExternalProject_Add(buildvm
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/host
        CMAKE_ARGS -DURHO3D_64BIT=${URHO3D_64BIT} -DDEST_RUNTIME_DIR=${CMAKE_BINARY_DIR}/bin/tool -DBAKED_CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR} -DHOST_XCFLAGS=${HOST_XCFLAGS} -DTARGET_ARCH=${TARGET_ARCH} -DDASM_FLAGS=${DASM_FLAGS} -DDASM_ARCH=${DASM_ARCH}
    )
else ()
    # Otherwise, build it internally as per normal
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
        COMMAND ${CMAKE_BINARY_DIR}/bin/tool/buildvm -m ${mode} -o ${GEN_SRC} ${ARGN}
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
    set (LJVM_BOUT lj_vm.s)
    enable_language (ASM)
    set (CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${DASH_MBIT}")
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
    set (LJCORE_C src/lj_gc.c src/lj_err.c src/lj_char.c src/lj_bc.c src/lj_obj.c
        src/lj_str.c src/lj_tab.c src/lj_func.c src/lj_udata.c src/lj_meta.c src/lj_debug.c
        src/lj_state.c src/lj_dispatch.c src/lj_vmevent.c src/lj_vmmath.c src/lj_strscan.c
        src/lj_api.c src/lj_lex.c src/lj_parse.c src/lj_bcread.c src/lj_bcwrite.c src/lj_load.c
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
setup_library ()

# Install headers for building and using the Urho3D library (no direct dependencies but library user may need them)
install_header_files (DIRECTORY src/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/LuaJIT FILES_MATCHING PATTERN *.h *.hpp)  # Note: the trailing slash is significant

# Setup additional Lua standalone target (this target can be transfered and executed on an embedded device, such as Raspberry Pi and Android)
if (NOT IOS)
    # Define target name for LuaJIT interpreter cum compiler
    set (TARGET_NAME luajit_interpreter)   # Note: intended target name is 'luajit' which clashes with 'LuaJIT' library target above for case-insensitive platform

    # Define source files
    set (SOURCE_FILES src/luajit.c)

    # Define dependency libs
    set (LIBS LuaJIT)
    if (NOT MSVC)
        list (APPEND LIBS m)
    endif ()

    # Setup target
    setup_executable (NODEPS)
    adjust_target_name ()   # Adjust to intended target output name

    # Define post build steps
    set (LUAJIT_DEP_DIR ${CMAKE_BINARY_DIR}/bin/jit)
    add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/src/jit ${LUAJIT_DEP_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/generated/vmdef.lua ${LUAJIT_DEP_DIR}
        COMMENT "Copying dependency files for luajit standalone executable")

    # Install dependency files required by luajit
    install (DIRECTORY ${LUAJIT_DEP_DIR} DESTINATION ${DEST_RUNTIME_DIR} ${DEST_PERMISSIONS})
endif ()

# Add directory containing the dependency files into the LuaJIT module search path
set (LUA_RDIR ./)     # Relative directory
set (LUA_IDIR ${CMAKE_INSTALL_PREFIX}/${DEST_RUNTIME_DIR}/)     # Installation directory
add_definitions (-DLUA_RDIR="${LUA_RDIR}" -DLUA_IDIR="${LUA_IDIR}")
