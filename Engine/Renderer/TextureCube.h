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

#ifndef RENDERER_TEXTURECUBE_H
#define RENDERER_TEXTURECUBE_H

#include "RenderSurface.h"
#include "SharedPtr.h"
#include "Texture.h"

class Deserializer;
class Image;

//! Cube texture resource
class TextureCube : public Texture
{
    DEFINE_TYPE(TextureCube);
    
public:
    //! Construct with renderer subsystem pointer, texture usage type and name
    TextureCube(Renderer* renderer, TextureUsage usage, const std::string& name = std::string());
    //! Destruct
    virtual ~TextureCube();
    
    //! Load resource. Throw exception on error
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    //! Release default pool resources
    virtual void onDeviceLost();
    //! Recreate default pool resources
    virtual void onDeviceReset();
    
    //! Set size and format
    void setSize(int size, unsigned format);
    //! Load one face from a stream
    void load(CubeMapFace face, Deserializer& source);
    //! Load one face from an image
    void load(CubeMapFace face, SharedPtr<Image> image);
    //! Lock a rectangular area from one face and mipmap level. Throw an exception if fails
    void lock(CubeMapFace face, unsigned level, void* rect, void* lockedRect);
    //! Unlock texture
    void unlock();
    
    //! Return render surface for one face
    RenderSurface* getRenderSurface(CubeMapFace face) const { return mRenderSurfaces[face]; }
    
private:
    //! Create texture
    void create();
    //! Release texture
    void release();
    
    //! Render surfaces
    SharedPtr<RenderSurface> mRenderSurfaces[MAX_CUBEMAP_FACES];
    //! Memory use per face
    unsigned mFaceMemoryUse[MAX_CUBEMAP_FACES];
    //! Currently locked mipmap level
    int mLockedLevel;
    //! Currently locked face
    CubeMapFace mLockedFace;
};

#endif // RENDERER_TEXTURECUBE
