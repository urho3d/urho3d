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
    float timeElapsed_ = 0.0f; 
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
    
    void DoFrame(float timeStep) 
    {
        timeElapsed_ += timeStep;
        stateMachineRunner_->Update(timeStep, timeElapsed_);
    }

};

class MockDelegate : public StateMachineDelegate {
    
public:
    MOCK_METHOD4(StateMachineDidTransit, void(StateMachine *sender, const Urho3D::String &stateFrom, const Urho3D::String &transitionName, const Urho3D::String &stateTo));
    MOCK_METHOD1(StateMachineDidUpdateBlendState, void(StateMachine *sender));
};

}



// Test how it was loaded
TEST_F(StateMachineTest, StateMachineConfigLoadingTest)
{
    EXPECT_EQ(loaded_, true);
    EXPECT_EQ(stateMachineConfig_->GetStatesCount(), 3);
}

// Test the configuration
TEST_F(StateMachineTest, StateMachineConfigLogicTests)
{
    EXPECT_EQ(stateMachineConfig_->CanTransit("Locked", "Unlock"), true);
    EXPECT_EQ(stateMachineConfig_->CanTransit("Opened", "Close"), true);
}

// Create instance and imitate life
TEST_F(StateMachineTest, StateMachineLogicTests)
{
    SharedPtr<StateMachine> stateMachine = SharedPtr<StateMachine>(new StateMachine(stateMachineConfig_, "Locked"));
    MockDelegate delegate;
    stateMachine->SetDelegate(&delegate);
    EXPECT_EQ(stateMachine->GetDelegate(), &delegate);
    
    EXPECT_EQ(stateMachine->GetCurrentState().state1_, "Locked");
    
    {
        bool success = stateMachine->Transit("abc");
        EXPECT_EQ(success, false);
        EXPECT_EQ(stateMachine->GetCurrentState().state1_, "Locked");
    }
    
    {
        StateMachine *s = stateMachine.Get();
        String from = "Locked";
        String trigger = "Unlock";
        String to = "Closed";
        EXPECT_CALL(delegate, StateMachineDidTransit(s, from, trigger, to)).Times(testing::AtLeast(1));
        
        bool success = stateMachine->Transit("Unlock");
        EXPECT_EQ(success, true);
        EXPECT_EQ(stateMachine->GetCurrentState().state1_, "Closed");
    }
    
}

// Confirm that state machine runner works correctly
TEST_F(StateMachineTest, StateMachineRunnerTests)
{
    SharedPtr<StateMachine> stateMachine = SharedPtr<StateMachine>(new StateMachine(stateMachineConfig_, "Locked"));
    MockDelegate delegate;
    stateMachine->SetDelegate(&delegate);
    EXPECT_EQ(stateMachine->GetDelegate(), &delegate);
    
    stateMachineRunner_->RunStateMachine(stateMachine);
    DoFrame(0);
    
    {
        String from = "Locked";
        String trigger = "Unlock";
        String to = "Closed";
        EXPECT_CALL(delegate, StateMachineDidTransit(stateMachine.Get(), from, trigger, to)).Times(testing::AtLeast(1));
        bool success = stateMachine->Transit("Unlock");
        EXPECT_EQ(success, true);
    }
     
    {    
        auto state = stateMachine->GetCurrentState();
        EXPECT_EQ(state.state1_, "Closed");
        EXPECT_EQ(state.state2_, "Locked");
        EXPECT_EQ(state.transition_, true);
        EXPECT_FLOAT_EQ(state.weigth1_, 0);
        EXPECT_FLOAT_EQ(state.weigth2_, 1);
    }
    
    {
        EXPECT_CALL(delegate, StateMachineDidUpdateBlendState(stateMachine.Get())).Times(testing::AtLeast(1));
    }
    DoFrame(0.125);
    
    {    
        auto state = stateMachine->GetCurrentState();
        EXPECT_EQ(state.state1_, "Closed");
        EXPECT_EQ(state.state2_, "Locked");
        EXPECT_EQ(state.transition_, true);
        EXPECT_FLOAT_EQ(state.weigth1_, 0.5);
        EXPECT_FLOAT_EQ(state.weigth2_, 0.5);
    }
    
    {
        EXPECT_CALL(delegate, StateMachineDidUpdateBlendState(stateMachine.Get())).Times(testing::AtLeast(1));
    }
    DoFrame(0.125);
    
    {    
        auto state = stateMachine->GetCurrentState();
        EXPECT_EQ(state.state1_, "Closed");
        EXPECT_EQ(state.state2_, "");
        EXPECT_EQ(state.transition_, false);
        EXPECT_FLOAT_EQ(state.weigth1_, 1);
        EXPECT_FLOAT_EQ(state.weigth2_, 0);
    }
    
}
