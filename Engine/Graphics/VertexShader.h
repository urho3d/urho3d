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

#pragma once

#include "GPUObject.h"
#include "Resource.h"

class Deserializer;

/// Vertex shader resource
class VertexShader : public Resource, public GPUObject
{
    OBJECT(VertexShader);
    
    friend unsigned GetVSRegister(VSParameter param);
    
public:
    /// Construct
    VertexShader(Context* context);
    /// Destruct
    virtual ~VertexShader();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Load resource. Return true if successful
    virtual bool Load(Deserializer& source);
    /// Release shader
    virtual void Release();
    
    /// Return whether uses a specific shader parameter
    bool HasParameter(VSParameter parameter) const { return useParameter_[parameter]; }
    /// Return whether is Shader Model 3 format
    bool IsSM3() const { return isSM3_; }
    
    /// Check whether a shader parameter needs update
    bool NeedParameterUpdate(VSParameter parameter, const void* source);
    
private:
    /// Load parameters from an XML file
    void LoadParameters();
    /// Clear parameter use flags
    void ClearParameters();
    
    /// Parameter use flags
    bool useParameter_[MAX_VS_PARAMETERS];
    /// Shader Model 3 flag
    bool isSM3_;
};
