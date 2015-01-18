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

# Check existence of stdint.h for LibCpuId
include (CheckIncludeFiles)
CHECK_INCLUDE_FILES (stdint.h HAVE_STDINT_H)
if (HAVE_STDINT_H)
    add_definitions (-DHAVE_STDINT_H)
endif ()

# Setup RPATH settings
if (URHO3D_LIB_TYPE STREQUAL SHARED AND NOT WIN32 AND NOT ANDROID AND NOT IOS)
    # Add RPATH entries when building
    set (CMAKE_SKIP_BUILD_RPATH FALSE)
    # But don't set them yet in the build tree
    set (CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
    if (APPLE)
        if (CMAKE_VERSION VERSION_GREATER 2.8.12 OR CMAKE_VERSION VERSION_EQUAL 2.8.12)
            set (CMAKE_MACOSX_RPATH TRUE)
        endif ()
        set (ORIGIN @loader_path)
    else ()
        set (ORIGIN $ORIGIN)
    endif ()
    # When installing/packaging set the first RPATH entry to the library location relative to the executable
    set (CMAKE_INSTALL_RPATH ${ORIGIN}/../lib${LIB_SUFFIX}/${PATH_SUFFIX})    # The library location is based on SDK install destination
    # The second entry to the install destination of the library, if the destination location is not in the system default search path
    list (FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX} isSystemDir)
    if (isSystemDir STREQUAL -1)
        list (APPEND CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${DEST_LIBRARY_DIR})
    endif ()
endif ()

# Add targets
foreach (TARGET FreeType JO LZ4 PugiXml rapidjson SDL StanHull STB)
    add_subdirectory (ThirdParty/${TARGET})
endforeach ()

if (URHO3D_ANGELSCRIPT)
    add_subdirectory (ThirdParty/AngelScript)
endif ()

if (URHO3D_LUA)
    add_subdirectory (ThirdParty/Lua${JIT})
    add_subdirectory (ThirdParty/toluapp/src/lib)
endif ()

if (URHO3D_NETWORK)
    add_subdirectory (ThirdParty/Civetweb)
    add_subdirectory (ThirdParty/kNet)
endif ()

if (URHO3D_NAVIGATION)
    add_subdirectory (ThirdParty/Detour)
    add_subdirectory (ThirdParty/Recast)
endif ()

if (URHO3D_PHYSICS)
    add_subdirectory (ThirdParty/Bullet)
endif ()

if (URHO3D_URHO2D)
    add_subdirectory (ThirdParty/Box2D)
endif ()

if (NOT IOS AND NOT ANDROID AND NOT RPI)
    if (URHO3D_OPENGL)
        add_subdirectory (ThirdParty/GLEW)
    else ()
        add_subdirectory (ThirdParty/MojoShader)
    endif ()
    add_subdirectory (ThirdParty/LibCpuId)
endif ()

# Urho3D game engine library
add_subdirectory (Urho3D)

# Urho3D tools
add_subdirectory (Tools)

# Urho3D samples
# Samples are built on iOS platform too when enabled. Currently there is no available mechanism to package each sample apps into individual *.apk
# for Android platform, so we deploy all samples into one apk and use a simple list view activity launcher to select the sample to run
if (URHO3D_SAMPLES)
    add_subdirectory (Samples)
endif ()

# Urho3D extras
# Do not build extras for iOS and Android
if (NOT IOS AND NOT ANDROID AND URHO3D_EXTRAS)
    add_subdirectory (Extras)
endif ()
