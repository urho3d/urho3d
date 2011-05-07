// dHeightfield Collider
//  Paul Cheyrou-Lagreze aka Tuan Kuranes 2006 Speed enhancements http://www.pop-3d.com
//  Martijn Buijs 2006 http://home.planet.nl/~buijs512/
// Based on Terrain & Cone contrib by:
//  Benoit CHAPEROT 2003-2004 http://www.jstarlab.com
//  Some code inspired by Magic Software


#include <ode/common.h>
#include <ode/collision.h>
#include <ode/matrix.h>
#include <ode/rotation.h>
#include <ode/odemath.h>
#include "config.h"
#include "collision_kernel.h"
#include "collision_std.h"
#include "collision_util.h"
#include "heightfield.h"



#if dTRIMESH_ENABLED
#include "collision_trimesh_colliders.h"
#endif // dTRIMESH_ENABLED

#define dMIN(A,B)  ((A)>(B) ? (B) : (A))
#define dMAX(A,B)  ((A)>(B) ? (A) : (B))


// Three-way MIN and MAX
#define dMIN3(A,B,C)	( (A)<(B) ? dMIN((A),(C)) : dMIN((B),(C)) )
#define dMAX3(A,B,C)	( (A)>(B) ? dMAX((A),(C)) : dMAX((B),(C)) )

#define dOPESIGN(a, op1, op2,b) \
    (a)[0] op1 op2 ((b)[0]); \
    (a)[1] op1 op2 ((b)[1]); \
    (a)[2] op1 op2 ((b)[2]);

#define dGeomRaySetNoNormalize(myRay, MyPoint, MyVector) {  \
    \
    dVector3Copy (MyPoint, (myRay).final_posr->pos);   \
    (myRay).final_posr->R[2] = (MyVector)[0];       \
    (myRay).final_posr->R[6] = (MyVector)[1];       \
    (myRay).final_posr->R[10] = (MyVector)[2];      \
    dGeomMoved (&myRay);                        \
            }

#define dGeomPlaneSetNoNormalize(MyPlane, MyPlaneDef) { \
    \
    (MyPlane)->p[0] = (MyPlaneDef)[0];  \
    (MyPlane)->p[1] = (MyPlaneDef)[1];  \
    (MyPlane)->p[2] = (MyPlaneDef)[2];  \
    (MyPlane)->p[3] = (MyPlaneDef)[3];  \
    dGeomMoved (MyPlane);           \
                    }
//////// Local Build Option ////////////////////////////////////////////////////

// Uncomment this #define to use the (0,0) corner of the geom as the origin,
// rather than the center. This was the way the original heightfield worked,
// but as it does not match the way all other geometries work, so for constancy it
// was changed to work like this.

// #define DHEIGHTFIELD_CORNER_ORIGIN


// Uncomment this #define to add heightfield triangles edge colliding
// Code is not guaranteed and I didn't find the need to add that as 
// colliding planes triangles and edge triangles seems enough.
// #define _HEIGHTFIELDEDGECOLLIDING


//////// dxHeightfieldData /////////////////////////////////////////////////////////////

// dxHeightfieldData constructor
dxHeightfieldData::dxHeightfieldData() :	m_fWidth( 0 ),
											m_fDepth( 0 ),
											m_fSampleWidth( 0 ),
											m_fSampleDepth( 0 ),
                                            m_fSampleZXAspect( 0 ),
											m_fInvSampleWidth( 0 ),
											m_fInvSampleDepth( 0 ),
											
											m_fHalfWidth( 0 ),
											m_fHalfDepth( 0 ),

											m_fMinHeight( 0 ),
											m_fMaxHeight( 0 ),
											m_fThickness( 0 ),
											m_fScale( 0 ),
											m_fOffset( 0 ),
											
											m_nWidthSamples( 0 ),
											m_nDepthSamples( 0 ),
											m_bCopyHeightData( 0 ),
											m_bWrapMode( 0 ),
											m_nGetHeightMode( 0 ),
											
											m_pHeightData( NULL ),
											m_pUserData( NULL ),
											
											m_pGetHeightCallback( NULL )
{
	memset( m_contacts, 0, sizeof( m_contacts ) );
}

// build Heightfield data
void dxHeightfieldData::SetData( int nWidthSamples, int nDepthSamples,
                                dReal fWidth, dReal fDepth,
                                dReal fScale, dReal fOffset, dReal fThickness,
                                int bWrapMode )
{
    dIASSERT( fWidth > REAL( 0.0 ) );
    dIASSERT( fDepth > REAL( 0.0 ) );
    dIASSERT( nWidthSamples > 0 );
    dIASSERT( nDepthSamples > 0 );

    // x,z bounds
    m_fWidth = fWidth;
    m_fDepth = fDepth;

    // cache half x,z bounds
    m_fHalfWidth = fWidth / REAL( 2.0 );
    m_fHalfDepth = fDepth / REAL( 2.0 );

    // scale and offset
    m_fScale = fScale;
    m_fOffset = fOffset;

    // infinite min height bounds
    m_fThickness = fThickness;

    // number of vertices per side
    m_nWidthSamples = nWidthSamples;
    m_nDepthSamples = nDepthSamples;

    m_fSampleWidth = m_fWidth / ( m_nWidthSamples - REAL( 1.0 ) );
    m_fSampleDepth = m_fDepth / ( m_nDepthSamples - REAL( 1.0 ) );

    m_fSampleZXAspect = m_fSampleDepth / m_fSampleWidth;

    m_fInvSampleWidth = REAL( 1.0 ) / m_fSampleWidth;
    m_fInvSampleDepth = REAL( 1.0 ) / m_fSampleDepth;

    // finite or repeated terrain?
    m_bWrapMode = bWrapMode;
}


// recomputes heights bounds
void dxHeightfieldData::ComputeHeightBounds()
{
    int i;
    dReal h;
    unsigned char *data_byte;
    short *data_short;
    float *data_float;
    double *data_double;

    switch ( m_nGetHeightMode )
    {

        // callback
    case 0:
        // change nothing, keep using default or user specified bounds
        return;

        // byte
    case 1:
        data_byte = (unsigned char*)m_pHeightData;
        m_fMinHeight = dInfinity;
        m_fMaxHeight = -dInfinity;

        for (i=0; i<m_nWidthSamples*m_nDepthSamples; i++)
        {
            h = data_byte[i];
            if (h < m_fMinHeight)	m_fMinHeight = h;
            if (h > m_fMaxHeight)	m_fMaxHeight = h;
        }

        break;

        // short
    case 2:
        data_short = (short*)m_pHeightData;
        m_fMinHeight = dInfinity;
        m_fMaxHeight = -dInfinity;

        for (i=0; i<m_nWidthSamples*m_nDepthSamples; i++)
        {
            h = data_short[i];
            if (h < m_fMinHeight)	m_fMinHeight = h;
            if (h > m_fMaxHeight)	m_fMaxHeight = h;
        }

        break;

        // float
    case 3:
        data_float = (float*)m_pHeightData;
        m_fMinHeight = dInfinity;
        m_fMaxHeight = -dInfinity;

        for (i=0; i<m_nWidthSamples*m_nDepthSamples; i++)
        {
            h = data_float[i];
            if (h < m_fMinHeight)	m_fMinHeight = h;
            if (h > m_fMaxHeight)	m_fMaxHeight = h;
        }

        break;

        // double
    case 4:
        data_double = (double*)m_pHeightData;
        m_fMinHeight = dInfinity;
        m_fMaxHeight = -dInfinity;

        for (i=0; i<m_nWidthSamples*m_nDepthSamples; i++)
        {
            h = static_cast< dReal >( data_double[i] );
            if (h < m_fMinHeight)	m_fMinHeight = h;
            if (h > m_fMaxHeight)	m_fMaxHeight = h;
        }

        break;

    }

    // scale and offset
    m_fMinHeight *= m_fScale;
    m_fMaxHeight *= m_fScale;
    m_fMinHeight += m_fOffset;
    m_fMaxHeight += m_fOffset;

    // add thickness
    m_fMinHeight -= m_fThickness;
}


// returns whether point is over terrain Cell triangle?
bool dxHeightfieldData::IsOnHeightfield2 ( const HeightFieldVertex * const CellCorner, 
    const dReal * const pos,  const bool isABC) const
{
    // WARNING!!!
    // This function must be written in the way to make sure that every point on
    // XZ plane falls in one and only one triangle. Keep that in mind if you 
    // intend to change the code.
    // Also remember about computational errors and possible mismatches in 
    // values if they are calculated differently in different places in the code.
    // Currently both the implementation has been optimized and effects of 
    // computational errors have been eliminated.

    dReal MaxX, MinX;
    dReal MaxZ, MinZ;

    if (isABC)
    {
        // point A
        MinX = CellCorner->vertex[0];
        if (pos[0] < MinX)
            return false;

        MaxX = (CellCorner->coords[0] + 1) * m_fSampleWidth;
        if (pos[0] >= MaxX)
            return false;

        MinZ = CellCorner->vertex[2];
        if (pos[2] < MinZ)
            return false;

        MaxZ = (CellCorner->coords[1] + 1) * m_fSampleDepth;
        if (pos[2] >= MaxZ)
            return false;

        return (MaxZ - pos[2]) > (pos[0] - MinX) * m_fSampleZXAspect;
    }
    else
    {
        // point D
        MaxX = CellCorner->vertex[0];
        if (pos[0] >= MaxX)
            return false;

        MinX = (CellCorner->coords[0] - 1) * m_fSampleWidth;
        if (pos[0] < MinX)
            return false;

        MaxZ = CellCorner->vertex[2];
        if (pos[2] >= MaxZ)
            return false;

        MinZ = (CellCorner->coords[1] - 1) * m_fSampleDepth;
        if (pos[2] < MinZ)
            return false;

        return (MaxZ - pos[2]) <= (pos[0] - MinX) * m_fSampleZXAspect;
    }
}


// returns height at given sample coordinates
dReal dxHeightfieldData::GetHeight( int x, int z )
{
    dReal h=0;
    unsigned char *data_byte;
    short *data_short;
    float *data_float;
    double *data_double;

    if ( m_bWrapMode == 0 )
    {
        // Finite
        if ( x < 0 ) x = 0;
        if ( z < 0 ) z = 0;
        if ( x > m_nWidthSamples - 1 ) x = m_nWidthSamples - 1;
        if ( z > m_nDepthSamples - 1 ) z = m_nDepthSamples - 1;
    }
    else
    {
        // Infinite
        x %= m_nWidthSamples - 1;
        z %= m_nDepthSamples - 1;
        if ( x < 0 ) x += m_nWidthSamples - 1;
        if ( z < 0 ) z += m_nDepthSamples - 1;
    }

    switch ( m_nGetHeightMode )
    {

        // callback (dReal)
    case 0:
        h = (*m_pGetHeightCallback)(m_pUserData, x, z);
        break;

        // byte
    case 1:
        data_byte = (unsigned char*)m_pHeightData;
        h = data_byte[x+(z * m_nWidthSamples)];
        break;

        // short
    case 2:
        data_short = (short*)m_pHeightData;
        h = data_short[x+(z * m_nWidthSamples)];
        break;

        // float
    case 3:
        data_float = (float*)m_pHeightData;
        h = data_float[x+(z * m_nWidthSamples)];
        break;

        // double
    case 4:
        data_double = (double*)m_pHeightData;
        h = (dReal)( data_double[x+(z * m_nWidthSamples)] );
        break;
    }

    return (h * m_fScale) + m_fOffset;
}


// returns height at given coordinates
dReal dxHeightfieldData::GetHeight( dReal x, dReal z )
{
	dReal dnX = dFloor( x * m_fInvSampleWidth );
	dReal dnZ = dFloor( z * m_fInvSampleDepth );

    dReal dx = ( x - ( dnX * m_fSampleWidth ) ) * m_fInvSampleWidth;
    dReal dz = ( z - ( dnZ * m_fSampleDepth ) ) * m_fInvSampleDepth;

    int nX = int( dnX );
    int nZ = int( dnZ );

    //dIASSERT( ( dx + dEpsilon >= 0.0f ) && ( dx - dEpsilon <= 1.0f ) );
    //dIASSERT( ( dz + dEpsilon >= 0.0f ) && ( dz - dEpsilon <= 1.0f ) );

    dReal y, y0;

    if ( dx + dz <= REAL( 1.0 ) ) // Use <= comparison to prefer simpler branch
    {
        y0 = GetHeight( nX, nZ );

        y = y0 + ( GetHeight( nX + 1, nZ ) - y0 ) * dx
            + ( GetHeight( nX, nZ + 1 ) - y0 ) * dz;
    }
    else
    {
        y0 = GetHeight( nX + 1, nZ + 1 );

        y = y0	+ ( GetHeight( nX + 1, nZ ) - y0 ) * ( REAL(1.0) - dz ) +
            ( GetHeight( nX, nZ + 1 ) - y0 ) * ( REAL(1.0) - dx );
    }

    return y;
}


// dxHeightfieldData destructor
dxHeightfieldData::~dxHeightfieldData()
{
    unsigned char *data_byte;
    short *data_short;
    float *data_float;
    double *data_double;

    if ( m_bCopyHeightData )
    {
        switch ( m_nGetHeightMode )
        {

            // callback
        case 0:
            // do nothing
            break;

            // byte
        case 1:
            dIASSERT( m_pHeightData );
            data_byte = (unsigned char*)m_pHeightData;
            delete [] data_byte;
            break;

            // short
        case 2:
            dIASSERT( m_pHeightData );
            data_short = (short*)m_pHeightData;
            delete [] data_short;
            break;

            // float
        case 3:
            dIASSERT( m_pHeightData );
            data_float = (float*)m_pHeightData;
            delete [] data_float;
            break;

            // double
        case 4:
            dIASSERT( m_pHeightData );
            data_double = (double*)m_pHeightData;
            delete [] data_double;
            break;

        }
    }
}


//////// dxHeightfield /////////////////////////////////////////////////////////////////


// dxHeightfield constructor
dxHeightfield::dxHeightfield( dSpaceID space,
                             dHeightfieldDataID data,
                             int bPlaceable )			:
    dxGeom( space, bPlaceable ),
    tempPlaneBuffer(0),
	tempPlaneInstances(0),
    tempPlaneBufferSize(0),
    tempTriangleBuffer(0),
    tempTriangleBufferSize(0),
    tempHeightBuffer(0),
	tempHeightInstances(0),
    tempHeightBufferSizeX(0),
    tempHeightBufferSizeZ(0)
{
    type = dHeightfieldClass;
    this->m_p_data = data;
}


// compute axis aligned bounding box
void dxHeightfield::computeAABB()
{
    const dxHeightfieldData *d = m_p_data;

    if ( d->m_bWrapMode == 0 )
    {
        // Finite
        if ( gflags & GEOM_PLACEABLE )
        {
            dReal dx[6], dy[6], dz[6];

            // Y-axis
            if (d->m_fMinHeight != -dInfinity)
            {
                dy[0] = ( final_posr->R[ 1] * d->m_fMinHeight );
                dy[1] = ( final_posr->R[ 5] * d->m_fMinHeight );
                dy[2] = ( final_posr->R[ 9] * d->m_fMinHeight );
            }
            else
            {
                // Multiplication is performed to obtain infinity of correct sign
                dy[0] = ( final_posr->R[ 1] ? final_posr->R[ 1] * -dInfinity : REAL(0.0) );
                dy[1] = ( final_posr->R[ 5] ? final_posr->R[ 5] * -dInfinity : REAL(0.0) );
                dy[2] = ( final_posr->R[ 9] ? final_posr->R[ 9] * -dInfinity : REAL(0.0) );
            }

            if (d->m_fMaxHeight != dInfinity)
            {
                dy[3] = ( final_posr->R[ 1] * d->m_fMaxHeight );
                dy[4] = ( final_posr->R[ 5] * d->m_fMaxHeight );
                dy[5] = ( final_posr->R[ 9] * d->m_fMaxHeight );
            }
            else
            {
                dy[3] = ( final_posr->R[ 1] ? final_posr->R[ 1] * dInfinity : REAL(0.0) );
                dy[4] = ( final_posr->R[ 5] ? final_posr->R[ 5] * dInfinity : REAL(0.0) );
                dy[5] = ( final_posr->R[ 9] ? final_posr->R[ 9] * dInfinity : REAL(0.0) );
            }

#ifdef DHEIGHTFIELD_CORNER_ORIGIN

            // X-axis
            dx[0] = 0;	dx[3] = ( final_posr->R[ 0] * d->m_fWidth );
            dx[1] = 0;	dx[4] = ( final_posr->R[ 4] * d->m_fWidth );
            dx[2] = 0;	dx[5] = ( final_posr->R[ 8] * d->m_fWidth );

            // Z-axis
            dz[0] = 0;	dz[3] = ( final_posr->R[ 2] * d->m_fDepth );
            dz[1] = 0;	dz[4] = ( final_posr->R[ 6] * d->m_fDepth );
            dz[2] = 0;	dz[5] = ( final_posr->R[10] * d->m_fDepth );

#else // DHEIGHTFIELD_CORNER_ORIGIN

            // X-axis
            dx[0] = ( final_posr->R[ 0] * -d->m_fHalfWidth );
            dx[1] = ( final_posr->R[ 4] * -d->m_fHalfWidth );
            dx[2] = ( final_posr->R[ 8] * -d->m_fHalfWidth );
            dx[3] = ( final_posr->R[ 0] * d->m_fHalfWidth );
            dx[4] = ( final_posr->R[ 4] * d->m_fHalfWidth );
            dx[5] = ( final_posr->R[ 8] * d->m_fHalfWidth );

            // Z-axis
            dz[0] = ( final_posr->R[ 2] * -d->m_fHalfDepth );
            dz[1] = ( final_posr->R[ 6] * -d->m_fHalfDepth );
            dz[2] = ( final_posr->R[10] * -d->m_fHalfDepth );
            dz[3] = ( final_posr->R[ 2] * d->m_fHalfDepth );
            dz[4] = ( final_posr->R[ 6] * d->m_fHalfDepth );
            dz[5] = ( final_posr->R[10] * d->m_fHalfDepth );

#endif // DHEIGHTFIELD_CORNER_ORIGIN

            // X extents
            aabb[0] = final_posr->pos[0] +
                dMIN3( dMIN( dx[0], dx[3] ), dMIN( dy[0], dy[3] ), dMIN( dz[0], dz[3] ) );
            aabb[1] = final_posr->pos[0] +
                dMAX3( dMAX( dx[0], dx[3] ), dMAX( dy[0], dy[3] ), dMAX( dz[0], dz[3] ) );

            // Y extents
            aabb[2] = final_posr->pos[1] +
                dMIN3( dMIN( dx[1], dx[4] ), dMIN( dy[1], dy[4] ), dMIN( dz[1], dz[4] ) );
            aabb[3] = final_posr->pos[1] +
                dMAX3( dMAX( dx[1], dx[4] ), dMAX( dy[1], dy[4] ), dMAX( dz[1], dz[4] ) );

            // Z extents
            aabb[4] = final_posr->pos[2] +
                dMIN3( dMIN( dx[2], dx[5] ), dMIN( dy[2], dy[5] ), dMIN( dz[2], dz[5] ) );
            aabb[5] = final_posr->pos[2] +
                dMAX3( dMAX( dx[2], dx[5] ), dMAX( dy[2], dy[5] ), dMAX( dz[2], dz[5] ) );
        }
        else
        {

#ifdef DHEIGHTFIELD_CORNER_ORIGIN

            aabb[0] = 0;					aabb[1] = d->m_fWidth;
            aabb[2] = d->m_fMinHeight;		aabb[3] = d->m_fMaxHeight;
            aabb[4] = 0;					aabb[5] = d->m_fDepth;

#else // DHEIGHTFIELD_CORNER_ORIGIN

            aabb[0] = -d->m_fHalfWidth;		aabb[1] = +d->m_fHalfWidth;
            aabb[2] = d->m_fMinHeight;		aabb[3] = d->m_fMaxHeight;
            aabb[4] = -d->m_fHalfDepth;		aabb[5] = +d->m_fHalfDepth;

#endif // DHEIGHTFIELD_CORNER_ORIGIN

        }
    }
    else
    {
        // Infinite
        if ( gflags & GEOM_PLACEABLE )
        {
            aabb[0] = -dInfinity;			aabb[1] = +dInfinity;
            aabb[2] = -dInfinity;			aabb[3] = +dInfinity;
            aabb[4] = -dInfinity;			aabb[5] = +dInfinity;
        }
        else
        {
            aabb[0] = -dInfinity;			aabb[1] = +dInfinity;
            aabb[2] = d->m_fMinHeight;		aabb[3] = d->m_fMaxHeight;
            aabb[4] = -dInfinity;			aabb[5] = +dInfinity;
        }
    }

}


// dxHeightfield destructor
dxHeightfield::~dxHeightfield()
{
	resetTriangleBuffer();
	resetPlaneBuffer();
	resetHeightBuffer();
}

void dxHeightfield::allocateTriangleBuffer(size_t numTri)
{
	size_t alignedNumTri = AlignBufferSize(numTri, TEMP_TRIANGLE_BUFFER_ELEMENT_COUNT_ALIGNMENT);
	tempTriangleBufferSize = alignedNumTri;
	tempTriangleBuffer = new HeightFieldTriangle[alignedNumTri];
}

void dxHeightfield::resetTriangleBuffer()
{
	delete[] tempTriangleBuffer;
}

void dxHeightfield::allocatePlaneBuffer(size_t numTri)
{
	size_t alignedNumTri = AlignBufferSize(numTri, TEMP_PLANE_BUFFER_ELEMENT_COUNT_ALIGNMENT);
	tempPlaneBufferSize = alignedNumTri;
	tempPlaneBuffer = new HeightFieldPlane *[alignedNumTri];
	tempPlaneInstances = new HeightFieldPlane[alignedNumTri];

	HeightFieldPlane *ptrPlaneMatrix = tempPlaneInstances;
	for (size_t indexTri = 0; indexTri != alignedNumTri; indexTri++)
	{
		tempPlaneBuffer[indexTri] = ptrPlaneMatrix;
		ptrPlaneMatrix += 1;
	}
}

void dxHeightfield::resetPlaneBuffer()
{
	delete[] tempPlaneInstances;
    delete[] tempPlaneBuffer;
}

void dxHeightfield::allocateHeightBuffer(size_t numX, size_t numZ)
{
	size_t alignedNumX = AlignBufferSize(numX, TEMP_HEIGHT_BUFFER_ELEMENT_COUNT_ALIGNMENT_X);
	size_t alignedNumZ = AlignBufferSize(numZ, TEMP_HEIGHT_BUFFER_ELEMENT_COUNT_ALIGNMENT_Z);
	tempHeightBufferSizeX = alignedNumX;
	tempHeightBufferSizeZ = alignedNumZ;
	tempHeightBuffer = new HeightFieldVertex *[alignedNumX];
	size_t numCells = alignedNumX * alignedNumZ;
	tempHeightInstances = new HeightFieldVertex [numCells];
	
	HeightFieldVertex *ptrHeightMatrix = tempHeightInstances;
	for (size_t indexX = 0; indexX != alignedNumX; indexX++)
	{
		tempHeightBuffer[indexX] = ptrHeightMatrix;
		ptrHeightMatrix += alignedNumZ;
	}
}

void dxHeightfield::resetHeightBuffer()
{
	delete[] tempHeightInstances;
    delete[] tempHeightBuffer;
}
//////// Heightfield data interface ////////////////////////////////////////////////////


dHeightfieldDataID dGeomHeightfieldDataCreate()
{
    return new dxHeightfieldData();
}


void dGeomHeightfieldDataBuildCallback( dHeightfieldDataID d,
                                       void* pUserData, dHeightfieldGetHeight* pCallback,
                                       dReal width, dReal depth, int widthSamples, int depthSamples,
                                       dReal scale, dReal offset, dReal thickness, int bWrap )
{
    dUASSERT( d, "argument not Heightfield data" );
    dIASSERT( pCallback );
    dIASSERT( widthSamples >= 2 );	// Ensure we're making something with at least one cell.
    dIASSERT( depthSamples >= 2 );

    // callback
    d->m_nGetHeightMode = 0;
    d->m_pUserData = pUserData;
    d->m_pGetHeightCallback = pCallback;

    // set info
    d->SetData( widthSamples, depthSamples, width, depth, scale, offset, thickness, bWrap );

    // default bounds
    d->m_fMinHeight = -dInfinity;
    d->m_fMaxHeight = dInfinity;
}


void dGeomHeightfieldDataBuildByte( dHeightfieldDataID d,
                                   const unsigned char *pHeightData, int bCopyHeightData,
                                   dReal width, dReal depth, int widthSamples, int depthSamples,
                                   dReal scale, dReal offset, dReal thickness, int bWrap )
{
    dUASSERT( d, "Argument not Heightfield data" );
    dIASSERT( pHeightData );
    dIASSERT( widthSamples >= 2 );	// Ensure we're making something with at least one cell.
    dIASSERT( depthSamples >= 2 );

    // set info
    d->SetData( widthSamples, depthSamples, width, depth, scale, offset, thickness, bWrap );
    d->m_nGetHeightMode = 1;
    d->m_bCopyHeightData = bCopyHeightData;

    if ( d->m_bCopyHeightData == 0 )
    {
        // Data is referenced only.
        d->m_pHeightData = pHeightData;
    }
    else
    {
        // We own the height data, allocate storage
        d->m_pHeightData = new unsigned char[ d->m_nWidthSamples * d->m_nDepthSamples ];
        dIASSERT( d->m_pHeightData );

        // Copy data.
        memcpy( (void*)d->m_pHeightData, pHeightData,
            sizeof( unsigned char ) * d->m_nWidthSamples * d->m_nDepthSamples );
    }

    // Find height bounds
    d->ComputeHeightBounds();
}


void dGeomHeightfieldDataBuildShort( dHeightfieldDataID d,
                                    const short* pHeightData, int bCopyHeightData,
                                    dReal width, dReal depth, int widthSamples, int depthSamples,
                                    dReal scale, dReal offset, dReal thickness, int bWrap )
{
    dUASSERT( d, "Argument not Heightfield data" );
    dIASSERT( pHeightData );
    dIASSERT( widthSamples >= 2 );	// Ensure we're making something with at least one cell.
    dIASSERT( depthSamples >= 2 );

    // set info
    d->SetData( widthSamples, depthSamples, width, depth, scale, offset, thickness, bWrap );
    d->m_nGetHeightMode = 2;
    d->m_bCopyHeightData = bCopyHeightData;

    if ( d->m_bCopyHeightData == 0 )
    {
        // Data is referenced only.
        d->m_pHeightData = pHeightData;
    }
    else
    {
        // We own the height data, allocate storage
        d->m_pHeightData = new short[ d->m_nWidthSamples * d->m_nDepthSamples ];
        dIASSERT( d->m_pHeightData );

        // Copy data.
        memcpy( (void*)d->m_pHeightData, pHeightData,
            sizeof( short ) * d->m_nWidthSamples * d->m_nDepthSamples );
    }

    // Find height bounds
    d->ComputeHeightBounds();
}


void dGeomHeightfieldDataBuildSingle( dHeightfieldDataID d,
                                     const float *pHeightData, int bCopyHeightData,
                                     dReal width, dReal depth, int widthSamples, int depthSamples,
                                     dReal scale, dReal offset, dReal thickness, int bWrap )
{
    dUASSERT( d, "Argument not Heightfield data" );
    dIASSERT( pHeightData );
    dIASSERT( widthSamples >= 2 );	// Ensure we're making something with at least one cell.
    dIASSERT( depthSamples >= 2 );

    // set info
    d->SetData( widthSamples, depthSamples, width, depth, scale, offset, thickness, bWrap );
    d->m_nGetHeightMode = 3;
    d->m_bCopyHeightData = bCopyHeightData;

    if ( d->m_bCopyHeightData == 0 )
    {
        // Data is referenced only.
        d->m_pHeightData = pHeightData;
    }
    else
    {
        // We own the height data, allocate storage
        d->m_pHeightData = new float[ d->m_nWidthSamples * d->m_nDepthSamples ];
        dIASSERT( d->m_pHeightData );

        // Copy data.
        memcpy( (void*)d->m_pHeightData, pHeightData,
            sizeof( float ) * d->m_nWidthSamples * d->m_nDepthSamples );
    }

    // Find height bounds
    d->ComputeHeightBounds();
}

void dGeomHeightfieldDataBuildDouble( dHeightfieldDataID d,
                                     const double *pHeightData, int bCopyHeightData,
                                     dReal width, dReal depth, int widthSamples, int depthSamples,
                                     dReal scale, dReal offset, dReal thickness, int bWrap )
{
    dUASSERT( d, "Argument not Heightfield data" );
    dIASSERT( pHeightData );
    dIASSERT( widthSamples >= 2 );	// Ensure we're making something with at least one cell.
    dIASSERT( depthSamples >= 2 );

    // set info
    d->SetData( widthSamples, depthSamples, width, depth, scale, offset, thickness, bWrap );
    d->m_nGetHeightMode = 4;
    d->m_bCopyHeightData = bCopyHeightData;

    if ( d->m_bCopyHeightData == 0 )
    {
        // Data is referenced only.
        d->m_pHeightData = pHeightData;
    }
    else
    {
        // We own the height data, allocate storage
        d->m_pHeightData = new double[ d->m_nWidthSamples * d->m_nDepthSamples ];
        dIASSERT( d->m_pHeightData );

        // Copy data.
        memcpy( (void*)d->m_pHeightData, pHeightData,
            sizeof( double ) * d->m_nWidthSamples * d->m_nDepthSamples );
    }

    // Find height bounds
    d->ComputeHeightBounds();
}




void dGeomHeightfieldDataSetBounds( dHeightfieldDataID d, dReal minHeight, dReal maxHeight )
{
    dUASSERT(d, "Argument not Heightfield data");
    d->m_fMinHeight = ( minHeight * d->m_fScale ) + d->m_fOffset - d->m_fThickness;
    d->m_fMaxHeight = ( maxHeight * d->m_fScale ) + d->m_fOffset;
}


void dGeomHeightfieldDataDestroy( dHeightfieldDataID d )
{
    dUASSERT(d, "argument not Heightfield data");
    delete d;
}


//////// Heightfield geom interface ////////////////////////////////////////////////////


dGeomID dCreateHeightfield( dSpaceID space, dHeightfieldDataID data, int bPlaceable )
{
    return new dxHeightfield( space, data, bPlaceable );
}


void dGeomHeightfieldSetHeightfieldData( dGeomID g, dHeightfieldDataID d )
{
    dxHeightfield* geom = (dxHeightfield*) g;
    geom->data = d;
}


dHeightfieldDataID dGeomHeightfieldGetHeightfieldData( dGeomID g )
{
    dxHeightfield* geom = (dxHeightfield*) g;
    return geom->m_p_data;
}

//////// dxHeightfield /////////////////////////////////////////////////////////////////


// Typedef for generic 'get point depth' function
typedef dReal dGetDepthFn( dGeomID g, dReal x, dReal y, dReal z );


#define DMESS(A)	\
    dMessage(0,"Contact Plane (%d %d %d) %.5e %.5e (%.5e %.5e %.5e)(%.5e %.5e %.5e)).",	\
    x,z,(A),	\
    pContact->depth,	\
    dGeomSphereGetRadius(o2),		\
    pContact->pos[0],	\
    pContact->pos[1],	\
    pContact->pos[2],	\
    pContact->normal[0],	\
    pContact->normal[1],	\
    pContact->normal[2]);

static inline bool DescendingTriangleSort(const HeightFieldTriangle * const A, const HeightFieldTriangle * const B)
{
    return ((A->maxAAAB - B->maxAAAB) > dEpsilon);
}
static inline bool DescendingPlaneSort(const HeightFieldPlane * const A, const HeightFieldPlane * const B)
{
    return ((A->maxAAAB - B->maxAAAB) > dEpsilon);
}

void dxHeightfield::sortPlanes(const size_t numPlanes)
{
    bool has_swapped = true;
    do
    {
        has_swapped = false;//reset flag
        for (size_t i = 0; i < numPlanes - 1; i++)
        {
            //if they are in the wrong order
            if (DescendingPlaneSort(tempPlaneBuffer[i], tempPlaneBuffer[i + 1]))
            { 
                //exchange them
                HeightFieldPlane * tempPlane = tempPlaneBuffer[i];
                tempPlaneBuffer[i] = tempPlaneBuffer[i + 1];
                tempPlaneBuffer[i + 1] = tempPlane;

                //we have swapped at least once, list may not be sorted yet
                has_swapped = true;
            }
        }
    }    //if no swaps were made during this pass, the list has been sorted
    while (has_swapped);
}

static inline dReal DistancePointToLine(const dVector3 &_point,
                                         const dVector3 &_pt0,
                                         const dVector3 &_Edge,
                                         const dReal _Edgelength)
{
    dVector3 v;
    dVector3Subtract(_point, _pt0, v);
    dVector3 s;
    dVector3Copy (_Edge, s);
    const dReal dot = dVector3Dot(v, _Edge) / _Edgelength;
    dVector3Scale(s, dot);
    dVector3Subtract(v, s, v);
    return dVector3Length(v);
}




int dxHeightfield::dCollideHeightfieldZone( const int minX, const int maxX, const int minZ, const int maxZ, 
                                           dxGeom* o2, const int numMaxContactsPossible,
                                           int flags, dContactGeom* contact, 
                                           int skip )
{
	dContactGeom *pContact = 0;
    int  x, z;
    // check if not above or inside terrain first
    // while filling a heightmap partial temporary buffer
    const unsigned int numX = (maxX - minX) + 1;
    const unsigned int numZ = (maxZ - minZ) + 1;
    const dReal minO2Height = o2->aabb[2];
    const dReal maxO2Height = o2->aabb[3];
    unsigned int x_local, z_local;
    dReal maxY = - dInfinity;
    dReal minY = dInfinity;
    // localize and const for faster access
    const dReal cfSampleWidth = m_p_data->m_fSampleWidth;
    const dReal cfSampleDepth = m_p_data->m_fSampleDepth;
    {
        if (tempHeightBufferSizeX < numX || tempHeightBufferSizeZ < numZ)
        {
            resetHeightBuffer();
			allocateHeightBuffer(numX, numZ);
        }

        dReal Xpos, Ypos;

        for ( x = minX, x_local = 0; x_local < numX; x++, x_local++)
        {
            Xpos = x * cfSampleWidth; // Always calculate pos via multiplication to avoid computational error accumulation during multiple additions

            const dReal c_Xpos = Xpos;
            HeightFieldVertex *HeightFieldRow = tempHeightBuffer[x_local];
            for ( z = minZ, z_local = 0; z_local < numZ; z++, z_local++)
            {
                Ypos = z * cfSampleDepth; // Always calculate pos via multiplication to avoid computational error accumulation during multiple additions

                const dReal h = m_p_data->GetHeight(x, z);
                HeightFieldRow[z_local].vertex[0] = c_Xpos;
                HeightFieldRow[z_local].vertex[1] = h;
                HeightFieldRow[z_local].vertex[2] = Ypos;
                HeightFieldRow[z_local].coords[0] = x;
                HeightFieldRow[z_local].coords[1] = z;

                maxY = dMAX(maxY, h);
                minY = dMIN(minY, h);
            }
        }
        if (minO2Height - maxY > -dEpsilon )
        {
			//totally above heightfield
            return 0;
        }
		if (minY - maxO2Height > -dEpsilon )
		{
			// totally under heightfield
			pContact = CONTACT(contact, 0);

			pContact->pos[0] = o2->final_posr->pos[0];
			pContact->pos[1] = minY;
			pContact->pos[2] = o2->final_posr->pos[2];

			pContact->normal[0] = 0;
			pContact->normal[1] = - 1;
			pContact->normal[2] = 0;

			pContact->depth =  minY - maxO2Height;

            pContact->side1 = -1;
            pContact->side2 = -1;

			return 1;
		}
    }
    // get All Planes that could collide against.
    dColliderFn *geomRayNCollider=0;
    dColliderFn *geomNPlaneCollider=0;
    dGetDepthFn *geomNDepthGetter=0;

    // int max_collisionContact = numMaxContactsPossible; -- not used
    switch (o2->type)
    {
    case dRayClass:
        geomRayNCollider		= NULL;
        geomNPlaneCollider	    = dCollideRayPlane;
        geomNDepthGetter		= NULL;
        //max_collisionContact    = 1;
        break;

    case dSphereClass:
        geomRayNCollider		= dCollideRaySphere;
        geomNPlaneCollider  	= dCollideSpherePlane;
        geomNDepthGetter		= dGeomSpherePointDepth;
        //max_collisionContact    = 3;
        break;

    case dBoxClass:
        geomRayNCollider		= dCollideRayBox;
        geomNPlaneCollider	    = dCollideBoxPlane;
        geomNDepthGetter		= dGeomBoxPointDepth;
        //max_collisionContact    = 8;
        break;

    case dCapsuleClass:
        geomRayNCollider		= dCollideRayCapsule;
        geomNPlaneCollider  	= dCollideCapsulePlane;
        geomNDepthGetter		= dGeomCapsulePointDepth;
        // max_collisionContact    = 3;
        break;

    case dCylinderClass:
        geomRayNCollider		= dCollideRayCylinder;
        geomNPlaneCollider	    = dCollideCylinderPlane;
        geomNDepthGetter		= NULL;// TODO: dGeomCCylinderPointDepth
        //max_collisionContact    = 3;
        break;

    case dConvexClass:
        geomRayNCollider		= dCollideRayConvex;
        geomNPlaneCollider  	= dCollideConvexPlane;
        geomNDepthGetter		= NULL;// TODO: dGeomConvexPointDepth;
        //max_collisionContact    = 3;
        break;

#if dTRIMESH_ENABLED

    case dTriMeshClass:
        geomRayNCollider		= dCollideRayTrimesh;
        geomNPlaneCollider	    = dCollideTrimeshPlane;
        geomNDepthGetter		= NULL;// TODO: dGeomTrimeshPointDepth;
        //max_collisionContact    = 3;
        break;

#endif // dTRIMESH_ENABLED

    default:
        dIASSERT(0);	// Shouldn't ever get here.
        break;

    }

    dxPlane myplane(0,0,0,0,0);
    dxPlane* sliding_plane = &myplane;
    dReal triplane[4];
    int i;

    // check some trivial case.
    // Vector Up plane
    if (maxY - minY < dEpsilon)
    {
        // it's a single plane.
        triplane[0] = 0;
        triplane[1] = 1;
        triplane[2] = 0;
        triplane[3] =  minY;
        dGeomPlaneSetNoNormalize (sliding_plane, triplane);
        // find collision and compute contact points
		const int numTerrainContacts = geomNPlaneCollider (o2, sliding_plane, flags, contact, skip);
		dIASSERT(numTerrainContacts <= numMaxContactsPossible);
        for (i = 0; i < numTerrainContacts; i++)
        {
			pContact = CONTACT(contact, i*skip);
            dOPESIGN(pContact->normal, =, -, triplane);
        }
        return numTerrainContacts;
    }
    
    /* -- This block is invalid as per Martijn Buijs <buijs512@planet.nl>

    The problem seems to be based on the erroneously assumption that if two of 
    the four vertices of a 'grid' are at the same height, the entire grid can be
    represented as a single plane. It works for an axis aligned slope, but fails
    on all 4 grids of a 3x3 spike feature. Since the plane normal is constructed
    from only 3 vertices (only one of the two triangles) this often results in 
    discontinuities at the grid edges (causing small jumps when the contact 
    point moves from one grid to another).

    // unique plane
    {
        // check for very simple plane heightfield
        dReal minXHeightDelta = dInfinity, maxXHeightDelta = - dInfinity;
        dReal minZHeightDelta = dInfinity, maxZHeightDelta = - dInfinity;


        dReal lastXHeight = tempHeightBuffer[0][0].vertex[1];
        for ( x_local = 1; x_local < numX; x_local++)
        {
            HeightFieldVertex *HeightFieldRow = tempHeightBuffer[x_local];

            const dReal deltaX = HeightFieldRow[0].vertex[1] - lastXHeight;

            maxXHeightDelta = dMAX (maxXHeightDelta,  deltaX);
            minXHeightDelta = dMIN (minXHeightDelta,  deltaX);

            dReal lastZHeight = HeightFieldRow[0].vertex[1];
            for ( z_local = 1; z_local < numZ; z_local++)
            {
                const dReal deltaZ = (HeightFieldRow[z_local].vertex[1] - lastZHeight);

                maxZHeightDelta = dMAX (maxZHeightDelta,  deltaZ);
                minZHeightDelta = dMIN (minZHeightDelta,  deltaZ);

            }
        }

        if (maxZHeightDelta - minZHeightDelta < dEpsilon && 
            maxXHeightDelta - minXHeightDelta < dEpsilon )
        {
            // it's a single plane.
            const dVector3 &A = tempHeightBuffer[0][0].vertex;
            const dVector3 &B = tempHeightBuffer[1][0].vertex;
            const dVector3 &C = tempHeightBuffer[0][1].vertex;

            // define 2 edges and a point that will define collision plane
            {
                dVector3 Edge1, Edge2; 
                dVector3Subtract(C, A, Edge1);
                dVector3Subtract(B, A, Edge2);
                dVector3Cross(Edge1, Edge2, triplane);
            }

            // Define Plane
            // Normalize plane normal
            const dReal dinvlength = REAL(1.0) / dVector3Length(triplane);
            triplane[0] *= dinvlength;
            triplane[1] *= dinvlength;
            triplane[2] *= dinvlength;
            // get distance to origin from plane 
            triplane[3] = dVector3Dot(triplane, A);

            dGeomPlaneSetNoNormalize (sliding_plane, triplane);
            // find collision and compute contact points
            const int numTerrainContacts = geomNPlaneCollider (o2, sliding_plane, flags, contact, skip);
			dIASSERT(numTerrainContacts <= numMaxContactsPossible);
            for (i = 0; i < numTerrainContacts; i++)
            {
				pContact = CONTACT(contact, i*skip);
                dOPESIGN(pContact->normal, =, -, triplane);
            }
            return numTerrainContacts;
        }
    }
    */

	int numTerrainContacts = 0;
	dContactGeom *PlaneContact = m_p_data->m_contacts;
	
    const unsigned int numTriMax = (maxX - minX) * (maxZ - minZ) * 2;
    if (tempTriangleBufferSize < numTriMax)
    {
        resetTriangleBuffer();
		allocateTriangleBuffer(numTriMax);
    }
    
    // Sorting triangle/plane  resulting from heightfield zone
    // Perhaps that would be necessary in case of too much limited
    // maximum contact point...
    // or in complex mesh case (trimesh and convex)
    // need some test or insights on this before enabling this.
    const bool isContactNumPointsLimited = 
        true;
    // (numMaxContacts < 8)
    //    || o2->type == dConvexClass
    //    || o2->type == dTriMeshClass
    //    || (numMaxContacts < (int)numTriMax)       
        


    // if small heightfield triangle related to O2 colliding
    // or no Triangle colliding at all.
    bool needFurtherPasses = (o2->type == dTriMeshClass);
    //compute Ratio between Triangle size and O2 aabb size
	// no FurtherPasses are needed in ray class
    if (o2->type != dRayClass  && needFurtherPasses == false)
    {
        const dReal xratio = (o2->aabb[1] - o2->aabb[0]) * m_p_data->m_fInvSampleWidth;
        if (xratio > REAL(1.5))
            needFurtherPasses = true;
        else
        {
            const dReal zratio = (o2->aabb[5] - o2->aabb[4]) * m_p_data->m_fInvSampleDepth;
            if (zratio > REAL(1.5))
                needFurtherPasses = true;
        }

    }

    unsigned int numTri = 0;
    HeightFieldVertex *A, *B, *C, *D;
    /*    (y is up)
         A--------B-...x
         |       /|
         |      / |
         |     /  |
         |    /   |
         |   /    |
         |  /     |
         | /      |
         |/       |
         C--------D   
         .
         .
         .
         z
    */  
    // keep only triangle that does intersect geom
    
    const unsigned int maxX_local = maxX - minX;
    const unsigned int maxZ_local = maxZ - minZ;

    for ( x_local = 0; x_local < maxX_local; x_local++)
    {
        HeightFieldVertex *HeightFieldRow      = tempHeightBuffer[x_local];
        HeightFieldVertex *HeightFieldNextRow  = tempHeightBuffer[x_local + 1];

        // First A
        C = &HeightFieldRow    [0];
        // First B
        D = &HeightFieldNextRow[0];

        for ( z_local = 0; z_local < maxZ_local; z_local++)
        {
            A = C;
            B = D;

            C = &HeightFieldRow    [z_local + 1];
            D = &HeightFieldNextRow[z_local + 1];

            const dReal AHeight = A->vertex[1];
            const dReal BHeight = B->vertex[1];
            const dReal CHeight = C->vertex[1];
            const dReal DHeight = D->vertex[1];

            const bool isACollide = AHeight > minO2Height;
            const bool isBCollide = BHeight > minO2Height;
            const bool isCCollide = CHeight > minO2Height;
            const bool isDCollide = DHeight > minO2Height;

            A->state = !(isACollide);
            B->state = !(isBCollide);
            C->state = !(isCCollide);
            D->state = !(isDCollide);

            if (isACollide || isBCollide || isCCollide)
            {
                HeightFieldTriangle * const CurrTriUp = &tempTriangleBuffer[numTri++];

                CurrTriUp->state = false;

                // changing point order here implies to change it in isOnHeightField
                CurrTriUp->vertices[0] = A;
                CurrTriUp->vertices[1] = B;
                CurrTriUp->vertices[2] = C;

                if (isContactNumPointsLimited)
                    CurrTriUp->setMinMax();
                CurrTriUp->isUp = true;
            }

            if (isBCollide || isCCollide || isDCollide)
            {
                HeightFieldTriangle * const CurrTriDown = &tempTriangleBuffer[numTri++];

                CurrTriDown->state = false;
                // changing point order here implies to change it in isOnHeightField

                CurrTriDown->vertices[0] = D;
                CurrTriDown->vertices[1] = B;
                CurrTriDown->vertices[2] = C;


                if (isContactNumPointsLimited)
                    CurrTriDown->setMinMax();
                CurrTriDown->isUp = false;
            }


            if (needFurtherPasses &&
                (isBCollide || isCCollide)
                &&
                (AHeight > CHeight &&
                 AHeight > BHeight &&
                 DHeight > CHeight &&
                 DHeight > BHeight))
            {
                // That means Edge BC is concave, therefore
                // BC Edge and B and C vertices cannot collide

                B->state = true;
                C->state = true;
            }
            // should find a way to check other edges (AB, BD, CD) too for concavity
        }
    }

    // at least on triangle should intersect geom
    dIASSERT (numTri != 0);
    // pass1: VS triangle as Planes
    // Group Triangle by same plane definition
    // as Terrain often has many triangles using same plane definition
    // then collide against that list of triangles.
    {

        dVector3 Edge1, Edge2;
        //compute all triangles normals.
        for (unsigned int k = 0; k < numTri; k++)
        {
            HeightFieldTriangle * const itTriangle = &tempTriangleBuffer[k];

            // define 2 edges and a point that will define collision plane
            dVector3Subtract(itTriangle->vertices[2]->vertex, itTriangle->vertices[0]->vertex, Edge1);
            dVector3Subtract(itTriangle->vertices[1]->vertex, itTriangle->vertices[0]->vertex, Edge2);

            // find a perpendicular vector to the triangle
            if  (itTriangle->isUp)
                dVector3Cross(Edge1, Edge2, triplane);
            else
                dVector3Cross(Edge2, Edge1, triplane);

            // Define Plane
            // Normalize plane normal
            const dReal dinvlength = REAL(1.0) / dVector3Length(triplane);
            triplane[0] *= dinvlength;
            triplane[1] *= dinvlength;
            triplane[2] *= dinvlength;
            // get distance to origin from plane 
            triplane[3] = dVector3Dot(triplane, itTriangle->vertices[0]->vertex);

            // saves normal for collision check (planes, triangles, vertices and edges.)
            dVector3Copy(triplane, itTriangle->planeDef);
            // saves distance for collision check (planes, triangles, vertices and edges.)
            itTriangle->planeDef[3] = triplane[3];
        }

        // group by Triangles by Planes sharing shame plane definition
        if (tempPlaneBufferSize  < numTri)
        {
            resetPlaneBuffer();
			allocatePlaneBuffer(numTri);
        }

        unsigned int numPlanes = 0;
        for (unsigned int k = 0; k < numTri; k++)
        {
            HeightFieldTriangle * const tri_base = &tempTriangleBuffer[k];

            if (tri_base->state == true)
                continue;// already tested or added to plane list.

            HeightFieldPlane * const currPlane = tempPlaneBuffer[numPlanes];
            currPlane->resetTriangleListSize(numTri - k);
            currPlane->addTriangle(tri_base);
            // saves normal for collision check (planes, triangles, vertices and edges.)
            dVector3Copy(tri_base->planeDef, currPlane->planeDef);
            // saves distance for collision check (planes, triangles, vertices and edges.)
            currPlane->planeDef[3]= tri_base->planeDef[3];

            const dReal normx = tri_base->planeDef[0];
            const dReal normy = tri_base->planeDef[1];
            const dReal normz = tri_base->planeDef[2];
            const dReal dist = tri_base->planeDef[3];

            for (unsigned int m = k + 1; m < numTri; m++)
            {

                HeightFieldTriangle * const tri_test = &tempTriangleBuffer[m];
                if (tri_test->state == true)
                    continue;// already tested or added to plane list.

                // normals and distance are the same.
                if (
                    dFabs(normy - tri_test->planeDef[1]) < dEpsilon &&  
                    dFabs(dist  - tri_test->planeDef[3]) < dEpsilon &&
                    dFabs(normx - tri_test->planeDef[0]) < dEpsilon && 
                    dFabs(normz - tri_test->planeDef[2]) < dEpsilon
                    )
                {
                    currPlane->addTriangle (tri_test);
                    tri_test->state = true;
                }
            }

            tri_base->state = true;
            if (isContactNumPointsLimited)
                currPlane->setMinMax();

            numPlanes++;
        }

        // sort planes
        if (isContactNumPointsLimited)
            sortPlanes(numPlanes);

#if !defined(NO_CONTACT_CULLING_BY_ISONHEIGHTFIELD2)
		/*
			Note by Oleh_Derevenko:
			It seems to be incorrect to limit contact count by some particular value
			since some of them (and even all of them) may be culled in following condition.
			However I do not see an easy way to fix this.
			If not that culling the flags modification should be changed here and
			additionally repeated after some contacts have been generated (in "if (didCollide)").
			The maximum of contacts in flags would then be set to minimum of contacts
			remaining and HEIGHTFIELDMAXCONTACTPERCELL.
		*/
		int planeTestFlags = (flags & ~NUMC_MASK) | HEIGHTFIELDMAXCONTACTPERCELL;
		dIASSERT((HEIGHTFIELDMAXCONTACTPERCELL & ~NUMC_MASK) == 0);
#else // if defined(NO_CONTACT_CULLING_BY_ISONHEIGHTFIELD2)
		int numMaxContactsPerPlane = dMIN(numMaxContactsPossible - numTerrainContacts, HEIGHTFIELDMAXCONTACTPERCELL);
		int planeTestFlags = (flags & ~NUMC_MASK) | numMaxContactsPerPlane;
		dIASSERT((HEIGHTFIELDMAXCONTACTPERCELL & ~NUMC_MASK) == 0);
#endif        
        
		for (unsigned int k = 0; k < numPlanes; k++)
        {
            HeightFieldPlane * const itPlane = tempPlaneBuffer[k];

            //set Geom
            dGeomPlaneSetNoNormalize (sliding_plane,  itPlane->planeDef);
            //dGeomPlaneSetParams (sliding_plane, triangle_Plane[0], triangle_Plane[1], triangle_Plane[2], triangle_Plane[3]);
            // find collision and compute contact points
            bool didCollide = false;
			const int numPlaneContacts = geomNPlaneCollider (o2, sliding_plane, planeTestFlags, PlaneContact, sizeof(dContactGeom));
			const size_t planeTriListSize = itPlane->trianglelistCurrentSize;
            for (i = 0; i < numPlaneContacts; i++)
            {
                dContactGeom *planeCurrContact = PlaneContact + i;
                // Check if contact point found in plane is inside Triangle.
                const dVector3 &pCPos = planeCurrContact->pos;
                for (size_t b = 0; planeTriListSize > b; b++)
                {  
                    if (m_p_data->IsOnHeightfield2 (itPlane->trianglelist[b]->vertices[0], 
                                                    pCPos, 
                                                    itPlane->trianglelist[b]->isUp))
                    {
						pContact = CONTACT(contact, numTerrainContacts*skip);
						dVector3Copy(pCPos, pContact->pos);
						dOPESIGN(pContact->normal, =, -, itPlane->planeDef);
						pContact->depth = planeCurrContact->depth;
                        pContact->side1 = planeCurrContact->side1;
                        pContact->side2 = planeCurrContact->side2;
						numTerrainContacts++;
						if ( numTerrainContacts == numMaxContactsPossible )
							return numTerrainContacts;

						didCollide = true;
						break;
					}
				}
            }
            if (didCollide)
            {
#if defined(NO_CONTACT_CULLING_BY_ISONHEIGHTFIELD2)
				/* Note by Oleh_Derevenko:
					This code is not used - see another note above
				*/
				numMaxContactsPerPlane = dMIN(numMaxContactsPossible - numTerrainContacts, HEIGHTFIELDMAXCONTACTPERCELL);
		        planeTestFlags = (flags & ~NUMC_MASK) | numMaxContactsPerPlane;
		        dIASSERT((HEIGHTFIELDMAXCONTACTPERCELL & ~NUMC_MASK) == 0);
#endif        
                for (size_t b = 0; planeTriListSize > b; b++)
                {                      
                    // flag Triangles Vertices as collided 
                    // to prevent any collision test of those
                    for (i = 0; i < 3; i++)
                        itPlane->trianglelist[b]->vertices[i]->state = true;
                }
            }
            else 
            {
                // flag triangle as not collided so that Vertices or Edge
                // of that triangles will be checked.
                for (size_t b = 0; planeTriListSize > b; b++)
                { 
                    itPlane->trianglelist[b]->state = false;
                }
            }
        }
    }
    

   
    // pass2: VS triangle vertices
    if (needFurtherPasses)
    {
        dxRay tempRay(0, 1); 
        dReal depth;
        bool vertexCollided;

		// Only one contact is necessary for ray test
		int rayTestFlags = (flags & ~NUMC_MASK) | 1;
		dIASSERT((1 & ~NUMC_MASK) == 0);
        //
        // Find Contact Penetration Depth of each vertices
        //
        for (unsigned int k = 0; k < numTri; k++)
        {
            const HeightFieldTriangle * const itTriangle = &tempTriangleBuffer[k];
            if (itTriangle->state == true)
                continue;// plane triangle did already collide.

            for (size_t i = 0; i < 3; i++)
            {
                HeightFieldVertex *vertex = itTriangle->vertices[i];
                if (vertex->state == true)
                    continue;// vertice did already collide.

                vertexCollided = false;
                const dVector3 &triVertex = vertex->vertex;
                if ( geomNDepthGetter )
                {
                    depth = geomNDepthGetter( o2,
                        triVertex[0], triVertex[1], triVertex[2] );
                    if (depth > dEpsilon)
                        vertexCollided = true;
                }
                else
                {
                    // We don't have a GetDepth function, so do a ray cast instead.
                    // NOTE: This isn't ideal, and a GetDepth function should be
                    // written for all geom classes.
                    tempRay.length = (minO2Height - triVertex[1]) * REAL(1000.0);

                    //dGeomRaySet( &tempRay, pContact->pos[0], pContact->pos[1], pContact->pos[2],
                    //    - itTriangle->Normal[0], - itTriangle->Normal[1], - itTriangle->Normal[2] );
                    dGeomRaySetNoNormalize(tempRay, triVertex, itTriangle->planeDef);

                    if ( geomRayNCollider( &tempRay, o2, rayTestFlags, PlaneContact, sizeof( dContactGeom ) ) )
                    {
                        depth = PlaneContact[0].depth;
                        vertexCollided = true;
                    }
                }
                if (vertexCollided)
                {
                    pContact = CONTACT(contact, numTerrainContacts*skip);
                    //create contact using vertices
                    dVector3Copy (triVertex, pContact->pos);
                    //create contact using Plane Normal
                    dOPESIGN(pContact->normal, =, -, itTriangle->planeDef);

                    pContact->depth = depth;
                    pContact->side1 = -1;
                    pContact->side2 = -1;

                    numTerrainContacts++;
                    if ( numTerrainContacts == numMaxContactsPossible ) 
                        return numTerrainContacts;

                    vertex->state = true;
                }
            }
        }
    }

#ifdef _HEIGHTFIELDEDGECOLLIDING
    // pass3: VS triangle Edges
    if (needFurtherPasses)
    {
        dVector3 Edge;
        dxRay edgeRay(0, 1);

		int numMaxContactsPerTri = dMIN(numMaxContactsPossible - numTerrainContacts, HEIGHTFIELDMAXCONTACTPERCELL);
		int triTestFlags = (flags & ~NUMC_MASK) | numMaxContactsPerTri;
		dIASSERT((HEIGHTFIELDMAXCONTACTPERCELL & ~NUMC_MASK) == 0);

        for (unsigned int k = 0; k < numTri; k++)
        {
            const HeightFieldTriangle * const itTriangle = &tempTriangleBuffer[k];

            if (itTriangle->state == true)
                continue;// plane did already collide.

            for (size_t m = 0; m < 3; m++)
            {
                const size_t next = (m + 1) % 3;
                HeightFieldVertex *vertex0 = itTriangle->vertices[m];
                HeightFieldVertex *vertex1 = itTriangle->vertices[next];

                // not concave or under the AABB 
                // nor triangle already collided against vertices
                if (vertex0->state == true && vertex1->state == true)
                    continue;// plane did already collide.
               
                dVector3Subtract(vertex1->vertex, vertex0->vertex, Edge);
                edgeRay.length = dVector3Length (Edge);
                dGeomRaySetNoNormalize(edgeRay, vertex1->vertex, Edge);
				int prevTerrainContacts = numTerrainContacts;
				pContact = CONTACT(contact, prevTerrainContacts*skip);
                const int numCollision = geomRayNCollider(&edgeRay,o2,triTestFlags,pContact,skip);
				dIASSERT(numCollision <= numMaxContactsPerTri);
				
				if (numCollision)
				{
					numTerrainContacts += numCollision;

					do
					{
						pContact = CONTACT(contact, prevTerrainContacts*skip);

						//create contact using Plane Normal
						dOPESIGN(pContact->normal, =, -, itTriangle->planeDef);

						pContact->depth = DistancePointToLine(pContact->pos, vertex1->vertex, Edge, edgeRay.length);
					}
					while (++prevTerrainContacts != numTerrainContacts);

					if ( numTerrainContacts == numMaxContactsPossible )
						return numTerrainContacts;

					numMaxContactsPerTri = dMIN(numMaxContactsPossible - numTerrainContacts, HEIGHTFIELDMAXCONTACTPERCELL);
					triTestFlags = (flags & ~NUMC_MASK) | numMaxContactsPerTri;
					dIASSERT((HEIGHTFIELDMAXCONTACTPERCELL & ~NUMC_MASK) == 0);
				}
            }

            itTriangle->vertices[0]->state = true;
            itTriangle->vertices[1]->state = true;
            itTriangle->vertices[2]->state = true;
        }
    }
#endif // _HEIGHTFIELDEDGECOLLIDING
    return numTerrainContacts;
}

int dCollideHeightfield( dxGeom *o1, dxGeom *o2, int flags, dContactGeom* contact, int skip )
{
    dIASSERT( skip >= (int)sizeof(dContactGeom) );
    dIASSERT( o1->type == dHeightfieldClass );
    dIASSERT((flags & NUMC_MASK) >= 1);

    int i;

    // if ((flags & NUMC_MASK) == 0) -- An assertion check is made on entry
	//	{ flags = (flags & ~NUMC_MASK) | 1; dIASSERT((1 & ~NUMC_MASK) == 0); }

    int numMaxTerrainContacts = (flags & NUMC_MASK);

    dxHeightfield *terrain = (dxHeightfield*) o1;

    dVector3 posbak;
    dMatrix3 Rbak;
    dReal aabbbak[6];
    int gflagsbak;
    dVector3 pos0,pos1;
    dMatrix3 R1;

    int numTerrainContacts = 0;
    int numTerrainOrigContacts = 0;

    //@@ Should find a way to set reComputeAABB to false in default case
    // aka DHEIGHTFIELD_CORNER_ORIGIN not defined and terrain not PLACEABLE
    // so that we can free some memory and speed up things a bit
    // while saving some precision loss 
#ifndef DHEIGHTFIELD_CORNER_ORIGIN
    const bool reComputeAABB = true;
#else
    const bool reComputeAABB = ( terrain->gflags & GEOM_PLACEABLE ) ? true : false;
#endif //DHEIGHTFIELD_CORNER_ORIGIN

    //
    // Transform O2 into Heightfield Space
    //
    if (reComputeAABB)
    {
        // Backup original o2 position, rotation and AABB.
        dVector3Copy( o2->final_posr->pos, posbak );
        dMatrix3Copy( o2->final_posr->R, Rbak );
        memcpy( aabbbak, o2->aabb, sizeof( dReal ) * 6 );
        gflagsbak = o2->gflags;
    }

    if ( terrain->gflags & GEOM_PLACEABLE )
    {
        // Transform o2 into heightfield space.
        dSubtractVectors3( pos0, o2->final_posr->pos, terrain->final_posr->pos );
        dMultiply1_331( pos1, terrain->final_posr->R, pos0 );
        dMultiply1_333( R1, terrain->final_posr->R, o2->final_posr->R );

        // Update o2 with transformed position and rotation.
        dVector3Copy( pos1, o2->final_posr->pos );
        dMatrix3Copy( R1, o2->final_posr->R );
    }

#ifndef DHEIGHTFIELD_CORNER_ORIGIN
    o2->final_posr->pos[ 0 ] += terrain->m_p_data->m_fHalfWidth;
    o2->final_posr->pos[ 2 ] += terrain->m_p_data->m_fHalfDepth;
#endif // DHEIGHTFIELD_CORNER_ORIGIN

    // Rebuild AABB for O2
    if (reComputeAABB)
        o2->computeAABB();

    //
    // Collide
    //

    //check if inside boundaries
    // using O2 aabb
    //  aabb[6] is (minx, maxx, miny, maxy, minz, maxz) 
    const bool wrapped = terrain->m_p_data->m_bWrapMode != 0;

    if ( !wrapped )
    {
        if (    o2->aabb[0] > terrain->m_p_data->m_fWidth //MinX
            ||  o2->aabb[4] > terrain->m_p_data->m_fDepth)//MinZ
            goto dCollideHeightfieldExit;

        if (    o2->aabb[1] < 0 //MaxX
            ||  o2->aabb[5] < 0)//MaxZ
            goto dCollideHeightfieldExit;
    }

	{ // To narrow scope of following variables
		const dReal fInvSampleWidth = terrain->m_p_data->m_fInvSampleWidth;
		int nMinX = (int)dFloor(dNextAfter(o2->aabb[0] * fInvSampleWidth, -dInfinity));
		int nMaxX = (int)dCeil(dNextAfter(o2->aabb[1] * fInvSampleWidth, dInfinity));
		const dReal fInvSampleDepth = terrain->m_p_data->m_fInvSampleDepth;
		int nMinZ = (int)dFloor(dNextAfter(o2->aabb[4] * fInvSampleDepth, -dInfinity));
		int nMaxZ = (int)dCeil(dNextAfter(o2->aabb[5] * fInvSampleDepth, dInfinity));

		if ( !wrapped )
		{
			nMinX = dMAX( nMinX, 0 );
			nMaxX = dMIN( nMaxX, terrain->m_p_data->m_nWidthSamples - 1 );
			nMinZ = dMAX( nMinZ, 0 );
			nMaxZ = dMIN( nMaxZ, terrain->m_p_data->m_nDepthSamples - 1 );

			dIASSERT ((nMinX < nMaxX) && (nMinZ < nMaxZ));
		}

		numTerrainOrigContacts = numTerrainContacts;
		numTerrainContacts += terrain->dCollideHeightfieldZone(
			nMinX,nMaxX,nMinZ,nMaxZ,o2,numMaxTerrainContacts - numTerrainContacts,
			flags,CONTACT(contact,numTerrainContacts*skip),skip	);
		dIASSERT( numTerrainContacts <= numMaxTerrainContacts );
	}

    dContactGeom *pContact;
    for ( i = numTerrainOrigContacts; i != numTerrainContacts; ++i )
    {
        pContact = CONTACT(contact,i*skip);
        pContact->g1 = o1;
        pContact->g2 = o2;
		// pContact->side1 = -1; -- Oleh_Derevenko: sides must not be erased here as they are set by respective colliders during ray/plane tests 
		// pContact->side2 = -1;
    }


    //------------------------------------------------------------------------------

dCollideHeightfieldExit:

    if (reComputeAABB)
    {
        // Restore o2 position, rotation and AABB
        dVector3Copy( posbak, o2->final_posr->pos );
        dMatrix3Copy( Rbak, o2->final_posr->R );
        memcpy( o2->aabb, aabbbak, sizeof(dReal)*6 );
        o2->gflags = gflagsbak;

        //
        // Transform Contacts to World Space
        //
        if ( terrain->gflags & GEOM_PLACEABLE )
        {
            for ( i = 0; i < numTerrainContacts; ++i )
            {
                pContact = CONTACT(contact,i*skip);
                dCopyVector3( pos0, pContact->pos );

#ifndef DHEIGHTFIELD_CORNER_ORIGIN
                pos0[ 0 ] -= terrain->m_p_data->m_fHalfWidth;
                pos0[ 2 ] -= terrain->m_p_data->m_fHalfDepth;
#endif // !DHEIGHTFIELD_CORNER_ORIGIN

                dMultiply0_331( pContact->pos, terrain->final_posr->R, pos0 );

                dAddVectors3( pContact->pos, pContact->pos, terrain->final_posr->pos );
                dCopyVector3( pos0, pContact->normal );

                dMultiply0_331( pContact->normal, terrain->final_posr->R, pos0 );
            }
        }
#ifndef DHEIGHTFIELD_CORNER_ORIGIN
        else
        {
            for ( i = 0; i < numTerrainContacts; ++i )
            {
                pContact = CONTACT(contact,i*skip);
                pContact->pos[ 0 ] -= terrain->m_p_data->m_fHalfWidth;
                pContact->pos[ 2 ] -= terrain->m_p_data->m_fHalfDepth;
            }
        }
#endif // !DHEIGHTFIELD_CORNER_ORIGIN
    }
    // Return contact count.
    return numTerrainContacts;
}



