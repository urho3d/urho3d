//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Drawable.h"
#include "Matrix3x4.h"
#include "Text.h"
#include "VertexBuffer.h"

namespace Urho3D
{

class Text;

/// 3D text component.
class Text3D : public Drawable
{
    OBJECT(Text3D);
    
public:
    /// Construct.
    Text3D(Context* context);
    /// Destruct.
    ~Text3D();
    /// Register object factory. Drawable must be registered first.
    static void RegisterObject(Context* context);
    
    /// Apply attribute changes that can not be applied immediately.
    virtual void ApplyAttributes();
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    virtual void UpdateBatches(const FrameInfo& frame);
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update.)
    virtual void UpdateGeometry(const FrameInfo& frame);
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    virtual UpdateGeometryType GetUpdateGeometryType();
    
    /// Set font and font size. Return true if successful.
    bool SetFont(const String& fontName, int size = DEFAULT_FONT_SIZE);
    /// Set font and font size. Return true if successful.
    bool SetFont(Font* font, int size = DEFAULT_FONT_SIZE);
    /// Set material.
    void SetMaterial(Material* material);
    /// Set text. Text is assumed to be either ASCII or UTF8-encoded.
    void SetText(const String& text);
    /// Set horizontal and vertical alignment.
    void SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign);
    /// Set horizontal alignment.
    void SetHorizontalAlignment(HorizontalAlignment align);
    /// Set vertical alignment.
    void SetVerticalAlignment(VerticalAlignment align);
    /// Set row alignment.
    void SetTextAlignment(HorizontalAlignment align);
    /// Set row spacing, 1.0 for original font spacing.
    void SetRowSpacing(float spacing);
    /// Set wordwrap. In wordwrap mode the text element will respect its current width. Otherwise it resizes itself freely.
    void SetWordwrap(bool enable);
    /// Set text width. Only has effect in word wrap mode.
    void SetWidth(int width);
    /// Set color on all corners.
    void SetColor(const Color& color);
    /// Set color on one corner.
    void SetColor(Corner corner, const Color& color);
    /// Set opacity.
    void SetOpacity(float opacity);
    /// Set whether to face camera automatically.
    void SetFaceCamera(bool enable);
    
    /// Return font.
    Font* GetFont() const;
    /// Return material.
    Material* GetMaterial() const;
    /// Return font size.
    int GetFontSize() const;
    /// Return text.
    const String& GetText() const;
    /// Return row alignment.
    HorizontalAlignment GetTextAlignment() const;
    /// Return horizontal alignment.
    HorizontalAlignment GetHorizontalAlignment() const;
    /// Return vertical alignment.
    VerticalAlignment GetVerticalAlignment() const;
    /// Return row spacing.
    float GetRowSpacing() const;
    /// Return wordwrap mode.
    bool GetWordwrap() const;
    /// Return text width.
    int GetWidth() const;
    /// Return row height.
    int GetRowHeight() const;
    /// Return number of rows.
    unsigned GetNumRows() const;
    /// Return width of each row.
    const PODVector<int>& GetRowWidths() const;
    /// Return corner color.
    const Color& GetColor(Corner corner) const;
    /// Return opacity.
    float GetOpacity() const;
    /// Return whether faces camera automatically.
    bool GetFaceCamera() const { return faceCamera_; }
    
    /// Set font attribute.
    void SetFontAttr(ResourceRef value);
    /// Return font attribute.
    ResourceRef GetFontAttr() const;
    /// Set material attribute.
    void SetMaterialAttr(ResourceRef value);
    /// Return material attribute.
    ResourceRef GetMaterialAttr() const;
    /// Get color attribute. Uses just the top-left color.
    const Color& GetColorAttr() const { return text_.color_[0]; }
    
protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    
private:
    /// Mark text & geometry dirty.
    void MarkTextDirty();
    /// Update text and font.
    void UpdateText();
    /// Update text %UI batches.
    void UpdateTextBatches();
    /// Create materials for text rendering. May only be called from the main thread. Text %UI batches must be up-to-date.
    void UpdateTextMaterials(bool forceUpdate = false);
    
    /// Internally used text element.
    Text text_;
    /// Geometries.
    Vector<SharedPtr<Geometry> > geometries_;
    /// Vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// Material to use as a base for the text material(s).
    SharedPtr<Material> material_;
    /// Text UI batches.
    PODVector<UIBatch> uiBatches_;
    /// Text vertex data.
    PODVector<float> uiVertexData_;
    /// Local-space bounding box.
    BoundingBox boundingBox_;
    /// Custom world transform for facing the camera automatically.
    Matrix3x4 customWorldTransform_;
    /// Face camera flag.
    bool faceCamera_;
    /// Text needs update flag.
    bool textDirty_;
    /// Geometry dirty flag.
    bool geometryDirty_;
};

}

