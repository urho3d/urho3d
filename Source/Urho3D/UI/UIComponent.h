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

#pragma once

#include "../Scene/Serializable.h"

namespace Urho3D
{

class UIElement;

/// Base class for UI components.
class URHO3D_API UIComponent : public Serializable
{
    URHO3D_OBJECT(UIComponent, Serializable);

    friend class UIElement;

public:
    /// Construct.
    UIComponent(Context* context);
    /// Destruct.
    virtual ~UIComponent();

    /// Handle enabled/disabled state change.
    virtual void OnSetEnabled() { }

    /// Save as XML data. Return true if successful.
    virtual bool SaveXML(XMLElement& dest) const;

    /// Set enabled/disabled state.
    void SetEnabled(bool enable);
    /// Remove from the element. If no other shared pointer references exist, causes immediate deletion.
    void Remove();

    /// Return element.
    UIElement* GetElement() const { return element_; }

    /// Return whether is enabled.
    bool IsEnabled() const { return enabled_; }

    /// Return whether is effectively enabled (element is also enabled.)
    bool IsEnabledEffective() const;
    /// Return component in the same element by type. If there are several, returns the first.
    UIComponent* GetComponent(StringHash type) const;
    /// Return components in the same element by type.
    void GetComponents(PODVector<UIComponent*>& dest, StringHash type) const;
    /// Template version of returning a component in the same element by type.
    template <class T> T* GetComponent() const;
    /// Template version of returning components in the same element by type.
    template <class T> void GetComponents(PODVector<T*>& dest) const;

protected:
    /// Handle element being assigned at creation.
    virtual void OnElementSet(UIElement* element);
    /// Handle element transform dirtied.
    virtual void OnMarkedDirty(UIElement* element);
    /// Handle element enabled status changing.
    virtual void OnElementSetEnabled(UIElement* element);
    /// Set element. Called by UIElement when creating the component.
    void SetElement(UIElement* element);

    /// Element.
    UIElement* element_;
    /// Enabled flag.
    bool enabled_;
};

template <class T> T* UIComponent::GetComponent() const { return static_cast<T*>(GetComponent(T::GetTypeStatic())); }

template <class T> void UIComponent::GetComponents(PODVector<T*>& dest) const
{
    GetComponents(reinterpret_cast<PODVector<UIComponent*>&>(dest), T::GetTypeStatic());
}

}
