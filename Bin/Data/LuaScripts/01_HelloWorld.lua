ExecuteFile("LuaScripts/Utilities/Sample.lua")

HelloWorld = {}

function HelloWorld:new()
    local o = {}
    self.__index = self
    setmetatable(o, self)
    setmetatable(self, {__index = Sample}) -- Set Sample as base class.
    return o
end

function HelloWorld:Start()
    Sample:Start() -- Call Start function in Sample.
    self:CreateText()
end

function HelloWorld:CreateText()
    local context = GetContext()
    local helloText = Text:new(context)

    helloText:SetText("Hello World from Urho3D!");

    local cache = GetCache()
    helloText:SetFont(cache:GetFont("Fonts/Anonymous Pro.ttf"), 30)
    helloText:SetColor(Color(0.0, 1.0, 0.0))
    
    helloText.horizontalAlignment = HA_CENTER;
    helloText.verticalAlignment = VA_CENTER;
    
    GetUI():GetRoot():AddChild(helloText)
end

local sample = nil

function Start()
    if sample == nil then
        sample = HelloWorld:new()
    end
    sample:Start()
end

function Stop()
    if sample ~= nil then
        sample:Stop()
    end
    sample = nil
end
