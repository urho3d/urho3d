# Define target name
set (TARGET_NAME Bullet)

# Define source files
file (GLOB CPP_FILES src/Bullet/BulletCollision/BroadphaseCollision/*.cpp 
    src/Bullet/BulletCollision/CollisionDispatch/*.cpp src/Bullet/BulletCollision/CollisionShapes/*.cpp 
    src/Bullet/BulletCollision/Gimpact/*.cpp src/Bullet/BulletCollision/NarrowPhaseCollision/*.cpp 
    src/Bullet/BulletDynamics/Character/*.cpp src/Bullet/BulletDynamics/ConstraintSolver/*.cpp
    src/Bullet/BulletDynamics/Dynamics/*.cpp src/Bullet/BulletDynamics/Vehicle/*.cpp src/Bullet/BulletSoftBody/*.cpp
    src/Bullet/BulletDynamics/Featherstone/*.cpp src/Bullet/BulletDynamics/MLCPSolvers/*.cpp
    src/Bullet/LinearMath/*.cpp)
file (GLOB H_FILES *.h src/Bullet/BulletCollision/BroadphaseCollision/*.h
    src/Bullet/BulletCollision/CollisionDispatch/*.h src/Bullet/BulletCollision/CollisionShapes/*.h
    src/Bullet/BulletCollision/Gimpact/*.h src/Bullet/BulletCollision/NarrowPhaseCollision/*.h
    src/Bullet/BulletDynamics/Character/*.h src/Bullet/BulletDynamics/ConstraintSolver/*.h
    src/Bullet/BulletDynamics/Dynamics/*.h src/Bullet/BulletDynamics/Vehicle/*.h src/Bullet/BulletSoftBody/*.h 
    src/Bullet/BulletDynamics/Featherstone/*.h src/Bullet/BulletDynamics/MLCPSolvers/*.h
    src/Bullet/LinearMath/*.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})
# Install dependency for Engine/Physics/PhysicsWorld.h and Engine/Physics/RigidBody.h
install (DIRECTORY src/Bullet/LinearMath DESTINATION ${DEST_INCLUDE_DIR}/Bullet ${DEST_PERMISSIONS} FILES_MATCHING PATTERN *.h)
set (INSTALL_INCLUDE_DIRS ${INSTALL_INCLUDE_DIRS} Bullet PARENT_SCOPE)

# Define dependency libs
set (INCLUDE_DIRS_ONLY ${INCLUDE_DIRS_ONLY} src/Bullet)
# Define some more includes to allow the Bullet library to build (Not required for Urho3D):
set (INCLUDE_DIRS_ONLY ${INCLUDE_DIRS_ONLY} src/Bullet)

# Setup target
setup_library ()
