//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include <Urho3D/Urho3D.h>

#include <Urho3D/UI/Button.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UIEvents.h>

#include "UIDrag.h"

#include <Urho3D/DebugNew.h>

DEFINE_APPLICATION_MAIN(UIDrag)

UIDrag::UIDrag(Context* context) :
    Sample(context)
{
}

void UIDrag::Start()
{
    // Execute base class startup
    Sample::Start();

    // Set mouse visible
    String platform = GetPlatform();
    if (platform != "Android" && platform != "iOS")
        GetSubsystem<Input>()->SetMouseVisible(true);

    // Create the UI content
    CreateGUI();
    CreateInstructions();

    // Hook up to the frame update events
    SubscribeToEvents();
}

void UIDrag::CreateGUI()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    UIElement* root = ui->GetRoot();
    // Load the style sheet from xml
    root->SetDefaultStyle(cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));

    for (int i=0; i < 10; i++)
    {
        Button* b = new Button(context_);
        root->AddChild(b);
        // Reference a style from the style sheet loaded earlier:
        b->SetStyle("Button");
        b->SetSize(300, 100);
        b->SetPosition(IntVector2(50*i, 50*i));

        SubscribeToEvent(b, E_DRAGMOVE, HANDLER(UIDrag, HandleDragMove));
        SubscribeToEvent(b, E_DRAGBEGIN, HANDLER(UIDrag, HandleDragBegin));
        SubscribeToEvent(b, E_DRAGCANCEL, HANDLER(UIDrag, HandleDragCancel));
        SubscribeToEvent(b, E_DRAGEND, HANDLER(UIDrag, HandleDragEnd));

        {
            Text* t = new Text(context_);
            b->AddChild(t);
            t->SetStyle("Text");
            t->SetHorizontalAlignment(HA_CENTER);
            t->SetVerticalAlignment(VA_CENTER);
            t->SetName("Text");
        }

        {
            Text* t = new Text(context_);
            b->AddChild(t);
            t->SetStyle("Text");
            t->SetName("Event Touch");
            t->SetHorizontalAlignment(HA_CENTER);
            t->SetVerticalAlignment(VA_BOTTOM);
        }

        {
            Text* t = new Text(context_);
            b->AddChild(t);
            t->SetStyle("Text");
            t->SetName("Num Touch");
            t->SetHorizontalAlignment(HA_CENTER);
            t->SetVerticalAlignment(VA_TOP);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        Text* t = new Text(context_);
        root->AddChild(t);
        t->SetStyle("Text");
        t->SetName("Touch "+ String(i));
        t->SetVisible(false);
    }
}

void UIDrag::CreateInstructions()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    // Construct new Text object, set string to display and font to use
    Text* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText("Drag on the buttons to move them around.\nMulti- button drag also supported.");
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);

    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}

void UIDrag::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, HANDLER(UIDrag, HandleUpdate));
}

void UIDrag::HandleDragBegin(StringHash eventType, VariantMap& eventData)
{
    using namespace DragBegin;
    Button* element = (Button*)eventData[P_ELEMENT].GetVoidPtr();

    int lx = eventData[P_X].GetInt();
    int ly = eventData[P_Y].GetInt();

    IntVector2 p = element->GetPosition();
    element->SetVar("START", p);
    element->SetVar("DELTA", IntVector2(p.x_ - lx, p.y_ - ly));

    int buttons = eventData[P_BUTTONS].GetInt();
    element->SetVar("BUTTONS", buttons);

    Text* t = (Text*)element->GetChild(String("Text"));
    t->SetText("Drag Begin Buttons: " + String(buttons));

    t = (Text*)element->GetChild(String("Num Touch"));
    t->SetText("Number of buttons: " + String(eventData[P_NUMBUTTONS].GetInt()));
}

void UIDrag::HandleDragMove(StringHash eventType, VariantMap& eventData)
{
    using namespace DragBegin;
    Button* element = (Button*)eventData[P_ELEMENT].GetVoidPtr();
    int buttons = eventData[P_BUTTONS].GetInt();
    IntVector2 d = element->GetVar("DELTA").GetIntVector2();
    int X = eventData[P_X].GetInt() + d.x_;
    int Y = eventData[P_Y].GetInt() + d.y_;
    int BUTTONS = element->GetVar("BUTTONS").GetInt();

    Text* t = (Text*)element->GetChild(String("Event Touch"));
    t->SetText("Drag Move Buttons: " + String(buttons));

    if (buttons == BUTTONS)
        element->SetPosition(IntVector2(X, Y));
}

void UIDrag::HandleDragCancel(StringHash eventType, VariantMap& eventData)
{
    using namespace DragBegin;
    Button* element = (Button*)eventData[P_ELEMENT].GetVoidPtr();
    IntVector2 P = element->GetVar("START").GetIntVector2();
    element->SetPosition(P);
}

void UIDrag::HandleDragEnd(StringHash eventType, VariantMap& eventData)
{
    using namespace DragBegin;
    Button* element = (Button*)eventData[P_ELEMENT].GetVoidPtr();
}

void UIDrag::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    UI* ui = GetSubsystem<UI>();
    UIElement* root = ui->GetRoot();

    Input* input = GetSubsystem<Input>();

    unsigned n = input->GetNumTouches();
    for (unsigned i = 0; i < n; i++)
    {
        Text* t = (Text*)root->GetChild("Touch " + String(i));
        TouchState* ts = input->GetTouch(i);
        t->SetText("Touch " + String(ts->touchID_));

        IntVector2 pos = ts->position_;
        pos.y_ -= 30;

        t->SetPosition(pos);
        t->SetVisible(true);
    }

    for (unsigned i = n; i < 10; i++)
    {
        Text* t = (Text*)root->GetChild("Touch " + String(i));
        t->SetVisible(false);
    }
}
