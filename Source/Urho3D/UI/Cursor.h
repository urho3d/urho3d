// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../GraphicsAPI/Texture.h"
#include "../Resource/Image.h"
#include "../UI/BorderImage.h"

struct SDL_Cursor;

namespace Urho3D
{

/// %Cursor shapes recognized by the UI subsystem.
enum CursorShape
{
    CS_NORMAL = 0,
    CS_IBEAM,
    CS_CROSS,
    CS_RESIZEVERTICAL,
    CS_RESIZEDIAGONAL_TOPRIGHT,
    CS_RESIZEHORIZONTAL,
    CS_RESIZEDIAGONAL_TOPLEFT,
    CS_RESIZE_ALL,
    CS_ACCEPTDROP,
    CS_REJECTDROP,
    CS_BUSY,
    CS_BUSY_ARROW,
    CS_MAX_SHAPES
};

/// %Cursor image and hotspot information.
struct URHO3D_API CursorShapeInfo
{
    /// Construct with defaults.
    CursorShapeInfo() :
        imageRect_(IntRect::ZERO),
        hotSpot_(IntVector2::ZERO),
        osCursor_(nullptr),
        systemDefined_(false),
        systemCursor_(-1)
    {
    }

    /// Construct with system cursor.
    explicit CursorShapeInfo(int systemCursor) :
        imageRect_(IntRect::ZERO),
        hotSpot_(IntVector2::ZERO),
        osCursor_(nullptr),
        systemDefined_(false),
        systemCursor_(systemCursor)
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
    /// System cursor index.
    int systemCursor_;
};

/// Mouse cursor %UI element.
class URHO3D_API Cursor : public BorderImage
{
    URHO3D_OBJECT(Cursor, BorderImage);

public:
    /// Construct.
    explicit Cursor(Context* context);
    /// Destruct.
    ~Cursor() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Return UI rendering batches.
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;

    /// Define a shape.
    void DefineShape(const String& shape, Image* image, const IntRect& imageRect, const IntVector2& hotSpot);
    /// Define a shape.
    void DefineShape(CursorShape shape, Image* image, const IntRect& imageRect, const IntVector2& hotSpot);
    /// Set current shape.
    /// @property
    void SetShape(const String& shape);
    /// Set current shape.
    void SetShape(CursorShape shape);
    /// Set whether to use system default shapes. Is only possible when the OS mouse cursor has been set visible from the Input subsystem.
    /// @property
    void SetUseSystemShapes(bool enable);

    /// Get current shape.
    /// @property
    const String& GetShape() const { return shape_; }

    /// Return whether is using system default shapes.
    /// @property
    bool GetUseSystemShapes() const { return useSystemShapes_; }

    /// Set shapes attribute.
    void SetShapesAttr(const VariantVector& value);
    /// Return shapes attribute.
    VariantVector GetShapesAttr() const;
    /// Apply pending OS cursor shape. Called by UI. No-op when the OS mouse pointer is not used.
    void ApplyOSCursorShape();

protected:
    /// Handle operating system mouse cursor visibility change event.
    void HandleMouseVisibleChanged(StringHash eventType, VariantMap& eventData);

    /// Current shape definition.
    String shape_;
    /// Shape definitions.
    HashMap<String, CursorShapeInfo> shapeInfos_;
    /// Use system default shapes flag.
    bool useSystemShapes_;
    /// OS cursor shape needs update flag.
    bool osShapeDirty_;
};

}
