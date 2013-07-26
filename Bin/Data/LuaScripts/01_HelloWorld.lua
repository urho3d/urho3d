ExecuteFile("LuaScripts/Utilities/Sample.lua")

function Start()
    SampleStart()
    
    CreateText()
end

function Stop()

    SampleStop()
end

function CreateText()
    local cache = GetCache()
    local context = GetContext()
    local helloText = Text:new(context)

    helloText:SetText("Hello World from Urho3D!");

    helloText:SetFont(cache:GetFont("Fonts/Anonymous Pro.ttf"), 30)
    helloText:SetColor(Color(0.0, 1.0, 0.0))

    helloText:SetHorizontalAlignment(HA_CENTER);
    helloText:SetVerticalAlignment(VA_CENTER);

    GetUI():GetRoot():AddChild(helloText)
end
