// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file
/// @nobindfile

#pragma once

#include "../Core/Context.h"
#include "../Core/Main.h"
#include "../Engine/Engine.h"

namespace Urho3D
{

class Engine;

/// Base class for creating applications which initialize the Urho3D engine and run a main loop until exited.
class URHO3D_API Application : public Object
{
    URHO3D_OBJECT(Application, Object);

public:
    /// Construct. Parse default engine parameters from the command line, and create the engine in an uninitialized state.
    explicit Application(Context* context);

    /// Setup before engine initialization. This is a chance to eg. modify the engine parameters. Call ErrorExit() to terminate without initializing the engine. Called by Application.
    virtual void Setup() { }

    /// Setup after engine initialization and before running the main loop. Call ErrorExit() to terminate without running the main loop. Called by Application.
    virtual void Start() { }

    /// Cleanup after the main loop. Called by Application.
    virtual void Stop() { }

    /// Initialize the engine and run the main loop, then return the application exit code. Catch out-of-memory exceptions while running.
    int Run();
    /// Show an error message (last log message if empty), terminate the main loop, and set failure exit code.
    void ErrorExit(const String& message = String::EMPTY);

protected:
    /// Handle log message.
    void HandleLogMessage(StringHash eventType, VariantMap& eventData);

    /// Urho3D engine.
    SharedPtr<Engine> engine_;
    /// Engine parameters map.
    VariantMap engineParameters_;
    /// Collected startup error log messages.
    String startupErrors_;
    /// Application exit code.
    int exitCode_;
};

// Macro for defining a main function which creates a Context and the application, then runs it
#if !defined(IOS) && !defined(TVOS)
#define URHO3D_DEFINE_APPLICATION_MAIN(className) \
int RunApplication() \
{ \
    Urho3D::SharedPtr<Urho3D::Context> context(new Urho3D::Context()); \
    Urho3D::SharedPtr<className> application(new className(context)); \
    return application->Run(); \
} \
URHO3D_DEFINE_MAIN(RunApplication())
#else
// On iOS/tvOS we will let this function exit, so do not hold the context and application in SharedPtr's
#define URHO3D_DEFINE_APPLICATION_MAIN(className) \
int RunApplication() \
{ \
    Urho3D::Context* context = new Urho3D::Context(); \
    className* application = new className(context); \
    return application->Run(); \
} \
URHO3D_DEFINE_MAIN(RunApplication());
#endif

}
