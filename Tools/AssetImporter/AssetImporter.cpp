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

#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <set>

#include <assimp.hpp>
#include <aiScene.h>
#include <aiPostProcess.h>

#include "DebugNew.h"

struct ExportModel
{
    ExportModel() :
        mTotalVertices(0),
        mTotalIndices(0),
        mRootBone(0)
    {
    }
    
    std::string mOutName;
    const aiScene* mScene;
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
    bool mLocalIDs;
    bool mNoExtensions;
    const aiScene* mScene;
    aiNode* mRootNode;
    std::vector<ExportModel> mModels;
    std::vector<aiNode*> mNodes;
    std::vector<unsigned> mNodeModelIndices;
};

int main(int argc, char** argv);
void run(const std::vector<std::string>& arguments);
void dumpNodes(const aiScene* scene, aiNode* rootNode, unsigned level);
void exportModel(const aiScene* scene, aiNode* rootNode, const std::string& outName, bool noAnimations);
void collectMeshes(ExportModel& model, aiNode* node);
void collectBones(ExportModel& model);
void collectBonesFinal(std::vector<aiNode*>& dest, const std::set<aiNode*>& necessary, aiNode* node);
void collectAnimations(ExportModel& model);
void buildBoneCollisionInfo(ExportModel& model);
void buildAndSaveModel(ExportModel& model);
void buildAndSaveAnimations(ExportModel& model);
void exportScene(const aiScene* scene, aiNode* rootNode, const std::string& outName, bool localIDs, bool noExtensions);
void collectSceneModels(ExportScene& scene, aiNode* node);
void collectSceneNodes(ExportScene& scene, aiNode* node);
void buildAndSaveScene(ExportScene& scene);
std::set<unsigned> getMeshesUnderNodeSet(aiNode* node);
std::vector<std::pair<aiNode*, aiMesh*> > getMeshesUnderNode(const aiScene* scene, aiNode* node);
unsigned getMeshIndex(const aiScene* scene, aiMesh* mesh);
unsigned getBoneIndex(ExportModel& model, const std::string& boneName);
aiBone* getMeshBone(ExportModel& model, const std::string& boneName);
void getBlendData(ExportModel& model, aiMesh* mesh, std::vector<unsigned>& boneMappings, std::vector<std::vector<unsigned char> >& blendIndices, std::vector<std::vector<float> >& blendWeights);
void writeShortIndices(unsigned short*& dest, aiMesh* mesh, unsigned index, unsigned offset);
void writeLargeIndices(unsigned*& dest, aiMesh* mesh, unsigned index, unsigned offset);
void writeVertex(float*& dest, aiMesh* mesh, unsigned index, unsigned elementMask, BoundingBox& box,
    const Matrix4x3& vertexTransform, const Matrix3& normalTransform, std::vector<std::vector<unsigned char> >& blendIndices,
    std::vector<std::vector<float> >& blendWeights);
unsigned getElementMask(aiMesh* mesh);
aiNode* findNode(const std::string& name, aiNode* rootNode, bool caseSensitive = true);
std::string toStdString(const aiString& str);
Vector3 toVector3(const aiVector3D& vec);
Vector2 toVector2(const aiVector2D& vec);
Quaternion toQuaternion(const aiQuaternion& quat);
aiMatrix4x4 getWorldTransform(aiNode* node, aiNode* rootNode);
aiMatrix4x4 getWorldTransform(aiMatrix4x4 transform, aiNode* node, aiNode* rootNode);
void getPosRotScale(const aiMatrix4x4& transform, Vector3& pos, Quaternion& rot, Vector3& scale);
void errorExit(const std::string& error);

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;
    
    for (int i = 1; i < argc; ++i)
        arguments.push_back(replace(std::string(argv[i]), '/', '\\'));
    
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
            "model     Export a model and animations. Output file is the model name\n"
            "scene     Export a scene. Output file is the scene XML file name\n"
            "dumpnodes Dump scene node structure. No output file is generated\n"
            "\n"
            "Options:\n"
            "-l        Use local ID's for scene entities\n"
            "-na       Do not export animations\n"
            "-ne       Do not create Octree & PhysicsWorld extensions to the scene\n"
            "-nm       Do not export materials\n"
            "-rX       Use scene node X as root node\n"
            "-t        Generate tangents to model(s)\n"
        );
    }
    
    std::string command = toLower(arguments[0]);
    std::string inFile = arguments[1];
    std::string outFile;
    std::string rootNodeName;
    if (arguments.size() > 2)
        outFile = arguments[2];
    
    bool noMaterials = false;
    bool noAnimations = false;
    bool noExtensions = false;
    bool localIDs = false;
    
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
    
    for (unsigned i = 3; i < arguments.size(); ++i)
    {
        if ((arguments[i].length() >= 2) && (arguments[i][0] == '-'))
        {
            std::string parameter;
            if (arguments[i].length() >= 3)
                parameter = arguments[i].substr(2);
            
            switch (tolower(arguments[i][1]))
            {
            case 't':
                flags |= aiProcess_CalcTangentSpace;
                break;
            case 'l':
                localIDs = true;
                break;
            case 'r':
                rootNodeName = parameter;
                break;
            case 'n':
                if (!parameter.empty())
                {
                    switch (tolower(parameter[0]))
                    {
                    case 'a':
                        noAnimations = true;
                        break;
                    case 'e':
                        noExtensions = true;
                        break;
                    case 'm':
                        noMaterials = true;
                        break;
                    }
                }
                break;
            }
        }
    }
    
    if ((command != "model") && (command != "scene") && (command != "dumpnodes"))
        errorExit("Unrecognized command " + command);
    
    Assimp::Importer importer;
    std::cout << "Reading file " << inFile << std::endl;
    const aiScene* scene = importer.ReadFile(inFile.c_str(), flags);
    if (!scene)
        errorExit("Could not open or parse input file " + inFile);
    
    aiNode* rootNode = scene->mRootNode;
    if (!rootNodeName.empty())
    {
        rootNode = findNode(rootNodeName, scene->mRootNode, false);
        if (!rootNode)
            errorExit("Could not find scene node " + rootNodeName);
    }
    
    if (command == "model")
        exportModel(scene, rootNode, outFile, noAnimations);
    if (command == "scene")
        exportScene(scene, rootNode, outFile, localIDs, noExtensions);
    if (command == "dumpnodes")
        dumpNodes(scene, rootNode, 0);
}

void dumpNodes(const aiScene* scene, aiNode* rootNode, unsigned level)
{
    if (!rootNode)
        return;
    
    std::string indent;
    indent.resize(level * 2);
    for (unsigned i = 0; i < level * 2; ++i)
        indent[i] = ' ';
    
    Vector3 pos, scale;
    Quaternion rot;
    getPosRotScale(rootNode->mTransformation, pos, rot, scale);
    
    std::cout << indent << "Node " << toStdString(rootNode->mName) << " pos " << toString(pos) << std::endl;
  
    if (rootNode->mNumMeshes == 1)
        std::cout << indent << "  " << rootNode->mNumMeshes << " geometry" << std::endl;
    if (rootNode->mNumMeshes > 1)
        std::cout << indent << "  " << rootNode->mNumMeshes << " geometries" << std::endl;
    
    for (unsigned i = 0; i < rootNode->mNumChildren; ++i)
        dumpNodes(scene, rootNode->mChildren[i], level + 1);
}

void exportModel(const aiScene* scene, aiNode* rootNode, const std::string& outName, bool noAnimations)
{
    if (outName.empty())
        errorExit("No output file defined");
    
    ExportModel model;
    model.mScene = scene;
    model.mRootNode = rootNode;
    model.mOutName = outName;
    
    collectMeshes(model, model.mRootNode);
    collectBones(model);
    buildBoneCollisionInfo(model);
    buildAndSaveModel(model);
    if (!noAnimations)
    {
        collectAnimations(model);
        buildAndSaveAnimations(model);
    }
}

void collectMeshes(ExportModel& model, aiNode* node)
{
    for (unsigned i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = model.mScene->mMeshes[node->mMeshes[i]];
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
            aiNode* boneNode = findNode(boneName, model.mScene->mRootNode, true);
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
            
            rootNodes.insert(rootNode);
            if (rootNodes.size() > 1)
                errorExit("Multiple skeleton root nodes found, not supported");
        }
    }
    
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
    const aiScene* scene = model.mScene;
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
}

void buildBoneCollisionInfo(ExportModel& model)
{
    for (unsigned i = 0; i < model.mMeshes.size(); ++i)
    {
        aiMesh* mesh = model.mMeshes[i];
        aiMatrix4x4 meshWorldTransform = getWorldTransform(model.mMeshNodes[i], model.mRootNode);
        for (unsigned j = 0; j < mesh->mNumBones; ++j)
        {
            aiBone* bone = mesh->mBones[j];
            std::string boneName = toStdString(bone->mName);
            unsigned boneIndex = getBoneIndex(model, boneName);
            if (boneIndex == M_MAX_UNSIGNED)
                continue;
            aiNode* boneNode = model.mBones[boneIndex];
            aiMatrix4x4 boneWorldTransform = getWorldTransform(boneNode, model.mRootNode);
            aiMatrix4x4 boneInverse = boneWorldTransform;
            boneInverse.Inverse();
            for (unsigned k = 0; k < bone->mNumWeights; ++k)
            {
                float weight = bone->mWeights[k].mWeight;
                if (weight > 0.33f)
                {
                    aiVector3D vertexWorldSpace = meshWorldTransform * mesh->mVertices[bone->mWeights[k].mVertexId];
                    aiVector3D vertexBoneSpace = boneInverse * vertexWorldSpace;
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
    
    std::cout << "Writing model from node " << rootNodeName << std::endl;
    
    if (model.mBones.size())
    {
        std::cout << "Model has a skeleton with " << model.mBones.size() << " bones, rootbone " +
            toStdString(model.mRootBone->mName) << std::endl;
    }
    
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
        std::cout << "Using separate buffers" << std::endl;
        for (unsigned i = 0; i < model.mMeshes.size(); ++i)
        {
            SharedPtr<IndexBuffer> ib(new IndexBuffer(0));
            SharedPtr<VertexBuffer> vb(new VertexBuffer(0));
            SharedPtr<Geometry> geom(new Geometry());
            // Get the world transform of the mesh for baking into the vertices
            Vector3 pos, scale;
            Quaternion rot;
            getPosRotScale(getWorldTransform(model.mMeshNodes[i], model.mRootNode), pos, rot, scale);
            Matrix4x3 vertexTransform;
            vertexTransform.define(pos, rot, scale);
            Matrix3 normalTransform = rot.getRotationMatrix();
            
            aiMesh* mesh = model.mMeshes[i];
            std::cout << "Geometry " << i << " has " << mesh->mNumVertices << " vertices " << mesh->mNumFaces * 3 << " indices"
                << std::endl;
            
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
        std::cout << "Using combined buffers" << std::endl;
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
            SharedPtr<Geometry> geom(new Geometry());
            
            // Get the world transform of the mesh for baking into the vertices
            Vector3 pos, scale;
            Quaternion rot;
            getPosRotScale(getWorldTransform(model.mMeshNodes[i], model.mRootNode), pos, rot, scale);
            Matrix4x3 vertexTransform;
            vertexTransform.define(pos, rot, scale);
            Matrix3 normalTransform = rot.getRotationMatrix();
            
            aiMesh* mesh = model.mMeshes[i];
            std::cout << "Geometry " << i << " has " << mesh->mNumVertices << " vertices " << mesh->mNumFaces * 3 << " indices"
                << std::endl;
            
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
    if (model.mBones.size())
    {
        Skeleton skeleton;
        std::vector<SharedPtr<Bone> > srcBones;
        
        for (unsigned i = 0; i < model.mBones.size(); ++i)
        {
            aiNode* boneNode = model.mBones[i];
            std::string boneName(toStdString(boneNode->mName));
            
            srcBones.push_back(SharedPtr<Bone>(new Bone(0, boneName)));
            srcBones[i]->setRootBone(srcBones[0]);
            
            aiMatrix4x4 transform;
            Vector3 pos, scale;
            Quaternion rot;
            // Make the root bone transform relative to the model's root node, if it is not already
            if (boneNode == model.mRootBone)
                transform = getWorldTransform(boneNode, model.mRootNode);
            else
                transform = boneNode->mTransformation;
            getPosRotScale(transform, pos, rot, scale);
            
            srcBones[i]->setBindTransform(pos, rot, scale);
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
        std::string animOutName = getPath(model.mOutName) + getFileName(model.mOutName) + "_" + animName + ".ani";
        
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
                    tform = getWorldTransform(tform, boneNode, model.mRootNode);
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

void exportScene(const aiScene* scene, aiNode* rootNode, const std::string& outName, bool localIDs, bool noExtensions)
{
    if (outName.empty())
        errorExit("No output file defined");
    
    ExportScene outScene;
    outScene.mOutName = outName;
    outScene.mLocalIDs = localIDs;
    outScene.mNoExtensions = noExtensions;
    outScene.mScene = scene;
    outScene.mRootNode = rootNode;
    
    collectSceneModels(outScene, rootNode);
    collectSceneNodes(outScene, rootNode);
    
    // Save models
    try
    {
        for (unsigned i = 0; i < outScene.mModels.size(); ++i)
            buildAndSaveModel(outScene.mModels[i]);
    }
    catch (...)
    {
    }
    
    // Save scene
    buildAndSaveScene(outScene);
}

void collectSceneModels(ExportScene& scene, aiNode* node)
{
    std::vector<std::pair<aiNode*, aiMesh*> > meshes = getMeshesUnderNode(scene.mScene, node);
    // If meshes encountered, do not recurse further, but build a model for export
    if (meshes.size())
    {
        ExportModel model;
        model.mScene = scene.mScene;
        model.mRootNode = node;
        model.mOutName = toStdString(node->mName) + ".mdl";
        std::cout << "Found model " << model.mOutName << std::endl;
        for (unsigned i = 0; i < meshes.size(); ++i)
        {
            aiMesh* mesh = meshes[i].second;
            unsigned meshIndex = getMeshIndex(scene.mScene, mesh);
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
                unique = false;
                break;
            }
        }
        if (unique)
        {
            collectBones(model);
            buildBoneCollisionInfo(model);
            scene.mModels.push_back(model);
        }
        return;
    }
    // If no meshes found, recurse to child nodes
    for (unsigned i = 0; i < node->mNumChildren; ++i)
        collectSceneModels(scene, node->mChildren[i]);
}

void collectSceneNodes(ExportScene& scene, aiNode* node)
{
    std::set<unsigned> meshIndices = getMeshesUnderNodeSet(node);;
    if (meshIndices.size())
    {
        // Check if a matching set of mesh indices is found from the models we are going to write (should be)
        for (unsigned i = 0; i < scene.mModels.size(); ++i)
        {
            if (scene.mModels[i].mMeshIndices == meshIndices)
            {
                std::cout << "Found node " << toStdString(node->mName) << std::endl;
                scene.mNodes.push_back(node);
                scene.mNodeModelIndices.push_back(i);
                break;
            }
        }
        return;
    }
    // If no meshes found, recurse to child nodes
    for (unsigned i = 0; i < node->mNumChildren; ++i)
        collectSceneNodes(scene, node->mChildren[i]);
}

void buildAndSaveScene(ExportScene& scene)
{
    std::cout << "Writing scene" << std::endl;
    
    SharedPtr<Scene> outScene(new Scene(0, getFileName(scene.mOutName)));
    if (!scene.mNoExtensions)
    {
        //! \todo Make the physics properties configurable
        PhysicsWorld* physicsWorld = new PhysicsWorld(outScene);
        physicsWorld->setGravity(Vector3(0.0f, -9.81f, 0.0f));
        outScene->addExtension(physicsWorld);
        
        //! \todo Make the octree properties configurable, or detect from the scene contents
        Octree* octree = new Octree(BoundingBox(-1000.0f, 1000.0f), 8, true);
        outScene->addExtension(octree);
    }
    
    for (unsigned i = 0; i < scene.mNodes.size(); ++i)
    {
        // Create a simple entity and static model component for each node
        Entity* entity = outScene->createEntity(toStdString(scene.mNodes[i]->mName), scene.mLocalIDs);
        StaticModel* staticModel = new StaticModel();
        entity->addComponent(staticModel);
        // Create a dummy model so that the reference can be stored
        SharedPtr<Model> dummyModel(new Model(0, scene.mModels[scene.mNodeModelIndices[i]].mOutName));
        staticModel->setModel(dummyModel);
        // Set a flattened transform
        Vector3 pos, scale;
        Quaternion rot;
        getPosRotScale(getWorldTransform(scene.mNodes[i], 0), pos, rot, scale);
        staticModel->setTransform(pos, rot, scale);
    }
    
    File file(scene.mOutName, FILE_WRITE);
    outScene->saveXML(file);
}

std::set<unsigned> getMeshesUnderNodeSet(aiNode* node)
{
    std::set<unsigned> ret;
    
    // Do not check this model directly, but rather check if there are meshes in the immediate children
    for (unsigned i = 0; i < node->mNumChildren; ++i)
    {
        aiNode* childNode = node->mChildren[i];
        for (unsigned j = 0; j < childNode->mNumMeshes; ++j)
            ret.insert(childNode->mMeshes[j]);
    }
    
    return ret;
}

std::vector<std::pair<aiNode*, aiMesh*> > getMeshesUnderNode(const aiScene* scene, aiNode* node)
{
    std::vector<std::pair<aiNode*, aiMesh*> > ret;
    
    // Do not check this model directly, but rather check if there are meshes in the immediate children
    for (unsigned i = 0; i < node->mNumChildren; ++i)
    {
        aiNode* childNode = node->mChildren[i];
        for (unsigned j = 0; j < childNode->mNumMeshes; ++j)
            ret.push_back(std::make_pair(childNode, scene->mMeshes[childNode->mMeshes[j]]));
    }
    
    return ret;
}

unsigned getMeshIndex(const aiScene* scene, aiMesh* mesh)
{
    for (unsigned i = 0; i < scene->mNumMeshes; ++i)
    {
        if (scene->mMeshes[i] == mesh)
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

aiMatrix4x4 getWorldTransform(aiNode* node, aiNode* rootNode)
{
    aiMatrix4x4 current = node->mTransformation;
    // If basenode is defined, go only up to it in the parent chain
    while ((node->mParent) && (node != rootNode))
    {
        node = node->mParent;
        current = node->mTransformation * current;
    }
    return current;
}

aiMatrix4x4 getWorldTransform(aiMatrix4x4 transform, aiNode* node, aiNode* rootNode)
{
    // If basenode is defined, go only up to it in the parent chain
    while ((node->mParent) && (node != rootNode))
    {
        node = node->mParent;
        transform = node->mTransformation * transform;
    }
    return transform;
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

void errorExit(const std::string& error)
{
    throw Exception(error);
}

