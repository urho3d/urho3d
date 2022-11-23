# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

if (NOT URHO3D_SAMPLES)
    return ()
endif ()

# Set project name
project (Urho3D-Samples)

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
