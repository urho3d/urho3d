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


#include "../Graphics/AnimatedModel.h"
#include "../Graphics/Camera.h"
#include "../Core/Context.h"
#include "../Core/CoreEvents.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Light.h"
#include "../Math/Polyhedron.h"
#include "../Core/Profiler.h"
#include "../Resource/ResourceCache.h"
#include "../Graphics/ShaderVariation.h"
#include "../Graphics/VertexBuffer.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* SUBSYSTEM_CATEGORY;

// Cap the amount of lines to prevent crash when eg. debug rendering large heightfields
static const unsigned MAX_LINES = 1000000;
// Cap the amount of triangles to prevent crash.
static const unsigned MAX_TRIANGLES = 100000;

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
    context->RegisterFactory<DebugRenderer>(SUBSYSTEM_CATEGORY);
}

void DebugRenderer::SetView(Camera* camera)
{
    if (!camera)
        return;

    view_ = camera->GetView();
    projection_ = camera->GetProjection();
    frustum_ = camera->GetFrustum();
}

void DebugRenderer::AddLine(const Vector3& start, const Vector3& end, const Color& color, bool depthTest)
{
    AddLine(start, end, color.ToUInt(), depthTest);
}

void DebugRenderer::AddLine(const Vector3& start, const Vector3& end, unsigned color, bool depthTest)
{
    if (lines_.Size() + noDepthLines_.Size() >= MAX_LINES)
        return;

    if (depthTest)
        lines_.Push(DebugLine(start, end, color));
    else
        noDepthLines_.Push(DebugLine(start, end, color));
}

void DebugRenderer::AddTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3,  const Color& color, bool depthTest)
{
    AddTriangle(v1, v2, v3, color.ToUInt(), depthTest);
}

void DebugRenderer::AddTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, unsigned color, bool depthTest)
{
    if (triangles_.Size() + noDepthTriangles_.Size() >= MAX_TRIANGLES)
        return;

    if (depthTest)
        triangles_.Push(DebugTriangle(v1, v2, v3, color));
    else
        noDepthTriangles_.Push(DebugTriangle(v1, v2, v3, color));
}

void DebugRenderer::AddNode(Node* node, float scale, bool depthTest)
{
    if (!node)
        return;

    Vector3 start = node->GetWorldPosition();
    Quaternion rotation = node->GetWorldRotation();

    AddLine(start, start + rotation * (scale * Vector3::RIGHT), Color::RED.ToUInt(), depthTest);
    AddLine(start, start + rotation * (scale * Vector3::UP), Color::GREEN.ToUInt(), depthTest);
    AddLine(start, start + rotation * (scale * Vector3::FORWARD), Color::BLUE.ToUInt(), depthTest);
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

    AddLine(min, v1, uintColor, depthTest);
    AddLine(v1, v2, uintColor, depthTest);
    AddLine(v2, v3, uintColor, depthTest);
    AddLine(v3, min, uintColor, depthTest);
    AddLine(v4, v5, uintColor, depthTest);
    AddLine(v5, max, uintColor, depthTest);
    AddLine(max, v6, uintColor, depthTest);
    AddLine(v6, v4, uintColor, depthTest);
    AddLine(min, v4, uintColor, depthTest);
    AddLine(v1, v5, uintColor, depthTest);
    AddLine(v2, max, uintColor, depthTest);
    AddLine(v3, v6, uintColor, depthTest);
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

    AddLine(v0, v1, uintColor, depthTest);
    AddLine(v1, v2, uintColor, depthTest);
    AddLine(v2, v3, uintColor, depthTest);
    AddLine(v3, v0, uintColor, depthTest);
    AddLine(v4, v5, uintColor, depthTest);
    AddLine(v5, v7, uintColor, depthTest);
    AddLine(v7, v6, uintColor, depthTest);
    AddLine(v6, v4, uintColor, depthTest);
    AddLine(v0, v4, uintColor, depthTest);
    AddLine(v1, v5, uintColor, depthTest);
    AddLine(v2, v7, uintColor, depthTest);
    AddLine(v3, v6, uintColor, depthTest);
}


void DebugRenderer::AddFrustum(const Frustum& frustum, const Color& color, bool depthTest)
{
    const Vector3* vertices = frustum.vertices_;
    unsigned uintColor = color.ToUInt();

    AddLine(vertices[0], vertices[1], uintColor, depthTest);
    AddLine(vertices[1], vertices[2], uintColor, depthTest);
    AddLine(vertices[2], vertices[3], uintColor, depthTest);
    AddLine(vertices[3], vertices[0], uintColor, depthTest);
    AddLine(vertices[4], vertices[5], uintColor, depthTest);
    AddLine(vertices[5], vertices[6], uintColor, depthTest);
    AddLine(vertices[6], vertices[7], uintColor, depthTest);
    AddLine(vertices[7], vertices[4], uintColor, depthTest);
    AddLine(vertices[0], vertices[4], uintColor, depthTest);
    AddLine(vertices[1], vertices[5], uintColor, depthTest);
    AddLine(vertices[2], vertices[6], uintColor, depthTest);
    AddLine(vertices[3], vertices[7], uintColor, depthTest);
}

void DebugRenderer::AddPolyhedron(const Polyhedron& poly, const Color& color, bool depthTest)
{
    unsigned uintColor = color.ToUInt();

    for (unsigned i = 0; i < poly.faces_.Size(); ++i)
    {
        const PODVector<Vector3>& face = poly.faces_[i];
        if (face.Size() >= 3)
        {
            for (unsigned j = 0; j < face.Size(); ++j)
                AddLine(face[j], face[(j + 1) % face.Size()], uintColor, depthTest);
        }
    }
}

static Vector3 PointOnSphere(const Sphere& sphere, unsigned theta, unsigned phi)
{
    return Vector3(
        sphere.center_.x_ + sphere.radius_ * Sin((float)theta) * Sin((float)phi),
        sphere.center_.y_ + sphere.radius_ * Cos((float)phi),
        sphere.center_.z_ + sphere.radius_ * Cos((float)theta) * Sin((float)phi)
    );
}

void DebugRenderer::AddSphere(const Sphere& sphere, const Color& color, bool depthTest)
{
    unsigned uintColor = color.ToUInt();
    
    for (unsigned j = 0; j < 180; j += 45)
    {
        for (unsigned i = 0; i < 360; i += 45)
        {
            Vector3 p1 = PointOnSphere(sphere, i, j);
            Vector3 p2 = PointOnSphere(sphere, i + 45, j);
            Vector3 p3 = PointOnSphere(sphere, i, j + 45);
            Vector3 p4 = PointOnSphere(sphere, i + 45, j + 45);
            
            AddLine(p1, p2, uintColor, depthTest);
            AddLine(p3, p4, uintColor, depthTest);
            AddLine(p1, p3, uintColor, depthTest);
            AddLine(p2, p4, uintColor, depthTest);
        }
    }
}

void DebugRenderer::AddSkeleton(const Skeleton& skeleton, const Color& color, bool depthTest)
{
    const Vector<Bone>& bones = skeleton.GetBones();
    if (!bones.Size())
        return;

    unsigned uintColor = color.ToUInt();

    for (unsigned i = 0; i < bones.Size(); ++i)
    {
        // Skip if bone contains no skinned geometry
        if (bones[i].radius_ < M_EPSILON && bones[i].boundingBox_.Size().LengthSquared() < M_EPSILON)
            continue;

        Node* boneNode = bones[i].node_;
        if (!boneNode)
            continue;

        Vector3 start = boneNode->GetWorldPosition();
        Vector3 end;

        unsigned j = bones[i].parentIndex_;
        Node* parentNode = boneNode->GetParent();

        // If bone has a parent defined, and it also skins geometry, draw a line to it. Else draw the bone as a point
        if (parentNode && (bones[j].radius_ >= M_EPSILON || bones[j].boundingBox_.Size().LengthSquared() >= M_EPSILON))
            end = parentNode->GetWorldPosition();
        else
            end = start;

        AddLine(start, end, uintColor, depthTest);
    }
}

void DebugRenderer::AddTriangleMesh(const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize,
    unsigned indexStart, unsigned indexCount, const Matrix3x4& transform, const Color& color, bool depthTest)
{
    unsigned uintColor = color.ToUInt();
    const unsigned char* srcData = (const unsigned char*)vertexData;

    // 16-bit indices
    if (indexSize == sizeof(unsigned short))
    {
        const unsigned short* indices = ((const unsigned short*)indexData) + indexStart;
        const unsigned short* indicesEnd = indices + indexCount;

        while (indices < indicesEnd)
        {
            Vector3 v0 = transform * *((const Vector3*)(&srcData[indices[0] * vertexSize]));
            Vector3 v1 = transform * *((const Vector3*)(&srcData[indices[1] * vertexSize]));
            Vector3 v2 = transform * *((const Vector3*)(&srcData[indices[2] * vertexSize]));

            AddLine(v0, v1, uintColor, depthTest);
            AddLine(v1, v2, uintColor, depthTest);
            AddLine(v2, v0, uintColor, depthTest);

            indices += 3;
        }
    }
    else
    {
        const unsigned* indices = ((const unsigned*)indexData) + indexStart;
        const unsigned* indicesEnd = indices + indexCount;

        while (indices < indicesEnd)
        {
            Vector3 v0 = transform * *((const Vector3*)(&srcData[indices[0] * vertexSize]));
            Vector3 v1 = transform * *((const Vector3*)(&srcData[indices[1] * vertexSize]));
            Vector3 v2 = transform * *((const Vector3*)(&srcData[indices[2] * vertexSize]));

            AddLine(v0, v1, uintColor, depthTest);
            AddLine(v1, v2, uintColor, depthTest);
            AddLine(v2, v0, uintColor, depthTest);

            indices += 3;
        }
    }
}

void DebugRenderer::Render()
{
    if (lines_.Empty() && noDepthLines_.Empty() && triangles_.Empty() && noDepthTriangles_.Empty())
        return;

    Graphics* graphics = GetSubsystem<Graphics>();
    // Engine does not render when window is closed or device is lost
    assert(graphics && graphics->IsInitialized() && !graphics->IsDeviceLost());

    PROFILE(RenderDebugGeometry);

    ShaderVariation* vs = graphics->GetShader(VS, "Basic", "VERTEXCOLOR");
    ShaderVariation* ps = graphics->GetShader(PS, "Basic", "VERTEXCOLOR");
    
    unsigned numVertices = (lines_.Size() + noDepthLines_.Size()) * 2 + (triangles_.Size() + noDepthTriangles_.Size()) * 3;
    // Resize the vertex buffer if too small or much too large
    if (vertexBuffer_->GetVertexCount() < numVertices || vertexBuffer_->GetVertexCount() > numVertices * 2)
        vertexBuffer_->SetSize(numVertices, MASK_POSITION | MASK_COLOR, true);

    float* dest = (float*)vertexBuffer_->Lock(0, numVertices, true);
    if (!dest)
        return;

    for (unsigned i = 0; i < lines_.Size(); ++i)
    {
        const DebugLine& line = lines_[i];

        dest[0] = line.start_.x_; dest[1] = line.start_.y_; dest[2] = line.start_.z_;
        ((unsigned&)dest[3]) = line.color_;
        dest[4] = line.end_.x_; dest[5] = line.end_.y_; dest[6] = line.end_.z_;
        ((unsigned&)dest[7]) = line.color_;

        dest += 8;
    }

    for (unsigned i = 0; i < noDepthLines_.Size(); ++i)
    {
        const DebugLine& line = noDepthLines_[i];

        dest[0] = line.start_.x_; dest[1] = line.start_.y_; dest[2] = line.start_.z_;
        ((unsigned&)dest[3]) = line.color_;
        dest[4] = line.end_.x_; dest[5] = line.end_.y_; dest[6] = line.end_.z_;
        ((unsigned&)dest[7]) = line.color_;

        dest += 8;
    }

    for (unsigned i = 0; i < triangles_.Size(); ++i)
    {
        const DebugTriangle& triangle = triangles_[i];

        dest[0] = triangle.v1_.x_; dest[1] = triangle.v1_.y_; dest[2] = triangle.v1_.z_;
        ((unsigned&)dest[3]) = triangle.color_;

        dest[4] = triangle.v2_.x_; dest[5] = triangle.v2_.y_; dest[6] = triangle.v2_.z_;
        ((unsigned&)dest[7]) = triangle.color_;
        
        dest[8] = triangle.v3_.x_; dest[9] = triangle.v3_.y_; dest[10] = triangle.v3_.z_;
        ((unsigned&)dest[11]) = triangle.color_;

        dest += 12;
    }

    for (unsigned i = 0; i < noDepthTriangles_.Size(); ++i)
    {
        const DebugTriangle& triangle = noDepthTriangles_[i];

        dest[0] = triangle.v1_.x_; dest[1] = triangle.v1_.y_; dest[2] = triangle.v1_.z_;
        ((unsigned&)dest[3]) = triangle.color_;

        dest[4] = triangle.v2_.x_; dest[5] = triangle.v2_.y_; dest[6] = triangle.v2_.z_;
        ((unsigned&)dest[7]) = triangle.color_;

        dest[8] = triangle.v3_.x_; dest[9] = triangle.v3_.y_; dest[10] = triangle.v3_.z_;
        ((unsigned&)dest[11]) = triangle.color_;

        dest += 12;
    }

    vertexBuffer_->Unlock();

    graphics->SetBlendMode(BLEND_REPLACE);
    graphics->SetColorWrite(true);
    graphics->SetCullMode(CULL_NONE);
    graphics->SetDepthWrite(true);
    graphics->SetDrawAntialiased(true);
    graphics->SetScissorTest(false);
    graphics->SetStencilTest(false);
    graphics->SetShaders(vs, ps);
    graphics->SetShaderParameter(VSP_MODEL, Matrix3x4::IDENTITY);
    graphics->SetShaderParameter(VSP_VIEWPROJ, projection_ * view_);
    graphics->SetShaderParameter(PSP_MATDIFFCOLOR, Color(1.0f, 1.0f, 1.0f, 1.0f));
    graphics->SetVertexBuffer(vertexBuffer_);

    unsigned start = 0;
    unsigned count = 0;
    if (lines_.Size())
    {
        count = lines_.Size() * 2;
        graphics->SetDepthTest(CMP_LESSEQUAL);
        graphics->Draw(LINE_LIST, start, count);
        start += count;
    }
    if (noDepthLines_.Size())
    {
        count = noDepthLines_.Size() * 2;
        graphics->SetDepthTest(CMP_ALWAYS);
        graphics->Draw(LINE_LIST, start, count);
        start += count;
    }
    
    graphics->SetBlendMode(BLEND_ALPHA);
    
    if (triangles_.Size())
    {
        count = triangles_.Size() * 3;
        graphics->SetDepthTest(CMP_LESSEQUAL);
        graphics->Draw(TRIANGLE_LIST, start, count);
        start += count;
    }
    if (noDepthTriangles_.Size())
    {
        count = noDepthTriangles_.Size() * 3;
        graphics->SetDepthTest(CMP_ALWAYS);
        graphics->Draw(TRIANGLE_LIST, start, count);
    }
}

bool DebugRenderer::IsInside(const BoundingBox& box) const
{
    return frustum_.IsInsideFast(box) == INSIDE;
}

void DebugRenderer::HandleEndFrame(StringHash eventType, VariantMap& eventData)
{
    // When the amount of debug geometry is reduced, release memory
    unsigned linesSize = lines_.Size();
    unsigned noDepthLinesSize = noDepthLines_.Size();
    unsigned trianglesSize = triangles_.Size();
    unsigned noDepthTrianglesSize = noDepthTriangles_.Size();

    lines_.Clear();
    noDepthLines_.Clear();
    triangles_.Clear();
    noDepthTriangles_.Clear();

    if (lines_.Capacity() > linesSize * 2)
        lines_.Reserve(linesSize);
    if (noDepthLines_.Capacity() > noDepthLinesSize * 2)
        noDepthLines_.Reserve(noDepthLinesSize);
    if (triangles_.Capacity() > trianglesSize * 2)
        triangles_.Reserve(trianglesSize);
    if (noDepthTriangles_.Capacity() > noDepthTrianglesSize * 2)
        noDepthTriangles_.Reserve(noDepthTrianglesSize);
}

}
