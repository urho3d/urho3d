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

#pragma once

#include "BoundingBox.h"
#include "Component.h"
#include "Quaternion.h"
#include "PhysicsDefs.h"
#include "ArrayPtr.h"

class DebugRenderer;
class Geometry;
class Model;
class PhysicsWorld;

/// Collision shape type.
enum ShapeType
{
    SHAPE_NONE = 0,
    SHAPE_BOX,
    SHAPE_SPHERE,
    SHAPE_CAPSULE,
    SHAPE_CYLINDER,
    SHAPE_TRIANGLEMESH,
    SHAPE_HEIGHTFIELD,
    SHAPE_CONVEXHULL
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
    TriangleMeshData(Model* model, bool makeConvexHull, float thickness, unsigned lodLevel, const Vector3& scale);
    /// Destruct. Free geometry data.
    ~TriangleMeshData();
    
    /// ODE trimesh geometry ID.
    dTriMeshDataID triMesh_;
    /// Vertex data.
    SharedArrayPtr<Vector3> vertexData_;
    /// Index data.
    SharedArrayPtr<unsigned> indexData_;
    /// Number of indices.
    unsigned indexCount_;
};

/// Heightfield geometry data.
struct HeightfieldData : public CollisionGeometryData
{
    /// Construct from a model.
    HeightfieldData(Model* model, IntVector2 numPoints, float thickness, unsigned lodLevel, const Vector3& scale);
    /// Destruct. Free geometry data.
    ~HeightfieldData();
    
    /// ODE heightfield geometry ID.
    dHeightfieldDataID heightfield_;
    /// Height values.
    SharedArrayPtr<float> heightData_;
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
    /// Perform finalization after a scene load or network update.
    virtual void FinishUpdate();
    
    /// Clear the collision geometry.
    void Clear();
    /// %Set as a sphere.
    void SetSphere(float radius, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// %Set as a box.
    void SetBox(const Vector3& size, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// %Set as a cylinder.
    void SetCylinder(float radius, float height, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// %Set as a capsule.
    void SetCapsule(float radius, float height, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// %Set as a triangle mesh.
    void SetTriangleMesh(Model* model, unsigned lodLevel, const Vector3& size = Vector3::UNITY, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// %Set as a heightfield.
    void SetHeightfield(Model* model, unsigned xPoints, unsigned zPoints, float thickness, unsigned lodLevel, const Vector3& size = Vector3::UNITY, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// %Set as a convex hull (internally an ODE trimesh as well.)
    void SetConvexHull(Model* model, float skinWidth, unsigned lodLevel, const Vector3& size = Vector3::UNITY, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY);
    /// %Set offset position.
    void SetPosition(const Vector3& position);
    /// %Set rotation.
    void SetRotation(const Quaternion& rotation);
    /// %Set offset transform.
    void SetTransform(const Vector3& position, const Quaternion& rotation);
    /// %Set collision group bits.
    void SetCollisionLayer(unsigned group);
    /// %Set collision mask bits.
    void SetCollisionMask(unsigned mask);
    /// %Set friction coefficient.
    void SetFriction(float friction);
    /// %Set bounce coefficient.
    void SetBounce(float bounce);
    /// %Set phantom flag. Phantom shapes generate collision events only, but no contact joints.
    void SetPhantom(bool enable);
    
    /// Return physics world.
    PhysicsWorld* GetPhysicsWorld() const { return physicsWorld_; }
    /// Return model (trimesh & heightfield only.)
    Model* GetModel() const { return model_; }
    /// Return shape type.
    ShapeType GetShapeType() const { return shapeType_; }
    /// Return ODE geometry.
    dGeomID GetGeometry() const { return geometry_; }
    /// Return unscaled shape size.
    const Vector3& GetSize() const { return size_; }
    /// Return number of points in X & Z dimensions (heightfield only.)
    IntVector2 GetNumPoints() const { return numPoints_; }
    /// Return thickness (convex hull & heightfield only.)
    float GetThickness() const { return thickness_; }
    /// Return model LOD level (trimesh & heightfield only.)
    unsigned GetLodLevel() const { return lodLevel_; }
    /// Return offset position.
    const Vector3& GetPosition() const { return position_; }
    /// Return rotation.
    const Quaternion& GetRotation() const { return rotation_; }
    /// Return collision group bits.
    unsigned GetCollisionLayer() const { return collisionLayer_; }
    /// Return collision mask bits.
    unsigned GetCollisionMask() const { return collisionMask_; }
    /// Return friction coefficient.
    float GetFriction() const { return friction_; }
    /// Return bounce coefficient.
    float GetBounce() const { return bounce_; }
    /// Return phantom flag.
    bool IsPhantom() const { return phantom_; }
    
    /// Update geometry transform and associate with rigid body if available.
    void UpdateTransform();
    /// Add debug geometry to the debug graphics.
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
    /// Create new geometry.
    void CreateGeometry();
    /// Remove existing geometry.
    void ReleaseGeometry(bool notifyBody = true);
    
    /// Physics world.
    WeakPtr<PhysicsWorld> physicsWorld_;
    /// Model for trimesh & heightfield geometry.
    SharedPtr<Model> model_;
    /// Geometry data for trimesh & heightfield geometry.
    SharedPtr<CollisionGeometryData> geometryData_;
    /// ODE geometry.
    dGeomID geometry_;
    /// Shape type.
    ShapeType shapeType_;
    /// Unscaled size of shape.
    Vector3 size_;
    /// Number of heightfield points in X & Z dimensions.
    IntVector2 numPoints_;
    /// Thickness.
    float thickness_;
    /// LOD level.
    unsigned lodLevel_;
    /// Offset position.
    Vector3 position_;
    /// Rotation.
    Quaternion rotation_;
    /// Scene node scale used to create the geometry.
    Vector3 geometryScale_;
    /// Collision group bits.
    unsigned collisionLayer_;
    /// Collision mask bits.
    unsigned collisionMask_;
    /// Friction coefficient.
    float friction_;
    /// Bounce coefficient.
    float bounce_;
    /// Phantom flag.
    bool phantom_;
    /// Recreate geometry flag.
    bool recreateGeometry_;
};
