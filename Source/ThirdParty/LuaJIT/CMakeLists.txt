# Define target name
set (TARGET_NAME LuaJIT)

if ( WIN32 AND NOT CYGWIN )
  # Windows systems
  add_definitions (-DLUAJIT_OS=LUAJIT_OS_WINDOWS)
  set ( LJVM_MODE peobj )  
elseif ( APPLE )
  set ( CMAKE_EXE_LINKER_FLAGS "-pagezero_size 10000 -image_base 100000000 -image_base 7fff04c4a000" )
  set ( LJVM_MODE machasm )
else ()
  set ( LJVM_MODE elfasm )
endif ()

## SOURCES
set ( LJLIB_C
  src/lib_base.c
  src/lib_math.c
  src/lib_bit.c
  src/lib_string.c
  src/lib_table.c
  src/lib_io.c
  src/lib_os.c
  src/lib_debug.c
  src/lib_jit.c
  src/lib_ffi.c
)
if ( LUA_USE_RELATIVE_LOADLIB )
  list ( APPEND LJLIB_C src/lib_package_rel.c )
else ()
  list ( APPEND LJLIB_C src/lib_package.c )
endif ()

macro(add_buildvm_target _target _mode)
  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated/${_target}
    COMMAND ${PROJECT_ROOT_DIR}/Bin/buildvm ARGS -m ${_mode} -o ${CMAKE_CURRENT_BINARY_DIR}/generated/${_target} ${ARGN}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS buildvm ${ARGN}
  )
endmacro(add_buildvm_target)

if ( WIN32 AND NOT CYGWIN )
  add_buildvm_target ( lj_vm.obj peobj )
  set (LJ_VM_SRC ${CMAKE_CURRENT_BINARY_DIR}/generated/lj_vm.obj)
else ()
  add_buildvm_target ( lj_vm.s ${LJVM_MODE} )
  set (LJ_VM_SRC ${CMAKE_CURRENT_BINARY_DIR}/generated/lj_vm.s)
endif ()

add_buildvm_target ( lj_ffdef.h   ffdef   ${LJLIB_C} )
add_buildvm_target ( lj_bcdef.h  bcdef  ${LJLIB_C} )
add_buildvm_target ( lj_folddef.h folddef src/lj_opt_fold.c )
add_buildvm_target ( lj_recdef.h  recdef  ${LJLIB_C} )
add_buildvm_target ( lj_libdef.h  libdef  ${LJLIB_C} )
add_buildvm_target ( jit/vmdef.lua  libvm  ${LJLIB_C} )

SET ( DEPS
  ${LJ_VM_SRC}
  ${CMAKE_CURRENT_BINARY_DIR}/generated/lj_ffdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/generated/lj_bcdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/generated/lj_libdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/generated/lj_recdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/generated/lj_folddef.h
)

## LuaJIT Library
include_directories ( ${CMAKE_CURRENT_BINARY_DIR}/generated dynasm src src/host )

set ( LJCORE_C 
  src/lj_gc.c
  src/lj_err.c
  src/lj_char.c
  src/lj_bc.c
  src/lj_obj.c
  src/lj_str.c
  src/lj_tab.c
  src/lj_func.c
  src/lj_udata.c
  src/lj_meta.c
  src/lj_debug.c
  src/lj_state.c
  src/lj_dispatch.c
  src/lj_vmevent.c
  src/lj_vmmath.c
  src/lj_strscan.c
  src/lj_api.c
  src/lj_lex.c
  src/lj_parse.c
  src/lj_bcread.c
  src/lj_bcwrite.c
  src/lj_load.c
  src/lj_ir.c
  src/lj_opt_mem.c
  src/lj_opt_fold.c
  src/lj_opt_narrow.c
  src/lj_opt_dce.c
  src/lj_opt_loop.c
  src/lj_opt_split.c
  src/lj_opt_sink.c
  src/lj_mcode.c
  src/lj_snap.c
  src/lj_record.c
  src/lj_crecord.c
  src/lj_ffrecord.c
  src/lj_asm.c
  src/lj_trace.c
  src/lj_gdbjit.c
  src/lj_ctype.c
  src/lj_cdata.c
  src/lj_cconv.c
  src/lj_ccall.c
  src/lj_ccallback.c
  src/lj_carith.c
  src/lj_clib.c
  src/lj_cparse.c
  src/lj_lib.c
  src/lj_alloc.c
  src/lib_aux.c
  src/lib_init.c
  ${LJLIB_C}
)

set (SOURCE_FILES ${LJCORE_C} ${DEPS})
set (INCLUDE_DIRS_ONLY ${CMAKE_CURRENT_BINARY_DIR}/generated dynasm src src/host )

# Setup target
setup_library ()
