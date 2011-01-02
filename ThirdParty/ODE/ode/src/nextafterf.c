/* _nextafterf() implementation for MSVC */

#include <ode/common.h>

#if defined(_ODE__NEXTAFTERF_REQUIRED)

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

/* A union which permits us to convert between a float and a 32 bit
   int.  */

typedef union
{
  float value;
  uint32 word;
} ieee_float_shape_type;

/* Get a 32 bit int from a float.  */

#define GET_FLOAT_WORD(i,d)					\
do {								\
  volatile ieee_float_shape_type gf_u;					\
  gf_u.value = (d);						\
  (i) = gf_u.word;						\
} while (0)

/* Set a float from a 32 bit int.  */

#define SET_FLOAT_WORD(d,i)					\
do {								\
  volatile ieee_float_shape_type sf_u;					\
  sf_u.word = (i);						\
  (d) = sf_u.value;						\
} while (0)


#undef nextafterf
float _nextafterf(float x, float y)
{
	int32 hx,hy,ix,iy;

	GET_FLOAT_WORD(hx,x);
	GET_FLOAT_WORD(hy,y);
	ix = hx&0x7fffffff;		/* |x| */
	iy = hy&0x7fffffff;		/* |y| */

	if((ix>0x7f800000) ||   /* x is nan */ 
	   (iy>0x7f800000))     /* y is nan */ 
	   return x+y;				
	if(x==y) return x;		/* x=y, return x */
	if(ix==0) {				/* x == 0 */
	    SET_FLOAT_WORD(x,(hy&0x80000000)|1);/* return +-minsubnormal */
	    y = x*x;
	    if(y==x) return y; else return x;	/* raise underflow flag */
	} 
	if(hx>=0) {				/* x > 0 */
	    if(hx>hy) {				/* x > y, x -= ulp */
		hx -= 1;
	    } else {				/* x < y, x += ulp */
		hx += 1;
	    }
	} else {				/* x < 0 */
	    if(hy>=0||hx>hy){			/* x < y, x -= ulp */
		hx -= 1;
	    } else {				/* x > y, x += ulp */
		hx += 1;
	    }
	}
	hy = hx&0x7f800000;
	if(hy>=0x7f800000) return x+x;	/* overflow  */
	if(hy<0x00800000) {		/* underflow */
	    y = x*x;
	    if(y!=x) {		/* raise underflow flag */
	        SET_FLOAT_WORD(y,hx);
		return y;
	    }
	}
	SET_FLOAT_WORD(x,hx);
	return x;
}


#endif // #if defined(_ODE__NEXTAFTERF_REQUIRED)
