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
#include "ModelConverterUtils.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <set>

#include "DebugNew.h"

static const unsigned VERTEX_CACHE_SIZE = 32;

std::vector<ModelIndexBuffer> indexBuffers;
std::vector<ModelVertexBuffer> vertexBuffers;
std::vector<std::vector<ModelSubGeometryLodLevel> > subGeometries;
std::vector<ModelBone> bones;
std::vector<ModelMorph> morphs;
BoundingBox box;
unsigned numSubMeshes = 0;
unsigned collisionLodLevel = M_MAX_UNSIGNED;
unsigned raycastLodLevel = M_MAX_UNSIGNED;
unsigned occlusionLodLevel = M_MAX_UNSIGNED;
bool useOneBuffer = true;

XMLFile meshFile;
XMLFile skelFile;

int main(int argc, char** argv);
void run(const std::vector<std::string>& arguments);
void loadSkeleton(const std::string& inputFileName);
void loadMesh(const std::string& inputFileName, bool generateTangents, bool splitSubMeshes, bool getMorphs);
void writeOutput(const std::string& outputFileName, bool exportAnimations, bool rotationsOnly);
void optimizeIndices(ModelSubGeometryLodLevel* subGeom, ModelVertexBuffer* vb, ModelIndexBuffer* ib);
void calculateScore(ModelVertex& vertex);
void errorExit(const std::string& error);

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;
    
    for (int i = 1; i < argc; ++i)
        arguments.push_back(std::string(argv[i]));
    
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
        errorExit("Usage: ModelConverter <input file> <output file> [options]\n"
                  "Options:\n"
                  "-a   Export animations\n"
                  "-lcX Use LOD level X for collision mesh, default middle LOD\n"
                  "-lrX Use LOD level X for raycasts, default same as visible LOD\n"
                  "-loX Use LOD level X for occlusion, default same as visible LOD\n"
                  "-m   Export morphs\n"
                  "-r   Export only rotations from animations\n"
                  "-s   Split each submesh into own vertex buffer\n"
                  "-t   Generate tangents\n");
    }
    
    bool generateTangents = false;
    bool getMorphs = false;
    bool splitSubMeshes = false;
    bool exportAnimations = false;
    bool rotationsOnly = false;
    
    if (arguments.size() > 2)
    {
        for (unsigned i = 2; i < arguments.size(); ++i)
        {
            if (arguments[i][0] == '-')
            {
                std::string arg = toLower(arguments[i].substr(1));
                switch (arg[0])
                {
                case 't':
                    generateTangents = true;
                    break;
                    
                case 'a':
                    exportAnimations = true;
                    break;
                    
                case 'r':
                    rotationsOnly = true;
                    break;
                    
                case 'm':
                    getMorphs = true;
                    break;
                    
                case 's':
                    splitSubMeshes = true;
                    break;
                    
                case 'l':
                    switch (arg[1])
                    {
                    case 'c':
                        collisionLodLevel = toInt(arg.substr(2));
                        break;
                        
                    case 'r':
                        raycastLodLevel = toInt(arg.substr(2));
                        break;
                        
                    case 'o':
                        occlusionLodLevel = toInt(arg.substr(2));
                        break;
                    }
                    break;
                }
            }
        }
    }
    
    loadSkeleton(arguments[0]);
    loadMesh(arguments[0], generateTangents, splitSubMeshes, getMorphs);
    writeOutput(arguments[1], exportAnimations, rotationsOnly);
    
    std::cout << "Finished" << std::endl;
}

void loadSkeleton(const std::string& inputFileName)
{
    // Process skeleton first (if found)
    XMLElement skeletonRoot;
    std::string skeletonFileName = replace(inputFileName, ".mesh.xml", ".skeleton.xml");
    try
    {
        File skeletonFileSource(skeletonFileName);
        skelFile.load(skeletonFileSource);
        skeletonRoot = skelFile.getRootElement();
    }
    catch (...)
    {
    }
    
    if (skeletonRoot.notNull())
    {
        XMLElement bonesRoot = skeletonRoot.getChildElement("bones", false);
        XMLElement bone = bonesRoot.getChildElement("bone", false);
        while (bone.notNull())
        {
            unsigned index = bone.getInt("id");
            std::string name = bone.getString("name");
            if (index >= bones.size())
                bones.resize(index + 1);
            
            // Convert from right- to left-handed
            XMLElement position = bone.getChildElement("position");
            float x = position.getFloat("x");
            float y = position.getFloat("y");
            float z = position.getFloat("z");
            Vector3 pos(x, y, -z);
            
            XMLElement rotation = bone.getChildElement("rotation");
            XMLElement axis = rotation.getChildElement("axis");
            float angle = -rotation.getFloat("angle") * M_RADTODEG;
            x = axis.getFloat("x");
            y = axis.getFloat("y");
            z = axis.getFloat("z");
            Vector3 axisVec(x, y, -z);
            Quaternion rot(angle, axisVec);
            
            bones[index].mName = name;
            bones[index].mParentIndex = index; // Fill in the correct parent later
            bones[index].mBindPosition = pos;
            bones[index].mBindRotation = rot;
            bones[index].mBindScale = Vector3::sUnity;
            bones[index].mCollisionMask = 0;
            bones[index].mRadius = 0.0f;
            
            bone = bone.getNextElement("bone");
        }
        
        // Go through the bone hierarchy
        XMLElement boneHierarchy = skeletonRoot.getChildElement("bonehierarchy");
        XMLElement boneParent = boneHierarchy.getChildElement("boneparent", false);
        while (boneParent.notNull())
        {
            std::string bone = boneParent.getString("bone");
            std::string parent = boneParent.getString("parent");
            unsigned i, j;
            for (i = 0; (i < bones.size()) && (bones[i].mName != bone); ++i)
            for (j = 0; (j < bones.size()) && (bones[j].mName != parent); ++j)
            
            if ((i >= bones.size()) || (j >= bones.size()))
                errorExit("Found indeterminate parent bone assignment");
            bones[i].mParentIndex = j;
            
            boneParent = boneParent.getNextElement("boneparent");
        }
        
        // Calculate bone derived positions
        for (unsigned i = 0; i < bones.size(); ++i)
        {
            Vector3 derivedPosition = bones[i].mBindPosition;
            Quaternion derivedRotation = bones[i].mBindRotation;
            Vector3 derivedScale = bones[i].mBindScale;
            
            unsigned index = bones[i].mParentIndex;
            if (index != i)
            {
                for (;;)
                {
                    derivedPosition = bones[index].mBindPosition + (bones[index].mBindRotation * (bones[index].mBindScale * derivedPosition));
                    derivedRotation = bones[index].mBindRotation * derivedRotation;
                    derivedScale = bones[index].mBindScale * derivedScale;
                    if (bones[index].mParentIndex != index)
                        index = bones[index].mParentIndex;
                    else
                        break;
                }
            }
            
            bones[i].mDerivedPosition = derivedPosition;
            bones[i].mDerivedRotation = derivedRotation;
            bones[i].mDerivedScale = derivedScale;
            bones[i].mWorldTransform.define(derivedPosition, derivedRotation, derivedScale);
            bones[i].mInverseWorldTransform = bones[i].mWorldTransform.getInverse();
        }
        
        std::cout << "Processed skeleton" << std::endl;
    }
}

void loadMesh(const std::string& inputFileName, bool generateTangents, bool splitSubMeshes, bool getMorphs)
{
    File meshFileSource(inputFileName);
    meshFile.load(meshFileSource);
    
    XMLElement root = meshFile.getRootElement();
    XMLElement subMeshes = root.getChildElement("submeshes");
    
    // Check whether there's benefit of avoiding 32bit indices by splitting each submesh into own buffer
    XMLElement subMesh = subMeshes.getChildElement("submesh");
    unsigned totalVertices = 0;
    unsigned maxSubMeshVertices = 0;
    while (subMesh.notNull())
    {
        XMLElement geometry = subMesh.getChildElement("geometry", false);
        if (geometry.notNull())
        {
            unsigned vertices = geometry.getInt("vertexcount");
            totalVertices += vertices;
            if (maxSubMeshVertices < vertices)
                maxSubMeshVertices = vertices;
        }
        ++numSubMeshes;
        
        subMesh = subMesh.getNextElement("submesh");
    }
    
    XMLElement sharedGeometry = root.getChildElement("sharedgeometry", false);
    if (sharedGeometry.notNull())
    {
        unsigned vertices = sharedGeometry.getInt("vertexcount");
        totalVertices += vertices;
        if (maxSubMeshVertices < vertices)
            maxSubMeshVertices = vertices;
    }
    
    if ((splitSubMeshes) || ((totalVertices > 65535) && (maxSubMeshVertices <= 65535)))
    {
        useOneBuffer = false;
        vertexBuffers.resize(numSubMeshes);
        indexBuffers.resize(numSubMeshes);
    }
    else
    {
        vertexBuffers.resize(1);
        indexBuffers.resize(1);
    }
    
    subMesh = subMeshes.getChildElement("submesh");
    unsigned indexStart = 0;
    unsigned vertexStart = 0;
    unsigned subMeshIndex = 0;
    
    std::vector<unsigned> vertexStarts;
    vertexStarts.resize(numSubMeshes);
    
    while (subMesh.notNull())
    {
        XMLElement geometry = subMesh.getChildElement("geometry", false);
        XMLElement faces = subMesh.getChildElement("faces");
        
        // If no submesh vertexbuffer, process the shared geometry, but do it only once
        unsigned vertices = 0;
        if (!geometry)
        {
            vertexStart = 0;
            if (!subMeshIndex)
                geometry = root.getChildElement("sharedgeometry");
        }
        
        if (geometry.notNull())
            vertices = geometry.getInt("vertexcount");
        
        ModelSubGeometryLodLevel subGeometryLodLevel;
        ModelVertexBuffer* vBuf;
        ModelIndexBuffer* iBuf;
        
        if (useOneBuffer)
        {
            vBuf = &vertexBuffers[0];
            if (vertices)
                vBuf->mVertices.resize(vertexStart + vertices);
            iBuf = &indexBuffers[0];
            
            subGeometryLodLevel.mVertexBuffer = 0;
            subGeometryLodLevel.mIndexBuffer = 0;
        }
        else
        {
            vertexStart = 0;
            indexStart = 0;
            
            vBuf = &vertexBuffers[subMeshIndex];
            vBuf->mVertices.resize(vertices);
            iBuf = &indexBuffers[subMeshIndex];
            
            subGeometryLodLevel.mVertexBuffer = subMeshIndex;
            subGeometryLodLevel.mIndexBuffer = subMeshIndex;
        }
        
        // Store the start vertex for later use
        vertexStarts[subMeshIndex] = vertexStart;
        
        // Ogre may have multiple buffers in one submesh. These will be merged into one
        XMLElement bufferDef;
        if (geometry)
            bufferDef = geometry.getChildElement("vertexbuffer");
        
        while (bufferDef.notNull())
        {
            if (bufferDef.hasAttribute("positions"))
                vBuf->mElementMask |= MASK_POSITION;
            if (bufferDef.hasAttribute("normals"))
                vBuf->mElementMask |= MASK_NORMAL;
            if (bufferDef.hasAttribute("texture_coords"))
                vBuf->mElementMask |= MASK_TEXCOORD1;
            
            unsigned vertexNum = vertexStart;
            if (vertices)
            {
                XMLElement vertex = bufferDef.getChildElement("vertex");
                while (vertex)
                {
                    XMLElement position = vertex.getChildElement("position", false);
                    if (position.notNull())
                    {
                        // Convert from right- to left-handed
                        float x = position.getFloat("x");
                        float y = position.getFloat("y");
                        float z = position.getFloat("z");
                        Vector3 vec(x, y, -z);
                        
                        vBuf->mVertices[vertexNum].mPosition = vec;
                        box.merge(vec);
                    }
                    XMLElement normal = vertex.getChildElement("normal", false);
                    if (normal.notNull())
                    {
                        // Convert from right- to left-handed
                        float x = normal.getFloat("x");
                        float y = normal.getFloat("y");
                        float z = normal.getFloat("z");
                        Vector3 vec(x, y, -z);
                        
                        vBuf->mVertices[vertexNum].mNormal = vec;
                    }
                    XMLElement uv = vertex.getChildElement("texcoord", false);
                    if (uv.notNull())
                    {
                        float x = uv.getFloat("u");
                        float y = uv.getFloat("v");
                        Vector2 vec(x, y);
                        
                        vBuf->mVertices[vertexNum].mTexCoord1 = vec;
                    }
                    
                    vertexNum++;
                    vertex = vertex.getNextElement("vertex");
                }
            }
            
            bufferDef = bufferDef.getNextElement("vertexbuffer");
        }
        
        unsigned triangles = faces.getInt("count");
        unsigned indices = triangles * 3;
        
        XMLElement triangle = faces.getChildElement("face");
        while (triangle)
        {
            unsigned v1 = triangle.getInt("v1");
            unsigned v2 = triangle.getInt("v2");
            unsigned v3 = triangle.getInt("v3");
            iBuf->mIndices.push_back(v3 + vertexStart);
            iBuf->mIndices.push_back(v2 + vertexStart);
            iBuf->mIndices.push_back(v1 + vertexStart);
            triangle = triangle.getNextElement("face");
        }
        
        subGeometryLodLevel.mIndexStart = indexStart;
        subGeometryLodLevel.mIndexCount = indices;
        if (vertexStart + vertices > 65535)
            iBuf->mIndexSize = sizeof(unsigned);
        
        if (bones.size())
        {
            XMLElement boneAssignments = subMesh.getChildElement("boneassignments", false);
            if (boneAssignments)
            {
                XMLElement boneAssignment = boneAssignments.getChildElement("vertexboneassignment", false);
                while (boneAssignment)
                {
                    unsigned vertex = boneAssignment.getInt("vertexindex") + vertexStart;
                    unsigned bone = boneAssignment.getInt("boneindex");
                    float weight = boneAssignment.getFloat("weight");
                    
                    BoneWeightAssignment assign;
                    assign.mBoneIndex = bone;
                    assign.mWeight = weight;
                    // Source data might have 0 weights. Disregard these
                    if (assign.mWeight > 0.0f)
                    {
                        subGeometryLodLevel.mBoneWeights[vertex].push_back(assign);
                        
                        if (assign.mWeight > 0.33f)
                        {
                            // Check distance of vertex from bone to get bone max. radius information
                            Vector3 bonePos = bones[bone].mDerivedPosition;
                            Vector3 vertexPos = vBuf->mVertices[vertex].mPosition;
                            float distance = (bonePos - vertexPos).getLength();
                            if (distance > bones[bone].mRadius)
                            {
                                bones[bone].mCollisionMask |= 1;
                                bones[bone].mRadius = distance;
                            }
                            // Build the hitbox for the bone
                            bones[bone].mBoundingBox.merge(bones[bone].mInverseWorldTransform * (vertexPos));
                            bones[bone].mCollisionMask |= 2;
                        }
                    }
                    boneAssignment = boneAssignment.getNextElement("vertexboneassignment");
                }
            }
            
            if ((subGeometryLodLevel.mBoneWeights.size()) && bones.size())
            {
                vBuf->mElementMask |= MASK_BLENDWEIGHTS | MASK_BLENDINDICES;
                bool sorted = false;
                
                // If amount of bones is larger than supported by HW skinning, must remap per submesh
                if (bones.size() > MAX_SKIN_MATRICES)
                {
                    std::map<unsigned, unsigned> usedBoneMap;
                    unsigned remapIndex = 0;
                    for (std::map<unsigned, std::vector<BoneWeightAssignment> >::iterator i =
                        subGeometryLodLevel.mBoneWeights.begin(); i != subGeometryLodLevel.mBoneWeights.end(); ++i)
                    {
                        // Sort the bone assigns by weight
                        std::sort(i->second.begin(), i->second.end(), compareWeights);
                        
                        // Use only the first 4 weights
                        for (unsigned j = 0; j < i->second.size() && j < 4; ++j)
                        {
                            unsigned originalIndex = i->second[j].mBoneIndex;
                            if (usedBoneMap.find(originalIndex) == usedBoneMap.end())
                            {
                                usedBoneMap[originalIndex] = remapIndex;
                                remapIndex++;
                            }
                            i->second[j].mBoneIndex = usedBoneMap[originalIndex];
                        }
                    }
                    
                    // If still too many bones in one subgeometry, error
                    if (usedBoneMap.size() > MAX_SKIN_MATRICES)
                        errorExit("Too many bones in submesh " + toString(subMeshIndex + 1));
                    
                    // Write mapping of vertex buffer bone indices to original bone indices
                    subGeometryLodLevel.mBoneMapping.resize(usedBoneMap.size());
                    for (std::map<unsigned, unsigned>::iterator j = usedBoneMap.begin(); j != usedBoneMap.end(); ++j)
                        subGeometryLodLevel.mBoneMapping[j->second] = j->first;
                    
                    sorted = true;
                }
                
                for (std::map<unsigned, std::vector<BoneWeightAssignment> >::iterator i = subGeometryLodLevel.mBoneWeights.begin();
                    i != subGeometryLodLevel.mBoneWeights.end(); ++i)
                {
                    // Sort the bone assigns by weight, if not sorted yet in bone remapping pass
                    if (!sorted)
                        std::sort(i->second.begin(), i->second.end(), compareWeights);
                    
                    float totalWeight = 0.0f;
                    float normalizationFactor = 0.0f;
                    
                    // Calculate normalization factor in case there are more than 4 blend weights, or they do not add up to 1
                    for (unsigned j = 0; j < i->second.size() && j < 4; ++j)
                        totalWeight += i->second[j].mWeight;
                    if (totalWeight > 0.0f)
                        normalizationFactor = 1.0f / totalWeight;
                    
                    for (unsigned j = 0; j < i->second.size() && j < 4; ++j)
                    {
                        vBuf->mVertices[i->first].mBlendIndices[j] = i->second[j].mBoneIndex;
                        vBuf->mVertices[i->first].mBlendWeights[j] = i->second[j].mWeight * normalizationFactor;
                    }
                    
                    // If there are less than 4 blend weights, fill rest with zero
                    for (unsigned j = i->second.size(); j < 4; ++j)
                    {
                        vBuf->mVertices[i->first].mBlendIndices[j] = 0;
                        vBuf->mVertices[i->first].mBlendWeights[j] = 0.0f;
                    }
                    
                    vBuf->mVertices[i->first].mHasBlendWeights = true;
                }
            }
        }
        else
            std::cout << "No skeleton loaded, skipping skinning information" << std::endl;
        
        indexStart += indices;
        vertexStart += vertices;
        
        optimizeIndices(&subGeometryLodLevel, vBuf, iBuf);
        
        std::cout << "Processed submesh " << subMeshIndex + 1 << ": " << vertices << " vertices " << triangles << " triangles" << std::endl;
        std::vector<ModelSubGeometryLodLevel> thisSubGeometry;
        thisSubGeometry.push_back(subGeometryLodLevel);
        subGeometries.push_back(thisSubGeometry);
        
        subMesh = subMesh.getNextElement("submesh");
        subMeshIndex++;
    }
    
    // Process LOD levels, if any
    XMLElement lods = root.getChildElement("levelofdetail", false);
    if (lods.notNull())
    {
        try
        {
            // For now, support only generated LODs, where the vertices are the same
            XMLElement lod = lods.getChildElement("lodgenerated", false);
            while (lod.notNull())
            {
                float distance = M_EPSILON;
                if (lod.hasAttribute("fromdepthsquared"))
                    distance = sqrtf(lod.getFloat("fromdepthsquared"));
                if (lod.hasAttribute("value"))
                    distance = lod.getFloat("value");
                XMLElement lodSubMesh = lod.getChildElement("lodfacelist", false);
                while (lodSubMesh.notNull())
                {
                    unsigned subMeshIndex = lodSubMesh.getInt("submeshindex");
                    unsigned triangles = lodSubMesh.getInt("numfaces");
                    
                    ModelSubGeometryLodLevel newLodLevel;
                    ModelSubGeometryLodLevel& originalLodLevel = subGeometries[subMeshIndex][0];
                    
                    // Copy all initial values
                    newLodLevel = originalLodLevel;
                    
                    ModelVertexBuffer* vBuf;
                    ModelIndexBuffer* iBuf;
                    
                    if (useOneBuffer)
                    {
                        vBuf = &vertexBuffers[0];
                        iBuf = &indexBuffers[0];
                    }
                    else
                    {
                        vBuf = &vertexBuffers[subMeshIndex];
                        iBuf = &indexBuffers[subMeshIndex];
                    }
                    
                    unsigned indexStart = iBuf->mIndices.size();
                    unsigned indexCount = triangles * 3;
                    unsigned vertexStart = vertexStarts[subMeshIndex];
                    
                    newLodLevel.mDistance = distance;
                    newLodLevel.mIndexStart = indexStart;
                    newLodLevel.mIndexCount = indexCount;
                    
                    // Append indices to the original index buffer
                    XMLElement triangle = lodSubMesh.getChildElement("face");
                    while (triangle.notNull())
                    {
                        unsigned v1 = triangle.getInt("v1");
                        unsigned v2 = triangle.getInt("v2");
                        unsigned v3 = triangle.getInt("v3");
                        iBuf->mIndices.push_back(v3 + vertexStart);
                        iBuf->mIndices.push_back(v2 + vertexStart);
                        iBuf->mIndices.push_back(v1 + vertexStart);
                        triangle = triangle.getNextElement("face");
                    }
                    
                    optimizeIndices(&newLodLevel, vBuf, iBuf);
                    
                    subGeometries[subMeshIndex].push_back(newLodLevel);
                    std::cout << "Processed LOD level for submesh " << subMeshIndex + 1 << ": distance " << distance << std::endl;
                    
                    lodSubMesh = lodSubMesh.getNextElement("lodfacelist");
                }
                lod = lod.getNextElement("lodgenerated");
            }
        }
        catch (...) {}
    }
    
    // Process poses/morphs
    // First find out all pose definitions
    if (getMorphs)
    {
        try
        {
            std::vector<XMLElement> poses;
            XMLElement posesRoot = root.getChildElement("poses", false);
            if (posesRoot.notNull())
            {
                XMLElement pose = posesRoot.getChildElement("pose", false);
                while (pose)
                {
                    poses.push_back(pose);
                    pose = pose.getNextElement("pose");
                }
            }
            
            // Then process animations using the poses
            XMLElement animsRoot = root.getChildElement("animations", false);
            if (animsRoot.notNull())
            {
                XMLElement anim = animsRoot.getChildElement("animation", false);
                while (anim.notNull())
                {
                    std::string name = anim.getString("name");
                    float length = anim.getFloat("length");
                    std::set<unsigned> usedPoses;
                    XMLElement tracks = anim.getChildElement("tracks", false);
                    if (tracks.notNull())
                    {
                        XMLElement track = tracks.getChildElement("track", false);
                        while (track.notNull())
                        {
                            XMLElement keyframes = track.getChildElement("keyframes", false);
                            if (keyframes.notNull())
                            {
                                XMLElement keyframe = keyframes.getChildElement("keyframe", false);
                                while (keyframe.notNull())
                                {
                                    float time = keyframe.getFloat("time");
                                    XMLElement poseref = keyframe.getChildElement("poseref", false);
                                    // Get only the end pose
                                    if ((poseref) && (time == length))
                                        usedPoses.insert(poseref.getInt("poseindex"));
                                    
                                    keyframe = keyframe.getNextElement("keyframe");
                                }
                            }
                            track = track.getNextElement("track");
                        }
                    }
                    
                    if (usedPoses.size())
                    {
                        ModelMorph newMorph;
                        newMorph.mName = name;
                        
                        if (useOneBuffer)
                            newMorph.mBuffers.resize(1);
                        else
                            newMorph.mBuffers.resize(usedPoses.size());
                        
                        unsigned bufIndex = 0;
                        
                        for (std::set<unsigned>::iterator i = usedPoses.begin(); i != usedPoses.end(); ++i)
                        {
                            XMLElement pose = poses[*i];
                            unsigned targetSubMesh = pose.getInt("index");
                            XMLElement poseOffset = pose.getChildElement("poseoffset", false);
                        
                            if (useOneBuffer)
                                newMorph.mBuffers[bufIndex].mVertexBuffer = 0;
                            else
                                newMorph.mBuffers[bufIndex].mVertexBuffer = targetSubMesh;
                            
                            newMorph.mBuffers[bufIndex].mElementMask = MASK_POSITION;
                            
                            ModelVertexBuffer* vBuf = &vertexBuffers[newMorph.mBuffers[bufIndex].mVertexBuffer];
                            
                            while (poseOffset.notNull())
                            {
                                // Convert from right- to left-handed
                                unsigned vertexIndex = poseOffset.getInt("index") + vertexStarts[targetSubMesh];
                                float x = poseOffset.getFloat("x");
                                float y = poseOffset.getFloat("y");
                                float z = poseOffset.getFloat("z");
                                Vector3 vec(x, y, -z);
                                
                                if (vBuf->mMorphCount == 0)
                                {
                                    vBuf->mMorphStart = vertexIndex;
                                    vBuf->mMorphCount = 1;
                                }
                                else
                                {
                                    unsigned first = vBuf->mMorphStart;
                                    unsigned last = first + vBuf->mMorphCount - 1;
                                    if (vertexIndex < first)
                                        first = vertexIndex;
                                    if (vertexIndex > last)
                                        last = vertexIndex;
                                    vBuf->mMorphStart = first;
                                    vBuf->mMorphCount = last - first + 1;
                                }
                                
                                ModelVertex newVertex;
                                newVertex.mPosition = vec;
                                newMorph.mBuffers[bufIndex].mVertices[vertexIndex] = newVertex;
                                poseOffset = poseOffset.getNextElement("poseoffset");
                            }
                            
                            if (!useOneBuffer)
                                ++bufIndex;
                        }
                        morphs.push_back(newMorph);
                        std::cout << "Processed morph " << name << " with " << usedPoses.size() << " sub-poses" << std::endl;
                    }
                    
                    anim = anim.getNextElement("animation");
                }
            }
        }
        catch (...) {}
    }
    
    // Check any of the buffers for vertices with missing blend weight assignments
    for (unsigned i = 0; i < vertexBuffers.size(); ++i)
    {
        if (vertexBuffers[i].mElementMask & MASK_BLENDWEIGHTS)
        {
            for (unsigned j = 0; j < vertexBuffers[i].mVertices.size(); ++j)
                if (!vertexBuffers[i].mVertices[j].mHasBlendWeights)
                    errorExit("Found a vertex with missing skinning information");
        }
    }
    
    // Tangent generation
    if (generateTangents)
    {
        for (unsigned i = 0; i < subGeometries.size(); ++i)
        {
            for (unsigned j = 0; j < subGeometries[i].size(); ++j)
            {
                ModelVertexBuffer& vBuf = vertexBuffers[subGeometries[i][j].mVertexBuffer];
                ModelIndexBuffer& iBuf = indexBuffers[subGeometries[i][j].mIndexBuffer];
                unsigned indexStart = subGeometries[i][j].mIndexStart;
                unsigned indexCount = subGeometries[i][j].mIndexCount;
                unsigned vertexCount = vBuf.mVertices.size();
                
                // If already has tangents, do not regenerate
                if (vBuf.mElementMask & MASK_TANGENT)
                    continue;
                
                vBuf.mElementMask |= MASK_TANGENT;
                
                // Tangent generation from
                // http://www.terathon.com/code/tangent.html
                Vector3 *tan1 = new Vector3[vertexCount * 2];
                Vector3 *tan2 = tan1 + vertexCount;
                memset(tan1, 0, sizeof(Vector3) * vertexCount * 2);
                
                if ((vBuf.mElementMask & (MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1)) != (MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1))
                    errorExit("To generate tangents, positions normals and texcoords are required");
                
                unsigned minVertex = M_MAX_UNSIGNED;
                unsigned maxVertex = 0;
                
                for (unsigned a = indexStart; a < indexStart + indexCount; ++a)
                {
                    if (iBuf.mIndices[a] < minVertex)
                        minVertex = iBuf.mIndices[a];
                    if (iBuf.mIndices[a] > maxVertex)
                        maxVertex = iBuf.mIndices[a];
                }
                
                for (unsigned a = indexStart; a < indexStart + indexCount; a += 3)
                {
                    unsigned i1 = iBuf.mIndices[a+0];
                    unsigned i2 = iBuf.mIndices[a+1];
                    unsigned i3 = iBuf.mIndices[a+2];
                    
                    const Vector3& v1 = vBuf.mVertices[i1].mPosition;
                    const Vector3& v2 = vBuf.mVertices[i2].mPosition;
                    const Vector3& v3 = vBuf.mVertices[i3].mPosition;
                    
                    const Vector2& w1 = vBuf.mVertices[i1].mTexCoord1;
                    const Vector2& w2 = vBuf.mVertices[i2].mTexCoord1;
                    const Vector2& w3 = vBuf.mVertices[i3].mTexCoord1;
                    
                    float x1 = v2.mX - v1.mX;
                    float x2 = v3.mX - v1.mX;
                    float y1 = v2.mY - v1.mY;
                    float y2 = v3.mY - v1.mY;
                    float z1 = v2.mZ - v1.mZ;
                    float z2 = v3.mZ - v1.mZ;
                    
                    float s1 = w2.mX - w1.mX;
                    float s2 = w3.mX - w1.mX;
                    float t1 = w2.mY - w1.mY;
                    float t2 = w3.mY - w1.mY;
                    
                    float r = 1.0f / (s1 * t2 - s2 * t1);
                    Vector3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
                            (t2 * z1 - t1 * z2) * r);
                    Vector3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
                            (s1 * z2 - s2 * z1) * r);
                    
                    tan1[i1] += sdir;
                    tan1[i2] += sdir;
                    tan1[i3] += sdir;
                    
                    tan2[i1] += tdir;
                    tan2[i2] += tdir;
                    tan2[i3] += tdir;
                }
                
                for (unsigned a = minVertex; a <= maxVertex; a++)
                {
                    const Vector3& n = vBuf.mVertices[a].mNormal;
                    const Vector3& t = tan1[a];
                    Vector3 xyz;
                    float w;
                    
                    // Gram-Schmidt orthogonalize
                    xyz = (t - n * n.dotProduct(t)).getNormalized();
                    
                    // Calculate handedness
                    w = n.crossProduct(t).dotProduct(tan2[a]) < 0.0f ? -1.0f : 1.0f;
                    
                    vBuf.mVertices[a].mTangent = Vector4(xyz, w);
                }
                
                delete[] tan1;
                
                std::cout << "Generated tangents" << std::endl;
            }
        }
    }
}

void writeOutput(const std::string& outputFileName, bool exportAnimations, bool rotationsOnly)
{
    // Begin serialization
    File dest(outputFileName, FILE_WRITE);
    
    // Vertexbuffers
    dest.writeUInt(vertexBuffers.size());
    for (unsigned i = 0; i < vertexBuffers.size(); ++i)
        vertexBuffers[i].writeData(dest);
    
    // Indexbuffers
    dest.writeUInt(indexBuffers.size());
    for (unsigned i = 0; i < indexBuffers.size(); ++i)
        indexBuffers[i].writeData(dest);
    
    // Subgeometries
    dest.writeUInt(subGeometries.size());
    for (unsigned i = 0; i < subGeometries.size(); ++i)
    {
        // Write bone mapping info from the first LOD level. It does not change for further LODs
        dest.writeUInt(subGeometries[i][0].mBoneMapping.size());
        for (unsigned k = 0; k < subGeometries[i][0].mBoneMapping.size(); ++k)
            dest.writeUInt(subGeometries[i][0].mBoneMapping[k]);
        
        // Lod levels for this subgeometry
        dest.writeUInt(subGeometries[i].size());
        for (unsigned j = 0; j < subGeometries[i].size(); ++j)
        {
            dest.writeFloat(subGeometries[i][j].mDistance);
            dest.writeUInt((unsigned)subGeometries[i][j].mPrimitiveType);
            dest.writeUInt(subGeometries[i][j].mVertexBuffer);
            dest.writeUInt(subGeometries[i][j].mIndexBuffer);
            dest.writeUInt(subGeometries[i][j].mIndexStart);
            dest.writeUInt(subGeometries[i][j].mIndexCount);
        }
    }
    
    // Morphs
    dest.writeUInt(morphs.size());
    for (unsigned i = 0; i < morphs.size(); ++i)
        morphs[i].writeData(dest);
    
    // Skeleton
    dest.writeUInt(bones.size());
    for (unsigned i = 0; i < bones.size(); ++i)
    {
        dest.writeString(bones[i].mName);
        dest.writeUInt(bones[i].mParentIndex);
        dest.writeVector3(bones[i].mBindPosition);
        dest.writeQuaternion(bones[i].mBindRotation);
        dest.writeVector3(bones[i].mBindScale);
        dest.writeUByte(bones[i].mCollisionMask);
        if (bones[i].mCollisionMask & 1)
            dest.writeFloat(bones[i].mRadius);
        if (bones[i].mCollisionMask & 2)
            dest.writeBoundingBox(bones[i].mBoundingBox);
    }
    
    // Bounding box
    dest.writeBoundingBox(box);
    
    // LOD level info
    dest.writeUInt(collisionLodLevel);
    dest.writeUInt(raycastLodLevel);
    dest.writeUInt(occlusionLodLevel);
    
    XMLElement skeletonRoot = skelFile.getRootElement("", false);
    if ((skeletonRoot.notNull()) && (exportAnimations))
    {
        // Go through animations
        XMLElement animationsRoot = skeletonRoot.getChildElement("animations", false);
        if (animationsRoot)
        {
            XMLElement animation = animationsRoot.getChildElement("animation", false);
            while (animation.notNull())
            {
                ModelAnimation newAnimation;
                newAnimation.mName = animation.getString("name");
                newAnimation.mLength = animation.getFloat("length");
                
                XMLElement tracksRoot = animation.getChildElement("tracks", false);
                XMLElement track = tracksRoot.getChildElement("track", false);
                while (track.notNull())
                {
                    std::string trackName = track.getString("bone");
                    ModelBone* bone = 0;
                    for (unsigned i = 0; i < bones.size(); ++i)
                    {
                        if (bones[i].mName == trackName)
                        {
                            bone = &bones[i];
                            break;
                        }
                    }
                    if (!bone)
                        errorExit("Found animation track for unknown bone " + trackName);
                    
                    AnimationTrack newAnimationTrack;
                    newAnimationTrack.mName = trackName;
                    if (!rotationsOnly)
                        newAnimationTrack.mChannelMask = CHANNEL_POSITION | CHANNEL_ROTATION;
                    else
                        newAnimationTrack.mChannelMask = CHANNEL_ROTATION;
                    
                    XMLElement keyFramesRoot = track.getChildElement("keyframes");
                    XMLElement keyFrame = keyFramesRoot.getChildElement("keyframe", false);
                    while (keyFrame.notNull())
                    {
                        AnimationKeyFrame newKeyFrame;
                        
                        // Convert from right- to left-handed
                        XMLElement position = keyFrame.getChildElement("translate");
                        float x = position.getFloat("x");
                        float y = position.getFloat("y");
                        float z = position.getFloat("z");
                        Vector3 pos(x, y, -z);
                        
                        XMLElement rotation = keyFrame.getChildElement("rotate");
                        XMLElement axis = rotation.getChildElement("axis");
                        float angle = -rotation.getFloat("angle") * M_RADTODEG;
                        x = axis.getFloat("x");
                        y = axis.getFloat("y");
                        z = axis.getFloat("z");
                        Vector3 axisVec(x, y, -z);
                        Quaternion rot(angle, axisVec);
                        
                        // Transform from bind-pose relative into absolute
                        pos = bone->mBindPosition + bone->mBindRotation * pos;
                        rot = bone->mBindRotation * rot;
                        
                        newKeyFrame.mTime = keyFrame.getFloat("time");
                        newKeyFrame.mPosition = pos;
                        newKeyFrame.mRotation = rot;
                        
                        newAnimationTrack.mKeyFrames.push_back(newKeyFrame);
                        keyFrame = keyFrame.getNextElement("keyframe");
                    }
                    
                    // Make sure keyframes are sorted from beginning to end
                    std::sort(newAnimationTrack.mKeyFrames.begin(), newAnimationTrack.mKeyFrames.end(), compareKeyFrames);
                    
                    // Do not add tracks with no keyframes
                    if (newAnimationTrack.mKeyFrames.size())
                        newAnimation.mTracks.push_back(newAnimationTrack);
                    
                    track = track.getNextElement("track");
                }
                
                // Write each animation into a separate file
                std::string animationFileName = replace(outputFileName, ".mdl", "") + "_" + newAnimation.mName + ".ani";
                File dest(animationFileName, FILE_WRITE);
                dest.writeString(newAnimation.mName);
                dest.writeFloat(newAnimation.mLength);
                dest.writeUInt(newAnimation.mTracks.size());
                for (unsigned i = 0; i < newAnimation.mTracks.size(); ++i)
                {
                    AnimationTrack& track = newAnimation.mTracks[i];
                    dest.writeString(track.mName);
                    dest.writeUByte(track.mChannelMask);
                    dest.writeUInt(track.mKeyFrames.size());
                    for (unsigned j = 0; j < track.mKeyFrames.size(); ++j)
                    {
                        AnimationKeyFrame& keyFrame = track.mKeyFrames[j];
                        dest.writeFloat(keyFrame.mTime);
                        if (track.mChannelMask & CHANNEL_POSITION)
                            dest.writeVector3(keyFrame.mPosition);
                        if (track.mChannelMask & CHANNEL_ROTATION)
                            dest.writeQuaternion(keyFrame.mRotation);
                        if (track.mChannelMask & CHANNEL_SCALE)
                            dest.writeVector3(keyFrame.mScale);
                    }
                }
                
                animation = animation.getNextElement("animation");
                std::cout << "Processed animation " << newAnimation.mName << std::endl;
            }
        }
    }
}

void optimizeIndices(ModelSubGeometryLodLevel* subGeom, ModelVertexBuffer* vb, ModelIndexBuffer* ib)
{
    std::vector<Triangle> oldTriangles;
    std::vector<Triangle> newTriangles;
    
    for (unsigned i = 0; i < vb->mVertices.size(); ++i)
    {
        vb->mVertices[i].mUseCount = 0;
        vb->mVertices[i].mCachePosition = -1;
    }
    
    if (subGeom->mIndexCount % 3)
        errorExit("Index count is not divisible by 3");
    
    for (unsigned i = subGeom->mIndexStart; i < subGeom->mIndexStart + subGeom->mIndexCount; i += 3)
    {
        Triangle triangle;
        triangle.mVertex1 = ib->mIndices[i];
        triangle.mVertex2 = ib->mIndices[i + 1];
        triangle.mVertex3 = ib->mIndices[i + 2];
        vb->mVertices[triangle.mVertex1].mUseCount++;
        vb->mVertices[triangle.mVertex2].mUseCount++;
        vb->mVertices[triangle.mVertex3].mUseCount++;
        oldTriangles.push_back(triangle);
    }
    
    for (unsigned i = 0; i < vb->mVertices.size(); ++i)
        calculateScore(vb->mVertices[i]);
    
    std::vector<unsigned> vertexCache;
    
    while (oldTriangles.size())
    {
        unsigned bestTriangle = M_MAX_UNSIGNED;
        float bestTriangleScore = -1.0f;
        
        // Find the best triangle at this point
        for (unsigned i = 0; i < oldTriangles.size(); ++i)
        {
            Triangle& triangle = oldTriangles[i];
            float triangleScore = 
                vb->mVertices[triangle.mVertex1].mScore +
                vb->mVertices[triangle.mVertex2].mScore +
                vb->mVertices[triangle.mVertex3].mScore;
            
            if (triangleScore > bestTriangleScore)
            {
                bestTriangle = i;
                bestTriangleScore = triangleScore;
            }
        }
        
        if (bestTriangle == M_MAX_UNSIGNED)
            errorExit("Could not find next triangle");
        
        // Add the best triangle
        Triangle triangleCopy = oldTriangles[bestTriangle];
        newTriangles.push_back(triangleCopy);
        oldTriangles.erase(oldTriangles.begin() + bestTriangle);
        
        // Reduce the use count
        vb->mVertices[triangleCopy.mVertex1].mUseCount--;
        vb->mVertices[triangleCopy.mVertex2].mUseCount--;
        vb->mVertices[triangleCopy.mVertex3].mUseCount--;
        
        // Model the LRU cache behaviour
        // Erase the triangle vertices from the middle of the cache, if they were there
        for (unsigned i = 0; i < vertexCache.size(); ++i)
        {
            if ((vertexCache[i] == triangleCopy.mVertex1) ||
                (vertexCache[i] == triangleCopy.mVertex2) ||
                (vertexCache[i] == triangleCopy.mVertex3))
            {
                vertexCache.erase(vertexCache.begin() + i);
                --i;
            }
        }
        
        // Then push them to the front
        vertexCache.insert(vertexCache.begin(), triangleCopy.mVertex1);
        vertexCache.insert(vertexCache.begin(), triangleCopy.mVertex2);
        vertexCache.insert(vertexCache.begin(), triangleCopy.mVertex3);
        
        // Update positions & scores of all vertices in the cache
        // Give position -1 if vertex is going to be erased
        for (unsigned i = 0; i < vertexCache.size(); ++i)
        {
            ModelVertex& vertex = vb->mVertices[vertexCache[i]];
            if (i >= VERTEX_CACHE_SIZE)
                vertex.mCachePosition = -1;
            else
                vertex.mCachePosition = i;
            calculateScore(vertex);
        }
        
        // Finally erase the extra vertices
        if (vertexCache.size() > VERTEX_CACHE_SIZE)
            vertexCache.resize(VERTEX_CACHE_SIZE);
    }
    
    // Rewrite the index data now
    unsigned i = subGeom->mIndexStart;
    for (unsigned j = 0; j < newTriangles.size(); ++j)
    {
        ib->mIndices[i++] = newTriangles[j].mVertex1;
        ib->mIndices[i++] = newTriangles[j].mVertex2;
        ib->mIndices[i++] = newTriangles[j].mVertex3;
    }
}

void calculateScore(ModelVertex& vertex)
{
    // Linear-Speed Vertex Cache Optimisation by Tom Forsyth from
    // http://home.comcast.net/~tom_forsyth/papers/fast_vert_cache_opt.html
    const float cacheDecayPower = 1.5f;
    const float lastTriScore = 0.75f;
    const float valenceBoostScale = 2.0f;
    const float valenceBoostPower = 0.5f;
    
    if (vertex.mUseCount == 0)
    {
        // No tri needs this vertex!
        vertex.mScore = -1.0f;
        return;
    }
    
    float score = 0.0f;
    int cachePosition = vertex.mCachePosition;
    if (cachePosition < 0)
    {
        // Vertex is not in FIFO cache - no score.
    }
    else
    {
        if (cachePosition < 3)
        {
            // This vertex was used in the last triangle,
            // so it has a fixed score, whichever of the three
            // it's in. Otherwise, you can get very different
            // answers depending on whether you add
            // the triangle 1,2,3 or 3,1,2 - which is silly.
            score = lastTriScore;
        }
        else
        {
            // Points for being high in the cache.
            const float scaler = 1.0f / (VERTEX_CACHE_SIZE - 3);
            score = 1.0f - (cachePosition - 3) * scaler;
            score = powf(score, cacheDecayPower);
        }
    }
    
    // Bonus points for having a low number of tris still to
    // use the vert, so we get rid of lone verts quickly.
    float valenceBoost = powf((float)vertex.mUseCount, -valenceBoostPower);
    score += valenceBoostScale * valenceBoost;
    vertex.mScore = score;
}

void errorExit(const std::string& error)
{
    throw Exception(error);
}
