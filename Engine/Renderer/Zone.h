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

#ifndef RENDERER_ZONE_H
#define RENDERER_ZONE_H

#include "Color.h"
#include "VolumeNode.h"

//! A scene node that describes global rendering properties
class Zone : public VolumeNode
{
    DEFINE_TYPE(Zone);
    
public:
    //! Construct with initial octant pointer and name
    Zone(Octant* octant = 0, const std::string& name = std::string());
    //! Destruct
    virtual ~Zone();
    
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
    
    //! Set bounding box. Will be used as an oriented bounding box to test whether the camera is inside
    void setBoundingBox(const BoundingBox& box);
    //! Set ambient color
    void setAmbientColor(const Color& color);
    //! Set fog color
    void setFogColor(const Color& color);
    //! Set fog start distance
    void setFogStart(float start);
    //! Set fog end distance
    void setFogEnd(float end);
    //! Set zone priority. If camera is inside several zones, the one with highest priority is used
    void setPriority(int priority);
    
    //! Return bounding box
    const BoundingBox& getBoundingBox() const { return mBoundingBox; }
    //! Return ambient color
    const Color& getAmbientColor() const { return mAmbientColor; }
    //! Return fog color
    const Color& getFogColor() const { return mFogColor; }
    //! Return fog start distance
    float getFogStart() const { return mFogStart; }
    //! Return fog end distance
    float getFogEnd() const { return mFogEnd; }
    //! Return zone priority
    int getPriority() const { return mPriority; }
    
    //! Check whether a point is inside
    virtual bool isInside(const Vector3& point);
    
protected:
    //! Update world-space bounding box
    virtual void onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox);
    
    //! Bounding box
    BoundingBox mBoundingBox;
    //! Ambient color
    Color mAmbientColor;
    //! Fog color
    Color mFogColor;
    //! Fog start distance
    float mFogStart;
    //! Fog end distance
    float mFogEnd;
    //! Zone priority
    int mPriority;
};

#endif // RENDERER_ZONE_H
