// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../Core/Object.h"
#include "../Core/Timer.h"
#include "../Container/ArrayPtr.h"
#include "../GraphicsAPI/GraphicsDefs.h"
#include "../Math/Frustum.h"

namespace Urho3D
{

class BoundingBox;
class Camera;
class IndexBuffer;
class IntRect;
class VertexBuffer;
struct Edge;
struct Gradients;

/// Occlusion hierarchy depth value.
struct DepthValue
{
    /// Minimum value.
    int min_;
    /// Maximum value.
    int max_;
};

/// Per-thread occlusion buffer data.
struct OcclusionBufferData
{
    /// Full buffer data with safety padding.
    SharedArrayPtr<int> dataWithSafety_;
    /// Buffer data.
    int* data_;
    /// Use flag.
    bool used_;
};

/// Stored occlusion render job.
struct OcclusionBatch
{
    /// Model matrix.
    Matrix3x4 model_;
    /// Vertex data pointer.
    const void* vertexData_;
    /// Vertex size in bytes.
    unsigned vertexSize_;
    /// Index data pointer. Null if using non-indexed geometry.
    const void* indexData_;
    /// Index size in bytes.
    unsigned indexSize_;
    /// Draw start. First index for indexed geometry, otherwise first vertex.
    unsigned drawStart_;
    /// Index or vertex count.
    unsigned drawCount_;
};

/// Software renderer for occlusion.
class URHO3D_API OcclusionBuffer : public Object
{
    URHO3D_OBJECT(OcclusionBuffer, Object);

public:
    /// Construct.
    explicit OcclusionBuffer(Context* context);
    /// Destruct.
    ~OcclusionBuffer() override;

    /// Set occlusion buffer size and whether to reserve multiple buffers for threading optimization.
    bool SetSize(int width, int height, bool threaded);
    /// Set camera view to render from.
    void SetView(Camera* camera);
    /// Set maximum triangles to render.
    void SetMaxTriangles(unsigned triangles);
    /// Set culling mode.
    void SetCullMode(CullMode mode);
    /// Reset number of triangles.
    void Reset();
    /// Clear the buffer.
    void Clear();
    /// Submit a triangle mesh to the buffer using non-indexed geometry. Return true if did not overflow the allowed triangle count.
    bool AddTriangles(const Matrix3x4& model, const void* vertexData, unsigned vertexSize, unsigned vertexStart, unsigned vertexCount);
    /// Submit a triangle mesh to the buffer using indexed geometry. Return true if did not overflow the allowed triangle count.
    bool AddTriangles(const Matrix3x4& model, const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize,
        unsigned indexStart, unsigned indexCount);
    /// Draw submitted batches. Uses worker threads if enabled during SetSize().
    void DrawTriangles();
    /// Build reduced size mip levels.
    void BuildDepthHierarchy();
    /// Reset last used timer.
    void ResetUseTimer();

    /// Return highest level depth values.
    int* GetBuffer() const { return buffers_.Size() ? buffers_[0].data_ : nullptr; }

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
    unsigned GetMaxTriangles() const { return maxTriangles_; }

    /// Return culling mode.
    CullMode GetCullMode() const { return cullMode_; }

    /// Return whether is using threads to speed up rendering.
    bool IsThreaded() const { return buffers_.Size() > 1; }

    /// Test a bounding box for visibility. For best performance, build depth hierarchy first.
    bool IsVisible(const BoundingBox& worldSpaceBox) const;
    /// Return time since last use in milliseconds.
    unsigned GetUseTimer();

    /// Draw a batch. Called internally.
    void DrawBatch(const OcclusionBatch& batch, i32 threadIndex);

private:
    /// Apply modelview transform to vertex.
    inline Vector4 ModelTransform(const Matrix4& transform, const Vector3& vertex) const;
    /// Apply projection and viewport transform to vertex.
    inline Vector3 ViewportTransform(const Vector4& vertex) const;
    /// Clip an edge.
    inline Vector4 ClipEdge(const Vector4& v0, const Vector4& v1, float d0, float d1) const;
    /// Return signed area of a triangle. If negative, is clockwise.
    inline float SignedArea(const Vector3& v0, const Vector3& v1, const Vector3& v2) const;
    /// Calculate viewport transform.
    void CalculateViewport();
    /// Draw a triangle.
    void DrawTriangle(Vector4* vertices, i32 threadIndex);
    /// Clip vertices against a plane.
    void ClipVertices(const Vector4& plane, Vector4* vertices, bool* triangles, unsigned& numTriangles);
    /// Draw a clipped triangle.
    void DrawTriangle2D(const Vector3* vertices, bool clockwise, i32 threadIndex);
    /// Clear a thread work buffer.
    void ClearBuffer(i32 threadIndex);
    /// Merge thread work buffers into the first buffer.
    void MergeBuffers();

    /// Highest-level buffer data per thread.
    Vector<OcclusionBufferData> buffers_;
    /// Reduced size depth buffers.
    Vector<SharedArrayPtr<DepthValue>> mipBuffers_;
    /// Submitted render jobs.
    Vector<OcclusionBatch> batches_;
    /// Buffer width.
    int width_{};
    /// Buffer height.
    int height_{};
    /// Number of rendered triangles.
    unsigned numTriangles_{};
    /// Maximum number of triangles.
    unsigned maxTriangles_;
    /// Culling mode.
    CullMode cullMode_{CULL_CCW};
    /// Depth hierarchy needs update flag.
    bool depthHierarchyDirty_{true};
    /// Culling reverse flag.
    bool reverseCulling_{};
    /// View transform matrix.
    Matrix3x4 view_;
    /// Projection matrix.
    Matrix4 projection_;
    /// Combined view and projection matrix.
    Matrix4 viewProj_;
    /// Last used timer.
    Timer useTimer_;
    /// Near clip distance.
    float nearClip_{};
    /// Far clip distance.
    float farClip_{};
    /// X scaling for viewport transform.
    float scaleX_{};
    /// Y scaling for viewport transform.
    float scaleY_{};
    /// X offset for viewport transform.
    float offsetX_{};
    /// Y offset for viewport transform.
    float offsetY_{};
    /// Combined X projection and viewport transform.
    float projOffsetScaleX_{};
    /// Combined Y projection and viewport transform.
    float projOffsetScaleY_{};
};

}
