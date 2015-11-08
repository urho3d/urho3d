// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_list.h"
#include "tb_core.h"
#include <assert.h>
#include <stdlib.h>
#include <memory.h>

namespace tb {

bool TBListBackend::Add(void *data)
{
	if (!GrowIfNeeded())
		return false;
	m_data->list[m_data->num] = data;
	m_data->num++;
	return true;
}

bool TBListBackend::Add(void *data, int index)
{
	assert(index >= 0 && index <= GetNumItems());
	if (!GrowIfNeeded())
		return false;
	if (index < m_data->num)
		memmove(&m_data->list[index + 1], &m_data->list[index], (m_data->num - index) * sizeof(void*));
	m_data->list[index] = data;
	m_data->num++;
	return true;
}

void TBListBackend::Set(void *data, int index)
{
	assert(index >= 0 && index < GetNumItems());
	m_data->list[index] = data;
}

void *TBListBackend::RemoveFast(int index)
{
	assert(index >= 0 && index < GetNumItems());
	void *data = m_data->list[index];
	m_data->list[index] = m_data->list[m_data->num - 1];
	m_data->num--;
	return data;
}

void *TBListBackend::Remove(int index)
{
	assert(index >= 0 && index < GetNumItems());
	void *data = m_data->list[index];
	if(index < m_data->num - 1)
		memmove(&m_data->list[index], &m_data->list[index + 1], (m_data->num - index - 1) * sizeof(void*));
	m_data->num--;
	return data;
}

void TBListBackend::RemoveAll()
{
	free(m_data);
	m_data = nullptr;
}

void TBListBackend::Swap(int index1, int index2)
{
	assert(index1 >= 0 && index1 < GetNumItems());
	assert(index2 >= 0 && index2 < GetNumItems());
	void *tmp = m_data->list[index1];
	m_data->list[index1] = m_data->list[index2];
	m_data->list[index2] = tmp;
}

int TBListBackend::Find(void *data) const
{
	int num = GetNumItems();
	for(int i = 0; i < num; i++)
	{
		if (Get(i) == data)
			return i;
	}
	return -1;
}

void *TBListBackend::Get(int index) const
{
	assert(index >= 0 && index < GetNumItems());
	return m_data->list[index];
}

bool TBListBackend::Reserve(int new_capacity)
{
	assert(new_capacity > 0);
	if (new_capacity > GetCapacity())
	{
		int num = GetNumItems();
		if (char *new_data = (char *) realloc(m_data, sizeof(TBLIST_DATA) + sizeof(void *) * (new_capacity)))
		{
			m_data = (TBLIST_DATA *) new_data;
			m_data->num = num;
			m_data->capacity = new_capacity;
			m_data->list = (void**) (new_data + sizeof(TBLIST_DATA));
			return true;
		}
		return false;
	}
	return true;
}

bool TBListBackend::GrowIfNeeded()
{
	int capacity = GetCapacity();
	if (GetNumItems() == capacity)
		return Reserve(CLAMP(4, capacity * 2, 1024));
	return true;
}

}; // namespace tb
