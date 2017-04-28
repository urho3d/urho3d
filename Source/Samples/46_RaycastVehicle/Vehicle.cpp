#include <Urho3D/Urho3D.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/Constraint.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/PhysicsUtils.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include "Vehicle.h"
#include <Urho3D/RaycastVehicle/RaycastVehicle.h>
//=============================================================================
//=============================================================================
#define CUBE_HALF_EXTENTS   1
#define DELETE_NULL(x)      { if (x) delete x; x = NULL; }
//=============================================================================
//=============================================================================
/// Applying attributes (doing nothing)
void Vehicle::ApplyAttributes()
{
}
void Vehicle::RegisterObject ( Context* context )
{
    context->RegisterFactory<Vehicle>();
    URHO3D_ATTRIBUTE ( "Steering", float, steering_, 0.0f, AM_DEFAULT );
    URHO3D_ATTRIBUTE ( "Controls Yaw", float, controls_.yaw_, 0.0f, AM_DEFAULT );
    URHO3D_ATTRIBUTE ( "Controls Pitch", float, controls_.pitch_, 0.0f, AM_DEFAULT );
}
//=============================================================================
//=============================================================================
Vehicle::Vehicle(Urho3D::Context* context) : LogicComponent(context)
    , steering_ ( 0.0f )
{
    m_fEngineForce = 0.0f;
    m_fBreakingForce = 0.0f;
    m_fVehicleSteering = 0.0f;
    m_fmaxEngineForce = 2500.f;//this should be engine/velocity dependent
    m_fmaxBreakingForce = 100.f;
    m_fwheelRadius = 0.5f;
    m_fsuspensionRestLength = 0.6f;//0.6
    m_fwheelWidth = 0.4f;
    m_fsuspensionStiffness = 14.0f;//20.f;
    m_fsuspensionDamping = 2.0f;//2.3f;
    m_fsuspensionCompression = 4.0f;//4.4f;
    m_fwheelFriction = 1000;//BT_LARGE_FLOAT;
    m_frollInfluence = 0.01f;//1.0f;
}
Vehicle::~Vehicle()
{
}

//=============================================================================
//=============================================================================
void Vehicle::Init()
{
    RaycastVehicle *vehicle = node_->CreateComponent<RaycastVehicle>();
    vehicle->Init();
    RigidBody *hullBody = node_->GetComponent<RigidBody>();
    hullBody->SetMass ( 800.0f );
    hullBody->SetLinearDamping ( 0.2f ); // Some air resistance
    hullBody->SetAngularDamping ( 0.5f );
    hullBody->SetCollisionLayer ( 1 );
    // This function is called only from the main program when initially creating the vehicle, not on scene load
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    StaticModel* hullObject = node_->CreateComponent<StaticModel>();
    // Setting-up collision shape
    CollisionShape* hullColShape = node_->CreateComponent<CollisionShape>();
    Vector3 v3BoxExtents = Vector3::ONE;//Vector3(1.5f, 1.0f, 3.0f);
    hullColShape->SetBox ( v3BoxExtents );
    node_->SetScale ( Vector3 ( 1.5f, 1.0f, 3.5f ) );

    hullObject->SetModel ( cache->GetResource<Model> ( "Models/Box.mdl" ) );
    hullObject->SetMaterial ( cache->GetResource<Material> ( "Materials/Stone.xml" ) );
    hullObject->SetCastShadows ( true );

    float connectionHeight = -0.4f;//1.2f;
    bool isFrontWheel=true;
    Vector3 wheelDirection ( 0,-1,0 );
    Vector3 wheelAxle ( -1,0,0 );
    Node *wheelNode = GetScene()->CreateChild();
    Vector3 connectionPoint ( CUBE_HALF_EXTENTS- ( 0.3f*GetWheelWidth()),connectionHeight,2*CUBE_HALF_EXTENTS-GetWheelRadius());
    wheelNode->SetRotation ( connectionPoint.x_ >= 0.0 ? Quaternion ( 0.0f, 0.0f, -90.0f ) : Quaternion ( 0.0f, 0.0f, 90.0f ) );
    vehicle->AddWheel(wheelNode, connectionPoint, wheelDirection, wheelAxle, m_fsuspensionRestLength, m_fwheelRadius, isFrontWheel);
    wheelNode = GetScene()->CreateChild();
    connectionPoint = Vector3( -CUBE_HALF_EXTENTS+ ( 0.3f*GetWheelWidth()),connectionHeight,2*CUBE_HALF_EXTENTS-GetWheelRadius());
    wheelNode->SetRotation ( connectionPoint.x_ >= 0.0 ? Quaternion ( 0.0f, 0.0f, -90.0f ) : Quaternion ( 0.0f, 0.0f, 90.0f ) );
    vehicle->AddWheel(wheelNode, connectionPoint, wheelDirection, wheelAxle, m_fsuspensionRestLength, m_fwheelRadius, isFrontWheel);
    isFrontWheel = false;
    wheelNode = GetScene()->CreateChild();
    connectionPoint = Vector3( -CUBE_HALF_EXTENTS+ ( 0.3f*GetWheelWidth()),connectionHeight,-2*CUBE_HALF_EXTENTS+GetWheelRadius());
    wheelNode->SetRotation ( connectionPoint.x_ >= 0.0 ? Quaternion ( 0.0f, 0.0f, -90.0f ) : Quaternion ( 0.0f, 0.0f, 90.0f ) );
    vehicle->AddWheel(wheelNode, connectionPoint, wheelDirection, wheelAxle, m_fsuspensionRestLength, m_fwheelRadius, isFrontWheel);
    wheelNode = GetScene()->CreateChild();
    connectionPoint = Vector3(CUBE_HALF_EXTENTS- ( 0.3f*GetWheelWidth()),connectionHeight,-2*CUBE_HALF_EXTENTS+GetWheelRadius());
    wheelNode->SetRotation ( connectionPoint.x_ >= 0.0 ? Quaternion ( 0.0f, 0.0f, -90.0f ) : Quaternion ( 0.0f, 0.0f, 90.0f ) );
    vehicle->AddWheel(wheelNode, connectionPoint, wheelDirection, wheelAxle, m_fsuspensionRestLength, m_fwheelRadius, isFrontWheel);
    for (int id = 0; id < vehicle->GetNumWheels(); id++) {
        vehicle->SetWheelSuspensionStiffness(id, m_fsuspensionStiffness);
        vehicle->SetWheelDampingRelaxation(id, m_fsuspensionDamping);
        vehicle->SetWheelDampingCompression(id, m_fsuspensionCompression);
        vehicle->SetWheelFrictionSlip(id, m_fwheelFriction);
        vehicle->SetWheelRollInfluence(id, m_frollInfluence);
    }

    vehicle->ResetSuspension();

    for ( int i = 0; i < vehicle->GetNumWheels(); i++ ) {
            //synchronize the wheels with the (interpolated) chassis worldtransform
            vehicle->UpdateWheelTransform(i, true);

            Vector3 v3Origin = vehicle->GetWheelPosition(i);
            Quaternion qRot = vehicle->GetWheelRotation(i);

            // create wheel node
            Node *wheelNode = vehicle->GetWheelNode(i);

            wheelNode->SetPosition ( v3Origin );
            Vector3 v3PosLS = vehicle->GetWheelConnectionPoint(i);

            wheelNode->SetScale ( Vector3 ( 1.0f, 0.65f, 1.0f ) );

            StaticModel *pWheel = wheelNode->CreateComponent<StaticModel>();
            pWheel->SetModel ( cache->GetResource<Model> ( "Models/Cylinder.mdl" ) );
            pWheel->SetMaterial ( cache->GetResource<Material> ( "Materials/Stone.xml" ) );
            pWheel->SetCastShadows ( true );
    }
}
//=============================================================================
//=============================================================================
void Vehicle::FixedUpdate(float timeStep)
{
    float newSteering = 0.0f;
    float accelerator = 0.0f;
    RaycastVehicle *vehicle = node_->GetComponent<RaycastVehicle>();
    // Read controls
    if ( controls_.buttons_ & CTRL_LEFT ) {
        newSteering = -1.0f;
    }
    if ( controls_.buttons_ & CTRL_RIGHT ) {
        newSteering = 1.0f;
    }
    if ( controls_.buttons_ & CTRL_FORWARD ) {
        accelerator = 1.0f;
    }
    if ( controls_.buttons_ & CTRL_BACK ) {
        accelerator = -0.5f;
    }
//    RaycastVehicle::FixedUpdate(timeStep);

// When steering, wake up the wheel rigidbodies so that their orientation is updated
    if ( newSteering != 0.0f ) {
        SetSteering(GetSteering() * 0.95f + newSteering * 0.05f);
    } else {
        SetSteering(GetSteering() * 0.8f + newSteering * 0.2f);
    }

// Set front wheel angles
    m_fVehicleSteering = steering_;
    int wheelIndex = 0;
    vehicle->SetSteeringValue(wheelIndex, m_fVehicleSteering);
    wheelIndex = 1;
    vehicle->SetSteeringValue(wheelIndex, m_fVehicleSteering);

// apply forces
    m_fEngineForce = m_fmaxEngineForce * accelerator;
    m_fBreakingForce = 0.f;

// 2x wheel drive
    for ( int i = 2; i < 4; ++i ) {
        vehicle->SetEngineForce(i, m_fEngineForce);
        //m_vehicle->setBrake( m_fBreakingForce, i );
    }
}
//=============================================================================
// sync wheels for rendering
//=============================================================================
void Vehicle::PostUpdate (float timeStep)
{
}
