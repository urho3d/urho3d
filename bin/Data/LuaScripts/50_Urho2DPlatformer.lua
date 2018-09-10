-- Urho2D platformer example.
-- This sample demonstrates:
--    - Creating an orthogonal 2D scene from tile map file
--    - Displaying the scene using the Renderer subsystem
--    - Handling keyboard to move a character and zoom 2D camera
--    - Generating physics shapes from the tmx file's objects
--    - Mixing physics and translations to move the character
--    - Using Box2D Contact listeners to handle the gameplay
--    - Displaying debug geometry for physics and tile map
-- Note that this sample uses some functions from Sample2D utility class.

require "LuaScripts/Utilities/Sample"
require "LuaScripts/Utilities/2D/Sample2D"


function Start()
    -- Set filename for load/save functions
    demoFilename = "Platformer2D"

    -- Execute the common startup for samples
    SampleStart()

    -- Create the scene content
    CreateScene()

    -- Create the UI content
    CreateUIContent("PLATFORMER 2D DEMO")

    -- Hook up to the frame update events
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()

    -- Create the Octree, DebugRenderer and PhysicsWorld2D components to the scene
    scene_:CreateComponent("Octree")
    scene_:CreateComponent("DebugRenderer")
    scene_:CreateComponent("PhysicsWorld2D")

    -- Create camera
    cameraNode = Node()
    local camera = cameraNode:CreateComponent("Camera")
    camera.orthographic = true
    camera.orthoSize = graphics.height * PIXEL_SIZE
    camera.zoom = 1.8 * Min(graphics.width / 1280, graphics.height / 800) -- Set zoom according to user's resolution to ensure full visibility (initial zoom (1.8) is set for full visibility at 1280x800 resolution)

    -- Setup the viewport for displaying the scene
    renderer:SetViewport(0, Viewport:new(scene_, camera))
    renderer.defaultZone.fogColor = Color(0.2, 0.2, 0.2) -- Set background color for the scene

    -- Create tile map from tmx file
    local tileMapNode = scene_:CreateChild("TileMap")
    local tileMap = tileMapNode:CreateComponent("TileMap2D")
    tileMap.tmxFile = cache:GetResource("TmxFile2D", "Urho2D/Tilesets/Ortho.tmx")
    local info = tileMap.info

    -- Create Spriter Imp character (from sample 33_SpriterAnimation)
    CreateCharacter(info, true, 0.8, Vector3(1, 8, 0), 0.2)

    -- Generate physics collision shapes from the tmx file's objects located in "Physics" (top) layer
    local tileMapLayer = tileMap:GetLayer(tileMap.numLayers - 1)
    CreateCollisionShapesFromTMXObjects(tileMapNode, tileMapLayer, info)

    -- Instantiate enemies and moving platforms at each placeholder of "MovingEntities" layer (placeholders are Poly Line objects defining a path from points)
    PopulateMovingEntities(tileMap:GetLayer(tileMap.numLayers - 2))

    -- Instantiate coins to pick at each placeholder of "Coins" layer (placeholders for coins are Rectangle objects)
    PopulateCoins(tileMap:GetLayer(tileMap.numLayers - 3))

    -- Instantiate triggers (for ropes, ladders, lava, slopes...) at each placeholder of "Triggers" layer (placeholders for triggers are Rectangle objects)
    PopulateTriggers(tileMap:GetLayer(tileMap.numLayers - 4))

    -- Create background
    CreateBackgroundSprite(info, 3.5, "Textures/HeightMap.png", true)

    -- Check when scene is rendered
    SubscribeToEvent("EndRendering", HandleSceneRendered)
end

function HandleSceneRendered()
    UnsubscribeFromEvent("EndRendering")
    SaveScene(true) -- Save the scene so we can reload it later
    scene_.updateEnabled = false -- Pause the scene as long as the UI is hiding it
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate")

    -- Subscribe HandlePostUpdate() function for processing post update events
    SubscribeToEvent("PostUpdate", "HandlePostUpdate")

    -- Subscribe to PostRenderUpdate to draw debug geometry
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate")

    -- Subscribe to Box2D contact listeners
    SubscribeToEvent("PhysicsBeginContact2D", "HandleCollisionBegin")
    SubscribeToEvent("PhysicsEndContact2D", "HandleCollisionEnd")

    -- Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent("SceneUpdate")
end

function HandleUpdate(eventType, eventData)
    -- Zoom in/out
    if cameraNode ~= nil then
        Zoom(cameraNode:GetComponent("Camera"))
    end

    -- Toggle debug geometry with 'Z' key
    if input:GetKeyPress(KEY_Z) then drawDebug = not drawDebug end

    -- Check for loading / saving the scene
    if input:GetKeyPress(KEY_F5) then
        SaveScene(false)
    end
    if input:GetKeyPress(KEY_F7) then
        ReloadScene(false)
    end
end

function HandlePostUpdate(eventType, eventData)
    if character2DNode == nil or cameraNode == nil then
        return
    end
    cameraNode.position = Vector3(character2DNode.position.x, character2DNode.position.y, -10) -- Camera tracks character
end

function HandlePostRenderUpdate(eventType, eventData)
    if drawDebug then
        scene_:GetComponent("PhysicsWorld2D"):DrawDebugGeometry()

        local tileMapNode = scene_:GetChild("TileMap", true)
        local map = tileMapNode:GetComponent("TileMap2D")
        map:DrawDebugGeometry(scene_:GetComponent("DebugRenderer"), false)
    end
end

function HandleCollisionBegin(eventType, eventData)
    -- Get colliding node
    local hitNode = eventData["NodeA"]:GetPtr("Node")
    if hitNode.name == "Imp" then
        hitNode = eventData["NodeB"]:GetPtr("Node")
    end
    local nodeName = hitNode.name
    local character = character2DNode:GetScriptObject()

    -- Handle ropes and ladders climbing
    if nodeName == "Climb" then
        if character.isClimbing then -- If transition between rope and top of rope (as we are using split triggers)
            character.climb2 = true
        else
            character.isClimbing = true

            -- Override gravity so that the character doesn't fall
            local body = character2DNode:GetComponent("RigidBody2D")
            body.gravityScale = 0

            -- Clear forces so that the character stops (should be performed by setting linear velocity to zero, but currently doesn't work)
            body.linearVelocity = Vector2.ZERO
            body.awake = false
            body.awake = true
        end
    end

    if nodeName == "CanJump" then
        character.aboveClimbable = true
    end

    -- Handle coins picking
    if nodeName == "Coin" then
        hitNode:Remove()
        character.remainingCoins = character.remainingCoins - 1
        if character.remainingCoins == 0 then
            ui.root:GetChild("Instructions", true).text = "!!! Go to the Exit !!!"
        end
        ui.root:GetChild("CoinsText", true).text = character.remainingCoins -- Update coins UI counter
        PlaySound("Powerup.wav")
    end

    -- Handle interactions with enemies
    if nodeName == "Enemy" or nodeName == "Orc" then
        local animatedSprite = character2DNode:GetComponent("AnimatedSprite2D")
        local deltaX = character2DNode.position.x - hitNode.position.x

        -- Orc killed if character is fighting in its direction when the contact occurs (flowers are not destroyable)
        if nodeName == "Orc" and animatedSprite.animation == "attack" and (deltaX < 0 == animatedSprite.flipX) then
            hitNode:GetScriptObject().emitTime = 1
            if not hitNode:GetChild("Emitter", true) then
                hitNode:GetComponent("RigidBody2D"):Remove() -- Remove Orc's body
                SpawnEffect(hitNode)
                PlaySound("BigExplosion.wav")
            end

        -- Player killed if not fighting in the direction of the Orc when the contact occurs, or when colliding with a flower
        else
            if not character2DNode:GetChild("Emitter", true) then
                character.wounded = true
                if nodeName == "Orc" then
                    hitNode:GetScriptObject().fightTimer = 1
                end
                SpawnEffect(character2DNode)
                PlaySound("BigExplosion.wav")
            end
        end
    end

    -- Handle exiting the level when all coins have been gathered
    if nodeName == "Exit" and character.remainingCoins == 0 then
        -- Update UI
        local instructions = ui.root:GetChild("Instructions", true)
        instructions.text = "!!! WELL DONE !!!"
        instructions.position = IntVector2.ZERO

        -- Put the character outside of the scene and magnify him
        character2DNode.position = Vector3(-20, 0, 0)
        character2DNode:SetScale(1.2)
    end

    -- Handle falling into lava
    if nodeName == "Lava" then
        local body = character2DNode:GetComponent("RigidBody2D")
        body:ApplyLinearImpulse(Vector2(0, 1) * MOVE_SPEED, body.massCenter, true) -- Violently project character out of lava
        if not character2DNode:GetChild("Emitter", true) then
            character.wounded = true
            SpawnEffect(character2DNode)
            PlaySound("BigExplosion.wav")
        end
    end

    -- Handle climbing a slope
    if nodeName == "Slope" then
        character.onSlope = true
    end
end

function HandleCollisionEnd(eventType, eventData)
    -- Get colliding node
    local hitNode = eventData["NodeA"]:GetPtr("Node")
    if hitNode.name == "Imp" then
        hitNode = eventData["NodeB"]:GetPtr("Node")
    end
    local nodeName = hitNode.name
    local character = character2DNode:GetScriptObject()

    -- Handle leaving a rope or ladder
    if nodeName == "Climb" then
        if character.climb2 then
            character.climb2 = false
        else
            character.isClimbing = false
            local body = character2DNode:GetComponent("RigidBody2D")
            body.gravityScale = 1 -- Restore gravity
        end
    end

    if nodeName == "CanJump" then
        character.aboveClimbable = false
    end

    -- Handle leaving a slope
    if nodeName == "Slope" then
        character.onSlope = false
        -- Clear forces (should be performed by setting linear velocity to zero, but currently doesn't work)
        local body = character2DNode:GetComponent("RigidBody2D")
        body.linearVelocity = Vector2.ZERO
        body.awake = false
        body.awake = true
    end
end


-- Character2D script object class
Character2D = ScriptObject()

function Character2D:Start()
    self.wounded = false
    self.killed = false
    self.timer = 0
    self.maxCoins = 0
    self.remainingCoins = 0
    self.remainingLifes = 3
    self.isClimbing = false
    self.climb2 = false -- Used only for ropes, as they are split into 2 shapes
    self.aboveClimbable = false
    self.onSlope = false
end

function Character2D:Save(serializer)
    self.isClimbing = false -- Overwrite before auto-deserialization
end

function Character2D:Update(timeStep)
    if character2DNode == nil then
        return
    end

    -- Handle wounded/killed states
    if self.killed then
        return
    end

    if self.wounded then
        self:HandleWoundedState(timeStep)
        return
    end

    -- Set temporary variables
    local node = self.node
    local body = node:GetComponent("RigidBody2D")
    local animatedSprite = node:GetComponent("AnimatedSprite2D")
    local onGround = false
    local jump = false

    -- Collision detection (AABB query)
    local characterHalfSize = Vector2(0.16, 0.16)
    local collidingBodies = scene_:GetComponent("PhysicsWorld2D"):GetRigidBodies(Rect(node.worldPosition2D - characterHalfSize - Vector2(0, 0.1), node.worldPosition2D + characterHalfSize))

    if table.maxn(collidingBodies) > 1 and not self.isClimbing then
        onGround = true
    end

    -- Set direction
    local moveDir = Vector2.ZERO -- Reset

    if input:GetKeyDown(KEY_LEFT) or input:GetKeyDown(KEY_A) then
        moveDir = moveDir + Vector2.LEFT
        animatedSprite.flipX = false -- Flip sprite (reset to default play on the X axis)
    end

    if input:GetKeyDown(KEY_RIGHT) or input:GetKeyDown(KEY_D) then
        moveDir = moveDir + Vector2.RIGHT
        animatedSprite.flipX = true -- Flip sprite (flip animation on the X axis)
    end

    -- Jump
    if (onGround or self.aboveClimbable) and (input:GetKeyPress(KEY_UP) or input:GetKeyPress(KEY_W)) then
        jump = true
    end

    -- Climb
    if self.isClimbing then
        if not self.aboveClimbable and (input:GetKeyDown(KEY_UP) or input:GetKeyDown(KEY_W)) then
            moveDir = moveDir + Vector2.UP
        end

        if input:GetKeyDown(KEY_DOWN) or input:GetKeyDown(KEY_S) then
            moveDir = moveDir + Vector2.DOWN
        end
    end

    -- Move
    if not moveDir:Equals(Vector2.ZERO) or jump then
        if self.onSlope then
            body:ApplyForceToCenter(moveDir * MOVE_SPEED / 2, true) -- When climbing a slope, apply force (todo: replace by setting linear velocity to zero when will work)
        else
            node:Translate(moveDir * timeStep * 1.8)
        end
        if jump then
            body:ApplyLinearImpulse(Vector2(0, 0.17) * MOVE_SPEED, body.massCenter, true)
        end
    end

    -- Animate
    if input:GetKeyDown(KEY_SPACE) then
        if animatedSprite.animation ~= "attack" then
            animatedSprite:SetAnimation("attack", LM_FORCE_LOOPED)
            animatedSprite.speed = 1.5
        end
    elseif not moveDir:Equals(Vector2.ZERO) then
        if animatedSprite.animation ~= "run" then
            animatedSprite:SetAnimation("run")
        end
    elseif animatedSprite.animation ~= "idle" then
        animatedSprite:SetAnimation("idle")
    end
end

function Character2D:HandleWoundedState(timeStep)
    local node = self.node
    local body = node:GetComponent("RigidBody2D")
    local animatedSprite = node:GetComponent("AnimatedSprite2D")

    -- Play "hit" animation in loop
    if animatedSprite.animation ~= "hit" then
        animatedSprite:SetAnimation("hit", LM_FORCE_LOOPED)
    end

    -- Update timer
    self.timer = self.timer + timeStep

    -- End of timer
    if self.timer > 2 then
        -- Reset timer
        self.timer = 0

        -- Clear forces (should be performed by setting linear velocity to zero, but currently doesn't work)
        body.linearVelocity = Vector2.ZERO
        body.awake = false
        body.awake = true

        -- Remove particle emitter
        node:GetChild("Emitter", true):Remove()

        -- Update lifes UI and counter
        self.remainingLifes = self.remainingLifes - 1
        ui.root:GetChild("LifeText", true).text = self.remainingLifes -- Update lifes UI counter

        -- Reset wounded state
        self.wounded = false

        -- Handle death
        if self.remainingLifes == 0 then
            self:HandleDeath()
            return
        end

        -- Re-position the character to the nearest point
        if node.position.x < 15 then
            node.position = Vector3(1, 8, 0)
        else
            node.position = Vector3(18.8, 9.2, 0)
        end
    end
end

function Character2D:HandleDeath()
    local node = self.node
    local body = node:GetComponent("RigidBody2D")
    local animatedSprite = node:GetComponent("AnimatedSprite2D")

    -- Set state to 'killed'
    self.killed = true

    -- Update UI elements
    local instructions = ui.root:GetChild("Instructions", true)
    instructions.text = "!!! GAME OVER !!!"
    ui.root:GetChild("ExitButton", true).visible = true
    ui.root:GetChild("PlayButton", true).visible = true

    -- Show mouse cursor so that we can click
    input.mouseVisible = true

    -- Put character outside of the scene and magnify him
    node.position = Vector3(-20, 0, 0)
    node:SetScale(1.2)

    -- Play death animation once
    if animatedSprite.animation ~= "dead2" then
        animatedSprite:SetAnimation("dead2")
    end
end
