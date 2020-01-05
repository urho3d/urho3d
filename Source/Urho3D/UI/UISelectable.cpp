//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../UI/UISelectable.h"

namespace Urho3D
{

extern const char* UI_CATEGORY;

void UISelectable::RegisterObject(Context* context)
{
    context->RegisterFactory<UISelectable>(UI_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);
    URHO3D_ATTRIBUTE("Selection Color", Color, selectionColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_ATTRIBUTE("Hover Color", Color, hoverColor_, Color::TRANSPARENT_BLACK, AM_FILE);
}

void UISelectable::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect & currentScissor)
{
    // Hovering and/or whole selection batch
    if ((hovering_ && hoverColor_.a_ > 0.0) || (selected_ && selectionColor_.a_ > 0.0f))
    {
        bool both = hovering_ && selected_ && hoverColor_.a_ > 0.0 && selectionColor_.a_ > 0.0f;
        UIBatch batch(this, BLEND_ALPHA, currentScissor, nullptr, &vertexData);
        batch.SetColor(both ? selectionColor_.Lerp(hoverColor_, 0.5f) :
            (selected_ && selectionColor_.a_ > 0.0f ? selectionColor_ : hoverColor_));
        batch.AddQuad(0.f, 0.f, (float)GetWidth(), (float)GetHeight(), 0, 0);
        UIBatch::AddOrMerge(batch, batches);
    }

    // Reset hovering for next frame
    hovering_ = false;
}

void UISelectable::SetSelectionColor(const Color& color)
{
    selectionColor_ = color;
}

void UISelectable::SetHoverColor(const Color& color)
{
    hoverColor_ = color;
}

}
