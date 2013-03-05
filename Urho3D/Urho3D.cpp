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

#include "Context.h"
#include "Engine.h"
#include "FileSystem.h"
#include "Log.h"
#include "Main.h"
#include "ProcessUtils.h"
#include "ResourceCache.h"
#include "ResourceEvents.h"
#include "ScriptFile.h"

#include <exception>

#include "DebugNew.h"

using namespace Urho3D;

class Application : public Object
{
    OBJECT(Application);
    
public:
    Application(Context* context);
    int Run(const String& scriptFileName);
    
private:
    void ErrorExit();
    void HandleScriptReloadStarted(StringHash eventType, VariantMap& eventData);
    void HandleScriptReloadFinished(StringHash eventType, VariantMap& eventData);
    void HandleScriptReloadFailed(StringHash eventType, VariantMap& eventData);
    int exitCode_;
};

int Run()
{
    try
    {
        // Check for script file name
        const Vector<String>& arguments = GetArguments();
        String scriptFileName;
        for (unsigned i = 0; i < arguments.Size(); ++i)
        {
            if (arguments[i][0] != '-')
            {
                scriptFileName = GetInternalPath(arguments[i]);
                break;
            }
        }
        
        #if defined(ANDROID) || defined(IOS)
        // Can not pass script name on mobile devices, so choose a hardcoded default
        scriptFileName = "Scripts/NinjaSnowWar.as";
        #endif
        
        // Show usage if not found
        if (scriptFileName.Empty())
        {
            ErrorDialog("Urho3D", "Usage: Urho3D <scriptfile> [options]\n\n"
                "The script file should implement the function void Start() for initializing the "
                "application and subscribing to all necessary events, such as the frame update.\n"
                #ifndef WIN32
                "\nCommand line options:\n"
                "-x<res>     Horizontal resolution\n"
                "-y<res>     Vertical resolution\n"
                "-m<level>   Enable hardware multisampling\n"
                "-v          Enable vertical sync\n"
                "-t          Enable triple buffering\n"
                "-w          Start in windowed mode\n"
                "-s          Enable resizing when in windowed mode\n"
                "-q          Enable quiet mode which does not log to standard output stream\n"
                "-b<length>  Sound buffer length in milliseconds\n"
                "-r<freq>    Sound mixing frequency in Hz\n"
                "-headless   Headless mode. No application window will be created\n"
                "-log<level> Change the log level, valid 'level' values are 'debug', 'info', 'warning', 'error'\n"
                "-lqshadows  Use low-quality (1-sample) shadow filtering\n"
                "-noshadows  Disable shadow rendering\n"
                "-nolimit    Disable frame limiter\n"
                "-nothreads  Disable worker threads\n"
                "-nosound    Disable sound output\n"
                "-noip       Disable sound mixing interpolation\n"
                "-sm2        Force SM2.0 rendering\n"
                #endif
            );
            return EXIT_FAILURE;
        }
        
        // Create the execution context and the application object. The application object is needed to subscribe to events
        // which allow to live-reload the script.
        SharedPtr<Context> context(new Context());
        SharedPtr<Application> application(new Application(context));
        return application->Run(scriptFileName);
    }
    catch (std::bad_alloc&)
    {
        ErrorDialog("Urho3D", "An out-of-memory error occurred. The application will now exit.");
        return EXIT_FAILURE;
    }
}

OBJECTTYPESTATIC(Application);

Application::Application(Context* context) :
    Object(context),
    exitCode_(EXIT_SUCCESS)
{
}

int Application::Run(const String& scriptFileName)
{
    SharedPtr<Engine> engine(new Engine(context_));
    if (engine->Initialize("Urho3D", "Urho3D.log", GetArguments()))
    {
        // Hold a shared pointer to the script file to make sure it is not unloaded during runtime
        engine->InitializeScripting();
        SharedPtr<ScriptFile> scriptFile(context_->GetSubsystem<ResourceCache>()->GetResource<ScriptFile>(scriptFileName));
        
        // If script loading is successful, execute engine loop
        if (scriptFile && scriptFile->Execute("void Start()"))
        {
            // Subscribe to script's reload event to allow live-reload of the application
            SubscribeToEvent(scriptFile, E_RELOADSTARTED, HANDLER(Application, HandleScriptReloadStarted));
            SubscribeToEvent(scriptFile, E_RELOADFINISHED, HANDLER(Application, HandleScriptReloadFinished));
            SubscribeToEvent(scriptFile, E_RELOADFAILED, HANDLER(Application, HandleScriptReloadFailed));
            
            while (!engine->IsExiting())
                engine->RunFrame();
            
            if (scriptFile->GetFunction("void Stop()"))
                scriptFile->Execute("void Stop()");
            
            return exitCode_;
        }
    }
    
    ErrorExit();
    return exitCode_;
}

void Application::ErrorExit()
{
    Engine* engine = context_->GetSubsystem<Engine>();
    engine->Exit(); // Close the rendering window

    // Only for WIN32, otherwise the last message would be double posted on Mac OS X and Linux platforms
    #ifdef WIN32
    Log* log = context_->GetSubsystem<Log>();   // May be null if ENABLE_LOGGING is not defined during built
    ErrorDialog("Urho3D", log ? log->GetLastMessage() : "Application has been terminated due to unexpected error.");
    #endif
    
    exitCode_ = EXIT_FAILURE;
}

void Application::HandleScriptReloadStarted(StringHash eventType, VariantMap& eventData)
{
    ScriptFile* scriptFile = static_cast<ScriptFile*>(GetEventSender());
    if (scriptFile->GetFunction("void Stop()"))
        scriptFile->Execute("void Stop()");
}

void Application::HandleScriptReloadFinished(StringHash eventType, VariantMap& eventData)
{
    ScriptFile* scriptFile = static_cast<ScriptFile*>(GetEventSender());
    // Restart the script application after reload
    if (!scriptFile->Execute("void Start()"))
        ErrorExit();
}

void Application::HandleScriptReloadFailed(StringHash eventType, VariantMap& eventData)
{
    ErrorExit();
}

DEFINE_MAIN(Run());
