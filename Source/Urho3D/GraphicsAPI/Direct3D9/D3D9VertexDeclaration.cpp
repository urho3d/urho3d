// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../../Precompiled.h"

#include "../../Graphics/Graphics.h"
#include "../../GraphicsAPI/Direct3D9/D3D9GraphicsImpl.h"
#include "../../GraphicsAPI/VertexBuffer.h"
#include "../../IO/Log.h"
#include "D3D9VertexDeclaration.h"

#include "../../DebugNew.h"

namespace Urho3D
{

const BYTE d3dElementType[] =
{
    D3DDECLTYPE_UNUSED, // Int (not supported by D3D9)
    D3DDECLTYPE_FLOAT1, // Float
    D3DDECLTYPE_FLOAT2, // Vector2
    D3DDECLTYPE_FLOAT3, // Vector3
    D3DDECLTYPE_FLOAT4, // Vector4
    D3DDECLTYPE_UBYTE4, // 4 bytes, not normalized
    D3DDECLTYPE_UBYTE4N // 4 bytes, normalized
};

const BYTE d3dElementUsage[] =
{
    D3DDECLUSAGE_POSITION,
    D3DDECLUSAGE_NORMAL,
    D3DDECLUSAGE_BINORMAL,
    D3DDECLUSAGE_TANGENT,
    D3DDECLUSAGE_TEXCOORD,
    D3DDECLUSAGE_COLOR,
    D3DDECLUSAGE_BLENDWEIGHT,
    D3DDECLUSAGE_BLENDINDICES,
    D3DDECLUSAGE_TEXCOORD // Object index (not supported by D3D9)
};

VertexDeclaration_D3D9::VertexDeclaration_D3D9(Graphics* graphics, const PODVector<VertexElement>& srcElements) :
    declaration_(nullptr)
{
    PODVector<VertexDeclarationElement_D3D9> elements;

    for (unsigned i = 0; i < srcElements.Size(); ++i)
    {
        const VertexElement& srcElement = srcElements[i];

        if (srcElement.semantic_ == SEM_OBJECTINDEX)
        {
            URHO3D_LOGWARNING("Object index attribute is not supported on Direct3D9 and will be ignored");
            continue;
        }

        VertexDeclarationElement_D3D9 element;
        element.semantic_ = srcElement.semantic_;
        element.type_ = srcElement.type_;
        element.index_ = srcElement.index_;
        element.streamIndex_ = 0;
        element.offset_ = srcElement.offset_;
        elements.Push(element);
    }

    Create(graphics, elements);
}

VertexDeclaration_D3D9::VertexDeclaration_D3D9(Graphics* graphics, const PODVector<VertexBuffer*>& buffers) :
    declaration_(nullptr)
{
    PODVector<VertexDeclarationElement_D3D9> elements;
    unsigned prevBufferElements = 0;

    for (unsigned i = 0; i < buffers.Size(); ++i)
    {
        if (!buffers[i])
            continue;

        const PODVector<VertexElement>& srcElements = buffers[i]->GetElements();
        bool isExisting = false;

        for (unsigned j = 0; j < srcElements.Size(); ++j)
        {
            const VertexElement& srcElement = srcElements[j];

            if (srcElement.semantic_ == SEM_OBJECTINDEX)
            {
                URHO3D_LOGWARNING("Object index attribute is not supported on Direct3D9 and will be ignored");
                continue;
            }

            // Override existing element if necessary
            for (unsigned k = 0; k < prevBufferElements; ++k)
            {
                if (elements[k].semantic_ == srcElement.semantic_ && elements[k].index_ == srcElement.index_)
                {
                    isExisting = true;
                    elements[k].streamIndex_ = i;
                    elements[k].offset_ = srcElement.offset_;
                    break;
                }
            }

            if (isExisting)
                continue;

            VertexDeclarationElement_D3D9 element;
            element.semantic_ = srcElement.semantic_;
            element.type_ = srcElement.type_;
            element.index_ = srcElement.index_;
            element.streamIndex_ = i;
            element.offset_ = srcElement.offset_;
            elements.Push(element);
        }

        prevBufferElements = elements.Size();
    }

    Create(graphics, elements);
}

VertexDeclaration_D3D9::VertexDeclaration_D3D9(Graphics* graphics, const Vector<SharedPtr<VertexBuffer> >& buffers) :
    declaration_(nullptr)
{
    PODVector<VertexDeclarationElement_D3D9> elements;
    unsigned prevBufferElements = 0;

    for (unsigned i = 0; i < buffers.Size(); ++i)
    {
        if (!buffers[i])
            continue;

        const PODVector<VertexElement>& srcElements = buffers[i]->GetElements();
        bool isExisting = false;

        for (unsigned j = 0; j < srcElements.Size(); ++j)
        {
            const VertexElement& srcElement = srcElements[j];

            if (srcElement.semantic_ == SEM_OBJECTINDEX)
            {
                URHO3D_LOGWARNING("Object index attribute is not supported on Direct3D9 and will be ignored");
                continue;
            }

            // Override existing element if necessary
            for (unsigned k = 0; k < prevBufferElements; ++k)
            {
                if (elements[k].semantic_ == srcElement.semantic_ && elements[k].index_ == srcElement.index_)
                {
                    isExisting = true;
                    elements[k].streamIndex_ = i;
                    elements[k].offset_ = srcElement.offset_;
                    break;
                }
            }

            if (isExisting)
                continue;

            VertexDeclarationElement_D3D9 element;
            element.semantic_ = srcElement.semantic_;
            element.type_ = srcElement.type_;
            element.index_ = srcElement.index_;
            element.streamIndex_ = i;
            element.offset_ = srcElement.offset_;
            elements.Push(element);
        }

        prevBufferElements = elements.Size();
    }

    Create(graphics, elements);
}

VertexDeclaration_D3D9::~VertexDeclaration_D3D9()
{
    Release();
}

void VertexDeclaration_D3D9::Create(Graphics* graphics, const PODVector<VertexDeclarationElement_D3D9>& elements)
{
    SharedArrayPtr<D3DVERTEXELEMENT9> elementArray(new D3DVERTEXELEMENT9[elements.Size() + 1]);

    D3DVERTEXELEMENT9* dest = elementArray;
    for (Vector<VertexDeclarationElement_D3D9>::ConstIterator i = elements.Begin(); i != elements.End(); ++i)
    {
        dest->Stream = (WORD)i->streamIndex_;
        dest->Offset = (WORD)i->offset_;
        dest->Type = d3dElementType[i->type_];
        dest->Method = D3DDECLMETHOD_DEFAULT;
        dest->Usage = d3dElementUsage[i->semantic_];
        dest->UsageIndex = i->index_;
        dest++;
    }

    dest->Stream = 0xff;
    dest->Offset = 0;
    dest->Type = D3DDECLTYPE_UNUSED;
    dest->Method = 0;
    dest->Usage = 0;
    dest->UsageIndex = 0;

    IDirect3DDevice9* device = graphics->GetImpl_D3D9()->GetDevice();
    HRESULT hr = device->CreateVertexDeclaration(elementArray, &declaration_);
    if (FAILED(hr))
    {
        URHO3D_SAFE_RELEASE(declaration_);
        URHO3D_LOGD3DERROR("Failed to create vertex declaration", hr);
    }
}

void VertexDeclaration_D3D9::Release()
{
    URHO3D_SAFE_RELEASE(declaration_);
}

}
