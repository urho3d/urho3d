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
set (TARGET_NAME LuaScript)

# Optionally enable Lua / C++ wrapper safety checks
if (NOT ENABLE_SAFE_LUA)
    add_definitions (-DTOLUA_RELEASE)
endif ()

# The host tool must be built natively and would be used when cross-compiling
if (CMAKE_CROSSCOMPILING OR IOS)
    execute_process (COMMAND ${PROJECT_ROOT_DIR}/Bin/tolua++ -v RESULT_VARIABLE TOLUA_EXIT_CODE OUTPUT_QUIET ERROR_QUIET)
    if (NOT TOLUA_EXIT_CODE EQUAL 0)
        message (WARNING "For cross-compiling build to be successful, the 'tolua++' tool must be built natively first and present in the 'Bin' folder." )
    endif ()
else ()
    add_subdirectory (../../ThirdParty/toluapp/src/bin ../../ThirdParty/toluapp/src/bin)
    set (TOLUADEP tolua++)
endif ()

# Define generated source files
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated)
file (GLOB API_PKG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/pkgs/*.pkg)
foreach (API_PKG_FILE ${API_PKG_FILES})
    get_filename_component (NAME ${API_PKG_FILE} NAME)
    string (REGEX REPLACE LuaAPI\\.pkg$ "" API ${NAME})
    set (GEN_CPP_FILE generated/${API}LuaAPI.cpp)
    set (GEN_CPP_FILES ${GEN_CPP_FILES} ${GEN_CPP_FILE})
    file (GLOB PKG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/pkgs/${API}/*.pkg)
    add_custom_command (OUTPUT ${GEN_CPP_FILE} 
        COMMAND ${PROJECT_ROOT_DIR}/Bin/tolua++ -L ToCppHook.lua -o ${CMAKE_CURRENT_BINARY_DIR}/${GEN_CPP_FILE} ${NAME}
        DEPENDS ${TOLUADEP} ${API_PKG_FILE} ${PKG_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/pkgs/ToCppHook.lua
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pkgs
        COMMENT "Generating tolua++ API binding on the fly for ${API}")
endforeach ()

# Define source files
define_source_files (EXTRA_CPP_FILES ${GEN_CPP_FILES})
install (FILES ${H_FILES} DESTINATION ${DEST_INCLUDE_DIR})

# Define dependency libs
set (LIBS ../../ThirdParty/Lua${JIT}/src)
set (LINK_LIBS_ONLY toluapp)
set (INCLUDE_DIRS_ONLY . .. ../Audio ../Container ../Core ../Engine ../Graphics ../Input ../IO ../Math ../Navigation ../Network ../Physics ../Resource ../Scene ../UI  ../Urho2D
    ../../ThirdParty/Box2D ../../ThirdParty/Bullet/src ../../ThirdParty/kNet/include ../../ThirdParty/SDL/include ../../ThirdParty/toluapp/include ${CMAKE_BINARY_DIR}/Engine)

# Setup target
setup_library ()
