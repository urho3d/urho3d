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

class StateMachine;

/// State machine transition. Belongs to a single StateMachineState instance
struct URHO3D_API StateMachineTransition
{
    /// Transition name
    String name_;
    /// Initial state
    String stateFrom_;
    /// Destination state
    String stateTo_;
    /// The time at which the destination state will start. The offset is in normalized time of the destination state.
    float offset_ = 0;
    /// The duration of the transition in seconds
    float duration_ = 0;
    /// When active the transition will have an exit time condition.
    bool hasExitTime_ = false;
    /// If hasExitTime is true, exitTime represents the exact time at which the transition can take effect.
    /// This is represented in normalized time, so for example an exit time of 0.75 means that on the first frame where 75% of the animation has played, the Exit Time condition will be true. On the next frame, the condition will be false.
    /// Transitions with exit times greater than one will be evaluated only once, so they can be used to exit at a specific time, after a fixed number of loops. For example, a transition with an exit time of 3.5 will be evaluated once, after three and a half loops.
    float exitTime_ = 0;
    
    /// Construct.
    /// This constructor is required for hashmap
    StateMachineTransition()
    {
        
    }

    /// Construct.
    StateMachineTransition(const String &name, const String &stateFrom, const String &stateTo)
    :name_(name)
    ,stateFrom_(stateFrom)
    ,stateTo_(stateTo)
    {
    }

};


/// Single state machine of a state machine. Belongs to a single StateMachineConfig instance
class URHO3D_API StateMachineState: public RefCounted
{
    friend class StateMachine;
    friend class StateMachineConfig;
    
public:
    /// Construct.
    explicit StateMachineState(const String &name);
    ~StateMachineState();
    
    /// Create new transition from this state to a given state with given transition name
    bool AddTransition(const StateMachineTransition &transition);
    /// Verifys if transition is possible
    bool CanTransit(const String &transitionName);
    
    String GetName() const;
    
private:
    
    // State name
    String name_;
    /// The default speed of the motion.
    float speed_ = 1.0;
    /// Name of the corresponded animation clip if applicable
    Urho3D::String animationClip_;// example "Animations/SampleScene/AnimationDoor1Close.ani",
    
    /// All transitions from this state
    /// key represents transition name (trigger or event that executes this transition)
    HashMap<String, StateMachineTransition> transitions_;

};



/// State machine listener interface definition
class URHO3D_API StateMachineDelegate 
{
    
public:
    /// Called when state machine transits to a new state
    virtual void StateMachineDidTransit(StateMachine *sender, const String &stateFrom, const String &transitionName, const String &stateTo) = 0;

};

/// State machine resource.
class URHO3D_API StateMachineConfig : public ResourceWithMetadata
{
    URHO3D_OBJECT(StateMachineConfig, ResourceWithMetadata);
    
    friend class StateMachine;
    
public:
    /// Construct.
    explicit StateMachineConfig(Context* context);
    /// Destruct.
    ~StateMachineConfig() override;
    /// Register object factory. Drawable must be registered first.
    static void RegisterObject(Context* context);

    /// Create new state
    bool AddState(const String &stateName);
    /// Create new transition
    bool AddTransition(const StateMachineTransition &transition);
    /// Verify if transition is correct
    bool CanTransit(const String &stateName, const String &transitionName);
    
    /// Load from JSON data. Removes all existing child nodes and components first. Return true if successful.
    bool LoadJSON(const JSONValue& source);
    
    /// Load from a JSON file. Return true if successful.
    bool LoadJSON(Deserializer& source);
    /// Load from a unity JSON file. Return true if successful.
    bool LoadUnityJSON(Deserializer& source);
    
    unsigned int GetStatesCount() const;

private:
    /// Available states
    HashMap<String, SharedPtr<StateMachineState>> states_;
    
};



/// State machine user
class URHO3D_API StateMachine: public RefCounted
{
    
public:
    /// Construct.
    explicit StateMachine(StateMachineConfig *config, const String &initialState);
    /// Destruct.
    ~StateMachine() override;
    
    /// Set delegate to listen events. Overrides existing delegate
    void SetDelegate(StateMachineDelegate *delegate);
    /// Get existing delegate
    StateMachineDelegate *GetDelegate();
    
    /// Execute transition
    bool Transit(const String &transitionName);
    
    /// Gets the current state name
    String GetCurrentState() const;
    
    /// Update transitions
    void OnUpdate(float time);
    
private:
    /// State machine configuration
    SharedPtr<StateMachineConfig> config_ = nullptr;
    
    /// Delegate for listening for transitions
    StateMachineDelegate *delegate_ = nullptr;
    
    /// Actual current state
    StateMachineState *stateCurrent_ = nullptr;
    
};



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
    
protected:
    
    float _transitionTime;
    
    
    /// Handle scene being assigned. This may happen several times during the component's lifetime. Scene-wide subsystems and events are subscribed to here.
    void OnSceneSet(Scene* scene) override;
    
private:
    
    /// Handle scene update event to control camera's pitch and yaw for all samples.
    void HandleSceneUpdate(StringHash eventType, VariantMap& eventData);
    
    HashMap<SharedPtr<StateMachine>, bool> stateMachines_;
//    PODVector<SharedPtr<StateMachine>> stateMachines_;
    
};

}
