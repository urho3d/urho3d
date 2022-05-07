// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/ProcessUtils.h"

#if defined(_WIN32) && !defined(URHO3D_WIN32_CONSOLE)
#include "../Core/MiniDump.h"
#include <windows.h>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif
#endif

// Define a platform-specific main function, which in turn executes the user-defined function

// MSVC debug mode: use memory leak reporting
#if defined(_MSC_VER) && defined(_DEBUG) && !defined(URHO3D_WIN32_CONSOLE)
#define URHO3D_DEFINE_MAIN(function) \
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) \
{ \
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); \
    Urho3D::ParseArguments(GetCommandLineW()); \
    return function; \
}
// MSVC release mode: write minidump on crash
#elif defined(_MSC_VER) && defined(URHO3D_MINIDUMPS) && !defined(URHO3D_WIN32_CONSOLE)
#define URHO3D_DEFINE_MAIN(function) \
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) \
{ \
    Urho3D::ParseArguments(GetCommandLineW()); \
    int exitCode; \
    __try \
    { \
        exitCode = function; \
    } \
    __except(Urho3D::WriteMiniDump("Urho3D", GetExceptionInformation())) \
    { \
    } \
    return exitCode; \
}
// Other Win32 or minidumps disabled: just execute the function
#elif defined(_WIN32) && !defined(URHO3D_WIN32_CONSOLE)
#define URHO3D_DEFINE_MAIN(function) \
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) \
{ \
    Urho3D::ParseArguments(GetCommandLineW()); \
    return function; \
}
// Android or iOS or tvOS: use SDL_main
#elif defined(__ANDROID__) || defined(IOS) || defined(TVOS)
#define URHO3D_DEFINE_MAIN(function) \
extern "C" __attribute__((visibility("default"))) int SDL_main(int argc, char** argv); \
int SDL_main(int argc, char** argv) \
{ \
    Urho3D::ParseArguments(argc, argv); \
    return function; \
}
// Linux or OS X: use main
#else
#define URHO3D_DEFINE_MAIN(function) \
int main(int argc, char** argv) \
{ \
    Urho3D::ParseArguments(argc, argv); \
    return function; \
}
#endif
