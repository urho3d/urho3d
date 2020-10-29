// Urho3D editor view & camera functions

WeakHandle previewCamera;

Node@ cameraLookAtNode;
Node@ cameraNode;
Camera@ camera;

float orthoCameraZoom = 1.0f;

Node@ gridNode;
CustomGeometry@ grid;

UIElement@ viewportUI; // holds the viewport ui, convienent for clearing and hiding
uint setViewportCursor = 0; // used to set cursor in post update
uint resizingBorder = 0; // current border that is dragging
uint viewportMode = VIEWPORT_SINGLE;
int  viewportBorderOffset = 2; // used to center borders over viewport seams,  should be half of width
int  viewportBorderWidth = 4; // width of a viewport resize border
IntRect viewportArea; // the area where the editor viewport is. if we ever want to have the viewport not take up the whole screen this abstracts that
IntRect viewportUIClipBorder = IntRect(27, 60, 0, 0); // used to clip viewport borders, the borders are ugly when going behind the transparent toolbars
RenderPath@ renderPath; // Renderpath to use on all views
String renderPathName;
bool gammaCorrection = false;
bool HDR = false;
bool contextMenuActionWaitFrame = false;
bool cameraFlyMode = true;
int hotKeyMode = 0; // used for checking that kind of style manipulation user are prefer (see HotKeysMode)
Vector3 lastSelectedNodesCenterPoint = Vector3(0,0,0); // for Blender mode to avoid own origin rotation when no nodes are selected. preserve last center for this
WeakHandle lastSelectedNode = null;
WeakHandle lastSelectedDrawable = null;
WeakHandle lastSelectedComponent = null;
Component@ coloringComponent = null;
String coloringTypeName;
String coloringPropertyName;
Color coloringOldColor;
float coloringOldScalar;
bool debugRenderDisabled = false;
bool restoreViewport = false;
IntVector2 oldHierarchyWindowPosition; // used for restore hierarchy position when switch between viewport modes
int oldHierarchyWindowHeight;
IntVector2 oldInspectorWindowPosition; // used for restore inspector position when switch between viewport modes
int oldInspectorWindowHeight;

const uint VIEWPORT_BORDER_H     = 0x00000001;
const uint VIEWPORT_BORDER_H1    = 0x00000002;
const uint VIEWPORT_BORDER_H2    = 0x00000004;
const uint VIEWPORT_BORDER_V     = 0x00000010;
const uint VIEWPORT_BORDER_V1    = 0x00000020;
const uint VIEWPORT_BORDER_V2    = 0x00000040;

const uint VIEWPORT_SINGLE       = 0x00000000;
const uint VIEWPORT_COMPACT 	 = 0x00009000;
const uint VIEWPORT_TOP          = 0x00000100;
const uint VIEWPORT_BOTTOM       = 0x00000200;
const uint VIEWPORT_LEFT         = 0x00000400;
const uint VIEWPORT_RIGHT        = 0x00000800;
const uint VIEWPORT_TOP_LEFT     = 0x00001000;
const uint VIEWPORT_TOP_RIGHT    = 0x00002000;
const uint VIEWPORT_BOTTOM_LEFT  = 0x00004000;
const uint VIEWPORT_BOTTOM_RIGHT = 0x00008000;

// Combinations for easier testing
const uint VIEWPORT_BORDER_H_ANY = 0x00000007;
const uint VIEWPORT_BORDER_V_ANY = 0x00000070;
const uint VIEWPORT_SPLIT_H      = 0x0000f300;
const uint VIEWPORT_SPLIT_V      = 0x0000fc00;
const uint VIEWPORT_SPLIT_HV     = 0x0000f000;
const uint VIEWPORT_TOP_ANY      = 0x00003300;
const uint VIEWPORT_BOTTOM_ANY   = 0x0000c200;
const uint VIEWPORT_LEFT_ANY     = 0x00005400;
const uint VIEWPORT_RIGHT_ANY    = 0x0000c800;
const uint VIEWPORT_QUAD         = 0x0000f000;

enum HotKeysMode
{
    HOTKEYS_MODE_STANDARD = 0,
    HOTKEYS_MODE_BLENDER
}

enum EditMode
{
    EDIT_MOVE = 0,
    EDIT_ROTATE,
    EDIT_SCALE,
    EDIT_SELECT,
    EDIT_SPAWN
}

enum AxisMode
{
    AXIS_WORLD = 0,
    AXIS_LOCAL
}

enum SnapScaleMode
{
    SNAP_SCALE_FULL = 0,
    SNAP_SCALE_HALF,
    SNAP_SCALE_QUARTER
}

void ResizeString(String& str, uint newSize)
{
    uint oldSize = str.Length();
    str.Resize(newSize);
    for (uint i = oldSize; i < newSize; ++i)
        str[i] = ' ';
}

// Holds info about a viewport such as camera settings and splits up shared resources
class ViewportContext
{
    float cameraYaw = 0;
    float cameraPitch = 0;
    Camera@ camera;
    Node@ cameraLookAtNode;
    Node@ cameraNode;
    SoundListener@ soundListener;
    Viewport@ viewport;
    bool enabled = false;
    uint index = 0;
    uint viewportId = 0;
    UIElement@ viewportContextUI;
    UIElement@ statusBar;
    Text@ cameraPosText;

    Window@ settingsWindow;
    LineEdit@ cameraPosX;
    LineEdit@ cameraPosY;
    LineEdit@ cameraPosZ;
    LineEdit@ cameraRotX;
    LineEdit@ cameraRotY;
    LineEdit@ cameraRotZ;
    LineEdit@ cameraZoom;
    LineEdit@ cameraOrthoSize;
    CheckBox@ cameraOrthographic;

    ViewportContext(IntRect viewRect, uint index_, uint viewportId_)
    {
        cameraNode = Node();
        cameraLookAtNode = Node();
        cameraLookAtNode.AddChild(cameraNode);        
        camera = cameraNode.CreateComponent("Camera");
        orthoCameraZoom = camera.zoom;
        camera.fillMode = fillMode;
        soundListener = cameraNode.CreateComponent("SoundListener");
        viewport = Viewport(editorScene, camera, viewRect, renderPath);
        index = index_;
        viewportId = viewportId_;
        camera.viewMask = 0xffffffff; // It's easier to only have 1 gizmo active this viewport is shared with the gizmo
    }

    void ResetCamera()
    {
        cameraSmoothInterpolate.Stop();

        cameraLookAtNode.position = Vector3(0, 0, 0);
        cameraLookAtNode.rotation = Quaternion();

        cameraNode.position = Vector3(0, 5, -10);
        // Look at the origin so user can see the scene.
        cameraNode.rotation = Quaternion(Vector3(0, 0, 1), -cameraNode.position);
        ReacquireCameraYawPitch();
        UpdateSettingsUI();
    }

    void ReacquireCameraYawPitch()
    {
        cameraYaw = cameraNode.rotation.yaw;
        cameraPitch = cameraNode.rotation.pitch;
    }

    void CreateViewportContextUI()
    {
        Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");

        viewportContextUI = UIElement();
        viewportUI.AddChild(viewportContextUI);
        viewportContextUI.SetPosition(viewport.rect.left, viewport.rect.top);
        viewportContextUI.SetFixedSize(viewport.rect.width, viewport.rect.height);
        viewportContextUI.clipChildren = true;

        statusBar = BorderImage("ToolBar");
        statusBar.style = "EditorToolBar";
        viewportContextUI.AddChild(statusBar);

        statusBar.SetLayout(LM_HORIZONTAL);
        statusBar.SetAlignment(HA_LEFT, VA_BOTTOM);
        statusBar.layoutSpacing = 4;
        statusBar.opacity = uiMaxOpacity;

        Button@ settingsButton = CreateSmallToolBarButton("Settings");
        statusBar.AddChild(settingsButton);

        cameraPosText = Text();
        statusBar.AddChild(cameraPosText);

        cameraPosText.SetFont(font, 11);
        cameraPosText.color = Color(1, 1, 0);
        cameraPosText.textEffect = TE_SHADOW;
        cameraPosText.priority = -100;

        settingsWindow = LoadEditorUI("UI/EditorViewport.xml");
        settingsWindow.opacity = uiMaxOpacity;
        settingsWindow.visible = false;
        viewportContextUI.AddChild(settingsWindow);

        cameraPosX = settingsWindow.GetChild("PositionX", true);
        cameraPosY = settingsWindow.GetChild("PositionY", true);
        cameraPosZ = settingsWindow.GetChild("PositionZ", true);
        cameraRotX = settingsWindow.GetChild("RotationX", true);
        cameraRotY = settingsWindow.GetChild("RotationY", true);
        cameraRotZ = settingsWindow.GetChild("RotationZ", true);
        cameraOrthographic = settingsWindow.GetChild("Orthographic", true);
        cameraZoom = settingsWindow.GetChild("Zoom", true);
        cameraOrthoSize = settingsWindow.GetChild("OrthoSize", true);

        SubscribeToEvent(cameraPosX, "TextChanged", "HandleSettingsLineEditTextChange");
        SubscribeToEvent(cameraPosY, "TextChanged", "HandleSettingsLineEditTextChange");
        SubscribeToEvent(cameraPosZ, "TextChanged", "HandleSettingsLineEditTextChange");
        SubscribeToEvent(cameraRotX, "TextChanged", "HandleSettingsLineEditTextChange");
        SubscribeToEvent(cameraRotY, "TextChanged", "HandleSettingsLineEditTextChange");
        SubscribeToEvent(cameraRotZ, "TextChanged", "HandleSettingsLineEditTextChange");
        SubscribeToEvent(cameraZoom, "TextChanged", "HandleSettingsLineEditTextChange");
        SubscribeToEvent(cameraOrthoSize, "TextChanged", "HandleSettingsLineEditTextChange");
        SubscribeToEvent(cameraOrthographic, "Toggled", "HandleOrthographicToggled");

        SubscribeToEvent(settingsButton, "Released", "ToggleViewportSettingsWindow");
        SubscribeToEvent(settingsWindow.GetChild("ResetCamera", true), "Released", "ResetCamera");
        SubscribeToEvent(settingsWindow.GetChild("CopyTransform", true), "Released", "HandleCopyTransformClicked");
        SubscribeToEvent(settingsWindow.GetChild("CloseButton", true), "Released", "CloseViewportSettingsWindow");
        SubscribeToEvent(settingsWindow.GetChild("Refresh", true), "Released", "UpdateSettingsUI");
        HandleResize();
    }

    void HandleResize()
    {
        viewportContextUI.SetPosition(viewport.rect.left, viewport.rect.top);
        viewportContextUI.SetFixedSize(viewport.rect.width, viewport.rect.height);
        if (viewport.rect.left < 34)
        {
            statusBar.layoutBorder = IntRect(34 - viewport.rect.left, 4, 4, 8);
            IntVector2 pos = settingsWindow.position;
            pos.x = 32 - viewport.rect.left;
            settingsWindow.position = pos;
        }
        else
        {
            statusBar.layoutBorder = IntRect(8, 4, 4, 8);
            IntVector2 pos = settingsWindow.position;
            pos.x = 5;
            settingsWindow.position = pos;
        }

        statusBar.SetFixedSize(viewport.rect.width, 22);
    }

    void ToggleOrthographic()
    {
        SetOrthographic(!camera.orthographic);
    }

    void SetOrthographic(bool orthographic)
    {
        camera.orthographic = orthographic;
        if (camera.orthographic)
            camera.zoom = orthoCameraZoom;
        else
            camera.zoom = 1.0f;
            
        UpdateSettingsUI();
    }

    void Update(float timeStep)
    {
        // Update camera smooth move
        if (cameraSmoothInterpolate.IsRunning())
        {
            cameraSmoothInterpolate.Update(timeStep);
        }

        Vector3 cameraPos = cameraNode.position;
        String xText(cameraPos.x);
        String yText(cameraPos.y);
        String zText(cameraPos.z);
        ResizeString(xText, 8);
        ResizeString(yText, 8);
        ResizeString(zText, 8);

        cameraPosText.text = String(
            "Pos: " + xText + " " + yText + " " + zText +
            " Zoom: " + camera.zoom);

        cameraPosText.size = cameraPosText.minSize;
    }

    void ToggleViewportSettingsWindow()
    {
        if (settingsWindow.visible)
            CloseViewportSettingsWindow();
        else
            OpenViewportSettingsWindow();
    }

    void OpenViewportSettingsWindow()
    {
        UpdateSettingsUI();
        /* settingsWindow.position = */
        settingsWindow.visible = true;
        settingsWindow.BringToFront();
    }

    void CloseViewportSettingsWindow()
    {
        settingsWindow.visible = false;
    }

    void UpdateSettingsUI()
    {
        cameraPosX.text = String(Floor(cameraNode.position.x * 1000) / 1000);
        cameraPosY.text = String(Floor(cameraNode.position.y * 1000) / 1000);
        cameraPosZ.text = String(Floor(cameraNode.position.z * 1000) / 1000);
        cameraRotX.text = String(Floor(cameraNode.rotation.pitch * 1000) / 1000);
        cameraRotY.text = String(Floor(cameraNode.rotation.yaw * 1000) / 1000);
        cameraRotZ.text = String(Floor(cameraNode.rotation.roll * 1000) / 1000);
        cameraZoom.text = String(Floor(camera.zoom * 1000) / 1000);
        cameraOrthoSize.text = String(Floor(camera.orthoSize * 1000) / 1000);
        // FIXME: this line below appears to be not only redundant but may cause infinite loop as well on Clang build
        // cameraOrthographic.checked = camera.orthographic;
    }

    void HandleOrthographicToggled(StringHash eventType, VariantMap& eventData)
    {
        SetOrthographic(cameraOrthographic.checked);
    }

    void HandleSettingsLineEditTextChange(StringHash eventType, VariantMap& eventData)
    {
        LineEdit@ element = eventData["Element"].GetPtr();
        if (element.text == "")
            return;

        if (element is cameraRotX ||  element is cameraRotY || element is cameraRotZ)
        {
            Vector3 euler = cameraNode.rotation.eulerAngles;
            if (element is cameraRotX)
                euler.x = element.text.ToFloat();
            else if (element is cameraRotY)
                euler.y = element.text.ToFloat();
            else if (element is cameraRotZ)
                euler.z = element.text.ToFloat();

            cameraNode.rotation = Quaternion(euler);
        }
        else if (element is cameraPosX ||  element is cameraPosY || element is cameraPosZ)
        {
            Vector3 pos = cameraNode.position;
            if (element is cameraPosX)
                pos.x = element.text.ToFloat();
            else if (element is cameraPosY)
                pos.y = element.text.ToFloat();
            else if (element is cameraPosZ)
                pos.z = element.text.ToFloat();

            cameraNode.position = pos;
        }
        else if (element is cameraZoom)
            camera.zoom = element.text.ToFloat();
        else if (element is cameraOrthoSize)
            camera.orthoSize = element.text.ToFloat();
    }
    void HandleCopyTransformClicked(StringHash eventType, VariantMap& eventData)
    {
        if (editNode !is null)
        {
            editNode.position = cameraNode.position;
            editNode.rotation = cameraNode.rotation;
        }
    }
}

Array<ViewportContext@> viewports;
ViewportContext@ activeViewport;

Text@ editorModeText;
Text@ renderStatsText;
Text@ modelInfoText;

EditMode editMode = EDIT_MOVE;
AxisMode axisMode = AXIS_WORLD;
FillMode fillMode = FILL_SOLID;
SnapScaleMode snapScaleMode = SNAP_SCALE_FULL;

float viewNearClip = 0.1;
float viewFarClip = 1000.0;
float viewFov = 45.0;


float cameraBaseSpeed = 3;
float cameraBaseRotationSpeed = 0.2;
float cameraShiftSpeedMultiplier = 5;
float moveStep = 0.5;
float rotateStep = 5;
float scaleStep = 0.1;
float snapScale = 1.0;
bool limitRotation = false;
bool moveSnap = false;
bool rotateSnap = false;
bool scaleSnap = false;
bool renderingDebug = false;
bool physicsDebug = false;
bool octreeDebug = false;
bool navigationDebug = false;
int pickMode = PICK_GEOMETRIES;
bool orbiting = false;

enum MouseOrbitMode
{
    ORBIT_RELATIVE = 0,
    ORBIT_WRAP
}

bool toggledMouseLock = false;
int mouseOrbitMode = ORBIT_RELATIVE;
bool mmbPanMode = false;
bool rotateAroundSelect = false;

enum NewNodeMode
{
    NEW_NODE_CAMERA_LOOKAT = 0,
    NEW_NODE_IN_CENTER,
    NEW_NODE_RAYCAST
}

int newNodeMode = NEW_NODE_CAMERA_LOOKAT;

bool showGrid = true;
bool grid2DMode = false;
uint gridSize = 16;
uint gridSubdivisions = 3;
float gridScale = 8.0;
Color gridColor(0.1, 0.1, 0.1);
Color gridSubdivisionColor(0.05, 0.05, 0.05);
Color gridXColor(0.5, 0.1, 0.1);
Color gridYColor(0.1, 0.5, 0.1);
Color gridZColor(0.1, 0.1, 0.5);

Array<int> pickModeDrawableFlags = {
    DRAWABLE_GEOMETRY,
    DRAWABLE_LIGHT,
    DRAWABLE_ZONE
};

Array<String> editModeText = {
    "Move",
    "Rotate",
    "Scale",
    "Select",
    "Spawn"
};

Array<String> axisModeText = {
    "World",
    "Local"
};

Array<String> pickModeText = {
    "Geometries",
    "Lights",
    "Zones",
    "Rigidbodies",
    "UI-elements"
};

Array<String> fillModeText = {
    "Solid",
    "Wire",
    "Point"
};

// This class provides smooth translation/rotation/zoom interpolation for the editor camera
class CameraSmoothInterpolate
{
    Vector3 lookAtNodeBeginPos;
    Vector3 cameraNodeBeginPos;
    
    Vector3 lookAtNodeEndPos;
    Vector3 cameraNodeEndPos;

    Quaternion cameraNodeBeginRot;
    Quaternion cameraNodeEndRot;

    float cameraBeginZoom;
    float cameraEndZoom;
    
    bool isRunning = false;
    float duration = 0.0f;
    float elapsedTime = 0.0f;

    bool interpLookAtNodePos = false;
    bool interpCameraNodePos = false;
    bool interpCameraRot = false;
    bool interpCameraZoom = false;

    CameraSmoothInterpolate()
    {
    }

    void SetLookAtNodePosition(Vector3 lookAtBeginPos, Vector3 lookAtEndPos)
    {
        lookAtNodeBeginPos = lookAtBeginPos;
        lookAtNodeEndPos = lookAtEndPos;
        interpLookAtNodePos = true;
    }

    void SetCameraNodePosition(Vector3 cameraBeginPos, Vector3 cameraEndPos)
    {
        cameraNodeBeginPos = cameraBeginPos;
        cameraNodeEndPos = cameraEndPos;
        interpCameraNodePos = true;
    }

    void SetCameraNodeRotation(Quaternion cameraBeginRot, Quaternion cameraEndRot)
    {
        cameraNodeBeginRot = cameraBeginRot;
        cameraNodeEndRot = cameraEndRot;
        interpCameraRot = true;
    }

    void SetCameraZoom(float beginZoom, float endZoom)
    {
        cameraBeginZoom = beginZoom;
        cameraEndZoom = endZoom;
        interpCameraZoom = true;
    }

    void Start(float duration_)
    {
        if (cameraLookAtNode is null || cameraNode is null || camera is null)
            return;

        duration = duration_;
        elapsedTime = 0.0f;
        isRunning = true;
    }

    void Stop()
    {
        interpLookAtNodePos = false;
        interpCameraNodePos = false;
        interpCameraRot = false;
        interpCameraZoom = false;

        isRunning = false;
    }

    void Finish()
    {
        if (!isRunning)
            return;

        if (cameraLookAtNode is null || cameraNode is null || camera is null)
            return;

        if (interpLookAtNodePos)
            cameraLookAtNode.worldPosition = lookAtNodeEndPos;
        
        if (interpCameraNodePos)
            cameraNode.position = cameraNodeEndPos;

        if (interpCameraRot)
        {
            cameraNode.rotation = cameraNodeEndRot;
            ReacquireCameraYawPitch();
        }

        if (interpCameraZoom)
        {
            orthoCameraZoom = cameraEndZoom;
            camera.zoom = cameraEndZoom;
        }

        interpLookAtNodePos = false;
        interpCameraNodePos = false;
        interpCameraRot = false;
        interpCameraZoom = false;

        isRunning = false;
    }

    bool IsRunning() const
    {
        return isRunning;
    }

    // Cubic easing out
    // http://robertpenner.com/easing/
    float EaseOut(float t, float b , float c, float d) 
    {
        return c * ((t = t / d - 1) * t * t + 1) + b;
    }

    void Update(float timeStep)
    {
        if (!isRunning)
            return;

        if (cameraLookAtNode is null || cameraNode is null || camera is null)
            return;

        elapsedTime += timeStep;
    
        if (elapsedTime <= duration)
        {
            float factor = EaseOut(elapsedTime, 0.0f, 1.0f, duration);

            if (interpLookAtNodePos)
                cameraLookAtNode.worldPosition = lookAtNodeBeginPos + (lookAtNodeEndPos - lookAtNodeBeginPos) * factor;
            
            if (interpCameraNodePos)
                cameraNode.position = cameraNodeBeginPos + (cameraNodeEndPos - cameraNodeBeginPos) * factor;

            if (interpCameraRot)
            {
                cameraNode.rotation = cameraNodeBeginRot.Slerp(cameraNodeEndRot, factor);
                ReacquireCameraYawPitch();
            }

            if (interpCameraZoom)
            {
                orthoCameraZoom = cameraBeginZoom + (cameraEndZoom - cameraBeginZoom) * factor;
                camera.zoom = orthoCameraZoom;
            }
        }
        else
        {
            Finish();
        }
    }
}


CameraSmoothInterpolate cameraSmoothInterpolate; // Camera smooth interpolation control

void SetRenderPath(const String&in newRenderPathName)
{
    renderPath = null;
    renderPathName = newRenderPathName.Trimmed();

    if (renderPathName.length > 0)
    {
        File@ file = cache.GetFile(renderPathName);
        if (file !is null)
        {
            XMLFile@ xml = XMLFile();
            if (xml.Load(file))
            {
                renderPath = RenderPath();
                if (!renderPath.Load(xml))
                    renderPath = null;
            }
        }
    }

    if (renderPath is null)
        renderPath = renderer.defaultRenderPath.Clone();

    // Append gamma correction postprocess and disable/enable it as requested
    renderPath.Append(cache.GetResource("XMLFile", "PostProcess/GammaCorrection.xml"));
    renderPath.SetEnabled("GammaCorrection", gammaCorrection);

    renderer.hdrRendering = HDR;

    for (uint i = 0; i < renderer.numViewports; ++i)
        renderer.viewports[i].renderPath = renderPath;

    if (materialPreview !is null && materialPreview.viewport !is null)
        materialPreview.viewport.renderPath = renderPath;

    if (particleEffectPreview !is null && particleEffectPreview.viewport !is null)
        particleEffectPreview.viewport.renderPath = renderPath;
}

void SetGammaCorrection(bool enable)
{
    gammaCorrection = enable;
    if (renderPath !is null)
        renderPath.SetEnabled("GammaCorrection", gammaCorrection);
}

void SetHDR(bool enable)
{
    HDR = enable;
    if (renderer !is null)
        renderer.hdrRendering = HDR;
}

void CreateCamera()
{
    // Set the initial viewport rect
    viewportArea = IntRect(0, 0, graphics.width, graphics.height);

    // Set viewport single to store default hierarchy/inspector height/positions
    if(viewportMode == VIEWPORT_COMPACT)
    {
        SetViewportMode(VIEWPORT_SINGLE);
        SetViewportMode(VIEWPORT_COMPACT);
    }
    else
    {
        SetViewportMode(viewportMode);
    }

    SetActiveViewport(viewports[0]);

    // Note: the camera is not inside the scene, so that it is not listed, and does not get deleted
    ResetCamera();

    // Set initial renderpath if defined
    SetRenderPath(renderPathName);
}

// Create any UI associated with changing the editor viewports
void CreateViewportUI()
{
    if (viewportUI is null)
    {
        viewportUI = UIElement();
        ui.root.AddChild(viewportUI);
    }

    viewportUI.SetFixedSize(viewportArea.width, viewportArea.height);
    viewportUI.position = IntVector2(viewportArea.top, viewportArea.left);
    viewportUI.clipChildren = true;
    viewportUI.clipBorder = viewportUIClipBorder;
    viewportUI.RemoveAllChildren();
    viewportUI.priority = -2000;

    Array<BorderImage@> borders;

    IntRect top;
    IntRect bottom;
    IntRect left;
    IntRect right;
    IntRect topLeft;
    IntRect topRight;
    IntRect bottomLeft;
    IntRect bottomRight;

    for (uint i = 0; i < viewports.length; ++i)
    {
        ViewportContext@ vc = viewports[i];
        vc.CreateViewportContextUI();

        if (vc.viewportId & VIEWPORT_TOP > 0)
            top = vc.viewport.rect;
        else if (vc.viewportId & VIEWPORT_BOTTOM > 0)
            bottom = vc.viewport.rect;
        else if (vc.viewportId & VIEWPORT_LEFT > 0)
            left = vc.viewport.rect;
        else if (vc.viewportId & VIEWPORT_RIGHT > 0)
            right = vc.viewport.rect;
        else if (vc.viewportId & VIEWPORT_TOP_LEFT > 0)
            topLeft = vc.viewport.rect;
        else if (vc.viewportId & VIEWPORT_TOP_RIGHT > 0)
            topRight = vc.viewport.rect;
        else if (vc.viewportId & VIEWPORT_BOTTOM_LEFT > 0)
            bottomLeft = vc.viewport.rect;
        else if (vc.viewportId & VIEWPORT_BOTTOM_RIGHT > 0)
            bottomRight = vc.viewport.rect;
    }

    // Creates resize borders based on the mode set
    if (viewportMode == VIEWPORT_QUAD) // independent borders for quad isn't easy
    {
        borders.Push(CreateViewportDragBorder(VIEWPORT_BORDER_V, topLeft.right - viewportBorderOffset, topLeft.top, viewportBorderWidth, viewportArea.height));
        borders.Push(CreateViewportDragBorder(VIEWPORT_BORDER_H, topLeft.left, topLeft.bottom-viewportBorderOffset, viewportArea.width, viewportBorderWidth));
    }
    else
    {
        // Figures what borders to create based on mode
        if (viewportMode & (VIEWPORT_LEFT|VIEWPORT_RIGHT) > 0)
        {
            borders.Push(
                viewportMode & VIEWPORT_LEFT > 0 ?
                    CreateViewportDragBorder(VIEWPORT_BORDER_V, left.right-viewportBorderOffset, left.top, viewportBorderWidth, left.height) :
                    CreateViewportDragBorder(VIEWPORT_BORDER_V, right.left-viewportBorderOffset, right.top, viewportBorderWidth, right.height)
                );
        }
        else
        {
            if (viewportMode & (VIEWPORT_TOP_LEFT|VIEWPORT_TOP_RIGHT) > 0)
                borders.Push(CreateViewportDragBorder(VIEWPORT_BORDER_V1, topLeft.right-viewportBorderOffset, topLeft.top, viewportBorderWidth, topLeft.height));
            if (viewportMode & (VIEWPORT_BOTTOM_LEFT|VIEWPORT_BOTTOM_RIGHT) > 0)
                borders.Push(CreateViewportDragBorder(VIEWPORT_BORDER_V2, bottomLeft.right-viewportBorderOffset, bottomLeft.top, viewportBorderWidth, bottomLeft.height));
        }

        if (viewportMode & (VIEWPORT_TOP|VIEWPORT_BOTTOM) > 0)
        {
            borders.Push(
                viewportMode & VIEWPORT_TOP > 0 ?
                    CreateViewportDragBorder(VIEWPORT_BORDER_H, top.left, top.bottom-viewportBorderOffset, top.width, viewportBorderWidth) :
                    CreateViewportDragBorder(VIEWPORT_BORDER_H, bottom.left, bottom.top-viewportBorderOffset, bottom.width, viewportBorderWidth)
                );
        }
        else
        {
            if (viewportMode & (VIEWPORT_TOP_LEFT|VIEWPORT_BOTTOM_LEFT) > 0)
                borders.Push(CreateViewportDragBorder(VIEWPORT_BORDER_H1, topLeft.left, topLeft.bottom-viewportBorderOffset, topLeft.width, viewportBorderWidth));
            if (viewportMode & (VIEWPORT_TOP_RIGHT|VIEWPORT_BOTTOM_RIGHT) > 0)
                borders.Push(CreateViewportDragBorder(VIEWPORT_BORDER_H2, topRight.left, topRight.bottom-viewportBorderOffset, topRight.width, viewportBorderWidth));
        }
    }
}

BorderImage@ CreateViewportDragBorder(uint value, int posX, int posY, int sizeX, int sizeY)
{
    BorderImage@ border = BorderImage();
    viewportUI.AddChild(border);
    border.name = "border";
    border.style = "ViewportBorder";
    border.vars["VIEWMODE"] = value;
    border.SetFixedSize(sizeX, sizeY); // relevant size gets set by viewport later
    border.position = IntVector2(posX, posY);
    border.opacity = uiMaxOpacity;
    SubscribeToEvent(border, "DragMove", "HandleViewportBorderDragMove");
    SubscribeToEvent(border, "DragEnd", "HandleViewportBorderDragEnd");
    return border;
}

void SetFillMode(FillMode fillMode_)
{
    fillMode = fillMode_;
    for (uint i = 0; i < viewports.length; ++i)
        viewports[i].camera.fillMode = fillMode_;
}

// Sets the viewport mode
void SetViewportMode(uint mode = VIEWPORT_SINGLE)
{
    // Remember old viewport positions
    Array<Vector3> cameralookAtPositions;
    Array<Quaternion> cameraLookAtRotations;
    Array<Vector3> cameraPositions;
    Array<Quaternion> cameraRotations;
    for (uint i = 0; i < viewports.length; ++i)
    {
        cameralookAtPositions.Push(viewports[i].cameraLookAtNode.position);
        cameraLookAtRotations.Push(viewports[i].cameraLookAtNode.rotation);

        cameraPositions.Push(viewports[i].cameraNode.position);
        cameraRotations.Push(viewports[i].cameraNode.rotation);
    }

    viewports.Clear();

    if(mode == VIEWPORT_COMPACT)
    {
        // Remember old hierarchy/inspector height/positions
        if(viewportMode != VIEWPORT_COMPACT){
            restoreViewport = true;
            oldHierarchyWindowPosition = hierarchyWindow.position;
            oldHierarchyWindowHeight = hierarchyWindow.height;
            oldInspectorWindowPosition = attributeInspectorWindow.position;
            oldInspectorWindowHeight = attributeInspectorWindow.height;
        }

        // Move and scale hierarchy window to left of screen
        ShowHierarchyWindow();
        hierarchyWindow.position = IntVector2(secondaryToolBar.width,toolBar.height + uiMenuBar.height);
        hierarchyWindow.height = viewportArea.height-(toolBar.height + uiMenuBar.height);

        // Move and scale inspector window to left of screen
        ShowAttributeInspectorWindow();
        attributeInspectorWindow.position = IntVector2(viewportArea.width-attributeInspectorWindow.width,toolBar.height + uiMenuBar.height);
        attributeInspectorWindow.height = viewportArea.height-(toolBar.height + uiMenuBar.height);

        // Hide close button and disable resize/movement inspector/hierarchy of windows
        attributeInspectorWindow.GetChild("CloseButton",true).visible = false;
        attributeInspectorWindow.resizable = false;
        attributeInspectorWindow.movable = false;
        hierarchyWindow.GetChild("CloseButton",true).visible = false;
        hierarchyWindow.resizable = false;
        hierarchyWindow.movable = false;

        // Create viewport on center of window
        {
            uint viewport = 0;
            ViewportContext@ vc = ViewportContext(
                IntRect(
                    secondaryToolBar.width + hierarchyWindow.width,
                    toolBar.height + uiMenuBar.height,
                    viewportArea.width-attributeInspectorWindow.width,
                    viewportArea.height),
                viewports.length + 1,
                viewportMode & (VIEWPORT_TOP|VIEWPORT_LEFT|VIEWPORT_TOP_LEFT)
            );
            viewports.Push(vc);
        }
        viewportMode = mode;

    }
    else
    {
        if(viewportMode == VIEWPORT_COMPACT)
        {
            // Restore hierarchy/inspector windows height/positions
            if(restoreViewport)
            {
                hierarchyWindow.position = oldHierarchyWindowPosition;
                hierarchyWindow.height = oldHierarchyWindowHeight;
                attributeInspectorWindow.position = oldInspectorWindowPosition;
                attributeInspectorWindow.height = oldInspectorWindowHeight;
            }

            // Show close button and enable resize/movement of inspector/hierarchy windows
            attributeInspectorWindow.GetChild("CloseButton",true).visible = true;
            attributeInspectorWindow.resizable = true;
            attributeInspectorWindow.movable = true;
            hierarchyWindow.GetChild("CloseButton",true).visible = true;
            hierarchyWindow.resizable = true;
            hierarchyWindow.movable = true;
        }

        viewportMode = mode;

        // Always have quad a
        {
            uint viewport = 0;
            ViewportContext@ vc = ViewportContext(
                IntRect(
                    0,
                    0,
                    mode & (VIEWPORT_LEFT|VIEWPORT_TOP_LEFT) > 0 ? viewportArea.width / 2 : viewportArea.width,
                    mode & (VIEWPORT_TOP|VIEWPORT_TOP_LEFT) > 0 ? viewportArea.height / 2 : viewportArea.height),
                viewports.length + 1,
                viewportMode & (VIEWPORT_TOP|VIEWPORT_LEFT|VIEWPORT_TOP_LEFT)
            );
            viewports.Push(vc);
        }

        uint topRight = viewportMode & (VIEWPORT_RIGHT|VIEWPORT_TOP_RIGHT);
        if (topRight > 0)
        {
            ViewportContext@ vc = ViewportContext(
                IntRect(
                    viewportArea.width/2,
                    0,
                    viewportArea.width,
                    mode & VIEWPORT_TOP_RIGHT > 0 ? viewportArea.height / 2 : viewportArea.height),
                viewports.length + 1,
                topRight
            );
            viewports.Push(vc);
        }

        uint bottomLeft = viewportMode & (VIEWPORT_BOTTOM|VIEWPORT_BOTTOM_LEFT);
        if (bottomLeft > 0)
        {
            ViewportContext@ vc = ViewportContext(
                IntRect(
                    0,
                    viewportArea.height / 2,
                    mode & (VIEWPORT_BOTTOM_LEFT) > 0 ? viewportArea.width / 2 : viewportArea.width,
                    viewportArea.height),
                viewports.length + 1,
                bottomLeft
            );
            viewports.Push(vc);
        }

        uint bottomRight = viewportMode & (VIEWPORT_BOTTOM_RIGHT);
        if (bottomRight > 0)
        {
            ViewportContext@ vc = ViewportContext(
                IntRect(
                    viewportArea.width / 2,
                    viewportArea.height / 2,
                    viewportArea.width,
                    viewportArea.height),
                viewports.length + 1,
                bottomRight
            );
            viewports.Push(vc);
        }

    }

    renderer.numViewports = viewports.length;
    for (uint i = 0; i < viewports.length; ++i)
        renderer.viewports[i] = viewports[i].viewport;

    // Restore camera positions as applicable. Default new viewports to the last camera position
    if (cameraPositions.length > 0)
    {
        for (uint i = 0; i < viewports.length; ++i)
        {
            uint src = i;
            if (src >= cameraPositions.length)
                src = cameraPositions.length - 1;

            viewports[i].cameraLookAtNode.position = cameralookAtPositions[src];
            viewports[i].cameraLookAtNode.rotation = cameraLookAtRotations[src];

            viewports[i].cameraNode.position = cameraPositions[src];
            viewports[i].cameraNode.rotation = cameraRotations[src];
        }
    }

    ReacquireCameraYawPitch();
    UpdateViewParameters();
    UpdateCameraPreview();
    CreateViewportUI();
}

// Create a preview viewport if a camera component is selected
void UpdateCameraPreview()
{
    previewCamera = null;
    StringHash cameraType("Camera");

    for (uint i = 0; i < selectedComponents.length; ++i)
    {
        if (selectedComponents[i].type == cameraType)
        {
            // Take the first encountered camera
            previewCamera = selectedComponents[i];
            break;
        }
    }
    // Also try nodes if not found from components
    if (previewCamera.Get() is null)
    {
        for (uint i = 0; i < selectedNodes.length; ++i)
        {
            previewCamera = selectedNodes[i].GetComponent("Camera");
            if (previewCamera.Get() !is null)
                break;
        }
    }

    // Remove extra viewport if it exists and no camera is selected
    if (previewCamera.Get() is null)
    {
        if (renderer.numViewports > viewports.length)
            renderer.numViewports = viewports.length;
    }
    else
    {
        if (renderer.numViewports < viewports.length + 1)
            renderer.numViewports = viewports.length + 1;

        int previewWidth = graphics.width / 4;
        int previewHeight = previewWidth * 9 / 16;
        int previewX = graphics.width - 10 - previewWidth;
        int previewY = graphics.height - 30 - previewHeight;

        Viewport@ previewView = Viewport();
        previewView.scene = editorScene;
        previewView.camera = previewCamera.Get();
        previewView.rect = IntRect(previewX, previewY, previewX + previewWidth, previewY + previewHeight);
        previewView.renderPath = renderPath;
        renderer.viewports[viewports.length] = previewView;
    }
}

void HandleViewportBorderDragMove(StringHash eventType, VariantMap& eventData)
{
    UIElement@ dragBorder = eventData["Element"].GetPtr();
    if (dragBorder is null)
        return;

    uint hPos;
    uint vPos;

    // Moves border to new cursor position, restricts motion to 1 axis, and keeps borders within view area
    if (resizingBorder & VIEWPORT_BORDER_V_ANY > 0)
    {
        hPos = Clamp(ui.cursorPosition.x, 150, viewportArea.width-150);
        vPos = dragBorder.position.y;
        dragBorder.position = IntVector2(hPos, vPos);
    }
    if (resizingBorder & VIEWPORT_BORDER_H_ANY > 0)
    {
        vPos = Clamp(ui.cursorPosition.y, 150, viewportArea.height-150);
        hPos = dragBorder.position.x;
        dragBorder.position = IntVector2(hPos, vPos);
    }

    // Move all dependent borders
    Array<UIElement@> borders = viewportUI.GetChildren();
    for (uint i = 0; i < borders.length; ++i)
    {
        BorderImage@ border = borders[i];
        if (border is null || border is dragBorder || border.name != "border")
            continue;

        uint borderViewMode = border.vars["VIEWMODE"].GetUInt();
        if (resizingBorder == VIEWPORT_BORDER_H)
        {
            if (borderViewMode == VIEWPORT_BORDER_V1)
            {
                border.SetFixedHeight(vPos);
            }
            else if (borderViewMode == VIEWPORT_BORDER_V2)
            {
                border.position = IntVector2(border.position.x, vPos);
                border.SetFixedHeight(viewportArea.height - vPos);
            }
        }
        else if (resizingBorder == VIEWPORT_BORDER_V)
        {
            if (borderViewMode == VIEWPORT_BORDER_H1)
            {
                border.SetFixedWidth(hPos);
            }
            else if (borderViewMode == VIEWPORT_BORDER_H2)
            {
                border.position = IntVector2(hPos, border.position.y);
                border.SetFixedWidth(viewportArea.width - hPos);
            }
        }
    }
}

void HandleViewportBorderDragEnd(StringHash eventType, VariantMap& eventData)
{
    // Sets the new viewports by checking all the dependencies
    Array<UIElement@> children = viewportUI.GetChildren();
    Array<BorderImage@> borders;

    BorderImage@ borderV;
    BorderImage@ borderV1;
    BorderImage@ borderV2;
    BorderImage@ borderH;
    BorderImage@ borderH1;
    BorderImage@ borderH2;

    for (uint i = 0; i < children.length; ++i)
    {
        if (children[i].name == "border")
        {
            BorderImage@ border = children[i];
            uint mode = border.vars["VIEWMODE"].GetUInt();
            if (mode == VIEWPORT_BORDER_V)
                borderV = border;
            else if (mode == VIEWPORT_BORDER_V1)
                borderV1 = border;
            else if (mode == VIEWPORT_BORDER_V2)
                borderV2 = border;
            else if (mode == VIEWPORT_BORDER_H)
                borderH = border;
            else if (mode == VIEWPORT_BORDER_H1)
                borderH1 = border;
            else if (mode == VIEWPORT_BORDER_H2)
                borderH2 = border;
        }
    }

    IntRect top;
    IntRect bottom;
    IntRect left;
    IntRect right;
    IntRect topLeft;
    IntRect topRight;
    IntRect bottomLeft;
    IntRect bottomRight;

    for (uint i = 0; i < viewports.length; ++i)
    {
        ViewportContext@ vc = viewports[i];
        if (vc.viewportId & VIEWPORT_TOP > 0)
            top = vc.viewport.rect;
        else if (vc.viewportId & VIEWPORT_BOTTOM > 0)
            bottom = vc.viewport.rect;
        else if (vc.viewportId & VIEWPORT_LEFT > 0)
            left = vc.viewport.rect;
        else if (vc.viewportId & VIEWPORT_RIGHT > 0)
            right = vc.viewport.rect;
        else if (vc.viewportId & VIEWPORT_TOP_LEFT > 0)
            topLeft = vc.viewport.rect;
        else if (vc.viewportId & VIEWPORT_TOP_RIGHT > 0)
            topRight = vc.viewport.rect;
        else if (vc.viewportId & VIEWPORT_BOTTOM_LEFT > 0)
            bottomLeft = vc.viewport.rect;
        else if (vc.viewportId & VIEWPORT_BOTTOM_RIGHT > 0)
            bottomRight = vc.viewport.rect;
    }

    if (borderV !is null)
    {
        if (viewportMode & VIEWPORT_LEFT > 0)
            left.right = borderV.position.x + viewportBorderOffset;
        if (viewportMode & VIEWPORT_TOP_LEFT > 0)
            topLeft.right = borderV.position.x + viewportBorderOffset;
        if (viewportMode & VIEWPORT_TOP_RIGHT > 0)
            topRight.left = borderV.position.x + viewportBorderOffset;
        if (viewportMode & VIEWPORT_RIGHT > 0)
            right.left = borderV.position.x + viewportBorderOffset;
        if (viewportMode & VIEWPORT_BOTTOM_LEFT > 0)
            bottomLeft.right = borderV.position.x + viewportBorderOffset;
        if (viewportMode & VIEWPORT_BOTTOM_RIGHT > 0)
            bottomRight.left = borderV.position.x + viewportBorderOffset;
    }
    else
    {
        if (borderV1 !is null)
        {
            if (viewportMode & VIEWPORT_TOP_LEFT > 0)
                topLeft.right = borderV1.position.x + viewportBorderOffset;
            if (viewportMode & VIEWPORT_TOP_RIGHT > 0)
                topRight.left = borderV1.position.x + viewportBorderOffset;
        }
        if (borderV2 !is null)
        {
            if (viewportMode & VIEWPORT_BOTTOM_LEFT > 0)
                bottomLeft.right = borderV2.position.x + viewportBorderOffset;
            if (viewportMode & VIEWPORT_BOTTOM_RIGHT > 0)
                bottomRight.left = borderV2.position.x + viewportBorderOffset;
        }
    }

    if (borderH !is null)
    {
        if (viewportMode & VIEWPORT_TOP > 0)
            top.bottom = borderH.position.y + viewportBorderOffset;
        if (viewportMode & VIEWPORT_TOP_LEFT > 0)
            topLeft.bottom = borderH.position.y + viewportBorderOffset;
        if (viewportMode & VIEWPORT_BOTTOM_LEFT > 0)
            bottomLeft.top = borderH.position.y + viewportBorderOffset;
        if (viewportMode & VIEWPORT_BOTTOM > 0)
            bottom.top = borderH.position.y + viewportBorderOffset;
        if (viewportMode & VIEWPORT_TOP_RIGHT > 0)
            topRight.bottom = borderH.position.y + viewportBorderOffset;
        if (viewportMode & VIEWPORT_BOTTOM_RIGHT > 0)
            bottomRight.top = borderH.position.y + viewportBorderOffset;
    }
    else
    {
        if (borderH1 !is null)
        {
            if (viewportMode & VIEWPORT_TOP_LEFT > 0)
                topLeft.bottom = borderH1.position.y+viewportBorderOffset;
            if (viewportMode & VIEWPORT_BOTTOM_LEFT > 0)
                bottomLeft.top = borderH1.position.y+viewportBorderOffset;
        }
        if (borderH2 !is null)
        {
            if (viewportMode & VIEWPORT_TOP_RIGHT > 0)
                topRight.bottom = borderH2.position.y+viewportBorderOffset;
            if (viewportMode & VIEWPORT_BOTTOM_RIGHT > 0)
                bottomRight.top = borderH2.position.y+viewportBorderOffset;
        }
    }

    // Applies the calculated changes
    for (uint i = 0; i < viewports.length; ++i)
    {
        ViewportContext@ vc = viewports[i];
        if (vc.viewportId & VIEWPORT_TOP > 0)
            vc.viewport.rect = top;
        else if (vc.viewportId & VIEWPORT_BOTTOM > 0)
            vc.viewport.rect = bottom;
        else if (vc.viewportId & VIEWPORT_LEFT > 0)
            vc.viewport.rect = left;
        else if (vc.viewportId & VIEWPORT_RIGHT > 0)
            vc.viewport.rect = right;
        else if (vc.viewportId & VIEWPORT_TOP_LEFT > 0)
            vc.viewport.rect = topLeft;
        else if (vc.viewportId & VIEWPORT_TOP_RIGHT > 0)
            vc.viewport.rect = topRight;
        else if (vc.viewportId & VIEWPORT_BOTTOM_LEFT > 0)
            vc.viewport.rect = bottomLeft;
        else if (vc.viewportId & VIEWPORT_BOTTOM_RIGHT > 0)
            vc.viewport.rect = bottomRight;
        vc.HandleResize();
    }

    // End drag state
    resizingBorder = 0;
    setViewportCursor = 0;
}

void SetViewportCursor()
{
    if (setViewportCursor & VIEWPORT_BORDER_V_ANY > 0)
        ui.cursor.shape = CS_RESIZEHORIZONTAL;
    else if (setViewportCursor & VIEWPORT_BORDER_H_ANY > 0)
        ui.cursor.shape = CS_RESIZEVERTICAL;
}

void SetActiveViewport(ViewportContext@ context)
{
    // Sets the global variables to the current context
    @cameraLookAtNode = context.cameraLookAtNode;
    @cameraNode = context.cameraNode;
    @camera = context.camera;
    @audio.listener = context.soundListener;

    // Camera is created before gizmo, this gets called again after UI is created
    if (gizmo !is null)
        gizmo.viewMask = camera.viewMask;

    @activeViewport = context;

    // If a mode is changed while in a drag or hovering over a border these can get out of sync
    resizingBorder = 0;
    setViewportCursor = 0;
}

void ResetCamera()
{
    for (uint i = 0; i < viewports.length; ++i)
        viewports[i].ResetCamera();
}

void ReacquireCameraYawPitch()
{
    for (uint i = 0; i < viewports.length; ++i)
        viewports[i].ReacquireCameraYawPitch();
}

void UpdateViewParameters()
{
    for (uint i = 0; i < viewports.length; ++i)
    {
        viewports[i].camera.nearClip = viewNearClip;
        viewports[i].camera.farClip = viewFarClip;
        viewports[i].camera.fov = viewFov;
    }
}

void CreateGrid()
{
    if (gridNode !is null)
        gridNode.Remove();

    gridNode = Node();
    gridNode.name = "EditorGrid";
    grid = gridNode.CreateComponent("CustomGeometry");
    grid.numGeometries = 1;
    grid.material = cache.GetResource("Material", "Materials/VColUnlit.xml");
    grid.viewMask = 0x80000000; // Editor raycasts use viewmask 0x7fffffff
    grid.occludee = false;

    UpdateGrid();
}

void HideGrid()
{
    if (grid !is null)
        grid.enabled = false;
}

void ShowGrid()
{
    if (grid !is null)
    {
        grid.enabled = true;

        if (editorScene.octree !is null)
            editorScene.octree.AddManualDrawable(grid);
    }
}

void UpdateGrid(bool updateGridGeometry = true)
{
    showGrid ? ShowGrid() : HideGrid();
    gridNode.scale = Vector3(gridScale, gridScale, gridScale);

    if (!updateGridGeometry)
        return;

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

    grid.BeginGeometry(0, LINE_LIST);
    float lineOffset = -halfSizeScaled;
    for (uint i = 0; i <= size; ++i)
    {
        bool lineCenter = i == halfSize;
        bool lineSubdiv = !Equals(Mod(i, subdivisionSize), 0.0);

        if (!grid2DMode)
        {
            grid.DefineVertex(Vector3(lineOffset, 0.0, halfSizeScaled));
            grid.DefineColor(lineCenter ? gridZColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            grid.DefineVertex(Vector3(lineOffset, 0.0, -halfSizeScaled));
            grid.DefineColor(lineCenter ? gridZColor : (lineSubdiv ? gridSubdivisionColor : gridColor));

            grid.DefineVertex(Vector3(-halfSizeScaled, 0.0, lineOffset));
            grid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            grid.DefineVertex(Vector3(halfSizeScaled, 0.0, lineOffset));
            grid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
        }
        else
        {
            grid.DefineVertex(Vector3(lineOffset, halfSizeScaled, 0.0));
            grid.DefineColor(lineCenter ? gridYColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            grid.DefineVertex(Vector3(lineOffset, -halfSizeScaled, 0.0));
            grid.DefineColor(lineCenter ? gridYColor : (lineSubdiv ? gridSubdivisionColor : gridColor));

            grid.DefineVertex(Vector3(-halfSizeScaled, lineOffset, 0.0));
            grid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            grid.DefineVertex(Vector3(halfSizeScaled, lineOffset, 0.0));
            grid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
        }

        lineOffset  += scale;
    }
    grid.Commit();
}

void CreateStatsBar()
{
    editorModeText = Text();
    ui.root.AddChild(editorModeText);
    renderStatsText = Text();
    ui.root.AddChild(renderStatsText);
    modelInfoText = Text();
    ui.root.AddChild(modelInfoText);
}

void SetupStatsBarText(Text@ text, Font@ font, int x, int y, HorizontalAlignment hAlign, VerticalAlignment vAlign)
{
    text.position = IntVector2(x, y);
    text.horizontalAlignment = hAlign;
    text.verticalAlignment = vAlign;
    text.SetFont(font, 11);
    text.color = Color(1, 1, 0);
    text.textEffect = TE_SHADOW;
    text.priority = -100;
}

void UpdateStats(float timeStep)
{
    String adding = "";
    // Todo: add localization
    if (hotKeyMode == HOTKEYS_MODE_BLENDER)
        adding = localization.Get("  CameraFlyMode: ") + (cameraFlyMode ? "True" : "False");

    editorModeText.text = String(
        localization.Get("Mode: ") + localization.Get(editModeText[editMode]) +
        localization.Get("  Axis: ") + localization.Get(axisModeText[axisMode]) +
        localization.Get("  Pick: ") + localization.Get(pickModeText[pickMode]) +
        localization.Get("  Fill: ") + localization.Get(fillModeText[fillMode]) +
        localization.Get("  Updates: ") + (runUpdate ? localization.Get("Running") : localization.Get("Paused") + adding));

    renderStatsText.text = String(
        localization.Get("Tris: ") + renderer.numPrimitives +
        localization.Get("  Batches: ") + renderer.numBatches +
        localization.Get("  Lights: ") + renderer.numLights[true] +
        localization.Get("  Shadowmaps: ") + renderer.numShadowMaps[true] +
        localization.Get("  Occluders: ") + renderer.numOccluders[true]);

    editorModeText.size = editorModeText.minSize;
    renderStatsText.size = renderStatsText.minSize;

    // Relayout stats bar
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");

    if(viewportMode != VIEWPORT_COMPACT)
    {
	if (ui.root.width >= editorModeText.size.x + renderStatsText.size.x + 45)
	{
            SetupStatsBarText(editorModeText, font, 35, 64, HA_LEFT, VA_TOP);
            SetupStatsBarText(renderStatsText, font, -4, 64, HA_RIGHT, VA_TOP);
            SetupStatsBarText(modelInfoText, font, 35, 88, HA_LEFT, VA_TOP);
	}
	else
	{
            SetupStatsBarText(editorModeText, font, 35, 64, HA_LEFT, VA_TOP);
            SetupStatsBarText(renderStatsText, font, 35, 78, HA_LEFT, VA_TOP);
            SetupStatsBarText(modelInfoText, font, 35, 102, HA_LEFT, VA_TOP);
	}
    }
    else
    {
        SetupStatsBarText(editorModeText, font, secondaryToolBar.width + hierarchyWindow.width + 10 , 64, HA_LEFT, VA_TOP);
        SetupStatsBarText(renderStatsText, font, secondaryToolBar.width + hierarchyWindow.width + 10 , 84, HA_LEFT, VA_TOP);
        SetupStatsBarText(modelInfoText, font, secondaryToolBar.width + hierarchyWindow.width + 10, 104, HA_LEFT, VA_TOP);
    }
}

void UpdateViewports(float timeStep)
{
    for(uint i = 0; i < viewports.length; ++i)
    {
        ViewportContext@ viewportContext = viewports[i];
        viewportContext.Update(timeStep);
    }
}

void SetMouseMode(bool enable)
{
    if (enable)
    {
        if (mouseOrbitMode == ORBIT_RELATIVE)
        {
            input.mouseMode = MM_RELATIVE;
            ui.cursor.visible = false;
        }
        else if (mouseOrbitMode == ORBIT_WRAP)
            input.mouseMode = MM_WRAP;
    }
    else
    {
        input.mouseMode = MM_ABSOLUTE;
        ui.cursor.visible = true;
    }
}

void SetMouseLock()
{
    toggledMouseLock = true;
    SetMouseMode(true);
    FadeUI();
}

void ReleaseMouseLock()
{
    if (toggledMouseLock)
    {
        toggledMouseLock = false;
        SetMouseMode(false);
    }
}

void CameraPan(Vector3 trans)
{
    cameraSmoothInterpolate.Stop();

    cameraLookAtNode.Translate(trans);
}

void CameraMoveForward(Vector3 trans)
{
    cameraSmoothInterpolate.Stop();
    
    cameraNode.Translate(trans, TS_PARENT);
}

void CameraRotateAroundLookAt(Quaternion rot)
{
    cameraSmoothInterpolate.Stop();
    
    cameraNode.rotation = rot;

    Vector3 dir = cameraNode.direction;
    dir.Normalize();

    float dist = cameraNode.position.length;

    cameraNode.position = -dir * dist;
}

void CameraRotateAroundCenter(Quaternion rot)
{
    cameraSmoothInterpolate.Stop();

    cameraNode.rotation = rot;
    
    Vector3 oldPos = cameraNode.worldPosition;

    Vector3 dir = cameraNode.worldDirection;
    dir.Normalize();

    float dist = cameraNode.position.length;

    cameraLookAtNode.worldPosition = cameraNode.worldPosition + dir * dist;
    cameraNode.worldPosition = oldPos;
}

void CameraRotateAroundSelect(Quaternion rot)
{
    cameraSmoothInterpolate.Stop();
    
    cameraNode.rotation = rot;

    Vector3 dir = cameraNode.direction;
    dir.Normalize();

    float dist = cameraNode.position.length;

    cameraNode.position = -dir * dist;

    Vector3 centerPoint;
    if ((selectedNodes.length > 0 || selectedComponents.length > 0))
        centerPoint = SelectedNodesCenterPoint();
    else
        centerPoint = lastSelectedNodesCenterPoint;

    // legacy way, camera look-at will jump to the selection
    cameraLookAtNode.worldPosition = centerPoint;
}

void CameraZoom(float zoom)
{
    cameraSmoothInterpolate.Stop();

    camera.zoom = Clamp(zoom, .1, 30);
}

void HandleStandardUserInput(float timeStep)
{
    // Speedup camera move if Shift key is down
    float speedMultiplier = 1.0;
    if (input.keyDown[KEY_LSHIFT])
        speedMultiplier = cameraShiftSpeedMultiplier;

    // Handle FPS mode
    if (!input.keyDown[KEY_LCTRL] && !input.keyDown[KEY_LALT])
    {
        if (input.keyDown[KEY_W] || input.keyDown[KEY_UP])
        {
            Vector3 dir = cameraNode.direction;
            dir.Normalize();

            CameraPan(dir * timeStep * cameraBaseSpeed * speedMultiplier);
            FadeUI();
        }
        if (input.keyDown[KEY_S] || input.keyDown[KEY_DOWN])
        {
            Vector3 dir = cameraNode.direction;
            dir.Normalize();

            CameraPan(-dir * timeStep * cameraBaseSpeed * speedMultiplier);
            FadeUI();
        }
        if (input.keyDown[KEY_A] || input.keyDown[KEY_LEFT])
        {
            Vector3 dir = cameraNode.right;
            dir.Normalize();

            CameraPan(-dir * timeStep * cameraBaseSpeed * speedMultiplier);
            FadeUI();
        }
        if (input.keyDown[KEY_D] || input.keyDown[KEY_RIGHT])
        {
            Vector3 dir = cameraNode.right;
            dir.Normalize();

            CameraPan(dir * timeStep * cameraBaseSpeed * speedMultiplier);
            FadeUI();
        }
        if (input.keyDown[KEY_E] || input.keyDown[KEY_PAGEUP])
        {
            Vector3 dir = cameraNode.up;
            dir.Normalize();

            CameraPan(dir * timeStep * cameraBaseSpeed * speedMultiplier);
            FadeUI();
        }
        if (input.keyDown[KEY_Q] || input.keyDown[KEY_PAGEDOWN])
        {
            Vector3 dir = cameraNode.up;
            dir.Normalize();

            CameraPan(-dir * timeStep * cameraBaseSpeed * speedMultiplier);
            FadeUI();
        }
    }

    // Zoom in/out
    if (input.mouseMoveWheel != 0 && ui.GetElementAt(ui.cursor.position) is null)
    {
        float distance = cameraNode.position.length;
        float ratio = distance / 40.0f;
        float factor = ratio < 1.0f ? ratio : 1.0f;

        if (!camera.orthographic)
        {
            Vector3 dir = cameraNode.direction;
            dir.Normalize();
            dir *= input.mouseMoveWheel * 40 * timeStep * cameraBaseSpeed * speedMultiplier * factor;

            CameraMoveForward(dir);
        }
        else
        {
            float zoom = camera.zoom + input.mouseMoveWheel * speedMultiplier * factor;
            
            CameraZoom(zoom);
        }
    }


    // Rotate/orbit/pan camera
    bool changeCamViewButton = false;
    
    changeCamViewButton = input.mouseButtonDown[MOUSEB_RIGHT] || input.mouseButtonDown[MOUSEB_MIDDLE];

    if (changeCamViewButton)
    {
        SetMouseLock();

        IntVector2 mouseMove = input.mouseMove;
        if (mouseMove.x != 0 || mouseMove.y != 0)
        {
            bool panTheCamera = false;

            if (input.mouseButtonDown[MOUSEB_MIDDLE])
            {
                if (mmbPanMode)
                    panTheCamera = !input.keyDown[KEY_LSHIFT];
                else
                    panTheCamera = input.keyDown[KEY_LSHIFT];
            }

            // Pan the camera
            if (panTheCamera)
            {
                Vector3 right = -cameraNode.worldRight;
                right.Normalize();
                right *= mouseMove.x;
                Vector3 up = cameraNode.worldUp;
                up.Normalize();
                up *= mouseMove.y;

                Vector3 trans = (right + up) * timeStep * cameraBaseSpeed * 0.5;

                CameraPan(trans);
            }
            else // Rotate the camera
            {
                activeViewport.cameraYaw += mouseMove.x * cameraBaseRotationSpeed;
                activeViewport.cameraPitch += mouseMove.y * cameraBaseRotationSpeed;

                if (limitRotation)
                    activeViewport.cameraPitch = Clamp(activeViewport.cameraPitch, -90.0, 90.0);

                Quaternion rot = Quaternion(activeViewport.cameraPitch, activeViewport.cameraYaw, 0);
                
                if (input.mouseButtonDown[MOUSEB_MIDDLE]) // Rotate around the camera center
                {
                    if (rotateAroundSelect)
                        CameraRotateAroundSelect(rot);
                    else
                        CameraRotateAroundLookAt(rot);
                    
                    orbiting = true;
                }
                else // Rotate around the look-at
                {
                    CameraRotateAroundCenter(rot);
                                            
                    orbiting = true;
                }
            }
        }
    }
    else
        ReleaseMouseLock();

    if (orbiting && !input.mouseButtonDown[MOUSEB_MIDDLE])
        orbiting = false;
}

void HandleBlenderUserInput(float timeStep)
{
    if (ui.HasModalElement() || ui.focusElement !is null)
    {
        ReleaseMouseLock();
        return;
    }

    // Check for camara fly mode
    if (input.keyDown[KEY_LSHIFT] && input.keyPress[KEY_F])
    {
        cameraFlyMode = !cameraFlyMode;
    }

    // Speedup camera move if Shift key is down
    float speedMultiplier = 1.0;
    if (input.keyDown[KEY_LSHIFT])
        speedMultiplier = cameraShiftSpeedMultiplier;

    // Handle FPS mode
    if (!input.keyDown[KEY_LCTRL] && !input.keyDown[KEY_LALT])
    {
        if (cameraFlyMode /*&& !input.keyDown[KEY_LSHIFT]*/)
        {
            if (input.keyDown[KEY_W] || input.keyDown[KEY_UP])
            {
                Vector3 dir = cameraNode.direction;
                dir.Normalize();

                CameraPan(dir * timeStep * cameraBaseSpeed * speedMultiplier);
                FadeUI();
            }
            if (input.keyDown[KEY_S] || input.keyDown[KEY_DOWN])
            {
                Vector3 dir = cameraNode.direction;
                dir.Normalize();

                CameraPan(-dir * timeStep * cameraBaseSpeed * speedMultiplier);
                FadeUI();
            }
            if (input.keyDown[KEY_A] || input.keyDown[KEY_LEFT])
            {
                Vector3 dir = cameraNode.right;
                dir.Normalize();

                CameraPan(-dir * timeStep * cameraBaseSpeed * speedMultiplier);
                FadeUI();
            }
            if (input.keyDown[KEY_D] || input.keyDown[KEY_RIGHT])
            {
                Vector3 dir = cameraNode.right;
                dir.Normalize();

                CameraPan(dir * timeStep * cameraBaseSpeed * speedMultiplier);
                FadeUI();
            }
            if (input.keyDown[KEY_E] || input.keyDown[KEY_PAGEUP])
            {
                Vector3 dir = cameraNode.up;
                dir.Normalize();

                CameraPan(dir * timeStep * cameraBaseSpeed * speedMultiplier);
                FadeUI();
            }
            if (input.keyDown[KEY_Q] || input.keyDown[KEY_PAGEDOWN])
            {
                Vector3 dir = cameraNode.up;
                dir.Normalize();

                CameraPan(-dir * timeStep * cameraBaseSpeed * speedMultiplier);
                FadeUI();
            }
        }
    }

    if (input.mouseMoveWheel != 0 && ui.GetElementAt(ui.cursor.position) is null)
    {
        if (!camera.orthographic)
        {
            if (input.keyDown[KEY_LSHIFT])
            {
                Vector3 dir = cameraNode.up;
                dir.Normalize();

                CameraPan(dir * input.mouseMoveWheel * 5 * timeStep * cameraBaseSpeed * speedMultiplier);
            }
            else if (input.keyDown[KEY_LCTRL])
            {
                Vector3 dir = cameraNode.right;
                dir.Normalize();

                CameraPan(dir * input.mouseMoveWheel * 5 * timeStep * cameraBaseSpeed * speedMultiplier);
            }
            else // Zoom in/out
            {
                float distance = cameraNode.position.length;
                float ratio = distance / 40.0f;
                float factor = ratio < 1.0f ? ratio : 1.0f;
                
                Vector3 dir = cameraNode.direction;
                dir.Normalize();
                dir *= input.mouseMoveWheel * 40 * timeStep * cameraBaseSpeed * speedMultiplier * factor;

                CameraMoveForward(dir);
            }
        }
        else
        {
            if (input.keyDown[KEY_LSHIFT])
            {
                Vector3 dir = cameraNode.up;
                dir.Normalize();

                CameraPan(dir * input.mouseMoveWheel * timeStep * cameraBaseSpeed * speedMultiplier * 4.0f);
            }
            else if (input.keyDown[KEY_LCTRL])
            {
                Vector3 dir = cameraNode.right;
                dir.Normalize();

                CameraPan(dir * input.mouseMoveWheel * timeStep * cameraBaseSpeed * speedMultiplier * 4.0f);
            }
            else
            {
                float zoom = camera.zoom + input.mouseMoveWheel * speedMultiplier * 0.5f;
                
                CameraZoom(zoom);
            }
        }
    }

    // Rotate/orbit/pan camera
    bool changeCamViewButton = input.mouseButtonDown[MOUSEB_MIDDLE] || cameraFlyMode;

    if (input.mouseButtonPress[MOUSEB_RIGHT] || input.keyDown[KEY_ESCAPE])
        cameraFlyMode = false;

    if (changeCamViewButton)
    {
        SetMouseLock();

        IntVector2 mouseMove = input.mouseMove;
        if (mouseMove.x != 0 || mouseMove.y != 0)
        {
            bool panTheCamera = false;

            if (!cameraFlyMode)
                panTheCamera = input.keyDown[KEY_LSHIFT];

            if (panTheCamera)
            {
                Vector3 right = -cameraNode.worldRight;
                right.Normalize();
                right *= mouseMove.x;
                Vector3 up = cameraNode.worldUp;
                up.Normalize();
                up *= mouseMove.y;

                Vector3 trans = (right + up) * timeStep * cameraBaseSpeed * 0.5;

                CameraPan(trans);
            }
            else
            {
                activeViewport.cameraYaw += mouseMove.x * cameraBaseRotationSpeed;
                activeViewport.cameraPitch += mouseMove.y * cameraBaseRotationSpeed;

                if (limitRotation)
                    activeViewport.cameraPitch = Clamp(activeViewport.cameraPitch, -90.0, 90.0);

                Quaternion rot = Quaternion(activeViewport.cameraPitch, activeViewport.cameraYaw, 0);
                
                if (cameraFlyMode)
                {
                    CameraRotateAroundCenter(rot);
                    orbiting = true;
                }
                else if (input.mouseButtonDown[MOUSEB_MIDDLE])
                {
                    if (rotateAroundSelect)
                        CameraRotateAroundSelect(rot);
                    else
                        CameraRotateAroundLookAt(rot);
                    
                    orbiting = true;
                }
            }
        }
    }
    else
        ReleaseMouseLock();

    if (orbiting && !input.mouseButtonDown[MOUSEB_MIDDLE])
        orbiting = false;
    
    // force to select component node for manipulation if selected only component and not his node
    if ((editMode != EDIT_SELECT && editNodes.empty) && lastSelectedComponent.Get() !is null)
    {
        if (lastSelectedComponent.Get() !is null)
        {
            Component@ component  = lastSelectedComponent.Get();
            SelectNode(component.node, false);
        }
    }
}

void UpdateView(float timeStep)
{
    if (ui.HasModalElement() || ui.focusElement !is null)
    {
        ReleaseMouseLock();
        return;
    }

    if (hotKeyMode == HOTKEYS_MODE_STANDARD)
    {    
        HandleStandardUserInput(timeStep);
    }    
    else if (hotKeyMode == HOTKEYS_MODE_BLENDER)
    {
        HandleBlenderUserInput(timeStep);
    }

    if (!editNodes.empty && editMode != EDIT_SELECT && input.keyDown[KEY_LCTRL])
    {
        Vector3 adjust(0, 0, 0);
        if (input.keyDown[KEY_UP])
            adjust.z = 1;
        if (input.keyDown[KEY_DOWN])
            adjust.z = -1;
        if (input.keyDown[KEY_LEFT])
            adjust.x = -1;
        if (input.keyDown[KEY_RIGHT])
            adjust.x = 1;
        if (input.keyDown[KEY_PAGEUP])
            adjust.y = 1;
        if (input.keyDown[KEY_PAGEDOWN])
            adjust.y = -1;
        if (editMode == EDIT_SCALE)
        {
            if (input.keyDown[KEY_KP_PLUS])
                adjust = Vector3(1, 1, 1);
            if (input.keyDown[KEY_KP_MINUS])
                adjust = Vector3(-1, -1, -1);
        }

        if (adjust == Vector3(0, 0, 0))
            return;

        bool moved = false;
        adjust *= timeStep * 10;

        switch (editMode)
        {
        case EDIT_MOVE:
            if (!moveSnap)
                moved = MoveNodes(adjust * moveStep);
            break;

        case EDIT_ROTATE:
            if (!rotateSnap)
                moved = RotateNodes(adjust * rotateStep);
            break;

        case EDIT_SCALE:
            if (!scaleSnap)
                moved = ScaleNodes(adjust * scaleStep);
            break;
        }

        if (moved)
            UpdateNodeAttributes();
    }

    // If not dragging
    if (resizingBorder == 0)
    {
        UIElement@ uiElement = ui.GetElementAt(ui.cursorPosition);
        if (uiElement !is null && uiElement.vars.Contains("VIEWMODE"))
        {
            setViewportCursor = uiElement.vars["VIEWMODE"].GetUInt();
            if (input.mouseButtonDown[MOUSEB_LEFT])
                resizingBorder = setViewportCursor;
        }
    }
}

void SteppedObjectManipulation(int key)
{
    if (editNodes.empty || editMode == EDIT_SELECT)
        return;

    // Do not react in non-snapped mode, because that is handled in frame update
    if (editMode == EDIT_MOVE && !moveSnap)
        return;
    if (editMode == EDIT_ROTATE && !rotateSnap)
        return;
    if (editMode == EDIT_SCALE && !scaleSnap)
        return;

    Vector3 adjust(0, 0, 0);
    if (key == KEY_UP)
        adjust.z = 1;
    if (key == KEY_DOWN)
        adjust.z = -1;
    if (key == KEY_LEFT)
        adjust.x = -1;
    if (key == KEY_RIGHT)
        adjust.x = 1;
    if (key == KEY_PAGEUP)
        adjust.y = 1;
    if (key == KEY_PAGEDOWN)
        adjust.y = -1;
    if (editMode == EDIT_SCALE)
    {
        if (key == KEY_KP_PLUS)
            adjust = Vector3(1, 1, 1);
        if (key == KEY_KP_MINUS)
            adjust = Vector3(-1, -1, -1);
    }

    if (adjust == Vector3(0, 0, 0))
        return;

    bool moved = false;

    switch (editMode)
    {
    case EDIT_MOVE:
        moved = MoveNodes(adjust);
        break;

    case EDIT_ROTATE:
        {
            float rotateStepScaled = rotateStep * snapScale;
            moved = RotateNodes(adjust * rotateStepScaled);
        }
        break;

    case EDIT_SCALE:
        {
            float scaleStepScaled = scaleStep * snapScale;
            moved = ScaleNodes(adjust * scaleStepScaled);
        }
        break;
    }

    if (moved)
        UpdateNodeAttributes();
}

void HandlePostRenderUpdate()
{
    DebugRenderer@ debug = editorScene.debugRenderer;
    if (debug is null || orbiting || debugRenderDisabled)
        return;

    // Visualize the currently selected nodes
    for (uint i = 0; i < selectedNodes.length; ++i)
        DrawNodeDebug(selectedNodes[i], debug);

    // Visualize the currently selected components
    for (uint i = 0; i < selectedComponents.length; ++i)
        selectedComponents[i].DrawDebugGeometry(debug, false);

    // Visualize the currently selected UI-elements
    for (uint i = 0; i < selectedUIElements.length; ++i)
        ui.DebugDraw(selectedUIElements[i]);

    if (renderingDebug)
        renderer.DrawDebugGeometry(false);

    if (physicsDebug && editorScene.physicsWorld !is null)
        editorScene.physicsWorld.DrawDebugGeometry(true);

    if (physicsDebug && editorScene.physicsWorld2D !is null)
    {
        bool needDraw = true;
        for (uint i = 0; i < selectedComponents.length; ++i)
        {
            if (cast<PhysicsWorld2D>(selectedComponents[i]) !is null)
            {
                needDraw = false; // Already drawed
                break;
            }
        }

        if (needDraw)
            physicsWorld2D.DrawDebugGeometry();
    }

    if (octreeDebug && editorScene.octree !is null)
        editorScene.octree.DrawDebugGeometry(true);

    if (navigationDebug)
    {
        CrowdManager@ crowdManager = editorScene.GetComponent("CrowdManager");
        if (crowdManager !is null)
            crowdManager.DrawDebugGeometry(true);

        Array<Component@>@ navMeshes = editorScene.GetComponents("NavigationMesh", true);
        for (uint i = 0; i < navMeshes.length; ++i)
            cast<NavigationMesh>(navMeshes[i]).DrawDebugGeometry(true);

        Array<Component@>@ dynNavMeshes = editorScene.GetComponents("DynamicNavigationMesh", true);
        for (uint i = 0; i < dynNavMeshes.length; ++i)
            cast<DynamicNavigationMesh>(dynNavMeshes[i]).DrawDebugGeometry(true);
    }

    if (setViewportCursor | resizingBorder > 0)
    {
        SetViewportCursor();
        if (resizingBorder == 0)
            setViewportCursor = 0;
    }

    ViewRaycast(false);
}

void DrawNodeDebug(Node@ node, DebugRenderer@ debug, bool drawNode = true)
{
    if (drawNode)
        debug.AddNode(node, 1.0, false);

    // Exception for the scene to avoid bringing the editor to its knees: drawing either the whole hierarchy or the subsystem-
    // components can have a large performance hit. Also do not draw terrain child nodes due to their large amount
    // (TerrainPatch component itself draws nothing as debug geometry)
    if (node !is editorScene && node.GetComponent("Terrain") is null)
    {
        for (uint j = 0; j < node.numComponents; ++j)
            node.components[j].DrawDebugGeometry(debug, false);

        // To avoid cluttering the view, do not draw the node axes for child nodes
        for (uint k = 0; k < node.numChildren; ++k)
            DrawNodeDebug(node.children[k], debug, false);
    }
}

void ViewMouseMove()
{
    Ray cameraRay = GetActiveViewportCameraRay();
    Component@ selectedComponent;

    if (pickMode < PICK_RIGIDBODIES && editorScene.octree !is null)
    {
        RayQueryResult result = editorScene.octree.RaycastSingle(cameraRay, RAY_TRIANGLE, camera.farClip,
            pickModeDrawableFlags[pickMode], 0x7fffffff);

        if (result.drawable !is null && result.drawable.typeName == "TerrainPatch" && result.drawable.node.parent !is null)
        {
            Terrain@ terrainComponent = result.drawable.node.parent.GetComponent("Terrain");
            terrainEditor.UpdateBrushVisualizer(terrainComponent, result.position);
        }
        else {
            terrainEditor.HideBrushVisualizer();
        }
    }

    // setting mouse position based on mouse position
    if (ui.IsDragging()) { }
    else if (ui.focusElement !is null || input.mouseButtonDown[MOUSEB_LEFT|MOUSEB_MIDDLE|MOUSEB_RIGHT])
        return;

    IntVector2 pos = ui.cursor.position;
    for (uint i = 0; i < viewports.length; ++i)
    {
        ViewportContext@ vc = viewports[i];
        if (vc !is activeViewport && vc.viewport.rect.IsInside(pos) == INSIDE)
            SetActiveViewport(vc);
    }
}

void ViewMouseClick()
{
    ViewRaycast(true);
}

Ray GetActiveViewportCameraRay()
{
    IntRect view = activeViewport.viewport.rect;
    return camera.GetScreenRay(
        float(ui.cursorPosition.x - view.left) / view.width,
        float(ui.cursorPosition.y - view.top) / view.height
    );
}

void ViewMouseClickEnd()
{
    // checks to close open popup windows
    IntVector2 pos = ui.cursorPosition;
    if (contextMenu !is null && contextMenu.enabled)
    {
        if (contextMenuActionWaitFrame)
            contextMenuActionWaitFrame = false;
        else
        {
            if (!contextMenu.IsInside(pos, true))
                CloseContextMenu();
        }
    }
    if (quickMenu !is null && quickMenu.enabled)
    {
        bool enabled = quickMenu.IsInside(pos, true);
        quickMenu.enabled = enabled;
        quickMenu.visible = enabled;
    }
}

void ViewRaycast(bool mouseClick)
{
    // Ignore if UI has modal element
    if (ui.HasModalElement())
        return;

    // Ignore if mouse is grabbed by other operation
    if (input.mouseGrabbed)
        return;

    IntVector2 pos = ui.cursorPosition;
    UIElement@ elementAtPos = ui.GetElementAt(pos, pickMode != PICK_UI_ELEMENTS);
    if (editMode == EDIT_SPAWN)
    {
        if(mouseClick && input.mouseButtonPress[MOUSEB_LEFT] && elementAtPos is null)
            SpawnObject();
        return;
    }

    // Do not raycast / change selection if hovering over the gizmo
    if (IsGizmoSelected())
        return;

    DebugRenderer@ debug = editorScene.debugRenderer;

    if (pickMode == PICK_UI_ELEMENTS)
    {
        bool leftClick = mouseClick && input.mouseButtonPress[MOUSEB_LEFT];
        bool multiselect = input.qualifierDown[QUAL_CTRL];

        // Only interested in user-created UI elements
        if (elementAtPos !is null && elementAtPos !is editorUIElement && elementAtPos.GetElementEventSender() is editorUIElement)
        {
            ui.DebugDraw(elementAtPos);

            if (leftClick)
                SelectUIElement(elementAtPos, multiselect);
        }
        // If clicked on emptiness in non-multiselect mode, clear the selection
        else if (leftClick && !multiselect && ui.GetElementAt(pos) is null)
            hierarchyList.ClearSelection();

        return;
    }

    // Do not raycast / change selection if hovering over a UI element when not in PICK_UI_ELEMENTS Mode
    if (elementAtPos !is null)
        return;

    Ray cameraRay = GetActiveViewportCameraRay();
    Component@ selectedComponent;

    if (pickMode < PICK_RIGIDBODIES)
    {
        if (editorScene.octree is null)
            return;

        RayQueryResult result = editorScene.octree.RaycastSingle(cameraRay, RAY_TRIANGLE, camera.farClip,
            pickModeDrawableFlags[pickMode], 0x7fffffff);

        if (result.drawable !is null)
        {
            Drawable@ drawable = result.drawable;

            // for actual last selected node or component in both modes
            if (hotKeyMode == HOTKEYS_MODE_STANDARD)
            {
                if (input.mouseButtonDown[MOUSEB_LEFT])
                {
                    lastSelectedNode = drawable.node;
                    lastSelectedDrawable = drawable;
                    lastSelectedComponent = drawable;
                }
            }
            else if (hotKeyMode == HOTKEYS_MODE_BLENDER)
            {
                if (input.mouseButtonDown[MOUSEB_RIGHT])
                {
                    lastSelectedNode = drawable.node;
                    lastSelectedDrawable = drawable;
                    lastSelectedComponent = drawable;
                }
            }

            // If selecting a terrain patch, select the parent terrain instead
            if (drawable.typeName != "TerrainPatch")
            {
                selectedComponent = drawable;
                if (debug !is null)
                {
                    debug.AddNode(drawable.node, 1.0, false);
                    drawable.DrawDebugGeometry(debug, false);
                }
            }
            else if (drawable.node.parent !is null){
                Terrain@ terrainComponent = drawable.node.parent.GetComponent("Terrain");
                selectedComponent = terrainComponent;
                if (selectedComponent is terrainComponent && input.mouseButtonDown[MOUSEB_LEFT])
                {
                    selectedComponent = terrainComponent;
                    terrainEditor.Work(terrainComponent, result.position);
                }
                else
                {
                    terrainEditor.targetColorSelected = false;
                }
            }
        }
    }
    else
    {
        if (editorScene.physicsWorld is null)
            return;

        // If we are not running the actual physics update, refresh collisions before raycasting
        if (!runUpdate)
            editorScene.physicsWorld.UpdateCollisions();

        PhysicsRaycastResult result = editorScene.physicsWorld.RaycastSingle(cameraRay, camera.farClip);
        if (result.body !is null)
        {
            RigidBody@ body = result.body;
            if (debug !is null)
            {
                debug.AddNode(body.node, 1.0, false);
                body.DrawDebugGeometry(debug, false);
            }
            selectedComponent = body;
        }
    }

    bool multiselect = false;
    bool componentSelectQualifier = false;
    bool mouseButtonPressRL = false;

    if (hotKeyMode == HOTKEYS_MODE_STANDARD)
    {
        mouseButtonPressRL = input.mouseButtonPress[MOUSEB_LEFT];
        componentSelectQualifier = input.qualifierDown[QUAL_SHIFT];
        multiselect = input.qualifierDown[QUAL_CTRL];
    }
    else if (hotKeyMode == HOTKEYS_MODE_BLENDER)
    {
        mouseButtonPressRL = input.mouseButtonPress[MOUSEB_RIGHT];
        componentSelectQualifier = input.qualifierDown[QUAL_CTRL];
        multiselect = input.qualifierDown[QUAL_SHIFT];
    }

    if (mouseClick && mouseButtonPressRL)
    {
        if (selectedComponent !is null)
        {
            if (componentSelectQualifier)
            {
                // If we are selecting components, but have nodes in existing selection, do not multiselect to prevent confusion
                if (!selectedNodes.empty)
                    multiselect = false;
                SelectComponent(selectedComponent, multiselect);
            }
            else
            {
                // If we are selecting nodes, but have components in existing selection, do not multiselect to prevent confusion
                if (!selectedComponents.empty)
                    multiselect = false;
                SelectNode(selectedComponent.node, multiselect);
            }
        }
        else
        {
            // If clicked on emptiness in non-multiselect mode, clear the selection
            if (!multiselect)
               SelectComponent(null, false);
        }
    }
}

Vector3 GetNewNodePosition(bool raycastToMouse = false)
{
    if (newNodeMode == NEW_NODE_IN_CENTER)
        return Vector3(0, 0, 0);
    if (newNodeMode == NEW_NODE_RAYCAST)
    {
        Ray cameraRay = raycastToMouse ? GetActiveViewportCameraRay() : camera.GetScreenRay(0.5, 0.5);
        Vector3 position, normal;
        if (GetSpawnPosition(cameraRay, camera.farClip, position, normal, 0, false))
            return position;
    }
    return cameraLookAtNode.worldPosition;
}

int GetShadowResolution()
{
    if (!renderer.drawShadows)
        return 0;
    int level = 1;
    int res = renderer.shadowMapSize;
    while (res > 512)
    {
        res >>= 1;
        ++level;
    }
    if (level > 3)
        level = 3;

    return level;
}

void SetShadowResolution(int level)
{
    if (level <= 0)
    {
        renderer.drawShadows = false;
        return;
    }
    else
    {
        renderer.drawShadows = true;
        renderer.shadowMapSize = 256 << level;
    }
}

void ToggleRenderingDebug()
{
    renderingDebug = !renderingDebug;
}

void TogglePhysicsDebug()
{
    physicsDebug = !physicsDebug;
}

void ToggleOctreeDebug()
{
    octreeDebug = !octreeDebug;
}

void ToggleNavigationDebug()
{
    navigationDebug = !navigationDebug;
}

bool StopTestAnimation()
{
    testAnimState = null;
    return true;
}

void MergeNodeBoundingBox(BoundingBox &inout box, Array<Component@>&inout visitedComponents, Node@ node)
{
    if (node is null || node is editorScene)
        return;

    // if node has no component, merge its world position
    if (node.numComponents == 0)
    {
        box.Merge(node.worldPosition);
    }

    // Merge components bounding box of this node
    for (uint i = 0; i < node.numComponents; ++i)
    {
        MergeComponentBoundingBox(box, visitedComponents, node.components[i]);
    }

    // Merge bounding boxes of child nodes recursively
    for (uint i = 0; i < node.numChildren; ++i)
    {
        Node@ child = node.children[i];
        MergeNodeBoundingBox(box, visitedComponents, child);
    }
}

void MergeComponentBoundingBox(BoundingBox &inout box, Array<Component@>&inout visitedComponents, Component@ component)
{
    if (component is null || visitedComponents.FindByRef(component) != -1)
        return;

    Drawable@ drawable = cast<Drawable>(component);

    // Merge drawable component's bounding box. Skip skybox, as its box is very large, as well as lights
    if (drawable !is null && cast<Skybox>(drawable) is null && cast<Light>(drawable) is null)
    {
        box.Merge(drawable.worldBoundingBox);
        visitedComponents.Push(component);
        return;
    }
    
    // If the component is not a drawable, merge the world position of its node
    if (component.node !is editorScene)
        box.Merge(component.node.worldPosition);

    visitedComponents.Push(component);
}

void LocateNodes(Array<Node@> nodes)
{
    if (nodes.empty || (nodes.length == 1 && nodes[0] is editorScene))
        return;

    // Calculate bounding box of all nodes
    BoundingBox box;
    Array<Component@> visitedComponents;

    for (uint i = 0; i < nodes.length; ++i)
    {
        MergeNodeBoundingBox(box, visitedComponents, nodes[i]);
    }

    FitCamera(box, true);
}

void LocateComponents(Array<Component@> components)
{
    if (components.empty || components.length == 1 && components[0].node is editorScene)
        return;

    // Calculate bounding box of all nodes
    BoundingBox box;
    Array<Component@> visitedComponents;

    for (uint i = 0; i < components.length; ++i)
    {
        MergeComponentBoundingBox(box, visitedComponents, components[i]);
    }

    FitCamera(box, true);
}

void LocateNodesAndComponents(Array<Node@> nodes, Array<Component@> components)
{
    if (nodes.length == 0 && components.length == 0)
        return;
        
    // Calculate bounding box of all nodes
    BoundingBox box;
    Array<Component@> visitedComponents;

    if (!nodes.empty && !(nodes.length == 1 && nodes[0] is editorScene))
    {
        for (uint i = 0; i < nodes.length; ++i)
        {
            MergeNodeBoundingBox(box, visitedComponents, nodes[i]);
        }
    }

    if (!components.empty)
    {
        for (uint i = 0; i < components.length; ++i)
        {
            MergeComponentBoundingBox(box, visitedComponents, components[i]);
        }
    }

    FitCamera(box, true);
}

void FitCamera(BoundingBox box, bool smooth)
{
    // Calculate proper camera distance - fit the bounding sphere into the camera frustum
    Sphere sphere = Sphere(box);

    float aspect = camera.aspectRatio;
    float fov = 0.0f;

    // Choose the small one from vertical and horizontal fovs
    if (aspect > 1.0f)
        fov = camera.fov;
    else
        fov = camera.fov * aspect;

    fov *= 0.5f;

    if (sphere.radius < 1.0f)
        sphere.radius = 1.0f;
    
    float distance = sphere.radius / Sin(fov);

    if (distance > viewFarClip)
        distance = viewFarClip;

    Vector3 dir = cameraNode.direction;
    dir.Normalize();

    // Make the distance a little farther 
    distance *= 1.1f;

    // Set zoom value a little bigger
    float zoom = camera.orthoSize / (sphere.radius * 2.0f);
    zoom *= 1.1f;

    // We put the pivot node to the center of the bounding sphere 
    // and put the camera node to the opposite of view direction
    Vector3 lookAtPos = sphere.center;
    Vector3 cameraPos = -dir * distance;
    
    cameraSmoothInterpolate.Stop();

    if (smooth)
    {
        cameraSmoothInterpolate.SetLookAtNodePosition(cameraLookAtNode.worldPosition, lookAtPos);
        cameraSmoothInterpolate.SetCameraNodePosition(cameraNode.position, cameraPos);

        if (camera.orthographic)
            cameraSmoothInterpolate.SetCameraZoom(camera.zoom, zoom);
        
        cameraSmoothInterpolate.Start(0.5f);
    }
    else
    {
        cameraLookAtNode.worldPosition = lookAtPos;
        cameraNode.position = cameraPos;

        if (camera.orthographic)
            camera.zoom = zoom;
    }
}

Vector3 SelectedNodesCenterPoint()
{
    Vector3 centerPoint;
    uint count = selectedNodes.length;
    for (uint i = 0; i < selectedNodes.length; ++i)
        centerPoint += selectedNodes[i].worldPosition;

    for (uint i = 0; i < selectedComponents.length; ++i)
    {
        Drawable@ drawable = cast<Drawable>(selectedComponents[i]);
        count++;
        if (drawable !is null)
            centerPoint += drawable.node.LocalToWorld(drawable.boundingBox.center);
        else
            centerPoint += selectedComponents[i].node.worldPosition;
    }

    if (count > 0)
    {
        lastSelectedNodesCenterPoint = centerPoint / count;
        return centerPoint / count;
    }
    else
    {
        lastSelectedNodesCenterPoint = centerPoint;
        return centerPoint;
    }
}

Drawable@ GetDrawableAtMousePostion()
{
    IntVector2 pos = ui.cursorPosition;
    Ray cameraRay = camera.GetScreenRay(float(pos.x) / activeViewport.viewport.rect.width, float(pos.y) / activeViewport.viewport.rect.height);

    if (editorScene.octree is null)
        return null;

    RayQueryResult result = editorScene.octree.RaycastSingle(cameraRay, RAY_TRIANGLE, camera.farClip, DRAWABLE_GEOMETRY, 0x7fffffff);

    return result.drawable;
}

void HandleBeginViewUpdate(StringHash eventType, VariantMap& eventData)
{
    // Hide gizmo, grid and debug icons from any camera other then active viewport
    if (eventData["Camera"].GetPtr() !is camera)
    {
        if (gizmo !is null)
            gizmo.viewMask = 0;
    }
    if (eventData["Camera"].GetPtr() is previewCamera.Get())
    {
        suppressSceneChanges = true;
        if (grid !is null)
            grid.viewMask = 0;
        if (debugIconsNode !is null)
            debugIconsNode.enabled = false;
        suppressSceneChanges = false;
    }
}

void HandleEndViewUpdate(StringHash eventType, VariantMap& eventData)
{
    // Restore gizmo and grid after camera view update
    if (eventData["Camera"].GetPtr() !is camera)
    {
        if (gizmo !is null)
            gizmo.viewMask = 0x80000000;
    }
    if (eventData["Camera"].GetPtr() is previewCamera.Get())
    {
        suppressSceneChanges = true;
        if (grid !is null)
            grid.viewMask = 0x80000000;
        if (debugIconsNode !is null)
            debugIconsNode.enabled = true;
        suppressSceneChanges = false;
    }
}

bool debugWasEnabled = true;

void HandleBeginViewRender(StringHash eventType, VariantMap& eventData)
{
    // Hide debug geometry from preview camera
    if (eventData["Camera"].GetPtr() is previewCamera.Get())
    {
        DebugRenderer@ debug = editorScene.GetComponent("DebugRenderer");
        if (debug !is null)
        {
            suppressSceneChanges = true; // Do not want UI update now
            debugWasEnabled = debug.enabled;
            debug.enabled = false;
            suppressSceneChanges = false;
        }
    }
}

void HandleEndViewRender(StringHash eventType, VariantMap& eventData)
{
    // Restore debug geometry after preview camera render
    if (eventData["Camera"].GetPtr() is previewCamera.Get())
    {
        DebugRenderer@ debug = editorScene.GetComponent("DebugRenderer");
        if (debug !is null)
        {
            suppressSceneChanges = true; // Do not want UI update now
            debug.enabled = debugWasEnabled;
            suppressSceneChanges = false;
        }
    }
}
