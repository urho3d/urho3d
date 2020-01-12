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

# Workaround for MinGW 6.1.0 and above where it throws ICE (internal compilation error) when -O3 is used
if (MINGW AND (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 6.1.0 OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 6.1.0))  # 6.1.0 is the last known bad version
    string (REPLACE -O3 -O2 CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
endif ()

# Define source files
file (GLOB CPP_FILES src/BulletCollision/BroadphaseCollision/*.cpp
    src/BulletCollision/CollisionDispatch/*.cpp src/BulletCollision/CollisionShapes/*.cpp
    src/BulletCollision/Gimpact/*.cpp src/BulletCollision/NarrowPhaseCollision/*.cpp
    src/BulletDynamics/Character/*.cpp src/BulletDynamics/ConstraintSolver/*.cpp
    src/BulletDynamics/Dynamics/*.cpp src/BulletDynamics/Featherstone/*.cpp
    src/BulletDynamics/MLCPSolvers/*.cpp src/BulletDynamics/Vehicle/*.cpp src/BulletSoftBody/*.cpp
    src/LinearMath/*.cpp)
file (GLOB H_FILES *.h src/BulletCollision/BroadphaseCollision/*.h
    src/BulletCollision/CollisionDispatch/*.h src/BulletCollision/CollisionShapes/*.h
    src/BulletCollision/Gimpact/*.h src/BulletCollision/NarrowPhaseCollision/*.h
    src/BulletDynamics/Character/*.h src/BulletDynamics/ConstraintSolver/*.h
    src/BulletDynamics/Dynamics/*.h src/BulletDynamics/Featherstone/*.h
    src/BulletDynamics/MLCPSolvers/*.h src/BulletDynamics/Vehicle/*.h src/BulletSoftBody/*.h
    src/LinearMath/*.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (INCLUDE_DIRS src)

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library (install dependency for Urho3D/Physics/PhysicsWorld.h, Urho3D/Physics/RigidBody.h, and Urho3D/Physics/PhysicsUtils.h)
install_header_files (DIRECTORY src/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/Bullet FILES_MATCHING PATTERN *.h)  # Note: the trailing slash is significant
