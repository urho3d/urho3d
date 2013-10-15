# Define target name
set (TARGET_NAME tolua++)

# Define source files
file (GLOB CPP_FILES *.c)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../../../../ThirdParty/Lua${JIT}/src)
set (LINK_LIBS_ONLY tolua++_static)
if (NOT MSVC)
    set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} m)
endif ()
set (INCLUDE_DIRS_ONLY ../../include)

# Setup target
if (ENABLE_LUAJIT AND ENABLE_64BIT AND APPLE AND NOT IOS)
    setup_macosx_linker_flags (CMAKE_EXE_LINKER_FLAGS)
endif ()
setup_executable ()
