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

#include <ode/common.h>
#include <ode/matrix.h>
#include "config.h"
#include "util.h"

// misc defines
#define ALLOCA dALLOCA16



void _dSetZero (dReal *a, int n)
{
  dAASSERT (a && n >= 0);
  dReal *acurr = a;
  int ncurr = n;
  while (ncurr > 0) {
    *(acurr++) = 0;
    --ncurr;
  }
}


void _dSetValue (dReal *a, int n, dReal value)
{
  dAASSERT (a && n >= 0);
  dReal *acurr = a;
  int ncurr = n;
  while (ncurr > 0) {
    *(acurr++) = value;
    --ncurr;
  }
}


void _dMultiply0 (dReal *A, const dReal *B, const dReal *C, int p, int q, int r)
{
  dAASSERT (A && B && C && p>0 && q>0 && r>0);
  const int qskip = dPAD(q);
  const int rskip = dPAD(r);
  dReal *aa = A;
  const dReal *bb = B;
  for (int i=p; i; aa+=rskip, bb+=qskip, --i) {
    dReal *a = aa;
    const dReal *cc = C, *ccend = C + r;
    for (; cc != ccend; ++a, ++cc) {
      dReal sum = REAL(0.0);
      const dReal *c = cc;
      const dReal *b = bb, *bend = bb + q;
      for (; b != bend; c+=rskip, ++b) {
        sum += (*b)*(*c);
      }
      (*a) = sum; 
    }
  }
}


void _dMultiply1 (dReal *A, const dReal *B, const dReal *C, int p, int q, int r)
{
  dAASSERT (A && B && C && p>0 && q>0 && r>0);
  const int pskip = dPAD(p);
  const int rskip = dPAD(r);
  dReal *aa = A;
  const dReal *bb = B, *bbend = B + p;
  for (; bb != bbend; aa += rskip, ++bb) {
    dReal *a = aa;
    const dReal *cc = C, *ccend = C + r;
    for (; cc != ccend; ++a, ++cc) {
      dReal sum = REAL(0.0);
      const dReal *b = bb, *c = cc;
      for (int k=q; k; b+=pskip, c+=rskip, --k) {
        sum += (*b)*(*c);
      }
      (*a) = sum;
    }
  }
}


void _dMultiply2 (dReal *A, const dReal *B, const dReal *C, int p, int q, int r)
{
  dAASSERT (A && B && C && p>0 && q>0 && r>0);
  const int rskip = dPAD(r);
  const int qskip = dPAD(q);
  dReal *aa = A;
  const dReal *bb = B;
  for (int i=p; i; aa+=rskip, bb+=qskip, --i) {
    dReal *a = aa, *aend = aa + r;
    const dReal *cc = C;
    for (; a != aend; cc+=qskip, ++a) {
      dReal sum = REAL(0.0);
      const dReal *b = bb, *c = cc, *cend = cc + q;
      for (; c != cend; ++b, ++c) {
        sum += (*b)*(*c);
      }
      (*a) = sum; 
    }
  }
}


int _dFactorCholesky (dReal *A, int n, void *tmpbuf/*[n]*/)
{
  dAASSERT (n > 0 && A);
  bool failure = false;
  const int nskip = dPAD (n);
  dReal *recip = tmpbuf ? (dReal *)tmpbuf : (dReal*) ALLOCA (n * sizeof(dReal));
  dReal *aa = A;
  for (int i=0; i<n; aa+=nskip, ++i) {
    dReal *cc = aa;
    {
      const dReal *bb = A;
      for (int j=0; j<i; bb+=nskip, ++cc, ++j) {
        dReal sum = *cc;
        const dReal *a = aa, *b = bb, *bend = bb + j;
        for (; b != bend; ++a, ++b) {
          sum -= (*a)*(*b);
        }
        *cc = sum * recip[j];
      }
    }
    {
      dReal sum = *cc;
      dReal *a = aa, *aend = aa + i;
      for (; a != aend; ++a) {
        sum -= (*a)*(*a);
      }
      if (sum <= REAL(0.0)) {
        failure = true;
        break;
      }
      dReal sumsqrt = dSqrt(sum);
      *cc = sumsqrt;
      recip[i] = dRecip (sumsqrt);
    }
  }
  return failure ? 0 : 1;
}


void _dSolveCholesky (const dReal *L, dReal *b, int n, void *tmpbuf/*[n]*/)
{
  dAASSERT (n > 0 && L && b);
  const int nskip = dPAD (n);
  dReal *y = tmpbuf ? (dReal *)tmpbuf : (dReal*) ALLOCA (n*sizeof(dReal));
  {
    const dReal *ll = L;
    for (int i=0; i<n; ll+=nskip, ++i) {
      dReal sum = REAL(0.0);
      for (int k=0; k < i; ++k) {
        sum += ll[k]*y[k];
      }
      dIASSERT(ll[i] != dReal(0.0));
      y[i] = (b[i]-sum)/ll[i];
    }
  }
  {
    const dReal *ll = L + (n - 1) * (nskip + 1);
    for (int i=n-1; i>=0; ll-=nskip+1, --i) {
      dReal sum = REAL(0.0);
      const dReal *l = ll + nskip;
      for (int k=i+1; k<n; l+=nskip, ++k) {
        sum += (*l)*b[k];
      }
      dIASSERT(*ll != dReal(0.0));
      b[i] = (y[i]-sum)/(*ll);
    }
  }
}


int _dInvertPDMatrix (const dReal *A, dReal *Ainv, int n, void *tmpbuf/*[nskip*(n+2)]*/)
{
  dAASSERT (n > 0 && A && Ainv);
  bool success = false;
  size_t FactorCholesky_size = _dEstimateFactorCholeskyTmpbufSize(n);
  size_t SolveCholesky_size = _dEstimateSolveCholeskyTmpbufSize(n);
  size_t MaxCholesky_size = FactorCholesky_size > SolveCholesky_size ? FactorCholesky_size : SolveCholesky_size;
  dIASSERT(MaxCholesky_size % sizeof(dReal) == 0);
  const int nskip = dPAD (n);
  const int nskip_mul_n = nskip*n;
  dReal *tmp = tmpbuf ? (dReal *)tmpbuf : (dReal*) ALLOCA (MaxCholesky_size + (nskip + nskip_mul_n)*sizeof(dReal));
  dReal *X = (dReal *)((char *)tmp + MaxCholesky_size);
  dReal *L = X + nskip;
  memcpy (L, A, nskip_mul_n*sizeof(dReal));
  if (dFactorCholesky (L,n,tmp)) {
    dSetZero (Ainv,nskip_mul_n);	// make sure all padding elements set to 0
    dReal *aa = Ainv, *xi = X, *xiend = X + n;
    for (; xi != xiend; ++aa, ++xi) {
      dSetZero(X, n);
      *xi = REAL(1.0);
      dSolveCholesky (L,X,n,tmp);
      dReal *a = aa;
      const dReal *x = X, *xend = X + n;
      for (; x!=xend; a+=nskip, ++x) {
        *a = *x;
      }
    }
    success = true;
  }
  return success ? 1 : 0;  
}


int _dIsPositiveDefinite (const dReal *A, int n, void *tmpbuf/*[nskip*(n+1)]*/)
{
  dAASSERT (n > 0 && A);
  size_t FactorCholesky_size = _dEstimateFactorCholeskyTmpbufSize(n);
  dIASSERT(FactorCholesky_size % sizeof(dReal) == 0);
  const int nskip = dPAD (n);
  const int nskip_mul_n = nskip*n;
  dReal *tmp = tmpbuf ? (dReal *)tmpbuf : (dReal*) ALLOCA (FactorCholesky_size + nskip_mul_n*sizeof(dReal));
  dReal *Acopy = (dReal *)((char *)tmp + FactorCholesky_size);
  memcpy (Acopy, A, nskip_mul_n * sizeof(dReal));
  return dFactorCholesky (Acopy, n, tmp);
}



void _dVectorScale (dReal *a, const dReal *d, int n)
{
  dAASSERT (a && d && n >= 0);
  for (int i=0; i<n; i++) {
    a[i] *= d[i];
  }
}


void _dSolveLDLT (const dReal *L, const dReal *d, dReal *b, int n, int nskip)
{
  dAASSERT (L && d && b && n > 0 && nskip >= n);
  dSolveL1 (L,b,n,nskip);
  dVectorScale (b,d,n);
  dSolveL1T (L,b,n,nskip);
}


void _dLDLTAddTL (dReal *L, dReal *d, const dReal *a, int n, int nskip, void *tmpbuf/*[2*nskip]*/)
{
  dAASSERT (L && d && a && n > 0 && nskip >= n);

  if (n < 2) return;
  dReal *W1 = tmpbuf ? (dReal *)tmpbuf : (dReal*) ALLOCA ((2*nskip)*sizeof(dReal));
  dReal *W2 = W1 + nskip;

  W1[0] = REAL(0.0);
  W2[0] = REAL(0.0);
  for (int j=1; j<n; ++j) {
    W1[j] = W2[j] = (dReal) (a[j] * M_SQRT1_2);
  }
  dReal W11 = (dReal) ((REAL(0.5)*a[0]+1)*M_SQRT1_2);
  dReal W21 = (dReal) ((REAL(0.5)*a[0]-1)*M_SQRT1_2);

  dReal alpha1 = REAL(1.0);
  dReal alpha2 = REAL(1.0);

  {
    dReal dee = d[0];
    dReal alphanew = alpha1 + (W11*W11)*dee;
    dIASSERT(alphanew != dReal(0.0));
    dee /= alphanew;
    dReal gamma1 = W11 * dee;
    dee *= alpha1;
    alpha1 = alphanew;
    alphanew = alpha2 - (W21*W21)*dee;
    dee /= alphanew;
    //dReal gamma2 = W21 * dee;
    alpha2 = alphanew;
    dReal k1 = REAL(1.0) - W21*gamma1;
    dReal k2 = W21*gamma1*W11 - W21;
    dReal *ll = L + nskip;
    for (int p=1; p<n; ll+=nskip, ++p) {
      dReal Wp = W1[p];
      dReal ell = *ll;
      W1[p] =    Wp - W11*ell;
      W2[p] = k1*Wp +  k2*ell;
    }
  }

  dReal *ll = L + (nskip + 1);
  for (int j=1; j<n; ll+=nskip+1, ++j) {
    dReal k1 = W1[j];
    dReal k2 = W2[j];

    dReal dee = d[j];
    dReal alphanew = alpha1 + (k1*k1)*dee;
    dIASSERT(alphanew != dReal(0.0));
    dee /= alphanew;
    dReal gamma1 = k1 * dee;
    dee *= alpha1;
    alpha1 = alphanew;
    alphanew = alpha2 - (k2*k2)*dee;
    dee /= alphanew;
    dReal gamma2 = k2 * dee;
    dee *= alpha2;
    d[j] = dee;
    alpha2 = alphanew;

    dReal *l = ll + nskip;
    for (int p=j+1; p<n; l+=nskip, ++p) {
      dReal ell = *l;
      dReal Wp = W1[p] - k1 * ell;
      ell += gamma1 * Wp;
      W1[p] = Wp;
      Wp = W2[p] - k2 * ell;
      ell -= gamma2 * Wp;
      W2[p] = Wp;
      *l = ell;
    }
  }
}


// macros for dLDLTRemove() for accessing A - either access the matrix
// directly or access it via row pointers. we are only supposed to reference
// the lower triangle of A (it is symmetric), but indexes i and j come from
// permutation vectors so they are not predictable. so do a test on the
// indexes - this should not slow things down too much, as we don't do this
// in an inner loop.

#define _GETA(i,j) (A[i][j])
//#define _GETA(i,j) (A[(i)*nskip+(j)])
#define GETA(i,j) ((i > j) ? _GETA(i,j) : _GETA(j,i))


void _dLDLTRemove (dReal **A, const int *p, dReal *L, dReal *d,
    int n1, int n2, int r, int nskip, void *tmpbuf/*n2 + 2*nskip*/)
{
  dAASSERT(A && p && L && d && n1 > 0 && n2 > 0 && r >= 0 && r < n2 &&
	   n1 >= n2 && nskip >= n1);
  #ifndef dNODEBUG
  for (int i=0; i<n2; ++i) dIASSERT(p[i] >= 0 && p[i] < n1);
  #endif

  if (r==n2-1) {
    return;		// deleting last row/col is easy
  }
  else {
    size_t LDLTAddTL_size = _dEstimateLDLTAddTLTmpbufSize(nskip);
    dIASSERT(LDLTAddTL_size % sizeof(dReal) == 0);
    dReal *tmp = tmpbuf ? (dReal *)tmpbuf : (dReal*) ALLOCA (LDLTAddTL_size + n2 * sizeof(dReal));
    if (r==0) {
      dReal *a = (dReal *)((char *)tmp + LDLTAddTL_size);
      const int p_0 = p[0];
      for (int i=0; i<n2; ++i) {
        a[i] = -GETA(p[i],p_0);
      }
      a[0] += REAL(1.0);
      dLDLTAddTL (L,d,a,n2,nskip,tmp);
    }
    else {
      dReal *t = (dReal *)((char *)tmp + LDLTAddTL_size);
      {
        dReal *Lcurr = L + r*nskip;
        for (int i=0; i<r; ++Lcurr, ++i) {
          dIASSERT(d[i] != dReal(0.0));
          t[i] = *Lcurr / d[i];
        }
      }
      dReal *a = t + r;
      {
        dReal *Lcurr = L + r*nskip;
        const int *pp_r = p + r, p_r = *pp_r;
        const int n2_minus_r = n2-r;
        for (int i=0; i<n2_minus_r; Lcurr+=nskip,++i) {
          a[i] = dDot(Lcurr,t,r) - GETA(pp_r[i],p_r);
        }
      }
      a[0] += REAL(1.0);
      dLDLTAddTL (L + r*nskip+r, d+r, a, n2-r, nskip, tmp);
    }
  }

  // snip out row/column r from L and d
  dRemoveRowCol (L,n2,nskip,r);
  if (r < (n2-1)) memmove (d+r,d+r+1,(n2-r-1)*sizeof(dReal));
}


void _dRemoveRowCol (dReal *A, int n, int nskip, int r)
{
  dAASSERT(A && n > 0 && nskip >= n && r >= 0 && r < n);
  if (r >= n-1) return;
  if (r > 0) {
    {
      const size_t move_size = (n-r-1)*sizeof(dReal);
      dReal *Adst = A + r;
      for (int i=0; i<r; Adst+=nskip,++i) {
        dReal *Asrc = Adst + 1;
        memmove (Adst,Asrc,move_size);
      }
    }
    {
      const size_t cpy_size = r*sizeof(dReal);
      dReal *Adst = A + r * nskip;
      for (int i=r; i<(n-1); ++i) {
        dReal *Asrc = Adst + nskip;
        memcpy (Adst,Asrc,cpy_size);
        Adst = Asrc;
      }
    }
  }
  {
    const size_t cpy_size = (n-r-1)*sizeof(dReal);
    dReal *Adst = A + r * (nskip + 1);
    for (int i=r; i<(n-1); ++i) {
      dReal *Asrc = Adst + (nskip + 1);
      memcpy (Adst,Asrc,cpy_size);
      Adst = Asrc - 1;
    }
  }
}


#undef dSetZero
#undef dSetValue
//#undef dDot
#undef dMultiply0
#undef dMultiply1
#undef dMultiply2
#undef dFactorCholesky
#undef dSolveCholesky
#undef dInvertPDMatrix
#undef dIsPositiveDefinite
//#undef dFactorLDLT
//#undef dSolveL1
//#undef dSolveL1T
#undef dVectorScale
#undef dSolveLDLT
#undef dLDLTAddTL
#undef dLDLTRemove
#undef dRemoveRowCol


void dSetZero (dReal *a, int n)
{
  _dSetZero (a, n);
}

void dSetValue (dReal *a, int n, dReal value)
{
  _dSetValue (a, n, value);
}

// dReal dDot (const dReal *a, const dReal *b, int n);

void dMultiply0 (dReal *A, const dReal *B, const dReal *C, int p,int q,int r)
{
  _dMultiply0 (A, B, C, p, q, r);
}

void dMultiply1 (dReal *A, const dReal *B, const dReal *C, int p,int q,int r)
{
  _dMultiply1 (A, B, C, p, q, r);
}

void dMultiply2 (dReal *A, const dReal *B, const dReal *C, int p,int q,int r)
{
  _dMultiply2 (A, B, C, p, q, r);
}

int dFactorCholesky (dReal *A, int n)
{
  return _dFactorCholesky (A, n, NULL);
}

void dSolveCholesky (const dReal *L, dReal *b, int n)
{
  _dSolveCholesky (L, b, n, NULL);
}

int dInvertPDMatrix (const dReal *A, dReal *Ainv, int n)
{
  return _dInvertPDMatrix (A, Ainv, n, NULL);
}

int dIsPositiveDefinite (const dReal *A, int n)
{
  return _dIsPositiveDefinite (A, n, NULL);
}

// void dFactorLDLT (dReal *A, dReal *d, int n, int nskip);
// void dSolveL1 (const dReal *L, dReal *b, int n, int nskip);
// void dSolveL1T (const dReal *L, dReal *b, int n, int nskip);

void dVectorScale (dReal *a, const dReal *d, int n)
{
  _dVectorScale (a, d, n);
}

void dSolveLDLT (const dReal *L, const dReal *d, dReal *b, int n, int nskip)
{
  _dSolveLDLT (L, d, b, n, nskip);
}

void dLDLTAddTL (dReal *L, dReal *d, const dReal *a, int n, int nskip)
{
  _dLDLTAddTL (L, d, a, n, nskip, NULL);
}

void dLDLTRemove (dReal **A, const int *p, dReal *L, dReal *d, int n1, int n2, int r, int nskip)
{
  _dLDLTRemove (A, p, L, d, n1, n2, r, nskip, NULL);
}

void dRemoveRowCol (dReal *A, int n, int nskip, int r)
{
  _dRemoveRowCol (A, n, nskip, r);
}

