//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Vector4.h"

class String;

/// RGBA color.
class Color
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
    
    /// Test for equality with another color.
    bool operator == (const Color& rhs) const { return Equals(r_, rhs.r_) && Equals(g_, rhs.g_) && Equals(b_, rhs.b_) && Equals(a_, rhs.a_); }
    /// Test for inequality with another color.
    bool operator != (const Color& rhs) const { return !Equals(r_, rhs.r_) || !Equals(g_, rhs.g_) || !Equals(b_, rhs.b_) || !Equals(a_, rhs.a_); }
    /// Multiply with a scalar.
    Color operator * (float rhs) const { return Color(r_ * rhs, g_ * rhs, b_ * rhs, a_ * rhs); }
    /// Add a color.
    Color operator + (const Color& rhs) const { return Color(r_ + rhs.r_, g_ + rhs.g_, b_ + rhs.b_, a_ + rhs.a_); }
    
    /// Add-assign a color.
    Color& operator += (const Color& rhs)
    {
        r_ += rhs.r_;
        g_ += rhs.g_;
        b_ += rhs.b_;
        a_ += rhs.a_;
        return *this;
    }
    
    /// Return float data.
    const float* GetData() const { return &r_; }
    /// Return RGB values as a Vector3.
    Vector3 RGBValues() const { return Vector3(r_, g_, b_); }
    /// Return approximate intensity.
    float Intensity() const { return RGBValues().DotProduct(Vector3(0.333f, 0.333f, 0.333f)); }
    
    /// Linear interpolation with another color.
    Color Lerp(const Color& rhs, float t) const
    {
        float invT = 1.0f - t;
        return Color(
            r_ * invT + rhs.r_ * t,
            g_ * invT + rhs.g_ * t,
            b_ * invT + rhs.b_ * t,
            a_ * invT + rhs.a_ * t
        );
    }
    
    /// Return color packed to a 32-bit integer. Only the range [0, 1] is supported for components.
    unsigned ToUInt() const
    {
        unsigned r = (unsigned)(Clamp(r_ * 255.0f, 0.0f, 255.0f));
        unsigned g = (unsigned)(Clamp(g_ * 255.0f, 0.0f, 255.0f));
        unsigned b = (unsigned)(Clamp(b_ * 255.0f, 0.0f, 255.0f));
        unsigned a = (unsigned)(Clamp(a_ * 255.0f, 0.0f, 255.0f));
        /// \todo Model data will need to be converted on OpenGL if it has vertex colors
        #ifdef USE_OPENGL
            return (((a) & 0xff) << 24) | (((b) & 0xff) << 16) | (((g) & 0xff) << 8) | ((r) & 0xff);
        #else
            return (((a) & 0xff) << 24) | (((r) & 0xff) << 16) | (((g) & 0xff) << 8) | ((b) & 0xff);
        #endif
    }
    
    /// Return as a four-dimensional vector.
    Vector4 ToVector4() const { return Vector4(r_, g_, b_, a_); }
    
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
    /// Opaque yellow color.
    static const Color YELLOW;
    /// Opaque red color.
    static const Color RED;
    /// Opaque green color.
    static const Color GREEN;
    /// Opaque green color.
    static const Color BLUE;
    /// Opaque black color.
    static const Color BLACK;
};

/// Color-time pair for color interpolation.
class ColorFade
{
public:
    /// Construct with default color and zero time.
    ColorFade() :
        time_(0.0f)
    {
    }
    
    /// Construct with a color and zero time.
    ColorFade(const Color& color) :
        color_(color),
        time_(0.0f)
    {
    }
    
    /// Construct from a color and time.
    ColorFade(const Color& color, float time) :
        color_(color),
        time_(time)
    {
    }
    
    /// Return interpolated value with another color-time pair, at the time specified.
    Color interpolate(const ColorFade& next, float time)
    {
        float timeInterval = next.time_ - time_;
        if (timeInterval > 0.0f)
        {
            float t = (time - time_) / timeInterval;
            return color_.Lerp(next.color_, t);
        }
        else
            return next.color_;
    }
    
    /// Color.
    Color color_;
    /// Time.
    float time_;
};
