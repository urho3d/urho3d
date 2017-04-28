# Copyright (c) 2008-2017 the Urho3D project.
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

# Define target name
set (TARGET_NAME ik)

include (CheckIncludeFiles)
check_include_files (stdint.h HAVE_STDINT_H)

# Memory debugging options, non-DEBUG and multi-config generator will set the default to FALSE
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set (DEFAULT_MEMORY_DEBUGGING 1)
endif ()
option (IK_MEMORY_DEBUGGING "Global switch for memory options. Keep track of the number of allocations and de-allocations and prints a report when the program shuts down" ${DEFAULT_MEMORY_DEBUGGING})
cmake_dependent_option (IK_MEMORY_BACKTRACE "Generate backtraces for every malloc(), making it easy to track down memory leaks" "${DEFAULT_MEMORY_DEBUGGING}" "IK_MEMORY_DEBUGGING AND NOT WEB" FALSE)

set (IK_REAL float CACHE STRING "Type to use for real numbers")
option (IK_DOT_OUTPUT "When enabled, the generated chains are dumped to DOT for debug purposes")

# Define source files
define_source_files (GLOB_CPP_PATTERNS src/*.c GLOB_H_PATTERNS include/ik/*.h)
if (IK_MEMORY_BACKTRACE)
    list (APPEND SOURCE_FILES src/platform/linux/backtrace_linux.c)
endif ()

# Define generated source files
set (IK_BUILD_TYPE STATIC)      # Urho always builds its 3rd-party as STATIC lib
configure_file (include/ik/export.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/generated/ik/export.h)
configure_file (include/ik/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/generated/ik/config.h)

# Define dependency libs
set (INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/include/generated include)

# Setup target
setup_library ()

# Install headers for building the Urho3D library
install_header_files (DIRECTORY include/ik/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/ik FILES_MATCHING PATTERN *.h USE_FILE_SYMLINK BUILD_TREE_ONLY)  # Note: the trailing slash is significant
install_header_files (FILES ${CMAKE_CURRENT_BINARY_DIR}/include/generated/ik/export.h ${CMAKE_CURRENT_BINARY_DIR}/include/generated/ik/config.h DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/ik BUILD_TREE_ONLY)
