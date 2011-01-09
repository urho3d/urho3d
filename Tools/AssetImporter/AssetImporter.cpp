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
#include "Quaternion.h"
#include "StringUtils.h"
#include "Vector3.h"
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

int main(int argc, char** argv);
void run(const std::vector<std::string>& arguments);
void errorExit(const std::string& error);
void processNode(const aiScene* scene, aiNode* node);
std::string toStdString(const aiString& str);
Vector3 toVector3(const aiVector3D& vec);
Vector2 toVector2(const aiVector2D& vec);
Quaternion toQuaternion(const aiQuaternion& quat);

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
    if (arguments.size() < 1)
        errorExit("Usage: AssetImporter <inputfile>\n");
    
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
    
    aiNode* rootNode = scene->mRootNode;
    if (rootNode)
        processNode(scene, rootNode);
}

void processNode(const aiScene* scene, aiNode* node)
{
    aiVector3D aiPos;
    aiQuaternion aiRot;
    aiVector3D aiScale;
    node->mTransformation.Decompose(aiScale, aiRot, aiPos);
    
    std::cout << "Node name: " << toStdString(node->mName) << std::endl;
    std::cout << "Pos: " << toString(toVector3(aiPos)) << std::endl;
    std::cout << "Rot: " << toString(toQuaternion(aiRot)) << std::endl;
    
    for (unsigned i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        std::cout << "Mesh name: " << toStdString(mesh->mName) << std::endl;
        std::cout << "Vertices: " << mesh->mNumVertices << std::endl;
        std::cout << "Faces: " << mesh->mNumFaces << std::endl;
    }
    
    for (unsigned i = 0; i < node->mNumChildren; ++i)
        processNode(scene, node->mChildren[i]);
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
