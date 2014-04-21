//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "ValueAnimationInfo.h"

namespace Urho3D
{

class Material;

/// Material shader parameter animation instance.
class URHO3D_API MaterialShaderParameterAnimationInstance : public ValueAnimationInfo
{
public:
    /// Construct.
    MaterialShaderParameterAnimationInstance(Material* material, const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed);
    /// Copy construct.
    MaterialShaderParameterAnimationInstance(const MaterialShaderParameterAnimationInstance& other);
    /// Destruct.
    ~MaterialShaderParameterAnimationInstance();

    /// Update. Return true when the animation is finished.
    bool Update(float timeStep);

    /// Return material.
    Material* GetMaterial() const { return material_; }
    /// Return shader parameter name.
    const String& GetName() const { return name_; }
    /// Return current time.
    float GetCurrentTime() const { return currentTime_; }

private:
    /// Material.
    WeakPtr<Material> material_;
    /// Shader parameter name.
    String name_;
    /// Current time.
    float currentTime_;
    /// Last scaled time.
    float lastScaledTime_;
};

}
