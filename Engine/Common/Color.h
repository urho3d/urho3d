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

#ifndef COMMON_COLOR_H
#define COMMON_COLOR_H

#include "Vector3.h"

//! An RGBA color
class Color
{
public:
    //! Construct with default values (opaque white)
    Color() :
        mR(1.0f),
        mG(1.0f),
        mB(1.0f),
        mA(1.0f)
    {
    }
    
    //! Copy-construct from another color
    Color(const Color& color) :
        mR(color.mR),
        mG(color.mG),
        mB(color.mB),
        mA(color.mA)
    {
    }
    
    //! Construct from another color and modify the alpha
    Color(const Color& color, float a) :
        mR(color.mR),
        mG(color.mG),
        mB(color.mB),
        mA(a)
    {
    }
    
    //! Construct from RGB values and set alpha fully opaque
    Color(float r, float g, float b) :
        mR(r),
        mG(g),
        mB(b),
        mA(1.0f)
    {
    }
    
    //! Construct from RGBA values
    Color(float r, float g, float b, float a) :
        mR(r),
        mG(g),
        mB(b),
        mA(a)
    {
    }
    
    //! Test for equality with another color
    bool operator == (const Color& rhs) const
    {
        return ((mR == rhs.mR) && (mG == rhs.mG) && (mB == rhs.mB) && (mA == rhs.mA));
    }
    
    //! Test for inequality with another color
    bool operator != (const Color& rhs) const
    {
        return ((mR != rhs.mR) || (mG != rhs.mG) || (mB != rhs.mB) || (mA != rhs.mA));
    }
    
    //! Multiply with a scalar
    Color operator * (float rhs) const
    {
        return Color(mR * rhs, mG * rhs, mB * rhs, mA * rhs);
    }
    
    //! Add a color
    Color operator + (const Color& rhs) const
    {
        return Color(mR + rhs.mR, mG + rhs.mG, mB + rhs.mB, mA + rhs.mA);
    }
    
    //! Add-assign a color
    Color& operator += (const Color& rhs)
    {
        mR += rhs.mR;
        mG += rhs.mG;
        mB += rhs.mB;
        mA += rhs.mA;
        return *this;
    }
    
    //! Return float data
    const float* getData() const { return &mR; }
    //! Return RGB values as a Vector3
    Vector3 getRGB() const { return Vector3(mR, mG, mB); }
    
    //! Linear interpolation with another color
    Color lerp(const Color& rhs, float t) const
    {
        float invT = 1.0f - t;
        return Color(
            mR * invT + rhs.mR * t,
            mG * invT + rhs.mG * t,
            mB * invT + rhs.mB * t,
            mA * invT + rhs.mA * t
        );
    }
    
    //! Red value
    float mR;
    //! Green value
    float mG;
    //! Blue value
    float mB;
    //! Alpha value
    float mA;
};

//! A color-time pair for color interpolation
class ColorFade
{
public:
    //! Construct with default color and zero time
    ColorFade() :
        mTime(0.0f)
    {
    }
    
    //! Construct with a color and zero time
    ColorFade(const Color& color) :
        mColor(color),
        mTime(0.0f)
    {
    }
    
    //! Construct from a color and time
    ColorFade(const Color& color, float time) :
        mColor(color),
        mTime(time)
    {
    }
    
    //! Return interpolated value with another color-time pair, at the time specified
    Color interpolate(const ColorFade& next, float time)
    {
        float timeInterval = next.mTime - mTime;
        
        if (timeInterval > 0.0f)
        {
            float t = (time - mTime) / timeInterval;
            return mColor.lerp(next.mColor, t);
        }
        else
            return next.mColor;
    }
    
    //! Color
    Color mColor;
    //! Time
    float mTime;
};

//! Return color packed to a 32-bit integer
inline unsigned getD3DColor(const Color& color)
{
    unsigned r = (unsigned)(clamp(color.mR * 255.0f, 0.0f, 255.0f));
    unsigned g = (unsigned)(clamp(color.mG * 255.0f, 0.0f, 255.0f));
    unsigned b = (unsigned)(clamp(color.mB * 255.0f, 0.0f, 255.0f));
    unsigned a = (unsigned)(clamp(color.mA * 255.0f, 0.0f, 255.0f));
    
    return (((a) & 0xff) << 24) | (((r) & 0xff) << 16) | (((g) & 0xff) << 8) | ((b) & 0xff);
}

#endif // COMMON_COLOR_H
