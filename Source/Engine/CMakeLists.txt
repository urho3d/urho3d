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
execute_process (COMMAND git describe --always WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} RESULT_VARIABLE GIT_EXIT_CODE OUTPUT_QUIET ERROR_QUIET)
if (GIT_EXIT_CODE EQUAL 0)
    if (WIN32)
        add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gitversion.h
            COMMAND for /F %%v in ('git describe --always --dirty') do echo const char* revision="%%v"\; >${CMAKE_CURRENT_BINARY_DIR}/gitversion.h DEPENDS ${STATIC_LIBRARY_TARGETS}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "Generating GIT revision number (tag + last commit SHA-1)")
    else ()
        add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gitversion.h
            COMMAND for v in `git describe --always --dirty`\; do echo 'const char* revision="'$$v'"\;' >${CMAKE_CURRENT_BINARY_DIR}/gitversion.h\; break\; done DEPENDS ${STATIC_LIBRARY_TARGETS}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "Generating GIT revision number (tag + last commit SHA-1)")
    endif ()
else ()
    # No GIT command line tool or not a GIT repository, generate a dummy version file
    file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/gitversion.h "const char* revision=\"Unversioned\";")
endif ()

# Define generated object files
# This is a hack as it relies on internal working of CMake
if (WIN32)
    set (CMAKE_DEBUG_POSTFIX _d)
    set (OBJ_EXT .obj)
else ()
    set (OBJ_EXT .o)
endif ()

foreach (TARGET ${STATIC_LIBRARY_TARGETS})
    get_target_property (SOURCES ${TARGET} SOURCES)
    get_target_property (INT_DIR ${TARGET} LOCATION)
    get_filename_component (INT_DIR ${INT_DIR} PATH)
    set (INT_DIR ${INT_DIR}/CMakeFiles/${TARGET}.dir)
    if (MSVC)
        if (CMAKE_GENERATOR MATCHES "2008")
            string (REPLACE /$(OutDir) "" INT_DIR ${INT_DIR})
        else ()
            string (REPLACE /$(Configuration) "" INT_DIR ${INT_DIR})
        endif ()
        if (USE_MKLINK)
            string (REGEX REPLACE \\.dir$ .lnk INT_DIR ${INT_DIR})
        endif ()
    elseif (XCODE)
        string (REPLACE /$(CONFIGURATION)$(EFFECTIVE_PLATFORM_NAME) "" INT_DIR ${INT_DIR})
        string (REGEX REPLACE \\.dir$ .lnk INT_DIR ${INT_DIR})
    endif ()
    
    foreach (SOURCE ${SOURCES})
        get_filename_component (NAME ${SOURCE} NAME)
        if (NAME MATCHES \\.c.*$|\\.mm?$|\\.S$|\\.s$)
            if (MSVC OR XCODE)
                string (REGEX REPLACE \\.c.*$|\\.mm?$|\\.S$|\\.s$ "" NAME ${NAME}) 
            endif ()
            set (SYS_DIR "")
            if (NOT MSVC AND NOT XCODE)
                get_filename_component (PATH ${SOURCE} PATH)
                foreach (DIR OpenGL Direct3D9 source src generated)
                    if (PATH MATCHES /${DIR}$)
                        set (SYS_DIR /${DIR})
                        break ()
                    elseif (PATH MATCHES /${DIR}/)
                        string (REGEX REPLACE .*/${DIR}/ "" SYS_DIR ${PATH})
                        set (SYS_DIR /${DIR}/${SYS_DIR})
                        break ()
                    elseif (PATH MATCHES ^${DIR}/|^${DIR}$)
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
set (SOURCE_FILES ${CPP_FILES} ${H_FILES} ${OBJ_FILES} gitversion.h)
set_source_files_properties (${OBJ_FILES} PROPERTIES GENERATED TRUE)

# Define dependency libs
set (INCLUDE_DIRS_ONLY ${CMAKE_CURRENT_BINARY_DIR})
if (LIB_TYPE STREQUAL SHARED)
    define_dependency_libs (Main)
endif ()

# Setup target
setup_library ()
if (NOT GIT_EXIT_CODE EQUAL 0)
    add_dependencies (${TARGET_NAME} ${STATIC_LIBRARY_TARGETS})
endif ()

# Setup the frameworks for Mac OS X platform
if (APPLE AND LIB_TYPE STREQUAL SHARED)
    setup_macosx_framework (FRAMEWORKS)
    set_target_properties (${TARGET_NAME} PROPERTIES LINK_FLAGS ${FRAMEWORKS})
endif ()

# Define post build steps
file (MAKE_DIRECTORY ${PROJECT_ROOT_DIR}/Lib)
if (MSVC)
    add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETPATH)\" \"${PROJECT_ROOT_DIR}/Lib\"
        COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETDIR)$(TARGETNAME).pdb\" \"${PROJECT_ROOT_DIR}/Lib\"
        COMMENT "Copying library and debug files to Lib directory")
    if (LIB_TYPE STREQUAL SHARED)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETDIR)$(TARGETNAME).lib\" \"${PROJECT_ROOT_DIR}/Lib\"
            COMMENT "Copying import library to Lib directory")
    endif ()
else ()
    # Strip the output shared library for embedded devices
    if (LIB_TYPE STREQUAL SHARED AND (CMAKE_CROSSCOMPILING OR IOS))
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${TARGET_NAME}>)
    endif ()
    set (OUTPUT_PATH ${PROJECT_ROOT_DIR}/Lib)
    if (ANDROID)
        set (OUTPUT_PATH ${ANDROID_LIBRARY_OUTPUT_PATH})
    elseif (CMAKE_CROSSCOMPILING)
        set (OUTPUT_PATH ${OUTPUT_PATH}-CC)
        if (SCP_TO_TARGET)
            add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND scp $<TARGET_FILE:${TARGET_NAME}> ${SCP_TO_TARGET} || exit 0)
        endif ()
    endif ()
    file (MAKE_DIRECTORY ${OUTPUT_PATH})
    add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different $<TARGET_FILE:${TARGET_NAME}> ${OUTPUT_PATH})
endif ()
