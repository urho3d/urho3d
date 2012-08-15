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
#include "BorderImage.h"
#include "InputEvents.h"
#include "ScrollBar.h"
#include "ScrollView.h"
#include "UIEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

static const float STEP_FACTOR = 300.0f;

OBJECTTYPESTATIC(ScrollView);

ScrollView::ScrollView(Context* context) :
    UIElement(context),
    viewPosition_(IntVector2::ZERO),
    viewSize_(IntVector2::ZERO),
    pageStep_(1.0f)
{
    clipChildren_ = true;
    active_ = true;
    focusMode_ = FM_FOCUSABLE_DEFOCUSABLE;
    
    horizontalScrollBar_ = new ScrollBar(context_);
    horizontalScrollBar_->SetAlignment(HA_LEFT, VA_BOTTOM);
    horizontalScrollBar_->SetOrientation(O_HORIZONTAL);
    verticalScrollBar_ = new ScrollBar(context_);
    verticalScrollBar_->SetAlignment(HA_RIGHT, VA_TOP);
    verticalScrollBar_->SetOrientation(O_VERTICAL);
    scrollPanel_ = new BorderImage(context_);
    scrollPanel_->SetActive(true);
    scrollPanel_->SetClipChildren(true);
    
    AddChild(horizontalScrollBar_);
    AddChild(verticalScrollBar_);
    AddChild(scrollPanel_);
    
    SubscribeToEvent(horizontalScrollBar_, E_SCROLLBARCHANGED, HANDLER(ScrollView, HandleScrollBarChanged));
    SubscribeToEvent(horizontalScrollBar_, E_VISIBLECHANGED, HANDLER(ScrollView, HandleScrollBarVisibleChanged));
    SubscribeToEvent(verticalScrollBar_, E_SCROLLBARCHANGED, HANDLER(ScrollView, HandleScrollBarChanged));
    SubscribeToEvent(verticalScrollBar_, E_VISIBLECHANGED, HANDLER(ScrollView, HandleScrollBarVisibleChanged));
}

ScrollView::~ScrollView()
{
}

void ScrollView::RegisterObject(Context* context)
{
    context->RegisterFactory<ScrollView>();
}

void ScrollView::SetStyle(const XMLElement& element)
{
    UIElement::SetStyle(element);
    
    if (element.HasChild("viewposition"))
        SetViewPosition(element.GetChild("viewposition").GetIntVector2("value"));
    if (element.HasChild("scrollstep"))
        SetScrollStep(element.GetChild("scrollstep").GetFloat("value"));
    if (element.HasChild("pagestep"))
        SetScrollStep(element.GetChild("pagestep").GetFloat("value"));
    
    XMLElement horizElem = element.GetChild("horizontalscrollbar");
    if (horizElem)
        horizontalScrollBar_->SetStyle(horizElem);
    XMLElement vertElem = element.GetChild("verticalscrollbar");
    if (vertElem)
        verticalScrollBar_->SetStyle(vertElem);
    XMLElement panelElem = element.GetChild("scrollpanel");
    if (panelElem)
        scrollPanel_->SetStyle(panelElem);
    
    UIElement* root = GetRoot();
    if (root && element.HasChild("contentelement"))
        SetContentElement(root->GetChild(element.GetChild("contentelement").GetAttribute("name"), true));
    
    // Set the scrollbar orientations again and perform size update now that the style is known
    horizontalScrollBar_->SetOrientation(O_HORIZONTAL);
    verticalScrollBar_->SetOrientation(O_VERTICAL);
    OnResize();
}

void ScrollView::OnWheel(int delta, int buttons, int qualifiers)
{
    if (delta > 0)
        verticalScrollBar_->StepBack();
    if (delta < 0)
        verticalScrollBar_->StepForward();
}

void ScrollView::OnKey(int key, int buttons, int qualifiers)
{
    switch (key)
    {
    case KEY_LEFT:
        if (horizontalScrollBar_->IsVisible())
        {
            if (qualifiers & QUAL_CTRL)
                horizontalScrollBar_->SetValue(0.0f);
            else
                horizontalScrollBar_->StepBack();
        }
        break;
        
    case KEY_RIGHT:
        if (horizontalScrollBar_->IsVisible())
        {
            if (qualifiers & QUAL_CTRL)
                horizontalScrollBar_->SetValue(horizontalScrollBar_->GetRange());
            else
                horizontalScrollBar_->StepForward();
        }
        break;
        
    case KEY_UP:
        if (verticalScrollBar_->IsVisible())
        {
            if (qualifiers & QUAL_CTRL)
                verticalScrollBar_->SetValue(0.0f);
            else
                verticalScrollBar_->StepBack();
        }
        break;
        
    case KEY_DOWN:
        if (verticalScrollBar_->IsVisible())
        {
            if (qualifiers & QUAL_CTRL)
                verticalScrollBar_->SetValue(verticalScrollBar_->GetRange());
            else
                verticalScrollBar_->StepForward();
        }
        break;
        
    case KEY_PAGEUP:
        if (verticalScrollBar_->IsVisible())
            verticalScrollBar_->ChangeValue(-pageStep_);
        break;
        
    case KEY_PAGEDOWN:
        if (verticalScrollBar_->IsVisible())
            verticalScrollBar_->ChangeValue(pageStep_);
        break;
    
    case KEY_HOME:
        if (verticalScrollBar_->IsVisible())
            verticalScrollBar_->SetValue(0.0f);
        break;
    
    case KEY_END:
        if (verticalScrollBar_->IsVisible())
            verticalScrollBar_->SetValue(verticalScrollBar_->GetRange());
        break;
    }
}

void ScrollView::OnResize()
{
    IntVector2 panelSize = GetSize();
    if (verticalScrollBar_->IsVisible())
        panelSize.x_ -= verticalScrollBar_->GetWidth();
    if (horizontalScrollBar_->IsVisible())
        panelSize.y_ -= horizontalScrollBar_->GetHeight();
    
    scrollPanel_->SetSize(panelSize);
    horizontalScrollBar_->SetWidth(scrollPanel_->GetWidth());
    verticalScrollBar_->SetHeight(scrollPanel_->GetHeight());
    
    UpdateViewSize();
}

void ScrollView::SetContentElement(UIElement* element)
{
    if (element == contentElement_)
        return;
    
    if (contentElement_)
    {
        scrollPanel_->RemoveChild(contentElement_);
        UnsubscribeFromEvent(contentElement_, E_RESIZED);
    }
    contentElement_ = element;
    if (contentElement_)
    {
        scrollPanel_->AddChild(contentElement_);
        SubscribeToEvent(contentElement_, E_RESIZED, HANDLER(ScrollView, HandleElementResized));
    }
    
    UpdateViewSize();
}

void ScrollView::SetViewPosition(const IntVector2& position)
{
    UpdateView(position);
    UpdateScrollBars();
}

void ScrollView::SetViewPosition(int x, int y)
{
    SetViewPosition(IntVector2(x, y));
}

void ScrollView::SetScrollBarsVisible(bool horizontal, bool vertical)
{
    horizontalScrollBar_->SetVisible(horizontal);
    verticalScrollBar_->SetVisible(vertical);
}

void ScrollView::SetScrollStep(float step)
{
    horizontalScrollBar_->SetScrollStep(step);
    verticalScrollBar_->SetScrollStep(step);
}

void ScrollView::SetPageStep(float step)
{
    pageStep_ = Max(step, 0.0f);
}

float ScrollView::GetScrollStep() const
{
    return horizontalScrollBar_->GetScrollStep();
}

void ScrollView::UpdateViewSize()
{
    IntVector2 size(IntVector2::ZERO);
    if (contentElement_)
        size = contentElement_->GetSize();
    
    viewSize_.x_ = Max(size.x_, scrollPanel_->GetWidth());
    viewSize_.y_ = Max(size.y_, scrollPanel_->GetHeight());
    UpdateView(viewPosition_);
    UpdateScrollBars();
}

void ScrollView::UpdateScrollBars()
{
    ignoreEvents_ = true;
    
    const IntVector2& size = scrollPanel_->GetSize();
    
    if (horizontalScrollBar_ && size.x_ > 0 && viewSize_.x_ > 0)
    {
        horizontalScrollBar_->SetRange((float)viewSize_.x_ / (float)size.x_ - 1.0f);
        horizontalScrollBar_->SetValue((float)viewPosition_.x_ / (float)size.x_);
        horizontalScrollBar_->SetStepFactor(STEP_FACTOR / (float)size.x_);
    }
    if (verticalScrollBar_ && size.y_ > 0 && viewSize_.y_ > 0)
    {
        verticalScrollBar_->SetRange((float)viewSize_.y_ / (float)size.y_ - 1.0f);
        verticalScrollBar_->SetValue((float)viewPosition_.y_ / (float)size.y_);
        verticalScrollBar_->SetStepFactor(STEP_FACTOR / (float)size.y_);
    }
    
    ignoreEvents_ = false;
}

void ScrollView::UpdateView(const IntVector2& position)
{
    IntVector2 oldPosition = viewPosition_;
    
    viewPosition_.x_ = Clamp(position.x_, 0, viewSize_.x_ - scrollPanel_->GetWidth());
    viewPosition_.y_ = Clamp(position.y_, 0, viewSize_.y_ - scrollPanel_->GetHeight());
    scrollPanel_->SetChildOffset(-viewPosition_);
    
    if (viewPosition_ != oldPosition)
    {
        using namespace ViewChanged;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        eventData[P_X] = viewPosition_.x_;
        eventData[P_Y] = viewPosition_.y_;
        SendEvent(E_VIEWCHANGED, eventData);
    }
}

void ScrollView::HandleScrollBarChanged(StringHash eventType, VariantMap& eventData)
{
    if (!ignoreEvents_)
    {
        UpdateView(IntVector2(
            (int)(horizontalScrollBar_->GetValue() * (float)scrollPanel_->GetWidth()),
            (int)(verticalScrollBar_->GetValue() * (float)scrollPanel_->GetHeight())
        ));
    }
}

void ScrollView::HandleScrollBarVisibleChanged(StringHash eventType, VariantMap& eventData)
{
    // Need to recalculate panel size when scrollbar visibility changes
    OnResize();
}

void ScrollView::HandleElementResized(StringHash eventType, VariantMap& eventData)
{
    UpdateViewSize();
}

}
