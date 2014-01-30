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

#include "GraphicsDefs.h"
#include "HashTable.h"
#include "Resource.h"

namespace Urho3D
{

class ShaderVariation;

/// Lighting mode of a pass.
enum PassLightingMode
{
    LIGHTING_UNLIT,
    LIGHTING_PERVERTEX,
    LIGHTING_PERPIXEL
};

/// %Material rendering pass, which defines shaders and render state.
class URHO3D_API Pass : public RefCounted
{
public:
    /// Construct.
    Pass(StringHash type);
    /// Destruct.
    ~Pass();
    
    /// Set blend mode.
    void SetBlendMode(BlendMode mode);
    /// Set depth compare mode.
    void SetDepthTestMode(CompareMode mode);
    /// Set pass lighting mode, affects what shader variations will be attempted to be loaded.
    void SetLightingMode(PassLightingMode mode);
    /// Set depth write on/off.
    void SetDepthWrite(bool enable);
    /// Set alpha masking hint. Completely opaque draw calls will be performed before alpha masked.
    void SetAlphaMask(bool enable);
    /// Set vertex shader name.
    void SetVertexShader(const String& name);
    /// Set pixel shader name.
    void SetPixelShader(const String& name);
    /// Set vertex shader defines.
    void SetVertexShaderDefines(const String& defines);
    /// Set pixel shader defines.
    void SetPixelShaderDefines(const String& defines);
    /// Reset shader pointers.
    void ReleaseShaders();
    /// Mark shaders loaded this frame.
    void MarkShadersLoaded(unsigned frameNumber);
    
    /// Return pass type.
    const StringHash& GetType() const { return type_; }
    /// Return blend mode.
    BlendMode GetBlendMode() const { return blendMode_; }
    /// Return depth compare mode.
    CompareMode GetDepthTestMode() const { return depthTestMode_; }
    /// Return pass lighting mode.
    PassLightingMode GetLightingMode() const { return lightingMode_; }
    /// Return last shaders loaded frame number.
    unsigned GetShadersLoadedFrameNumber() const { return shadersLoadedFrameNumber_; }
    /// Return depth write mode.
    bool GetDepthWrite() const { return depthWrite_; }
    /// Return alpha masking hint.
    bool GetAlphaMask() const { return alphaMask_; }
    /// Return vertex shader name.
    const String& GetVertexShader() const { return vertexShaderName_; }
    /// Return pixel shader name.
    const String& GetPixelShader() const { return pixelShaderName_; }
    /// Return vertex shader defines.
    const String& GetVertexShaderDefines() const { return vertexShaderDefines_; }
    /// Return pixel shader defines.
    const String& GetPixelShaderDefines() const { return pixelShaderDefines_; }
    /// Return vertex shaders.
    Vector<SharedPtr<ShaderVariation> >& GetVertexShaders() { return vertexShaders_; }
    /// Return pixel shaders.
    Vector<SharedPtr<ShaderVariation> >& GetPixelShaders() { return pixelShaders_; }
    
private:
    /// Pass type.
    StringHash type_;
    /// Blend mode.
    BlendMode blendMode_;
    /// Depth compare mode.
    CompareMode depthTestMode_;
    /// Lighting mode.
    PassLightingMode lightingMode_;
    /// Last shaders loaded frame number.
    unsigned shadersLoadedFrameNumber_;
    /// Depth write mode.
    bool depthWrite_;
    /// Alpha masking hint.
    bool alphaMask_;
    /// Vertex shader name.
    String vertexShaderName_;
    /// Pixel shader name.
    String pixelShaderName_;
    /// Vertex shader defines.
    String vertexShaderDefines_;
    /// Pixel shader defines.
    String pixelShaderDefines_;
    /// Vertex shaders.
    Vector<SharedPtr<ShaderVariation> > vertexShaders_;
    /// Pixel shaders.
    Vector<SharedPtr<ShaderVariation> > pixelShaders_;
};

/// %Material technique. Consists of several passes.
class URHO3D_API Technique : public Resource
{
    OBJECT(Technique);
    
    friend class Renderer;
    
public:
    /// Construct.
    Technique(Context* context);
    /// Destruct.
    ~Technique();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Load resource. Return true if successful.
    virtual bool Load(Deserializer& source);
    
    /// Set whether requires %Shader %Model 3.
    void SetIsSM3(bool enable);
    /// Create a new pass.
    Pass* CreatePass(StringHash type);
    /// Remove a pass.
    void RemovePass(StringHash type);
    /// Reset shader pointers in all passes.
    void ReleaseShaders();
    
    /// Return whether requires %Shader %Model 3.
    bool IsSM3() const { return isSM3_; }
    /// Return whether has a pass.
    bool HasPass(StringHash type) const { return  passes_.Find(type.Value()) != 0; }
    
    /// Return a pass, or null if not found.
    Pass* GetPass(StringHash type) const
    {
        SharedPtr<Pass>* passPtr = passes_.Find(type.Value());
        return passPtr ? passPtr->Get() : 0;
    }
    
private:
    /// Require %Shader %Model 3 flag.
    bool isSM3_;
    /// Passes.
    HashTable<SharedPtr<Pass>, 16> passes_;
};

}
