// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Scene/Component.h"

namespace Urho3D
{

/// %Sound listener component.
class URHO3D_API SoundListener : public Component
{
    URHO3D_OBJECT(SoundListener, Component);

public:
    /// Construct.
    explicit SoundListener(Context* context);
    /// Destruct.
    ~SoundListener() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);
};

}
