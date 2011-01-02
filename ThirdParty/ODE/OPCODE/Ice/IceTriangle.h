///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains a handy triangle class.
 *	\file		IceTriangle.h
 *	\author		Pierre Terdiman
 *	\date		January, 17, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef __ICETRIANGLE_H__
#define __ICETRIANGLE_H__

	// Forward declarations
	class Moment;

	// Partitioning values
	enum PartVal
	{
		TRI_MINUS_SPACE		= 0,			//!< Triangle is in the negative space
		TRI_PLUS_SPACE		= 1,			//!< Triangle is in the positive space
		TRI_INTERSECT		= 2,			//!< Triangle intersects plane
		TRI_ON_PLANE		= 3,			//!< Triangle and plane are coplanar

		TRI_FORCEDWORD		= 0x7fffffff
	};

	// A triangle class.
	class ICEMATHS_API Triangle
	{
		public:
		//! Constructor
		inline_					Triangle()													{}
		//! Constructor
		inline_					Triangle(const Point& p0, const Point& p1, const Point& p2)	{ mVerts[0]=p0; mVerts[1]=p1; mVerts[2]=p2; }
		//! Copy constructor
		inline_					Triangle(const Triangle& triangle)
								{
									mVerts[0] = triangle.mVerts[0];
									mVerts[1] = triangle.mVerts[1];
									mVerts[2] = triangle.mVerts[2];
								}
		//! Destructor
		inline_					~Triangle()													{}
		//! Vertices
				Point			mVerts[3];

		// Methods
				void			Flip();
				float			Area() const;
				float			Perimeter()	const;
				float			Compacity()	const;
				void			Normal(Point& normal) const;
				void			DenormalizedNormal(Point& normal) const;
				void			Center(Point& center) const;
		inline_	Plane			PlaneEquation() const	{ return Plane(mVerts[0], mVerts[1], mVerts[2]);	}

				PartVal			TestAgainstPlane(const Plane& plane, float epsilon) const;
//				float			Distance(Point& cp, Point& cq, Tri& tri);
				void			ComputeMoment(Moment& m);
				float			MinEdgeLength() const;
				float			MaxEdgeLength() const;
				void			ComputePoint(float u, float v, Point& pt, udword* nearvtx=null)	const;
				void			Inflate(float fat_coeff, bool constant_border);
	};

#endif // __ICETRIANGLE_H__
