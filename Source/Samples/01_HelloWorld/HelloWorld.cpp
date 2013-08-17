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

#include "CoreEvents.h"
#include "Engine.h"
#include "Font.h"
#include "Input.h"
#include "ProcessUtils.h"
#include "Text.h"
#include "UI.h"

#include "HelloWorld.h"

#include "DebugNew.h"

// Expands to this example's entry-point
DEFINE_APPLICATION_MAIN(HelloWorld)

HelloWorld::HelloWorld(Context* context) :
    Sample(context)
{
}

void HelloWorld::Start()
{
    // Execute base class startup
    Sample::Start();

    // Create "Hello World" Text
    CreateText();

    // Finally, hook-up this HelloWorld instance to handle update events
    SubscribeToEvents();
}

void HelloWorld::CreateText()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    // Construct new Text object
    SharedPtr<Text> helloText(new Text(context_));

    // Set String to display
    helloText->SetText("Hello World from Urho3D!");

    // Set font and text color
    helloText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 30);
    helloText->SetColor(Color(0.0f, 1.0f, 0.0f));

    // Align Text center-screen
    helloText->SetHorizontalAlignment(HA_CENTER);
    helloText->SetVerticalAlignment(VA_CENTER);

    // Add Text instance to the UI root element
    GetSubsystem<UI>()->GetRoot()->AddChild(helloText);
}

void HelloWorld::SubscribeToEvents()
{
    // Subscribes HandleUpdate() method for processing update events
    SubscribeToEvent(E_UPDATE, HANDLER(HelloWorld, HandleUpdate));
}

void HelloWorld::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Do nothing for now, could be extended to eg. animate the display
}
