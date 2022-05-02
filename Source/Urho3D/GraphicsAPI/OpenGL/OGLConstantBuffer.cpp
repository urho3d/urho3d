//
// Copyright (c) 2008-2022 the Urho3D project.
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
#include "../../GraphicsAPI/ConstantBuffer.h"
#include "../../GraphicsAPI/GraphicsImpl.h"
#include "../../IO/Log.h"

#include "../../DebugNew.h"

namespace Urho3D
{

void ConstantBuffer::Release_OGL()
{
    if (object_.name_)
    {
        if (!graphics_)
            return;

#ifndef GL_ES_VERSION_2_0
        graphics_->SetUBO_OGL(0);
        glDeleteBuffers(1, &object_.name_);
#endif
        object_.name_ = 0;
    }

    shadowData_.Reset();
    size_ = 0;
}

void ConstantBuffer::OnDeviceReset_OGL()
{
    if (size_)
        SetSize_OGL(size_); // Recreate
}

bool ConstantBuffer::SetSize_OGL(unsigned size)
{
    if (!size)
    {
        URHO3D_LOGERROR("Can not create zero-sized constant buffer");
        return false;
    }

    // Round up to next 16 bytes
    size += 15;
    size &= 0xfffffff0;

    size_ = size;
    dirty_ = false;
    shadowData_ = new unsigned char[size_];
    memset(shadowData_.Get(), 0, size_);

    if (graphics_)
    {
#ifndef GL_ES_VERSION_2_0
        if (!object_.name_)
            glGenBuffers(1, &object_.name_);
        graphics_->SetUBO_OGL(object_.name_);
        glBufferData(GL_UNIFORM_BUFFER, size_, shadowData_.Get(), GL_DYNAMIC_DRAW);
#endif
    }

    return true;
}

void ConstantBuffer::Apply_OGL()
{
    if (dirty_ && object_.name_)
    {
#ifndef GL_ES_VERSION_2_0
        graphics_->SetUBO_OGL(object_.name_);
        glBufferData(GL_UNIFORM_BUFFER, size_, shadowData_.Get(), GL_DYNAMIC_DRAW);
#endif
        dirty_ = false;
    }
}

}
