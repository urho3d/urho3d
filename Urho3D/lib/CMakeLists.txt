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

# Define target name
set (TARGET_NAME Urho3D_lib)
if (ENABLE_LIBRARY MATCHES "SHARED|shared") 
    set (LIB_TYPE SHARED)
endif ()

# Define generated source files
if (WIN32)
    add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/svnversion.h
        COMMAND for /F %%v in ('svnversion -n ${PROJECT_SOURCE_DIR}') do echo const char* revision="%%v"\; >${CMAKE_CURRENT_BINARY_DIR}/svnversion.h DEPENDS Urho3D
        COMMENT "Generating subversion revision number")
else ()
    add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/svnversion.h
        COMMAND for v in `svnversion -n ${PROJECT_SOURCE_DIR}`\; do echo 'const char* revision="'$$v'"\;' >${CMAKE_CURRENT_BINARY_DIR}/svnversion.h\; break\; done DEPENDS Urho3D
        COMMENT "Generating subversion revision number")
endif ()

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES} svnversion.h)

# Define dependency libs
set (INCLUDE_DIRS_ONLY ${CMAKE_CURRENT_BINARY_DIR})

# Setup target
setup_library ()
adjust_library_name ()

if (MSVC)
# todo
else ()
    # Setting up the frameworks for Mac OS X platform
    if (APPLE AND LIB_TYPE STREQUAL SHARED)
        setup_macosx_framework (FRAMEWORKS)
    endif ()

    # Linker/Archiver adjustment to include all objects on the fly (works for GCC and Clang)
    set_target_properties (${TARGET_NAME} PROPERTIES RULE_LAUNCH_LINK
        "${CMAKE_SOURCE_DIR}/cmake/Scripts/ExternalObjectLinker.sh OUTDIR ${CMAKE_BINARY_DIR}/CMakeScriptOutput OBJECTS <OBJECTS> TARGETS ${STATIC_LIBRARY_TARGETS} FRAMEWORKS ${FRAMEWORKS} COMMAND")
endif ()
