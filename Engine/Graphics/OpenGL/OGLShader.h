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

#pragma once

#include "ArrayPtr.h"
#include "Resource.h"
#include "ShaderParser.h"

namespace Urho3D
{

class ShaderVariation;

/// %Shader resource consisting of several shader variations.
class Shader : public Resource
{
    OBJECT(Shader);
    
public:
    /// Construct.
    Shader(Context* context);
    /// Destruct.
    virtual ~Shader();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Load resource. Return true if successful.
    virtual bool Load(Deserializer& source);
    
    /// Return a named variation. Return null if not found.
    ShaderVariation* GetVariation(ShaderType type, const String& name);
    
private:
    /// Process source code and include files. Return true if successful.
    bool ProcessSource(SharedArrayPtr<char>& dest, unsigned& length, const String& fileName);
    
    /// Vertex shader GLSL source code.
    SharedArrayPtr<char> vsSourceCode_;
    /// Pixel shader GLSL source code.
    SharedArrayPtr<char> psSourceCode_;
    /// Vertex shader source code length.
    unsigned vsSourceCodeLength_;
    /// Pixel shader code length.
    unsigned psSourceCodeLength_;
    /// Vertex shader variation parser.
    ShaderParser vsParser_;
    /// Pixel shader variation parser.
    ShaderParser psParser_;
    /// Vertex shader variations.
    HashMap<StringHash, SharedPtr<ShaderVariation> > vsVariations_;
    /// Pixel shader variations.
    HashMap<StringHash, SharedPtr<ShaderVariation> > psVariations_;
};

}
