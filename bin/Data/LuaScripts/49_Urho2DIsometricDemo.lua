-- Tile map example.
-- This sample demonstrates:
--    - Creating an isometric 2D scene with tile map
--    - Displaying the scene using the Renderer subsystem
--    - Handling keyboard to move a character and zoom 2D camera
--    - Generating physics shapes from the tmx file's objects
--    - Displaying debug geometry for physics and tile map
-- Note that this sample uses some functions from Sample2D utility class.

require "LuaScripts/Utilities/Sample"
require "LuaScripts/Utilities/2D/Sample2D"


function Start()
    -- Set filename for load/save functions
    demoFilename = "Isometric2D"

    -- Execute the common startup for samples
    SampleStart()

    -- Create the scene content
    CreateScene()

    -- Create the UI content
    CreateUIContent("ISOMETRIC 2.5D DEMO")

    -- Hook up to the frame update events
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()

    -- Create the Octree, DebugRenderer and PhysicsWorld2D components to the scene
    scene_:CreateComponent("Octree")
    scene_:CreateComponent("DebugRenderer")
    local physicsWorld = scene_:CreateComponent("PhysicsWorld2D")
    physicsWorld.gravity = Vector2.ZERO -- Neutralize gravity as the character will always be grounded

    -- Create camera
    cameraNode = Node()
    local camera = cameraNode:CreateComponent("Camera")
    camera.orthographic = true
    camera.orthoSize = graphics.height * PIXEL_SIZE
    zoom = 2 * Min(graphics.width / 1280, graphics.height / 800) -- Set zoom according to user's resolution to ensure full visibility (initial zoom (2) is set for full visibility at 1280x800 resolution)
    camera.zoom = zoom

    -- Setup the viewport for displaying the scene
    renderer:SetViewport(0, Viewport:new(scene_, camera))
    renderer.defaultZone.fogColor = Color(0.2, 0.2, 0.2) -- Set background color for the scene

    -- Create tile map from tmx file
    local tmxFile = cache:GetResource("TmxFile2D", "Urho2D/Tilesets/atrium.tmx")
    local tileMapNode = scene_:CreateChild("TileMap")
    local tileMap = tileMapNode:CreateComponent("TileMap2D")
    tileMap.tmxFile = tmxFile
    local info = tileMap.info

    -- Create Spriter Imp character (from sample 33_SpriterAnimation)
    CreateCharacter(info, true, 0, Vector3(-5, 11, 0), 0.15)

    -- Generate physics collision shapes from the tmx file's objects located in "Physics" (top) layer
    local tileMapLayer = tileMap:GetLayer(tileMap.numLayers - 1)
    CreateCollisionShapesFromTMXObjects(tileMapNode, tileMapLayer, info)

    -- Instantiate enemies and moving platforms at each placeholder of "MovingEntities" layer (placeholders are Poly Line objects defining a path from points)
    PopulateMovingEntities(tileMap:GetLayer(tileMap.numLayers - 2))

    -- Instantiate coins to pick at each placeholder of "Coins" layer (placeholders for coins are Rectangle objects)
    PopulateCoins(tileMap:GetLayer(tileMap.numLayers - 3))

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

    -- Subscribe to PostRenderUpdate to draw physics shapes
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate")

    -- Subscribe to Box2D contact listeners
    SubscribeToEvent("PhysicsBeginContact2D", "HandleCollisionBegin")

    -- Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent("SceneUpdate")
end

function HandleUpdate(eventType, eventData)
    -- Zoom in/out
    Zoom(cameraNode:GetComponent("Camera"))

    -- Toggle debug geometry with spacebar
    if input:GetKeyPress(KEY_Z) then drawDebug = not drawDebug end

    -- Check for loading / saving the scene
    if input:GetKeyPress(KEY_F5) then
        SaveScene()
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
        scene_:GetComponent("PhysicsWorld2D"):DrawDebugGeometry(true)
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
    local character = character2DNode:GetScriptObject("Character2D")

    -- Handle coins picking
    if nodeName == "Coin" then
        hitNode:Remove()
        character.remainingCoins = character.remainingCoins - 1
        if character.remainingCoins == 0 then
            local instructions = ui.root:GetChild("Instructions", true)
            instructions.text = "!!! You got all the coins !!!"
        end
        local coinsText = ui.root:GetChild("CoinsText", true)
        coinsText.text = character.remainingCoins -- Update coins UI counter
        PlaySound("Powerup.wav")
    end

    -- Handle interactions with enemies
    if nodeName == "Orc" then
        local animatedSprite = character2DNode:GetComponent("AnimatedSprite2D")
        local deltaX = character2DNode.position.x - hitNode.position.x

        -- Orc killed if character is fighting in its direction when the contact occurs
        if animatedSprite.animation == "attack" and deltaX < 0 == animatedSprite.flipX then
            hitNode:GetScriptObject("Mover").emitTime = 1
            if hitNode:GetChild("Emitter", true) == nil then
                hitNode:GetComponent("RigidBody2D"):Remove() -- Remove Orc's body
                SpawnEffect(hitNode)
                PlaySound("BigExplosion.wav")
            end
        -- Player killed if not fighting in the direction of the Orc when the contact occurs
        else
            if character2DNode:GetChild("Emitter", true) == nil then
                character.wounded = true
                if nodeName == "Orc" then
                    hitNode:GetScriptObject("Mover").fightTimer = 1
                end
                SpawnEffect(character2DNode)
                PlaySound("BigExplosion.wav")
            end
        end
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

    local node = self.node
    local animatedSprite = node:GetComponent("AnimatedSprite2D")

    -- Set direction
    local moveDir = Vector3.ZERO -- Reset
    local speedX = Clamp(MOVE_SPEED_X / zoom, 0.4, 1)
    local speedY = speedX

    if input:GetKeyDown(KEY_LEFT) or input:GetKeyDown(KEY_A) then
        moveDir = moveDir + Vector3.LEFT * speedX
        animatedSprite.flipX = false -- Flip sprite (reset to default play on the X axis)
    end
    if input:GetKeyDown(KEY_RIGHT) or input:GetKeyDown(KEY_D) then
        moveDir = moveDir + Vector3.RIGHT * speedX
        animatedSprite.flipX = true -- Flip sprite (flip animation on the X axis)
    end

    if not moveDir:Equals(Vector3.ZERO) then
        speedY = speedX * MOVE_SPEED_SCALE
    end

    if input:GetKeyDown(KEY_UP) or input:GetKeyDown(KEY_W) then
        moveDir = moveDir + Vector3.UP * speedY
    end
    if input:GetKeyDown(KEY_DOWN) or input:GetKeyDown(KEY_S) then
        moveDir = moveDir + Vector3.DOWN * speedY
    end

    -- Move
    if not moveDir:Equals(Vector3.ZERO) then
        node:Translate(moveDir * timeStep)
    end

    -- Animate
    if input:GetKeyDown(KEY_SPACE) then
        if animatedSprite.animation ~= "attack" then
            animatedSprite:SetAnimation("attack", LM_FORCE_LOOPED)
        end
    elseif not moveDir:Equals(Vector3.ZERO) then
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

    if self.timer > 2.0 then
        -- Reset timer
        self.timer = 0.0

        -- Clear forces (should be performed by setting linear velocity to zero, but currently doesn't work)
        body.linearVelocity = Vector2(0.0, 0.0)
        body.awake = false
        body.awake = true

        -- Remove particle emitter
        node:GetChild("Emitter", true):Remove()

        -- Update lifes UI and counter
        self.remainingLifes = self.remainingLifes - 1
        local lifeText = ui.root:GetChild("LifeText", true)
        lifeText.text = self.remainingLifes -- Update lifes UI counter

        -- Reset wounded state
        self.wounded = false

        -- Handle death
        if self.remainingLifes == 0 then
            self:HandleDeath()
            return
        end

        -- Re-position the character to the nearest point
        if node.position.x < 15.0 then
            node.position = Vector3(1.0, 8.0, 0.0)
        else
            node.position = Vector3(18.8, 9.2, 0.0)
        end
    end
end

function Character2D:HandleDeath()

    local node = self.node
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
    node.position = Vector3(-20.0, 0.0, 0.0)
    node:SetScale(1.2)

    -- Play death animation once
    if animatedSprite.animation ~= "dead2" then
        animatedSprite:SetAnimation("dead2")
    end
end