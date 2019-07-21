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

#ifndef CAT_MATRIX_HPP
#define CAT_MATRIX_HPP

#include <cat/gfx/Vector.hpp>

namespace cat {

#define FOR_EACH_ELEMENT(index) for (int index = 0; index < ELEMENTS; ++index)


/*
	4x4 matrix elements arranged column major (row, column):

		m[0]  m[4]  m[8]  m[12]
		m[1]  m[5]  m[9]  m[13]
		m[2]  m[6]  m[10] m[14]
		m[3]  m[7]  m[11] m[15]

	Matrix element order corresponds to OpenGL matrix ordering s.t. in a
	4x4 matrix the elements define the following new coordinate system:

		new x-axis vector: { m[0]  m[1]  m[2]  }
		new y-axis vector: { m[4]  m[5]  m[6]  }
		new z-axis vector: { m[7]  m[9]  m[10] }
		new origin:        { m[12] m[13] m[14] }
*/

template<int ROWS, int COLS, class Scalar> class Matrix
{
protected:
	static const int ELEMENTS = ROWS * COLS;
	Scalar _elements[ROWS * COLS];

public:
	// Short-hand for the current matrix type
	typedef Matrix<ROWS, COLS, Scalar> mytype;

	// Default constructor does not initialize elements
	Matrix()
	{
	}

	// Copy constructor
	Matrix(const mytype &u)
	{
		memcpy(_elements, u._elements, sizeof(_elements));
	}

	// Assignment operator
	mytype &operator=(const mytype &u)
	{
		memcpy(_elements, u._elements, sizeof(_elements));
	}

	// Load zero matrix
	void loadZero()
	{
		OBJCLR(_elements);
	}

	// Load identity matrix
	void loadIdentity()
	{
		OBJCLR(_elements);

		// Write a 1 along the diagonal
		for (int ii = 0; ii < ROWS && ii < COLS; ++ii)
		{
			_elements[ii * ROWS + ii] = static_cast<Scalar>( 1 );
		}
	}

	// Addition in-place
	mytype &operator+=(const mytype &u)
	{
		FOR_EACH_ELEMENT(ii) _elements[ii] += u._elements[ii];
	}

	// Subtraction in-place
	mytype &operator-=(const mytype &u)
	{
		FOR_EACH_ELEMENT(ii) _elements[ii] -= u._elements[ii];
	}

	// Multiplication by scalar in-place
	mytype &operator*=(Scalar u)
	{
		FOR_EACH_ELEMENT(ii) _elements[ii] *= u;
	}

	// Division by scalar in-place
	mytype &operator/=(Scalar u)
	{
		FOR_EACH_ELEMENT(ii) _elements[ii] /= u;
	}

	// Matrix multiplication
	template<int OTHER_COLS>
	Matrix<ROWS, OTHER_COLS, Scalar> operator*(const Matrix<COLS, OTHER_COLS, Scalar> &u)
	{
		Matrix<ROWS, OTHER_COLS, Scalar> result;

		// For each row of the matrix product,
		for (int r = 0; r < ROWS; ++r)
		{
			// For each column of the matrix product,
			for (int c = 0; c < OTHER_COLS; ++c)
			{
				Scalar x = static_cast<Scalar>( 0 );

				// For each row of the right operand (u),
				for (int ii = 0; ii < COLS; ++ii)
				{
					// Accumulate sum of products
					x += (*this)(r, ii) * u(ii, c);
				}

				// Write the sum
				result(r, c) = x;
			}
		}

		return result;
	}

	// Accessors
    inline Scalar &operator()(int ii) { return _elements[ii]; }
    inline const Scalar &operator()(int ii) const { return _elements[ii]; }

    inline Scalar &operator()(int row, int col) { return _elements[col * ROWS + row]; }
    inline const Scalar &operator()(int row, int col) const { return _elements[col * ROWS + row]; }
};


// Short-hand for common usages:

typedef Matrix<2, 2, u32> Matrix2x2u;
typedef Matrix<3, 3, u32> Matrix3x3u;
typedef Matrix<4, 4, u32> Matrix4x4u;

typedef Matrix<2, 2, s32> Matrix2x2i;
typedef Matrix<3, 3, s32> Matrix3x3i;
typedef Matrix<4, 4, s32> Matrix4x4i;

typedef Matrix<2, 2, f32> Matrix2x2f;
typedef Matrix<3, 3, f32> Matrix3x3f;
typedef Matrix<4, 4, f32> Matrix4x4f;

typedef Matrix<2, 2, f64> Matrix2x2d;
typedef Matrix<3, 3, f64> Matrix3x3d;
typedef Matrix<4, 4, f64> Matrix4x4d;


#undef FOR_EACH_ELEMENT

} // namespace cat

#endif // CAT_MATRIX_HPP
