-- Rotator script object class. Script objects to be added to a scene node must implement the empty ScriptObject interface
Rotator = ScriptObject()

function Rotator:Start()
    self.rotationSpeed = {0.0, 0.0, 0.0}
end

function Rotator:SetRotationSpeed(speed)
    self.rotationSpeed[1] = speed.x;
    self.rotationSpeed[2] = speed.y;
    self.rotationSpeed[3] = speed.z;
end

function Rotator:Update(timeStep)
    local x = self.rotationSpeed[1] * timeStep
    local y = self.rotationSpeed[2] * timeStep
    local z = self.rotationSpeed[3] * timeStep
    self.node:RotateXYZ(x, y, z)
end
