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
# As a workaround, we unset CMAKE_FIND_ROOT_PATH (even when we are cross-compiling) but in this scope ONLY in order to always do a non-rooted search for Doxygen package
unset (CMAKE_FIND_ROOT_PATH)
# Find Doxygen and DOT packages
find_package (Doxygen QUIET)

if (DOXYGEN_FOUND)
    # Generate platform specific Doxyfile automatically
    if (NOT USE_OPENGL EQUAL DOXYFILE_USE_OPENGL OR ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in IS_NEWER_THAN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
        set (DOXYFILE_USE_OPENGL ${USE_OPENGL} CACHE INTERNAL "USE_OPENGL flag when Doxyfile was last generated")
        if (USE_OPENGL)
            set (EXCLUDE_GRAPHICS_API Direct3D9)
        else ()
            set (EXCLUDE_GRAPHICS_API OpenGL)
        endif ()
        configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    endif ()

    # Dump AngelScript and LuaScript API to Doxygen file if the tool is available
    # CMake's custom command output is intentionally set to mismatch with the tool's output file location to achieve two desired side-effect results:
    # 1) 'make clean' does not remove the generated ScriptAPI.dox and LuaScriptAPI.dox in the 'Docs' subdirectory
    # 2) ScriptAPI.dox and LuaScriptAPI.dox always get refreshed first before the 'doc' target is being built (similar to VS-only PRE_BUILD custom command)
    if (TARGET ScriptCompiler)
        add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ScriptAPI.dox
            COMMAND ${PROJECT_ROOT_DIR}/Bin/ScriptCompiler -dumpapi ScriptAPI.dox AngelScriptAPI.h
            DEPENDS Urho3D ScriptCompiler
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Dumping AngelScript API to ScriptAPI.dox")
    else ()
        add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ScriptAPI.dox COMMAND echo dummy >${CMAKE_CURRENT_BINARY_DIR}/ScriptAPI.dox)
    endif ()
    if (ENABLE_LUAJIT)
        set (jit jit)
    endif ()
    if (TARGET lua${jit}_interpreter)
        add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/LuaScriptAPI.dox
            COMMAND ${PROJECT_ROOT_DIR}/Bin/lua${jit} pkgToDox.lua ${CMAKE_CURRENT_SOURCE_DIR}/LuaScriptAPI.dox *.pkg
            DEPENDS Urho3D lua${jit}_interpreter
            WORKING_DIRECTORY ${PROJECT_ROOT_DIR}/Source/Engine/LuaScript/pkgs
            COMMENT "Dumping LuaScript API to LuaScriptAPI.dox")
    else ()
        add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/LuaScriptAPI.dox COMMAND echo dummy >${CMAKE_CURRENT_BINARY_DIR}/LuaScriptAPI.dox)
    endif ()

    # If ENABLE_DOCS build option is set then add the custom 'doc' target into the default 'all' target, i.e. a normal build would not only build the software but also the documentation
    if (ENABLE_DOCS_QUIET)
        set (ENABLE_DOCS 1)
        if (CMAKE_HOST_WIN32)
            set (REDIRECT_STDOUT 1>nul)     # In quiet mode, redirect standard output stream of Doxygen to a null device
        else ()
            set (REDIRECT_STDOUT 1>/dev/null)
        endif ()
    endif ()
    if (ENABLE_DOCS)
        set (ALL ALL)
    endif ()

    # Add custom 'doc' target for generating Urho3D documentation
    add_custom_target (doc ${ALL}
        COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile ${REDIRECT_STDOUT}
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/ScriptAPI.dox ${CMAKE_CURRENT_BINARY_DIR}/LuaScriptAPI.dox   # Note: these two dependencies need to be made explicit or otherwise CMake would not automatically 'refresh' them with provided custom command
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating documentation with Doxygen")
endif ()

# Make sure html output directory exists and not empty
file (WRITE ${CMAKE_CURRENT_SOURCE_DIR}/html/Readme.txt "If ENABLE_DOCS build option is not set then use 'make doc' command or an equivalent command in IDE to re-generate Urho3D documentation before calling 'make install' or its equivalent.")
    
# Currently it is not possible to make built-in 'install' target to depend on 'doc' in CMake, therefore 'make doc' command need to be invoked manually before 'make install' in order to install the SDK with complete documentation
# Unless, ENABLE_DOCS build option is set in which case the custom 'doc' target is part of the default 'all' target which in turn the 'install' target depends on, so a single 'make install' alone is suffice to install everything 
install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/html/ DESTINATION ${DEST_SHARE_DIR}/Docs USE_SOURCE_PERMISSIONS)
