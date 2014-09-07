#
# Copyright (c) 2008-2014 the Urho3D project.
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

if (WIN32)
    set (CMAKE_DEBUG_POSTFIX _d)
endif ()

# Define generated source files
add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/librevision.h
    COMMAND ${CMAKE_COMMAND} -DFILENAME=${CMAKE_CURRENT_BINARY_DIR}/librevision.h -P CMake/Modules/GetUrho3DRevision.cmake
    DEPENDS ${STATIC_LIBRARY_TARGETS} ${PROJECT_SOURCE_DIR}/CMake/Modules/GetUrho3DRevision.cmake
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Generating GIT revision number (tag + last commit SHA-1)")

# Define generated object files
# This is a hack as it relies on internal working of CMake
if (MSVC AND URHO3D_LIB_TYPE STREQUAL SHARED)   # MSVC linker does not have force_load/whole_archive equivalent
    foreach (TARGET ${STATIC_LIBRARY_TARGETS})
        get_target_property (SOURCES ${TARGET} SOURCES)
        get_target_property (INT_DIR ${TARGET} LOCATION)
        get_filename_component (INT_DIR ${INT_DIR} PATH)
        if (CMAKE_GENERATOR MATCHES 2008)
            string (REPLACE /$(OutDir) /${TARGET}.dir/$(ConfigurationName) INT_DIR ${INT_DIR})
        else ()
            string (REPLACE /$(Configuration) /${TARGET}.dir/$(ConfigurationName) INT_DIR ${INT_DIR})
        endif ()
        foreach (SOURCE ${SOURCES})
            get_filename_component (NAME ${SOURCE} NAME)
            if (NAME MATCHES \\.c.*$|\\.mm?$|\\.S$|\\.s$)
                string (REGEX REPLACE \\.c.*$|\\.mm?$|\\.S$|\\.s$ .obj NAME ${NAME})
                list (APPEND OBJ_FILES ${INT_DIR}/${NAME})
            elseif (NAME MATCHES \\.obj$)
                list (APPEND OBJ_FILES ${SOURCE})
            endif ()
        endforeach ()
        source_group ("Object Files\\${TARGET}" FILES ${OBJ_FILES})
        list (APPEND ALL_OBJ_FILES ${OBJ_FILES})
        unset (OBJ_FILES)
    endforeach ()
endif ()

# Define source files
set (SOURCES Audio Container Core Engine Graphics Input IO Math Network Resource Scene UI Urho2D)
if (URHO3D_ANGELSCRIPT)
    list (APPEND SOURCES Script)
endif ()

if (URHO3D_NAVIGATION)
    list (APPEND SOURCES Navigation)
endif ()

if (URHO3D_PHYSICS)
    list (APPEND SOURCES Physics)
endif ()

foreach (SOURCE ${SOURCES})
    add_subdirectory (${SOURCE})
    install (DIRECTORY ${SOURCE}/ DESTINATION ${DEST_INCLUDE_DIR} ${DEST_PERMISSIONS} FILES_MATCHING PATTERN *.h)    # Note: the trailing slash is significant
    source_group ("Source Files\\${SOURCE}" FILES ${${SOURCE}_CPP_FILES})
    source_group ("Header Files\\${SOURCE}" FILES ${${SOURCE}_H_FILES})
    list (APPEND ENGINE_SOURCE_FILES ${${SOURCE}_CPP_FILES} ${${SOURCE}_H_FILES})
    list (APPEND ENGINE_INCLUDE_DIRS_ONLY ${SOURCE})
endforeach ()
define_source_files (EXTRA_CPP_FILES ${ENGINE_SOURCE_FILES} EXTRA_H_FILES ${CMAKE_CURRENT_BINARY_DIR}/librevision.h PCH)
install (FILES ${H_FILES} DESTINATION ${DEST_INCLUDE_DIR})
list (APPEND SOURCE_FILES ${ALL_OBJ_FILES})
set_source_files_properties (${ALL_OBJ_FILES} PROPERTIES GENERATED TRUE)
if (APPLE)
    set (AMALG_EXCLUDES_PLATFORM_SPECIFIC |MathAPI)
elseif (MSVC)
    set (AMALG_EXCLUDES_PLATFORM_SPECIFIC |Camera|Color|Frustum|MathAPI|Network|Precompiled|ResourceCache|Text\\.|Window)
endif ()
set (AMALG_EXCLUDES "(CollisionShape|Constraint|HttpRequest|SoundSource|Variant${AMALG_EXCLUDES_PLATFORM_SPECIFIC})")
set (AMALG_FINAL_TARGET 1)

# Define dependency libs
foreach (LIST_NAME LIBS INCLUDE_DIRS_ONLY LINK_LIBS_ONLY)
    set_list (${LIST_NAME} ENGINE_${LIST_NAME} REMOVE_DUPLICATE)
endforeach ()
# Add include directories to find the export header and SDL header
list (APPEND INCLUDE_DIRS_ONLY ${CMAKE_CURRENT_BINARY_DIR} ../ThirdParty/SDL/include)

# Setup library output path
if (ANDROID)
    set (OUTPUT_PATH ${ANDROID_LIBRARY_OUTPUT_PATH})
else ()
    set (OUTPUT_PATH ${PROJECT_ROOT_DIR}/${PLATFORM_PREFIX}Lib)     # ${PLATFORM_PREFIX} is empty for native build
endif ()
set_output_directories (${OUTPUT_PATH} ARCHIVE LIBRARY)
 
# Setup target
setup_library (${URHO3D_LIB_TYPE})
if (NOT ANDROID)
    file (READ .soversion SOVERSION)
    string (STRIP ${SOVERSION} SOVERSION)
    string (REGEX MATCH "([^.]+)\\.([^.]+)\\.(.+)" MATCHED ${SOVERSION})
    if (MATCHED)
        set_target_properties (${TARGET_NAME} PROPERTIES VERSION ${MATCHED} SOVERSION ${CMAKE_MATCH_1})
    else ()
        message (FATAL_ERROR "The .soversion file is corrupted. It should contain a version number with this format major(0xFFFF).minor(0xFF).patch-level(0xFF). e.g.: 0.1.2")
    endif ()
endif ()
install (TARGETS ${TARGET_NAME} RUNTIME DESTINATION ${DEST_RUNTIME_DIR} LIBRARY DESTINATION ${DEST_LIBRARY_DIR} ARCHIVE DESTINATION ${DEST_LIBRARY_DIR})
if (NOT GIT_EXIT_CODE EQUAL 0)
    add_dependencies (${TARGET_NAME} ${STATIC_LIBRARY_TARGETS})
endif ()

# Setup dependency frameworks and libraries
if (APPLE)
    if (IOS)
        setup_ios_linker_flags (LINKER_FLAGS)
        # Add a custom target to build Mach-O universal binary consisting of iphoneos (universal ARM archs including 'arm64' if 64-bit is enabled) and iphonesimulator (i386 arch and also x86_64 arch if 64-bit is enabled)
        add_custom_target (${TARGET_NAME}_universal
            COMMAND lipo -info $<TARGET_FILE:${TARGET_NAME}> |egrep -v 'i386.+armv7' && xcodebuild -target ${TARGET_NAME} -configuration $(CONFIGURATION) -sdk iphonesimulator && mv $<TARGET_FILE:${TARGET_NAME}>{,.iphonesimulator} && xcodebuild -target ${TARGET_NAME} -configuration $(CONFIGURATION) -sdk iphoneos && mv $<TARGET_FILE:${TARGET_NAME}>{,.iphoneos} && lipo -create -output $<TARGET_FILE:${TARGET_NAME}>{,.iphonesimulator,.iphoneos} && rm $<TARGET_FILE:${TARGET_NAME}>{.iphonesimulator,.iphoneos} || echo $<TARGET_FILE:${TARGET_NAME}> is already a Mach-O universal binary consisting of both iphoneos and iphonesimulator archs
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Creating Mach-O universal binary library consisting of both iphoneos and iphonesimulator archs")
    else ()
        # Intentionally use built-in CMAKE_EXE_LINKER_FLAGS here although CMake does not use it when building library, but the variable would be used later when configuring Urho3D.pc for MacOSX platform
        setup_macosx_linker_flags (CMAKE_EXE_LINKER_FLAGS)
        # LuaJIT 64-bit specific - replace EXE linker flags with flags for building shared library (adapted from LuaJIT's original Makefile)
        string (REPLACE "-pagezero_size 10000 -image_base 100000000" "-image_base 7fff04c4a000" LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})
    endif ()
    set_target_properties (${TARGET_NAME} PROPERTIES LINK_FLAGS ${LINKER_FLAGS})
    set (FORCE_LOAD -force_load)
elseif (NOT MSVC)
    set_property (TARGET ${TARGET_NAME} APPEND PROPERTY LINK_LIBRARIES -Wl,--whole-archive)
    if (WIN32 AND URHO3D_LIB_TYPE STREQUAL SHARED)
        set_target_properties (${TARGET_NAME} PROPERTIES PREFIX "")
    endif ()
endif ()
foreach (TARGET ${STATIC_LIBRARY_TARGETS})
    get_target_property (ARCHIVE ${TARGET} LOCATION)
    if (NOT MSVC)
        set_property (TARGET ${TARGET_NAME} APPEND PROPERTY LINK_LIBRARIES ${FORCE_LOAD} ${ARCHIVE})    # Only works in Apple (Xcode and Makefile) and GCC while building shared library
    endif ()
    if (XCODE OR MSVC)
        set_property (TARGET ${TARGET_NAME} APPEND_STRING PROPERTY STATIC_LIBRARY_FLAGS " ${ARCHIVE}")  # Only works in Apple (Xcode only) and MSVC while building static library
    else ()
        list (APPEND ARCHIVES ${ARCHIVE})
    endif ()
endforeach ()
if (NOT XCODE AND NOT MSVC)
    if (NOT APPLE)
        set_property (TARGET ${TARGET_NAME} APPEND PROPERTY LINK_LIBRARIES -Wl,--no-whole-archive)
    endif ()
    if (NOT URHO3D_LIB_TYPE STREQUAL SHARED)    # GCC ar does not take archives directly as input like Apple libtool, however, it can be scripted to do so
        if (APPLE)
            add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
                COMMAND mv $<TARGET_FILE:${TARGET_NAME}>{,.engine}
                COMMAND libtool -static $<TARGET_FILE:${TARGET_NAME}>.engine ${ARCHIVES} -o $<TARGET_FILE:${TARGET_NAME}>
                COMMAND rm $<TARGET_FILE:${TARGET_NAME}>.engine
                COMMENT "Merging all archives into a single static library using libtool")
        else ()
            add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E rename $<TARGET_FILE:${TARGET_NAME}> $<TARGET_FILE:${TARGET_NAME}>.engine
                COMMAND echo CREATE $<TARGET_FILE:${TARGET_NAME}> >script.ar
                COMMAND echo ADDLIB $<TARGET_FILE:${TARGET_NAME}>.engine >>script.ar)
            foreach (ARCHIVE ${ARCHIVES})
                add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND echo ADDLIB ${ARCHIVE} >>script.ar)
            endforeach ()
            add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
                COMMAND echo SAVE >>script.ar
                COMMAND echo END >>script.ar
                COMMAND ${CMAKE_AR} -M <script.ar
                COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:${TARGET_NAME}>.engine script.ar
                COMMENT "Merging all archives into a single static library using ar")
        endif ()
    endif ()
endif ()
# todo This is a deprecated property in CMake version 2.8.12 - Remove below commands when CMake minimum version is 2.8.12
if (CMAKE_VERSION VERSION_LESS 2.8.12)
    set_target_properties (${TARGET_NAME} PROPERTIES LINK_INTERFACE_LIBRARIES "")
    if (URHO3D_LIB_TYPE STREQUAL SHARED)
        if (NOT MSVC AND CMAKE_VERSION VERSION_LESS 2.8.11)
            get_target_property (LINK_LIBRARIES ${TARGET_NAME} LINK_LIBRARIES)
            target_link_libraries (${TARGET_NAME} LINK_PRIVATE ${LINK_LIBRARIES})
        endif ()
    else ()
        set_target_properties (${TARGET_NAME} PROPERTIES LINK_LIBRARIES "")
    endif ()
endif ()
# end todo

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
    set (SYSROOT ${RASPI_SYSROOT} ${MINGW_SYSROOT})  # SYSROOT is empty for native build
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
    string (REPLACE ";" " -I\${includedir}/" ENGINE_INCLUDE_DIRS "-I\${includedir};${INSTALL_INCLUDE_DIRS}")
    configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Urho3D.pc.in ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.pc @ONLY)
    install (FILES ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.pc DESTINATION ${DEST_PKGCONFIG_DIR})
endif ()

# Setup the compiler flags for building shared library (do this here so that it does not interfere with the pkg-config file generation above)
if (URHO3D_LIB_TYPE STREQUAL SHARED)
    # Hide the symbols that are not explicitly marked for export
    add_compiler_export_flags ()
    # Use PIC on platforms that support it (shared library type has this property set to true by default, so we only have to deal with those static ones that the shared library links against)
    set_target_properties (${STATIC_LIBRARY_TARGETS} PROPERTIES POSITION_INDEPENDENT_CODE true)
    if (NOT MSVC AND NOT (CMAKE_CROSSCOMPILING AND MINGW) AND CMAKE_VERSION VERSION_LESS 2.8.9)  # \todo Remove this when CMake minimum version is 2.8.9
        set_property (TARGET ${STATIC_LIBRARY_TARGETS} APPEND PROPERTY COMPILE_FLAGS -fPIC)
    endif ()
endif ()

# Define post build steps
# Strip the output shared library for embedded devices
if (URHO3D_LIB_TYPE STREQUAL SHARED AND (CMAKE_CROSSCOMPILING OR IOS))
    add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${TARGET_NAME}>
        COMMENT "Stripping shared library")
endif ()
if (CMAKE_CROSSCOMPILING AND NOT ANDROID AND URHO3D_SCP_TO_TARGET)
    # Ensure SCP is the last command
    add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND scp $<TARGET_FILE:${TARGET_NAME}> ${URHO3D_SCP_TO_TARGET} || exit 0
        COMMENT "Scp-ing library to target system")
endif ()
