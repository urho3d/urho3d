// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

// Класс SpriteBatch разбит на части для более легкого восприятия кода

#pragma once

#include "../Core/Object.h"
#include "../Graphics/Graphics.h"
#include "../GraphicsAPI/IndexBuffer.h"
#include "../GraphicsAPI/ShaderVariation.h"
#include "../GraphicsAPI/Texture2D.h"
#include "../GraphicsAPI/VertexBuffer.h"

namespace Urho3D
{

/// @nobindtemp
class URHO3D_API SpriteBatchBase : public Object
{
    URHO3D_OBJECT(SpriteBatchBase, Object);

    // ============================ Пакетный рендеринг треугольников ============================

private:

    // Максимальное число треугольников в порции
    inline static constexpr i32 MAX_TRIANGLES_IN_PORTION = 600;

    // Число вершин в треугольнике
    inline static constexpr i32 VERTICES_PER_TRIANGLE = 3;

    // Атрибуты вершин треугольников
    struct TVertex
    {
        Vector3 position_;
        u32 color_; // Цвет в формате 0xAABBGGRR
    };

    // Текущая порция треугольников
    TVertex tVertices_[MAX_TRIANGLES_IN_PORTION * VERTICES_PER_TRIANGLE];

    // Число вершин в массиве tVertices_
    i32 tNumVertices_ = 0;

    // Шейдеры для рендеринга треугольников. Инициализируются в конструкторе
    ShaderVariation* tVertexShader_;
    ShaderVariation* tPixelShader_;

    // Вершинный буфер для треугольников (индексный буфер не используется)
    SharedPtr<VertexBuffer> tVertexBuffer_;

protected:

    // Данные для функции AddTriangle().
    // Заполняем заранее выделенную память, вместо передачи кучи аргументов в функцию
    struct
    {
        TVertex v0_, v1_, v2_;
    } triangle_;

    // Добавляет 3 вершины в массив tVertices_. Вызывает Flush(), если массив полон.
    // Перед вызовом этой функции необходимо заполнить структуру triangle_
    void AddTriangle();

public:

    /// Указывает цвет для следующих треугольников (в формате 0xAABBGGRR)
    void SetShapeColor(u32 color);

    /// Указывает цвет для следующих треугольников
    void SetShapeColor(const Color& color);

    // ============================ Пакетный рендеринг четырехугольников ============================

private:

    // Максимальное число четырёхугольников в порции
    inline static constexpr i32 MAX_QUADS_IN_PORTION = 500;

    // Четырёхугольник состоит из двух треугольников, а значит у него 6 вершин.
    // То есть каждый четырёхугольник занимает 6 элементов в индексном буфере
    inline static constexpr i32 INDICES_PER_QUAD = 6;

    // Две вершины четырёхугольника идентичны для обоих треугольников, поэтому
    // в вершинном буфере каждый четырёхугольник занимает 4 элемента
    inline static constexpr i32 VERTICES_PER_QUAD = 4;

    // Атрибуты вершин четырёхугольников
    struct QVertex
    {
        Vector3 position_;
        u32 color_; // Цвет в формате 0xAABBGGRR
        Vector2 uv_;
    };

    // Текущая порция четырёхугольников
    QVertex qVertices_[MAX_QUADS_IN_PORTION * VERTICES_PER_QUAD];

    // Число вершин в массиве qVertices_
    i32 qNumVertices_ = 0;

    // Текущая текстура
    Texture2D* qCurrentTexture_ = nullptr;

    // Текущие шейдеры
    ShaderVariation* qCurrentVS_ = nullptr;
    ShaderVariation* qCurrentPS_ = nullptr;

    // Буферы
    SharedPtr<IndexBuffer> qIndexBuffer_;
    SharedPtr<VertexBuffer> qVertexBuffer_;

protected:

    // Данные для функции AddQuad().
    // Заполняем заранее выделенную память, вместо передачи кучи аргументов в функцию
    struct
    {
        Texture2D* texture_;
        ShaderVariation* vs_;
        ShaderVariation* ps_;
        QVertex v0_, v1_, v2_, v3_;
    } quad_;

    // Добавляет 4 вершины в массив quads_.
    // Если массив полон или требуемые шейдеры или текстура отличаются от текущих, то автоматически
    // происходит вызов функции Flush() (то есть начинается новая порция).
    // Перед вызовом этой функции необходимо заполнить структуру quad_
    void AddQuad();

    // ============================ Общее ============================

private:

    void UpdateViewProjMatrix();
    IntRect GetViewportRect();

protected:

    // Кешируем доступ к подсистеме. Инициализируется в конструкторе
    Graphics* graphics_ = nullptr;

public:

    // Режим наложения
    BlendMode blendMode_ = BLEND_ALPHA;

    // Если использовать CMP_LESSEQUAL, то будет учитываться содержимое буфера глубины
    // (но сам SpriteBatch ничего не пишет в буфер глубины).
    // При CMP_ALWAYS каждый выводимый спрайт будет перекрывать прежде отрисованные пиксели
    CompareMode compareMode_ = CMP_ALWAYS;

    // Если определена камера, то SpriteBatch рисует в мировых координатах
    Camera* camera_ = nullptr;

    // Размеры виртуального экрана. Если одна из координат <= 0, то используются реальные размеры экрана
    IntVector2 virtualScreenSize_ = IntVector2(0, 0);

    bool VirtualScreenUsed() const { return virtualScreenSize_.x_ > 0 && virtualScreenSize_.y_ > 0; }

    // Конструктор
    SpriteBatchBase(Context* context);

    // Рендерит накопленную геометрию (то есть текущую порцию)
    void Flush();

    // Переводит реальные координаты в виртуальные. Используется для курсора мыши
    Vector2 GetVirtualPos(const Vector2& realPos);
};

} // namespace Urho3D
