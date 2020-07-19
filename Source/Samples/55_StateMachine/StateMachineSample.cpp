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

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/RenderPath.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/StateMachine.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Slider.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Text3D.h>
#ifdef URHO3D_ANGELSCRIPT
#include <Urho3D/AngelScript/Script.h>
#endif

#include "StateMachineSample.h"
#include "StateMachineComponents.h"

#include <Urho3D/DebugNew.h>

URHO3D_DEFINE_APPLICATION_MAIN(StateMachineSample)

StateMachineSample::StateMachineSample(Context* context) :
    Sample(context)
{
    engineParameters_[EP_RESOURCE_PATHS] = "HouseScene;Data;CoreData";
}

void StateMachineSample::Start()
{
    // Execute base class startup
    Sample::Start();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateUI();
    CreateInstructions();

    // Setup the viewport for displaying the scene
    SetupViewport();

    // Subscribe to global events for camera movement
    SubscribeToEvents();
}

void StateMachineSample::CreateInstructions()
{
    auto* cache = GetSubsystem<ResourceCache>();
    auto* ui = GetSubsystem<UI>();

    // Construct new Text object, set string to display and font to use
    auto* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText("Use sliders to change Roughness and Metallic\n"
        "Hold RMB and use WASD keys and mouse to move");
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
    instructionText->SetTextAlignment(HA_CENTER);

    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}

void StateMachineSample::CreateScene()
{
    ProjectNMetaData::RegisterObject(context_);
    
    auto* cache = GetSubsystem<ResourceCache>();

#ifdef URHO3D_ANGELSCRIPT
    // The scene uses an AngelScript component for animation. Instantiate the subsystem if possible
    context_->RegisterSubsystem(new Script(context_));
#endif

    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<PhysicsWorld>();
    scene_->CreateComponent<StateMachineRunner>();
    
//    scene_->CreateComponent<DebugRenderer>();
//    DebugHud* debugHud = engine_->CreateDebugHud();
//    debugHud->SetMode(DEBUGHUD_SHOW_ALL);

    // Load scene content prepared in the editor (XML format). GetFile() returns an open file from the resource system
    // which scene.LoadXML() will read
    SharedPtr<File> file = cache->GetFile("Scenes/SampleSceneShort.xml");
    
    XMLFile xmlFile(scene_->GetContext());
    xmlFile.Load(*file.Get());
    
    Urho3D::Node *node = new Urho3D::Node(scene_->GetContext());
    node->LoadXML(xmlFile.GetRoot());
    scene_->AddChild(node);
    
    sceneData_ = std::make_shared<GameSceneData>();
    sceneData_->analyse(scene_);
    
//    auto z = scene_->CreateComponent<Zone>();
//    z->SetBoundingBox(BoundingBox(Vector3(-100, -100, -100), Vector3(1000, 1000, 1000)));
//    float c = 0.1;
//    z->SetAmbientColor(Color(c, c, c, 1));

//    Node* sphereWithDynamicMatNode = scene_->GetChild("SphereWithDynamicMat");
//    auto* staticModel = sphereWithDynamicMatNode->GetComponent<StaticModel>();
//    dynamicMaterial_ = staticModel->GetMaterial(0);

//    Node* zoneNode = scene_->GetChild("Zone");
//    zone_ = zoneNode->GetComponent<Zone>();

    // Create the camera (not included in the scene file)
    cameraNode_ = scene_->CreateChild("Camera");
    cameraNode_->CreateComponent<Camera>();

    cameraNode_->SetPosition(Vector3(120.0f, 9, 115));
    cameraNode_->LookAt(Vector3(95.0f, 2.0f, 115.0f));
    yaw_ = cameraNode_->GetRotation().YawAngle();
    pitch_ = cameraNode_->GetRotation().PitchAngle();
    
    {
        Node* text = scene_->CreateChild("roofsText");
        text->SetPosition(Vector3(110, 5.0f, 108));
        text->SetDirection(Vector3(-1, 0, -1));
        auto* textComponent = text->CreateComponent<Text3D>();
        textComponent->SetText(String("Press R to hide Roofs"));
        textComponent->SetFont(cache->GetResource<Font>("Fonts/BlueHighway.sdf"), 34);
    }
    
    {
        Node* text = scene_->CreateChild("doorText");
        text->SetPosition(Vector3(107, 2.5f, 108));
        text->SetDirection(Vector3(-1, 0, -1));
        auto* textComponent = text->CreateComponent<Text3D>();
        textComponent->SetText(String("Click on the door"));
        textComponent->SetFont(cache->GetResource<Font>("Fonts/BlueHighway.sdf"), 34);
    }
    
    
//    SharedPtr<Material> m = cache->GetResource<Material>("Techniques/PBR/PBREmissive.xml")->Clone();
//    m->SetShaderParameter("MatEmissiveColor", Variant(Vector3(1, 1, 1)));
//    m->SetShaderParameter("MatDiffColor", Variant(Vector3(1, 1, 1)));
//    boxText1->SetMaterial(m);
}

void StateMachineSample::CreateUI()
{
    auto* cache = GetSubsystem<ResourceCache>();
    auto* ui = GetSubsystem<UI>();

    // Set up global UI style into the root UI element
    auto* style = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    ui->GetRoot()->SetDefaultStyle(style);

    // Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will
    // control the camera, and when visible, it will interact with the UI
//    SharedPtr<Cursor> cursor(new Cursor(context_));
//    cursor->SetStyleAuto();
//    ui->SetCursor(cursor);
//    // Set starting position of the cursor at the rendering window center
//    auto* graphics = GetSubsystem<Graphics>();
//    cursor->SetPosition(graphics->GetWidth() / 2, graphics->GetHeight() / 2);

//    roughnessLabel_ = ui->GetRoot()->CreateChild<Text>();
//    roughnessLabel_->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
//    roughnessLabel_->SetPosition(370, 50);
//    roughnessLabel_->SetTextEffect(TE_SHADOW);
//
//    metallicLabel_ = ui->GetRoot()->CreateChild<Text>();
//    metallicLabel_->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
//    metallicLabel_->SetPosition(370, 100);
//    metallicLabel_->SetTextEffect(TE_SHADOW);
//
//    ambientLabel_ = ui->GetRoot()->CreateChild<Text>();
//    ambientLabel_->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
//    ambientLabel_->SetPosition(370, 150);
//    ambientLabel_->SetTextEffect(TE_SHADOW);

    auto* roughnessSlider = ui->GetRoot()->CreateChild<Slider>();
    roughnessSlider->SetStyleAuto();
    roughnessSlider->SetPosition(50, 50);
    roughnessSlider->SetSize(300, 20);
    roughnessSlider->SetRange(1.0f); // 0 - 1 range
    SubscribeToEvent(roughnessSlider, E_SLIDERCHANGED, URHO3D_HANDLER(StateMachineSample, HandleRoughnessSliderChanged));
    roughnessSlider->SetValue(0.5f);

    auto* metallicSlider = ui->GetRoot()->CreateChild<Slider>();
    metallicSlider->SetStyleAuto();
    metallicSlider->SetPosition(50, 100);
    metallicSlider->SetSize(300, 20);
    metallicSlider->SetRange(1.0f); // 0 - 1 range
    SubscribeToEvent(metallicSlider, E_SLIDERCHANGED, URHO3D_HANDLER(StateMachineSample, HandleMetallicSliderChanged));
    metallicSlider->SetValue(0.5f);

    auto* ambientSlider = ui->GetRoot()->CreateChild<Slider>();
    ambientSlider->SetStyleAuto();
    ambientSlider->SetPosition(50, 150);
    ambientSlider->SetSize(300, 20);
    ambientSlider->SetRange(10.0f); // 0 - 10 range
    SubscribeToEvent(ambientSlider, E_SLIDERCHANGED, URHO3D_HANDLER(StateMachineSample, HandleAmbientSliderChanged));
//    ambientSlider->SetValue(zone_->GetAmbientColor().a_);
}

void StateMachineSample::HandleRoughnessSliderChanged(StringHash eventType, VariantMap& eventData)
{
    float newValue = eventData[SliderChanged::P_VALUE].GetFloat();
//    dynamicMaterial_->SetShaderParameter("Roughness", newValue);
//    roughnessLabel_->SetText("Roughness: " + String(newValue));
}

void StateMachineSample::HandleMetallicSliderChanged(StringHash eventType, VariantMap& eventData)
{
    float newValue = eventData[SliderChanged::P_VALUE].GetFloat();
//    dynamicMaterial_->SetShaderParameter("Metallic", newValue);
//    metallicLabel_->SetText("Metallic: " + String(newValue));
}

void StateMachineSample::HandleAmbientSliderChanged(StringHash eventType, VariantMap& eventData)
{
    float newValue = eventData[SliderChanged::P_VALUE].GetFloat();
//    Color col = Color(0.0, 0.0, 0.0, newValue);
//    zone_->SetAmbientColor(col);
//    ambientLabel_->SetText("Ambient HDR Scale: " + String(zone_->GetAmbientColor().a_));
}

void StateMachineSample::SetupViewport()
{
    auto* cache = GetSubsystem<ResourceCache>();
    auto* renderer = GetSubsystem<Renderer>();

    renderer->SetHDRRendering(true);
    scene_->SetSmoothingConstant(50);

    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);

    // Add post-processing effects appropriate with the example scene
    SharedPtr<RenderPath> effectRenderPath = viewport->GetRenderPath()->Clone();
    effectRenderPath->Append(cache->GetResource<XMLFile>("PostProcess/FXAA2.xml"));
    effectRenderPath->Append(cache->GetResource<XMLFile>("PostProcess/GammaCorrection.xml"));
    effectRenderPath->Append(cache->GetResource<XMLFile>("_HouseScenePostprocess/Tonemap.xml"));
    
    // This one is very heavy
//    effectRenderPath->Append(cache->GetResource<XMLFile>("HouseScenePostprocess/BloomHDRSimple.xml"));

    viewport->SetRenderPath(effectRenderPath);
    GetSubsystem<Input>()->SetMouseVisible(true);
}

void StateMachineSample::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for camera motion
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(StateMachineSample, HandleUpdate));
}

void StateMachineSample::MoveCamera(float timeStep)
{
    // Right mouse button controls mouse cursor visibility: hide when pressed
    auto* ui = GetSubsystem<UI>();
    auto* input = GetSubsystem<Input>();

    // Do not move if the UI has a focused element
    if (ui->GetFocusElement())
        return;

    // Movement speed as world units per second
    const float MOVE_SPEED = 10.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;

    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    // Only move the camera when the cursor is hidden
    if (input->GetMouseButtonDown(MOUSEB_RIGHT))
    {
        IntVector2 mouseMove = input->GetMouseMove();
        yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
        pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
        pitch_ = Clamp(pitch_, -90.0f, 90.0f);

        // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
        cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
    }

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input->GetKeyDown(KEY_W))
        cameraNode_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_S))
        cameraNode_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_A))
        cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_D))
        cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);
    
    if (!input->GetKeyDown(KEY_R)) 
    {
        if (rDown_) {
            rDown_ = false;
            SwitchRoofs();
        }
    }
    else {
        rDown_ = true;
    }
}

void StateMachineSample::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);
    
    //
    CheckClick();
}

void StateMachineSample::CheckClick()
{
    auto* input = GetSubsystem<Input>();
    if (input->GetMouseButtonDown(MOUSEB_LEFT)) {
        mouseDown_ = true;
        return;
    }
    bool checkClick = false;
    if (mouseDown_) {
        checkClick = true;
        mouseDown_ = false;
    }
    if (!checkClick) {
        return;
    }
    
    UI* ui = scene_->GetSubsystem<UI>();
    IntVector2 pos = ui->GetCursorPosition();
    Graphics* graphics = scene_->GetSubsystem<Graphics>();
    Camera* camera = cameraNode_->GetComponent<Camera>();
    Ray cameraRay = camera->GetScreenRay((float)pos.x_ / graphics->GetWidth(), (float)pos.y_ / graphics->GetHeight());
    PODVector<RayQueryResult> raycastResults;
    RayOctreeQuery sceneQuery(raycastResults, cameraRay, RAY_TRIANGLE, 250, DRAWABLE_GEOMETRY);
    scene_->GetComponent<Octree>()->Raycast(sceneQuery);
    
    if (raycastResults.Size() == 0) 
    {
        return;
    }
    
    Node *node = nullptr;
    ProjectNMetaData *metadata = nullptr;
    float distance = 1000;
    for (unsigned i = 0; i < raycastResults.Size(); i ++) 
    {
        RayQueryResult& thisResult = raycastResults[i];
        if (!thisResult.node_) 
        {
            continue;
        }
        if (thisResult.node_ == node && distance < thisResult.distance_ + 0.01) 
        {
            continue;
        }
        
        Node *thisNode = thisResult.node_;
        ProjectNMetaData *thisMetadata = thisNode->GetComponent<ProjectNMetaData>();
        while (thisMetadata == nullptr)
        {
            Node *parentNode = thisNode->GetParent();
            if (!parentNode) {
                break;
            }
            thisNode = parentNode;
            
            thisMetadata = thisNode->GetComponent<ProjectNMetaData>();
        }
        if (!thisMetadata) 
        {
            continue;
        }
        if (thisMetadata->_isRoof && !roofsShown_) 
        {
            continue;
        }
        if (distance < thisResult.distance_ + 0.01) 
        {
            continue;
        }
        
        distance = thisResult.distance_;
        metadata = thisMetadata;
        node = thisNode;
    }
    
    if (metadata == nullptr) 
    {
        return;
    }
    
    if (metadata->_gameObjectType == ProjectNMetaData::ObjectType::Door) 
    {
        if (metadata->_gameObjectId == "door1") 
        {
            if (metadata->_gameObjectElementId == "1") 
            {
                SwitchDoorState(node);
                return;
            }
        }
    }
}

void StateMachineSample::SwitchDoorState(Urho3D::Node *node)
{
    static int a = 0;
    if (a%2 == 0) 
    {
        auto controller = node->CreateComponent<AnimationController>();
        controller->PlayExclusive("_Animations/Door1Animations/Door1Animation.ani", 0, false);
    }
    else 
    {
        auto controller = node->CreateComponent<AnimationController>();
        controller->PlayExclusive("_Animations/Door1Animations/Door1Animation.ani", 0, false);
        controller->SetSpeed("_Animations/Door1Animations/Door1Animation.ani", -1);
    }
    a++;
}

void StateMachineSample::SwitchRoofs()
{
    roofsShown_ = !roofsShown_;
    for (size_t i = 0; i < sceneData_->_roofs.size(); i++) {
        sceneData_->_roofs[i]->GetComponent<ProjectNMetaData>()->setRoofVisible(roofsShown_);
    }
}

void StateMachineSample::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    // If draw debug mode is enabled, draw viewport debug geometry, which will show eg. drawable bounding boxes and skeleton
    // bones. Note that debug geometry has to be separately requested each frame. Disable depth test so that we can see the
    // bones properly
    if (false)
    {
        GetSubsystem<Renderer>()->DrawDebugGeometry(false);
    }
    
    if (false)
    {
        // Use debug renderer to output physics world debug.
        auto debugRendererComp = scene_->GetComponent<DebugRenderer>();
        auto physicsComp = scene_->GetComponent<PhysicsWorld>();
        if(physicsComp != nullptr)
        {
            physicsComp->DrawDebugGeometry(debugRendererComp, false);
        }
    }
}
