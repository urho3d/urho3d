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

#include "../../Graphics/GraphicsDefs.h"
#include "../../Math/Color.h"

#include <d3d11.h>
#include <dxgi.h>
#include <SDL/SDL.h>

namespace Urho3D
{

/// %Graphics implementation. Holds API-specific objects.
class URHO3D_API GraphicsImpl
{
    friend class Graphics;

public:
    /// Construct.
    GraphicsImpl();

    /// Return Direct3D device.
    ID3D11Device* GetDevice() const { return device_; }

    /// Return Direct3D immediate device context.
    ID3D11DeviceContext* GetDeviceContext() const { return deviceContext_; }

    /// Return swapchain.
    IDXGISwapChain* GetSwapChain() const { return swapChain_; }

    /// Return window.
    SDL_Window* GetWindow() const { return window_; }

private:
    /// SDL window.
    SDL_Window* window_;
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
};

}
