include (CheckIncludeFiles)

# Disable unnecessary build types
set (CMAKE_CONFIGURATION_TYPES "RelWithDebInfo;Debug;Release" CACHE STRING "Configurations" FORCE)

# Set the build type if not explicitly set, for single-configuration generator only
if (NOT MSVC AND NOT CMAKE_GENERATOR STREQUAL "Xcode" AND NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "RelWithDebInfo")
endif ()

# Set project name
project (Urho3D)

# Set minimum version
cmake_minimum_required (VERSION 2.6)

if (COMMAND cmake_policy)
    cmake_policy (SET CMP0003 NEW)
endif ()

# Enable 64-bit build. Disabled by default. On Visual Studio, depends on the generator used
if (NOT MSVC)
    # set (ENABLE_64BIT 1)
else ()
    if (CMAKE_GENERATOR MATCHES "Win64")
        set (ENABLE_64BIT 1)
    endif ()
endif ()

# Enable SSE instruction set. Requires Pentium III or Athlon XP processor at minimum.
set (ENABLE_SSE 1)
add_definitions (-DENABLE_SSE)

# Enable structured exception handling and minidumps on MSVC only.
if (MSVC)
    set (ENABLE_MINIDUMPS 1)
    add_definitions (-DENABLE_MINIDUMPS)
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
# set, but Windows graphics card drivers are usually better optimized for Direct3D.
if (NOT MSVC)
    set (USE_OPENGL 1)
    add_definitions (-DUSE_OPENGL)
endif ()

# If not on Windows, enable Unix mode for kNet library.
if (NOT WIN32)
    add_definitions (-DUNIX)
endif ()

# Check existence of stdint.h for LibCpuId
CHECK_INCLUDE_FILES (stdint.h HAVE_STDINT_H)
if (HAVE_STDINT_H)
    add_definitions(-DHAVE_STDINT_H)
endif ()

# Add definitions for GLEW
if (NOT IOS AND NOT ANDROID AND USE_OPENGL)
    add_definitions(-DGLEW_STATIC)
    add_definitions(-DGLEW_NO_GLU)
endif ()

# Platform and compiler specific options
if (IOS)
    # IOS-specific setup
    add_definitions (-DIOS)
    set (CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_32_BIT))
    set (CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
    set (MACOSX_BUNDLE_GUI_IDENTIFIER "com.googlecode.urho3d")
    set (CMAKE_OSX_SYSROOT "iphoneos")	# Set to "Latest iOS"
elseif (CMAKE_GENERATOR STREQUAL "Xcode")
    # MacOSX-Xcode-specific setup
    if (NOT ENABLE_64BIT)
        set (CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_32_BIT))
    endif ()
    set (CMAKE_OSX_SYSROOT "")		# Set to "Current OS X"
    #set (CMAKE_OSX_SYSROOT "macosx")	# Set to "Latest OS X"
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
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof")
    elseif (NOT IOS)
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -ffast-math")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -O2 -ffast-math")
        if (ENABLE_64BIT)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
        else ()
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
            if (ENABLE_SSE)
                set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse")
                set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse")
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
    string (REGEX REPLACE "\\.\\./|ThirdParty/|Engine/|Extras/|/Include|/include|/src" "" STRIP_LIBS "${LIBS};${LINK_LIBS_ONLY}")
    target_link_libraries (${TARGET_NAME} ${STRIP_LIBS})
endmacro ()

# Macro for setting up a library target
macro (setup_library)
    add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
    setup_target ()
endmacro ()

# Macro for setting up an executable target
macro (setup_executable)
    add_executable (${TARGET_NAME} ${EXE_TYPE} ${SOURCE_FILES})
    setup_target ()
    if (MSVC)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETPATH)\" ${PROJECT_SOURCE_DIR}/Bin)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETDIR)$(TARGETNAME).pdb\" ${PROJECT_SOURCE_DIR}/Bin)
    elseif (IOS)
        set_target_properties (${TARGET_NAME} PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
    else ()
        get_target_property (EXECUTABLE_NAME ${TARGET_NAME} LOCATION)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${EXECUTABLE_NAME} ${PROJECT_SOURCE_DIR}/Bin)
    endif ()
endmacro ()

# Macro for setting up an executable target with resources to copy
macro (setup_main_executable)
    # Define resource files
    if (APPLE)
        set (RESOURCE_FILES ${PROJECT_SOURCE_DIR}/Bin/CoreData ${PROJECT_SOURCE_DIR}/Bin/Data)
        set_source_files_properties(${RESOURCE_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
        set (SOURCE_FILES ${SOURCE_FILES} ${RESOURCE_FILES})
    endif ()

    # Setup target
    if (WIN32)
        set (EXE_TYPE WIN32)
    elseif (IOS)
        set (CMAKE_EXE_LINKER_FLAGS "-framework AudioToolbox -framework CoreAudio -framework CoreGraphics -framework Foundation -framework OpenGLES -framework QuartzCore -framework UIKit")
        set (EXE_TYPE MACOSX_BUNDLE)
    elseif (APPLE)
        set (CMAKE_EXE_LINKER_FLAGS "-framework AudioUnit -framework Carbon -framework Cocoa -framework CoreAudio -framework ForceFeedback -framework IOKit -framework OpenGL -framework CoreServices")
    endif ()
    if (NOT ANDROID)
        setup_executable ()
    else ()
        add_library (${TARGET_NAME} SHARED ${SOURCE_FILES})
        setup_target ()
        # Strip the output shared library
        get_target_property (EXECUTABLE_NAME ${TARGET_NAME} LOCATION)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} ${EXECUTABLE_NAME})
    endif ()

    # Define a custom target to check for resource modification
    if (IOS)
        get_target_property (TARGET_LOC ${TARGET_NAME} LOCATION)
        string (REGEX REPLACE "/Contents/MacOS" "" TARGET_LOC ${TARGET_LOC})    # The regex replacement is temporary workaround to correct the wrong location caused by CMake/Xcode generator bug
        add_custom_target (RESOURCE_CHECK_${TARGET_NAME} ALL
            \(\( `find ${RESOURCE_FILES} -newer ${TARGET_LOC} 2>/dev/null |wc -l` \)\) && touch -cm ${SOURCE_FILES} || exit 0
            COMMENT "This is a dummy target to check for changes in the Resource folders"
        )
        add_dependencies (${TARGET_NAME} RESOURCE_CHECK_${TARGET_NAME})
    endif ()
endmacro ()

# Add SDL as a global include directory
include_directories (ThirdParty/SDL/include)

# If using Windows and not OpenGL, find DirectX SDK include & library directories
# Based on realXtend Tundra CMake build system (https://github.com/realXtend/naali)
if (WIN32 AND NOT USE_OPENGL)
    find_path(DirectX_INCLUDE_DIR d3dx9.h
        "$ENV{DIRECTX_ROOT}/Include"
        "$ENV{DXSDK_DIR}/Include"
        "C:/apps_x86/Microsoft DirectX SDK*/Include"
        "C:/Program Files (x86)/Microsoft DirectX SDK*/Include"
        "C:/apps/Microsoft DirectX SDK*/Include"
        "C:/Program Files/Microsoft DirectX SDK*/Include")

    if (CMAKE_CL_64)
        set (DirectX_LIBRARY_PATHS
            "$ENV{DIRECTX_ROOT}/Lib/x64"
            "$ENV{DXSDK_DIR}/Lib/x64"
            "C:/Program Files (x86)/Microsoft DirectX SDK*/Lib/x64"
            "C:/Program Files/Microsoft DirectX SDK*/Lib/x64")
    else ()
        set (DirectX_LIBRARY_PATHS
            "$ENV{DIRECTX_ROOT}/Lib"
            "$ENV{DIRECTX_ROOT}/Lib/x86"
            "$ENV{DXSDK_DIR}/Lib"
            "$ENV{DXSDK_DIR}/Lib/x86"
            "C:/Program Files (x86)/Microsoft DirectX SDK*/Lib"
            "C:/Program Files (x86)/Microsoft DirectX SDK*/Lib/x86"
            "C:/Program Files/Microsoft DirectX SDK*/Lib"
            "C:/Program Files/Microsoft DirectX SDK*/Lib/x86")
    endif ()
        
    find_path (DirectX_LIBRARY_DIR d3d9.lib ${DirectX_LIBRARY_PATHS})

    if (DirectX_INCLUDE_DIR AND DirectX_LIBRARY_DIR)
        include_directories (${DirectX_INCLUDE_DIR})
        link_directories (${DirectX_LIBRARY_DIR})
    endif ()
endif ()

# Add projects
add_subdirectory (Engine/Audio)
add_subdirectory (Engine/Container)
add_subdirectory (Engine/Core)
add_subdirectory (Engine/Engine)
add_subdirectory (Engine/Graphics)
add_subdirectory (Engine/Input)
add_subdirectory (Engine/IO)
add_subdirectory (Engine/Math)
add_subdirectory (Engine/Navigation)
add_subdirectory (Engine/Network)
add_subdirectory (Engine/Physics)
add_subdirectory (Engine/Resource)
add_subdirectory (Engine/Scene)
add_subdirectory (Engine/Script)
add_subdirectory (Engine/UI)
add_subdirectory (ThirdParty/AngelScript)
add_subdirectory (ThirdParty/Bullet)
add_subdirectory (ThirdParty/Detour)
add_subdirectory (ThirdParty/FreeType)
add_subdirectory (ThirdParty/kNet)
add_subdirectory (ThirdParty/PugiXml)
add_subdirectory (ThirdParty/Recast)
add_subdirectory (ThirdParty/SDL)
add_subdirectory (ThirdParty/StanHull)
add_subdirectory (ThirdParty/STB)
add_subdirectory (ThirdParty/JO)

# Alternative Lua bindings. Uncomment the following line to enable
# set (ENABLE_LUA 1)
if (ENABLE_LUA)
    add_definitions (-DENABLE_LUA)
    add_subdirectory (ThirdParty/Lua)
    add_subdirectory (ThirdParty/tolua++/src/lib)
    add_subdirectory (Extras/LuaScript)
endif ()

if (NOT IOS AND NOT ANDROID)
    if (USE_OPENGL)
        add_subdirectory (ThirdParty/GLEW)
    endif ()
    add_subdirectory (ThirdParty/Assimp)
    add_subdirectory (ThirdParty/LibCpuId)
    if (ENABLE_LUA)
        add_subdirectory (ThirdParty/tolua++/src/bin)
    endif ()
    add_subdirectory (Tools/AssetImporter)
    add_subdirectory (Tools/OgreImporter)
    add_subdirectory (Tools/PackageTool)
    add_subdirectory (Tools/RampGenerator)
    add_subdirectory (Tools/ScriptCompiler)
    add_subdirectory (Tools/DocConverter)
endif ()

if (NOT USE_OPENGL)
    add_subdirectory (ThirdParty/MojoShader)
    add_subdirectory (Tools/ShaderCompiler)
endif ()

# Urho3D samples. Uncomment to enable
# set (ENABLE_SAMPLES 1)
if (ENABLE_SAMPLES AND NOT IOS AND NOT ANDROID)
    add_subdirectory (Samples)
endif ()   

# Urho3D extras. Uncomment to enable
# Todo: CharacterDemo will be moved to Samples
# set (ENABLE_EXTRAS 1)
if (ENABLE_EXTRAS)
    if (NOT IOS AND NOT ANDROID)
        add_subdirectory (Extras/OgreBatchConverter)
        add_subdirectory (Extras/CharacterDemo)
    endif ()
endif ()

add_subdirectory (Urho3D)
