//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Graphics/Camera.h"
#include "../IO/Log.h"
#include "../Graphics/OcclusionBuffer.h"

#include <cstring>

#include "../DebugNew.h"

namespace Urho3D
{

static const unsigned CLIPMASK_X_POS = 0x1;
static const unsigned CLIPMASK_X_NEG = 0x2;
static const unsigned CLIPMASK_Y_POS = 0x4;
static const unsigned CLIPMASK_Y_NEG = 0x8;
static const unsigned CLIPMASK_Z_POS = 0x10;
static const unsigned CLIPMASK_Z_NEG = 0x20;

OcclusionBuffer::OcclusionBuffer(Context* context) :
    Object(context),
    buffer_(0),
    width_(0),
    height_(0),
    numTriangles_(0),
    maxTriangles_(OCCLUSION_DEFAULT_MAX_TRIANGLES),
    cullMode_(CULL_CCW),
    depthHierarchyDirty_(true),
    reverseCulling_(false),
    nearClip_(0.0f),
    farClip_(0.0f)
{
}

OcclusionBuffer::~OcclusionBuffer()
{
}

bool OcclusionBuffer::SetSize(int width, int height)
{
    // Force the height to an even amount of pixels for better mip generation
    if (height & 1)
        ++height;
    
    if (width == width_ && height == height_)
        return true;
    
    if (width <= 0 || height <= 0)
        return false;
    
    if (!IsPowerOfTwo(width))
    {
        LOGERROR("Width is not a power of two");
        return false;
    }
    
    width_ = width;
    height_ = height;
    
    // Reserve extra memory in case 3D clipping is not exact
    fullBuffer_ = new int[width * (height + 2) + 2];
    buffer_ = fullBuffer_.Get() + width + 1;
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
    
    view_ = camera->GetView();
    projection_ = camera->GetProjection(false);
    viewProj_ = projection_ * view_;
    nearClip_ = camera->GetNearClip();
    farClip_ = camera->GetFarClip();
    reverseCulling_ = camera->GetReverseCulling();
    CalculateViewport();
}

void OcclusionBuffer::SetMaxTriangles(unsigned triangles)
{
    maxTriangles_ = triangles;
}

void OcclusionBuffer::SetCullMode(CullMode mode)
{
    if (reverseCulling_)
    {
        if (mode == CULL_CW)
            mode = CULL_CCW;
        else if (mode == CULL_CCW)
            mode = CULL_CW;
    }
    cullMode_ = mode;
}

void OcclusionBuffer::Reset()
{
    numTriangles_ = 0;
}

void OcclusionBuffer::Clear()
{
    if (!buffer_)
        return;
    
    Reset();
    
    int* dest = buffer_;
    int count = width_ * height_;
    
    while (count--)
        *dest++ = 0x7fffffff;
    
    depthHierarchyDirty_ = true;
}

bool OcclusionBuffer::Draw(const Matrix3x4& model, const void* vertexData, unsigned vertexSize, unsigned vertexStart, unsigned vertexCount)
{
    const unsigned char* srcData = ((const unsigned char*)vertexData) + vertexStart * vertexSize;
    
    Matrix4 modelViewProj = viewProj_ * model;
    depthHierarchyDirty_ = true;
    
    // Theoretical max. amount of vertices if each of the 6 clipping planes doubles the triangle count
    Vector4 vertices[64 * 3];
    
    // 16-bit indices
    unsigned index = 0;
    while (index + 2 < vertexCount)
    {
        if (numTriangles_ >= maxTriangles_)
            return false;
        
        const Vector3& v0 = *((const Vector3*)(&srcData[index * vertexSize]));
        const Vector3& v1 = *((const Vector3*)(&srcData[(index + 1) * vertexSize]));
        const Vector3& v2 = *((const Vector3*)(&srcData[(index + 2) * vertexSize]));
        
        vertices[0] = ModelTransform(modelViewProj, v0);
        vertices[1] = ModelTransform(modelViewProj, v1);
        vertices[2] = ModelTransform(modelViewProj, v2);
        DrawTriangle(vertices);
        
        index += 3;
    }
    
    return true;
}

bool OcclusionBuffer::Draw(const Matrix3x4& model, const void* vertexData, unsigned vertexSize, const void* indexData,
    unsigned indexSize, unsigned indexStart, unsigned indexCount)
{
    const unsigned char* srcData = (const unsigned char*)vertexData;
    
    Matrix4 modelViewProj = viewProj_ * model;
    depthHierarchyDirty_ = true;
    
    // Theoretical max. amount of vertices if each of the 6 clipping planes doubles the triangle count
    Vector4 vertices[64 * 3];
    
    // 16-bit indices
    if (indexSize == sizeof(unsigned short))
    {
        const unsigned short* indices = ((const unsigned short*)indexData) + indexStart;
        const unsigned short* indicesEnd = indices + indexCount;
        
        while (indices < indicesEnd)
        {
            if (numTriangles_ >= maxTriangles_)
                return false;
            
            const Vector3& v0 = *((const Vector3*)(&srcData[indices[0] * vertexSize]));
            const Vector3& v1 = *((const Vector3*)(&srcData[indices[1] * vertexSize]));
            const Vector3& v2 = *((const Vector3*)(&srcData[indices[2] * vertexSize]));
            
            vertices[0] = ModelTransform(modelViewProj, v0);
            vertices[1] = ModelTransform(modelViewProj, v1);
            vertices[2] = ModelTransform(modelViewProj, v2);
            DrawTriangle(vertices);
            
            indices += 3;
        }
    }
    else
    {
        const unsigned* indices = ((const unsigned*)indexData) + indexStart;
        const unsigned* indicesEnd = indices + indexCount;
        
        while (indices < indicesEnd)
        {
            if (numTriangles_ >= maxTriangles_)
                return false;
            
            const Vector3& v0 = *((const Vector3*)(&srcData[indices[0] * vertexSize]));
            const Vector3& v1 = *((const Vector3*)(&srcData[indices[1] * vertexSize]));
            const Vector3& v2 = *((const Vector3*)(&srcData[indices[2] * vertexSize]));
            
            vertices[0] = ModelTransform(modelViewProj, v0);
            vertices[1] = ModelTransform(modelViewProj, v1);
            vertices[2] = ModelTransform(modelViewProj, v2);
            DrawTriangle(vertices);
            
            indices += 3;
        }
    }
    
    return true;
}

void OcclusionBuffer::BuildDepthHierarchy()
{
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
            DepthValue* dest = mipBuffers_[0].Get() + y * width;
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
            DepthValue* src = mipBuffers_[i - 1].Get() + (y * 2) * prevWidth;
            DepthValue* dest = mipBuffers_[i].Get() + y * width;
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

void OcclusionBuffer::ResetUseTimer()
{
    useTimer_.Reset();
}

bool OcclusionBuffer::IsVisible(const BoundingBox& worldSpaceBox) const
{
    if (!buffer_)
        return true;
    
    // Transform corners to projection space
    Vector4 vertices[8];
    vertices[0] = ModelTransform(viewProj_, worldSpaceBox.min_);
    vertices[1] = ModelTransform(viewProj_, Vector3(worldSpaceBox.max_.x_, worldSpaceBox.min_.y_, worldSpaceBox.min_.z_));
    vertices[2] = ModelTransform(viewProj_, Vector3(worldSpaceBox.min_.x_, worldSpaceBox.max_.y_, worldSpaceBox.min_.z_));
    vertices[3] = ModelTransform(viewProj_, Vector3(worldSpaceBox.max_.x_, worldSpaceBox.max_.y_, worldSpaceBox.min_.z_));
    vertices[4] = ModelTransform(viewProj_, Vector3(worldSpaceBox.min_.x_, worldSpaceBox.min_.y_, worldSpaceBox.max_.z_));
    vertices[5] = ModelTransform(viewProj_, Vector3(worldSpaceBox.max_.x_, worldSpaceBox.min_.y_, worldSpaceBox.max_.z_));
    vertices[6] = ModelTransform(viewProj_, Vector3(worldSpaceBox.min_.x_, worldSpaceBox.max_.y_, worldSpaceBox.max_.z_));
    vertices[7] = ModelTransform(viewProj_, worldSpaceBox.max_);
    
    // Apply a far clip relative bias
    for (unsigned i = 0; i < 8; ++i)
        vertices[i].z_ -= OCCLUSION_RELATIVE_BIAS;
    
    // Transform to screen space. If any of the corners cross the near plane, assume visible
    float minX, maxX, minY, maxY, minZ;
    
    if (vertices[0].z_ <= 0.0f)
        return true;
    
    Vector3 projected = ViewportTransform(vertices[0]);
    minX = maxX = projected.x_;
    minY = maxY = projected.y_;
    minZ = projected.z_;
    
    // Project the rest
    for (unsigned i = 1; i < 8; ++i)
    {
        if (vertices[i].z_ <= 0.0f)
            return true;
        
        projected = ViewportTransform(vertices[i]);
        
        if (projected.x_ < minX) minX = projected.x_;
        if (projected.x_ > maxX) maxX = projected.x_;
        if (projected.y_ < minY) minY = projected.y_;
        if (projected.y_ > maxY) maxY = projected.y_;
        if (projected.z_ < minZ) minZ = projected.z_;
    }
    
    // Expand the bounding box 1 pixel in each direction to be conservative and correct rasterization offset
    IntRect rect(
        (int)(minX - 1.5f), (int)(minY - 1.5f),
        (int)(maxX + 0.5f), (int)(maxY + 0.5f)
    );
    
    // If the rect is outside, let frustum culling handle
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
    
    // Convert depth to integer and apply final bias
    int z = (int)(minZ + 0.5f) - OCCLUSION_FIXED_BIAS;
    
    if (!depthHierarchyDirty_)
    {
        // Start from lowest mip level and check if a conclusive result can be found
        for (int i = mipBuffers_.Size() - 1; i >= 0; --i)
        {
            int shift = i + 1;
            int width = width_ >> shift;
            int left = rect.left_ >> shift;
            int right = rect.right_ >> shift;
            
            DepthValue* buffer = mipBuffers_[i].Get();
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

unsigned OcclusionBuffer::GetUseTimer()
{
    return useTimer_.GetMSec(false);
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

inline float OcclusionBuffer::SignedArea(const Vector3& v0, const Vector3& v1, const Vector3& v2) const
{
    float aX = v0.x_ - v1.x_;
    float aY = v0.y_ - v1.y_;
    float bX = v2.x_ - v1.x_;
    float bY = v2.y_ - v1.y_;
    return aX * bY - aY * bX;
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
    bool drawOk = false;
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
        
        bool clockwise = SignedArea(projected[0], projected[1], projected[2]) < 0.0f;
        if (cullMode_ == CULL_NONE || (cullMode_ == CULL_CCW && clockwise) || (cullMode_ == CULL_CW && !clockwise))
        {
            DrawTriangle2D(projected, clockwise);
            drawOk = true;
        }
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
                
                bool clockwise = SignedArea(projected[0], projected[1], projected[2]) < 0.0f;
                if (cullMode_ == CULL_NONE || (cullMode_ == CULL_CCW && clockwise) || (cullMode_ == CULL_CW && !clockwise))
                {
                    DrawTriangle2D(projected, clockwise);
                    drawOk = true;
                }
            }
        }
    }
    
    if (drawOk)
        ++numTriangles_;
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
                
                vertices[newIdx] = ClipEdge(vertices[index], vertices[index + 2], d0, d2);
                vertices[newIdx + 1] = vertices[index] = ClipEdge(vertices[index], vertices[index + 1], d0, d1);
                vertices[newIdx + 2] = vertices[index + 2];
            }
            else if (d1 < 0.0f)
            {
                unsigned newIdx = numTriangles * 3;
                triangles[numTriangles] = true;
                ++numTriangles;
                
                vertices[newIdx + 1] = ClipEdge(vertices[index + 1], vertices[index], d1, d0);
                vertices[newIdx + 2] = vertices[index + 1] = ClipEdge(vertices[index + 1], vertices[index + 2], d1, d2);
                vertices[newIdx] = vertices[index];
            }
            else if (d2 < 0.0f)
            {
                unsigned newIdx = numTriangles * 3;
                triangles[numTriangles] = true;
                ++numTriangles;
                
                vertices[newIdx + 2] = ClipEdge(vertices[index + 2], vertices[index + 1], d2, d1);
                vertices[newIdx] = vertices[index + 2] = ClipEdge(vertices[index + 2], vertices[index], d2, d0);
                vertices[newIdx + 1] = vertices[index + 1];
            }
        }
    }
}

// Code based on Chris Hecker's Perspective Texture Mapping series in the Game Developer magazine
// Also available online at http://chrishecker.com/Miscellaneous_Technical_Articles

/// %Gradients of a software rasterized triangle.
struct Gradients
{
    /// Construct from vertices.
    Gradients(const Vector3* vertices)
    {
        float invdX = 1.0f / (((vertices[1].x_ - vertices[2].x_) *
            (vertices[0].y_ - vertices[2].y_)) -
            ((vertices[0].x_ - vertices[2].x_) *
            (vertices[1].y_ - vertices[2].y_)));
        
        float invdY = -invdX;
        
        dInvZdX_ = invdX * (((vertices[1].z_ - vertices[2].z_) * (vertices[0].y_ - vertices[2].y_)) -
            ((vertices[0].z_ - vertices[2].z_) * (vertices[1].y_ - vertices[2].y_)));
        
        dInvZdY_ = invdY * (((vertices[1].z_ - vertices[2].z_) * (vertices[0].x_ - vertices[2].x_)) -
            ((vertices[0].z_ - vertices[2].z_) * (vertices[1].x_ - vertices[2].x_)));
        
        dInvZdXInt_ = (int)dInvZdX_;
    }
    
    /// Integer horizontal gradient.
    int dInvZdXInt_;
    /// Horizontal gradient.
    float dInvZdX_;
    /// Vertical gradient.
    float dInvZdY_;
};

/// %Edge of a software rasterized triangle.
struct Edge
{
    /// Construct from gradients and top & bottom vertices.
    Edge(const Gradients& gradients, const Vector3& top, const Vector3& bottom, int topY)
    {
        float height = (bottom.y_ - top.y_);
        float slope = (height != 0.0f) ? (bottom.x_ - top.x_) / height : 0.0f;
        float yPreStep = (float)(topY + 1) - top.y_;
        float xPreStep = slope * yPreStep;
        
        x_ = (int)((xPreStep + top.x_) * OCCLUSION_X_SCALE + 0.5f);
        xStep_ = (int)(slope * OCCLUSION_X_SCALE + 0.5f);
        invZ_ = (int)(top.z_ + xPreStep * gradients.dInvZdX_ + yPreStep * gradients.dInvZdY_ + 0.5f);
        invZStep_ = (int)(slope * gradients.dInvZdX_ + gradients.dInvZdY_ + 0.5f);
    }
    
    /// X coordinate.
    int x_;
    /// X coordinate step.
    int xStep_;
    /// Inverse Z.
    int invZ_;
    /// Inverse Z step.
    int invZStep_;
};

void OcclusionBuffer::DrawTriangle2D(const Vector3* vertices, bool clockwise)
{
    int top, middle, bottom;
    bool middleIsRight;
    
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
    int bottomY = (int)vertices[bottom].y_;
    
    // Check for degenerate triangle
    if (topY == bottomY)
        return;
    
    // Reverse middleIsRight test if triangle is counterclockwise
    if (!clockwise)
        middleIsRight = !middleIsRight;

    Gradients gradients(vertices);
    Edge topToMiddle(gradients, vertices[top], vertices[middle], topY);
    Edge topToBottom(gradients, vertices[top], vertices[bottom], topY);
    Edge middleToBottom(gradients, vertices[middle], vertices[bottom], middleY);
    
    if (middleIsRight)
    {
        // Top half
        int* row = buffer_ + topY * width_;
        int* endRow = buffer_ + middleY * width_;
        while (row < endRow)
        {
            int invZ = topToBottom.invZ_;
            int* dest = row + (topToBottom.x_ >> 16);
            int* end = row + (topToMiddle.x_ >> 16);
            while (dest < end)
            {
                if (invZ < *dest)
                    *dest = invZ;
                invZ += gradients.dInvZdXInt_;
                ++dest;
            }
            
            topToBottom.x_ += topToBottom.xStep_;
            topToBottom.invZ_ += topToBottom.invZStep_;
            topToMiddle.x_ += topToMiddle.xStep_;
            row += width_;
        }
        
        // Bottom half
        row = buffer_ + middleY * width_;
        endRow = buffer_ + bottomY * width_;
        while (row < endRow)
        {
            int invZ = topToBottom.invZ_;
            int* dest = row + (topToBottom.x_ >> 16);
            int* end = row + (middleToBottom.x_ >> 16);
            while (dest < end)
            {
                if (invZ < *dest)
                    *dest = invZ;
                invZ += gradients.dInvZdXInt_;
                ++dest;
            }
            
            topToBottom.x_ += topToBottom.xStep_;
            topToBottom.invZ_ += topToBottom.invZStep_;
            middleToBottom.x_ += middleToBottom.xStep_;
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
            int invZ = topToMiddle.invZ_;
            int* dest = row + (topToMiddle.x_ >> 16);
            int* end = row + (topToBottom.x_ >> 16);
            while (dest < end)
            {
                if (invZ < *dest)
                    *dest = invZ;
                invZ += gradients.dInvZdXInt_;
                ++dest;
            }
            
            topToMiddle.x_ += topToMiddle.xStep_;
            topToMiddle.invZ_ += topToMiddle.invZStep_;
            topToBottom.x_ += topToBottom.xStep_;
            row += width_;
        }
        
        // Bottom half
        row = buffer_ + middleY * width_;
        endRow = buffer_ + bottomY * width_;
        while (row < endRow)
        {
            int invZ = middleToBottom.invZ_;
            int* dest = row + (middleToBottom.x_ >> 16);
            int* end = row + (topToBottom.x_ >> 16);
            while (dest < end)
            {
                if (invZ < *dest)
                    *dest = invZ;
                invZ += gradients.dInvZdXInt_;
                ++dest;
            }
            
            middleToBottom.x_ += middleToBottom.xStep_;
            middleToBottom.invZ_ += middleToBottom.invZStep_;
            topToBottom.x_ += topToBottom.xStep_;
            row += width_;
        }
    }
}

}
