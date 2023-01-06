// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#include "SpriteBatch.h"

#include "../UI/FontFace.h"

namespace Urho3D
{

SpriteBatch::SpriteBatch(Context* context) : SpriteBatchBase(context)
{
    spriteVS_ = graphics_->GetShader(VS, "Basic", "DIFFMAP VERTEXCOLOR");
    spritePS_ = graphics_->GetShader(PS, "Basic", "DIFFMAP VERTEXCOLOR");
    ttfTextVS_ = graphics_->GetShader(VS, "Text");
    ttfTextPS_ = graphics_->GetShader(PS, "Text", "ALPHAMAP");
    spriteTextVS_ = graphics_->GetShader(VS, "Text");
    spriteTextPS_ = graphics_->GetShader(PS, "Text");
    sdfTextVS_ = graphics_->GetShader(VS, "Text");
    sdfTextPS_ = graphics_->GetShader(PS, "Text", "SIGNED_DISTANCE_FIELD");
    shapeVS_ = graphics_->GetShader(VS, "Basic", "VERTEXCOLOR");
    shapePS_ = graphics_->GetShader(PS, "Basic", "VERTEXCOLOR");
}

static Rect PosToDest(const Vector2& position, Texture2D* texture, const Rect* src)
{
    if (src == nullptr)
    {
        // Проверки не производятся, текстура должна быть корректной
        return Rect
        (
            position.x_,
            position.y_,
            position.x_ + texture->GetWidth(),
            position.y_ + texture->GetHeight()
        );
    }
    else
    {
        return Rect
        (
            position.x_,
            position.y_,
            position.x_ + (src->Right() - src->Left()), // Сперва вычисляем размер, так как там вероятно более близкие
            position.y_ + (src->Bottom() - src->Top()) // значения и меньше ошибка вычислений
        );
    }
}

// Преобразует пиксельные координаты в диапазон [0, 1]
static Rect SrcToUV(const Rect* source, Texture2D* texture)
{
    if (source == nullptr)
    {
        return Rect(Vector2::ZERO, Vector2::ONE);
    }
    else
    {
        // Проверки не производятся, текстура должна быть корректной
        float invWidth = 1.0f / texture->GetWidth();
        float invHeight = 1.0f / texture->GetHeight();
        return Rect
        (
            source->min_.x_ * invWidth,
            source->min_.y_ * invHeight,
            source->max_.x_ * invWidth,
            source->max_.y_ * invHeight
        );
    }
}

void SpriteBatch::DrawSprite(Texture2D* texture, const Rect& destination, const Rect* source, u32 color,
    float rotation, const Vector2& origin, const Vector2& scale, FlipModes flipModes)
{
    if (!texture)
        return;

    sprite_.texture_ = texture;
    sprite_.vs_ = spriteVS_;
    sprite_.ps_ = spritePS_;
    sprite_.destination_ = destination;
    sprite_.sourceUV_ = SrcToUV(source, texture);
    sprite_.flipModes_ = flipModes;
    sprite_.scale_ = scale;
    sprite_.rotation_ = rotation;
    sprite_.origin_ = origin;
    sprite_.color0_ = color;
    sprite_.color1_ = color;
    sprite_.color2_ = color;
    sprite_.color3_ = color;

    DrawSpriteInternal();
}

void SpriteBatch::DrawSprite(Texture2D* texture, const Vector2& position, const Rect* source, u32 color,
    float rotation, const Vector2 &origin, const Vector2& scale, FlipModes flipModes)
{
    if (!texture)
        return;

    sprite_.texture_ = texture;
    sprite_.vs_ = spriteVS_;
    sprite_.ps_ = spritePS_;
    sprite_.destination_ = PosToDest(position, texture, source);
    sprite_.sourceUV_ = SrcToUV(source, texture);
    sprite_.flipModes_ = flipModes;
    sprite_.scale_ = scale;
    sprite_.rotation_ = rotation;
    sprite_.origin_ = origin;
    sprite_.color0_ = color;
    sprite_.color1_ = color;
    sprite_.color2_ = color;
    sprite_.color3_ = color;

    DrawSpriteInternal();
}

void SpriteBatch::DrawSpriteInternal()
{
    quad_.vs_ = sprite_.vs_;
    quad_.ps_ = sprite_.ps_;
    quad_.texture_ = sprite_.texture_;

    // Если спрайт не отмасштабирован и не повёрнут, то прорисовка очень проста
    if (sprite_.rotation_ == 0.0f && sprite_.scale_ == Vector2::ONE)
    {
        // Сдвигаем спрайт на -origin
        Rect resultDest(sprite_.destination_.min_ - sprite_.origin_, sprite_.destination_.max_ - sprite_.origin_);

        // Лицевая грань задаётся по часовой стрелке. Учитываем, что ось Y направлена вниз.
        // Но нет большой разницы, так как спрайты двусторонние
        quad_.v0_.position_ = Vector3(resultDest.min_.x_, resultDest.min_.y_, 0); // Верхний левый угол спрайта
        quad_.v1_.position_ = Vector3(resultDest.max_.x_, resultDest.min_.y_, 0); // Верхний правый угол
        quad_.v2_.position_ = Vector3(resultDest.max_.x_, resultDest.max_.y_, 0); // Нижний правый угол
        quad_.v3_.position_ = Vector3(resultDest.min_.x_, resultDest.max_.y_, 0); // Нижний левый угол
    }
    else
    {
        // Масштабировать и вращать необходимо относительно центра локальных координат:
        // 1) При стандартном origin == Vector2::ZERO, который соответствует верхнему левому углу спрайта,
        //    локальные координаты будут Rect(ноль, размерыСпрайта),
        //    то есть Rect(Vector2::ZERO, destination.max_ - destination.min_)
        // 2) При ненулевом origin нужно сдвинуть на -origin
        Rect local(-sprite_.origin_, sprite_.destination_.max_ - sprite_.destination_.min_ - sprite_.origin_);

        float sin, cos;
        SinCos(sprite_.rotation_, sin, cos);

        // Нам нужна матрица, которая масштабирует и поворачивает вершину в локальных координатах, а затем
        // смещает ее в требуемые мировые координаты.
        // Но в матрице 3x3 последняя строка "0 0 1", умножать на которую бессмысленно.
        // Поэтому вычисляем без матрицы для оптимизации
        float m11 = cos * sprite_.scale_.x_; float m12 = -sin * sprite_.scale_.y_; float m13 = sprite_.destination_.min_.x_;
        float m21 = sin * sprite_.scale_.x_; float m22 =  cos * sprite_.scale_.y_; float m23 = sprite_.destination_.min_.y_;
        //          0                                      0                                     1

        float minXm11 = local.min_.x_ * m11;
        float minXm21 = local.min_.x_ * m21;
        float maxXm11 = local.max_.x_ * m11;
        float maxXm21 = local.max_.x_ * m21;
        float minYm12 = local.min_.y_ * m12;
        float minYm22 = local.min_.y_ * m22;
        float maxYm12 = local.max_.y_ * m12;
        float maxYm22 = local.max_.y_ * m22;

        // transform * Vector3(local.min_.x_, local.min_.y_, 1.0f);
        quad_.v0_.position_ = Vector3(minXm11 + minYm12 + m13,
                                      minXm21 + minYm22 + m23,
                                      0.0f);

        // transform * Vector3(local.max_.x_, local.min_.y_, 1.0f).
        quad_.v1_.position_ = Vector3(maxXm11 + minYm12 + m13,
                                      maxXm21 + minYm22 + m23,
                                      0.0f);

        // transform * Vector3(local.max_.x_, local.max_.y_, 1.0f).
        quad_.v2_.position_ = Vector3(maxXm11 + maxYm12 + m13,
                                      maxXm21 + maxYm22 + m23,
                                      0.0f);

        // transform * Vector3(local.min_.x_, local.max_.y_, 1.0f).
        quad_.v3_.position_ = Vector3(minXm11 + maxYm12 + m13,
                                      minXm21 + maxYm22 + m23,
                                      0.0f);
    }

    if (!!(sprite_.flipModes_ & FlipModes::Horizontally))
        Swap(sprite_.sourceUV_.min_.x_, sprite_.sourceUV_.max_.x_);

    if (!!(sprite_.flipModes_ & FlipModes::Vertically))
        Swap(sprite_.sourceUV_.min_.y_, sprite_.sourceUV_.max_.y_);

    quad_.v0_.color_ = sprite_.color0_;
    quad_.v0_.uv_ = sprite_.sourceUV_.min_;

    quad_.v1_.color_ = sprite_.color1_;
    quad_.v1_.uv_ = Vector2(sprite_.sourceUV_.max_.x_, sprite_.sourceUV_.min_.y_);

    quad_.v2_.color_ = sprite_.color2_;
    quad_.v2_.uv_ = sprite_.sourceUV_.max_;

    quad_.v3_.color_ = sprite_.color3_;
    quad_.v3_.uv_ = Vector2(sprite_.sourceUV_.min_.x_, sprite_.sourceUV_.max_.y_);

    AddQuad();
}

void SpriteBatch::DrawString(const String& text, Font* font, float fontSize, const Vector2& position, u32 color,
    float rotation, const Vector2& origin, const Vector2& scale, FlipModes flipModes)
{
    if (text.Length() == 0)
        return;

    Vector<c32> unicodeText;
    for (i32 i = 0; i < text.Length();)
        unicodeText.Push(text.NextUTF8Char(i));

    if (font->GetFontType() == FONT_FREETYPE)
    {
        sprite_.vs_ = ttfTextVS_;
        sprite_.ps_ = ttfTextPS_;
    }
    else // FONT_BITMAP
    {
        if (font->IsSDFFont())
        {
            sprite_.vs_ = sdfTextVS_;
            sprite_.ps_ = sdfTextPS_;
        }
        else
        {
            sprite_.vs_ = spriteTextVS_;
            sprite_.ps_ = spriteTextPS_;
        }
    }

    sprite_.flipModes_ = flipModes;
    sprite_.scale_ = scale;
    sprite_.rotation_ = rotation;
    sprite_.color0_ = color;
    sprite_.color1_ = color;
    sprite_.color2_ = color;
    sprite_.color3_ = color;

    FontFace* face = font->GetFace(fontSize);
    const Vector<SharedPtr<Texture2D>>& textures = face->GetTextures();
    // По идее все текстуры одинакового размера
    float pixelWidth = 1.0f / textures[0]->GetWidth();
    float pixelHeight = 1.0f / textures[0]->GetHeight();

    Vector2 charPos = position;
    Vector2 charOrig = origin;

    i32 i = 0;
    i32 step = 1;

    if (!!(flipModes & FlipModes::Horizontally))
    {
        i = unicodeText.Size() - 1;
        step = -1;
    }

    for (; i >= 0 && i < unicodeText.Size(); i += step)
    {
        const FontGlyph* glyph = face->GetGlyph(unicodeText[i]);
        float gx = (float)glyph->x_;
        float gy = (float)glyph->y_;
        float gw = (float)glyph->width_;
        float gh = (float)glyph->height_;
        float gox = (float)glyph->offsetX_;
        float goy = (float)glyph->offsetY_;

        sprite_.texture_ = textures[glyph->page_];
        sprite_.destination_ = Rect(charPos.x_, charPos.y_, charPos.x_ + gw, charPos.y_ + gh);
        sprite_.sourceUV_ = Rect(gx * pixelWidth, gy * pixelHeight, (gx + gw) * pixelWidth, (gy + gh) * pixelHeight);

        // Модифицируем origin, а не позицию, чтобы было правильное вращение
        sprite_.origin_ = !!(flipModes & FlipModes::Vertically) ? charOrig - Vector2(gox, face->GetRowHeight() - goy - gh) : charOrig - Vector2(gox, goy);

        DrawSpriteInternal();

        charOrig.x_ -= (float)glyph->advanceX_;
    }
}

// В отличие от Sign() никогда не возвращает ноль
template <typename T>
T MySign(T value) { return value >= 0.0f ? 1.0f : -1.0f; }

void SpriteBatch::DrawTriangle(const Vector2& v0, const Vector2& v1, const Vector2& v2)
{
    triangle_.v0_.position_ = Vector3(v0);
    triangle_.v1_.position_ = Vector3(v1);
    triangle_.v2_.position_ = Vector3(v2);
    AddTriangle();
}

void SpriteBatch::DrawLine(const Vector2& start, const Vector2&end, float width)
{
    float len = (end - start).Length();
    if (Equals(len, 0.0f))
        return;

    // Линия - это прямоугольный полигон. Когда линия не повернута (угол поворота равен нулю), она горизонтальна.
    //   v0 ┌───────────────┐ v1
    //start ├───────────────┤ end
    //   v3 └───────────────┘ v2
    // Пользователь задает координаты точек start и end, а нам нужно определить координаты вершин v0, v1, v2, v3.
    // Легче всего вычислить СМЕЩЕНИЯ вершин v0 и v3 от точки start и смещения вершин v1 и v2 от точки end,
    // а потом прибавить эти смещения к координатам точек start и end.

    // Когда линия горизонтальна, v0 имеет смещение (0, -halfWidth) относительно точки start,
    // а вершина v3 имеет смещение (0, halfWidth) относительно той же точки start.
    // Аналогично v1 = (0, -halfWidth) и v2 = (0, halfWidth) относительно точки end.
    float halfWidth = Abs(width * 0.5f);

    // Так как мы оперируем смещениями, то при повороте линии вершины v0 и v3 вращаются вокруг start, а v1 и v2 - вокруг end.
    // Итак, вращаем точку v0 с локальными координатами (0, halfWidth).
    // {newX = oldX * cos(deltaAngle) - oldY * sin(deltaAngle) = 0 * cos(deltaAngle) - halfWidth * sin(deltaAngle)
    // {newY = oldX * sin(deltaAngle) + oldY * cos(deltaAngle) = 0 * sin(deltaAngle) + halfWidth * cos(deltaAngle)
    // Так как повернутая линия может оказаться в любом квадранте, при вычислениии синуса и косинуса нам важен знак.
    len = len * MySign(end.x_ - start.x_) * MySign(end.y_ - start.y_);
    float cos = (end.x_ - start.x_) / len; // Прилежащий катет к гипотенузе.
    float sin = (end.y_ - start.y_) / len; // Противолежащий катет к гипотенузе.
    Vector2 offset = Vector2(-halfWidth * sin, halfWidth * cos);

    // Так как противоположные стороны параллельны, то можно не делать повторных вычислений:
    // смещение v0 всегда равно смещению v1, смещение v3 = смещению v2.
    // К тому же смещения вершин v0, v1 отличаются от смещений вершин v3, v2 только знаком (противоположны).
    Vector2 v0 = Vector2(start.x_ + offset.x_, start.y_ + offset.y_);
    Vector2 v1 = Vector2(end.x_ + offset.x_, end.y_ + offset.y_);
    Vector2 v2 = Vector2(end.x_ - offset.x_, end.y_ - offset.y_);
    Vector2 v3 = Vector2(start.x_ - offset.x_, start.y_ - offset.y_);

    DrawTriangle(v0, v1, v2);
    DrawTriangle(v2, v3, v0);
}

void SpriteBatch::DrawLine(float startX, float startY, float endX, float endY, float width)
{
    DrawLine(Vector2(startX, startY), Vector2(endX, endY), width);
}

void SpriteBatch::DrawAABoxSolid(const Vector2& centerPos, const Vector2& halfSize)
{
    DrawAABoxSolid(centerPos.x_, centerPos.y_, halfSize.x_, halfSize.y_);
}

void SpriteBatch::DrawAABBSolid(const Vector2& min, const Vector2& max)
{
    Vector2 rightTop = Vector2(max.x_, min.y_); // Правый верхний угол
    Vector2 leftBot = Vector2(min.x_, max.y_); // Левый нижний

    DrawTriangle(min, rightTop, max);
    DrawTriangle(leftBot, min, max);
}

void SpriteBatch::DrawAABoxSolid(float centerX, float centerY, float halfWidth, float halfHeight)
{
    if (halfWidth < M_EPSILON || halfHeight < M_EPSILON)
        return;

    Vector2 v0 = Vector2(centerX - halfWidth, centerY - halfHeight); // Левый верхний угол
    Vector2 v1 = Vector2(centerX + halfWidth, centerY - halfHeight); // Правый верхний
    Vector2 v2 = Vector2(centerX + halfWidth, centerY + halfHeight); // Правый нижний
    Vector2 v3 = Vector2(centerX - halfWidth, centerY + halfHeight); // Левый нижний

    DrawTriangle(v0, v1, v2);
    DrawTriangle(v2, v3, v0);
}

void SpriteBatch::DrawAABoxBorder(float centerX, float centerY, float halfWidth, float halfHeight, float borderWidth)
{
    if (borderWidth < M_EPSILON || halfWidth < M_EPSILON || halfHeight < M_EPSILON)
        return;

    float halfBorderWidth = borderWidth * 0.5f;

    // Тут нужно обработать случай, когда толщина границы больше размера AABB

    // Верхняя граница
    float y = centerY - halfHeight + halfBorderWidth;
    DrawLine(centerX - halfWidth, y, centerX + halfWidth, y, borderWidth);

    // Нижняя граница
    y = centerY + halfHeight - halfBorderWidth;
    DrawLine(centerX - halfWidth, y, centerX + halfWidth, y, borderWidth);

    // При отрисовке боковых границ не перекрываем верхнюю и нижнюю, чтобы нормально отрисовывалось в случае полупрозрачного цвета

    // Левая граница
    float x = centerX - halfWidth + halfBorderWidth;
    DrawLine(x, centerY - halfHeight + borderWidth, x, centerY + halfHeight - borderWidth, borderWidth);

    // Правая граница
    x = centerX + halfWidth - halfBorderWidth;
    DrawLine(x, centerY - halfHeight + borderWidth, x, centerY + halfHeight - borderWidth, borderWidth);
}

void SpriteBatch::DrawCircle(const Vector2& centerPos, float radius)
{
    const int numPoints = 40;
    Vector2 points[numPoints];

    for (int i = 0; i < numPoints; ++i)
    {
        float angle = 360.0f * (float)i / (float)numPoints;
        float cos, sin;
        SinCos(angle, sin, cos);
        points[i] = Vector2(cos, sin) * radius + centerPos;
    }

    for (int i = 1; i < numPoints; ++i)
        DrawTriangle(points[i], points[i - 1], centerPos);

    // Рисуем последний сегмент
    DrawTriangle(points[0], points[numPoints - 1], centerPos);
}

void SpriteBatch::DrawCircle(float centerX, float centerY, float radius)
{
    DrawCircle(Vector2(centerX, centerY), radius);
}

// Поворачивает вектор по часовой стрелке на 90 градусов
static Vector2 RotatePlus90(const Vector2& v)
{
    Vector2 result(-v.y_, v.x_);
    return result;
}

// Поворачивает вектор по часовой стрелке на -90 градусов
static Vector2 RotateMinus90(const Vector2& v)
{
    Vector2 result(v.y_, -v.x_);
    return result;
}

void SpriteBatch::DrawArrow(const Vector2& start, const Vector2& end, float width)
{
    // TODO: настроить Doxygen на поддержку картинок и тут ссылку на картинку
    Vector2 vec = end - start;

    float len = vec.Length();
    if (len < M_EPSILON)
        return;

    Vector2 dir = vec.Normalized();

    // TODO: Обработать случай, когда вектор короткий
    float headLen = width * 2; // Длина наконечника
    float shaftLen = len - headLen; // Длина древка
    Vector2 headStart = dir * shaftLen + start; // Начало наконечника
    Vector2 head = dir * headLen; // Вектор от точки headStart до точки end
    Vector2 headTop = RotateMinus90(head) + headStart;
    Vector2 headBottom = RotatePlus90(head) + headStart;
    DrawLine(start, headStart, width);
    DrawTriangle(headStart, headTop, end);
    DrawTriangle(headStart, headBottom, end);
}

}