// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Object.h"
#include "../Core/Timer.h"

namespace Urho3D
{

class Console;
class DebugHud;

/// Urho3D engine. Creates the other subsystems.
class URHO3D_API Engine : public Object
{
    URHO3D_OBJECT(Engine, Object);

public:
    /// Construct.
    explicit Engine(Context* context);
    /// Destruct. Free all subsystems.
    ~Engine() override;

    /// Initialize engine using parameters given and show the application window. Return true if successful.
    bool Initialize(const VariantMap& parameters);
    /// Reinitialize resource cache subsystem using parameters given. Implicitly called by Initialize. Return true if successful.
    bool InitializeResourceCache(const VariantMap& parameters, bool removeOld = true);
    /// Run one frame.
    void RunFrame();
    /// Create the console and return it. May return null if engine configuration does not allow creation (headless mode).
    Console* CreateConsole();
    /// Create the debug hud.
    DebugHud* CreateDebugHud();
    /// Set minimum frames per second. If FPS goes lower than this, time will appear to slow down.
    /// @property
    void SetMinFps(int fps);
    /// Set maximum frames per second. The engine will sleep if FPS is higher than this.
    /// @property
    void SetMaxFps(int fps);
    /// Set maximum frames per second when the application does not have input focus.
    /// @property
    void SetMaxInactiveFps(int fps);
    /// Set how many frames to average for timestep smoothing. Default is 2. 1 disables smoothing.
    /// @property
    void SetTimeStepSmoothing(int frames);
    /// Set whether to pause update events and audio when minimized.
    /// @property
    void SetPauseMinimized(bool enable);
    /// Set whether to exit automatically on exit request (window close button).
    /// @property
    void SetAutoExit(bool enable);
    /// Override timestep of the next frame. Should be called in between RunFrame() calls.
    void SetNextTimeStep(float seconds);
    /// Close the graphics window and set the exit flag. No-op on iOS/tvOS, as an iOS/tvOS application can not legally exit.
    void Exit();
    /// Dump profiling information to the log.
    void DumpProfiler();
    /// Dump information of all resources to the log.
    void DumpResources(bool dumpFileName = false);
    /// Dump information of all memory allocations to the log. Supported in MSVC debug mode only.
    void DumpMemory();

    /// Get timestep of the next frame. Updated by ApplyFrameLimit().
    float GetNextTimeStep() const { return timeStep_; }

    /// Return the minimum frames per second.
    /// @property
    int GetMinFps() const { return minFps_; }

    /// Return the maximum frames per second.
    /// @property
    int GetMaxFps() const { return maxFps_; }

    /// Return the maximum frames per second when the application does not have input focus.
    /// @property
    int GetMaxInactiveFps() const { return maxInactiveFps_; }

    /// Return how many frames to average for timestep smoothing.
    /// @property
    int GetTimeStepSmoothing() const { return timeStepSmoothing_; }

    /// Return whether to pause update events and audio when minimized.
    /// @property
    bool GetPauseMinimized() const { return pauseMinimized_; }

    /// Return whether to exit automatically on exit request.
    /// @property
    bool GetAutoExit() const { return autoExit_; }

    /// Return whether engine has been initialized.
    /// @property
    bool IsInitialized() const { return initialized_; }

    /// Return whether exit has been requested.
    /// @property
    bool IsExiting() const { return exiting_; }

    /// Return whether the engine has been created in headless mode.
    /// @property
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
    static const Variant
        & GetParameter(const VariantMap& parameters, const String& parameter, const Variant& defaultValue = Variant::EMPTY);

private:
    /// Handle exit requested event. Auto-exit if enabled.
    void HandleExitRequested(StringHash eventType, VariantMap& eventData);
    /// Actually perform the exit actions.
    void DoExit();

    /// Frame update timer.
    HiresTimer frameTimer_;
    /// Previous timesteps for smoothing.
    Vector<float> lastTimeSteps_;
    /// Next frame timestep in seconds.
    float timeStep_;
    /// How many frames to average for the smoothed timestep.
    unsigned timeStepSmoothing_;
    /// Minimum frames per second.
    unsigned minFps_;
    /// Maximum frames per second.
    unsigned maxFps_;
    /// Maximum frames per second when the application does not have input focus.
    unsigned maxInactiveFps_;
    /// Pause when minimized flag.
    bool pauseMinimized_;
#ifdef URHO3D_TESTING
    /// Time out counter for testing.
    long long timeOut_;
#endif
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
