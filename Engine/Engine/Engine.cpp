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

#include "Precompiled.h"
#include "Audio.h"
#include "Console.h"
#include "Context.h"
#include "CoreEvents.h"
#include "DebugHud.h"
#include "Engine.h"
#include "FileSystem.h"
#include "Graphics.h"
#include "Input.h"
#include "Log.h"
#include "Network.h"
#include "PackageFile.h"
#include "PhysicsWorld.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "Script.h"
#include "ScriptAPI.h"
#include "StringUtils.h"
#include "UI.h"

#include "DebugNew.h"

OBJECTTYPESTATIC(Engine);

Engine::Engine(Context* context) :
    Object(context),
    minFps_(10),
    maxFps_(200),
    maxInactiveFps_(50),
    timeStep_(0),
    initialized_(false),
    exiting_(false),
    headless_(false)
{
}

Engine::~Engine()
{
}

bool Engine::Initialize(const String& windowTitle, const String& logName, const Vector<String>& arguments)
{
    if (initialized_)
        return true;
    
    RenderMode mode = RENDER_FORWARD;
    int width = 0;
    int height = 0;
    int multiSample = 1;
    int buffer = 100;
    int mixRate = 44100;
    bool fullscreen = true;
    bool vsync = false;
    bool forceSM2 = false;
    bool shadows = true;
    bool sound = true;
    bool stereo = true;
    bool interpolate = true;
    
    for (unsigned i = 0; i < arguments.Size(); ++i)
    {
        if (arguments[i][0] == '-' && arguments[i].Length() >= 2)
        {
            String argument = arguments[i].Substring(1).ToLower();
            
            if (argument == "headless")
                headless_ = true;
            else if (argument == "deferred")
                mode = RENDER_DEFERRED;
            else if (argument == "nolimit")
                SetMaxFps(0);
            else if (argument == "nosound")
                sound = false;
            else if (argument == "noip")
                interpolate = false;
            else if (argument == "mono")
                stereo = false;
            else if (argument == "noshadows")
                shadows = false;
            else if (argument == "sm2")
                forceSM2 = true;
            else
            {
                switch (tolower(argument[0]))
                {
                case 'x':
                    if (arguments[i].Length() > 1)
                        width = ToInt(argument.Substring(1));
                    break;
                    
                case 'y':
                    if (arguments[i].Length() > 1)
                        height = ToInt(argument.Substring(1));
                    break;
                
                case 'm':
                    if (arguments[i].Length() > 1)
                        multiSample = ToInt(argument.Substring(1));
                    break;
                    
                case 'b':
                    if (arguments[i].Length() > 1)
                        buffer = ToInt(argument.Substring(1));
                    break;
                    
                case 'r':
                    if (arguments[i].Length() > 1)
                        mixRate = ToInt(argument.Substring(1));
                    break;
                    
                case 'v':
                    vsync = true;
                    break;
                    
                case 'f':
                    fullscreen = true;
                    break;
                    
                case 'w':
                    fullscreen = false;
                    break;
                }
            }
        }
    }
    
    // Register object factories and attributes first, then subsystems
    RegisterObjects();
    RegisterSubsystems();
    
    // Start logging
    Log* log = GetSubsystem<Log>();
    log->Open(logName);
    
    // Add default resource paths: CoreData package or directory, Data package or directory, system fonts directory
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    String exePath = fileSystem->GetProgramDir();
    if (fileSystem->FileExists(exePath + "CoreData.pak"))
    {
        SharedPtr<PackageFile> package(new PackageFile(context_));
        package->Open(exePath + "CoreData.pak");
        cache->AddPackageFile(package);
    }
    else if (fileSystem->DirExists(exePath + "CoreData"))
        cache->AddResourcePath(exePath + "CoreData");
    if (fileSystem->FileExists(exePath + "Data.pak"))
    {
        SharedPtr<PackageFile> package(new PackageFile(context_));
        package->Open(exePath + "Data.pak");
        cache->AddPackageFile(package);
    }
    else if (fileSystem->DirExists(exePath + "Data"))
        cache->AddResourcePath(exePath + "Data");
    
    // Initialize graphics & audio output
    if (!headless_)
    {
        Graphics* graphics = GetSubsystem<Graphics>();
        graphics->SetForceSM2(forceSM2);
        if (!graphics->SetMode(mode, width, height, fullscreen, vsync, multiSample))
            return false;
        graphics->SetWindowTitle(windowTitle);
        if (!shadows)
            GetSubsystem<Renderer>()->SetDrawShadows(false);
        if (sound)
            GetSubsystem<Audio>()->SetMode(buffer, mixRate, stereo, interpolate);
    }
    
    frameTimer_.Reset();
    
    initialized_ = true;
    return true;
}

bool Engine::InitializeScripting()
{
    if (!initialized_)
        return false;
    
    // Check if scripting already initialized
    if (GetSubsystem<Script>())
        return true;
    
    RegisterScriptLibrary(context_);
    context_->RegisterSubsystem(new Script(context_));
   
    {
        PROFILE(RegisterScriptAPI);
        
        asIScriptEngine* engine = GetSubsystem<Script>()->GetScriptEngine();
        RegisterMathAPI(engine);
        RegisterCoreAPI(engine);
        RegisterIOAPI(engine);
        RegisterResourceAPI(engine);
        RegisterSceneAPI(engine);
        RegisterGraphicsAPI(engine);
        RegisterInputAPI(engine);
        RegisterAudioAPI(engine);
        RegisterUIAPI(engine);
        RegisterNetworkAPI(engine);
        RegisterPhysicsAPI(engine);
        RegisterScriptAPI(engine);
        RegisterEngineAPI(engine);
    }
    
    return true;
}

void Engine::RunFrame()
{
    if (!initialized_ || exiting_)
        return;
    
    if (!headless_)
    {
        if (!GetSubsystem<Graphics>()->IsInitialized())
        {
            Exit();
            return;
        }
    }
    
    Time* time = GetSubsystem<Time>();
    time->BeginFrame(timeStep_);
    
    Render();
    
    // If scripting initialized, garbage collect before getting the next time step
    Script* script = GetSubsystem<Script>();
    if (script)
        script->GarbageCollect(false);
    
    GetNextTimeStep();
    
    time->EndFrame();
}

Console* Engine::CreateConsole()
{
    if (headless_ || !initialized_)
        return 0;
    context_->RegisterSubsystem(new Console(context_));
    return GetSubsystem<Console>();
}

DebugHud* Engine::CreateDebugHud()
{
    if (headless_ || !initialized_)
        return 0;
    context_->RegisterSubsystem(new DebugHud(context_));
    return GetSubsystem<DebugHud>();
}

void Engine::SetMinFps(int fps)
{
    minFps_ = Max(fps, 0);
}

void Engine::SetMaxFps(int fps)
{
    maxFps_ = Max(fps, 0);
}

void Engine::SetMaxInactiveFps(int fps)
{
    maxInactiveFps_ = Max(fps, 0);
}

void Engine::Exit()
{
    Graphics* graphics = GetSubsystem<Graphics>();
    if (graphics)
        graphics->Close();
    
    exiting_ = true;
}

void Engine::DumpProfilingData()
{
    Profiler* profiler = GetSubsystem<Profiler>();
    if (profiler)
    {
        profiler->EndFrame();
        LOGRAW(profiler->GetData(true, false, true) + "\n");
    }
}

void Engine::DumpResources()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    const Map<ShortStringHash, ResourceGroup>& resourceGroups = cache->GetAllResources();
    LOGRAW("\n");
    
    for (Map<ShortStringHash, ResourceGroup>::ConstIterator i = resourceGroups.Begin();
        i != resourceGroups.End(); ++i)
    {
        unsigned num = i->second_.resources_.Size();
        unsigned memoryUse = i->second_.memoryUse_;
        
        if (num)
        {
            LOGRAW("Resource type " + i->second_.resources_.Begin()->second_->GetTypeName() +
                ": count " + num + " memory use " + String(memoryUse) + "\n");
        }
    }
    
    LOGRAW("Total memory use of all resources " + String(cache->GetTotalMemoryUse()) + "\n\n");
}

void Engine::Render()
{
    Graphics* graphics = GetSubsystem<Graphics>();
    
    // Do not render if device lost
    if (graphics && graphics->BeginFrame())
    {
        GetSubsystem<Renderer>()->Render();
        GetSubsystem<UI>()->Render();
        graphics->EndFrame();
    }
}

void Engine::GetNextTimeStep()
{
    PROFILE(ApplyFrameLimiter);
    
    if (!initialized_)
        return;
    
    int maxFps = maxFps_;
    Input* input = GetSubsystem<Input>();
    if (input && !input->IsActive())
        maxFps = maxInactiveFps_;
    
    int timeAcc = 0;
    
    if (maxFps)
    {
        int targetMax = 1000 / maxFps;
        for (;;)
        {
            timeAcc += frameTimer_.GetMSec(true);
            if (timeAcc >= targetMax)
                break;
            
            unsigned wait = (targetMax - timeAcc);
            Time::Sleep(wait / 2);
        }
    }
    else
        timeAcc = frameTimer_.GetMSec(true);
    
    // If FPS lower than minimum, clamp elapsed time
    if (minFps_)
    {
        int targetMin = 1000 / minFps_;
        if (timeAcc > targetMin)
            timeAcc = targetMin;
    }
    
    timeStep_ = timeAcc;
}

void Engine::RegisterObjects()
{
    RegisterResourceLibrary(context_);
    RegisterSceneLibrary(context_);
    RegisterGraphicsLibrary(context_);
    RegisterAudioLibrary(context_);
    RegisterUILibrary(context_);
    RegisterPhysicsLibrary(context_);
}

void Engine::RegisterSubsystems()
{
    // Register self as a subsystem
    context_->RegisterSubsystem(this);
    
    // Create and register the rest of the subsystems
    context_->RegisterSubsystem(new Time(context_));
    #ifdef ENABLE_PROFILING
    context_->RegisterSubsystem(new Profiler(context_));
    #endif
    context_->RegisterSubsystem(new Log(context_));
    context_->RegisterSubsystem(new FileSystem(context_));
    context_->RegisterSubsystem(new ResourceCache(context_));
    context_->RegisterSubsystem(new Network(context_));
    
    if (!headless_)
    {
        context_->RegisterSubsystem(new Graphics(context_));
        context_->RegisterSubsystem(new Renderer(context_));
    }
    
    context_->RegisterSubsystem(new Input(context_));
    context_->RegisterSubsystem(new UI(context_));
    context_->RegisterSubsystem(new Audio(context_));
}
