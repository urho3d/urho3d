-- Urho2D platformer example.
-- This sample demonstrates:
--    - Creating an orthogonal 2D scene with tile map
--    - Displaying the scene using the Renderer subsystem
--    - Handling keyboard to move a character and zoom 2D camera
--    - Generating physics shapes from the tmx file's objects
--    - Using physics to move the character
-- Note that this sample uses some functions from Sample2D utility class.

require "LuaScripts/Utilities/Sample"
require "LuaScripts/Utilities/Sample2D"

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create the scene content
    CreateScene()

    -- Create the UI content
    CreateInstructions("Use WASD keys or Arrows to move\nPageUp/PageDown/MouseWheel to zoom\nF5/F7 to save/reload scene\n'Z' to toggle debug geometry\nSpace to fight")

    -- Hook up to the frame update events
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()

    -- Create the Octree, DebugRenderer and PhysicsWorld2D component to the scene
    scene_:CreateComponent("Octree")
    scene_:CreateComponent("DebugRenderer")
    local physicsWorld = scene_:CreateComponent("PhysicsWorld2D")

    -- Create camera and define viewport
    cameraNode = Node()
    local camera = cameraNode:CreateComponent("Camera")
    camera.orthographic = true
    camera.orthoSize = graphics.height * PIXEL_SIZE
    camera.zoom = 1.8 * Min(graphics.width / 1280, graphics.height / 800) -- Set zoom according to user's resolution to ensure full visibility (initial zoom (1.8) is set for full visibility at 1280x800 resolution)

    -- Setup the viewport for displaying the scene
    renderer:SetViewport(0, Viewport:new(scene_, camera))
    renderer.defaultZone.fogColor = Color(0.2, 0.2, 0.2) -- Set background color for the scene

    -- Get tmx file
    local tmxFile = cache:GetResource("TmxFile2D", "Urho2D/Tilesets/Ortho.tmx")
    if tmxFile == nil then
        return
    end

    local tileMapNode = scene_:CreateChild("TileMap")
    local tileMap = tileMapNode:CreateComponent("TileMap2D")
    tileMap.tmxFile = tmxFile
    local info = tileMap.info

    -- Set "Background" layer as lowest (currently not used as we can't control layer opacity)
    local backgroundLayer = tileMap:GetLayer(2)
    backgroundLayer:SetDrawOrder(-1)

    -- Get top layer ("Physics") which stores the objects for shapes
    local tileMapLayer = tileMap:GetLayer(tileMap.numLayers - 1)

    -- Generate physics collision shapes from the tmx file's objects located in "Physics" layer
    CreateCollisionShapesFromTMXObjects(tileMapNode, tileMapLayer, info)

    -- Get "Enemies" layer which stores the placeholder objects for enemies and their paths
    local enemiesLayer = tileMap:GetLayer(tileMap.numLayers - 2)

    -- Create enemy (will be cloned at each placeholder)
    local enemyNode = CreateEnemy()

    -- Instantiate enemies at each placeholder (in this sample, placeholders are Poly Line objects defining start and end points)
    for i=0, enemiesLayer:GetNumObjects() -1 do
        local enemyObject = enemiesLayer:GetObject(i) -- Get placeholder object (TileMapObject2D)
        if enemyObject.objectType ~= OT_POLYLINE then
            print("A non Poly Line Object has been found in 'Enemies' layer and skipped")
            break
        end
        local enemyClone = scene_:GetChild("Enemy"):Clone()
        local offset = Vector2(0, 0.15)
        enemyClone.position2D = enemyObject:GetPoint(0) + offset
        local mover = enemyClone:CreateScriptObject("Mover") -- Create script object that handles enemy translation
        mover.path = CreatePathFromPoints(enemyObject) -- Set path from points
        -- Override default speed
        if enemyObject:HasProperty("Speed") then
            mover.speed = enemyObject:GetProperty("Speed")
        end
    end

    -- Get "Coins" layer which stores the placeholder objects for coins
    local coinsLayer = tileMap:GetLayer(tileMap.numLayers - 3)

    -- Create coin (will be cloned at each placeholder)
    local coinNode = CreateCoin()

    -- Instantiate coins to pick at each placeholder
    for i=0, coinsLayer:GetNumObjects() -1 do
        local coinObject = coinsLayer:GetObject(i) -- Get placeholder object (TileMapObject2D)
        local coinClone = coinNode:Clone()
        coinClone.position2D = coinObject.position + coinObject.size / 2 + Vector2(0, 0.15)
    end

    -- Get "MovingPlatforms" layer which stores the placeholder objects for moving platforms
    local platformsLayer = tileMap:GetLayer(tileMap.numLayers - 4)

    -- Create platform (will be cloned at each placeholder)
    local platformNode = CreateMovingPlatform()

    -- Instantiate moving platforms at each placeholder (in this sample, placeholders are Poly Line objects defining start and end points)
    for i=0, platformsLayer:GetNumObjects() -1 do
        local platformObject = platformsLayer:GetObject(i) -- Get placeholder object (TileMapObject2D)
        if platformObject.objectType ~= OT_POLYLINE then
            print("A non Poly Line Object has been found in 'MovingPlatforms' layer and skipped")
            break
        end
        local platformClone = platformNode:Clone()
        platformClone.position2D = platformObject:GetPoint(0)
        local mover = platformClone:CreateScriptObject("Mover") -- Create script object that handles platform translation
        mover.path = CreatePathFromPoints(platformObject) -- Set path from points
        -- Override default speed
        if platformObject:HasProperty("Speed") then
            mover.speed = platformObject:GetProperty("Speed")
        end
    end

    -- Create Spriter Imp character (from sample 33_SpriterAnimation)
    CreateCharacter(info, true, 0.8, Vector3(1, 23, 0))
end

function CreateEnemy()
    local node = scene_:CreateChild("Enemy")
    local staticSprite = node:CreateComponent("StaticSprite2D")
    staticSprite.sprite = cache:GetResource("Sprite2D", "Urho2D/Aster.png")
    local body = node:CreateComponent("RigidBody2D")
    body.bodyType = BT_STATIC
    local shape = node:CreateComponent("CollisionCircle2D") -- Create circle shape
    shape.radius = 0.32 -- Set radius
    return node
end

function CreateCoin()
    local node = scene_:CreateChild("Coin")
    node:SetScale(0.5)
    local animatedSprite = node:CreateComponent("AnimatedSprite2D")
    animatedSprite:SetAnimation(cache:GetResource("AnimationSet2D", "Urho2D/GoldIcon.scml"), "idle") -- Get scml file and Play "idle" anim
    local body = node:CreateComponent("RigidBody2D")
    body.bodyType = BT_STATIC
    local shape = node:CreateComponent("CollisionCircle2D") -- Create circle shape
    shape.radius = 0.32 -- Set radius
    shape.trigger = true
    return node
end

function CreateMovingPlatform()
    local node = scene_:CreateChild("MovingPlatform")
    node.scale = Vector3(3, 1, 0)
    local staticSprite = node:CreateComponent("StaticSprite2D")
    staticSprite.sprite = cache:GetResource("Sprite2D", "Urho2D/Box.png")
    local body = node:CreateComponent("RigidBody2D")
    body.bodyType = BT_STATIC
    local shape = node:CreateComponent("CollisionBox2D") -- Create rectangular shape
    shape.size = Vector2(0.32, 0.32) -- Set box size
    shape.friction = 0.8 -- Set friction
    return node
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
        scene_:SaveXML(fileSystem:GetProgramDir().."Data/Scenes/TileMapOrtho.xml")
    end
    if input:GetKeyPress(KEY_F7) then
        scene_:LoadXML(fileSystem:GetProgramDir().."Data/Scenes/TileMapOrtho.xml")
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
    if drawDebug then
        scene_:GetComponent("PhysicsWorld2D"):DrawDebugGeometry(true)
    end
end

-- Character2D script object class
Character2D = ScriptObject()

function Character2D:Update(timeStep)
    local node = self.node
    local body = node:GetComponent("RigidBody2D")
    local animatedSprite = node:GetComponent("AnimatedSprite2D")

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

    if input:GetKeyPress(KEY_UP) or input:GetKeyDown(KEY_W) then -- Jump
        local jumpForce = 50
        if moveDir:Equals(Vector2.ZERO) then jumpForce = 35 end
        moveDir = moveDir + Vector2(0, jumpForce)
    end

    -- Move
    if not moveDir:Equals(Vector2.ZERO) then
        body:ApplyForceToCenter(moveDir * MOVE_SPEED)
        body:ApplyForceToCenter(body.linearVelocity * -10) -- Limit max speed and facilitate return to rest
    end

    -- Animate
    if input:GetKeyDown(KEY_SPACE) then
        if animatedSprite.animation ~= "attack" then
            animatedSprite:SetAnimation("attack", LM_FORCE_LOOPED)
            animatedSprite.speed = 1.5
        end
    elseif not moveDir:Equals(Vector2.ZERO) then
        if animatedSprite.animation ~= "run" then
            animatedSprite:SetAnimation("run", LM_FORCE_LOOPED)
        end
    elseif animatedSprite.animation ~= "idle" then
        animatedSprite:SetAnimation("idle", LM_FORCE_LOOPED)
    end
end