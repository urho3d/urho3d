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
        if (CMAKE_GENERATOR MATCHES 2008)
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
            unset (DIR_SUFFIX)
            if (NOT MSVC AND NOT XCODE)
                get_filename_component (PATH ${SOURCE} PATH)
                foreach (DIR source src generated)
                    if (PATH MATCHES \(ThirdParty|Engine\)/.*/${DIR}$)
                        set (DIR_SUFFIX /${DIR})
                        break ()
                    elseif (PATH MATCHES ThirdParty/.*/${DIR}/)
                        string (REGEX REPLACE .*/${DIR}/ "" DIR_SUFFIX ${PATH})
                        set (DIR_SUFFIX /${DIR}/${DIR_SUFFIX})
                        break ()
                    elseif (PATH MATCHES ^${DIR}/|^${DIR}$)
                        set (DIR_SUFFIX /${PATH})
                        break ()
                    endif ()
                endforeach ()
            endif ()
            list (APPEND OBJ_FILES ${INT_DIR}${DIR_SUFFIX}/${NAME}${OBJ_EXT})
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
    install (DIRECTORY ${SOURCE}/ DESTINATION ${DEST_INCLUDE_DIR} USE_SOURCE_PERMISSIONS FILES_MATCHING PATTERN *.h)    # Note: the trailing slash is significant
    source_group ("Source Files\\${SOURCE}" FILES ${${SOURCE}_CPP_FILES})
    source_group ("Header Files\\${SOURCE}" FILES ${${SOURCE}_H_FILES})
    list (APPEND ENGINE_SOURCE_FILES ${${SOURCE}_CPP_FILES} ${${SOURCE}_H_FILES})
    list (APPEND ENGINE_INCLUDE_DIRS_ONLY ${SOURCE})
endforeach ()
define_source_files (EXTRA_CPP_FILES ${ENGINE_SOURCE_FILES} EXTRA_H_FILES ${CMAKE_CURRENT_BINARY_DIR}/gitversion.h PCH)
install (FILES ${H_FILES} DESTINATION ${DEST_INCLUDE_DIR})
list (APPEND SOURCE_FILES ${ALL_OBJ_FILES})
set_source_files_properties (${ALL_OBJ_FILES} PROPERTIES GENERATED TRUE)

# Define dependency libs
foreach (LIST_NAME LIBS INCLUDE_DIRS_ONLY LINK_LIBS_ONLY)
    set_list (${LIST_NAME} ENGINE_${LIST_NAME} REMOVE_DUPLICATE)
endforeach ()
# Add include directory to find the export header
list (APPEND INCLUDE_DIRS_ONLY ${CMAKE_BINARY_DIR}/Engine)

# Setup library output path
set (OUTPUT_PATH ${PROJECT_ROOT_DIR}/Lib)
if (ANDROID)
    set (OUTPUT_PATH ${ANDROID_LIBRARY_OUTPUT_PATH})
elseif (CMAKE_CROSSCOMPILING)
    set (OUTPUT_PATH ${OUTPUT_PATH}-CC)
endif ()
set_output_directories (${OUTPUT_PATH} ARCHIVE LIBRARY)
 
# Setup target
setup_library (${URHO3D_LIB_TYPE})
install (TARGETS ${TARGET_NAME} RUNTIME DESTINATION ${DEST_RUNTIME_DIR} LIBRARY DESTINATION ${DEST_LIBRARY_DIR} ARCHIVE DESTINATION ${DEST_LIBRARY_DIR})
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
    generate_export_header (${TARGET_NAME} EXPORT_MACRO_NAME URHO3D_API EXPORT_FILE_NAME Urho3D.h)
    set (URHO3D_EXPORTS_LIB_TYPE ${URHO3D_LIB_TYPE} CACHE INTERNAL "Lib type when Urho3D export header was last generated")
    
    # Append Urho3D license notice to the export header file
    file (READ ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.h EXPORT_DEFINE)
    configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Urho3D.h.in ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.h)
endif ()
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.h DESTINATION ${DEST_INCLUDE_DIR})

# Generate platform specific pkg-config file for the benefit of Urho3D library users via SDK without CMake
if (NOT ANDROID AND NOT IOS)
    set (SYSROOT ${RASPI_SYSROOT})  # SYSROOT is empty for native build
    string (REPLACE "${SYSROOT}" "" DEST_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
    get_directory_property (URHO3D_COMPILE_DEFINITIONS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMPILE_DEFINITIONS)
    list (REMOVE_ITEM URHO3D_COMPILE_DEFINITIONS HAVE_STDINT_H GLEW_STATIC GLEW_NO_GLU)     # Remove those defines that are only used for building the library and not needed by library user
    string (REPLACE ";" " -D" URHO3D_COMPILE_DEFINITIONS ";${URHO3D_COMPILE_DEFINITIONS}")
    string (REPLACE ";" " " URHO3D_ABS_PATH_LIBS "${ABSOLUTE_PATH_LIBS}")   # Note: need to always "stringify" a variable in list context for replace to work correctly, besides the list could be empty
    string (REPLACE "${SYSROOT}" "\${pc_sysrootdir}" URHO3D_ABS_PATH_LIBS "${URHO3D_ABS_PATH_LIBS}") 
    string (REPLACE ";" " -l" URHO3D_LIBS "-lUrho3D;${LINK_LIBS_ONLY}")
    get_directory_property (GLOBAL_INCLUDE_DIRS DIRECTORY ${CMAKE_SOURCE_DIR} INCLUDE_DIRECTORIES)
    if (GLOBAL_INCLUDE_DIRS)
        string (REPLACE ";" " -I" GLOBAL_INCLUDE_DIRS ";${GLOBAL_INCLUDE_DIRS}")
        string (REPLACE "${SYSROOT}" "" GLOBAL_INCLUDE_DIRS ${GLOBAL_INCLUDE_DIRS})
    endif ()
    string (REPLACE ";" " -I\${includedir}/" URHO3D_INCLUDE_DIRS "-I\${includedir};${INSTALL_INCLUDE_DIRS}")
    configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Urho3D.pc.in ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.pc @ONLY)
    install (FILES ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.pc DESTINATION ${DEST_PKGCONFIG_DIR})
endif ()

# Setup the compiler flags for building shared library (do this here so that it does not interfere with the pkg-config file generation above)
if (URHO3D_LIB_TYPE STREQUAL SHARED)
    # Hide the symbols that are not explicitly marked for export
    add_compiler_export_flags ()
    # Use PIC on platforms that support it (shared library type has this property set to true by default, so we only have to deal with those static ones that the shared library links against)
    set_target_properties (${STATIC_LIBRARY_TARGETS} PROPERTIES POSITION_INDEPENDENT_CODE true) 
endif ()

# Define post build steps
# Strip the output shared library for embedded devices
if (URHO3D_LIB_TYPE STREQUAL SHARED AND (CMAKE_CROSSCOMPILING OR IOS))
    add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${TARGET_NAME}>
    COMMENT "Stripping shared library")
endif ()
if (RASPI AND SCP_TO_TARGET)
    # Ensure SCP is the last command
    add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND scp $<TARGET_FILE:${TARGET_NAME}> ${SCP_TO_TARGET} || exit 0)
endif ()
