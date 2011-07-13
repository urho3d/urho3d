/* Copyright 2010 Jukka Jylänki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
#pragma once

/** @file SharedPtr.h
	@brief SharedPtr, intrusive reference counting for multiple pointer owners. */

#include <cstdlib>
#include <cassert>

/// Smart pointer for dynamic single object allocations on the heap.
#define Ptr(type) kNet::SharedPtr< type > 

namespace kNet
{

/// Objects that require reference count tracking derive publicly from this.
/// \note The dtor of RefCountable is not virtual. NEVER manage pointers to RefCountables
///       and never delete a pointer to a RefCountable.
class RefCountable
{
public:
	RefCountable()
	:refCount(0)
	{
	}

	~RefCountable()
	{
		refCount = -100000; // Mark the refCount to an arbitrary negative value so that any increments or decrements will catch an assertion failure.
	}

	void AddRef()
	{ 
		assert(refCount >= 0); 
		++refCount;
	}

	void DecRef()
	{ 
		assert(refCount > 0); 
		--refCount; 
	}

	int RefCount() const
	{ 
		return refCount;
	}

private:
	int refCount;
};

/** @brief SharedPtr is an intrusive refcount-tracked single-object lifetime-manager.

SharedPtr wraps raw pointers to objects and manages reference 
counting on the number of users on the pointer. When all users abandon the object,
FreeFunc::free(T*) is called to clean up the memory used by the resource. */
template<typename T>
class SharedPtr
{
public:
	/// Constructs a zero pointer.
	SharedPtr():dataPtr(0) {}

	/// Constructs from a raw pointer.
	SharedPtr(T *ptr);

	/// Constructs from an existing SharedPtr.
	SharedPtr(const SharedPtr<T> &rhs);

	/// Template copy constructor for types that allow conversions to other types.
	template<typename T2>
	SharedPtr(const SharedPtr<T2> &rhs);

	/// Assignment from another SharedPtr.
	SharedPtr<T> &operator=(const SharedPtr<T> &rhs);

	/// Assignment from a raw ptr.
	SharedPtr<T> &operator=(T *ptr);

	// Releases use of the object.
	~SharedPtr();

	unsigned int RefCount() const; ///< Returns the reference count of the currently held object.

	const T *ptr() const; ///< Const access to the pointer.
	const T *operator->() const; ///< Const dereference and access object.
	const T &operator*() const; ///< Const dereference object.

	operator T*(); ///< Implicit conversion to a raw pointer.

	T *ptr(); ///< Returns a pointer to the object or 0 if empty.
	T *operator->(); ///< Dereference and access object.
	T &operator*(); ///< Dereference object.

	operator bool() const; ///< Test if pointer is good.

	operator bool(); ///< Test if pointer is good.

private:
	T *dataPtr;			///< Pointer to the actual data.

	void AddRef();		///< Increases reference count.
	void Release();	///< Decreases reference count and deletes the object if 0.
};

/** Equality comparison for two SharedPtr. Note that the types must match.
	@param a First operand
	@param b Second operand
	@return true if the objects point to the same object, false otherwise. */
template<typename T>
bool operator==(const SharedPtr<T> &a, const SharedPtr<T> &b)
{
	if (a.ptr() == b.ptr())
		return true;
	else
		return false;
}

} // ~kNet

#include "kNet/SharedPtr.inl"

