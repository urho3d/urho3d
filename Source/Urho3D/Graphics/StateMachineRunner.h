//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Resource/Resource.h"
#include "../Scene/Component.h"



namespace Urho3D
{

class Scene;
class StateMachine;



/// Scene component that bypass scene update to all state machines
class URHO3D_API StateMachineRunner : public Component
{
    URHO3D_OBJECT(StateMachineRunner, Component);

public:
    /// Construct.
    explicit StateMachineRunner(Context* context);
    /// Destruct.
    ~StateMachineRunner() override;
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    void RunStateMachine(SharedPtr<StateMachine> stateMachine);
    void StopStateMachine(SharedPtr<StateMachine> stateMachine);
    
    float GetElapsedTime() const { return elapsedTime_; }
    
    void Update(float timeStep, float elapsedTime);
    
protected:
    
    /// Handle scene being assigned. This may happen several times during the component's lifetime. Scene-wide subsystems and events are subscribed to here.
    void OnSceneSet(Scene* scene) override;
    
private:
    
    /// Scene time
    float elapsedTime_ = 0;
    
    /// Handle scene update event to control camera's pitch and yaw for all samples.
    void HandleSceneUpdate(StringHash eventType, VariantMap& eventData);
    
    HashMap<SharedPtr<StateMachine>, bool> stateMachines_;
    
};

}
