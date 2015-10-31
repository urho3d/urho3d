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
{
}

//=============================================================================
//=============================================================================
TBDemo::~TBDemo()
{
    if ( pUTBMain_ )
    {
        delete pUTBMain_;
        pUTBMain_ = NULL;
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
    pUTBMain_->RunDemo();
}


