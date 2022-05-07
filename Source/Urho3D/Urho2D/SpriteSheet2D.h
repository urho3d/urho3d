// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Resource/Resource.h"

namespace Urho3D
{

class PListFile;
class Sprite2D;
class Texture2D;
class XMLFile;
class JSONFile;

/// Sprite sheet.
class URHO3D_API SpriteSheet2D : public Resource
{
    URHO3D_OBJECT(SpriteSheet2D, Resource);

public:
    /// Construct.
    explicit SpriteSheet2D(Context* context);
    /// Destruct.
    ~SpriteSheet2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    bool BeginLoad(Deserializer& source) override;
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    bool EndLoad() override;

    /// Set texture.
    /// @property
    void SetTexture(Texture2D* texture);
    /// Define sprite.
    void DefineSprite(const String& name, const IntRect& rectangle, const Vector2& hotSpot = Vector2(0.5f, 0.5f),
        const IntVector2& offset = IntVector2::ZERO);

    /// Return texture.
    /// @property
    Texture2D* GetTexture() const { return texture_; }
    /// Return sprite.
    Sprite2D* GetSprite(const String& name) const;

    /// Return sprite mapping.
    const HashMap<String, SharedPtr<Sprite2D> >& GetSpriteMapping() const { return spriteMapping_; }

private:
    /// Begin load from PList file.
    bool BeginLoadFromPListFile(Deserializer& source);
    /// End load from PList file.
    bool EndLoadFromPListFile();

    /// Begin load from XML file.
    bool BeginLoadFromXMLFile(Deserializer& source);
    /// End load from XML file.
    bool EndLoadFromXMLFile();
    /// Begin load from JSON file.
    bool BeginLoadFromJSONFile(Deserializer& source);
    /// End load from JSON file.
    bool EndLoadFromJSONFile();

    /// Texture.
    SharedPtr<Texture2D> texture_;
    /// Sprite mapping.
    HashMap<String, SharedPtr<Sprite2D> > spriteMapping_;
    /// PList file used while loading.
    SharedPtr<PListFile> loadPListFile_;
    /// XML file used while loading.
    SharedPtr<XMLFile> loadXMLFile_;
    /// JSON file used while loading.
    SharedPtr<JSONFile> loadJSONFile_;
    /// Texture name used while loading.
    String loadTextureName_;
};

}
