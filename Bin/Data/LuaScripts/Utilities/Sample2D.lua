-- Convenient functions for Urho2D samples:
--    - Generate collision shapes from a tmx file objects
--    - Create Spriter Imp character
--    - Handle camera zoom using PageUp, PageDown and MouseWheel
--    - Create UI instructions
--    - Set global variables
--    - Set XML patch instructions for screen joystick

CAMERA_MIN_DIST = 0.1
CAMERA_MAX_DIST = 6

MOVE_SPEED = 23 -- Movement speed as world units per second
MOVE_SPEED_X = 1.5 -- Movement speed for isometric maps
MOVE_SPEED_SCALE = 1 -- Scaling factor based on tiles' aspect ratio

character2DNode = nil
zoom = 2 -- Speed is scaled according to zoom


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

function CreateCharacter(info, createObject, friction, position)
    character2DNode = scene_:CreateChild("Imp")
    character2DNode.position = position
    character2DNode:SetScale(0.2)
    local animatedSprite = character2DNode:CreateComponent("AnimatedSprite2D")
    animatedSprite:SetAnimation(cache:GetResource("AnimationSet2D", "Urho2D/imp/imp.scml"), "idle") -- Get scml file and Play "idle" anim
    animatedSprite:SetLayer(1) -- Put character over tile map
    local body = character2DNode:CreateComponent("RigidBody2D")
    body.bodyType = BT_DYNAMIC
    body.allowSleep = false
    local shape = character2DNode:CreateComponent("CollisionCircle2D")
    shape.radius = 1.2 -- Set shape size
    shape.friction = friction -- Set friction
    shape.restitution = 0.1 -- Bounce
    if createObject then
        character2DNode:CreateScriptObject("Character2D") -- Create a ScriptObject to handle character behavior
    end

    -- Scale character's speed on the Y axis according to tiles' aspect ratio
    MOVE_SPEED_SCALE = info.tileHeight / info.tileWidth
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

function CreateInstructions(text)
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText.text = text
    instructionText:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15)
    instructionText.textAlignment = HA_CENTER -- Center rows in relation to each other

    -- Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER
    instructionText.verticalAlignment = VA_CENTER
    instructionText:SetPosition(0, ui.root.height / 4)
end

function CreatePathFromPoints(object)
    local path = {}
    for i=0, object.numPoints -1 do
        table.insert(path, object:GetPoint(i))
    end
    return path
end

-- Mover script object class
Mover = ScriptObject()

function Mover:Start()
    self.speed = 0.5
    self.path = {}
    self.currentPathID = 2
end

function Mover:Update(timeStep)
    local node = self.node

    -- Set direction and move to target
    local dir = self.path[self.currentPathID] - node.position2D
    node:Translate(dir:Normalized() * Abs(self.speed) * timeStep)

    -- Check for new target to reach
    if Abs(dir:Length()) < 0.1 then
        if self.speed > 0 then
            if self.currentPathID + 1 <= table.maxn(self.path) then
                self.currentPathID = self.currentPathID + 1
            else
                self.currentPathID = self.currentPathID - 1
                self.speed = -self.speed
            end
        else
            if self.currentPathID - 1 > 0 then
                self.currentPathID = self.currentPathID - 1
            else
                self.currentPathID = 2
                self.speed = -self.speed
            end
        end
    end
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "   <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" ..
        "   <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Zoom In</replace>" ..
        "   <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" ..
        "       <element type=\"Text\">" ..
        "           <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "           <attribute name=\"Text\" value=\"PAGEUP\" />" ..
        "       </element>" ..
        "   </add>" ..
        "   <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" ..
        "   <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Zoom Out</replace>" ..
        "   <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" ..
        "       <element type=\"Text\">" ..
        "           <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "           <attribute name=\"Text\" value=\"PAGEDOWN\" />" ..
        "       </element>" ..
        "   </add>" ..
        "</patch>"
end