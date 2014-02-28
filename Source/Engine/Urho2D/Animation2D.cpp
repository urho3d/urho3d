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
    keyFrames_.Clear();
    keyFrameTimes_.Clear();

    SharedPtr<XMLFile> xmlFile(new XMLFile(context_));
    if(!xmlFile->Load(source))
    {
        LOGERROR("Could not load animation");
        return false;
    }

    SetMemoryUse(source.GetSize());

    XMLElement rootElem = xmlFile->GetRoot("Animaiton");
    if (!rootElem)
    {
        LOGERROR("Invalid animation");
        return false;
    }

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    XMLElement keyFrameElem = rootElem.GetChild("KeyFrame");
    if (!keyFrameElem)
    {
        LOGERROR("Could not found key frame");
        return false;
    }
    
    float totalTime = 0.0f;

    while (keyFrameElem)
    {
        KeyFrame2D keyFrame;
        keyFrame.duration_ = keyFrameElem.GetFloat("duration");

        Vector<String> names = keyFrameElem.GetAttribute("sprite").Split('@');
        if (names.Size() == 1)
        {
            Sprite2D* sprite = cache->GetResource<Sprite2D>(names[0]);
            if (!sprite)
            {
                LOGERROR("Could not get sprite");
                return false;
            }

            keyFrame.sprite_ = sprite;
        }
        else
        {
            SpriteSheet2D* spriteSheet = cache->GetResource<SpriteSheet2D>(names[0]);
            if (!spriteSheet)
            {
                LOGERROR("Could not get sprite speet");
                return false;
            }

            Sprite2D* sprite = spriteSheet->GetSprite(names[1]);
            if (!sprite)
            {
                LOGERROR("Could not get sprite");
                return false;
            }

            keyFrame.sprite_ = sprite;
        }

        keyFrames_.Push(keyFrame);

        totalTime += keyFrame.duration_;
        keyFrameTimes_.Push(totalTime);

        keyFrameElem = keyFrameElem.GetNext("KeyFrame");
    }

    return true;
}

bool Animation2D::Save(Serializer& dest) const
{
    return false;
}

float Animation2D::GetTotalTime() const
{
    return keyFrameTimes_.Empty() ? 0.0f : keyFrameTimes_.Back();
}

unsigned Animation2D::GetNumKeyFrames() const
{
    return keyFrames_.Size();
}

const KeyFrame2D* Animation2D::GetKeyFrameByTime(float time) const
{
    if (time < 0.0f)
        return 0;

    for (unsigned i = 0; i < keyFrameTimes_.Size(); ++i)
    {
        if (time < keyFrameTimes_[i])
            return &keyFrames_[i];
    }

    return 0;
}

const KeyFrame2D* Animation2D::GetKeyFrameByIndex(unsigned index) const
{
    return index < keyFrames_.Size() ? &keyFrames_[index] : 0;
}

}