//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../UI/UIComponent.h"
#include "../UI/UIElement.h"

#include "../DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:6293)
#endif

namespace Urho3D
{

UIComponent::UIComponent(Context* context) :
    Serializable(context),
    element_(0),
    enabled_(true)
{
}

UIComponent::~UIComponent()
{
}

bool UIComponent::SaveXML(XMLElement& dest) const
{
    // Write type
    if (!dest.SetString("type", GetTypeName()))
        return false;

    // Write attributes
    return Serializable::SaveXML(dest);
}

void UIComponent::SetEnabled(bool enable)
{
    if (enable != enabled_)
    {
        enabled_ = enable;
        OnSetEnabled();
    }
}

void UIComponent::Remove()
{
    if (element_)
        element_->RemoveComponent(this);
}

void UIComponent::OnElementSet(UIElement* element)
{
}

void UIComponent::OnMarkedDirty(UIElement* element)
{
}

void UIComponent::OnElementSetEnabled(UIElement* element)
{
}

void UIComponent::SetElement(UIElement* element)
{
    element_ = element;
    OnElementSet(element_);
}

UIComponent* UIComponent::GetComponent(StringHash type) const
{
    return element_ ? element_->GetComponent(type) : 0;
}

bool UIComponent::IsEnabledEffective() const
{
    return enabled_ && element_ && element_->IsEnabled();
}

void UIComponent::GetComponents(PODVector<UIComponent*>& dest, StringHash type) const
{
    if (element_)
        element_->GetComponents(dest, type);
    else
        dest.Clear();
}

}
