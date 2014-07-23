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
#include "Context.h"
#include "Sprite2D.h"
#include "SpriteSheet2D.h"
#include "Texture2D.h"

#include "DebugNew.h"

namespace Urho3D
{

Sprite2D::Sprite2D(Context* context) :
    Resource(context), 
    hotSpot_(0.5f, 0.5f),
    offset_(0, 0)
{

}

Sprite2D::~Sprite2D()
{

}

void Sprite2D::RegisterObject(Context* context)
{
    context->RegisterFactory<Sprite2D>();
}

bool Sprite2D::BeginLoad(Deserializer& source)
{
    loadTexture_ = new Texture2D(context_);
    loadTexture_->SetName(GetName());
    // In case we're async loading, only call BeginLoad() for the texture (load image but do not upload to GPU)
    if (!loadTexture_->BeginLoad(source))
    {
        loadTexture_.Reset();
        return false;
    }
    
    return true;
}

bool Sprite2D::EndLoad()
{
    // Finish loading of the texture in the main thread
    bool success = false;
    if (loadTexture_ && loadTexture_->EndLoad())
    {
        success = true;
        SetTexture(loadTexture_);
        
        if (texture_)
            SetRectangle(IntRect(0, 0, texture_->GetWidth(), texture_->GetHeight()));
    }

    loadTexture_.Reset();
    return success;
}

void Sprite2D::SetTexture(Texture2D* texture)
{
    texture_ = texture;
}

void Sprite2D::SetRectangle(const IntRect& rectangle)
{
    rectangle_ = rectangle;
}

void Sprite2D::SetHotSpot(const Vector2& hotSpot)
{
    hotSpot_ = hotSpot;
}

void Sprite2D::SetOffset(const IntVector2& offset)
{
    offset_ = offset;
}

void Sprite2D::SetSpriteSheet(SpriteSheet2D* spriteSheet)
{
    spriteSheet_ = spriteSheet;
}

}
