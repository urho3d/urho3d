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
    add_definitions (-DENABLE_MINIDUMPS)
    set (DBGHELP_LIB dbghelp.lib)
else ()
    set (DBGHELP_LIB "")
endif ()
  
# Enable profiling. This only affects whether autoprofile-blocks (PROFILE macro) will be generated;
# the profiler is compiled and instantiated nevertheless.
add_definitions (-DENABLE_PROFILING)

# Enable runtime integrity checks for RefCounted objects.
add_definitions (-DENABLE_REFCOUNTED_CHECKS)

# Compiler-specific options
if (MSVC)
    add_definitions (-D_CRT_SECURE_NO_WARNINGS)
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
    set (CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE} /MT /fp:fast /Zi")
    set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELWITHDEBINFO} /GL")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} /MT /fp:fast /Zi /D _SECURE_SCL=0")
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /GL")
    set (CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF /DEBUG")
    set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF /LTCG")
endif ()
if (MINGW)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
    set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
endif ()

# Macro for precompiled headers
macro (enable_pch)
    if (MSVC)
        foreach(FILE ${CPP_FILES})
            if (${FILE} MATCHES "Precompiled.cpp$")
                set_source_files_properties(${FILE} PROPERTIES COMPILE_FLAGS "/YcPrecompiled.h")
            else()
                set_source_files_properties(${FILE} PROPERTIES COMPILE_FLAGS "/YuPrecompiled.h")
            endif()
        endforeach ()
    endif ()
endmacro ()

# Macro for exe finalization
macro (finalize_exe)
    if (MSVC)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different $(TARGETPATH) ${PROJECT_BINARY_DIR}/bin)
        add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different $(TARGETDIR)$(TARGETNAME).pdb ${PROJECT_BINARY_DIR}/bin)
    endif ()
    if (MINGW)
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
macro (add_shader NAME)
    add_custom_command (
        OUTPUT ../../Bin/CoreData/Shaders/SM2/${NAME}.xml
        COMMAND ../../Bin/ShaderCompiler ${NAME}.xml ../../Bin/CoreData/Shaders/SM2 SM2
        DEPENDS ShaderCompiler Common.hlsl ${NAME}.hlsl ${NAME}.xml
    )

    add_custom_command (
        OUTPUT ../../Bin/CoreData/Shaders/SM3/${NAME}.xml
        COMMAND ../../Bin/ShaderCompiler ${NAME}.xml ../../Bin/CoreData/Shaders/SM3 SM3
        DEPENDS ShaderCompiler Common.hlsl ${NAME}.hlsl ${NAME}.xml
    )

    set (ALL_SHADERS ${ALL_SHADERS} ../../Bin/CoreData/Shaders/SM2/${NAME}.xml ../../Bin/CoreData/Shaders/SM3/${NAME}.xml)
endmacro ()

# Recurse subdirectories
add_subdirectory (Engine/Audio)
add_subdirectory (Engine/Common)
add_subdirectory (Engine/Engine)
add_subdirectory (Engine/Input)
add_subdirectory (Engine/Math)
add_subdirectory (Engine/Network)
add_subdirectory (Engine/Physics)
add_subdirectory (Engine/Renderer)
add_subdirectory (Engine/Resource)
add_subdirectory (Engine/Scene)
add_subdirectory (Engine/Script)
add_subdirectory (Engine/UI)
add_subdirectory (Examples/NetworkTest)
add_subdirectory (Examples/NinjaSnowWar)
add_subdirectory (Examples/Urho3D)
add_subdirectory (SourceAssets/Models)
add_subdirectory (SourceAssets/Shaders)
add_subdirectory (ThirdParty/AngelScript)
add_subdirectory (ThirdParty/Assimp)
add_subdirectory (ThirdParty/ENet)
add_subdirectory (ThirdParty/FreeType)
add_subdirectory (ThirdParty/ODE)
add_subdirectory (ThirdParty/StanHull)
add_subdirectory (ThirdParty/STB)
add_subdirectory (ThirdParty/TinyXML)
add_subdirectory (Tools/AssetImporter)
add_subdirectory (Tools/NormalMapTool)
add_subdirectory (Tools/OgreImporter)
add_subdirectory (Tools/PackageTool)
add_subdirectory (Tools/RampGenerator)
add_subdirectory (Tools/ShaderCompiler)
