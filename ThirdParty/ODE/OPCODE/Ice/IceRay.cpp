///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains code for rays.
 *	\file		IceRay.cpp
 *	\author		Pierre Terdiman
 *	\date		April, 4, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Ray class.
 *	A ray is a half-line P(t) = mOrig + mDir * t, with 0 <= t <= +infinity
 *	\class		Ray
 *	\author		Pierre Terdiman
 *	\version	1.0
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	O = Origin = impact point
	i = normalized vector along the x axis
	j = normalized vector along the y axis = actually the normal vector in O
	D = Direction vector, norm |D| = 1
	N = Projection of D on y axis, norm |N| = normal reaction
	T = Projection of D on x axis, norm |T| = tangential reaction
	R = Reflexion vector

              ^y
              |
              |
              |
       _  _  _| _ _ _
       *      *      *|
        \     |     /
         \    |N   /  |
         R\   |   /D
           \  |  /    |
            \ | /
    _________\|/______*_______>x
               O    T

	Let define theta = angle between D and N. Then cos(theta) = |N| / |D| = |N| since D is normalized.

	j|D = |j|*|D|*cos(theta) => |N| = j|D

	Then we simply have:

	D = N + T

	To compute tangential reaction :

	T = D - N

	To compute reflexion vector :

	R = N - T = N - (D-N) = 2*N - D
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Precompiled Header
#include "Stdafx.h"

using namespace IceMaths;

float Ray::SquareDistance(const Point& point, float* t)	const
{
	Point Diff = point - mOrig;
	float fT = Diff | mDir;

	if(fT<=0.0f)
	{
		fT = 0.0f;
	}
	else
	{
		fT /= mDir.SquareMagnitude();
		Diff -= fT*mDir;
	}

	if(t) *t = fT;

	return Diff.SquareMagnitude();
}
