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

# Define generated source files
execute_process (COMMAND git describe --always WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} RESULT_VARIABLE GIT_EXIT_CODE OUTPUT_QUIET ERROR_QUIET)
if (GIT_EXIT_CODE EQUAL 0)
    if (CMAKE_HOST_WIN32)
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
    if (MSVC)
        if (CMAKE_GENERATOR MATCHES "2008")
            string (REPLACE /$(OutDir) /${TARGET}.dir/$(ConfigurationName) INT_DIR ${INT_DIR})
        else ()
            string (REPLACE /$(Configuration) /${TARGET}.dir/$(ConfigurationName) INT_DIR ${INT_DIR})
        endif ()
    else ()
        set (INT_DIR ${INT_DIR}/CMakeFiles/${TARGET}.dir)
    endif ()
    if (XCODE)
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
            list (APPEND OBJ_FILES ${INT_DIR}${SYS_DIR}/${NAME}${OBJ_EXT})
        elseif (NAME MATCHES \\.o.*$)
            list (APPEND OBJ_FILES ${SOURCE})
        endif ()
    endforeach ()
    source_group ("Object Files\\${TARGET}" FILES ${OBJ_FILES})
    list (APPEND ALL_OBJ_FILES ${OBJ_FILES})
    unset (OBJ_FILES)
endforeach ()

# Define source files
foreach (SOURCE Audio Container Core Engine Graphics Input IO Math Navigation Network Physics Resource Scene Script UI)
    add_subdirectory (${SOURCE})
    source_group ("Source Files\\${SOURCE}" FILES ${${SOURCE}_CPP_FILES})
    source_group ("Header Files\\${SOURCE}" FILES ${${SOURCE}_H_FILES})
    list (APPEND ENGINE_SOURCE_FILES ${${SOURCE}_CPP_FILES} ${${SOURCE}_H_FILES})
    list (APPEND ENGINE_INCLUDE_DIRS_ONLY ${SOURCE})
endforeach ()
define_source_files (EXTRA_CPP_FILES ${ENGINE_SOURCE_FILES} EXTRA_H_FILES gitversion.h PCH)
list (APPEND SOURCE_FILES ${ALL_OBJ_FILES})
set_source_files_properties (${ALL_OBJ_FILES} PROPERTIES GENERATED TRUE)

# Define dependency libs
foreach (LIST_NAME LIBS INCLUDE_DIRS_ONLY LINK_LIBS_ONLY)
    set_list (${LIST_NAME} ENGINE_${LIST_NAME} REMOVE_DUPLICATE)
endforeach ()

# Setup target
setup_library (${URHO3D_LIB_TYPE})
adjust_library_name ()
if (NOT GIT_EXIT_CODE EQUAL 0)
    add_dependencies (${TARGET_NAME} ${STATIC_LIBRARY_TARGETS})
endif ()

# Setup the frameworks for Mac OS X platform
if (APPLE AND URHO3D_LIB_TYPE STREQUAL SHARED)
    if (IOS)
        setup_ios_linker_flags (LINKER_FLAGS)
    else ()
        setup_macosx_linker_flags (LINKER_FLAGS)
    endif ()
    set_target_properties (${TARGET_NAME} PROPERTIES LINK_FLAGS ${LINKER_FLAGS})
endif ()

# Generate platform specific export header file automatically
if (NOT URHO3D_LIB_TYPE STREQUAL URHO3D_EXPORTS_LIB_TYPE OR ${CMAKE_CURRENT_SOURCE_DIR}/Urho3D.h.in IS_NEWER_THAN ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.h)
    set_target_properties (${TARGET_NAME} PROPERTIES DEFINE_SYMBOL URHO3D_EXPORTS)
    generate_export_header (${TARGET_NAME} BASE_NAME ${LIB_NAME} EXPORT_MACRO_NAME URHO3D_API EXPORT_FILE_NAME Urho3D.h)
    set (URHO3D_EXPORTS_LIB_TYPE ${URHO3D_LIB_TYPE} CACHE INTERNAL "Lib type when Urho3D export header was last generated")
    
    # Append Urho3D license notice to the export header file
    file (READ ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.h EXPORT_DEFINE)
    configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Urho3D.h.in ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.h) 
endif ()

# Define post build steps
file (MAKE_DIRECTORY ${PROJECT_ROOT_DIR}/Lib)
if (MSVC)
    add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETPATH)\" \"${PROJECT_ROOT_DIR}/Lib\"
        COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETDIR)$(TARGETNAME).pdb\" \"${PROJECT_ROOT_DIR}/Lib\"
        COMMENT "Copying library and debug files to Lib directory")
    if (URHO3D_LIB_TYPE STREQUAL SHARED)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETDIR)$(TARGETNAME).lib\" \"${PROJECT_ROOT_DIR}/Lib\"
            COMMENT "Copying import library to Lib directory")
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETPATH)\" \"${PROJECT_ROOT_DIR}/Bin\"
            COMMENT "Copying shared library to Bin directory")
    endif ()
else ()
    # Strip the output shared library for embedded devices
    if (URHO3D_LIB_TYPE STREQUAL SHARED AND (CMAKE_CROSSCOMPILING OR IOS))
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
