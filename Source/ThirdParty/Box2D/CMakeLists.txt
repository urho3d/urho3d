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
set (TARGET_NAME Box2D)

set(BOX2D_Collision_SRCS
    Box2D/Collision/b2BroadPhase.cpp
    Box2D/Collision/b2CollideCircle.cpp
    Box2D/Collision/b2CollideEdge.cpp
    Box2D/Collision/b2CollidePolygon.cpp
    Box2D/Collision/b2Collision.cpp
    Box2D/Collision/b2Distance.cpp
    Box2D/Collision/b2DynamicTree.cpp
    Box2D/Collision/b2TimeOfImpact.cpp
)
set(BOX2D_Collision_HDRS
    Box2D/Collision/b2BroadPhase.h
    Box2D/Collision/b2Collision.h
    Box2D/Collision/b2Distance.h
    Box2D/Collision/b2DynamicTree.h
    Box2D/Collision/b2TimeOfImpact.h
)
set(BOX2D_Shapes_SRCS
    Box2D/Collision/Shapes/b2CircleShape.cpp
    Box2D/Collision/Shapes/b2EdgeShape.cpp
    Box2D/Collision/Shapes/b2ChainShape.cpp
    Box2D/Collision/Shapes/b2PolygonShape.cpp
)
set(BOX2D_Shapes_HDRS
    Box2D/Collision/Shapes/b2CircleShape.h
    Box2D/Collision/Shapes/b2EdgeShape.h
    Box2D/Collision/Shapes/b2ChainShape.h
    Box2D/Collision/Shapes/b2PolygonShape.h
    Box2D/Collision/Shapes/b2Shape.h
)
set(BOX2D_Common_SRCS
    Box2D/Common/b2BlockAllocator.cpp
    Box2D/Common/b2Draw.cpp
    Box2D/Common/b2Math.cpp
    Box2D/Common/b2Settings.cpp
    Box2D/Common/b2StackAllocator.cpp
    Box2D/Common/b2Timer.cpp
)
set(BOX2D_Common_HDRS
    Box2D/Common/b2BlockAllocator.h
    Box2D/Common/b2Draw.h
    Box2D/Common/b2GrowableStack.h
    Box2D/Common/b2Math.h
    Box2D/Common/b2Settings.h
    Box2D/Common/b2StackAllocator.h
    Box2D/Common/b2Timer.h
)
set(BOX2D_Dynamics_SRCS
    Box2D/Dynamics/b2Body.cpp
    Box2D/Dynamics/b2ContactManager.cpp
    Box2D/Dynamics/b2Fixture.cpp
    Box2D/Dynamics/b2Island.cpp
    Box2D/Dynamics/b2World.cpp
    Box2D/Dynamics/b2WorldCallbacks.cpp
)
set(BOX2D_Dynamics_HDRS
    Box2D/Dynamics/b2Body.h
    Box2D/Dynamics/b2ContactManager.h
    Box2D/Dynamics/b2Fixture.h
    Box2D/Dynamics/b2Island.h
    Box2D/Dynamics/b2TimeStep.h
    Box2D/Dynamics/b2World.h
    Box2D/Dynamics/b2WorldCallbacks.h
)
set(BOX2D_Contacts_SRCS
    Box2D/Dynamics/Contacts/b2CircleContact.cpp
    Box2D/Dynamics/Contacts/b2Contact.cpp
    Box2D/Dynamics/Contacts/b2ContactSolver.cpp
    Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
    Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
    Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
    Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
    Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
    Box2D/Dynamics/Contacts/b2PolygonContact.cpp
)
set(BOX2D_Contacts_HDRS
    Box2D/Dynamics/Contacts/b2CircleContact.h
    Box2D/Dynamics/Contacts/b2Contact.h
    Box2D/Dynamics/Contacts/b2ContactSolver.h
    Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h
    Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h
    Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h
    Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h
    Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h
    Box2D/Dynamics/Contacts/b2PolygonContact.h
)
set(BOX2D_Joints_SRCS
    Box2D/Dynamics/Joints/b2DistanceJoint.cpp
    Box2D/Dynamics/Joints/b2FrictionJoint.cpp
    Box2D/Dynamics/Joints/b2GearJoint.cpp
    Box2D/Dynamics/Joints/b2Joint.cpp
    Box2D/Dynamics/Joints/b2MotorJoint.cpp
    Box2D/Dynamics/Joints/b2MouseJoint.cpp
    Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
    Box2D/Dynamics/Joints/b2PulleyJoint.cpp
    Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
    Box2D/Dynamics/Joints/b2RopeJoint.cpp
    Box2D/Dynamics/Joints/b2WeldJoint.cpp
    Box2D/Dynamics/Joints/b2WheelJoint.cpp
)
set(BOX2D_Joints_HDRS
    Box2D/Dynamics/Joints/b2DistanceJoint.h
    Box2D/Dynamics/Joints/b2FrictionJoint.h
    Box2D/Dynamics/Joints/b2GearJoint.h
    Box2D/Dynamics/Joints/b2Joint.h
    Box2D/Dynamics/Joints/b2MotorJoint.h
    Box2D/Dynamics/Joints/b2MouseJoint.h
    Box2D/Dynamics/Joints/b2PrismaticJoint.h
    Box2D/Dynamics/Joints/b2PulleyJoint.h
    Box2D/Dynamics/Joints/b2RevoluteJoint.h
    Box2D/Dynamics/Joints/b2RopeJoint.h
    Box2D/Dynamics/Joints/b2WeldJoint.h
    Box2D/Dynamics/Joints/b2WheelJoint.h
)
set(BOX2D_Rope_SRCS
    Box2D/Rope/b2Rope.cpp
)
set(BOX2D_Rope_HDRS
    Box2D/Rope/b2Rope.h
)
set(BOX2D_General_HDRS
    Box2D/Box2D.h
)

# Define source files
file (GLOB CPP_FILES 
    ${BOX2D_Collision_SRCS}
    ${BOX2D_Shapes_SRCS}
    ${BOX2D_Common_SRCS}
    ${BOX2D_Dynamics_SRCS}
    ${BOX2D_Contacts_SRCS}
    ${BOX2D_Joints_SRCS}
    ${BOX2D_Rope_SRCS})

file (GLOB H_FILES 
    ${BOX2D_Collision_HDRS}
    ${BOX2D_Shapes_HDRS}
    ${BOX2D_Common_HDRS}
    ${BOX2D_Dynamics_HDRS}
    ${BOX2D_Contacts_HDRS}
    ${BOX2D_Joints_HDRS}
    ${BOX2D_Rope_HDRS}
    ${BOX2D_General_HDRS})

set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# These are used to create visual studio folders.
source_group(Collision FILES ${BOX2D_Collision_SRCS} ${BOX2D_Collision_HDRS})
source_group(Collision\\Shapes FILES ${BOX2D_Shapes_SRCS} ${BOX2D_Shapes_HDRS})
source_group(Common FILES ${BOX2D_Common_SRCS} ${BOX2D_Common_HDRS})
source_group(Dynamics FILES ${BOX2D_Dynamics_SRCS} ${BOX2D_Dynamics_HDRS})
source_group(Dynamics\\Contacts FILES ${BOX2D_Contacts_SRCS} ${BOX2D_Contacts_HDRS})
source_group(Dynamics\\Joints FILES ${BOX2D_Joints_SRCS} ${BOX2D_Joints_HDRS})
source_group(Include FILES ${BOX2D_General_HDRS})
source_group(Rope FILES ${BOX2D_Rope_SRCS} ${BOX2D_Rope_HDRS})

# Define dependency libs
set (INCLUDE_DIRS .)

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library (install dependency for Urho3D/Urho2D/PhysicsWorld2D.h and Urho3D/Urho2D/RigidBody2D.h)
install_header_files (DIRECTORY Box2D DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty FILES_MATCHING PATTERN *.h)
