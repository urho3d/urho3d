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

# Set the build type if not explicitly set, for single-configuration generator only
if (CMAKE_GENERATOR STREQUAL Xcode)
    set (XCODE TRUE)
endif ()
if (NOT MSVC AND NOT XCODE AND NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Release")
endif ()

# Enable SSE instruction set. Requires Pentium III or Athlon XP processor at minimum.
if (NOT DEFINED ENABLE_SSE)
    set (ENABLE_SSE 1)
endif ()
if (ENABLE_SSE)
    add_definitions (-DENABLE_SSE)
endif ()

# Enable structured exception handling and minidumps on MSVC only.
if (MSVC)
    if (NOT DEFINED ENABLE_MINIDUMPS)
        set (ENABLE_MINIDUMPS 1)
    endif ()
    if (ENABLE_MINIDUMPS)
        add_definitions (-DENABLE_MINIDUMPS)
    endif ()
endif ()

# By default use the MSVC dynamic runtime. To eliminate the need to distribute the runtime installer,
# this can be switched off if not using Urho3D as a shared library.
if (MSVC)
    if (USE_STATIC_RUNTIME)
        set (RELEASE_RUNTIME "/MT")
        set (DEBUG_RUNTIME "/MTd")
    else ()
        set (RELEASE_RUNTIME "")
        set (DEBUG_RUNTIME "")
    endif ()
endif ()

# Enable file watcher support for automatic resource reloads.
add_definitions (-DENABLE_FILEWATCHER)

# Enable profiling. If disabled, autoprofileblocks become no-ops and the Profiler subsystem is not
# instantiated.
add_definitions (-DENABLE_PROFILING)

# Enable logging. If disabled, LOGXXXX macros become no-ops and the Log subsystem is not instantiated.
add_definitions (-DENABLE_LOGGING)

# If not on MSVC, enable use of OpenGL instead of Direct3D9 (either not compiling on Windows or
# with a compiler that may not have an up-to-date DirectX SDK). This can also be unconditionally
# enabled, but Windows graphics card drivers are usually better optimized for Direct3D.
if (NOT MSVC)
    set (USE_OPENGL 1)
endif ()
if (USE_OPENGL)
    add_definitions (-DUSE_OPENGL)
endif ()

# If not on Windows, enable Unix mode for kNet library.
if (NOT WIN32)
    add_definitions (-DUNIX)
endif ()

# If using Windows and not OpenGL, find DirectX SDK include & library directories
# Note: if a recent Windows SDK is installed instead, it will be possible to compile without;
# therefore do not log a fatal error in that case
if (WIN32 AND NOT USE_OPENGL)
    find_package (Direct3D)
    if (DIRECT3D_FOUND)
        include_directories (${DIRECT3D_INCLUDE_DIR})
    endif ()
endif ()

# For Raspbery Pi, find Broadcom VideoCore IV firmware
if (RASPI)
    find_package (BCM_VC REQUIRED)
    include_directories (${BCM_VC_INCLUDE_DIR})    
endif ()

# Platform and compiler specific options
if (IOS)
    # IOS-specific setup
    add_definitions (-DIOS)
    if (ENABLE_64BIT)
        set (CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_INCLUDING_64_BIT))
    else ()
        set (CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_32_BIT))
    endif ()
    set (CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
    if (NOT MACOSX_BUNDLE_GUI_IDENTIFIER)
        set (MACOSX_BUNDLE_GUI_IDENTIFIER "com.googlecode.urho3d")
    endif ()
    set (CMAKE_OSX_SYSROOT "iphoneos")    # Set to "Latest iOS"
elseif (XCODE)
    # MacOSX-Xcode-specific setup
    if (NOT ENABLE_64BIT)
        set (CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_32_BIT))
    endif ()
    set (CMAKE_OSX_SYSROOT "")        # Set to "Current OS X"
    #set (CMAKE_OSX_SYSROOT "macosx") # Set to "Latest OS X"
endif ()
if (MSVC)
    # Visual Studio-specific setup
    add_definitions (-D_CRT_SECURE_NO_WARNINGS)
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${DEBUG_RUNTIME}")
    set (CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE} ${RELEASE_RUNTIME} /fp:fast /Zi /GS-")
    set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELWITHDEBINFO}")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEBUG_RUNTIME}")
    set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} ${RELEASE_RUNTIME} /fp:fast /Zi /GS- /D _SECURE_SCL=0")
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
    # SSE flag is redundant if already compiling as 64bit
    if (ENABLE_SSE AND NOT ENABLE_64BIT)
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /arch:SSE")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE")
    endif ()
    set (CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF /DEBUG")
    set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF")
else ()
    # GCC-specific setup
    if (ANDROID)
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -fstack-protector")
        if (ENABLE_64BIT)
            # For now just reference it to suppress "unused variable" warning
        endif ()
    elseif (NOT IOS)
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffast-math")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -ffast-math")
        if (RASPI)
            add_definitions (-DRASPI)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -Wno-psabi")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -Wno-psabi")
        elseif (ENABLE_64BIT)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
        else ()
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
            if (ENABLE_SSE)
                if (NOT WIN32)
                    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse")
                    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse")
                else ()
                    message (STATUS "Using SSE2 instead of SSE because SSE fails on some Windows ports of GCC")
                    message (STATUS "Disable SSE with the CMake option -DENABLE_SSE=0 if this is not desired")
                    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse2")
                    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
                endif ()
            endif ()
        endif ()
        if (WIN32)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
            # Additional compiler flags for Windows ports of GCC
            set (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")
            set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")
            # Reduce GCC optimization level from -O3 to -O2 for stability in RELEASE build type
            set (CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
            set (CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
        endif ()
        set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG -D_DEBUG")
        set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -D_DEBUG")
    endif ()
endif ()

if (URHO3D_BUILD_TYPE)
    string (TOUPPER ${URHO3D_BUILD_TYPE} URHO3D_BUILD_TYPE)
endif ()

# Include CMake builtin module for building shared library support
include (GenerateExportHeader)

# Determine the project root directory
get_filename_component (PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR} PATH)

# Override builtin macro and function to suit our need, always generate header file regardless of target type...
macro (_DO_SET_MACRO_VALUES TARGET_LIBRARY)
    set (DEFINE_DEPRECATED)
    set (DEFINE_EXPORT)
    set (DEFINE_IMPORT)
    set (DEFINE_NO_EXPORT)

    if (COMPILER_HAS_DEPRECATED_ATTR)
        set (DEFINE_DEPRECATED "__attribute__ ((__deprecated__))")
    elseif (COMPILER_HAS_DEPRECATED)
        set (DEFINE_DEPRECATED "__declspec(deprecated)")
    endif ()

    get_property (type TARGET ${TARGET_LIBRARY} PROPERTY TYPE)

    if (type MATCHES "STATIC|SHARED")
        if (WIN32)
            set (DEFINE_EXPORT "__declspec(dllexport)")
            set (DEFINE_IMPORT "__declspec(dllimport)")
        elseif (COMPILER_HAS_HIDDEN_VISIBILITY AND USE_COMPILER_HIDDEN_VISIBILITY)
            set (DEFINE_EXPORT "__attribute__((visibility(\"default\")))")
            set (DEFINE_IMPORT "__attribute__((visibility(\"default\")))")
            set (DEFINE_NO_EXPORT "__attribute__((visibility(\"hidden\")))")
        endif ()
    endif ()
endmacro ()
# ... except, when target is a module library type
function (GENERATE_EXPORT_HEADER TARGET_LIBRARY)
    get_property (type TARGET ${TARGET_LIBRARY} PROPERTY TYPE)
    if (${type} MATCHES MODULE)
        message (WARNING "This macro should not be used with libraries of type MODULE")
        return ()
    endif ()
    _test_compiler_hidden_visibility()
    _test_compiler_has_deprecated()
    _do_set_macro_values(${TARGET_LIBRARY})
    _do_generate_export_header(${TARGET_LIBRARY} ${ARGN})
endfunction ()

# Override builtin function to suit our need, takes care of C flags as well as CXX flags
function (add_compiler_export_flags)
    if (NOT ANDROID AND NOT MSVC AND NOT DEFINED USE_COMPILER_HIDDEN_VISIBILITY AND NOT DEFINED COMPILER_HAS_DEPRECATED)
        message (STATUS "Following tests check whether compiler installed in this system has export/import and deprecated attributes support")
        message (STATUS "CMake will generate a suitable export header file for this system based on the test result")
        message (STATUS "It is OK to proceed to build Urho3D regardless of the test result")
    endif ()
    _test_compiler_hidden_visibility ()
    _test_compiler_has_deprecated ()

    if (NOT (USE_COMPILER_HIDDEN_VISIBILITY AND COMPILER_HAS_HIDDEN_VISIBILITY))
        # Just return if there are no flags to add.
        return ()
    endif ()

    set (EXTRA_FLAGS "-fvisibility=hidden")
    # Either return the extra flags needed in the supplied argument, or to the
    # CMAKE_C_FLAGS if no argument is supplied.
    if (ARGV1)
        set (${ARGV1} "${EXTRA_FLAGS}" PARENT_SCOPE)
    else ()
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_FLAGS}" PARENT_SCOPE)
    endif ()

    if (COMPILER_HAS_HIDDEN_INLINE_VISIBILITY)
        set (EXTRA_FLAGS "${EXTRA_FLAGS} -fvisibility-inlines-hidden")
    endif ()

    # Either return the extra flags needed in the supplied argument, or to the
    # CMAKE_CXX_FLAGS if no argument is supplied.
    if (ARGV0)
        set (${ARGV0} "${EXTRA_FLAGS}" PARENT_SCOPE)
    else ()
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_FLAGS}" PARENT_SCOPE)
    endif ()
endfunction ()

# Macro for precompiled headers
macro (enable_pch)
    if (MSVC)
        foreach (FILE ${SOURCE_FILES})
            if (FILE MATCHES \\.cpp$)
                if (FILE MATCHES Precompiled\\.cpp$)
                    set_source_files_properties(${FILE} PROPERTIES COMPILE_FLAGS "/YcPrecompiled.h")
                else ()
                    set_source_files_properties(${FILE} PROPERTIES COMPILE_FLAGS "/YuPrecompiled.h")
                endif ()
            endif ()
        endforeach ()
    else ()
        # TODO: to enable usage of precompiled header in GCC, for now just make sure the correct Precompiled.h is found in the search
        foreach (FILE ${SOURCE_FILES})
            if (FILE MATCHES Precompiled\\.h$)
                get_filename_component (PATH ${FILE} PATH)
                include_directories (${PATH})
                break ()
            endif ()
        endforeach ()
    endif ()
endmacro ()

# Macro for setting up dependency lib for compilation and linking of a target
macro (setup_target)
    # Include directories
    include_directories (${LIBS} ${INCLUDE_DIRS_ONLY})
    # Link libraries
    define_dependency_libs (${TARGET_NAME})
    string (REGEX REPLACE \\.\\./|ThirdParty/|Engine/|Extras/|/include|/src "" STRIP_LIBS "${LIBS};${LINK_LIBS_ONLY}")
    target_link_libraries (${TARGET_NAME} ${STRIP_LIBS} ${ABSOLUTE_PATH_LIBS})
endmacro ()

# Macro for setting up a library target
macro (setup_library)
    add_library (${TARGET_NAME} ${LIB_TYPE} ${SOURCE_FILES})
    setup_target ()

    if (CMAKE_PROJECT_NAME STREQUAL Urho3D AND NOT LIB_TYPE STREQUAL SHARED AND URHO3D_BUILD_TYPE MATCHES STATIC|SHARED)
        set (STATIC_LIBRARY_TARGETS ${STATIC_LIBRARY_TARGETS} ${TARGET_NAME} PARENT_SCOPE)
        if (URHO3D_BUILD_TYPE STREQUAL SHARED)
            set_target_properties (${TARGET_NAME} PROPERTIES COMPILE_DEFINITIONS URHO3D_EXPORTS)
        elseif (URHO3D_BUILD_TYPE STREQUAL STATIC)
            set_target_properties (${TARGET_NAME} PROPERTIES COMPILE_DEFINITIONS URHO3D_STATIC_DEFINE)
        endif ()

        if (MSVC)
            # Specific to VS generator
            # On VS2008 we need to add a backslash to the IntDir, on later VS it already exists
            if (CMAKE_GENERATOR MATCHES "2008")
                set (INTDIR_SLASH "\\")
            else ()
                set (INTDIR_SLASH "")
            endif ()
            if (USE_MKLINK)
                set (SYMLINK ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET_NAME}.lnk)
                add_custom_command (TARGET ${TARGET_NAME} PRE_LINK
                    COMMAND rd \"${SYMLINK}\"
                    COMMAND mklink /D \"${SYMLINK}\" \"$(ProjectDir)$(IntDir)\"
                    COMMENT "Creating a symbolic link pointing to object file directory")
            else ()
                file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET_NAME}.dir)
                add_custom_command (TARGET ${TARGET_NAME} PRE_LINK
                    COMMAND copy /B \"$(ProjectDir)$(IntDir)${INTDIR_SLASH}*.obj\" \"$(ProjectDir)CMakeFiles\\${TARGET_NAME}.dir\"
                    COMMENT "Copying object files to a common location also used by Makefile generator")
            endif ()
        elseif (XCODE)
            # Specific to Xcode generator
            set (SYMLINK ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET_NAME}.lnk)
            add_custom_command (TARGET ${TARGET_NAME} PRE_LINK
                COMMAND rm -f ${SYMLINK} && ln -s "$(OBJECT_FILE_DIR)-$(CURRENT_VARIANT)/$(CURRENT_ARCH)" ${SYMLINK}
                COMMENT "Creating a symbolic link pointing to object file directory")
        endif ()
    endif ()
endmacro ()

# Macro for setting up an executable target
macro (setup_executable)
    add_executable (${TARGET_NAME} ${EXE_TYPE} ${SOURCE_FILES})
    setup_target ()
    if (MSVC)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETPATH)\" \"${PROJECT_ROOT_DIR}/Bin\"
            COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETDIR)$(TARGETNAME).pdb\" \"${PROJECT_ROOT_DIR}/Bin\"
            COMMENT "Copying executable and debug files to Bin directory")
    elseif (IOS)
        set_target_properties (${TARGET_NAME} PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
    else ()
        get_target_property (EXECUTABLE_NAME ${TARGET_NAME} LOCATION)
        if (CMAKE_CROSSCOMPILING)
            file (MAKE_DIRECTORY ${PROJECT_ROOT_DIR}/Bin-CC)
            add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${EXECUTABLE_NAME} ${PROJECT_ROOT_DIR}/Bin-CC)
            if (SCP_TO_TARGET)
                add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND scp ${EXECUTABLE_NAME} ${SCP_TO_TARGET} || exit 0)
            endif ()
        else ()
            add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${EXECUTABLE_NAME} ${PROJECT_ROOT_DIR}/Bin)
        endif ()
    endif ()
endmacro ()

# Macro for setting up linker flags for Mac OS X desktop build
macro (setup_macosx_linker_flags LINKER_FLAGS)
    # Framework list to link against 
    set (FLAGS "-framework AudioUnit -framework Carbon -framework Cocoa -framework CoreAudio -framework ForceFeedback -framework IOKit -framework OpenGL -framework CoreServices")
    # LuaJIT specific - extra linker flags for linking against LuaJIT in 64-bit Mac OS X desktop build
    if (ENABLE_LUA_JIT AND ENABLE_64BIT)
        if (URHO3D_BUILD_TYPE STREQUAL SHARED)
            set (FLAGS "${FLAGS} -image_base 7fff04c4a000")
        else ()
            set (FLAGS "${FLAGS} -pagezero_size 10000 -image_base 100000000")
        endif ()
    endif ()
    set (${LINKER_FLAGS} ${FLAGS})
endmacro ()

# Macro for setting up linker flags for IOS build
macro (setup_ios_linker_flags LINKER_FLAGS)
    # Framework list to link against 
    set (${LINKER_FLAGS} "-framework AudioToolbox -framework CoreAudio -framework CoreGraphics -framework Foundation -framework OpenGLES -framework QuartzCore -framework UIKit")
endmacro ()

# Macro for setting up an executable target with resources to copy
macro (setup_main_executable)
    # Define resource files
    if (XCODE)
        set (RESOURCE_FILES ${PROJECT_ROOT_DIR}/Bin/CoreData ${PROJECT_ROOT_DIR}/Bin/Data)
        set_source_files_properties(${RESOURCE_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
        set (SOURCE_FILES ${SOURCE_FILES} ${RESOURCE_FILES})
    endif ()

    # Define external dependency libraries, for the convenience of other main target (not in Urho3D project) referencing Urho3D as external library
    if (NOT CMAKE_PROJECT_NAME STREQUAL Urho3D AND NOT TARGET_NAME STREQUAL Main)
        define_dependency_libs (Main)
    endif ()

    # Setup target
    if (ANDROID)
        # Add SDL native init function
        if (CMAKE_PROJECT_NAME STREQUAL Urho3D)
            set (SOURCE_FILES ${SOURCE_FILES} ${PROJECT_SOURCE_DIR}/ThirdParty/SDL/src/main/android/SDL_android_main.c)
        elseif (EXISTS $ENV{URHO3D_HOME}/Source/ThirdParty/SDL/src/main/android/SDL_android_main.c)
            set (SOURCE_FILES ${SOURCE_FILES} $ENV{URHO3D_HOME}/Source/ThirdParty/SDL/src/main/android/SDL_android_main.c)
        endif ()
        # Setup target as main shared library
        set (LIB_TYPE SHARED)
        setup_library ()
        # Copy other dependent shared libraries to Android library output path
        foreach(FILE ${ABSOLUTE_PATH_LIBS})
            get_filename_component (EXT ${FILE} EXT)
            if (EXT STREQUAL .so)
                get_filename_component (NAME ${FILE} NAME)
                add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${FILE} ${ANDROID_LIBRARY_OUTPUT_PATH}
                    COMMAND ${CMAKE_COMMAND} ARGS -E touch ${ANDROID_LIBRARY_OUTPUT_PATH}/${NAME}
                    COMMENT "Copying ${NAME} to target library directory")
            endif ()
        endforeach ()
        # Copy target main shared library to Android library output path
        file (MAKE_DIRECTORY ${ANDROID_LIBRARY_OUTPUT_PATH})
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${TARGET_NAME}>
            COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different $<TARGET_FILE:${TARGET_NAME}> ${ANDROID_LIBRARY_OUTPUT_PATH}
            COMMAND ${CMAKE_COMMAND} ARGS -E touch ${ANDROID_LIBRARY_OUTPUT_PATH}/lib${TARGET_NAME}.so
            COMMENT "Stripping and copying lib${TARGET_NAME}.so to target library directory")
    else ()
        if (WIN32)
            set (EXE_TYPE WIN32)
        elseif (IOS)
            set (EXE_TYPE MACOSX_BUNDLE)
            setup_ios_linker_flags (CMAKE_EXE_LINKER_FLAGS)
        elseif (APPLE)
            setup_macosx_linker_flags (CMAKE_EXE_LINKER_FLAGS)
        endif ()
        setup_executable ()
    endif ()

    if (XCODE)
        get_target_property (TARGET_LOC ${TARGET_NAME} LOCATION)
        if (IOS)
            # Define a custom target to check for resource modification
            string (REGEX REPLACE "/Contents/MacOS" "" TARGET_LOC ${TARGET_LOC})    # The regex replacement is temporary workaround to correct the wrong location caused by CMake/Xcode generator bug
            add_custom_target (RESOURCE_CHECK_${TARGET_NAME} ALL
                \(\( `find ${RESOURCE_FILES} -newer ${TARGET_LOC} 2>/dev/null |wc -l` \)\) && touch -cm ${SOURCE_FILES} || exit 0
                COMMENT "Checking for changes in the Resource folders")
            add_dependencies (${TARGET_NAME} RESOURCE_CHECK_${TARGET_NAME})
        else ()
            # Create symbolic links to allow debugging/running the main executable within Xcode itself
            get_filename_component (PATH ${TARGET_LOC} PATH)
            file (RELATIVE_PATH REL_PATH ${PATH} ${PROJECT_ROOT_DIR}/Bin)
            add_custom_command (TARGET ${TARGET_NAME} POST_BUILD
                COMMAND for dir in CoreData Data\; do cmake -E create_symlink ${REL_PATH}/$$dir ${PATH}/$$dir\; done
                COMMENT "Creating symbolic links to allow debugging/running the main executable within Xcode itself")
        endif ()
    endif ()
endmacro ()

# Macro for adjusting library output name by dropping _suffix from the target name
macro (adjust_library_name)
    string (REGEX REPLACE "_.*$" "" LIB_NAME ${TARGET_NAME})
    set_target_properties (${TARGET_NAME} PROPERTIES OUTPUT_NAME ${LIB_NAME})
endmacro ()

# Macro for defining external library dependencies
# The purpose of this macro is emulate CMake to set the external library dependencies transitively
# It works for both targets setup within Urho3D project and outside Urho3D project that uses Urho3D as external static/shared library
macro (define_dependency_libs TARGET)
    # ThirdParty/SDL external dependency
    if (${TARGET} MATCHES SDL|Main)
        if (WIN32)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} user32 gdi32 winmm imm32 ole32 oleaut32 version uuid)
        elseif (APPLE)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} dl pthread)
        elseif (ANDROID)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} dl log)
        else ()
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} dl pthread rt)
            if (RASPI)
                set (ABSOLUTE_PATH_LIBS ${ABSOLUTE_PATH_LIBS} ${BCM_VC_LIBRARIES})
            endif ()
        endif ()
    endif ()

    # ThirdParty/kNet & ThirdParty/Civetweb external dependency
    if (${TARGET} MATCHES Civetweb|kNet|Main)
        if (WIN32)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} ws2_32)
        elseif (NOT ANDROID)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} pthread)
        endif ()
    endif ()

    # ThirdParty/LuaJIT external dependency
    if (ENABLE_LUA_JIT AND ${TARGET} MATCHES LuaJIT|Main)
        if (NOT WIN32)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} dl m)
            if (NOT APPLE)
                set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-E")
            endif ()
        endif ()
    endif ()

    # Engine/Core external dependency
    if (${TARGET} MATCHES Core|Main)
        if (WIN32)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} winmm)
            if (ENABLE_MINIDUMPS)
                set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} dbghelp)
            endif ()
        elseif (NOT ANDROID)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} pthread)
        endif ()
    endif ()

    # Engine/Graphics external dependency
    if (${TARGET} MATCHES Graphics|Main)
        if (USE_OPENGL)
            if (WIN32)
                set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} opengl32)
            elseif (ANDROID)
                set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} GLESv1_CM GLESv2)
            elseif (NOT APPLE AND NOT RASPI)
                set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} GL)
            endif ()
        else ()
            set (ABSOLUTE_PATH_LIBS ${ABSOLUTE_PATH_LIBS} ${DIRECT3D_LIBRARY})
        endif ()
    endif ()

    # Main external dependency
    if (${TARGET} STREQUAL Main AND URHO3D_LIBRARIES)
        set (ABSOLUTE_PATH_LIBS ${ABSOLUTE_PATH_LIBS} ${URHO3D_LIBRARIES})
    endif ()

    if (LINK_LIBS_ONLY)
        list (SORT LINK_LIBS_ONLY)
        list (REMOVE_DUPLICATES LINK_LIBS_ONLY)
    endif ()
endmacro ()
