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

#include "Object.h"
#include "Timer.h"

namespace Urho3D
{

class Console;
class DebugHud;

/// Urho3D engine. Creates the other subsystems.
class Engine : public Object
{
    OBJECT(Engine);
    
public:
    /// Construct.
    Engine(Context* context);
    /// Destruct. Free all subsystems.
    virtual ~Engine();
    
    /// Initialize engine using parameters given and show the application window. Return true if successful.
    bool Initialize(const VariantMap& parameters);
    /// Run one frame.
    void RunFrame();
    /// Create the console and return it. May return null if engine configuration does not allow creation (headless mode.)
    Console* CreateConsole();
    /// Create the debug hud.
    DebugHud* CreateDebugHud();
    /// Set minimum frames per second. If FPS goes lower than this, time will appear to slow down.
    void SetMinFps(int fps);
    /// Set maximum frames per second. The engine will sleep if FPS is higher than this.
    void SetMaxFps(int fps);
    /// Set maximum frames per second when the application does not have input focus.
    void SetMaxInactiveFps(int fps);
    /// Set whether to pause update events and audio when minimized.
    void SetPauseMinimized(bool enable);
    /// Set whether to exit automatically on exit request (window close button.)
    void SetAutoExit(bool enable);
    /// Close the application window and set the exit flag.
    void Exit();
    /// Dump profiling information to the log.
    void DumpProfiler();
    /// Dump information of all resources to the log.
    void DumpResources();
    /// Dump information of all memory allocations to the log. Supported in MSVC debug mode only.
    void DumpMemory();
    
    /// Return the minimum frames per second.
    int GetMinFps() const { return minFps_; }
    /// Return the maximum frames per second.
    int GetMaxFps() const { return maxFps_; }
    /// Return the maximum frames per second when the application does not have input focus.
    int GetMaxInactiveFps() const { return maxInactiveFps_; }
    /// Return whether to pause update events and audio when minimized.
    bool GetPauseMinimized() const { return pauseMinimized_; }
    /// Return whether to exit automatically on exit request.
    bool GetAutoExit() const { return autoExit_; }
    /// Return whether engine has been initialized.
    bool IsInitialized() const { return initialized_; }
    /// Return whether exit has been requested.
    bool IsExiting() const { return exiting_; }
    /// Return whether the engine has been created in headless mode.
    bool IsHeadless() const { return headless_; }
    
    /// Send frame update events.
    void Update();
    /// Render after frame update.
    void Render();
    /// Get the timestep for the next frame and sleep for frame limiting if necessary.
    void ApplyFrameLimit();
    
    /// Parse the engine startup parameters map from command line arguments.
    static VariantMap ParseParameters(const Vector<String>& arguments);
    /// Return whether startup parameters contains a specific parameter.
    static bool HasParameter(const VariantMap& parameters, const String& parameter);
    /// Get an engine startup parameter, with default value if missing.
    static const Variant& GetParameter(const VariantMap& parameters, const String& parameter, const Variant& defaultValue = Variant::EMPTY);
    
private:
    /// Handle exit requested event.
    void HandleExitRequested(StringHash eventType, VariantMap& eventData);
    
    /// Frame update timer.
    HiresTimer frameTimer_;
    /// Next frame timestep in seconds.
    float timeStep_;
    /// Minimum frames per second.
    unsigned minFps_;
    /// Maximum frames per second.
    unsigned maxFps_;
    /// Maximum frames per second when the application does not have input focus.
    unsigned maxInactiveFps_;
    /// Pause when minimized flag.
    bool pauseMinimized_;
    /// Auto-exit flag.
    bool autoExit_;
    /// Initialized flag.
    bool initialized_;
    /// Exiting flag.
    bool exiting_;
    /// Headless mode flag.
    bool headless_;
    /// Audio paused flag.
    bool audioPaused_;
};

}
