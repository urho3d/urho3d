// Urho3D spawn editor

LineEdit@ positionOffsetX;
LineEdit@ positionOffsetY;
LineEdit@ positionOffsetZ;
LineEdit@ randomRotationX;
LineEdit@ randomRotationY;
LineEdit@ randomRotationZ;
LineEdit@ randomScaleMinEdit;
LineEdit@ randomScaleMaxEdit;
LineEdit@ numberSpawnedObjectsEdit;
LineEdit@ spawnRadiusEdit;
LineEdit@ spawnCountEdit;

Window@ spawnWindow;
Vector3 positionOffset = Vector3(0, 0, 0);
Vector3 randomRotation = Vector3(0, 0, 0);
float randomScaleMin = 1;
float randomScaleMax = 1;
uint spawnCount = 1;
float spawnRadius = 0;
bool useNormal = true;
bool alignToAABBBottom = true;
bool spawnOnSelection = false;
uint numberSpawnedObjects = 1;
Array<String> spawnedObjectsNames;

void CreateSpawnEditor()
{
    if (spawnWindow !is null)
        return;

    spawnWindow = LoadEditorUI("UI/EditorSpawnWindow.xml");
    ui.root.AddChild(spawnWindow);
    spawnWindow.opacity = uiMaxOpacity;

    int height = Min(ui.root.height - 60, 500);
    spawnWindow.SetSize(300, height);
    CenterDialog(spawnWindow);

    HideSpawnEditor();
    SubscribeToEvent(spawnWindow.GetChild("CloseButton", true), "Released", "HideSpawnEditor");
    positionOffsetX = spawnWindow.GetChild("PositionOffset.x", true);
    positionOffsetY = spawnWindow.GetChild("PositionOffset.y", true);
    positionOffsetZ = spawnWindow.GetChild("PositionOffset.z", true);
    positionOffsetX.text = String(positionOffset.x);
    positionOffsetY.text = String(positionOffset.y);
    positionOffsetZ.text = String(positionOffset.z);
    randomRotationX = spawnWindow.GetChild("RandomRotation.x", true);
    randomRotationY = spawnWindow.GetChild("RandomRotation.y", true);
    randomRotationZ = spawnWindow.GetChild("RandomRotation.z", true);
    randomRotationX.text = String(randomRotation.x);
    randomRotationY.text = String(randomRotation.y);
    randomRotationZ.text = String(randomRotation.z);
    
    randomScaleMinEdit = spawnWindow.GetChild("RandomScaleMin", true);
    randomScaleMaxEdit = spawnWindow.GetChild("RandomScaleMax", true);
    randomScaleMinEdit.text = String(randomScaleMin);
    randomScaleMaxEdit.text = String(randomScaleMax);
    CheckBox@ useNormalToggle = spawnWindow.GetChild("UseNormal", true);
    useNormalToggle.checked = useNormal;
    CheckBox@ alignToAABBBottomToggle = spawnWindow.GetChild("AlignToAABBBottom", true);
    alignToAABBBottomToggle.checked = alignToAABBBottom;
    CheckBox@ spawnOnSelectionToggle = spawnWindow.GetChild("SpawnOnSelected", true);
    spawnOnSelectionToggle.checked = spawnOnSelection;    

    numberSpawnedObjectsEdit = spawnWindow.GetChild("NumberSpawnedObjects", true);
    numberSpawnedObjectsEdit.text = String(numberSpawnedObjects);

    spawnRadiusEdit = spawnWindow.GetChild("SpawnRadius", true);
    spawnCountEdit = spawnWindow.GetChild("SpawnCount", true);
    spawnRadiusEdit.text = String(spawnRadius);
    spawnCountEdit.text = String(spawnCount);

    SubscribeToEvent(positionOffsetX, "TextChanged", "EditPositionOffset");
    SubscribeToEvent(positionOffsetY, "TextChanged", "EditPositionOffset");
    SubscribeToEvent(positionOffsetZ, "TextChanged", "EditPositionOffset");
    SubscribeToEvent(randomRotationX, "TextChanged", "EditRandomRotation");
    SubscribeToEvent(randomRotationY, "TextChanged", "EditRandomRotation");
    SubscribeToEvent(randomRotationZ, "TextChanged", "EditRandomRotation");
    SubscribeToEvent(randomScaleMinEdit, "TextChanged", "EditRandomScale");
    SubscribeToEvent(randomScaleMaxEdit, "TextChanged", "EditRandomScale");
    SubscribeToEvent(spawnRadiusEdit, "TextChanged", "EditSpawnRadius");
    SubscribeToEvent(spawnCountEdit, "TextChanged", "EditSpawnCount");
    SubscribeToEvent(useNormalToggle, "Toggled", "ToggleUseNormal");
    SubscribeToEvent(alignToAABBBottomToggle, "Toggled", "ToggleAlignToAABBBottom");
    SubscribeToEvent(spawnOnSelectionToggle, "Toggled", "ToggleSpawnOnSelected");
    SubscribeToEvent(numberSpawnedObjectsEdit, "TextFinished", "UpdateNumberSpawnedObjects");
    SubscribeToEvent(spawnWindow.GetChild("SetSpawnMode", true), "Released", "SetSpawnMode");
    RefreshPickedObjects();
}

bool ToggleSpawnEditor()
{
    if (spawnWindow.visible == false)
        ShowSpawnEditor();
    else
        HideSpawnEditor();
    return true;
}

void ShowSpawnEditor()
{
    spawnWindow.visible = true;
    spawnWindow.BringToFront();
}

void HideSpawnEditor()
{
    spawnWindow.visible = false;
}

void PickSpawnObject()
{
    @resourcePicker = GetResourcePicker(StringHash("Node"));
    if (resourcePicker is null)
        return;

    String lastPath = resourcePicker.lastPath;
    if (lastPath.empty)
        lastPath = sceneResourcePath;
    CreateFileSelector(localization.Get("Pick ") + resourcePicker.typeName, "OK", "Cancel", lastPath, resourcePicker.filters, resourcePicker.lastFilter, false);
    SubscribeToEvent(uiFileSelector, "FileSelected", "PickSpawnObjectDone");
}

void EditPositionOffset(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    positionOffset = Vector3(positionOffsetX.text.ToFloat(), positionOffsetY.text.ToFloat(), positionOffsetZ.text.ToFloat());
    UpdateHierarchyItem(editorScene);
}

void EditRandomRotation(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    randomRotation = Vector3(randomRotationX.text.ToFloat(), randomRotationY.text.ToFloat(), randomRotationZ.text.ToFloat());
    UpdateHierarchyItem(editorScene);
}

void EditRandomScale(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    randomScaleMin = randomScaleMinEdit.text.ToFloat();
    randomScaleMax = randomScaleMaxEdit.text.ToFloat();
    UpdateHierarchyItem(editorScene);
}

void ToggleUseNormal(StringHash eventType, VariantMap& eventData)
{
    useNormal = cast<CheckBox>(eventData["Element"].GetPtr()).checked;
}

void ToggleAlignToAABBBottom(StringHash eventType, VariantMap& eventData)
{
    alignToAABBBottom = cast<CheckBox>(eventData["Element"].GetPtr()).checked;
}

void ToggleSpawnOnSelected(StringHash eventType, VariantMap& eventData)
{
    spawnOnSelection = cast<CheckBox>(eventData["Element"].GetPtr()).checked;
}

void UpdateNumberSpawnedObjects(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    numberSpawnedObjects = edit.text.ToUInt();
    edit.text = String(numberSpawnedObjects);
    RefreshPickedObjects();
}

void EditSpawnRadius(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    spawnRadius = edit.text.ToFloat();
}

void EditSpawnCount(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    spawnCount = edit.text.ToUInt();
}

void RefreshPickedObjects()
{
    spawnedObjectsNames.Resize(numberSpawnedObjects);
    ListView@ list = spawnWindow.GetChild("SpawnedObjects", true);
    list.RemoveAllItems();

    for (uint i = 0; i < numberSpawnedObjects; ++i)
    {
        UIElement@ parent = CreateAttributeEditorParentWithSeparatedLabel(list, "Object " +(i+1), i, 0, false);
        
        UIElement@ container = UIElement();
        container.SetLayout(LM_HORIZONTAL, 4, IntRect(10, 0, 4, 0));
        container.SetFixedHeight(ATTR_HEIGHT);
        parent.AddChild(container);

        LineEdit@ nameEdit = CreateAttributeLineEdit(container, null, i, 0);
        nameEdit.name = "TextureNameEdit" + String(i);

        Button@ pickButton = CreateResourcePickerButton(container, null, i, 0, "smallButtonPick");
        SubscribeToEvent(pickButton, "Released", "PickSpawnedObject");
        nameEdit.text = spawnedObjectsNames[i];

        SubscribeToEvent(nameEdit, "TextFinished", "EditSpawnedObjectName");
    }
}

void EditSpawnedObjectName(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ nameEdit = eventData["Element"].GetPtr();
    int index = nameEdit.vars["Index"].GetUInt();
    String resourceName = VerifySpawnedObjectFile(nameEdit.text);
    nameEdit.text = resourceName;
    spawnedObjectsNames[index] = resourceName;
}

String VerifySpawnedObjectFile(const String&in resourceName)
{
    File@ file = cache.GetFile(resourceName);
    if(file !is null)
        return resourceName;
    else
        return String();
}

void PickSpawnedObject(StringHash eventType, VariantMap& eventData)
{
    UIElement@ button = eventData["Element"].GetPtr();
    resourcePickIndex = button.vars["Index"].GetUInt();
    CreateFileSelector("Pick spawned object", "Pick", "Cancel", uiNodePath, uiSceneFilters, uiNodeFilter);
    
    SubscribeToEvent(uiFileSelector, "FileSelected", "PickSpawnedObjectNameDone");
}

void PickSpawnedObjectNameDone(StringHash eventType, VariantMap& eventData)
{
    StoreResourcePickerPath();
    CloseFileSelector();

    if (!eventData["OK"].GetBool())
    {
        @resourcePicker = null;
        return;
    }

    String resourceName = GetResourceNameFromFullName(eventData["FileName"].GetString());
    spawnedObjectsNames[resourcePickIndex] = VerifySpawnedObjectFile(resourceName);
    @resourcePicker = null;
    RefreshPickedObjects();
}

void SetSpawnMode(StringHash eventType, VariantMap& eventData)
{
    editMode = EDIT_SPAWN;
}

void PlaceObject(Vector3 spawnPosition, Vector3 normal)
{
    Quaternion spawnRotation;
    if (useNormal)
        spawnRotation = Quaternion(Vector3(0, 1, 0), normal);
    spawnRotation = Quaternion(Random(-randomRotation.x, randomRotation.x),
        Random(-randomRotation.y, randomRotation.y), Random(-randomRotation.z, randomRotation.z)) * spawnRotation;

    int number = RandomInt(0, spawnedObjectsNames.length);
    File@ file = cache.GetFile(spawnedObjectsNames[number]);
    Node@ spawnedObject = InstantiateNodeFromFile(file, spawnPosition + (spawnRotation * positionOffset), spawnRotation, Random(randomScaleMin, randomScaleMax));
    if (spawnedObject is null)
    {
        spawnedObjectsNames[number] = spawnedObjectsNames[spawnedObjectsNames.length - 1];
        --numberSpawnedObjects;
        RefreshPickedObjects();
        return;
    }
}

bool GetSpawnPosition(const Ray&in cameraRay, float maxDistance, Vector3&out position, Vector3&out normal, float randomRadius = 0.0,
    bool allowNoHit = true)
{
    if (pickMode < PICK_RIGIDBODIES && editorScene.octree !is null)
    {
        RayQueryResult result = editorScene.octree.RaycastSingle(cameraRay, RAY_TRIANGLE, maxDistance, DRAWABLE_GEOMETRY,
            0x7fffffff);
        if (result.drawable !is null)
        {
            if (randomRadius > 0)
            {
                Vector3 basePosition = RandomizeSpawnPosition(result.position, randomRadius);
                basePosition.y += randomRadius;
                result = editorScene.octree.RaycastSingle(Ray(basePosition, Vector3(0, -1, 0)), RAY_TRIANGLE, randomRadius * 2.0,
                    DRAWABLE_GEOMETRY, 0x7fffffff);
                if (result.drawable !is null)
                {
                    position = result.position;
                    normal = result.normal;
                    return true;
                }
            }
            else
            {
                position = result.position;
                normal = result.normal;
                return true;
            }
        }
    }
    else if (editorScene.physicsWorld !is null)
    {
        // If we are not running the actual physics update, refresh collisions before raycasting
        if (!runUpdate)
            editorScene.physicsWorld.UpdateCollisions();

        PhysicsRaycastResult result = editorScene.physicsWorld.RaycastSingle(cameraRay, maxDistance);

        if (result.body !is null)
        {
            if (randomRadius > 0)
            {
                Vector3 basePosition = RandomizeSpawnPosition(result.position, randomRadius);
                basePosition.y += randomRadius;
                result = editorScene.physicsWorld.RaycastSingle(Ray(basePosition, Vector3(0, -1, 0)), randomRadius * 2.0);
                if (result.body !is null)
                {
                    position = result.position;
                    normal = result.normal;
                    return true;
                }
            }
            else
            {
                position = result.position;
                normal = result.normal;
                return true;
            }
        }
    }

    position = cameraRay.origin + cameraRay.direction * maxDistance;
    normal = Vector3(0, 1, 0);
    return allowNoHit;
}

bool GetSpawnPositionOnNode(const Ray&in cameraRay, float maxDistance, Vector3&out position, Vector3&out normal, Node@ node, float randomRadius = 0.0,
    bool allowNoHit = true)
{
    if (pickMode < PICK_RIGIDBODIES && editorScene.octree !is null)
    {
        Array<RayQueryResult> results = editorScene.octree.Raycast(cameraRay, RAY_TRIANGLE, maxDistance, DRAWABLE_GEOMETRY, 0x7fffffff);
        
        if (!results.empty)
        {
            RayQueryResult result = results[0];

            for(uint i = 0; i < results.length; i++)
            {
                if (results[i].node is node)
                {
                    result = results[i];
                    break;
                }
            }

            if (randomRadius > 0)
            {
                Vector3 basePosition = RandomizeSpawnPosition(result.position, randomRadius);
                basePosition.y += randomRadius;
                Array<RayQueryResult> randomResults = editorScene.octree.Raycast(Ray(basePosition, Vector3(0, -1, 0)), RAY_TRIANGLE, randomRadius * 2.0, DRAWABLE_GEOMETRY, 0x7fffffff);

                if (randomResults.length == 0)
                {
                    position = result.position;
                    normal = result.normal;
                    return true;
                }

                result = randomResults[0];

                // Find node in results
                for(uint i = 0; i < randomResults.length; i++)
                {
                    if (randomResults[i].node is node)
                    {
                        result = randomResults[i];
                        break;
                    }
                }

                position = result.position;
                normal = result.normal;
                return true;
            }
            else
            {
                position = result.position;
                normal = result.normal;
                return true;
            }
        }
    }

    position = cameraRay.origin + cameraRay.direction * maxDistance;
    normal = Vector3(0, 1, 0);
    return allowNoHit;
}

Vector3 RandomizeSpawnPosition(const Vector3&in position, float randomRadius)
{
    float angle = Random() * 360.0;
    float distance = Random() * randomRadius;
    return position + Quaternion(0, angle, 0) * Vector3(0, 0, distance);
}

void SpawnObject()
{
    Node@ selectedNode = null;
    
    if (spawnOnSelection)
    if (selectedNodes.length > 0)
        selectedNode = selectedNodes[0];
        
    if (spawnedObjectsNames.length == 0)
        return;
        
    IntRect view = activeViewport.viewport.rect;
    
    for (uint i = 0; i < spawnCount; ++i)
    {
        Ray cameraRay = GetActiveViewportCameraRay();
        Vector3 position, normal;
        bool result = false;
        
        if (spawnOnSelection && selectedNode != null)
            result = GetSpawnPositionOnNode(cameraRay, camera.farClip, position, normal, selectedNode, spawnRadius, false);
        else
            result = GetSpawnPosition(cameraRay, camera.farClip, position, normal, spawnRadius, false);        
        
        if (result)
            PlaceObject(position, normal);
    }
}
