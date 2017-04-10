//
// Copyright (c) 2008-2017 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../Scene/LogicComponent.h"
#include <Bullet/BulletDynamics/Vehicle/btRaycastVehicle.h>
#include "../Physics/PhysicsUtils.h"
#include "../Physics/RigidBody.h"

namespace Urho3D
{

class URHO3D_API RaycastVehicle : public LogicComponent
{
        URHO3D_OBJECT(RaycastVehicle, LogicComponent)
public:
        /// Construct.
        RaycastVehicle(Urho3D::Context* context);
        ~RaycastVehicle();
        /// Register object factory and attributes.
        static void RegisterObject(Context* context);
        /// Perform post-load after deserialization. Acquire the components from the scene nodes.
        virtual void ApplyAttributes();
        /// Add a wheel
        void AddWheel(Node *wheelNode, Vector3 connectionPoint, Vector3 wheelDirection, Vector3 wheelAxle, float restLength, float wheelRadius, bool frontWheel);
        /// Reset all suspension
        void ResetSuspension(void);
        /// Update transform for particular wheel
        void UpdateWheelTransform(int wheel, bool interpolated);
        /// Get wheel position relative to RigidBody
        Vector3 GetWheelPosition(int wheel);
        /// Get wheel rotation relative to RigidBody
        Quaternion GetWheelRotation(int wheel);
        /// Get wheel connection point relative to RigidBody
        Vector3 GetWheelConnectionPoint(int wheel);
        /// Get number of attached wheels
        int GetNumWheels()
        {
            return m_vehicle->getNumWheels();
        }
        /// Get Node of the wheel
        Node *GetWheelNode(int wheel)
        {
            return m_vpNodeWheel[wheel];
        }
        /// Set steering value of particular wheel
        void SetSteeringValue(int wheel, float steeringValue);
        /// Set suspension stiffness for particular wheel
        void SetWheelSuspensionStiffness(int wheel, float stiffness);
        /// Get suspension stiffness for particular wheel
        float GetWheelSuspensionStiffness(int wheel);
        /// Set wheel damping relaxation
        void SetWheelDampingRelaxation(int wheel, float damping);
        /// Get wheel damping relaxation
        float GetWheelDampingRelaxation(int wheel);
        /// Set wheel damping compression
        void SetWheelDampingCompression(int wheel, float compression);
        /// Get wheel damping compression
        float GetWheelDampingCompression(int wheel);
        /// Set wheel friction slip
        void SetWheelFrictionSlip(int wheel, float slip);
        /// Get wheel friction slip
        float GetWheelFrictionSlip(int wheel);
        /// Set wheel roll influence
        void SetWheelRollInfluence(int wheel, float rollInfluence);
        /// Get wheel roll influence
        float GetWheelRollInfluence(int wheel);
        /// Set engine force for the wheel
        void SetEngineForce(int wheel, float force);
        /// Init the vehicle component after creation
        void Init();
        void FixedUpdate(float timeStep);
        void PostUpdate(float timeStep);
private:
        bool activate;
        // Hull RigidBody
        WeakPtr<RigidBody> hullBody_;
        // raycast vehicle
        btRaycastVehicle::btVehicleTuning   m_tuning;
        btVehicleRaycaster                  *m_vehicleRayCaster;
        btRaycastVehicle                    *m_vehicle;

        // IDs of the wheel scene nodes for serialization.
        Vector<Node*>           m_vpNodeWheel;
        Vector<Quaternion>      orig_rotation;
};

void RegisterRaycastVehicleLibrary(Context* context);
}
