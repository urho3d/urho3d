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
#include "GraphicsDefs.h"
#include "Resource.h"

class Deserializer;

/// Pixel shader resource
class PixelShader : public Resource, public GPUObject
{
    OBJECT(PixelShader);
    
public:
    /// Construct
    PixelShader(Context* context);
    /// Destruct
    virtual ~PixelShader();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Load resource. Return true if successful
    virtual bool Load(Deserializer& source);
    /// Release shader
    virtual void Release();
    
    /// Return whether uses a specific shader parameter
    bool HasParameter(PSParameter parameter) const { return useParameter_[parameter]; }
    /// Return whether uses a texture unit
    bool HasTextureUnit(TextureUnit unit) const { return useTextureUnit_[unit]; }
    /// Return whether is Shader Model 3 format
    bool IsSM3() const { return isSM3_; }
    
    /// Check whether a shader parameter needs update
    bool NeedParameterUpdate(PSParameter parameter, const void* source);
    
private:
    /// Load parameters from an XML file
    void LoadParameters();
    
    /// Parameter use flags
    bool useParameter_[MAX_PS_PARAMETERS];
    /// Texture unit use flags
    bool useTextureUnit_[MAX_TEXTURE_UNITS];
    /// Shader Model 3 flag
    bool isSM3_;
};
