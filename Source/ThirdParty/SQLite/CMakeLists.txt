# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME sqlite)

# Define preprocessor macros
add_definitions (-DSQLITE_USE_URI=1 -DSQLITE_ENABLE_COLUMN_METADATA -DSQLITE_SOUNDEX)   # https://www.sqlite.org/compile.html
if (WEB)
    # Do not use pthread and dl libraries for Web platform
    add_definitions (-DSQLITE_THREADSAFE=0 -DSQLITE_OMIT_LOAD_EXTENSION)
elseif (MINGW)
    # We only support MinGW with "_mingw.h" header file, note the leading underscore
    add_definitions (-D_HAVE__MINGW_H)
endif ()
foreach (VAR HAVE_STDINT_H HAVE_INTTYPES_H HAVE_MALLOC_H HAVE_MALLOC_USABLE_SIZE)
    if (${VAR})
        add_definitions (-D${VAR})
    endif ()
endforeach ()

# Define source files
set (SOURCE_FILES src/sqlite3.c)

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library
install_header_files (DIRECTORY src/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/SQLite FILES_MATCHING PATTERN *.h)  # Note: the trailing slash is significant

# Setup additional SQLite CLI standalone target (this target can be transfered and executed on an embedded device, such as Raspberry Pi and Android)
if (NOT IOS AND NOT TVOS AND NOT WEB)
    # Define target name for SQLite shell
    set (TARGET_NAME sqlite3)

    # Define source files
    set (SOURCE_FILES src/shell.c src/sqlite3.c src/sqlite3.h)

    # Define dependency libs
    if (NOT WIN32)
        set (LIBS dl)
        if (READLINE_FOUND)
            add_definitions (-DHAVE_READLINE)
            list (APPEND INCLUDE_DIRS ${READLINE_INCLUDE_DIRS})
            list (APPEND LIBS ${READLINE_LIBRARIES})
        endif ()
    endif ()

    # Setup target
    setup_executable (NODEPS)
endif ()

# SQLite will not work correctly with the -ffast-math option, so unset it in this scope only
string (REPLACE -ffast-math "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")    # Stringify for string replacement
