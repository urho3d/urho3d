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

# Define target name
set (TARGET_NAME Urho3DPlayer)

# Define source files
define_source_files ()

# Setup target with resource copying
setup_main_executable (NOBUNDLE)

# Setup test cases
if (URHO3D_ANGELSCRIPT)
    add_test (NAME Editor COMMAND ${TARGET_NAME} Scripts/Editor.as -w -timeout ${URHO3D_TEST_TIME_OUT})
    add_test (NAME NinjaSnowWar COMMAND ${TARGET_NAME} Scripts/NinjaSnowWar.as -w -timeout ${URHO3D_TEST_TIME_OUT})
    add_test (NAME SpritesAS COMMAND ${TARGET_NAME} Scripts/03_Sprites.as -w -timeout ${URHO3D_TEST_TIME_OUT})
endif ()
if (URHO3D_LUA)
    add_test (NAME SpritesLua COMMAND ${TARGET_NAME} LuaScripts/03_Sprites.lua -w -timeout ${URHO3D_TEST_TIME_OUT})
endif ()

# Symlink/copy helper shell scripts or batch files to invoke Urho3DPlayer
if (NOT IOS AND NOT ANDROID)
    # Ensure the output directory exist before creating the symlinks
    file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    foreach (FILE Editor NinjaSnowWar)
        create_symlink (${CMAKE_SOURCE_DIR}/bin/${FILE}${SCRIPT_EXT} ${CMAKE_BINARY_DIR}/bin/${FILE}${SCRIPT_EXT} FALLBACK_TO_COPY)
    endforeach ()
endif ()
