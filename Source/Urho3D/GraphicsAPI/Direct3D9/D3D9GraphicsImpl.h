// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../../GraphicsAPI/Direct3D9/D3D9ShaderProgram.h"
#include "../../GraphicsAPI/Direct3D9/D3D9VertexDeclaration.h"
#include "../../Math/Color.h"

#include <d3d9.h>

namespace Urho3D
{

#define URHO3D_SAFE_RELEASE(p) if (p) { ((IUnknown*)p)->Release();  p = 0; }

#define URHO3D_LOGD3DERROR(msg, hr) URHO3D_LOGERRORF("%s (HRESULT %x)", msg, (unsigned)hr)

using ShaderProgramMap_D3D9 = HashMap<Pair<ShaderVariation*, ShaderVariation*>, SharedPtr<ShaderProgram_D3D9> >;
using VertexDeclarationMap_D3D9 = HashMap<unsigned long long, SharedPtr<VertexDeclaration_D3D9> >;

/// %Graphics implementation. Holds API-specific objects.
class URHO3D_API GraphicsImpl_D3D9
{
    friend class Graphics;

public:
    /// Construct.
    GraphicsImpl_D3D9();

    /// Return Direct3D device.
    IDirect3DDevice9* GetDevice() const { return device_; }

    /// Return device capabilities.
    const D3DCAPS9& GetDeviceCaps() const { return deviceCaps_; }

    /// Return adapter identifier.
    const D3DADAPTER_IDENTIFIER9& GetAdapterIdentifier() const { return adapterIdentifier_; }

    /// Return whether a texture format and usage is supported.
    bool CheckFormatSupport(D3DFORMAT format, DWORD usage, D3DRESOURCETYPE type);

    /// Return whether a multisample level is supported.
    bool CheckMultiSampleSupport(D3DFORMAT format, int level);

private:
    /// Direct3D interface.
    IDirect3D9* interface_;
    /// Direct3D device.
    IDirect3DDevice9* device_;
    /// Default color surface.
    IDirect3DSurface9* defaultColorSurface_;
    /// Default depth-stencil surface.
    IDirect3DSurface9* defaultDepthStencilSurface_;
    /// Frame query for flushing the GPU command queue.
    IDirect3DQuery9* frameQuery_;
    /// Adapter number.
    DWORD adapter_;
    /// Device type.
    D3DDEVTYPE deviceType_;
    /// Device capabilities.
    D3DCAPS9 deviceCaps_;
    /// Adapter identifier.
    D3DADAPTER_IDENTIFIER9 adapterIdentifier_;
    /// Direct3D presentation parameters.
    D3DPRESENT_PARAMETERS presentParams_;
    /// Texture min filter modes in use.
    D3DTEXTUREFILTERTYPE minFilters_[MAX_TEXTURE_UNITS];
    /// Texture mag filter modes in use.
    D3DTEXTUREFILTERTYPE magFilters_[MAX_TEXTURE_UNITS];
    /// Texture mip filter modes in use.
    D3DTEXTUREFILTERTYPE mipFilters_[MAX_TEXTURE_UNITS];
    /// Texture U coordinate addressing modes in use.
    D3DTEXTUREADDRESS uAddressModes_[MAX_TEXTURE_UNITS];
    /// Texture V coordinate addressing modes in use.
    D3DTEXTUREADDRESS vAddressModes_[MAX_TEXTURE_UNITS];
    /// Texture W coordinate addressing modes in use.
    D3DTEXTUREADDRESS wAddressModes_[MAX_TEXTURE_UNITS];
    /// Texture anisotropy setting in use.
    unsigned maxAnisotropy_[MAX_TEXTURE_UNITS];
    /// Texture border colors in use.
    Color borderColors_[MAX_TEXTURE_UNITS];
    /// Device lost flag.
    bool deviceLost_;
    /// Frame query issued flag.
    bool queryIssued_;
    /// sRGB mode in use.
    bool sRGBModes_[MAX_TEXTURE_UNITS];
    /// sRGB write flag.
    bool sRGBWrite_;
    /// Color surfaces in use.
    IDirect3DSurface9* colorSurfaces_[MAX_RENDERTARGETS];
    /// Depth-stencil surface in use.
    IDirect3DSurface9* depthStencilSurface_;
    /// Blending enabled flag.
    DWORD blendEnable_;
    /// Source blend mode.
    D3DBLEND srcBlend_;
    /// Destination blend mode.
    D3DBLEND destBlend_;
    /// Blend operation.
    D3DBLENDOP blendOp_;
    /// Vertex declarations.
    VertexDeclarationMap_D3D9 vertexDeclarations_;
    /// Stream frequencies by vertex buffer.
    unsigned streamFrequencies_[MAX_VERTEX_STREAMS];
    /// Stream offsets by vertex buffer.
    unsigned streamOffsets_[MAX_VERTEX_STREAMS];
    /// Vertex declaration in use.
    VertexDeclaration_D3D9* vertexDeclaration_;
    /// Shader programs.
    ShaderProgramMap_D3D9 shaderPrograms_;
    /// Shader program in use.
    ShaderProgram_D3D9* shaderProgram_;

};

}
