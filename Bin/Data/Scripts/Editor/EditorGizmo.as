// Urho3D editor node transform gizmo handling

Node@ gizmoNode;
StaticModel@ gizmo;

const float axisMaxD = 0.1;
const float axisMaxT = 1.0;
const float rotSensitivity = 50.0;

class GizmoAxis
{
    Ray axisRay;
    bool selected;
    float t;
    float d;
    float lastT;
    float lastD;

    GizmoAxis()
    {
        selected = false;
        t = 0.0;
        d = 0.0;
        lastT = 0.0;
        lastD = 0.0;
    }

    void Update(Ray cameraRay, float scale, bool drag)
    {
        lastT = t;
        lastD = d;

        Vector3 closest = cameraRay.ClosestPoint(axisRay);
        Vector3 projected = axisRay.Project(closest);
        d = axisRay.Distance(closest);
        t = (projected - axisRay.origin).DotProduct(axisRay.direction);

        // Update selected status only when not dragging
        if (!drag)
            selected = d < axisMaxD * scale && t >= 0.0 && t <= axisMaxT * scale;
    }
}

GizmoAxis gizmoAxisX;
GizmoAxis gizmoAxisY;
GizmoAxis gizmoAxisZ;

void CreateGizmo()
{
    gizmoNode = Node();
    gizmo = gizmoNode.CreateComponent("StaticModel");
    gizmo.model = cache.GetResource("Model", "Models/Axes.mdl");
    gizmo.materials[0] = cache.GetResource("Material", "Materials/RedUnlit.xml");
    gizmo.materials[1] = cache.GetResource("Material", "Materials/GreenUnlit.xml");
    gizmo.materials[2] = cache.GetResource("Material", "Materials/BlueUnlit.xml");
    gizmo.visible = false;

    if (editorScene.octree !is null)
        editorScene.octree.AddUnculledDrawable(gizmo);
}

void UpdateGizmo()
{
    PositionGizmo();
    ResizeGizmo();
    UseGizmo();
}

void PositionGizmo()
{
    if (gizmo is null)
        return;

    if (editNodes.empty)
    {
        gizmo.visible = false;
        return;
    }
    
    Vector3 center(0, 0, 0);
    
    for (uint i = 0; i < editNodes.length; ++i)
        center += editNodes[i].worldPosition;

    center /= editNodes.length;
    gizmoNode.position = center;

    if (axisMode == AXIS_WORLD || editNodes.length > 1)
        gizmoNode.rotation = Quaternion();
    else
        gizmoNode.rotation = editNodes[0].worldRotation;

    gizmo.visible = true;
}

void ResizeGizmo()
{
    if (gizmo is null || !gizmo.visible)
        return;

    float c = 0.1;

    if (camera.orthographic)
        gizmoNode.scale = Vector3(c, c, c);
    else
    {
        /// \todo if matrix classes were exposed to script could simply use the camera's inverse world transform
        float z = (cameraNode.worldRotation.Inverse() * (gizmoNode.worldPosition - cameraNode.worldPosition)).z;
        gizmoNode.scale = Vector3(c * z, c * z, c * z);
    }
}

void CalculateGizmoAxes()
{
    gizmoAxisX.axisRay = Ray(gizmoNode.position, gizmoNode.rotation * Vector3(1, 0, 0));
    gizmoAxisY.axisRay = Ray(gizmoNode.position, gizmoNode.rotation * Vector3(0, 1, 0));
    gizmoAxisZ.axisRay = Ray(gizmoNode.position, gizmoNode.rotation * Vector3(0, 0, 1));
}

void UseGizmo()
{
    if (gizmo is null || !gizmo.visible)
        return;

    IntVector2 pos = ui.cursorPosition;
    if (ui.GetElementAt(pos) !is null)
        return;
    Ray cameraRay = camera.GetScreenRay(float(pos.x) / graphics.width, float(pos.y) / graphics.height);
    float scale = gizmoNode.scale.x;

    // Recalculate axes only when not left-dragging
    bool drag = input.mouseButtonDown[MOUSEB_LEFT];
    if (!drag)
        CalculateGizmoAxes();

    gizmoAxisX.Update(cameraRay, scale, drag);
    gizmoAxisY.Update(cameraRay, scale, drag);
    gizmoAxisZ.Update(cameraRay, scale, drag);

    gizmo.materials[0] = cache.GetResource("Material", gizmoAxisX.selected ? "Materials/BrightRedUnlit.xml" : "Materials/RedUnlit.xml");
    gizmo.materials[1] = cache.GetResource("Material", gizmoAxisY.selected ? "Materials/BrightGreenUnlit.xml" : "Materials/GreenUnlit.xml");
    gizmo.materials[2] = cache.GetResource("Material", gizmoAxisZ.selected ? "Materials/BrightBlueUnlit.xml" : "Materials/BlueUnlit.xml");

    if (drag)
    {
        /// \todo Implement scaling
        /// \todo Implement snapping
        if (moveMode == OBJ_MOVE)
        {
            Vector3 adjust(0, 0, 0);
            if (gizmoAxisX.selected)
                adjust += gizmoAxisX.axisRay.direction * (gizmoAxisX.t - gizmoAxisX.lastT);
            if (gizmoAxisY.selected)
                adjust += gizmoAxisY.axisRay.direction * (gizmoAxisY.t - gizmoAxisY.lastT);
            if (gizmoAxisZ.selected)
                adjust += gizmoAxisZ.axisRay.direction * (gizmoAxisZ.t - gizmoAxisZ.lastT);

            if (adjust.length > M_EPSILON)
            {
                for (uint i = 0; i < editNodes.length; ++i)
                {
                    Node@ node = editNodes[i];
                    Vector3 nodeAdjust = adjust;
                    if (node.parent !is null)
                        nodeAdjust = node.parent.WorldToLocal(Vector4(nodeAdjust, 0.0));
                    node.position = node.position + nodeAdjust;
                }

                UpdateNodeAttributes();
            }
        }
        else if (moveMode == OBJ_ROTATE)
        {
            Vector3 adjust(0, 0, 0);
            if (gizmoAxisX.selected)
                adjust.x = (gizmoAxisX.d - gizmoAxisX.lastD) * rotSensitivity / scale;
            if (gizmoAxisY.selected)
                adjust.y = (gizmoAxisY.d - gizmoAxisY.lastD) * rotSensitivity / scale;
            if (gizmoAxisZ.selected)
                adjust.z = (gizmoAxisZ.d - gizmoAxisZ.lastD) * rotSensitivity / scale;

            if (adjust.length > M_EPSILON)
            {
                for (uint i = 0; i < editNodes.length; ++i)
                {
                    /// \todo When multiple nodes selected, rotate them around the gizmo
                    Node@ node = editNodes[i];
                    Quaternion rotQuat(adjust);
                    if (axisMode == AXIS_WORLD)
                        node.rotation = rotQuat * node.rotation;
                    else
                        node.rotation = node.rotation * rotQuat;
                }
                
                UpdateNodeAttributes();
            }
        }
    }
}

bool IsGizmoSelected()
{
    return gizmoAxisX.selected || gizmoAxisY.selected || gizmoAxisZ.selected;
}
