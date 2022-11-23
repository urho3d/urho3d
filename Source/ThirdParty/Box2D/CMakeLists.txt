# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME Box2D)

# Define source files
define_source_files (RECURSE GLOB_CPP_PATTERNS src/*.cpp src/*.h GLOB_H_PATTERNS include/*.h GROUP)

set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (INCLUDE_DIRS include)

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library (install dependency for Urho3D/Physics2D/PhysicsWorld2D.h and Urho3D/Physics2D/RigidBody2D.h)
install_header_files (DIRECTORY include/box2d DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty)
