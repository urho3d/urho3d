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

if (NOT URHO3D_SAMPLES)
    return ()
endif ()

# Set project name
project (Urho3D-Samples)

setup_lint ()

# Find Urho3D library
find_package (Urho3D REQUIRED)
include_directories (${URHO3D_INCLUDE_DIRS})

# Include common to all samples
set (COMMON_SAMPLE_H_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Sample.h" "${CMAKE_CURRENT_SOURCE_DIR}/Sample.inl")

# Define dependency libs
set (INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

# Macro for adding sample subdirectory
macro (add_sample_subdirectory SOURCE_DIR)
    if (DEFINED ENV{included_sample})
        if (DEFINED ENV{INCLUDED_SAMPLE_${SOURCE_DIR}})
            add_subdirectory (${SOURCE_DIR} ${ARGN})
        endif ()
    elseif (NOT DEFINED ENV{EXCLUDED_SAMPLE_${SOURCE_DIR}})
        add_subdirectory (${SOURCE_DIR} ${ARGN})
    endif ()
endmacro ()

# Add samples
file (GLOB_RECURSE DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CMakeLists.txt)
list (SORT DIRS)
foreach (DIR ${DIRS})
    get_filename_component (DIR ${DIR} PATH)
    if (DIR)
        add_sample_subdirectory (${DIR})
    endif ()
endforeach ()
