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

#include "Resource.h"

class ShaderVariation;

/// Shader resource consisting of several shader variations
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
    
    /// Get a named variation. Return null if not found or could not be created.
    ShaderVariation* GetVariation(const String& name);
    /// Get a named variation. Return null if not found or could not be created.
    ShaderVariation* GetVariation(StringHash nameHash);
    /// Release (unload) all variations.
    void ReleaseAll();
    
    /// Return shader type.
    ShaderType GetShaderType() const { return shaderType_; }
    /// Return whether requires Shader Model 3.
    bool IsSM3() const { return isSM3_; }
    /// Return number of variations.
    unsigned GetNumVariations() const { return variations_.Size(); }
    
private:
    /// Shader type.
    ShaderType shaderType_;
    /// Shader Model 3 flag.
    bool isSM3_;
    /// Shader variations. Will be in an unloaded state until requested.
    Map<StringHash, SharedPtr<ShaderVariation> > variations_;
};
