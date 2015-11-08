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

#pragma once

#include "Sample.h"

namespace Urho3D
{
class UTBMain;
}

namespace tb
{
class TBMessageWindow;
}

using namespace tb;
using namespace Urho3D;

//=============================================================================
URHO3D_EVENT(E_TBMSG, TBMessageNamespace)
{
    URHO3D_PARAM(P_TBWIDGET, Widget);  // TBWidget pointer
}

//=============================================================================
//=============================================================================
class UTBListener : public Object, public TBWidgetListener
{
    URHO3D_OBJECT(UTBListener, Object);
public:
    UTBListener(Context *context);

    ~UTBListener();

    void CreateMsgWindow();
	virtual void OnWidgetRemove(TBWidget *parent, TBWidget *child);
	virtual bool OnWidgetInvokeEvent(TBWidget *widget, const TBWidgetEvent &ev);

    TBWidget* GetTBMessageWidget()
    {
        return (TBWidget*)pTBMessageWindow_;
    }
protected:
    void SendEventMsg();

protected:
    TBMessageWindow     *pTBMessageWindow_;

};

//=============================================================================
//=============================================================================
/// Database demo. This sample demonstrates how to use database subsystem to connect to a database and execute adhoc SQL statements.
class TBDemo : public Sample
{
    URHO3D_OBJECT(TBDemo, Sample)

public:
    /// Construct.
    TBDemo(Context* context);
    /// Destruct.
    virtual ~TBDemo();

    /// Setup after engine initialization and before running the main loop.
    virtual void Setup();
    virtual void Start();

protected:
    void HandleTBMessage(StringHash eventType, VariantMap& eventData);

    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    virtual String GetScreenJoystickPatchString() const { return
        "<patch>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button2']]\">"
        "        <attribute name=\"Is Visible\" value=\"false\" />"
        "    </add>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">"
        "        <attribute name=\"Is Visible\" value=\"false\" />"
        "    </add>"
        "</patch>";
    }

    SharedPtr<UTBMain>  pUTBMain_;
    UTBListener         *pTBListener_;
};
