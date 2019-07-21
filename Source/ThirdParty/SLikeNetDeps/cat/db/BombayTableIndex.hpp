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

#ifndef CAT_BOMBAY_TABLE_INDEX_HPP
#define CAT_BOMBAY_TABLE_INDEX_HPP

#include <cat/db/BombayTable.hpp>

namespace cat {

namespace bombay {


/*
	Returning 0 from one of these hash functions will cause insertion or lookup to fail,
	which is how invalid input is intended to be handled.
*/

class IHash
{
public:
	virtual u64 HashField(const void *just_field) = 0;
	virtual u64 HashComplete(const void *complete_record) = 0;
	virtual u64 HashVarField(const void *just_field, u32 bytes) { return HashField(just_field); }
};

#define DECL_BOMBAY_SCHEMA_VAR_FIELD_HASH(T) \
class T : public bombay::IHash \
{ \
public: \
	u64 HashField(const void *just_field); \
	u64 HashComplete(const void *complete_record); \
	u64 HashVarField(const void *just_field, u32 bytes); \
};

#define DECL_BOMBAY_SCHEMA_FIXED_FIELD_HASH(T) \
class T : public bombay::IHash \
{ \
public: \
	u64 HashField(const void *just_field); \
	u64 HashComplete(const void *complete_record); \
};



/*
	Table index must present a complete index of the contents of a Table.

	The index uses some region of bytes in each entry as a key to find
	the entry given just that set of bytes.  For example, mapping a user
	name to a database node.

	The table index should be loaded from disk on startup.  If this is
	not possible, then an index rebuild will need to be done on startup.

	Hash table size will be at least twice as large as the number of
	database entries, growing as needed.

	To avoid a lot of expensive setup, each element is arranged like this:

		<-- MSB           LSB -->
		C(1 bit) || OFFSET+1 (63 bits)
		HASH(64 bits)

	C: Collision flag
		0 = No collision
		1 = Collision, actual data may be stored at next walk location

	OFFSET+1: Database file offset for this entry that contains the
		full unique identifier.  One(1) is added to the offset in
		the memory representation of the index table element, so that
		OFFSET = ~0 will be set by zeroing out the table.
		0 = No data at this table element.
		Other values = Valid offset+1

	HASH: 64-bit full hash
		Only low bits are used for table lookup, so hash does not need
		to be recomputed if the table grows and lookup of something that
		is not in the table does not have collisions half the time.

	The whole structure fits in one cache line on an x86 server.
*/

class Table;

class TableIndex : public AsyncFile
{
	friend class Table;

	ShutdownObserver *_shutdown_observer;
	Table *_parent;
	IHash *_index_hash;
	TableIndex *_next, *_next_unique, *_next_loading;

protected:
	// (multiplier-1) divisible by all prime factors of table size
	// (multiplier-1) is a multiple of 4 if table size is a multiple of 4
	// Increment is relatively prime to the table size.
	static const u32 COLLISION_MULTIPLIER = 71*7487 * 4 + 1;
	static const u32 COLLISION_INCREMENTER = 1017234223;

	static const u64 OFFSET_MASK = (~(u64)0) >> 1;
	static const u64 COLLIDE_MASK = ~OFFSET_MASK;
	static const u32 MIN_ELEMENTS = 1024;

	static const u32 TABLE_FOOTER_BYTES = 16;
	static const u64 TABLE_CHECK_HASH_SALT = 0x74B1301234DEADBE;

	RWLock _lock;

	u64 *_table;
	u32 _table_raw_bytes;
	u32 _table_elements; // A power of 2; just subtract 1 to make a mask
	u32 _used_elements;

	char _file_path[MAX_PATH+1];

	bool AllocateTable();
	bool DoubleTable();
	void FreeTable();

protected:
	void Save();

public:
	TableIndex(Table *parent, const char *index_file_path,
			   IHash *hash_function, ShutdownObserver *shutdown_observer);
	~TableIndex();

	bool Initialize();

protected:
	virtual bool OnRead(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes);

public:
	CAT_INLINE const char *GetFilePath() { return _file_path; }

public:
	CAT_INLINE u64 VarField(const void *data, u32 bytes)
	{
		return _index_hash->HashVarField(data, bytes);
	}
	CAT_INLINE u64 Field(const void *data)
	{
		return _index_hash->HashField(data);
	}
	CAT_INLINE u64 Complete(const void *data)
	{
		return _index_hash->HashComplete(data);
	}

public:
	// Hash value of 0 will be ignored
	u64 Lookup(u64 hash);
	void Insert(u64 hash, u64 offset);
	void Remove(u64 hash);

public:
	CAT_INLINE u64 LookupVarField(const void *data, u32 bytes)
	{
		return Lookup(_index_hash->HashVarField(data, bytes));
	}
	CAT_INLINE u64 LookupField(const void *data)
	{
		return Lookup(_index_hash->HashField(data));
	}
	CAT_INLINE u64 LookupComplete(const void *data)
	{
		return Lookup(_index_hash->HashComplete(data));
	}

public:
	CAT_INLINE void InsertVarField(const void *data, u32 bytes, u64 offset)
	{
		Insert(_index_hash->HashVarField(data, bytes), offset);
	}
	CAT_INLINE void InsertField(const void *data, u64 offset)
	{
		Insert(_index_hash->HashField(data), offset);
	}
	CAT_INLINE void InsertComplete(const void *data, u64 offset)
	{
		Insert(_index_hash->HashComplete(data), offset);
	}

public:
	CAT_INLINE void RemoveVarField(const void *data, u32 bytes)
	{
		Remove(_index_hash->HashVarField(data, bytes));
	}
	CAT_INLINE void RemoveField(const void *data)
	{
		Remove(_index_hash->HashField(data));
	}
	CAT_INLINE void RemoveComplete(const void *data)
	{
		Remove(_index_hash->HashComplete(data));
	}
};


} // namespace bombay

} // namespace cat

#endif // CAT_BOMBAY_TABLE_INDEX_HPP
