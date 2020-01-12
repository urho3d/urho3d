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
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Terrain.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/Constraint.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RaycastVehicle.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>

#include "RaycastVehicleDemo.h"
#include "Vehicle.h"

#include <Urho3D/DebugNew.h>

const float CAMERA_DISTANCE = 10.0f;

URHO3D_DEFINE_APPLICATION_MAIN(RaycastVehicleDemo)

RaycastVehicleDemo::RaycastVehicleDemo(Context* context)
    : Sample(context)
{
    // Register factory and attributes for the Vehicle component so it can be created via CreateComponent, and loaded / saved
    Vehicle::RegisterObject(context);
}

void RaycastVehicleDemo::Start()
{
    // Execute base class startup
    Sample::Start();
    // Create static scene content
    CreateScene();
    // Create the controllable vehicle
    CreateVehicle();
    // Create the UI content
    CreateInstructions();
    // Subscribe to necessary events
    SubscribeToEvents();
    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_RELATIVE);
}

void RaycastVehicleDemo::CreateScene()
{
    auto* cache = GetSubsystem<ResourceCache>();
    scene_ = new Scene(context_);
    // Create scene subsystem components
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<PhysicsWorld>();
    // Create camera and define viewport. We will be doing load / save, so it's convenient to create the camera outside the scene,
    // so that it won't be destroyed and recreated, and we don't have to redefine the viewport on load
    cameraNode_ = new Node(context_);
    auto* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(500.0f);
    GetSubsystem<Renderer>()->SetViewport(0, new Viewport(context_, scene_, camera));
    // Create static scene content. First create a zone for ambient lighting and fog control
    Node* zoneNode = scene_->CreateChild("Zone");
    auto* zone = zoneNode->CreateComponent<Zone>();
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(300.0f);
    zone->SetFogEnd(500.0f);
    zone->SetBoundingBox(BoundingBox(-2000.0f, 2000.0f));
    // Create a directional light with cascaded shadow mapping
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.3f, -0.5f, 0.425f));
    auto* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetSpecularIntensity(0.5f);
    // Create heightmap terrain with collision
    Node* terrainNode = scene_->CreateChild("Terrain");
    terrainNode->SetPosition(Vector3::ZERO);
    auto* terrain = terrainNode->CreateComponent<Terrain>();
    terrain->SetPatchSize(64);
    terrain->SetSpacing(Vector3(3.0f, 0.1f, 3.0f)); // Spacing between vertices and vertical resolution of the height map
    terrain->SetSmoothing(true);
    terrain->SetHeightMap(cache->GetResource<Image>("Textures/HeightMap.png"));
    terrain->SetMaterial(cache->GetResource<Material>("Materials/Terrain.xml"));
    // The terrain consists of large triangles, which fits well for occlusion rendering, as a hill can occlude all
    // terrain patches and other objects behind it
    terrain->SetOccluder(true);
    auto* body = terrainNode->CreateComponent<RigidBody>();
    body->SetCollisionLayer(2); // Use layer bitmask 2 for static geometry
    auto* shape =
        terrainNode->CreateComponent<CollisionShape>();
    shape->SetTerrain();
    // Create 1000 mushrooms in the terrain. Always face outward along the terrain normal
    const unsigned NUM_MUSHROOMS = 1000;
    for (unsigned i = 0; i < NUM_MUSHROOMS; ++i)
    {
        Node* objectNode = scene_->CreateChild("Mushroom");
        Vector3 position(Random(2000.0f) - 1000.0f, 0.0f, Random(2000.0f) - 1000.0f);
        position.y_ = terrain->GetHeight(position) - 0.1f;
        objectNode->SetPosition(position);
        // Create a rotation quaternion from up vector to terrain normal
        objectNode->SetRotation(Quaternion(Vector3::UP, terrain->GetNormal(position)));
        objectNode->SetScale(3.0f);
        auto* object = objectNode->CreateComponent<StaticModel>();
        object->SetModel(cache->GetResource<Model>("Models/Mushroom.mdl"));
        object->SetMaterial(cache->GetResource<Material>("Materials/Mushroom.xml"));
        object->SetCastShadows(true);
        auto* body = objectNode->CreateComponent<RigidBody>();
        body->SetCollisionLayer(2);
        auto* shape = objectNode->CreateComponent<CollisionShape>();
        shape->SetTriangleMesh(object->GetModel(), 0);
    }
}

void RaycastVehicleDemo::CreateVehicle()
{
    Node* vehicleNode = scene_->CreateChild("Vehicle");
    vehicleNode->SetPosition(Vector3(0.0f, 25.0f, 0.0f));
    // Create the vehicle logic component
    vehicle_ = vehicleNode->CreateComponent<Vehicle>();
    // Create the rendering and physics components
    vehicle_->Init();
}

void RaycastVehicleDemo::CreateInstructions()
{
    auto* cache = GetSubsystem<ResourceCache>();
    auto* ui = GetSubsystem<UI>();
    // Construct new Text object, set string to display and font to use
    auto* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText(
        "Use WASD keys to drive, F to brake, mouse/touch to rotate camera\n"
        "F5 to save scene, F7 to load");
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
    // The text has multiple rows. Center them in relation to each other
    instructionText->SetTextAlignment(HA_CENTER);
    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}

void RaycastVehicleDemo::SubscribeToEvents()
{
    // Subscribe to Update event for setting the vehicle controls before physics simulation
    SubscribeToEvent(E_UPDATE,
                     URHO3D_HANDLER(RaycastVehicleDemo, HandleUpdate));
    // Subscribe to PostUpdate event for updating the camera position after physics simulation
    SubscribeToEvent(E_POSTUPDATE,
                     URHO3D_HANDLER(RaycastVehicleDemo,
                                    HandlePostUpdate));
    // Unsubscribe the SceneUpdate event from base class as the camera node is being controlled in HandlePostUpdate() in this sample
    UnsubscribeFromEvent(E_SCENEUPDATE);
}

void RaycastVehicleDemo::HandleUpdate(StringHash eventType,
                                 VariantMap& eventData)
{
    using namespace Update;
    auto* input = GetSubsystem<Input>();
    if (vehicle_)
    {
        auto* ui = GetSubsystem<UI>();
        // Get movement controls and assign them to the vehicle component. If UI has a focused element, clear controls
        if (!ui->GetFocusElement())
        {
            vehicle_->controls_.Set(CTRL_FORWARD, input->GetKeyDown(KEY_W));
            vehicle_->controls_.Set(CTRL_BACK, input->GetKeyDown(KEY_S));
            vehicle_->controls_.Set(CTRL_LEFT, input->GetKeyDown(KEY_A));
            vehicle_->controls_.Set(CTRL_RIGHT, input->GetKeyDown(KEY_D));
            vehicle_->controls_.Set(CTRL_BRAKE, input->GetKeyDown(KEY_F));
            // Add yaw & pitch from the mouse motion or touch input. Used only for the camera, does not affect motion
            if (touchEnabled_)
            {
                for (unsigned i = 0; i < input->GetNumTouches(); ++i)
                {
                    TouchState* state = input->GetTouch(i);
                    if (!state->touchedElement_) // Touch on empty space
                    {
                        auto* camera = cameraNode_->GetComponent<Camera>();
                        if (!camera)
                        {
                            return;
                        }
                        auto* graphics = GetSubsystem<Graphics>();
                        vehicle_->controls_.yaw_ += TOUCH_SENSITIVITY * camera->GetFov() / graphics->GetHeight() * state->delta_.x_;
                        vehicle_->controls_.pitch_ += TOUCH_SENSITIVITY * camera->GetFov() / graphics->GetHeight() * state->delta_.y_;
                    }
                }
            }
            else
            {
                vehicle_->controls_.yaw_ += (float)input->GetMouseMoveX() * YAW_SENSITIVITY;
                vehicle_->controls_.pitch_ += (float)input->GetMouseMoveY() * YAW_SENSITIVITY;
            }
            // Limit pitch
            vehicle_->controls_.pitch_ = Clamp(vehicle_->controls_.pitch_, 0.0f, 80.0f);
            // Check for loading / saving the scene
            if (input->GetKeyPress(KEY_F5))
            {
                File saveFile(context_, GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Scenes/RaycastVehicleDemo.xml",
                              FILE_WRITE);
                scene_->SaveXML(saveFile);
            }
            if (input->GetKeyPress(KEY_F7))
            {
                File loadFile(context_, GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Scenes/RaycastVehicleDemo.xml",
                              FILE_READ);
                scene_->LoadXML(loadFile);
                // After loading we have to reacquire the weak pointer to the Vehicle component, as it has been recreated
                // Simply find the vehicle's scene node by name as there's only one of them
                Node* vehicleNode = scene_->GetChild("Vehicle", true);
                if (vehicleNode)
                {
                    vehicle_ = vehicleNode->GetComponent<Vehicle>();
                }
            }
        }
        else
        {
            vehicle_->controls_.Set(CTRL_FORWARD | CTRL_BACK | CTRL_LEFT | CTRL_RIGHT | CTRL_BRAKE, false);
        }
    }
}

void RaycastVehicleDemo::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    if (!vehicle_)
    {
        return;
    }
    Node* vehicleNode = vehicle_->GetNode();
    // Physics update has completed. Position camera behind vehicle
    Quaternion dir(vehicleNode->GetRotation().YawAngle(), Vector3::UP);
    dir = dir * Quaternion(vehicle_->controls_.yaw_, Vector3::UP);
    dir = dir * Quaternion(vehicle_->controls_.pitch_, Vector3::RIGHT);
    Vector3 cameraTargetPos =
        vehicleNode->GetPosition() - dir * Vector3(0.0f, 0.0f, CAMERA_DISTANCE);
    Vector3 cameraStartPos = vehicleNode->GetPosition();
    // Raycast camera against static objects (physics collision mask 2)
    // and move it closer to the vehicle if something in between
    Ray cameraRay(cameraStartPos, cameraTargetPos - cameraStartPos);
    float cameraRayLength = (cameraTargetPos - cameraStartPos).Length();
    PhysicsRaycastResult result;
    scene_->GetComponent<PhysicsWorld>()->RaycastSingle(result, cameraRay, cameraRayLength, 2);
    if (result.body_)
    {
        cameraTargetPos = cameraStartPos + cameraRay.direction_ * (result.distance_ - 0.5f);
    }
    cameraNode_->SetPosition(cameraTargetPos);
    cameraNode_->SetRotation(dir);
}
