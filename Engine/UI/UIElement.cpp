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

#include "Precompiled.h"
#include "Context.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "UIElement.h"
#include "UIEvents.h"

#include "DebugNew.h"

static const String horizontalAlignments[] =
{
    "left",
    "center",
    "right"
};

static const String verticalAlignments[] =
{
    "top",
    "center",
    "bottom"
};

static const String focusModes[] =
{
    "notfocusable",
    "resetfocus",
    "focusable",
    "focusabledefocusable"
};

static const String dragDropModes[] =
{
    "disabled",
    "source",
    "target",
    "sourceandtarget"
};

OBJECTTYPESTATIC(UIElement);

UIElement::UIElement(Context* context) :
    Object(context),
    parent_(0),
    clipBorder_(IntRect::ZERO),
    priority_(0),
    opacity_(1.0f),
    bringToFront_(false),
    bringToBack_(true),
    clipChildren_(false),
    active_(false),
    focusMode_(FM_NOTFOCUSABLE),
    focus_(false),
    selected_(false),
    visible_(true),
    hovering_(false),
    dragDropMode_(DD_DISABLED),
    layoutMode_(LM_FREE),
    layoutSpacing_(0),
    layoutBorder_(IntRect::ZERO),
    resizeNestingLevel_(0),
    layoutNestingLevel_(0),
    position_(IntVector2::ZERO),
    size_(IntVector2::ZERO),
    minSize_(IntVector2::ZERO),
    maxSize_(M_MAX_INT, M_MAX_INT),
    childOffset_(IntVector2::ZERO),
    horizontalAlignment_(HA_LEFT),
    verticalAlignment_(VA_TOP),
    positionDirty_(true),
    opacityDirty_(true),
    derivedColorDirty_(true),
    colorGradient_(false)
{
}

UIElement::~UIElement()
{
    // If child elements have outside references, detach them
    while (children_.Size())
    {
        const SharedPtr<UIElement>& element = children_.Back();
        if (element.GetRefCount() > 1)
        {
            element->parent_ = 0;
            element->MarkDirty();
        }
        children_.Pop();
    }
}

void UIElement::RegisterObject(Context* context)
{
    context->RegisterFactory<UIElement>();
}

void UIElement::SetStyle(const XMLElement& element)
{
    if (element.HasAttribute("name"))
        name_ = element.GetString("name");
    if (element.HasChildElement("position"))
        SetPosition(element.GetChildElement("position").GetIntVector2("value"));
    if (element.HasChildElement("size"))
        SetSize(element.GetChildElement("size").GetIntVector2("value"));
    if (element.HasChildElement("width"))
        SetWidth(element.GetChildElement("width").GetInt("value"));
    if (element.HasChildElement("height"))
        SetHeight(element.GetChildElement("height").GetInt("value"));
    if (element.HasChildElement("minsize"))
        SetMinSize(element.GetChildElement("minsize").GetIntVector2("value"));
    if (element.HasChildElement("minwidth"))
        SetMinWidth(element.GetChildElement("minwidth").GetInt("value"));
    if (element.HasChildElement("minheight"))
        SetMinHeight(element.GetChildElement("minheight").GetInt("value"));
    if (element.HasChildElement("maxsize"))
        SetMaxSize(element.GetChildElement("maxsize").GetIntVector2("value"));
    if (element.HasChildElement("maxwidth"))
        SetMinWidth(element.GetChildElement("maxwidth").GetInt("value"));
    if (element.HasChildElement("maxheight"))
        SetMinHeight(element.GetChildElement("maxheight").GetInt("value"));
    if (element.HasChildElement("fixedsize"))
        SetFixedSize(element.GetChildElement("fixedsize").GetIntVector2("value"));
    if (element.HasChildElement("fixedwidth"))
        SetFixedWidth(element.GetChildElement("fixedwidth").GetInt("value"));
    if (element.HasChildElement("fixedheight"))
        SetFixedHeight(element.GetChildElement("fixedheight").GetInt("value"));
    if (element.HasChildElement("alignment"))
    {
        XMLElement alignElem = element.GetChildElement("alignment");
        
        String horiz;
        String vert;
        if (alignElem.HasAttribute("horizontal"))
            horiz = alignElem.GetStringLower("horizontal");
        if (alignElem.HasAttribute("vertical"))
            vert = alignElem.GetStringLower("vertical");
        if (alignElem.HasAttribute("h"))
            horiz = alignElem.GetStringLower("h");
        if (alignElem.HasAttribute("v"))
            vert = alignElem.GetStringLower("v");
        if (!horiz.Empty())
            SetHorizontalAlignment((HorizontalAlignment)GetStringListIndex(horiz, horizontalAlignments, 3, 0));
        if (!vert.Empty())
            SetVerticalAlignment((VerticalAlignment)GetStringListIndex(vert, verticalAlignments, 3, 0));
    }
    if (element.HasChildElement("clipborder"))
        SetClipBorder(element.GetChildElement("clipborder").GetIntRect("value"));
    if (element.HasChildElement("priority"))
        SetPriority(element.GetChildElement("priority").GetInt("value"));
    if (element.HasChildElement("opacity"))
        SetOpacity(element.GetChildElement("opacity").GetFloat("value"));
    if (element.HasChildElement("color"))
    {
        XMLElement colorElem = element.GetChildElement("color");
        if (colorElem.HasAttribute("value"))
            SetColor(colorElem.GetColor("value"));
        if (colorElem.HasAttribute("topleft"))
            SetColor(C_TOPLEFT, colorElem.GetColor("topleft"));
        if (colorElem.HasAttribute("topright"))
            SetColor(C_TOPRIGHT, colorElem.GetColor("topright"));
        if (colorElem.HasAttribute("bottomleft"))
            SetColor(C_BOTTOMLEFT, colorElem.GetColor("bottomleft"));
        if (colorElem.HasAttribute("bottomright"))
            SetColor(C_BOTTOMRIGHT, colorElem.GetColor("bottomright"));
    }
    if (element.HasChildElement("bringtofront"))
        SetBringToFront(element.GetChildElement("bringtofront").GetBool("enable"));
    if (element.HasChildElement("bringtoback"))
        SetBringToBack(element.GetChildElement("bringtoback").GetBool("enable"));
    if (element.HasChildElement("clipchildren"))
        SetClipChildren(element.GetChildElement("clipchildren").GetBool("enable"));
    if (element.HasChildElement("enabled"))
        SetActive(element.GetChildElement("enabled").GetBool("enable"));
    if (element.HasChildElement("selected"))
        SetSelected(element.GetChildElement("selected").GetBool("enable"));
    if (element.HasChildElement("visible"))
        SetVisible(element.GetChildElement("visible").GetBool("enable"));
    if (element.HasChildElement("focusmode"))
    {
        String focusMode = element.GetChildElement("focusmode").GetStringLower("value");
        SetFocusMode((FocusMode)GetStringListIndex(focusMode, focusModes, 4, 0));
        if (focusMode == "defocusable")
            SetFocusMode(FM_FOCUSABLE_DEFOCUSABLE);
    }
    if (element.HasChildElement("dragdropmode"))
    {
        String dragDropMode = element.GetChildElement("dragdropmode").GetStringLower("value");
        SetDragDropMode(GetStringListIndex(dragDropMode, dragDropModes, 4, 0));
    }
    if (element.HasChildElement("layout"))
    {
        XMLElement layoutElem = element.GetChildElement("layout");
        String mode = layoutElem.GetStringLower("mode");
        if (mode == "free")
            layoutMode_ = LM_FREE;
        if ((mode == "horizontal") || (mode == "h"))
            layoutMode_ = LM_HORIZONTAL;
        if ((mode == "vertical") || (mode == "v"))
            layoutMode_ = LM_VERTICAL;
        
        if (layoutElem.HasAttribute("spacing"))
            layoutSpacing_ = Max(layoutElem.GetInt("spacing"), 0);
        if (layoutElem.HasAttribute("border"))
            SetLayoutBorder(layoutElem.GetIntRect("border"));
        else
            UpdateLayout();
    }
    if (element.HasChildElement("vars"))
        vars_ = element.GetChildElement("vars").GetVariantMap();
}

void UIElement::Update(float timeStep)
{
}

void UIElement::GetBatches(PODVector<UIBatch>& batches, PODVector<UIQuad>& quads, const IntRect& currentScissor)
{
    // Reset hovering for next frame
    hovering_ = false;
}

void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    hovering_ = true;
}

void UIElement::OnClick(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
}

void UIElement::OnDragStart(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
}

void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
}

void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, Cursor* cursor)
{
}

bool UIElement::OnDragDropTest(UIElement* source)
{
    return true;
}

bool UIElement::OnDragDropFinish(UIElement* source)
{
    return true;
}

void UIElement::OnWheel(int delta, int buttons, int qualifiers)
{
}

void UIElement::OnKey(int key, int buttons, int qualifiers)
{
}

void UIElement::OnChar(unsigned char c, int buttons, int qualifiers)
{
}

void UIElement::OnResize()
{
}

void UIElement::OnFocus()
{
}

void UIElement::OnDefocus()
{
}

void UIElement::SetName(const String& name)
{
    name_ = name;
}

void UIElement::SetPosition(const IntVector2& position)
{
    if (position != position_)
    {
        position_ = position;
        MarkDirty();
    }
}

void UIElement::SetPosition(int x, int y)
{
    SetPosition(IntVector2(x, y));
}

void UIElement::SetSize(const IntVector2& size)
{
    ++resizeNestingLevel_;
    
    IntVector2 validatedSize;
    validatedSize.x_ = Clamp(size.x_, minSize_.x_, maxSize_.x_);
    validatedSize.y_ = Clamp(size.y_, minSize_.y_, maxSize_.y_);
    
    if (validatedSize != size_)
    {
        size_ = validatedSize;
        
        if (resizeNestingLevel_ == 1)
        {
            // Check if parent element's layout needs to be updated first
            if (parent_)
                parent_->UpdateLayout();
            
            MarkDirty();
            OnResize();
            UpdateLayout();
            
            using namespace Resized;
            
            VariantMap eventData;
            eventData[P_ELEMENT] = (void*)this;
            eventData[P_WIDTH] = size_.x_;
            eventData[P_HEIGHT] = size_.y_;
            SendEvent(E_RESIZED, eventData);
        }
    }
    
    --resizeNestingLevel_;
}

void UIElement::SetSize(int width, int height)
{
    SetSize(IntVector2(width, height));
}

void UIElement::SetWidth(int width)
{
    SetSize(IntVector2(width, size_.y_));
}

void UIElement::SetHeight(int height)
{
    SetSize(IntVector2(size_.x_, height));
}

void UIElement::SetMinSize(const IntVector2& minSize)
{
    minSize_.x_ = Max(minSize.x_, 0);
    minSize_.y_ = Max(minSize.y_, 0);
    SetSize(size_);
}

void UIElement::SetMinSize(int width, int height)
{
    SetMinSize(IntVector2(width, height));
}

void UIElement::SetMinWidth(int width)
{
    SetMinSize(IntVector2(width, minSize_.y_));
}

void UIElement::SetMinHeight(int height)
{
    SetMinSize(IntVector2(minSize_.x_, height));
}

void UIElement::SetMaxSize(const IntVector2& maxSize)
{
    maxSize_.x_ = Max(maxSize.x_, 0);
    maxSize_.y_ = Max(maxSize.y_, 0);
    SetSize(size_);
}

void UIElement::SetMaxSize(int width, int height)
{
    SetMaxSize(IntVector2(width, height));
}

void UIElement::SetMaxWidth(int width)
{
    SetMaxSize(IntVector2(width, maxSize_.y_));
}

void UIElement::SetMaxHeight(int height)
{
    SetMaxSize(IntVector2(maxSize_.x_, height));
}

void UIElement::SetFixedSize(const IntVector2& size)
{
    minSize_ = maxSize_ = IntVector2(Max(size.x_, 0), Max(size.y_, 0));
    SetSize(size);
}

void UIElement::SetFixedSize(int width, int height)
{
    SetFixedSize(IntVector2(width, height));
}

void UIElement::SetFixedWidth(int width)
{
    minSize_.x_ = maxSize_.x_ = Max(width, 0);
    SetWidth(width);
}

void UIElement::SetFixedHeight(int height)
{
    minSize_.y_ = maxSize_.y_ = Max(height, 0);
    SetHeight(height);
}

void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign)
{
    horizontalAlignment_ = hAlign;
    verticalAlignment_ = vAlign;
    MarkDirty();
}

void UIElement::SetHorizontalAlignment(HorizontalAlignment align)
{
    horizontalAlignment_ = align;
    MarkDirty();
}

void UIElement::SetVerticalAlignment(VerticalAlignment align)
{
    verticalAlignment_ = align;
    MarkDirty();
}

void UIElement::SetClipBorder(const IntRect& rect)
{
    clipBorder_.left_ = Max(rect.left_, 0);
    clipBorder_.top_ = Max(rect.top_, 0);
    clipBorder_.right_ = Max(rect.right_, 0);
    clipBorder_.bottom_ = Max(rect.bottom_, 0);
}

void UIElement::SetColor(const Color& color)
{
    for (unsigned i = 0; i < MAX_UIELEMENT_CORNERS; ++i)
        color_[i] = color;
    colorGradient_ = false;
    derivedColorDirty_ = true;
}

void UIElement::SetColor(Corner corner, const Color& color)
{
    color_[corner] = color;
    colorGradient_ = false;
    derivedColorDirty_ = true;
    
    for (unsigned i = 0; i < MAX_UIELEMENT_CORNERS; ++i)
    {
        if ((i != corner) && (color_[i] != color_[corner]))
            colorGradient_ = true;
    }
}

void UIElement::SetPriority(int priority)
{
    priority_ = priority;
}

void UIElement::SetOpacity(float opacity)
{
    opacity_ = Clamp(opacity, 0.0f, 1.0f);
    MarkDirty();
}

void UIElement::SetBringToFront(bool enable)
{
    bringToFront_ = enable;
}

void UIElement::SetBringToBack(bool enable)
{
    bringToBack_ = enable;
}

void UIElement::SetClipChildren(bool enable)
{
    clipChildren_ = enable;
}

void UIElement::SetActive(bool enable)
{
    active_ = enable;
}

void UIElement::SetFocusMode(FocusMode mode)
{
    focusMode_ = mode;
}

void UIElement::SetFocus(bool enable)
{
    if (focusMode_ < FM_FOCUSABLE)
        enable = false;
    
    if (enable != focus_)
    {
        focus_ = enable;
        
        if (enable)
            OnFocus();
        else
            OnDefocus();
        
        using namespace Focused;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        SendEvent(focus_ ? E_FOCUSED : E_DEFOCUSED, eventData);
    }
}

void UIElement::SetSelected(bool enable)
{
    selected_ = enable;
}

void UIElement::SetVisible(bool enable)
{
    if (enable != visible_)
    {
        visible_ = enable;
        
        // Parent's layout may change as a result of visibility change
        if (parent_)
            parent_->UpdateLayout();
        
        using namespace VisibleChanged;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        eventData[P_VISIBLE] = visible_;
        SendEvent(E_VISIBLECHANGED, eventData);
    }
}

void UIElement::SetDragDropMode(unsigned mode)
{
    dragDropMode_ = mode;
}

void UIElement::SetStyle(XMLFile* file, const String& typeName)
{
    if (!file)
        return;
    
    XMLElement rootElem = file->GetRootElement();
    XMLElement childElem = rootElem.GetChildElement("element");
    while (childElem)
    {
        if (childElem.GetString("type") == typeName)
        {
            SetStyle(childElem);
            return;
        }
        childElem = childElem.GetNextElement("element");
    }
}

void UIElement::SetStyleAuto(XMLFile* file)
{
    SetStyle(file, GetTypeName());
}

void UIElement::SetLayout(LayoutMode mode, int spacing, const IntRect& border)
{
    layoutMode_ = mode;
    layoutSpacing_ = Max(spacing, 0);
    layoutBorder_ = IntRect(Max(border.left_, 0), Max(border.top_, 0), Max(border.right_, 0), Max(border.bottom_, 0));
    UpdateLayout();
}

void UIElement::SetLayoutMode(LayoutMode mode)
{
    layoutMode_ = mode;
    UpdateLayout();
}

void UIElement::SetLayoutSpacing(int spacing)
{
    layoutSpacing_ = Max(spacing, 0);
    UpdateLayout();
}

void UIElement::SetLayoutBorder(const IntRect& border)
{
    layoutBorder_ = IntRect(Max(border.left_, 0), Max(border.top_, 0), Max(border.right_, 0), Max(border.bottom_, 0));
    UpdateLayout();
}

void UIElement::UpdateLayout()
{
    if ((layoutMode_ == LM_FREE) || (layoutNestingLevel_))
        return;
    
    // Prevent further updates while this update happens
    DisableLayoutUpdate();
    
    Vector<int> positions;
    Vector<int> sizes;
    Vector<int> minSizes;
    Vector<int> maxSizes;
    
    if (layoutMode_ == LM_HORIZONTAL)
    {
        int minChildHeight = 0;
        
        for (unsigned i = 0; i < children_.Size(); ++i)
        {
            if (!children_[i]->IsVisible())
                continue;
            positions.Push(0);
            sizes.Push(children_[i]->GetWidth());
            minSizes.Push(children_[i]->GetMinWidth());
            maxSizes.Push(children_[i]->GetMaxWidth());
            minChildHeight = Max(minChildHeight, children_[i]->GetMinHeight());
        }
        
        CalculateLayout(positions, sizes, minSizes, maxSizes, GetWidth(), layoutBorder_.left_, layoutBorder_.right_,
            layoutSpacing_);
        
        int width = CalculateLayoutParentSize(sizes, layoutBorder_.left_, layoutBorder_.right_, layoutSpacing_);
        int height = Max(GetHeight(), minChildHeight + layoutBorder_.top_ + layoutBorder_.bottom_);
        int minWidth = Min(CalculateLayoutParentSize(minSizes, layoutBorder_.left_, layoutBorder_.right_, layoutSpacing_), maxSize_.x_);
        int minHeight = Min(minChildHeight + layoutBorder_.top_ + layoutBorder_.bottom_, maxSize_.y_);
        // Respect fixed size if already set
        if (minSize_.x_ != maxSize_.x_)
            minSize_.x_ = minWidth;
        if (minSize_.y_ != maxSize_.y_)
            minSize_.y_ = minHeight;
        SetSize(width, height);
        // Validate the size before resizing child elements, in case of min/max limits
        width = size_.x_;
        height = size_.y_;
        
        unsigned j = 0;
        for (unsigned i = 0; i < children_.Size(); ++i)
        {
            if (!children_[i]->IsVisible())
                continue;
            children_[i]->SetHorizontalAlignment(HA_LEFT);
            children_[i]->SetPosition(positions[j], GetLayoutChildPosition(children_[i]).y_);
            children_[i]->SetSize(sizes[j], height - layoutBorder_.top_ - layoutBorder_.bottom_);
            ++j;
        }
    }
    
    if (layoutMode_ == LM_VERTICAL)
    {
        int minChildWidth = 0;
        int maxChildWidth = M_MAX_INT;
        
        for (unsigned i = 0; i < children_.Size(); ++i)
        {
            if (!children_[i]->IsVisible())
                continue;
            positions.Push(0);
            sizes.Push(children_[i]->GetHeight());
            minSizes.Push(children_[i]->GetMinHeight());
            maxSizes.Push(children_[i]->GetMaxHeight());
            minChildWidth = Max(minChildWidth, children_[i]->GetMinWidth());
        }
        
        CalculateLayout(positions, sizes, minSizes, maxSizes, GetHeight(), layoutBorder_.top_, layoutBorder_.bottom_,
            layoutSpacing_);
        
        int height = CalculateLayoutParentSize(sizes, layoutBorder_.top_, layoutBorder_.bottom_, layoutSpacing_);
        int width = Max(GetWidth(), minChildWidth + layoutBorder_.left_ + layoutBorder_.right_);
        int minHeight = Min(CalculateLayoutParentSize(minSizes, layoutBorder_.top_, layoutBorder_.bottom_, layoutSpacing_), maxSize_.y_);
        int minWidth = Min(minChildWidth + layoutBorder_.left_ + layoutBorder_.right_, maxSize_.x_);
        if (minSize_.x_ != maxSize_.x_)
            minSize_.x_ = minWidth;
        if (minSize_.y_ != maxSize_.y_)
            minSize_.y_ = minHeight;
        SetSize(width, height);
        width = size_.x_;
        height = size_.y_;
        
        unsigned j = 0;
        for (unsigned i = 0; i < children_.Size(); ++i)
        {
            if (!children_[i]->IsVisible())
                continue;
            children_[i]->SetVerticalAlignment(VA_TOP);
            children_[i]->SetPosition(GetLayoutChildPosition(children_[i]).x_, positions[j]);
            children_[i]->SetSize(width - layoutBorder_.left_ - layoutBorder_.right_, sizes[j]);
            ++j;
        }
    }
    
    EnableLayoutUpdate();
}

void UIElement::DisableLayoutUpdate()
{
    ++layoutNestingLevel_;
}

void UIElement::EnableLayoutUpdate()
{
    --layoutNestingLevel_;
}

void UIElement::BringToFront()
{
    // Follow the parent chain to the top level window. If it has BringToFront mode, bring it to front now
    UIElement* root = GetRootElement();
    UIElement* ptr = this;
    while ((ptr) && (ptr->GetParent() != root))
        ptr = ptr->GetParent();
    if ((!ptr) || (!ptr->GetBringToFront()))
        return;
    
    // Get the highest priority used by all other top level elements, assign that to the new front element
    // and decrease others' priority by one. However, take into account only active (enabled) elements
    // and those which have the BringToBack flag set
    int maxPriority = M_MIN_INT;
    Vector<UIElement*> topLevelElements = root->GetChildren();
    for (Vector<UIElement*>::Iterator i = topLevelElements.Begin(); i != topLevelElements.End(); ++i)
    {
        UIElement* other = *i;
        if ((other->IsActive()) && (other->bringToBack_) && (other != ptr))
        {
            int priority = other->GetPriority();
            maxPriority = Max(priority, maxPriority);
            other->SetPriority(priority - 1);
        }
    }
    if (maxPriority != M_MIN_INT)
        ptr->SetPriority(maxPriority);
}

void UIElement::AddChild(UIElement* element)
{
    InsertChild(children_.Size(), element);
}

void UIElement::InsertChild(unsigned index, UIElement* element)
{
    // Check for illegal parent assignments
    if ((!element) || (element == this) || (element->parent_ == this) || (parent_ == element))
        return;
    
    // Add first, then remove from old parent, to ensure the element does not get deleted
    if (index >= children_.Size())
        children_.Push(SharedPtr<UIElement>(element));
    else
        children_.Insert(children_.Begin() + index, SharedPtr<UIElement>(element));
    
    if (element->parent_)
        element->parent_->RemoveChild(element);
    
    element->parent_ = this;
    element->MarkDirty();
    UpdateLayout();
}

void UIElement::RemoveChild(UIElement* element)
{
    for (Vector<SharedPtr<UIElement> >::Iterator i = children_.Begin(); i != children_.End(); ++i)
    {
        if ((*i) == element)
        {
            element->parent_ = 0;
            element->MarkDirty();
            children_.Erase(i);
            UpdateLayout();
            return;
        }
    }
}

void UIElement::RemoveAllChildren()
{
    while (children_.Size())
    {
        const SharedPtr<UIElement>& element = children_.Back();
        element->parent_ = 0;
        element->MarkDirty();
        children_.Pop();
    }
}

void UIElement::Remove()
{
    if (parent_)
        parent_->RemoveChild(this);
}

void UIElement::SetParent(UIElement* parent)
{
    if (parent)
        parent->AddChild(this);
}

IntVector2 UIElement::GetScreenPosition()
{
    if (positionDirty_)
    {
        IntVector2 pos = position_;
        const UIElement* parent = parent_;
        const UIElement* current = this;
        
        while (parent)
        {
            switch (current->horizontalAlignment_)
            {
            case HA_LEFT:
                pos.x_ += parent->position_.x_;
                break;
                
            case HA_CENTER:
                pos.x_ += parent->position_.x_ + parent->size_.x_ / 2 - current->size_.x_ / 2;
                break;
                
            case HA_RIGHT:
                pos.x_ += parent->position_.x_ + parent->size_.x_ - current->size_.x_;
                break;
            }
            switch (current->verticalAlignment_)
            {
            case VA_TOP:
                pos.y_ += parent->position_.y_;
                break;
                
            case VA_CENTER:
                pos.y_ += parent->position_.y_ + parent->size_.y_ / 2 - current->size_.y_ / 2;
                break;
                
            case VA_BOTTOM:
                pos.y_ += parent->position_.y_ + parent->size_.y_ - current->size_.y_;
                break;
            }
            
            pos += parent->childOffset_;
            
            current = parent;
            parent = parent->parent_;
        }
        
        screenPosition_ = pos;
        positionDirty_ = false;
    }
    
    return screenPosition_;
}

float UIElement::GetDerivedOpacity()
{
    if (opacityDirty_)
    {
        float opacity = opacity_;
        const UIElement* parent = parent_;
        
        while (parent)
        {
            opacity *= parent->opacity_;
            parent = parent->parent_;
        }
        
        derivedOpacity_ = opacity;
        opacityDirty_ = false;
    }
    
    return derivedOpacity_;
}

Vector<UIElement*> UIElement::GetChildren(bool recursive) const
{
    if (!recursive)
    {
        Vector<UIElement*> ret;
        for (Vector<SharedPtr<UIElement> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
            ret.Push(*i);
        
        return ret;
    }
    else
    {
        Vector<UIElement*> allChildren;
        GetChildrenRecursive(allChildren);
        
        return allChildren;
    }
}

unsigned UIElement::GetNumChildren(bool recursive) const
{
    if (!recursive)
        return children_.Size();
    else
    {
        unsigned allChildren = children_.Size();
        for (Vector<SharedPtr<UIElement> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
            allChildren += (*i)->GetNumChildren(true);
        
        return allChildren;
    }
}

UIElement* UIElement::GetChild(unsigned index) const
{
    return index < children_.Size() ? children_[index] : (UIElement*)0;
}

UIElement* UIElement::GetChild(const String& name, bool recursive) const
{
    for (Vector<SharedPtr<UIElement> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
    {
        if ((*i)->name_ == name)
            return *i;
        
        if (recursive)
        {
            UIElement* element = (*i)->GetChild(name, true);
            if (element)
                return element;
        }
    }
    
    return 0;
}

UIElement* UIElement::GetRootElement() const
{
    UIElement* root = parent_;
    if (!root)
        return 0;
    while (root->GetParent())
        root = root->GetParent();
    return root;
}

unsigned UIElement::GetUIntColor()
{
    if (derivedColorDirty_)
    {
        Color color = color_[C_TOPLEFT];
        color.a_ *= GetDerivedOpacity();
        uintColor_ = color.ToUInt();
        derivedColorDirty_ = false;
    }
    
    return uintColor_;
}

IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition)
{
    return screenPosition - GetScreenPosition();
}

IntVector2 UIElement::ElementToScreen(const IntVector2& position)
{
    return position + GetScreenPosition();
}

bool UIElement::IsInside(IntVector2 position, bool isScreen)
{
    if (isScreen)
        position = ScreenToElement(position);
    return (position.x_ >= 0) && (position.y_ >= 0) && (position.x_ < size_.x_) && (position.y_ < size_.y_);
}

bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen)
{
    // If child elements are clipped, no need to expand the rect
    if (clipChildren_)
        return IsInside(position, isScreen);
    
    if (!isScreen)
        position = ElementToScreen(position);
    
    IntRect combined = GetCombinedScreenRect();
    return (position.x_ >= combined.left_) && (position.y_ >= combined.top_) && (position.x_ < combined.right_) &&
        (position.y_ < combined.bottom_);
}

IntRect UIElement::GetCombinedScreenRect()
{
    IntVector2 screenPosition(GetScreenPosition());
    IntRect combined(screenPosition.x_, screenPosition.y_, screenPosition.x_ + size_.x_, screenPosition.y_ + size_.y_);
    
    for (Vector<SharedPtr<UIElement> >::Iterator i = children_.Begin(); i != children_.End(); ++i)
    {
        IntVector2 childPos = (*i)->GetScreenPosition();
        const IntVector2& childSize = (*i)->GetSize();
        if (childPos.x_ < combined.left_)
            combined.left_ = childPos.x_;
        if (childPos.y_ < combined.top_)
            combined.top_ = childPos.y_;
        if (childPos.x_ + childSize.x_ > combined.right_)
            combined.right_ = childPos.x_ + childSize.x_;
        if (childPos.y_ + childSize.y_ > combined.bottom_)
            combined.bottom_ = childPos.y_ + childSize.y_;
    }
    
    return combined;
}

void UIElement::SetChildOffset(const IntVector2& offset)
{
    if (offset != childOffset_)
    {
        childOffset_ = offset;
        for (Vector<SharedPtr<UIElement> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
            (*i)->MarkDirty();
    }
}

void UIElement::SetHovering(bool enable)
{
    hovering_ = enable;
}

void UIElement::AdjustScissor(IntRect& currentScissor)
{
    if (clipChildren_)
    {
        IntVector2 screenPos = GetScreenPosition();
        currentScissor.left_ = Max(currentScissor.left_, screenPos.x_ + clipBorder_.left_);
        currentScissor.top_ = Max(currentScissor.top_, screenPos.y_ + clipBorder_.top_);
        currentScissor.right_ = Min(currentScissor.right_, screenPos.x_ + size_.x_ - clipBorder_.right_);
        currentScissor.bottom_ = Min(currentScissor.bottom_, screenPos.y_ + size_.y_ - clipBorder_.bottom_);
        
        if (currentScissor.right_ < currentScissor.left_)
            currentScissor.right_ = currentScissor.left_;
        if (currentScissor.bottom_ < currentScissor.top_)
            currentScissor.bottom_ = currentScissor.top_;
    }
}

void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<UIQuad>& quads, IntRect
    currentScissor)
{
    unsigned initialSize = quads.Size();
    GetBatches(batches, quads, currentScissor);
    for (unsigned i = initialSize; i < quads.Size(); ++i)
    {
        quads[i].left_ += offset.x_;
        quads[i].top_ += offset.y_;
        quads[i].right_ += offset.x_;
        quads[i].bottom_ += offset.y_;
    }
    
    AdjustScissor(currentScissor);
    for (Vector<SharedPtr<UIElement> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
    {
        if ((*i)->IsVisible())
            (*i)->GetBatchesWithOffset(offset, batches, quads, currentScissor);
    }
}

void UIElement::MarkDirty()
{
    positionDirty_ = true;
    opacityDirty_ = true;
    derivedColorDirty_ = true;
    
    for (Vector<SharedPtr<UIElement> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
        (*i)->MarkDirty();
}

void UIElement::GetChildrenRecursive(Vector<UIElement*>& dest) const
{
    for (Vector<SharedPtr<UIElement> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
    {
        dest.Push(*i);
        (*i)->GetChildrenRecursive(dest);
    }
}

int UIElement::CalculateLayoutParentSize(const Vector<int>& sizes, int begin, int end, int spacing)
{
    int width = begin + end;
    for (unsigned i = 0; i < sizes.Size(); ++i)
    {
        // If calculating maximum size, and the default is specified, do not overflow it
        if (sizes[i] == M_MAX_INT)
            return M_MAX_INT;
        width += sizes[i];
        if (i < sizes.Size() - 1)
            width += spacing;
    }
    return width;
}

void UIElement::CalculateLayout(Vector<int>& positions, Vector<int>& sizes, const Vector<int>& minSizes,
        const Vector<int>& maxSizes, int targetSize, int begin, int end, int spacing)
{
    int numChildren = sizes.Size();
    if (!numChildren)
        return;
    int targetTotalSize = targetSize - begin - end - (numChildren - 1) * spacing;
    if (targetTotalSize < 0)
        targetTotalSize = 0;
    int targetChildSize = targetTotalSize / numChildren;
    int remainder = targetTotalSize % numChildren;
    float add = (float)remainder / numChildren;
    float acc = 0.0f;
    
    // Initial pass
    for (int i = 0; i < numChildren; ++i)
    {
        int targetSize = targetChildSize;
        if (remainder)
        {
            acc += add;
            if (acc >= 0.5f)
            {
                acc -= 1.0f;
                ++targetSize;
                --remainder;
            }
        }
        sizes[i] = Clamp(targetSize, minSizes[i], maxSizes[i]);
    }
    
    // Error correction passes
    for (;;)
    {
        int actualTotalSize = 0;
        for (int i = 0; i < numChildren; ++i)
            actualTotalSize += sizes[i];
        int error = targetTotalSize - actualTotalSize;
        // Break if no error
        if (!error)
            break;
        
        // Check which of the children can be resized to correct the error. If none, must break
        Vector<unsigned> resizable;
        for (int i = 0; i < numChildren; ++i)
        {
            if ((error < 0) && (sizes[i] > minSizes[i]))
                resizable.Push(i);
            else if ((error > 0) && (sizes[i] < maxSizes[i]))
                resizable.Push(i);
        }
        if (resizable.Empty())
            break;
        
        int numResizable = resizable.Size();
        int errorPerChild = error / numResizable;
        remainder = (abs(error)) % numResizable;
        add = (float)remainder / numResizable;
        acc = 0.0f;
        
        for (int i = 0; i < numResizable; ++i)
        {
            unsigned idx = resizable[i];
            int targetSize = sizes[idx] + errorPerChild;
            if (remainder)
            {
                acc += add;
                if (acc >= 0.5f)
                {
                    acc -= 1.0f;
                    targetSize = error < 0 ? targetSize - 1 : targetSize + 1;
                    --remainder;
                }
            }
            
            sizes[idx] = Clamp(targetSize, minSizes[idx], maxSizes[idx]);
        }
    }
    
    // Calculate final positions
    int position = begin;
    for (int i = 0; i < numChildren; ++i)
    {
        positions[i] = position;
        position += sizes[i];
        position += spacing;
    }
}

IntVector2 UIElement::GetLayoutChildPosition(UIElement* child)
{
    IntVector2 ret(IntVector2::ZERO);
    
    HorizontalAlignment ha = child->GetHorizontalAlignment();
    switch (ha)
    {
    case HA_LEFT:
        ret.x_ = layoutBorder_.left_;
        break;
        
    case HA_RIGHT:
        ret.x_ = -layoutBorder_.right_;
        break;
    }
    
    VerticalAlignment va = child->GetVerticalAlignment();
    switch (va)
    {
    case VA_TOP:
        ret.y_ = layoutBorder_.top_;
        break;
        
    case VA_BOTTOM:
        ret.y_ = -layoutBorder_.bottom_;
        break;
    }
    
    return ret;
}

