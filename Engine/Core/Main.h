//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#pragma once

#include "ProcessUtils.h"

#ifdef WIN32
#include "MiniDump.h"
#include <windows.h>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif
#endif

using namespace Urho3D;

// Define a platform-specific main function, which in turn executes the user-defined function

// MSVC debug mode: use memory leak reporting
#if defined(_MSC_VER) && defined(_DEBUG)
#define DEFINE_MAIN(function) \
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) \
{ \
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); \
    ParseArguments(GetCommandLineW()); \
    function; \
    return 0; \
}
// MSVC release mode: write minidump on crash
#elif defined(_MSC_VER) && defined(ENABLE_MINIDUMPS)
#define DEFINE_MAIN(function) \
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) \
{ \
    ParseArguments(GetCommandLineW()); \
    __try \
    { \
        function; \
    } \
    __except(WriteMiniDump("Urho3D", GetExceptionInformation())) \
    { \
    } \
    return 0; \
}
// Other Win32 or minidumps disabled: just execute the function
#elif defined(WIN32)
#define DEFINE_MAIN(function) \
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) \
{ \
    ParseArguments(GetCommandLineW()); \
    function; \
    return 0; \
}
// Android or iOS: use SDL_main
#elif defined(ANDROID) || defined(IOS)
#define DEFINE_MAIN(function) \
extern "C" int SDL_main(int argc, char** argv); \
int SDL_main(int argc, char** argv) \
{ \
    ParseArguments(argc, argv); \
    function; \
    return 0; \
}
// Linux or OS X: use main
#else
#define DEFINE_MAIN(function) \
int main(int argc, char** argv) \
{ \
    ParseArguments(argc, argv); \
    function; \
    return 0; \
}
#endif
