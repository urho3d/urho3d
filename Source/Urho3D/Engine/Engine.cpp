//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Audio/Audio.h"
#include "../Engine/Console.h"
#include "../Core/Context.h"
#include "../Core/CoreEvents.h"
#include "../Engine/DebugHud.h"
#include "../Engine/Engine.h"
#include "../IO/FileSystem.h"
#include "../Graphics/Graphics.h"
#include "../Input/Input.h"
#include "../Input/InputEvents.h"
#include "../IO/Log.h"
#ifdef URHO3D_NAVIGATION
#include "../Navigation/NavigationMesh.h"
#endif
#ifdef URHO3D_NETWORK
#include "../Network/Network.h"
#endif
#include "../IO/PackageFile.h"
#ifdef URHO3D_PHYSICS
#include "../Physics/PhysicsWorld.h"
#endif
#include "../Core/ProcessUtils.h"
#include "../Core/Profiler.h"
#include "../Graphics/Renderer.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"
#include "../UI/UI.h"
#ifdef URHO3D_URHO2D
#include "../Urho2D/Urho2D.h"
#endif
#include "../Core/WorkQueue.h"
#include "../Resource/XMLFile.h"

#include "../DebugNew.h"

#if defined(_MSC_VER) && defined(_DEBUG)
// From dbgint.h
#define nNoMansLandSize 4

typedef struct _CrtMemBlockHeader
{
    struct _CrtMemBlockHeader* pBlockHeaderNext;
    struct _CrtMemBlockHeader* pBlockHeaderPrev;
    char* szFileName;
    int nLine;
    size_t nDataSize;
    int nBlockUse;
    long lRequest;
    unsigned char gap[nNoMansLandSize];
} _CrtMemBlockHeader;
#endif

namespace Urho3D
{

extern const char* logLevelPrefixes[];

Engine::Engine(Context* context) :
    Object(context),
    timeStep_(0.0f),
    timeStepSmoothing_(2),
    minFps_(10),
    #if defined(ANDROID) || defined(IOS) || defined(RPI)
    maxFps_(60),
    maxInactiveFps_(10),
    pauseMinimized_(true),
    #else
    maxFps_(200),
    maxInactiveFps_(60),
    pauseMinimized_(false),
    #endif
#ifdef URHO3D_TESTING
    timeOut_(0),
#endif
    autoExit_(true),
    initialized_(false),
    exiting_(false),
    headless_(false),
    audioPaused_(false)
{
    // Register self as a subsystem
    context_->RegisterSubsystem(this);

    // Create subsystems which do not depend on engine initialization or startup parameters
    context_->RegisterSubsystem(new Time(context_));
    context_->RegisterSubsystem(new WorkQueue(context_));
    #ifdef URHO3D_PROFILING
    context_->RegisterSubsystem(new Profiler(context_));
    #endif
    context_->RegisterSubsystem(new FileSystem(context_));
    #ifdef URHO3D_LOGGING
    context_->RegisterSubsystem(new Log(context_));
    #endif
    context_->RegisterSubsystem(new ResourceCache(context_));
    #ifdef URHO3D_NETWORK
    context_->RegisterSubsystem(new Network(context_));
    #endif
    context_->RegisterSubsystem(new Input(context_));
    context_->RegisterSubsystem(new Audio(context_));
    context_->RegisterSubsystem(new UI(context_));

    // Register object factories for libraries which are not automatically registered along with subsystem creation
    RegisterSceneLibrary(context_);

#ifdef URHO3D_PHYSICS
    RegisterPhysicsLibrary(context_);
#endif
    
#ifdef URHO3D_NAVIGATION
    RegisterNavigationLibrary(context_);
#endif

    SubscribeToEvent(E_EXITREQUESTED, HANDLER(Engine, HandleExitRequested));
}

Engine::~Engine()
{
}

bool Engine::Initialize(const VariantMap& parameters)
{
    if (initialized_)
        return true;

    PROFILE(InitEngine);

    // Set headless mode
    headless_ = GetParameter(parameters, "Headless", false).GetBool();

    // Register the rest of the subsystems
    if (!headless_)
    {
        context_->RegisterSubsystem(new Graphics(context_));
        context_->RegisterSubsystem(new Renderer(context_));
    }
    else
    {
        // Register graphics library objects explicitly in headless mode to allow them to work without using actual GPU resources
        RegisterGraphicsLibrary(context_);
    }

#ifdef URHO3D_URHO2D
    // 2D graphics library is dependent on 3D graphics library
    RegisterUrho2DLibrary(context_);
#endif

    // Start logging
    Log* log = GetSubsystem<Log>();
    if (log)
    {
        if (HasParameter(parameters, "LogLevel"))
            log->SetLevel(GetParameter(parameters, "LogLevel").GetInt());
        log->SetQuiet(GetParameter(parameters, "LogQuiet", false).GetBool());
        log->Open(GetParameter(parameters, "LogName", "Urho3D.log").GetString());
    }

    // Set maximally accurate low res timer
    GetSubsystem<Time>()->SetTimerPeriod(1);

    // Configure max FPS
    if (GetParameter(parameters, "FrameLimiter", true) == false)
        SetMaxFps(0);

    // Set amount of worker threads according to the available physical CPU cores. Using also hyperthreaded cores results in
    // unpredictable extra synchronization overhead. Also reserve one core for the main thread
    unsigned numThreads = GetParameter(parameters, "WorkerThreads", true).GetBool() ? GetNumPhysicalCPUs() - 1 : 0;
    if (numThreads)
    {
        GetSubsystem<WorkQueue>()->CreateThreads(numThreads);

        LOGINFOF("Created %u worker thread%s", numThreads, numThreads > 1 ? "s" : "");
    }

    // Add resource paths
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    FileSystem* fileSystem = GetSubsystem<FileSystem>();

    String resourcePrefixPath = AddTrailingSlash(GetParameter(parameters, "ResourcePrefixPath", getenv("URHO3D_PREFIX_PATH")).GetString());
    if (resourcePrefixPath.Empty())
        resourcePrefixPath = fileSystem->GetProgramDir();
    else if (!IsAbsolutePath(resourcePrefixPath))
        resourcePrefixPath = fileSystem->GetProgramDir() + resourcePrefixPath;
    Vector<String> resourcePaths = GetParameter(parameters, "ResourcePaths", "Data;CoreData").GetString().Split(';');
    Vector<String> resourcePackages = GetParameter(parameters, "ResourcePackages").GetString().Split(';');
    Vector<String> autoLoadPaths = GetParameter(parameters, "AutoloadPaths", "Autoload").GetString().Split(';');

    for (unsigned i = 0; i < resourcePaths.Size(); ++i)
    {
        bool success = false;

        // If path is not absolute, prefer to add it as a package if possible
        if (!IsAbsolutePath(resourcePaths[i]))
        {
            String packageName = resourcePrefixPath + resourcePaths[i] + ".pak";
            if (fileSystem->FileExists(packageName))
                success = cache->AddPackageFile(packageName);

            if (!success)
            {
                String pathName = resourcePrefixPath + resourcePaths[i];
                if (fileSystem->DirExists(pathName))
                    success = cache->AddResourceDir(pathName);
            }
        }
        else
        {
            String pathName = resourcePaths[i];
            if (fileSystem->DirExists(pathName))
                success = cache->AddResourceDir(pathName);
        }

        if (!success)
        {
            LOGERRORF("Failed to add resource path '%s', check the documentation on how to set the 'resource prefix path'", resourcePaths[i].CString());
            return false;
        }
    }

    // Then add specified packages
    for (unsigned i = 0; i < resourcePackages.Size(); ++i)
    {
        String packageName = resourcePrefixPath + resourcePackages[i];
        if (fileSystem->FileExists(packageName))
        {
            if (!cache->AddPackageFile(packageName))
            {
                LOGERRORF("Failed to add resource package '%s', check the documentation on how to set the 'resource prefix path'", resourcePackages[i].CString());
                return false;
            }
        }
        else
            LOGDEBUGF("Skip specified resource package '%s' as it does not exist, check the documentation on how to set the 'resource prefix path'", resourcePackages[i].CString());
    }
    
    // Add auto load folders. Prioritize these (if exist) before the default folders
    for (unsigned i = 0; i < autoLoadPaths.Size(); ++i)
    {
        String autoLoadPath(autoLoadPaths[i]);
        if (!IsAbsolutePath(autoLoadPath))
            autoLoadPath = resourcePrefixPath + autoLoadPath;

        if (fileSystem->DirExists(autoLoadPath))
        {
            // Add all the subdirs (non-recursive) as resource directory
            Vector<String> subdirs;
            fileSystem->ScanDir(subdirs, autoLoadPath, "*", SCAN_DIRS, false);
            for (unsigned y = 0; y < subdirs.Size(); ++y)
            {
                String dir = subdirs[y];
                if (dir.StartsWith("."))
                    continue;

                String autoResourceDir = autoLoadPath + "/" + dir;
                if (!cache->AddResourceDir(autoResourceDir, 0))
                {
                    LOGERRORF("Failed to add resource directory '%s' in autoload path %s, check the documentation on how to set the 'resource prefix path'", dir.CString(), autoLoadPaths[i].CString());
                    return false;
                }
            }

            // Add all the found package files (non-recursive)
            Vector<String> paks;
            fileSystem->ScanDir(paks, autoLoadPath, "*.pak", SCAN_FILES, false);
            for (unsigned y = 0; y < paks.Size(); ++y)
            {
                String pak = paks[y];
                if (pak.StartsWith("."))
                    continue;

                String autoPackageName = autoLoadPath + "/" + pak;
                if (!cache->AddPackageFile(autoPackageName, 0))
                {
                    LOGERRORF("Failed to add package file '%s' in autoload path %s, check the documentation on how to set the 'resource prefix path'", pak.CString(), autoLoadPaths[i].CString());
                    return false;
                }
            }
        }
        else
            LOGDEBUGF("Skipped autoload path '%s' as it does not exist, check the documentation on how to set the 'resource prefix path'", autoLoadPaths[i].CString());
    }

    // Initialize graphics & audio output
    if (!headless_)
    {
        Graphics* graphics = GetSubsystem<Graphics>();
        Renderer* renderer = GetSubsystem<Renderer>();

        if (HasParameter(parameters, "ExternalWindow"))
            graphics->SetExternalWindow(GetParameter(parameters, "ExternalWindow").GetVoidPtr());
        graphics->SetForceSM2(GetParameter(parameters, "ForceSM2", false).GetBool());
        graphics->SetWindowTitle(GetParameter(parameters, "WindowTitle", "Urho3D").GetString());
        graphics->SetWindowIcon(cache->GetResource<Image>(GetParameter(parameters, "WindowIcon", String::EMPTY).GetString()));
        graphics->SetFlushGPU(GetParameter(parameters, "FlushGPU", false).GetBool());
        graphics->SetOrientations(GetParameter(parameters, "Orientations", "LandscapeLeft LandscapeRight").GetString());

        if (HasParameter(parameters, "WindowPositionX") && HasParameter(parameters, "WindowPositionY"))
            graphics->SetWindowPosition(GetParameter(parameters, "WindowPositionX").GetInt(), GetParameter(parameters, "WindowPositionY").GetInt());

        if (!graphics->SetMode(
            GetParameter(parameters, "WindowWidth", 0).GetInt(),
            GetParameter(parameters, "WindowHeight", 0).GetInt(),
            GetParameter(parameters, "FullScreen", true).GetBool(),
            GetParameter(parameters, "Borderless", false).GetBool(),
            GetParameter(parameters, "WindowResizable", false).GetBool(),
            GetParameter(parameters, "VSync", false).GetBool(),
            GetParameter(parameters, "TripleBuffer", false).GetBool(),
            GetParameter(parameters, "MultiSample", 1).GetInt()
        ))
            return false;

        if (HasParameter(parameters, "DumpShaders"))
            graphics->BeginDumpShaders(GetParameter(parameters, "DumpShaders", String::EMPTY).GetString());
        if (HasParameter(parameters, "RenderPath"))
            renderer->SetDefaultRenderPath(cache->GetResource<XMLFile>(GetParameter(parameters, "RenderPath").GetString()));

        renderer->SetDrawShadows(GetParameter(parameters, "Shadows", true).GetBool());
        if (renderer->GetDrawShadows() && GetParameter(parameters, "LowQualityShadows", false).GetBool())
            renderer->SetShadowQuality(SHADOWQUALITY_LOW_16BIT);
        renderer->SetMaterialQuality(GetParameter(parameters, "MaterialQuality", QUALITY_HIGH).GetInt());
        renderer->SetTextureQuality(GetParameter(parameters, "TextureQuality", QUALITY_HIGH).GetInt());
        renderer->SetTextureFilterMode((TextureFilterMode)GetParameter(parameters, "TextureFilterMode", FILTER_TRILINEAR).GetInt());
        renderer->SetTextureAnisotropy(GetParameter(parameters, "TextureAnisotropy", 4).GetInt());
        
        if (GetParameter(parameters, "Sound", true).GetBool())
        {
            GetSubsystem<Audio>()->SetMode(
                GetParameter(parameters, "SoundBuffer", 100).GetInt(),
                GetParameter(parameters, "SoundMixRate", 44100).GetInt(),
                GetParameter(parameters, "SoundStereo", true).GetBool(),
                GetParameter(parameters, "SoundInterpolation", true).GetBool()
            );
        }
    }

    // Init FPU state of main thread
    InitFPU();

    // Initialize input
    if (HasParameter(parameters, "TouchEmulation"))
        GetSubsystem<Input>()->SetTouchEmulation(GetParameter(parameters, "TouchEmulation").GetBool());

    #ifdef URHO3D_TESTING
    if (HasParameter(parameters, "TimeOut"))
        timeOut_ = GetParameter(parameters, "TimeOut", 0).GetInt() * 1000000LL;
    #endif

    // In debug mode, check now that all factory created objects can be created without crashing
    #ifdef _DEBUG
    if (!resourcePaths.Empty())
    {
        const HashMap<StringHash, SharedPtr<ObjectFactory> >& factories = context_->GetObjectFactories();
        for (HashMap<StringHash, SharedPtr<ObjectFactory> >::ConstIterator i = factories.Begin(); i != factories.End(); ++i)
            SharedPtr<Object> object = i->second_->CreateObject();
    }
    #endif

    frameTimer_.Reset();

    LOGINFO("Initialized engine");
    initialized_ = true;
    return true;
}

void Engine::RunFrame()
{
    assert(initialized_);

    // If not headless, and the graphics subsystem no longer has a window open, assume we should exit
    if (!headless_ && !GetSubsystem<Graphics>()->IsInitialized())
        exiting_ = true;

    if (exiting_)
        return;

    // Note: there is a minimal performance cost to looking up subsystems (uses a hashmap); if they would be looked up several
    // times per frame it would be better to cache the pointers
    Time* time = GetSubsystem<Time>();
    Input* input = GetSubsystem<Input>();
    Audio* audio = GetSubsystem<Audio>();

    time->BeginFrame(timeStep_);

    // If pause when minimized -mode is in use, stop updates and audio as necessary
    if (pauseMinimized_ && input->IsMinimized())
    {
        if (audio->IsPlaying())
        {
            audio->Stop();
            audioPaused_ = true;
        }
    }
    else
    {
        // Only unpause when it was paused by the engine
        if (audioPaused_)
        {
            audio->Play();
            audioPaused_ = false;
        }

        Update();
    }

    Render();
    ApplyFrameLimit();

    time->EndFrame();
}

Console* Engine::CreateConsole()
{
    if (headless_ || !initialized_)
        return 0;

    // Return existing console if possible
    Console* console = GetSubsystem<Console>();
    if (!console)
    {
        console = new Console(context_);
        context_->RegisterSubsystem(console);
    }

    return console;
}

DebugHud* Engine::CreateDebugHud()
{
    if (headless_ || !initialized_)
        return 0;

     // Return existing debug HUD if possible
    DebugHud* debugHud = GetSubsystem<DebugHud>();
    if (!debugHud)
    {
        debugHud = new DebugHud(context_);
        context_->RegisterSubsystem(debugHud);
    }

    return debugHud;
}

void Engine::SetTimeStepSmoothing(int frames)
{
    timeStepSmoothing_ = Clamp(frames, 1, 20);
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

void Engine::SetPauseMinimized(bool enable)
{
    pauseMinimized_ = enable;
}

void Engine::SetAutoExit(bool enable)
{
    // On mobile platforms exit is mandatory if requested by the platform itself and should not be attempted to be disabled
#if defined(ANDROID) || defined(IOS)
    enable = true;
#endif
    autoExit_ = enable;
}

void Engine::SetNextTimeStep(float seconds)
{
    timeStep_ = Max(seconds, 0.0f);
}

void Engine::Exit()
{
#if defined(IOS)
    // On iOS it's not legal for the application to exit on its own, instead it will be minimized with the home key
#else
    DoExit();
#endif
}

void Engine::DumpProfiler()
{
    Profiler* profiler = GetSubsystem<Profiler>();
    if (profiler)
        LOGRAW(profiler->GetData(true, true) + "\n");
}

void Engine::DumpResources(bool dumpFileName)
{
    #ifdef URHO3D_LOGGING
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    const HashMap<StringHash, ResourceGroup>& resourceGroups = cache->GetAllResources();
    LOGRAW("\n");
    
    if (dumpFileName)
    {
        LOGRAW("Used resources:\n");
    }
    
    for (HashMap<StringHash, ResourceGroup>::ConstIterator i = resourceGroups.Begin();
        i != resourceGroups.End(); ++i)
    {
        const HashMap<StringHash, SharedPtr<Resource> >& resources = i->second_.resources_;
        if (dumpFileName)
        {
            for (HashMap<StringHash, SharedPtr<Resource> >::ConstIterator j = resources.Begin();
                j != resources.End(); ++j)
            {
                LOGRAW(j->second_->GetName() + "\n");
            }

        }
        else
        {
            unsigned num = resources.Size();
            unsigned memoryUse = i->second_.memoryUse_;

            if (num)
            {
                LOGRAW("Resource type " + resources.Begin()->second_->GetTypeName() +
                    ": count " + String(num) + " memory use " + String(memoryUse) + "\n");
            }
        }
    }

    if (!dumpFileName)
    {
        LOGRAW("Total memory use of all resources " + String(cache->GetTotalMemoryUse()) + "\n\n");
    }
    #endif
}

void Engine::DumpMemory()
{
    #ifdef URHO3D_LOGGING
    #if defined(_MSC_VER) && defined(_DEBUG)
    _CrtMemState state;
    _CrtMemCheckpoint(&state);
    _CrtMemBlockHeader* block = state.pBlockHeader;
    unsigned total = 0;
    unsigned blocks = 0;

    for (;;)
    {
        if (block && block->pBlockHeaderNext)
            block = block->pBlockHeaderNext;
        else
            break;
    }

    while (block)
    {
        if (block->nBlockUse > 0)
        {
            if (block->szFileName)
                LOGRAW("Block " + String((int)block->lRequest) + ": " + String(block->nDataSize) + " bytes, file " + String(block->szFileName) + " line " + String(block->nLine) + "\n");
            else
                LOGRAW("Block " + String((int)block->lRequest) + ": " + String(block->nDataSize) + " bytes\n");

            total += block->nDataSize;
            ++blocks;
        }
        block = block->pBlockHeaderPrev;
    }

    LOGRAW("Total allocated memory " + String(total) + " bytes in " + String(blocks) + " blocks\n\n");
    #else
    LOGRAW("DumpMemory() supported on MSVC debug mode only\n\n");
    #endif
    #endif
}

void Engine::Update()
{
    PROFILE(Update);

    // Logic update event
    using namespace Update;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_TIMESTEP] = timeStep_;
    SendEvent(E_UPDATE, eventData);

    // Logic post-update event
    SendEvent(E_POSTUPDATE, eventData);

    // Rendering update event
    SendEvent(E_RENDERUPDATE, eventData);

    // Post-render update event
    SendEvent(E_POSTRENDERUPDATE, eventData);
}

void Engine::Render()
{
    if (headless_)
        return;

    PROFILE(Render);

    // If device is lost, BeginFrame will fail and we skip rendering
    Graphics* graphics = GetSubsystem<Graphics>();
    if (!graphics->BeginFrame())
        return;

    GetSubsystem<Renderer>()->Render();
    GetSubsystem<UI>()->Render();
    graphics->EndFrame();
}

void Engine::ApplyFrameLimit()
{
    if (!initialized_)
        return;

    int maxFps = maxFps_;
    Input* input = GetSubsystem<Input>();
    if (input && !input->HasFocus())
        maxFps = Min(maxInactiveFps_, maxFps);

    long long elapsed = 0;

    // Perform waiting loop if maximum FPS set
    if (maxFps)
    {
        PROFILE(ApplyFrameLimit);

        long long targetMax = 1000000LL / maxFps;

        for (;;)
        {
            elapsed = frameTimer_.GetUSec(false);
            if (elapsed >= targetMax)
                break;

            // Sleep if 1 ms or more off the frame limiting goal
            if (targetMax - elapsed >= 1000LL)
            {
                unsigned sleepTime = (unsigned)((targetMax - elapsed) / 1000LL);
                Time::Sleep(sleepTime);
            }
        }
    }

    elapsed = frameTimer_.GetUSec(true);
    #ifdef URHO3D_TESTING
    if (timeOut_ > 0)
    {
        timeOut_ -= elapsed;
        if (timeOut_ <= 0)
            Exit();
    }
    #endif

    // If FPS lower than minimum, clamp elapsed time
    if (minFps_)
    {
        long long targetMin = 1000000LL / minFps_;
        if (elapsed > targetMin)
            elapsed = targetMin;
    }

    // Perform timestep smoothing
    timeStep_ = 0.0f;
    lastTimeSteps_.Push(elapsed / 1000000.0f);
    if (lastTimeSteps_.Size() > timeStepSmoothing_)
    {
        // If the smoothing configuration was changed, ensure correct amount of samples
        lastTimeSteps_.Erase(0, lastTimeSteps_.Size() - timeStepSmoothing_);
        for (unsigned i = 0; i < lastTimeSteps_.Size(); ++i)
            timeStep_ += lastTimeSteps_[i];
        timeStep_ /= lastTimeSteps_.Size();
    }
    else
        timeStep_ = lastTimeSteps_.Back();
}

VariantMap Engine::ParseParameters(const Vector<String>& arguments)
{
    VariantMap ret;

    for (unsigned i = 0; i < arguments.Size(); ++i)
    {
        if (arguments[i].Length() > 1 && arguments[i][0] == '-')
        {
            String argument = arguments[i].Substring(1).ToLower();
            String value = i + 1 < arguments.Size() ? arguments[i + 1] : String::EMPTY;

            if (argument == "headless")
                ret["Headless"] = true;
            else if (argument == "nolimit")
                ret["FrameLimiter"] = false;
            else if (argument == "flushgpu")
                ret["FlushGPU"] = true;
            else if (argument == "landscape")
                ret["Orientations"] = "LandscapeLeft LandscapeRight " + ret["Orientations"].GetString();
            else if (argument == "portrait")
                ret["Orientations"] = "Portrait PortraitUpsideDown " + ret["Orientations"].GetString();
            else if (argument == "nosound")
                ret["Sound"] = false;
            else if (argument == "noip")
                ret["SoundInterpolation"] = false;
            else if (argument == "mono")
                ret["SoundStereo"] = false;
            else if (argument == "prepass")
                ret["RenderPath"] = "RenderPaths/Prepass.xml";
            else if (argument == "deferred")
                ret["RenderPath"] = "RenderPaths/Deferred.xml";
            else if (argument == "renderpath" && !value.Empty())
            {
                ret["RenderPath"] = value;
                ++i;
            }
            else if (argument == "noshadows")
                ret["Shadows"] = false;
            else if (argument == "lqshadows")
                ret["LowQualityShadows"] = true;
            else if (argument == "nothreads")
                ret["WorkerThreads"] = false;
            else if (argument == "sm2")
                ret["ForceSM2"] = true;
            else if (argument == "v")
                ret["VSync"] = true;
            else if (argument == "t")
                ret["TripleBuffer"] = true;
            else if (argument == "w")
                ret["FullScreen"] = false;
            else if (argument == "s")
                ret["WindowResizable"] = true;
            else if (argument == "borderless")
                ret["Borderless"] = true;
            else if (argument == "q")
                ret["LogQuiet"] = true;
            else if (argument == "log" && !value.Empty())
            {
                int logLevel = GetStringListIndex(value.CString(), logLevelPrefixes, -1);
                if (logLevel != -1)
                {
                    ret["LogLevel"] = logLevel;
                    ++i;
                }
            }
            else if (argument == "x" && !value.Empty())
            {
                ret["WindowWidth"] = ToInt(value);
                ++i;
            }
            else if (argument == "y" && !value.Empty())
            {
                ret["WindowHeight"] = ToInt(value);
                ++i;
            }
            else if (argument == "m" && !value.Empty())
            {
                ret["MultiSample"] = ToInt(value);
                ++i;
            }
            else if (argument == "b" && !value.Empty())
            {
                ret["SoundBuffer"] = ToInt(value);
                ++i;
            }
            else if (argument == "r" && !value.Empty())
            {
                ret["SoundMixRate"] = ToInt(value);
                ++i;
            }
            else if (argument == "pp" && !value.Empty())
            {
                ret["ResourcePrefixPath"] = value;
                ++i;
            }
            else if (argument == "p" && !value.Empty())
            {
                ret["ResourcePaths"] = value;
                ++i;
            }
            else if (argument == "pf" && !value.Empty())
            {
                ret["ResourcePackages"] = value;
                ++i;
            }
            else if (argument == "ap" && !value.Empty())
            {
                ret["AutoloadPaths"] = value;
                ++i;
            }
            else if (argument == "ds" && !value.Empty())
            {
                ret["DumpShaders"] = value;
                ++i;
            }
            else if (argument == "mq" && !value.Empty())
            {
                ret["MaterialQuality"] = ToInt(value);
                ++i;
            }
            else if (argument == "tq" && !value.Empty())
            {
                ret["TextureQuality"] = ToInt(value);
                ++i;
            }
            else if (argument == "tf" && !value.Empty())
            {
                ret["TextureFilterMode"] = ToInt(value);
                ++i;
            }
            else if (argument == "af" && !value.Empty())
            {
                ret["TextureFilterMode"] = FILTER_ANISOTROPIC;
                ret["TextureAnisotropy"] = ToInt(value);
                ++i;
            }
            else if (argument == "touch")
                ret["TouchEmulation"] = true;
            #ifdef URHO3D_TESTING
            else if (argument == "timeout" && !value.Empty())
            {
                ret["TimeOut"] = ToInt(value);
                ++i;
            }
            #endif
        }
    }

    return ret;
}

bool Engine::HasParameter(const VariantMap& parameters, const String& parameter)
{
    StringHash nameHash(parameter);
    return parameters.Find(nameHash) != parameters.End();
}

const Variant& Engine::GetParameter(const VariantMap& parameters, const String& parameter, const Variant& defaultValue)
{
    StringHash nameHash(parameter);
    VariantMap::ConstIterator i = parameters.Find(nameHash);
    return i != parameters.End() ? i->second_ : defaultValue;
}

void Engine::HandleExitRequested(StringHash eventType, VariantMap& eventData)
{
    if (autoExit_)
    {
        // Do not call Exit() here, as it contains mobile platform -specific tests to not exit.
        // If we do receive an exit request from the system on those platforms, we must comply
        DoExit();
    }
}

void Engine::DoExit()
{
    Graphics* graphics = GetSubsystem<Graphics>();
    if (graphics)
        graphics->Close();

    exiting_ = true;
}

}
