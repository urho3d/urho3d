//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Material.h"
#include "Text.h"
#include "Text3D.h"

namespace Urho3D
{

OBJECTTYPESTATIC(Text3D);

Text3D::Text3D(Context* context) :
    Drawable(context, DRAWABLE_GEOMETRY),
    text_(new Text(context))
{
    batches_.Resize(1);
}

Text3D::~Text3D()
{
}

void Text3D::RegisterObject(Context* context)
{
    context->RegisterFactory<Text3D>();
}

bool Text3D::SetFont(const String& fontName, int size)
{
    return text_->SetFont(fontName, size);
}

bool Text3D::SetFont(Font* font, int size)
{
    return text_->SetFont(font, size);
}

void Text3D::SetText(const String& text)
{
    text_->SetText(text);
}

void Text3D::SetTextAlignment(HorizontalAlignment align)
{
    text_->SetTextAlignment(align);
}

void Text3D::SetRowSpacing(float spacing)
{
    text_->SetRowSpacing(spacing);
}

void Text3D::SetMaterial(Material* material)
{
    batches_[0].material_ = material;
}

void Text3D::SetWordwrap(bool enable)
{
    text_->SetWordwrap(enable);
}

Font* Text3D::GetFont() const
{
    return text_->GetFont();
}

int Text3D::GetFontSize() const
{
    return text_->GetFontSize();
}

const String& Text3D::GetText() const
{
    return text_->GetText();
}

HorizontalAlignment Text3D::GetTextAlignment() const
{
    return text_->GetTextAlignment();
}

float Text3D::GetRowSpacing() const
{
    return text_->GetRowSpacing();
}

bool Text3D::GetWordwrap() const
{
    return text_->GetWordwrap();
}

int Text3D::GetRowHeight() const
{
    return text_->GetRowHeight();
}

unsigned Text3D::GetNumRows() const
{
    return text_->GetNumRows();
}

const PODVector<int>& Text3D::GetRowWidths() const
{
    return text_->GetRowWidths();
}

Material* Text3D::GetMaterial() const
{
    return batches_[0].material_;
}

void Text3D::OnWorldBoundingBoxUpdate()
{
}

}
