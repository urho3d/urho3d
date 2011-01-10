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
#include "File.h"
#include "Geometry.h"
#include "IndexBuffer.h"
#include "Model.h"
#include "Quaternion.h"
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
        mTotalIndices(0)
    {
    }
    
    std::string mOutName;
    const aiScene* mScene;
    aiNode* mRootNode;
    std::vector<aiMesh*> mMeshes;
    std::vector<aiNode*> mMeshNodes;
    unsigned mTotalVertices;
    unsigned mTotalIndices;
};

int main(int argc, char** argv);
void run(const std::vector<std::string>& arguments);
void errorExit(const std::string& error);
void exportModel(ExportModel& model);
void collectMeshes(ExportModel& model, aiNode* node);
void buildModel(ExportModel& model);
std::string toStdString(const aiString& str);
Vector3 toVector3(const aiVector3D& vec);
Vector2 toVector2(const aiVector2D& vec);
Quaternion toQuaternion(const aiQuaternion& quat);
aiMatrix4x4 getWorldTransform(aiNode* node, aiNode* baseNode);
void getPosRotScale(const aiMatrix4x4& transform, Vector3& pos, Quaternion& rot, Vector3& scale);

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
        errorExit("Usage: AssetImporter <inputfile> <outputfile>\n");
    
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(arguments[0].c_str(),
        aiProcess_ConvertToLeftHanded |
        aiProcess_JoinIdenticalVertices |
        aiProcess_Triangulate |
        aiProcess_GenSmoothNormals |
        aiProcess_LimitBoneWeights |
        aiProcess_ImproveCacheLocality |
        aiProcess_FixInfacingNormals |
        aiProcess_FindInvalidData |
        aiProcess_FindInstances |
        aiProcess_OptimizeMeshes);
    
    if (!scene)
        errorExit("Could not open input file " + arguments[0]);
    
    ExportModel model;
    model.mOutName = arguments[1];
    model.mScene = scene;
    model.mRootNode = scene->mRootNode;
    exportModel(model);
}

void exportModel(ExportModel& model)
{
    collectMeshes(model, model.mRootNode);
    buildModel(model);
}

void collectMeshes(ExportModel& model, aiNode* node)
{
    for (unsigned i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = model.mScene->mMeshes[node->mMeshes[i]];
        model.mMeshes.push_back(mesh);
        model.mMeshNodes.push_back(node);
        
        model.mTotalVertices += mesh->mNumVertices;
        model.mTotalIndices += mesh->mNumFaces * 3;
    }
    
    for (unsigned i = 0; i < node->mNumChildren; ++i)
        collectMeshes(model, node->mChildren[i]);
}

void buildModel(ExportModel& model)
{
    SharedPtr<Model> outModel(new Model(0));
    outModel->setNumGeometries(model.mMeshes.size());
    BoundingBox box;
    
    for (unsigned i = 0; i < model.mMeshes.size(); ++i)
    {
        SharedPtr<IndexBuffer> ib(new IndexBuffer(0));
        SharedPtr<VertexBuffer> vb(new VertexBuffer(0));
        SharedPtr<Geometry> geom(new Geometry());
        
        // Get the world transform of the mesh for baking into the vertices
        Vector3 pos;
        Quaternion rot;
        Vector3 scale;
        getPosRotScale(getWorldTransform(model.mMeshNodes[i], model.mRootNode), pos, rot, scale);
        Matrix4x3 vertexTransform;
        vertexTransform.define(pos, rot, scale);
        Matrix3 normalTransform = rot.getRotationMatrix();
        
        aiMesh* mesh = model.mMeshes[i];
        bool largeIndices = mesh->mNumVertices > 65535;
        unsigned elementMask = MASK_POSITION;
        if (mesh->HasNormals())
            elementMask |= MASK_NORMAL;
        //if (mesh->HasTangentsAndBitangents())
        //    elementMask |= MASK_TANGENT;
        //if (mesh->GetNumColorChannels() > 0)
        //    elementMask |= MASK_COLOR;
        if (mesh->GetNumUVChannels() > 0)
            elementMask |= MASK_TEXCOORD1;
        //if (mesh->GetNumUVChannels() > 1)
        //    elementMask |= MASK_TEXCOORD2;
        
        ib->setSize(mesh->mNumFaces * 3, largeIndices);
        vb->setSize(mesh->mNumVertices, elementMask);
        
        // Build the index data
        void* indexData = ib->lock(0, ib->getIndexCount(), LOCK_NORMAL);
        if (!largeIndices)
        {
            unsigned short* dest = (unsigned short*)indexData;
            for (unsigned j = 0; j < mesh->mNumFaces; ++j)
            {
                *dest++ = mesh->mFaces[j].mIndices[0];
                *dest++ = mesh->mFaces[j].mIndices[1];
                *dest++ = mesh->mFaces[j].mIndices[2];
            }
        }
        else
        {
            unsigned* dest = (unsigned*)indexData;
            for (unsigned j = 0; j < mesh->mNumFaces; ++j)
            {
                *dest++ = mesh->mFaces[j].mIndices[0];
                *dest++ = mesh->mFaces[j].mIndices[1];
                *dest++ = mesh->mFaces[j].mIndices[2];
            }
        }
        
        // Build the vertex data
        void* vertexData = vb->lock(0, vb->getVertexCount(), LOCK_NORMAL);
        float* dest = (float*)vertexData;
        for (unsigned j = 0; j < mesh->mNumVertices; ++j)
        {
            Vector3 vertex = vertexTransform * toVector3(mesh->mVertices[j]);
            box.merge(vertex);
            *dest++ = vertex.mX;
            *dest++ = vertex.mY;
            *dest++ = vertex.mZ;
            if (elementMask & MASK_NORMAL)
            {
                Vector3 normal = normalTransform * toVector3(mesh->mNormals[j]);
                *dest++ = normal.mX;
                *dest++ = normal.mY;
                *dest++ = normal.mZ;
            }
            if (elementMask & MASK_TEXCOORD1)
            {
                Vector3 texCoord = toVector3(mesh->mTextureCoords[0][j]);
                *dest++ = texCoord.mX;
                *dest++ = texCoord.mY;
            }
        }
        
        ib->unlock();
        vb->unlock();
        
        // Define the geometry
        geom->setIndexBuffer(ib);
        geom->setVertexBuffer(0, vb);
        geom->setDrawRange(TRIANGLE_LIST, 0, mesh->mNumFaces * 3, true);
        outModel->setNumGeometryLodLevels(i, 1);
        outModel->setGeometry(i, 0, geom);
        outModel->setBoundingBox(box);
    }
    
    File outFile(model.mOutName, FILE_WRITE);
    outModel->save(outFile);
}

void errorExit(const std::string& error)
{
    throw Exception(error);
}

std::string toStdString(const aiString& str)
{
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

aiMatrix4x4 getWorldTransform(aiNode* node, aiNode* baseNode)
{
    aiMatrix4x4 current = node->mTransformation;
    // If basenode is defined, go only up to it in the parent chain
    while ((node->mParent) && (node != baseNode))
    {
        node = node->mParent;
        current = node->mTransformation * current;
    }
    return current;
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
