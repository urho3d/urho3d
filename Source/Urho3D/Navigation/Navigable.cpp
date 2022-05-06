// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Navigation/Navigable.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* NAVIGATION_CATEGORY;

Navigable::Navigable(Context* context) :
    Component(context),
    recursive_(true)
{
}

Navigable::~Navigable() = default;

void Navigable::RegisterObject(Context* context)
{
    context->RegisterFactory<Navigable>(NAVIGATION_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Recursive", bool, recursive_, true, AM_DEFAULT);
}

void Navigable::SetRecursive(bool enable)
{
    recursive_ = enable;
}

}
