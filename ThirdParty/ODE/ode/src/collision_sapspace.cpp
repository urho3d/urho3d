/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001-2003 Russell L. Smith.       *
 * All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 2.1 of the License, or (at  *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file LICENSE.TXT.                                               *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file LICENSE-BSD.TXT.                                       *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
 *                                                                       *
 *************************************************************************/

// Modified by Lasse Öörni for Urho3D

/*
 *  Sweep and Prune adaptation/tweaks for ODE by Aras Pranckevicius.
 *  Additional work by David Walters
 *  Original code:
 *		OPCODE - Optimized Collision Detection
 *		Copyright (C) 2001 Pierre Terdiman
 *		Homepage: http://www.codercorner.com/Opcode.htm
 *
 *	This version does complete radix sort, not "classical" SAP. So, we
 *	have no temporal coherence, but are able to handle any movement
 *	velocities equally well.
 */

#include <ode/common.h>
#include <ode/matrix.h>
#include <ode/collision_space.h>
#include <ode/collision.h>

#include "config.h"
#include "collision_kernel.h"
#include "collision_space_internal.h"

// Reference counting helper for radix sort global data.
//static void RadixSortRef();
//static void RadixSortDeref();


// --------------------------------------------------------------------------
//  Radix Sort Context
// --------------------------------------------------------------------------

struct RaixSortContext
{
public:
	RaixSortContext(): mCurrentSize(0), mCurrentUtilization(0), mRanksValid(false), mRanksBuffer(NULL), mPrimaryRanks(NULL) {}
	~RaixSortContext() { FreeRanks(); }

	// OPCODE's Radix Sorting, returns a list of indices in sorted order
	const uint32* RadixSort( const float* input2, uint32 nb );

private:
	void FreeRanks();
	void AllocateRanks(size_t nNewSize);

	void ReallocateRanksIfNecessary(size_t nNewSize);

private:
	void SetCurrentSize(size_t nValue) { mCurrentSize = nValue; }
	size_t GetCurrentSize() const { return mCurrentSize; }

    void SetCurrentUtilization(size_t nValue) { mCurrentUtilization = nValue; }
    size_t GetCurrentUtilization() const { return mCurrentUtilization; }

	uint32 *GetRanks1() const { return mPrimaryRanks; }
	uint32 *GetRanks2() const { return mRanksBuffer + ((mRanksBuffer + mCurrentSize) - mPrimaryRanks); }
	void SwapRanks() { mPrimaryRanks = GetRanks2(); }

	bool AreRanksValid() const { return mRanksValid; }
	void InvalidateRanks() { mRanksValid = false; }
	void ValidateRanks() { mRanksValid = true; }

private:
	size_t mCurrentSize;						//!< Current size of the indices list
    size_t mCurrentUtilization;					//!< Current utilization of the indices list
	bool mRanksValid;
	uint32* mRanksBuffer;						//!< Two lists allocated sequentially in a single block
	uint32* mPrimaryRanks;
};

void RaixSortContext::AllocateRanks(size_t nNewSize)
{
	dIASSERT(GetCurrentSize() == 0);

	mRanksBuffer = new uint32[2 * nNewSize];
	mPrimaryRanks = mRanksBuffer;

	SetCurrentSize(nNewSize);
}

void RaixSortContext::FreeRanks()
{
	SetCurrentSize(0);

	delete[] mRanksBuffer;
}

void RaixSortContext::ReallocateRanksIfNecessary(size_t nNewSize)
{
	size_t nCurUtilization = GetCurrentUtilization();
	
	if (nNewSize != nCurUtilization)
	{
        size_t nCurSize = GetCurrentSize();

		if ( nNewSize > nCurSize )
		{
			// Free previously used ram
			FreeRanks();

			// Get some fresh one
			AllocateRanks(nNewSize);
		}

		InvalidateRanks();
        SetCurrentUtilization(nNewSize);
	}
}

// --------------------------------------------------------------------------
//  SAP space code
// --------------------------------------------------------------------------

struct dxSAPSpace : public dxSpace
{
	// Constructor / Destructor
	dxSAPSpace( dSpaceID _space, int sortaxis );
	~dxSAPSpace();

	// dxSpace
	virtual dxGeom* getGeom(int i);
	virtual void add(dxGeom* g);
	virtual void remove(dxGeom* g);
	virtual void dirty(dxGeom* g);
	virtual void computeAABB();
	virtual void cleanGeoms();
	virtual void collide( void *data, dNearCallback *callback );
	virtual void collide2( void *data, dxGeom *geom, dNearCallback *callback );

private:

	//--------------------------------------------------------------------------
	// Local Declarations
	//--------------------------------------------------------------------------

	//! A generic couple structure
	struct Pair
	{
		uint32 id0;	//!< First index of the pair
		uint32 id1;	//!< Second index of the pair

		// Default and Value Constructor
		Pair() {}
		Pair( uint32 i0, uint32 i1 ) : id0( i0 ), id1( i1 ) {}
	};

	//--------------------------------------------------------------------------
	// Helpers
	//--------------------------------------------------------------------------

	/**
	 *	Complete box pruning.
	 *  Returns a list of overlapping pairs of boxes, each box of the pair
	 *  belongs to the same set.
	 *
	 *	@param	count	[in] number of boxes.
	 *	@param	geoms	[in] geoms of boxes.
	 *	@param	pairs	[out] array of overlapping pairs.
	 */
	void BoxPruning( int count, const dxGeom** geoms, dArray< Pair >& pairs );


	//--------------------------------------------------------------------------
	// Implementation Data
	//--------------------------------------------------------------------------

	// We have two lists (arrays of pointers) to dirty and clean
	// geoms. Each geom knows it's index into the corresponding list
	// (see macros above).
	dArray<dxGeom*> DirtyList; // dirty geoms
	dArray<dxGeom*> GeomList;	// clean geoms

	// For SAP, we ultimately separate "normal" geoms and the ones that have
	// infinite AABBs. No point doing SAP on infinite ones (and it doesn't handle
	// infinite geoms anyway).
	dArray<dxGeom*> TmpGeomList;	// temporary for normal geoms
	dArray<dxGeom*> TmpInfGeomList;	// temporary for geoms with infinite AABBs

	// Our sorting axes. (X,Z,Y is often best). Stored *2 for minor speedup
	// Axis indices into geom's aabb are: min=idx, max=idx+1
	uint32 ax0idx;
	uint32 ax1idx;
	uint32 ax2idx;

	// pruning position array scratch pad
	// NOTE: this is float not dReal because of the OPCODE radix sorter
	dArray< float > poslist;
	RaixSortContext	sortContext;
};

// Creation
dSpaceID dSweepAndPruneSpaceCreate( dxSpace* space, int axisorder ) {
	return new dxSAPSpace( space, axisorder );
}


//==============================================================================

#define GEOM_ENABLED(g) (((g)->gflags & GEOM_ENABLE_TEST_MASK) == GEOM_ENABLE_TEST_VALUE)

// HACK: We abuse 'next' and 'tome' members of dxGeom to store indice into dirty/geom lists.
#define GEOM_SET_DIRTY_IDX(g,idx) { (g)->next = (dxGeom*)(size_t)(idx); }
#define GEOM_SET_GEOM_IDX(g,idx) { (g)->tome = (dxGeom**)(size_t)(idx); }
#define GEOM_GET_DIRTY_IDX(g) ((int)(size_t)(g)->next)
#define GEOM_GET_GEOM_IDX(g) ((int)(size_t)(g)->tome)
#define GEOM_INVALID_IDX (-1)


/*
 *  A bit of repetitive work - similar to collideAABBs, but doesn't check
 *  if AABBs intersect (because SAP returns pairs with overlapping AABBs).
 */
static void collideGeomsNoAABBs( dxGeom *g1, dxGeom *g2, void *data, dNearCallback *callback )
{
	dIASSERT( (g1->gflags & GEOM_AABB_BAD)==0 );
	dIASSERT( (g2->gflags & GEOM_AABB_BAD)==0 );

	// no contacts if both geoms on the same body, and the body is not 0
	if (g1->body == g2->body && g1->body) return;

	// test if the category and collide bitfields match
    // Urho3D: modified to allow easier collision exclusion
    if (!(g1->category_bits & g2->collide_bits) || !(g2->category_bits & g1->collide_bits))
        return;

	dReal *bounds1 = g1->aabb;
	dReal *bounds2 = g2->aabb;

	// check if either object is able to prove that it doesn't intersect the
	// AABB of the other
	if (g1->AABBTest (g2,bounds2) == 0) return;
	if (g2->AABBTest (g1,bounds1) == 0) return;

	// the objects might actually intersect - call the space callback function
	callback (data,g1,g2);
};


dxSAPSpace::dxSAPSpace( dSpaceID _space, int axisorder ) : dxSpace( _space )
{
	type = dSweepAndPruneSpaceClass;

	// Init AABB to infinity
	aabb[0] = -dInfinity;
	aabb[1] = dInfinity;
	aabb[2] = -dInfinity;
	aabb[3] = dInfinity;
	aabb[4] = -dInfinity;
	aabb[5] = dInfinity;

	ax0idx = ( ( axisorder ) & 3 ) << 1;
	ax1idx = ( ( axisorder >> 2 ) & 3 ) << 1;
	ax2idx = ( ( axisorder >> 4 ) & 3 ) << 1;
}

dxSAPSpace::~dxSAPSpace()
{
	CHECK_NOT_LOCKED(this);
	if ( cleanup ) {
		// note that destroying each geom will call remove()
		for ( ; DirtyList.size(); dGeomDestroy( DirtyList[ 0 ] ) ) {}
		for ( ; GeomList.size(); dGeomDestroy( GeomList[ 0 ] ) ) {}
	}
	else {
		// just unhook them
		for ( ; DirtyList.size(); remove( DirtyList[ 0 ] ) ) {}
		for ( ; GeomList.size(); remove( GeomList[ 0 ] ) ) {}
	}
}

dxGeom* dxSAPSpace::getGeom( int i )
{
	dUASSERT( i >= 0 && i < count, "index out of range" );
	int dirtySize = DirtyList.size();
	if( i < dirtySize )
		return DirtyList[i];
	else
		return GeomList[i-dirtySize];
}

void dxSAPSpace::add( dxGeom* g )
{
	CHECK_NOT_LOCKED (this);
	dAASSERT(g);
	dUASSERT(g->parent_space == 0 && g->next == 0, "geom is already in a space");

	g->gflags |= GEOM_DIRTY | GEOM_AABB_BAD;

	// add to dirty list
	GEOM_SET_DIRTY_IDX( g, DirtyList.size() );
	GEOM_SET_GEOM_IDX( g, GEOM_INVALID_IDX );
	DirtyList.push( g );

	g->parent_space = this;
	this->count++;

	dGeomMoved(this);
}

void dxSAPSpace::remove( dxGeom* g )
{
	CHECK_NOT_LOCKED(this);
	dAASSERT(g);
	dUASSERT(g->parent_space == this,"object is not in this space");

	// remove
	int dirtyIdx = GEOM_GET_DIRTY_IDX(g);
	int geomIdx = GEOM_GET_GEOM_IDX(g);
	// must be in one list, not in both
	dUASSERT(
		(dirtyIdx==GEOM_INVALID_IDX && geomIdx>=0 && geomIdx<GeomList.size()) ||
		(geomIdx==GEOM_INVALID_IDX && dirtyIdx>=0 && dirtyIdx<DirtyList.size()),
		"geom indices messed up" );
	if( dirtyIdx != GEOM_INVALID_IDX ) {
		// we're in dirty list, remove
		int dirtySize = DirtyList.size();
		dxGeom* lastG = DirtyList[dirtySize-1];
		DirtyList[dirtyIdx] = lastG;
		GEOM_SET_DIRTY_IDX(lastG,dirtyIdx);
		GEOM_SET_DIRTY_IDX(g,GEOM_INVALID_IDX);
		DirtyList.setSize( dirtySize-1 );
	} else {
		// we're in geom list, remove
		int geomSize = GeomList.size();
		dxGeom* lastG = GeomList[geomSize-1];
		GeomList[geomIdx] = lastG;
		GEOM_SET_GEOM_IDX(lastG,geomIdx);
		GEOM_SET_GEOM_IDX(g,GEOM_INVALID_IDX);
		GeomList.setSize( geomSize-1 );
	}
	count--;

	// safeguard
	g->parent_space = 0;

	// the bounding box of this space (and that of all the parents) may have
	// changed as a consequence of the removal.
	dGeomMoved(this);
}

void dxSAPSpace::dirty( dxGeom* g )
{
	dAASSERT(g);
	dUASSERT(g->parent_space == this,"object is not in this space");

	// check if already dirtied
	int dirtyIdx = GEOM_GET_DIRTY_IDX(g);
	if( dirtyIdx != GEOM_INVALID_IDX )
		return;

	int geomIdx = GEOM_GET_GEOM_IDX(g);
	dUASSERT( geomIdx>=0 && geomIdx<GeomList.size(), "geom indices messed up" );

	// remove from geom list, place last in place of this
	int geomSize = GeomList.size();
	dxGeom* lastG = GeomList[geomSize-1];
	GeomList[geomIdx] = lastG;
	GEOM_SET_GEOM_IDX(lastG,geomIdx);
	GeomList.setSize( geomSize-1 );

	// add to dirty list
	GEOM_SET_GEOM_IDX( g, GEOM_INVALID_IDX );
	GEOM_SET_DIRTY_IDX( g, DirtyList.size() );
	DirtyList.push( g );
}

void dxSAPSpace::computeAABB()
{
	// TODO?
}

void dxSAPSpace::cleanGeoms()
{
	int dirtySize = DirtyList.size();
	if( !dirtySize )
		return;

	// compute the AABBs of all dirty geoms, clear the dirty flags,
	// remove from dirty list, place into geom list
	lock_count++;

	int geomSize = GeomList.size();
	GeomList.setSize( geomSize + dirtySize ); // ensure space in geom list

	for( int i = 0; i < dirtySize; ++i ) {
		dxGeom* g = DirtyList[i];
		if( IS_SPACE(g) ) {
			((dxSpace*)g)->cleanGeoms();
		}
		g->recomputeAABB();
		g->gflags &= (~(GEOM_DIRTY|GEOM_AABB_BAD));
		// remove from dirty list, add to geom list
		GEOM_SET_DIRTY_IDX( g, GEOM_INVALID_IDX );
		GEOM_SET_GEOM_IDX( g, geomSize + i );
		GeomList[geomSize+i] = g;
	}
	// clear dirty list
	DirtyList.setSize( 0 );

	lock_count--;
}

void dxSAPSpace::collide( void *data, dNearCallback *callback )
{
	dAASSERT (callback);

	lock_count++;

	cleanGeoms();

	// by now all geoms are in GeomList, and DirtyList must be empty
	int geom_count = GeomList.size();
	dUASSERT( geom_count == count, "geom counts messed up" );

	// separate all ENABLED geoms into infinite AABBs and normal AABBs
	TmpGeomList.setSize(0);
	TmpInfGeomList.setSize(0);
	int axis0max = ax0idx + 1;
	for( int i = 0; i < geom_count; ++i ) {
		dxGeom* g = GeomList[i];
		if( !GEOM_ENABLED(g) ) // skip disabled ones
			continue;
		const dReal& amax = g->aabb[axis0max];
		if( amax == dInfinity ) // HACK? probably not...
			TmpInfGeomList.push( g );
		else
			TmpGeomList.push( g );
	}

	// do SAP on normal AABBs
	dArray< Pair > overlapBoxes;
	int tmp_geom_count = TmpGeomList.size();
	if ( tmp_geom_count > 0 )
	{
		// Size the poslist (+1 for infinity end cap)
		poslist.setSize( tmp_geom_count + 1 );

		// Generate a list of overlapping boxes
		BoxPruning( tmp_geom_count, (const dxGeom**)TmpGeomList.data(), overlapBoxes );
	}

	// collide overlapping
	int overlapCount = overlapBoxes.size();
	for( int j = 0; j < overlapCount; ++j )
	{
		const Pair& pair = overlapBoxes[ j ];
		dxGeom* g1 = TmpGeomList[ pair.id0 ];
		dxGeom* g2 = TmpGeomList[ pair.id1 ];
		collideGeomsNoAABBs( g1, g2, data, callback );
	}

	int infSize = TmpInfGeomList.size();
	int normSize = TmpGeomList.size();
	int m, n;

	for ( m = 0; m < infSize; ++m )
	{
		dxGeom* g1 = TmpInfGeomList[ m ];

		// collide infinite ones
		for( n = m+1; n < infSize; ++n ) {
			dxGeom* g2 = TmpInfGeomList[n];
			collideGeomsNoAABBs( g1, g2, data, callback );
		}

		// collide infinite ones with normal ones
		for( n = 0; n < normSize; ++n ) {
			dxGeom* g2 = TmpGeomList[n];
			collideGeomsNoAABBs( g1, g2, data, callback );
		}
	}

	lock_count--;
}

void dxSAPSpace::collide2( void *data, dxGeom *geom, dNearCallback *callback )
{
	dAASSERT (geom && callback);

	// TODO: This is just a simple N^2 implementation

	lock_count++;

	cleanGeoms();
	geom->recomputeAABB();

	// intersect bounding boxes
	int geom_count = GeomList.size();
	for ( int i = 0; i < geom_count; ++i ) {
		dxGeom* g = GeomList[i];
		if ( GEOM_ENABLED(g) )
			collideAABBs (g,geom,data,callback);
	}

	lock_count--;
}


void dxSAPSpace::BoxPruning( int count, const dxGeom** geoms, dArray< Pair >& pairs )
{
	// 1) Build main list using the primary axis
	//  NOTE: uses floats instead of dReals because that's what radix sort wants
	for( int i = 0; i < count; ++i )
		poslist[ i ] = (float)TmpGeomList[i]->aabb[ ax0idx ];
	poslist[ count++ ] = FLT_MAX;

	// 2) Sort the list
	const uint32* Sorted = sortContext.RadixSort( poslist.data(), count );

	// 3) Prune the list
	const uint32* const LastSorted = Sorted + count;
	const uint32* RunningAddress = Sorted;

	Pair IndexPair;
	while ( RunningAddress < LastSorted && Sorted < LastSorted )
	{
		IndexPair.id0 = *Sorted++;

		// empty, this loop just advances RunningAddress
		while ( poslist[*RunningAddress++] < poslist[IndexPair.id0] ) {}

		if ( RunningAddress < LastSorted )
		{
			const uint32* RunningAddress2 = RunningAddress;

			const dReal idx0ax0max = geoms[IndexPair.id0]->aabb[ax0idx+1];
			const dReal idx0ax1max = geoms[IndexPair.id0]->aabb[ax1idx+1];
			const dReal idx0ax2max = geoms[IndexPair.id0]->aabb[ax2idx+1];

			while ( poslist[ IndexPair.id1 = *RunningAddress2++ ] <= idx0ax0max )
			{
				const dReal* aabb0 = geoms[ IndexPair.id0 ]->aabb;
				const dReal* aabb1 = geoms[ IndexPair.id1 ]->aabb;

				// Intersection?
				if ( idx0ax1max >= aabb1[ax1idx] && aabb1[ax1idx+1] >= aabb0[ax1idx] )
				if ( idx0ax2max >= aabb1[ax2idx] && aabb1[ax2idx+1] >= aabb0[ax2idx] )
				{
					pairs.push( IndexPair );
				}
			}
		}

	}; // while ( RunningAddress < LastSorted && Sorted < LastSorted )
}


//==============================================================================

//------------------------------------------------------------------------------
// Radix Sort
//------------------------------------------------------------------------------



#define CHECK_PASS_VALIDITY(pass)															\
	/* Shortcut to current counters */														\
	uint32* CurCount = &mHistogram[pass<<8];												\
																							\
	/* Reset flag. The sorting pass is supposed to be performed. (default) */				\
	bool PerformPass = true;																\
																							\
	/* Check pass validity */																\
																							\
	/* If all values have the same byte, sorting is useless. */								\
	/* It may happen when sorting bytes or words instead of dwords. */						\
	/* This routine actually sorts words faster than dwords, and bytes */					\
	/* faster than words. Standard running time (O(4*n))is reduced to O(2*n) */				\
	/* for words and O(n) for bytes. Running time for floats depends on actual values... */	\
																							\
	/* Get first byte */																	\
	uint8 UniqueVal = *(((uint8*)input)+pass);												\
																							\
	/* Check that byte's counter */															\
	if(CurCount[UniqueVal]==nb)	PerformPass=false;

// WARNING ONLY SORTS IEEE FLOATING-POINT VALUES
const uint32* RaixSortContext::RadixSort( const float* input2, uint32 nb )
{
	uint32* input = (uint32*)input2;

	// Resize lists if needed
	ReallocateRanksIfNecessary(nb);

	// Allocate histograms & offsets on the stack
	uint32 mHistogram[256*4];
	uint32* mLink[256];

	// Create histograms (counters). Counters for all passes are created in one run.
	// Pros:	read input buffer once instead of four times
	// Cons:	mHistogram is 4Kb instead of 1Kb
	// Floating-point values are always supposed to be signed values, so there's only one code path there.
	// Please note the floating point comparison needed for temporal coherence! Although the resulting asm code
	// is dreadful, this is surprisingly not such a performance hit - well, I suppose that's a big one on first
	// generation Pentiums....We can't make comparison on integer representations because, as Chris said, it just
	// wouldn't work with mixed positive/negative values....
	{
		/* Clear counters/histograms */
		memset(mHistogram, 0, 256*4*sizeof(uint32));

		/* Prepare to count */
		uint8* p = (uint8*)input;
		uint8* pe = &p[nb*4];
		uint32* h0= &mHistogram[0];		/* Histogram for first pass (LSB)	*/
		uint32* h1= &mHistogram[256];	/* Histogram for second pass		*/
		uint32* h2= &mHistogram[512];	/* Histogram for third pass			*/
		uint32* h3= &mHistogram[768];	/* Histogram for last pass (MSB)	*/

		bool AlreadySorted = true;	/* Optimism... */

		if (!AreRanksValid())
		{
			/* Prepare for temporal coherence */
			float* Running = (float*)input2;
			float PrevVal = *Running;

			while(p!=pe)
			{
				/* Read input input2 in previous sorted order */
				float Val = *Running++;
				/* Check whether already sorted or not */
				if(Val<PrevVal)	{ AlreadySorted = false; break; } /* Early out */
				/* Update for next iteration */
				PrevVal = Val;

				/* Create histograms */
				h0[*p++]++;	h1[*p++]++;	h2[*p++]++;	h3[*p++]++;
			}

			/* If all input values are already sorted, we just have to return and leave the */
			/* previous list unchanged. That way the routine may take advantage of temporal */
			/* coherence, for example when used to sort transparent faces.					*/
			if(AlreadySorted)
			{
				uint32* const Ranks1 = GetRanks1();
				for(uint32 i=0;i<nb;i++)	Ranks1[i] = i;
				return Ranks1;
			}
		}
		else
		{
			/* Prepare for temporal coherence */
			uint32* const Ranks1 = GetRanks1();

			uint32* Indices = Ranks1;
			float PrevVal = (float)input2[*Indices];

			while(p!=pe)
			{
				/* Read input input2 in previous sorted order */
				float Val = (float)input2[*Indices++];
				/* Check whether already sorted or not */
				if(Val<PrevVal)	{ AlreadySorted = false; break; } /* Early out */
				/* Update for next iteration */
				PrevVal = Val;

				/* Create histograms */
				h0[*p++]++;	h1[*p++]++;	h2[*p++]++;	h3[*p++]++;
			}

			/* If all input values are already sorted, we just have to return and leave the */
			/* previous list unchanged. That way the routine may take advantage of temporal */
			/* coherence, for example when used to sort transparent faces.					*/
			if(AlreadySorted)	{ return Ranks1;	}
		}

		/* Else there has been an early out and we must finish computing the histograms */
		while(p!=pe)
		{
			/* Create histograms without the previous overhead */
			h0[*p++]++;	h1[*p++]++;	h2[*p++]++;	h3[*p++]++;
		}
	}

	// Compute #negative values involved if needed
	uint32 NbNegativeValues = 0;

	// An efficient way to compute the number of negatives values we'll have to deal with is simply to sum the 128
	// last values of the last histogram. Last histogram because that's the one for the Most Significant Byte,
	// responsible for the sign. 128 last values because the 128 first ones are related to positive numbers.
	uint32* h3= &mHistogram[768];
	for(uint32 i=128;i<256;i++)	NbNegativeValues += h3[i];	// 768 for last histogram, 128 for negative part

	// Radix sort, j is the pass number (0=LSB, 3=MSB)
	for(uint32 j=0;j<4;j++)
	{
		// Should we care about negative values?
		if(j!=3)
		{
			// Here we deal with positive values only
			CHECK_PASS_VALIDITY(j);

			if(PerformPass)
			{
				uint32* const Ranks2 = GetRanks2();
				// Create offsets
				mLink[0] = Ranks2;
				for(uint32 i=1;i<256;i++)		mLink[i] = mLink[i-1] + CurCount[i-1];

				// Perform Radix Sort
				uint8* InputBytes = (uint8*)input;
				InputBytes += j;
				if (!AreRanksValid())
				{
					for(uint32 i=0;i<nb;i++)
					{
						*mLink[InputBytes[i<<2]]++ = i;
					}

					ValidateRanks();
				}
				else
				{
					uint32* const Ranks1 = GetRanks1();

					uint32* Indices				= Ranks1;
					uint32* const IndicesEnd	= Ranks1 + nb;
					while(Indices!=IndicesEnd)
					{
						uint32 id = *Indices++;
						*mLink[InputBytes[id<<2]]++ = id;
					}
				}

				// Swap pointers for next pass. Valid indices - the most recent ones - are in mRanks after the swap.
				SwapRanks();
			}
		}
		else
		{
			// This is a special case to correctly handle negative values
			CHECK_PASS_VALIDITY(j);

			if(PerformPass)
			{
				uint32* const Ranks2 = GetRanks2();

				// Create biased offsets, in order for negative numbers to be sorted as well
				mLink[0] = Ranks2 + NbNegativeValues;										// First positive number takes place after the negative ones
				for(uint32 i=1;i<128;i++)		mLink[i] = mLink[i-1] + CurCount[i-1];		// 1 to 128 for positive numbers

				// We must reverse the sorting order for negative numbers!
				mLink[255] = Ranks2;
				for(uint32 i=0;i<127;i++)	mLink[254-i] = mLink[255-i] + CurCount[255-i];		// Fixing the wrong order for negative values
				for(uint32 i=128;i<256;i++)	mLink[i] += CurCount[i];							// Fixing the wrong place for negative values

				// Perform Radix Sort
				if (!AreRanksValid())
				{
					for(uint32 i=0;i<nb;i++)
					{
						uint32 Radix = input[i]>>24;							// Radix byte, same as above. AND is useless here (uint32).
						// ### cmp to be killed. Not good. Later.
						if(Radix<128)		*mLink[Radix]++ = i;		// Number is positive, same as above
						else				*(--mLink[Radix]) = i;		// Number is negative, flip the sorting order
					}

					ValidateRanks();
				}
				else
				{
					uint32* const Ranks1 = GetRanks1();

					for(uint32 i=0;i<nb;i++)
					{
						uint32 Radix = input[Ranks1[i]]>>24;							// Radix byte, same as above. AND is useless here (uint32).
						// ### cmp to be killed. Not good. Later.
						if(Radix<128)		*mLink[Radix]++ = Ranks1[i];		// Number is positive, same as above
						else				*(--mLink[Radix]) = Ranks1[i];		// Number is negative, flip the sorting order
					}
				}
				// Swap pointers for next pass. Valid indices - the most recent ones - are in mRanks after the swap.
				SwapRanks();
			}
			else
			{
				// The pass is useless, yet we still have to reverse the order of current list if all values are negative.
				if(UniqueVal>=128)
				{
					if (!AreRanksValid())
					{
						uint32* const Ranks2 = GetRanks2();
						// ###Possible?
						for(uint32 i=0;i<nb;i++)
						{
							Ranks2[i] = nb-i-1;
						}

						ValidateRanks();
					}
					else
					{
						uint32* const Ranks1 = GetRanks1();
						uint32* const Ranks2 = GetRanks2();
						for(uint32 i=0;i<nb;i++)	Ranks2[i] = Ranks1[nb-i-1];
					}

					// Swap pointers for next pass. Valid indices - the most recent ones - are in mRanks after the swap.
					SwapRanks();
				}
			}
		}
	}

	// Return indices
	uint32* const Ranks1 = GetRanks1();
	return Ranks1;
}

