//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#include "BoundingBox.h"
#include "ArrayPtr.h"
#include "Component.h"
#include "Quaternion.h"

class DebugRenderer;
class Geometry;
class Model;
class PhysicsWorld;
class RigidBody;

class btBvhTriangleMeshShape;
class btCollisionShape;
class btCompoundShape;
class btTriangleMesh;

/// Collision shape type.
enum ShapeType
{
    SHAPE_BOX = 0,
    SHAPE_SPHERE,
    SHAPE_CYLINDER,
    SHAPE_CAPSULE,
    SHAPE_CONE,
    SHAPE_TRIANGLEMESH,
    SHAPE_CONVEXHULL,
    SHAPE_HEIGHTFIELD
};

/// Base class for collision shape geometry data.
struct CollisionGeometryData : public RefCounted
{
    /// Original model name
    String modelName_;
};

/// Triangle mesh geometry data.
struct TriangleMeshData : public CollisionGeometryData
{
    /// Construct from a model.
    TriangleMeshData(Model* model, unsigned lodLevel);
    /// Destruct. Free geometry data.
    ~TriangleMeshData();
    
    /// Bullet triangle mesh data.
    btTriangleMesh* meshData_;
    /// Bullet triangle mesh collision shape.
    btBvhTriangleMeshShape* shape_;
};

/// Convex hull geometry data.
struct ConvexData : public CollisionGeometryData
{
    /// Construct from a model.
    ConvexData(Model* model, unsigned lodLevel, float thickness);
    /// Destruct. Free geometry data.
    ~ConvexData();
    
    /// Vertex data.
    SharedArrayPtr<Vector3> vertexData_;
    /// Number of vertices.
    unsigned vertexCount_;
};

/// Heightfield geometry data.
struct HeightfieldData : public CollisionGeometryData
{
    /// Construct from a model.
    HeightfieldData(Model* model, unsigned lodLevel, IntVector2 numPoints);
    /// Destruct. Free geometry data.
    ~HeightfieldData();
    
    /// Height values.
    SharedArrayPtr<float> heightData_;
    /// Heightfield number of points in X & Z dimensions.
    IntVector2 numPoints_;
    /// Heightfield bounding box.
    BoundingBox boundingBox_;
    /// X spacing.
    float xSpacing_;
    /// Z spacing.
    float zSpacing_;
};

/// Physics collision shape component.
class CollisionShape : public Component
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
    
    /// %Set as a sphere.
    void SetSphere(float diameter, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// %Set as a box.
    void SetBox(const Vector3& size, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// %Set as a cylinder.
    void SetCylinder(float diameter, float height, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// %Set as a capsule.
    void SetCapsule(float diameter, float height, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
   /// %Set as a cone.
    void SetCone(float diameter, float height, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// %Set as a triangle mesh.
    void SetTriangleMesh(Model* model, unsigned lodLevel, const Vector3& size = Vector3::ONE, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// %Set as a heightfield.
    void SetHeightfield(Model* model, unsigned lodLevel, unsigned xPoints, unsigned zPoints, const Vector3& size = Vector3::ONE, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// %Set as a convex hull (internally an ODE trimesh as well.)
    void SetConvexHull(Model* model, unsigned lodLevel, float thickness, const Vector3& size = Vector3::ONE, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// %Set shape type.
    void SetShapeType(ShapeType type);
    /// %Set shape size.
    void SetSize(const Vector3& size);
    /// %Set offset position.
    void SetPosition(const Vector3& position);
    /// %Set offset rotation.
    void SetRotation(const Quaternion& rotation);
    /// %Set offset transform.
    void SetTransform(const Vector3& position, const Quaternion& rotation);
    /// %Set triangle mesh / convex hull / heightfield model.
    void SetModel(Model* model);
    /// %Set model LOD level.
    void SetLodLevel(unsigned lodLevel);
    /// %Set convex hull thickness.
    void SetThickness(float thickness);
    /// %Set heightfield number of points in X & Z dimensions. Use (0,0) to guess from the model.
    void SetNumPoints(const IntVector2& numPoints);
    /// %Set heightfield flip edges flag.
    void SetFlipEdges(bool enable);
    
    /// Return Bullet collision shape.
    btCollisionShape* GetCollisionShape() const { return shape_; }
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
    /// Return triangle mesh / convex hull / heightfield model.
    Model* GetModel() const { return model_; }
    /// Return model LOD level.
    unsigned GetLodLevel() const { return lodLevel_; }
    /// Return convex hull thickness.
    float GetThickness() const { return thickness_; }
    /// Return heightfield number of points in X & Z dimensions.
    const IntVector2& GetNumPoints() const { return numPoints_; }
    /// Return heightfield flip edges flag.
    bool GetFlipEdges() { return flipEdges_; }
    
    /// Update the new collision shape to the RigidBody, and tell it to update its mass.
    void NotifyRigidBody();
    /// Add debug geometry to the debug renderer.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);
    /// %Set model attribute.
    void SetModelAttr(ResourceRef value);
    /// Return model attribute.
    ResourceRef GetModelAttr() const;
    
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
    /// Release the collision shape.
    void ReleaseShape();
    
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
    /// Heightfield number of points.
    IntVector2 numPoints_;
    /// Model LOD level.
    unsigned lodLevel_;
    /// Hull thickness.
    float thickness_;
    /// Heightfield flip edges flag.
    bool flipEdges_;
    /// Dirty flag.
    bool dirty_;
};
