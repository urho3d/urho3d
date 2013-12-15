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

# Based on src/Makefile from http://luajit.org
# The cross-compiling logic is ported to CMake as verbatim as possible although currently Urho3D does not support all of them

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
# Use -DENABLE_LUAJIT_AMALG=1 to compile LuaJIT core as one huge C file and allows GCC to generate faster and shorter code
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
    
    if (ENABLE_64BIT)
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
            COMMAND egrep "LJ_|MIPSEL|__SSE__" OUTPUT_VARIABLE TARGET_TESTARCH ERROR_QUIET)
    else ()
        execute_process (COMMAND ${CMAKE_C_COMPILER} ${TARGET_TCFLAGS} -E ${CMAKE_CURRENT_SOURCE_DIR}/src/lj_arch.h -dM OUTPUT_VARIABLE TARGET_TESTARCH ERROR_QUIET)
    endif ()
endif ()

# Makefile: Build mode handling
# Urho3D only builds static LuaJIT library

# Makefile: Make targets
# These host tools must be built natively and would be used when cross-compiling
if (CMAKE_CROSSCOMPILING OR IOS)
    # Cross-compiling
    If (IOS)
        set (BUILDVM_X buildvm-ios)
    elseif (ANDROID)
        set (BUILDVM_X buildvm-android)
    elseif (RASPI)
        set (BUILDVM_X buildvm-raspi)
    else ()
        message (FATAL_ERROR "Unsupported cross-compiling target") 
    endif ()
    execute_process (COMMAND ${PROJECT_ROOT_DIR}/Bin/${BUILDVM_X} RESULT_VARIABLE BUILDVM_EXIT_CODE OUTPUT_QUIET ERROR_QUIET)
    if (NOT BUILDVM_EXIT_CODE EQUAL 1)
        file (WRITE ${PROJECT_ROOT_DIR}/Bin/${BUILDVM_X}-arch.txt ${TARGET_TESTARCH})
        message (FATAL_ERROR
            "The configuration cannot be done now because the target-specific '${BUILDVM_X}' tool has not been built yet. "
            "However, the specific target architecture information is now saved. "
            "Reconfigure the desktop native build to incorporate the saved information by calling the respective batch/shell script for native build (it might be the same script as this one). "
            "Then run make or the equivalent command to actually build the missing tool natively. "
            "Finally, after the tool is built, come back to call this batch/shell script again to complete this configuration.")
    endif ()
else ()
    # Not cross-compiling
    set (WARNING "# This is a generated file. DO NOT EDIT!")
    
    # minilua
    configure_file (CMakeLists.txt-minilua.in ${CMAKE_CURRENT_BINARY_DIR}/generated/minilua/CMakeLists.txt @ONLY)
    add_subdirectory (${CMAKE_CURRENT_BINARY_DIR}/generated/minilua generated/minilua)
    
    # buildvm
    configure_file (CMakeLists.txt-buildvm.in ${CMAKE_CURRENT_BINARY_DIR}/generated/buildvm/CMakeLists.txt @ONLY)
    add_subdirectory (${CMAKE_CURRENT_BINARY_DIR}/generated/buildvm generated/buildvm)
    set (BUILDVM_DEP buildvm)
    set (BUILDVM_X buildvm)
    
    # Also build variants for the supported target architectures
    file (GLOB VARIANT_ARCHS ${PROJECT_ROOT_DIR}/Bin/buildvm-*-arch.txt)
    foreach (VARIANT_ARCH ${VARIANT_ARCHS})
        string (REGEX REPLACE "^.*buildvm(-.*)-arch\\.txt$" \\1 VARIANT ${VARIANT_ARCH})
        file (READ ${VARIANT_ARCH} TARGET_TESTARCH)
        configure_file (CMakeLists.txt-buildvm.in ${CMAKE_CURRENT_BINARY_DIR}/generated/buildvm${VARIANT}/CMakeLists.txt @ONLY)
        add_subdirectory (${CMAKE_CURRENT_BINARY_DIR}/generated/buildvm${VARIANT} generated/buildvm${VARIANT})
    endforeach ()
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
    add_custom_command(OUTPUT ${GEN_SRC}
        COMMAND ${PROJECT_ROOT_DIR}/Bin/${BUILDVM_X} -m ${mode} -o ${GEN_SRC} ${ARGN} DEPENDS ${BUILDVM_DEP} ${ARGN}
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
    if (TARGET_LJARCH STREQUAL x64)
        if (ENABLE_64BIT)
            set (CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -m64")
        else ()
            set (CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -m32")
        endif ()
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
endforeach()
generate_source (lj_folddef.h folddef src/lj_opt_fold.c)

# Define source files
if (ENABLE_LUAJIT_AMALG)
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
set (INCLUDE_DIRS_ONLY ${CMAKE_CURRENT_BINARY_DIR}/generated)

# Setup target
setup_library ()

# On Android platform, use 'adb push' to copy the tool(s) from android-Bin to Android (virtual) device; use 'adb shell' to login into a remote shell to execute the tool in the (virtual) device
# The tools are not built on iOS platform as there is no (easy) way to execute them on the iOS device
if (NOT IOS AND (NOT DEFINED ENABLE_TOOLS OR ENABLE_TOOLS))
    # Define target name for LuaJIT interpreter cum compiler
    set (TARGET_NAME luajit_interpreter)   # Note: intended target name is 'luajit' which clashes with 'LuaJIT' library target above for case-insensitive platform

    # Define source files
    set (SOURCE_FILES src/luajit.c)

    # Define dependency libs
    set (LINK_LIBS_ONLY LuaJIT)

    # Setup target
    setup_executable ()
    adjust_target_name ()   # Adjust to intended target output name
endif ()
