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
            
            String stateFrom = state->name_;
            String stateTo = transitionJson["destinationState"].GetString();
            
            StateMachineConfigTransition transition(stateFrom, stateTo);
            transition.offset_ = transitionJson["offset"].GetFloat();
            transition.duration_ = transitionJson["duration"].GetFloat();
            transition.hasExitTime_ = transitionJson["duration"].GetFloat();
            transition.exitTime_ = transitionJson["exitTime"].GetFloat();
            
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

bool StateMachineConfig::LoadUnityJSON(Deserializer& source)
{
    JSONFile jsonFile(context_);
    jsonFile.Load(source);
    
    auto root = jsonFile.GetRoot();
    if (!root.Contains("layers")) 
    {
        return false;
    }
    auto layers = root["layers"].GetArray();
    if (layers.Size() == 0) 
    {
        return false;
    }
    auto firstLayer = layers[0];
    if (!firstLayer.Contains("stateMachine")) 
    {
        return false;
    }
    auto stateMachine = firstLayer["stateMachine"];
    return LoadJSON(stateMachine);
}



bool StateMachineParameterSource::Get(const String &parameterName) const
{
    auto valueI = parameters_.Find(parameterName);
    if (valueI != parameters_.End())
    {
        return valueI->second_;
    }
    
    return false;
}

void StateMachineParameterSource::Set(const String &parameterName, bool value)
{
    bool oldValue = Get(parameterName);
    if (oldValue == value) 
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



StateMachine::StateMachine(StateMachineConfig *config, const String &initialState, SharedPtr<StateMachineParameterSource> parameters)
:config_(config)
,stateCurrent_(config->states_[initialState].Get())
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
    transitionStartTime_ = 0.0f;
    transitionElapsedTime_ = 0.0f;
    transitionStateFrom_ = nullptr;
    transitionData_ = StateMachineConfigTransition();
}

void StateMachine::CheckTransitions()
{
    // Check if any transition condition satisfied;
    int transitionIndex = -1;
    
    for (unsigned t = 0; t < stateCurrent_->transitions_.Size(); t++) 
    {
        auto &transition = stateCurrent_->transitions_[t];
        if (transition_ && transition == transitionData_) 
        {
            continue;
        }
        
        if (transition.conditions_.Size() == 0) 
        {
            transitionIndex = t;
            break;
        }
        
        int conditionIndex = -1;
        for (unsigned c = 0; c < transition.conditions_.Size(); c++) 
        {
            auto &condition = transition.conditions_[c];
            bool currentValue = parameters_->Get(condition.parameter_);
            if (condition.value_ == currentValue) 
            {
                conditionIndex = c;
                break;
            }
        }
        
        if (conditionIndex != -1) 
        {
            transitionIndex = t;
            break;
        }
    }
    
    if (transitionIndex == -1) 
    {
        return;
    }
    
    // do the transition
    SharedPtr<StateMachineConfigState> oldState = stateCurrent_;
    StateMachineConfigTransition transitionData = stateCurrent_->transitions_[transitionIndex];
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
        delegate_->StateMachineDidTransit(this, oldState->GetName(), stateCurrent_->GetName());
    }
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
