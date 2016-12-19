#
# Copyright (c) 2008-2016 the Urho3D project.
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

if (CMAKE_PROJECT_NAME STREQUAL Urho3D)
    # Set project name
    project (Urho3D-Clang-Tools)

    # All Clang-tools must be natively built and output to bin/tool/clang subdir to differentiate them from the rest
    set_output_directories (${CMAKE_BINARY_DIR}/bin/tool/clang RUNTIME PDB)
else ()
    # Set CMake minimum version and CMake policy required by Urho3D-CMake-common module
    if (WIN32)
        cmake_minimum_required (VERSION 3.2.3)      # Going forward all platforms will use this as minimum version
    else ()
        cmake_minimum_required (VERSION 2.8.6)
    endif ()
    if (COMMAND cmake_policy)
        cmake_policy (SET CMP0003 NEW)
        if (CMAKE_VERSION VERSION_GREATER 2.8.12 OR CMAKE_VERSION VERSION_EQUAL 2.8.12)
            # INTERFACE_LINK_LIBRARIES defines the link interface
            cmake_policy (SET CMP0022 NEW)
        endif ()
        if (CMAKE_VERSION VERSION_GREATER 3.0.0 OR CMAKE_VERSION VERSION_EQUAL 3.0.0)
            # Disallow use of the LOCATION target property - so we set to OLD as we still need it
            cmake_policy (SET CMP0026 OLD)
            # MACOSX_RPATH is enabled by default
            cmake_policy (SET CMP0042 NEW)
        endif ()
    endif ()

    # Set project name
    project (Urho3D-ExternalProject-${URHO3D_CLANG_TOOLS})

    # Set CMake modules search path
    set (CMAKE_MODULE_PATH ${BAKED_CMAKE_SOURCE_DIR}/CMake/Modules)

    # Include Urho3D Cmake common module
    include (Urho3D-CMake-common)

    # Setup SDK-like include dir in the build tree for building the Clang-tools
    file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${DEST_INCLUDE_DIR}/ThirdParty)
endif ()

# LLVM/Clang is assumed to be installed in a system-wide location when not explicitily defined using env-var
if (DEFINED ENV{LLVM_CLANG_ROOT})
    link_directories ($ENV{LLVM_CLANG_ROOT}/lib)
    include_directories ($ENV{LLVM_CLANG_ROOT}/include)
endif ()
execute_process (COMMAND ${LLVM_CONFIG} --bindir OUTPUT_VARIABLE LLVM_BINDIR OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)

# No exception and no RTTI
if (MSVC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHs-c- /GR-")
else ()
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")
endif ()

# Define common dependency libs
set (LIBS clangTooling clangFrontend clangDriver clangParse clangSerialization clangSema clangEdit clangAnalysis clangToolingCore
        clangRewrite clangLex clangASTMatchers clangAST clangBasic
        LLVMBitReader LLVMMC LLVMMCParser LLVMOption LLVMSupport)
execute_process (COMMAND ${LLVM_CONFIG} --system-libs OUTPUT_VARIABLE LLVM_SYSLIBS OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
string (REGEX REPLACE " *-l" ";" LLVM_SYSLIBS "${LLVM_SYSLIBS}")   # Stringify against empty output variable
list (APPEND LIBS ${LLVM_SYSLIBS})
set (INCLUDE_DIRS ${CMAKE_BINARY_DIR}/${DEST_INCLUDE_DIR}/ThirdParty)

# Clang-tools can be built in two ways: on the fly in normal build one at a time or build all of them in a special Clang-tools build tree (for development)
if (CMAKE_PROJECT_NAME MATCHES ExternalProject)
    # Externally build the Clang-tool for actual use in a normal build
    add_subdirectory (${URHO3D_CLANG_TOOLS})
else ()
    # Define source files for the tools
    get_target_property (SOURCES Urho3D SOURCES)
    string (REGEX REPLACE "[^;]+\\.h" "" SOURCES "${SOURCES}")   # Stringify to preserve the semicolons
    string (REGEX REPLACE "[^;]+generated[^;]+\\.cpp" "" SOURCES "${SOURCES}")
    file (GLOB BINDING_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/Source/Urho3D ${CMAKE_SOURCE_DIR}/Source/Urho3D/Script/*API.cpp)
    string (REGEX REPLACE "[^;]+API\\.cpp" "" ANNOTATED_SOURCES "${SOURCES}")

    # List of tools
    add_subdirectory (Annotator)
    add_subdirectory (AutoBinder)

    # List of targets
    if (EXISTS ${LLVM_BINDIR}/clang-query)  # This tool is from clang-tools-extra repository which user may have not installed
        add_custom_target (ast-query
            COMMAND ${CMAKE_COMMAND} -E echo "Building AST for query, please be patient..."
            COMMAND ${LLVM_BINDIR}/clang-query -p ${CMAKE_BINARY_DIR} $$option ${SOURCES}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Source/Urho3D
            COMMENT "Executing clang-query on Urho3D library source files")
    endif ()
    add_custom_target (ast
        COMMAND ${CMAKE_COMMAND} -E echo "Usage: option=-help make ast"
        COMMAND ${LLVM_BINDIR}/clang-check -p ${CMAKE_BINARY_DIR} $$option ${SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Source/Urho3D
        COMMENT "Executing clang-check on Urho3D library source files")
    add_custom_target (binding-ast
        COMMAND ${CMAKE_COMMAND} -E echo "Usage: option=-help make binding-ast"
        COMMAND ${LLVM_BINDIR}/clang-check -p ${CMAKE_BINARY_DIR} $$option ${BINDING_SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Source/Urho3D
        COMMENT "Executing clang-check on (existing) AngelScript API bindings source files")
    add_custom_target (annotate
        COMMAND ${CMAKE_BINARY_DIR}/bin/tool/clang/Annotator -p ${CMAKE_BINARY_DIR} ${SOURCES}
        DEPENDS Annotator
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Source/Urho3D
        COMMENT "Annotating Urho3D library source files")
    add_custom_target (autobinder
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Source/Urho3D/generated
        COMMAND ${CMAKE_BINARY_DIR}/bin/tool/clang/AutoBinder -p ${CMAKE_BINARY_DIR} -t ${CMAKE_CURRENT_SOURCE_DIR}/AutoBinder/Templates -o ${CMAKE_BINARY_DIR}/Source/Urho3D/generated -s AngelScript -s LuaScript -s JavaScript ${ANNOTATED_SOURCES}
        DEPENDS AutoBinder
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Source/Urho3D
        COMMENT "Auto-binding for all script subsystems")
    add_custom_target (autobinder-angelscript
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Source/Urho3D/generated
        COMMAND ${CMAKE_BINARY_DIR}/bin/tool/clang/AutoBinder -p ${CMAKE_BINARY_DIR} -t ${CMAKE_CURRENT_SOURCE_DIR}/AutoBinder/Templates -o ${CMAKE_BINARY_DIR}/Source/Urho3D/generated -s AngelScript ${ANNOTATED_SOURCES}
        DEPENDS AutoBinder
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Source/Urho3D
        COMMENT "Auto-binding for AngelScript")
    add_custom_target (autobinder-luascript
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Source/Urho3D/generated
        COMMAND ${CMAKE_BINARY_DIR}/bin/tool/clang/AutoBinder -p ${CMAKE_BINARY_DIR} -t ${CMAKE_CURRENT_SOURCE_DIR}/AutoBinder/Templates -o ${CMAKE_BINARY_DIR}/Source/Urho3D/generated -s LuaScript ${ANNOTATED_SOURCES}
        DEPENDS AutoBinder
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Source/Urho3D
        COMMENT "Auto-binding for LuaScript")
    add_custom_target (autobinder-javascript
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Source/Urho3D/generated
        COMMAND ${CMAKE_BINARY_DIR}/bin/tool/clang/AutoBinder -p ${CMAKE_BINARY_DIR} -t ${CMAKE_CURRENT_SOURCE_DIR}/AutoBinder/Templates -o ${CMAKE_BINARY_DIR}/Source/Urho3D/generated -s JavaScript ${ANNOTATED_SOURCES}
        DEPENDS AutoBinder
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Source/Urho3D
        COMMENT "Auto-binding for JavaScript")
endif ()
