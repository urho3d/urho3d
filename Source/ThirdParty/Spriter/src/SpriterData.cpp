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

#include "SpriterData.h"
#include "pugixml.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>

using namespace pugi;

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
        if (!folders_.empty())
        {
            for (size_t i = 0; i < folders_.size(); ++i)
                delete folders_[i];
            folders_.clear();
        }

        if (!entities_.empty())
        {
            for (size_t i = 0; i < entities_.size(); ++i)
                delete entities_[i];
            entities_.clear();
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
            folders_.push_back(new  Folder());
            if (!folders_.back()->Load(folderNode))
                return false;
        }

        for (xml_node entityNode = node.child("entity"); !entityNode.empty(); entityNode = entityNode.next_sibling("entity"))
        {
            entities_.push_back(new  Entity());
            if (!entities_.back()->Load(entityNode))
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
        for (size_t i = 0; i < files_.size(); ++i)
            delete files_[i];
        files_.clear();
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
            files_.push_back(new  File(this));
            if (!files_.back()->Load(fileNode))
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
        for (size_t i = 0; i < characterMaps_.size(); ++i)
            delete characterMaps_[i];
        characterMaps_.clear();

        for (size_t i = 0; i < animations_.size(); ++i)
            delete animations_[i];
        animations_.clear();
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
            characterMaps_.push_back(new CharacterMap());
            if (!characterMaps_.back()->Load(characterMapNode))
                return false;
        }

        for (xml_node animationNode = node.child("animation"); !animationNode.empty(); animationNode = animationNode.next_sibling("animation"))
        {
            animations_.push_back(new  Animation());
            if (!animations_.back()->Load(animationNode))
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
        for (size_t i = 0; i < maps_.size(); ++i)
            delete maps_[i];
        maps_.clear();
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
            maps_.push_back(new MapInstruction());
            if (!maps_.back()->Load(mapNode))
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
        if (!mainlineKeys_.empty())
        {
            for (size_t i = 0; i < mainlineKeys_.size(); ++i)
                delete mainlineKeys_[i];
            mainlineKeys_.clear();
        }

        for (size_t i = 0; i < timelines_.size(); ++i)
            delete timelines_[i];
        timelines_.clear();
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
            mainlineKeys_.push_back(new MainlineKey());
            if (!mainlineKeys_.back()->Load(keyNode))
                return false;
        }

        for (xml_node timelineNode = node.child("timeline"); !timelineNode.empty(); timelineNode = timelineNode.next_sibling("timeline"))
        {
            timelines_.push_back(new Timeline());
            if (!timelines_.back()->Load(timelineNode))
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
        for (size_t i = 0; i < boneRefs_.size(); ++i)
            delete boneRefs_[i];
        boneRefs_.clear();

        for (size_t i = 0; i < objectRefs_.size(); ++i)
            delete objectRefs_[i];
        objectRefs_.clear();
    }

    bool MainlineKey::Load(const pugi::xml_node& node)
    {
        id_ = node.attribute("id").as_int();
        time_ = node.attribute("time").as_float() * 0.001f;

        for (xml_node boneRefNode = node.child("bone_ref"); !boneRefNode.empty(); boneRefNode = boneRefNode.next_sibling("bone_ref"))
        {
            boneRefs_.push_back(new Ref());
            if (!boneRefs_.back()->Load(boneRefNode))
                return false;
        }

        for (xml_node objectRefNode = node.child("object_ref"); !objectRefNode.empty(); objectRefNode = objectRefNode.next_sibling("object_ref"))
        {
            objectRefs_.push_back(new Ref());
            if (!objectRefs_.back()->Load(objectRefNode))
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
        for (size_t i = 0; i < keys_.size(); ++i)
            delete keys_[i];
        keys_.clear();
    }

    bool Timeline::Load(const pugi::xml_node& node)
    {
        Reset();

        if (strcmp(node.name(), "timeline"))
            return false;

        id_ = node.attribute("id").as_int();
        name_ = node.attribute("name").as_string();

        std::string typeString = node.attribute("type").as_string("sprite");
        if (typeString == "bone")
        {
            objectType_ = BONE;
            for (xml_node keyNode = node.child("key"); !keyNode.empty(); keyNode = keyNode.next_sibling("key"))
            {
                keys_.push_back(new BoneTimelineKey(this));
                if (!keys_.back()->Load(keyNode))
                    return false;
            }
        }
        else if (typeString == "sprite")
        {
            objectType_ = SPRITE;
            for (xml_node keyNode = node.child("key"); !keyNode.empty(); keyNode = keyNode.next_sibling("key"))
            {
                keys_.push_back(new SpriteTimelineKey(this));
                if (!keys_.back()->Load(keyNode))
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

        /*
        std::string curveTypeString = node.attribute("curve_type").as_string("linear");
        if (curveTypeString == "linear")
            curveType = LINEAR;
        else if (curveTypeString == "quadratic")
            curveType = QUADRATIC;
        else if (curveTypeString == "cubic")
            curveType = CUBIC;
        */
        // Force linear
        curveType_ = LINEAR;

        c1_ = node.attribute("c1").as_float();
        c2_ = node.attribute("c2").as_float();
        c3_ = node.attribute("c2").as_float();
        c4_ = node.attribute("c2").as_float();

        return true;
    }

    TimelineKey& TimelineKey::operator=(const TimelineKey& rhs)
    {
        id_ = rhs.id_;
        time_ = rhs.time_;
        curveType_ = rhs.curveType_;
        c1_ = rhs.c1_;
        c2_ = rhs.c2_;
        c3_ = rhs.c3_;
        c4_ = rhs.c4_;
        return *this;
    }

    void TimelineKey::Interpolate(const TimelineKey& other, float t)
    {

    }

    float toRadians(float deg)
    {
        const float PI = 3.141592653589793f;
        return deg * PI / 180.0f;
    }

    float under360(float rotation)
    {
        while (rotation > 360.0f)
        {
            rotation -= 360.0f;
        }

        while (rotation < 0.0f)
        {
            rotation += 360.0f;
        }

        return rotation;
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
            
            float parentRad = toRadians(under360(parentInfo.angle_));

            float s = sinf(parentRad);
            float c = cosf(parentRad);

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

    inline float linear(float a, float b, float t)
    {
        return a + (b - a) * t;
    }

    void SpatialInfo::Interpolate(const SpatialInfo& other, float t)
    {
        x_ = linear(x_, other.x_, t);
        y_ = linear(y_, other.y_, t);

        if (spin > 0.0f && (other.angle_ - angle_ < 0.0f))
        {
            angle_ = linear(angle_, other.angle_ + 360.0f, t);
        }
        else if (spin < 0.0f && (other.angle_ - angle_ > 0.0f))
        {
            angle_ = linear(angle_, other.angle_ - 360.0f, t);
        }
        else
        {
            angle_ = linear(angle_, other.angle_, t);
        }

        scaleX_ = linear(scaleX_, other.scaleX_, t);
        scaleY_ = linear(scaleY_, other.scaleY_, t);
        alpha_ = linear(alpha_, other.alpha_, t);
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
        length_ = linear(length_, o.length_, t);
        width_ = linear(width_, o.width_, t);
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
        pivotX_ = linear(pivotX_, o.pivotX_, t);
        pivotY_ = linear(pivotY_, o.pivotY_, t);
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
