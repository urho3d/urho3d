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

#include "Precompiled.h"
#include "Context.h"
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "InputEvents.h"
#include "Log.h"
#include "Node.h"
#include "UIRoot.h"

#include "DebugNew.h"

namespace Urho3D
{

extern URHO3D_API const float PIXEL_SIZE;

UIRoot::UIRoot(Context* context) :
    UIRect(context)
{
    SubscribeToEvent(E_SCREENMODE, HANDLER(UIRoot, HandleScreenMode));
    SubscribeToEvent(E_MOUSEBUTTONDOWN, HANDLER(UIRoot, HandleMouseButtonDown));
    SubscribeToEvent(E_MOUSEBUTTONUP, HANDLER(UIRoot, HandleMouseButtonUp));
    SubscribeToEvent(E_MOUSEMOVE, HANDLER(UIRoot, HandleMouseMove));
    // SubscribeToEvent(E_MOUSEWHEEL, HANDLER(UIRoot, HandleMouseWheel));
    // SubscribeToEvent(E_TOUCHBEGIN, HANDLER(UIRoot, HandleTouchBegin));
    // SubscribeToEvent(E_TOUCHEND, HANDLER(UIRoot, HandleTouchEnd));
    // SubscribeToEvent(E_TOUCHMOVE, HANDLER(UIRoot, HandleTouchMove));
    // SubscribeToEvent(E_KEYDOWN, HANDLER(UIRoot, HandleKeyDown));
    // SubscribeToEvent(E_TEXTINPUT, HANDLER(UIRoot, HandleTextInput));
    // SubscribeToEvent(E_DROPFILE, HANDLER(UIRoot, HandleDropFile));
}

UIRoot::~UIRoot()
{
}

void UIRoot::RegisterObject(Context* context)
{
    context->RegisterFactory<UIRoot>();    
}

void UIRoot::OnNodeSet(Node* node)
{
    Graphics* graphics = GetSubsystem<Graphics>();
    float width = (float)(graphics->GetWidth()) * PIXEL_SIZE;
    float height = (float)(graphics->GetHeight()) * PIXEL_SIZE;
    SetSize(Vector2(width, height));
}

void UIRoot::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    using namespace ScreenMode;
    
    float width = ((float)eventData[P_WIDTH].GetInt()) * PIXEL_SIZE;
    float height = ((float)eventData[P_HEIGHT].GetInt()) * PIXEL_SIZE;
    SetSize(Vector2(width, height));
}

void UIRoot::HandleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseButtonDown;

    // TODO:
}

void UIRoot::HandleMouseButtonUp(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseButtonUp;

    // TODO:
}

void UIRoot::HandleMouseMove(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseMove;

    // TODO:
}

}