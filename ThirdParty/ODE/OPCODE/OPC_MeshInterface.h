///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *	OPCODE - Optimized Collision Detection
 *	Copyright (C) 2001 Pierre Terdiman
 *	Homepage: http://www.codercorner.com/Opcode.htm
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains a mesh interface.
 *	\file		OPC_MeshInterface.h
 *	\author		Pierre Terdiman
 *	\date		November, 27, 2002
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef __OPC_MESHINTERFACE_H__
#define __OPC_MESHINTERFACE_H__

	struct VertexPointers
	{
		const Point*	Vertex[3];
		
		bool BackfaceCulling(const Point& source)
		{
			const Point& p0 = *Vertex[0];
			const Point& p1 = *Vertex[1];
			const Point& p2 = *Vertex[2];

			// Compute normal direction
			Point Normal = (p2 - p1)^(p0 - p1);

			// Backface culling
			return (Normal | (source - p0)) >= 0.0f;
		}
	};

	struct VertexPointersEx
	{
		VertexPointers	vp;
		dTriIndex	Index[3];
	};

	typedef			Point				ConversionArea[3];

#ifdef OPC_USE_CALLBACKS
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 *	User-callback, called by OPCODE to request vertices from the app.
	 *	\param		triangle_index	[in] face index for which the system is requesting the vertices
	 *	\param		triangle		[out] triangle's vertices (must be provided by the user)
	 *	\param		user_data		[in] user-defined data from SetCallback()
	 */
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef void	(*RequestCallback)	(udword triangle_index, VertexPointers& triangle, void* user_data);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	*	User-callback, called by OPCODE to request vertex indices from the app.
	*	\param		triangle_index	[in] face index for which the system is requesting the vertices
	*	\param		triangle		[out] triangle's vertices with indices (must be provided by the user)
	*	\param		user_data		[in] user-defined data from SetExCallback()
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef void	(*RequestExCallback)	(udword triangle_index, VertexPointersEx& triangle, void* user_data);
#endif

	class OPCODE_API MeshInterface
	{
		public:
		// Constructor / Destructor
											MeshInterface();
											~MeshInterface();
		// Common settings
		inline_			udword				GetNbTriangles()	const	{ return mNbTris;	}
		inline_			udword				GetNbVertices()		const	{ return mNbVerts;	}
		inline_			void				SetNbTriangles(udword nb)	{ mNbTris = nb;		}
		inline_			void				SetNbVertices(udword nb)	{ mNbVerts = nb;	}

#ifdef OPC_USE_CALLBACKS
		// Callback settings

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Callback control: setups object callback. Must provide triangle-vertices for a given triangle index.
		 *	\param		callback	[in] user-defined callback
		 *	\param		user_data	[in] user-defined data
		 *	\return		true if success
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						bool				SetCallback(RequestCallback callback, void* user_data);
		inline_			void*				GetUserData()		const	{ return mUserData;		}
		inline_			RequestCallback		GetCallback()		const	{ return mObjCallback;	}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		*	Callback control: setups object callback. Must provide triangle-vertices for a given triangle index.
		*	\param		callback	[in] user-defined callback
		*	\param		user_data	[in] user-defined data
		*	\return		true if success
		*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool				SetExCallback(RequestExCallback callback, void* user_data);
		inline_			void*				GetExUserData()		const	{ return mExUserData;		}
		inline_			RequestExCallback	GetExCallback()		const	{ return mObjExCallback;	}
#else
		// Pointers settings

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Pointers control: setups object pointers. Must provide access to faces and vertices for a given object.
		 *	\param		tris	[in] pointer to triangles
		 *	\param		verts	[in] pointer to vertices
		 *	\return		true if success
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						bool				SetPointers(const IndexedTriangle* tris, const Point* verts);
		inline_	const	IndexedTriangle*	GetTris()			const	{ return mTris;			}
		inline_	const	Point*				GetVerts()			const	{ return mVerts;		}

	#ifdef OPC_USE_STRIDE
		// Strides settings

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Strides control
		 *	\param		tri_stride		[in] size of a triangle in bytes. The first sizeof(IndexedTriangle) bytes are used to get vertex indices.
		 *	\param		vertex_stride	[in] size of a vertex in bytes. The first sizeof(Point) bytes are used to get vertex position.
		 *	\return		true if success
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						bool				SetStrides(udword tri_stride=sizeof(IndexedTriangle), udword vertex_stride=sizeof(Point));
		inline_			udword				GetTriStride()		const	{ return mTriStride;	}
		inline_			udword				GetVertexStride()	const	{ return mVertexStride;	}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		*	Single/Double control
		*	\param		value		[in] Indicates if mesh data is provided as array of \c single values. If \c false, data is expected to contain \c double elements.
		*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline_			void				SetSingle(bool value)
											{
												mFetchTriangle = (value ? &MeshInterface::FetchTriangleFromSingles : &MeshInterface::FetchTriangleFromDoubles);
												mFetchExTriangle = (value ? &MeshInterface::FetchExTriangleFromSingles : &MeshInterface::FetchExTriangleFromDoubles);
											}

	#else
		inline_			bool				SetStrides(udword tri_stride=sizeof(IndexedTriangle), udword vertex_stride=sizeof(Point)) { return true; }
		inline_			void				SetSingle(bool value) {}
		inline_			udword				GetTriStride()		const	{ return sizeof(IndexedTriangle);	}
		inline_			udword				GetVertexStride()	const	{ return sizeof(Point);	}
	#endif
#endif

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Fetches a triangle given a triangle index.
		 *	\param		vp		[out] required triangle's vertex pointers
		 *	\param		index	[in] triangle index
		 *	\param		vc      [in,out] storage required for data conversion (pass local variable with same scope as \a vp, as \a vp may point to this memory on return)
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline_			void				GetTriangle(VertexPointers& vp, udword index, ConversionArea vc)	const
											{
#ifdef OPC_USE_CALLBACKS
												(mObjCallback)(index, vp, mUserData);
#else
	#ifdef OPC_USE_STRIDE
												// Since there was conditional statement "if (Single)" which was unpredictable for compiler 
												// and required both branches to be always generated what made inlining a questionable 
												// benefit, I consider it better to introduce a forced call
												// but get rig of branching and dead code injection.
												((*this).*mFetchTriangle)(vp, index, vc);
	#else
												const Point* Verts = GetVerts();
												const IndexedTriangle* T = &mTris[index];
												vp.Vertex[0] = &Verts[T->mVRef[0]];
												vp.Vertex[1] = &Verts[T->mVRef[1]];
												vp.Vertex[2] = &Verts[T->mVRef[2]];
	#endif
#endif
											}

		inline_			bool				GetExTriangle(VertexPointersEx& vpe, udword index, ConversionArea vc)	const
											{
#ifdef OPC_USE_CALLBACKS
												if (mObjExCallback) { (mObjExCallback)(index, vpe, mUserData); return true; }
												else { (mObjCallback)(index, vpe.vp, mUserData); return false; }
#else
	#ifdef OPC_USE_STRIDE
												// Since there was conditional statement "if (Single)" which was unpredictable for compiler 
												// and required both branches to be always generated what made inlining a questionable 
												// benefit, I consider it better to introduce a forced call
												// but get rig of branching and dead code injection.
												((*this).*mFetchExTriangle)(vpe, index, vc);
												return true;
	#else
												const Point* Verts = GetVerts();
												const IndexedTriangle* T = &mTris[index];
												dTriIndex VertIndex0 = T->mVRef[0];
												vpe.Index[0] = VertIndex0;
												vpe.vp.Vertex[0] = &Verts[VertIndex0];
												dTriIndex VertIndex1 = T->mVRef[1];
												vpe.Index[1] = VertIndex1;
												vpe.vp.Vertex[1] = &Verts[VertIndex1];
												dTriIndex VertIndex2 = T->mVRef[2];
												vpe.Index[2] = VertIndex2;
												vpe.vp.Vertex[2] = &Verts[VertIndex2];
												return true;
	#endif
#endif
											}

		private:
#ifndef OPC_USE_CALLBACKS
	#ifdef OPC_USE_STRIDE
		void				FetchTriangleFromSingles(VertexPointers& vp, udword index, ConversionArea vc) const;
		void				FetchTriangleFromDoubles(VertexPointers& vp, udword index, ConversionArea vc) const;
		void				FetchExTriangleFromSingles(VertexPointersEx& vpe, udword index, ConversionArea vc) const;
		void				FetchExTriangleFromDoubles(VertexPointersEx& vpe, udword index, ConversionArea vc) const;
	#endif
#endif

		public:
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Remaps client's mesh according to a permutation.
		 *	\param		nb_indices	[in] number of indices in the permutation (will be checked against number of triangles)
		 *	\param		permutation	[in] list of triangle indices
		 *	\return		true if success
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool				RemapClient(udword nb_indices, const dTriIndex* permutation)	const;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Checks the mesh interface is valid, i.e. things have been setup correctly.
		 *	\return		true if valid
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						bool				IsValid()		const;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Checks the mesh itself is valid.
		 *	Currently we only look for degenerate faces.
		 *	\return		number of degenerate faces
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						udword				CheckTopology()	const;
		private:

						udword				mNbTris;			//!< Number of triangles in the input model
						udword				mNbVerts;			//!< Number of vertices in the input model
#ifdef OPC_USE_CALLBACKS
		// User callback
						void*				mUserData;			//!< User-defined data sent to callback
						RequestCallback		mObjCallback;		//!< Object callback
						void*				mExUserData;		//!< User-defined data sent to ex-callback
						RequestExCallback	mObjExCallback;		//!< Object ex-callback
#else
		// User pointers
	#ifdef OPC_USE_STRIDE
						udword				mTriStride;			//!< Possible triangle stride in bytes [Opcode 1.3]
						udword				mVertexStride;		//!< Possible vertex stride in bytes [Opcode 1.3]
				typedef	void (MeshInterface:: *TriangleFetchProc)(VertexPointers& vp, udword index, ConversionArea vc) const;
						TriangleFetchProc	mFetchTriangle;
				typedef	void (MeshInterface:: *ExTriangleFetchProc)(VertexPointersEx& vpe, udword index, ConversionArea vc) const;
						ExTriangleFetchProc	mFetchExTriangle;
	#endif
						const	IndexedTriangle*	mTris;				//!< Array of indexed triangles
						const	Point*				mVerts;				//!< Array of vertices
#endif
	};

#endif //__OPC_MESHINTERFACE_H__
