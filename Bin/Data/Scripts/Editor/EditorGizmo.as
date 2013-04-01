// Urho3D editor node transform gizmo handling

Node@ gizmoNode;
StaticModel@ gizmo;

const float axisMaxD = 0.1;
const float axisMaxT = 1.0;
const float rotSensitivity = 50.0;

EditMode lastGizmoMode;

class GizmoAxis
{
    Ray axisRay;
    bool selected;
    bool lastSelected;
    float t;
    float d;
    float lastT;
    float lastD;

    GizmoAxis()
    {
        selected = false;
        lastSelected = false;
        t = 0.0;
        d = 0.0;
        lastT = 0.0;
        lastD = 0.0;
    }

    void Update(Ray cameraRay, float scale, bool drag)
    {
        // Do not select when UI has modal element
        if (ui.modalElement !is null)
        {
            selected = false;
            return;
        }
        
        Vector3 closest = cameraRay.ClosestPoint(axisRay);
        Vector3 projected = axisRay.Project(closest);
        d = axisRay.Distance(closest);
        t = (projected - axisRay.origin).DotProduct(axisRay.direction);

        // Determine the sign of d from a plane that goes through the camera position to the axis
        Plane axisPlane(cameraNode.position, axisRay.origin, axisRay.origin + axisRay.direction);
        if (axisPlane.Distance(closest) < 0.0)
            d = -d;

        // Update selected status only when not dragging
        if (!drag)
        {
            selected = Abs(d) < axisMaxD * scale && t >= -axisMaxD * scale && t <= axisMaxT * scale;
            lastT = t;
            lastD = d;
        }
    }

    void Moved()
    {
        lastT = t;
        lastD = d;
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
    gizmo.enabled = false;
    gizmo.viewMask = 0x80000000; // Editor raycasts use viewmask 0x7fffffff
    gizmo.occludee = false;

    gizmoAxisX.lastSelected = false;
    gizmoAxisY.lastSelected = false;
    gizmoAxisZ.lastSelected = false;
    lastGizmoMode = EDIT_MOVE;
}

void HideGizmo()
{
    if (gizmo !is null)
        gizmo.enabled = false;
}

void ShowGizmo()
{
    if (gizmo !is null)
    {
        gizmo.enabled = true;

        // Because setting enabled = false detaches the gizmo from octree,
        // and it is a manually added drawable, must readd to octree when showing
        if (editorScene.octree !is null)
            editorScene.octree.AddManualDrawable(gizmo);
    }
}

void UpdateGizmo()
{
    UseGizmo();
    PositionGizmo();
    ResizeGizmo();
}

void PositionGizmo()
{
    if (gizmo is null)
        return;

    if (editNodes.empty)
    {
        HideGizmo();
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

    if (editMode != lastGizmoMode)
    {
        switch (editMode)
        {
        case EDIT_MOVE:
            gizmo.model = cache.GetResource("Model", "Models/Axes.mdl");
            break;

        case EDIT_ROTATE:
            gizmo.model = cache.GetResource("Model", "Models/RotateAxes.mdl");
            break;

        case EDIT_SCALE:
            gizmo.model = cache.GetResource("Model", "Models/ScaleAxes.mdl");
            break;
        }

        lastGizmoMode = editMode;
    }

    if (editMode != EDIT_SELECT && !gizmo.enabled)
        ShowGizmo();
    else if (editMode == EDIT_SELECT && gizmo.enabled)
        HideGizmo();
}

void ResizeGizmo()
{
    if (gizmo is null || !gizmo.enabled)
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

void GizmoMoved()
{
    gizmoAxisX.Moved();
    gizmoAxisY.Moved();
    gizmoAxisZ.Moved();
}

void UseGizmo()
{
    if (gizmo is null || !gizmo.enabled || editMode == EDIT_SELECT)
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

    if (gizmoAxisX.selected != gizmoAxisX.lastSelected)
    {
        gizmo.materials[0] = cache.GetResource("Material", gizmoAxisX.selected ? "Materials/BrightRedUnlit.xml" : "Materials/RedUnlit.xml");
        gizmoAxisX.lastSelected = gizmoAxisX.selected;
    }
    if (gizmoAxisY.selected != gizmoAxisY.lastSelected)
    {
        gizmo.materials[1] = cache.GetResource("Material", gizmoAxisY.selected ? "Materials/BrightGreenUnlit.xml" : "Materials/GreenUnlit.xml");
        gizmoAxisY.lastSelected = gizmoAxisY.selected;
    }
    if (gizmoAxisZ.selected != gizmoAxisZ.lastSelected)
    {
        gizmo.materials[2] = cache.GetResource("Material", gizmoAxisZ.selected ? "Materials/BrightBlueUnlit.xml" : "Materials/BlueUnlit.xml");
        gizmoAxisZ.lastSelected = gizmoAxisZ.selected;
    };

    if (drag)
    {
        bool moved = false;

        if (editMode == EDIT_MOVE)
        {
            Vector3 adjust(0, 0, 0);
            if (gizmoAxisX.selected)
                adjust += Vector3(1, 0, 0) * (gizmoAxisX.t - gizmoAxisX.lastT);
            if (gizmoAxisY.selected)
                adjust += Vector3(0, 1, 0) * (gizmoAxisY.t - gizmoAxisY.lastT);
            if (gizmoAxisZ.selected)
                adjust += Vector3(0, 0, 1) * (gizmoAxisZ.t - gizmoAxisZ.lastT);

            moved = MoveNodes(adjust);
        }
        else if (editMode == EDIT_ROTATE)
        {
            Vector3 adjust(0, 0, 0);
            if (gizmoAxisX.selected)
                adjust.x = (gizmoAxisX.d - gizmoAxisX.lastD) * rotSensitivity / scale;
            if (gizmoAxisY.selected)
                adjust.y = -(gizmoAxisY.d - gizmoAxisY.lastD) * rotSensitivity / scale;
            if (gizmoAxisZ.selected)
                adjust.z = (gizmoAxisZ.d - gizmoAxisZ.lastD) * rotSensitivity / scale;

            moved = RotateNodes(adjust);
        }
        else if (editMode == EDIT_SCALE)
        {
            Vector3 adjust(0, 0, 0);
            if (gizmoAxisX.selected)
                adjust += Vector3(1, 0, 0) * (gizmoAxisX.t - gizmoAxisX.lastT);
            if (gizmoAxisY.selected)
                adjust += Vector3(0, 1, 0) * (gizmoAxisY.t - gizmoAxisY.lastT);
            if (gizmoAxisZ.selected)
                adjust += Vector3(0, 0, 1) * (gizmoAxisZ.t - gizmoAxisZ.lastT);

            // Special handling for uniform scale: use the unmodified X-axis movement only
            if (editMode == EDIT_SCALE && gizmoAxisX.selected && gizmoAxisY.selected && gizmoAxisZ.selected)
            {
                float x = gizmoAxisX.t - gizmoAxisX.lastT;
                adjust = Vector3(x, x, x);
            }

            moved = ScaleNodes(adjust);
        }

        if (moved)
        {
            GizmoMoved();
            UpdateNodeAttributes();
        }
    }
}

bool IsGizmoSelected()
{
    return gizmo !is null && gizmo.enabled && (gizmoAxisX.selected || gizmoAxisY.selected || gizmoAxisZ.selected);
}

bool MoveNodes(Vector3 adjust)
{
    bool moved = false;

    if (adjust.length > M_EPSILON)
    {
        for (uint i = 0; i < editNodes.length; ++i)
        {
            Node@ node = editNodes[i];
            Vector3 nodeAdjust = adjust;
            if (axisMode == AXIS_LOCAL && editNodes.length == 1)
                nodeAdjust = node.worldRotation * nodeAdjust;

            Vector3 worldPos = node.worldPosition;
            Vector3 oldPos = node.position;

            if (!moveSnap)
                worldPos += nodeAdjust;
            else
            {
                if (nodeAdjust.x != 0)
                {
                    worldPos.x += nodeAdjust.x * moveStep;
                    worldPos.x = Floor(worldPos.x / moveStep + 0.5) * moveStep;
                }
                if (nodeAdjust.y != 0)
                {
                    worldPos.y += nodeAdjust.y * moveStep;
                    worldPos.y = Floor(worldPos.y / moveStep + 0.5) * moveStep;
                }
                if (nodeAdjust.z != 0)
                {
                    worldPos.z += nodeAdjust.z * moveStep;
                    worldPos.z = Floor(worldPos.z / moveStep + 0.5) * moveStep;
                }
            }

            if (node.parent is null)
                node.position = worldPos;
            else
                node.position = node.parent.WorldToLocal(worldPos);

            if (node.position != oldPos)
                moved = true;
        }
    }

    return moved;
}

bool RotateNodes(Vector3 adjust)
{
    bool moved = false;

    if (rotateSnap)
    {
        adjust.x = Floor(adjust.x / rotateStep + 0.5) * rotateStep;
        adjust.y = Floor(adjust.y / rotateStep + 0.5) * rotateStep;
        adjust.z = Floor(adjust.z / rotateStep + 0.5) * rotateStep;
    }

    if (adjust.length > M_EPSILON)
    {
        moved = true;

        for (uint i = 0; i < editNodes.length; ++i)
        {
            Node@ node = editNodes[i];
            Quaternion rotQuat(adjust);
            if (axisMode == AXIS_LOCAL && editNodes.length == 1)
                node.rotation = node.rotation * rotQuat;
            else
            {
                Vector3 offset = node.worldPosition - gizmoAxisX.axisRay.origin;
                if (node.parent !is null && node.parent.worldRotation != Quaternion(1, 0, 0, 0))
                    rotQuat = node.parent.worldRotation.Inverse() * rotQuat * node.parent.worldRotation;
                node.rotation = rotQuat * node.rotation;
                Vector3 newPosition = gizmoAxisX.axisRay.origin + rotQuat * offset;
                if (node.parent !is null)
                    newPosition = node.parent.WorldToLocal(newPosition);
                node.position = newPosition;
            }
        }
    }

    return moved;
}

bool ScaleNodes(Vector3 adjust)
{
    bool moved = false;

    if (adjust.length > M_EPSILON)
    {
        for (uint i = 0; i < editNodes.length; ++i)
        {
            Node@ node = editNodes[i];

            Vector3 scale = node.scale;
            Vector3 oldScale = scale;

            if (!scaleSnap)
                scale += adjust;
            else
            {
                if (adjust.x != 0)
                {
                    scale.x += adjust.x * scaleStep;
                    scale.x = Floor(scale.x / scaleStep + 0.5) * scaleStep;
                }
                if (adjust.y != 0)
                {
                    scale.y += adjust.y * scaleStep;
                    scale.y = Floor(scale.y / scaleStep + 0.5) * scaleStep;
                }
                if (adjust.z != 0)
                {
                    scale.z += adjust.z * scaleStep;
                    scale.z = Floor(scale.z / scaleStep + 0.5) * scaleStep;
                }
            }

            if (scale != oldScale)
                moved = true;

            node.scale = scale;
        }
    }

    return moved;
}
