//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Math/MathDefs.h"
#include "../Urho2D/SpriterData2D.h"

#include <PugiXml/pugixml.hpp>

#include <cstring>

using namespace pugi;

namespace Urho3D
{

namespace Spriter
{

SpriterData::SpriterData()
{
}

SpriterData::~SpriterData()
{
    Reset();
}

void SpriterData::Reset()
{
    if (!folders_.Empty())
    {
        for (size_t i = 0; i < folders_.Size(); ++i)
            delete folders_[i];
        folders_.Clear();
    }

    if (!entities_.Empty())
    {
        for (size_t i = 0; i < entities_.Size(); ++i)
            delete entities_[i];
        entities_.Clear();
    }
}

bool SpriterData::Load(const pugi::xml_node& node)
{
    Reset();

    if (strcmp(node.name(), "spriter_data"))
        return false;

    scmlVersion_ = node.attribute("scml_version").as_int();
    generator_ = node.attribute("generator").as_string();
    generatorVersion_ = node.attribute("scml_version").as_string();

    for (xml_node folderNode = node.child("folder"); !folderNode.empty(); folderNode = folderNode.next_sibling("folder"))
    {
        folders_.Push(new  Folder());
        if (!folders_.Back()->Load(folderNode))
            return false;
    }

    for (xml_node entityNode = node.child("entity"); !entityNode.empty(); entityNode = entityNode.next_sibling("entity"))
    {
        entities_.Push(new  Entity());
        if (!entities_.Back()->Load(entityNode))
            return false;
    }

    return true;
}

bool SpriterData::Load(const void* data, size_t size)
{
    xml_document document;
    if (!document.load_buffer(data, size))
        return false;

    return Load(document.child("spriter_data"));
}

Folder::Folder()
{

}

Folder::~Folder()
{
    Reset();
}

void Folder::Reset()
{
    for (size_t i = 0; i < files_.Size(); ++i)
        delete files_[i];
    files_.Clear();
}

bool Folder::Load(const pugi::xml_node& node)
{
    Reset();

    if (strcmp(node.name(), "folder"))
        return false;

    id_ = node.attribute("id").as_int();
    name_ = node.attribute("name").as_string();

    for (xml_node fileNode = node.child("file"); !fileNode.empty(); fileNode = fileNode.next_sibling("file"))
    {
        files_.Push(new  File(this));
        if (!files_.Back()->Load(fileNode))
            return false;
    }

    return true;
}

File::File(Folder* folder) : 
    folder_(folder)
{
}

File::~File()
{
}

bool File::Load(const pugi::xml_node& node)
{
    if (strcmp(node.name(), "file"))
        return false;

    id_ = node.attribute("id").as_int();
    name_ = node.attribute("name").as_string();
    width_ = node.attribute("width").as_float();
    height_ = node.attribute("height").as_float();
    pivotX_ = node.attribute("pivot_x").as_float(0.0f);
    pivotY_ = node.attribute("pivot_y").as_float(1.0f);

    return true;
}

Entity::Entity()
{

}

Entity::~Entity()
{
    Reset();
}

void Entity::Reset()
{
    for (size_t i = 0; i < characterMaps_.Size(); ++i)
        delete characterMaps_[i];
    characterMaps_.Clear();

    for (size_t i = 0; i < animations_.Size(); ++i)
        delete animations_[i];
    animations_.Clear();
}

bool Entity::Load(const pugi::xml_node& node)
{
    Reset();

    if (strcmp(node.name(), "entity"))
        return false;

    id_ = node.attribute("id").as_int();
    name_ = node.attribute("name").as_string();

    for (xml_node characterMapNode = node.child("character_map"); !characterMapNode.empty(); characterMapNode = characterMapNode.next_sibling("character_map"))
    {
        characterMaps_.Push(new CharacterMap());
        if (!characterMaps_.Back()->Load(characterMapNode))
            return false;
    }

    for (xml_node animationNode = node.child("animation"); !animationNode.empty(); animationNode = animationNode.next_sibling("animation"))
    {
        animations_.Push(new  Animation());
        if (!animations_.Back()->Load(animationNode))
            return false;
    }

    return true;
}

CharacterMap::CharacterMap()
{

}

CharacterMap::~CharacterMap()
{

}

void CharacterMap::Reset()
{
    for (size_t i = 0; i < maps_.Size(); ++i)
        delete maps_[i];
    maps_.Clear();
}

bool CharacterMap::Load(const pugi::xml_node& node)
{
    Reset();

    if (strcmp(node.name(), "character_map"))
        return false;

    id_ = node.attribute("id").as_int();
    name_ = node.attribute("name").as_string();

    for (xml_node mapNode = node.child("map"); !mapNode.empty(); mapNode = mapNode.next_sibling("map"))
    {
        maps_.Push(new MapInstruction());
        if (!maps_.Back()->Load(mapNode))
            return false;
    }

    return false;
}

MapInstruction::MapInstruction()
{

}

MapInstruction::~MapInstruction()
{

}

bool MapInstruction::Load(const pugi::xml_node& node)
{
    if (strcmp(node.name(), "map"))
        return false;

    folder_ = node.attribute("folder").as_int();
    file_ = node.attribute("file").as_int();
    targetFolder_ = node.attribute("target_folder").as_int(-1);
    targetFile_ = node.attribute("target_file").as_int(-1);

    return true;
}

Animation::Animation()
{

}

Animation::~Animation()
{
    Reset();
}

void Animation::Reset()
{
    if (!mainlineKeys_.Empty())
    {
        for (size_t i = 0; i < mainlineKeys_.Size(); ++i)
            delete mainlineKeys_[i];
        mainlineKeys_.Clear();
    }

    for (size_t i = 0; i < timelines_.Size(); ++i)
        delete timelines_[i];
    timelines_.Clear();
}

bool Animation::Load(const pugi::xml_node& node)
{
    Reset();

    if (strcmp(node.name(), "animation"))
        return false;

    id_ = node.attribute("id").as_int();
    name_ = node.attribute("name").as_string();
    length_ = node.attribute("length").as_float() * 0.001f;
    looping_ = node.attribute("looping").as_bool(true);

    xml_node mainlineNode = node.child("mainline");
    for (xml_node keyNode = mainlineNode.child("key"); !keyNode.empty(); keyNode = keyNode.next_sibling("key"))
    {
        mainlineKeys_.Push(new MainlineKey());
        if (!mainlineKeys_.Back()->Load(keyNode))
            return false;
    }

    for (xml_node timelineNode = node.child("timeline"); !timelineNode.empty(); timelineNode = timelineNode.next_sibling("timeline"))
    {
        timelines_.Push(new Timeline());
        if (!timelines_.Back()->Load(timelineNode))
            return false;
    }

    return true;
}

MainlineKey::MainlineKey()
{

}

MainlineKey::~MainlineKey()
{
    Reset();
}

void MainlineKey::Reset()
{
    for (size_t i = 0; i < boneRefs_.Size(); ++i)
        delete boneRefs_[i];
    boneRefs_.Clear();

    for (size_t i = 0; i < objectRefs_.Size(); ++i)
        delete objectRefs_[i];
    objectRefs_.Clear();
}

bool MainlineKey::Load(const pugi::xml_node& node)
{
    id_ = node.attribute("id").as_int();
    time_ = node.attribute("time").as_float() * 0.001f;

    for (xml_node boneRefNode = node.child("bone_ref"); !boneRefNode.empty(); boneRefNode = boneRefNode.next_sibling("bone_ref"))
    {
        boneRefs_.Push(new Ref());
        if (!boneRefs_.Back()->Load(boneRefNode))
            return false;
    }

    for (xml_node objectRefNode = node.child("object_ref"); !objectRefNode.empty(); objectRefNode = objectRefNode.next_sibling("object_ref"))
    {
        objectRefs_.Push(new Ref());
        if (!objectRefs_.Back()->Load(objectRefNode))
            return false;
    }

    return true;
}

Ref::Ref()
{

}

Ref::~Ref()
{
}

bool Ref::Load(const pugi::xml_node& node)
{
    if (strcmp(node.name(), "bone_ref") && strcmp(node.name(), "object_ref"))
        return false;

    id_ = node.attribute("id").as_int();
    parent_ = node.attribute("parent").as_int(-1);
    timeline_ = node.attribute("timeline").as_int();
    key_ = node.attribute("key").as_int();
    zIndex_ = node.attribute("z_index").as_int();

    return true;
}

Timeline::Timeline()
{

}

Timeline::~Timeline()
{
    Reset();
}

void Timeline::Reset()
{
    for (size_t i = 0; i < keys_.Size(); ++i)
        delete keys_[i];
    keys_.Clear();
}

bool Timeline::Load(const pugi::xml_node& node)
{
    Reset();

    if (strcmp(node.name(), "timeline"))
        return false;

    id_ = node.attribute("id").as_int();
    name_ = node.attribute("name").as_string();

    String typeString;
    xml_attribute typeAttr = node.attribute("type");
    if (typeAttr.empty())
        typeString = node.attribute("object_type").as_string("sprite");
    else
        typeString = typeAttr.as_string("sprite");
    
    if (typeString == "bone")
    {
        objectType_ = BONE;
        for (xml_node keyNode = node.child("key"); !keyNode.empty(); keyNode = keyNode.next_sibling("key"))
        {
            keys_.Push(new BoneTimelineKey(this));
            if (!keys_.Back()->Load(keyNode))
                return false;
        }
    }
    else if (typeString == "sprite")
    {
        objectType_ = SPRITE;
        for (xml_node keyNode = node.child("key"); !keyNode.empty(); keyNode = keyNode.next_sibling("key"))
        {
            keys_.Push(new SpriteTimelineKey(this));
            if (!keys_.Back()->Load(keyNode))
                return false;
        }
    }
    else
    {
        // Unsupported object type now.
        return false;
    }

    return true;
}

TimelineKey::TimelineKey(Timeline* timeline)
{
    this->timeline_ = timeline;
}

TimelineKey::~TimelineKey()
{
}

bool TimelineKey::Load(const pugi::xml_node& node)
{
    if (strcmp(node.name(), "key"))
        return false;

    id_ = node.attribute("id").as_int();
    time_ = node.attribute("time").as_float() * 0.001f;

    String curveType = node.attribute("curve_type").as_string("linear");
    if (curveType == "instant")
        curveType_ = INSTANT;
    else if (curveType == "linear")
        curveType_ = LINEAR;
    else if (curveType == "quadratic")
        curveType_ = QUADRATIC;
    else if (curveType == "cubic")
        curveType_ = CUBIC;
    else
        curveType_ = LINEAR;

    c1_ = node.attribute("c1").as_float();
    c2_ = node.attribute("c2").as_float();

    return true;
}

TimelineKey& TimelineKey::operator=(const TimelineKey& rhs)
{
    id_ = rhs.id_;
    time_ = rhs.time_;
    curveType_ = rhs.curveType_;
    c1_ = rhs.c1_;
    c2_ = rhs.c2_;
    return *this;
}

// From http://www.brashmonkey.com/ScmlDocs/ScmlReference.html

inline float Linear(float a, float b, float t)
{
    return a + (b - a) * t;
}

inline float Quadratic(float a, float b, float c, float t)
{
    return Linear(Linear(a, b, t), Linear(b, c, t), t);
}

inline float Cubic(float a, float b, float c, float d, float t)
{
    return Linear(Quadratic(a, b, c, t), Quadratic(b, c, d, t), t);
}

float TimelineKey::GetTByCurveType(float currentTime, float nextTimelineTime) const
{
    if (curveType_ == INSTANT)
        return 0.0f;

    float t = (currentTime - time_) / (nextTimelineTime - time_);
    switch (curveType_)
    {
    case LINEAR:
        return t;

    case QUADRATIC:
        return Quadratic(0.0f, c1_, 1.0f, t);

    case CUBIC:
        return Cubic(0.0f, c1_, c2_, 1.0f, t);

    default:
        return 0.0f;
    }
}

SpatialInfo::SpatialInfo(float x, float y, float angle, float scale_x, float scale_y, float a, int spin)
{
    this->x_ = x; 
    this->y_ = y; 
    this->angle_ = angle;
    this->scaleX_ = scale_x; 
    this->scaleY_ = scale_y; 
    this->alpha_ = a;
    this->spin = spin;
}

SpatialInfo SpatialInfo::UnmapFromParent(const SpatialInfo& parentInfo) const
{
    float unmappedX;
    float unmappedY;
    float unmappedAngle = angle_ + parentInfo.angle_;
    float unmappedScaleX = scaleX_ * parentInfo.scaleX_;
    float unmappedScaleY = scaleY_ * parentInfo.scaleY_;
    float unmappedAlpha = alpha_ * parentInfo.alpha_;

    if (x_ != 0.0f || y_ != 0.0f)
    {
        float preMultX = x_ * parentInfo.scaleX_;
        float preMultY = y_ * parentInfo.scaleY_;

        float s = Sin(parentInfo.angle_);
        float c = Cos(parentInfo.angle_);

        unmappedX = (preMultX * c) - (preMultY * s) + parentInfo.x_;
        unmappedY = (preMultX * s) + (preMultY * c) + parentInfo.y_;
    }
    else
    {
        unmappedX = parentInfo.x_;
        unmappedY = parentInfo.y_;
    }

    return SpatialInfo(unmappedX, unmappedY, unmappedAngle, unmappedScaleX, unmappedScaleY, unmappedAlpha, spin);
}

void SpatialInfo::Interpolate(const SpatialInfo& other, float t)
{
    x_ = Linear(x_, other.x_, t);
    y_ = Linear(y_, other.y_, t);

    if (spin > 0.0f && (other.angle_ - angle_ < 0.0f))
    {
        angle_ = Linear(angle_, other.angle_ + 360.0f, t);
    }
    else if (spin < 0.0f && (other.angle_ - angle_ > 0.0f))
    {
        angle_ = Linear(angle_, other.angle_ - 360.0f, t);
    }
    else
    {
        angle_ = Linear(angle_, other.angle_, t);
    }

    scaleX_ = Linear(scaleX_, other.scaleX_, t);
    scaleY_ = Linear(scaleY_, other.scaleY_, t);
    alpha_ = Linear(alpha_, other.alpha_, t);
}

SpatialTimelineKey::SpatialTimelineKey(Timeline* timeline) : 
    TimelineKey(timeline)
{

}

SpatialTimelineKey::~SpatialTimelineKey()
{

}

bool SpatialTimelineKey::Load(const xml_node& node)
{
    if (!TimelineKey::Load(node))
        return false;

    xml_node childNode = node.child("bone");
    if (childNode.empty())
        childNode = node.child("object");

    info_.x_ = childNode.attribute("x").as_float();
    info_.y_ = childNode.attribute("y").as_float();
    info_.angle_ = childNode.attribute("angle").as_float();
    info_.scaleX_ = childNode.attribute("scale_x").as_float(1.0f);
    info_.scaleY_ = childNode.attribute("scale_y").as_float(1.0f);
    info_.alpha_ = childNode.attribute("a").as_float(1.0f);

    info_.spin = node.attribute("spin").as_int(1);

    return true;
}

SpatialTimelineKey& SpatialTimelineKey::operator=(const SpatialTimelineKey& rhs)
{
    TimelineKey::operator=(rhs);
    info_ = rhs.info_;
    return *this;
}   

void SpatialTimelineKey::Interpolate(const TimelineKey& other, float t)
{
    const SpatialTimelineKey& o = (const SpatialTimelineKey&)other;
    info_.Interpolate(o.info_, t);
}

BoneTimelineKey::BoneTimelineKey(Timeline* timeline) : 
    SpatialTimelineKey(timeline)
{

}

BoneTimelineKey::~BoneTimelineKey()
{

}

TimelineKey* BoneTimelineKey::Clone() const
{
    BoneTimelineKey* result = new BoneTimelineKey(timeline_);
    *result = *this;
    return result;
}

bool BoneTimelineKey::Load(const xml_node& node)
{
    if (!SpatialTimelineKey::Load(node))
        return false;

    xml_node boneNode = node.child("bone");
    length_ = boneNode.attribute("length").as_float(200.0f);
    width_ = boneNode.attribute("width").as_float(10.0f);

    return true;
}

BoneTimelineKey& BoneTimelineKey::operator=(const BoneTimelineKey& rhs)
{
    SpatialTimelineKey::operator=(rhs);
    length_ = rhs.length_;
    width_ = rhs.width_;

    return *this;
}

void BoneTimelineKey::Interpolate(const TimelineKey& other, float t)
{
    SpatialTimelineKey::Interpolate(other, t);

    const BoneTimelineKey& o = (const BoneTimelineKey&)other;
    length_ = Linear(length_, o.length_, t);
    width_ = Linear(width_, o.width_, t);
}

TimelineKey* SpriteTimelineKey::Clone() const
{
    SpriteTimelineKey* result = new SpriteTimelineKey(timeline_);
    *result = *this;
    return result;
}

SpriteTimelineKey::SpriteTimelineKey(Timeline* timeline) : 
    SpatialTimelineKey(timeline)
{
}

SpriteTimelineKey::~SpriteTimelineKey()
{

}

bool SpriteTimelineKey::Load(const pugi::xml_node& node)
{
    if (!SpatialTimelineKey::Load(node))
        return false;

    xml_node objectNode = node.child("object");
    folderId_ = objectNode.attribute("folder").as_int(-1);
    fileId_ = objectNode.attribute("file").as_int(-1);

    xml_attribute pivotXAttr = objectNode.attribute("pivot_x");
    xml_attribute pivotYAttr = objectNode.attribute("pivot_y");
    if (pivotXAttr.empty() && pivotYAttr.empty())
        useDefaultPivot_ = true;
    else
    {
        useDefaultPivot_ = false;
        pivotX_ = pivotXAttr.as_float(0.0f);
        pivotY_ = pivotYAttr.as_float(1.0f);
    }

    return true;
}

void SpriteTimelineKey::Interpolate(const TimelineKey& other, float t)
{
    SpatialTimelineKey::Interpolate(other, t);
        
    const SpriteTimelineKey& o = (const SpriteTimelineKey&)other;
    pivotX_ = Linear(pivotX_, o.pivotX_, t);
    pivotY_ = Linear(pivotY_, o.pivotY_, t);
}

SpriteTimelineKey& SpriteTimelineKey::operator=(const SpriteTimelineKey& rhs)
{
    SpatialTimelineKey::operator=(rhs);
        
    folderId_ = rhs.folderId_;
    fileId_ = rhs.fileId_;
    useDefaultPivot_ = rhs.useDefaultPivot_;
    pivotX_ = rhs.pivotX_;
    pivotY_ = rhs.pivotY_;

    return *this;
}

}

}
