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

#include "Exception.h"
#include "Animation.h"
#include "File.h"
#include "Geometry.h"
#include "IndexBuffer.h"
#include "Light.h"
#include "Material.h"
#include "Model.h"
#include "Octree.h"
#include "PhysicsWorld.h"
#include "Quaternion.h"
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

struct ExportModel
{
    ExportModel() :
        mTotalVertices(0),
        mTotalIndices(0),
        mRootBone(0)
    {
    }
    
    std::string mOutName;
    aiNode* mRootNode;
    std::set<unsigned> mMeshIndices;
    std::vector<aiMesh*> mMeshes;
    std::vector<aiNode*> mMeshNodes;
    std::vector<aiNode*> mBones;
    std::vector<aiAnimation*> mAnimations;
    std::vector<float> mBoneRadii;
    std::vector<BoundingBox> mBoneHitboxes;
    aiNode* mRootBone;
    unsigned mTotalVertices;
    unsigned mTotalIndices;
};

struct ExportScene
{
    std::string mOutName;
    aiNode* mRootNode;
    std::vector<ExportModel> mModels;
    std::vector<aiNode*> mNodes;
    std::vector<unsigned> mNodeModelIndices;
};

Command gCommand = CMD_NONE;
const aiScene* gScene = 0;
aiNode* gRootNode = 0;
std::string gMaterialListName;
std::string gResourcePath;
bool gUseSubdirs = true;
bool gLocalIDs = false;
bool gSaveBinary = false;
bool gCreateZone = true;
bool gNoAnimations = false;

int main(int argc, char** argv);
void run(const std::vector<std::string>& arguments);
void dumpNodes(aiNode* rootNode, unsigned level);

void exportModel(const std::string& outName);
void collectMeshes(ExportModel& model, aiNode* node);
void collectBones(ExportModel& model);
void collectBonesFinal(std::vector<aiNode*>& dest, const std::set<aiNode*>& necessary, aiNode* node);
void collectAnimations(ExportModel& model);
void buildBoneCollisionInfo(ExportModel& model);
void buildAndSaveModel(ExportModel& model);
void buildAndSaveAnimations(ExportModel& model);

void exportScene(const std::string& outName);
void collectSceneModels(ExportScene& scene, aiNode* node);
void buildAndSaveScene(ExportScene& scene);

void exportMaterials(std::set<std::string>& usedTextures);
void buildAndSaveMaterial(aiMaterial* material, std::set<std::string>& usedTextures);
void copyTextures(const std::set<std::string>& usedTextures, const std::string& sourcePath);

void combineLods(const std::vector<float>& lodDistances, const std::vector<std::string>& modelNames, const std::string& outName,
    unsigned collisionLodLevel, unsigned raycastLodLevel, unsigned occlusionLodLevel);

void getMeshesUnderNode(std::vector<std::pair<aiNode*, aiMesh*> >& meshes, aiNode* node);
unsigned getMeshIndex(aiMesh* mesh);
unsigned getBoneIndex(ExportModel& model, const std::string& boneName);
aiBone* getMeshBone(ExportModel& model, const std::string& boneName);
Matrix4x3 getOffsetMatrix(ExportModel& model, const std::string& boneName);
void getBlendData(ExportModel& model, aiMesh* mesh, std::vector<unsigned>& boneMappings, std::vector<std::vector<unsigned char> >&
    blendIndices, std::vector<std::vector<float> >& blendWeights);
std::string getMeshMaterialName(aiMesh* mesh);

void writeShortIndices(unsigned short*& dest, aiMesh* mesh, unsigned index, unsigned offset);
void writeLargeIndices(unsigned*& dest, aiMesh* mesh, unsigned index, unsigned offset);
void writeVertex(float*& dest, aiMesh* mesh, unsigned index, unsigned elementMask, BoundingBox& box,
    const Matrix4x3& vertexTransform, const Matrix3& normalTransform, std::vector<std::vector<unsigned char> >& blendIndices,
    std::vector<std::vector<float> >& blendWeights);
unsigned getElementMask(aiMesh* mesh);

aiNode* findNode(const std::string& name, aiNode* rootNode, bool caseSensitive = true);
aiMatrix4x4 getDerivedTransform(aiNode* node, aiNode* rootNode);
aiMatrix4x4 getDerivedTransform(aiMatrix4x4 transform, aiNode* node, aiNode* rootNode);
aiMatrix4x4 getMeshBakingTransform(aiNode* meshNode, aiNode* modelRootNode);
void getPosRotScale(const aiMatrix4x4& transform, Vector3& pos, Quaternion& rot, Vector3& scale);

std::string toStdString(const aiString& str);
Vector3 toVector3(const aiVector3D& vec);
Vector2 toVector2(const aiVector2D& vec);
Quaternion toQuaternion(const aiQuaternion& quat);
std::string sanitateAssetName(const std::string& name);

void errorExit(const std::string& error);

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;
    
    for (int i = 1; i < argc; ++i)
        arguments.push_back(argv[i]);
    
    try
    {
        run(arguments);
    }
    catch (Exception& e)
    {
        std::cout << e.whatStr() << std::endl;
        return 1;
    }
    
    return 0;
}

void run(const std::vector<std::string>& arguments)
{
    if (arguments.size() < 2)
    {
        errorExit(
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
            "-lcX  Use LOD level X for collision mesh, default is middle LOD\n"
            "-lrX  Use LOD level X for raycast, default is same as visible\n"
            "-loX  Use LOD level X for occlusion, default is same as visible\n"
            "-mX   Output a material list file X (model mode only)\n"
            "-na   Do not export animations\n"
            "-nm   Do not export materials\n"
            "-ns   Do not create subdirectories for resources\n"
            "-nz   Do not create a zone and a directional light (scene mode only)\n"
            "-pX   Set path X for scene resources. Default is output file path\n"
            "-rX   Use scene node X as root node\n"
            "-t    Generate tangents to model(s)"
        );
    }
    
    std::string command = toLower(arguments[0]);
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
    
    unsigned collisionLodLevel = M_MAX_UNSIGNED;
    unsigned raycastLodLevel = M_MAX_UNSIGNED;
    unsigned occlusionLodLevel = M_MAX_UNSIGNED;
    
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
                gSaveBinary = true;
                break;
                
            case 'i':
                gLocalIDs = true;
                break;
                
            case 'l':
                if (parameter.length() > 1)
                {
                    switch (tolower(parameter[0]))
                    {
                    case 'c':
                        collisionLodLevel = toInt(parameter.substr(1));
                        break;
                        
                    case 'r':
                        raycastLodLevel = toInt(parameter.substr(1));
                        break;
                        
                    case 'o':
                        occlusionLodLevel = toInt(parameter.substr(1));
                        break;
                    }
                }
                break;
                
            case 'm':
                gMaterialListName = replace(parameter, '\\', '/');
                break;
                
            case 'p':
                gResourcePath = fixPath(parameter);
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
                        gNoAnimations = true;
                        break;
                        
                    case 'm':
                        noMaterials = true;
                        break;
                        
                    case 's':
                        gUseSubdirs = false;
                        break;
                        
                    case 'z':
                        gCreateZone = false;
                        break;
                    }
                }
                break;
            }
        }
    }
    
    if (command == "model")
        gCommand = CMD_MODEL;
    else if (command == "scene")
        gCommand = CMD_SCENE;
    else if (command == "dump")
        gCommand = CMD_DUMP;
    else if (command == "lod")
        gCommand = CMD_LOD;
    else
        errorExit("Unrecognized command " + command);
        
    if (gCommand != CMD_LOD)
    {
        std::string inFile = arguments[1];
        std::string outFile;
        if ((arguments.size() > 2) && (arguments[2][0] != '-'))
            outFile = replace(arguments[2], '\\', '/');
        
        if (gResourcePath.empty())
        {
            gResourcePath = getPath(outFile);
            // If output file already has the Models/ path (model mode), do not take it into the resource path
            if (gCommand == CMD_MODEL)
            {
                std::string resPathLower = toLower(gResourcePath);
                if (resPathLower.rfind("models/") == resPathLower.length() - 7)
                    gResourcePath = gResourcePath.substr(0, gResourcePath.length() - 7);
            }
            if (gResourcePath.empty())
                gResourcePath = "./";
        }
        
        gResourcePath = fixPath(gResourcePath);
        
        Assimp::Importer importer;
        std::cout << "Reading file " << inFile << std::endl;
        gScene = importer.ReadFile(getOSPath(inFile).c_str(), flags);
        if (!gScene)
            errorExit("Could not open or parse input file " + inFile);
        
        gRootNode = gScene->mRootNode;
        if (!rootNodeName.empty())
        {
            gRootNode = findNode(rootNodeName, gRootNode, false);
            if (!gRootNode)
                errorExit("Could not find scene node " + rootNodeName);
        }
        
        switch (gCommand)
        {
        case CMD_DUMP:
            dumpNodes(gRootNode, 0);
            return;
        
        case CMD_MODEL:
            exportModel(outFile);
            break;
            
        case CMD_SCENE:
            exportScene(outFile);
            break;
        }
        
        if (!noMaterials)
        {
            std::set<std::string> usedTextures;
            exportMaterials(usedTextures);
            copyTextures(usedTextures, getPath(inFile));
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
            errorExit("Must define at least 2 LOD levels");
        if (!(numLodArguments & 1))
            errorExit("No output file defined");
        
        for (unsigned i = 1; i < numLodArguments + 1; ++i)
        {
            if (i == numLodArguments)
                outFile = replace(arguments[i], '\\', '/');
            else
            {
                if (i & 1)
                    lodDistances.push_back(max(toFloat(arguments[i]), 0.0f));
                else
                    modelNames.push_back(replace(arguments[i], '\\', '/'));
            }
        }
        
        if (collisionLodLevel >= lodDistances.size())
            collisionLodLevel = M_MAX_UNSIGNED;
        if (raycastLodLevel >= lodDistances.size())
            raycastLodLevel = M_MAX_UNSIGNED;
        if (occlusionLodLevel >= lodDistances.size())
            occlusionLodLevel = M_MAX_UNSIGNED;
        
        if (lodDistances[0] != 0.0f)
        {
            std::cout << "Warning: first LOD distance forced to 0" << std::endl;
            lodDistances[0] = 0.0f;
        }
        
        combineLods(lodDistances, modelNames, outFile, collisionLodLevel, raycastLodLevel, occlusionLodLevel);
    }
}

void dumpNodes(aiNode* rootNode, unsigned level)
{
    if (!rootNode)
        return;
    
    std::string indent;
    indent.resize(level * 2);
    for (unsigned i = 0; i < level * 2; ++i)
        indent[i] = ' ';
    
    Vector3 pos, scale;
    Quaternion rot;
    aiMatrix4x4 transform = getDerivedTransform(rootNode, gRootNode);
    getPosRotScale(transform, pos, rot, scale);
    
    std::cout << indent << "Node " << toStdString(rootNode->mName) << " pos " << toString(pos) << std::endl;
    
    if (rootNode->mNumMeshes == 1)
        std::cout << indent << "  " << rootNode->mNumMeshes << " geometry" << std::endl;
    if (rootNode->mNumMeshes > 1)
        std::cout << indent << "  " << rootNode->mNumMeshes << " geometries" << std::endl;
    
    for (unsigned i = 0; i < rootNode->mNumChildren; ++i)
        dumpNodes(rootNode->mChildren[i], level + 1);
}

void exportModel(const std::string& outName)
{
    if (outName.empty())
        errorExit("No output file defined");
    
    ExportModel model;
    model.mRootNode = gRootNode;
    model.mOutName = outName;
    
    collectMeshes(model, model.mRootNode);
    collectBones(model);
    buildBoneCollisionInfo(model);
    buildAndSaveModel(model);
    if (!gNoAnimations)
    {
        collectAnimations(model);
        buildAndSaveAnimations(model);
    }
    
    // Write material references if requested
    if (!gMaterialListName.empty())
    {
        File listFile(gMaterialListName, FILE_WRITE);
        for (unsigned i = 0; i < model.mMeshes.size(); ++i)
            listFile.writeLine(getMeshMaterialName(model.mMeshes[i]));
    }
}

void collectMeshes(ExportModel& model, aiNode* node)
{
    for (unsigned i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = gScene->mMeshes[node->mMeshes[i]];
        for (unsigned j = 0; j < model.mMeshes.size(); ++j)
        {
            if (mesh == model.mMeshes[j])
            {
                std::cout << "Warning: same mesh found multiple times" << std::endl;
                break;
            }
        }
        
        model.mMeshIndices.insert(node->mMeshes[i]);
        model.mMeshes.push_back(mesh);
        model.mMeshNodes.push_back(node);
        model.mTotalVertices += mesh->mNumVertices;
        model.mTotalIndices += mesh->mNumFaces * 3;
    }
    
    for (unsigned i = 0; i < node->mNumChildren; ++i)
        collectMeshes(model, node->mChildren[i]);
}

void collectBones(ExportModel& model)
{
    std::set<aiNode*> necessary;
    std::set<aiNode*> rootNodes;
    
    for (unsigned i = 0; i < model.mMeshes.size(); ++i)
    {
        aiMesh* mesh = model.mMeshes[i];
        aiNode* meshNode = model.mMeshNodes[i];
        aiNode* meshParentNode = meshNode->mParent;
        aiNode* rootNode = 0;
        
        for (unsigned j = 0; j < mesh->mNumBones; ++j)
        {
            aiBone* bone = mesh->mBones[j];
            std::string boneName(toStdString(bone->mName));
            aiNode* boneNode = findNode(boneName, gScene->mRootNode, true);
            if (!boneNode)
                errorExit("Could not find scene node for bone " + boneName);
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
                    errorExit("Skeleton with multiple root nodes found, not supported");
            }
        }
        rootNodes.clear();
        rootNodes.insert(commonParent);
        necessary.insert(commonParent);
    }
    
    if (rootNodes.empty())
        return;
    
    model.mRootBone = *rootNodes.begin();
    collectBonesFinal(model.mBones, necessary, model.mRootBone);
    // Initialize the bone collision info
    model.mBoneRadii.resize(model.mBones.size());
    model.mBoneHitboxes.resize(model.mBones.size());
    for (unsigned i = 0; i < model.mBones.size(); ++i)
    {
        model.mBoneRadii[i] = 0.0f;
        model.mBoneHitboxes[i] = BoundingBox(0.0f, 0.0f);
    }
}

void collectBonesFinal(std::vector<aiNode*>& dest, const std::set<aiNode*>& necessary, aiNode* node)
{
    if (necessary.find(node) != necessary.end())
    {
        dest.push_back(node);
        for (unsigned i = 0; i < node->mNumChildren; ++i)
            collectBonesFinal(dest, necessary, node->mChildren[i]);
    }
}

void collectAnimations(ExportModel& model)
{
    const aiScene* scene = gScene;
    for (unsigned i = 0; i < scene->mNumAnimations; ++i)
    {
        aiAnimation* anim = scene->mAnimations[i];
        bool modelBoneFound = false;
        for (unsigned j = 0; j < anim->mNumChannels; ++j)
        {
            aiNodeAnim* channel = anim->mChannels[j];
            std::string channelName = toStdString(channel->mNodeName);
            if (getBoneIndex(model, channelName) != M_MAX_UNSIGNED)
            {
                modelBoneFound = true;
                break;
            }
        }
        if (modelBoneFound)
            model.mAnimations.push_back(anim);
    }
    
    //! \todo Vertex morphs are ignored for now
}

void buildBoneCollisionInfo(ExportModel& model)
{
    for (unsigned i = 0; i < model.mMeshes.size(); ++i)
    {
        aiMesh* mesh = model.mMeshes[i];
        for (unsigned j = 0; j < mesh->mNumBones; ++j)
        {
            aiBone* bone = mesh->mBones[j];
            std::string boneName = toStdString(bone->mName);
            unsigned boneIndex = getBoneIndex(model, boneName);
            if (boneIndex == M_MAX_UNSIGNED)
                continue;
            aiNode* boneNode = model.mBones[boneIndex];
            for (unsigned k = 0; k < bone->mNumWeights; ++k)
            {
                float weight = bone->mWeights[k].mWeight;
                if (weight > 0.33f)
                {
                    aiVector3D vertexBoneSpace = bone->mOffsetMatrix * mesh->mVertices[bone->mWeights[k].mVertexId];
                    Vector3 vertex = toVector3(vertexBoneSpace);
                    float radius = vertex.getLength();
                    if (radius > model.mBoneRadii[boneIndex])
                        model.mBoneRadii[boneIndex] = radius;
                    model.mBoneHitboxes[boneIndex].merge(vertex);
                }
            }
        }
    }
}

void buildAndSaveModel(ExportModel& model)
{
    if (!model.mRootNode)
        errorExit("Null root node for model");
    std::string rootNodeName = toStdString(model.mRootNode->mName);
    if (!model.mMeshes.size())
        errorExit("No geometries found starting from node " + rootNodeName);
    
    std::cout << "Writing model " << rootNodeName << std::endl;
    
    SharedPtr<Model> outModel(new Model(0));
    outModel->setNumGeometries(model.mMeshes.size());
    std::vector<std::vector<unsigned> > allBoneMappings;
    BoundingBox box;
    
    bool combineBuffers = true;
    // Check if buffers can be combined (same vertex element mask, under 65535 vertices)
    unsigned elementMask = getElementMask(model.mMeshes[0]);
    for (unsigned i = 1; i < model.mMeshes.size(); ++i)
    {
        if (getElementMask(model.mMeshes[i]) != elementMask)
        {
            combineBuffers = false;
            break;
        }
    }
    // Check if keeping separate buffers allows to avoid 32-bit indices
    if ((combineBuffers) && (model.mTotalVertices > 65535))
    {
        bool allUnder65k = true;
        for (unsigned i = 0; i < model.mMeshes.size(); ++i)
        {
            if (model.mMeshes[i]->mNumVertices > 65535)
                allUnder65k = false;
        }
        if (allUnder65k == true)
            combineBuffers = false;
    }
    
    if (!combineBuffers)
    {
        std::cout << "Writing separate buffers" << std::endl;
        for (unsigned i = 0; i < model.mMeshes.size(); ++i)
        {
            // Get the world transform of the mesh for baking into the vertices
            Matrix4x3 vertexTransform;
            Matrix3 normalTransform;
            Vector3 pos, scale;
            Quaternion rot;
            getPosRotScale(getMeshBakingTransform(model.mMeshNodes[i], model.mRootNode), pos, rot, scale);
            vertexTransform.define(pos, rot, scale);
            normalTransform = rot.getRotationMatrix();
            
            SharedPtr<IndexBuffer> ib(new IndexBuffer(0));
            SharedPtr<VertexBuffer> vb(new VertexBuffer(0));
            SharedPtr<Geometry> geom(new Geometry());
            
            aiMesh* mesh = model.mMeshes[i];
            std::cout << "Writing geometry " << i << " with " << mesh->mNumVertices << " vertices " << mesh->mNumFaces * 3 
                << " indices" << std::endl;
            
            bool largeIndices = mesh->mNumVertices > 65535;
            unsigned elementMask = getElementMask(mesh);
            
            ib->setSize(mesh->mNumFaces * 3, largeIndices);
            vb->setSize(mesh->mNumVertices, elementMask);
            
            // Build the index data
            void* indexData = ib->lock(0, ib->getIndexCount(), LOCK_NORMAL);
            if (!largeIndices)
            {
                unsigned short* dest = (unsigned short*)indexData;
                for (unsigned j = 0; j < mesh->mNumFaces; ++j)
                    writeShortIndices(dest, mesh, j, 0);
            }
            else
            {
                unsigned* dest = (unsigned*)indexData;
                for (unsigned j = 0; j < mesh->mNumFaces; ++j)
                    writeLargeIndices(dest, mesh, j, 0);
            }
            
            // Build the vertex data
            // If there are bones, get blend data
            std::vector<std::vector<unsigned char> > blendIndices;
            std::vector<std::vector<float> > blendWeights;
            std::vector<unsigned> boneMappings;
            if (model.mBones.size())
                getBlendData(model, mesh, boneMappings, blendIndices, blendWeights);
            
            void* vertexData = vb->lock(0, vb->getVertexCount(), LOCK_NORMAL);
            float* dest = (float*)vertexData;
            for (unsigned j = 0; j < mesh->mNumVertices; ++j)
                writeVertex(dest, mesh, j, elementMask, box, vertexTransform, normalTransform, blendIndices, blendWeights);
            
            ib->unlock();
            vb->unlock();
            
            // Define the geometry
            geom->setIndexBuffer(ib);
            geom->setVertexBuffer(0, vb);
            geom->setDrawRange(TRIANGLE_LIST, 0, mesh->mNumFaces * 3, true);
            outModel->setNumGeometryLodLevels(i, 1);
            outModel->setGeometry(i, 0, geom);
            if (model.mBones.size() > MAX_SKIN_MATRICES)
                allBoneMappings.push_back(boneMappings);
        }
    }
    else
    {
        SharedPtr<IndexBuffer> ib(new IndexBuffer(0));
        SharedPtr<VertexBuffer> vb(new VertexBuffer(0));
        
        bool largeIndices = model.mTotalIndices > 65535;
        ib->setSize(model.mTotalIndices, largeIndices);
        vb->setSize(model.mTotalVertices, elementMask);
        
        unsigned startVertexOffset = 0;
        unsigned startIndexOffset = 0;
        void* indexData = ib->lock(0, ib->getIndexCount(), LOCK_NORMAL);
        void* vertexData = vb->lock(0, vb->getVertexCount(), LOCK_NORMAL);
        // The buffer is in CPU memory, and therefore locking is irrelevant. Unlock so that draw range checking can lock again
        ib->unlock();
        vb->unlock();
        
        for (unsigned i = 0; i < model.mMeshes.size(); ++i)
        {
            // Get the world transform of the mesh for baking into the vertices
            Matrix4x3 vertexTransform;
            Matrix3 normalTransform;
            Vector3 pos, scale;
            Quaternion rot;
            getPosRotScale(getMeshBakingTransform(model.mMeshNodes[i], model.mRootNode), pos, rot, scale);
            vertexTransform.define(pos, rot, scale);
            normalTransform = rot.getRotationMatrix();
            
            SharedPtr<Geometry> geom(new Geometry());
            
            aiMesh* mesh = model.mMeshes[i];
            std::cout << "Writing geometry " << i << " with " << mesh->mNumVertices << " vertices " << mesh->mNumFaces * 3 
                << " indices" << std::endl;
            
            // Build the index data
            if (!largeIndices)
            {
                unsigned short* dest = (unsigned short*)indexData + startIndexOffset;
                for (unsigned j = 0; j < mesh->mNumFaces; ++j)
                    writeShortIndices(dest, mesh, j, startVertexOffset);
            }
            else
            {
                unsigned* dest = (unsigned*)indexData + startIndexOffset;
                for (unsigned j = 0; j < mesh->mNumFaces; ++j)
                    writeLargeIndices(dest, mesh, j, startVertexOffset);
            }
            
            // Build the vertex data
            // If there are bones, get blend data
            std::vector<std::vector<unsigned char> > blendIndices;
            std::vector<std::vector<float> > blendWeights;
            std::vector<unsigned> boneMappings;
            if (model.mBones.size())
                getBlendData(model, mesh, boneMappings, blendIndices, blendWeights);
            
            float* dest = (float*)((unsigned char*)vertexData + startVertexOffset * vb->getVertexSize());
            for (unsigned j = 0; j < mesh->mNumVertices; ++j)
                writeVertex(dest, mesh, j, elementMask, box, vertexTransform, normalTransform, blendIndices, blendWeights);
            
            // Define the geometry
            geom->setIndexBuffer(ib);
            geom->setVertexBuffer(0, vb);
            geom->setDrawRange(TRIANGLE_LIST, startIndexOffset, mesh->mNumFaces * 3, true);
            outModel->setNumGeometryLodLevels(i, 1);
            outModel->setGeometry(i, 0, geom);
            if (model.mBones.size() > MAX_SKIN_MATRICES)
                allBoneMappings.push_back(boneMappings);
            
            startVertexOffset += mesh->mNumVertices;
            startIndexOffset += mesh->mNumFaces * 3;
        }
    }
    
    outModel->setBoundingBox(box);
    
    // Build skeleton if necessary
    if ((model.mBones.size()) && (model.mRootBone))
    {
        std::cout << "Writing skeleton with " << model.mBones.size() << " bones, rootbone " +
            toStdString(model.mRootBone->mName) << std::endl;
        
        Skeleton skeleton;
        std::vector<SharedPtr<Bone> > srcBones;
        
        for (unsigned i = 0; i < model.mBones.size(); ++i)
        {
            aiNode* boneNode = model.mBones[i];
            std::string boneName(toStdString(boneNode->mName));
            
            srcBones.push_back(SharedPtr<Bone>(new Bone(0, boneName)));
            srcBones[i]->setRootBone(srcBones[0]);
            
            aiMatrix4x4 transform = boneNode->mTransformation;
            // Make the root bone transform relative to the model's root node, if it is not already
            if (boneNode == model.mRootBone)
                transform = getDerivedTransform(boneNode, model.mRootNode);
            
            Vector3 pos, scale;
            Quaternion rot;
            getPosRotScale(transform, pos, rot, scale);
            
            // Get offset information if exists
            srcBones[i]->setOffsetMatrix(getOffsetMatrix(model, boneName));
            
            srcBones[i]->setInitialTransform(pos, rot, scale);
            srcBones[i]->setRadius(model.mBoneRadii[i]);
            srcBones[i]->setBoundingBox(model.mBoneHitboxes[i]);
        }
        // Set the bone hierarchy
        for (unsigned i = 1; i < model.mBones.size(); ++i)
        {
            std::string parentName = toStdString(model.mBones[i]->mParent->mName);
            for (unsigned j = 0; j < srcBones.size(); ++j)
            {
                if ((srcBones[j]->getName() == parentName) && (i != j))
                {
                    srcBones[j]->addChild(srcBones[i]);
                    break;
                }
            }
        }
        
        skeleton.setBones(srcBones, srcBones[0]);
        outModel->setSkeleton(skeleton);
        if (model.mBones.size() > MAX_SKIN_MATRICES)
            outModel->setGeometryBoneMappings(allBoneMappings);
    }
    
    File outFile(model.mOutName, FILE_WRITE);
    outModel->save(outFile);
}

void buildAndSaveAnimations(ExportModel& model)
{
    for (unsigned i = 0; i < model.mAnimations.size(); ++i)
    {
        aiAnimation* anim = model.mAnimations[i];
        std::string animName = toStdString(anim->mName);
        if (animName.empty())
            animName = "Anim" + toString(i + 1);
        std::string animOutName = getPath(model.mOutName) + getFileName(model.mOutName) + "_" + sanitateAssetName(animName) + ".ani";
        
        SharedPtr<Animation> outAnim(new Animation());
        float tickConversion = 1.0f / (float)anim->mTicksPerSecond;
        outAnim->setAnimationName(animName);
        outAnim->setLength((float)anim->mDuration * tickConversion);
        
        std::cout << "Writing animation " << animName << " length " << outAnim->getLength() << std::endl;
        std::vector<AnimationTrack> tracks;
        for (unsigned j = 0; j < anim->mNumChannels; ++j)
        {
            aiNodeAnim* channel = anim->mChannels[j];
            std::string channelName = toStdString(channel->mNodeName);
            unsigned boneIndex = getBoneIndex(model, channelName);
            if (boneIndex == M_MAX_UNSIGNED)
            {
                std::cout << "Warning: skipping animation track " << channelName << " not found in model skeleton" << std::endl;
                continue;
            }
            
            aiNode* boneNode = model.mBones[boneIndex];
            
            AnimationTrack track;
            track.mName = channelName;
            track.mNameHash = StringHash(channelName);
            
            // Check which channels are used
            track.mChannelMask = 0;
            if (channel->mNumPositionKeys > 1)
                track.mChannelMask |= CHANNEL_POSITION;
            if (channel->mNumRotationKeys > 1)
                track.mChannelMask |= CHANNEL_ROTATION;
            if (channel->mNumScalingKeys > 1)
                track.mChannelMask |= CHANNEL_SCALE;
            // Check for redundant identity scale in all keyframes and remove in that case
            if (track.mChannelMask & CHANNEL_SCALE)
            {
                bool redundantScale = true;
                for (unsigned k = 0; k < channel->mNumScalingKeys; ++k)
                {
                    float SCALE_EPSILON = 0.000001f;
                    Vector3 scaleVec = toVector3(channel->mScalingKeys[k].mValue);
                    if ((fabsf(scaleVec.mX - 1.0f) >= SCALE_EPSILON) || (fabsf(scaleVec.mY - 1.0f) >= SCALE_EPSILON) ||
                        (fabsf(scaleVec.mZ - 1.0f) >= SCALE_EPSILON))
                    {
                        redundantScale = false;
                        break;
                    }
                }
                if (redundantScale)
                    track.mChannelMask &= ~CHANNEL_SCALE;
            }
            
            if (!track.mChannelMask)
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
                kf.mTime = 0.0f;
                kf.mPosition = Vector3::sZero;
                kf.mRotation = Quaternion::sIdentity;
                kf.mScale = Vector3::sUnity;
                
                // Get time for the keyframe
                if ((track.mChannelMask & CHANNEL_POSITION) && (k < channel->mNumPositionKeys))
                    kf.mTime = (float)channel->mPositionKeys[k].mTime * tickConversion;
                else if ((track.mChannelMask & CHANNEL_ROTATION) && (k < channel->mNumRotationKeys))
                    kf.mTime = (float)channel->mRotationKeys[k].mTime * tickConversion;
                else if ((track.mChannelMask & CHANNEL_SCALE) && (k < channel->mNumScalingKeys))
                    kf.mTime = (float)channel->mScalingKeys[k].mTime * tickConversion;
                
                // Start with the bone's base transform
                aiMatrix4x4 boneTransform = boneNode->mTransformation;
                aiVector3D pos, scale;
                aiQuaternion rot;
                boneTransform.Decompose(scale, rot, pos);
                // Then apply the active channels
                if ((track.mChannelMask & CHANNEL_POSITION) && (k < channel->mNumPositionKeys))
                    pos = channel->mPositionKeys[k].mValue;
                if ((track.mChannelMask & CHANNEL_ROTATION) && (k < channel->mNumRotationKeys))
                    rot = channel->mRotationKeys[k].mValue;
                if ((track.mChannelMask & CHANNEL_SCALE) && (k < channel->mNumScalingKeys))
                    scale = channel->mScalingKeys[k].mValue;
                
                // If root bone, transform with the model root node transform
                if (!boneIndex)
                {
                    aiMatrix4x4 transMat, scaleMat, rotMat;
                    aiMatrix4x4::Translation(pos, transMat);
                    aiMatrix4x4::Scaling(scale, scaleMat);
                    rotMat = aiMatrix4x4(rot.GetMatrix());
                    aiMatrix4x4 tform = transMat * rotMat * scaleMat;
                    tform = getDerivedTransform(tform, boneNode, model.mRootNode);
                    tform.Decompose(scale, rot, pos);
                }
                
                if (track.mChannelMask & CHANNEL_POSITION)
                    kf.mPosition = toVector3(pos);
                if (track.mChannelMask & CHANNEL_ROTATION)
                    kf.mRotation = toQuaternion(rot);
                if (track.mChannelMask & CHANNEL_SCALE)
                    kf.mScale = toVector3(scale);
                
                track.mKeyFrames.push_back(kf);
            }
            
            tracks.push_back(track);
        }
        
        outAnim->setTracks(tracks);
        
        File outFile(animOutName, FILE_WRITE);
        outAnim->save(outFile);
    }
}

void exportScene(const std::string& outName)
{
    ExportScene outScene;
    outScene.mOutName = outName;
    outScene.mRootNode = gRootNode;
    
    if (gUseSubdirs)
        createDirectory(gResourcePath + "Models");
    
    collectSceneModels(outScene, gRootNode);
    
    // Save models
    try
    {
        for (unsigned i = 0; i < outScene.mModels.size(); ++i)
            buildAndSaveModel(outScene.mModels[i]);
    }
    catch (Exception &e)
    {
        std::cout << e.whatStr() << std::endl;
    }
    
    // Save scene
    buildAndSaveScene(outScene);
}

void collectSceneModels(ExportScene& scene, aiNode* node)
{
    std::vector<std::pair<aiNode*, aiMesh*> > meshes;
    getMeshesUnderNode(meshes, node);
    
    if (meshes.size())
    {
        ExportModel model;
        model.mRootNode = node;
        model.mOutName = gResourcePath + (gUseSubdirs ? "Models/" : "") + sanitateAssetName(toStdString(node->mName)) + ".mdl";
        for (unsigned i = 0; i < meshes.size(); ++i)
        {
            aiMesh* mesh = meshes[i].second;
            unsigned meshIndex = getMeshIndex(mesh);
            model.mMeshIndices.insert(meshIndex);
            model.mMeshes.push_back(mesh);
            model.mMeshNodes.push_back(meshes[i].first);
            model.mTotalVertices += mesh->mNumVertices;
            model.mTotalIndices += mesh->mNumFaces * 3;
        }
        
        // Check if a model with identical mesh indices already exists. If yes, do not export twice
        bool unique = true;
        for (unsigned i = 0; i < scene.mModels.size(); ++i)
        {
            if (scene.mModels[i].mMeshIndices == model.mMeshIndices)
            {
                std::cout << "Added node " << toStdString(node->mName) << std::endl;
                scene.mNodes.push_back(node);
                scene.mNodeModelIndices.push_back(i);
                unique = false;
                break;
            }
        }
        if (unique)
        {
            std::cout << "Added model " << model.mOutName << std::endl;
            std::cout << "Added node " << toStdString(node->mName) << std::endl;
            collectBones(model);
            buildBoneCollisionInfo(model);
            if (!gNoAnimations)
            {
                collectAnimations(model);
                buildAndSaveAnimations(model);
            }
            
            scene.mModels.push_back(model);
            scene.mNodes.push_back(node);
            scene.mNodeModelIndices.push_back(scene.mModels.size() - 1);
        }
    }
    
    for (unsigned i = 0; i < node->mNumChildren; ++i)
        collectSceneModels(scene, node->mChildren[i]);
}

void buildAndSaveScene(ExportScene& scene)
{
    std::cout << "Writing scene" << std::endl;
    
    SharedPtr<Scene> outScene(new Scene(0, getFileName(scene.mOutName)));
    
    //! \todo Make the physics properties configurable
    PhysicsWorld* physicsWorld = new PhysicsWorld();
    physicsWorld->setGravity(Vector3(0.0f, -9.81f, 0.0f));
    outScene->addExtension(physicsWorld);
    
    //! \todo Make the octree properties configurable, or detect from the scene contents
    Octree* octree = new Octree(BoundingBox(-1000.0f, 1000.0f), 8, true);
    outScene->addExtension(octree);
    
    if (gCreateZone)
    {
        Entity* entity = outScene->createEntity("Zone", gLocalIDs);
        
        Zone* zone = new Zone();
        entity->addComponent(zone);
        zone->setBoundingBox(BoundingBox(-1000.0f, 1000.f));
        zone->setAmbientColor(Color(0.25f, 0.25f, 0.25f));
        
        Light* light = new Light();
        entity->addComponent(light);
        light->setLightType(LIGHT_DIRECTIONAL);
        light->setRotation(Vector3(60.0f, 30.0f, 0.0f));
    }
    
    std::map<std::string, SharedPtr<Material> > dummyMaterials;
    
    for (unsigned i = 0; i < scene.mNodes.size(); ++i)
    {
        const ExportModel& model = scene.mModels[scene.mNodeModelIndices[i]];
        
        // Create a simple entity and static model component for each node
        Entity* entity = outScene->createEntity(toStdString(scene.mNodes[i]->mName), gLocalIDs);
        StaticModel* staticModel = new StaticModel();
        entity->addComponent(staticModel);
        // Create a dummy model so that the reference can be stored
        std::string modelPath = (gUseSubdirs ? "Models/" : "") + getFileNameAndExtension(model.mOutName);
        SharedPtr<Model> dummyModel(new Model(0, modelPath));
        dummyModel->setNumGeometries(model.mMeshes.size());
        staticModel->setModel(dummyModel);
        // Set a flattened transform
        Vector3 pos, scale;
        Quaternion rot;
        getPosRotScale(getDerivedTransform(scene.mNodes[i], gRootNode), pos, rot, scale);
        staticModel->setTransform(pos, rot, scale);
        // Set materials if they are known
        for (unsigned j = 0; j < model.mMeshes.size(); ++j)
        {
            std::string matName = getMeshMaterialName(model.mMeshes[j]);
            if (!matName.empty())
            {
                // Create a dummy material so that the reference can be stored
                if (dummyMaterials.find(matName) == dummyMaterials.end())
                    dummyMaterials[matName] = new Material(matName);
                staticModel->setMaterial(j, dummyMaterials[matName]);
            }
        }
    }
    
    File file(scene.mOutName, FILE_WRITE);
    if (!gSaveBinary)
        outScene->saveXML(file);
    else
        outScene->save(file);
}

void exportMaterials(std::set<std::string>& usedTextures)
{
    if (gUseSubdirs)
        createDirectory(gResourcePath + "Materials");
    
    for (unsigned i = 0; i < gScene->mNumMaterials; ++i)
    {
        try
        {
            buildAndSaveMaterial(gScene->mMaterials[i], usedTextures);
        }
        catch (Exception& e)
        {
            std::cout << e.whatStr() << std::endl;
        }
    }
}

void buildAndSaveMaterial(aiMaterial* material, std::set<std::string>& usedTextures)
{
    // Material must have name so it can be successfully saved
    aiString matNameStr;
    material->Get(AI_MATKEY_NAME, matNameStr);
    std::string matName = sanitateAssetName(toStdString(matNameStr));
    if (matName.empty())
        return;
    
    std::cout << "Writing material " << matName << std::endl;
    
    // Do not actually create a material instance, but instead craft an xml file manually, defining a suitable base material
    XMLFile outMaterial;
    XMLElement materialElem = outMaterial.createRootElement("material");
    
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
        diffuseTexName = getFileNameAndExtension(toStdString(stringVal));
    if (material->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), stringVal) == AI_SUCCESS)
        normalTexName = getFileNameAndExtension(toStdString(stringVal));
    if (material->Get(AI_MATKEY_COLOR_DIFFUSE, colorVal) == AI_SUCCESS)
        diffuseColor = Color(colorVal.r, colorVal.g, colorVal.b);
    if (material->Get(AI_MATKEY_OPACITY, floatVal) == AI_SUCCESS)
    {
        if (floatVal < 1.0f)
            hasAlpha = true;
        diffuseColor.mA = floatVal;
    }
    if (material->Get(AI_MATKEY_SHININESS, floatVal) == AI_SUCCESS)
        specPower = floatVal;
    if (material->Get(AI_MATKEY_SHININESS_STRENGTH, floatVal) == AI_SUCCESS)
        specIntensity = floatVal;
    if (material->Get(AI_MATKEY_TWOSIDED, intVal) == AI_SUCCESS)
        twoSided = (intVal != 0);
    
    std::string baseMatName = "Materials/Default";
    if (!diffuseTexName.empty())
    {
        baseMatName += "Diff";
        if (!normalTexName.empty())
            baseMatName += "Normal";
    }
    if (hasAlpha)
        baseMatName += "Alpha";
    if (twoSided)
        baseMatName += "TS";
    
    XMLElement baseElem = materialElem.createChildElement("base");
    baseElem.setString("name", baseMatName + ".xml");
    
    XMLElement techniqueElem = materialElem.createChildElement("technique");
    if (!diffuseTexName.empty())
    {
        XMLElement diffuseElem = techniqueElem.createChildElement("texture");
        diffuseElem.setString("unit", "diffuse");
        diffuseElem.setString("name", (gUseSubdirs ? "Textures/" : "") + diffuseTexName);
        usedTextures.insert(diffuseTexName);
    }
    if (!normalTexName.empty())
    {
        XMLElement normalElem = techniqueElem.createChildElement("texture");
        normalElem.setString("unit", "diffuse");
        normalElem.setString("name", (gUseSubdirs ? "Textures/" : "") + normalTexName);
        usedTextures.insert(normalTexName);
    }
    XMLElement diffuseColorElem = techniqueElem.createChildElement("parameter");
    diffuseColorElem.setString("name", "MatDiffColor");
    diffuseColorElem.setColor("value", diffuseColor);
    XMLElement specularElem = techniqueElem.createChildElement("parameter");
    specularElem.setString("name", "MatSpecProperties");
    specularElem.setVector2("value", Vector2(specIntensity, specPower));
    
    File outFile(gResourcePath + (gUseSubdirs ? "Materials/" : "" ) + matName + ".xml", FILE_WRITE);
    outMaterial.save(outFile);
}

void copyTextures(const std::set<std::string>& usedTextures, const std::string& sourcePath)
{
    if (gUseSubdirs)
        createDirectory(gResourcePath + "Textures");
    
    for (std::set<std::string>::const_iterator i = usedTextures.begin(); i != usedTextures.end(); ++i)
    {
        std::cout << "Copying texture " << *i << std::endl;
        copyFile(sourcePath + *i, gResourcePath + (gUseSubdirs ? "Textures/" : "") + *i);
    }
}

void combineLods(const std::vector<float>& lodDistances, const std::vector<std::string>& modelNames, const std::string& outName,
    unsigned collisionLodLevel, unsigned raycastLodLevel, unsigned occlusionLodLevel)
{
    // Load models
    std::vector<SharedPtr<Model> > srcModels;
    for (unsigned i = 0; i < modelNames.size(); ++i)
    {
        std::cout << "Reading LOD level " << i << ": model " + modelNames[i] << " distance " << lodDistances[i] << std::endl;
        File srcFile(modelNames[i]);
        SharedPtr<Model> srcModel(new Model(0, modelNames[i]));
        srcModel->load(srcFile, 0);
        srcModels.push_back(srcModel);
    }
    
    // Check that none of the models already has LOD levels
    for (unsigned i = 0; i < srcModels.size(); ++i)
    {
        for (unsigned j = 0; j < srcModels[i]->getNumGeometries(); ++j)
        {
            if (srcModels[i]->getNumGeometryLodLevels(j) > 1)
                errorExit(modelNames[i] + " already has multiple LOD levels defined");
        }
    }
    
    // Check for number of geometries (need to have same amount for now)
    for (unsigned i = 1; i < srcModels.size(); ++i)
    {
        if (srcModels[i]->getNumGeometries() != srcModels[0]->getNumGeometries())
            errorExit(modelNames[i] + " has different amount of geometries than " + modelNames[0]);
    }
    
    // If there are bones, check for compatibility (need to have exact match for now)
    for (unsigned i = 1; i < srcModels.size(); ++i)
    {
        if (srcModels[i]->getSkeleton().getNumBones() != srcModels[0]->getSkeleton().getNumBones())
            errorExit(modelNames[i] + " has different amount of bones than " + modelNames[0]);
        for (unsigned j = 0; j < srcModels[0]->getSkeleton().getNumBones(); ++j)
        {
            if (srcModels[i]->getSkeleton().getBone(j)->getName() != srcModels[0]->getSkeleton().getBone(j)->getName())
                errorExit(modelNames[i] + " has different bones than " + modelNames[0]);
        }
        if (srcModels[i]->getGeometryBoneMappings() != srcModels[0]->getGeometryBoneMappings())
            errorExit(modelNames[i] + " has different per-geometry bone mappings than " + modelNames[0]);
    }
    
    // Create the final model
    SharedPtr<Model> outModel(new Model(0, outName));
    outModel->setNumGeometries(srcModels[0]->getNumGeometries());
    for (unsigned i = 0; i < srcModels[0]->getNumGeometries(); ++i)
    {
        outModel->setNumGeometryLodLevels(i, srcModels.size());
        for (unsigned j = 0; j < srcModels.size(); ++j)
        {
            Geometry* geom = srcModels[j]->getGeometry(i, 0);
            geom->setLodDistance(lodDistances[j]);
            outModel->setGeometry(i, j, geom);
        }
    }
    outModel->setSkeleton(srcModels[0]->getSkeleton());
    outModel->setGeometryBoneMappings(srcModels[0]->getGeometryBoneMappings());
    outModel->setBoundingBox(srcModels[0]->getBoundingBox());
    outModel->setCollisionLodLevel(collisionLodLevel);
    outModel->setRaycastLodLevel(raycastLodLevel);
    outModel->setOcclusionLodLevel(occlusionLodLevel);
    //! \todo Vertex morphs are ignored for now
    
    // Save the final model
    std::cout << "Writing output model" << std::endl;
    File outFile(outName, FILE_WRITE);
    outModel->save(outFile);
}

void getMeshesUnderNode(std::vector<std::pair<aiNode*, aiMesh*> >& dest, aiNode* node)
{
    for (unsigned i = 0; i < node->mNumMeshes; ++i)
        dest.push_back(std::make_pair(node, gScene->mMeshes[node->mMeshes[i]]));
}

unsigned getMeshIndex(aiMesh* mesh)
{
    for (unsigned i = 0; i < gScene->mNumMeshes; ++i)
    {
        if (gScene->mMeshes[i] == mesh)
            return i;
    }
    return M_MAX_UNSIGNED;
}

unsigned getBoneIndex(ExportModel& model, const std::string& boneName)
{
    for (unsigned i = 0; i < model.mBones.size(); ++i)
    {
        if (toStdString(model.mBones[i]->mName) == boneName)
            return i;
    }
    return M_MAX_UNSIGNED;
}

aiBone* getMeshBone(ExportModel& model, const std::string& boneName)
{
    for (unsigned i = 0; i < model.mMeshes.size(); ++i)
    {
        aiMesh* mesh = model.mMeshes[i];
        for (unsigned j = 0; j < mesh->mNumBones; ++j)
        {
            aiBone* bone = mesh->mBones[j];
            if (toStdString(bone->mName) == boneName)
                return bone;
        }
    }
    return 0;
}

Matrix4x3 getOffsetMatrix(ExportModel& model, const std::string& boneName)
{
    for (unsigned i = 0; i < model.mMeshes.size(); ++i)
    {
        aiMesh* mesh = model.mMeshes[i];
        aiNode* node = model.mMeshNodes[i];
        for (unsigned j = 0; j < mesh->mNumBones; ++j)
        {
            aiBone* bone = mesh->mBones[j];
            if (toStdString(bone->mName) == boneName)
            {
                aiMatrix4x4 offset = bone->mOffsetMatrix;
                aiMatrix4x4 nodeDerivedInverse = getMeshBakingTransform(node, model.mRootNode);
                nodeDerivedInverse.Inverse();
                offset *= nodeDerivedInverse;
                Matrix4x3 ret;
                memcpy(&ret.m00, &offset.a1, sizeof(Matrix4x3));
                return ret;
            }
        }
    }
    return Matrix4x3::sIdentity;
}

void getBlendData(ExportModel& model, aiMesh* mesh, std::vector<unsigned>& boneMappings, std::vector<std::vector<unsigned char> >&
    blendIndices, std::vector<std::vector<float> >& blendWeights)
{
    blendIndices.resize(mesh->mNumVertices);
    blendWeights.resize(mesh->mNumVertices);
    boneMappings.clear();
    
    // If model has more bones than can fit vertex shader parameters, write the per-geometry mappings
    if (model.mBones.size() > MAX_SKIN_MATRICES)
    {
        if (mesh->mNumBones > MAX_SKIN_MATRICES)
            errorExit("Geometry has too many bone influences");
        boneMappings.resize(mesh->mNumBones);
        for (unsigned i = 0; i < mesh->mNumBones; ++i)
        {
            aiBone* bone = mesh->mBones[i];
            std::string boneName = toStdString(bone->mName);
            unsigned globalIndex = getBoneIndex(model, boneName);
            if (globalIndex == M_MAX_UNSIGNED)
                errorExit("Bone " + boneName + " not found");
            boneMappings[i] = globalIndex;
            for (unsigned j = 0; j < bone->mNumWeights; ++j)
            {
                unsigned vertex = bone->mWeights[j].mVertexId;
                blendIndices[vertex].push_back(i);
                blendWeights[vertex].push_back(bone->mWeights[j].mWeight);
                if (blendWeights[vertex].size() > 4)
                    errorExit("More than 4 bone influences on vertex");
            }
        }
    }
    else
    {
        for (unsigned i = 0; i < mesh->mNumBones; ++i)
        {
            aiBone* bone = mesh->mBones[i];
            std::string boneName = toStdString(bone->mName);
            unsigned globalIndex = getBoneIndex(model, boneName);
            if (globalIndex == M_MAX_UNSIGNED)
                errorExit("Bone " + boneName + " not found");
            for (unsigned j = 0; j < bone->mNumWeights; ++j)
            {
                unsigned vertex = bone->mWeights[j].mVertexId;
                blendIndices[vertex].push_back(globalIndex);
                blendWeights[vertex].push_back(bone->mWeights[j].mWeight);
                if (blendWeights[vertex].size() > 4)
                    errorExit("More than 4 bone influences on vertex");
            }
        }
    }
}

std::string getMeshMaterialName(aiMesh* mesh)
{
    aiMaterial* material = gScene->mMaterials[mesh->mMaterialIndex];
    aiString matNameStr;
    material->Get(AI_MATKEY_NAME, matNameStr);
    std::string matName = sanitateAssetName(toStdString(matNameStr));
    if (matName.empty())
        return matName;
    else
        return (gUseSubdirs ? "Materials/" : "") + matName + ".xml";
}

void writeShortIndices(unsigned short*& dest, aiMesh* mesh, unsigned index, unsigned offset)
{
    *dest++ = mesh->mFaces[index].mIndices[0] + offset;
    *dest++ = mesh->mFaces[index].mIndices[1] + offset;
    *dest++ = mesh->mFaces[index].mIndices[2] + offset;
}

void writeLargeIndices(unsigned*& dest, aiMesh* mesh, unsigned index, unsigned offset)
{
    *dest++ = mesh->mFaces[index].mIndices[0] + offset;
    *dest++ = mesh->mFaces[index].mIndices[1] + offset;
    *dest++ = mesh->mFaces[index].mIndices[2] + offset;
}

void writeVertex(float*& dest, aiMesh* mesh, unsigned index, unsigned elementMask, BoundingBox& box,
    const Matrix4x3& vertexTransform, const Matrix3& normalTransform, std::vector<std::vector<unsigned char> >& blendIndices,
    std::vector<std::vector<float> >& blendWeights)
{
    Vector3 vertex = vertexTransform * toVector3(mesh->mVertices[index]);
    box.merge(vertex);
    *dest++ = vertex.mX;
    *dest++ = vertex.mY;
    *dest++ = vertex.mZ;
    if (elementMask & MASK_NORMAL)
    {
        Vector3 normal = normalTransform * toVector3(mesh->mNormals[index]);
        *dest++ = normal.mX;
        *dest++ = normal.mY;
        *dest++ = normal.mZ;
    }
    if (elementMask & MASK_COLOR)
    {
        *((unsigned*)dest) = getD3DColor(Color(mesh->mColors[0][index].r, mesh->mColors[0][index].g, mesh->mColors[0][index].b,
            mesh->mColors[0][index].a));
        ++dest;
    }
    if (elementMask & MASK_TEXCOORD1)
    {
        Vector3 texCoord = toVector3(mesh->mTextureCoords[0][index]);
        *dest++ = texCoord.mX;
        *dest++ = texCoord.mY;
    }
    if (elementMask & MASK_TEXCOORD2)
    {
        Vector3 texCoord = toVector3(mesh->mTextureCoords[1][index]);
        *dest++ = texCoord.mX;
        *dest++ = texCoord.mY;
    }
    if (elementMask & MASK_TANGENT)
    {
        Vector3 tangent = normalTransform * toVector3(mesh->mTangents[index]);
        Vector3 normal = normalTransform * toVector3(mesh->mNormals[index]);
        Vector3 bitangent = normalTransform * toVector3(mesh->mBitangents[index]);
        // Check handedness
        float w = 1.0f;
        if ((tangent.crossProduct(normal)).dotProduct(bitangent) < 0.5f)
            w = -1.0f;
        
        *dest++ = tangent.mX;
        *dest++ = tangent.mY;
        *dest++ = tangent.mZ;
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

unsigned getElementMask(aiMesh* mesh)
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

aiNode* findNode(const std::string& name, aiNode* rootNode, bool caseSensitive)
{
    if (!rootNode)
        return 0;
    if (!caseSensitive)
    {
        if (toLower(toStdString(rootNode->mName)) == toLower(name))
            return rootNode;
    }
    else
    {
        if (toStdString(rootNode->mName) == name)
            return rootNode;
    }
    for (unsigned i = 0; i < rootNode->mNumChildren; ++i)
    {
        aiNode* found = findNode(name, rootNode->mChildren[i], caseSensitive);
        if (found)
            return found;
    }
    return 0;
}

aiMatrix4x4 getDerivedTransform(aiNode* node, aiNode* rootNode)
{
    return getDerivedTransform(node->mTransformation, node, rootNode);
}

aiMatrix4x4 getDerivedTransform(aiMatrix4x4 transform, aiNode* node, aiNode* rootNode)
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

aiMatrix4x4 getMeshBakingTransform(aiNode* meshNode, aiNode* modelRootNode)
{
    if (meshNode == modelRootNode)
        return aiMatrix4x4();
    else
        return getDerivedTransform(meshNode, modelRootNode);
}

void getPosRotScale(const aiMatrix4x4& transform, Vector3& pos, Quaternion& rot, Vector3& scale)
{
    aiVector3D aiPos;
    aiQuaternion aiRot;
    aiVector3D aiScale;
    transform.Decompose(aiScale, aiRot, aiPos);
    pos = toVector3(aiPos);
    rot = toQuaternion(aiRot);
    scale = toVector3(aiScale);
}


std::string toStdString(const aiString& str)
{
    if ((!str.data) || (!str.length))
        return std::string();
    else
        return std::string(str.data);
}

Vector3 toVector3(const aiVector3D& vec)
{
    return Vector3(vec.x, vec.y, vec.z);
}

Vector2 toVector2(const aiVector2D& vec)
{
    return Vector2(vec.x, vec.y);
}

Quaternion toQuaternion(const aiQuaternion& quat)
{
    return Quaternion(quat.w, quat.x, quat.y, quat.z);
}

std::string sanitateAssetName(const std::string& name)
{
    std::string fixedName = name;
    replaceInPlace(fixedName, "<", "");
    replaceInPlace(fixedName, ">", "");
    replaceInPlace(fixedName, "?", "");
    replaceInPlace(fixedName, "*", "");
    replaceInPlace(fixedName, ":", "");
    replaceInPlace(fixedName, "\"", "");
    replaceInPlace(fixedName, "/", "");
    replaceInPlace(fixedName, "\\", "");
    replaceInPlace(fixedName, "|", "");
    
    return fixedName;
}

void errorExit(const std::string& error)
{
    throw Exception(error);
}
