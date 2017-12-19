//
// Copyright (c) 2008-2017 the Urho3D project.
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

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/RenderSurface.h>
#include <Urho3D/Graphics/RenderPath.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Technique.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>

#include "LightmapDemo.h"
#include "LightmapCreator.h"

#include <Urho3D/DebugNew.h>
//=============================================================================
//=============================================================================
URHO3D_DEFINE_APPLICATION_MAIN(LightmapDemo)

//=============================================================================
//=============================================================================
LightmapDemo::LightmapDemo(Context* context)
    : Sample(context)
    , lightingProcessComplete_(false)
    , startLightmapProcess_(false)
{
}

void LightmapDemo::Setup()
{
    engineParameters_["WindowTitle"]   = "Lightmap Demo";
    engineParameters_["LogName"]       = GetSubsystem<FileSystem>()->GetProgramDir() + "lightmap.log";
    engineParameters_["FullScreen"]    = false;
    engineParameters_["Headless"]      = false;
    engineParameters_["WindowWidth"]   = 1280; 
    engineParameters_["WindowHeight"]  = 720;
    engineParameters_["ResourcePaths"] = "Data;CoreData;Data/Lightmap;";
}

void LightmapDemo::Start()
{
    Sample::Start();

    CreateScene();

    CreateLightmapCreator();

    CreateInstructions();

    SubscribeToEvents();

    Sample::InitMouseMode(MM_RELATIVE);

    ChangeDebugHudText();
}

void LightmapDemo::CreateScene()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    scene_ = new Scene(context_);
    XMLFile *xmlLevel = cache->GetResource<XMLFile>("Lightmap/roomScene.xml");
    scene_->LoadXML(xmlLevel->GetRoot());

    scene_->CreateComponent<DebugRenderer>();

    // cam
    cameraNode_ = scene_->CreateChild("Camera");
    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(300.0f);

    // viewport
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, camera));
    GetSubsystem<Renderer>()->SetViewport(0, viewport);

    // cam pos, pitch and yaw
    Node *spawnNode = scene_->GetChild("cameraSpawn");
    cameraNode_->SetPosition(spawnNode->GetWorldPosition());
    Vector3 euAngles = spawnNode->GetWorldRotation().EulerAngles();
    pitch_ = euAngles.x_;
    yaw_ = euAngles.y_;
}

void LightmapDemo::CreateLightmapCreator()
{
    context_->RegisterSubsystem(new LightmapCreator(context_));
}

void LightmapDemo::CreateInstructions()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    // Construct new Text object, set string to display and font to use
    instructionText_ = ui->GetRoot()->CreateChild<Text>();
    instructionText_->SetText("F5 to start lightmap process");
    instructionText_->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 12);
    instructionText_->SetColor(Color::CYAN);

    // Position the text relative to the screen center
    instructionText_->SetHorizontalAlignment(HA_CENTER);
    instructionText_->SetPosition(0, 10);

    textProcessStatus_ = ui->GetRoot()->CreateChild<Text>();
    //textProcessStatus_->SetText("Use WASD keys and mouse/touch to move");
    textProcessStatus_->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 12);
    textProcessStatus_->SetColor(Color::YELLOW);
    //textProcessStatus_->SetHorizontalAlignment(HA_CENTER);
    textProcessStatus_->SetPosition(20, 50);
}

void LightmapDemo::ChangeDebugHudText()
{
    // change profiler text
    if (GetSubsystem<DebugHud>())
    {
        Text *dbgText = GetSubsystem<DebugHud>()->GetProfilerText();
        dbgText->SetColor(Color::CYAN);
        dbgText->SetTextEffect(TE_NONE);

        dbgText = GetSubsystem<DebugHud>()->GetStatsText();
        dbgText->SetColor(Color::CYAN);
        dbgText->SetTextEffect(TE_NONE);

        dbgText = GetSubsystem<DebugHud>()->GetMemoryText();
        dbgText->SetColor(Color::CYAN);
        dbgText->SetTextEffect(TE_NONE);

        dbgText = GetSubsystem<DebugHud>()->GetModeText();
        dbgText->SetColor(Color::CYAN);
        dbgText->SetTextEffect(TE_NONE);
    }
}

void LightmapDemo::MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (GetSubsystem<UI>()->GetFocusElement())
        return;

    Input* input = GetSubsystem<Input>();

    // Movement speed as world units per second
    const float MOVE_SPEED = 20.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;

    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    IntVector2 mouseMove = input->GetMouseMove();
    yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
    pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
    pitch_ = Clamp(pitch_, -90.0f, 90.0f);

    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input->GetKeyDown(KEY_W))
        cameraNode_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_S))
        cameraNode_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_A))
        cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_D))
        cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);
}

void LightmapDemo::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(LightmapDemo, HandleUpdate));
    SubscribeToEvent(E_INDIRECTLIGHTSTATUS, URHO3D_HANDLER(LightmapDemo, HandleLightingStatus));
}

void LightmapDemo::HandleLightingStatus(StringHash eventType, VariantMap& eventData)
{
    using namespace IndirectLightStatus;

    String title = eventData[P_TITLE].GetString();
    unsigned total = eventData[P_TOTAL].GetUInt();
    unsigned complete = eventData[P_COMPLETED].GetUInt();
    bool removemsg = eventData[P_REMOVEMSG].GetBool();

    if (!removemsg)
    {
        textProcessStatus_->SetText(title + ToString("%u/%u", complete, total));
    }
    else
    {
        textProcessStatus_->SetText("");
        instructionText_->SetText("F5 to process light bounce");
        lightingProcessComplete_ = true;
    }
}

void LightmapDemo::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    Input* input = GetSubsystem<Input>();

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);

    if (input->GetKeyDown(KEY_F5) && !startLightmapProcess_)
    {
        String outputPath = GetSubsystem<FileSystem>()->GetProgramDir() + String("/Data/Lightmap/BakedTextures/");
        LightmapCreator *lightmapCreator = GetSubsystem<LightmapCreator>();
        lightmapCreator->Init(scene_, outputPath);
        lightmapCreator->GenerateLightmaps();

        instructionText_->SetText("");

        startLightmapProcess_ = true;
    }

    if (input->GetKeyDown(KEY_F5) && lightingProcessComplete_)
    {
        LightmapCreator *lightmapCreator = GetSubsystem<LightmapCreator>();
        lightmapCreator->ProcessAdditionalLightBounce();
        instructionText_->SetText("");

        lightingProcessComplete_ = false;
    }

}
