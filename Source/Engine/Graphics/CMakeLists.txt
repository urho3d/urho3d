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
set (TARGET_NAME Graphics)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)

if (USE_OPENGL)
    if (RASPI)
        include_directories (${BCM_VC_INCLUDE_DIR})
    endif ()
    file (GLOB SYS_CPP_FILES OpenGL/*.cpp)
    file (GLOB SYS_H_FILES OpenGL/*.h)
else ()
    file (GLOB SYS_CPP_FILES Direct3D9/*.cpp)
    file (GLOB SYS_H_FILES Direct3D9/*.h)
endif ()

set (SOURCE_FILES ${CPP_FILES} ${H_FILES} ${SYS_CPP_FILES} ${SYS_H_FILES})

# Define dependency libs
set (LIBS ../Container ../Core ../IO ../Math ../Resource ../Scene)
set (INCLUDE_DIRS_ONLY .)
set (LINK_LIBS_ONLY SDL)

if (USE_OPENGL AND NOT IOS AND NOT ANDROID AND NOT RASPI)
    set (LIBS ${LIBS} ../../ThirdParty/GLEW)
endif ()

# Setup target
enable_pch ()
setup_library ()
