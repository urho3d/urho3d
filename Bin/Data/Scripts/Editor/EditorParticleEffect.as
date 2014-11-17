// Urho3D material editor

Window@ particleEffectWindow;
ParticleEffect@ editParticleEffect;
XMLFile@ oldParticleEffectState;
bool inParticleEffectRefresh = true;
View3D@ particleEffectPreview;
Scene@ particlePreviewScene;
Node@ particleEffectPreviewNode;
Node@ particlePreviewCameraNode;
Node@ particlePreviewLightNode;
Light@ particlePreviewLight;
ParticleEmitter@ particleEffectEmitter;

void CreateParticleEffectEditor()
{
    if (particleEffectWindow !is null)
        return;

    particleEffectWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorParticleEffectWindow.xml"));
    ui.root.AddChild(particleEffectWindow);
    particleEffectWindow.opacity = uiMaxOpacity;

    InitParticleEffectPreview();
    RefreshParticleEffectEditor();

    int height = Min(ui.root.height - 60, 500);
    particleEffectWindow.SetSize(300, height);
    CenterDialog(particleEffectWindow);

    HideParticleEffectEditor();

    SubscribeToEvent(particleEffectWindow.GetChild("NewButton", true), "Released", "NewParticleEffect");
    SubscribeToEvent(particleEffectWindow.GetChild("RevertButton", true), "Released", "RevertParticleEffect");
    SubscribeToEvent(particleEffectWindow.GetChild("SaveButton", true), "Released", "SaveParticleEffect");
    SubscribeToEvent(particleEffectWindow.GetChild("SaveAsButton", true), "Released", "SaveParticleEffectAs");
    SubscribeToEvent(particleEffectWindow.GetChild("CloseButton", true), "Released", "HideParticleEffectEditor");
    SubscribeToEvent(particleEffectWindow.GetChild("ConstantForceX", true), "TextChanged", "EditParticleEffectConstantForce");
    SubscribeToEvent(particleEffectWindow.GetChild("ConstantForceY", true), "TextChanged", "EditParticleEffectConstantForce");
    SubscribeToEvent(particleEffectWindow.GetChild("ConstantForceZ", true), "TextChanged", "EditParticleEffectConstantForce");
    SubscribeToEvent(particleEffectWindow.GetChild("DirectionMinX", true), "TextChanged", "EditParticleEffectDirection");
    SubscribeToEvent(particleEffectWindow.GetChild("DirectionMinY", true), "TextChanged", "EditParticleEffectDirection");
    SubscribeToEvent(particleEffectWindow.GetChild("DirectionMinZ", true), "TextChanged", "EditParticleEffectDirection");
    SubscribeToEvent(particleEffectWindow.GetChild("DirectionMaxX", true), "TextChanged", "EditParticleEffectDirection");
    SubscribeToEvent(particleEffectWindow.GetChild("DirectionMaxY", true), "TextChanged", "EditParticleEffectDirection");
    SubscribeToEvent(particleEffectWindow.GetChild("DirectionMaxZ", true), "TextChanged", "EditParticleEffectDirection");
    SubscribeToEvent(particleEffectWindow.GetChild("DampingForce", true), "TextChanged", "EditParticleEffectDampingForce");
    SubscribeToEvent(particleEffectWindow.GetChild("ActiveTime", true), "TextChanged", "EditParticleEffectActiveTime");
    SubscribeToEvent(particleEffectWindow.GetChild("InactiveTime", true), "TextChanged", "EditParticleEffectInactiveTime");
    SubscribeToEvent(particleEffectWindow.GetChild("ParticleSizeMinX", true), "TextChanged", "EditParticleEffectParticleSize");
    SubscribeToEvent(particleEffectWindow.GetChild("ParticleSizeMinY", true), "TextChanged", "EditParticleEffectParticleSize");
    SubscribeToEvent(particleEffectWindow.GetChild("ParticleSizeMaxX", true), "TextChanged", "EditParticleEffectParticleSize");
    SubscribeToEvent(particleEffectWindow.GetChild("ParticleSizeMaxY", true), "TextChanged", "EditParticleEffectParticleSize");
    SubscribeToEvent(particleEffectWindow.GetChild("TimeToLiveMin", true), "TextChanged", "EditParticleEffectTimeToLive");
    SubscribeToEvent(particleEffectWindow.GetChild("TimeToLiveMax", true), "TextChanged", "EditParticleEffectTimeToLive");
    SubscribeToEvent(particleEffectWindow.GetChild("VelocityMin", true), "TextChanged", "EditParticleEffectVelocity");
    SubscribeToEvent(particleEffectWindow.GetChild("VelocityMax", true), "TextChanged", "EditParticleEffectVelocity");
    SubscribeToEvent(particleEffectWindow.GetChild("RotationMin", true), "TextChanged", "EditParticleEffectRotation");
    SubscribeToEvent(particleEffectWindow.GetChild("RotationMax", true), "TextChanged", "EditParticleEffectRotation");
    SubscribeToEvent(particleEffectWindow.GetChild("RotationSpeedMin", true), "TextChanged", "EditParticleEffectRotationSpeed");
    SubscribeToEvent(particleEffectWindow.GetChild("RotationSpeedMax", true), "TextChanged", "EditParticleEffectRotationSpeed");
    SubscribeToEvent(particleEffectWindow.GetChild("SizeAdd", true), "TextChanged", "EditParticleEffectSizeAdd");
    SubscribeToEvent(particleEffectWindow.GetChild("SizeMultiply", true), "TextChanged", "EditParticleEffectSizeMultiply");
    SubscribeToEvent(particleEffectWindow.GetChild("AnimationLodBias", true), "TextChanged", "EditParticleEffectAnimationLodBias");
    SubscribeToEvent(particleEffectWindow.GetChild("NumParticles", true), "TextChanged", "EditParticleEffectNumParticles");
    SubscribeToEvent(particleEffectWindow.GetChild("EmitterSizeX", true), "TextChanged", "EditParticleEffectEmitterSize");
    SubscribeToEvent(particleEffectWindow.GetChild("EmitterSizeY", true), "TextChanged", "EditParticleEffectEmitterSize");
    SubscribeToEvent(particleEffectWindow.GetChild("EmitterSizeZ", true), "TextChanged", "EditParticleEffectEmitterSize");
    SubscribeToEvent(particleEffectWindow.GetChild("EmissionRateMin", true), "TextChanged", "EditParticleEffectEmissionRate");
    SubscribeToEvent(particleEffectWindow.GetChild("EmissionRateMax", true), "TextChanged", "EditParticleEffectEmissionRate");
    SubscribeToEvent(particleEffectWindow.GetChild("EmitterShape", true), "ItemSelected", "EditParticleEffectEmitterShape");
    SubscribeToEvent(particleEffectWindow.GetChild("Scaled", true), "Toggled", "EditParticleEffectScaled");
    SubscribeToEvent(particleEffectWindow.GetChild("Sorted", true), "Toggled", "EditParticleEffectSorted");
    SubscribeToEvent(particleEffectWindow.GetChild("Relative", true), "Toggled", "EditParticleEffectRelative");

}

void EditParticleEffectConstantForce(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    Vector3 v = editParticleEffect.constantForce;

    if (element.name == "ConstantForceX")
        editParticleEffect.constantForce = Vector3(element.text.ToFloat(), v.y, v.z);

    if (element.name == "ConstantForceY")
        editParticleEffect.constantForce = Vector3(v.x, element.text.ToFloat(), v.z);

    if (element.name == "ConstantForceZ")
        editParticleEffect.constantForce = Vector3(v.x, v.y, element.text.ToFloat());
}

void EditParticleEffectDirection(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    Vector3 vMin = editParticleEffect.minDirection;
    Vector3 vMax = editParticleEffect.maxDirection;

    if (element.name == "DirectionMinX")
        editParticleEffect.minDirection = Vector3(element.text.ToFloat(), vMin.y, vMin.z);

    if (element.name == "DirectionMinY")
        editParticleEffect.minDirection = Vector3(vMin.x, element.text.ToFloat(), vMin.z);

    if (element.name == "DirectionMinZ")
        editParticleEffect.minDirection = Vector3(vMin.x, vMin.y, element.text.ToFloat());

    if (element.name == "DirectionMaxX")
        editParticleEffect.maxDirection = Vector3(element.text.ToFloat(), vMax.y, vMax.z);

    if (element.name == "DirectionMaxY")
        editParticleEffect.maxDirection = Vector3(vMax.x, element.text.ToFloat(), vMax.z);

    if (element.name == "DirectionMaxZ")
        editParticleEffect.maxDirection = Vector3(vMax.x, vMax.y, element.text.ToFloat());
}

void EditParticleEffectDampingForce(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    editParticleEffect.dampingForce = element.text.ToFloat();
}

void EditParticleEffectActiveTime(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    editParticleEffect.activeTime = element.text.ToFloat();
    particleEffectEmitter.Reset();
}

void EditParticleEffectInactiveTime(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    editParticleEffect.inactiveTime = element.text.ToFloat();
    particleEffectEmitter.Reset();
}

void EditParticleEffectParticleSize(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    Vector2 vMin = editParticleEffect.minParticleSize;
    Vector2 vMax = editParticleEffect.maxParticleSize;

    if (element.name == "ParticleSizeMinX")
        editParticleEffect.minParticleSize = Vector2(element.text.ToFloat(), vMin.y);

    if (element.name == "ParticleSizeMinY")
        editParticleEffect.minParticleSize = Vector2(vMin.x, element.text.ToFloat());

    if (element.name == "ParticleSizeMaxX")
        editParticleEffect.maxParticleSize = Vector2(element.text.ToFloat(), vMax.y);

    if (element.name == "ParticleSizeMaxY")
        editParticleEffect.maxParticleSize = Vector2(vMax.x, element.text.ToFloat());
}

void EditParticleEffectTimeToLive(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    float vMin = editParticleEffect.minTimeToLive;
    float vMax = editParticleEffect.maxTimeToLive;

    if (element.name == "TimeToLiveMin")
        editParticleEffect.minTimeToLive = element.text.ToFloat();

    if (element.name == "TimeToLiveMax")
        editParticleEffect.maxTimeToLive = element.text.ToFloat();
}

void EditParticleEffectVelocity(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    float vMin = editParticleEffect.minVelocity;
    float vMax = editParticleEffect.maxVelocity;

    if (element.name == "VelocityMin")
        editParticleEffect.minVelocity = element.text.ToFloat();

    if (element.name == "VelocityMax")
        editParticleEffect.maxVelocity = element.text.ToFloat();
}

void EditParticleEffectRotation(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    float vMin = editParticleEffect.minRotation;
    float vMax = editParticleEffect.maxRotation;

    if (element.name == "RotationMin")
        editParticleEffect.minRotation = element.text.ToFloat();

    if (element.name == "RotationMax")
        editParticleEffect.maxRotation = element.text.ToFloat();
}

void EditParticleEffectRotationSpeed(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    float vMin = editParticleEffect.minRotationSpeed;
    float vMax = editParticleEffect.maxRotationSpeed;

    if (element.name == "RotationSpeedMin")
        editParticleEffect.minRotationSpeed = element.text.ToFloat();

    if (element.name == "RotationSpeedMax")
        editParticleEffect.maxRotationSpeed = element.text.ToFloat();
}

void EditParticleEffectSizeAdd(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    editParticleEffect.sizeAdd = element.text.ToFloat();
}

void EditParticleEffectSizeMultiply(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    editParticleEffect.sizeMul = element.text.ToFloat();
}

void EditParticleEffectAnimationLodBias(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    editParticleEffect.animationLodBias = element.text.ToFloat();
}

void EditParticleEffectNumParticles(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    editParticleEffect.numParticles = element.text.ToInt();
    particleEffectEmitter.ApplyEffect();
}

void EditParticleEffectEmitterSize(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    Vector3 v = editParticleEffect.emitterSize;

    if (element.name == "EmitterSizeX")
        editParticleEffect.emitterSize = Vector3(element.text.ToFloat(), v.y, v.z);

    if (element.name == "EmitterSizeY")
        editParticleEffect.emitterSize = Vector3(v.x, element.text.ToFloat(), v.z);

    if (element.name == "EmitterSizeZ")
        editParticleEffect.emitterSize = Vector3(v.x, v.y, element.text.ToFloat());
}

void EditParticleEffectEmissionRate(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();

    if (element.name == "EmissionRateMin")
        editParticleEffect.minEmissionRate = element.text.ToFloat();

    if (element.name == "EmissionRateMax")
        editParticleEffect.maxEmissionRate = element.text.ToFloat();
}

void EditParticleEffectEmitterShape(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ element = eventData["Element"].GetPtr();

    switch (element.selection)
    {
        case 0:
            editParticleEffect.emitterType = EMITTER_BOX;
            break;

        case 1:
            editParticleEffect.emitterType = EMITTER_SPHERE;
            break;
    }
}

void EditParticleEffectMaterial(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ element = eventData["Element"].GetPtr();
    
    editParticleEffect.material = cache.GetResource("Material", element.text);
    particleEffectEmitter.ApplyEffect();
}

void PickEditParticleEffectMaterial(StringHash eventType, VariantMap& eventData)
{
    
}

void EditParticleEffectScaled(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ element = eventData["Element"].GetPtr();

    editParticleEffect.scaled = element.checked;
    particleEffectEmitter.ApplyEffect();
}

void EditParticleEffectSorted(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ element = eventData["Element"].GetPtr();

    editParticleEffect.sorted = element.checked;
    particleEffectEmitter.ApplyEffect();
}

void EditParticleEffectRelative(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ element = eventData["Element"].GetPtr();

    editParticleEffect.relative = element.checked;
    particleEffectEmitter.ApplyEffect();
}

bool ShowParticleEffectEditor()
{
    RefreshParticleEffectEditor();
    particleEffectWindow.visible = true;
    particleEffectWindow.BringToFront();
    return true;
}

void HideParticleEffectEditor()
{
    particleEffectWindow.visible = false;
}

void InitParticleEffectPreview()
{
    particlePreviewScene = Scene("particlePreviewScene");
    particlePreviewScene.CreateComponent("Octree");

    Node@ zoneNode = particlePreviewScene.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000, 1000);
    zone.ambientColor = Color(0.15, 0.15, 0.15);
    zone.fogColor = Color(0, 0, 0);
    zone.fogStart = 10.0;
    zone.fogEnd = 100.0;

    particlePreviewCameraNode = particlePreviewScene.CreateChild("PreviewCamera");
    particlePreviewCameraNode.position = Vector3(0, 0, -2.5);
    Camera@ camera = particlePreviewCameraNode.CreateComponent("Camera");
    camera.nearClip = 0.1f;
    camera.farClip = 100.0f;

    particlePreviewLightNode = particlePreviewScene.CreateChild("particlePreviewLight");
    particlePreviewLightNode.direction = Vector3(0.5, -0.5, 0.5);
    particlePreviewLight = particlePreviewLightNode.CreateComponent("Light");
    particlePreviewLight.lightType = LIGHT_DIRECTIONAL;
    particlePreviewLight.specularIntensity = 0.5;

    particleEffectPreviewNode = particlePreviewScene.CreateChild("PreviewEmitter");
    particleEffectPreviewNode.rotation = Quaternion(0, 0, 0);
    StaticModel@ gizmo = particleEffectPreviewNode.CreateComponent("StaticModel");
    gizmo.model = cache.GetResource("Model", "Models/Editor/Axes.mdl");
    gizmo.materials[0] = cache.GetResource("Material", "Materials/Editor/RedUnlit.xml");
    gizmo.materials[1] = cache.GetResource("Material", "Materials/Editor/GreenUnlit.xml");
    gizmo.materials[2] = cache.GetResource("Material", "Materials/Editor/BlueUnlit.xml");
    gizmo.occludee = false;

    particleEffectEmitter = particleEffectPreviewNode.CreateComponent("ParticleEmitter");
    editParticleEffect = cache.GetResource("ParticleEffect", "Particle/SnowExplosion.xml");
    editParticleEffect.activeTime = 0;
    particleEffectEmitter.effect = editParticleEffect;

    SubscribeToEvent(particleEffectPreviewNode, "Update", "HandleParticleEffectUpdate");

    particleEffectPreview = particleEffectWindow.GetChild("ParticleEffectPreview", true);
    particleEffectPreview.SetFixedHeight(100);
    particleEffectPreview.SetView(particlePreviewScene, camera);
    //particleEffectPreview.autoUpdate = true;

    SubscribeToEvent(particleEffectPreview, "DragMove", "RotateParticleEffectPreview");
}

void HandleParticleEffectUpdate(StringHash eventType, VariantMap& eventData)
{
    log.Info("ASDSA");
    if (!particleEffectEmitter.emitting)
    {
        log.Info("Reset emitter");
        particleEffectEmitter.Reset();
    }
}

void EditParticleEffect(ParticleEffect@ effect)
{
    if (editParticleEffect !is null)
        UnsubscribeFromEvent(editParticleEffect, "ReloadFinished");

    editParticleEffect = effect;
    effect.activeTime = 0;

    if (editParticleEffect !is null)
        SubscribeToEvent(editParticleEffect, "ReloadFinished", "RefreshParticleEffectEditor");

    ShowParticleEffectEditor();
}

void RefreshParticleEffectEditor()
{
    RefreshParticleEffectPreview();
    RefreshParticleEffectName();
    //RefreshParticleEffectInitial();
    RefreshParticleEffectMaterial();
}

void RefreshParticleEffectPreview()
{
    particleEffectEmitter.effect = editParticleEffect;
    particleEffectPreview.QueueUpdate();
}

void RefreshParticleEffectName()
{
    UIElement@ container = particleEffectWindow.GetChild("NameContainer", true);
    container.RemoveAllChildren();

    LineEdit@ nameEdit = CreateAttributeLineEdit(container, null, 0, 0);
    if (editParticleEffect !is null)
        nameEdit.text = editParticleEffect.name;
    SubscribeToEvent(nameEdit, "TextFinished", "EditParticleEffectName");

    Button@ pickButton = CreateResourcePickerButton(container, null, 0, 0, "Pick");
    SubscribeToEvent(pickButton, "Released", "PickEditParticleEffect");
}

void RefreshParticleEffectMaterial()
{
    UIElement@ container = particleEffectWindow.GetChild("ParticleMaterialContainer", true);
    container.RemoveAllChildren();

    LineEdit@ nameEdit = CreateAttributeLineEdit(container, null, 0, 0);
    if (editParticleEffect !is null)
        nameEdit.text = editParticleEffect.material.name;

    SubscribeToEvent(nameEdit, "TextFinished", "EditParticleEffectMaterial");

    Button@ pickButton = CreateResourcePickerButton(container, null, 0, 0, "Pick");
    SubscribeToEvent(pickButton, "Released", "PickEditParticleEffectMaterial");
}

void RotateParticleEffectPreview(StringHash eventType, VariantMap& eventData)
{
    int elemX = eventData["ElementX"].GetInt();
    int elemY = eventData["ElementY"].GetInt();
    
    if (particleEffectPreview.height > 0 && particleEffectPreview.width > 0)
    {
        float yaw = ((particleEffectPreview.height / 2) - elemY) * (90.0 / particleEffectPreview.height);
        float pitch = ((particleEffectPreview.width / 2) - elemX) * (90.0 / particleEffectPreview.width);

        particleEffectPreviewNode.rotation = particleEffectPreviewNode.rotation.Slerp(Quaternion(yaw, pitch, 0), 0.1);
        particleEffectPreview.QueueUpdate();
    }
}

void EditParticleEffectName(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ nameEdit = eventData["Element"].GetPtr();
    String newParticleEffectName = nameEdit.text.Trimmed();
    if (!newParticleEffectName.empty)
    {
        ParticleEffect@ newParticleEffect = cache.GetResource("ParticleEffect", newParticleEffectName);
        if (newParticleEffect !is null)
            EditParticleEffect(newParticleEffect);
    }
}

void PickEditParticleEffect()
{
    @resourcePicker = GetResourcePicker(StringHash("ParticleEffect"));
    if (resourcePicker is null)
        return;

    String lastPath = resourcePicker.lastPath;
    if (lastPath.empty)
        lastPath = sceneResourcePath;
    CreateFileSelector("Pick " + resourcePicker.typeName, "OK", "Cancel", lastPath, resourcePicker.filters, resourcePicker.lastFilter);
    SubscribeToEvent(uiFileSelector, "FileSelected", "PickEditParticleEffectDone");
}

void PickEditParticleEffectDone(StringHash eventType, VariantMap& eventData)
{
    StoreResourcePickerPath();
    CloseFileSelector();

    if (!eventData["OK"].GetBool())
    {
        @resourcePicker = null;
        return;
    }

    String resourceName = eventData["FileName"].GetString();
    Resource@ res = GetPickedResource(resourceName);

    if (res !is null)
        EditParticleEffect(cast<ParticleEffect>(res));

    @resourcePicker = null;
}

void NewParticleEffect()
{
    EditParticleEffect(ParticleEffect());
}

void RevertParticleEffect()
{
    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();
    cache.ReloadResource(editParticleEffect);
    EndParticleEffectEdit();
    
    RefreshParticleEffectEditor();
}

void SaveParticleEffect()
{
    if (editParticleEffect is null || editParticleEffect.name.empty)
        return;

    String fullName = cache.GetResourceFileName(editParticleEffect.name);
    if (fullName.empty)
        return;

    File saveFile(fullName, FILE_WRITE);
    editParticleEffect.Save(saveFile);
}

void SaveParticleEffectAs()
{
    if (editParticleEffect is null)
        return;

    @resourcePicker = GetResourcePicker(StringHash("ParticleEffect"));
    if (resourcePicker is null)
        return;

    String lastPath = resourcePicker.lastPath;
    if (lastPath.empty)
        lastPath = sceneResourcePath;
    CreateFileSelector("Save material as", "Save", "Cancel", lastPath, resourcePicker.filters, resourcePicker.lastFilter);
    SubscribeToEvent(uiFileSelector, "FileSelected", "SaveParticleEffectAsDone");
}

void SaveParticleEffectAsDone(StringHash eventType, VariantMap& eventData)
{
    StoreResourcePickerPath();
    CloseFileSelector();
    @resourcePicker = null;

    if (editParticleEffect is null)
        return;

    if (!eventData["OK"].GetBool())
    {
        @resourcePicker = null;
        return;
    }

    String fullName = eventData["FileName"].GetString();

    // Add default extension for saving if not specified
    String filter = eventData["Filter"].GetString();
    if (GetExtension(fullName).empty && filter != "*.*")
        fullName = fullName + filter.Substring(1);

    File saveFile(fullName, FILE_WRITE);
    if (editParticleEffect.Save(saveFile))
    {
        saveFile.Close();

        // Load the new resource to update the name in the editor
        ParticleEffect@ newEffect = cache.GetResource("ParticleEffect", GetResourceNameFromFullName(fullName));
        if (newEffect !is null)
            EditParticleEffect(newEffect);
    }
}

void BeginParticleEffectEdit()
{
    if (editParticleEffect is null)
        return;

    oldParticleEffectState = XMLFile();
    XMLElement particleEffectElem = oldParticleEffectState.CreateRoot("particleemitter");
    //editParticleEffect.Save(particleEffectElem);
}

void EndParticleEffectEdit()
{
    if (editParticleEffect is null)
        return;
    if (!dragEditAttribute)
    {
        EditParticleEffectAction@ action = EditParticleEffectAction();
        action.Define(editParticleEffect, oldParticleEffectState);
        SaveEditAction(action);
    }
    
    particleEffectPreview.QueueUpdate();
}
