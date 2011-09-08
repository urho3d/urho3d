# Set minimum version
cmake_minimum_required (VERSION 2.6)

# Disable "unnecessary" build types
set (CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "Configurations" FORCE)

if (COMMAND cmake_policy)
    cmake_policy (SET CMP0003 NEW)
endif ()

# Set project name
project (Urho3D)

# Enable structured exception handling and minidumps on MSVC only. Note: minidump generation requires
# a Windows XP or newer version of dbghelp.dll, so disable it if you want Windows 2000 compatibility.
if (MSVC)
    set (ENABLE_MINIDUMPS 1)
    add_definitions (-DENABLE_MINIDUMPS)
endif ()

# Enable profiling. If disabled, autoprofileblocks become no-ops and the Profiler subsystem is not
# instantiated.
add_definitions (-DENABLE_PROFILING)

# If not on Windows, enable use of OpenGL instead of Direct3D9 (so called "Turso3D" mode.) Setting
# this on Windows is not recommended, as graphics card drivers are usually better optimized for
# Direct3D.
if (NOT WIN32)
    set (USE_OPENGL 1)
    add_definitions (-DUSE_OPENGL)
    add_definitions (-DUNIX)
endif ()

# Compiler-specific options
if (MSVC)
    add_definitions (-D_CRT_SECURE_NO_WARNINGS)
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
    set (CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE} /MT /fp:fast /Zi /GS-")
    set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELWITHDEBINFO} /GL")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} /MT /fp:fast /Zi /GS- /D _SECURE_SCL=0")
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /GL")
    set (CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF /DEBUG")
    set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF /LTCG")
else ()
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -m32")
    set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Bin)
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
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different $(TARGETPATH) ${PROJECT_BINARY_DIR}/Bin)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different $(TARGETDIR)$(TARGETNAME).pdb ${PROJECT_BINARY_DIR}/Bin)
    else ()
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND strip ARGS ${EXECUTABLE_OUTPUT_PATH}/${TARGET_NAME}${CMAKE_EXECUTABLE_SUFFIX})
    endif ()
endmacro ()

# Macro for lib finalization
macro (finalize_lib)
    if (MSVC)
        set_target_properties (${TARGET_NAME} PROPERTIES STATIC_LIBRARY_FLAGS_RELEASE "/LTCG")
    endif ()
endmacro ()

# Macro for model asset compilation
macro (add_model NAME PARAMETERS)
    add_custom_command (
        OUTPUT ../../Bin/Data/Models/${NAME}.mdl
        COMMAND ../../Bin/OgreImporter ${NAME}.mesh.xml ../../Bin/Data/Models/${NAME}.mdl ${PARAMETERS}
        DEPENDS OgreImporter ${NAME}.mesh.xml
    )

    set (ALL_MODELS ${ALL_MODELS} ../../Bin/Data/Models/${NAME}.mdl)
endmacro ()

# Macro for shader asset compilation
if (USE_OPENGL)
    macro (add_shader NAME)
        add_custom_command (
            OUTPUT ../../Bin/CoreData/Shaders/GLSL/${NAME}.vert
            COMMAND ../../Bin/GLShaderProcessor ${NAME}.xml ../../Bin/CoreData/Shaders/GLSL
            DEPENDS GLShaderProcessor ${NAME}.vert ${NAME}.frag Uniforms.vert Transform.vert ScreenPos.vert Uniforms.frag Samplers.frag Lighting.frag Fog.frag ${NAME}.xml
        )
        
        set (ALL_SHADERS ${ALL_SHADERS} ../../Bin/CoreData/Shaders/GLSL/${NAME}.vert)
    endmacro ()
else()
    macro (add_shader NAME)
        add_custom_command (
            OUTPUT ../../Bin/CoreData/Shaders/SM2FB/${NAME}.vs2
            COMMAND ../../Bin/ShaderCompiler ${NAME}.xml ../../Bin/CoreData/Shaders/SM2FB FALLBACK
            DEPENDS ShaderCompiler Uniforms.hlsl Samplers.hlsl Transform.hlsl ScreenPos.hlsl Lighting.hlsl Fog.hlsl ${NAME}.hlsl ${NAME}.xml
        )
        
        add_custom_command (
            OUTPUT ../../Bin/CoreData/Shaders/SM2/${NAME}.vs2
            COMMAND ../../Bin/ShaderCompiler ${NAME}.xml ../../Bin/CoreData/Shaders/SM2
            DEPENDS ShaderCompiler Uniforms.hlsl Samplers.hlsl Transform.hlsl ScreenPos.hlsl Lighting.hlsl Fog.hlsl ${NAME}.hlsl ${NAME}.xml
        )
            
        add_custom_command (
            OUTPUT ../../Bin/CoreData/Shaders/SM3/${NAME}.vs3
            COMMAND ../../Bin/ShaderCompiler ${NAME}.xml ../../Bin/CoreData/Shaders/SM3 SM3
            DEPENDS ShaderCompiler Uniforms.hlsl Samplers.hlsl Transform.hlsl ScreenPos.hlsl Lighting.hlsl Fog.hlsl ${NAME}.hlsl ${NAME}.xml
        )

        set (ALL_SHADERS ${ALL_SHADERS} ../../Bin/CoreData/Shaders/SM2FB/${NAME}.vs2 ../../Bin/CoreData/Shaders/SM2/${NAME}.vs2 ../../Bin/CoreData/Shaders/SM3/${NAME}.vs3)
    endmacro ()
endif ()

# If GLFW used, add it as a global include directory
if (USE_OPENGL)
    include_directories (ThirdParty/GLFW/include)
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
add_subdirectory (Engine/Network)
add_subdirectory (Engine/Physics)
add_subdirectory (Engine/Resource)
add_subdirectory (Engine/Scene)
add_subdirectory (Engine/Script)
add_subdirectory (Engine/UI)
add_subdirectory (SourceAssets/Models)
add_subdirectory (ThirdParty/AngelScript)
add_subdirectory (ThirdParty/Assimp)
add_subdirectory (ThirdParty/FreeType)
add_subdirectory (ThirdParty/kNet)
add_subdirectory (ThirdParty/ODE)
add_subdirectory (ThirdParty/PortAudio)
add_subdirectory (ThirdParty/StanHull)
add_subdirectory (ThirdParty/STB)
add_subdirectory (ThirdParty/TinyXML)
add_subdirectory (Tools/AssetImporter)
add_subdirectory (Tools/NormalMapTool)
add_subdirectory (Tools/OgreImporter)
add_subdirectory (Tools/PackageTool)
add_subdirectory (Tools/RampGenerator)
add_subdirectory (Urho3D)

if (USE_OPENGL)
    add_subdirectory (SourceAssets/GLSLShaders)
    add_subdirectory (ThirdParty/GLee)
    add_subdirectory (ThirdParty/GLFW)
    add_subdirectory (Tools/GLShaderProcessor)
else ()
    add_subdirectory (SourceAssets/HLSLShaders)
    add_subdirectory (Tools/ShaderCompiler)
endif ()

