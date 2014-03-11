//
// Copyright (c) 2008-2014 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "HashBase.h"
#include "StringHash.h"

namespace Urho3D
{

class Vector3;

/// Primitive type.
enum PrimitiveType
{
    TRIANGLE_LIST = 0,
    LINE_LIST
};

/// %Geometry type.
enum GeometryType
{
    GEOM_STATIC = 0,
    GEOM_SKINNED = 1,
    GEOM_INSTANCED = 2,
    GEOM_BILLBOARD = 3,
    GEOM_STATIC_NOINSTANCING = 4,
    MAX_GEOMETRYTYPES = 4,
};

/// Blending mode.
enum BlendMode
{
    BLEND_REPLACE = 0,
    BLEND_ADD,
    BLEND_MULTIPLY,
    BLEND_ALPHA,
    BLEND_ADDALPHA,
    BLEND_PREMULALPHA,
    BLEND_INVDESTALPHA,
    BLEND_SUBTRACT,
    BLEND_SUBTRACTALPHA,
    MAX_BLENDMODES
};

/// Depth or stencil compare mode.
enum CompareMode
{
    CMP_ALWAYS = 0,
    CMP_EQUAL,
    CMP_NOTEQUAL,
    CMP_LESS,
    CMP_LESSEQUAL,
    CMP_GREATER,
    CMP_GREATEREQUAL,
    MAX_COMPAREMODES
};

/// Culling mode.
enum CullMode
{
    CULL_NONE = 0,
    CULL_CCW,
    CULL_CW,
    MAX_CULLMODES
};

/// Fill mode.
enum FillMode
{
    FILL_SOLID = 0,
    FILL_WIREFRAME,
    FILL_POINT
};

/// Stencil operation.
enum StencilOp
{
    OP_KEEP = 0,
    OP_ZERO,
    OP_REF,
    OP_INCR,
    OP_DECR
};

/// Vertex/index buffer lock state.
enum LockState
{
    LOCK_NONE = 0,
    LOCK_HARDWARE,
    LOCK_SHADOW,
    LOCK_SCRATCH
};

/// Vertex elements.
enum VertexElement
{
    ELEMENT_POSITION = 0,
    ELEMENT_NORMAL,
    ELEMENT_COLOR,
    ELEMENT_TEXCOORD1,
    ELEMENT_TEXCOORD2,
    ELEMENT_CUBETEXCOORD1,
    ELEMENT_CUBETEXCOORD2,
    ELEMENT_TANGENT,
    ELEMENT_BLENDWEIGHTS,
    ELEMENT_BLENDINDICES,
    ELEMENT_INSTANCEMATRIX1,
    ELEMENT_INSTANCEMATRIX2,
    ELEMENT_INSTANCEMATRIX3,
    MAX_VERTEX_ELEMENTS
};

/// Texture filtering mode.
enum TextureFilterMode
{
    FILTER_NEAREST = 0,
    FILTER_BILINEAR,
    FILTER_TRILINEAR,
    FILTER_ANISOTROPIC,
    FILTER_DEFAULT,
    MAX_FILTERMODES
};

/// Texture addressing mode.
enum TextureAddressMode
{
    ADDRESS_WRAP = 0,
    ADDRESS_MIRROR,
    ADDRESS_CLAMP,
    ADDRESS_BORDER,
    MAX_ADDRESSMODES
};

/// Texture coordinates.
enum TextureCoordinate
{
    COORD_U = 0,
    COORD_V,
    COORD_W,
    MAX_COORDS
};

/// Texture usage types.
enum TextureUsage
{
    TEXTURE_STATIC = 0,
    TEXTURE_DYNAMIC,
    TEXTURE_RENDERTARGET,
    TEXTURE_DEPTHSTENCIL
};

/// Cube map faces.
enum CubeMapFace
{
    FACE_POSITIVE_X = 0,
    FACE_NEGATIVE_X,
    FACE_POSITIVE_Y,
    FACE_NEGATIVE_Y,
    FACE_POSITIVE_Z,
    FACE_NEGATIVE_Z,
    MAX_CUBEMAP_FACES
};

/// Update mode for render surface viewports.
enum RenderSurfaceUpdateMode
{
    SURFACE_MANUALUPDATE = 0,
    SURFACE_UPDATEVISIBLE,
    SURFACE_UPDATEALWAYS
};

/// Shader types.
enum ShaderType
{
    VS = 0,
    PS,
};

// Inbuilt shader parameters.
extern StringHash VSP_AMBIENTSTARTCOLOR;
extern StringHash VSP_AMBIENTENDCOLOR;
extern StringHash VSP_BILLBOARDROT;
extern StringHash VSP_CAMERAPOS;
extern StringHash VSP_CAMERAROT;
extern StringHash VSP_NEARCLIP;
extern StringHash VSP_FARCLIP;
extern StringHash VSP_DEPTHMODE;
extern StringHash VSP_DELTATIME;
extern StringHash VSP_ELAPSEDTIME;
extern StringHash VSP_FRUSTUMSIZE;
extern StringHash VSP_GBUFFEROFFSETS;
extern StringHash VSP_LIGHTDIR;
extern StringHash VSP_LIGHTPOS;
extern StringHash VSP_MODEL;
extern StringHash VSP_VIEWPROJ;
extern StringHash VSP_UOFFSET;
extern StringHash VSP_VOFFSET;
extern StringHash VSP_ZONE;
extern StringHash VSP_LIGHTMATRICES;
extern StringHash VSP_SKINMATRICES;
extern StringHash VSP_VERTEXLIGHTS;
extern StringHash PSP_AMBIENTCOLOR;
extern StringHash PSP_DELTATIME;
extern StringHash PSP_ELAPSEDTIME;
extern StringHash PSP_FOGCOLOR;
extern StringHash PSP_FOGPARAMS;
extern StringHash PSP_GBUFFERINVSIZE;
extern StringHash PSP_LIGHTCOLOR;
extern StringHash PSP_LIGHTDIR;
extern StringHash PSP_LIGHTPOS;
extern StringHash PSP_MATDIFFCOLOR;
extern StringHash PSP_MATEMISSIVECOLOR;
extern StringHash PSP_MATENVMAPCOLOR;
extern StringHash PSP_MATSPECCOLOR;
extern StringHash PSP_NEARCLIP;
extern StringHash PSP_FARCLIP;
extern StringHash PSP_SHADOWCUBEADJUST;
extern StringHash PSP_SHADOWDEPTHFADE;
extern StringHash PSP_SHADOWINTENSITY;
extern StringHash PSP_SHADOWMAPINVSIZE;
extern StringHash PSP_SHADOWSPLITS;
extern StringHash PSP_LIGHTMATRICES;

// Inbuilt pass types
extern StringHash PASS_BASE;
extern StringHash PASS_LITBASE;
extern StringHash PASS_LIGHT;
extern StringHash PASS_ALPHA;
extern StringHash PASS_LITALPHA;
extern StringHash PASS_SHADOW;
extern StringHash PASS_DEFERRED;
extern StringHash PASS_PREPASS;
extern StringHash PASS_MATERIAL;
extern StringHash PASS_POSTOPAQUE;
extern StringHash PASS_REFRACT;
extern StringHash PASS_POSTALPHA;

// Scale calculation from bounding box diagonal.
extern Vector3 DOT_SCALE;

/// Texture units.
enum TextureUnit
{
    TU_DIFFUSE = 0,
    TU_ALBEDOBUFFER = 0,
    TU_NORMAL = 1,
    TU_NORMALBUFFER = 1,
    TU_SPECULAR = 2,
    TU_EMISSIVE = 3,
    TU_ENVIRONMENT = 4,
    MAX_MATERIAL_TEXTURE_UNITS = 5,
    TU_LIGHTRAMP = 5,
    TU_LIGHTSHAPE = 6,
    TU_SHADOWMAP = 7,
    TU_FACESELECT = 8,
    TU_INDIRECTION = 9,
    TU_DEPTHBUFFER = 10,
    TU_LIGHTBUFFER = 11,
    TU_VOLUMEMAP = 12,
    MAX_TEXTURE_UNITS = 13
};

/// Shader parameter groups for determining need to update.
enum ShaderParameterGroup
{
    SP_FRAME = 0,
    SP_CAMERA,
    SP_VIEWPORT,
    SP_ZONE,
    SP_LIGHT,
    SP_VERTEXLIGHTS,
    SP_MATERIAL,
    SP_OBJECTTRANSFORM,
    MAX_SHADER_PARAMETER_GROUPS
};

static const int QUALITY_LOW = 0;
static const int QUALITY_MEDIUM = 1;
static const int QUALITY_HIGH = 2;
static const int QUALITY_MAX = 15;

static const int SHADOWQUALITY_LOW_16BIT = 0;
static const int SHADOWQUALITY_LOW_24BIT = 1;
static const int SHADOWQUALITY_HIGH_16BIT = 2;
static const int SHADOWQUALITY_HIGH_24BIT = 3;

static const unsigned CLEAR_COLOR = 0x1;
static const unsigned CLEAR_DEPTH = 0x2;
static const unsigned CLEAR_STENCIL = 0x4;

static const unsigned MASK_NONE = 0x0;
static const unsigned MASK_POSITION = 0x1;
static const unsigned MASK_NORMAL = 0x2;
static const unsigned MASK_COLOR = 0x4;
static const unsigned MASK_TEXCOORD1 = 0x8;
static const unsigned MASK_TEXCOORD2 = 0x10;
static const unsigned MASK_CUBETEXCOORD1 = 0x20;
static const unsigned MASK_CUBETEXCOORD2 = 0x40;
static const unsigned MASK_TANGENT = 0x80;
static const unsigned MASK_BLENDWEIGHTS = 0x100;
static const unsigned MASK_BLENDINDICES = 0x200;
static const unsigned MASK_INSTANCEMATRIX1 = 0x400;
static const unsigned MASK_INSTANCEMATRIX2 = 0x800;
static const unsigned MASK_INSTANCEMATRIX3 = 0x1000;
static const unsigned MASK_DEFAULT = 0xffffffff;
static const unsigned NO_ELEMENT = 0xffffffff;

static const int MAX_RENDERTARGETS = 4;
static const int MAX_VERTEX_STREAMS = 4;
static const int MAX_SKIN_MATRICES = 64;
static const int MAX_CONSTANT_REGISTERS = 256;

static const int BITS_PER_COMPONENT = 8;
}
