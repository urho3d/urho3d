-- Rotator script object class. Script objects to be added to a scene node must implement the empty ScriptObject interface
Rotator = ScriptObject()

function Rotator:Start()
    self.rotationSpeed = Vector3(0, 0, 0)
end

function Rotator:SetRotationSpeed(speed)
    -- Need to make a copy of the speed object because in this sample demo the speed object is transient on C++ side
    self.rotationSpeed = Vector3(speed)
end

function Rotator:Update(timeStep)
    local x = self.rotationSpeed.x * timeStep
    local y = self.rotationSpeed.y * timeStep
    local z = self.rotationSpeed.z * timeStep
    self.node:Rotate(Quaternion(x, y, z))
end
