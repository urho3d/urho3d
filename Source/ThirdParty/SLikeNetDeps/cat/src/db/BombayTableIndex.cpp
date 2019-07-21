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

#include <cat/db/BombayTableIndex.hpp>
#include <cat/port/AlignedAlloc.hpp>
#include <cat/io/Logging.hpp>
#include <cat/hash/MurmurHash2.hpp>
using namespace cat;
using namespace bombay;

TableIndex::TableIndex(Table *parent, const char *file_path,
					   IHash *hash_function, ShutdownObserver *shutdown_observer)
	: AsyncFile(REFOBJ_PRIO_0+17)
{
	_shutdown_observer = shutdown_observer;
	if (shutdown_observer)
		shutdown_observer->AddRef();

	_parent = parent;
	_index_hash = hash_function;
	CAT_STRNCPY(_file_path, file_path, sizeof(_file_path));

	_table = 0;
	_table_elements = 0;
	_used_elements = 0;
	_table_raw_bytes = 0;

	_next = 0;
	_next_unique = 0;
	_next_loading = 0;
}

TableIndex::~TableIndex()
{
	FreeTable();

	if (_index_hash) delete _index_hash;

	ThreadRefObject::SafeRelease(_shutdown_observer);
}


//// Table Management

bool TableIndex::AllocateTable()
{
	static const u32 MIN_BYTES = (MIN_ELEMENTS << 4) + TABLE_FOOTER_BYTES;

	u64 *page = (u64*)LargeAligned::Acquire(MIN_BYTES);
	if (!page)
	{
		FATAL("TableIndex") << "Out of memory: Unable to allocate minimum size table for " << _file_path;
		return false;
	}

	FreeTable();

	_table_elements = MIN_ELEMENTS;
	_table_raw_bytes = MIN_BYTES;
	_table = page;
	_used_elements = 0;

	return true;
}

bool TableIndex::DoubleTable()
{
	// Calculate next highest power-of-2
	u32 target_size = _table_elements << 1;
	u32 bytes = (target_size << 4) + TABLE_FOOTER_BYTES;

	// Allocate that amount of memory
	u64 *page = (u64*)LargeAligned::Acquire(bytes);
	if (!page) return false;

	// Zero it
	CAT_CLR(page, bytes - TABLE_FOOTER_BYTES);

	// If there is an old table (should be),
	u64 *old = _table;
	if (old)
	{
		// Redistribute the old table elements across the expanded table
		for (u32 ii = 0, end = _table_elements, mask = target_size - 1; ii < end; ++ii)
		{
			u64 offset = old[ii << 1];

			// If this old element is used,
			if (offset)
			{
				u64 hash = old[(ii << 1) + 1];
				u32 key = (u32)hash & mask;

				// While collision in new table,
				u64 newoffset;
				while ((newoffset = page[key << 1]))
				{
					page[key << 1] = newoffset | COLLIDE_MASK;

					// LCG with period equal to the table size
					key = (key * COLLISION_MULTIPLIER + COLLISION_INCREMENTER) & mask;
				}

				// Write old element in new table
				page[key << 1] = offset & OFFSET_MASK;
				page[(key << 1) + 1] = hash;
			}
		}

		LargeAligned::Release(old);
	}

	// Choose new table
	_table = page;
	_table_elements = target_size;
	_table_raw_bytes = bytes;

	return true;
}

void TableIndex::FreeTable()
{
	if (_table)
	{
		LargeAligned::Release(_table);

		_table = 0;
		_table_elements = 0;
		_table_raw_bytes = 0;
		_used_elements = 0;
	}
}


//// Access

void TableIndex::Save()
{
	if (!_table) return;

	INFO("TableIndex") << "Saving index file for " << _file_path;

	AsyncBuffer *buffer = AsyncBuffer::Wrap(_table, _table_raw_bytes);
	if (!buffer)
	{
		WARN("TableIndex") << "Out of memory: Unable to write table index for " << _file_path;
		return;
	}

	// Write footer
	_table[_table_elements << 1] = _used_elements;
	_table[(_table_elements << 1) + 1] = MurmurHash64(_table, _table_raw_bytes - 8, TABLE_CHECK_HASH_SALT);

	if (!Write(buffer, 0))
	{
		WARN("TableIndex") << "Unable to write table index for " << _file_path;
	}
}

bool TableIndex::Initialize()
{
	if (!Open(_file_path, ASYNCFILE_READ | ASYNCFILE_WRITE))
	{
		FATAL("TableIndex") << "Unable to open index file " << _file_path;
		return false;
	}

	u32 size = (u32)GetSize(); // Table size is always assumed < 4 GB
	u32 element_bytes = size - TABLE_FOOTER_BYTES;
	u32 table_elements = element_bytes >> 4;

	if (!size || table_elements < MIN_ELEMENTS || !CAT_IS_POWER_OF_2(element_bytes))
	{
		WARN("TableIndex") << "Table index for " << _file_path << " was not found.  Regenerating index..";

		return AllocateTable() && _parent->RequestIndexRebuild(this);
	}
	else
	{
		INFO("TableIndex") << "Requesting read of index file for " << _parent->GetFilePath() << "..";

		_table_elements = table_elements;
		_table_raw_bytes = size;

		_table = (u64*)LargeAligned::Acquire(size);
		if (!_table)
		{
			FATAL("TableIndex") << "Out of memory: Unable to allocate table index " << _file_path;
			return false;
		}

		AsyncBuffer *buffer = AsyncBuffer::Wrap(_table, size);
		if (!buffer)
		{
			WARN("TableIndex") << "Out of memory: Unable to acquire read object for " << _file_path;
			return false;
		}

		if (!Read(buffer, 0, fastdelegate::MakeDelegate(this, &TableIndex::OnRead)))
		{
			FATAL("TableIndex") << "Read failure: Unable to read table index " << _file_path;
			return false;
		}
	}

	return true;
}

bool TableIndex::OnRead(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes)
{
	u64 *data = buffer->GetData<u64>();
	u64 offset = buffer->GetOffset();

	if (error || offset != 0 || bytes != _table_raw_bytes || data != _table)
	{
		WARN("TableIndex") << "Table index for " << _file_path << " was truncated.  Regenerating index..";

		AllocateTable() && _parent->RequestIndexRebuild(this);
		return true;
	}

	// Read footer
	_used_elements = (u32)_table[_table_elements << 1];

	if (_table[(_table_elements << 1) + 1] != MurmurHash64(_table, _table_raw_bytes - 8, TABLE_CHECK_HASH_SALT))
	{
		WARN("TableIndex") << "Table index for " << _file_path << " was corrupted.  Regenerating index..";

		AllocateTable() && _parent->RequestIndexRebuild(this);
		return true;
	}

	INFO("TableIndex") << "Table index read for " << _file_path << " successful.";

	return true;
}


//// User Interface

u64 TableIndex::Lookup(u64 hash)
{
	if (!hash) return INVALID_RECORD_OFFSET;

	u32 mask = _table_elements - 1;
	u32 key = (hash - 1) & mask;

	AutoReadLock lock(_lock);

	// Find table entry starting from key
	u64 *table = _table;
	u64 offset;
	while ((offset = table[key << 1]))
	{
		u64 existing = table[(key << 1) + 1];

		// If we found it,
		if (hash == existing) return (offset & OFFSET_MASK) - 1;

		// Break on a break in the collision list
		if (!(offset & COLLIDE_MASK)) break;

		// LCG with period equal to the table size
		key = (key * COLLISION_MULTIPLIER + COLLISION_INCREMENTER) & mask;
	}

	return INVALID_RECORD_OFFSET;
}

void TableIndex::Insert(u64 hash, u64 offset)
{
	if (!hash) return;

	u32 mask = _table_elements - 1;
	u32 key = (hash - 1) & mask;

	AutoWriteLock lock(_lock);

	// Grow if too many used elements
	if (_used_elements >= (_table_elements >> 1))
	{
		if (!DoubleTable())
		{
			FATAL("TableIndex") << "Out of memory: Unable to double size of index table " << _file_path;
			return;
		}
	}

	// Find insertion point in the case of collision
	u64 *table = _table;
	u64 oldoffset;
	while ((oldoffset = table[key << 1]) & OFFSET_MASK)
	{
		table[key << 1] = oldoffset | COLLIDE_MASK;

		// LCG with period equal to the table size
		key = (key * COLLISION_MULTIPLIER + COLLISION_INCREMENTER) & mask;
	}

	// Insert preserving collision flag
	table[key << 1] = oldoffset | (offset + 1);
	table[(key << 1) + 1] = hash;

	++_used_elements;
}

void TableIndex::Remove(u64 hash)
{
	if (!hash) return;

	u32 mask = _table_elements - 1;
	u32 key = (hash - 1) & mask;
	u32 last = key; // Represents the last valid entry

	AutoWriteLock lock(_lock);

	// Find insertion point in the case of collision
	u64 *table = _table;
	u64 offset;
	while ((offset = table[key << 1]))
	{
		u64 existing = table[(key << 1) + 1];

		// If found entry to remove,
		if (hash == existing)
		{
			offset &= COLLIDE_MASK;

			table[key << 1] = offset;
			table[(key << 1) + 1] = 0; // Set invalid hash value

			--_used_elements;

			// If last entry is to be unlinked,
			if (!offset && last != key)
			{
				// Unlink from previous
				table[last << 1] &= OFFSET_MASK;

				// Zero out entries between previous and removed entry
				for (;;)
				{
					// LCG with period equal to the table size
					last = (last * COLLISION_MULTIPLIER + COLLISION_INCREMENTER) & mask;

					if (last == key) break;

					table[last << 1] = 0;
				}
			}

			break;
		}

		// Break on a break in the collision list
		if (!(offset & COLLIDE_MASK)) break;

		// If offset is set,
		if (offset & OFFSET_MASK)
		{
			// Relocate the last valid entry
			last = key;
		}

		// LCG with period equal to the table size
		key = (key * COLLISION_MULTIPLIER + COLLISION_INCREMENTER) & mask;
	}
}
