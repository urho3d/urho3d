// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../../Precompiled.h"

#include "../../Graphics/Graphics.h"
#include "../../GraphicsAPI/ConstantBuffer.h"
#include "../../IO/Log.h"

#include "../../DebugNew.h"

namespace Urho3D
{

void ConstantBuffer::OnDeviceReset_D3D9()
{
}

void ConstantBuffer::Release_D3D9()
{
}

bool ConstantBuffer::SetSize_D3D9(unsigned size)
{
    URHO3D_LOGERROR("Constant buffers are not supported on Direct3D9");
    return false;
}

void ConstantBuffer::Apply_D3D9()
{
}

}
