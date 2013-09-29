# Define target name
set (TARGET_NAME buildvm)

# Dynasm
set ( DASM ${CMAKE_CURRENT_SOURCE_DIR}/../../../dynasm/dynasm.lua )
set ( DASM_T ${CMAKE_CURRENT_SOURCE_DIR}/../buildvm_arch.h )

# Proper detection of flags
set ( DASM_VER "" )
set ( DASM_FLAGS -D FPU -D HFABI )
set ( DASM_ARCH x86 )

# Raspberry PI, ARM
if ( ${CMAKE_SYSTEM_PROCESSOR} MATCHES "armv6l" )
  set ( DASM_ARCH arm )
  list ( APPEND DASM_FLAGS -D DUALNUM )
  set ( DASM_VER 60 )
endif ()

# Windows is ... special
if ( WIN32 )
  list ( APPEND DASM_FLAGS -D WIN )
endif ()

# 32bit vs 64bit
if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
  list ( APPEND DASM_FLAGS -D P64 )
endif ()

if ( NOT LUAJIT_DISABLE_JIT )
  list ( APPEND DASM_FLAGS -D JIT )
endif ()

if ( NOT LUAJIT_DISABLE_FFI )
  list ( APPEND DASM_FLAGS -D FFI )
endif ()

if ( NOT LUAJIT_CPU_SSE2 )
  list ( APPEND DASM_FLAGS -D SSE2 )
endif ()

list ( APPEND DASM_FLAGS -D VER=${DASM_VER} )
string ( REPLACE ";" " " DASM_FLAGS_STR "${DASM_FLAGS}")

set ( DASM_DASC ${CMAKE_CURRENT_SOURCE_DIR}/../../vm_${DASM_ARCH}.dasc )

# Generate buildvm arch header
add_custom_command(OUTPUT ${DASM_T}
  COMMAND ${PROJECT_ROOT_DIR}/Bin/minilua ${DASM} ${DASM_FLAGS} -o ${DASM_T} ${DASM_DASC}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../dynasm
  DEPENDS minilua
)

# Define source files
file (GLOB C_FILES ../buildvm*.c)
set (SOURCE_FILES ${C_FILES} ${DASM_T})

set (INCLUDE_DIRS_ONLY . ../../)
# Setup target
setup_executable ()
