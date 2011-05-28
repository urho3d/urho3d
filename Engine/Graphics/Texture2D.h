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

#include "RenderSurface.h"
#include "SharedPtr.h"
#include "Texture.h"

class Image;

/// 2D texture resource
class Texture2D : public Texture
{
    OBJECT(Texture2D);
    
public:
    /// Construct
    Texture2D(Context* context);
    /// Destruct
    virtual ~Texture2D();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Load resource. Return true if successful
    virtual bool Load(Deserializer& source);
    /// Release default pool resources
    virtual void OnDeviceLost();
    /// Recreate default pool resources
    virtual void OnDeviceReset();
    /// Release texture
    virtual void Release();
    
    /// Set size, format and usage. Zero size will follow application window size. Return true if successful
    bool SetSize(int width, int height, unsigned format, TextureUsage usage = TEXTURE_STATIC);
    /// Load from an image. Return true if successful
    bool Load(SharedPtr<Image> image);
    /// Lock a rectangular area from a mipmap level. A null rectangle locks the entire texture. Return true if successful
    bool Lock(unsigned level, IntRect* rect, LockedRect& lockedRect);
    /// Unlock texture
    void Unlock();
    
    /// Return render surface
    RenderSurface* GetRenderSurface() const { return renderSurface_; }
    
private:
    /// Create texture
    bool Create();
    
    /// Render surface
    SharedPtr<RenderSurface> renderSurface_;
    /// Currently locked mipmap level
    int lockedLevel_;
    /// Follow window size flag
    bool followWindowSize_;
};
