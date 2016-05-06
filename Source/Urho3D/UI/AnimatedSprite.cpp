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

#include "../Core/Context.h"
#include "../Core/CoreEvents.h"
#include "../UI/AnimatedSprite.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* UI_CATEGORY;

AnimatedSprite::AnimatedSprite(Context* context) :
    Sprite(context),
    time_(0.0f),
    speed_(0.0f),
    numFrames_(1),
    columns_(M_MAX_UNSIGNED)
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(AnimatedSprite, HandleUpdate));
}

void AnimatedSprite::RegisterObject(Context* context)
{
    context->RegisterFactory<AnimatedSprite>(UI_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(Sprite);
    URHO3D_ACCESSOR_ATTRIBUTE("Time", GetTime, SetTime, float, 0.0f, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Speed", GetSpeed, SetSpeed, float, 0.0f, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Number of Frames", GetNumFrames, SetNumFrames, unsigned, 1, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Columns", GetColumns, SetColumns, unsigned, M_MAX_UNSIGNED, AM_FILE);
}

void AnimatedSprite::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    time_ += timeStep;
    FixupTime();
}

void AnimatedSprite::FixupTime()
{
    if (speed_ < M_EPSILON)
        time_ = 0.0f;
    else
        time_ = fmod(time_, numFrames_ / speed_);
}

void AnimatedSprite::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    bool allOpaque = true;
    if (GetDerivedOpacity() < 1.0f || color_[C_TOPLEFT].a_ < 1.0f || color_[C_TOPRIGHT].a_ < 1.0f ||
        color_[C_BOTTOMLEFT].a_ < 1.0f || color_[C_BOTTOMRIGHT].a_ < 1.0f)
        allOpaque = false;

    const IntVector2& size = GetSize();
    UIBatch batch(this, blendMode_ == BLEND_REPLACE && !allOpaque ? BLEND_ALPHA : blendMode_,
                  currentScissor, texture_, &vertexData);

    int frameWidth = imageRect_.right_ - imageRect_.left_;
    int frameHeight = imageRect_.bottom_ - imageRect_.top_;
    int frameIndex = (int)fmod(time_ * speed_, (float)numFrames_);
    int row = frameIndex / columns_;
    int column = frameIndex % columns_;
    int texOffsetX = imageRect_.left_ + frameWidth * column;
    int texOffsetY = imageRect_.top_ + frameHeight * row;

    batch.AddQuad(GetTransform(), 0, 0, size.x_, size.y_, texOffsetX, texOffsetY, frameWidth, frameHeight);

    UIBatch::AddOrMerge(batch, batches);

    // Reset hovering for next frame.
    hovering_ = false;
}

void AnimatedSprite::SetNumFrames(unsigned numFrames)
{
    numFrames_ = numFrames;

    if (numFrames_ == 0)
        numFrames_ = 1;

    FixupTime();
}

void AnimatedSprite::SetColumns(unsigned columns)
{
    columns_ = columns;

    if (columns_ == 0)
        columns_ = 1;
}

void AnimatedSprite::SetSpeed(float speed)
{
    speed_ = speed;
    FixupTime();
}

void AnimatedSprite::SetTime(float time)
{
    time_ = time;
    FixupTime();
}

}
