#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "testBase.h"
#include <Urho3D/Math/Vector2.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Math/Ray.h>
#include <Urho3D/Graphics/StateMachine.h>



TEST_F(UrhoBaseTest, StateMachineConfigLoadingTest)
{
    ResourceCache *cache = context_->GetSubsystem<ResourceCache>();
    SharedPtr<File> file = cache->GetFile("Animations/House/Door1AnimController.json");
    
    StateMachineConfig *stateMachineConfig = new StateMachineConfig(context_);
    ASSERT_EQ(stateMachineConfig->LoadUnityJSON(*file.Get()), true);
    ASSERT_EQ(stateMachineConfig->GetStatesCount(), 3);
}


TEST_F(UrhoBaseTest, StateMachineConfigLogicTests)
{
    ResourceCache *cache = context_->GetSubsystem<ResourceCache>();
    SharedPtr<File> file = cache->GetFile("Animations/House/Door1AnimController.json");
    
    StateMachineConfig *stateMachineConfig = new StateMachineConfig(context_);
    stateMachineConfig->LoadUnityJSON(*file.Get());
    
    ASSERT_EQ(stateMachineConfig->CanTransitFromState("Locked", "Opened"), false);
    ASSERT_EQ(stateMachineConfig->CanTransitFromState("Locked", "Closed"), true);
}
