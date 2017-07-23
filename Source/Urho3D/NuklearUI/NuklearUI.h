//
// Copyright (c) 2008-2017 the Urho3D project.
// Copyright (c) 2016 Rokas Kupstys
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

#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT 1
#define NK_INCLUDE_FONT_BAKING 1
// #define NK_INCLUDE_DEFAULT_FONT 1
#define NK_INCLUDE_COMMAND_USERDATA 1
// #define NK_INCLUDE_STANDARD_IO 1
#define NK_ASSERT
#define NK_INCLUDE_FIXED_TYPES 1
#define NK_INCLUDE_DEFAULT_ALLOCATOR 1
#define NK_INCLUDE_STANDARD_VARARGS 1

#include "../Core/Object.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/VertexBuffer.h"

namespace Nuklear
{
#include "../ThirdParty/Nuklear/nuklear.h"
}

class URHO3D_API NuklearUI : public Urho3D::Object
{
    URHO3D_OBJECT(NuklearUI, Object);

public:
    NuklearUI(Urho3D::Context* ctx);
    virtual ~NuklearUI();

    Nuklear::nk_context* GetNkContext()
    {
        return &nk_ctx_;
    }
    operator Nuklear::nk_context*()
    {
        return &nk_ctx_;
    }
    Nuklear::nk_font_atlas* GetFontAtlas()
    {
        return &atlas_;
    }

    bool SetFont(const Urho3D::String & fontFile, float fontSize);
    void FinalizeFonts();

protected:
    void OnInputBegin(Urho3D::StringHash, Urho3D::VariantMap&);
    void OnRawEvent(Urho3D::StringHash, Urho3D::VariantMap& args);
    void OnInputEnd(Urho3D::StringHash, Urho3D::VariantMap&);
    void OnEndRendering(Urho3D::StringHash, Urho3D::VariantMap&);

    static void ClipboardCopy(Nuklear::nk_handle usr, const char* text, int len);
    static void ClipboardPaste(Nuklear::nk_handle usr, Nuklear::nk_text_edit* edit);

    const int MAX_VERTEX_MEMORY;
    const int MAX_ELEMENT_MEMORY;

	Urho3D::SharedPtr<Urho3D::Graphics> graphics_;

    Nuklear::nk_context nk_ctx_;
    Nuklear::nk_font_atlas atlas_;
    Nuklear::nk_buffer commands_;
    Nuklear::nk_draw_null_texture null_texture_;
	Urho3D::SharedPtr<Urho3D::VertexBuffer> vertex_buffer_;
	Urho3D::SharedPtr<Urho3D::IndexBuffer> index_buffer_;
    Urho3D::Vector< Urho3D::SharedPtr< Urho3D::Texture2D > > font_textures_;
    float uiScale_;
    Nuklear::nk_convert_config config_;
	Urho3D::SharedPtr<Urho3D::Texture2D> nullTex;
};