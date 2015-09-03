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

#include <Urho3D/Urho3D.h>

#include <Urho3D/Core/Context.h>
#include <Urho3D/Resource/ResourceCache.h>

#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/Animation.h>
#include <Urho3D/Graphics/AnimationState.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/DebugRenderer.h>

#include "RootMotionComputer.h"

#include <Urho3D/DebugNew.h>

/*
 * Obtain the position of t projected onto rootNode's zx plane
 * */
inline Vector3 GetProjectedPosition(Node* r, Node* t)
{
    Vector3 p = r->GetWorldTransform().Inverse() * t->GetWorldPosition();
    p.y_ = 0;
    return p;
}

/*
 * Obtain the projection of axis on t onto rootNode's zx plane
 * */
inline Vector3 GetProjectedAxis(Node* r, Node* t, Vector3 axis)
{
    Quaternion invQ = r->GetWorldRotation().Inverse();
    Vector3 dir = t->GetWorldRotation() * axis;
    Vector3 p =  invQ * dir;
    p.y_ = 0;
    return p;
}

RootMotionComputer::RootMotionComputer(Context* context) :
    LogicComponent(context),
    debugGizmoSize(0.25f),
    computationMode(TranslationAndRotation),
    pelvis(NULL),
    rootNode(NULL)
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    SetUpdateEventMask(USE_UPDATE);
}

void RootMotionComputer::Update(float timeStep)
{
    // Components have their scene node as a member variable for convenient access. Rotate the scene node now: construct a
    // rotation quaternion from Euler angles, scale rotation speed with the scene update time step
    // node_->Rotate(Quaternion(rotationSpeed_.x_ * timeStep, rotationSpeed_.y_ * timeStep, rotationSpeed_.z_ * timeStep));
}

void RootMotionComputer::SetupNewAnimInfo(const String& animName)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    AnimatedModel* model = GetComponent<AnimatedModel>();
    if (!model)
        return;

    Animation* anim = cache->GetResource<Animation>(animName);
    if (!anim)
        return;

    AnimInfo newInfo;
    SharedPtr<AnimationState> state(new AnimationState(model, anim));
    state->SetTime(0.0f);
    state->SetWeight(1.0f);
    state->Apply();

    newInfo.startPosition = GetProjectedPosition(rootNode, pelvis);
    newInfo.previousPosition = GetProjectedPosition(rootNode, pelvis);
    newInfo.startAxis = GetProjectedAxis(rootNode, pelvis, pelvisRightAxis);
    newInfo.previousAxis = GetProjectedAxis(rootNode, pelvis, pelvisRightAxis);

    state->SetTime(anim->GetLength());
    state->Apply();

    newInfo.endPosition = GetProjectedPosition(rootNode, pelvis);
    newInfo.endAxis = GetProjectedAxis(rootNode, pelvis, pelvisRightAxis);
        
    // store the total rotation over the course of the animation
    Quaternion q;
    q.FromRotationTo(newInfo.startAxis, newInfo.endAxis);
    newInfo.totalRotation = q;
    animInfoTable[StringHash(animName)] = newInfo;
}

void RootMotionComputer::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (!pelvis)
        return;

    float distance = 10.0f;
    Vector3 dir = pelvis->GetWorldRotation() * pelvisRightAxis * debugGizmoSize;
    // draw pelvis right axis
    debug->AddLine(pelvis->GetWorldPosition(), pelvis->GetWorldPosition() + dir * distance, Color::RED, depthTest);

    // draw root node axes
    dir = rootNode->GetWorldRotation() * Vector3::FORWARD * debugGizmoSize;
    debug->AddLine(rootNode->GetWorldPosition(), rootNode->GetWorldPosition() + dir * distance, Color::BLUE, depthTest);

    dir = rootNode->GetWorldRotation() * Vector3::RIGHT * debugGizmoSize;
    debug->AddLine(rootNode->GetWorldPosition(), rootNode->GetWorldPosition() + dir * distance, Color::RED, depthTest);

    dir = rootNode->GetWorldRotation() * Vector3::UP * debugGizmoSize;
    debug->AddLine(rootNode->GetWorldPosition(), rootNode->GetWorldPosition() + dir * distance, Color::GREEN, depthTest);
}

void RootMotionComputer::OnNodeSet(Node* node)
{
    if (!node)
        return;

    Node* p = node->GetParent();
    while (!p)
    {
        node = p;
        p = node->GetParent();
    }

    rootNode = node;
}

void RootMotionComputer::ComputeRootMotion()
{
    // store whether or not we should be bothering to compute rotation parameters
    bool isRotationMode = (computationMode == TranslationAndRotation);

    AnimationController* ac = GetComponent<AnimationController>();
        
    // an array to store any AnimationStates that have been added to the animation component since the last frame
    ArrayList newlyAddedAnimationStates = null;
    
    // first store current actual weight and time information for all AnimationStates
    foreach (AnimationState aState in anim)
    {
        // store the highest and lowest layers for use in a later iteration
        highestLayer = Mathf.Max(highestLayer, aState.layer);
        lowestLayer = Mathf.Min(lowestLayer, aState.layer);
        
        // if any new animation states have been added, then deal with them in a following iteration
        if (!animInfoTable.ContainsKey(aState))
        {
            AddAnimInfoToTable(aState);
            newlyAddedAnimationStates.Add(aState);
            continue;
        }
        
        info = (AnimInfo) animInfoTable[aState];
        info.currentNormalizedTime = aState.normalizedTime;
        info.currentWeight = aState.weight;
        
        animInfoTable[aState] = info;
        
        // scrub the weight down to 0 for the next iteration
        aState.weight = 0f;
    }
    
    // if any new AnimationStates have been added, add their info to the table
    if (newlyAddedAnimationStates != null && newlyAddedAnimationStates.Count > 0)
    {
        // first set all weights to 0, which will include newly added states
        foreach (AnimationState aState in anim) aState.weight = 0f;
        
        // store all the properties for the new states
        foreach (AnimationState aState in newlyAddedAnimationStates) SetupNewAnimInfo(aState);
    }
    
    // compute normalized AnimationState weights across layers since Unity does not expose them
    float remainingWeight = 1f;
    for (int i=highestLayer; i>=lowestLayer; i--)
    {           
        float weightOnThisLayer = 0f;
        foreach (AnimationState aState in anim)
        {
            if (aState.layer != i) continue;
            
            info = (AnimInfo) animInfoTable[aState];
            
            // find out how much weight the animation state is actually contributing this frame
            if (!aState.enabled || remainingWeight <= 0f)
            {
                info.contributingWeight = 0f;
            }
            else
            {
                info.contributingWeight = remainingWeight * info.currentWeight;
            }
            
            weightOnThisLayer += info.contributingWeight;
            
            animInfoTable[aState] = info;
        }
        // if the weight on this layer is > 1, then normalize it
        // using Blend() or setting weights manually will not affect other weights on the layer, so they must be manually renormalized
        if (weightOnThisLayer > 1f)
        {
            float oneOverWeightOnThisLayer = 1f/weightOnThisLayer;
            foreach (AnimationState aState in anim)
            {
                if (aState.layer != i) continue;
                info = (AnimInfo) animInfoTable[aState];
                info.contributingWeight = info.contributingWeight * oneOverWeightOnThisLayer;
                animInfoTable[aState] = info;
            }
            weightOnThisLayer = 1f;
        }
        remainingWeight -= weightOnThisLayer;
    }
    
    // reset the delta values for this frame
    dPosition = Vector3::ZERO
    dRotation = Quaternion::IDENTITY;
    
    // compute each AnimationState's individual contribution to the current frame's delta values
    foreach (AnimationState aState in anim)
    {   
        info = (AnimInfo) animInfoTable[aState];
        
        // early out if this state was contributing nothing this frame
        if (info.contributingWeight == 0f) continue;
        
        // early out if aState uses additive blending
        // NOTE: Not entirely sure if this is ideal or not, but it generally should be
        if (aState.blendMode == AnimationBlendMode.Additive) continue;
                    
        // scrub the weight up to 1 for sampling values
        aState.weight = 1f;
        
        // sample the values for the projected root configuration back one frame
        // NOTE: cannot simply store these values from one frame to the next since user may manually change the time value at any point
        aState.time = aState.time - Time.deltaTime * aState.speed;
        info.previousNormalizedTime = aState.normalizedTime;
        anim.Sample();
        info.previousAxis = GetProjectedAxis(pelvis, pelvisRightAxis);
        info.previousPosition = GetProjectedPosition(pelvis);
        
        // sample the values for the projected root configuration at the current frame
        aState.normalizedTime = info.currentNormalizedTime;
        anim.Sample();
        info.currentPosition = GetProjectedPosition(pelvis);
        info.currentAxis = GetProjectedAxis(pelvis, pelvisRightAxis);
        
        // ensure both normalizedTime values are positive
        info.previousNormalizedTime = 1f + info.previousNormalizedTime - (int)info.previousNormalizedTime;
        info.currentNormalizedTime = 1f + info.currentNormalizedTime - (int)info.currentNormalizedTime;
        
        // determine the contribution to the root's delta this frame based on whether the animation looped since the previous frame
        if (info.previousNormalizedTime-(int)info.previousNormalizedTime > info.currentNormalizedTime-(int)info.currentNormalizedTime)
        {
            // compute displacement with respect to identity
            p = info.contributingWeight * ((info.endPosition - info.previousPosition) + (info.currentPosition - info.startPosition));
            if (isRotationMode)
            {
                // rotate displacement into current orientation
                p = Quaternion.FromToRotation(info.currentAxis, info.totalRotation*Vector3.right) * p;  
                // compute angular displacement and append to result
                dRotation *= Quaternion.Slerp(Quaternion.identity, 
                    Quaternion.FromToRotation(info.previousAxis, info.endAxis) * Quaternion.FromToRotation(info.startAxis, info.currentAxis), 
                    info.contributingWeight);
            }
            // append displacement to result
            dPosition += p;
        }
        else
        {
            // compute displacement with respect to identity
            p = info.contributingWeight * (info.currentPosition - info.previousPosition);
            if (isRotationMode)
            {
                // rotate displacement into current orientation
                p = Quaternion.FromToRotation(info.currentAxis, Vector3.right) * p;
                // compute angular displacement and append to result
                dRotation *= Quaternion.Slerp(Quaternion.identity, Quaternion.FromToRotation(info.previousAxis, info.currentAxis), info.contributingWeight);
            }
            // append displacement to result
            dPosition += p;
        }
        dPosition=dPosition*0.25f;
        
        // scrub the weight back down to 0 so as to not affect sampling of other states
        aState.weight = 0f;
    }
    
    // reset weights to where they were before computation
    foreach (AnimationState aState in anim)
    {   
        info = (AnimInfo) animInfoTable[aState];
        aState.weight = info.currentWeight;
    }
    
    // return the character to its current pose
    anim.Sample();
    
    // delta values for the first frame should simply move from the starting configuration into the current frame of animation
    if (isFirstFrame)
    {
        // simply translate and rotate to the current projected position and orientation
        dPosition = GetProjectedPosition(pelvis);
        dRotation = Quaternion.FromToRotation(Vector3.right, GetProjectedAxis(pelvis, pelvisRightAxis));
        
        // rotate displacement into current orientation
        if (isRotationMode) dPosition = Quaternion.FromToRotation(GetProjectedAxis(pelvis, pelvisRightAxis), Vector3.right) * dPosition;
                    
        isFirstFrame = false;
    }
    
    // store the local position of the pelvis before returning it to hover over the root
    pLocalPosition = pelvis.localPosition;
    
    // zero out the local x-component of the position delta if root translation method is z-only
    if (computationMode == RootMotionComputationMode.ZTranslation) dPosition = Vector3.forward * Vector3.Dot(dPosition, Vector3.forward);
    // otherwise zero out the local x-position of the pelvis
    else pLocalPosition.x = 0f;
    
    // return the pelvis to a point hovering over the root
    pLocalPosition.z = 0f;
    pelvis.localPosition = pLocalPosition;
                            
    // if computing rotation, then zero out local y-rotation of the pelvis
    if (isRotationMode) pelvis.localRotation = Quaternion.FromToRotation(GetProjectedAxis(pelvis, pelvisRightAxis), Vector3.right) * pelvis.localRotation;
    
#if 0
    // draw debug lines if requested
    if (isDebugMode) DrawDebug();
    
    // return if root movement is not requested (e.g. a character controller will use delta values)
    if (!applyMotion) return;
    
    // apply rotation if requested
    if (isRotationMode) rootNode.localRotation *= dRotation;
    
    // apply translation
    rootNode.Translate(dPosition, Space.Self);
#endif

}