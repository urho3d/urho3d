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
#include "Camera.h"
#include "Context.h"
#include "CoreEvents.h"
#include "DebugRenderer.h"
#include "Graphics.h"
#include "Light.h"
#include "Profiler.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "ShaderVariation.h"

#include "DebugNew.h"

OBJECTTYPESTATIC(DebugRenderer);

DebugRenderer::DebugRenderer(Context* context) :
    Component(context)
{
    SubscribeToEvent(E_ENDFRAME, HANDLER(DebugRenderer, HandleEndFrame));
}

DebugRenderer::~DebugRenderer()
{
}

void DebugRenderer::RegisterObject(Context* context)
{
    context->RegisterFactory<DebugRenderer>();
}

void DebugRenderer::SetView(Camera* camera)
{
    if (!camera)
        return;
    
    view_ = camera->GetInverseWorldTransform();
    projection_ = camera->GetProjection(false);
    frustum_ = camera->GetFrustum();
}

void DebugRenderer::AddLine(const Vector3& start, const Vector3& end, const Color& color, bool depthTest)
{
    if (depthTest)
        lines_.Push(DebugLine(start, end, color.ToUInt()));
    else
        noDepthLines_.Push(DebugLine(start, end, color.ToUInt()));
}

void DebugRenderer::AddBoundingBox(const BoundingBox& box, const Color& color, bool depthTest)
{
    const Vector3& min = box.min_;
    const Vector3& max = box.max_;
    
    Vector3 v0(max.x_, min.y_, min.z_);
    Vector3 v1(max.x_, max.y_, min.z_);
    Vector3 v2(min.x_, max.y_, min.z_);
    Vector3 v3(min.x_, min.y_, max.z_);
    Vector3 v4(max.x_, min.y_, max.z_);
    Vector3 v5(min.x_, max.y_, max.z_);
    
    unsigned d3dColor = color.ToUInt();
    
    PODVector<DebugLine>* dest = &lines_;
    if (!depthTest)
        dest = &noDepthLines_;
    
    dest->Push(DebugLine(min, v0, d3dColor));
    dest->Push(DebugLine(v0, v1, d3dColor));
    dest->Push(DebugLine(v1, v2, d3dColor));
    dest->Push(DebugLine(v2, min, d3dColor));
    dest->Push(DebugLine(v3, v4, d3dColor));
    dest->Push(DebugLine(v4, max, d3dColor));
    dest->Push(DebugLine(max, v5, d3dColor));
    dest->Push(DebugLine(v5, v3, d3dColor));
    dest->Push(DebugLine(min, v3, d3dColor));
    dest->Push(DebugLine(v0, v4, d3dColor));
    dest->Push(DebugLine(v1, max, d3dColor));
    dest->Push(DebugLine(v2, v5, d3dColor));
}

void DebugRenderer::AddBoundingBox(const BoundingBox& box, const Matrix3x4& transform, const Color& color, bool depthTest)
{
    const Vector3& min = box.min_;
    const Vector3& max = box.max_;
    
    Vector3 v0(transform * Vector3(min.x_, min.y_, min.z_));
    Vector3 v1(transform * Vector3(max.x_, min.y_, min.z_));
    Vector3 v2(transform * Vector3(max.x_, max.y_, min.z_));
    Vector3 v3(transform * Vector3(min.x_, max.y_, min.z_));
    Vector3 v4(transform * Vector3(min.x_, min.y_, max.z_));
    Vector3 v5(transform * Vector3(max.x_, min.y_, max.z_));
    Vector3 v6(transform * Vector3(max.x_, max.y_, max.z_));
    Vector3 v7(transform * Vector3(min.x_, max.y_, max.z_));
    
    unsigned d3dColor = color.ToUInt();
    
    PODVector<DebugLine>* dest = &lines_;
    if (!depthTest)
        dest = &noDepthLines_;
    
    dest->Push(DebugLine(v0, v1, d3dColor));
    dest->Push(DebugLine(v1, v2, d3dColor));
    dest->Push(DebugLine(v2, v3, d3dColor));
    dest->Push(DebugLine(v3, v0, d3dColor));
    dest->Push(DebugLine(v4, v5, d3dColor));
    dest->Push(DebugLine(v5, v6, d3dColor));
    dest->Push(DebugLine(v6, v7, d3dColor));
    dest->Push(DebugLine(v7, v4, d3dColor));
    dest->Push(DebugLine(v0, v4, d3dColor));
    dest->Push(DebugLine(v1, v5, d3dColor));
    dest->Push(DebugLine(v2, v6, d3dColor));
    dest->Push(DebugLine(v3, v7, d3dColor));
}

void DebugRenderer::AddFrustum(const Frustum& frustum, const Color& color, bool depthTest)
{
    const Vector3* vertices = frustum.vertices_;
    unsigned d3dColor = color.ToUInt();
    
    PODVector<DebugLine>* dest = &lines_;
    if (!depthTest)
        dest = &noDepthLines_;
    
    dest->Push(DebugLine(vertices[0], vertices[1], d3dColor));
    dest->Push(DebugLine(vertices[1], vertices[2], d3dColor));
    dest->Push(DebugLine(vertices[2], vertices[3], d3dColor));
    dest->Push(DebugLine(vertices[3], vertices[0], d3dColor));
    dest->Push(DebugLine(vertices[4], vertices[5], d3dColor));
    dest->Push(DebugLine(vertices[5], vertices[6], d3dColor));
    dest->Push(DebugLine(vertices[6], vertices[7], d3dColor));
    dest->Push(DebugLine(vertices[7], vertices[4], d3dColor));
    dest->Push(DebugLine(vertices[0], vertices[4], d3dColor));
    dest->Push(DebugLine(vertices[1], vertices[5], d3dColor));
    dest->Push(DebugLine(vertices[2], vertices[6], d3dColor));
    dest->Push(DebugLine(vertices[3], vertices[7], d3dColor));
}

void DebugRenderer::AddSkeleton(const Skeleton& skeleton, const Color& color, bool depthTest)
{
    const Vector<Bone>& bones = skeleton.GetBones();
    if (!bones.Size())
        return;
    
    DebugLine newLine;
    newLine.color_ = color.ToUInt();
    
    PODVector<DebugLine>* dest = &lines_;
    if (!depthTest)
        dest = &noDepthLines_;
    
    for (unsigned i = 0; i < bones.Size(); ++i)
    {
        Node* boneNode = bones[i].node_;
        if (!boneNode)
            continue;
        Node* parentNode = boneNode->GetParent();
        
        newLine.start_ = boneNode->GetWorldPosition();
        // If bone has a parent defined, draw a line to it. Else draw the bone as a point
        if (parentNode)
            newLine.end_ = parentNode->GetWorldPosition();
        else
            newLine.end_ = newLine.start_;
        
        dest->Push(newLine);
    }
}


void DebugRenderer::Render()
{
    PROFILE(RenderDebugGeometry);
    
    if (lines_.Empty() && noDepthLines_.Empty())
        return;
    
    Graphics* graphics = GetSubsystem<Graphics>();
    Renderer* renderer = GetSubsystem<Renderer>();
    
    graphics->SetAlphaTest(false);
    graphics->SetBlendMode(BLEND_REPLACE);
    graphics->SetColorWrite(true);
    graphics->SetCullMode(CULL_NONE);
    graphics->SetDepthWrite(true);
    graphics->SetDepthTest(CMP_LESSEQUAL);
    graphics->SetFillMode(FILL_SOLID);
    graphics->SetScissorTest(false);
    graphics->SetStencilTest(false);
    graphics->SetShaders(renderer->GetVertexShader("Basic_VCol"), renderer->GetPixelShader("Basic_VCol"));
    graphics->SetShaderParameter(VSP_MODEL, Matrix3x4::IDENTITY);
    graphics->SetShaderParameter(VSP_VIEWPROJ, projection_ * view_);
    graphics->SetShaderParameter(PSP_MATDIFFCOLOR, Color(1.0f, 1.0f, 1.0f, 1.0f));
    
    // Draw all line geometry with depth testing
    if (lines_.Size())
    {
        graphics->BeginImmediate(LINE_LIST, lines_.Size() * 2, MASK_POSITION | MASK_COLOR);
        float* dest = (float*)graphics->GetImmediateDataPtr();
        
        for (unsigned i = 0; i < lines_.Size(); ++i)
        {
            const DebugLine& line = lines_[i];
            
            *dest++ = line.start_.x_; *dest++ = line.start_.y_; *dest++ = line.start_.z_;
            *((unsigned*)dest) = line.color_; dest++;
            
            *dest++ = line.end_.x_; *dest++ = line.end_.y_; *dest++ = line.end_.z_;
            *((unsigned*)dest) = line.color_; dest++;
        }
        
        graphics->EndImmediate();
    }
    
    // Draw all line geometry without depth testing
    graphics->SetDepthTest(CMP_ALWAYS);
    if (noDepthLines_.Size())
    {
        graphics->BeginImmediate(LINE_LIST, noDepthLines_.Size() * 2, MASK_POSITION | MASK_COLOR);
        float* dest = (float*)graphics->GetImmediateDataPtr();
        
        for (unsigned i = 0; i < noDepthLines_.Size(); ++i)
        {
            const DebugLine& line = noDepthLines_[i];
            
            *dest++ = line.start_.x_; *dest++ = line.start_.y_; *dest++ = line.start_.z_;
            *((unsigned*)dest) = line.color_; dest++;
            
            *dest++ = line.end_.x_; *dest++ = line.end_.y_; *dest++ = line.end_.z_;
            *((unsigned*)dest) = line.color_; dest++;
        }
        
        graphics->EndImmediate();
    }
}

bool DebugRenderer::IsInside(const BoundingBox& box) const
{
    return frustum_.IsInsideFast(box) == INSIDE;
}

void DebugRenderer::HandleEndFrame(StringHash eventType, VariantMap& eventData)
{
    lines_.Clear();
    noDepthLines_.Clear();
}
