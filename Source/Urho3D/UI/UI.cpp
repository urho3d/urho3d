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

#include "../UI/CheckBox.h"
#include "../Core/Context.h"
#include "../Core/CoreEvents.h"
#include "../UI/Cursor.h"
#include "../UI/DropDownList.h"
#include "../UI/FileSelector.h"
#include "../UI/Font.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicsEvents.h"
#include "../Input/Input.h"
#include "../Input/InputEvents.h"
#include "../UI/LineEdit.h"
#include "../UI/ListView.h"
#include "../IO/Log.h"
#include "../Math/Matrix3x4.h"
#include "../UI/MessageBox.h"
#include "../Core/Profiler.h"
#include "../Resource/ResourceCache.h"
#include "../UI/ScrollBar.h"
#include "../Graphics/Shader.h"
#include "../Graphics/ShaderVariation.h"
#include "../UI/Slider.h"
#include "../Container/Sort.h"
#include "../UI/Sprite.h"
#include "../UI/Text.h"
#include "../UI/Text3D.h"
#include "../Graphics/Texture2D.h"
#include "../UI/ToolTip.h"
#include "../UI/UI.h"
#include "../UI/UIEvents.h"
#include "../Graphics/VertexBuffer.h"
#include "../UI/Window.h"
#include "../UI/View3D.h"

#include <SDL/SDL.h>

#include "../DebugNew.h"

#define TOUCHID_MASK(id) (1 << id)

namespace Urho3D
{

StringHash VAR_ORIGIN("Origin");
const StringHash VAR_ORIGINAL_PARENT("OriginalParent");
const StringHash VAR_ORIGINAL_CHILD_INDEX("OriginalChildIndex");
const StringHash VAR_PARENT_CHANGED("ParentChanged");

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
    doubleClickInterval_(DEFAULT_DOUBLECLICK_INTERVAL),
    dragBeginInterval_(DEFAULT_DRAGBEGIN_INTERVAL),
    defaultToolTipDelay_(DEFAULT_TOOLTIP_DELAY),
    dragBeginDistance_(DEFAULT_DRAGBEGIN_DISTANCE),
    mouseButtons_(0),
    lastMouseButtons_(0),
    qualifiers_(0),
    maxFontTextureSize_(DEFAULT_FONT_TEXTURE_MAX_SIZE),
    dragElementsCount_(0),
    dragConfirmedCount_(0),
    initialized_(false),
    usingTouchInput_(false),
    #ifdef WIN32
    nonFocusedMouseWheel_(false),    // Default MS Windows behaviour
    #else
    nonFocusedMouseWheel_(true),     // Default Mac OS X and Linux behaviour
    #endif
    useSystemClipboard_(false),
    #if defined(ANDROID) || defined(IOS)
    useScreenKeyboard_(true),
    #else
    useScreenKeyboard_(false),
    #endif
    useMutableGlyphs_(false),
    forceAutoHint_(false),
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
    SubscribeToEvent(E_TEXTINPUT, HANDLER(UI, HandleTextInput));
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
    eventData[P_CLICKEDELEMENT] = originalElement;
    eventData[P_ELEMENT] = element;
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
        modalElement->SetParent(static_cast<UIElement*>(modalElement->GetVar(VAR_ORIGINAL_PARENT).GetPtr()),
            modalElement->GetVar(VAR_ORIGINAL_CHILD_INDEX).GetUInt());
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
                element->SetParent(static_cast<UIElement*>(element->GetVar(VAR_ORIGINAL_PARENT).GetPtr()),
                    element->GetVar(VAR_ORIGINAL_CHILD_INDEX).GetUInt());
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

    // Expire hovers
    for (HashMap<WeakPtr<UIElement>, bool>::Iterator i = hoveredElements_.Begin(); i != hoveredElements_.End(); ++i)
        i->second_ = false;

    Input* input = GetSubsystem<Input>();
    bool mouseGrabbed = input->IsMouseGrabbed();

    IntVector2 cursorPos;
    bool cursorVisible;
    GetCursorPositionAndVisible(cursorPos, cursorVisible);

    // Drag begin based on time
    if (dragElementsCount_ > 0 && !mouseGrabbed)
    {
        for (HashMap<WeakPtr<UIElement>, UI::DragData*>::Iterator i = dragElements_.Begin(); i != dragElements_.End(); )
        {
            WeakPtr<UIElement> dragElement = i->first_;
            UI::DragData* dragData = i->second_;

            if (!dragElement)
            {
                i = DragElementErase(i);
                continue;
            }

            if (!dragData->dragBeginPending)
            {
                ++i;
                continue;
            }

            if (dragData->dragBeginTimer.GetMSec(false) >= (unsigned)(dragBeginInterval_ * 1000))
            {
                dragData->dragBeginPending = false;
                IntVector2 beginSendPos = dragData->dragBeginSumPos / dragData->numDragButtons;
                dragConfirmedCount_ ++;
                if (!usingTouchInput_)
                    dragElement->OnDragBegin(dragElement->ScreenToElement(beginSendPos), beginSendPos, dragData->dragButtons, qualifiers_,cursor_);
                else
                    dragElement->OnDragBegin(dragElement->ScreenToElement(beginSendPos), beginSendPos, dragData->dragButtons, 0, 0);

                SendDragOrHoverEvent(E_DRAGBEGIN, dragElement, beginSendPos, IntVector2::ZERO, dragData);
            }

            ++i;
        }
    }

    // Mouse hover
    if (!mouseGrabbed && !input->GetTouchEmulation())
    {
        if (!usingTouchInput_ && cursorVisible)
            ProcessHover(cursorPos, mouseButtons_, qualifiers_, cursor_);
    }

    // Touch hover
    unsigned numTouches = input->GetNumTouches();
    for (unsigned i = 0; i < numTouches; ++i)
    {
        TouchState* touch = input->GetTouch(i);
        ProcessHover(touch->position_, TOUCHID_MASK(touch->touchID_), 0, 0);
    }

    // End hovers that expired without refreshing
    for (HashMap<WeakPtr<UIElement>, bool>::Iterator i = hoveredElements_.Begin(); i != hoveredElements_.End();)
    {
        if (i->first_.Expired() || !i->second_)
        {
            UIElement* element = i->first_;
            if (element)
            {
                using namespace HoverEnd;

                VariantMap& eventData = GetEventDataMap();
                eventData[P_ELEMENT] = element;
                element->SendEvent(E_HOVEREND, eventData);
            }
            i = hoveredElements_.Erase(i);
        }
        else
            ++i;
    }

    Update(timeStep, rootElement_);
    Update(timeStep, rootModalElement_);
}

void UI::RenderUpdate()
{
    assert(rootElement_ && rootModalElement_ && graphics_);

    PROFILE(GetUIBatches);

    uiRendered_ = false;

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

void UI::Render(bool resetRenderTargets)
{
    // Perform the default render only if not rendered yet
    if (resetRenderTargets && uiRendered_)
        return;

    PROFILE(RenderUI);

    // If the OS cursor is visible, apply its shape now if changed
    bool osCursorVisible = GetSubsystem<Input>()->IsMouseVisible();
    if (cursor_ && osCursorVisible)
        cursor_->ApplyOSCursorShape();

    SetVertexData(vertexBuffer_, vertexData_);
    SetVertexData(debugVertexBuffer_, debugVertexData_);

    // Render non-modal batches
    Render(resetRenderTargets, vertexBuffer_, batches_, 0, nonModalBatchSize_);
    // Render debug draw
    Render(resetRenderTargets, debugVertexBuffer_, debugDrawBatches_, 0, debugDrawBatches_.Size());
    // Render modal batches
    Render(resetRenderTargets, vertexBuffer_, batches_, nonModalBatchSize_, batches_.Size());

    // Clear the debug draw batches and data
    debugDrawBatches_.Clear();
    debugVertexData_.Clear();

    uiRendered_ = true;
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

void UI::SetClipboardText(const String& text)
{
    clipBoard_ = text;
    if (useSystemClipboard_)
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

void UI::SetUseSystemClipboard(bool enable)
{
    useSystemClipboard_ = enable;
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

const Vector<UIElement*> UI::GetDragElements()
{
    // Do not return the element until drag begin event has actually been posted
    if (!dragElementsConfirmed_.Empty())
        return dragElementsConfirmed_;

    for (HashMap<WeakPtr<UIElement>, UI::DragData*>::Iterator i = dragElements_.Begin(); i != dragElements_.End(); )
    {
        WeakPtr<UIElement> dragElement = i->first_;
        UI::DragData* dragData = i->second_;

        if (!dragElement)
        {
            i = DragElementErase(i);
            continue;
        }

        if (!dragData->dragBeginPending)
            dragElementsConfirmed_.Push(dragElement);

        ++i;
    }

    return dragElementsConfirmed_;
}

UIElement* UI::GetDragElement(unsigned index)
{
    GetDragElements();
    if (index >= dragElementsConfirmed_.Size())
        return (UIElement*)0;

    return dragElementsConfirmed_[index];
}

const String& UI::GetClipboardText() const
{
    if (useSystemClipboard_)
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

void UI::Render(bool resetRenderTargets, VertexBuffer* buffer, const PODVector<UIBatch>& batches, unsigned batchStart, unsigned batchEnd)
{
    // Engine does not render when window is closed or device is lost
    assert(graphics_ && graphics_->IsInitialized() && !graphics_->IsDeviceLost());

    if (batches.Empty())
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
    graphics_->SetColorWrite(true);
    graphics_->SetCullMode(CULL_CCW);
    graphics_->SetDepthTest(CMP_ALWAYS);
    graphics_->SetDepthWrite(false);
    graphics_->SetDrawAntialiased(false);
    graphics_->SetFillMode(FILL_SOLID);
    graphics_->SetStencilTest(false);
    if (resetRenderTargets)
        graphics_->ResetRenderTargets();
    graphics_->SetVertexBuffer(buffer);

    ShaderVariation* noTextureVS = graphics_->GetShader(VS, "Basic", "VERTEXCOLOR");
    ShaderVariation* diffTextureVS = graphics_->GetShader(VS, "Basic", "DIFFMAP VERTEXCOLOR");
    ShaderVariation* noTexturePS = graphics_->GetShader(PS, "Basic", "VERTEXCOLOR");
    ShaderVariation* diffTexturePS = graphics_->GetShader(PS, "Basic", "DIFFMAP VERTEXCOLOR");
    ShaderVariation* diffMaskTexturePS = graphics_->GetShader(PS, "Basic", "DIFFMAP ALPHAMASK VERTEXCOLOR");
    ShaderVariation* alphaTexturePS = graphics_->GetShader(PS, "Basic", "ALPHAMAP VERTEXCOLOR");

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
                        int layoutMaxSize = current->GetLayoutMaxSize();

                        if (screenPos < 0 && layoutMaxSize > 0)
                        {
                            unsigned toSkip = -screenPos / layoutMaxSize;
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
    // Prefer software cursor then OS-specific cursor
    if (cursor_ && cursor_->IsVisible())
    {
        pos = cursor_->GetPosition();
        visible = true;
    }
    else if (GetSubsystem<Input>()->GetMouseMode() == MM_RELATIVE)
        visible = true;
    else
    {
        Input* input = GetSubsystem<Input>();
        pos = input->GetMousePosition();
        visible = input->IsMouseVisible();

        if (!visible && cursor_)
            pos = cursor_->GetPosition();
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

    for (HashMap<WeakPtr<UIElement>, UI::DragData*>::Iterator i = dragElements_.Begin(); i != dragElements_.End();)
    {
        WeakPtr<UIElement> dragElement = i->first_;
        UI::DragData* dragData = i->second_;

        if (!dragElement)
        {
            i = DragElementErase(i);
            continue;
        }

        bool dragSource = dragElement && (dragElement->GetDragDropMode() & DD_SOURCE) != 0;
        bool dragTarget = element && (element->GetDragDropMode() & DD_TARGET) != 0;
        bool dragDropTest = dragSource && dragTarget && element != dragElement;
        // If drag start event has not been posted yet, do not do drag handling here
        if (dragData->dragBeginPending)
            dragSource = dragTarget = dragDropTest = false;

        // Hover effect
        // If a drag is going on, transmit hover only to the element being dragged, unless it's a drop target
        if (element && element->IsEnabled())
        {
            if (dragElement == element || dragDropTest)
            {
                element->OnHover(element->ScreenToElement(cursorPos), cursorPos, buttons, qualifiers, cursor);

                // Begin hover event
                if (!hoveredElements_.Contains(element))
                {
                    SendDragOrHoverEvent(E_HOVERBEGIN, element, cursorPos, IntVector2::ZERO, 0);
                    // Exit if element is destroyed by the event handling
                    if (!element)
                        return;
                }
                hoveredElements_[element] = true;
            }
        }

        // Drag and drop test
        if (dragDropTest)
        {
            bool accept = element->OnDragDropTest(dragElement);
            if (accept)
            {
                using namespace DragDropTest;

                VariantMap& eventData = GetEventDataMap();
                eventData[P_SOURCE] = dragElement.Get();
                eventData[P_TARGET] = element.Get();
                eventData[P_ACCEPT] = accept;
                SendEvent(E_DRAGDROPTEST, eventData);
                accept = eventData[P_ACCEPT].GetBool();
            }

            if (cursor)
                cursor->SetShape(accept ? CS_ACCEPTDROP : CS_REJECTDROP);
        }
        else if (dragSource && cursor)
            cursor->SetShape(dragElement == element ? CS_ACCEPTDROP : CS_REJECTDROP);

        ++i;
    }

    // Hover effect
    // If no drag is going on, transmit hover event.
    if (element && element->IsEnabled())
    {
        if (dragElementsCount_ == 0)
        {
            element->OnHover(element->ScreenToElement(cursorPos), cursorPos, buttons, qualifiers, cursor);

            // Begin hover event
            if (!hoveredElements_.Contains(element))
            {
                SendDragOrHoverEvent(E_HOVERBEGIN, element, cursorPos, IntVector2::ZERO, 0);
                // Exit if element is destroyed by the event handling
                if (!element)
                    return;
            }
            hoveredElements_[element] = true;
        }
    }
}

void UI::ProcessClickBegin(const IntVector2& cursorPos, int button, int buttons, int qualifiers, Cursor* cursor, bool cursorVisible)
{
    if (cursorVisible)
    {
        WeakPtr<UIElement> element(GetElementAt(cursorPos));

        bool newButton;
        if (usingTouchInput_)
            newButton = (button & buttons) == 0;
        else
            newButton = true;
        buttons |= button;

        if (element)
            SetFocusElement (element);

        // Focus change events may destroy the element, check again.
        if (element)
        {
            // Handle focusing & bringing to front
            element->BringToFront();

            // Handle click
            element->OnClickBegin(element->ScreenToElement(cursorPos), cursorPos, button, buttons, qualifiers, cursor);
            SendClickEvent(E_UIMOUSECLICK, NULL, element, cursorPos, button, buttons, qualifiers);

            // Fire double click event if element matches and is in time
            if (doubleClickElement_ && element == doubleClickElement_ && clickTimer_.GetMSec(true) <
                (unsigned)(doubleClickInterval_ * 1000) && lastMouseButtons_ == buttons)
            {
                element->OnDoubleClick(element->ScreenToElement(cursorPos), cursorPos, button, buttons, qualifiers, cursor);
                doubleClickElement_.Reset();
                SendClickEvent(E_UIMOUSEDOUBLECLICK, NULL, element, cursorPos, button, buttons, qualifiers);
            }
            else
            {
                doubleClickElement_ = element;
                clickTimer_.Reset();
            }

            // Handle start of drag. Click handling may have caused destruction of the element, so check the pointer again
            bool dragElementsContain = dragElements_.Contains(element);
            if (element && !dragElementsContain)
            {
                DragData* dragData = new DragData();
                dragElements_[element] = dragData;
                dragData->dragBeginPending = true;
                dragData->sumPos = cursorPos;
                dragData->dragBeginSumPos = cursorPos;
                dragData->dragBeginTimer.Reset();
                dragData->dragButtons = button;
                dragData->numDragButtons = CountSetBits(dragData->dragButtons);
                dragElementsCount_++;

                dragElementsContain = dragElements_.Contains(element);
            }
            else if (element && dragElementsContain && newButton)
            {
                DragData* dragData = dragElements_[element];
                dragData->sumPos += cursorPos;
                dragData->dragBeginSumPos += cursorPos;
                dragData->dragButtons |= button;
                dragData->numDragButtons = CountSetBits(dragData->dragButtons);
            }
        }
        else
        {
            // If clicked over no element, or a disabled element, lose focus (but not if there is a modal element)
            if (!HasModalElement())
                SetFocusElement(0);
            SendClickEvent(E_UIMOUSECLICK, NULL, element, cursorPos, button, buttons, qualifiers);
        }

        lastMouseButtons_ = buttons;
    }
}

void UI::ProcessClickEnd(const IntVector2& cursorPos, int button, int buttons, int qualifiers, Cursor* cursor, bool cursorVisible)
{
    if (cursorVisible)
    {
        WeakPtr<UIElement> element(GetElementAt(cursorPos));

        // Handle end of drag
        for (HashMap<WeakPtr<UIElement>, UI::DragData*>::Iterator i = dragElements_.Begin(); i != dragElements_.End();)
        {
            WeakPtr<UIElement> dragElement = i->first_;
            UI::DragData* dragData = i->second_;

            if (!dragElement)
            {
                i = DragElementErase(i);
                continue;
            }

            if (dragData->dragButtons & button)
            {
                // Handle end of click
                if (element)
                    element->OnClickEnd(element->ScreenToElement(cursorPos), cursorPos, button, buttons, qualifiers, cursor, dragElement);

                SendClickEvent(E_UIMOUSECLICKEND, dragElement, element, cursorPos, button, buttons, qualifiers);

                if (dragElement && dragElement->IsEnabled() && dragElement->IsVisible() && !dragData->dragBeginPending)
                {
                    dragElement->OnDragEnd(dragElement->ScreenToElement(cursorPos), cursorPos, dragData->dragButtons, buttons, cursor);
                    SendDragOrHoverEvent(E_DRAGEND, dragElement, cursorPos, IntVector2::ZERO, dragData);

                    bool dragSource = dragElement && (dragElement->GetDragDropMode() & DD_SOURCE) != 0;
                    if (dragSource)
                    {
                        bool dragTarget = element && (element->GetDragDropMode() & DD_TARGET) != 0;
                        bool dragDropFinish = dragSource && dragTarget && element != dragElement;

                        if (dragDropFinish)
                        {
                            bool accept = element->OnDragDropFinish(dragElement);

                            // OnDragDropFinish() may have caused destruction of the elements, so check the pointers again
                            if (accept && dragElement && element)
                            {
                                using namespace DragDropFinish;

                                VariantMap& eventData = GetEventDataMap();
                                eventData[P_SOURCE] = dragElement.Get();
                                eventData[P_TARGET] = element.Get();
                                eventData[P_ACCEPT] = accept;
                                SendEvent(E_DRAGDROPFINISH, eventData);
                            }
                        }
                    }
                }

                i = DragElementErase(i);
            }
            else
                ++i;
        }
    }
}

void UI::ProcessMove(const IntVector2& cursorPos, const IntVector2& cursorDeltaPos, int buttons, int qualifiers, Cursor* cursor, bool cursorVisible)
{
    if (cursorVisible && dragElementsCount_ > 0 && buttons)
    {
        Input* input = GetSubsystem<Input>();
        bool mouseGrabbed = input->IsMouseGrabbed();
        for (HashMap<WeakPtr<UIElement>, UI::DragData*>::Iterator i = dragElements_.Begin(); i != dragElements_.End();)
        {
            WeakPtr<UIElement> dragElement = i->first_;
            UI::DragData* dragData = i->second_;

            if (!dragElement)
            {
                i = DragElementErase(i);
                continue;
            }

            if (!(dragData->dragButtons & buttons))
            {
                ++i;
                continue;
            }

            // Calculate the position that we should send for this drag event.
            IntVector2 sendPos;
            if (usingTouchInput_)
            {
                dragData->sumPos += cursorDeltaPos;
                sendPos.x_ = dragData->sumPos.x_ / dragData->numDragButtons;
                sendPos.y_ = dragData->sumPos.y_ / dragData->numDragButtons;
            }
            else
            {
                dragData->sumPos = cursorPos;
                sendPos = cursorPos;
            }

            if (dragElement->IsEnabled() && dragElement->IsVisible())
            {
                // Signal drag begin if distance threshold was exceeded

                if (dragData->dragBeginPending && !mouseGrabbed)
                {
                    IntVector2 beginSendPos;
                    beginSendPos.x_ = dragData->dragBeginSumPos.x_ / dragData->numDragButtons;
                    beginSendPos.y_ = dragData->dragBeginSumPos.y_ / dragData->numDragButtons;

                    IntVector2 offset = cursorPos - beginSendPos;
                    if (Abs(offset.x_) >= dragBeginDistance_ || Abs(offset.y_) >= dragBeginDistance_)
                    {
                        dragData->dragBeginPending = false;
                        dragConfirmedCount_ ++;
                        dragElement->OnDragBegin(dragElement->ScreenToElement(beginSendPos), beginSendPos, buttons, qualifiers, cursor);
                        SendDragOrHoverEvent(E_DRAGBEGIN, dragElement, beginSendPos, IntVector2::ZERO, dragData);
                    }
                }

                if (!dragData->dragBeginPending)
                {
                    dragElement->OnDragMove(dragElement->ScreenToElement(sendPos), sendPos, cursorDeltaPos, buttons, qualifiers, cursor);
                    SendDragOrHoverEvent(E_DRAGMOVE, dragElement, sendPos, cursorDeltaPos, dragData);
                }
            }
            else
            {
                dragElement->OnDragEnd(dragElement->ScreenToElement(sendPos), sendPos, dragData->dragButtons, buttons, cursor);
                SendDragOrHoverEvent(E_DRAGEND, dragElement, sendPos, IntVector2::ZERO, dragData);
                dragElement.Reset();
            }

            ++i;
        }
    }
}

void UI::SendDragOrHoverEvent(StringHash eventType, UIElement* element, const IntVector2& screenPos, const IntVector2& deltaPos, UI::DragData* dragData)
{
    if (!element)
        return;

    IntVector2 relativePos = element->ScreenToElement(screenPos);

    using namespace DragMove;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_ELEMENT] = element;
    eventData[P_X] = screenPos.x_;
    eventData[P_Y] = screenPos.y_;
    eventData[P_ELEMENTX] = relativePos.x_;
    eventData[P_ELEMENTY] = relativePos.y_;

    if (eventType == E_DRAGMOVE)
    {
        eventData[P_DX] = deltaPos.x_;
        eventData[P_DY] = deltaPos.y_;
    }

    if (dragData)
    {
        eventData[P_BUTTONS] = dragData->dragButtons;
        eventData[P_NUMBUTTONS] = dragData->numDragButtons;
    }

    element->SendEvent(eventType, eventData);
}

void UI::SendClickEvent(StringHash eventType, UIElement* beginElement, UIElement* endElement, const IntVector2& pos, int button, int buttons, int qualifiers)
{
    VariantMap& eventData = GetEventDataMap();
    eventData[UIMouseClick::P_ELEMENT] = endElement;
    eventData[UIMouseClick::P_X] = pos.x_;
    eventData[UIMouseClick::P_Y] = pos.y_;
    eventData[UIMouseClick::P_BUTTON] = button;
    eventData[UIMouseClick::P_BUTTONS] = buttons;
    eventData[UIMouseClick::P_QUALIFIERS] = qualifiers;

    // For click end events, send also the element the click began on
    if (eventType == E_UIMOUSECLICKEND)
        eventData[UIMouseClickEnd::P_BEGINELEMENT] = beginElement;

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
    using namespace MouseButtonDown;

    mouseButtons_ = eventData[P_BUTTONS].GetInt();
    qualifiers_ = eventData[P_QUALIFIERS].GetInt();
    usingTouchInput_ = false;

    IntVector2 cursorPos;
    bool cursorVisible;
    GetCursorPositionAndVisible(cursorPos, cursorVisible);

    // Handle drag cancelling
    ProcessDragCancel();

    Input* input = GetSubsystem<Input>();

    if (!input->IsMouseGrabbed())
        ProcessClickBegin(cursorPos, eventData[P_BUTTON].GetInt(), mouseButtons_, qualifiers_, cursor_, cursorVisible);
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

    IntVector2 DeltaP = IntVector2(eventData[P_DX].GetInt(), eventData[P_DY].GetInt());

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

    ProcessMove(cursorPos, DeltaP, mouseButtons_, qualifiers_, cursor_, cursorVisible);
}

void UI::HandleMouseWheel(StringHash eventType, VariantMap& eventData)
{
    Input* input = GetSubsystem<Input>();
    if (input->IsMouseGrabbed())
        return;

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
    Input* input = GetSubsystem<Input>();
    if (input->IsMouseGrabbed())
        return;

    using namespace TouchBegin;

    IntVector2 pos(eventData[P_X].GetInt(), eventData[P_Y].GetInt());
    usingTouchInput_ = true;

    int touchId = TOUCHID_MASK(eventData[P_TOUCHID].GetInt());
    WeakPtr<UIElement> element(GetElementAt(pos));

    if (element)
    {
        ProcessClickBegin(pos, touchId, touchDragElements_[element], 0, 0, true);
        touchDragElements_[element] |= touchId;
    }
    else
        ProcessClickBegin(pos, touchId, touchId, 0, 0, true);
}

void UI::HandleTouchEnd(StringHash eventType, VariantMap& eventData)
{
    using namespace TouchEnd;

    IntVector2 pos(eventData[P_X].GetInt(), eventData[P_Y].GetInt());

    // Get the touch index
    int touchId = TOUCHID_MASK(eventData[P_TOUCHID].GetInt());

    // Transmit hover end to the position where the finger was lifted
    WeakPtr<UIElement> element(GetElementAt(pos));

    // Clear any drag events that were using the touch id
    for (HashMap<WeakPtr<UIElement>, int>::Iterator i = touchDragElements_.Begin(); i != touchDragElements_.End(); )
    {
        int touches = i->second_;
        if (touches & touchId)
            i = touchDragElements_.Erase(i);
        else
            ++i;
    }

    if (element && element->IsEnabled())
        element->OnHover(element->ScreenToElement(pos), pos, 0, 0, 0);

    ProcessClickEnd(pos, touchId, 0, 0, 0, true);
}

void UI::HandleTouchMove(StringHash eventType, VariantMap& eventData)
{
    using namespace TouchMove;

    IntVector2 pos(eventData[P_X].GetInt(), eventData[P_Y].GetInt());
    IntVector2 deltaPos(eventData[P_DX].GetInt(), eventData[P_DY].GetInt());
    usingTouchInput_ = true;

    int touchId = TOUCHID_MASK(eventData[P_TOUCHID].GetInt());

    ProcessMove(pos, deltaPos, touchId, 0, 0, true);
}

void UI::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;

    mouseButtons_ = eventData[P_BUTTONS].GetInt();
    qualifiers_ = eventData[P_QUALIFIERS].GetInt();
    int key = eventData[P_KEY].GetInt();

    // Cancel UI dragging
    if (key == KEY_ESC && dragElementsCount_ > 0)
    {
        ProcessDragCancel();

        return;
    }

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
            if (window && window->GetModalAutoDismiss())
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

void UI::HandleTextInput(StringHash eventType, VariantMap& eventData)
{
    using namespace TextInput;

    mouseButtons_ = eventData[P_BUTTONS].GetInt();
    qualifiers_ = eventData[P_QUALIFIERS].GetInt();

    UIElement* element = focusElement_;
    if (element)
        element->OnTextInput(eventData[P_TEXT].GetString(), mouseButtons_, qualifiers_);
}

void UI::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    // If have a cursor, and a drag is not going on, reset the cursor shape. Application logic that wants to apply
    // custom shapes can do it after this, but needs to do it each frame
    if (cursor_ && dragElementsCount_ == 0)
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
        uiEventData[P_ELEMENT] = element;

        if (element)
        {
            IntVector2 relativePos = element->ScreenToElement(screenPos);
            uiEventData[P_ELEMENTX] = relativePos.x_;
            uiEventData[P_ELEMENTY] = relativePos.y_;
        }

        SendEvent(E_UIDROPFILE, uiEventData);
    }
}

HashMap<WeakPtr<UIElement>, UI::DragData*>::Iterator UI::DragElementErase(HashMap<WeakPtr<UIElement>, UI::DragData*>::Iterator i)
{
    // If running the engine frame in response to an event (re-entering UI frame logic) the dragElements_ may already be empty
    if (dragElements_.Empty())
        return dragElements_.End();

    dragElementsConfirmed_.Clear();

    WeakPtr<UIElement> dragElement = i->first_;
    DragData* dragData = i->second_;

    if (!dragData->dragBeginPending)
        --dragConfirmedCount_;
    i = dragElements_.Erase(i);
    --dragElementsCount_;

    delete dragData;
    return i;
}

void UI::ProcessDragCancel()
{
    // How to tell difference between drag cancel and new selection on multi-touch?
    if (usingTouchInput_)
        return;

    IntVector2 cursorPos;
    bool cursorVisible;
    GetCursorPositionAndVisible(cursorPos, cursorVisible);

    for (HashMap<WeakPtr<UIElement>, UI::DragData*>::Iterator i = dragElements_.Begin(); i != dragElements_.End();)
    {
        WeakPtr<UIElement> dragElement = i->first_;
        UI::DragData* dragData = i->second_;

        if (dragElement && dragElement->IsEnabled() && dragElement->IsVisible() && !dragData->dragBeginPending)
        {
            dragElement->OnDragCancel(dragElement->ScreenToElement(cursorPos), cursorPos, dragData->dragButtons, mouseButtons_, cursor_);
            SendDragOrHoverEvent(E_DRAGCANCEL, dragElement, cursorPos, IntVector2::ZERO, dragData);
            i = DragElementErase(i);
        }
        else
            ++i;
    }
}

IntVector2 UI::SumTouchPositions(UI::DragData* dragData, const IntVector2& oldSendPos)
{
    IntVector2 sendPos = oldSendPos;
    if (usingTouchInput_)
    {
        int buttons = dragData->dragButtons;
        dragData->sumPos = IntVector2::ZERO;
        Input* input = GetSubsystem<Input>();
        for (int i = 0; (1 << i) <= buttons; i++)
        {
            if ((1 << i) & buttons)
            {
                TouchState* ts = input->GetTouch(i);
                if (!ts)
                    break;
                IntVector2 pos = ts->position_;
                dragData->sumPos.x_ += pos.x_;
                dragData->sumPos.y_ += pos.y_;
            }
        }
        sendPos.x_ = dragData->sumPos.x_ / dragData->numDragButtons;
        sendPos.y_ = dragData->sumPos.y_ / dragData->numDragButtons;
    }
    return sendPos;
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
