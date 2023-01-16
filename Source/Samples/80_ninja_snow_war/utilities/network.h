// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include <Urho3D/Container/Str.h>

namespace Urho3D
{

inline bool runServer = false;
inline bool runClient = false;
inline String serverAddress;
inline u16 serverPort = 1234;
inline String userName;
inline bool nobgm = false; // Без фоновой музыки

void ParseNetworkArguments();

} // namespace Urho3D
