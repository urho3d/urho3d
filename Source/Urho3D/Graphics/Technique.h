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

#pragma once

#include "../Graphics/GraphicsDefs.h"
#include "../Container/HashTable.h"
#include "../Resource/Resource.h"

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
    /// Set whether requires %Shader %Model 3.
    void SetIsSM3(bool enable);
    /// Set whether requires desktop level hardware.
    void SetIsDesktop(bool enable);
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
    /// Return whether requires %Shader %Model 3.
    bool IsSM3() const { return isSM3_; }
    /// Return whether requires desktop level hardware.
    bool IsDesktop() const { return isDesktop_; }
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
    /// Require %Shader %Model 3 flag.
    bool isSM3_;
    /// Require desktop level hardware flag.
    bool isDesktop_;
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
    
    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);
    
    /// Set whether requires %Shader %Model 3.
    void SetIsSM3(bool enable);
    /// Set whether requires desktop level hardware.
    void SetIsDesktop(bool enable);
    /// Create a new pass.
    Pass* CreatePass(StringHash type);
    /// Remove a pass.
    void RemovePass(StringHash type);
    /// Reset shader pointers in all passes.
    void ReleaseShaders();
    
    /// Return whether requires %Shader %Model 3.
    bool IsSM3() const { return isSM3_; }
    /// Return whether requires desktop level hardware.
    bool IsDesktop() const { return isDesktop_; }
    /// Return whether technique is supported by the current hardware.
    bool IsSupported() const { return (!isSM3_ || sm3Support_) && (!isDesktop_ || desktopSupport_); }
    /// Return whether has a pass.
    bool HasPass(StringHash type) const { return  passes_.Find(type.Value()) != 0; }
    
    /// Return a pass, or null if not found.
    Pass* GetPass(StringHash type) const
    {
        SharedPtr<Pass>* passPtr = passes_.Find(type.Value());
        return passPtr ? passPtr->Get() : 0;
    }
    
    /// Return a pass that is supported for rendering, or null if not found.
    Pass* GetSupportedPass(StringHash type) const
    {
        SharedPtr<Pass>* passPtr = passes_.Find(type.Value());
        Pass* pass = passPtr ? passPtr->Get() : 0;
        return pass && (!pass->IsSM3() || sm3Support_) && (!pass->IsDesktop() || desktopSupport_) ? pass : 0;
    }
    
    /// Return number of passes.
    unsigned GetNumPasses() const { return numPasses_; }
    /// Return all the pass types in the hash table. The returned collection is not guaranteed to be in the same order as the hash table insertion order.
    Vector<StringHash> GetPassTypes() const;
    /// Return all the passes in the hash table. The returned collection is not guaranteed to be in the same order as the hash table insertion order.
    PODVector<Pass*> GetPasses() const;

private:
    /// Require %Shader %Model 3 flag.
    bool isSM3_;
    /// Cached %Shader %Model 3 support flag.
    bool sm3Support_;
    /// Require desktop GPU flag.
    bool isDesktop_;
    /// Cached desktop GPU support flag.
    bool desktopSupport_;
    /// Passes.
    HashTable<SharedPtr<Pass>, 16> passes_;
    /// Number of passes.
    unsigned numPasses_;
};

}
