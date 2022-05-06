// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Audio/SoundListener.h"
#include "../Core/Context.h"

namespace Urho3D
{

extern const char* AUDIO_CATEGORY;

SoundListener::SoundListener(Context* context) :
    Component(context)
{
}

SoundListener::~SoundListener() = default;

void SoundListener::RegisterObject(Context* context)
{
    context->RegisterFactory<SoundListener>(AUDIO_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
}

}
