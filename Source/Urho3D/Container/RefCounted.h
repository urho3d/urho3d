//
// Copyright (c) 2008-2019 the Urho3D project.
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

#ifdef URHO3D_IS_BUILDING
#include "Urho3D.h"
#else
#include <Urho3D/Urho3D.h>
#endif

#include "../Container/Str.h"
#include "../Math/StringHash.h"

namespace Urho3D
{

using ClassID = const void*;
/// Macro to be included in RefCounted derived classes for efficient RTTI
#define URHO3D_REFCOUNTED(typeName) \
    public: \
        virtual Urho3D::StringHash GetType() const override { return GetTypeStatic(); } \
        static Urho3D::StringHash GetTypeStatic() {static const Urho3D::StringHash _type(#typeName); return _type; } \
        virtual const Urho3D::String& GetTypeName() const override { return GetTypeNameStatic(); } \
        static const Urho3D::String& GetTypeNameStatic() { static const Urho3D::String _typeName(#typeName); return _typeName; } \
        virtual Urho3D::ClassID GetClassID() const override { return GetClassIDStatic(); } \
        static Urho3D::ClassID GetClassIDStatic() { static const int typeID = 0; return (Urho3D::ClassID) &typeID; }

/// Reference count structure.
struct RefCount
{
    /// Construct.
    RefCount() :
        refs_(0),
        weakRefs_(0)
    {
    }

    /// Destruct.
    ~RefCount()
    {
        // Set reference counts below zero to fire asserts if this object is still accessed
        refs_ = -1;
        weakRefs_ = -1;
    }

    /// Reference count. If below zero, the object has been destroyed.
    int refs_;
    /// Weak reference count.
    int weakRefs_;
};

/// Base class for intrusively reference-counted objects. These are noncopyable and non-assignable.
class URHO3D_API RefCounted
{
public:
    /// Construct. Allocate the reference count structure and set an initial self weak reference.
    RefCounted();
    /// Destruct. Mark as expired and also delete the reference count structure if no outside weak references exist.
    virtual ~RefCounted();

    /// Prevent copy construction.
    RefCounted(const RefCounted& rhs) = delete;
    /// Prevent assignment.
    RefCounted& operator =(const RefCounted& rhs) = delete;
    /// Adjust RefCounted subobject is Object. Always return false.
    virtual bool IsObject() const { return false; }
    /// Get type name as Object
    virtual const String& GetTypeName() const = 0;
    /// Get type hashcode as Object
    virtual StringHash GetType() const = 0;
    /// Get the unique id of the class
    virtual ClassID GetClassID() const { return GetClassIDStatic(); };
    /// Get the unique id of the class
    static ClassID GetClassIDStatic() { static const int typeID = 0; return (ClassID) &typeID; }

    /// Increment reference count. Can also be called outside of a SharedPtr for traditional reference counting.
    void AddRef();
    /// Decrement reference count and delete self if no more references. Can also be called outside of a SharedPtr for traditional reference counting.
    void ReleaseRef();
    /// Return reference count.
    int Refs() const;
    /// Return weak reference count.
    int WeakRefs() const;

    /// Return pointer to the reference count structure.
    RefCount* RefCountPtr() { return refCount_; }

private:
    /// Pointer to the reference count structure.
    RefCount* refCount_;
};

}
