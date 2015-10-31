// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_hashtable.h"
#include "tb_system.h"
#include "tb_tempbuffer.h"

namespace tb {

//FIX: reduce memory (block allocation of ITEM)
//FIX: should shrink when deleting single items (but not when adding items!)
//FIX: should grow when about 70% full instead of 100%

// == TBHashTable =======================================================================

TBHashTable::TBHashTable()
	: m_buckets(0)
	, m_num_buckets(0)
	, m_num_items(0)
{
}

TBHashTable::~TBHashTable()
{
	RemoveAll();
}

void TBHashTable::RemoveAll(bool delete_content)
{
#ifdef TB_RUNTIME_DEBUG_INFO
	//Debug();
#endif
	for (uint32 i = 0; i < m_num_buckets; i++)
	{
		ITEM *item = m_buckets[i];
		while (item)
		{
			ITEM *item_next = item->next;
			if (delete_content)
				DeleteContent(item->content);
			delete item;
			item = item_next;
		}
	}
	delete [] m_buckets;
	m_buckets = nullptr;
	m_num_buckets = m_num_items = 0;
}

bool TBHashTable::Rehash(uint32 new_num_buckets)
{
	if (new_num_buckets == m_num_buckets)
		return true;
	if (ITEM **new_buckets = new ITEM*[new_num_buckets])
	{
		memset(new_buckets, 0, sizeof(ITEM*) * new_num_buckets);
		// Rehash all items into the new buckets
		for (uint32 i = 0; i < m_num_buckets; i++)
		{
			ITEM *item = m_buckets[i];
			while (item)
			{
				ITEM *item_next = item->next;
				// Add it to new_buckets
				uint32 bucket = item->key & (new_num_buckets - 1);
				item->next = new_buckets[bucket];
				new_buckets[bucket] = item;
				item = item_next;
			}
		}
		// Delete old buckets and update
		delete [] m_buckets;
		m_buckets = new_buckets;
		m_num_buckets = new_num_buckets;
		return true;
	}
	return false;
}

bool TBHashTable::NeedRehash() const
{
	// Grow if more items than buckets
	return !m_num_buckets || m_num_items >= m_num_buckets;
}

uint32 TBHashTable::GetSuitableBucketsCount() const
{
	// As long as we use FNV for TBID (in TBGetHash), power of two hash sizes are the best.
	if (!m_num_items)
		return 16;
	return m_num_items * 2;
}

void *TBHashTable::Get(uint32 key) const
{
	if (!m_num_buckets)
		return nullptr;
	uint32 bucket = key & (m_num_buckets - 1);
	ITEM *item = m_buckets[bucket];
	while (item)
	{
		if (item->key == key)
			return item->content;
		item = item->next;
	}
	return nullptr;
}

bool TBHashTable::Add(uint32 key, void *content)
{
	if (NeedRehash() && !Rehash(GetSuitableBucketsCount()))
		return false;
	assert(!Get(key));
	if (ITEM *item = new ITEM)
	{
		uint32 bucket = key & (m_num_buckets - 1);
		item->key = key;
		item->content = content;
		item->next = m_buckets[bucket];
		m_buckets[bucket] = item;
		m_num_items++;
		return true;
	}
	return false;
}

void *TBHashTable::Remove(uint32 key)
{
	if (!m_num_buckets)
		return nullptr;
	uint32 bucket = key & (m_num_buckets - 1);
	ITEM *item = m_buckets[bucket];
	ITEM *prev_item = nullptr;
	while (item)
	{
		if (item->key == key)
		{
			if (prev_item)
				prev_item->next = item->next;
			else
				m_buckets[bucket] = item->next;
			void *content = item->content;
			delete item;
			return content;
		}
		prev_item = item;
		item = item->next;
	}
	assert(!"This hash table didn't contain the given key!");
	return nullptr;
}

void TBHashTable::Delete(uint32 key)
{
	DeleteContent(Remove(key));
}

#ifdef TB_RUNTIME_DEBUG_INFO

void TBHashTable::Debug()
{
	TBTempBuffer line;
	line.AppendString("Hash table: ");
	int total_count = 0;
	for (uint32 i = 0; i < m_num_buckets; i++)
	{
		int count = 0;
		ITEM *item = m_buckets[i];
		while (item)
		{
			count++;
			item = item->next;
		}
		TBStr tmp; tmp.SetFormatted("%d ", count);
		line.AppendString(tmp);
		total_count += count;
	}
	TBStr tmp; tmp.SetFormatted(" (total: %d of %d buckets)\n", total_count, m_num_buckets);
	line.AppendString(tmp);
	TBDebugOut(line.GetData());
}

#endif // TB_RUNTIME_DEBUG_INFO

// == TBHashTableIterator ===============================================================

TBHashTableIterator::TBHashTableIterator(TBHashTable *hash_table)
	: m_hash_table(hash_table)
	, m_current_bucket(0)
	, m_current_item(nullptr)
{
}

void *TBHashTableIterator::GetNextContent()
{
	if (m_current_bucket == m_hash_table->m_num_buckets)
		return nullptr;
	if (m_current_item && m_current_item->next)
		m_current_item = m_current_item->next;
	else
	{
		if (m_current_item)
			m_current_bucket++;
		if (m_current_bucket == m_hash_table->m_num_buckets)
			return nullptr;
		while (m_current_bucket < m_hash_table->m_num_buckets)
		{
			m_current_item = m_hash_table->m_buckets[m_current_bucket];
			if (m_current_item)
				break;
			m_current_bucket++;
		}
	}
	return m_current_item ? m_current_item->content : nullptr;
}

}; // namespace tb
