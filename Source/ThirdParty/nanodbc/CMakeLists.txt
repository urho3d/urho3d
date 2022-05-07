# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME nanodbc)

# Define source files
define_source_files (GLOB_CPP_PATTERNS nanodbc/*.cpp GLOB_H_PATTERNS nanodbc/*.h)

# Define dependency libs
set (INCLUDE_DIRS .)
if (ODBC_INCLUDE_DIRS)
    LIST (APPEND INCLUDE_DIRS ${ODBC_INCLUDE_DIRS})
endif ()
if (ODBC_DEFINES)
    add_definitions (${ODBC_DEFINES})
endif ()

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library
install_header_files (DIRECTORY nanodbc/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/nanodbc FILES_MATCHING PATTERN *.h)  # Note: the trailing slash is significant
