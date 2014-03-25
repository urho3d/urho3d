//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "Context.h"
#include "Drawable2D.h"
#include "DrawableProxy2D.h"
#include "Geometry.h"
#include "Log.h"
#include "Material.h"
#include "Node.h"
#include "VertexBuffer.h"
#include "Sort.h"

#include "DebugNew.h"

namespace Urho3D
{

DrawableProxy2D::DrawableProxy2D(Context* context) :
    Drawable(context, DRAWABLE_GEOMETRY),
    vertexBuffer_(new VertexBuffer(context_)),
    orderDirty_(true)
{
}

DrawableProxy2D::~DrawableProxy2D()
{
}

void DrawableProxy2D::RegisterObject(Context* context)
{
    context->RegisterFactory<DrawableProxy2D>();
}

void DrawableProxy2D::UpdateBatches(const FrameInfo& frame)
{
    unsigned count = materials_.Size();
    batches_.Resize(count);

    for (unsigned i = 0; i < count; ++i)
    {
        batches_[i].distance_ = 10.0f + (count - i) * 0.001f;
        batches_[i].material_ = materials_[i];
        batches_[i].geometry_ = geometries_[i];
        batches_[i].worldTransform_ = &Matrix3x4::IDENTITY;
    }
}

void DrawableProxy2D::UpdateGeometry(const FrameInfo& frame)
{
    materials_.Clear();

    if (orderDirty_)
    {
        Sort(drawables_.Begin(), drawables_.End(), CompareDrawable2Ds);
        orderDirty_ = false;
    }

    float timeStep = frame.timeStep_;

    unsigned vertexCount = 0;
    for (unsigned i = 0; i < drawables_.Size(); ++i)
        vertexCount += drawables_[i]->GetVertices().Size();

    if (vertexCount == 0)
        return;

    vertexCount = vertexCount / 4 * 6;

    vertexBuffer_->SetSize(vertexCount, MASK_VERTEX2D);
    Vertex2D* dest = reinterpret_cast<Vertex2D*>(vertexBuffer_->Lock(0, vertexCount, true));
    if (dest)
    {
        unsigned start = 0;
        unsigned count = 0;
        Material* material = 0;

        for (unsigned d = 0; d < drawables_.Size(); ++d)
        {
            Material* currMaterial = drawables_[d]->GetUsedMaterial();
            const Vector<Vertex2D>& vertices = drawables_[d]->GetVertices();
            if (!currMaterial || vertices.Empty())
                continue;

            if (material != currMaterial)
            {
                if (material)
                {
                    AddBatch(material, start, count);
                    start += count;
                    count = 0;
                }

                material = currMaterial;
            }

            for (unsigned i = 0; i < vertices.Size(); i += 4)
            {
                dest[0] = vertices[i + 0];
                dest[1] = vertices[i + 1];
                dest[2] = vertices[i + 2];

                dest[3] = vertices[i + 0];
                dest[4] = vertices[i + 2];
                dest[5] = vertices[i + 3];
                dest += 6;
            }

            count += vertices.Size() / 4 * 6;
        }

        if (material)
            AddBatch(material, start, count);

        vertexBuffer_->Unlock();
    }
    else
        LOGERROR("Failed to lock vertex buffer");
}

UpdateGeometryType DrawableProxy2D::GetUpdateGeometryType()
{
    return UPDATE_WORKER_THREAD;
}

void DrawableProxy2D::AddDrawable(Drawable2D* drawable)
{
    if (!drawable)
        return;

    if (drawables_.Contains(drawable))
        return;

    drawables_.Push(drawable);
    orderDirty_ = true;
}

void DrawableProxy2D::RemoveDrawable(Drawable2D* drawable)
{
    if (!drawable)
        return;

    drawables_.Remove(drawable);
    orderDirty_ = true;
}

void DrawableProxy2D::OnWorldBoundingBoxUpdate()
{
    boundingBox_.Clear();

    for (unsigned i = 0; i < drawables_.Size(); ++i)
        boundingBox_.Merge(drawables_[i]->GetWorldBoundingBox());

    worldBoundingBox_ = boundingBox_;
}

void DrawableProxy2D::AddBatch(Material* material, unsigned vertexStart, unsigned vertexCount)
{
    if (!material)
        return;

    materials_.Push(SharedPtr<Material>(material));

    unsigned batchSize = materials_.Size();
    if (geometries_.Size() < batchSize)
    {
        SharedPtr<Geometry> geometry(new Geometry(context_));
        geometry->SetVertexBuffer(0, vertexBuffer_, MASK_VERTEX2D);
        geometries_.Push(geometry);
    }

    geometries_[batchSize - 1]->SetDrawRange(TRIANGLE_LIST, 0, 0, vertexStart, vertexCount);
}

}
