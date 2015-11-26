#
# Copyright (c) 2008-2015 the Urho3D project.
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

# Set project name
project (Urho3D-Tools)

# Find Urho3D library
find_package (Urho3D REQUIRED)
include_directories (${URHO3D_INCLUDE_DIRS})

# Urho3DPlayer target is rather special, although it is here, it is not a tool because it is built into target platform binary as opposed to host platform
if (NOT EMSCRIPTEN)
    add_subdirectory (Urho3DPlayer)
endif ()

# Build PackageTool using host compiler toolchain
if ((CMAKE_CROSSCOMPILING OR IOS) AND URHO3D_PACKAGING)
    # When cross-compiling, build the host tool as external project
    include (ExternalProject)
    if (IOS)
        # For iOS target, ensure the host environment is cleared first; Also workaround a known CMake/Xcode generator bug which prevents it from installing binaries correctly
        set (IOS_FIX CMAKE_COMMAND /usr/bin/env -i PATH=$ENV{PATH} ${CMAKE_COMMAND} BUILD_COMMAND bash -c "sed -i '' 's/EFFECTIVE_PLATFORM_NAME//g' CMakeScripts/install_postBuildPhase.make*")
    endif ()
    ExternalProject_Add (PackageTool
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/Source/Tools/PackageTool
        CMAKE_ARGS -DDEST_RUNTIME_DIR=${CMAKE_BINARY_DIR}/bin/tool -DBAKED_CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR} -DBAKED_CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR} ${IOS_FIX})
    if (CMAKE_HOST_WIN32 AND NOT URHO3D_MKLINK)
        add_dependencies (PackageTool Urho3D)   # Ensure Urho3D headers are fresh when building PackageTool externally on Windows host system without MKLINK
    endif ()
    install (PROGRAMS ${CMAKE_BINARY_DIR}/bin/tool/PackageTool DESTINATION ${DEST_RUNTIME_DIR}/tool)
endif ()

# All tools must be natively built and output to bin/tool subdir to differentiate them from target platfrom binaries in the bin directory
set_tool_output_directories ()

if (URHO3D_TOOLS)
    # Urho3D tools
    add_subdirectory (AssetImporter)
    add_subdirectory (OgreImporter)
    add_subdirectory (PackageTool)
    add_subdirectory (RampGenerator)
    add_subdirectory (SpritePacker)
    if (URHO3D_ANGELSCRIPT)
        add_subdirectory (ScriptCompiler)
    endif ()
elseif ((NOT CMAKE_CROSSCOMPILING AND NOT IOS) AND URHO3D_PACKAGING)
    # PackageTool target is required but we are not cross-compiling, so build it as per normal
    add_subdirectory (PackageTool)
endif ()
