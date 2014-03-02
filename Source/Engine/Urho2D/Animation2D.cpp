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
#include "Context.h"
#include "Deserializer.h"
#include "Log.h"
#include "ResourceCache.h"
#include "Serializer.h"
#include "Sprite2D.h"
#include "SpriteSheet2D.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

Animation2D::Animation2D(Context* context) : Resource(context)
{

}

Animation2D::~Animation2D()
{

}

void Animation2D::RegisterObject(Context* context)
{
    context->RegisterFactory<Animation2D>();
}

bool Animation2D::Load(Deserializer& source)
{
    frameEndTimes_.Clear();
    frameSprites_.Clear();

    SharedPtr<XMLFile> xmlFile(new XMLFile(context_));
    if(!xmlFile->Load(source))
    {
        LOGERROR("Could not load animation");
        return false;
    }

    SetMemoryUse(source.GetSize());

    XMLElement rootElem = xmlFile->GetRoot("Animation");
    if (!rootElem)
    {
        LOGERROR("Invalid animation");
        return false;
    }

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    XMLElement keyFrameElem = rootElem.GetChild("Frame");
    if (!keyFrameElem)
    {
        LOGERROR("Could not found key frame");
        return false;
    }

    float endTime = 0.0f;

    while (keyFrameElem)
    {
        endTime += keyFrameElem.GetFloat("duration");
        frameEndTimes_.Push(endTime);

        SharedPtr<Sprite2D> sprite;
        Vector<String> names = keyFrameElem.GetAttribute("sprite").Split('@');
        if (names.Size() == 1)
            sprite = cache->GetResource<Sprite2D>(names[0]);
        else if (names.Size() == 2)
        {
            SpriteSheet2D* spriteSheet = cache->GetResource<SpriteSheet2D>(names[0]);
            if (!spriteSheet)
            {
                LOGERROR("Could not get sprite speet");
                return false;
            }

            sprite = spriteSheet->GetSprite(names[1]);
        }

        if (!sprite)
        {
            LOGERROR("Could not get sprite");
            return false;
        }

        frameSprites_.Push(sprite);
        keyFrameElem = keyFrameElem.GetNext("Frame");
    }

    return true;
}

bool Animation2D::Save(Serializer& dest) const
{
    XMLFile xmlFile(context_);
    XMLElement rootElem = xmlFile.CreateRoot("Animation");
    
    float endTime = 0.0f;
    for (unsigned i = 0; i < frameSprites_.Size(); ++i)
    {
        XMLElement frameElem = rootElem.CreateChild("Frame");
        frameElem.SetFloat("duration", frameEndTimes_[i] - endTime);
        endTime = frameEndTimes_[i];

        Sprite2D* sprite = frameSprites_[i];
        SpriteSheet2D* spriteSheet = sprite->GetSpriteSheet();
        if (!spriteSheet)
            frameElem.SetString("sprite", sprite->GetName());
        else
            frameElem.SetString("sprite", spriteSheet->GetName() + "@" + sprite->GetName());
    }

    return xmlFile.Save(dest);
}

float Animation2D::GetTotalTime() const
{
    return frameEndTimes_.Empty() ? 0.0f : frameEndTimes_.Back();
}

unsigned Animation2D::GetNumFrames() const
{
    return frameSprites_.Size();
}

Sprite2D* Animation2D::GetFrameSprite(unsigned index) const
{
    if (index < frameSprites_.Size())
        return frameSprites_[index];

    return 0;
}

Sprite2D* Animation2D::GetFrameSpriteByTime(float time) const
{
    if (time < 0.0f)
        return 0;

    for (unsigned i = 0; i < frameEndTimes_.Size(); ++i)
    {
        if (time <= frameEndTimes_[i])
            return frameSprites_[i];
    }

    return 0;
}

}