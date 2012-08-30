//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Input.h"
#include "InputEvents.h"
#include "LineEdit.h"
#include "ListView.h"
#include "Log.h"
#include "Matrix3x4.h"
#include "Profiler.h"
#include "Renderer.h"
#include "ScrollBar.h"
#include "Shader.h"
#include "ShaderVariation.h"
#include "Slider.h"
#include "Text.h"
#include "Texture2D.h"
#include "UI.h"
#include "UIEvents.h"
#include "VertexBuffer.h"
#include "Window.h"

#include "Sort.h"

#include "DebugNew.h"

namespace Urho3D
{

OBJECTTYPESTATIC(UI);

UI::UI(Context* context) :
    Object(context),
    mouseButtons_(0),
    qualifiers_(0),
    initialized_(false)
{
    SubscribeToEvent(E_SCREENMODE, HANDLER(UI, HandleScreenMode));
    SubscribeToEvent(E_MOUSEBUTTONDOWN, HANDLER(UI, HandleMouseButtonDown));
    SubscribeToEvent(E_MOUSEBUTTONUP, HANDLER(UI, HandleMouseButtonUp));
    SubscribeToEvent(E_MOUSEMOVE, HANDLER(UI, HandleMouseMove));
    SubscribeToEvent(E_MOUSEWHEEL, HANDLER(UI, HandleMouseWheel));
    SubscribeToEvent(E_TOUCHBEGIN, HANDLER(UI, HandleTouchBegin));
    SubscribeToEvent(E_TOUCHEND, HANDLER(UI, HandleTouchEnd));
    SubscribeToEvent(E_TOUCHMOVE, HANDLER(UI, HandleTouchMove));
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
    if (!rootElement_)
        return;
    
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
    if (!rootElement_)
        return;
    
    using namespace FocusChanged;
    
    VariantMap eventData;
    eventData[P_CLICKEDELEMENT] = (void*)element;
    
    if (element)
    {
        // Return if already has focus
        if (focusElement_ == element)
            return;
        
        // Search for an element in the hierarchy that can alter focus. If none found, exit
        element = GetFocusableElement(element);
        if (!element)
            return;
    }
    
    // Remove focus from the old element
    if (focusElement_)
    {
        UIElement* oldFocusElement = focusElement_;
        focusElement_.Reset();
        
        VariantMap focusEventData;
        focusEventData[Defocused::P_ELEMENT] = oldFocusElement;
        oldFocusElement->SendEvent(E_DEFOCUSED, focusEventData);
    }
    
    // Then set focus to the new
    if (element && element->GetFocusMode() >= FM_FOCUSABLE)
    {
        focusElement_ = element;
        
        VariantMap focusEventData;
        focusEventData[Focused::P_ELEMENT] = element;
        element->SendEvent(E_FOCUSED, focusEventData);
    }
    
    eventData[P_ELEMENT] = (void*)element;
    SendEvent(E_FOCUSCHANGED, eventData);
}

void UI::Clear()
{
    if (!rootElement_)
        return;
    
    rootElement_->RemoveAllChildren();
    if (cursor_)
        rootElement_->AddChild(cursor_);
}

void UI::Update(float timeStep)
{
    if (!rootElement_)
        return;
    
    PROFILE(UpdateUI);
    
    if (cursor_ && cursor_->IsVisible())
    {
        IntVector2 pos = cursor_->GetPosition();
        WeakPtr<UIElement> element(GetElementAt(pos));
        
        bool dragSource = dragElement_ && (dragElement_->GetDragDropMode() & DD_SOURCE) != 0;
        bool dragTarget = element && (element->GetDragDropMode() & DD_TARGET) != 0;
        bool dragDropTest = dragSource && dragTarget && element != dragElement_;
        
        // Hover effect
        // If a drag is going on, transmit hover only to the element being dragged, unless it's a drop target
        if (element)
        {
            if (!dragElement_ || dragElement_ == element || dragDropTest)
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
                eventData[P_SOURCE] = (void*)dragElement_.Get();
                eventData[P_TARGET] = (void*)element.Get();
                eventData[P_ACCEPT] = accept;
                SendEvent(E_DRAGDROPTEST, eventData);
                accept = eventData[P_ACCEPT].GetBool();
            }
            
            cursor_->SetShape(accept ? CS_ACCEPTDROP : CS_REJECTDROP);
        }
        else if (dragSource)
            cursor_->SetShape(dragElement_ == element ? CS_ACCEPTDROP : CS_REJECTDROP);
    }
    
    // Touch hover
    Input* input = GetSubsystem<Input>();
    if (input)
    {
        unsigned numTouches = input->GetNumTouches();
        for (unsigned i = 0; i < numTouches; ++i)
        {
            TouchState* touch = input->GetTouch(i);
            WeakPtr<UIElement> element(GetElementAt(touch->position_));
            if (element)
                element->OnHover(element->ScreenToElement(touch->position_), touch->position_, MOUSEB_LEFT, 0, 0);
        }
    }
    
    Update(timeStep, rootElement_);
}

void UI::RenderUpdate()
{
    if (!rootElement_ || !graphics_)
        return;
    
    PROFILE(GetUIBatches);
    
    // If the OS cursor is visible, do not render the UI's own cursor
    bool osCursorVisible = GetSubsystem<Input>()->IsMouseVisible();
    bool uiCursorVisible = false;
    if (osCursorVisible && cursor_)
    {
        uiCursorVisible = cursor_->IsVisible();
        cursor_->SetTempVisible(false);
    }
    
    // Get batches & quads from the UI elements
    batches_.Clear();
    quads_.Clear();
    const IntVector2& rootSize = rootElement_->GetSize();
    GetBatches(rootElement_, IntRect(0, 0, rootSize.x_, rootSize.y_));
    
    // If no drag, reset cursor shape for next frame
    if (cursor_ && !dragElement_)
        cursor_->SetShape(CS_NORMAL);
    
    // Restore UI cursor visibility state
    if (osCursorVisible && cursor_)
        cursor_->SetTempVisible(uiCursorVisible);
}

void UI::Render()
{
    PROFILE(RenderUI);
    
    if (!graphics_ || graphics_->IsDeviceLost() || !quads_.Size())
        return;
    
    // Update quad geometry into the vertex buffer
    unsigned numVertices = quads_.Size() * 6;
    // Resize the vertex buffer if too small or much too large
    if (vertexBuffer_->GetVertexCount() < numVertices || vertexBuffer_->GetVertexCount() > numVertices * 2)
        vertexBuffer_->SetSize(numVertices, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1, true);
    
    unsigned vertexSize = vertexBuffer_->GetVertexSize();
    void* dest = vertexBuffer_->Lock(0, numVertices, true);
    if (!dest)
        return;
    
    for (unsigned i = 0; i < batches_.Size(); ++i)
        batches_[i].UpdateGeometry(graphics_, ((unsigned char*)dest) + batches_[i].quadStart_ * vertexSize * 6);
    
    vertexBuffer_->Unlock();
    
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
    
    graphics_->ClearParameterSources();
    graphics_->SetCullMode(CULL_CCW);
    graphics_->SetDepthTest(CMP_ALWAYS);
    graphics_->SetDepthWrite(false);
    graphics_->SetStencilTest(false);
    graphics_->ResetRenderTargets();
    
    ShaderVariation* ps = 0;
    ShaderVariation* vs = 0;
    
    unsigned alphaFormat = Graphics::GetAlphaFormat();
    
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        const UIBatch& batch = batches_[i];
        if (!batch.quadCount_)
            continue;
        
        if (!batch.texture_)
        {
            ps = noTexturePS_;
            vs = noTextureVS_;
        }
        else
        {
            // If texture contains only an alpha channel, use alpha shader (for fonts)
            vs = diffTextureVS_;
            
            if (batch.texture_->GetFormat() == alphaFormat)
                ps = alphaTexturePS_;
            else if (batch.blendMode_ != BLEND_ALPHA && batch.blendMode_ != BLEND_ADDALPHA && batch.blendMode_ != BLEND_PREMULALPHA)
                ps = diffMaskTexturePS_;
            else
                ps = diffTexturePS_;
        }
        
        graphics_->SetShaders(vs, ps);
        if (graphics_->NeedParameterUpdate(SP_OBJECTTRANSFORM, this))
            graphics_->SetShaderParameter(VSP_MODEL, Matrix3x4::IDENTITY);
        if (graphics_->NeedParameterUpdate(SP_CAMERA, this))
            graphics_->SetShaderParameter(VSP_VIEWPROJ, projection);
        if (graphics_->NeedParameterUpdate(SP_MATERIAL, this))
            graphics_->SetShaderParameter(PSP_MATDIFFCOLOR, Color(1.0f, 1.0f, 1.0f, 1.0f));
        
        graphics_->SetBlendMode(batch.blendMode_);
        graphics_->SetScissorTest(true, batch.scissor_);
        graphics_->SetTexture(0, batch.texture_);
        graphics_->SetVertexBuffer(vertexBuffer_);
        graphics_->Draw(TRIANGLE_LIST, batch.quadStart_ * 6, batch.quadCount_ * 6);
    }
}

SharedPtr<UIElement> UI::LoadLayout(Deserializer& source, XMLFile* styleFile)
{
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    if (!xml->Load(source))
        return SharedPtr<UIElement>();
    else
        return LoadLayout(xml, styleFile);
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
    
    XMLElement rootElem = file->GetRoot("element");
    if (!rootElem)
    {
        LOGERROR("No root UI element in " + file->GetName());
        return root;
    }
    
    String typeName = rootElem.GetAttribute("type");
    if (typeName.Empty())
        typeName = "UIElement";
    
    root = DynamicCast<UIElement>(context_->CreateObject(ShortStringHash(typeName)));
    if (!root)
    {
        LOGERROR("Could not create unknown UI element " + typeName);
        return root;
    }
    
    root->LoadXML(rootElem, styleFile);
    return root;
}

bool UI::SaveLayout(Serializer& dest, UIElement* element)
{
    PROFILE(SaveUILayout);
    
    if (element)
        return element->SaveXML(dest);
    else
        return false;
}

void UI::SetClipBoardText(const String& text)
{
    clipBoard_ = text;
}

UIElement* UI::GetElementAt(const IntVector2& position, bool activeOnly)
{
    if (!rootElement_)
        return 0;
    
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
    return focusElement_;
}

UIElement* UI::GetFrontElement() const
{
    if (!rootElement_)
        return 0;
    
    const Vector<SharedPtr<UIElement> >& rootChildren = rootElement_->GetChildren();
    int maxPriority = M_MIN_INT;
    UIElement* front = 0;
    
    for (unsigned i = 0; i < rootChildren.Size(); ++i)
    {
        // Do not take into account input-disabled elements, hidden elements or those that are always in the front
        if (!rootChildren[i]->IsActive() || !rootChildren[i]->IsVisible() || !rootChildren[i]->GetBringToBack())
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
    Renderer* renderer = GetSubsystem<Renderer>();
    
    if (!graphics || !graphics->IsInitialized() || !renderer)
        return;
    
    PROFILE(InitUI);
    
    graphics_ = graphics;
    
    rootElement_ = new UIElement(context_);
    rootElement_->SetSize(graphics->GetWidth(), graphics->GetHeight());
    
    noTextureVS_ = renderer->GetVertexShader("Basic_VCol");
    diffTextureVS_ = renderer->GetVertexShader("Basic_DiffVCol");
    noTexturePS_ = renderer->GetPixelShader("Basic_VCol");
    diffTexturePS_ = renderer->GetPixelShader("Basic_DiffVCol");
    diffMaskTexturePS_ = renderer->GetPixelShader("Basic_DiffAlphaMaskVCol");
    alphaTexturePS_ = renderer->GetPixelShader("Basic_AlphaVCol");
    
    vertexBuffer_ = new VertexBuffer(context_);
    
    LOGINFO("Initialized user interface");
    initialized_ = true;
}

void UI::Update(float timeStep, UIElement* element)
{
    element->Update(timeStep);
    
    const Vector<SharedPtr<UIElement> >& children = element->GetChildren();
    for (Vector<SharedPtr<UIElement> >::ConstIterator i = children.Begin(); i != children.End(); ++i)
        Update(timeStep, *i);
}

void UI::GetBatches(UIElement* element, IntRect currentScissor)
{
    // Set clipping scissor for child elements. No need to draw if zero size
    element->AdjustScissor(currentScissor);
    if (currentScissor.left_ == currentScissor.right_ || currentScissor.top_ == currentScissor.bottom_)
        return;
    
    element->SortChildren();
    const Vector<SharedPtr<UIElement> >& children = element->GetChildren();
    if (children.Empty())
        return;
    
    // For non-root elements draw all children of same priority before recursing into their children: assumption is that they have
    // same renderstate
    Vector<SharedPtr<UIElement> >::ConstIterator i = children.Begin();
    if (element != rootElement_)
    {
        Vector<SharedPtr<UIElement> >::ConstIterator j = i;
        int currentPriority = children.Front()->GetPriority();
        while (i != children.End())
        {
            while (j != children.End() && (*j)->GetPriority() == currentPriority)
            {
                if (IsVisible(*j, currentScissor))
                    (*j)->GetBatches(batches_, quads_, currentScissor);
                ++j;
            }
            // Now recurse into the children
            while (i != j)
            {
                if (IsVisible(*i, currentScissor))
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
                if (IsVisible(*i, currentScissor))
                    (*i)->GetBatches(batches_, quads_, currentScissor);
                GetBatches(*i, currentScissor);
            }
            ++i;
        }
    }
}

bool UI::IsVisible(UIElement* element, const IntRect& currentScissor)
{
    // First check element's visibility
    if (!element->IsVisible())
        return false;

    // Then check element dimensions against the scissor rectangle
    const IntVector2& screenPos = element->GetScreenPosition();
    if (screenPos.x_ >= currentScissor.right_ || screenPos.x_ + element->GetWidth() <= currentScissor.left_ ||
        screenPos.y_ >= currentScissor.bottom_ || screenPos.y_ + element->GetHeight() <= currentScissor.top_)
        return false;
    else
        return true;
}

void UI::GetElementAt(UIElement*& result, UIElement* current, const IntVector2& position, bool activeOnly)
{
    if (!current)
        return;
    
    current->SortChildren();
    const Vector<SharedPtr<UIElement> >& children = current->GetChildren();
    LayoutMode parentLayoutMode = current->GetLayoutMode();
    
    for (Vector<SharedPtr<UIElement> >::ConstIterator i = children.Begin(); i != children.End(); ++i)
    {
        UIElement* element = *i;
        bool hasChildren = element->GetNumChildren() > 0;
        
        if (element != cursor_.Get() && element->IsVisible())
        {
            if (element->IsInside(position, true))
            {
                // Store the current result, then recurse into its children. Because children
                // are sorted from lowest to highest priority, the topmost match should remain
                if (element->IsActive() || !activeOnly)
                    result = element;
                
                if (hasChildren)
                    GetElementAt(result, element, position, activeOnly);
                // Layout optimization: if the element has no children, can break out after the first match
                else if (parentLayoutMode != LM_FREE)
                    break;
            }
            else
            {
                if (hasChildren)
                {
                    if (element->IsInsideCombined(position, true))
                        GetElementAt(result, element, position, activeOnly);
                }
                // Layout optimization: if position is much beyond the visible screen, check how many elements we can skip,
                // or if we already passed all visible elements
                else if (parentLayoutMode != LM_FREE)
                {
                    if (i == children.Begin())
                    {
                        int screenPos = (parentLayoutMode == LM_HORIZONTAL) ? element->GetScreenPosition().x_ :
                            element->GetScreenPosition().y_;
                        int layoutMinSize = current->GetLayoutMinSize();
                        
                        if (screenPos < 0 && layoutMinSize > 0)
                        {
                            unsigned toSkip = -screenPos / layoutMinSize;
                            if (toSkip > 0)
                            {
                                i += (toSkip - 1);
                                if (i >= children.End())
                                    break;
                            }
                        }
                    }
                    else if (parentLayoutMode == LM_HORIZONTAL)
                    {
                        if (element->GetScreenPosition().x_ >= rootElement_->GetSize().x_)
                            break;
                    }
                    else if (parentLayoutMode == LM_VERTICAL)
                    {
                        if (element->GetScreenPosition().y_ >= rootElement_->GetSize().y_)
                            break;
                    }
                }
            }
        }
    }
}

UIElement* UI::GetFocusableElement(UIElement* element)
{
    while (element)
    {
        if (element->GetFocusMode() != FM_NOTFOCUSABLE)
            break;
        element = element->GetParent();
    }
    return element;
}

void UI::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    using namespace ScreenMode;
    
    if (!initialized_)
        Initialize();
    else
        rootElement_->SetSize(eventData[P_WIDTH].GetInt(), eventData[P_HEIGHT].GetInt());
}

void UI::HandleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
    mouseButtons_ = eventData[MouseButtonDown::P_BUTTONS].GetInt();
    qualifiers_ = eventData[MouseButtonDown::P_QUALIFIERS].GetInt();
    int button = eventData[MouseButtonDown::P_BUTTON].GetInt();
    
    if (cursor_ && cursor_->IsVisible())
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
            if (element && !dragElement_ && mouseButtons_ == MOUSEB_LEFT)
            {
                dragElement_ = element;
                element->OnDragBegin(element->ScreenToElement(pos), pos, mouseButtons_, qualifiers_, cursor_);
            }
        }
        else
        {
            // If clicked over no element, or a disabled element, lose focus
            SetFocusElement(0);
        }
        
        using namespace UIMouseClick;
        
        VariantMap eventData;
        eventData[UIMouseClick::P_ELEMENT] = (void*)element.Get();
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
    
    if (cursor_ && (cursor_->IsVisible() || dragElement_))
    {
        IntVector2 pos = cursor_->GetPosition();
        
        if (dragElement_ && !mouseButtons_)
        {
            if (dragElement_->IsActive() && dragElement_->IsVisible())
            {
                dragElement_->OnDragEnd(dragElement_->ScreenToElement(pos), pos, cursor_);
                
                // Drag and drop finish
                bool dragSource = dragElement_ && (dragElement_->GetDragDropMode() & DD_SOURCE) != 0;
                if (dragSource)
                {
                    WeakPtr<UIElement> target(GetElementAt(pos));
                    bool dragTarget = target && (target->GetDragDropMode() & DD_TARGET) != 0;
                    bool dragDropFinish = dragSource && dragTarget && target != dragElement_;
                    
                    if (dragDropFinish)
                    {
                        bool accept = target->OnDragDropFinish(dragElement_);
                        
                        // OnDragDropFinish() may have caused destruction of the elements, so check the pointers again
                        if (accept && dragElement_ && target)
                        {
                            using namespace DragDropFinish;
                            
                            VariantMap eventData;
                            eventData[P_SOURCE] = (void*)dragElement_.Get();
                            eventData[P_TARGET] = (void*)target.Get();
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

void UI::HandleMouseMove(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseMove;
    
    mouseButtons_ = eventData[P_BUTTONS].GetInt();
    qualifiers_ = eventData[P_QUALIFIERS].GetInt();
    
    if (cursor_)
    {
        Input* input = GetSubsystem<Input>();
        const IntVector2& rootSize = rootElement_->GetSize();
        
        if (!input->IsMouseVisible())
        {
            // Relative mouse motion: move cursor only when visible
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
            // Absolute mouse motion: move always
            cursor_->SetPosition(IntVector2(eventData[P_X].GetInt(), eventData[P_Y].GetInt()));
        }
        
        if (dragElement_ && mouseButtons_)
        {
            IntVector2 pos = cursor_->GetPosition();
            if (dragElement_->IsActive() && dragElement_->IsVisible())
                dragElement_->OnDragMove(dragElement_->ScreenToElement(pos), pos, mouseButtons_, qualifiers_, cursor_);
            else
            {
                dragElement_->OnDragEnd(dragElement_->ScreenToElement(pos), pos, cursor_);
                dragElement_.Reset();
            }
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
    else
    {
        // If no element has actual focus, get the element at cursor
        if (cursor_)
        {
            IntVector2 pos = cursor_->GetPosition();
            UIElement* element = GetElementAt(pos);
            // If the element itself is not focusable, search for a focusable parent
            element = GetFocusableElement(element);
            if (element && element->GetFocusMode() >= FM_FOCUSABLE)
                element->OnWheel(delta, mouseButtons_, qualifiers_);
        }
    }
}


void UI::HandleTouchBegin(StringHash eventType, VariantMap& eventData)
{
    using namespace TouchBegin;
    
    IntVector2 pos(eventData[P_X].GetInt(), eventData[P_Y].GetInt());
    WeakPtr<UIElement> element(GetElementAt(pos));
    
    if (element)
    {
        // Handle focusing & bringing to front
        SetFocusElement(element);
        element->BringToFront();
        
        // Handle click
        element->OnClick(element->ScreenToElement(pos), pos, MOUSEB_LEFT, 0, 0);
        
        // Handle start of drag. OnClick() may have caused destruction of the element, so check the pointer again
        if (element && !dragElement_ )
        {
            dragElement_ = element;
            element->OnDragBegin(element->ScreenToElement(pos), pos, MOUSEB_LEFT, 0, 0);
        }
    }
    else
    {
        // If clicked over no element, or a disabled element, lose focus
        SetFocusElement(0);
    }
    
    using namespace UIMouseClick;
    
    VariantMap clickEventData;
    clickEventData[UIMouseClick::P_ELEMENT] = (void*)element.Get();
    clickEventData[UIMouseClick::P_X] = pos.x_;
    clickEventData[UIMouseClick::P_Y] = pos.y_;
    clickEventData[UIMouseClick::P_BUTTON] = MOUSEB_LEFT;
    clickEventData[UIMouseClick::P_BUTTONS] = MOUSEB_LEFT;
    clickEventData[UIMouseClick::P_QUALIFIERS] = 0;
    SendEvent(E_UIMOUSECLICK, clickEventData);
}

void UI::HandleTouchEnd(StringHash eventType, VariantMap& eventData)
{
    using namespace TouchEnd;
    
    IntVector2 pos(eventData[P_X].GetInt(), eventData[P_Y].GetInt());
    
    // Transmit hover end to the position where the finger was lifted
    WeakPtr<UIElement> element(GetElementAt(pos));
    if (element)
        element->OnHover(element->ScreenToElement(pos), pos, 0, 0, 0);
    
    if (dragElement_)
    {
        if (dragElement_->IsActive() && dragElement_->IsVisible())
        {
            dragElement_->OnDragEnd(dragElement_->ScreenToElement(pos), pos, cursor_);
            
            // Drag and drop finish
            bool dragSource = dragElement_ && (dragElement_->GetDragDropMode() & DD_SOURCE) != 0;
            if (dragSource)
            {
                WeakPtr<UIElement> target(GetElementAt(pos));
                bool dragTarget = target && (target->GetDragDropMode() & DD_TARGET) != 0;
                bool dragDropFinish = dragSource && dragTarget && target != dragElement_;
                
                if (dragDropFinish)
                {
                    bool accept = target->OnDragDropFinish(dragElement_);
                    
                    // OnDragDropFinish() may have caused destruction of the elements, so check the pointers again
                    if (accept && dragElement_ && target)
                    {
                        using namespace DragDropFinish;
                        
                        VariantMap eventData;
                        eventData[P_SOURCE] = (void*)dragElement_.Get();
                        eventData[P_TARGET] = (void*)target.Get();
                        eventData[P_ACCEPT] = accept;
                        SendEvent(E_DRAGDROPFINISH, eventData);
                    }
                }
            }
        }
        
        dragElement_.Reset();
    }
}

void UI::HandleTouchMove(StringHash eventType, VariantMap& eventData)
{
    using namespace TouchMove;
    
    IntVector2 pos(eventData[P_X].GetInt(), eventData[P_Y].GetInt());
    
    if (dragElement_)
    {
        if (dragElement_->IsActive() && dragElement_->IsVisible())
            dragElement_->OnDragMove(dragElement_->ScreenToElement(pos), pos, MOUSEB_LEFT, 0, 0);
        else
        {
            dragElement_->OnDragEnd(dragElement_->ScreenToElement(pos), pos, 0);
            dragElement_.Reset();
        }
    }
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
            while (topLevel && topLevel->GetParent() != rootElement_)
                topLevel = topLevel->GetParent();
            if (topLevel)
            {
                topLevel->GetChildren(tempElements_, true);
                for (PODVector<UIElement*>::Iterator i = tempElements_.Begin(); i != tempElements_.End();)
                {
                    if ((*i)->GetFocusMode() < FM_FOCUSABLE)
                        i = tempElements_.Erase(i);
                    else
                        ++i;
                }
                for (unsigned i = 0; i < tempElements_.Size(); ++i)
                {
                    if (tempElements_[i] == element)
                    {
                        UIElement* next = tempElements_[(i + 1) % tempElements_.Size()];
                        SetFocusElement(next);
                        return;
                    }
                }
            }
        }
        // Defocus the element
        else if (key == KEY_ESC && element->GetFocusMode() == FM_FOCUSABLE_DEFOCUSABLE)
            element->SetFocus(false);
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

}
