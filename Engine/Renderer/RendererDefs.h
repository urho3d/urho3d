//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#ifndef RENDERER_RENDERERDEFS_H
#define RENDERER_RENDERERDEFS_H

//! Rendering mode
enum RenderMode
{
    RENDER_DEFERRED = 0,
    RENDER_PREPASS,
    RENDER_FORWARD
};

//! Primitive type
enum PrimitiveType
{
    TRIANGLE_LIST = 0,
    LINE_LIST
};

//! Blending mode
enum BlendMode
{
    BLEND_REPLACE = 0,
    BLEND_ADD,
    BLEND_MULTIPLY,
    BLEND_ALPHA,
    BLEND_ADDALPHA,
    BLEND_PREMULALPHA,
    BLEND_INVDESTALPHA,
    MAX_BLENDMODES
};

//! Depth or stencil compare mode
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

//! Culling mode
enum CullMode
{
    CULL_NONE = 0,
    CULL_CCW,
    CULL_CW,
    MAX_CULLMODES
};

//! Fill mode
enum FillMode
{
    FILL_SOLID = 0,
    FILL_WIREFRAME
};

//! Stencil operation
enum StencilOp
{
    OP_KEEP = 0,
    OP_ZERO,
    OP_REF,
    OP_INCR,
    OP_DECR
};

//! Buffer lock mode
enum LockMode
{
    LOCK_NORMAL,
    LOCK_DISCARD,
    LOCK_NOOVERWRITE,
    LOCK_READONLY
};

//! Vertex elements
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
    ELEMENT_INSTANCENUMBER
};

//! Texture filtering mode
enum TextureFilterMode
{
    FILTER_NEAREST = 0,
    FILTER_BILINEAR,
    FILTER_TRILINEAR,
    FILTER_ANISOTROPIC,
    FILTER_DEFAULT,
    MAX_FILTERMODES
};

//! Texture addressing mode
enum TextureAddressMode
{
    ADDRESS_WRAP = 0,
    ADDRESS_MIRROR,
    ADDRESS_CLAMP,
    ADDRESS_BORDER,
    MAX_ADDRESSMODES
};

//! Texture coordinates
enum TextureCoordinate
{
    COORD_U = 0,
    COORD_V,
    COORD_W,
    MAX_COORDS
};

//! Rendering passes
enum PassType
{
    PASS_DEFERRED = 0,
    PASS_PREPASS,
    PASS_MATERIAL,
    PASS_EMISSIVE,
    PASS_POSTOPAQUE,
    PASS_AMBIENT,
    PASS_NEGATIVE,
    PASS_LIGHT,
    PASS_SHADOW,
    MAX_PASSES
};

//! Instancing mode
enum InstancingMode
{
    SHADER_INSTANCING = 0,
    HARDWARE_INSTANCING,
};

//! Cube map faces
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

static const int QUALITY_LOW = 0;
static const int QUALITY_MEDIUM = 1;
static const int QUALITY_HIGH = 2;
static const int QUALITY_MAX = 15;

static const unsigned CLEAR_COLOR = 1;
static const unsigned CLEAR_DEPTH = 2;
static const unsigned CLEAR_STENCIL = 4;

static const unsigned MAX_RENDERTARGETS = 4;
static const unsigned MAX_TEXTURE_UNITS = 8;
static const unsigned MAX_VERTEX_STREAMS = 4;
static const unsigned MAX_VERTEX_ELEMENTS = 14;
static const unsigned MAX_SKIN_MATRICES = 64;
static const unsigned MAX_INSTANCES_PER_BATCH = 32;

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
static const unsigned MASK_INSTANCENUMBER = 0x400;
static const unsigned MASK_INSTANCEMATRIX1 = 0x800;
static const unsigned MASK_INSTANCEMATRIX2 = 0x1000;
static const unsigned MASK_INSTANCEMATRIX3 = 0x2000;
static const unsigned MASK_DEFAULT = 0xffffffff;
static const unsigned NO_ELEMENT = 0xffffffff;

static const float ANIMATION_LOD_BASESCALE = 2500.0f;

static const unsigned MAX_VERTEX_LIGHTS = 4;

static const unsigned MAX_CONSTANT_REGISTERS = 256;

#endif // RENDERER_RENDERERDEFS_H
