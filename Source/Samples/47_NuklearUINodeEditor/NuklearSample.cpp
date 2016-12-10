//
// Copyright (c) 2008-2017 the Urho3D project.
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
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>

#include "NuklearSample.h"
#include "Urho3D/NuklearUI/NuklearUI.h"

URHO3D_DEFINE_APPLICATION_MAIN(NuklearSample)

NuklearSample::NuklearSample(Context* context)
    : Sample(context)
{
}

void NuklearSample::Start()
{
    // Execute base class startup
    Sample::Start();

    // Finally subscribe to the update event. Note that by subscribing events at this point we have already missed some events
    // like the ScreenMode event sent by the Graphics subsystem when opening the application window. To catch those as well we
    // could subscribe in the constructor instead.
    SubscribeToEvents();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);

    Nuklear = new NuklearUI(context_);
    context_->RegisterSubsystem(Nuklear);

	// Additional font initialization here.
	// Nuklear->SetFont("Fonts/Anonymous Pro.ttf", 14);
    Nuklear->FinalizeFonts();
}

void NuklearSample::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(NuklearSample, HandleUpdate));
}

void NuklearSample::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Get Nuklear context from Nuklear Subsystem
    Nuklear::nk_context* Context = Nuklear->GetNkContext();

    if (!Context)
    {
        return;
    }
    Nuklear::node_editor(Context);
}
