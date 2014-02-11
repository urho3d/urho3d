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

# Define target name for Lua library
set (TARGET_NAME Lua)

# Define source files
file (GLOB C_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.c)
list (REMOVE_ITEM C_FILES src/lua.c src/luac.c)
file (GLOB H_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.h)
set (SOURCE_FILES ${C_FILES} ${H_FILES})

# Setup target
setup_library ()

# On Android platform, use 'adb push' to copy the tool(s) from android-Bin to Android (virtual) device; use 'adb shell' to login into a remote shell to execute the tool in the (virtual) device
# The tools are not built on iOS platform as there is no (easy) way to execute them on the iOS device
if (NOT IOS AND (NOT DEFINED ENABLE_TOOLS OR ENABLE_TOOLS))
    # Define target name for Lua interpreter
    set (TARGET_NAME lua_interpreter)   # Note: intended target name is 'lua' which clashes with 'Lua' library target above for case-insensitive platform

    # Define source files
    set (SOURCE_FILES src/lua.c)

    # Define dependency libs
    set (LINK_LIBS_ONLY Lua)
    if (NOT MSVC)
        list (APPEND LINK_LIBS_ONLY m)
    endif ()

    # Setup target
    setup_executable (NODEPS)
    adjust_target_name ()   # Adjust to intended target output name

    # Define target name for Lua compiler
    set (TARGET_NAME luac)

    # Define source files
    set (SOURCE_FILES src/luac.c)

    # Define dependency libs
    # Same as above

    # Setup target
    setup_executable (NODEPS)
endif ()
