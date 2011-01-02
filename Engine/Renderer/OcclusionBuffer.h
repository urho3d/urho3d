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

#ifndef RENDERER_OCCLUSIONBUFFER_H
#define RENDERER_OCCLUSIONBUFFER_H

#include "Frustum.h"
#include "RendererDefs.h"
#include "SharedArrayPtr.h"

#include <vector>

class BoundingBox;
class Camera;
class IndexBuffer;
class IntRect;
class VertexBuffer;
struct Edge;
struct Gradients;

//! Occlusion hierarchy depth range
struct DepthValue
{
    int mMin;
    int mMax;
};

static const int OCCLUSION_MIN_SIZE = 8;
static const unsigned OCCLUSION_DEFAULT_MAX_TRIANGLES = 5000;
static const float OCCLUSION_X_SCALE = 65536.0f;
static const float OCCLUSION_Z_SCALE = 16777216.0f;

//! Software renderer for occlusion
class OcclusionBuffer : public RefCounted
{
public:
    //! Construct
    OcclusionBuffer();
    //! Destruct
    virtual ~OcclusionBuffer();
    
    //! Set occlusion buffer size
    bool setSize(int width, int height);
    //! Set camera view to render from
    void setView(Camera& camera);
    //! Set maximum triangles to render
    void setMaxTriangles(unsigned triangles);
    //! Set culling mode
    void setCullMode(CullMode mode);
    //! Reset number of triangles
    void reset();
    //! Clear buffer
    void clear();
    //! Draw triangle mesh to buffer
    bool draw(const Matrix4x3& model, const unsigned char* vertexData, unsigned vertexSize, const unsigned char* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount);
    //! Build depth hierarchy
    void buildDepthHierarchy();
    
    //! Return highest level depth values
    int* getBuffer() const { return mBuffer; }
    //! Return view transform matrix
    const Matrix4x3& getView() const { return mView; }
    //! Return projection matrix
    const Matrix4& getProjection() const { return mProjection; }
    //! Return buffer width
    int getWidth() const { return mWidth; }
    //! Return buffer height
    int getHeight() const { return mHeight; }
    //! Return number of rendered triangles
    unsigned getNumTriangles() const { return mNumTriangles; }
    //! Return maximum number of triangles
    unsigned getMaxTriangles() const { return mMaxTriangles; }
    //! Return culling mode
    CullMode getCullMode() const { return mCullMode; }
    //! Test a bounding box for visibility. For best performance, build depth hierarchy first
    bool isVisible(const BoundingBox& worldSpaceBox) const;
    
private:
    //! Apply modelview transform to vertex
    inline Vector4 modelTransform(const Matrix4& transform, const Vector3& vertex) const;
    //! Apply projection and viewport transform to vertex
    inline Vector3 viewportTransform(const Vector4& vertex) const;
    //! Clip an edge
    inline Vector4 clipEdge(const Vector4& v0, const Vector4& v1, float d0, float d1) const;
    //! Check facing of a triangle
    inline bool checkFacing(const Vector3& v0, const Vector3& v1, const Vector3& v2) const;
    //! Calculate viewport transform
    void calculateViewport();
    //! Draw a triangle
    void drawTriangle(Vector4* vertices);
    //! Clip vertices against a plane
    void clipVertices(const Vector4& plane, Vector4* vertices, bool* triangles, unsigned& numTriangles);
    //! Draw a clipped triangle
    void drawTriangle2D(const Vector3* vertices);
    
    //! Highest level depth buffer
    int* mBuffer;
    //! Buffer width
    int mWidth;
    //! Buffer height
    int mHeight;
    //! Number of rendered triangles
    unsigned mNumTriangles;
    //! Maximum number of triangles
    unsigned mMaxTriangles;
    //! Culling mode
    CullMode mCullMode;
    //! Depth hierarchy needs update flag
    bool mHierarchyDirty;
    //! View transform matrix
    Matrix4x3 mView;
    //! Projection matrix
    Matrix4 mProjection;
    //! Combined view and projection matrix
    Matrix4 mViewProj;
    //! Near clip distance
    float mNearClip;
    //! Far clip distance
    float mFarClip;
    //! Depth bias to apply
    float mDepthBias;
    //! X scaling for viewport transform
    float mScaleX;
    //! Y scaling for viewport transform
    float mScaleY;
    //! X offset for viewport transform
    float mOffsetX;
    //! Y offset for viewport transform
    float mOffsetY;
    //! Combined X projection and viewport transform
    float mProjOffsetScaleX;
    //! Combined Y projection and viewport transform
    float mProjOffsetScaleY;
    //! Highest level buffer with safety padding
    SharedArrayPtr<int> mFullBuffer;
    //! Depth hierarchy buffers
    std::vector<SharedArrayPtr<DepthValue> > mReducedBuffers;
};

#endif // RENDERER_OCCLUSIONBUFFER_H
