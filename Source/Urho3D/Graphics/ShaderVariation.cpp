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

#include "../Graphics/Graphics.h"
#include "../Graphics/Shader.h"
#include "../Graphics/ShaderVariation.h"

#include "../DebugNew.h"

namespace Urho3D
{

ShaderParameter::ShaderParameter(const String& name, unsigned glType, int location) :   // NOLINT(hicpp-member-init)
    name_{name},
    glType_{glType},
    location_{location}
{
}

ShaderParameter::ShaderParameter(ShaderType type, const String& name, unsigned offset, unsigned size, unsigned buffer) :    // NOLINT(hicpp-member-init)
    type_{type},
    name_{name},
    offset_{offset},
    size_{size},
    buffer_{buffer}
{
}

ShaderParameter::ShaderParameter(ShaderType type, const String& name, unsigned reg, unsigned regCount) :    // NOLINT(hicpp-member-init)
    type_{type},
    name_{name},
    register_{reg},
    regCount_{regCount}
{
}

ShaderVariation::ShaderVariation(Shader* owner, ShaderType type) :
    GPUObject(owner->GetSubsystem<Graphics>()),
    owner_(owner),
    type_(type)
{
}

ShaderVariation::~ShaderVariation()
{
    Release();
}

void ShaderVariation::SetName(const String& name)
{
    name_ = name;
}

Shader* ShaderVariation::GetOwner() const
{
    return owner_;
}

}
