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

#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/ShaderVariation.h"
#include "../../Graphics/VertexBuffer.h"
#include "../../Graphics/VertexDeclaration.h"

#include "../../DebugNew.h"

namespace Urho3D
{

VertexDeclaration::VertexDeclaration(Graphics* graphics, ShaderVariation* vertexShader, unsigned elementMask) :
    inputLayout_(0)
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
    
    Create(graphics, vertexShader, elements);
}

VertexDeclaration::VertexDeclaration(Graphics* graphics, ShaderVariation* vertexShader, const PODVector<VertexBuffer*>& buffers,
    const PODVector<unsigned>& elementMasks) :
    inputLayout_(0)
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
    
    Create(graphics, vertexShader, elements);
}

VertexDeclaration::VertexDeclaration(Graphics* graphics, ShaderVariation* vertexShader, const Vector<SharedPtr<VertexBuffer> >& buffers,
    const PODVector<unsigned>& elementMasks) :
    inputLayout_(0)
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
    
    Create(graphics, vertexShader, elements);
}

VertexDeclaration::~VertexDeclaration()
{
    Release();
}

void VertexDeclaration::Create(Graphics* graphics, ShaderVariation* vertexShader, const PODVector<VertexDeclarationElement>& elements)
{
    /// \todo Implement
}

void VertexDeclaration::Release()
{
    if (inputLayout_)
    {
        inputLayout_->Release();
        inputLayout_ = 0;
    }
}

}
