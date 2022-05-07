# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

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
