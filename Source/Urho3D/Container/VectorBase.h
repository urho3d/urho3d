// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#ifdef URHO3D_IS_BUILDING
#include "Urho3D.h"
#else
#include <Urho3D/Urho3D.h>
#endif

#include "../Base/Iter.h"
#include "../Base/PrimitiveTypes.h"
#include "../Container/Swap.h"

namespace Urho3D
{

/// %Vector base class.
/** Note that to prevent extra memory use due to vtable pointer, %VectorBase intentionally does not declare a virtual destructor
    and therefore %VectorBase pointers should never be used.
  */
class URHO3D_API VectorBase
{
public:
    /// Construct.
    VectorBase() noexcept :
        size_(0),
        capacity_(0),
        buffer_(nullptr)
    {
    }

    /// Swap with another vector.
    void Swap(VectorBase& rhs)
    {
        Urho3D::Swap(size_, rhs.size_);
        Urho3D::Swap(capacity_, rhs.capacity_);
        Urho3D::Swap(buffer_, rhs.buffer_);
    }

protected:
    static unsigned char* AllocateBuffer(unsigned size);

    /// Size of vector.
    u32 size_;
    /// Buffer capacity.
    u32 capacity_;
    /// Buffer.
    u8* buffer_;
};

}
