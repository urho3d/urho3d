// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
    /// @nobind
    static void RegisterObject(Context* context);

    /// Return UIElement.
    /// @property
    UIElement* GetRoot() const;
    /// Return material which will be used for rendering UI texture.
    /// @property
    Material* GetMaterial() const;
    /// Return texture which will be used for rendering UI to.
    /// @property
    Texture2D* GetTexture() const;
    /// Set index of viewport to be used for screen coordinate translation.
    void SetViewportIndex(unsigned index);

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
