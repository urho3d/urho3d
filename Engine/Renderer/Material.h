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

#ifndef RENDERER_MATERIAL_H
#define RENDERER_MATERIAL_H

#include "Color.h"
#include "RendererDefs.h"
#include "Resource.h"
#include "ShaderDefs.h"
#include "SharedPtr.h"
#include "Vector4.h"

class Material;
class PixelShader;
class Texture;
class Texture2D;
class TextureCube;
class VertexShader;

//! Material rendering pass
class MaterialPass
{
public:
    //! Construct with default values
    MaterialPass();
    //! Destruction
    ~MaterialPass();
    
    //! Set alpha masking hint on/off
    void setAlphaMask(bool enable);
    //! Set alpha test on/off
    void setAlphaTest(bool enable);
    //! Set blend mode
    void setBlendMode(BlendMode mode);
    //! Set hardware culling mode
    void setCullMode(CullMode mode);
    //! Set depth compare mode
    void setDepthTestMode(CompareMode mode);
    //! Set depth write on/off
    void setDepthWrite(bool enable);
    //! Set vertex shader name
    void setVertexShader(const std::string& name);
    //! Set pixel shader name
    void setPixelShader(const std::string& name);
    //! Reset shader pointers
    void releaseShaders();
    
    //! Set parent material
    void setParent(Material* parent);
    
    //! Return parent material
    Material* getParent() const { return mParent; }
    //! Return alpha masking hint
    bool getAlphaMask() const { return mAlphaMask; }
    //! Return alpha test mode
    bool getAlphaTest() const { return mAlphaTest; }
    //! Return blend mode
    BlendMode getBlendMode() const { return mBlendMode; }
    //! Return hardware culling mode
    CullMode getCullMode() const { return mCullMode; }
    //! Return depth compare mode
    CompareMode getDepthTestMode() const { return mDepthTestMode; }
    //! Return depth write mode
    bool getDepthWrite() const { return mDepthWrite; }
    //! Return vertex shader name
    const std::string& getVertexShaderName() const { return mVertexShaderName; }
    //! Return pixel shader name
    const std::string& getPixelShaderName() const { return mPixelShaderName; }
    //! Return vertex shaders
    std::vector<SharedPtr<VertexShader> >& getVertexShaders() { return mVertexShaders; }
    //! Return pixel shaders
    std::vector<SharedPtr<PixelShader> >& getPixelShaders() { return mPixelShaders; }
    
private:
    //! Parent material
    Material* mParent;
    //! Alpha masking hint
    bool mAlphaMask;
    //! Alpha test mode
    bool mAlphaTest;
    //! Blend mode
    BlendMode mBlendMode;
    //! Hardware culling mode
    CullMode mCullMode;
    //! Depth compare mode
    CompareMode mDepthTestMode;
    //! Depth write mode
    bool mDepthWrite;
    //! Vertex shader name
    std::string mVertexShaderName;
    //! Pixel shader name
    std::string mPixelShaderName;
    //! Vertex shaders
    std::vector<SharedPtr<VertexShader> > mVertexShaders;
    //! Pixel shaders
    std::vector<SharedPtr<PixelShader> > mPixelShaders;
};

//! Material technique. Consists of several passes
class MaterialTechnique
{
    friend class Pipeline;
    
public:
    //! Construct with default values
    MaterialTechnique();
    //! Destruct
    ~MaterialTechnique();
    
    //! Set quality level
    void setQualityLevel(int quality);
    //! Set LOD distance
    void setLodDistance(float distance);
    //! Set whether requires Shader Model 3
    void setRequireSM3(bool enable);
    //! Set a vertex shader parameter
    void setVertexShaderParameter(VSParameter parameter, const Vector4& value);
    //! Set a pixel shader parameter
    void setPixelShaderParameter(PSParameter parameter, const Vector4& value);
    //! Set a texture
    void setTexture(TextureUnit unit, Texture* texture);
    //! Set texture coordinate transform
    void setUVTransform(const Vector2& offset, float rotation, const Vector2& repeat);
    //! Set texture coordinate transform
    void setUVTransform(const Vector2& offset, float rotation, float repeat);
    //! Create a new pass
    MaterialPass* createPass(PassType pass);
    //! Remove a pass
    void removePass(PassType pass);
    //! Reset shader pointers in all passes
    void releaseShaders();
    
    //! Set parent material
    void setParent(Material* parent);
    //! Mark for rendering an auxiliary view this frame
    void markForAuxView(unsigned frameNumber);
    //! Mark shaders loaded this frame
    void markShadersLoaded(unsigned frameNumber);
    
    //! Return whether has a pass
    bool hasPass(PassType pass) const
    {
        return mPasses.find(pass) != mPasses.end();
    }
    
    //! Return a pass
    MaterialPass* getPass(PassType pass)
    {
        std::map<PassType, MaterialPass>::iterator i = mPasses.find(pass);
        if (i != mPasses.end())
            return &(i->second);
        else
            return 0;
    }
    
    //! Return parent material
    Material* getParent() const { return mParent; }
    //! Return quality level
    int getQualityLevel() const { return mQualityLevel; }
    //! Return LOD distance
    float getLodDistance() const { return mLodDistance; }
    //! Return whether requires Shader Model 3
    bool getRequireSM3() const { return mRequireSM3; }
    //! Return all passes
    const std::map<PassType, MaterialPass>& getPasses() const { return mPasses; }
    //! Return all textures
    const std::vector<SharedPtr<Texture> >& getTextures() const { return mTextures; }
    //! Return texture by unit
    Texture* getTexture(TextureUnit unit) const;
    //! Return all vertex shader parameters
    const std::map<VSParameter, Vector4>& getVertexShaderParameters() const { return mVSParameters; }
    //! Return all pixel shader parameters
    const std::map<PSParameter, Vector4>& getPixelShaderParameters() const { return mPSParameters; }
    //! Return last auxiliary view rendered frame number
    unsigned getAuxViewFrameNumber() const { return mAuxViewFrameNumber; }
    //! Return last shaders loaded frame number
    unsigned getShadersLoadedFrameNumber() const { return mShadersLoadedFrameNumber; }
    
private:
    //! Parent material
    Material* mParent;
    //! Quality level
    int mQualityLevel;
    //! LOD distance
    float mLodDistance;
    //! Require Shader Model 3 flag
    bool mRequireSM3;
    //! Last auxiliary view rendered frame number
    unsigned mShadersLoadedFrameNumber;
    //! Last shaders loaded frame number
    unsigned mAuxViewFrameNumber;
    //! Passes
    std::map<PassType, MaterialPass> mPasses;
    //! Textures
    std::vector<SharedPtr<Texture> > mTextures;
    //! Vertex shader parameters
    std::map<VSParameter, Vector4> mVSParameters;
    //! Pixel shader parameters
    std::map<PSParameter, Vector4> mPSParameters;
};

//! Describes how to render geometries
class Material : public Resource
{
    DEFINE_TYPE(Material);
    
public:
    //! Construct with name and one default technique
    Material(const std::string& name = std::string());
    //! Destruct
    ~Material();
    
    //! Load resource
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    
    //! Set number of techniques
    void setNumTechniques(unsigned num);
    //! Set vertex shader parameter in all techniques
    void setVertexShaderParameter(VSParameter parameter, const Vector4& value);
    //! Set pixel shader parameter in all techniques
    void setPixelShaderParameter(PSParameter parameter, const Vector4& value);
    //! Set texture in all techniques
    void setTexture(TextureUnit unit, Texture* texture);
    //! Set texture coordinate transform in all techniques
    void setUVTransform(const Vector2& offset, float rotation, const Vector2& repeat);
    //! Set texture coordinate transform in all techniques
    void setUVTransform(const Vector2& offset, float rotation, float repeat);
    //! Mark needing shadow casting and occlusion re-evaluation
    void setDirty();
    //! Reset all shader pointers
    void releaseShaders();
    //! Clone material
    SharedPtr<Material> clone(const std::string& cloneName = std::string()) const;
    
    //! Return number of techniques
    unsigned getNumTechniques() const { return mTechniques.size(); }
    //! Return technique by index
    MaterialTechnique* getTechnique(unsigned index);
    //! Return pass
    MaterialPass* getPass(unsigned technique, PassType pass);
    //! Return whether casts shadows
    bool getCastShadows();
    //! Return whether should render occlusion
    bool getOcclusion();
    //! Return culling mode for occlusion rendering
    CullMode getOcclusionCullMode();
    
    //! Return name for pass
    static const std::string& getPassName(PassType pass);
    
private:
    //! Re-evaluate shadow casting and occlusion rendering
    void update();
    
    //! Techniques
    std::vector<MaterialTechnique> mTechniques;
    //! Needs shadow casting and occlusion re-evaluation flag
    bool mDirty;
    //! Casts shadows flag
    bool mCastShadows;
    //! Should render occlusion flag
    bool mOcclusion;
    //! Culling mode for occlusion rendering
    CullMode mOcclusionCullMode;
};

#endif // RENDERER_MATERIAL_H
