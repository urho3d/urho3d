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
#include "Animation2D.h"
#include "AnimationSet2D.h"
#include "Context.h"
#include "Drawable2D.h"
#include "FileSystem.h"
#include "Log.h"
#include "ResourceCache.h"
#include "Sprite2D.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

AnimationSet2D::AnimationSet2D(Context* context) :
    Resource(context)
{
}

AnimationSet2D::~AnimationSet2D()
{
}

void AnimationSet2D::RegisterObject(Context* context)
{
    context->RegisterFactory<AnimationSet2D>();
}

bool AnimationSet2D::Load(Deserializer& source)
{
    XMLFile xmlFile(context_);
    if (!xmlFile.Load(source))
    {
        LOGERROR("Load XML filed " + source.GetName());
        return false;
    }

    XMLElement rootElem = xmlFile.GetRoot("spriter_data");
    if (!rootElem)
    {
        LOGERROR("Invalid spriter file " + source.GetName());
        return false;
    }
    
    if (!LoadFolders(rootElem))
        return false;

    XMLElement entityElem = rootElem.GetChild("entity");
    if (!entityElem)
    {
        LOGERROR("Could not find entity");
        return false;
    }
    
    for (XMLElement animationElem = entityElem.GetChild("animation"); animationElem; animationElem = animationElem.GetNext("animation"))
    {
        if (!LoadAnimation(animationElem))
            return false;
    }

    return true;
}

unsigned AnimationSet2D::GetNumAnimations() const
{
    return animations_.Size();
}

Animation2D* AnimationSet2D::GetAnimation(unsigned index) const
{
    if (index < animations_.Size())
        return animations_[index];
    return 0;
}

Animation2D* AnimationSet2D::GetAnimation(const String& name) const
{
    for (unsigned i = 0; i < animations_.Size(); ++i)
    {
        if (animations_[i]->GetName() == name)
            return animations_[i];
    }
    return 0;
}

Sprite2D* AnimationSet2D::GetSprite(unsigned folderId, unsigned fileId) const
{
    unsigned key = (folderId << 16) + fileId;
    HashMap<unsigned, SharedPtr<Sprite2D> >::ConstIterator i = sprites_.Find(key);
    if (i != sprites_.End())
        return i->second_;
    return 0;
}

bool AnimationSet2D::LoadFolders(const XMLElement& rootElem)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    String parentPath = GetParentPath(GetName());

    for (XMLElement folderElem = rootElem.GetChild("folder"); folderElem; folderElem = folderElem.GetNext("folder"))
    {
        unsigned folderId = folderElem.GetUInt("id");

        for (XMLElement fileElem = folderElem.GetChild("file"); fileElem; fileElem = fileElem.GetNext("file"))
        {
            unsigned fileId = fileElem.GetUInt("id");
            String fileName = fileElem.GetAttribute("name");

            SharedPtr<Sprite2D> sprite(cache->GetResource<Sprite2D>(parentPath + fileName));
            if (!sprite)
            {
                LOGERROR("Could not load sprite " + parentPath + fileName);
                return false;
            }
            
            Vector2 hotSpot(0.0f, 1.0f);
            if (fileElem.HasAttribute("pivot_x"))
                hotSpot.x_ = fileElem.GetFloat("pivot_x");
            if (fileElem.HasAttribute("pivot_y"))
                hotSpot.y_ = fileElem.GetFloat("pivot_y");
            sprite->SetHotSpot(hotSpot);

            sprites_[(folderId << 16) + fileId] = sprite;
        }
    }

    return true;
}


bool AnimationSet2D::LoadAnimation(const XMLElement& animationElem)
{
    SharedPtr<Animation2D> animation(new Animation2D(this));
    
    String name = animationElem.GetAttribute("name");
    animation->SetName(name);

    float length = animationElem.GetFloat("length") * 0.001f;
    animation->SetLength(length);

    bool looped = true;
    if (animationElem.HasAttribute("looping"))
        looped = animationElem.GetBool("looping");
    animation->SetLooped(looped);

    // Load main line
    XMLElement mainlineElem = animationElem.GetChild("mainline");
    for (XMLElement keyElem = mainlineElem.GetChild("key"); keyElem; keyElem = keyElem.GetNext("key"))
    {
        MainlineKey mainlineKey;
        mainlineKey.time_ = keyElem.GetFloat("time") * 0.001f;

        // Just support object ref now
        for (XMLElement objectRefElem = keyElem.GetChild("object_ref"); objectRefElem; objectRefElem = objectRefElem.GetNext("object_ref"))
        {
            ObjectRef objectRef;
            objectRef.timeline_ = objectRefElem.GetInt("timeline");
            objectRef.key_ = objectRefElem.GetInt("key");
            objectRef.zIndex_ = objectRefElem.GetInt("z_index");

            mainlineKey.objectRefs_.Push(objectRef);
        }

        animation->AddMainlineKey(mainlineKey);
    }

    // Load time lines
    for (XMLElement timelineElem = animationElem.GetChild("timeline"); timelineElem; timelineElem = timelineElem.GetNext("timeline"))
    {
        Timeline timeline;
        timeline.name_ = timelineElem.GetAttribute("name");

        for (XMLElement keyElem = timelineElem.GetChild("key"); keyElem; keyElem = keyElem.GetNext("key"))
        {
            ObjectKey objectKey;
            objectKey.time_ = keyElem.GetFloat("time") * 0.001f;
            objectKey.spin_ = 1;
            if (keyElem.HasAttribute("spin"))
                objectKey.spin_ = keyElem.GetInt("spin");

            XMLElement objectElem = keyElem.GetChild("object");          
            
            int folder = objectElem.GetUInt("folder");
            int file = objectElem.GetUInt("file");
            objectKey.sprite_ = GetSprite(folder, file);
            if (!objectKey.sprite_)
            {
                LOGERROR("Could not find sprite");
                return false;
            }

            objectKey.position_.x_ = objectElem.GetFloat("x") * PIXEL_SIZE;
            objectKey.position_.y_ = objectElem.GetFloat("y") * PIXEL_SIZE;
            
            if (objectElem.HasAttribute("pivot_x"))
                objectKey.hotSpot_.x_ = objectElem.GetFloat("pivot_x");
            else
                objectKey.hotSpot_.x_ = objectKey.sprite_->GetHotSpot().x_;

            if (objectElem.HasAttribute("pivot_y"))
                objectKey.hotSpot_.y_ = objectElem.GetFloat("pivot_y");
            else
                objectKey.hotSpot_.y_ = objectKey.sprite_->GetHotSpot().y_;

            if (objectElem.HasAttribute("scale_x"))
                objectKey.scale_.x_ = objectElem.GetFloat("scale_x");

            if (objectElem.HasAttribute("scale_y"))
                objectKey.scale_.y_ = objectElem.GetFloat("scale_y");

            objectKey.angle_= objectElem.GetFloat("angle");
                
            if (objectElem.HasAttribute("a"))
                objectKey.alpha_ = objectElem.GetFloat("a");

            timeline.objectKeys_.Push(objectKey);
        }

        // Add end key for looped animation
        if (looped && timeline.objectKeys_.Back().time_ != length)
        {
            ObjectKey objectKey = timeline.objectKeys_.Front();
            objectKey.time_ = length;
            timeline.objectKeys_.Push(objectKey);
        }

        animation->AddTimeline(timeline);
    }

    animations_.Push(animation);

    return true;
}


}
