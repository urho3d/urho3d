/*
	Copyright (c) 2009-2010 Christopher A. Taylor.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	* Neither the name of LibCat nor the names of its contributors may be used
	  to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CAT_ALIGNED_ALLOC_HPP
#define CAT_ALIGNED_ALLOC_HPP

#include <cat/Platform.hpp>

#include <cstddef> // size_t
#include <vector> // std::_Construct and std::_Destroy


namespace cat {


// Small to medium -size aligned heap allocator
class Aligned
{
public:
	CAT_INLINE Aligned() {}

	// Acquires memory aligned to a CPU cache-line byte boundary from the heap
    static void *Acquire(u32 bytes);

	// Resizes an aligned pointer
	static void *Resize(void *ptr, u32 bytes);

    // Release an aligned pointer
    static void Release(void *ptr);

    template<class T>
    static inline void Delete(T *ptr)
    {
        ptr->~T();
        Release(ptr);
    }

	static Aligned ii;
};

#if 0
// Use STLAlignedAllocator in place of the standard STL allocator
// to make use of the Aligned in STL types.
template<typename T>
class STLAlignedAllocator
{
public:
	typedef std::size_t size_type;
	typedef std::size_t difference_type;
	typedef T *pointer;
	typedef const T *const_pointer;
	typedef T &reference;
	typedef const T &const_reference;
	typedef T value_type;

	template<typename S>
	struct rebind
	{
		typedef STLAlignedAllocator<S> other;
	};

	pointer address(reference X) const
	{
		return &X;
	}

	const_pointer address(const_reference X) const
	{
		return &X;
	}

	STLAlignedAllocator() throw ()
	{
	}

	template<typename S>
	STLAlignedAllocator(const STLAlignedAllocator<S> &cp) throw ()
	{
	}

	template<typename S>
	STLAlignedAllocator<T> &operator=(const STLAlignedAllocator<S> &cp) throw ()
	{
		return *this;
	}

	pointer allocate(size_type Count, const void *Hint = 0)
	{
		return (pointer)Aligned::Acquire((u32)Count * sizeof(T));
	}

	void deallocate(pointer Ptr, size_type Count)
	{
		Aligned::Release(Ptr);
	}

	void construct(pointer Ptr, const T &Val)
	{
		std::_Construct(Ptr, Val);
	}

	void destroy(pointer Ptr)
	{
		std::_Destroy(Ptr);
	}

	size_type max_size() const
	{
		return 0x00FFFFFF;
	}

	template<typename S>
	bool operator==(STLAlignedAllocator <S> const &) const throw()
	{
		return true;
	}

	template<typename S>
	bool operator!=(STLAlignedAllocator <S> const &) const throw()
	{
		return false;
	}
};
#endif


// Large-size aligned heap allocator
class LargeAligned
{
public:
	// Acquires memory aligned to a CPU cache-line byte boundary from the heap
    static void *Acquire(u32 bytes);

    // Release an aligned pointer
    static void Release(void *ptr);
};

#if 0
// Use STLAlignedAllocator in place of the standard STL allocator
// to make use of the Aligned in STL types.
template<typename T>
class STLLargeAlignedAllocator
{
public:
	typedef std::size_t size_type;
	typedef std::size_t difference_type;
	typedef T *pointer;
	typedef const T *const_pointer;
	typedef T &reference;
	typedef const T &const_reference;
	typedef T value_type;

	template<typename S>
	struct rebind
	{
		typedef STLLargeAlignedAllocator<S> other;
	};

	pointer address(reference X) const
	{
		return &X;
	}

	const_pointer address(const_reference X) const
	{
		return &X;
	}

	STLLargeAlignedAllocator() throw ()
	{
	}

	template<typename S>
	STLLargeAlignedAllocator(const STLLargeAlignedAllocator<S> &cp) throw ()
	{
	}

	template<typename S>
	STLLargeAlignedAllocator<T> &operator=(const STLLargeAlignedAllocator<S> &cp) throw ()
	{
		return *this;
	}

	pointer allocate(size_type Count, const void *Hint = 0)
	{
		return (pointer)LargeAligned::Acquire((u32)Count * sizeof(T));
	}

	void deallocate(pointer Ptr, size_type Count)
	{
		LargeAligned::Release(Ptr);
	}

	void construct(pointer Ptr, const T &Val)
	{
		std::_Construct(Ptr, Val);
	}

	void destroy(pointer Ptr)
	{
		std::_Destroy(Ptr);
	}

	size_type max_size() const
	{
		return 0x00FFFFFF;
	}

	template<typename S>
	bool operator==(STLLargeAlignedAllocator <S> const &) const throw()
	{
		return true;
	}

	template<typename S>
	bool operator!=(STLLargeAlignedAllocator <S> const &) const throw()
	{
		return false;
	}
};
#endif


u32 GetCacheLineBytes();


} // namespace cat

// Provide placement new constructor and delete pair to allow for
// an easy syntax to create objects from the RegionAllocator:
//   T *a = new (Aligned()) T();
// The object can be freed with:
//   Aligned::Delete(a);
// Which insures that the destructor is called before freeing memory
CAT_INLINE void *operator new[](std::size_t bytes, cat::Aligned &) throw()
{
	return cat::Aligned::Acquire((int)bytes);
}

// Placement "delete": Does not call destructor
CAT_INLINE void operator delete(void *ptr, cat::Aligned &) throw()
{
	cat::Aligned::Release(ptr);
}

#endif // CAT_ENDIAN_NEUTRAL_HPP
