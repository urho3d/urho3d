//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "AnimatedSprite2D.h"
#include "AnimationSet2D.h"
#include "Application.h"
#include "Camera.h"
#include "CollisionBox2D.h"
#include "CollisionChain2D.h"
#include "CollisionCircle2D.h"
#include "CollisionPolygon2D.h"
#include "Console.h"
#include "Cursor.h"
#include "DebugHud.h"
#include "Engine.h"
#include "FileSystem.h"
#include "Font.h"
#include "Graphics.h"
#include "Input.h"
#include "InputEvents.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "RigidBody2D.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "Sprite.h"
#include "StringUtils.h"
#include "Text.h"
#include "Texture2D.h"
#include "TileMap2D.h"
#include "TileMapLayer2D.h"
#include "Timer.h"
#include "TmxFile2D.h"
#include "UI.h"
#include "XMLFile.h"

#include "Sample2D.h"


Sample2D::Sample2D(Context* context) :
    Object(context)
{
}

Sample2D::~Sample2D()
{
}

void Sample2D::CreateCollisionShapesFromTMXObjects(Node* tileMapNode, TileMapLayer2D* tileMapLayer, TileMapInfo2D info)
{
    // Create rigid body to the root node
    RigidBody2D* body = tileMapNode->CreateComponent<RigidBody2D>();
    body->SetBodyType(BT_STATIC);

    // Generate physics collision shapes and rigid bodies from the tmx file's objects located in "Physics" layer
    for (int i = 0; i < tileMapLayer->GetNumObjects(); ++i)
    {
        TileMapObject2D* tileMapObject = tileMapLayer->GetObject(i); // Get physics objects

        // Create collision shape from tmx object
        switch (tileMapObject->GetObjectType())
        {
            case OT_RECTANGLE:
            {
                CreateRectangleShape(tileMapNode, tileMapObject, tileMapObject->GetSize(), info);
            }
            break;

            case OT_ELLIPSE:
            {
                CreateCircleShape(tileMapNode, tileMapObject, tileMapObject->GetSize().x_ / 2, info); // Ellipse is built as a Circle shape as it doesn't exist in Box2D
            }
            break;

            case OT_POLYGON:
            {
                CreatePolygonShape(tileMapNode, tileMapObject);
            }
            break;

            case OT_POLYLINE:
            {
                CreatePolyLineShape(tileMapNode, tileMapObject);
            }
            break;
        }
    }
}

CollisionBox2D* Sample2D::CreateRectangleShape(Node* node, TileMapObject2D* object, Vector2 size, TileMapInfo2D info)
{
    CollisionBox2D* shape = node->CreateComponent<CollisionBox2D>();
    shape->SetSize(size);
    if (info.orientation_ == O_ORTHOGONAL)
        shape->SetCenter(object->GetPosition() + size / 2);
    else
    {
        shape->SetCenter(object->GetPosition() + Vector2(info.tileWidth_ / 2, 0.0f));
        shape->SetAngle(45.0f); // If our tile map is isometric then shape is losange
    }
    shape->SetFriction(0.8f);
    if (object->HasProperty("Friction"))
        shape->SetFriction(ToFloat(object->GetProperty("Friction")));
    return shape;
}

CollisionCircle2D* Sample2D::CreateCircleShape(Node* node, TileMapObject2D* object, float radius, TileMapInfo2D info)
{
    CollisionCircle2D* shape = node->CreateComponent<CollisionCircle2D>();
    Vector2 size = object->GetSize();
    if (info.orientation_ == O_ORTHOGONAL)
        shape->SetCenter(object->GetPosition() + size / 2);
    else
    {
        shape->SetCenter(object->GetPosition() + Vector2(info.tileWidth_ / 2, 0.0f));
    }

    shape->SetRadius(radius);
    shape->SetFriction(0.8f);
    if (object->HasProperty("Friction"))
        shape->SetFriction(ToFloat(object->GetProperty("Friction")));
    return shape;
}

CollisionPolygon2D* Sample2D::CreatePolygonShape(Node* node, TileMapObject2D* object)
{
    CollisionPolygon2D* shape = node->CreateComponent<CollisionPolygon2D>();
    int numVertices = object->GetNumPoints();
    shape->SetVertexCount(numVertices);
    for (int i = 0; i < numVertices; ++i)
        shape->SetVertex(i, object->GetPoint(i));
    shape->SetFriction(0.8f);
    if (object->HasProperty("Friction"))
        shape->SetFriction(ToFloat(object->GetProperty("Friction")));
    return shape;
}

CollisionChain2D* Sample2D::CreatePolyLineShape(Node* node, TileMapObject2D* object)
{
    CollisionChain2D* shape = node->CreateComponent<CollisionChain2D>();
    int numVertices = object->GetNumPoints();
    shape->SetVertexCount(numVertices);
    for (int i = 0; i < numVertices; ++i)
        shape->SetVertex(i, object->GetPoint(i));
    shape->SetFriction(0.8f);
    if (object->HasProperty("Friction"))
        shape->SetFriction(ToFloat(object->GetProperty("Friction")));
    return shape;
}

Node* Sample2D::CreateCharacter(Scene* scene_, TileMapInfo2D info, float friction, Vector3 position)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Node* spriteNode = scene_->CreateChild("Imp");
    spriteNode->SetPosition(position);
    spriteNode->SetScale(0.2f);
    AnimatedSprite2D* animatedSprite = spriteNode->CreateComponent<AnimatedSprite2D>();
    animatedSprite->SetAnimation(cache->GetResource<AnimationSet2D>("Urho2D/imp/imp.scml"), "idle"); // Get scml file and Play "idle" anim
    animatedSprite->SetLayer(1); // Put character over tile map
    RigidBody2D* impBody = spriteNode->CreateComponent<RigidBody2D>();
    impBody->SetBodyType(BT_DYNAMIC);
    impBody->SetAllowSleep(false);
    CollisionCircle2D* shape = spriteNode->CreateComponent<CollisionCircle2D>();
    shape->SetRadius(1.2f); // Set shape size
    shape->SetFriction(friction); // Set friction
    shape->SetRestitution(0.1f); // Bounce

    return spriteNode;
}

float Sample2D::Zoom(Camera* camera)
{
    Input* input = GetSubsystem<Input>();
    float zoom_ = camera->GetZoom();

    if (input->GetMouseMoveWheel() != 0)
        zoom_ = Clamp(zoom_ + input->GetMouseMoveWheel() * 0.1f, CAMERA_MIN_DIST, CAMERA_MAX_DIST);
        camera->SetZoom(zoom_);

    if (input->GetKeyDown(KEY_PAGEUP))
    {
        zoom_ = Clamp(zoom_ * 1.01f, CAMERA_MIN_DIST, CAMERA_MAX_DIST);
        camera->SetZoom(zoom_);
    }

    if (input->GetKeyDown(KEY_PAGEDOWN))
    {
        zoom_ = Clamp(zoom_ * 0.99f, CAMERA_MIN_DIST, CAMERA_MAX_DIST);
        camera->SetZoom(zoom_);
    }

    return zoom_;
}

void Sample2D::CreateInstructions(String text)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    // Construct new Text object, set string to display and font to use
    Text* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText(text);
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
    instructionText->SetTextAlignment(HA_CENTER); // Center rows in relation to each other

    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}
