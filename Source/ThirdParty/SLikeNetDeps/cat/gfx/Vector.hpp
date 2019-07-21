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

#ifndef CAT_VECTOR_HPP
#define CAT_VECTOR_HPP

#include <cat/gfx/Scalar.hpp>

namespace cat {

#define FOR_EACH_DIMENSION(index) for (int index = 0; index < DIM; ++index)


// Generic vector class for linear algebra
template<int DIM, typename Scalar, typename Double> class Vector
{
protected:
	// Protected internal storage of vector components
	Scalar _elements[DIM];

public:
	// Short-hand for the current vector type
	typedef Vector<DIM, Scalar, Double> mytype;

	// Uninitialized vector is not cleared
	Vector() {}

	// Component-wise initializing constructors
	Vector(Scalar x, Scalar y)
	{
		_elements[0] = x;
		_elements[1] = y;
	}
	Vector(Scalar x, Scalar y, Scalar z)
	{
		_elements[0] = x;
		_elements[1] = y;
		_elements[2] = z;
	}
	Vector(Scalar x, Scalar y, Scalar z, Scalar w)
	{
		_elements[0] = x;
		_elements[1] = y;
		_elements[2] = z;
		_elements[3] = w;
	}

	// Make the vector a copy of a given vector
	mytype &copy(const mytype &u)
	{
		memcpy(_elements, u._elements, sizeof(_elements));

        return *this;
	}

	// Copy constructor
	Vector(const mytype &u)
	{
		copy(u);
	}

	// Assignment operator
	mytype &operator=(const mytype &u)
	{
        return copy(u);
	}

	// Magnitude calculation
	Double magnitude() const
	{
		Double element, sum = 0;

		FOR_EACH_DIMENSION(ii)
		{
			element = _elements[ii];
			sum += element * element;
		}

		return static_cast<Double>( sqrt(sum) );
	}

	// Fast normalization for 32-bit floating point elements in-place
	mytype &normalize_fast_f32()
	{
		f32 element = _elements[0];
		f32 sum = element * element;

		for (int ii = 1; ii < DIM; ++ii)
		{
			element = _elements[ii];
			sum += element * element;
		}

		// If sum is not close to 1, then perform normalization:
		if (sum > 1.005f || sum < 0.995f)
		{
			f32 inv = InvSqrt(sum);

			FOR_EACH_DIMENSION(ii) _elements[ii] *= inv;
		}

		return *this;
	}

	// Normalization in-place
	mytype &normalize()
	{
		Double m = magnitude();
		Double inv = static_cast<Double>( 1 ) / m;

		FOR_EACH_DIMENSION(ii) _elements[ii] *= inv;

		return *this;
	}

	// Zero elements
	void zero()
	{
		OBJCLR(_elements);
	}

	// Is zero?
	bool isZero()
	{
		FOR_EACH_DIMENSION(ii)
			if (_elements[ii] != static_cast<Scalar>( 0 ))
				return false;

		return true;
	}

	// For consistency with Matrix class, use the () operator instead of [] to index it
	inline Scalar &operator()(int ii) { return _elements[ii]; }
	inline Scalar &x() { return _elements[0]; }
	inline Scalar &y() { return _elements[1]; }
	inline Scalar &z() { return _elements[2]; }
	inline Scalar &w() { return _elements[3]; }

	// Const version for accessors
	inline const Scalar &operator()(int ii) const { return _elements[ii]; }
	inline const Scalar &x() const { return _elements[0]; }
	inline const Scalar &y() const { return _elements[1]; }
	inline const Scalar &z() const { return _elements[2]; }
	inline const Scalar &w() const { return _elements[3]; }

	// Negation
	mytype operator-() const
	{
		mytype x;

		FOR_EACH_DIMENSION(ii) x._elements[ii] = -_elements[ii];

		return x;
	}

	// Negation in-place
	mytype &negate()
	{
		FOR_EACH_DIMENSION(ii) _elements[ii] = -_elements[ii];

		return *this;
	}

	// Addition
	mytype operator+(const mytype &u) const
	{
		mytype x;

		FOR_EACH_DIMENSION(ii) x._elements[ii] = _elements[ii] + u._elements[ii];

		return x;
	}

	// Addition in-place
	mytype &operator+=(const mytype &u)
	{
		FOR_EACH_DIMENSION(ii) _elements[ii] += u._elements[ii];

		return *this;
	}

	// Add a scalar to each element in-place
	mytype &addToEachElement(Scalar u)
	{
		FOR_EACH_DIMENSION(ii) _elements[ii] += u;

		return *this;
	}

	// Subtraction
	mytype operator-(const mytype &u) const
	{
		mytype x;

		FOR_EACH_DIMENSION(ii) x._elements[ii] = _elements[ii] - u._elements[ii];

		return x;
	}

	// Subtraction in-place
	mytype &operator-=(const mytype &u)
	{
		FOR_EACH_DIMENSION(ii) _elements[ii] -= u._elements[ii];

		return *this;
	}

	// Subtract a scalar from each element in-place
	mytype &subtractFromEachElement(Scalar u)
	{
		FOR_EACH_DIMENSION(ii) _elements[ii] -= u;

		return *this;
	}

	// Scalar multiplication
	mytype operator*(Scalar u) const
	{
		mytype x;

		FOR_EACH_DIMENSION(ii) x._elements[ii] = u * _elements[ii];

		return x;
	}

	// Scalar multiplication in-place
	mytype &operator*=(Scalar u)
	{
		FOR_EACH_DIMENSION(ii) _elements[ii] *= u;

		return *this;
	}

	// Component-wise multiply in-place
	mytype &componentMultiply(const mytype &u)
	{
		FOR_EACH_DIMENSION(ii) _elements[ii] *= u._elements[ii];

		return *this;
	}

	// Scalar division
	mytype operator/(Scalar u) const
	{
		mytype x;

		Scalar inv_u = static_cast<Scalar>( 1 ) / static_cast<Scalar>( u );

		FOR_EACH_DIMENSION(ii) x._elements[ii] = _elements[ii] * inv_u;

		return x;
	}

	// Scalar division in-place
	mytype &operator/=(Scalar u)
	{
		Scalar inv_u = static_cast<Scalar>( 1 ) / static_cast<Scalar>( u );

		FOR_EACH_DIMENSION(ii) _elements[ii] *= inv_u;

		return *this;
	}

	// Component-wise divide in-place
	mytype &componentDivide(const mytype &u)
	{
		FOR_EACH_DIMENSION(ii) _elements[ii] /= u._elements[ii];

		return *this;
	}

	// Dot product
	Double dotProduct(const mytype &u) const
	{
		Double sum = 0;

		FOR_EACH_DIMENSION(ii)
			sum += static_cast<Double>( _elements[ii] )
				* static_cast<Double>( u._elements[ii] );

		return sum;
	}

public:
	// Only for 2-element vectors:

	// Generate a 2D rotation vector in-place
	void generateRotation2D(f32 angle)
	{
		x() = cos(angle);
		y() = sin(angle);
	}

	// Add rotation vector in-place
	mytype &addRotation2D(const mytype &r)
	{
		Double ax = x(), ay = y();
		Double rx = r.x(), ry = r.y();

		x() = static_cast<Scalar>( ax*rx - ay*ry ); // cos(a+r) = cos(a)*cos(r) - sin(a)*sin(r)
		y() = static_cast<Scalar>( ay*rx + ax*ry ); // sin(a+r) = sin(a)*cos(r) + cos(a)*sin(r)

		return *this;
	}

	// Subtract rotation vector in-place
	mytype &subtractRotation2D(const mytype &r)
	{
		Double ax = x(), ay = y();
		Double rx = r.x(), ry = r.y();

		x() = static_cast<Scalar>( ax*rx + ay*ry ); // cos(a-r) = cos(a)*cos(r) + sin(a)*sin(r)
		y() = static_cast<Scalar>( ay*rx - ax*ry ); // sin(a-r) = sin(a)*cos(r) - cos(a)*sin(r)

		return *this;
	}

	// Cross product: Result is a scalar
	f32 crossProduct2D(const mytype &u)
	{
		return x() * u.y() - y() * u.x();
	}

public:
	// Only for 3-element vectors:

	// Cross product: Result is a 3D vector
	mytype crossProduct3D(const mytype &u)
	{
		mytype result;

		result.x() = y() * u.z() - z() * u.y();
		result.y() = z() * u.x() - x() * u.z();
		result.z() = x() * u.y() - y() * u.x();

		return result;
	}
};


// Short-hand for common usages:

typedef Vector<2, u32, u32> Vector2u;
typedef Vector<3, u32, u32> Vector3u;
typedef Vector<4, u32, u32> Vector4u;

typedef Vector<2, s32, s32> Vector2s;
typedef Vector<3, s32, s32> Vector3s;
typedef Vector<4, s32, s32> Vector4s;

typedef Vector<2, f32, f64> Vector2f;
typedef Vector<3, f32, f64> Vector3f;
typedef Vector<4, f32, f64> Vector4f;

typedef Vector<2, f64, f64> Vector2d;
typedef Vector<3, f64, f64> Vector3d;
typedef Vector<4, f64, f64> Vector4d;


#undef FOR_EACH_DIMENSION

} // namespace cat

#endif // CAT_VECTOR_HPP
