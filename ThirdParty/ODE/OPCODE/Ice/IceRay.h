///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains code for rays.
 *	\file		IceRay.h
 *	\author		Pierre Terdiman
 *	\date		April, 4, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef __ICERAY_H__
#define __ICERAY_H__

	class ICEMATHS_API Ray
	{
		public:
		//! Constructor
		inline_					Ray()																{}
		//! Constructor
		inline_					Ray(const Point& orig, const Point& dir) : mOrig(orig), mDir(dir)	{}
		//! Copy constructor
		inline_					Ray(const Ray& ray) : mOrig(ray.mOrig), mDir(ray.mDir)				{}
		//! Destructor
		inline_					~Ray()																{}

						float	SquareDistance(const Point& point, float* t=null)	const;
		inline_			float	Distance(const Point& point, float* t=null)			const			{ return sqrtf(SquareDistance(point, t));	}

						Point	mOrig;		//!< Ray origin
						Point	mDir;		//!< Normalized direction
	};

	inline_ void ComputeReflexionVector(Point& reflected, const Point& incoming_dir, const Point& outward_normal)
	{
		reflected = incoming_dir - outward_normal * 2.0f * (incoming_dir|outward_normal);
	}

	inline_ void ComputeReflexionVector(Point& reflected, const Point& source, const Point& impact, const Point& normal)
	{
		Point V = impact - source;
		reflected = V - normal * 2.0f * (V|normal);
	}

	inline_ void DecomposeVector(Point& normal_compo, Point& tangent_compo, const Point& outward_dir, const Point& outward_normal)
	{
		normal_compo = outward_normal * (outward_dir|outward_normal);
		tangent_compo = outward_dir - normal_compo;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 *	Transforms a direction vector from world space to local space
	 *	\param		local_dir	[out] direction vector in local space
	 *	\param		world_dir	[in] direction vector in world space
	 *	\param		world		[in] world transform
	 */
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	inline_ void ComputeLocalDirection(Point& local_dir, const Point& world_dir, const Matrix4x4& world)
	{
		// Get world direction back in local space
//		Matrix3x3 InvWorld = world;
//		local_dir = InvWorld * world_dir;
		local_dir = Matrix3x3(world) * world_dir;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 *	Transforms a position vector from world space to local space
	 *	\param		local_pt	[out] position vector in local space
	 *	\param		world_pt	[in] position vector in world space
	 *	\param		world		[in] world transform
	 */
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	inline_ void ComputeLocalPoint(Point& local_pt, const Point& world_pt, const Matrix4x4& world)
	{
		// Get world vertex back in local space
		Matrix4x4 InvWorld = world;
		InvWorld.Invert();
		local_pt = world_pt * InvWorld;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 *	Transforms a ray from world space to local space
	 *	\param		local_ray	[out] ray in local space
	 *	\param		world_ray	[in] ray in world space
	 *	\param		world		[in] world transform
	 */
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	inline_ void ComputeLocalRay(Ray& local_ray, const Ray& world_ray, const Matrix4x4& world)
	{
		// Get world ray back in local space
		ComputeLocalDirection(local_ray.mDir, world_ray.mDir, world);
		ComputeLocalPoint(local_ray.mOrig, world_ray.mOrig, world);
	}

#endif // __ICERAY_H__
