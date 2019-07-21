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

#ifndef CAT_REGION_ALLOCATOR_HPP
#define CAT_REGION_ALLOCATOR_HPP

#include <cat/Singleton.hpp>
#include <memory>
#include <xstring>
#include <sstream>

namespace cat {


// A region-based allocator that is lock-free, supporting
// a range of allocation block sizes that are pre-allocated
// in a pre-determined way, tuned to the application.
class RegionAllocator : public Singleton<RegionAllocator>
{
    CAT_SINGLETON(RegionAllocator);

protected:
    struct RegionInfoHead
    {
        u32 next_bitmap_entry;
    };

    struct RegionInfo : public RegionInfoHead
    {
        volatile u32 bitmap[1];
    };

    // 64, 128, 256, 512, 1024, 2048 only
    static const u32 REGION_COUNT = 6;
    static const u32 BLOCK_SIZE[REGION_COUNT];

    u32 bytes_overall;
    u32 blocks_per_region[REGION_COUNT];
    u32 bitmap_dwords[REGION_COUNT];
    u8 *regions[REGION_COUNT];
    RegionInfo *region_info[REGION_COUNT];

    //u32 errors;

public:
    bool Valid();

    void Shutdown();

public:
    void *Acquire(u32 bytes);
    void *Resize(void *ptr, u32 bytes);
    void Release(void *ptr);

    template<class T>
    CAT_INLINE void Delete(T *ptr)
    {
        ptr->~T();
        Release(ptr);
    }

	// Acquires a buffer from the allocator that is the size of the type.
	// It further allocates a number of extra bytes beyond the end of the buffer.
	// Release the buffer with:
	//   RegionAllocator::ii->Release(ptr);
	template<class T> T *AcquireBuffer(u32 extra_bytes = 0)
	{
		return reinterpret_cast<T*>( Acquire(sizeof(T) + extra_bytes) );
	}
};

// Use STLRegionAllocator in place of the standard STL allocator
// to make use of the RegionAllocator in STL types.  Some common
// usage typedefs follow this class definition below.
template<typename T>
class STLRegionAllocator
{
public:
    typedef size_t size_type;
    typedef size_t difference_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef T value_type;

    template<typename S>
    struct rebind
    {
        typedef STLRegionAllocator<S> other;
    };

    pointer address(reference X) const
    {
        return &X;
    }

    const_pointer address(const_reference X) const
    {
        return &X;
    }

    STLRegionAllocator() throw ()
    {
    }

    template<typename S>
    STLRegionAllocator(const STLRegionAllocator<S> &cp) throw ()
    {
    }

    template<typename S>
    STLRegionAllocator<T> &operator=(const STLRegionAllocator<S> &cp) throw ()
    {
        return *this;
    }

    pointer allocate(size_type Count, const void *Hint = 0)
    {
        return (pointer)RegionAllocator::ii->Acquire((u32)Count * sizeof(T));
    }

    void deallocate(pointer Ptr, size_type Count)
    {
        RegionAllocator::ii->Release(Ptr);
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
	bool operator==(STLRegionAllocator <S> const &) const throw()
	{
		return true;
	}

	template<typename S>
	bool operator!=(STLRegionAllocator <S> const &) const throw()
	{
		return false;
	}
};

// Common usage typedefs for using RegionAllocator as the STL allocator
typedef std::basic_ostringstream<char, std::char_traits<char>, STLRegionAllocator<char> > region_ostringstream;
typedef std::basic_string<char, std::char_traits<char>, STLRegionAllocator<char> > region_string;


} // namespace cat

// Provide placement new constructor and delete pair to allow for
// an easy syntax to create objects from the RegionAllocator:
//   T *a = new (RegionAllocator::ii) T();
// The object can be freed with:
//   RegionAllocator::ii->Delete(a);
// Which insures that the destructor is called before freeing memory
inline void *operator new(size_t bytes, cat::RegionAllocator *allocator)
{
    return allocator->Acquire((cat::u32)bytes);
}

inline void operator delete(void *ptr, cat::RegionAllocator *allocator)
{
    allocator->Release(ptr);
}


#endif // CAT_REGION_ALLOCATOR_HPP
