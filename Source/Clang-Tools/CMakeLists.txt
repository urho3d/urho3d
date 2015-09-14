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

# Fastcomp/Clang libs and headers are assumed to be installed in system-wide location when not explicitily defined using env-var
if (DEFINED ENV{FASTCOMP_CLANG_ROOT})
    link_directories ($ENV{FASTCOMP_CLANG_ROOT}/lib)
    include_directories ($ENV{FASTCOMP_CLANG_ROOT}/include)
endif ()

# No exception and no RTTI
if (MSVC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHs-c- /GR-")
else ()
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")
endif ()

# All tools must be natively built and output to bin/tool subdir to differentiate them from target platfrom binaries in the bin directory
set_tool_output_directories ()

add_subdirectory (Annotator)

# Add a custom target to start the annotate task
get_target_property (SOURCES Urho3D SOURCES)
string (REGEX REPLACE "[^;]+\\.h" "" SOURCES "${SOURCES}")   # Stringify to preserve the semicolons
string (REGEX REPLACE "[^;]+generated[^;]+\\.cpp" "" SOURCES "${SOURCES}")
add_custom_target (annotate
    COMMAND ${CMAKE_BINARY_DIR}/bin/tool/Annotator -ast-dump -ast-dump-filter=Urho3D::Audio -p ${CMAKE_BINARY_DIR} ${SOURCES}
    DEPENDS Annotator
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Source/Urho3D
    COMMENT "Annotating Urho3D library source files")
