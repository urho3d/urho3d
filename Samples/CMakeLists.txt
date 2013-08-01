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

# Include common to all samples
set (COMMON_SAMPLE_H_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Sample.h" "${CMAKE_CURRENT_SOURCE_DIR}/Sample.inl")

# Define dependency libs
set (LIBS ../../Engine/Container
          ../../Engine/Core
          ../../Engine/Engine
          ../../Engine/Graphics
          ../../Engine/Input
          ../../Engine/IO
          ../../Engine/Math
          ../../Engine/Resource
          ../../Engine/Scene
          ../../Engine/UI)
set (INCLUDE_DIRS_ONLY ${CMAKE_CURRENT_SOURCE_DIR})

# Add samples
add_subdirectory (01_HelloWorld)
add_subdirectory (02_HelloGUI)
