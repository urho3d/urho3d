#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "testBase.h"
#include <Urho3D/Math/Vector2.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Math/Ray.h>
#include <Urho3D/Graphics/StateMachine.h>



namespace {

class StateMachineTest : public ::UrhoBaseTest
{
    
protected:
    SharedPtr<StateMachineConfig> stateMachineConfig_;
    SharedPtr<StateMachineRunner> stateMachineRunner_;
    bool loaded_ = false;
    
    void SetUp() override
    {
        UrhoBaseTest::SetUp();
        
        ResourceCache *cache = context_->GetSubsystem<ResourceCache>();
        SharedPtr<File> file = cache->GetFile("Animations/House/Door1AnimController.json");
        
        stateMachineConfig_ = SharedPtr<StateMachineConfig>(new StateMachineConfig(context_));
        loaded_ = stateMachineConfig_->LoadUnityJSON(*file.Get());
        
        stateMachineRunner_ = context_->CreateObject<StateMachineRunner>();
    }

    void TearDown() override
    {
        UrhoBaseTest::TearDown();
    }

};

class MockDelegate : public StateMachineDelegate {
    
public:
    MOCK_METHOD4(StateMachineDidTransit, void(StateMachine *sender, const String &stateFrom, const String &transitionName, const String &stateTo));
};

}



// Test how it was loaded
TEST_F(StateMachineTest, StateMachineConfigLoadingTest)
{
    ASSERT_EQ(loaded_, true);
    ASSERT_EQ(stateMachineConfig_->GetStatesCount(), 3);
}

// Test the configuration
TEST_F(StateMachineTest, StateMachineConfigLogicTests)
{
    ASSERT_EQ(stateMachineConfig_->CanTransit("Locked", "Unlock"), true);
    ASSERT_EQ(stateMachineConfig_->CanTransit("Opened", "Close"), true);
}

// Create instance and imitate life
TEST_F(StateMachineTest, StateMachineLogicTests)
{
    SharedPtr<StateMachine> stateMachine = SharedPtr<StateMachine>(new StateMachine(stateMachineConfig_, "Locked"));
    MockDelegate delegate;
    stateMachine->SetDelegate(&delegate);
    ASSERT_EQ(stateMachine->GetDelegate(), &delegate);
    
    
    
}

// Confirm that state machine runner works correctly
TEST_F(StateMachineTest, StateMachineRunnerTests)
{
    SharedPtr<StateMachine> stateMachine = SharedPtr<StateMachine>(new StateMachine(stateMachineConfig_, "Locked"));
    MockDelegate delegate;
    stateMachine->SetDelegate(&delegate);
    ASSERT_EQ(stateMachine->GetDelegate(), &delegate);
    
    stateMachineRunner_->RunStateMachine(stateMachine);
    
}
