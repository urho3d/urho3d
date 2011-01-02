///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *	OPCODE - Optimized Collision Detection
 *	Copyright (C) 2001 Pierre Terdiman
 *	Homepage: http://www.codercorner.com/Opcode.htm
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains code for an AABB collider.
 *	\file		OPC_AABBCollider.h
 *	\author		Pierre Terdiman
 *	\date		January, 1st, 2002
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef __OPC_AABBCOLLIDER_H__
#define __OPC_AABBCOLLIDER_H__

	struct OPCODE_API AABBCache : VolumeCache
	{
						AABBCache() : FatCoeff(1.1f)
						{
							FatBox.mCenter.Zero();
							FatBox.mExtents.Zero();
						}

		// Cached faces signature
		CollisionAABB	FatBox;		//!< Box used when performing the query resulting in cached faces
		// User settings
		float			FatCoeff;	//!< mRadius2 multiplier used to create a fat sphere
	};

	class OPCODE_API AABBCollider : public VolumeCollider
	{
		public:
		// Constructor / Destructor
											AABBCollider();
		virtual								~AABBCollider();

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Generic collision query for generic OPCODE models. After the call, access the results:
		 *	- with GetContactStatus()
		 *	- with GetNbTouchedPrimitives()
		 *	- with GetTouchedPrimitives()
		 *
		 *	\param		cache			[in/out] a box cache
		 *	\param		box				[in] collision AABB in world space
		 *	\param		model			[in] Opcode model to collide with
		 *	\return		true if success
		 *	\warning	SCALE NOT SUPPORTED. The matrices must contain rotation & translation parts only.
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							bool			Collide(AABBCache& cache, const CollisionAABB& box, const Model& model);
		//
							bool			Collide(AABBCache& cache, const CollisionAABB& box, const AABBTree* tree);
		protected:
							CollisionAABB	mBox;			//!< Query box in (center, extents) form
							Point			mMin;			//!< Query box min point
							Point			mMax;			//!< Query box max point
		// Leaf description
							Point			mLeafVerts[3];	//!< Triangle vertices
		// Internal methods
							void			_Collide(const AABBCollisionNode* node);
							void			_Collide(const AABBNoLeafNode* node);
							void			_Collide(const AABBQuantizedNode* node);
							void			_Collide(const AABBQuantizedNoLeafNode* node);
							void			_Collide(const AABBTreeNode* node);
							void			_CollideNoPrimitiveTest(const AABBCollisionNode* node);
							void			_CollideNoPrimitiveTest(const AABBNoLeafNode* node);
							void			_CollideNoPrimitiveTest(const AABBQuantizedNode* node);
							void			_CollideNoPrimitiveTest(const AABBQuantizedNoLeafNode* node);
			// Overlap tests
		inline_				BOOL			AABBContainsBox(const Point& bc, const Point& be);
		inline_				BOOL			AABBAABBOverlap(const Point& b, const Point& Pb);
		inline_				BOOL			TriBoxOverlap();
			// Init methods
							BOOL			InitQuery(AABBCache& cache, const CollisionAABB& box);
	};

	class OPCODE_API HybridAABBCollider : public AABBCollider
	{
		public:
		// Constructor / Destructor
											HybridAABBCollider();
		virtual								~HybridAABBCollider();

							bool			Collide(AABBCache& cache, const CollisionAABB& box, const HybridModel& model);
		protected:
							Container		mTouchedBoxes;
	};

#endif // __OPC_AABBCOLLIDER_H__
