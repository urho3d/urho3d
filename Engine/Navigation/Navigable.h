//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Component.h"

namespace Urho3D
{

/// Navigable geometry properties component. Any geometry components from this node and child nodes will be included in the navigation mesh. Physics geometry is preferred to drawable geometry, if available.
class Navigable : public Component
{
    OBJECT(Navigable);
    
public:
    /// Construct.
    Navigable(Context* context);
    /// Destruct.
    virtual ~Navigable();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Set navigation geometry flags, meaning is user-defined.
    void SetFlags(unsigned flags);
    
    /// Return navigation geometry flags.
    unsigned GetFlags() const { return flags_; }
    
private:
    /// Navigation geometry flags.
    unsigned flags_;
};

}
