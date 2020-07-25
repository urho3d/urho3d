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

#include "StateMachineRunner.h"
#include "StateMachineConfig.h"
#include "StateMachine.h"


namespace Urho3D
{

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
