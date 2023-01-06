// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#ifdef _WIN32

// Avoid using byte in rpcndr.h
#define byte BYTE
#include <windows.h>
#undef byte

#endif // def _WIN32
