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

#include "Context.h"
#include "File.h"
#include "FileSystem.h"
#include "OgreImporterUtils.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <set>

#include "DebugNew.h"

static const int VERTEX_CACHE_SIZE = 32;

SharedPtr<Context> context_(new Context());
SharedPtr<XMLFile> meshFile_(new XMLFile(context_));
SharedPtr<XMLFile> skelFile_(new XMLFile(context_));
std::vector<ModelIndexBuffer> indexBuffers_;
std::vector<ModelVertexBuffer> vertexBuffers_;
std::vector<std::vector<ModelSubGeometryLodLevel> > subGeometries_;
std::vector<ModelBone> bones_;
std::vector<ModelMorph> morphs_;
BoundingBox boundingBox_;
unsigned numSubMeshes_ = 0;
bool useOneBuffer_ = true;

int main(int argc, char** argv);
void Run(const std::vector<std::string>& arguments);
void LoadSkeleton(const std::string& skeletonFileName);
void LoadMesh(const std::string& inputFileName, bool generateTangents, bool splitSubMeshes, bool GetMorphs);
void WriteOutput(const std::string& outputFileName, bool exportAnimations, bool rotationsOnly);
void OptimizeIndices(ModelSubGeometryLodLevel* subGeom, ModelVertexBuffer* vb, ModelIndexBuffer* ib);
void CalculateScore(ModelVertex& vertex);
void ErrorExit(const std::string& error);

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;
    
    for (int i = 1; i < argc; ++i)
        arguments.push_back(std::string(argv[i]));
    
    Run(arguments);
    return 0;
}

void Run(const std::vector<std::string>& arguments)
{
    if (arguments.size() < 2)
    {
        ErrorExit(
            "Usage: OgreImporter <input file> <output file> [options]\n\n"
            "Options:\n"
            "-a   Export animations\n"
            "-m   Export morphs\n"
            "-r   Export only rotations from animations\n"
            "-s   Split each submesh into own vertex buffer\n"
            "-t   Generate tangents\n"
        );
    }
    
    bool generateTangents = false;
    bool GetMorphs = false;
    bool splitSubMeshes = false;
    bool exportAnimations = false;
    bool rotationsOnly = false;
    
    if (arguments.size() > 2)
    {
        for (unsigned i = 2; i < arguments.size(); ++i)
        {
            if (arguments[i][0] == '-')
            {
                std::string arg = ToLower(arguments[i].substr(1));
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
                    GetMorphs = true;
                    break;
                    
                case 's':
                    splitSubMeshes = true;
                    break;
                }
            }
        }
    }
    
    LoadMesh(arguments[0], generateTangents, splitSubMeshes, GetMorphs);
    WriteOutput(arguments[1], exportAnimations, rotationsOnly);
    
    std::cout << "Finished" << std::endl;
}

void LoadSkeleton(const std::string& skeletonFileName)
{
    // Process skeleton first (if found)
    XMLElement skeletonRoot;
    File skeletonFileSource(context_);
    skeletonFileSource.Open(skeletonFileName);
    skelFile_->Load(skeletonFileSource);
    skeletonRoot = skelFile_->GetRootElement();
    
    if (skeletonRoot)
    {
        XMLElement bonesRoot = skeletonRoot.GetChildElement("bones");
        XMLElement bone = bonesRoot.GetChildElement("bone");
        while (bone)
        {
            unsigned index = bone.GetInt("id");
            std::string name = bone.GetString("name");
            if (index >= bones_.size())
                bones_.resize(index + 1);
            
            // Convert from right- to left-handed
            XMLElement position = bone.GetChildElement("position");
            float x = position.GetFloat("x");
            float y = position.GetFloat("y");
            float z = position.GetFloat("z");
            Vector3 pos(x, y, -z);
            
            XMLElement rotation = bone.GetChildElement("rotation");
            XMLElement axis = rotation.GetChildElement("axis");
            float angle = -rotation.GetFloat("angle") * M_RADTODEG;
            x = axis.GetFloat("x");
            y = axis.GetFloat("y");
            z = axis.GetFloat("z");
            Vector3 axisVec(x, y, -z);
            Quaternion rot(angle, axisVec);
            
            bones_[index].name_ = name;
            bones_[index].parentIndex_ = index; // Fill in the correct parent later
            bones_[index].bindPosition_ = pos;
            bones_[index].bindRotation_ = rot;
            bones_[index].bindScale_ = Vector3::UNITY;
            bones_[index].collisionMask_ = 0;
            bones_[index].radius_ = 0.0f;
            
            bone = bone.GetNextElement("bone");
        }
        
        // Go through the bone hierarchy
        XMLElement boneHierarchy = skeletonRoot.GetChildElement("bonehierarchy");
        XMLElement boneParent = boneHierarchy.GetChildElement("boneparent");
        while (boneParent)
        {
            std::string bone = boneParent.GetString("bone");
            std::string parent = boneParent.GetString("parent");
            unsigned i = 0, j = 0;
            for (i = 0; (i < bones_.size()) && (bones_[i].name_ != bone); ++i)
            for (j = 0; (j < bones_.size()) && (bones_[j].name_ != parent); ++j)
            
            if ((i >= bones_.size()) || (j >= bones_.size()))
                ErrorExit("Found indeterminate parent bone assignment");
            bones_[i].parentIndex_ = j;
            
            boneParent = boneParent.GetNextElement("boneparent");
        }
        
        // Calculate bone derived positions
        for (unsigned i = 0; i < bones_.size(); ++i)
        {
            Vector3 derivedPosition = bones_[i].bindPosition_;
            Quaternion derivedRotation = bones_[i].bindRotation_;
            Vector3 derivedScale = bones_[i].bindScale_;
            
            unsigned index = bones_[i].parentIndex_;
            if (index != i)
            {
                for (;;)
                {
                    derivedPosition = bones_[index].bindPosition_ + (bones_[index].bindRotation_ * (bones_[index].bindScale_ * derivedPosition));
                    derivedRotation = bones_[index].bindRotation_ * derivedRotation;
                    derivedScale = bones_[index].bindScale_ * derivedScale;
                    if (bones_[index].parentIndex_ != index)
                        index = bones_[index].parentIndex_;
                    else
                        break;
                }
            }
            
            bones_[i].derivedPosition_ = derivedPosition;
            bones_[i].derivedRotation_ = derivedRotation;
            bones_[i].derivedScale_ = derivedScale;
            bones_[i].worldTransform_ = Matrix4x3(derivedPosition, derivedRotation, derivedScale);
            bones_[i].inverseWorldTransform_ = bones_[i].worldTransform_.GetInverse();
        }
        
        std::cout << "Processed skeleton" << std::endl;
    }
}

void LoadMesh(const std::string& inputFileName, bool generateTangents, bool splitSubMeshes, bool GetMorphs)
{
    File meshFileSource(context_);
    meshFileSource.Open(inputFileName);
    if (!meshFile_->Load(meshFileSource))
        ErrorExit("Could not load input file " + inputFileName);
    
    XMLElement root = meshFile_->GetRootElement();
    XMLElement subMeshes = root.GetChildElement("submeshes");
    XMLElement skeletonLink = root.GetChildElement("skeletonlink");
    
    std::string skeletonName = skeletonLink.GetString("name");
    if (!skeletonName.empty())
        LoadSkeleton(GetPath(inputFileName) + GetFileName(skeletonName) + ".skeleton.xml");
    
    // Check whether there's benefit of avoiding 32bit indices by splitting each submesh into own buffer
    XMLElement subMesh = subMeshes.GetChildElement("submesh");
    unsigned totalVertices = 0;
    unsigned maxSubMeshVertices = 0;
    while (subMesh)
    {
        XMLElement geometry = subMesh.GetChildElement("geometry");
        if (geometry)
        {
            unsigned vertices = geometry.GetInt("vertexcount");
            totalVertices += vertices;
            if (maxSubMeshVertices < vertices)
                maxSubMeshVertices = vertices;
        }
        ++numSubMeshes_;
        
        subMesh = subMesh.GetNextElement("submesh");
    }
    
    XMLElement sharedGeometry = root.GetChildElement("sharedgeometry");
    if (sharedGeometry)
    {
        unsigned vertices = sharedGeometry.GetInt("vertexcount");
        totalVertices += vertices;
        if (maxSubMeshVertices < vertices)
            maxSubMeshVertices = vertices;
    }
    
    if ((splitSubMeshes) || ((totalVertices > 65535) && (maxSubMeshVertices <= 65535)))
    {
        useOneBuffer_ = false;
        vertexBuffers_.resize(numSubMeshes_);
        indexBuffers_.resize(numSubMeshes_);
    }
    else
    {
        vertexBuffers_.resize(1);
        indexBuffers_.resize(1);
    }
    
    subMesh = subMeshes.GetChildElement("submesh");
    unsigned indexStart = 0;
    unsigned vertexStart = 0;
    unsigned subMeshIndex = 0;
    
    std::vector<unsigned> vertexStarts;
    vertexStarts.resize(numSubMeshes_);
    
    while (subMesh)
    {
        XMLElement geometry = subMesh.GetChildElement("geometry");
        XMLElement faces = subMesh.GetChildElement("faces");
        
        // If no submesh vertexbuffer, process the shared geometry, but do it only once
        unsigned vertices = 0;
        if (!geometry)
        {
            vertexStart = 0;
            if (!subMeshIndex)
                geometry = root.GetChildElement("sharedgeometry");
        }
        
        if (geometry)
            vertices = geometry.GetInt("vertexcount");
        
        ModelSubGeometryLodLevel subGeometryLodLevel;
        ModelVertexBuffer* vBuf;
        ModelIndexBuffer* iBuf;
        
        if (useOneBuffer_)
        {
            vBuf = &vertexBuffers_[0];
            if (vertices)
                vBuf->vertices_.resize(vertexStart + vertices);
            iBuf = &indexBuffers_[0];
            
            subGeometryLodLevel.vertexBuffer_ = 0;
            subGeometryLodLevel.indexBuffer_ = 0;
        }
        else
        {
            vertexStart = 0;
            indexStart = 0;
            
            vBuf = &vertexBuffers_[subMeshIndex];
            vBuf->vertices_.resize(vertices);
            iBuf = &indexBuffers_[subMeshIndex];
            
            subGeometryLodLevel.vertexBuffer_ = subMeshIndex;
            subGeometryLodLevel.indexBuffer_ = subMeshIndex;
        }
        
        // Store the start vertex for later use
        vertexStarts[subMeshIndex] = vertexStart;
        
        // Ogre may have multiple buffers in one submesh. These will be merged into one
        XMLElement bufferDef;
        if (geometry)
            bufferDef = geometry.GetChildElement("vertexbuffer");
        
        while (bufferDef)
        {
            if (bufferDef.HasAttribute("positions"))
                vBuf->elementMask_ |= MASK_POSITION;
            if (bufferDef.HasAttribute("normals"))
                vBuf->elementMask_ |= MASK_NORMAL;
            if (bufferDef.HasAttribute("texture_coords"))
                vBuf->elementMask_ |= MASK_TEXCOORD1;
            
            unsigned vertexNum = vertexStart;
            if (vertices)
            {
                XMLElement vertex = bufferDef.GetChildElement("vertex");
                while (vertex)
                {
                    XMLElement position = vertex.GetChildElement("position");
                    if (position)
                    {
                        // Convert from right- to left-handed
                        float x = position.GetFloat("x");
                        float y = position.GetFloat("y");
                        float z = position.GetFloat("z");
                        Vector3 vec(x, y, -z);
                        
                        vBuf->vertices_[vertexNum].position_ = vec;
                        boundingBox_.Merge(vec);
                    }
                    XMLElement normal = vertex.GetChildElement("normal");
                    if (normal)
                    {
                        // Convert from right- to left-handed
                        float x = normal.GetFloat("x");
                        float y = normal.GetFloat("y");
                        float z = normal.GetFloat("z");
                        Vector3 vec(x, y, -z);
                        
                        vBuf->vertices_[vertexNum].normal_ = vec;
                    }
                    XMLElement uv = vertex.GetChildElement("texcoord");
                    if (uv)
                    {
                        float x = uv.GetFloat("u");
                        float y = uv.GetFloat("v");
                        Vector2 vec(x, y);
                        
                        vBuf->vertices_[vertexNum].texCoord1_ = vec;
                    }
                    
                    vertexNum++;
                    vertex = vertex.GetNextElement("vertex");
                }
            }
            
            bufferDef = bufferDef.GetNextElement("vertexbuffer");
        }
        
        unsigned triangles = faces.GetInt("count");
        unsigned indices = triangles * 3;
        
        XMLElement triangle = faces.GetChildElement("face");
        while (triangle)
        {
            unsigned v1 = triangle.GetInt("v1");
            unsigned v2 = triangle.GetInt("v2");
            unsigned v3 = triangle.GetInt("v3");
            iBuf->indices_.push_back(v3 + vertexStart);
            iBuf->indices_.push_back(v2 + vertexStart);
            iBuf->indices_.push_back(v1 + vertexStart);
            triangle = triangle.GetNextElement("face");
        }
        
        subGeometryLodLevel.indexStart_ = indexStart;
        subGeometryLodLevel.indexCount_ = indices;
        if (vertexStart + vertices > 65535)
            iBuf->indexSize_ = sizeof(unsigned);
        
        if (bones_.size())
        {
            XMLElement boneAssignments = subMesh.GetChildElement("boneassignments");
            if (boneAssignments)
            {
                XMLElement boneAssignment = boneAssignments.GetChildElement("vertexboneassignment");
                while (boneAssignment)
                {
                    unsigned vertex = boneAssignment.GetInt("vertexindex") + vertexStart;
                    unsigned bone = boneAssignment.GetInt("boneindex");
                    float weight = boneAssignment.GetFloat("weight");
                    
                    BoneWeightAssignment assign;
                    assign.boneIndex_ = bone;
                    assign.weight_ = weight;
                    // Source data might have 0 weights. Disregard these
                    if (assign.weight_ > 0.0f)
                    {
                        subGeometryLodLevel.boneWeights_[vertex].push_back(assign);
                        
                        if (assign.weight_ > 0.33f)
                        {
                            // Check distance of vertex from bone to get bone max. radius information
                            Vector3 bonePos = bones_[bone].derivedPosition_;
                            Vector3 vertexPos = vBuf->vertices_[vertex].position_;
                            float distance = (bonePos - vertexPos).GetLength();
                            if (distance > bones_[bone].radius_)
                            {
                                bones_[bone].collisionMask_ |= 1;
                                bones_[bone].radius_ = distance;
                            }
                            // Build the hitbox for the bone
                            bones_[bone].boundingBox_.Merge(bones_[bone].inverseWorldTransform_ * (vertexPos));
                            bones_[bone].collisionMask_ |= 2;
                        }
                    }
                    boneAssignment = boneAssignment.GetNextElement("vertexboneassignment");
                }
            }
            
            if ((subGeometryLodLevel.boneWeights_.size()) && bones_.size())
            {
                vBuf->elementMask_ |= MASK_BLENDWEIGHTS | MASK_BLENDINDICES;
                bool sorted = false;
                
                // If amount of bones_ is larger than supported by HW skinning, must remap per submesh
                if (bones_.size() > MAX_SKIN_MATRICES)
                {
                    std::map<unsigned, unsigned> usedBoneMap;
                    unsigned remapIndex = 0;
                    for (std::map<unsigned, std::vector<BoneWeightAssignment> >::iterator i =
                        subGeometryLodLevel.boneWeights_.begin(); i != subGeometryLodLevel.boneWeights_.end(); ++i)
                    {
                        // Sort the bone assigns by weight
                        std::sort(i->second.begin(), i->second.end(), CompareWeights);
                        
                        // Use only the first 4 weights
                        for (unsigned j = 0; j < i->second.size() && j < 4; ++j)
                        {
                            unsigned originalIndex = i->second[j].boneIndex_;
                            if (usedBoneMap.find(originalIndex) == usedBoneMap.end())
                            {
                                usedBoneMap[originalIndex] = remapIndex;
                                remapIndex++;
                            }
                            i->second[j].boneIndex_ = usedBoneMap[originalIndex];
                        }
                    }
                    
                    // If still too many bones_ in one subgeometry, error
                    if (usedBoneMap.size() > MAX_SKIN_MATRICES)
                        ErrorExit("Too many bones_ in submesh " + ToString(subMeshIndex + 1));
                    
                    // Write mapping of vertex buffer bone indices to original bone indices
                    subGeometryLodLevel.boneMapping_.resize(usedBoneMap.size());
                    for (std::map<unsigned, unsigned>::iterator j = usedBoneMap.begin(); j != usedBoneMap.end(); ++j)
                        subGeometryLodLevel.boneMapping_[j->second] = j->first;
                    
                    sorted = true;
                }
                
                for (std::map<unsigned, std::vector<BoneWeightAssignment> >::iterator i = subGeometryLodLevel.boneWeights_.begin();
                    i != subGeometryLodLevel.boneWeights_.end(); ++i)
                {
                    // Sort the bone assigns by weight, if not sorted yet in bone remapping pass
                    if (!sorted)
                        std::sort(i->second.begin(), i->second.end(), CompareWeights);
                    
                    float totalWeight = 0.0f;
                    float normalizationFactor = 0.0f;
                    
                    // Calculate normalization factor in case there are more than 4 blend weights, or they do not add up to 1
                    for (unsigned j = 0; j < i->second.size() && j < 4; ++j)
                        totalWeight += i->second[j].weight_;
                    if (totalWeight > 0.0f)
                        normalizationFactor = 1.0f / totalWeight;
                    
                    for (unsigned j = 0; j < i->second.size() && j < 4; ++j)
                    {
                        vBuf->vertices_[i->first].blendIndices_[j] = i->second[j].boneIndex_;
                        vBuf->vertices_[i->first].blendWeights_[j] = i->second[j].weight_ * normalizationFactor;
                    }
                    
                    // If there are less than 4 blend weights, fill rest with zero
                    for (unsigned j = i->second.size(); j < 4; ++j)
                    {
                        vBuf->vertices_[i->first].blendIndices_[j] = 0;
                        vBuf->vertices_[i->first].blendWeights_[j] = 0.0f;
                    }
                    
                    vBuf->vertices_[i->first].hasBlendWeights_ = true;
                }
            }
        }
        else
            std::cout << "No skeleton loaded, skipping skinning information" << std::endl;
        
        indexStart += indices;
        vertexStart += vertices;
        
        OptimizeIndices(&subGeometryLodLevel, vBuf, iBuf);
        
        std::cout << "Processed submesh " << subMeshIndex + 1 << ": " << vertices << " vertices " << triangles << " triangles" << std::endl;
        std::vector<ModelSubGeometryLodLevel> thisSubGeometry;
        thisSubGeometry.push_back(subGeometryLodLevel);
        subGeometries_.push_back(thisSubGeometry);
        
        subMesh = subMesh.GetNextElement("submesh");
        subMeshIndex++;
    }
    
    // Process LOD levels, if any
    XMLElement lods = root.GetChildElement("levelofdetail");
    if (lods)
    {
        try
        {
            // For now, support only generated LODs, where the vertices are the same
            XMLElement lod = lods.GetChildElement("lodgenerated");
            while (lod)
            {
                float distance = M_EPSILON;
                if (lod.HasAttribute("fromdepthsquared"))
                    distance = sqrtf(lod.GetFloat("fromdepthsquared"));
                if (lod.HasAttribute("value"))
                    distance = lod.GetFloat("value");
                XMLElement lodSubMesh = lod.GetChildElement("lodfacelist");
                while (lodSubMesh)
                {
                    unsigned subMeshIndex = lodSubMesh.GetInt("submeshindex");
                    unsigned triangles = lodSubMesh.GetInt("numfaces");
                    
                    ModelSubGeometryLodLevel newLodLevel;
                    ModelSubGeometryLodLevel& originalLodLevel = subGeometries_[subMeshIndex][0];
                    
                    // Copy all initial values
                    newLodLevel = originalLodLevel;
                    
                    ModelVertexBuffer* vBuf;
                    ModelIndexBuffer* iBuf;
                    
                    if (useOneBuffer_)
                    {
                        vBuf = &vertexBuffers_[0];
                        iBuf = &indexBuffers_[0];
                    }
                    else
                    {
                        vBuf = &vertexBuffers_[subMeshIndex];
                        iBuf = &indexBuffers_[subMeshIndex];
                    }
                    
                    unsigned indexStart = iBuf->indices_.size();
                    unsigned indexCount = triangles * 3;
                    unsigned vertexStart = vertexStarts[subMeshIndex];
                    
                    newLodLevel.distance_ = distance;
                    newLodLevel.indexStart_ = indexStart;
                    newLodLevel.indexCount_ = indexCount;
                    
                    // Append indices to the original index buffer
                    XMLElement triangle = lodSubMesh.GetChildElement("face");
                    while (triangle)
                    {
                        unsigned v1 = triangle.GetInt("v1");
                        unsigned v2 = triangle.GetInt("v2");
                        unsigned v3 = triangle.GetInt("v3");
                        iBuf->indices_.push_back(v3 + vertexStart);
                        iBuf->indices_.push_back(v2 + vertexStart);
                        iBuf->indices_.push_back(v1 + vertexStart);
                        triangle = triangle.GetNextElement("face");
                    }
                    
                    OptimizeIndices(&newLodLevel, vBuf, iBuf);
                    
                    subGeometries_[subMeshIndex].push_back(newLodLevel);
                    std::cout << "Processed LOD level for submesh " << subMeshIndex + 1 << ": distance " << distance << std::endl;
                    
                    lodSubMesh = lodSubMesh.GetNextElement("lodfacelist");
                }
                lod = lod.GetNextElement("lodgenerated");
            }
        }
        catch (...) {}
    }
    
    // Process poses/morphs
    // First find out all pose definitions
    if (GetMorphs)
    {
        try
        {
            std::vector<XMLElement> poses;
            XMLElement posesRoot = root.GetChildElement("poses");
            if (posesRoot)
            {
                XMLElement pose = posesRoot.GetChildElement("pose");
                while (pose)
                {
                    poses.push_back(pose);
                    pose = pose.GetNextElement("pose");
                }
            }
            
            // Then process animations using the poses
            XMLElement animsRoot = root.GetChildElement("animations");
            if (animsRoot)
            {
                XMLElement anim = animsRoot.GetChildElement("animation");
                while (anim)
                {
                    std::string name = anim.GetString("name");
                    float length = anim.GetFloat("length");
                    std::set<unsigned> usedPoses;
                    XMLElement tracks = anim.GetChildElement("tracks");
                    if (tracks)
                    {
                        XMLElement track = tracks.GetChildElement("track");
                        while (track)
                        {
                            XMLElement keyframes = track.GetChildElement("keyframes");
                            if (keyframes)
                            {
                                XMLElement keyframe = keyframes.GetChildElement("keyframe");
                                while (keyframe)
                                {
                                    float time = keyframe.GetFloat("time");
                                    XMLElement poseref = keyframe.GetChildElement("poseref");
                                    // Get only the end pose
                                    if ((poseref) && (time == length))
                                        usedPoses.insert(poseref.GetInt("poseindex"));
                                    
                                    keyframe = keyframe.GetNextElement("keyframe");
                                }
                            }
                            track = track.GetNextElement("track");
                        }
                    }
                    
                    if (usedPoses.size())
                    {
                        ModelMorph newMorph;
                        newMorph.name_ = name;
                        
                        if (useOneBuffer_)
                            newMorph.buffers_.resize(1);
                        else
                            newMorph.buffers_.resize(usedPoses.size());
                        
                        unsigned bufIndex = 0;
                        
                        for (std::set<unsigned>::iterator i = usedPoses.begin(); i != usedPoses.end(); ++i)
                        {
                            XMLElement pose = poses[*i];
                            unsigned targetSubMesh = pose.GetInt("index");
                            XMLElement poseOffset = pose.GetChildElement("poseoffset");
                        
                            if (useOneBuffer_)
                                newMorph.buffers_[bufIndex].vertexBuffer_ = 0;
                            else
                                newMorph.buffers_[bufIndex].vertexBuffer_ = targetSubMesh;
                            
                            newMorph.buffers_[bufIndex].elementMask_ = MASK_POSITION;
                            
                            ModelVertexBuffer* vBuf = &vertexBuffers_[newMorph.buffers_[bufIndex].vertexBuffer_];
                            
                            while (poseOffset)
                            {
                                // Convert from right- to left-handed
                                unsigned vertexIndex = poseOffset.GetInt("index") + vertexStarts[targetSubMesh];
                                float x = poseOffset.GetFloat("x");
                                float y = poseOffset.GetFloat("y");
                                float z = poseOffset.GetFloat("z");
                                Vector3 vec(x, y, -z);
                                
                                if (vBuf->morphCount_ == 0)
                                {
                                    vBuf->morphStart_ = vertexIndex;
                                    vBuf->morphCount_ = 1;
                                }
                                else
                                {
                                    unsigned first = vBuf->morphStart_;
                                    unsigned last = first + vBuf->morphCount_ - 1;
                                    if (vertexIndex < first)
                                        first = vertexIndex;
                                    if (vertexIndex > last)
                                        last = vertexIndex;
                                    vBuf->morphStart_ = first;
                                    vBuf->morphCount_ = last - first + 1;
                                }
                                
                                ModelVertex newVertex;
                                newVertex.position_ = vec;
                                newMorph.buffers_[bufIndex].vertices_[vertexIndex] = newVertex;
                                poseOffset = poseOffset.GetNextElement("poseoffset");
                            }
                            
                            if (!useOneBuffer_)
                                ++bufIndex;
                        }
                        morphs_.push_back(newMorph);
                        std::cout << "Processed morph " << name << " with " << usedPoses.size() << " sub-poses" << std::endl;
                    }
                    
                    anim = anim.GetNextElement("animation");
                }
            }
        }
        catch (...) {}
    }
    
    // Check any of the buffers for vertices with missing blend weight assignments
    for (unsigned i = 0; i < vertexBuffers_.size(); ++i)
    {
        if (vertexBuffers_[i].elementMask_ & MASK_BLENDWEIGHTS)
        {
            for (unsigned j = 0; j < vertexBuffers_[i].vertices_.size(); ++j)
                if (!vertexBuffers_[i].vertices_[j].hasBlendWeights_)
                    ErrorExit("Found a vertex with missing skinning information");
        }
    }
    
    // Tangent generation
    if (generateTangents)
    {
        for (unsigned i = 0; i < subGeometries_.size(); ++i)
        {
            for (unsigned j = 0; j < subGeometries_[i].size(); ++j)
            {
                ModelVertexBuffer& vBuf = vertexBuffers_[subGeometries_[i][j].vertexBuffer_];
                ModelIndexBuffer& iBuf = indexBuffers_[subGeometries_[i][j].indexBuffer_];
                unsigned indexStart = subGeometries_[i][j].indexStart_;
                unsigned indexCount = subGeometries_[i][j].indexCount_;
                unsigned vertexCount = vBuf.vertices_.size();
                
                // If already has tangents, do not regenerate
                if (vBuf.elementMask_ & MASK_TANGENT)
                    continue;
                
                vBuf.elementMask_ |= MASK_TANGENT;
                
                // Tangent generation from
                // http://www.terathon.com/code/tangent.html
                Vector3 *tan1 = new Vector3[vertexCount * 2];
                Vector3 *tan2 = tan1 + vertexCount;
                memset(tan1, 0, sizeof(Vector3) * vertexCount * 2);
                
                if ((vBuf.elementMask_ & (MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1)) != (MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1))
                    ErrorExit("To generate tangents, positions normals and texcoords are required");
                
                unsigned minVertex = M_MAX_UNSIGNED;
                unsigned maxVertex = 0;
                
                for (unsigned a = indexStart; a < indexStart + indexCount; ++a)
                {
                    if (iBuf.indices_[a] < minVertex)
                        minVertex = iBuf.indices_[a];
                    if (iBuf.indices_[a] > maxVertex)
                        maxVertex = iBuf.indices_[a];
                }
                
                for (unsigned a = indexStart; a < indexStart + indexCount; a += 3)
                {
                    unsigned i1 = iBuf.indices_[a+0];
                    unsigned i2 = iBuf.indices_[a+1];
                    unsigned i3 = iBuf.indices_[a+2];
                    
                    const Vector3& v1 = vBuf.vertices_[i1].position_;
                    const Vector3& v2 = vBuf.vertices_[i2].position_;
                    const Vector3& v3 = vBuf.vertices_[i3].position_;
                    
                    const Vector2& w1 = vBuf.vertices_[i1].texCoord1_;
                    const Vector2& w2 = vBuf.vertices_[i2].texCoord1_;
                    const Vector2& w3 = vBuf.vertices_[i3].texCoord1_;
                    
                    float x1 = v2.x_ - v1.x_;
                    float x2 = v3.x_ - v1.x_;
                    float y1 = v2.y_ - v1.y_;
                    float y2 = v3.y_ - v1.y_;
                    float z1 = v2.z_ - v1.z_;
                    float z2 = v3.z_ - v1.z_;
                    
                    float s1 = w2.x_ - w1.x_;
                    float s2 = w3.x_ - w1.x_;
                    float t1 = w2.y_ - w1.y_;
                    float t2 = w3.y_ - w1.y_;
                    
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
                    const Vector3& n = vBuf.vertices_[a].normal_;
                    const Vector3& t = tan1[a];
                    Vector3 xyz;
                    float w;
                    
                    // Gram-Schmidt orthogonalize
                    xyz = (t - n * n.DotProduct(t)).GetNormalized();
                    
                    // Calculate handedness
                    w = n.CrossProduct(t).DotProduct(tan2[a]) < 0.0f ? -1.0f : 1.0f;
                    
                    vBuf.vertices_[a].tangent_ = Vector4(xyz, w);
                }
                
                delete[] tan1;
                
                std::cout << "Generated tangents" << std::endl;
            }
        }
    }
}

void WriteOutput(const std::string& outputFileName, bool exportAnimations, bool rotationsOnly)
{
    // Begin serialization
    {
        File dest(context_);
        if (!dest.Open(outputFileName, FILE_WRITE))
            ErrorExit("Could not open output file " + outputFileName);
        
        // ID
        dest.WriteID("UMDL");
        
        // Vertexbuffers
        dest.WriteUInt(vertexBuffers_.size());
        for (unsigned i = 0; i < vertexBuffers_.size(); ++i)
            vertexBuffers_[i].WriteData(dest);
        
        // Indexbuffers
        dest.WriteUInt(indexBuffers_.size());
        for (unsigned i = 0; i < indexBuffers_.size(); ++i)
            indexBuffers_[i].WriteData(dest);
        
        // Subgeometries
        dest.WriteUInt(subGeometries_.size());
        for (unsigned i = 0; i < subGeometries_.size(); ++i)
        {
            // Write bone mapping info from the first LOD level. It does not change for further LODs
            dest.WriteUInt(subGeometries_[i][0].boneMapping_.size());
            for (unsigned k = 0; k < subGeometries_[i][0].boneMapping_.size(); ++k)
                dest.WriteUInt(subGeometries_[i][0].boneMapping_[k]);
            
            // Lod levels for this subgeometry
            dest.WriteUInt(subGeometries_[i].size());
            for (unsigned j = 0; j < subGeometries_[i].size(); ++j)
            {
                dest.WriteFloat(subGeometries_[i][j].distance_);
                dest.WriteUInt((unsigned)subGeometries_[i][j].primitiveType_);
                dest.WriteUInt(subGeometries_[i][j].vertexBuffer_);
                dest.WriteUInt(subGeometries_[i][j].indexBuffer_);
                dest.WriteUInt(subGeometries_[i][j].indexStart_);
                dest.WriteUInt(subGeometries_[i][j].indexCount_);
            }
        }
        
        // Morphs
        dest.WriteUInt(morphs_.size());
        for (unsigned i = 0; i < morphs_.size(); ++i)
            morphs_[i].WriteData(dest);
        
        // Skeleton
        dest.WriteUInt(bones_.size());
        for (unsigned i = 0; i < bones_.size(); ++i)
        {
            dest.WriteString(bones_[i].name_);
            dest.WriteUInt(bones_[i].parentIndex_);
            dest.WriteVector3(bones_[i].bindPosition_);
            dest.WriteQuaternion(bones_[i].bindRotation_);
            dest.WriteVector3(bones_[i].bindScale_);
            
            Matrix4x3 offsetMatrix(bones_[i].derivedPosition_, bones_[i].derivedRotation_, bones_[i].derivedScale_);
            offsetMatrix = offsetMatrix.GetInverse();
            dest.Write(offsetMatrix.GetData(), sizeof(Matrix4x3));
            
            dest.WriteUByte(bones_[i].collisionMask_);
            if (bones_[i].collisionMask_ & 1)
                dest.WriteFloat(bones_[i].radius_);
            if (bones_[i].collisionMask_ & 2)
                dest.WriteBoundingBox(bones_[i].boundingBox_);
        }
        
        // Bounding box
        dest.WriteBoundingBox(boundingBox_);
    }
    
    XMLElement skeletonRoot = skelFile_->GetRootElement("");
    if ((skeletonRoot) && (exportAnimations))
    {
        // Go through animations
        XMLElement animationsRoot = skeletonRoot.GetChildElement("animations");
        if (animationsRoot)
        {
            XMLElement animation = animationsRoot.GetChildElement("animation");
            while (animation)
            {
                ModelAnimation newAnimation;
                newAnimation.name_ = animation.GetString("name");
                newAnimation.length_ = animation.GetFloat("length");
                
                XMLElement tracksRoot = animation.GetChildElement("tracks");
                XMLElement track = tracksRoot.GetChildElement("track");
                while (track)
                {
                    std::string trackName = track.GetString("bone");
                    ModelBone* bone = 0;
                    for (unsigned i = 0; i < bones_.size(); ++i)
                    {
                        if (bones_[i].name_ == trackName)
                        {
                            bone = &bones_[i];
                            break;
                        }
                    }
                    if (!bone)
                        ErrorExit("Found animation track for unknown bone " + trackName);
                    
                    AnimationTrack newAnimationTrack;
                    newAnimationTrack.name_ = trackName;
                    if (!rotationsOnly)
                        newAnimationTrack.channelMask_ = CHANNEL_POSITION | CHANNEL_ROTATION;
                    else
                        newAnimationTrack.channelMask_ = CHANNEL_ROTATION;
                    
                    XMLElement keyFramesRoot = track.GetChildElement("keyframes");
                    XMLElement keyFrame = keyFramesRoot.GetChildElement("keyframe");
                    while (keyFrame)
                    {
                        AnimationKeyFrame newKeyFrame;
                        
                        // Convert from right- to left-handed
                        XMLElement position = keyFrame.GetChildElement("translate");
                        float x = position.GetFloat("x");
                        float y = position.GetFloat("y");
                        float z = position.GetFloat("z");
                        Vector3 pos(x, y, -z);
                        
                        XMLElement rotation = keyFrame.GetChildElement("rotate");
                        XMLElement axis = rotation.GetChildElement("axis");
                        float angle = -rotation.GetFloat("angle") * M_RADTODEG;
                        x = axis.GetFloat("x");
                        y = axis.GetFloat("y");
                        z = axis.GetFloat("z");
                        Vector3 axisVec(x, y, -z);
                        Quaternion rot(angle, axisVec);
                        
                        // Transform from bind-pose relative into absolute
                        pos = bone->bindPosition_ + bone->bindRotation_ * pos;
                        rot = bone->bindRotation_ * rot;
                        
                        newKeyFrame.time_ = keyFrame.GetFloat("time");
                        newKeyFrame.position_ = pos;
                        newKeyFrame.rotation_ = rot;
                        
                        newAnimationTrack.keyFrames_.push_back(newKeyFrame);
                        keyFrame = keyFrame.GetNextElement("keyframe");
                    }
                    
                    // Make sure keyframes are sorted from beginning to end
                    std::sort(newAnimationTrack.keyFrames_.begin(), newAnimationTrack.keyFrames_.end(), CompareKeyFrames);
                    
                    // Do not add tracks with no keyframes
                    if (newAnimationTrack.keyFrames_.size())
                        newAnimation.tracks_.push_back(newAnimationTrack);
                    
                    track = track.GetNextElement("track");
                }
                
                // Write each animation into a separate file
                std::string animationFileName = Replace(outputFileName, ".mdl", "") + "_" + newAnimation.name_ + ".ani";
                File dest(context_);
                if (!dest.Open(animationFileName, FILE_WRITE))
                    ErrorExit("Could not open output file " + animationFileName);
                dest.WriteID("UANI");
                dest.WriteString(newAnimation.name_);
                dest.WriteFloat(newAnimation.length_);
                dest.WriteUInt(newAnimation.tracks_.size());
                for (unsigned i = 0; i < newAnimation.tracks_.size(); ++i)
                {
                    AnimationTrack& track = newAnimation.tracks_[i];
                    dest.WriteString(track.name_);
                    dest.WriteUByte(track.channelMask_);
                    dest.WriteUInt(track.keyFrames_.size());
                    for (unsigned j = 0; j < track.keyFrames_.size(); ++j)
                    {
                        AnimationKeyFrame& keyFrame = track.keyFrames_[j];
                        dest.WriteFloat(keyFrame.time_);
                        if (track.channelMask_ & CHANNEL_POSITION)
                            dest.WriteVector3(keyFrame.position_);
                        if (track.channelMask_ & CHANNEL_ROTATION)
                            dest.WriteQuaternion(keyFrame.rotation_);
                        if (track.channelMask_ & CHANNEL_SCALE)
                            dest.WriteVector3(keyFrame.scale_);
                    }
                }
                
                animation = animation.GetNextElement("animation");
                std::cout << "Processed animation " << newAnimation.name_ << std::endl;
            }
        }
    }
}

void OptimizeIndices(ModelSubGeometryLodLevel* subGeom, ModelVertexBuffer* vb, ModelIndexBuffer* ib)
{
    std::vector<Triangle> oldTriangles;
    std::vector<Triangle> newTriangles;
    
    for (unsigned i = 0; i < vb->vertices_.size(); ++i)
    {
        vb->vertices_[i].useCount_ = 0;
        vb->vertices_[i].cachePosition_ = -1;
    }
    
    if (subGeom->indexCount_ % 3)
        ErrorExit("Index count is not divisible by 3");
    
    for (unsigned i = subGeom->indexStart_; i < subGeom->indexStart_ + subGeom->indexCount_; i += 3)
    {
        Triangle triangle;
        triangle.v0_ = ib->indices_[i];
        triangle.v1_ = ib->indices_[i + 1];
        triangle.v2_ = ib->indices_[i + 2];
        vb->vertices_[triangle.v0_].useCount_++;
        vb->vertices_[triangle.v1_].useCount_++;
        vb->vertices_[triangle.v2_].useCount_++;
        oldTriangles.push_back(triangle);
    }
    
    for (unsigned i = 0; i < vb->vertices_.size(); ++i)
        CalculateScore(vb->vertices_[i]);
    
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
                vb->vertices_[triangle.v0_].score_ +
                vb->vertices_[triangle.v1_].score_ +
                vb->vertices_[triangle.v2_].score_;
            
            if (triangleScore > bestTriangleScore)
            {
                bestTriangle = i;
                bestTriangleScore = triangleScore;
            }
        }
        
        if (bestTriangle == M_MAX_UNSIGNED)
            ErrorExit("Could not find next triangle");
        
        // Add the best triangle
        Triangle triangleCopy = oldTriangles[bestTriangle];
        newTriangles.push_back(triangleCopy);
        oldTriangles.erase(oldTriangles.begin() + bestTriangle);
        
        // Reduce the use count
        vb->vertices_[triangleCopy.v0_].useCount_--;
        vb->vertices_[triangleCopy.v1_].useCount_--;
        vb->vertices_[triangleCopy.v2_].useCount_--;
        
        // Model the LRU cache behaviour
        // Erase the triangle vertices from the middle of the cache, if they were there
        for (unsigned i = 0; i < vertexCache.size(); ++i)
        {
            if ((vertexCache[i] == triangleCopy.v0_) ||
                (vertexCache[i] == triangleCopy.v1_) ||
                (vertexCache[i] == triangleCopy.v2_))
            {
                vertexCache.erase(vertexCache.begin() + i);
                --i;
            }
        }
        
        // Then push them to the front
        vertexCache.insert(vertexCache.begin(), triangleCopy.v0_);
        vertexCache.insert(vertexCache.begin(), triangleCopy.v1_);
        vertexCache.insert(vertexCache.begin(), triangleCopy.v2_);
        
        // Update positions & scores of all vertices in the cache
        // Give position -1 if vertex is going to be erased
        for (unsigned i = 0; i < vertexCache.size(); ++i)
        {
            ModelVertex& vertex = vb->vertices_[vertexCache[i]];
            if (i >= VERTEX_CACHE_SIZE)
                vertex.cachePosition_ = -1;
            else
                vertex.cachePosition_ = i;
            CalculateScore(vertex);
        }
        
        // Finally erase the extra vertices
        if (vertexCache.size() > VERTEX_CACHE_SIZE)
            vertexCache.resize(VERTEX_CACHE_SIZE);
    }
    
    // Rewrite the index data now
    unsigned i = subGeom->indexStart_;
    for (unsigned j = 0; j < newTriangles.size(); ++j)
    {
        ib->indices_[i++] = newTriangles[j].v0_;
        ib->indices_[i++] = newTriangles[j].v1_;
        ib->indices_[i++] = newTriangles[j].v2_;
    }
}

void CalculateScore(ModelVertex& vertex)
{
    // Linear-Speed Vertex Cache Optimisation by Tom Forsyth from
    // http://home.comcast.net/~tom_forsyth/papers/fast_vert_cache_opt.html
    const float cacheDecayPower = 1.5f;
    const float lastTriScore = 0.75f;
    const float valenceBoostScale = 2.0f;
    const float valenceBoostPower = 0.5f;
    
    if (vertex.useCount_ == 0)
    {
        // No tri needs this vertex!
        vertex.score_ = -1.0f;
        return;
    }
    
    float score = 0.0f;
    int cachePosition = vertex.cachePosition_;
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
    float valenceBoost = powf((float)vertex.useCount_, -valenceBoostPower);
    score += valenceBoostScale * valenceBoost;
    vertex.score_ = score;
}

void ErrorExit(const std::string& error)
{
    std::cout << error;
    exit(1);
}
