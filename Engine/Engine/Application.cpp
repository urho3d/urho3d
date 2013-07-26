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
#include "Application.h"
#include "Engine.h"
#include "ProcessUtils.h"

#include <exception>

#include "DebugNew.h"

Application::Application(Context* context) :
    Object(context)
{
    engineParameters_ = Engine::ParseParameters(GetArguments());

    // Create the Engine, but do not initialize it yet. Subsystems except Graphics & Renderer are registered at this point
    engine_ = new Engine(context);
}

Application::~Application()
{
}

int Application::Run()
{
    try
    {
        int exitCode = Setup();
        if (exitCode)
            return exitCode;

        if (!engine_->Initialize(engineParameters_))
            return EXIT_FAILURE;

        exitCode = Start();
        if (exitCode)
            return exitCode;

        while (!engine_->IsExiting())
            engine_->RunFrame();

        exitCode = Stop();
        return exitCode;
    }
    catch (std::bad_alloc&)
    {
        ErrorDialog(GetTypeName(), "An out-of-memory error occurred. The application will now exit.");
        return EXIT_FAILURE;
    }
}
