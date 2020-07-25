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

/// State machine transition condition.
struct StateMachineConfigTransitionCondition {
    /// Variable name
    String parameter_;
    /// Desired value for condition to be satisfied
    bool value_ = true;
};



/// State machine transition. Belongs to a single StateMachineState instance
struct URHO3D_API StateMachineConfigTransition
{
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
    /// Conditions for this transition
    Vector<StateMachineConfigTransitionCondition> conditions_;
    
    /// Construct.
    /// This constructor is required for hashmap
    StateMachineConfigTransition()
    {
        
    }

    /// Construct.
    StateMachineConfigTransition(const String &stateFrom, const String &stateTo)
    :stateFrom_(stateFrom)
    ,stateTo_(stateTo)
    {
    }

    bool operator ==(const StateMachineConfigTransition &other) {
        return stateTo_ == other.stateTo_ && stateFrom_ == other.stateFrom_;
    }
    
};


/// Single state machine of a state machine. Belongs to a single StateMachineConfig instance
class URHO3D_API StateMachineConfigState: public RefCounted
{
    friend class StateMachine;
    friend class StateMachineConfig;
    
public:
    /// Construct.
    explicit StateMachineConfigState(const String &name);
    ~StateMachineConfigState();
    
    /// Create new transition from this state to a given state with given transition name
    void AddTransition(const StateMachineConfigTransition &transition);
    /// Get the state name
    String GetName() const;
    /// Check if this parameter may cause transitions
    bool HaveTransitionsFor(const String &parameterName);
    
private:
    
    // State name
    String name_;
    /// The default speed of the motion.
    float speed_ = 1.0;
    /// Name of the corresponded animation clip if applicable
    Urho3D::String animationClip_;// example "Animations/SampleScene/AnimationDoor1Close.ani",
    
    /// All transitions from this state
    /// key represents transition name (trigger or event that executes this transition)
    Vector<StateMachineConfigTransition> transitions_;

};



/// State machine resource.
class URHO3D_API StateMachineConfig : public Resource
{
    URHO3D_OBJECT(StateMachineConfig, Resource);
    
    friend class StateMachine;
    
public:
    /// Construct.
    explicit StateMachineConfig(Context* context);
    /// Destruct.
    ~StateMachineConfig() override;
    /// Register object factory. Drawable must be registered first.
    static void RegisterObject(Context* context);
    
    bool BeginLoad(Deserializer& source) override;

    /// Get number of states
    unsigned int GetStatesCount() const;
    /// Create new state
    bool AddState(const String &stateName);
    /// Create new transition
    bool AddTransition(const StateMachineConfigTransition &transition);
    
    /// Load from JSON data. Removes all existing child nodes and components first. Return true if successful.
    bool LoadJSON(const JSONValue& source);
    /// Load from a JSON file. Return true if successful.
    bool LoadJSON(Deserializer& source);
    /// Load from a unity JSON file. Return true if successful.
    bool LoadUnityJSON(Deserializer& source);

private:
    /// Available states
    HashMap<String, SharedPtr<StateMachineConfigState>> states_;

};


}
