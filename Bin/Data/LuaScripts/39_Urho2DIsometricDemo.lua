-- Urho2D tile map example.
-- This sample demonstrates:
--     - Creating an isometric 2D scene with tile map
--     - Displaying the scene using the Renderer subsystem
--     - Handling keyboard to move a character and zoom 2D camera
--     - Generating physics shapes from the tmx file's objects
-- Note that this sample uses some functions from Sample2D utility class.

require "LuaScripts/Utilities/Sample"
require "LuaScripts/Utilities/Sample2D"


function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create the scene content
    CreateScene()

    -- Create the UI content
    CreateInstructions("Use WASD keys or arrows to move,\nPageUp/PageDown/MouseWheel to zoom,\nF5/F7 to save/reload scene,\n'Z' to toggle debug geometry\nSpace to fight")

    -- Hook up to the frame update events
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()

    -- Create the Octree, DebugRenderer and PhysicsWorld2D component to the scene
    scene_:CreateComponent("Octree")
    scene_:CreateComponent("DebugRenderer")
    local physicsWorld = scene_:CreateComponent("PhysicsWorld2D")
    physicsWorld.gravity = Vector2.ZERO -- Neutralize gravity as the character will always be grounded

    -- Create camera and define viewport
    cameraNode = Node() -- scene_:CreateChild("Camera")
    local camera = cameraNode:CreateComponent("Camera")
    camera.orthographic = true
    camera.orthoSize = graphics.height * PIXEL_SIZE
    zoom = 2 * Min(graphics.width / 1280, graphics.height / 800) -- Set zoom according to user's resolution to ensure full visibility (initial zoom (2) is set for full visibility at 1280x800 resolution)
    camera.zoom = zoom
    renderer:SetViewport(0, Viewport:new(scene_, camera))

    -- Get tmx file
    local tmxFile = cache:GetResource("TmxFile2D", "Urho2D/Tilesets/atrium.tmx")
    if tmxFile == nil then
        return
    end

    local tileMapNode = scene_:CreateChild("TileMap")
    local tileMap = tileMapNode:CreateComponent("TileMap2D")
    tileMap.tmxFile = tmxFile
    local info = tileMap.info

    -- Get top layer ("Physics") which stores the objects for shapes
    local tileMapLayer = tileMap:GetLayer(tileMap.numLayers - 1)

    -- Generate physics collision shapes from the tmx file's objects located in "Physics" layer
    CreateCollisionShapesFromTMXObjects(tileMapNode, tileMapLayer, info)

    -- Create Spriter Imp character (from sample 33_SpriterAnimation)
    CreateCharacter(info, true, 0, Vector3(-5, 11, 0))
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate")

    -- Subscribe HandlePostUpdate() function for processing post update events
    SubscribeToEvent("PostUpdate", "HandlePostUpdate")

    -- Subscribe to PostRenderUpdate to draw physics shapes
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate")

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
        scene_:SaveXML(fileSystem:GetProgramDir().."Data/Scenes/TileMap.xml")
    end
    if input:GetKeyPress(KEY_F7) then
        scene_:LoadXML(fileSystem:GetProgramDir().."Data/Scenes/TileMap.xml")
        -- After loading we have to reacquire the character scene node, as it has been recreated
        -- Simply find by name as there's only one of them
        character2DNode = scene_:GetChild("Imp", true);
        if character2DNode == nil then
            return
        end
    end
end

function HandlePostUpdate(eventType, eventData)
    if character2DNode == nil or cameraNode == nil then
        return
    end
    cameraNode.position = Vector3(character2DNode.position.x, character2DNode.position.y, -10) -- Camera tracks character
end

function HandlePostRenderUpdate(eventType, eventData)
    if drawDebug then scene_:GetComponent("PhysicsWorld2D"):DrawDebugGeometry(true) end
end

-- Character2D script object class
Character2D = ScriptObject()

function Character2D:Update(timeStep)
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
            animatedSprite:SetAnimation("run", LM_FORCE_LOOPED)
        end
    elseif animatedSprite.animation ~= "idle" then
        animatedSprite:SetAnimation("idle", LM_FORCE_LOOPED)
    end
end
