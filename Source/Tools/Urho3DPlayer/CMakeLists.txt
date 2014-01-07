#
# Copyright (c) 2008-2013 the Urho3D project.
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
setup_main_executable ()

# Setup test cases
if (ENABLE_ANGELSCRIPT)
    add_test (NAME Editor COMMAND ${TARGET_NAME} Data/Scripts/Editor.as -w -timeout ${TEST_TIME_OUT})
    add_test (NAME NinjaSnowWar COMMAND ${TARGET_NAME} Data/Scripts/NinjaSnowWar.as -w -timeout ${TEST_TIME_OUT})
    add_test (NAME SpritesAS COMMAND ${TARGET_NAME} Data/Scripts/03_Sprites.as -w -timeout ${TEST_TIME_OUT})
endif ()
if (ENABLE_LUA)
    add_test (NAME SpritesLua COMMAND ${TARGET_NAME} Data/LuaScripts/03_Sprites.lua -w -timeout ${TEST_TIME_OUT})
endif ()
