#pragma once
#include <Urho3D/Input/Controls.h>
#include <Urho3D/Physics/PhysicsUtils.h>
#include <Urho3D/Scene/LogicComponent.h>

namespace Urho3D
{
class Constraint;
class Node;
class RigidBody;
}
using namespace Urho3D;

const int CTRL_FORWARD = (1 << 0);
const int CTRL_BACK = (1 << 1);
const int CTRL_LEFT = (1 << 2);
const int CTRL_RIGHT = (1 << 3);
const int CTRL_BRAKE = (1 << 4);
const float YAW_SENSITIVITY = 0.1f;
const float ENGINE_POWER = 10.0f;
const float MAX_WHEEL_ANGLE = 22.5f;
// Vehicle component, responsible for physical movement according to controls.
// Encapsulates RaycastVehicle
class Vehicle : public LogicComponent
{
    URHO3D_OBJECT(Vehicle, LogicComponent)
    public :
        /// Construct.
        Vehicle(Context* context);
    ~Vehicle();
    /// Register object factory and attributes.
    static void RegisterObject(Context* context);
    /// Perform post-load after deserialization. Acquire the components from the scene nodes.
    virtual void ApplyAttributes();

    /// Initialize the vehicle. Create rendering and physics components. Called by the application.
    void Init();

    /// Handle physics world update. Called by LogicComponent base class.
    virtual void FixedUpdate(float timeStep);
    /// Updating wheel effects here
    virtual void PostUpdate(float timeStep);

    /// Movement controls.
    Controls controls_;
    /// Get steering value
    float GetSteering()
    {
        return steering_;
    }
    /// Set steering value
    void SetSteering(float steering)
    {
        steering_ = steering;
    }
    /// Get wheel radius
    float GetWheelRadius()
    {
        return wheelRadius_;
    }
    /// Get wheel width
    float GetWheelWidth()
    {
        return wheelWidth_;
    }
    /// Used for saving - get IDs of particle nodes (memorizing these)
    VariantVector GetParticleNodeIDsAttr() const;
    /// Used for loading - set IDs of particle nodes (creating these)
    void SetParticleNodeIDsAttr(const VariantVector& value);

private:
    /// Creates particle emitter
    void CreateEmitter(Vector3 place);
    /// Current left/right steering amount (-1 to 1.)
    float steering_;
    /// tmp storage for steering
    float vehicleSteering_;
    /// linear momentum supplied by engine to RigidBody
    float engineForce_;
    /// rotational momentum preventing (dampening) wheels rotation
    float brakingForce_;
    /// maximum linear momentum supplied by engine to RigidBody
    float maxEngineForce_;
    /// stored wheel radius
    float wheelRadius_;
    /// suspension rest length (in meters)
    float suspensionRestLength_;
    /// width of wheel (used only in calculation of wheel placement)
    float wheelWidth_;
    /// suspension stiffness
    float suspensionStiffness_;
    /// suspension damping
    float suspensionDamping_;
    /// suspension compression
    float suspensionCompression_;
    /// wheel friction
    float wheelFriction_;
    /// wheel roll influence (how much car will turn sidewise)
    float rollInfluence_;
    // emitter data for saving
    Vector< Node* > particleEmitterNodeList_;
    // value to calculate acceleration
    Vector3 prevVelocity_;
    // emitter data for saving
    VariantVector emitterSaveData_;
    // storing points for emitters
    Vector3 connectionPoints_[4];
    // Do not recreate emitters if they are already created
    bool emittersCreated;
};
