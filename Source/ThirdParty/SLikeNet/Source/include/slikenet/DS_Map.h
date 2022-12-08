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

/// \file DS_Map.h
/// \internal
/// \brief Map
///


#ifndef __RAKNET_MAP_H
#define __RAKNET_MAP_H

#include "DS_OrderedList.h"
#include "Export.h"
#include "memoryoverride.h"
#include "assert.h"

// If I want to change this to a red-black tree, this is a good site: http://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html
// This makes insertions and deletions faster.  But then traversals are slow, while they are currently fast.

/// The namespace DataStructures was only added to avoid compiler errors for commonly named data structures
/// As these data structures are stand-alone, you can use them outside of RakNet for your own projects if you wish.
namespace DataStructures
{
	/// The default comparison has to be first so it can be called as a default parameter.
	/// It then is followed by MapNode, followed by NodeComparisonFunc
	template <class key_type>
		int defaultMapKeyComparison(const key_type &a, const key_type &b)
	{
		if (a<b) return -1; if (a==b) return 0; return 1;
	}

	/// \note IMPORTANT! If you use defaultMapKeyComparison then call IMPLEMENT_DEFAULT_COMPARISON or you will get an unresolved external linker error.
	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&, const key_type&)=defaultMapKeyComparison<key_type> >
	class RAK_DLL_EXPORT Map
	{
	public:
		static void IMPLEMENT_DEFAULT_COMPARISON(void) {DataStructures::defaultMapKeyComparison<key_type>(key_type(),key_type());}

		struct MapNode
		{
			MapNode() {}
			MapNode(key_type _key, data_type _data) : mapNodeKey(_key), mapNodeData(_data) {}
			MapNode& operator = ( const MapNode& input ) {mapNodeKey=input.mapNodeKey; mapNodeData=input.mapNodeData; return *this;}
			MapNode( const MapNode & input) {mapNodeKey=input.mapNodeKey; mapNodeData=input.mapNodeData;}
			key_type mapNodeKey;
			data_type mapNodeData;
		};

		// Has to be a static because the comparison callback for DataStructures::OrderedList is a C function
		static int NodeComparisonFunc(const key_type &a, const MapNode &b)
		{
			return key_comparison_func(a, b.mapNodeKey);
		}

		Map();
		~Map();
		Map( const Map& original_copy );
		Map& operator= ( const Map& original_copy );

		data_type& Get(const key_type &key) const; 
		data_type Pop(const key_type &key);
		// Add if needed
		void Set(const key_type &key, const data_type &data);
		// Must already exist
		void SetExisting(const key_type &key, const data_type &data);
		// Must add
		void SetNew(const key_type &key, const data_type &data);
		bool Has(const key_type &key) const;
		bool Delete(const key_type &key);
		data_type& operator[] ( const unsigned int position ) const;
		key_type GetKeyAtIndex( const unsigned int position ) const;
		unsigned GetIndexAtKey( const key_type &key );
		void RemoveAtIndex(const unsigned index);
		void Clear(void);
		unsigned Size(void) const;

	protected:
		DataStructures::OrderedList< key_type,MapNode,&Map::NodeComparisonFunc > mapNodeList;

		void SaveLastSearch(const key_type &key, unsigned index) const;
		bool HasSavedSearchResult(const key_type &key) const;

		unsigned lastSearchIndex;
		key_type lastSearchKey;
		bool lastSearchIndexValid;
	};

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	Map<key_type, data_type, key_comparison_func>::Map()
	{
		lastSearchIndexValid=false;
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	Map<key_type, data_type, key_comparison_func>::~Map()
	{
		Clear();
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	Map<key_type, data_type, key_comparison_func>::Map( const Map& original_copy )
	{
		mapNodeList=original_copy.mapNodeList;
        lastSearchIndex=original_copy.lastSearchIndex;
		lastSearchKey=original_copy.lastSearchKey;
		lastSearchIndexValid=original_copy.lastSearchIndexValid;
	}

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	Map<key_type, data_type, key_comparison_func>& Map<key_type, data_type, key_comparison_func>::operator= ( const Map& original_copy )
	{
		mapNodeList=original_copy.mapNodeList;
		lastSearchIndex=original_copy.lastSearchIndex;
		lastSearchKey=original_copy.lastSearchKey;
		lastSearchIndexValid=original_copy.lastSearchIndexValid;
		return *this;
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	data_type& Map<key_type, data_type, key_comparison_func>::Get(const key_type &key) const
	{
		if (HasSavedSearchResult(key))
			return mapNodeList[lastSearchIndex].mapNodeData;

		bool objectExists;
		unsigned index;
		index=mapNodeList.GetIndexFromKey(key, &objectExists);
		RakAssert(objectExists);
		SaveLastSearch(key,index);
		return mapNodeList[index].mapNodeData;
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	unsigned Map<key_type, data_type, key_comparison_func>::GetIndexAtKey( const key_type &key )
	{
		if (HasSavedSearchResult(key))
			return lastSearchIndex;

		bool objectExists;
		unsigned index;
		index=mapNodeList.GetIndexFromKey(key, &objectExists);
		if (objectExists==false)
		{
			RakAssert(objectExists);
		}
		SaveLastSearch(key,index);
		return index;
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	void Map<key_type, data_type, key_comparison_func>::RemoveAtIndex(const unsigned index)
	{
		mapNodeList.RemoveAtIndex(index);
		lastSearchIndexValid=false;
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
		data_type Map<key_type, data_type, key_comparison_func>::Pop(const key_type &key)
	{
		bool objectExists;
		unsigned index;
		if (HasSavedSearchResult(key))
			index=lastSearchIndex;
		else
		{
			index=mapNodeList.GetIndexFromKey(key, &objectExists);
			RakAssert(objectExists);
		}		
		data_type tmp = mapNodeList[index].mapNodeData;
		mapNodeList.RemoveAtIndex(index);
		lastSearchIndexValid=false;
		return tmp;
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	void Map<key_type, data_type, key_comparison_func>::Set(const key_type &key, const data_type &data)
	{
		bool objectExists;
		unsigned index;

		if (HasSavedSearchResult(key))
		{
			mapNodeList[lastSearchIndex].mapNodeData=data;
			return;
		}
		
		index=mapNodeList.GetIndexFromKey(key, &objectExists);

		if (objectExists)
		{
			SaveLastSearch(key,index);
			mapNodeList[index].mapNodeData=data;
		}
		else
		{
			SaveLastSearch(key,mapNodeList.Insert(key,MapNode(key,data), true, _FILE_AND_LINE_));
		}
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	void Map<key_type, data_type, key_comparison_func>::SetExisting(const key_type &key, const data_type &data)
	{
		bool objectExists;
		unsigned index;

		if (HasSavedSearchResult(key))
		{
			index=lastSearchIndex;
		}
		else
		{
			index=mapNodeList.GetIndexFromKey(key, &objectExists);
			RakAssert(objectExists);
			SaveLastSearch(key,index);
		}		

		mapNodeList[index].mapNodeData=data;
	}	

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	void Map<key_type, data_type, key_comparison_func>::SetNew(const key_type &key, const data_type &data)
	{
#ifdef _DEBUG
		bool objectExists;
		mapNodeList.GetIndexFromKey(key, &objectExists);
		RakAssert(objectExists==false);
#endif
		SaveLastSearch(key,mapNodeList.Insert(key,MapNode(key,data), true, _FILE_AND_LINE_));
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	bool Map<key_type, data_type, key_comparison_func>::Has(const key_type &key) const
	{
		if (HasSavedSearchResult(key))
			return true;

		bool objectExists;
		unsigned index;
		index=mapNodeList.GetIndexFromKey(key, &objectExists);
		if (objectExists)
			SaveLastSearch(key,index);
		return objectExists;
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	bool Map<key_type, data_type, key_comparison_func>::Delete(const key_type &key)
	{
		if (HasSavedSearchResult(key))
		{
			lastSearchIndexValid=false;
			mapNodeList.RemoveAtIndex(lastSearchIndex);   
			return true;
		}

		bool objectExists;
		unsigned index;
		index=mapNodeList.GetIndexFromKey(key, &objectExists);
		if (objectExists)
		{
			lastSearchIndexValid=false;
			mapNodeList.RemoveAtIndex(index);
			return true;
		}
		else
			return false;
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	void Map<key_type, data_type, key_comparison_func>::Clear(void)
	{
		lastSearchIndexValid=false;
		mapNodeList.Clear(false, _FILE_AND_LINE_);
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	data_type& Map<key_type, data_type, key_comparison_func>::operator[]( const unsigned int position ) const
	{
		return mapNodeList[position].mapNodeData;
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
		key_type Map<key_type, data_type, key_comparison_func>::GetKeyAtIndex( const unsigned int position ) const
	{
		return mapNodeList[position].mapNodeKey;
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	unsigned Map<key_type, data_type, key_comparison_func>::Size(void) const
	{
		return mapNodeList.Size();
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	void Map<key_type, data_type, key_comparison_func>::SaveLastSearch(const key_type &key, const unsigned index) const
	{
		(void) key;
		(void) index;

		/*
		lastSearchIndex=index;
		lastSearchKey=key;
		lastSearchIndexValid=true;
		*/
	}

	template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
	bool Map<key_type, data_type, key_comparison_func>::HasSavedSearchResult(const key_type &key) const
	{
		(void) key;

		// Not threadsafe!
		return false;
		// return lastSearchIndexValid && key_comparison_func(key,lastSearchKey)==0;
	}
}

#endif
