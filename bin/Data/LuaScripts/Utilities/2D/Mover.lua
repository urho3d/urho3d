-- Mover script object class
--    - Handles entity (enemy, platform...) translation along a path (set of Vector2 points)
--    - Supports looping paths and animation flip
--    - Default speed is 0.8 if 'Speed' property is not set in the tmx file objects

Mover = ScriptObject()

function Mover:Start()
    self.speed = 0.8
    self.path = {}
    self.currentPathID = 2
    self.emitTime = 0
    self.fightTimer = 0
    self.flip = 0
end

function Mover:Load(deserializer)
    self:SetPathAttr(deserializer:ReadBuffer())
end

function Mover:Save(serializer)
    serializer:WriteBuffer(self:GetPathAttr())
end

function Mover:SetPathAttr(buffer)
    if buffer.size == 0 then
        return
    end

    while not buffer.eof do
        table.insert(self.path, buffer:ReadVector2())
    end
end

function Mover:GetPathAttr()
    local ret = VectorBuffer()

    for i=1, table.maxn(self.path) do
        ret:WriteVector2(self.path[i])
    end

    return ret
end

function Mover:Update(timeStep)
    if table.maxn(self.path) < 2 then
        return
    end

    local node = self.node

    -- Handle Orc states (idle/wounded/fighting)
    if node.name == "Orc" then
        local animatedSprite = node:GetComponent("AnimatedSprite2D")
        local anim = "run"

        -- Handle wounded state
        if self.emitTime > 0 then
            self.emitTime = self.emitTime + timeStep
            anim = "dead"

            -- Handle dead
            if self.emitTime >= 3 then
                self.node:Remove()
                return
            end
        else
            -- Handle fighting state
            if self.fightTimer > 0 then
                anim = "attack"
                self.flip = character2DNode.position.x - node.position.x
                self.fightTimer = self.fightTimer + timeStep
                if self.fightTimer >= 3 then
                    self.fightTimer = 0 -- Reset
                end
            end
            -- Flip Orc animation according to speed, or player position when fighting
            animatedSprite.flipX = self.flip >= 0
        end
        -- Animate
        if animatedSprite.animation ~= anim then
            animatedSprite:SetAnimation(anim)
        end
    end

    -- Don't move if fighting or wounded
    if self.fightTimer > 0 or self.emitTime > 0 then
        return
    end

    -- Set direction and move to target
    local dir = self.path[self.currentPathID] - node.position2D
    local dirNormal = dir:Normalized()
    node:Translate(Vector3(dirNormal.x, dirNormal.y, 0) * Abs(self.speed) * timeStep)
    self.flip = dir.x

    if Abs(dir:Length()) < 0.1 then
        if self.speed > 0 then
            if self.currentPathID + 1 <= table.maxn(self.path) then
                self.currentPathID = self.currentPathID + 1
            else
                -- If loop, go to first waypoint, which equates to last one (and never reverse)
                if self.path[self.currentPathID] == self.path[1] then
                    self.currentPathID = 1
                    return
                end
                -- Reverse path if not looping
                self.currentPathID = self.currentPathID - 1
                self.speed = -self.speed
            end
        else
            if self.currentPathID - 1 > 0 then
                self.currentPathID = self.currentPathID - 1
            else
                -- Reverse path
                self.currentPathID = 2
                self.speed = -self.speed
            end
        end
    end
end