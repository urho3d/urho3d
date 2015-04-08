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

#pragma once

#include "../Math/BoundingBox.h"
#include "../Container/ArrayPtr.h"
#include "../Scene/Component.h"
#include "../Math/Quaternion.h"

class btBvhTriangleMeshShape;
class btCollisionShape;
class btCompoundShape;
class btTriangleMesh;

struct btTriangleInfoMap;

namespace Urho3D
{

class CustomGeometry;
class Geometry;
class Model;
class PhysicsWorld;
class RigidBody;
class Terrain;
class TriangleMeshInterface;

/// Collision shape type.
enum ShapeType
{
    SHAPE_BOX = 0,
    SHAPE_SPHERE,
    SHAPE_STATICPLANE,
    SHAPE_CYLINDER,
    SHAPE_CAPSULE,
    SHAPE_CONE,
    SHAPE_TRIANGLEMESH,
    SHAPE_CONVEXHULL,
    SHAPE_TERRAIN
};

/// Base class for collision shape geometry data.
struct CollisionGeometryData : public RefCounted
{
};

/// Triangle mesh geometry data.
struct TriangleMeshData : public CollisionGeometryData
{
    /// Construct from a model.
    TriangleMeshData(Model* model, unsigned lodLevel);
    /// Construct from a custom geometry.
    TriangleMeshData(CustomGeometry* custom);
    /// Destruct. Free geometry data.
    ~TriangleMeshData();

    /// Bullet triangle mesh interface.
    TriangleMeshInterface* meshInterface_;
    /// Bullet triangle mesh collision shape.
    btBvhTriangleMeshShape* shape_;
    /// Bullet triangle info map.
    btTriangleInfoMap* infoMap_;
};

/// Convex hull geometry data.
struct ConvexData : public CollisionGeometryData
{
    /// Construct from a model.
    ConvexData(Model* model, unsigned lodLevel);
    /// Construct from a custom geometry.
    ConvexData(CustomGeometry* custom);
    /// Destruct. Free geometry data.
    ~ConvexData();

    /// Build the convex hull from vertices.
    void BuildHull(const PODVector<Vector3>& vertices);

    /// Vertex data.
    SharedArrayPtr<Vector3> vertexData_;
    /// Number of vertices.
    unsigned vertexCount_;
    /// Index data.
    SharedArrayPtr<unsigned> indexData_;
    /// Number of indices.
    unsigned indexCount_;
};

/// Heightfield geometry data.
struct HeightfieldData : public CollisionGeometryData
{
    /// Construct from a terrain.
    HeightfieldData(Terrain* terrain, unsigned lodLevel);
    /// Destruct. Free geometry data.
    ~HeightfieldData();

    /// Height data. On LOD level 0 the original height data will be used.
    SharedArrayPtr<float> heightData_;
    /// Vertex spacing.
    Vector3 spacing_;
    /// Heightmap size.
    IntVector2 size_;
    /// Minimum height.
    float minHeight_;
    /// Maximum height.
    float maxHeight_;
};

/// Physics collision shape component.
class URHO3D_API CollisionShape : public Component
{
    OBJECT(CollisionShape);

public:
    /// Construct.
    CollisionShape(Context* context);
    /// Destruct. Free the geometry data and clean up unused data from the geometry data cache.
    virtual ~CollisionShape();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Handle attribute write access.
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& src);
    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    virtual void ApplyAttributes();
    /// Handle enabled/disabled state change.
    virtual void OnSetEnabled();
    /// Visualize the component as debug geometry.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

    /// Set as a box.
    void SetBox(const Vector3& size, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// Set as a sphere.
    void SetSphere(float diameter, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// Set as a static plane.
    void SetStaticPlane(const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// Set as a cylinder.
    void SetCylinder(float diameter, float height, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// Set as a capsule.
    void SetCapsule(float diameter, float height, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// Set as a cone.
    void SetCone(float diameter, float height, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// Set as a triangle mesh from Model. If you update a model's geometry and want to reapply the shape, call physicsWorld->RemoveCachedGeometry(model) first.
    void SetTriangleMesh(Model* model, unsigned lodLevel = 0, const Vector3& scale = Vector3::ONE, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// Set as a triangle mesh from CustomGeometry.
    void SetCustomTriangleMesh(CustomGeometry* custom, const Vector3& scale = Vector3::ONE, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// Set as a convex hull from Model.
    void SetConvexHull(Model* model, unsigned lodLevel = 0, const Vector3& scale = Vector3::ONE, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// Set as a convex hull from CustomGeometry.
    void SetCustomConvexHull(CustomGeometry* custom, const Vector3& scale = Vector3::ONE, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// Set as a terrain. Only works if the same scene node contains a Terrain component.
    void SetTerrain(unsigned lodLevel = 0);
    /// Set shape type.
    void SetShapeType(ShapeType type);
    /// Set shape size.
    void SetSize(const Vector3& size);
    /// Set offset position.
    void SetPosition(const Vector3& position);
    /// Set offset rotation.
    void SetRotation(const Quaternion& rotation);
    /// Set offset transform.
    void SetTransform(const Vector3& position, const Quaternion& rotation);
    /// Set collision margin.
    void SetMargin(float margin);
    /// Set triangle mesh / convex hull model.
    void SetModel(Model* model);
    /// Set model LOD level.
    void SetLodLevel(unsigned lodLevel);

    /// Return Bullet collision shape.
    btCollisionShape* GetCollisionShape() const { return shape_; }
    /// Return the shared geometry data.
    CollisionGeometryData* GetGeometryData() const { return geometry_; }
    /// Return physics world.
    PhysicsWorld* GetPhysicsWorld() const { return physicsWorld_; }
    /// Return shape type.
    ShapeType GetShapeType() const { return shapeType_; }
    /// Return shape size.
    const Vector3& GetSize() const { return size_; }
    /// Return offset position.
    const Vector3& GetPosition() const { return position_; }
    /// Return offset rotation.
    const Quaternion& GetRotation() const { return rotation_; }
    /// Return collision margin.
    float GetMargin() const { return margin_; }
    /// Return triangle mesh / convex hull model.
    Model* GetModel() const { return model_; }
    /// Return model LOD level.
    unsigned GetLodLevel() const { return lodLevel_; }
    /// Return world-space bounding box.
    BoundingBox GetWorldBoundingBox() const;

    /// Update the new collision shape to the RigidBody.
    void NotifyRigidBody(bool updateMass = true);
    /// Set model attribute.
    void SetModelAttr(const ResourceRef& value);
    /// Return model attribute.
    ResourceRef GetModelAttr() const;
    /// Release the collision shape.
    void ReleaseShape();

protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);

private:
    /// Find the parent rigid body component and return its compound collision shape.
    btCompoundShape* GetParentCompoundShape();
    /// Update the collision shape after attribute changes.
    void UpdateShape();
    /// Update terrain collision shape from the terrain component.
    void HandleTerrainCreated(StringHash eventType, VariantMap& eventData);
    /// Update trimesh or convex shape after a model has reloaded itself.
    void HandleModelReloadFinished(StringHash eventType, VariantMap& eventData);

    /// Physics world.
    WeakPtr<PhysicsWorld> physicsWorld_;
    /// Rigid body.
    WeakPtr<RigidBody> rigidBody_;
    /// Model.
    SharedPtr<Model> model_;
    /// Shared geometry data.
    SharedPtr<CollisionGeometryData> geometry_;
    /// Bullet collision shape.
    btCollisionShape* shape_;
    /// Collision shape type.
    ShapeType shapeType_;
    /// Offset position.
    Vector3 position_;
    /// Offset rotation.
    Quaternion rotation_;
    /// Shape size.
    Vector3 size_;
    /// Cached world scale for determining if the collision shape needs update.
    Vector3 cachedWorldScale_;
    /// Model LOD level.
    unsigned lodLevel_;
    /// CustomGeometry component ID for convex hull mode. 0 if not creating the convex hull from a CustomGeometry.
    int customGeometryID_;
    /// Collision margin.
    float margin_;
    /// Recrease collision shape flag.
    bool recreateShape_;
};

}
