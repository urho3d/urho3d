// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
