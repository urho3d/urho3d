//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Scene/Component.h"

namespace Urho3D
{

/// Component which tags geometry for inclusion in the navigation mesh. Optionally auto-includes geometry from child nodes.
class URHO3D_API Navigable : public Component
{
    URHO3D_OBJECT(Navigable, Component);

public:
    /// Construct.
    Navigable(Context* context);
    /// Destruct.
    virtual ~Navigable();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Set whether geometry is automatically collected from child nodes. Default true.
    void SetRecursive(bool enable);

    /// Return whether geometry is automatically collected from child nodes.
    bool IsRecursive() const { return recursive_; }

private:
    /// Recursive flag.
    bool recursive_;
};

}
