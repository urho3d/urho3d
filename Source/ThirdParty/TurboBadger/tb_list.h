// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_LIST_H
#define TB_LIST_H

#include "tb_core.h"
namespace tb {

/** TBList is a list (array) of pointers to any kind of objects.
	This is the backend for TBListOf and TBListAutoDeleteOf.
	You should use the typed TBListOf or TBListAutoDeleteOf for object storing! */
class TBListBackend
{
public:
	TBListBackend() : m_data(nullptr) {}
	~TBListBackend() { RemoveAll(); }
	bool Reserve(int num);
	bool GrowIfNeeded();
	bool Add(void *data);
	bool Add(void *data, int index);
	void Set(void *data, int index);
	void *Get(int index) const;
	void *operator [] (int index) const { return Get(index); }
	void *RemoveFast(int index);
	void *Remove(int index);
	void RemoveAll();
	void Swap(int index1, int index2);
	int Find(void *data) const;
	int GetNumItems() const { return m_data ? m_data->num : 0; }
	int GetCapacity() const { return m_data ? m_data->capacity : 0; }
private:
	struct TBLIST_DATA {
		int num;
		int capacity;
		void **list;
	};
	TBLIST_DATA *m_data;
};

/** TBListOf is a list (array) of pointers to the specified object type.
	Note: The objects won't be deleted automatically. If you want that,
	use TBListAutoDeleteOf! */
template<class T>
class TBListOf
{
public:
	/** Make sure there is space for at least num items in the list. Returns false on OOM failure. */
	bool Reserve(int num)					{ return m_list.Reserve(num); }

	/** Make sure there is space for at least one more item in the list. Returns false on OOM failure.
		There's no need to call this, but it can make OOM handling easier in some situations since you
		can guarantee there is space is in a list *before* you allocate an object to insert into it. */
	bool GrowIfNeeded()						{ return m_list.GrowIfNeeded(); }

	/** Add data at the end of the list. Returns false on OOM failure. */
	bool Add(T *data)						{ return m_list.Add(data); }

	/** Add data at the given index in the list. Returns false on OOM failure. */
	bool Add(T *data, int index)			{ return m_list.Add(data, index); }

	/** Replace the item at the index with the new data */
	void Set(T *data, int index)			{ m_list.Set(data, index); }

	/** Returns the content at position index. */
	T *Get(int index) const					{ return (T *) m_list.Get(index); }

	/** Returns the content at position index. */
	T *operator [] (int index) const		{ return (T *) m_list.Get(index); }

	/** Remove the item at position index from the list and returns the pointer.
		This method should only be used when the order of the list is not important.
		If the order is important, use Remove() */
	T *RemoveFast(int index)				{ return (T *) m_list.RemoveFast(index); }

	/** Remove the item at position index from the list and returns the pointer. */
	T *Remove(int index)					{ return (T *) m_list.Remove(index); }

	/** Deletes the item at position index after removing it from the list.
		This method should only be used when the order of the list is not important.
		If the order is important, use Delete() */
	void DeleteFast(int index)				{ delete (T *) m_list.RemoveFast(index); }

	/** Deletes the item at position index after removing it from the list. */
	void Delete(int index)					{ delete (T *) m_list.Remove(index); }

	/** Remove all items without deleding them. */
	void RemoveAll()						{ m_list.RemoveAll(); }

	/** Remove and delete all items from the list. */
	void DeleteAll()
	{
		for (int i = 0; i < GetNumItems(); i++)
			delete (T *) Get(i);
		m_list.RemoveAll();
	}

	/** Swap the items at index1 and index2 */
	void Swap(int index1, int index2)		{ m_list.Swap(index1, index2); }

	/** Search for the item with the given data and return the found index, or -1 if not found. */
	int Find(T *data) const					{ return m_list.Find(data); }

	/** Get the number of items in the list. */
	int GetNumItems() const					{ return m_list.GetNumItems(); }

	/** Get the capacity of the list number of items it can hold without allocating more memory) */
	int GetCapacity() const					{ return m_list.GetCapacity(); }
private:
	TBListBackend m_list;
};

/** TBListAutoDeleteOf is a list (array) of pointers to the specified object type.
	The objects will be deleted automatically on destruction. */
template<class T>
class TBListAutoDeleteOf : public TBListOf<T>
{
public:
	~TBListAutoDeleteOf() { TBListOf<T>::DeleteAll(); }
};

}; // namespace tb

#endif // TB_LIST_H
