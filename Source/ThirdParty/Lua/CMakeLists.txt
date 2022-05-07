# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name for Lua library
set (TARGET_NAME Lua)

# Define source files
define_source_files (GLOB_CPP_PATTERNS src/*.c GLOB_H_PATTERNS src/*.h EXCLUDE_PATTERNS src/lua.c src/luac.c)

# Define dependency libs
if (READLINE_FOUND)
    add_definitions (-DLUA_USE_READLINE)
    list (APPEND INCLUDE_DIRS ${READLINE_INCLUDE_DIRS})
    list (APPEND LIBS ${READLINE_LIBRARIES})
endif ()

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library (no direct dependencies but library user may need them)
install_header_files (DIRECTORY src/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/Lua FILES_MATCHING PATTERN *.h)  # Note: the trailing slash is significant

# Setup additional Lua standalone targets (these targets can be transfered and executed on an embedded device, such as Raspberry Pi and Android)
if (NOT CMAKE_PROJECT_NAME MATCHES ^Urho3D-ExternalProject-tolua\\+\\+ AND NOT IOS AND NOT TVOS AND NOT WEB)
    # Define target name for Lua interpreter
    set (TARGET_NAME lua_interpreter)   # Note: intended target name is 'lua' which clashes with 'Lua' library target above for case-insensitive platform

    # Define source files
    set (SOURCE_FILES src/lua.c)

    # Define dependency libs
    set (LIBS Lua)
    if (NOT MSVC)
        list (APPEND LIBS m)
    endif ()

    # Setup target
    setup_executable (NODEPS)
    adjust_target_name ()   # Adjust to intended target output name

    # Define target name for Lua compiler
    set (TARGET_NAME luac)

    # Define source files
    set (SOURCE_FILES src/luac.c)

    # Define dependency libs
    # Same as above

    # Setup target
    setup_executable (NODEPS)
endif ()
