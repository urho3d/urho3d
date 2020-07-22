#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "testBase.h"
#include <Urho3D/Math/Vector2.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Math/Ray.h>
#include <Urho3D/Graphics/StateMachine.h>



class StateMachineTest : public ::UrhoBaseTest
{
protected:
    
    StateMachineConfig *stateMachineConfig_;
    bool loaded_ = false;
    
    void SetUp() override
    {
        UrhoBaseTest::SetUp();
        
        ResourceCache *cache = context_->GetSubsystem<ResourceCache>();
        SharedPtr<File> file = cache->GetFile("Animations/House/Door1AnimController.json");
        
        stateMachineConfig_ = new StateMachineConfig(context_);
        loaded_ = stateMachineConfig_->LoadUnityJSON(*file.Get());
    }

    void TearDown() override
    {
        delete stateMachineConfig_;
        stateMachineConfig_ = nullptr;
        UrhoBaseTest::TearDown();
    }

};



TEST_F(StateMachineTest, StateMachineConfigLoadingTest)
{
    ASSERT_EQ(loaded_, true);
    ASSERT_EQ(stateMachineConfig_->GetStatesCount(), 3);
}


TEST_F(StateMachineTest, StateMachineConfigLogicTests)
{
    ASSERT_EQ(stateMachineConfig_->CanTransitFromState("Locked", "Opened"), false);
    ASSERT_EQ(stateMachineConfig_->CanTransitFromState("Locked", "Closed"), true);
}
