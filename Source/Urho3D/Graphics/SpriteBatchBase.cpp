// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#include "SpriteBatchBase.h"

#include "Graphics.h"
#include "Camera.h"

namespace Urho3D
{

void SpriteBatchBase::AddTriangle()
{
    // Рендерили четырёхугольники, а теперь нужно рендерить треугольники
    if (qNumVertices_ > 0)
        Flush();

    memcpy(tVertices_ + tNumVertices_, &triangle_, sizeof(triangle_));
    tNumVertices_ += VERTICES_PER_TRIANGLE;

    // Если после добавления вершин мы заполнили массив до предела, то рендерим порцию
    if (tNumVertices_ == MAX_TRIANGLES_IN_PORTION * VERTICES_PER_TRIANGLE)
        Flush();
}

void SpriteBatchBase::SetShapeColor(u32 color)
{
    triangle_.v0_.color_ = color;
    triangle_.v1_.color_ = color;
    triangle_.v2_.color_ = color;
}

void SpriteBatchBase::SetShapeColor(const Color& color)
{
    SetShapeColor(color.ToU32());
}

void SpriteBatchBase::AddQuad()
{
    // Рендерили треугольники, а теперь нужно рендерить четырехугольники
    if (tNumVertices_ > 0)
        Flush();

    if (quad_.texture_ != qCurrentTexture_ || quad_.vs_ != qCurrentVS_ || quad_.ps_ != qCurrentPS_)
    {
        Flush();

        qCurrentVS_ = quad_.vs_;
        qCurrentPS_ = quad_.ps_;
        qCurrentTexture_ = quad_.texture_;
    }

    memcpy(qVertices_ + qNumVertices_, &(quad_.v0_), sizeof(QVertex) * VERTICES_PER_QUAD);
    qNumVertices_ += VERTICES_PER_QUAD;

    // Если после добавления вершин мы заполнили массив до предела, то рендерим порцию
    if (qNumVertices_ == MAX_QUADS_IN_PORTION * VERTICES_PER_QUAD)
        Flush();
}

IntRect SpriteBatchBase::GetViewportRect()
{
    if (!VirtualScreenUsed())
        return IntRect(0, 0, graphics_->GetWidth(), graphics_->GetHeight());

    float realAspect = (float)graphics_->GetWidth() / graphics_->GetHeight();
    float virtualAspect = (float)virtualScreenSize_.x_ / virtualScreenSize_.y_;

    float virtualScreenScale;
    if (realAspect > virtualAspect)
    {
        // Окно шире, чем надо. Будут пустые полосы по бокам
        virtualScreenScale = (float)graphics_->GetHeight() / virtualScreenSize_.y_;
    }
    else
    {
        // Высота окна больше, чем надо. Будут пустые полосы сверху и снизу
        virtualScreenScale = (float)graphics_->GetWidth() / virtualScreenSize_.x_;
    }

    i32 viewportWidth = (i32)(virtualScreenSize_.x_ * virtualScreenScale);
    i32 viewportHeight = (i32)(virtualScreenSize_.y_ * virtualScreenScale);

    // Центрируем вьюпорт
    i32 viewportX = (graphics_->GetWidth() - viewportWidth) / 2;
    i32 viewportY = (graphics_->GetHeight() - viewportHeight) / 2;

    return IntRect(viewportX, viewportY, viewportWidth + viewportX, viewportHeight + viewportY);
}

Vector2 SpriteBatchBase::GetVirtualPos(const Vector2& realPos)
{
    if (!VirtualScreenUsed())
        return realPos;

    IntRect viewportRect = GetViewportRect();
    float factor = (float)virtualScreenSize_.x_ / viewportRect.Width();

    float virtualX = (realPos.x_ - viewportRect.left_) * factor;
    float virtualY = (realPos.y_ - viewportRect.top_) * factor;

    return Vector2(virtualX, virtualY);
}

void SpriteBatchBase::UpdateViewProjMatrix()
{
    if (camera_)
    {
        Matrix4 matrix = camera_->GetGPUProjection() * camera_->GetView();
        graphics_->SetShaderParameter(VSP_VIEWPROJ, matrix);
        return;
    }

    i32 width;
    i32 height;

    if (VirtualScreenUsed())
    {
        width = virtualScreenSize_.x_;
        height = virtualScreenSize_.y_;
    }
    else
    {
        width = graphics_->GetWidth();
        height = graphics_->GetHeight();
    }

    float pixelWidth = 2.0f / width; // Двойка, так как длина отрезка [-1, 1] равна двум
    float pixelHeight = 2.0f / height;

    Matrix4 matrix = Matrix4(pixelWidth,  0.0f,         0.0f, -1.0f,
                             0.0f,       -pixelHeight,  0.0f,  1.0f,
                             0.0f,        0.0f,         1.0f,  0.0f,
                             0.0f,        0.0f,         0.0f,  1.0f);

    graphics_->SetShaderParameter(VSP_VIEWPROJ, matrix);
}

using GpuIndex16 = u16;

SpriteBatchBase::SpriteBatchBase(Context* context) : Object(context)
{
    graphics_ = GetSubsystem<Graphics>();

    qIndexBuffer_ = new IndexBuffer(context_);
    qIndexBuffer_->SetShadowed(true);

    // Индексный буфер всегда содержит набор четырёхугольников, поэтому его можно сразу заполнить
    qIndexBuffer_->SetSize(MAX_QUADS_IN_PORTION * INDICES_PER_QUAD, false);
    GpuIndex16* buffer = (GpuIndex16*)qIndexBuffer_->Lock(0, qIndexBuffer_->GetIndexCount());
    for (i32 i = 0; i < MAX_QUADS_IN_PORTION; i++)
    {
        // Первый треугольник четырёхугольника
        buffer[i * INDICES_PER_QUAD + 0] = i * VERTICES_PER_QUAD + 0;
        buffer[i * INDICES_PER_QUAD + 1] = i * VERTICES_PER_QUAD + 1;
        buffer[i * INDICES_PER_QUAD + 2] = i * VERTICES_PER_QUAD + 2;

        // Второй треугольник
        buffer[i * INDICES_PER_QUAD + 3] = i * VERTICES_PER_QUAD + 2;
        buffer[i * INDICES_PER_QUAD + 4] = i * VERTICES_PER_QUAD + 3;
        buffer[i * INDICES_PER_QUAD + 5] = i * VERTICES_PER_QUAD + 0;
    }
    qIndexBuffer_->Unlock();

    qVertexBuffer_ = new VertexBuffer(context_);
    qVertexBuffer_->SetSize(MAX_QUADS_IN_PORTION * VERTICES_PER_QUAD, VertexElements::Position | VertexElements::Color | VertexElements::TexCoord1, true);

    tVertexBuffer_ = new VertexBuffer(context_);
    tVertexBuffer_->SetSize(MAX_TRIANGLES_IN_PORTION * VERTICES_PER_TRIANGLE, VertexElements::Position | VertexElements::Color, true);
    tVertexShader_ = graphics_->GetShader(VS, "TriangleBatch");
    tPixelShader_ = graphics_->GetShader(PS, "TriangleBatch");
    SetShapeColor(Color::WHITE);
}

void SpriteBatchBase::Flush()
{
    if (tNumVertices_ > 0)
    {
        graphics_->ResetRenderTargets();
        graphics_->ClearParameterSources();
        graphics_->SetCullMode(CULL_NONE);
        graphics_->SetDepthWrite(false);
        graphics_->SetStencilTest(false);
        graphics_->SetScissorTest(false);
        graphics_->SetColorWrite(true);
        graphics_->SetDepthTest(compareMode_);
        graphics_->SetBlendMode(blendMode_);
        graphics_->SetViewport(GetViewportRect());

        graphics_->SetIndexBuffer(nullptr);
        graphics_->SetVertexBuffer(tVertexBuffer_);
        graphics_->SetTexture(0, nullptr);

        // Параметры шейдеров нужно задавать после указания шейдеров
        graphics_->SetShaders(tVertexShader_, tPixelShader_);
        graphics_->SetShaderParameter(VSP_MODEL, Matrix3x4::IDENTITY);
        UpdateViewProjMatrix();

        // Копируем накопленную геометрию в память видеокарты
        TVertex* buffer = (TVertex*)tVertexBuffer_->Lock(0, tNumVertices_, true);
        memcpy(buffer, tVertices_, tNumVertices_ * sizeof(TVertex));
        tVertexBuffer_->Unlock();

        // И отрисовываем её
        graphics_->Draw(TRIANGLE_LIST, 0, tNumVertices_);

        // Начинаем новую порцию
        tNumVertices_ = 0;
    }

    else if (qNumVertices_ > 0)
    {
        graphics_->ResetRenderTargets();
        graphics_->ClearParameterSources();
        graphics_->SetCullMode(CULL_NONE);
        graphics_->SetDepthWrite(false);
        graphics_->SetStencilTest(false);
        graphics_->SetScissorTest(false);
        graphics_->SetColorWrite(true);
        graphics_->SetDepthTest(compareMode_);
        graphics_->SetBlendMode(blendMode_);
        graphics_->SetViewport(GetViewportRect());

        graphics_->SetIndexBuffer(qIndexBuffer_);
        graphics_->SetVertexBuffer(qVertexBuffer_);
        graphics_->SetTexture(0, qCurrentTexture_);

        // Параметры шейдеров нужно задавать после указания шейдеров
        graphics_->SetShaders(qCurrentVS_, qCurrentPS_);
        graphics_->SetShaderParameter(VSP_MODEL, Matrix3x4::IDENTITY);
        UpdateViewProjMatrix();
        // Мы используем только цвета вершин. Но это значение требует шейдер Basic
        graphics_->SetShaderParameter(PSP_MATDIFFCOLOR, Color::WHITE);

        // Копируем накопленную геометрию в память видеокарты
        QVertex* buffer = (QVertex*)qVertexBuffer_->Lock(0, qNumVertices_, true);
        memcpy(buffer, qVertices_, qNumVertices_ * sizeof(QVertex));
        qVertexBuffer_->Unlock();

        // И отрисовываем её
        i32 numQuads = qNumVertices_ / VERTICES_PER_QUAD;
        graphics_->Draw(TRIANGLE_LIST, 0, numQuads * INDICES_PER_QUAD, 0, qNumVertices_);

        // Начинаем новую порцию
        qNumVertices_ = 0;
    }
}

}