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
#include "AudioComponentFactory.h"
#include "AudioResourceFactory.h"
#include "BaseComponentFactory.h"
#include "BaseResourceFactory.h"
#include "Client.h"
#include "Cursor.h"
#include "DebugHud.h"
#include "DebugRenderer.h"
#include "Engine.h"
#include "EngineComponentFactory.h"
#include "EngineEvents.h"
#include "Input.h"
#include "Log.h"
#include "Network.h"
#include "Octree.h"
#include "PackageFile.h"
#include "PhysicsComponentFactory.h"
#include "PhysicsResourceFactory.h"
#include "PhysicsWorld.h"
#include "Pipeline.h"
#include "Profiler.h"
#include "RegisterLibraries.h"
#include "Renderer.h"
#include "RendererComponentFactory.h"
#include "RendererResourceFactory.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "ScriptComponentFactory.h"
#include "ScriptEngine.h"
#include "ScriptResourceFactory.h"
#include "Server.h"
#include "StringUtils.h"
#include "UI.h"
#include "UIResourceFactory.h"

#include <windows.h>

#include "DebugNew.h"

Engine* Engine::sInstance = 0;

Engine::Engine(const std::string& logFileName, bool headless) :
    mMinFps(10),
    mMaxFps(200),
    mMaxInactiveFps(50),
    mDebugDrawMode(DEBUGDRAW_NONE),
    mFlushGPU(true),
    mInitialized(false),
    mExiting(false),
    mHeadless(headless)
{
    if (sInstance)
        EXCEPTION("Engine already exists");
    
    // Set multimedia timer accuracy to allow measuring up to 200 fps
    setTimerPeriod(5);
    
    // Create profiler, log & resource cache already here
    mProfiler = new Profiler();
    
    #ifdef _DEBUG
    mLog = new Log(logFileName, LOG_DEBUG);
    #else
    mLog = new Log(logFileName, LOG_INFO);
    #endif
    
    mCache = new ResourceCache();
    
    // Register the inbuilt events as local only
    static const std::string inbuiltEvents[] = {
        "Update", "PostUpdate", "PostRenderUpdate", "ClientIdentity", "ClientJoinedScene", "ClientLeftScene", "ClientControls",
        "ClientDisconnected", "GotSceneInfoList", "JoinedScene", "JoinSceneFailed", "FileTransferCompleted", "FileTransferFailed",
        "ControlsUpdate", "ControlsPlayback", "MouseButtonDown", "MouseButtonUp", "MouseMove", "KeyDown", "KeyUp", "Char",
        "PeerConnected", "NetworkPacket", "PeerDisconnected", "PhysicsPreStep", "PhysicsPostStep", "PhysicsCollision",
        "EntityCollision", "WindowMessage", "WindowResized", "BeginFrame", "EndFrame", "SceneUpdate", "ScenePostUpdate",
        "AsyncLoadProgress", "AsyncLoadFinished", "TryFocus", "Focused", "Defocused", "Pressed", "Toggled", "SliderChanged",
        "ViewChanged", "TextChanged", "TextFinished", "ItemSelected", ""
    };
    
    for (unsigned i = 0; inbuiltEvents[i].length(); ++i)
        registerLocalOnlyEvent(inbuiltEvents[i]);
    
    sInstance = this;
}

Engine::~Engine()
{
    // Restore default multimedia timer accuracy
    setTimerPeriod(0);
    
    if (sInstance == this)
        sInstance = 0;
}

void Engine::init(const std::string& windowTitle, const std::vector<std::string>& arguments)
{
    PROFILE(Engine_Init);
    
    if (mInitialized)
        return;
    
    RenderMode mode = RENDER_DEFERRED;
    int width = 0;
    int height = 0;
    int multiSample = 0;
    bool fullscreen = true;
    bool vsync = false;
    bool forceSM2 = false;
    
    int mixRate = 44100;
    int buffer = 100;
    bool sound = true;
    bool stereo = true;
    bool sixteenBit = true;
    bool interpolate = true;
    
    for (unsigned i = 0; i < arguments.size(); ++i)
    {
        if ((arguments[i][0] == '-') && (arguments[i].length() >= 2))
        {
            std::string argument = toLower(arguments[i].substr(1));
            
            if (argument == "nosound")
                sound = false;
            else if (argument == "noip")
                interpolate = false;
            else if (argument == "mono")
                stereo = false;
            else if (argument == "8bit")
                sixteenBit = false;
            else if (argument == "deferred")
                mode = RENDER_DEFERRED;
            else if (argument == "prepass")
                mode = RENDER_PREPASS;
            else if (argument == "forward")
                mode = RENDER_FORWARD;
            else if (argument == "sm2")
                forceSM2 = true;
            else
            {
                switch (tolower(argument[0]))
                {
                case 'x':
                    if (arguments[i].length() > 1)
                        width = toInt(argument.substr(1));
                    break;
                    
                case 'y':
                    if (arguments[i].length() > 1)
                        height = toInt(argument.substr(1));
                    break;
                
                case 'm':
                    if (arguments[i].length() > 1)
                        multiSample = toInt(argument.substr(1));
                    break;
                    
                case 'b':
                    if (arguments[i].length() > 1)
                        buffer = toInt(argument.substr(1));
                    break;
                    
                case 'r':
                    if (arguments[i].length() > 1)
                        mixRate = toInt(argument.substr(1));
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
    
    if (!mHeadless)
    {
        mRenderer = new Renderer(windowTitle);
        mRenderer->setForceSM2(forceSM2);
        mRenderer->setMode(mode, width, height, fullscreen, vsync, multiSample);
        
        mAudio = new Audio(mRenderer->getWindowHandle());
        if (sound)
            mAudio->setMode(buffer, mixRate, sixteenBit, stereo, interpolate);
    }
    else
    {
        // Create the audio system also in headless mode so that length of sound effects can be "simulated"
        mAudio = new Audio((int)INVALID_HANDLE_VALUE);
    }
    
    mInput = new Input(mRenderer);
    
    mNetwork = new Network();
    
    // If no resource paths or packages already defined, add the default resource path
    if ((mCache->getPackageFiles().empty()) && (mCache->getResourcePaths().empty()))
        mCache->addResourcePath("Data");
    
    mCache->addResourceFactory(new BaseResourceFactory());
    mCache->addResourceFactory(new AudioResourceFactory(mAudio));
    mCache->addResourceFactory(new PhysicsResourceFactory());
    mCache->addResourceFactory(new RendererResourceFactory(mRenderer));
    mCache->addResourceFactory(new UIResourceFactory(mRenderer));
    
    if (!mHeadless)
    {
        mDebugRenderer = new DebugRenderer(mRenderer, mCache);
        mPipeline = new Pipeline(mRenderer, mCache);
        mUI = new UI(mRenderer, mCache);
    }
    
    mInitialized = true;
}

void Engine::runFrame(Scene* scene, Camera* camera, bool updateScene)
{
    if ((!mInitialized) || (mExiting))
        return;
    
    if ((mRenderer) && (mRenderer->isClosed()))
    {
        exit();
        return;
    }
    
    mProfiler->beginFrame();
    
    {
        PROFILE(Engine_RunFrame);
        
        float timeStep = getNextTimeStep();
        update(timeStep, scene, camera, updateScene);
        render();
    }
    
    mProfiler->endFrame();
}

SharedPtr<Scene> Engine::createScene(const std::string& name, const BoundingBox& octreeSize, unsigned octreeLevels, bool usePhysics)
{
    SharedPtr<Scene> scene(new Scene(mCache, name));
    
    // Add the default extensions & component factories
    Octree* octree = new Octree(octreeSize, octreeLevels, mHeadless);
    scene->addExtension(octree);
    scene->addComponentFactory(new AudioComponentFactory(mAudio));
    scene->addComponentFactory(new BaseComponentFactory());
    scene->addComponentFactory(new EngineComponentFactory(octree));
    scene->addComponentFactory(new RendererComponentFactory(octree));
    if (mScriptEngine)
        scene->addComponentFactory(new ScriptComponentFactory(mScriptEngine));
    
    // Enable physics as necessary
    if (usePhysics)
    {
        PhysicsWorld* world = new PhysicsWorld(scene);
        scene->addExtension(world);
        scene->addComponentFactory(new PhysicsComponentFactory(world));
    }
    
    return scene;
}

Network* Engine::createNetwork()
{
    if (!mNetwork)
        mNetwork = new Network();
    return mNetwork;
}

Client* Engine::createClient(const std::string& downloadDirectory)
{
    if (!mClient)
    {
        createNetwork();
        mClient = new Client(mNetwork, mCache, downloadDirectory);
    }
    return mClient;
}

void Engine::removeClient()
{
    mClient.reset();
}

Server* Engine::createServer()
{
    if (!mServer)
    {
        createNetwork();
        mServer = new Server(mNetwork);
    }
    return mServer;
}

void Engine::removeServer()
{
    mServer.reset();
}

ScriptEngine* Engine::createScriptEngine()
{
    if (!mScriptEngine)
    {
        mScriptEngine = new ScriptEngine();
        mCache->addResourceFactory(new ScriptResourceFactory(mScriptEngine));
        registerScriptAPI();
    }
    return mScriptEngine;
}

DebugHud* Engine::createDebugHud()
{
    if (!mDebugHud)
        mDebugHud = new DebugHud(this);
    return mDebugHud;
}

void Engine::setMinFps(int fps)
{
    mMinFps = max(fps, 0);
}

void Engine::setMaxFps(int fps)
{
    mMaxFps = max(fps, 0);
}

void Engine::setMaxInactiveFps(int fps)
{
    mMaxInactiveFps = max(fps, 0);
}

void Engine::setDebugDrawMode(int mode)
{
    mDebugDrawMode = mode;
}

void Engine::setFlushGPU(bool enable)
{
    mFlushGPU = enable;
}

void Engine::exit()
{
    // To close window / stop audio here is not necessary, but gives impression of faster response,
    // while other uninitialization still goes on
    mAudio->stop();
    if (mRenderer)
        mRenderer->close();
    
    mExiting = true;
}

void Engine::dumpProfilingData()
{
    mProfiler->endFrame();
    mLog->writeRaw(mProfiler->getData(true, false, true));
    mLog->writeRaw("\n");
}

void Engine::dumpResources()
{
    const std::map<ShortStringHash, ResourceGroup>& resourceGroups = mCache->getAllResources();
    mLog->writeRaw("\n");
    
    for (std::map<ShortStringHash, ResourceGroup>::const_iterator i = resourceGroups.begin();
        i != resourceGroups.end(); ++i)
    {
        unsigned num = i->second.mResources.size();
        unsigned memoryUse = i->second.mMemoryUse;
        
        if (num)
        {
            mLog->writeRaw("Resource type " + i->second.mResources.begin()->second->getTypeName() +
                ": count " + toString(num) + " memory use " + toString(memoryUse) + "\n");
        }
    }
    
    mLog->writeRaw("Total memory use of all resources " + toString(mCache->getTotalMemoryUse()) + "\n");
    mLog->writeRaw("\n");
}

UIElement* Engine::getUIRoot() const
{
    if (!mUI)
        return 0;
    
    return mUI->getRootElement();
}

Cursor* Engine::getUICursor() const
{
    if (!mUI)
        return 0;
    
    return mUI->getCursor();
}

float Engine::getNextTimeStep()
{
    PROFILE(Engine_Sleep);
    
    if (!mInitialized)
        return 0.0f;
    
    int maxFps = mMaxFps;
    if (!mInput->isActive())
        maxFps = mMaxInactiveFps;
    
    int timeAcc = 0;
    
    if (maxFps)
    {
        int targetMax = 1000 / maxFps;
        for (;;)
        {
            timeAcc += mFrameTimer.getMSec(true);
            if (timeAcc >= targetMax)
                break;
            
            unsigned wait = (targetMax - timeAcc);
            Sleep(wait / 2);
        }
    }
    else
        timeAcc = mFrameTimer.getMSec(true);
    
    // If FPS lower than minimum, clamp elapsed time
    if (mMinFps)
    {
        int targetMin = 1000 / mMinFps;
        if (timeAcc > targetMin)
            timeAcc = targetMin;
    }
    
    return timeAcc / 1000.0f;
}

void Engine::update(float timeStep, Scene* scene, Camera* camera, bool updateScene)
{
    PROFILE(Engine_Update);
    
    if (!mInitialized)
        return;
    
    // If client or server exist, they are assumed to update the scene on their own.
    // In those cases set updateScene = false
    if ((mClient) && (mClient->getScene() == scene))
        updateScene = false;
    if ((mServer) && (mServer->hasScene(scene)))
        updateScene = false;
    
    // Make weak pointers of the scene & camera, in case update logic destroys them
    WeakPtr<Scene> sceneWeak(scene);
    WeakPtr<Camera> cameraWeak(camera);
    
    // Clear debug rendering output from last frame
    if (mDebugRenderer)
        mDebugRenderer->clear();
    
    // Input update
    mInput->update();
    
    // Network update
    if (mNetwork)
        mNetwork->update();
    
    // Application update
    using namespace Update;
    
    VariantMap updateData;
    updateData[P_TIMESTEP] = timeStep;
    sendEvent(EVENT_UPDATE, updateData);
    
    // Client and server update
    if (mClient)
        mClient->update(timeStep);
    if (mServer)
        mServer->update(timeStep);
    
    // Scene update
    if ((sceneWeak) && (updateScene))
        scene->update(timeStep);
    
    // Application post-update
    sendEvent(EVENT_POSTUPDATE, updateData);
    
    // Rendering and debug geometry update
    if (mPipeline)
    {
        // Do not render if the scene is loading asynchronously, and thus incomplete
        if ((sceneWeak) && (cameraWeak) && (!sceneWeak->isAsyncLoading()))
        {
            mPipeline->update(timeStep, scene->getExtension<Octree>(), camera);
            
            if (mDebugRenderer)
            {
                mDebugRenderer->setView(camera);
                if (mDebugDrawMode & DEBUGDRAW_RENDERING)
                    mPipeline->drawDebugGeometry(mDebugRenderer);
                if (mDebugDrawMode & DEBUGDRAW_PHYSICS)
                {
                    PhysicsWorld* world = scene->getExtension<PhysicsWorld>();
                    if (world)
                        world->drawDebugGeometry(mDebugRenderer);
                }
            }
        }
        else
            mPipeline->update(timeStep, 0, 0);
    }
    
    if (mDebugHud)
        mDebugHud->update(timeStep);
    
    // Application post-render update
    sendEvent(EVENT_POSTRENDERUPDATE, updateData);
    
    // UI rendering update
    if (mUI)
        mUI->update(timeStep);
    
    // Audio update
    mAudio->update(timeStep);
    
    // Script garbage collection
    if (mScriptEngine)
        mScriptEngine->garbageCollect();
}

void Engine::render()
{
    PROFILE(Engine_Render);
    
    if (!mRenderer)
        return;
    
    // Do not render if device lost
    if (!mRenderer->beginFrame())
        return;
    
    mPipeline->render();
    mDebugRenderer->render();
    mUI->render();
    
    mRenderer->endFrame(mFlushGPU);
}

void Engine::registerScriptAPI()
{
    PROFILE(Script_RegisterAPI);
    
    asIScriptEngine* engine = mScriptEngine->getAngelScriptEngine();
    
    // Libraries need to be registered in their dependency order, so that there are for example no undefined Math types
    // when Common types depending on them are being registered
    
    LOGDEBUG("Registering Math library");
    registerMathLibrary(engine);
    
    LOGDEBUG("Registering Common library");
    registerCommonLibrary(engine);
    
    LOGDEBUG("Registering Event library");
    registerEventLibrary(engine);
    
    LOGDEBUG("Registering Resource library");
    registerResourceLibrary(engine);
    
    LOGDEBUG("Registering Scene library");
    registerSceneLibrary(engine);
    
    LOGDEBUG("Registering Audio library");
    registerAudioLibrary(engine);
    
    LOGDEBUG("Registering Renderer library");
    registerRendererLibrary(engine);
    
    LOGDEBUG("Registering Input library");
    registerInputLibrary(engine);
    
    LOGDEBUG("Registering UI library");
    registerUILibrary(engine);
    
    LOGDEBUG("Registering Physics library");
    registerPhysicsLibrary(engine);
    
    LOGDEBUG("Registering Script library");
    registerScriptLibrary(engine);
    
    LOGDEBUG("Registering Engine library");
    registerEngineLibrary(engine);
}
