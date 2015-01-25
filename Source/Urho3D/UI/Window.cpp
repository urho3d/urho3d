//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "../Core/Context.h"
#include "../UI/Cursor.h"
#include "../Input/InputEvents.h"
#include "../UI/UI.h"
#include "../UI/UIEvents.h"
#include "../UI/Window.h"

#include "../DebugNew.h"

namespace Urho3D
{

static const int DEFAULT_RESIZE_BORDER = 4;

extern const char* UI_CATEGORY;

Window::Window(Context* context) :
    BorderImage(context),
    movable_(false),
    resizable_(false),
    fixedWidthResizing_(false),
    fixedHeightResizing_(false),
    resizeBorder_(DEFAULT_RESIZE_BORDER, DEFAULT_RESIZE_BORDER, DEFAULT_RESIZE_BORDER, DEFAULT_RESIZE_BORDER),
    dragMode_(DRAG_NONE),
    modal_(false),
    modalAutoDismiss_(true),
    modalShadeColor_(Color::TRANSPARENT),
    modalFrameColor_(Color::TRANSPARENT),
    modalFrameSize_(IntVector2::ZERO)

{
    bringToFront_ = true;
    clipChildren_ = true;
    SetEnabled(true);
}

Window::~Window()
{
}

void Window::RegisterObject(Context* context)
{
    context->RegisterFactory<Window>(UI_CATEGORY);

    COPY_BASE_ATTRIBUTES(BorderImage);
    UPDATE_ATTRIBUTE_DEFAULT_VALUE("Bring To Front", true);
    UPDATE_ATTRIBUTE_DEFAULT_VALUE("Clip Children", true);
    UPDATE_ATTRIBUTE_DEFAULT_VALUE("Is Enabled", true);
    ACCESSOR_ATTRIBUTE("Resize Border", GetResizeBorder, SetResizeBorder, IntRect, IntRect(DEFAULT_RESIZE_BORDER, \
        DEFAULT_RESIZE_BORDER, DEFAULT_RESIZE_BORDER, DEFAULT_RESIZE_BORDER), AM_FILE);
    ACCESSOR_ATTRIBUTE("Is Movable", IsMovable, SetMovable, bool, false, AM_FILE);
    ACCESSOR_ATTRIBUTE("Is Resizable", IsResizable, SetResizable, bool, false, AM_FILE);
    ACCESSOR_ATTRIBUTE("Fixed Width Resizing", GetFixedWidthResizing, SetFixedWidthResizing, bool, false, AM_FILE);
    ACCESSOR_ATTRIBUTE("Fixed Height Resizing", GetFixedHeightResizing, SetFixedHeightResizing, bool, false, AM_FILE);
    ACCESSOR_ATTRIBUTE("Is Modal", IsModal, SetModal, bool, false, AM_FILE);
    ACCESSOR_ATTRIBUTE("Modal Shade Color", GetModalShadeColor, SetModalShadeColor, Color, Color::TRANSPARENT, AM_FILE);
    ACCESSOR_ATTRIBUTE("Modal Frame Color", GetModalFrameColor, SetModalFrameColor, Color, Color::TRANSPARENT, AM_FILE);
    ACCESSOR_ATTRIBUTE("Modal Frame Size", GetModalFrameSize, SetModalFrameSize, IntVector2, IntVector2::ZERO, AM_FILE);
    // Modal auto dismiss is purposefully not an attribute, as using it can make the editor lock up.
    // Instead it should be set false in code when needed
}

void Window::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    if (modal_)
    {
        // Modal shade
        if (modalShadeColor_ != Color::TRANSPARENT)
        {
            UIElement* rootElement = GetRoot();
            const IntVector2& rootSize = rootElement->GetSize();
            UIBatch batch(rootElement, BLEND_ALPHA, IntRect(0, 0, rootSize.x_, rootSize.y_), 0, &vertexData);
            batch.SetColor(modalShadeColor_);
            batch.AddQuad(0, 0, rootSize.x_, rootSize.y_, 0, 0);
            UIBatch::AddOrMerge(batch, batches);
        }

        // Modal frame
        if (modalFrameColor_ != Color::TRANSPARENT && modalFrameSize_ != IntVector2::ZERO)
        {
            UIBatch batch(this, BLEND_ALPHA, currentScissor, 0, &vertexData);
            int x = GetIndentWidth();
            IntVector2 size = GetSize();
            size.x_ -= x;
            batch.SetColor(modalFrameColor_);
            batch.AddQuad(x - modalFrameSize_.x_, -modalFrameSize_.y_, size.x_ + 2 * modalFrameSize_.x_, size.y_ + 2 * modalFrameSize_.y_, 0, 0);
            UIBatch::AddOrMerge(batch, batches);
        }
    }

    BorderImage::GetBatches(batches, vertexData, currentScissor);
}

void Window::OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    UIElement::OnHover(position, screenPosition, buttons, qualifiers, cursor);

    if (dragMode_ == DRAG_NONE)
    {
        WindowDragMode mode = GetDragMode(position);
        SetCursorShape(mode, cursor);
    }
    else
        SetCursorShape(dragMode_, cursor);
}

void Window::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    UIElement::OnDragBegin(position, screenPosition, buttons, qualifiers, cursor);

    if (buttons != MOUSEB_LEFT || !CheckAlignment())
    {
        dragMode_ = DRAG_NONE;
        return;
    }

    dragBeginCursor_ = screenPosition;
    dragBeginPosition_ = GetPosition();
    dragBeginSize_ = GetSize();
    dragMode_ = GetDragMode(position);
    SetCursorShape(dragMode_, cursor);
}

void Window::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, int buttons, int qualifiers, Cursor* cursor)
{
    if (dragMode_ == DRAG_NONE)
        return;

    IntVector2 delta = screenPosition - dragBeginCursor_;
    IntVector2 dragSize;
    IntVector2 resizeBorderSize(resizeBorder_.left_ + resizeBorder_.right_, resizeBorder_.top_ + resizeBorder_.bottom_);

    const IntVector2& position_ = GetPosition();
    const IntVector2& size_ = GetSize();
    const IntVector2& minSize_ = GetMinSize();
    const IntVector2& maxSize_ = GetMaxSize();

    switch (dragMode_)
    {
    case DRAG_MOVE:
        SetPosition(dragBeginPosition_ + delta);
        break;

    case DRAG_RESIZE_TOPLEFT:
        SetPosition(Clamp(dragBeginPosition_.x_ + delta.x_, position_.x_ - (maxSize_.x_ - size_.x_), position_.x_ + (size_.x_ - minSize_.x_)),
            Clamp(dragBeginPosition_.y_ + delta.y_, position_.y_ - (maxSize_.y_ - size_.y_), position_.y_ + (size_.y_ - minSize_.y_)));
        dragSize = dragBeginSize_ - delta;
        fixedWidthResizing_ ? SetFixedWidth(Max(dragSize.x_, resizeBorderSize.x_)) : SetWidth(dragSize.x_);
        fixedHeightResizing_ ? SetFixedHeight(Max(dragSize.y_, resizeBorderSize.y_)) : SetHeight(dragSize.y_);
        break;

    case DRAG_RESIZE_TOP:
        SetPosition(dragBeginPosition_.x_, Clamp(dragBeginPosition_.y_ + delta.y_, position_.y_ - (maxSize_.y_ - size_.y_), position_.y_ + (size_.y_ - minSize_.y_)));
        dragSize = IntVector2(dragBeginSize_.x_, dragBeginSize_.y_ - delta.y_);
        fixedHeightResizing_ ? SetFixedHeight(Max(dragSize.y_, resizeBorderSize.y_)) : SetHeight(dragSize.y_);
        break;

    case DRAG_RESIZE_TOPRIGHT:
        SetPosition(dragBeginPosition_.x_, Clamp(dragBeginPosition_.y_ + delta.y_, position_.y_ - (maxSize_.y_ - size_.y_), position_.y_ + (size_.y_ - minSize_.y_)));
        dragSize = IntVector2(dragBeginSize_.x_ + delta.x_, dragBeginSize_.y_ - delta.y_);
        fixedWidthResizing_ ? SetFixedWidth(Max(dragSize.x_, resizeBorderSize.x_)) : SetWidth(dragSize.x_);
        fixedHeightResizing_ ? SetFixedHeight(Max(dragSize.y_, resizeBorderSize.y_)) : SetHeight(dragSize.y_);
        break;

    case DRAG_RESIZE_RIGHT:
        dragSize = IntVector2(dragBeginSize_.x_ + delta.x_, dragBeginSize_.y_);
        fixedWidthResizing_ ? SetFixedWidth(Max(dragSize.x_, resizeBorderSize.x_)) : SetWidth(dragSize.x_);
        break;

    case DRAG_RESIZE_BOTTOMRIGHT:
        dragSize = dragBeginSize_ + delta;
        fixedWidthResizing_ ? SetFixedWidth(Max(dragSize.x_, resizeBorderSize.x_)) : SetWidth(dragSize.x_);
        fixedHeightResizing_ ? SetFixedHeight(Max(dragSize.y_, resizeBorderSize.y_)) : SetHeight(dragSize.y_);
        break;

    case DRAG_RESIZE_BOTTOM:
        dragSize = IntVector2(dragBeginSize_.x_, dragBeginSize_.y_ + delta.y_);
        fixedHeightResizing_ ? SetFixedHeight(Max(dragSize.y_, resizeBorderSize.y_)) : SetHeight(dragSize.y_);
        break;

    case DRAG_RESIZE_BOTTOMLEFT:
        SetPosition(Clamp(dragBeginPosition_.x_ + delta.x_, position_.x_ - (maxSize_.x_ - size_.x_), position_.x_ + (size_.x_ - minSize_.x_)), dragBeginPosition_.y_);
        dragSize = IntVector2(dragBeginSize_.x_ - delta.x_, dragBeginSize_.y_ + delta.y_);
        fixedWidthResizing_ ? SetFixedWidth(Max(dragSize.x_, resizeBorderSize.x_)) : SetWidth(dragSize.x_);
        fixedHeightResizing_ ? SetFixedHeight(Max(dragSize.y_, resizeBorderSize.y_)) : SetHeight(dragSize.y_);
        break;

    case DRAG_RESIZE_LEFT:
        SetPosition(Clamp(dragBeginPosition_.x_ + delta.x_, position_.x_ - (maxSize_.x_ - size_.x_), position_.x_ + (size_.x_ - minSize_.x_)), dragBeginPosition_.y_);
        dragSize = IntVector2(dragBeginSize_.x_ - delta.x_, dragBeginSize_.y_);
        fixedWidthResizing_ ? SetFixedWidth(Max(dragSize.x_, resizeBorderSize.x_)) : SetWidth(dragSize.x_);
        break;

    default:
        break;
    }

    ValidatePosition();
    SetCursorShape(dragMode_, cursor);
}

void Window::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, int dragButtons, int buttons, Cursor* cursor)
{
    UIElement::OnDragEnd(position, screenPosition, dragButtons, buttons, cursor);

    dragMode_ = DRAG_NONE;
}

void Window::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, int dragButtons, int buttons, Cursor* cursor)
{
    UIElement::OnDragCancel(position, screenPosition, dragButtons, buttons, cursor);

    if (dragButtons == MOUSEB_LEFT)
    {
        dragMode_ = DRAG_NONE;
        SetPosition(dragBeginPosition_);
        SetSize(dragBeginSize_);
    }
}

void Window::SetMovable(bool enable)
{
    movable_ = enable;
}

void Window::SetResizable(bool enable)
{
    resizable_ = enable;
}

void Window::SetFixedWidthResizing(bool enable)
{
    fixedWidthResizing_ = enable;
}

void Window::SetFixedHeightResizing(bool enable)
{
    fixedHeightResizing_ = enable;
}

void Window::SetResizeBorder(const IntRect& rect)
{
    resizeBorder_.left_ = Max(rect.left_, 0);
    resizeBorder_.top_ = Max(rect.top_, 0);
    resizeBorder_.right_ = Max(rect.right_, 0);
    resizeBorder_.bottom_ = Max(rect.bottom_, 0);
}

void Window::SetModal(bool modal)
{
    if (GetSubsystem<UI>()->SetModalElement(this, modal))
    {
        modal_ = modal;

        using namespace ModalChanged;

        VariantMap& eventData = GetEventDataMap();
        eventData[P_ELEMENT] = this;
        eventData[P_MODAL] = modal;
        SendEvent(E_MODALCHANGED, eventData);
    }
}

void Window::SetModalShadeColor(const Color& color)
{
    modalShadeColor_ = color;
}

void Window::SetModalFrameColor(const Color& color)
{
    modalFrameColor_ = color;
}

void Window::SetModalFrameSize(const IntVector2& size)
{
    modalFrameSize_ = size;
}

void Window::SetModalAutoDismiss(bool enable)
{
    modalAutoDismiss_ = enable;
}

WindowDragMode Window::GetDragMode(const IntVector2& position) const
{
    WindowDragMode mode = DRAG_NONE;

    // Top row
    if (position.y_ < resizeBorder_.top_)
    {
        if (movable_)
            mode = DRAG_MOVE;
        if (resizable_)
        {
            mode = DRAG_RESIZE_TOP;
            if (position.x_ < resizeBorder_.left_)
                mode = DRAG_RESIZE_TOPLEFT;
            if (position.x_ >= GetWidth() - resizeBorder_.right_)
                mode = DRAG_RESIZE_TOPRIGHT;
        }
    }
    // Bottom row
    else if (position.y_ >= GetHeight() - resizeBorder_.bottom_)
    {
        if (movable_)
            mode = DRAG_MOVE;
        if (resizable_)
        {
            mode = DRAG_RESIZE_BOTTOM;
            if (position.x_ < resizeBorder_.left_)
                mode = DRAG_RESIZE_BOTTOMLEFT;
            if (position.x_ >= GetWidth() - resizeBorder_.right_)
                mode = DRAG_RESIZE_BOTTOMRIGHT;
        }
    }
    // Middle
    else
    {
        if (movable_)
            mode = DRAG_MOVE;
        if (resizable_)
        {
            if (position.x_ < resizeBorder_.left_)
                mode = DRAG_RESIZE_LEFT;
            if (position.x_ >= GetWidth() - resizeBorder_.right_)
                mode = DRAG_RESIZE_RIGHT;
        }
    }

    return mode;
}

void Window::SetCursorShape(WindowDragMode mode, Cursor* cursor) const
{
    CursorShape shape = CS_NORMAL;

    switch (mode)
    {
    case DRAG_RESIZE_TOP:
    case DRAG_RESIZE_BOTTOM:
        shape = CS_RESIZEVERTICAL;
        break;

    case DRAG_RESIZE_LEFT:
    case DRAG_RESIZE_RIGHT:
        shape = CS_RESIZEHORIZONTAL;
        break;

    case DRAG_RESIZE_TOPRIGHT:
    case DRAG_RESIZE_BOTTOMLEFT:
        shape = CS_RESIZEDIAGONAL_TOPRIGHT;
        break;

    case DRAG_RESIZE_TOPLEFT:
    case DRAG_RESIZE_BOTTOMRIGHT:
        shape = CS_RESIZEDIAGONAL_TOPLEFT;
        break;

    default:
        break;
    }

    if (cursor)
        cursor->SetShape(shape);
}

void Window::ValidatePosition()
{
    // Check that window does not go more than halfway outside its parent in either dimension
    if (!parent_)
        return;

    const IntVector2& parentSize = parent_->GetSize();
    IntVector2 position = GetPosition();
    IntVector2 halfSize = GetSize() / 2;

    position.x_ = Clamp(position.x_, -halfSize.x_, parentSize.x_ - halfSize.x_);
    position.y_ = Clamp(position.y_, -halfSize.y_, parentSize.y_ - halfSize.y_);

    SetPosition(position);
}

bool Window::CheckAlignment() const
{
    // Only top left-alignment is supported for move and resize
    if (GetHorizontalAlignment() == HA_LEFT && GetVerticalAlignment() == VA_TOP)
        return true;
    else
        return false;
}

}
