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

#ifndef CAT_SPHYNX_COLLEXION_HPP
#define CAT_SPHYNX_COLLEXION_HPP

#include <cat/threads/Mutex.hpp>
#include <cat/threads/RegionAllocator.hpp>
#include <cat/net/SphynxTransport.hpp>

namespace cat {


namespace sphynx {


/*
	The purpose of sphynx::Collexion and sphynx::CollexionIterator is to
	store lists of Connexion object references and iterate through them.

	Since the number of clients may be in the thousands, I feel it is
	important to scale effectively.  So in the Collexion data structure,
	insertion and removal are O(1) operations.  Also locks should be held
	for the smallest amount of time possible, so I have taken care to make
	locks short and reduce the amount of locking.  For example, the iterator
	caches large blocks of data instead of locking for each iteration.

	The design is optimized for cache usage, re-using common code to benefit
	from code cache and allocating and accessing table entries on cache line
	boundaries to double memory performance over a naive approach.
*/


//// sphynx::Collexion

template<class T>
class CollexionIterator;

template<class T>
struct CollexionElement
{
	// Number of active enumerators using this element
	// If references are held it cannot be deleted
	// so the KILL flag is set on the 'next' member and
	// the final enumerator to reduce the reference count
	// to zero is responsible for removal.
	u32 refcnt;

	// Bitfield:
	//  1 bit: COLLISION FLAG
	//  1 bit: KILL FLAG
	//  30 bits: Table index to next element in list + 1
	u32 next;

	// Data at this table element
	T *conn;
};

struct CollexionElement2
{
	// Previous table element in list + 1
	u32 last;

	// Hash of data pointer from main entry (so it doesn't need to be recalculated during growth)
	u32 hash;
};

template<class T>
class Collexion
{
	static const u32 COLLIDE_MASK = 0x80000000;
	static const u32 KILL_MASK = 0x40000000;
	static const u32 NEXT_MASK = 0x3fffffff;
	static const u32 MIN_ALLOCATED = 32;

private:
	// Number of used table elements
	u32 _used;

	// Number of allocated table elements
	u32 _allocated;

	// First table index in list of active elements
	u32 _first;

	// Primary table
	CollexionElement<T> *_table;

	// Secondary table, split off so that primary table elements will
	// fit on a cache line.  Contains data that is only accessed rarely.
	CollexionElement2 *_table2;

	// Table lock
	Mutex _lock;

protected:
	// Attempt to double size of hash table (does not hold lock)
	bool DoubleTable();

	// Hash a pointer to a 32-bit table key
	static CAT_INLINE u32 HashPtr(T *ptr)
	{
		u64 key = 0xBADdecafDEADbeef;

#if defined(CAT_WORD_64)
		key ^= *(u64*)&ptr;
#else
		key ^= *(u32*)&ptr;
#endif

		key = (~key) + (key << 18);
		key = key ^ (key >> 31);
		key = key * 21;
		key = key ^ (key >> 11);
		key = key + (key << 6);
		key = key ^ (key >> 22);
		return (u32)key;
	}

	// Common functions shared by interface for good code cache usage:

	// Unlink a table key
	void Unlink(u32 key);

	// Fill an iterator with the next set of data
	// Returns false if no data remains to fill
	void Fill(CollexionIterator<T> &iter, u32 first);

	// Find a hash table key based on data
	u32 Find(T *conn);

public:
	// Ctor zeros everything
	Collexion()
	{
		_first = 0;
		_used = 0;
		_allocated = 0;
		_table = 0;
		_table2 = 0;
	}

	// Dtor releases dangling memory
	~Collexion();

	// Returns true if table is empty
	CAT_INLINE bool IsEmpty() { return _used == 0; }

	// Insert Connexion object, return false if already present or out of memory
	bool Insert(T *conn);

	// Remove Connexion object from list if it exists
	bool Remove(T *conn);

	// Begin iterating through list
	void Begin(CollexionIterator<T> &iter);

	// Iterate
	void Next(CollexionIterator<T> &iter, bool refill = true);
};


//// sphynx::CollexionIterator

template<class T>
class CollexionIterator
{
	friend class Collexion<T>;

	static const u32 MAX_CACHE = 256;

	// Parent Collexion object
	Collexion<T> *_parent;

	// First and last hash table indices in parent
	u32 _first, _last;

	// Stores the size of the parent when snapshot was taken,
	// will invalidate _first and _last if table changed size
	u32 _prev_allocated;

	// Connexion object cache, to avoid locking and unlocking a lot
	T *_cache[MAX_CACHE];

	// Offset into cache and total elements in cache
	// Will grab another cache once offset reaches total
	u32 _offset, _total;

public:
	// Smart pointer -style accessors
	CAT_INLINE T *Get() throw() { return _cache[_offset]; }
	CAT_INLINE T *operator->() throw() { return _cache[_offset]; }
	CAT_INLINE T &operator*() throw() { return *_cache[_offset]; }
	CAT_INLINE operator T*() { return _cache[_offset]; }

public:
	// Ctor: Grabs first cache of Connexions
	CollexionIterator(Collexion<T> &begin);

	// Dtor: Calls Release()
	~CollexionIterator();

	// Iterate to next Connexion object in list
	CollexionIterator &operator++();

	// Releases reference to any outstanding Connexions
	void Release();
};


//// sphynx::Collexion

template<class T>
bool Collexion<T>::DoubleTable()
{
	u32 new_allocated = _allocated << 1;
	if (new_allocated < MIN_ALLOCATED) new_allocated = MIN_ALLOCATED;

	// Allocate secondary table
	u32 new_bytes2 = sizeof(CollexionElement2) * new_allocated;
	CollexionElement2 *new_table2 = reinterpret_cast<CollexionElement2*>(
		RegionAllocator::ii->Acquire(new_bytes2) );

	if (!new_table2) return false;

	// Allocate primary table
	u32 new_bytes = sizeof(CollexionElement<T>) * new_allocated;
	CollexionElement<T> *new_table = reinterpret_cast<CollexionElement<T> *>(
		RegionAllocator::ii->Acquire(new_bytes) );

	if (!new_table)
	{
		RegionAllocator::ii->Release(new_table2);
		return false;
	}

	CAT_CLR(new_table, new_bytes);

	u32 new_first = 0;

	if (_table && _table2)
	{
		// For each entry in the old table,
		u32 ii = _first, mask = _allocated - 1;

		while (ii)
		{
			--ii;
			CollexionElement<T> *oe = &_table[ii];
			u32 hash = _table2[ii].hash;
			u32 key = hash & mask;

			// While collisions occur,
			while (new_table[key].conn)
			{
				// Mark collision
				new_table[key].next |= COLLIDE_MASK;

				// Walk collision list
				key = (key * COLLISION_MULTIPLIER + COLLISION_INCREMENTER) & mask;
			}

			// Fill new table element
			new_table[key].conn = oe->conn;
			new_table2[key].hash = hash;
			// new_table[key].refcnt is already zero

			// Link new element to new list
			if (new_first)
			{
				new_table[key].next |= new_first;
				new_table2[new_first - 1].last = key;
			}
			// new_table[key].next is already zero so no need to zero it here
			new_first = key + 1;

			// Get next old table entry
			ii = oe->next & NEXT_MASK;
		}

		// Zero head->last
		new_table2[new_first - 1].last = 0;
	}

	// Resulting linked list starting with _first-1 will extend until e->next == 0

	if (_table2) RegionAllocator::ii->Release(_table2);
	if (_table) RegionAllocator::ii->Release(_table);

	_table = new_table;
	_table2 = new_table2;
	_allocated = new_allocated;
	_first = new_first;
	return true;
}

template<class T>
Collexion<T>::~Collexion()
{
	if (_table2)
	{
		RegionAllocator::ii->Release(_table2);
	}

	// If table doesn't exist, return
	if (!_table) return;

	// For each allocated table entry,
	for (u32 ii = 0; ii < _allocated; ++ii)
	{
		// Get Connexion object
		T *conn = _table[ii].conn;

		// If object is valid, release it
		if (conn) conn->ReleaseRef();
	}

	// Release table memory
	RegionAllocator::ii->Release(_table);
}

template<class T>
bool Collexion<T>::Insert(T *conn)
{
	u32 hash = HashPtr(conn);
	conn->AddRef();

	AutoMutex lock(_lock);

	// If more than half of the table will be used,
	if (_used >= (_allocated >> 1))
	{
		// Double the size of the table (O(1) allocation pattern)
		// Growing pains are softened by careful design
		if (!DoubleTable())
		{
			// On growth failure, return false
			lock.Release();

			conn->ReleaseRef();

			return false;
		}
	}

	// Mask off high bits to make table key from hash
	u32 mask = _allocated - 1;
	u32 key = hash & mask;

	// While empty table entry not found,
	while (_table[key].conn)
	{
		// If Connexion object is already in the table,
		if (_table[key].conn == conn)
		{
			// Return false on duplicate
			lock.Release();

			conn->ReleaseRef();

			return false;
		}

		// Mark as a collision
		_table[key].next |= COLLIDE_MASK;

		// Walk collision list
		key = (key * COLLISION_MULTIPLIER + COLLISION_INCREMENTER) & mask;
	}

	// Fill new element
	_table[key].conn = conn;
	_table[key].refcnt = 0;
	_table2[key].hash = hash;
	_table2[key].last = 0;

	// Link new element to front of list
	if (_first) _table2[_first - 1].last = key + 1;
	_table[key].next = (_table[key].next & COLLIDE_MASK) | _first;
	_first = key + 1;

	++_used;
	return true;
}

template<class T>
void Collexion<T>::Unlink(u32 key)
{
	// Clear reference
	_table[key].conn = 0;

	// Unlink from active list
	u32 next = _table[key].next & NEXT_MASK;
	u32 last = _table2[key].last;

	if (last) _table[last-1].next = (_table[last-1].next & ~NEXT_MASK) | next;
	else _first = next;
	if (next) _table2[next-1].last = last;

	// If this key was a leaf on a collision wind,
	if (!(_table[key].next & COLLIDE_MASK))
	{
		u32 mask = _allocated - 1;

		do
		{
			// Go backwards through the collision list one step
			key = ((key + COLLISION_INCRINVERSE) * COLLISION_MULTINVERSE) & mask;

			// Stop where collision list stops
			if (!(_table[key].next & COLLIDE_MASK))
				break;

			// Turn off collision key for previous entry
			_table[key].next &= ~COLLIDE_MASK;

		} while (!_table[key].conn);
	}

	// Update number of used elements
	--_used;
}

template<class T>
bool Collexion<T>::Remove(T *conn)
{
	u32 hash = HashPtr(conn);

	AutoMutex lock(_lock);

	// If table doesn't exist,
	if (!_allocated) return false;

	// Mask off high bits to make table key from hash
	u32 mask = _allocated - 1;
	u32 key = hash & mask;

	// While target table entry not found,
	for (;;)
	{
		// If target was found,
		if (_table[key].conn == conn)
		{
			if (_table[key].refcnt)
			{
				// Mark it killed so iterator can clean it up when it's finished
				_table[key].next |= KILL_MASK;
			}
			else
			{
				Unlink(key);

				lock.Release();

				conn->ReleaseRef();
			}

			// Return success
			return true;
		}

		if (!(_table[key].next & COLLIDE_MASK))
		{
			break; // End of collision list
		}

		// Walk collision list
		key = (key * COLLISION_MULTIPLIER + COLLISION_INCREMENTER) & mask;
	}

	// Return failure: not found
	return false;
}

template<class T>
void Collexion<T>::Fill(CollexionIterator<T> &iter, u32 first)
{
	u32 key = first;

	// Find first list element that does not want to die
	while (key && (_table[key-1].next & KILL_MASK))
	{
		// Go to next
		key = _table[key-1].next & NEXT_MASK;
	}

	iter._offset = 0;

	// If no elements in table,
	if (!key)
	{
		// Return empty set
		iter._cache[0] = 0;
		iter._total = 0;
		iter._first = 0;
		iter._last = 0;
		return;
	}

	// Remember size of hash table in case it grows before iterator is done
	iter._prev_allocated = _allocated;

	// Remember first key for next iteration
	iter._first = key;

	// For each of the first MAX_CACHE elements in the table, copy the data pointer to cache
	u32 ii = 0, final = 0;

	do
	{
		// If element does not want to die,
		if (!(_table[key-1].next & KILL_MASK))
		{
			// Copy data pointer
			iter._cache[ii] = _table[key-1].conn;

			// Increment reference count for element
			_table[key-1].refcnt++;

			// Remember key as the next iteration starting point
			final = key;

			// Check if copy is complete
			if (++ii >= CollexionIterator<T>::MAX_CACHE) break;
		}

		// Go to next key
		key = _table[key-1].next & NEXT_MASK;

	} while (key);

	// Record number of elements written
	iter._total = ii;

	// Remember next key for next iteration
	iter._last = final;
}

template<class T>
void Collexion<T>::Begin(CollexionIterator<T> &iter)
{
	iter._parent = this;

	AutoMutex lock(_lock);

	Fill(iter, _first);
}

// Find a hash table key based on data
template<class T>
u32 Collexion<T>::Find(T *conn)
{
	u32 mask = _allocated - 1;
	u32 key = HashPtr(conn) & mask;

	// Find the object in the collision list starting at the expected location
	while (_table[key].conn != conn)
	{
		// If at the end of the collision list,
		if (!(_table[key].next & COLLIDE_MASK))
			break; // Should never happen

		// Walk collision list
		key = (key * COLLISION_MULTIPLIER + COLLISION_INCREMENTER) & mask;
	}

	return key;
}

template<class T>
void Collexion<T>::Next(CollexionIterator<T> &iter, bool refill)
{
	T *release_list[CollexionIterator<T>::MAX_CACHE];
	u32 release_ii = 0;

	u32 key = iter._first;
	u32 last = iter._last;

	// If iteration is done,
	if (!key) return;

	AutoMutex lock(_lock);

	// If hash table changed size (rare),
	if (iter._prev_allocated != _allocated)
	{
		// iter._first and iter._last are invalid
		// ...but we can find them again based on the cached pointers!
		key = Find(iter._cache[0]) + 1;
		last = Find(iter._cache[iter._total - 1]) + 1;
	}

	last = _table[last-1].next & NEXT_MASK;

	// Release any table elements that want to die now
	do 
	{
		u32 flags = _table[key-1].next;

		// If reference count is now zero for this element,
		if (0 == --_table[key-1].refcnt)
		{
			// If element wants to die,
			if (flags & KILL_MASK)
			{
				// Prepare to release data after lock is released
				release_list[release_ii++] = _table[key-1].conn;

				Unlink(key-1);
			}
		}

		key = flags & NEXT_MASK;

	} while (key != last);

	// Fill iterator starting with next key
	if (refill) Fill(iter, key);

	lock.Release();

	if (!refill)
	{
		// Return empty set
		iter._cache[0] = 0;
		iter._total = 0;
		iter._offset = 0;
		iter._first = 0;
		iter._last = 0;
	}

	// Release data awaiting destruction
	for (u32 ii = 0; ii < release_ii; ++ii)
	{
		release_list[ii]->ReleaseRef();
	}
}


//// sphynx::CollexionIterator

template<class T>
CollexionIterator<T>::CollexionIterator(Collexion<T> &begin)
{
	begin.Begin(*this);
}

template<class T>
CollexionIterator<T>::~CollexionIterator()
{
	Release();
}

template<class T>
CollexionIterator<T> &CollexionIterator<T>::operator++()
{
	if (++_offset >= _total)
	{
		_parent->Next(*this, true);
	}

	return *this;
}

template<class T>
void CollexionIterator<T>::Release()
{
	if (_parent)
	{
		_parent->Next(*this, false);
		_parent = 0;
	}
}


} // namespace sphynx


} // namespace cat

#endif // CAT_SPHYNX_COLLEXION_HPP
