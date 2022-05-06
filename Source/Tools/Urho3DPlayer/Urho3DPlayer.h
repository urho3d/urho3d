// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include <Urho3D/Engine/Application.h>

using namespace Urho3D;

/// Urho3DPlayer application runs a script specified on the command line.
class Urho3DPlayer : public Application
{
    URHO3D_OBJECT(Urho3DPlayer, Application);

public:
    /// Construct.
    explicit Urho3DPlayer(Context* context);

    /// Setup before engine initialization. Verify that a script file has been specified.
    void Setup() override;
    /// Setup after engine initialization. Load the script and execute its start function.
    void Start() override;
    /// Cleanup after the main loop. Run the script's stop function if it exists.
    void Stop() override;

private:
    /// Handle reload start of the script file.
    void HandleScriptReloadStarted(StringHash eventType, VariantMap& eventData);
    /// Handle reload success of the script file.
    void HandleScriptReloadFinished(StringHash eventType, VariantMap& eventData);
    /// Handle reload failure of the script file.
    void HandleScriptReloadFailed(StringHash eventType, VariantMap& eventData);
    /// Parse script file name from the first argument.
    void GetScriptFileName();

    /// Script file name.
    String scriptFileName_;
    /// Flag whether CommandLine.txt was already successfully read.
    bool commandLineRead_;

#ifdef URHO3D_ANGELSCRIPT
    /// Script file.
    SharedPtr<ScriptFile> scriptFile_;
#endif
};
