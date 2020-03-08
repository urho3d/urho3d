//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/CoreEvents.h"
#include "../Core/Profiler.h"
#include "../Graphics/AnimatedModel.h"
#include "../Graphics/Camera.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Light.h"
#include "../Graphics/ShaderVariation.h"
#include "../Graphics/VertexBuffer.h"
#include "../Math/Polyhedron.h"
#include "../Resource/ResourceCache.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* SUBSYSTEM_CATEGORY;

// Cap the amount of lines to prevent crash when eg. debug rendering large heightfields
static const unsigned MAX_LINES = 1000000;
// Cap the amount of triangles to prevent crash.
static const unsigned MAX_TRIANGLES = 100000;

DebugRenderer::DebugRenderer(Context* context) :
    Component(context),
    lineAntiAlias_(false)
{
    vertexBuffer_ = new VertexBuffer(context_);

    SubscribeToEvent(E_ENDFRAME, URHO3D_HANDLER(DebugRenderer, HandleEndFrame));
}

DebugRenderer::~DebugRenderer() = default;

void DebugRenderer::RegisterObject(Context* context)
{
    context->RegisterFactory<DebugRenderer>(SUBSYSTEM_CATEGORY);
    URHO3D_ACCESSOR_ATTRIBUTE("Line Antialias", GetLineAntiAlias, SetLineAntiAlias, bool, false, AM_DEFAULT);
}

void DebugRenderer::SetLineAntiAlias(bool enable)
{
    if (enable != lineAntiAlias_)
    {
        lineAntiAlias_ = enable;
        MarkNetworkUpdate();
    }
}

void DebugRenderer::SetView(Camera* camera)
{
    if (!camera)
        return;

    view_ = camera->GetView();
    projection_ = camera->GetProjection();
    gpuProjection_ = camera->GetGPUProjection();
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

void DebugRenderer::AddTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Color& color, bool depthTest)
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

void DebugRenderer::AddPolygon(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, const Color& color, bool depthTest)
{
    AddTriangle(v1, v2, v3, color, depthTest);
    AddTriangle(v3, v4, v1, color, depthTest);
}

void DebugRenderer::AddPolygon(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, unsigned color, bool depthTest)
{
    AddTriangle(v1, v2, v3, color, depthTest);
    AddTriangle(v3, v4, v1, color, depthTest);
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

void DebugRenderer::AddBoundingBox(const BoundingBox& box, const Color& color, bool depthTest, bool solid)
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

    if (!solid)
    {
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
    else
    {
        AddPolygon(min, v1, v2, v3, uintColor, depthTest);
        AddPolygon(v4, v5, max, v6, uintColor, depthTest);
        AddPolygon(min, v4, v6, v3, uintColor, depthTest);
        AddPolygon(v1, v5, max, v2, uintColor, depthTest);
        AddPolygon(v3, v2, max, v6, uintColor, depthTest);
        AddPolygon(min, v1, v5, v4, uintColor, depthTest);
    }
}

void DebugRenderer::AddBoundingBox(const BoundingBox& box, const Matrix3x4& transform, const Color& color, bool depthTest, bool solid)
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

    if (!solid)
    {
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
    else
    {
        AddPolygon(v0, v1, v2, v3, uintColor, depthTest);
        AddPolygon(v4, v5, v7, v6, uintColor, depthTest);
        AddPolygon(v0, v4, v6, v3, uintColor, depthTest);
        AddPolygon(v1, v5, v7, v2, uintColor, depthTest);
        AddPolygon(v3, v2, v7, v6, uintColor, depthTest);
        AddPolygon(v0, v1, v5, v4, uintColor, depthTest);
    }
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

void DebugRenderer::AddSphere(const Sphere& sphere, const Color& color, bool depthTest)
{
    unsigned uintColor = color.ToUInt();

    for (auto j = 0; j < 180; j += 45)
    {
        for (auto i = 0; i < 360; i += 45)
        {
            Vector3 p1 = sphere.GetPoint(i, j);
            Vector3 p2 = sphere.GetPoint(i + 45, j);
            Vector3 p3 = sphere.GetPoint(i, j + 45);
            Vector3 p4 = sphere.GetPoint(i + 45, j + 45);

            AddLine(p1, p2, uintColor, depthTest);
            AddLine(p3, p4, uintColor, depthTest);
            AddLine(p1, p3, uintColor, depthTest);
            AddLine(p2, p4, uintColor, depthTest);
        }
    }
}

void DebugRenderer::AddSphereSector(const Sphere& sphere, const Quaternion& rotation, float angle,
    bool drawLines, const Color& color, bool depthTest)
{
    if (angle <= 0.0f)
        return;
    else if (angle >= 360.0f)
    {
        AddSphere(sphere, color, depthTest);
        return;
    }

    static const unsigned numCircleSegments = 8;
    static const unsigned numLines = 4;
    static const float arcStep = 45.0f;

    const unsigned uintColor = color.ToUInt();
    const float halfAngle = 0.5f * angle;
    const unsigned numArcSegments = static_cast<unsigned>(Ceil(halfAngle / arcStep)) + 1;

    // Draw circle
    for (unsigned j = 0; j < numCircleSegments; ++j)
    {
        AddLine(
            sphere.center_ + rotation * sphere.GetLocalPoint(j * 360.0f / numCircleSegments, halfAngle),
            sphere.center_ + rotation * sphere.GetLocalPoint((j + 1) * 360.0f / numCircleSegments, halfAngle),
            uintColor, depthTest);
    }

    // Draw arcs
    const unsigned step = numCircleSegments / numLines;
    for (unsigned i = 0; i < numArcSegments - 1; ++i)
    {
        for (unsigned j = 0; j < numCircleSegments; j += step)
        {
            const float nextPhi = i + 1 == numArcSegments - 1 ? halfAngle : (i + 1) * arcStep;
            AddLine(
                sphere.center_ + rotation * sphere.GetLocalPoint(j * 360.0f / numCircleSegments, i * arcStep),
                sphere.center_ + rotation * sphere.GetLocalPoint(j * 360.0f / numCircleSegments, nextPhi),
                uintColor, depthTest);
        }
    }

    // Draw lines
    if (drawLines)
    {
        for (unsigned j = 0; j < numCircleSegments; j += step)
        {
            AddLine(sphere.center_,
                sphere.center_ + rotation * sphere.GetLocalPoint(j * 360.0f / numCircleSegments, halfAngle),
                uintColor, depthTest);
        }
    }
}

void DebugRenderer::AddCylinder(const Vector3& position, float radius, float height, const Color& color, bool depthTest)
{
    Sphere sphere(position, radius);
    Vector3 heightVec(0, height, 0);
    Vector3 offsetXVec(radius, 0, 0);
    Vector3 offsetZVec(0, 0, radius);
    for (auto i = 0; i < 360; i += 45)
    {
        Vector3 p1 = sphere.GetPoint(i, 90);
        Vector3 p2 = sphere.GetPoint(i + 45, 90);
        AddLine(p1, p2, color, depthTest);
        AddLine(p1 + heightVec, p2 + heightVec, color, depthTest);
    }
    AddLine(position + offsetXVec, position + heightVec + offsetXVec, color, depthTest);
    AddLine(position - offsetXVec, position + heightVec - offsetXVec, color, depthTest);
    AddLine(position + offsetZVec, position + heightVec + offsetZVec, color, depthTest);
    AddLine(position - offsetZVec, position + heightVec - offsetZVec, color, depthTest);
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

void DebugRenderer::AddTriangleMesh(const void* vertexData, unsigned vertexSize, const void* indexData,
    unsigned indexSize, unsigned indexStart, unsigned indexCount, const Matrix3x4& transform, const Color& color, bool depthTest)
{
    AddTriangleMesh(vertexData, vertexSize, 0, indexData, indexSize, indexStart, indexCount, transform, color, depthTest);
}

void DebugRenderer::AddTriangleMesh(const void* vertexData, unsigned vertexSize, unsigned vertexStart, const void* indexData,
    unsigned indexSize, unsigned indexStart, unsigned indexCount, const Matrix3x4& transform, const Color& color, bool depthTest)
{
    unsigned uintColor = color.ToUInt();
    const auto* srcData = ((const unsigned char*)vertexData) + vertexStart;

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

void DebugRenderer::AddCircle(const Vector3& center, const Vector3& normal, float radius, const Color& color, int steps, bool depthTest)
{
    Quaternion orientation;
    orientation.FromRotationTo(Vector3::UP, normal.Normalized());
    Vector3 p = orientation * Vector3(radius, 0, 0) + center;
    unsigned uintColor = color.ToUInt();

    for(int i = 1; i <= steps; ++i)
    {
        const float angle = (float)i / (float)steps * 360.0f;
        Vector3 v(radius * Cos(angle), 0, radius * Sin(angle));
        Vector3 c = orientation * v + center;
        AddLine(p, c, uintColor, depthTest);
        p = c;
    }

    p = center + normal * (radius / 4.0f);
    AddLine(center, p, uintColor, depthTest);
}

void DebugRenderer::AddCross(const Vector3& center, float size, const Color& color, bool depthTest)
{
    unsigned uintColor = color.ToUInt();

    float halfSize = size / 2.0f;
    for (int i = 0; i < 3; ++i)
    {
        float start[3] = { center.x_, center.y_, center.z_ };
        float end[3] = { center.x_, center.y_, center.z_ };
        start[i] -= halfSize;
        end[i] += halfSize;
        AddLine(Vector3(start), Vector3(end), uintColor, depthTest);
    }
}

void DebugRenderer::AddQuad(const Vector3& center, float width, float height, const Color& color, bool depthTest)
{
    unsigned uintColor = color.ToUInt();

    Vector3 v0(center.x_ - width / 2, center.y_, center.z_ - height / 2);
    Vector3 v1(center.x_ + width / 2, center.y_, center.z_ - height / 2);
    Vector3 v2(center.x_ + width / 2, center.y_, center.z_ + height / 2);
    Vector3 v3(center.x_ - width / 2, center.y_, center.z_ + height / 2);
    AddLine(v0, v1, uintColor, depthTest);
    AddLine(v1, v2, uintColor, depthTest);
    AddLine(v2, v3, uintColor, depthTest);
    AddLine(v3, v0, uintColor, depthTest);
}

void DebugRenderer::Render()
{
    if (!HasContent())
        return;

    auto* graphics = GetSubsystem<Graphics>();
    // Engine does not render when window is closed or device is lost
    assert(graphics && graphics->IsInitialized() && !graphics->IsDeviceLost());

    URHO3D_PROFILE(RenderDebugGeometry);

    ShaderVariation* vs = graphics->GetShader(VS, "Basic", "VERTEXCOLOR");
    ShaderVariation* ps = graphics->GetShader(PS, "Basic", "VERTEXCOLOR");

    unsigned numVertices = (lines_.Size() + noDepthLines_.Size()) * 2 + (triangles_.Size() + noDepthTriangles_.Size()) * 3;
    // Resize the vertex buffer if too small or much too large
    if (vertexBuffer_->GetVertexCount() < numVertices || vertexBuffer_->GetVertexCount() > numVertices * 2)
        vertexBuffer_->SetSize(numVertices, MASK_POSITION | MASK_COLOR, true);

    auto* dest = (float*)vertexBuffer_->Lock(0, numVertices, true);
    if (!dest)
        return;

    for (unsigned i = 0; i < lines_.Size(); ++i)
    {
        const DebugLine& line = lines_[i];

        dest[0] = line.start_.x_;
        dest[1] = line.start_.y_;
        dest[2] = line.start_.z_;
        ((unsigned&)dest[3]) = line.color_;
        dest[4] = line.end_.x_;
        dest[5] = line.end_.y_;
        dest[6] = line.end_.z_;
        ((unsigned&)dest[7]) = line.color_;

        dest += 8;
    }

    for (unsigned i = 0; i < noDepthLines_.Size(); ++i)
    {
        const DebugLine& line = noDepthLines_[i];

        dest[0] = line.start_.x_;
        dest[1] = line.start_.y_;
        dest[2] = line.start_.z_;
        ((unsigned&)dest[3]) = line.color_;
        dest[4] = line.end_.x_;
        dest[5] = line.end_.y_;
        dest[6] = line.end_.z_;
        ((unsigned&)dest[7]) = line.color_;

        dest += 8;
    }

    for (unsigned i = 0; i < triangles_.Size(); ++i)
    {
        const DebugTriangle& triangle = triangles_[i];

        dest[0] = triangle.v1_.x_;
        dest[1] = triangle.v1_.y_;
        dest[2] = triangle.v1_.z_;
        ((unsigned&)dest[3]) = triangle.color_;

        dest[4] = triangle.v2_.x_;
        dest[5] = triangle.v2_.y_;
        dest[6] = triangle.v2_.z_;
        ((unsigned&)dest[7]) = triangle.color_;

        dest[8] = triangle.v3_.x_;
        dest[9] = triangle.v3_.y_;
        dest[10] = triangle.v3_.z_;
        ((unsigned&)dest[11]) = triangle.color_;

        dest += 12;
    }

    for (unsigned i = 0; i < noDepthTriangles_.Size(); ++i)
    {
        const DebugTriangle& triangle = noDepthTriangles_[i];

        dest[0] = triangle.v1_.x_;
        dest[1] = triangle.v1_.y_;
        dest[2] = triangle.v1_.z_;
        ((unsigned&)dest[3]) = triangle.color_;

        dest[4] = triangle.v2_.x_;
        dest[5] = triangle.v2_.y_;
        dest[6] = triangle.v2_.z_;
        ((unsigned&)dest[7]) = triangle.color_;

        dest[8] = triangle.v3_.x_;
        dest[9] = triangle.v3_.y_;
        dest[10] = triangle.v3_.z_;
        ((unsigned&)dest[11]) = triangle.color_;

        dest += 12;
    }

    vertexBuffer_->Unlock();

    graphics->SetBlendMode(lineAntiAlias_ ? BLEND_ALPHA : BLEND_REPLACE);
    graphics->SetColorWrite(true);
    graphics->SetCullMode(CULL_NONE);
    graphics->SetDepthWrite(true);
    graphics->SetLineAntiAlias(lineAntiAlias_);
    graphics->SetScissorTest(false);
    graphics->SetStencilTest(false);
    graphics->SetShaders(vs, ps);
    graphics->SetShaderParameter(VSP_MODEL, Matrix3x4::IDENTITY);
    graphics->SetShaderParameter(VSP_VIEW, view_);
    graphics->SetShaderParameter(VSP_VIEWINV, view_.Inverse());
    graphics->SetShaderParameter(VSP_VIEWPROJ, gpuProjection_ * view_);
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
    graphics->SetDepthWrite(false);

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

    graphics->SetLineAntiAlias(false);
}

bool DebugRenderer::IsInside(const BoundingBox& box) const
{
    return frustum_.IsInsideFast(box) == INSIDE;
}

bool DebugRenderer::HasContent() const
{
    return !(lines_.Empty() && noDepthLines_.Empty() && triangles_.Empty() && noDepthTriangles_.Empty());
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
