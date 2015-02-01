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
#include "../Graphics/Light.h"
#include "../Resource/Resource.h"
#include "../Scene/ValueAnimationInfo.h"
#include "../Math/Vector4.h"

namespace Urho3D
{

class Material;
class Pass;
class Scene;
class Technique;
class Texture;
class Texture2D;
class TextureCube;
class ValueAnimationInfo;

/// %Material's shader parameter definition.
struct MaterialShaderParameter
{
    /// Name.
    String name_;
    /// Value.
    Variant value_;
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

/// Material's shader parameter animation instance.
class ShaderParameterAnimationInfo : public ValueAnimationInfo
{
public:
    /// Construct.
    ShaderParameterAnimationInfo(Material* material, const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed);
    /// Copy construct.
    ShaderParameterAnimationInfo(const ShaderParameterAnimationInfo& other);
    /// Destruct.
    ~ShaderParameterAnimationInfo();

    /// Return shader parameter name.
    const String& GetName() const { return name_; }

protected:
    /// Apply new animation value to the target object. Called by Update().
    virtual void ApplyValue(const Variant& newValue);
    
private:
    /// Shader parameter name.
    String name_;
};

/// Describes how to render 3D geometries.
class URHO3D_API Material : public Resource
{
    OBJECT(Material);

public:
    /// Construct.
    Material(Context* context);
    /// Destruct.
    ~Material();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    virtual bool EndLoad();
    /// Save resource. Return true if successful.
    virtual bool Save(Serializer& dest) const;

    /// Load from an XML element. Return true if successful.
    bool Load(const XMLElement& source);
    /// Save to an XML element. Return true if successful.
    bool Save(XMLElement& dest) const;
    /// Set number of techniques.
    void SetNumTechniques(unsigned num);
    /// Set technique.
    void SetTechnique(unsigned index, Technique* tech, unsigned qualityLevel = 0, float lodDistance = 0.0f);
    /// Set shader parameter.
    void SetShaderParameter(const String& name, const Variant& value);
    /// Set shader parameter animation.
    void SetShaderParameterAnimation(const String& name, ValueAnimation* animation, WrapMode wrapMode = WM_LOOP, float speed = 1.0f);
    /// Set shader parameter animation wrap mode.
    void SetShaderParameterAnimationWrapMode(const String& name, WrapMode wrapMode);
    /// Set shader parameter animation speed.
    void SetShaderParameterAnimationSpeed(const String& name, float speed);
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
    /// Associate the material with a scene to ensure that shader parameter animation happens in sync with scene update, respecting the scene time scale. If no scene is set, the global update events will be used.
    void SetScene(Scene* scene);
    /// Remove shader parameter.
    void RemoveShaderParameter(const String& name);
    /// Reset all shader pointers.
    void ReleaseShaders();
    /// Clone the material.
    SharedPtr<Material> Clone(const String& cloneName = String::EMPTY) const;
    /// Ensure that material techniques are listed in correct order.
    void SortTechniques();
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
    const Variant& GetShaderParameter(const String& name) const;
    /// Return shader parameter animation.
    ValueAnimation* GetShaderParameterAnimation(const String& name) const;
    /// Return shader parameter animation wrap mode.
    WrapMode GetShaderParameterAnimationWrapMode(const String& name) const;
    /// Return shader parameter animation speed.
    float GetShaderParameterAnimationSpeed(const String& name) const;
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
    /// Return the scene associated with the material for shader parameter animation updates.
    Scene* GetScene() const;
    /// Return the last non-null texture unit + 1. Used as an optimization when applying the material to render state.
    unsigned GetNumUsedTextureUnits() const { return numUsedTextureUnits_; }
    /// Return shader parameter hash value. Used as an optimization to avoid setting shader parameters unnecessarily.
    unsigned GetShaderParameterHash() const { return shaderParameterHash_; }

    /// Return name for texture unit.
    static String GetTextureUnitName(TextureUnit unit);
    /// Parse a shader parameter value from a string. Retunrs either a bool, a float, or a 2 to 4-component vector.
    static Variant ParseShaderParameterValue(const String& value);

private:
    /// Re-evaluate occlusion rendering.
    void CheckOcclusion();
    /// Reset to defaults.
    void ResetToDefaults();
    /// Recalculate shader parameter hash.
    void RefreshShaderParameterHash();
    /// Recalculate the memory used by the material.
    void RefreshMemoryUse();
    /// Return shader parameter animation info.
    ShaderParameterAnimationInfo* GetShaderParameterAnimationInfo(const String& name) const;
    /// Update whether should be subscribed to scene or global update events for shader parameter animation.
    void UpdateEventSubscription();
    /// Update shader parameter animations.
    void HandleAttributeAnimationUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Techniques.
    Vector<TechniqueEntry> techniques_;
    /// Textures.
    SharedPtr<Texture> textures_[MAX_TEXTURE_UNITS];
    /// %Shader parameters.
    HashMap<StringHash, MaterialShaderParameter> shaderParameters_;
    /// %Shader parameters animation infos.
    HashMap<StringHash, SharedPtr<ShaderParameterAnimationInfo> > shaderParameterAnimationInfos_;
    /// Normal culling mode.
    CullMode cullMode_;
    /// Culling mode for shadow rendering.
    CullMode shadowCullMode_;
    /// Depth bias parameters.
    BiasParameters depthBias_;
    /// Last auxiliary view rendered frame number.
    unsigned auxViewFrameNumber_;
    /// Number of maximum non-null texture unit + 1.
    unsigned numUsedTextureUnits_;
    /// Shader parameter hash value.
    unsigned shaderParameterHash_;
    /// Render occlusion flag.
    bool occlusion_;
    /// Specular lighting flag.
    bool specular_;
    /// Flag for whether is subscribed to animation updates.
    bool subscribed_;
    /// Flag to suppress parameter hash and memory use recalculation when setting multiple shader parameters (loading or resetting the material.)
    bool batchedParameterUpdate_;
    /// XML file used while loading.
    SharedPtr<XMLFile> loadXMLFile_;
    /// Associated scene for shader parameter animation updates.
    WeakPtr<Scene> scene_;
};

}
