/* Copyright 2010 Jukka Jylänki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
#pragma once

/** @file SequentialIntegerSet.h
	@brief The SequentialIntegerSet class. */
#pragma once

#include "kNet/Alignment.h"
#include "kNet/NetworkLogging.h"

namespace kNet
{

class SequentialIntegerSet
{
public:
	explicit SequentialIntegerSet(int tableSize_)
	:tableSize(tableSize_), tableSizeMask(tableSize_-1)
	{
		assert(IS_POW2(tableSize));
		table = new unsigned long[tableSize];

		// A bit unconventionally, a value of 0xFFFFFFFF denotes an empty spot.
		memset(table, 0xFF, sizeof(unsigned long) * tableSize);

		size = 0;
	}
	~SequentialIntegerSet()
	{
		delete[] table;
	}

	/// Cannot necessarily return the exact size, but only an upper bound.
	int Size() const { return size; }

	int Capacity() const { return tableSize; }

	int CountSize()
	{
		size = 0;
		for(int i = 0; i < tableSize; ++i)
			if (IsValid(table[i]))
				++size;
	}

	void Prune()
	{
		unsigned long *newTable = new unsigned long[tableSize];
		size = 0;
		for(int i = 0; i < tableSize; ++i)
			if (IsValid(table[i]))
			{
				Add(newTable, table[i]);				
				++size;
			}
		delete[] table;
		table = newTable;
	}

	/// Returns the index in the table where the given value should exist.
	int Hash(unsigned long value) const { return (int)(value & tableSizeMask); }

	/// Probes the given index linearly and returns the next index to look in.
	int LinearProbe(int idx) const { return (idx + 1) & tableSizeMask; }

	bool IsNull(unsigned long value) const { return value == 0xFFFFFFFF; }

	bool IsValid(unsigned long value) const { return !IsNull(value); }

	void Add(unsigned long value)	
	{
		Add(table, value);
	}

	bool Exists(unsigned long value) const
	{
		return table[Hash(value)] == value;
	}

private:
	unsigned long *table;
	int tableSize;
	int tableSizeMask;
	int size;

	void Add(unsigned long *dstTable, int value)
	{
		dstTable[Hash(value)] = value;
	}

	SequentialIntegerSet(const SequentialIntegerSet &); ///\todo Implement.
	void operator =(const SequentialIntegerSet &); ///\todo Implement.

};

} // ~kNet
