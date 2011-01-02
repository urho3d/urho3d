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
#include <ode/mass.h>
#include <ode/odemath.h>
#include <ode/matrix.h>
#include "config.h"

// Local dependencies
#include "collision_kernel.h"

#if dTRIMESH_ENABLED
  #include "collision_trimesh_internal.h"
#endif // dTRIMESH_ENABLED

#define	SQR(x)			((x)*(x))						//!< Returns x square
#define	CUBE(x)			((x)*(x)*(x))					//!< Returns x cube

#define _I(i,j) I[(i)*4+(j)]


// return 1 if ok, 0 if bad

int dMassCheck (const dMass *m)
{
  int i;

  if (m->mass <= 0) {
    dDEBUGMSG ("mass must be > 0");
    return 0;
  }
  if (!dIsPositiveDefinite (m->I,3,NULL)) {
    dDEBUGMSG ("inertia must be positive definite");
    return 0;
  }

  // verify that the center of mass position is consistent with the mass
  // and inertia matrix. this is done by checking that the inertia around
  // the center of mass is also positive definite. from the comment in
  // dMassTranslate(), if the body is translated so that its center of mass
  // is at the point of reference, then the new inertia is:
  //   I + mass*crossmat(c)^2
  // note that requiring this to be positive definite is exactly equivalent
  // to requiring that the spatial inertia matrix
  //   [ mass*eye(3,3)   M*crossmat(c)^T ]
  //   [ M*crossmat(c)   I               ]
  // is positive definite, given that I is PD and mass>0. see the theorem
  // about partitioned PD matrices for proof.

  dMatrix3 I2,chat;
  dSetZero (chat,12);
  dSetCrossMatrixPlus (chat,m->c,4);
  dMultiply0_333 (I2,chat,chat);
  for (i=0; i<3; i++) I2[i] = m->I[i] + m->mass*I2[i];
  for (i=4; i<7; i++) I2[i] = m->I[i] + m->mass*I2[i];
  for (i=8; i<11; i++) I2[i] = m->I[i] + m->mass*I2[i];
  if (!dIsPositiveDefinite (I2,3,NULL)) {
    dDEBUGMSG ("center of mass inconsistent with mass parameters");
    return 0;
  }
  return 1;
}


void dMassSetZero (dMass *m)
{
  dAASSERT (m);
  m->mass = REAL(0.0);
  dSetZero (m->c,sizeof(m->c) / sizeof(dReal));
  dSetZero (m->I,sizeof(m->I) / sizeof(dReal));
}


void dMassSetParameters (dMass *m, dReal themass,
			 dReal cgx, dReal cgy, dReal cgz,
			 dReal I11, dReal I22, dReal I33,
			 dReal I12, dReal I13, dReal I23)
{
  dAASSERT (m);
  dMassSetZero (m);
  m->mass = themass;
  m->c[0] = cgx;
  m->c[1] = cgy;
  m->c[2] = cgz;
  m->_I(0,0) = I11;
  m->_I(1,1) = I22;
  m->_I(2,2) = I33;
  m->_I(0,1) = I12;
  m->_I(0,2) = I13;
  m->_I(1,2) = I23;
  m->_I(1,0) = I12;
  m->_I(2,0) = I13;
  m->_I(2,1) = I23;
  dMassCheck (m);
}


void dMassSetSphere (dMass *m, dReal density, dReal radius)
{
  dMassSetSphereTotal (m, (dReal) ((REAL(4.0)/REAL(3.0)) * M_PI *
			  radius*radius*radius * density), radius);
}


void dMassSetSphereTotal (dMass *m, dReal total_mass, dReal radius)
{
  dAASSERT (m);
  dMassSetZero (m);
  m->mass = total_mass;
  dReal II = REAL(0.4) * total_mass * radius*radius;
  m->_I(0,0) = II;
  m->_I(1,1) = II;
  m->_I(2,2) = II;

# ifndef dNODEBUG
  dMassCheck (m);
# endif
}


void dMassSetCapsule (dMass *m, dReal density, int direction,
		      dReal radius, dReal length)
{
  dReal M1,M2,Ia,Ib;
  dAASSERT (m);
  dUASSERT (direction >= 1 && direction <= 3,"bad direction number");
  dMassSetZero (m);
  M1 = (dReal) (M_PI*radius*radius*length*density);			  // cylinder mass
  M2 = (dReal) ((REAL(4.0)/REAL(3.0))*M_PI*radius*radius*radius*density); // total cap mass
  m->mass = M1+M2;
  Ia = M1*(REAL(0.25)*radius*radius + (REAL(1.0)/REAL(12.0))*length*length) +
    M2*(REAL(0.4)*radius*radius + REAL(0.375)*radius*length + REAL(0.25)*length*length);
  Ib = (M1*REAL(0.5) + M2*REAL(0.4))*radius*radius;
  m->_I(0,0) = Ia;
  m->_I(1,1) = Ia;
  m->_I(2,2) = Ia;
  m->_I(direction-1,direction-1) = Ib;

# ifndef dNODEBUG
  dMassCheck (m);
# endif
}


void dMassSetCapsuleTotal (dMass *m, dReal total_mass, int direction,
			   dReal a, dReal b)
{
  dMassSetCapsule (m, 1.0, direction, a, b);
  dMassAdjust (m, total_mass);
}


void dMassSetCylinder (dMass *m, dReal density, int direction,
		       dReal radius, dReal length)
{
  dMassSetCylinderTotal (m, (dReal) (M_PI*radius*radius*length*density),
			    direction, radius, length);
}

void dMassSetCylinderTotal (dMass *m, dReal total_mass, int direction,
			    dReal radius, dReal length)
{
  dReal r2,I;
  dAASSERT (m);
  dUASSERT (direction >= 1 && direction <= 3,"bad direction number");
  dMassSetZero (m);
  r2 = radius*radius;
  m->mass = total_mass;
  I = total_mass*(REAL(0.25)*r2 + (REAL(1.0)/REAL(12.0))*length*length);
  m->_I(0,0) = I;
  m->_I(1,1) = I;
  m->_I(2,2) = I;
  m->_I(direction-1,direction-1) = total_mass*REAL(0.5)*r2;

# ifndef dNODEBUG
  dMassCheck (m);
# endif
}


void dMassSetBox (dMass *m, dReal density,
		  dReal lx, dReal ly, dReal lz)
{
  dMassSetBoxTotal (m, lx*ly*lz*density, lx, ly, lz);
}


void dMassSetBoxTotal (dMass *m, dReal total_mass,
		       dReal lx, dReal ly, dReal lz)
{
  dAASSERT (m);
  dMassSetZero (m);
  m->mass = total_mass;
  m->_I(0,0) = total_mass/REAL(12.0) * (ly*ly + lz*lz);
  m->_I(1,1) = total_mass/REAL(12.0) * (lx*lx + lz*lz);
  m->_I(2,2) = total_mass/REAL(12.0) * (lx*lx + ly*ly);

# ifndef dNODEBUG
  dMassCheck (m);
# endif
}






/*
 * dMassSetTrimesh, implementation by Gero Mueller.
 * Based on Brian Mirtich, "Fast and Accurate Computation of
 * Polyhedral Mass Properties," journal of graphics tools, volume 1,
 * number 2, 1996.
*/
void dMassSetTrimesh( dMass *m, dReal density, dGeomID g )
{
	dAASSERT (m);
	dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");

	dMassSetZero (m);

#if dTRIMESH_ENABLED

	dxTriMesh *TriMesh = (dxTriMesh *)g;
	unsigned int triangles = FetchTriangleCount( TriMesh );

	dReal nx, ny, nz;
	unsigned int i, A, B, C;
	// face integrals
	dReal Fa, Fb, Fc, Faa, Fbb, Fcc, Faaa, Fbbb, Fccc, Faab, Fbbc, Fcca;

	// projection integrals
	dReal P1, Pa, Pb, Paa, Pab, Pbb, Paaa, Paab, Pabb, Pbbb;

	dReal T0 = 0;
	dReal T1[3] = {0., 0., 0.};
	dReal T2[3] = {0., 0., 0.};
	dReal TP[3] = {0., 0., 0.};

	for( i = 0; i < triangles; i++ )	 	
	{
		dVector3 v[3];
		FetchTransformedTriangle( TriMesh, i, v);

		dVector3 n, a, b;
		dSubtractVectors3( a, v[1], v[0] ); 
		dSubtractVectors3( b, v[2], v[0] ); 
		dCalcVectorCross3( n, b, a );
		nx = fabs(n[0]);
		ny = fabs(n[1]);
		nz = fabs(n[2]);

		if( nx > ny && nx > nz )
			C = 0;
		else
			C = (ny > nz) ? 1 : 2;

		// Even though all triangles might be initially valid, 
		// a triangle may degenerate into a segment after applying 
		// space transformation.
		if (n[C] != REAL(0.0))
		{
			A = (C + 1) % 3;
			B = (A + 1) % 3;

			// calculate face integrals
			{
				dReal w;
				dReal k1, k2, k3, k4;

				//compProjectionIntegrals(f);
				{
					dReal a0=0, a1=0, da;
					dReal b0=0, b1=0, db;
					dReal a0_2, a0_3, a0_4, b0_2, b0_3, b0_4;
					dReal a1_2, a1_3, b1_2, b1_3;
					dReal C1, Ca, Caa, Caaa, Cb, Cbb, Cbbb;
					dReal Cab, Kab, Caab, Kaab, Cabb, Kabb;

					P1 = Pa = Pb = Paa = Pab = Pbb = Paaa = Paab = Pabb = Pbbb = 0.0;

					for( int j = 0; j < 3; j++)
					{
						switch(j)
						{
						case 0:
							a0 = v[0][A];
							b0 = v[0][B];
							a1 = v[1][A];
							b1 = v[1][B];
							break;
						case 1:
							a0 = v[1][A];
							b0 = v[1][B];
							a1 = v[2][A];
							b1 = v[2][B];
							break;
						case 2:
							a0 = v[2][A];
							b0 = v[2][B];
							a1 = v[0][A];
							b1 = v[0][B];
							break;
						}
						da = a1 - a0;
						db = b1 - b0;
						a0_2 = a0 * a0; a0_3 = a0_2 * a0; a0_4 = a0_3 * a0;
						b0_2 = b0 * b0; b0_3 = b0_2 * b0; b0_4 = b0_3 * b0;
						a1_2 = a1 * a1; a1_3 = a1_2 * a1; 
						b1_2 = b1 * b1; b1_3 = b1_2 * b1;

						C1 = a1 + a0;
						Ca = a1*C1 + a0_2; Caa = a1*Ca + a0_3; Caaa = a1*Caa + a0_4;
						Cb = b1*(b1 + b0) + b0_2; Cbb = b1*Cb + b0_3; Cbbb = b1*Cbb + b0_4;
						Cab = 3*a1_2 + 2*a1*a0 + a0_2; Kab = a1_2 + 2*a1*a0 + 3*a0_2;
						Caab = a0*Cab + 4*a1_3; Kaab = a1*Kab + 4*a0_3;
						Cabb = 4*b1_3 + 3*b1_2*b0 + 2*b1*b0_2 + b0_3;
						Kabb = b1_3 + 2*b1_2*b0 + 3*b1*b0_2 + 4*b0_3;

						P1 += db*C1;
						Pa += db*Ca;
						Paa += db*Caa;
						Paaa += db*Caaa;
						Pb += da*Cb;
						Pbb += da*Cbb;
						Pbbb += da*Cbbb;
						Pab += db*(b1*Cab + b0*Kab);
						Paab += db*(b1*Caab + b0*Kaab);
						Pabb += da*(a1*Cabb + a0*Kabb);
					}

					P1 /= 2.0;
					Pa /= 6.0;
					Paa /= 12.0;
					Paaa /= 20.0;
					Pb /= -6.0;
					Pbb /= -12.0;
					Pbbb /= -20.0;
					Pab /= 24.0;
					Paab /= 60.0;
					Pabb /= -60.0;
				}			

				w = - dCalcVectorDot3(n, v[0]);

				k1 = 1 / n[C]; k2 = k1 * k1; k3 = k2 * k1; k4 = k3 * k1;

				Fa = k1 * Pa;
				Fb = k1 * Pb;
				Fc = -k2 * (n[A]*Pa + n[B]*Pb + w*P1);

				Faa = k1 * Paa;
				Fbb = k1 * Pbb;
				Fcc = k3 * (SQR(n[A])*Paa + 2*n[A]*n[B]*Pab + SQR(n[B])*Pbb +
					w*(2*(n[A]*Pa + n[B]*Pb) + w*P1));

				Faaa = k1 * Paaa;
				Fbbb = k1 * Pbbb;
				Fccc = -k4 * (CUBE(n[A])*Paaa + 3*SQR(n[A])*n[B]*Paab 
					+ 3*n[A]*SQR(n[B])*Pabb + CUBE(n[B])*Pbbb
					+ 3*w*(SQR(n[A])*Paa + 2*n[A]*n[B]*Pab + SQR(n[B])*Pbb)
					+ w*w*(3*(n[A]*Pa + n[B]*Pb) + w*P1));

				Faab = k1 * Paab;
				Fbbc = -k2 * (n[A]*Pabb + n[B]*Pbbb + w*Pbb);
				Fcca = k3 * (SQR(n[A])*Paaa + 2*n[A]*n[B]*Paab + SQR(n[B])*Pabb
					+ w*(2*(n[A]*Paa + n[B]*Pab) + w*Pa));
			}


			T0 += n[0] * ((A == 0) ? Fa : ((B == 0) ? Fb : Fc));

			T1[A] += n[A] * Faa;
			T1[B] += n[B] * Fbb;
			T1[C] += n[C] * Fcc;
			T2[A] += n[A] * Faaa;
			T2[B] += n[B] * Fbbb;
			T2[C] += n[C] * Fccc;
			TP[A] += n[A] * Faab;
			TP[B] += n[B] * Fbbc;
			TP[C] += n[C] * Fcca;
		}
	}

	T1[0] /= 2; T1[1] /= 2; T1[2] /= 2;
	T2[0] /= 3; T2[1] /= 3; T2[2] /= 3;
	TP[0] /= 2; TP[1] /= 2; TP[2] /= 2;

	m->mass = density * T0;
	m->_I(0,0) = density * (T2[1] + T2[2]);
	m->_I(1,1) = density * (T2[2] + T2[0]);
	m->_I(2,2) = density * (T2[0] + T2[1]);
	m->_I(0,1) = - density * TP[0];
	m->_I(1,0) = - density * TP[0];
	m->_I(2,1) = - density * TP[1];
	m->_I(1,2) = - density * TP[1];
	m->_I(2,0) = - density * TP[2];
	m->_I(0,2) = - density * TP[2];

	// Added to address SF bug 1729095
	dMassTranslate( m, T1[0] / T0,  T1[1] / T0,  T1[2] / T0 );

# ifndef dNODEBUG
	dMassCheck (m);
# endif

#endif // dTRIMESH_ENABLED
}


void dMassSetTrimeshTotal( dMass *m, dReal total_mass, dGeomID g)
{
  dAASSERT( m );
  dUASSERT( g && g->type == dTriMeshClass, "argument not a trimesh" );
  dMassSetTrimesh( m, 1.0, g );
  dMassAdjust( m, total_mass );
}




void dMassAdjust (dMass *m, dReal newmass)
{
  dAASSERT (m);
  dReal scale = newmass / m->mass;
  m->mass = newmass;
  for (int i=0; i<3; i++) for (int j=0; j<3; j++) m->_I(i,j) *= scale;

# ifndef dNODEBUG
  dMassCheck (m);
# endif
}


void dMassTranslate (dMass *m, dReal x, dReal y, dReal z)
{
  // if the body is translated by `a' relative to its point of reference,
  // the new inertia about the point of reference is:
  //
  //   I + mass*(crossmat(c)^2 - crossmat(c+a)^2)
  //
  // where c is the existing center of mass and I is the old inertia.

  int i,j;
  dMatrix3 ahat,chat,t1,t2;
  dReal a[3];

  dAASSERT (m);

  // adjust inertia matrix
  dSetZero (chat,12);
  dSetCrossMatrixPlus (chat,m->c,4);
  a[0] = x + m->c[0];
  a[1] = y + m->c[1];
  a[2] = z + m->c[2];
  dSetZero (ahat,12);
  dSetCrossMatrixPlus (ahat,a,4);
  dMultiply0_333 (t1,ahat,ahat);
  dMultiply0_333 (t2,chat,chat);
  for (i=0; i<3; i++) for (j=0; j<3; j++)
    m->_I(i,j) += m->mass * (t2[i*4+j]-t1[i*4+j]);

  // ensure perfect symmetry
  m->_I(1,0) = m->_I(0,1);
  m->_I(2,0) = m->_I(0,2);
  m->_I(2,1) = m->_I(1,2);

  // adjust center of mass
  m->c[0] += x;
  m->c[1] += y;
  m->c[2] += z;

# ifndef dNODEBUG
  dMassCheck (m);
# endif
}


void dMassRotate (dMass *m, const dMatrix3 R)
{
  // if the body is rotated by `R' relative to its point of reference,
  // the new inertia about the point of reference is:
  //
  //   R * I * R'
  //
  // where I is the old inertia.

  dMatrix3 t1;
  dReal t2[3];

  dAASSERT (m);

  // rotate inertia matrix
  dMultiply2_333 (t1,m->I,R);
  dMultiply0_333 (m->I,R,t1);

  // ensure perfect symmetry
  m->_I(1,0) = m->_I(0,1);
  m->_I(2,0) = m->_I(0,2);
  m->_I(2,1) = m->_I(1,2);

  // rotate center of mass
  dMultiply0_331 (t2,R,m->c);
  m->c[0] = t2[0];
  m->c[1] = t2[1];
  m->c[2] = t2[2];

# ifndef dNODEBUG
  dMassCheck (m);
# endif
}


void dMassAdd (dMass *a, const dMass *b)
{
  int i;
  dAASSERT (a && b);
  dReal denom = dRecip (a->mass + b->mass);
  for (i=0; i<3; i++) a->c[i] = (a->c[i]*a->mass + b->c[i]*b->mass)*denom;
  a->mass += b->mass;
  for (i=0; i<12; i++) a->I[i] += b->I[i];
}


// Backwards compatible API
void dMassSetCappedCylinder(dMass *a, dReal b, int c, dReal d, dReal e)
{
  return dMassSetCapsule(a,b,c,d,e);
}

void dMassSetCappedCylinderTotal(dMass *a, dReal b, int c, dReal d, dReal e)
{
  return dMassSetCapsuleTotal(a,b,c,d,e);
}

