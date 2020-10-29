//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Graphics/Drawable.h"
#include "../Graphics/VertexBuffer.h"
#include "../Math/Matrix3x4.h"
#include "../UI/Text.h"

namespace Urho3D
{

class Text;

/// 3D text component.
class URHO3D_API Text3D : public Drawable
{
    URHO3D_OBJECT(Text3D, Drawable);

public:
    /// Construct.
    explicit Text3D(Context* context);
    /// Destruct.
    ~Text3D() override;
    /// Register object factory. Drawable must be registered first.
    static void RegisterObject(Context* context);

    /// Apply attribute changes that can not be applied immediately.
    void ApplyAttributes() override;
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    void UpdateBatches(const FrameInfo& frame) override;
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update).
    void UpdateGeometry(const FrameInfo& frame) override;
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    UpdateGeometryType GetUpdateGeometryType() override;

    /// Set font by looking from resource cache by name and font size. Return true if successful.
    bool SetFont(const String& fontName, float size = DEFAULT_FONT_SIZE);
    /// Set font and font size. Return true if successful.
    bool SetFont(Font* font, float size = DEFAULT_FONT_SIZE);
    /// Set font size only while retaining the existing font. Return true if successful.
    /// @property
    bool SetFontSize(float size);
    /// Set material.
    /// @property
    void SetMaterial(Material* material);
    /// Set text. Text is assumed to be either ASCII or UTF8-encoded.
    /// @property
    void SetText(const String& text);
    /// Set horizontal and vertical alignment.
    void SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign);
    /// Set horizontal alignment.
    /// @property
    void SetHorizontalAlignment(HorizontalAlignment align);
    /// Set vertical alignment.
    /// @property
    void SetVerticalAlignment(VerticalAlignment align);
    /// Set row alignment.
    /// @property
    void SetTextAlignment(HorizontalAlignment align);
    /// Set row spacing, 1.0 for original font spacing.
    /// @property
    void SetRowSpacing(float spacing);
    /// Set wordwrap. In wordwrap mode the text element will respect its current width. Otherwise it resizes itself freely.
    /// @property
    void SetWordwrap(bool enable);
    /// Set text effect.
    /// @property
    void SetTextEffect(TextEffect textEffect);
    /// Set shadow offset.
    /// @property
    void SetEffectShadowOffset(const IntVector2& offset);
    /// Set stroke thickness.
    /// @property
    void SetEffectStrokeThickness(int thickness);
    /// Set stroke rounding. Corners of the font will be rounded off in the stroke so the stroke won't have corners.
    /// @property
    void SetEffectRoundStroke(bool roundStroke);
    /// Set effect color.
    /// @property
    void SetEffectColor(const Color& effectColor);
    /// Set effect Z bias.
    /// @property
    void SetEffectDepthBias(float bias);
    /// Set text width. Only has effect in word wrap mode.
    /// @property
    void SetWidth(int width);
    /// Set color on all corners.
    /// @property
    void SetColor(const Color& color);
    /// Set color on one corner.
    /// @property{set_colors}
    void SetColor(Corner corner, const Color& color);
    /// Set opacity.
    /// @property
    void SetOpacity(float opacity);
    /// Set whether text has fixed size on screen (pixel-perfect) regardless of distance to camera. Works best when combined with face camera rotation. Default false.
    /// @property
    void SetFixedScreenSize(bool enable);
    /// Set how the text should rotate in relation to the camera. Default is to not rotate (FC_NONE).
    /// @property
    void SetFaceCameraMode(FaceCameraMode mode);

    /// Return font.
    /// @property
    Font* GetFont() const;
    /// Return font size.
    /// @property
    float GetFontSize() const;
    /// Return material.
    /// @property
    Material* GetMaterial() const;
    /// Return text.
    /// @property
    const String& GetText() const;
    /// Return row alignment.
    /// @property
    HorizontalAlignment GetTextAlignment() const;
    /// Return horizontal alignment.
    /// @property
    HorizontalAlignment GetHorizontalAlignment() const;
    /// Return vertical alignment.
    /// @property
    VerticalAlignment GetVerticalAlignment() const;
    /// Return row spacing.
    /// @property
    float GetRowSpacing() const;
    /// Return wordwrap mode.
    /// @property
    bool GetWordwrap() const;
    /// Return text effect.
    /// @property
    TextEffect GetTextEffect() const;
    /// Return effect shadow offset.
    /// @property
    const IntVector2& GetEffectShadowOffset() const;
    /// Return effect stroke thickness.
    /// @property
    int GetEffectStrokeThickness() const;
    /// Return effect round stroke.
    /// @property
    bool GetEffectRoundStroke() const;
    /// Return effect color.
    /// @property
    const Color& GetEffectColor() const;
    /// Return effect depth bias.
    /// @property
    float GetEffectDepthBias() const;
    /// Return text width.
    /// @property
    int GetWidth() const;
    /// Return text height.
    /// @property
    int GetHeight() const;
    /// Return row height.
    /// @property
    int GetRowHeight() const;
    /// Return number of rows.
    /// @property
    unsigned GetNumRows() const;
    /// Return number of characters.
    /// @property
    unsigned GetNumChars() const;
    /// Return width of row by index.
    /// @property{get_rowWidths}
    int GetRowWidth(unsigned index) const;
    /// Return position of character by index relative to the text element origin.
    /// @property{get_charPositions}
    Vector2 GetCharPosition(unsigned index);
    /// Return size of character by index.
    /// @property{get_charSizes}
    Vector2 GetCharSize(unsigned index);
    /// Return corner color.
    /// @property{get_colors}
    const Color& GetColor(Corner corner) const;
    /// Return opacity.
    /// @property
    float GetOpacity() const;
    /// Return whether text has fixed screen size.
    /// @property
    bool IsFixedScreenSize() const { return fixedScreenSize_; }
    /// Return how the text rotates in relation to the camera.
    /// @property
    FaceCameraMode GetFaceCameraMode() const { return faceCameraMode_; }

    /// Set font attribute.
    void SetFontAttr(const ResourceRef& value);
    /// Return font attribute.
    ResourceRef GetFontAttr() const;
    /// Set material attribute.
    void SetMaterialAttr(const ResourceRef& value);
    /// Return material attribute.
    ResourceRef GetMaterialAttr() const;
    /// Set text attribute.
    void SetTextAttr(const String& value);
    /// Return text attribute.
    String GetTextAttr() const;

    /// Get color attribute. Uses just the top-left color.
    const Color& GetColorAttr() const { return text_.colors_[0]; }

protected:
    /// Handle node being assigned.
    void OnNodeSet(Node* node) override;
    /// Recalculate the world-space bounding box.
    void OnWorldBoundingBoxUpdate() override;
    /// Mark text & geometry dirty.
    void MarkTextDirty();
    /// Update text %UI batches.
    void UpdateTextBatches();
    /// Create materials for text rendering. May only be called from the main thread. Text %UI batches must be up-to-date.
    void UpdateTextMaterials(bool forceUpdate = false);
    /// Recalculate camera facing and fixed screen size.
    void CalculateFixedScreenSize(const FrameInfo& frame);

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
    /// Custom world transform for facing the camera automatically.
    Matrix3x4 customWorldTransform_;
    /// Text rotation mode in relation to the camera.
    FaceCameraMode faceCameraMode_;
    /// Minimal angle between text normal and look-at direction.
    float minAngle_;
    /// Fixed screen size flag.
    bool fixedScreenSize_;
    /// Text needs update flag.
    bool textDirty_;
    /// Geometry dirty flag.
    bool geometryDirty_;
    /// Flag for whether currently using SDF shader defines in the generated material.
    bool usingSDFShader_;
    /// Font texture data lost flag.
    bool fontDataLost_;
};

}

