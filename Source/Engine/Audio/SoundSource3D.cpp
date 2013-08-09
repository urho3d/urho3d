//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Audio.h"
#include "Context.h"
#include "Node.h"
#include "Sound.h"
#include "SoundListener.h"
#include "SoundSource3D.h"

#include "DebugNew.h"

namespace Urho3D
{

static const float DEFAULT_NEARDISTANCE = 0.0f;
static const float DEFAULT_FARDISTANCE = 100.0f;
static const float DEFAULT_ROLLOFF = 2.0f;
static const float MIN_ROLLOFF = 0.1f;

extern const char* AUDIO_CATEGORY;

SoundSource3D::SoundSource3D(Context* context) :
    SoundSource(context),
    nearDistance_(DEFAULT_NEARDISTANCE),
    farDistance_(DEFAULT_FARDISTANCE),
    rolloffFactor_(DEFAULT_ROLLOFF)
{
    // Start from zero volume until attenuation properly calculated
    attenuation_ = 0.0f;
}

void SoundSource3D::RegisterObject(Context* context)
{
    context->RegisterFactory<SoundSource3D>(AUDIO_CATEGORY);

    COPY_BASE_ATTRIBUTES(SoundSource3D, SoundSource);
    // Remove Attenuation and Panning as attribute as they are constantly being updated
    REMOVE_ATTRIBUTE(SoundSource3D, "Attenuation");
    REMOVE_ATTRIBUTE(SoundSource3D, "Panning");
    ATTRIBUTE(SoundSource3D, VAR_FLOAT, "Near Distance", nearDistance_, DEFAULT_NEARDISTANCE, AM_DEFAULT);
    ATTRIBUTE(SoundSource3D, VAR_FLOAT, "Far Distance", farDistance_, DEFAULT_FARDISTANCE, AM_DEFAULT);
    ATTRIBUTE(SoundSource3D, VAR_FLOAT, "Rolloff Factor", rolloffFactor_, DEFAULT_ROLLOFF, AM_DEFAULT);
}

void SoundSource3D::Update(float timeStep)
{
    CalculateAttenuation();
    SoundSource::Update(timeStep);
}

void SoundSource3D::SetDistanceAttenuation(float nearDistance, float farDistance, float rolloffFactor)
{
    nearDistance_ = Max(nearDistance, 0.0f);
    farDistance_ = Max(farDistance, 0.0f);
    rolloffFactor_ = Max(rolloffFactor, MIN_ROLLOFF);
    MarkNetworkUpdate();
}

void SoundSource3D::SetFarDistance(float distance)
{
    farDistance_ = Max(distance, 0.0f);
    MarkNetworkUpdate();
}

void SoundSource3D::SetNearDistance(float distance)
{
    nearDistance_ = Max(distance, 0.0f);
    MarkNetworkUpdate();
}

void SoundSource3D::SetRolloffFactor(float factor)
{
    rolloffFactor_ = Max(factor, MIN_ROLLOFF);
    MarkNetworkUpdate();
}

void SoundSource3D::CalculateAttenuation()
{
    if (!audio_)
        return;

    float interval = farDistance_ - nearDistance_;
    if (interval > 0.0f && node_)
    {
        SoundListener* listener = audio_->GetListener();

        // Listener must either be sceneless or in the same scene, else attenuate sound to silence
        if (listener && listener->IsEnabledEffective() && (!listener->GetScene() || listener->GetScene() == GetScene()))
        {
            Node* listenerNode = listener->GetNode();
            Vector3 relativePos(listenerNode->GetWorldRotation().Inverse() * (node_->GetWorldPosition() - listenerNode->GetWorldPosition()));
            float distance = Clamp(relativePos.Length() - nearDistance_, 0.0f, interval);
            float attenuation = powf(1.0f - distance / interval, rolloffFactor_);
            float panning = relativePos.Normalized().x_;

            attenuation_ = attenuation;
            panning_ = panning;
        }
        else
            attenuation_ = 0.0f;
    }
    else
        attenuation_ = 0.0f;
}

}
