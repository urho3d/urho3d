// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Navigation/CrowdAgent.h>
#include <Urho3D/Navigation/DynamicNavigationMesh.h>
#include <Urho3D/Navigation/Navigable.h>
#include <Urho3D/Navigation/NavigationEvents.h>
#include <Urho3D/Navigation/Obstacle.h>
#include <Urho3D/Navigation/OffMeshConnection.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>

#include "CrowdNavigation.h"

#include <Urho3D/DebugNew.h>

URHO3D_DEFINE_APPLICATION_MAIN(CrowdNavigation)

CrowdNavigation::CrowdNavigation(Context* context) :
    Sample(context)
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

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_ABSOLUTE);
}

void CrowdNavigation::CreateScene()
{
    auto* cache = GetSubsystem<ResourceCache>();

    scene_ = new Scene(context_);

    // Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    // Also create a DebugRenderer component so that we can draw debug geometry
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<DebugRenderer>();

    // Create scene node & StaticModel component for showing a static plane
    Node* planeNode = scene_->CreateChild("Plane");
    planeNode->SetScale(Vector3(100.0f, 1.0f, 100.0f));
    auto* planeObject = planeNode->CreateComponent<StaticModel>();
    planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
    planeObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml"));

    // Create a Zone component for ambient lighting & fog control
    Node* zoneNode = scene_->CreateChild("Zone");
    auto* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(100.0f);
    zone->SetFogEnd(300.0f);

    // Create a directional light to the world. Enable cascaded shadows on it
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
    auto* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    // Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));

    // Create randomly sized boxes. If boxes are big enough, make them occluders
    Node* boxGroup = scene_->CreateChild("Boxes");
    for (unsigned i = 0; i < 20; ++i)
    {
        Node* boxNode = boxGroup->CreateChild("Box");
        float size = 1.0f + Random(10.0f);
        boxNode->SetPosition(Vector3(Random(80.0f) - 40.0f, size * 0.5f, Random(80.0f) - 40.0f));
        boxNode->SetScale(size);
        auto* boxObject = boxNode->CreateComponent<StaticModel>();
        boxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
        boxObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
        boxObject->SetCastShadows(true);
        if (size >= 3.0f)
            boxObject->SetOccluder(true);
    }

    // Create a DynamicNavigationMesh component to the scene root
    auto* navMesh = scene_->CreateComponent<DynamicNavigationMesh>();
    // Set small tiles to show navigation mesh streaming
    navMesh->SetTileSize(32);
    // Enable drawing debug geometry for obstacles and off-mesh connections
    navMesh->SetDrawObstacles(true);
    navMesh->SetDrawOffMeshConnections(true);
    // Set the agent height large enough to exclude the layers under boxes
    navMesh->SetAgentHeight(10.0f);
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
    CreateBoxOffMeshConnections(navMesh, boxGroup);

    // Create some mushrooms as obstacles. Note that obstacles are non-walkable areas
    for (unsigned i = 0; i < 100; ++i)
        CreateMushroom(Vector3(Random(90.0f) - 45.0f, 0.0f, Random(90.0f) - 45.0f));

    // Create a CrowdManager component to the scene root
    auto* crowdManager = scene_->CreateComponent<CrowdManager>();
    CrowdObstacleAvoidanceParams params = crowdManager->GetObstacleAvoidanceParams(0);
    // Set the params to "High (66)" setting
    params.velBias = 0.5f;
    params.adaptiveDivs = 7;
    params.adaptiveRings = 3;
    params.adaptiveDepth = 3;
    crowdManager->SetObstacleAvoidanceParams(0, params);

    // Create some movable barrels. We create them as crowd agents, as for moving entities it is less expensive and more convenient than using obstacles
    CreateMovingBarrels(navMesh);

    // Create Jack node as crowd agent
    SpawnJack(Vector3(-5.0f, 0.0f, 20.0f), scene_->CreateChild("Jacks"));

    // Create the camera. Set far clip to match the fog. Note: now we actually create the camera node outside the scene, because
    // we want it to be unaffected by scene load / save
    cameraNode_ = new Node(context_);
    auto* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(300.0f);

    // Set an initial position for the camera scene node above the plane and looking down
    cameraNode_->SetPosition(Vector3(0.0f, 50.0f, 0.0f));
    pitch_ = 80.0f;
    cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
}

void CrowdNavigation::CreateUI()
{
    auto* cache = GetSubsystem<ResourceCache>();
    auto* ui = GetSubsystem<UI>();

    // Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will
    // control the camera, and when visible, it will point the raycast target
    auto* style = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    SharedPtr<Cursor> cursor(new Cursor(context_));
    cursor->SetStyleAuto(style);
    ui->SetCursor(cursor);

    // Set starting position of the cursor at the rendering window center
    auto* graphics = GetSubsystem<Graphics>();
    cursor->SetPosition(graphics->GetWidth() / 2, graphics->GetHeight() / 2);

    // Construct new Text object, set string to display and font to use
    instructionText_ = ui->GetRoot()->CreateChild<Text>();
    instructionText_->SetText(
        "Use WASD keys to move, RMB to rotate view\n"
        "LMB to set destination, SHIFT+LMB to spawn a Jack\n"
        "MMB or O key to add obstacles or remove obstacles/agents\n"
        "F5 to save scene, F7 to load\n"
        "Tab to toggle navigation mesh streaming\n"
        "Space to toggle debug geometry\n"
        "F12 to toggle this instruction text"
    );
    instructionText_->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
    // The text has multiple rows. Center them in relation to each other
    instructionText_->SetTextAlignment(HA_CENTER);

    // Position the text relative to the screen center
    instructionText_->SetHorizontalAlignment(HA_CENTER);
    instructionText_->SetVerticalAlignment(VA_CENTER);
    instructionText_->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}

void CrowdNavigation::SetupViewport()
{
    auto* renderer = GetSubsystem<Renderer>();

    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void CrowdNavigation::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(CrowdNavigation, HandleUpdate));

    // Subscribe HandlePostRenderUpdate() function for processing the post-render update event, during which we request debug geometry
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(CrowdNavigation, HandlePostRenderUpdate));

    // Subscribe HandleCrowdAgentFailure() function for resolving invalidation issues with agents, during which we
    // use a larger extents for finding a point on the navmesh to fix the agent's position
    SubscribeToEvent(E_CROWD_AGENT_FAILURE, URHO3D_HANDLER(CrowdNavigation, HandleCrowdAgentFailure));

    // Subscribe HandleCrowdAgentReposition() function for controlling the animation
    SubscribeToEvent(E_CROWD_AGENT_REPOSITION, URHO3D_HANDLER(CrowdNavigation, HandleCrowdAgentReposition));

    // Subscribe HandleCrowdAgentFormation() function for positioning agent into a formation
    SubscribeToEvent(E_CROWD_AGENT_FORMATION, URHO3D_HANDLER(CrowdNavigation, HandleCrowdAgentFormation));
}

void CrowdNavigation::SpawnJack(const Vector3& pos, Node* jackGroup)
{
    auto* cache = GetSubsystem<ResourceCache>();
    SharedPtr<Node> jackNode(jackGroup->CreateChild("Jack"));
    jackNode->SetPosition(pos);
    auto* modelObject = jackNode->CreateComponent<AnimatedModel>();
    modelObject->SetModel(cache->GetResource<Model>("Models/Jack.mdl"));
    modelObject->SetMaterial(cache->GetResource<Material>("Materials/Jack.xml"));
    modelObject->SetCastShadows(true);
    jackNode->CreateComponent<AnimationController>();

    // Create a CrowdAgent component and set its height and realistic max speed/acceleration. Use default radius
    auto* agent = jackNode->CreateComponent<CrowdAgent>();
    agent->SetHeight(2.0f);
    agent->SetMaxSpeed(3.0f);
    agent->SetMaxAccel(5.0f);
}

void CrowdNavigation::CreateMushroom(const Vector3& pos)
{
    auto* cache = GetSubsystem<ResourceCache>();

    Node* mushroomNode = scene_->CreateChild("Mushroom");
    mushroomNode->SetPosition(pos);
    mushroomNode->SetRotation(Quaternion(0.0f, Random(360.0f), 0.0f));
    mushroomNode->SetScale(2.0f + Random(0.5f));
    auto* mushroomObject = mushroomNode->CreateComponent<StaticModel>();
    mushroomObject->SetModel(cache->GetResource<Model>("Models/Mushroom.mdl"));
    mushroomObject->SetMaterial(cache->GetResource<Material>("Materials/Mushroom.xml"));
    mushroomObject->SetCastShadows(true);

    // Create the navigation Obstacle component and set its height & radius proportional to scale
    auto* obstacle = mushroomNode->CreateComponent<Obstacle>();
    obstacle->SetRadius(mushroomNode->GetScale().x_);
    obstacle->SetHeight(mushroomNode->GetScale().y_);
}

void CrowdNavigation::CreateBoxOffMeshConnections(DynamicNavigationMesh* navMesh, Node* boxGroup)
{
    const Vector<SharedPtr<Node>>& boxes = boxGroup->GetChildren();
    for (const SharedPtr<Node>& box : boxes)
    {
        Vector3 boxPos = box->GetPosition();
        float boxHalfSize = box->GetScale().x_ / 2;

        // Create 2 empty nodes for the start & end points of the connection. Note that order matters only when using one-way/unidirectional connection.
        Node* connectionStart = box->CreateChild("ConnectionStart");
        connectionStart->SetWorldPosition(navMesh->FindNearestPoint(boxPos + Vector3(boxHalfSize, -boxHalfSize, 0))); // Base of box
        Node* connectionEnd = connectionStart->CreateChild("ConnectionEnd");
        connectionEnd->SetWorldPosition(navMesh->FindNearestPoint(boxPos + Vector3(boxHalfSize, boxHalfSize, 0))); // Top of box

        // Create the OffMeshConnection component to one node and link the other node
        auto* connection = connectionStart->CreateComponent<OffMeshConnection>();
        connection->SetEndPoint(connectionEnd);
    }
}

void CrowdNavigation::CreateMovingBarrels(DynamicNavigationMesh* navMesh)
{
    auto* cache = GetSubsystem<ResourceCache>();
    Node* barrel = scene_->CreateChild("Barrel");
    auto* model = barrel->CreateComponent<StaticModel>();
    model->SetModel(cache->GetResource<Model>("Models/Cylinder.mdl"));
    auto* material = cache->GetResource<Material>("Materials/StoneTiled.xml");
    model->SetMaterial(material);
    material->SetTexture(TU_DIFFUSE, cache->GetResource<Texture2D>("Textures/TerrainDetail2.dds"));
    model->SetCastShadows(true);
    for (unsigned i = 0;  i < 20; ++i)
    {
        Node* clone = barrel->Clone();
        float size = 0.5f + Random(1.0f);
        clone->SetScale(Vector3(size / 1.5f, size * 2.0f, size / 1.5f));
        clone->SetPosition(navMesh->FindNearestPoint(Vector3(Random(80.0f) - 40.0f, size * 0.5f, Random(80.0f) - 40.0f)));
        auto* agent = clone->CreateComponent<CrowdAgent>();
        agent->SetRadius(clone->GetScale().x_ * 0.5f);
        agent->SetHeight(size);
        agent->SetNavigationQuality(NAVIGATIONQUALITY_LOW);
    }
    barrel->Remove();
}

void CrowdNavigation::SetPathPoint(bool spawning)
{
    Vector3 hitPos;
    Drawable* hitDrawable;

    if (Raycast(250.0f, hitPos, hitDrawable))
    {
        auto* navMesh = scene_->GetComponent<DynamicNavigationMesh>();
        Vector3 pathPos = navMesh->FindNearestPoint(hitPos, Vector3(1.0f, 1.0f, 1.0f));
        Node* jackGroup = scene_->GetChild("Jacks");
        if (spawning)
            // Spawn a jack at the target position
            SpawnJack(pathPos, jackGroup);
        else
            // Set crowd agents target position
            scene_->GetComponent<CrowdManager>()->SetCrowdTarget(pathPos, jackGroup);
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
            hitNode->Remove();
        else
            CreateMushroom(hitPos);
    }
}

bool CrowdNavigation::Raycast(float maxDistance, Vector3& hitPos, Drawable*& hitDrawable)
{
    hitDrawable = nullptr;

    auto* ui = GetSubsystem<UI>();
    IntVector2 pos = ui->GetCursorPosition();
    // Check the cursor is visible and there is no UI element in front of the cursor
    if (!ui->GetCursor()->IsVisible() || ui->GetElementAt(pos, true))
        return false;

    pos = ui->ConvertUIToSystem(pos);

    auto* graphics = GetSubsystem<Graphics>();
    auto* camera = cameraNode_->GetComponent<Camera>();
    Ray cameraRay = camera->GetScreenRay((float)pos.x_ / graphics->GetWidth(), (float)pos.y_ / graphics->GetHeight());
    // Pick only geometry objects, not eg. zones or lights, only get the first (closest) hit
    Vector<RayQueryResult> results;
    RayOctreeQuery query(results, cameraRay, RAY_TRIANGLE, maxDistance, DrawableTypes::Geometry);
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
    auto* ui = GetSubsystem<UI>();
    auto* input = GetSubsystem<Input>();
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
    if (input->GetKeyDown(KEY_W))
        cameraNode_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_S))
        cameraNode_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_A))
        cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_D))
        cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);

    // Set destination or spawn a new jack with left mouse button
    if (input->GetMouseButtonPress(MOUSEB_LEFT))
        SetPathPoint(input->GetQualifierDown(QUAL_SHIFT));
    // Add new obstacle or remove existing obstacle/agent with middle mouse button
    else if (input->GetMouseButtonPress(MOUSEB_MIDDLE) || input->GetKeyPress(KEY_O))
        AddOrRemoveObject();

    // Check for loading/saving the scene from/to the file Data/Scenes/CrowdNavigation.xml relative to the executable directory
    if (input->GetKeyPress(KEY_F5))
    {
        File saveFile(context_, GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Scenes/CrowdNavigation.xml", FILE_WRITE);
        scene_->SaveXML(saveFile);
    }
    else if (input->GetKeyPress(KEY_F7))
    {
        File loadFile(context_, GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Scenes/CrowdNavigation.xml", FILE_READ);
        scene_->LoadXML(loadFile);
    }

    // Toggle debug geometry with space
    else if (input->GetKeyPress(KEY_SPACE))
        drawDebug_ = !drawDebug_;

    // Toggle instruction text with F12
    else if (input->GetKeyPress(KEY_F12))
    {
        if (instructionText_)
            instructionText_->SetVisible(!instructionText_->IsVisible());
    }
}

void CrowdNavigation::ToggleStreaming(bool enabled)
{
    auto* navMesh = scene_->GetComponent<DynamicNavigationMesh>();
    if (enabled)
    {
        int maxTiles = (2 * streamingDistance_ + 1) * (2 * streamingDistance_ + 1);
        BoundingBox boundingBox = navMesh->GetBoundingBox();
        SaveNavigationData();
        navMesh->Allocate(boundingBox, maxTiles);
    }
    else
        navMesh->Build();
}

void CrowdNavigation::UpdateStreaming()
{
    // Center the navigation mesh at the crowd of jacks
    Vector3 averageJackPosition;
    if (Node* jackGroup = scene_->GetChild("Jacks"))
    {
        const unsigned numJacks = jackGroup->GetNumChildren();
        for (unsigned i = 0; i < numJacks; ++i)
            averageJackPosition += jackGroup->GetChild(i)->GetWorldPosition();
        averageJackPosition /= (float)numJacks;
    }

    // Compute currently loaded area
    auto* navMesh = scene_->GetComponent<DynamicNavigationMesh>();
    const IntVector2 jackTile = navMesh->GetTileIndex(averageJackPosition);
    const IntVector2 numTiles = navMesh->GetNumTiles();
    const IntVector2 beginTile = VectorMax(IntVector2::ZERO, jackTile - IntVector2::ONE * streamingDistance_);
    const IntVector2 endTile = VectorMin(jackTile + IntVector2::ONE * streamingDistance_, numTiles - IntVector2::ONE);

    // Remove tiles
    for (HashSet<IntVector2>::Iterator i = addedTiles_.Begin(); i != addedTiles_.End();)
    {
        const IntVector2 tileIdx = *i;
        if (beginTile.x_ <= tileIdx.x_ && tileIdx.x_ <= endTile.x_ && beginTile.y_ <= tileIdx.y_ && tileIdx.y_ <= endTile.y_)
            ++i;
        else
        {
            navMesh->RemoveTile(tileIdx);
            i = addedTiles_.Erase(i);
        }
    }

    // Add tiles
    for (int z = beginTile.y_; z <= endTile.y_; ++z)
        for (int x = beginTile.x_; x <= endTile.x_; ++x)
        {
            const IntVector2 tileIdx(x, z);
            if (!navMesh->HasTile(tileIdx) && tileData_.Contains(tileIdx))
            {
                addedTiles_.Insert(tileIdx);
                navMesh->AddTile(tileData_[tileIdx]);
            }
        }
}

void CrowdNavigation::SaveNavigationData()
{
    auto* navMesh = scene_->GetComponent<DynamicNavigationMesh>();
    tileData_.Clear();
    addedTiles_.Clear();
    const IntVector2 numTiles = navMesh->GetNumTiles();
    for (int z = 0; z < numTiles.y_; ++z)
        for (int x = 0; x <= numTiles.x_; ++x)
        {
            const IntVector2 tileIdx = IntVector2(x, z);
            tileData_[tileIdx] = navMesh->GetTileData(tileIdx);
        }
}

void CrowdNavigation::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);

    // Update streaming
    auto* input = GetSubsystem<Input>();
    if (input->GetKeyPress(KEY_TAB))
    {
        useStreaming_ = !useStreaming_;
        ToggleStreaming(useStreaming_);
    }
    if (useStreaming_)
        UpdateStreaming();

}

void CrowdNavigation::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    if (drawDebug_)
    {
        // Visualize navigation mesh, obstacles and off-mesh connections
        scene_->GetComponent<DynamicNavigationMesh>()->DrawDebugGeometry(true);
        // Visualize agents' path and position to reach
        scene_->GetComponent<CrowdManager>()->DrawDebugGeometry(true);
    }
}

void CrowdNavigation::HandleCrowdAgentFailure(StringHash eventType, VariantMap& eventData)
{
    using namespace CrowdAgentFailure;

    auto* node = static_cast<Node*>(eventData[P_NODE].GetPtr());
    auto agentState = (CrowdAgentState)eventData[P_CROWD_AGENT_STATE].GetI32();

    // If the agent's state is invalid, likely from spawning on the side of a box, find a point in a larger area
    if (agentState == CA_STATE_INVALID)
    {
        // Get a point on the navmesh using more generous extents
        Vector3 newPos = scene_->GetComponent<DynamicNavigationMesh>()->FindNearestPoint(node->GetPosition(), Vector3(5.0f, 5.0f, 5.0f));
        // Set the new node position, CrowdAgent component will automatically reset the state of the agent
        node->SetPosition(newPos);
    }
}

void CrowdNavigation::HandleCrowdAgentReposition(StringHash eventType, VariantMap& eventData)
{
    static const char* WALKING_ANI = "Models/Jack_Walk.ani";

    using namespace CrowdAgentReposition;

    auto* node = static_cast<Node*>(eventData[P_NODE].GetPtr());
    auto* agent = static_cast<CrowdAgent*>(eventData[P_CROWD_AGENT].GetPtr());
    Vector3 velocity = eventData[P_VELOCITY].GetVector3();
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Only Jack agent has animation controller
    auto* animCtrl = node->GetComponent<AnimationController>();
    if (animCtrl)
    {
        float speed = velocity.Length();
        if (animCtrl->IsPlaying(WALKING_ANI))
        {
            float speedRatio = speed / agent->GetMaxSpeed();
            // Face the direction of its velocity but moderate the turning speed based on the speed ratio and timeStep
            node->SetRotation(node->GetRotation().Slerp(Quaternion(Vector3::FORWARD, velocity), 10.0f * timeStep * speedRatio));
            // Throttle the animation speed based on agent speed ratio (ratio = 1 is full throttle)
            animCtrl->SetSpeed(WALKING_ANI, speedRatio * 1.5f);
        }
        else
            animCtrl->Play(WALKING_ANI, 0, true, 0.1f);

        // If speed is too low then stop the animation
        if (speed < agent->GetRadius())
            animCtrl->Stop(WALKING_ANI, 0.5f);
    }
}

void CrowdNavigation::HandleCrowdAgentFormation(StringHash eventType, VariantMap& eventData)
{
    using namespace CrowdAgentFormation;

    unsigned index = eventData[P_INDEX].GetU32();
    unsigned size = eventData[P_SIZE].GetU32();
    Vector3 position = eventData[P_POSITION].GetVector3();

    // The first agent will always move to the exact position, all other agents will select a random point nearby
    if (index)
    {
        auto* crowdManager = static_cast<CrowdManager*>(GetEventSender());
        auto* agent = static_cast<CrowdAgent*>(eventData[P_CROWD_AGENT].GetPtr());
        eventData[P_POSITION] = crowdManager->GetRandomPointInCircle(position, agent->GetRadius(), agent->GetQueryFilterType());
    }
}
