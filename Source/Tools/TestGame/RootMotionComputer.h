//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Container/HashMap.h>
#include <Urho3D/Math/StringHash.h>

using namespace Urho3D;

// a struct to store information about all of the animation states
struct AnimInfo
{
    float currentNormalizedTime;
    float previousNormalizedTime;
    float currentWeight; // the actual weight value queried from the AnimationState
    float contributingWeight; // the weight the AnimationState is actually contributing to the final result based on layers
    Vector3 currentPosition;
    Vector3 previousPosition;
    Vector3 startPosition;
    Vector3 endPosition;
    Vector3 currentAxis;
    Vector3 previousAxis;
    Vector3 startAxis;
    Vector3 endAxis;
    Quaternion totalRotation;
};

// an enum to describe how delta values should be computed
enum RootMotionComputationMode
{
    ZTranslation,
    XZTranslation,
    TranslationAndRotation
};

/// RootMotionComputer component,
class RootMotionComputer : public LogicComponent
{
    OBJECT(RootMotionComputer)

public:
    /// Construct.
    RootMotionComputer(Context* context);

    /// Register object factory and attributes.
    static void RegisterObject(Context* context);

    /// Handle scene update. Called by LogicComponent base class.
    virtual void Update(float timeStep);

    void SetupNewAnimInfo(const String& animName);

protected:
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

private:
    RootMotionComputationMode           computationMode;

    float                               debugGizmoSize;

    // the pelvis joint from which the script obtains x-z motion and y-rotation for the root
    Node*                               pelvis;

    Node*                               rootNode;

    // its local axis specifying the right direction
    Vector3                             pelvisRightAxis;

    // a variable to temporarily store and set the pelvis local position after computation
    Vector3                             pLocalPosition;

    // local-space delta position since previous frame
    Vector3                             dPosition;

    // local-space delta rotation since previous frame
    Quaternion                          dRotation;

    HashMap<StringHash, AnimInfo>       animInfoTable;

};
