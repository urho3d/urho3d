// Urho3D editor import functions

bool useLocalIDs = false;

void ImportModel(const String&in fileName)
{
    String modelName = "Models/" + GetFileName(fileName) + ".mdl";
    String outFileName = sceneResourcePath + modelName;
    String materialListName = sceneResourcePath + "_tempmatlist_.txt";

    fileSystem.CreateDir(sceneResourcePath + "Models");
    
    Array<String> args;
    args.Push("model");
    args.Push("\"" + fileName + "\"");
    args.Push("\"" + outFileName + "\"");
    args.Push("-p\"" + sceneResourcePath + "\"");
    args.Push("-m\"" + materialListName + "\"");

    if (fileSystem.SystemRun(fileSystem.programDir + "AssetImporter.exe", args) == 0)
    {
        Node@ newNode = editorScene.CreateChild(GetFileName(fileName));
        StaticModel@ newModel = newNode.CreateComponent("StaticModel");
        newNode.position = GetNewNodePosition();
        newModel.model = cache.GetResource("Model", modelName);

        if (fileSystem.FileExists(materialListName))
        {
            File list(materialListName, FILE_READ);
            for (uint i = 0; i < newModel.numGeometries; ++i)
            {
                if (!list.eof)
                    newModel.materials[i] = cache.GetResource("Material", list.ReadLine());
                else
                    break;
            }
            list.Close();
            fileSystem.Delete(materialListName);
        }

        UpdateAndFocusNode(newNode);
    }
}

void ImportScene(const String&in fileName)
{
    // Handle Tundra scene files here in code, otherwise via AssetImporter
    if (GetExtension(fileName) == ".txml")
        ImportTundraScene(fileName);
    else
    {
        // Export scene to a temp file, then load and delete it if successful
        String tempSceneName = sceneResourcePath + "_tempscene_.xml";
        Array<String> args;
        args.Push("scene");
        args.Push("\"" + fileName + "\"");
        args.Push("\"" + tempSceneName + "\"");
        args.Push("-p\"" + sceneResourcePath + "\"");
        
        if (useLocalIDs)
            args.Push("-i");

        if (fileSystem.SystemRun(fileSystem.programDir + "AssetImporter.exe", args) == 0)
        {
            String currentFileName = sceneFileName;
            LoadScene(tempSceneName);
            fileSystem.Delete(tempSceneName);          
            sceneFileName = currentFileName;
            UpdateWindowTitle();
        }
    }
}

void ImportTundraScene(const String&in fileName)
{
    fileSystem.CreateDir(sceneResourcePath + "Materials");
    fileSystem.CreateDir(sceneResourcePath + "Models");
    fileSystem.CreateDir(sceneResourcePath + "Textures");
    
    XMLFile source;
    source.Load(File(fileName, FILE_READ));
    String filePath = GetPath(fileName);

    XMLElement sceneElem = source.root;
    XMLElement entityElem = sceneElem.GetChild("entity");
    
    Array<String> convertedMaterials;
    Array<String> convertedMeshes;

    // Clear old scene, then create a zone and a directional light first
    CreateScene();

    Node@ zoneNode = editorScene.CreateChild("Zone", useLocalIDs ? LOCAL : REPLICATED);
    Zone@ zone = zoneNode.CreateComponent("Zone");
    Node@ lightNode = editorScene.CreateChild("GlobalLight", useLocalIDs ? LOCAL : REPLICATED);
    Light@ light = lightNode.CreateComponent("Light");
    lightNode.rotation = Quaternion(60, 30, 0);
    light.lightType = LIGHT_DIRECTIONAL;
    light.castShadows = true;
    light.shadowCascade = CascadeParameters(3, 0.95, 0.2, 1000000);
    zone.boundingBox = BoundingBox(-1000, 1000);
    zone.ambientColor = Color(0.5, 0.5, 0.5);
    zone.fogColor = Color(0.5, 0.7, 1.0);
    zone.fogStart = 100.0;
    zone.fogEnd = 500.0;

    while (!entityElem.isNull)
    {
        String nodeName;
        String meshName;
        Vector3 meshPos;
        Vector3 meshRot;
        Vector3 meshScale(1, 1, 1);
        Vector3 pos;
        Vector3 rot;
        Vector3 scale(1, 1, 1);
        bool castShadows = false;
        float drawDistance = 0;
        Array<String> materialNames;

        XMLElement compElem = entityElem.GetChild("component");
        while (!compElem.isNull)
        {
            String compType = compElem.GetAttribute("type");

            if (compType == "EC_Mesh")
            {
                Array<String> coords = GetComponentAttribute(compElem, "Transform").Split(',');
                meshPos = GetVector3FromStrings(coords, 0);
                meshRot = GetVector3FromStrings(coords, 3);
                meshScale = GetVector3FromStrings(coords, 6);
                meshName = GetComponentAttribute(compElem, "Mesh ref");
                castShadows = GetComponentAttribute(compElem, "Cast shadows").ToBool();
                drawDistance = GetComponentAttribute(compElem, "Draw distance").ToFloat();
                materialNames = GetComponentAttribute(compElem, "Mesh materials").Split(';');
                ProcessRef(meshName);
                for (uint i = 0; i < materialNames.length; ++i)
                    ProcessRef(materialNames[i]);
            }
            if (compType == "EC_Name")
                nodeName = GetComponentAttribute(compElem, "name");
            if (compType == "EC_Placeable")
            {
                Array<String> coords = GetComponentAttribute(compElem, "Transform").Split(',');
                pos = GetVector3FromStrings(coords, 0);
                rot = GetVector3FromStrings(coords, 3);
                scale = GetVector3FromStrings(coords, 6);
            }
            
            compElem = compElem.GetNext("component");
        }

        // For now we are only interested of meshes
        if (!meshName.empty)
        {
            for (uint i = 0; i < materialNames.length; ++i)
            {
                bool found = false;
                for (uint j = 0; j < convertedMaterials.length; ++j)
                {
                    if (convertedMaterials[j] == materialNames[i])
                    {
                        found = true;
                        break;
                    }                    
                }
    
                if (!found)
                {
                    ConvertMaterial(materialNames[i], filePath);
                    convertedMaterials.Push(materialNames[i]);
                }
            }
    
            bool found = false;
            for (uint i = 0; i < convertedMeshes.length; ++i)
            {
                if (convertedMeshes[i] == meshName)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
                ConvertModel(meshName, filePath);
    
            Node@ newNode = editorScene.CreateChild(nodeName, useLocalIDs ? LOCAL : REPLICATED);
            StaticModel@ model = newNode.CreateComponent("StaticModel");

            // Calculate final transform in an Ogre-like fashion
            Quaternion quat = Quaternion(rot);
            Quaternion meshQuat = Quaternion(meshRot);            
            Quaternion finalQuat = quat * meshQuat;
            Vector3 finalScale = scale * meshScale;
            Vector3 finalPos = pos + quat * (scale * meshPos);

            newNode.SetTransform(finalPos, finalQuat, finalScale);
            model.model = cache.GetResource("Model", "Models/" + meshName.Replaced(".mesh", ".mdl"));
            model.drawDistance = drawDistance;
            model.castShadows = castShadows;
            for (uint i = 0; i < materialNames.length; ++i)
                model.materials[i] = cache.GetResource("Material", "Materials/" + materialNames[i].Replaced(".material", ".xml"));
        }

        entityElem = entityElem.GetNext("entity");
    }

    UpdateSceneWindow();
    UpdateWindowTitle();    
}

String GetComponentAttribute(XMLElement compElem, const String&in name)
{
    XMLElement attrElem = compElem.GetChild("attribute");
    while (!attrElem.isNull)
    {
        if (attrElem.GetAttribute("name") == name)
            return attrElem.GetAttribute("value");

        attrElem = attrElem.GetNext("attribute");
    }

    return "";
}

Vector3 GetVector3FromStrings(Array<String>@ coords, uint startIndex)
{
    return Vector3(coords[startIndex].ToFloat(), coords[startIndex + 1].ToFloat(), coords[startIndex + 2].ToFloat());
}

void ProcessRef(String& ref)
{
    if (ref.StartsWith("local://"))
        ref = ref.Substring(8);
    if (ref.StartsWith("file://"))
        ref = ref.Substring(7);
}

void ConvertModel(const String&in modelName, const String&in filePath)
{
    // Convert .mesh to .mesh.xml
    String cmdLine = "ogrexmlconverter.exe \"" + filePath + modelName + "\" \"" + filePath + modelName + ".xml\"";
    fileSystem.SystemCommand(cmdLine.Replaced('/', '\\'));

    // Convert .mesh.xml to .mdl
    Array<String> args;
    args.Push("\"" + filePath + modelName + ".xml\"");
    args.Push("\"" + sceneResourcePath + "Models/" + modelName.Replaced(".mesh", ".mdl") + "\"");
    args.Push("-a");
    fileSystem.SystemRun(fileSystem.programDir + "OgreImporter.exe", args);
}

void ConvertMaterial(const String&in materialName, const String&in filePath)
{
    String fileName = filePath + materialName;
    String outFileName = sceneResourcePath + "Materials/" + GetFileName(materialName) + ".xml";

    if (!fileSystem.FileExists(fileName))
        return;

    bool mask = false;
    bool twoSided = false;
    String textureName;

    File file(fileName, FILE_READ);
    while (!file.eof)
    {
        String line = file.ReadLine().Trimmed();
        if (line.StartsWith("alpha_rejection"))
            mask = true;
        if (line.StartsWith("cull_hardware none"))
            twoSided = true;
        if (line.StartsWith("texture "))
        {
            textureName = line.Substring(8);
            ProcessRef(textureName);
        }
    }

    XMLFile outMat;
    XMLElement rootElem = outMat.CreateRoot("material");
    XMLElement techniqueElem = rootElem.CreateChild("technique");
    techniqueElem.SetAttribute("name", mask ? "Techniques/DiffAlphaMask.xml" : "Techniques/Diff.xml");
    if (twoSided)
    {
        XMLElement cullElem = rootElem.CreateChild("cull");
        cullElem.SetAttribute("value", "none");
        XMLElement shadowCullElem = rootElem.CreateChild("shadowcull");
        shadowCullElem.SetAttribute("value", "none");
    }

    if (!textureName.empty)
    {
        XMLElement textureElem = rootElem.CreateChild("texture");
        textureElem.SetAttribute("unit", "diffuse");
        textureElem.SetAttribute("name", "Textures/" + textureName);

        File outFile(outFileName, FILE_WRITE);
        outMat.Save(outFile);
        outFile.Close();
    
        fileSystem.Copy(filePath + textureName, sceneResourcePath + "Textures/" + textureName);
    }
}
