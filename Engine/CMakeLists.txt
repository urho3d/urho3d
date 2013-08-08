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
set (TARGET_NAME Urho3D)
if (URHO3D_BUILD_TYPE STREQUAL SHARED) 
    set (LIB_TYPE SHARED)
endif ()

# Define generated source files
if (WIN32)
    add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/svnversion.h
        COMMAND for /F %%v in ('svnversion -n ${PROJECT_SOURCE_DIR}') do echo const char* revision="%%v"\; >${CMAKE_CURRENT_BINARY_DIR}/svnversion.h DEPENDS ${STATIC_LIBRARY_TARGETS}
        COMMENT "Generating subversion revision number")
else ()
    add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/svnversion.h
        COMMAND for v in `svnversion -n ${PROJECT_SOURCE_DIR}`\; do echo 'const char* revision="'$$v'"\;' >${CMAKE_CURRENT_BINARY_DIR}/svnversion.h\; break\; done DEPENDS ${STATIC_LIBRARY_TARGETS}
        COMMENT "Generating subversion revision number")
endif ()

# Define generated object files
# This is a hack as it relies on internal working of CMake
if (MSVC)
    set (OBJ_EXT .obj)
else ()
    set (OBJ_EXT .o)
endif ()

foreach (TARGET ${STATIC_LIBRARY_TARGETS})
    get_target_property (SOURCES ${TARGET} SOURCES)
    get_target_property (INT_DIR ${TARGET} LOCATION)
    get_filename_component (INT_DIR ${INT_DIR} PATH)
    if (MSVC)
        string (REPLACE /$(Configuration) "" INT_DIR ${INT_DIR})
    endif ()
    set (INT_DIR ${INT_DIR}/CMakeFiles/${TARGET}.dir)
    
    foreach (SOURCE ${SOURCES})
        get_filename_component (NAME ${SOURCE} NAME)
        if (NAME MATCHES \\.c.*$)
            if (MSVC)
                string (REGEX REPLACE \\.c.*$ "" NAME ${NAME}) 
            endif ()
            set (SYS_DIR "")
            if (NOT MSVC)
                get_filename_component (PATH ${SOURCE} PATH)
                foreach (DIR OpenGL Direct3D9 Source source src generated)
                    if (PATH MATCHES /${DIR}$)
                        set (SYS_DIR /${DIR})
                        break ()
                    elseif (PATH MATCHES /${DIR}/)
                        string (REGEX REPLACE .*/${DIR}/ "" SYS_DIR ${PATH})
                        set (SYS_DIR /${DIR}/${SYS_DIR})
                        break ()
                    elseif (PATH MATCHES ^${DIR}/)
                        set (SYS_DIR /${PATH})
                        break ()
                    endif ()
                endforeach ()
            endif ()
            set (OBJ_FILES ${OBJ_FILES} ${INT_DIR}${SYS_DIR}/${NAME}${OBJ_EXT})
        elseif (NAME MATCHES \\.o.*$)
            set (OBJ_FILES ${OBJ_FILES} ${SOURCE})
        endif ()
    endforeach ()
endforeach ()

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES} ${OBJ_FILES} svnversion.h)
set_source_files_properties (${OBJ_FILES} PROPERTIES GENERATED TRUE)

# Define dependency libs
set (INCLUDE_DIRS_ONLY ${CMAKE_CURRENT_BINARY_DIR})
if (MSVC)
    define_dependency_libs (Main)
endif ()

# Setup target
setup_library ()

# Setting up the frameworks for Mac OS X platform
if (APPLE AND LIB_TYPE STREQUAL SHARED)
    setup_macosx_framework (FRAMEWORKS)
    set_target_properties (${TARGET_NAME} PROPERTIES LINK_FLAGS ${FRAMEWORKS})
endif ()
