// dHeightfield Collider
//  Martijn Buijs 2006 http://home.planet.nl/~buijs512/
// Based on Terrain & Cone contrib by:
//  Benoit CHAPEROT 2003-2004 http://www.jstarlab.com

#ifndef _DHEIGHTFIELD_H_
#define _DHEIGHTFIELD_H_
//------------------------------------------------------------------------------

#include <ode/common.h>
#include "collision_kernel.h"


#define HEIGHTFIELDMAXCONTACTPERCELL 10


class HeightFieldVertex;
class HeightFieldEdge;
class HeightFieldTriangle;

//
// dxHeightfieldData
//
// Heightfield Data structure
//
struct dxHeightfieldData
{
    dReal m_fWidth;				// World space heightfield dimension on X axis
    dReal m_fDepth;				// World space heightfield dimension on Z axis
    dReal m_fSampleWidth;		// Vertex spacing on X axis edge (== m_vWidth / (m_nWidthSamples-1))
    dReal m_fSampleDepth;		// Vertex spacing on Z axis edge (== m_vDepth / (m_nDepthSamples-1))
    dReal m_fSampleZXAspect;    // Relation of Z axis spacing to X axis spacing (== m_fSampleDepth / m_fSampleWidth)
    dReal m_fInvSampleWidth;		// Cache of inverse Vertex count on X axis edge (== m_vWidth / (m_nWidthSamples-1))
    dReal m_fInvSampleDepth;		// Cache of inverse Vertex count on Z axis edge (== m_vDepth / (m_nDepthSamples-1))

    dReal m_fHalfWidth;			// Cache of half of m_fWidth
    dReal m_fHalfDepth;			// Cache of half of m_fDepth

    dReal m_fMinHeight;        // Min sample height value (scaled and offset)
    dReal m_fMaxHeight;        // Max sample height value (scaled and offset)
    dReal m_fThickness;        // Surface thickness (added to bottom AABB)
    dReal m_fScale;            // Sample value multiplier
    dReal m_fOffset;           // Vertical sample offset

    int	m_nWidthSamples;       // Vertex count on X axis edge (number of samples)
    int	m_nDepthSamples;       // Vertex count on Z axis edge (number of samples)
    int m_bCopyHeightData;     // Do we own the sample data?
    int	m_bWrapMode;           // Heightfield wrapping mode (0=finite, 1=infinite)
    int m_nGetHeightMode;      // GetHeight mode ( 0=callback, 1=byte, 2=short, 3=float )

    const void* m_pHeightData; // Sample data array
    void* m_pUserData;         // Callback user data

    dContactGeom            m_contacts[HEIGHTFIELDMAXCONTACTPERCELL];

    dHeightfieldGetHeight* m_pGetHeightCallback;		// Callback pointer.

    dxHeightfieldData();
    ~dxHeightfieldData();

    void SetData( int nWidthSamples, int nDepthSamples,
        dReal fWidth, dReal fDepth,
        dReal fScale, dReal fOffset,
        dReal fThickness, int bWrapMode );

    void ComputeHeightBounds();

    bool IsOnHeightfield2  ( const HeightFieldVertex * const CellCorner, 
        const dReal * const pos,  const bool isABC) const;

    dReal GetHeight(int x, int z);
    dReal GetHeight(dReal x, dReal z);

};

typedef int HeightFieldVertexCoords[2];

class HeightFieldVertex
{
public:
    HeightFieldVertex(){};

    dVector3 vertex;
    HeightFieldVertexCoords coords;
    bool state;
};

class HeightFieldEdge
{
public:
    HeightFieldEdge(){};

    HeightFieldVertex   *vertices[2];
};

class HeightFieldTriangle
{
public:
    HeightFieldTriangle(){};

    inline void setMinMax()
    {
        maxAAAB = vertices[0]->vertex[1] > vertices[1]->vertex[1] ? vertices[0]->vertex[1] : vertices[1]->vertex[1];
        maxAAAB = vertices[2]->vertex[1] > maxAAAB  ? vertices[2]->vertex[1] : maxAAAB;
    };

    HeightFieldVertex   *vertices[3];
    dReal               planeDef[4];
    dReal               maxAAAB;

    bool                isUp;
    bool                state;
};

class HeightFieldPlane
{
public:
    HeightFieldPlane():
      trianglelist(0),
      trianglelistReservedSize(0),
      trianglelistCurrentSize(0)
    {

    };
    ~HeightFieldPlane()
    {
        delete [] trianglelist;
    };

    inline void setMinMax()
    {
        const size_t asize = trianglelistCurrentSize;
        if (asize > 0)
        {  
            maxAAAB = trianglelist[0]->maxAAAB;
            for (size_t k = 1; asize > k; k++)
            {   
                if (trianglelist[k]->maxAAAB >  maxAAAB)
                    maxAAAB = trianglelist[k]->maxAAAB;
            }
        }
    };

    void resetTriangleListSize(const size_t newSize)
    {
        if (trianglelistReservedSize < newSize)
        {
            delete [] trianglelist;
            trianglelistReservedSize = newSize;
            trianglelist = new HeightFieldTriangle *[newSize];
        }
        trianglelistCurrentSize = 0;
    }

    void addTriangle(HeightFieldTriangle *tri)
    {
		dIASSERT(trianglelistCurrentSize < trianglelistReservedSize);

        trianglelist[trianglelistCurrentSize++] = tri;
    }

    HeightFieldTriangle **trianglelist;
    size_t              trianglelistReservedSize;
    size_t              trianglelistCurrentSize;

    dReal   maxAAAB;
    dReal   planeDef[4];
};

//
// dxHeightfield
//
// Heightfield geom structure
//
struct dxHeightfield : public dxGeom
{
    dxHeightfieldData* m_p_data;

    dxHeightfield( dSpaceID space, dHeightfieldDataID data, int bPlaceable );
    ~dxHeightfield();

    void computeAABB();

    int dCollideHeightfieldZone( const int minX, const int maxX, const int minZ, const int maxZ,  
        dxGeom *o2, const int numMaxContacts,
        int flags, dContactGeom *contact, int skip );

	enum
	{
		TEMP_PLANE_BUFFER_ELEMENT_COUNT_ALIGNMENT = 4,
		TEMP_HEIGHT_BUFFER_ELEMENT_COUNT_ALIGNMENT_X = 4,
		TEMP_HEIGHT_BUFFER_ELEMENT_COUNT_ALIGNMENT_Z = 4,
		TEMP_TRIANGLE_BUFFER_ELEMENT_COUNT_ALIGNMENT = 1, // Triangles are easy to reallocate and hard to predict
	};

	static inline size_t AlignBufferSize(size_t value, size_t alignment) { dIASSERT((alignment & (alignment - 1)) == 0); return (value + (alignment - 1)) & ~(alignment - 1); }

	void  allocateTriangleBuffer(size_t numTri);
	void  resetTriangleBuffer();
	void  allocatePlaneBuffer(size_t numTri);
	void  resetPlaneBuffer();
	void  allocateHeightBuffer(size_t numX, size_t numZ);
    void  resetHeightBuffer();

    void  sortPlanes(const size_t numPlanes);

    HeightFieldPlane    **tempPlaneBuffer;
    HeightFieldPlane    *tempPlaneInstances;
    size_t              tempPlaneBufferSize;

    HeightFieldTriangle *tempTriangleBuffer;
    size_t              tempTriangleBufferSize;

    HeightFieldVertex   **tempHeightBuffer;
	HeightFieldVertex   *tempHeightInstances;
    size_t              tempHeightBufferSizeX;
    size_t              tempHeightBufferSizeZ;

};


//------------------------------------------------------------------------------
#endif //_DHEIGHTFIELD_H_
