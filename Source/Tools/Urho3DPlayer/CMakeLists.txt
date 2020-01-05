#
# Copyright (c) 2008-2020 the Urho3D project.
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

if (NOT URHO3D_PLAYER)
    return ()
endif ()

# Define target name
set (TARGET_NAME Urho3DPlayer)

# Define source files
define_source_files ()
if (NOT WEB)
    define_resource_dirs (EXTRA_DIRS ${CMAKE_SOURCE_DIR}/bin/Autoload)
endif ()

# Setup target with resource copying
setup_main_executable (NOBUNDLE)

# Setup test cases
if (URHO3D_ANGELSCRIPT)
    setup_test (NAME Editor OPTIONS Scripts/Editor.as -w)
    setup_test (NAME NinjaSnowWar OPTIONS Scripts/NinjaSnowWar.as -w)
    setup_test (NAME SpritesAS OPTIONS Scripts/03_Sprites.as -w)
endif ()
if (URHO3D_LUA)
    setup_test (NAME SpritesLua OPTIONS LuaScripts/03_Sprites.lua -w)
endif ()

# Symlink/copy helper shell scripts or batch files to invoke Urho3DPlayer
if (NOT IOS AND NOT TVOS AND NOT ANDROID AND NOT WEB AND NOT CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    # Ensure the output directory exist before creating the symlinks
    file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    file (GLOB FILES RELATIVE ${CMAKE_SOURCE_DIR}/bin ${CMAKE_SOURCE_DIR}/bin/*${SCRIPT_EXT})
    foreach (FILE ${FILES})
        create_symlink (${CMAKE_SOURCE_DIR}/bin/${FILE} ${CMAKE_BINARY_DIR}/bin/${FILE} FALLBACK_TO_COPY)
    endforeach ()
endif ()
