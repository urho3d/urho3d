//Import realXtend Tundra scene file (Much missing features. Handles only everything in the same path)

void autoCollisionMesh()
{
    array<string> createdCollisions;
    
    array<Entity@> entities = editorScene.getAllEntities();
    for (uint i = 0; i < entities.size(); ++i)
    {
        StaticModel@ model = entities[i].getComponent("StaticModel");
        if (model !is null)
        {
            Model@ mesh = model.getModel();
            if (mesh !is null)
            {
                string collisionName = "Physics/" + getFileName(mesh.getName()) + ".xml";
                // Create collision file if not exist yet
                bool found = false;
                for (uint i = 0; i < createdCollisions.size(); ++i)
                {
                    if (createdCollisions[i] == collisionName)
                    {
                        found = true;
                        break;
                    }
                }
                
                if (!found)
                {
                    XMLFile collision;
                    XMLElement rootElem = collision.createRootElement("collisionshape");
                    XMLElement triangleMeshElem = rootElem.createChildElement("trianglemesh");
                    triangleMeshElem.setAttribute("name", mesh.getName());
                    
                    collision.save(File(sceneResourcePath + collisionName, FILE_WRITE));
                }
                
                // Swap around so that rigidbody gets the model's world transform, and then model can have identity
                RigidBody@ body = entities[i].createComponent("RigidBody");
                body.setPosition(model.getWorldPosition());
                body.setRotation(model.getWorldRotation());
                body.setScale(model.getWorldScale());
                model.setPosition(Vector3(0, 0, 0));
                model.setRotation(Quaternion());
                model.setScale(Vector3(1, 1, 1));
                body.addChild(model);
                body.setCollisionShape(cache.getResource("CollisionShape", collisionName));
            }
        }
        
        updateSceneWindow(false);
    }
}

void importTundraScene(string fileName)
{
    createDirectory(sceneResourcePath + "Materials");
    createDirectory(sceneResourcePath + "Models");
    createDirectory(sceneResourcePath + "Textures");
    createDirectory(sceneResourcePath + "Physics");
    
    XMLFile source;
    source.load(File(fileName, FILE_READ));
    string filePath = getPath(fileName);

    XMLElement sceneElem = source.getRootElement();
    XMLElement entityElem = sceneElem.getChildElement("entity");
    
    array<string> convertedMaterials;
    array<string> convertedMeshes;
    
    // Clear old scene, then create a zone and a directional light first
    editorScene.removeAllEntities();
    Entity@ zoneEntity = editorScene.createEntity();
    Zone@ zone = zoneEntity.createComponent("Zone");
    Light@ sunLight = zoneEntity.createComponent("Light");
    sunLight.setLightType(LIGHT_DIRECTIONAL);
    sunLight.setRotation(Quaternion(60, 30, 0));
    sunLight.setCastShadows(true);
    sunLight.setShadowCascade(CascadeParameters(3, 0.95, 0.2, 1000000));
    zone.setBoundingBox(BoundingBox(-1000, 1000));
    zone.setAmbientColor(Color(0.5, 0.5, 0.5));
    zone.setFogColor(Color(0.5, 0.7, 1.0));
    zone.setFogStart(100);
    zone.setFogEnd(500);
    
    while (entityElem.notNull())
    {
        string entityName;
        string meshName;
        Vector3 pos;
        Vector3 rot;
        Vector3 scale;
        bool castShadows = false;
        float drawDistance = 0;
        array<string> materialNames;

        XMLElement compElem = entityElem.getChildElement("component");
        while (compElem.notNull())
        {
            string compType = compElem.getAttribute("type");
            if (compType == "EC_Mesh")
            {
                meshName = getComponentAttribute(compElem, "Mesh ref");
                castShadows = getComponentAttribute(compElem, "Cast shadows").toBool();
                drawDistance = getComponentAttribute(compElem, "Draw distance").toFloat();
                materialNames = getComponentAttribute(compElem, "Mesh materials").split(';');
                processRef(meshName);
                for (uint i = 0; i < materialNames.size(); ++i)
                    processRef(materialNames[i]);
            }
            if (compType == "EC_Name")
                entityName = getComponentAttribute(compElem, "name");
            if (compType == "EC_Placeable")
            {
                array<string> coords = getComponentAttribute(compElem, "Transform").split(',');
                pos = getVector3FromStrings(coords, 0);
                rot = getVector3FromStrings(coords, 3);
                scale = getVector3FromStrings(coords, 6);
                
                // Fix coordinate system
                pos = Vector3(pos.x, pos.z, pos.y);
                rot = Vector3(rot.x, -rot.z + 180, rot.y);
                //scale = Vector3(scale.x, scale.y, scale.z);
            }
            
            compElem = compElem.getNextElement("component");
        }

        // For now we are only interested of meshes
        if (meshName.empty())
            continue;
        
        for (uint i = 0; i < materialNames.size(); ++i)
        {
            bool found = false;
            for (uint j = 0; j < convertedMaterials.size(); ++j)
            {
                if (convertedMaterials[j] == materialNames[i])
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                convertMaterial(materialNames[i], filePath);
                convertedMaterials.push(materialNames[i]);
            }
        }

        bool found = false;
        for (uint i = 0; i < convertedMeshes.size(); ++i)
        {
            if (convertedMeshes[i] == meshName)
            {
                found = true;
                break;
            }
        }
        if (!found)
            convertModel(meshName, filePath);

        Entity@ newEntity = editorScene.createEntity(entityName);
        StaticModel@ model = newEntity.createComponent("StaticModel");
        
        model.setTransform(pos, Quaternion(rot), scale);
        model.setModel(cache.getResource("Model", "Models/" + meshName.replace(".mesh", ".mdl")));
        model.setDrawDistance(drawDistance);
        model.setCastShadows(castShadows);
        for (uint i = 0; i < materialNames.size(); ++i)
            model.setMaterial(i, cache.getResource("Material", "Materials/" + materialNames[i].replace(".material", ".xml")));

        updateSceneWindow(false);
        
        entityElem = entityElem.getNextElement("entity");
    }
}

string getComponentAttribute(XMLElement compElem, string name)
{
    XMLElement attrElem = compElem.getChildElement("attribute");
    while (attrElem.notNull())
    {
        if (attrElem.getAttribute("name") == name)
            return attrElem.getAttribute("value");

        attrElem = attrElem.getNextElement("attribute");
    }

    return "";
}

Vector3 getVector3FromStrings(array<string>@ coords, uint startIndex)
{
    return Vector3(coords[startIndex].toFloat(), coords[startIndex + 1].toFloat(), coords[startIndex + 2].toFloat());
}

void processRef(string& ref)
{
    if (ref.find("local://") == 0)
        ref = ref.substr(8);
}

void convertModel(const string& in modelName, const string& in filePath)
{
    string cmdLine1 = "ogrexmlconverter.exe \"" + filePath + modelName + "\" \"" + filePath + modelName + ".xml\"";
    string cmdLine2 = getExecutableDirectory() + "OgreImporter.exe \"" + filePath + modelName + ".xml\" \"" + sceneResourcePath + "Models/" + modelName.replace(".mesh", ".mdl") + "\" -a -t";
    
    if (!fileExists(filePath + modelName + ".xml"))
        systemCommand(cmdLine1.replace('/', '\\'));
    if (!fileExists(sceneResourcePath + "Models/" + modelName.replace(".mesh", ".mdl")))
        systemCommand(cmdLine2.replace('/', '\\'));
}

void convertMaterial(const string& in materialName, const string& in filePath)
{
    string fileName = filePath + materialName;
    string outFileName = sceneResourcePath + "Materials/" + getFileName(materialName) + ".xml";

    if (!fileExists(fileName))
        return;

    bool mask = false;
    bool twoSided = false;
    string textureName;

    File file(fileName, FILE_READ);
    while (!file.isEof())
    {
        string line = file.readLine().trim();
        if (line.find("alpha_rejection") == 0)
            mask = true;
        if (line.find("cull_hardware none") == 0)
            twoSided = true;
        if (line.find("texture ") == 0)
        {
            textureName = line.substr(8);
            processRef(textureName);
        }
    }

    XMLFile outMat;
    XMLElement rootElem = outMat.createRootElement("material");
    
    XMLElement baseElem = rootElem.createChildElement("base");
    string baseName = mask ? "Materials/DefaultDiffAlphaMask.xml" : "Materials/DefaultDiff.xml";
    if (twoSided)
        baseName = baseName.replace(".xml", "TS.xml");
    baseElem.setAttribute("name", baseName);
    
    
    XMLElement techniqueElem = rootElem.createChildElement("technique");
    
    if (!textureName.empty())
    {
        XMLElement textureElem = techniqueElem.createChildElement("texture");
        textureElem.setAttribute("unit", "diffuse");
        textureElem.setAttribute("name", "Textures/" + textureName);

        File outFile(outFileName, FILE_WRITE);
        outMat.save(outFile);
        outFile.close();
    
        copyFile(filePath + textureName, sceneResourcePath + "Textures/" + textureName);
    }
}
