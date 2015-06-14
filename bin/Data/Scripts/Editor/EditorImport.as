// Urho3D editor import functions

String importOptions = "-t";

class ParentAssignment
{
    uint childID;
    String parentName;
}

class AssetMapping
{
    String assetName;
    String fullAssetName;
}

Array<AssetMapping> assetMappings;

String assetImporterPath;

int ExecuteAssetImporter(Array<String>@ args)
{
    if (assetImporterPath.empty)
    {
        String exeSuffix = "";
        if (GetPlatform() == "Windows")
            exeSuffix = ".exe";
        // Try both with and without the tool directory; a packaged build may not have the tool directory
        assetImporterPath = fileSystem.programDir + "tool/AssetImporter" + exeSuffix;
        if (!fileSystem.FileExists(assetImporterPath))
            assetImporterPath = fileSystem.programDir + "AssetImporter" + exeSuffix;
    }

    return fileSystem.SystemRun(assetImporterPath, args);
}

void ImportModel(const String&in fileName)
{
    if (fileName.empty)
        return;

    ui.cursor.shape = CS_BUSY;

    String modelName = "Models/" + GetFileName(fileName) + ".mdl";
    String outFileName = sceneResourcePath + modelName;
    fileSystem.CreateDir(sceneResourcePath + "Models");

    Array<String> args;
    args.Push("model");
    args.Push("\"" + fileName + "\"");
    args.Push("\"" + outFileName + "\"");
    args.Push("-p \"" + sceneResourcePath + "\"");
    Array<String> options = importOptions.Trimmed().Split(' ');
    for (uint i = 0; i < options.length; ++i)
        args.Push(options[i]);
    // If material lists are to be applied, make sure the option to create them exists
    if (applyMaterialList)
        args.Push("-l");

    if (ExecuteAssetImporter(args) == 0)
    {
        Node@ newNode = editorScene.CreateChild(GetFileName(fileName));
        StaticModel@ newModel = newNode.CreateComponent("StaticModel");
        newNode.position = GetNewNodePosition();
        newModel.model = cache.GetResource("Model", modelName);
        newModel.ApplyMaterialList(); // Setup default materials if possible

        // Create an undo action for the create
        CreateNodeAction action;
        action.Define(newNode);
        SaveEditAction(action);
        SetSceneModified();

        FocusNode(newNode);
    }
    else
        log.Error("Failed to execute AssetImporter to import model");
}

void ImportScene(const String&in fileName)
{
    if (fileName.empty)
        return;

    ui.cursor.shape = CS_BUSY;

    // Handle Tundra scene files here in code, otherwise via AssetImporter
    if (GetExtension(fileName) == ".txml")
        ImportTundraScene(fileName);
    else
    {
        // Export scene to a temp file, then load and delete it if successful
        String tempSceneName = sceneResourcePath + TEMP_SCENE_NAME;
        Array<String> args;
        args.Push("scene");
        args.Push("\"" + fileName + "\"");
        args.Push("\"" + tempSceneName + "\"");
        args.Push("-p \"" + sceneResourcePath + "\"");
        Array<String> options = importOptions.Trimmed().Split(' ');
        for (uint i = 0; i < options.length; ++i)
            args.Push(options[i]);
        if (applyMaterialList)
            args.Push("-l");
        if (ExecuteAssetImporter(args) == 0)
        {
            skipMruScene = true; // set to avoid adding tempscene to mru
            LoadScene(tempSceneName);
            fileSystem.Delete(tempSceneName);
            UpdateWindowTitle();
        }
        else
            log.Error("Failed to execute AssetImporter to import scene");
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
    Array<ParentAssignment> parentAssignments;

    // Read the scene directory structure recursively to get assetname to full assetname mappings
    Array<String> fileNames = fileSystem.ScanDir(filePath, "*.*", SCAN_FILES, true);
    for (uint i = 0; i < fileNames.length; ++i)
    {
        AssetMapping mapping;
        mapping.assetName = GetFileNameAndExtension(fileNames[i]);
        mapping.fullAssetName = fileNames[i];
        assetMappings.Push(mapping);
    }

    // Clear old scene, then create a zone and a directional light first
    ResetScene();

    // Set standard gravity
    editorScene.CreateComponent("PhysicsWorld");
    editorScene.physicsWorld.gravity = Vector3(0, -9.81, 0);

    // Create zone & global light
    Node@ zoneNode = editorScene.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000, 1000);
    zone.ambientColor = Color(0.364, 0.364, 0.364);
    zone.fogColor = Color(0.707792, 0.770537, 0.831373);
    zone.fogStart = 100.0;
    zone.fogEnd = 500.0;

    Node@ lightNode = editorScene.CreateChild("GlobalLight");
    Light@ light = lightNode.CreateComponent("Light");
    lightNode.rotation = Quaternion(60, 30, 0);
    light.lightType = LIGHT_DIRECTIONAL;
    light.color = Color(0.639, 0.639, 0.639);
    light.castShadows = true;
    light.shadowCascade = CascadeParameters(5, 15.0, 50.0, 0.0, 0.9);

    // Loop through scene entities
    while (!entityElem.isNull)
    {
        String nodeName;
        String meshName;
        String parentName;
        Vector3 meshPos;
        Vector3 meshRot;
        Vector3 meshScale(1, 1, 1);
        Vector3 pos;
        Vector3 rot;
        Vector3 scale(1, 1, 1);
        bool castShadows = false;
        float drawDistance = 0;
        Array<String> materialNames;

        int shapeType = -1;
        float mass = 0.0f;
        Vector3 bodySize;
        bool trigger = false;
        bool kinematic = false;
        uint collisionLayer;
        uint collisionMask;
        String collisionMeshName;

        XMLElement compElem = entityElem.GetChild("component");
        while (!compElem.isNull)
        {
            String compType = compElem.GetAttribute("type");

            if (compType == "EC_Mesh" || compType == "Mesh")
            {
                Array<String> coords = GetComponentAttribute(compElem, "Transform").Split(',');
                meshPos = GetVector3FromStrings(coords, 0);
                meshPos.z = -meshPos.z; // Convert to lefthanded
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
            if (compType == "EC_Name" || compType == "Name")
                nodeName = GetComponentAttribute(compElem, "name");
            if (compType == "EC_Placeable" || compType == "Placeable")
            {
                Array<String> coords = GetComponentAttribute(compElem, "Transform").Split(',');
                pos = GetVector3FromStrings(coords, 0);
                pos.z = -pos.z; // Convert to lefthanded
                rot = GetVector3FromStrings(coords, 3);
                scale = GetVector3FromStrings(coords, 6);
                parentName = GetComponentAttribute(compElem, "Parent entity ref");
            }
            if (compType == "EC_RigidBody" || compType == "RigidBody")
            {
                shapeType = GetComponentAttribute(compElem, "Shape type").ToInt();
                mass = GetComponentAttribute(compElem, "Mass").ToFloat();
                bodySize = GetComponentAttribute(compElem, "Size").ToVector3();
                collisionMeshName = GetComponentAttribute(compElem, "Collision mesh ref");
                trigger = GetComponentAttribute(compElem, "Phantom").ToBool();
                kinematic = GetComponentAttribute(compElem, "Kinematic").ToBool();
                collisionLayer = GetComponentAttribute(compElem, "Collision Layer").ToInt();
                collisionMask = GetComponentAttribute(compElem, "Collision Mask").ToInt();
                ProcessRef(collisionMeshName);
            }

            compElem = compElem.GetNext("component");
        }

        // If collision mesh not specified for the rigid body, assume same as the visible mesh
        if ((shapeType == 4 || shapeType == 6) && collisionMeshName.Trimmed().empty)
            collisionMeshName = meshName;

        if (!meshName.empty || shapeType >= 0)
        {
            for (uint i = 0; i < materialNames.length; ++i)
                ConvertMaterial(materialNames[i], filePath, convertedMaterials);

            ConvertModel(meshName, filePath, convertedMeshes);
            ConvertModel(collisionMeshName, filePath, convertedMeshes);

            Node@ newNode = editorScene.CreateChild(nodeName);

            // Calculate final transform in an Ogre-like fashion
            Quaternion quat = GetTransformQuaternion(rot);
            Quaternion meshQuat = GetTransformQuaternion(meshRot);
            Quaternion finalQuat = quat * meshQuat;
            Vector3 finalScale = scale * meshScale;
            Vector3 finalPos = pos + quat * (scale * meshPos);

            newNode.SetTransform(finalPos, finalQuat, finalScale);

            // Create model
            if (!meshName.empty)
            {
                StaticModel@ model = newNode.CreateComponent("StaticModel");
                model.model = cache.GetResource("Model", GetOutModelName(meshName));
                model.drawDistance = drawDistance;
                model.castShadows = castShadows;
                // Set default grey material to match Tundra defaults
                model.material = cache.GetResource("Material", "Materials/DefaultGrey.xml");
                // Then try to assign the actual materials
                for (uint i = 0; i < materialNames.length; ++i)
                {
                    Material@ mat = cache.GetResource("Material", GetOutMaterialName(materialNames[i]));
                    if (mat !is null)
                        model.materials[i] = mat;
                }
            }

            // Create rigidbody & collision shape
            if (shapeType >= 0)
            {
                RigidBody@ body = newNode.CreateComponent("RigidBody");

                // If mesh has scaling, undo it for the collision shape
                bodySize.x /= meshScale.x;
                bodySize.y /= meshScale.y;
                bodySize.z /= meshScale.z;

                CollisionShape@ shape = newNode.CreateComponent("CollisionShape");
                switch (shapeType)
                {
                case 0:
                    shape.SetBox(bodySize);
                    break;

                case 1:
                    shape.SetSphere(bodySize.x);
                    break;

                case 2:
                    shape.SetCylinder(bodySize.x, bodySize.y);
                    break;

                case 3:
                    shape.SetCapsule(bodySize.x, bodySize.y);
                    break;

                case 4:
                    shape.SetTriangleMesh(cache.GetResource("Model", GetOutModelName(collisionMeshName)), 0, bodySize);
                    break;

                case 6:
                    shape.SetConvexHull(cache.GetResource("Model", GetOutModelName(collisionMeshName)), 0, bodySize);
                    break;
                }

                body.collisionLayer = collisionLayer;
                body.collisionMask = collisionMask;
                body.trigger = trigger;
                body.mass = mass;
            }

            // Store pending parent assignment if necessary
            if (!parentName.empty)
            {
                ParentAssignment assignment;
                assignment.childID = newNode.id;
                assignment.parentName = parentName;
                parentAssignments.Push(assignment);
            }
        }

        entityElem = entityElem.GetNext("entity");
    }

    // Process any parent assignments now
    for (uint i = 0; i < parentAssignments.length; ++i)
    {
        Node@ childNode = editorScene.GetNode(parentAssignments[i].childID);
        Node@ parentNode = editorScene.GetChild(parentAssignments[i].parentName, true);
        if (childNode !is null && parentNode !is null)
            childNode.parent = parentNode;
    }

    UpdateHierarchyItem(editorScene, true);
    UpdateWindowTitle();
    assetMappings.Clear();
}

String GetFullAssetName(const String& assetName)
{
    for (uint i = 0; i < assetMappings.length; ++i)
    {
        if (assetMappings[i].assetName == assetName)
            return assetMappings[i].fullAssetName;
    }

    return assetName;
}

Quaternion GetTransformQuaternion(Vector3 rotEuler)
{
    // Convert rotation to lefthanded
    Quaternion rotateX(-rotEuler.x, Vector3(1, 0, 0));
    Quaternion rotateY(-rotEuler.y, Vector3(0, 1, 0));
    Quaternion rotateZ(-rotEuler.z, Vector3(0, 0, -1));
    return rotateZ * rotateY * rotateX;
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

String GetOutModelName(const String&in ref)
{
    return "Models/" + GetFullAssetName(ref).Replaced('/', '_').Replaced(".mesh", ".mdl");
}

String GetOutMaterialName(const String&in ref)
{
    return "Materials/" + GetFullAssetName(ref).Replaced('/', '_').Replaced(".material", ".xml");
}

String GetOutTextureName(const String&in ref)
{
    return "Textures/" + GetFullAssetName(ref).Replaced('/', '_');
}

void ConvertModel(const String&in modelName, const String&in filePath, Array<String>@ convertedModels)
{
    if (modelName.Trimmed().empty)
        return;

    for (uint i = 0; i < convertedModels.length; ++i)
    {
        if (convertedModels[i] == modelName)
            return;
    }

    String meshFileName = filePath + GetFullAssetName(modelName);
    String xmlFileName = filePath + GetFullAssetName(modelName) + ".xml";
    String outFileName = sceneResourcePath + GetOutModelName(modelName);

    // Convert .mesh to .mesh.xml
    String cmdLine = "ogrexmlconverter \"" + meshFileName + "\" \"" + xmlFileName + "\"";
    if (!fileSystem.FileExists(xmlFileName))
        fileSystem.SystemCommand(cmdLine.Replaced('/', '\\'));

    if (!fileSystem.FileExists(outFileName))
    {
        // Convert .mesh.xml to .mdl
        Array<String> args;
        args.Push("\"" + xmlFileName + "\"");
        args.Push("\"" + outFileName + "\"");
        args.Push("-a");
        fileSystem.SystemRun(fileSystem.programDir + "tool/OgreImporter", args);
    }

    convertedModels.Push(modelName);
}

void ConvertMaterial(const String&in materialName, const String&in filePath, Array<String>@ convertedMaterials)
{
    if (materialName.Trimmed().empty)
        return;

    for (uint i = 0; i < convertedMaterials.length; ++i)
    {
        if (convertedMaterials[i] == materialName)
            return;
    }

    String fileName = filePath + GetFullAssetName(materialName);
    String outFileName = sceneResourcePath + GetOutMaterialName(materialName);

    if (!fileSystem.FileExists(fileName))
        return;

    bool mask = false;
    bool twoSided = false;
    bool uvScaleSet = false;
    String textureName;
    Vector2 uvScale(1, 1);
    Color diffuse(1, 1, 1, 1);

    File file(fileName, FILE_READ);
    while (!file.eof)
    {
        String line = file.ReadLine().Trimmed();
        if (line.StartsWith("alpha_rejection") || line.StartsWith("scene_blend alpha_blend"))
            mask = true;
        if (line.StartsWith("cull_hardware none"))
            twoSided = true;
        // Todo: handle multiple textures per material
        if (textureName.empty && line.StartsWith("texture "))
        {
            textureName = line.Substring(8);
            ProcessRef(textureName);
        }
        if (!uvScaleSet && line.StartsWith("scale "))
        {
            uvScale = line.Substring(6).ToVector2();
            uvScaleSet = true;
        }
        if (line.StartsWith("diffuse "))
            diffuse = line.Substring(8).ToColor();
    }

    XMLFile outMat;
    XMLElement rootElem = outMat.CreateRoot("material");
    XMLElement techniqueElem = rootElem.CreateChild("technique");

    if (twoSided)
    {
        XMLElement cullElem = rootElem.CreateChild("cull");
        cullElem.SetAttribute("value", "none");
        XMLElement shadowCullElem = rootElem.CreateChild("shadowcull");
        shadowCullElem.SetAttribute("value", "none");
    }

    if (!textureName.empty)
    {
        techniqueElem.SetAttribute("name", mask ? "Techniques/DiffAlphaMask.xml" : "Techniques/Diff.xml");

        String outTextureName = GetOutTextureName(textureName);
        XMLElement textureElem = rootElem.CreateChild("texture");
        textureElem.SetAttribute("unit", "diffuse");
        textureElem.SetAttribute("name", outTextureName);

        fileSystem.Copy(filePath + GetFullAssetName(textureName), sceneResourcePath + outTextureName);
    }
    else
        techniqueElem.SetAttribute("name", "NoTexture.xml");

    if (uvScale != Vector2(1, 1))
    {
        XMLElement uScaleElem = rootElem.CreateChild("parameter");
        uScaleElem.SetAttribute("name", "UOffset");
        uScaleElem.SetVector3("value", Vector3(1 / uvScale.x, 0, 0));

        XMLElement vScaleElem = rootElem.CreateChild("parameter");
        vScaleElem.SetAttribute("name", "VOffset");
        vScaleElem.SetVector3("value", Vector3(0, 1 / uvScale.y, 0));
    }

    if (diffuse != Color(1, 1, 1, 1))
    {
        XMLElement diffuseElem = rootElem.CreateChild("parameter");
        diffuseElem.SetAttribute("name", "MatDiffColor");
        diffuseElem.SetColor("value", diffuse);
    }

    File outFile(outFileName, FILE_WRITE);
    outMat.Save(outFile);
    outFile.Close();

    convertedMaterials.Push(materialName);
}
