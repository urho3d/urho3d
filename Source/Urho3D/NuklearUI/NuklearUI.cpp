// Copyright (c) 2008-2017 the Urho3D project.
// Copyright (c) 2016 Rokas Kupstys
// Copyright (c) 2016 Yehonatan Ballas
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
#define NK_IMPLEMENTATION 1
#include "../Precompiled.h"
#include "../Core/CoreEvents.h"
#include "../Core/Object.h"
#include "../Resource/ResourceCache.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicsEvents.h"
#include "../Input/InputEvents.h"
#include "SDL/SDL.h"
#include "../NuklearUI/NuklearUI.h"
#include "../DebugNew.h"
#undef NK_IMPLEMENTATION

using namespace Nuklear;
using namespace Urho3D;

namespace Nuklear
{
struct nk_sdl_vertex
{
    float position[2];
    float uv[2];
    nk_byte col[4];
};
}

NuklearUI::NuklearUI(Context* ctx)
    : Object(ctx)
    , MAX_VERTEX_MEMORY(2048 * 1024)
    , MAX_ELEMENT_MEMORY(512 * 1024)
    , uiScale_(1.0f)
    , graphics_(GetSubsystem< Graphics >())
	, nullTex(new Texture2D(graphics_->GetContext()))
{
    nk_init_default(&nk_ctx_, 0);
    nk_ctx_.clip.copy = &ClipboardCopy;
    nk_ctx_.clip.paste = &ClipboardPaste;
    nk_ctx_.clip.userdata = nk_handle_ptr(0);

    nk_buffer_init_default(&commands_);
    index_buffer_ = new IndexBuffer(graphics_->GetContext());
    vertex_buffer_ = new VertexBuffer(graphics_->GetContext());
    nullTex->SetNumLevels(1);
    unsigned whiteOpaque = 0xffffffff;
    nullTex->SetSize(1, 1, Graphics::GetRGBAFormat());
    nullTex->SetData(0, 0, 0, 1, 1, &whiteOpaque);
    null_texture_.texture.ptr = nullTex;

    PODVector< VertexElement > elems;
    elems.Push(VertexElement(TYPE_VECTOR2, SEM_POSITION));
    elems.Push(VertexElement(TYPE_VECTOR2, SEM_TEXCOORD));
    elems.Push(VertexElement(TYPE_UBYTE4_NORM, SEM_COLOR));
    vertex_buffer_->SetSize(MAX_VERTEX_MEMORY / sizeof(nk_sdl_vertex), elems, true);
    index_buffer_->SetSize(MAX_ELEMENT_MEMORY / sizeof(unsigned short), false, true);

    static const Nuklear::nk_draw_vertex_layout_element vertex_layout[] = {
        {NK_VERTEX_POSITION, NK_FORMAT_FLOAT, NK_OFFSETOF(Nuklear::nk_sdl_vertex, position)},
        {NK_VERTEX_TEXCOORD, NK_FORMAT_FLOAT, NK_OFFSETOF(Nuklear::nk_sdl_vertex, uv)},
        {NK_VERTEX_COLOR, NK_FORMAT_R8G8B8A8, NK_OFFSETOF(Nuklear::nk_sdl_vertex, col)},
        {NK_VERTEX_LAYOUT_END}};
    NK_MEMSET(&config_, 0, sizeof(config_));
    config_.vertex_layout = vertex_layout;
    config_.vertex_size = sizeof(Nuklear::nk_sdl_vertex);
    config_.vertex_alignment = NK_ALIGNOF(Nuklear::nk_sdl_vertex);
    config_.null = null_texture_;
    config_.circle_segment_count = 22;
    config_.curve_segment_count = 22;
    config_.arc_segment_count = 22;
    config_.global_alpha = 1.0f;
    config_.shape_AA = NK_ANTI_ALIASING_OFF;
    config_.line_AA = NK_ANTI_ALIASING_OFF;

    SubscribeToEvent(E_INPUTBEGIN, URHO3D_HANDLER(NuklearUI, OnInputBegin));
    SubscribeToEvent(E_SDLRAWINPUT, URHO3D_HANDLER(NuklearUI, OnRawEvent));
    SubscribeToEvent(E_INPUTEND, URHO3D_HANDLER(NuklearUI, OnInputEnd));
    SubscribeToEvent(E_ENDRENDERING, URHO3D_HANDLER(NuklearUI, OnEndRendering));

    nk_font_atlas_init_default(&atlas_);
    nk_font_atlas_begin(&atlas_);

    SetFont("Fonts/Anonymous Pro.ttf", 14);
}

void NuklearUI::ClipboardCopy(Nuklear::nk_handle usr, const char* text, int len)
{
    Urho3D::String str = Urho3D::String(text, (unsigned int)len);
    SDL_SetClipboardText(str.CString());
}

void NuklearUI::ClipboardPaste(Nuklear::nk_handle usr, Nuklear::nk_text_edit* edit)
{
    const char* text = SDL_GetClipboardText();
    if (text)
    {
        Nuklear::nk_textedit_paste(edit, text, Nuklear::nk_strlen(text));
    }
    (void)usr;
}

bool NuklearUI::SetFont(const Urho3D::String &fontFile, float fontSize)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SharedPtr<File> file = cache->GetFile(fontFile, true);

    if (!file->IsOpen())
    {
        return false;
    }

    unsigned fileLen = file->GetSize();

    if (fileLen == 0)
    {
        return false;
    }

    file->Seek(0);

    SharedArrayPtr<unsigned char> data(new unsigned char[fileLen]);

    if (file->Read(data, fileLen) != fileLen)
    {
        file->Close();
        return false;
    }

    struct Nuklear::nk_font* nkFont = Nuklear::nk_font_atlas_add_from_memory(&atlas_, data.Get(), (Nuklear::nk_size)fileLen, fontSize, 0);
    
    if (nkFont == 0)
    {
        file->Close();
        return false;
    }

    Nuklear::nk_style_set_font(&nk_ctx_, &nkFont->handle);

    file->Close();
    return true;
}

void NuklearUI::FinalizeFonts()
{
    const void* image;
    int w, h;
    image = nk_font_atlas_bake(&atlas_, &w, &h, NK_FONT_ATLAS_RGBA32);

    SharedPtr< Texture2D > fontTex(new Texture2D(graphics_->GetContext()));
    fontTex->SetNumLevels(1);
    fontTex->SetSize(w, h, Graphics::GetRGBAFormat());
    fontTex->SetData(0, 0, 0, w, h, image);

    // Remember the created texture for cleanup
    font_textures_.Push(fontTex);

    nk_font_atlas_end(&atlas_, nk_handle_ptr(fontTex), &null_texture_);
}

NuklearUI::~NuklearUI()
{
    nk_font_atlas_clear(&atlas_);
    nk_free(&nk_ctx_);
}

void NuklearUI::OnInputBegin(StringHash, VariantMap&)
{
    nk_input_begin(&nk_ctx_);
}

void NuklearUI::OnRawEvent(StringHash, VariantMap& args)
{
    SDL_Event* evt = static_cast< SDL_Event* >(args[SDLRawInput::P_SDLEVENT].Get< void* >());
    nk_context* ctx = &nk_ctx_;
    if (evt->type == SDL_KEYUP || evt->type == SDL_KEYDOWN)
    {
        /* key events */
        int down = evt->type == SDL_KEYDOWN;
        const Uint8* state = SDL_GetKeyboardState(0);
        SDL_Keycode sym = evt->key.keysym.sym;
        if (sym == SDLK_RSHIFT || sym == SDLK_LSHIFT)
        {
            nk_input_key(ctx, NK_KEY_SHIFT, down);
        }
        else if (sym == SDLK_DELETE)
        {
            nk_input_key(ctx, NK_KEY_DEL, down);
        }
        else if (sym == SDLK_RETURN)
        {
            nk_input_key(ctx, NK_KEY_ENTER, down);
        }
        else if (sym == SDLK_TAB)
        {
            nk_input_key(ctx, NK_KEY_TAB, down);
        }
        else if (sym == SDLK_BACKSPACE)
        {
            nk_input_key(ctx, NK_KEY_BACKSPACE, down);
        }
        else if (sym == SDLK_HOME)
        {
            nk_input_key(ctx, NK_KEY_TEXT_START, down);
            nk_input_key(ctx, NK_KEY_SCROLL_START, down);
        }
        else if (sym == SDLK_END)
        {
            nk_input_key(ctx, NK_KEY_TEXT_END, down);
            nk_input_key(ctx, NK_KEY_SCROLL_END, down);
        }
        else if (sym == SDLK_PAGEDOWN)
        {
            nk_input_key(ctx, NK_KEY_SCROLL_DOWN, down);
        }
        else if (sym == SDLK_PAGEUP)
        {
            nk_input_key(ctx, NK_KEY_SCROLL_UP, down);
        }
        else if (sym == SDLK_z)
        {
            nk_input_key(ctx, NK_KEY_TEXT_UNDO, down && state[SDL_SCANCODE_LCTRL]);
        }
        else if (sym == SDLK_r)
        {
            nk_input_key(ctx, NK_KEY_TEXT_REDO, down && state[SDL_SCANCODE_LCTRL]);
        }
        else if (sym == SDLK_c)
        {
            nk_input_key(ctx, NK_KEY_COPY, down && state[SDL_SCANCODE_LCTRL]);
        }
        else if (sym == SDLK_v)
        {
            nk_input_key(ctx, NK_KEY_PASTE, down && state[SDL_SCANCODE_LCTRL]);
        }
        else if (sym == SDLK_x)
        {
            nk_input_key(ctx, NK_KEY_CUT, down && state[SDL_SCANCODE_LCTRL]);
        }
        else if (sym == SDLK_b)
        {
            nk_input_key(ctx, NK_KEY_TEXT_LINE_START, down && state[SDL_SCANCODE_LCTRL]);
        }
        else if (sym == SDLK_e)
        {
            nk_input_key(ctx, NK_KEY_TEXT_LINE_END, down && state[SDL_SCANCODE_LCTRL]);
        }
        else if (sym == SDLK_UP)
        {
            nk_input_key(ctx, NK_KEY_UP, down);
        }
        else if (sym == SDLK_DOWN)
        {
            nk_input_key(ctx, NK_KEY_DOWN, down);
        }
        else if (sym == SDLK_LEFT)
        {
            if (state[SDL_SCANCODE_LCTRL])
            {
                nk_input_key(ctx, NK_KEY_TEXT_WORD_LEFT, down);
            }
            else
            {
                nk_input_key(ctx, NK_KEY_LEFT, down);
            }
        }
        else if (sym == SDLK_RIGHT)
        {
            if (state[SDL_SCANCODE_LCTRL])
            {
                nk_input_key(ctx, NK_KEY_TEXT_WORD_RIGHT, down);
            }
            else
            {
                nk_input_key(ctx, NK_KEY_RIGHT, down);
            }
        }
        else
        {
            return;
        }
        return;
    }
    else if (evt->type == SDL_MOUSEBUTTONDOWN || evt->type == SDL_MOUSEBUTTONUP)
    {
        /* mouse button */
        int down = evt->type == SDL_MOUSEBUTTONDOWN;
        const int x = evt->button.x, y = evt->button.y;
        if (evt->button.button == SDL_BUTTON_LEFT)
        {
            nk_input_button(ctx, NK_BUTTON_LEFT, x, y, down);
        }
        if (evt->button.button == SDL_BUTTON_MIDDLE)
        {
            nk_input_button(ctx, NK_BUTTON_MIDDLE, x, y, down);
        }
        if (evt->button.button == SDL_BUTTON_RIGHT)
        {
            nk_input_button(ctx, NK_BUTTON_RIGHT, x, y, down);
        }
        return;
    }
    else if (evt->type == SDL_MOUSEMOTION)
    {
        if (ctx->input.mouse.grabbed)
        {
            int x = (int)ctx->input.mouse.prev.x, y = (int)ctx->input.mouse.prev.y;
            nk_input_motion(ctx, x + evt->motion.xrel, y + evt->motion.yrel);
        }
        else
        {
            nk_input_motion(ctx, evt->motion.x, evt->motion.y);
        }
        return;
    }
    else if (evt->type == SDL_TEXTINPUT)
    {
        nk_glyph glyph = {};
        memcpy(glyph, evt->text.text, NK_UTF_SIZE);
        nk_input_glyph(ctx, glyph);
        return;
    }
    else if (evt->type == SDL_MOUSEWHEEL)
    {
        nk_input_scroll(ctx, nk_vec2((float)evt->wheel.x, (float)evt->wheel.y));
        return;
    }
}

void NuklearUI::OnInputEnd(StringHash, VariantMap&)
{
    nk_input_end(&nk_ctx_);
}

void NuklearUI::OnEndRendering(StringHash, VariantMap&)
{
    // Engine does not render when window is closed or device is lost
    assert(graphics_ && graphics_->IsInitialized() && !graphics_->IsDeviceLost());

    // Max. vertex / index count is not assumed to change later
    void* vertexData = vertex_buffer_->Lock(0, vertex_buffer_->GetVertexCount(), true);
    void* indexData = index_buffer_->Lock(0, index_buffer_->GetIndexCount(), true);
    if (vertexData && indexData)
    {
        Nuklear::nk_buffer vbuf, ebuf;
        nk_buffer_init_fixed(&vbuf, vertexData, (nk_size)MAX_VERTEX_MEMORY);
        nk_buffer_init_fixed(&ebuf, indexData, (nk_size)MAX_ELEMENT_MEMORY);
        nk_convert(&nk_ctx_, &commands_, &vbuf, &ebuf, &config_);
#if defined(_WIN32) && !defined(URHO3D_D3D11) && !defined(URHO3D_OPENGL)
        for (int i = 0; i < vertex_buffer_->GetVertexCount(); i++)
        {
            nk_sdl_vertex* v = (nk_sdl_vertex*)vertexData + i;
            v->position[0] += 0.5f;
            v->position[1] += 0.5f;
        }
#endif
        IntVector2 viewSize = graphics_->GetViewport().Size();
        Vector2 invScreenSize(1.0f / (float)viewSize.x_, 1.0f / (float)viewSize.y_);
        Vector2 scale(2.0f * invScreenSize.x_, -2.0f * invScreenSize.y_);
        Vector2 offset(-1.0f, 1.0f);

        Matrix4 projection(Matrix4::IDENTITY);
        projection.m00_ = scale.x_ * uiScale_;
        projection.m03_ = offset.x_;
        projection.m11_ = scale.y_ * uiScale_;
        projection.m13_ = offset.y_;
        projection.m22_ = 1.0f;
        projection.m23_ = 0.0f;
        projection.m33_ = 1.0f;

        graphics_->SetVertexBuffer(vertex_buffer_);
        graphics_->SetIndexBuffer(index_buffer_);

        vertex_buffer_->Unlock();
        index_buffer_->Unlock();

        unsigned index = 0;
        const Nuklear::nk_draw_command* cmd;
        nk_draw_foreach(cmd, &nk_ctx_, &commands_)
        {
            if (!cmd->elem_count)
            {
                continue;
            }

            ShaderVariation* ps;
            ShaderVariation* vs;

            Texture2D* texture = static_cast< Texture2D* >(cmd->texture.ptr);
            if (!texture)
            {
                ps = graphics_->GetShader(PS, "Basic", "VERTEXCOLOR");
                vs = graphics_->GetShader(VS, "Basic", "VERTEXCOLOR");
            }
            else
            {
                // If texture contains only an alpha channel, use alpha shader (for fonts)
                vs = graphics_->GetShader(VS, "Basic", "DIFFMAP VERTEXCOLOR");
                if (texture->GetFormat() == Graphics::GetAlphaFormat())
                    ps = graphics_->GetShader(PS, "Basic", "ALPHAMAP VERTEXCOLOR");
                else
                    ps = graphics_->GetShader(PS, "Basic", "DIFFMAP VERTEXCOLOR");
            }

            graphics_->SetShaders(vs, ps);
            if (graphics_->NeedParameterUpdate(SP_OBJECT, this))
            {
                graphics_->SetShaderParameter(VSP_MODEL, Matrix3x4::IDENTITY);
            }
            if (graphics_->NeedParameterUpdate(SP_CAMERA, this))
            {
                graphics_->SetShaderParameter(VSP_VIEWPROJ, projection);
            }
            if (graphics_->NeedParameterUpdate(SP_MATERIAL, this))
            {
                graphics_->SetShaderParameter(PSP_MATDIFFCOLOR, Color(1.0f, 1.0f, 1.0f, 1.0f));
            }
            float elapsedTime = GetSubsystem< Time >()->GetElapsedTime();
            graphics_->SetShaderParameter(VSP_ELAPSEDTIME, elapsedTime);
            graphics_->SetShaderParameter(PSP_ELAPSEDTIME, elapsedTime);

            IntRect scissor = IntRect((int)cmd->clip_rect.x, (int)cmd->clip_rect.y,
                                      (int)(cmd->clip_rect.x + cmd->clip_rect.w),
                                      (int)(cmd->clip_rect.y + cmd->clip_rect.h));
            scissor.left_ = (int)(scissor.left_ * uiScale_);
            scissor.top_ = (int)(scissor.top_ * uiScale_);
            scissor.right_ = (int)(scissor.right_ * uiScale_);
            scissor.bottom_ = (int)(scissor.bottom_ * uiScale_);

            graphics_->SetBlendMode(BLEND_ALPHA);
            graphics_->SetScissorTest(true, scissor);
            graphics_->SetTexture(0, (Texture2D*)cmd->texture.ptr);
            graphics_->Draw(TRIANGLE_LIST, index, cmd->elem_count, 0, 0, vertex_buffer_->GetVertexCount());
            index += cmd->elem_count;
        }
        nk_clear(&nk_ctx_);
    }
    graphics_->SetScissorTest(false);
}