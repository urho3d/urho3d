// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

// Работает в двух режимах - рендеринг фигур и рендеринг спрайтов.
// Если после рисования спрайтов рисуется какая-либо фигура (или наоборот) автоматически вызывается Flush().

#pragma once

#include "SpriteBatchBase.h"

#include "../UI/Font.h"

namespace Urho3D
{

/// Режимы зеркального отображения спрайтов и текста
enum class FlipModes : u32
{
    None = 0,
    Horizontally = 1,
    Vertically = 2,
    Both = Horizontally | Vertically
};
URHO3D_FLAGS(FlipModes);

/// @nobindtemp
class URHO3D_API SpriteBatch : public SpriteBatchBase
{
    URHO3D_OBJECT(SpriteBatch, SpriteBatchBase);

    // ============================ Рисование фигур с помощью функции AddTriangle() ============================

public:

    void DrawTriangle(const Vector2& v0, const Vector2& v1, const Vector2& v2);

    void DrawLine(const Vector2& start, const Vector2&end, float width);
    void DrawLine(float startX, float startY, float endX, float endY, float width);

    void DrawAABBSolid(const Vector2& min, const Vector2& max);
    void DrawAABoxSolid(const Vector2& centerPos, const Vector2& halfSize);
    void DrawAABoxSolid(float centerX, float centerY, float halfWidth, float halfHeight);

    void DrawCircle(const Vector2& centerPos, float radius);
    void DrawCircle(float centerX, float centerY, float radius);

    // Граница рисуется по внутреннему периметру (не выходит за пределы AABox)
    void DrawAABoxBorder(float centerX, float centerY, float halfWidth, float halfHeight, float borderWidth);

    void DrawArrow(const Vector2& start, const Vector2& end, float width);

    // ========================== Рисование спрайтов и текста с помощью функции AddQuad() ==========================

public:

    /// color - цвет в формате 0xAABBGGRR
    void DrawSprite(Texture2D* texture, const Rect& destination, const Rect* source = nullptr, u32 color = 0xFFFFFFFF,
        float rotation = 0.0f, const Vector2& origin = Vector2::ZERO, const Vector2& scale = Vector2::ONE, FlipModes flipModes = FlipModes::None);

    /// color - цвет в формате 0xAABBGGRR
    void DrawSprite(Texture2D* texture, const Vector2& position, const Rect* source = nullptr, u32 color = 0xFFFFFFFF,
        float rotation = 0.0f, const Vector2 &origin = Vector2::ZERO, const Vector2& scale = Vector2::ONE, FlipModes flipModes = FlipModes::None);

    /// color - цвет в формате 0xAABBGGRR
    void DrawString(const String& text, Font* font, float fontSize, const Vector2& position, u32 color = 0xFFFFFFFF,
        float rotation = 0.0f, const Vector2& origin = Vector2::ZERO, const Vector2& scale = Vector2::ONE, FlipModes flipModes = FlipModes::None);

private:

    // Кэширование шейдеров. Инициализируются в конструкторе
    ShaderVariation* spriteVS_;
    ShaderVariation* spritePS_;
    ShaderVariation* ttfTextVS_;
    ShaderVariation* ttfTextPS_;
    ShaderVariation* spriteTextVS_;
    ShaderVariation* spriteTextPS_;
    ShaderVariation* sdfTextVS_;
    ShaderVariation* sdfTextPS_;
    ShaderVariation* shapeVS_;
    ShaderVariation* shapePS_;

    // Данные для функции DrawSpriteInternal()
    struct
    {
        Texture2D* texture_;
        ShaderVariation* vs_;
        ShaderVariation* ps_;
        Rect destination_;
        Rect sourceUV_; // Текстурные координаты в диапазоне [0, 1]
        FlipModes flipModes_;
        Vector2 scale_;
        float rotation_;
        Vector2 origin_;
        u32 color0_;
        u32 color1_;
        u32 color2_;
        u32 color3_;
    } sprite_;

    // Перед вызовом этой функции нужно заполнить структуру sprite_
    void DrawSpriteInternal();

    // ========================================= Остальное =========================================

public:

    SpriteBatch(Context* context);
};

}
