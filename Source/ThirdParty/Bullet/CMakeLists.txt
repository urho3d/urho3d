#
# Copyright (c) 2008-2020 the Urho3D project.
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
set (TARGET_NAME Bullet)

# Define preprocessor macros
if (BT_USE_DOUBLE_PRECISION)
    add_definitions (-DBT_USE_DOUBLE_PRECISION)
endif ()
if (BT_THREADSAFE)
    add_definitions (-DBT_THREADSAFE=1)
endif ()
if (BT_USE_OPENMP)
    add_definitions (-DBT_USE_OPENMP=1)
endif ()

# Define source files
define_source_files (RECURSE GLOB_CPP_PATTERNS src/*.cpp GLOB_H_PATTERNS src/*.h src/*.hpp)

# Define dependency libs
set (INCLUDE_DIRS src)

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library (install dependency for Urho3D/Physics/PhysicsWorld.h, Urho3D/Physics/RigidBody.h, and Urho3D/Physics/PhysicsUtils.h)
install_header_files (DIRECTORY src/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/Bullet FILES_MATCHING PATTERN *.h)  # Note: the trailing slash is significant
