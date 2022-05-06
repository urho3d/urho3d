// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

namespace Urho3D
{

class Node;
class BufferedSoundStream;

}

/// Sound synthesis example.
/// This sample demonstrates:
///     - Playing back a sound stream produced on-the-fly by a simple CPU synthesis algorithm
class SoundSynthesis : public Sample
{
    URHO3D_OBJECT(SoundSynthesis, Sample);

public:
    /// Construct.
    explicit SoundSynthesis(Context* context);

    /// Setup before engine initialization. Modifies the engine parameters.
    void Setup() override;
    /// Setup after engine initialization and before running the main loop.
    void Start() override;

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    String GetScreenJoystickPatchString() const override { return
        "<patch>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button2']]\">"
        "        <attribute name=\"Is Visible\" value=\"false\" />"
        "    </add>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">"
        "        <attribute name=\"Is Visible\" value=\"false\" />"
        "    </add>"
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />"
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Up</replace>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">"
        "        <element type=\"Text\">"
        "            <attribute name=\"Name\" value=\"KeyBinding\" />"
        "            <attribute name=\"Text\" value=\"UP\" />"
        "        </element>"
        "    </add>"
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />"
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Down</replace>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">"
        "        <element type=\"Text\">"
        "            <attribute name=\"Name\" value=\"KeyBinding\" />"
        "            <attribute name=\"Text\" value=\"DOWN\" />"
        "        </element>"
        "    </add>"
        "</patch>";
    }

private:
    /// Construct the sound stream and start playback.
    void CreateSound();
    /// Buffer more sound data.
    void UpdateSound();
    /// Construct an instruction text to the UI.
    void CreateInstructions();
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    /// Scene node for the sound component.
    SharedPtr<Node> node_;
    /// Sound stream that we update.
    SharedPtr<BufferedSoundStream> soundStream_;
    /// Instruction text.
    SharedPtr<Text> instructionText_;
    /// Filter coefficient for the sound.
    float filter_;
    /// Synthesis accumulator.
    float accumulator_;
    /// First oscillator.
    float osc1_;
    /// Second oscillator.
    float osc2_;
};
