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

#include <Urho3D/Urho3D.h>

#include <Urho3D/Core/Context.h>
#include <Urho3D/IO/File.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Container/HashSet.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/Container/Sort.h>
#include <Urho3D/Graphics/Tangent.h>
#include <Urho3D/Resource/XMLFile.h>

#include "OgreImporterUtils.h"

#ifdef WIN32
#include <windows.h>
#endif

#include <cstddef>
#include <cstring>

#include <Urho3D/DebugNew.h>

static const int VERTEX_CACHE_SIZE = 32;

SharedPtr<Context> context_(new Context());
SharedPtr<XMLFile> meshFile_(new XMLFile(context_));
SharedPtr<XMLFile> skelFile_(new XMLFile(context_));
Vector<ModelIndexBuffer> indexBuffers_;
Vector<ModelVertexBuffer> vertexBuffers_;
Vector<Vector<ModelSubGeometryLodLevel> > subGeometries_;
Vector<Vector3> subGeometryCenters_;
Vector<ModelBone> bones_;
Vector<ModelMorph> morphs_;
Vector<String> materialNames_;
BoundingBox boundingBox_;
unsigned numSubMeshes_ = 0;
bool useOneBuffer_ = true;

int main(int argc, char** argv);
void Run(const Vector<String>& arguments);
void LoadSkeleton(const String& skeletonFileName);
void LoadMesh(const String& inputFileName, bool generateTangents, bool splitSubMeshes, bool exportMorphs);
void WriteOutput(const String& outputFileName, bool exportAnimations, bool rotationsOnly, bool saveMaterialList);
void OptimizeIndices(ModelSubGeometryLodLevel* subGeom, ModelVertexBuffer* vb, ModelIndexBuffer* ib);
void CalculateScore(ModelVertex& vertex);
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
            "Usage: OgreImporter <input file> <output file> [options]\n\n"
            "Options:\n"
            "-l      Output a material list file\n"
            "-na     Do not output animations\n"
            "-nm     Do not output morphs\n"
            "-r      Output only rotations from animations\n"
            "-s      Split each submesh into own vertex buffer\n"
            "-t      Generate tangents\n"
        );
    }
    
    bool generateTangents = false;
    bool splitSubMeshes = false;
    bool exportAnimations = true;
    bool exportMorphs = true;
    bool rotationsOnly = false;
    bool saveMaterialList = false;
    
    if (arguments.Size() > 2)
    {
        for (unsigned i = 2; i < arguments.Size(); ++i)
        {
            if (arguments[i].Length() > 1 && arguments[i][0] == '-')
            {
                String argument = arguments[i].Substring(1).ToLower();
                if (argument == "l")
                    saveMaterialList = true;
                else if (argument == "r")
                    rotationsOnly = true;
                else if (argument == "s")
                    splitSubMeshes = true;
                else if (argument == "t")
                    generateTangents = true;
                else if (argument.Length() == 2 && argument[0] == 'n')
                {
                    switch (tolower(argument[1]))
                    {
                    case 'a':
                        exportAnimations = false;
                        break;
                        
                    case 'm':
                        exportMorphs = false;
                        break;
                    }
                    break;
                }
            }
        }
    }
    
    LoadMesh(arguments[0], generateTangents, splitSubMeshes, exportMorphs);
    WriteOutput(arguments[1], exportAnimations, rotationsOnly, saveMaterialList);
    
    PrintLine("Finished");
}

void LoadSkeleton(const String& skeletonFileName)
{
    // Process skeleton first (if found)
    XMLElement skeletonRoot;
    File skeletonFileSource(context_);
    skeletonFileSource.Open(skeletonFileName);
    if (!skelFile_->Load(skeletonFileSource))
        PrintLine("Failed to load skeleton " + skeletonFileName);
    skeletonRoot = skelFile_->GetRoot();
    
    if (skeletonRoot)
    {
        XMLElement bonesRoot = skeletonRoot.GetChild("bones");
        XMLElement bone = bonesRoot.GetChild("bone");
        while (bone)
        {
            unsigned index = bone.GetInt("id");
            String name = bone.GetAttribute("name");
            if (index >= bones_.Size())
                bones_.Resize(index + 1);
            
            // Convert from right- to left-handed
            XMLElement position = bone.GetChild("position");
            float x = position.GetFloat("x");
            float y = position.GetFloat("y");
            float z = position.GetFloat("z");
            Vector3 pos(x, y, -z);
            
            XMLElement rotation = bone.GetChild("rotation");
            XMLElement axis = rotation.GetChild("axis");
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
            bones_[index].bindScale_ = Vector3::ONE;
            bones_[index].collisionMask_ = 0;
            bones_[index].radius_ = 0.0f;
            
            bone = bone.GetNext("bone");
        }
        
        // Go through the bone hierarchy
        XMLElement boneHierarchy = skeletonRoot.GetChild("bonehierarchy");
        XMLElement boneParent = boneHierarchy.GetChild("boneparent");
        while (boneParent)
        {
            String bone = boneParent.GetAttribute("bone");
            String parent = boneParent.GetAttribute("parent");
            unsigned i = 0, j = 0;
            for (i = 0; i < bones_.Size() && bones_[i].name_ != bone; ++i);
            for (j = 0; j < bones_.Size() && bones_[j].name_ != parent; ++j);
            
            if (i >= bones_.Size() || j >= bones_.Size())
                ErrorExit("Found indeterminate parent bone assignment");
            bones_[i].parentIndex_ = j;
            
            boneParent = boneParent.GetNext("boneparent");
        }
        
        // Calculate bone derived positions
        for (unsigned i = 0; i < bones_.Size(); ++i)
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
            bones_[i].worldTransform_ = Matrix3x4(derivedPosition, derivedRotation, derivedScale);
            bones_[i].inverseWorldTransform_ = bones_[i].worldTransform_.Inverse();
        }
        
        PrintLine("Processed skeleton");
    }
}

void LoadMesh(const String& inputFileName, bool generateTangents, bool splitSubMeshes, bool exportMorphs)
{
    File meshFileSource(context_);
    meshFileSource.Open(inputFileName);
    if (!meshFile_->Load(meshFileSource))
        ErrorExit("Could not load input file " + inputFileName);
    
    XMLElement root = meshFile_->GetRoot("mesh");
    XMLElement subMeshes = root.GetChild("submeshes");
    XMLElement skeletonLink = root.GetChild("skeletonlink");
    if (root.IsNull())
        ErrorExit("Could not load input file " + inputFileName);
    
    String skeletonName = skeletonLink.GetAttribute("name");
    if (!skeletonName.Empty())
        LoadSkeleton(GetPath(inputFileName) + GetFileName(skeletonName) + ".skeleton.xml");
    
    // Check whether there's benefit of avoiding 32bit indices by splitting each submesh into own buffer
    XMLElement subMesh = subMeshes.GetChild("submesh");
    unsigned totalVertices = 0;
    unsigned maxSubMeshVertices = 0;
    while (subMesh)
    {
        materialNames_.Push(subMesh.GetAttribute("material"));
        XMLElement geometry = subMesh.GetChild("geometry");
        if (geometry)
        {
            unsigned vertices = geometry.GetInt("vertexcount");
            totalVertices += vertices;
            if (maxSubMeshVertices < vertices)
                maxSubMeshVertices = vertices;
        }
        ++numSubMeshes_;
        
        subMesh = subMesh.GetNext("submesh");
    }
    
    XMLElement sharedGeometry = root.GetChild("sharedgeometry");
    if (sharedGeometry)
    {
        unsigned vertices = sharedGeometry.GetInt("vertexcount");
        totalVertices += vertices;
        if (maxSubMeshVertices < vertices)
            maxSubMeshVertices = vertices;
    }
    
    if (!sharedGeometry && (splitSubMeshes || (totalVertices > 65535 && maxSubMeshVertices <= 65535)))
    {
        useOneBuffer_ = false;
        vertexBuffers_.Resize(numSubMeshes_);
        indexBuffers_.Resize(numSubMeshes_);
    }
    else
    {
        vertexBuffers_.Resize(1);
        indexBuffers_.Resize(1);
    }
    
    subMesh = subMeshes.GetChild("submesh");
    unsigned indexStart = 0;
    unsigned vertexStart = 0;
    unsigned subMeshIndex = 0;
    
    PODVector<unsigned> vertexStarts;
    vertexStarts.Resize(numSubMeshes_);
    
    while (subMesh)
    {
        XMLElement geometry = subMesh.GetChild("geometry");
        XMLElement faces = subMesh.GetChild("faces");
        
        // If no submesh vertexbuffer, process the shared geometry, but do it only once
        unsigned vertices = 0;
        if (!geometry)
        {
            vertexStart = 0;
            if (!subMeshIndex)
                geometry = root.GetChild("sharedgeometry");
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
                vBuf->vertices_.Resize(vertexStart + vertices);
            iBuf = &indexBuffers_[0];
            
            subGeometryLodLevel.vertexBuffer_ = 0;
            subGeometryLodLevel.indexBuffer_ = 0;
        }
        else
        {
            vertexStart = 0;
            indexStart = 0;
            
            vBuf = &vertexBuffers_[subMeshIndex];
            vBuf->vertices_.Resize(vertices);
            iBuf = &indexBuffers_[subMeshIndex];
            
            subGeometryLodLevel.vertexBuffer_ = subMeshIndex;
            subGeometryLodLevel.indexBuffer_ = subMeshIndex;
        }
        
        // Store the start vertex for later use
        vertexStarts[subMeshIndex] = vertexStart;
        
        // Ogre may have multiple buffers in one submesh. These will be merged into one
        XMLElement bufferDef;
        if (geometry)
            bufferDef = geometry.GetChild("vertexbuffer");
        
        while (bufferDef)
        {
            if (bufferDef.HasAttribute("positions"))
                vBuf->elementMask_ |= MASK_POSITION;
            if (bufferDef.HasAttribute("normals"))
                vBuf->elementMask_ |= MASK_NORMAL;
            if (bufferDef.HasAttribute("texture_coords"))
            {
                vBuf->elementMask_ |= MASK_TEXCOORD1;
                if (bufferDef.GetInt("texture_coords") > 1)
                    vBuf->elementMask_ |= MASK_TEXCOORD2;
            }
            
            unsigned vertexNum = vertexStart;
            if (vertices)
            {
                XMLElement vertex = bufferDef.GetChild("vertex");
                while (vertex)
                {
                    XMLElement position = vertex.GetChild("position");
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
                    XMLElement normal = vertex.GetChild("normal");
                    if (normal)
                    {
                        // Convert from right- to left-handed
                        float x = normal.GetFloat("x");
                        float y = normal.GetFloat("y");
                        float z = normal.GetFloat("z");
                        Vector3 vec(x, y, -z);
                        
                        vBuf->vertices_[vertexNum].normal_ = vec;
                    }
                    XMLElement uv = vertex.GetChild("texcoord");
                    if (uv)
                    {
                        float x = uv.GetFloat("u");
                        float y = uv.GetFloat("v");
                        Vector2 vec(x, y);
                        
                        vBuf->vertices_[vertexNum].texCoord1_ = vec;
                        
                        if (vBuf->elementMask_ & MASK_TEXCOORD2)
                        {
                            uv = uv.GetNext("texcoord");
                            if (uv)
                            {
                                float x = uv.GetFloat("u");
                                float y = uv.GetFloat("v");
                                Vector2 vec(x, y);
                                
                                vBuf->vertices_[vertexNum].texCoord2_ = vec;
                            }
                        }
                    }
                    
                    vertexNum++;
                    vertex = vertex.GetNext("vertex");
                }
            }
            
            bufferDef = bufferDef.GetNext("vertexbuffer");
        }
        
        unsigned triangles = faces.GetInt("count");
        unsigned indices = triangles * 3;
        
        XMLElement triangle = faces.GetChild("face");
        while (triangle)
        {
            unsigned v1 = triangle.GetInt("v1");
            unsigned v2 = triangle.GetInt("v2");
            unsigned v3 = triangle.GetInt("v3");
            iBuf->indices_.Push(v3 + vertexStart);
            iBuf->indices_.Push(v2 + vertexStart);
            iBuf->indices_.Push(v1 + vertexStart);
            triangle = triangle.GetNext("face");
        }
        
        subGeometryLodLevel.indexStart_ = indexStart;
        subGeometryLodLevel.indexCount_ = indices;
        if (vertexStart + vertices > 65535)
            iBuf->indexSize_ = sizeof(unsigned);
        
        XMLElement boneAssignments = subMesh.GetChild("boneassignments");
        if (bones_.Size())
        {
            if (boneAssignments)
            {
                XMLElement boneAssignment = boneAssignments.GetChild("vertexboneassignment");
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
                        subGeometryLodLevel.boneWeights_[vertex].Push(assign);
                        
                        // Require skinning weight to be sufficiently large before vertex contributes to bone hitbox
                        if (assign.weight_ > 0.33f)
                        {
                            // Check distance of vertex from bone to get bone max. radius information
                            Vector3 bonePos = bones_[bone].derivedPosition_;
                            Vector3 vertexPos = vBuf->vertices_[vertex].position_;
                            float distance = (bonePos - vertexPos).Length();
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
                    boneAssignment = boneAssignment.GetNext("vertexboneassignment");
                }
            }
            
            if ((subGeometryLodLevel.boneWeights_.Size()) && bones_.Size())
            {
                vBuf->elementMask_ |= MASK_BLENDWEIGHTS | MASK_BLENDINDICES;
                bool sorted = false;
                
                // If amount of bones is larger than supported by HW skinning, must remap per submesh
                if (bones_.Size() > MAX_SKIN_MATRICES)
                {
                    HashMap<unsigned, unsigned> usedBoneMap;
                    unsigned remapIndex = 0;
                    for (HashMap<unsigned, PODVector<BoneWeightAssignment> >::Iterator i =
                        subGeometryLodLevel.boneWeights_.Begin(); i != subGeometryLodLevel.boneWeights_.End(); ++i)
                    {
                        // Sort the bone assigns by weight
                        Sort(i->second_.Begin(), i->second_.End(), CompareWeights);
                        
                        // Use only the first 4 weights
                        for (unsigned j = 0; j < i->second_.Size() && j < 4; ++j)
                        {
                            unsigned originalIndex = i->second_[j].boneIndex_;
                            if (!usedBoneMap.Contains(originalIndex))
                            {
                                usedBoneMap[originalIndex] = remapIndex;
                                remapIndex++;
                            }
                            i->second_[j].boneIndex_ = usedBoneMap[originalIndex];
                        }
                    }
                    
                    // If still too many bones in one subgeometry, error
                    if (usedBoneMap.Size() > MAX_SKIN_MATRICES)
                        ErrorExit("Too many bones in submesh " + String(subMeshIndex + 1));
                    
                    // Write mapping of vertex buffer bone indices to original bone indices
                    subGeometryLodLevel.boneMapping_.Resize(usedBoneMap.Size());
                    for (HashMap<unsigned, unsigned>::Iterator j = usedBoneMap.Begin(); j != usedBoneMap.End(); ++j)
                        subGeometryLodLevel.boneMapping_[j->second_] = j->first_;
                    
                    sorted = true;
                }
                
                for (HashMap<unsigned, PODVector<BoneWeightAssignment> >::Iterator i = subGeometryLodLevel.boneWeights_.Begin();
                    i != subGeometryLodLevel.boneWeights_.End(); ++i)
                {
                    // Sort the bone assigns by weight, if not sorted yet in bone remapping pass
                    if (!sorted)
                        Sort(i->second_.Begin(), i->second_.End(), CompareWeights);
                    
                    float totalWeight = 0.0f;
                    float normalizationFactor = 0.0f;
                    
                    // Calculate normalization factor in case there are more than 4 blend weights, or they do not add up to 1
                    for (unsigned j = 0; j < i->second_.Size() && j < 4; ++j)
                        totalWeight += i->second_[j].weight_;
                    if (totalWeight > 0.0f)
                        normalizationFactor = 1.0f / totalWeight;
                    
                    for (unsigned j = 0; j < i->second_.Size() && j < 4; ++j)
                    {
                        vBuf->vertices_[i->first_].blendIndices_[j] = i->second_[j].boneIndex_;
                        vBuf->vertices_[i->first_].blendWeights_[j] = i->second_[j].weight_ * normalizationFactor;
                    }
                    
                    // If there are less than 4 blend weights, fill rest with zero
                    for (unsigned j = i->second_.Size(); j < 4; ++j)
                    {
                        vBuf->vertices_[i->first_].blendIndices_[j] = 0;
                        vBuf->vertices_[i->first_].blendWeights_[j] = 0.0f;
                    }
                    
                    vBuf->vertices_[i->first_].hasBlendWeights_ = true;
                }
            }
        }
        else if (boneAssignments)
            PrintLine("No skeleton loaded, skipping skinning information");
        
        // Calculate center for the subgeometry
        Vector3 center = Vector3::ZERO;
        for (unsigned i = 0; i < iBuf->indices_.Size(); i += 3)
        {
            center += vBuf->vertices_[iBuf->indices_[i]].position_;
            center += vBuf->vertices_[iBuf->indices_[i + 1]].position_;
            center += vBuf->vertices_[iBuf->indices_[i + 2]].position_;
        }
        if (iBuf->indices_.Size())
            center /= (float)iBuf->indices_.Size();
        subGeometryCenters_.Push(center);
        
        indexStart += indices;
        vertexStart += vertices;
        
        OptimizeIndices(&subGeometryLodLevel, vBuf, iBuf);
        
        PrintLine("Processed submesh " + String(subMeshIndex + 1) + ": " + String(vertices) + " vertices " + 
            String(triangles) + " triangles");
        Vector<ModelSubGeometryLodLevel> thisSubGeometry;
        thisSubGeometry.Push(subGeometryLodLevel);
        subGeometries_.Push(thisSubGeometry);
        
        subMesh = subMesh.GetNext("submesh");
        subMeshIndex++;
    }
    
    // Process LOD levels, if any
    XMLElement lods = root.GetChild("levelofdetail");
    if (lods)
    {
        try
        {
            // For now, support only generated LODs, where the vertices are the same
            XMLElement lod = lods.GetChild("lodgenerated");
            while (lod)
            {
                float distance = M_EPSILON;
                if (lod.HasAttribute("fromdepthsquared"))
                    distance = sqrtf(lod.GetFloat("fromdepthsquared"));
                if (lod.HasAttribute("value"))
                    distance = lod.GetFloat("value");
                XMLElement lodSubMesh = lod.GetChild("lodfacelist");
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
                    
                    unsigned indexStart = iBuf->indices_.Size();
                    unsigned indexCount = triangles * 3;
                    unsigned vertexStart = vertexStarts[subMeshIndex];
                    
                    newLodLevel.distance_ = distance;
                    newLodLevel.indexStart_ = indexStart;
                    newLodLevel.indexCount_ = indexCount;
                    
                    // Append indices to the original index buffer
                    XMLElement triangle = lodSubMesh.GetChild("face");
                    while (triangle)
                    {
                        unsigned v1 = triangle.GetInt("v1");
                        unsigned v2 = triangle.GetInt("v2");
                        unsigned v3 = triangle.GetInt("v3");
                        iBuf->indices_.Push(v3 + vertexStart);
                        iBuf->indices_.Push(v2 + vertexStart);
                        iBuf->indices_.Push(v1 + vertexStart);
                        triangle = triangle.GetNext("face");
                    }
                    
                    OptimizeIndices(&newLodLevel, vBuf, iBuf);
                    
                    subGeometries_[subMeshIndex].Push(newLodLevel);
                    PrintLine("Processed LOD level for submesh " + String(subMeshIndex + 1) + ": distance " + String(distance));
                    
                    lodSubMesh = lodSubMesh.GetNext("lodfacelist");
                }
                lod = lod.GetNext("lodgenerated");
            }
        }
        catch (...) {}
    }
    
    // Process poses/morphs
    // First find out all pose definitions
    if (exportMorphs)
    {
        try
        {
            Vector<XMLElement> poses;
            XMLElement posesRoot = root.GetChild("poses");
            if (posesRoot)
            {
                XMLElement pose = posesRoot.GetChild("pose");
                while (pose)
                {
                    poses.Push(pose);
                    pose = pose.GetNext("pose");
                }
            }
            
            // Then process animations using the poses
            XMLElement animsRoot = root.GetChild("animations");
            if (animsRoot)
            {
                XMLElement anim = animsRoot.GetChild("animation");
                while (anim)
                {
                    String name = anim.GetAttribute("name");
                    float length = anim.GetFloat("length");
                    HashSet<unsigned> usedPoses;
                    XMLElement tracks = anim.GetChild("tracks");
                    if (tracks)
                    {
                        XMLElement track = tracks.GetChild("track");
                        while (track)
                        {
                            XMLElement keyframes = track.GetChild("keyframes");
                            if (keyframes)
                            {
                                XMLElement keyframe = keyframes.GetChild("keyframe");
                                while (keyframe)
                                {
                                    float time = keyframe.GetFloat("time");
                                    XMLElement poseref = keyframe.GetChild("poseref");
                                    // Get only the end pose
                                    if (poseref && time == length)
                                        usedPoses.Insert(poseref.GetInt("poseindex"));
                                    
                                    keyframe = keyframe.GetNext("keyframe");
                                }
                            }
                            track = track.GetNext("track");
                        }
                    }
                    
                    if (usedPoses.Size())
                    {
                        ModelMorph newMorph;
                        newMorph.name_ = name;
                        
                        if (useOneBuffer_)
                            newMorph.buffers_.Resize(1);
                        else
                            newMorph.buffers_.Resize(usedPoses.Size());
                        
                        unsigned bufIndex = 0;
                        
                        for (HashSet<unsigned>::Iterator i = usedPoses.Begin(); i != usedPoses.End(); ++i)
                        {
                            XMLElement pose = poses[*i];
                            unsigned targetSubMesh = pose.GetInt("index");
                            XMLElement poseOffset = pose.GetChild("poseoffset");
                        
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
                                newMorph.buffers_[bufIndex].vertices_.Push(MakePair(vertexIndex, newVertex));
                                poseOffset = poseOffset.GetNext("poseoffset");
                            }
                            
                            if (!useOneBuffer_)
                                ++bufIndex;
                        }
                        morphs_.Push(newMorph);
                        PrintLine("Processed morph " + name + " with " + String(usedPoses.Size()) + " sub-poses");
                    }
                    
                    anim = anim.GetNext("animation");
                }
            }
        }
        catch (...) {}
    }
    
    // Check any of the buffers for vertices with missing blend weight assignments
    for (unsigned i = 0; i < vertexBuffers_.Size(); ++i)
    {
        if (vertexBuffers_[i].elementMask_ & MASK_BLENDWEIGHTS)
        {
            for (unsigned j = 0; j < vertexBuffers_[i].vertices_.Size(); ++j)
                if (!vertexBuffers_[i].vertices_[j].hasBlendWeights_)
                    ErrorExit("Found a vertex with missing skinning information");
        }
    }
    
    // Tangent generation
    if (generateTangents)
    {
        for (unsigned i = 0; i < subGeometries_.Size(); ++i)
        {
            for (unsigned j = 0; j < subGeometries_[i].Size(); ++j)
            {
                ModelVertexBuffer& vBuf = vertexBuffers_[subGeometries_[i][j].vertexBuffer_];
                ModelIndexBuffer& iBuf = indexBuffers_[subGeometries_[i][j].indexBuffer_];
                unsigned indexStart = subGeometries_[i][j].indexStart_;
                unsigned indexCount = subGeometries_[i][j].indexCount_;
                
                // If already has tangents, do not regenerate
                if (vBuf.elementMask_ & MASK_TANGENT || vBuf.vertices_.Empty() || iBuf.indices_.Empty())
                    continue;
                
                vBuf.elementMask_ |= MASK_TANGENT;
                
                if ((vBuf.elementMask_ & (MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1)) != (MASK_POSITION | MASK_NORMAL |
                    MASK_TEXCOORD1))
                    ErrorExit("To generate tangents, positions normals and texcoords are required");
                
                GenerateTangents(&vBuf.vertices_[0], sizeof(ModelVertex), &iBuf.indices_[0], sizeof(unsigned), indexStart,
                    indexCount, offsetof(ModelVertex, normal_), offsetof(ModelVertex, texCoord1_), offsetof(ModelVertex,
                    tangent_));
                
                PrintLine("Generated tangents");
            }
        }
    }
}

void WriteOutput(const String& outputFileName, bool exportAnimations, bool rotationsOnly, bool saveMaterialList)
{
    // Begin serialization
    {
        File dest(context_);
        if (!dest.Open(outputFileName, FILE_WRITE))
            ErrorExit("Could not open output file " + outputFileName);
        
        // ID
        dest.WriteFileID("UMDL");
        
        // Vertexbuffers
        dest.WriteUInt(vertexBuffers_.Size());
        for (unsigned i = 0; i < vertexBuffers_.Size(); ++i)
            vertexBuffers_[i].WriteData(dest);
        
        // Indexbuffers
        dest.WriteUInt(indexBuffers_.Size());
        for (unsigned i = 0; i < indexBuffers_.Size(); ++i)
            indexBuffers_[i].WriteData(dest);
        
        // Subgeometries
        dest.WriteUInt(subGeometries_.Size());
        for (unsigned i = 0; i < subGeometries_.Size(); ++i)
        {
            // Write bone mapping info from the first LOD level. It does not change for further LODs
            dest.WriteUInt(subGeometries_[i][0].boneMapping_.Size());
            for (unsigned k = 0; k < subGeometries_[i][0].boneMapping_.Size(); ++k)
                dest.WriteUInt(subGeometries_[i][0].boneMapping_[k]);
            
            // Lod levels for this subgeometry
            dest.WriteUInt(subGeometries_[i].Size());
            for (unsigned j = 0; j < subGeometries_[i].Size(); ++j)
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
        dest.WriteUInt(morphs_.Size());
        for (unsigned i = 0; i < morphs_.Size(); ++i)
            morphs_[i].WriteData(dest);
        
        // Skeleton
        dest.WriteUInt(bones_.Size());
        for (unsigned i = 0; i < bones_.Size(); ++i)
        {
            dest.WriteString(bones_[i].name_);
            dest.WriteUInt(bones_[i].parentIndex_);
            dest.WriteVector3(bones_[i].bindPosition_);
            dest.WriteQuaternion(bones_[i].bindRotation_);
            dest.WriteVector3(bones_[i].bindScale_);
            
            Matrix3x4 offsetMatrix(bones_[i].derivedPosition_, bones_[i].derivedRotation_, bones_[i].derivedScale_);
            offsetMatrix = offsetMatrix.Inverse();
            dest.Write(offsetMatrix.Data(), sizeof(Matrix3x4));
            
            dest.WriteUByte(bones_[i].collisionMask_);
            if (bones_[i].collisionMask_ & 1)
                dest.WriteFloat(bones_[i].radius_);
            if (bones_[i].collisionMask_ & 2)
                dest.WriteBoundingBox(bones_[i].boundingBox_);
        }
        
        // Bounding box
        dest.WriteBoundingBox(boundingBox_);
        
        // Geometry centers
        for (unsigned i = 0; i < subGeometryCenters_.Size(); ++i)
            dest.WriteVector3(subGeometryCenters_[i]);
    }
    
    if (saveMaterialList)
    {
        String materialListName = ReplaceExtension(outputFileName, ".txt");
        File listFile(context_);
        if (listFile.Open(materialListName, FILE_WRITE))
        {
            for (unsigned i = 0; i < materialNames_.Size(); ++i)
            {
                // Assume the materials will be located inside the standard Materials subdirectory
                listFile.WriteLine("Materials/" + ReplaceExtension(SanitateAssetName(materialNames_[i]), ".xml"));
            }
        }
        else
            PrintLine("Warning: could not write material list file " + materialListName);
    }
    
    XMLElement skeletonRoot = skelFile_->GetRoot("skeleton");
    if (skeletonRoot && exportAnimations)
    {
        // Go through animations
        XMLElement animationsRoot = skeletonRoot.GetChild("animations");
        if (animationsRoot)
        {
            XMLElement animation = animationsRoot.GetChild("animation");
            while (animation)
            {
                ModelAnimation newAnimation;
                newAnimation.name_ = animation.GetAttribute("name");
                newAnimation.length_ = animation.GetFloat("length");
                
                XMLElement tracksRoot = animation.GetChild("tracks");
                XMLElement track = tracksRoot.GetChild("track");
                while (track)
                {
                    String trackName = track.GetAttribute("bone");
                    ModelBone* bone = 0;
                    for (unsigned i = 0; i < bones_.Size(); ++i)
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
                    
                    XMLElement keyFramesRoot = track.GetChild("keyframes");
                    XMLElement keyFrame = keyFramesRoot.GetChild("keyframe");
                    while (keyFrame)
                    {
                        AnimationKeyFrame newKeyFrame;
                        
                        // Convert from right- to left-handed
                        XMLElement position = keyFrame.GetChild("translate");
                        float x = position.GetFloat("x");
                        float y = position.GetFloat("y");
                        float z = position.GetFloat("z");
                        Vector3 pos(x, y, -z);
                        
                        XMLElement rotation = keyFrame.GetChild("rotate");
                        XMLElement axis = rotation.GetChild("axis");
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
                        
                        newAnimationTrack.keyFrames_.Push(newKeyFrame);
                        keyFrame = keyFrame.GetNext("keyframe");
                    }
                    
                    // Make sure keyframes are sorted from beginning to end
                    Sort(newAnimationTrack.keyFrames_.Begin(), newAnimationTrack.keyFrames_.End(), CompareKeyFrames);
                    
                    // Do not add tracks with no keyframes
                    if (newAnimationTrack.keyFrames_.Size())
                        newAnimation.tracks_.Push(newAnimationTrack);
                    
                    track = track.GetNext("track");
                }
                
                // Write each animation into a separate file
                String animationFileName = outputFileName.Replaced(".mdl", "");
                animationFileName += "_" + newAnimation.name_ + ".ani";
                
                File dest(context_);
                if (!dest.Open(animationFileName, FILE_WRITE))
                    ErrorExit("Could not open output file " + animationFileName);
                
                dest.WriteFileID("UANI");
                dest.WriteString(newAnimation.name_);
                dest.WriteFloat(newAnimation.length_);
                dest.WriteUInt(newAnimation.tracks_.Size());
                for (unsigned i = 0; i < newAnimation.tracks_.Size(); ++i)
                {
                    AnimationTrack& track = newAnimation.tracks_[i];
                    dest.WriteString(track.name_);
                    dest.WriteUByte(track.channelMask_);
                    dest.WriteUInt(track.keyFrames_.Size());
                    for (unsigned j = 0; j < track.keyFrames_.Size(); ++j)
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
                
                animation = animation.GetNext("animation");
                PrintLine("Processed animation " + newAnimation.name_);
            }
        }
    }
}

void OptimizeIndices(ModelSubGeometryLodLevel* subGeom, ModelVertexBuffer* vb, ModelIndexBuffer* ib)
{
    PODVector<Triangle> oldTriangles;
    PODVector<Triangle> newTriangles;
    
    if (subGeom->indexCount_ % 3)
    {
        PrintLine("Index count is not divisible by 3, skipping index optimization");
        return;
    }
    
    for (unsigned i = 0; i < vb->vertices_.Size(); ++i)
    {
        vb->vertices_[i].useCount_ = 0;
        vb->vertices_[i].cachePosition_ = -1;
    }
    
    for (unsigned i = subGeom->indexStart_; i < subGeom->indexStart_ + subGeom->indexCount_; i += 3)
    {
        Triangle triangle;
        triangle.v0_ = ib->indices_[i];
        triangle.v1_ = ib->indices_[i + 1];
        triangle.v2_ = ib->indices_[i + 2];
        vb->vertices_[triangle.v0_].useCount_++;
        vb->vertices_[triangle.v1_].useCount_++;
        vb->vertices_[triangle.v2_].useCount_++;
        oldTriangles.Push(triangle);
    }
    
    for (unsigned i = 0; i < vb->vertices_.Size(); ++i)
        CalculateScore(vb->vertices_[i]);
    
    PODVector<unsigned> vertexCache;
    
    while (oldTriangles.Size())
    {
        unsigned bestTriangle = M_MAX_UNSIGNED;
        float bestTriangleScore = -1.0f;
        
        // Find the best triangle at this point
        for (unsigned i = 0; i < oldTriangles.Size(); ++i)
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
        {
            PrintLine("Could not find next triangle, aborting index optimization");
            return;
        }
        
        // Add the best triangle
        Triangle triangleCopy = oldTriangles[bestTriangle];
        newTriangles.Push(triangleCopy);
        oldTriangles.Erase(oldTriangles.Begin() + bestTriangle);
        
        // Reduce the use count
        vb->vertices_[triangleCopy.v0_].useCount_--;
        vb->vertices_[triangleCopy.v1_].useCount_--;
        vb->vertices_[triangleCopy.v2_].useCount_--;
        
        // Model the LRU cache behaviour
        // Erase the triangle vertices from the middle of the cache, if they were there
        for (unsigned i = 0; i < vertexCache.Size(); ++i)
        {
            if ((vertexCache[i] == triangleCopy.v0_) ||
                (vertexCache[i] == triangleCopy.v1_) ||
                (vertexCache[i] == triangleCopy.v2_))
            {
                vertexCache.Erase(vertexCache.Begin() + i);
                --i;
            }
        }
        
        // Then push them to the front
        vertexCache.Insert(vertexCache.Begin(), triangleCopy.v0_);
        vertexCache.Insert(vertexCache.Begin(), triangleCopy.v1_);
        vertexCache.Insert(vertexCache.Begin(), triangleCopy.v2_);
        
        // Update positions & scores of all vertices in the cache
        // Give position -1 if vertex is going to be erased
        for (unsigned i = 0; i < vertexCache.Size(); ++i)
        {
            ModelVertex& vertex = vb->vertices_[vertexCache[i]];
            if (i >= VERTEX_CACHE_SIZE)
                vertex.cachePosition_ = -1;
            else
                vertex.cachePosition_ = i;
            CalculateScore(vertex);
        }
        
        // Finally erase the extra vertices
        if (vertexCache.Size() > VERTEX_CACHE_SIZE)
            vertexCache.Resize(VERTEX_CACHE_SIZE);
    }
    
    // Rewrite the index data now
    unsigned i = subGeom->indexStart_;
    for (unsigned j = 0; j < newTriangles.Size(); ++j)
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
