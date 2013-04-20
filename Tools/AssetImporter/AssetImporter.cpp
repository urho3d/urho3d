//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Animation.h"
#include "Context.h"
#include "DebugRenderer.h"
#include "File.h"
#include "FileSystem.h"
#include "Geometry.h"
#include "Graphics.h"
#include "IndexBuffer.h"
#include "Light.h"
#include "Material.h"
#include "Model.h"
#include "Octree.h"
#include "PhysicsWorld.h"
#include "ProcessUtils.h"
#include "Quaternion.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "StaticModel.h"
#include "StringUtils.h"
#include "Vector3.h"
#include "VertexBuffer.h"
#include "WorkQueue.h"
#include "XMLFile.h"
#include "Zone.h"

#include "Sort.h"

#ifdef WIN32
#include <windows.h>
#endif

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <cstring>

#include "DebugNew.h"

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
String resourcePath_;
bool useSubdirs_ = true;
bool localIDs_ = false;
bool saveBinary_ = false;
bool createZone_ = true;
bool noAnimations_ = false;
bool noMaterials_ = false;

float defaultTicksPerSecond_ = 4800.0f;

int main(int argc, char** argv);
void Run(const Vector<String>& arguments);
void DumpNodes(aiNode* rootNode, unsigned level);

void ExportModel(const String& outName);
void CollectMeshes(OutModel& model, aiNode* node);
void CollectBones(OutModel& model);
void CollectBonesFinal(PODVector<aiNode*>& dest, const HashSet<aiNode*>& necessary, aiNode* node);
void CollectAnimations(OutModel& model);
void BuildBoneCollisionInfo(OutModel& model);
void BuildAndSaveModel(OutModel& model);
void BuildAndSaveAnimations(OutModel& model);

void ExportScene(const String& outName);
void CollectSceneModels(OutScene& scene, aiNode* node);
void BuildAndSaveScene(OutScene& scene);

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
unsigned GetNumValidFaces(aiMesh* mesh);

void WriteShortIndices(unsigned short*& dest, aiMesh* mesh, unsigned index, unsigned offset);
void WriteLargeIndices(unsigned*& dest, aiMesh* mesh, unsigned index, unsigned offset);
void WriteVertex(float*& dest, aiMesh* mesh, unsigned index, unsigned elementMask, BoundingBox& box,
    const Matrix3x4& vertexTransform, const Matrix3& normalTransform, Vector<PODVector<unsigned char> >& blendIndices,
    Vector<PODVector<float> >& blendWeights);
unsigned GetElementMask(aiMesh* mesh);

aiNode* GetNode(const String& name, aiNode* rootNode, bool caseSensitive = true);
aiMatrix4x4 GetDerivedTransform(aiNode* node, aiNode* rootNode);
aiMatrix4x4 GetDerivedTransform(aiMatrix4x4 transform, aiNode* node, aiNode* rootNode);
aiMatrix4x4 GetMeshBakingTransform(aiNode* meshNode, aiNode* modelRootNode);
void GetPosRotScale(const aiMatrix4x4& transform, Vector3& pos, Quaternion& rot, Vector3& scale);

String FromAIString(const aiString& str);
Vector3 ToVector3(const aiVector3D& vec);
Vector2 ToVector2(const aiVector2D& vec);
Quaternion ToQuaternion(const aiQuaternion& quat);
Matrix3x4 ToMatrix3x4(const aiMatrix4x4& mat);
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
            "model Output a model and a material list\n"
            "scene Output a scene\n"
            "dump  Dump scene node structure. No output file is generated\n"
            "lod   Combine several Urho3D models as LOD levels of the output model\n"
            "      Syntax: lod <dist0> <mdl0> <dist1 <mdl1> ... <output file>\n"
            "\n"
            "Options:\n"
            "-b    Save scene in binary format, default format is XML\n"
            "-h    Generate hard instead of smooth normals if input file has no normals\n"
            "-i    Use local ID's for scene nodes\n"
            "-na   Do not output animations\n"
            "-nm   Do not output materials\n"
            "-ns   Do not create subdirectories for resources\n"
            "-nz   Do not create a zone and a directional light (scene mode only)\n"
            "-nf   Do not fix infacing normals\n"
            "-pX   Set path X for scene resources. Default is output file path\n"
            "-rX   Use scene node X as root node\n"
            "-fX   Animation tick frequency to use if unspecified. Default 4800\n"
            "-t    Generate tangents\n"
        );
    }
    
    RegisterSceneLibrary(context_);
    RegisterGraphicsLibrary(context_);
    RegisterPhysicsLibrary(context_);
    context_->RegisterSubsystem(new FileSystem(context_));
    context_->RegisterSubsystem(new ResourceCache(context_));
    context_->RegisterSubsystem(new WorkQueue(context_));
    
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
        if (arguments[i].Length() >= 2 && arguments[i][0] == '-')
        {
            String parameter;
            if (arguments[i].Length() >= 3)
                parameter = arguments[i].Substring(2);
            
            switch (tolower(arguments[i][1]))
            {
            case 'b':
                saveBinary_ = true;
                break;
                
            case 'h':
                flags &= ~aiProcess_GenSmoothNormals;
                flags |= aiProcess_GenNormals;
                break;
                
            case 'i':
                localIDs_ = true;
                break;
                
            case 'p':
                resourcePath_ = AddTrailingSlash(parameter);
                break;
                
            case 'r':
                rootNodeName = parameter;
                break;
                
            case 't':
                flags |= aiProcess_CalcTangentSpace;
                break;
                
            case 'f':
                defaultTicksPerSecond_ = ToFloat(parameter);
                break;
                
            case 'n':
                if (!parameter.Empty())
                {
                    switch (tolower(parameter[0]))
                    {
                    case 'a':
                        noAnimations_ = true;
                        break;
                        
                    case 'm':
                        noMaterials_ = true;
                        break;
                        
                    case 's':
                        useSubdirs_ = false;
                        break;
                        
                    case 'z':
                        createZone_ = false;
                        break;
                        
                    case 'f':
                        flags &= ~aiProcess_FixInfacingNormals;
                        break;
                    }
                }
                break;
            }
        }
    }
    
    if (command == "model" || command == "scene" || command == "dump")
    {
        String inFile = arguments[1];
        String outFile;
        if (arguments.Size() > 2 && arguments[2][0] != '-')
            outFile = GetInternalPath(arguments[2]);
        
        if (resourcePath_.Empty())
        {
            resourcePath_ = GetPath(outFile);
            // If output file already has the Models/ path (model mode), do not take it into the resource path
            if (command == "model")
            {
                String resPathLower = resourcePath_.ToLower();
                if (resPathLower.FindLast("models/") == resPathLower.Length() - 7)
                    resourcePath_ = resourcePath_.Substring(0, resourcePath_.Length() - 7);
            }
            if (resourcePath_.Empty())
                resourcePath_ = "./";
        }
        
        resourcePath_ = AddTrailingSlash(resourcePath_);
        
        if (command != "dump" && outFile.Empty())
            ErrorExit("No output file defined");
        
        PrintLine("Reading file " + inFile);
        scene_ = aiImportFile(GetNativePath(inFile).CString(), flags);
        if (!scene_)
            ErrorExit("Could not open or parse input file " + inFile);
        
        // In model mode, if scene has no animations, can flatten the hierarchy to combine submeshes with same material
        /// \todo It is slow to load scene twice just to know whether there are animations
        if (command == "model" && (!scene_->HasAnimations() || noAnimations_))
        {
            aiReleaseImport(scene_);
            flags |= aiProcess_OptimizeGraph | aiProcess_PreTransformVertices;
            scene_ = aiImportFile(GetNativePath(inFile).CString(), flags);
        }

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
            ExportModel(outFile);
        
        if (command == "scene")
            ExportScene(outFile);
        
        if (!noMaterials_)
        {
            HashSet<String> usedTextures;
            ExportMaterials(usedTextures);
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

void ExportModel(const String& outName)
{
    if (outName.Empty())
        ErrorExit("No output file defined");
    
    OutModel model;
    model.rootNode_ = rootNode_;
    model.outName_ = outName;
    
    CollectMeshes(model, model.rootNode_);
    CollectBones(model);
    BuildBoneCollisionInfo(model);
    BuildAndSaveModel(model);
    if (!noAnimations_)
    {
        CollectAnimations(model);
        BuildAndSaveAnimations(model);
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

void CollectBones(OutModel& model)
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
                if (!boneNode || boneNode == meshNode || boneNode == meshParentNode)
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

void CollectBonesFinal(PODVector<aiNode*>& dest, const HashSet<aiNode*>& necessary, aiNode* node)
{
    if (necessary.Find(node) != necessary.End())
    {
        dest.Push(node);
        for (unsigned i = 0; i < node->mNumChildren; ++i)
            CollectBonesFinal(dest, necessary, node->mChildren[i]);
    }
}

void CollectAnimations(OutModel& model)
{
    const aiScene* scene = scene_;
    for (unsigned i = 0; i < scene->mNumAnimations; ++i)
    {
        aiAnimation* anim = scene->mAnimations[i];
        bool modelBoneFound = false;
        for (unsigned j = 0; j < anim->mNumChannels; ++j)
        {
            aiNodeAnim* channel = anim->mChannels[j];
            String channelName = FromAIString(channel->mNodeName);
            if (GetBoneIndex(model, channelName) != M_MAX_UNSIGNED)
            {
                modelBoneFound = true;
                break;
            }
        }
        if (modelBoneFound)
            model.animations_.Push(anim);
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
        if (model.bones_.Size() > MAX_SKIN_MATRICES)
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
        if (model.bones_.Size() > MAX_SKIN_MATRICES)
            outModel->SetGeometryBoneMappings(allBoneMappings);
    }
    
    File outFile(context_);
    if (!outFile.Open(model.outName_, FILE_WRITE))
        ErrorExit("Could not open output file " + model.outName_);
    outModel->Save(outFile);
    
    // If exporting materials, also save material list for use by the editor
    if (!noMaterials_)
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

void BuildAndSaveAnimations(OutModel& model)
{
    for (unsigned i = 0; i < model.animations_.Size(); ++i)
    {
        aiAnimation* anim = model.animations_[i];
        String animName = FromAIString(anim->mName);
        if (animName.Empty())
            animName = "Anim" + String(i + 1);
        String animOutName = GetPath(model.outName_) + GetFileName(model.outName_) + "_" + SanitateAssetName(animName) + ".ani";
        
        SharedPtr<Animation> outAnim(new Animation(context_));
        float ticksPerSecond = (float)anim->mTicksPerSecond;
        // If ticks per second not specified, it's probably a .X file. In this case use the default tick rate
        if (ticksPerSecond < M_EPSILON)
            ticksPerSecond = defaultTicksPerSecond_;
        float tickConversion = 1.0f / ticksPerSecond;
        outAnim->SetAnimationName(animName);
        outAnim->SetLength((float)anim->mDuration * tickConversion);
        
        PrintLine("Writing animation " + animName + " length " + String(outAnim->GetLength()));
        Vector<AnimationTrack> tracks;
        for (unsigned j = 0; j < anim->mNumChannels; ++j)
        {
            aiNodeAnim* channel = anim->mChannels[j];
            String channelName = FromAIString(channel->mNodeName);
            unsigned boneIndex = GetBoneIndex(model, channelName);
            if (boneIndex == M_MAX_UNSIGNED)
            {
                PrintLine("Warning: skipping animation track " + channelName + " not found in model skeleton");
                continue;
            }
            
            aiNode* boneNode = model.bones_[boneIndex];
            
            AnimationTrack track;
            track.name_ = channelName;
            track.nameHash_ = channelName;
            
            // Check which channels are used
            track.channelMask_ = 0;
            if (channel->mNumPositionKeys > 1)
                track.channelMask_ |= CHANNEL_POSITION;
            if (channel->mNumRotationKeys > 1)
                track.channelMask_ |= CHANNEL_ROTATION;
            if (channel->mNumScalingKeys > 1)
                track.channelMask_ |= CHANNEL_SCALE;
            // Check for redundant identity scale in all keyframes and remove in that case
            if (track.channelMask_ & CHANNEL_SCALE)
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
                    track.channelMask_ &= ~CHANNEL_SCALE;
            }
            
            if (!track.channelMask_)
                PrintLine("Warning: skipping animation track " + channelName + " with no keyframes");
            
            // Currently only same amount of keyframes is supported
            // Note: should also check the times of individual keyframes for match
            if ((channel->mNumPositionKeys > 1 && channel->mNumRotationKeys > 1 && channel->mNumPositionKeys != channel->mNumRotationKeys) ||
                (channel->mNumPositionKeys > 1 && channel->mNumScalingKeys > 1 && channel->mNumPositionKeys != channel->mNumScalingKeys) ||
                (channel->mNumRotationKeys > 1 && channel->mNumScalingKeys > 1 && channel->mNumRotationKeys != channel->mNumScalingKeys))
            {
                PrintLine("Warning: differing amounts of channel keyframes, skipping animation track " + channelName);
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
                
                // Get time for the keyframe
                if (track.channelMask_ & CHANNEL_POSITION && k < channel->mNumPositionKeys)
                    kf.time_ = (float)channel->mPositionKeys[k].mTime * tickConversion;
                else if (track.channelMask_ & CHANNEL_ROTATION && k < channel->mNumRotationKeys)
                    kf.time_ = (float)channel->mRotationKeys[k].mTime * tickConversion;
                else if (track.channelMask_ & CHANNEL_SCALE && k < channel->mNumScalingKeys)
                    kf.time_ = (float)channel->mScalingKeys[k].mTime * tickConversion;
                
                // Start with the bone's base transform
                aiMatrix4x4 boneTransform = boneNode->mTransformation;
                aiVector3D pos, scale;
                aiQuaternion rot;
                boneTransform.Decompose(scale, rot, pos);
                // Then apply the active channels
                if (track.channelMask_ & CHANNEL_POSITION && k < channel->mNumPositionKeys)
                    pos = channel->mPositionKeys[k].mValue;
                if (track.channelMask_ & CHANNEL_ROTATION && k < channel->mNumRotationKeys)
                    rot = channel->mRotationKeys[k].mValue;
                if (track.channelMask_ & CHANNEL_SCALE && k < channel->mNumScalingKeys)
                    scale = channel->mScalingKeys[k].mValue;
                
                // If root bone, transform with the model root node transform
                if (!boneIndex)
                {
                    aiMatrix4x4 transMat, scaleMat, rotMat;
                    aiMatrix4x4::Translation(pos, transMat);
                    aiMatrix4x4::Scaling(scale, scaleMat);
                    rotMat = aiMatrix4x4(rot.GetMatrix());
                    aiMatrix4x4 tform = transMat * rotMat * scaleMat;
                    tform = GetDerivedTransform(tform, boneNode, model.rootNode_);
                    tform.Decompose(scale, rot, pos);
                }
                
                if (track.channelMask_ & CHANNEL_POSITION)
                    kf.position_ = ToVector3(pos);
                if (track.channelMask_ & CHANNEL_ROTATION)
                    kf.rotation_ = ToQuaternion(rot);
                if (track.channelMask_ & CHANNEL_SCALE)
                    kf.scale_ = ToVector3(scale);
                
                track.keyFrames_.Push(kf);
            }
            
            tracks.Push(track);
        }
        
        outAnim->SetTracks(tracks);
        
        File outFile(context_);
        if (!outFile.Open(animOutName, FILE_WRITE))
            ErrorExit("Could not open output file " + animOutName);
        outAnim->Save(outFile);
    }
}

void ExportScene(const String& outName)
{
    OutScene outScene;
    outScene.outName_ = outName;
    outScene.rootNode_ = rootNode_;
    
    if (useSubdirs_)
        context_->GetSubsystem<FileSystem>()->CreateDir(resourcePath_ + "Models");
    
    CollectSceneModels(outScene, rootNode_);
    
    // Save models and their material lists
    for (unsigned i = 0; i < outScene.models_.Size(); ++i)
        BuildAndSaveModel(outScene.models_[i]);
    
    // Save scene
    BuildAndSaveScene(outScene);
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
        if (unique)
        {
            PrintLine("Added model " + model.outName_);
            PrintLine("Added node " + FromAIString(node->mName));
            CollectBones(model);
            BuildBoneCollisionInfo(model);
            if (!noAnimations_)
            {
                CollectAnimations(model);
                BuildAndSaveAnimations(model);
            }
            
            scene.models_.Push(model);
            scene.nodes_.Push(node);
            scene.nodeModelIndices_.Push(scene.models_.Size() - 1);
        }
    }
    
    for (unsigned i = 0; i < node->mNumChildren; ++i)
        CollectSceneModels(scene, node->mChildren[i]);
}

void BuildAndSaveScene(OutScene& scene)
{
    PrintLine("Writing scene");
    
    SharedPtr<Scene> outScene(new Scene(context_));
    
    /// \todo Make the physics properties configurable
    outScene->CreateComponent<PhysicsWorld>();
    
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
    
    ResourceCache* cache = context_->GetSubsystem<ResourceCache>();
    
    // Create geometry nodes
    for (unsigned i = 0; i < scene.nodes_.Size(); ++i)
    {
        const OutModel& model = scene.models_[scene.nodeModelIndices_[i]];
        
        Node* modelNode = outScene->CreateChild(FromAIString(scene.nodes_[i]->mName), localIDs_ ? LOCAL : REPLICATED);
        StaticModel* staticModel = modelNode->CreateComponent<StaticModel>();
        
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
        
        // Set a flattened transform
        Vector3 pos, scale;
        Quaternion rot;
        GetPosRotScale(GetDerivedTransform(scene.nodes_[i], rootNode_), pos, rot, scale);
        modelNode->SetTransform(pos, rot, scale);
        // Set materials if they are known
        for (unsigned j = 0; j < model.meshes_.Size(); ++j)
        {
            String matName = GetMeshMaterialName(model.meshes_[j]);
            if (!matName.Empty())
            {
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
    }
    
    // Create lights
    for (unsigned i = 0; i < scene_->mNumLights; ++i)
    {
        aiLight* light = scene_->mLights[i];
        aiNode* lightNode = GetNode(FromAIString(light->mName), rootNode_, true);
        if (!lightNode)
            continue;
        Matrix3x4 lightNodeTransform = ToMatrix3x4(GetDerivedTransform(lightNode, rootNode_));
        Vector3 lightWorldPosition = lightNodeTransform * ToVector3(light->mPosition);
        Vector3 lightWorldDirection = lightNodeTransform.RotationMatrix() * ToVector3(light->mDirection);
        
        Node* outNode = outScene->CreateChild(FromAIString(light->mName));
        Light* outLight = outNode->CreateComponent<Light>();
        outLight->SetColor(Color(light->mColorDiffuse.r, light->mColorDiffuse.g, light->mColorDiffuse.b));
        
        switch (light->mType)
        {
        case aiLightSource_DIRECTIONAL:
            outNode->SetDirection(lightWorldDirection);
            outLight->SetLightType(LIGHT_DIRECTIONAL);
            break;
        case aiLightSource_SPOT:
            outNode->SetPosition(lightWorldPosition);
            outNode->SetDirection(lightWorldDirection);
            outLight->SetLightType(LIGHT_SPOT);
            outLight->SetFov(light->mAngleOuterCone * M_RADTODEG);
            break;
        case aiLightSource_POINT:
            outNode->SetPosition(lightWorldPosition);
            outLight->SetLightType(LIGHT_POINT);
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
    
    File file(context_);
    if (!file.Open(scene.outName_, FILE_WRITE))
        ErrorExit("Could not open output file " + scene.outName_);
    if (!saveBinary_)
        outScene->SaveXML(file);
    else
        outScene->Save(file);
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
    // Material must have name so it can be successfully saved
    aiString matNameStr;
    material->Get(AI_MATKEY_NAME, matNameStr);
    String matName = SanitateAssetName(FromAIString(matNameStr));
    if (matName.Empty())
        return;
    
    PrintLine("Writing material " + matName);
    
    // Do not actually create a material instance, but instead craft an xml file manually
    XMLFile outMaterial(context_);
    XMLElement materialElem = outMaterial.CreateRoot("material");
    
    String diffuseTexName;
    String normalTexName;
    String specularTexName;
    String lightmapTexName;
    Color diffuseColor;
    Color specularColor;
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
        specularTexName = GetFileNameAndExtension(FromAIString(stringVal));
    if (material->Get(AI_MATKEY_COLOR_DIFFUSE, colorVal) == AI_SUCCESS)
        diffuseColor = Color(colorVal.r, colorVal.g, colorVal.b);
    if (material->Get(AI_MATKEY_COLOR_SPECULAR, colorVal) == AI_SUCCESS)
        specularColor = Color(colorVal.r, colorVal.g, colorVal.b);
    if (material->Get(AI_MATKEY_OPACITY, floatVal) == AI_SUCCESS)
    {
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
    }
    if (hasAlpha)
        techniqueName += "Alpha";
    
    XMLElement techniqueElem = materialElem.CreateChild("technique");
    techniqueElem.SetString("name", techniqueName + ".xml");
    
    if (!diffuseTexName.Empty())
    {
        XMLElement diffuseElem = materialElem.CreateChild("texture");
        diffuseElem.SetString("unit", "diffuse");
        diffuseElem.SetString("name", (useSubdirs_ ? "Textures/" : "") + diffuseTexName);
        usedTextures.Insert(diffuseTexName);
    }
    if (!normalTexName.Empty())
    {
        XMLElement normalElem = materialElem.CreateChild("texture");
        normalElem.SetString("unit", "normal");
        normalElem.SetString("name", (useSubdirs_ ? "Textures/" : "") + normalTexName);
        usedTextures.Insert(normalTexName);
    }
    if (!specularTexName.Empty())
    {
        XMLElement normalElem = materialElem.CreateChild("texture");
        normalElem.SetString("unit", "specular");
        normalElem.SetString("name", (useSubdirs_ ? "Textures/" : "") + specularTexName);
        usedTextures.Insert(specularTexName);
    }
    if (!lightmapTexName.Empty())
    {
        XMLElement normalElem = materialElem.CreateChild("texture");
        normalElem.SetString("unit", "emissive");
        normalElem.SetString("name", (useSubdirs_ ? "Textures/" : "") + lightmapTexName);
        usedTextures.Insert(lightmapTexName);
    }
    
    XMLElement diffuseColorElem = materialElem.CreateChild("parameter");
    diffuseColorElem.SetString("name", "MatDiffColor");
    diffuseColorElem.SetColor("value", diffuseColor);
    XMLElement specularElem = materialElem.CreateChild("parameter");
    specularElem.SetString("name", "MatSpecColor");
    specularElem.SetVector4("value", Vector4(specularColor.r_, specularColor.g_, specularColor.b_, specPower));
    
    if (twoSided)
    {
        XMLElement cullElem = materialElem.CreateChild("cull");
        XMLElement shadowCullElem = materialElem.CreateChild("shadowcull");
        cullElem.SetString("value", "none");
        shadowCullElem.SetString("value", "none");
    }
    
    File outFile(context_);
    String outFileName = resourcePath_ + (useSubdirs_ ? "Materials/" : "" ) + matName + ".xml";
    if (!outFile.Open(outFileName, FILE_WRITE))
        ErrorExit("Could not open output file " + outFileName);
    outMaterial.Save(outFile);
}

void CopyTextures(const HashSet<String>& usedTextures, const String& sourcePath)
{
    if (useSubdirs_)
        context_->GetSubsystem<FileSystem>()->CreateDir(resourcePath_ + "Textures");
    
    for (HashSet<String>::ConstIterator i = usedTextures.Begin(); i != usedTextures.End(); ++i)
    {
        PrintLine("Copying texture " + (*i));
        context_->GetSubsystem<FileSystem>()->Copy(sourcePath + *i, resourcePath_ + (useSubdirs_ ? "Textures/" : "") + *i);
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
    if (model.bones_.Size() > MAX_SKIN_MATRICES)
    {
        if (mesh->mNumBones > MAX_SKIN_MATRICES)
            ErrorExit("Geometry has too many bone influences");
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
                if (blendWeights[vertex].Size() > 4)
                    ErrorExit("More than 4 bone influences on vertex");
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
                if (blendWeights[vertex].Size() > 4)
                    ErrorExit("More than 4 bone influences on vertex");
            }
        }
    }
}

String GetMeshMaterialName(aiMesh* mesh)
{
    aiMaterial* material = scene_->mMaterials[mesh->mMaterialIndex];
    aiString matNameStr;
    material->Get(AI_MATKEY_NAME, matNameStr);
    String matName = SanitateAssetName(FromAIString(matNameStr));
    if (matName.Empty())
        return matName;
    else
        return (useSubdirs_ ? "Materials/" : "") + matName + ".xml";
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

aiMatrix4x4 GetDerivedTransform(aiNode* node, aiNode* rootNode)
{
    return GetDerivedTransform(node->mTransformation, node, rootNode);
}

aiMatrix4x4 GetDerivedTransform(aiMatrix4x4 transform, aiNode* node, aiNode* rootNode)
{
    // If basenode is defined, go only up to it in the parent chain
    while (node && node != rootNode)
    {
        node = node->mParent;
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
