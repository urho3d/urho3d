// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include <Urho3D/Urho3DAll.h>

namespace Urho3D
{

struct Player
{
    i32 score;
    String name;
    NodeId nodeID;
    WeakPtr<Connection> connection;
    Controls lastControls;

    Player();
};

struct HiscoreEntry
{
    i32 score;
    String name;
};

} // namespace Urho3D

