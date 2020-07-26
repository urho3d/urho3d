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
#include "../Graphics/StateMachineConfig.h"



namespace Urho3D
{

class StateMachineConfig;
class StateMachineConfigState;
class StateMachine;
class StateMachineRunner;



/// Represents the actual state of the state machine instance. Including blending between 2 states
struct URHO3D_API StateMachineState 
{
    /// First state and weight 
    String state1_;
    float weigth1_;
    
    /// Second state and weight
    String state2_;
    float weigth2_;
    
    /// Indicates if state machine is in transition state (state is blended)
    bool transition_ = false;
    
    StateMachineState(const String &state1, float weigth1, const String &state2, float weigth2)
    :state1_(state1)
    ,weigth1_(weigth1)
    ,state2_(state2)
    ,weigth2_(weigth2)
    {}
    
};



/// Parameter source listener interface 
class URHO3D_API StateMachineParameterSourceListener {
public:
    virtual void OnParameterDidChangeValue(const String &parameterName, bool oldValue, bool newValue) = 0;
    
};



/// Storage for variables used by state machines
class URHO3D_API StateMachineParameterSource: public RefCounted 
{
public:
    /// Retrieve value
    bool Get(const String &parameterName, bool *exists = nullptr) const;
    /// Sets new value
    void Set(const String &parameterName, bool value);
    
    /// Subscribe listener for updates
    void Subscribe(StateMachineParameterSourceListener *listener);
    /// Unsubscribe listener from updates
    void Unsubscribe(StateMachineParameterSourceListener *listener);
    
private:
    /// Available states
    HashMap<String, bool> parameters_;
    /// Subscribed listeners
    HashMap<StateMachineParameterSourceListener *, bool> listeners_;
};



/// State machine listener interface definition
class URHO3D_API StateMachineDelegate 
{
    
public:
    /// Called when state machine transits to a new state
    virtual void StateMachineDidTransit(StateMachine *sender, const String &stateFrom, const String &stateTo) = 0;
    virtual void StateMachineDidUpdateBlendState(StateMachine *sender) = 0;

};



/// State machine instance
class URHO3D_API StateMachine: public RefCounted, public StateMachineParameterSourceListener
{
    
public:
    /// Construct.
    explicit StateMachine(StateMachineConfig *config, SharedPtr<StateMachineParameterSource> parameters);
    /// Destruct.
    ~StateMachine() override;
    
    /// Set delegate to listen events. Overrides existing delegate
    void SetDelegate(StateMachineDelegate *delegate);
    /// Get existing delegate
    StateMachineDelegate *GetDelegate();
    
    /// Gets the current state name
    StateMachineState GetCurrentState() const { return stateCurrentCombined_; }
    /// Set new current state
    void SetState(const String &state);
    /// Update transitions
    void OnUpdate(float timeStep, float elapsedTime);
    /// Indicates when state machine is assigned to runner
    void OnRunnerSet(StateMachineRunner* runner);
    
private:
    /// State machine configuration
    SharedPtr<StateMachineConfig> config_ = nullptr;
    
    /// Delegate for listening this state machine transitions
    StateMachineDelegate *delegate_ = nullptr;
    
    /// Owner that is running the state machine
    StateMachineRunner* runner_ = nullptr;
    
    /// Current state config
    SharedPtr<StateMachineConfigState> stateCurrent_ = nullptr;
    /// Parameter storage. It is a separate object because it can be shared across multiple state machines 
    SharedPtr<StateMachineParameterSource> parameters_ = nullptr;
    /// Actualt current state including transition and blending information 
    StateMachineState stateCurrentCombined_;
    
    /// Transition information
    bool transition_ = false; 
    float transitionElapsedTime_ = 0; 
    SharedPtr<StateMachineConfigState> transitionStateFrom_ = nullptr;
    StateMachineConfigTransition transitionData_;
    
    /// Clears the transition data by setting default values in there 
    void ClearTranitionData();
    
    /// Do actual check for any available transitions
    void CheckTransitions();
    /// Checks one transition. Return true if transition happend, false otherwise  
    bool CheckSingleTransition();
    /// Update the blend state and report to listener
    void UpdateStateCombined();
    
public:
    // StateMachineParameterSourceListener 
    void OnParameterDidChangeValue(const String &parameterName, bool oldValue, bool newValue) override;
    
};

}
