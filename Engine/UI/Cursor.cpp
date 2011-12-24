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
#include "Context.h"
#include "Cursor.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "Texture2D.h"

#include "DebugNew.h"

static const String shapeNames[] =
{
    "normal",
    "resizevertical",
    "resizediagonal_topright",
    "resizehorizontal",
    "resizediagonal_topleft",
    "acceptdrop",
    "rejectdrop",
    ""
};

OBJECTTYPESTATIC(Cursor);

Cursor::Cursor(Context* context) :
    BorderImage(context),
    shape_(CS_NORMAL)
{
    // Show on top of all other UI elements
    priority_ = M_MAX_INT;
    
    for (unsigned i = 0; i < CS_MAX_SHAPES; ++i)
    {
        CursorShapeInfo& info = shapeInfos_[i];
        info.imageRect_ = IntRect::ZERO;
        info.hotSpot_ = IntVector2::ZERO;
    }
}

Cursor::~Cursor()
{
}

void Cursor::RegisterObject(Context* context)
{
    context->RegisterFactory<Cursor>();
}

void Cursor::SetStyle(const XMLElement& element)
{
    UIElement::SetStyle(element);
    
    XMLElement shapeElem = element.GetChild("shape");
    while (shapeElem)
    {
        CursorShape shape = (CursorShape)GetStringListIndex(shapeElem.GetStringLower("name"), shapeNames, CS_NORMAL);
        DefineShape(shape, GetSubsystem<ResourceCache>()->GetResource<Texture2D>(shapeElem.GetAttribute("texture")),
            shapeElem.GetIntRect("imagerect"), shapeElem.GetIntVector2("hotspot"));
        shapeElem = shapeElem.GetNext("shape");
    }
}

void Cursor::DefineShape(CursorShape shape, Texture* texture, const IntRect& imageRect, const IntVector2& hotSpot)
{
    CursorShapeInfo& info = shapeInfos_[shape];
    info.texture_ = texture;
    info.imageRect_ = imageRect;
    info.hotSpot_ = hotSpot;
    
    // Reset current shape if it was edited
    if (shape == shape_)
        SetShape(shape_);
}

void Cursor::SetShape(CursorShape shape)
{
    shape_ = shape;
    
    CursorShapeInfo& info = shapeInfos_[shape_];
    texture_ = info.texture_;
    imageRect_ = info.imageRect_;
    SetSize(info.imageRect_.right_ - info.imageRect_.left_, info.imageRect_.bottom_ - info.imageRect_.top_);
}

void Cursor::GetBatches(PODVector<UIBatch>& batches, PODVector<UIQuad>& quads, const IntRect& currentScissor)
{
    unsigned initialSize = quads.Size();
    const IntVector2& offset = shapeInfos_[shape_].hotSpot_;
    
    BorderImage::GetBatches(batches, quads, currentScissor);
    for (unsigned i = initialSize; i < quads.Size(); ++i)
    {
        quads[i].left_ -= offset.x_;
        quads[i].top_ -= offset.y_;
        quads[i].right_ -= offset.x_;
        quads[i].bottom_ -= offset.y_;
    }
}
