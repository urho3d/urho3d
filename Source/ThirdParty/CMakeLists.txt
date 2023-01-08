# Copyright (c) 2022-2023 the Dviglo project
# Copyright (c) 2008-2023 the Urho3D project
# License: MIT

# В IDE сторонние библиотеки будут помещены в папку third-party libs
set (CMAKE_FOLDER "third-party libs")

foreach (TARGET ETCPACK FreeType LZ4 PugiXml rapidjson SDL StanHull STB)
    add_subdirectory (${TARGET})
endforeach ()

if (URHO3D_ANGELSCRIPT)
    add_subdirectory (AngelScript)
    if (WEB OR (ARM AND URHO3D_64BIT) OR URHO3D_FORCE_AS_MAX_PORTABILITY)
        add_subdirectory (boost)
    endif ()
endif ()

if (URHO3D_LUA)
    add_subdirectory (Lua${JIT})
    add_subdirectory (toluapp/src/lib)
endif ()

if (URHO3D_NETWORK)
    add_subdirectory (Civetweb)
    add_subdirectory (SLikeNet)
endif ()

if (URHO3D_DATABASE_ODBC)
    add_subdirectory (nanodbc)
endif ()
if (URHO3D_DATABASE_SQLITE)
    add_subdirectory (SQLite)
endif ()

if (URHO3D_IK)
    add_subdirectory (ik)
endif ()

if (URHO3D_NAVIGATION)
    add_subdirectory (Detour)
    add_subdirectory (DetourCrowd)
    add_subdirectory (DetourTileCache)
    add_subdirectory (Recast)
endif ()

if (URHO3D_URHO2D)
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/spine)
        add_subdirectory (spine)
        # Add definition for Spine
        add_definitions (-DURHO3D_SPINE)
    endif ()
endif ()

if (URHO3D_WEBP)
    add_subdirectory (WebP)
endif ()

if (URHO3D_PHYSICS)
    add_subdirectory (Bullet)
endif ()

if (URHO3D_PHYSICS2D)
    add_subdirectory (Box2D)
endif ()

if (URHO3D_TRACY_PROFILING)
    add_subdirectory (Tracy)
endif ()

if (NOT ANDROID AND NOT ARM AND NOT WEB)
    if (URHO3D_OPENGL)
        add_subdirectory (GLEW)
    endif()

    if (NOT CMAKE_SYSTEM_NAME STREQUAL Linux)
        add_subdirectory (LibCpuId)
    endif ()
endif ()

# В CMake нельзя менять переменные, объявленные выше родительской области видимости
# https://levelup.gitconnected.com/cmake-variable-scope-f062833581b7
# Вызовы макроса setup_library() пополняют список статических таргетов STATIC_LIBRARY_TARGETS,
# используя PARENT_SCOPE (т.е. в scope папки ThirdParty).
# Пробрасываем сформированный список ещё на уровень выше, чтобы список был доступен
# в scope папки Source.
# Возможно вместо этого стоит использовать GLOBAL property в качестве глобальной переменной
set (STATIC_LIBRARY_TARGETS ${STATIC_LIBRARY_TARGETS} PARENT_SCOPE)
