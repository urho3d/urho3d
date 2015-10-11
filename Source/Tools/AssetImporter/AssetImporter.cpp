//
// Copyright (c) 2008-2015 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/Core/WorkQueue.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/Animation.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/IndexBuffer.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/VertexBuffer.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/IO/File.h>
#include <Urho3D/IO/FileSystem.h>
#ifdef URHO3D_PHYSICS
#include <Urho3D/Physics/PhysicsWorld.h>
#endif
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/Scene/Scene.h>

#ifdef WIN32
#include <windows.h>
#endif

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/DefaultLogger.hpp>

#include <Urho3D/DebugNew.h>

using namespace Urho3D;

struct OutModel
{
    OutModel() :
        rootBone_(0),
        totalVertices_(0),
        totalIndices_(0)
    {
    }

    String outName_;
    aiNode* rootNode_;
    HashSet<unsigned> meshIndices_;
    PODVector<aiMesh*> meshes_;
    PODVector<aiNode*> meshNodes_;
    PODVector<aiNode*> bones_;
    PODVector<aiAnimation*> animations_;
    PODVector<float> boneRadii_;
    PODVector<BoundingBox> boneHitboxes_;
    aiNode* rootBone_;
    unsigned totalVertices_;
    unsigned totalIndices_;
};

struct OutScene
{
    String outName_;
    aiNode* rootNode_;
    Vector<OutModel> models_;
    PODVector<aiNode*> nodes_;
    PODVector<unsigned> nodeModelIndices_;
};

SharedPtr<Context> context_(new Context());
const aiScene* scene_ = 0;
aiNode* rootNode_ = 0;
String inputName_;
String resourcePath_;
String outPath_;
bool useSubdirs_ = true;
bool localIDs_ = false;
bool saveBinary_ = false;
bool createZone_ = true;
bool noAnimations_ = false;
bool noHierarchy_ = false;
bool noMaterials_ = false;
bool noTextures_ = false;
bool noMaterialDiffuseColor_ = false;
bool noEmptyNodes_ = false;
bool saveMaterialList_ = false;
bool includeNonSkinningBones_ = false;
bool verboseLog_ = false;
bool emissiveAO_ = false;
bool noOverwriteMaterial_ = false;
bool noOverwriteTexture_ = false;
bool noOverwriteNewerTexture_ = false;
bool checkUniqueModel_ = true;
bool moveToBindPose_ = false;
unsigned maxBones_ = 64;
Vector<String> nonSkinningBoneIncludes_;
Vector<String> nonSkinningBoneExcludes_;

HashSet<aiAnimation*> allAnimations_;
PODVector<aiAnimation*> sceneAnimations_;

float defaultTicksPerSecond_ = 4800.0f;

int main(int argc, char** argv);
void Run(const Vector<String>& arguments);
void DumpNodes(aiNode* rootNode, unsigned level);

void ExportModel(const String& outName, bool animationOnly);
void CollectMeshes(OutModel& model, aiNode* node);
void CollectBones(OutModel& model, bool animationOnly = false);
void CollectBonesFinal(PODVector<aiNode*>& dest, const HashSet<aiNode*>& necessary, aiNode* node);
void MoveToBindPose(OutModel& model, aiNode* current);
void CollectAnimations(OutModel* model = 0);
void BuildBoneCollisionInfo(OutModel& model);
void BuildAndSaveModel(OutModel& model);
void BuildAndSaveAnimations(OutModel* model = 0);

void ExportScene(const String& outName, bool asPrefab);
void CollectSceneModels(OutScene& scene, aiNode* node);
void CreateHierarchy(Scene* scene, aiNode* srcNode, HashMap<aiNode*, Node*>& nodeMapping);
Node* CreateSceneNode(Scene* scene, aiNode* srcNode, HashMap<aiNode*, Node*>& nodeMapping);
void BuildAndSaveScene(OutScene& scene, bool asPrefab);

void ExportMaterials(HashSet<String>& usedTextures);
void BuildAndSaveMaterial(aiMaterial* material, HashSet<String>& usedTextures);
void CopyTextures(const HashSet<String>& usedTextures, const String& sourcePath);

void CombineLods(const PODVector<float>& lodDistances, const Vector<String>& modelNames, const String& outName);

void GetMeshesUnderNode(Vector<Pair<aiNode*, aiMesh*> >& meshes, aiNode* node);
unsigned GetMeshIndex(aiMesh* mesh);
unsigned GetBoneIndex(OutModel& model, const String& boneName);
aiBone* GetMeshBone(OutModel& model, const String& boneName);
Matrix3x4 GetOffsetMatrix(OutModel& model, const String& boneName);
void GetBlendData(OutModel& model, aiMesh* mesh, PODVector<unsigned>& boneMappings, Vector<PODVector<unsigned char> >&
    blendIndices, Vector<PODVector<float> >& blendWeights);
String GetMeshMaterialName(aiMesh* mesh);
String GetMaterialTextureName(const String& nameIn);
String GenerateMaterialName(aiMaterial* material);
String GenerateTextureName(unsigned texIndex);
unsigned GetNumValidFaces(aiMesh* mesh);

void WriteShortIndices(unsigned short*& dest, aiMesh* mesh, unsigned index, unsigned offset);
void WriteLargeIndices(unsigned*& dest, aiMesh* mesh, unsigned index, unsigned offset);
void WriteVertex(float*& dest, aiMesh* mesh, unsigned index, unsigned elementMask, BoundingBox& box,
    const Matrix3x4& vertexTransform, const Matrix3& normalTransform, Vector<PODVector<unsigned char> >& blendIndices,
    Vector<PODVector<float> >& blendWeights);
unsigned GetElementMask(aiMesh* mesh);

aiNode* GetNode(const String& name, aiNode* rootNode, bool caseSensitive = true);
aiMatrix4x4 GetDerivedTransform(aiNode* node, aiNode* rootNode, bool rootInclusive = true);
aiMatrix4x4 GetDerivedTransform(aiMatrix4x4 transform, aiNode* node, aiNode* rootNode, bool rootInclusive = true);
aiMatrix4x4 GetMeshBakingTransform(aiNode* meshNode, aiNode* modelRootNode);
void GetPosRotScale(const aiMatrix4x4& transform, Vector3& pos, Quaternion& rot, Vector3& scale);

String FromAIString(const aiString& str);
Vector3 ToVector3(const aiVector3D& vec);
Vector2 ToVector2(const aiVector2D& vec);
Quaternion ToQuaternion(const aiQuaternion& quat);
Matrix3x4 ToMatrix3x4(const aiMatrix4x4& mat);
aiMatrix4x4 ToAIMatrix4x4(const Matrix3x4& mat);
String SanitateAssetName(const String& name);

int main(int argc, char** argv)
{
    Vector<String> arguments;

    #ifdef WIN32
    arguments = ParseArguments(GetCommandLineW());
    #else
    arguments = ParseArguments(argc, argv);
    #endif

    Run(arguments);
    return 0;
}

void Run(const Vector<String>& arguments)
{
    if (arguments.Size() < 2)
    {
        ErrorExit(
            "Usage: AssetImporter <command> <input file> <output file> [options]\n"
            "See http://assimp.sourceforge.net/main_features_formats.html for input formats\n\n"
            "Commands:\n"
            "model      Output a model\n"
            "scene      Output a scene\n"
            "node       Output a node and its children (prefab)\n"
            "dump       Dump scene node structure. No output file is generated\n"
            "lod        Combine several Urho3D models as LOD levels of the output model\n"
            "           Syntax: lod <dist0> <mdl0> <dist1 <mdl1> ... <output file>\n"
            "\n"
            "Options:\n"
            "-b          Save scene in binary format, default format is XML\n"
            "-h          Generate hard instead of smooth normals if input file has no normals\n"
            "-i          Use local ID's for scene nodes\n"
            "-l          Output a material list file for models\n"
            "-na         Do not output animations\n"
            "-nm         Do not output materials\n"
            "-nt         Do not output material textures\n"
            "-nc         Do not use material diffuse color value, instead output white\n"
            "-nh         Do not save full node hierarchy (scene mode only)\n"
            "-ns         Do not create subdirectories for resources\n"
            "-nz         Do not create a zone and a directional light (scene mode only)\n"
            "-nf         Do not fix infacing normals\n"
            "-ne         Do not save empty nodes (scene mode only)\n"
            "-mb <x>     Maximum number of bones per submesh. Default 64\n"
            "-p <path>   Set path for scene resources. Default is output file path\n"
            "-r <name>   Use the named scene node as root node\n"
            "-f <freq>   Animation tick frequency to use if unspecified. Default 4800\n"
            "-o          Optimize redundant submeshes. Loses scene hierarchy and animations\n"
            "-s <filter> Include non-skinning bones in the model's skeleton. Can be given a\n"
            "            case-insensitive semicolon separated filter list. Bone is included\n"
            "            if its name contains any of the filters. Prefix filter with minus\n"
            "            sign to use as an exclude. For example -s \"Bip01;-Dummy;-Helper\"\n"
            "-t          Generate tangents\n"
            "-v          Enable verbose Assimp library logging\n"
            "-eao        Interpret material emissive texture as ambient occlusion\n"
            "-cm         Check and do not overwrite if material exists\n"
            "-ct         Check and do not overwrite if texture exists\n"
            "-ctn        Check and do not overwrite if texture has newer timestamp\n"
            "-am         Export all meshes even if identical (scene mode only)\n"
            "-bp         Move bones to bind pose before saving model\n"
        );
    }

    context_->RegisterSubsystem(new FileSystem(context_));
    context_->RegisterSubsystem(new ResourceCache(context_));
    context_->RegisterSubsystem(new WorkQueue(context_));
    RegisterSceneLibrary(context_);
    RegisterGraphicsLibrary(context_);
#ifdef URHO3D_PHYSICS
    RegisterPhysicsLibrary(context_);
#endif

    String command = arguments[0].ToLower();
    String rootNodeName;

    unsigned flags =
        aiProcess_ConvertToLeftHanded |
        aiProcess_JoinIdenticalVertices |
        aiProcess_Triangulate |
        aiProcess_GenSmoothNormals |
        aiProcess_LimitBoneWeights |
        aiProcess_ImproveCacheLocality |
        aiProcess_RemoveRedundantMaterials |
        aiProcess_FixInfacingNormals |
        aiProcess_FindInvalidData |
        aiProcess_GenUVCoords |
        aiProcess_FindInstances |
        aiProcess_OptimizeMeshes;

    for (unsigned i = 2; i < arguments.Size(); ++i)
    {
        if (arguments[i].Length() > 1 && arguments[i][0] == '-')
        {
            String argument = arguments[i].Substring(1).ToLower();
            String value = i + 1 < arguments.Size() ? arguments[i + 1] : String::EMPTY;

            if (argument == "b")
                saveBinary_ = true;
            else if (argument == "h")
            {
                flags &= ~aiProcess_GenSmoothNormals;
                flags |= aiProcess_GenNormals;
            }
            else if (argument == "i")
                localIDs_ = true;
            else if (argument == "l")
                saveMaterialList_ = true;
            else if (argument == "t")
                flags |= aiProcess_CalcTangentSpace;
            else if (argument == "o")
                flags |= aiProcess_PreTransformVertices;
            else if (argument.Length() == 2 && argument[0] == 'n')
            {
                switch (tolower(argument[1]))
                {
                case 'a':
                    noAnimations_ = true;
                    break;

                case 'c':
                    noMaterialDiffuseColor_ = true;
                    break;

                case 'm':
                    noMaterials_ = true;
                    break;

                case 'h':
                    noHierarchy_ = true;
                    break;

                case 'e':
                    noEmptyNodes_ = true;
                    break;

                case 's':
                    useSubdirs_ = false;
                    break;

                case 't':
                    noTextures_ = true;
                    break;

                case 'z':
                    createZone_ = false;
                    break;

                case 'f':
                    flags &= ~aiProcess_FixInfacingNormals;
                    break;
                }
            }
            else if (argument == "mb" && !value.Empty())
            {
                maxBones_ = ToUInt(value);
                if (maxBones_ < 1)
                    maxBones_ = 1;
                ++i;
            }
            else if (argument == "p" && !value.Empty())
            {
                resourcePath_ = AddTrailingSlash(value);
                ++i;
            }
            else if (argument == "r" && !value.Empty())
            {
                rootNodeName = value;
                ++i;
            }
            else if (argument == "f" && !value.Empty())
            {
                defaultTicksPerSecond_ = ToFloat(value);
                ++i;
            }
            else if (argument == "s")
            {
                includeNonSkinningBones_ = true;
                if (value.Length() && (value[0] != '-' || value.Length() > 3))
                {
                    Vector<String> filters = value.Split(';');
                    for (unsigned i = 0; i < filters.Size(); ++i)
                    {
                        if (filters[i][0] == '-')
                            nonSkinningBoneExcludes_.Push(filters[i].Substring(1));
                        else
                            nonSkinningBoneIncludes_.Push(filters[i]);
                    }
                }
            }
            else if (argument == "v")
                verboseLog_ = true;
            else if (argument == "eao")
                emissiveAO_ = true;
            else if (argument == "cm")
                noOverwriteMaterial_ = true;
            else if (argument == "ct")
                noOverwriteTexture_ = true;
            else if (argument == "ctn")
                noOverwriteNewerTexture_ = true;
            else if (argument == "am")
                checkUniqueModel_ = false;
            else if (argument == "bp")
                moveToBindPose_ = true;
        }
    }

    if (command == "model" || command == "scene" || command == "node" || command == "dump")
    {
        String inFile = arguments[1];
        String outFile;
        if (arguments.Size() > 2 && arguments[2][0] != '-')
            outFile = GetInternalPath(arguments[2]);

        inputName_ = GetFileName(inFile);
        outPath_ = GetPath(outFile);

        if (resourcePath_.Empty())
        {
            resourcePath_ = outPath_;
            // If output file already has the Models/ path (model mode), do not take it into the resource path
            if (command == "model")
            {
                if (resourcePath_.EndsWith("Models/", false))
                    resourcePath_ = resourcePath_.Substring(0, resourcePath_.Length() - 7);
            }
            if (resourcePath_.Empty())
                resourcePath_ = "./";
        }

        resourcePath_ = AddTrailingSlash(resourcePath_);

        if (command != "dump" && outFile.Empty())
            ErrorExit("No output file defined");

        if (verboseLog_)
            Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE, aiDefaultLogStream_STDOUT);

        PrintLine("Reading file " + inFile);
        scene_ = aiImportFile(GetNativePath(inFile).CString(), flags);
        if (!scene_)
            ErrorExit("Could not open or parse input file " + inFile + ": " + String(aiGetErrorString()));

        if (verboseLog_)
            Assimp::DefaultLogger::kill();

        rootNode_ = scene_->mRootNode;
        if (!rootNodeName.Empty())
        {
            rootNode_ = GetNode(rootNodeName, rootNode_, false);
            if (!rootNode_)
                ErrorExit("Could not find scene node " + rootNodeName);
        }

        if (command == "dump")
        {
            DumpNodes(rootNode_, 0);
            return;
        }

        if (command == "model")
            ExportModel(outFile, scene_->mFlags & AI_SCENE_FLAGS_INCOMPLETE);

        if (command == "scene" || command == "node")
        {
            bool asPrefab = command == "node";
            // Saving as prefab requires the hierarchy, especially the root node
            if (asPrefab)
                noHierarchy_ = false;
            ExportScene(outFile, asPrefab);
        }

        if (!noMaterials_)
        {
            HashSet<String> usedTextures;
            ExportMaterials(usedTextures);
            if (!noTextures_)
                CopyTextures(usedTextures, GetPath(inFile));
        }
    }
    else if (command == "lod")
    {
        PODVector<float> lodDistances;
        Vector<String> modelNames;
        String outFile;

        unsigned numLodArguments = 0;
        for (unsigned i = 1; i < arguments.Size(); ++i)
        {
            if (arguments[i][0] == '-')
                break;
            ++numLodArguments;
        }
        if (numLodArguments < 4)
            ErrorExit("Must define at least 2 LOD levels");
        if (!(numLodArguments & 1))
            ErrorExit("No output file defined");

        for (unsigned i = 1; i < numLodArguments + 1; ++i)
        {
            if (i == numLodArguments)
                outFile = GetInternalPath(arguments[i]);
            else
            {
                if (i & 1)
                    lodDistances.Push(Max(ToFloat(arguments[i]), 0.0f));
                else
                    modelNames.Push(GetInternalPath(arguments[i]));
            }
        }

        if (lodDistances[0] != 0.0f)
        {
            PrintLine("Warning: first LOD distance forced to 0");
            lodDistances[0] = 0.0f;
        }

        CombineLods(lodDistances, modelNames, outFile);
    }
    else
        ErrorExit("Unrecognized command " + command);
}

void DumpNodes(aiNode* rootNode, unsigned level)
{
    if (!rootNode)
        return;

    String indent(' ', level * 2);
    Vector3 pos, scale;
    Quaternion rot;
    aiMatrix4x4 transform = GetDerivedTransform(rootNode, rootNode_);
    GetPosRotScale(transform, pos, rot, scale);

    PrintLine(indent + "Node " + FromAIString(rootNode->mName) + " pos " + String(pos));

    if (rootNode->mNumMeshes == 1)
        PrintLine(indent + "  " + String(rootNode->mNumMeshes) + " geometry");
    if (rootNode->mNumMeshes > 1)
        PrintLine(indent + "  " + String(rootNode->mNumMeshes) + " geometries");

    for (unsigned i = 0; i < rootNode->mNumChildren; ++i)
        DumpNodes(rootNode->mChildren[i], level + 1);
}

void ExportModel(const String& outName, bool animationOnly)
{
    if (outName.Empty())
        ErrorExit("No output file defined");

    OutModel model;
    model.rootNode_ = rootNode_;
    model.outName_ = outName;

    CollectMeshes(model, model.rootNode_);
    CollectBones(model, animationOnly);
    BuildBoneCollisionInfo(model);
    BuildAndSaveModel(model);
    if (!noAnimations_)
    {
        CollectAnimations(&model);
        BuildAndSaveAnimations(&model);

        // Save scene-global animations
        CollectAnimations();
        BuildAndSaveAnimations();
    }
}

void CollectMeshes(OutModel& model, aiNode* node)
{
    for (unsigned i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene_->mMeshes[node->mMeshes[i]];
        for (unsigned j = 0; j < model.meshes_.Size(); ++j)
        {
            if (mesh == model.meshes_[j])
            {
                PrintLine("Warning: same mesh found multiple times");
                break;
            }
        }

        model.meshIndices_.Insert(node->mMeshes[i]);
        model.meshes_.Push(mesh);
        model.meshNodes_.Push(node);
        model.totalVertices_ += mesh->mNumVertices;
        model.totalIndices_ += GetNumValidFaces(mesh) * 3;
    }

    for (unsigned i = 0; i < node->mNumChildren; ++i)
        CollectMeshes(model, node->mChildren[i]);
}

void CollectBones(OutModel& model, bool animationOnly)
{
    HashSet<aiNode*> necessary;
    HashSet<aiNode*> rootNodes;

    for (unsigned i = 0; i < model.meshes_.Size(); ++i)
    {
        aiMesh* mesh = model.meshes_[i];
        aiNode* meshNode = model.meshNodes_[i];
        aiNode* meshParentNode = meshNode->mParent;
        aiNode* rootNode = 0;

        for (unsigned j = 0; j < mesh->mNumBones; ++j)
        {
            aiBone* bone = mesh->mBones[j];
            String boneName(FromAIString(bone->mName));
            aiNode* boneNode = GetNode(boneName, scene_->mRootNode, true);
            if (!boneNode)
                ErrorExit("Could not find scene node for bone " + boneName);
            necessary.Insert(boneNode);
            rootNode = boneNode;

            for (;;)
            {
                boneNode = boneNode->mParent;
                if (!boneNode || ((boneNode == meshNode || boneNode == meshParentNode) && !animationOnly))
                    break;
                rootNode = boneNode;
                necessary.Insert(boneNode);
            }

            if (rootNodes.Find(rootNode) == rootNodes.End())
                rootNodes.Insert(rootNode);
        }
    }

    // If we find multiple root nodes, try to remedy by using their parent instead
    if (rootNodes.Size() > 1)
    {
        aiNode* commonParent = (*rootNodes.Begin())->mParent;
        for (HashSet<aiNode*>::Iterator i = rootNodes.Begin(); i != rootNodes.End(); ++i)
        {
            if (*i != commonParent)
            {
                if (!commonParent || (*i)->mParent != commonParent)
                    ErrorExit("Skeleton with multiple root nodes found, not supported");
            }
        }
        rootNodes.Clear();
        rootNodes.Insert(commonParent);
        necessary.Insert(commonParent);
    }

    if (rootNodes.Empty())
        return;

    model.rootBone_ = *rootNodes.Begin();

    // Move the model to bind pose now if requested
    if (moveToBindPose_)
    {
        PrintLine("Moving bones to bind pose");
        MoveToBindPose(model, model.rootBone_);
    }

    CollectBonesFinal(model.bones_, necessary, model.rootBone_);
    // Initialize the bone collision info
    model.boneRadii_.Resize(model.bones_.Size());
    model.boneHitboxes_.Resize(model.bones_.Size());
    for (unsigned i = 0; i < model.bones_.Size(); ++i)
    {
        model.boneRadii_[i] = 0.0f;
        model.boneHitboxes_[i] = BoundingBox(0.0f, 0.0f);
    }
}

void MoveToBindPose(OutModel& model, aiNode* current)
{
    String nodeName(FromAIString(current->mName));
    Matrix3x4 bindWorldTransform = GetOffsetMatrix(model, nodeName).Inverse();
    // Skip if we get an identity offset matrix (bone lookup failed)
    if (!bindWorldTransform.Equals(Matrix3x4::IDENTITY))
    {
        if (current->mParent && current != model.rootNode_)
        {
            aiMatrix4x4 parentWorldTransform = GetDerivedTransform(current->mParent, model.rootNode_, true);
            Matrix3x4 parentInverse = ToMatrix3x4(parentWorldTransform).Inverse();
            current->mTransformation = ToAIMatrix4x4(parentInverse * bindWorldTransform);
        }
        else
            current->mTransformation = ToAIMatrix4x4(bindWorldTransform);
    }

    for (unsigned i = 0; i < current->mNumChildren; ++i)
        MoveToBindPose(model, current->mChildren[i]);
}

void CollectBonesFinal(PODVector<aiNode*>& dest, const HashSet<aiNode*>& necessary, aiNode* node)
{
    bool includeBone = necessary.Find(node) != necessary.End();
    String boneName = FromAIString(node->mName);

    // Check include/exclude filters for non-skinned bones
    if (!includeBone && includeNonSkinningBones_)
    {
        // If no includes specified, include by default but check for excludes
        if (nonSkinningBoneIncludes_.Empty())
            includeBone = true;

        // Check against includes/excludes
        for (unsigned i = 0; i < nonSkinningBoneIncludes_.Size(); ++i)
        {
            if (boneName.Contains(nonSkinningBoneIncludes_[i], false))
            {
                includeBone = true;
                break;
            }
        }
        for (unsigned i = 0; i < nonSkinningBoneExcludes_.Size(); ++i)
        {
            if (boneName.Contains(nonSkinningBoneExcludes_[i], false))
            {
                includeBone = false;
                break;
            }
        }

        if (includeBone)
            PrintLine("Including non-skinning bone " + boneName);
    }

    if (includeBone)
        dest.Push(node);

    for (unsigned i = 0; i < node->mNumChildren; ++i)
        CollectBonesFinal(dest, necessary, node->mChildren[i]);
}

void CollectAnimations(OutModel* model)
{
    const aiScene* scene = scene_;
    for (unsigned i = 0; i < scene->mNumAnimations; ++i)
    {
        aiAnimation* anim = scene->mAnimations[i];
        if (allAnimations_.Contains(anim))
            continue;

        if (model)
        {
            bool modelBoneFound = false;
            for (unsigned j = 0; j < anim->mNumChannels; ++j)
            {
                aiNodeAnim* channel = anim->mChannels[j];
                String channelName = FromAIString(channel->mNodeName);
                if (GetBoneIndex(*model, channelName) != M_MAX_UNSIGNED)
                {
                    modelBoneFound = true;
                    break;
                }
            }
            if (modelBoneFound)
            {
                model->animations_.Push(anim);
                allAnimations_.Insert(anim);
            }
        }
        else
        {
            sceneAnimations_.Push(anim);
            allAnimations_.Insert(anim);
        }
    }

    /// \todo Vertex morphs are ignored for now
}

void BuildBoneCollisionInfo(OutModel& model)
{
    for (unsigned i = 0; i < model.meshes_.Size(); ++i)
    {
        aiMesh* mesh = model.meshes_[i];
        for (unsigned j = 0; j < mesh->mNumBones; ++j)
        {
            aiBone* bone = mesh->mBones[j];
            String boneName = FromAIString(bone->mName);
            unsigned boneIndex = GetBoneIndex(model, boneName);
            if (boneIndex == M_MAX_UNSIGNED)
                continue;
            for (unsigned k = 0; k < bone->mNumWeights; ++k)
            {
                float weight = bone->mWeights[k].mWeight;
                // Require skinning weight to be sufficiently large before vertex contributes to bone hitbox
                if (weight > 0.33f)
                {
                    aiVector3D vertexBoneSpace = bone->mOffsetMatrix * mesh->mVertices[bone->mWeights[k].mVertexId];
                    Vector3 vertex = ToVector3(vertexBoneSpace);
                    float radius = vertex.Length();
                    if (radius > model.boneRadii_[boneIndex])
                        model.boneRadii_[boneIndex] = radius;
                    model.boneHitboxes_[boneIndex].Merge(vertex);
                }
            }
        }
    }
}

void BuildAndSaveModel(OutModel& model)
{
    if (!model.rootNode_)
        ErrorExit("Null root node for model");
    String rootNodeName = FromAIString(model.rootNode_->mName);
    if (!model.meshes_.Size())
        ErrorExit("No geometries found starting from node " + rootNodeName);

    PrintLine("Writing model " + rootNodeName);

    SharedPtr<Model> outModel(new Model(context_));
    Vector<PODVector<unsigned> > allBoneMappings;
    BoundingBox box;

    unsigned numValidGeometries = 0;

    bool combineBuffers = true;
    // Check if buffers can be combined (same vertex element mask, under 65535 vertices)
    unsigned elementMask = GetElementMask(model.meshes_[0]);
    for (unsigned i = 0; i < model.meshes_.Size(); ++i)
    {
        if (GetNumValidFaces(model.meshes_[i]))
        {
            ++numValidGeometries;
            if (i > 0 && GetElementMask(model.meshes_[i]) != elementMask)
                combineBuffers = false;
        }
    }
    // Check if keeping separate buffers allows to avoid 32-bit indices
    if (combineBuffers && model.totalVertices_ > 65535)
    {
        bool allUnder65k = true;
        for (unsigned i = 0; i < model.meshes_.Size(); ++i)
        {
            if (GetNumValidFaces(model.meshes_[i]))
            {
                if (model.meshes_[i]->mNumVertices > 65535)
                    allUnder65k = false;
            }
        }
        if (allUnder65k == true)
            combineBuffers = false;
    }

    SharedPtr<IndexBuffer> ib;
    SharedPtr<VertexBuffer> vb;
    Vector<SharedPtr<VertexBuffer> > vbVector;
    Vector<SharedPtr<IndexBuffer> > ibVector;
    unsigned startVertexOffset = 0;
    unsigned startIndexOffset = 0;
    unsigned destGeomIndex = 0;

    outModel->SetNumGeometries(numValidGeometries);

    for (unsigned i = 0; i < model.meshes_.Size(); ++i)
    {
        aiMesh* mesh = model.meshes_[i];
        unsigned elementMask = GetElementMask(mesh);
        unsigned validFaces = GetNumValidFaces(mesh);
        if (!validFaces)
            continue;

        bool largeIndices;
        if (combineBuffers)
            largeIndices = model.totalIndices_ > 65535;
        else
            largeIndices = mesh->mNumVertices > 65535;

        // Create new buffers if necessary
        if (!combineBuffers || vbVector.Empty())
        {
            vb = new VertexBuffer(context_);
            ib = new IndexBuffer(context_);

            if (combineBuffers)
            {
                ib->SetSize(model.totalIndices_, largeIndices);
                vb->SetSize(model.totalVertices_, elementMask);
            }
            else
            {
                ib->SetSize(validFaces * 3, largeIndices);
                vb->SetSize(mesh->mNumVertices, elementMask);
            }

            vbVector.Push(vb);
            ibVector.Push(ib);
            startVertexOffset = 0;
            startIndexOffset = 0;
        }

        // Get the world transform of the mesh for baking into the vertices
        Matrix3x4 vertexTransform;
        Matrix3 normalTransform;
        Vector3 pos, scale;
        Quaternion rot;
        GetPosRotScale(GetMeshBakingTransform(model.meshNodes_[i], model.rootNode_), pos, rot, scale);
        vertexTransform = Matrix3x4(pos, rot, scale);
        normalTransform = rot.RotationMatrix();

        SharedPtr<Geometry> geom(new Geometry(context_));

        PrintLine("Writing geometry " + String(i) + " with " + String(mesh->mNumVertices) + " vertices " +
            String(validFaces * 3) + " indices");

        unsigned char* vertexData = vb->GetShadowData();
        unsigned char* indexData = ib->GetShadowData();

        // Build the index data
        if (!largeIndices)
        {
            unsigned short* dest = (unsigned short*)indexData + startIndexOffset;
            for (unsigned j = 0; j < mesh->mNumFaces; ++j)
                WriteShortIndices(dest, mesh, j, startVertexOffset);
        }
        else
        {
            unsigned* dest = (unsigned*)indexData + startIndexOffset;
            for (unsigned j = 0; j < mesh->mNumFaces; ++j)
                WriteLargeIndices(dest, mesh, j, startVertexOffset);
        }

        // Build the vertex data
        // If there are bones, get blend data
        Vector<PODVector<unsigned char> > blendIndices;
        Vector<PODVector<float> > blendWeights;
        PODVector<unsigned> boneMappings;
        if (model.bones_.Size())
            GetBlendData(model, mesh, boneMappings, blendIndices, blendWeights);

        float* dest = (float*)((unsigned char*)vertexData + startVertexOffset * vb->GetVertexSize());
        for (unsigned j = 0; j < mesh->mNumVertices; ++j)
            WriteVertex(dest, mesh, j, elementMask, box, vertexTransform, normalTransform, blendIndices, blendWeights);

        // Calculate the geometry center
        Vector3 center = Vector3::ZERO;
        if (validFaces)
        {
            for (unsigned j = 0; j < mesh->mNumFaces; ++j)
            {
                if (mesh->mFaces[j].mNumIndices == 3)
                {
                    center += vertexTransform * ToVector3(mesh->mVertices[mesh->mFaces[j].mIndices[0]]);
                    center += vertexTransform * ToVector3(mesh->mVertices[mesh->mFaces[j].mIndices[1]]);
                    center += vertexTransform * ToVector3(mesh->mVertices[mesh->mFaces[j].mIndices[2]]);
                }
            }

            center /= (float)validFaces * 3;
        }

        // Define the geometry
        geom->SetIndexBuffer(ib);
        geom->SetVertexBuffer(0, vb);
        geom->SetDrawRange(TRIANGLE_LIST, startIndexOffset, validFaces * 3, true);
        outModel->SetNumGeometryLodLevels(destGeomIndex, 1);
        outModel->SetGeometry(destGeomIndex, 0, geom);
        outModel->SetGeometryCenter(destGeomIndex, center);
        if (model.bones_.Size() > maxBones_)
            allBoneMappings.Push(boneMappings);

        startVertexOffset += mesh->mNumVertices;
        startIndexOffset += validFaces * 3;
        ++destGeomIndex;
    }

    // Define the model buffers and bounding box
    PODVector<unsigned> emptyMorphRange;
    outModel->SetVertexBuffers(vbVector, emptyMorphRange, emptyMorphRange);
    outModel->SetIndexBuffers(ibVector);
    outModel->SetBoundingBox(box);

    // Build skeleton if necessary
    if (model.bones_.Size() && model.rootBone_)
    {
        PrintLine("Writing skeleton with " + String(model.bones_.Size()) + " bones, rootbone " +
            FromAIString(model.rootBone_->mName));

        Skeleton skeleton;
        Vector<Bone>& bones = skeleton.GetModifiableBones();

        for (unsigned i = 0; i < model.bones_.Size(); ++i)
        {
            aiNode* boneNode = model.bones_[i];
            String boneName(FromAIString(boneNode->mName));

            Bone newBone;
            newBone.name_ = boneName;

            aiMatrix4x4 transform = boneNode->mTransformation;
            // Make the root bone transform relative to the model's root node, if it is not already
            if (boneNode == model.rootBone_)
                transform = GetDerivedTransform(boneNode, model.rootNode_);

            GetPosRotScale(transform, newBone.initialPosition_, newBone.initialRotation_, newBone.initialScale_);

            // Get offset information if exists
            newBone.offsetMatrix_ = GetOffsetMatrix(model, boneName);
            newBone.radius_ = model.boneRadii_[i];
            newBone.boundingBox_ = model.boneHitboxes_[i];
            newBone.collisionMask_ = BONECOLLISION_SPHERE | BONECOLLISION_BOX;
            newBone.parentIndex_ = i;
            bones.Push(newBone);
        }
        // Set the bone hierarchy
        for (unsigned i = 1; i < model.bones_.Size(); ++i)
        {
            String parentName = FromAIString(model.bones_[i]->mParent->mName);
            for (unsigned j = 0; j < bones.Size(); ++j)
            {
                if (bones[j].name_ == parentName)
                {
                    bones[i].parentIndex_ = j;
                    break;
                }
            }
        }

        outModel->SetSkeleton(skeleton);
        if (model.bones_.Size() > maxBones_)
            outModel->SetGeometryBoneMappings(allBoneMappings);
    }

    File outFile(context_);
    if (!outFile.Open(model.outName_, FILE_WRITE))
        ErrorExit("Could not open output file " + model.outName_);
    outModel->Save(outFile);

    // If exporting materials, also save material list for use by the editor
    if (!noMaterials_ && saveMaterialList_)
    {
        String materialListName = ReplaceExtension(model.outName_, ".txt");
        File listFile(context_);
        if (listFile.Open(materialListName, FILE_WRITE))
        {
            for (unsigned i = 0; i < model.meshes_.Size(); ++i)
                listFile.WriteLine(GetMeshMaterialName(model.meshes_[i]));
        }
        else
            PrintLine("Warning: could not write material list file " + materialListName);
    }
}

void BuildAndSaveAnimations(OutModel* model)
{
    const PODVector<aiAnimation*>& animations = model ? model->animations_ : sceneAnimations_;

    for (unsigned i = 0; i < animations.Size(); ++i)
    {
        aiAnimation* anim = animations[i];

        float duration = (float)anim->mDuration;
        String animName = FromAIString(anim->mName);
        String animOutName;

        if (animName.Empty())
            animName = "Anim" + String(i + 1);
        if (model)
            animOutName = GetPath(model->outName_) + GetFileName(model->outName_) + "_" + SanitateAssetName(animName) + ".ani";
        else
            animOutName = outPath_ + SanitateAssetName(animName) + ".ani";

        float ticksPerSecond = (float)anim->mTicksPerSecond;
        // If ticks per second not specified, it's probably a .X file. In this case use the default tick rate
        if (ticksPerSecond < M_EPSILON)
            ticksPerSecond = defaultTicksPerSecond_;
        float tickConversion = 1.0f / ticksPerSecond;

        // Find out the start time of animation from each channel's first keyframe for adjusting the keyframe times
        // to start from zero
        float startTime = duration;
        for (unsigned j = 0; j < anim->mNumChannels; ++j)
        {
            aiNodeAnim* channel = anim->mChannels[j];
            if (channel->mNumPositionKeys > 0)
                startTime = Min(startTime, (float)channel->mPositionKeys[0].mTime);
            if (channel->mNumRotationKeys > 0)
                startTime = Min(startTime, (float)channel->mRotationKeys[0].mTime);
            if (channel->mScalingKeys > 0)
                startTime = Min(startTime, (float)channel->mScalingKeys[0].mTime);
        }
        duration -= startTime;

        SharedPtr<Animation> outAnim(new Animation(context_));
        outAnim->SetAnimationName(animName);
        outAnim->SetLength(duration * tickConversion);

        PrintLine("Writing animation " + animName + " length " + String(outAnim->GetLength()));
        for (unsigned j = 0; j < anim->mNumChannels; ++j)
        {
            aiNodeAnim* channel = anim->mChannels[j];
            String channelName = FromAIString(channel->mNodeName);
            aiNode* boneNode = 0;
            bool isRootBone = false;

            if (model)
            {
                unsigned boneIndex = GetBoneIndex(*model, channelName);
                if (boneIndex == M_MAX_UNSIGNED)
                {
                    PrintLine("Warning: skipping animation track " + channelName + " not found in model skeleton");
                    outAnim->RemoveTrack(channelName);
                    continue;
                }
                boneNode = model->bones_[boneIndex];
                isRootBone = boneIndex == 0;
            }
            else
            {
                boneNode = GetNode(channelName, scene_->mRootNode);
                if (!boneNode)
                {
                    PrintLine("Warning: skipping animation track " + channelName + " whose scene node was not found");
                    outAnim->RemoveTrack(channelName);
                    continue;
                }
            }

            // To export single frame animation, check if first key frame is identical to bone transformation
            aiVector3D bonePos, boneScale;
            aiQuaternion boneRot;
            boneNode->mTransformation.Decompose(boneScale, boneRot, bonePos);

            bool posEqual = true;
            bool scaleEqual = true;
            bool rotEqual = true;

            if (channel->mNumPositionKeys > 0 && !ToVector3(bonePos).Equals(ToVector3(channel->mPositionKeys[0].mValue)))
                posEqual = false;
            if (channel->mNumScalingKeys > 0 && !ToVector3(boneScale).Equals(ToVector3(channel->mScalingKeys[0].mValue)))
                scaleEqual = false;
            if (channel->mNumRotationKeys > 0 && !ToQuaternion(boneRot).Equals(ToQuaternion(channel->mRotationKeys[0].mValue)))
                rotEqual = false;

            AnimationTrack* track = outAnim->CreateTrack(channelName);

            // Check which channels are used
            track->channelMask_ = 0;
            if (channel->mNumPositionKeys > 1 || !posEqual)
                track->channelMask_ |= CHANNEL_POSITION;
            if (channel->mNumRotationKeys > 1 || !rotEqual)
                track->channelMask_ |= CHANNEL_ROTATION;
            if (channel->mNumScalingKeys > 1 || !scaleEqual)
                track->channelMask_ |= CHANNEL_SCALE;
            // Check for redundant identity scale in all keyframes and remove in that case
            if (track->channelMask_ & CHANNEL_SCALE)
            {
                bool redundantScale = true;
                for (unsigned k = 0; k < channel->mNumScalingKeys; ++k)
                {
                    float SCALE_EPSILON = 0.000001f;
                    Vector3 scaleVec = ToVector3(channel->mScalingKeys[k].mValue);
                    if (fabsf(scaleVec.x_ - 1.0f) >= SCALE_EPSILON || fabsf(scaleVec.y_ - 1.0f) >= SCALE_EPSILON ||
                        fabsf(scaleVec.z_ - 1.0f) >= SCALE_EPSILON)
                    {
                        redundantScale = false;
                        break;
                    }
                }
                if (redundantScale)
                    track->channelMask_ &= ~CHANNEL_SCALE;
            }

            if (!track->channelMask_)
            {
                PrintLine("Warning: skipping animation track " + channelName + " with no keyframes");
                outAnim->RemoveTrack(channelName);
                continue;
            }

            // Currently only same amount of keyframes is supported
            // Note: should also check the times of individual keyframes for match
            if ((channel->mNumPositionKeys > 1 && channel->mNumRotationKeys > 1 && channel->mNumPositionKeys != channel->mNumRotationKeys) ||
                (channel->mNumPositionKeys > 1 && channel->mNumScalingKeys > 1 && channel->mNumPositionKeys != channel->mNumScalingKeys) ||
                (channel->mNumRotationKeys > 1 && channel->mNumScalingKeys > 1 && channel->mNumRotationKeys != channel->mNumScalingKeys))
            {
                PrintLine("Warning: differing amounts of channel keyframes, skipping animation track " + channelName);
                outAnim->RemoveTrack(channelName);
                continue;
            }

            unsigned keyFrames = channel->mNumPositionKeys;
            if (channel->mNumRotationKeys > keyFrames)
                keyFrames = channel->mNumRotationKeys;
            if (channel->mNumScalingKeys > keyFrames)
                keyFrames = channel->mNumScalingKeys;

            for (unsigned k = 0; k < keyFrames; ++k)
            {
                AnimationKeyFrame kf;
                kf.time_ = 0.0f;
                kf.position_ = Vector3::ZERO;
                kf.rotation_ = Quaternion::IDENTITY;
                kf.scale_ = Vector3::ONE;

                // Get time for the keyframe. Adjust with animation's start time
                if (track->channelMask_ & CHANNEL_POSITION && k < channel->mNumPositionKeys)
                    kf.time_ = ((float)channel->mPositionKeys[k].mTime - startTime) * tickConversion;
                else if (track->channelMask_ & CHANNEL_ROTATION && k < channel->mNumRotationKeys)
                    kf.time_ = ((float)channel->mRotationKeys[k].mTime - startTime) * tickConversion;
                else if (track->channelMask_ & CHANNEL_SCALE && k < channel->mNumScalingKeys)
                    kf.time_ = ((float)channel->mScalingKeys[k].mTime - startTime) * tickConversion;

                // Make sure time stays positive
                kf.time_ = Max(kf.time_, 0.0f);

                // Start with the bone's base transform
                aiMatrix4x4 boneTransform = boneNode->mTransformation;
                aiVector3D pos, scale;
                aiQuaternion rot;
                boneTransform.Decompose(scale, rot, pos);
                // Then apply the active channels
                if (track->channelMask_ & CHANNEL_POSITION && k < channel->mNumPositionKeys)
                    pos = channel->mPositionKeys[k].mValue;
                if (track->channelMask_ & CHANNEL_ROTATION && k < channel->mNumRotationKeys)
                    rot = channel->mRotationKeys[k].mValue;
                if (track->channelMask_ & CHANNEL_SCALE && k < channel->mNumScalingKeys)
                    scale = channel->mScalingKeys[k].mValue;

                // If root bone, transform with the model root node transform
                if (model && isRootBone)
                {
                    aiMatrix4x4 transMat, scaleMat, rotMat;
                    aiMatrix4x4::Translation(pos, transMat);
                    aiMatrix4x4::Scaling(scale, scaleMat);
                    rotMat = aiMatrix4x4(rot.GetMatrix());
                    aiMatrix4x4 tform = transMat * rotMat * scaleMat;
                    tform = GetDerivedTransform(tform, boneNode, model->rootNode_);
                    tform.Decompose(scale, rot, pos);
                }

                if (track->channelMask_ & CHANNEL_POSITION)
                    kf.position_ = ToVector3(pos);
                if (track->channelMask_ & CHANNEL_ROTATION)
                    kf.rotation_ = ToQuaternion(rot);
                if (track->channelMask_ & CHANNEL_SCALE)
                    kf.scale_ = ToVector3(scale);

                track->keyFrames_.Push(kf);
            }
        }

        File outFile(context_);
        if (!outFile.Open(animOutName, FILE_WRITE))
            ErrorExit("Could not open output file " + animOutName);
        outAnim->Save(outFile);
    }
}

void ExportScene(const String& outName, bool asPrefab)
{
    OutScene outScene;
    outScene.outName_ = outName;
    outScene.rootNode_ = rootNode_;

    if (useSubdirs_)
        context_->GetSubsystem<FileSystem>()->CreateDir(resourcePath_ + "Models");

    CollectSceneModels(outScene, rootNode_);

    // Save models, their material lists and animations
    for (unsigned i = 0; i < outScene.models_.Size(); ++i)
        BuildAndSaveModel(outScene.models_[i]);

    // Save scene-global animations
    if (!noAnimations_)
    {
        CollectAnimations();
        BuildAndSaveAnimations();
    }

    // Save scene
    BuildAndSaveScene(outScene, asPrefab);
}

void CollectSceneModels(OutScene& scene, aiNode* node)
{
    Vector<Pair<aiNode*, aiMesh*> > meshes;
    GetMeshesUnderNode(meshes, node);

    if (meshes.Size())
    {
        OutModel model;
        model.rootNode_ = node;
        model.outName_ = resourcePath_ + (useSubdirs_ ? "Models/" : "") + SanitateAssetName(FromAIString(node->mName)) + ".mdl";
        for (unsigned i = 0; i < meshes.Size(); ++i)
        {
            aiMesh* mesh = meshes[i].second_;
            unsigned meshIndex = GetMeshIndex(mesh);
            model.meshIndices_.Insert(meshIndex);
            model.meshes_.Push(mesh);
            model.meshNodes_.Push(meshes[i].first_);
            model.totalVertices_ += mesh->mNumVertices;
            model.totalIndices_ += GetNumValidFaces(mesh) * 3;
        }

        // Check if a model with identical mesh indices already exists. If yes, do not export twice
        bool unique = true;
        if (checkUniqueModel_)
        {
            for (unsigned i = 0; i < scene.models_.Size(); ++i)
            {
                if (scene.models_[i].meshIndices_ == model.meshIndices_)
                {
                    PrintLine("Added node " + FromAIString(node->mName));
                    scene.nodes_.Push(node);
                    scene.nodeModelIndices_.Push(i);
                    unique = false;
                    break;
                }
            }
        }
        if (unique)
        {
            PrintLine("Added model " + model.outName_);
            PrintLine("Added node " + FromAIString(node->mName));
            CollectBones(model);
            BuildBoneCollisionInfo(model);
            if (!noAnimations_)
            {
                CollectAnimations(&model);
                BuildAndSaveAnimations(&model);
            }

            scene.models_.Push(model);
            scene.nodes_.Push(node);
            scene.nodeModelIndices_.Push(scene.models_.Size() - 1);
        }
    }

    for (unsigned i = 0; i < node->mNumChildren; ++i)
        CollectSceneModels(scene, node->mChildren[i]);
}

void CreateHierarchy(Scene* scene, aiNode* srcNode, HashMap<aiNode*, Node*>& nodeMapping)
{
    CreateSceneNode(scene, srcNode, nodeMapping);
    for (unsigned i = 0; i < srcNode->mNumChildren; ++i)
        CreateHierarchy(scene, srcNode->mChildren[i], nodeMapping);
}

Node* CreateSceneNode(Scene* scene, aiNode* srcNode, HashMap<aiNode*, Node*>& nodeMapping)
{
    if (nodeMapping.Contains(srcNode))
        return nodeMapping[srcNode];
    // Flatten hierarchy if requested
    if (noHierarchy_)
    {
        Node* outNode = scene->CreateChild(FromAIString(srcNode->mName), localIDs_ ? LOCAL : REPLICATED);
        Vector3 pos, scale;
        Quaternion rot;
        GetPosRotScale(GetDerivedTransform(srcNode, rootNode_), pos, rot, scale);
        outNode->SetTransform(pos, rot, scale);
        nodeMapping[srcNode] = outNode;

        return outNode;
    }

    if (srcNode == rootNode_ || !srcNode->mParent)
    {
        Node* outNode = scene->CreateChild(FromAIString(srcNode->mName), localIDs_ ? LOCAL : REPLICATED);
        Vector3 pos, scale;
        Quaternion rot;
        GetPosRotScale(srcNode->mTransformation, pos, rot, scale);
        outNode->SetTransform(pos, rot, scale);
        nodeMapping[srcNode] = outNode;

        return outNode;
    }
    else
    {
        // Ensure the existence of the parent chain as in the original file
        if (!nodeMapping.Contains(srcNode->mParent))
            CreateSceneNode(scene, srcNode->mParent, nodeMapping);

        Node* parent = nodeMapping[srcNode->mParent];
        Node* outNode = parent->CreateChild(FromAIString(srcNode->mName), localIDs_ ? LOCAL : REPLICATED);
        Vector3 pos, scale;
        Quaternion rot;
        GetPosRotScale(srcNode->mTransformation, pos, rot, scale);
        outNode->SetTransform(pos, rot, scale);
        nodeMapping[srcNode] = outNode;

        return outNode;
    }
}

void BuildAndSaveScene(OutScene& scene, bool asPrefab)
{
    if (!asPrefab)
        PrintLine("Writing scene");
    else
        PrintLine("Writing node hierarchy");

    SharedPtr<Scene> outScene(new Scene(context_));

    if (!asPrefab)
    {
        #ifdef URHO3D_PHYSICS
        /// \todo Make the physics properties configurable
        outScene->CreateComponent<PhysicsWorld>();
        #endif

        /// \todo Make the octree properties configurable, or detect from the scene contents
        outScene->CreateComponent<Octree>();

        outScene->CreateComponent<DebugRenderer>();

        if (createZone_)
        {
            Node* zoneNode = outScene->CreateChild("Zone", localIDs_ ? LOCAL : REPLICATED);
            Zone* zone = zoneNode->CreateComponent<Zone>();
            zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.f));
            zone->SetAmbientColor(Color(0.25f, 0.25f, 0.25f));

            // Create default light only if scene does not define them
            if (!scene_->HasLights())
            {
                Node* lightNode = outScene->CreateChild("GlobalLight", localIDs_ ? LOCAL : REPLICATED);
                Light* light = lightNode->CreateComponent<Light>();
                light->SetLightType(LIGHT_DIRECTIONAL);
                lightNode->SetRotation(Quaternion(60.0f, 30.0f, 0.0f));
            }
        }
    }

    ResourceCache* cache = context_->GetSubsystem<ResourceCache>();

    HashMap<aiNode*, Node*> nodeMapping;

    Node* outRootNode = 0;
    if (asPrefab)
        outRootNode = CreateSceneNode(outScene, rootNode_, nodeMapping);
    else
    {
        // If not saving as a prefab, associate the root node with the scene first to prevent unnecessary creation of a root
        // However do not do that if the root node does not have an identity matrix, or itself contains a model
        // (models at the Urho scene root are not preferable)
        if (ToMatrix3x4(rootNode_->mTransformation).Equals(Matrix3x4::IDENTITY) && !scene.nodes_.Contains(rootNode_))
           nodeMapping[rootNode_] = outScene;
    }

    // If is allowed to export empty nodes, export the full Assimp node hierarchy first
    if (!noHierarchy_ && !noEmptyNodes_)
        CreateHierarchy(outScene, rootNode_, nodeMapping);

    // Create geometry nodes
    for (unsigned i = 0; i < scene.nodes_.Size(); ++i)
    {
        const OutModel& model = scene.models_[scene.nodeModelIndices_[i]];
        Node* modelNode = CreateSceneNode(outScene, scene.nodes_[i], nodeMapping);
        StaticModel* staticModel = model.bones_.Empty() ? modelNode->CreateComponent<StaticModel>() : modelNode->CreateComponent<AnimatedModel>();

        // Create a dummy model so that the reference can be stored
        String modelName = (useSubdirs_ ? "Models/" : "") + GetFileNameAndExtension(model.outName_);
        if (!cache->Exists(modelName))
        {
            Model* dummyModel = new Model(context_);
            dummyModel->SetName(modelName);
            dummyModel->SetNumGeometries(model.meshes_.Size());
            cache->AddManualResource(dummyModel);
        }
        staticModel->SetModel(cache->GetResource<Model>(modelName));

        // Set materials if they are known
        for (unsigned j = 0; j < model.meshes_.Size(); ++j)
        {
            String matName = GetMeshMaterialName(model.meshes_[j]);
            // Create a dummy material so that the reference can be stored
            if (!cache->Exists(matName))
            {
                Material* dummyMat = new Material(context_);
                dummyMat->SetName(matName);
                cache->AddManualResource(dummyMat);
            }
            staticModel->SetMaterial(j, cache->GetResource<Material>(matName));
        }
    }

    // Create lights
    if (!asPrefab)
    {
        for (unsigned i = 0; i < scene_->mNumLights; ++i)
        {
            aiLight* light = scene_->mLights[i];
            aiNode* lightNode = GetNode(FromAIString(light->mName), rootNode_, true);
            if (!lightNode)
                continue;
            Node* outNode = CreateSceneNode(outScene, lightNode, nodeMapping);

            Vector3 lightAdjustPosition = ToVector3(light->mPosition);
            Vector3 lightAdjustDirection = ToVector3(light->mDirection);
            // If light is not aligned at the scene node, an adjustment node needs to be created
            if (!lightAdjustPosition.Equals(Vector3::ZERO) || (light->mType != aiLightSource_POINT &&
                !lightAdjustDirection.Equals(Vector3::FORWARD)))
            {
                outNode = outNode->CreateChild("LightAdjust");
                outNode->SetPosition(lightAdjustPosition);
                outNode->SetDirection(lightAdjustDirection);
            }

            Light* outLight = outNode->CreateComponent<Light>();
            outLight->SetColor(Color(light->mColorDiffuse.r, light->mColorDiffuse.g, light->mColorDiffuse.b));

            switch (light->mType)
            {
            case aiLightSource_DIRECTIONAL:
                outLight->SetLightType(LIGHT_DIRECTIONAL);
                break;
            case aiLightSource_SPOT:
                outLight->SetLightType(LIGHT_SPOT);
                outLight->SetFov(light->mAngleOuterCone * 0.5f * M_RADTODEG);
                break;
            case aiLightSource_POINT:
                outLight->SetLightType(LIGHT_POINT);
                break;
            default:
                break;
            }

            // Calculate range from attenuation parameters so that light intensity has been reduced to 10% at that distance
            if (light->mType != aiLightSource_DIRECTIONAL)
            {
                float a = light->mAttenuationQuadratic;
                float b = light->mAttenuationLinear;
                float c = -10.0f;
                if (!Equals(a, 0.0f))
                {
                    float root1 = (-b + sqrtf(b * b - 4.0f * a * c)) / (2.0f * a);
                    float root2 = (-b - sqrtf(b * b - 4.0f * a * c)) / (2.0f * a);
                    outLight->SetRange(Max(root1, root2));
                }
                else if (!Equals(b, 0.0f))
                    outLight->SetRange(-c / b);
            }
        }
    }

    File file(context_);
    if (!file.Open(scene.outName_, FILE_WRITE))
        ErrorExit("Could not open output file " + scene.outName_);
    if (!asPrefab)
    {
        if (!saveBinary_)
            outScene->SaveXML(file);
        else
            outScene->Save(file);
    }
    else
    {
        if (!saveBinary_)
            outRootNode->SaveXML(file);
        else
            outRootNode->Save(file);
    }
}

void ExportMaterials(HashSet<String>& usedTextures)
{
    if (useSubdirs_)
        context_->GetSubsystem<FileSystem>()->CreateDir(resourcePath_ + "Materials");

    for (unsigned i = 0; i < scene_->mNumMaterials; ++i)
        BuildAndSaveMaterial(scene_->mMaterials[i], usedTextures);
}

void BuildAndSaveMaterial(aiMaterial* material, HashSet<String>& usedTextures)
{
    aiString matNameStr;
    material->Get(AI_MATKEY_NAME, matNameStr);
    String matName = SanitateAssetName(FromAIString(matNameStr));
    if (matName.Trimmed().Empty())
        matName = GenerateMaterialName(material);

    // Do not actually create a material instance, but instead craft an xml file manually
    XMLFile outMaterial(context_);
    XMLElement materialElem = outMaterial.CreateRoot("material");

    String diffuseTexName;
    String normalTexName;
    String specularTexName;
    String lightmapTexName;
    String emissiveTexName;
    Color diffuseColor = Color::WHITE;
    Color specularColor;
    Color emissiveColor = Color::BLACK;
    bool hasAlpha = false;
    bool twoSided = false;
    float specPower = 1.0f;

    aiString stringVal;
    float floatVal;
    int intVal;
    aiColor3D colorVal;

    if (material->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), stringVal) == AI_SUCCESS)
        diffuseTexName = GetFileNameAndExtension(FromAIString(stringVal));
    if (material->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), stringVal) == AI_SUCCESS)
        normalTexName = GetFileNameAndExtension(FromAIString(stringVal));
    if (material->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), stringVal) == AI_SUCCESS)
        specularTexName = GetFileNameAndExtension(FromAIString(stringVal));
    if (material->Get(AI_MATKEY_TEXTURE(aiTextureType_LIGHTMAP, 0), stringVal) == AI_SUCCESS)
        lightmapTexName = GetFileNameAndExtension(FromAIString(stringVal));
    if (material->Get(AI_MATKEY_TEXTURE(aiTextureType_EMISSIVE, 0), stringVal) == AI_SUCCESS)
        emissiveTexName = GetFileNameAndExtension(FromAIString(stringVal));
    if (!noMaterialDiffuseColor_)
    {
        if (material->Get(AI_MATKEY_COLOR_DIFFUSE, colorVal) == AI_SUCCESS)
            diffuseColor = Color(colorVal.r, colorVal.g, colorVal.b);
    }
    if (material->Get(AI_MATKEY_COLOR_SPECULAR, colorVal) == AI_SUCCESS)
        specularColor = Color(colorVal.r, colorVal.g, colorVal.b);
    if (!emissiveAO_)
    {
        if (material->Get(AI_MATKEY_COLOR_EMISSIVE, colorVal) == AI_SUCCESS)
            emissiveColor = Color(colorVal.r, colorVal.g, colorVal.b);
    }
    if (material->Get(AI_MATKEY_OPACITY, floatVal) == AI_SUCCESS)
    {
        /// \hack New Assimp behavior - some materials may return 0 opacity, which is invisible.
        /// Revert to full opacity in that case
        if (floatVal < M_EPSILON)
            floatVal = 1.0f;

        if (floatVal < 1.0f)
            hasAlpha = true;
        diffuseColor.a_ = floatVal;
    }
    if (material->Get(AI_MATKEY_SHININESS, floatVal) == AI_SUCCESS)
        specPower = floatVal;
    if (material->Get(AI_MATKEY_TWOSIDED, intVal) == AI_SUCCESS)
        twoSided = (intVal != 0);

    String techniqueName = "Techniques/NoTexture";
    if (!diffuseTexName.Empty())
    {
        techniqueName = "Techniques/Diff";
        if (!normalTexName.Empty())
            techniqueName += "Normal";
        if (!specularTexName.Empty())
            techniqueName += "Spec";
        // For now lightmap does not coexist with normal & specular
        if (normalTexName.Empty() && specularTexName.Empty() && !lightmapTexName.Empty())
            techniqueName += "LightMap";
        if (lightmapTexName.Empty() && !emissiveTexName.Empty())
            techniqueName += emissiveAO_ ? "AO" : "Emissive";
    }
    if (hasAlpha)
        techniqueName += "Alpha";

    XMLElement techniqueElem = materialElem.CreateChild("technique");
    techniqueElem.SetString("name", techniqueName + ".xml");

    if (!diffuseTexName.Empty())
    {
        XMLElement diffuseElem = materialElem.CreateChild("texture");
        diffuseElem.SetString("unit", "diffuse");
        diffuseElem.SetString("name", GetMaterialTextureName(diffuseTexName));
        usedTextures.Insert(diffuseTexName);
    }
    if (!normalTexName.Empty())
    {
        XMLElement normalElem = materialElem.CreateChild("texture");
        normalElem.SetString("unit", "normal");
        normalElem.SetString("name", GetMaterialTextureName(normalTexName));
        usedTextures.Insert(normalTexName);
    }
    if (!specularTexName.Empty())
    {
        XMLElement specularElem = materialElem.CreateChild("texture");
        specularElem.SetString("unit", "specular");
        specularElem.SetString("name", GetMaterialTextureName(specularTexName));
        usedTextures.Insert(specularTexName);
    }
    if (!lightmapTexName.Empty())
    {
        XMLElement lightmapElem = materialElem.CreateChild("texture");
        lightmapElem.SetString("unit", "emissive");
        lightmapElem.SetString("name", GetMaterialTextureName(lightmapTexName));
        usedTextures.Insert(lightmapTexName);
    }
    if (!emissiveTexName.Empty())
    {
        XMLElement emissiveElem = materialElem.CreateChild("texture");
        emissiveElem.SetString("unit", "emissive");
        emissiveElem.SetString("name", GetMaterialTextureName(emissiveTexName));
        usedTextures.Insert(emissiveTexName);
    }

    XMLElement diffuseColorElem = materialElem.CreateChild("parameter");
    diffuseColorElem.SetString("name", "MatDiffColor");
    diffuseColorElem.SetColor("value", diffuseColor);
    XMLElement specularElem = materialElem.CreateChild("parameter");
    specularElem.SetString("name", "MatSpecColor");
    specularElem.SetVector4("value", Vector4(specularColor.r_, specularColor.g_, specularColor.b_, specPower));
    XMLElement emissiveColorElem = materialElem.CreateChild("parameter");
    emissiveColorElem.SetString("name", "MatEmissiveColor");
    emissiveColorElem.SetColor("value", emissiveColor);

    if (twoSided)
    {
        XMLElement cullElem = materialElem.CreateChild("cull");
        XMLElement shadowCullElem = materialElem.CreateChild("shadowcull");
        cullElem.SetString("value", "none");
        shadowCullElem.SetString("value", "none");
    }

    FileSystem* fileSystem = context_->GetSubsystem<FileSystem>();

    String outFileName = resourcePath_ + (useSubdirs_ ? "Materials/" : "" ) + matName + ".xml";
    if (noOverwriteMaterial_ && fileSystem->FileExists(outFileName))
    {
        PrintLine("Skipping save of existing material " + matName);
        return;
    }

    PrintLine("Writing material " + matName);

    File outFile(context_);
    if (!outFile.Open(outFileName, FILE_WRITE))
        ErrorExit("Could not open output file " + outFileName);
    outMaterial.Save(outFile);
}

void CopyTextures(const HashSet<String>& usedTextures, const String& sourcePath)
{
    FileSystem* fileSystem = context_->GetSubsystem<FileSystem>();

    if (useSubdirs_)
        fileSystem->CreateDir(resourcePath_ + "Textures");

    for (HashSet<String>::ConstIterator i = usedTextures.Begin(); i != usedTextures.End(); ++i)
    {
        // Handle assimp embedded textures
        if (i->Length() && i->At(0) == '*')
        {
            unsigned texIndex = ToInt(i->Substring(1));
            if (texIndex >= scene_->mNumTextures)
                PrintLine("Skipping out of range texture index " + String(texIndex));
            else
            {
                aiTexture* tex = scene_->mTextures[texIndex];
                String fullDestName = resourcePath_ + GenerateTextureName(texIndex);
                bool destExists = fileSystem->FileExists(fullDestName);
                if (destExists && noOverwriteTexture_)
                {
                    PrintLine("Skipping copy of existing embedded texture " + GetFileNameAndExtension(fullDestName));
                    continue;
                }
                // Encoded texture
                if (!tex->mHeight)
                {
                    PrintLine("Saving embedded texture " + GetFileNameAndExtension(fullDestName));
                    File dest(context_, fullDestName, FILE_WRITE);
                    dest.Write((const void*)tex->pcData, tex->mWidth);
                }
                // RGBA8 texture
                else
                {
                    PrintLine("Saving embedded RGBA texture " + GetFileNameAndExtension(fullDestName));
                    Image image(context_);
                    image.SetSize(tex->mWidth, tex->mHeight, 4);
                    memcpy(image.GetData(), (const void*)tex->pcData, tex->mWidth * tex->mHeight * 4);
                    image.SavePNG(fullDestName);
                }
            }
        }
        else
        {
            String fullSourceName = sourcePath + *i;
            String fullDestName = resourcePath_ + (useSubdirs_ ? "Textures/" : "") + *i;

            if (!fileSystem->FileExists(fullSourceName))
            {
                PrintLine("Skipping copy of nonexisting material texture " + *i);
                continue;
            }
            {
                File test(context_, fullSourceName);
                if (!test.GetSize())
                {
                    PrintLine("Skipping copy of zero-size material texture " + *i);
                    continue;
                }
            }

            bool destExists = fileSystem->FileExists(fullDestName);
            if (destExists && noOverwriteTexture_)
            {
                PrintLine("Skipping copy of existing texture " + *i);
                continue;
            }
            if (destExists && noOverwriteNewerTexture_ && fileSystem->GetLastModifiedTime(fullDestName) >
                fileSystem->GetLastModifiedTime(fullSourceName))
            {
                PrintLine("Skipping copying of material texture " + *i + ", destination is newer");
                continue;
            }

            PrintLine("Copying material texture " + *i);
            fileSystem->Copy(fullSourceName, fullDestName);
        }
    }
}

void CombineLods(const PODVector<float>& lodDistances, const Vector<String>& modelNames, const String& outName)
{
    // Load models
    Vector<SharedPtr<Model> > srcModels;
    for (unsigned i = 0; i < modelNames.Size(); ++i)
    {
        PrintLine("Reading LOD level " + String(i) + ": model " + modelNames[i] + " distance " + String(lodDistances[i]));
        File srcFile(context_);
        srcFile.Open(modelNames[i]);
        SharedPtr<Model> srcModel(new Model(context_));
        if (!srcModel->Load(srcFile))
            ErrorExit("Could not load input model " + modelNames[i]);
        srcModels.Push(srcModel);
    }

    // Check that none of the models already has LOD levels
    for (unsigned i = 0; i < srcModels.Size(); ++i)
    {
        for (unsigned j = 0; j < srcModels[i]->GetNumGeometries(); ++j)
        {
            if (srcModels[i]->GetNumGeometryLodLevels(j) > 1)
                ErrorExit(modelNames[i] + " already has multiple LOD levels defined");
        }
    }

    // Check for number of geometries (need to have same amount for now)
    for (unsigned i = 1; i < srcModels.Size(); ++i)
    {
        if (srcModels[i]->GetNumGeometries() != srcModels[0]->GetNumGeometries())
            ErrorExit(modelNames[i] + " has different amount of geometries than " + modelNames[0]);
    }

    // If there are bones, check for compatibility (need to have exact match for now)
    for (unsigned i = 1; i < srcModels.Size(); ++i)
    {
        if (srcModels[i]->GetSkeleton().GetNumBones() != srcModels[0]->GetSkeleton().GetNumBones())
            ErrorExit(modelNames[i] + " has different amount of bones than " + modelNames[0]);
        for (unsigned j = 0; j < srcModels[0]->GetSkeleton().GetNumBones(); ++j)
        {
            if (srcModels[i]->GetSkeleton().GetBone(j)->name_ != srcModels[0]->GetSkeleton().GetBone(j)->name_)
                ErrorExit(modelNames[i] + " has different bones than " + modelNames[0]);
        }
        if (srcModels[i]->GetGeometryBoneMappings() != srcModels[0]->GetGeometryBoneMappings())
            ErrorExit(modelNames[i] + " has different per-geometry bone mappings than " + modelNames[0]);
    }

    Vector<SharedPtr<VertexBuffer> > vbVector;
    Vector<SharedPtr<IndexBuffer> > ibVector;
    PODVector<unsigned> emptyMorphRange;

    // Create the final model
    SharedPtr<Model> outModel(new Model(context_));
    outModel->SetNumGeometries(srcModels[0]->GetNumGeometries());
    for (unsigned i = 0; i < srcModels[0]->GetNumGeometries(); ++i)
    {
        outModel->SetNumGeometryLodLevels(i, srcModels.Size());
        for (unsigned j = 0; j < srcModels.Size(); ++j)
        {
            Geometry* geometry = srcModels[j]->GetGeometry(i, 0);
            geometry->SetLodDistance(lodDistances[j]);
            outModel->SetGeometry(i, j, geometry);

            for (unsigned k = 0; k < geometry->GetNumVertexBuffers(); ++k)
            {
                SharedPtr<VertexBuffer> vb(geometry->GetVertexBuffer(k));
                if (!vbVector.Contains(vb))
                    vbVector.Push(vb);
            }

            SharedPtr<IndexBuffer> ib(geometry->GetIndexBuffer());
            if (!ibVector.Contains(ib))
                ibVector.Push(ib);
        }
    }

    outModel->SetVertexBuffers(vbVector, emptyMorphRange, emptyMorphRange);
    outModel->SetIndexBuffers(ibVector);
    outModel->SetSkeleton(srcModels[0]->GetSkeleton());
    outModel->SetGeometryBoneMappings(srcModels[0]->GetGeometryBoneMappings());
    outModel->SetBoundingBox(srcModels[0]->GetBoundingBox());
    /// \todo Vertex morphs are ignored for now

    // Save the final model
    PrintLine("Writing output model");
    File outFile(context_);
    if (!outFile.Open(outName, FILE_WRITE))
        ErrorExit("Could not open output file " + outName);
    outModel->Save(outFile);
}

void GetMeshesUnderNode(Vector<Pair<aiNode*, aiMesh*> >& dest, aiNode* node)
{
    for (unsigned i = 0; i < node->mNumMeshes; ++i)
        dest.Push(MakePair(node, scene_->mMeshes[node->mMeshes[i]]));
}

unsigned GetMeshIndex(aiMesh* mesh)
{
    for (unsigned i = 0; i < scene_->mNumMeshes; ++i)
    {
        if (scene_->mMeshes[i] == mesh)
            return i;
    }
    return M_MAX_UNSIGNED;
}

unsigned GetBoneIndex(OutModel& model, const String& boneName)
{
    for (unsigned i = 0; i < model.bones_.Size(); ++i)
    {
        if (boneName == model.bones_[i]->mName.data)
            return i;
    }
    return M_MAX_UNSIGNED;
}

aiBone* GetMeshBone(OutModel& model, const String& boneName)
{
    for (unsigned i = 0; i < model.meshes_.Size(); ++i)
    {
        aiMesh* mesh = model.meshes_[i];
        for (unsigned j = 0; j < mesh->mNumBones; ++j)
        {
            aiBone* bone = mesh->mBones[j];
            if (boneName == bone->mName.data)
                return bone;
        }
    }
    return 0;
}

Matrix3x4 GetOffsetMatrix(OutModel& model, const String& boneName)
{
    for (unsigned i = 0; i < model.meshes_.Size(); ++i)
    {
        aiMesh* mesh = model.meshes_[i];
        aiNode* node = model.meshNodes_[i];
        for (unsigned j = 0; j < mesh->mNumBones; ++j)
        {
            aiBone* bone = mesh->mBones[j];
            if (boneName == bone->mName.data)
            {
                aiMatrix4x4 offset = bone->mOffsetMatrix;
                aiMatrix4x4 nodeDerivedInverse = GetMeshBakingTransform(node, model.rootNode_);
                nodeDerivedInverse.Inverse();
                offset *= nodeDerivedInverse;
                return ToMatrix3x4(offset);
            }
        }
    }
    return Matrix3x4::IDENTITY;
}

void GetBlendData(OutModel& model, aiMesh* mesh, PODVector<unsigned>& boneMappings, Vector<PODVector<unsigned char> >&
    blendIndices, Vector<PODVector<float> >& blendWeights)
{
    blendIndices.Resize(mesh->mNumVertices);
    blendWeights.Resize(mesh->mNumVertices);
    boneMappings.Clear();

    // If model has more bones than can fit vertex shader parameters, write the per-geometry mappings
    if (model.bones_.Size() > maxBones_)
    {
        if (mesh->mNumBones > maxBones_)
        {
            ErrorExit(
                "Geometry (submesh) has over " + String(maxBones_) + " bone influences. Try splitting to more submeshes\n"
                "that each stay at " + String(maxBones_) + " bones or below."
            );
        }
        boneMappings.Resize(mesh->mNumBones);
        for (unsigned i = 0; i < mesh->mNumBones; ++i)
        {
            aiBone* bone = mesh->mBones[i];
            String boneName = FromAIString(bone->mName);
            unsigned globalIndex = GetBoneIndex(model, boneName);
            if (globalIndex == M_MAX_UNSIGNED)
                ErrorExit("Bone " + boneName + " not found");
            boneMappings[i] = globalIndex;
            for (unsigned j = 0; j < bone->mNumWeights; ++j)
            {
                unsigned vertex = bone->mWeights[j].mVertexId;
                blendIndices[vertex].Push(i);
                blendWeights[vertex].Push(bone->mWeights[j].mWeight);
            }
        }
    }
    else
    {
        for (unsigned i = 0; i < mesh->mNumBones; ++i)
        {
            aiBone* bone = mesh->mBones[i];
            String boneName = FromAIString(bone->mName);
            unsigned globalIndex = GetBoneIndex(model, boneName);
            if (globalIndex == M_MAX_UNSIGNED)
                ErrorExit("Bone " + boneName + " not found");
            for (unsigned j = 0; j < bone->mNumWeights; ++j)
            {
                unsigned vertex = bone->mWeights[j].mVertexId;
                blendIndices[vertex].Push(globalIndex);
                blendWeights[vertex].Push(bone->mWeights[j].mWeight);
            }
        }
    }

    // Normalize weights now if necessary, also remove too many influences
    for (unsigned i = 0; i < blendWeights.Size(); ++i)
    {
        if (blendWeights[i].Size() > 4)
        {
            PrintLine("Warning: more than 4 bone influences in vertex " + String(i));

            while (blendWeights[i].Size() > 4)
            {
                unsigned lowestIndex = 0;
                float lowest = M_INFINITY;
                for (unsigned j = 0; j < blendWeights[i].Size(); ++j)
                {
                    if (blendWeights[i][j] < lowest)
                    {
                        lowest = blendWeights[i][j];
                        lowestIndex = j;
                    }
                }
                blendWeights[i].Erase(lowestIndex);
                blendIndices[i].Erase(lowestIndex);
            }
        }

        float sum = 0.0f;
        for (unsigned j = 0; j < blendWeights[i].Size(); ++j)
            sum += blendWeights[i][j];
        if (sum != 1.0f && sum != 0.0f)
        {
            for (unsigned j = 0; j < blendWeights[i].Size(); ++j)
                blendWeights[i][j] /= sum;
        }
    }
}

String GetMeshMaterialName(aiMesh* mesh)
{
    aiMaterial* material = scene_->mMaterials[mesh->mMaterialIndex];
    aiString matNameStr;
    material->Get(AI_MATKEY_NAME, matNameStr);
    String matName = SanitateAssetName(FromAIString(matNameStr));
    if (matName.Trimmed().Empty())
        matName = GenerateMaterialName(material);

    return (useSubdirs_ ? "Materials/" : "") + matName + ".xml";
}

String GenerateMaterialName(aiMaterial* material)
{
    for (unsigned i = 0; i < scene_->mNumMaterials; ++i)
    {
        if (scene_->mMaterials[i] == material)
            return inputName_ + "_Material" + String(i);
    }

    // Should not go here
    return String::EMPTY;
}

String GetMaterialTextureName(const String& nameIn)
{
    // Detect assimp embedded texture
    if (nameIn.Length() && nameIn[0] == '*')
        return GenerateTextureName(ToInt(nameIn.Substring(1)));
    else
        return (useSubdirs_ ? "Textures/" : "") + nameIn;
}

String GenerateTextureName(unsigned texIndex)
{
    if (texIndex < scene_->mNumTextures)
    {
        // If embedded texture contains encoded data, use the format hint for file extension. Else save RGBA8 data as PNG
        aiTexture* tex = scene_->mTextures[texIndex];
        if (!tex->mHeight)
            return (useSubdirs_ ? "Textures/" : "") + inputName_ + "_Texture" + String(texIndex) + "." + tex->achFormatHint;
        else
            return (useSubdirs_ ? "Textures/" : "") + inputName_ + "_Texture" + String(texIndex) + ".png";
    }

    // Should not go here
    return String::EMPTY;
}

unsigned GetNumValidFaces(aiMesh* mesh)
{
    unsigned ret = 0;

    for (unsigned j = 0; j < mesh->mNumFaces; ++j)
    {
        if (mesh->mFaces[j].mNumIndices == 3)
            ++ret;
    }

    return ret;
}

void WriteShortIndices(unsigned short*& dest, aiMesh* mesh, unsigned index, unsigned offset)
{
    if (mesh->mFaces[index].mNumIndices == 3)
    {
        *dest++ = mesh->mFaces[index].mIndices[0] + offset;
        *dest++ = mesh->mFaces[index].mIndices[1] + offset;
        *dest++ = mesh->mFaces[index].mIndices[2] + offset;
    }
}

void WriteLargeIndices(unsigned*& dest, aiMesh* mesh, unsigned index, unsigned offset)
{
    if (mesh->mFaces[index].mNumIndices == 3)
    {
        *dest++ = mesh->mFaces[index].mIndices[0] + offset;
        *dest++ = mesh->mFaces[index].mIndices[1] + offset;
        *dest++ = mesh->mFaces[index].mIndices[2] + offset;
    }
}

void WriteVertex(float*& dest, aiMesh* mesh, unsigned index, unsigned elementMask, BoundingBox& box,
    const Matrix3x4& vertexTransform, const Matrix3& normalTransform, Vector<PODVector<unsigned char> >& blendIndices,
    Vector<PODVector<float> >& blendWeights)
{
    Vector3 vertex = vertexTransform * ToVector3(mesh->mVertices[index]);
    box.Merge(vertex);
    *dest++ = vertex.x_;
    *dest++ = vertex.y_;
    *dest++ = vertex.z_;
    if (elementMask & MASK_NORMAL)
    {
        Vector3 normal = normalTransform * ToVector3(mesh->mNormals[index]);
        *dest++ = normal.x_;
        *dest++ = normal.y_;
        *dest++ = normal.z_;
    }
    if (elementMask & MASK_COLOR)
    {
        *((unsigned*)dest) = Color(mesh->mColors[0][index].r, mesh->mColors[0][index].g, mesh->mColors[0][index].b,
            mesh->mColors[0][index].a).ToUInt();
        ++dest;
    }
    if (elementMask & MASK_TEXCOORD1)
    {
        Vector3 texCoord = ToVector3(mesh->mTextureCoords[0][index]);
        *dest++ = texCoord.x_;
        *dest++ = texCoord.y_;
    }
    if (elementMask & MASK_TEXCOORD2)
    {
        Vector3 texCoord = ToVector3(mesh->mTextureCoords[1][index]);
        *dest++ = texCoord.x_;
        *dest++ = texCoord.y_;
    }
    if (elementMask & MASK_TANGENT)
    {
        Vector3 tangent = normalTransform * ToVector3(mesh->mTangents[index]);
        Vector3 normal = normalTransform * ToVector3(mesh->mNormals[index]);
        Vector3 bitangent = normalTransform * ToVector3(mesh->mBitangents[index]);
        // Check handedness
        float w = 1.0f;
        if ((tangent.CrossProduct(normal)).DotProduct(bitangent) < 0.5f)
            w = -1.0f;

        *dest++ = tangent.x_;
        *dest++ = tangent.y_;
        *dest++ = tangent.z_;
        *dest++ = w;
    }
    if (elementMask & MASK_BLENDWEIGHTS)
    {
        for (unsigned i = 0; i < 4; ++i)
        {
            if (i < blendWeights[index].Size())
                *dest++ = blendWeights[index][i];
            else
                *dest++ = 0.0f;
        }
    }
    if (elementMask & MASK_BLENDINDICES)
    {
        unsigned char* destBytes = (unsigned char*)dest;
        ++dest;
        for (unsigned i = 0; i < 4; ++i)
        {
            if (i < blendIndices[index].Size())
                *destBytes++ = blendIndices[index][i];
            else
                *destBytes++ = 0;
        }
    }
}

unsigned GetElementMask(aiMesh* mesh)
{
    unsigned elementMask = MASK_POSITION;
    if (mesh->HasNormals())
        elementMask |= MASK_NORMAL;
    if (mesh->HasTangentsAndBitangents())
        elementMask |= MASK_TANGENT;
    if (mesh->GetNumColorChannels() > 0)
        elementMask |= MASK_COLOR;
    if (mesh->GetNumUVChannels() > 0)
        elementMask |= MASK_TEXCOORD1;
    if (mesh->GetNumUVChannels() > 1)
        elementMask |= MASK_TEXCOORD2;
    if (mesh->HasBones())
        elementMask |= (MASK_BLENDWEIGHTS | MASK_BLENDINDICES);
    return elementMask;
}

aiNode* GetNode(const String& name, aiNode* rootNode, bool caseSensitive)
{
    if (!rootNode)
        return 0;
    if (!name.Compare(rootNode->mName.data, caseSensitive))
        return rootNode;
    for (unsigned i = 0; i < rootNode->mNumChildren; ++i)
    {
        aiNode* found = GetNode(name, rootNode->mChildren[i], caseSensitive);
        if (found)
            return found;
    }
    return 0;
}

aiMatrix4x4 GetDerivedTransform(aiNode* node, aiNode* rootNode, bool rootInclusive)
{
    return GetDerivedTransform(node->mTransformation, node, rootNode, rootInclusive);
}

aiMatrix4x4 GetDerivedTransform(aiMatrix4x4 transform, aiNode* node, aiNode* rootNode, bool rootInclusive)
{
    // If basenode is defined, go only up to it in the parent chain
    while (node && node != rootNode)
    {
        node = node->mParent;
        if (!rootInclusive && node == rootNode)
            break;
        if (node)
            transform = node->mTransformation * transform;
    }
    return transform;
}

aiMatrix4x4 GetMeshBakingTransform(aiNode* meshNode, aiNode* modelRootNode)
{
    if (meshNode == modelRootNode)
        return aiMatrix4x4();
    else
        return GetDerivedTransform(meshNode, modelRootNode);
}

void GetPosRotScale(const aiMatrix4x4& transform, Vector3& pos, Quaternion& rot, Vector3& scale)
{
    aiVector3D aiPos;
    aiQuaternion aiRot;
    aiVector3D aiScale;
    transform.Decompose(aiScale, aiRot, aiPos);
    pos = ToVector3(aiPos);
    rot = ToQuaternion(aiRot);
    scale = ToVector3(aiScale);
}


String FromAIString(const aiString& str)
{
    return String(str.data);
}

Vector3 ToVector3(const aiVector3D& vec)
{
    return Vector3(vec.x, vec.y, vec.z);
}

Vector2 ToVector2(const aiVector2D& vec)
{
    return Vector2(vec.x, vec.y);
}

Quaternion ToQuaternion(const aiQuaternion& quat)
{
    return Quaternion(quat.w, quat.x, quat.y, quat.z);
}

Matrix3x4 ToMatrix3x4(const aiMatrix4x4& mat)
{
    Matrix3x4 ret;
    memcpy(&ret.m00_, &mat.a1, sizeof(Matrix3x4));
    return ret;
}

aiMatrix4x4 ToAIMatrix4x4(const Matrix3x4& mat)
{
    aiMatrix4x4 ret;
    memcpy(&ret.a1, &mat.m00_, sizeof(Matrix3x4));
    return ret;
}

String SanitateAssetName(const String& name)
{
    String fixedName = name;
    fixedName.Replace("<", "");
    fixedName.Replace(">", "");
    fixedName.Replace("?", "");
    fixedName.Replace("*", "");
    fixedName.Replace(":", "");
    fixedName.Replace("\"", "");
    fixedName.Replace("/", "");
    fixedName.Replace("\\", "");
    fixedName.Replace("|", "");

    return fixedName;
}
