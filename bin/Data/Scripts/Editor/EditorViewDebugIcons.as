// Editor debug icons

BillboardSet@ debugIconsSetDirectionalLights;
BillboardSet@ debugIconsSetSpotLights;
BillboardSet@ debugIconsSetPointLights;
BillboardSet@ debugIconsSetCameras;
BillboardSet@ debugIconsSetSoundSources;
BillboardSet@ debugIconsSetSoundSources3D;
BillboardSet@ debugIconsSetSoundListeners;
BillboardSet@ debugIconsSetZones;
BillboardSet@ debugIconsSetSplinesPoints;
BillboardSet@ debugIconsSetTriggers;
BillboardSet@ debugIconsSetCustomGeometry;
BillboardSet@ debugIconsSetParticleEmitters;




Node@ debugIconsNode = null;
int stepDebugIconsUpdate = 60; //ms
int timeToNextDebugIconsUpdate = 0;
int stepDebugIconsUpdateSplinePath = 500; //ms
int timeToNextDebugIconsUpdateSplinePath = 0;
const int splinePathResolution = 16;
bool debugIconsShow = true;
bool supressDebugIconsShow = false;
Vector2 debugIconsSize = Vector2(0.025, 0.025);
Vector2 debugIconsSizeSmall = debugIconsSize / 1.5;
Vector2 debugIconsSizeBig = debugIconsSize * 1.5;



void CreateDebugIcons() 
{
    if (editorScene is null) return;
    
    debugIconsSetDirectionalLights = debugIconsNode.CreateComponent("BillboardSet");
    debugIconsSetDirectionalLights.material = cache.GetResource("Material", "Materials/Editor/DebugIconLight.xml");
    debugIconsSetDirectionalLights.material.renderOrder = 255;
    debugIconsSetDirectionalLights.sorted = true;
    debugIconsSetDirectionalLights.temporary = true;
    debugIconsSetDirectionalLights.viewMask = 0x80000000;
    
    debugIconsSetSpotLights = debugIconsNode.CreateComponent("BillboardSet");
    debugIconsSetSpotLights.material = cache.GetResource("Material", "Materials/Editor/DebugIconSpotLight.xml");
    debugIconsSetSpotLights.material.renderOrder = 255;
    debugIconsSetSpotLights.sorted = true;
    debugIconsSetSpotLights.temporary = true;
    debugIconsSetSpotLights.viewMask = 0x80000000;
    
    debugIconsSetPointLights = debugIconsNode.CreateComponent("BillboardSet");
    debugIconsSetPointLights.material = cache.GetResource("Material", "Materials/Editor/DebugIconPointLight.xml");
    debugIconsSetPointLights.material.renderOrder = 255;
    debugIconsSetPointLights.sorted = true;
    debugIconsSetPointLights.temporary = true;
    debugIconsSetPointLights.viewMask = 0x80000000;
        
    debugIconsSetCameras = debugIconsNode.CreateComponent("BillboardSet");
    debugIconsSetCameras.material = cache.GetResource("Material", "Materials/Editor/DebugIconCamera.xml");
    debugIconsSetCameras.material.renderOrder = 255;
    debugIconsSetCameras.sorted = true;
    debugIconsSetCameras.temporary = true;
    debugIconsSetCameras.viewMask = 0x80000000;
    
    debugIconsSetSoundSources = debugIconsNode.CreateComponent("BillboardSet");
    debugIconsSetSoundSources.material = cache.GetResource("Material", "Materials/Editor/DebugIconSoundSource.xml");
    debugIconsSetSoundSources.material.renderOrder = 255;
    debugIconsSetSoundSources.sorted = true;
    debugIconsSetSoundSources.temporary = true;
    debugIconsSetSoundSources.viewMask = 0x80000000;

    debugIconsSetSoundSources3D = debugIconsNode.CreateComponent("BillboardSet");
    debugIconsSetSoundSources3D.material = cache.GetResource("Material", "Materials/Editor/DebugIconSoundSource.xml");
    debugIconsSetSoundSources3D.material.renderOrder = 255;
    debugIconsSetSoundSources3D.sorted = true;
    debugIconsSetSoundSources3D.temporary = true;
    debugIconsSetSoundSources3D.viewMask = 0x80000000;
    
    debugIconsSetSoundListeners = debugIconsNode.CreateComponent("BillboardSet");
    debugIconsSetSoundListeners.material = cache.GetResource("Material", "Materials/Editor/DebugIconSoundListener.xml");
    debugIconsSetSoundListeners.material.renderOrder = 255;
    debugIconsSetSoundListeners.sorted = true;
    debugIconsSetSoundListeners.temporary = true;
    debugIconsSetSoundListeners.viewMask = 0x80000000;
    
    debugIconsSetZones = debugIconsNode.CreateComponent("BillboardSet");
    debugIconsSetZones.material = cache.GetResource("Material", "Materials/Editor/DebugIconZone.xml");
    debugIconsSetZones.material.renderOrder = 255;
    debugIconsSetZones.sorted = true;
    debugIconsSetZones.temporary = true;
    debugIconsSetZones.viewMask = 0x80000000;
    
    debugIconsSetSplinesPoints = debugIconsNode.CreateComponent("BillboardSet");
    debugIconsSetSplinesPoints.material = cache.GetResource("Material", "Materials/Editor/DebugIconSplinePathPoint.xml");
    debugIconsSetSplinesPoints.material.renderOrder = 255;
    debugIconsSetSplinesPoints.sorted = true;
    debugIconsSetSplinesPoints.temporary = true;
    debugIconsSetSplinesPoints.viewMask = 0x80000000;
    
    debugIconsSetTriggers = debugIconsNode.CreateComponent("BillboardSet");
    debugIconsSetTriggers.material = cache.GetResource("Material", "Materials/Editor/DebugIconCollisionTrigger.xml");
    debugIconsSetTriggers.material.renderOrder = 255;
    debugIconsSetTriggers.sorted = true;
    debugIconsSetTriggers.temporary = true;
    debugIconsSetTriggers.viewMask = 0x80000000;
    
    debugIconsSetCustomGeometry = debugIconsNode.CreateComponent("BillboardSet");
    debugIconsSetCustomGeometry.material = cache.GetResource("Material", "Materials/Editor/DebugIconCustomGeometry.xml");
    debugIconsSetCustomGeometry.material.renderOrder = 255;
    debugIconsSetCustomGeometry.sorted = true;
    debugIconsSetCustomGeometry.temporary = true;
    debugIconsSetCustomGeometry.viewMask = 0x80000000;
    
    debugIconsSetParticleEmitters = debugIconsNode.CreateComponent("BillboardSet");
    debugIconsSetParticleEmitters.material = cache.GetResource("Material", "Materials/Editor/DebugIconParticleEmitter.xml");
    debugIconsSetParticleEmitters.material.renderOrder = 255;
    debugIconsSetParticleEmitters.sorted = true;
    debugIconsSetParticleEmitters.temporary = true;
    debugIconsSetParticleEmitters.viewMask = 0x80000000; 


}

void UpdateViewDebugIcons() 
{
    if (editorScene is null) return;
    
    if (timeToNextDebugIconsUpdate > time.systemTime) return; 
    
    debugIconsNode = editorScene.GetChild("DebugIconsContainer", true);
    
    
    if (debugIconsNode is null) 
    {
        debugIconsNode = editorScene.CreateChild("DebugIconsContainer", LOCAL);
        debugIconsNode.temporary = true;
    } 
    
    
    // Checkout if debugIconsNode do not have any BBS component, add they at once
    BillboardSet@ bbs = debugIconsNode.GetComponent("BillboardSet");
    
    if (bbs is null) 
    {
        CreateDebugIcons();
    }
        
    if (debugIconsSetPointLights !is null) 
    {
        debugIconsSetDirectionalLights.enabled = debugIconsShow;
        debugIconsSetSpotLights.enabled = debugIconsShow;
        debugIconsSetPointLights.enabled = debugIconsShow;
        debugIconsSetCameras.enabled = debugIconsShow;
        debugIconsSetSoundSources.enabled = debugIconsShow;
        debugIconsSetSoundSources3D.enabled = debugIconsShow;
        debugIconsSetSoundListeners.enabled = debugIconsShow;
        debugIconsSetZones.enabled = debugIconsShow;
        debugIconsSetSplinesPoints.enabled = debugIconsShow;
        debugIconsSetTriggers.enabled = debugIconsShow;
        debugIconsSetCustomGeometry.enabled = debugIconsShow;
        debugIconsSetParticleEmitters.enabled = debugIconsShow;
           
    }
    
    if (debugIconsShow == false) return; 
    
    Vector3 camPos = activeViewport.cameraNode.worldPosition;
        
    if (debugIconsSetPointLights !is null) 
    {
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
    
    
    if (timeToNextDebugIconsUpdateSplinePath < time.systemTime) 
    {
        if (debugIconsSetSplinesPoints !is null) 
        {
            // Collect all scene's SplinePath and add it
            Array<Node@> nodes = editorScene.GetChildrenWithComponent("SplinePath", true);
            
            if (nodes.length > 0) 
            {
                debugIconsSetSplinesPoints.numBillboards = nodes.length * splinePathResolution;
                
                float splineStep = 1.0f / splinePathResolution;
                                        
                for(int i=0; i < nodes.length; i++) 
                {
                    
                    SplinePath@ sp = nodes[i].GetComponent("SplinePath");
                    if(sp !is null) 
                    {
                        Vector3 splinePoint;
                        // Create path
                        for(int step=0; step < splinePathResolution; step++) 
                        {
                            splinePoint = sp.GetPoint(splineStep * step);
                            
                            float distance = (camPos - splinePoint).length;
                            int index = (i * splinePathResolution) + step;    
                            Billboard@ bb = debugIconsSetSplinesPoints.billboards[index];
                            bb.position = splinePoint;
                            bb.size = debugIconsSizeSmall * distance;
                            
                            if (step == 0) 
                            {
                                bb.color = Color(1,1,0);
                                bb.size = debugIconsSize * distance;
                            }
                            else if ((step+1) >= (splinePathResolution - splineStep))
                            {
                                bb.color = Color(0,1,0);
                                bb.size = debugIconsSize * distance;
                            }
                            else
                            {
                                bb.color = Color(1,1,1);
                                bb.size = debugIconsSizeSmall * distance;
                            }    
                            bb.enabled = sp.enabled;
                        }
                    }                                       
                }
                
                debugIconsSetSplinesPoints.Commit();   
            }
        }
        
        if (debugIconsSetTriggers !is null) 
        {
            // Collect all scene's RigidBody and add it
            Array<Node@> nodes = editorScene.GetChildrenWithComponent("RigidBody", true);
            
            if (nodes.length > 0) 
            {
                debugIconsSetTriggers.numBillboards = nodes.length;
                for (int i=0;i<nodes.length; i++) 
                {
                    RigidBody@ rigidbody = nodes[i].GetComponent("RigidBody");
                    if (rigidbody.trigger) 
                    {
                        Billboard@ bb = debugIconsSetTriggers.billboards[i];
                        bb.position = nodes[i].worldPosition;
                        float distance = (camPos - nodes[i].worldPosition).length;
                        bb.size = debugIconsSize * distance;
                        bb.enabled = rigidbody.enabled;
                    }
                }
                
                debugIconsSetTriggers.Commit();   
            }
        }
        
        if (debugIconsSetCustomGeometry !is null) 
        {
            // Collect all scene's CustomGeometry and add it
            Array<Node@> nodes = editorScene.GetChildrenWithComponent("CustomGeometry", true);
            
            if (nodes.length > 0) 
            {
                debugIconsSetCustomGeometry.numBillboards = nodes.length;
                for (int i=0;i<nodes.length; i++) 
                {
                    CustomGeometry@ customGeometry = nodes[i].GetComponent("CustomGeometry");

                    Billboard@ bb = debugIconsSetCustomGeometry.billboards[i];
                    bb.position = nodes[i].worldPosition;
                    float distance = (camPos - nodes[i].worldPosition).length;
                    bb.size = debugIconsSize * distance;
                    bb.enabled = customGeometry.enabled;
                }
                
                debugIconsSetCustomGeometry.Commit();   
            }
        }
        
        if (debugIconsSetParticleEmitters !is null) 
        {
            // Collect all scene's ParticleEmitter and add it
            Array<Node@> nodes = editorScene.GetChildrenWithComponent("ParticleEmitter", true);
            
            if (nodes.length > 0) 
            {
                debugIconsSetParticleEmitters.numBillboards = nodes.length;
                for (int i=0;i<nodes.length; i++) 
                {
                    ParticleEmitter@ particleEmitter = nodes[i].GetComponent("ParticleEmitter");

                    Billboard@ bb = debugIconsSetParticleEmitters.billboards[i];
                    bb.position = nodes[i].worldPosition;
                    float distance = (camPos - nodes[i].worldPosition).length;
                    bb.size = debugIconsSizeBig * distance;
                    bb.enabled = particleEmitter.enabled;
                }
                
                debugIconsSetParticleEmitters.Commit();   
            }
        }
        
        timeToNextDebugIconsUpdateSplinePath = time.systemTime + stepDebugIconsUpdateSplinePath;
    }
    
    timeToNextDebugIconsUpdate = time.systemTime + stepDebugIconsUpdate;
}