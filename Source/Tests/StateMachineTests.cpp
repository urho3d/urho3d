#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "testBase.h"
#include <Urho3D/Math/Vector2.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Math/Ray.h>
#include <Urho3D/Graphics/StateMachine.h>



TEST_F(UrhoBaseTest, StateMachineTests)
{
    ResourceCache *cache = context_->GetSubsystem<ResourceCache>();
    SharedPtr<File> file = cache->GetFile("Animations/House/Door1AnimController.json");
    
    StateMachineConfig *stateMachineConfig = new StateMachineConfig(context_);
    stateMachineConfig->LoadJSON(*file.Get());
    int a = 10;
    ASSERT_EQ(a, 10);
}
