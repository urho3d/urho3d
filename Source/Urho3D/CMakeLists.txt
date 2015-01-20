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
    DEPENDS ${STATIC_LIBRARY_TARGETS} ${CMAKE_SOURCE_DIR}/CMake/Modules/GetUrho3DRevision.cmake
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating GIT revision number (tag + last commit SHA-1)")

if (URHO3D_LUA)
    # The host tool must be built natively
    if (CMAKE_CROSSCOMPILING OR IOS)
        # When cross-compiling, build the host tool as external project
        include (ExternalProject)
        if (IOS)
            # For iOS target, its host is MacOSX; Also workaround a known CMake/Xcode generator bug which prevents it from installing binaries correctly
            set (OSX_HOST -DCMAKE_OSX_SYSROOT=macosx BUILD_COMMAND bash -c "sed -i '' 's/EFFECTIVE_PLATFORM_NAME//g' CMakeScripts/install_postBuildPhase.make*")
        endif ()
        ExternalProject_Add(tolua++
            SOURCE_DIR ${CMAKE_SOURCE_DIR}/Source/ThirdParty/toluapp/src/bin
            CMAKE_ARGS -DJIT=${JIT} -DDEST_RUNTIME_DIR=${CMAKE_BINARY_DIR}/bin/tool -DBAKED_CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR} ${OSX_HOST}
        )
    else ()
        # Otherwise, build it internally as per normal
        add_subdirectory (../ThirdParty/toluapp/src/bin ../ThirdParty/toluapp/src/bin)
    endif ()

    # Use the host tool to generate source files for tolua++ API binding
    file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated)
    file (GLOB API_PKG_FILES LuaScript/pkgs/*.pkg)
    foreach (DIR Navigation Network Physics Urho2D)
        string (TOUPPER URHO3D_${DIR} OPT)
        if (NOT ${OPT})
            list (REMOVE_ITEM API_PKG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/pkgs/${DIR}LuaAPI.pkg)
        endif ()
    endforeach ()
    foreach (API_PKG_FILE ${API_PKG_FILES})
        get_filename_component (NAME ${API_PKG_FILE} NAME)
        string (REGEX REPLACE LuaAPI\\.pkg$ "" DIR ${NAME})
        set (GEN_CPP_FILE generated/${DIR}LuaAPI.cpp)
        list (APPEND GEN_CPP_FILES ${GEN_CPP_FILE})
        file (GLOB PKG_FILES LuaScript/pkgs/${DIR}/*.pkg)
        add_custom_command (OUTPUT ${GEN_CPP_FILE}
            COMMAND ${CMAKE_BINARY_DIR}/bin/tool/tolua++ -L ToCppHook.lua -o ${CMAKE_CURRENT_BINARY_DIR}/${GEN_CPP_FILE} ${NAME}
            DEPENDS tolua++ ${API_PKG_FILE} ${PKG_FILES} LuaScript/pkgs/ToCppHook.lua
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/LuaScript/pkgs
            COMMENT "Generating tolua++ DIR binding on the fly for ${DIR}")
    endforeach ()
else ()
    list (APPEND EXCLUDED_SOURCE_DIRS LuaScript)
endif ()

# Define generated object files
# This is a hack as it relies on internal working of CMake
if (MSVC AND URHO3D_LIB_TYPE STREQUAL SHARED)   # MSVC linker does not have force_load/whole_archive equivalent
    foreach (TARGET ${STATIC_LIBRARY_TARGETS})
        get_target_property (SOURCES ${TARGET} SOURCES)
        get_target_property (INT_DIR ${TARGET} LOCATION)
        if (INT_DIR)
            get_filename_component (INT_DIR ${INT_DIR} PATH)
            if (CMAKE_GENERATOR MATCHES 2008)
                string (REPLACE /$(OutDir) /${TARGET}.dir/$(ConfigurationName) INT_DIR ${INT_DIR})
            else ()
                string (REPLACE /$(Configuration) /${TARGET}.dir/$(ConfigurationName) INT_DIR ${INT_DIR})
            endif ()
            foreach (SOURCE ${SOURCES})
                get_filename_component (NAME ${SOURCE} NAME)
                if (NAME MATCHES \\.c.*$|\\.mm?$|\\.S$|\\.s$)
                    string (REGEX REPLACE \\.c.*$|\\.mm?$|\\.S$|\\.s$ "" NAME ${NAME})
                    list (APPEND OBJ_FILES ${INT_DIR}/${NAME}.obj)
                elseif (NAME MATCHES \\.o.*$)
                    list (APPEND OBJ_FILES ${SOURCE})
                endif ()
            endforeach ()
            source_group ("Object Files\\${TARGET}" FILES ${OBJ_FILES})
            list (APPEND ALL_OBJ_FILES ${OBJ_FILES})
            unset (OBJ_FILES)
        endif ()
    endforeach ()
endif ()

# Define source files
if (NOT URHO3D_ANGELSCRIPT)
    list (APPEND EXCLUDED_SOURCE_DIRS Script)
endif ()
foreach (DIR Navigation Network Physics Urho2D)
    string (TOUPPER URHO3D_${DIR} OPT)
    if (NOT ${OPT})
        list (APPEND EXCLUDED_SOURCE_DIRS ${DIR})
    endif ()
endforeach ()
if (URHO3D_OPENGL)
    # Exclude the opposite source directory
    list (APPEND EXCLUDED_SOURCE_DIRS Graphics/Direct3D9)
else ()
    list (APPEND EXCLUDED_SOURCE_DIRS Graphics/OpenGL)
endif ()
if (APPLE AND NOT IOS)
    set (GLOB_OBJC_PATTERN *.m)     # Should only pick up MacFileWatcher.m for MacOSX platform at the moment
endif ()
string (REPLACE ";" "/[^;]+;" EXCLUDE_PATTERNS "${EXCLUDED_SOURCE_DIRS};")
define_source_files (EXCLUDE_PATTERNS ${EXCLUDE_PATTERNS} GLOB_CPP_PATTERNS *.cpp ${GLOB_OBJC_PATTERN} EXTRA_H_FILES librevision.h RECURSE GROUP PCH)
list (APPEND SOURCE_FILES ${GEN_CPP_FILES} ${ALL_OBJ_FILES})
set_source_files_properties (${ALL_OBJ_FILES} PROPERTIES GENERATED TRUE)

# Define dependency libs
# Add include directories to find the precompiled header, export header, and installed headers from thirdparty libs
set (INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_BINARY_DIR}/${DEST_INCLUDE_DIR}/ThirdParty)
if (URHO3D_PHYSICS)
    # Bullet library depends on its own include dir to be added in the header search path
    # This is more practical than patching its header files in many places to make them work with relative path
    list (APPEND INCLUDE_DIRS ${CMAKE_BINARY_DIR}/${DEST_INCLUDE_DIR}/ThirdParty/Bullet)
endif ()
if (URHO3D_LUA)
    # ditto for Lua/LuaJIT
    list (APPEND INCLUDE_DIRS ${CMAKE_BINARY_DIR}/${DEST_INCLUDE_DIR}/ThirdParty/Lua${JIT})
endif ()

# Setup library output path
if (ANDROID)
    set (OUTPUT_PATH ${ANDROID_LIBRARY_OUTPUT_PATH})
else ()
    set (OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
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
    if (ARCHIVE)
        if (NOT MSVC)
            set_property (TARGET ${TARGET_NAME} APPEND PROPERTY LINK_LIBRARIES ${FORCE_LOAD} ${ARCHIVE})    # Only works in Apple (Xcode and Makefile) and GCC while building shared library
        endif ()
        if (XCODE OR MSVC)
            set_property (TARGET ${TARGET_NAME} APPEND_STRING PROPERTY STATIC_LIBRARY_FLAGS " ${ARCHIVE}")  # Only works in Apple (Xcode only) and MSVC while building static library
        else ()
            list (APPEND ARCHIVES ${ARCHIVE})
        endif ()
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
if (${CMAKE_CURRENT_SOURCE_DIR}/Urho3D.h.in IS_NEWER_THAN ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.h)
    set_target_properties (${TARGET_NAME} PROPERTIES DEFINE_SYMBOL URHO3D_EXPORTS)
    generate_export_header (${TARGET_NAME} EXPORT_MACRO_NAME URHO3D_API EXPORT_FILE_NAME Urho3D.h)
    file (READ ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.h EXPORT_DEFINE)
    if (MSVC)
        string (REPLACE "#define URHO3D_API_H" "#define URHO3D_API_H\n\n#pragma warning(disable: 4251)\n#pragma warning(disable: 4275)" EXPORT_DEFINE ${EXPORT_DEFINE})
    endif ()
    configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Urho3D.h.in ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.h)
endif ()

# Install headers for using the Urho3D library
install_header_files (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION ${DEST_INCLUDE_DIR} FILES_MATCHING PATTERN *.h USE_FILE_SYMLINK)    # Note: the trailing slash is significant
install_header_files (FILES ${CMAKE_CURRENT_BINARY_DIR}/librevision.h ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.h DESTINATION ${DEST_INCLUDE_DIR})

# Generate platform specific pkg-config file for the benefit of Urho3D library users via SDK without CMake
get_directory_property (URHO3D_COMPILE_DEFINITIONS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMPILE_DEFINITIONS)
list (REMOVE_ITEM URHO3D_COMPILE_DEFINITIONS HAVE_STDINT_H GLEW_STATIC GLEW_NO_GLU)     # Remove those defines that are only used for building the library and not needed by library user
if (ABSOLUTE_PATH_LIBS)
    string (REPLACE ";" "\" \"" URHO3D_ABS_PATH_LIBS "\"${ABSOLUTE_PATH_LIBS}\"")   # Note: need to always "stringify" a variable in list context for replace to work correctly, besides the list could be empty
    string (REPLACE "${SYSROOT}" "\${pc_sysrootdir}" URHO3D_ABS_PATH_LIBS "${URHO3D_ABS_PATH_LIBS}")
endif ()
set (LIB_NAME Urho3D)
if (MINGW)
    if (CMAKE_BUILD_TYPE STREQUAL Debug)
        set (LIB_NAME ${LIB_NAME}_d)
    endif ()
    if (URHO3D_LIB_TYPE STREQUAL SHARED)
        set (LIB_NAME ${LIB_NAME}.dll)
    endif ()
endif ()
if (MSVC)
    # todo: Add a post build command to adjust the LIB_NAME when in Debug configuration (CMake/VS generator is multi-config)
    set (DASH /)
    set (LIB_DIR "/LIBPATH:\"\${libdir}\"")
    string (REPLACE ";" ".lib\" \"" URHO3D_LIBS "\"${LIB_NAME};${LIBS}.lib\"")
else ()
    set (DASH -)
    set (LIB_DIR "-L\"\${libdir}\"")
    string (REPLACE ";" " -l" URHO3D_LIBS "-l${LIB_NAME};${LIBS}")
endif ()
string (REPLACE ";" " ${DASH}D" URHO3D_COMPILE_DEFINITIONS ";${URHO3D_COMPILE_DEFINITIONS}")
get_directory_property (GLOBAL_INCLUDE_DIRS DIRECTORY ${CMAKE_SOURCE_DIR} INCLUDE_DIRECTORIES)
if (GLOBAL_INCLUDE_DIRS)
    string (REPLACE ";" "\" ${DASH}I\"" GLOBAL_INCLUDE_DIRS "${DASH}I\"${GLOBAL_INCLUDE_DIRS}\"")
    string (REPLACE "${SYSROOT}" "" GLOBAL_INCLUDE_DIRS ${GLOBAL_INCLUDE_DIRS})
endif ()
set (ENGINE_INCLUDE_DIRS "${DASH}I\"\${includedir}\" ${DASH}I\"\${includedir}/${PATH_SUFFIX}/ThirdParty\"")
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Urho3D.pc.in ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.pc @ONLY)
if (ANDROID)
    set (RENAME RENAME Urho3D-${ANDROID_NDK_ABI_NAME}.pc)
endif ()
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/Urho3D.pc DESTINATION ${DEST_PKGCONFIG_DIR} ${RENAME})

# Setup the compiler flags for building shared library (do this here so that it does not interfere with the pkg-config file generation above)
if (URHO3D_LIB_TYPE STREQUAL SHARED)
    # Hide the symbols that are not explicitly marked for export
    add_compiler_export_flags ()
    # Use PIC on platforms that support it (shared library type has this property set to true by default, so we only have to deal with those static ones that the shared library links against)
    set_target_properties (${STATIC_LIBRARY_TARGETS} PROPERTIES POSITION_INDEPENDENT_CODE true)
    if (NOT MSVC AND NOT (CMAKE_CROSSCOMPILING AND MINGW) AND CMAKE_VERSION VERSION_LESS 2.8.9)  # todo: Remove this when CMake minimum version is 2.8.9
        set_property (TARGET ${STATIC_LIBRARY_TARGETS} APPEND PROPERTY COMPILE_FLAGS -fPIC)
    endif ()
endif ()

# Define post build steps
if (ANDROID_NDK_GDB)
    # Copy the library while it still has debug symbols for ndk-gdb
    add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${TARGET_NAME}> ${NDK_GDB_SOLIB_PATH}
        COMMENT "Copying Urho3D library with debug symbols to ${NDK_GDB_SOLIB_PATH} directory")
endif ()
if (URHO3D_LIB_TYPE STREQUAL SHARED AND (ANDROID OR RPI OR IOS))
    # Strip the output shared library for embedded devices
    add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${TARGET_NAME}>
        COMMENT "Stripping Urho3D shared library")
endif ()
if (URHO3D_SCP_TO_TARGET)
    # Ensure SCP is the last command
    add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND scp $<TARGET_FILE:${TARGET_NAME}> ${URHO3D_SCP_TO_TARGET} || exit 0
        COMMENT "Scp-ing Urho3D library to target system")
endif ()
