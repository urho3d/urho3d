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

#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "BoundingBox.h"
#include "EventListener.h"
#include "SharedPtr.h"
#include "Timer.h"

#include <string>
#include <vector>

class Audio;
class Camera;
class Client;
class Console;
class Cursor;
class DebugHud;
class Input;
class Log;
class Network;
class Pipeline;
class Profiler;
class Renderer;
class ResourceCache;
class Scene;
class ScriptEngine;
class ScriptFile;
class Server;
class UI;
class UIElement;

//! Urho3D engine. Creates the other subsystems
class Engine : public RefCounted, public EventListener
{
    friend Engine* getEngine();
    
public:
    //! Construct with window title, log file name and whether to start in headless mode
    Engine(const std::string& windowTitle = "Urho3D", const std::string& logFileName = "Urho3D.log", bool headless = false);
    //! Destruct. Free all subsystems
    virtual ~Engine();
    
    //! Initialize and show the application window
    void init(const std::vector<std::string>& arguments = std::vector<std::string>());
    //! Run one frame
    void runFrame();
    //! Create a scene
    SharedPtr<Scene> createScene(const std::string& name = "Default", const BoundingBox& octreeSize =
        BoundingBox(-1000.0f, 1000.0f), unsigned octreeLevels = 8, bool usePhysics = true);
    //! Create the network subsystem
    Network* createNetwork();
    //! Create the client subsystem. Creates also the network subsystem if not yet created
    Client* createClient(const std::string& downloadDirectory);
    //! Create the server subsystem. Creates also the network subsystem if not yet created
    Server* createServer();
    //! Create the script engine. Call before creating scripted scenes or loading script files
    ScriptEngine* createScriptEngine();
    //! Create the console
    Console* createConsole();
    //! Create the debug hud
    DebugHud* createDebugHud();
    //! Remove the client subsystem
    void removeClient();
    //! Remove the server subsystem
    void removeServer();
    //! Set the default scene. This will always be available as the "scene" global property to scripting
    void setDefaultScene(Scene* scene);
    //! Set the default script file. This will be used in immediate mode
    void setDefaultScriptFile(ScriptFile* file);
    //! Set minimum frames per second. If FPS goes lower than this, time will appear to slow down
    void setMinFps(int fps);
    //! Set maximum frames per second. The engine will sleep if FPS is higher than this
    void setMaxFps(int fps);
    //! Set maximum frames per second when the application is inactive
    void setMaxInactiveFps(int fps);
    //! Set whether the GPU is flushed after each frame. Can prevent mouse latency and frame rate jitter, but reduces CPU/GPU parallelism
    void setFlushGPU(bool enable);
    //! Close the application window and set the exit flag
    void exit();
    //! Dump profiling information to the log
    void dumpProfilingData();
    //! Dump information of all resources to the log
    void dumpResources();
    
    //! Return audio subsystem
    Audio* getAudio() const { return mAudio; }
    //! Return client subsystem
    Client* getClient() const { return mClient; }
    //! Return console if created
    Console* getConsole() const { return mConsole; }
    //! Return debug hud if created
    DebugHud* getDebugHud() const { return mDebugHud; }
    //! Return input subsystem
    Input* getInput() const { return mInput; }
    //! Return log
    Log* getLog() const { return mLog; }
    //! Return network subsystem if cretsed
    Network* getNetwork() const { return mNetwork; }
    //! Return high-level rendering pipeline. Null in headless mode
    Pipeline* getPipeline() const { return mPipeline; }
    //! Return profiler
    Profiler* getProfiler() const { return mProfiler; }
    //! Return renderer subsystem. Null in headless mode
    Renderer* getRenderer() const { return mRenderer; }
    //! Return resource cache
    ResourceCache* getResourceCache() const { return mCache; }
    //! Return script engine if created
    ScriptEngine* getScriptEngine() const { return mScriptEngine; }
    //! Return server subsystem if created
    Server* getServer() const { return mServer; }
    //! Return UI subsystem. Null in headless mode
    UI* getUI() const { return mUI; }
    //! Return UI root element. Null in headless mode
    UIElement* getUIRoot() const;
    //! Return UI cursor if it has been set
    Cursor* getUICursor() const;
    //! Return the default scene
    Scene* getDefaultScene() const { return mDefaultScene; }
    //! Return the minimum frames per second
    int getMinFps() const { return mMinFps; }
    //! Return the maximum frames per second
    int getMaxFps() const { return mMaxFps; }
    //! Return the maximum frames per second when the application is inactive
    int getMaxInactiveFps() const { return mMaxInactiveFps; }
    //! Return the GPU flush flag
    bool getFlushGPU() const { return mFlushGPU; }
    //! Return whether engine has been initialized
    bool isInitialized() const { return mInitialized; }
    //! Return whether exit has been requested
    bool isExiting() const { return mExiting; }
    //! Return whether the engine has been created in headless mode
    bool isHeadless() const { return mHeadless; }
    
    //! Return the timestep for the next frame and sleep for frame limiting if necessary
    float getNextTimeStep();
    //! Run the update for one frame
    void update(float timeStep);
    //! Run the rendering for one frame
    void render();
    
private:
    //! Register the script API after script engine creation
    void registerScriptAPI();
    
    //! Log
    SharedPtr<Log> mLog;
    //! Profiler
    SharedPtr<Profiler> mProfiler;
    //! Renderer subsystem
    SharedPtr<Renderer> mRenderer;
    //! Audio subsystem
    SharedPtr<Audio> mAudio;
    //! Input subsystem
    SharedPtr<Input> mInput;
    //! Resource cache
    SharedPtr<ResourceCache> mCache;
    //! High-level rendering pipeline
    SharedPtr<Pipeline> mPipeline;
    //! UI subsystem
    SharedPtr<UI> mUI;
    //! Network subsystem
    SharedPtr<Network> mNetwork;
    //! Client subsystem
    SharedPtr<Client> mClient;
    //! Server subsystem
    SharedPtr<Server> mServer;
    //! Console
    SharedPtr<Console> mConsole;
    //! Debug hud
    SharedPtr<DebugHud> mDebugHud;
    //! Script engine
    SharedPtr<ScriptEngine> mScriptEngine;
    //! Default scene
    WeakPtr<Scene> mDefaultScene;
    //! Window title
    std::string mWindowTitle;
    //! Frame update timer
    Timer mFrameTimer;
    //! Minimum frames per second
    unsigned mMinFps;
    //! Maximum frames per second
    unsigned mMaxFps;
    //! Maximum frames per second when the application is inactive
    unsigned mMaxInactiveFps;
    //! Flush GPU flag
    bool mFlushGPU;
    //! Initialized flag
    bool mInitialized;
    //! Exiting flag
    bool mExiting;
    //! Headless mode flag
    bool mHeadless;
    
    //! Engine instance
    static Engine* sInstance;
};

//! Return the Engine instance
inline Engine* getEngine()
{
    return Engine::sInstance;
}

//! Return the scene of the active context, or the default scene
Scene* getScriptContextScene();

#endif // ENGINE_ENGINE_H
