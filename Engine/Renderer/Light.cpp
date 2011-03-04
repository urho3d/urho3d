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
#include "DebugRenderer.h"
#include "Light.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "XMLElement.h"

#include "DebugNew.h"

static LightType DEFAULT_LIGHTTYPE = LIGHT_POINT;
static const float DEFAULT_FOV = 30.0f;
static const float DEFAULT_CONSTANTBIAS = 0.0001f;
static const float DEFAULT_SLOPESCALEDBIAS = 0.0001f;
static const float DEFAULT_LAMBDA = 0.5f;
static const float DEFAULT_SHADOWFADERANGE = 0.2f;
static const float DEFAULT_SHADOWQUANTIZE = 0.5f;
static const float DEFAULT_SHADOWMINVIEW = 3.0f;
static const float DEFAULT_SHADOWNEARFARRATIO = 0.002f;

static const std::string typeNames[] =
{
    "directional",
    "spot",
    "point",
    "splitpoint"
};

void BiasParameters::validate()
{
    mConstantBias = clamp(mConstantBias, 0.0f, 1.0f);
    mSlopeScaledBias = clamp(mSlopeScaledBias, 0.0f, 1.0f);
}

void CascadeParameters::validate()
{
    mSplits = max(mSplits, 1);
    mLambda = clamp(mLambda, 0.0f, 1.0f);
    mSplitFadeRange = clamp(mSplitFadeRange, M_EPSILON, 0.5f);
    mShadowRange = max(mShadowRange, M_EPSILON);
}

void FocusParameters::validate()
{
    mQuantize = max(mQuantize, SHADOW_MIN_QUANTIZE);
    mMinView = max(mMinView, SHADOW_MIN_VIEW);
}

Light::Light(Octant* octant, const std::string& name) :
    VolumeNode(NODE_LIGHT, octant, name),
    mLightType(DEFAULT_LIGHTTYPE),
    mSpecularIntensity(0.0f),
    mRange(0.0f),
    mFov(DEFAULT_FOV),
    mAspectRatio(1.0f),
    mFadeDistance(0.0f),
    mDetailLevel(0),
    mShadowDetailLevel(0),
    mShadowBias(BiasParameters(DEFAULT_CONSTANTBIAS, DEFAULT_SLOPESCALEDBIAS)),
    mShadowCascade(CascadeParameters(1, DEFAULT_LAMBDA, DEFAULT_SHADOWFADERANGE, M_LARGE_VALUE)),
    mShadowFocus(FocusParameters(true, true, true, DEFAULT_SHADOWQUANTIZE, DEFAULT_SHADOWMINVIEW)),
    mShadowFadeDistance(0.0f),
    mShadowIntensity(0.0f),
    mShadowResolution(1.0f),
    mShadowNearFarRatio(DEFAULT_SHADOWNEARFARRATIO),
    mNearSplit(0.0f),
    mFarSplit(M_LARGE_VALUE),
    mNearFadeRange(M_EPSILON),
    mFarFadeRange(M_EPSILON),
    mFrustumDirty(true),
    mShadowMap(0),
    mOriginalLight(0)
{
}

Light::~Light()
{
}

void Light::save(Serializer& dest)
{
    // Write VolumeNode properties
    VolumeNode::save(dest);
    
    // Write Light properties
    dest.writeUByte((unsigned char)mLightType);
    dest.writeColor(mColor);
    dest.writeFloat(mSpecularIntensity);
    dest.writeFloat(mRange);
    dest.writeFloat(mFov);
    dest.writeFloat(mAspectRatio);
    dest.writeFloat(mFadeDistance);
    dest.writeUByte(mDetailLevel);
    dest.writeUByte(mShadowDetailLevel);
    dest.writeFloat(mShadowBias.mConstantBias);
    dest.writeFloat(mShadowBias.mSlopeScaledBias);
    dest.writeFloat(mShadowCascade.mLambda);
    dest.writeFloat(mShadowCascade.mShadowRange);
    dest.writeFloat(mShadowCascade.mSplitFadeRange);
    dest.writeVLE(mShadowCascade.mSplits);
    dest.writeBool(mShadowFocus.mFocus);
    dest.writeBool(mShadowFocus.mNonUniform);
    dest.writeBool(mShadowFocus.mZoomOut);
    dest.writeFloat(mShadowFocus.mQuantize);
    dest.writeFloat(mShadowFocus.mMinView);
    dest.writeFloat(mShadowFadeDistance);
    dest.writeFloat(mShadowIntensity);
    dest.writeFloat(mShadowResolution);
    dest.writeFloat(mShadowNearFarRatio);
    
    dest.writeStringHash(getResourceHash(mRampTexture));
    if (mRampTexture)
        dest.writeBool(mRampTexture->getType() == TextureCube::getTypeStatic());
    dest.writeStringHash(getResourceHash(mShapeTexture));
    if (mShapeTexture)
        dest.writeBool(mShapeTexture->getType() == TextureCube::getTypeStatic());
}

void Light::load(Deserializer& source, ResourceCache* cache)
{
    // Read VolumeNode properties
    VolumeNode::load(source, cache);
    
    // Read Light properties
    mLightType = (LightType)source.readUByte();
    mColor = source.readColor();
    mSpecularIntensity = source.readFloat();
    mRange = source.readFloat();
    mFov = source.readFloat();
    mAspectRatio = source.readFloat();
    mFadeDistance = source.readFloat();
    mDetailLevel = source.readUByte();
    mShadowDetailLevel = source.readUByte();
    mShadowBias.mConstantBias = source.readFloat();
    mShadowBias.mSlopeScaledBias = source.readFloat();
    mShadowCascade.mLambda = source.readFloat();
    mShadowCascade.mShadowRange = source.readFloat();
    mShadowCascade.mSplitFadeRange = source.readFloat();
    mShadowCascade.mSplits = source.readVLE();
    mShadowFocus.mFocus = source.readBool();
    mShadowFocus.mNonUniform = source.readBool();
    mShadowFocus.mZoomOut = source.readBool();
    mShadowFocus.mQuantize = source.readFloat();
    mShadowFocus.mMinView = source.readFloat();
    mShadowFadeDistance = source.readFloat();
    mShadowIntensity = source.readFloat();
    mShadowResolution = source.readFloat();
    mShadowNearFarRatio = source.readFloat();
    
    StringHash rampTexture = source.readStringHash();
    if (rampTexture)
    {
        if (!source.readBool())
            mRampTexture = cache->getResource<Texture2D>(rampTexture);
        else
            mRampTexture = cache->getResource<TextureCube>(rampTexture);
    }
    StringHash shapeTexture = source.readStringHash();
    if (shapeTexture)
    {
        if (!source.readBool())
            mShapeTexture = cache->getResource<Texture2D>(shapeTexture);
        else
            mShapeTexture = cache->getResource<TextureCube>(shapeTexture);
    }
    
    mShadowBias.validate();
    mShadowCascade.validate();
    mShadowFocus.validate();
}

void Light::saveXML(XMLElement& dest)
{
    // Write VolumeNode properties
    VolumeNode::saveXML(dest);
    
    // Write Light properties
    XMLElement lightElem = dest.createChildElement("light");
    lightElem.setString("type", typeNames[mLightType]);
    lightElem.setColor("color", mColor);
    lightElem.setFloat("specular", mSpecularIntensity);
    lightElem.setFloat("range", mRange);
    lightElem.setFloat("fov", mFov);
    lightElem.setFloat("aspectratio", mAspectRatio);
    
    XMLElement lodElem = dest.getChildElement("lod");
    lodElem.setFloat("fadedistance", mFadeDistance);
    lodElem.setInt("detail", mDetailLevel);
    lodElem.setInt("shadowdetail", mShadowDetailLevel);
    
    XMLElement shadowElem = dest.createChildElement("shadows");
    shadowElem.setFloat("fadedistance", mShadowFadeDistance);
    shadowElem.setFloat("intensity", mShadowIntensity);
    shadowElem.setFloat("resolution", mShadowResolution);
    shadowElem.setFloat("nearfarratio", mShadowNearFarRatio);
    
    XMLElement biasElem = dest.createChildElement("shadowbias");
    biasElem.setFloat("constant", mShadowBias.mConstantBias);
    biasElem.setFloat("slopescaled", mShadowBias.mSlopeScaledBias);
    
    XMLElement cascadeElem = dest.createChildElement("shadowcascade");
    cascadeElem.setFloat("lambda", mShadowCascade.mLambda);
    cascadeElem.setFloat("maxrange", mShadowCascade.mShadowRange);
    cascadeElem.setFloat("faderange", mShadowCascade.mSplitFadeRange);
    cascadeElem.setInt("splits", mShadowCascade.mSplits);
    
    XMLElement focusElem = dest.createChildElement("shadowfocus");
    focusElem.setBool("enable", mShadowFocus.mFocus);
    focusElem.setBool("nonuniform", mShadowFocus.mNonUniform);
    focusElem.setBool("zoomout", mShadowFocus.mZoomOut);
    focusElem.setFloat("quantize", mShadowFocus.mQuantize);
    focusElem.setFloat("minview", mShadowFocus.mMinView);
    
    XMLElement rampElem = dest.createChildElement("ramptexture");
    rampElem.setString("name", getResourceName(mRampTexture));
    
    XMLElement spotElem = dest.createChildElement("spottexture");
    spotElem.setString("name", getResourceName(mShapeTexture));
}

void Light::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read VolumeNode properties
    VolumeNode::loadXML(source, cache);
    
    // Read Light properties
    XMLElement lightElem = source.getChildElement("light");
    mLightType = (LightType)getIndexFromStringList(lightElem.getStringLower("type"), typeNames, 3, 0);
    mColor = lightElem.getColor("color");
    mSpecularIntensity = lightElem.getFloat("specular");
    mRange = lightElem.getFloat("range");
    mFov = lightElem.getFloat("fov");
    mAspectRatio = lightElem.getFloat("aspectratio");
    
    XMLElement lodElem = source.getChildElement("lod");
    mFadeDistance = lodElem.getFloat("fadedistance");
    mDetailLevel = lodElem.getInt("detail");
    mShadowDetailLevel = lodElem.getInt("shadowdetail");
    
    XMLElement shadowElem = source.getChildElement("shadows");
    mShadowFadeDistance = shadowElem.getFloat("fadedistance");
    mShadowIntensity = shadowElem.getFloat("intensity");
    mShadowResolution = shadowElem.getFloat("resolution");
    mShadowNearFarRatio = shadowElem.getFloat("nearfarratio");
    
    XMLElement biasElem = source.getChildElement("shadowbias");
    mShadowBias.mConstantBias = biasElem.getFloat("constant");
    mShadowBias.mSlopeScaledBias = biasElem.getFloat("slopescaled");
    
    XMLElement cascadeElem = source.getChildElement("shadowcascade");
    mShadowCascade.mLambda = cascadeElem.getFloat("lambda");
    mShadowCascade.mShadowRange = cascadeElem.getFloat("maxrange");
    mShadowCascade.mSplitFadeRange = cascadeElem.getFloat("faderange");
    mShadowCascade.mSplits = cascadeElem.getInt("splits");
    
    XMLElement focusElem = source.getChildElement("shadowfocus");
    mShadowFocus.mFocus = focusElem.getBool("enable");
    mShadowFocus.mNonUniform = focusElem.getBool("nonuniform");
    mShadowFocus.mZoomOut = focusElem.getBool("zoomout");
    mShadowFocus.mQuantize = focusElem.getFloat("quantize");
    mShadowFocus.mMinView = focusElem.getFloat("minview");
    
    XMLElement rampElem = source.getChildElement("ramptexture");
    std::string name = rampElem.getString("name");
    if (getExtension(name) == ".xml")
        mRampTexture = cache->getResource<TextureCube>(name);
    else
        mRampTexture = cache->getResource<Texture2D>(name);
    
    XMLElement spotElem = source.getChildElement("spottexture");
    name = spotElem.getString("name");
    if (getExtension(name) == ".xml")
        mShapeTexture = cache->getResource<TextureCube>(name);
    else
        mShapeTexture = cache->getResource<Texture2D>(name);
    
    mShadowBias.validate();
    mShadowCascade.validate();
    mShadowFocus.validate();
}

bool Light::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    // Write VolumeNode properties and see if there were any changes
    bool prevBits = VolumeNode::writeNetUpdate(dest, destRevision, baseRevision, info);
    
    // Build bitmask of changed properties
    unsigned char bits = 0;
    unsigned char bits2 = 0;
    unsigned char detailLevels = mDetailLevel | (mShadowDetailLevel << 4);
    checkUByte((unsigned char)mLightType, DEFAULT_LIGHTTYPE, baseRevision, bits, 1);
    checkUByte(detailLevels, 0, baseRevision, bits, 1);
    checkColor(mColor, Color(), baseRevision, bits, 2);
    checkFloat(mSpecularIntensity, 0.0f, baseRevision, bits, 2);
    checkFloat(mRange, 0.0f, baseRevision, bits, 4);
    checkFloat(mFov, DEFAULT_FOV, baseRevision, bits, 8);
    checkFloat(mAspectRatio, 1.0f, baseRevision, bits, 16);
    checkFloat(mFadeDistance, 0.0f, baseRevision, bits, 32);
    checkStringHash(getResourceHash(mRampTexture), StringHash(), baseRevision, bits, 64);
    checkStringHash(getResourceHash(mShapeTexture), StringHash(), baseRevision, bits, 128);
    checkFloat(mShadowBias.mConstantBias, DEFAULT_CONSTANTBIAS, baseRevision, bits2, 1);
    checkFloat(mShadowBias.mSlopeScaledBias, DEFAULT_SLOPESCALEDBIAS, baseRevision, bits2, 1);
    checkFloat(mShadowCascade.mLambda, DEFAULT_LAMBDA, baseRevision, bits2, 2);
    checkFloat(mShadowCascade.mShadowRange, M_LARGE_VALUE, baseRevision, bits2, 2);
    checkFloat(mShadowCascade.mSplitFadeRange, DEFAULT_SHADOWFADERANGE, baseRevision, bits2, 2);
    checkVLE(mShadowCascade.mSplits, 1, baseRevision, bits2, 2);
    checkBool(mShadowFocus.mFocus, true, baseRevision, bits2, 4);
    checkBool(mShadowFocus.mNonUniform, true, baseRevision, bits2, 4);
    checkBool(mShadowFocus.mZoomOut, true, baseRevision, bits2, 4);
    checkFloat(mShadowFocus.mQuantize, DEFAULT_SHADOWQUANTIZE, baseRevision, bits2, 4);
    checkFloat(mShadowFocus.mMinView, DEFAULT_SHADOWMINVIEW, baseRevision, bits2, 4);
    checkFloat(mShadowFadeDistance, 0.0f, baseRevision, bits2, 8);
    checkUByte((unsigned char)(mShadowIntensity * 255), 0, baseRevision, bits2, 16);
    checkUByte((unsigned char)(mShadowResolution * 100), 100, baseRevision, bits2, 32);
    checkFloat(mShadowNearFarRatio, DEFAULT_SHADOWNEARFARRATIO, baseRevision, bits2, 64);
    
    // Send only information necessary for the light type, and shadow data only for shadowed lights
    if (mLightType == LIGHT_DIRECTIONAL)
        bits &= ~(4 | 32);
    if (mLightType != LIGHT_SPOT)
        bits &= ~(8 | 16);
    if (!mCastShadows)
        bits2 = 0;
    
    dest.writeUByte(bits);
    dest.writeUByte(bits2);
    writeUByteDelta((unsigned char)mLightType, dest, destRevision, bits & 1);
    writeUByteDelta(detailLevels, dest, destRevision, bits & 1);
    writeColorDelta(mColor, dest, destRevision, bits & 2);
    writeFloatDelta(mSpecularIntensity, dest, destRevision, bits & 2);
    writeFloatDelta(mRange, dest, destRevision, bits & 4);
    writeFloatDelta(mFov, dest, destRevision, bits & 8);
    writeFloatDelta(mAspectRatio, dest, destRevision, bits & 16);
    writeFloatDelta(mFadeDistance, dest, destRevision, bits & 32);
    writeStringHashDelta(getResourceHash(mRampTexture), dest, destRevision, bits & 64);
    if ((bits & 64) && (mRampTexture))
        dest.writeBool(mRampTexture->getType() == TextureCube::getTypeStatic());
    writeStringHashDelta(getResourceHash(mShapeTexture), dest, destRevision, bits & 128);
    if ((bits & 128) && (mShapeTexture))
        dest.writeBool(mShapeTexture->getType() == TextureCube::getTypeStatic());
    writeFloatDelta(mShadowBias.mConstantBias, dest, destRevision, bits2 & 1);
    writeFloatDelta(mShadowBias.mSlopeScaledBias, dest, destRevision, bits2 & 1);
    writeFloatDelta(mShadowCascade.mLambda, dest, destRevision, bits2 & 2);
    writeFloatDelta(mShadowCascade.mShadowRange, dest, destRevision, bits2 & 2);
    writeFloatDelta(mShadowCascade.mSplitFadeRange, dest, destRevision, bits2 & 2);
    writeVLEDelta(mShadowCascade.mSplits, dest, destRevision, bits2 & 2);
    writeBoolDelta(mShadowFocus.mFocus, dest, destRevision, bits2 & 4);
    writeBoolDelta(mShadowFocus.mNonUniform, dest, destRevision, bits2 & 4);
    writeBoolDelta(mShadowFocus.mZoomOut, dest, destRevision, bits2 & 4);
    writeFloatDelta(mShadowFocus.mQuantize, dest, destRevision, bits2 & 4);
    writeFloatDelta(mShadowFocus.mMinView, dest, destRevision, bits2 & 4);
    writeFloatDelta(mShadowFadeDistance, dest, destRevision, bits2 & 8);
    writeUByteDelta((unsigned char)(mShadowIntensity * 255), dest, destRevision, bits2 & 16);
    writeUByteDelta((unsigned char)(mShadowResolution * 100), dest, destRevision, bits2 & 32);
    writeFloatDelta(mShadowNearFarRatio, dest, destRevision, bits2 & 64);
    
    return prevBits || (bits != 0) || (bits2 != 0);
}

void Light::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    // Read VolumeNode properties
    VolumeNode::readNetUpdate(source, cache, info);
    
    unsigned char bits = source.readUByte();
    unsigned char bits2 = source.readUByte();
    if (bits & 1)
    {
        mLightType = (LightType)source.readUByte();
        unsigned char detailLevels = source.readUByte();
        mDetailLevel = detailLevels & 15;
        mShadowDetailLevel = detailLevels >> 4;
    }
    readColorDelta(mColor, source, bits & 2);
    readFloatDelta(mSpecularIntensity, source, bits & 2);
    readFloatDelta(mRange, source, bits & 4);
    readFloatDelta(mFov, source, bits & 8);
    readFloatDelta(mAspectRatio, source, bits & 16);
    readFloatDelta(mFadeDistance, source, bits & 32);
    if (bits & 64)
    {
        StringHash rampTexture = source.readStringHash();
        if (rampTexture)
        {
            if (!source.readBool())
                mRampTexture = cache->getResource<Texture2D>(rampTexture);
            else
                mRampTexture = cache->getResource<TextureCube>(rampTexture);
        }
    }
    if (bits & 128)
    {
        StringHash shapeTexture = source.readStringHash();
        if (shapeTexture)
        {
            if (!source.readBool())
                mShapeTexture = cache->getResource<Texture2D>(shapeTexture);
            else
                mShapeTexture = cache->getResource<TextureCube>(shapeTexture);
        }
    }
    readFloatDelta(mShadowBias.mConstantBias, source, bits2 & 1);
    readFloatDelta(mShadowBias.mSlopeScaledBias, source, bits2 & 1);
    readFloatDelta(mShadowCascade.mLambda, source, bits2 & 2);
    readFloatDelta(mShadowCascade.mShadowRange, source, bits2 & 2);
    readFloatDelta(mShadowCascade.mSplitFadeRange, source, bits2 & 2);
    readVLEDelta(mShadowCascade.mSplits, source, bits2 & 2);
    readBoolDelta(mShadowFocus.mFocus, source, bits2 & 4);
    readBoolDelta(mShadowFocus.mNonUniform, source, bits2 & 4);
    readBoolDelta(mShadowFocus.mZoomOut, source, bits2 & 4);
    readFloatDelta(mShadowFocus.mQuantize, source, bits2 & 4);
    readFloatDelta(mShadowFocus.mMinView, source, bits2 & 4);
    readFloatDelta(mShadowFadeDistance, source, bits2 & 8);
    if (bits2 & 16)
    {
        int shadowIntensity = source.readUByte();
        mShadowIntensity = shadowIntensity / 255.0f;
    }
    if (bits2 & 32)
    {
        int shadowResolution = source.readUByte();
        mShadowResolution = shadowResolution / 100.0f;
    }
    readFloatDelta(mShadowNearFarRatio, source, bits2 & 64);
    
    if (bits)
        markDirty();
}

void Light::getResourceRefs(std::vector<Resource*>& dest)
{
    if (mRampTexture)
        dest.push_back(mRampTexture);
    if (mShapeTexture)
        dest.push_back(mShapeTexture);
}

void Light::updateDistance(const FrameInfo& frame)
{
    switch (mLightType)
    {
    case LIGHT_DIRECTIONAL:
        // Directional light affects the whole scene, so it is always "closest"
        mDistance = 0.0f;
        break;
        
    default:
        mDistance = frame.mCamera->getDistance(getWorldPosition());
        break;
    }
}

void Light::overrideTransforms(unsigned batchIndex, Camera& camera, const Matrix4x3** model, const Matrix4x3** view)
{
    // Can use a static matrix because these are asked for one node at a time
    static Matrix4x3 lightModel;
    
    *model = &lightModel;
    
    switch (mLightType)
    {
    case LIGHT_DIRECTIONAL:
        lightModel = getDirLightTransform(camera, false);
        // Because of precision issues, set view to identity instead of adjusting model transform to match
        *view = &Matrix4x3::sIdentity;
        break;
        
    case LIGHT_POINT:
        lightModel.define(getWorldPosition(), Quaternion::sIdentity, mRange);
        break;
        
    case LIGHT_SPOT:
        {
            float yScale = tan(mFov * M_DEGTORAD * 0.5f) * mRange;
            float xScale = mAspectRatio * yScale;
            lightModel.define(getWorldPosition(), getWorldRotation(), Vector3(xScale, yScale, mRange));
        }
        break;
        
    case LIGHT_SPLITPOINT:
        lightModel.define(getWorldPosition(), getWorldRotation(), mRange);
        break;
    }
}

void Light::drawDebugGeometry(DebugRenderer* debug)
{
    switch (mLightType)
    {
    case LIGHT_SPOT:
        debug->addFrustum(getFrustum(), mColor, false);
        break;
        
    case LIGHT_POINT:
        debug->addBoundingBox(getWorldBoundingBox(), getColor(), false);
        break;
    }
}

void Light::setLightType(LightType type)
{
    mLightType = type;
    
    // Validate shape texture type: 2D for spot lights, cube for point lights. Change to null if wrong
    if ((mLightType == LIGHT_SPOT) && (mShapeTexture) && (mShapeTexture->getType() != Texture2D::getTypeStatic()))
        mShapeTexture = 0;
    if ((mLightType == LIGHT_POINT) && (mShapeTexture) && (mShapeTexture->getType() != TextureCube::getTypeStatic()))
        mShapeTexture = 0;
    
    if (!isDirty())
        markDirty();
}

void Light::setColor(const Color& color)
{
    mColor = color;
}

void Light::setRange(float range)
{
    mRange = max(range, 0.0f);
    
    if (!isDirty())
        markDirty();
}

void Light::setFov(float fov)
{
    mFov = clamp(fov, 0.0f, M_MAX_FOV);
    
    if (!isDirty())
        markDirty();
}

void Light::setAspectRatio(float aspectRatio)
{
    mAspectRatio = max(aspectRatio, M_EPSILON);
    
    if (!isDirty())
        markDirty();
}

void Light::setShadowNearFarRatio(float nearFarRatio)
{
    mShadowNearFarRatio = clamp(nearFarRatio, 0.0f, 0.5f);
}

void Light::setSpecularIntensity(float intensity)
{
    mSpecularIntensity = max(intensity, 0.0f);
}

void Light::setFadeDistance(float distance)
{
    mFadeDistance = max(distance, 0.0f);
}

void Light::setDetailLevel(int detailLevel, int shadowDetailLevel)
{
    mDetailLevel = clamp(detailLevel, 0, QUALITY_MAX);
    mShadowDetailLevel = clamp(shadowDetailLevel, 0, QUALITY_MAX);
}

void Light::setShadowBias(const BiasParameters& parameters)
{
    mShadowBias = parameters;
    mShadowBias.validate();
}

void Light::setShadowCascade(const CascadeParameters& parameters)
{
    mShadowCascade = parameters;
    mShadowCascade.validate();
}

void Light::setShadowFocus(const FocusParameters& parameters)
{
    mShadowFocus = parameters;
    mShadowFocus.validate();
}

void Light::setShadowFadeDistance(float distance)
{
    mShadowFadeDistance = max(distance, 0.0f);
}

void Light::setShadowIntensity(float intensity)
{
    mShadowIntensity = clamp(intensity, 0.0f, 1.0f);
}

void Light::setShadowResolution(float resolution)
{
    mShadowResolution = clamp(resolution, 0.25f, 1.0f);
}

void Light::setRampTexture(Texture* texture)
{
    mRampTexture = texture;
}

void Light::setShapeTexture(Texture* texture)
{
    mShapeTexture = texture;
}

void Light::copyFrom(Light* original)
{
    mOriginalLight = original;
    setPosition(original->getWorldPosition());
    setRotation(original->getWorldRotation());
    setScale(original->getWorldScale());
    mCastShadows = original->mCastShadows;
    mDrawDistance = original->mDrawDistance;
    mShadowDistance = original->mShadowDistance;
    mViewMask = original->mViewMask;
    mLightMask = original->mLightMask;
    mDistance = original->mDistance;
    mLightType = original->mLightType;
    mRange = original->mRange;
    mFov = original->mFov;
    mAspectRatio = original->mAspectRatio;
    mColor = original->mColor;
    mSpecularIntensity = original->mSpecularIntensity;
    mFadeDistance = original->mFadeDistance;
    mShadowBias = original->mShadowBias;
    mShadowCascade = original->mShadowCascade;
    mShadowFocus = original->mShadowFocus;
    mShadowFadeDistance = original->mShadowFadeDistance;
    mShadowIntensity = original->mShadowIntensity;
    mShadowResolution = original->mShadowResolution;
    mRampTexture = original->mRampTexture;
    mShapeTexture = original->mShapeTexture;
}

bool Light::isNegative() const
{
    return (mColor.mR < 0.0f) || (mColor.mG < 0.0f) || (mColor.mB < 0.0f);
}

const Frustum& Light::getFrustum()
{
    // Note: frustum is also used for the point light when it is split for shadow rendering
    if (mFrustumDirty)
    {
        Matrix4x3 transform;
        transform.define(getWorldPosition(), getWorldRotation(), 1.0f);
        // Set a small near clip distance, so that the near plane can be calculated
        // Note: this is not necessarily the same near clip as on the actual shadow camera
        mFrustum.define(mFov, mAspectRatio, 1.0f, M_MIN_NEARCLIP, mRange, transform);
    }
    
    return mFrustum;
}

float Light::getVolumeExtent() const
{
    switch (mLightType)
    {
    case LIGHT_POINT:
        return mRange * 1.36f;
        
    case LIGHT_SPOT:
        {
            float safeRange = mRange * 1.001f;
            float yScale = tan(mFov * M_DEGTORAD * 0.5f) * safeRange;
            float xScale = mAspectRatio * yScale;
            return sqrtf(xScale * xScale + yScale * yScale + safeRange * safeRange);
        }
        
    case LIGHT_SPLITPOINT:
        {
            float safeRange = mRange * 1.001f;
            return sqrtf(3.0f * safeRange * safeRange);
        }
        
    default:
        return M_LARGE_VALUE;
    }
}

Matrix4x3 Light::getDirLightTransform(Camera& camera, bool getNearQuad) const
{
    Vector3 farVector = camera.getFrustumFarSize();
    float nearClip = camera.getNearClip();
    float farClip = camera.getFarClip();
    
    float distance;
    
    if (getNearQuad)
        distance = max(mNearSplit - mNearFadeRange, nearClip);
    else
        distance = min(mFarSplit, farClip);
    if (!camera.isOrthographic())
        farVector *= (distance / farClip);
    else
        farVector.mZ *= (distance / farClip);
        
    Matrix4x3 transform;
    transform.define(Vector3(0.0f, 0.0f, farVector.mZ), Quaternion::sIdentity, Vector3(farVector.mX, farVector.mY, 1.0f));
    return transform;
}

void Light::onMarkedDirty()
{
    VolumeNode::onMarkedDirty();
    
    mFrustumDirty = true;
}

void Light::onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox)
{
    switch (mLightType)
    {
    case LIGHT_DIRECTIONAL:
        // Directional light always sets humongous bounding box not affected by transform
        worldBoundingBox.define(-M_LARGE_VALUE, M_LARGE_VALUE);
        break;
        
    case LIGHT_POINT:
        {
            const Vector3& center = getWorldPosition();
            Vector3 edge(mRange, mRange, mRange);
            worldBoundingBox.define(center - edge, center + edge);
        }
        break;
        
    case LIGHT_SPOT:
    case LIGHT_SPLITPOINT:
        // Frustum is already transformed into world space
        worldBoundingBox.define(getFrustum());
        break;
    }
}

void Light::setNearSplit(float nearSplit)
{
    mNearSplit = max(nearSplit, 0.0f);
}

void Light::setFarSplit(float farSplit)
{
    mFarSplit = max(farSplit, 0.0f);
}

void Light::setNearFadeRange(float range)
{
    mNearFadeRange = max(range, M_EPSILON);
}

void Light::setFarFadeRange(float range)
{
    mFarFadeRange = max(range, M_EPSILON);
}

void Light::setShadowMap(Texture2D* shadowMap)
{
    mShadowMap = shadowMap;
}
