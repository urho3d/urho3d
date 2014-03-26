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
#include "GraphicsEvents.h"
#include "IndexBuffer.h"
#include "Log.h"
#include "Material.h"
#include "Node.h"
#include "Profiler.h"
#include "Scene.h"
#include "VertexBuffer.h"
#include "Sort.h"

#include "DebugNew.h"

namespace Urho3D
{

DrawableProxy2D::DrawableProxy2D(Context* context) :
    Drawable(context, DRAWABLE_GEOMETRY),
    indexBuffer_(new IndexBuffer(context_)),
    vertexBuffer_(new VertexBuffer(context_)),
    orderDirty_(true),
    indexCount_(0),
    vertexCount_(0)
{
    SubscribeToEvent(E_BEGINVIEWUPDATE, HANDLER(DrawableProxy2D, HandleBeginViewUpdate));
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
    unsigned count = batches_.Size();

    // Update non-thread critical parts of the source batches
    for (unsigned i = 0; i < count; ++i)
    {
        batches_[i].distance_ = 10.0f + (count - i) * 0.001f;
        batches_[i].worldTransform_ = &Matrix3x4::IDENTITY;
    }
}

void DrawableProxy2D::UpdateGeometry(const FrameInfo& frame)
{
    // Fill index buffer
    if (indexBuffer_->GetIndexCount() < indexCount_)
    {
        bool largeIndices = vertexCount_ > 0xffff;
        indexBuffer_->SetSize(indexCount_, largeIndices, true);
        void* buffer = indexBuffer_->Lock(0, indexCount_, true);
        if (buffer)
        {
            unsigned quadCount = indexCount_ / 6;
            if (largeIndices)
            {
                unsigned* dest = reinterpret_cast<unsigned*>(buffer);
                for (unsigned i = 0; i < quadCount; ++i)
                {
                    unsigned base = i * 4;
                    dest[0] = base;
                    dest[1] = base + 1;
                    dest[2] = base + 2;
                    dest[3] = base;
                    dest[4] = base + 2;
                    dest[5] = base + 3;
                    dest += 6;
                }
            }
            else
            {
                unsigned short* dest = reinterpret_cast<unsigned short*>(buffer);
                for (unsigned i = 0; i < quadCount; ++i)
                {
                    unsigned base = i * 4;
                    dest[0] = (unsigned short)(base);
                    dest[1] = (unsigned short)(base + 1);
                    dest[2] = (unsigned short)(base + 2);
                    dest[3] = (unsigned short)(base);
                    dest[4] = (unsigned short)(base + 2);
                    dest[5] = (unsigned short)(base + 3);
                    dest += 6;
                }
            }

            indexBuffer_->Unlock();
        }
        else
        {
            LOGERROR("Failed to lock index buffer");
            return;
        }
    }

    if (vertexBuffer_->GetVertexCount() < vertexCount_)
        vertexBuffer_->SetSize(vertexCount_, MASK_VERTEX2D);

    if (vertexCount_)
    {
        Vertex2D* dest = reinterpret_cast<Vertex2D*>(vertexBuffer_->Lock(0, vertexCount_, true));
        if (dest)
        {
            Material* material = 0;
            unsigned iStart = 0;
            unsigned iCount = 0;
            unsigned vStart = 0;
            unsigned vCount = 0;

            for (unsigned d = 0; d < drawables_.Size(); ++d)
            {
                if (!drawablesVisible_[d])
                    continue;

                const Vector<Vertex2D>& vertices = drawables_[d]->GetVertices();
                for (unsigned i = 0; i < vertices.Size(); ++i)
                    dest[i] = vertices[i];
                dest += vertices.Size();
            }

            vertexBuffer_->Unlock();
        }
        else
            LOGERROR("Failed to lock vertex buffer");
    }
}

UpdateGeometryType DrawableProxy2D::GetUpdateGeometryType()
{
    return UPDATE_MAIN_THREAD;
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
    // Set a large dummy bounding box to ensure the proxy is rendered
    boundingBox_.Define(-M_LARGE_VALUE, M_LARGE_VALUE);
    worldBoundingBox_ = boundingBox_;
}

void DrawableProxy2D::HandleBeginViewUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace BeginViewUpdate;

    // Check that we are updating the correct scene
    if (GetScene() != eventData[P_SCENE].GetPtr())
        return;

    PROFILE(UpdateDrawableProxy2D);

    if (orderDirty_)
    {
        Sort(drawables_.Begin(), drawables_.End(), CompareDrawable2Ds);
        orderDirty_ = false;
    }

    vertexCount_ = 0;

    if (drawablesVisible_.Size() != drawables_.Size())
        drawablesVisible_.Resize(drawables_.Size());

    /// \todo We could add frustum culling, but that would be problematic if we have several viewports. Right now all Drawable2D's
    /// are always submitted for rendering
    for (unsigned i = 0; i < drawables_.Size(); ++i)
    {
        Material* usedMaterial = drawables_[i]->GetUsedMaterial();
        const Vector<Vertex2D>& vertices = drawables_[i]->GetVertices();
        if (drawables_[i]->GetUsedMaterial() && vertices.Size())
        {
            drawablesVisible_[i] = true;
            vertexCount_ += vertices.Size();
        }
        else
            drawablesVisible_[i] = false;
    }

    indexCount_ = vertexCount_ / 4 * 6;

    // Go through the drawables to form geometries & batches, but upload the actual vertex data later
    materials_.Clear();

    Material* material = 0;
    unsigned iStart = 0;
    unsigned iCount = 0;
    unsigned vStart = 0;
    unsigned vCount = 0;

    for (unsigned d = 0; d < drawables_.Size(); ++d)
    {
        if (!drawablesVisible_[d])
            continue;

        Material* usedMaterial = drawables_[d]->GetUsedMaterial();
        const Vector<Vertex2D>& vertices = drawables_[d]->GetVertices();

        if (material != usedMaterial)
        {
            if (material)
            {
                AddBatch(material, iStart, iCount, vStart, vCount);
                iStart += iCount;
                iCount = 0;
                vStart += vCount;
                vCount = 0;
            }

            material = usedMaterial;
        }

        iCount += vertices.Size() / 4 * 6;
        vCount += vertices.Size();
    }

    if (material)
        AddBatch(material, iStart, iCount, vStart, vCount);

    // Now the amount of batches is known. Build the part of source batches that are sensitive to threading issues
    // (material & geometry pointers)
    unsigned count = materials_.Size();
    batches_.Resize(count);

    for (unsigned i = 0; i < count; ++i)
    {
        batches_[i].material_ = materials_[i];
        batches_[i].geometry_ = geometries_[i];
    }
}

void DrawableProxy2D::AddBatch(Material* material, unsigned indexStart, unsigned indexCount, unsigned vertexStart, unsigned vertexCount)
{
    if (!material || indexCount == 0 || vertexCount == 0)
        return;

    materials_.Push(SharedPtr<Material>(material));

    unsigned batchSize = materials_.Size();
    if (geometries_.Size() < batchSize)
    {
        SharedPtr<Geometry> geometry(new Geometry(context_));
        geometry->SetIndexBuffer(indexBuffer_);
        geometry->SetVertexBuffer(0, vertexBuffer_, MASK_VERTEX2D);
        geometries_.Push(geometry);
    }

    geometries_[batchSize - 1]->SetDrawRange(TRIANGLE_LIST, indexStart, indexCount, vertexStart, vertexCount, false);
}

}
