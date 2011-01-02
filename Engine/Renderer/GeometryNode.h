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

#ifndef RENDERER_GEOMETRYNODE_H
#define RENDERER_GEOMETRYNODE_H

#include "RendererDefs.h"
#include "ShaderDefs.h"
#include "VolumeNode.h"

class Geometry;
class Light;
class Material;
class OcclusionBuffer;
class Ray;
class Renderer;

//! Abstract base class for renderable scene nodes
class GeometryNode : public VolumeNode
{
public:
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
    
    //! Calculate distance for rendering
    virtual void updateDistance(const FrameInfo& frame);
    //! Prepare geometry for rendering
    virtual void updateGeometry(const FrameInfo& frame, Renderer* renderer) = 0;
    //! Return number of batches
    virtual unsigned getNumBatches() = 0;
    //! Return geometry by batch index
    virtual Geometry* getBatchGeometry(unsigned batchIndex) = 0;
    //! Return material by batch index
    virtual Material* getBatchMaterial(unsigned batchIndex) = 0;
    //! Return vertex shader parameter
    virtual bool getVertexShaderParameter(unsigned batchIndex, VSParameter parameter, const float** data, unsigned* count);
    //! Draw to occlusion buffer
    virtual bool drawOcclusion(OcclusionBuffer* buffer);
    
    //! Set LOD bias
    void setLodBias(float bias);
    
    //! Return LOD bias
    float getLodBias() const { return mLodBias; }
    //! Return LOD scaled distance
    float getLodDistance() const { return mLodDistance; }
    
protected:
    //! Construct with the specified node flags, initial octant pointer and name
    GeometryNode(unsigned flags, Octant* octant, const std::string& name);
    
    //! LOD bias
    float mLodBias;
    //! LOD bias
    float mLodDistance;
    //! LOD needs update flag
    bool mLodLevelsDirty;
};

#endif // RENDERER_GEOMETRYNODE_H
