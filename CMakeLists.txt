# Disable unnecessary build types
set (CMAKE_CONFIGURATION_TYPES "RelWithDebInfo;Debug;Release" CACHE STRING "Configurations" FORCE)

# Set project name
project (Urho3D)

# Set minimum version
cmake_minimum_required (VERSION 2.6)

if (COMMAND cmake_policy)
    cmake_policy (SET CMP0003 NEW)
endif ()

if (IOS)
    # IOS-specific setup
    add_definitions (-DIOS)
    enable_language (ASM)
    set (CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_32_BIT))
    set (CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
    set (MACOSX_BUNDLE_GUI_IDENTIFIER "com.googlecode.urho3d")
    set (CMAKE_OSX_SYSROOT "iphoneos")	# Set to "Latest iOS"
elseif (APPLE)
    if (CMAKE_GENERATOR STREQUAL "Xcode")
        # MacOSX-specific setup
        set (CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_32_BIT))
        set (CMAKE_OSX_SYSROOT "")		# Set to "Current OS X"
        #set (CMAKE_OSX_SYSROOT "macosx")	# Set to "Latest OS X"
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

# Compiler-specific options
if (MSVC)
    add_definitions (-D_CRT_SECURE_NO_WARNINGS)
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
    set (CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE} /MT /fp:fast /Zi /GS-")
    set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELWITHDEBINFO}")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} /MT /fp:fast /Zi /GS- /D _SECURE_SCL=0")
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
    if (ENABLE_SSE)
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /arch:SSE")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE")
    endif ()
    set (CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF /DEBUG")
    set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF")
else ()
    if (NOT IOS)
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -m32")
        if (ENABLE_SSE)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse")
        endif ()
        if (WIN32)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
        endif ()
    endif ()
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
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

# Macro for exe finalization
macro (finalize_exe)
    if (MSVC)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETPATH)\" ${PROJECT_SOURCE_DIR}/Bin)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different \"$(TARGETDIR)$(TARGETNAME).pdb\" ${PROJECT_SOURCE_DIR}/Bin)
    elseif (NOT IOS)
        get_target_property (EXECUTABLE_NAME ${TARGET_NAME} LOCATION)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${EXECUTABLE_NAME} ${PROJECT_SOURCE_DIR}/Bin)
    endif ()
endmacro ()

# Macro for lib finalization
macro (finalize_lib)
endmacro ()

# Add SDL as a global include directory
include_directories (ThirdParty/SDL/include)

# Add projects
add_subdirectory (Engine/Audio)
add_subdirectory (Engine/Container)
add_subdirectory (Engine/Core)
add_subdirectory (Engine/Engine)
add_subdirectory (Engine/Graphics)
add_subdirectory (Engine/Input)
add_subdirectory (Engine/IO)
add_subdirectory (Engine/Math)
add_subdirectory (Engine/Network)
add_subdirectory (Engine/Physics)
add_subdirectory (Engine/Resource)
add_subdirectory (Engine/Scene)
add_subdirectory (Engine/Script)
add_subdirectory (Engine/UI)
add_subdirectory (ThirdParty/AngelScript)
add_subdirectory (ThirdParty/Bullet)
add_subdirectory (ThirdParty/FreeType)
add_subdirectory (ThirdParty/kNet)
add_subdirectory (ThirdParty/PugiXml)
add_subdirectory (ThirdParty/SDL)
add_subdirectory (ThirdParty/StanHull)
add_subdirectory (ThirdParty/STB)
add_subdirectory (ThirdParty/JO)
add_subdirectory (Urho3D)

if (NOT IOS)
    if (USE_OPENGL)
        add_subdirectory (ThirdParty/GLee)
    endif ()
    add_subdirectory (ThirdParty/Assimp)
    add_subdirectory (ThirdParty/LibCpuId)
    add_subdirectory (Tools/AssetImporter)
    add_subdirectory (Tools/OgreImporter)
    add_subdirectory (Tools/PackageTool)
    add_subdirectory (Tools/RampGenerator)
endif ()

if (NOT USE_OPENGL)
    add_subdirectory (ThirdParty/MojoShader)
    add_subdirectory (Tools/ShaderCompiler)
endif ()
