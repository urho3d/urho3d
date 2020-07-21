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
#include "../Scene/SceneEvents.h"

#include "../DebugNew.h"



namespace Urho3D
{

StateMachineState::StateMachineState(const String &name)
:name_(name)
{}

StateMachineState::~StateMachineState()
{
    transitions_.Clear();
}

bool StateMachineState::AddTransition(const StateMachineTransition &transition)
{
    if (transitions_.Contains(transition.name_))
    {
        return false;
    }
    
    transitions_.Insert(Pair<String, StateMachineTransition>(transition.name_, transition));
    return true;
}

bool StateMachineState::CanTransit(const String &transitionName)
{
    return transitions_.Contains(transitionName);
}

String StateMachineState::GetName() const
{
    return name_;
}



StateMachineConfig::StateMachineConfig(Context* context)
:ResourceWithMetadata(context)
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

    
    states_.Insert(Pair<String, SharedPtr<StateMachineState>>(stateName, SharedPtr<StateMachineState>(new StateMachineState(stateName))));
    return true;
}

bool StateMachineConfig::AddTransition(const StateMachineTransition &transition)
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
    
    StateMachineState *state = states_[transition.stateFrom_].Get();
    return state->AddTransition(transition);
}

bool StateMachineConfig::CanTransitFromState(const String &stateName, const String &transitionName)
{
    auto stateIterator = states_.Find(stateName);
    if (stateIterator == states_.End())
    {
        return false;
    }
    
    StateMachineState *state = stateIterator->second_.Get();
    return state->CanTransit(transitionName);
}

bool StateMachineConfig::LoadJSON(const JSONValue& source)
{
    return true;
}

bool StateMachineConfig::LoadJSON(Deserializer& source)
{
    JSONFile jsonFile(context_);
    jsonFile.Load(source);
    return LoadJSON(jsonFile.GetRoot());
}

bool StateMachineConfig::LoadUnityJSON(Deserializer& source)
{
    JSONFile jsonFile(context_);
    jsonFile.Load(source);
    
    auto root = jsonFile.GetRoot();
    if (!root.Contains("layers")) {
        return false;
    }
    auto layers = root["layers"].GetArray();
    if (layers.Size() == 0) {
        return false;
    }
    auto firstLayer = layers[0];
    if (!firstLayer.Contains("stateMachine")) {
        return false;
    }
    auto stateMachine = firstLayer["stateMachine"];
    return LoadJSON(stateMachine);
}

unsigned int StateMachineConfig::GetStatesCount() const
{
    return states_.Size();
}



StateMachine::StateMachine(StateMachineConfig *config, const String &initialState)
:config_(config)
,stateCurrent_(config->states_[initialState].Get())
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
    
    String oldStateName = stateCurrent_->GetName();
    stateCurrent_ = config_->states_[stateCurrent_->transitions_[transitionName].stateTo_].Get();
    if (delegate_)
    {
        delegate_->StateMachineDidTransit(this, oldStateName, transitionName, stateCurrent_->GetName());
    }
    return true;
}

String StateMachine::GetCurrentState() const
{
    return stateCurrent_->name_;
}

void StateMachine::OnUpdate(float time)
{}



StateMachineRunner::StateMachineRunner(Context* context)
:Component(context)
{}

StateMachineRunner::~StateMachineRunner() = default;
    
void StateMachineRunner::RegisterObject(Context* context)
{
    context->RegisterFactory<StateMachineRunner>();
}
    
void StateMachineRunner::RunStateMachine(SharedPtr<StateMachine> stateMachine)
{
    stateMachines_[stateMachine] = true;
}

void StateMachineRunner::StopStateMachine(SharedPtr<StateMachine> stateMachine)
{
    stateMachines_.Erase(stateMachine);
}   

void StateMachineRunner::OnSceneSet(Scene* scene) 
{
    Component::OnSceneSet(scene);
    
    if (scene) {
        // Subscribe scene update event
        SubscribeToEvent(E_SCENEUPDATE, URHO3D_HANDLER(StateMachineRunner, HandleSceneUpdate));
    }
    else {
        UnsubscribeFromEvent(E_SCENEUPDATE);
    }
}

void StateMachineRunner::HandleSceneUpdate(StringHash eventType, VariantMap& eventData)
{
    auto timeStep = eventData[SceneUpdate::P_TIMESTEP].GetFloat();
    for (auto i = stateMachines_.Begin(); i != stateMachines_.End(); i++) 
    {
        i->first_->OnUpdate(timeStep);
    }
}

}
