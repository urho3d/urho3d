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

#ifndef CAT_BOMBAY_TABLE_HPP
#define CAT_BOMBAY_TABLE_HPP

#include <cat/threads/RWLock.hpp>
#include <cat/io/ThreadPoolFiles.hpp>
#include <cat/db/BombayTableIndex.hpp>

namespace cat {

namespace bombay {


static u64 INVALID_RECORD_OFFSET = ~(u64)0;

struct CacheNode
{
	CacheNode *parent, *lower, *higher;
	u64 offset;
};

class TableIndex;
class IHash;


// Query() AsyncBuffer tag must derive from AsyncQueryRead
struct AsyncQueryRead
{
	ThreadRefObject *_reference;
	AsyncCallback _callback;

	CAT_INLINE void SetCallback(AsyncCallback callback = 0, ThreadRefObject *reference = 0)
	{
		if (reference)
			reference->AddRef();

		_callback = callback;
		_reference = reference;
	}
};


///// Table

class Table : public AsyncFile
{
	ShutdownObserver *_shutdown_observer;
	u32 _record_bytes; // Bytes per record (without CacheNode overhead)
	u64 _next_record; // Next record offset

protected:
	RWLock _lock;

	u64 _index_database_size, _index_read_offset, _index_read_completed;
	u32 _index_read_size;
	static const u32 MAX_INDEX_READ_SIZE = 32768;
	static const int NUM_PARALLEL_INDEX_READS = 3;

	// Cache hash table of binary trees
	static const u32 TARGET_TREE_SIZE = 16;
	static const u32 MIN_TABLE_SIZE = 2048;

	u32 _hash_table_size;
	CacheNode **_cache_hash_table;

	u8 *_cache; // Cache memory
	u32 _cache_bytes; // Cache bytes
	u32 _next_cache_slot; // Offset in cache memory to next free slot
	bool _cache_full; // Cache full flag for optimization

	TableIndex *_head_index, *_head_index_unique;
	TableIndex *_head_index_waiting, *_head_index_update;

	bool AllocateCache();
	void FreeCache();

	// Node versions
	CacheNode *FindNode(u64 offset);
	void UnlinkNode(CacheNode *node);
	void InsertNode(u64 offset, u32 key, CacheNode *hint, CacheNode *node);

	// Always returns with a cache node; may re-use an old cache node
	u8 *SetOffset(u64 offset);
	u8 *InsertOffset(u64 offset);
	u8 *PeekOffset(u64 offset);
	bool RemoveOffset(u64 offset);

public:
	Table(const char *file_path, u32 record_bytes, u32 cache_bytes, ShutdownObserver *shutdown_observer);
	virtual ~Table();

private:
	TableIndex *MakeIndex(const char *index_file_path, IHash *hash_function, bool unique);
	u64 UniqueIndexLookup(const void *data);

public:
	// To initialize, run MakeIndex() for all of the desired indexing routines,
	// and then run Initialize(), which will initialize index objects.
	template<class THashFunc> CAT_INLINE TableIndex *MakeIndex(const char *index_file_path, bool unique)
	{
		return MakeIndex(index_file_path, new THashFunc, unique);
	}

	bool Initialize();

public:
	CAT_INLINE u32 GetCacheBytes() { return _cache_bytes; }
	CAT_INLINE u32 GetRecordBytes() { return _record_bytes; }

protected:
	virtual bool OnRemoveRead(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes);
	virtual bool OnQueryRead(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes);

protected:
	bool StartIndexing();
	bool StartIndexingRead();
	void OnIndexingDone();

	virtual bool OnIndexingRead(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes);

public:
	bool RequestIndexRebuild(TableIndex *index);

public:
	// Insert an AsyncBuffer data buffer
	u64 Insert(void *data);

	// Update with an AsyncBuffer data buffer
	bool Update(void *data, u64 offset);

	// Query with an AsyncBuffer
	// NOTE: Query() AsyncBuffer tag must derive from AsyncQueryRead
	bool Query(u64 offset, AsyncBuffer *buffer);

	// Remove based on offset
	bool Remove(u64 offset);
};


} // namespace bombay

} // namespace cat

#endif // CAT_BOMBAY_TABLE_HPP
