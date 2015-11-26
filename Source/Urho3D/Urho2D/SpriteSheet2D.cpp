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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Graphics/Texture2D.h"
#include "../IO/Deserializer.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../Resource/PListFile.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/XMLFile.h"
#include "../Urho2D/Sprite2D.h"
#include "../Urho2D/SpriteSheet2D.h"

#include "../DebugNew.h"

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
    if (GetName().Empty())
        SetName(source.GetName());

    loadTextureName_.Clear();
    spriteMapping_.Clear();

    String extension = GetExtension(source.GetName());
    if (extension == ".plist")
        return BeginLoadFromPListFile(source);

    if (extension == ".xml")
        return BeginLoadFromXMLFile(source);

    URHO3D_LOGERROR("Unsupported file type");
    return false;
}

bool SpriteSheet2D::EndLoad()
{
    if (loadPListFile_)
        return EndLoadFromPListFile();

    if (loadXMLFile_)
        return EndLoadFromXMLFile();

    return false;
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

bool SpriteSheet2D::BeginLoadFromPListFile(Deserializer& source)
{
    loadPListFile_ = new PListFile(context_);
    if (!loadPListFile_->Load(source))
    {
        URHO3D_LOGERROR("Could not load sprite sheet");
        loadPListFile_.Reset();
        return false;
    }

    SetMemoryUse(source.GetSize());

    const PListValueMap& root = loadPListFile_->GetRoot();
    const PListValueMap& metadata = root["metadata"]->GetValueMap();
    const String& textureFileName = metadata["realTextureFileName"]->GetString();

    // If we're async loading, request the texture now. Finish during EndLoad().
    loadTextureName_ = GetParentPath(GetName()) + textureFileName;
    if (GetAsyncLoadState() == ASYNC_LOADING)
        GetSubsystem<ResourceCache>()->BackgroundLoadResource<Texture2D>(loadTextureName_, true, this);

    return true;
}

bool SpriteSheet2D::EndLoadFromPListFile()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    texture_ = cache->GetResource<Texture2D>(loadTextureName_);
    if (!texture_)
    {
        URHO3D_LOGERROR("Could not load texture " + loadTextureName_);
        loadXMLFile_.Reset();
        loadTextureName_.Clear();
        return false;
    }

    const PListValueMap& root = loadPListFile_->GetRoot();
    const PListValueMap& frames = root["frames"]->GetValueMap();
    for (PListValueMap::ConstIterator i = frames.Begin(); i != frames.End(); ++i)
    {
        String name = i->first_.Split('.')[0];

        const PListValueMap& frameInfo = i->second_.GetValueMap();
        if (frameInfo["rotated"]->GetBool())
        {
            URHO3D_LOGWARNING("Rotated sprite is not support now");
            continue;
        }

        IntRect rectangle = frameInfo["frame"]->GetIntRect();
        Vector2 hotSpot(0.5f, 0.5f);
        IntVector2 offset(0, 0);

        IntRect sourceColorRect = frameInfo["sourceColorRect"]->GetIntRect();
        if (sourceColorRect.left_ != 0 && sourceColorRect.top_ != 0)
        {
            offset.x_ = -sourceColorRect.left_;
            offset.y_ = -sourceColorRect.top_;

            IntVector2 sourceSize = frameInfo["sourceSize"]->GetIntVector2();
            hotSpot.x_ = ((float)offset.x_ + sourceSize.x_ / 2) / rectangle.Width();
            hotSpot.y_ = 1.0f - ((float)offset.y_ + sourceSize.y_ / 2) / rectangle.Height();
        }

        DefineSprite(name, rectangle, hotSpot, offset);
    }

    loadXMLFile_.Reset();
    loadTextureName_.Clear();
    return true;
}

bool SpriteSheet2D::BeginLoadFromXMLFile(Deserializer& source)
{
    loadXMLFile_ = new XMLFile(context_);
    if (!loadXMLFile_->Load(source))
    {
        URHO3D_LOGERROR("Could not load sprite sheet");
        loadXMLFile_.Reset();
        return false;
    }

    SetMemoryUse(source.GetSize());

    XMLElement rootElem = loadXMLFile_->GetRoot("TextureAtlas");
    if (!rootElem)
    {
        URHO3D_LOGERROR("Invalid sprite sheet");
        loadXMLFile_.Reset();
        return false;
    }

    // If we're async loading, request the texture now. Finish during EndLoad().
    loadTextureName_ = GetParentPath(GetName()) + rootElem.GetAttribute("imagePath");
    if (GetAsyncLoadState() == ASYNC_LOADING)
        GetSubsystem<ResourceCache>()->BackgroundLoadResource<Texture2D>(loadTextureName_, true, this);

    return true;
}

bool SpriteSheet2D::EndLoadFromXMLFile()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    texture_ = cache->GetResource<Texture2D>(loadTextureName_);
    if (!texture_)
    {
        URHO3D_LOGERROR("Could not load texture " + loadTextureName_);
        loadXMLFile_.Reset();
        loadTextureName_.Clear();
        return false;
    }

    XMLElement rootElem = loadXMLFile_->GetRoot("TextureAtlas");
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

    loadXMLFile_.Reset();
    loadTextureName_.Clear();
    return true;
}

}
