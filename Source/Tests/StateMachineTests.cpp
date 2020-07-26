#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "testBase.h"
#include <Urho3D/Math/Vector2.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Math/Ray.h>
#include <Urho3D/Graphics/StateMachineConfig.h>
#include <Urho3D/Graphics/StateMachine.h>
#include <Urho3D/Graphics/StateMachineRunner.h>



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
        loaded_ = stateMachineConfig_->LoadJSON(*file.Get());
        
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
    MOCK_METHOD3(StateMachineDidTransit, void(StateMachine *sender, const Urho3D::String &stateFrom, const Urho3D::String &stateTo));
    MOCK_METHOD1(StateMachineDidUpdateBlendState, void(StateMachine *sender));
    
};

class MockParameterSourceListener : public StateMachineParameterSourceListener {
    
public:
    MOCK_METHOD3(OnParameterDidChangeValue, void(const String &parameterName, bool oldValue, bool newValue));
    
};

}



// Test how it was loaded
TEST_F(StateMachineTest, StateMachineConfigLoadingTest)
{
    EXPECT_EQ(loaded_, true);
    EXPECT_EQ(stateMachineConfig_->GetStatesCount(), 5);
}

// Create instance and imitate life
TEST_F(StateMachineTest, StateMachineLogicTests)
{
    SharedPtr<StateMachineParameterSource> parameterSource = SharedPtr<StateMachineParameterSource>(new StateMachineParameterSource());
    parameterSource->Set("Locked", true);
    
    SharedPtr<StateMachine> stateMachine = SharedPtr<StateMachine>(new StateMachine(stateMachineConfig_, parameterSource));
    MockDelegate delegate;
    stateMachine->SetDelegate(&delegate);
    EXPECT_EQ(stateMachine->GetDelegate(), &delegate);
    
    EXPECT_EQ(stateMachine->GetCurrentState().state1_, "Locked");
    
    {
        parameterSource->Set("abc", true);
        EXPECT_EQ(stateMachine->GetCurrentState().state1_, "Locked");
    }
    
    {
        StateMachine *s = stateMachine.Get();
        String from = "Locked";
        String to = "Closed";
        EXPECT_CALL(delegate, StateMachineDidTransit(s, from, to)).Times(testing::AtLeast(1));
        
        parameterSource->Set("Locked", false);
        EXPECT_EQ(stateMachine->GetCurrentState().state1_, "Closed");
    }
    
}

// Confirm that state machine runner works correctly
TEST_F(StateMachineTest, StateMachineRunnerTests)
{
    SharedPtr<StateMachineParameterSource> parameterSource = SharedPtr<StateMachineParameterSource>(new StateMachineParameterSource());
    parameterSource->Set("Locked", true);
    
    SharedPtr<StateMachine> stateMachine = SharedPtr<StateMachine>(new StateMachine(stateMachineConfig_, parameterSource));
    
    {
        MockDelegate delegate;
        stateMachine->SetDelegate(&delegate);
        EXPECT_EQ(stateMachine->GetDelegate(), &delegate);
        
        stateMachine->SetDelegate(nullptr);
        EXPECT_EQ(stateMachine->GetDelegate(), nullptr);
    }
    
    stateMachineRunner_->RunStateMachine(stateMachine);
    DoFrame(0.0f);
    
    {
        String from = "Locked";
        String to = "Closed";
        
        MockDelegate delegate;
        stateMachine->SetDelegate(&delegate);
        EXPECT_CALL(delegate, StateMachineDidTransit(stateMachine.Get(), from, to)).Times(testing::Exactly(1));
        parameterSource->Set("Locked", false);
        
        stateMachine->SetDelegate(nullptr);
    }
     
    {    
        auto state = stateMachine->GetCurrentState();
        EXPECT_EQ(state.state1_, "Closed");
        EXPECT_EQ(state.state2_, "");
        EXPECT_EQ(state.transition_, false);
        EXPECT_FLOAT_EQ(state.weigth1_, 1.0f);
        EXPECT_FLOAT_EQ(state.weigth2_, 0.0f);
    }
    
    // transit to open state
    {
        MockDelegate delegate;
        stateMachine->SetDelegate(&delegate);
        
        String from = "Closed";
        String to = "Opening";
        EXPECT_CALL(delegate, StateMachineDidTransit(stateMachine.Get(), from, to)).Times(testing::Exactly(1));
        parameterSource->Set("Opened", true);
        
        stateMachine->SetDelegate(nullptr);
    }
    
    {    
        auto state = stateMachine->GetCurrentState();
        EXPECT_EQ(state.state1_, "Opening");
        EXPECT_EQ(state.state2_, "Closed");
        EXPECT_EQ(state.transition_, true);
        EXPECT_FLOAT_EQ(state.weigth1_, 0.0f);
        EXPECT_FLOAT_EQ(state.weigth2_, 1.0f);
    }
    
    {
        MockDelegate delegate;
        stateMachine->SetDelegate(&delegate);
        
        EXPECT_CALL(delegate, StateMachineDidUpdateBlendState(stateMachine.Get())).Times(testing::Exactly(1));
        DoFrame(0.5f);
        
        stateMachine->SetDelegate(nullptr);
    }
    
    {    
        auto state = stateMachine->GetCurrentState();
        EXPECT_EQ(state.state1_, "Opening");
        EXPECT_EQ(state.state2_, "Closed");
        EXPECT_EQ(state.transition_, true);
        EXPECT_FLOAT_EQ(state.weigth1_, 0.5f);
        EXPECT_FLOAT_EQ(state.weigth2_, 0.5f);
    }
    
    {
        MockDelegate delegate;
        stateMachine->SetDelegate(&delegate);
        
        EXPECT_CALL(delegate, StateMachineDidUpdateBlendState(stateMachine.Get())).Times(testing::Exactly(1));
        
        String from = "Opening";
        String to = "Opened";
        EXPECT_CALL(delegate, StateMachineDidTransit(stateMachine.Get(), from, to)).Times(testing::Exactly(1));
        DoFrame(0.5f);
        
        stateMachine->SetDelegate(nullptr);
    }
    
    {    
        auto state = stateMachine->GetCurrentState();
        EXPECT_EQ(state.state1_, "Opened");
        EXPECT_EQ(state.state2_, "");
        EXPECT_EQ(state.transition_, false);
        EXPECT_FLOAT_EQ(state.weigth1_, 1.0f);
        EXPECT_FLOAT_EQ(state.weigth2_, 0.0f);
    }
    
    stateMachineRunner_->StopStateMachine(stateMachine);
}

TEST_F(StateMachineTest, StateMachineMultipleInstantTransitionTests)
{
    // Load config once again and and add instant transition
    ResourceCache *cache = context_->GetSubsystem<ResourceCache>();
    SharedPtr<File> file = cache->GetFile("Animations/House/Door1AnimController.json");
    
    SharedPtr<StateMachineConfig> stateMachineConfig = SharedPtr<StateMachineConfig>(new StateMachineConfig(context_));
    stateMachineConfig->LoadJSON(*file.Get());
    
    stateMachineConfig->AddState("Opened2");
    StateMachineConfigTransition transition("Opened", "Opened2");
    stateMachineConfig->AddTransition(transition);
    EXPECT_EQ(stateMachineConfig->GetStatesCount(), 6);
    
    SharedPtr<StateMachineParameterSource> parameterSource = SharedPtr<StateMachineParameterSource>(new StateMachineParameterSource());
    parameterSource->Set("Locked", true);    
    SharedPtr<StateMachine> stateMachine = SharedPtr<StateMachine>(new StateMachine(stateMachineConfig, parameterSource));
    
    stateMachineRunner_->RunStateMachine(stateMachine);
    
    {
        parameterSource->Set("Locked", false);
    }
     
    {    
        auto state = stateMachine->GetCurrentState();
        EXPECT_EQ(state.state1_, "Closed");
        EXPECT_EQ(state.state2_, "");
        EXPECT_EQ(state.transition_, false);
        EXPECT_FLOAT_EQ(state.weigth1_, 1.0f);
        EXPECT_FLOAT_EQ(state.weigth2_, 0.0f);
    }
    
    {
        DoFrame(1.0f);
    }
    
    {    
        auto state = stateMachine->GetCurrentState();
        EXPECT_EQ(state.state1_, "Closed");
        EXPECT_EQ(state.state2_, "");
        EXPECT_EQ(state.transition_, false);
        EXPECT_FLOAT_EQ(state.weigth1_, 1.0f);
        EXPECT_FLOAT_EQ(state.weigth2_, 0.0f);
    }
    
    // transit to open state
    {
        parameterSource->Set("Opened", true);
        DoFrame(0.5f);
    }
    
    {    
        auto state = stateMachine->GetCurrentState();
        EXPECT_EQ(state.state1_, "Opening");
        EXPECT_EQ(state.state2_, "Closed");
        EXPECT_EQ(state.transition_, true);
        EXPECT_FLOAT_EQ(state.weigth1_, 0.5f);
        EXPECT_FLOAT_EQ(state.weigth2_, 0.5f);
    }
    
    // Key thig here - 2 consecutive transitions will happen on a single frame 
    // Both transitions shoud be reported in StateMachineDidTransit
    {
        MockDelegate delegate;
        stateMachine->SetDelegate(&delegate);
        
        EXPECT_CALL(delegate, StateMachineDidUpdateBlendState(stateMachine.Get())).Times(testing::Exactly(1));
        
        String from = "Opening";
        String to = "Opened";
        EXPECT_CALL(delegate, StateMachineDidTransit(stateMachine.Get(), from, to)).Times(testing::Exactly(1));
        String from2 = "Opened";
        String to2 = "Opened2";
        EXPECT_CALL(delegate, StateMachineDidTransit(stateMachine.Get(), from2, to2)).Times(testing::Exactly(1));
        DoFrame(0.5f);
        
        stateMachine->SetDelegate(nullptr);
    }
    
    // Check that we actually transitted into Opened2
    {    
        auto state = stateMachine->GetCurrentState();
        EXPECT_EQ(state.state1_, "Opened2");
        EXPECT_EQ(state.state2_, "");
        EXPECT_EQ(state.transition_, false);
        EXPECT_FLOAT_EQ(state.weigth1_, 1.0f);
        EXPECT_FLOAT_EQ(state.weigth2_, 0.0f);
    }
    
    stateMachineRunner_->StopStateMachine(stateMachine);
}

// Confirm that parameter source will call its listener
TEST_F(StateMachineTest, StateMachineParameterSourceTests)
{    
    StateMachineParameterSource parameterSource;

    String parameterName = "someValue";
    {
        // set false 1st time - should report to listener
        MockParameterSourceListener listener;
        parameterSource.Subscribe(&listener);
        
        EXPECT_CALL(listener, OnParameterDidChangeValue(parameterName, false, false)).Times(testing::Exactly(1));
        parameterSource.Set(parameterName, false);
        
        parameterSource.Unsubscribe(&listener);
    }
    
    {
        // set false 2nd time - no report
        MockParameterSourceListener listener;
        parameterSource.Subscribe(&listener);
        
        EXPECT_CALL(listener, OnParameterDidChangeValue(parameterName, false, false)).Times(testing::Exactly(0));
        parameterSource.Set(parameterName, false);
        
        parameterSource.Unsubscribe(&listener);
    }
}

TEST_F(StateMachineTest, StateMachineSetStateTests)
{
    SharedPtr<StateMachineParameterSource> parameterSource = SharedPtr<StateMachineParameterSource>(new StateMachineParameterSource());    
    
    SharedPtr<StateMachine> stateMachine = SharedPtr<StateMachine>(new StateMachine(stateMachineConfig_, parameterSource));
    
    stateMachineRunner_->RunStateMachine(stateMachine);
    DoFrame(0.0f);
    parameterSource->Set("Locked", false);

    // go to closed state instantly
    // opened is false
    
    // set the state instantly and confirm that machine will report and start moving to closed state 
    // since opened is still false
    {
        MockDelegate delegate;
        stateMachine->SetDelegate(&delegate);
        
        String from = "Closed";
        String to = "Opened";
        EXPECT_CALL(delegate, StateMachineDidTransit(stateMachine.Get(), from, to)).Times(testing::Exactly(1));
        String from2 = "Opened";
        String to2 = "Closing";
        EXPECT_CALL(delegate, StateMachineDidTransit(stateMachine.Get(), from2, to2)).Times(testing::Exactly(1));
        
        EXPECT_CALL(delegate, StateMachineDidUpdateBlendState(stateMachine.Get())).Times(testing::Exactly(1));
        stateMachine->SetState("Opened");
        
        stateMachine->SetDelegate(nullptr);
    }
    
    {    
        auto state = stateMachine->GetCurrentState();
        EXPECT_EQ(state.state1_, "Closing");
        EXPECT_EQ(state.state2_, "Opened");
        EXPECT_EQ(state.transition_, true);
        EXPECT_FLOAT_EQ(state.weigth1_, 0.0f);
        EXPECT_FLOAT_EQ(state.weigth2_, 1.0f);
    }
    
    stateMachineRunner_->StopStateMachine(stateMachine);
}


