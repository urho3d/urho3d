//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Polyhedron.h"
#include "Profiler.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "ShaderVariation.h"
#include "VertexBuffer.h"

#include "DebugNew.h"

OBJECTTYPESTATIC(DebugRenderer);

DebugRenderer::DebugRenderer(Context* context) :
    Component(context)
{
    vertexBuffer_ = new VertexBuffer(context_);
    
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
    projection_ = camera->GetProjection();
    frustum_ = camera->GetFrustum();
}

void DebugRenderer::AddLine(const Vector3& start, const Vector3& end, const Color& color, bool depthTest)
{
    if (depthTest)
        lines_.Push(DebugLine(start, end, color.ToUInt()));
    else
        noDepthLines_.Push(DebugLine(start, end, color.ToUInt()));
}

void DebugRenderer::AddLine(const Vector3& start, const Vector3& end, unsigned color, bool depthTest)
{
    if (depthTest)
        lines_.Push(DebugLine(start, end, color));
    else
        noDepthLines_.Push(DebugLine(start, end, color));
}

void DebugRenderer::AddNode(Node* node, float scale, bool depthTest)
{
    if (!node)
        return;
    
    Vector3 start = node->GetWorldPosition();
    Quaternion rotation = node->GetWorldRotation();
    
    if (depthTest)
    {
        lines_.Push(DebugLine(start, start + rotation * (scale * Vector3::RIGHT), Color::RED.ToUInt()));
        lines_.Push(DebugLine(start, start + rotation * (scale * Vector3::UP), Color::GREEN.ToUInt()));
        lines_.Push(DebugLine(start, start + rotation * (scale * Vector3::FORWARD), Color::BLUE.ToUInt()));
    }
    else
    {
        noDepthLines_.Push(DebugLine(start, start + rotation * (scale * Vector3::RIGHT), Color::RED.ToUInt()));
        noDepthLines_.Push(DebugLine(start, start + rotation * (scale * Vector3::UP), Color::GREEN.ToUInt()));
        noDepthLines_.Push(DebugLine(start, start + rotation * (scale * Vector3::FORWARD), Color::BLUE.ToUInt()));
    }
}

void DebugRenderer::AddBoundingBox(const BoundingBox& box, const Color& color, bool depthTest)
{
    const Vector3& min = box.min_;
    const Vector3& max = box.max_;
    
    Vector3 v1(max.x_, min.y_, min.z_);
    Vector3 v2(max.x_, max.y_, min.z_);
    Vector3 v3(min.x_, max.y_, min.z_);
    Vector3 v4(min.x_, min.y_, max.z_);
    Vector3 v5(max.x_, min.y_, max.z_);
    Vector3 v6(min.x_, max.y_, max.z_);
    
    unsigned uintColor = color.ToUInt();
    
    PODVector<DebugLine>* dest = &lines_;
    if (!depthTest)
        dest = &noDepthLines_;
    
    dest->Push(DebugLine(min, v1, uintColor));
    dest->Push(DebugLine(v1, v2, uintColor));
    dest->Push(DebugLine(v2, v3, uintColor));
    dest->Push(DebugLine(v3, min, uintColor));
    dest->Push(DebugLine(v4, v5, uintColor));
    dest->Push(DebugLine(v5, max, uintColor));
    dest->Push(DebugLine(max, v6, uintColor));
    dest->Push(DebugLine(v6, v4, uintColor));
    dest->Push(DebugLine(min, v4, uintColor));
    dest->Push(DebugLine(v1, v5, uintColor));
    dest->Push(DebugLine(v2, max, uintColor));
    dest->Push(DebugLine(v3, v6, uintColor));
}

void DebugRenderer::AddBoundingBox(const BoundingBox& box, const Matrix3x4& transform, const Color& color, bool depthTest)
{
    const Vector3& min = box.min_;
    const Vector3& max = box.max_;
    
    Vector3 v0(transform * min);
    Vector3 v1(transform * Vector3(max.x_, min.y_, min.z_));
    Vector3 v2(transform * Vector3(max.x_, max.y_, min.z_));
    Vector3 v3(transform * Vector3(min.x_, max.y_, min.z_));
    Vector3 v4(transform * Vector3(min.x_, min.y_, max.z_));
    Vector3 v5(transform * Vector3(max.x_, min.y_, max.z_));
    Vector3 v6(transform * Vector3(min.x_, max.y_, max.z_));
    Vector3 v7(transform * max);
    
    unsigned uintColor = color.ToUInt();
    
    PODVector<DebugLine>* dest = &lines_;
    if (!depthTest)
        dest = &noDepthLines_;
    
    dest->Push(DebugLine(v0, v1, uintColor));
    dest->Push(DebugLine(v1, v2, uintColor));
    dest->Push(DebugLine(v2, v3, uintColor));
    dest->Push(DebugLine(v3, v0, uintColor));
    dest->Push(DebugLine(v4, v5, uintColor));
    dest->Push(DebugLine(v5, v7, uintColor));
    dest->Push(DebugLine(v7, v6, uintColor));
    dest->Push(DebugLine(v6, v4, uintColor));
    dest->Push(DebugLine(v0, v4, uintColor));
    dest->Push(DebugLine(v1, v5, uintColor));
    dest->Push(DebugLine(v2, v7, uintColor));
    dest->Push(DebugLine(v3, v6, uintColor));
}


void DebugRenderer::AddFrustum(const Frustum& frustum, const Color& color, bool depthTest)
{
    const Vector3* vertices = frustum.vertices_;
    unsigned uintColor = color.ToUInt();
    
    PODVector<DebugLine>* dest = &lines_;
    if (!depthTest)
        dest = &noDepthLines_;
    
    dest->Push(DebugLine(vertices[0], vertices[1], uintColor));
    dest->Push(DebugLine(vertices[1], vertices[2], uintColor));
    dest->Push(DebugLine(vertices[2], vertices[3], uintColor));
    dest->Push(DebugLine(vertices[3], vertices[0], uintColor));
    dest->Push(DebugLine(vertices[4], vertices[5], uintColor));
    dest->Push(DebugLine(vertices[5], vertices[6], uintColor));
    dest->Push(DebugLine(vertices[6], vertices[7], uintColor));
    dest->Push(DebugLine(vertices[7], vertices[4], uintColor));
    dest->Push(DebugLine(vertices[0], vertices[4], uintColor));
    dest->Push(DebugLine(vertices[1], vertices[5], uintColor));
    dest->Push(DebugLine(vertices[2], vertices[6], uintColor));
    dest->Push(DebugLine(vertices[3], vertices[7], uintColor));
}

void DebugRenderer::AddPolyhedron(const Polyhedron& poly, const Color& color, bool depthTest)
{
    unsigned uintColor = color.ToUInt();
    
    PODVector<DebugLine>* dest = &lines_;
    if (!depthTest)
        dest = &noDepthLines_;
    
    for (unsigned i = 0; i < poly.faces_.Size(); ++i)
    {
        const PODVector<Vector3>& face = poly.faces_[i];
        if (face.Size() >= 3)
        {
            for (unsigned j = 0; j < face.Size(); ++j)
                dest->Push(DebugLine(face[j], face[(j + 1) % face.Size()], uintColor));
        }
    }
}

void DebugRenderer::AddSphere(const Sphere& sphere, const Color& color, bool depthTest)
{
    const Vector3& center = sphere.center_;
    float radius = sphere.radius_;
    unsigned uintColor = color.ToUInt();
    
    for (unsigned i = 0; i < 360; i += 45)
    {
        unsigned j = i + 45;
        float a = radius * sinf(i * M_DEGTORAD);
        float b = radius * cosf(i * M_DEGTORAD);
        float c = radius * sinf(j * M_DEGTORAD);
        float d = radius * cosf(j * M_DEGTORAD);
        Vector3 start, end;
        
        start = center + Vector3(a, b, 0.0f);
        end = center + Vector3(c, d, 0.0f);
        AddLine(start, end, uintColor, depthTest);
        start = center + Vector3(a, 0.0f, b);
        end = center + Vector3(c, 0.0f, d);
        AddLine(start, end, uintColor, depthTest);
        start = center + Vector3(0.0f, a, b);
        end = center + Vector3(0.0f, c, d);
        AddLine(start, end, uintColor, depthTest);
    }
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
        // Skip if bone contains no skinned geometry
        if (bones[i].radius_ < M_EPSILON && bones[i].boundingBox_.Size().LengthSquared() < M_EPSILON)
            continue;
        
        Node* boneNode = bones[i].node_;
        if (!boneNode)
            continue;
        
        newLine.start_ = boneNode->GetWorldPosition();
        
        unsigned j = bones[i].parentIndex_;
        Node* parentNode = boneNode->GetParent();
        
        // If bone has a parent defined, and it also skins geometry, draw a line to it. Else draw the bone as a point
        if (parentNode && (bones[j].radius_ >= M_EPSILON || bones[j].boundingBox_.Size().LengthSquared() >= M_EPSILON))
            newLine.end_ = parentNode->GetWorldPosition();
        else
            newLine.end_ = newLine.start_;
        
        dest->Push(newLine);
    }
}

void DebugRenderer::AddTriangleMesh(const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize,
    unsigned indexStart, unsigned indexCount, const Matrix3x4& transform, const Color& color, bool depthTest)
{
    unsigned uintColor = color.ToUInt();
    
    PODVector<DebugLine>* dest = &lines_;
    if (!depthTest)
        dest = &noDepthLines_;
    
    const unsigned char* vertexDataChar = (const unsigned char*)vertexData;
    unsigned oldSize = dest->Size();
    dest->Resize(oldSize + indexCount);
    DebugLine* destLines = &dest->At(oldSize);
    
    // 16-bit indices
    if (indexSize == sizeof(unsigned short))
    {
        const unsigned short* indices = ((const unsigned short*)indexData) + indexStart;
        const unsigned short* indicesEnd = indices + indexCount;
        
        while (indices < indicesEnd)
        {
            const Vector3& v0 = *((const Vector3*)(&vertexDataChar[indices[0] * vertexSize]));
            const Vector3& v1 = *((const Vector3*)(&vertexDataChar[indices[1] * vertexSize]));
            const Vector3& v2 = *((const Vector3*)(&vertexDataChar[indices[2] * vertexSize]));
            
            destLines[0].start_ = transform * v0;
            destLines[0].end_ = transform * v1;
            destLines[0].color_ = uintColor;
            
            destLines[1].start_ = destLines[0].end_;
            destLines[1].end_ = transform * v2;
            destLines[1].color_ = uintColor;
            
            destLines[2].start_ = destLines[1].end_;
            destLines[2].end_ = destLines[0].start_;
            destLines[2].color_ = uintColor;
            
            indices += 3;
            destLines += 3;
        }
    }
    else
    {
        const unsigned* indices = ((const unsigned*)indexData) + indexStart;
        const unsigned* indicesEnd = indices + indexCount;
        
        while (indices < indicesEnd)
        {
            const Vector3& v0 = *((const Vector3*)(&vertexDataChar[indices[0] * vertexSize]));
            const Vector3& v1 = *((const Vector3*)(&vertexDataChar[indices[1] * vertexSize]));
            const Vector3& v2 = *((const Vector3*)(&vertexDataChar[indices[2] * vertexSize]));
            
            destLines[0].start_ = transform * v0;
            destLines[0].end_ = transform * v1;
            destLines[0].color_ = uintColor;
            
            destLines[1].start_ = destLines[0].end_;
            destLines[1].end_ = transform * v2;
            destLines[1].color_ = uintColor;
            
            destLines[2].start_ = destLines[1].end_;
            destLines[2].end_ = destLines[0].start_;
            destLines[2].color_ = uintColor;
            
            indices += 3;
            destLines += 3;
        }
    }
}

void DebugRenderer::Render()
{
    if (lines_.Empty() && noDepthLines_.Empty())
        return;
    
    Graphics* graphics = GetSubsystem<Graphics>();
    Renderer* renderer = GetSubsystem<Renderer>();
    
    if (!graphics || graphics->IsDeviceLost())
        return;
    
    PROFILE(RenderDebugGeometry);
    
    unsigned numVertices = (lines_.Size() + noDepthLines_.Size()) * 2;
    // Resize the vertex buffer if too small or much too large
    if (vertexBuffer_->GetVertexCount() < numVertices || vertexBuffer_->GetVertexCount() > numVertices * 2)
        vertexBuffer_->SetSize(numVertices, MASK_POSITION | MASK_COLOR, true);
    
    void* scratch = graphics->ReserveScratchBuffer(numVertices * vertexBuffer_->GetVertexSize());
    float* dest = (float*)scratch;
    
    for (unsigned i = 0; i < lines_.Size(); ++i)
    {
        const DebugLine& line = lines_[i];
            
        *dest++ = line.start_.x_; *dest++ = line.start_.y_; *dest++ = line.start_.z_;
        *((unsigned*)dest) = line.color_; dest++;
            
        *dest++ = line.end_.x_; *dest++ = line.end_.y_; *dest++ = line.end_.z_;
        *((unsigned*)dest) = line.color_; dest++;
    }
    
    for (unsigned i = 0; i < noDepthLines_.Size(); ++i)
    {
        const DebugLine& line = noDepthLines_[i];
            
        *dest++ = line.start_.x_; *dest++ = line.start_.y_; *dest++ = line.start_.z_;
        *((unsigned*)dest) = line.color_; dest++;
            
        *dest++ = line.end_.x_; *dest++ = line.end_.y_; *dest++ = line.end_.z_;
        *((unsigned*)dest) = line.color_; dest++;
    }
    
    vertexBuffer_->SetDataRange(scratch, 0, numVertices, true);
    graphics->FreeScratchBuffer(scratch);
    
    graphics->SetBlendMode(BLEND_REPLACE);
    graphics->SetColorWrite(true);
    graphics->SetCullMode(CULL_NONE);
    graphics->SetDepthWrite(true);
    graphics->SetScissorTest(false);
    graphics->SetStencilTest(false);
    graphics->SetShaders(renderer->GetVertexShader("Basic_VCol"), renderer->GetPixelShader("Basic_VCol"));
    graphics->SetShaderParameter(VSP_MODEL, Matrix3x4::IDENTITY);
    graphics->SetShaderParameter(VSP_VIEWPROJ, projection_ * view_);
    graphics->SetShaderParameter(PSP_MATDIFFCOLOR, Color(1.0f, 1.0f, 1.0f, 1.0f));
    graphics->SetVertexBuffer(vertexBuffer_);
    
    if (lines_.Size())
    {
        graphics->SetDepthTest(CMP_LESSEQUAL);
        graphics->Draw(LINE_LIST, 0, lines_.Size() * 2);
    }
    if (noDepthLines_.Size())
    {
        graphics->SetDepthTest(CMP_ALWAYS);
        graphics->Draw(LINE_LIST, lines_.Size() * 2, noDepthLines_.Size() * 2);
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
