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

#include "../../Precompiled.h"

#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/VertexBuffer.h"
#include "../../Graphics/VertexDeclaration.h"

#include "../../DebugNew.h"

namespace Urho3D
{

const BYTE d3dElementType[] =
{
    D3DDECLTYPE_FLOAT3, // Position
    D3DDECLTYPE_FLOAT3, // Normal
    D3DDECLTYPE_UBYTE4N, // Color
    D3DDECLTYPE_FLOAT2, // Texcoord1
    D3DDECLTYPE_FLOAT2, // Texcoord2
    D3DDECLTYPE_FLOAT3, // Cubetexcoord1
    D3DDECLTYPE_FLOAT3, // Cubetexcoord2
    D3DDECLTYPE_FLOAT4, // Tangent
    D3DDECLTYPE_FLOAT4, // Blendweights
    D3DDECLTYPE_UBYTE4, // Blendindices
    D3DDECLTYPE_FLOAT4, // Instancematrix1
    D3DDECLTYPE_FLOAT4, // Instancematrix2
    D3DDECLTYPE_FLOAT4 // Instancematrix3
};

const BYTE d3dElementUsage[] =
{
    D3DDECLUSAGE_POSITION, // Position
    D3DDECLUSAGE_NORMAL, // Normal
    D3DDECLUSAGE_COLOR, // Color
    D3DDECLUSAGE_TEXCOORD, // Texcoord1
    D3DDECLUSAGE_TEXCOORD, // Texcoord2
    D3DDECLUSAGE_TEXCOORD, // Cubetexcoord1
    D3DDECLUSAGE_TEXCOORD, // Cubetexcoord2
    D3DDECLUSAGE_TANGENT, // Tangent
    D3DDECLUSAGE_BLENDWEIGHT, // Blendweights
    D3DDECLUSAGE_BLENDINDICES, // Blendindices
    D3DDECLUSAGE_TEXCOORD, // Instancematrix1
    D3DDECLUSAGE_TEXCOORD, // Instancematrix2
    D3DDECLUSAGE_TEXCOORD // Instancematrix3
};

const BYTE d3dElementUsageIndex[] =
{
    0, // Position
    0, // Normal
    0, // Color
    0, // Texcoord1
    1, // Texcoord2
    0, // Cubetexcoord1
    1, // Cubetexcoord2
    0, // Tangent
    0, // Blendweights
    0, // Blendindices
    2, // Instancematrix1
    3, // Instancematrix2
    4 // Instancematrix3
};

VertexDeclaration::VertexDeclaration(Graphics* graphics, unsigned elementMask) :
    declaration_(0)
{
    PODVector<VertexDeclarationElement> elements;
    unsigned offset = 0;

    for (unsigned i = 0; i < MAX_VERTEX_ELEMENTS; ++i)
    {
        VertexElement element = (VertexElement)i;

        if (elementMask & (1 << i))
        {
            VertexDeclarationElement newElement;
            newElement.stream_ = 0;
            newElement.element_ = element;
            newElement.offset_ = offset;
            offset += VertexBuffer::elementSize[i];

            elements.Push(newElement);
        }
    }

    Create(graphics, elements);
}

VertexDeclaration::VertexDeclaration(Graphics* graphics, const PODVector<VertexBuffer*>& buffers,
    const PODVector<unsigned>& elementMasks) :
    declaration_(0)
{
    unsigned usedElementMask = 0;
    PODVector<VertexDeclarationElement> elements;

    for (unsigned i = 0; i < buffers.Size(); ++i)
    {
        if (buffers[i])
        {
            unsigned elementMask = elementMasks[i];

            if (elementMask == MASK_DEFAULT)
                elementMask = buffers[i]->GetElementMask();
            else
            {
                if ((buffers[i]->GetElementMask() & elementMask) != elementMask)
                    return;
            }

            for (unsigned j = 0; j < MAX_VERTEX_ELEMENTS; ++j)
            {
                VertexElement element = (VertexElement)j;

                if (elementMask & (1 << j) && !(usedElementMask & (1 << j)))
                {
                    VertexDeclarationElement newElement;
                    newElement.stream_ = i;
                    newElement.element_ = element;
                    newElement.offset_ = buffers[i]->GetElementOffset(element);
                    usedElementMask |= 1 << j;

                    elements.Push(newElement);
                }
            }
        }
    }

    Create(graphics, elements);
}

VertexDeclaration::VertexDeclaration(Graphics* graphics, const Vector<SharedPtr<VertexBuffer> >& buffers,
    const PODVector<unsigned>& elementMasks) :
    declaration_(0)
{
    unsigned usedElementMask = 0;
    PODVector<VertexDeclarationElement> elements;

    for (unsigned i = 0; i < buffers.Size(); ++i)
    {
        if (buffers[i])
        {
            unsigned elementMask = elementMasks[i];

            if (elementMask == MASK_DEFAULT)
                elementMask = buffers[i]->GetElementMask();
            else
            {
                if ((buffers[i]->GetElementMask() & elementMask) != elementMask)
                    return;
            }

            for (unsigned j = 0; j < MAX_VERTEX_ELEMENTS; ++j)
            {
                VertexElement element = (VertexElement)j;

                if (elementMask & (1 << j) && !(usedElementMask & (1 << j)))
                {
                    VertexDeclarationElement newElement;
                    newElement.stream_ = i;
                    newElement.element_ = element;
                    newElement.offset_ = buffers[i]->GetElementOffset(element);
                    usedElementMask |= 1 << j;

                    elements.Push(newElement);
                }
            }
        }
    }

    Create(graphics, elements);
}

VertexDeclaration::~VertexDeclaration()
{
    Release();
}

void VertexDeclaration::Create(Graphics* graphics, const PODVector<VertexDeclarationElement>& elements)
{
    SharedArrayPtr<D3DVERTEXELEMENT9> elementArray(new D3DVERTEXELEMENT9[elements.Size() + 1]);

    D3DVERTEXELEMENT9* dest = elementArray;
    for (Vector<VertexDeclarationElement>::ConstIterator i = elements.Begin(); i != elements.End(); ++i)
    {
        dest->Stream = (WORD)i->stream_;
        dest->Offset = (WORD)i->offset_;
        dest->Type = d3dElementType[i->element_];
        dest->Method = D3DDECLMETHOD_DEFAULT;
        dest->Usage = d3dElementUsage[i->element_];
        dest->UsageIndex = d3dElementUsageIndex[i->element_];
        dest++;
    }

    dest->Stream = 0xff;
    dest->Offset = 0;
    dest->Type = D3DDECLTYPE_UNUSED;
    dest->Method = 0;
    dest->Usage = 0;
    dest->UsageIndex = 0;

    IDirect3DDevice9* device = graphics->GetImpl()->GetDevice();
    if (!device)
        return;

    device->CreateVertexDeclaration(elementArray, &declaration_);
}

void VertexDeclaration::Release()
{
    if (declaration_)
    {
        declaration_->Release();
        declaration_ = 0;
    }
}

}
