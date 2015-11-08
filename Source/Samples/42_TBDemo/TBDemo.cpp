//
// Copyright (c) 2008-2015 the Urho3D project.
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
#include <Urho3D/UI/UTBMain.h>
#include <Urho3D/UI/UTBRendererBatcher.h>
#include <TurboBadger/tb_message_window.h>

#include "TBDemo.h"

#include <Urho3D/DebugNew.h>

//=============================================================================
//=============================================================================
// Expands to this example's entry-point
URHO3D_DEFINE_APPLICATION_MAIN(TBDemo)

//=============================================================================
//=============================================================================
TBDemo::TBDemo(Context* context)
    : Sample(context)
    , pUTBMain_( NULL )
    , pTBListener_( NULL )
{
}

//=============================================================================
//=============================================================================
TBDemo::~TBDemo()
{
    if ( pUTBMain_ )
    {
        pUTBMain_->Remove();
        pUTBMain_ = NULL;
    }

    if ( pTBListener_ )
    {
        delete pTBListener_;
        pTBListener_ = NULL;
    }
}

//=============================================================================
//=============================================================================
void TBDemo::Setup()
{
    // Modify engine startup parameters
    engineParameters_["WindowTitle"] = GetTypeName();
    engineParameters_["LogName"]     = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_["FullScreen"]  = false;
    engineParameters_["Headless"]    = false;
    engineParameters_["Sound"]       = false;
    engineParameters_["WindowWidth"] = 1280; 
    engineParameters_["WindowHeight"]= 720;
}

//=============================================================================
//=============================================================================
void TBDemo::Start()
{
    // Execute base class startup
    Sample::Start();

    // Set mouse visible
    String platform = GetPlatform();
    if ( platform != "Android" && platform != "iOS" )
    {
        GetSubsystem<Input>()->SetMouseVisible(true);
    }

    // create UTB main
    Graphics *graphics = GetSubsystem<Graphics>();
    pUTBMain_ = new UTBMain( GetContext(), graphics->GetWidth(), graphics->GetHeight() );
    pUTBMain_->Init( "Data/TB/" );

    // create a msg win
    pTBListener_ = new UTBListener( GetContext() );
    pTBListener_->CreateMsgWindow();

    SubscribeToEvent(E_TBMSG, URHO3D_HANDLER(TBDemo, HandleTBMessage));
}

void TBDemo::HandleTBMessage(StringHash eventType, VariantMap& eventData)
{
    using namespace TBMessageNamespace;

    TBWidget *pTBWidget = (TBWidget*)eventData[P_TBWIDGET].GetVoidPtr();

    if ( pTBListener_->GetTBMessageWidget() == pTBWidget )
    {
        pUTBMain_->RunDemo();
    }
}

//=============================================================================
//=============================================================================
UTBListener::UTBListener(Context *context)
    : Object( context )
    , pTBMessageWindow_( NULL )
{
}

UTBListener::~UTBListener()
{
    if ( pTBMessageWindow_ )
    {
        pTBMessageWindow_ = NULL;
    }
}

void UTBListener::CreateMsgWindow()
{
#ifdef URHO3D_TB_DEMO
    TBStr text("\nHellow World from Turbo Badger.\n\nClick OK to get started.");
#else
    TBStr text("\nHellow World\n\n-DURHO3D_TB_DEMO=1 missing in the build option\n");
#endif
    pTBMessageWindow_ = new TBMessageWindow( &UTBRendererBatcher::Singleton().Root(), TBIDC("") );
    pTBMessageWindow_->Show("Start Message", text);

    TBWidgetListener::AddGlobalListener( this );
}

void UTBListener::OnWidgetRemove(TBWidget *parent, TBWidget *child)
{
    if ( pTBMessageWindow_ == child )
    {
        TBWidgetListener::RemoveGlobalListener( this );
    }
}

bool UTBListener::OnWidgetInvokeEvent(TBWidget *widget, const TBWidgetEvent &ev) 
{ 
    if ( pTBMessageWindow_ && pTBMessageWindow_ == ev.target )
    {
        if ( ev.type == EVENT_TYPE_CLICK )
        {
            TBWidgetListener::RemoveGlobalListener( this );

            SendEventMsg();
        }
    }

    return false; 
}

void UTBListener::SendEventMsg()
{
    using namespace TBMessageNamespace;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_TBWIDGET] = GetTBMessageWidget();

    SendEvent( E_TBMSG, eventData );
}

