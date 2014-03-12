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

#include "Precompiled.h"
#include "AnimatedSprite2D.h"
#include "Animation2D.h"
#include "CollisionShape2D.h"
#include "Drawable2D.h"
#include "ParticleEmitter2D.h"
#include "ParticleModel2D.h"
#include "PhysicsWorld2D.h"
#include "RigidBody2D.h"
#include "Sprite2D.h"
#include "SpriteSheet2D.h"
#include "StaticSprite2D.h"

#include "DebugNew.h"

namespace Urho3D
{

const char* URHO2D_CATEGORY = "Urho2D";

void RegisterUrho2DLibrary(Context* context)
{
    // Must register objects from base to derived order
    Drawable2D::RegisterObject(context);
    StaticSprite2D::RegisterObject(context);
    AnimatedSprite2D::RegisterObject(context);
    Animation2D::RegisterObject(context);
    ParticleEmitter2D::RegisterObject(context);
    ParticleModel2D::RegisterObject(context);
    Sprite2D::RegisterObject(context);
    SpriteSheet2D::RegisterObject(context);

    PhysicsWorld2D::RegisterObject(context);
    RigidBody2D::RegisterObject(context);
    CollisionShape2D::RegisterObject(context);
}

}
