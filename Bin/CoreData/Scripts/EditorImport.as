// Urho3D editor import functions

void importModel(const string& in fileName)
{
    string modelName = "Models/" + getFileName(fileName) + ".mdl";
    string outFileName = sceneResourcePath + modelName;
    string materialListName = sceneResourcePath + "_tempmatlist_.txt";

    array<string> args;
    args.push("model");
    args.push("\"" + fileName + "\"");
    args.push("\"" + outFileName + "\"");
    args.push("-p\"" + sceneResourcePath + "\"");
    args.push("-m\"" + materialListName + "\"");

    if (systemRun(getExecutableDirectory() + "AssetImporter.exe", args) == 0)
    {
        Entity@ newEntity = editorScene.createEntity(getFileName(fileName));
        StaticModel@ newModel = newEntity.createComponent("StaticModel");
        newModel.setPosition(camera.getWorldPosition() + camera.getWorldRotation() * Vector3(0, 0, newNodeDistance));
        newModel.setModel(cache.getResource("Model", modelName));

        if (fileExists(materialListName))
        {
            File list(materialListName, FILE_READ);
            for (uint i = 0; i < newModel.getNumGeometries(); ++i)
            {
                if (!list.isEof())
                    newModel.setMaterial(i, cache.getResource("Material", list.readLine()));
                else
                    break;
            }
            list.close();
            deleteFile(materialListName);
        }

        updateAndFocusNewEntity(newEntity);
    }
}

void importScene(const string& in fileName)
{
    // Handle Tundra scene files here in code, otherwise via AssetImporter
    if (getExtension(fileName) == ".txml")
        importTundraScene(fileName);
    else
    {
        // Export scene to a temp file, then load and delete it if successful
        string tempSceneName = sceneResourcePath + "_tempscene_.xml";
        array<string> args;
        args.push("scene");
        args.push("\"" + fileName + "\"");
        args.push("\"" + tempSceneName + "\"");
        args.push("-p\"" + sceneResourcePath + "\"");
        
        if (systemRun(getExecutableDirectory() + "AssetImporter.exe", args) == 0)
        {
            string currentFileName = sceneFileName;
            loadScene(tempSceneName);
            deleteFile(tempSceneName);
            sceneFileName = currentFileName;
            updateWindowTitle();
        }
    }
}

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

void importTundraScene(const string& in fileName)
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
    createScene();

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

string getComponentAttribute(XMLElement compElem, const string& in name)
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
    // Convert .mesh to .mesh.xml
    string cmdLine = "ogrexmlconverter.exe \"" + filePath + modelName + "\" \"" + filePath + modelName + ".xml\"";
    systemCommand(cmdLine.replace('/', '\\'));

    // Convert .mesh.xml to .mdl
    array<string> args;
    args.push("\"" + filePath + modelName + ".xml\"");
    args.push("\"" + sceneResourcePath + "Models/" + modelName.replace(".mesh", ".mdl") + "\"");
    args.push("-a");
    systemRun(getExecutableDirectory() + "OgreImporter.exe", args);
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
