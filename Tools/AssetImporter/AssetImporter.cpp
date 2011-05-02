//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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
#include "Quaternion.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "StaticModel.h"
#include "StringUtils.h"
#include "Vector3.h"
#include "VertexBuffer.h"
#include "XMLFile.h"
#include "Zone.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <set>

#include <assimp.hpp>
#include <aiScene.h>
#include <aiPostProcess.h>

#include "DebugNew.h"

enum Command
{
    CMD_NONE = 0,
    CMD_MODEL,
    CMD_SCENE,
    CMD_DUMP,
    CMD_LOD
};

struct OutModel
{
    OutModel() :
        totalVertices_(0),
        totalIndices_(0),
        rootBone_(0)
    {
    }
    
    std::string outName_;
    aiNode* rootNode_;
    std::set<unsigned> meshIndices_;
    std::vector<aiMesh*> meshes_;
    std::vector<aiNode*> meshNodes_;
    std::vector<aiNode*> bones_;
    std::vector<aiAnimation*> animations_;
    std::vector<float> boneRadii_;
    std::vector<BoundingBox> boneHitboxes_;
    aiNode* rootBone_;
    unsigned totalVertices_;
    unsigned totalIndices_;
};

struct OutScene
{
    std::string outName_;
    aiNode* rootNode_;
    std::vector<OutModel> models_;
    std::vector<aiNode*> nodes_;
    std::vector<unsigned> nodeModelIndices_;
};

SharedPtr<Context> context_(new Context());
SharedPtr<FileSystem> fileSystem_(new FileSystem(context_));
Command command_ = CMD_NONE;
const aiScene* scene_ = 0;
aiNode* rootNode_ = 0;
std::string materialListName_;
std::string resourcePath_;
bool useSubdirs_ = true;
bool localIDs_ = false;
bool saveBinary_ = false;
bool createZone_ = true;
bool noAnimations_ = false;

int main(int argc, char** argv);
void Run(const std::vector<std::string>& arguments);
void DumpNodes(aiNode* rootNode, unsigned level);

void ExportModel(const std::string& outName);
void CollectMeshes(OutModel& model, aiNode* node);
void CollectBones(OutModel& model);
void CollectBonesFinal(std::vector<aiNode*>& dest, const std::set<aiNode*>& necessary, aiNode* node);
void CollectAnimations(OutModel& model);
void BuildBoneCollisionInfo(OutModel& model);
void BuildAndSaveModel(OutModel& model);
void BuildAndSaveAnimations(OutModel& model);

void ExportScene(const std::string& outName);
void CollectSceneModels(OutScene& scene, aiNode* node);
void BuildAndSaveScene(OutScene& scene);

void ExportMaterials(std::set<std::string>& usedTextures);
void BuildAndSaveMaterial(aiMaterial* material, std::set<std::string>& usedTextures);
void CopyTextures(const std::set<std::string>& usedTextures, const std::string& sourcePath);

void CombineLods(const std::vector<float>& lodDistances, const std::vector<std::string>& modelNames, const std::string& outName);

void GetMeshesUnderNode(std::vector<std::pair<aiNode*, aiMesh*> >& meshes, aiNode* node);
unsigned GetMeshIndex(aiMesh* mesh);
unsigned GetBoneIndex(OutModel& model, const std::string& boneName);
aiBone* GetMeshBone(OutModel& model, const std::string& boneName);
Matrix4x3 GetOffsetMatrix(OutModel& model, const std::string& boneName);
void GetBlendData(OutModel& model, aiMesh* mesh, std::vector<unsigned>& boneMappings, std::vector<std::vector<unsigned char> >&
    blendIndices, std::vector<std::vector<float> >& blendWeights);
std::string GetMeshMaterialName(aiMesh* mesh);

void WriteShortIndices(unsigned short*& dest, aiMesh* mesh, unsigned index, unsigned offset);
void WriteLargeIndices(unsigned*& dest, aiMesh* mesh, unsigned index, unsigned offset);
void WriteVertex(float*& dest, aiMesh* mesh, unsigned index, unsigned elementMask, BoundingBox& box,
    const Matrix4x3& vertexTransform, const Matrix3& normalTransform, std::vector<std::vector<unsigned char> >& blendIndices,
    std::vector<std::vector<float> >& blendWeights);
unsigned GetElementMask(aiMesh* mesh);

aiNode* FindNode(const std::string& name, aiNode* rootNode, bool caseSensitive = true);
aiMatrix4x4 GetDerivedTransform(aiNode* node, aiNode* rootNode);
aiMatrix4x4 GetDerivedTransform(aiMatrix4x4 transform, aiNode* node, aiNode* rootNode);
aiMatrix4x4 GetMeshBakingTransform(aiNode* meshNode, aiNode* modelRootNode);
void GetPosRotScale(const aiMatrix4x4& transform, Vector3& pos, Quaternion& rot, Vector3& scale);

std::string ToStdString(const aiString& str);
Vector3 ToVector3(const aiVector3D& vec);
Vector2 ToVector2(const aiVector2D& vec);
Quaternion ToQuaternion(const aiQuaternion& quat);
std::string SanitateAssetName(const std::string& name);

void ErrorExit(const std::string& error);

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;
    
    for (int i = 1; i < argc; ++i)
        arguments.push_back(argv[i]);
    
    Run(arguments);
    return 0;
}

void Run(const std::vector<std::string>& arguments)
{
    if (arguments.size() < 2)
    {
        ErrorExit(
            "Usage: AssetImporter <command> <input file> <output file> [options]\n"
            "See http://assimp.sourceforge.net/main_features_formats.html for input formats\n\n"
            "Commands:\n"
            "model Export a model\n"
            "scene Export a scene\n"
            "dump  Dump scene node structure. No output file is generated\n"
            "lod   Combine several Urho3D models as LOD levels of the output model\n"
            "      Syntax: lod <dist0> <mdl0> <dist1 <mdl1> ... <output file>\n"
            "\n"
            "Options:\n"
            "-b    Save scene in binary format, default format is XML\n"
            "-i    Use local ID's for scene entities\n"
            "-mX   Output a material list file X (model mode only)\n"
            "-na   Do not export animations\n"
            "-nm   Do not export materials\n"
            "-ns   Do not create subdirectories for resources\n"
            "-nz   Do not create a zone and a directional light (scene mode only)\n"
            "-pX   Set path X for scene resources. Default is output file path\n"
            "-rX   Use scene node X as root node\n"
            "-t    Generate tangents to model(s)\n"
        );
    }
    
    RegisterSceneLibrary(context_);
    RegisterGraphicsLibrary(context_);
    RegisterPhysicsLibrary(context_);
    context_->RegisterSubsystem(new FileSystem(context_));
    context_->RegisterSubsystem(new ResourceCache(context_));
    
    std::string command = ToLower(arguments[0]);
    std::string rootNodeName;
    
    bool noMaterials = false;
    
    unsigned flags = 
        aiProcess_ConvertToLeftHanded |
        aiProcess_JoinIdenticalVertices |
        aiProcess_Triangulate |
        aiProcess_GenSmoothNormals |
        aiProcess_LimitBoneWeights |
        aiProcess_ImproveCacheLocality |
        aiProcess_FixInfacingNormals |
        aiProcess_FindInvalidData |
        aiProcess_FindInstances |
        aiProcess_OptimizeMeshes;
    
    for (unsigned i = 2; i < arguments.size(); ++i)
    {
        if ((arguments[i].length() >= 2) && (arguments[i][0] == '-'))
        {
            std::string parameter;
            if (arguments[i].length() >= 3)
                parameter = arguments[i].substr(2);
            
            switch (tolower(arguments[i][1]))
            {
            case 'b':
                saveBinary_ = true;
                break;
                
            case 'i':
                localIDs_ = true;
                break;
                
            case 'm':
                materialListName_ = Replace(parameter, '\\', '/');
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
                
            case 'n':
                if (!parameter.empty())
                {
                    switch (tolower(parameter[0]))
                    {
                    case 'a':
                        noAnimations_ = true;
                        break;
                        
                    case 'm':
                        noMaterials = true;
                        break;
                        
                    case 's':
                        useSubdirs_ = false;
                        break;
                        
                    case 'z':
                        createZone_ = false;
                        break;
                    }
                }
                break;
            }
        }
    }
    
    if (command == "model")
        command_ = CMD_MODEL;
    else if (command == "scene")
        command_ = CMD_SCENE;
    else if (command == "dump")
        command_ = CMD_DUMP;
    else if (command == "lod")
        command_ = CMD_LOD;
    else
        ErrorExit("Unrecognized command " + command);
        
    if (command_ != CMD_LOD)
    {
        std::string inFile = arguments[1];
        std::string outFile;
        if ((arguments.size() > 2) && (arguments[2][0] != '-'))
            outFile = Replace(arguments[2], '\\', '/');
        
        if (resourcePath_.empty())
        {
            resourcePath_ = GetPath(outFile);
            // If output file already has the Models/ path (model mode), do not take it into the resource path
            if (command_ == CMD_MODEL)
            {
                std::string resPathLower = ToLower(resourcePath_);
                if (resPathLower.rfind("models/") == resPathLower.length() - 7)
                    resourcePath_ = resourcePath_.substr(0, resourcePath_.length() - 7);
            }
            if (resourcePath_.empty())
                resourcePath_ = "./";
        }
        
        resourcePath_ = AddTrailingSlash(resourcePath_);
        
        Assimp::Importer importer;
        std::cout << "Reading file " << inFile << std::endl;
        scene_ = importer.ReadFile(GetNativePath(inFile).c_str(), flags);
        if (!scene_)
            ErrorExit("Could not open or parse input file " + inFile);
        
        rootNode_ = scene_->mRootNode;
        if (!rootNodeName.empty())
        {
            rootNode_ = FindNode(rootNodeName, rootNode_, false);
            if (!rootNode_)
                ErrorExit("Could not find scene node " + rootNodeName);
        }
        
        switch (command_)
        {
        case CMD_DUMP:
            DumpNodes(rootNode_, 0);
            return;
        
        case CMD_MODEL:
            ExportModel(outFile);
            break;
            
        case CMD_SCENE:
            ExportScene(outFile);
            break;
        }
        
        if (!noMaterials)
        {
            std::set<std::string> usedTextures;
            ExportMaterials(usedTextures);
            CopyTextures(usedTextures, GetPath(inFile));
        }
    }
    else
    {
        std::vector<float> lodDistances;
        std::vector<std::string> modelNames;
        std::string outFile;
        
        unsigned numLodArguments = 0;
        for (unsigned i = 1; i < arguments.size(); ++i)
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
                outFile = Replace(arguments[i], '\\', '/');
            else
            {
                if (i & 1)
                    lodDistances.push_back(Max(ToFloat(arguments[i]), 0.0f));
                else
                    modelNames.push_back(Replace(arguments[i], '\\', '/'));
            }
        }
        
        if (lodDistances[0] != 0.0f)
        {
            std::cout << "Warning: first LOD distance forced to 0" << std::endl;
            lodDistances[0] = 0.0f;
        }
        
        CombineLods(lodDistances, modelNames, outFile);
    }
}

void DumpNodes(aiNode* rootNode, unsigned level)
{
    if (!rootNode)
        return;
    
    std::string indent;
    indent.resize(level * 2);
    for (unsigned i = 0; i < level * 2; ++i)
        indent[i] = ' ';
    
    Vector3 pos, scale;
    Quaternion rot;
    aiMatrix4x4 transform = GetDerivedTransform(rootNode, rootNode_);
    GetPosRotScale(transform, pos, rot, scale);
    
    std::cout << indent << "Node " << ToStdString(rootNode->mName) << " pos " << ToString(pos) << std::endl;
    
    if (rootNode->mNumMeshes == 1)
        std::cout << indent << "  " << rootNode->mNumMeshes << " geometry" << std::endl;
    if (rootNode->mNumMeshes > 1)
        std::cout << indent << "  " << rootNode->mNumMeshes << " geometries" << std::endl;
    
    for (unsigned i = 0; i < rootNode->mNumChildren; ++i)
        DumpNodes(rootNode->mChildren[i], level + 1);
}

void ExportModel(const std::string& outName)
{
    if (outName.empty())
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
    
    // Write material references if requested
    if (!materialListName_.empty())
    {
        File listFile(context_);
        if (listFile.Open(materialListName_, FILE_WRITE))
        {
            for (unsigned i = 0; i < model.meshes_.size(); ++i)
                listFile.WriteLine(GetMeshMaterialName(model.meshes_[i]));
        }
        else
            std::cout << "Warning: could not write material list file " + materialListName_ << std::endl;
    }
}

void CollectMeshes(OutModel& model, aiNode* node)
{
    for (unsigned i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene_->mMeshes[node->mMeshes[i]];
        for (unsigned j = 0; j < model.meshes_.size(); ++j)
        {
            if (mesh == model.meshes_[j])
            {
                std::cout << "Warning: same mesh found multiple times" << std::endl;
                break;
            }
        }
        
        model.meshIndices_.insert(node->mMeshes[i]);
        model.meshes_.push_back(mesh);
        model.meshNodes_.push_back(node);
        model.totalVertices_ += mesh->mNumVertices;
        model.totalIndices_ += mesh->mNumFaces * 3;
    }
    
    for (unsigned i = 0; i < node->mNumChildren; ++i)
        CollectMeshes(model, node->mChildren[i]);
}

void CollectBones(OutModel& model)
{
    std::set<aiNode*> necessary;
    std::set<aiNode*> rootNodes;
    
    for (unsigned i = 0; i < model.meshes_.size(); ++i)
    {
        aiMesh* mesh = model.meshes_[i];
        aiNode* meshNode = model.meshNodes_[i];
        aiNode* meshParentNode = meshNode->mParent;
        aiNode* rootNode = 0;
        
        for (unsigned j = 0; j < mesh->mNumBones; ++j)
        {
            aiBone* bone = mesh->mBones[j];
            std::string boneName(ToStdString(bone->mName));
            aiNode* boneNode = FindNode(boneName, scene_->mRootNode, true);
            if (!boneNode)
                ErrorExit("Could not find scene node for bone " + boneName);
            necessary.insert(boneNode);
            rootNode = boneNode;
            
            for (;;)
            {
                boneNode = boneNode->mParent;
                if ((!boneNode) || (boneNode == meshNode) || (boneNode == meshParentNode))
                    break;
                rootNode = boneNode;
                necessary.insert(boneNode);
            }
            
            if (rootNodes.find(rootNode) == rootNodes.end())
                rootNodes.insert(rootNode);
        }
    }
    
    // If we find multiple root nodes, try to remedy by using their parent instead
    if (rootNodes.size() > 1)
    {
        aiNode* commonParent = (*rootNodes.begin())->mParent;
        for (std::set<aiNode*>::iterator i = rootNodes.begin(); i != rootNodes.end(); ++i)
        {
            if ((*i) != commonParent)
            {
                if ((!commonParent) || ((*i)->mParent != commonParent))
                    ErrorExit("Skeleton with multiple root nodes found, not supported");
            }
        }
        rootNodes.clear();
        rootNodes.insert(commonParent);
        necessary.insert(commonParent);
    }
    
    if (rootNodes.empty())
        return;
    
    model.rootBone_ = *rootNodes.begin();
    CollectBonesFinal(model.bones_, necessary, model.rootBone_);
    // Initialize the bone collision info
    model.boneRadii_.resize(model.bones_.size());
    model.boneHitboxes_.resize(model.bones_.size());
    for (unsigned i = 0; i < model.bones_.size(); ++i)
    {
        model.boneRadii_[i] = 0.0f;
        model.boneHitboxes_[i] = BoundingBox(0.0f, 0.0f);
    }
}

void CollectBonesFinal(std::vector<aiNode*>& dest, const std::set<aiNode*>& necessary, aiNode* node)
{
    if (necessary.find(node) != necessary.end())
    {
        dest.push_back(node);
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
            std::string channelName = ToStdString(channel->mNodeName);
            if (GetBoneIndex(model, channelName) != M_MAX_UNSIGNED)
            {
                modelBoneFound = true;
                break;
            }
        }
        if (modelBoneFound)
            model.animations_.push_back(anim);
    }
    
    /// \todo Vertex morphs are ignored for now
}

void BuildBoneCollisionInfo(OutModel& model)
{
    for (unsigned i = 0; i < model.meshes_.size(); ++i)
    {
        aiMesh* mesh = model.meshes_[i];
        for (unsigned j = 0; j < mesh->mNumBones; ++j)
        {
            aiBone* bone = mesh->mBones[j];
            std::string boneName = ToStdString(bone->mName);
            unsigned boneIndex = GetBoneIndex(model, boneName);
            if (boneIndex == M_MAX_UNSIGNED)
                continue;
            aiNode* boneNode = model.bones_[boneIndex];
            for (unsigned k = 0; k < bone->mNumWeights; ++k)
            {
                float weight = bone->mWeights[k].mWeight;
                if (weight > 0.33f)
                {
                    aiVector3D vertexBoneSpace = bone->mOffsetMatrix * mesh->mVertices[bone->mWeights[k].mVertexId];
                    Vector3 vertex = ToVector3(vertexBoneSpace);
                    float radius = vertex.GetLength();
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
    std::string rootNodeName = ToStdString(model.rootNode_->mName);
    if (!model.meshes_.size())
        ErrorExit("No geometries found starting from node " + rootNodeName);
    
    std::cout << "Writing model " << rootNodeName << std::endl;
    
    SharedPtr<Model> outModel(new Model(context_));
    outModel->SetNumGeometries(model.meshes_.size());
    std::vector<std::vector<unsigned> > allBoneMappings;
    BoundingBox box;
    
    bool combineBuffers = true;
    // Check if buffers can be combined (same vertex element mask, under 65535 vertices)
    unsigned elementMask = GetElementMask(model.meshes_[0]);
    for (unsigned i = 1; i < model.meshes_.size(); ++i)
    {
        if (GetElementMask(model.meshes_[i]) != elementMask)
        {
            combineBuffers = false;
            break;
        }
    }
    // Check if keeping separate buffers allows to avoid 32-bit indices
    if ((combineBuffers) && (model.totalVertices_ > 65535))
    {
        bool allUnder65k = true;
        for (unsigned i = 0; i < model.meshes_.size(); ++i)
        {
            if (model.meshes_[i]->mNumVertices > 65535)
                allUnder65k = false;
        }
        if (allUnder65k == true)
            combineBuffers = false;
    }
    
    if (!combineBuffers)
    {
        std::cout << "Writing separate buffers" << std::endl;
        for (unsigned i = 0; i < model.meshes_.size(); ++i)
        {
            // Get the world transform of the mesh for baking into the vertices
            Matrix4x3 vertexTransform;
            Matrix3 normalTransform;
            Vector3 pos, scale;
            Quaternion rot;
            GetPosRotScale(GetMeshBakingTransform(model.meshNodes_[i], model.rootNode_), pos, rot, scale);
            vertexTransform = Matrix4x3(pos, rot, scale);
            normalTransform = rot.GetRotationMatrix();
            
            SharedPtr<IndexBuffer> ib(new IndexBuffer(context_));
            SharedPtr<VertexBuffer> vb(new VertexBuffer(context_));
            SharedPtr<Geometry> geom(new Geometry(context_));
            
            aiMesh* mesh = model.meshes_[i];
            std::cout << "Writing geometry " << i << " with " << mesh->mNumVertices << " vertices " << mesh->mNumFaces * 3 
                << " indices" << std::endl;
            
            bool largeIndices = mesh->mNumVertices > 65535;
            unsigned elementMask = GetElementMask(mesh);
            
            ib->SetSize(mesh->mNumFaces * 3, largeIndices);
            vb->SetSize(mesh->mNumVertices, elementMask);
            
            // Build the index data
            void* indexData = ib->Lock(0, ib->GetIndexCount(), LOCK_NORMAL);
            if (!largeIndices)
            {
                unsigned short* dest = (unsigned short*)indexData;
                for (unsigned j = 0; j < mesh->mNumFaces; ++j)
                    WriteShortIndices(dest, mesh, j, 0);
            }
            else
            {
                unsigned* dest = (unsigned*)indexData;
                for (unsigned j = 0; j < mesh->mNumFaces; ++j)
                    WriteLargeIndices(dest, mesh, j, 0);
            }
            
            // Build the vertex data
            // If there are bones, get blend data
            std::vector<std::vector<unsigned char> > blendIndices;
            std::vector<std::vector<float> > blendWeights;
            std::vector<unsigned> boneMappings;
            if (model.bones_.size())
                GetBlendData(model, mesh, boneMappings, blendIndices, blendWeights);
            
            void* vertexData = vb->Lock(0, vb->GetVertexCount(), LOCK_NORMAL);
            float* dest = (float*)vertexData;
            for (unsigned j = 0; j < mesh->mNumVertices; ++j)
                WriteVertex(dest, mesh, j, elementMask, box, vertexTransform, normalTransform, blendIndices, blendWeights);
            
            ib->Unlock();
            vb->Unlock();
            
            // Define the geometry
            geom->SetIndexBuffer(ib);
            geom->SetVertexBuffer(0, vb);
            geom->SetDrawRange(TRIANGLE_LIST, 0, mesh->mNumFaces * 3, true);
            outModel->SetNumGeometryLodLevels(i, 1);
            outModel->SetGeometry(i, 0, geom);
            if (model.bones_.size() > MAX_SKIN_MATRICES)
                allBoneMappings.push_back(boneMappings);
        }
    }
    else
    {
        SharedPtr<IndexBuffer> ib(new IndexBuffer(context_));
        SharedPtr<VertexBuffer> vb(new VertexBuffer(context_));
        
        bool largeIndices = model.totalIndices_ > 65535;
        ib->SetSize(model.totalIndices_, largeIndices);
        vb->SetSize(model.totalVertices_, elementMask);
        
        unsigned startVertexOffset = 0;
        unsigned startIndexOffset = 0;
        void* indexData = ib->Lock(0, ib->GetIndexCount(), LOCK_NORMAL);
        void* vertexData = vb->Lock(0, vb->GetVertexCount(), LOCK_NORMAL);
        // The buffer is in CPU memory, and therefore locking is irrelevant. Unlock so that draw range checking can lock again
        ib->Unlock();
        vb->Unlock();
        
        for (unsigned i = 0; i < model.meshes_.size(); ++i)
        {
            // Get the world transform of the mesh for baking into the vertices
            Matrix4x3 vertexTransform;
            Matrix3 normalTransform;
            Vector3 pos, scale;
            Quaternion rot;
            GetPosRotScale(GetMeshBakingTransform(model.meshNodes_[i], model.rootNode_), pos, rot, scale);
            vertexTransform = Matrix4x3(pos, rot, scale);
            normalTransform = rot.GetRotationMatrix();
            
            SharedPtr<Geometry> geom(new Geometry(context_));
            
            aiMesh* mesh = model.meshes_[i];
            std::cout << "Writing geometry " << i << " with " << mesh->mNumVertices << " vertices " << mesh->mNumFaces * 3 
                << " indices" << std::endl;
            
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
            std::vector<std::vector<unsigned char> > blendIndices;
            std::vector<std::vector<float> > blendWeights;
            std::vector<unsigned> boneMappings;
            if (model.bones_.size())
                GetBlendData(model, mesh, boneMappings, blendIndices, blendWeights);
            
            float* dest = (float*)((unsigned char*)vertexData + startVertexOffset * vb->GetVertexSize());
            for (unsigned j = 0; j < mesh->mNumVertices; ++j)
                WriteVertex(dest, mesh, j, elementMask, box, vertexTransform, normalTransform, blendIndices, blendWeights);
            
            // Define the geometry
            geom->SetIndexBuffer(ib);
            geom->SetVertexBuffer(0, vb);
            geom->SetDrawRange(TRIANGLE_LIST, startIndexOffset, mesh->mNumFaces * 3, true);
            outModel->SetNumGeometryLodLevels(i, 1);
            outModel->SetGeometry(i, 0, geom);
            if (model.bones_.size() > MAX_SKIN_MATRICES)
                allBoneMappings.push_back(boneMappings);
            
            startVertexOffset += mesh->mNumVertices;
            startIndexOffset += mesh->mNumFaces * 3;
        }
    }
    
    outModel->SetBoundingBox(box);
    
    // Build skeleton if necessary
    if ((model.bones_.size()) && (model.rootBone_))
    {
        std::cout << "Writing skeleton with " << model.bones_.size() << " bones, rootbone " +
            ToStdString(model.rootBone_->mName) << std::endl;
        
        Skeleton skeleton;
        std::vector<Bone>& bones = skeleton.GetModifiableBones();
        
        for (unsigned i = 0; i < model.bones_.size(); ++i)
        {
            aiNode* boneNode = model.bones_[i];
            std::string boneName(ToStdString(boneNode->mName));
            
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
            bones.push_back(newBone);
        }
        // Set the bone hierarchy
        for (unsigned i = 1; i < model.bones_.size(); ++i)
        {
            std::string parentName = ToStdString(model.bones_[i]->mParent->mName);
            for (unsigned j = 0; j < bones.size(); ++j)
            {
                if (bones[j].name_ == parentName)
                {
                    bones[i].parentIndex_ = j;
                    break;
                }
            }
        }
        
        outModel->SetSkeleton(skeleton);
        if (model.bones_.size() > MAX_SKIN_MATRICES)
            outModel->SetGeometryBoneMappings(allBoneMappings);
    }
    
    File outFile(context_);
    if (!outFile.Open(model.outName_, FILE_WRITE))
        ErrorExit("Could not open output file " + model.outName_);
    outModel->Save(outFile);
}

void BuildAndSaveAnimations(OutModel& model)
{
    for (unsigned i = 0; i < model.animations_.size(); ++i)
    {
        aiAnimation* anim = model.animations_[i];
        std::string aniname_ = ToStdString(anim->mName);
        if (aniname_.empty())
            aniname_ = "Anim" + ToString(i + 1);
        std::string anioutName_ = GetPath(model.outName_) + GetFileName(model.outName_) + "_" + SanitateAssetName(aniname_) + ".ani";
        
        SharedPtr<Animation> outAnim(new Animation(context_));
        float tickConversion = 1.0f / (float)anim->mTicksPerSecond;
        outAnim->SetAnimationName(aniname_);
        outAnim->SetLength((float)anim->mDuration * tickConversion);
        
        std::cout << "Writing animation " << aniname_ << " length " << outAnim->GetLength() << std::endl;
        std::vector<AnimationTrack> tracks;
        for (unsigned j = 0; j < anim->mNumChannels; ++j)
        {
            aiNodeAnim* channel = anim->mChannels[j];
            std::string channelName = ToStdString(channel->mNodeName);
            unsigned boneIndex = GetBoneIndex(model, channelName);
            if (boneIndex == M_MAX_UNSIGNED)
            {
                std::cout << "Warning: skipping animation track " << channelName << " not found in model skeleton" << std::endl;
                continue;
            }
            
            aiNode* boneNode = model.bones_[boneIndex];
            
            AnimationTrack track;
            track.name_ = channelName;
            track.nameHash_ = StringHash(channelName);
            
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
                    if ((fabsf(scaleVec.x_ - 1.0f) >= SCALE_EPSILON) || (fabsf(scaleVec.y_ - 1.0f) >= SCALE_EPSILON) ||
                        (fabsf(scaleVec.z_ - 1.0f) >= SCALE_EPSILON))
                    {
                        redundantScale = false;
                        break;
                    }
                }
                if (redundantScale)
                    track.channelMask_ &= ~CHANNEL_SCALE;
            }
            
            if (!track.channelMask_)
                std::cout << "Warning: skipping animation track " << channelName << " with no keyframes" << std::endl;
            
            // Currently only same amount of keyframes is supported
            // Note: should also check the times of individual keyframes for match
            if (((channel->mNumPositionKeys > 1) && (channel->mNumRotationKeys > 1) && (channel->mNumPositionKeys != channel->mNumRotationKeys)) ||
                ((channel->mNumPositionKeys > 1) && (channel->mNumScalingKeys > 1) && (channel->mNumPositionKeys != channel->mNumScalingKeys)) ||
                ((channel->mNumRotationKeys > 1) && (channel->mNumScalingKeys > 1) && (channel->mNumRotationKeys != channel->mNumScalingKeys)))
            {
                std::cout << "Warning: differing amounts of channel keyframes, skipping animation track " << channelName << std::endl;
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
                kf.scale_ = Vector3::UNITY;
                
                // Get time for the keyframe
                if ((track.channelMask_ & CHANNEL_POSITION) && (k < channel->mNumPositionKeys))
                    kf.time_ = (float)channel->mPositionKeys[k].mTime * tickConversion;
                else if ((track.channelMask_ & CHANNEL_ROTATION) && (k < channel->mNumRotationKeys))
                    kf.time_ = (float)channel->mRotationKeys[k].mTime * tickConversion;
                else if ((track.channelMask_ & CHANNEL_SCALE) && (k < channel->mNumScalingKeys))
                    kf.time_ = (float)channel->mScalingKeys[k].mTime * tickConversion;
                
                // Start with the bone's base transform
                aiMatrix4x4 boneTransform = boneNode->mTransformation;
                aiVector3D pos, scale;
                aiQuaternion rot;
                boneTransform.Decompose(scale, rot, pos);
                // Then apply the active channels
                if ((track.channelMask_ & CHANNEL_POSITION) && (k < channel->mNumPositionKeys))
                    pos = channel->mPositionKeys[k].mValue;
                if ((track.channelMask_ & CHANNEL_ROTATION) && (k < channel->mNumRotationKeys))
                    rot = channel->mRotationKeys[k].mValue;
                if ((track.channelMask_ & CHANNEL_SCALE) && (k < channel->mNumScalingKeys))
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
                
                track.keyFrames_.push_back(kf);
            }
            
            tracks.push_back(track);
        }
        
        outAnim->SetTracks(tracks);
        
        File outFile(context_);
        if (!outFile.Open(anioutName_, FILE_WRITE))
            ErrorExit("Could not open output file " + anioutName_);
        outAnim->Save(outFile);
    }
}

void ExportScene(const std::string& outName)
{
    OutScene outScene;
    outScene.outName_ = outName;
    outScene.rootNode_ = rootNode_;
    
    if (useSubdirs_)
        fileSystem_->CreateDir(resourcePath_ + "Models");
    
    CollectSceneModels(outScene, rootNode_);
    
    // Save models
    for (unsigned i = 0; i < outScene.models_.size(); ++i)
        BuildAndSaveModel(outScene.models_[i]);
    
    // Save scene
    BuildAndSaveScene(outScene);
}

void CollectSceneModels(OutScene& scene, aiNode* node)
{
    std::vector<std::pair<aiNode*, aiMesh*> > meshes;
    GetMeshesUnderNode(meshes, node);
    
    if (meshes.size())
    {
        OutModel model;
        model.rootNode_ = node;
        model.outName_ = resourcePath_ + (useSubdirs_ ? "Models/" : "") + SanitateAssetName(ToStdString(node->mName)) + ".mdl";
        for (unsigned i = 0; i < meshes.size(); ++i)
        {
            aiMesh* mesh = meshes[i].second;
            unsigned meshIndex = GetMeshIndex(mesh);
            model.meshIndices_.insert(meshIndex);
            model.meshes_.push_back(mesh);
            model.meshNodes_.push_back(meshes[i].first);
            model.totalVertices_ += mesh->mNumVertices;
            model.totalIndices_ += mesh->mNumFaces * 3;
        }
        
        // Check if a model with identical mesh indices already exists. If yes, do not export twice
        bool unique = true;
        for (unsigned i = 0; i < scene.models_.size(); ++i)
        {
            if (scene.models_[i].meshIndices_ == model.meshIndices_)
            {
                std::cout << "Added node " << ToStdString(node->mName) << std::endl;
                scene.nodes_.push_back(node);
                scene.nodeModelIndices_.push_back(i);
                unique = false;
                break;
            }
        }
        if (unique)
        {
            std::cout << "Added model " << model.outName_ << std::endl;
            std::cout << "Added node " << ToStdString(node->mName) << std::endl;
            CollectBones(model);
            BuildBoneCollisionInfo(model);
            if (!noAnimations_)
            {
                CollectAnimations(model);
                BuildAndSaveAnimations(model);
            }
            
            scene.models_.push_back(model);
            scene.nodes_.push_back(node);
            scene.nodeModelIndices_.push_back(scene.models_.size() - 1);
        }
    }
    
    for (unsigned i = 0; i < node->mNumChildren; ++i)
        CollectSceneModels(scene, node->mChildren[i]);
}

void BuildAndSaveScene(OutScene& scene)
{
    std::cout << "Writing scene" << std::endl;
    
    SharedPtr<Scene> outScene(new Scene(context_));
    outScene->SetName(GetFileName(scene.outName_));
    
    /// \todo Make the physics properties configurable
    PhysicsWorld* physicsWorld = outScene->CreateComponent<PhysicsWorld>();
    physicsWorld->SetGravity(Vector3(0.0f, -9.81f, 0.0f));
    
    /// \todo Make the octree properties configurable, or detect from the scene contents
    Octree* octree = outScene->CreateComponent<Octree>();
    
    if (createZone_)
    {
        Node* zoneNode = outScene->CreateChild("Zone");
        Zone* zone = zoneNode->CreateComponent<Zone>();
        zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.f));
        zone->SetAmbientColor(Color(0.25f, 0.25f, 0.25f));
        
        Node* lightNode = outScene->CreateChild("GlobalLight");
        Light* light = lightNode->CreateComponent<Light>();
        light->SetLightType(LIGHT_DIRECTIONAL);
        lightNode->SetRotation(Quaternion(60.0f, 30.0f, 0.0f));
    }
    
    ResourceCache* cache = context_->GetSubsystem<ResourceCache>();
    
    for (unsigned i = 0; i < scene.nodes_.size(); ++i)
    {
        const OutModel& model = scene.models_[scene.nodeModelIndices_[i]];
        
        // Create a static model component for each node
        Node* modelNode = outScene->CreateChild(ToStdString(scene.nodes_[i]->mName));
        StaticModel* staticModel = modelNode->CreateComponent<StaticModel>();
        
        // Create a dummy model so that the reference can be stored
        std::string modelName = (useSubdirs_ ? "Models/" : "") + GetFileNameAndExtension(model.outName_);
        if (!cache->Exists(modelName))
        {
            Model* dummyModel = new Model(context_);
            dummyModel->SetName(modelName);
            dummyModel->SetNumGeometries(model.meshes_.size());
            cache->AddManualResource(dummyModel);
        }
        staticModel->SetModel(cache->GetResource<Model>(modelName));
        
        // Set a flattened transform
        Vector3 pos, scale;
        Quaternion rot;
        GetPosRotScale(GetDerivedTransform(scene.nodes_[i], rootNode_), pos, rot, scale);
        modelNode->SetTransform(pos, rot, scale);
        // Set materials if they are known
        for (unsigned j = 0; j < model.meshes_.size(); ++j)
        {
            std::string matName = GetMeshMaterialName(model.meshes_[j]);
            if (!matName.empty())
            {
                // Create a dummy material so that the reference can be stored
                if (!cache->Exists(matName))
                {
                    Material* dummyMat = new Material(context_);
                    dummyMat->SetName(matName);
                    cache->AddManualResource(dummyMat);
                }
                staticModel->SetMaterial(cache->GetResource<Material>(matName));
            }
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

void ExportMaterials(std::set<std::string>& usedTextures)
{
    if (useSubdirs_)
        fileSystem_->CreateDir(resourcePath_ + "Materials");
    
    for (unsigned i = 0; i < scene_->mNumMaterials; ++i)
        BuildAndSaveMaterial(scene_->mMaterials[i], usedTextures);
}

void BuildAndSaveMaterial(aiMaterial* material, std::set<std::string>& usedTextures)
{
    // Material must have name so it can be successfully saved
    aiString matNameStr;
    material->Get(AI_MATKEY_NAME, matNameStr);
    std::string matName = SanitateAssetName(ToStdString(matNameStr));
    if (matName.empty())
        return;
    
    std::cout << "Writing material " << matName << std::endl;
    
    // Do not actually create a material instance, but instead craft an xml file manually
    XMLFile outMaterial(context_);
    XMLElement materialElem = outMaterial.CreateRootElement("material");
    
    std::string diffuseTexName;
    std::string normalTexName;
    Color diffuseColor;
    bool hasAlpha = false;
    bool twoSided = false;
    float specIntensity = 0.0f;
    float specPower = 1.0f;
    
    aiString stringVal;
    float floatVal;
    int intVal;
    aiColor3D colorVal;
    
    if (material->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), stringVal) == AI_SUCCESS)
        diffuseTexName = GetFileNameAndExtension(ToStdString(stringVal));
    if (material->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), stringVal) == AI_SUCCESS)
        normalTexName = GetFileNameAndExtension(ToStdString(stringVal));
    if (material->Get(AI_MATKEY_COLOR_DIFFUSE, colorVal) == AI_SUCCESS)
        diffuseColor = Color(colorVal.r, colorVal.g, colorVal.b);
    if (material->Get(AI_MATKEY_OPACITY, floatVal) == AI_SUCCESS)
    {
        if (floatVal < 1.0f)
            hasAlpha = true;
        diffuseColor.a_ = floatVal;
    }
    if (material->Get(AI_MATKEY_SHININESS, floatVal) == AI_SUCCESS)
        specPower = floatVal;
    if (material->Get(AI_MATKEY_SHININESS_STRENGTH, floatVal) == AI_SUCCESS)
        specIntensity = floatVal;
    if (material->Get(AI_MATKEY_TWOSIDED, intVal) == AI_SUCCESS)
        twoSided = (intVal != 0);
    
    std::string techniqueName = "Techniques/NoTexture";
    if (!diffuseTexName.empty())
    {
        techniqueName = "Techniques/Diff";
        if (!normalTexName.empty())
            techniqueName += "Normal";
    }
    if (hasAlpha)
        techniqueName += "Alpha";
    
    XMLElement techniqueElem = materialElem.CreateChildElement("technique");
    techniqueElem.SetString("name", techniqueName + ".xml");
    
    if (!diffuseTexName.empty())
    {
        XMLElement diffuseElem = materialElem.CreateChildElement("texture");
        diffuseElem.SetString("unit", "diffuse");
        diffuseElem.SetString("name", (useSubdirs_ ? "Textures/" : "") + diffuseTexName);
        usedTextures.insert(diffuseTexName);
    }
    if (!normalTexName.empty())
    {
        XMLElement normalElem = materialElem.CreateChildElement("texture");
        normalElem.SetString("unit", "diffuse");
        normalElem.SetString("name", (useSubdirs_ ? "Textures/" : "") + normalTexName);
        usedTextures.insert(normalTexName);
    }
    
    XMLElement diffuseColorElem = materialElem.CreateChildElement("parameter");
    diffuseColorElem.SetString("name", "MatDiffColor");
    diffuseColorElem.SetColor("value", diffuseColor);
    XMLElement specularElem = materialElem.CreateChildElement("parameter");
    specularElem.SetString("name", "MatSpecProperties");
    specularElem.SetVector2("value", Vector2(specIntensity, specPower));
    
    if (twoSided)
    {
        XMLElement cullElem = materialElem.CreateChildElement("cull");
        XMLElement shadowCullElem = materialElem.CreateChildElement("shadowcull");
        cullElem.SetString("value", "none");
        shadowCullElem.SetString("value", "none");
    }
    
    File outFile(context_);
    std::string outFileName = resourcePath_ + (useSubdirs_ ? "Materials/" : "" ) + matName + ".xml";
    if (!outFile.Open(outFileName, FILE_WRITE))
        ErrorExit("Could not open output file " + outFileName);
    outMaterial.Save(outFile);
}

void CopyTextures(const std::set<std::string>& usedTextures, const std::string& sourcePath)
{
    if (useSubdirs_)
        fileSystem_->CreateDir(resourcePath_ + "Textures");
    
    for (std::set<std::string>::const_iterator i = usedTextures.begin(); i != usedTextures.end(); ++i)
    {
        std::cout << "Copying texture " << *i << std::endl;
        fileSystem_->Copy(sourcePath + *i, resourcePath_ + (useSubdirs_ ? "Textures/" : "") + *i);
    }
}

void CombineLods(const std::vector<float>& lodDistances, const std::vector<std::string>& modelNames, const std::string& outName)
{
    // Load models
    std::vector<SharedPtr<Model> > srcModels;
    for (unsigned i = 0; i < modelNames.size(); ++i)
    {
        std::cout << "Reading LOD level " << i << ": model " + modelNames[i] << " distance " << lodDistances[i] << std::endl;
        File srcFile(context_);
        srcFile.Open(modelNames[i]);
        SharedPtr<Model> srcModel(new Model(context_));
        if (!srcModel->Load(srcFile))
            ErrorExit("Could not load input model " + modelNames[i]);
        srcModels.push_back(srcModel);
    }
    
    // Check that none of the models already has LOD levels
    for (unsigned i = 0; i < srcModels.size(); ++i)
    {
        for (unsigned j = 0; j < srcModels[i]->GetNumGeometries(); ++j)
        {
            if (srcModels[i]->GetNumGeometryLodLevels(j) > 1)
                ErrorExit(modelNames[i] + " already has multiple LOD levels defined");
        }
    }
    
    // Check for number of geometries (need to have same amount for now)
    for (unsigned i = 1; i < srcModels.size(); ++i)
    {
        if (srcModels[i]->GetNumGeometries() != srcModels[0]->GetNumGeometries())
            ErrorExit(modelNames[i] + " has different amount of geometries than " + modelNames[0]);
    }
    
    // If there are bones, check for compatibility (need to have exact match for now)
    for (unsigned i = 1; i < srcModels.size(); ++i)
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
    
    // Create the final model
    SharedPtr<Model> outModel(new Model(context_));
    outModel->SetNumGeometries(srcModels[0]->GetNumGeometries());
    for (unsigned i = 0; i < srcModels[0]->GetNumGeometries(); ++i)
    {
        outModel->SetNumGeometryLodLevels(i, srcModels.size());
        for (unsigned j = 0; j < srcModels.size(); ++j)
        {
            Geometry* geom = srcModels[j]->GetGeometry(i, 0);
            geom->SetLodDistance(lodDistances[j]);
            outModel->SetGeometry(i, j, geom);
        }
    }
    outModel->SetSkeleton(srcModels[0]->GetSkeleton());
    outModel->SetGeometryBoneMappings(srcModels[0]->GetGeometryBoneMappings());
    outModel->SetBoundingBox(srcModels[0]->GetBoundingBox());
    /// \todo Vertex morphs are ignored for now
    
    // Save the final model
    std::cout << "Writing output model" << std::endl;
    File outFile(context_);
    if (!outFile.Open(outName, FILE_WRITE))
        ErrorExit("Could not open output file " + outName);
    outModel->Save(outFile);
}

void GetMeshesUnderNode(std::vector<std::pair<aiNode*, aiMesh*> >& dest, aiNode* node)
{
    for (unsigned i = 0; i < node->mNumMeshes; ++i)
        dest.push_back(std::make_pair(node, scene_->mMeshes[node->mMeshes[i]]));
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

unsigned GetBoneIndex(OutModel& model, const std::string& boneName)
{
    for (unsigned i = 0; i < model.bones_.size(); ++i)
    {
        if (ToStdString(model.bones_[i]->mName) == boneName)
            return i;
    }
    return M_MAX_UNSIGNED;
}

aiBone* GetMeshBone(OutModel& model, const std::string& boneName)
{
    for (unsigned i = 0; i < model.meshes_.size(); ++i)
    {
        aiMesh* mesh = model.meshes_[i];
        for (unsigned j = 0; j < mesh->mNumBones; ++j)
        {
            aiBone* bone = mesh->mBones[j];
            if (ToStdString(bone->mName) == boneName)
                return bone;
        }
    }
    return 0;
}

Matrix4x3 GetOffsetMatrix(OutModel& model, const std::string& boneName)
{
    for (unsigned i = 0; i < model.meshes_.size(); ++i)
    {
        aiMesh* mesh = model.meshes_[i];
        aiNode* node = model.meshNodes_[i];
        for (unsigned j = 0; j < mesh->mNumBones; ++j)
        {
            aiBone* bone = mesh->mBones[j];
            if (ToStdString(bone->mName) == boneName)
            {
                aiMatrix4x4 offset = bone->mOffsetMatrix;
                aiMatrix4x4 nodeDerivedInverse = GetMeshBakingTransform(node, model.rootNode_);
                nodeDerivedInverse.Inverse();
                offset *= nodeDerivedInverse;
                Matrix4x3 ret;
                memcpy(&ret.m00_, &offset.a1, sizeof(Matrix4x3));
                return ret;
            }
        }
    }
    return Matrix4x3::IDENTITY;
}

void GetBlendData(OutModel& model, aiMesh* mesh, std::vector<unsigned>& boneMappings, std::vector<std::vector<unsigned char> >&
    blendIndices, std::vector<std::vector<float> >& blendWeights)
{
    blendIndices.resize(mesh->mNumVertices);
    blendWeights.resize(mesh->mNumVertices);
    boneMappings.clear();
    
    // If model has more bones than can fit vertex shader parameters, write the per-geometry mappings
    if (model.bones_.size() > MAX_SKIN_MATRICES)
    {
        if (mesh->mNumBones > MAX_SKIN_MATRICES)
            ErrorExit("Geometry has too many bone influences");
        boneMappings.resize(mesh->mNumBones);
        for (unsigned i = 0; i < mesh->mNumBones; ++i)
        {
            aiBone* bone = mesh->mBones[i];
            std::string boneName = ToStdString(bone->mName);
            unsigned globalIndex = GetBoneIndex(model, boneName);
            if (globalIndex == M_MAX_UNSIGNED)
                ErrorExit("Bone " + boneName + " not found");
            boneMappings[i] = globalIndex;
            for (unsigned j = 0; j < bone->mNumWeights; ++j)
            {
                unsigned vertex = bone->mWeights[j].mVertexId;
                blendIndices[vertex].push_back(i);
                blendWeights[vertex].push_back(bone->mWeights[j].mWeight);
                if (blendWeights[vertex].size() > 4)
                    ErrorExit("More than 4 bone influences on vertex");
            }
        }
    }
    else
    {
        for (unsigned i = 0; i < mesh->mNumBones; ++i)
        {
            aiBone* bone = mesh->mBones[i];
            std::string boneName = ToStdString(bone->mName);
            unsigned globalIndex = GetBoneIndex(model, boneName);
            if (globalIndex == M_MAX_UNSIGNED)
                ErrorExit("Bone " + boneName + " not found");
            for (unsigned j = 0; j < bone->mNumWeights; ++j)
            {
                unsigned vertex = bone->mWeights[j].mVertexId;
                blendIndices[vertex].push_back(globalIndex);
                blendWeights[vertex].push_back(bone->mWeights[j].mWeight);
                if (blendWeights[vertex].size() > 4)
                    ErrorExit("More than 4 bone influences on vertex");
            }
        }
    }
}

std::string GetMeshMaterialName(aiMesh* mesh)
{
    aiMaterial* material = scene_->mMaterials[mesh->mMaterialIndex];
    aiString matNameStr;
    material->Get(AI_MATKEY_NAME, matNameStr);
    std::string matName = SanitateAssetName(ToStdString(matNameStr));
    if (matName.empty())
        return matName;
    else
        return (useSubdirs_ ? "Materials/" : "") + matName + ".xml";
}

void WriteShortIndices(unsigned short*& dest, aiMesh* mesh, unsigned index, unsigned offset)
{
    *dest++ = mesh->mFaces[index].mIndices[0] + offset;
    *dest++ = mesh->mFaces[index].mIndices[1] + offset;
    *dest++ = mesh->mFaces[index].mIndices[2] + offset;
}

void WriteLargeIndices(unsigned*& dest, aiMesh* mesh, unsigned index, unsigned offset)
{
    *dest++ = mesh->mFaces[index].mIndices[0] + offset;
    *dest++ = mesh->mFaces[index].mIndices[1] + offset;
    *dest++ = mesh->mFaces[index].mIndices[2] + offset;
}

void WriteVertex(float*& dest, aiMesh* mesh, unsigned index, unsigned elementMask, BoundingBox& box,
    const Matrix4x3& vertexTransform, const Matrix3& normalTransform, std::vector<std::vector<unsigned char> >& blendIndices,
    std::vector<std::vector<float> >& blendWeights)
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
            if (i < blendWeights[index].size())
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
            if (i < blendIndices[index].size())
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

aiNode* FindNode(const std::string& name, aiNode* rootNode, bool caseSensitive)
{
    if (!rootNode)
        return 0;
    if (!caseSensitive)
    {
        if (ToLower(ToStdString(rootNode->mName)) == ToLower(name))
            return rootNode;
    }
    else
    {
        if (ToStdString(rootNode->mName) == name)
            return rootNode;
    }
    for (unsigned i = 0; i < rootNode->mNumChildren; ++i)
    {
        aiNode* found = FindNode(name, rootNode->mChildren[i], caseSensitive);
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
    while ((node) && (node != rootNode))
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


std::string ToStdString(const aiString& str)
{
    if ((!str.data) || (!str.length))
        return std::string();
    else
        return std::string(str.data);
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

std::string SanitateAssetName(const std::string& name)
{
    std::string fixedName = name;
    ReplaceInPlace(fixedName, "<", "");
    ReplaceInPlace(fixedName, ">", "");
    ReplaceInPlace(fixedName, "?", "");
    ReplaceInPlace(fixedName, "*", "");
    ReplaceInPlace(fixedName, ":", "");
    ReplaceInPlace(fixedName, "\"", "");
    ReplaceInPlace(fixedName, "/", "");
    ReplaceInPlace(fixedName, "\\", "");
    ReplaceInPlace(fixedName, "|", "");
    
    return fixedName;
}

void ErrorExit(const std::string& error)
{
    std::cout << error;
    exit(1);
}
