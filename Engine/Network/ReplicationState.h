//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#include "Variant.h"

/// Last sent state of a component for network replication.
struct ComponentReplicationState
{
    /// Component type.
    ShortStringHash type_;
    /// Attribute values.
    Vector<Variant> attributes_;
    /// Update frame number.
    unsigned frameNumber_;
};

/// Last sent state of a node for network replication.
struct NodeReplicationState
{
    /// Attribute values.
    Vector<Variant> attributes_;
    /// User variables.
    VariantMap vars_;
    /// Components by ID.
    HashMap<unsigned, ComponentReplicationState> components_;
    /// Interest management priority accumulator.
    float priorityAcc_;
    /// Update frame number.
    unsigned frameNumber_;
};
