//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Button.h"
#include "CheckBox.h"
#include "CoreEvents.h"
#include "Engine.h"
#include "Input.h"
#include "LineEdit.h"
#include "Text.h"
#include "UI.h"
#include "UIEvents.h"
#include "Window.h"

#include "HelloGUI.h"

#include "DebugNew.h"

DEFINE_APPLICATION_MAIN(HelloGUI)

HelloGUI::HelloGUI(Context* context) :
    Sample(context),
    uiRoot_(GetSubsystem<UI>()->GetRoot()),
    window_()
{
}

void HelloGUI::Start()
{
    // Execute base class startup
    Sample::Start();

    // Enable OS cursor
    GetSubsystem<Input>()->SetMouseVisible(true);

    // Load XML file containing default UI style sheet
    SharedPtr<ResourceCache> cache(GetSubsystem<ResourceCache>());
    SharedPtr<XMLFile> style(cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));

    // Set the loaded style as default style
    this->uiRoot_->SetDefaultStyle(style);

    // Initialize Window
    this->InitWindow();

    // Create and add some controls to the Window
    this->InitControls();

    SubscribeToEvents();
}

void HelloGUI::InitControls()
{
    // Create a CheckBox
    CheckBox* checkBox = new CheckBox(context_);
    checkBox->SetName("CheckBox");

    // Create a Button
    Button* button = new Button(context_);
    button->SetName("Button");
    button->SetMinHeight(24);

    // Create a LineEdit
    LineEdit* lineEdit = new LineEdit(context_);
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
    this->window_ = SharedPtr<Window>(new Window(context_));
    this->uiRoot_->AddChild(window_);

    // Set Window size and layout settings
    window_->SetMinSize(384, 192);
    window_->SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    window_->SetAlignment(HA_CENTER, VA_CENTER);
    window_->SetName("Window");

    // Create Window 'titlebar' container
    UIElement* titleBar = new UIElement(context_);
    titleBar->SetMinSize(0, 24);
    titleBar->SetVerticalAlignment(VA_TOP);
    titleBar->SetLayoutMode(LM_HORIZONTAL);

    // Create the Window title Text
    Text* windowTitle = new Text(context_);
    windowTitle->SetName("WindowTitle");
    windowTitle->SetText("Hello GUI!");

    // Create the Window's close button
    Button* buttonClose = new Button(context_);
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

    // Lastly, subscribe to buttonClose release (following a 'press') events
    SubscribeToEvent(buttonClose, E_RELEASED, HANDLER(HelloGUI, HandleClosePressed));
}

void HelloGUI::SubscribeToEvents()
{
    // Subscribe handler; invoked whenever a mouse click event is dispatched
    SubscribeToEvent(E_UIMOUSECLICK, HANDLER(HelloGUI, HandleControlClicked));
}

void HelloGUI::HandleClosePressed(StringHash eventType, VariantMap& eventData)
{
    GetSubsystem<Engine>()->Exit();
}

void HelloGUI::HandleControlClicked(StringHash eventType, VariantMap& eventData)
{
    // Get the Text control acting as the Window's title
    SharedPtr<Text> windowTitle((Text*)window_->GetChild(String("WindowTitle"), true));

    // Get control that was clicked
    UIElement* clicked = static_cast<UIElement*>(eventData[UIMouseClick::P_ELEMENT].GetPtr());

    String name = "...?";
    if (clicked)
    {
        // Get the name of the control that was clicked
        name = clicked->GetName();
    }

    // Update the Window's title text
    windowTitle->SetText(String("Hello " + name + "!"));
}
