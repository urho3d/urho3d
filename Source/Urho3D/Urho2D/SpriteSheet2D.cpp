// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../GraphicsAPI/Texture2D.h"
#include "../IO/Deserializer.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../Resource/JSONFile.h"
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

SpriteSheet2D::~SpriteSheet2D() = default;

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

    if (extension == ".json")
        return BeginLoadFromJSONFile(source);


    URHO3D_LOGERROR("Unsupported file type");
    return false;
}

bool SpriteSheet2D::EndLoad()
{
    if (loadPListFile_)
        return EndLoadFromPListFile();

    if (loadXMLFile_)
        return EndLoadFromXMLFile();

    if (loadJSONFile_)
        return EndLoadFromJSONFile();

    return false;
}

void SpriteSheet2D::SetTexture(Texture2D* texture)
{
    loadTextureName_.Clear();
    texture_ = texture;
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

Sprite2D* SpriteSheet2D::GetSprite(const String& name) const
{
    HashMap<String, SharedPtr<Sprite2D>>::ConstIterator i = spriteMapping_.Find(name);
    if (i == spriteMapping_.End())
        return nullptr;

    return i->second_;
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
    auto* cache = GetSubsystem<ResourceCache>();
    texture_ = cache->GetResource<Texture2D>(loadTextureName_);
    if (!texture_)
    {
        URHO3D_LOGERROR("Could not load texture " + loadTextureName_);
        loadPListFile_.Reset();
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
            hotSpot.x_ = (offset.x_ + sourceSize.x_ / 2.f) / rectangle.Width();
            hotSpot.y_ = 1.0f - (offset.y_ + sourceSize.y_ / 2.f) / rectangle.Height();
        }

        DefineSprite(name, rectangle, hotSpot, offset);
    }

    loadPListFile_.Reset();
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
    auto* cache = GetSubsystem<ResourceCache>();
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

        int x = subTextureElem.GetI32("x");
        int y = subTextureElem.GetI32("y");
        int width = subTextureElem.GetI32("width");
        int height = subTextureElem.GetI32("height");
        IntRect rectangle(x, y, x + width, y + height);

        Vector2 hotSpot(0.5f, 0.5f);
        IntVector2 offset(0, 0);
        if (subTextureElem.HasAttribute("frameWidth") && subTextureElem.HasAttribute("frameHeight"))
        {
            offset.x_ = subTextureElem.GetI32("frameX");
            offset.y_ = subTextureElem.GetI32("frameY");
            int frameWidth = subTextureElem.GetI32("frameWidth");
            int frameHeight = subTextureElem.GetI32("frameHeight");
            hotSpot.x_ = (offset.x_ + frameWidth / 2.f) / width;
            hotSpot.y_ = 1.0f - (offset.y_ + frameHeight / 2.f) / height;
        }

        DefineSprite(name, rectangle, hotSpot, offset);

        subTextureElem = subTextureElem.GetNext("SubTexture");
    }

    loadXMLFile_.Reset();
    loadTextureName_.Clear();
    return true;
}

bool SpriteSheet2D::BeginLoadFromJSONFile(Deserializer& source)
{
    loadJSONFile_ = new JSONFile(context_);
    if (!loadJSONFile_->Load(source))
    {
        URHO3D_LOGERROR("Could not load sprite sheet");
        loadJSONFile_.Reset();
        return false;
    }

    SetMemoryUse(source.GetSize());

    JSONValue rootElem = loadJSONFile_->GetRoot();
    if (rootElem.IsNull())
    {
        URHO3D_LOGERROR("Invalid sprite sheet");
        loadJSONFile_.Reset();
        return false;
    }

    // If we're async loading, request the texture now. Finish during EndLoad().
    loadTextureName_ = GetParentPath(GetName()) + rootElem.Get("imagePath").GetString();
    if (GetAsyncLoadState() == ASYNC_LOADING)
        GetSubsystem<ResourceCache>()->BackgroundLoadResource<Texture2D>(loadTextureName_, true, this);

    return true;
}

bool SpriteSheet2D::EndLoadFromJSONFile()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    texture_ = cache->GetResource<Texture2D>(loadTextureName_);
    if (!texture_)
    {
        URHO3D_LOGERROR("Could not load texture " + loadTextureName_);
        loadJSONFile_.Reset();
        loadTextureName_.Clear();
        return false;
    }

    JSONValue rootVal = loadJSONFile_->GetRoot();
    JSONArray subTextureArray = rootVal.Get("subtextures").GetArray();

    for (const JSONValue& subTextureVal : subTextureArray)
    {
        String name = subTextureVal.Get("name").GetString();

        int x = subTextureVal.Get("x").GetI32();
        int y = subTextureVal.Get("y").GetI32();
        int width = subTextureVal.Get("width").GetI32();
        int height = subTextureVal.Get("height").GetI32();
        IntRect rectangle(x, y, x + width, y + height);

        Vector2 hotSpot(0.5f, 0.5f);
        IntVector2 offset(0, 0);
        JSONValue frameWidthVal = subTextureVal.Get("frameWidth");
        JSONValue frameHeightVal = subTextureVal.Get("frameHeight");

        if (!frameWidthVal.IsNull() && !frameHeightVal.IsNull())
        {
            offset.x_ = subTextureVal.Get("frameX").GetI32();
            offset.y_ = subTextureVal.Get("frameY").GetI32();
            int frameWidth = frameWidthVal.GetI32();
            int frameHeight = frameHeightVal.GetI32();
            hotSpot.x_ = (offset.x_ + frameWidth / 2.f) / width;
            hotSpot.y_ = 1.0f - (offset.y_ + frameHeight / 2.f) / height;
        }

        DefineSprite(name, rectangle, hotSpot, offset);
    }

    loadJSONFile_.Reset();
    loadTextureName_.Clear();
    return true;
}

}
