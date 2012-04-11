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

#include "CollisionShape.h"

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

/// Convex hull collision shape component.
class ConvexShape : public CollisionShape
{
    OBJECT(ConvexShape);
    
public:
    /// Construct.
    ConvexShape(Context* context);
    /// Destruct.
    ~ConvexShape();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// %Set model.
    void SetModel(Model* model);
    /// %Set LOD level.
    void SetLodLevel(unsigned lodLevel);
    /// %Set hull thickness.
    void SetThickness(float thickness);
    /// %Set model scaling.
    void SetSize(const Vector3& size);
    
    /// Return model.
    Model* GetModel() const;
    /// Return LOD level.
    unsigned GetLodLevel() const { return lodLevel_; }
    /// Return hull thickness.
    float GetThickness() const { return thickness_; }
    /// Return model scaling.
    const Vector3& GetSize() { return size_; }
    
    /// %Set model attribute.
    void SetModelAttr(ResourceRef value);
    /// Return model attribute.
    ResourceRef GetModelAttr() const;
    
protected:
    /// Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);
    /// Update the collision shape.
    virtual void UpdateCollisionShape();
    
private:
    /// Model.
    SharedPtr<Model> model_;
    /// Current geometry data.
    SharedPtr<ConvexData> geometry_;
    /// Model scaling.
    Vector3 size_;
    /// LOD level.
    unsigned lodLevel_;
    /// Hull thickness.
    float thickness_;
};
