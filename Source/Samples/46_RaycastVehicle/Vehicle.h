#pragma once
#include <Urho3D/Input/Controls.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Physics/PhysicsUtils.h>

namespace Urho3D
{
    class Constraint;
    class Node;
    class RigidBody;
}
using namespace Urho3D;
//=============================================================================
//=============================================================================
const int CTRL_FORWARD = 1;
const int CTRL_BACK = 2;
const int CTRL_LEFT = 4;
const int CTRL_RIGHT = 8;
const float YAW_SENSITIVITY = 0.1f;
const float ENGINE_POWER = 10.0f;
const float DOWN_FORCE = 10.0f;
const float MAX_WHEEL_ANGLE = 22.5f;
//=============================================================================
// Vehicle component, responsible for physical movement according to controls.
// Encapsulates RaycastVehicle
//=============================================================================
class Vehicle : public LogicComponent
{
        URHO3D_OBJECT(Vehicle, LogicComponent)
public:
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
        virtual void PostUpdate(float timeStep);

/// Movement controls.
        Controls controls_;
/// Steering control
        float GetSteering()
        {
            return steering_;
        }
        void SetSteering(float steering)
        {
            steering_ = steering;
        }
        float GetWheelRadius()
        {
            return m_fwheelRadius;
        }
        float GetWheelWidth()
        {
            return m_fwheelWidth;
        }
private:
        /// Current left/right steering amount (-1 to 1.)
        float steering_;
        float m_fVehicleSteering;
        float m_fEngineForce;
        float m_fBreakingForce;
        float m_fmaxEngineForce;
        float m_fmaxBreakingForce;
        float m_fwheelRadius;
        float m_fsuspensionRestLength;
        float m_fwheelWidth;
        float m_fsuspensionStiffness;
        float m_fsuspensionDamping;
        float m_fsuspensionCompression;
        float m_fwheelFriction;
        float m_frollInfluence;
};
