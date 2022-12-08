/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#ifndef _GRID_SECTORIZER_H
#define _GRID_SECTORIZER_H

//#define _USE_ORDERED_LIST

#include "memoryoverride.h"

#ifdef _USE_ORDERED_LIST
#include "DS_OrderedList.h"
#else
#include "DS_List.h"
#endif

class GridSectorizer
{
public:
	GridSectorizer();
	~GridSectorizer();

	// _cellWidth, _cellHeight is the width and height of each cell in world units
	// minX, minY, maxX, maxY are the world dimensions (can be changed to dynamically allocate later if needed)
	void Init(const float _maxCellWidth, const float _maxCellHeight, const float minX, const float minY, const float maxX, const float maxY);

	// Adds a pointer to the grid with bounding rectangle dimensions
	void AddEntry(void *entry, const float minX, const float minY, const float maxX, const float maxY);

#ifdef _USE_ORDERED_LIST

	// Removes a pointer, as above
	void RemoveEntry(void *entry, const float minX, const float minY, const float maxX, const float maxY);

	// Adds and removes in one pass, more efficient than calling both functions consecutively
	void MoveEntry(void *entry, const float sourceMinX, const float sourceMinY, const float sourceMaxX, const float sourceMaxY,
		const float destMinX, const float destMinY, const float destMaxX, const float destMaxY);

#endif

	// Adds to intersectionList all entries in a certain radius
	void GetEntries(DataStructures::List<void*>& intersectionList, const float minX, const float minY, const float maxX, const float maxY);

	void Clear(void);

protected:
	int WorldToCellX(const float input) const;
	int WorldToCellY(const float input) const;
	int WorldToCellXOffsetAndClamped(const float input) const;
	int WorldToCellYOffsetAndClamped(const float input) const;

	// Returns true or false if a position crosses cells in the grid.  If false, you don't need to move entries
	bool PositionCrossesCells(const float originX, const float originY, const float destinationX, const float destinationY) const;

	float cellOriginX, cellOriginY;
	float cellWidth, cellHeight;
	float invCellWidth, invCellHeight;
	float gridWidth, gridHeight;
	int gridCellWidthCount, gridCellHeightCount;


	// int gridWidth, gridHeight;

#ifdef _USE_ORDERED_LIST
	DataStructures::OrderedList<void*, void*>* grid;
#else
	DataStructures::List<void*>* grid;
#endif
};

#endif
