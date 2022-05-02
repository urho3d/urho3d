//
// Copyright (c) 2008-2022 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/CustomGeometry.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/DrawableEvents.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/Model.h"
#include "../Graphics/Terrain.h"
#include "../GraphicsAPI/IndexBuffer.h"
#include "../GraphicsAPI/VertexBuffer.h"
#include "../IO/Log.h"
#include "../Physics/CollisionShape.h"
#include "../Physics/PhysicsUtils.h"
#include "../Physics/PhysicsWorld.h"
#include "../Physics/RigidBody.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/ResourceEvents.h"
#include "../Scene/Scene.h"

#include <Bullet/BulletCollision/CollisionDispatch/btInternalEdgeUtility.h>
#include <Bullet/BulletCollision/CollisionShapes/btBoxShape.h>
#include <Bullet/BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <Bullet/BulletCollision/CollisionShapes/btCompoundShape.h>
#include <Bullet/BulletCollision/CollisionShapes/btConeShape.h>
#include <Bullet/BulletCollision/CollisionShapes/btConvexHullShape.h>
#include <Bullet/BulletCollision/CollisionShapes/btCylinderShape.h>
#include <Bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <Bullet/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.h>
#include <Bullet/BulletCollision/CollisionShapes/btSphereShape.h>
#include <Bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.h>
#include <Bullet/BulletCollision/CollisionShapes/btStaticPlaneShape.h>
#include <Bullet/BulletCollision/Gimpact/btGImpactShape.h>
#include <Bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <StanHull/hull.h>

using namespace std;

namespace Urho3D
{

static const float DEFAULT_COLLISION_MARGIN = 0.04f;
static const unsigned QUANTIZE_MAX_TRIANGLES = 1000000;

static const btVector3 WHITE(1.0f, 1.0f, 1.0f);
static const btVector3 GREEN(0.0f, 1.0f, 0.0f);

static const char* typeNames[] =
{
    "Box",
    "Sphere",
    "StaticPlane",
    "Cylinder",
    "Capsule",
    "Cone",
    "TriangleMesh",
    "ConvexHull",
    "Terrain",
    "GImpactMesh",
    nullptr
};

extern const char* PHYSICS_CATEGORY;

class TriangleMeshInterface : public btTriangleIndexVertexArray
{
public:
    TriangleMeshInterface(Model* model, unsigned lodLevel) :
        btTriangleIndexVertexArray()
    {
        unsigned numGeometries = model->GetNumGeometries();
        unsigned totalTriangles = 0;

        for (unsigned i = 0; i < numGeometries; ++i)
        {
            Geometry* geometry = model->GetGeometry(i, lodLevel);
            if (!geometry)
            {
                URHO3D_LOGWARNING("Skipping null geometry for triangle mesh collision");
                continue;
            }

            SharedArrayPtr<unsigned char> vertexData;
            SharedArrayPtr<unsigned char> indexData;
            unsigned vertexSize;
            unsigned indexSize;
            const PODVector<VertexElement>* elements;

            geometry->GetRawDataShared(vertexData, vertexSize, indexData, indexSize, elements);
            if (!vertexData || !indexData || !elements || VertexBuffer::GetElementOffset(*elements, TYPE_VECTOR3, SEM_POSITION) != 0)
            {
                URHO3D_LOGWARNING("Skipping geometry with no or unsuitable CPU-side geometry data for triangle mesh collision");
                continue;
            }

            // Keep shared pointers to the vertex/index data so that if it's unloaded or changes size, we don't crash
            dataArrays_.Push(vertexData);
            dataArrays_.Push(indexData);

            unsigned indexStart = geometry->GetIndexStart();
            unsigned indexCount = geometry->GetIndexCount();

            btIndexedMesh meshIndex;
            meshIndex.m_numTriangles = indexCount / 3;
            meshIndex.m_triangleIndexBase = &indexData[indexStart * indexSize];
            meshIndex.m_triangleIndexStride = 3 * indexSize;
            meshIndex.m_numVertices = 0;
            meshIndex.m_vertexBase = vertexData;
            meshIndex.m_vertexStride = vertexSize;
            meshIndex.m_indexType = (indexSize == sizeof(unsigned short)) ? PHY_SHORT : PHY_INTEGER;
            meshIndex.m_vertexType = PHY_FLOAT;
            m_indexedMeshes.push_back(meshIndex);

            totalTriangles += meshIndex.m_numTriangles;
        }

        // Bullet will not work properly with quantized AABB compression, if the triangle count is too large. Use a conservative
        // threshold value
        useQuantize_ = totalTriangles <= QUANTIZE_MAX_TRIANGLES;
    }

    explicit TriangleMeshInterface(CustomGeometry* custom) :
        btTriangleIndexVertexArray()
    {
        const Vector<PODVector<CustomGeometryVertex> >& srcVertices = custom->GetVertices();
        unsigned totalVertexCount = 0;
        unsigned totalTriangles = 0;

        for (unsigned i = 0; i < srcVertices.Size(); ++i)
            totalVertexCount += srcVertices[i].Size();

        if (totalVertexCount)
        {
            // CustomGeometry vertex data is unindexed, so build index data here
            SharedArrayPtr<unsigned char> vertexData(new unsigned char[totalVertexCount * sizeof(Vector3)]);
            SharedArrayPtr<unsigned char> indexData(new unsigned char[totalVertexCount * sizeof(unsigned)]);
            dataArrays_.Push(vertexData);
            dataArrays_.Push(indexData);

            auto* destVertex = reinterpret_cast<Vector3*>(&vertexData[0]);
            auto* destIndex = reinterpret_cast<unsigned*>(&indexData[0]);
            unsigned k = 0;

            for (unsigned i = 0; i < srcVertices.Size(); ++i)
            {
                for (unsigned j = 0; j < srcVertices[i].Size(); ++j)
                {
                    *destVertex++ = srcVertices[i][j].position_;
                    *destIndex++ = k++;
                }
            }

            btIndexedMesh meshIndex;
            meshIndex.m_numTriangles = totalVertexCount / 3;
            meshIndex.m_triangleIndexBase = indexData;
            meshIndex.m_triangleIndexStride = 3 * sizeof(unsigned);
            meshIndex.m_numVertices = totalVertexCount;
            meshIndex.m_vertexBase = vertexData;
            meshIndex.m_vertexStride = sizeof(Vector3);
            meshIndex.m_indexType = PHY_INTEGER;
            meshIndex.m_vertexType = PHY_FLOAT;
            m_indexedMeshes.push_back(meshIndex);

            totalTriangles += meshIndex.m_numTriangles;
        }

        useQuantize_ = totalTriangles <= QUANTIZE_MAX_TRIANGLES;
    }

    /// OK to use quantization flag.
    bool useQuantize_;

private:
    /// Shared vertex/index data used in the collision.
    Vector<SharedArrayPtr<unsigned char> > dataArrays_;
};

TriangleMeshData::TriangleMeshData(Model* model, unsigned lodLevel)
{
    meshInterface_ = make_unique<TriangleMeshInterface>(model, lodLevel);
    shape_ = make_unique<btBvhTriangleMeshShape>(meshInterface_.get(), meshInterface_->useQuantize_, true);

    infoMap_ = make_unique<btTriangleInfoMap>();
    btGenerateInternalEdgeInfo(shape_.get(), infoMap_.get());
}

TriangleMeshData::TriangleMeshData(CustomGeometry* custom)
{
    meshInterface_ = make_unique<TriangleMeshInterface>(custom);
    shape_ = make_unique<btBvhTriangleMeshShape>(meshInterface_.get(), meshInterface_->useQuantize_, true);

    infoMap_ = make_unique<btTriangleInfoMap>();
    btGenerateInternalEdgeInfo(shape_.get(), infoMap_.get());
}

GImpactMeshData::GImpactMeshData(Model* model, unsigned lodLevel)
{
    meshInterface_ = make_unique<TriangleMeshInterface>(model, lodLevel);
}

GImpactMeshData::GImpactMeshData(CustomGeometry* custom)
{
    meshInterface_ = make_unique<TriangleMeshInterface>(custom);
}

ConvexData::ConvexData(Model* model, unsigned lodLevel)
{
    PODVector<Vector3> vertices;
    unsigned numGeometries = model->GetNumGeometries();

    for (unsigned i = 0; i < numGeometries; ++i)
    {
        Geometry* geometry = model->GetGeometry(i, lodLevel);
        if (!geometry)
        {
            URHO3D_LOGWARNING("Skipping null geometry for convex hull collision");
            continue;
        };

        const unsigned char* vertexData;
        const unsigned char* indexData;
        unsigned vertexSize;
        unsigned indexSize;
        const PODVector<VertexElement>* elements;

        geometry->GetRawData(vertexData, vertexSize, indexData, indexSize, elements);
        if (!vertexData || VertexBuffer::GetElementOffset(*elements, TYPE_VECTOR3, SEM_POSITION) != 0)
        {
            URHO3D_LOGWARNING("Skipping geometry with no or unsuitable CPU-side geometry data for convex hull collision");
            continue;
        }

        unsigned vertexStart = geometry->GetVertexStart();
        unsigned vertexCount = geometry->GetVertexCount();

        // Copy vertex data
        for (unsigned j = 0; j < vertexCount; ++j)
        {
            const Vector3& v = *((const Vector3*)(&vertexData[(vertexStart + j) * vertexSize]));
            vertices.Push(v);
        }
    }

    BuildHull(vertices);
}

ConvexData::ConvexData(CustomGeometry* custom)
{
    const Vector<PODVector<CustomGeometryVertex> >& srcVertices = custom->GetVertices();
    PODVector<Vector3> vertices;

    for (unsigned i = 0; i < srcVertices.Size(); ++i)
    {
        for (unsigned j = 0; j < srcVertices[i].Size(); ++j)
            vertices.Push(srcVertices[i][j].position_);
    }

    BuildHull(vertices);
}

void ConvexData::BuildHull(const PODVector<Vector3>& vertices)
{
    if (vertices.Size())
    {
        // Build the convex hull from the raw geometry
        StanHull::HullDesc desc;
        desc.SetHullFlag(StanHull::QF_TRIANGLES);
        desc.mVcount = vertices.Size();
        desc.mVertices = vertices[0].Data();
        desc.mVertexStride = 3 * sizeof(float);
        desc.mSkinWidth = 0.0f;

        StanHull::HullLibrary lib;
        StanHull::HullResult result;
        lib.CreateConvexHull(desc, result);

        vertexCount_ = result.mNumOutputVertices;
        vertexData_ = new Vector3[vertexCount_];

        indexCount_ = result.mNumIndices;
        indexData_ = new unsigned[indexCount_];

        // Copy vertex data & index data
        memcpy(vertexData_.Get(), result.mOutputVertices, vertexCount_ * sizeof(Vector3));
        memcpy(indexData_.Get(), result.mIndices, indexCount_ * sizeof(unsigned));

        lib.ReleaseResult(result);
    }
    else
    {
        vertexCount_ = 0;
        indexCount_ = 0;
    }
}

HeightfieldData::HeightfieldData(Terrain* terrain, unsigned lodLevel) :
    heightData_(terrain->GetHeightData()),
    spacing_(terrain->GetSpacing()),
    size_(terrain->GetNumVertices()),
    minHeight_(0.0f),
    maxHeight_(0.0f)
{
    if (heightData_)
    {
        if (lodLevel > 0)
        {
            IntVector2 lodSize = size_;
            Vector3 lodSpacing = spacing_;
            unsigned skip = 1;

            for (unsigned i = 0; i < lodLevel; ++i)
            {
                skip *= 2;
                lodSpacing.x_ *= 2.0f;
                lodSpacing.z_ *= 2.0f;
                int rX = lodSize.x_ & 1u;
                int rY = lodSize.y_ & 1u;
                lodSize.x_ >>= 1;
                lodSize.y_ >>= 1;
                lodSize.x_ += rX;
                lodSize.y_ += rY;
                if (lodSize.x_ <= 2 || lodSize.y_ <= 2)
                    break;
            }

            SharedArrayPtr<float> lodHeightData(new float[lodSize.x_ * lodSize.y_]);
            for (int y = 0, dY = 0; y < size_.y_ && dY < lodSize.y_; y += skip, ++dY)
            {
                for (int x = 0, dX = 0; x < size_.x_ && dX < lodSize.x_; x += skip, ++dX)
                    lodHeightData[dY * lodSize.x_ + dX] = heightData_[y * size_.x_ + x];
            }

            size_ = lodSize;
            spacing_ = lodSpacing;
            heightData_ = lodHeightData;
        }

        auto points = (unsigned)(size_.x_ * size_.y_);
        float* data = heightData_.Get();

        minHeight_ = maxHeight_ = data[0];
        for (unsigned i = 1; i < points; ++i)
        {
            minHeight_ = Min(minHeight_, data[i]);
            maxHeight_ = Max(maxHeight_, data[i]);
        }
    }
}

bool HasDynamicBuffers(Model* model, unsigned lodLevel)
{
    unsigned numGeometries = model->GetNumGeometries();

    for (unsigned i = 0; i < numGeometries; ++i)
    {
        Geometry* geometry = model->GetGeometry(i, lodLevel);
        if (!geometry)
            continue;
        unsigned numVertexBuffers = geometry->GetNumVertexBuffers();
        for (unsigned j = 0; j < numVertexBuffers; ++j)
        {
            VertexBuffer* buffer = geometry->GetVertexBuffer(j);
            if (!buffer)
                continue;
            if (buffer->IsDynamic())
                return true;
        }
        IndexBuffer* buffer = geometry->GetIndexBuffer();
        if (buffer && buffer->IsDynamic())
            return true;
    }

    return false;
}

CollisionGeometryData* CreateCollisionGeometryData(ShapeType shapeType, Model* model, unsigned lodLevel)
{
    switch (shapeType)
    {
    case SHAPE_TRIANGLEMESH:
        return new TriangleMeshData(model, lodLevel);
    case SHAPE_CONVEXHULL:
        return new ConvexData(model, lodLevel);
    case SHAPE_GIMPACTMESH:
        return new GImpactMeshData(model, lodLevel);
    default:
        return nullptr;
    }
}

CollisionGeometryData* CreateCollisionGeometryData(ShapeType shapeType, CustomGeometry* custom)
{
    switch (shapeType)
    {
    case SHAPE_TRIANGLEMESH:
        return new TriangleMeshData(custom);
    case SHAPE_CONVEXHULL:
        return new ConvexData(custom);
    case SHAPE_GIMPACTMESH:
        return new GImpactMeshData(custom);
    default:
        return nullptr;
    }
}

btCollisionShape* CreateCollisionGeometryDataShape(ShapeType shapeType, CollisionGeometryData* geometry, const Vector3& scale)
{
    switch (shapeType)
    {
    case SHAPE_TRIANGLEMESH:
        {
            auto* triMesh = static_cast<TriangleMeshData*>(geometry);
            return new btScaledBvhTriangleMeshShape(triMesh->shape_.get(), ToBtVector3(scale));
        }
    case SHAPE_CONVEXHULL:
        {
            auto* convex = static_cast<ConvexData*>(geometry);
            auto* shape = new btConvexHullShape((btScalar*)convex->vertexData_.Get(), convex->vertexCount_, sizeof(Vector3));
            shape->setLocalScaling(ToBtVector3(scale));
            return shape;
        }
    case SHAPE_GIMPACTMESH:
        {
            auto* gimpactMesh = static_cast<GImpactMeshData*>(geometry);
            auto* shape = new btGImpactMeshShape(gimpactMesh->meshInterface_.get());
            shape->setLocalScaling(ToBtVector3(scale));
            shape->updateBound();
            return shape;
        }
    default:
        return nullptr;
    }
}

CollisionShape::CollisionShape(Context* context) :
    Component(context),
    shapeType_(SHAPE_BOX),
    position_(Vector3::ZERO),
    rotation_(Quaternion::IDENTITY),
    size_(Vector3::ONE),
    cachedWorldScale_(Vector3::ONE),
    lodLevel_(0),
    customGeometryID_(0),
    margin_(DEFAULT_COLLISION_MARGIN),
    recreateShape_(true),
    retryCreation_(false)
{
}

CollisionShape::~CollisionShape()
{
    ReleaseShape();

    if (physicsWorld_)
        physicsWorld_->RemoveCollisionShape(this);
}

void CollisionShape::RegisterObject(Context* context)
{
    context->RegisterFactory<CollisionShape>(PHYSICS_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ENUM_ATTRIBUTE_EX("Shape Type", shapeType_, MarkShapeDirty, typeNames, SHAPE_BOX, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Size", Vector3, size_, MarkShapeDirty, Vector3::ONE, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Offset Position", GetPosition, SetPosition, Vector3, Vector3::ZERO, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Offset Rotation", GetRotation, SetRotation, Quaternion, Quaternion::IDENTITY, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Model", GetModelAttr, SetModelAttr, ResourceRef, ResourceRef(Model::GetTypeStatic()), AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("LOD Level", int, lodLevel_, MarkShapeDirty, 0, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Collision Margin", float, margin_, MarkShapeDirty, DEFAULT_COLLISION_MARGIN, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("CustomGeometry ComponentID", unsigned, customGeometryID_, MarkShapeDirty, 0, AM_DEFAULT | AM_COMPONENTID);
}

void CollisionShape::ApplyAttributes()
{
    if (recreateShape_)
    {
        UpdateShape();
        NotifyRigidBody();
    }
}

void CollisionShape::OnSetEnabled()
{
    NotifyRigidBody();
}

void CollisionShape::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && physicsWorld_ && shape_ && node_ && IsEnabledEffective())
    {
        // Use the rigid body's world transform if possible, as it may be different from the rendering transform
        Matrix3x4 worldTransform;
        auto* body = GetComponent<RigidBody>();
        bool bodyActive = false;
        if (body)
        {
            worldTransform = Matrix3x4(body->GetPosition(), body->GetRotation(), node_->GetWorldScale());
            bodyActive = body->IsActive();
        }
        else
            worldTransform = node_->GetWorldTransform();

        // Special case code for convex hull: bypass Bullet's own rendering to draw triangles correctly, not just edges
        if (shapeType_ == SHAPE_CONVEXHULL)
        {
            auto*convexData = static_cast<ConvexData*>(GetGeometryData());
            auto* body = GetComponent<RigidBody>();
            Color color = bodyActive ? Color::WHITE : Color::GREEN;
            Matrix3x4 shapeTransform(worldTransform * position_, worldTransform.Rotation() * rotation_, worldTransform.Scale());

            if (convexData)
            {
                for (unsigned i = 0; i < convexData->indexCount_; i += 3)
                {
                    Vector3 a = shapeTransform * convexData->vertexData_[convexData->indexData_[i + 0]];
                    Vector3 b = shapeTransform * convexData->vertexData_[convexData->indexData_[i + 1]];
                    Vector3 c = shapeTransform * convexData->vertexData_[convexData->indexData_[i + 2]];
                    debug->AddLine(a, b, color, depthTest);
                    debug->AddLine(b, c, color, depthTest);
                    debug->AddLine(a, c, color, depthTest);
                }
             }
        }
        else
        {
            physicsWorld_->SetDebugRenderer(debug);
            physicsWorld_->SetDebugDepthTest(depthTest);

            Vector3 position = position_;
            // For terrains, undo the height centering performed automatically by Bullet
            if (shapeType_ == SHAPE_TERRAIN && geometry_)
            {
                auto* heightfield = static_cast<HeightfieldData*>(geometry_.Get());
                position.y_ += (heightfield->minHeight_ + heightfield->maxHeight_) * 0.5f;
            }

            Vector3 worldPosition(worldTransform * position);
            Quaternion worldRotation(worldTransform.Rotation() * rotation_);

            btDiscreteDynamicsWorld* world = physicsWorld_->GetWorld();
            world->debugDrawObject(btTransform(ToBtQuaternion(worldRotation), ToBtVector3(worldPosition)), shape_.get(), bodyActive ?
                WHITE : GREEN);

            physicsWorld_->SetDebugRenderer(nullptr);
        }
    }
}

void CollisionShape::SetBox(const Vector3& size, const Vector3& position, const Quaternion& rotation)
{
    if (model_)
        UnsubscribeFromEvent(model_, E_RELOADFINISHED);

    shapeType_ = SHAPE_BOX;
    size_ = size;
    position_ = position;
    rotation_ = rotation;
    model_.Reset();
    customGeometryID_ = 0;

    UpdateShape();
    NotifyRigidBody();
    MarkNetworkUpdate();
}

void CollisionShape::SetSphere(float diameter, const Vector3& position, const Quaternion& rotation)
{
    if (model_)
        UnsubscribeFromEvent(model_, E_RELOADFINISHED);

    shapeType_ = SHAPE_SPHERE;
    size_ = Vector3(diameter, diameter, diameter);
    position_ = position;
    rotation_ = rotation;
    model_.Reset();
    customGeometryID_ = 0;

    UpdateShape();
    NotifyRigidBody();
    MarkNetworkUpdate();
}

void CollisionShape::SetStaticPlane(const Vector3& position, const Quaternion& rotation)
{
    if (model_)
        UnsubscribeFromEvent(model_, E_RELOADFINISHED);

    shapeType_ = SHAPE_STATICPLANE;
    position_ = position;
    rotation_ = rotation;
    model_.Reset();
    customGeometryID_ = 0;

    UpdateShape();
    NotifyRigidBody();
    MarkNetworkUpdate();
}

void CollisionShape::SetCylinder(float diameter, float height, const Vector3& position, const Quaternion& rotation)
{
    if (model_)
        UnsubscribeFromEvent(model_, E_RELOADFINISHED);

    shapeType_ = SHAPE_CYLINDER;
    size_ = Vector3(diameter, height, diameter);
    position_ = position;
    rotation_ = rotation;
    model_.Reset();
    customGeometryID_ = 0;

    UpdateShape();
    NotifyRigidBody();
    MarkNetworkUpdate();
}

void CollisionShape::SetCapsule(float diameter, float height, const Vector3& position, const Quaternion& rotation)
{
    if (model_)
        UnsubscribeFromEvent(model_, E_RELOADFINISHED);

    shapeType_ = SHAPE_CAPSULE;
    size_ = Vector3(diameter, height, diameter);
    position_ = position;
    rotation_ = rotation;
    model_.Reset();
    customGeometryID_ = 0;

    UpdateShape();
    NotifyRigidBody();
    MarkNetworkUpdate();
}

void CollisionShape::SetCone(float diameter, float height, const Vector3& position, const Quaternion& rotation)
{
    if (model_)
        UnsubscribeFromEvent(model_, E_RELOADFINISHED);

    shapeType_ = SHAPE_CONE;
    size_ = Vector3(diameter, height, diameter);
    position_ = position;
    rotation_ = rotation;
    model_.Reset();
    customGeometryID_ = 0;

    UpdateShape();
    NotifyRigidBody();
    MarkNetworkUpdate();
}

void CollisionShape::SetTriangleMesh(Model* model, unsigned lodLevel, const Vector3& scale, const Vector3& position,
    const Quaternion& rotation)
{
    SetModelShape(SHAPE_TRIANGLEMESH, model, lodLevel, scale, position, rotation);
}

void CollisionShape::SetCustomTriangleMesh(CustomGeometry* custom, const Vector3& scale, const Vector3& position,
    const Quaternion& rotation)
{
    SetCustomShape(SHAPE_TRIANGLEMESH, custom, scale, position, rotation);
}

void CollisionShape::SetConvexHull(Model* model, unsigned lodLevel, const Vector3& scale, const Vector3& position,
    const Quaternion& rotation)
{
    SetModelShape(SHAPE_CONVEXHULL, model, lodLevel, scale, position, rotation);
}

void CollisionShape::SetCustomConvexHull(CustomGeometry* custom, const Vector3& scale, const Vector3& position,
    const Quaternion& rotation)
{
    SetCustomShape(SHAPE_CONVEXHULL, custom, scale, position, rotation);
}

void CollisionShape::SetGImpactMesh(Model* model, unsigned lodLevel, const Vector3& scale, const Vector3& position,
    const Quaternion& rotation)
{
    SetModelShape(SHAPE_GIMPACTMESH, model, lodLevel, scale, position, rotation);
}

void CollisionShape::SetCustomGImpactMesh(CustomGeometry* custom, const Vector3& scale, const Vector3& position,
    const Quaternion& rotation)
{
    SetCustomShape(SHAPE_GIMPACTMESH, custom, scale, position, rotation);
}

void CollisionShape::SetTerrain(unsigned lodLevel)
{
    auto* terrain = GetComponent<Terrain>();
    if (!terrain)
    {
        URHO3D_LOGERROR("No terrain component, can not set terrain shape");
        return;
    }

    if (model_)
        UnsubscribeFromEvent(model_, E_RELOADFINISHED);

    shapeType_ = SHAPE_TERRAIN;
    lodLevel_ = lodLevel;

    UpdateShape();
    NotifyRigidBody();
    MarkNetworkUpdate();
}

void CollisionShape::SetShapeType(ShapeType type)
{
    if (type != shapeType_)
    {
        shapeType_ = type;
        UpdateShape();
        NotifyRigidBody();
        MarkNetworkUpdate();
    }
}

void CollisionShape::SetSize(const Vector3& size)
{
    if (size != size_)
    {
        size_ = size;
        UpdateShape();
        NotifyRigidBody();
        MarkNetworkUpdate();
    }
}

void CollisionShape::SetPosition(const Vector3& position)
{
    if (position != position_)
    {
        position_ = position;
        NotifyRigidBody();
        MarkNetworkUpdate();
    }
}

void CollisionShape::SetRotation(const Quaternion& rotation)
{
    if (rotation != rotation_)
    {
        rotation_ = rotation;
        NotifyRigidBody();
        MarkNetworkUpdate();
    }
}

void CollisionShape::SetTransform(const Vector3& position, const Quaternion& rotation)
{
    if (position != position_ || rotation != rotation_)
    {
        position_ = position;
        rotation_ = rotation;
        NotifyRigidBody();
        MarkNetworkUpdate();
    }
}

void CollisionShape::SetMargin(float margin)
{
    margin = Max(margin, 0.0f);

    if (margin != margin_)
    {
        if (shape_)
            shape_->setMargin(margin);
        margin_ = margin;
        MarkNetworkUpdate();
    }
}

void CollisionShape::SetModel(Model* model)
{
    if (model != model_)
    {
        if (model_)
            UnsubscribeFromEvent(model_, E_RELOADFINISHED);

        model_ = model;
        if (shapeType_ >= SHAPE_TRIANGLEMESH)
        {
            UpdateShape();
            NotifyRigidBody();
        }
        MarkNetworkUpdate();
    }
}

void CollisionShape::SetLodLevel(unsigned lodLevel)
{
    if (lodLevel != lodLevel_)
    {
        lodLevel_ = lodLevel;
        if (shapeType_ >= SHAPE_TRIANGLEMESH)
        {
            UpdateShape();
            NotifyRigidBody();
        }
        MarkNetworkUpdate();
    }
}

BoundingBox CollisionShape::GetWorldBoundingBox() const
{
    if (shape_ && node_)
    {
        // Use the rigid body's world transform if possible, as it may be different from the rendering transform
        auto* body = GetComponent<RigidBody>();
        Matrix3x4 worldTransform = body ? Matrix3x4(body->GetPosition(), body->GetRotation(), node_->GetWorldScale()) :
            node_->GetWorldTransform();

        Vector3 worldPosition(worldTransform * position_);
        Quaternion worldRotation(worldTransform.Rotation() * rotation_);
        btTransform shapeWorldTransform(ToBtQuaternion(worldRotation), ToBtVector3(worldPosition));
        btVector3 aabbMin, aabbMax;
        shape_->getAabb(shapeWorldTransform, aabbMin, aabbMax);

        return BoundingBox(ToVector3(aabbMin), ToVector3(aabbMax));
    }
    else
        return BoundingBox();
}

void CollisionShape::NotifyRigidBody(bool updateMass)
{
    btCompoundShape* compound = GetParentCompoundShape();
    if (node_ && shape_ && compound)
    {
        // Remove the shape first to ensure it is not added twice
        compound->removeChildShape(shape_.get());

        if (IsEnabledEffective())
        {
            // Then add with updated offset
            Vector3 position = position_;
            // For terrains, undo the height centering performed automatically by Bullet
            if (shapeType_ == SHAPE_TERRAIN && geometry_)
            {
                auto* heightfield = static_cast<HeightfieldData*>(geometry_.Get());
                position.y_ += (heightfield->minHeight_ + heightfield->maxHeight_) * 0.5f;
            }

            btTransform offset;
            offset.setOrigin(ToBtVector3(node_->GetWorldScale() * position));
            offset.setRotation(ToBtQuaternion(rotation_));
            compound->addChildShape(offset, shape_.get());
        }

        // Finally tell the rigid body to update its mass
        if (updateMass)
            rigidBody_->UpdateMass();
    }
}

void CollisionShape::SetModelAttr(const ResourceRef& value)
{
    auto* cache = GetSubsystem<ResourceCache>();
    model_ = cache->GetResource<Model>(value.name_);
    recreateShape_ = true;
    MarkNetworkUpdate();
}

ResourceRef CollisionShape::GetModelAttr() const
{
    return GetResourceRef(model_, Model::GetTypeStatic());
}

void CollisionShape::ReleaseShape()
{
    btCompoundShape* compound = GetParentCompoundShape();
    if (shape_ && compound)
    {
        compound->removeChildShape(shape_.get());
        rigidBody_->UpdateMass();
    }

    shape_.reset();
    geometry_.Reset();

    if (physicsWorld_)
        physicsWorld_->CleanupGeometryCache();
}

void CollisionShape::OnNodeSet(Node* node)
{
    if (node)
    {
        node->AddListener(this);
        cachedWorldScale_ = node->GetWorldScale();

        // Terrain collision shape depends on the terrain component's geometry updates. Subscribe to them
        SubscribeToEvent(node, E_TERRAINCREATED, URHO3D_HANDLER(CollisionShape, HandleTerrainCreated));
    }
}

void CollisionShape::OnSceneSet(Scene* scene)
{
    if (scene)
    {
        if (scene == node_)
            URHO3D_LOGWARNING(GetTypeName() + " should not be created to the root scene node");

        physicsWorld_ = scene->GetOrCreateComponent<PhysicsWorld>();
        physicsWorld_->AddCollisionShape(this);

        // Create shape now if necessary (attributes modified before adding to scene)
        if (retryCreation_)
        {
            UpdateShape();
            NotifyRigidBody();
        }
    }
    else
    {
        ReleaseShape();

        if (physicsWorld_)
            physicsWorld_->RemoveCollisionShape(this);

        // Recreate when moved to a scene again
        retryCreation_ = true;
    }
}

void CollisionShape::OnMarkedDirty(Node* node)
{
    Vector3 newWorldScale = node_->GetWorldScale();
    if (HasWorldScaleChanged(cachedWorldScale_, newWorldScale) && shape_)
    {
        // Physics operations are not safe from worker threads
        Scene* scene = GetScene();
        if (scene && scene->IsThreadedUpdate())
        {
            scene->DelayedMarkedDirty(this);
            return;
        }

        switch (shapeType_)
        {
        case SHAPE_BOX:
        case SHAPE_SPHERE:
        case SHAPE_CYLINDER:
        case SHAPE_CAPSULE:
        case SHAPE_CONE:
            shape_->setLocalScaling(ToBtVector3(newWorldScale));
            break;

        case SHAPE_TRIANGLEMESH:
        case SHAPE_CONVEXHULL:
            shape_->setLocalScaling(ToBtVector3(newWorldScale * size_));
            break;

        case SHAPE_TERRAIN:
            {
                auto* heightfield = static_cast<HeightfieldData*>(geometry_.Get());
                shape_->setLocalScaling(ToBtVector3(Vector3(heightfield->spacing_.x_, 1.0f, heightfield->spacing_.z_) *
                                                    newWorldScale * size_));
            }
            break;

        default:
            break;
        }

        NotifyRigidBody();

        cachedWorldScale_ = newWorldScale;
    }
}

btCompoundShape* CollisionShape::GetParentCompoundShape()
{
    if (!rigidBody_)
        rigidBody_ = GetComponent<RigidBody>();

    return rigidBody_ ? rigidBody_->GetCompoundShape() : nullptr;
}

void CollisionShape::UpdateShape()
{
    URHO3D_PROFILE(UpdateCollisionShape);

    ReleaseShape();

    // If no physics world available now mark for retry later
    if (!physicsWorld_)
    {
        retryCreation_ = true;
        return;
    }

    if (node_)
    {
        cachedWorldScale_ = node_->GetWorldScale();

        switch (shapeType_)
        {
        case SHAPE_BOX:
            shape_ = make_unique<btBoxShape>(ToBtVector3(size_ * 0.5f));
            shape_->setLocalScaling(ToBtVector3(cachedWorldScale_));
            break;

        case SHAPE_SPHERE:
            shape_ = make_unique<btSphereShape>(size_.x_ * 0.5f);
            shape_->setLocalScaling(ToBtVector3(cachedWorldScale_));
            break;

        case SHAPE_STATICPLANE:
            shape_ = make_unique<btStaticPlaneShape>(btVector3(0.0f, 1.0f, 0.0f), 0.0f);
            break;

        case SHAPE_CYLINDER:
            shape_ = make_unique<btCylinderShape>(btVector3(size_.x_ * 0.5f, size_.y_ * 0.5f, size_.x_ * 0.5f));
            shape_->setLocalScaling(ToBtVector3(cachedWorldScale_));
            break;

        case SHAPE_CAPSULE:
            shape_ = make_unique<btCapsuleShape>(size_.x_ * 0.5f, Max(size_.y_ - size_.x_, 0.0f));
            shape_->setLocalScaling(ToBtVector3(cachedWorldScale_));
            break;

        case SHAPE_CONE:
            shape_ = make_unique<btConeShape>(size_.x_ * 0.5f, size_.y_);
            shape_->setLocalScaling(ToBtVector3(cachedWorldScale_));
            break;

        case SHAPE_TRIANGLEMESH:
            UpdateCachedGeometryShape(physicsWorld_->GetTriMeshCache());
            break;

        case SHAPE_CONVEXHULL:
            UpdateCachedGeometryShape(physicsWorld_->GetConvexCache());
            break;

        case SHAPE_GIMPACTMESH:
            UpdateCachedGeometryShape(physicsWorld_->GetGImpactTrimeshCache());
            break;

        case SHAPE_TERRAIN:
            size_ = size_.Abs();
            {
                auto* terrain = GetComponent<Terrain>();
                if (terrain && terrain->GetHeightData())
                {
                    geometry_ = new HeightfieldData(terrain, lodLevel_);
                    auto* heightfield = static_cast<HeightfieldData*>(geometry_.Get());

                    shape_ = make_unique<btHeightfieldTerrainShape>(
                        heightfield->size_.x_, heightfield->size_.y_, heightfield->heightData_.Get(),
                        1.0f, heightfield->minHeight_, heightfield->maxHeight_, 1, PHY_FLOAT, false);
                    
                    shape_->setLocalScaling(
                        ToBtVector3(Vector3(heightfield->spacing_.x_, 1.0f, heightfield->spacing_.z_) * cachedWorldScale_ * size_));
                }
            }
            break;

        default:
            shape_.reset(this->UpdateDerivedShape(shapeType_, cachedWorldScale_));
            break;
        }

        if (shape_)
        {
            shape_->setUserPointer(this);
            shape_->setMargin(margin_);
        }
    }

    if (physicsWorld_)
        physicsWorld_->CleanupGeometryCache();

    recreateShape_ = false;
    retryCreation_ = false;
}

void CollisionShape::UpdateCachedGeometryShape(CollisionGeometryDataCache& cache)
{
    Scene* scene = GetScene();
    size_ = size_.Abs();
    if (customGeometryID_ && scene)
    {
        auto* custom = dynamic_cast<CustomGeometry*>(scene->GetComponent(customGeometryID_));
        if (custom)
        {
            geometry_ = CreateCollisionGeometryData(shapeType_, custom);
            assert(geometry_);
            
            shape_.reset(CreateCollisionGeometryDataShape(shapeType_, geometry_.Get(), cachedWorldScale_ * size_));
            assert(shape_);
        }
        else
            URHO3D_LOGWARNING("Could not find custom geometry component ID " + String(customGeometryID_) +
                " for collision shape creation");
    }
    else if (model_ && model_->GetNumGeometries())
    {
        // Check the geometry cache
        Pair<Model*, unsigned> id = MakePair(model_.Get(), lodLevel_);
        auto cachedGeometry = cache.Find(id);
        if (cachedGeometry != cache.End())
            geometry_ = cachedGeometry->second_;
        else
        {
            geometry_ = CreateCollisionGeometryData(shapeType_, model_, lodLevel_);
            assert(geometry_);
            // Check if model has dynamic buffers, do not cache in that case
            if (!HasDynamicBuffers(model_, lodLevel_))
                cache[id] = geometry_;
        }

        shape_.reset(CreateCollisionGeometryDataShape(shapeType_, geometry_.Get(), cachedWorldScale_ * size_));
        assert(shape_);
        // Watch for live reloads of the collision model to reload the geometry if necessary
        SubscribeToEvent(model_, E_RELOADFINISHED, URHO3D_HANDLER(CollisionShape, HandleModelReloadFinished));
    }
}

void CollisionShape::SetModelShape(ShapeType shapeType, Model* model, unsigned lodLevel,
    const Vector3& scale, const Vector3& position, const Quaternion& rotation)
{
    if (!model)
    {
        URHO3D_LOGERROR("Null model, can not set collsion shape");
        return;
    }

    if (model_)
        UnsubscribeFromEvent(model_, E_RELOADFINISHED);

    shapeType_ = shapeType;
    model_ = model;
    lodLevel_ = lodLevel;
    size_ = scale;
    position_ = position;
    rotation_ = rotation;
    customGeometryID_ = 0;

    UpdateShape();
    NotifyRigidBody();
    MarkNetworkUpdate();
}

void CollisionShape::SetCustomShape(ShapeType shapeType, CustomGeometry* custom,
    const Vector3& scale, const Vector3& position, const Quaternion& rotation)
{
    if (!custom)
    {
        URHO3D_LOGERROR("Null custom geometry, can not set collsion shape");
        return;
    }
    if (custom->GetScene() != GetScene())
    {
        URHO3D_LOGERROR("Custom geometry is not in the same scene as the collision shape, can not set collsion shape");
        return;
    }

    if (model_)
        UnsubscribeFromEvent(model_, E_RELOADFINISHED);

    shapeType_ = shapeType;
    model_.Reset();
    lodLevel_ = 0;
    size_ = scale;
    position_ = position;
    rotation_ = rotation;
    customGeometryID_ = custom->GetID();

    UpdateShape();
    NotifyRigidBody();
    MarkNetworkUpdate();
}

btCollisionShape* CollisionShape::UpdateDerivedShape(int shapeType, const Vector3& newWorldScale)
{
    // To be overridden in derived classes.
    return nullptr;
}

void CollisionShape::HandleTerrainCreated(StringHash eventType, VariantMap& eventData)
{
    if (shapeType_ == SHAPE_TERRAIN)
    {
        UpdateShape();
        NotifyRigidBody();
    }
}

void CollisionShape::HandleModelReloadFinished(StringHash eventType, VariantMap& eventData)
{
    if (physicsWorld_)
        physicsWorld_->RemoveCachedGeometry(model_);
    if (shapeType_ == SHAPE_TRIANGLEMESH || shapeType_ == SHAPE_CONVEXHULL)
    {
        UpdateShape();
        NotifyRigidBody();
    }
}

}
