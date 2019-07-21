/*
	Copyright (c) 2009 Christopher A. Taylor.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	* Neither the name of LibCat nor the names of its contributors may be used
	  to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

/*
    Based on code from "Physics for Game Developers", David M. Bourg

    slerp() code adapted from this website:
    http://www.number-none.com/product/Understanding%20Slerp,%20Then%20Not%20Using%20It/index.html
*/

#ifndef CAT_QUATERNION_HPP
#define CAT_QUATERNION_HPP

#include <cat/gfx/Vector.hpp>
#include <cat/gfx/Matrix.hpp>

namespace cat {


// Generic quaternion class for linear algebra
template <typename Scalar, typename Double>
class Quaternion
{
protected:
	// Backed by a 4D vector with elements arranged as <x,y,z,w>
	Vector<4, Scalar, Double> _v;

public:
	// Short-hand for the current quaternion type
	typedef Quaternion<Scalar, Double> mytype;

	// Short-hand for the vector type
	typedef Vector<3, Scalar, Double> vectype;

	// Uninitialized quaternion is not cleared
	Quaternion() { }

	// Copy constructor
	Quaternion(const mytype &u)
		: _v(u._v)
	{
	}

	// Initialization constructor
	Quaternion(const vectype &v, Scalar w)
		: _v(v)
	{
	}

	// Initialization constructor
	Quaternion(Scalar x, Scalar y, Scalar z, Scalar w)
		: _v(x, y, z, w)
	{
	}

	// Assignment operator
	mytype &operator=(const mytype &u)
	{
		_v.copy(u._v);

		return *this;
	}

	// Convert from Euler angle representation
	// Pre-condition: angles in radians (see Deg2Rad in Scalar.hpp)
	void setFromEulerAngles(f32 xroll, f32 ypitch, f32 zyaw)
	{
		f64 croll = cos(0.5f * xroll);
		f64 cpitch = cos(0.5f * ypitch);
		f64 cyaw = cos(0.5f * zyaw);
		f64 sroll = sin(0.5f * xroll);
		f64 spitch = sin(0.5f * ypitch);
		f64 syaw = sin(0.5f * zyaw);

		f64 cyawcpitch = cyaw * cpitch;
		f64 syawspitch = syaw * spitch;
		f64 cyawspitch = cyaw * spitch;
		f64 syawcpitch = syaw * cpitch;

		_v(0) = static_cast<Scalar>( cyawcpitch * sroll - syawspitch * croll );
		_v(1) = static_cast<Scalar>( cyawspitch * croll + syawcpitch * sroll );
		_v(2) = static_cast<Scalar>( syawcpitch * croll - cyawspitch * sroll );
		_v(3) = static_cast<Scalar>( cyawcpitch * croll + syawspitch * sroll );

		_v.normalize();
	}

	// Convert from axis-angle representation
	// Pre-condition: axis must be unit-length
	void setFromAxisAngle(const vectype &axis, f32 angle)
	{
		angle *= 0.5f;

		Scalar theta = static_cast<Scalar>( sin(angle) );

		_v(0) = theta * axis(0);
		_v(1) = theta * axis(1);
		_v(2) = theta * axis(2);
		_v(3) = static_cast<Scalar>( cos(angle) );
	}

	// Conjugate
	mytype operator~() const
	{
		return mytype(-_v(0), -_v(1), -_v(2), _v(3));
	}

	// Conjugate in-place
	mytype &conjugate() const
	{
		_v(0) = -_v(0);
		_v(1) = -_v(1);
		_v(2) = -_v(2);

		return *this;
	}

	// Multiply by quaternion
	mytype operator*(const mytype &u)
	{
		// Cache each of the elements since each is used 4 times
		Double x1 = _v(0), x2 = u._v(0);
		Double y1 = _v(1), y2 = u._v(1);
		Double z1 = _v(2), z2 = u._v(2);
		Double w1 = _v(3), w2 = u._v(3);

		// Quaternion multiplication formula:
		Scalar x3 = static_cast<Scalar>( w1*x2 + x1*w2 + y1*z2 - z1*y2 );
		Scalar y3 = static_cast<Scalar>( w1*y2 - x1*z2 + y1*w2 + z1*x2 );
		Scalar z3 = static_cast<Scalar>( w1*z2 + x1*y2 - y1*x2 + z1*w2 );
		Scalar w3 = static_cast<Scalar>( w1*w2 - x1*x2 - y1*y2 - z1*z2 );

		return mytype(x3, y3, z3, w3);
	}

	// Multiply by quaternion in-place: this = this * u
	mytype &operator*=(const mytype &u)
	{
		// Cache each of the elements since each is used 4 times
		Double x1 = _v(0), x2 = u._v(0);
		Double y1 = _v(1), y2 = u._v(1);
		Double z1 = _v(2), z2 = u._v(2);
		Double w1 = _v(3), w2 = u._v(3);

		// Quaternion multiplication formula:
		_v(0) = static_cast<Scalar>( w1*x2 + x1*w2 + y1*z2 - z1*y2 );
		_v(1) = static_cast<Scalar>( w1*y2 - x1*z2 + y1*w2 + z1*x2 );
		_v(2) = static_cast<Scalar>( w1*z2 + x1*y2 - y1*x2 + z1*w2 );
		_v(3) = static_cast<Scalar>( w1*w2 - x1*x2 - y1*y2 - z1*z2 );

		return *this;
	}

	// Multiply by quaternion in-place: this = u * this
	mytype &postMultiply(const mytype &u)
	{
		// Cache each of the elements since each is used 4 times
		Double x2 = _v(0), x1 = u._v(0);
		Double y2 = _v(1), y1 = u._v(1);
		Double z2 = _v(2), z1 = u._v(2);
		Double w2 = _v(3), w1 = u._v(3);

		// Quaternion multiplication formula:
		_v(0) = static_cast<Scalar>( w1*x2 + x1*w2 + y1*z2 - z1*y2 );
		_v(1) = static_cast<Scalar>( w1*y2 - x1*z2 + y1*w2 + z1*x2 );
		_v(2) = static_cast<Scalar>( w1*z2 + x1*y2 - y1*x2 + z1*w2 );
		_v(3) = static_cast<Scalar>( w1*w2 - x1*x2 - y1*y2 - z1*z2 );

		return *this;
	}

	// Rotate given vector in-place
	void rotate(vectype &u)
	{
		// Implements the simple formula: (q1 * u2 * ~q1).getVector()

		// Cache each of the elements since each is used 4 times
		Double x1 = _v(0), x2 = u(0);
		Double y1 = _v(1), y2 = u(1);
		Double z1 = _v(2), z2 = u(2);
		Double w1 = _v(3);

		// Quaternion-vector multiplication formula (q3 = q1 * u2):
		Double x3 = w1*x2 + y1*z2 - z1*y2;
		Double y3 = w1*y2 - x1*z2 + z1*x2;
		Double z3 = w1*z2 + x1*y2 - y1*x2;
		Double w3 = -(x1*x2 + y1*y2 + z1*z2);

		// Quaternion multiplication formula (q2' = q3 * ~q1):
		u(0) = static_cast<Scalar>( w1*x3 - x1*w3 + y1*z3 - z1*y3 );
		u(1) = static_cast<Scalar>( w1*y3 - x1*z3 - y1*w3 + z1*x3 );
		u(2) = static_cast<Scalar>( w1*z3 + x1*y3 - y1*x3 - z1*w3 );
	}

	// NLERP: Very fast, non-constant velocity and torque-minimal
	// Precondition: q1, q2 are unit length
	friend void nlerp(const mytype &q1, const mytype &q2, Scalar t, mytype &result)
	{
		// Linearly interpolate and normalize result
		// This formula is a little more work than "q1 + (q2 - q1) * t"
		// but less likely to lose precision when it matters

		// Cosine of phi, the angle between the two vectors
		Double cos_phi = q1._v.dotProduct(q2._v);

		// I have read this may try to rotate around the "long way" sometimes and to
		// fix that we check if cos(phi) is negative and invert one of the inputs.
		if (cos_phi < 0.0)
		{
			result._v = -q1._v;
		}
		else
		{
			result._v = q1._v;
		}

		// Simple linear interpolation
		Scalar scale0 = static_cast<Scalar>(1) - t;
		Scalar scale1 = t;

		result._v *= scale0;
		result._v += q2._v * scale1;
		result._v.normalize();
	}

	// SLERP: Slower, constant velocity and torque-minimal
	// Precondition: q1, q2 are unit length
	friend void slerp(const mytype &q1, const mytype &q2, Scalar t, mytype &result)
	{
		// Cosine of phi, the angle between the two vectors
		Double cos_phi = q1._v.dotProduct(q2._v);

		// I have read this may try to rotate around the "long way" sometimes and to
		// fix that we check if cos(phi) is negative and invert one of the inputs.
		if (cos_phi < 0.0)
		{
			cos_phi = -cos_phi;
			result._v = -q1._v;
		}
		else
		{
			result._v = q1._v;
		}

		// Default to simple linear interpolation
		Scalar scale0 = static_cast<Scalar>(1) - t;
		Scalar scale1 = t;

		// If the distance is not small we need to do full slerp:
		if (cos_phi < 0.9995)
		{
			// cos_phi is guaranteed to be within the domain of acos(), 0..1
			Double phi = static_cast<Double>( acos(cos_phi) );
			Double inv_sin_phi = static_cast<Double>(1) / sin(phi);

			scale0 = static_cast<Scalar>( sin(scale0 * phi) * inv_sin_phi );
			scale1 = static_cast<Scalar>( sin(scale1 * phi) * inv_sin_phi );
		}

		result._v *= scale0;
		result._v += q2._v * scale1;
		result._v.normalize();
	}

	// Get angle of rotation
	Scalar getAngle()
	{
        return static_cast<Scalar>( 2 ) * static_cast<Scalar>( acos(_v(3)) );
	}

	// Get axis of rotation
	vectype getAxis()
	{
		return vectype(_v(0), _v(1), _v(2)).normalize();
	}

	// Get matrix form of the rotation represented by this quaternion
	void getMatrix4x4(Matrix<4, 4, Scalar> &result)
	{
		Double dx = _v(0);
		Double dy = _v(1);
		Double dz = _v(2);
		Double dw = _v(3);

		Double x2 = dx * dx;
		Double y2 = dy * dy;
		Double z2 = dz * dz;
		Double xy = dx * dy;
		Double yz = dy * dz;
		Double zx = dz * dx;
		Double xw = dx * dw;
		Double yw = dy * dw;
		Double zw = dz * dw;

		const Double ONE = static_cast<Double>( 1 );
		const Double TWO = static_cast<Double>( 2 );

		// Result is written in OpenGL column-major matrix order:
		result( 0) = static_cast<Scalar>( ONE - TWO * (y2 + z2) );
		result( 1) = static_cast<Scalar>( TWO * (xy - zw) );
		result( 2) = static_cast<Scalar>( TWO * (zx + yw) );
		result( 3) = static_cast<Scalar>( 0 );

		result( 4) = static_cast<Scalar>( TWO * (xy + zw) );
		result( 5) = static_cast<Scalar>( ONE - TWO * (x2 + z2) );
		result( 6) = static_cast<Scalar>( TWO * (yz - xw) );
		result( 7) = static_cast<Scalar>( 0 );

		result( 8) = static_cast<Scalar>( TWO * (zx - yw) );
		result( 9) = static_cast<Scalar>( TWO * (yz + xw) );
		result(10) = static_cast<Scalar>( ONE - TWO * (x2 + y2) );
		result(11) = static_cast<Scalar>( 0 );

		result(12) = static_cast<Scalar>( 0 );
		result(13) = static_cast<Scalar>( 0 );
		result(14) = static_cast<Scalar>( 0 );
		result(15) = static_cast<Scalar>( ONE );
	}

	// Get Euler angles
	vectype Quaternion::getEulerAngles()
	{
		Double dx = _v(0);
		Double dy = _v(1);
		Double dz = _v(2);
		Double dw = _v(3);

		Double x2 = dx * dx;
		Double y2 = dy * dy;
		Double z2 = dz * dz;
		Double w2 = dw * dw;
		Double xy = dx * dy;
		Double yz = dy * dz;
		Double xw = dx * dw;
		Double yw = dy * dw;
		Double zw = dz * dw;

		const Double TWO = static_cast<Double>( 2 );

		Double r11 = w2 + x2 - y2 - z2;
		Double r21 = TWO * (xy + zw);
		Double r31 = TWO * (xy - yw);
		Double r32 = TWO * (yz + xw);
		Double r33 = w2 - x2 - y2 + z2;

		Double tmp = fabs(r31);
		const Double LIMIT = static_cast<Double>( 0.999999 );

		if (tmp > LIMIT)
		{
			Double xz = dx * dz;

			Double r12 = TWO * (yz - zw);
			Double r13 = TWO * (xz + yw);

			return vectype(static_cast<Scalar>( 0 ),
						   static_cast<Scalar>( -CAT_HALF_PI_64 * r31 / tmp ),
						   static_cast<Scalar>( atan2(-r12, -r31 * r13) ));
		}

		return vectype(static_cast<Scalar>( atan2(r32, r33) ),
					   static_cast<Scalar>( asin(-r31) ),
					   static_cast<Scalar>( atan2(r21, r11) ));
	}
};


// Short-hand for common usages:

typedef Quaternion<f32, f64> Quaternion4f;
typedef Quaternion<f64, f64> Quaternion4d;


} // namespace cat

#endif // CAT_QUATERNION_HPP
