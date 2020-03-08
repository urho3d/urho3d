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

#include "../IO/Log.h"
#include "../Core/Context.h"
#include "../Scene/Node.h"
#include "../Urho2D/Sprite2D.h"
#include "../Urho2D/StretchableSprite2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

namespace
{

void checkBorder(int border, float drawSize)
{
    /* not clamping yet, as drawSize may still change and come to accommodate large borders */
    if (border < 0 || border * PIXEL_SIZE > drawSize)
        URHO3D_LOGWARNINGF("Border out of bounds (%d), may be clamped", border);
}

Rect calcEffectiveBorder(const IntRect& border, const Vector2& drawSize)
{
    Vector2 min{Clamp(border.left_ * PIXEL_SIZE, 0.0f, drawSize.x_),
                Clamp(border.bottom_ * PIXEL_SIZE, 0.0f, drawSize.y_)};
    return Rect{min, {Clamp(border.right_ * PIXEL_SIZE, 0.0f, drawSize.x_ - min.x_),
                      Clamp(border.top_ * PIXEL_SIZE, 0.0f, drawSize.y_ - min.y_)} /* max*/ };
}

void prepareXYCoords(float coords[4], float low, float high, float lowBorder, float highBorder, float scale)
{
    coords[0] = low * scale;
    coords[3] = high * scale;

    auto scaleSign = Sign(scale);
    auto borderSize = lowBorder + highBorder;
    if (borderSize > scaleSign * (coords[3] - coords[0]))
    {
        auto size = high - low;
        coords[1] = coords[2] = scale * (low + (lowBorder * size / borderSize));
    }
    else
    {
        auto absScale = Abs(scale);
        coords[1] = (low * absScale + lowBorder) * scaleSign;
        coords[2] = (high * absScale - highBorder) * scaleSign;
    }
}

void prepareUVCoords(float coords[4], float low, float high, float lowBorder, float highBorder, float drawSize)
{
    coords[0] = low;
    coords[1] = low + lowBorder / drawSize;
    coords[2] = high - highBorder / drawSize;
    coords[3] = high;
}

void prepareVertices(Vertex2D vtx[4][4], const float xs[4], const float ys[4], const float us[4], const float vs[4], unsigned color,
    const Vector3& position, const Quaternion& rotation)
{
    for (unsigned i = 0; i < 4; ++i)
    {
        for (unsigned j = 0; j < 4; ++j)
        {
            vtx[i][j].position_ = position + rotation * Vector3{xs[i], ys[j], 0.0f};
            vtx[i][j].color_ = color;
            vtx[i][j].uv_ = Vector2{us[i], vs[j]};
        }
    }
}

void pushVertices(Vector<Vertex2D>& target, const Vertex2D source[4][4])
{
    for (unsigned i = 0; i < 3; ++i) // iterate over 3 columns
    {
        if (!Equals(source[i][0].position_.x_,
            source[i + 1][0].position_.x_)) // if width != 0
        {
            for (unsigned j = 0; j < 3; ++j) // iterate over 3 lines
            {
                if (!Equals(source[0][j].position_.y_,
                    source[0][j + 1].position_.y_)) // if height != 0
                {
                    target.Push(source[i][j]);          // V0 in V1---V2
                    target.Push(source[i][j + 1]);      // V1 in |   / |
                    target.Push(source[i + 1][j + 1]);  // V2 in | /   |
                    target.Push(source[i + 1][j]);      // V3 in V0---V3
                }
            }
        }
    }
}

} // namespace

extern const char* URHO2D_CATEGORY;

StretchableSprite2D::StretchableSprite2D(Context* context) :
    StaticSprite2D{context}
{
}

void StretchableSprite2D::RegisterObject(Context* context)
{
    context->RegisterFactory<StretchableSprite2D>(URHO2D_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(StaticSprite2D);
    URHO3D_ACCESSOR_ATTRIBUTE("Border", GetBorder, SetBorder, IntRect, IntRect::ZERO, AM_DEFAULT);
}

void StretchableSprite2D::SetBorder(const IntRect& border)
{
    border_ = border;

    auto drawSize = drawRect_.Size();

    checkBorder(border_.left_, drawSize.x_);
    checkBorder(border_.right_, drawSize.x_);
    checkBorder(border_.left_ + border_.right_, drawSize.x_);

    checkBorder(border_.bottom_, drawSize.y_);
    checkBorder(border_.top_, drawSize.y_);
    checkBorder(border_.bottom_ + border_.top_, drawSize.y_);
}

void StretchableSprite2D::UpdateSourceBatches()
{
    /* The general idea is to subdivide the image in the following 9 patches

       *---*---*---*
     2 |   |   |   |
       *---*---*---*
     1 |   |   |   |
       *---*---*---*
     0 |   |   |   |
       *---*---*---*
         0   1   2

     X scaling works as follow: as long as the scale determines that the total
     width is larger than the sum of the widths of columns 0 and 2, only
     column 1 is scaled. Otherwise, column 1 is removed and columns 0 and 2 are
     scaled, maintaining their relative size. The same principle applies for
     Y scaling (but with lines rather than columns). */

    if (!sourceBatchesDirty_ || !sprite_ || (!useTextureRect_ && !sprite_->GetTextureRectangle(textureRect_, flipX_, flipY_)))
        return;

    Vector<Vertex2D>& vertices = sourceBatches_[0].vertices_;
    vertices.Clear();

    auto effectiveBorder = calcEffectiveBorder(border_, drawRect_.Size());

    float xs[4], ys[4], us[4], vs[4]; // prepare all coordinates
    const auto signedScale = node_->GetSignedWorldScale();

    prepareXYCoords(xs, drawRect_.min_.x_, drawRect_.max_.x_, effectiveBorder.min_.x_, effectiveBorder.max_.x_, signedScale.x_);
    prepareXYCoords(ys, drawRect_.min_.y_, drawRect_.max_.y_, effectiveBorder.min_.y_, effectiveBorder.max_.y_, signedScale.y_);

    prepareUVCoords(us, textureRect_.min_.x_, textureRect_.max_.x_, effectiveBorder.min_.x_, effectiveBorder.max_.x_,
        drawRect_.max_.x_ - drawRect_.min_.x_);
    prepareUVCoords(vs, textureRect_.min_.y_, textureRect_.max_.y_, -effectiveBorder.min_.y_,
        -effectiveBorder.max_.y_ /* texture y direction inverted*/, drawRect_.max_.y_ - drawRect_.min_.y_);

    Vertex2D vtx[4][4]; // prepare all vertices
    prepareVertices(vtx, xs, ys, us, vs, color_.ToUInt(), node_->GetWorldPosition(), node_->GetWorldRotation());

    pushVertices(vertices, vtx); // push the vertices that make up each patch

    sourceBatchesDirty_ = false;
}

}
