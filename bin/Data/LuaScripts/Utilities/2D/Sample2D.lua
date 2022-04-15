-- Convenient functions for Urho2D and Physics2D samples:
--    - Generate collision shapes from a tmx file objects
--    - Create Spriter Imp character
--    - Load Mover script object class from file
--    - Create enemies, coins and platforms to tile map placeholders
--    - Handle camera zoom using PageUp, PageDown and MouseWheel
--    - Create UI interface
--    - Create a particle emitter attached to a given node
--    - Play a non-looping sound effect
--    - Create a background sprite
--    - Set global variables
--    - Set XML patch instructions for screen joystick

CAMERA_MIN_DIST = 0.1
CAMERA_MAX_DIST = 6

MOVE_SPEED = 23 -- Movement speed as world units per second
MOVE_SPEED_X = 2.5 -- Movement speed for isometric maps
MOVE_SPEED_SCALE = 1 -- Scaling factor based on tiles' aspect ratio

LIFES = 3
zoom = 2 -- Speed is scaled according to zoom
demoFilename = ""
character2DNode = nil


function CreateCollisionShapesFromTMXObjects(tileMapNode, tileMapLayer, info)
    -- Create rigid body to the root node
    local body = tileMapNode:CreateComponent("RigidBody2D")
    body.bodyType = BT_STATIC

    -- Generate physics collision shapes from the tmx file's objects located in "Physics" layer
    for i=0, tileMapLayer:GetNumObjects() -1 do
        local tileMapObject = tileMapLayer:GetObject(i) -- Get physics objects (TileMapObject2D)
        local objectType = tileMapObject.objectType

        -- Create collision shape from tmx object
        local shape

        if objectType == OT_RECTANGLE then
            shape = tileMapNode:CreateComponent("CollisionBox2D")
            local size = tileMapObject.size
            shape.size = size
            if info.orientation == O_ORTHOGONAL then
                shape.center = tileMapObject.position + size / 2
            else
                shape.center = tileMapObject.position + Vector2(info.tileWidth / 2, 0)
                shape.angle = 45 -- If our tile map is isometric then shape is losange
            end

        elseif objectType == OT_ELLIPSE then
            shape = tileMapNode:CreateComponent("CollisionCircle2D") -- Ellipse is built as a circle shape as there's no equivalent in Box2D
            local size = tileMapObject.size
            shape.radius = size.x / 2
            if info.orientation == O_ORTHOGONAL then
                shape.center = tileMapObject.position + size / 2
            else
                shape.center = tileMapObject.position + Vector2(info.tileWidth / 2, 0)
            end

        elseif objectType == OT_POLYGON then
            shape = tileMapNode:CreateComponent("CollisionPolygon2D")

        elseif objectType == OT_POLYLINE then
            shape = tileMapNode:CreateComponent("CollisionChain2D")

        else break
        end

        if objectType == OT_POLYGON or objectType == OT_POLYLINE then -- Build shape from vertices
            local numVertices = tileMapObject.numPoints
            shape.vertexCount = numVertices
            for i=0, numVertices - 1 do
                shape:SetVertex(i, tileMapObject:GetPoint(i))
            end
        end

        shape.friction = 0.8
        if tileMapObject:HasProperty("Friction") then
            shape.friction = ToFloat(tileMapObject:GetProperty("Friction"))
        end
    end
end

function CreateCharacter(info, createObject, friction, position, scale)
    character2DNode = scene_:CreateChild("Imp")
    character2DNode.position = position
    character2DNode:SetScale(scale)
    local animatedSprite = character2DNode:CreateComponent("AnimatedSprite2D")
    local animationSet = cache:GetResource("AnimationSet2D", "Urho2D/imp/imp.scml")
    animatedSprite.animationSet = animationSet
    animatedSprite.animation = "idle"
    animatedSprite:SetLayer(3) -- Put character over tile map (which is on layer 0) and over Orcs (which are on layer 1)
-- 
    local body = character2DNode:CreateComponent("RigidBody2D")
    body.bodyType = BT_DYNAMIC
    body.allowSleep = false

    local shape = character2DNode:CreateComponent("CollisionCircle2D")
    shape.radius = 1.1 -- Set shape size
    shape.friction = friction -- Set friction
    shape.restitution = 0.1 -- Slight bounce
    if createObject then
        character2DNode:CreateScriptObject("Character2D") -- Create a ScriptObject to handle character behavior
    end

    -- Scale character's speed on the Y axis according to tiles' aspect ratio (for isometric only)
    MOVE_SPEED_SCALE = info.tileHeight / info.tileWidth
end

function CreateTrigger()
    local node = scene_:CreateChild("Trigger") -- Clones will be renamed according to object type
    local body = node:CreateComponent("RigidBody2D")
    body.bodyType = BT_STATIC
    local shape = node:CreateComponent("CollisionBox2D") -- Create box shape
    shape.trigger = true
    return node
end

function CreateEnemy()
    local node = scene_:CreateChild("Enemy")
    local staticSprite = node:CreateComponent("StaticSprite2D")
    staticSprite.sprite = cache:GetResource("Sprite2D", "Urho2D/Aster.png")
    local body = node:CreateComponent("RigidBody2D")
    body.bodyType = BT_STATIC
    local shape = node:CreateComponent("CollisionCircle2D") -- Create circle shape
    shape.radius = 0.25 -- Set radius
    return node
end

function CreateOrc()
    local node = scene_:CreateChild("Orc")
    node.scale = character2DNode.scale -- Use same scale as player character
    local animatedSprite = node:CreateComponent("AnimatedSprite2D")
    -- Get scml file and Play "run" anim
    local animationSet = cache:GetResource("AnimationSet2D", "Urho2D/Orc/Orc.scml")
    animatedSprite.animationSet = animationSet
    animatedSprite.animation = "run"
    animatedSprite:SetLayer(2) -- Make orc always visible
    local body = node:CreateComponent("RigidBody2D")
    local shape = node:CreateComponent("CollisionCircle2D") -- Create circle shape
    shape.radius = 1.3 -- Set shape size
    shape.trigger = true
    return node
end

function CreateCoin()
    local node = scene_:CreateChild("Coin")
    node:SetScale(0.5)
    local animatedSprite = node:CreateComponent("AnimatedSprite2D")
    -- Get scml file and Play "idle" anim
    local animationSet = cache:GetResource("AnimationSet2D", "Urho2D/GoldIcon.scml")
    animatedSprite.animationSet = animationSet
    animatedSprite.animation = "idle"
    animatedSprite:SetLayer(2)
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
    local shape = node:CreateComponent("CollisionBox2D") -- Create box shape
    shape.size = Vector2(0.32, 0.32) -- Set box size
    shape.friction = 0.8 -- Set friction
    return node
end

function PopulateMovingEntities(movingEntitiesLayer)
    -- Create enemy, Orc and moving platform nodes (will be cloned at each placeholder)
    local enemyNode = CreateEnemy()
    local orcNode = CreateOrc()
    local platformNode = CreateMovingPlatform()

    -- Instantiate enemies and moving platforms at each placeholder (placeholders are Poly Line objects defining a path from points)
    for i=0, movingEntitiesLayer:GetNumObjects() -1 do
        -- Get placeholder object (TileMapObject2D)
        local movingObject = movingEntitiesLayer:GetObject(i)
        if movingObject.objectType == OT_POLYLINE then
            -- Clone the moving entity node and position it at placeholder point
            local movingClone = nil
            local offset = Vector2.ZERO
            if movingObject.type == "Enemy" then
                movingClone = enemyNode:Clone()
                offset = Vector2(0, -0.32)
            elseif movingObject.type == "Orc" then
                movingClone = orcNode:Clone()
            elseif movingObject.type == "MovingPlatform" then
                movingClone = platformNode:Clone()
            else
                break
            end
            movingClone.position2D = movingObject:GetPoint(0) + offset

            -- Create script object that handles entity translation along its path (load from file)
            local mover = movingClone:CreateScriptObject("LuaScripts/Utilities/2D/Mover.lua", "Mover")

            -- Set path from points
            mover.path = CreatePathFromPoints(movingObject, offset)

            -- Override default speed
            if movingObject:HasProperty("Speed") then
                mover.speed = movingObject:GetProperty("Speed")
            end
        end
    end

    -- Remove nodes used for cloning purpose
    enemyNode:Remove()
    orcNode:Remove()
    platformNode:Remove()
end

function PopulateCoins(coinsLayer)
    -- Create coin (will be cloned at each placeholder)
    local coinNode = CreateCoin()

    -- Instantiate coins to pick at each placeholder
    for i=0, coinsLayer:GetNumObjects() -1 do
        local coinObject = coinsLayer:GetObject(i) -- Get placeholder object (TileMapObject2D)
        local coinClone = coinNode:Clone()
        coinClone.position2D = coinObject.position + coinObject.size / 2 + Vector2(0, 0.16)
    end

    -- Init coins counters
    local character = character2DNode:GetScriptObject()
    character.remainingCoins = coinsLayer.numObjects
    character.maxCoins = coinsLayer.numObjects

    -- Remove node used for cloning purpose
    coinNode:Remove()
end

function PopulateTriggers(triggersLayer)
    -- Create trigger node (will be cloned at each placeholder)
    local triggerNode = CreateTrigger()

    -- Instantiate triggers at each placeholder (Rectangle objects)
    for i=0, triggersLayer:GetNumObjects() -1 do
        local triggerObject = triggersLayer:GetObject(i) -- Get placeholder object (TileMapObject2D)
        if triggerObject.objectType == OT_RECTANGLE then
            local triggerClone = triggerNode:Clone()
            triggerClone.name = triggerObject.type
            triggerClone:GetComponent("CollisionBox2D").size = triggerObject.size
            triggerClone.position2D = triggerObject.position + triggerObject.size / 2
        end
    end
end

function Zoom(camera)
    if input.mouseMoveWheel then
        zoom = Clamp(camera.zoom + input.mouseMoveWheel * 0.1, CAMERA_MIN_DIST, CAMERA_MAX_DIST)
        camera.zoom = zoom
    end

    if input:GetKeyDown(KEY_PAGEUP) then
        zoom = Clamp(camera.zoom * 1.01, CAMERA_MIN_DIST, CAMERA_MAX_DIST)
        camera.zoom = zoom
    end

    if input:GetKeyDown(KEY_PAGEDOWN) then
        zoom = Clamp(camera.zoom * 0.99, CAMERA_MIN_DIST, CAMERA_MAX_DIST)
        camera.zoom = zoom
    end
end

function CreatePathFromPoints(object, offset)
    local path = {}
    for i=0, object.numPoints -1 do
        table.insert(path, object:GetPoint(i) + offset)
    end
    return path
end

function CreateUIContent(demoTitle)
    -- Set the default UI style and font
    ui.root.defaultStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")
    local font = cache:GetResource("Font", "Fonts/Anonymous Pro.ttf")

    -- We create in-game UIs (coins and lifes) first so that they are hidden by the fullscreen UI (we could also temporary hide them using SetVisible)

    -- Create the UI for displaying the remaining coins
    local coinsUI = ui.root:CreateChild("BorderImage", "Coins")
    coinsUI.texture = cache:GetResource("Texture2D", "Urho2D/GoldIcon.png")
    coinsUI:SetSize(50, 50)
    coinsUI.imageRect = IntRect(0, 64, 60, 128)
    coinsUI:SetAlignment(HA_LEFT, VA_TOP)
    coinsUI:SetPosition(5, 5)
    local coinsText = coinsUI:CreateChild("Text", "CoinsText")
    coinsText:SetAlignment(HA_CENTER, VA_CENTER)
    coinsText:SetFont(font, 24)
    coinsText.textEffect = TE_SHADOW
    coinsText.text = character2DNode:GetScriptObject().remainingCoins

    -- Create the UI for displaying the remaining lifes
    local lifeUI = ui.root:CreateChild("BorderImage", "Life")
    lifeUI.texture = cache:GetResource("Texture2D", "Urho2D/imp/imp_all.png")
    lifeUI:SetSize(70, 80)
    lifeUI:SetAlignment(HA_RIGHT, VA_TOP)
    lifeUI:SetPosition(-5, 5)
    local lifeText = lifeUI:CreateChild("Text", "LifeText")
    lifeText:SetAlignment(HA_CENTER, VA_CENTER)
    lifeText:SetFont(font, 24)
    lifeText.textEffect = TE_SHADOW
    lifeText.text = LIFES

    -- Create the fullscreen UI for start/end
    local fullUI = ui.root:CreateChild("Window", "FullUI")
    fullUI:SetStyleAuto()
    fullUI:SetSize(ui.root.width, ui.root.height)
    fullUI.enabled = false -- Do not react to input, only the 'Exit' and 'Play' buttons will

    -- Create the title
    local title = fullUI:CreateChild("BorderImage", "Title")
    title:SetMinSize(fullUI.width, 50)
    title.texture = cache:GetResource("Texture2D", "Textures/HeightMap.png")
    title:SetFullImageRect()
    title:SetAlignment(HA_CENTER, VA_TOP)
    local titleText = title:CreateChild("Text", "TitleText")
    titleText:SetAlignment(HA_CENTER, VA_CENTER)
    titleText:SetFont(font, 24)
    titleText.text = demoTitle

    -- Create the image
    local spriteUI = fullUI:CreateChild("BorderImage", "Sprite")
    spriteUI.texture = cache:GetResource("Texture2D", "Urho2D/imp/imp_all.png")
    spriteUI:SetSize(238, 271)
    spriteUI:SetAlignment(HA_CENTER, VA_CENTER)
    spriteUI:SetPosition(0, - ui.root.height / 4)

    -- Create the 'EXIT' button
    local exitButton = ui.root:CreateChild("Button", "ExitButton")
    exitButton:SetStyleAuto()
    exitButton.focusMode = FM_RESETFOCUS
    exitButton:SetSize(100, 50)
    exitButton:SetAlignment(HA_CENTER, VA_CENTER)
    exitButton:SetPosition(-100, 0)
    local exitText = exitButton:CreateChild("Text", "ExitText")
    exitText:SetAlignment(HA_CENTER, VA_CENTER)
    exitText:SetFont(font, 24)
    exitText.text = "EXIT"
    SubscribeToEvent(exitButton, "Released", "HandleExitButton")

    -- Create the 'PLAY' button
    local playButton = ui.root:CreateChild("Button", "PlayButton")
    playButton:SetStyleAuto()
    playButton.focusMode = FM_RESETFOCUS
    playButton:SetSize(100, 50)
    playButton:SetAlignment(HA_CENTER, VA_CENTER)
    playButton:SetPosition(100, 0)
    local playText = playButton:CreateChild("Text", "PlayText")
    playText:SetAlignment(HA_CENTER, VA_CENTER)
    playText:SetFont(font, 24)
    playText.text = "PLAY"
    SubscribeToEvent(playButton, "Released", "HandlePlayButton")

    -- Create the instructions
    local instructionText = ui.root:CreateChild("Text", "Instructions")
    instructionText:SetFont(font, 15)
    instructionText.textAlignment = HA_CENTER -- Center rows in relation to each other
    instructionText.text = "Use WASD keys or Arrows to move\nPageUp/PageDown/MouseWheel to zoom\nF5/F7 to save/reload scene\n'Z' to toggle debug geometry\nSpace to fight"
    instructionText:SetAlignment(HA_CENTER, VA_CENTER)
    instructionText:SetPosition(0, ui.root.height / 4)

    -- Show mouse cursor
    input.mouseVisible = true
end

function HandleExitButton()
    engine:Exit()
end

function HandlePlayButton()
    -- Remove fullscreen UI and unfreeze the scene
    if ui.root:GetChild("FullUI", true) then
        ui.root:GetChild("FullUI", true):Remove()
        scene_.updateEnabled = true
    else
        -- Reload the scene
        ReloadScene(true)
    end

    -- Hide Instructions and Play/Exit buttons
    ui.root:GetChild("Instructions", true).text = ""
    ui.root:GetChild("ExitButton", true).visible = false
    ui.root:GetChild("PlayButton", true).visible = false

    -- Hide mouse cursor
    input.mouseVisible = false
end

function SaveScene(initial)
    local filename = demoFilename
    if not initial then
        filename = demoFilename .. "InGame"
    end

    scene_:SaveXML(fileSystem:GetProgramDir() .. "Data/Scenes/" .. filename .. ".xml")
end

function ReloadScene(reInit)
    local filename = demoFilename
    if not reInit then
        filename = demoFilename .. "InGame"
    end

    scene_:LoadXML(fileSystem:GetProgramDir().."Data/Scenes/" .. filename .. ".xml")
    -- After loading we have to reacquire the character scene node, as it has been recreated
    -- Simply find by name as there's only one of them
    character2DNode = scene_:GetChild("Imp", true)
    if character2DNode == nil then
        return
    end

    -- Set what value to use depending whether reload is requested from 'PLAY' button (reInit=true) or 'F7' key (reInit=false)
    local character = character2DNode:GetScriptObject()
    local lifes = character.remainingLifes
    local coins =character.remainingCoins
    if reInit then
        lifes = LIFES
        coins = character.maxCoins
    end

    -- Update lifes UI and value
    local lifeText = ui.root:GetChild("LifeText", true)
    lifeText.text = lifes
    character.remainingLifes = lifes

    -- Update coins UI and value
    local coinsText = ui.root:GetChild("CoinsText", true)
    coinsText.text = coins
    character.remainingCoins = coins
end

function SpawnEffect(node)
    local particleNode = node:CreateChild("Emitter")
    particleNode:SetScale(0.5 / node.scale.x)
    local particleEmitter = particleNode:CreateComponent("ParticleEmitter2D")
    particleEmitter.effect = cache:GetResource("ParticleEffect2D", "Urho2D/sun.pex")
    particleEmitter.layer = 2
end

function PlaySound(soundName)
    local soundNode = scene_:CreateChild("Sound")
    local source = soundNode:CreateComponent("SoundSource")
    source:Play(cache:GetResource("Sound", "Sounds/" .. soundName))
end

function CreateBackgroundSprite(info, scale, texture, animate)
    local node = scene_:CreateChild("Background")
    node.position = Vector3(info.mapWidth, info.mapHeight, 0) / 2
    node:SetScale(scale)
    local sprite = node:CreateComponent("StaticSprite2D")
    sprite.sprite = cache:GetResource("Sprite2D", texture)
    SetRandomSeed(time:GetSystemTime()) -- Randomize from system clock
    sprite.color = Color(Random(0, 1), Random(0, 1), Random(0, 1), 1)
    sprite.layer = -99

    -- Create rotation animation
    if animate then
        local animation = ValueAnimation:new()
        animation:SetKeyFrame(0, Variant(Quaternion(0, 0, 0)))
        animation:SetKeyFrame(1, Variant(Quaternion(0, 0, 180)))
        animation:SetKeyFrame(2, Variant(Quaternion(0, 0, 0)))
        node:SetAttributeAnimation("Rotation", animation, WM_LOOP, 0.05)
    end
end


-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "   <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" ..
        "   <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Fight</replace>" ..
        "   <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" ..
        "       <element type=\"Text\">" ..
        "           <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "           <attribute name=\"Text\" value=\"SPACE\" />" ..
        "       </element>" ..
        "   </add>" ..
        "   <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" ..
        "   <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Jump</replace>" ..
        "   <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" ..
        "       <element type=\"Text\">" ..
        "           <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "           <attribute name=\"Text\" value=\"UP\" />" ..
        "       </element>" ..
        "   </add>" ..
        "</patch>"
end
