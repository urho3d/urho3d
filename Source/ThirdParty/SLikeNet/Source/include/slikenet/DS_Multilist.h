/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/// \file DS_Multilist.h
/// \internal
/// \brief ADT that can represent an unordered list, ordered list, stack, or queue with a common interface
///

#ifndef __MULTILIST_H
#define __MULTILIST_H 

#include "assert.h"
#include <string.h> // memmove
#include "Export.h"
#include "memoryoverride.h"
#include "NativeTypes.h"


/// What algorithm to use to store the data for the Multilist
enum MultilistType
{
	/// Removing from the middle of the list will swap the end of the list rather than shift the elements. Push and Pop operate on the tail.
	ML_UNORDERED_LIST,
	/// A normal list, with the list order preserved. Push and Pop operate on the tail.
	ML_STACK,
	/// A queue. Push and Pop operate on the head
	ML_QUEUE,
	/// A list that is always kept in order. Elements must be unique, and compare against each other consistently using <, ==, and >
	ML_ORDERED_LIST,
	/// A list whose type can change at runtime
	ML_VARIABLE_DURING_RUNTIME
};

/// The namespace DataStructures was only added to avoid compiler errors for commonly named data structures
/// As these data structures are stand-alone, you can use them outside of RakNet for your own projects if you wish.
namespace DataStructures
{
	/// Can be used with Multilist::ForEach
	/// Assuming the Multilist holds pointers, will delete those pointers
	template <class templateType>
	void DeletePtr_RakNet(templateType &ptr, const char *file, unsigned int line ) { SLNet::OP_DELETE(ptr, file, line);}

	/// Can be used with Multilist::ForEach
	/// Assuming the Multilist holds pointers, will delete those pointers
	template <class templateType>
	void DeletePtr(templateType &ptr) {delete ptr;}

	/// The following is invalid.
	/// bool operator<( const MyClass *myClass, const int &inputKey ) {return myClass->value < inputKey;}
	/// At least one type has to be a reference to a class
	/// MLKeyRef is a helper class to turn a native type into a class, so you can compare that native type against a pointer to a different class
	/// Used for he Multilist, when _DataType != _KeyType 
	template < class templateType >
	class MLKeyRef
	{
	public:
		MLKeyRef(const templateType& input) : val(input) {}
		const templateType &Get(void) const {return val;}
		bool operator<( const templateType &right ) {return val < right;}
		bool operator>( const templateType &right ) {return val > right;}
		bool operator==( const templateType &right ) {return val == right;}
	protected:
		const templateType &val;
	private:
		// MLKeyRef is not copy-assignable
		MLKeyRef& operator=(const MLKeyRef& master);
	};

	/// For the Multilist, when _DataType != _KeyType, you must define the comparison operators between the key and the data
	/// This is non-trivial due to the need to use MLKeyRef in case the type held is a pointer to a structure or class and the key type is not a class
	/// For convenience, this macro will implement the comparison operators under the following conditions
	/// 1. _DataType is a pointer to a class or structure
	/// 2. The key is a member variable of _DataType
	#define DEFINE_MULTILIST_PTR_TO_MEMBER_COMPARISONS( _CLASS_NAME_, _KEY_TYPE_, _MEMBER_VARIABLE_NAME_ ) \
	bool operator<( const DataStructures::MLKeyRef<_KEY_TYPE_> &inputKey, const _CLASS_NAME_ *cls ) {return inputKey.Get() < cls->_MEMBER_VARIABLE_NAME_;} \
	bool operator>( const DataStructures::MLKeyRef<_KEY_TYPE_> &inputKey, const _CLASS_NAME_ *cls ) {return inputKey.Get() > cls->_MEMBER_VARIABLE_NAME_;} \
	bool operator==( const DataStructures::MLKeyRef<_KEY_TYPE_> &inputKey, const _CLASS_NAME_ *cls ) {return inputKey.Get() == cls->_MEMBER_VARIABLE_NAME_;}

	typedef uint32_t DefaultIndexType;

	/// \brief The multilist, representing an abstract data type that generally holds lists.
	/// \param[in] _MultilistType What type of list this is, \sa MultilistType
	/// \param[in] _DataType What type of data this list holds.
	/// \param[in] _KeyType If a function takes a key to sort on, what type of key this is. The comparison operator between _DataType and _KeyType must be defined
	/// \param[in] _IndexType What variable type to use for indices
	template <const MultilistType _MultilistType, class _DataType, class _KeyType=_DataType, class _IndexType=DefaultIndexType>
	class RAK_DLL_EXPORT Multilist
	{
	public:
		Multilist();
		~Multilist();
		Multilist( const Multilist& source );
		Multilist& operator= ( const Multilist& source );
		_DataType& operator[] ( const _IndexType position ) const;
		/// Unordered list, stack is LIFO
		/// QUEUE is FIFO
		/// Ordered list is inserted in order
		void Push(const _DataType &d, const char *file=__FILE__, unsigned int line=__LINE__ );
		void Push(const _DataType &d, const _KeyType &key, const char *file=__FILE__, unsigned int line=__LINE__ );

		/// \brief Gets or removes and gets an element from the list, according to the same rules as Push().
		/// Ordered list is LIFO for the purposes of Pop and Peek.
		_DataType &Pop(const char *file=__FILE__, unsigned int line=__LINE__);
		_DataType &Peek(void) const;

		/// \brief Same as Push(), except FIFO and LIFO are reversed.
		/// Ordered list still inserts in order.
		void PushOpposite(const _DataType &d, const char *file=__FILE__, unsigned int line=__LINE__ );
		void PushOpposite(const _DataType &d, const _KeyType &key, const char *file=__FILE__, unsigned int line=__LINE__ );

		/// \brief Same as Pop() and Peek(), except FIFO and LIFO are reversed.
		_DataType &PopOpposite(const char *file=__FILE__, unsigned int line=__LINE__);
		_DataType &PeekOpposite(void) const;

		/// \brief Stack,Queue: Inserts at index indicated, elements are shifted. 
		/// Ordered list: Inserts, position is ignored
		void InsertAtIndex(const _DataType &d, _IndexType index, const char *file=__FILE__, unsigned int line=__LINE__);	
		
		/// \brief Unordered list, removes at index indicated, swaps last element with that element.
		/// Otherwise, array is shifted left to overwrite removed element
		/// \details Index[0] returns the same as Pop() for a queue. 
		/// Same as PopOpposite() for the list and ordered list
		void RemoveAtIndex(_IndexType position, const char *file=__FILE__, unsigned int line=__LINE__);

		/// \brief Find the index of \a key, and remove at that index.
		bool RemoveAtKey(_KeyType key, bool assertIfDoesNotExist, const char *file=__FILE__, unsigned int line=__LINE__);

		/// \brief Finds the index of \a key. Return -1 if the key is not found.
		_IndexType GetIndexOf(_KeyType key) const;

		/// \brief Returns where in the list we should insert the item, to preserve list order.
		/// Returns -1 if the item is already in the list
		_IndexType GetInsertionIndex(_KeyType key) const;

		/// \brief Finds the index of \a key. Return 0 if the key is not found. Useful if _DataType is always non-zero pointers.
		_DataType GetPtr(_KeyType key) const;

		/// \brief Iterate over the list, calling the function pointer on each element.
		void ForEach(void (*func)(_DataType &item, const char *file, unsigned int line), const char *file, unsigned int line);
		void ForEach(void (*func)(_DataType &item));	

		/// \brief Returns if the list is empty.
		bool IsEmpty(void) const;

		/// \brief Returns the number of elements used in the list.
		_IndexType GetSize(void) const;

		/// \brief Empties the list. The list is not deallocated if it is small, 
		/// unless \a deallocateSmallBlocks is true
		void Clear( bool deallocateSmallBlocks=true, const char *file=__FILE__, unsigned int line=__LINE__ );

		/// \brief Empties the list, first calling SLNet::OP_Delete on all items.
		/// \details The list is not deallocated if it is small, unless \a deallocateSmallBlocks is true
		void ClearPointers( bool deallocateSmallBlocks=true, const char *file=__FILE__, unsigned int line=__LINE__ );

		/// \brief Empty one item from the list, first calling SLNet::OP_Delete on that item.
		void ClearPointer( _KeyType key, const char *file=__FILE__, unsigned int line=__LINE__ );

		/// \brief Reverses the elements in the list, and flips the sort order 
		/// returned by GetSortOrder() if IsSorted() returns true at the time the function is called
		void ReverseList(void);

		/// \brief Reallocates the list to a larger size.
		/// If \a size is smaller than the value returned by GetSize(), the call does nothing.
		void Reallocate(_IndexType size, const char *file=__FILE__, unsigned int line=__LINE__);

		/// \brief Sorts the list unless it is an ordered list, in which it does nothing as the list is assumed to already be sorted.
		/// \details However, if \a force is true, it will also resort the ordered list, useful if the comparison operator between _KeyType and _DataType would now return different results
		/// Once the list is sorted, further operations to lookup by key will be log2(n) until the list is modified
		void Sort(bool force);

		/// \brief Sets the list to be remembered as sorted.
		/// \details Optimization if the source is sorted already
		void TagSorted(void);

		/// \brief Defaults to ascending.
		/// \details Used by Sort(), and by ML_ORDERED_LIST
		void SetSortOrder(bool ascending);

		/// \brief Returns true if ascending.
		bool GetSortOrder(void) const;

		/// \brief Returns true if the list is currently believed to be in a sorted state.
		/// \details Doesn't actually check for sortedness, just if Sort() 
		/// was recently called, or MultilistType is ML_ORDERED_LIST
		bool IsSorted(void) const;

		/// Returns what type of list this is
		MultilistType GetMultilistType(void) const;

		/// \brief Changes what type of list this is.
		/// \pre Template must be defined with ML_VARIABLE_DURING_RUNTIME for this to do anything
		/// \param[in] mlType Any value of the enum MultilistType, except ML_VARIABLE_DURING_RUNTIME
		void SetMultilistType(MultilistType newType);

		/// \brief Returns the intersection of two lists.
		/// Intersection is items common to both lists.
		static void FindIntersection(
			Multilist& source1,
			Multilist& source2, 
			Multilist& intersection,
			Multilist& uniqueToSource1,
			Multilist& uniqueToSource2);

	protected:
		void ReallocateIfNeeded(const char *file, unsigned int line);
		void DeallocateIfNeeded(const char *file, unsigned int line);
		void ReallocToSize(_IndexType newAllocationSize, const char *file, unsigned int line);
		void ReverseListInternal(void);
		void InsertInOrderedList(const _DataType &d, const _KeyType &key);
		_IndexType GetIndexFromKeyInSortedList(const _KeyType &key, bool *objectExists) const;
		void InsertShiftArrayRight(const _DataType &d, _IndexType index);
		void DeleteShiftArrayLeft(_IndexType index);
		void QSortAscending(_IndexType left, _IndexType right);
		void QSortDescending(_IndexType left, _IndexType right);
		void CopySource( const Multilist& source );

		/// An array of user values
		_DataType* data;
		
		/// Number of elements in the list 		
		_IndexType dataSize;
		
		/// Size of \a array 		
		_IndexType allocationSize;

		/// Array index for the head of the queue
		_IndexType queueHead;

		/// Array index for the tail of the queue
		_IndexType queueTail;

		/// How many bytes the user chose to preallocate
		/// Won't automatically deallocate below this
		_IndexType preallocationSize;

		enum
		{
			ML_UNSORTED,
			ML_SORTED_ASCENDING,
			ML_SORTED_DESCENDING
		} sortState;

		bool ascendingSort;

		// In case we are using the variable type multilist
		MultilistType variableMultilistType;
	};

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::Multilist()
	{
		data=0;
		dataSize=0;
		allocationSize=0;
		ascendingSort=true;
		sortState=ML_UNSORTED;
		queueHead=0;
		queueTail=0;
		preallocationSize=0;

#pragma warning( push )
#pragma warning(disable:4127)	// conditional expression is constant
		if (_MultilistType==ML_ORDERED_LIST)
			sortState=ML_SORTED_ASCENDING;
		else
			sortState=ML_UNSORTED;

		if (_MultilistType==ML_VARIABLE_DURING_RUNTIME)
			variableMultilistType=ML_UNORDERED_LIST;
#pragma warning( pop )
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::~Multilist()
	{
		if (data!=0)
			SLNet::OP_DELETE_ARRAY(data, _FILE_AND_LINE_);
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::Multilist( const Multilist& source )
	{
		CopySource(source);
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	Multilist<_MultilistType, _DataType, _KeyType, _IndexType>& Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::operator= ( const Multilist& source )
	{
		Clear(true);
		CopySource(source);
		return *this;
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::CopySource( const Multilist& source )
	{
		dataSize=source.GetSize();
		ascendingSort=source.ascendingSort;
		sortState=source.sortState;
		queueHead=0;
		queueTail=dataSize;
		preallocationSize=source.preallocationSize;
		variableMultilistType=source.variableMultilistType;
		if (source.data==0)
		{
			data=0;
			allocationSize=0;
		}
		else
		{
			allocationSize=dataSize;
			data = SLNet::OP_NEW_ARRAY<_DataType>(dataSize,_FILE_AND_LINE_);
			_IndexType i;
			for (i=0; i < dataSize; i++)
				data[i]=source[i];
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	_DataType& Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::operator[] ( const _IndexType position ) const
	{
		RakAssert(position<GetSize());

		if (GetMultilistType()==ML_QUEUE)
		{
			if ( queueHead + position >= allocationSize )
				return data[ queueHead + position - allocationSize ];
			else
				return data[ queueHead + position ];
		}
		
		return data[position];
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::Push(const _DataType &d, const char *file, unsigned int line )
	{
		Push(d,d,file,line);
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::Push(const _DataType &d, const _KeyType &key, const char *file, unsigned int line )
	{
		ReallocateIfNeeded(file,line);

		if (GetMultilistType()==ML_UNORDERED_LIST || GetMultilistType()==ML_STACK)
		{
			data[dataSize]=d;
			dataSize++;
		}
		else if (GetMultilistType()==ML_QUEUE)
		{
			data[queueTail++] = d;

			if ( queueTail == allocationSize )
				queueTail = 0;
			dataSize++;
		}
		else
		{
			RakAssert(GetMultilistType()==ML_ORDERED_LIST);
			InsertInOrderedList(d,key);
		}

		if (GetMultilistType()==ML_UNORDERED_LIST || GetMultilistType()==ML_STACK || GetMultilistType()==ML_QUEUE)
		{
			// Break sort if no longer sorted
			if (sortState!=ML_UNSORTED && dataSize>1)
			{
				if (ascendingSort)
				{
					if ( MLKeyRef<_KeyType>(key) < operator[](dataSize-2) )
						sortState=ML_UNSORTED;
				}
				else
				{
					if ( MLKeyRef<_KeyType>(key) > operator[](dataSize-2) )
						sortState=ML_UNSORTED;
				}

				sortState=ML_UNSORTED;
			}
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	_DataType &Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::Pop(const char *file, unsigned int line)
	{
		RakAssert(IsEmpty()==false);
		DeallocateIfNeeded(file,line);
		if (GetMultilistType()==ML_UNORDERED_LIST || GetMultilistType()==ML_STACK || GetMultilistType()==ML_ORDERED_LIST)
		{
			dataSize--;
			return data[dataSize];
		}
		else
		{
			RakAssert(GetMultilistType()==ML_QUEUE);

			if ( ++queueHead == allocationSize )
				queueHead = 0;

			if ( queueHead == 0 )
				return data[ allocationSize -1 ];

			dataSize--;
			return data[ queueHead -1 ];
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	_DataType &Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::Peek(void) const
	{
		RakAssert(IsEmpty()==false);
		if (GetMultilistType()==ML_UNORDERED_LIST || GetMultilistType()==ML_STACK || GetMultilistType()==ML_ORDERED_LIST)
		{
			return data[dataSize-1];
		}
		else
		{
			RakAssert(GetMultilistType()==ML_QUEUE);
			return data[ queueHead ];
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::PushOpposite(const _DataType &d, const char *file, unsigned int line )
	{
		PushOpposite(d,d,file,line);
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::PushOpposite(const _DataType &d, const _KeyType &key, const char *file, unsigned int line )
	{
		ReallocateIfNeeded(file,line);

		// Unordered list Push at back
		if (GetMultilistType()==ML_UNORDERED_LIST)
		{
			data[dataSize]=d;
			dataSize++;
		}
		else if (GetMultilistType()==ML_STACK)
		{
			// Stack push at front of the list, instead of back as normal
			InsertAtIndex(d,0,file,line);
		}
		else if (GetMultilistType()==ML_QUEUE)
		{
			// Queue push at front of the list, instead of back as normal
			InsertAtIndex(d,0,file,line);
		}
		else
		{
			RakAssert(GetMultilistType()==ML_ORDERED_LIST);
			InsertInOrderedList(d,key);
		}

		if (GetMultilistType()==ML_UNORDERED_LIST || GetMultilistType()==ML_STACK || GetMultilistType()==ML_QUEUE)
		{
			// Break sort if no longer sorted
			if (sortState!=ML_UNSORTED && dataSize>1)
			{
				if (ascendingSort)
				{
					if ( MLKeyRef<_KeyType>(key) > operator[](1) )
						sortState=ML_UNSORTED;
				}
				else
				{
					if ( MLKeyRef<_KeyType>(key) < operator[](1) )
						sortState=ML_UNSORTED;
				}
			}
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	_DataType &Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::PopOpposite(const char *file, unsigned int line)
	{
		RakAssert(IsEmpty()==false);
		if (GetMultilistType()==ML_UNORDERED_LIST || GetMultilistType()==ML_STACK || GetMultilistType()==ML_ORDERED_LIST)
		{
			// Copy leftmost to end
			ReallocateIfNeeded(file,line);
			data[dataSize]=data[0];
			DeleteShiftArrayLeft(0);
			--dataSize;
			// Assuming still leaves at least one element past the end of the list allocated
			DeallocateIfNeeded(file,line);
			// Return end
			return data[dataSize+1];
		}
		else
		{
			RakAssert(GetMultilistType()==ML_QUEUE);
			// Deallocate first, since we are returning off the existing list
			DeallocateIfNeeded(file,line);
			dataSize--;

			if (queueTail==0)
				queueTail=allocationSize-1;
			else
				--queueTail;

			return data[queueTail];
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	_DataType &Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::PeekOpposite(void) const
	{
		RakAssert(IsEmpty()==false);
		if (GetMultilistType()==ML_UNORDERED_LIST || GetMultilistType()==ML_STACK || GetMultilistType()==ML_ORDERED_LIST)
		{
			return data[0];
		}
		else
		{
			RakAssert(GetMultilistType()==ML_QUEUE);
			_IndexType priorIndex;
			if (queueTail==0)
				priorIndex=allocationSize-1;
			else
				priorIndex=queueTail-1;

			return data[priorIndex];
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::InsertAtIndex(const _DataType &d, _IndexType index, const char *file, unsigned int line)
	{
		ReallocateIfNeeded(file,line);

		if (GetMultilistType()==ML_UNORDERED_LIST || GetMultilistType()==ML_STACK || GetMultilistType()==ML_ORDERED_LIST)
		{
			if (index>=dataSize)
			{
				// insert at end
				data[dataSize]=d;

				dataSize++;
			}
			else
			{
				// insert at index
				InsertShiftArrayRight(d,index);
			}
		}
		else
		{
			data[queueTail++] = d;

			if ( queueTail == allocationSize )
				queueTail = 0;

			++dataSize;

			if (dataSize==1)
				return;

			_IndexType writeIndex, readIndex, trueWriteIndex, trueReadIndex;
			writeIndex=dataSize-1;
			readIndex=writeIndex-1;
			while (readIndex >= index)
			{
				if ( queueHead + writeIndex >= allocationSize )
					trueWriteIndex = queueHead + writeIndex - allocationSize;
				else
					trueWriteIndex = queueHead + writeIndex;

				if ( queueHead + readIndex >= allocationSize )
					trueReadIndex = queueHead + readIndex - allocationSize;
				else
					trueReadIndex = queueHead + readIndex;

				data[trueWriteIndex]=data[trueReadIndex];

				if (readIndex==0)
					break;
				writeIndex--;
				readIndex--;
			}

			if ( queueHead + index >= allocationSize )
				trueWriteIndex = queueHead + index - allocationSize;
			else
				trueWriteIndex = queueHead + index;

			data[trueWriteIndex]=d;
		}

		// #med - use different approach here (template specialization?)
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4127) // conditional expression is constant
#endif
		if (_MultilistType != ML_ORDERED_LIST)
#ifdef _MSC_VER
#pragma warning(pop)
#endif
			sortState=ML_UNSORTED;
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::RemoveAtIndex(_IndexType position, const char *file, unsigned int line)
	{
		RakAssert(position < dataSize);
		RakAssert(IsEmpty()==false);

		if (GetMultilistType()==ML_UNORDERED_LIST)
		{
			// Copy tail to current
			data[position]=data[dataSize-1];
		}
		else if (GetMultilistType()==ML_STACK || GetMultilistType()==ML_ORDERED_LIST)
		{
			DeleteShiftArrayLeft(position);
		}
		else
		{
			RakAssert(GetMultilistType()==ML_QUEUE);

			_IndexType index, next;

			if ( queueHead + position >= allocationSize )
				index = queueHead + position - allocationSize;
			else
				index = queueHead + position;

			next = index + 1;

			if ( next == allocationSize )
				next = 0;

			while ( next != queueTail )
			{
				// Overwrite the previous element
				data[ index ] = data[ next ];
				index = next;
				//next = (next + 1) % allocationSize;

				if ( ++next == allocationSize )
					next = 0;
			}

			// Move the queueTail back
			if ( queueTail == 0 )
				queueTail = allocationSize - 1;
			else
				--queueTail;
		}
		
		
		dataSize--;
		DeallocateIfNeeded(file,line);
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	bool Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::RemoveAtKey(_KeyType key, bool assertIfDoesNotExist, const char *file, unsigned int line)
	{
		_IndexType index = GetIndexOf(key);
		if (index==(_IndexType)-1)
		{
			RakAssert(assertIfDoesNotExist==false && "RemoveAtKey element not found");
			return false;
		}
		RemoveAtIndex(index,file,line);
		return true;
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	_IndexType Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::GetIndexOf(_KeyType key) const
	{
		_IndexType i;
		if (IsSorted())
		{
			bool objectExists;
			i=GetIndexFromKeyInSortedList(key, &objectExists);
			if (objectExists)
				return i;
			return (_IndexType)-1;
		}
		else if (GetMultilistType()==ML_UNORDERED_LIST || GetMultilistType()==ML_STACK)
		{
			for (i=0; i < dataSize; i++)
			{
				if (MLKeyRef<_KeyType>(key)==data[i])
					return i;
			}
			return (_IndexType)-1;
		}
		else
		{
			RakAssert( GetMultilistType()==ML_QUEUE );

			for (i=0; i < dataSize; i++)
			{
				if (MLKeyRef<_KeyType>(key)==operator[](i))
					return i;
			}
			return (_IndexType)-1;
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	_IndexType Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::GetInsertionIndex(_KeyType key) const
	{
		_IndexType i;
		if (IsSorted())
		{
			bool objectExists;
			i=GetIndexFromKeyInSortedList(key, &objectExists);
			if (objectExists)
				return (_IndexType)-1;
			return i;
		}
		else if (GetMultilistType()==ML_UNORDERED_LIST || GetMultilistType()==ML_STACK)
		{
			for (i=0; i < dataSize; i++)
			{
				if (MLKeyRef<_KeyType>(key)==data[i])
					return (_IndexType)-1;
			}
			return dataSize;
		}
		else
		{
			RakAssert( GetMultilistType()==ML_QUEUE );

			for (i=0; i < dataSize; i++)
			{
				if (MLKeyRef<_KeyType>(key)==operator[](i))
					return (_IndexType)-1;
			}
			return dataSize;
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	_DataType Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::GetPtr(_KeyType key) const
	{
		_IndexType i = GetIndexOf(key);
		if (i==(_IndexType)-1)
			return 0;
		return data[i];
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::ForEach(void (*func)(_DataType &item, const char *file, unsigned int line), const char *file, unsigned int line)
	{
		_IndexType i;
		for (i=0; i < dataSize; i++)
			func(operator[](i), file, line);
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::ForEach(void (*func)(_DataType &item))
	{
		_IndexType i;
		for (i=0; i < dataSize; i++)
			func(operator[](i));
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	bool Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::IsEmpty(void) const
	{
		return dataSize==0;
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	_IndexType Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::GetSize(void) const
	{
		return dataSize;
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::Clear( bool deallocateSmallBlocks, const char *file, unsigned int line )
	{
		dataSize=0;
		if (GetMultilistType()==ML_ORDERED_LIST)
			if (ascendingSort)
				sortState=ML_SORTED_ASCENDING;
			else
				sortState=ML_SORTED_DESCENDING;
		else
			sortState=ML_UNSORTED;
		queueHead=0;
		queueTail=0;

		if (deallocateSmallBlocks && allocationSize < 128 && data)
		{
			SLNet::OP_DELETE_ARRAY(data,file,line);
			data=0;
			allocationSize=0;
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::ClearPointers( bool deallocateSmallBlocks, const char *file, unsigned int line )
	{
		_IndexType i;
		for (i=0; i < dataSize; i++)
			SLNet::OP_DELETE(operator[](i), file, line);
		Clear(deallocateSmallBlocks, file, line);
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::ClearPointer( _KeyType key, const char *file, unsigned int line )
	{
		_IndexType i;
		i = GetIndexOf(key);
		if (i!=-1)
		{
			SLNet::OP_DELETE(operator[](i), file, line);
			RemoveAtIndex(i);
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::ReverseList(void)
	{
		if (IsSorted())
			ascendingSort=!ascendingSort;

		ReverseListInternal();
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::Reallocate(_IndexType size, const char *file, unsigned int line)
	{
		_IndexType newAllocationSize;
		if (size < dataSize)
			newAllocationSize=dataSize;
		else
			newAllocationSize=size;
		preallocationSize=size;
		ReallocToSize(newAllocationSize,file,line);
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::Sort(bool force)
	{
		if (IsSorted() && force==false)
			return;

		if (dataSize>1)
		{
			if (ascendingSort)
				QSortAscending(0,dataSize-1);		
			else
				QSortDescending(0,dataSize-1);
		}

		TagSorted();
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::TagSorted(void)
	{
		if (ascendingSort)
			sortState=ML_SORTED_ASCENDING;
		else
			sortState=ML_SORTED_DESCENDING;
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::QSortAscending(_IndexType leftEdge, _IndexType rightEdge)
	{
		_DataType temp;
		_IndexType left=leftEdge;
		_IndexType right=rightEdge;
		_IndexType pivotIndex=left++;

		while (left<right)
		{
			if (data[left] <= data[pivotIndex])
			{
				++left;
			}
			else
			{
				temp=data[left];
				data[left]=data[right];
				data[right]=temp;
				--right;
			}
		}

		temp=data[pivotIndex];

		// Move pivot to center
		if (data[left] > data[pivotIndex])
		{
			--left;

			data[pivotIndex]=data[left];
			data[left]=temp;
		}
		else
		{
			data[pivotIndex]=data[left];
			data[left]=temp;

			--left;
		}

		if (left!=leftEdge)
			QSortAscending(leftEdge, left);

		if (right!=rightEdge)
			QSortAscending(right, rightEdge);		
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::QSortDescending(_IndexType leftEdge, _IndexType rightEdge)
	{
		_DataType temp;
		_IndexType left=leftEdge;
		_IndexType right=rightEdge;
		_IndexType pivotIndex=left++;

		while (left<right)
		{
			if (data[left] >= data[pivotIndex])
			{
				++left;
			}
			else
			{
				temp=data[left];
				data[left]=data[right];
				data[right]=temp;
				--right;
			}
		}

		temp=data[pivotIndex];

		// Move pivot to center
		if (data[left] < data[pivotIndex])
		{
			--left;

			data[pivotIndex]=data[left];
			data[left]=temp;
		}
		else
		{
			data[pivotIndex]=data[left];
			data[left]=temp;

			--left;
		}

		if (left!=leftEdge)
			QSortDescending(leftEdge, left);

		if (right!=rightEdge)
			QSortDescending(right, rightEdge);		
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::SetSortOrder(bool ascending)
	{
		if (ascendingSort!=ascending && IsSorted())
		{
			ascendingSort=ascending;
			// List is sorted, and the sort order has changed. So reverse the list
			ReverseListInternal();
		}
		else
			ascendingSort=ascending;
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	bool Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::GetSortOrder(void) const
	{
		return ascendingSort;
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	bool Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::IsSorted(void) const
	{
		return GetMultilistType()==ML_ORDERED_LIST || sortState!=ML_UNSORTED;
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	MultilistType Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::GetMultilistType(void) const
	{
#pragma warning( push )
#pragma warning(disable:4127)	// conditional expression is constant
		if (_MultilistType==ML_VARIABLE_DURING_RUNTIME)
#pragma warning( pop )
			return variableMultilistType;
		return _MultilistType;
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::SetMultilistType(MultilistType newType)
	{
		RakAssert(_MultilistType==ML_VARIABLE_DURING_RUNTIME);
		switch (variableMultilistType)
		{
		case ML_UNORDERED_LIST:
			switch (newType)
			{
			case ML_UNORDERED_LIST:
				// No change
				break;
			case ML_STACK:
				// Same data format
				break;
			case ML_QUEUE:
				queueHead=0;
				queueTail=dataSize;
				break;
			case ML_ORDERED_LIST:
				Sort(false);
				break;
			}
			break;
		case ML_STACK:
			switch (newType)
			{
			case ML_UNORDERED_LIST:
				// Same data format
				break;
			case ML_STACK:
				// No change
				break;
			case ML_QUEUE:
				queueHead=0;
				queueTail=dataSize;
				break;
			case ML_ORDERED_LIST:
				Sort(false);
				break;
			}
			break;
		case ML_QUEUE:
			switch (newType)
			{
			case ML_UNORDERED_LIST:
			case ML_STACK:
			case ML_ORDERED_LIST:
				if (queueTail < queueHead)
				{
					// Realign data if wrapped
					ReallocToSize(dataSize, _FILE_AND_LINE_);
				}
				else
				{
					// Else can just copy starting at head
					_IndexType i;
					for (i=0; i < dataSize; i++)
						data[i]=operator[](i);
				}
				if (newType==ML_ORDERED_LIST)
					Sort(false);
				break;
			case ML_QUEUE:
				// No change
				break;
			}
			break;
		case ML_ORDERED_LIST:
			switch (newType)
			{
			case ML_UNORDERED_LIST:
			case ML_STACK:
			case ML_QUEUE:
				// Same data format
				// Tag as sorted
				if (ascendingSort)
					sortState=ML_SORTED_ASCENDING;
				else
					sortState=ML_SORTED_DESCENDING;
				if (newType==ML_QUEUE)
				{
					queueHead=0;
					queueTail=dataSize;
				}
				break;
			case ML_ORDERED_LIST:
				// No change
				break;
			}
			break;
		}

		variableMultilistType=newType;
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::FindIntersection(
		Multilist& source1,
		Multilist& source2, 
		Multilist& intersection,
		Multilist& uniqueToSource1,
		Multilist& uniqueToSource2)
	{
		_IndexType index1=0, index2=0;
		source1.SetSortOrder(true);
		source2.SetSortOrder(true);
		source1.Sort(false);
		source2.Sort(false);
		intersection.Clear(true,_FILE_AND_LINE_);
		uniqueToSource1.Clear(true,_FILE_AND_LINE_);
		uniqueToSource2.Clear(true,_FILE_AND_LINE_);
		
		while (index1 < source1.GetSize() && index2 < source2.GetSize())
		{
			if (source1[index1]<source2[index2])
			{
				uniqueToSource1.Push(source1[index1],_FILE_AND_LINE_);
				index1++;
			}
			else if (source1[index1]==source2[index2])
			{
				intersection.Push(source1[index1],_FILE_AND_LINE_);
				index1++;
				index2++;
			}
			else
			{
				uniqueToSource2.Push(source2[index2],_FILE_AND_LINE_);
				index2++;
			}
		}
		while (index1 < source1.GetSize())
		{
			uniqueToSource1.Push(source1[index1],_FILE_AND_LINE_);
			index1++;
		}
		while (index2 < source2.GetSize())
		{
			uniqueToSource2.Push(source2[index2],_FILE_AND_LINE_);
			index2++;
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::ReallocateIfNeeded(const char *file, unsigned int line)
	{
		if (dataSize<allocationSize)
			return;

		_IndexType newAllocationSize;
		if (allocationSize<16)
			newAllocationSize=32;
		else if (allocationSize>65536)
			newAllocationSize=allocationSize+65536;
		else
		{
			newAllocationSize=allocationSize<<1; // * 2
			// Protect against underflow
			if (newAllocationSize < allocationSize)
				newAllocationSize=allocationSize+65536;
		}

		ReallocToSize(newAllocationSize,file,line);
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::DeallocateIfNeeded(const char *file, unsigned int line)
	{
		if (allocationSize<512)
			return;
		if (dataSize >= allocationSize/3 )
			return;
		if (dataSize <= preallocationSize )
			return;
		
		_IndexType newAllocationSize = dataSize<<1; // * 2

		ReallocToSize(newAllocationSize,file,line);
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::ReallocToSize(_IndexType newAllocationSize, const char *file, unsigned int line)
	{
		_DataType* newData = SLNet::OP_NEW_ARRAY<_DataType>(newAllocationSize,file,line);
		_IndexType i;
		for (i=0; i < dataSize; i++)
			newData[i]=operator[](i);
		if (dataSize>0)
		{
			SLNet::OP_DELETE_ARRAY(data,file,line);
			if (GetMultilistType()==ML_QUEUE)
			{
				queueHead=0;
				queueTail=dataSize;
			}
		}
		data=newData;
		allocationSize=newAllocationSize;
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::ReverseListInternal(void)
	{
		_DataType temp;
		_IndexType i;
		for (i=0; i < dataSize/2; i++)
		{
			temp=operator[](i);
			operator[](i)=operator[](dataSize-1-i);
			operator[](dataSize-1-i)=temp;
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::InsertInOrderedList(const _DataType &d, const _KeyType &key)
	{
		RakAssert(GetMultilistType()==ML_ORDERED_LIST);

		bool objectExists;
		_IndexType index;
		index = GetIndexFromKeyInSortedList(key, &objectExists);

	//	if (objectExists)
	//	{
			// Ordered list only allows unique insertions
	//		RakAssert("Duplicate insertion into ordered list" && false);
	//		return;
	//	}

		if (index>=dataSize)
		{
			// insert at end
			data[dataSize]=d;
			dataSize++;
		}
		else
		{
			// insert at index
			InsertShiftArrayRight(d,index);
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	_IndexType Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::GetIndexFromKeyInSortedList(const _KeyType &key, bool *objectExists) const
	{
		RakAssert(IsSorted());
		_IndexType index, upperBound, lowerBound;

		if (dataSize==0)
		{
			*objectExists=false;
			return 0;
		}

		upperBound=dataSize-1;
		lowerBound=0;
		index = dataSize/2;

		for(;;)
		{
			if (MLKeyRef<_KeyType>(key) > operator[](index) )
			{
				if (ascendingSort)
					lowerBound=index+1;
				else
					upperBound=index-1;
			}
			else if (MLKeyRef<_KeyType>(key) < operator[](index) )
			{
				if (ascendingSort)
					upperBound=index-1;
				else
					lowerBound=index+1;
			}
			else
			{
				// ==
				*objectExists=true;
				return index;
			}

			index=lowerBound+(upperBound-lowerBound)/2;

			if (lowerBound>upperBound || upperBound==(_IndexType)-1)
			{
				*objectExists=false;
				return lowerBound; // No match
			}
		}
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::InsertShiftArrayRight(const _DataType &d, _IndexType index)
	{
		RakAssert(_MultilistType!=ML_QUEUE);

		// Move the elements in the list to make room
		_IndexType i;
		for ( i = dataSize; i != index; i-- )
			data[ i ] = data[ i - 1 ];

		// Insert the new item at the correct spot
		data[ index ] = d;

		++dataSize;
	}

	template <const MultilistType _MultilistType, class _DataType, class _KeyType, class _IndexType>
	void Multilist<_MultilistType, _DataType, _KeyType, _IndexType>::DeleteShiftArrayLeft( _IndexType index )
	{
		RakAssert(index < dataSize);
		RakAssert(_MultilistType!=ML_QUEUE);

		_IndexType i;
		for ( i = index; i < dataSize-1; i++ )
			data[i]=data[i+1];
	}
};

/*
struct KeyAndValue
{
	int key;
	short value;
};

DEFINE_MULTILIST_PTR_TO_MEMBER_COMPARISONS(KeyAndValue,int,key)

void MultilistUnitTest(void)
{
	DataStructures::DefaultIndexType oldSize;
	DataStructures::Multilist<ML_UNORDERED_LIST, int> ml1;
	ml1.Reallocate(64);
	RakAssert(ml1.IsEmpty());
	ml1.Push(53);
	RakAssert(ml1.Peek()==53);
	RakAssert(ml1.IsEmpty()==false);
	RakAssert(ml1.Pop()==53);
	RakAssert(ml1.IsEmpty()==true);
	for (int i=0; i < 512; i++)
	ml1.Push(i);
	RakAssert(ml1.GetIndexOf(200)==200);
	RakAssert(ml1.PeekOpposite()==0);
	RakAssert(ml1.PopOpposite()==0);
	RakAssert(ml1.PeekOpposite()==1);
	RakAssert(ml1.Peek()==511);
	ml1.ReverseList();
	for (int i=0; i < 511; i++)
	RakAssert(ml1[i]==511-i);
	RakAssert(ml1.PeekOpposite()==511);
	RakAssert(ml1.Peek()==1);
	oldSize = ml1.GetSize();
	ml1.RemoveAtIndex(0);
	RakAssert(ml1.GetSize()==oldSize-1);
	RakAssert(ml1.PeekOpposite()==1);
	ml1.Clear(_FILE_AND_LINE_);
	RakAssert(ml1.IsEmpty()==true);

	ml1.Sort(true);
	ml1.Clear(_FILE_AND_LINE_);

	ml1.Push(100);
	ml1.Sort(true);
	ml1.Clear(_FILE_AND_LINE_);

	ml1.Push(50);
	ml1.Push(100);
	ml1.Sort(true);
	ml1.Clear(_FILE_AND_LINE_);

	ml1.Push(100);
	ml1.Push(50);
	ml1.Sort(true);
	ml1.Clear(_FILE_AND_LINE_);

	ml1.Push(100);
	ml1.Push(50);
	ml1.Push(150);
	ml1.Push(25);
	ml1.Push(175);
	ml1.Sort(true);
	RakAssert(ml1[0]==25);
	RakAssert(ml1[1]==50);
	RakAssert(ml1[2]==100);
	RakAssert(ml1[3]==150);
	RakAssert(ml1[4]==175);
	RakAssert(ml1.GetIndexOf(25)==0);
	RakAssert(ml1.GetIndexOf(50)==1);
	RakAssert(ml1.GetIndexOf(100)==2);
	RakAssert(ml1.GetIndexOf(150)==3);
	RakAssert(ml1.GetIndexOf(175)==4);
	ml1.Clear(_FILE_AND_LINE_);

	ml1.Push(1);
	ml1.Push(2);
	ml1.Push(3);
	ml1.Push(4);
	ml1.Push(5);
	ml1.Sort(true);
	RakAssert(ml1[0]==1);
	RakAssert(ml1[1]==2);
	RakAssert(ml1[2]==3);
	RakAssert(ml1[3]==4);
	RakAssert(ml1[4]==5);
	RakAssert(ml1.GetIndexOf(1)==0);
	RakAssert(ml1.GetIndexOf(2)==1);
	RakAssert(ml1.GetIndexOf(3)==2);
	RakAssert(ml1.GetIndexOf(4)==3);
	RakAssert(ml1.GetIndexOf(5)==4);
	ml1.Clear(_FILE_AND_LINE_);

	ml1.Push(5);
	ml1.Push(4);
	ml1.Push(3);
	ml1.Push(2);
	ml1.Push(1);
	ml1.Sort(true);
	RakAssert(ml1[0]==1);
	RakAssert(ml1[1]==2);
	RakAssert(ml1[2]==3);
	RakAssert(ml1[3]==4);
	RakAssert(ml1[4]==5);
	RakAssert(ml1.GetIndexOf(1)==0);
	RakAssert(ml1.GetIndexOf(2)==1);
	RakAssert(ml1.GetIndexOf(3)==2);
	RakAssert(ml1.GetIndexOf(4)==3);
	RakAssert(ml1.GetIndexOf(5)==4);
	ml1.Sort(true);
	RakAssert(ml1[0]==1);
	RakAssert(ml1[1]==2);
	RakAssert(ml1[2]==3);
	RakAssert(ml1[3]==4);
	RakAssert(ml1[4]==5);
	RakAssert(ml1.GetIndexOf(1)==0);
	RakAssert(ml1.GetIndexOf(2)==1);
	RakAssert(ml1.GetIndexOf(3)==2);
	RakAssert(ml1.GetIndexOf(4)==3);
	RakAssert(ml1.GetIndexOf(5)==4);
	ml1.Clear(_FILE_AND_LINE_);

	DataStructures::Multilist<ML_STACK, int> ml2;
	ml2.Reallocate(64);
	RakAssert(ml2.IsEmpty());
	ml2.Push(53);
	RakAssert(ml2.Peek()==53);
	RakAssert(ml2.IsEmpty()==false);
	RakAssert(ml2.Pop()==53);
	RakAssert(ml2.IsEmpty()==true);
	for (int i=0; i < 512; i++)
	ml2.Push(i);
	RakAssert(ml2.GetIndexOf(200)==200);
	RakAssert(ml2.PeekOpposite()==0);
	RakAssert(ml2.PopOpposite()==0);
	RakAssert(ml2.PeekOpposite()==1);
	RakAssert(ml2.Peek()==511);
	ml2.ReverseList();
	for (int i=0; i < 511; i++)
	RakAssert(ml2[i]==511-i);
	RakAssert(ml2.PeekOpposite()==511);
	RakAssert(ml2.Peek()==1);
	oldSize = ml2.GetSize();
	ml2.RemoveAtIndex(0);
	RakAssert(ml2.GetSize()==oldSize-1);
	RakAssert(ml2.Peek()==1);
	RakAssert(ml2.PeekOpposite()==510);
	ml2.Clear(_FILE_AND_LINE_);
	RakAssert(ml2.IsEmpty()==true);

	DataStructures::Multilist<ML_QUEUE, int> ml3;
	RakAssert(ml3.IsEmpty());
	ml3.Push(53);
	RakAssert(ml3.Peek()==53);
	RakAssert(ml3.IsEmpty()==false);
	RakAssert(ml3.Pop()==53);
	RakAssert(ml3.IsEmpty()==true);
	for (int i=0; i < 512; i++)
	ml3.Push(i);
	RakAssert(ml3.GetIndexOf(200)==200);
	RakAssert(ml3.PeekOpposite()==511);
	RakAssert(ml3.PopOpposite()==511);
	RakAssert(ml3.PeekOpposite()==510);
	RakAssert(ml3.Peek()==0);
	ml3.ReverseList();
	for (int i=0; i < 511; i++)
	RakAssert(ml3[i]==511-1-i);
	RakAssert(ml3.PeekOpposite()==0);
	RakAssert(ml3.Peek()==510);
	oldSize = ml3.GetSize();
	ml3.RemoveAtIndex(0);
	RakAssert(ml3.GetSize()==oldSize-1);
	RakAssert(ml3.Peek()==509);
	RakAssert(ml3.PeekOpposite()==0);
	ml3.Clear(_FILE_AND_LINE_);
	RakAssert(ml3.IsEmpty()==true);

	ml3.PushOpposite(100);
	ml3.PushOpposite(50);
	ml3.PushOpposite(150);
	ml3.PushOpposite(25);
	ml3.PushOpposite(175);
	ml3.Sort(true);
	RakAssert(ml3[0]==25);
	RakAssert(ml3[1]==50);
	RakAssert(ml3[2]==100);
	RakAssert(ml3[3]==150);
	RakAssert(ml3[4]==175);
	RakAssert(ml3.GetIndexOf(25)==0);
	RakAssert(ml3.GetIndexOf(50)==1);
	RakAssert(ml3.GetIndexOf(100)==2);
	RakAssert(ml3.GetIndexOf(150)==3);
	RakAssert(ml3.GetIndexOf(175)==4);
	ml3.Clear(_FILE_AND_LINE_);

	ml3.PushOpposite(1);
	ml3.PushOpposite(2);
	ml3.PushOpposite(3);
	ml3.PushOpposite(4);
	ml3.PushOpposite(5);
	ml3.Sort(true);
	RakAssert(ml3[0]==1);
	RakAssert(ml3[1]==2);
	RakAssert(ml3[2]==3);
	RakAssert(ml3[3]==4);
	RakAssert(ml3[4]==5);
	RakAssert(ml3.GetIndexOf(1)==0);
	RakAssert(ml3.GetIndexOf(2)==1);
	RakAssert(ml3.GetIndexOf(3)==2);
	RakAssert(ml3.GetIndexOf(4)==3);
	RakAssert(ml3.GetIndexOf(5)==4);
	ml3.Clear(_FILE_AND_LINE_);

	ml3.PushOpposite(5);
	ml3.PushOpposite(4);
	ml3.PushOpposite(3);
	ml3.PushOpposite(2);
	ml3.PushOpposite(1);
	ml3.Sort(true);
	RakAssert(ml3[0]==1);
	RakAssert(ml3[1]==2);
	RakAssert(ml3[2]==3);
	RakAssert(ml3[3]==4);
	RakAssert(ml3[4]==5);
	RakAssert(ml3.GetIndexOf(1)==0);
	RakAssert(ml3.GetIndexOf(2)==1);
	RakAssert(ml3.GetIndexOf(3)==2);
	RakAssert(ml3.GetIndexOf(4)==3);
	RakAssert(ml3.GetIndexOf(5)==4);
	ml3.Sort(true);
	RakAssert(ml3[0]==1);
	RakAssert(ml3[1]==2);
	RakAssert(ml3[2]==3);
	RakAssert(ml3[3]==4);
	RakAssert(ml3[4]==5);
	RakAssert(ml3.GetIndexOf(1)==0);
	RakAssert(ml3.GetIndexOf(2)==1);
	RakAssert(ml3.GetIndexOf(3)==2);
	RakAssert(ml3.GetIndexOf(4)==3);
	RakAssert(ml3.GetIndexOf(5)==4);

	ml3.SetSortOrder(false);
	ml3.Sort(false);
	RakAssert(ml3[0]==5);
	RakAssert(ml3[1]==4);
	RakAssert(ml3[2]==3);
	RakAssert(ml3[3]==2);
	RakAssert(ml3[4]==1);
	RakAssert(ml3.GetIndexOf(1)==4);
	RakAssert(ml3.GetIndexOf(2)==3);
	RakAssert(ml3.GetIndexOf(3)==2);
	RakAssert(ml3.GetIndexOf(4)==1);
	RakAssert(ml3.GetIndexOf(5)==0);

	ml3.Clear(_FILE_AND_LINE_);

	DataStructures::Multilist<ML_ORDERED_LIST, int> ml4;
	ml4.Reallocate(64);
	RakAssert(ml4.IsEmpty());
	ml4.Push(53);
	RakAssert(ml4.Peek()==53);
	RakAssert(ml4.IsEmpty()==false);
	RakAssert(ml4.Pop()==53);
	RakAssert(ml4.IsEmpty()==true);
	for (int i=0; i < 512; i++)
	ml4.Push(i);
	RakAssert(ml4.GetIndexOf(200)==200);
	RakAssert(ml4.PeekOpposite()==0);
	RakAssert(ml4.PopOpposite()==0);
	RakAssert(ml4.PeekOpposite()==1);
	RakAssert(ml4.Peek()==511);
	ml4.ReverseList();
	for (int i=0; i < 511; i++)
	RakAssert(ml4[i]==511-i);
	RakAssert(ml4.PeekOpposite()==511);
	RakAssert(ml4.Peek()==1);
	oldSize = ml4.GetSize();
	ml4.RemoveAtIndex(0);
	RakAssert(ml4.GetSize()==oldSize-1);
	RakAssert(ml4.Peek()==1);
	RakAssert(ml4.PeekOpposite()==510);
	ml4.Clear(_FILE_AND_LINE_);
	RakAssert(ml4.IsEmpty()==true);

	DataStructures::Multilist<ML_ORDERED_LIST, KeyAndValue*, int> ml5;

	for (int i=0; i < 16; i++)
	{
		KeyAndValue *kav = new KeyAndValue;
		kav->key=i;
		kav->value=i+100;
		ml5.Push(kav,kav->key);
	}

	RakAssert(ml5.GetIndexOf(0)==0);
	RakAssert(ml5.GetIndexOf(5)==5);
	RakAssert(ml5.GetIndexOf(15)==15);
	RakAssert(ml5.GetIndexOf(16)==-1);
	ml5.RemoveAtKey(0,true);
	RakAssert(ml5.GetIndexOf(1)==0);
	KeyAndValue *iPtr = ml5.GetPtr(5);
	RakAssert(iPtr);
	RakAssert(iPtr->value=105);
	iPtr = ml5.GetPtr(1234);
	RakAssert(iPtr==0);
	ml5.ForEach(DataStructures::DeletePtr<KeyAndValue*>);


	DataStructures::Multilist<ML_VARIABLE_DURING_RUNTIME, int> ml6;
	ml6.Push(2);
	ml6.Push(1);
	ml6.Push(6);
	ml6.Push(3);
	RakAssert(ml6.Peek()==3);
	ml6.SetMultilistType(ML_STACK);
	RakAssert(ml6.Peek()==3);
	ml6.SetMultilistType(ML_QUEUE);
	RakAssert(ml6.Peek()==2);
	ml6.SetMultilistType(ML_ORDERED_LIST);
	RakAssert(ml6.Peek()=6);
	ml6.SetMultilistType(ML_STACK);
	RakAssert(ml6.Peek()==6);
	ml6.SetMultilistType(ML_QUEUE);
	RakAssert(ml6.Peek()==1);
}

*/

#endif
