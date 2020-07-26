//
// Copyright (c) 2008-2020 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "Sample.h"
#include <memory>
#include <Urho3D/Graphics/StateMachine.h>

namespace Urho3D
{

class Drawable;
class Node;
class Scene;
class Zone;
class Text3D;

class StateMachine;
class StateMachineParameterSource;

}

class GameSceneData;

/// State machine example.
/// This sample demonstrates:
///      - Loading state machine  from config
///      - Start update
///      - Listening for state machine updates
class StateMachineSample : public Sample, public Urho3D::StateMachineDelegate
{
    URHO3D_OBJECT(StateMachineSample, Sample);

public:
    /// Construct.
    explicit StateMachineSample(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

private:
    
    std::shared_ptr<GameSceneData> sceneData_;
    
    bool mouseDown_ = false;
    bool rDown_ = false;
    bool roofsShown_ = true;
    
    bool tDown_ = false;
    bool yDown_ = false;
    
    void UpdateTextLocked();
    void UpdateTextOpened();
    void UpdateTextDoorState();
    
    Text3D *textLockedValue_ = nullptr;
    Text3D *textOpenedValue_ = nullptr;
    
    Text3D *textDoorState_ = nullptr;
    SharedPtr<StateMachine> stateMachineDoor_ = nullptr;
    
    
    SharedPtr<StateMachineParameterSource> parameterSource_ = nullptr;
    
    /// Construct the scene content.
    void CreateScene();
    /// Construct user interface elements.
    void CreateUI();
    /// Set up a viewport for displaying the scene.
    void SetupViewport();
    /// Subscribe to application-wide logic update event.
    void SubscribeToEvents();
    /// Reads input and moves the camera.
    void MoveCamera(float timeStep);
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Construct an instruction text to the UI.
    void CreateInstructions();

    /// Do 
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);
    
    ///
    void SwitchRoofs();
    
public:
    /// StateMachineDelegate
    void StateMachineDidTransit(StateMachine *sender, const String &stateFrom, const String &stateTo) override;
    void StateMachineDidUpdateBlendState(StateMachine *sender) override;

};
