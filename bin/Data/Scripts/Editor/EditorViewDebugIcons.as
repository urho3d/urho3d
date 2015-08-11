// Editor debug icons

BillboardSet@ debugIconsSetDirectionalLights;
BillboardSet@ debugIconsSetSpotLights;
BillboardSet@ debugIconsSetPointLights;
BillboardSet@ debugIconsSetCameras;
BillboardSet@ debugIconsSetSoundSources;
BillboardSet@ debugIconsSetSoundSources3D;
BillboardSet@ debugIconsSetSoundListeners;
BillboardSet@ debugIconsSetZones;


int stepDebugIconsUpdate = 30; //ms
int timeToNextDebugIconsUpdate = 0;
bool debugIconsShow = true;
Vector2 debugIconsSize = Vector2(0.025, 0.025);

void CreateDebugIcons() 
{
    if (editorScene is null) return;
     
    debugIconsSetDirectionalLights = editorScene.CreateComponent("BillboardSet");
    debugIconsSetDirectionalLights.material = cache.GetResource("Material", "Materials/Editor/DebugIconLight.xml");
    debugIconsSetDirectionalLights.material.renderOrder = 255;
    debugIconsSetDirectionalLights.sorted = true;
    debugIconsSetDirectionalLights.temporary = true;
    debugIconsSetDirectionalLights.viewMask = 0x80000000;

    debugIconsSetSpotLights = editorScene.CreateComponent("BillboardSet");
    debugIconsSetSpotLights.material = cache.GetResource("Material", "Materials/Editor/DebugIconSpotLight.xml");
    debugIconsSetSpotLights.material.renderOrder = 255;
    debugIconsSetSpotLights.sorted = true;
    debugIconsSetSpotLights.temporary = true;
    debugIconsSetSpotLights.viewMask = 0x80000000;
    
    debugIconsSetPointLights = editorScene.CreateComponent("BillboardSet");
    debugIconsSetPointLights.material = cache.GetResource("Material", "Materials/Editor/DebugIconPointLight.xml");
    debugIconsSetPointLights.material.renderOrder = 255;
    debugIconsSetPointLights.sorted = true;
    debugIconsSetPointLights.temporary = true;
    debugIconsSetPointLights.viewMask = 0x80000000;
        
    debugIconsSetCameras = editorScene.CreateComponent("BillboardSet");
    debugIconsSetCameras.material = cache.GetResource("Material", "Materials/Editor/DebugIconCamera.xml");
    debugIconsSetCameras.material.renderOrder = 255;
    debugIconsSetCameras.sorted = true;
    debugIconsSetCameras.temporary = true;
    debugIconsSetCameras.viewMask = 0x80000000;
    
    debugIconsSetSoundSources = editorScene.CreateComponent("BillboardSet");
    debugIconsSetSoundSources.material = cache.GetResource("Material", "Materials/Editor/DebugIconSoundSource.xml");
    debugIconsSetSoundSources.material.renderOrder = 255;
    debugIconsSetSoundSources.sorted = true;
    debugIconsSetSoundSources.temporary = true;
    debugIconsSetSoundSources.viewMask = 0x80000000;

    debugIconsSetSoundSources3D = editorScene.CreateComponent("BillboardSet");
    debugIconsSetSoundSources3D.material = cache.GetResource("Material", "Materials/Editor/DebugIconSoundSource.xml");
    debugIconsSetSoundSources3D.material.renderOrder = 255;
    debugIconsSetSoundSources3D.sorted = true;
    debugIconsSetSoundSources3D.temporary = true;
    debugIconsSetSoundSources3D.viewMask = 0x80000000;
    
    debugIconsSetSoundListeners = editorScene.CreateComponent("BillboardSet");
    debugIconsSetSoundListeners.material = cache.GetResource("Material", "Materials/Editor/DebugIconSoundListener.xml");
    debugIconsSetSoundListeners.material.renderOrder = 255;
    debugIconsSetSoundListeners.sorted = true;
    debugIconsSetSoundListeners.temporary = true;
    debugIconsSetSoundListeners.viewMask = 0x80000000;
    
    debugIconsSetZones = editorScene.CreateComponent("BillboardSet");
    debugIconsSetZones.material = cache.GetResource("Material", "Materials/Editor/DebugIconZone.xml");
    debugIconsSetZones.material.renderOrder = 255;
    debugIconsSetZones.sorted = true;
    debugIconsSetZones.temporary = true;
    debugIconsSetZones.viewMask = 0x80000000;
    
}

void UpdateViewDebugIcons() 
{
    if (timeToNextDebugIconsUpdate > time.systemTime) return; 
    
    if (editorScene is null) return;
    // Checkout if scene do not have BBS component, add it once
    BillboardSet@ bbs = editorScene.GetComponent("BillboardSet");
    if (bbs is null) 
    {
        CreateDebugIcons();
    }
    
    Vector3 camPos = cameraNode.worldPosition;
        
    if (debugIconsSetPointLights !is null) 
    {
        debugIconsSetDirectionalLights.enabled = debugIconsShow;
        debugIconsSetSpotLights.enabled = debugIconsShow;
        debugIconsSetPointLights.enabled = debugIconsShow;
        
        Array<Node@> nodes = editorScene.GetChildrenWithComponent("Light", true);
        
        if (nodes.length > 0) 
        {
            debugIconsSetDirectionalLights.numBillboards = 0;
            debugIconsSetSpotLights.numBillboards = 0;
            debugIconsSetPointLights.numBillboards = 0;
            
            debugIconsSetPointLights.Commit();
            debugIconsSetSpotLights.Commit();
            debugIconsSetDirectionalLights.Commit();
            
            
            debugIconsSetDirectionalLights.numBillboards = nodes.length;
            debugIconsSetSpotLights.numBillboards = nodes.length;
            debugIconsSetPointLights.numBillboards = nodes.length;
            
            for (int i=0;i<nodes.length; i++) 
            {
                Light@ light = nodes[i].GetComponent("Light");
                
                if (light.lightType == LIGHT_POINT) 
                {
                    Billboard@ bb = debugIconsSetPointLights.billboards[i];
                    bb.position = nodes[i].worldPosition;
                    bb.color = light.effectiveColor;
                    float distance = (camPos - nodes[i].worldPosition).length;
                    bb.size = debugIconsSize * distance;
                    bb.enabled = true;
                }
                else if (light.lightType == LIGHT_DIRECTIONAL) 
                {
                    Billboard@ bb = debugIconsSetDirectionalLights.billboards[i];
                    bb.position = nodes[i].worldPosition;
                    bb.color = light.effectiveColor;
                    float distance = (camPos - nodes[i].worldPosition).length;
                    bb.size = debugIconsSize * distance;
                    bb.enabled = true;
                }
                else if (light.lightType == LIGHT_SPOT) 
                {
                    Billboard@ bb = debugIconsSetSpotLights.billboards[i];
                    bb.position = nodes[i].worldPosition;
                    bb.color = light.effectiveColor;
                    float distance = (camPos - nodes[i].worldPosition).length;
                    bb.size = debugIconsSize * distance;
                    bb.enabled = true;
                }
            }
            
            debugIconsSetPointLights.Commit();
            debugIconsSetSpotLights.Commit();
            debugIconsSetDirectionalLights.Commit();
            
        }
    }
    
    
    if (debugIconsSetCameras !is null) 
    {
        debugIconsSetCameras.enabled = debugIconsShow;
        Array<Node@> nodes = editorScene.GetChildrenWithComponent("Camera", true);

        if (nodes.length > 0) 
        {
            debugIconsSetCameras.numBillboards = nodes.length;
            for (int i=0;i<nodes.length; i++) 
            {
                Camera@ camera = nodes[i].GetComponent("Camera");
                Billboard@ bb = debugIconsSetCameras.billboards[i];
                bb.position = nodes[i].worldPosition;
                
                // if mainCamera enough closer to selected camera then make bb size relative to distance
                float distance = (camPos - nodes[i].worldPosition).length;
                bb.size = debugIconsSize * distance;
                
                bb.enabled = true;
            }
            
            debugIconsSetCameras.Commit();
        }
    }
    
    if (debugIconsSetSoundSources !is null) 
    {
        debugIconsSetSoundSources.enabled = debugIconsShow;
        
        Array<Node@> nodes = editorScene.GetChildrenWithComponent("SoundSource", true);

        if (nodes.length > 0) 
        {
            debugIconsSetSoundSources.numBillboards = nodes.length;
            for (int i=0;i<nodes.length; i++) 
            {
                Component@ component = nodes[i].GetComponent("SoundSource");
                Billboard@ bb = debugIconsSetSoundSources.billboards[i];
                bb.position = nodes[i].worldPosition;
                float distance = (camPos - nodes[i].worldPosition).length;
                bb.size = debugIconsSize * distance;
                bb.enabled = component.enabled;
            }
            
            debugIconsSetSoundSources.Commit();
        }        
    }
    
    if (debugIconsSetSoundSources3D !is null) 
    {
        debugIconsSetSoundSources3D.enabled = debugIconsShow;
        
        Array<Node@> nodes = editorScene.GetChildrenWithComponent("SoundSource3D", true);

        if (nodes.length > 0) 
        {
            debugIconsSetSoundSources3D.numBillboards = nodes.length;
            for (int i=0;i<nodes.length; i++) 
            {
                Component@ component = nodes[i].GetComponent("SoundSource3D");
                Billboard@ bb = debugIconsSetSoundSources3D.billboards[i];
                bb.position = nodes[i].worldPosition;
                float distance = (camPos - nodes[i].worldPosition).length;
                bb.size = debugIconsSize * distance;
                bb.enabled = component.enabled;
            }
            
            debugIconsSetSoundSources3D.Commit();
        }        
    }
    
    if (debugIconsSetSoundListeners !is null) 
    {
        debugIconsSetSoundListeners.enabled = debugIconsShow;
        Array<Node@> nodes = editorScene.GetChildrenWithComponent("SoundListener" , true);

        if (nodes.length > 0) 
        {
            debugIconsSetSoundListeners.numBillboards = nodes.length;
            for (int i=0;i<nodes.length; i++) 
            {
                Component@ component = nodes[i].GetComponent("SoundListener");
                Billboard@ bb = debugIconsSetSoundListeners.billboards[i];
                bb.position = nodes[i].worldPosition;
                float distance = (camPos - nodes[i].worldPosition).length;
                bb.size = debugIconsSize * distance;
                bb.enabled = component.enabled;
            }
            
            debugIconsSetSoundListeners.Commit();
        }        
    }
    
    if (debugIconsSetZones !is null) 
    {
        debugIconsSetZones.enabled = debugIconsShow;

        // Collect all scene's Zones and add it
        Array<Node@> nodes = editorScene.GetChildrenWithComponent("Zone", true);
        
        Zone@ zone = editorScene.GetComponent("Zone");
        if (zone !is null) 
        {
            debugIconsSetZones.numBillboards = 1;
            Billboard@ bb = debugIconsSetZones.billboards[0];
            bb.position = Vector3(0,0,0);
            float distance = (camPos - bb.position).length;
            bb.size = debugIconsSize * distance;
            //bb.color = zone.ambientColor;
            bb.enabled = zone.enabled; 
        }
        
        if (nodes.length > 0) 
        {
            debugIconsSetZones.numBillboards = 1 + nodes.length;
            for (int i=0;i<nodes.length; i++) 
            {
                Zone@ zone = nodes[i].GetComponent("Zone");
                Billboard@ bb = debugIconsSetZones.billboards[i+1];
                bb.position = nodes[i].worldPosition;
                float distance = (camPos - nodes[i].worldPosition).length;
                bb.size = debugIconsSize * distance;
                //bb.color = zone.ambientColor;
                bb.enabled = zone.enabled;
            }
            
            debugIconsSetZones.Commit();
        }
    }
      
    timeToNextDebugIconsUpdate = time.systemTime + stepDebugIconsUpdate;
}