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

#ifndef RENDERER_TEXTURE2D_H
#define RENDERER_TEXTURE2D_H

#include "RenderSurface.h"
#include "SharedPtr.h"
#include "Texture.h"

class Image;

//! 2D texture resource
class Texture2D : public Texture
{
    DEFINE_TYPE(Texture2D);
    
public:
    //! Construct with renderer subsystem pointer, texture usage type and name
    Texture2D(Renderer*, TextureUsage usage, const std::string& name = std::string());
    //! Destruct
    virtual ~Texture2D();
    
    //! Load resource. Throw exception on error
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    //! Release default pool resources
    virtual void onDeviceLost();
    //! Recreate default pool resources
    virtual void onDeviceReset();
    
    //! Set size and format. Zero size will follow application window size
    void setSize(int width, int height, unsigned format);
    //! Load from an image
    void load(SharedPtr<Image> image);
    //! Lock a rectangular area from a mipmap level. Throw an exception if fails
    void lock(unsigned level, void* rect, void* lockedRect);
    //! Unlock texture
    void unlock();
    
    //! Return render surface
    RenderSurface* getRenderSurface() const { return mRenderSurface; }
    
private:
    //! Create texture
    void create();
    //! Release texture
    void release();
    
    //! Render surface
    SharedPtr<RenderSurface> mRenderSurface;
    //! Currently locked mipmap level
    int mLockedLevel;
    //! Follow window size flag
    bool mFollowWindowSize;
};

#endif // RENDERER_TEXTURE2D
