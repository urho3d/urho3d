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

#include "GUITest.h"

#include "Camera.h"
#include "CoreEvents.h"
#include "Engine.h"
#include "Font.h"
#include "Graphics.h"
#include "Input.h"
#include "Octree.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "Zone.h"
#include "Drawable2D.h"
#include "Log.h"

#include "UIEvents.h"
#include "Text.h"
#include "UIElement.h"
#include "Button.h"
#include "LineEdit.h"

#include "DebugNew.h"

DEFINE_APPLICATION_MAIN(GUITest)

GUITest::GUITest(Context* context) :
    Sample(context)
{
}

void GUITest::Start()
{
    // Execute base class startup
    Sample::Start();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateGUI();

    // Setup the viewport for displaying the scene
    SetupViewport();

    // Hook up to the frame update events
    SubscribeToEvents();
}

void GUITest::CreateScene()
{
    Log* log = GetSubsystem<Log>();
    log->SetLevel(0);
    log->SetQuiet(false);

    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();

    // Create camera node
    cameraNode_ = scene_->CreateChild("Camera");
    // Set camera's position
    cameraNode_->SetPosition(Vector3(0.0f, 0.0f, -10.0f));

    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetOrthographic(true);

    Graphics* graphics = GetSubsystem<Graphics>();
    camera->SetOrthoSize((float)graphics->GetHeight() * PIXEL_SIZE);

    GetSubsystem<Input>()->SetMouseVisible(true);
    GetSubsystem<Input>()->SetTouchEmulation(true);
}

void GUITest::CreateGUI()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    UIElement* root = ui->GetRoot();
    // Load the style sheet from xml
    root->SetDefaultStyle(cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));

    {
        LineEdit* l = new LineEdit(context_);
        root->AddChild(l);
        l->SetStyle("LineEdit");
        l->SetHorizontalAlignment(HA_CENTER);
        l->SetVerticalAlignment(VA_BOTTOM);
        l->SetSize(300, 40);
        l->SetMode(LEM_NUMERIC);
        l->SetValue(0.0f);
        l->SetDragEditIncrement(0.5f);
        // Can do a combo:
        //l->SetDragEditCombo(MOUSEB_LEFT | MOUSEB_RIGHT);
        l->SetDragEditCombo(MOUSEB_RIGHT);

        SubscribeToEvent(l, E_DRAGBEGIN, HANDLER(GUITest, HandleLineEditDragBegin));
        SubscribeToEvent(l, E_TEXTFINISHED, HANDLER(GUITest, HandleTextFinished));
    }
    for (int i=0; i < 10; i++)
    {
        Button* b = new Button(context_);
        root->AddChild(b);
        // Reference a style from the style sheet loaded earlier:
        b->SetStyle("Button");
        b->SetSize(300, 100);
        b->SetPosition(IntVector2(50*i, 50*i));

        SubscribeToEvent(b, E_DRAGMOVE, HANDLER(GUITest, HandleDragMove));
        SubscribeToEvent(b, E_DRAGBEGIN, HANDLER(GUITest, HandleDragBegin));
        SubscribeToEvent(b, E_DRAGCANCEL, HANDLER(GUITest, HandleDragCancel));
        SubscribeToEvent(b, E_DRAGEND, HANDLER(GUITest, HandleDragEnd));

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
        t->SetText("Touch "+ String(i));
        t->SetName("Touch "+ String(i));
        t->SetVisible(false);
    }
}

void GUITest::SetupViewport()
{
    Renderer* renderer = GetSubsystem<Renderer>();

    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void GUITest::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, HANDLER(GUITest, HandleUpdate));
    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent(E_SCENEUPDATE);
}

void GUITest::HandleDragBegin(StringHash eventType, VariantMap& eventData)
{
    using namespace DragBegin;
    Button* element = (Button*)eventData[P_ELEMENT].GetVoidPtr();

    element->BringToFront();

    int lx = eventData[P_X].GetInt();
    int ly = eventData[P_Y].GetInt();

    IntVector2 p = element->GetPosition();
    element->SetVar("STARTX", p.x_);
    element->SetVar("STARTY", p.y_);
    element->SetVar("DX", p.x_ - lx);
    element->SetVar("DY", p.y_ - ly);

    int buttons = eventData[P_BUTTONS].GetInt();
    element->SetVar("BUTTONS", buttons);

    Text* t = (Text*)element->GetChild(String("Text"));
    t->SetText(String(buttons));

    t = (Text*)element->GetChild(String("Num Touch"));
    t->SetText(String(eventData[P_NUMBUTTONS].GetInt()));
}

void GUITest::HandleDragMove(StringHash eventType, VariantMap& eventData)
{
    using namespace DragBegin;
    Button* element = (Button*)eventData[P_ELEMENT].GetVoidPtr();
    int buttons = eventData[P_BUTTONS].GetInt();
    int X = eventData[P_X].GetInt() + element->GetVar("DX").GetInt();
    int Y = eventData[P_Y].GetInt() + element->GetVar("DY").GetInt();
    int BUTTONS = element->GetVar("BUTTONS").GetInt();

    Text* t = (Text*)element->GetChild(String("Event Touch"));
    t->SetText(String(buttons));

    if (buttons == BUTTONS)
        element->SetPosition(IntVector2(X, Y));
}

void GUITest::HandleDragCancel(StringHash eventType, VariantMap& eventData)
{
    using namespace DragBegin;
    Button* element = (Button*)eventData[P_ELEMENT].GetVoidPtr();
    int X = element->GetVar("STARTX").GetInt();
    int Y = element->GetVar("STARTY").GetInt();
    element->SetPosition(IntVector2(X, Y));
}

void GUITest::HandleDragEnd(StringHash eventType, VariantMap& eventData)
{
    using namespace DragBegin;
    Button* element = (Button*)eventData[P_ELEMENT].GetVoidPtr();
}

void GUITest::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    UI* ui = GetSubsystem<UI>();
    UIElement* root = ui->GetRoot();

    Input* input = GetSubsystem<Input>();

    unsigned n = input->GetNumTouches();
    for (unsigned i = 0; i < n; i++)
    {
        Text* t = (Text*)root->GetChild("Touch " + String(i));
        TouchState* ts = input->GetTouch(i);

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

void GUITest::HandleTextFinished(StringHash eventType, VariantMap& eventData)
{
    using namespace TextFinished;
    LOGDEBUG("Text finished: " + eventData[P_TEXT].GetString());
    LOGDEBUG("Value finished: " + String(eventData[P_VALUE].GetFloat()));
}

void GUITest::HandleLineEditDragBegin(StringHash eventType, VariantMap& eventData)
{
    using namespace DragBegin;
    LineEdit* l = (LineEdit*)eventData[P_ELEMENT].GetVoidPtr();
    // Increment faster when the value in the LineEdit box is higher.
    l->SetDragEditIncrement(Clamp(Abs(l->GetValue() * 0.01f), 0.01f, 10.0f));
}
