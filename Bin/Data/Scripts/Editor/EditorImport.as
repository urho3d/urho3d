// Urho3D editor import functions

bool useLocalIDs = false;

class ParentAssignment
{
    uint childID;
    String parentName;
}

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
    Array<ParentAssignment> parentAssignments;

    // Clear old scene, then create a zone and a directional light first
    CreateScene();
    
    // Set standard gravity
    editorScene.physicsWorld.gravity = Vector3(0, -9.81, 0);

    // Create zone & global light
    Node@ zoneNode = editorScene.CreateChild("Zone", useLocalIDs ? LOCAL : REPLICATED);
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000, 1000);
    zone.ambientColor = Color(0.364, 0.364, 0.364);
    zone.fogColor = Color(0.707792, 0.770537, 0.831373);
    zone.fogStart = 100.0;
    zone.fogEnd = 500.0;

    Node@ lightNode = editorScene.CreateChild("GlobalLight", useLocalIDs ? LOCAL : REPLICATED);
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
        bool phantom = false;
        bool kinematic = false;
        uint collisionLayer;
        uint collisionMask;
        String collisionMeshName;

        XMLElement compElem = entityElem.GetChild("component");
        while (!compElem.isNull)
        {
            String compType = compElem.GetAttribute("type");

            if (compType == "EC_Mesh")
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
            if (compType == "EC_Name")
                nodeName = GetComponentAttribute(compElem, "name");
            if (compType == "EC_Placeable")
            {
                Array<String> coords = GetComponentAttribute(compElem, "Transform").Split(',');
                pos = GetVector3FromStrings(coords, 0);
                pos.z = -pos.z; // Convert to lefthanded
                rot = GetVector3FromStrings(coords, 3);
                scale = GetVector3FromStrings(coords, 6);
                parentName = GetComponentAttribute(compElem, "Parent entity ref");
            }
            if (compType == "EC_RigidBody")
            {
                shapeType = GetComponentAttribute(compElem, "Shape type").ToInt();
                mass = GetComponentAttribute(compElem, "Mass").ToFloat();
                bodySize = GetComponentAttribute(compElem, "Size").ToVector3();
                collisionMeshName = GetComponentAttribute(compElem, "Collision mesh ref");
                phantom = GetComponentAttribute(compElem, "Phantom").ToBool();
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

            Node@ newNode = editorScene.CreateChild(nodeName, useLocalIDs ? LOCAL : REPLICATED);

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
                model.model = cache.GetResource("Model", "Models/" + meshName.Replaced(".mesh", ".mdl"));
                model.drawDistance = drawDistance;
                model.castShadows = castShadows;
                // Set default grey material to match Tundra defaults
                model.material = cache.GetResource("Material", "Materials/DefaultGrey.xml");
                // Then try to assign the actual materials
                for (uint i = 0; i < materialNames.length; ++i)
                {
                    Material@ mat = cache.GetResource("Material", "Materials/" + materialNames[i].Replaced(".material", ".xml"));
                    if (mat !is null)
                        model.materials[i] = mat;
                }
            }
            
            // Create collision shape
            if (shapeType >= 0)
            {
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
                    shape.SetTriangleMesh(cache.GetResource("Model", "Models/" + collisionMeshName.Replaced(".mesh", ".mdl")), 0, bodySize);
                    break;
                    
                case 6:
                    shape.SetConvexHull(cache.GetResource("Model", "Models/" + collisionMeshName.Replaced(".mesh", ".mdl")), 0.1, 0, bodySize);
                    break;
                }
                
                shape.collisionLayer = collisionLayer;
                shape.collisionMask = collisionMask;
                shape.phantom = phantom;

                // Create rigid body if the object should be dynamic or kinematic
                if (mass > 0.0)
                {
                    RigidBody@ body = newNode.CreateComponent("RigidBody");
                    //if (kinematic)
                    //    mass = 0.0;
                    body.mass = mass;
                }
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

    UpdateSceneWindow();
    UpdateWindowTitle();
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

void ConvertModel(const String&in modelName, const String&in filePath, Array<String>@ convertedModels)
{
    if (modelName.Trimmed().empty)
        return;

    for (uint i = 0; i < convertedModels.length; ++i)
    {
        if (convertedModels[i] == modelName)
            return;
    }

    // Convert .mesh to .mesh.xml
    String cmdLine = "ogrexmlconverter.exe \"" + filePath + modelName + "\" \"" + filePath + modelName + ".xml\"";
    fileSystem.SystemCommand(cmdLine.Replaced('/', '\\'));

    // Convert .mesh.xml to .mdl
    Array<String> args;
    args.Push("\"" + filePath + modelName + ".xml\"");
    args.Push("\"" + sceneResourcePath + "Models/" + modelName.Replaced(".mesh", ".mdl") + "\"");
    args.Push("-a");
    fileSystem.SystemRun(fileSystem.programDir + "OgreImporter.exe", args);
    
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
    
    convertedMaterials.Push(materialName);
}
