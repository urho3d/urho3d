//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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
#include "CheckBox.h"
#include "Context.h"
#include "CoreEvents.h"
#include "Cursor.h"
#include "DropDownList.h"
#include "FileSelector.h"
#include "Font.h"
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "GraphicsImpl.h"
#include "InputEvents.h"
#include "LineEdit.h"
#include "ListView.h"
#include "Log.h"
#include "Matrix4x3.h"
#include "PixelShader.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "ScrollBar.h"
#include "Slider.h"
#include "StringUtils.h"
#include "Text.h"
#include "Texture2D.h"
#include "Time.h"
#include "UI.h"
#include "UIEvents.h"
#include "VertexShader.h"
#include "Window.h"

#include "Sort.h"

#include "DebugNew.h"

static bool CompareUIElements(const UIElement* lhs, const UIElement* rhs)
{
    return lhs->GetPriority() < rhs->GetPriority();
}

OBJECTTYPESTATIC(UI);

UI::UI(Context* context) :
    Object(context),
    mouseButtons_(0),
    qualifiers_(0),
    initialized_(false)
{
    SubscribeToEvent(E_SCREENMODE, HANDLER(UI, HandleScreenMode));
    SubscribeToEvent(E_MOUSEMOVE, HANDLER(UI, HandleMouseMove));
    SubscribeToEvent(E_MOUSEBUTTONDOWN, HANDLER(UI, HandleMouseButtonDown));
    SubscribeToEvent(E_MOUSEBUTTONUP, HANDLER(UI, HandleMouseButtonUp));
    SubscribeToEvent(E_MOUSEWHEEL, HANDLER(UI, HandleMouseWheel));
    SubscribeToEvent(E_KEYDOWN, HANDLER(UI, HandleKeyDown));
    SubscribeToEvent(E_CHAR, HANDLER(UI, HandleChar));
    SubscribeToEvent(E_POSTUPDATE, HANDLER(UI, HandlePostUpdate));
    SubscribeToEvent(E_RENDERUPDATE, HANDLER(UI, HandleRenderUpdate));
    
    // Try to initialize right now, but skip if screen mode is not yet set
    Initialize();
}

UI::~UI()
{
}

void UI::SetCursor(Cursor* cursor)
{
    // Remove old cursor (if any) and set new
    if (cursor_)
    {
        rootElement_->RemoveChild(cursor_);
        cursor_.Reset();
    }
    if (cursor)
    {
        rootElement_->AddChild(cursor);
        cursor_ = cursor;
        
        IntVector2 pos = cursor_->GetPosition();
        const IntVector2& rootSize = rootElement_->GetSize();
        pos.x_ = Clamp(pos.x_, 0, rootSize.x_ - 1);
        pos.y_ = Clamp(pos.y_, 0, rootSize.y_ - 1);
        cursor_->SetPosition(pos);
    }
}

void UI::SetFocusElement(UIElement* element)
{
    using namespace FocusChanged;
    
    VariantMap eventData;
    eventData[P_ORIGINALELEMENT] = (void*)element;
    
    if (element)
    {
        // Return if already has focus
        if (element->HasFocus())
            return;
        // If element can not be focused, and does not reset the focus either, search toward the parent
        for (;;)
        {
            if (element->GetFocusMode() != FM_NOTFOCUSABLE)
                break;
            element = element->GetParent();
            // Return if did not find any parent element that changes the focus
            if (!element)
                return;
        }
    }
    
    Vector<UIElement*> allChildren = rootElement_->GetChildren(true);
    
    // Go through all elements to clear the old focus
    for (Vector<UIElement*>::Iterator i = allChildren.Begin(); i != allChildren.End(); ++i)
    {
        UIElement* other = *i;
        if ((other != element) && (other->HasFocus()))
            other->SetFocus(false);
    }
    
    if (element)
        element->SetFocus(true);
    
    eventData[P_ELEMENT] = (void*)element;
    SendEvent(E_FOCUSCHANGED, eventData);
}

void UI::Clear()
{
    rootElement_->RemoveAllChildren();
    if (cursor_)
        rootElement_->AddChild(cursor_);
}

void UI::Update(float timeStep)
{
    PROFILE(UpdateUI);
    
    if ((cursor_) && (cursor_->IsVisible()))
    {
        IntVector2 pos = cursor_->GetPosition();
        WeakPtr<UIElement> element(GetElementAt(pos));
        
        bool dragSource = (dragElement_) && ((dragElement_->GetDragDropMode() & DD_SOURCE) != 0);
        bool dragTarget = (element) && ((element->GetDragDropMode() & DD_TARGET) != 0);
        bool dragDropTest = (dragSource) && (dragTarget) && (element != dragElement_);
        
        // Hover effect
        // If a drag is going on, transmit hover only to the element being dragged, unless it's a drop target
        if (element)
        {
            if ((!dragElement_) || (dragElement_ == element) || (dragDropTest))
                element->OnHover(element->ScreenToElement(pos), pos, mouseButtons_, qualifiers_, cursor_);
        }
        
        // Drag and drop test
        if (dragDropTest)
        {
            bool accept = element->OnDragDropTest(dragElement_);
            if (accept)
            {
                using namespace DragDropTest;
                
                VariantMap eventData;
                eventData[P_SOURCE] = (void*)dragElement_.GetPtr();
                eventData[P_TARGET] = (void*)element.GetPtr();
                eventData[P_ACCEPT] = accept;
                SendEvent(E_DRAGDROPTEST, eventData);
                accept = eventData[P_ACCEPT].GetBool();
            }
            
            cursor_->SetShape(accept ? CS_ACCEPTDROP : CS_REJECTDROP);
        }
        else if (dragSource)
            cursor_->SetShape(dragElement_ == element ? CS_ACCEPTDROP : CS_REJECTDROP);
    }
    
    // Defocus element now if should
    if (defocusElement_)
    {
        // Do nothing if the focus element changed in the meanwhile
        if (defocusElement_ == GetFocusElement())
            SetFocusElement(0);
        defocusElement_.Reset();
    }
    
    Update(timeStep, rootElement_);
}

void UI::RenderUpdate()
{
    if ((!graphics_) || (graphics_->IsDeviceLost()))
        return;
    
    PROFILE(GetUIBatches);
    
    batches_.Clear();
    quads_.Clear();
    const IntVector2& rootSize = rootElement_->GetSize();
    GetBatches(rootElement_, IntRect(0, 0, rootSize.x_, rootSize.y_));
    
    // If no drag, reset cursor shape for next frame
    if ((cursor_) && (!dragElement_))
        cursor_->SetShape(CS_NORMAL);
}

void UI::Render()
{
    PROFILE(RenderUI);
    
    if (!graphics_)
        return;
    
    Vector2 scale(2.0f, -2.0f);
    Vector2 offset(-1.0f, 1.0f);
    
    Matrix4 projection(Matrix4::IDENTITY);
    projection.m00_ = scale.x_;
    projection.m03_ = offset.x_;
    projection.m11_ = scale.y_;
    projection.m13_ = offset.y_;
    projection.m22_ = 1.0f;
    projection.m23_ = 0.0f;
    projection.m33_ = 1.0f;
    
    graphics_->ResetRenderTargets();
    graphics_->SetCullMode(CULL_CCW);
    graphics_->SetDepthTest(CMP_ALWAYS);
    graphics_->SetDepthWrite(false);
    graphics_->SetFillMode(FILL_SOLID);
    graphics_->SetStencilTest(false);
    graphics_->SetVertexShaderParameter(VSP_MODEL, Matrix4x3::IDENTITY);
    graphics_->SetVertexShaderParameter(VSP_VIEWPROJ, projection);
    graphics_->SetPixelShaderParameter(PSP_MATDIFFCOLOR, Color(1.0f, 1.0f, 1.0f, 1.0f));
    
    PixelShader* ps = 0;
    VertexShader* vs = 0;
    
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        // Choose shaders here so that UIBatch does not need to look up shaders each time
        if (!batches_[i].texture_)
        {
            ps = noTexturePS_;
            vs = noTextureVS_;
        }
        else
        {
            // If texture contains only an alpha channel, use the alpha pixel shader
            vs = diffTextureVS_;
            
            if (batches_[i].texture_->GetFormat() == D3DFMT_A8)
                ps = alphaTexturePS_;
            else
                ps = diffTexturePS_;
        }
        
        batches_[i].Draw(graphics_, vs, ps);
    }
}

SharedPtr<UIElement> UI::LoadLayout(XMLFile* file, XMLFile* styleFile)
{
    PROFILE(LoadUILayout);
    
    SharedPtr<UIElement> root;
    
    if (!file)
    {
        LOGERROR("Null UI layout XML file");
        return root;
    }
    
    LOGDEBUG("Loading UI layout " + file->GetName());
    
    XMLElement rootElem = file->GetRootElement("element");
    if (!rootElem)
    {
        LOGERROR("No root UI element in " + file->GetName());
        return root;
    }
    
    String type = rootElem.GetString("type");
    root = DynamicCast<UIElement>(context_->CreateObject(ShortStringHash(type)));
    if (!root)
    {
        LOGERROR("Could not create UI element " + type);
        return root;
    }
    root->SetName(rootElem.GetString("name"));
    
    String styleName = rootElem.HasAttribute("style") ? rootElem.GetString("style") : rootElem.GetString("type");
    // First set the base style from the style file if exists, then apply UI layout overrides
    if (styleFile)
        root->SetStyle(styleFile, styleName);
    root->SetStyle(rootElem);
    
    // Load rest of the elements recursively
    LoadLayout(root, rootElem, styleFile);
    
    return root;
}

void UI::SetClipBoardText(const String& text)
{
    clipBoard_ = text;
}

UIElement* UI::GetElementAt(const IntVector2& position, bool activeOnly)
{
    UIElement* result = 0;
    GetElementAt(result, rootElement_, position, activeOnly);
    return result;
}

UIElement* UI::GetElementAt(int x, int y, bool activeOnly)
{
    return GetElementAt(IntVector2(x, y), activeOnly);
}

UIElement* UI::GetFocusElement() const
{
    Vector<UIElement*> allChildren = rootElement_->GetChildren(true);
    for (Vector<UIElement*>::Iterator i = allChildren.Begin(); i != allChildren.End(); ++i)
    {
        if ((*i)->HasFocus())
            return *i;
    }
    
    return 0;
}

UIElement* UI::GetFrontElement() const
{
    Vector<UIElement*> rootChildren = rootElement_->GetChildren(false);
    int maxPriority = M_MIN_INT;
    UIElement* front = 0;
    
    for (unsigned i = 0; i < rootChildren.Size(); ++i)
    {
        // Do not take into account input-disabled elements, hidden elements or those that are always in the front
        if ((!rootChildren[i]->IsActive()) || (!rootChildren[i]->IsVisible()) || (!rootChildren[i]->GetBringToBack()))
            continue;
        
        int priority = rootChildren[i]->GetPriority();
        if (priority > maxPriority)
        {
            maxPriority = priority;
            front = rootChildren[i];
        }
    }
    
    return front;
}

IntVector2 UI::GetCursorPosition()
{
    if (!cursor_)
        return IntVector2::ZERO;
    else
        return cursor_->GetPosition();
}

void UI::Initialize()
{
    Graphics* graphics = GetSubsystem<Graphics>();
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    if ((!graphics) || (!graphics->IsInitialized()) || (!cache))
        return;
    
    PROFILE(InitUI);
    
    graphics_ = graphics;
    cache_ = cache;
    
    rootElement_ = new UIElement(context_);
    rootElement_->SetSize(graphics->GetWidth(), graphics->GetHeight());
    
    noTextureVS_ = cache->GetResource<VertexShader>("Shaders/SM2/Basic_VCol.vs2");
    diffTextureVS_ = cache->GetResource<VertexShader>("Shaders/SM2/Basic_DiffVCol.vs2");
    noTexturePS_ = cache->GetResource<PixelShader>("Shaders/SM2/Basic_VCol.ps2");
    diffTexturePS_ = cache->GetResource<PixelShader>("Shaders/SM2/Basic_DiffVCol.ps2");
    alphaTexturePS_ = cache->GetResource<PixelShader>("Shaders/SM2/Basic_AlphaVCol.ps2");
    
    LOGINFO("Initialized user interface");
    initialized_ = true;
}

void UI::Update(float timeStep, UIElement* element)
{
    element->Update(timeStep);
    
    const Vector<UIElement*> children = element->GetChildren();
    for (Vector<UIElement*>::ConstIterator i = children.Begin(); i != children.End(); ++i)
        Update(timeStep, *i);
}

void UI::GetBatches(UIElement* element, IntRect currentScissor)
{
    // Set clipping scissor for child elements. No need to draw if zero size
    element->AdjustScissor(currentScissor);
    if ((currentScissor.left_ == currentScissor.right_) || (currentScissor.top_ == currentScissor.bottom_))
        return;
    
    Vector<UIElement*> children = element->GetChildren();
    if (children.Empty())
        return;
    
    Sort(children.Begin(), children.End(), CompareUIElements);
    
    // For non-root elements draw all children of same priority before recursing into their children: assumption is that they have
    // same renderstate
    Vector<UIElement*>::ConstIterator i = children.Begin();
    if (element != rootElement_)
    {
        Vector<UIElement*>::ConstIterator j = i;
        int currentPriority = children.Front()->GetPriority();
        while (i != children.End())
        {
            while ((j != children.End()) && ((*j)->GetPriority() == currentPriority))
            {
                if ((*j)->IsVisible())
                    (*j)->GetBatches(batches_, quads_, currentScissor);
                ++j;
            }
            // Now recurse into the children
            while (i != j)
            {
                if ((*i)->IsVisible())
                    GetBatches(*i, currentScissor);
                ++i;
            }
            if (i != children.End())
                currentPriority = (*i)->GetPriority();
        }
    }
    // On the root level draw each element and its children immediately after to avoid artifacts
    else
    {
        while (i != children.End())
        {
            if ((*i)->IsVisible())
            {
                (*i)->GetBatches(batches_, quads_, currentScissor);
                GetBatches(*i, currentScissor);
            }
            ++i;
        }
    }
}

void UI::GetElementAt(UIElement*& result, UIElement* current, const IntVector2& position, bool activeOnly)
{
    if (!current)
        return;
    
    // Get children from lowest priority to highest
    Vector<UIElement*> children = current->GetChildren(false);
    Sort(children.Begin(), children.End(), CompareUIElements);
    
    for (Vector<UIElement*>::ConstIterator i = children.Begin(); i != children.End(); ++i)
    {
        UIElement* element = *i;
        if ((element != cursor_.GetPtr()) && (element->IsVisible()))
        {
            if (element->IsInside(position, true))
            {
                // Store the current result, then recurse into its children. Because children
                // are sorted from lowest to highest priority, the topmost match should remain
                if ((element->IsActive()) || (!activeOnly))
                    result = element;
            }
            
            if (element->IsInsideCombined(position, true))
                GetElementAt(result, element, position, activeOnly);
        }
    }
}

void UI::LoadLayout(UIElement* current, const XMLElement& elem, XMLFile* styleFile)
{
    XMLElement childElem = elem.GetChildElement("element");
    while (childElem)
    {
        // Create element
        String type = childElem.GetString("type");
        SharedPtr<UIElement> child = DynamicCast<UIElement>(context_->CreateObject(ShortStringHash(type)));
        if (!child)
        {
            LOGERROR("Could not create UI element " + type);
            childElem = childElem.GetNextElement("element");
            continue;
        }
        child->SetName(childElem.GetString("name"));
        
        // Add to the hierarchy
        current->AddChild(child);
        
        // First set the base style from the style file if exists, then apply UI layout overrides
        String styleName = childElem.HasAttribute("style") ? childElem.GetString("style") : childElem.GetString("type");
        if (styleFile)
            child->SetStyle(styleFile, styleName);
        child->SetStyle(childElem);
        
        // Load the children recursively
        LoadLayout(child, childElem, styleFile);
        
        childElem = childElem.GetNextElement("element");
    }
}

void UI::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    using namespace ScreenMode;
    
    if (!initialized_)
        Initialize();
    else
        rootElement_->SetSize(eventData[P_WIDTH].GetInt(), eventData[P_HEIGHT].GetInt());
}

void UI::HandleMouseMove(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseMove;
    
    mouseButtons_ = eventData[P_BUTTONS].GetInt();
    qualifiers_ = eventData[P_QUALIFIERS].GetInt();
    
    if (cursor_)
    {
        const IntVector2& rootSize = rootElement_->GetSize();
        
        if (eventData[P_CLIPCURSOR].GetBool())
        {
            // When in confined cursor mode, move cursor only when visible
            if (cursor_->IsVisible())
            {
                IntVector2 pos = cursor_->GetPosition();
                pos.x_ += eventData[P_DX].GetInt();
                pos.y_ += eventData[P_DY].GetInt();
                pos.x_ = Clamp(pos.x_, 0, rootSize.x_ - 1);
                pos.y_ = Clamp(pos.y_, 0, rootSize.y_ - 1);
                cursor_->SetPosition(pos);
            }
        }
        else
        {
            // When in non-confined mode, move cursor always to ensure accurate position
            IntVector2 pos(eventData[P_X].GetInt(), eventData[P_Y].GetInt());
            bool inside = (pos.x_ >= 0) && (pos.x_ < rootSize.x_) && (pos.y_ >= 0) && (pos.y_ < rootSize.y_);
            
            // Hide by moving completely outside if outside
            // (do not use SetVisible(), so that actual visibility remains under application control)
            if (pos.x_ < 0)
                pos.x_ = -cursor_->GetWidth() * 2;
            if (pos.x_ >= rootSize.x_)
                pos.x_ = rootSize.x_ + cursor_->GetWidth() * 2;
            if (pos.y_ < 0)
                pos.y_ = -cursor_->GetHeight() * 2;
            if (pos.y_ >= rootSize.y_)
                pos.y_ = rootSize.y_ + cursor_->GetHeight() * 2;
            cursor_->SetPosition(pos);
            
            // Do not drag when outside
            if (!inside)
                return;
        }
        
        if ((dragElement_) && (mouseButtons_))
        {
            IntVector2 pos = cursor_->GetPosition();
            if ((dragElement_->IsActive()) && (dragElement_->IsVisible()))
                dragElement_->OnDragMove(dragElement_->ScreenToElement(pos), pos, mouseButtons_, qualifiers_, cursor_);
            else
            {
                dragElement_->OnDragEnd(dragElement_->ScreenToElement(pos), pos, cursor_);
                dragElement_.Reset();
            }
        }
    }
}

void UI::HandleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
    mouseButtons_ = eventData[MouseButtonDown::P_BUTTONS].GetInt();
    qualifiers_ = eventData[MouseButtonDown::P_QUALIFIERS].GetInt();
    int button = eventData[MouseButtonDown::P_BUTTON].GetInt();
    
    if ((cursor_) && (cursor_->IsVisible()))
    {
        IntVector2 pos = cursor_->GetPosition();
        WeakPtr<UIElement> element(GetElementAt(pos));
        
        if (element)
        {
            // Handle focusing & bringing to front
            if (button == MOUSEB_LEFT)
            {
                SetFocusElement(element);
                element->BringToFront();
            }
            
            // Handle click
            element->OnClick(element->ScreenToElement(pos), pos, mouseButtons_, qualifiers_, cursor_);
            
            // Handle start of drag. OnClick() may have caused destruction of the element, so check the pointer again
            if ((element) && (!dragElement_) && (mouseButtons_ == MOUSEB_LEFT))
            {
                dragElement_ = element;
                element->OnDragStart(element->ScreenToElement(pos), pos, mouseButtons_, qualifiers_, cursor_);
            }
        }
        else
        {
            // If clicked over no element, or a disabled element, try to lose focus
            defocusElement_ = GetFocusElement();
        }
        
        using namespace UIMouseClick;
        
        VariantMap eventData;
        eventData[UIMouseClick::P_ELEMENT] = (void*)element.GetPtr();
        eventData[UIMouseClick::P_X] = pos.x_;
        eventData[UIMouseClick::P_Y] = pos.y_;
        eventData[UIMouseClick::P_BUTTON] = button;
        eventData[UIMouseClick::P_BUTTONS] = mouseButtons_;
        eventData[UIMouseClick::P_QUALIFIERS] = qualifiers_;
        SendEvent(E_UIMOUSECLICK, eventData);
    }
}

void UI::HandleMouseButtonUp(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseButtonUp;
    
    mouseButtons_ = eventData[P_BUTTONS].GetInt();
    qualifiers_ = eventData[P_QUALIFIERS].GetInt();
    
    if ((cursor_) && ((cursor_->IsVisible()) || (dragElement_)))
    {
        IntVector2 pos = cursor_->GetPosition();
        
        if ((dragElement_) && (!mouseButtons_))
        {
            if ((dragElement_->IsActive()) && (dragElement_->IsVisible()))
            {
                dragElement_->OnDragEnd(dragElement_->ScreenToElement(pos), pos, cursor_);
                
                // Drag and drop finish
                bool dragSource = (dragElement_) && ((dragElement_->GetDragDropMode() & DD_SOURCE) != 0);
                if (dragSource)
                {
                    WeakPtr<UIElement> target(GetElementAt(pos));
                    bool dragTarget = (target) && ((target->GetDragDropMode() & DD_TARGET) != 0);
                    bool dragDropFinish = (dragSource) && (dragTarget) && (target != dragElement_);
                    
                    if (dragDropFinish)
                    {
                        bool accept = target->OnDragDropFinish(dragElement_);
                        
                        // OnDragDropFinish() may have caused destruction of the elements, so check the pointers again
                        if ((accept) && (dragElement_) && (target))
                        {
                            using namespace DragDropFinish;
                            
                            VariantMap eventData;
                            eventData[P_SOURCE] = (void*)dragElement_.GetPtr();
                            eventData[P_TARGET] = (void*)target.GetPtr();
                            eventData[P_ACCEPT] = accept;
                            SendEvent(E_DRAGDROPFINISH, eventData);
                        }
                    }
                }
            }
            
            dragElement_.Reset();
        }
    }
}

void UI::HandleMouseWheel(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseWheel;
    
    mouseButtons_ = eventData[P_BUTTONS].GetInt();
    qualifiers_ = eventData[P_QUALIFIERS].GetInt();
    int delta = eventData[P_WHEEL].GetInt();
    
    UIElement* element = GetFocusElement();
    if (element)
        element->OnWheel(delta, mouseButtons_, qualifiers_);
}

void UI::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;
    
    mouseButtons_ = eventData[P_BUTTONS].GetInt();
    qualifiers_ = eventData[P_QUALIFIERS].GetInt();
    int key = eventData[P_KEY].GetInt();
    
    UIElement* element = GetFocusElement();
    if (element)
    {
        // Switch focus between focusable elements in the same top level window
        if (key == KEY_TAB)
        {
            UIElement* topLevel = element->GetParent();
            while ((topLevel) && (topLevel->GetParent() != rootElement_))
                topLevel = topLevel->GetParent();
            if (topLevel)
            {
                Vector<UIElement*> children = topLevel->GetChildren(true);
                for (Vector<UIElement*>::Iterator i = children.Begin(); i != children.End();)
                {
                    if ((*i)->GetFocusMode() < FM_FOCUSABLE)
                        i = children.Erase(i);
                    else
                        ++i;
                }
                for (unsigned i = 0; i < children.Size(); ++i)
                {
                    if (children[i] == element)
                    {
                        UIElement* next = children[(i + 1) % children.Size()];
                        SetFocusElement(next);
                        return;
                    }
                }
            }
        }
        // Defocus the element
        else if ((key == KEY_ESC) && (element->GetFocusMode() == FM_FOCUSABLE_DEFOCUSABLE))
            defocusElement_ = element;
        // If none of the special keys, pass the key to the focused element
        else
            element->OnKey(key, mouseButtons_, qualifiers_);
    }
}

void UI::HandleChar(StringHash eventType, VariantMap& eventData)
{
    using namespace Char;
    
    mouseButtons_ = eventData[P_BUTTONS].GetInt();
    qualifiers_ = eventData[P_QUALIFIERS].GetInt();
    
    UIElement* element = GetFocusElement();
    if (element)
        element->OnChar(eventData[P_CHAR].GetInt(), mouseButtons_, qualifiers_);
}

void UI::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    if (initialized_)
    {
        using namespace PostUpdate;
        
        Update(eventData[P_TIMESTEP].GetFloat());
    }
}

void UI::HandleRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    if (initialized_)
        RenderUpdate();
}

void RegisterUILibrary(Context* context)
{
    Font::RegisterObject(context);
    
    UIElement::RegisterObject(context);
    BorderImage::RegisterObject(context);
    Button::RegisterObject(context);
    CheckBox::RegisterObject(context);
    Cursor::RegisterObject(context);
    Text::RegisterObject(context);
    Window::RegisterObject(context);
    LineEdit::RegisterObject(context);
    Slider::RegisterObject(context);
    ScrollBar::RegisterObject(context);
    ScrollView::RegisterObject(context);
    ListView::RegisterObject(context);
    Menu::RegisterObject(context);
    DropDownList::RegisterObject(context);
    FileSelector::RegisterObject(context);
}
