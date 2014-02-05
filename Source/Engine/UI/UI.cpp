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
#include "MessageBox.h"
#include "Profiler.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "ScrollBar.h"
#include "Shader.h"
#include "ShaderVariation.h"
#include "Slider.h"
#include "Sort.h"
#include "Sprite.h"
#include "Text.h"
#include "Text3D.h"
#include "Texture2D.h"
#include "ToolTip.h"
#include "UI.h"
#include "UIEvents.h"
#include "VertexBuffer.h"
#include "Window.h"
#include "View3D.h"

#include <SDL.h>

#include "DebugNew.h"

namespace Urho3D
{

ShortStringHash VAR_ORIGIN("Origin");
const ShortStringHash VAR_ORIGINAL_PARENT("OriginalParent");
const ShortStringHash VAR_ORIGINAL_CHILD_INDEX("OriginalChildIndex");
const ShortStringHash VAR_PARENT_CHANGED("ParentChanged");

const float DEFAULT_DOUBLECLICK_INTERVAL = 0.5f;
const float DEFAULT_DRAGBEGIN_INTERVAL = 0.5f;
const float DEFAULT_TOOLTIP_DELAY = 0.5f;
const int DEFAULT_DRAGBEGIN_DISTANCE = 5;
const int DEFAULT_FONT_TEXTURE_MAX_SIZE = 2048;

const char* UI_CATEGORY = "UI";

UI::UI(Context* context) :
    Object(context),
    rootElement_(new UIElement(context)),
    rootModalElement_(new UIElement(context)),
    mouseButtons_(0),
    lastMouseButtons_(0),
    qualifiers_(0),
    maxFontTextureSize_(DEFAULT_FONT_TEXTURE_MAX_SIZE),
    doubleClickInterval_(DEFAULT_DOUBLECLICK_INTERVAL),
    dragBeginInterval_(DEFAULT_DRAGBEGIN_INTERVAL),
    dragBeginDistance_(DEFAULT_DRAGBEGIN_DISTANCE),
    defaultToolTipDelay_(DEFAULT_TOOLTIP_DELAY),
    initialized_(false),
    usingTouchInput_(false),
    #ifdef WIN32
    nonFocusedMouseWheel_(false),    // Default MS Windows behaviour
    #else
    nonFocusedMouseWheel_(true),     // Default Mac OS X and Linux behaviour
    #endif
    useSystemClipBoard_(false),
    #if defined(ANDROID) || defined(IOS)
    useScreenKeyboard_(true),
    #else
    useScreenKeyboard_(false),
    #endif
    useMutableGlyphs_(false),
    forceAutoHint_(false),
    dragBeginPending_(false),
    nonModalBatchSize_(0)
{
    rootElement_->SetTraversalMode(TM_DEPTH_FIRST);
    rootModalElement_->SetTraversalMode(TM_DEPTH_FIRST);
    
    // Register UI library object factories
    RegisterUILibrary(context_);

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
    SubscribeToEvent(E_DROPFILE, HANDLER(UI, HandleDropFile));

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

void UI::SetFocusElement(UIElement* element, bool byKey)
{
    using namespace FocusChanged;

    UIElement* originalElement = element;

    if (element)
    {
        // Return if already has focus
        if (focusElement_ == element)
            return;

        // Only allow child elements of the modal element to receive focus
        if (HasModalElement())
        {
            UIElement* topLevel = element->GetParent();
            while (topLevel && topLevel->GetParent() != rootElement_)
                topLevel = topLevel->GetParent();
            if (topLevel)   // If parented to non-modal root then ignore
                return;
        }

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

        VariantMap& focusEventData = GetEventDataMap();
        focusEventData[Defocused::P_ELEMENT] = oldFocusElement;
        oldFocusElement->SendEvent(E_DEFOCUSED, focusEventData);
    }

    // Then set focus to the new
    if (element && element->GetFocusMode() >= FM_FOCUSABLE)
    {
        focusElement_ = element;

        VariantMap& focusEventData = GetEventDataMap();
        focusEventData[Focused::P_ELEMENT] = element;
        focusEventData[Focused::P_BYKEY] = byKey;
        element->SendEvent(E_FOCUSED, focusEventData);
    }

    VariantMap& eventData = GetEventDataMap();
    eventData[P_CLICKEDELEMENT] = (void*)originalElement;
    eventData[P_ELEMENT] = (void*)element;
    SendEvent(E_FOCUSCHANGED, eventData);
}

bool UI::SetModalElement(UIElement* modalElement, bool enable)
{
    if (!modalElement)
        return false;

    // Currently only allow modal window
    if (modalElement->GetType() != Window::GetTypeStatic())
        return false;

    assert(rootModalElement_);
    UIElement* currParent = modalElement->GetParent();
    if (enable)
    {
        // Make sure it is not already the child of the root modal element
        if (currParent == rootModalElement_)
            return false;

        // Adopt modal root as parent
        modalElement->SetVar(VAR_ORIGINAL_PARENT, currParent);
        modalElement->SetVar(VAR_ORIGINAL_CHILD_INDEX, currParent ? currParent->FindChild(modalElement) : M_MAX_UNSIGNED);
        modalElement->SetParent(rootModalElement_);

        // If it is a popup element, bring along its top-level parent
        UIElement* originElement = static_cast<UIElement*>(modalElement->GetVar(VAR_ORIGIN).GetPtr());
        if (originElement)
        {
            UIElement* element = originElement;
            while (element && element->GetParent() != rootElement_)
                element = element->GetParent();
            if (element)
            {
                originElement->SetVar(VAR_PARENT_CHANGED, element);
                UIElement* oriParent = element->GetParent();
                element->SetVar(VAR_ORIGINAL_PARENT, oriParent);
                element->SetVar(VAR_ORIGINAL_CHILD_INDEX, oriParent ? oriParent->FindChild(element) : M_MAX_UNSIGNED);
                element->SetParent(rootModalElement_);
            }
        }

        return true;
    }
    else
    {
        // Only the modal element can disable itself
        if (currParent != rootModalElement_)
            return false;

        // Revert back to original parent
        modalElement->SetParent(static_cast<UIElement*>(modalElement->GetVar(VAR_ORIGINAL_PARENT).GetPtr()), modalElement->GetVar(VAR_ORIGINAL_CHILD_INDEX).GetUInt());
        VariantMap& vars = const_cast<VariantMap&>(modalElement->GetVars());
        vars.Erase(VAR_ORIGINAL_PARENT);
        vars.Erase(VAR_ORIGINAL_CHILD_INDEX);

        // If it is a popup element, revert back its top-level parent
        UIElement* originElement = static_cast<UIElement*>(modalElement->GetVar(VAR_ORIGIN).GetPtr());
        if (originElement)
        {
            UIElement* element = static_cast<UIElement*>(originElement->GetVar(VAR_PARENT_CHANGED).GetPtr());
            if (element)
            {
                const_cast<VariantMap&>(originElement->GetVars()).Erase(VAR_PARENT_CHANGED);
                element->SetParent(static_cast<UIElement*>(element->GetVar(VAR_ORIGINAL_PARENT).GetPtr()), element->GetVar(VAR_ORIGINAL_CHILD_INDEX).GetUInt());
                vars = const_cast<VariantMap&>(element->GetVars());
                vars.Erase(VAR_ORIGINAL_PARENT);
                vars.Erase(VAR_ORIGINAL_CHILD_INDEX);
            }
        }

        return true;
    }
}

void UI::Clear()
{
    rootElement_->RemoveAllChildren();
    rootModalElement_->RemoveAllChildren();
    if (cursor_)
        rootElement_->AddChild(cursor_);
}

void UI::Update(float timeStep)
{
    assert(rootElement_ && rootModalElement_);

    PROFILE(UpdateUI);

    IntVector2 cursorPos;
    bool cursorVisible;
    GetCursorPositionAndVisible(cursorPos, cursorVisible);

    // Drag begin based on time
    if (dragElement_ && dragBeginPending_)
    {
        if (dragBeginTimer_.GetMSec(false) >= (unsigned)(dragBeginInterval_ * 1000))
        {
            dragBeginPending_ = false;
            if (!usingTouchInput_)
            {
                dragElement_->OnDragBegin(dragElement_->ScreenToElement(dragBeginPos_), dragBeginPos_, mouseButtons_, qualifiers_,
                    cursor_);
            }
            else
                dragElement_->OnDragBegin(dragElement_->ScreenToElement(dragBeginPos_), dragBeginPos_, MOUSEB_LEFT, 0, 0);
            SendDragEvent(E_DRAGBEGIN, dragElement_, dragBeginPos_);
        }
    }
    
    // Mouse hover
    if (!usingTouchInput_ && cursorVisible)
        ProcessHover(cursorPos, mouseButtons_, qualifiers_, cursor_);
    
    // Touch hover
    Input* input = GetSubsystem<Input>();
    unsigned numTouches = input->GetNumTouches();
    for (unsigned i = 0; i < numTouches; ++i)
    {
        TouchState* touch = input->GetTouch(i);
        ProcessHover(touch->position_, MOUSEB_LEFT, 0, 0);
    }
    
    Update(timeStep, rootElement_);
    Update(timeStep, rootModalElement_);
}

void UI::RenderUpdate()
{
    assert(rootElement_ && rootModalElement_ && graphics_);

    PROFILE(GetUIBatches);

    // If the OS cursor is visible, do not render the UI's own cursor
    bool osCursorVisible = GetSubsystem<Input>()->IsMouseVisible();
    
    // Get rendering batches from the non-modal UI elements
    batches_.Clear();
    vertexData_.Clear();
    const IntVector2& rootSize = rootElement_->GetSize();
    IntRect currentScissor = IntRect(0, 0, rootSize.x_, rootSize.y_);
    GetBatches(rootElement_, currentScissor);

    // Save the batch size of the non-modal batches for later use
    nonModalBatchSize_ = batches_.Size();

    // Get rendering batches from the modal UI elements
    GetBatches(rootModalElement_, currentScissor);

    // Get batches from the cursor (and its possible children) last to draw it on top of everything
    if (cursor_ && cursor_->IsVisible() && !osCursorVisible)
    {
        currentScissor = IntRect(0, 0, rootSize.x_, rootSize.y_);
        cursor_->GetBatches(batches_, vertexData_, currentScissor);
        GetBatches(cursor_, currentScissor);
    }
}

void UI::Render()
{
    PROFILE(RenderUI);

    // If the OS cursor is visible, apply its shape now if changed
    bool osCursorVisible = GetSubsystem<Input>()->IsMouseVisible();
    if (cursor_ && osCursorVisible)
        cursor_->ApplyOSCursorShape();
    
    SetVertexData(vertexBuffer_, vertexData_);
    SetVertexData(debugVertexBuffer_, debugVertexData_);

    // Render non-modal batches
    Render(vertexBuffer_, batches_, 0, nonModalBatchSize_);
    // Render debug draw
    Render(debugVertexBuffer_, debugDrawBatches_, 0, debugDrawBatches_.Size());
    // Render modal batches
    Render(vertexBuffer_, batches_, nonModalBatchSize_, batches_.Size());

    // Clear the debug draw batches and data
    debugDrawBatches_.Clear();
    debugVertexData_.Clear();
}

void UI::DebugDraw(UIElement* element)
{
    if (element)
    {
        const IntVector2& rootSize = rootElement_->GetSize();
        element->GetDebugDrawBatches(debugDrawBatches_, debugVertexData_, IntRect(0, 0, rootSize.x_, rootSize.y_));
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

    root = DynamicCast<UIElement>(context_->CreateObject(typeName));
    if (!root)
    {
        LOGERROR("Could not create unknown UI element " + typeName);
        return root;
    }

    // Use default style file of the root element if it has one
    if (!styleFile)
        styleFile = rootElement_->GetDefaultStyle(false);
    // Set it as default for later use by children elements
    if (styleFile)
        root->SetDefaultStyle(styleFile);

    root->LoadXML(rootElem, styleFile);
    return root;
}

bool UI::SaveLayout(Serializer& dest, UIElement* element)
{
    PROFILE(SaveUILayout);

    return element && element->SaveXML(dest);
}

void UI::SetClipBoardText(const String& text)
{
    clipBoard_ = text;
    if (useSystemClipBoard_)
        SDL_SetClipboardText(text.CString());
}

void UI::SetDoubleClickInterval(float interval)
{
    doubleClickInterval_ = Max(interval, 0.0f);
}

void UI::SetDragBeginInterval(float interval)
{
    dragBeginInterval_ = Max(interval, 0.0f);
}

void UI::SetDragBeginDistance(int pixels)
{
    dragBeginDistance_ = Max(pixels, 0);
}

void UI::SetDefaultToolTipDelay(float delay)
{
    defaultToolTipDelay_ = Max(delay, 0.0f);
}

void UI::SetMaxFontTextureSize(int size)
{
    if (IsPowerOfTwo(size) && size >= FONT_TEXTURE_MIN_SIZE)
    {
        if (size != maxFontTextureSize_)
        {
            maxFontTextureSize_ = size;
            ReleaseFontFaces();
        }
    }
}

void UI::SetNonFocusedMouseWheel(bool nonFocusedMouseWheel)
{
    nonFocusedMouseWheel_ = nonFocusedMouseWheel;
}

void UI::SetUseSystemClipBoard(bool enable)
{
    useSystemClipBoard_ = enable;
}

void UI::SetUseScreenKeyboard(bool enable)
{
    useScreenKeyboard_ = enable;
}

void UI::SetUseMutableGlyphs(bool enable)
{
    if (enable != useMutableGlyphs_)
    {
        useMutableGlyphs_ = enable;
        ReleaseFontFaces();
    }
}

void UI::SetForceAutoHint(bool enable)
{
    if (enable != forceAutoHint_)
    {
        forceAutoHint_ = enable;
        ReleaseFontFaces();
    }
}

IntVector2 UI::GetCursorPosition() const
{
    return cursor_ ? cursor_->GetPosition() : GetSubsystem<Input>()->GetMousePosition();
}

UIElement* UI::GetElementAt(const IntVector2& position, bool enabledOnly)
{
    UIElement* result = 0;
    GetElementAt(result, HasModalElement() ? rootModalElement_ : rootElement_, position, enabledOnly);
    return result;
}

UIElement* UI::GetElementAt(int x, int y, bool enabledOnly)
{
    return GetElementAt(IntVector2(x, y), enabledOnly);
}

UIElement* UI::GetFrontElement() const
{
    const Vector<SharedPtr<UIElement> >& rootChildren = rootElement_->GetChildren();
    int maxPriority = M_MIN_INT;
    UIElement* front = 0;

    for (unsigned i = 0; i < rootChildren.Size(); ++i)
    {
        // Do not take into account input-disabled elements, hidden elements or those that are always in the front
        if (!rootChildren[i]->IsEnabled() || !rootChildren[i]->IsVisible() || !rootChildren[i]->GetBringToBack())
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

UIElement* UI::GetDragElement() const
{
    // Do not return the element until drag begin event has actually been posted
    return dragBeginPending_ ? (UIElement*)0 : dragElement_;
}

const String& UI::GetClipBoardText() const
{
    if (useSystemClipBoard_)
    {
        char* text = SDL_GetClipboardText();
        clipBoard_ = String(text);
        if (text)
            SDL_free(text);
    }
    
    return clipBoard_;
}

bool UI::HasModalElement() const
{
    return rootModalElement_->GetNumChildren() > 0;
}

void UI::Initialize()
{
    Graphics* graphics = GetSubsystem<Graphics>();

    if (!graphics || !graphics->IsInitialized())
        return;

    PROFILE(InitUI);

    graphics_ = graphics;

    rootElement_->SetSize(graphics->GetWidth(), graphics->GetHeight());
    rootModalElement_->SetSize(rootElement_->GetSize());

    vertexBuffer_ = new VertexBuffer(context_);
    debugVertexBuffer_ = new VertexBuffer(context_);

    initialized_ = true;

    SubscribeToEvent(E_BEGINFRAME, HANDLER(UI, HandleBeginFrame));
    SubscribeToEvent(E_POSTUPDATE, HANDLER(UI, HandlePostUpdate));
    SubscribeToEvent(E_RENDERUPDATE, HANDLER(UI, HandleRenderUpdate));

    LOGINFO("Initialized user interface");
}

void UI::Update(float timeStep, UIElement* element)
{
    // Keep a weak pointer to the element in case it destroys itself on update
    WeakPtr<UIElement> elementWeak(element);

    element->Update(timeStep);
    if (elementWeak.Expired())
        return;

    const Vector<SharedPtr<UIElement> >& children = element->GetChildren();
    // Update of an element may modify its child vector. Use just index-based iteration to be safe
    for (unsigned i = 0; i < children.Size(); ++i)
        Update(timeStep, children[i]);
}

void UI::SetVertexData(VertexBuffer* dest, const PODVector<float>& vertexData)
{
    if (vertexData.Empty())
        return;

    // Update quad geometry into the vertex buffer
    // Resize the vertex buffer first if too small or much too large
    unsigned numVertices = vertexData.Size() / UI_VERTEX_SIZE;
    if (dest->GetVertexCount() < numVertices || dest->GetVertexCount() > numVertices * 2)
        dest->SetSize(numVertices, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1, true);

    dest->SetData(&vertexData[0]);
}

void UI::Render(VertexBuffer* buffer, const PODVector<UIBatch>& batches, unsigned batchStart, unsigned batchEnd)
{
    // Engine does not render when window is closed or device is lost
    assert(graphics_ && graphics_->IsInitialized() && !graphics_->IsDeviceLost());

    Renderer* renderer = GetSubsystem<Renderer>();
    if (!renderer || batches.Empty())
        return;

    Vector2 invScreenSize(1.0f / (float)graphics_->GetWidth(), 1.0f / (float)graphics_->GetHeight());
    Vector2 scale(2.0f * invScreenSize.x_, -2.0f * invScreenSize.y_);
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
    graphics_->SetVertexBuffer(buffer);

    ShaderVariation* noTextureVS = renderer->GetShader(VS, "Basic", "VERTEXCOLOR");
    ShaderVariation* diffTextureVS = renderer->GetShader(VS, "Basic", "DIFFMAP VERTEXCOLOR");
    ShaderVariation* noTexturePS = renderer->GetShader(PS, "Basic", "VERTEXCOLOR");
    ShaderVariation* diffTexturePS = renderer->GetShader(PS, "Basic", "DIFFMAP VERTEXCOLOR");
    ShaderVariation* diffMaskTexturePS = renderer->GetShader(PS, "Basic", "DIFFMAP ALPHAMASK VERTEXCOLOR");
    ShaderVariation* alphaTexturePS = renderer->GetShader(PS, "Basic", "ALPHAMAP VERTEXCOLOR");

    unsigned alphaFormat = Graphics::GetAlphaFormat();

    for (unsigned i = batchStart; i < batchEnd; ++i)
    {
        const UIBatch& batch = batches[i];
        if (batch.vertexStart_ == batch.vertexEnd_)
            continue;

        ShaderVariation* ps;
        ShaderVariation* vs;

        if (!batch.texture_)
        {
            ps = noTexturePS;
            vs = noTextureVS;
        }
        else
        {
            // If texture contains only an alpha channel, use alpha shader (for fonts)
            vs = diffTextureVS;

            if (batch.texture_->GetFormat() == alphaFormat)
                ps = alphaTexturePS;
            else if (batch.blendMode_ != BLEND_ALPHA && batch.blendMode_ != BLEND_ADDALPHA && batch.blendMode_ != BLEND_PREMULALPHA)
                ps = diffMaskTexturePS;
            else
                ps = diffTexturePS;
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
        graphics_->Draw(TRIANGLE_LIST, batch.vertexStart_ / UI_VERTEX_SIZE, (batch.vertexEnd_ - batch.vertexStart_) /
            UI_VERTEX_SIZE);
    }
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
    if (element->GetTraversalMode() == TM_BREADTH_FIRST)
    {
        Vector<SharedPtr<UIElement> >::ConstIterator j = i;
        while (i != children.End())
        {
            int currentPriority = (*i)->GetPriority();
            while (j != children.End() && (*j)->GetPriority() == currentPriority)
            {
                if ((*j)->IsWithinScissor(currentScissor) && (*j) != cursor_)
                    (*j)->GetBatches(batches_, vertexData_, currentScissor);
                ++j;
            }
            // Now recurse into the children
            while (i != j)
            {
                if ((*i)->IsVisible() && (*i) != cursor_)
                    GetBatches(*i, currentScissor);
                ++i;
            }
        }
    }
    // On the root level draw each element and its children immediately after to avoid artifacts
    else
    {
        while (i != children.End())
        {
            if ((*i) != cursor_)
            {
                if ((*i)->IsWithinScissor(currentScissor))
                    (*i)->GetBatches(batches_, vertexData_, currentScissor);
                if ((*i)->IsVisible())
                    GetBatches(*i, currentScissor);
            }
            ++i;
        }
    }
}

void UI::GetElementAt(UIElement*& result, UIElement* current, const IntVector2& position, bool enabledOnly)
{
    if (!current)
        return;

    current->SortChildren();
    const Vector<SharedPtr<UIElement> >& children = current->GetChildren();
    LayoutMode parentLayoutMode = current->GetLayoutMode();

    for (unsigned i = 0; i < children.Size(); ++i)
    {
        UIElement* element = children[i];
        bool hasChildren = element->GetNumChildren() > 0;

        if (element != cursor_.Get() && element->IsVisible())
        {
            if (element->IsInside(position, true))
            {
                // Store the current result, then recurse into its children. Because children
                // are sorted from lowest to highest priority, the topmost match should remain
                if (element->IsEnabled() || !enabledOnly)
                    result = element;

                if (hasChildren)
                    GetElementAt(result, element, position, enabledOnly);
                // Layout optimization: if the element has no children, can break out after the first match
                else if (parentLayoutMode != LM_FREE)
                    break;
            }
            else
            {
                if (hasChildren)
                {
                    if (element->IsInsideCombined(position, true))
                        GetElementAt(result, element, position, enabledOnly);
                }
                // Layout optimization: if position is much beyond the visible screen, check how many elements we can skip,
                // or if we already passed all visible elements
                else if (parentLayoutMode != LM_FREE)
                {
                    if (!i)
                    {
                        int screenPos = (parentLayoutMode == LM_HORIZONTAL) ? element->GetScreenPosition().x_ :
                            element->GetScreenPosition().y_;
                        int layoutMinSize = current->GetLayoutMinSize();

                        if (screenPos < 0 && layoutMinSize > 0)
                        {
                            unsigned toSkip = -screenPos / layoutMinSize;
                            if (toSkip > 0)
                                i += (toSkip - 1);
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

void UI::GetCursorPositionAndVisible(IntVector2& pos, bool& visible)
{
    if (cursor_)
    {
        pos = cursor_->GetPosition();
        visible = cursor_->IsVisible();
    }
    else
    {
        Input* input = GetSubsystem<Input>();
        pos = input->GetMousePosition();
        visible = input->IsMouseVisible();
    }
}

void UI::SetCursorShape(CursorShape shape)
{
    if (cursor_)
        cursor_->SetShape(shape);
}

void UI::ReleaseFontFaces()
{
    LOGDEBUG("Reloading font faces");

    PODVector<Font*> fonts;
    GetSubsystem<ResourceCache>()->GetResources<Font>(fonts);

    for (unsigned i = 0; i < fonts.Size(); ++i)
        fonts[i]->ReleaseFaces();
}

void UI::ProcessHover(const IntVector2& cursorPos, int buttons, int qualifiers, Cursor* cursor)
{
    WeakPtr<UIElement> element(GetElementAt(cursorPos));

    bool dragSource = dragElement_ && (dragElement_->GetDragDropMode() & DD_SOURCE) != 0;
    bool dragTarget = element && (element->GetDragDropMode() & DD_TARGET) != 0;
    bool dragDropTest = dragSource && dragTarget && element != dragElement_;
    // If drag start event has not been posted yet, do not do drag handling here
    if (dragBeginPending_)
        dragSource = dragTarget = dragDropTest = false;

    // Hover effect
    // If a drag is going on, transmit hover only to the element being dragged, unless it's a drop target
    if (element && element->IsEnabled())
    {
        if (!dragElement_ || dragElement_ == element || dragDropTest)
            element->OnHover(element->ScreenToElement(cursorPos), cursorPos, buttons, qualifiers, cursor);
    }

    // Drag and drop test
    if (dragDropTest)
    {
        bool accept = element->OnDragDropTest(dragElement_);
        if (accept)
        {
            using namespace DragDropTest;

            VariantMap& eventData = GetEventDataMap();
            eventData[P_SOURCE] = (void*)dragElement_.Get();
            eventData[P_TARGET] = (void*)element.Get();
            eventData[P_ACCEPT] = accept;
            SendEvent(E_DRAGDROPTEST, eventData);
            accept = eventData[P_ACCEPT].GetBool();
        }

        if (cursor)
            cursor->SetShape(accept ? CS_ACCEPTDROP : CS_REJECTDROP);
    }
    else if (dragSource && cursor)
        cursor->SetShape(dragElement_ == element ? CS_ACCEPTDROP : CS_REJECTDROP);
}

void UI::ProcessClickBegin(const IntVector2& cursorPos, int button, int buttons, int qualifiers, Cursor* cursor, bool cursorVisible)
{
    if (cursorVisible)
    {
        WeakPtr<UIElement> element(GetElementAt(cursorPos));

        if (element)
        {
            // Handle focusing & bringing to front
            if (button == MOUSEB_LEFT)
            {
                SetFocusElement(element);
                element->BringToFront();
            }

            // Handle click
            element->OnClickBegin(element->ScreenToElement(cursorPos), cursorPos, button, buttons, qualifiers, cursor);
            SendClickEvent(E_UIMOUSECLICK, element, cursorPos, button, buttons, qualifiers);

            // Remember element clicked on for the click end
            clickElement_ = element;
            
            // Fire double click event if element matches and is in time
            if (doubleClickElement_ && element == doubleClickElement_ && clickTimer_.GetMSec(true) <
                (unsigned)(doubleClickInterval_ * 1000) && lastMouseButtons_ == buttons)
            {
                element->OnDoubleClick(element->ScreenToElement(cursorPos), cursorPos, button, buttons, qualifiers, cursor);
                doubleClickElement_.Reset();
                SendClickEvent(E_UIMOUSEDOUBLECLICK, element, cursorPos, button, buttons, qualifiers);
            }
            else
            {
                doubleClickElement_ = element;
                clickTimer_.Reset();
            }
            
            // Handle start of drag. Click handling may have caused destruction of the element, so check the pointer again
            if (element && !dragElement_ && buttons == MOUSEB_LEFT)
            {
                dragElement_ = element;
                dragBeginPending_ = true;
                dragBeginPos_ = cursorPos;
                dragBeginTimer_.Reset();
            }
        }
        else
        {
            // If clicked over no element, or a disabled element, lose focus
            SetFocusElement(0);
            SendClickEvent(E_UIMOUSECLICK, element, cursorPos, button, buttons, qualifiers);
        }
        
        lastMouseButtons_ = buttons;
    }
}

void UI::ProcessClickEnd(const IntVector2& cursorPos, int button, int buttons, int qualifiers, Cursor* cursor, bool cursorVisible)
{
    if (cursorVisible)
    {
        WeakPtr<UIElement> element(GetElementAt(cursorPos));

        // Handle end of click
        if (element)
            element->OnClickEnd(element->ScreenToElement(cursorPos), cursorPos, button, buttons, qualifiers, cursor, clickElement_);
        
        SendClickEvent(E_UIMOUSECLICKEND, element, cursorPos, button, buttons, qualifiers);
        
        // Handle end of drag
        if (dragElement_ && !buttons)
        {
            if (dragElement_->IsEnabled() && dragElement_->IsVisible() && !dragBeginPending_)
            {
                dragElement_->OnDragEnd(dragElement_->ScreenToElement(cursorPos), cursorPos, cursor);
                SendDragEvent(E_DRAGEND, dragElement_, cursorPos);

                bool dragSource = dragElement_ && (dragElement_->GetDragDropMode() & DD_SOURCE) != 0;
                if (dragSource)
                {
                    bool dragTarget = element && (element->GetDragDropMode() & DD_TARGET) != 0;
                    bool dragDropFinish = dragSource && dragTarget && element != dragElement_;

                    if (dragDropFinish)
                    {
                        bool accept = element->OnDragDropFinish(dragElement_);

                        // OnDragDropFinish() may have caused destruction of the elements, so check the pointers again
                        if (accept && dragElement_ && element)
                        {
                            using namespace DragDropFinish;

                            VariantMap& eventData = GetEventDataMap();
                            eventData[P_SOURCE] = (void*)dragElement_.Get();
                            eventData[P_TARGET] = (void*)element.Get();
                            eventData[P_ACCEPT] = accept;
                            SendEvent(E_DRAGDROPFINISH, eventData);
                        }
                    }
                }
            }

            dragElement_.Reset();
            dragBeginPending_ = false;
        }
        
        clickElement_.Reset();
    }
}

void UI::ProcessMove(const IntVector2& cursorPos, int buttons, int qualifiers, Cursor* cursor, bool cursorVisible)
{
    if (cursorVisible && dragElement_ && buttons)
    {
        if (dragElement_->IsEnabled() && dragElement_->IsVisible())
        {
            // Signal drag begin if distance threshold was exceeded
            if (dragBeginPending_)
            {
                IntVector2 offset = cursorPos - dragBeginPos_;
                if (Abs(offset.x_) >= dragBeginDistance_ || Abs(offset.y_) >= dragBeginDistance_)
                {
                    dragBeginPending_ = false;
                    dragElement_->OnDragBegin(dragElement_->ScreenToElement(dragBeginPos_), dragBeginPos_, buttons, qualifiers, cursor);
                    SendDragEvent(E_DRAGBEGIN, dragElement_, dragBeginPos_);
                }
            }
            
            if (!dragBeginPending_)
            {
                dragElement_->OnDragMove(dragElement_->ScreenToElement(cursorPos), cursorPos, buttons, qualifiers, cursor);
                SendDragEvent(E_DRAGMOVE, dragElement_, cursorPos);
            }
        }
        else
        {
            dragElement_->OnDragEnd(dragElement_->ScreenToElement(cursorPos), cursorPos, cursor);
            SendDragEvent(E_DRAGEND, dragElement_, cursorPos);
            dragElement_.Reset();
        }
    }
}

void UI::SendDragEvent(StringHash eventType, UIElement* element, const IntVector2& screenPos)
{
    if (!element)
        return;

    IntVector2 relativePos = element->ScreenToElement(screenPos);

    using namespace DragBegin;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_ELEMENT] = (void*)element;
    eventData[P_X] = screenPos.x_;
    eventData[P_Y] = screenPos.y_;
    eventData[P_ELEMENTX] = relativePos.x_;
    eventData[P_ELEMENTY] = relativePos.y_;

    element->SendEvent(eventType, eventData);
}

void UI::SendClickEvent(StringHash eventType, UIElement* element, const IntVector2& pos, int button, int buttons, int qualifiers)
{
    VariantMap& eventData = GetEventDataMap();
    eventData[UIMouseClick::P_ELEMENT] = (void*)element;
    eventData[UIMouseClick::P_X] = pos.x_;
    eventData[UIMouseClick::P_Y] = pos.y_;
    eventData[UIMouseClick::P_BUTTON] = button;
    eventData[UIMouseClick::P_BUTTONS] = buttons;
    eventData[UIMouseClick::P_QUALIFIERS] = qualifiers;
    
    // For click end events, send also the element the click began on
    if (eventType == E_UIMOUSECLICKEND)
        eventData[UIMouseClickEnd::P_BEGINELEMENT] = clickElement_;
    
    SendEvent(eventType, eventData);
}

void UI::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    using namespace ScreenMode;

    if (!initialized_)
        Initialize();
    else
    {
        rootElement_->SetSize(eventData[P_WIDTH].GetInt(), eventData[P_HEIGHT].GetInt());
        rootModalElement_->SetSize(rootElement_->GetSize());
    }
}

void UI::HandleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
    mouseButtons_ = eventData[MouseButtonDown::P_BUTTONS].GetInt();
    qualifiers_ = eventData[MouseButtonDown::P_QUALIFIERS].GetInt();
    usingTouchInput_ = false;

    IntVector2 cursorPos;
    bool cursorVisible;
    GetCursorPositionAndVisible(cursorPos, cursorVisible);

    ProcessClickBegin(cursorPos, eventData[MouseButtonDown::P_BUTTON].GetInt(), mouseButtons_, qualifiers_, cursor_,
        cursorVisible);
}

void UI::HandleMouseButtonUp(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseButtonUp;

    mouseButtons_ = eventData[P_BUTTONS].GetInt();
    qualifiers_ = eventData[P_QUALIFIERS].GetInt();

    IntVector2 cursorPos;
    bool cursorVisible;
    GetCursorPositionAndVisible(cursorPos, cursorVisible);

    ProcessClickEnd(cursorPos, eventData[P_BUTTON].GetInt(), mouseButtons_, qualifiers_, cursor_, cursorVisible);
}

void UI::HandleMouseMove(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseMove;

    mouseButtons_ = eventData[P_BUTTONS].GetInt();
    qualifiers_ = eventData[P_QUALIFIERS].GetInt();
    usingTouchInput_ = false;

    Input* input = GetSubsystem<Input>();
    const IntVector2& rootSize = rootElement_->GetSize();

    if (cursor_)
    {
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
    }

    IntVector2 cursorPos;
    bool cursorVisible;
    GetCursorPositionAndVisible(cursorPos, cursorVisible);

    ProcessMove(cursorPos, mouseButtons_, qualifiers_, cursor_, cursorVisible);
}

void UI::HandleMouseWheel(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseWheel;

    mouseButtons_ = eventData[P_BUTTONS].GetInt();
    qualifiers_ = eventData[P_QUALIFIERS].GetInt();
    int delta = eventData[P_WHEEL].GetInt();
    usingTouchInput_ = false;

    IntVector2 cursorPos;
    bool cursorVisible;
    GetCursorPositionAndVisible(cursorPos, cursorVisible);

    UIElement* element;
    if (!nonFocusedMouseWheel_&& (element = focusElement_))
        element->OnWheel(delta, mouseButtons_, qualifiers_);
    else
    {
        // If no element has actual focus or in non-focused mode, get the element at cursor
        if (cursorVisible)
        {
            element = GetElementAt(cursorPos);
            if (nonFocusedMouseWheel_)
            {
                // Going up the hierarchy chain to find element that could handle mouse wheel
                while (element)
                {
                    if (element->GetType() == ListView::GetTypeStatic() ||
                        element->GetType() == ScrollView::GetTypeStatic())
                        break;
                    element = element->GetParent();
                }
            }
            else
                // If the element itself is not focusable, search for a focusable parent,
                // although the focusable element may not actually handle mouse wheel
                element = GetFocusableElement(element);

            if (element && (nonFocusedMouseWheel_ || element->GetFocusMode() >= FM_FOCUSABLE))
                element->OnWheel(delta, mouseButtons_, qualifiers_);
        }
    }
}

void UI::HandleTouchBegin(StringHash eventType, VariantMap& eventData)
{
    using namespace TouchBegin;

    IntVector2 pos(eventData[P_X].GetInt(), eventData[P_Y].GetInt());
    WeakPtr<UIElement> element(GetElementAt(pos));
    usingTouchInput_ = true;

    ProcessClickBegin(pos, MOUSEB_LEFT, MOUSEB_LEFT, 0, 0, true);
}

void UI::HandleTouchEnd(StringHash eventType, VariantMap& eventData)
{
    using namespace TouchEnd;

    IntVector2 pos(eventData[P_X].GetInt(), eventData[P_Y].GetInt());

    // Transmit hover end to the position where the finger was lifted
    UIElement* element = GetElementAt(pos);
    if (element && element->IsEnabled())
        element->OnHover(element->ScreenToElement(pos), pos, 0, 0, 0);

    ProcessClickEnd(pos, MOUSEB_LEFT, 0, 0, 0, true);
}

void UI::HandleTouchMove(StringHash eventType, VariantMap& eventData)
{
    using namespace TouchMove;

    IntVector2 pos(eventData[P_X].GetInt(), eventData[P_Y].GetInt());
    usingTouchInput_ = true;

    ProcessMove(pos, MOUSEB_LEFT, 0, 0, true);
}

void UI::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;

    mouseButtons_ = eventData[P_BUTTONS].GetInt();
    qualifiers_ = eventData[P_QUALIFIERS].GetInt();
    int key = eventData[P_KEY].GetInt();

    // Dismiss modal element if any when ESC key is pressed
    if (key == KEY_ESC && HasModalElement())
    {
        UIElement* element = rootModalElement_->GetChild(rootModalElement_->GetNumChildren() - 1);
        if (element->GetVars().Contains(VAR_ORIGIN))
            // If it is a popup, dismiss by defocusing it
            SetFocusElement(0);
        else
        {
            // If it is a modal window, by resetting its modal flag
            Window* window = dynamic_cast<Window*>(element);
            if (window)
                window->SetModal(false);
        }

        return;
    }

    UIElement* element = focusElement_;
    if (element)
    {
        // Switch focus between focusable elements in the same top level window
        if (key == KEY_TAB)
        {
            UIElement* topLevel = element->GetParent();
            while (topLevel && topLevel->GetParent() != rootElement_ && topLevel->GetParent() != rootModalElement_)
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
                        int dir = (qualifiers_ & QUAL_SHIFT) ? -1 : 1;
                        unsigned nextIndex = (tempElements_.Size() + i + dir) % tempElements_.Size();
                        UIElement* next = tempElements_[nextIndex];
                        SetFocusElement(next, true);
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

    UIElement* element = focusElement_;
    if (element)
        element->OnChar(eventData[P_CHAR].GetInt(), mouseButtons_, qualifiers_);
}

void UI::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    // If have a cursor, and a drag is not going on, reset the cursor shape. Application logic that wants to apply
    // custom shapes can do it after this, but needs to do it each frame
    if (cursor_ && !dragElement_)
        cursor_->SetShape(CS_NORMAL);
}

void UI::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace PostUpdate;

    Update(eventData[P_TIMESTEP].GetFloat());
}

void UI::HandleRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    RenderUpdate();
}

void UI::HandleDropFile(StringHash eventType, VariantMap& eventData)
{
    Input* input = GetSubsystem<Input>();
    
    // Sending the UI variant of the event only makes sense if the OS cursor is visible (not locked to window center)
    if (input->IsMouseVisible())
    {
        IntVector2 screenPos = input->GetMousePosition();
        UIElement* element = GetElementAt(screenPos);
        
        using namespace UIDropFile;
        
        VariantMap uiEventData;
        uiEventData[P_FILENAME] = eventData[P_FILENAME];
        uiEventData[P_X] = screenPos.x_;
        uiEventData[P_Y] = screenPos.y_;
        uiEventData[P_ELEMENT] = (void*)element;
        
        if (element)
        {
            IntVector2 relativePos = element->ScreenToElement(screenPos);
            uiEventData[P_ELEMENTX] = relativePos.x_;
            uiEventData[P_ELEMENTY] = relativePos.y_;
        }
        
        SendEvent(E_UIDROPFILE, uiEventData);
    }
}

void RegisterUILibrary(Context* context)
{
    Font::RegisterObject(context);

    UIElement::RegisterObject(context);
    BorderImage::RegisterObject(context);
    Sprite::RegisterObject(context);
    Button::RegisterObject(context);
    CheckBox::RegisterObject(context);
    Cursor::RegisterObject(context);
    Text::RegisterObject(context);
    Text3D::RegisterObject(context);
    Window::RegisterObject(context);
    View3D::RegisterObject(context);
    LineEdit::RegisterObject(context);
    Slider::RegisterObject(context);
    ScrollBar::RegisterObject(context);
    ScrollView::RegisterObject(context);
    ListView::RegisterObject(context);
    Menu::RegisterObject(context);
    DropDownList::RegisterObject(context);
    FileSelector::RegisterObject(context);
    MessageBox::RegisterObject(context);
    ToolTip::RegisterObject(context);
}

}
