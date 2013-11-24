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

# Set project name
project (Urho3D-Docs)

# There could be bug in CMake find_package() command, it currently does not honor NO_CMAKE_FIND_ROOT_PATH option for a non-rooted search as per CMake's documentation
# As a workaround, we unset CMAKE_FIND_ROOT_PATH in this scope ONLY to always do a non-rooted search for Doxygen package (even when we are cross-compiling)
unset (CMAKE_FIND_ROOT_PATH)
# Find Doxygen and DOT packages
find_package (Doxygen QUIET)

if (DOXYGEN_FOUND)
    # Generate platform specific Doxyfile automatically
    if (NOT USE_OPENGL EQUAL DOXYFILE_USE_OPENGL OR ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in IS_NEWER_THAN ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
        set (DOXYFILE_USE_OPENGL ${USE_OPENGL} CACHE INTERNAL "USE_OPENGL flag when Doxyfile was last generated")
        if (USE_OPENGL)
            set (EXCLUDE_GRAPHICS_API Direct3D9)
        else ()
            set (EXCLUDE_GRAPHICS_API OpenGL)
        endif ()
        configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile) 
    endif ()

    # Dump AngelScript and LuaScript API to Doxygen file if the tool is available
    if (TARGET ScriptCompiler)
        add_custom_command (OUTPUT ScriptAPI.dox
            COMMAND ${PROJECT_ROOT_DIR}/Bin/ScriptCompiler -dumpapi ScriptAPI.dox AngelScriptAPI.h DEPENDS Urho3D ScriptCompiler
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Dumping AngelScript API to ScriptAPI.dox")
    endif ()
    execute_process (COMMAND lua -v RESULT_VARIABLE LUA_EXIT_CODE OUTPUT_QUIET ERROR_QUIET)
    if (LUA_EXIT_CODE EQUAL 0)
        add_custom_command (OUTPUT LuaScriptAPI.dox
            COMMAND lua pkgToDox.lua ${CMAKE_CURRENT_BINARY_DIR}/LuaScriptAPI.dox *.pkg DEPENDS Urho3D
            WORKING_DIRECTORY ${PROJECT_ROOT_DIR}/Source/Engine/LuaScript/pkgs
            COMMENT "Dumping LuaScript API to LuaScriptAPI.dox")
    endif ()
    
    # Add custom 'doc' target for generating Urho3D documentation
    add_custom_target (doc
        COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile DEPENDS ScriptAPI.dox LuaScriptAPI.dox
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Doxygen")
endif ()

# Make sure html output directory exists and not empty
file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/html/Readme.txt "Use 'make doc' command or an equivalent command in IDE to re-generate Urho3D documentation.")
    
# Currently it is not possible to make built-in 'install' target to depends on 'doc' in CMake, therefore 'make doc' command need to be invoked manually before 'make install' in order to install the SDK with complete documentation
install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html/ DESTINATION ${DEST_SHARE_DIR}/Docs USE_SOURCE_PERMISSIONS)
