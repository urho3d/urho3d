///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains FPU related code.
 *	\file		IceFPU.h
 *	\author		Pierre Terdiman
 *	\date		April, 4, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef __ICEFPU_H__
#define __ICEFPU_H__

	#define	SIGN_BITMASK			0x80000000

	namespace {
		union float_udword { float f; udword u; };
		union float_sdword { float f; sdword s; };
	}


	//! Integer representation of a floating-point value.
	//#define IR(x)					((udword&)(x))
	static inline udword IR(float x) { float_udword fu; fu.f = x; return fu.u; }

	//! Signed integer representation of a floating-point value.
	//#define SIR(x)					((sdword&)(x))
	static inline sdword SIR(float x) { float_sdword fs; fs.f = x; return fs.s; }

	//! Absolute integer representation of a floating-point value
	#define AIR(x)					(IR(x)&0x7fffffff)

	//! Floating-point representation of an integer value.
	//#define FR(x)					((float&)(x))
	static inline float FR(unsigned x) { float_udword fu; fu.u = x; return fu.f; }

	//! Integer-based comparison of a floating point value.
	//! Don't use it blindly, it can be faster or slower than the FPU comparison, depends on the context.
	#define IS_NEGATIVE_FLOAT(x)	(IR(x)&0x80000000)

	//! Fast fabs for floating-point values. It just clears the sign bit.
	//! Don't use it blindy, it can be faster or slower than the FPU comparison, depends on the context.
	inline_ float FastFabs(float x)
	{
		udword FloatBits = IR(x)&0x7fffffff;
		return FR(FloatBits);
	}

	//! Fast square root for floating-point values.
	inline_ float FastSqrt(float square)
	{
		return sqrt(square);
	}

	//! Saturates positive to zero.
	inline_ float fsat(float f)
	{
		udword y = IR(f) & ~(SIR(f) >>31);
		return FR(y);
	}

	//! Computes 1.0f / sqrtf(x).
	inline_ float frsqrt(float f)
	{
		float x = f * 0.5f;
		udword y = 0x5f3759df - (IR(f) >> 1);
		// Iteration...
		const float fy = FR(y);
		const float result = fy * ( 1.5f - ( x * fy * fy ) );
		// Result
		return result;
	}

	//! Computes 1.0f / sqrtf(x). Comes from NVIDIA.
	inline_ float InvSqrt(const float& x)
	{
		const udword tmp = (udword(IEEE_1_0 << 1) + IEEE_1_0 - IR(x)) >> 1;      
		const float y = FR(tmp);
		return y * (1.47f - 0.47f * x * y * y);
	}

	//! Computes 1.0f / sqrtf(x). Comes from Quake3. Looks like the first one I had above.
	//! See http://www.magic-software.com/3DGEDInvSqrt.html
	inline_ float RSqrt(float number)
	{
		int i;
		float x2, y;
		const float threehalfs = 1.5f;

		x2 = number * 0.5f;
		y  = number;
		i  = IR(y);
		i  = 0x5f3759df - (i >> 1);
		y  = FR(i);
		y  = y * (threehalfs - (x2 * y * y));

		return y;
	}

	//! TO BE DOCUMENTED
	inline_ float fsqrt(float f)
	{
		udword y = ( ( SIR(f) - 0x3f800000 ) >> 1 ) + 0x3f800000;
		// Iteration...?
		// (float&)y = (3.0f - ((float&)y * (float&)y) / f) * (float&)y * 0.5f;
		// Result
		return FR(y);
	}

	//! Returns the float ranged espilon value.
	inline_ float fepsilon(float f)
	{
		udword b = IR(f) & 0xff800000;
		udword a = b | 0x00000001;
		// Result
		return FR(a) - FR(b);
	}

	//! Is the float valid ?
	inline_ bool IsNAN(float value)				{ return (IR(value)&0x7f800000) == 0x7f800000;	}
	inline_ bool IsIndeterminate(float value)	{ return IR(value) == 0xffc00000;				}
	inline_ bool IsPlusInf(float value)			{ return IR(value) == 0x7f800000;				}
	inline_ bool IsMinusInf(float value)		{ return IR(value) == 0xff800000;				}

	inline_	bool IsValidFloat(float value)
	{
		if(IsNAN(value))			return false;
		if(IsIndeterminate(value))	return false;
		if(IsPlusInf(value))		return false;
		if(IsMinusInf(value))		return false;
		return true;
	}

	#define CHECK_VALID_FLOAT(x)	ASSERT(IsValidFloat(x));

/*
	//! FPU precision setting function.
	inline_ void SetFPU()
	{
		// This function evaluates whether the floating-point
		// control word is set to single precision/round to nearest/
		// exceptions disabled. If these conditions don't hold, the
		// function changes the control word to set them and returns
		// TRUE, putting the old control word value in the passback
		// location pointed to by pwOldCW.
		{
			uword wTemp, wSave;
 
			__asm fstcw wSave
			if (wSave & 0x300 ||            // Not single mode
				0x3f != (wSave & 0x3f) ||   // Exceptions enabled
				wSave & 0xC00)              // Not round to nearest mode
			{
				__asm
				{
					mov ax, wSave
					and ax, not 300h    ;; single mode
					or  ax, 3fh         ;; disable all exceptions
					and ax, not 0xC00   ;; round to nearest mode
					mov wTemp, ax
					fldcw   wTemp
				}
			}
		}
	}
*/
	//! This function computes the slowest possible floating-point value (you can also directly use FLT_EPSILON)
	inline_ float ComputeFloatEpsilon()
	{
		const float f = FR( IR(1.0f) ^ 1 );
		return f - 1.0f;	// You can check it's the same as FLT_EPSILON
	}

	inline_ bool IsFloatZero(float x, float epsilon=1e-6f)
	{
		return x*x < epsilon;
	}

	#define FCOMI_ST0	_asm	_emit	0xdb	_asm	_emit	0xf0
	#define FCOMIP_ST0	_asm	_emit	0xdf	_asm	_emit	0xf0
	#define FCMOVB_ST0	_asm	_emit	0xda	_asm	_emit	0xc0
	#define FCMOVNB_ST0	_asm	_emit	0xdb	_asm	_emit	0xc0

	#define FCOMI_ST1	_asm	_emit	0xdb	_asm	_emit	0xf1
	#define FCOMIP_ST1	_asm	_emit	0xdf	_asm	_emit	0xf1
	#define FCMOVB_ST1	_asm	_emit	0xda	_asm	_emit	0xc1
	#define FCMOVNB_ST1	_asm	_emit	0xdb	_asm	_emit	0xc1

	#define FCOMI_ST2	_asm	_emit	0xdb	_asm	_emit	0xf2
	#define FCOMIP_ST2	_asm	_emit	0xdf	_asm	_emit	0xf2
	#define FCMOVB_ST2	_asm	_emit	0xda	_asm	_emit	0xc2
	#define FCMOVNB_ST2	_asm	_emit	0xdb	_asm	_emit	0xc2

	#define FCOMI_ST3	_asm	_emit	0xdb	_asm	_emit	0xf3
	#define FCOMIP_ST3	_asm	_emit	0xdf	_asm	_emit	0xf3
	#define FCMOVB_ST3	_asm	_emit	0xda	_asm	_emit	0xc3
	#define FCMOVNB_ST3	_asm	_emit	0xdb	_asm	_emit	0xc3

	#define FCOMI_ST4	_asm	_emit	0xdb	_asm	_emit	0xf4
	#define FCOMIP_ST4	_asm	_emit	0xdf	_asm	_emit	0xf4
	#define FCMOVB_ST4	_asm	_emit	0xda	_asm	_emit	0xc4
	#define FCMOVNB_ST4	_asm	_emit	0xdb	_asm	_emit	0xc4

	#define FCOMI_ST5	_asm	_emit	0xdb	_asm	_emit	0xf5
	#define FCOMIP_ST5	_asm	_emit	0xdf	_asm	_emit	0xf5
	#define FCMOVB_ST5	_asm	_emit	0xda	_asm	_emit	0xc5
	#define FCMOVNB_ST5	_asm	_emit	0xdb	_asm	_emit	0xc5

	#define FCOMI_ST6	_asm	_emit	0xdb	_asm	_emit	0xf6
	#define FCOMIP_ST6	_asm	_emit	0xdf	_asm	_emit	0xf6
	#define FCMOVB_ST6	_asm	_emit	0xda	_asm	_emit	0xc6
	#define FCMOVNB_ST6	_asm	_emit	0xdb	_asm	_emit	0xc6

	#define FCOMI_ST7	_asm	_emit	0xdb	_asm	_emit	0xf7
	#define FCOMIP_ST7	_asm	_emit	0xdf	_asm	_emit	0xf7
	#define FCMOVB_ST7	_asm	_emit	0xda	_asm	_emit	0xc7
	#define FCMOVNB_ST7	_asm	_emit	0xdb	_asm	_emit	0xc7

	//! A global function to find MAX(a,b) using FCOMI/FCMOV
	inline_ float FCMax2(float a, float b)
	{
		return (a > b) ? a : b;
	}

	//! A global function to find MIN(a,b) using FCOMI/FCMOV
	inline_ float FCMin2(float a, float b)
	{
		return (a < b) ? a : b;
	}

	//! A global function to find MAX(a,b,c) using FCOMI/FCMOV
	inline_ float FCMax3(float a, float b, float c)
	{
		return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
	}

	//! A global function to find MIN(a,b,c) using FCOMI/FCMOV
	inline_ float FCMin3(float a, float b, float c)
	{
		return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
	}

	inline_ int ConvertToSortable(float f)
	{
		int Fi = SIR(f);
		int Fmask = (Fi>>31);
		Fi ^= Fmask;
		Fmask &= ~(1<<31);
		Fi -= Fmask;
		return Fi;
	}

	enum FPUMode
	{
		FPU_FLOOR		= 0,
		FPU_CEIL		= 1,
		FPU_BEST		= 2,

		FPU_FORCE_DWORD	= 0x7fffffff
	};

	FUNCTION ICECORE_API FPUMode	GetFPUMode();
	FUNCTION ICECORE_API void		SaveFPU();
	FUNCTION ICECORE_API void		RestoreFPU();
	FUNCTION ICECORE_API void		SetFPUFloorMode();
	FUNCTION ICECORE_API void		SetFPUCeilMode();
	FUNCTION ICECORE_API void		SetFPUBestMode();

	FUNCTION ICECORE_API void		SetFPUPrecision24();
	FUNCTION ICECORE_API void		SetFPUPrecision53();
	FUNCTION ICECORE_API void		SetFPUPrecision64();
	FUNCTION ICECORE_API void		SetFPURoundingChop();
	FUNCTION ICECORE_API void		SetFPURoundingUp();
	FUNCTION ICECORE_API void		SetFPURoundingDown();
	FUNCTION ICECORE_API void		SetFPURoundingNear();

	FUNCTION ICECORE_API int		intChop(const float& f);
	FUNCTION ICECORE_API int		intFloor(const float& f);
	FUNCTION ICECORE_API int		intCeil(const float& f);

#endif // __ICEFPU_H__
