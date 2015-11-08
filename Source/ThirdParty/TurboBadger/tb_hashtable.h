// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_HASHTABLE_H
#define TB_HASHTABLE_H

#include "tb_core.h"
#include <assert.h>

namespace tb {

/** TBHashTable is a minimal hash table, for hashing anything using a uint32 key. */

class TBHashTable
{
public:
	TBHashTable();
	virtual ~TBHashTable();

	/** Remove all items without deleting the content. */
	void RemoveAll() { RemoveAll(false); }

	/** Remove all items and delete the content.
		This requires TBHashTable to be subclassed and implementing DeleteContent.
		You would typically do this by using TBHashTableOf or TBHashTableAutoDeleteOf. */
	void DeleteAll() { RemoveAll(true); }

	/** Get the content for the given key, or nullptr if not found. */
	void *Get(uint32 key) const;

	/** Add content with the given key.
		Returns false if out of memory. */
	bool Add(uint32 key, void *content);

	/** Remove the content with the given key. */
	void *Remove(uint32 key);

	/** Delete the content with the given key. */
	void Delete(uint32 key);

	/** Rehash the table so use the given number of buckets.
		Returns false if out of memory. */
	bool Rehash(uint32 num_buckets);

	/** Return true if the hashtable itself think it's time to rehash. */
	bool NeedRehash() const;

	/** Get the number of buckets the hashtable itself thinks is suitable for
		the current number of items. */
	uint32 GetSuitableBucketsCount() const;

#ifdef TB_RUNTIME_DEBUG_INFO
	/** Print out some debug info about the hash table. */
	void Debug();
#endif

protected:
	/** Delete the content of a item. This is called if calling DeleteAll, and must be
		implemented in a subclass that knows about the content type. */
	virtual void DeleteContent(void *content) { assert(!"You need to subclass and implement!"); }
private:
	friend class TBHashTableIterator;
	void RemoveAll(bool delete_content);
	struct ITEM {
		uint32 key;
		ITEM *next;
		void *content;
	} **m_buckets;
	uint32 m_num_buckets;
	uint32 m_num_items;
};

/** TBHashTableIterator is a iterator for stepping through all content stored in a TBHashTable. */
//FIX: make it safe in case the current item is removed from the hashtable
class TBHashTableIterator
{
public:
	TBHashTableIterator(TBHashTable *hash_table);
	void *GetNextContent();
private:
	TBHashTable *m_hash_table;
	uint32 m_current_bucket;
	TBHashTable::ITEM *m_current_item;
};

/** TBHashTableIteratorOf is a TBHashTableIterator which auto cast to the class type. */
template<class T>
class TBHashTableIteratorOf : private TBHashTableIterator
{
public:
	TBHashTableIteratorOf(TBHashTable *hash_table) : TBHashTableIterator(hash_table) {}
	T *GetNextContent() { return (T*) TBHashTableIterator::GetNextContent(); }
};

/** TBHashTableOf is a TBHashTable with the given class type as content. */
template<class T>
class TBHashTableOf : public TBHashTable
{
// FIX: Don't do public inheritance! Either inherit privately and forward, or use a private member backend!
public:
	T *Get(uint32 key) const { return (T*) TBHashTable::Get(key); }

protected:
	virtual void DeleteContent(void *content) { delete (T*) content; }
};

/** TBHashTableOf is a TBHashTable with the given class type as content.
	It will delete all content automaticallt on destruction. */
template<class T>
class TBHashTableAutoDeleteOf : public TBHashTable
{
public:
	~TBHashTableAutoDeleteOf() { DeleteAll(); }

	T *Get(uint32 key) const { return (T*) TBHashTable::Get(key); }

protected:
	virtual void DeleteContent(void *content) { delete (T*) content; }
};

}; // namespace tb

#endif // TB_HASHTABLE_H
