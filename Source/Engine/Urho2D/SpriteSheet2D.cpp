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
#include "Deserializer.h"
#include "FileSystem.h"
#include "Log.h"
#include "ResourceCache.h"
#include "Serializer.h"
#include "Sprite2D.h"
#include "SpriteSheet2D.h"
#include "Texture2D.h"
#include "XMLFile.h"

#include "DebugNew.h"


namespace Urho3D
{

SpriteSheet2D::SpriteSheet2D(Context* context) :
    Resource(context)
{

}

SpriteSheet2D::~SpriteSheet2D()
{

}

void SpriteSheet2D::RegisterObject(Context* context)
{
    context->RegisterFactory<SpriteSheet2D>();
}

bool SpriteSheet2D::BeginLoad(Deserializer& source)
{
    spriteMapping_.Clear();

    SharedPtr<XMLFile> xmlFile(new XMLFile(context_));
    if(!xmlFile->Load(source))
    {
        LOGERROR("Could not load sprite sheet");
        return false;
    }

    SetMemoryUse(source.GetSize());

    XMLElement rootElem = xmlFile->GetRoot("TextureAtlas");
    if (!rootElem)
    {
        LOGERROR("Invalid sprite sheet");
        return false;
    }

    String textureFileName = rootElem.GetAttribute("imagePath");
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    texture_ = cache->GetResource<Texture2D>(GetParentPath(GetName()) + textureFileName);
    if (!texture_)
    {
        LOGERROR("Could not load texture " + GetParentPath(GetName()) + textureFileName);
        return false;
    }

    XMLElement subTextureElem = rootElem.GetChild("SubTexture");
    while (subTextureElem)
    {
        String name = subTextureElem.GetAttribute("name");

        int x = subTextureElem.GetInt("x");
        int y = subTextureElem.GetInt("y");
        int width = subTextureElem.GetInt("width");
        int height = subTextureElem.GetInt("height");
        IntRect rectangle(x, y, x + width, y + height);

        Vector2 hotSpot(0.5f, 0.5f);
        IntVector2 offset(0, 0);
        if (subTextureElem.HasAttribute("frameWidth") && subTextureElem.HasAttribute("frameHeight"))
        {
            offset.x_ = subTextureElem.GetInt("frameX");
            offset.y_ = subTextureElem.GetInt("frameY");
            int frameWidth = subTextureElem.GetInt("frameWidth");
            int frameHeight = subTextureElem.GetInt("frameHeight");
            hotSpot.x_ = ((float)offset.x_ + frameWidth / 2) / width;
            hotSpot.y_ = 1.0f - ((float)offset.y_ + frameHeight / 2) / height;
        }

        DefineSprite(name, rectangle, hotSpot, offset);

        subTextureElem = subTextureElem.GetNext("SubTexture");
    }

    return true;
}

Sprite2D* SpriteSheet2D::GetSprite(const String& name) const
{
    HashMap<String, SharedPtr<Sprite2D> >::ConstIterator i = spriteMapping_.Find(name);
    if (i == spriteMapping_.End())
        return 0;

    return i->second_;
}

void SpriteSheet2D::DefineSprite(const String& name, const IntRect& rectangle, const Vector2& hotSpot, const IntVector2& offset)
{
    if (!texture_)
        return;

    if (GetSprite(name))
        return;

    SharedPtr<Sprite2D> sprite(new Sprite2D(context_));
    sprite->SetName(name);
    sprite->SetTexture(texture_);
    sprite->SetRectangle(rectangle);
    sprite->SetHotSpot(hotSpot);
    sprite->SetOffset(offset);
    sprite->SetSpriteSheet(this);

    spriteMapping_[name] = sprite;
}

}
