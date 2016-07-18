-- Http request example.
-- This example demonstrates:
--     - How to use Http request API

require "LuaScripts/Utilities/Sample"

local message = ""
local text = nil
local httpRequest = nil

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create the user interface
    CreateUI()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)

    -- Subscribe to basic events such as update
    SubscribeToEvents()
end

function CreateUI()
    -- Construct new Text object
    text = Text:new()

    -- Set font and text color
    text:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15)
    text.color = Color(1.0, 1.0, 0.0)

    -- Align Text center-screen
    text.horizontalAlignment = HA_CENTER
    text.verticalAlignment = VA_CENTER

    -- Add Text instance to the UI root element
    ui.root:AddChild(text)
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing HTTP request
    SubscribeToEvent("Update", "HandleUpdate")
end

function HandleUpdate(eventType, eventData)
    -- Create HTTP request
    if httpRequest == nil then
        httpRequest = network:MakeHttpRequest("http://httpbin.org/ip")
    else
        -- Initializing HTTP request
        if httpRequest.state == HTTP_INITIALIZING then
            return
        -- An error has occured
        elseif httpRequest.state == HTTP_ERROR then
            text.text = "An error has occured."
            UnsubscribeFromEvent("Update")
        -- Get message data
        else
            if httpRequest.availableSize > 0 then
                message = message .. httpRequest:ReadLine()
            else
                text.text = "Processing..."

                local json = JSONFile:new()
                json:FromString(message)

                local val = json:GetRoot():Get("origin")

                if val.isNull then
                    text.text = "Invalid string."
                else
                    text.text =  "Your IP is: " .. val:GetString()
                end

                json:delete()
                httpRequest:delete()

                UnsubscribeFromEvent("Update")
            end       
        end
    end
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "</patch>"
end
