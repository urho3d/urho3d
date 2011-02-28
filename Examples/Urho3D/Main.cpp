//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Exception.h"
#include "Application.h"
#include "ProcessUtils.h"

#include <windows.h>

#include "DebugNew.h"

void run(const char* cmdLine);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
    #if defined(_MSC_VER) && defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif
    
    #if defined(ENABLE_MINIDUMPS) && !defined(_DEBUG)
    __try
    {
        run(cmdLine);
    }
    __except(writeMiniDump("Urho3D", GetExceptionInformation())) {}
    #else
    run(cmdLine);
    #endif
    
    return 0;
}

void run(const char* cmdLine)
{
    parseArguments(cmdLine);
    
    #if !defined(_MSC_VER) || !defined(_DEBUG)
    std::string error;
    try
    {
        Application application;
        application.run();
    }
    catch (Exception& e)
    {
        error = e.whatStr();
    }
    // Let the rendering window close first before showing the error dialog
    if (!error.empty())
        errorDialog("Urho3D", error);
    #else
    Application application;
    application.run();
    #endif
}
