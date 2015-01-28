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

#pragma once

#include "Object.h"



namespace Urho3D
{

class Node;
class Scene;
class Sprite;

}

class Character2D;

// All Urho3D classes reside in namespace Urho3D
using namespace Urho3D;

const float CAMERA_MIN_DIST = 0.1f;
const float CAMERA_MAX_DIST = 6.0f;

const float MOVE_SPEED_SCALE = 1.0f; // Scaling factor based on tiles' aspect ratio

/// Convenient functions for Urho2D samples:
///    - Generate collision shapes from a tmx file objects
///    - Create Spriter Imp character
///    - Handle camera zoom using PageUp, PageDown and MouseWheel
///    - Create UI instructions
class Sample2D : public Object
{
    OBJECT(Sample2D);

public:
    /// Construct.
    Sample2D(Context* context);
    /// Destruct.
    ~Sample2D();

    /// Generate physics collision shapes from the tmx file's objects located in tileMapLayer.
    void CreateCollisionShapesFromTMXObjects(Node* tileMapNode, TileMapLayer2D* tileMapLayer, TileMapInfo2D info);
    /// Build collision shape from Tiled 'Rectangle' objects.
    CollisionBox2D* CreateRectangleShape(Node* node, TileMapObject2D* object, Vector2 size, TileMapInfo2D info);
    /// Build collision shape from Tiled 'Ellipse' objects.
    CollisionCircle2D* CreateCircleShape(Node* node, TileMapObject2D* object, float radius, TileMapInfo2D info);
    /// Build collision shape from Tiled 'Polygon' objects.
    CollisionPolygon2D* CreatePolygonShape(Node* node, TileMapObject2D* object);
    /// Build collision shape from Tiled 'Poly Line' objects.
    CollisionChain2D* CreatePolyLineShape(Node* node, TileMapObject2D* object);
    /// Create Imp Spriter character.
    Node* CreateCharacter(Scene* scene_, TileMapInfo2D info, float friction, Vector3 position);
    /// Read input and zoom the camera.
    float Zoom(Camera* camera);
    /// Create UI instructions.
    void CreateInstructions(String text);
};