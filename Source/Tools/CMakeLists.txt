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

# Urho3DPlayer target is rather special, although it is here, it is not a tool because it builds into platform-specific binary
add_subdirectory (Urho3DPlayer)

# Do not build tools for iOS and Android regardless of the URHO3D_TOOLS build option
if (NOT IOS AND NOT ANDROID AND URHO3D_TOOLS)
    # All tools must be natively built and output to bin/tool subdir to differentiate them from platform-specific binaries in the bin directory
    set_output_directories (${CMAKE_BINARY_DIR}/bin/tool RUNTIME PDB)
    # Urho3D tools
    add_subdirectory (AssetImporter)
    add_subdirectory (OgreImporter)
    add_subdirectory (PackageTool)
    add_subdirectory (RampGenerator)
    if (URHO3D_ANGELSCRIPT)
        add_subdirectory (ScriptCompiler)
    endif ()
endif ()
