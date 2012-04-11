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

/// Heightfield geometry data.
struct HeightfieldData : public CollisionGeometryData
{
    /// Construct from a model.
    HeightfieldData(Model* model, unsigned lodLevel, IntVector2 dimensions);
    /// Destruct. Free geometry data.
    ~HeightfieldData();
    
    /// Height values.
    SharedArrayPtr<float> heightData_;
    /// Heightfield dimensions.
    IntVector2 dimensions_;
    /// Heightfield bounding box.
    BoundingBox boundingBox_;
    /// X spacing.
    float xSpacing_;
    /// Z spacing.
    float zSpacing_;
};

/// Heightfield collision shape component.
class HeightfieldShape : public CollisionShape
{
    OBJECT(HeightfieldShape);
    
public:
    /// Construct.
    HeightfieldShape(Context* context);
    /// Destruct.
    ~HeightfieldShape();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// %Set model.
    void SetModel(Model* model);
    /// %Set LOD level.
    void SetLodLevel(unsigned lodLevel);
    /// %Set heightfield dimensions. Use 0 to guess from the model.
    void SetDimensions(const IntVector2& dimensions);
    /// %Set model scaling.
    void SetSize(const Vector3& size);
    /// %Set flip edges flag.
    void SetFlipEdges(bool enable);
    
    /// Return model.
    Model* GetModel() const;
    /// Return LOD level.
    unsigned GetLodLevel() const { return lodLevel_; }
    /// Return heightfield dimensions.
    const IntVector2& GetDimensions() const { return dimensions_; }
    /// Return model scaling.
    const Vector3& GetSize() { return size_; }
    /// Return flip edges flag.
    bool GetFlipEdges() { return flipEdges_; }
    
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
    SharedPtr<HeightfieldData> geometry_;
    /// Heightfield dimensions.
    IntVector2 dimensions_;
    /// Model scaling.
    Vector3 size_;
    /// LOD level.
    unsigned lodLevel_;
    /// Flip edges flag.
    bool flipEdges_;
};
