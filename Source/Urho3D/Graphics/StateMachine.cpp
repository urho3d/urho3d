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

bool StateMachineConfigState::AddTransition(const StateMachineConfigTransition &transition)
{
    if (transitions_.Contains(transition.name_))
    {
        return false;
    }
    
    transitions_.Insert(Pair<String, StateMachineConfigTransition>(transition.name_, transition));
    return true;
}

bool StateMachineConfigState::CanTransit(const String &transitionName)
{
    return transitions_.Contains(transitionName);
}

String StateMachineConfigState::GetName() const
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
    return state->AddTransition(transition);
}

bool StateMachineConfig::CanTransit(const String &stateName, const String &transitionName)
{
    auto stateIterator = states_.Find(stateName);
    if (stateIterator == states_.End())
    {
        return false;
    }
    
    StateMachineConfigState *state = stateIterator->second_.Get();
    return state->CanTransit(transitionName);
}

bool StateMachineConfig::LoadJSON(const JSONValue& source)
{
    auto states = source["states"].GetArray();
    for (size_t i = 0; i < states.Size(); i++) 
    {
        auto stateJson = states[i];
        SharedPtr<StateMachineConfigState> state = SharedPtr<StateMachineConfigState>(new StateMachineConfigState(stateJson["name"].GetString()));
        state->speed_ = stateJson["speed"].GetFloat();
        state->animationClip_ = stateJson["animationClip"].GetString();
        
        auto transitionsJson = stateJson["transitions"].GetArray();
        for (size_t j = 0; j < transitionsJson.Size(); j++) 
        {
            auto transitionJson = transitionsJson[j];    
            auto conditionsJson = transitionJson["conditions"].GetArray();
            if (conditionsJson.Size() == 0) {
                continue;
            }
            
            String name = conditionsJson[0]["parameter"].GetString();
            String stateFrom = state->name_;
            String stateTo = transitionJson["destinationState"].GetString();
            
            StateMachineConfigTransition transition(name, stateFrom, stateTo);
            transition.offset_ = transitionJson["offset"].GetFloat();
            transition.duration_ = transitionJson["duration"].GetFloat();
            transition.hasExitTime_ = transitionJson["duration"].GetFloat();
            transition.exitTime_ = transitionJson["exitTime"].GetFloat();
            
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
,stateCurrentCombined_(stateCurrent_->GetName(), 1.0f, "", 0.0f)
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
    
    if (transition_) 
    {
        // TODO smth?
        // cancel?
        
        // clear data
        ClearTranitionData();
    }
    
    // do the transition
    SharedPtr<StateMachineConfigState> oldState = stateCurrent_;
    StateMachineConfigTransition transitionData = stateCurrent_->transitions_[transitionName];
    stateCurrent_ = config_->states_[transitionData.stateTo_].Get();
    
    if (transitionData.duration_ > 0.001f && runner_) 
    {
        transition_ = true;
        transitionStartTime_ = runner_->GetElapsedTime();
        transitionStateFrom_ = oldState;
        transitionElapsedTime_ = 0;
        transitionData_ = transitionData;
    }
    
    UpdateStateCombined();
    
    if (delegate_)
    {
        delegate_->StateMachineDidTransit(this, oldState->GetName(), transitionName, stateCurrent_->GetName());
    }
    return true;
}

void StateMachine::OnUpdate(float time, float elapsedTime)
{
    if (!transition_) 
    {
        return;
    }
    
    transitionElapsedTime_ += elapsedTime;
    if (transitionElapsedTime_ >= transitionData_.duration_) 
    {
        // transition is done
        // clear data
        ClearTranitionData();
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
    transitionStartTime_ = 0.0f;
    transitionElapsedTime_ = 0.0f;
    transitionStateFrom_ = nullptr;
    transitionData_ = StateMachineConfigTransition();
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
    stateMachine->OnRunnerSet(this);
}

void StateMachineRunner::StopStateMachine(SharedPtr<StateMachine> stateMachine)
{
    stateMachines_.Erase(stateMachine);
    stateMachine->OnRunnerSet(nullptr);
}

void StateMachineRunner::Update(float timeStep, float elapsedTime)
{
    for (auto i = stateMachines_.Begin(); i != stateMachines_.End(); i++) 
    {
        i->first_->OnUpdate(timeStep, elapsedTime);
    }
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
    auto scene = static_cast<Scene *>(eventData[SceneUpdate::P_SCENE].GetPtr());
    Update(timeStep, scene->GetElapsedTime());
}

}
