//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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

namespace Urho3D
{

static const char* shapeNames[] =
{
    "Normal",
    "ResizeVertical",
    "ResizeDiagonalTopRight",
    "ResizeHorizontal",
    "ResizeDiagonalTopLeft",
    "AcceptDrop",
    "RejectDrop",
    0
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
    
    ACCESSOR_ATTRIBUTE(Cursor, VAR_VARIANTVECTOR, "Shapes", GetShapesAttr, SetShapesAttr, VariantVector, VariantVector(), AM_FILE);
    COPY_BASE_ATTRIBUTES(Cursor, BorderImage);
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
    SetSize(info.imageRect_.Size());
}

void Cursor::SetShapesAttr(VariantVector value)
{
    unsigned index = 0;
    if (!value.Size())
        return;
    
    unsigned numShapes = value[index++].GetUInt();
    while (numShapes-- && (index + 4) <= value.Size())
    {
        CursorShape shape = (CursorShape)GetStringListIndex(value[index++].GetString().CString(), shapeNames, CS_MAX_SHAPES);
        if (shape != CS_MAX_SHAPES)
        {
            ResourceRef ref = value[index++].GetResourceRef();
            IntRect imageRect = value[index++].GetIntRect();
            IntVector2 hotSpot = value[index++].GetIntVector2();
            DefineShape(shape, GetSubsystem<ResourceCache>()->GetResource<Texture2D>(ref.id_), imageRect, hotSpot);
        }
        else
            index += 3;
    }
}

VariantVector Cursor::GetShapesAttr() const
{
    VariantVector ret;
    
    unsigned numShapes = 0;
    for (unsigned i = 0; i < CS_MAX_SHAPES; ++i)
    {
        if (shapeInfos_[i].imageRect_ != IntRect::ZERO)
            ++numShapes;
    }
    
    ret.Push(numShapes);
    for (unsigned i = 0; i < CS_MAX_SHAPES; ++i)
    {
        if (shapeInfos_[i].imageRect_ != IntRect::ZERO)
        {
            ret.Push(String(shapeNames[i]));
            ret.Push(GetResourceRef(shapeInfos_[i].texture_, Texture2D::GetTypeStatic()));
            ret.Push(shapeInfos_[i].imageRect_);
            ret.Push(shapeInfos_[i].hotSpot_);
        }
    }
    
    return ret;
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

}
