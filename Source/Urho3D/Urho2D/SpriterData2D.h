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
    SpriterData();
    ~SpriterData();

    void Reset();
    bool Load(const pugi::xml_node& node);
    bool Load(const void* data, size_t size);

    int scmlVersion_;
    String generator_;
    String generatorVersion_;
    PODVector<Folder*> folders_;
    PODVector<Entity*> entities_;
};

/// Folder.
struct Folder
{
    Folder();
    ~Folder();

    void Reset();
    bool Load(const pugi::xml_node& node);

    int id_;
    String name_;
    PODVector<File*> files_;
};

/// File.
struct File
{
    File(Folder* folder);
    ~File();

    bool Load(const pugi::xml_node& node);

    Folder* folder_;
    int id_;
    String name_;
    float width_;
    float height_;
    float pivotX_;
    float pivotY_;
};

/// Entity.
struct Entity
{
    Entity();
    ~Entity();

    void Reset();
    bool Load(const pugi::xml_node& node);

    int id_;
    String name_;
    PODVector<CharacterMap*> characterMaps_;
    PODVector<Animation*> animations_;
};

/// Character map.
struct CharacterMap
{
    CharacterMap();
    ~CharacterMap();

    void Reset();
    bool Load(const pugi::xml_node& node);

    int id_;
    String name_;
    PODVector<MapInstruction*> maps_;
};

/// Map instruction.
struct MapInstruction
{
    MapInstruction();
    ~MapInstruction();

    bool Load(const pugi::xml_node& node);

    int folder_;
    int file_;
    int targetFolder_;
    int targetFile_;
};

/// Animation.
struct Animation
{
    Animation();
    ~Animation();

    void Reset();
    bool Load(const pugi::xml_node& node);

    int id_;
    String name_;
    float length_;
    bool looping_;
    PODVector<MainlineKey*> mainlineKeys_;
    PODVector<Timeline*> timelines_;
};

/// Mainline key.
struct MainlineKey
{
    MainlineKey();
    ~MainlineKey();

    void Reset();
    bool Load(const pugi::xml_node& node);

    int id_;
    float time_;
    PODVector<Ref*> boneRefs_;
    PODVector<Ref*> objectRefs_;
};

/// Ref.
struct Ref
{
    Ref();
    ~Ref();

    bool Load(const pugi::xml_node& node);

    int id_;
    int parent_;
    int timeline_;
    int key_;
    int zIndex_;
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
    Timeline();
    ~Timeline();

    void Reset();
    bool Load(const pugi::xml_node& node);

    int id_;
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
    TimelineKey(Timeline* timeline);
    virtual ~TimelineKey();

    virtual ObjectType GetObjectType() const = 0;
    virtual TimelineKey* Clone() const = 0;
    virtual bool Load(const pugi::xml_node& node);
    virtual void Interpolate(const TimelineKey& other, float t) = 0;
    TimelineKey& operator=(const TimelineKey& rhs);
    float GetTByCurveType(float currentTime, float nextTimelineTime) const;

    Timeline* timeline_;
    int id_;
    float time_;
    CurveType curveType_;
    float c1_;
    float c2_;
};

/// Spatial info.
struct SpatialInfo
{
    float x_;
    float y_;
    float angle_;
    float scaleX_;
    float scaleY_;
    float alpha_;
    int spin;

    SpatialInfo(float x = 0.0f, float y = 0.0f, float angle = 0.0f, float scale_x = 1, float scale_y = 1, float a = 1, int spin = 1);
    SpatialInfo UnmapFromParent(const SpatialInfo& parentInfo) const;
    void Interpolate(const SpatialInfo& other, float t);
};

/// Spatial timeline key.
struct SpatialTimelineKey : TimelineKey
{
    SpatialInfo info_;

    SpatialTimelineKey(Timeline* timeline);
    virtual ~SpatialTimelineKey();

    virtual bool Load(const pugi::xml_node& node);
    virtual void Interpolate(const TimelineKey& other, float t);
    SpatialTimelineKey& operator=(const SpatialTimelineKey& rhs);
};

/// Bone timeline key.
struct BoneTimelineKey : SpatialTimelineKey
{
    float length_;
    float width_;

    BoneTimelineKey(Timeline* timeline);
    virtual ~BoneTimelineKey();

    virtual ObjectType GetObjectType() const { return BONE; }
    virtual TimelineKey* Clone() const;
    virtual bool Load(const pugi::xml_node& node);
    virtual void Interpolate(const TimelineKey& other, float t);
    BoneTimelineKey& operator=(const BoneTimelineKey& rhs);
};

/// Sprite timeline key.
struct SpriteTimelineKey : SpatialTimelineKey
{
    int folderId_;
    int fileId_;
    bool useDefaultPivot_;
    float pivotX_;
    float pivotY_;

    // Run time data.
    int zIndex_;

    SpriteTimelineKey(Timeline* timeline);
    virtual ~SpriteTimelineKey();

    virtual ObjectType GetObjectType() const { return SPRITE; }
    virtual TimelineKey* Clone() const;
    virtual bool Load(const pugi::xml_node& node);
    virtual void Interpolate(const TimelineKey& other, float t);
    SpriteTimelineKey& operator=(const SpriteTimelineKey& rhs);
};

}

}
