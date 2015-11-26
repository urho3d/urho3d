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

#pragma once

#include "../Math/Vector4.h"

// Defined by Windows headers
#undef TRANSPARENT

namespace Urho3D
{

class String;

/// RGBA color.
class URHO3D_API Color
{
public:
    /// Construct with default values (opaque white.)
    Color() :
        r_(1.0f),
        g_(1.0f),
        b_(1.0f),
        a_(1.0f)
    {
    }

    /// Copy-construct from another color.
    Color(const Color& color) :
        r_(color.r_),
        g_(color.g_),
        b_(color.b_),
        a_(color.a_)
    {
    }

    /// Construct from another color and modify the alpha.
    Color(const Color& color, float a) :
        r_(color.r_),
        g_(color.g_),
        b_(color.b_),
        a_(a)
    {
    }

    /// Construct from RGB values and set alpha fully opaque.
    Color(float r, float g, float b) :
        r_(r),
        g_(g),
        b_(b),
        a_(1.0f)
    {
    }

    /// Construct from RGBA values.
    Color(float r, float g, float b, float a) :
        r_(r),
        g_(g),
        b_(b),
        a_(a)
    {
    }

    /// Construct from a float array.
    explicit Color(const float* data) :
        r_(data[0]),
        g_(data[1]),
        b_(data[2]),
        a_(data[3])
    {
    }
    
    /// Assign from another color.
    Color& operator =(const Color& rhs)
    {
        r_ = rhs.r_;
        g_ = rhs.g_;
        b_ = rhs.b_;
        a_ = rhs.a_;
        return *this;
    }    

    /// Test for equality with another color without epsilon.
    bool operator ==(const Color& rhs) const { return r_ == rhs.r_ && g_ == rhs.g_ && b_ == rhs.b_ && a_ == rhs.a_; }

    /// Test for inequality with another color without epsilon.
    bool operator !=(const Color& rhs) const { return r_ != rhs.r_ || g_ != rhs.g_ || b_ != rhs.b_ || a_ != rhs.a_; }

    /// Multiply with a scalar.
    Color operator *(float rhs) const { return Color(r_ * rhs, g_ * rhs, b_ * rhs, a_ * rhs); }

    /// Add a color.
    Color operator +(const Color& rhs) const { return Color(r_ + rhs.r_, g_ + rhs.g_, b_ + rhs.b_, a_ + rhs.a_); }

    /// Return negation.
    Color operator -() const { return Color(-r_, -g_, -b_, -a_); }

    /// Substract a color.
    Color operator -(const Color& rhs) const { return Color(r_ - rhs.r_, g_ - rhs.g_, b_ - rhs.b_, a_ - rhs.a_); }

    /// Add-assign a color.
    Color& operator +=(const Color& rhs)
    {
        r_ += rhs.r_;
        g_ += rhs.g_;
        b_ += rhs.b_;
        a_ += rhs.a_;
        return *this;
    }

    /// Return float data.
    const float* Data() const { return &r_; }

    /// Return color packed to a 32-bit integer, with R component in the lowest 8 bits. Components are clamped to [0, 1] range.
    unsigned ToUInt() const;
    /// Return HSL color-space representation as a Vector3; the RGB values are clipped before conversion but not changed in the process.
    Vector3 ToHSL() const;
    /// Return HSV color-space representation as a Vector3; the RGB values are clipped before conversion but not changed in the process.
    Vector3 ToHSV() const;
    /// Set RGBA values from specified HSL values and alpha.
    void FromHSL(float h, float s, float l, float a = 1.0f);
    /// Set RGBA values from specified HSV values and alpha.
    void FromHSV(float h, float s, float v, float a = 1.0f);

    /// Return RGB as a three-dimensional vector.
    Vector3 ToVector3() const { return Vector3(r_, g_, b_); }

    /// Return RGBA as a four-dimensional vector.
    Vector4 ToVector4() const { return Vector4(r_, g_, b_, a_); }

    /// Return sum of RGB components.
    float SumRGB() const { return r_ + g_ + b_; }

    /// Return average value of the RGB channels.
    float Average() const { return (r_ + g_ + b_) / 3.0f; }

    /// Return the 'grayscale' representation of RGB values, as used by JPEG and PAL/NTSC among others.
    float Luma() const { return r_ * 0.299f + g_ * 0.587f + b_ * 0.114f; }

    /// Return the colorfulness relative to the brightness of a similarly illuminated white.
    float Chroma() const;
    /// Return hue mapped to range [0, 1.0).
    float Hue() const;
    /// Return saturation as defined for HSL.
    float SaturationHSL() const;
    /// Return saturation as defined for HSV.
    float SaturationHSV() const;

    /// Return value as defined for HSV: largest value of the RGB components. Equivalent to calling MinRGB().
    float Value() const { return MaxRGB(); }

    /// Return lightness as defined for HSL: average of the largest and smallest values of the RGB components.
    float Lightness() const;

    /// Stores the values of least and greatest RGB component at specified pointer addresses, optionally clipping those values to [0, 1] range.
    void Bounds(float* min, float* max, bool clipped = false) const;
    /// Return the largest value of the RGB components.
    float MaxRGB() const;
    /// Return the smallest value of the RGB components.
    float MinRGB() const;
    /// Return range, defined as the difference between the greatest and least RGB component.
    float Range() const;

    /// Clip to [0, 1.0] range.
    void Clip(bool clipAlpha = false);
    /// Inverts the RGB channels and optionally the alpha channel as well.
    void Invert(bool invertAlpha = false);
    /// Return linear interpolation of this color with another color.
    Color Lerp(const Color& rhs, float t) const;

    /// Return color with absolute components.
    Color Abs() const { return Color(Urho3D::Abs(r_), Urho3D::Abs(g_), Urho3D::Abs(b_), Urho3D::Abs(a_)); }

    /// Test for equality with another color with epsilon.
    bool Equals(const Color& rhs) const
    {
        return Urho3D::Equals(r_, rhs.r_) && Urho3D::Equals(g_, rhs.g_) && Urho3D::Equals(b_, rhs.b_) && Urho3D::Equals(a_, rhs.a_);
    }

    /// Return as string.
    String ToString() const;

    /// Red value.
    float r_;
    /// Green value.
    float g_;
    /// Blue value.
    float b_;
    /// Alpha value.
    float a_;

    /// Opaque white color.
    static const Color WHITE;
    /// Opaque gray color.
    static const Color GRAY;
    /// Opaque black color.
    static const Color BLACK;
    /// Opaque red color.
    static const Color RED;
    /// Opaque green color.
    static const Color GREEN;
    /// Opaque blue color.
    static const Color BLUE;
    /// Opaque cyan color.
    static const Color CYAN;
    /// Opaque magenta color.
    static const Color MAGENTA;
    /// Opaque yellow color.
    static const Color YELLOW;
    /// Transparent color (black with no alpha).
    static const Color TRANSPARENT;

protected:
    /// Return hue value given greatest and least RGB component, value-wise.
    float Hue(float min, float max) const;
    /// Return saturation (HSV) given greatest and least RGB component, value-wise.
    float SaturationHSV(float min, float max) const;
    /// Return saturation (HSL) given greatest and least RGB component, value-wise.
    float SaturationHSL(float min, float max) const;
    /// Calculate and set RGB values. Convenience function used by FromHSV and FromHSL to avoid code duplication.
    void FromHCM(float h, float c, float m);
};

/// Multiply Color with a scalar.
inline Color operator *(float lhs, const Color& rhs) { return rhs * lhs; }

}
