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
#include "HashMap.h"
#include "Object.h"

class Texture2D;
class XMLFile;

/// Post-processing effect pass
class PostProcessPass : public RefCounted
{
public:
    /// Construct.
    PostProcessPass();
    /// Destruct.
    ~PostProcessPass();
    
    /// %Set vertex shader name.
    void SetVertexShader(const String& name);
    /// %Set pixel shader name.
    void SetPixelShader(const String& name);
    /// %Set texture name. This can be a named rendertarget, or a texture resource name.
    void SetTexture(TextureUnit unit, const String& name);
    /// %Set shader parameter.
    void SetShaderParameter(const String& name, const Vector4& value);
    /// Remove shader parameter.
    void RemoveShaderParameter(const String& name);
    /// %Set output rendertarget name.
    void SetOutput(const String& name);
    
    /// Return vertex shader name.
    const String& GetVertexShader() const { return vertexShaderName_; }
    /// Return pixel shader name.
    const String& GetPixelShader() const { return pixelShaderName_; }
    /// Return texture name.
    const String& GetTexture(TextureUnit unit) const;
    /// Return all texture names.
    const String* GetTextures() const { return &textureNames_[0]; }
    /// Return shader parameter.
    const Vector4& GetShaderParameter(const String& name) const;
    /// Return all shader parameters.
    const HashMap<StringHash, Vector4>& GetShaderParameters() const { return shaderParameters_; }
    /// Return output rendertarget name.
    const String& GetOutput() const { return outputName_; }
    
private:
    /// Vertex shader name.
    String vertexShaderName_;
    /// Pixel shader name.
    String pixelShaderName_;
    /// Texture names by unit.
    String textureNames_[MAX_MATERIAL_TEXTURE_UNITS];
    /// Shader parameters.
    HashMap<StringHash, Vector4> shaderParameters_;
    /// Output rendertarget name.
    String outputName_;
};

/// Post-processing rendertarget.
struct PostProcessRenderTarget
{
    /// Texture format.
    unsigned format_;
    /// Size.
    IntVector2 size_;
    /// Divisor mode flag.
    bool sizeDivisor_;
    /// Filtering flag.
    bool filtered_;
};

/// Post-processing effect.
class PostProcess : public Object
{
    OBJECT(PostProcess);
    
public:
    /// Construct.
    PostProcess(Context* context);
    /// Destruct.
    ~PostProcess();
    
    /// Load parameters from an XML file. Return true if successful.
    bool LoadParameters(XMLFile* file);
    /// Set number of passes.
    void SetNumPasses(unsigned passes);
    /// Create a rendertarget. Width and height are either absolute pixels or viewport size divisors. Return true if successful.
    bool CreateRenderTarget(const String& name, unsigned width, unsigned height, unsigned format, bool sizeDivisor, bool filtered);
    /// Remove a rendertarget.
    void RemoveRenderTarget(const String& name);
    /// Set active flag.
    void SetActive(bool active);
    
    /// Return parameter XML file.
    XMLFile* GetParameters() const { return parameterSource_; }
    /// Return number of passes.
    unsigned GetNumPasses() const { return passes_.Size(); }
    /// Return pass by index.
    PostProcessPass* GetPass(unsigned index) const;
    /// Return if has a specific rendertarget.
    bool HasRenderTarget(const String& name) const;
    /// Return all rendertargets.
    const HashMap<StringHash, PostProcessRenderTarget>& GetRenderTargets() const { return renderTargets_; }
    
    /// Return active flag.
    bool IsActive() const { return active_; }
    
private:
    /// Parameter XML file.
    SharedPtr<XMLFile> parameterSource_;
    /// Effect passes.
    Vector<SharedPtr<PostProcessPass> > passes_;
    /// Rendertargets.
    HashMap<StringHash, PostProcessRenderTarget> renderTargets_;
    /// Active flag.
    bool active_;
};
