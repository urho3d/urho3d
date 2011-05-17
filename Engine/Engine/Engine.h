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

#pragma once

#include "Object.h"
#include "Timer.h"

class Console;
class DebugHud;

/// Urho3D engine. Creates the other subsystems
class Engine : public Object
{
    OBJECT(Engine);
    
public:
    /// Construct
    Engine(Context* context);
    /// Destruct. Free all subsystems
    virtual ~Engine();
    
    /// Initialize and show the application window. Return true if successful
    bool Initialize(const String& windowTitle = "Urho3D", const String& logName = "Urho3D.log", const std::vector<String>&
        arguments = std::vector<String>());
    /// Initialize script subsystem and register the script API. Return true if successful (engine must be initialized first)
    bool InitializeScripting();
    /// Run one frame
    void RunFrame();
    /// Create the console and return it. May return null if engine configuration does not allow creation (headless mode)
    Console* CreateConsole();
    /// Create the debug hud
    DebugHud* CreateDebugHud();
    /// Set minimum frames per second. If FPS goes lower than this, time will appear to slow down
    void SetMinFps(int fps);
    /// Set maximum frames per second. The engine will sleep if FPS is higher than this
    void SetMaxFps(int fps);
    /// Set maximum frames per second when the application is inactive
    void SetMaxInactiveFps(int fps);
    /// Close the application window and set the exit flag
    void Exit();
    /// Dump profiling information to the log
    void DumpProfilingData();
    /// Dump information of all resources to the log
    void DumpResources();
    
    /// Return the minimum frames per second
    int GetMinFps() const { return minFps_; }
    /// Return the maximum frames per second
    int GetMaxFps() const { return maxFps_; }
    /// Return the maximum frames per second when the application is inactive
    int GetMaxInactiveFps() const { return maxInactiveFps_; }
    /// Return whether engine has been initialized
    bool IsInitialized() const { return initialized_; }
    /// Return whether exit has been requested
    bool IsExiting() const { return exiting_; }
    /// Return whether the engine has been created in headless mode
    bool IsHeadless() const { return headless_; }
    
    /// Render after frame update
    void Render();
    /// Get the timestep for the next frame and sleep for frame limiting if necessary
    void GetNextTimeStep();
    
private:
    /// Register object factories and attributes
    void RegisterObjects();
    /// Create and register subsystems. In headless mode graphics, input & UI are not created
    void RegisterSubsystems();
    
    /// Frame update timer
    Timer frameTimer_;
    /// Next frame timestep in milliseconds
    unsigned timeStep_;
    /// Minimum frames per second
    unsigned minFps_;
    /// Maximum frames per second
    unsigned maxFps_;
    /// Maximum frames per second when the application is inactive
    unsigned maxInactiveFps_;
    /// Initialized flag
    bool initialized_;
    /// Exiting flag
    bool exiting_;
    /// Headless mode flag
    bool headless_;
};
