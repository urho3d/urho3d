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
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Navigation/Navigable.h>
#include <Urho3D/Navigation/NavigationMesh.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>

#include "Navigation.h"

#include <Urho3D/DebugNew.h>

URHO3D_DEFINE_APPLICATION_MAIN(Navigation)

Navigation::Navigation(Context* context) :
    Sample(context),
    drawDebug_(false),
    useStreaming_(false),
    streamingDistance_(2)
{
}

void Navigation::Start()
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
    Sample::InitMouseMode(MM_RELATIVE);
}

void Navigation::CreateScene()
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

    // Create some mushrooms
    const unsigned NUM_MUSHROOMS = 100;
    for (unsigned i = 0; i < NUM_MUSHROOMS; ++i)
        CreateMushroom(Vector3(Random(90.0f) - 45.0f, 0.0f, Random(90.0f) - 45.0f));

    // Create randomly sized boxes. If boxes are big enough, make them occluders
    const unsigned NUM_BOXES = 20;
    for (unsigned i = 0; i < NUM_BOXES; ++i)
    {
        Node* boxNode = scene_->CreateChild("Box");
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

    // Create Jack node that will follow the path
    jackNode_ = scene_->CreateChild("Jack");
    jackNode_->SetPosition(Vector3(-5.0f, 0.0f, 20.0f));
    auto* modelObject = jackNode_->CreateComponent<AnimatedModel>();
    modelObject->SetModel(cache->GetResource<Model>("Models/Jack.mdl"));
    modelObject->SetMaterial(cache->GetResource<Material>("Materials/Jack.xml"));
    modelObject->SetCastShadows(true);

    // Create a NavigationMesh component to the scene root
    auto* navMesh = scene_->CreateComponent<NavigationMesh>();
    // Set small tiles to show navigation mesh streaming
    navMesh->SetTileSize(32);
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

    // Create the camera. Limit far clip distance to match the fog
    cameraNode_ = scene_->CreateChild("Camera");
    auto* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(300.0f);

    // Set an initial position for the camera scene node above the plane and looking down
    cameraNode_->SetPosition(Vector3(0.0f, 50.0f, 0.0f));
    pitch_ = 80.0f;
    cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
}

void Navigation::CreateUI()
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
    auto* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText(
        "Use WASD keys to move, RMB to rotate view\n"
        "LMB to set destination, SHIFT+LMB to teleport\n"
        "MMB or O key to add or remove obstacles\n"
        "Tab to toggle navigation mesh streaming\n"
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

void Navigation::SetupViewport()
{
    auto* renderer = GetSubsystem<Renderer>();

    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void Navigation::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Navigation, HandleUpdate));

    // Subscribe HandlePostRenderUpdate() function for processing the post-render update event, during which we request
    // debug geometry
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(Navigation, HandlePostRenderUpdate));
}

void Navigation::MoveCamera(float timeStep)
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

    // Set destination or teleport with left mouse button
    if (input->GetMouseButtonPress(MOUSEB_LEFT))
        SetPathPoint();
    // Add or remove objects with middle mouse button, then rebuild navigation mesh partially
    if (input->GetMouseButtonPress(MOUSEB_MIDDLE) || input->GetKeyPress(KEY_O))
        AddOrRemoveObject();

    // Toggle debug geometry with space
    if (input->GetKeyPress(KEY_SPACE))
        drawDebug_ = !drawDebug_;
}

void Navigation::SetPathPoint()
{
    Vector3 hitPos;
    Drawable* hitDrawable;
    auto* navMesh = scene_->GetComponent<NavigationMesh>();

    if (Raycast(250.0f, hitPos, hitDrawable))
    {
        Vector3 pathPos = navMesh->FindNearestPoint(hitPos, Vector3(1.0f, 1.0f, 1.0f));

        if (GetSubsystem<Input>()->GetQualifierDown(QUAL_SHIFT))
        {
            // Teleport
            currentPath_.Clear();
            jackNode_->LookAt(Vector3(pathPos.x_, jackNode_->GetPosition().y_, pathPos.z_), Vector3::UP);
            jackNode_->SetPosition(pathPos);
        }
        else
        {
            // Calculate path from Jack's current position to the end point
            endPos_ = pathPos;
            navMesh->FindPath(currentPath_, jackNode_->GetPosition(), endPos_);
        }
    }
}

void Navigation::AddOrRemoveObject()
{
    // Raycast and check if we hit a mushroom node. If yes, remove it, if no, create a new one
    Vector3 hitPos;
    Drawable* hitDrawable;

    if (!useStreaming_ && Raycast(250.0f, hitPos, hitDrawable))
    {
        // The part of the navigation mesh we must update, which is the world bounding box of the associated
        // drawable component
        BoundingBox updateBox;

        Node* hitNode = hitDrawable->GetNode();
        if (hitNode->GetName() == "Mushroom")
        {
            updateBox = hitDrawable->GetWorldBoundingBox();
            hitNode->Remove();
        }
        else
        {
            Node* newNode = CreateMushroom(hitPos);
            updateBox = newNode->GetComponent<StaticModel>()->GetWorldBoundingBox();
        }

        // Rebuild part of the navigation mesh, then recalculate path if applicable
        auto* navMesh = scene_->GetComponent<NavigationMesh>();
        navMesh->Build(updateBox);
        if (currentPath_.Size())
            navMesh->FindPath(currentPath_, jackNode_->GetPosition(), endPos_);
    }
}

Node* Navigation::CreateMushroom(const Vector3& pos)
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

    return mushroomNode;
}

bool Navigation::Raycast(float maxDistance, Vector3& hitPos, Drawable*& hitDrawable)
{
    hitDrawable = nullptr;

    auto* ui = GetSubsystem<UI>();
    IntVector2 pos = ui->GetCursorPosition();
    // Check the cursor is visible and there is no UI element in front of the cursor
    if (!ui->GetCursor()->IsVisible() || ui->GetElementAt(pos, true))
        return false;

    auto* graphics = GetSubsystem<Graphics>();
    auto* camera = cameraNode_->GetComponent<Camera>();
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

void Navigation::FollowPath(float timeStep)
{
    if (currentPath_.Size())
    {
        Vector3 nextWaypoint = currentPath_[0]; // NB: currentPath[0] is the next waypoint in order

        // Rotate Jack toward next waypoint to reach and move. Check for not overshooting the target
        float move = 5.0f * timeStep;
        float distance = (jackNode_->GetPosition() - nextWaypoint).Length();
        if (move > distance)
            move = distance;

        jackNode_->LookAt(nextWaypoint, Vector3::UP);
        jackNode_->Translate(Vector3::FORWARD * move);

        // Remove waypoint if reached it
        if (distance < 0.1f)
            currentPath_.Erase(0);
    }
}

void Navigation::ToggleStreaming(bool enabled)
{
    auto* navMesh = scene_->GetComponent<NavigationMesh>();
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

void Navigation::UpdateStreaming()
{
    // Center the navigation mesh at the jack
    auto* navMesh = scene_->GetComponent<NavigationMesh>();
    const IntVector2 jackTile = navMesh->GetTileIndex(jackNode_->GetWorldPosition());
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

void Navigation::SaveNavigationData()
{
    auto* navMesh = scene_->GetComponent<NavigationMesh>();
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

void Navigation::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);

    // Make Jack follow the Detour path
    FollowPath(timeStep);

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

void Navigation::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    // If draw debug mode is enabled, draw navigation mesh debug geometry
    if (drawDebug_)
        scene_->GetComponent<NavigationMesh>()->DrawDebugGeometry(true);

    if (currentPath_.Size())
    {
        // Visualize the current calculated path
        auto* debug = scene_->GetComponent<DebugRenderer>();
        debug->AddBoundingBox(BoundingBox(endPos_ - Vector3(0.1f, 0.1f, 0.1f), endPos_ + Vector3(0.1f, 0.1f, 0.1f)),
            Color(1.0f, 1.0f, 1.0f));

        // Draw the path with a small upward bias so that it does not clip into the surfaces
        Vector3 bias(0.0f, 0.05f, 0.0f);
        debug->AddLine(jackNode_->GetPosition() + bias, currentPath_[0] + bias, Color(1.0f, 1.0f, 1.0f));

        if (currentPath_.Size() > 1)
        {
            for (unsigned i = 0; i < currentPath_.Size() - 1; ++i)
                debug->AddLine(currentPath_[i] + bias, currentPath_[i + 1] + bias, Color(1.0f, 1.0f, 1.0f));
        }
    }
}
