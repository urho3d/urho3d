//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include <Urho3D/Audio/BufferedSoundStream.h>
#include <Urho3D/Audio/SoundSource.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>

#include "SoundSynthesis.h"

#include <Urho3D/DebugNew.h>

// Expands to this example's entry-point
URHO3D_DEFINE_APPLICATION_MAIN(SoundSynthesis)

SoundSynthesis::SoundSynthesis(Context* context) :
    Sample(context),
    filter_(0.5f),
    accumulator_(0.0f),
    osc1_(0.0f),
    osc2_(180.0f)
{
}

void SoundSynthesis::Setup()
{
    // Modify engine startup parameters
    Sample::Setup();
    engineParameters_["Sound"] = true;
}

void SoundSynthesis::Start()
{
    // Execute base class startup
    Sample::Start();

    // Create the sound stream & start playback
    CreateSound();

    // Create the UI content
    CreateInstructions();

    // Hook up to the frame update events
    SubscribeToEvents();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);
}

void SoundSynthesis::CreateSound()
{
    // Sound source needs a node so that it is considered enabled
    node_ = new Node(context_);
    SoundSource* source = node_->CreateComponent<SoundSource>();

    soundStream_ = new BufferedSoundStream();
    // Set format: 44100 Hz, sixteen bit, mono
    soundStream_->SetFormat(44100, true, false);

    // Start playback. We don't have data in the stream yet, but the SoundSource will wait until there is data,
    // as the stream is by default in the "don't stop at end" mode
    source->Play(soundStream_);
}

void SoundSynthesis::UpdateSound()
{
    // Try to keep 1/10 seconds of sound in the buffer, to avoid both dropouts and unnecessary latency
    float targetLength = 1.0f / 10.0f;
    float requiredLength = targetLength - soundStream_->GetBufferLength();
    if (requiredLength < 0.0f)
        return;

    unsigned numSamples = (unsigned)(soundStream_->GetFrequency() * requiredLength);
    if (!numSamples)
        return;

    // Allocate a new buffer and fill it with a simple two-oscillator algorithm. The sound is over-amplified
    // (distorted), clamped to the 16-bit range, and finally lowpass-filtered according to the coefficient
    SharedArrayPtr<signed short> newData(new signed short[numSamples]);
    for (unsigned i = 0; i < numSamples; ++i)
    {
        osc1_ = fmodf(osc1_ + 1.0f, 360.0f);
        osc2_ = fmodf(osc2_ + 1.002f, 360.0f);

        float newValue = Clamp((Sin(osc1_) + Sin(osc2_)) * 100000.0f, -32767.0f, 32767.0f);
        accumulator_ = Lerp(accumulator_, newValue, filter_);
        newData[i] = (int)accumulator_;
    }

    // Queue buffer to the stream for playback
    soundStream_->AddData(newData, numSamples * sizeof(signed short));
}

void SoundSynthesis::CreateInstructions()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    // Construct new Text object, set string to display and font to use
    instructionText_ = ui->GetRoot()->CreateChild<Text>();
    instructionText_->SetText("Use cursor up and down to control sound filtering");
    instructionText_->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);

    // Position the text relative to the screen center
    instructionText_->SetTextAlignment(HA_CENTER);
    instructionText_->SetHorizontalAlignment(HA_CENTER);
    instructionText_->SetVerticalAlignment(VA_CENTER);
    instructionText_->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}

void SoundSynthesis::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(SoundSynthesis, HandleUpdate));
}

void SoundSynthesis::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Use keys to control the filter constant
    Input* input = GetSubsystem<Input>();
    if (input->GetKeyDown(KEY_UP))
        filter_ += timeStep * 0.5f;
    if (input->GetKeyDown(KEY_DOWN))
        filter_ -= timeStep * 0.5f;
    filter_ = Clamp(filter_, 0.01f, 1.0f);

    instructionText_->SetText("Use cursor up and down to control sound filtering\n"
        "Coefficient: " + String(filter_));

    UpdateSound();
}
