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

// QuadTreeSpace by Erwin de Vries.
// With math corrections by Oleh Derevenko. ;)

#include <ode/common.h>
#include <ode/matrix.h>
#include <ode/collision_space.h>
#include <ode/collision.h>
#include "config.h"
#include "collision_kernel.h"

#include "collision_space_internal.h"


#define AXIS0 0
#define AXIS1 1
#define UP 2

//#define DRAWBLOCKS

const int SPLITAXIS = 2;
const int SPLITS = SPLITAXIS * SPLITAXIS;

#define GEOM_ENABLED(g) (((g)->gflags & GEOM_ENABLE_TEST_MASK) == GEOM_ENABLE_TEST_VALUE)

class Block{
public:
	dReal mMinX, mMaxX;
	dReal mMinZ, mMaxZ;

	dGeomID mFirst;
	int mGeomCount;

	Block* mParent;
	Block* mChildren;

	void Create(const dReal MinX, const dReal MaxX, const dReal MinZ, const dReal MaxZ, Block* Parent, int Depth, Block*& Blocks);

	void Collide(void* UserData, dNearCallback* Callback);
	void Collide(dGeomID g1, dGeomID g2, void* UserData, dNearCallback* Callback);

	void CollideLocal(dGeomID g2, void* UserData, dNearCallback* Callback);
	
	void AddObject(dGeomID Object);
	void DelObject(dGeomID Object);
	void Traverse(dGeomID Object);

	bool Inside(const dReal* AABB);
	
	Block* GetBlock(const dReal* AABB);
	Block* GetBlockChild(const dReal* AABB);
};


#ifdef DRAWBLOCKS
#include "..\..\Include\drawstuff\\drawstuff.h"

static void DrawBlock(Block* Block){
	dVector3 v[8];
	v[0][AXIS0] = Block->mMinX;
	v[0][UP] = REAL(-1.0);
	v[0][AXIS1] = Block->mMinZ;
	
	v[1][AXIS0] = Block->mMinX;
	v[1][UP] = REAL(-1.0);
	v[1][AXIS1] = Block->mMaxZ;
	
	v[2][AXIS0] = Block->mMaxX;
	v[2][UP] = REAL(-1.0);
	v[2][AXIS1] = Block->mMinZ;
	
	v[3][AXIS0] = Block->mMaxX;
	v[3][UP] = REAL(-1.0);
	v[3][AXIS1] = Block->mMaxZ;
	
	v[4][AXIS0] = Block->mMinX;
	v[4][UP] = REAL(1.0);
	v[4][AXIS1] = Block->mMinZ;
	
	v[5][AXIS0] = Block->mMinX;
	v[5][UP] = REAL(1.0);
	v[5][AXIS1] = Block->mMaxZ;
	
	v[6][AXIS0] = Block->mMaxX;
	v[6][UP] = REAL(1.0);
	v[6][AXIS1] = Block->mMinZ;
	
	v[7][AXIS0] = Block->mMaxX;
	v[7][UP] = REAL(1.0);
	v[7][AXIS1] = Block->mMaxZ;
	
	// Bottom
	dsDrawLine(v[0], v[1]);
	dsDrawLine(v[1], v[3]);
	dsDrawLine(v[3], v[2]);
	dsDrawLine(v[2], v[0]);
	
	// Top
	dsDrawLine(v[4], v[5]);
	dsDrawLine(v[5], v[7]);
	dsDrawLine(v[7], v[6]);
	dsDrawLine(v[6], v[4]);
	
	// Sides
	dsDrawLine(v[0], v[4]);
	dsDrawLine(v[1], v[5]);
	dsDrawLine(v[2], v[6]);
	dsDrawLine(v[3], v[7]);
}
#endif	//DRAWBLOCKS


void Block::Create(const dReal MinX, const dReal MaxX, const dReal MinZ, const dReal MaxZ, Block* Parent, int Depth, Block*& Blocks){
	dIASSERT(MinX <= MaxX);
	dIASSERT(MinZ <= MaxZ);

	mGeomCount = 0;
	mFirst = 0;

	mMinX = MinX;
	mMaxX = MaxX;

	mMinZ = MinZ;
	mMaxZ = MaxZ;

	this->mParent = Parent;

	if (Depth > 0){
		mChildren = Blocks;
		Blocks += SPLITS;

		const dReal ChildExtentX = (MaxX - MinX) / SPLITAXIS;
		const dReal ChildExtentZ = (MaxZ - MinZ) / SPLITAXIS;

		const int ChildDepth = Depth - 1;
		int Index = 0;

		dReal ChildRightX = MinX;
		for (int i = 0; i < SPLITAXIS; i++){
			const dReal ChildLeftX = ChildRightX;
			ChildRightX = (i != SPLITAXIS - 1) ? ChildLeftX + ChildExtentX : MaxX;

			dReal ChildRightZ = MinZ;
			for (int j = 0; j < SPLITAXIS; j++){
				const dReal ChildLeftZ = ChildRightZ;
				ChildRightZ = (j != SPLITAXIS - 1) ? ChildLeftZ + ChildExtentZ : MaxZ;

				mChildren[Index].Create(ChildLeftX, ChildRightX, ChildLeftZ, ChildRightZ, this, ChildDepth, Blocks);
				++Index;
			}
		}
	}
	else mChildren = 0;
}

void Block::Collide(void* UserData, dNearCallback* Callback){
#ifdef DRAWBLOCKS
	DrawBlock(this);
#endif
	// Collide the local list
	dxGeom* g = mFirst;
	while (g){
		if (GEOM_ENABLED(g)){
			Collide(g, g->next, UserData, Callback);
		}
		g = g->next;
	}

	// Recurse for children
	if (mChildren){
		for (int i = 0; i < SPLITS; i++){
			Block &CurrentChild = mChildren[i];
			if (CurrentChild.mGeomCount <= 1){	// Early out
				continue;
			}
			CurrentChild.Collide(UserData, Callback);
		}
	}
}

// Note: g2 is assumed to be in this Block
void Block::Collide(dxGeom* g1, dxGeom* g2, void* UserData, dNearCallback* Callback){
#ifdef DRAWBLOCKS
	DrawBlock(this);
#endif
	// Collide against local list
	while (g2){
		if (GEOM_ENABLED(g2)){
			collideAABBs (g1, g2, UserData, Callback);
		}
		g2 = g2->next;
	}

	// Collide against children
	if (mChildren){
		for (int i = 0; i < SPLITS; i++){
			Block &CurrentChild = mChildren[i];
			// Early out for empty blocks
			if (CurrentChild.mGeomCount == 0){
				continue;
			}

			// Does the geom's AABB collide with the block?
			// Don't do AABB tests for single geom blocks.
			if (CurrentChild.mGeomCount == 1){
				//
			}
			else if (true){
				if (g1->aabb[AXIS0 * 2 + 0] >= CurrentChild.mMaxX ||
					g1->aabb[AXIS0 * 2 + 1] < CurrentChild.mMinX ||
					g1->aabb[AXIS1 * 2 + 0] >= CurrentChild.mMaxZ ||
					g1->aabb[AXIS1 * 2 + 1] < CurrentChild.mMinZ) continue;
			}
			CurrentChild.Collide(g1, CurrentChild.mFirst, UserData, Callback);
		}
	}
}

void Block::CollideLocal(dxGeom* g2, void* UserData, dNearCallback* Callback){
	// Collide against local list
	dxGeom* g1 = mFirst;
	while (g1){
		if (GEOM_ENABLED(g1)){
			collideAABBs (g1, g2, UserData, Callback);
		}
		g1 = g1->next;
	}
}

void Block::AddObject(dGeomID Object){
	// Add the geom
	Object->next = mFirst;
	mFirst = Object;
	Object->tome = (dxGeom**)this;

	// Now traverse upwards to tell that we have a geom
	Block* Block = this;
	do{
		Block->mGeomCount++;
		Block = Block->mParent;
	}
	while (Block);
}

void Block::DelObject(dGeomID Object){
	// Del the geom
	dxGeom* g = mFirst;
	dxGeom* Last = 0;
	while (g){
		if (g == Object){
			if (Last){
				Last->next = g->next;
			}
			else mFirst = g->next;

			break;
		}
		Last = g;
		g = g->next;
	}

	Object->tome = 0;

	// Now traverse upwards to tell that we have lost a geom
	Block* Block = this;
	do{
		Block->mGeomCount--;
		Block = Block->mParent;
	}
	while (Block);
}

void Block::Traverse(dGeomID Object){
	Block* NewBlock = GetBlock(Object->aabb);

	if (NewBlock != this){
		// Remove the geom from the old block and add it to the new block.
		// This could be more optimal, but the loss should be very small.
		DelObject(Object);
		NewBlock->AddObject(Object);
	}
}

bool Block::Inside(const dReal* AABB){
	return AABB[AXIS0 * 2 + 0] >= mMinX && AABB[AXIS0 * 2 + 1] < mMaxX && AABB[AXIS1 * 2 + 0] >= mMinZ && AABB[AXIS1 * 2 + 1] < mMaxZ;
}

Block* Block::GetBlock(const dReal* AABB){
	if (Inside(AABB)){
		return GetBlockChild(AABB);	// Child or this will have a good block
	}
	else if (mParent){
		return mParent->GetBlock(AABB);	// Parent has a good block
	}
	else return this;	// We are at the root, so we have little choice
}

Block* Block::GetBlockChild(const dReal* AABB){
	if (mChildren){
		for (int i = 0; i < SPLITS; i++){
			Block &CurrentChild = mChildren[i];
			if (CurrentChild.Inside(AABB)){
				return CurrentChild.GetBlockChild(AABB);	// Child will have good block
			}
		}
	}
	return this;	// This is the best block
}

//****************************************************************************
// quadtree space

struct dxQuadTreeSpace : public dxSpace{
	Block* Blocks;	// Blocks[0] is the root

	dArray<dxGeom*> DirtyList;

	dxQuadTreeSpace(dSpaceID _space, const dVector3 Center, const dVector3 Extents, int Depth);
	~dxQuadTreeSpace();

	dxGeom* getGeom(int i);
	
	void add(dxGeom* g);
	void remove(dxGeom* g);
	void dirty(dxGeom* g);

	void computeAABB();
	
	void cleanGeoms();
	void collide(void* UserData, dNearCallback* Callback);
	void collide2(void* UserData, dxGeom* g1, dNearCallback* Callback);

	// Temp data
	Block* CurrentBlock;	// Only used while enumerating
	int* CurrentChild;	// Only used while enumerating
	int CurrentLevel;	// Only used while enumerating
	dxGeom* CurrentObject;	// Only used while enumerating
	int CurrentIndex;
};

dxQuadTreeSpace::dxQuadTreeSpace(dSpaceID _space, const dVector3 Center, const dVector3 Extents, int Depth) : dxSpace(_space){
	type = dQuadTreeSpaceClass;

	int BlockCount = 0;
	// TODO: should be just BlockCount = (4^(n+1) - 1)/3
	for (int i = 0; i <= Depth; i++){
		BlockCount += (int)pow((dReal)SPLITS, i);
	}

	Blocks = (Block*)dAlloc(BlockCount * sizeof(Block));
	Block* Blocks = this->Blocks + 1;	// This pointer gets modified!

	dReal MinX = Center[AXIS0] - Extents[AXIS0];
	dReal MaxX = dNextAfter((Center[AXIS0] + Extents[AXIS0]), (dReal)dInfinity);
	dReal MinZ = Center[AXIS1] - Extents[AXIS1];
	dReal MaxZ = dNextAfter((Center[AXIS1] + Extents[AXIS1]), (dReal)dInfinity);
	this->Blocks[0].Create(MinX, MaxX, MinZ, MaxZ, 0, Depth, Blocks);

	CurrentBlock = 0;
	CurrentChild = (int*)dAlloc((Depth + 1) * sizeof(int));
	CurrentLevel = 0;
	CurrentObject = 0;
	CurrentIndex = -1;

	// Init AABB. We initialize to infinity because it is not illegal for an object to be outside of the tree. Its simply inserted in the root block
	aabb[0] = -dInfinity;
	aabb[1] = dInfinity;
	aabb[2] = -dInfinity;
	aabb[3] = dInfinity;
	aabb[4] = -dInfinity;
	aabb[5] = dInfinity;
}

dxQuadTreeSpace::~dxQuadTreeSpace(){
	int Depth = 0;
	Block* Current = &Blocks[0];
	while (Current){
		Depth++;
		Current = Current->mChildren;
	}

	int BlockCount = 0;
	for (int i = 0; i < Depth; i++){
		BlockCount += (int)pow((dReal)SPLITS, i);
	}

	dFree(Blocks, BlockCount * sizeof(Block));
	dFree(CurrentChild, (Depth + 1) * sizeof(int));
}

dxGeom* dxQuadTreeSpace::getGeom(int Index){
	dUASSERT(Index >= 0 && Index < count, "index out of range");

	//@@@
	dDebug (0,"dxQuadTreeSpace::getGeom() not yet implemented");

	return 0;

	// This doesnt work

	/*if (CurrentIndex == Index){
		// Loop through all objects in the local list
CHILDRECURSE:
		if (CurrentObject){
			dGeomID g = CurrentObject;
			CurrentObject = CurrentObject->next;
			CurrentIndex++;
		
#ifdef DRAWBLOCKS
			DrawBlock(CurrentBlock);
#endif	//DRAWBLOCKS
			return g;
		}
		else{
			// Now lets loop through our children. Starting at index 0.
			if (CurrentBlock->Children){
				CurrentChild[CurrentLevel] = 0;
PARENTRECURSE:
				for (int& i = CurrentChild[CurrentLevel]; i < SPLITS; i++){
					if (CurrentBlock->Children[i].GeomCount == 0){
						continue;
					}
					CurrentBlock = &CurrentBlock->Children[i];
					CurrentObject = CurrentBlock->First;
				
					i++;
				
					CurrentLevel++;
					goto CHILDRECURSE;
				}
			}
		}
		
		// Now lets go back to the parent so it can continue processing its other children.
		if (CurrentBlock->Parent){
			CurrentBlock = CurrentBlock->Parent;
			CurrentLevel--;
			goto PARENTRECURSE;
		}
	}
	else{
		CurrentBlock = &Blocks[0];
		CurrentLevel = 0;
		CurrentObject = CurrentObject;
		CurrentIndex = 0;

		// Other states are already set
		CurrentObject = CurrentBlock->First;
	}


	if (current_geom && current_index == Index - 1){
		//current_geom = current_geom->next; // next
		current_index = Index;
		return current_geom;
	}
	else for (int i = 0; i < Index; i++){	// this will be verrrrrrry slow
		getGeom(i);
	}*/

	return 0;
}

void dxQuadTreeSpace::add(dxGeom* g){
	CHECK_NOT_LOCKED (this);
	dAASSERT(g);
	dUASSERT(g->parent_space == 0 && g->next == 0, "geom is already in a space");

	g->gflags |= GEOM_DIRTY | GEOM_AABB_BAD;
	DirtyList.push(g);

	// add
	g->parent_space = this;
	Blocks[0].GetBlock(g->aabb)->AddObject(g);	// Add to best block
	count++;
	
	// enumerator has been invalidated
	current_geom = 0;
	
	dGeomMoved(this);
}

void dxQuadTreeSpace::remove(dxGeom* g){
	CHECK_NOT_LOCKED(this);
	dAASSERT(g);
	dUASSERT(g->parent_space == this,"object is not in this space");
	
	// remove
	((Block*)g->tome)->DelObject(g);
	count--;

	for (int i = 0; i < DirtyList.size(); i++){
		if (DirtyList[i] == g){
			DirtyList.remove(i);
			// (mg) there can be multiple instances of a dirty object on stack  be sure to remove ALL and not just first, for this we decrement i
			--i;
		}
	}
	
	// safeguard
	g->next = 0;
	g->tome = 0;
	g->parent_space = 0;
	
	// enumerator has been invalidated
	current_geom = 0;
	
	// the bounding box of this space (and that of all the parents) may have
	// changed as a consequence of the removal.
	dGeomMoved(this);
}

void dxQuadTreeSpace::dirty(dxGeom* g){
	DirtyList.push(g);
}

void dxQuadTreeSpace::computeAABB(){
	//
}

void dxQuadTreeSpace::cleanGeoms(){
	// compute the AABBs of all dirty geoms, and clear the dirty flags
	lock_count++;
	
	for (int i = 0; i < DirtyList.size(); i++){
		dxGeom* g = DirtyList[i];
		if (IS_SPACE(g)){
			((dxSpace*)g)->cleanGeoms();
		}
		g->recomputeAABB();
		g->gflags &= (~(GEOM_DIRTY|GEOM_AABB_BAD));

		((Block*)g->tome)->Traverse(g);
	}
	DirtyList.setSize(0);

	lock_count--;
}

void dxQuadTreeSpace::collide(void* UserData, dNearCallback* Callback){
  dAASSERT(Callback);

  lock_count++;
  cleanGeoms();

  Blocks[0].Collide(UserData, Callback);

  lock_count--;
}


struct DataCallback {
        void *data;
        dNearCallback *callback;
};
// Invokes the callback with arguments swapped
static void swap_callback(void *data, dxGeom *g1, dxGeom *g2)
{
        DataCallback *dc = (DataCallback*)data;
        dc->callback(dc->data, g2, g1);
}


void dxQuadTreeSpace::collide2(void* UserData, dxGeom* g2, dNearCallback* Callback){
  dAASSERT(g2 && Callback);

  lock_count++;
  cleanGeoms();
  g2->recomputeAABB();

  if (g2->parent_space == this){
	  // The block the geom is in
	  Block* CurrentBlock = (Block*)g2->tome;
	  
	  // Collide against block and its children
	  DataCallback dc = {UserData, Callback};
	  CurrentBlock->Collide(g2, CurrentBlock->mFirst, &dc, swap_callback);
	  
	  // Collide against parents
	  while ((CurrentBlock = CurrentBlock->mParent))
		  CurrentBlock->CollideLocal(g2, UserData, Callback);

  }
  else {
        DataCallback dc = {UserData, Callback};
        Blocks[0].Collide(g2, Blocks[0].mFirst, &dc, swap_callback);
  }

  lock_count--;
}

dSpaceID dQuadTreeSpaceCreate(dxSpace* space, const dVector3 Center, const dVector3 Extents, int Depth){
	return new dxQuadTreeSpace(space, Center, Extents, Depth);
}
