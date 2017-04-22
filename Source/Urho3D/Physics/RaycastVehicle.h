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
#include "../Physics/PhysicsUtils.h"
#include "../Physics/RigidBody.h"

namespace Urho3D
{

    class RaycastVehicleData;

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
            /// Add a wheel (all parameters are relative to RigidBody/node)
            void AddWheel(Node *wheelNode, Vector3 wheelDirection, Vector3 wheelAxle, float restLength, float wheelRadius, bool frontWheel);
            /// Reset all suspension
            void ResetSuspension(void);
            /// Update transform for particular wheel
            void UpdateWheelTransform(int wheel, bool interpolated);
            /// Get wheel position relative to RigidBody
            Vector3 GetWheelPosition(int wheel);
            /// Get wheel rotation relative to RigidBody
            Quaternion GetWheelRotation(int wheel);
            /// Get wheel connection point relative to RigidBody
            Vector3 GetWheelConnectionPoint(int wheel) const;
            /// Get number of attached wheels
            int GetNumWheels() const;
            /// Get Node of the wheel
            Node *GetWheelNode(int wheel) const;
            /// Set steering value of particular wheel
            void SetSteeringValue(int wheel, float steeringValue);
            /// Get steering value of particular wheel
            float GetSteeringValue(int wheel) const;
            /// Set suspension stiffness for particular wheel
            void SetWheelSuspensionStiffness(int wheel, float stiffness);
            /// Get suspension stiffness for particular wheel
            float GetWheelSuspensionStiffness(int wheel) const;
            /// Set wheel damping relaxation
            void SetWheelDampingRelaxation(int wheel, float damping);
            /// Get wheel damping relaxation
            float GetWheelDampingRelaxation(int wheel) const;
            /// Set wheel damping compression
            void SetWheelDampingCompression(int wheel, float compression);
            /// Get wheel damping compression
            float GetWheelDampingCompression(int wheel) const;
            /// Set wheel friction slip
            void SetWheelFrictionSlip(int wheel, float slip);
            /// Get wheel friction slip
            float GetWheelFrictionSlip(int wheel) const;
            /// Set wheel roll influence
            void SetWheelRollInfluence(int wheel, float rollInfluence);
            /// Get wheel roll influence
            float GetWheelRollInfluence(int wheel) const;
            /// Set engine force for the wheel
            void SetEngineForce(int wheel, float force);
            /// Get engine force for the wheel
            float GetEngineForce(int wheel) const;
            /// Set hand brake (wheel rotation blocking force)
            void SetBrake(int wheel, float force);
            /// Get hand break value
            float GetBrake(int wheel) const;
            /// Set wheel radius
            void SetWheelRadius(int wheel, float wheelRadius);
            /// Get wheel radius
            float GetWheelRadius(int wheel) const;
            /// Sets node initial positions
            void ResetWheels();
            /// Get wheel rest length
            void SetWheelRestLength(int wheel, float length);
            /// Get wheel rest length
            float GetWheelRestLength(int wheel) const;
            /// Set sliding factor 0 <= x <= 1
            /// the less the value, more sliding.
            void SetWheelSkidInfo(int wheel, float factor);
            /// Sliding factor 0 <= x <= 1
            float GetWheelSkidInfo(int wheel) const;
            /// true if wheel touches ground (raycast hits something)
            bool WheelIsGrounded(int wheel) const;
            /// Set maximum suspension travel value
            void SetMaxSuspensionTravel(int wheel, float maxSuspensionTravel);
            /// Get maximum suspension travel value
            float GetMaxSuspensionTravel(int wheel);
            /// Set wheel direction vector
            void SetWheelDirection(int wheel, Vector3 direction);
            /// Get wheel direction vector
            Vector3 GetWheelDirection(int wheel) const;
            /// Set wheel axle vector
            void SetWheelAxle(int wheel, Vector3 axle);
            /// Get wheel axle vector
            Vector3 GetWheelAxle(int wheel) const;
            /// Get wheel slide speed
            float GetWheelSideSlipSpeed(int wheel) const;
            /// get side speed which is considered sliding
            float GetMaxSideSlipSpeed() const;
            /// set side speed which is considered sliding
            void SetMaxSideSlipSpeed(float speed);
            /// set cumuative skid info
            void SetWheelSkidInfoCumulative(int wheel, float skid);
            /// get cumuative skid info
            float GetWheelSkidInfoCumulative(int wheel) const;
            /// true if front wheel, otherwise false
            bool IsFrontWheel(int wheel) const;
            /// get wheel contact position
            Vector3 GetContactPosition(int wheel) const;
            // get contact normal
            Vector3 GetContactNormal(int wheel) const;
            /// Set revolution per minute value for when weel
            /// doesn't touch ground
            /// If set to 0 (or not set), calculated from engine force
            /// (probably not what you want).
            void SetInAirRPM(float rpm);
            /// Get revolution per minute value for when weel
            /// doesn't touch ground
            float GetInAirRPM() const;
            /// Init the vehicle component after creation
            void Init();
            void FixedUpdate(float timeStep);
            void FixedPostUpdate(float timeStep);
            void PostUpdate(float timeStep);
            VariantVector GetWheelDataForSave() const;
            void SetLoadedWheelData(const VariantVector& value);
        private:
            // If the RigidBody should be activated
            bool activate_;
            // Hull RigidBody
            WeakPtr<RigidBody> hullBody_;
            // Opaque Bullet data hidden from public
            RaycastVehicleData *vehicleData_;
            // Nodes of all wheels
            Vector<Node*>           wheelNodes_;
            // All wheels original rotations
            // These are applied in addition to wheel
            // rotations by btRaycastVehicle
            Vector<Quaternion>      origRotation_;
            // Revolutions per minute value for in-air motor wheels
            // It is per vehicle. I know, I will fix this later.
            // FIXME: set this one per wheel
            float                   inAirRPM_;
            // Per-wheel extra settings
            Vector<float> skidInfoCumulative_;
            // wheel side movement speed
            Vector<float> wheelSideSlipSpeed_;
            // side slip speed threshold
            float maxSideSlipSpeed_;
            // Loaded data temporarily wait here for ApplyAttributes
            // to come pick them up
            VariantVector loadedWheelData_;
    };

    void RegisterRaycastVehicleLibrary(Context* context);
}
