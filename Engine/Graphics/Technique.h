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

#include "GraphicsDefs.h"
#include "Resource.h"

class ShaderVariation;

/// Material rendering pass, which defines shaders and render state
class Pass
{
public:
    /// Construct with defaults
    Pass();
    /// Construct with pass type
    Pass(PassType type);
    /// Destruct
    ~Pass();
    
    /// Set alpha masking hint on/off
    void SetAlphaMask(bool enable);
    /// Set alpha test on/off
    void SetAlphaTest(bool enable);
    /// Set blend mode
    void SetBlendMode(BlendMode mode);
    /// Set depth compare mode
    void SetDepthTestMode(CompareMode mode);
    /// Set depth write on/off
    void SetDepthWrite(bool enable);
    /// Set vertex shader name
    void SetVertexShader(const String& name);
    /// Set pixel shader name
    void SetPixelShader(const String& name);
    /// Reset shader pointers
    void ReleaseShaders();
    
    /// Return pass type
    PassType GetType() const { return type_; }
    /// Return alpha masking hint
    bool GetAlphaMask() const { return alphaMask_; }
    /// Return alpha test mode
    bool GetAlphaTest() const { return alphaTest_; }
    /// Return blend mode
    BlendMode GetBlendMode() const { return blendMode_; }
    /// Return depth compare mode
    CompareMode GetDepthTestMode() const { return depthTestMode_; }
    /// Return depth write mode
    bool GetDepthWrite() const { return depthWrite_; }
    /// Return vertex shader name
    const String& GetVertexShaderName() const { return vertexShaderName_; }
    /// Return pixel shader name
    const String& GetPixelShaderName() const { return pixelShaderName_; }
    /// Return vertex shaders
    Vector<SharedPtr<ShaderVariation> >& GetVertexShaders() { return vertexShaders_; }
    /// Return pixel shaders
    Vector<SharedPtr<ShaderVariation> >& GetPixelShaders() { return pixelShaders_; }
    
private:
    /// Pass type
    PassType type_;
    /// Alpha masking hint
    bool alphaMask_;
    /// Alpha test mode
    bool alphaTest_;
    /// Blend mode
    BlendMode blendMode_;
    /// Depth compare mode
    CompareMode depthTestMode_;
    /// Depth write mode
    bool depthWrite_;
    /// Vertex shader name
    String vertexShaderName_;
    /// Pixel shader name
    String pixelShaderName_;
    /// Vertex shaders
    Vector<SharedPtr<ShaderVariation> > vertexShaders_;
    /// Pixel shaders
    Vector<SharedPtr<ShaderVariation> > pixelShaders_;
};

/// Material technique. Consists of several passes
class Technique : public Resource
{
    OBJECT(Technique);
    
    friend class Renderer;
    
public:
    /// Construct
    Technique(Context* context);
    /// Destruct
    ~Technique();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Load resource. Return true if successful
    virtual bool Load(Deserializer& source);
    
    /// Set whether requires Shader Model 3
    void SetIsSM3(bool enable);
    /// Create a new pass
    Pass* CreatePass(PassType pass);
    /// Remove a pass
    void RemovePass(PassType pass);
    /// Reset shader pointers in all passes
    void ReleaseShaders();
    
    /// Mark shaders loaded this frame
    void MarkShadersLoaded(unsigned frameNumber);
    
    /// Return whether has a pass
    bool HasPass(PassType pass) const
    {
        return passes_.Find(pass) != passes_.End();
    }
    
    /// Return a pass
    Pass* GetPass(PassType pass)
    {
        Map<PassType, Pass>::Iterator i = passes_.Find(pass);
        if (i != passes_.End())
            return &(i->second_);
        else
            return 0;
    }
    
    /// Return whether requires Shader Model 3
    bool IsSM3() const { return isSM3_; }
    /// Return all passes
    const Map<PassType, Pass>& GetPasses() const { return passes_; }
    /// Return last shaders loaded frame number
    unsigned GetShadersLoadedFrameNumber() const { return shadersLoadedFrameNumber_; }
    
    /// Return name for pass
    static const String& GetPassName(PassType pass);
    
private:
    /// Require Shader Model 3 flag
    bool isSM3_;
    /// Last shaders loaded frame number
    unsigned shadersLoadedFrameNumber_;
    /// Passes
    Map<PassType, Pass> passes_;
};
