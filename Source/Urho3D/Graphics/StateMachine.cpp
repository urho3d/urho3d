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

#include "../DebugNew.h"



namespace Urho3D
{

StateMachineState::StateMachineState(const String &name)
:name_(name)
{}

StateMachineState::~StateMachineState()
{
    for (auto i = transitions_.Begin(); i != transitions_.End(); i++)
    {
        delete i->second_;
    }
    transitions_.Clear();
}

bool StateMachineState::AddTransition(const String &stateTo, const String &transitionName)
{
    if (transitions_.Contains(transitionName))
    {
        return false;
    }
    
    StateMachineTransition *transition = new StateMachineTransition(transitionName, name_, stateTo);
    transitions_.Insert(Pair<String, StateMachineTransition *>(transitionName, transition));
    return true;
}

bool StateMachineState::CanTransit(const String &transitionName)
{
    return transitions_.Contains(transitionName);
}



StateMachineConfig::StateMachineConfig(Context* context)
:ResourceWithMetadata(context)
{}

StateMachineConfig::~StateMachineConfig()
{
    for (auto i = states_.Begin(); i != states_.End(); i++)
    {
        delete i->second_;
    }
    states_.Clear();
}

void StateMachineConfig::RegisterObject(Context* context)
{
    context->RegisterFactory<StateMachineConfig>();
}

bool StateMachineConfig::BeginLoad(Deserializer& source)
{
    return true;
}

bool StateMachineConfig::Save(Serializer& dest) const
{
    return true;
}

bool StateMachineConfig::AddState(const String &stateName)
{
    if (states_.Contains(stateName))
    {
        return false;
    }
    
    StateMachineState *newState = new StateMachineState(stateName);
    states_.Insert(Pair<String, StateMachineState *>(stateName, newState));
    return true;
}

bool StateMachineConfig::AddTransition(const String &stateFrom, const String &stateTo, const String &transitionName)
{
    auto stateIterator = states_.Find(stateFrom);
    if (stateIterator == states_.End())
    {
        return false;
    }
    
    if (!states_.Contains(stateTo))
    {
        return false;
    }
    
    StateMachineState *state = states_[stateFrom];
    return state->AddTransition(stateTo, transitionName);
}

//bool StateMachineConfig::IsTransitionMuted(const String &transitionName)
//{}
//
//bool StateMachineConfig::SetTransitionMuted(const String &transitionName, bool value)
//{}

bool StateMachineConfig::CanTransitFromState(const String &stateName, const String &transitionName)
{
    auto stateIterator = states_.Find(stateName);
    if (stateIterator == states_.End())
    {
        return false;
    }
    
    StateMachineState *state = stateIterator->second_;
    return state->CanTransit(transitionName);
}



StateMachine::StateMachine(StateMachineConfig *config, const String &initialState)
:config_(config)
,stateCurrent_(config->states_[initialState])
{
    
}

StateMachine::~StateMachine() = default;

void StateMachine::SetDelegate(StateMachineDelegate *delegate)
{
    delegate_ = delegate;
}

StateMachineDelegate *StateMachine::GetDelegate()
{
    return delegate_;
}

bool StateMachine::Transit(const String &transitionName)
{
    if (!stateCurrent_->CanTransit(transitionName))
    {
        return false;
    }
    
    String oldStateName = stateCurrent_->name_;
    stateCurrent_ = config_->states_[stateCurrent_->transitions_[transitionName]->stateTo_];
    if (delegate_)
    {
        delegate_->StateMachineDidTransit(this, oldStateName, transitionName, stateCurrent_->name_);
    }
    return true;
}

String StateMachine::GetCurrentState() const
{
    return stateCurrent_->name_;
}

}
