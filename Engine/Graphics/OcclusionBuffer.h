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

#include "Frustum.h"
#include "Object.h"
#include "GraphicsDefs.h"
#include "ArrayPtr.h"

class BoundingBox;
class Camera;
class IndexBuffer;
class IntRect;
class VertexBuffer;
struct Edge;
struct Gradients;

/// Occlusion hierarchy depth range.
struct DepthValue
{
    /// Minimum value.
    int min_;
    /// Maximum value.
    int max_;
};

static const int OCCLUSION_MIN_SIZE = 8;
static const int OCCLUSION_DEFAULT_MAX_TRIANGLES = 5000;
static const int OCCLUSION_DEPTH_BIAS = 1;
static const float OCCLUSION_X_SCALE = 65536.0f;
static const float OCCLUSION_Z_SCALE = 65536.0f;

/// Software renderer for occlusion.
class OcclusionBuffer : public Object
{
    OBJECT(OcclusionBuffer);
    
public:
    /// Construct.
    OcclusionBuffer(Context* context);
    /// Destruct.
    virtual ~OcclusionBuffer();
    
    /// %Set occlusion buffer size.
    bool SetSize(int width, int height);
    /// %Set camera view to render from.
    void SetView(Camera* camera);
    /// %Set maximum triangles to render.
    void SetMaxTriangles(unsigned triangles);
    /// %Set culling mode.
    void SetCullMode(CullMode mode);
    /// Reset number of triangles.
    void Reset();
    /// Clear the buffer.
    void Clear();
    /// Draw a triangle mesh to the buffer.
    bool Draw(const Matrix3x4& model, const unsigned char* vertexData, unsigned vertexSize, const unsigned char* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount);
    /// Build reduced size mip levels.
    void BuildDepthHierarchy();
    
    /// Return highest level depth values.
    int* GetBuffer() const { return buffer_; }
    /// Return view transform matrix.
    const Matrix3x4& GetView() const { return view_; }
    /// Return projection matrix.
    const Matrix4& GetProjection() const { return projection_; }
    /// Return buffer width.
    int GetWidth() const { return width_; }
    /// Return buffer height.
    int GetHeight() const { return height_; }
    /// Return number of rendered triangles.
    unsigned GetNumTriangles() const { return numTriangles_; }
    /// Return maximum number of triangles.
    unsigned GetMaxTriangles() const { return max_Triangles; }
    /// Return culling mode.
    CullMode GetCullMode() const { return cullMode_; }
    /// Test a bounding box for visibility. For best performance, build depth hierarchy first.
    bool IsVisible(const BoundingBox& worldSpaceBox) const;
    
private:
    /// Apply modelview transform to vertex.
    inline Vector4 ModelTransform(const Matrix4& transform, const Vector3& vertex) const;
    /// Apply projection and viewport transform to vertex.
    inline Vector3 ViewportTransform(const Vector4& vertex) const;
    /// Clip an edge.
    inline Vector4 ClipEdge(const Vector4& v0, const Vector4& v1, float d0, float d1) const;
    /// Check facing of a triangle.
    inline bool CheckFacing(const Vector3& v0, const Vector3& v1, const Vector3& v2) const;
    /// Calculate viewport transform.
    void CalculateViewport();
    /// Draw a triangle.
    void DrawTriangle(Vector4* vertices);
    /// Clip vertices against a plane.
    void ClipVertices(const Vector4& plane, Vector4* vertices, bool* triangles, unsigned& numTriangles);
    /// Draw a clipped triangle.
    void DrawTriangle2D(const Vector3* vertices);
    
    /// Highest level depth buffer.
    int* buffer_;
    /// Buffer width.
    int width_;
    /// Buffer height.
    int height_;
    /// Number of rendered triangles.
    unsigned numTriangles_;
    /// Maximum number of triangles.
    unsigned max_Triangles;
    /// Culling mode.
    CullMode cullMode_;
    /// Depth hierarchy needs update flag.
    bool depthHierarchyDirty_;
    /// View transform matrix.
    Matrix3x4 view_;
    /// Projection matrix.
    Matrix4 projection_;
    /// Combined view and projection matrix.
    Matrix4 viewProj_;
    /// Near clip distance.
    float nearClip_;
    /// Far clip distance.
    float farClip_;
    /// X scaling for viewport transform.
    float scaleX_;
    /// Y scaling for viewport transform.
    float scaleY_;
    /// X offset for viewport transform.
    float offsetX_;
    /// Y offset for viewport transform.
    float offsetY_;
    /// Combined X projection and viewport transform.
    float projOffsetScaleX_;
    /// Combined Y projection and viewport transform.
    float projOffsetScaleY_;
    /// Highest level buffer with safety padding.
    SharedArrayPtr<int> fullBuffer_;
    /// Reduced size depth buffers.
    Vector<SharedArrayPtr<DepthValue> > mipBuffers_;
};
