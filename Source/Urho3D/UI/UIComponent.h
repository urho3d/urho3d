//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Scene/Component.h"
#include "../UI/UIElement.h"

namespace Urho3D
{

class Material;
class Texture2D;
class StaticModel;
class Viewport;
class UIElement;
class UIBatch;
class VertexBuffer;
class UIElement3D;

class URHO3D_API UIComponent : public Component
{
    URHO3D_OBJECT(UIComponent, Component);

public:
    /// Construct.
    explicit UIComponent(Context* context);
    /// Destruct.
    ~UIComponent() override;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Return UIElement.
    UIElement* GetRoot() const;
    /// Return material which will be used for rendering UI texture.
    Material* GetMaterial() const;
    /// Return texture which will be used for rendering UI to.
    Texture2D* GetTexture() const;
    /// Set index of viewport to be used for screen coordinate translation.
    void SetViewportIndex(unsigned int index);

protected:
    /// Handle component being added to Node or removed from it.
    void OnNodeSet(Node* node) override;
    /// Handle resizing of element. Setting size of element will automatically resize texture. UIElement size matches size of texture.
    void OnElementResized(StringHash eventType, VariantMap& args);

    /// Material that is set to the model.
    SharedPtr<Material> material_;
    /// Texture that UIElement will be rendered into.
    SharedPtr<Texture2D> texture_;
    /// Model created by this component. If node already has StaticModel then this will be null.
    SharedPtr<StaticModel> model_;
    /// UIElement to be rendered into texture. It also handles screen to UI coordinate translation.
    SharedPtr<UIElement3D> rootElement_;
    /// Viewport index to be set when component is added to a node.
    unsigned viewportIndex_;
};

}
