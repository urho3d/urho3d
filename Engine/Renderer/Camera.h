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

#ifndef RENDERER_CAMERA_H
#define RENDERER_CAMERA_H

#include "Frustum.h"
#include "Node.h"
#include "Ray.h"

static const unsigned VIEW_NONE = 0x0;
static const unsigned VIEW_MAIN = 0x1;
static const unsigned VIEW_REFLECTION = 0x2;
static const unsigned VIEW_CUBEREFLECTION = 0x4;
static const unsigned VIEW_ALL = 0xffffffff;

//! Scene node with projection parameters
class Camera : public Node
{
    DEFINE_TYPE(Camera);
    
public:
    //! Construct with name
    Camera(const std::string& name = std::string());
    //! Destruct
    virtual ~Camera();
    
    //! Write component state to a stream
    virtual void save(Serializer& dest);
    //! Read component state from a stream
    virtual void load(Deserializer& source, ResourceCache* cache);
    //! Write component state to an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read component state from an XML element
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    //! Write a network update
    virtual bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    //! Read a network update
    virtual void readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info);
    
    //! Set near clip distance
    void setNearClip(float nearClip);
    //! Set far clip distance
    void setFarClip(float farClip);
    //! Set field of view
    void setFov(float fov);
    //! Set orthographic mode view uniform size
    void setOrthoSize(float orthoSize);
    //! Set orthographic mode view size
    void setOrthoSize(const Vector2& orthoSize);
    //! Set aspect ratio
    void setAspectRatio(float aspectRatio);
    //! Set zoom
    void setZoom(float zoom);
    //! Set LOD bias
    void setLodBias(float bias);
    //! Set orthographic mode enabled/disabled
    void setOrthographic(bool enable);
    //! Set automatic aspect ratio based on viewport dimensions
    void setAutoAspectRatio(bool enable);
    //! Set view mask bits
    void setViewMask(unsigned mask);
    //! Override drawing of shadows
    void setDrawShadowsOverride(bool enable);
    //! Override light detail level
    void setLightDetailLevelOverride(int level);
    //! Override material quality
    void setMaterialQualityOverride(int quality);
    //! Override maximum number of occluder triangles
    void setMaxOccluderTrianglesOverride(int triangles);
    
    //! Return far clip distance
    float getFarClip() const { return mFarClip; }
    //! Return near clip distance
    float getNearClip() const;
    //! Return field of view
    float getFov() const { return mFov; }
    //! Return orthographic mode size
    float getOrthoSize() const { return mOrthoSize; } 
    //! Return aspect ratio
    float getAspectRatio() const { return mAspectRatio; }
    //! Return zoom
    float getZoom() const { return mZoom; }
    //! Return LOD bias
    float getLodBias() const { return mLodBias; }
    //! Return orthographic flag
    bool isOrthographic() const { return mOrthographic; }
    //! Return auto aspect ratio flag
    bool getAutoAspectRatio() const { return mAutoAspectRatio; }
    //! Return view mask bits
    unsigned getViewMask() const { return mViewMask; }
    //! Return draw shadows override
    bool getDrawShadowsOverride() const { return mDrawShadowsOverride; }
    //! Return light detail level override
    int getLightDetailLevelOverride() const { return mLightDetailLevelOverride; }
    //! Return material quality level override
    int getMaterialQualityOverride() const { return mMaterialQualityOverride; }
    //! Return occluder triangles maximum number override
    int getMaxOccluderTrianglesOverride() const { return mMaxOccluderTrianglesOverride; }
    //! Return inverse world transform matrix
    const Matrix4x3& getInverseWorldTransform();
    //! Return frustum in world space
    const Frustum& getFrustum();
    //! Return projection matrix
    const Matrix4& getProjection();
    //! Return frustum near vector
    const Vector3& getFrustumNearSize();
    //! Return frustum far vector
    const Vector3& getFrustumFarSize();
    //! Return half view size
    float getHalfViewSize() const;
    //! Return frustum transformed to view space
    Frustum getViewSpaceFrustum() const;
    //! Return frustum split by custom near and far clip distances
    Frustum getSplitFrustum(float nearClip, float farClip);
    //! Return ray corresponding to screen coordinates (0.0 to 1.0)
    Ray getScreenRay(float x, float y);
    //! Return forward vector
    Vector3 getForwardVector();
    //! Return right vector
    Vector3 getRightVector();
    //! Return up vector
    Vector3 getUpVector();
    //! Return distance to position. In orthographic mode uses only Z coordinate
    float getDistance(const Vector3& worldPos);
    //! Return squared distance to position. In orthographic mode uses only Z coordinate
    float getDistanceSquared(const Vector3& worldPos);
    //! Return a scene node's LOD scaled distance
    float getLodDistance(float distance, float scale, float bias) const;
    
protected:
    //! Transform has changed. Mark frustum and projection to need updating
    virtual void onMarkedDirty();
    
private:
    //! Mark projection to need updating
    void markProjectionDirty();
    //! Update frustum vectors
    void updateFrustumSize();
    
    //! Inverse world transform matrix
    Matrix4x3 mInverseWorldTransform;
    //! Projection matrix
    Matrix4 mProjection;
    //! Frustum
    Frustum mFrustum;
    //! Frustum near vector
    Vector3 mNear;
    //! Frustum far vector
    Vector3 mFar;
    //! Near clip distance
    float mNearClip;
    //! Far clip distance
    float mFarClip;
    //! Field of view
    float mFov;
    //! Orthographic view size
    float mOrthoSize;
    //! Aspect ratio
    float mAspectRatio;
    //! Zoom
    float mZoom;
    //! LOD bias
    float mLodBias;
    //! Orthographic mode flag
    bool mOrthographic;
    //! Auto aspect ratio flag
    bool mAutoAspectRatio;
    //! View mask bits
    unsigned mViewMask;
    //! Draw shadows override
    bool mDrawShadowsOverride;
    //! Light detail level override
    int mLightDetailLevelOverride;
    //! Material quality level override
    int mMaterialQualityOverride;
    //! Maximum occluder triangles override
    int mMaxOccluderTrianglesOverride;
    //! Last visible frame number
    unsigned mInViewFrameNumber;
    //! Inverse world transform matrix dirty flag
    bool mInverseWorldTransformDirty;
    //! Frustum needs update flag
    bool mFrustumDirty;
    //! Projection matrix needs update flag
    bool mProjectionDirty;
    //! Frustum vectors need update flag
    bool mFrustumSizeDirty;
};

#endif // RENDERER_CAMERA_H
