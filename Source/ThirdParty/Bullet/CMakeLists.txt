# Define target name
set (TARGET_NAME Bullet)

# Define source files
file (GLOB CPP_FILES src/BulletCollision/BroadphaseCollision/*.cpp 
    src/BulletCollision/CollisionDispatch/*.cpp src/BulletCollision/CollisionShapes/*.cpp 
    src/BulletCollision/Gimpact/*.cpp src/BulletCollision/NarrowPhaseCollision/*.cpp 
    src/BulletDynamics/Character/*.cpp src/BulletDynamics/ConstraintSolver/*.cpp
    src/BulletDynamics/Dynamics/*.cpp src/BulletDynamics/Vehicle/*.cpp src/BulletSoftBody/*.cpp
    src/BulletDynamics/Featherstone/*.cpp src/BulletDynamics/MLCPSolvers/*.cpp
    src/LinearMath/*.cpp)
file (GLOB H_FILES *.h src/BulletCollision/BroadphaseCollision/*.h
    src/BulletCollision/CollisionDispatch/*.h src/BulletCollision/CollisionShapes/*.h
    src/BulletCollision/Gimpact/*.h src/BulletCollision/NarrowPhaseCollision/*.h
    src/BulletDynamics/Character/*.h src/BulletDynamics/ConstraintSolver/*.h
    src/BulletDynamics/Dynamics/*.h src/BulletDynamics/Vehicle/*.h src/BulletSoftBody/*.h 
    src/BulletDynamics/Featherstone/*.h src/BulletDynamics/MLCPSolvers/*.h
    src/LinearMath/*.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})
# Install dependency for Engine/Physics/PhysicsWorld.h and Engine/Physics/RigidBody.h
install (DIRECTORY src/LinearMath DESTINATION ${DEST_INCLUDE_DIR}/Bullet ${DEST_PERMISSIONS} FILES_MATCHING PATTERN *.h)
set (INSTALL_INCLUDE_DIRS ${INSTALL_INCLUDE_DIRS} Bullet PARENT_SCOPE)
set (AMALG_EXCLUDES "(btDantzigLCP|btSoftBodyHelpers|Gimpact|Narrow)")

# Define dependency libs
set (INCLUDE_DIRS_ONLY src)

# Setup target
setup_library ()
