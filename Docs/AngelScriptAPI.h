// Script API header intended to be 'force included' in IDE for AngelScript content assist / code completion

#define int8 signed char
#define int16 signed short
#define int64 long
#define uint8 unsigned char
#define uint16 unsigned short
#define uint64 unsigned long
#define null 0

// Classes

class AnimatedModel
{
// Methods:
AnimationState AddAnimationState(Animation);
void ApplyAttributes();
void ApplyMaterialList(const String& = String ( ));
void DrawDebugGeometry(DebugRenderer, bool);
AnimationState GetAnimationState(Animation) const;
AnimationState GetAnimationState(uint) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
float GetMorphWeight(uint) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllAnimationStates();
void RemoveAnimationState(Animation);
void RemoveAnimationState(AnimationState);
void RemoveAnimationState(const String&);
void RemoveAnimationState(uint);
void RemoveInstanceDefault();
void ResetMorphWeights();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetMorphWeight(uint, float);

// Properties:
float animationLodBias;
/* readonly */
Array<AnimationState> animationStates;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
float lodBias;
/* writeonly */
Material material;
Array<Material> materials;
uint maxLights;
Model model;
/* readonly */
Array<String> morphNames;
Array<float> morphWeights;
/* readonly */
Node node;
/* readonly */
uint numAnimationStates;
/* readonly */
uint numAttributes;
/* readonly */
uint numGeometries;
/* readonly */
uint numMorphs;
bool occludee;
bool occluder;
/* readonly */
int refs;
float shadowDistance;
uint shadowMask;
/* readonly */
Skeleton skeleton;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool updateInvisible;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
/* readonly */
Zone zone;
uint zoneMask;
};

class AnimatedSprite2D
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetFlip(bool, bool);

// Properties:
Animation2D animation;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
BlendMode blendMode;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
Color color;
CycleMode cycleMode;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
bool flipX;
bool flipY;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
float lodBias;
Material material;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
bool occludee;
bool occluder;
/* readonly */
int refs;
float shadowDistance;
uint shadowMask;
float speed;
Sprite2D sprite;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
float zValue;
uint zoneMask;
};

class Animation
{
// Methods:
void AddTrigger(float, bool, const Variant&);
bool Load(File);
void RemoveAllTriggers();
void RemoveTrigger(uint);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String animationName;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
float length;
/* readonly */
uint memoryUse;
String name;
/* readonly */
uint numTracks;
uint numTriggers;
/* readonly */
int refs;
/* readonly */
Array<AnimationTriggerPoint> triggers;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class Animation2D
{
// Methods:
Sprite GetFrameSprite(uint) const;
Sprite GetFrameSpriteByTime(float) const;
bool Load(File);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
uint memoryUse;
String name;
/* readonly */
uint numFrames;
/* readonly */
int refs;
/* readonly */
float totalTime;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class AnimationController
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
bool Fade(const String&, float, float);
bool FadeOthers(const String&, float, float);
AnimationState GetAnimationState(StringHash) const;
AnimationState GetAnimationState(const String&) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
float GetAutoFade(const String&) const;
float GetFadeTarget(const String&) const;
uint8 GetLayer(const String&) const;
float GetLength(const String&) const;
bool GetLooped(const String&) const;
float GetSpeed(const String&) const;
float GetTime(const String&) const;
float GetWeight(const String&) const;
bool IsFadingIn(const String&) const;
bool IsFadingOut(const String&) const;
bool IsPlaying(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
bool Play(const String&, uint8, bool, float = 0.0f);
bool PlayExclusive(const String&, uint8, bool, float = 0.0f);
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
bool SetAutoFade(const String&, float);
bool SetLayer(const String&, uint8);
bool SetLooped(const String&, bool);
bool SetSpeed(const String&, float);
bool SetStartBone(const String&, const String&);
bool SetTime(const String&, float);
bool SetWeight(const String&, float);
void Stop(const String&, float = 0.0f);
void StopAll(float = 0.0f);
void StopLayer(uint8, float = 0.0f);
const String& GetStartBone(const String&) const;

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
int refs;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class AnimationState
{
// Methods:
void AddTime(float);
void AddWeight(float);
void Apply();
float GetBoneWeight(StringHash) const;
float GetBoneWeight(uint) const;
uint GetTrackIndex(StringHash) const;
uint GetTrackIndex(const String&) const;
void SetBoneWeight(StringHash, float, bool = false);
void SetBoneWeight(const String&, float, bool = false);
void SetBoneWeight(uint, float, bool = false);

// Properties:
/* readonly */
Animation animation;
Array<float> boneWeights;
/* readonly */
bool enabled;
uint8 layer;
/* readonly */
float length;
bool looped;
/* readonly */
AnimatedModel model;
/* readonly */
Node node;
/* readonly */
int refs;
Bone startBone;
float time;
/* readonly */
int weakRefs;
float weight;
};

class AnimationTriggerPoint
{

// Properties:
Variant data;
float time;
};

template <class T> class Array
{
// Methods:
void Clear();
void Erase(uint);
int Find(const T&) const;
int Find(uint, const T&) const;
void Insert(uint, const T&);
void Pop();
void Push(const T&);
void Resize(uint);
void Reverse();
void Sort();
void Sort(uint, uint);
void SortReverse();
void SortReverse(uint, uint);

// Properties:
/* readonly */
bool empty;
uint length;
};

class AttributeInfo
{

// Properties:
Variant defaultValue;
/* readonly */
Array<String> enumNames;
uint mode;
String name;
VariantType type;
};

class Audio
{
// Methods:
bool Play();
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetMode(int, int, bool, bool = true);
void Stop();

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
bool initialized;
/* readonly */
bool interpolation;
SoundListener listener;
Array<float> masterGain;
/* readonly */
int mixRate;
/* readonly */
bool playing;
/* readonly */
int refs;
/* readonly */
uint sampleSize;
/* readonly */
bool stereo;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class BiasParameters
{

// Properties:
float constantBias;
float slopeScaledBias;
};

class Billboard
{

// Properties:
Color color;
bool enabled;
Vector3 position;
float rotation;
Vector2 size;
Rect uv;
};

class BillboardSet
{
// Methods:
void ApplyAttributes();
void Commit();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
float animationLodBias;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
Array<Billboard> billboards;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
bool faceCamera;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
float lodBias;
Material material;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
uint numBillboards;
bool occludee;
bool occluder;
/* readonly */
int refs;
bool relative;
bool scaled;
float shadowDistance;
uint shadowMask;
bool sorted;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
/* readonly */
Zone zone;
uint zoneMask;
};

class Bone
{

// Properties:
bool animated;
BoundingBox boundingBox;
Vector3 initialPosition;
Quaternion initialRotation;
Vector3 initialScale;
String name;
Node node;
float radius;
};

class BorderImage
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
BlendMode blendMode;
IntRect border;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool focus;
FocusMode focusMode;
int height;
HorizontalAlignment horizontalAlignment;
IntVector2 hoverOffset;
/* readonly */
bool hovering;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
float opacity;
UIElement parent;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool selected;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class BoundingBox
{
// Methods:
void Clear();
void Clip(const BoundingBox&);
void Define(const BoundingBox&);
void Define(const Frustum&);
void Define(const Polyhedron&);
void Define(const Sphere&);
void Define(const Vector3&);
void Define(const Vector3&, const Vector3&);
void Define(float, float);
Intersection IsInside(const BoundingBox&) const;
Intersection IsInside(const Sphere&) const;
Intersection IsInside(const Vector3&) const;
void Merge(const BoundingBox&);
void Merge(const Frustum&);
void Merge(const Polyhedron&);
void Merge(const Sphere&);
void Merge(const Vector3&);
Rect Projected(const Matrix4&) const;
String ToString() const;
void Transform(const Matrix3&);
void Transform(const Matrix3x4&);
BoundingBox Transformed(const Matrix3&) const;
BoundingBox Transformed(const Matrix3x4&) const;

// Properties:
/* readonly */
Vector3 center;
bool defined;
/* readonly */
Vector3 halfSize;
Vector3 max;
Vector3 min;
/* readonly */
Vector3 size;
};

class Button
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetPressedChildOffset(int, int);
void SetPressedOffset(int, int);
void SetRepeat(float, float);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
BlendMode blendMode;
IntRect border;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool focus;
FocusMode focusMode;
int height;
HorizontalAlignment horizontalAlignment;
IntVector2 hoverOffset;
/* readonly */
bool hovering;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
float opacity;
UIElement parent;
IntVector2 position;
/* readonly */
bool pressed;
IntVector2 pressedChildOffset;
IntVector2 pressedOffset;
int priority;
/* readonly */
int refs;
float repeatDelay;
float repeatRate;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool selected;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class Camera
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
float GetDistance(const Vector3&) const;
float GetDistanceSquared(const Vector3&) const;
Ray GetScreenRay(float, float) const;
Frustum GetSplitFrustum(float, float) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
Vector3 ScreenToWorldPoint(const Vector3&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetOrthoSize(const Vector2&);
Vector2 WorldToScreenPoint(const Vector3&) const;

// Properties:
float aspectRatio;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool autoAspectRatio;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
Plane clipPlane;
/* readonly */
Matrix3x4 effectiveWorldTransform;
bool enabled;
/* readonly */
bool enabledEffective;
float farClip;
FillMode fillMode;
float fov;
/* readonly */
Frustum frustum;
/* readonly */
float halfViewSize;
/* readonly */
uint id;
float lodBias;
float nearClip;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
float orthoSize;
bool orthographic;
/* readonly */
Matrix4 projection;
Vector2 projectionOffset;
Plane reflectionPlane;
/* readonly */
int refs;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useClipping;
bool useReflection;
/* readonly */
Matrix3x4 view;
uint viewMask;
uint viewOverrideFlags;
/* readonly */
Frustum viewSpaceFrustum;
/* readonly */
int weakRefs;
float zoom;
};

class CascadeParameters
{

// Properties:
float biasAutoAdjust;
float fadeStart;
float split1;
float split2;
float split3;
float split4;
};

class CheckBox
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetCheckedOffset(int, int);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
BlendMode blendMode;
IntRect border;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
bool checked;
IntVector2 checkedOffset;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool focus;
FocusMode focusMode;
int height;
HorizontalAlignment horizontalAlignment;
IntVector2 hoverOffset;
/* readonly */
bool hovering;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
float opacity;
UIElement parent;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool selected;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class CollisionBox2D
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetCenter(float, float);
void SetSize(float, float);

// Properties:
float angle;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
int categoryBits;
Vector2 center;
float density;
bool enabled;
/* readonly */
bool enabledEffective;
float friction;
int groupIndex;
/* readonly */
uint id;
/* readonly */
float inertia;
int maskBits;
/* readonly */
float mass;
/* readonly */
Vector2 massCenter;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
int refs;
float restitution;
bool sensor;
Vector2 size;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class CollisionChain2D
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
Array<Vector2> GetVertices() const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetVertex(uint, const Vector2&);
void SetVertices(Array<Vector2>);
const Vector2& GetVertex(uint) const;

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
int categoryBits;
float density;
bool enabled;
/* readonly */
bool enabledEffective;
float friction;
int groupIndex;
/* readonly */
uint id;
/* readonly */
float inertia;
bool loop;
int maskBits;
/* readonly */
float mass;
/* readonly */
Vector2 massCenter;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
int refs;
float restitution;
bool sensor;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint vertexCount;
/* readonly */
int weakRefs;
};

class CollisionCircle2D
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetCenter(float, float);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
int categoryBits;
Vector2 center;
float density;
bool enabled;
/* readonly */
bool enabledEffective;
float friction;
int groupIndex;
/* readonly */
uint id;
/* readonly */
float inertia;
int maskBits;
/* readonly */
float mass;
/* readonly */
Vector2 massCenter;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
float radius;
/* readonly */
int refs;
float restitution;
bool sensor;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class CollisionEdge2D
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetVertices(const Vector2&, const Vector2&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
int categoryBits;
float density;
bool enabled;
/* readonly */
bool enabledEffective;
float friction;
int groupIndex;
/* readonly */
uint id;
/* readonly */
float inertia;
int maskBits;
/* readonly */
float mass;
/* readonly */
Vector2 massCenter;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
int refs;
float restitution;
bool sensor;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
Vector2 vertex1;
Vector2 vertex2;
/* readonly */
int weakRefs;
};

class CollisionPolygon2D
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
Array<Vector2> GetVertices() const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetVertex(uint, const Vector2&);
void SetVertices(Array<Vector2>);
const Vector2& GetVertex(uint) const;

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
int categoryBits;
float density;
bool enabled;
/* readonly */
bool enabledEffective;
float friction;
int groupIndex;
/* readonly */
uint id;
/* readonly */
float inertia;
int maskBits;
/* readonly */
float mass;
/* readonly */
Vector2 massCenter;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
int refs;
float restitution;
bool sensor;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint vertexCount;
/* readonly */
int weakRefs;
};

class CollisionShape
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetBox(const Vector3&, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetCapsule(float, float, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetCone(float, float, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetConvexHull(Model, uint = 0, const Vector3& = Vector3 ( 1 , 1 , 1 ), const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetCustomConvexHull(CustomGeometry, const Vector3& = Vector3 ( 1 , 1 , 1 ), const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetCylinder(float, float, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetSphere(float, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetStaticPlane(const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetTerrain();
void SetTransform(const Vector3&, const Quaternion&);
void SetTriangleMesh(Model, uint = 0, const Vector3& = Vector3 ( 1 , 1 , 1 ), const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
uint lodLevel;
float margin;
Model model;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
Vector3 position;
/* readonly */
int refs;
Quaternion rotation;
ShapeType shapeType;
Vector3 size;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
};

class CollisionShape2D
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
int categoryBits;
float density;
bool enabled;
/* readonly */
bool enabledEffective;
float friction;
int groupIndex;
/* readonly */
uint id;
/* readonly */
float inertia;
int maskBits;
/* readonly */
float mass;
/* readonly */
Vector2 massCenter;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
int refs;
float restitution;
bool sensor;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Color
{
// Methods:
Color Abs() const;
float Average() const;
float Chroma() const;
void Clip(bool);
bool Equals() const;
void FromHSL(float, float, float, float);
void FromHSV(float, float, float, float);
float Hue() const;
void Invert(bool);
Color Lerp(const Color&, float) const;
float Lightness() const;
float Luma() const;
float MaxRGB() const;
float MinRGB() const;
float Range() const;
float SaturationHSL() const;
float SaturationHSV() const;
float SumRGB() const;
Vector3 ToHSL() const;
Vector3 ToHSV() const;
String ToString() const;
uint ToUInt() const;
float Value() const;

// Properties:
float a;
float b;
/* readonly */
Array<float> data;
float g;
float r;
/* readonly */
Vector3 rgb;
/* readonly */
Vector4 rgba;
};

class ColorFrame
{

// Properties:
Color color;
float time;
};

class Component
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
int refs;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Connection
{
// Methods:
void Disconnect(int = 0);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SendMessage(int, bool, bool, const VectorBuffer&, uint = 0);
void SendRemoteEvent(Node, const String&, bool, const VariantMap& = VariantMap ( ));
void SendRemoteEvent(const String&, bool, const VariantMap& = VariantMap ( ));
String ToString() const;

// Properties:
/* readonly */
String address;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
bool client;
/* readonly */
bool connectPending;
/* readonly */
bool connected;
Controls controls;
/* readonly */
String downloadName;
/* readonly */
float downloadProgress;
VariantMap identity;
bool logStatistics;
/* readonly */
uint numDownloads;
/* readonly */
uint16 port;
Vector3 position;
/* readonly */
int refs;
Scene scene;
/* readonly */
bool sceneLoaded;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Console
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void Toggle();
void UpdateElements();

// Properties:
bool autoVisibleOnError;
/* readonly */
BorderImage background;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
XMLFile defaultStyle;
/* readonly */
uint historyPosition;
/* readonly */
Array<String> historyRow;
/* readonly */
LineEdit lineEdit;
uint numHistoryRows;
uint numRows;
/* readonly */
int refs;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool visible;
/* readonly */
int weakRefs;
};

class Constraint
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* writeonly */
Vector3 axis;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
float cfm;
ConstraintType constraintType;
bool disableCollision;
bool enabled;
/* readonly */
bool enabledEffective;
float erp;
Vector2 highLimit;
/* readonly */
uint id;
Vector2 lowLimit;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* writeonly */
Vector3 otherAxis;
RigidBody otherBody;
Vector3 otherPosition;
Quaternion otherRotation;
/* readonly */
RigidBody ownBody;
Vector3 position;
/* readonly */
int refs;
Quaternion rotation;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
Vector3 worldPosition;
};

class Controls
{
// Methods:
bool IsDown(uint) const;
bool IsPressed(uint, const Controls&) const;
void Reset();
void Set(uint, bool);

// Properties:
uint buttons;
VariantMap extraData;
float pitch;
float yaw;
};

class Cursor
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DefineShape(CursorShape, Texture, const IntRect&, const IntVector2&);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
BlendMode blendMode;
IntRect border;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool focus;
FocusMode focusMode;
int height;
HorizontalAlignment horizontalAlignment;
IntVector2 hoverOffset;
/* readonly */
bool hovering;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
float opacity;
UIElement parent;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool selected;
CursorShape shape;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
bool useSystemShapes;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class CustomGeometry
{
// Methods:
void ApplyAttributes();
void BeginGeometry(uint, PrimitiveType);
void Clear();
void Commit();
void DefineColor(const Color&);
void DefineNormal(const Vector3&);
void DefineTangent(const Vector4&);
void DefineTexCoord(const Vector2&);
void DefineVertex(const Vector3&);
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
float lodBias;
/* writeonly */
Material material;
Array<Material> materials;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
uint numGeometries;
bool occludee;
bool occluder;
/* readonly */
int refs;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
/* readonly */
Zone zone;
uint zoneMask;
};

class DebugHud
{
// Methods:
void ClearAppStats();
void ResetAppStats(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAppStats(const String&, const String&);
void SetAppStats(const String&, const Variant&);
void Toggle(uint);
void ToggleAll();

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
XMLFile defaultStyle;
uint mode;
/* readonly */
Text modeText;
float profilerInterval;
uint profilerMaxDepth;
/* readonly */
Text profilerText;
/* readonly */
int refs;
/* readonly */
Text statsText;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useRendererStats;
/* readonly */
int weakRefs;
};

class DebugRenderer
{
// Methods:
void AddBoundingBox(const BoundingBox&, const Color&, bool = true);
void AddFrustum(const Frustum&, const Color&, bool = true);
void AddLine(const Vector3&, const Vector3&, const Color&, bool = true);
void AddNode(Node, float = 1.0, bool = true);
void AddPolyhedron(const Polyhedron&, const Color&, bool = true);
void AddSkeleton(Skeleton, const Color&, bool = true);
void AddSphere(const Sphere&, const Color&, bool = true);
void AddTriangle(const Vector3&, const Vector3&, const Vector3&, const Color&, bool = true);
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
int refs;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class DecalSet
{
// Methods:
bool AddDecal(Drawable, const Vector3&, const Quaternion&, float, float, float, const Vector2&, const Vector2&, float = 0.0, float = 0.1, uint = 0xffffffff);
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllDecals();
void RemoveDecals(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
float lodBias;
Material material;
uint maxIndices;
uint maxLights;
uint maxVertices;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
uint numDecals;
/* readonly */
uint numIndices;
/* readonly */
uint numVertices;
bool occludee;
bool occluder;
/* readonly */
int refs;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
/* readonly */
Zone zone;
uint zoneMask;
};

class Deserializer
{
// Methods:
Array<uint8> Read(uint);
bool ReadBool();
BoundingBox ReadBoundingBox();
int8 ReadByte();
Color ReadColor();
String ReadFileID();
float ReadFloat();
int ReadInt();
IntRect ReadIntRect();
IntVector2 ReadIntVector2();
String ReadLine();
uint ReadNetID();
Quaternion ReadPackedQuaternion();
Vector3 ReadPackedVector3(float);
Quaternion ReadQuaternion();
int16 ReadShort();
ShortStringHash ReadShortStringHash();
String ReadString();
StringHash ReadStringHash();
uint8 ReadUByte();
uint ReadUInt();
uint16 ReadUShort();
uint ReadVLE();
Variant ReadVariant();
VariantMap ReadVariantMap();
Vector2 ReadVector2();
Vector3 ReadVector3();
Vector4 ReadVector4();
uint Seek(uint);

// Properties:
/* readonly */
uint checksum;
/* readonly */
bool eof;
/* readonly */
String name;
/* readonly */
uint position;
/* readonly */
uint size;
};

class Dictionary
{
// Methods:
void Clear();
void Erase(const String&);
bool Exists(const String&) const;
bool Get(const String&, void*) const;
bool Get(const String&, double&) const;
bool Get(const String&, int64&) const;
void Set(const String&, void*);
void Set(const String&, double&);
void Set(const String&, int64&);

// Properties:
/* readonly */
bool empty;
/* readonly */
Array<String> keys;
/* readonly */
uint length;
};

class Drawable
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
float lodBias;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
bool occludee;
bool occluder;
/* readonly */
int refs;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
uint zoneMask;
};

class Drawable2D
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
BlendMode blendMode;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
float lodBias;
Material material;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
bool occludee;
bool occluder;
/* readonly */
int refs;
float shadowDistance;
uint shadowMask;
Sprite2D sprite;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
float zValue;
uint zoneMask;
};

class DropDownList
{
// Methods:
void AddChild(UIElement);
void AddItem(UIElement);
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
Array<UIElement> GetItems() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
void InsertItem(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveAllItems();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveItem(UIElement);
void RemoveItem(uint);
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAccelerator(int, int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetPressedChildOffset(int, int);
void SetPressedOffset(int, int);
void SetRepeat(float, float);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);
UIElement getPopup() const;

// Properties:
/* readonly */
int acceleratorKey;
/* readonly */
int acceleratorQualifiers;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
BlendMode blendMode;
IntRect border;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool focus;
FocusMode focusMode;
int height;
HorizontalAlignment horizontalAlignment;
IntVector2 hoverOffset;
/* readonly */
bool hovering;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
/* readonly */
Array<UIElement> items;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
/* readonly */
ListView listView;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
/* readonly */
uint numItems;
float opacity;
UIElement parent;
/* readonly */
UIElement placeholder;
String placeholderText;
IntVector2 position;
/* readonly */
bool pressed;
IntVector2 pressedChildOffset;
IntVector2 pressedOffset;
int priority;
/* readonly */
int refs;
float repeatDelay;
float repeatRate;
bool resizePopup;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool selected;
/* readonly */
UIElement selectedItem;
uint selection;
bool showPopup;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class Engine
{
// Methods:
Console CreateConsole();
DebugHud CreateDebugHud();
void DumpMemory();
void DumpProfiler();
void DumpResources();
void Exit();
void RunFrame();
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
bool autoExit;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
bool exiting;
/* readonly */
bool headless;
/* readonly */
bool initialized;
int maxFps;
int maxInactiveFps;
int minFps;
bool pauseMinimized;
/* readonly */
int refs;
int timeStepSmoothing;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class File
{
// Methods:
void Close();
bool Open(const String&, FileMode = FILE_READ);
Array<uint8> Read(uint);
bool ReadBool();
BoundingBox ReadBoundingBox();
int8 ReadByte();
Color ReadColor();
String ReadFileID();
float ReadFloat();
int ReadInt();
IntRect ReadIntRect();
IntVector2 ReadIntVector2();
String ReadLine();
uint ReadNetID();
Quaternion ReadPackedQuaternion();
Vector3 ReadPackedVector3(float);
Quaternion ReadQuaternion();
int16 ReadShort();
ShortStringHash ReadShortStringHash();
String ReadString();
StringHash ReadStringHash();
uint8 ReadUByte();
uint ReadUInt();
uint16 ReadUShort();
uint ReadVLE();
Variant ReadVariant();
VariantMap ReadVariantMap();
Vector2 ReadVector2();
Vector3 ReadVector3();
Vector4 ReadVector4();
uint Seek(uint);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
uint Write(Array<uint8>);
bool WriteBool(bool);
bool WriteBoundingBox(const BoundingBox&);
bool WriteByte(int8);
bool WriteColor(const Color&);
bool WriteFileID(const String&);
bool WriteFloat(float);
bool WriteInt(int);
bool WriteIntRect(const IntRect&);
bool WriteIntVector2(const IntVector2&);
bool WriteLine(const String&);
bool WriteNetID(uint);
bool WritePackedQuaternion(const Quaternion&);
bool WritePackedVector3(const Vector3&, float);
bool WriteQuaternion(const Quaternion&);
bool WriteShort(int16);
bool WriteShortStringHash(const ShortStringHash&);
bool WriteString(const String&);
bool WriteStringHash(const StringHash&);
bool WriteUByte(uint8);
bool WriteUInt(uint);
bool WriteUShort(uint16);
bool WriteVLE(uint);
bool WriteVariant(const Variant&);
bool WriteVariantMap(const VariantMap&);
bool WriteVector2(const Vector2&);
bool WriteVector3(const Vector3&);
bool WriteVector4(const Vector4&);

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
uint checksum;
/* readonly */
bool eof;
/* readonly */
FileMode mode;
/* readonly */
String name;
/* readonly */
bool open;
/* readonly */
bool packaged;
/* readonly */
uint position;
/* readonly */
int refs;
/* readonly */
uint size;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class FileSelector
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetButtonTexts(const String&, const String&);
void SetFilters(Array<String>, uint);
void UpdateElements();

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
Button cancelButton;
/* readonly */
String category;
XMLFile defaultStyle;
bool directoryMode;
/* readonly */
ListView fileList;
String fileName;
/* readonly */
LineEdit fileNameEdit;
/* readonly */
String filter;
/* readonly */
uint filterIndex;
/* readonly */
DropDownList filterList;
/* readonly */
Button okButton;
String path;
/* readonly */
LineEdit pathEdit;
/* readonly */
int refs;
String title;
/* readonly */
Text titleText;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
/* readonly */
Window window;
};

class FileSystem
{
// Methods:
bool Copy(const String&, const String&);
bool CreateDir(const String&);
bool Delete(const String&);
bool DirExists(const String&) const;
bool FileExists(const String&) const;
uint GetLastModifiedTime(const String&) const;
bool Rename(const String&, const String&);
Array<String> ScanDir(const String&, const String&, uint, bool) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
int SystemCommand(const String&);
bool SystemOpen(const String&, const String&);
int SystemRun(const String&, Array<String>);

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
String currentDir;
/* readonly */
String programDir;
/* readonly */
int refs;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
String userDocumentsDir;
/* readonly */
int weakRefs;
};

class FocusParameters
{

// Properties:
bool autoSize;
bool focus;
float minView;
bool nonUniform;
float quantize;
};

class Font
{
// Methods:
bool Load(File);
bool Save(File) const;
bool SaveXML(File, int, bool = false);
bool SaveXML(const String&, int, bool = false);
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class Frustum
{
// Methods:
void Define(const BoundingBox&, const Matrix3x4&);
void Define(const Vector3&, const Vector3&, const Matrix3x4&);
void Define(float, float, float, float, float, const Matrix3x4&);
void DefineOrtho(float, float, float, float, float, const Matrix3x4&);
float Distance(const Vector3&) const;
Intersection IsInside(const BoundingBox&);
Intersection IsInside(const Sphere&);
Intersection IsInside(const Vector3&);
void Transform(const Matrix3&);
void Transform(const Matrix3x4&);
Frustum Transformed(const Matrix3&) const;
Frustum Transformed(const Matrix3x4&) const;

// Properties:
/* readonly */
Array<Vector3> vertices;
};

class Graphics
{
// Methods:
void BeginDumpShaders(const String&);
void Close();
void EndDumpShaders();
void Maximize();
void Minimize();
void PrecacheShaders(File);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetMode(int, int);
bool SetMode(int, int, bool, bool, bool, bool, bool, int);
void SetWindowPosition(int, int);
bool TakeScreenShot(Image);
bool ToggleFullscreen();

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
bool borderless;
/* readonly */
String category;
/* readonly */
bool deferredSupport;
/* readonly */
IntVector2 desktopResolution;
/* readonly */
bool deviceLost;
bool flushGPU;
bool forceSM2;
/* readonly */
bool fullscreen;
/* readonly */
bool hardwareShadowSupport;
/* readonly */
int height;
/* readonly */
bool initialized;
/* readonly */
bool instancingSupport;
/* readonly */
bool lightPrepassSupport;
/* readonly */
int multiSample;
/* readonly */
Array<int> multiSampleLevels;
/* readonly */
uint numBatches;
/* readonly */
uint numPrimitives;
/* readonly */
int refs;
/* readonly */
bool resizable;
/* readonly */
Array<IntVector2> resolutions;
bool sRGB;
/* readonly */
bool sRGBSupport;
/* readonly */
bool sRGBWriteSupport;
/* readonly */
bool sm3Support;
/* readonly */
bool tripleBuffer;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
bool vsync;
/* readonly */
int weakRefs;
/* readonly */
int width;
/* writeonly */
Image windowIcon;
IntVector2 windowPosition;
String windowTitle;
};

class HttpRequest
{
// Methods:
Array<uint8> Read(uint);
bool ReadBool();
BoundingBox ReadBoundingBox();
int8 ReadByte();
Color ReadColor();
String ReadFileID();
float ReadFloat();
int ReadInt();
IntRect ReadIntRect();
IntVector2 ReadIntVector2();
String ReadLine();
uint ReadNetID();
Quaternion ReadPackedQuaternion();
Vector3 ReadPackedVector3(float);
Quaternion ReadQuaternion();
int16 ReadShort();
ShortStringHash ReadShortStringHash();
String ReadString();
StringHash ReadStringHash();
uint8 ReadUByte();
uint ReadUInt();
uint16 ReadUShort();
uint ReadVLE();
Variant ReadVariant();
VariantMap ReadVariantMap();
Vector2 ReadVector2();
Vector3 ReadVector3();
Vector4 ReadVector4();
uint Seek(uint);

// Properties:
/* readonly */
uint availableSize;
/* readonly */
uint checksum;
/* readonly */
bool eof;
/* readonly */
String error;
/* readonly */
String name;
/* readonly */
bool open;
/* readonly */
uint position;
/* readonly */
int refs;
/* readonly */
uint size;
/* readonly */
HttpRequestState state;
/* readonly */
String url;
/* readonly */
String verb;
/* readonly */
int weakRefs;
};

class Image
{
// Methods:
void Clear(const Color&);
void FlipVertical();
Color GetPixel(int, int) const;
Color GetPixel(int, int, int) const;
Color GetPixelBilinear(float, float) const;
Color GetPixelTrilinear(float, float, float) const;
bool Load(File);
bool LoadColorLUT(File);
void Resize(int, int);
bool Save(File) const;
void SaveBMP(const String&) const;
void SaveJPG(const String&, int) const;
void SavePNG(const String&) const;
void SaveTGA(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetPixel(int, int, const Color&);
void SetPixel(int, int, int, const Color&);
bool SetSize(int, int, int, uint);
bool SetSize(int, int, uint);

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
uint components;
/* readonly */
bool compressed;
/* readonly */
int depth;
/* readonly */
int height;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
/* readonly */
int width;
};

class Input
{
// Methods:
void CloseJoystick(uint);
bool DetectJoysticks();
int GetKeyFromName(const String&) const;
int GetKeyFromScancode(int) const;
String GetKeyName(int) const;
int GetScancodeFromKey(int) const;
int GetScancodeFromName(const String&) const;
String GetScancodeName(int) const;
bool OpenJoystick(uint);
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
bool focus;
/* readonly */
Array<String> joystickNames;
/* readonly */
Array<JoystickState> joysticks;
/* readonly */
Array<bool> keyDown;
/* readonly */
Array<bool> keyPress;
/* readonly */
bool minimized;
/* readonly */
Array<bool> mouseButtonDown;
/* readonly */
Array<bool> mouseButtonPress;
/* readonly */
IntVector2 mouseMove;
/* readonly */
int mouseMoveWheel;
/* readonly */
int mouseMoveX;
/* readonly */
int mouseMoveY;
/* readonly */
IntVector2 mousePosition;
bool mouseVisible;
/* readonly */
uint numJoysticks;
/* readonly */
uint numTouches;
/* readonly */
Array<bool> qualifierDown;
/* readonly */
Array<bool> qualifierPress;
/* readonly */
int qualifiers;
/* readonly */
int refs;
/* readonly */
Array<bool> scancodeDown;
/* readonly */
Array<bool> scancodePress;
/* readonly */
bool screenKeyboardSupport;
bool screenKeyboardVisible;
bool toggleFullscreen;
/* readonly */
Array<TouchState> touches;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class IntRect
{
// Methods:
Intersection IsInside(const IntVector2&) const;

// Properties:
int bottom;
/* readonly */
Array<int> data;
/* readonly */
int height;
int left;
int right;
/* readonly */
IntVector2 size;
int top;
/* readonly */
int width;
};

class IntVector2
{
// Methods:
String ToString() const;

// Properties:
/* readonly */
Array<int> data;
int x;
int y;
};

class JoystickState
{

// Properties:
/* readonly */
Array<float> axisPosition;
/* readonly */
Array<bool> buttonDown;
/* readonly */
Array<bool> buttonPress;
/* readonly */
Array<int> hatPosition;
String name;
/* readonly */
uint numAxes;
/* readonly */
uint numButtons;
/* readonly */
uint numHats;
};

class Light
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
float aspectRatio;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
BoundingBox boundingBox;
float brightness;
bool castShadows;
/* readonly */
String category;
Color color;
float drawDistance;
/* readonly */
Color effectiveColor;
/* readonly */
float effectiveSpecularIntensity;
bool enabled;
/* readonly */
bool enabledEffective;
float fadeDistance;
float fov;
/* readonly */
Frustum frustum;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
LightType lightType;
float lodBias;
uint maxLights;
/* readonly */
bool negative;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
bool occludee;
bool occluder;
bool perVertex;
Texture rampTexture;
float range;
/* readonly */
int refs;
BiasParameters shadowBias;
CascadeParameters shadowCascade;
float shadowDistance;
float shadowFadeDistance;
FocusParameters shadowFocus;
float shadowIntensity;
uint shadowMask;
float shadowNearFarRatio;
float shadowResolution;
Texture shapeTexture;
float specularIntensity;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
uint zoneMask;
};

class LineEdit
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
BlendMode blendMode;
IntRect border;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
/* readonly */
BorderImage cursor;
float cursorBlinkRate;
bool cursorMovable;
uint cursorPosition;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
uint dragDropMode;
uint echoCharacter;
bool editable;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool focus;
FocusMode focusMode;
int height;
HorizontalAlignment horizontalAlignment;
IntVector2 hoverOffset;
/* readonly */
bool hovering;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
uint maxLength;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
float opacity;
UIElement parent;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool selected;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
String text;
bool textCopyable;
/* readonly */
Text textElement;
bool textSelectable;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class ListView
{
// Methods:
void AddChild(UIElement);
void AddItem(UIElement);
void AddSelection(uint);
void ApplyAttributes();
void BringToFront();
void ChangeSelection(int, bool);
void ClearSelection();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
void Expand(uint, bool, bool = false);
uint FindChild(UIElement) const;
uint FindItem(UIElement);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
Array<UIElement> GetItems() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
void InsertItem(uint, UIElement, UIElement = null);
bool IsExpanded(uint) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool IsSelected(uint) const;
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveAllItems();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveItem(UIElement, uint = 0);
void RemoveItem(uint);
void RemoveSelection(uint);
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetScrollBarsVisible(bool, bool);
void SetSelections(Array<uint>);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void SetViewPosition(int, int);
void ToggleExpand(uint, bool = false);
void ToggleSelection(uint);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
int baseIndent;
/* readonly */
ShortStringHash baseType;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
bool clearSelectionOnDefocus;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
/* readonly */
UIElement contentElement;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool focus;
FocusMode focusMode;
int height;
bool hierarchyMode;
HighlightMode highlightMode;
HorizontalAlignment horizontalAlignment;
/* readonly */
ScrollBar horizontalScrollBar;
/* readonly */
bool hovering;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
/* readonly */
Array<UIElement> items;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
bool multiselect;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
/* readonly */
uint numItems;
float opacity;
float pageStep;
UIElement parent;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool scrollBarsAutoVisible;
/* readonly */
BorderImage scrollPanel;
float scrollStep;
bool selected;
/* readonly */
UIElement selectedItem;
/* readonly */
Array<UIElement> selectedItems;
uint selection;
/* readonly */
Array<uint> selections;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
/* readonly */
ScrollBar verticalScrollBar;
IntVector2 viewPosition;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class Log
{
// Methods:
void Close();
void Debug(const String&);
void Error(const String&);
void Info(const String&);
void Open(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void Warning(const String&);
void Write(const String&, bool = false);

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
String lastMessage;
int level;
bool quiet;
/* readonly */
int refs;
bool timeStamp;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Material
{
// Methods:
Material Clone(const String& = String ( )) const;
bool Load(File);
bool Load(const XMLElement&);
void RemoveShaderParameter(const String&);
bool Save(File) const;
bool Save(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetTechnique(uint, Technique, uint = 0, float = 0.0);
void SetUVTransform(const Vector2&, float, const Vector2&);
void SetUVTransform(const Vector2&, float, float);
void SortTechniques();

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
CullMode cullMode;
BiasParameters depthBias;
/* readonly */
uint memoryUse;
String name;
uint numTechniques;
/* readonly */
bool occlusion;
/* readonly */
int refs;
/* readonly */
Array<String> shaderParameterNames;
Array<Variant> shaderParameters;
CullMode shadowCullMode;
/* readonly */
Array<TechniqueEntry> techniqueEntries;
/* readonly */
Array<Technique> techniques;
Array<Texture> textures;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class Matrix3
{
// Methods:
bool Equals(const Matrix3&) const;
Matrix3 Inverse() const;
Vector3 Scale() const;
Matrix3 Scaled(const Vector3&) const;
void SetScale(const Vector3&);
void SetScale(float);
Matrix3 Transpose() const;

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

class Matrix3x4
{
// Methods:
void Decompose(Vector3&, Quaternion&, Vector3&) const;
bool Equals(const Matrix3x4&) const;
Matrix3x4 Inverse() const;
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

class Matrix4
{
// Methods:
void Decompose(Vector3&, Quaternion&, Vector3&) const;
bool Equals(const Matrix4&) const;
Matrix4 Inverse() const;
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

class Menu
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAccelerator(int, int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPopupOffset(int, int);
void SetPosition(int, int);
void SetPressedChildOffset(int, int);
void SetPressedOffset(int, int);
void SetRepeat(float, float);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
int acceleratorKey;
/* readonly */
int acceleratorQualifiers;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
BlendMode blendMode;
IntRect border;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool focus;
FocusMode focusMode;
int height;
HorizontalAlignment horizontalAlignment;
IntVector2 hoverOffset;
/* readonly */
bool hovering;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
float opacity;
UIElement parent;
UIElement popup;
IntVector2 popupOffset;
IntVector2 position;
/* readonly */
bool pressed;
IntVector2 pressedChildOffset;
IntVector2 pressedOffset;
int priority;
/* readonly */
int refs;
float repeatDelay;
float repeatRate;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool selected;
bool showPopup;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class MessageBox
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
String message;
/* readonly */
int refs;
String title;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
/* readonly */
UIElement window;
};

class Model
{
// Methods:
bool Load(File);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
BoundingBox boundingBox;
/* readonly */
String category;
/* readonly */
uint memoryUse;
String name;
/* readonly */
uint numGeometries;
/* readonly */
Array<uint> numGeometryLodLevels;
/* readonly */
uint numMorphs;
/* readonly */
int refs;
/* readonly */
Skeleton skeleton;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class Navigable
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
bool recursive;
/* readonly */
int refs;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class NavigationMesh
{
// Methods:
void ApplyAttributes();
bool Build();
bool Build(const BoundingBox&);
void DrawDebugGeometry(DebugRenderer, bool);
void DrawDebugGeometry(bool);
Vector3 FindNearestPoint(const Vector3&, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
Array<Vector3> FindPath(const Vector3&, const Vector3&, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
float GetDistanceToWall(const Vector3&, float, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
Vector3 GetRandomPoint();
Vector3 GetRandomPointInCircle(const Vector3&, float, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
Vector3 MoveAlongSurface(const Vector3&, const Vector3&, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ), uint = 3);
Vector3 Raycast(const Vector3&, const Vector3&, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
float agentHeight;
float agentMaxClimb;
float agentMaxSlope;
float agentRadius;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
BoundingBox boundingBox;
/* readonly */
String category;
float cellHeight;
float cellSize;
float detailSampleDistance;
float detailSampleMaxError;
float edgeMaxError;
float edgeMaxLength;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool initialized;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
IntVector2 numTiles;
Vector3 padding;
/* readonly */
int refs;
float regionMergeSize;
float regionMinSize;
bool temporary;
int tileSize;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
};

class Network
{
// Methods:
void BroadcastMessage(int, bool, bool, const VectorBuffer&, uint = 0);
void BroadcastRemoteEvent(Node, const String&, bool, const VariantMap& = VariantMap ( ));
void BroadcastRemoteEvent(Scene, const String&, bool, const VariantMap& = VariantMap ( ));
void BroadcastRemoteEvent(const String&, bool, const VariantMap& = VariantMap ( ));
bool CheckRemoteEvent(const String&) const;
bool Connect(const String&, uint16, Scene, const VariantMap& = VariantMap ( ));
void Disconnect(int = 0);
HttpRequest MakeHttpRequest(const String&, const String& = String ( ), Array<String> = null, const String& = String ( ));
void RegisterRemoteEvent(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool StartServer(uint16);
void StopServer();
void UnregisterAllRemoteEvents();
void UnregisterRemoteEvent(const String&) const;

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
Array<Connection> clientConnections;
String packageCacheDir;
/* readonly */
int refs;
/* readonly */
Connection serverConnection;
/* readonly */
bool serverRunning;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
int updateFps;
/* readonly */
int weakRefs;
};

class NetworkPriority
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
bool alwaysUpdateOwner;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
float basePriority;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
float distanceFactor;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
float minPriority;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
int refs;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Node
{
// Methods:
void AddChild(Node, uint = M_MAX_UNSIGNED);
void ApplyAttributes();
Node Clone(CreateMode = REPLICATED);
Node CreateChild(const String& = String ( ), CreateMode = REPLICATED, uint = 0);
Component CreateComponent(const String&, CreateMode = REPLICATED, uint = 0);
ScriptObject CreateScriptObject(ScriptFile, const String&, CreateMode = REPLICATED);
ScriptObject CreateScriptObject(const String&, const String&, CreateMode = REPLICATED);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
Node GetChild(const String&, bool = false) const;
Array<Node> GetChildren(bool = false) const;
Array<Node> GetChildrenWithComponent(const String&, bool = false) const;
Array<Node> GetChildrenWithScript(bool = false) const;
Array<Node> GetChildrenWithScript(const String&, bool = false) const;
Component GetComponent(const String&) const;
Array<Component> GetComponents() const;
Array<Component> GetComponents(const String&, bool = false) const;
Component GetOrCreateComponent(const String&, CreateMode = REPLICATED, uint = 0);
ScriptObject GetScriptObject() const;
ScriptObject GetScriptObject(const String&) const;
bool HasComponent(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
Vector3 LocalToWorld(const Vector3&) const;
Vector3 LocalToWorld(const Vector4&) const;
void LookAt(const Vector3&, const Vector3& = Vector3 ( 0 , 1 , 0 ));
void Pitch(float, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveAllComponents();
void RemoveChild(Node);
void RemoveChildren(bool, bool, bool);
void RemoveComponent(Component);
void RemoveComponent(const String&);
void RemoveComponents(bool, bool);
void RemoveInstanceDefault();
void ResetToDefault();
void Roll(float, bool = false);
void Rotate(const Quaternion&, bool = false);
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
void Scale(const Vector3&);
void Scale(float);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetEnabled(bool, bool);
void SetScale(float);
void SetTransform(const Vector3&, const Quaternion&);
void SetTransform(const Vector3&, const Quaternion&, const Vector3&);
void SetTransform(const Vector3&, const Quaternion&, float);
void SetWorldTransform(const Vector3&, const Quaternion&);
void SetWorldTransform(const Vector3&, const Quaternion&, const Vector3&);
void SetWorldTransform(const Vector3&, const Quaternion&, float);
void Translate(const Vector3&);
void TranslateRelative(const Vector3&);
Vector3 WorldToLocal(const Vector3&) const;
Vector3 WorldToLocal(const Vector4&) const;
void Yaw(float, bool = false);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
Array<Node> children;
/* readonly */
Array<Component> components;
Vector3 direction;
bool enabled;
/* readonly */
uint id;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
/* readonly */
uint numComponents;
Connection owner;
Node parent;
Vector3 position;
/* readonly */
int refs;
/* readonly */
Vector3 right;
Quaternion rotation;
Vector3 scale;
/* readonly */
Scene scene;
/* readonly */
ScriptObject scriptObject;
bool temporary;
/* readonly */
Matrix3x4 transform;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
Vector3 up;
/* readonly */
VariantMap vars;
/* readonly */
int weakRefs;
Vector3 worldDirection;
Vector3 worldPosition;
/* readonly */
Vector3 worldRight;
Quaternion worldRotation;
Vector3 worldScale;
/* readonly */
Matrix3x4 worldTransform;
/* readonly */
Vector3 worldUp;
};

class Object
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
int refs;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Octree
{
// Methods:
void AddManualDrawable(Drawable);
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
void DrawDebugGeometry(bool) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
Array<Node> GetDrawables(const BoundingBox&, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK);
Array<Node> GetDrawables(const Frustum&, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK);
Array<Node> GetDrawables(const Sphere&, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK);
Array<Node> GetDrawables(const Vector3&, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK);
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
Array<RayQueryResult> Raycast(const Ray&, RayQueryLevel = RAY_TRIANGLE, float = M_INFINITY, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK) const;
RayQueryResult RaycastSingle(const Ray&, RayQueryLevel = RAY_TRIANGLE, float = M_INFINITY, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK) const;
void Remove();
void RemoveInstanceDefault();
void RemoveManualDrawable(Drawable);
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetSize(const BoundingBox&, uint);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
uint numLevels;
/* readonly */
int refs;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
};

class OffMeshConnection
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
bool bidirectional;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
Node endPoint;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
float radius;
/* readonly */
int refs;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class PackageFile
{
// Methods:
bool Exists(const String&) const;
bool Open(const String&, uint = 0) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool compressed() const;

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
uint checksum;
/* readonly */
String name;
/* readonly */
uint numFiles;
/* readonly */
int refs;
/* readonly */
uint totalSize;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ParticleEmitter
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool Load(XMLFile);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool Save(XMLFile);
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetColor(const Color&);
void SetEmitting(bool, bool);

// Properties:
float activeTime;
float animationLodBias;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
/* readonly */
Array<ColorFrame> colors;
Vector3 constantForce;
float dampingForce;
float drawDistance;
/* writeonly */
float emissionRate;
Vector3 emitterSize;
EmitterType emitterType;
bool emitting;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool inView;
float inactiveTime;
uint lightMask;
float lodBias;
Material material;
Vector3 maxDirection;
float maxEmissionRate;
uint maxLights;
Vector3 maxParticleSize;
float maxRotation;
float maxRotationSpeed;
float maxTimeToLive;
float maxVelocity;
Vector3 minDirection;
float minEmissionRate;
Vector2 minParticleSize;
float minRotation;
float minRotationSpeed;
float minTimeToLive;
float minVelocity;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
uint numColors;
uint numParticles;
uint numTextureFrames;
bool occludee;
bool occluder;
/* writeonly */
Vector2 particleSize;
/* readonly */
int refs;
bool relative;
/* writeonly */
float rotation;
/* writeonly */
float rotationSpeed;
bool scaled;
float shadowDistance;
uint shadowMask;
float sizeAdd;
float sizeMul;
bool sorted;
bool temporary;
/* readonly */
Array<TextureFrame> textureFrames;
/* writeonly */
float timeToLive;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool updateInvisible;
/* writeonly */
float velocity;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
/* readonly */
Zone zone;
uint zoneMask;
};

class ParticleEmitter2D
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
BlendMode blendMode;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
float lodBias;
Material material;
uint maxLights;
ParticleModel2D model;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
bool occludee;
bool occluder;
/* readonly */
int refs;
float shadowDistance;
uint shadowMask;
Sprite2D sprite;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
float zValue;
uint zoneMask;
};

class ParticleModel2D
{
// Methods:
bool Load(File);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class Pass
{

// Properties:
bool alphaMask;
BlendMode blendMode;
CompareMode depthTestMode;
bool depthWrite;
PassLightingMode lightingMode;
String pixelShader;
String pixelShaderDefines;
/* readonly */
int refs;
String vertexShader;
String vertexShaderDefines;
/* readonly */
int weakRefs;
};

class PhysicsRaycastResult
{

// Properties:
/* readonly */
RigidBody body;
float distance;
Vector3 normal;
Vector3 position;
};

class PhysicsWorld
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
void DrawDebugGeometry(bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
Array<RigidBody> GetRigidBodies(RigidBody);
Array<RigidBody> GetRigidBodies(const BoundingBox&, uint = 0xffff);
Array<RigidBody> GetRigidBodies(const Sphere&, uint = 0xffff);
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
Array<PhysicsRaycastResult> Raycast(const Ray&, float = M_INFINITY, uint = 0xffff);
PhysicsRaycastResult RaycastSingle(const Ray&, float = M_INFINITY, uint = 0xffff);
void Remove();
void RemoveCachedGeometry(Model);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
PhysicsRaycastResult SphereCast(const Ray&, float, float = M_INFINITY, uint = 0xffff);
void Update(float);
void UpdateCollisions();

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
int fps;
Vector3 gravity;
/* readonly */
uint id;
bool internalEdge;
bool interpolation;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
int numIterations;
/* readonly */
int refs;
bool splitImpulse;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class PhysicsWorld2D
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry() const;
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
bool allowSleeping;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool autoClearForces;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
bool continuousPhysics;
bool drawAabb;
bool drawCenterOfMass;
bool drawJoint;
bool drawPair;
bool drawShape;
bool enabled;
/* readonly */
bool enabledEffective;
Vector2 gravity;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
uint positionIterations;
/* readonly */
int refs;
bool subStepping;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint velocityIterations;
bool warmStarting;
/* readonly */
int weakRefs;
};

class Plane
{
// Methods:
void Define(const Vector3&, const Vector3&);
void Define(const Vector3&, const Vector3&, const Vector3&);
void Define(const Vector4&);
float Distance(const Vector3&) const;
Vector3 Reflect(const Vector3&) const;
Vector4 ToVector4() const;
void Transform(const Matrix3&);
void Transform(const Matrix3x4&);
void Transform(const Matrix4&);
Plane Transformed(const Matrix3&) const;
Plane Transformed(const Matrix3x4&) const;
Plane Transformed(const Matrix4&) const;

// Properties:
Vector3 absNormal;
float d;
Vector3 normal;
/* readonly */
Matrix3x4 reflectionMatrix;
};

class Polyhedron
{
// Methods:
void AddFace(const Vector3&, const Vector3&, const Vector3&);
void AddFace(const Vector3&, const Vector3&, const Vector3&, const Vector3&);
void AddFace(const Array<Vector3>);
void Clear();
void Clip(const BoundingBox&);
void Clip(const Frustum&);
void Define(const BoundingBox&);
void Define(const Frustum&);
void Transform(const Matrix3&);
void Transform(const Matrix3x4&);
Polyhedron Transformed(const Matrix3&) const;
Polyhedron Transformed(const Matrix3x4&) const;

// Properties:
/* readonly */
Array<Array<Vector3>> face;
/* readonly */
uint numFaces;
};

class Quaternion
{
// Methods:
float DotProduct(const Quaternion&) const;
bool Equals(const Quaternion&) const;
void FromAngleAxis(float, const Vector3&);
void FromAxes(const Vector3&, const Vector3&, const Vector3&);
void FromEulerAngles(float, float, float);
void FromLookRotation(const Vector3&, const Vector3&);
void FromRotationTo(const Vector3&, const Vector3&);
Quaternion Inverse() const;
bool IsNaN() const;
Quaternion Nlerp(Quaternion, float, bool) const;
void Normalize();
Quaternion Normalized() const;
Quaternion Slerp(Quaternion, float) const;
String ToString() const;

// Properties:
/* readonly */
Vector3 eulerAngles;
/* readonly */
float pitch;
/* readonly */
float roll;
float w;
float x;
float y;
/* readonly */
float yaw;
float z;
};

class Ray
{
// Methods:
Vector3 ClosestPoint(const Ray&) const;
void Define(const Vector3&, const Vector3&);
float Distance(const Vector3&) const;
float HitDistance(const BoundingBox&) const;
float HitDistance(const Frustum&, bool = true) const;
float HitDistance(const Sphere&) const;
float HitDistance(const Vector3&, const Vector3&, const Vector3&) const;
Vector3 Project(const Vector3&) const;
Ray Transformed(const Matrix3x4&) const;

// Properties:
Vector3 direction;
Vector3 origin;
};

class RayQueryResult
{

// Properties:
float distance;
/* readonly */
Drawable drawable;
/* readonly */
Node node;
Vector3 normal;
Vector3 position;
uint subObject;
};

class Rect
{
// Methods:
void Clear();
void Clip(const Rect&);
void Define(const Vector2&);
void Define(const Vector2&, const Vector2&);
bool Equals(const Rect&) const;
Intersection IsInside(const Vector2&) const;
void Merge(const Rect&);
void Merge(const Vector2&);
Vector4 ToVector4() const;

// Properties:
float bottom;
/* readonly */
Vector2 center;
bool defined;
/* readonly */
Vector2 halfSize;
float left;
Vector2 max;
Vector2 min;
float right;
/* readonly */
Vector2 size;
float top;
};

class RefCounted
{

// Properties:
/* readonly */
int refs;
/* readonly */
int weakRefs;
};

class RenderPath
{
// Methods:
void AddCommand(const RenderPathCommand&);
void AddRenderTarget(const RenderTargetInfo&);
bool Append(XMLFile);
RenderPath Clone();
void InsertCommand(uint, const RenderPathCommand&);
bool Load(XMLFile);
void RemoveCommand(uint);
void RemoveCommands(const String&);
void RemoveRenderTarget(const String&);
void RemoveRenderTarget(uint);
void RemoveRenderTargts(const String&);
void SetEnabled(const String&, bool);
void ToggleEnabled(const String&);

// Properties:
Array<RenderPathCommand> commands;
/* readonly */
uint numCommands;
/* readonly */
uint numRenderTargets;
/* readonly */
int refs;
Array<RenderTargetInfo> renderTargets;
Array<Variant> shaderParameters;
/* readonly */
int weakRefs;
};

class RenderPathCommand
{
// Methods:
void RemoveShaderParameter(const String&);

// Properties:
Color clearColor;
float clearDepth;
uint clearFlags;
uint clearStencil;
bool enabled;
bool markToStencil;
String metadata;
uint numOutputs;
Array<String> outputNames;
String pass;
String pixelShaderDefines;
String pixelShaderName;
Array<Variant> shaderParameters;
RenderCommandSortMode sortMode;
String tag;
Array<String> textureNames;
RenderCommandType type;
bool useFogColor;
bool useLitBase;
bool vertexLights;
String vertexShaderDefines;
String vertexShaderName;
};

class RenderSurface
{
// Methods:
void QueueUpdate();

// Properties:
/* readonly */
int height;
RenderSurface linkedDepthStencil;
RenderSurface linkedRenderTarget;
uint numViewports;
/* readonly */
Texture parentTexture;
RenderSurfaceUpdateMode updateMode;
/* readonly */
TextureUsage usage;
Array<Viewport> viewports;
/* readonly */
int width;
};

class RenderTargetInfo
{

// Properties:
bool enabled;
bool filtered;
uint format;
String name;
bool persistent;
bool sRGB;
IntVector2 size;
RenderTargetSizeMode sizeMode;
String tag;
};

class Renderer
{
// Methods:
void DrawDebugGeometry(bool) const;
void ReloadShaders() const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetDefaultRenderPath(XMLFile);

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
Material defaultLightRamp;
/* readonly */
Material defaultLightSpot;
/* readonly */
Material defaultMaterial;
RenderPath defaultRenderPath;
/* readonly */
Zone defaultZone;
bool drawShadows;
bool dynamicInstancing;
bool hdrRendering;
int materialQuality;
int maxInstanceTriangles;
int maxOccluderTriangles;
int maxShadowCascades;
int maxShadowMaps;
int maxSortedInstances;
int minInstances;
/* readonly */
uint numBatches;
/* readonly */
Array<uint> numGeometries;
/* readonly */
Array<uint> numLights;
/* readonly */
Array<uint> numOccluders;
/* readonly */
uint numPrimitives;
/* readonly */
Array<uint> numShadowMaps;
uint numViewports;
/* readonly */
uint numViews;
float occluderSizeThreshold;
int occlusionBufferSize;
/* readonly */
int refs;
bool reuseShadowMaps;
int shadowMapSize;
int shadowQuality;
bool specularLighting;
int textureAnisotropy;
TextureFilterMode textureFilterMode;
int textureQuality;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
Array<Viewport> viewports;
/* readonly */
int weakRefs;
};

class Resource
{
// Methods:
bool Load(File);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class ResourceCache
{
// Methods:
bool AddManualResource(Resource);
void AddPackageFile(PackageFile, uint = M_MAX_UNSIGNED);
bool AddResourceDir(const String&, uint = M_MAX_UNSIGNED);
bool Exists(const String&) const;
File GetFile(const String&);
String GetPreferredResourceDir(const String&) const;
Resource GetResource(ShortStringHash, const String&, bool = true);
Resource GetResource(const String&, const String&, bool = true);
String GetResourceFileName(const String&) const;
void ReleaseAllResources(bool = false);
void ReleaseResource(const String&, const String&, bool = false);
void ReleaseResources(ShortStringHash, bool = false);
void ReleaseResources(const String&, bool = false);
void ReleaseResources(const String&, const String&, bool = false);
bool ReloadResource(Resource);
void RemovePackageFile(PackageFile, bool = true, bool = false);
void RemovePackageFile(const String&, bool = true, bool = false);
void RemoveResourceDir(const String&);
String SanitateResourceDirName(const String&) const;
String SanitateResourceName(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
bool autoReloadResources;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
Array<uint> memoryBudget;
/* readonly */
Array<uint> memoryUse;
/* readonly */
Array<PackageFile> packageFiles;
/* readonly */
int refs;
/* readonly */
Array<String> resourceDirs;
bool returnFailedResources;
/* readonly */
bool seachPackagesFirst;
/* writeonly */
bool searchPackagesFirst;
/* readonly */
uint totalMemoryUse;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ResourceRef
{

// Properties:
String name;
ShortStringHash type;
};

class ResourceRefList
{
// Methods:
void Resize(uint);

// Properties:
/* readonly */
bool empty;
/* readonly */
uint length;
Array<String> names;
ShortStringHash type;
};

class RigidBody
{
// Methods:
void Activate();
void ApplyAttributes();
void ApplyForce(const Vector3&);
void ApplyForce(const Vector3&, const Vector3&);
void ApplyImpulse(const Vector3&);
void ApplyImpulse(const Vector3&, const Vector3&);
void ApplyTorque(const Vector3&);
void ApplyTorqueImpulse(const Vector3&);
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
Vector3 GetVelocityAtPoint(const Vector3&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void ReAddBodyToWorld();
void Remove();
void RemoveInstanceDefault();
void ResetForces();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetCollisionLayerAndMask(uint, uint);
void SetTransform(const Vector3&, const Quaternion&);

// Properties:
/* readonly */
bool active;
float angularDamping;
Vector3 angularFactor;
float angularRestThreshold;
Vector3 angularVelocity;
Vector3 anisotropicFriction;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
float ccdMotionThreshold;
float ccdRadius;
/* readonly */
Vector3 centerOfMass;
/* readonly */
Array<RigidBody> collidingBodies;
CollisionEventMode collisionEventMode;
uint collisionLayer;
uint collisionMask;
float contactProcessingThreshold;
bool enabled;
/* readonly */
bool enabledEffective;
float friction;
Vector3 gravityOverride;
/* readonly */
uint id;
bool kinematic;
float linearDamping;
Vector3 linearFactor;
float linearRestThreshold;
Vector3 linearVelocity;
float mass;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
bool phantom;
Vector3 position;
/* readonly */
int refs;
float restitution;
float rollingFriction;
Quaternion rotation;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useGravity;
/* readonly */
int weakRefs;
};

class RigidBody2D
{
// Methods:
void ApplyAngularImpulse(float, bool);
void ApplyAttributes();
void ApplyForce(const Vector2&, const Vector2&, bool);
void ApplyForceToCenter(const Vector2&, bool);
void ApplyLinearImpulse(const Vector2&, const Vector2&, bool);
void ApplyTorque(float, bool);
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
bool allowSleep;
float angularDamping;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool awake;
/* readonly */
ShortStringHash baseType;
BodyType2D bodyType;
bool bullet;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
bool fixedRotation;
float gravityScale;
/* readonly */
uint id;
float inertia;
float linearDamping;
Vector2 linearVelocity;
float mass;
Vector2 massCenter;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
int refs;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useFixtureMass;
/* readonly */
int weakRefs;
};

class Scene
{
// Methods:
void AddChild(Node, uint = M_MAX_UNSIGNED);
void AddRequiredPackageFile(PackageFile);
void ApplyAttributes();
void Clear(bool = true, bool = true);
void ClearRequiredPackageFiles();
Node CreateChild(const String& = String ( ), CreateMode = REPLICATED, uint = 0);
Component CreateComponent(const String&, CreateMode = REPLICATED, uint = 0);
ScriptObject CreateScriptObject(ScriptFile, const String&, CreateMode = REPLICATED);
ScriptObject CreateScriptObject(const String&, const String&, CreateMode = REPLICATED);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
Node GetChild(const String&, bool = false) const;
Array<Node> GetChildren(bool = false) const;
Array<Node> GetChildrenWithComponent(const String&, bool = false) const;
Array<Node> GetChildrenWithScript(bool = false) const;
Array<Node> GetChildrenWithScript(const String&, bool = false) const;
Component GetComponent(const String&) const;
Component GetComponent(uint);
Array<Component> GetComponents() const;
Array<Component> GetComponents(const String&, bool = false) const;
Node GetNode(uint);
Component GetOrCreateComponent(const String&, CreateMode = REPLICATED, uint = 0);
ScriptObject GetScriptObject() const;
ScriptObject GetScriptObject(const String&) const;
bool HasComponent(const String&) const;
Node Instantiate(File, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node InstantiateXML(File, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node InstantiateXML(XMLFile, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node InstantiateXML(const XMLElement&, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
bool Load(File, bool = false);
bool LoadAsync(File);
bool LoadAsyncXML(File);
bool LoadXML(File);
bool LoadXML(const XMLElement&, bool = false);
Vector3 LocalToWorld(const Vector3&) const;
Vector3 LocalToWorld(const Vector4&) const;
void LookAt(const Vector3&, const Vector3& = Vector3 ( 0 , 1 , 0 ));
void Pitch(float, bool = false);
void RegisterVar(const String&);
void Remove();
void RemoveAllChildren();
void RemoveAllComponents();
void RemoveChild(Node);
void RemoveChildren(bool, bool, bool);
void RemoveComponent(Component);
void RemoveComponent(const String&);
void RemoveComponents(bool, bool);
void RemoveInstanceDefault();
void ResetToDefault();
void Roll(float, bool = false);
void Rotate(const Quaternion&, bool = false);
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
void Scale(const Vector3&);
void Scale(float);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetScale(float);
void SetTransform(const Vector3&, const Quaternion&);
void SetTransform(const Vector3&, const Quaternion&, const Vector3&);
void SetTransform(const Vector3&, const Quaternion&, float);
void SetWorldTransform(const Vector3&, const Quaternion&);
void SetWorldTransform(const Vector3&, const Quaternion&, const Vector3&);
void SetWorldTransform(const Vector3&, const Quaternion&, float);
void StopAsyncLoading();
const String& GetVarName(ShortStringHash) const;
void Translate(const Vector3&);
void TranslateRelative(const Vector3&);
void UnregisterAllVars(const String&);
void UnregisterVar(const String&);
void Update(float);
Vector3 WorldToLocal(const Vector3&) const;
Vector3 WorldToLocal(const Vector4&) const;
void Yaw(float, bool = false);

// Properties:
/* readonly */
bool asyncLoading;
/* readonly */
float asyncProgress;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
uint checksum;
/* readonly */
Array<Node> children;
/* readonly */
Array<Component> components;
/* readonly */
DebugRenderer debugRenderer;
Vector3 direction;
float elapsedTime;
/* readonly */
String fileName;
/* readonly */
uint id;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
/* readonly */
uint numComponents;
/* readonly */
Octree octree;
Node parent;
/* readonly */
PhysicsWorld physicsWorld;
/* readonly */
PhysicsWorld2D physicsWorld2D;
Vector3 position;
/* readonly */
int refs;
/* readonly */
Array<PackageFile> requiredPackageFiles;
/* readonly */
Vector3 right;
Quaternion rotation;
Vector3 scale;
/* readonly */
ScriptObject scriptObject;
float smoothingConstant;
float snapThreshold;
bool temporary;
float timeScale;
/* readonly */
Matrix3x4 transform;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
Vector3 up;
bool updateEnabled;
/* readonly */
VariantMap vars;
/* readonly */
int weakRefs;
Vector3 worldDirection;
Vector3 worldPosition;
/* readonly */
Vector3 worldRight;
Quaternion worldRotation;
Vector3 worldScale;
/* readonly */
Matrix3x4 worldTransform;
/* readonly */
Vector3 worldUp;
};

class Script
{
// Methods:
void DumpAPI(DumpMode = DOXYGEN);
bool Execute(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
Scene defaultScene;
ScriptFile defaultScriptFile;
bool executeConsoleCommands;
/* readonly */
int refs;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ScriptFile
{
// Methods:
void ClearDelayedExecute(const String& = String ( ));
void DelayedExecute(float, bool, const String&);
void DelayedExecute(float, bool, const String&, const Array<Variant>);
bool Execute(const String&, const Array<Variant>);
bool Load(File);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
bool compiled;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class ScriptInstance
{
// Methods:
void ApplyAttributes();
void ClearDelayedExecute(const String& = String ( ));
bool CreateObject(ScriptFile, const String&);
void DelayedExecute(float, bool, const String&);
void DelayedExecute(float, bool, const String&, const Array<Variant>);
void DrawDebugGeometry(DebugRenderer, bool);
bool Execute(const String&);
bool Execute(const String&, const Array<Variant>);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
String className;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
ScriptObject object;
/* readonly */
int refs;
ScriptFile scriptFile;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ScriptObject
{
};

class ScrollBar
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
void ChangeValue(float);
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void StepBack();
void StepForward();
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
Button backButton;
/* readonly */
ShortStringHash baseType;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
/* readonly */
float effectiveScrollStep;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool focus;
FocusMode focusMode;
/* readonly */
Button forwardButton;
int height;
HorizontalAlignment horizontalAlignment;
/* readonly */
bool hovering;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
float opacity;
Orientation orientation;
UIElement parent;
IntVector2 position;
int priority;
float range;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
float scrollStep;
bool selected;
IntVector2 size;
/* readonly */
Slider slider;
bool sortChildren;
float stepFactor;
String style;
bool temporary;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
float value;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class ScrollView
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetScrollBarsVisible(bool, bool);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void SetViewPosition(int, int);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
UIElement contentElement;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool focus;
FocusMode focusMode;
int height;
HorizontalAlignment horizontalAlignment;
/* readonly */
ScrollBar horizontalScrollBar;
/* readonly */
bool hovering;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
float opacity;
float pageStep;
UIElement parent;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool scrollBarsAutoVisible;
/* readonly */
BorderImage scrollPanel;
float scrollStep;
bool selected;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
/* readonly */
ScrollBar verticalScrollBar;
IntVector2 viewPosition;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class Serializable
{
// Methods:
void ApplyAttributes();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
uint numAttributes;
/* readonly */
int refs;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Serializer
{
// Methods:
uint Write(Array<uint8>);
bool WriteBool(bool);
bool WriteBoundingBox(const BoundingBox&);
bool WriteByte(int8);
bool WriteColor(const Color&);
bool WriteFileID(const String&);
bool WriteFloat(float);
bool WriteInt(int);
bool WriteIntRect(const IntRect&);
bool WriteIntVector2(const IntVector2&);
bool WriteLine(const String&);
bool WriteNetID(uint);
bool WritePackedQuaternion(const Quaternion&);
bool WritePackedVector3(const Vector3&, float);
bool WriteQuaternion(const Quaternion&);
bool WriteShort(int16);
bool WriteShortStringHash(const ShortStringHash&);
bool WriteString(const String&);
bool WriteStringHash(const StringHash&);
bool WriteUByte(uint8);
bool WriteUInt(uint);
bool WriteUShort(uint16);
bool WriteVLE(uint);
bool WriteVariant(const Variant&);
bool WriteVariantMap(const VariantMap&);
bool WriteVector2(const Vector2&);
bool WriteVector3(const Vector3&);
bool WriteVector4(const Vector4&);
};

class ShortStringHash
{
// Methods:
String ToString() const;

// Properties:
/* readonly */
uint16 value;
};

class Skeleton
{
// Methods:
Bone GetBone(const String&) const;
void Reset();

// Properties:
/* readonly */
Array<Bone> bones;
/* readonly */
uint numBones;
/* readonly */
Bone rootBone;
};

class Skybox
{
// Methods:
void ApplyAttributes();
void ApplyMaterialList(const String& = String ( ));
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
float lodBias;
/* writeonly */
Material material;
Array<Material> materials;
uint maxLights;
Model model;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
uint numGeometries;
bool occludee;
bool occluder;
/* readonly */
int refs;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
/* readonly */
Zone zone;
uint zoneMask;
};

class Slider
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
void ChangeValue(float);
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
BlendMode blendMode;
IntRect border;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool focus;
FocusMode focusMode;
int height;
HorizontalAlignment horizontalAlignment;
IntVector2 hoverOffset;
/* readonly */
bool hovering;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
/* readonly */
BorderImage knob;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
float opacity;
Orientation orientation;
UIElement parent;
IntVector2 position;
int priority;
float range;
/* readonly */
int refs;
float repeatRate;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool selected;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
float value;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class SmoothedTransform
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void Update(float, float);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool inProgress;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
int refs;
Vector3 targetPosition;
Quaternion targetRotation;
Vector3 targetWorldPosition;
Quaternion targetWorldRotation;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Sound
{
// Methods:
bool Load(File);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
bool compressed;
/* readonly */
float frequency;
/* readonly */
float length;
bool looped;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
/* readonly */
uint sampleSize;
/* readonly */
bool sixteenBit;
/* readonly */
bool stereo;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class SoundListener
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
int refs;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class SoundSource
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Play(Sound);
void Play(Sound, float);
void Play(Sound, float, float);
void Play(Sound, float, float, float);
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void Stop();

// Properties:
/* readonly */
float attenuation;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool autoRemove;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
float frequency;
float gain;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
float panning;
/* readonly */
bool playing;
/* readonly */
int refs;
/* readonly */
Sound sound;
SoundType soundType;
bool temporary;
/* readonly */
float timePosition;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class SoundSource3D
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Play(Sound);
void Play(Sound, float);
void Play(Sound, float, float);
void Play(Sound, float, float, float);
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAngleAttenuation(float, float);
bool SetAttribute(const String&, const Variant&);
void SetDistanceAttenuation(float, float, float);
void Stop();

// Properties:
/* readonly */
float attenuation;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool autoRemove;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
float farDistance;
float frequency;
float gain;
/* readonly */
uint id;
float innerAngle;
float nearDistance;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
float outerAngle;
float panning;
/* readonly */
bool playing;
/* readonly */
int refs;
float rolloffFactor;
/* readonly */
Sound sound;
SoundType soundType;
bool temporary;
/* readonly */
float timePosition;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Sphere
{
// Methods:
void Clear();
void Define(const BoundingBox&);
void Define(const Frustum&);
void Define(const Polyhedron&);
void Define(const Sphere&);
void Define(const Vector3&, float);
float Distance(const Vector3&) const;
Intersection IsInside(const BoundingBox&) const;
Intersection IsInside(const Sphere&) const;
Intersection IsInside(const Vector3&) const;
void Merge(const BoundingBox&);
void Merge(const Frustum&);
void Merge(const Sphere&);
void Merge(const Vector3&);

// Properties:
Vector3 center;
bool defined;
float radius;
};

class Spline
{
// Methods:
void AddKnot(const Variant&);
void AddKnot(const Variant&, uint);
void Clear();
Variant GetPoint(float);
void RemoveKnot();
void RemoveKnot(uint);

// Properties:
InterpolationMode interpolationMode;
Array<Variant> knot;
Array<Variant> knots;
};

class SplinePath
{
// Methods:
void AddControlPoint(Node, uint = M_MAX_UNSIGNED);
void ApplyAttributes();
void ClearControlPoints();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
Vector3 GetPoint(float) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Move(float);
void Remove();
void RemoveControlPoint(Node);
void RemoveInstanceDefault();
void Reset();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
Node controlledNode;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
InterpolationMode interpolationMode;
/* readonly */
bool isFinished;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
Vector3 position;
/* readonly */
int refs;
float speed;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Sprite
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHotSpot(int, int);
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(float, float);
void SetScale(float);
void SetScale(float, float);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
BlendMode blendMode;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
Array<UIElement> children;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
bool elementEventSender;
int height;
HorizontalAlignment horizontalAlignment;
IntVector2 hotSpot;
IntRect imageRect;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
float opacity;
UIElement parent;
Vector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
float rotation;
Vector2 scale;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
Texture texture;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class Sprite2D
{
// Methods:
bool Load(File);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
Vector2 hotSpot;
/* readonly */
uint memoryUse;
String name;
IntRect rectangle;
/* readonly */
int refs;
Texture2D texture;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class SpriteSheet2D
{
// Methods:
void DefineSprite(const String&, const IntRect&, const Vector2&);
Sprite2D GetSprite(const String&);
bool Load(File);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void UpdateSprite(const String&, const IntRect&, const Vector2&);

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
/* readonly */
Texture2D texture;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class StaticModel
{
// Methods:
void ApplyAttributes();
void ApplyMaterialList(const String& = String ( ));
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool IsInside(const Vector3&) const;
bool IsInsideLocal(const Vector3&) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
float lodBias;
/* writeonly */
Material material;
Array<Material> materials;
uint maxLights;
Model model;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
uint numGeometries;
bool occludee;
bool occluder;
uint occlusionLodLevel;
/* readonly */
int refs;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
uint zoneMask;
};

class StaticModelGroup
{
// Methods:
void AddInstanceNode(Node);
void ApplyAttributes();
void ApplyMaterialList(const String& = String ( ));
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllInstanceNodes();
void RemoveInstanceDefault();
void RemoveInstanceNode(Node);
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool inView;
/* readonly */
Array<Node> instanceNodes;
uint lightMask;
float lodBias;
/* writeonly */
Material material;
Array<Material> materials;
uint maxLights;
Model model;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
uint numGeometries;
/* readonly */
uint numInstanceNodes;
bool occludee;
bool occluder;
uint occlusionLodLevel;
/* readonly */
int refs;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
/* readonly */
Zone zone;
uint zoneMask;
};

class StaticSprite2D
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetFlip(bool, bool);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
BlendMode blendMode;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
Color color;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
bool flipX;
bool flipY;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
float lodBias;
Material material;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
bool occludee;
bool occluder;
/* readonly */
int refs;
float shadowDistance;
uint shadowMask;
Sprite2D sprite;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
float zValue;
uint zoneMask;
};

class String
{
// Methods:
void AppendUTF8(uint);
uint AtUTF8(uint) const;
uint ByteOffsetUTF8(uint) const;
void Clear();
int Compare(const String&, bool = true) const;
bool Contains(const String&, bool = true) const;
bool Contains(uint8, bool = true) const;
bool EndsWith(const String&, bool = true) const;
uint Find(const String&, uint = 0, bool = true) const;
uint Find(uint8, uint = 0, bool = true) const;
uint FindLast(const String&, uint = 0xffffffff, bool = true) const;
uint FindLast(uint8, uint = 0xffffffff, bool = true) const;
void Join(Array<String>&, const String&);
uint NextUTF8Char(uint&) const;
void Replace(const String&, const String&, bool = true);
void Replace(uint8, uint8, bool = true);
void ReplaceUTF8(uint, uint);
String Replaced(const String&, const String&, bool = true) const;
String Replaced(uint8, uint8, bool = true) const;
void Resize(uint);
void SetUTF8FromLatin1(const String&);
Array<String> Split(uint8) const;
bool StartsWith(const String&, bool = true) const;
String Substring(uint) const;
String Substring(uint, uint) const;
String SubstringUTF8(uint) const;
String SubstringUTF8(uint, uint) const;
bool ToBool() const;
Color ToColor() const;
float ToFloat() const;
int ToInt() const;
IntRect ToIntRect() const;
IntVector2 ToIntVector2() const;
String ToLower() const;
Quaternion ToQuaternion() const;
uint ToUInt() const;
String ToUpper() const;
Vector2 ToVector2() const;
Vector3 ToVector3() const;
Vector4 ToVector4(bool = false) const;
Variant ToVectorVariant() const;
String Trimmed() const;

// Properties:
/* readonly */
bool empty;
/* readonly */
uint length;
/* readonly */
uint utf8Length;
};

class StringHash
{
// Methods:
String ToString() const;

// Properties:
/* readonly */
uint value;
};

class Technique
{
// Methods:
Pass CreatePass(StringHash);
bool HasPass(StringHash) const;
bool Load(File);
void RemovePass(StringHash);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
uint memoryUse;
String name;
/* readonly */
Array<Pass> passes;
/* readonly */
int refs;
bool sm3;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class TechniqueEntry
{

// Properties:
float lodDistance;
int qualityLevel;
Technique technique;
};

class Terrain
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
float GetHeight(const Vector3&) const;
Vector3 GetNormal(const Vector3&) const;
TerrainPatch GetPatch(int, int) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
Image heightMap;
/* readonly */
uint id;
uint lightMask;
float lodBias;
Material material;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
IntVector2 numPatches;
/* readonly */
IntVector2 numVertices;
bool occludee;
bool occluder;
int patchSize;
/* readonly */
Array<TerrainPatch> patches;
/* readonly */
int refs;
float shadowDistance;
uint shadowMask;
bool smoothing;
Vector3 spacing;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
uint zoneMask;
};

class TerrainPatch
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
float lodBias;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
bool occludee;
bool occluder;
/* readonly */
int refs;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
uint zoneMask;
};

class Text
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
void ClearSelection();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
bool SetFont(Font, int);
bool SetFont(const String&, int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetSelection(uint, uint = M_MAX_UNSIGNED);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
Array<IntVector2> charPositions;
/* readonly */
Array<IntVector2> charSizes;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
Color effectColor;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool focus;
FocusMode focusMode;
/* readonly */
Font font;
/* readonly */
int fontSize;
int height;
HorizontalAlignment horizontalAlignment;
Color hoverColor;
/* readonly */
bool hovering;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChars;
/* readonly */
uint numChildren;
/* readonly */
uint numRows;
float opacity;
UIElement parent;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
int rowHeight;
float rowSpacing;
/* readonly */
Array<int> rowWidths;
/* readonly */
IntVector2 screenPosition;
bool selected;
Color selectionColor;
/* readonly */
uint selectionLength;
/* readonly */
uint selectionStart;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
String text;
HorizontalAlignment textAlignment;
TextEffect textEffect;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
int weakRefs;
int width;
bool wordwrap;
};

class Text3D
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
bool SetFont(Font, int);
bool SetFont(const String&, int);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
/* readonly */
Array<IntVector2> charPositions;
/* readonly */
Array<IntVector2> charSizes;
/* writeonly */
Color color;
Array<Color> colors;
float drawDistance;
Color effectColor;
float effectDepthBias;
bool enabled;
/* readonly */
bool enabledEffective;
bool faceCamera;
/* readonly */
Font font;
/* readonly */
int fontSize;
HorizontalAlignment horizontalAlignment;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
float lodBias;
Material material;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
uint numChars;
/* readonly */
uint numRows;
bool occludee;
bool occluder;
float opacity;
/* readonly */
int refs;
/* readonly */
int rowHeight;
float rowSpacing;
/* readonly */
Array<int> rowWidths;
float shadowDistance;
uint shadowMask;
bool temporary;
String text;
HorizontalAlignment textAlignment;
TextEffect textEffect;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
VerticalAlignment verticalAlignment;
uint viewMask;
/* readonly */
int weakRefs;
int width;
bool wordwrap;
/* readonly */
BoundingBox worldBoundingBox;
uint zoneMask;
};

class Texture
{
// Methods:
void ClearDataLost();
bool Load(File);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetNumLevels(uint);

// Properties:
Array<TextureAddressMode> addressMode;
Texture backupTexture;
/* readonly */
ShortStringHash baseType;
Color borderColor;
/* readonly */
String category;
/* readonly */
bool compressed;
/* readonly */
bool dataLost;
TextureFilterMode filterMode;
/* readonly */
uint format;
/* readonly */
int height;
/* readonly */
Array<int> levelHeight;
/* readonly */
Array<int> levelWidth;
/* readonly */
uint levels;
/* readonly */
uint memoryUse;
Array<int> mipsToSkip;
String name;
/* readonly */
int refs;
bool sRGB;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
TextureUsage usage;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
/* readonly */
int width;
};

class Texture2D
{
// Methods:
void ClearDataLost();
bool Load(File);
bool Load(Image, bool = false);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetNumLevels(uint);
bool SetSize(int, int, uint, TextureUsage = TEXTURE_STATIC);

// Properties:
Array<TextureAddressMode> addressMode;
Texture backupTexture;
/* readonly */
ShortStringHash baseType;
Color borderColor;
/* readonly */
String category;
/* readonly */
bool compressed;
/* readonly */
bool dataLost;
TextureFilterMode filterMode;
/* readonly */
uint format;
/* readonly */
int height;
/* readonly */
Array<int> levelHeight;
/* readonly */
Array<int> levelWidth;
/* readonly */
uint levels;
/* readonly */
uint memoryUse;
Array<int> mipsToSkip;
String name;
/* readonly */
int refs;
/* readonly */
RenderSurface renderSurface;
bool sRGB;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
TextureUsage usage;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
/* readonly */
int width;
};

class Texture3D
{
// Methods:
void ClearDataLost();
bool Load(File);
bool Load(Image, bool = false);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetNumLevels(uint);
bool SetSize(int, int, uint, TextureUsage = TEXTURE_STATIC);

// Properties:
Array<TextureAddressMode> addressMode;
Texture backupTexture;
/* readonly */
ShortStringHash baseType;
Color borderColor;
/* readonly */
String category;
/* readonly */
bool compressed;
/* readonly */
bool dataLost;
TextureFilterMode filterMode;
/* readonly */
uint format;
/* readonly */
int height;
/* readonly */
Array<int> levelHeight;
/* readonly */
Array<int> levelWidth;
/* readonly */
uint levels;
/* readonly */
uint memoryUse;
Array<int> mipsToSkip;
String name;
/* readonly */
int refs;
/* readonly */
RenderSurface renderSurface;
bool sRGB;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
TextureUsage usage;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
/* readonly */
int width;
};

class TextureCube
{
// Methods:
void ClearDataLost();
bool Load(CubeMapFace, Image, bool = false);
bool Load(File);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetNumLevels(uint);
bool SetSize(int, uint, TextureUsage = TEXTURE_STATIC);

// Properties:
Array<TextureAddressMode> addressMode;
Texture backupTexture;
/* readonly */
ShortStringHash baseType;
Color borderColor;
/* readonly */
String category;
/* readonly */
bool compressed;
/* readonly */
bool dataLost;
TextureFilterMode filterMode;
/* readonly */
uint format;
/* readonly */
int height;
/* readonly */
Array<int> levelHeight;
/* readonly */
Array<int> levelWidth;
/* readonly */
uint levels;
/* readonly */
uint memoryUse;
Array<int> mipsToSkip;
String name;
/* readonly */
int refs;
/* readonly */
Array<RenderSurface> renderSurfaces;
bool sRGB;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
TextureUsage usage;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
/* readonly */
int width;
};

class TextureFrame
{

// Properties:
float time;
Rect uv;
};

class Time
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
float elapsedTime;
/* readonly */
uint frameNumber;
/* readonly */
int refs;
/* readonly */
uint systemTime;
/* readonly */
String timeStamp;
/* readonly */
float timeStep;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Timer
{
// Methods:
uint GetMSec(bool);
void Reset();
};

class ToolTip
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
XMLFile defaultStyle;
float delay;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool focus;
FocusMode focusMode;
int height;
HorizontalAlignment horizontalAlignment;
/* readonly */
bool hovering;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
float opacity;
UIElement parent;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool selected;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class TouchState
{

// Properties:
IntVector2 delta;
IntVector2 lastPosition;
IntVector2 position;
float pressure;
int touchID;
};

class UI
{
// Methods:
void Clear();
void DebugDraw(UIElement);
UIElement GetElementAt(const IntVector2&, bool = true);
UIElement GetElementAt(int, int, bool = true);
bool HasModalElement() const;
UIElement LoadLayout(File);
UIElement LoadLayout(File, XMLFile);
UIElement LoadLayout(XMLFile);
UIElement LoadLayout(XMLFile, XMLFile);
bool SaveLayout(File, UIElement);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetFocusElement(UIElement, bool = false);

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
String clipBoardText;
Cursor cursor;
/* readonly */
IntVector2 cursorPosition;
float defaultToolTipDelay;
float doubleClickInterval;
int dragBeginDistance;
float dragBeginInterval;
/* readonly */
UIElement dragElement;
UIElement focusElement;
bool forceAutoHint;
/* readonly */
UIElement frontElement;
int maxFontTextureSize;
/* readonly */
UIElement modalRoot;
bool nonFocusedMouseWheel;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useMutableGlyphs;
bool useScreenKeyboard;
bool useSystemClipBoard;
/* readonly */
int weakRefs;
};

class UIElement
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool focus;
FocusMode focusMode;
int height;
HorizontalAlignment horizontalAlignment;
/* readonly */
bool hovering;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
float opacity;
UIElement parent;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool selected;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class Variant
{
// Methods:
void Clear();
const Color& GetColor() const;
void FromString(VariantType, const String&);
void FromString(const String&, const String&);
bool GetBool() const;
VectorBuffer GetBuffer() const;
float GetFloat() const;
int GetInt() const;
RefCounted GetPtr() const;
ShortStringHash GetShortStringHash() const;
StringHash GetStringHash() const;
uint GetUInt() const;
Array<Variant> GetVariantVector() const;
const IntRect& GetIntRect() const;
const IntVector2& GetIntVector2() const;
const Quaternion& GetQuaternion() const;
const ResourceRef& GetResourceRef() const;
const ResourceRefList& GetResourceRefList() const;
const String& GetString() const;
String ToString() const;
const VariantMap& GetVariantMap() const;
const Vector2& GetVector2() const;
const Vector3& GetVector3() const;
const Vector4& GetVector4() const;
/* deprecated */
Camera GetCamera() const;
/* deprecated */
CollisionShape GetCollisionShape() const;
/* deprecated */
Component GetComponent() const;
/* deprecated */
Connection GetConnection() const;
/* deprecated */
Node GetNode() const;
/* deprecated */
PhysicsWorld GetPhysicsWorld() const;
/* deprecated */
RenderSurface GetRenderSurface() const;
/* deprecated */
RigidBody GetRigidBody() const;
/* deprecated */
Scene GetScene() const;
/* deprecated */
Serializable GetSerializable() const;
/* deprecated */
Texture GetTexture() const;
/* deprecated */
UIElement GetUIElement() const;

// Properties:
/* readonly */
bool empty;
/* readonly */
VariantType type;
/* readonly */
String typeName;
/* readonly */
bool zero;
};

class VariantMap
{
// Methods:
void Clear();
bool Contains(ShortStringHash) const;
bool Contains(const String&) const;
bool Erase(ShortStringHash);
bool Erase(const String&);

// Properties:
/* readonly */
Array<ShortStringHash> keys;
/* readonly */
uint length;
};

class Vector2
{
// Methods:
float AbsDotProduct(const Vector2&) const;
float DotProduct(const Vector2&) const;
bool Equals(const Vector2&) const;
bool IsNaN() const;
Vector2 Lerp(const Vector2&, float) const;
void Normalize();
Vector2 Normalized() const;
String ToString() const;

// Properties:
/* readonly */
Array<float> data;
/* readonly */
float length;
/* readonly */
float lengthSquared;
float x;
float y;
};

class Vector3
{
// Methods:
float AbsDotProduct(const Vector3&) const;
float Angle(const Vector3&) const;
Vector3 CrossProduct(const Vector3&) const;
float DotProduct(const Vector3&) const;
bool Equals(const Vector3&) const;
bool IsNaN() const;
Vector3 Lerp(const Vector3&, float) const;
void Normalize();
Vector3 Normalized() const;
String ToString() const;

// Properties:
/* readonly */
Array<float> data;
/* readonly */
float length;
/* readonly */
float lengthSquared;
float x;
float y;
float z;
};

class Vector4
{
// Methods:
float AbsDotProduct(const Vector4&) const;
float DotProduct(const Vector4&) const;
bool Equals(const Vector4&) const;
bool IsNaN() const;
Vector4 Lerp(const Vector4&, float) const;
String ToString() const;

// Properties:
/* readonly */
Array<float> data;
float w;
float x;
float y;
float z;
};

class VectorBuffer
{
// Methods:
void Clear();
Array<uint8> Read(uint);
bool ReadBool();
BoundingBox ReadBoundingBox();
int8 ReadByte();
Color ReadColor();
String ReadFileID();
float ReadFloat();
int ReadInt();
IntRect ReadIntRect();
IntVector2 ReadIntVector2();
String ReadLine();
uint ReadNetID();
Quaternion ReadPackedQuaternion();
Vector3 ReadPackedVector3(float);
Quaternion ReadQuaternion();
int16 ReadShort();
ShortStringHash ReadShortStringHash();
String ReadString();
StringHash ReadStringHash();
uint8 ReadUByte();
uint ReadUInt();
uint16 ReadUShort();
uint ReadVLE();
Variant ReadVariant();
VariantMap ReadVariantMap();
Vector2 ReadVector2();
Vector3 ReadVector3();
Vector4 ReadVector4();
void Resize(uint);
uint Seek(uint);
void SetData(Deserializer, uint);
uint Write(Array<uint8>);
bool WriteBool(bool);
bool WriteBoundingBox(const BoundingBox&);
bool WriteByte(int8);
bool WriteColor(const Color&);
bool WriteFileID(const String&);
bool WriteFloat(float);
bool WriteInt(int);
bool WriteIntRect(const IntRect&);
bool WriteIntVector2(const IntVector2&);
bool WriteLine(const String&);
bool WriteNetID(uint);
bool WritePackedQuaternion(const Quaternion&);
bool WritePackedVector3(const Vector3&, float);
bool WriteQuaternion(const Quaternion&);
bool WriteShort(int16);
bool WriteShortStringHash(const ShortStringHash&);
bool WriteString(const String&);
bool WriteStringHash(const StringHash&);
bool WriteUByte(uint8);
bool WriteUInt(uint);
bool WriteUShort(uint16);
bool WriteVLE(uint);
bool WriteVariant(const Variant&);
bool WriteVariantMap(const VariantMap&);
bool WriteVector2(const Vector2&);
bool WriteVector3(const Vector3&);
bool WriteVector4(const Vector4&);

// Properties:
/* readonly */
uint checksum;
/* readonly */
bool eof;
/* readonly */
String name;
/* readonly */
uint position;
/* readonly */
uint size;
};

class View3D
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void QueueUpdate();
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void SetView(Scene, Camera);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool autoUpdate;
/* readonly */
ShortStringHash baseType;
bool bringToBack;
bool bringToFront;
/* readonly */
Node cameraNode;
/* readonly */
String category;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
XMLFile defaultStyle;
/* readonly */
Texture2D depthTexture;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
bool fixedHeightResizing;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool fixedWidthResizing;
bool focus;
FocusMode focusMode;
uint format;
int height;
HorizontalAlignment horizontalAlignment;
/* readonly */
bool hovering;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
bool modal;
Color modalFrameColor;
IntVector2 modalFrameSize;
Color modalShadeColor;
bool movable;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
float opacity;
UIElement parent;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
Texture2D renderTexture;
bool resizable;
IntRect resizeBorder;
/* readonly */
UIElement root;
/* readonly */
Scene scene;
/* readonly */
IntVector2 screenPosition;
bool selected;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
/* readonly */
Viewport viewport;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class Viewport
{
// Methods:
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetRenderPath(XMLFile);

// Properties:
/* readonly */
ShortStringHash baseType;
Camera camera;
/* readonly */
String category;
IntRect rect;
/* readonly */
int refs;
RenderPath renderPath;
Scene scene;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class WeakHandle
{
// Methods:
RefCounted Get() const;

// Properties:
/* readonly */
bool expired;
/* readonly */
int refs;
/* readonly */
int weakRefs;
};

class Window
{
// Methods:
void AddChild(UIElement);
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const ShortStringHash&, const Variant& = Variant ( ), bool = false) const;
UIElement GetChild(const String&, bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
UIElement GetElementEventSender() const;
uint GetNumChildren(bool) const;
void InsertChild(uint, UIElement);
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File, bool = false);
bool LoadChildXML(XMLFile, XMLFile = null);
bool LoadChildXML(const XMLElement&, XMLFile = null, bool = false);
bool LoadXML(File);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void Remove();
void RemoveAllChildren();
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(File);
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
bool SetAttribute(const String&, const Variant&);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxSize(int, int);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const ShortStringHash&);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
IntVector2 childOffset;
/* readonly */
Array<UIElement> children;
IntRect clipBorder;
bool clipChildren;
/* writeonly */
Color color;
/* readonly */
bool colorGradient;
Array<Color> colors;
/* readonly */
IntRect combinedScreenRect;
XMLFile defaultStyle;
/* readonly */
float derivedOpacity;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enabled;
/* readonly */
bool fixedHeight;
bool fixedHeightResizing;
/* readonly */
bool fixedSize;
/* readonly */
bool fixedWidth;
bool fixedWidthResizing;
bool focus;
FocusMode focusMode;
int height;
HorizontalAlignment horizontalAlignment;
/* readonly */
bool hovering;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
LayoutMode layoutMode;
int layoutSpacing;
int maxHeight;
IntVector2 maxSize;
int maxWidth;
int minHeight;
IntVector2 minSize;
int minWidth;
bool modal;
Color modalFrameColor;
IntVector2 modalFrameSize;
Color modalShadeColor;
bool movable;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
float opacity;
UIElement parent;
IntVector2 position;
int priority;
/* readonly */
int refs;
bool resizable;
IntRect resizeBorder;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool selected;
IntVector2 size;
bool sortChildren;
String style;
bool temporary;
TraversalMode traversalMode;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
int weakRefs;
int width;
};

class XMLElement
{
// Methods:
XMLElement CreateChild(const String&);
String GetAttribute(const String& = String ( )) const;
String GetAttributeLower(const String&) const;
Array<String> GetAttributeNames() const;
String GetAttributeUpper(const String&) const;
bool GetBool(const String&) const;
BoundingBox GetBoundingBox() const;
XMLElement GetChild(const String& = String ( )) const;
Color GetColor(const String&) const;
float GetFloat(const String&) const;
int GetInt(const String&) const;
XMLElement GetNext(const String& = String ( )) const;
Quaternion GetQuaternion(const String&) const;
ResourceRef GetResourceRef() const;
ResourceRefList GetResourceRefList() const;
uint GetUInt(const String&) const;
String GetValue() const;
Variant GetVariant() const;
VariantMap GetVariantMap() const;
Array<Variant> GetVariantVector() const;
Vector2 GetVector2(const String&) const;
Vector3 GetVector3(const String&) const;
Vector4 GetVector4(const String&) const;
Variant GetVectorVariant(const String&) const;
bool HasAttribute(const String&) const;
bool HasChild(const String&) const;
bool RemoveAttribute(const String& = String ( ));
bool RemoveChild(const String&);
bool RemoveChild(const XMLElement&);
bool RemoveChildren(const String& = String ( ));
XPathResultSet Select(const String&);
XPathResultSet SelectPrepared(const XPathQuery&);
XMLElement SelectSingle(const String&);
XMLElement SelectSinglePrepared(const XPathQuery&);
bool SetAttribute(const String&);
bool SetAttribute(const String&, const String&);
bool SetBool(const String&, bool);
bool SetBoundingBox(const BoundingBox&);
bool SetColor(const String&, const Color&);
bool SetFloat(const String&, float);
bool SetInt(const String&, int);
bool SetQuaternion(const String&, const Quaternion&);
bool SetResourceRef(const String&, const ResourceRef&);
bool SetResourceRefList(const String&, const ResourceRefList&);
bool SetUInt(const String&, uint);
bool SetValue(const String&);
bool SetVariant(const Variant&);
bool SetVariantMap(const VariantMap&);
bool SetVariantVector(Array<Variant>);
bool SetVector2(const String&, const Vector2&);
bool SetVector3(const String&, const Vector3&);
bool SetVector4(const String&, const Vector4&);
bool SetVectorVariant(const String&, const Variant&);

// Properties:
/* readonly */
XMLFile file;
/* readonly */
bool isNull;
/* readonly */
String name;
/* readonly */
XMLElement nextResult;
/* readonly */
bool notNull;
/* readonly */
uint numAttributes;
/* readonly */
XMLElement parent;
String value;
};

class XMLFile
{
// Methods:
XMLElement CreateRoot(const String&);
XMLElement GetRoot(const String& = String ( ));
bool Load(File);
void Patch(XMLElement);
void Patch(XMLFile);
bool Save(File) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
ShortStringHash baseType;
/* readonly */
String category;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
/* readonly */
XMLElement root;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class XPathQuery
{
// Methods:
void Bind();
void Clear();
XPathResultSet Evaluate(XMLElement);
bool EvaluateToBool(XMLElement);
float EvaluateToFloat(XMLElement);
String EvaluateToString(XMLElement);
bool SetQuery(const String&, const String& = String ( ), bool = true);
bool SetVariable(const String&, bool);
bool SetVariable(const String&, const String&);
bool SetVariable(const String&, const XPathResultSet&);
bool SetVariable(const String&, float);

// Properties:
String query;
};

class XPathResultSet
{

// Properties:
/* readonly */
bool empty;
/* readonly */
XMLElement firstResult;
/* readonly */
uint size;
};

class Zone
{
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool IsInView(Camera) const;
bool Load(File, bool = false);
bool LoadXML(const XMLElement&, bool = false);
void MarkNetworkUpdate() const;
void Remove();
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);

// Properties:
Color ambientColor;
/* readonly */
Color ambientEndColor;
bool ambientGradient;
/* readonly */
Color ambientStartColor;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
ShortStringHash baseType;
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool enabled;
/* readonly */
bool enabledEffective;
Color fogColor;
float fogEnd;
float fogHeight;
float fogHeightScale;
float fogStart;
bool heightFog;
/* readonly */
uint id;
/* readonly */
bool inView;
/* readonly */
Matrix3x4 inverseWorldTransform;
uint lightMask;
float lodBias;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
bool occludee;
bool occluder;
bool override;
int priority;
/* readonly */
int refs;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
ShortStringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
uint zoneMask;
};

// Enumerations

enum BlendMode
{
BLEND_REPLACE,
BLEND_ADD,
BLEND_MULTIPLY,
BLEND_ALPHA,
BLEND_ADDALPHA,
BLEND_PREMULALPHA,
BLEND_INVDESTALPHA,
BLEND_SUBTRACT,
BLEND_SUBTRACTALPHA,
};

enum BodyType2D
{
BT_STATIC,
BT_DYNAMIC,
BT_KINEMATIC,
};

enum CollisionEventMode
{
COLLISION_NEVER,
COLLISION_ACTIVE,
COLLISION_ALWAYS,
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

enum ConstraintType
{
CONSTRAINT_POINT,
CONSTRAINT_HINGE,
CONSTRAINT_SLIDER,
CONSTRAINT_CONETWIST,
};

enum Corner
{
C_TOPLEFT,
C_TOPRIGHT,
C_BOTTOMLEFT,
C_BOTTOMRIGHT,
};

enum CreateMode
{
REPLICATED,
LOCAL,
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

enum CullMode
{
CULL_NONE,
CULL_CCW,
CULL_CW,
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

enum CycleMode
{
CM_LOOP,
CM_CLAMP,
CM_PINGPONG,
};

enum DumpMode
{
DOXYGEN,
C_HEADER,
};

enum EmitterType
{
EMITTER_SPHERE,
EMITTER_BOX,
};

enum EmitterType2D
{
EMITTER_TYPE_GRAVITY,
EMITTER_TYPE_RADIAL,
};

enum FileMode
{
FILE_READ,
FILE_WRITE,
FILE_READWRITE,
};

enum FillMode
{
FILL_SOLID,
FILL_WIREFRAME,
FILL_POINT,
};

enum FocusMode
{
FM_NOTFOCUSABLE,
FM_RESETFOCUS,
FM_FOCUSABLE,
FM_FOCUSABLE_DEFOCUSABLE,
};

enum HighlightMode
{
HM_NEVER,
HM_FOCUS,
HM_ALWAYS,
};

enum HorizontalAlignment
{
HA_LEFT,
HA_CENTER,
HA_RIGHT,
};

enum HttpRequestState
{
HTTP_INITIALIZING,
HTTP_ERROR,
HTTP_OPEN,
HTTP_CLOSED,
};

enum InterpolationMode
{
BEZIER_CURVE,
};

enum Intersection
{
OUTSIDE,
INTERSECTS,
INSIDE,
};

enum LayoutMode
{
LM_FREE,
LM_HORIZONTAL,
LM_VERTICAL,
};

enum LightType
{
LIGHT_DIRECTIONAL,
LIGHT_SPOT,
LIGHT_POINT,
};

enum Orientation
{
O_HORIZONTAL,
O_VERTICAL,
};

enum PassLightingMode
{
LIGHTING_UNLIT,
LIGHTING_PERVERTEX,
LIGHTING_PERPIXEL,
};

enum PrimitiveType
{
TRIANGLE_LIST,
LINE_LIST,
};

enum RayQueryLevel
{
RAY_AABB,
RAY_OBB,
RAY_TRIANGLE,
};

enum RenderCommandSortMode
{
SORT_FRONTTOBACK,
SORT_BACKTOFRONT,
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

enum RenderSurfaceUpdateMode
{
SURFACE_MANUALUPDATE,
SURFACE_UPDATEVISIBLE,
SURFACE_UPDATEALWAYS,
};

enum RenderTargetSizeMode
{
SIZE_ABSOLUTE,
SIZE_RENDERTARGETDIVISOR,
SIZE_VIEWPORTDIVISOR,
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

enum SoundType
{
SOUND_EFFECT,
SOUND_AMBIENT,
SOUND_VOICE,
SOUND_MUSIC,
SOUND_MASTER,
};

enum TextEffect
{
TE_NONE,
TE_SHADOW,
TE_STROKE,
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

enum TextureFilterMode
{
FILTER_NEAREST,
FILTER_BILINEAR,
FILTER_TRILINEAR,
FILTER_ANISOTROPIC,
FILTER_DEFAULT,
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
TU_VOLUMEMAP,
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

enum TraversalMode
{
TM_BREADTH_FIRST,
TM_DEPTH_FIRST,
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
VAR_VOIDPTR,
VAR_RESOURCEREF,
VAR_RESOURCEREFLIST,
VAR_VARIANTVECTOR,
VAR_VARIANTMAP,
VAR_INTRECT,
VAR_INTVECTOR2,
VAR_PTR,
};

enum VerticalAlignment
{
VA_TOP,
VA_CENTER,
VA_BOTTOM,
};

// Global functions
float Abs(float);
float Acos(float);
String AddTrailingSlash(const String&);
float Asin(float);
float Atan(float);
float Atan2(float, float);
float Ceil(float);
float Clamp(float, float, float);
int Clamp(int, int, int);
void ClearDelayedExecute(const String& = String ( ));
float Cos(float);
void DelayedExecute(float, bool, const String&);
void DelayedExecute(float, bool, const String&, const Array<Variant>);
bool Equals(float, float);
void ErrorDialog(const String&, const String&);
float Floor(float);
uint GetAlphaFormat();
Array<String> GetArguments();
String GetConsoleInput();
uint GetDepthStencilFormat();
Object GetEventSender();
String GetExtension(const String&, bool = true);
String GetFileName(const String&);
String GetFileNameAndExtension(const String&, bool = false);
uint GetFloat16Format();
uint GetFloat32Format();
uint GetFormat(const String&);
String GetInternalPath(const String&);
uint GetLuminanceAlphaFormat();
uint GetLuminanceFormat();
uint GetNumLogicalCPUs();
uint GetNumPhysicalCPUs();
Array<String> GetObjectCategories();
Array<String> GetObjectsByCategory(const String&);
String GetParentPath(const String&);
String GetPath(const String&);
String GetPlatform();
uint GetRG16Format();
uint GetRGBA16Format();
uint GetRGBAFloat16Format();
uint GetRGBAFloat32Format();
uint GetRGBAFormat();
uint GetRGBFormat();
uint GetRGFloat16Format();
uint GetRGFloat32Format();
uint GetRandomSeed();
String GetTextureUnitName(TextureUnit);
bool IsAbsolutePath(const String&);
bool IsAlpha(uint);
bool IsDigit(uint);
bool IsNaN(float);
bool IsPowerOfTwo(uint);
String Join(Array<String>&, const String&);
float Lerp(float, float, float);
void MarkNetworkUpdate();
float Max(float, float);
int Max(int, int);
float Min(float, float);
int Min(int, int);
float Mod(float, float);
uint NextPowerOfTwo(uint);
void OpenConsoleWindow();
float Pow(float, float);
void Print(bool, bool = false);
void Print(const String&, bool = false);
void Print(const Variant&, bool = false);
void Print(float, bool = false);
void Print(int, bool = false);
void Print(uint, bool = false);
void PrintCallStack(bool = false);
float Random();
float Random(float);
float Random(float, float);
int RandomInt();
int RandomInt(int);
int RandomInt(int, int);
float RandomNormal(float, float);
void Remove();
String RemoveTrailingSlash(const String&);
String ReplaceExtension(const String&, const String&);
uint SDBMHash(uint, uint8);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetRandomSeed(uint);
float Sign(float);
float Sin(float);
float SmoothStep(float, float, float);
float Sqrt(float);
const String& GetTypeName(ShortStringHash);
void SubscribeToEvent(Object, const String&, const String&);
void SubscribeToEvent(const String&, const String&);
float Tan(float);
uint ToLower(uint);
String ToStringHex(int);
uint ToUpper(uint);
void UnsubscribeFromAllEvents();
void UnsubscribeFromAllEventsExcept(Array<String>);
void UnsubscribeFromEvent(Object, const String&);
void UnsubscribeFromEvent(const String&);
void UnsubscribeFromEvents(Object);

// Global properties
Audio audio;
ResourceCache cache;
Console console;
DebugHud debugHud;
DebugRenderer debugRenderer;
Engine engine;
FileSystem fileSystem;
Graphics graphics;
Input input;
Log log;
Network network;
Node node;
Octree octree;
PhysicsWorld physicsWorld;
PhysicsWorld2D physicsWorld2D;
Renderer renderer;
ResourceCache resourceCache;
Scene scene;
Script script;
ScriptFile scriptFile;
ScriptInstance self;
Time time;
UI ui;

// Global constants
uint AM_COMPONENTID;
uint AM_DEFAULT;
uint AM_FILE;
uint AM_LATESTDATA;
uint AM_NET;
uint AM_NODEID;
uint AM_NODEIDVECTOR;
uint AM_NOEDIT;
int CONTROLLER_AXIS_LEFTX;
int CONTROLLER_AXIS_LEFTY;
int CONTROLLER_AXIS_RIGHTX;
int CONTROLLER_AXIS_RIGHTY;
int CONTROLLER_AXIS_TRIGGERLEFT;
int CONTROLLER_AXIS_TRIGGERRIGHT;
int CONTROLLER_BUTTON_A;
int CONTROLLER_BUTTON_B;
int CONTROLLER_BUTTON_BACK;
int CONTROLLER_BUTTON_DPAD_DOWN;
int CONTROLLER_BUTTON_DPAD_LEFT;
int CONTROLLER_BUTTON_DPAD_RIGHT;
int CONTROLLER_BUTTON_DPAD_UP;
int CONTROLLER_BUTTON_GUIDE;
int CONTROLLER_BUTTON_LEFTSHOULDER;
int CONTROLLER_BUTTON_LEFTSTICK;
int CONTROLLER_BUTTON_RIGHTSHOULDER;
int CONTROLLER_BUTTON_RIGHTSTICK;
int CONTROLLER_BUTTON_START;
int CONTROLLER_BUTTON_X;
int CONTROLLER_BUTTON_Y;
uint DD_DISABLED;
uint DD_SOURCE;
uint DD_SOURCE_AND_TARGET;
uint DD_TARGET;
uint DEBUGHUD_SHOW_ALL;
uint DEBUGHUD_SHOW_MODE;
uint DEBUGHUD_SHOW_NONE;
uint DEBUGHUD_SHOW_PROFILER;
uint DEBUGHUD_SHOW_STATS;
uint DEFAULT_LIGHTMASK;
uint DEFAULT_VIEWMASK;
uint DRAWABLE_ANY;
uint DRAWABLE_GEOMETRY;
uint DRAWABLE_LIGHT;
uint DRAWABLE_ZONE;
uint FIRST_LOCAL_ID;
uint FIRST_REPLICATED_ID;
int HAT_CENTER;
int HAT_DOWN;
int HAT_LEFT;
int HAT_RIGHT;
int HAT_UP;
int KEY_0;
int KEY_1;
int KEY_2;
int KEY_3;
int KEY_4;
int KEY_5;
int KEY_6;
int KEY_7;
int KEY_8;
int KEY_9;
int KEY_A;
int KEY_ALT;
int KEY_APPLICATION;
int KEY_B;
int KEY_BACKSPACE;
int KEY_C;
int KEY_CAPSLOCK;
int KEY_CTRL;
int KEY_D;
int KEY_DELETE;
int KEY_DOWN;
int KEY_E;
int KEY_END;
int KEY_ESC;
int KEY_F;
int KEY_F1;
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
int KEY_F2;
int KEY_F20;
int KEY_F21;
int KEY_F22;
int KEY_F23;
int KEY_F24;
int KEY_F3;
int KEY_F4;
int KEY_F5;
int KEY_F6;
int KEY_F7;
int KEY_F8;
int KEY_F9;
int KEY_G;
int KEY_GUI;
int KEY_H;
int KEY_HOME;
int KEY_I;
int KEY_INSERT;
int KEY_J;
int KEY_K;
int KEY_KP_0;
int KEY_KP_1;
int KEY_KP_2;
int KEY_KP_3;
int KEY_KP_4;
int KEY_KP_5;
int KEY_KP_6;
int KEY_KP_7;
int KEY_KP_8;
int KEY_KP_9;
int KEY_KP_DIVIDE;
int KEY_KP_ENTER;
int KEY_KP_MINUS;
int KEY_KP_MULTIPLY;
int KEY_KP_PERIOD;
int KEY_KP_PLUS;
int KEY_L;
int KEY_LALT;
int KEY_LCTRL;
int KEY_LEFT;
int KEY_LGUI;
int KEY_LSHIFT;
int KEY_M;
int KEY_N;
int KEY_NUMLOCKCLEAR;
int KEY_O;
int KEY_P;
int KEY_PAGEDOWN;
int KEY_PAGEUP;
int KEY_PAUSE;
int KEY_PRINTSCREEN;
int KEY_Q;
int KEY_R;
int KEY_RALT;
int KEY_RCTRL;
int KEY_RETURN;
int KEY_RETURN2;
int KEY_RGUI;
int KEY_RIGHT;
int KEY_RSHIFT;
int KEY_S;
int KEY_SCROLLLOCK;
int KEY_SELECT;
int KEY_SHIFT;
int KEY_SPACE;
int KEY_T;
int KEY_TAB;
int KEY_U;
int KEY_UP;
int KEY_V;
int KEY_W;
int KEY_X;
int KEY_Y;
int KEY_Z;
uint LAST_LOCAL_ID;
uint LAST_REPLICATED_ID;
int LOG_DEBUG;
int LOG_ERROR;
int LOG_INFO;
int LOG_NONE;
int LOG_WARNING;
int MOUSEB_LEFT;
int MOUSEB_MIDDLE;
int MOUSEB_RIGHT;
float M_DEGTORAD;
float M_DEGTORAD_2;
float M_EPSILON;
float M_HALF_PI;
float M_INFINITY;
float M_LARGE_EPSILON;
float M_LARGE_VALUE;
int M_MAX_INT;
uint M_MAX_UNSIGNED;
int M_MIN_INT;
uint M_MIN_UNSIGNED;
float M_PI;
float M_RADTODEG;
float PIXEL_SIZE;
int QUALITY_HIGH;
int QUALITY_LOW;
int QUALITY_MAX;
int QUALITY_MEDIUM;
int QUAL_ALT;
int QUAL_ANY;
int QUAL_CTRL;
int QUAL_SHIFT;
int SCANCODE_0;
int SCANCODE_1;
int SCANCODE_2;
int SCANCODE_3;
int SCANCODE_4;
int SCANCODE_5;
int SCANCODE_6;
int SCANCODE_7;
int SCANCODE_8;
int SCANCODE_9;
int SCANCODE_A;
int SCANCODE_AC_BACK;
int SCANCODE_AC_BOOKMARKS;
int SCANCODE_AC_FORWARD;
int SCANCODE_AC_HOME;
int SCANCODE_AC_REFRESH;
int SCANCODE_AC_SEARCH;
int SCANCODE_AC_STOP;
int SCANCODE_AGAIN;
int SCANCODE_ALT;
int SCANCODE_ALTERASE;
int SCANCODE_APOSTROPHE;
int SCANCODE_APP1;
int SCANCODE_APP2;
int SCANCODE_APPLICATION;
int SCANCODE_AUDIOMUTE;
int SCANCODE_AUDIONEXT;
int SCANCODE_AUDIOPLAY;
int SCANCODE_AUDIOPREV;
int SCANCODE_AUDIOSTOP;
int SCANCODE_B;
int SCANCODE_BACKSLASH;
int SCANCODE_BACKSPACE;
int SCANCODE_BRIGHTNESSDOWN;
int SCANCODE_BRIGHTNESSUP;
int SCANCODE_C;
int SCANCODE_CALCULATOR;
int SCANCODE_CANCEL;
int SCANCODE_CAPSLOCK;
int SCANCODE_CLEAR;
int SCANCODE_CLEARAGAIN;
int SCANCODE_COMMA;
int SCANCODE_COMPUTER;
int SCANCODE_COPY;
int SCANCODE_CRSEL;
int SCANCODE_CTRL;
int SCANCODE_CURRENCYSUBUNIT;
int SCANCODE_CURRENCYUNIT;
int SCANCODE_CUT;
int SCANCODE_D;
int SCANCODE_DECIMALSEPARATOR;
int SCANCODE_DELETE;
int SCANCODE_DISPLAYSWITCH;
int SCANCODE_DOWN;
int SCANCODE_E;
int SCANCODE_EJECT;
int SCANCODE_END;
int SCANCODE_EQUALS;
int SCANCODE_ESCAPE;
int SCANCODE_EXECUTE;
int SCANCODE_EXSEL;
int SCANCODE_F;
int SCANCODE_F1;
int SCANCODE_F10;
int SCANCODE_F11;
int SCANCODE_F12;
int SCANCODE_F13;
int SCANCODE_F14;
int SCANCODE_F15;
int SCANCODE_F16;
int SCANCODE_F17;
int SCANCODE_F18;
int SCANCODE_F19;
int SCANCODE_F2;
int SCANCODE_F20;
int SCANCODE_F21;
int SCANCODE_F22;
int SCANCODE_F23;
int SCANCODE_F24;
int SCANCODE_F3;
int SCANCODE_F4;
int SCANCODE_F5;
int SCANCODE_F6;
int SCANCODE_F7;
int SCANCODE_F8;
int SCANCODE_F9;
int SCANCODE_FIND;
int SCANCODE_G;
int SCANCODE_GRAVE;
int SCANCODE_GUI;
int SCANCODE_H;
int SCANCODE_HELP;
int SCANCODE_HOME;
int SCANCODE_I;
int SCANCODE_INSERT;
int SCANCODE_INTERNATIONAL1;
int SCANCODE_INTERNATIONAL2;
int SCANCODE_INTERNATIONAL3;
int SCANCODE_INTERNATIONAL4;
int SCANCODE_INTERNATIONAL5;
int SCANCODE_INTERNATIONAL6;
int SCANCODE_INTERNATIONAL7;
int SCANCODE_INTERNATIONAL8;
int SCANCODE_INTERNATIONAL9;
int SCANCODE_J;
int SCANCODE_K;
int SCANCODE_KBDILLUMDOWN;
int SCANCODE_KBDILLUMTOGGLE;
int SCANCODE_KBDILLUMUP;
int SCANCODE_KP_0;
int SCANCODE_KP_00;
int SCANCODE_KP_000;
int SCANCODE_KP_1;
int SCANCODE_KP_2;
int SCANCODE_KP_3;
int SCANCODE_KP_4;
int SCANCODE_KP_5;
int SCANCODE_KP_6;
int SCANCODE_KP_7;
int SCANCODE_KP_8;
int SCANCODE_KP_9;
int SCANCODE_KP_A;
int SCANCODE_KP_AMPERSAND;
int SCANCODE_KP_AT;
int SCANCODE_KP_B;
int SCANCODE_KP_BACKSPACE;
int SCANCODE_KP_BINARY;
int SCANCODE_KP_C;
int SCANCODE_KP_CLEAR;
int SCANCODE_KP_CLEARENTRY;
int SCANCODE_KP_COLON;
int SCANCODE_KP_COMMA;
int SCANCODE_KP_D;
int SCANCODE_KP_DBLAMPERSAND;
int SCANCODE_KP_DBLVERTICALBAR;
int SCANCODE_KP_DECIMAL;
int SCANCODE_KP_DIVIDE;
int SCANCODE_KP_E;
int SCANCODE_KP_ENTER;
int SCANCODE_KP_EQUALS;
int SCANCODE_KP_EQUALSAS400;
int SCANCODE_KP_EXCLAM;
int SCANCODE_KP_F;
int SCANCODE_KP_GREATER;
int SCANCODE_KP_HASH;
int SCANCODE_KP_HEXADECIMAL;
int SCANCODE_KP_LEFTBRACE;
int SCANCODE_KP_LEFTPAREN;
int SCANCODE_KP_LESS;
int SCANCODE_KP_MEMADD;
int SCANCODE_KP_MEMCLEAR;
int SCANCODE_KP_MEMDIVIDE;
int SCANCODE_KP_MEMMULTIPLY;
int SCANCODE_KP_MEMRECALL;
int SCANCODE_KP_MEMSTORE;
int SCANCODE_KP_MEMSUBTRACT;
int SCANCODE_KP_MINUS;
int SCANCODE_KP_MULTIPLY;
int SCANCODE_KP_OCTAL;
int SCANCODE_KP_PERCENT;
int SCANCODE_KP_PERIOD;
int SCANCODE_KP_PLUS;
int SCANCODE_KP_PLUSMINUS;
int SCANCODE_KP_POWER;
int SCANCODE_KP_RIGHTBRACE;
int SCANCODE_KP_RIGHTPAREN;
int SCANCODE_KP_SPACE;
int SCANCODE_KP_TAB;
int SCANCODE_KP_VERTICALBAR;
int SCANCODE_KP_XOR;
int SCANCODE_L;
int SCANCODE_LALT;
int SCANCODE_LANG1;
int SCANCODE_LANG2;
int SCANCODE_LANG3;
int SCANCODE_LANG4;
int SCANCODE_LANG5;
int SCANCODE_LANG6;
int SCANCODE_LANG7;
int SCANCODE_LANG8;
int SCANCODE_LANG9;
int SCANCODE_LCTRL;
int SCANCODE_LEFT;
int SCANCODE_LEFTBRACKET;
int SCANCODE_LGUI;
int SCANCODE_LSHIFT;
int SCANCODE_M;
int SCANCODE_MAIL;
int SCANCODE_MEDIASELECT;
int SCANCODE_MENU;
int SCANCODE_MINUS;
int SCANCODE_MODE;
int SCANCODE_MUTE;
int SCANCODE_N;
int SCANCODE_NONUSBACKSLASH;
int SCANCODE_NONUSHASH;
int SCANCODE_NUMLOCKCLEAR;
int SCANCODE_O;
int SCANCODE_OPER;
int SCANCODE_OUT;
int SCANCODE_P;
int SCANCODE_PAGEDOWN;
int SCANCODE_PAGEUP;
int SCANCODE_PASTE;
int SCANCODE_PAUSE;
int SCANCODE_PERIOD;
int SCANCODE_POWER;
int SCANCODE_PRINTSCREEN;
int SCANCODE_PRIOR;
int SCANCODE_Q;
int SCANCODE_R;
int SCANCODE_RALT;
int SCANCODE_RCTRL;
int SCANCODE_RETURN;
int SCANCODE_RETURN2;
int SCANCODE_RGUI;
int SCANCODE_RIGHT;
int SCANCODE_RIGHTBRACKET;
int SCANCODE_RSHIFT;
int SCANCODE_S;
int SCANCODE_SCROLLLOCK;
int SCANCODE_SELECT;
int SCANCODE_SEMICOLON;
int SCANCODE_SEPARATOR;
int SCANCODE_SHIFT;
int SCANCODE_SLASH;
int SCANCODE_SLEEP;
int SCANCODE_SPACE;
int SCANCODE_STOP;
int SCANCODE_SYSREQ;
int SCANCODE_T;
int SCANCODE_TAB;
int SCANCODE_THOUSANDSSEPARATOR;
int SCANCODE_U;
int SCANCODE_UNDO;
int SCANCODE_UNKNOWN;
int SCANCODE_UP;
int SCANCODE_V;
int SCANCODE_VOLUMEDOWN;
int SCANCODE_VOLUMEUP;
int SCANCODE_W;
int SCANCODE_WWW;
int SCANCODE_X;
int SCANCODE_Y;
int SCANCODE_Z;
uint SCAN_DIRS;
uint SCAN_FILES;
uint SCAN_HIDDEN;
int SHADOWQUALITY_HIGH_16BIT;
int SHADOWQUALITY_HIGH_24BIT;
int SHADOWQUALITY_LOW_16BIT;
int SHADOWQUALITY_LOW_24BIT;
uint VO_DISABLE_OCCLUSION;
uint VO_DISABLE_SHADOWS;
uint VO_LOW_MATERIAL_QUALITY;
uint VO_NONE;
