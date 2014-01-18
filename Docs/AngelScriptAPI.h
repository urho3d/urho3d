// Script API header intended to be 'force included' in IDE for AngelScript content assist / code completion

#define int8 signed char
#define int16 signed short
#define int64 long
#define uint8 unsigned char
#define uint16 unsigned short
#define uint64 unsigned long
#define null 0

// Enumerations

enum Intersection
{
OUTSIDE,
INTERSECTS,
INSIDE,
};

enum VariantType
{
VAR_NONE,
VAR_INT,
VAR_BOOL,
VAR_FLOAT,
VAR_VECTOR2,
VAR_VECTOR3,
VAR_VECTOR4,
VAR_QUATERNION,
VAR_COLOR,
VAR_STRING,
VAR_BUFFER,
VAR_PTR,
VAR_RESOURCEREF,
VAR_RESOURCEREFLIST,
VAR_VARIANTVECTOR,
VAR_VARIANTMAP,
VAR_INTRECT,
VAR_INTVECTOR2,
};

enum FileMode
{
FILE_READ,
FILE_WRITE,
FILE_READWRITE,
};

enum CreateMode
{
REPLICATED,
LOCAL,
};

enum FillMode
{
FILL_SOLID,
FILL_WIREFRAME,
FILL_POINT,
};

enum RenderCommandType
{
CMD_NONE,
CMD_CLEAR,
CMD_SCENEPASS,
CMD_QUAD,
CMD_FORWARDLIGHTS,
CMD_LIGHTVOLUMES,
};

enum RenderCommandSortMode
{
SORT_FRONTTOBACK,
SORT_BACKTOFRONT,
};

enum RenderTargetSizeMode
{
SIZE_ABSOLUTE,
SIZE_RENDERTARGETDIVISOR,
SIZE_VIEWPORTDIVISOR,
};

enum TextureUnit
{
TU_DIFFUSE,
TU_NORMAL,
TU_SPECULAR,
TU_EMISSIVE,
TU_ENVIRONMENT,
TU_LIGHTRAMP,
TU_LIGHTSHAPE,
TU_SHADOWMAP,
TU_FACESELECT,
TU_INDIRECTION,
TU_ALBEDOBUFFER,
TU_NORMALBUFFER,
TU_DEPTHBUFFER,
TU_LIGHTBUFFER,
MAX_MATERIAL_TEXTURE_UNITS,
MAX_TEXTURE_UNITS,
};

enum TextureUsage
{
TEXTURE_STATIC,
TEXTURE_DYNAMIC,
TEXTURE_RENDERTARGET,
TEXTURE_DEPTHSTENCIL,
};

enum TextureFilterMode
{
FILTER_NEAREST,
FILTER_BILINEAR,
FILTER_TRILINEAR,
FILTER_ANISOTROPIC,
FILTER_DEFAULT,
};

enum TextureAddressMode
{
ADDRESS_WRAP,
ADDRESS_MIRROR,
ADDRESS_CLAMP,
ADDRESS_BORDER,
};

enum TextureCoordinate
{
COORD_U,
COORD_V,
COORD_W,
};

enum CubeMapFace
{
FACE_POSITIVE_X,
FACE_NEGATIVE_X,
FACE_POSITIVE_Y,
FACE_NEGATIVE_Y,
FACE_POSITIVE_Z,
FACE_NEGATIVE_Z,
};

enum RenderSurfaceUpdateMode
{
SURFACE_MANUALUPDATE,
SURFACE_UPDATEVISIBLE,
SURFACE_UPDATEALWAYS,
};

enum BlendMode
{
BLEND_REPLACE,
BLEND_ADD,
BLEND_MULTIPLY,
BLEND_ALPHA,
BLEND_ADDALPHA,
BLEND_PREMULALPHA,
BLEND_INVDESTALPHA,
};

enum CompareMode
{
CMP_ALWAYS,
CMP_EQUAL,
CMP_NOTEQUAL,
CMP_LESS,
CMP_LESSEQUAL,
CMP_GREATER,
CMP_GREATEREQUAL,
};

enum CullMode
{
CULL_NONE,
CULL_CCW,
CULL_CW,
};

enum PassLightingMode
{
LIGHTING_UNLIT,
LIGHTING_PERVERTEX,
LIGHTING_PERPIXEL,
};

enum LightType
{
LIGHT_DIRECTIONAL,
LIGHT_SPOT,
LIGHT_POINT,
};

enum EmitterType
{
EMITTER_SPHERE,
EMITTER_BOX,
};

enum PrimitiveType
{
TRIANGLE_LIST,
LINE_LIST,
};

enum RayQueryLevel
{
RAY_AABB_NOSUBOBJECTS,
RAY_AABB,
RAY_OBB,
RAY_TRIANGLE,
};

enum SoundType
{
SOUND_EFFECT,
SOUND_AMBIENT,
SOUND_VOICE,
SOUND_MUSIC,
SOUND_MASTER,
};

enum HorizontalAlignment
{
HA_LEFT,
HA_CENTER,
HA_RIGHT,
};

enum VerticalAlignment
{
VA_TOP,
VA_CENTER,
VA_BOTTOM,
};

enum Corner
{
C_TOPLEFT,
C_TOPRIGHT,
C_BOTTOMLEFT,
C_BOTTOMRIGHT,
};

enum Orientation
{
O_HORIZONTAL,
O_VERTICAL,
};

enum FocusMode
{
FM_NOTFOCUSABLE,
FM_RESETFOCUS,
FM_FOCUSABLE,
FM_FOCUSABLE_DEFOCUSABLE,
};

enum LayoutMode
{
LM_FREE,
LM_HORIZONTAL,
LM_VERTICAL,
};

enum TraversalMode
{
TM_BREADTH_FIRST,
TM_DEPTH_FIRST,
};

enum CursorShape
{
CS_NORMAL,
CS_RESIZEVERTICAL,
CS_RESIZEDIAGONAL_TOPRIGHT,
CS_RESIZEHORIZONTAL,
CS_RESIZEDIAGONAL_TOPLEFT,
CS_ACCEPTDROP,
CS_REJECTDROP,
CS_BUSY,
};

enum HighlightMode
{
HM_NEVER,
HM_FOCUS,
HM_ALWAYS,
};

enum TextEffect
{
TE_NONE,
TE_SHADOW,
TE_STROKE,
};

enum HttpRequestState
{
HTTP_INITIALIZING,
HTTP_ERROR,
HTTP_OPEN,
HTTP_CLOSED,
};

enum ShapeType
{
SHAPE_BOX,
SHAPE_SPHERE,
SHAPE_STATICPLANE,
SHAPE_CYLINDER,
SHAPE_CAPSULE,
SHAPE_CONE,
SHAPE_TRIANGLEMESH,
SHAPE_CONVEXHULL,
SHAPE_TERRAIN,
};

enum CollisionEventMode
{
COLLISION_NEVER,
COLLISION_ACTIVE,
COLLISION_ALWAYS,
};

enum ConstraintType
{
CONSTRAINT_POINT,
CONSTRAINT_HINGE,
CONSTRAINT_SLIDER,
CONSTRAINT_CONETWIST,
};

enum DumpMode
{
DOXYGEN,
C_HEADER,
};

// Classes

template <class T> class Array
{
// Methods:
void Insert(uint, const T&);
void Erase(uint);
void Push(const T&);
void Pop();
void Resize(uint);
void Clear();
void Sort();
void Sort(uint, uint);
void SortReverse();
void SortReverse(uint, uint);
void Reverse();
int Find(const T&) const;
int Find(uint, const T&) const;

// Properties:
uint length;
/* (readonly) */
bool empty;
};

class String
{
// Methods:
void Replace(uint8, uint8, bool = true);
void Replace(const String&, const String&, bool = true);
String Replaced(uint8, uint8, bool = true) const;
String Replaced(const String&, const String&, bool = true) const;
void Resize(uint);
uint Find(const String&, uint = 0, bool = true) const;
uint Find(uint8, uint = 0, bool = true) const;
uint FindLast(const String&, uint = 0xffffffff, bool = true) const;
uint FindLast(uint8, uint = 0xffffffff, bool = true) const;
bool StartsWith(const String&, bool = true) const;
bool EndsWith(const String&, bool = true) const;
String Substring(uint) const;
String Substring(uint, uint) const;
String ToUpper() const;
String ToLower() const;
String Trimmed() const;
void SetUTF8FromLatin1(const String&);
uint ByteOffsetUTF8(uint) const;
uint NextUTF8Char(uint&) const;
uint AtUTF8(uint) const;
void ReplaceUTF8(uint, uint);
void AppendUTF8(uint);
String SubstringUTF8(uint) const;
String SubstringUTF8(uint, uint) const;
int Compare(const String&, bool = true) const;
bool Contains(const String&, bool = true) const;
bool Contains(uint8, bool = true) const;
void Clear();
Array<String> Split(uint8) const;
void Join(Array<String>&, const String&);
bool ToBool() const;
float ToFloat() const;
int ToInt() const;
uint ToUInt() const;
Color ToColor() const;
IntRect ToIntRect() const;
IntVector2 ToIntVector2() const;
Quaternion ToQuaternion() const;
Vector2 ToVector2() const;
Vector3 ToVector3() const;
Vector4 ToVector4(bool = false) const;
Variant ToVectorVariant() const;

// Properties:
/* (readonly) */
uint utf8Length;
/* (readonly) */
uint length;
/* (readonly) */
bool empty;
};

class Dictionary
{
// Methods:
void Set(const String&, void*);
bool Get(const String&, void*) const;
void Set(const String&, int64&);
bool Get(const String&, int64&) const;
void Set(const String&, double&);
bool Get(const String&, double&) const;
bool Exists(const String&) const;
void Erase(const String&);
void Clear();

// Properties:
/* (readonly) */
bool empty;
/* (readonly) */
uint length;
/* (readonly) */
Array<String> keys;
};

class IntVector2
{
// Methods:
String ToString() const;

// Properties:
/* (readonly) */
Array<int> data;
int x;
int y;
};

class IntRect
{
// Methods:
Intersection IsInside(const IntVector2&) const;

// Properties:
/* (readonly) */
Array<int> data;
/* (readonly) */
IntVector2 size;
/* (readonly) */
int width;
/* (readonly) */
int height;
int left;
int top;
int right;
int bottom;
};

class Vector2
{
// Methods:
void Normalize();
float DotProduct(const Vector2&) const;
float AbsDotProduct(const Vector2&) const;
Vector2 Lerp(const Vector2&, float) const;
bool Equals(const Vector2&) const;
Vector2 Normalized() const;
String ToString() const;

// Properties:
/* (readonly) */
Array<float> data;
/* (readonly) */
float length;
/* (readonly) */
float lengthSquared;
float x;
float y;
};

class Vector3
{
// Methods:
void Normalize();
float DotProduct(const Vector3&) const;
float AbsDotProduct(const Vector3&) const;
Vector3 CrossProduct(const Vector3&) const;
Vector3 Lerp(const Vector3&, float) const;
bool Equals(const Vector3&) const;
Vector3 Normalized() const;
String ToString() const;

// Properties:
/* (readonly) */
Array<float> data;
/* (readonly) */
float length;
/* (readonly) */
float lengthSquared;
float x;
float y;
float z;
};

class Vector4
{
// Methods:
float DotProduct(const Vector4&) const;
float AbsDotProduct(const Vector4&) const;
Vector4 Lerp(const Vector4&, float) const;
bool Equals(const Vector4&) const;
String ToString() const;

// Properties:
/* (readonly) */
Array<float> data;
float x;
float y;
float z;
float w;
};

class Quaternion
{
// Methods:
void FromAngleAxis(float, const Vector3&);
void FromEulerAngles(float, float, float);
void FromRotationTo(const Vector3&, const Vector3&);
void FromAxes(const Vector3&, const Vector3&, const Vector3&);
void FromLookRotation(const Vector3&, const Vector3&);
void Normalize();
Quaternion Normalized() const;
Quaternion Inverse() const;
float DotProduct(const Quaternion&) const;
Quaternion Slerp(Quaternion, float) const;
Quaternion Nlerp(Quaternion, float, bool) const;
bool Equals(const Quaternion&) const;
String ToString() const;

// Properties:
/* (readonly) */
Vector3 eulerAngles;
/* (readonly) */
float yaw;
/* (readonly) */
float pitch;
/* (readonly) */
float roll;
float w;
float x;
float y;
float z;
};

class Matrix3
{
// Methods:
Vector3 Scale() const;
Matrix3 Scaled(const Vector3&) const;
void SetScale(const Vector3&);
void SetScale(float);
Matrix3 Transpose() const;
Matrix3 Inverse() const;
bool Equals(const Matrix3&) const;

// Properties:
float m00;
float m01;
float m02;
float m10;
float m11;
float m12;
float m20;
float m21;
float m22;
};

class Matrix4
{
// Methods:
Quaternion Rotation() const;
Matrix3 RotationMatrix() const;
Vector3 Scale() const;
void SetRotation(const Matrix3&);
void SetScale(const Vector3&);
void SetScale(float);
void SetTranslation(const Vector3&);
Matrix3 ToMatrix3() const;
Vector3 Translation() const;
Matrix4 Transpose() const;
void Decompose(Vector3&, Quaternion&, Vector3&) const;
Matrix4 Inverse() const;
bool Equals(const Matrix4&) const;

// Properties:
float m00;
float m01;
float m02;
float m03;
float m10;
float m11;
float m12;
float m13;
float m20;
float m21;
float m22;
float m23;
float m30;
float m31;
float m32;
float m33;
};

class Matrix3x4
{
// Methods:
Quaternion Rotation() const;
Matrix3 RotationMatrix() const;
Vector3 Scale() const;
void SetRotation(const Matrix3&);
void SetScale(const Vector3&);
void SetScale(float);
void SetTranslation(const Vector3&);
Matrix3 ToMatrix3() const;
Matrix4 ToMatrix4() const;
Vector3 Translation() const;
void Decompose(Vector3&, Quaternion&, Vector3&) const;
Matrix3x4 Inverse() const;
bool Equals(const Matrix3x4&) const;

// Properties:
float m00;
float m01;
float m02;
float m03;
float m10;
float m11;
float m12;
float m13;
float m20;
float m21;
float m22;
float m23;
};

class Rect
{
// Methods:
void Define(const Vector2&, const Vector2&);
void Define(const Vector2&);
void Merge(const Vector2&);
void Merge(const Rect&);
void Clip(const Rect&);
void Clear();
bool Equals(const Rect&) const;
Intersection IsInside(const Vector2&) const;
Vector4 ToVector4() const;

// Properties:
/* (readonly) */
Vector2 center;
/* (readonly) */
Vector2 size;
/* (readonly) */
Vector2 halfSize;
Vector2 min;
Vector2 max;
float left;
float top;
float right;
float bottom;
bool defined;
};

class BoundingBox
{
// Methods:
void Define(const Vector3&, const Vector3&);
void Define(float, float);
void Define(const Vector3&);
void Define(const BoundingBox&);
void Define(const Frustum&);
void Define(const Polyhedron&);
void Define(const Sphere&);
void Merge(const Vector3&);
void Merge(const BoundingBox&);
void Merge(const Frustum&);
void Merge(const Polyhedron&);
void Merge(const Sphere&);
void Clip(const BoundingBox&);
void Clear();
void Transform(const Matrix3&);
void Transform(const Matrix3x4&);
Intersection IsInside(const Vector3&) const;
Intersection IsInside(const Sphere&) const;
Intersection IsInside(const BoundingBox&) const;
BoundingBox Transformed(const Matrix3&) const;
BoundingBox Transformed(const Matrix3x4&) const;
Rect Projected(const Matrix4&) const;
String ToString() const;

// Properties:
/* (readonly) */
Vector3 center;
/* (readonly) */
Vector3 size;
/* (readonly) */
Vector3 halfSize;
Vector3 min;
Vector3 max;
bool defined;
};

class Frustum
{
// Methods:
void Define(float, float, float, float, float, const Matrix3x4&);
void Define(const Vector3&, const Vector3&, const Matrix3x4&);
void Define(const BoundingBox&, const Matrix3x4&);
void DefineOrtho(float, float, float, float, float, const Matrix3x4&);
void Transform(const Matrix3&);
void Transform(const Matrix3x4&);
Intersection IsInside(const Vector3&);
Intersection IsInside(const BoundingBox&);
Intersection IsInside(const Sphere&);
float Distance(const Vector3&) const;
Frustum Transformed(const Matrix3&) const;
Frustum Transformed(const Matrix3x4&) const;

// Properties:
/* (readonly) */
Array<Vector3> vertices;
};

class Polyhedron
{
// Methods:
void AddFace(const Vector3&, const Vector3&, const Vector3&);
void AddFace(const Vector3&, const Vector3&, const Vector3&, const Vector3&);
void AddFace(const Array<Vector3>);
void Define(const BoundingBox&);
void Define(const Frustum&);
void Clip(const BoundingBox&);
void Clip(const Frustum&);
void Clear();
void Transform(const Matrix3&);
void Transform(const Matrix3x4&);
Polyhedron Transformed(const Matrix3&) const;
Polyhedron Transformed(const Matrix3x4&) const;

// Properties:
/* (readonly) */
uint numFaces;
/* (readonly) */
Array<Array<Vector3>> face;
};

class Sphere
{
// Methods:
void Define(const Vector3&, float);
void Define(const BoundingBox&);
void Define(const Frustum&);
void Define(const Polyhedron&);
void Define(const Sphere&);
void Merge(const Vector3&);
void Merge(const BoundingBox&);
void Merge(const Frustum&);
void Merge(const Sphere&);
void Clear();
Intersection IsInside(const Vector3&) const;
Intersection IsInside(const Sphere&) const;
Intersection IsInside(const BoundingBox&) const;
float Distance(const Vector3&) const;

// Properties:
Vector3 center;
float radius;
bool defined;
};

class Plane
{
// Methods:
void Define(const Vector3&, const Vector3&, const Vector3&);
void Define(const Vector3&, const Vector3&);
void Define(const Vector4&);
void Transform(const Matrix3&);
void Transform(const Matrix3x4&);
void Transform(const Matrix4&);
float Distance(const Vector3&) const;
Vector3 Reflect(const Vector3&) const;
Plane Transformed(const Matrix3&) const;
Plane Transformed(const Matrix3x4&) const;
Plane Transformed(const Matrix4&) const;
Vector4 ToVector4() const;

// Properties:
/* (readonly) */
Matrix3x4 reflectionMatrix;
Vector3 normal;
Vector3 absNormal;
float intercept;
};

class Ray
{
// Methods:
void Define(const Vector3&, const Vector3&);
Vector3 Project(const Vector3&) const;
float Distance(const Vector3&) const;
Vector3 ClosestPoint(const Ray&) const;
float HitDistance(const Sphere&) const;
float HitDistance(const BoundingBox&) const;
float HitDistance(const Frustum&, bool = true) const;
float HitDistance(const Vector3&, const Vector3&, const Vector3&) const;
Ray Transformed(const Matrix3x4&) const;

// Properties:
Vector3 origin;
Vector3 direction;
};

class Color
{
// Methods:
uint ToUInt() const;
Vector3 ToHSL() const;
Vector3 ToHSV() const;
void FromHSL(float, float, float, float);
void FromHSV(float, float, float, float);
float SumRGB() const;
float Average() const;
float Luma() const;
float Chroma() const;
float Hue() const;
float SaturationHSL() const;
float SaturationHSV() const;
float Value() const;
float Lightness() const;
float MaxRGB() const;
float MinRGB() const;
float Range() const;
void Clip(bool);
void Invert(bool);
Color Lerp(const Color&, float) const;
String ToString() const;

// Properties:
/* (readonly) */
Array<float> data;
/* (readonly) */
Vector3 rgb;
/* (readonly) */
Vector4 rgba;
float r;
float g;
float b;
float a;
};

class StringHash
{
// Methods:
String ToString() const;

// Properties:
/* (readonly) */
uint value;
};

class ShortStringHash
{
// Methods:
String ToString() const;

// Properties:
/* (readonly) */
uint16 value;
};

class ResourceRef
{

// Properties:
ShortStringHash type;
String name;
};

class ResourceRefList
{
// Methods:
void Resize(uint);

// Properties:
/* (readonly) */
uint length;
/* (readonly) */
bool empty;
Array<String> names;
ShortStringHash type;
};

class Variant
{
// Methods:
void Clear();
int GetInt() const;
uint GetUInt() const;
StringHash GetStringHash() const;
ShortStringHash GetShortStringHash() const;
bool GetBool() const;
float GetFloat() const;
const Vector2& GetVector2() const;
const Vector3& GetVector3() const;
const Vector4& GetVector4() const;
const Quaternion& GetQuaternion() const;
const Color& GetColor() const;
const String& GetString() const;
const ResourceRef& GetResourceRef() const;
const ResourceRefList& GetResourceRefList() const;
Array<Variant> GetVariantVector() const;
const VariantMap& GetVariantMap() const;
const IntRect& GetIntRect() const;
const IntVector2& GetIntVector2() const;
void FromString(const String&, const String&);
void FromString(VariantType, const String&);
String ToString() const;
VectorBuffer GetBuffer() const;
Serializable GetSerializable() const;
Node GetNode() const;
Component GetComponent() const;
Scene GetScene() const;
Camera GetCamera() const;
RenderSurface GetRenderSurface() const;
Texture GetTexture() const;
UIElement GetUIElement() const;
Connection GetConnection() const;
CollisionShape GetCollisionShape() const;
RigidBody GetRigidBody() const;
PhysicsWorld GetPhysicsWorld() const;

// Properties:
/* (readonly) */
bool zero;
/* (readonly) */
bool empty;
/* (readonly) */
VariantType type;
/* (readonly) */
String typeName;
};

class VariantMap
{
// Methods:
bool Contains(const String&) const;
bool Erase(const String&);
bool Contains(ShortStringHash) const;
bool Erase(ShortStringHash);
void Clear();

// Properties:
/* (readonly) */
uint length;
/* (readonly) */
Array<ShortStringHash> keys;
};

class AttributeInfo
{

// Properties:
/* (readonly) */
Array<String> enumNames;
VariantType type;
String name;
Variant defaultValue;
uint mode;
};

class RefCounted
{

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
};

class Object
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
};

class WeakHandle
{
// Methods:
RefCounted Get() const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
bool expired;
};

class Timer
{
// Methods:
uint GetMSec(bool);
void Reset();
};

class Time
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint frameNumber;
/* (readonly) */
float timeStep;
/* (readonly) */
float elapsedTime;
/* (readonly) */
uint systemTime;
/* (readonly) */
String timeStamp;
};

class Log
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void Open(const String&);
void Close();
void Write(const String&, bool = false);
void Debug(const String&);
void Info(const String&);
void Warning(const String&);
void Error(const String&);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
int level;
bool timeStamp;
/* (readonly) */
String lastMessage;
bool quiet;
};

class Serializer
{
// Methods:
uint Write(Array<uint8>);
bool WriteInt(int);
bool WriteShort(int16);
bool WriteByte(int8);
bool WriteUInt(uint);
bool WriteUShort(uint16);
bool WriteUByte(uint8);
bool WriteBool(bool);
bool WriteFloat(float);
bool WriteIntRect(const IntRect&);
bool WriteIntVector2(const IntVector2&);
bool WriteVector2(const Vector2&);
bool WriteVector3(const Vector3&);
bool WritePackedVector3(const Vector3&, float);
bool WriteVector4(const Vector4&);
bool WriteQuaternion(const Quaternion&);
bool WritePackedQuaternion(const Quaternion&);
bool WriteColor(const Color&);
bool WriteBoundingBox(const BoundingBox&);
bool WriteString(const String&);
bool WriteFileID(const String&);
bool WriteStringHash(const StringHash&);
bool WriteShortStringHash(const ShortStringHash&);
bool WriteVariant(const Variant&);
bool WriteVariantMap(const VariantMap&);
bool WriteVLE(uint);
bool WriteNetID(uint);
bool WriteLine(const String&);
};

class Deserializer
{
// Methods:
Array<uint8> Read(uint);
int ReadInt();
int16 ReadShort();
int8 ReadByte();
uint ReadUInt();
uint16 ReadUShort();
uint8 ReadUByte();
bool ReadBool();
float ReadFloat();
IntRect ReadIntRect();
IntVector2 ReadIntVector2();
Vector2 ReadVector2();
Vector3 ReadVector3();
Vector3 ReadPackedVector3(float);
Vector4 ReadVector4();
Quaternion ReadQuaternion();
Quaternion ReadPackedQuaternion();
Color ReadColor();
BoundingBox ReadBoundingBox();
String ReadString();
String ReadFileID();
StringHash ReadStringHash();
ShortStringHash ReadShortStringHash();
Variant ReadVariant();
VariantMap ReadVariantMap();
uint ReadVLE();
uint ReadNetID();
String ReadLine();
uint Seek(uint);

// Properties:
/* (readonly) */
String name;
/* (readonly) */
uint checksum;
/* (readonly) */
uint position;
/* (readonly) */
uint size;
/* (readonly) */
bool eof;
};

class File
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Open(const String&, FileMode = FILE_READ);
void Close();
uint Write(Array<uint8>);
bool WriteInt(int);
bool WriteShort(int16);
bool WriteByte(int8);
bool WriteUInt(uint);
bool WriteUShort(uint16);
bool WriteUByte(uint8);
bool WriteBool(bool);
bool WriteFloat(float);
bool WriteIntRect(const IntRect&);
bool WriteIntVector2(const IntVector2&);
bool WriteVector2(const Vector2&);
bool WriteVector3(const Vector3&);
bool WritePackedVector3(const Vector3&, float);
bool WriteVector4(const Vector4&);
bool WriteQuaternion(const Quaternion&);
bool WritePackedQuaternion(const Quaternion&);
bool WriteColor(const Color&);
bool WriteBoundingBox(const BoundingBox&);
bool WriteString(const String&);
bool WriteFileID(const String&);
bool WriteStringHash(const StringHash&);
bool WriteShortStringHash(const ShortStringHash&);
bool WriteVariant(const Variant&);
bool WriteVariantMap(const VariantMap&);
bool WriteVLE(uint);
bool WriteNetID(uint);
bool WriteLine(const String&);
Array<uint8> Read(uint);
int ReadInt();
int16 ReadShort();
int8 ReadByte();
uint ReadUInt();
uint16 ReadUShort();
uint8 ReadUByte();
bool ReadBool();
float ReadFloat();
IntRect ReadIntRect();
IntVector2 ReadIntVector2();
Vector2 ReadVector2();
Vector3 ReadVector3();
Vector3 ReadPackedVector3(float);
Vector4 ReadVector4();
Quaternion ReadQuaternion();
Quaternion ReadPackedQuaternion();
Color ReadColor();
BoundingBox ReadBoundingBox();
String ReadString();
String ReadFileID();
StringHash ReadStringHash();
ShortStringHash ReadShortStringHash();
Variant ReadVariant();
VariantMap ReadVariantMap();
uint ReadVLE();
uint ReadNetID();
String ReadLine();
uint Seek(uint);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
FileMode mode;
/* (readonly) */
bool open;
/* (readonly) */
bool packaged;
/* (readonly) */
String name;
/* (readonly) */
uint checksum;
/* (readonly) */
uint position;
/* (readonly) */
uint size;
/* (readonly) */
bool eof;
};

class VectorBuffer
{
// Methods:
void SetData(Deserializer, uint);
void Clear();
void Resize(uint);
uint Write(Array<uint8>);
bool WriteInt(int);
bool WriteShort(int16);
bool WriteByte(int8);
bool WriteUInt(uint);
bool WriteUShort(uint16);
bool WriteUByte(uint8);
bool WriteBool(bool);
bool WriteFloat(float);
bool WriteIntRect(const IntRect&);
bool WriteIntVector2(const IntVector2&);
bool WriteVector2(const Vector2&);
bool WriteVector3(const Vector3&);
bool WritePackedVector3(const Vector3&, float);
bool WriteVector4(const Vector4&);
bool WriteQuaternion(const Quaternion&);
bool WritePackedQuaternion(const Quaternion&);
bool WriteColor(const Color&);
bool WriteBoundingBox(const BoundingBox&);
bool WriteString(const String&);
bool WriteFileID(const String&);
bool WriteStringHash(const StringHash&);
bool WriteShortStringHash(const ShortStringHash&);
bool WriteVariant(const Variant&);
bool WriteVariantMap(const VariantMap&);
bool WriteVLE(uint);
bool WriteNetID(uint);
bool WriteLine(const String&);
Array<uint8> Read(uint);
int ReadInt();
int16 ReadShort();
int8 ReadByte();
uint ReadUInt();
uint16 ReadUShort();
uint8 ReadUByte();
bool ReadBool();
float ReadFloat();
IntRect ReadIntRect();
IntVector2 ReadIntVector2();
Vector2 ReadVector2();
Vector3 ReadVector3();
Vector3 ReadPackedVector3(float);
Vector4 ReadVector4();
Quaternion ReadQuaternion();
Quaternion ReadPackedQuaternion();
Color ReadColor();
BoundingBox ReadBoundingBox();
String ReadString();
String ReadFileID();
StringHash ReadStringHash();
ShortStringHash ReadShortStringHash();
Variant ReadVariant();
VariantMap ReadVariantMap();
uint ReadVLE();
uint ReadNetID();
String ReadLine();
uint Seek(uint);

// Properties:
/* (readonly) */
String name;
/* (readonly) */
uint checksum;
/* (readonly) */
uint position;
/* (readonly) */
uint size;
/* (readonly) */
bool eof;
};

class FileSystem
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool FileExists(const String&) const;
bool DirExists(const String&) const;
uint GetLastModifiedTime(const String&) const;
Array<String> ScanDir(const String&, const String&, uint, bool) const;
bool CreateDir(const String&);
int SystemCommand(const String&);
int SystemRun(const String&, Array<String>);
bool SystemOpen(const String&, const String&);
bool Copy(const String&, const String&);
bool Rename(const String&, const String&);
bool Delete(const String&);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String currentDir;
/* (readonly) */
String programDir;
/* (readonly) */
String userDocumentsDir;
};

class PackageFile
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Open(const String&, uint = 0) const;
bool Exists(const String&) const;
bool compressed() const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
String name;
/* (readonly) */
uint numFiles;
/* (readonly) */
uint totalSize;
/* (readonly) */
uint checksum;
};

class Resource
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File);
bool Save(File) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String name;
/* (readonly) */
uint memoryUse;
/* (readonly) */
uint useTimer;
};

class ResourceCache
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool AddResourceDir(const String&, uint = - 1);
void AddPackageFile(PackageFile, uint = - 1);
bool AddManualResource(Resource);
void RemoveResourceDir(const String&);
void RemovePackageFile(PackageFile, bool = true, bool = false);
void RemovePackageFile(const String&, bool = true, bool = false);
void ReleaseResource(const String&, const String&, bool = false);
void ReleaseResources(ShortStringHash, bool = false);
void ReleaseResources(const String&, const String&, bool = false);
void ReleaseResources(const String&, bool = false);
void ReleaseAllResources(bool = false);
bool ReloadResource(Resource);
bool Exists(const String&) const;
File GetFile(const String&);
String GetPreferredResourceDir(const String&) const;
String SanitateResourceName(const String&) const;
String SanitateResourceDirName(const String&) const;
String GetResourceFileName(const String&) const;
Resource GetResource(const String&, const String&);
Resource GetResource(ShortStringHash, const String&);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
Array<uint> memoryBudget;
/* (readonly) */
Array<uint> memoryUse;
/* (readonly) */
uint totalMemoryUse;
/* (readonly) */
Array<String> resourceDirs;
/* (readonly) */
Array<PackageFile> packageFiles;
/* (writeonly) */
bool searchPackagesFirst;
/* (readonly) */
bool seachPackagesFirst;
bool autoReloadResources;
};

class Image
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File);
bool Save(File) const;
void FlipVertical();
void SaveBMP(const String&);
void SavePNG(const String&);
void SaveTGA(const String&);
void SaveJPG(const String&, int);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String name;
/* (readonly) */
uint memoryUse;
/* (readonly) */
uint useTimer;
/* (readonly) */
int width;
/* (readonly) */
int height;
/* (readonly) */
uint components;
/* (readonly) */
bool compressed;
};

class XMLFile
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File);
bool Save(File) const;
XMLElement CreateRoot(const String&);
XMLElement GetRoot(const String& = String ( ));
void Patch(XMLFile);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String name;
/* (readonly) */
uint memoryUse;
/* (readonly) */
uint useTimer;
/* (readonly) */
XMLElement root;
};

class XMLElement
{
// Methods:
XMLElement CreateChild(const String&);
bool RemoveChild(const XMLElement&);
bool RemoveChild(const String&);
bool RemoveChildren(const String& = String ( ));
bool RemoveAttribute(const String& = String ( ));
XMLElement SelectSingle(const String&);
XMLElement SelectSinglePrepared(const XPathQuery&);
XPathResultSet Select(const String&);
XPathResultSet SelectPrepared(const XPathQuery&);
bool SetValue(const String&);
bool SetAttribute(const String&, const String&);
bool SetAttribute(const String&);
bool SetBool(const String&, bool);
bool SetBoundingBox(const BoundingBox&);
bool SetColor(const String&, const Color&);
bool SetFloat(const String&, float);
bool SetInt(const String&, int);
bool SetUInt(const String&, uint);
bool SetQuaternion(const String&, const Quaternion&);
bool SetVariant(const Variant&);
bool SetResourceRef(const String&, const ResourceRef&);
bool SetResourceRefList(const String&, const ResourceRefList&);
bool SetVariantVector(Array<Variant>);
bool SetVariantMap(const VariantMap&);
bool SetVector2(const String&, const Vector2&);
bool SetVector3(const String&, const Vector3&);
bool SetVector4(const String&, const Vector4&);
bool SetVectorVariant(const String&, const Variant&);
bool HasAttribute(const String&) const;
String GetValue() const;
String GetAttribute(const String& = String ( )) const;
String GetAttributeLower(const String&) const;
String GetAttributeUpper(const String&) const;
Array<String> GetAttributeNames() const;
bool HasChild(const String&) const;
XMLElement GetChild(const String& = String ( )) const;
XMLElement GetNext(const String& = String ( )) const;
bool GetBool(const String&) const;
BoundingBox GetBoundingBox() const;
Color GetColor(const String&) const;
float GetFloat(const String&) const;
uint GetUInt(const String&) const;
int GetInt(const String&) const;
Quaternion GetQuaternion(const String&) const;
Variant GetVariant() const;
ResourceRef GetResourceRef() const;
ResourceRefList GetResourceRefList() const;
Array<Variant> GetVariantVector() const;
VariantMap GetVariantMap() const;
Vector2 GetVector2(const String&) const;
Vector3 GetVector3(const String&) const;
Vector4 GetVector4(const String&) const;
Variant GetVectorVariant(const String&) const;

// Properties:
String value;
/* (readonly) */
String name;
/* (readonly) */
uint numAttributes;
/* (readonly) */
bool isNull;
/* (readonly) */
bool notNull;
/* (readonly) */
XMLElement parent;
/* (readonly) */
XMLFile file;
/* (readonly) */
XMLElement nextResult;
};

class XPathResultSet
{

// Properties:
/* (readonly) */
XMLElement firstResult;
/* (readonly) */
uint size;
/* (readonly) */
bool empty;
};

class XPathQuery
{
// Methods:
void Bind();
bool SetVariable(const String&, bool);
bool SetVariable(const String&, float);
bool SetVariable(const String&, const String&);
bool SetVariable(const String&, const XPathResultSet&);
bool SetQuery(const String&, const String& = String ( ), bool = true);
void Clear();
bool EvaluateToBool(XMLElement);
float EvaluateToFloat(XMLElement);
String EvaluateToString(XMLElement);
XPathResultSet Evaluate(XMLElement);

// Properties:
String query;
};

class Serializable
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
};

class Component
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
};

class Node
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void SetScale(float);
void SetTransform(const Vector3&, const Quaternion&);
void SetTransform(const Vector3&, const Quaternion&, float);
void SetTransform(const Vector3&, const Quaternion&, const Vector3&);
void SetWorldTransform(const Vector3&, const Quaternion&);
void SetWorldTransform(const Vector3&, const Quaternion&, float);
void SetWorldTransform(const Vector3&, const Quaternion&, const Vector3&);
void Translate(const Vector3&);
void TranslateRelative(const Vector3&);
void Rotate(const Quaternion&, bool = false);
void Pitch(float, bool = false);
void Yaw(float, bool = false);
void Roll(float, bool = false);
void LookAt(const Vector3&, const Vector3& = Vector3 ( 0 , 1 , 0 ));
void Scale(float);
void Scale(const Vector3&);
Node CreateChild(const String& = String ( ), CreateMode = REPLICATED, uint = 0);
void AddChild(Node);
void RemoveChild(Node);
void RemoveAllChildren();
void RemoveChildren(bool, bool, bool);
void Remove();
Component CreateComponent(const String&, CreateMode = REPLICATED, uint = 0);
Component GetOrCreateComponent(const String&, CreateMode = REPLICATED, uint = 0);
void RemoveComponent(Component);
void RemoveComponent(const String&);
void RemoveAllComponents();
void RemoveComponents(bool, bool);
Array<Node> GetChildren(bool = false) const;
Array<Node> GetChildrenWithComponent(const String&, bool = false) const;
Array<Node> GetChildrenWithScript(bool = false) const;
Array<Node> GetChildrenWithScript(const String&, bool = false) const;
Node GetChild(const String&, bool = false) const;
Array<Component> GetComponents() const;
Array<Component> GetComponents(const String&, bool = false) const;
Component GetComponent(const String&) const;
bool HasComponent(const String&) const;
Vector3 LocalToWorld(const Vector3&) const;
Vector3 LocalToWorld(const Vector4&) const;
Vector3 WorldToLocal(const Vector3&) const;
Vector3 WorldToLocal(const Vector4&) const;
void SetEnabled(bool, bool);
bool SaveXML(File);
Node Clone(CreateMode = REPLICATED);
ScriptObject CreateScriptObject(ScriptFile, const String&, CreateMode = REPLICATED);
ScriptObject CreateScriptObject(const String&, const String&, CreateMode = REPLICATED);
ScriptObject GetScriptObject() const;
ScriptObject GetScriptObject(const String&) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
Vector3 position;
Quaternion rotation;
Vector3 direction;
/* (readonly) */
Vector3 up;
/* (readonly) */
Vector3 right;
Vector3 scale;
Vector3 worldPosition;
Quaternion worldRotation;
Vector3 worldDirection;
/* (readonly) */
Vector3 worldUp;
/* (readonly) */
Vector3 worldRight;
Vector3 worldScale;
/* (readonly) */
Matrix3x4 transform;
/* (readonly) */
Matrix3x4 worldTransform;
/* (readonly) */
uint id;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<Node> children;
/* (readonly) */
uint numComponents;
/* (readonly) */
Array<Component> components;
String name;
Node parent;
/* (readonly) */
VariantMap vars;
bool enabled;
/* (readonly) */
Scene scene;
Connection owner;
/* (readonly) */
ScriptObject scriptObject;
};

class SmoothedTransform
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void Update(float, float);
void DrawDebugGeometry(DebugRenderer, bool);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
Vector3 targetPosition;
Quaternion targetRotation;
Vector3 targetWorldPosition;
Quaternion targetWorldRotation;
/* (readonly) */
bool inProgress;
};

class Scene
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void SetScale(float);
void SetTransform(const Vector3&, const Quaternion&);
void SetTransform(const Vector3&, const Quaternion&, float);
void SetTransform(const Vector3&, const Quaternion&, const Vector3&);
void SetWorldTransform(const Vector3&, const Quaternion&);
void SetWorldTransform(const Vector3&, const Quaternion&, float);
void SetWorldTransform(const Vector3&, const Quaternion&, const Vector3&);
void Translate(const Vector3&);
void TranslateRelative(const Vector3&);
void Rotate(const Quaternion&, bool = false);
void Pitch(float, bool = false);
void Yaw(float, bool = false);
void Roll(float, bool = false);
void LookAt(const Vector3&, const Vector3& = Vector3 ( 0 , 1 , 0 ));
void Scale(float);
void Scale(const Vector3&);
Node CreateChild(const String& = String ( ), CreateMode = REPLICATED, uint = 0);
void AddChild(Node);
void RemoveChild(Node);
void RemoveAllChildren();
void RemoveChildren(bool, bool, bool);
void Remove();
Component CreateComponent(const String&, CreateMode = REPLICATED, uint = 0);
Component GetOrCreateComponent(const String&, CreateMode = REPLICATED, uint = 0);
void RemoveComponent(Component);
void RemoveComponent(const String&);
void RemoveAllComponents();
void RemoveComponents(bool, bool);
Array<Node> GetChildren(bool = false) const;
Array<Node> GetChildrenWithComponent(const String&, bool = false) const;
Array<Node> GetChildrenWithScript(bool = false) const;
Array<Node> GetChildrenWithScript(const String&, bool = false) const;
Node GetChild(const String&, bool = false) const;
Array<Component> GetComponents() const;
Array<Component> GetComponents(const String&, bool = false) const;
Component GetComponent(const String&) const;
bool HasComponent(const String&) const;
Vector3 LocalToWorld(const Vector3&) const;
Vector3 LocalToWorld(const Vector4&) const;
Vector3 WorldToLocal(const Vector3&) const;
Vector3 WorldToLocal(const Vector4&) const;
bool LoadXML(File);
bool SaveXML(File);
bool LoadAsync(File);
bool LoadAsyncXML(File);
void StopAsyncLoading();
Node Instantiate(File, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node InstantiateXML(File, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node InstantiateXML(XMLFile, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node InstantiateXML(const XMLElement&, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
void Clear(bool = true, bool = true);
void AddRequiredPackageFile(PackageFile);
void ClearRequiredPackageFiles();
void RegisterVar(const String&);
void UnregisterVar(const String&);
void UnregisterAllVars(const String&);
Component GetComponent(uint);
Node GetNode(uint);
const String& GetVarName(ShortStringHash) const;
void Update(float);
ScriptObject CreateScriptObject(ScriptFile, const String&, CreateMode = REPLICATED);
ScriptObject CreateScriptObject(const String&, const String&, CreateMode = REPLICATED);
ScriptObject GetScriptObject() const;
ScriptObject GetScriptObject(const String&) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
Vector3 position;
Quaternion rotation;
Vector3 direction;
/* (readonly) */
Vector3 up;
/* (readonly) */
Vector3 right;
Vector3 scale;
Vector3 worldPosition;
Quaternion worldRotation;
Vector3 worldDirection;
/* (readonly) */
Vector3 worldUp;
/* (readonly) */
Vector3 worldRight;
Vector3 worldScale;
/* (readonly) */
Matrix3x4 transform;
/* (readonly) */
Matrix3x4 worldTransform;
/* (readonly) */
uint id;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<Node> children;
/* (readonly) */
uint numComponents;
/* (readonly) */
Array<Component> components;
String name;
Node parent;
/* (readonly) */
VariantMap vars;
bool updateEnabled;
float timeScale;
float elapsedTime;
float smoothingConstant;
float snapThreshold;
/* (readonly) */
bool asyncLoading;
/* (readonly) */
float asyncProgress;
/* (readonly) */
uint checksum;
/* (readonly) */
String fileName;
/* (readonly) */
Array<PackageFile> requiredPackageFiles;
/* (readonly) */
DebugRenderer debugRenderer;
/* (readonly) */
Octree octree;
/* (readonly) */
PhysicsWorld physicsWorld;
/* (readonly) */
ScriptObject scriptObject;
};

class Bone
{

// Properties:
Node node;
String name;
Vector3 initialPosition;
Quaternion initialRotation;
Vector3 initialScale;
bool animated;
float radius;
BoundingBox boundingBox;
};

class Skeleton
{
// Methods:
void Reset();
Bone GetBone(const String&) const;

// Properties:
/* (readonly) */
Bone rootBone;
/* (readonly) */
uint numBones;
/* (readonly) */
Array<Bone> bones;
};

class DebugRenderer
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void AddLine(const Vector3&, const Vector3&, const Color&, bool = true);
void AddNode(Node, float = 1.0, bool = true);
void AddBoundingBox(const BoundingBox&, const Color&, bool = true);
void AddFrustum(const Frustum&, const Color&, bool = true);
void AddPolyhedron(const Polyhedron&, const Color&, bool = true);
void AddSphere(const Sphere&, const Color&, bool = true);
void AddSkeleton(Skeleton, const Color&, bool = true);
void DrawDebugGeometry(DebugRenderer, bool);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
};

class Camera
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
void SetOrthoSize(const Vector2&);
Frustum GetSplitFrustum(float, float) const;
Ray GetScreenRay(float, float) const;
Vector2 WorldToScreenPoint(const Vector3&) const;
Vector3 ScreenToWorldPoint(const Vector3&) const;
float GetDistance(const Vector3&) const;
float GetDistanceSquared(const Vector3&) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
float nearClip;
float farClip;
float fov;
float orthoSize;
float aspectRatio;
float zoom;
float lodBias;
bool orthographic;
bool autoAspectRatio;
Vector2 projectionOffset;
bool useReflection;
Plane reflectionPlane;
bool useClipping;
Plane clipPlane;
uint viewMask;
uint viewOverrideFlags;
FillMode fillMode;
/* (readonly) */
Frustum frustum;
/* (readonly) */
Matrix4 projection;
/* (readonly) */
Matrix3x4 view;
/* (readonly) */
Frustum viewSpaceFrustum;
/* (readonly) */
float halfViewSize;
/* (readonly) */
Matrix3x4 effectiveWorldTransform;
};

class RenderTargetInfo
{

// Properties:
String name;
String tag;
uint format;
IntVector2 size;
RenderTargetSizeMode sizeMode;
bool enabled;
bool filtered;
bool sRGB;
};

class RenderPathCommand
{
// Methods:
void RemoveShaderParameter(const String&);

// Properties:
Array<String> textureNames;
Array<Variant> shaderParameters;
uint numOutputs;
Array<String> outputNames;
String tag;
RenderCommandType type;
RenderCommandSortMode sortMode;
String pass;
String metadata;
uint clearFlags;
Color clearColor;
float clearDepth;
uint clearStencil;
bool enabled;
bool useFogColor;
bool markToStencil;
bool vertexLights;
bool useLitBase;
bool useScissor;
String vertexShaderName;
String pixelShaderName;
};

class RenderPath
{
// Methods:
RenderPath Clone();
bool Load(XMLFile);
bool Append(XMLFile);
void SetEnabled(const String&, bool);
void ToggleEnabled(const String&);
void AddRenderTarget(const RenderTargetInfo&);
void RemoveRenderTarget(uint);
void RemoveRenderTarget(const String&);
void RemoveRenderTargts(const String&);
void AddCommand(const RenderPathCommand&);
void InsertCommand(uint, const RenderPathCommand&);
void RemoveCommand(uint);
void RemoveCommands(const String&);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
uint numRenderTargets;
Array<RenderTargetInfo> renderTargets;
/* (readonly) */
uint numCommands;
Array<RenderPathCommand> commands;
Array<Variant> shaderParameters;
};

class Texture
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File);
bool Save(File) const;
void SetNumLevels(uint);
void ClearDataLost();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String name;
/* (readonly) */
uint memoryUse;
/* (readonly) */
uint useTimer;
/* (readonly) */
TextureUsage usage;
/* (readonly) */
uint format;
/* (readonly) */
bool compressed;
/* (readonly) */
uint levels;
/* (readonly) */
int width;
/* (readonly) */
int height;
/* (readonly) */
Array<int> levelWidth;
/* (readonly) */
Array<int> levelHeight;
TextureFilterMode filterMode;
Array<TextureAddressMode> addressMode;
Color borderColor;
bool sRGB;
Texture backupTexture;
Array<int> mipsToSkip;
/* (readonly) */
bool dataLost;
};

class Viewport
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetRenderPath(XMLFile);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
Scene scene;
Camera camera;
RenderPath renderPath;
IntRect rect;
};

class RenderSurface
{
// Methods:
void QueueUpdate();

// Properties:
/* (readonly) */
Texture parentTexture;
/* (readonly) */
int width;
/* (readonly) */
int height;
/* (readonly) */
TextureUsage usage;
uint numViewports;
Array<Viewport> viewports;
RenderSurfaceUpdateMode updateMode;
RenderSurface linkedRenderTarget;
RenderSurface linkedDepthStencil;
};

class Texture2D
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File);
bool Save(File) const;
void SetNumLevels(uint);
void ClearDataLost();
bool SetSize(int, int, uint, TextureUsage = TEXTURE_STATIC);
bool Load(Image, bool = false);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String name;
/* (readonly) */
uint memoryUse;
/* (readonly) */
uint useTimer;
/* (readonly) */
TextureUsage usage;
/* (readonly) */
uint format;
/* (readonly) */
bool compressed;
/* (readonly) */
uint levels;
/* (readonly) */
int width;
/* (readonly) */
int height;
/* (readonly) */
Array<int> levelWidth;
/* (readonly) */
Array<int> levelHeight;
TextureFilterMode filterMode;
Array<TextureAddressMode> addressMode;
Color borderColor;
bool sRGB;
Texture backupTexture;
Array<int> mipsToSkip;
/* (readonly) */
bool dataLost;
/* (readonly) */
RenderSurface renderSurface;
};

class TextureCube
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File);
bool Save(File) const;
void SetNumLevels(uint);
void ClearDataLost();
bool SetSize(int, uint, TextureUsage = TEXTURE_STATIC);
bool Load(CubeMapFace, Image, bool = false);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String name;
/* (readonly) */
uint memoryUse;
/* (readonly) */
uint useTimer;
/* (readonly) */
TextureUsage usage;
/* (readonly) */
uint format;
/* (readonly) */
bool compressed;
/* (readonly) */
uint levels;
/* (readonly) */
int width;
/* (readonly) */
int height;
/* (readonly) */
Array<int> levelWidth;
/* (readonly) */
Array<int> levelHeight;
TextureFilterMode filterMode;
Array<TextureAddressMode> addressMode;
Color borderColor;
bool sRGB;
Texture backupTexture;
Array<int> mipsToSkip;
/* (readonly) */
bool dataLost;
/* (readonly) */
Array<RenderSurface> renderSurfaces;
};

class BiasParameters
{

// Properties:
float constantBias;
float slopeScaledBias;
};

class Pass
{

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
BlendMode blendMode;
CompareMode depthTestMode;
PassLightingMode lightingMode;
bool depthWrite;
bool alphaMask;
String vertexShader;
String pixelShader;
};

class Technique
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File);
bool Save(File) const;
Pass CreatePass(StringHash);
void RemovePass(StringHash);
bool HasPass(StringHash) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String name;
/* (readonly) */
uint memoryUse;
/* (readonly) */
uint useTimer;
bool sm3;
/* (readonly) */
Array<Pass> passes;
};

class TechniqueEntry
{

// Properties:
Technique technique;
int qualityLevel;
float lodDistance;
};

class Material
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File);
bool Save(File) const;
bool Load(const XMLElement&);
bool Save(XMLElement&) const;
void SetTechnique(uint, Technique, uint = 0, float = 0.0);
void SetUVTransform(const Vector2&, float, const Vector2&);
void SetUVTransform(const Vector2&, float, float);
void RemoveShaderParameter(const String&);
void SortTechniques();
Material Clone(const String& = String ( )) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String name;
/* (readonly) */
uint memoryUse;
/* (readonly) */
uint useTimer;
uint numTechniques;
/* (readonly) */
Array<Technique> techniques;
/* (readonly) */
Array<TechniqueEntry> techniqueEntries;
Array<Variant> shaderParameters;
/* (readonly) */
Array<String> shaderParameterNames;
Array<Texture> textures;
/* (readonly) */
bool occlusion;
CullMode cullMode;
CullMode shadowCullMode;
BiasParameters depthBias;
};

class Model
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File);
bool Save(File) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String name;
/* (readonly) */
uint memoryUse;
/* (readonly) */
uint useTimer;
/* (readonly) */
BoundingBox boundingBox;
/* (readonly) */
Skeleton skeleton;
/* (readonly) */
uint numGeometries;
/* (readonly) */
Array<uint> numGeometryLodLevels;
/* (readonly) */
uint numMorphs;
};

class AnimationTriggerPoint
{

// Properties:
float time;
Variant data;
};

class Animation
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File);
bool Save(File) const;
void AddTrigger(float, bool, const Variant&);
void RemoveTrigger(uint);
void RemoveAllTriggers();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String name;
/* (readonly) */
uint memoryUse;
/* (readonly) */
uint useTimer;
/* (readonly) */
String animationName;
/* (readonly) */
float length;
/* (readonly) */
uint numTracks;
uint numTriggers;
/* (readonly) */
Array<AnimationTriggerPoint> triggers;
};

class Drawable
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
/* (readonly) */
bool inView;
bool castShadows;
bool occluder;
bool occludee;
float drawDistance;
float shadowDistance;
float lodBias;
uint viewMask;
uint lightMask;
uint shadowMask;
uint zoneMask;
uint maxLights;
/* (readonly) */
BoundingBox boundingBox;
/* (readonly) */
BoundingBox worldBoundingBox;
};

class CascadeParameters
{

// Properties:
float split1;
float split2;
float split3;
float split4;
float fadeStart;
float biasAutoAdjust;
};

class FocusParameters
{

// Properties:
bool focus;
bool nonUniform;
bool autoSize;
float quantize;
float minView;
};

class Light
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
/* (readonly) */
bool inView;
bool castShadows;
bool occluder;
bool occludee;
float drawDistance;
float shadowDistance;
float lodBias;
uint viewMask;
uint lightMask;
uint shadowMask;
uint zoneMask;
uint maxLights;
/* (readonly) */
BoundingBox boundingBox;
/* (readonly) */
BoundingBox worldBoundingBox;
LightType lightType;
bool perVertex;
Color color;
float specularIntensity;
float range;
float fov;
float aspectRatio;
float fadeDistance;
BiasParameters shadowBias;
CascadeParameters shadowCascade;
FocusParameters shadowFocus;
float shadowFadeDistance;
float shadowIntensity;
float shadowResolution;
float shadowNearFarRatio;
Texture rampTexture;
Texture shapeTexture;
/* (readonly) */
Frustum frustum;
};

class Zone
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
/* (readonly) */
bool inView;
bool castShadows;
bool occluder;
bool occludee;
float drawDistance;
float shadowDistance;
float lodBias;
uint viewMask;
uint lightMask;
uint shadowMask;
uint zoneMask;
uint maxLights;
BoundingBox boundingBox;
/* (readonly) */
BoundingBox worldBoundingBox;
/* (readonly) */
Matrix3x4 inverseWorldTransform;
Color ambientColor;
/* (readonly) */
Color ambientStartColor;
/* (readonly) */
Color ambientEndColor;
Color fogColor;
float fogStart;
float fogEnd;
int priority;
bool override;
bool ambientGradient;
};

class StaticModel
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
void ApplyMaterialList(const String& = String ( ));
bool IsInside(const Vector3&) const;
bool IsInsideLocal(const Vector3&) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
/* (readonly) */
bool inView;
bool castShadows;
bool occluder;
bool occludee;
float drawDistance;
float shadowDistance;
float lodBias;
uint viewMask;
uint lightMask;
uint shadowMask;
uint zoneMask;
uint maxLights;
/* (readonly) */
BoundingBox boundingBox;
/* (readonly) */
BoundingBox worldBoundingBox;
Model model;
/* (writeonly) */
Material material;
Array<Material> materials;
/* (readonly) */
uint numGeometries;
uint occlusionLodLevel;
};

class StaticModelGroup
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
void ApplyMaterialList(const String& = String ( ));
void AddInstanceNode(Node);
void RemoveInstanceNode(Node);
void RemoveAllInstanceNodes();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
/* (readonly) */
bool inView;
bool castShadows;
bool occluder;
bool occludee;
float drawDistance;
float shadowDistance;
float lodBias;
uint viewMask;
uint lightMask;
uint shadowMask;
uint zoneMask;
uint maxLights;
/* (readonly) */
BoundingBox boundingBox;
/* (readonly) */
BoundingBox worldBoundingBox;
Model model;
/* (writeonly) */
Material material;
Array<Material> materials;
/* (readonly) */
uint numGeometries;
/* (readonly) */
Zone zone;
uint occlusionLodLevel;
/* (readonly) */
uint numInstanceNodes;
/* (readonly) */
Array<Node> instanceNodes;
};

class Skybox
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
void ApplyMaterialList(const String& = String ( ));

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
/* (readonly) */
bool inView;
bool castShadows;
bool occluder;
bool occludee;
float drawDistance;
float shadowDistance;
float lodBias;
uint viewMask;
uint lightMask;
uint shadowMask;
uint zoneMask;
uint maxLights;
/* (readonly) */
BoundingBox boundingBox;
/* (readonly) */
BoundingBox worldBoundingBox;
Model model;
/* (writeonly) */
Material material;
Array<Material> materials;
/* (readonly) */
uint numGeometries;
/* (readonly) */
Zone zone;
};

class AnimationState
{
// Methods:
void AddWeight(float);
void AddTime(float);
void Apply();
void SetBoneWeight(uint, float, bool = false);
void SetBoneWeight(const String&, float, bool = false);
void SetBoneWeight(StringHash, float, bool = false);
float GetBoneWeight(uint) const;
float GetBoneWeight(StringHash) const;
uint GetTrackIndex(const String&) const;
uint GetTrackIndex(StringHash) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
Bone startBone;
bool looped;
float weight;
float time;
uint8 layer;
/* (readonly) */
Animation animation;
/* (readonly) */
AnimatedModel model;
/* (readonly) */
Node node;
/* (readonly) */
bool enabled;
/* (readonly) */
float length;
Array<float> boneWeights;
};

class AnimatedModel
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
void ApplyMaterialList(const String& = String ( ));
AnimationState AddAnimationState(Animation);
void RemoveAnimationState(Animation);
void RemoveAnimationState(const String&);
void RemoveAnimationState(AnimationState);
void RemoveAnimationState(uint);
void RemoveAllAnimationStates();
void SetMorphWeight(uint, float);
void ResetMorphWeights();
float GetMorphWeight(uint) const;
AnimationState GetAnimationState(Animation) const;
AnimationState GetAnimationState(uint) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
/* (readonly) */
bool inView;
bool castShadows;
bool occluder;
bool occludee;
float drawDistance;
float shadowDistance;
float lodBias;
uint viewMask;
uint lightMask;
uint shadowMask;
uint zoneMask;
uint maxLights;
/* (readonly) */
BoundingBox boundingBox;
/* (readonly) */
BoundingBox worldBoundingBox;
Model model;
/* (writeonly) */
Material material;
Array<Material> materials;
/* (readonly) */
uint numGeometries;
/* (readonly) */
Zone zone;
float animationLodBias;
bool updateInvisible;
/* (readonly) */
Skeleton skeleton;
/* (readonly) */
uint numAnimationStates;
/* (readonly) */
Array<AnimationState> animationStates;
/* (readonly) */
uint numMorphs;
/* (readonly) */
Array<String> morphNames;
Array<float> morphWeights;
};

class AnimationController
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
bool Play(const String&, uint8, bool, float = 0.0f);
bool PlayExclusive(const String&, uint8, bool, float = 0.0f);
void Stop(const String&, float = 0.0f);
void StopLayer(uint8, float = 0.0f);
void StopAll(float = 0.0f);
bool Fade(const String&, float, float);
bool FadeOthers(const String&, float, float);
bool SetLayer(const String&, uint8);
bool SetStartBone(const String&, const String&);
bool SetTime(const String&, float);
bool SetWeight(const String&, float);
bool SetLooped(const String&, bool);
bool SetSpeed(const String&, float);
bool SetAutoFade(const String&, float);
bool IsPlaying(const String&) const;
bool IsFadingIn(const String&) const;
bool IsFadingOut(const String&) const;
uint8 GetLayer(const String&) const;
const String& GetStartBone(const String&) const;
float GetTime(const String&) const;
float GetWeight(const String&) const;
bool GetLooped(const String&) const;
float GetLength(const String&) const;
float GetSpeed(const String&) const;
float GetAutoFade(const String&) const;
float GetFadeTarget(const String&) const;
AnimationState GetAnimationState(const String&) const;
AnimationState GetAnimationState(StringHash) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
};

class Billboard
{

// Properties:
Vector3 position;
Vector2 size;
Rect uv;
Color color;
float rotation;
bool enabled;
};

class BillboardSet
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
void Commit();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
/* (readonly) */
bool inView;
bool castShadows;
bool occluder;
bool occludee;
float drawDistance;
float shadowDistance;
float lodBias;
uint viewMask;
uint lightMask;
uint shadowMask;
uint zoneMask;
uint maxLights;
/* (readonly) */
BoundingBox boundingBox;
/* (readonly) */
BoundingBox worldBoundingBox;
Material material;
uint numBillboards;
bool relative;
bool sorted;
bool scaled;
bool faceCamera;
float animationLodBias;
/* (readonly) */
Array<Billboard> billboards;
/* (readonly) */
Zone zone;
};

class ColorFrame
{

// Properties:
Color color;
float time;
};

class TextureFrame
{

// Properties:
Rect uv;
float time;
};

class ParticleEmitter
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
bool Load(XMLFile);
bool Save(XMLFile);
void SetEmitting(bool, bool);
void SetColor(const Color&);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
/* (readonly) */
bool inView;
bool castShadows;
bool occluder;
bool occludee;
float drawDistance;
float shadowDistance;
float lodBias;
uint viewMask;
uint lightMask;
uint shadowMask;
uint zoneMask;
uint maxLights;
/* (readonly) */
BoundingBox boundingBox;
/* (readonly) */
BoundingBox worldBoundingBox;
Material material;
bool relative;
bool sorted;
bool scaled;
bool updateInvisible;
float animationLodBias;
bool emitting;
uint numParticles;
/* (writeonly) */
float emissionRate;
float minEmissionRate;
float maxEmissionRate;
EmitterType emitterType;
Vector3 emitterSize;
float activeTime;
float inactiveTime;
/* (writeonly) */
float timeToLive;
float minTimeToLive;
float maxTimeToLive;
/* (writeonly) */
Vector2 particleSize;
Vector2 minParticleSize;
Vector3 maxParticleSize;
Vector3 minDirection;
Vector3 maxDirection;
/* (writeonly) */
float velocity;
float minVelocity;
float maxVelocity;
/* (writeonly) */
float rotation;
float minRotation;
float maxRotation;
/* (writeonly) */
float rotationSpeed;
float minRotationSpeed;
float maxRotationSpeed;
Vector3 constantForce;
float dampingForce;
float sizeAdd;
float sizeMul;
/* (readonly) */
Array<ColorFrame> colors;
uint numColors;
/* (readonly) */
Array<TextureFrame> textureFrames;
uint numTextureFrames;
/* (readonly) */
Zone zone;
};

class CustomGeometry
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
void Clear();
void BeginGeometry(uint, PrimitiveType);
void DefineVertex(const Vector3&);
void DefineNormal(const Vector3&);
void DefineColor(const Color&);
void DefineTexCoord(const Vector2&);
void DefineTangent(const Vector4&);
void Commit();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
/* (readonly) */
bool inView;
bool castShadows;
bool occluder;
bool occludee;
float drawDistance;
float shadowDistance;
float lodBias;
uint viewMask;
uint lightMask;
uint shadowMask;
uint zoneMask;
uint maxLights;
/* (readonly) */
BoundingBox boundingBox;
/* (readonly) */
BoundingBox worldBoundingBox;
/* (writeonly) */
Material material;
Array<Material> materials;
uint numGeometries;
/* (readonly) */
Zone zone;
};

class DecalSet
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
bool AddDecal(Drawable, const Vector3&, const Quaternion&, float, float, float, const Vector2&, const Vector2&, float = 0.0, float = 0.1, uint = 0xffffffff);
void RemoveDecals(uint);
void RemoveAllDecals();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
/* (readonly) */
bool inView;
bool castShadows;
bool occluder;
bool occludee;
float drawDistance;
float shadowDistance;
float lodBias;
uint viewMask;
uint lightMask;
uint shadowMask;
uint zoneMask;
uint maxLights;
/* (readonly) */
BoundingBox boundingBox;
/* (readonly) */
BoundingBox worldBoundingBox;
Material material;
/* (readonly) */
uint numDecals;
/* (readonly) */
uint numVertices;
/* (readonly) */
uint numIndices;
uint maxVertices;
uint maxIndices;
/* (readonly) */
Zone zone;
};

class TerrainPatch
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
/* (readonly) */
bool inView;
bool castShadows;
bool occluder;
bool occludee;
float drawDistance;
float shadowDistance;
float lodBias;
uint viewMask;
uint lightMask;
uint shadowMask;
uint zoneMask;
uint maxLights;
/* (readonly) */
BoundingBox boundingBox;
/* (readonly) */
BoundingBox worldBoundingBox;
};

class Terrain
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
float GetHeight(const Vector3&) const;
Vector3 GetNormal(const Vector3&) const;
TerrainPatch GetPatch(int, int) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
Material material;
bool smoothing;
Image heightMap;
int patchSize;
Vector3 spacing;
/* (readonly) */
IntVector2 numVertices;
/* (readonly) */
IntVector2 numPatches;
/* (readonly) */
Array<TerrainPatch> patches;
bool castShadows;
bool occluder;
bool occludee;
float drawDistance;
float shadowDistance;
float lodBias;
uint viewMask;
uint lightMask;
uint shadowMask;
uint zoneMask;
uint maxLights;
};

class RayQueryResult
{

// Properties:
/* (readonly) */
Drawable drawable;
/* (readonly) */
Node node;
Vector3 position;
Vector3 normal;
float distance;
uint subObject;
};

class Octree
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
void SetSize(const BoundingBox&, uint);
void DrawDebugGeometry(bool) const;
void AddManualDrawable(Drawable);
void RemoveManualDrawable(Drawable);
Array<RayQueryResult> Raycast(const Ray&, RayQueryLevel = RAY_TRIANGLE, float = M_INFINITY, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK) const;
RayQueryResult RaycastSingle(const Ray&, RayQueryLevel = RAY_TRIANGLE, float = M_INFINITY, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK) const;
Array<Node> GetDrawables(const Vector3&, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK);
Array<Node> GetDrawables(const BoundingBox&, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK);
Array<Node> GetDrawables(const Frustum&, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK);
Array<Node> GetDrawables(const Sphere&, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
/* (readonly) */
BoundingBox worldBoundingBox;
/* (readonly) */
uint numLevels;
};

class Graphics
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetMode(int, int, bool, bool, bool, bool, bool, int);
bool SetMode(int, int);
void SetWindowPosition(int, int);
bool ToggleFullscreen();
void Maximize();
void Minimize();
void Close();
bool TakeScreenShot(Image);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String windowTitle;
/* (writeonly) */
Image windowIcon;
IntVector2 windowPosition;
bool sRGB;
bool flushGPU;
/* (readonly) */
int width;
/* (readonly) */
int height;
/* (readonly) */
int multiSample;
/* (readonly) */
bool fullscreen;
/* (readonly) */
bool resizable;
/* (readonly) */
bool borderless;
/* (readonly) */
bool vsync;
/* (readonly) */
bool tripleBuffer;
/* (readonly) */
bool initialized;
/* (readonly) */
bool deviceLost;
/* (readonly) */
uint numPrimitives;
/* (readonly) */
uint numBatches;
/* (readonly) */
bool sm3Support;
/* (readonly) */
bool instancingSupport;
/* (readonly) */
bool lightPrepassSupport;
/* (readonly) */
bool deferredSupport;
/* (readonly) */
bool hardwareShadowSupport;
/* (readonly) */
bool sRGBSupport;
/* (readonly) */
bool sRGBWriteSupport;
bool forceSM2;
/* (readonly) */
Array<IntVector2> resolutions;
/* (readonly) */
Array<int> multiSampleLevels;
/* (readonly) */
IntVector2 desktopResolution;
};

class Renderer
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void DrawDebugGeometry(bool) const;
void ReloadShaders() const;
void SetDefaultRenderPath(XMLFile);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
uint numViewports;
Array<Viewport> viewports;
RenderPath defaultRenderPath;
/* (readonly) */
Zone defaultZone;
bool specularLighting;
int textureAnisotropy;
TextureFilterMode textureFilterMode;
int textureQuality;
int materialQuality;
bool drawShadows;
int shadowMapSize;
int shadowQuality;
int maxShadowCascades;
int maxShadowMaps;
bool reuseShadowMaps;
bool dynamicInstancing;
int minInstances;
int maxInstanceTriangles;
int maxSortedInstances;
int maxOccluderTriangles;
int occlusionBufferSize;
float occluderSizeThreshold;
/* (readonly) */
uint numPrimitives;
/* (readonly) */
uint numBatches;
/* (readonly) */
uint numViews;
/* (readonly) */
Array<uint> numGeometries;
/* (readonly) */
Array<uint> numLights;
/* (readonly) */
Array<uint> numShadowMaps;
/* (readonly) */
Array<uint> numOccluders;
};

class TouchState
{

// Properties:
int touchID;
IntVector2 position;
IntVector2 delta;
float pressure;
};

class JoystickState
{

// Properties:
/* (readonly) */
uint numButtons;
/* (readonly) */
uint numAxes;
/* (readonly) */
uint numHats;
/* (readonly) */
Array<bool> buttonDown;
/* (readonly) */
Array<bool> buttonPress;
/* (readonly) */
Array<float> axisPosition;
/* (readonly) */
Array<int> hatPosition;
String name;
};

class Input
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool OpenJoystick(uint);
void CloseJoystick(uint);
bool DetectJoysticks();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
bool mouseVisible;
bool screenKeyboardVisible;
/* (readonly) */
bool screenKeyboardSupport;
bool toggleFullscreen;
/* (readonly) */
Array<bool> keyDown;
/* (readonly) */
Array<bool> keyPress;
/* (readonly) */
Array<bool> mouseButtonDown;
/* (readonly) */
Array<bool> mouseButtonPress;
/* (readonly) */
Array<bool> qualifierDown;
/* (readonly) */
Array<bool> qualifierPress;
/* (readonly) */
int qualifiers;
/* (readonly) */
IntVector2 mousePosition;
/* (readonly) */
IntVector2 mouseMove;
/* (readonly) */
int mouseMoveX;
/* (readonly) */
int mouseMoveY;
/* (readonly) */
int mouseMoveWheel;
/* (readonly) */
uint numTouches;
/* (readonly) */
Array<TouchState> touches;
/* (readonly) */
uint numJoysticks;
/* (readonly) */
Array<String> joystickNames;
/* (readonly) */
Array<JoystickState> joysticks;
/* (readonly) */
bool focus;
/* (readonly) */
bool minimized;
};

class Sound
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File);
bool Save(File) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String name;
/* (readonly) */
uint memoryUse;
/* (readonly) */
uint useTimer;
/* (readonly) */
float length;
/* (readonly) */
uint sampleSize;
/* (readonly) */
float frequency;
bool looped;
/* (readonly) */
bool sixteenBit;
/* (readonly) */
bool stereo;
/* (readonly) */
bool compressed;
};

class SoundListener
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
};

class SoundSource
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
void Play(Sound);
void Play(Sound, float);
void Play(Sound, float, float);
void Play(Sound, float, float, float);
void Stop();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
SoundType soundType;
float frequency;
float gain;
float panning;
/* (readonly) */
Sound sound;
/* (readonly) */
float timePosition;
/* (readonly) */
float attenuation;
bool autoRemove;
/* (readonly) */
bool playing;
};

class SoundSource3D
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
void Play(Sound);
void Play(Sound, float);
void Play(Sound, float, float);
void Play(Sound, float, float, float);
void Stop();
void SetDistanceAttenuation(float, float, float);
void SetAngleAttenuation(float, float);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
SoundType soundType;
float frequency;
float gain;
float panning;
/* (readonly) */
Sound sound;
/* (readonly) */
float timePosition;
/* (readonly) */
float attenuation;
bool autoRemove;
/* (readonly) */
bool playing;
float nearDistance;
float farDistance;
float innerAngle;
float outerAngle;
float rolloffFactor;
};

class Audio
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetMode(int, int, bool, bool = true);
bool Play();
void Stop();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
Array<float> masterGain;
SoundListener listener;
/* (readonly) */
uint sampleSize;
/* (readonly) */
int mixRate;
/* (readonly) */
bool stereo;
/* (readonly) */
bool interpolation;
/* (readonly) */
bool playing;
/* (readonly) */
bool initialized;
};

class Font
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File);
bool Save(File) const;
bool SaveXML(File, int, bool = false);
bool SaveXML(const String&, int, bool = false);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String name;
/* (readonly) */
uint memoryUse;
/* (readonly) */
uint useTimer;
};

class UIElement
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
};

class BorderImage
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;
void SetFullImageRect();
void SetHoverOffset(int, int);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
Texture texture;
IntRect imageRect;
IntRect border;
IntVector2 hoverOffset;
BlendMode blendMode;
bool tiled;
};

class Sprite
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
uint GetNumChildren(bool) const;
void SetPosition(float, float);
void SetHotSpot(int, int);
void SetScale(float, float);
void SetScale(float);
void SetFullImageRect();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 size;
int width;
int height;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool sortChildren;
bool useDerivedOpacity;
bool visible;
/* (readonly) */
bool colorGradient;
XMLFile defaultStyle;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
Vector2 position;
IntVector2 hotSpot;
Vector2 scale;
float rotation;
Texture texture;
IntRect imageRect;
BlendMode blendMode;
};

class Button
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetPressedOffset(int, int);
void SetPressedChildOffset(int, int);
void SetRepeat(float, float);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
Texture texture;
IntRect imageRect;
IntRect border;
IntVector2 hoverOffset;
BlendMode blendMode;
bool tiled;
IntVector2 pressedOffset;
IntVector2 pressedChildOffset;
float repeatDelay;
float repeatRate;
/* (readonly) */
bool pressed;
};

class CheckBox
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetCheckedOffset(int, int);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
Texture texture;
IntRect imageRect;
IntRect border;
IntVector2 hoverOffset;
BlendMode blendMode;
bool tiled;
bool checked;
IntVector2 checkedOffset;
};

class Cursor
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;
void SetFullImageRect();
void SetHoverOffset(int, int);
void DefineShape(CursorShape, Texture, const IntRect&, const IntVector2&);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
Texture texture;
IntRect imageRect;
IntRect border;
IntVector2 hoverOffset;
BlendMode blendMode;
bool tiled;
CursorShape shape;
bool useSystemShapes;
};

class Slider
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;
void SetFullImageRect();
void SetHoverOffset(int, int);
void ChangeValue(float);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
Texture texture;
IntRect imageRect;
IntRect border;
IntVector2 hoverOffset;
BlendMode blendMode;
bool tiled;
Orientation orientation;
float range;
float value;
/* (readonly) */
BorderImage knob;
float repeatRate;
};

class ScrollBar
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;
void ChangeValue(float);
void StepBack();
void StepForward();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
Orientation orientation;
float range;
float value;
float scrollStep;
float stepFactor;
/* (readonly) */
float effectiveScrollStep;
/* (readonly) */
Button backButton;
/* (readonly) */
Button forwardButton;
/* (readonly) */
Slider slider;
};

class ScrollView
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;
void SetViewPosition(int, int);
void SetScrollBarsVisible(bool, bool);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
UIElement contentElement;
IntVector2 viewPosition;
float scrollStep;
float pageStep;
/* (readonly) */
ScrollBar horizontalScrollBar;
/* (readonly) */
ScrollBar verticalScrollBar;
/* (readonly) */
BorderImage scrollPanel;
bool scrollBarsAutoVisible;
};

class ListView
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;
void SetViewPosition(int, int);
void SetScrollBarsVisible(bool, bool);
void AddItem(UIElement);
void InsertItem(uint, UIElement, UIElement = null);
void RemoveItem(UIElement, uint = 0);
void RemoveItem(uint);
void RemoveAllItems();
void AddSelection(uint);
void RemoveSelection(uint);
void ToggleSelection(uint);
void ChangeSelection(int, bool);
void SetSelections(Array<uint>);
void ClearSelection();
void Expand(uint, bool, bool = false);
void ToggleExpand(uint, bool = false);
bool IsSelected(uint) const;
bool IsExpanded(uint) const;
Array<UIElement> GetItems() const;
uint FindItem(UIElement);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
IntVector2 viewPosition;
/* (readonly) */
UIElement contentElement;
/* (readonly) */
ScrollBar horizontalScrollBar;
/* (readonly) */
ScrollBar verticalScrollBar;
/* (readonly) */
BorderImage scrollPanel;
bool scrollBarsAutoVisible;
float scrollStep;
float pageStep;
/* (readonly) */
uint numItems;
/* (readonly) */
Array<UIElement> items;
uint selection;
/* (readonly) */
Array<uint> selections;
/* (readonly) */
UIElement selectedItem;
/* (readonly) */
Array<UIElement> selectedItems;
HighlightMode highlightMode;
bool multiselect;
bool hierarchyMode;
int baseIndent;
bool clearSelectionOnDefocus;
};

class Text
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;
bool SetFont(const String&, int);
bool SetFont(Font, int);
void SetSelection(uint, uint = M_MAX_UNSIGNED);
void ClearSelection();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
/* (readonly) */
Font font;
/* (readonly) */
int fontSize;
String text;
HorizontalAlignment textAlignment;
float rowSpacing;
bool wordwrap;
/* (readonly) */
uint selectionStart;
/* (readonly) */
uint selectionLength;
Color selectionColor;
Color hoverColor;
TextEffect textEffect;
Color effectColor;
/* (readonly) */
uint numRows;
/* (readonly) */
int rowHeight;
};

class Text3D
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
bool SetFont(const String&, int);
bool SetFont(Font, int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
/* (readonly) */
bool inView;
bool castShadows;
bool occluder;
bool occludee;
float drawDistance;
float shadowDistance;
float lodBias;
uint viewMask;
uint lightMask;
uint shadowMask;
uint zoneMask;
uint maxLights;
/* (readonly) */
BoundingBox boundingBox;
/* (readonly) */
BoundingBox worldBoundingBox;
/* (readonly) */
Font font;
/* (readonly) */
int fontSize;
Material material;
String text;
HorizontalAlignment textAlignment;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
float rowSpacing;
bool wordwrap;
TextEffect textEffect;
Color effectColor;
float effectDepthBias;
int width;
/* (writeonly) */
Color color;
Array<Color> colors;
float opacity;
bool faceCamera;
/* (readonly) */
uint numRows;
/* (readonly) */
int rowHeight;
};

class LineEdit
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;
void SetFullImageRect();
void SetHoverOffset(int, int);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
Texture texture;
IntRect imageRect;
IntRect border;
IntVector2 hoverOffset;
BlendMode blendMode;
bool tiled;
String text;
uint cursorPosition;
float cursorBlinkRate;
uint maxLength;
uint echoCharacter;
bool cursorMovable;
bool textSelectable;
bool textCopyable;
/* (readonly) */
Text textElement;
/* (readonly) */
BorderImage cursor;
};

class Menu
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetPressedOffset(int, int);
void SetPressedChildOffset(int, int);
void SetRepeat(float, float);
void SetPopupOffset(int, int);
void SetAccelerator(int, int);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
Texture texture;
IntRect imageRect;
IntRect border;
IntVector2 hoverOffset;
BlendMode blendMode;
bool tiled;
IntVector2 pressedOffset;
IntVector2 pressedChildOffset;
float repeatDelay;
float repeatRate;
/* (readonly) */
bool pressed;
UIElement popup;
IntVector2 popupOffset;
bool showPopup;
/* (readonly) */
int acceleratorKey;
/* (readonly) */
int acceleratorQualifiers;
};

class MessageBox
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String title;
String message;
/* (readonly) */
UIElement window;
};

class DropDownList
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetPressedOffset(int, int);
void SetPressedChildOffset(int, int);
void SetRepeat(float, float);
void SetAccelerator(int, int);
void AddItem(UIElement);
void InsertItem(uint, UIElement);
void RemoveItem(UIElement);
void RemoveItem(uint);
void RemoveAllItems();
Array<UIElement> GetItems() const;
UIElement getPopup() const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
Texture texture;
IntRect imageRect;
IntRect border;
IntVector2 hoverOffset;
BlendMode blendMode;
bool tiled;
IntVector2 pressedOffset;
IntVector2 pressedChildOffset;
float repeatDelay;
float repeatRate;
/* (readonly) */
bool pressed;
bool showPopup;
uint selection;
bool resizePopup;
/* (readonly) */
int acceleratorKey;
/* (readonly) */
int acceleratorQualifiers;
/* (readonly) */
uint numItems;
/* (readonly) */
Array<UIElement> items;
/* (readonly) */
UIElement selectedItem;
/* (readonly) */
ListView listView;
/* (readonly) */
UIElement placeholder;
String placeholderText;
};

class Window
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
bool movable;
bool resizable;
IntRect resizeBorder;
bool modal;
Color modalShadeColor;
Color modalFrameColor;
IntVector2 modalFrameSize;
bool fixedWidthResizing;
bool fixedHeightResizing;
};

class View3D
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;
void SetView(Scene, Camera);
void QueueUpdate();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
bool movable;
bool resizable;
IntRect resizeBorder;
bool modal;
Color modalShadeColor;
Color modalFrameColor;
IntVector2 modalFrameSize;
bool fixedWidthResizing;
bool fixedHeightResizing;
uint format;
bool autoUpdate;
/* (readonly) */
Texture2D renderTexture;
/* (readonly) */
Texture2D depthTexture;
/* (readonly) */
Viewport viewport;
/* (readonly) */
Scene scene;
/* (readonly) */
Node cameraNode;
};

class FileSelector
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetButtonTexts(const String&, const String&);
void SetFilters(Array<String>, uint);
void UpdateElements();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String title;
String path;
String fileName;
bool directoryMode;
/* (readonly) */
String filter;
/* (readonly) */
uint filterIndex;
XMLFile defaultStyle;
/* (readonly) */
Window window;
/* (readonly) */
Text titleText;
/* (readonly) */
ListView fileList;
/* (readonly) */
LineEdit pathEdit;
/* (readonly) */
LineEdit fileNameEdit;
/* (readonly) */
DropDownList filterList;
/* (readonly) */
Button okButton;
/* (readonly) */
Button cancelButton;
};

class ToolTip
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool SaveXML(File);
bool SetStyle(const XMLElement&);
bool SetStyle(const String&, XMLFile = null);
bool SetStyleAuto(XMLFile = null);
void SetPosition(int, int);
void SetSize(int, int);
void SetMinSize(int, int);
void SetMaxSize(int, int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFixedHeight(int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void UpdateLayout();
void DisableLayoutUpdate();
void EnableLayoutUpdate();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void AddChild(UIElement);
void InsertChild(uint, UIElement);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveAllChildren();
void Remove();
uint FindChild(UIElement) const;
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
const Variant& GetVar(const ShortStringHash&);
IntVector2 ScreenToElement(const IntVector2&);
IntVector2 ElementToScreen(const IntVector2&);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
uint GetNumChildren(bool) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
String style;
String name;
IntVector2 position;
IntVector2 size;
int width;
int height;
IntVector2 minSize;
int minWidth;
int minHeight;
IntVector2 maxSize;
int maxWidth;
int maxHeight;
/* (readonly) */
bool fixedSize;
/* (readonly) */
bool fixedWidth;
/* (readonly) */
bool fixedHeight;
HorizontalAlignment horizontalAlignment;
VerticalAlignment verticalAlignment;
IntRect clipBorder;
/* (writeonly) */
Color color;
Array<Color> colors;
int priority;
float opacity;
bool bringToFront;
bool bringToBack;
bool clipChildren;
bool sortChildren;
bool useDerivedOpacity;
bool enabled;
bool editable;
bool focus;
bool selected;
bool visible;
/* (readonly) */
bool hovering;
bool internal;
/* (readonly) */
bool colorGradient;
FocusMode focusMode;
uint dragDropMode;
TraversalMode traversalMode;
XMLFile defaultStyle;
LayoutMode layoutMode;
int layoutSpacing;
IntRect layoutBorder;
int indent;
int indentSpacing;
/* (readonly) */
int indentWidth;
/* (readonly) */
IntVector2 childOffset;
bool elementEventSender;
/* (readonly) */
uint numChildren;
/* (readonly) */
uint numAllChildren;
/* (readonly) */
Array<UIElement> children;
UIElement parent;
/* (readonly) */
UIElement root;
/* (readonly) */
IntVector2 screenPosition;
/* (readonly) */
IntRect combinedScreenRect;
/* (readonly) */
float derivedOpacity;
/* (readonly) */
VariantMap vars;
float delay;
};

class UI
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void Clear();
void DebugDraw(UIElement);
UIElement LoadLayout(File);
UIElement LoadLayout(File, XMLFile);
UIElement LoadLayout(XMLFile);
UIElement LoadLayout(XMLFile, XMLFile);
bool SaveLayout(File, UIElement);
void SetFocusElement(UIElement, bool = false);
UIElement GetElementAt(const IntVector2&, bool = true);
UIElement GetElementAt(int, int, bool = true);
bool HasModalElement() const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
Cursor cursor;
/* (readonly) */
IntVector2 cursorPosition;
UIElement focusElement;
/* (readonly) */
UIElement frontElement;
/* (readonly) */
UIElement dragElement;
/* (readonly) */
UIElement root;
/* (readonly) */
UIElement modalRoot;
String clipBoardText;
float doubleClickInterval;
float dragBeginInterval;
int dragBeginDistance;
float defaultToolTipDelay;
int maxFontTextureSize;
bool nonFocusedMouseWheel;
bool useSystemClipBoard;
bool useScreenKeyboard;
bool useMutableGlyphs;
bool forceAutoHint;
};

class Controls
{
// Methods:
void Reset();
void Set(uint, bool);
bool IsDown(uint) const;
bool IsPressed(uint, const Controls&) const;

// Properties:
uint buttons;
float yaw;
float pitch;
VariantMap extraData;
};

class NetworkPriority
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
float basePriority;
float distanceFactor;
float minPriority;
bool alwaysUpdateOwner;
};

class Connection
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SendMessage(int, bool, bool, const VectorBuffer&, uint = 0);
void SendRemoteEvent(const String&, bool, const VariantMap& = VariantMap ( ));
void SendRemoteEvent(Node, const String&, bool, const VariantMap& = VariantMap ( ));
void Disconnect(int = 0);
String ToString() const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
Scene scene;
bool logStatistics;
/* (readonly) */
bool client;
/* (readonly) */
bool connected;
/* (readonly) */
bool connectPending;
/* (readonly) */
bool sceneLoaded;
/* (readonly) */
String address;
/* (readonly) */
uint16 port;
/* (readonly) */
uint numDownloads;
/* (readonly) */
String downloadName;
/* (readonly) */
float downloadProgress;
Vector3 position;
Controls controls;
VariantMap identity;
};

class HttpRequest
{
// Methods:
Array<uint8> Read(uint);
int ReadInt();
int16 ReadShort();
int8 ReadByte();
uint ReadUInt();
uint16 ReadUShort();
uint8 ReadUByte();
bool ReadBool();
float ReadFloat();
IntRect ReadIntRect();
IntVector2 ReadIntVector2();
Vector2 ReadVector2();
Vector3 ReadVector3();
Vector3 ReadPackedVector3(float);
Vector4 ReadVector4();
Quaternion ReadQuaternion();
Quaternion ReadPackedQuaternion();
Color ReadColor();
BoundingBox ReadBoundingBox();
String ReadString();
String ReadFileID();
StringHash ReadStringHash();
ShortStringHash ReadShortStringHash();
Variant ReadVariant();
VariantMap ReadVariantMap();
uint ReadVLE();
uint ReadNetID();
String ReadLine();
uint Seek(uint);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
String name;
/* (readonly) */
uint checksum;
/* (readonly) */
uint position;
/* (readonly) */
uint size;
/* (readonly) */
bool eof;
/* (readonly) */
String url;
/* (readonly) */
String verb;
/* (readonly) */
String error;
/* (readonly) */
HttpRequestState state;
/* (readonly) */
uint availableSize;
/* (readonly) */
bool open;
};

class Network
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Connect(const String&, uint16, Scene, const VariantMap& = VariantMap ( ));
void Disconnect(int = 0);
bool StartServer(uint16);
void StopServer();
void BroadcastMessage(int, bool, bool, const VectorBuffer&, uint = 0);
void BroadcastRemoteEvent(const String&, bool, const VariantMap& = VariantMap ( ));
void BroadcastRemoteEvent(Scene, const String&, bool, const VariantMap& = VariantMap ( ));
void BroadcastRemoteEvent(Node, const String&, bool, const VariantMap& = VariantMap ( ));
void RegisterRemoteEvent(const String&) const;
void UnregisterRemoteEvent(const String&) const;
void UnregisterAllRemoteEvents();
bool CheckRemoteEvent(const String&) const;
HttpRequest MakeHttpRequest(const String&, const String& = String ( ), Array<String> = null, const String& = String ( ));

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
int updateFps;
String packageCacheDir;
/* (readonly) */
bool serverRunning;
/* (readonly) */
Connection serverConnection;
/* (readonly) */
Array<Connection> clientConnections;
};

class CollisionShape
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
void SetBox(const Vector3&, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetSphere(float, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetStaticPlane(const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetCylinder(float, float, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetCapsule(float, float, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetCone(float, float, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetTriangleMesh(Model, uint = 0, const Vector3& = Vector3 ( 1 , 1 , 1 ), const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetConvexHull(Model, uint = 0, const Vector3& = Vector3 ( 1 , 1 , 1 ), const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetCustomConvexHull(CustomGeometry, const Vector3& = Vector3 ( 1 , 1 , 1 ), const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetTerrain();
void SetTransform(const Vector3&, const Quaternion&);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
ShapeType shapeType;
Vector3 size;
Vector3 position;
Quaternion rotation;
float margin;
Model model;
uint lodLevel;
/* (readonly) */
BoundingBox worldBoundingBox;
};

class RigidBody
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
void SetTransform(const Vector3&, const Quaternion&);
void SetCollisionLayerAndMask(uint, uint);
void ApplyForce(const Vector3&);
void ApplyForce(const Vector3&, const Vector3&);
void ApplyTorque(const Vector3&);
void ApplyImpulse(const Vector3&);
void ApplyImpulse(const Vector3&, const Vector3&);
void ApplyTorqueImpulse(const Vector3&);
void ResetForces();
void Activate();
void ReAddBodyToWorld();
Vector3 GetVelocityAtPoint(const Vector3&) const;

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
float mass;
Vector3 position;
Quaternion rotation;
Vector3 linearVelocity;
Vector3 linearFactor;
float linearRestThreshold;
float linearDamping;
Vector3 angularVelocity;
Vector3 angularFactor;
float angularRestThreshold;
float angularDamping;
float friction;
Vector3 anisotropicFriction;
float rollingFriction;
float restitution;
float contactProcessingThreshold;
float ccdRadius;
float ccdMotionThreshold;
bool useGravity;
Vector3 gravityOverride;
/* (readonly) */
Vector3 centerOfMass;
bool phantom;
bool kinematic;
/* (readonly) */
bool active;
uint collisionLayer;
uint collisionMask;
CollisionEventMode collisionEventMode;
/* (readonly) */
Array<RigidBody> collidingBodies;
};

class Constraint
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
ConstraintType constraintType;
Vector3 position;
Quaternion rotation;
/* (writeonly) */
Vector3 axis;
Vector3 otherPosition;
Quaternion otherRotation;
/* (writeonly) */
Vector3 otherAxis;
Vector3 worldPosition;
Vector2 highLimit;
Vector2 lowLimit;
float erp;
float cfm;
bool disableCollision;
/* (readonly) */
RigidBody ownBody;
RigidBody otherBody;
};

class PhysicsRaycastResult
{

// Properties:
/* (readonly) */
RigidBody body;
Vector3 position;
Vector3 normal;
float distance;
};

class PhysicsWorld
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
void Update(float);
void UpdateCollisions();
Array<PhysicsRaycastResult> Raycast(const Ray&, float = M_INFINITY, uint = 0xffff);
PhysicsRaycastResult RaycastSingle(const Ray&, float = M_INFINITY, uint = 0xffff);
PhysicsRaycastResult SphereCast(const Ray&, float, float = M_INFINITY, uint = 0xffff);
Array<RigidBody> GetRigidBodies(const Sphere&, uint = 0xffff);
Array<RigidBody> GetRigidBodies(const BoundingBox&, uint = 0xffff);
Array<RigidBody> GetRigidBodies(RigidBody);
void DrawDebugGeometry(bool);
void RemoveCachedGeometry(Model);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
Vector3 gravity;
int numIterations;
int fps;
bool interpolation;
bool internalEdge;
bool splitImpulse;
};

class Navigable
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
bool recursive;
};

class NavigationMesh
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
bool Build();
bool Build(const BoundingBox&);
Vector3 FindNearestPoint();
Vector3 MoveAlongSurface();
Array<Vector3> FindPath(const Vector3&, const Vector3&, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
Vector3 GetRandomPoint();
Vector3 GetRandomPointInCircle(const Vector3&, float, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
float GetDistanceToWall(const Vector3&, float, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
Vector3 Raycast(const Vector3&, const Vector3&, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
void DrawDebugGeometry(bool);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
int tileSize;
float cellSize;
float cellHeight;
float agentHeight;
float agentRadius;
float agentMaxClimb;
float agentMaxSlope;
float regionMinSize;
float regionMergeSize;
float edgeMaxLength;
float edgeMaxError;
float detailSampleDistance;
float detailSampleMaxError;
Vector3 padding;
/* (readonly) */
bool initialized;
/* (readonly) */
BoundingBox boundingBox;
/* (readonly) */
BoundingBox worldBoundingBox;
/* (readonly) */
IntVector2 numTiles;
};

class OffMeshConnection
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
Node endPoint;
float radius;
bool bidirectional;
};

class ScriptFile
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File);
bool Save(File) const;
bool Execute(const String&, const Array<Variant>);
void DelayedExecute(float, bool, const String&, const Array<Variant>);
void DelayedExecute(float, bool, const String&);
void ClearDelayedExecute(const String& = String ( ));

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
String name;
/* (readonly) */
uint memoryUse;
/* (readonly) */
uint useTimer;
/* (readonly) */
bool compiled;
};

class ScriptObject
{
};

class ScriptInstance
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Load(File, bool = false);
bool Save(File) const;
bool LoadXML(const XMLElement&, bool = false);
bool SaveXML(XMLElement&) const;
void ApplyAttributes();
bool SetAttribute(const String&, const Variant&);
void ResetToDefault();
void RemoveInstanceDefault();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
void Remove();
void MarkNetworkUpdate() const;
void DrawDebugGeometry(DebugRenderer, bool);
bool CreateObject(ScriptFile, const String&);
bool Execute(const String&, const Array<Variant>);
bool Execute(const String&);
void DelayedExecute(float, bool, const String&, const Array<Variant>);
void DelayedExecute(float, bool, const String&);
void ClearDelayedExecute(const String& = String ( ));

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
/* (readonly) */
uint numAttributes;
Array<Variant> attributes;
/* (readonly) */
Array<Variant> attributeDefaults;
/* (readonly) */
Array<AttributeInfo> attributeInfos;
bool temporary;
bool enabled;
/* (readonly) */
bool enabledEffective;
/* (readonly) */
uint id;
/* (readonly) */
Node node;
int fixedUpdateFps;
ScriptFile scriptFile;
/* (readonly) */
ScriptObject object;
String className;
};

class Script
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool Execute(const String&);
void DumpAPI(DumpMode = DOXYGEN);

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
ScriptFile defaultScriptFile;
Scene defaultScene;
};

class Console
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void Toggle();
void UpdateElements();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
XMLFile defaultStyle;
bool visible;
uint numRows;
uint numHistoryRows;
/* (readonly) */
uint historyPosition;
/* (readonly) */
Array<String> historyRow;
/* (readonly) */
BorderImage background;
/* (readonly) */
LineEdit lineEdit;
};

class DebugHud
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void Toggle(uint);
void ToggleAll();
void SetAppStats(const String&, const Variant&);
void SetAppStats(const String&, const String&);
void ResetAppStats(const String&);
void ClearAppStats();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
XMLFile defaultStyle;
uint mode;
uint profilerMaxDepth;
float profilerInterval;
bool useRendererStats;
/* (readonly) */
Text statsText;
/* (readonly) */
Text modeText;
/* (readonly) */
Text profilerText;
};

class Engine
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void RunFrame();
void Exit();
void DumpProfiler();
void DumpResources();
void DumpMemory();
Console CreateConsole();
DebugHud CreateDebugHud();

// Properties:
/* (readonly) */
int refs;
/* (readonly) */
int weakRefs;
/* (readonly) */
ShortStringHash type;
/* (readonly) */
ShortStringHash baseType;
/* (readonly) */
String typeName;
/* (readonly) */
String category;
int minFps;
int maxFps;
int timeStepSmoothing;
int maxInactiveFps;
bool pauseMinimized;
bool autoExit;
/* (readonly) */
bool initialized;
/* (readonly) */
bool exiting;
/* (readonly) */
bool headless;
};

// Global functions
bool Equals(float, float);
float Sin(float);
float Cos(float);
float Tan(float);
float Asin(float);
float Acos(float);
float Atan(float);
float Atan2(float, float);
float Abs(float);
float Sign(float);
float Sqrt(float);
float Pow(float, float);
float Min(float, float);
int Min(int, int);
float Max(float, float);
int Max(int, int);
float Clamp(float, float, float);
float SmoothStep(float, float, float);
int Clamp(int, int, int);
float Lerp(float, float, float);
float Mod(float, float);
float Floor(float);
float Ceil(float);
float Random();
float Random(float);
float Random(float, float);
int RandomInt();
int RandomInt(int);
int RandomInt(int, int);
void SetRandomSeed(uint);
uint GetRandomSeed();
String ToStringHex(int);
String Join(Array<String>&, const String&);
bool IsDigit(uint);
bool IsAlpha(uint);
void ErrorDialog(const String&, const String&);
void OpenConsoleWindow();
String GetConsoleInput();
Array<String> GetArguments();
String GetPlatform();
uint GetNumPhysicalCPUs();
uint GetNumLogicalCPUs();
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SubscribeToEvent(const String&, const String&);
void SubscribeToEvent(Object, const String&, const String&);
void UnsubscribeFromEvent(const String&);
void UnsubscribeFromEvent(Object, const String&);
void UnsubscribeFromEvents(Object);
void UnsubscribeFromAllEvents();
void UnsubscribeFromAllEventsExcept(Array<String>);
Object GetEventSender();
const String& GetTypeName(ShortStringHash);
void Print(const String&, bool = false);
void Print(int, bool = false);
void Print(uint, bool = false);
void Print(float, bool = false);
void Print(bool, bool = false);
void Print(const Variant&, bool = false);
void PrintCallStack(bool = false);
String GetPath(const String&);
String GetFileName(const String&);
String GetExtension(const String&, bool = true);
String GetFileNameAndExtension(const String&, bool = false);
String ReplaceExtension(const String&, const String&);
String AddTrailingSlash(const String&);
String RemoveTrailingSlash(const String&);
String GetParentPath(const String&);
String GetInternalPath(const String&);
bool IsAbsolutePath(const String&);
Array<String> GetObjectCategories();
Array<String> GetObjectsByCategory(const String&);
uint GetAlphaFormat();
uint GetLuminanceFormat();
uint GetLuminanceAlphaFormat();
uint GetRGBFormat();
uint GetRGBAFormat();
uint GetRGBA16Format();
uint GetRGBAFloat16Format();
uint GetRGBAFloat32Format();
uint GetRG16Format();
uint GetRGFloat16Format();
uint GetRGFloat32Format();
uint GetFloat16Format();
uint GetFloat32Format();
uint GetDepthStencilFormat();
uint GetFormat(const String&);
String GetTextureUnitName(TextureUnit);
void MarkNetworkUpdate();
void DelayedExecute(float, bool, const String&, const Array<Variant>);
void DelayedExecute(float, bool, const String&);
void ClearDelayedExecute(const String& = String ( ));
void Remove();

// Global properties
Time time;
Log log;
FileSystem fileSystem;
ResourceCache resourceCache;
ResourceCache cache;
Node node;
Scene scene;
DebugRenderer debugRenderer;
Octree octree;
Graphics graphics;
Renderer renderer;
Input input;
Audio audio;
UI ui;
Network network;
PhysicsWorld physicsWorld;
ScriptFile scriptFile;
ScriptInstance self;
Script script;
Console console;
DebugHud debugHud;
Engine engine;

// Global constants
float M_INFINITY;
float M_EPSILON;
float M_LARGE_EPSILON;
float M_LARGE_VALUE;
float M_DEGTORAD;
float M_DEGTORAD_2;
float M_RADTODEG;
float M_PI;
float M_HALF_PI;
int M_MIN_INT;
int M_MAX_INT;
uint M_MIN_UNSIGNED;
uint M_MAX_UNSIGNED;
int LOG_DEBUG;
int LOG_INFO;
int LOG_WARNING;
int LOG_ERROR;
int LOG_NONE;
uint SCAN_FILES;
uint SCAN_DIRS;
uint SCAN_HIDDEN;
uint AM_FILE;
uint AM_NET;
uint AM_DEFAULT;
uint AM_LATESTDATA;
uint AM_NOEDIT;
uint AM_NODEID;
uint AM_COMPONENTID;
uint AM_NODEIDVECTOR;
uint FIRST_REPLICATED_ID;
uint LAST_REPLICATED_ID;
uint FIRST_LOCAL_ID;
uint LAST_LOCAL_ID;
uint VO_NONE;
uint VO_LOW_MATERIAL_QUALITY;
uint VO_DISABLE_SHADOWS;
uint VO_DISABLE_OCCLUSION;
uint DRAWABLE_GEOMETRY;
uint DRAWABLE_LIGHT;
uint DRAWABLE_ZONE;
uint DRAWABLE_ANY;
uint DEFAULT_VIEWMASK;
uint DEFAULT_LIGHTMASK;
int QUALITY_LOW;
int QUALITY_MEDIUM;
int QUALITY_HIGH;
int SHADOWQUALITY_LOW_16BIT;
int SHADOWQUALITY_LOW_24BIT;
int SHADOWQUALITY_HIGH_16BIT;
int SHADOWQUALITY_HIGH_24BIT;
int MOUSEB_LEFT;
int MOUSEB_RIGHT;
int MOUSEB_MIDDLE;
int QUAL_SHIFT;
int QUAL_CTRL;
int QUAL_ALT;
int QUAL_ANY;
int KEY_BACKSPACE;
int KEY_TAB;
int KEY_RETURN;
int KEY_RETURN2;
int KEY_KP_ENTER;
int KEY_PAUSE;
int KEY_CAPSLOCK;
int KEY_ESC;
int KEY_SPACE;
int KEY_PAGEUP;
int KEY_PAGEDOWN;
int KEY_END;
int KEY_HOME;
int KEY_LEFT;
int KEY_UP;
int KEY_RIGHT;
int KEY_DOWN;
int KEY_INSERT;
int KEY_DELETE;
int KEY_LWIN;
int KEY_RWIN;
int KEY_APPS;
int KEY_NUMPAD0;
int KEY_NUMPAD1;
int KEY_NUMPAD2;
int KEY_NUMPAD3;
int KEY_NUMPAD4;
int KEY_NUMPAD5;
int KEY_NUMPAD6;
int KEY_NUMPAD7;
int KEY_NUMPAD8;
int KEY_NUMPAD9;
int KEY_MULTIPLY;
int KEY_ADD;
int KEY_SUBTRACT;
int KEY_DECIMAL;
int KEY_DIVIDE;
int KEY_F1;
int KEY_F2;
int KEY_F3;
int KEY_F4;
int KEY_F5;
int KEY_F6;
int KEY_F7;
int KEY_F8;
int KEY_F9;
int KEY_F10;
int KEY_F11;
int KEY_F12;
int KEY_F13;
int KEY_F14;
int KEY_F15;
int KEY_F16;
int KEY_F17;
int KEY_F18;
int KEY_F19;
int KEY_F20;
int KEY_F21;
int KEY_F22;
int KEY_F23;
int KEY_F24;
int KEY_NUMLOCK;
int KEY_SCROLLLOCK;
int KEY_LSHIFT;
int KEY_RSHIFT;
int KEY_LCTRL;
int KEY_RCTRL;
int KEY_LALT;
int KEY_RALT;
int HAT_CENTER;
int HAT_UP;
int HAT_RIGHT;
int HAT_DOWN;
int HAT_LEFT;
uint DD_DISABLED;
uint DD_SOURCE;
uint DD_TARGET;
uint DD_SOURCE_AND_TARGET;
uint DEBUGHUD_SHOW_NONE;
uint DEBUGHUD_SHOW_STATS;
uint DEBUGHUD_SHOW_MODE;
uint DEBUGHUD_SHOW_PROFILER;
uint DEBUGHUD_SHOW_ALL;
