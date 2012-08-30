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

#include "Precompiled.h"
#include "Context.h"
#include "Log.h"
#include "ResourceCache.h"
#include "Sort.h"
#include "StringUtils.h"
#include "UI.h"
#include "UIElement.h"
#include "UIEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

static const char* horizontalAlignments[] =
{
    "Left",
    "Center",
    "Right",
    0
};

static const char* verticalAlignments[] =
{
    "Top",
    "Center",
    "Bottom",
    0
};

static const char* focusModes[] =
{
    "NotFocusable",
    "ResetFocus",
    "Focusable",
    "FocusableDefocusable",
    0
};

static const char* dragDropModes[] =
{
    "Disabled",
    "Source",
    "Target",
    "SourceAndTarget",
    0
};

static const char* layoutModes[] =
{
    "Free",
    "Horizontal",
    "Vertical",
    0
};

static bool CompareUIElements(const UIElement* lhs, const UIElement* rhs)
{
    return lhs->GetPriority() < rhs->GetPriority();
}

template<> HorizontalAlignment Variant::Get<HorizontalAlignment>() const
{
    return (HorizontalAlignment)GetInt();
}

template<> VerticalAlignment Variant::Get<VerticalAlignment>() const
{
    return (VerticalAlignment)GetInt();
}

template<> FocusMode Variant::Get<FocusMode>() const
{
    return (FocusMode)GetInt();
}

template<> LayoutMode Variant::Get<LayoutMode>() const
{
    return (LayoutMode)GetInt();
}

OBJECTTYPESTATIC(UIElement);

UIElement::UIElement(Context* context) :
    Serializable(context),
    parent_(0),
    clipBorder_(IntRect::ZERO),
    priority_(0),
    bringToFront_(false),
    bringToBack_(true),
    clipChildren_(false),
    sortChildren_(true),
    active_(false),
    selected_(false),
    visible_(true),
    hovering_(false),
    internal_(false),
    focusMode_(FM_NOTFOCUSABLE),
    dragDropMode_(DD_DISABLED),
    layoutMode_(LM_FREE),
    layoutSpacing_(0),
    layoutBorder_(IntRect::ZERO),
    resizeNestingLevel_(0),
    layoutNestingLevel_(0),
    layoutMinSize_(0),
    position_(IntVector2::ZERO),
    size_(IntVector2::ZERO),
    minSize_(IntVector2::ZERO),
    maxSize_(M_MAX_INT, M_MAX_INT),
    childOffset_(IntVector2::ZERO),
    horizontalAlignment_(HA_LEFT),
    verticalAlignment_(VA_TOP),
    opacity_(1.0f),
    positionDirty_(true),
    opacityDirty_(true),
    derivedColorDirty_(true),
    sortOrderDirty_(false),
    colorGradient_(false)
{
}

UIElement::~UIElement()
{
    // If child elements have outside references, detach them
    while (children_.Size())
    {
        const SharedPtr<UIElement>& element = children_.Back();
        if (element.Refs() > 1)
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
    
    REF_ACCESSOR_ATTRIBUTE(UIElement, VAR_STRING, "Name", GetName, SetName, String, String(), AM_FILE);
    REF_ACCESSOR_ATTRIBUTE(UIElement, VAR_INTVECTOR2, "Position", GetPosition, SetPosition, IntVector2, IntVector2::ZERO, AM_FILE);
    REF_ACCESSOR_ATTRIBUTE(UIElement, VAR_INTVECTOR2, "Size", GetSize, SetSize, IntVector2, IntVector2::ZERO, AM_FILE);
    REF_ACCESSOR_ATTRIBUTE(UIElement, VAR_INTVECTOR2, "Min Size", GetMinSize, SetMinSize, IntVector2, IntVector2::ZERO, AM_FILE);
    REF_ACCESSOR_ATTRIBUTE(UIElement, VAR_INTVECTOR2, "Max Size", GetMaxSize, SetMaxSize, IntVector2, IntVector2::ZERO, AM_FILE);
    ENUM_ACCESSOR_ATTRIBUTE(UIElement, "Horiz Alignment", GetHorizontalAlignment, SetHorizontalAlignment, HorizontalAlignment, horizontalAlignments, HA_LEFT, AM_FILE);
    ENUM_ACCESSOR_ATTRIBUTE(UIElement, "Vert Alignment", GetVerticalAlignment, SetVerticalAlignment, VerticalAlignment, verticalAlignments, VA_TOP, AM_FILE);
    REF_ACCESSOR_ATTRIBUTE(UIElement, VAR_INTRECT, "Clip Border", GetClipBorder, SetClipBorder, IntRect, IntRect::ZERO, AM_FILE);
    ACCESSOR_ATTRIBUTE(UIElement, VAR_INT, "Priority", GetPriority, SetPriority, int, 0, AM_FILE);
    ACCESSOR_ATTRIBUTE(UIElement, VAR_FLOAT, "Opacity", GetOpacity, SetOpacity, float, 1.0f, AM_FILE);
    ATTRIBUTE(UIElement, VAR_COLOR, "Top Left Color", color_[0], Color::WHITE, AM_FILE);
    ATTRIBUTE(UIElement, VAR_COLOR, "Top Right Color", color_[1], Color::WHITE, AM_FILE);
    ATTRIBUTE(UIElement, VAR_COLOR, "Bottom Left Color", color_[2], Color::WHITE, AM_FILE);
    ATTRIBUTE(UIElement, VAR_COLOR, "Bottom Right Color", color_[3], Color::WHITE, AM_FILE);
    ACCESSOR_ATTRIBUTE(UIElement, VAR_BOOL, "Is Active", IsActive, SetActive, bool, false, AM_FILE);
    ACCESSOR_ATTRIBUTE(UIElement, VAR_BOOL, "Is Selected", IsSelected, SetSelected, bool, false, AM_FILE);
    ACCESSOR_ATTRIBUTE(UIElement, VAR_BOOL, "Is Visible", IsVisible, SetVisible, bool, true, AM_FILE);
    ACCESSOR_ATTRIBUTE(UIElement, VAR_BOOL, "Bring To Front", GetBringToFront, SetBringToFront, bool, false, AM_FILE);
    ACCESSOR_ATTRIBUTE(UIElement, VAR_BOOL, "Bring To Back", GetBringToBack, SetBringToBack, bool, true, AM_FILE);
    ACCESSOR_ATTRIBUTE(UIElement, VAR_BOOL, "Clip Children", GetClipChildren, SetClipChildren, bool, false, AM_FILE);
    ENUM_ACCESSOR_ATTRIBUTE(UIElement, "Focus Mode", GetFocusMode, SetFocusMode, FocusMode, focusModes, FM_NOTFOCUSABLE, AM_FILE);
    ENUM_ACCESSOR_ATTRIBUTE(UIElement, "Drag And Drop Mode", GetDragDropMode, SetDragDropMode, unsigned, dragDropModes, DD_DISABLED, AM_FILE);
    ENUM_ACCESSOR_ATTRIBUTE(UIElement, "Layout Mode", GetLayoutMode, SetLayoutMode, LayoutMode, layoutModes, LM_FREE, AM_FILE);
    ACCESSOR_ATTRIBUTE(UIElement, VAR_INT, "Layout Spacing", GetLayoutSpacing, SetLayoutSpacing, int, 0, AM_FILE);
    REF_ACCESSOR_ATTRIBUTE(UIElement, VAR_INTRECT, "Layout Border", GetLayoutBorder, SetLayoutBorder, IntRect, IntRect::ZERO, AM_FILE);
    ATTRIBUTE(UIElement, VAR_VARIANTMAP, "Variables", vars_, VariantMap(), AM_FILE);
}

void UIElement::ApplyAttributes()
{
    colorGradient_ = false;
    derivedColorDirty_ = true;
    
    for (unsigned i = 1; i < MAX_UIELEMENT_CORNERS; ++i)
    {
        if (color_[i] != color_[0])
            colorGradient_ = true;
    }
}

bool UIElement::LoadXML(const XMLElement& source)
{
    return LoadXML(source, 0);
}

bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile)
{
    // Apply the style first, but only for non-internal elements
    if (!internal_ && styleFile)
    {
        // Use style override if defined, otherwise type name
        String styleName = source.GetAttribute("style");
        if (styleName.Empty())
            styleName = GetTypeName();
        
        SetStyle(styleFile, styleName);
    }
    
    // Then load rest of the attributes from the source
    if (!Serializable::LoadXML(source))
        return false;
    
    unsigned nextInternalChild = 0;
    
    // Load child elements. Internal elements are not to be created as they already exist
    XMLElement childElem = source.GetChild("element");
    while (childElem)
    {
        bool internalElem = childElem.GetBool("internal");
        String typeName = childElem.GetAttribute("type");
        if (typeName.Empty())
            typeName = "UIElement";
        UIElement* child = 0;
        
        if (!internalElem)
            child = CreateChild(ShortStringHash(typeName));
        else
        {
            for (unsigned i = nextInternalChild; i < children_.Size(); ++i)
            {
                if (children_[i]->IsInternal() && children_[i]->GetTypeName() == typeName)
                {
                    child = children_[i];
                    nextInternalChild = i + 1;
                    break;
                }
            }
            
            if (!child)
                LOGWARNING("Could not find matching internal child element of type " + typeName + " in " + GetTypeName());
        }
        
        if (child)
        {
            if (!child->LoadXML(childElem, styleFile))
                return false;
        }
        
        childElem = childElem.GetNext("element");
    }
    
    ApplyAttributes();
    
    return true;
}

bool UIElement::SaveXML(XMLElement& dest)
{
    // Write type and internal flag
    if (!dest.SetString("type", GetTypeName()))
        return false;
    if (internal_)
    {
        if (!dest.SetBool("internal", internal_))
            return false;
    }
    
    // Write attributes
    if (!Serializable::SaveXML(dest))
        return false;
    
    // Write child elements
    for (unsigned i = 0; i < children_.Size(); ++i)
    {
        UIElement* element = children_[i];
        XMLElement childElem = dest.CreateChild("element");
        if (!element->SaveXML(childElem))
            return false;
    }
    
    return true;
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

void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
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

void UIElement::OnChar(unsigned c, int buttons, int qualifiers)
{
}

void UIElement::OnResize()
{
}

bool UIElement::LoadXML(Deserializer& source)
{
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    if (!xml->Load(source))
        return false;
    
    return LoadXML(xml->GetRoot());
}

bool UIElement::SaveXML(Serializer& dest)
{
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    XMLElement rootElem = xml->CreateRoot("element");
    if (!SaveXML(rootElem))
        return false;
    
    return xml->Save(dest);
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
        if (i != corner && color_[i] != color_[corner])
            colorGradient_ = true;
    }
}

void UIElement::SetPriority(int priority)
{
    priority_ = priority;
    if (parent_)
        parent_->sortOrderDirty_ = true;
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

void UIElement::SetSortChildren(bool enable)
{
    if (!sortChildren_ && enable)
        sortOrderDirty_ = true;
    
    sortChildren_ = enable;
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
    
    UI* ui = GetSubsystem<UI>();
    if (!ui)
        return;
    
    if (enable)
    {
        if (ui->GetFocusElement() != this)
            ui->SetFocusElement(this);
    }
    else
    {
        if (ui->GetFocusElement() == this)
            ui->SetFocusElement(0);
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
    
    XMLElement rootElem = file->GetRoot();
    XMLElement childElem = rootElem.GetChild("element");
    while (childElem)
    {
        if (typeName == childElem.GetAttribute("type"))
        {
            SetStyle(childElem);
            return;
        }
        childElem = childElem.GetNext("element");
    }
}


void UIElement::SetStyle(const XMLElement& element)
{
    LoadXML(element);
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
    if (layoutMode_ == LM_FREE || layoutNestingLevel_)
        return;
    
    // Prevent further updates while this update happens
    DisableLayoutUpdate();
    
    PODVector<int> positions;
    PODVector<int> sizes;
    PODVector<int> minSizes;
    PODVector<int> maxSizes;
    
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
    UIElement* root = GetRoot();
    UIElement* ptr = this;
    while (ptr && ptr->GetParent() != root)
        ptr = ptr->GetParent();
    if (!ptr || !ptr->GetBringToFront())
        return;
    
    // Get the highest priority used by all other top level elements, assign that to the new front element
    // and decrease others' priority by one. However, take into account only active (enabled) elements
    // and those which have the BringToBack flag set
    int maxPriority = M_MIN_INT;
    const Vector<SharedPtr<UIElement> >& rootChildren = root->GetChildren();
    for (Vector<SharedPtr<UIElement> >::ConstIterator i = rootChildren.Begin(); i != rootChildren.End(); ++i)
    {
        UIElement* other = *i;
        if (other->IsActive() && other->bringToBack_ && other != ptr)
        {
            int priority = other->GetPriority();
            maxPriority = Max(priority, maxPriority);
            other->SetPriority(priority - 1);
        }
    }
    if (maxPriority != M_MIN_INT)
        ptr->SetPriority(maxPriority);
}

UIElement* UIElement::CreateChild(ShortStringHash type, const String& name)
{
    // Check that creation succeeds and that the object in fact is a UI element
    SharedPtr<UIElement> newElement = DynamicCast<UIElement>(context_->CreateObject(type));
    if (!newElement)
    {
        LOGERROR("Could not create unknown UI element type " + type.ToString());
        return 0;
    }
    
    newElement->SetName(name);
    
    AddChild(newElement);
    return newElement;
}

void UIElement::AddChild(UIElement* element)
{
    InsertChild(children_.Size(), element);
}

void UIElement::InsertChild(unsigned index, UIElement* element)
{
    // Check for illegal or redundant parent assignment
    if (!element || element == this || element->parent_ == this)
        return;
     // Check for possible cyclic parent assignment
    UIElement* parent = parent_;
    while (parent)
    {
        if (parent == element)
            return;
        parent = parent->parent_;
    }
    
    // Add first, then remove from old parent, to ensure the element does not get deleted
    if (index >= children_.Size())
        children_.Push(SharedPtr<UIElement>(element));
    else
        children_.Insert(children_.Begin() + index, SharedPtr<UIElement>(element));
    
    if (element->parent_)
        element->parent_->RemoveChild(element);
    
    if (sortChildren_)
        sortOrderDirty_ = true;
    
    element->parent_ = this;
    element->MarkDirty();
    UpdateLayout();
}

void UIElement::RemoveChild(UIElement* element)
{
    for (Vector<SharedPtr<UIElement> >::Iterator i = children_.Begin(); i != children_.End(); ++i)
    {
        if (*i == element)
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

void UIElement::SetVar(ShortStringHash key, const Variant& value)
{
    vars_[key] = value;
}

void UIElement::SetInternal(bool enable)
{
    internal_ = enable;
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

bool UIElement::HasFocus() const
{
    UI* ui = GetSubsystem<UI>();
    if (!ui)
        return false;
    else
        return ui->GetFocusElement() == this;
}

void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive) const
{
    dest.Clear();
    
    if (!recursive)
    {
        for (Vector<SharedPtr<UIElement> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
            dest.Push(*i);
    }
    else
        GetChildrenRecursive(dest);
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

UIElement* UIElement::GetRoot() const
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

const Variant& UIElement::GetVar(ShortStringHash key) const
{
    VariantMap::ConstIterator i = vars_.Find(key);
    if (i != vars_.End())
        return i->second_;
    else
        return Variant::EMPTY;
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
    return position.x_ >= 0 && position.y_ >= 0 && position.x_ < size_.x_ && position.y_ < size_.y_;
}

bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen)
{
    // If child elements are clipped, no need to expand the rect
    if (clipChildren_)
        return IsInside(position, isScreen);
    
    if (!isScreen)
        position = ElementToScreen(position);
    
    IntRect combined = GetCombinedScreenRect();
    return position.x_ >= combined.left_ && position.y_ >= combined.top_ && position.x_ < combined.right_ &&
        position.y_ < combined.bottom_;
}

IntRect UIElement::GetCombinedScreenRect()
{
    IntVector2 screenPosition(GetScreenPosition());
    IntRect combined(screenPosition.x_, screenPosition.y_, screenPosition.x_ + size_.x_, screenPosition.y_ + size_.y_);
    
    if (!clipChildren_)
    {
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
    }
    
    return combined;
}

void UIElement::SortChildren()
{
    if (sortChildren_ && sortOrderDirty_)
    {
        Sort(children_.Begin(), children_.End(), CompareUIElements);
        sortOrderDirty_ = false;
    }
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

void UIElement::SetTempVisible(bool enable)
{
    visible_ = enable;
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

void UIElement::GetChildrenRecursive(PODVector<UIElement*>& dest) const
{
    for (Vector<SharedPtr<UIElement> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
    {
        UIElement* element = *i;
        dest.Push(element);
        if (!element->children_.Empty())
            element->GetChildrenRecursive(dest);
    }
}

int UIElement::CalculateLayoutParentSize(const PODVector<int>& sizes, int begin, int end, int spacing)
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

void UIElement::CalculateLayout(PODVector<int>& positions, PODVector<int>& sizes, const PODVector<int>& minSizes,
        const PODVector<int>& maxSizes, int targetSize, int begin, int end, int spacing)
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
        PODVector<unsigned> resizable;
        for (int i = 0; i < numChildren; ++i)
        {
            if (error < 0 && sizes[i] > minSizes[i])
                resizable.Push(i);
            else if (error > 0 && sizes[i] < maxSizes[i])
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
            unsigned index = resizable[i];
            int targetSize = sizes[index] + errorPerChild;
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
            
            sizes[index] = Clamp(targetSize, minSizes[index], maxSizes[index]);
        }
    }
    
    // Calculate final positions and store the minimum child element size
    layoutMinSize_ = M_MAX_INT;
    int position = begin;
    for (int i = 0; i < numChildren; ++i)
    {
        positions[i] = position;
        position += sizes[i];
        position += spacing;
        if (sizes[i] < layoutMinSize_)
            layoutMinSize_ = sizes[i];
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


}
