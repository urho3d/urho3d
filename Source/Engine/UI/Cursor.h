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

#include "BorderImage.h"
#include "Image.h"
#include "Texture.h"

#include <SDL_mouse.h>

namespace Urho3D
{

/// %Cursor shapes recognized by the UI subsystem.
enum CursorShape
{
    CS_NORMAL = 0,
    CS_RESIZEVERTICAL,
    CS_RESIZEDIAGONAL_TOPRIGHT,
    CS_RESIZEHORIZONTAL,
    CS_RESIZEDIAGONAL_TOPLEFT,
    CS_ACCEPTDROP,
    CS_REJECTDROP,
    CS_BUSY,
    CS_MAX_SHAPES
};

/// %Cursor image and hotspot information.
struct CursorShapeInfo
{
    /// Construct with defaults.
    CursorShapeInfo() :
        imageRect_(IntRect::ZERO),
        hotSpot_(IntVector2::ZERO),
        osCursor_(0),
        systemDefined_(false)
    {
    }
    
    /// Image.
    SharedPtr<Image> image_;
    /// Texture.
    SharedPtr<Texture> texture_;
    /// Image rectangle.
    IntRect imageRect_;
    /// Hotspot coordinates.
    IntVector2 hotSpot_;
    /// OS cursor.
    SDL_Cursor* osCursor_;
    /// Whether the OS cursor is system defined.
    bool systemDefined_;
};

/// Mouse cursor %UI element.
class URHO3D_API Cursor : public BorderImage
{
    OBJECT(Cursor);
    
public:
    /// Construct.
    Cursor(Context* context);
    /// Destruct.
    virtual ~Cursor();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Return UI rendering batches.
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);
    
    /// Define a shape.
    void DefineShape(CursorShape shape, Image* image, const IntRect& imageRect, const IntVector2& hotSpot);
    /// Set current shape.
    void SetShape(CursorShape shape);
    /// Set whether to use system default shapes. Is only possible when the OS mouse cursor has been set visible from the Input subsystem.
    void SetUseSystemShapes(bool enable);
    /// Get current shape.
    CursorShape GetShape() const { return shape_; }
    /// Return whether is using system default shapes.
    bool GetUseSystemShapes() const { return useSystemShapes_; }
    
    /// Set shapes attribute.
    void SetShapesAttr(VariantVector value);
    /// Return shapes attribute.
    VariantVector GetShapesAttr() const;

protected:
    /// Apply the current shape.
    void ApplyShape();
    /// Handle operating system mouse cursor visibility change event.
    void HandleMouseVisibleChanged(StringHash eventType, VariantMap& eventData);
    
    /// Current shape index.
    CursorShape shape_;
    /// Shape definitions.
    CursorShapeInfo shapeInfos_[CS_MAX_SHAPES];
    /// Use system default shapes flag.
    bool useSystemShapes_;
};

}
