// Urho3D material editor

Window@ particleEffectWindow;
ParticleEffect@ editParticleEffect;
XMLFile@ oldParticleEffectState;
bool inParticleEffectRefresh = false;
View3D@ particleEffectPreview;
Camera@ particlePreviewCamera;
Scene@ particlePreviewScene;
Node@ particleEffectPreviewNode;
Node@ particleEffectPreviewGizmoNode;
Node@ particleEffectPreviewGridNode;
CustomGeometry@ particleEffectPreviewGrid;
Node@ particlePreviewCameraNode;
Node@ particlePreviewLightNode;
Light@ particlePreviewLight;
ParticleEmitter@ particleEffectEmitter;
float particleResetTimer;
bool showParticlePreviewAxes = true;
Vector3 particleViewCamDir;
Vector3 particleViewCamRot;
float particleViewCamDist;

float gizmoOffset = 0.1f;
float gizmoOffsetX;
float gizmoOffsetY;

void CreateParticleEffectEditor()
{
    if (particleEffectWindow !is null)
        return;

    particleEffectWindow = LoadEditorUI("UI/EditorParticleEffectWindow.xml");
    ui.root.AddChild(particleEffectWindow);
    particleEffectWindow.opacity = uiMaxOpacity;

    InitParticleEffectPreview();
    InitParticleEffectBasicAttributes();
    RefreshParticleEffectEditor();

    int width = Min(ui.root.width - 60, 800);
    int height = Min(ui.root.height - 60, 600);
    particleEffectWindow.SetSize(width, height);
    CenterDialog(particleEffectWindow);

    HideParticleEffectEditor();

    SubscribeToEvent(particleEffectWindow.GetChild("NewButton", true), "Released", "NewParticleEffect");
    SubscribeToEvent(particleEffectWindow.GetChild("RevertButton", true), "Released", "RevertParticleEffect");
    SubscribeToEvent(particleEffectWindow.GetChild("SaveButton", true), "Released", "SaveParticleEffect");
    SubscribeToEvent(particleEffectWindow.GetChild("SaveAsButton", true), "Released", "SaveParticleEffectAs");
    SubscribeToEvent(particleEffectWindow.GetChild("CloseButton", true), "Released", "HideParticleEffectEditor");
    SubscribeToEvent(particleEffectWindow.GetChild("NewColorFrame", true), "Released", "EditParticleEffectColorFrameNew");
    SubscribeToEvent(particleEffectWindow.GetChild("RemoveColorFrame", true), "Released", "EditParticleEffectColorFrameRemove");
    SubscribeToEvent(particleEffectWindow.GetChild("ColorFrameSort", true), "Released", "EditParticleEffectColorFrameSort");
    SubscribeToEvent(particleEffectWindow.GetChild("NewTextureFrame", true), "Released", "EditParticleEffectTextureFrameNew");
    SubscribeToEvent(particleEffectWindow.GetChild("RemoveTextureFrame", true), "Released", "EditParticleEffectTextureFrameRemove");
    SubscribeToEvent(particleEffectWindow.GetChild("TextureFrameSort", true), "Released", "EditParticleEffectTextureFrameSort");
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

    SubscribeToEvent(particleEffectWindow.GetChild("ConstantForceX", true), "TextFinished", "EditParticleEffectConstantForce");
    SubscribeToEvent(particleEffectWindow.GetChild("ConstantForceY", true), "TextFinished", "EditParticleEffectConstantForce");
    SubscribeToEvent(particleEffectWindow.GetChild("ConstantForceZ", true), "TextFinished", "EditParticleEffectConstantForce");
    SubscribeToEvent(particleEffectWindow.GetChild("DirectionMinX", true), "TextFinished", "EditParticleEffectDirection");
    SubscribeToEvent(particleEffectWindow.GetChild("DirectionMinY", true), "TextFinished", "EditParticleEffectDirection");
    SubscribeToEvent(particleEffectWindow.GetChild("DirectionMinZ", true), "TextFinished", "EditParticleEffectDirection");
    SubscribeToEvent(particleEffectWindow.GetChild("DirectionMaxX", true), "TextFinished", "EditParticleEffectDirection");
    SubscribeToEvent(particleEffectWindow.GetChild("DirectionMaxY", true), "TextFinished", "EditParticleEffectDirection");
    SubscribeToEvent(particleEffectWindow.GetChild("DirectionMaxZ", true), "TextFinished", "EditParticleEffectDirection");
    SubscribeToEvent(particleEffectWindow.GetChild("DampingForce", true), "TextFinished", "EditParticleEffectDampingForce");
    SubscribeToEvent(particleEffectWindow.GetChild("ActiveTime", true), "TextFinished", "EditParticleEffectActiveTime");
    SubscribeToEvent(particleEffectWindow.GetChild("InactiveTime", true), "TextFinished", "EditParticleEffectInactiveTime");
    SubscribeToEvent(particleEffectWindow.GetChild("ParticleSizeMinX", true), "TextFinished", "EditParticleEffectParticleSize");
    SubscribeToEvent(particleEffectWindow.GetChild("ParticleSizeMinY", true), "TextFinished", "EditParticleEffectParticleSize");
    SubscribeToEvent(particleEffectWindow.GetChild("ParticleSizeMaxX", true), "TextFinished", "EditParticleEffectParticleSize");
    SubscribeToEvent(particleEffectWindow.GetChild("ParticleSizeMaxY", true), "TextFinished", "EditParticleEffectParticleSize");
    SubscribeToEvent(particleEffectWindow.GetChild("TimeToLiveMin", true), "TextFinished", "EditParticleEffectTimeToLive");
    SubscribeToEvent(particleEffectWindow.GetChild("TimeToLiveMax", true), "TextFinished", "EditParticleEffectTimeToLive");
    SubscribeToEvent(particleEffectWindow.GetChild("VelocityMin", true), "TextFinished", "EditParticleEffectVelocity");
    SubscribeToEvent(particleEffectWindow.GetChild("VelocityMax", true), "TextFinished", "EditParticleEffectVelocity");
    SubscribeToEvent(particleEffectWindow.GetChild("RotationMin", true), "TextFinished", "EditParticleEffectRotation");
    SubscribeToEvent(particleEffectWindow.GetChild("RotationMax", true), "TextFinished", "EditParticleEffectRotation");
    SubscribeToEvent(particleEffectWindow.GetChild("RotationSpeedMin", true), "TextFinished", "EditParticleEffectRotationSpeed");
    SubscribeToEvent(particleEffectWindow.GetChild("RotationSpeedMax", true), "TextFinished", "EditParticleEffectRotationSpeed");
    SubscribeToEvent(particleEffectWindow.GetChild("SizeAdd", true), "TextFinished", "EditParticleEffectSizeAdd");
    SubscribeToEvent(particleEffectWindow.GetChild("SizeMultiply", true), "TextFinished", "EditParticleEffectSizeMultiply");
    SubscribeToEvent(particleEffectWindow.GetChild("AnimationLodBias", true), "TextFinished", "EditParticleEffectAnimationLodBias");
    SubscribeToEvent(particleEffectWindow.GetChild("NumParticles", true), "TextFinished", "EditParticleEffectNumParticles");
    SubscribeToEvent(particleEffectWindow.GetChild("EmitterSizeX", true), "TextFinished", "EditParticleEffectEmitterSize");
    SubscribeToEvent(particleEffectWindow.GetChild("EmitterSizeY", true), "TextFinished", "EditParticleEffectEmitterSize");
    SubscribeToEvent(particleEffectWindow.GetChild("EmitterSizeZ", true), "TextFinished", "EditParticleEffectEmitterSize");
    SubscribeToEvent(particleEffectWindow.GetChild("EmissionRateMin", true), "TextFinished", "EditParticleEffectEmissionRate");
    SubscribeToEvent(particleEffectWindow.GetChild("EmissionRateMax", true), "TextFinished", "EditParticleEffectEmissionRate");

    SubscribeToEvent(particleEffectWindow.GetChild("EmitterShape", true), "ItemSelected", "EditParticleEffectEmitterShape");
    SubscribeToEvent(particleEffectWindow.GetChild("Scaled", true), "Toggled", "EditParticleEffectScaled");
    SubscribeToEvent(particleEffectWindow.GetChild("Sorted", true), "Toggled", "EditParticleEffectSorted");
    SubscribeToEvent(particleEffectWindow.GetChild("Relative", true), "Toggled", "EditParticleEffectRelative");
    SubscribeToEvent(particleEffectWindow.GetChild("FixedScreenSize", true), "Toggled", "EditParticleEffectFixedScreenSize");
    SubscribeToEvent(particleEffectWindow.GetChild("FaceCameraMode", true), "ItemSelected", "EditParticleEffectFaceCameraMode");

    SubscribeToEvent(particleEffectWindow.GetChild("ResetViewport", true), "Released", "ParticleEffectResetViewport");
    SubscribeToEvent(particleEffectWindow.GetChild("ShowGrid", true), "Toggled", "ParticleEffectShowGrid");
}

void SetGizmoPosition()
{
    Vector3 screenPos = Vector3(gizmoOffsetX, gizmoOffsetY, 25.0);
    Vector3 newPos = particlePreviewCamera.ScreenToWorldPoint(screenPos);
    particleEffectPreviewGizmoNode.position = newPos;
}

void ResetCameraTransformation()
{
    particlePreviewCameraNode.position = Vector3(0, 0, -5);
    particlePreviewCameraNode.LookAt(Vector3(0, 0, 0));
    particleViewCamDir = -particlePreviewCameraNode.position;
    
    // Manually set initial rotation because eulerAngle always return 0 on first frame
    particleViewCamRot = Vector3(0.0, 180.0, 0.0);

    particleViewCamDist = particleViewCamDir.length;
    particleViewCamDir.Normalize();
}

void ParticleEffectResetViewport(StringHash eventType, VariantMap& eventData)
{
    ResetCameraTransformation();
    SetGizmoPosition();
    particleEffectPreview.QueueUpdate();
}

void ParticleEffectShowGrid(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ element = eventData["Element"].GetPtr();
    showParticlePreviewAxes = element.checked;
    particleEffectPreviewGridNode.enabled = showParticlePreviewAxes;
    particleEffectPreview.QueueUpdate();
}

void EditParticleEffectColorFrameNew(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    uint num = editParticleEffect.numColorFrames;
    editParticleEffect.numColorFrames = num + 1;
    RefreshParticleEffectColorFrames();

    EndParticleEffectEdit();
}

void EditParticleEffectTextureFrameNew(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    uint num = editParticleEffect.numTextureFrames;
    editParticleEffect.numTextureFrames = num + 1;
    RefreshParticleEffectTextureFrames();

    EndParticleEffectEdit();
}

void EditParticleEffectColorFrameRemove(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    ListView@ lv = particleEffectWindow.GetChild("ColorFrameListView", true);
    if (lv !is null && lv.selection != M_MAX_UNSIGNED)
    {
        BeginParticleEffectEdit();
        
        editParticleEffect.RemoveColorFrame(lv.selection);
        RefreshParticleEffectColorFrames();

        EndParticleEffectEdit();
    }

}

void EditParticleEffectTextureFrameRemove(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    ListView@ lv = particleEffectWindow.GetChild("TextureFrameListView", true);
    if (lv !is null && lv.selection != M_MAX_UNSIGNED)
    {
        BeginParticleEffectEdit();
        
        editParticleEffect.RemoveTextureFrame(lv.selection);
        RefreshParticleEffectTextureFrames();

        EndParticleEffectEdit();
    }
}

void EditParticleEffectColorFrameSort(StringHash eventType, VariantMap& eventData)
{
    RefreshParticleEffectColorFrames();
}

void EditParticleEffectTextureFrameSort(StringHash eventType, VariantMap& eventData)
{
    RefreshParticleEffectTextureFrames();
}

void InitParticleEffectBasicAttributes()
{
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("ConstantForceX", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("ConstantForceY", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("ConstantForceZ", true)));

    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("DirectionMinX", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("DirectionMinY", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("DirectionMinZ", true)));

    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("DirectionMaxX", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("DirectionMaxY", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("DirectionMaxZ", true)));

    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("DampingForce", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("ActiveTime", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("InactiveTime", true)));

    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("ParticleSizeMinX", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("ParticleSizeMinY", true)));

    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("ParticleSizeMaxX", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("ParticleSizeMaxY", true)));

    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("TimeToLiveMin", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("TimeToLiveMax", true)));

    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("VelocityMin", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("VelocityMax", true)));

    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("RotationMin", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("RotationMax", true)));

    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("RotationSpeedMin", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("RotationSpeedMax", true)));

    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("SizeAdd", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("SizeMultiply", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("AnimationLodBias", true)));

    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("NumParticles", true)));

    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("EmitterSizeX", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("EmitterSizeY", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("EmitterSizeZ", true)));

    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("EmissionRateMin", true)));
    CreateDragSlider(cast<LineEdit>(particleEffectWindow.GetChild("EmissionRateMax", true)));

}

void EditParticleEffectConstantForce(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();

    Vector3 v = editParticleEffect.constantForce;

    if (element.name == "ConstantForceX")
        editParticleEffect.constantForce = Vector3(element.text.ToFloat(), v.y, v.z);

    if (element.name == "ConstantForceY")
        editParticleEffect.constantForce = Vector3(v.x, element.text.ToFloat(), v.z);

    if (element.name == "ConstantForceZ")
        editParticleEffect.constantForce = Vector3(v.x, v.y, element.text.ToFloat());

    EndParticleEffectEdit();
}

void EditParticleEffectDirection(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

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

    EndParticleEffectEdit();
}

void EditParticleEffectDampingForce(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();

    editParticleEffect.dampingForce = element.text.ToFloat();

    EndParticleEffectEdit();
}

void EditParticleEffectActiveTime(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    if (particleEffectEmitter is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();

    editParticleEffect.activeTime = element.text.ToFloat();
    particleEffectEmitter.Reset();

    EndParticleEffectEdit();
}

void EditParticleEffectInactiveTime(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    if (particleEffectEmitter is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();

    editParticleEffect.inactiveTime = element.text.ToFloat();
    particleEffectEmitter.Reset();

    EndParticleEffectEdit();
}

void EditParticleEffectParticleSize(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

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

    EndParticleEffectEdit();
}

void EditParticleEffectTimeToLive(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();

    float vMin = editParticleEffect.minTimeToLive;
    float vMax = editParticleEffect.maxTimeToLive;

    if (element.name == "TimeToLiveMin")
        editParticleEffect.minTimeToLive = element.text.ToFloat();

    if (element.name == "TimeToLiveMax")
        editParticleEffect.maxTimeToLive = element.text.ToFloat();

    EndParticleEffectEdit();
}

void EditParticleEffectVelocity(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();

    float vMin = editParticleEffect.minVelocity;
    float vMax = editParticleEffect.maxVelocity;

    if (element.name == "VelocityMin")
        editParticleEffect.minVelocity = element.text.ToFloat();

    if (element.name == "VelocityMax")
        editParticleEffect.maxVelocity = element.text.ToFloat();

    EndParticleEffectEdit();
}

void EditParticleEffectRotation(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();

    float vMin = editParticleEffect.minRotation;
    float vMax = editParticleEffect.maxRotation;

    if (element.name == "RotationMin")
        editParticleEffect.minRotation = element.text.ToFloat();

    if (element.name == "RotationMax")
        editParticleEffect.maxRotation = element.text.ToFloat();

    EndParticleEffectEdit();
}

void EditParticleEffectRotationSpeed(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();

    float vMin = editParticleEffect.minRotationSpeed;
    float vMax = editParticleEffect.maxRotationSpeed;

    if (element.name == "RotationSpeedMin")
        editParticleEffect.minRotationSpeed = element.text.ToFloat();

    if (element.name == "RotationSpeedMax")
        editParticleEffect.maxRotationSpeed = element.text.ToFloat();

    EndParticleEffectEdit();
}

void EditParticleEffectSizeAdd(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();

    editParticleEffect.sizeAdd = element.text.ToFloat();

    EndParticleEffectEdit();
}

void EditParticleEffectSizeMultiply(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();

    editParticleEffect.sizeMul = element.text.ToFloat();

    EndParticleEffectEdit();
}

void EditParticleEffectAnimationLodBias(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();

    editParticleEffect.animationLodBias = element.text.ToFloat();

    EndParticleEffectEdit();
}

void EditParticleEffectNumParticles(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    if (particleEffectEmitter is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();

    editParticleEffect.numParticles = element.text.ToInt();
    particleEffectEmitter.ApplyEffect();

    EndParticleEffectEdit();
}

void EditParticleEffectEmitterSize(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();

    Vector3 v = editParticleEffect.emitterSize;

    if (element.name == "EmitterSizeX")
        editParticleEffect.emitterSize = Vector3(element.text.ToFloat(), v.y, v.z);

    if (element.name == "EmitterSizeY")
        editParticleEffect.emitterSize = Vector3(v.x, element.text.ToFloat(), v.z);

    if (element.name == "EmitterSizeZ")
        editParticleEffect.emitterSize = Vector3(v.x, v.y, element.text.ToFloat());

    EndParticleEffectEdit();
}

void EditParticleEffectEmissionRate(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();

    if (element.name == "EmissionRateMin")
        editParticleEffect.minEmissionRate = element.text.ToFloat();

    if (element.name == "EmissionRateMax")
        editParticleEffect.maxEmissionRate = element.text.ToFloat();

    EndParticleEffectEdit();
}

void EditParticleEffectEmitterShape(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    DropDownList@ element = eventData["Element"].GetPtr();

    switch (element.selection)
    {
        case 0:
            editParticleEffect.emitterType = EMITTER_SPHERE;
            break;

        case 1:
            editParticleEffect.emitterType = EMITTER_BOX;
            break;
    }

    EndParticleEffectEdit();
}

void EditParticleEffectFaceCameraMode(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    BeginParticleEffectEdit();

    DropDownList@ element = eventData["Element"].GetPtr();

    switch (element.selection)
    {
        case 0:
            editParticleEffect.faceCameraMode = FC_NONE;
            break;

        case 1:
            editParticleEffect.faceCameraMode = FC_ROTATE_XYZ;
            break;

        case 2:
            editParticleEffect.faceCameraMode = FC_ROTATE_Y;
            break;

        case 3:
            editParticleEffect.faceCameraMode = FC_LOOKAT_XYZ;
            break;

        case 4:
            editParticleEffect.faceCameraMode = FC_LOOKAT_Y;
            break;

        case 5:
            editParticleEffect.faceCameraMode = FC_DIRECTION;
            break;
    }

    particleEffectEmitter.ApplyEffect();

    EndParticleEffectEdit();
}

void EditParticleEffectMaterial(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    if (particleEffectEmitter is null)
        return;

    LineEdit@ element = eventData["Element"].GetPtr();
    Material@ res = cache.GetResource("Material", element.text);

    if (res !is null)
    {
        BeginParticleEffectEdit();

        editParticleEffect.material = res;
        particleEffectEmitter.ApplyEffect();
        
        EndParticleEffectEdit();
    }
}

void PickEditParticleEffectMaterial(StringHash eventType, VariantMap& eventData)
{
    @resourcePicker = GetResourcePicker(StringHash("Material"));
    if (resourcePicker is null)
        return;

    String lastPath = resourcePicker.lastPath;
    if (lastPath.empty)
        lastPath = sceneResourcePath;
    CreateFileSelector(localization.Get("Pick ") + resourcePicker.typeName, "OK", "Cancel", lastPath, resourcePicker.filters, resourcePicker.lastFilter, false);
    SubscribeToEvent(uiFileSelector, "FileSelected", "PickEditParticleEffectMaterialDone");
}

void PickEditParticleEffectMaterialDone(StringHash eventType, VariantMap& eventData)
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

    if (res !is null && editParticleEffect !is null && particleEffectEmitter !is null)
    {
        editParticleEffect.material = res;
        particleEffectEmitter.ApplyEffect();
        RefreshParticleEffectMaterial();
    }

    @resourcePicker = null;
}

void EditParticleEffectScaled(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    if (particleEffectEmitter is null)
        return;

    BeginParticleEffectEdit();

    CheckBox@ element = eventData["Element"].GetPtr();

    editParticleEffect.scaled = element.checked;
    particleEffectEmitter.ApplyEffect();

    EndParticleEffectEdit();
}

void EditParticleEffectSorted(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    if (particleEffectEmitter is null)
        return;

    BeginParticleEffectEdit();

    CheckBox@ element = eventData["Element"].GetPtr();

    editParticleEffect.sorted = element.checked;
    particleEffectEmitter.ApplyEffect();

    EndParticleEffectEdit();
}

void EditParticleEffectRelative(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    if (particleEffectEmitter is null)
        return;

    BeginParticleEffectEdit();

    CheckBox@ element = eventData["Element"].GetPtr();

    editParticleEffect.relative = element.checked;
    particleEffectEmitter.ApplyEffect();

    EndParticleEffectEdit();
}

void EditParticleEffectFixedScreenSize(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    if (particleEffectEmitter is null)
        return;

    BeginParticleEffectEdit();

    CheckBox@ element = eventData["Element"].GetPtr();

    editParticleEffect.fixedScreenSize = element.checked;
    particleEffectEmitter.ApplyEffect();

    EndParticleEffectEdit();
}

bool ToggleParticleEffectEditor()
{
    if (particleEffectWindow.visible == false)
        ShowParticleEffectEditor();
    else
        HideParticleEffectEditor();
    return true;
}

void ShowParticleEffectEditor()
{
    RefreshParticleEffectEditor();
    particleEffectWindow.visible = true;
    particleEffectWindow.BringToFront();
}

void HideParticleEffectEditor()
{
    if (particleEffectWindow !is null)
        particleEffectWindow.visible = false;
}

void UpdateParticleEffectPreviewGrid()
{
    uint gridSize = 8;
    uint gridSubdivisions = 3;

    //particleEffectPreviewGridNode.scale = Vector3(gridScale, gridScale, gridScale);
    uint size = uint(Floor(gridSize / 2) * 2);
    float halfSizeScaled = size / 2;
    float scale = 1.0;
    uint subdivisionSize = uint(Pow(2.0f, float(gridSubdivisions)));

    if (subdivisionSize > 0)
    {
        size *= subdivisionSize;
        scale /= subdivisionSize;
    }

    uint halfSize = size / 2;

    particleEffectPreviewGrid.BeginGeometry(0, LINE_LIST);
    float lineOffset = -halfSizeScaled;
    for (uint i = 0; i <= size; ++i)
    {
        bool lineCenter = i == halfSize;
        bool lineSubdiv = !Equals(Mod(i, subdivisionSize), 0.0);

        if (!grid2DMode)
        {
            particleEffectPreviewGrid.DefineVertex(Vector3(lineOffset, 0.0, halfSizeScaled));
            particleEffectPreviewGrid.DefineColor(lineCenter ? gridZColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            particleEffectPreviewGrid.DefineVertex(Vector3(lineOffset, 0.0, -halfSizeScaled));
            particleEffectPreviewGrid.DefineColor(lineCenter ? gridZColor : (lineSubdiv ? gridSubdivisionColor : gridColor));

            particleEffectPreviewGrid.DefineVertex(Vector3(-halfSizeScaled, 0.0, lineOffset));
            particleEffectPreviewGrid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            particleEffectPreviewGrid.DefineVertex(Vector3(halfSizeScaled, 0.0, lineOffset));
            particleEffectPreviewGrid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
        }
        else
        {
            particleEffectPreviewGrid.DefineVertex(Vector3(lineOffset, halfSizeScaled, 0.0));
            particleEffectPreviewGrid.DefineColor(lineCenter ? gridYColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            particleEffectPreviewGrid.DefineVertex(Vector3(lineOffset, -halfSizeScaled, 0.0));
            particleEffectPreviewGrid.DefineColor(lineCenter ? gridYColor : (lineSubdiv ? gridSubdivisionColor : gridColor));

            particleEffectPreviewGrid.DefineVertex(Vector3(-halfSizeScaled, lineOffset, 0.0));
            particleEffectPreviewGrid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            particleEffectPreviewGrid.DefineVertex(Vector3(halfSizeScaled, lineOffset, 0.0));
            particleEffectPreviewGrid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
        }

        lineOffset  += scale;
    }
    particleEffectPreviewGrid.Commit();
    
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
    zone.fogEnd = 1000.0;

    particlePreviewCameraNode = particlePreviewScene.CreateChild("PreviewCamera");
    particlePreviewCamera = particlePreviewCameraNode.CreateComponent("Camera");
    particlePreviewCamera.nearClip = 0.1f;
    particlePreviewCamera.farClip = 1000.0f;
    particlePreviewCamera.fov = 45.0f;

    particlePreviewLightNode = particlePreviewScene.CreateChild("particlePreviewLight");
    particlePreviewLightNode.direction = Vector3(0.5, -0.5, 0.5);
    particlePreviewLight = particlePreviewLightNode.CreateComponent("Light");
    particlePreviewLight.lightType = LIGHT_DIRECTIONAL;
    particlePreviewLight.specularIntensity = 0.5;

    particleEffectPreviewNode = particlePreviewScene.CreateChild("PreviewEmitter");
    particleEffectPreviewNode.rotation = Quaternion(0, 0, 0);
    
    ResetCameraTransformation();

    particleEffectPreviewGizmoNode = particlePreviewScene.CreateChild("Gizmo");
    StaticModel@ gizmo = particleEffectPreviewGizmoNode.CreateComponent("StaticModel");
    gizmo.model = cache.GetResource("Model", "Models/Editor/Axes.mdl");
    gizmo.materials[0] = cache.GetResource("Material", "Materials/Editor/RedUnlit.xml");
    gizmo.materials[1] = cache.GetResource("Material", "Materials/Editor/GreenUnlit.xml");
    gizmo.materials[2] = cache.GetResource("Material", "Materials/Editor/BlueUnlit.xml");
    gizmo.occludee = false;

    particleEffectPreviewGridNode = particlePreviewScene.CreateChild("Grid");
    particleEffectPreviewGrid = particleEffectPreviewGridNode.CreateComponent("CustomGeometry");
    particleEffectPreviewGrid.numGeometries = 1;
    particleEffectPreviewGrid.material = cache.GetResource("Material", "Materials/VColUnlit.xml");
    particleEffectPreviewGrid.viewMask = 0x80000000; // Editor raycasts use viewmask 0x7fffffff
    particleEffectPreviewGrid.occludee = false;

    UpdateParticleEffectPreviewGrid();

    particleEffectEmitter = particleEffectPreviewNode.CreateComponent("ParticleEmitter");
    editParticleEffect = CreateNewParticleEffect();
    particleEffectEmitter.effect = editParticleEffect;

    particleEffectPreview = particleEffectWindow.GetChild("ParticleEffectPreview", true);
    particleEffectPreview.SetView(particlePreviewScene, particlePreviewCamera);
    particleEffectPreview.viewport.renderPath = renderPath;

    SubscribeToEvent(particleEffectPreview, "DragMove", "NavigateParticleEffectPreview");
    SubscribeToEvent(particleEffectPreview, "Resized", "ResizeParticleEffectPreview");
}

ParticleEffect@ CreateNewParticleEffect()
{
    ParticleEffect@ effect = ParticleEffect();
    Material@ res = cache.GetResource("Material", "Materials/Particle.xml");
    if (res is null)
        log.Error("Could not load default material for new particle effect.");
    effect.material = res;
    effect.AddColorTime(Color(1,1,1,1), 0.0f);
    return effect;
}

void EditParticleEffect(ParticleEffect@ effect)
{
    if (effect is null)
        return;

    if (editParticleEffect !is null)
        UnsubscribeFromEvent(editParticleEffect, "ReloadFinished");

    if (!effect.name.empty)
        cache.ReloadResource(effect);
        
    editParticleEffect = effect;
    particleEffectEmitter.effect = editParticleEffect;

    if (editParticleEffect !is null)
        SubscribeToEvent(editParticleEffect, "ReloadFinished", "RefreshParticleEffectEditor");

    ShowParticleEffectEditor();
}

void RefreshParticleEffectEditor()
{
    inParticleEffectRefresh = true;

    RefreshParticleEffectPreview();
    RefreshParticleEffectName();
    RefreshParticleEffectBasicAttributes();
    RefreshParticleEffectMaterial();
    RefreshParticleEffectColorFrames();
    RefreshParticleEffectTextureFrames();

    inParticleEffectRefresh = false;
}

void RefreshParticleEffectColorFrames()
{
    if (editParticleEffect is null)
        return;

    editParticleEffect.SortColorFrames();

    ListView@ lv = particleEffectWindow.GetChild("ColorFrameListView", true);
    if (lv is null)
        return;
        
    lv.RemoveAllItems();

    for (uint i = 0; i < editParticleEffect.numColorFrames; i++)
    {
        ColorFrame@ colorFrame = editParticleEffect.GetColorFrame(i);

        Button@ container = Button();
        lv.AddItem(container);
        container.style = "Button";
        container.imageRect = IntRect(18, 2, 30, 14);
        container.minSize = IntVector2(0, 20);
        container.maxSize = IntVector2(2147483647, 20);
        container.layoutMode = LM_HORIZONTAL;
        container.layoutBorder = IntRect(3,1,3,1);
        container.layoutSpacing = 4;

        UIElement@ labelContainer = UIElement();
        container.AddChild(labelContainer);
        labelContainer.style = "HorizontalPanel";
        labelContainer.minSize = IntVector2(0, 16);
        labelContainer.maxSize = IntVector2(2147483647, 16);
        labelContainer.verticalAlignment = VA_CENTER;

        {
            LineEdit@ le = LineEdit();
            labelContainer.AddChild(le);
            le.name = "ColorTime";
            le.vars["ColorFrame"] = i;
            le.style = "LineEdit";
            le.minSize = IntVector2(0, 16);
            le.maxSize = IntVector2(40, 16);
            le.text = colorFrame.time;
            le.cursorPosition = 0;
            CreateDragSlider(le);

            SubscribeToEvent(le, "TextChanged", "EditParticleEffectColorFrame");
        }

        UIElement@ textContainer = UIElement();
        labelContainer.AddChild(textContainer);
        textContainer.minSize = IntVector2(0, 16);
        textContainer.maxSize = IntVector2(2147483647, 16);
        textContainer.verticalAlignment = VA_CENTER;

        Text@ t = Text();
        textContainer.AddChild(t);
        t.style = "Text";
        t.text = "Color";
        t.autoLocalizable = true;

        UIElement@ editContainer = UIElement();
        container.AddChild(editContainer);
        editContainer.style = "HorizontalPanel";
        editContainer.minSize = IntVector2(0, 16);
        editContainer.maxSize = IntVector2(2147483647, 16);
        editContainer.verticalAlignment = VA_CENTER;

        {
            LineEdit@ le = LineEdit();
            editContainer.AddChild(le);
            le.name = "ColorR";
            le.vars["ColorFrame"] = i;
            le.style = "LineEdit";
            le.text = colorFrame.color.r;
            le.cursorPosition = 0;
            CreateDragSlider(le);

            SubscribeToEvent(le, "TextChanged", "EditParticleEffectColorFrame");
        }
        {
            LineEdit@ le = LineEdit();
            editContainer.AddChild(le);
            le.name = "ColorG";
            le.vars["ColorFrame"] = i;
            le.style = "LineEdit";
            le.text = colorFrame.color.g;
            le.cursorPosition = 0;
            CreateDragSlider(le);

            SubscribeToEvent(le, "TextChanged", "EditParticleEffectColorFrame");
        }
        {
            LineEdit@ le = LineEdit();
            editContainer.AddChild(le);
            le.name = "ColorB";
            le.vars["ColorFrame"] = i;
            le.style = "LineEdit";
            le.text = colorFrame.color.b;
            le.cursorPosition = 0;
            CreateDragSlider(le);

            SubscribeToEvent(le, "TextChanged", "EditParticleEffectColorFrame");
        }
        {
            LineEdit@ le = LineEdit();
            editContainer.AddChild(le);
            le.name = "ColorA";
            le.vars["ColorFrame"] = i;
            le.style = "LineEdit";
            le.text = colorFrame.color.a;
            le.cursorPosition = 0;
            CreateDragSlider(le);

            SubscribeToEvent(le, "TextChanged", "EditParticleEffectColorFrame");
        }

    }
}

void RefreshParticleEffectTextureFrames()
{
    if (editParticleEffect is null)
        return;

    editParticleEffect.SortTextureFrames();

    ListView@ lv = particleEffectWindow.GetChild("TextureFrameListView", true);
    if (lv is null)
        return;

    lv.RemoveAllItems();

    for (uint i = 0; i < editParticleEffect.numTextureFrames; i++)
    {
        TextureFrame@ textureFrame = editParticleEffect.GetTextureFrame(i);
        if (textureFrame is null)
            continue;

        Button@ container = Button();
        lv.AddItem(container);
        container.style = "Button";
        container.imageRect = IntRect(18, 2, 30, 14);
        container.minSize = IntVector2(0, 20);
        container.maxSize = IntVector2(2147483647, 20);
        container.layoutMode = LM_HORIZONTAL;
        container.layoutBorder = IntRect(1,1,1,1);
        container.layoutSpacing = 4;

        UIElement@ labelContainer = UIElement();
        container.AddChild(labelContainer);
        labelContainer.style = "HorizontalPanel";
        labelContainer.minSize = IntVector2(0, 16);
        labelContainer.maxSize = IntVector2(2147483647, 16);
        labelContainer.verticalAlignment = VA_CENTER;

        {
            LineEdit@ le = LineEdit();
            labelContainer.AddChild(le);
            le.name = "TextureTime";
            le.vars["TextureFrame"] = i;
            le.style = "LineEdit";
            le.minSize = IntVector2(0, 16);
            le.maxSize = IntVector2(40, 16);
            le.text = textureFrame.time;
            le.cursorPosition = 0;
            CreateDragSlider(le);

            SubscribeToEvent(le, "TextChanged", "EditParticleEffectTextureFrame");
        }

        UIElement@ textContainer = UIElement();
        labelContainer.AddChild(textContainer);
        textContainer.minSize = IntVector2(0, 16);
        textContainer.maxSize = IntVector2(2147483647, 16);
        textContainer.verticalAlignment = VA_CENTER;

        Text@ t = Text();
        textContainer.AddChild(t);
        t.style = "Text";
        t.text = "Texture";
        t.autoLocalizable = true;

        UIElement@ editContainer = UIElement();
        container.AddChild(editContainer);
        editContainer.style = "HorizontalPanel";
        editContainer.minSize = IntVector2(0, 16);
        editContainer.maxSize = IntVector2(2147483647, 16);
        editContainer.verticalAlignment = VA_CENTER;

        {
            LineEdit@ le = LineEdit();
            editContainer.AddChild(le);
            le.name = "TextureMinX";
            le.vars["TextureFrame"] = i;
            le.style = "LineEdit";
            le.text = textureFrame.uv.min.x;
            le.cursorPosition = 0;
            CreateDragSlider(le);

            SubscribeToEvent(le, "TextChanged", "EditParticleEffectTextureFrame");
        }
        {
            LineEdit@ le = LineEdit();
            editContainer.AddChild(le);
            le.name = "TextureMinY";
            le.vars["TextureFrame"] = i;
            le.style = "LineEdit";
            le.text = textureFrame.uv.min.y;
            le.cursorPosition = 0;
            CreateDragSlider(le);

            SubscribeToEvent(le, "TextChanged", "EditParticleEffectTextureFrame");
        }
        {
            LineEdit@ le = LineEdit();
            editContainer.AddChild(le);
            le.name = "TextureMaxX";
            le.vars["TextureFrame"] = i;
            le.style = "LineEdit";
            le.text = textureFrame.uv.max.x;
            le.cursorPosition = 0;
            CreateDragSlider(le);

            SubscribeToEvent(le, "TextChanged", "EditParticleEffectTextureFrame");
        }
        {
            LineEdit@ le = LineEdit();
            editContainer.AddChild(le);
            le.name = "TextureMaxY";
            le.vars["TextureFrame"] = i;
            le.style = "LineEdit";
            le.text = textureFrame.uv.max.y;
            le.cursorPosition = 0;
            CreateDragSlider(le);

            SubscribeToEvent(le, "TextChanged", "EditParticleEffectTextureFrame");
        }
    }
}

void EditParticleEffectColorFrame(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    if (particleEffectEmitter is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();
    uint i = element.vars["ColorFrame"].GetInt();
    ColorFrame@ cf = editParticleEffect.GetColorFrame(i);

    if (element.name == "ColorTime")
        cf.time = element.text.ToFloat();

    if (element.name == "ColorR")
        cf.color = Color(element.text.ToFloat(), cf.color.g, cf.color.b, cf.color.a);

    if (element.name == "ColorG")
        cf.color = Color(cf.color.r, element.text.ToFloat(), cf.color.b, cf.color.a);

    if (element.name == "ColorB")
        cf.color = Color(cf.color.r, cf.color.g, element.text.ToFloat(), cf.color.a);

    if (element.name == "ColorA")
        cf.color = Color(cf.color.r, cf.color.g, cf.color.b, element.text.ToFloat());

    editParticleEffect.SetColorFrame(i, cf);
    particleEffectEmitter.Reset();

    EndParticleEffectEdit();
}

void EditParticleEffectTextureFrame(StringHash eventType, VariantMap& eventData)
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    if (particleEffectEmitter is null)
        return;

    BeginParticleEffectEdit();

    LineEdit@ element = eventData["Element"].GetPtr();
    uint i = element.vars["TextureFrame"].GetInt();
    TextureFrame@ tf = editParticleEffect.GetTextureFrame(i);

    if (element.name == "TextureTime")
        tf.time = element.text.ToFloat();

    if (element.name == "TextureMinX")
        tf.uv = Rect(element.text.ToFloat(), tf.uv.min.y, tf.uv.max.x, tf.uv.max.y);

    if (element.name == "TextureMinY")
        tf.uv = Rect(tf.uv.min.x, element.text.ToFloat(), tf.uv.max.x, tf.uv.max.y);

    if (element.name == "TextureMaxX")
        tf.uv = Rect(tf.uv.min.x, tf.uv.min.y, element.text.ToFloat(), tf.uv.max.y);

    if (element.name == "TextureMaxY")
        tf.uv = Rect(tf.uv.min.x, tf.uv.min.y, tf.uv.max.x, element.text.ToFloat());

    editParticleEffect.SetTextureFrame(i, tf);
    particleEffectEmitter.Reset();

    EndParticleEffectEdit();
}

void RefreshParticleEffectPreview()
{
    if (particleEffectEmitter is null || editParticleEffect is null)
        return;
    cast<CheckBox>(particleEffectWindow.GetChild("ShowGrid", true)).checked = showParticlePreviewAxes;
    particleEffectEmitter.effect = editParticleEffect;
    particleEffectEmitter.Reset();
    particleEffectPreview.QueueUpdate();
}

void RefreshParticleEffectName()
{
    UIElement@ container = particleEffectWindow.GetChild("NameContainer", true);
    if (container is null)
        return;
        
    container.RemoveAllChildren();

    LineEdit@ nameEdit = CreateAttributeLineEdit(container, null, 0, 0);
    if (editParticleEffect !is null)
        nameEdit.text = editParticleEffect.name;
    SubscribeToEvent(nameEdit, "TextFinished", "EditParticleEffectName");

    Button@ pickButton = CreateResourcePickerButton(container, null, 0, 0, "smallButtonPick");
    SubscribeToEvent(pickButton, "Released", "PickEditParticleEffect");
}

void RefreshParticleEffectBasicAttributes()
{
    if (editParticleEffect is null)
        return;

    cast<LineEdit>(particleEffectWindow.GetChild("ConstantForceX", true)).text = editParticleEffect.constantForce.x;
    cast<LineEdit>(particleEffectWindow.GetChild("ConstantForceY", true)).text = editParticleEffect.constantForce.y;
    cast<LineEdit>(particleEffectWindow.GetChild("ConstantForceZ", true)).text = editParticleEffect.constantForce.z;

    cast<LineEdit>(particleEffectWindow.GetChild("DirectionMinX", true)).text = editParticleEffect.minDirection.x;
    cast<LineEdit>(particleEffectWindow.GetChild("DirectionMinY", true)).text = editParticleEffect.minDirection.y;
    cast<LineEdit>(particleEffectWindow.GetChild("DirectionMinZ", true)).text = editParticleEffect.minDirection.z;

    cast<LineEdit>(particleEffectWindow.GetChild("DirectionMaxX", true)).text = editParticleEffect.maxDirection.x;
    cast<LineEdit>(particleEffectWindow.GetChild("DirectionMaxY", true)).text = editParticleEffect.maxDirection.y;
    cast<LineEdit>(particleEffectWindow.GetChild("DirectionMaxZ", true)).text = editParticleEffect.maxDirection.z;

    cast<LineEdit>(particleEffectWindow.GetChild("DampingForce", true)).text = editParticleEffect.dampingForce;
    cast<LineEdit>(particleEffectWindow.GetChild("ActiveTime", true)).text = editParticleEffect.activeTime;
    cast<LineEdit>(particleEffectWindow.GetChild("InactiveTime", true)).text = editParticleEffect.inactiveTime;

    cast<LineEdit>(particleEffectWindow.GetChild("ParticleSizeMinX", true)).text = editParticleEffect.minParticleSize.x;
    cast<LineEdit>(particleEffectWindow.GetChild("ParticleSizeMinY", true)).text = editParticleEffect.minParticleSize.y;

    cast<LineEdit>(particleEffectWindow.GetChild("ParticleSizeMaxX", true)).text = editParticleEffect.maxParticleSize.x;
    cast<LineEdit>(particleEffectWindow.GetChild("ParticleSizeMaxY", true)).text = editParticleEffect.maxParticleSize.y;

    cast<LineEdit>(particleEffectWindow.GetChild("TimeToLiveMin", true)).text = editParticleEffect.minTimeToLive;
    cast<LineEdit>(particleEffectWindow.GetChild("TimeToLiveMax", true)).text = editParticleEffect.maxTimeToLive;

    cast<LineEdit>(particleEffectWindow.GetChild("VelocityMin", true)).text = editParticleEffect.minVelocity;
    cast<LineEdit>(particleEffectWindow.GetChild("VelocityMax", true)).text = editParticleEffect.maxVelocity;

    cast<LineEdit>(particleEffectWindow.GetChild("RotationMin", true)).text = editParticleEffect.minRotation;
    cast<LineEdit>(particleEffectWindow.GetChild("RotationMax", true)).text = editParticleEffect.maxRotation;

    cast<LineEdit>(particleEffectWindow.GetChild("RotationSpeedMin", true)).text = editParticleEffect.minRotationSpeed;
    cast<LineEdit>(particleEffectWindow.GetChild("RotationSpeedMax", true)).text = editParticleEffect.maxRotationSpeed;

    cast<LineEdit>(particleEffectWindow.GetChild("SizeAdd", true)).text = editParticleEffect.sizeAdd;
    cast<LineEdit>(particleEffectWindow.GetChild("SizeMultiply", true)).text = editParticleEffect.sizeMul;
    cast<LineEdit>(particleEffectWindow.GetChild("AnimationLodBias", true)).text = editParticleEffect.animationLodBias;

    cast<LineEdit>(particleEffectWindow.GetChild("NumParticles", true)).text = editParticleEffect.numParticles;

    cast<LineEdit>(particleEffectWindow.GetChild("EmitterSizeX", true)).text = editParticleEffect.emitterSize.x;
    cast<LineEdit>(particleEffectWindow.GetChild("EmitterSizeY", true)).text = editParticleEffect.emitterSize.y;
    cast<LineEdit>(particleEffectWindow.GetChild("EmitterSizeZ", true)).text = editParticleEffect.emitterSize.z;

    cast<LineEdit>(particleEffectWindow.GetChild("EmissionRateMin", true)).text = editParticleEffect.minEmissionRate;
    cast<LineEdit>(particleEffectWindow.GetChild("EmissionRateMax", true)).text = editParticleEffect.maxEmissionRate;

    switch (editParticleEffect.emitterType)
    {
        case EMITTER_SPHERE:
            cast<DropDownList>(particleEffectWindow.GetChild("EmitterShape", true)).selection = 0;
            break;
        case EMITTER_BOX:
            cast<DropDownList>(particleEffectWindow.GetChild("EmitterShape", true)).selection = 1;
            break;
    }

    switch (editParticleEffect.faceCameraMode)
    {
        case FC_NONE:
            cast<DropDownList>(particleEffectWindow.GetChild("FaceCameraMode", true)).selection = 0;
            break;
        case FC_ROTATE_XYZ:
            cast<DropDownList>(particleEffectWindow.GetChild("FaceCameraMode", true)).selection = 1;
            break;
        case FC_ROTATE_Y:
            cast<DropDownList>(particleEffectWindow.GetChild("FaceCameraMode", true)).selection = 2;
            break;
        case FC_LOOKAT_XYZ:
            cast<DropDownList>(particleEffectWindow.GetChild("FaceCameraMode", true)).selection = 3;
            break;
        case FC_LOOKAT_Y:
            cast<DropDownList>(particleEffectWindow.GetChild("FaceCameraMode", true)).selection = 4;
            break;
        case FC_DIRECTION:
            cast<DropDownList>(particleEffectWindow.GetChild("FaceCameraMode", true)).selection = 5;
            break;
    }

    cast<CheckBox>(particleEffectWindow.GetChild("Scaled", true)).checked = editParticleEffect.scaled;
    cast<CheckBox>(particleEffectWindow.GetChild("Sorted", true)).checked = editParticleEffect.sorted;
    cast<CheckBox>(particleEffectWindow.GetChild("Relative", true)).checked = editParticleEffect.relative;
    cast<CheckBox>(particleEffectWindow.GetChild("FixedScreenSize", true)).checked = editParticleEffect.fixedScreenSize;
}

void RefreshParticleEffectMaterial()
{
    UIElement@ container = particleEffectWindow.GetChild("ParticleMaterialContainer", true);
    if (container is null)
        return;
        
    container.RemoveAllChildren();

    LineEdit@ nameEdit = CreateAttributeLineEdit(container, null, 0, 0);
    if (editParticleEffect !is null)
    {
        if (editParticleEffect.material !is null)
            nameEdit.text = editParticleEffect.material.name;
        else
        {
            nameEdit.text = "Materials/Particle.xml";
            Material@ res = cache.GetResource("Material", "Materials/Particle.xml");
            if (res !is null)
                editParticleEffect.material = res;
        }
    }

    SubscribeToEvent(nameEdit, "TextFinished", "EditParticleEffectMaterial");

    Button@ pickButton = CreateResourcePickerButton(container, null, 0, 0, "smallButtonPick");
    SubscribeToEvent(pickButton, "Released", "PickEditParticleEffectMaterial");
}

void NavigateParticleEffectPreview(StringHash eventType, VariantMap& eventData)
{
    int dx = eventData["DX"].GetInt();
    int dy = eventData["DY"].GetInt();

    if (particleEffectPreview.height > 0 && particleEffectPreview.width > 0)
    {
        if (!input.keyDown[KEY_LSHIFT])
        {
            particleViewCamRot.x -= dy * 20 * time.timeStep;
            particleViewCamRot.y += dx * 20 * time.timeStep;
            particleViewCamRot.x = Clamp(particleViewCamRot.x, -89.5, 89.5);
        }
        else
        {
            particleViewCamDist += dy * 1.5 * time.timeStep;
            particleViewCamDist -= dx * 1.5 * time.timeStep;
            particleViewCamDist = Max(particleViewCamDist, 0.2);
        }
        particlePreviewCameraNode.position = particleEffectPreviewNode.position + 
            Quaternion(particleViewCamRot.x, particleViewCamRot.y, 0) * particleViewCamDir * particleViewCamDist;
        particlePreviewCameraNode.LookAt(particleEffectPreviewNode.position);

        SetGizmoPosition();
        particleEffectPreview.QueueUpdate();
    }

}

void ResizeParticleEffectPreview(StringHash eventType, VariantMap& eventData)
{
    
    float width = float(particleEffectPreview.width);
    float height = float(particleEffectPreview.height);
    
    // Manually set aspect ratio because first frame is always returning aspect ratio of 1
    float aspectRatio = width / height;
    particlePreviewCamera.aspectRatio = aspectRatio;

    gizmoOffsetX = gizmoOffset;
    gizmoOffsetY = 1.0f - gizmoOffset * aspectRatio;

    if(width > height)
    {
        aspectRatio = height / width;
        gizmoOffsetY = 1.0f - gizmoOffset;
        gizmoOffsetX = gizmoOffset * aspectRatio;
    }

    SetGizmoPosition();
    particleEffectPreview.QueueUpdate();
}

void EditParticleEffectName(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ nameEdit = eventData["Element"].GetPtr();
    String newParticleEffectName = nameEdit.text.Trimmed();
    if (!newParticleEffectName.empty && !(editParticleEffect !is null && newParticleEffectName == editParticleEffect.name))
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
    CreateFileSelector(localization.Get("Pick ") + resourcePicker.typeName, "OK", "Cancel", lastPath, resourcePicker.filters, resourcePicker.lastFilter, false);
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
    BeginParticleEffectEdit();

    EditParticleEffect(CreateNewParticleEffect());
    
    EndParticleEffectEdit();
}

void RevertParticleEffect()
{
    if (inParticleEffectRefresh)
        return;

    if (editParticleEffect is null)
        return;

    if (editParticleEffect.name.empty)
    {
        NewParticleEffect();
        return;
    }

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
    CreateFileSelector("Save particle effect as", "Save", "Cancel", lastPath, resourcePicker.filters, resourcePicker.lastFilter);
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

    inParticleEffectRefresh = true;

    oldParticleEffectState = XMLFile();
    XMLElement particleElem = oldParticleEffectState.CreateRoot("particleeffect");
    editParticleEffect.Save(particleElem);
}

void EndParticleEffectEdit()
{
    if (editParticleEffect is null)
        return;

    if (!dragEditAttribute)
    {
        EditParticleEffectAction@ action = EditParticleEffectAction();
        action.Define(particleEffectEmitter, editParticleEffect, oldParticleEffectState);
        SaveEditAction(action);
    }

    inParticleEffectRefresh = false;
    
    particleEffectPreview.QueueUpdate();
}
