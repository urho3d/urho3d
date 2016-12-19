
/// Settings
String cubeMapGen_Name;
String cubeMapGen_Path;
int cubeMapGen_Size;

Array<EditorCubeCapture@> activeCubeCapture; // Editor capture tasks in progress, Stop() method of EditorCubeCapture moves forward through the queue as captures are finished
Array<Zone@> cloneZones; // Duplicate zones constructed to prevent IBL doubling
Array<Zone@> disabledZones; // Zones that were disabled to prevent IBL doubling
const String cubemapDefaultOutputPath = "Textures/Cubemaps";

void PrepareZonesForCubeRendering()
{
    // Only clone zones when we aren't actively processing
    if (cloneZones.length > 0)
        return;
        
    Array<Component@>@ zones = editorScene.GetComponents("Zone", true);
    for (uint i = 0; i < zones.length; ++i)
    {
        Zone@ srcZone = cast<Zone>(zones[i]);
        if (zones[i].enabled)
        {
            Zone@ cloneZone = srcZone.node.CreateComponent("Zone");
            cloneZone.zoneMask = srcZone.zoneMask;
            cloneZone.priority = srcZone.priority;
            cloneZone.boundingBox = srcZone.boundingBox;
            
            cloneZone.ambientColor = srcZone.ambientColor;
            cloneZone.ambientGradient = srcZone.ambientGradient;
            
            cloneZone.fogColor = srcZone.fogColor;
            cloneZone.fogStart = srcZone.fogStart;
            cloneZone.fogEnd = srcZone.fogEnd;
            cloneZone.fogHeight = srcZone.fogHeight;
            cloneZone.fogHeightScale = srcZone.fogHeightScale;
            cloneZone.heightFog = srcZone.heightFog;
            
            srcZone.enabled = false;
            
            // Add the zones to our temporary lists
            cloneZones.Push(cloneZone);
            disabledZones.Push(srcZone);
        }
    }
    
    // Hide grid and debugIcons until bake
    if (grid !is null)
        grid.viewMask = 0;
    if (debugIconsNode !is null)
        debugIconsNode.enabled = false;
    debugRenderDisabled = true;
}

void UnprepareZonesForCubeRendering()
{
    // Clean up the clones
    for (uint i = 0; i < cloneZones.length; ++i)
        cloneZones[i].Remove();
    cloneZones.Clear();
        
    // Reenable anyone we disabled
    for (uint i = 0; i < disabledZones.length; ++i)
        disabledZones[i].enabled = true;
    disabledZones.Clear();
    
    // Show grid and debug icons    
    if (grid !is null)
        grid.viewMask = 0x80000000;
    if (debugIconsNode !is null)
        debugIconsNode.enabled = true;
    debugRenderDisabled = false;
}

class EditorCubeCapture : ScriptObject // script object in order to get events
{
    private String name_;
    private String path_;
    private Node@ camNode_;
    private Camera@ camera_;
    private Zone@ target_;
    private Viewport@ viewport_;
    private Texture2D@ renderImage_;
    private RenderSurface@ renderSurface_;
    int updateCycle_;
    String imagePath_;
    
    EditorCubeCapture(Zone@ forZone)
    {
        PrepareZonesForCubeRendering();
        
        // Store name and path because if we have a lot of zones it could take long enough to queue another go, and it may have different settings
        name_ = cubeMapGen_Name;
        path_ = sceneResourcePath + cubeMapGen_Path;

        updateCycle_ = 0;
    
        target_ = forZone;
    
        camNode_ = scene.CreateChild("RenderCamera");
        camera_ = camNode_.GetOrCreateComponent("Camera");
        camera_.fov = 90.0f;
        camera_.nearClip = 0.0001f;
        camera_.aspectRatio = 1.0f;
        camNode_.worldPosition = forZone.node.worldPosition;
        
        viewport_ = Viewport(scene, camera_);
        viewport_.renderPath = renderer.viewports[0].renderPath;
        
        updateCycle_ = 0;
    }
    
    ~EditorCubeCapture()
    {
        camNode_.Remove();
    }
    
    void Start()
    {
        // Construct render surface 
        renderImage_ = Texture2D();
        renderImage_.SetSize(cubeMapGen_Size, cubeMapGen_Size, GetRGBAFormat(), TEXTURE_RENDERTARGET);
        
        renderSurface_ = renderImage_.renderSurface;
        renderSurface_.viewports[0] = viewport_;
        renderSurface_.updateMode = SURFACE_UPDATEALWAYS;
    
        SubscribeToEvent("BeginFrame", "HandlePreRender");
        SubscribeToEvent("EndFrame", "HandlePostRender");
    }
    
    private void Stop()
    {
        camNode_.Remove();
        camNode_ = null;
        viewport_ = null;
        renderSurface_ = null;
        
        UnsubscribeFromEvent("BeginFrame");
        UnsubscribeFromEvent("EndFrame");
        
        WriteXML();
        
        // Remove ourselves from the processing list and if necessary clean things up
        // If others are pending in the queue then start the next one
        activeCubeCapture.Erase(activeCubeCapture.FindByRef(this));
        if (activeCubeCapture.length == 0)
            UnprepareZonesForCubeRendering();
        else
            activeCubeCapture[0].Start();
    }
    
    // Position camera accordingly
    void HandlePreRender(StringHash eventType, VariantMap& eventData)
    {
        if (camNode_ !is null)
        {
            ++updateCycle_;
        
            if (updateCycle_ < 7)
                camNode_.worldRotation = RotationOf(GetFaceForCycle(updateCycle_));
            else
                Stop();
        }
    }
    
    // Save our image
    void HandlePostRender(StringHash eventType, VariantMap& eventData)
    {
        Image@ img = renderImage_.GetImage();
        String sceneName = editorScene.name.length > 0 ? editorScene.name + "/" : "";
        String path = path_ + "/" + sceneName;
        fileSystem.CreateDir(path);
        path = path + "/" + String(target_.id) + "_" + GetFaceName(GetFaceForCycle(updateCycle_)) + ".png";
        img.SavePNG(path);
    }
    
    private void WriteXML()
    {
        String sceneName = editorScene.name.length > 0 ? "/" + editorScene.name + "/" : "";
        String basePath = AddTrailingSlash(path_ + sceneName);
        String cubeName = name_.length > 0 ? (name_ + "_") : "";
        String xmlPath = basePath + "/" + name_ + String(target_.id) + ".xml";
        XMLFile@ file = XMLFile();
        XMLElement rootElem = file.CreateRoot("cubemap");
        
        for (int i = 0; i < 6; ++i)
        {
            XMLElement faceElem = rootElem.CreateChild("face");
            faceElem.SetAttribute("name", GetResourceNameFromFullName(basePath + cubeName + String(target_.id) + "_" + GetFaceName(CubeMapFace(i)) + ".png"));
        }

        file.Save(File(xmlPath, FILE_WRITE), "    ");

        ResourceRef ref;
        ref.type = StringHash("TextureCube");
        ref.name = GetResourceNameFromFullName(xmlPath);
        target_.SetAttribute("Zone Texture", Variant(ref));
    }
    
    private CubeMapFace GetFaceForCycle(int cycle)
    {
        switch (updateCycle_)
        {
        case 1:
            return FACE_POSITIVE_X;
        case 2:                                                
            return FACE_POSITIVE_Y;                                   
        case 3:                                                
            return FACE_POSITIVE_Z;
        case 4:
            return FACE_NEGATIVE_X;
        case 5:
            return FACE_NEGATIVE_Y;
        case 6:
            return FACE_NEGATIVE_Z;
        }
        return FACE_POSITIVE_X;
    }
    
    private String GetFaceName(CubeMapFace face)
    {
        switch (face)
        {
        case FACE_POSITIVE_X:
            return "PosX";
        case FACE_POSITIVE_Y:                                  
            return "PosY";                                   
        case FACE_POSITIVE_Z:                                  
            return "PosZ";
        case FACE_NEGATIVE_X:
            return "NegX";
        case FACE_NEGATIVE_Y:
            return "NegY";
        case FACE_NEGATIVE_Z:
            return "NegZ";
        }
        return "PosX";
    }
    
    private Quaternion RotationOf(CubeMapFace face)
    {
        Quaternion result;
        switch (face)
        {
            //  Rotate camera according to probe rotation
            case FACE_POSITIVE_X:
                result = Quaternion(0, 90, 0);
                break;
            case FACE_NEGATIVE_X:
                result = Quaternion(0, -90, 0);
                break;
            case FACE_POSITIVE_Y:
                result = Quaternion(-90, 0, 0);
                break;
            case FACE_NEGATIVE_Y:
                result = Quaternion(90, 0, 0);
                break;
            case FACE_POSITIVE_Z:
                result = Quaternion(0, 0, 0);
                break;
            case FACE_NEGATIVE_Z:
                result = Quaternion(0, 180, 0);
                break;
        }
        return result;
    }
}