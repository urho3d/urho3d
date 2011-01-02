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
#include "IndexBuffer.h"
#include "Log.h"
#include "OcclusionBuffer.h"
#include "Profiler.h"
#include "StringUtils.h"
#include "VertexBuffer.h"

#include <cstring>

#include "DebugNew.h"

static const unsigned CLIPMASK_X_POS = 0x1;
static const unsigned CLIPMASK_X_NEG = 0x2;
static const unsigned CLIPMASK_Y_POS = 0x4;
static const unsigned CLIPMASK_Y_NEG = 0x8;
static const unsigned CLIPMASK_Z_POS = 0x10;
static const unsigned CLIPMASK_Z_NEG = 0x20;

OcclusionBuffer::OcclusionBuffer() :
    mBuffer(0),
    mWidth(0),
    mHeight(0),
    mNumTriangles(0),
    mMaxTriangles(OCCLUSION_DEFAULT_MAX_TRIANGLES),
    mCullMode(CULL_CCW),
    mHierarchyDirty(true),
    mNearClip(0.0f),
    mFarClip(0.0f),
    mDepthBias(0.0f)
{
}

OcclusionBuffer::~OcclusionBuffer()
{
}

bool OcclusionBuffer::setSize(int width, int height)
{
    if ((width == mWidth) && (height == mHeight))
        return true;
    
    if ((width <= 0) || (height <= 0))
        return false;
    
    if (!isPowerOfTwo(width))
    {
        LOGERROR("Width is not a power of two");
        return false;
    }
    
    PROFILE(Occlusion_SetSize);
    
    mWidth = width;
    mHeight = height;
    // Reserve extra memory in case 3D clipping is not exact
    mFullBuffer = new int[width * (height + 2)];
    mBuffer = mFullBuffer.getPtr() + 1 * width;
    mReducedBuffers.clear();
    
    // Build buffers for reduced levels
    for (;;)
    {
        width = (width + 1) / 2;
        height = (height + 1) / 2;
        
        mReducedBuffers.push_back(SharedArrayPtr<DepthValue>(new DepthValue[width * height]));
        
        if ((width <= OCCLUSION_MIN_SIZE) && (height <= OCCLUSION_MIN_SIZE))
            break;
    }
    
    LOGINFO("Set occlusion buffer size " + toString(mWidth) + "x" + toString(mHeight) + " with " + 
        toString(mReducedBuffers.size()) + " reduced levels");
    
    calculateViewport();
    return true;
}

void OcclusionBuffer::setView(Camera& camera)
{
    mView = camera.getInverseWorldTransform();
    mProjection = camera.getProjection();
    mViewProj = mProjection * mView;
    mNearClip = camera.getNearClip();
    mFarClip = camera.getFarClip();
    mDepthBias = mFarClip * 0.00002f;
    calculateViewport();
}

void OcclusionBuffer::setMaxTriangles(unsigned triangles)
{
    mMaxTriangles = triangles;
}

void OcclusionBuffer::setCullMode(CullMode mode)
{
    mCullMode = mode;
}

void OcclusionBuffer::reset()
{
    mNumTriangles = 0;
}

void OcclusionBuffer::clear()
{
    PROFILE(Occlusion_Clear);
    
    if (!mBuffer)
        return;
    
    reset();
    
    int* dest = mBuffer;
    int count = mWidth * mHeight;
    
    while (count)
    {
        *dest++ = 0x7fffffff;
        --count;
    }
    
    mHierarchyDirty = true;
}

bool OcclusionBuffer::draw(const Matrix4x3& model, const unsigned char* vertexData, unsigned vertexSize,
    const unsigned char* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount)
{
    PROFILE(Occlusion_DrawGeometry);
    
    Matrix4 modelViewProj = mViewProj * model;
    mHierarchyDirty = true;
    
    // Theoretical max. amount of vertices if each of the 6 clipping planes doubles the triangle count
    Vector4 vertices[64 * 3];
    
    // 16-bit indices
    if (indexSize == sizeof(unsigned short))
    {
        const unsigned short* indices = (const unsigned short*)indexData;
        
        for (unsigned i = indexStart; i < indexStart + indexCount; i += 3)
        {
            if (mNumTriangles >= mMaxTriangles)
                return false;
            
            const Vector3& v0 = *((const Vector3*)(&vertexData[indices[i] * vertexSize]));
            const Vector3& v1 = *((const Vector3*)(&vertexData[indices[i + 1] * vertexSize]));
            const Vector3& v2 = *((const Vector3*)(&vertexData[indices[i + 2] * vertexSize]));
            
            vertices[0] = modelTransform(modelViewProj, v0);
            vertices[1] = modelTransform(modelViewProj, v1);
            vertices[2] = modelTransform(modelViewProj, v2);
            drawTriangle(vertices);
        }
    }
    else
    {
        const unsigned* indices = (const unsigned*)indexData;
        
        for (unsigned i = indexStart; i < indexStart + indexCount; i += 3)
        {
            if (mNumTriangles >= mMaxTriangles)
                return false;
            
            const Vector3& v0 = *((const Vector3*)(&vertexData[indices[i] * vertexSize]));
            const Vector3& v1 = *((const Vector3*)(&vertexData[indices[i + 1] * vertexSize]));
            const Vector3& v2 = *((const Vector3*)(&vertexData[indices[i + 2] * vertexSize]));
            
            vertices[0] = modelTransform(modelViewProj, v0);
            vertices[1] = modelTransform(modelViewProj, v1);
            vertices[2] = modelTransform(modelViewProj, v2);
            drawTriangle(vertices);
        }
    }
    
    return true;
}

void OcclusionBuffer::buildDepthHierarchy()
{
    PROFILE(Occlusion_BuildDepthHierarchy);
    
    if (!mBuffer)
        return;
    
    // Build the first reduced level from the pixel-level data
    int width = (mWidth + 1) / 2;
    int height = (mHeight + 1) / 2;
    if (mReducedBuffers.size())
    {
        for (int y = 0; y < height; ++y)
        {
            int* src = mBuffer + (y * 2) * mWidth;
            DepthValue* dest = mReducedBuffers[0].getPtr() + y * width;
            DepthValue* end = dest + width;
            
            if (y * 2 + 1 < mHeight)
            {
                int* src2 = src + mWidth;
                while (dest < end)
                {
                    int minUpper = min(src[0], src[1]);
                    int minLower = min(src2[0], src2[1]);
                    dest->mMin = min(minUpper, minLower);
                    int maxUpper = max(src[0], src[1]);
                    int maxLower = max(src2[0], src2[1]);
                    dest->mMax = max(maxUpper, maxLower);
                    
                    src += 2;
                    src2 += 2;
                    ++dest;
                }
            }
            else
            {
                while (dest < end)
                {
                    dest->mMin = min(src[0], src[1]);
                    dest->mMax = max(src[0], src[1]);
                    
                    src += 2;
                    ++dest;
                }
            }
        }
    }
    
    // Build the rest of the reduced levels
    for (unsigned i = 1; i < mReducedBuffers.size(); ++i)
    {
        int prevWidth = width;
        int prevHeight = height;
        width = (width + 1) / 2;
        height = (height + 1) / 2;
        
        for (int y = 0; y < height; ++y)
        {
            DepthValue* src = mReducedBuffers[i - 1].getPtr() + (y * 2) * prevWidth;
            DepthValue* dest = mReducedBuffers[i].getPtr() + y * width;
            DepthValue* end = dest + width;
            
            if (y * 2 + 1 < prevHeight)
            {
                DepthValue* src2 = src + prevWidth;
                while (dest < end)
                {
                    int minUpper = min(src[0].mMin, src[1].mMin);
                    int minLower = min(src2[0].mMin, src2[1].mMin);
                    dest->mMin = min(minUpper, minLower);
                    int maxUpper = max(src[0].mMax, src[1].mMax);
                    int maxLower = max(src2[0].mMax, src2[1].mMax);
                    dest->mMax = max(maxUpper, maxLower);
                    
                    src += 2;
                    src2 += 2;
                    ++dest;
                }
            }
            else
            {
                while (dest < end)
                {
                    dest->mMin = min(src[0].mMin, src[1].mMin);
                    dest->mMax = max(src[0].mMax, src[1].mMax);
                    
                    src += 2;
                    ++dest;
                }
            }
        }
    }
    
    mHierarchyDirty = false;
}

bool OcclusionBuffer::isVisible(const BoundingBox& worldSpaceBox) const
{
    if (!mBuffer)
        return true;
    
    Vector3 vertices[8];
    
    // Transform corners to view space. Note: do not directly transform the bounding box, as this would expand it unnecessarily
    vertices[0] = mView * worldSpaceBox.mMin;
    vertices[1] = mView * Vector3(worldSpaceBox.mMax.mX, worldSpaceBox.mMin.mY, worldSpaceBox.mMin.mZ);
    vertices[2] = mView * Vector3(worldSpaceBox.mMin.mX, worldSpaceBox.mMax.mY, worldSpaceBox.mMin.mZ);
    vertices[3] = mView * Vector3(worldSpaceBox.mMax.mX, worldSpaceBox.mMax.mY, worldSpaceBox.mMin.mZ);
    vertices[4] = mView * Vector3(worldSpaceBox.mMin.mX, worldSpaceBox.mMin.mY, worldSpaceBox.mMax.mZ);
    vertices[5] = mView * Vector3(worldSpaceBox.mMax.mX, worldSpaceBox.mMin.mY, worldSpaceBox.mMax.mZ);
    vertices[6] = mView * Vector3(worldSpaceBox.mMin.mX, worldSpaceBox.mMax.mY, worldSpaceBox.mMax.mZ);
    vertices[7] = mView * worldSpaceBox.mMax;
    
    // Project to screen. If any of the corners cross the near plane, assume visible
    float minX, maxX, minY, maxY, minZ;
    
    // Subtract a small bias to prevent self-occlusion artifacts
    // (need for bias results from different floating point transformations producing different errors)
    vertices[0].mZ -= mDepthBias;
    if (vertices[0].mZ <= mNearClip)
        return true;
    
    // Project the first corner to initialize the rectangle
    float invW = 1.0f / (vertices[0].mZ * mProjection.m32 + mProjection.m33);
    minX = maxX = invW * (mProjOffsetScaleX * vertices[0].mX) + mOffsetX;
    minY = maxY = invW * (mProjOffsetScaleY * vertices[0].mY) + mOffsetY;
    minZ = invW * (mProjection.m22 * vertices[0].mZ + mProjection.m23);
    
    // Project the rest
    for (unsigned i = 1; i < 8; ++i)
    {
        // Subtract a small bias to prevent self-occlusion artifacts
        vertices[i].mZ -= mDepthBias;
        if (vertices[i].mZ <= mNearClip)
            return true;
        
        float invW = 1.0f / (vertices[i].mZ * mProjection.m32 + mProjection.m33);
        float x = invW * (mProjOffsetScaleX * vertices[i].mX) + mOffsetX;
        float y = invW * (mProjOffsetScaleY * vertices[i].mY) + mOffsetY;
        float z = invW * (mProjection.m22 * vertices[i].mZ + mProjection.m23);
        
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
    if ((rect.mRight < 0) || (rect.mBottom < 0))
        return true;
    if ((rect.mLeft >= mWidth) || (rect.mTop >= mHeight))
        return true;
    
    // Clipping of rect
    if (rect.mLeft < 0)
        rect.mLeft = 0;
    if (rect.mTop < 0)
        rect.mTop = 0;
    if (rect.mRight >= mWidth)
        rect.mRight = mWidth - 1;
    if (rect.mBottom >= mHeight)
        rect.mBottom = mHeight - 1;
    
    int z = ((int)(minZ * OCCLUSION_Z_SCALE));
    
    if (!mHierarchyDirty)
    {
        // Start from lowest reduced level and check if a conclusive result can be found
        for (int i = mReducedBuffers.size() - 1; i >= 0; --i)
        {
            int shift = i + 1;
            int width = mWidth >> shift;
            int left = rect.mLeft >> shift;
            int right = rect.mRight >> shift;
            
            DepthValue* buffer = mReducedBuffers[i].getPtr();
            DepthValue* row = buffer + (rect.mTop >> shift) * width;
            DepthValue* endRow = buffer + (rect.mBottom >> shift) * width;
            bool allOccluded = true;
            
            while (row <= endRow)
            {
                DepthValue* src = row + left;
                DepthValue* end = row + right;
                while (src <= end)
                {
                    if (z <= src->mMin)
                        return true;
                    if (z <= src->mMax)
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
    int* row = mBuffer + rect.mTop * mWidth;
    int* endRow = mBuffer + rect.mBottom * mWidth;
    while (row <= endRow)
    {
        int* src = row + rect.mLeft;
        int* end = row + rect.mRight;
        while (src <= end)
        {
            if (z <= *src)
                return true;
            ++src;
        }
        row += mWidth;
    }
    
    return false;
}

inline Vector4 OcclusionBuffer::modelTransform(const Matrix4& transform, const Vector3& vertex) const
{
    return Vector4(
        transform.m00 * vertex.mX + transform.m01 * vertex.mY + transform.m02 * vertex.mZ + transform.m03,
        transform.m10 * vertex.mX + transform.m11 * vertex.mY + transform.m12 * vertex.mZ + transform.m13,
        transform.m20 * vertex.mX + transform.m21 * vertex.mY + transform.m22 * vertex.mZ + transform.m23,
        transform.m30 * vertex.mX + transform.m31 * vertex.mY + transform.m32 * vertex.mZ + transform.m33
    );
}

inline Vector3 OcclusionBuffer::viewportTransform(const Vector4& vertex) const
{
    float invW = 1.0f / vertex.mW;
    return Vector3(
        invW * vertex.mX * mScaleX + mOffsetX,
        invW * vertex.mY * mScaleY + mOffsetY,
        invW * vertex.mZ * OCCLUSION_Z_SCALE
    );
}

inline Vector4 OcclusionBuffer::clipEdge(const Vector4& v0, const Vector4& v1, float d0, float d1) const
{
    float t = d0 / (d0 - d1);
    return v0 + t * (v1 - v0);
}

inline bool OcclusionBuffer::checkFacing(const Vector3& v0, const Vector3& v1, const Vector3& v2) const
{
    if (mCullMode == CULL_NONE)
        return true;
    
    float aX = v0.mX - v1.mX;
    float aY = v0.mY - v1.mY;
    float bX = v2.mX - v1.mX;
    float bY = v2.mY - v1.mY;
    float signedArea = aX * bY - aY * bX;
    
    if (mCullMode == CULL_CCW)
        return signedArea < 0.0f;
    else
        return signedArea > 0.0f;
}

void OcclusionBuffer::calculateViewport()
{
    // Add half pixel offset due to 3D frustum culling
    mScaleX = 0.5f * mWidth;
    mScaleY = -0.5f * mHeight;
    mOffsetX = 0.5f * mWidth + 0.5f;
    mOffsetY = 0.5f * mHeight + 0.5f;
    mProjOffsetScaleX = mProjection.m00 * mScaleX;
    mProjOffsetScaleY = mProjection.m11 * mScaleY;
}

void OcclusionBuffer::drawTriangle(Vector4* vertices)
{
    unsigned clipMask = 0;
    unsigned andClipMask = 0;
    Vector3 projected[3];
    
    // Build the clip plane mask for the triangle
    for (unsigned i = 0; i < 3; ++i)
    {
        unsigned vertexClipMask = 0;
        
        if (vertices[i].mX > vertices[i].mW)
            vertexClipMask |= CLIPMASK_X_POS;
        if (vertices[i].mX < -vertices[i].mW)
            vertexClipMask |= CLIPMASK_X_NEG;
        if (vertices[i].mY > vertices[i].mW)
            vertexClipMask |= CLIPMASK_Y_POS;
        if (vertices[i].mY < -vertices[i].mW)
            vertexClipMask |= CLIPMASK_Y_NEG;
        if (vertices[i].mZ > vertices[i].mW)
            vertexClipMask |= CLIPMASK_Z_POS;
        if (vertices[i].mZ < 0.0f)
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
        projected[0] = viewportTransform(vertices[0]);
        projected[1] = viewportTransform(vertices[1]);
        projected[2] = viewportTransform(vertices[2]);
        
        if (checkFacing(projected[0], projected[1], projected[2]))
            drawTriangle2D(projected);
    }
    else
    {
        bool triangles[64];
        
        // Initial triangle
        triangles[0] = true;
        unsigned numTriangles = 1;
        
        if (clipMask & CLIPMASK_X_POS)
            clipVertices(Vector4(-1.0f, 0.0f, 0.0f, 1.0f), vertices, triangles, numTriangles);
        if (clipMask & CLIPMASK_X_NEG)
            clipVertices(Vector4(1.0f, 0.0f, 0.0f, 1.0f), vertices, triangles, numTriangles);
        if (clipMask & CLIPMASK_Y_POS)
            clipVertices(Vector4(0.0f, -1.0f, 0.0f, 1.0f), vertices, triangles, numTriangles);
        if (clipMask & CLIPMASK_Y_NEG)
            clipVertices(Vector4(0.0f, 1.0f, 0.0f, 1.0f), vertices, triangles, numTriangles);
        if (clipMask & CLIPMASK_Z_POS)
            clipVertices(Vector4(0.0f, 0.0f, -1.0f, 1.0f), vertices, triangles, numTriangles);
        if (clipMask & CLIPMASK_Z_NEG)
            clipVertices(Vector4(0.0f, 0.0f, 1.0f, 0.0f), vertices, triangles, numTriangles);
        
        // Draw each accepted triangle
        for (unsigned i = 0; i < numTriangles; ++i)
        {
            if (triangles[i])
            {
                unsigned index = i * 3;
                projected[0] = viewportTransform(vertices[index]);
                projected[1] = viewportTransform(vertices[index + 1]);
                projected[2] = viewportTransform(vertices[index + 2]);
                
                if (checkFacing(projected[0], projected[1], projected[2]))
                    drawTriangle2D(projected);
            }
        }
    }
}

void OcclusionBuffer::clipVertices(const Vector4& plane, Vector4* vertices, bool* triangles, unsigned& numTriangles)
{
    unsigned num = numTriangles;
    
    for (unsigned i = 0; i < num; ++i)
    {
        if (triangles[i])
        {
            unsigned index = i * 3;
            float d0 = plane.dotProduct(vertices[index]);
            float d1 = plane.dotProduct(vertices[index + 1]);
            float d2 = plane.dotProduct(vertices[index + 2]);
            
            // If all vertices behind the plane, reject triangle
            if ((d0 < 0.0f) && (d1 < 0.0f) && (d2 < 0.0f))
            {
                triangles[i] = false;
                continue;
            }
            // If 2 vertices behind the plane, create a new triangle in-place
            else if ((d0 < 0.0f) && (d1 < 0.0f))
            {
                vertices[index] = clipEdge(vertices[index], vertices[index + 2], d0, d2);
                vertices[index + 1] = clipEdge(vertices[index + 1], vertices[index + 2], d1, d2);
            }
            else if ((d0 < 0.0f) && (d2 < 0.0f))
            {
                vertices[index] = clipEdge(vertices[index], vertices[index + 1], d0, d1);
                vertices[index + 2] = clipEdge(vertices[index + 2], vertices[index + 1], d2, d1);
            }
            else if ((d1 < 0.0f) && (d2 < 0.0f))
            {
                vertices[index + 1] = clipEdge(vertices[index + 1], vertices[index], d1, d0);
                vertices[index + 2] = clipEdge(vertices[index + 2], vertices[index], d2, d0);
            }
            // 1 vertex behind the plane: create one new triangle, and modify one in-place
            else if (d0 < 0.0f)
            {
                unsigned newIdx = numTriangles * 3;
                triangles[numTriangles] = true;
                ++numTriangles;
                    
                vertices[newIdx] = clipEdge(vertices[index], vertices[index + 1], d0, d1);
                vertices[newIdx + 1] = vertices[index + 1];
                vertices[newIdx + 2] = vertices[index] = clipEdge(vertices[index], vertices[index + 2], d0, d2);
            }
            else if (d1 < 0.0f)
            {
                unsigned newIdx = numTriangles * 3;
                triangles[numTriangles] = true;
                ++numTriangles;
                    
                vertices[newIdx + 1] = clipEdge(vertices[index + 1], vertices[index + 2], d1, d2);
                vertices[newIdx + 2] = vertices[index + 2];
                vertices[newIdx] = vertices[index + 1] = clipEdge(vertices[index + 1], vertices[index], d1, d0);
            }
            else if (d2 < 0.0f)
            {
                unsigned newIdx = numTriangles * 3;
                triangles[numTriangles] = true;
                ++numTriangles;
                    
                vertices[newIdx + 2] = clipEdge(vertices[index + 2], vertices[index], d2, d0);
                vertices[newIdx] = vertices[index];
                vertices[newIdx + 1] = vertices[index + 2] = clipEdge(vertices[index + 2], vertices[index + 1], d2, d1);
            }
        }
    }
}

// Code based on Chris Hecker's Perspective Texture Mapping series in the Game Developer magazine
// Also available online at http://chrishecker.com/Miscellaneous_Technical_Articles

//! Gradients of a software rasterized triangle
struct Gradients
{
    //! Construct from vertices
    Gradients(const Vector3* vertices)
    {
        float invdX = 1.0f / (((vertices[1].mX - vertices[2].mX) *
            (vertices[0].mY - vertices[2].mY)) -
            ((vertices[0].mX - vertices[2].mX) *
            (vertices[1].mY - vertices[2].mY)));
        
        float invdY = -invdX;
        
        mDInvZdX = invdX * (((vertices[1].mZ - vertices[2].mZ) * (vertices[0].mY - vertices[2].mY)) -
            ((vertices[0].mZ - vertices[2].mZ) * (vertices[1].mY - vertices[2].mY)));
        
        mDInvZdY = invdY * (((vertices[1].mZ - vertices[2].mZ) * (vertices[0].mX - vertices[2].mX)) -
            ((vertices[0].mZ - vertices[2].mZ) * (vertices[1].mX - vertices[2].mX)));
        
        mDInvZdXInt = (int)mDInvZdX;
    }
    
    //! Integer horizontal gradient
    int mDInvZdXInt;
    //! Horizontal gradient
    float mDInvZdX;
    //! Vertical gradient
    float mDInvZdY;
};

//! Edge of a software rasterized triangle
struct Edge
{
    //! Construct from gradients and top & bottom vertices
    Edge(const Gradients& gradients, const Vector3& top, const Vector3& bottom, int topY)
    {
        float slope = (bottom.mX - top.mX) / (bottom.mY - top.mY);
        float yPreStep = (float)(topY + 1) - top.mY;
        float xPreStep = slope * yPreStep;
        
        mX = (int)((xPreStep + top.mX) * OCCLUSION_X_SCALE);
        mXStep = (int)(slope * OCCLUSION_X_SCALE);
        mInvZ = (int)(top.mZ + xPreStep * gradients.mDInvZdX + yPreStep * gradients.mDInvZdY);
        mInvZStep = (int)(slope * gradients.mDInvZdX + gradients.mDInvZdY);
    }
    
    //! X coordinate
    int mX;
    //! X coordinate step
    int mXStep;
    //! Inverse Z
    int mInvZ;
    //! Inverse Z step
    int mInvZStep;
};

void OcclusionBuffer::drawTriangle2D(const Vector3* vertices)
{
    int top, middle, bottom;
    bool middleIsRight;
    
    mNumTriangles++;
    
    // Sort vertices in Y-direction
    if (vertices[0].mY < vertices[1].mY)
    {
        if (vertices[2].mY < vertices[0].mY)
        {
            top = 2; middle = 0; bottom = 1;
            middleIsRight = true;
        }
        else
        {
            top = 0;
            if (vertices[1].mY < vertices[2].mY)
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
        if (vertices[2].mY < vertices[1].mY)
        {
            top = 2; middle = 1; bottom = 0;
            middleIsRight = false;
        }
        else
        {
            top = 1;
            if (vertices[0].mY < vertices[2].mY)
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
    
    int topY = (int)vertices[top].mY;
    int middleY = (int)vertices[middle].mY;
    int bottomY = (int)vertices[bottom].mY;
    
    // Check for degenerate triangle
    if (topY == bottomY)
        return;
    
    Gradients gradients(vertices);
    Edge topToMiddle(gradients, vertices[top], vertices[middle], topY);
    Edge topToBottom(gradients, vertices[top], vertices[bottom], topY);
    Edge middleToBottom(gradients, vertices[middle], vertices[bottom], middleY);
    
    // The triangle is clockwise, so if bottom > middle then middle is right
    if (middleIsRight)
    {
        // Top half
        int* row = mBuffer + topY * mWidth;
        int* endRow = mBuffer + middleY * mWidth;
        while (row < endRow)
        {
            int invZ = topToBottom.mInvZ;
            int* dest = row + (topToBottom.mX >> 16);
            int* end = row + (topToMiddle.mX >> 16);
            while (dest < end)
            {
                if (invZ < *dest)
                    *dest = invZ;
                invZ += gradients.mDInvZdXInt;
                ++dest;
            }
            
            topToBottom.mX += topToBottom.mXStep;
            topToBottom.mInvZ += topToBottom.mInvZStep;
            topToMiddle.mX += topToMiddle.mXStep;
            row += mWidth;
        }
        
        // Bottom half
        row = mBuffer + middleY * mWidth;
        endRow = mBuffer + bottomY * mWidth;
        while (row < endRow)
        {
            int invZ = topToBottom.mInvZ;
            int* dest = row + (topToBottom.mX >> 16);
            int* end = row + (middleToBottom.mX >> 16);
            while (dest < end)
            {
                if (invZ < *dest)
                    *dest = invZ;
                invZ += gradients.mDInvZdXInt;
                ++dest;
            }
            
            topToBottom.mX += topToBottom.mXStep;
            topToBottom.mInvZ += topToBottom.mInvZStep;
            middleToBottom.mX += middleToBottom.mXStep;
            row += mWidth;
        }
    }
    else
    {
        // Top half
        int* row = mBuffer + topY * mWidth;
        int* endRow = mBuffer + middleY * mWidth;
        while (row < endRow)
        {
            int invZ = topToMiddle.mInvZ;
            int* dest = row + (topToMiddle.mX >> 16);
            int* end = row + (topToBottom.mX >> 16);
            while (dest < end)
            {
                if (invZ < *dest)
                    *dest = invZ;
                invZ += gradients.mDInvZdXInt;
                ++dest;
            }
            
            topToMiddle.mX += topToMiddle.mXStep;
            topToMiddle.mInvZ += topToMiddle.mInvZStep;
            topToBottom.mX += topToBottom.mXStep;
            row += mWidth;
        }
        
        // Bottom half
        row = mBuffer + middleY * mWidth;
        endRow = mBuffer + bottomY * mWidth;
        while (row < endRow)
        {
            int invZ = middleToBottom.mInvZ;
            int* dest = row + (middleToBottom.mX >> 16);
            int* end = row + (topToBottom.mX >> 16);
            while (dest < end)
            {
                if (invZ < *dest)
                    *dest = invZ;
                invZ += gradients.mDInvZdXInt;
                ++dest;
            }
            
            middleToBottom.mX += middleToBottom.mXStep;
            middleToBottom.mInvZ += middleToBottom.mInvZStep;
            topToBottom.mX += topToBottom.mXStep;
            row += mWidth;
        }
    }
}
