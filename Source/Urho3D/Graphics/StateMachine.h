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

namespace Urho3D
{

class StateMachine;

struct URHO3D_API StateMachineTransition
{
    /// Transition name
    String name_;
    
    /// initial state
    String stateFrom_;
    /// destination state
    String stateTo_;
    
//    /// disables a transition (unity style)
//    bool mute_ = false;

    /// Construct.
    StateMachineTransition(const String &name, const String &stateFrom, const String &stateTo)
    :name_(name)
    ,stateFrom_(stateFrom)
    ,stateTo_(stateTo)
    {
    }

};

struct URHO3D_API StateMachineState
{
    // State name
    String name_;
    
    /// All transitions from this state
    /// key represents trigger
    HashMap<String, StateMachineTransition *> transitions_;
    
    /// Construct.
    StateMachineState(const String &name);
    ~StateMachineState();
    
    bool AddTransition(const String &stateTo, const String &transitionName);
    bool CanTransit(const String &transitionName);

};

class URHO3D_API StateMachineDelegate 
{
public:
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

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    bool BeginLoad(Deserializer& source) override;
    /// Save resource. Return true if successful.
    bool Save(Serializer& dest) const override;

    /// Create new state
    bool AddState(const String &stateName);
    /// Create new transition
    bool AddTransition(const String &stateFrom, const String &stateTo, const String &transitionName);
    
//    bool IsTransitionMuted(const String &transitionName);
//    bool SetTransitionMuted(const String &transitionName, bool value);
    
    /// Verify if transition is correct
    bool CanTransitFromState(const String &stateName, const String &transitionName);

private:
    
    /// Available states
    HashMap<String, StateMachineState *> states_;
};



/// State machine user
class URHO3D_API StateMachine: public RefCounted
{
    
public:
    /// Construct.
    explicit StateMachine(StateMachineConfig *config, const String &initialState);
    /// Destruct.
    ~StateMachine() override;
    /// Register object factory. Drawable must be registered first.
    static void RegisterObject(Context* context);
    
    /// Set delegate to listen events. Overrides existing delegate
    void SetDelegate(StateMachineDelegate *delegate);
    /// Get existing delegate
    StateMachineDelegate *GetDelegate();
    
    /// Execute transition
    bool Transit(const String &transitionName);
    
private:
    
    /// State machine configuration
    SharedPtr<StateMachineConfig> config_ = nullptr;
    
    /// Delegate for listening for transitions
    StateMachineDelegate *delegate_ = nullptr;
    
    /// Actual current state
    StateMachineState *stateCurrent_ = nullptr;
};

}
