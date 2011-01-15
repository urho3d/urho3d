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

#include "Precompiled.h"
#include "Camera.h"
#include "RendererDefs.h"
#include "ReplicationUtils.h"
#include "XMLElement.h"

#include <cstring>

#include "DebugNew.h"

static const float DEFAULT_NEARCLIP = 0.1f;
static const float DEFAULT_FARCLIP = 1000.0f;
static const float DEFAULT_FOV = 45.0f;
static const float DEFAULT_ORTHOSIZE = 20.0f;

Camera::Camera(const std::string& name) :
    Node(NODE_CAMERA, name),
    mNearClip(DEFAULT_NEARCLIP),
    mFarClip(DEFAULT_FARCLIP),
    mFov(DEFAULT_FOV),
    mOrthoSize(DEFAULT_ORTHOSIZE),
    mAspectRatio(1.0f),
    mZoom(1.0f),
    mLodBias(1.0f),
    mOrthographic(false),
    mViewMask(VIEW_MAIN),
    mDrawShadowsOverride(true),
    mLightDetailLevelOverride(QUALITY_MAX),
    mMaterialQualityOverride(QUALITY_MAX),
    mMaxOccluderTrianglesOverride(M_MAX_INT),
    mInViewFrameNumber(M_MAX_UNSIGNED),
    mInverseWorldTransformDirty(true),
    mFrustumDirty(true),
    mProjectionDirty(true),
    mFrustumSizeDirty(true)
{
}

Camera::~Camera()
{
}

void Camera::save(Serializer& dest)
{
    // Write Node properties
    Node::save(dest);
    
    // Write Camera properties
    dest.writeFloat(mNearClip);
    dest.writeFloat(mFarClip);
    dest.writeFloat(mFov);
    dest.writeFloat(mOrthoSize);
    dest.writeFloat(mAspectRatio);
    dest.writeFloat(mZoom);
    dest.writeFloat(mLodBias);
    dest.writeBool(mOrthographic);
    dest.writeUInt(mViewMask);
    dest.writeBool(mDrawShadowsOverride);
    dest.writeUByte(mLightDetailLevelOverride);
    dest.writeUByte(mMaterialQualityOverride);
    dest.writeInt(mMaxOccluderTrianglesOverride);
}

void Camera::load(Deserializer& source, ResourceCache* cache)
{
    // Read Node properties
    Node::load(source, cache);
    
    // Read Camera properties
    mNearClip = source.readFloat();
    mFarClip = source.readFloat();
    mFov = source.readFloat();
    mOrthoSize = source.readFloat();
    mAspectRatio = source.readFloat();
    mZoom = source.readFloat();
    mLodBias = source.readFloat();
    mOrthographic = source.readBool();
    mViewMask = source.readUInt();
    mDrawShadowsOverride = source.readBool();
    mLightDetailLevelOverride = source.readUByte();
    mMaterialQualityOverride = source.readUByte();
    mMaxOccluderTrianglesOverride = source.readInt();
    
    markProjectionDirty();
}

void Camera::saveXML(XMLElement& dest)
{
    // Write Node properties
    Node::saveXML(dest);
    
    // Write Camera properties
    XMLElement projectionElem = dest.createChildElement("projection");
    projectionElem.setFloat("nearclip", mNearClip);
    projectionElem.setFloat("farclip", mFarClip);
    projectionElem.setBool("orthographic", mOrthographic);
    projectionElem.setFloat("fov", mFov);
    projectionElem.setFloat("orthosize", mOrthoSize);
    projectionElem.setFloat("aspectratio", mAspectRatio);
    projectionElem.setFloat("zoom", mZoom);
    
    XMLElement lodElem = dest.createChildElement("lod");
    lodElem.setInt("viewmask", mViewMask);
    lodElem.setFloat("lodbias", mLodBias);
    
    XMLElement overrideElem = dest.createChildElement("override");
    overrideElem.setBool("drawshadows", mDrawShadowsOverride);
    overrideElem.setInt("lightdetail", mLightDetailLevelOverride);
    overrideElem.setInt("matquality", mMaterialQualityOverride);
    overrideElem.setInt("occludertris", mMaxOccluderTrianglesOverride);
}

void Camera::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read Node properties
    Node::loadXML(source, cache);
    
    // Read Camera properties
    XMLElement projectionElem = source.getChildElement("projection");
    mNearClip = projectionElem.getFloat("nearclip");
    mFarClip  = projectionElem.getFloat("farclip");
    mOrthographic = projectionElem.getBool("orthographic");
    mFov = projectionElem.getFloat("fov");
    mOrthoSize = projectionElem.getFloat("orthosize");
    mAspectRatio = projectionElem.getFloat("aspectratio");
    mZoom = projectionElem.getFloat("zoom");
    
    XMLElement lodElem = source.getChildElement("lod");
    mViewMask = lodElem.getInt("viewmask");
    mLodBias = lodElem.getFloat("lodbias");
    
    XMLElement overrideElem = source.getChildElement("override");
    mDrawShadowsOverride = overrideElem.getBool("drawshadows");
    mLightDetailLevelOverride = overrideElem.getInt("lightdetail");
    mMaterialQualityOverride = overrideElem.getInt("matquality");
    mMaxOccluderTrianglesOverride = overrideElem.getInt("occludertris");
}

bool Camera::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    // Write Node properties and see if there were any changes
    bool prevBits = Node::writeNetUpdate(dest, destRevision, baseRevision, info);
    
    // Build bitmask of changed properties
    unsigned char bits = 0;
    unsigned char qualityOverrides = mLightDetailLevelOverride | (mMaterialQualityOverride << 4);
    checkFloat(mNearClip, DEFAULT_NEARCLIP, baseRevision, bits, 1);
    checkFloat(mFarClip, DEFAULT_FARCLIP, baseRevision, bits, 1);
    checkFloat(mFov, DEFAULT_FOV, baseRevision, bits, 2);
    checkFloat(mOrthoSize, DEFAULT_ORTHOSIZE, baseRevision, bits, 4);
    checkFloat(mAspectRatio, 1.0f, baseRevision, bits, 4);
    checkBool(mOrthographic, false, baseRevision, bits, 4);
    checkFloat(mZoom, 1.0f, baseRevision, bits, 8);
    checkFloat(mLodBias, 1.0f, baseRevision, bits, 16);
    checkUInt(mViewMask, VIEW_ALL, baseRevision, bits, 32);
    checkBool(mDrawShadowsOverride, true, baseRevision, bits, 64);
    checkUByte(qualityOverrides, QUALITY_MAX | (QUALITY_MAX << 4), baseRevision, bits, 64);
    checkInt(mMaxOccluderTrianglesOverride, M_MAX_INT, baseRevision, bits, 64);
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    writeFloatDelta(mNearClip, dest, destRevision, bits & 1);
    writeFloatDelta(mFarClip, dest, destRevision, bits & 1);
    writeFloatDelta(mFov, dest, destRevision, bits & 2);
    writeFloatDelta(mOrthoSize, dest, destRevision, bits & 4);
    writeFloatDelta(mAspectRatio, dest, destRevision, bits & 4);
    writeBoolDelta(mOrthographic, dest, destRevision, bits & 4);
    writeFloatDelta(mZoom, dest, destRevision, bits & 8);
    writeFloatDelta(mLodBias, dest, destRevision, bits & 16);
    writeUIntDelta(mViewMask, dest, destRevision, bits & 32);
    writeBoolDelta(mDrawShadowsOverride, dest, destRevision, bits & 64);
    writeUByteDelta(qualityOverrides, dest, destRevision, bits & 64);
    writeIntDelta(mMaxOccluderTrianglesOverride, dest, destRevision, bits & 64);
    
    return prevBits || (bits != 0);
}

void Camera::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    // Read Node properties
    Node::readNetUpdate(source, cache, info);
    
    unsigned char bits = source.readUByte();
    readFloatDelta(mNearClip, source, bits & 1);
    readFloatDelta(mFarClip, source, bits & 1);
    readFloatDelta(mFov, source, bits & 2);
    readFloatDelta(mOrthoSize, source, bits & 4);
    readFloatDelta(mAspectRatio, source, bits & 4);
    readBoolDelta(mOrthographic, source, bits & 4);
    readFloatDelta(mZoom, source, bits & 8);
    readFloatDelta(mLodBias, source, bits & 16);
    readUIntDelta(mViewMask, source, bits & 32);
    if (bits & 64)
    {
        mDrawShadowsOverride = source.readBool();
        unsigned char qualityOverrides = source.readUByte();
        mLightDetailLevelOverride = qualityOverrides & 15;
        mMaterialQualityOverride = qualityOverrides >> 4;
        mMaxOccluderTrianglesOverride = source.readInt();
    }
    
    if (bits)
        markProjectionDirty();
}

void Camera::setNearClip(float nearClip)
{
    mNearClip = max(nearClip, 0.0f);
    markProjectionDirty();
}

void Camera::setFarClip(float farClip)
{
    mFarClip = max(farClip, 0.0f);
    markProjectionDirty();
}

void Camera::setFov(float fov)
{
    mFov = clamp(fov, 0.0f, M_MAX_FOV);
    markProjectionDirty();
}

void Camera::setOrthoSize(float orthoSize)
{
    mOrthoSize = orthoSize;
    mAspectRatio = 1.0f;
    markProjectionDirty();
}

void Camera::setOrthoSize(const Vector2& orthoSize)
{
    mOrthoSize = orthoSize.mY;
    mAspectRatio = orthoSize.mX / orthoSize.mY;
    markProjectionDirty();
}

void Camera::setAspectRatio(float aspectRatio)
{
    mAspectRatio = aspectRatio;
    markProjectionDirty();
}

void Camera::setZoom(float zoom)
{
    mZoom = max(zoom, M_EPSILON);
    markProjectionDirty();
}

void Camera::setLodBias(float bias)
{
    mLodBias = max(bias, M_EPSILON);
}

void Camera::setOrthographic(bool enable)
{
    mOrthographic = enable;
    markProjectionDirty();
}

void Camera::setViewMask(unsigned mask)
{
    mViewMask = mask;
}

void Camera::setDrawShadowsOverride(bool enable)
{
    mDrawShadowsOverride = enable;
}

void Camera::setLightDetailLevelOverride(int quality)
{
    mLightDetailLevelOverride = clamp(quality, QUALITY_LOW, QUALITY_MAX);
}

void Camera::setMaterialQualityOverride(int quality)
{
    mMaterialQualityOverride = clamp(quality, QUALITY_LOW, QUALITY_MAX);
}

void Camera::setMaxOccluderTrianglesOverride(int triangles)
{
    mMaxOccluderTrianglesOverride = triangles;
}

float Camera::getNearClip() const
{
    // Orthographic camera has always near clip at 0 to avoid trouble with shader depth parameters,
    // and unlike in perspective mode there should be no depth buffer precision issue
    if (!mOrthographic)
        return mNearClip;
    else
        return 0.0f;
}

Frustum Camera::getViewSpaceFrustum() const
{
    Frustum ret;
    
    if (!mOrthographic)
        ret.define(mFov, mAspectRatio, mZoom, getNearClip(), mFarClip);
    else
        ret.defineOrtho(mOrthoSize, mAspectRatio, mZoom, getNearClip(), mFarClip);
    
    return ret;
}

Frustum Camera::getSplitFrustum(float nearClip, float farClip)
{
    Frustum ret;
    
    nearClip = max(nearClip, getNearClip());
    farClip = min(farClip, mFarClip);
    if (farClip < nearClip)
        farClip = nearClip;
    
    if (!mOrthographic)
        ret.define(mFov, mAspectRatio, mZoom, nearClip, farClip, getWorldTransform());
    else
        ret.defineOrtho(mOrthoSize, mAspectRatio, mZoom, nearClip, farClip, getWorldTransform());
    
    return ret;
}

Ray Camera::getScreenRay(float x, float y)
{
    Matrix4 viewProjInverse = (getProjection() * getInverseWorldTransform()).getInverse();
    
    // The parameters range from 0.0 to 1.0. Expand to normalized device coordinates (-1.0 to 1.0) & flip Y axis
    x = 2.0f * x - 1.0f;
    y = 1.0f - 2.0f * y;
    
    Vector3 near(x, y, 0.0f);
    Vector3 far(x, y, 1.0f);
    
    Ray ray;
    ray.mOrigin = viewProjInverse * near;
    ray.mDirection = ((viewProjInverse * far) - ray.mOrigin).getNormalized();
    
    return ray;
}

const Matrix4x3& Camera::getInverseWorldTransform()
{
    if (mInverseWorldTransformDirty)
    {
        mInverseWorldTransform = getWorldTransform().getInverse();
        mInverseWorldTransformDirty = false;
    }
    
    return mInverseWorldTransform;
}

const Frustum& Camera::getFrustum()
{
    if (mFrustumDirty)
    {
        if (!mOrthographic)
            mFrustum.define(mFov, mAspectRatio, mZoom, getNearClip(), mFarClip, getWorldTransform());
        else
            mFrustum.defineOrtho(mOrthoSize, mAspectRatio, mZoom, getNearClip(), mFarClip, getWorldTransform());
        
        mFrustumDirty = false;
    }
    
    return mFrustum;
}

const Matrix4& Camera::getProjection()
{
    if (mProjectionDirty)
    {
        memset(&mProjection, 0, sizeof(mProjection));
        
        if (!mOrthographic)
        {
            float nearClip = getNearClip();
            float h = (1.0f / tanf(mFov * M_DEGTORAD * 0.5f)) * mZoom;
            float w = h / mAspectRatio;
            float q = mFarClip / (mFarClip - nearClip);
            
            mProjection.m00 = w;
            mProjection.m11 = h;
            mProjection.m22 = q;
            mProjection.m23 = -q * nearClip;
            mProjection.m32 = 1.0f;
        }
        else
        {
            // Disregard near clip, because it does not affect depth precision as with perspective projection
            float h = (1.0f / (mOrthoSize * 0.5f)) * mZoom;
            float w = h / mAspectRatio;
            float q = 1.0f / mFarClip;

            mProjection.m00 = w;
            mProjection.m11 = h;
            mProjection.m22 = q;
            mProjection.m33 = 1.0f;
        }
        
        mProjectionDirty = false;
    }
    
    return mProjection;
}

const Vector3& Camera::getFrustumNearSize()
{
    if (mFrustumSizeDirty)
        updateFrustumSize();
    
    return mNear;
}

const Vector3& Camera::getFrustumFarSize()
{
    if (mFrustumSizeDirty)
        updateFrustumSize();
    
    return mFar;
}

float Camera::getHalfViewSize() const
{
    if (!mOrthographic)
        return tanf(mFov * M_DEGTORAD * 0.5f) / mZoom;
    else
        return mOrthoSize * 0.5f / mZoom;
}

Vector3 Camera::getForwardVector()
{
    return getWorldRotation() * Vector3::sForward;
}

Vector3 Camera::getRightVector()
{
    return getWorldRotation() * Vector3::sRight;
}

Vector3 Camera::getUpVector()
{
    return getWorldRotation() * Vector3::sUp;
}

float Camera::getDistance(const Vector3& worldPos)
{
    if (!mOrthographic)
        return (worldPos - getWorldPosition()).getLengthFast();
    else
        return fabsf((getInverseWorldTransform() * worldPos).mZ);
}

float Camera::getDistanceSquared(const Vector3& worldPos)
{
    if (!mOrthographic)
        return (worldPos - getWorldPosition()).getLengthSquared();
    else
    {
        float distance = (getInverseWorldTransform() * worldPos).mZ;
        return distance * distance;
    }
}

float Camera::getLodDistance(float distance, float scale, float bias) const
{
    float d = max(mLodBias * bias * scale * mZoom, M_EPSILON);
    if (!mOrthographic)
        return distance / d;
    else
        return mOrthoSize / d;
}

void Camera::markInView(unsigned frameNumber)
{
    mInViewFrameNumber = frameNumber;
}

void Camera::onMarkedDirty()
{
    mInverseWorldTransformDirty = true;
    mFrustumDirty = true;
    mProjectionDirty = true;
}

void Camera::markProjectionDirty()
{
    mFrustumDirty = true;
    mProjectionDirty = true;
    mFrustumSizeDirty = true;
}

void Camera::updateFrustumSize()
{
    mNear.mZ = getNearClip();
    mFar.mZ = mFarClip;
    
    if (!mOrthographic)
    {
        float halfViewSize = tanf(mFov * M_DEGTORAD * 0.5f) / mZoom;
        mNear.mY = mNear.mZ * halfViewSize;
        mNear.mX = mNear.mY * mAspectRatio;
        mFar.mY = mFar.mZ * halfViewSize;
        mFar.mX = mFar.mY * mAspectRatio;
    }
    else
    {
        float halfViewSize = mOrthoSize * 0.5f / mZoom;
        mNear.mY = mFar.mY = halfViewSize;
        mNear.mX = mFar.mX = mNear.mY * mAspectRatio;
    }
    
    mFrustumSizeDirty = false;
}
