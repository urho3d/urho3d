// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Graphics/Material.h"
#include "../GraphicsAPI/GraphicsDefs.h"
#include "../Math/Color.h"
#include "../Math/Rect.h"

namespace Urho3D
{

class PixelShader;
class Graphics;
class Matrix3x4;
class Texture;
class UIElement;

static const unsigned UI_VERTEX_SIZE = 6;

/// %UI rendering draw call.
class URHO3D_API UIBatch
{
public:
    /// Construct with defaults.
    UIBatch();
    /// Construct.
    UIBatch(UIElement* element, BlendMode blendMode, const IntRect& scissor, Texture* texture, PODVector<float>* vertexData);

    /// Set new color for the batch. Overrides gradient.
    void SetColor(const Color& color, bool overrideAlpha = false);
    /// Restore UI element's default color.
    void SetDefaultColor();
    /// Add a quad.
    void AddQuad(float x, float y, float width, float height, int texOffsetX, int texOffsetY, int texWidth = 0, int texHeight = 0);
    /// Add a quad using a transform matrix.
    void AddQuad(const Matrix3x4& transform, int x, int y, int width, int height, int texOffsetX, int texOffsetY, int texWidth = 0,
        int texHeight = 0);
    /// Add a quad with tiled texture.
    void AddQuad(int x, int y, int width, int height, int texOffsetX, int texOffsetY, int texWidth, int texHeight, bool tiled);
    /// Add a quad with freeform points and UVs. Uses the current color, not gradient. Points should be specified in clockwise order.
    void AddQuad(const Matrix3x4& transform, const IntVector2& a, const IntVector2& b, const IntVector2& c, const IntVector2& d,
        const IntVector2& texA, const IntVector2& texB, const IntVector2& texC, const IntVector2& texD);
    /// Add a quad with freeform points, UVs and colors. Points should be specified in clockwise order.
    void AddQuad(const Matrix3x4& transform, const IntVector2& a, const IntVector2& b, const IntVector2& c, const IntVector2& d,
        const IntVector2& texA, const IntVector2& texB, const IntVector2& texC, const IntVector2& texD, const Color& colA,
        const Color& colB, const Color& colC, const Color& colD);
    /// Merge with another batch.
    bool Merge(const UIBatch& batch);
    /// Return an interpolated color for the UI element.
    unsigned GetInterpolatedColor(float x, float y);

    /// Add or merge a batch.
    static void AddOrMerge(const UIBatch& batch, PODVector<UIBatch>& batches);

    /// Element this batch represents.
    UIElement* element_{};
    /// Blending mode.
    BlendMode blendMode_{BLEND_REPLACE};
    /// Scissor rectangle.
    IntRect scissor_;
    /// Texture.
    Texture* texture_{};
    /// Inverse texture size.
    Vector2 invTextureSize_{Vector2::ONE};
    /// Vertex data.
    PODVector<float>* vertexData_{};
    /// Vertex data start index.
    unsigned vertexStart_{};
    /// Vertex data end index.
    unsigned vertexEnd_{};
    /// Current color. By default calculated from the element.
    unsigned color_{};
    /// Gradient flag.
    bool useGradient_{};
    /// Custom material.
    Material* customMaterial_{};

    /// Position adjustment vector for pixel-perfect rendering. Initialized by UI.
    static Vector3 posAdjust;
};

}
