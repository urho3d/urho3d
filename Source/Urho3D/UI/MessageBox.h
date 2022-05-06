// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

class Button;
class Text;
class UIElement;
class XMLFile;

/// Message box dialog. Manages its lifetime automatically, so the application does not need to hold a reference to it, and shouldn't attempt to destroy it manually.
class URHO3D_API MessageBox : public Object
{
    URHO3D_OBJECT(MessageBox, Object);

public:
    /// Construct. If layout file is not given, use the default message box layout. If style file is not given, use the default style file from root UI element.
    explicit MessageBox(Context* context, const String& messageString = String::EMPTY, const String& titleString = String::EMPTY,
        XMLFile* layoutFile = nullptr, XMLFile* styleFile = nullptr);
    /// Destruct.
    ~MessageBox() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Set title text. No-ops if there is no title text element.
    /// @property
    void SetTitle(const String& text);
    /// Set message text. No-ops if there is no message text element.
    /// @property
    void SetMessage(const String& text);

    /// Return title text. Return empty string if there is no title text element.
    /// @property
    const String& GetTitle() const;
    /// Return message text. Return empty string if there is no message text element.
    /// @property
    const String& GetMessage() const;

    /// Return dialog window.
    /// @property
    UIElement* GetWindow() const { return window_; }

private:
    /// Handle events that dismiss the message box.
    void HandleMessageAcknowledged(StringHash eventType, VariantMap& eventData);

    /// UI element containing the whole UI layout. Typically it is a Window element type.
    UIElement* window_;
    /// Title text element.
    Text* titleText_;
    /// Message text element.
    Text* messageText_;
    /// OK button element.
    Button* okButton_;
};

}
