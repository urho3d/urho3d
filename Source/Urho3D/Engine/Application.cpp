// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Engine/Application.h"
#include "../IO/IOEvents.h"
#include "../IO/Log.h"

#if defined(IOS) || defined(TVOS)
#include "../Graphics/Graphics.h"
#include <SDL/SDL.h>
#endif

#include "../DebugNew.h"

namespace Urho3D
{

#if defined(IOS) || defined(TVOS) || defined(__EMSCRIPTEN__)
// Code for supporting SDL_iPhoneSetAnimationCallback() and emscripten_set_main_loop_arg()
#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#endif
void RunFrame(void* data)
{
    static_cast<Engine*>(data)->RunFrame();
}
#endif

Application::Application(Context* context) :
    Object(context),
    exitCode_(EXIT_SUCCESS)
{
    engineParameters_ = Engine::ParseParameters(GetArguments());

    // Create the Engine, but do not initialize it yet. Subsystems except Graphics & Renderer are registered at this point
    engine_ = new Engine(context);

    // Subscribe to log messages so that can show errors if ErrorExit() is called with empty message
    SubscribeToEvent(E_LOGMESSAGE, URHO3D_HANDLER(Application, HandleLogMessage));
}

int Application::Run()
{
#if !defined(__GNUC__) || __EXCEPTIONS
    try
    {
#endif
        Setup();
        if (exitCode_)
            return exitCode_;

        if (!engine_->Initialize(engineParameters_))
        {
            ErrorExit();
            return exitCode_;
        }

        Start();
        if (exitCode_)
            return exitCode_;

        // Platforms other than iOS/tvOS and Emscripten run a blocking main loop
#if !defined(IOS) && !defined(TVOS) && !defined(__EMSCRIPTEN__)
        while (!engine_->IsExiting())
            engine_->RunFrame();

        Stop();
        // iOS/tvOS will setup a timer for running animation frames so eg. Game Center can run. In this case we do not
        // support calling the Stop() function, as the application will never stop manually
#else
#if defined(IOS) || defined(TVOS)
        SDL_iPhoneSetAnimationCallback(GetSubsystem<Graphics>()->GetWindow(), 1, &RunFrame, engine_);
#elif defined(__EMSCRIPTEN__)
        emscripten_set_main_loop_arg(RunFrame, engine_, 0, 1);
#endif
#endif

        return exitCode_;
#if !defined(__GNUC__) || __EXCEPTIONS
    }
    catch (std::bad_alloc&)
    {
        ErrorDialog(GetTypeName(), "An out-of-memory error occurred. The application will now exit.");
        return EXIT_FAILURE;
    }
#endif
}

void Application::ErrorExit(const String& message)
{
    engine_->Exit(); // Close the rendering window
    exitCode_ = EXIT_FAILURE;

    if (!message.Length())
    {
        ErrorDialog(GetTypeName(), startupErrors_.Length() ? startupErrors_ :
            "Application has been terminated due to unexpected error.");
    }
    else
        ErrorDialog(GetTypeName(), message);
}

void Application::HandleLogMessage(StringHash eventType, VariantMap& eventData)
{
    using namespace LogMessage;

    if (eventData[P_LEVEL].GetInt() == LOG_ERROR)
    {
        // Strip the timestamp if necessary
        String error = eventData[P_MESSAGE].GetString();
        unsigned bracketPos = error.Find(']');
        if (bracketPos != String::NPOS)
            error = error.Substring(bracketPos + 2);

        startupErrors_ += error + "\n";
    }
}


}
