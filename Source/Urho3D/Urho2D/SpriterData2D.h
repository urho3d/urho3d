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

/// \file

#pragma once

namespace pugi
{
class xml_node;
}

namespace Urho3D
{

namespace Spriter
{

struct Animation;
struct BoneTimelineKey;
struct CharacterMap;
struct Entity;
struct File;
struct Folder;
struct MainlineKey;
struct MapInstruction;
struct Ref;
struct SpatialInfo;
struct SpatialTimelineKey;
struct SpriterData;
struct SpriteTimelineKey;
struct Timeline;
struct TimelineKey;

/// Spriter data.
struct SpriterData
{
    SpriterData() = default;
    ~SpriterData();

    void Reset();
    bool Load(const pugi::xml_node& node);
    bool Load(const void* data, size_t size);

    int scmlVersion_{};
    String generator_;
    String generatorVersion_;
    PODVector<Folder*> folders_;
    PODVector<Entity*> entities_;
};

/// Folder.
struct Folder
{
    Folder() = default;
    ~Folder();

    void Reset();
    bool Load(const pugi::xml_node& node);

    int id_{};
    String name_;
    PODVector<File*> files_;
};

/// File.
struct File
{
    explicit File(Folder* folder);
    ~File() = default;

    bool Load(const pugi::xml_node& node);

    Folder* folder_{};
    int id_{};
    String name_;
    float width_{};
    float height_{};
    float pivotX_{};
    float pivotY_{};
};

/// Entity.
struct Entity
{
    Entity() = default;
    ~Entity();

    void Reset();
    bool Load(const pugi::xml_node& node);

    int id_{};
    String name_;
    PODVector<CharacterMap*> characterMaps_;
    PODVector<Animation*> animations_;
};

/// Character map.
struct CharacterMap
{
    CharacterMap() = default;
    ~CharacterMap();

    void Reset();
    bool Load(const pugi::xml_node& node);

    int id_{};
    String name_;
    PODVector<MapInstruction*> maps_;
};

/// Map instruction.
struct MapInstruction
{
    MapInstruction() = default;
    ~MapInstruction() = default;

    bool Load(const pugi::xml_node& node);

    int folder_{};
    int file_{};
    int targetFolder_{};
    int targetFile_{};
};

/// Animation.
struct Animation
{
    Animation() = default;
    ~Animation();

    void Reset();
    bool Load(const pugi::xml_node& node);

    int id_{};
    String name_;
    float length_{};
    bool looping_{};
    PODVector<MainlineKey*> mainlineKeys_;
    PODVector<Timeline*> timelines_;
};

/// Mainline key.
struct MainlineKey
{
    MainlineKey() = default;
    ~MainlineKey();

    void Reset();
    bool Load(const pugi::xml_node& node);

    int id_{};
    float time_{};
    PODVector<Ref*> boneRefs_;
    PODVector<Ref*> objectRefs_;
};

/// Ref.
struct Ref
{
    Ref() = default;
    ~Ref() = default;

    bool Load(const pugi::xml_node& node);

    int id_{};
    int parent_{};
    int timeline_{};
    int key_{};
    int zIndex_{};
};

/// Object type.
enum ObjectType
{
    BONE = 0,
    SPRITE
};

/// Timeline.
struct Timeline
{
    Timeline() = default;
    ~Timeline();

    void Reset();
    bool Load(const pugi::xml_node& node);

    int id_{};
    String name_;
    ObjectType objectType_;
    PODVector<SpatialTimelineKey*> keys_;
};

/// Curve type.
enum CurveType
{
    INSTANT = 0,
    LINEAR,
    QUADRATIC,
    CUBIC
};

/// Timeline key.
struct TimelineKey
{
    explicit TimelineKey(Timeline* timeline);
    virtual ~TimelineKey() = default;

    virtual ObjectType GetObjectType() const = 0;
    virtual TimelineKey* Clone() const = 0;
    virtual bool Load(const pugi::xml_node& node);
    virtual void Interpolate(const TimelineKey& other, float t) = 0;
    TimelineKey& operator=(const TimelineKey& rhs);
    float GetTByCurveType(float currentTime, float nextTimelineTime) const;

    Timeline* timeline_{};
    int id_{};
    float time_{};
    CurveType curveType_{};
    float c1_{};
    float c2_{};
};

/// Spatial info.
struct SpatialInfo
{
    SpatialInfo(float x, float y, float angle, float scale_x, float scale_y, float alpha = 1, int spin = 1);

    SpatialInfo UnmapFromParent(const SpatialInfo& parentInfo) const;
    void Interpolate(const SpatialInfo& other, float t);

    float x_;
    float y_;
    float angle_;
    float scaleX_;
    float scaleY_;
    float alpha_;
    int spin_;
};

/// Spatial timeline key.
struct SpatialTimelineKey : TimelineKey
{
    explicit SpatialTimelineKey(Timeline* timeline);
    ~SpatialTimelineKey() override = default;

    bool Load(const pugi::xml_node& node) override;
    void Interpolate(const TimelineKey& other, float t) override;
    SpatialTimelineKey& operator=(const SpatialTimelineKey& rhs) = default;

    SpatialInfo info_;
};

/// Bone timeline key.
struct BoneTimelineKey : SpatialTimelineKey
{
    explicit BoneTimelineKey(Timeline* timeline);
    ~BoneTimelineKey() override = default;

    ObjectType GetObjectType() const override { return BONE; }

    TimelineKey* Clone() const override;
    bool Load(const pugi::xml_node& node) override;
    void Interpolate(const TimelineKey& other, float t) override;
    BoneTimelineKey& operator=(const BoneTimelineKey& rhs) = default;

    float length_{};
    float width_{};
};

/// Sprite timeline key.
struct SpriteTimelineKey : SpatialTimelineKey
{
    explicit SpriteTimelineKey(Timeline* timeline);
    ~SpriteTimelineKey() override = default;

    ObjectType GetObjectType() const override { return SPRITE; }

    TimelineKey* Clone() const override;
    bool Load(const pugi::xml_node& node) override;
    void Interpolate(const TimelineKey& other, float t) override;
    SpriteTimelineKey& operator=(const SpriteTimelineKey& rhs);

    int folderId_{};
    int fileId_{};
    bool useDefaultPivot_{};
    float pivotX_{};
    float pivotY_{};

    /// Run time data.
    int zIndex_{};
};

}

}
