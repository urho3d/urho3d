// Editor debug icons
// to add new std debug icons just add IconType, IconsTypesMaterials and ComponentTypes items

enum IconsTypes 
{
    ICON_POINT_LIGHT = 0,
    ICON_SPOT_LIGHT,
    ICON_DIRECTIONAL_LIGHT,
    ICON_CAMERA,
    ICON_SOUND_SOURCE,
    ICON_SOUND_SOURCE_3D,
    ICON_SOUND_LISTENERS,
    ICON_ZONE,
    ICON_SPLINE_PATH,
    ICON_TRIGGER,
    ICON_CUSTOM_GEOMETRY,
    ICON_PARTICLE_EMITTER,
    ICON_COUNT
}

enum IconsColorType 
{
    ICON_COLOR_DEFAULT = 0,
    ICON_COLOR_SPLINE_PATH_BEGIN,
    ICON_COLOR_SPLINE_PATH_END
}

Array<Color> debugIconsColors = { Color(1,1,1) , Color(1,1,0), Color(0,1,0) };

Array<String> iconsTypesMaterials = {"DebugIconPointLight.xml",
                                     "DebugIconSpotLight.xml",
                                     "DebugIconLight.xml",
                                     "DebugIconCamera.xml",
                                     "DebugIconSoundSource.xml",
                                     "DebugIconSoundSource.xml",
                                     "DebugIconSoundListener.xml",
                                     "DebugIconZone.xml",
                                     "DebugIconSplinePathPoint.xml",
                                     "DebugIconCollisionTrigger.xml",
                                     "DebugIconCustomGeometry.xml",
                                     "DebugIconParticleEmitter.xml"};

Array<String> componentTypes = {"Light",
                                "Light",
                                "Light",
                                "Camera",
                                "SoundSource",
                                "SoundSource3D",
                                "SoundListener",
                                "Zone",
                                "SplinePath",
                                "RigidBody",
                                "CustomGeometry",
                                "ParticleEmitter"};

Array<BillboardSet@> debugIconsSet(ICON_COUNT);
Node@ debugIconsNode = null;
int stepDebugIconsUpdate = 100; //ms
uint timeToNextDebugIconsUpdate = 0;
int stepDebugIconsUpdateSplinePath = 1000; //ms
uint timeToNextDebugIconsUpdateSplinePath = 0;
const int splinePathResolution = 16;
const float splineStep = 1.0f / splinePathResolution;
bool debugIconsShow = true;
Vector2 debugIconsSize = Vector2(64, 64);
Vector2 debugIconsSizeSmall = debugIconsSize / 1.5;
VariantMap debugIconsPlacement;
const int debugIconsPlacementIndent = 1.0;
const float debugIconsOrthoDistance = 15.0;
const float debugIconAlphaThreshold = 0.1;
const float maxDistance = 50.0;

void CreateDebugIcons(Node@ tempNode)
{
    if (editorScene is null) return;
    debugIconsSet.Resize(ICON_COUNT);
    for (int i = 0; i < ICON_COUNT; ++i)
    {
        debugIconsSet[i] = tempNode.CreateComponent("BillboardSet");
        debugIconsSet[i].material = cache.GetResource("Material", "Materials/Editor/" + iconsTypesMaterials[i]);
        debugIconsSet[i].sorted = true;
        debugIconsSet[i].temporary = true;
        debugIconsSet[i].fixedScreenSize = true;
        debugIconsSet[i].viewMask = 0x80000000;
    }
}

void UpdateViewDebugIcons()
{
    if (editorScene is null || timeToNextDebugIconsUpdate > time.systemTime) return;

    debugIconsNode = editorScene.GetChild("DebugIconsContainer", true);

    if (debugIconsNode is null) 
    {
        debugIconsNode = editorScene.CreateChild("DebugIconsContainer", LOCAL);
        debugIconsNode.temporary = true;
    }
    // Checkout if debugIconsNode do not have any BBS component, add all at once
    BillboardSet@ isBSExist = debugIconsNode.GetComponent("BillboardSet");
    if (isBSExist is null)
        CreateDebugIcons(debugIconsNode);

    if (debugIconsSet[ICON_POINT_LIGHT] !is null)
    {
        for (int i = 0; i < ICON_COUNT; ++i)
            debugIconsSet[i].enabled = debugIconsShow;
    }

    if (debugIconsShow == false) return;

    Vector3 camPos = activeViewport.cameraNode.worldPosition;
    bool isOrthographic = activeViewport.camera.orthographic;
    debugIconsPlacement.Clear();

    for (int iconType = 0; iconType < ICON_COUNT; ++iconType)
    {
        if (debugIconsSet[iconType] !is null)
        {
            // SplinePath update resolution
            if (iconType == ICON_SPLINE_PATH && timeToNextDebugIconsUpdateSplinePath > time.systemTime)
                continue;

            Array<Node@> nodes = editorScene.GetChildrenWithComponent(componentTypes[iconType], true);

            // Clear old data
            if (iconType == ICON_SPLINE_PATH)
                ClearCommit(ICON_SPLINE_PATH, ICON_SPLINE_PATH + 1, nodes.length * splinePathResolution);
            else if (iconType == ICON_POINT_LIGHT || iconType == ICON_SPOT_LIGHT || iconType == ICON_DIRECTIONAL_LIGHT)
                ClearCommit(ICON_POINT_LIGHT, ICON_DIRECTIONAL_LIGHT + 1, nodes.length);
            else
                ClearCommit(iconType, iconType + 1, nodes.length);

            if (nodes.length > 0)
            {
                // Fill with new data
                for (uint i = 0; i < nodes.length; ++i)
                {
                    Component@ component = nodes[i].GetComponent(componentTypes[iconType]);
                    if (component is null) continue;

                    Color finalIconColor = debugIconsColors[ICON_COLOR_DEFAULT];
                    float distance = (camPos - nodes[i].worldPosition).length;
                    if (isOrthographic)
                        distance = debugIconsOrthoDistance;
                    int iconsOffset = debugIconsPlacement[StringHash(nodes[i].id)].GetInt();
                    float iconsYPos = 0;

                    if (iconType == ICON_SPLINE_PATH)
                    {
                        SplinePath@ sp = cast<SplinePath>(component);
                        if (sp !is null)
                        {
                            if (sp.length > 0.01f)
                            {
                                for (int step = 0; step < splinePathResolution; step++)
                                {
                                    int index = (i * splinePathResolution) + step;
                                    Vector3 splinePoint = sp.GetPoint(splineStep * step);
                                    Billboard@ bb = debugIconsSet[ICON_SPLINE_PATH].billboards[index];
                                    float stepDistance = (camPos - splinePoint).length;
                                    if (isOrthographic)
                                        stepDistance = debugIconsOrthoDistance;

                                    if (step == 0) // SplinePath start
                                    {
                                        bb.color = debugIconsColors[ICON_COLOR_SPLINE_PATH_BEGIN];
                                        bb.size = debugIconsSize;
                                        bb.position = splinePoint;
                                    }
                                    else if ((step+1) >= (splinePathResolution - splineStep)) // SplinePath end
                                    {
                                        bb.color = debugIconsColors[ICON_COLOR_SPLINE_PATH_END];
                                        bb.size = debugIconsSize;
                                        bb.position = splinePoint;
                                    }
                                    else // SplinePath middle points
                                    {
                                        bb.color = finalIconColor;
                                        bb.size = debugIconsSizeSmall;
                                        bb.position = splinePoint;
                                    }
                                    bb.enabled = sp.enabled;
                                    // Blend Icon relatively by distance to it
                                    bb.color = Color(bb.color.r, bb.color.g, bb.color.b, 1.2f - 1.0f / (maxDistance / stepDistance));
                                    if (bb.color.a < debugIconAlphaThreshold)
                                        bb.enabled = false;
                                }
                            }
                        }
                    }
                    else
                    {
                        Billboard@ bb = debugIconsSet[iconType].billboards[i];

                        if (iconType == ICON_TRIGGER)
                        {
                            RigidBody@ rigidbody = cast<RigidBody>(component);
                            if (rigidbody !is null)
                            {
                                if (rigidbody.trigger == false)
                                    continue;
                            }
                        }
                        else if (iconType == ICON_POINT_LIGHT || iconType == ICON_SPOT_LIGHT || iconType == ICON_DIRECTIONAL_LIGHT)
                        {
                            Light@ light = cast<Light>(component);
                            if (light !is null)
                            {
                                if (light.lightType == LIGHT_POINT)
                                    bb = debugIconsSet[ICON_POINT_LIGHT].billboards[i];
                                else if (light.lightType == LIGHT_DIRECTIONAL)
                                    bb = debugIconsSet[ICON_DIRECTIONAL_LIGHT].billboards[i];
                                else if (light.lightType == LIGHT_SPOT)
                                    bb = debugIconsSet[ICON_SPOT_LIGHT].billboards[i];

                                finalIconColor = light.effectiveColor;
                            }
                        }

                        bb.position = nodes[i].worldPosition;
                        bb.size = debugIconsSize;

                        // Blend Icon relatively by distance to it
                        bb.color = Color(finalIconColor.r, finalIconColor.g, finalIconColor.b, 1.2f - 1.0f / (maxDistance / distance));
                        bb.enabled = component.enabled;
                        // Discard billboard if it almost transparent
                        if (bb.color.a < debugIconAlphaThreshold)
                            bb.enabled = false;
                        IncrementIconPlacement(bb.enabled, nodes[i], 1);
                    }
                }
                Commit(iconType, iconType+1);
                // SplinePath update resolution
                if (iconType == ICON_SPLINE_PATH)
                    timeToNextDebugIconsUpdateSplinePath = time.systemTime + stepDebugIconsUpdateSplinePath;
            }
        }
    }
    timeToNextDebugIconsUpdate = time.systemTime + stepDebugIconsUpdate;
}

void ClearCommit(int begin, int end, int newLength)
{
    for (int i = begin; i < end; ++i)
    {
        BillboardSet@ iconSet = debugIconsSet[i];
        iconSet.numBillboards = newLength;

        for (int j = 0; j < newLength; ++j)
        {
            Billboard@ bb = iconSet.billboards[j];
            bb.enabled = false;
        }

        iconSet.Commit();
    }
}

void Commit(int begin, int end)
{
    for (int i = begin; i < end; ++i)
    {
        debugIconsSet[i].Commit();
    }
}

void IncrementIconPlacement(bool componentEnabled, Node@ node, int offset)
{
    if (componentEnabled == true)
    {
        int oldPlacement = debugIconsPlacement[StringHash(node.id)].GetInt();
        debugIconsPlacement[StringHash(node.id)] = Variant(oldPlacement + offset);
    }
}