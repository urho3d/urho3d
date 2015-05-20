//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include <Urho3D/Urho3D.h>

#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Math/MathDefs.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Navigation/CrowdAgent.h>
#include <Urho3D/Navigation/DetourCrowdManager.h>
#include <Urho3D/Navigation/DynamicNavigationMesh.h>
#include <Urho3D/Navigation/Navigable.h>
#include <Urho3D/Navigation/NavigationEvents.h>
#include <Urho3D/Navigation/Obstacle.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Navigation/OffMeshConnection.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/Graphics/Zone.h>

#include "CrowdNavigation.h"

#include <Urho3D/DebugNew.h>

DEFINE_APPLICATION_MAIN(CrowdNavigation)

CrowdNavigation::CrowdNavigation(Context* context) :
    Sample(context),
    drawDebug_(false)
{
}

void CrowdNavigation::Start()
{
    // Execute base class startup
    Sample::Start();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateUI();

    // Setup the viewport for displaying the scene
    SetupViewport();

    // Hook up to the frame update and render post-update events
    SubscribeToEvents();
}

void CrowdNavigation::CreateScene()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    scene_ = new Scene(context_);

    // Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    // Also create a DebugRenderer component so that we can draw debug geometry
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<DebugRenderer>();

    // Create scene node & StaticModel component for showing a static plane
    Node* planeNode = scene_->CreateChild("Plane");
    planeNode->SetScale(Vector3(100.0f, 1.0f, 100.0f));
    StaticModel* planeObject = planeNode->CreateComponent<StaticModel>();
    planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
    planeObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml"));

    // Create a Zone component for ambient lighting & fog control
    Node* zoneNode = scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(100.0f);
    zone->SetFogEnd(300.0f);

    // Create a directional light to the world. Enable cascaded shadows on it
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    // Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));

    // Create randomly sized boxes. If boxes are big enough, make them occluders
    Vector< SharedPtr<Node> > boxes;
    for (unsigned i = 0; i < 20; ++i)
    {
        Node* boxNode = scene_->CreateChild("Box");
        float size = 1.0f + Random(10.0f);
        boxNode->SetPosition(Vector3(Random(80.0f) - 40.0f, size * 0.5f, Random(80.0f) - 40.0f));
        boxNode->SetScale(size);
        StaticModel* boxObject = boxNode->CreateComponent<StaticModel>();
        boxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
        boxObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
        boxObject->SetCastShadows(true);
        if (size >= 3.0f)
        {
            boxObject->SetOccluder(true);
            boxes.Push(SharedPtr<Node>(boxNode));
        }
    }

    // Create a DynamicNavigationMesh component to the scene root
    DynamicNavigationMesh* navMesh = scene_->CreateComponent<DynamicNavigationMesh>();
    // Enable drawing debug geometry for obstacles and off-mesh connections
    navMesh->SetDrawObstacles(true);
    navMesh->SetDrawOffMeshConnections(true);
    // Set the agent height large enough to exclude the layers under boxes
    navMesh->SetAgentHeight(10.0f);
    // Set nav mesh tilesize to something reasonable
    navMesh->SetTileSize(64);
    // Set nav mesh cell height to minimum (allows agents to be grounded)
    navMesh->SetCellHeight(0.05f);
    // Create a Navigable component to the scene root. This tags all of the geometry in the scene as being part of the
    // navigation mesh. By default this is recursive, but the recursion could be turned off from Navigable
    scene_->CreateComponent<Navigable>();
    // Add padding to the navigation mesh in Y-direction so that we can add objects on top of the tallest boxes
    // in the scene and still update the mesh correctly
    navMesh->SetPadding(Vector3(0.0f, 10.0f, 0.0f));
    // Now build the navigation geometry. This will take some time. Note that the navigation mesh will prefer to use
    // physics geometry from the scene nodes, as it often is simpler, but if it can not find any (like in this example)
    // it will use renderable geometry instead
    navMesh->Build();

    // Create an off-mesh connection to each box to make them climbable (tiny boxes are skipped). A connection is built from 2 nodes.
    // Note that OffMeshConnections must be added before building the navMesh, but as we are adding Obstacles next, tiles will be automatically rebuilt.
    // Creating connections post-build here allows us to use FindNearestPoint() to procedurally set accurate positions for the connection
    CreateBoxOffMeshConnections(navMesh, boxes);

    // Create a DetourCrowdManager component to the scene root
    crowdManager_ = scene_->CreateComponent<DetourCrowdManager>();

    // Create Jack node as crowd agent
    SpawnJack(Vector3(-5.0f, 0.0f, 20.0f));

    // Create some mushrooms as obstacles. Note that obstacles are added onto an already buit navigation mesh
    for (unsigned i = 0; i < 100; ++i)
        CreateMushroom(Vector3(Random(90.0f) - 45.0f, 0.0f, Random(90.0f) - 45.0f));

    // Create the camera. Set far clip to match the fog. Note: now we actually create the camera node outside the scene, because
    // we want it to be unaffected by scene load / save
    cameraNode_ = new Node(context_);
    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(300.0f);

    // Set an initial position for the camera scene node above the plane
    cameraNode_->SetPosition(Vector3(0.0f, 5.0f, 0.0f));
}

void CrowdNavigation::CreateUI()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    // Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will
    // control the camera, and when visible, it will point the raycast target
    XMLFile* style = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    SharedPtr<Cursor> cursor(new Cursor(context_));
    cursor->SetStyleAuto(style);
    ui->SetCursor(cursor);

    // Set starting position of the cursor at the rendering window center
    Graphics* graphics = GetSubsystem<Graphics>();
    cursor->SetPosition(graphics->GetWidth() / 2, graphics->GetHeight() / 2);

    // Construct new Text object, set string to display and font to use
    Text* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText(
        "Use WASD keys to move, RMB to rotate view\n"
        "LMB to set destination, SHIFT+LMB to spawn a Jack\n"
        "MMB to add obstacles or remove obstacles/agents\n"
        "F5 to save scene, F7 to load\n"
        "Space to toggle debug geometry"
    );
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
    // The text has multiple rows. Center them in relation to each other
    instructionText->SetTextAlignment(HA_CENTER);

    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}

void CrowdNavigation::SetupViewport()
{
    Renderer* renderer = GetSubsystem<Renderer>();

    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void CrowdNavigation::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, HANDLER(CrowdNavigation, HandleUpdate));

    // Subscribe HandlePostRenderUpdate() function for processing the post-render update event, during which we request
    // debug geometry
    SubscribeToEvent(E_POSTRENDERUPDATE, HANDLER(CrowdNavigation, HandlePostRenderUpdate));

    // Subscribe HandleCrowdAgentFailure() function for resolving invalidation issues with agents, during which we
    // use a larger extents for finding a point on the navmesh to fix the agent's position
    SubscribeToEvent(E_CROWD_AGENT_FAILURE, HANDLER(CrowdNavigation, HandleCrowdAgentFailure));
}

void CrowdNavigation::SpawnJack(const Vector3& pos)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SharedPtr<Node> jackNode(scene_->CreateChild("Jack"));
    jackNode->SetPosition(pos);
    AnimatedModel* modelObject = jackNode->CreateComponent<AnimatedModel>();
    modelObject->SetModel(cache->GetResource<Model>("Models/Jack.mdl"));
    modelObject->SetMaterial(cache->GetResource<Material>("Materials/Jack.xml"));
    modelObject->SetCastShadows(true);

    // Create a CrowdAgent component and set its height (use default radius)
    CrowdAgent* agent = jackNode->CreateComponent<CrowdAgent>();
    agent->SetHeight(2.0f);
    agents_ = crowdManager_->GetActiveAgents(); // Update agents container
}

Node* CrowdNavigation::CreateMushroom(const Vector3& pos)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    Node* mushroomNode = scene_->CreateChild("Mushroom");
    mushroomNode->SetPosition(pos);
    mushroomNode->SetRotation(Quaternion(0.0f, Random(360.0f), 0.0f));
    mushroomNode->SetScale(2.0f + Random(0.5f));
    StaticModel* mushroomObject = mushroomNode->CreateComponent<StaticModel>();
    mushroomObject->SetModel(cache->GetResource<Model>("Models/Mushroom.mdl"));
    mushroomObject->SetMaterial(cache->GetResource<Material>("Materials/Mushroom.xml"));
    mushroomObject->SetCastShadows(true);

    // Create the navigation Obstacle component and set its height & radius proportional to scale
    Obstacle* obstacle = mushroomNode->CreateComponent<Obstacle>();
    obstacle->SetRadius(mushroomNode->GetScale().x_);
    obstacle->SetHeight(mushroomNode->GetScale().y_);

    return mushroomNode;
}

void CrowdNavigation::CreateBoxOffMeshConnections(DynamicNavigationMesh* navMesh, Vector< SharedPtr<Node> > boxes)
{
    for (unsigned i=0; i < boxes.Size(); ++i)
    {
        Node* box = boxes[i];
        Vector3 boxPos = box->GetPosition();
        float boxHalfSize = box->GetScale().x_ / 2;

        // Create 2 empty nodes for the start & end points of the connection. Note that order matters only when using one-way/unidirectional connection.
        Node* connectionStart = scene_->CreateChild("ConnectionStart");
        connectionStart->SetPosition(navMesh->FindNearestPoint(boxPos + Vector3(boxHalfSize, -boxHalfSize, 0))); // Base of box
        Node* connectionEnd = connectionStart->CreateChild("ConnectionEnd");
        connectionEnd->SetWorldPosition(navMesh->FindNearestPoint(boxPos + Vector3(boxHalfSize, boxHalfSize, 0))); // Top of box

        // Create the OffMeshConnection component to one node and link the other node
        OffMeshConnection* connection = connectionStart->CreateComponent<OffMeshConnection>();
        connection->SetEndPoint(connectionEnd);
    }
}

void CrowdNavigation::SetPathPoint()
{
    Vector3 hitPos;
    Drawable* hitDrawable;
    DynamicNavigationMesh* navMesh = scene_->GetComponent<DynamicNavigationMesh>();

    if (Raycast(250.0f, hitPos, hitDrawable))
    {
        Vector3 pathPos = navMesh->FindNearestPoint(hitPos, Vector3(1.0f, 1.0f, 1.0f));

        if (GetSubsystem<Input>()->GetQualifierDown(QUAL_SHIFT))
            // Spawn a jack at the target position
            SpawnJack(pathPos);
        else
        {
            // Set target position and ignit agents' move
            for (unsigned i = 0; i < agents_.Size(); ++i)
            {
                CrowdAgent* agent = agents_[i];

                // The first agent will always move to the exact position
                if (i == 0)
                    agent->SetMoveTarget(pathPos);
                else
                {
                    // Other agents will move to a random point nearby
                    Vector3 targetPos = navMesh->FindNearestPoint(pathPos + Vector3(Random(-4.5f, 4.5f), 0.0f, Random(-4.5f, 4.5f)), Vector3(1.0f, 1.0f, 1.0f));
                    agent->SetMoveTarget(targetPos);
                }
            }
        }
    }
}

void CrowdNavigation::AddOrRemoveObject()
{
    // Raycast and check if we hit a mushroom node. If yes, remove it, if no, create a new one
    Vector3 hitPos;
    Drawable* hitDrawable;

    if (Raycast(250.0f, hitPos, hitDrawable))
    {
        Node* hitNode = hitDrawable->GetNode();

        // Note that navmesh rebuild happens when the Obstacle component is removed
        if (hitNode->GetName() == "Mushroom")
            hitNode->Remove();
        else if (hitNode->GetName() == "Jack")
        {
            hitNode->Remove();
            agents_ = crowdManager_->GetActiveAgents(); // Update agents container
        }
        else
            CreateMushroom(hitPos);
    }
}

bool CrowdNavigation::Raycast(float maxDistance, Vector3& hitPos, Drawable*& hitDrawable)
{
    hitDrawable = 0;

    UI* ui = GetSubsystem<UI>();
    IntVector2 pos = ui->GetCursorPosition();
    // Check the cursor is visible and there is no UI element in front of the cursor
    if (!ui->GetCursor()->IsVisible() || ui->GetElementAt(pos, true))
        return false;

    Graphics* graphics = GetSubsystem<Graphics>();
    Camera* camera = cameraNode_->GetComponent<Camera>();
    Ray cameraRay = camera->GetScreenRay((float)pos.x_ / graphics->GetWidth(), (float)pos.y_ / graphics->GetHeight());
    // Pick only geometry objects, not eg. zones or lights, only get the first (closest) hit
    PODVector<RayQueryResult> results;
    RayOctreeQuery query(results, cameraRay, RAY_TRIANGLE, maxDistance, DRAWABLE_GEOMETRY);
    scene_->GetComponent<Octree>()->RaycastSingle(query);
    if (results.Size())
    {
        RayQueryResult& result = results[0];
        hitPos = result.position_;
        hitDrawable = result.drawable_;
        return true;
    }

    return false;
}

void CrowdNavigation::MoveCamera(float timeStep)
{
    // Right mouse button controls mouse cursor visibility: hide when pressed
    UI* ui = GetSubsystem<UI>();
    Input* input = GetSubsystem<Input>();
    ui->GetCursor()->SetVisible(!input->GetMouseButtonDown(MOUSEB_RIGHT));

    // Do not move if the UI has a focused element (the console)
    if (ui->GetFocusElement())
        return;

    // Movement speed as world units per second
    const float MOVE_SPEED = 20.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;

    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    // Only move the camera when the cursor is hidden
    if (!ui->GetCursor()->IsVisible())
    {
        IntVector2 mouseMove = input->GetMouseMove();
        yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
        pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
        pitch_ = Clamp(pitch_, -90.0f, 90.0f);

        // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
        cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
    }

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input->GetKeyDown('W'))
        cameraNode_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('S'))
        cameraNode_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('A'))
        cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('D'))
        cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);

    // Set destination or spawn a new jack with left mouse button
    if (input->GetMouseButtonPress(MOUSEB_LEFT))
        SetPathPoint();
    // Add new obstacle or remove existing obstacle/agent with middle mouse button
    if (input->GetMouseButtonPress(MOUSEB_MIDDLE))
        AddOrRemoveObject();

    // Check for loading/saving the scene from/to the file Data/Scenes/CrowdNavigation.xml relative to the executable directory
    if (input->GetKeyPress(KEY_F5))
    {
        File saveFile(context_, GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Scenes/CrowdNavigation.xml", FILE_WRITE);
        scene_->SaveXML(saveFile);
    }
    if (input->GetKeyPress(KEY_F7))
    {
        File loadFile(context_, GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Scenes/CrowdNavigation.xml", FILE_READ);
        scene_->LoadXML(loadFile);

        // After reload, reacquire crowd manager & agents
        crowdManager_ = scene_->GetComponent<DetourCrowdManager>();
        agents_ = crowdManager_->GetActiveAgents();

        // Re-enable debug draw for obstacles & off-mesh connections
        DynamicNavigationMesh* navMesh = scene_->GetComponent<DynamicNavigationMesh>();
        navMesh->SetDrawObstacles(true);
        navMesh->SetDrawOffMeshConnections(true);
    }

    // Toggle debug geometry with space
    if (input->GetKeyPress(KEY_SPACE))
        drawDebug_ = !drawDebug_;
}

void CrowdNavigation::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);

    // Make the CrowdAgents face the direction of their velocity
    for (unsigned i = 0; i < agents_.Size(); ++i)
    {
        CrowdAgent* agent = agents_[i];
        Vector3 vel = agent->GetActualVelocity();
        agent->GetNode()->SetWorldDirection(vel);
    }
}

void CrowdNavigation::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    // If draw debug mode is enabled, draw navigation debug geometry
    if (drawDebug_)
    {
        // Visualize navigation mesh and obstacles
        DynamicNavigationMesh* navMesh = scene_->GetComponent<DynamicNavigationMesh>();
        navMesh->DrawDebugGeometry(true);

        // Visualize agents' path and position to reach
        DetourCrowdManager* crowdManager = scene_->GetComponent<DetourCrowdManager>();
        crowdManager->DrawDebugGeometry(true);
    }
}

void CrowdNavigation::HandleCrowdAgentFailure(StringHash eventType, VariantMap& eventData)
{
    using namespace CrowdAgentFailure;

    Node* node = static_cast<Node*>(eventData[P_NODE].GetPtr());
    CrowdAgent* agent = static_cast<CrowdAgent*>(eventData[P_CROWD_AGENT].GetPtr());
    CrowdAgentState agentState = (CrowdAgentState)eventData[P_CROWD_AGENT_STATE].GetInt();

    // If the agent's state is invalid, likely from spawning on the side of a box, find a point in a larger area
    if (agentState == CROWD_AGENT_INVALID)
    {
        DynamicNavigationMesh* navMesh = scene_->GetComponent<DynamicNavigationMesh>();
        // Get a point on the navmesh using more generous extents
        Vector3 newPt = navMesh->FindNearestPoint(node->GetWorldPosition(), Vector3(5.0f, 5.0f, 5.0f));
        // Set the new node position, CrowdAgent component will automatically reset the state of the agent
        node->SetWorldPosition(newPt);
    }
}