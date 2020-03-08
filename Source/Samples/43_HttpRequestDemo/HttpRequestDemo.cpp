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

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/HttpRequest.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>

#include "HttpRequestDemo.h"

#include <Urho3D/DebugNew.h>

URHO3D_DEFINE_APPLICATION_MAIN(HttpRequestDemo)

HttpRequestDemo::HttpRequestDemo(Context* context) :
    Sample(context)
{
}

void HttpRequestDemo::Start()
{
    // Execute base class startup
    Sample::Start();

    // Create the user interface
    CreateUI();

    // Subscribe to basic events such as update
    SubscribeToEvents();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);
}

void HttpRequestDemo::CreateUI()
{
    auto* cache = GetSubsystem<ResourceCache>();

    // Construct new Text object
    text_ = new Text(context_);

    // Set font and text color
    text_->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
    text_->SetColor(Color(1.0f, 1.0f, 0.0f));

    // Align Text center-screen
    text_->SetHorizontalAlignment(HA_CENTER);
    text_->SetVerticalAlignment(VA_CENTER);

    // Add Text instance to the UI root element
    GetSubsystem<UI>()->GetRoot()->AddChild(text_);
}

void HttpRequestDemo::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing HTTP request
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(HttpRequestDemo, HandleUpdate));
}

void HttpRequestDemo::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    auto* network = GetSubsystem<Network>();

    if (httpRequest_.Null())
        httpRequest_ = network->MakeHttpRequest("http://httpbin.org/ip");
    else
    {
        // Initializing HTTP request
        if (httpRequest_->GetState() == HTTP_INITIALIZING)
            return;
        // An error has occurred
        else if (httpRequest_->GetState() == HTTP_ERROR)
        {
            text_->SetText("An error has occurred.");
            UnsubscribeFromEvent("Update");
        }
        // Get message data
        else
        {
            if (httpRequest_->GetAvailableSize() > 0)
                message_ += httpRequest_->ReadLine();
            else
            {
                text_->SetText("Processing...");

                SharedPtr<JSONFile> json(new JSONFile(context_));
                json->FromString(message_);

                JSONValue val = json->GetRoot().Get("origin");

                if (val.IsNull())
                    text_->SetText("Invalid string.");
                else
                    text_->SetText("Your IP is: " + val.GetString());

                UnsubscribeFromEvent("Update");
            }
        }
    }
}
