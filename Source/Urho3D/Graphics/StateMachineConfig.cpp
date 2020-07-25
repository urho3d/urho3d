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



namespace Urho3D
{

StateMachineConfigState::StateMachineConfigState(const String &name)
:name_(name)
{}

StateMachineConfigState::~StateMachineConfigState()
{
    transitions_.Clear();
}

void StateMachineConfigState::AddTransition(const StateMachineConfigTransition &transition)
{
    transitions_.Push(transition);
}

String StateMachineConfigState::GetName() const
{
    return name_;
}

bool StateMachineConfigState::HaveTransitionsFor(const String &parameterName)
{
    for (unsigned t = 0; t < transitions_.Size(); t++) 
    {
        auto &transition = transitions_[t];
        
        for (unsigned c = 0; c < transition.conditions_.Size(); c++) 
        {
            auto &condition = transition.conditions_[c];
            if (condition.parameter_ == parameterName) {
                return true;
            }
        }
    }
    return false;
}



StateMachineConfig::StateMachineConfig(Context* context)
:Resource(context)
{}

StateMachineConfig::~StateMachineConfig()
{
    states_.Clear();
}

void StateMachineConfig::RegisterObject(Context* context)
{
    context->RegisterFactory<StateMachineConfig>();
}

bool StateMachineConfig::BeginLoad(Deserializer& source) 
{
    return LoadJSON(source);
}

unsigned int StateMachineConfig::GetStatesCount() const
{
    return states_.Size();
}

bool StateMachineConfig::AddState(const String &stateName)
{
    if (states_.Contains(stateName))
    {
        return false;
    }

    states_.Insert(Pair<String, SharedPtr<StateMachineConfigState>>(stateName, SharedPtr<StateMachineConfigState>(new StateMachineConfigState(stateName))));
    return true;
}

bool StateMachineConfig::AddTransition(const StateMachineConfigTransition &transition)
{
    auto stateIterator = states_.Find(transition.stateFrom_);
    if (stateIterator == states_.End())
    {
        return false;
    }
    
    if (!states_.Contains(transition.stateTo_))
    {
        return false;
    }
    
    StateMachineConfigState *state = states_[transition.stateFrom_].Get();
    state->AddTransition(transition);
    return true;
}

bool StateMachineConfig::LoadJSON(const JSONValue& source)
{
    defaultState_ = source["defaultState"].GetString(); 
    auto states = source["states"].GetArray();
    for (size_t i = 0; i < states.Size(); i++) 
    {
        auto stateJson = states[i];
        SharedPtr<StateMachineConfigState> state = SharedPtr<StateMachineConfigState>(new StateMachineConfigState(stateJson["name"].GetString()));
        
        auto transitionsJson = stateJson["transitions"].GetArray();
        for (size_t j = 0; j < transitionsJson.Size(); j++) 
        {
            auto transitionJson = transitionsJson[j];    
            
            String stateFrom = state->name_;
            String stateTo = transitionJson["destinationState"].GetString();
            StateMachineConfigTransition transition(stateFrom, stateTo);
            transition.duration_ = transitionJson["duration"].GetFloat();
            
            auto conditionsJson = transitionJson["conditions"].GetArray();
            for (unsigned c = 0; c < conditionsJson.Size(); c++) 
            {
                auto conditionJson = conditionsJson[c];

                String name = conditionJson["parameter"].GetString();
                bool value = conditionJson["mode"].GetInt() == 1;
                
                StateMachineConfigTransitionCondition condition;
                condition.parameter_ = name;
                condition.value_ = value;
                transition.conditions_.Push(condition);
            }
            
            state->AddTransition(transition);
        }
        states_[state->name_] = state;
    }
    return true;
}

bool StateMachineConfig::LoadJSON(Deserializer& source)
{
    JSONFile jsonFile(context_);
    jsonFile.Load(source);
    return LoadJSON(jsonFile.GetRoot());
}

}
