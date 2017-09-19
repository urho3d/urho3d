-- Sound effects example
-- This sample demonstrates:
--     - Playing sound effects and music
--     - Controlling sound and music master volume

require "LuaScripts/Utilities/Sample"

local soundNames = {
    "Fist",
    "Explosion",
    "Power-up"
    }

local soundResourceNames = {
    "Sounds/PlayerFistHit.wav",
    "Sounds/BigExplosion.wav",
    "Sounds/Powerup.wav"
    }

local musicSource

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create a scene which will not be actually rendered, but is used to hold SoundSource components while they play sounds
    scene_ = Scene()

    -- Create music sound source
    musicSource = scene_:CreateComponent("SoundSource")
    -- Set the sound type to music so that master volume control works correctly
    musicSource.soundType = SOUND_MUSIC

    -- Enable OS cursor
    input.mouseVisible = true

    -- Create the user interface
    CreateUI()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)
end

function CreateUI()

    local uiStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")
    -- Set style to the UI root so that elements will inherit it
    ui.root.defaultStyle = uiStyle

    -- Create buttons for playing back sounds
    for i, v in ipairs(soundNames) do
        local button = CreateButton((i - 1) * 140 + 20, 20, 120, 40, v)
        -- Store the sound effect resource name as a custom variable into the button
        button:SetVar(StringHash("SoundResource"), Variant(soundResourceNames[i]))
        SubscribeToEvent(button, "Pressed", "HandlePlaySound")
    end

    -- Create buttons for playing/stopping music
    local button = CreateButton(20, 80, 120, 40, "Play Music")
    SubscribeToEvent(button, "Released", "HandlePlayMusic")

    button = CreateButton(160, 80, 120, 40, "Stop Music")
    SubscribeToEvent(button, "Released", "HandleStopMusic")

    -- Create sliders for controlling sound and music master volume
    local slider = CreateSlider(20, 140, 200, 20, "Sound Volume")
    slider.value = audio:GetMasterGain(SOUND_EFFECT)
    SubscribeToEvent(slider, "SliderChanged", "HandleSoundVolume")

    slider = CreateSlider(20, 200, 200, 20, "Music Volume")
    slider.value = audio:GetMasterGain(SOUND_MUSIC)
    SubscribeToEvent(slider, "SliderChanged", "HandleMusicVolume")
end

function CreateButton(x, y, xSize, ySize, text)
    local font = cache:GetResource("Font", "Fonts/Anonymous Pro.ttf")

    -- Create the button and center the text onto it
    local button = ui.root:CreateChild("Button")
    button:SetStyleAuto()
    button:SetPosition(x, y)
    button:SetSize(xSize, ySize)

    local buttonText = button:CreateChild("Text")
    buttonText:SetAlignment(HA_CENTER, VA_CENTER)
    buttonText:SetFont(font, 12)
    buttonText:SetText(text)

    return button
end

function CreateSlider(x, y, xSize, ySize, text)
    local font = cache:GetResource("Font", "Fonts/Anonymous Pro.ttf")

    -- Create text and slider below it
    local sliderText = ui.root:CreateChild("Text")
    sliderText:SetPosition(x, y)
    sliderText:SetFont(font, 12)
    sliderText:SetText(text)

    local slider = ui.root:CreateChild("Slider")
    slider:SetStyleAuto()
    slider:SetPosition(x, y + 20)
    slider:SetSize(xSize, ySize)
    -- Use 0-1 range for controlling sound/music master volume
    slider.range = 1.0

    return slider
end

function HandlePlaySound(sender, eventType, eventData)
    local button = tolua.cast(GetEventSender(), "Button")
    local soundResourceName = button:GetVar(StringHash("SoundResource")):GetString()

    -- Get the sound resource
    local sound = cache:GetResource("Sound", soundResourceName)

    if sound ~= nil then
        -- Create a SoundSource component for playing the sound. The SoundSource component plays
        -- non-positional audio, so its 3D position in the scene does not matter. For positional sounds the
        -- SoundSource3D component would be used instead
        local soundSource = scene_:CreateComponent("SoundSource")
        soundSource:SetAutoRemoveMode(REMOVE_COMPONENT)
        soundSource:Play(sound)
        -- In case we also play music, set the sound volume below maximum so that we don't clip the output
        soundSource.gain = 0.7
    end
end

function HandlePlayMusic(eventType, eventData)
    local music = cache:GetResource("Sound", "Music/Ninja Gods.ogg")
    -- Set the song to loop
    music.looped = true

    musicSource:Play(music)
end

function HandleStopMusic(eventType, eventData)
    musicSource:Stop()
end

function HandleSoundVolume(eventType, eventData)
    local newVolume = eventData["Value"]:GetFloat()
    audio:SetMasterGain(SOUND_EFFECT, newVolume)
end

function HandleMusicVolume(eventType, eventData)
    local newVolume = eventData["Value"]:GetFloat()
    audio:SetMasterGain(SOUND_MUSIC, newVolume)
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button2']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "</patch>"
end
