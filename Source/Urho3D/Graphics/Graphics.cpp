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

#include "../Core/Profiler.h"
#include "../Graphics/AnimatedModel.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationController.h"
#include "../Graphics/Camera.h"
#include "../Graphics/CustomGeometry.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/DecalSet.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicsImpl.h"
#include "../Graphics/Material.h"
#include "../Graphics/Octree.h"
#include "../Graphics/ParticleEffect.h"
#include "../Graphics/ParticleEmitter.h"
#include "../Graphics/RibbonTrail.h"
#include "../Graphics/Shader.h"
#include "../Graphics/ShaderPrecache.h"
#include "../Graphics/Skybox.h"
#include "../Graphics/StaticModelGroup.h"
#include "../Graphics/Technique.h"
#include "../Graphics/Terrain.h"
#include "../Graphics/TerrainPatch.h"
#ifdef _WIN32
#include "../Graphics/Texture2D.h"
#endif
#include "../Graphics/Texture2DArray.h"
#include "../Graphics/Texture3D.h"
#include "../Graphics/TextureCube.h"
#include "../Graphics/Zone.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"

#include <SDL/SDL.h>

#include "../DebugNew.h"

namespace Urho3D
{

void Graphics::SetExternalWindow(void* window)
{
    if (!window_)
        externalWindow_ = window;
    else
        URHO3D_LOGERROR("Window already opened, can not set external window");
}

void Graphics::SetWindowTitle(const String& windowTitle)
{
    windowTitle_ = windowTitle;
    if (window_)
        SDL_SetWindowTitle(window_, windowTitle_.CString());
}

void Graphics::SetWindowIcon(Image* windowIcon)
{
    windowIcon_ = windowIcon;
    if (window_)
        CreateWindowIcon();
}

void Graphics::SetWindowPosition(const IntVector2& position)
{
    if (window_)
        SDL_SetWindowPosition(window_, position.x_, position.y_);
    else
        position_ = position; // Sets as initial position for OpenWindow()
}

void Graphics::SetWindowPosition(int x, int y)
{
    SetWindowPosition(IntVector2(x, y));
}

void Graphics::SetOrientations(const String& orientations)
{
    orientations_ = orientations.Trimmed();
    SDL_SetHint(SDL_HINT_ORIENTATIONS, orientations_.CString());
}

bool Graphics::ToggleFullscreen()
{
    return SetMode(width_, height_, !fullscreen_, borderless_, resizable_, highDPI_, vsync_, tripleBuffer_, multiSample_, monitor_, refreshRate_);
}

void Graphics::SetShaderParameter(StringHash param, const Variant& value)
{
    switch (value.GetType())
    {
    case VAR_BOOL:
        SetShaderParameter(param, value.GetBool());
        break;

    case VAR_INT:
        SetShaderParameter(param, value.GetInt());
        break;

    case VAR_FLOAT:
    case VAR_DOUBLE:
        SetShaderParameter(param, value.GetFloat());
        break;

    case VAR_VECTOR2:
        SetShaderParameter(param, value.GetVector2());
        break;

    case VAR_VECTOR3:
        SetShaderParameter(param, value.GetVector3());
        break;

    case VAR_VECTOR4:
        SetShaderParameter(param, value.GetVector4());
        break;

    case VAR_COLOR:
        SetShaderParameter(param, value.GetColor());
        break;

    case VAR_MATRIX3:
        SetShaderParameter(param, value.GetMatrix3());
        break;

    case VAR_MATRIX3X4:
        SetShaderParameter(param, value.GetMatrix3x4());
        break;

    case VAR_MATRIX4:
        SetShaderParameter(param, value.GetMatrix4());
        break;

    case VAR_BUFFER:
        {
            const PODVector<unsigned char>& buffer = value.GetBuffer();
            if (buffer.Size() >= sizeof(float))
                SetShaderParameter(param, reinterpret_cast<const float*>(&buffer[0]), buffer.Size() / sizeof(float));
        }
        break;

    default:
        // Unsupported parameter type, do nothing
        break;
    }
}

IntVector2 Graphics::GetWindowPosition() const
{
    if (window_)
    {
        IntVector2 position;
        SDL_GetWindowPosition(window_, &position.x_, &position.y_);
        return position;
    }
    return position_;
}

PODVector<IntVector3> Graphics::GetResolutions(int monitor) const
{
    PODVector<IntVector3> ret;
    // Emscripten is not able to return a valid list
#ifndef __EMSCRIPTEN__
    auto numModes = (unsigned)SDL_GetNumDisplayModes(monitor);

    for (unsigned i = 0; i < numModes; ++i)
    {
        SDL_DisplayMode mode;
        SDL_GetDisplayMode(monitor, i, &mode);
        int width = mode.w;
        int height = mode.h;
        int rate = mode.refresh_rate;

        // Store mode if unique
        bool unique = true;
        for (unsigned j = 0; j < ret.Size(); ++j)
        {
            if (ret[j].x_ == width && ret[j].y_ == height && ret[j].z_ == rate)
            {
                unique = false;
                break;
            }
        }

        if (unique)
            ret.Push(IntVector3(width, height, rate));
    }
#endif

    return ret;
}

IntVector2 Graphics::GetDesktopResolution(int monitor) const
{
#if !defined(__ANDROID__) && !defined(IOS) && !defined(TVOS)
    SDL_DisplayMode mode;
    SDL_GetDesktopDisplayMode(monitor, &mode);
    return IntVector2(mode.w, mode.h);
#else
    // SDL_GetDesktopDisplayMode() may not work correctly on mobile platforms. Rather return the window size
    return IntVector2(width_, height_);
#endif
}

int Graphics::GetMonitorCount() const
{
    return SDL_GetNumVideoDisplays();
}

int Graphics::GetCurrentMonitor() const
{
    return window_ ? SDL_GetWindowDisplayIndex(window_) : 0;
}

bool Graphics::GetMaximized() const
{
    return window_? static_cast<bool>(SDL_GetWindowFlags(window_) & SDL_WINDOW_MAXIMIZED) : false;
}

Vector3 Graphics::GetDisplayDPI(int monitor) const
{
    Vector3 result;
    SDL_GetDisplayDPI(monitor, &result.z_, &result.x_, &result.y_);
    return result;
}

void Graphics::Maximize()
{
    if (!window_)
        return;

    SDL_MaximizeWindow(window_);
}

void Graphics::Minimize()
{
    if (!window_)
        return;

    SDL_MinimizeWindow(window_);
}

void Graphics::Raise() const
{
    if (!window_)
        return;

    SDL_RaiseWindow(window_);
}

void Graphics::BeginDumpShaders(const String& fileName)
{
    shaderPrecache_ = new ShaderPrecache(context_, fileName);
}

void Graphics::EndDumpShaders()
{
    shaderPrecache_.Reset();
}

void Graphics::PrecacheShaders(Deserializer& source)
{
    URHO3D_PROFILE(PrecacheShaders);

    ShaderPrecache::LoadShaders(this, source);
}

void Graphics::SetShaderCacheDir(const String& path)
{
    String trimmedPath = path.Trimmed();
    if (trimmedPath.Length())
        shaderCacheDir_ = AddTrailingSlash(trimmedPath);
}

void Graphics::AddGPUObject(GPUObject* object)
{
    MutexLock lock(gpuObjectMutex_);

    gpuObjects_.Push(object);
}

void Graphics::RemoveGPUObject(GPUObject* object)
{
    MutexLock lock(gpuObjectMutex_);

    gpuObjects_.Remove(object);
}

void* Graphics::ReserveScratchBuffer(unsigned size)
{
    if (!size)
        return nullptr;

    if (size > maxScratchBufferRequest_)
        maxScratchBufferRequest_ = size;

    // First check for a free buffer that is large enough
    for (Vector<ScratchBuffer>::Iterator i = scratchBuffers_.Begin(); i != scratchBuffers_.End(); ++i)
    {
        if (!i->reserved_ && i->size_ >= size)
        {
            i->reserved_ = true;
            return i->data_.Get();
        }
    }

    // Then check if a free buffer can be resized
    for (Vector<ScratchBuffer>::Iterator i = scratchBuffers_.Begin(); i != scratchBuffers_.End(); ++i)
    {
        if (!i->reserved_)
        {
            i->data_ = new unsigned char[size];
            i->size_ = size;
            i->reserved_ = true;

            URHO3D_LOGDEBUG("Resized scratch buffer to size " + String(size));

            return i->data_.Get();
        }
    }

    // Finally allocate a new buffer
    ScratchBuffer newBuffer;
    newBuffer.data_ = new unsigned char[size];
    newBuffer.size_ = size;
    newBuffer.reserved_ = true;
    scratchBuffers_.Push(newBuffer);

    URHO3D_LOGDEBUG("Allocated scratch buffer with size " + String(size));

    return newBuffer.data_.Get();
}

void Graphics::FreeScratchBuffer(void* buffer)
{
    if (!buffer)
        return;

    for (Vector<ScratchBuffer>::Iterator i = scratchBuffers_.Begin(); i != scratchBuffers_.End(); ++i)
    {
        if (i->reserved_ && i->data_.Get() == buffer)
        {
            i->reserved_ = false;
            return;
        }
    }

    URHO3D_LOGWARNING("Reserved scratch buffer " + ToStringHex((unsigned)(size_t)buffer) + " not found");
}

void Graphics::CleanupScratchBuffers()
{
    for (Vector<ScratchBuffer>::Iterator i = scratchBuffers_.Begin(); i != scratchBuffers_.End(); ++i)
    {
        if (!i->reserved_ && i->size_ > maxScratchBufferRequest_ * 2 && i->size_ >= 1024 * 1024)
        {
            i->data_ = maxScratchBufferRequest_ > 0 ? (new unsigned char[maxScratchBufferRequest_]) : nullptr;
            i->size_ = maxScratchBufferRequest_;

            URHO3D_LOGDEBUG("Resized scratch buffer to size " + String(maxScratchBufferRequest_));
        }
    }

    maxScratchBufferRequest_ = 0;
}

void Graphics::CreateWindowIcon()
{
    if (windowIcon_)
    {
        SDL_Surface* surface = windowIcon_->GetSDLSurface();
        if (surface)
        {
            SDL_SetWindowIcon(window_, surface);
            SDL_FreeSurface(surface);
        }
    }
}

void RegisterGraphicsLibrary(Context* context)
{
    Animation::RegisterObject(context);
    Material::RegisterObject(context);
    Model::RegisterObject(context);
    Shader::RegisterObject(context);
    Technique::RegisterObject(context);
    Texture2D::RegisterObject(context);
    Texture2DArray::RegisterObject(context);
    Texture3D::RegisterObject(context);
    TextureCube::RegisterObject(context);
    Camera::RegisterObject(context);
    Drawable::RegisterObject(context);
    Light::RegisterObject(context);
    StaticModel::RegisterObject(context);
    StaticModelGroup::RegisterObject(context);
    Skybox::RegisterObject(context);
    AnimatedModel::RegisterObject(context);
    AnimationController::RegisterObject(context);
    BillboardSet::RegisterObject(context);
    ParticleEffect::RegisterObject(context);
    ParticleEmitter::RegisterObject(context);
    RibbonTrail::RegisterObject(context);
    CustomGeometry::RegisterObject(context);
    DecalSet::RegisterObject(context);
    Terrain::RegisterObject(context);
    TerrainPatch::RegisterObject(context);
    DebugRenderer::RegisterObject(context);
    Octree::RegisterObject(context);
    Zone::RegisterObject(context);
}

}
