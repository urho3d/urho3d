// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../UI/BorderImage.h"

namespace Urho3D
{

/// %Window movement and resizing modes.
enum WindowDragMode
{
    DRAG_NONE,
    DRAG_MOVE,
    DRAG_RESIZE_TOPLEFT,
    DRAG_RESIZE_TOP,
    DRAG_RESIZE_TOPRIGHT,
    DRAG_RESIZE_RIGHT,
    DRAG_RESIZE_BOTTOMRIGHT,
    DRAG_RESIZE_BOTTOM,
    DRAG_RESIZE_BOTTOMLEFT,
    DRAG_RESIZE_LEFT
};

/// %Window %UI element that can optionally by moved or resized.
class URHO3D_API Window : public BorderImage
{
    URHO3D_OBJECT(Window, BorderImage);

public:
    /// Construct.
    explicit Window(Context* context);
    /// Destruct.
    ~Window() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Return UI rendering batches.
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;

    /// React to mouse hover.
    void OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override;
    /// React to mouse drag begin.
    void
        OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override;
    /// React to mouse drag motion.
    void OnDragMove
        (const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers,
            Cursor* cursor) override;
    /// React to mouse drag end.
    void
        OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) override;
    /// React to mouse drag cancel.
    void
        OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) override;

    /// Set whether can be moved.
    /// @property
    void SetMovable(bool enable);
    /// Set whether can be resized.
    /// @property
    void SetResizable(bool enable);
    /// Set whether resizing width is fixed.
    /// @property
    void SetFixedWidthResizing(bool enable);
    /// Set whether resizing height is fixed.
    /// @property
    void SetFixedHeightResizing(bool enable);
    /// Set resize area width at edges.
    /// @property
    void SetResizeBorder(const IntRect& rect);
    /// Set modal flag. When the modal flag is set, the focused window needs to be dismissed first to allow other UI elements to gain focus.
    /// @property
    void SetModal(bool modal);
    /// Set modal shade color.
    /// @property
    void SetModalShadeColor(const Color& color);
    /// Set modal frame color.
    /// @property
    void SetModalFrameColor(const Color& color);
    /// Set modal frame size.
    /// @property
    void SetModalFrameSize(const IntVector2& size);
    /// Set whether model window can be dismissed with the escape key. Default true.
    /// @property
    void SetModalAutoDismiss(bool enable);

    /// Return whether is movable.
    /// @property
    bool IsMovable() const { return movable_; }

    /// Return whether is resizable.
    /// @property
    bool IsResizable() const { return resizable_; }

    /// Return whether is resizing width is fixed.
    /// @property
    bool GetFixedWidthResizing() const { return fixedWidthResizing_; }

    /// Return whether is resizing height is fixed.
    /// @property
    bool GetFixedHeightResizing() const { return fixedHeightResizing_; }

    /// Return resize area width at edges.
    /// @property
    const IntRect& GetResizeBorder() const { return resizeBorder_; }

    /// Return modal flag.
    /// @property
    bool IsModal() const { return modal_; }

    /// Get modal shade color.
    /// @property
    const Color& GetModalShadeColor() const { return modalShadeColor_; }

    /// Get modal frame color.
    /// @property
    const Color& GetModalFrameColor() const { return modalFrameColor_; }

    /// Get modal frame size.
    /// @property
    const IntVector2& GetModalFrameSize() const { return modalFrameSize_; }

    /// Return whether can be dismissed with escape key.
    /// @property
    bool GetModalAutoDismiss() const { return modalAutoDismiss_; }

protected:
    /// Identify drag mode (move/resize).
    WindowDragMode GetDragMode(const IntVector2& position) const;
    /// Set cursor shape based on drag mode.
    void SetCursorShape(WindowDragMode mode, Cursor* cursor) const;
    /// Validate window position.
    void ValidatePosition();
    /// Check whether alignment supports moving and resizing.
    bool CheckAlignment() const;

    /// Movable flag.
    bool movable_;
    /// Resizable flag.
    bool resizable_;
    /// Fixed width resize flag.
    bool fixedWidthResizing_;
    /// Fixed height resize flag.
    bool fixedHeightResizing_;
    /// Resize area width at edges.
    IntRect resizeBorder_;
    /// Current drag mode.
    WindowDragMode dragMode_;
    /// Mouse position at drag begin.
    IntVector2 dragBeginCursor_;
    /// Original position at drag begin.
    IntVector2 dragBeginPosition_;
    /// Original size at drag begin.
    IntVector2 dragBeginSize_;
    /// Modal flag.
    bool modal_;
    /// Modal auto dismiss (with escape key) flag. Default true.
    bool modalAutoDismiss_;
    /// Modal shade color, used when modal flag is set.
    Color modalShadeColor_;
    /// Modal frame color, used when modal flag is set.
    Color modalFrameColor_;
    /// Modal frame size, used when modal flag is set.
    IntVector2 modalFrameSize_;
};

}
