//
// Copyright (c) 2008-2016 the Urho3D project.
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

#pragma once

#include "../Scene/Component.h"
#include "../Scene/Scene.h"

struct ik_effector_t;

namespace Urho3D
{

class Context;
class IKSolver;

class IKEffector : public Component
{
    URHO3D_OBJECT(IKEffector, Component)

public:

    /// Constructs a new IK effector.
    IKEffector(Context* context);

    /// Destructs he IK effector.
    virtual ~IKEffector();

    /*!
     * Registers this class as an object factory.
     */
    static void RegisterObject(Context* context);

    /// Retrieves the node that is being used as a target. Can be NULL.
    Node* GetTargetNode() const;

    /*!
     * @brief The position of the target node provides the target position of
     * the effector node.
     *
     * The IK chain is solved such that the node to which this component is
     * attached to will try to move to the position of the target node.
     * @param targetNode A scene node that acts as a target. Specifying NULL
     * will erase the target and cause the solver to ignore this chain.
     * @note You will get very strange behaviour if you specify a target node
     * that is part the IK chain being solved for (circular dependency). Don't
     * do that.
     */
    void SetTargetNode(Node* targetNode);

    /*!
     * @brief Retrieves the name of the target node. The node doesn't
     * necessarily have to exist in the scene graph.
     */
    const String& GetTargetName() const;

    /*!
     * @brief Sets the name of the target node. The node doesn't necessarily
     * have to exist in the scene graph. When a node is created that matches
     * this name, it is selected as the target.
     */
    void SetTargetName(const String& nodeName);

    const Vector3& GetTargetPosition() const;
    void SetTargetPosition(const Vector3& targetPosition);

    const Quaternion& GetTargetRotation() const;
    void SetTargetRotation(const Quaternion& targetRotation);

    Vector3 GetTargetRotationEuler() const;
    void SetTargetRotationEuler(const Vector3& targetRotation);

    unsigned GetChainLength() const;
    void SetChainLength(unsigned chainLength);

    float GetWeight() const;
    void SetWeight(float weight);

    float GetRotationWeight() const;
    void SetRotationWeight(float weight);

    float GetRotationDecay() const;
    void SetRotationDecay(float decay);

    bool DoWeightedNlerp() const;
    void SetWeightedNlerp(bool enable);

    bool DoInheritParentRotation() const;
    void SetInheritParentRotation(bool enable);

    void UpdateTargetNodePosition();

    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

    void SetSolver(IKSolver* solver);
    void SetEffector(ik_effector_t* effector);

private:
    WeakPtr<Node> targetNode_;
    WeakPtr<IKSolver> solver_;
    ik_effector_t* ikEffector_;

    String targetName_;
    Vector3 targetPosition_;
    Quaternion targetRotation_;
    unsigned chainLength_;
    float weight_;
    float rotationWeight_;
    float rotationDecay_;
    bool weightedNlerp_;
    bool inheritParentRotation_;
};

} // namespace Urho3D
