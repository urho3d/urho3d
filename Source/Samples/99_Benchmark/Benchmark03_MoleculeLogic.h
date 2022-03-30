//
// Copyright (c) 2008-2022 the Urho3D project.
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

#include <Urho3D/Scene/LogicComponent.h>

namespace U3D = Urho3D;

class Benchmark03_MoleculeLogic : public U3D::LogicComponent
{
public:
    URHO3D_OBJECT(Benchmark03_MoleculeLogic, LogicComponent);

private:
    i32 moleculeType_;
    U3D::Vector2 velocity_;
    U3D::Vector2 force_;

public:
    explicit Benchmark03_MoleculeLogic(U3D::Context* context);

    void SetParameters(i32 moleculeType);

    i32 GetMoleculeType() const { return moleculeType_; }

    // Update the velocity of this molecule
    void Update(float timeStep) override;

    // Move this molecule only after updating the velocities of all molecules 
    void PostUpdate(float timeStep) override;
};
