#include "StateMachine.h"
#include "../Precompiled.h"

#include "../Container/Sort.h"
#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/Animation.h"
#include "../IO/Deserializer.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../IO/Serializer.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/XMLFile.h"
#include "../Resource/JSONFile.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"

#include "../DebugNew.h"

#include "StateMachineConfig.h"



namespace Urho3D
{

bool StateMachineParameterSource::Get(const String &parameterName, bool *exists) const
{
    auto valueI = parameters_.Find(parameterName);
    if (valueI != parameters_.End())
    {
        if (exists != nullptr) 
        {
            *exists = true;
        }
        return valueI->second_;
    }
    if (exists != nullptr) 
    {
        *exists = false;
    }
    return false;
}

void StateMachineParameterSource::Set(const String &parameterName, bool value)
{
    bool exists = false;
    bool oldValue = Get(parameterName, &exists);
    if (exists && oldValue == value) 
    {
        return;
    }
    
    parameters_[parameterName] = value;
    
    for (auto i = listeners_.Begin(); i != listeners_.End(); i++) 
    {
        i->first_->OnParameterDidChangeValue(parameterName, oldValue, value);
    }
}

void StateMachineParameterSource::Subscribe(StateMachineParameterSourceListener *listener)
{
    listeners_[listener] = true;
}

void StateMachineParameterSource::Unsubscribe(StateMachineParameterSourceListener *listener)
{
    listeners_.Erase(listener);
}



StateMachine::StateMachine(StateMachineConfig *config, SharedPtr<StateMachineParameterSource> parameters)
:config_(config)
,stateCurrent_(config->states_[config->GetDefaultState()].Get())
,parameters_(parameters)
,stateCurrentCombined_(stateCurrent_->GetName(), 1.0f, "", 0.0f)
{
    parameters_->Subscribe(this);
}

StateMachine::~StateMachine() 
{
    parameters_->Unsubscribe(this);
}

void StateMachine::SetDelegate(StateMachineDelegate *delegate)
{
    delegate_ = delegate;
}

StateMachineDelegate *StateMachine::GetDelegate()
{
    return delegate_;
}

void StateMachine::SetState(const String &state)
{
    assert(config_->states_.Contains(state));
    
    if (state == stateCurrent_->name_) 
    {
        return;
    }
    
    bool transition = transition_;
    if (transition) 
    {
        ClearTranitionData();
    }
    
    SharedPtr<StateMachineConfigState> oldState = stateCurrent_;
    stateCurrent_ = config_->states_[state].Get();
    
    if (delegate_)
    {
        delegate_->StateMachineDidTransit(this, oldState->GetName(), stateCurrent_->GetName());
    }
    
    CheckTransitions();
    UpdateStateCombined();
    
    if (delegate_)
    {
        delegate_->StateMachineDidUpdateBlendState(this);
    }
}

void StateMachine::OnUpdate(float timeStep, float elapsedTime)
{
    if (!transition_) 
    {
        return;
    }
    
    transitionElapsedTime_ += timeStep;
    if (transitionElapsedTime_ >= transitionData_.duration_) 
    {
        // transition is done
        // clear data
        ClearTranitionData();
        
        CheckTransitions();
    }
    
    UpdateStateCombined();
    
    if (delegate_)
    {
        delegate_->StateMachineDidUpdateBlendState(this);
    }
}

void StateMachine::OnRunnerSet(StateMachineRunner* runner)
{
    runner_ = runner;
}

void StateMachine::ClearTranitionData()
{
    transition_ = false;
    transitionElapsedTime_ = 0.0f;
    transitionStateFrom_ = nullptr;
    transitionData_ = StateMachineConfigTransition();
}

void StateMachine::CheckTransitions()
{
    assert(!transition_);
    
    HashMap<String, bool> states;
    
    bool check = true;
    
    // check - transition was made
    // transition_ - transition is not instant. if not instant - abort
    // states.Contains(stateCurrent_->name_) - continuous loop! abort checking
    while (check && !transition_ && !states.Contains(stateCurrent_->name_)) 
    {
        states[stateCurrent_->name_] = true;
        check = CheckSingleTransition();
    }
}

bool StateMachine::CheckSingleTransition()
{
    assert(!transition_);
    
    // Check if any transition condition satisfied;
    int transitionIndex = -1;
    
    for (unsigned t = 0; t < stateCurrent_->transitions_.Size(); t++) 
    {
        auto &transition = stateCurrent_->transitions_[t];
        if (transition_ && transition == transitionData_) 
        {
            continue;
        }
        
        bool valid = true;
        for (unsigned c = 0; c < transition.conditions_.Size(); c++) 
        {
            auto &condition = transition.conditions_[c];
            bool currentValue = parameters_->Get(condition.parameter_);
            if (condition.value_ != currentValue) 
            {
                valid = false;
                break;
            }
        }
        
        if (valid) 
        {
            transitionIndex = t;
            break;
        }
    }
    
    if (transitionIndex == -1) 
    {
        return false;
    }
    
    // do the transition
    SharedPtr<StateMachineConfigState> oldState = stateCurrent_;
    StateMachineConfigTransition transitionData = stateCurrent_->transitions_[transitionIndex];
    stateCurrent_ = config_->states_[transitionData.stateTo_].Get();
    
    if (transitionData.duration_ > 0.001f && runner_) 
    {
        transition_ = true;
        transitionStateFrom_ = oldState;
        transitionElapsedTime_ = 0;
        transitionData_ = transitionData;
    }
    
    UpdateStateCombined();
    
    if (delegate_)
    {
        delegate_->StateMachineDidTransit(this, oldState->GetName(), stateCurrent_->GetName());
    }
    
    return true;
}

void StateMachine::UpdateStateCombined()
{
    StateMachineState result(stateCurrent_->name_, 1.0f, "", 0.0f);
    if (transition_) 
    {
        result.state2_ = transitionStateFrom_->GetName();
        float duration = transitionData_.duration_;
        float actual = transitionElapsedTime_;
        float normalized = actual / duration;
        result.weigth1_ = normalized;
        result.weigth2_ = 1.0f - normalized;
        result.transition_ = true;
    }
    stateCurrentCombined_ = result;
}

void StateMachine::OnParameterDidChangeValue(const String &parameterName, bool oldValue, bool newValue) 
{
    if (!transition_) 
    {
        if (stateCurrent_->HaveTransitionsFor(parameterName)) 
        {
            CheckTransitions();
        }
    }
}

}
