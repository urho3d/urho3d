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
#include "Log.h"
#include "Renderer.h"
#include "RendererImpl.h"
#include "VertexBuffer.h"
#include "VertexDeclaration.h"

#include "DebugNew.h"

const BYTE d3dElementType[] =
{
    D3DDECLTYPE_FLOAT3, // Position
    D3DDECLTYPE_FLOAT3, // Normal
    D3DDECLTYPE_D3DCOLOR, // Color
    D3DDECLTYPE_FLOAT2, // Texcoord1
    D3DDECLTYPE_FLOAT2, // Texcoord2
    D3DDECLTYPE_FLOAT3, // Cubetexcoord1
    D3DDECLTYPE_FLOAT3, // Cubetexcoord2
    D3DDECLTYPE_FLOAT4, // Tangent
    D3DDECLTYPE_FLOAT4, // Blendweights
    D3DDECLTYPE_UBYTE4, // Blendindices
    D3DDECLTYPE_FLOAT1, // Instancenumber
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
    D3DDECLUSAGE_TEXCOORD, // Instancenumber
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
    2, // Instancenumber
    2, // Instancematrix1
    3, // Instancematrix2
    4, // Instancematrix3
};

VertexDeclaration::VertexDeclaration(Renderer* renderer, unsigned elementMask) :
    mDeclaration(0)
{
    std::vector<VertexDeclarationElement> elements;
    unsigned offset = 0;
    
    for (unsigned i = 0; i < MAX_VERTEX_ELEMENTS; ++i)
    {
        VertexElement element = (VertexElement)i;
        
        if (elementMask & (1 << i))
        {
            VertexDeclarationElement newElement;
            newElement.mStream = 0;
            newElement.mElement = element;
            newElement.mOffset = offset;
            offset += VertexBuffer::sElementSize[i];
            
            elements.push_back(newElement);
        }
    }
    
    create(renderer, elements);
}

VertexDeclaration::VertexDeclaration(Renderer* renderer, const std::vector<VertexBuffer*>& buffers, const std::vector<unsigned>& elementMasks) :
    mDeclaration(0)
{
    unsigned usedElementMask = 0;
    std::vector<VertexDeclarationElement> elements;
    
    for (unsigned i = 0; i < buffers.size(); ++i)
    {
        if (buffers[i])
        {
            unsigned elementMask = elementMasks[i];
            
            if (elementMask == MASK_DEFAULT)
                elementMask = buffers[i]->getElementMask();
            else
            {
                if ((buffers[i]->getElementMask() & elementMask) != elementMask)
                    EXCEPTION("Vertex buffer does not contain all required elements");
            }
            
            for (unsigned j = 0; j < MAX_VERTEX_ELEMENTS; ++j)
            {
                VertexElement element = (VertexElement)j;
                
                if ((elementMask & (1 << j)) && (!(usedElementMask & (1 << j))))
                {
                    VertexDeclarationElement newElement;
                    newElement.mStream = i;
                    newElement.mElement = element;
                    newElement.mOffset = buffers[i]->getElementOffset(element);
                    usedElementMask |= 1 << j;
                    
                    elements.push_back(newElement);
                }
            }
        }
    }
    
    create(renderer, elements);
}

VertexDeclaration::VertexDeclaration(Renderer* renderer, const std::vector<SharedPtr<VertexBuffer> >& buffers, const std::vector<unsigned>& elementMasks) :
    mDeclaration(0)
{
    unsigned usedElementMask = 0;
    std::vector<VertexDeclarationElement> elements;
    
    for (unsigned i = 0; i < buffers.size(); ++i)
    {
        if (buffers[i])
        {
            unsigned elementMask = elementMasks[i];
            
            if (elementMask == MASK_DEFAULT)
                elementMask = buffers[i]->getElementMask();
            else
            {
                if ((buffers[i]->getElementMask() & elementMask) != elementMask)
                    EXCEPTION("Vertex buffer does not contain all required elements");
            }
            
            for (unsigned j = 0; j < MAX_VERTEX_ELEMENTS; ++j)
            {
                VertexElement element = (VertexElement)j;
                
                if ((elementMask & (1 << j)) && (!(usedElementMask & (1 << j))))
                {
                    VertexDeclarationElement newElement;
                    newElement.mStream = i;
                    newElement.mElement = element;
                    newElement.mOffset = buffers[i]->getElementOffset(element);
                    usedElementMask |= 1 << j;
                    
                    elements.push_back(newElement);
                }
            }
        }
    }
    
    create(renderer, elements);
}

VertexDeclaration::~VertexDeclaration()
{
    release();
}

void VertexDeclaration::create(Renderer* renderer, const std::vector<VertexDeclarationElement>& elements)
{
    SharedArrayPtr<D3DVERTEXELEMENT9> elementArray(new D3DVERTEXELEMENT9[elements.size() + 1]);
    
    D3DVERTEXELEMENT9* dest = elementArray;
    for (std::vector<VertexDeclarationElement>::const_iterator i = elements.begin(); i != elements.end(); ++i)
    {
        dest->Stream = i->mStream;
        dest->Offset = i->mOffset;
        dest->Type = d3dElementType[i->mElement];
        dest->Method = D3DDECLMETHOD_DEFAULT;
        dest->Usage = d3dElementUsage[i->mElement];
        dest->UsageIndex = d3dElementUsageIndex[i->mElement];
        dest++;
    }
    
    dest->Stream = 0xff;
    dest->Offset = 0;
    dest->Type = D3DDECLTYPE_UNUSED;
    dest->Method = 0;
    dest->Usage = 0;
    dest->UsageIndex = 0;
    
    if (FAILED(renderer->getImpl()->getDevice()->CreateVertexDeclaration(elementArray, &mDeclaration)))
        EXCEPTION("Could not create vertex declaration");
}

void VertexDeclaration::release()
{
    if (mDeclaration)
    {
        mDeclaration->Release();
        mDeclaration = 0;
    }
}
