//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include <Urho3D/Audio/Audio.h>
#include <Urho3D/Audio/AudioEvents.h>
#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundSource.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Slider.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIEvents.h>

#include "SoundEffects.h"

#include <Urho3D/DebugNew.h>

// Custom variable identifier for storing sound effect name within the UI element
static const StringHash VAR_SOUNDRESOURCE("SoundResource");
static const unsigned NUM_SOUNDS = 3;

static const char* soundNames[] = {
    "Fist",
    "Explosion",
    "Power-up"
};

static const char* soundResourceNames[] = {
    "Sounds/PlayerFistHit.wav",
    "Sounds/BigExplosion.wav",
    "Sounds/Powerup.wav"
};

URHO3D_DEFINE_APPLICATION_MAIN(SoundEffects)

SoundEffects::SoundEffects(Context* context) :
    Sample(context),
    musicSource_(nullptr)
{
}

void SoundEffects::Setup()
{
    // Modify engine startup parameters
    Sample::Setup();
    engineParameters_[EP_SOUND] = true;
}

void SoundEffects::Start()
{
    // Execute base class startup
    Sample::Start();

    // Create a scene which will not be actually rendered, but is used to hold SoundSource components while they play sounds
    scene_ = new Scene(context_);

    // Create music sound source
    musicSource_ = scene_->CreateComponent<SoundSource>();
    // Set the sound type to music so that master volume control works correctly
    musicSource_->SetSoundType(SOUND_MUSIC);

    // Enable OS cursor
    GetSubsystem<Input>()->SetMouseVisible(true);

    // Create the user interface
    CreateUI();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);
}

void SoundEffects::CreateUI()
{
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    auto* cache = GetSubsystem<ResourceCache>();
    auto* uiStyle = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    // Set style to the UI root so that elements will inherit it
    root->SetDefaultStyle(uiStyle);

    // Create buttons for playing back sounds
    for (unsigned i = 0; i < NUM_SOUNDS; ++i)
    {
        Button* button = CreateButton(i * 140 + 20, 20, 120, 40, soundNames[i]);
        // Store the sound effect resource name as a custom variable into the button
        button->SetVar(VAR_SOUNDRESOURCE, soundResourceNames[i]);
        SubscribeToEvent(button, E_PRESSED, URHO3D_HANDLER(SoundEffects, HandlePlaySound));
    }

    // Create buttons for playing/stopping music
    Button* button = CreateButton(20, 80, 120, 40, "Play Music");
    SubscribeToEvent(button, E_RELEASED, URHO3D_HANDLER(SoundEffects, HandlePlayMusic));

    button = CreateButton(160, 80, 120, 40, "Stop Music");
    SubscribeToEvent(button, E_RELEASED, URHO3D_HANDLER(SoundEffects, HandleStopMusic));

    auto* audio = GetSubsystem<Audio>();

    // Create sliders for controlling sound and music master volume
    Slider* slider = CreateSlider(20, 140, 200, 20, "Sound Volume");
    slider->SetValue(audio->GetMasterGain(SOUND_EFFECT));
    SubscribeToEvent(slider, E_SLIDERCHANGED, URHO3D_HANDLER(SoundEffects, HandleSoundVolume));

    slider = CreateSlider(20, 200, 200, 20, "Music Volume");
    slider->SetValue(audio->GetMasterGain(SOUND_MUSIC));
    SubscribeToEvent(slider, E_SLIDERCHANGED, URHO3D_HANDLER(SoundEffects, HandleMusicVolume));
}

Button* SoundEffects::CreateButton(int x, int y, int xSize, int ySize, const String& text)
{
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    auto* cache = GetSubsystem<ResourceCache>();
    auto* font = cache->GetResource<Font>("Fonts/Anonymous Pro.ttf");

    // Create the button and center the text onto it
    auto* button = root->CreateChild<Button>();
    button->SetStyleAuto();
    button->SetPosition(x, y);
    button->SetSize(xSize, ySize);

    auto* buttonText = button->CreateChild<Text>();
    buttonText->SetAlignment(HA_CENTER, VA_CENTER);
    buttonText->SetFont(font, 12);
    buttonText->SetText(text);

    return button;
}

Slider* SoundEffects::CreateSlider(int x, int y, int xSize, int ySize, const String& text)
{
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    auto* cache = GetSubsystem<ResourceCache>();
    auto* font = cache->GetResource<Font>("Fonts/Anonymous Pro.ttf");

    // Create text and slider below it
    auto* sliderText = root->CreateChild<Text>();
    sliderText->SetPosition(x, y);
    sliderText->SetFont(font, 12);
    sliderText->SetText(text);

    auto* slider = root->CreateChild<Slider>();
    slider->SetStyleAuto();
    slider->SetPosition(x, y + 20);
    slider->SetSize(xSize, ySize);
    // Use 0-1 range for controlling sound/music master volume
    slider->SetRange(1.0f);

    return slider;
}

void SoundEffects::HandlePlaySound(StringHash eventType, VariantMap& eventData)
{
    auto* button = static_cast<Button*>(GetEventSender());
    const String& soundResourceName = button->GetVar(VAR_SOUNDRESOURCE).GetString();

    // Get the sound resource
    auto* cache = GetSubsystem<ResourceCache>();
    auto* sound = cache->GetResource<Sound>(soundResourceName);

    if (sound)
    {
        // Create a SoundSource component for playing the sound. The SoundSource component plays
        // non-positional audio, so its 3D position in the scene does not matter. For positional sounds the
        // SoundSource3D component would be used instead
        auto* soundSource = scene_->CreateComponent<SoundSource>();
        // Component will automatically remove itself when the sound finished playing
        soundSource->SetAutoRemoveMode(REMOVE_COMPONENT);
        soundSource->Play(sound);
        // In case we also play music, set the sound volume below maximum so that we don't clip the output
        soundSource->SetGain(0.75f);
    }
}

void SoundEffects::HandlePlayMusic(StringHash eventType, VariantMap& eventData)
{
    auto* cache = GetSubsystem<ResourceCache>();
    auto* music = cache->GetResource<Sound>("Music/Ninja Gods.ogg");
    // Set the song to loop
    music->SetLooped(true);

    musicSource_->Play(music);
}

void SoundEffects::HandleStopMusic(StringHash eventType, VariantMap& eventData)
{
    // Remove the music player node from the scene
    musicSource_->Stop();
}

void SoundEffects::HandleSoundVolume(StringHash eventType, VariantMap& eventData)
{
    using namespace SliderChanged;

    float newVolume = eventData[P_VALUE].GetFloat();
    GetSubsystem<Audio>()->SetMasterGain(SOUND_EFFECT, newVolume);
}

void SoundEffects::HandleMusicVolume(StringHash eventType, VariantMap& eventData)
{
    using namespace SliderChanged;

    float newVolume = eventData[P_VALUE].GetFloat();
    GetSubsystem<Audio>()->SetMasterGain(SOUND_MUSIC, newVolume);
}
