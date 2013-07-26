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

#pragma once

#include "Main.h"
#include "Object.h"

namespace Urho3D
{

class Engine;

/// Base class for creating applications which initialize the Urho3D engine and run a main loop until exited.
class Application : public Object
{
    OBJECT(Application);
    
public:
    /// Construct. Parse default engine parameters from the command line, and create the engine in an uninitialized state.
    Application(Context* context);

    /// Destruct.
    ~Application();

    /// Setup before engine initialization. This is a chance to eg. modify the engine parameters. Return nonzero to terminate with an error exit code without initializing the engine.
    virtual int Setup() { return 0; }

    /// Startup after engine initialization and before running the main loop. Return nonzero to terminate with an error exit code without running the main loop.
    virtual int Start() { return 0; }

    /// Cleanup after the main loop. Return the exit code for the application.
    virtual int Stop() { return 0; }

    /// Initialize the engine and run the main loop, then return the application exit code. Catch out-of-memory exceptions while running.
    int Run();

protected:
    /// Urho3D engine.
    SharedPtr<Engine> engine_;
    /// Engine parameters map.
    VariantMap engineParameters_;
};

// Macro for defining a main function which creates a Context and the application, then runs it
#define DEFINE_APPLICATION_MAIN(className) \
int RunApplication() \
{ \
    SharedPtr<Context> context(new Context()); \
    SharedPtr<className> application(new className(context)); \
    return application->Run(); \
} \
DEFINE_MAIN(RunApplication());

}