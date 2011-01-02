///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains axes definition.
 *	\file		IceAxes.h
 *	\author		Pierre Terdiman
 *	\date		January, 29, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef __ICEAXES_H__
#define __ICEAXES_H__

	enum PointComponent
	{
		X					= 0,
		Y					= 1,
		Z					= 2,
		W					= 3,

		FORCE_DWORD		= 0x7fffffff
	};

	enum AxisOrder
	{
		AXES_XYZ			= (X)|(Y<<2)|(Z<<4),
		AXES_XZY			= (X)|(Z<<2)|(Y<<4),
		AXES_YXZ			= (Y)|(X<<2)|(Z<<4),
		AXES_YZX			= (Y)|(Z<<2)|(X<<4),
		AXES_ZXY			= (Z)|(X<<2)|(Y<<4),
		AXES_ZYX			= (Z)|(Y<<2)|(X<<4),

		AXES_FORCE_DWORD	= 0x7fffffff
	};

	class ICEMATHS_API Axes
	{
		public:

		inline_			Axes(AxisOrder order)
						{
							mAxis0 = (order   ) & 3;
							mAxis1 = (order>>2) & 3;
							mAxis2 = (order>>4) & 3;
						}
		inline_			~Axes()		{}

				udword	mAxis0;
				udword	mAxis1;
				udword	mAxis2;
	};

#endif // __ICEAXES_H__
