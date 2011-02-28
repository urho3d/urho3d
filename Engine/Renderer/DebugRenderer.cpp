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
#include "AnimatedModel.h"
#include "DebugRenderer.h"
#include "Light.h"
#include "PixelShader.h"
#include "Pipeline.h"
#include "Profiler.h"
#include "Renderer.h"
#include "RendererEvents.h"
#include "ResourceCache.h"
#include "VertexShader.h"

#include "DebugNew.h"

DebugRenderer::DebugRenderer()
{
    subscribeToEvent(EVENT_ENDFRAME, EVENT_HANDLER(DebugRenderer, handleEndFrame));
}

void DebugRenderer::render(Pipeline* pipeline, Camera* camera)
{
    if ((!camera) || ((!mLines.size()) && (!mNoDepthLines.size())))
        return;
    
    PROFILE(DebugGeometry_Render);
    
    Renderer* renderer = pipeline->getRenderer();
    
    renderer->setAlphaTest(false);
    renderer->setBlendMode(BLEND_REPLACE);
    renderer->setColorWrite(true);
    renderer->setCullMode(CULL_NONE);
    renderer->setDepthWrite(true);
    renderer->setDepthTest(CMP_LESSEQUAL);
    renderer->setFillMode(FILL_SOLID);
    renderer->setScissorTest(false);
    renderer->setStencilTest(false);
    renderer->setVertexShader(pipeline->getVertexShader("Basic_VCol"));
    renderer->setPixelShader(pipeline->getPixelShader("Basic_VCol"));
    renderer->setVertexShaderConstant(getVSRegister(VSP_MODELVIEWPROJ), camera->getProjection() * camera->getInverseWorldTransform());
    renderer->setPixelShaderConstant(getPSRegister(PSP_MATDIFFCOLOR), Color(1.0f, 1.0f, 1.0f, 1.0f));
    
    // Draw all line geometry with depth testing
    if (mLines.size())
    {
        renderer->beginImmediate(LINE_LIST, mLines.size() * 2, MASK_POSITION | MASK_COLOR);
        float* dest = (float*)renderer->getImmediateDataPtr();
        
        for (unsigned i = 0; i < mLines.size(); ++i)
        {
            const DebugLine& line = mLines[i];
            
            *dest++ = line.mStart.mX; *dest++ = line.mStart.mY; *dest++ = line.mStart.mZ;
            *((unsigned*)dest) = line.mColor; dest++;
            
            *dest++ = line.mEnd.mX; *dest++ = line.mEnd.mY; *dest++ = line.mEnd.mZ;
            *((unsigned*)dest) = line.mColor; dest++;
        }
        
        renderer->endImmediate();
    }
    
    // Draw all line geometry without depth testing
    renderer->setDepthTest(CMP_ALWAYS);
    if (mNoDepthLines.size())
    {
        renderer->beginImmediate(LINE_LIST, mNoDepthLines.size() * 2, MASK_POSITION | MASK_COLOR);
        float* dest = (float*)renderer->getImmediateDataPtr();
        
        for (unsigned i = 0; i < mNoDepthLines.size(); ++i)
        {
            const DebugLine& line = mNoDepthLines[i];
            
            *dest++ = line.mStart.mX; *dest++ = line.mStart.mY; *dest++ = line.mStart.mZ;
            *((unsigned*)dest) = line.mColor; dest++;
            
            *dest++ = line.mEnd.mX; *dest++ = line.mEnd.mY; *dest++ = line.mEnd.mZ;
            *((unsigned*)dest) = line.mColor; dest++;
        }
        
        renderer->endImmediate();
    }
}

void DebugRenderer::addLine(const Vector3& start, const Vector3& end, const Color& color, bool depthTest)
{
    if (depthTest)
        mLines.push_back(DebugLine(start, end, getD3DColor(color)));
    else
        mNoDepthLines.push_back(DebugLine(start, end, getD3DColor(color)));
}

void DebugRenderer::addBoundingBox(const BoundingBox& box, const Color& color, bool depthTest)
{
    const Vector3& min = box.mMin;
    const Vector3& max = box.mMax;
    
    Vector3 v0(max.mX, min.mY, min.mZ);
    Vector3 v1(max.mX, max.mY, min.mZ);
    Vector3 v2(min.mX, max.mY, min.mZ);
    Vector3 v3(min.mX, min.mY, max.mZ);
    Vector3 v4(max.mX, min.mY, max.mZ);
    Vector3 v5(min.mX, max.mY, max.mZ);
    
    unsigned d3dColor = getD3DColor(color);
    
    std::vector<DebugLine>* dest = &mLines;
    if (!depthTest)
        dest = &mNoDepthLines;
    
    dest->push_back(DebugLine(min, v0, d3dColor));
    dest->push_back(DebugLine(v0, v1, d3dColor));
    dest->push_back(DebugLine(v1, v2, d3dColor));
    dest->push_back(DebugLine(v2, min, d3dColor));
    dest->push_back(DebugLine(v3, v4, d3dColor));
    dest->push_back(DebugLine(v4, max, d3dColor));
    dest->push_back(DebugLine(max, v5, d3dColor));
    dest->push_back(DebugLine(v5, v3, d3dColor));
    dest->push_back(DebugLine(min, v3, d3dColor));
    dest->push_back(DebugLine(v0, v4, d3dColor));
    dest->push_back(DebugLine(v1, max, d3dColor));
    dest->push_back(DebugLine(v2, v5, d3dColor));
}

void DebugRenderer::addBoundingBox(const BoundingBox& box, const Matrix4x3& transform, const Color& color, bool depthTest)
{
    const Vector3& min = box.mMin;
    const Vector3& max = box.mMax;
    
    Vector3 v0(transform * Vector3(min.mX, min.mY, min.mZ));
    Vector3 v1(transform * Vector3(max.mX, min.mY, min.mZ));
    Vector3 v2(transform * Vector3(max.mX, max.mY, min.mZ));
    Vector3 v3(transform * Vector3(min.mX, max.mY, min.mZ));
    Vector3 v4(transform * Vector3(min.mX, min.mY, max.mZ));
    Vector3 v5(transform * Vector3(max.mX, min.mY, max.mZ));
    Vector3 v6(transform * Vector3(max.mX, max.mY, max.mZ));
    Vector3 v7(transform * Vector3(min.mX, max.mY, max.mZ));
    
    unsigned d3dColor = getD3DColor(color);
    
    std::vector<DebugLine>* dest = &mLines;
    if (!depthTest)
        dest = &mNoDepthLines;
    
    dest->push_back(DebugLine(v0, v1, d3dColor));
    dest->push_back(DebugLine(v1, v2, d3dColor));
    dest->push_back(DebugLine(v2, v3, d3dColor));
    dest->push_back(DebugLine(v3, v0, d3dColor));
    dest->push_back(DebugLine(v4, v5, d3dColor));
    dest->push_back(DebugLine(v5, v6, d3dColor));
    dest->push_back(DebugLine(v6, v7, d3dColor));
    dest->push_back(DebugLine(v7, v4, d3dColor));
    dest->push_back(DebugLine(v0, v4, d3dColor));
    dest->push_back(DebugLine(v1, v5, d3dColor));
    dest->push_back(DebugLine(v2, v6, d3dColor));
    dest->push_back(DebugLine(v3, v7, d3dColor));
}

void DebugRenderer::addFrustum(const Frustum& frustum, const Color& color, bool depthTest)
{
    const Vector3* vertices = frustum.getVertices();
    unsigned d3dColor = getD3DColor(color);
    
    std::vector<DebugLine>* dest = &mLines;
    if (!depthTest)
        dest = &mNoDepthLines;
    
    dest->push_back(DebugLine(vertices[0], vertices[1], d3dColor));
    dest->push_back(DebugLine(vertices[1], vertices[2], d3dColor));
    dest->push_back(DebugLine(vertices[2], vertices[3], d3dColor));
    dest->push_back(DebugLine(vertices[3], vertices[0], d3dColor));
    dest->push_back(DebugLine(vertices[4], vertices[5], d3dColor));
    dest->push_back(DebugLine(vertices[5], vertices[6], d3dColor));
    dest->push_back(DebugLine(vertices[6], vertices[7], d3dColor));
    dest->push_back(DebugLine(vertices[7], vertices[4], d3dColor));
    dest->push_back(DebugLine(vertices[0], vertices[4], d3dColor));
    dest->push_back(DebugLine(vertices[1], vertices[5], d3dColor));
    dest->push_back(DebugLine(vertices[2], vertices[6], d3dColor));
    dest->push_back(DebugLine(vertices[3], vertices[7], d3dColor));
}

void DebugRenderer::addSkeleton(const Skeleton& skeleton, const Color& color, bool depthTest)
{
    const std::vector<SharedPtr<Bone> >& bones = skeleton.getBones();
    if (!bones.size())
        return;
    
    DebugLine newLine;
    newLine.mColor = getD3DColor(color);
    
    std::vector<DebugLine>* dest = &mLines;
    if (!depthTest)
        dest = &mNoDepthLines;
    
    for (unsigned i = 0; i < bones.size(); ++i)
    {
        Bone* bone = bones[i];
        Node* parent = bone->getParent();
        if ((parent->getNodeFlags() & NODE_BONE) == 0)
            parent = 0;
            
        newLine.mStart = bone->getWorldPosition();
        // If bone has a parent defined, draw a line to it. Else draw the bone as a point
        if (parent)
            newLine.mEnd = parent->getWorldPosition();
        else
            newLine.mEnd = newLine.mStart;
        
        dest->push_back(newLine);
    }
}

void DebugRenderer::handleEndFrame(StringHash eventType, VariantMap& eventData)
{
    mLines.clear();
    mNoDepthLines.clear();
}
