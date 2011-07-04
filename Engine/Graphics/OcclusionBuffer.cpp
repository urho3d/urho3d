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
#include "Log.h"
#include "OcclusionBuffer.h"
#include "Profiler.h"

#include <cstring>

#include "DebugNew.h"

static const unsigned CLIPMASK_X_POS = 0x1;
static const unsigned CLIPMASK_X_NEG = 0x2;
static const unsigned CLIPMASK_Y_POS = 0x4;
static const unsigned CLIPMASK_Y_NEG = 0x8;
static const unsigned CLIPMASK_Z_POS = 0x10;
static const unsigned CLIPMASK_Z_NEG = 0x20;

OBJECTTYPESTATIC(OcclusionBuffer);

OcclusionBuffer::OcclusionBuffer(Context* context) :
    Object(context),
    buffer_(0),
    width_(0),
    height_(0),
    numTriangles_(0),
    max_Triangles(OCCLUSION_DEFAULT_MAX_TRIANGLES),
    cullMode_(CULL_CCW),
    depthHierarchyDirty_(true),
    nearClip_(0.0f),
    farClip_(0.0f),
    depthBias_(0.0f)
{
}

OcclusionBuffer::~OcclusionBuffer()
{
}

bool OcclusionBuffer::SetSize(int width, int height)
{
    if (width == width_ && height == height_)
        return true;
    
    if (width <= 0 || height <= 0)
        return false;
    
    if (!IsPowerOfTwo(width))
    {
        LOGERROR("Width is not a power of two");
        return false;
    }
    
    PROFILE(ResizeOcclusion);
    
    width_ = width;
    height_ = height;
    // Reserve extra memory in case 3D clipping is not exact
    fullBuffer_ = new int[width * (height + 2)];
    buffer_ = fullBuffer_.Ptr() + 1 * width;
    mipBuffers_.Clear();
    
    // Build buffers for mip levels
    for (;;)
    {
        width = (width + 1) / 2;
        height = (height + 1) / 2;
        
        mipBuffers_.Push(SharedArrayPtr<DepthValue>(new DepthValue[width * height]));
        
        if (width <= OCCLUSION_MIN_SIZE && height <= OCCLUSION_MIN_SIZE)
            break;
    }
    
    LOGDEBUG("Set occlusion buffer size " + String(width_) + "x" + String(height_) + " with " + 
        String(mipBuffers_.Size()) + " mip levels");
    
    CalculateViewport();
    return true;
}

void OcclusionBuffer::SetView(Camera* camera)
{
    if (!camera)
        return;
    
    view_ = camera->GetInverseWorldTransform();
    projection_ = camera->GetProjection();
    viewProj_ = projection_ * view_;
    nearClip_ = camera->GetNearClip();
    farClip_ = camera->GetFarClip();
    depthBias_ = farClip_ * 0.00002f;
    CalculateViewport();
}

void OcclusionBuffer::SetMaxTriangles(unsigned triangles)
{
    max_Triangles = triangles;
}

void OcclusionBuffer::SetCullMode(CullMode mode)
{
    cullMode_ = mode;
}

void OcclusionBuffer::Reset()
{
    numTriangles_ = 0;
}

void OcclusionBuffer::Clear()
{
    PROFILE(ClearOcclusion);
    
    if (!buffer_)
        return;
    
    Reset();
    
    int* dest = buffer_;
    int count = width_ * height_;
    
    while (count)
    {
        *dest++ = 0x7fffffff;
        --count;
    }
    
    depthHierarchyDirty_ = true;
}

bool OcclusionBuffer::Draw(const Matrix3x4& model, const unsigned char* vertexData, unsigned vertexSize,
    const unsigned char* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount)
{
    PROFILE(DrawOcclusion);
    
    Matrix4 modelViewProj = viewProj_ * model;
    depthHierarchyDirty_ = true;
    
    // Theoretical max. amount of vertices if each of the 6 clipping planes doubles the triangle count
    Vector4 vertices[64 * 3];
    
    // 16-bit indices
    if (indexSize == sizeof(unsigned short))
    {
        const unsigned short* indices = (const unsigned short*)indexData;
        
        for (unsigned i = indexStart; i < indexStart + indexCount; i += 3)
        {
            if (numTriangles_ >= max_Triangles)
                return false;
            
            const Vector3& v0 = *((const Vector3*)(&vertexData[indices[i] * vertexSize]));
            const Vector3& v1 = *((const Vector3*)(&vertexData[indices[i + 1] * vertexSize]));
            const Vector3& v2 = *((const Vector3*)(&vertexData[indices[i + 2] * vertexSize]));
            
            vertices[0] = ModelTransform(modelViewProj, v0);
            vertices[1] = ModelTransform(modelViewProj, v1);
            vertices[2] = ModelTransform(modelViewProj, v2);
            DrawTriangle(vertices);
        }
    }
    else
    {
        const unsigned* indices = (const unsigned*)indexData;
        
        for (unsigned i = indexStart; i < indexStart + indexCount; i += 3)
        {
            if (numTriangles_ >= max_Triangles)
                return false;
            
            const Vector3& v0 = *((const Vector3*)(&vertexData[indices[i] * vertexSize]));
            const Vector3& v1 = *((const Vector3*)(&vertexData[indices[i + 1] * vertexSize]));
            const Vector3& v2 = *((const Vector3*)(&vertexData[indices[i + 2] * vertexSize]));
            
            vertices[0] = ModelTransform(modelViewProj, v0);
            vertices[1] = ModelTransform(modelViewProj, v1);
            vertices[2] = ModelTransform(modelViewProj, v2);
            DrawTriangle(vertices);
        }
    }
    
    return true;
}

void OcclusionBuffer::BuildDepthHierarchy()
{
    PROFILE(BuildDepthHierarchy);
    
    if (!buffer_)
        return;
    
    // Build the first mip level from the pixel-level data
    int width = (width_ + 1) / 2;
    int height = (height_ + 1) / 2;
    if (mipBuffers_.Size())
    {
        for (int y = 0; y < height; ++y)
        {
            int* src = buffer_ + (y * 2) * width_;
            DepthValue* dest = mipBuffers_[0].Ptr() + y * width;
            DepthValue* end = dest + width;
            
            if (y * 2 + 1 < height_)
            {
                int* src2 = src + width_;
                while (dest < end)
                {
                    int minUpper = Min(src[0], src[1]);
                    int minLower = Min(src2[0], src2[1]);
                    dest->min_ = Min(minUpper, minLower);
                    int maxUpper = Max(src[0], src[1]);
                    int maxLower = Max(src2[0], src2[1]);
                    dest->max_ = Max(maxUpper, maxLower);
                    
                    src += 2;
                    src2 += 2;
                    ++dest;
                }
            }
            else
            {
                while (dest < end)
                {
                    dest->min_ = Min(src[0], src[1]);
                    dest->max_ = Max(src[0], src[1]);
                    
                    src += 2;
                    ++dest;
                }
            }
        }
    }
    
    // Build the rest of the mip levels
    for (unsigned i = 1; i < mipBuffers_.Size(); ++i)
    {
        int prevWidth = width;
        int prevHeight = height;
        width = (width + 1) / 2;
        height = (height + 1) / 2;
        
        for (int y = 0; y < height; ++y)
        {
            DepthValue* src = mipBuffers_[i - 1].Ptr() + (y * 2) * prevWidth;
            DepthValue* dest = mipBuffers_[i].Ptr() + y * width;
            DepthValue* end = dest + width;
            
            if (y * 2 + 1 < prevHeight)
            {
                DepthValue* src2 = src + prevWidth;
                while (dest < end)
                {
                    int minUpper = Min(src[0].min_, src[1].min_);
                    int minLower = Min(src2[0].min_, src2[1].min_);
                    dest->min_ = Min(minUpper, minLower);
                    int maxUpper = Max(src[0].max_, src[1].max_);
                    int maxLower = Max(src2[0].max_, src2[1].max_);
                    dest->max_ = Max(maxUpper, maxLower);
                    
                    src += 2;
                    src2 += 2;
                    ++dest;
                }
            }
            else
            {
                while (dest < end)
                {
                    dest->min_ = Min(src[0].min_, src[1].min_);
                    dest->max_ = Max(src[0].max_, src[1].max_);
                    
                    src += 2;
                    ++dest;
                }
            }
        }
    }
    
    depthHierarchyDirty_ = false;
}

bool OcclusionBuffer::IsVisible(const BoundingBox& worldSpaceBox) const
{
    if (!buffer_)
        return true;
    
    Vector3 vertices[8];
    
    // Transform corners to view space. Note: do not directly transform the bounding box, as this would expand it unnecessarily
    vertices[0] = view_ * worldSpaceBox.min_;
    vertices[1] = view_ * Vector3(worldSpaceBox.max_.x_, worldSpaceBox.min_.y_, worldSpaceBox.min_.z_);
    vertices[2] = view_ * Vector3(worldSpaceBox.min_.x_, worldSpaceBox.max_.y_, worldSpaceBox.min_.z_);
    vertices[3] = view_ * Vector3(worldSpaceBox.max_.x_, worldSpaceBox.max_.y_, worldSpaceBox.min_.z_);
    vertices[4] = view_ * Vector3(worldSpaceBox.min_.x_, worldSpaceBox.min_.y_, worldSpaceBox.max_.z_);
    vertices[5] = view_ * Vector3(worldSpaceBox.max_.x_, worldSpaceBox.min_.y_, worldSpaceBox.max_.z_);
    vertices[6] = view_ * Vector3(worldSpaceBox.min_.x_, worldSpaceBox.max_.y_, worldSpaceBox.max_.z_);
    vertices[7] = view_ * worldSpaceBox.max_;
    
    // Project to screen. If any of the corners cross the near plane, assume visible
    float minX, maxX, minY, maxY, minZ;
    
    // Subtract a small bias to prevent self-occlusion artifacts
    // (need for bias results from different floating point transformations producing different errors)
    vertices[0].z_ -= depthBias_;
    if (vertices[0].z_ <= nearClip_)
        return true;
    
    // Project the first corner to initialize the rectangle
    float invW = 1.0f / (vertices[0].z_ * projection_.m32_ + projection_.m33_);
    minX = maxX = invW * (projOffsetScaleX_ * vertices[0].x_) + offsetX_;
    minY = maxY = invW * (projOffsetScaleY_ * vertices[0].y_) + offsetY_;
    minZ = invW * (projection_.m22_ * vertices[0].z_ + projection_.m23_);
    
    // Project the rest
    for (unsigned i = 1; i < 8; ++i)
    {
        // Subtract a small bias to prevent self-occlusion artifacts
        vertices[i].z_ -= depthBias_;
        if (vertices[i].z_ <= nearClip_)
            return true;
        
        float invW = 1.0f / (vertices[i].z_ * projection_.m32_ + projection_.m33_);
        float x = invW * (projOffsetScaleX_ * vertices[i].x_) + offsetX_;
        float y = invW * (projOffsetScaleY_ * vertices[i].y_) + offsetY_;
        float z = invW * (projection_.m22_ * vertices[i].z_ + projection_.m23_);
        
        if (x < minX) minX = x;
        if (x > maxX) maxX = x;
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
        if (z < minZ) minZ = z;
    }
    
    // Expand the bounding box 1 pixel in each direction to be conservative and correct rasterization offset
    IntRect rect(
        (int)(minX - 1.5f), (int)(minY - 1.5f),
        (int)(maxX + 0.5f), (int)(maxY + 0.5f)
    );
    
    // If outside, can not test, so assume visible (should be frustum culled in that case)
    if (rect.right_ < 0 || rect.bottom_ < 0)
        return true;
    if (rect.left_ >= width_ || rect.top_ >= height_)
        return true;
    
    // Clipping of rect
    if (rect.left_ < 0)
        rect.left_ = 0;
    if (rect.top_ < 0)
        rect.top_ = 0;
    if (rect.right_ >= width_)
        rect.right_ = width_ - 1;
    if (rect.bottom_ >= height_)
        rect.bottom_ = height_ - 1;
    
    int z = ((int)(minZ * OCCLUSION_Z_SCALE));
    
    if (!depthHierarchyDirty_)
    {
        // Start from lowest mip level and check if a conclusive result can be found
        for (int i = mipBuffers_.Size() - 1; i >= 0; --i)
        {
            int shift = i + 1;
            int width = width_ >> shift;
            int left = rect.left_ >> shift;
            int right = rect.right_ >> shift;
            
            DepthValue* buffer = mipBuffers_[i].Ptr();
            DepthValue* row = buffer + (rect.top_ >> shift) * width;
            DepthValue* endRow = buffer + (rect.bottom_ >> shift) * width;
            bool allOccluded = true;
            
            while (row <= endRow)
            {
                DepthValue* src = row + left;
                DepthValue* end = row + right;
                while (src <= end)
                {
                    if (z <= src->min_)
                        return true;
                    if (z <= src->max_)
                        allOccluded = false;
                    ++src;
                }
                row += width;
            }
            
            if (allOccluded)
                return false;
        }
    }
    
    // If no conclusive result, finally check the pixel-level data
    int* row = buffer_ + rect.top_ * width_;
    int* endRow = buffer_ + rect.bottom_ * width_;
    while (row <= endRow)
    {
        int* src = row + rect.left_;
        int* end = row + rect.right_;
        while (src <= end)
        {
            if (z <= *src)
                return true;
            ++src;
        }
        row += width_;
    }
    
    return false;
}

inline Vector4 OcclusionBuffer::ModelTransform(const Matrix4& transform, const Vector3& vertex) const
{
    return Vector4(
        transform.m00_ * vertex.x_ + transform.m01_ * vertex.y_ + transform.m02_ * vertex.z_ + transform.m03_,
        transform.m10_ * vertex.x_ + transform.m11_ * vertex.y_ + transform.m12_ * vertex.z_ + transform.m13_,
        transform.m20_ * vertex.x_ + transform.m21_ * vertex.y_ + transform.m22_ * vertex.z_ + transform.m23_,
        transform.m30_ * vertex.x_ + transform.m31_ * vertex.y_ + transform.m32_ * vertex.z_ + transform.m33_
    );
}

inline Vector3 OcclusionBuffer::ViewportTransform(const Vector4& vertex) const
{
    float invW = 1.0f / vertex.w_;
    return Vector3(
        invW * vertex.x_ * scaleX_ + offsetX_,
        invW * vertex.y_ * scaleY_ + offsetY_,
        invW * vertex.z_ * OCCLUSION_Z_SCALE
    );
}

inline Vector4 OcclusionBuffer::ClipEdge(const Vector4& v0, const Vector4& v1, float d0, float d1) const
{
    float t = d0 / (d0 - d1);
    return v0 + t * (v1 - v0);
}

inline bool OcclusionBuffer::CheckFacing(const Vector3& v0, const Vector3& v1, const Vector3& v2) const
{
    if (cullMode_ == CULL_NONE)
        return true;
    
    float aX = v0.x_ - v1.x_;
    float aY = v0.y_ - v1.y_;
    float bX = v2.x_ - v1.x_;
    float bY = v2.y_ - v1.y_;
    float signedArea = aX * bY - aY * bX;
    
    if (cullMode_ == CULL_CCW)
        return signedArea < 0.0f;
    else
        return signedArea > 0.0f;
}

void OcclusionBuffer::CalculateViewport()
{
    // Add half pixel offset due to 3D frustum culling
    scaleX_ = 0.5f * width_;
    scaleY_ = -0.5f * height_;
    offsetX_ = 0.5f * width_ + 0.5f;
    offsetY_ = 0.5f * height_ + 0.5f;
    projOffsetScaleX_ = projection_.m00_ * scaleX_;
    projOffsetScaleY_ = projection_.m11_ * scaleY_;
}

void OcclusionBuffer::DrawTriangle(Vector4* vertices)
{
    unsigned clipMask = 0;
    unsigned andClipMask = 0;
    Vector3 projected[3];
    
    // Build the clip plane mask for the triangle
    for (unsigned i = 0; i < 3; ++i)
    {
        unsigned vertexClipMask = 0;
        
        if (vertices[i].x_ > vertices[i].w_)
            vertexClipMask |= CLIPMASK_X_POS;
        if (vertices[i].x_ < -vertices[i].w_)
            vertexClipMask |= CLIPMASK_X_NEG;
        if (vertices[i].y_ > vertices[i].w_)
            vertexClipMask |= CLIPMASK_Y_POS;
        if (vertices[i].y_ < -vertices[i].w_)
            vertexClipMask |= CLIPMASK_Y_NEG;
        if (vertices[i].z_ > vertices[i].w_)
            vertexClipMask |= CLIPMASK_Z_POS;
        if (vertices[i].z_ < 0.0f)
            vertexClipMask |= CLIPMASK_Z_NEG;
        
        clipMask |= vertexClipMask;
        
        if (!i)
            andClipMask = vertexClipMask;
        else
            andClipMask &= vertexClipMask;
    }
    
    // If triangle is fully behind any clip plane, can reject quickly
    if (andClipMask)
        return;
    
    // Check if triangle is fully inside
    if (!clipMask)
    {
        projected[0] = ViewportTransform(vertices[0]);
        projected[1] = ViewportTransform(vertices[1]);
        projected[2] = ViewportTransform(vertices[2]);
        
        if (CheckFacing(projected[0], projected[1], projected[2]))
            DrawTriangle2D(projected);
    }
    else
    {
        bool triangles[64];
        
        // Initial triangle
        triangles[0] = true;
        unsigned numTriangles = 1;
        
        if (clipMask & CLIPMASK_X_POS)
            ClipVertices(Vector4(-1.0f, 0.0f, 0.0f, 1.0f), vertices, triangles, numTriangles);
        if (clipMask & CLIPMASK_X_NEG)
            ClipVertices(Vector4(1.0f, 0.0f, 0.0f, 1.0f), vertices, triangles, numTriangles);
        if (clipMask & CLIPMASK_Y_POS)
            ClipVertices(Vector4(0.0f, -1.0f, 0.0f, 1.0f), vertices, triangles, numTriangles);
        if (clipMask & CLIPMASK_Y_NEG)
            ClipVertices(Vector4(0.0f, 1.0f, 0.0f, 1.0f), vertices, triangles, numTriangles);
        if (clipMask & CLIPMASK_Z_POS)
            ClipVertices(Vector4(0.0f, 0.0f, -1.0f, 1.0f), vertices, triangles, numTriangles);
        if (clipMask & CLIPMASK_Z_NEG)
            ClipVertices(Vector4(0.0f, 0.0f, 1.0f, 0.0f), vertices, triangles, numTriangles);
        
        // Draw each accepted triangle
        for (unsigned i = 0; i < numTriangles; ++i)
        {
            if (triangles[i])
            {
                unsigned index = i * 3;
                projected[0] = ViewportTransform(vertices[index]);
                projected[1] = ViewportTransform(vertices[index + 1]);
                projected[2] = ViewportTransform(vertices[index + 2]);
                
                if (CheckFacing(projected[0], projected[1], projected[2]))
                    DrawTriangle2D(projected);
            }
        }
    }
}

void OcclusionBuffer::ClipVertices(const Vector4& plane, Vector4* vertices, bool* triangles, unsigned& numTriangles)
{
    unsigned num = numTriangles;
    
    for (unsigned i = 0; i < num; ++i)
    {
        if (triangles[i])
        {
            unsigned index = i * 3;
            float d0 = plane.DotProduct(vertices[index]);
            float d1 = plane.DotProduct(vertices[index + 1]);
            float d2 = plane.DotProduct(vertices[index + 2]);
            
            // If all vertices behind the plane, reject triangle
            if (d0 < 0.0f && d1 < 0.0f && d2 < 0.0f)
            {
                triangles[i] = false;
                continue;
            }
            // If 2 vertices behind the plane, create a new triangle in-place
            else if (d0 < 0.0f && d1 < 0.0f)
            {
                vertices[index] = ClipEdge(vertices[index], vertices[index + 2], d0, d2);
                vertices[index + 1] = ClipEdge(vertices[index + 1], vertices[index + 2], d1, d2);
            }
            else if (d0 < 0.0f && d2 < 0.0f)
            {
                vertices[index] = ClipEdge(vertices[index], vertices[index + 1], d0, d1);
                vertices[index + 2] = ClipEdge(vertices[index + 2], vertices[index + 1], d2, d1);
            }
            else if (d1 < 0.0f && d2 < 0.0f)
            {
                vertices[index + 1] = ClipEdge(vertices[index + 1], vertices[index], d1, d0);
                vertices[index + 2] = ClipEdge(vertices[index + 2], vertices[index], d2, d0);
            }
            // 1 vertex behind the plane: create one new triangle, and modify one in-place
            else if (d0 < 0.0f)
            {
                unsigned newIdx = numTriangles * 3;
                triangles[numTriangles] = true;
                ++numTriangles;
                    
                vertices[newIdx] = ClipEdge(vertices[index], vertices[index + 1], d0, d1);
                vertices[newIdx + 1] = vertices[index + 1];
                vertices[newIdx + 2] = vertices[index] = ClipEdge(vertices[index], vertices[index + 2], d0, d2);
            }
            else if (d1 < 0.0f)
            {
                unsigned newIdx = numTriangles * 3;
                triangles[numTriangles] = true;
                ++numTriangles;
                    
                vertices[newIdx + 1] = ClipEdge(vertices[index + 1], vertices[index + 2], d1, d2);
                vertices[newIdx + 2] = vertices[index + 2];
                vertices[newIdx] = vertices[index + 1] = ClipEdge(vertices[index + 1], vertices[index], d1, d0);
            }
            else if (d2 < 0.0f)
            {
                unsigned newIdx = numTriangles * 3;
                triangles[numTriangles] = true;
                ++numTriangles;
                    
                vertices[newIdx + 2] = ClipEdge(vertices[index + 2], vertices[index], d2, d0);
                vertices[newIdx] = vertices[index];
                vertices[newIdx + 1] = vertices[index + 2] = ClipEdge(vertices[index + 2], vertices[index + 1], d2, d1);
            }
        }
    }
}

// Code based on Chris Hecker's Perspective Texture Mapping series in the Game Developer magazine
// Also available online at http://chrishecker.com/Miscellaneous_Technical_Articles

/// Gradients of a software rasterized triangle
struct Gradients
{
    /// Construct from vertices
    Gradients(const Vector3* vertices)
    {
        float invdX = 1.0f / (((vertices[1].x_ - vertices[2].x_) *
            (vertices[0].y_ - vertices[2].y_)) -
            ((vertices[0].x_ - vertices[2].x_) *
            (vertices[1].y_ - vertices[2].y_)));
        
        float invdY = -invdX;
        
        mDInvZdX = invdX * (((vertices[1].z_ - vertices[2].z_) * (vertices[0].y_ - vertices[2].y_)) -
            ((vertices[0].z_ - vertices[2].z_) * (vertices[1].y_ - vertices[2].y_)));
        
        mDInvZdY = invdY * (((vertices[1].z_ - vertices[2].z_) * (vertices[0].x_ - vertices[2].x_)) -
            ((vertices[0].z_ - vertices[2].z_) * (vertices[1].x_ - vertices[2].x_)));
        
        mDInvZdXInt = (int)mDInvZdX;
    }
    
    /// Integer horizontal gradient
    int mDInvZdXInt;
    /// Horizontal gradient
    float mDInvZdX;
    /// Vertical gradient
    float mDInvZdY;
};

/// Edge of a software rasterized triangle
struct Edge
{
    /// Construct from gradients and top & bottom vertices
    Edge(const Gradients& gradients, const Vector3& top, const Vector3& bottom, int topY)
    {
        float slope = (bottom.x_ - top.x_) / (bottom.y_ - top.y_);
        float yPreStep = (float)(topY + 1) - top.y_;
        float xPreStep = slope * yPreStep;
        
        x_ = (int)((xPreStep + top.x_) * OCCLUSION_X_SCALE);
        x_Step = (int)(slope * OCCLUSION_X_SCALE);
        mInvZ = (int)(top.z_ + xPreStep * gradients.mDInvZdX + yPreStep * gradients.mDInvZdY);
        mInvZStep = (int)(slope * gradients.mDInvZdX + gradients.mDInvZdY);
    }
    
    /// X coordinate
    int x_;
    /// X coordinate step
    int x_Step;
    /// Inverse Z
    int mInvZ;
    /// Inverse Z step
    int mInvZStep;
};

void OcclusionBuffer::DrawTriangle2D(const Vector3* vertices)
{
    int top, middle, bottom;
    bool middleIsRight;
    
    numTriangles_++;
    
    // Sort vertices in Y-direction
    if (vertices[0].y_ < vertices[1].y_)
    {
        if (vertices[2].y_ < vertices[0].y_)
        {
            top = 2; middle = 0; bottom = 1;
            middleIsRight = true;
        }
        else
        {
            top = 0;
            if (vertices[1].y_ < vertices[2].y_)
            {
                middle = 1; bottom = 2;
                middleIsRight = true;
            }
            else
            {
                middle = 2; bottom = 1;
                middleIsRight = false;
            }
        }
    }
    else
    {
        if (vertices[2].y_ < vertices[1].y_)
        {
            top = 2; middle = 1; bottom = 0;
            middleIsRight = false;
        }
        else
        {
            top = 1;
            if (vertices[0].y_ < vertices[2].y_)
            {
                middle = 0; bottom = 2;
                middleIsRight = false;
            }
            else
            {
                middle = 2; bottom = 0;
                middleIsRight = true;
            }
        }
    }
    
    int topY = (int)vertices[top].y_;
    int middleY = (int)vertices[middle].y_;
    int bottoy_ = (int)vertices[bottom].y_;
    
    // Check for degenerate triangle
    if (topY == bottoy_)
        return;
    
    Gradients gradients(vertices);
    Edge topToMiddle(gradients, vertices[top], vertices[middle], topY);
    Edge topToBottom(gradients, vertices[top], vertices[bottom], topY);
    Edge middleToBottom(gradients, vertices[middle], vertices[bottom], middleY);
    
    // The triangle is clockwise, so if bottom > middle then middle is right
    if (middleIsRight)
    {
        // Top half
        int* row = buffer_ + topY * width_;
        int* endRow = buffer_ + middleY * width_;
        while (row < endRow)
        {
            int invZ = topToBottom.mInvZ;
            int* dest = row + (topToBottom.x_ >> 16);
            int* end = row + (topToMiddle.x_ >> 16);
            while (dest < end)
            {
                if (invZ < *dest)
                    *dest = invZ;
                invZ += gradients.mDInvZdXInt;
                ++dest;
            }
            
            topToBottom.x_ += topToBottom.x_Step;
            topToBottom.mInvZ += topToBottom.mInvZStep;
            topToMiddle.x_ += topToMiddle.x_Step;
            row += width_;
        }
        
        // Bottom half
        row = buffer_ + middleY * width_;
        endRow = buffer_ + bottoy_ * width_;
        while (row < endRow)
        {
            int invZ = topToBottom.mInvZ;
            int* dest = row + (topToBottom.x_ >> 16);
            int* end = row + (middleToBottom.x_ >> 16);
            while (dest < end)
            {
                if (invZ < *dest)
                    *dest = invZ;
                invZ += gradients.mDInvZdXInt;
                ++dest;
            }
            
            topToBottom.x_ += topToBottom.x_Step;
            topToBottom.mInvZ += topToBottom.mInvZStep;
            middleToBottom.x_ += middleToBottom.x_Step;
            row += width_;
        }
    }
    else
    {
        // Top half
        int* row = buffer_ + topY * width_;
        int* endRow = buffer_ + middleY * width_;
        while (row < endRow)
        {
            int invZ = topToMiddle.mInvZ;
            int* dest = row + (topToMiddle.x_ >> 16);
            int* end = row + (topToBottom.x_ >> 16);
            while (dest < end)
            {
                if (invZ < *dest)
                    *dest = invZ;
                invZ += gradients.mDInvZdXInt;
                ++dest;
            }
            
            topToMiddle.x_ += topToMiddle.x_Step;
            topToMiddle.mInvZ += topToMiddle.mInvZStep;
            topToBottom.x_ += topToBottom.x_Step;
            row += width_;
        }
        
        // Bottom half
        row = buffer_ + middleY * width_;
        endRow = buffer_ + bottoy_ * width_;
        while (row < endRow)
        {
            int invZ = middleToBottom.mInvZ;
            int* dest = row + (middleToBottom.x_ >> 16);
            int* end = row + (topToBottom.x_ >> 16);
            while (dest < end)
            {
                if (invZ < *dest)
                    *dest = invZ;
                invZ += gradients.mDInvZdXInt;
                ++dest;
            }
            
            middleToBottom.x_ += middleToBottom.x_Step;
            middleToBottom.mInvZ += middleToBottom.mInvZStep;
            topToBottom.x_ += topToBottom.x_Step;
            row += width_;
        }
    }
}
