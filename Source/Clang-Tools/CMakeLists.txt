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
project (Urho3D-Clang-Tools)

# LLVM/Clang is assumed to be installed in a system-wide location when not explicitily defined using env-var
if (DEFINED ENV{LLVM_CLANG_ROOT})
    link_directories ($ENV{LLVM_CLANG_ROOT}/lib)
    include_directories ($ENV{LLVM_CLANG_ROOT}/include)
    set (BINDIR $ENV{LLVM_CLANG_ROOT}/bin/)
endif ()

# No exception and no RTTI
if (MSVC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHs-c- /GR-")
else ()
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")
endif ()

# All tools must be natively built and output to bin/tool subdir to differentiate them from target platfrom binaries in the bin directory
set_tool_output_directories ()

# Define source files for the tools
get_target_property (SOURCES Urho3D SOURCES)
string (REGEX REPLACE "[^;]+\\.h" "" SOURCES "${SOURCES}")   # Stringify to preserve the semicolons
string (REGEX REPLACE "[^;]+generated[^;]+\\.cpp" "" SOURCES "${SOURCES}")
file (GLOB API_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/Source/Urho3D ${CMAKE_SOURCE_DIR}/Source/Urho3D/Script/*API.cpp)

# Define common dependency libs
set (LIBS clangTooling clangFrontend clangDriver clangParse clangSerialization clangSema clangEdit clangAnalysis clangLex clangAST clangBasic
        LLVMBitReader LLVMMC LLVMOption LLVMMCParser LLVMSupport)
execute_process (COMMAND ${LLVM_CONFIG} --system-libs OUTPUT_VARIABLE LLVM_SYSLIBS OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
string (REGEX REPLACE " *-l" ";" LLVM_SYSLIBS "${LLVM_SYSLIBS}")   # Stringify against empty output variable
list (APPEND LIBS ${LLVM_SYSLIBS})

# List of tools
add_subdirectory (ScriptBindingExtractor)
add_subdirectory (Annotator)

# List of targets
add_custom_target (ast      # Possible options are: dump|list|print; example usage: opt=dump make ast
    COMMAND ${BINDIR}clang-check -p ${CMAKE_BINARY_DIR} -ast-$$opt ${API_SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Source/Urho3D
    COMMENT "Executing clang-check on AngelScript API bindings source files")
add_custom_target (annotate
    COMMAND ${CMAKE_BINARY_DIR}/bin/tool/ScriptBindingExtractor -p ${CMAKE_BINARY_DIR} ${API_SOURCES} >${CMAKE_BINARY_DIR}/bindings.json
    COMMAND ${CMAKE_BINARY_DIR}/bin/tool/Annotator -p ${CMAKE_BINARY_DIR} -b ${CMAKE_BINARY_DIR}/bindings.json ${SOURCES}
    DEPENDS ScriptBindingExtractor Annotator
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Source/Urho3D
    COMMENT "Annotating Urho3D library source files")
