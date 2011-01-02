///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains code for segments.
 *	\file		IceSegment.h
 *	\author		Pierre Terdiman
 *	\date		April, 4, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef __ICESEGMENT_H__
#define __ICESEGMENT_H__

	class ICEMATHS_API Segment
	{
		public:
		//! Constructor
		inline_					Segment()															{}
		//! Constructor
		inline_					Segment(const Point& p0, const Point& p1) : mP0(p0), mP1(p1)		{}
		//! Copy constructor
		inline_					Segment(const Segment& seg) : mP0(seg.mP0), mP1(seg.mP1)			{}
		//! Destructor
		inline_					~Segment()															{}

		inline_	const	Point&	GetOrigin()						const	{ return mP0;						}
		inline_			Point	ComputeDirection()				const	{ return mP1 - mP0;					}
		inline_			void	ComputeDirection(Point& dir)	const	{ dir = mP1 - mP0;					}
		inline_			float	ComputeLength()					const	{ return mP1.Distance(mP0);			}
		inline_			float	ComputeSquareLength()			const	{ return mP1.SquareDistance(mP0);	}

		inline_			void	SetOriginDirection(const Point& origin, const Point& direction)
								{
									mP0 = mP1 = origin;
									mP1 += direction;
								}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Computes a point on the segment
		 *	\param		pt	[out] point on segment
		 *	\param		t	[in] point's parameter [t=0 => pt = mP0, t=1 => pt = mP1]
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline_			void	ComputePoint(Point& pt, float t)	const	{	pt = mP0 + t * (mP1 - mP0);		}

						float	SquareDistance(const Point& point, float* t=null)	const;
		inline_			float	Distance(const Point& point, float* t=null)			const			{ return sqrtf(SquareDistance(point, t));	}

						Point	mP0;		//!< Start of segment
						Point	mP1;		//!< End of segment
	};

#endif // __ICESEGMENT_H__
