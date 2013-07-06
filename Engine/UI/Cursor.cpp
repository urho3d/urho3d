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
#include "Cursor.h"
#include "Input.h"
#include "Ptr.h"
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
    "Busy",
    0
};

extern const char* UI_CATEGORY;

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
        info.osCursor_ = 0;
    }
}

Cursor::~Cursor()
{
    for (unsigned i = 0; i < CS_MAX_SHAPES; ++i)
    {
        CursorShapeInfo& info = shapeInfos_[i];
        if (info.osCursor_)
        {
            SDL_FreeCursor(info.osCursor_);
            info.osCursor_ = 0;
        }
    }
}

void Cursor::RegisterObject(Context* context)
{
    context->RegisterFactory<Cursor>(UI_CATEGORY);

    COPY_BASE_ATTRIBUTES(Cursor, BorderImage);
    UPDATE_ATTRIBUTE_DEFAULT_VALUE(Cursor, "Priority", M_MAX_INT);
    ACCESSOR_ATTRIBUTE(Cursor, VAR_VARIANTVECTOR, "Shapes", GetShapesAttr, SetShapesAttr, VariantVector, Variant::emptyVariantVector, AM_FILE);
}

void Cursor::DefineShape(CursorShape shape, Image* image, const IntRect& imageRect, const IntVector2& hotSpot, bool osMouseVisible)
{
    if (!image)
        return;
    
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    CursorShapeInfo& info = shapeInfos_[shape];
    
    // Prefer to get the texture with same name from cache to prevent creating several copies of the texture
    if (cache->Exists(image->GetName()))
        info.texture_ = cache->GetResource<Texture2D>(image->GetName());
    else
    {
        Texture2D* texture = new Texture2D(context_);
        texture->Load(SharedPtr<Image>(image));
        info.texture_ = texture;
    }
    
    info.imageRect_ = imageRect;
    info.hotSpot_ = hotSpot;
    if (info.osCursor_)
    {
        SDL_FreeCursor(info.osCursor_);
        info.osCursor_ = 0;
    }

    if (osMouseVisible)
    {
        unsigned comp = image->GetComponents();
        int imageWidth = image->GetWidth();
        int width = imageRect.Width();
        int height = imageRect.Height();

        // Assume little-endian for all the supported platforms
        unsigned rMask = 0x000000ff;
        unsigned gMask = 0x0000ff00;
        unsigned bMask = 0x00ff0000;
        unsigned aMask = 0xff000000;

        SDL_Surface* surface = (comp >= 3 ? SDL_CreateRGBSurface(0, width, height, comp * 8, rMask, gMask, bMask, aMask) : 0);
        if (surface)
        {
            unsigned char* destination = reinterpret_cast<unsigned char*>(surface->pixels);
            unsigned char* source = image->GetData() + comp * (imageWidth * imageRect.top_ + imageRect.left_);
            for (int i = 0; i < height; ++i)
            {
                memcpy(destination, source, comp * width);
                destination += comp * width;
                source += comp * imageWidth;
            }
            info.osCursor_ = SDL_CreateColorCursor(surface, info.hotSpot_.x_, info.hotSpot_.y_);
            SDL_FreeSurface(surface);
        }
    }

    // Reset current shape if it was edited
    if (shape == shape_)
    {
        shape_ = CS_MAX_SHAPES;
        SetShape(shape);
    }
}

void Cursor::SetShape(CursorShape shape)
{
    if (shape == shape_ || shape < CS_NORMAL || shape >= CS_MAX_SHAPES)
        return;

    shape_ = shape;

    CursorShapeInfo& info = shapeInfos_[shape_];
    texture_ = info.texture_;
    imageRect_ = info.imageRect_;
    SetSize(info.imageRect_.Size());

    if (info.osCursor_)
        SDL_SetCursor(info.osCursor_);
}

void Cursor::SetShapesAttr(VariantVector value)
{
    unsigned index = 0;
    if (!value.Size())
        return;

    Input* input = GetSubsystem<Input>();
    bool osMouseVisible = input->IsMouseVisible();

    unsigned numShapes = value[index++].GetUInt();
    while (numShapes-- && (index + 4) <= value.Size())
    {
        CursorShape shape = (CursorShape)GetStringListIndex(value[index++].GetString().CString(), shapeNames, CS_MAX_SHAPES);
        if (shape != CS_MAX_SHAPES)
        {
            ResourceRef ref = value[index++].GetResourceRef();
            IntRect imageRect = value[index++].GetIntRect();
            IntVector2 hotSpot = value[index++].GetIntVector2();
            DefineShape(shape, GetSubsystem<ResourceCache>()->GetResource<Image>(ref.id_), imageRect, hotSpot, osMouseVisible);
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

void Cursor::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    unsigned initialSize = vertexData.Size();
    const IntVector2& offset = shapeInfos_[shape_].hotSpot_;
    Vector2 floatOffset(-(float)offset.x_, -(float)offset.y_);

    BorderImage::GetBatches(batches, vertexData, currentScissor);
    for (unsigned i = initialSize; i < vertexData.Size(); i += 6)
    {
        vertexData[i] += floatOffset.x_;
        vertexData[i + 1] += floatOffset.y_;
    }
}

}
