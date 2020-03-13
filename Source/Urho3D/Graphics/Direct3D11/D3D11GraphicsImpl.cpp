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

#include "../../Precompiled.h"

#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"

#include "../../DebugNew.h"

namespace Urho3D
{

GraphicsImpl::GraphicsImpl() :
    device_(nullptr),
    deviceContext_(nullptr),
    swapChain_(nullptr),
    defaultRenderTargetView_(nullptr),
    defaultDepthTexture_(nullptr),
    defaultDepthStencilView_(nullptr),
    depthStencilView_(nullptr),
    resolveTexture_(nullptr),
    shaderProgram_(nullptr)
{
    for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
        renderTargetViews_[i] = nullptr;

    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
    {
        shaderResourceViews_[i] = nullptr;
        samplers_[i] = nullptr;
    }

    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        vertexBuffers_[i] = nullptr;
        vertexSizes_[i] = 0;
        vertexOffsets_[i] = 0;
    }

    for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
    {
        constantBuffers_[VS][i] = nullptr;
        constantBuffers_[PS][i] = nullptr;
    }
}

bool GraphicsImpl::CheckMultiSampleSupport(DXGI_FORMAT format, unsigned sampleCount) const
{
    if (sampleCount < 2)
        return true; // Not multisampled

    UINT numLevels = 0;
    if (FAILED(device_->CheckMultisampleQualityLevels(format, sampleCount, &numLevels)))
        return false;
    else
        return numLevels > 0;
}

unsigned GraphicsImpl::GetMultiSampleQuality(DXGI_FORMAT format, unsigned sampleCount) const
{
    if (sampleCount < 2)
        return 0; // Not multisampled, should use quality 0

    if (device_->GetFeatureLevel() >= D3D_FEATURE_LEVEL_10_1)
        return 0xffffffff; // D3D10.1+ standard level

    UINT numLevels = 0;
    if (FAILED(device_->CheckMultisampleQualityLevels(format, sampleCount, &numLevels)) || !numLevels)
        return 0; // Errored or sample count not supported
    else
        return numLevels - 1; // D3D10.0 and below: use the best quality
}

}
