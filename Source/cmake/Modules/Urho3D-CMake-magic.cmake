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

# Disable unnecessary build types
set (CMAKE_CONFIGURATION_TYPES "RelWithDebInfo;Debug;Release" CACHE STRING "Configurations" FORCE)

# Set the build type if not explicitly set, for single-configuration generator only
if (CMAKE_GENERATOR STREQUAL Xcode)
    set (XCODE TRUE)
endif ()
if (NOT MSVC AND NOT XCODE AND NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Release")
endif ()

# On Visual Studio, whether to enable 64-bit build depends on the generator used
if (MSVC AND CMAKE_GENERATOR MATCHES "Win64")
    set (ENABLE_64BIT 1)
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
if (WIN32 AND NOT USE_OPENGL)
    find_package (Direct3D REQUIRED)
    include_directories (${DIRECT3D_INCLUDE_DIR})
    link_directories (${DIRECT3D_LIBRARY_DIR})
endif ()

# For Raspbery Pi, find Broadcom VideoCore IV firmware 
if (RASPI)
    find_package (BCM_VC REQUIRED)
    link_directories (${BCM_VC_LIBRARY_DIR})
endif ()

# Platform and compiler specific options
if (IOS)
    # IOS-specific setup
    add_definitions (-DIOS)
    set (CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_32_BIT))
    set (CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
    set (MACOSX_BUNDLE_GUI_IDENTIFIER "com.googlecode.urho3d")
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
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
    set (CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE} /MT /fp:fast /Zi /GS-")
    set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELWITHDEBINFO}")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} /MT /fp:fast /Zi /GS- /D _SECURE_SCL=0")
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
    elseif (NOT IOS)
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -ffast-math")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -O2 -ffast-math")
        if (RASPI)
            add_definitions (-DRASPI)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard")
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
                    message ("-- Using SSE2 instead of SSE because SSE fails on some Windows ports of GCC.")
                    message ("-- Disable SSE with the CMake option -DENABLE_SSE=0 if this is not desired.")
                    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse2")
                    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
                endif ()
            endif ()
        endif ()
        if (WIN32)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
        endif ()
    endif ()
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
endif ()

if (URHO3D_BUILD_TYPE)
    string (TOUPPER ${URHO3D_BUILD_TYPE} URHO3D_BUILD_TYPE)
endif ()

# Include CMake builtin module for building shared library support
include (GenerateExportHeader)

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
        foreach(FILE ${SOURCE_FILES})
            if (${FILE} MATCHES "[A-Za-z0-9 _/]*[.]cpp")
                if (${FILE} MATCHES "Precompiled.cpp$")
                    set_source_files_properties(${FILE} PROPERTIES COMPILE_FLAGS "/YcPrecompiled.h")
                else ()
                    set_source_files_properties(${FILE} PROPERTIES COMPILE_FLAGS "/YuPrecompiled.h")
                endif ()
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
    string (REGEX REPLACE "\\.\\./|ThirdParty/|Engine/|Extras/|/Include|/include|/src" "" STRIP_LIBS "${LIBS};${LINK_LIBS_ONLY}")
    target_link_libraries (${TARGET_NAME} ${STRIP_LIBS})
endmacro ()

# Macro for setting up a library target
macro (setup_library)
    add_library (${TARGET_NAME} ${LIB_TYPE} ${SOURCE_FILES})
    setup_target ()
    
    if (CMAKE_PROJECT_NAME STREQUAL Urho3D AND NOT LIB_TYPE STREQUAL SHARED AND URHO3D_BUILD_TYPE MATCHES "STATIC|SHARED" AND NOT IOS AND NOT ANDROID)
        set (STATIC_LIBRARY_TARGETS ${STATIC_LIBRARY_TARGETS} ${TARGET_NAME} PARENT_SCOPE)
        if (URHO3D_BUILD_TYPE STREQUAL SHARED)
            set_target_properties (${TARGET_NAME} PROPERTIES COMPILE_DEFINITIONS URHO3D_EXPORTS)
        elseif (URHO3D_BUILD_TYPE STREQUAL STATIC)
            set_target_properties (${TARGET_NAME} PROPERTIES COMPILE_DEFINITIONS URHO3D_STATIC_DEFINE)
        endif ()

        if (MSVC)
            # Specific to VS generator
            if (USE_MKLINK)
                set (SYMLINK ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET_NAME}.lnk)
                add_custom_command (TARGET ${TARGET_NAME} PRE_LINK
                    COMMAND rd \"${SYMLINK}\"
                    COMMAND mklink /D \"${SYMLINK}\" \"$(ProjectDir)$(IntDir)\"
                    COMMENT "Creating a symbolic link pointing to object file directory")
            else ()
                file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET_NAME}.dir)
                add_custom_command (TARGET ${TARGET_NAME} PRE_LINK
                    COMMAND copy /B \"$(ProjectDir)$(IntDir)*.obj\" \"$(ProjectDir)CMakeFiles\\${TARGET_NAME}.dir\"
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
            COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETPATH)\" \"${PROJECT_SOURCE_DIR}/../Bin\"
            COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETDIR)$(TARGETNAME).pdb\" \"${PROJECT_SOURCE_DIR}/../Bin\"
            COMMENT "Copying executable and debug files to Bin directory")
    elseif (IOS)
        set_target_properties (${TARGET_NAME} PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
    else ()
        get_target_property (EXECUTABLE_NAME ${TARGET_NAME} LOCATION)
        if (CMAKE_CROSSCOMPILING)
            file (MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/../Bin-CC)
            add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${EXECUTABLE_NAME} ${PROJECT_SOURCE_DIR}/../Bin-CC)
            if (SCP_TO_TARGET)
                add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND scp ${EXECUTABLE_NAME} ${SCP_TO_TARGET} || exit 0)
            endif ()
        else ()
            add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${EXECUTABLE_NAME} ${PROJECT_SOURCE_DIR}/../Bin)
        endif ()
    endif ()
endmacro ()

# Macro for setting up linker flags to link against the framework for Mac OS X desktop build
macro (setup_macosx_framework FRAMEWORKS)
    set (${FRAMEWORKS} "-framework AudioUnit -framework Carbon -framework Cocoa -framework CoreAudio -framework ForceFeedback -framework IOKit -framework OpenGL -framework CoreServices")
endmacro ()

# Macro for setting up linker flags to link against the framework for IOS build
macro (setup_ios_framework FRAMEWORKS)
    set (${FRAMEWORKS} "-framework AudioToolbox -framework CoreAudio -framework CoreGraphics -framework Foundation -framework OpenGLES -framework QuartzCore -framework UIKit")
endmacro ()

# Macro for setting up an executable target with resources to copy
macro (setup_main_executable)
    # Define resource files
    if (APPLE)
        set (RESOURCE_FILES ${PROJECT_SOURCE_DIR}/../Bin/CoreData ${PROJECT_SOURCE_DIR}/../Bin/Data)
        set_source_files_properties(${RESOURCE_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
        set (SOURCE_FILES ${SOURCE_FILES} ${RESOURCE_FILES})
    endif ()

    # Define external dependency libraries, for the convenience of other main target (not in Urho3D project) referencing Urho3D as external library
    if (NOT TARGET_NAME STREQUAL Main)
        define_dependency_libs (Main)
    endif ()

    # Setup target
    if (ANDROID)
        set (LIB_TYPE SHARED)
        setup_library ()
        # Strip the output shared library
        get_target_property (TARGET_LOC ${TARGET_NAME} LOCATION)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} ${TARGET_LOC})
    else ()
        if (WIN32)
            set (EXE_TYPE WIN32)
        elseif (IOS)
            set (EXE_TYPE MACOSX_BUNDLE)
            setup_ios_framework (CMAKE_EXE_LINKER_FLAGS)
        elseif (APPLE)
            setup_macosx_framework (CMAKE_EXE_LINKER_FLAGS)
        endif ()
        setup_executable ()
    endif ()

    # Define a custom target to check for resource modification
    if (IOS)
        get_target_property (TARGET_LOC ${TARGET_NAME} LOCATION)
        string (REGEX REPLACE "/Contents/MacOS" "" TARGET_LOC ${TARGET_LOC})    # The regex replacement is temporary workaround to correct the wrong location caused by CMake/Xcode generator bug
        add_custom_target (RESOURCE_CHECK_${TARGET_NAME} ALL
            \(\( `find ${RESOURCE_FILES} -newer ${TARGET_LOC} 2>/dev/null |wc -l` \)\) && touch -cm ${SOURCE_FILES} || exit 0
            COMMENT "This is a dummy target to check for changes in the Resource folders")
        add_dependencies (${TARGET_NAME} RESOURCE_CHECK_${TARGET_NAME})
    endif ()
endmacro ()

# Macro for adjusting library output name by dropping _suffix from the target name
macro (adjust_library_name)
    string (REGEX REPLACE "_.*$" "" LIB_NAME ${TARGET_NAME}) 
    set_target_properties (${TARGET_NAME} PROPERTIES OUTPUT_NAME ${LIB_NAME})
endmacro ()

# Macro for defining external library dependencies
# The purpose of this macro is emulate CMake way to set the external library dependencies transitively to a Main target (in other CMake build script) that uses Urho3D static/shared library 
macro (define_dependency_libs TARGET)
    # ThirdParty/SDL external dependency
    if (${TARGET} MATCHES "SDL|Main")
        if (WIN32)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} user32 gdi32 winmm imm32 ole32 oleaut32 version uuid)
        elseif (APPLE)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} dl pthread)
        elseif (ANDROID)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} dl log)
        else ()
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} dl pthread rt)
            if (RASPI)
                set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} bcm_host)
            endif ()
        endif ()
    endif ()

    # ThirdParty/kNet external dependency
    if (${TARGET} MATCHES "kNet|Main")
        if (WIN32)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} ws2_32.lib)
        elseif (NOT ANDROID)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} pthread)
        endif ()
    endif ()
    
    # Engine/Core external dependency
    if (${TARGET} MATCHES "Core|Main")
        if (WIN32)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} winmm.lib)
            if (ENABLE_MINIDUMPS)
                set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} dbghelp.lib)
            endif ()
        elseif (NOT ANDROID)
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} pthread)
        endif ()
    endif ()
    
    # Engine/Graphics external dependency
    if (${TARGET} MATCHES "Graphics|Main")
        if (USE_OPENGL)
            if (WIN32)
                set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} opengl32)
            elseif (ANDROID OR RASPI)
                set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} GLESv1_CM GLESv2)
            elseif (NOT APPLE)
                set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} GL)
            endif ()
        else ()
            set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} d3d9)
        endif ()
    endif ()
    
    # Main external dependency
    if (${TARGET} STREQUAL Main AND NOT CMAKE_PROJECT_NAME STREQUAL Urho3D)
        set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} Urho3D)
    endif ()
    
    if (LINK_LIBS_ONLY)
        list (SORT LINK_LIBS_ONLY)
        list (REMOVE_DUPLICATES LINK_LIBS_ONLY)
    endif ()
endmacro ()
