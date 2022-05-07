// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../../GraphicsAPI/ConstantBuffer.h"
#include "../../GraphicsAPI/Direct3D11/D3D11ShaderProgram.h"
#include "../../GraphicsAPI/Direct3D11/D3D11VertexDeclaration.h"
#include "../../GraphicsAPI/GraphicsDefs.h"
#include "../../Math/Color.h"

#include <d3d11.h>
#include <dxgi.h>

namespace Urho3D
{

#define URHO3D_SAFE_RELEASE(p) if (p) { ((IUnknown*)p)->Release();  p = 0; }

#define URHO3D_LOGD3DERROR(msg, hr) URHO3D_LOGERRORF("%s (HRESULT %x)", msg, (unsigned)hr)

using ShaderProgramMap_D3D11 = HashMap<Pair<ShaderVariation*, ShaderVariation*>, SharedPtr<ShaderProgram_D3D11> >;
using VertexDeclarationMap_D3D11 = HashMap<unsigned long long, SharedPtr<VertexDeclaration_D3D11> >;
using ConstantBufferMap = HashMap<unsigned, SharedPtr<ConstantBuffer> >;

/// %Graphics implementation. Holds API-specific objects.
class URHO3D_API GraphicsImpl_D3D11
{
    friend class Graphics;

public:
    /// Construct.
    GraphicsImpl_D3D11();

    /// Return Direct3D device.
    ID3D11Device* GetDevice() const { return device_; }

    /// Return Direct3D immediate device context.
    ID3D11DeviceContext* GetDeviceContext() const { return deviceContext_; }

    /// Return swapchain.
    IDXGISwapChain* GetSwapChain() const { return swapChain_; }

    /// Return whether multisampling is supported for a given texture format and sample count.
    bool CheckMultiSampleSupport(DXGI_FORMAT format, unsigned sampleCount) const;

    /// Return multisample quality level for a given texture format and sample count. The sample count must be supported. On D3D feature level 10.1+, uses the standard level. Below that uses the best quality.
    unsigned GetMultiSampleQuality(DXGI_FORMAT format, unsigned sampleCount) const;

private:
    /// Graphics device.
    ID3D11Device* device_;
    /// Immediate device context.
    ID3D11DeviceContext* deviceContext_;
    /// Swap chain.
    IDXGISwapChain* swapChain_;
    /// Default (backbuffer) rendertarget view.
    ID3D11RenderTargetView* defaultRenderTargetView_;
    /// Default depth-stencil texture.
    ID3D11Texture2D* defaultDepthTexture_;
    /// Default depth-stencil view.
    ID3D11DepthStencilView* defaultDepthStencilView_;
    /// Current color rendertarget views.
    ID3D11RenderTargetView* renderTargetViews_[MAX_RENDERTARGETS];
    /// Current depth-stencil view.
    ID3D11DepthStencilView* depthStencilView_;
    /// Created blend state objects.
    HashMap<unsigned, ID3D11BlendState*> blendStates_;
    /// Created depth state objects.
    HashMap<unsigned, ID3D11DepthStencilState*> depthStates_;
    /// Created rasterizer state objects.
    HashMap<unsigned, ID3D11RasterizerState*> rasterizerStates_;
    /// Intermediate texture for multisampled screenshots and less than whole viewport multisampled resolve, created on demand.
    ID3D11Texture2D* resolveTexture_;
    /// Bound shader resource views.
    ID3D11ShaderResourceView* shaderResourceViews_[MAX_TEXTURE_UNITS];
    /// Bound sampler state objects.
    ID3D11SamplerState* samplers_[MAX_TEXTURE_UNITS];
    /// Bound vertex buffers.
    ID3D11Buffer* vertexBuffers_[MAX_VERTEX_STREAMS];
    /// Bound constant buffers.
    ID3D11Buffer* constantBuffers_[2][MAX_SHADER_PARAMETER_GROUPS];
    /// Vertex sizes per buffer.
    unsigned vertexSizes_[MAX_VERTEX_STREAMS];
    /// Vertex stream offsets per buffer.
    unsigned vertexOffsets_[MAX_VERTEX_STREAMS];
    /// Rendertargets dirty flag.
    bool renderTargetsDirty_;
    /// Textures dirty flag.
    bool texturesDirty_;
    /// Vertex declaration dirty flag.
    bool vertexDeclarationDirty_;
    /// Blend state dirty flag.
    bool blendStateDirty_;
    /// Depth state dirty flag.
    bool depthStateDirty_;
    /// Rasterizer state dirty flag.
    bool rasterizerStateDirty_;
    /// Scissor rect dirty flag.
    bool scissorRectDirty_;
    /// Stencil ref dirty flag.
    bool stencilRefDirty_;
    /// Hash of current blend state.
    unsigned blendStateHash_;
    /// Hash of current depth state.
    unsigned depthStateHash_;
    /// Hash of current rasterizer state.
    unsigned rasterizerStateHash_;
    /// First dirtied texture unit.
    unsigned firstDirtyTexture_;
    /// Last dirtied texture unit.
    unsigned lastDirtyTexture_;
    /// First dirtied vertex buffer.
    unsigned firstDirtyVB_;
    /// Last dirtied vertex buffer.
    unsigned lastDirtyVB_;
    /// Vertex declarations.
    VertexDeclarationMap_D3D11 vertexDeclarations_;
    /// Constant buffer search map.
    ConstantBufferMap allConstantBuffers_;
    /// Currently dirty constant buffers.
    PODVector<ConstantBuffer*> dirtyConstantBuffers_;
    /// Shader programs.
    ShaderProgramMap_D3D11 shaderPrograms_;
    /// Shader program in use.
    ShaderProgram_D3D11* shaderProgram_;
};

}
