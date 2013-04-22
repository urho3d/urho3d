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
#include "Light.h"
#include "Resource.h"
#include "Vector4.h"

namespace Urho3D
{

class Pass;
class Technique;
class Texture;
class Texture2D;
class TextureCube;

/// %Material's shader parameter definition.
struct MaterialShaderParameter
{
    /// Name.
    String name_;
    /// Value.
    Vector4 value_;
};

/// %Material's technique list entry.
struct TechniqueEntry
{
    /// Construct with defaults.
    TechniqueEntry();
    /// Construct with parameters.
    TechniqueEntry(Technique* tech, unsigned qualityLevel, float lodDistance);
    /// Destruct.
    ~TechniqueEntry();
    
    /// Technique.
    SharedPtr<Technique> technique_;
    /// Quality level.
    int qualityLevel_;
    /// LOD distance.
    float lodDistance_;
};

/// Describes how to render 3D geometries.
class Material : public Resource
{
    OBJECT(Material);
    
public:
    /// Construct.
    Material(Context* context);
    /// Destruct.
    ~Material();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Load resource. Return true if successful.
    virtual bool Load(Deserializer& source);
    /// Save resource. Return true if successful.
    virtual bool Save(Serializer& dest) const;
    
    /// Set number of techniques.
    void SetNumTechniques(unsigned num);
    /// Set technique.
    void SetTechnique(unsigned index, Technique* tech, unsigned qualityLevel = 0, float lodDistance = 0.0f);
    /// Set shader parameter.
    void SetShaderParameter(const String& name, const Vector4& value);
    /// Set texture.
    void SetTexture(TextureUnit unit, Texture* texture);
    /// Set texture coordinate transform.
    void SetUVTransform(const Vector2& offset, float rotation, const Vector2& repeat);
    /// Set texture coordinate transform.
    void SetUVTransform(const Vector2& offset, float rotation, float repeat);
    /// Set culling mode.
    void SetCullMode(CullMode mode);
    /// Set culling mode for shadows.
    void SetShadowCullMode(CullMode mode);
    /// Set depth bias.
    void SetDepthBias(const BiasParameters& parameters);
    /// Remove shader parameter.
    void RemoveShaderParameter(const String& name);
    /// Reset all shader pointers.
    void ReleaseShaders();
    /// Clone material.
    SharedPtr<Material> Clone(const String& cloneName = String::EMPTY) const;
    /// Mark material for auxiliary view rendering.
    void MarkForAuxView(unsigned frameNumber);
    
    /// Return number of techniques.
    unsigned GetNumTechniques() const { return techniques_.Size(); }
    /// Return all techniques.
    const Vector<TechniqueEntry>& GetTechniques() const { return techniques_; }
    /// Return technique entry by index.
    const TechniqueEntry& GetTechniqueEntry(unsigned index) const;
    /// Return technique by index.
    Technique* GetTechnique(unsigned index) const;
    /// Return pass by technique index and pass type.
    Pass* GetPass(unsigned index, StringHash passType) const;
    /// Return texture by unit.
    Texture* GetTexture(TextureUnit unit) const;
   /// Return all textures.
    const SharedPtr<Texture>* GetTextures() const { return &textures_[0]; }
    /// Return shader parameter.
    const Vector4& GetShaderParameter(const String& name) const;
    /// Return all shader parameters.
    const HashMap<StringHash, MaterialShaderParameter>& GetShaderParameters() const { return shaderParameters_; }
    /// Return normal culling mode.
    CullMode GetCullMode() const { return cullMode_; }
    /// Return culling mode for shadows.
    CullMode GetShadowCullMode() const { return shadowCullMode_; }
    /// Return depth bias.
    const BiasParameters& GetDepthBias() const { return depthBias_; }
    /// Return last auxiliary view rendered frame number.
    unsigned GetAuxViewFrameNumber() const { return auxViewFrameNumber_; }
    /// Return whether should render occlusion.
    bool GetOcclusion() const { return occlusion_; }
    /// Return whether should render specular.
    bool GetSpecular() const { return specular_; }
    
    /// Return name for texture unit.
    static const String& GetTextureUnitName(TextureUnit unit);
    
private:
    /// Re-evaluate occlusion rendering.
    void CheckOcclusion();
    /// Reset to defaults.
    void ResetToDefaults();
    
    /// Techniques.
    Vector<TechniqueEntry> techniques_;
    /// Textures.
    SharedPtr<Texture> textures_[MAX_MATERIAL_TEXTURE_UNITS];
    /// %Shader parameters.
    HashMap<StringHash, MaterialShaderParameter> shaderParameters_;
    /// Normal culling mode.
    CullMode cullMode_;
    /// Culling mode for shadow rendering.
    CullMode shadowCullMode_;
    /// Depth bias parameters.
    BiasParameters depthBias_;
    /// Last auxiliary view rendered frame number.
    unsigned auxViewFrameNumber_;
    /// Render occlusion flag.
    bool occlusion_;
    /// Specular lighting flag.
    bool specular_;
};

}
