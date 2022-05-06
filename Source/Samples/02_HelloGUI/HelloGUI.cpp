// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/GraphicsAPI/Texture2D.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/CheckBox.h>
#include <Urho3D/UI/LineEdit.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/ToolTip.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/UI/Window.h>

#include "HelloGUI.h"

#include <Urho3D/DebugNew.h>

URHO3D_DEFINE_APPLICATION_MAIN(HelloGUI)

HelloGUI::HelloGUI(Context* context) :
    Sample(context),
    uiRoot_(GetSubsystem<UI>()->GetRoot()),
    dragBeginPosition_(IntVector2::ZERO)
{
}

void HelloGUI::Start()
{
    // Execute base class startup
    Sample::Start();

    // Enable OS cursor
    GetSubsystem<Input>()->SetMouseVisible(true);

    // Load XML file containing default UI style sheet
    auto* cache = GetSubsystem<ResourceCache>();
    auto* style = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");

    // Set the loaded style as default style
    uiRoot_->SetDefaultStyle(style);

    // Initialize Window
    InitWindow();

    // Create and add some controls to the Window
    InitControls();

    // Create a draggable Fish
    CreateDraggableFish();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);
}

void HelloGUI::InitControls()
{
    // Create a CheckBox
    auto* checkBox = new CheckBox(context_);
    checkBox->SetName("CheckBox");

    // Create a Button
    auto* button = new Button(context_);
    button->SetName("Button");
    button->SetMinHeight(24);

    // Create a LineEdit
    auto* lineEdit = new LineEdit(context_);
    lineEdit->SetName("LineEdit");
    lineEdit->SetMinHeight(24);

    // Add controls to Window
    window_->AddChild(checkBox);
    window_->AddChild(button);
    window_->AddChild(lineEdit);

    // Apply previously set default style
    checkBox->SetStyleAuto();
    button->SetStyleAuto();
    lineEdit->SetStyleAuto();
}

void HelloGUI::InitWindow()
{
    // Create the Window and add it to the UI's root node
    window_ = new Window(context_);
    uiRoot_->AddChild(window_);

    // Set Window size and layout settings
    window_->SetMinWidth(384);
    window_->SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    window_->SetAlignment(HA_CENTER, VA_CENTER);
    window_->SetName("Window");

    // Create Window 'titlebar' container
    auto* titleBar = new UIElement(context_);
    titleBar->SetMinSize(0, 24);
    titleBar->SetVerticalAlignment(VA_TOP);
    titleBar->SetLayoutMode(LM_HORIZONTAL);

    // Create the Window title Text
    auto* windowTitle = new Text(context_);
    windowTitle->SetName("WindowTitle");
    windowTitle->SetText("Hello GUI!");

    // Create the Window's close button
    auto* buttonClose = new Button(context_);
    buttonClose->SetName("CloseButton");

    // Add the controls to the title bar
    titleBar->AddChild(windowTitle);
    titleBar->AddChild(buttonClose);

    // Add the title bar to the Window
    window_->AddChild(titleBar);

    // Apply styles
    window_->SetStyleAuto();
    windowTitle->SetStyleAuto();
    buttonClose->SetStyle("CloseButton");

    // Subscribe to buttonClose release (following a 'press') events
    SubscribeToEvent(buttonClose, E_RELEASED, URHO3D_HANDLER(HelloGUI, HandleClosePressed));

    // Subscribe also to all UI mouse clicks just to see where we have clicked
    SubscribeToEvent(E_UIMOUSECLICK, URHO3D_HANDLER(HelloGUI, HandleControlClicked));
}

void HelloGUI::CreateDraggableFish()
{
    auto* cache = GetSubsystem<ResourceCache>();
    auto* graphics = GetSubsystem<Graphics>();

    // Create a draggable Fish button
    auto* draggableFish = new Button(context_);
    draggableFish->SetTexture(cache->GetResource<Texture2D>("Textures/UrhoDecal.dds")); // Set texture
    draggableFish->SetBlendMode(BLEND_ADD);
    draggableFish->SetSize(128, 128);
    draggableFish->SetPosition((graphics->GetWidth() - draggableFish->GetWidth()) / 2, 200);
    draggableFish->SetName("Fish");
    uiRoot_->AddChild(draggableFish);

    // Add a tooltip to Fish button
    auto* toolTip = new ToolTip(context_);
    draggableFish->AddChild(toolTip);
    toolTip->SetPosition(IntVector2(draggableFish->GetWidth() + 5, draggableFish->GetWidth() / 2)); // slightly offset from close button
    auto* textHolder = new BorderImage(context_);
    toolTip->AddChild(textHolder);
    textHolder->SetStyle("ToolTipBorderImage");
    auto* toolTipText = new Text(context_);
    textHolder->AddChild(toolTipText);
    toolTipText->SetStyle("ToolTipText");
    toolTipText->SetText("Please drag me!");

    // Subscribe draggableFish to Drag Events (in order to make it draggable)
    // See "Event list" in documentation's Main Page for reference on available Events and their eventData
    SubscribeToEvent(draggableFish, E_DRAGBEGIN, URHO3D_HANDLER(HelloGUI, HandleDragBegin));
    SubscribeToEvent(draggableFish, E_DRAGMOVE, URHO3D_HANDLER(HelloGUI, HandleDragMove));
    SubscribeToEvent(draggableFish, E_DRAGEND, URHO3D_HANDLER(HelloGUI, HandleDragEnd));
}

void HelloGUI::HandleDragBegin(StringHash eventType, VariantMap& eventData)
{
    // Get UIElement relative position where input (touch or click) occurred (top-left = IntVector2(0,0))
    dragBeginPosition_ = IntVector2(eventData["ElementX"].GetInt(), eventData["ElementY"].GetInt());
}

void HelloGUI::HandleDragMove(StringHash eventType, VariantMap& eventData)
{
    IntVector2 dragCurrentPosition = IntVector2(eventData["X"].GetInt(), eventData["Y"].GetInt());
    UIElement* draggedElement = static_cast<UIElement*>(eventData["Element"].GetPtr());
    draggedElement->SetPosition(dragCurrentPosition - dragBeginPosition_);
}

void HelloGUI::HandleDragEnd(StringHash eventType, VariantMap& eventData) // For reference (not used here)
{
}

void HelloGUI::HandleClosePressed(StringHash eventType, VariantMap& eventData)
{
    if (GetPlatform() != "Web")
        engine_->Exit();
}

void HelloGUI::HandleControlClicked(StringHash eventType, VariantMap& eventData)
{
    // Get the Text control acting as the Window's title
    auto* windowTitle = window_->GetChildStaticCast<Text>("WindowTitle", true);

    // Get control that was clicked
    auto* clicked = static_cast<UIElement*>(eventData[UIMouseClick::P_ELEMENT].GetPtr());

    String name = "...?";
    if (clicked)
    {
        // Get the name of the control that was clicked
        name = clicked->GetName();
    }

    // Update the Window's title text
    windowTitle->SetText("Hello " + name + "!");
}
