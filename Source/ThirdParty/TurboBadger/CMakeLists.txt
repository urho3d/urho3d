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

# Define target name
set (TARGET_NAME TurboBadger)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" ../FreeType/include ../SDL/include)

if(APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -Wall -Wextra -Wno-unused-parameter")
    add_definitions(-DMACOSX)
endif(APPLE)

if(NOT URHO3D_TB_DEMO)
    add_definitions(-DTB_FONT_RENDERER_FREETYPE)
    file (GLOB CPP_FILES *.cpp image/*.cpp animation/*.cpp parser/*.cpp renderers/*.cpp utf8/*.cpp)
    file (GLOB H_FILES *.h image/*.h animation/*.h parser/*.h renderers/*.h utf8/*.h)
    set (INCLUDE_DIRS . image animation parser renderers utf8)
else ()
    add_definitions(-DTB_FONT_RENDERER_TBBF)
    file (GLOB CPP_FILES *.cpp image/*.cpp animation/*.cpp parser/*.cpp renderers/*.cpp utf8/*.cpp tests/*.cpp)
    file (GLOB H_FILES *.h image/*.h animation/*.h parser/*.h renderers/*.h utf8/*.h tests/*.h)
    set (INCLUDE_DIRS . image animation parser renderers utf8 tests)
endif ()

set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

setup_library ()
install_header_files (DIRECTORY . DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/TurboBadger FILES_MATCHING PATTERN *.h)  # Note: the trailing slash is significant

