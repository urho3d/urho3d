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

#include "Precompiled.h"
#include "CollisionShape.h"
#include "Geometry.h"
#include "Log.h"
#include "Model.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include <ode/ode.h>
#include <hull.h>

#include "DebugNew.h"

std::map<std::string, SharedPtr<TriangleMeshData> > CollisionShape::sTriangleMeshCache;
std::map<std::string, SharedPtr<HeightfieldData> > CollisionShape::sHeightfieldCache;

void getVertexAndIndexData(const Model* model, unsigned lodLevel, SharedArrayPtr<Vector3>& destVertexData, unsigned& destVertexCount, SharedArrayPtr<unsigned>& destIndexData, unsigned& destIndexCount)
{
    const std::vector<std::vector<SharedPtr<Geometry> > >& geometries = model->getGeometries();
    
    destVertexCount = 0;
    destIndexCount = 0;
    
    for (unsigned i = 0; i < geometries.size(); ++i)
    {
        unsigned subGeometryLodLevel = lodLevel;
        if (subGeometryLodLevel >= geometries[i].size())
            subGeometryLodLevel = geometries[i].size() / 2;
        
        Geometry* geom = geometries[i][subGeometryLodLevel];
        if (!geom)
            EXCEPTION("Null geometry for CollisionShape");
        
        destVertexCount += geom->getVertexCount();
        destIndexCount += geom->getIndexCount();
    }
    
    destVertexData = new Vector3[destVertexCount];
    destIndexData = new unsigned[destIndexCount];
    
    unsigned firstVertex = 0;
    unsigned firstIndex = 0;
    
    for (unsigned i = 0; i < geometries.size(); ++i)
    {
        unsigned subGeometryLodLevel = lodLevel;
        if (subGeometryLodLevel >= geometries[i].size())
            subGeometryLodLevel = geometries[i].size() / 2;
        
        Geometry* geom = geometries[i][subGeometryLodLevel];
        if (!geom)
            EXCEPTION("Null geometry for CollisionShape");
        
        const unsigned char* vertexData;
        const unsigned char* indexData;
        unsigned vertexSize;
        unsigned indexSize;
        
        geom->lockRawData(vertexData, vertexSize, indexData, indexSize);
        if ((!vertexData) || (!indexData))
            EXCEPTION("Raw geometry data unavailable for CollisionShape");
        
        unsigned vertexStart = geom->getVertexStart();
        unsigned vertexCount = geom->getVertexCount();
        
        // Copy vertex data
        for (unsigned j = 0; j < vertexCount; ++j)
        {
            const Vector3& v = *((const Vector3*)(&vertexData[(vertexStart + j) * vertexSize]));
            destVertexData[firstVertex + j] = v;
        }
        
        unsigned indexStart = geom->getIndexStart();
        unsigned indexCount = geom->getIndexCount();
        
        // 16-bit indices
        if (indexSize == sizeof(unsigned short))
        {
            const unsigned short* indices = (const unsigned short*)indexData;
            
            for (unsigned j = 0; j < indexCount; j += 3)
            {
                // Rebase the indices according to our vertex numbering
                destIndexData[firstIndex + j] = indices[indexStart + j] - vertexStart + firstVertex;
                destIndexData[firstIndex + j + 1] = indices[indexStart + j + 1] - vertexStart + firstVertex;
                destIndexData[firstIndex + j + 2] = indices[indexStart + j + 2] - vertexStart + firstVertex;
            }
        }
        // 32-bit indices
        else
        {
            const unsigned* indices = (const unsigned*)indexData;
            
            for (unsigned j = 0; j < indexCount; j += 3)
            {
                // Rebase the indices according to our vertex numbering
                destIndexData[firstIndex + j] = indices[indexStart + j] - vertexStart + firstVertex;
                destIndexData[firstIndex + j + 1] = indices[indexStart + j + 1] - vertexStart + firstVertex;
                destIndexData[firstIndex + j + 2] = indices[indexStart + j + 2] - vertexStart + firstVertex;
            }
        }
        
        firstVertex += vertexCount;
        firstIndex += indexCount;
        
        geom->unlockRawData();
    }
}

TriangleMeshData::TriangleMeshData(const Model* model, bool makeConvexHull, float skinWidth, unsigned lodLevel) :
    mTriMesh(0),
    mVertexCount(0),
    mIndexCount(0)
{
    if (!model)
        EXCEPTION("Null model for TriangleMeshData");
    
    if (!makeConvexHull)
    {
        mID = model->getName() + toString(lodLevel);
        getVertexAndIndexData(model, lodLevel, mVertexData, mVertexCount, mIndexData, mIndexCount);
    }
    else
    {
        mID = model->getName() + toString(lodLevel) + "hull" + toString(skinWidth);
        
        SharedArrayPtr<Vector3> originalVertices;
        SharedArrayPtr<unsigned> originalIndices;
        unsigned originalVertexCount;
        unsigned originalIndexCount;
        
        getVertexAndIndexData(model, lodLevel, originalVertices, originalVertexCount, originalIndices, originalIndexCount);
        
        // Build the convex hull from the raw geometry
        StanHull::HullDesc desc;
        desc.SetHullFlag(StanHull::QF_TRIANGLES);
        desc.mVcount = originalVertexCount;
        desc.mVertices = (float*)originalVertices.getPtr();
        desc.mVertexStride = 3 * sizeof(float);
        
        StanHull::HullLibrary lib;
        StanHull::HullResult result;
        lib.CreateConvexHull(desc, result);
    
        mVertexCount = result.mNumOutputVertices;
        mIndexCount = result.mNumIndices;
        
        // Copy vertex data
        mVertexData = new Vector3[mVertexCount];
        memcpy(mVertexData.getPtr(), result.mOutputVertices, mVertexCount * sizeof(Vector3));
        
        // Copy index data
        mIndexData = new unsigned[mIndexCount];
        memcpy(mIndexData.getPtr(), result.mIndices, mIndexCount * sizeof(unsigned));
    }
    
    mTriMesh = dGeomTriMeshDataCreate();
    
    dGeomTriMeshDataBuildSingle(mTriMesh, mVertexData.getPtr(), sizeof(Vector3), mVertexCount,
        mIndexData.getPtr(), mIndexCount, 3 * sizeof(unsigned));
    
    mMemoryUse = sizeof(TriangleMeshData) + mVertexCount * sizeof(Vector3) + mIndexCount * sizeof(unsigned);
}

TriangleMeshData::TriangleMeshData(const TriangleMeshData* source, const Vector3& scale) :
    mTriMesh(0)
{
    if (!source)
        EXCEPTION("Null TriangleMeshData source");
    
    mID = source->mID + toString(scale);
    
    mVertexCount = source->mVertexCount;
    mIndexCount = source->mIndexCount;
    mVertexData = new Vector3[mVertexCount];
    mIndexData = source->mIndexData;
    
    // Copy and scale vertex data
    for (unsigned i = 0; i < mVertexCount; ++i)
        mVertexData[i] = scale * source->mVertexData[i];
    
    mTriMesh = dGeomTriMeshDataCreate();
    
    dGeomTriMeshDataBuildSingle(mTriMesh, mVertexData.getPtr(), sizeof(Vector3), mVertexCount,
        mIndexData.getPtr(), mIndexCount, 3 * sizeof(unsigned));
    
    // Indices are re-used, so account only for the scaled vertices
    mMemoryUse = sizeof(TriangleMeshData) + mVertexCount * sizeof(Vector3);
}

TriangleMeshData::~TriangleMeshData()
{
    if (mTriMesh)
    {
        dGeomTriMeshDataDestroy(mTriMesh);
        mTriMesh = 0;
    }
}

HeightfieldData::HeightfieldData(const Model* model, unsigned xPoints, unsigned zPoints, float thickness, unsigned lodLevel) :
    mHeightfield(0),
    mThickness(thickness)
{
    if (!model)
        EXCEPTION("Null model for HeightfieldData");
    
    mID = model->getName() + toString(mThickness) + toString(lodLevel);
    
    const std::vector<std::vector<SharedPtr<Geometry> > >& geometries = model->getGeometries();
    
    if (!geometries.size())
        EXCEPTION("No geometries for HeightfieldData");
    
    if (lodLevel >= geometries[0].size())
        lodLevel = geometries[0].size() / 2;
    
    Geometry* geom = geometries[0][lodLevel];
    if (!geom)
        EXCEPTION("Null geometry for HeightfieldData");
    
    const unsigned char* vertexData;
    const unsigned char* indexData;
    unsigned vertexSize;
    unsigned indexSize;
    
    geom->lockRawData(vertexData, vertexSize, indexData, indexSize);
    if ((!vertexData) || (!indexData))
        EXCEPTION("Raw geometry data unavailable");
    
    unsigned indexStart = geom->getIndexStart();
    unsigned indexCount = geom->getIndexCount();
    
    // If x & z size not specified, try to guess them
    if ((!xPoints) || (!zPoints))
        xPoints = zPoints = (int)sqrtf((float)geom->getVertexCount());
    
    // Then allocate the heightfield
    mXPoints = xPoints;
    mZPoints = zPoints;
    mBoundingBox = model->getBoundingBox();
    mHeightData = new float[xPoints * zPoints];
    
    // Calculate spacing from model's bounding box
    float xSpacing = (mBoundingBox.mMax.mX - mBoundingBox.mMin.mX) / (xPoints - 1);
    float zSpacing = (mBoundingBox.mMax.mZ - mBoundingBox.mMin.mZ) / (zPoints - 1);
    
    // Initialize the heightfield with minimum height
    for (unsigned i = 0; i < xPoints * zPoints; ++i)
        mHeightData[i] = mBoundingBox.mMin.mY;
    
    unsigned vertexStart = geom->getVertexStart();
    unsigned vertexCount = geom->getVertexCount();
    
    // Now go through vertex data and fit the vertices into the heightfield
    for (unsigned i = vertexStart; i < vertexStart + vertexCount; ++i)
    {
        const Vector3& vertex = *((const Vector3*)(&vertexData[i * vertexSize]));
        unsigned x = (int)((vertex.mX - mBoundingBox.mMin.mX) / xSpacing + 0.25f);
        unsigned z = (int)((vertex.mZ - mBoundingBox.mMin.mZ) / zSpacing + 0.25f);
        if (x >= xPoints)
            x = xPoints - 1;
        if (z >= zPoints)
            z = zPoints - 1;
        if (vertex.mY > mHeightData[z * xPoints + x])
            mHeightData[z * xPoints + x] = vertex.mY;
    }
    
    geom->unlockRawData();
    
    mHeightfield = dGeomHeightfieldDataCreate();
    
    dGeomHeightfieldDataBuildSingle(mHeightfield, mHeightData.getPtr(), 0, mBoundingBox.mMax.mX - mBoundingBox.mMin.mX,
        mBoundingBox.mMax.mZ - mBoundingBox.mMin.mZ, mXPoints, mZPoints, 1.0f, 0.0f, mThickness, 0);
    dGeomHeightfieldDataSetBounds(mHeightfield, mBoundingBox.mMin.mY, mBoundingBox.mMax.mY);
    
    mMemoryUse = sizeof(HeightfieldData) + mXPoints * mZPoints * sizeof(float);
}

HeightfieldData::HeightfieldData(const HeightfieldData* source, const Vector3& scale) :
    mHeightfield(0)
{
    if (!source)
        EXCEPTION("Null HeightfieldData source");
    
    mID = source->mID + toString(scale);
    
    mXPoints = source->mXPoints;
    mZPoints = source->mZPoints;
    mThickness = source->mThickness * scale.mY;
    mBoundingBox = source->mBoundingBox;
    mHeightData = new float[mXPoints * mZPoints];
    
    // Adjust bounding box, and copy & scale the height data
    mBoundingBox.mMin *= scale;
    mBoundingBox.mMax *= scale;
    for (unsigned i = 0; i < mXPoints * mZPoints; ++i)
        mHeightData[i] = source->mHeightData[i] * scale.mY;
    
    mHeightfield = dGeomHeightfieldDataCreate();
    
    dGeomHeightfieldDataBuildSingle(mHeightfield, mHeightData.getPtr(), 0, mBoundingBox.mMax.mX - mBoundingBox.mMin.mX,
        mBoundingBox.mMax.mZ - mBoundingBox.mMin.mZ, mXPoints, mZPoints, 1.0f, 0.0f, mThickness, 0);
    dGeomHeightfieldDataSetBounds(mHeightfield, mBoundingBox.mMin.mY, mBoundingBox.mMax.mY);
    
    mMemoryUse = sizeof(HeightfieldData) + mXPoints * mZPoints * sizeof(float);
}

HeightfieldData::~HeightfieldData()
{
    if (mHeightfield)
    {
        dGeomHeightfieldDataDestroy(mHeightfield);
        mHeightfield = 0;
    }
}

CollisionShape::CollisionShape(const std::string& name) :
    Resource(name)
{
}

CollisionShape::~CollisionShape()
{
    clear();
}

void CollisionShape::load(Deserializer& source, ResourceCache* cache)
{
    clear();
    
    XMLFile xml;
    xml.load(source, cache);
    
    XMLElement rootElem = xml.getRootElement();
    XMLElement shapeElem = rootElem.getChildElement("");
    while (shapeElem)
    {
        std::string type = shapeElem.getName();
        Vector3 position = Vector3::sZero;
        Quaternion rotation = Quaternion::sIdentity;
        if (shapeElem.hasAttribute("position"))
            position = shapeElem.getVector3("position");
        if (shapeElem.hasAttribute("rotation"))
            rotation = shapeElem.getQuaternion("rotation");
        
        if (type == "sphere")
            addSphere(shapeElem.getFloat("radius"), position, rotation);
        
        if (type == "box")
        {
            Vector3 size = Vector3::sZero;
            
            if (shapeElem.hasAttribute("size"))
                size = shapeElem.getVector3("size");
            else if (shapeElem.hasAttribute("halfsize"))
                size = shapeElem.getVector3("halfsize") * 2.0f;
            addBox(size, position, rotation);
        }
        
        if (type == "cylinder")
            addCylinder(shapeElem.getFloat("radius"), shapeElem.getFloat("height"), position, rotation);
        
        if (type == "capsule")
            addCapsule(shapeElem.getFloat("radius"), shapeElem.getFloat("height"), position, rotation);
        
        if (type == "trianglemesh")
        {
            Model* model = cache->getResource<Model>(shapeElem.getString("name"));
            unsigned lodLevel = model->getCollisionLodLevel();
            if (shapeElem.hasAttribute("lodlevel"))
                lodLevel = shapeElem.getInt("lodlevel");
            addTriangleMesh(model, lodLevel, position, rotation);
        }
        
        if (type == "heightfield")
        {
            Model* model = cache->getResource<Model>(shapeElem.getString("name"));
            unsigned xSize = 0;
            unsigned zSize = 0;
            float thickness = 1.0f;
            unsigned lodLevel = model->getCollisionLodLevel();
            if (shapeElem.hasAttribute("xsize"))
                xSize = shapeElem.getInt("xsize");
            if (shapeElem.hasAttribute("zsize"))
                zSize = shapeElem.getInt("zsize");
            if (shapeElem.hasAttribute("xpoints"))
                xSize = shapeElem.getInt("xpoints");
            if (shapeElem.hasAttribute("zpoints"))
                zSize = shapeElem.getInt("zpoints");
            if (shapeElem.hasAttribute("lodlevel"))
                lodLevel = shapeElem.getInt("lodlevel");
            if (shapeElem.hasAttribute("thickness"))
                thickness = shapeElem.getFloat("thickness");
            addHeightfield(model, xSize, zSize, thickness, lodLevel, position, rotation);
        }
        
        if (type == "convexhull")
        {
            Model* model = cache->getResource<Model>(shapeElem.getString("name"));
            unsigned lodLevel = model->getCollisionLodLevel();
            float skinWidth = 0.0f;
            if (shapeElem.hasAttribute("lodlevel"))
                lodLevel = shapeElem.getInt("lodlevel");
            if (shapeElem.hasAttribute("skinwidth"))
                skinWidth = shapeElem.getFloat("skinwidth");
            addConvexHull(model, skinWidth, lodLevel, position, rotation);
        }
        
        shapeElem = shapeElem.getNextElement();
    }
}

void CollisionShape::addSphere(float radius, const Vector3& position, const Quaternion& rotation)
{
    CollisionSubShape newShape;
    newShape.mType = SHAPE_SPHERE;
    newShape.mPosition = position;
    newShape.mRotation = rotation;
    newShape.mSize = Vector3(radius, radius, radius);
    
    mSubShapes.push_back(newShape);
    setMemoryUse(getMemoryUse() + sizeof(CollisionSubShape));
}

void CollisionShape::addBox(const Vector3& size, const Vector3& position, const Quaternion& rotation)
{
    CollisionSubShape newShape;
    newShape.mType = SHAPE_BOX;
    newShape.mPosition = position;
    newShape.mRotation = rotation;
    newShape.mSize = size;
    
    mSubShapes.push_back(newShape);
    setMemoryUse(getMemoryUse() + sizeof(CollisionSubShape));
}

void CollisionShape::addCapsule(float radius, float height, const Vector3& position, const Quaternion& rotation)
{
    CollisionSubShape newShape;
    newShape.mType = SHAPE_CAPSULE;
    newShape.mPosition = position;
    newShape.mRotation = rotation;
    newShape.mSize = Vector3(radius, radius, height);
    
    mSubShapes.push_back(newShape);
    setMemoryUse(getMemoryUse() + sizeof(CollisionSubShape));
}

void CollisionShape::addCylinder(float radius, float height, const Vector3& position, const Quaternion& rotation)
{
    CollisionSubShape newShape;
    newShape.mType = SHAPE_CYLINDER;
    newShape.mPosition = position;
    newShape.mRotation = rotation;
    newShape.mSize = Vector3(radius, radius, height);
    
    mSubShapes.push_back(newShape);
    setMemoryUse(getMemoryUse() + sizeof(CollisionSubShape));
}

void CollisionShape::addTriangleMesh(const Model* model, unsigned lodLevel, const Vector3& position, const Quaternion& rotation)
{
    PROFILE(Physics_AddTriangleMesh);
    
    if (!model)
    {
        LOGERROR("Null model for addTriangleMesh");
        return;
    }
    
    CollisionSubShape newShape;
    newShape.mType = SHAPE_TRIANGLEMESH;
    newShape.mPosition = position;
    newShape.mRotation = rotation;
    newShape.mSize = model->getBoundingBox().getSize();
    
    // Check cache
    std::string id = model->getName() + toString(lodLevel);
    std::map<std::string, SharedPtr<TriangleMeshData> >::iterator i = sTriangleMeshCache.find(id);
    if (i != sTriangleMeshCache.end())
        newShape.mGeometryData = staticCast<CollisionGeometryData>(i->second);
    else
    {
        SharedPtr<TriangleMeshData> newData(new TriangleMeshData(model, false, 0.0f, lodLevel));
        sTriangleMeshCache[id] = newData;
        newShape.mGeometryData = staticCast<CollisionGeometryData>(newData);
    }
    
    mSubShapes.push_back(newShape);
    setMemoryUse(getMemoryUse() + sizeof(CollisionSubShape) + newShape.mGeometryData->mMemoryUse);
}

void CollisionShape::addHeightfield(const Model* model, unsigned xPoints, unsigned zPoints, float thickness, unsigned lodLevel, const Vector3& position, const Quaternion& rotation)
{
    PROFILE(Physics_AddTriangleMesh);
    
    if (!model)
    {
        LOGERROR("Null model for addHeightField");
        return;
    }
    
    CollisionSubShape newShape;
    newShape.mType = SHAPE_HEIGHTFIELD;
    newShape.mPosition = position;
    newShape.mRotation = rotation;
    newShape.mSize = model->getBoundingBox().getSize();
    
    // Check cache
    std::string id = model->getName() + toString(thickness) + toString(lodLevel);
    std::map<std::string, SharedPtr<HeightfieldData> >::iterator i = sHeightfieldCache.find(id);
    if (i != sHeightfieldCache.end())
        newShape.mGeometryData = staticCast<CollisionGeometryData>(i->second);
    else
    {
        SharedPtr<HeightfieldData> newData(new HeightfieldData(model, xPoints, zPoints, thickness, lodLevel));
        sHeightfieldCache[id] = newData;
        newShape.mGeometryData = staticCast<CollisionGeometryData>(newData);
    }
    
    mSubShapes.push_back(newShape);
    setMemoryUse(getMemoryUse() + sizeof(CollisionSubShape) + newShape.mGeometryData->mMemoryUse);
}

void CollisionShape::addConvexHull(const Model* model, float skinWidth, unsigned lodLevel, const Vector3& position, const Quaternion& rotation)
{
    PROFILE(Physics_AddConvexHull);
    
    if (!model)
    {
        LOGERROR("Null model for addConvexHull");
        return;
    }
    
    CollisionSubShape newShape;
    newShape.mType = SHAPE_TRIANGLEMESH;
    newShape.mPosition = position;
    newShape.mRotation = rotation;
    newShape.mSize = model->getBoundingBox().getSize();
    
    // Check cache
    std::string id = model->getName() + toString(lodLevel) + "hull" + toString(skinWidth);
    std::map<std::string, SharedPtr<TriangleMeshData> >::iterator i = sTriangleMeshCache.find(id);
    if (i != sTriangleMeshCache.end())
        newShape.mGeometryData = staticCast<CollisionGeometryData>(i->second);
    else
    {
        SharedPtr<TriangleMeshData> newData(new TriangleMeshData(model, true, skinWidth, lodLevel));
        sTriangleMeshCache[id] = newData;
        newShape.mGeometryData = staticCast<CollisionGeometryData>(newData);
    }
    
    mSubShapes.push_back(newShape);
    setMemoryUse(getMemoryUse() + sizeof(CollisionSubShape) + newShape.mGeometryData->mMemoryUse);
}

void CollisionShape::clear()
{
    mSubShapes.clear();
    setMemoryUse(sizeof(CollisionShape));
    cleanupCaches();
}

void CollisionShape::createGeometries(std::vector<dGeomID>& geoms, std::vector<SharedPtr<CollisionGeometryData> >& geomDatas, dSpaceID space, const Vector3& scale)
{
    PROFILE(Physics_CreateGeometries);
    
    for (unsigned i = 0; i < mSubShapes.size(); ++i)
    {
        const CollisionSubShape& shape = mSubShapes[i];
        Vector3 size = shape.mSize * scale;
        dGeomID newGeom = 0;
        
        switch (shape.mType)
        {
        case SHAPE_BOX:
            newGeom = dCreateBox(space, size.mX, size.mY, size.mZ);
            break;
            
        case SHAPE_SPHERE:
            newGeom = dCreateSphere(space, size.mX);
            break;
            
        case SHAPE_CAPSULE:
            newGeom = dCreateCapsule(space, size.mX, size.mZ);
            break;
            
        case SHAPE_CYLINDER:
            newGeom = dCreateCylinder(space, size.mX, size.mZ);
            break;
            
        case SHAPE_TRIANGLEMESH:
            if (scale == Vector3::sUnity)
                newGeom = dCreateTriMesh(space, staticCast<TriangleMeshData>(shape.mGeometryData)->mTriMesh, 0, 0, 0);
            else
            {
                // If the mesh is scaled, need to create an unique copy of the geometry
                // Check cache first
                std::string id = shape.mGeometryData->mID + toString(scale);
                std::map<std::string, SharedPtr<TriangleMeshData> >::iterator j = sTriangleMeshCache.find(id);
                if (j != sTriangleMeshCache.end())
                {
                    newGeom = dCreateTriMesh(space, j->second->mTriMesh, 0, 0, 0);
                    geomDatas.push_back(staticCast<CollisionGeometryData>(j->second));
                }
                else
                {
                    LOGDEBUG("Creating unique copy of collision mesh, scale " + toString(scale));
                    SharedPtr<TriangleMeshData> newData(new TriangleMeshData(staticCast<TriangleMeshData>(shape.mGeometryData), scale));
                    sTriangleMeshCache[id] = newData;
                    newGeom = dCreateTriMesh(space, newData->mTriMesh, 0, 0, 0);
                    geomDatas.push_back(staticCast<CollisionGeometryData>(newData));
                }
            }
            break;
            
        case SHAPE_HEIGHTFIELD:
            if (scale == Vector3::sUnity)
                newGeom = dCreateHeightfield(space, staticCast<HeightfieldData>(shape.mGeometryData)->mHeightfield, 1);
            else
            {
                // If the heightfield is scaled, need to create an unique copy of the geometry
                // Check cache first
                std::string id = shape.mGeometryData->mID + toString(scale);
                std::map<std::string, SharedPtr<HeightfieldData> >::iterator j = sHeightfieldCache.find(id);
                if (j != sHeightfieldCache.end())
                {
                    newGeom = dCreateHeightfield(space, j->second->mHeightfield, 1);
                    geomDatas.push_back(staticCast<CollisionGeometryData>(j->second));
                }
                else
                {
                    LOGDEBUG("Creating unique copy of heightfield, scale " + toString(scale));
                    SharedPtr<HeightfieldData> newData(new HeightfieldData(staticCast<HeightfieldData>(shape.mGeometryData), scale));
                    sHeightfieldCache[id] = newData;
                    newGeom = dCreateHeightfield(space, newData->mHeightfield, 1);
                    geomDatas.push_back(staticCast<CollisionGeometryData>(newData));
                }
            }
            break;
        }
        
        if (newGeom)
            geoms.push_back(newGeom);
    }
}

void CollisionShape::setBodyAndTransforms(const std::vector<dGeomID>& geoms, dBodyID body, const Vector3& position, const Quaternion& rotation, const Vector3& scale)
{
    for (unsigned i = 0; (i < mSubShapes.size()) && (i < geoms.size()); ++i)
    {
        const CollisionSubShape& shape = mSubShapes[i];
        dGeomSetBody(geoms[i], body);
        
        // If using a body, can set geometry offset. If not, have to calculate the full transform manually
        if (body)
        {
            if ((shape.mPosition != Vector3::sZero) || (shape.mRotation != Quaternion::sIdentity))
            {
                Vector3 offset = scale * shape.mPosition;
                
                dGeomSetOffsetPosition(geoms[i], offset.mX, offset.mY, offset.mZ);
                dGeomSetOffsetQuaternion(geoms[i], shape.mRotation.getData());
            }
        }
        else
        {
            Vector3 worldPos = position + (rotation * (scale * shape.mPosition));
            Quaternion worldRot = rotation * shape.mRotation;
            
            dGeomSetPosition(geoms[i], worldPos.mX, worldPos.mY, worldPos.mZ);
            dGeomSetQuaternion(geoms[i], worldRot.getData());
        }
    }
}

void CollisionShape::calculateMass(void* dest, const std::vector<dGeomID>& geoms, float density, const Vector3& scale)
{
    dMass* mass = (dMass*)dest;
    if (!mass)
        return;
    
    dMassSetZero(mass);
    
    for (unsigned i = 0; (i < mSubShapes.size()) && (i < geoms.size()); ++i)
    {
        const CollisionSubShape& shape = mSubShapes[i];
        dMass subMass;
        Vector3 size = shape.mSize * scale;
        Vector3 offset = shape.mPosition * scale;
        
        switch (shape.mType)
        {
        case SHAPE_BOX:
            dMassSetBox(&subMass, density, size.mX, size.mY, size.mZ);
            break;
        case SHAPE_SPHERE:
            dMassSetSphere(&subMass, density, size.mX);
            break;
        case SHAPE_CYLINDER:
            dMassSetCylinder(&subMass, density, 2, size.mX, size.mZ);
            break;
        case SHAPE_CAPSULE:
            dMassSetCapsule(&subMass, density, 2, size.mX, size.mZ);
            break;
        case SHAPE_TRIANGLEMESH:
            dMassSetBox(&subMass, density, size.mX, size.mY, size.mZ);
            break;
        }
        
        dMatrix3 rotMatrix;
        dRfromQ(rotMatrix, shape.mRotation.getData());
        dMassTranslate(&subMass, offset.mX, offset.mY, offset.mZ);
        dMassRotate(&subMass, rotMatrix);
        dMassAdd(mass, &subMass);
    }
    
    // Translate final mass to center; anything else is unsupported in ODE
    dMassTranslate(mass, -mass->c[0], -mass->c[1], -mass->c[2]);
}

void CollisionShape::cleanupCaches()
{
    // Clear cached shapes whose only reference is the cache itself
    for (std::map<std::string, SharedPtr<TriangleMeshData> >::iterator i = sTriangleMeshCache.begin();
        i != sTriangleMeshCache.end();)
    {
        std::map<std::string, SharedPtr<TriangleMeshData> >::iterator current = i;
        ++i;
        if (current->second.getRefCount() == 1)
            sTriangleMeshCache.erase(current);
    }
    
    for (std::map<std::string, SharedPtr<HeightfieldData> >::iterator i = sHeightfieldCache.begin();
        i != sHeightfieldCache.end();)
    {
        std::map<std::string, SharedPtr<HeightfieldData> >::iterator current = i;
        ++i;
        if (current->second.getRefCount() == 1)
            sHeightfieldCache.erase(current);
    }
}
