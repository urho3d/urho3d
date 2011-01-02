/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001,2002 Russell L. Smith.       *
 * All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 2.1 of the License, or (at  *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file LICENSE.TXT.                                               *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file LICENSE-BSD.TXT.                                       *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
 *                                                                       *
 *************************************************************************/

#include <ode/odeconfig.h>
#include <ode/misc.h>
#include <ode/matrix.h>
#include "config.h"

//****************************************************************************
// random numbers

static unsigned long seed = 0;

unsigned long dRand()
{
  seed = (1664525UL*seed + 1013904223UL) & 0xffffffff;
  return seed;
}


unsigned long  dRandGetSeed()
{
  return seed;
}


void dRandSetSeed (unsigned long s)
{
  seed = s;
}


int dTestRand()
{
  unsigned long oldseed = seed;
  int ret = 1;
  seed = 0;
  if (dRand() != 0x3c6ef35f || dRand() != 0x47502932 ||
      dRand() != 0xd1ccf6e9 || dRand() != 0xaaf95334 ||
      dRand() != 0x6252e503) ret = 0;
  seed = oldseed;
  return ret;
}


// adam's all-int straightforward(?) dRandInt (0..n-1)
int dRandInt (int n)
{
  // seems good; xor-fold and modulus
  const unsigned long un = n;
  // Since there is no memory barrier macro in ODE assign via volatile variable 
  // to prevent compiler reusing seed as value of `r'
  volatile unsigned long raw_r = dRand();
  unsigned long r = raw_r;
  
  // note: probably more aggressive than it needs to be -- might be
  //       able to get away without one or two of the innermost branches.
  // if (un <= 0x00010000UL) {
  //   r ^= (r >> 16);
  //   if (un <= 0x00000100UL) {
  //     r ^= (r >> 8);
  //     if (un <= 0x00000010UL) {
  //       r ^= (r >> 4);
  //       if (un <= 0x00000004UL) {
  //         r ^= (r >> 2);
  //         if (un <= 0x00000002UL) {
  //           r ^= (r >> 1);
  //         }
  //       }
  //     }
  //   }
  // }
  // Optimized version of above
  if (un <= 0x00000010UL) {
    r ^= (r >> 16);
    r ^= (r >> 8);
    r ^= (r >> 4);
    if (un <= 0x00000002UL) {
      r ^= (r >> 2);
      r ^= (r >> 1);
    } else {
      if (un <= 0x00000004UL) {
        r ^= (r >> 2);
      }
    }
  } else {
    if (un <= 0x00000100UL) {
      r ^= (r >> 16);
      r ^= (r >> 8);
    } else {
      if (un <= 0x00010000UL) {
        r ^= (r >> 16);
      }
    }
  }

  return (int) (r % un);    
}


dReal dRandReal()
{
  return ((dReal) dRand()) / ((dReal) 0xffffffff);
}

//****************************************************************************
// matrix utility stuff

void dPrintMatrix (const dReal *A, int n, int m, char *fmt, FILE *f)
{
  int skip = dPAD(m);
  const dReal *Arow = A;
  for (int i=0; i<n; Arow+=skip, ++i) {
    for (int j=0; j<m; ++j) fprintf (f,fmt,Arow[j]);
    fprintf (f,"\n");
  }
}


void dMakeRandomVector (dReal *A, int n, dReal range)
{
  int i;
  for (i=0; i<n; i++) A[i] = (dRandReal()*REAL(2.0)-REAL(1.0))*range;
}


void dMakeRandomMatrix (dReal *A, int n, int m, dReal range)
{
  int skip = dPAD(m);
//  dSetZero (A,n*skip);
  dReal *Arow = A;
  for (int i=0; i<n; Arow+=skip, ++i) {
    for (int j=0; j<m; ++j) Arow[j] = (dRandReal()*REAL(2.0)-REAL(1.0))*range;
  }
}


void dClearUpperTriangle (dReal *A, int n)
{
  int skip = dPAD(n);
  dReal *Arow = A;
  for (int i=0; i<n; Arow+=skip, ++i) {
    for (int j=i+1; j<n; ++j) Arow[j] = 0;
  }
}


dReal dMaxDifference (const dReal *A, const dReal *B, int n, int m)
{
  int skip = dPAD(m);
  dReal max = REAL(0.0);
  const dReal *Arow = A, *Brow = B;
  for (int i=0; i<n; Arow+=skip, Brow +=skip, ++i) {
    for (int j=0; j<m; ++j) {
      dReal diff = dFabs(Arow[j] - Brow[j]);
      if (diff > max) max = diff;
    }
  }
  return max;
}


dReal dMaxDifferenceLowerTriangle (const dReal *A, const dReal *B, int n)
{
  int skip = dPAD(n);
  dReal max = REAL(0.0);
  const dReal *Arow = A, *Brow = B;
  for (int i=0; i<n; Arow+=skip, Brow+=skip, ++i) {
    for (int j=0; j<=i; ++j) {
      dReal diff = dFabs(Arow[j] - Brow[j]);
      if (diff > max) max = diff;
    }
  }
  return max;
}

