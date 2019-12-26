// Script API header intended to be 'force included' in IDE for AngelScript content assist / code completion

#define int8 signed char
#define int16 signed short
#define int64 long
#define uint8 unsigned char
#define uint16 unsigned short
#define uint64 unsigned long
#define null 0
#define in
#define out
#define inout
#define is ==
#define interface struct
#define class struct
#define cast reinterpret_cast
#define mixin
#define funcdef

// Classes

class Animatable
{
public:
// Methods:
void ApplyAttributes();
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
/* readonly */
int refs;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class AnimatedModel
{
public:
// Methods:
AnimationState AddAnimationState(Animation);
void ApplyAttributes();
void ApplyMaterialList(const String& = String ( ));
void DrawDebugGeometry(DebugRenderer, bool);
AnimationState GetAnimationState(Animation) const;
AnimationState GetAnimationState(uint) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
float GetMorphWeight(uint) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllAnimationStates();
void RemoveAnimationState(Animation);
void RemoveAnimationState(AnimationState);
void RemoveAnimationState(const String&);
void RemoveAnimationState(uint);
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetMorphWeights();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
void SetMorphWeight(uint, float);
void UpdateBoneBoundingBox();

// Properties:
bool animationEnabled;
float animationLodBias;
/* readonly */
Array<AnimationState> animationStates;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
/* readonly */
Skeleton skeleton;
bool temporary;
/* readonly */
StringHash type;
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
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimation(const String&, LoopMode2D = LM_DEFAULT);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetFlip(bool, bool, bool = false);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
float alpha;
String animation;
bool animationEnabled;
AnimationSet2D animationSet;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
BlendMode blendMode;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
Color color;
Material customMaterial;
float drawDistance;
Rect drawRect;
bool enabled;
/* readonly */
bool enabledEffective;
String entity;
bool flipX;
bool flipY;
Vector2 hotSpot;
/* readonly */
uint id;
/* readonly */
bool inView;
int layer;
uint lightMask;
float lodBias;
LoopMode2D loopMode;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
int orderInLayer;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
float speed;
Sprite2D sprite;
bool swapXY;
bool temporary;
Rect textureRect;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDrawRect;
bool useHotSpot;
bool useTextureRect;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
uint zoneMask;
};

class Animation
{
public:
Animation();
Animation(const String&in);
// Methods:
void AddMetadata(const String&, const Variant&);
void AddTrigger(const AnimationTriggerPoint&);
void AddTrigger(float, bool, const Variant&);
Animation Clone(const String& = String ( )) const;
AnimationTrack CreateTrack(const String&);
AnimationTrack GetTrack(uint);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
void RemoveAllMetadata();
bool RemoveAllTracks();
void RemoveAllTriggers();
void RemoveMetadata(const String&);
bool RemoveTrack(const String&);
void RemoveTrigger(uint);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
String animationName;
/* readonly */
String category;
/* readonly */
bool hasMetadata;
float length;
/* readonly */
uint memoryUse;
Array<Variant> metadata;
String name;
/* readonly */
uint numTracks;
uint numTriggers;
/* readonly */
int refs;
/* readonly */
Array<AnimationTrack> tracks;
Array<AnimationTriggerPoint> triggers;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class AnimationControl
{
public:

// Properties:
float autoFadeTime;
float fadeTime;
StringHash hash;
String name;
bool removeOnCompletion;
float speed;
float targetWeight;
};

class AnimationController
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
bool Fade(const String&, float, float);
bool FadeOthers(const String&, float, float);
AnimationState GetAnimationState(StringHash) const;
AnimationState GetAnimationState(const String&) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
float GetAutoFade(const String&) const;
AnimationBlendMode GetBlendMode(const String&) const;
float GetFadeTarget(const String&) const;
float GetFadeTime(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
uint8 GetLayer(const String&) const;
float GetLength(const String&) const;
bool GetLooped(const String&) const;
bool GetRemoveOnCompletion(const String&);
float GetSpeed(const String&) const;
float GetTime(const String&) const;
float GetWeight(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsAtEnd(const String&) const;
bool IsFadingIn(const String&) const;
bool IsFadingOut(const String&) const;
bool IsPlaying(const String&) const;
bool IsPlaying(uint8) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
bool Play(const String&, uint8, bool, float = 0.0f);
bool PlayExclusive(const String&, uint8, bool, float = 0.0f);
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
bool SetAutoFade(const String&, float);
bool SetBlendMode(const String&, AnimationBlendMode);
void SetInterceptNetworkUpdate(const String&, bool);
bool SetLayer(const String&, uint8);
bool SetLooped(const String&, bool);
bool SetRemoveOnCompletion(const String&, bool);
bool SetSpeed(const String&, float);
bool SetStartBone(const String&, const String&);
bool SetTime(const String&, float);
bool SetWeight(const String&, float);
void Stop(const String&, float = 0.0f);
void StopAll(float = 0.0f);
void StopLayer(uint8, float = 0.0f);
const String& GetStartBone(const String&) const;

// Properties:
bool animationEnabled;
/* readonly */
Array<AnimationControl> animations;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
uint numAnimations;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class AnimationKeyFrame
{
public:
~AnimationKeyFrame();
AnimationKeyFrame();
AnimationKeyFrame(const AnimationKeyFrame&in);

// Properties:
Vector3 position;
Quaternion rotation;
Vector3 scale;
float time;
};

class AnimationSet2D
{
public:
AnimationSet2D();
AnimationSet2D(const String&in);
// Methods:
String GetAnimation(uint) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String category;
/* readonly */
uint memoryUse;
String name;
/* readonly */
uint numAnimations;
/* readonly */
int refs;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class AnimationState
{
public:
AnimationState(Node&, Animation&);
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
AnimationBlendMode blendMode;
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

class AnimationTrack
{
public:
// Methods:
void AddKeyFrame(const AnimationKeyFrame&);
void InsertKeyFrame(uint, const AnimationKeyFrame&);
void RemoveAllKeyFrames();
void RemoveKeyFrame(uint);

// Properties:
uint8 channelMask;
Array<AnimationKeyFrame> keyFrames;
String name;
StringHash nameHash;
/* readonly */
uint numKeyFrames;
};

class AnimationTriggerPoint
{
public:
~AnimationTriggerPoint();
AnimationTriggerPoint();
AnimationTriggerPoint(const AnimationTriggerPoint&in);

// Properties:
Variant data;
float time;
};

template <class T>
class Array
{
public:
Array(int&in);
Array(int&in, uint);
Array(int&in, uint, const T&in);
// Methods:
void Clear();
void Erase(uint);
int Find(const T&) const;
int Find(uint, const T&) const;
int FindByRef(const T&) const;
int FindByRef(uint, const T&) const;
void Insert(uint, const T&);
void Pop();
void Push(const T&);
void Reserve(uint);
void Resize(uint);
void Reverse();
void Sort();
void Sort(uint, uint);
void SortReverse();
void SortReverse(uint, uint);
bool Swap(Array<T>&);

// Properties:
/* readonly */
bool empty;
uint length;
};

class AttributeInfo
{
public:
~AttributeInfo();
AttributeInfo();
AttributeInfo(const AttributeInfo&in);

// Properties:
Variant defaultValue;
/* readonly */
Array<String> enumNames;
VariantMap metadata;
uint mode;
String name;
VariantType type;
};

class Audio
{
public:
// Methods:
bool HasMasterGain(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsSoundTypePaused(const String&);
void PauseSoundType(const String&);
bool Play();
void ResumeAll();
void ResumeSoundType(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetMode(int, int, bool, bool = true);
void Stop();

// Properties:
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
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class BiasParameters
{
public:
BiasParameters();
BiasParameters(const BiasParameters&in);
BiasParameters(float, float, float normalOffset = 0.0f);

// Properties:
float constantBias;
float normalOffset;
float slopeScaledBias;
};

class Billboard
{
public:

// Properties:
Color color;
Vector3 direction;
bool enabled;
Vector3 position;
float rotation;
Vector2 size;
Rect uv;
};

class BillboardSet
{
public:
// Methods:
void ApplyAttributes();
void Commit();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
float animationLodBias;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
FaceCameraMode faceCameraMode;
bool fixedScreenSize;
/* readonly */
uint id;
/* readonly */
bool inView;
uint lightMask;
float lodBias;
Material material;
uint maxLights;
float minAngle;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
uint numBillboards;
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
/* readonly */
int refs;
bool relative;
/* readonly */
bool replicated;
bool scaled;
float shadowDistance;
uint shadowMask;
bool sorted;
bool temporary;
/* readonly */
StringHash type;
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
public:

// Properties:
bool animated;
BoundingBox boundingBox;
Vector3 initialPosition;
Quaternion initialRotation;
Vector3 initialScale;
String name;
Node node;
uint parentIndex;
float radius;
};

class BorderImage
{
public:
BorderImage();
BorderImage(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetDisabledOffset(int, int);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
IntVector2 disabledOffset;
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
IntRect imageBorder;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Material material;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
ObjectAnimation objectAnimation;
float opacity;
UIElement parent;
Vector2 pivot;
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
/* readonly */
Array<String> tags;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class BoundingBox
{
public:
BoundingBox();
BoundingBox(const BoundingBox&in);
BoundingBox(const Rect&in);
BoundingBox(const Vector3&in, const Vector3&in);
BoundingBox(float, float);
BoundingBox(const Frustum&in);
BoundingBox(const Polyhedron&in);
BoundingBox(const Sphere&in);
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
bool Defined() const;
float DistanceToPoint(const Vector3&) const;
Intersection IsInside(const BoundingBox&) const;
Intersection IsInside(const Sphere&) const;
Intersection IsInside(const Vector3&) const;
Intersection IsInsideFast(const BoundingBox&) const;
Intersection IsInsideFast(const Sphere&) const;
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
/* readonly */
Vector3 halfSize;
Vector3 max;
Vector3 min;
/* readonly */
Vector3 size;
};

class Button
{
public:
Button();
Button(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetDisabledOffset(int, int);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetPressedChildOffset(int, int);
void SetPressedOffset(int, int);
void SetRepeat(float, float);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
IntVector2 disabledOffset;
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
IntRect imageBorder;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Material material;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
ObjectAnimation objectAnimation;
float opacity;
UIElement parent;
Vector2 pivot;
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
/* readonly */
Array<String> tags;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class Camera
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
float GetDistance(const Vector3&) const;
float GetDistanceSquared(const Vector3&) const;
bool GetInterceptNetworkUpdate(const String&) const;
Ray GetScreenRay(float, float) const;
Frustum GetSplitFrustum(float, float) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
Vector3 ScreenToWorldPoint(const Vector3&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
void SetOrthoSize(const Vector2&);
Vector2 WorldToScreenPoint(const Vector3&) const;

// Properties:
bool animationEnabled;
float aspectRatio;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool autoAspectRatio;
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
Matrix4 gpuProjection;
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
ObjectAnimation objectAnimation;
float orthoSize;
bool orthographic;
Matrix4 projection;
Vector2 projectionOffset;
Plane reflectionPlane;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
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
public:
CascadeParameters();
CascadeParameters(const CascadeParameters&in);
CascadeParameters(float, float, float, float, float, float biasAutoAdjust = 1.0);

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
public:
CheckBox();
CheckBox(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetCheckedOffset(int, int);
void SetDeepEnabled(bool);
void SetDisabledOffset(int, int);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
IntVector2 disabledOffset;
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
IntRect imageBorder;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Material material;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
ObjectAnimation objectAnimation;
float opacity;
UIElement parent;
Vector2 pivot;
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
/* readonly */
Array<String> tags;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class CollisionBox2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetCenter(float, float);
void SetInterceptNetworkUpdate(const String&, bool);
void SetSize(float, float);

// Properties:
float angle;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
float restitution;
Vector2 size;
bool temporary;
bool trigger;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class CollisionChain2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
Array<Vector2> GetVertices() const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
void SetVertex(uint, const Vector2&);
void SetVertices(Array<Vector2>);
const Vector2& GetVertex(uint) const;

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
float restitution;
bool temporary;
bool trigger;
/* readonly */
StringHash type;
/* readonly */
String typeName;
uint vertexCount;
/* readonly */
int weakRefs;
};

class CollisionCircle2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetCenter(float, float);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
float radius;
/* readonly */
int refs;
/* readonly */
bool replicated;
float restitution;
bool temporary;
bool trigger;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class CollisionEdge2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
void SetVertices(const Vector2&, const Vector2&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
float restitution;
bool temporary;
bool trigger;
/* readonly */
StringHash type;
/* readonly */
String typeName;
Vector2 vertex1;
Vector2 vertex2;
/* readonly */
int weakRefs;
};

class CollisionPolygon2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
Array<Vector2> GetVertices() const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
void SetVertex(uint, const Vector2&);
void SetVertices(Array<Vector2>);
const Vector2& GetVertex(uint) const;

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
float restitution;
bool temporary;
bool trigger;
/* readonly */
StringHash type;
/* readonly */
String typeName;
uint vertexCount;
/* readonly */
int weakRefs;
};

class CollisionShape
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetBox(const Vector3&, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetCapsule(float, float, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetCone(float, float, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetConvexHull(Model, uint = 0, const Vector3& = Vector3 ( 1 , 1 , 1 ), const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetCustomConvexHull(CustomGeometry, const Vector3& = Vector3 ( 1 , 1 , 1 ), const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetCustomTriangleMesh(CustomGeometry, const Vector3& = Vector3 ( 1 , 1 , 1 ), const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetCylinder(float, float, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetInterceptNetworkUpdate(const String&, bool);
void SetSphere(float, const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetStaticPlane(const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));
void SetTerrain(uint = 0);
void SetTransform(const Vector3&, const Quaternion&);
void SetTriangleMesh(Model, uint = 0, const Vector3& = Vector3 ( 1 , 1 , 1 ), const Vector3& = Vector3 ( ), const Quaternion& = Quaternion ( ));

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
Vector3 position;
/* readonly */
int refs;
/* readonly */
bool replicated;
Quaternion rotation;
ShapeType shapeType;
Vector3 size;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
};

class CollisionShape2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
float restitution;
bool temporary;
bool trigger;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Color
{
public:
Color();
Color(const Color&in);
Color(float, float, float, float);
Color(float, float, float);
Color(float[]&inout);
// Methods:
Color Abs() const;
float Average() const;
float Chroma() const;
void Clip(bool);
bool Equals() const;
void FromHSL(float, float, float, float);
void FromHSV(float, float, float, float);
void FromUInt(uint);
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
public:

// Properties:
Color color;
float time;
};

class Component
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Connection
{
public:
// Methods:
void Disconnect(int = 0);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SendMessage(int, bool, bool, const VectorBuffer&, uint = 0);
void SendPackageToClient(PackageFile);
void SendRemoteEvent(Node, const String&, bool, const VariantMap& = VariantMap ( ));
void SendRemoteEvent(const String&, bool, const VariantMap& = VariantMap ( ));
String ToString() const;

// Properties:
/* readonly */
String address;
/* readonly */
float bytesInPerSec;
/* readonly */
float bytesOutPerSec;
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
/* readonly */
uint lastHeardTime;
bool logStatistics;
/* readonly */
uint numDownloads;
/* readonly */
int packetsInPerSec;
/* readonly */
int packetsOutPerSec;
/* readonly */
uint16 port;
Vector3 position;
/* readonly */
int refs;
Quaternion rotation;
/* readonly */
float roundTripTime;
Scene scene;
/* readonly */
bool sceneLoaded;
uint8 timeStamp;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Console
{
public:
// Methods:
void AddAutoComplete(const String&);
void CopySelectedRows() const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void RemoveAutoComplete(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void Toggle();
void UpdateElements();

// Properties:
bool autoVisibleOnError;
/* readonly */
BorderImage background;
/* readonly */
String category;
/* readonly */
Button closeButton;
String commandInterpreter;
XMLFile defaultStyle;
bool focusOnShow;
/* readonly */
uint historyPosition;
/* readonly */
Array<String> historyRow;
/* readonly */
LineEdit lineEdit;
uint numBufferedRows;
uint numHistoryRows;
uint numRows;
/* readonly */
int refs;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool visible;
/* readonly */
int weakRefs;
};

class Constraint
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* writeonly */
Vector3 axis;
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
ObjectAnimation objectAnimation;
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
/* readonly */
bool replicated;
Quaternion rotation;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
Vector3 worldPosition;
};

class Constraint2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool collideConnected;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
RigidBody2D otherBody;
/* readonly */
RigidBody2D ownerBody;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ConstraintDistance2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool collideConnected;
float dampingRatio;
bool enabled;
/* readonly */
bool enabledEffective;
float frequencyHz;
/* readonly */
uint id;
float length;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
RigidBody2D otherBody;
Vector2 otherBodyAnchor;
/* readonly */
RigidBody2D ownerBody;
Vector2 ownerBodyAnchor;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ConstraintFriction2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
Vector2 anchor;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool collideConnected;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
float maxForce;
float maxTorque;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
RigidBody2D otherBody;
/* readonly */
RigidBody2D ownerBody;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ConstraintGear2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool collideConnected;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
RigidBody2D otherBody;
Constraint2D otherConstraint;
/* readonly */
RigidBody2D ownerBody;
Constraint2D ownerConstraint;
float ratio;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ConstraintMotor2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
float angularOffset;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool collideConnected;
float correctionFactor;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
Vector2 linearOffset;
float maxForce;
float maxTorque;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
RigidBody2D otherBody;
/* readonly */
RigidBody2D ownerBody;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ConstraintMouse2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool collideConnected;
float dampingRatio;
bool enabled;
/* readonly */
bool enabledEffective;
float frequencyHz;
/* readonly */
uint id;
float maxForce;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
RigidBody2D otherBody;
/* readonly */
RigidBody2D ownerBody;
/* readonly */
int refs;
/* readonly */
bool replicated;
Vector2 target;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ConstraintPrismatic2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
Vector2 anchor;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
Vector2 axis;
/* readonly */
String category;
bool collideConnected;
bool enableLimit;
bool enableMotor;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
float lowerTranslation;
float maxMotorForce;
float motorSpeed;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
RigidBody2D otherBody;
/* readonly */
RigidBody2D ownerBody;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
float upperTranslation;
/* readonly */
int weakRefs;
};

class ConstraintPulley2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool collideConnected;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
RigidBody2D otherBody;
Vector2 otherBodyAnchor;
Vector2 otherBodyGroundAnchor;
/* readonly */
RigidBody2D ownerBody;
Vector2 ownerBodyAnchor;
Vector2 ownerBodyGroundAnchor;
float ratio;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ConstraintRevolute2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
Vector2 anchor;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool collideConnected;
bool enableLimit;
bool enableMotor;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
float lowerAngle;
float maxMotorTorque;
float motorSpeed;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
RigidBody2D otherBody;
/* readonly */
RigidBody2D ownerBody;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
float upperAngle;
/* readonly */
int weakRefs;
};

class ConstraintRope2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool collideConnected;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
float maxLength;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
RigidBody2D otherBody;
Vector2 otherBodyAnchor;
/* readonly */
RigidBody2D ownerBody;
Vector2 ownerBodyAnchor;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ConstraintWeld2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
Vector2 anchor;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool collideConnected;
float dampingRatio;
bool enabled;
/* readonly */
bool enabledEffective;
float frequencyHz;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
RigidBody2D otherBody;
/* readonly */
RigidBody2D ownerBody;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ConstraintWheel2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
Vector2 anchor;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
Vector2 axis;
/* readonly */
String category;
bool collideConnected;
float dampingRatio;
bool enableMotor;
bool enabled;
/* readonly */
bool enabledEffective;
float frequencyHz;
/* readonly */
uint id;
float maxMotorTorque;
float motorSpeed;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
RigidBody2D otherBody;
/* readonly */
RigidBody2D ownerBody;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Controls
{
public:
~Controls();
Controls();
Controls(const Controls&in);
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

class CrowdAgent
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
void DrawDebugGeometry(bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetTarget();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
/* readonly */
Vector3 actualVelocity;
/* readonly */
CrowdAgentState agentState;
bool animationEnabled;
/* readonly */
bool arrived;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
/* readonly */
Vector3 desiredVelocity;
bool enabled;
/* readonly */
bool enabledEffective;
float height;
/* readonly */
uint id;
/* readonly */
bool inCrowd;
float maxAccel;
float maxSpeed;
NavigationPushiness navigationPushiness;
NavigationQuality navigationQuality;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
uint obstacleAvoidanceType;
/* readonly */
Vector3 position;
uint queryFilterType;
float radius;
/* readonly */
int refs;
/* readonly */
bool replicated;
/* readonly */
bool requestedTarget;
/* readonly */
CrowdAgentRequestedTarget requestedTargetType;
Vector3 targetPosition;
/* readonly */
CrowdAgentTargetState targetState;
Vector3 targetVelocity;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool updateNodePosition;
/* readonly */
int weakRefs;
};

class CrowdManager
{
public:
// Methods:
void ApplyAttributes();
const CrowdObstacleAvoidanceParams& GetObstacleAvoidanceParams(uint);
void DrawDebugGeometry(DebugRenderer, bool);
void DrawDebugGeometry(bool);
Vector3 FindNearestPoint(const Vector3&, int);
Array<CrowdAgent> GetAgents(Node = null, bool = true);
float GetAreaCost(uint, uint);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
float GetDistanceToWall(const Vector3&, float, int);
uint16 GetExcludeFlags(uint);
uint16 GetIncludeFlags(uint);
bool GetInterceptNetworkUpdate(const String&) const;
Vector3 GetRandomPoint(int);
Vector3 GetRandomPointInCircle(const Vector3&, float, int);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
Vector3 MoveAlongSurface(const Vector3&, const Vector3&, int, uint = 3);
Vector3 Raycast(const Vector3&, const Vector3&, int);
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetCrowdTarget(Node = null);
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
void SetAreaCost(uint, uint, float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetCrowdTarget(const Vector3&, Node = null);
void SetCrowdVelocity(const Vector3&, Node = null);
void SetExcludeFlags(uint, uint16);
void SetIncludeFlags(uint, uint16);
void SetInterceptNetworkUpdate(const String&, bool);
void SetObstacleAvoidanceParams(uint, const CrowdObstacleAvoidanceParams&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
float maxAgentRadius;
int maxAgents;
NavigationMesh navMesh;
/* readonly */
Node node;
/* readonly */
Array<uint> numAreas;
/* readonly */
uint numAttributes;
/* readonly */
uint numObstacleAvoidanceTypes;
/* readonly */
uint numQueryFilterTypes;
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class CrowdObstacleAvoidanceParams
{
public:

// Properties:
uint8 adaptiveDepth;
uint8 adaptiveDivs;
uint8 adaptiveRings;
uint8 gridSize;
float horizTime;
float velBias;
float weightCurVel;
float weightDesVel;
float weightSide;
float weightToi;
};

class Cursor
{
public:
Cursor();
Cursor(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DefineShape(CursorShape, Texture, const IntRect&, const IntVector2&);
void DefineShape(const String&, Texture, const IntRect&, const IntVector2&);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetDisabledOffset(int, int);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetShape(CursorShape);
void SetShape(const String&);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
IntVector2 disabledOffset;
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
IntRect imageBorder;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Material material;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
ObjectAnimation objectAnimation;
float opacity;
UIElement parent;
Vector2 pivot;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool selected;
String shape;
IntVector2 size;
bool sortChildren;
String style;
/* readonly */
Array<String> tags;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
bool useSystemShapes;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class CustomGeometry
{
public:
// Methods:
void ApplyAttributes();
void BeginGeometry(uint, PrimitiveType);
void Clear();
void Commit();
void DefineColor(const Color&);
void DefineGeometry(uint, PrimitiveType, uint, bool, bool, bool, bool);
void DefineNormal(const Vector3&);
void DefineTangent(const Vector4&);
void DefineTexCoord(const Vector2&);
void DefineVertex(const Vector3&);
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
CustomGeometryVertex GetVertex(uint, uint);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool dynamic;
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
/* readonly */
Array<uint> numVertices;
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
StringHash type;
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

class CustomGeometryVertex
{
public:

// Properties:
uint color;
Vector3 normal;
Vector3 position;
Vector4 tangent;
Vector2 texCoord;
};

class Database
{
public:
// Methods:
DbConnection Connect(const String&);
void Disconnect(DbConnection);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String category;
uint poolSize;
/* readonly */
bool pooling;
/* readonly */
int refs;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class DbConnection
{
public:
// Methods:
DbResult Execute(const String&, bool = false);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String category;
/* readonly */
bool connected;
/* readonly */
String connectionString;
/* readonly */
int refs;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class DbResult
{
public:
~DbResult();
DbResult();
DbResult(const DbResult&in);

// Properties:
/* readonly */
Array<String> columns;
/* readonly */
int64 numAffectedRows;
/* readonly */
uint numColumns;
/* readonly */
uint numRows;
/* readonly */
Array<Array<Variant>> row;
};

class DebugHud
{
public:
// Methods:
void ClearAppStats();
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void ResetAppStats(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAppStats(const String&, const String&);
void SetAppStats(const String&, const Variant&);
void Toggle(uint);
void ToggleAll();
void Update();

// Properties:
/* readonly */
String category;
XMLFile defaultStyle;
/* readonly */
Text memoryText;
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
StringHash type;
/* readonly */
String typeName;
bool useRendererStats;
/* readonly */
int weakRefs;
};

class DebugRenderer
{
public:
// Methods:
void AddBoundingBox(const BoundingBox&, const Color&, bool = true, bool = false);
void AddCircle(const Vector3&, const Vector3&, float, const Color&, int = 64, bool = true);
void AddCross(const Vector3&, float, const Color&, bool = true);
void AddFrustum(const Frustum&, const Color&, bool = true);
void AddLine(const Vector3&, const Vector3&, const Color&, bool = true);
void AddNode(Node, float = 1.0, bool = true);
void AddPolygon(const Vector3&, const Vector3&, const Vector3&, const Vector3&, const Color&, bool = true);
void AddPolyhedron(const Polyhedron&, const Color&, bool = true);
void AddQuad(const Vector3&, float, float, const Color&, bool = true);
void AddSkeleton(Skeleton, const Color&, bool = true);
void AddSphere(const Sphere&, const Color&, bool = true);
void AddSphereSector(const Sphere&, const Quaternion&, float, bool, const Color&, bool = true);
void AddTriangle(const Vector3&, const Vector3&, const Vector3&, const Color&, bool = true);
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
bool lineAntiAlias;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class DecalSet
{
public:
// Methods:
bool AddDecal(Drawable, const Vector3&, const Quaternion&, float, float, float, const Vector2&, const Vector2&, float = 0.0, float = 0.1, uint = 0xffffffff);
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllDecals();
void RemoveAttributeAnimation(const String&);
void RemoveDecals(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
bool optimizeBufferSize;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
StringHash type;
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
public:
// Methods:
Array<uint8> Read(uint);
bool ReadBool();
BoundingBox ReadBoundingBox();
int8 ReadByte();
Color ReadColor();
double ReadDouble();
String ReadFileID();
float ReadFloat();
int ReadInt();
int64 ReadInt64();
IntRect ReadIntRect();
IntVector2 ReadIntVector2();
String ReadLine();
Matrix3 ReadMatrix3();
Matrix3x4 ReadMatrix3x4();
Matrix4 ReadMatrix4();
uint ReadNetID();
Quaternion ReadPackedQuaternion();
Vector3 ReadPackedVector3(float);
Quaternion ReadQuaternion();
int16 ReadShort();
String ReadString();
StringHash ReadStringHash();
uint8 ReadUByte();
uint ReadUInt();
uint64 ReadUInt64();
uint16 ReadUShort();
uint ReadVLE();
Variant ReadVariant();
VariantMap ReadVariantMap();
Vector2 ReadVector2();
Vector3 ReadVector3();
Vector4 ReadVector4();
VectorBuffer ReadVectorBuffer(uint);
uint Seek(uint);
uint SeekRelative(int);
uint Tell() const;

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
public:
Dictionary();
// Methods:
void Clear();
void Erase(const String&);
bool Exists(const String&) const;
bool Get(const String&, void*) const;
bool Get(const String&, double&) const;
bool Get(const String&, int64&) const;
void Set(const String&, const void*);
void Set(const String&, const double&);
void Set(const String&, const int64&);

// Properties:
/* readonly */
bool empty;
/* readonly */
Array<String> keys;
/* readonly */
uint length;
};

class DictionaryValue
{
public:
~DictionaryValue();
DictionaryValue();
};

class Drawable
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
StringHash type;
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
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
int layer;
uint lightMask;
float lodBias;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
int orderInLayer;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
uint zoneMask;
};

class DropDownList
{
public:
DropDownList();
DropDownList(const String&in);
// Methods:
void AddChild(UIElement);
void AddItem(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
Array<UIElement> GetItems() const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
void InsertItem(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllItems();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveItem(UIElement);
void RemoveItem(uint);
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAccelerator(int, int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetDisabledOffset(int, int);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetPressedChildOffset(int, int);
void SetPressedOffset(int, int);
void SetRepeat(float, float);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const StringHash&);
UIElement getPopup() const;

// Properties:
/* readonly */
int acceleratorKey;
/* readonly */
int acceleratorQualifiers;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
IntVector2 disabledOffset;
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
IntRect imageBorder;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
/* readonly */
Array<UIElement> items;
IntRect layoutBorder;
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
/* readonly */
ListView listView;
Material material;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
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
ObjectAnimation objectAnimation;
float opacity;
UIElement parent;
Vector2 pivot;
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
/* readonly */
Array<String> tags;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class DynamicNavigationMesh
{
public:
// Methods:
bool AddTile(const VectorBuffer&) const;
bool Allocate(const BoundingBox&, uint);
void ApplyAttributes();
bool Build();
bool Build(const BoundingBox&);
bool Build(const IntVector2&, const IntVector2&);
void DrawDebugGeometry(DebugRenderer, bool);
void DrawDebugGeometry(bool);
Vector3 FindNearestPoint(const Vector3&, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
Array<Vector3> FindPath(const Vector3&, const Vector3&, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
float GetAreaCost(uint) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
float GetDistanceToWall(const Vector3&, float, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
bool GetInterceptNetworkUpdate(const String&) const;
Vector3 GetRandomPoint();
Vector3 GetRandomPointInCircle(const Vector3&, float, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
BoundingBox GetTileBoundingBox(const IntVector2&) const;
VectorBuffer GetTileData(const IntVector2&) const;
IntVector2 GetTileIndex(const Vector3&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTile(const IntVector2&) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
Vector3 MoveAlongSurface(const Vector3&, const Vector3&, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ), int = 3);
Vector3 Raycast(const Vector3&, const Vector3&, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
void Remove();
void RemoveAllTiles();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void RemoveTile(const IntVector2&);
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
void SetAreaCost(uint, float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
float agentHeight;
float agentMaxClimb;
float agentMaxSlope;
float agentRadius;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
BoundingBox boundingBox;
/* readonly */
String category;
float cellHeight;
float cellSize;
float detailSampleDistance;
float detailSampleMaxError;
bool drawNavAreas;
bool drawObstacles;
bool drawOffMeshConnections;
float edgeMaxError;
float edgeMaxLength;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool initialized;
bool maxLayers;
uint maxObstacles;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
IntVector2 numTiles;
ObjectAnimation objectAnimation;
Vector3 padding;
NavmeshPartitionType partitionType;
/* readonly */
int refs;
float regionMergeSize;
float regionMinSize;
/* readonly */
bool replicated;
bool temporary;
int tileSize;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
};

class Engine
{
public:
// Methods:
Console CreateConsole();
DebugHud CreateDebugHud();
void DumpMemory();
void DumpProfiler();
void DumpResources(bool = false);
void Exit();
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void RunFrame();
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
bool autoExit;
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
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class File
{
public:
File();
File(const String&in, FileMode mode = FILE_READ);
// Methods:
void Close();
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Open(const String&, FileMode = FILE_READ);
Array<uint8> Read(uint);
bool ReadBool();
BoundingBox ReadBoundingBox();
int8 ReadByte();
Color ReadColor();
double ReadDouble();
String ReadFileID();
float ReadFloat();
int ReadInt();
int64 ReadInt64();
IntRect ReadIntRect();
IntVector2 ReadIntVector2();
String ReadLine();
Matrix3 ReadMatrix3();
Matrix3x4 ReadMatrix3x4();
Matrix4 ReadMatrix4();
uint ReadNetID();
Quaternion ReadPackedQuaternion();
Vector3 ReadPackedVector3(float);
Quaternion ReadQuaternion();
int16 ReadShort();
String ReadString();
StringHash ReadStringHash();
uint8 ReadUByte();
uint ReadUInt();
uint64 ReadUInt64();
uint16 ReadUShort();
uint ReadVLE();
Variant ReadVariant();
VariantMap ReadVariantMap();
Vector2 ReadVector2();
Vector3 ReadVector3();
Vector4 ReadVector4();
VectorBuffer ReadVectorBuffer(uint);
uint Seek(uint);
uint SeekRelative(int);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
uint Tell() const;
uint Write(Array<uint8>);
bool WriteBool(bool);
bool WriteBoundingBox(const BoundingBox&);
bool WriteByte(int8);
bool WriteColor(const Color&);
bool WriteDouble(double);
bool WriteFileID(const String&);
bool WriteFloat(float);
bool WriteInt(int);
bool WriteInt64(int64);
bool WriteIntRect(const IntRect&);
bool WriteIntVector2(const IntVector2&);
bool WriteLine(const String&);
bool WriteMatrix3(const Matrix3&);
bool WriteMatrix3x4(const Matrix3x4&);
bool WriteMatrix4(const Matrix4&);
bool WriteNetID(uint);
bool WritePackedQuaternion(const Quaternion&);
bool WritePackedVector3(const Vector3&, float);
bool WriteQuaternion(const Quaternion&);
bool WriteShort(int16);
bool WriteString(const String&);
bool WriteStringHash(const StringHash&);
bool WriteUByte(uint8);
bool WriteUInt(uint);
bool WriteUInt64(uint64);
bool WriteUShort(uint16);
bool WriteVLE(uint);
bool WriteVariant(const Variant&);
bool WriteVariantMap(const VariantMap&);
bool WriteVector2(const Vector2&);
bool WriteVector3(const Vector3&);
bool WriteVector4(const Vector4&);
bool WriteVectorBuffer(const VectorBuffer&);

// Properties:
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
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class FileSelector
{
public:
FileSelector();
// Methods:
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetButtonTexts(const String&, const String&);
void SetFilters(Array<String>, uint);
void UpdateElements();

// Properties:
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
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
/* readonly */
Window window;
};

class FileSystem
{
public:
// Methods:
bool Copy(const String&, const String&);
bool CreateDir(const String&);
bool Delete(const String&);
bool DirExists(const String&) const;
bool FileExists(const String&) const;
String GetAppPreferencesDir(const String&, const String&) const;
uint GetLastModifiedTime(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Rename(const String&, const String&);
Array<String> ScanDir(const String&, const String&, uint, bool) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetLastModifiedTime(const String&, uint);
int SystemCommand(const String&, bool = false);
uint SystemCommandAsync(const String&);
bool SystemOpen(const String&, const String&);
int SystemRun(const String&, Array<String>);
uint SystemRunAsync(const String&, Array<String>);

// Properties:
/* readonly */
String category;
String currentDir;
bool executeConsoleCommands;
/* readonly */
String programDir;
/* readonly */
int refs;
/* readonly */
String temporaryDir;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
String userDocumentsDir;
/* readonly */
int weakRefs;
};

class FocusParameters
{
public:
FocusParameters();
FocusParameters(const FocusParameters&in);
FocusParameters(bool, bool, bool, float, float);

// Properties:
bool autoSize;
bool focus;
float minView;
bool nonUniform;
float quantize;
};

class Font
{
public:
Font();
Font(const String&in);
// Methods:
IntVector2 GetTotalGlyphOffset(float) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
bool SaveXML(File, int, bool = false, const String& = "\t");
bool SaveXML(VectorBuffer&, int, bool = false, const String& = "\t");
bool SaveXML(const String&, int, bool = false, const String& = "\t");
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
IntVector2 absoluteGlyphOffset;
/* readonly */
String category;
/* readonly */
FontType fontType;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
Vector2 scaledGlyphOffset;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class Frustum
{
public:
~Frustum();
Frustum();
Frustum(const Frustum&in);
// Methods:
void Define(const BoundingBox&, const Matrix3x4&);
void Define(const Matrix4&);
void Define(const Vector3&, const Vector3&, const Matrix3x4&);
void Define(float, float, float, float, float, const Matrix3x4&);
void DefineOrtho(float, float, float, float, float, const Matrix3x4&);
void DefineSplit(const Matrix4&, float, float);
float Distance(const Vector3&) const;
Intersection IsInside(const BoundingBox&);
Intersection IsInside(const Sphere&);
Intersection IsInside(const Vector3&);
Intersection IsInsideFast(const BoundingBox&) const;
Intersection IsInsideFast(const Sphere&) const;
void Transform(const Matrix3&);
void Transform(const Matrix3x4&);
Frustum Transformed(const Matrix3&) const;
Frustum Transformed(const Matrix3x4&) const;

// Properties:
/* readonly */
Array<Vector3> vertices;
};

class Geometry
{
public:
Geometry();
// Methods:
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetDrawRange(PrimitiveType, uint, uint, bool = true);
bool SetDrawRange(PrimitiveType, uint, uint, uint, uint, bool = true);
void SetIndexBuffer(IndexBuffer);
bool SetVertexBuffer(uint, VertexBuffer);

// Properties:
/* readonly */
String category;
/* readonly */
bool empty;
IndexBuffer indexBuffer;
/* readonly */
uint indexCount;
/* readonly */
uint indexStart;
float lodDistance;
uint numVertexBuffers;
/* readonly */
PrimitiveType primitiveType;
/* readonly */
int refs;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
Array<VertexBuffer> vertexBuffers;
/* readonly */
uint vertexCount;
/* readonly */
uint vertexStart;
/* readonly */
int weakRefs;
};

class Graphics
{
public:
// Methods:
void BeginDumpShaders(const String&);
void Close();
void EndDumpShaders();
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void Maximize();
void Minimize();
void PrecacheShaders(File);
void PrecacheShaders(VectorBuffer&);
void Raise();
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetMode(int, int);
bool SetMode(int, int, bool, bool, bool, bool, bool, bool, int, int, int);
void SetWindowPosition(int, int);
bool TakeScreenShot(Image);
bool ToggleFullscreen();

// Properties:
/* readonly */
String apiName;
/* readonly */
bool borderless;
/* readonly */
String category;
/* readonly */
int currentMonitor;
/* readonly */
bool deferredSupport;
/* readonly */
Array<IntVector2> desktopResolution;
/* readonly */
bool deviceLost;
/* readonly */
Array<Vector3> displayDPI;
bool dither;
bool flushGPU;
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
bool maximized;
/* readonly */
int monitorCount;
/* readonly */
int multiSample;
/* readonly */
Array<int> multiSampleLevels;
/* readonly */
uint numBatches;
/* readonly */
uint numPrimitives;
String orientations;
/* readonly */
bool readableDepthSupport;
/* readonly */
int refs;
/* readonly */
bool resizable;
/* readonly */
Array<Array<IntVector3>> resolutions;
bool sRGB;
/* readonly */
bool sRGBSupport;
/* readonly */
bool sRGBWriteSupport;
String shaderCacheDir;
/* readonly */
IntVector2 size;
/* readonly */
bool tripleBuffer;
/* readonly */
StringHash type;
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
public:
// Methods:
Array<uint8> Read(uint);
bool ReadBool();
BoundingBox ReadBoundingBox();
int8 ReadByte();
Color ReadColor();
double ReadDouble();
String ReadFileID();
float ReadFloat();
int ReadInt();
int64 ReadInt64();
IntRect ReadIntRect();
IntVector2 ReadIntVector2();
String ReadLine();
Matrix3 ReadMatrix3();
Matrix3x4 ReadMatrix3x4();
Matrix4 ReadMatrix4();
uint ReadNetID();
Quaternion ReadPackedQuaternion();
Vector3 ReadPackedVector3(float);
Quaternion ReadQuaternion();
int16 ReadShort();
String ReadString();
StringHash ReadStringHash();
uint8 ReadUByte();
uint ReadUInt();
uint64 ReadUInt64();
uint16 ReadUShort();
uint ReadVLE();
Variant ReadVariant();
VariantMap ReadVariantMap();
Vector2 ReadVector2();
Vector3 ReadVector3();
Vector4 ReadVector4();
VectorBuffer ReadVectorBuffer(uint);
uint Seek(uint);
uint SeekRelative(int);
uint Tell() const;

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

class IKEffector
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
void DrawDebugGeometry(bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
uint chainLength;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
float rotationDecay;
float rotationWeight;
String targetName;
Node targetNode;
Vector3 targetPosition;
Quaternion targetRotation;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
float weight;
};

class IKSolver
{
public:
// Methods:
void ApplyActivePoseToScene();
void ApplyAttributes();
void ApplyOriginalPoseToActivePose();
void ApplyOriginalPoseToScene();
void ApplySceneToActivePose();
void ApplySceneToInitialPose();
void CalculateJointRotations();
void DrawDebugGeometry(DebugRenderer, bool);
void DrawDebugGeometry(bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void RebuildChainTrees();
void RecalculateSegmentLengths();
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
void Solve();

// Properties:
bool AUTO_SOLVE;
bool CONSTRAINTS;
bool JOINT_ROTATIONS;
bool TARGET_ROTATIONS;
bool UPDATE_ACTIVE_POSE;
bool UPDATE_ORIGINAL_POSE;
bool USE_ORIGINAL_POSE;
IKAlgorithm algorithm;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
uint maximumIterations;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
float tolerance;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Image
{
public:
Image();
Image(const String&in);
// Methods:
void Clear(const Color&);
void ClearInt(uint);
bool FlipHorizontal();
bool FlipVertical();
Color GetPixel(int, int) const;
Color GetPixel(int, int, int) const;
Color GetPixelBilinear(float, float) const;
uint GetPixelInt(int, int) const;
uint GetPixelInt(int, int, int) const;
Color GetPixelTrilinear(float, float, float) const;
Image GetSubimage(const IntRect&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
bool LoadColorLUT(File);
bool LoadColorLUT(VectorBuffer&);
bool Resize(int, int);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
bool SaveBMP(const String&) const;
bool SaveDDS(const String&) const;
bool SaveJPG(const String&, int) const;
bool SavePNG(const String&) const;
bool SaveTGA(const String&) const;
bool SaveWEBP(const String&, float = 0.0f) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetPixel(int, int, const Color&);
void SetPixel(int, int, int, const Color&);
void SetPixelInt(int, int, int, uint);
void SetPixelInt(int, int, uint);
bool SetSize(int, int, int, uint);
bool SetSize(int, int, uint);
bool SetSubimage(const Image, const IntRect&) const;

// Properties:
/* readonly */
bool array;
/* readonly */
String category;
/* readonly */
uint components;
/* readonly */
bool compressed;
/* readonly */
CompressedFormat compressedFormat;
/* readonly */
bool cubemap;
/* readonly */
int depth;
/* readonly */
bool hasAlphaChannel;
/* readonly */
int height;
/* readonly */
uint memoryUse;
String name;
/* readonly */
uint numCompressedLevels;
/* readonly */
int refs;
/* readonly */
bool sRGB;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
/* readonly */
int width;
};

class IndexBuffer
{
public:
IndexBuffer();
// Methods:
VectorBuffer GetData();
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetData(VectorBuffer&);
bool SetDataRange(VectorBuffer&, uint, uint, bool = false);
void SetSize(uint, bool, bool = false);

// Properties:
/* readonly */
String category;
/* readonly */
bool dynamic;
/* readonly */
uint indexCount;
/* readonly */
uint indexSize;
/* readonly */
int refs;
bool shadowed;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Input
{
public:
// Methods:
int AddScreenJoystick(XMLFile = null, XMLFile = null);
void CenterMousePosition();
int GetKeyFromName(const String&) const;
int GetKeyFromScancode(int) const;
String GetKeyName(int) const;
int GetScancodeFromKey(int) const;
int GetScancodeFromName(const String&) const;
String GetScancodeName(int) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
uint LoadGestures(File);
uint LoadGestures(VectorBuffer&);
bool RecordGesture();
void RemoveAllGestures();
bool RemoveGesture(uint);
bool RemoveScreenJoystick(int);
void ResetMouseGrabbed();
void ResetMouseMode();
void ResetMouseVisible();
bool SaveGesture(File, uint);
bool SaveGesture(VectorBuffer&, uint);
bool SaveGestures(File);
bool SaveGestures(VectorBuffer&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetMouseGrabbed(bool, bool = false);
void SetMouseMode(MouseMode, bool = false);
void SetMouseVisible(bool, bool = false);

// Properties:
/* readonly */
String category;
/* readonly */
bool focus;
/* readonly */
Vector2 inputScale;
/* readonly */
Array<JoystickState> joysticks;
/* readonly */
Array<JoystickState> joysticksByIndex;
/* readonly */
Array<JoystickState> joysticksByName;
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
bool mouseGrabbed;
/* readonly */
bool mouseLocked;
MouseMode mouseMode;
/* readonly */
IntVector2 mouseMove;
/* readonly */
int mouseMoveWheel;
/* readonly */
int mouseMoveX;
/* readonly */
int mouseMoveY;
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
Array<bool> screenJoystickVisible;
/* readonly */
bool screenKeyboardSupport;
bool screenKeyboardVisible;
bool toggleFullscreen;
bool touchEmulation;
/* readonly */
Array<TouchState> touches;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class IntRect
{
public:
IntRect();
IntRect(const IntRect&in);
IntRect(int, int, int, int);
IntRect(const IntVector2&in, const IntVector2&in);
IntRect(int[]&inout);
// Methods:
int Clip(const IntRect&);
Intersection IsInside(const IntVector2&) const;
int Merge(const IntRect&);

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
public:
IntVector2();
IntVector2(const IntVector2&in);
IntVector2(int, int);
IntVector2(int[]&inout);
// Methods:
float Length() const;
uint ToHash() const;
String ToString() const;

// Properties:
/* readonly */
Array<int> data;
int x;
int y;

// Constants:
static const IntVector2 DOWN;
static const IntVector2 LEFT;
static const IntVector2 ONE;
static const IntVector2 RIGHT;
static const IntVector2 UP;
static const IntVector2 ZERO;
};

class IntVector3
{
public:
IntVector3();
IntVector3(const IntVector3&in);
IntVector3(int, int, int);
IntVector3(int[]&inout);
// Methods:
float Length() const;
uint ToHash() const;
String ToString() const;

// Properties:
/* readonly */
Array<int> data;
int x;
int y;
int z;

// Constants:
static const IntVector3 BACK;
static const IntVector3 DOWN;
static const IntVector3 FORWARD;
static const IntVector3 LEFT;
static const IntVector3 ONE;
static const IntVector3 RIGHT;
static const IntVector3 UP;
static const IntVector3 ZERO;
};

class JSONFile
{
public:
JSONFile();
JSONFile(const String&in);
// Methods:
bool FromString(const String&);
JSONValue& GetRoot();
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
bool Save(File) const;
bool Save(File, const String&) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
String ToString(const String& = String ( "\t" )) const;

// Properties:
/* readonly */
String category;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
/* readonly */
JSONValue root;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class JSONValue
{
public:
~JSONValue();
JSONValue();
JSONValue(bool);
JSONValue(int);
JSONValue(uint);
JSONValue(float);
JSONValue(double);
JSONValue(const String&in);
JSONValue(const JSONValue&in);
// Methods:
void Clear();
bool Contains(const String&) const;
void Erase(const String&);
void Erase(uint, uint = 1);
bool GetBool(bool = false) const;
double GetDouble(double = 0) const;
float GetFloat(float = 0) const;
int GetInt(int = 0) const;
uint GetUInt(uint = 0) const;
Variant GetVariant(Variant = Variant ( )) const;
VariantMap GetVariantMap(VariantMap = VariantMap ( )) const;
void Insert(uint, const JSONValue&);
const JSONValue& Get(const String&) const;
void Pop();
void Push(const JSONValue&);
void Resize(uint);
void Set(const String&, const JSONValue&);
void SetVariant(const Variant&);
void SetVariantMap(const VariantMap&);
const String& GetString(const String& = String ( )) const;

// Properties:
/* readonly */
bool isArray;
/* readonly */
bool isBool;
/* readonly */
bool isNull;
/* readonly */
bool isNumber;
/* readonly */
bool isObject;
/* readonly */
bool isString;
/* readonly */
Array<String> keys;
/* readonly */
JSONNumberType numberType;
/* readonly */
String numberTypeName;
/* readonly */
uint size;
/* readonly */
JSONValueType valueType;
/* readonly */
String valueTypeName;
/* readonly */
Array<JSONValue> values;
};

class JoystickState
{
public:

// Properties:
/* readonly */
Array<float> axisPosition;
/* readonly */
Array<bool> buttonDown;
/* readonly */
Array<bool> buttonPress;
/* readonly */
bool controller;
/* readonly */
Array<int> hatPosition;
int joystickID;
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
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
float aspectRatio;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
BoundingBox boundingBox;
float brightness;
bool castShadows;
/* readonly */
String category;
Color color;
/* readonly */
Color colorFromTemperature;
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
float length;
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
/* readonly */
int numShadowSplits;
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
bool perVertex;
float radius;
Texture rampTexture;
float range;
/* readonly */
int refs;
/* readonly */
bool replicated;
BiasParameters shadowBias;
CascadeParameters shadowCascade;
float shadowDistance;
float shadowFadeDistance;
FocusParameters shadowFocus;
float shadowIntensity;
uint shadowMask;
float shadowMaxExtrusion;
float shadowNearFarRatio;
float shadowResolution;
Texture shapeTexture;
float specularIntensity;
float temperature;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool usePhysicalValues;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
uint zoneMask;
};

class LineEdit
{
public:
LineEdit();
LineEdit(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetDisabledOffset(int, int);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
IntVector2 disabledOffset;
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
uint echoCharacter;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
IntRect imageBorder;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Material material;
Vector2 maxAnchor;
int maxHeight;
uint maxLength;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
ObjectAnimation objectAnimation;
float opacity;
UIElement parent;
Vector2 pivot;
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
/* readonly */
Array<String> tags;
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
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class ListView
{
public:
ListView();
ListView(const String&in);
// Methods:
void AddChild(UIElement);
void AddItem(UIElement);
void AddSelection(uint);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
void ChangeSelection(int, bool);
void ClearSelection();
void CopySelectedItemsToClipboard();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableInternalLayoutUpdate();
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableInternalLayoutUpdate();
void EnableLayoutUpdate();
void Expand(uint, bool, bool = false);
uint FindChild(UIElement) const;
uint FindItem(UIElement);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
Array<UIElement> GetItems() const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
void InsertItem(uint, UIElement, UIElement = null);
bool IsChildOf(UIElement) const;
bool IsExpanded(uint) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool IsSelected(uint) const;
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllItems();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveItem(UIElement, uint = 0);
void RemoveItem(uint);
void RemoveObjectAnimation();
void RemoveSelection(uint);
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
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
void UpdateInternalLayout();
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool autoDisableChildren;
float autoDisableThreshold;
int baseIndent;
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
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
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
ObjectAnimation objectAnimation;
float opacity;
float pageStep;
UIElement parent;
Vector2 pivot;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool scrollBarsAutoVisible;
float scrollDeceleration;
/* readonly */
BorderImage scrollPanel;
float scrollSnapEpsilon;
float scrollStep;
bool selectOnClickEnd;
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
/* readonly */
Array<String> tags;
bool temporary;
TraversalMode traversalMode;
/* readonly */
StringHash type;
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
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class Localization
{
public:
// Methods:
String Get(const String&);
String GetLanguage(int);
int GetLanguageIndex(const String&);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void LoadJSONFile(const String&, const String = String ( "" ) const);
void LoadMultipleLanguageJSON(const JSONValue&);
void LoadSingleLanguageJSON(const JSONValue&, const String& = String ( "" ) const);
void Reset();
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetLanguage(const String&);
void SetLanguage(int);

// Properties:
/* readonly */
String category;
/* readonly */
String language;
/* readonly */
int languageIndex;
/* readonly */
int numLanguages;
/* readonly */
int refs;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Log
{
public:
// Methods:
void Close();
void Debug(const String&);
void Error(const String&);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void Info(const String&);
void Open(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void Trace(const String&);
void Warning(const String&);
void Write(const String&, bool = false);

// Properties:
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
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Material
{
public:
Material();
Material(const String&in);
// Methods:
Material Clone(const String& = String ( )) const;
Pass GetPass(uint, const String&);
ValueAnimation GetShaderParameterAnimation(const String&) const;
float GetShaderParameterAnimationSpeed(const String&) const;
WrapMode GetShaderParameterAnimationWrapMode(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const JSONValue&);
bool Load(const String&);
bool Load(const XMLElement&);
void RemoveShaderParameter(const String&);
bool Save(File) const;
bool Save(JSONValue&) const;
bool Save(VectorBuffer&) const;
bool Save(XMLElement&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetShaderParameterAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetShaderParameterAnimationSpeed(const String&, float);
void SetShaderParameterAnimationWrapMode(const String&, WrapMode);
void SetTechnique(uint, Technique, uint = 0, float = 0.0);
void SetUVTransform(const Vector2&, float, const Vector2&);
void SetUVTransform(const Vector2&, float, float);
void SortTechniques();

// Properties:
bool alphaToCoverage;
/* readonly */
String category;
CullMode cullMode;
BiasParameters depthBias;
FillMode fillMode;
bool lineAntiAlias;
/* readonly */
uint memoryUse;
String name;
uint numTechniques;
bool occlusion;
String pixelShaderDefines;
/* readonly */
int refs;
uint8 renderOrder;
Scene scene;
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
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
String vertexShaderDefines;
/* readonly */
int weakRefs;
};

class Matrix2
{
public:
Matrix2();
Matrix2(const Matrix2&in);
Matrix2(float, float, float, float);
// Methods:
bool Equals(const Matrix2&) const;
Matrix2 Inverse() const;
Vector2 Scale() const;
Matrix2 Scaled(const Vector2&) const;
void SetScale(const Vector2&);
void SetScale(float);
String ToString() const;
Matrix2 Transpose() const;

// Properties:
float m00;
float m01;
float m10;
float m11;
};

class Matrix3
{
public:
Matrix3();
Matrix3(const Matrix3&in);
Matrix3(float, float, float, float, float, float, float, float, float);
// Methods:
bool Equals(const Matrix3&) const;
Matrix3 Inverse() const;
Vector3 Scale() const;
Matrix3 Scaled(const Vector3&) const;
void SetScale(const Vector3&);
void SetScale(float);
String ToString() const;
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
public:
Matrix3x4();
Matrix3x4(const Matrix3x4&in);
Matrix3x4(const Matrix3&in);
Matrix3x4(const Matrix4&in);
Matrix3x4(float, float, float, float, float, float, float, float, float, float, float, float);
Matrix3x4(const Vector3&in, const Quaternion&in, const Vector3&in);
Matrix3x4(const Vector3&in, const Quaternion&in, float);
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
String ToString() const;
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
public:
Matrix4();
Matrix4(const Matrix4&in);
Matrix4(const Matrix3&in);
Matrix4(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
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
String ToString() const;
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
public:
Menu();
Menu(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAccelerator(int, int);
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetDisabledOffset(int, int);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
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
const Variant& GetVar(const StringHash&);

// Properties:
/* readonly */
int acceleratorKey;
/* readonly */
int acceleratorQualifiers;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
IntVector2 disabledOffset;
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
IntRect imageBorder;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Material material;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
ObjectAnimation objectAnimation;
float opacity;
UIElement parent;
Vector2 pivot;
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
/* readonly */
Array<String> tags;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class MessageBox
{
public:
MessageBox(const String&in messageString = String ( ), const String&in titleString = String ( ), XMLFile& layoutFile = null, XMLFile& styleFile = null);
// Methods:
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String category;
String message;
/* readonly */
int refs;
String title;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
/* readonly */
UIElement window;
};

class Model
{
public:
Model();
Model(const String&in);
// Methods:
void AddMetadata(const String&, const Variant&);
Model Clone(const String& = String ( )) const;
Geometry GetGeometry(uint, uint) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
void RemoveAllMetadata();
void RemoveMetadata(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetGeometry(uint, uint, Geometry);
bool SetIndexBuffers(Array<IndexBuffer>);
bool SetVertexBuffers(Array<Array<Array<VertexBuffer>, uint>, uint>);

// Properties:
BoundingBox boundingBox;
/* readonly */
String category;
Array<Vector3> geometryCenters;
/* readonly */
bool hasMetadata;
/* readonly */
uint memoryUse;
Array<Variant> metadata;
String name;
uint numGeometries;
Array<uint> numGeometryLodLevels;
/* readonly */
uint numMorphs;
/* readonly */
int refs;
/* readonly */
Skeleton skeleton;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class NamedPipe
{
public:
NamedPipe();
NamedPipe(const String&in, bool);
// Methods:
void Close();
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Open(const String&, bool);
Array<uint8> Read(uint);
bool ReadBool();
BoundingBox ReadBoundingBox();
int8 ReadByte();
Color ReadColor();
double ReadDouble();
String ReadFileID();
float ReadFloat();
int ReadInt();
int64 ReadInt64();
IntRect ReadIntRect();
IntVector2 ReadIntVector2();
String ReadLine();
Matrix3 ReadMatrix3();
Matrix3x4 ReadMatrix3x4();
Matrix4 ReadMatrix4();
uint ReadNetID();
Quaternion ReadPackedQuaternion();
Vector3 ReadPackedVector3(float);
Quaternion ReadQuaternion();
int16 ReadShort();
String ReadString();
StringHash ReadStringHash();
uint8 ReadUByte();
uint ReadUInt();
uint64 ReadUInt64();
uint16 ReadUShort();
uint ReadVLE();
Variant ReadVariant();
VariantMap ReadVariantMap();
Vector2 ReadVector2();
Vector3 ReadVector3();
Vector4 ReadVector4();
VectorBuffer ReadVectorBuffer(uint);
uint Seek(uint);
uint SeekRelative(int);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
uint Tell() const;
uint Write(Array<uint8>);
bool WriteBool(bool);
bool WriteBoundingBox(const BoundingBox&);
bool WriteByte(int8);
bool WriteColor(const Color&);
bool WriteDouble(double);
bool WriteFileID(const String&);
bool WriteFloat(float);
bool WriteInt(int);
bool WriteInt64(int64);
bool WriteIntRect(const IntRect&);
bool WriteIntVector2(const IntVector2&);
bool WriteLine(const String&);
bool WriteMatrix3(const Matrix3&);
bool WriteMatrix3x4(const Matrix3x4&);
bool WriteMatrix4(const Matrix4&);
bool WriteNetID(uint);
bool WritePackedQuaternion(const Quaternion&);
bool WritePackedVector3(const Vector3&, float);
bool WriteQuaternion(const Quaternion&);
bool WriteShort(int16);
bool WriteString(const String&);
bool WriteStringHash(const StringHash&);
bool WriteUByte(uint8);
bool WriteUInt(uint);
bool WriteUInt64(uint64);
bool WriteUShort(uint16);
bool WriteVLE(uint);
bool WriteVariant(const Variant&);
bool WriteVariantMap(const VariantMap&);
bool WriteVector2(const Vector2&);
bool WriteVector3(const Vector3&);
bool WriteVector4(const Vector4&);
bool WriteVectorBuffer(const VectorBuffer&);

// Properties:
/* readonly */
String category;
/* readonly */
uint checksum;
/* readonly */
bool eof;
/* readonly */
String name;
/* readonly */
bool open;
/* readonly */
uint position;
/* readonly */
int refs;
/* readonly */
bool server;
/* readonly */
uint size;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class NavArea
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
uint areaID;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
BoundingBox boundingBox;
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
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
};

class Navigable
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
bool recursive;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class NavigationMesh
{
public:
// Methods:
bool AddTile(const VectorBuffer&) const;
bool Allocate(const BoundingBox&, uint);
void ApplyAttributes();
bool Build();
bool Build(const BoundingBox&);
bool Build(const IntVector2&, const IntVector2&);
void DrawDebugGeometry(DebugRenderer, bool);
void DrawDebugGeometry(bool);
Vector3 FindNearestPoint(const Vector3&, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
Array<Vector3> FindPath(const Vector3&, const Vector3&, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
float GetAreaCost(uint) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
float GetDistanceToWall(const Vector3&, float, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
bool GetInterceptNetworkUpdate(const String&) const;
Vector3 GetRandomPoint();
Vector3 GetRandomPointInCircle(const Vector3&, float, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
BoundingBox GetTileBoundingBox(const IntVector2&) const;
VectorBuffer GetTileData(const IntVector2&) const;
IntVector2 GetTileIndex(const Vector3&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTile(const IntVector2&) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
Vector3 MoveAlongSurface(const Vector3&, const Vector3&, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ), int = 3);
Vector3 Raycast(const Vector3&, const Vector3&, const Vector3& = Vector3 ( 1.0 , 1.0 , 1.0 ));
void Remove();
void RemoveAllTiles();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void RemoveTile(const IntVector2&);
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
void SetAreaCost(uint, float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
float agentHeight;
float agentMaxClimb;
float agentMaxSlope;
float agentRadius;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
BoundingBox boundingBox;
/* readonly */
String category;
float cellHeight;
float cellSize;
float detailSampleDistance;
float detailSampleMaxError;
bool drawNavAreas;
bool drawOffMeshConnections;
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
ObjectAnimation objectAnimation;
Vector3 padding;
NavmeshPartitionType partitionType;
/* readonly */
int refs;
float regionMergeSize;
float regionMinSize;
/* readonly */
bool replicated;
bool temporary;
int tileSize;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
};

class Network
{
public:
// Methods:
bool AttemptNATPunchtrough(const String&, Scene, const VariantMap& = VariantMap ( ));
void BroadcastMessage(int, bool, bool, const VectorBuffer&, uint = 0);
void BroadcastRemoteEvent(Node, const String&, bool, const VariantMap& = VariantMap ( ));
void BroadcastRemoteEvent(Scene, const String&, bool, const VariantMap& = VariantMap ( ));
void BroadcastRemoteEvent(const String&, bool, const VariantMap& = VariantMap ( ));
bool CheckRemoteEvent(const String&) const;
bool Connect(const String&, uint16, Scene, const VariantMap& = VariantMap ( ));
void Disconnect(int = 0);
bool DiscoverHosts(uint16);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
HttpRequest MakeHttpRequest(const String&, const String& = String ( ), Array<String> = null, const String& = String ( ));
void RegisterRemoteEvent(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SendPackageToClients(Scene, PackageFile);
bool SetDiscoveryBeacon(const VariantMap& = VariantMap ( ));
void SetNATServerInfo(const String&, uint16);
bool SetPassword(const String&);
void StartNATClient() const;
bool StartServer(uint16, uint = 128);
void StopServer();
void UnregisterAllRemoteEvents();
void UnregisterRemoteEvent(const String&) const;

// Properties:
/* readonly */
String category;
/* readonly */
Array<Connection> clientConnections;
/* readonly */
String guid;
String packageCacheDir;
/* readonly */
int refs;
/* readonly */
Connection serverConnection;
/* readonly */
bool serverRunning;
int simulatedLatency;
float simulatedPacketLoss;
/* readonly */
String startNATClient;
/* readonly */
StringHash type;
/* readonly */
String typeName;
int updateFps;
/* readonly */
int weakRefs;
};

class NetworkPriority
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool alwaysUpdateOwner;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
float basePriority;
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
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Node
{
public:
Node();
Node(const String&in);
// Methods:
void AddChild(Node, uint = M_MAX_UNSIGNED);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
Node Clone(CreateMode = REPLICATED);
Component CloneComponent(Component, CreateMode, uint = 0);
Component CloneComponent(Component, uint = 0);
Node CreateChild(const String& = String ( ), CreateMode = REPLICATED, uint = 0, bool = false);
Component CreateComponent(const String&, CreateMode = REPLICATED, uint = 0);
ScriptObject CreateScriptObject(ScriptFile, const String&, CreateMode = REPLICATED);
ScriptObject CreateScriptObject(const String&, const String&, CreateMode = REPLICATED);
Node CreateTemporaryChild(const String& = String ( ), CreateMode = REPLICATED, uint = 0);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
Node GetChild(const String&, bool = false) const;
Array<Node> GetChildren(bool = false) const;
Array<Node> GetChildrenWithComponent(const String&, bool = false) const;
Array<Node> GetChildrenWithScript(bool = false) const;
Array<Node> GetChildrenWithScript(const String&, bool = false) const;
Array<Node> GetChildrenWithTag(const String&, bool = false) const;
Component GetComponent(const String&, bool = false) const;
Array<Component> GetComponents() const;
Array<Component> GetComponents(const String&, bool = false) const;
bool GetInterceptNetworkUpdate(const String&) const;
Component GetOrCreateComponent(const String&, CreateMode = REPLICATED, uint = 0);
Component GetParentComponent(const String&, bool = false) const;
ScriptObject GetScriptObject() const;
ScriptObject GetScriptObject(const String&) const;
bool HasComponent(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&);
bool IsChildOf(Node) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
Vector3 LocalToWorld(const Vector3&) const;
Vector3 LocalToWorld(const Vector4&) const;
Vector2 LocalToWorld2D(const Vector2&) const;
bool LookAt(const Vector3&, const Vector3& = Vector3 ( 0 , 1 , 0 ), TransformSpace = TS_WORLD);
void MarkDirty();
void MarkNetworkUpdate() const;
void Pitch(float, TransformSpace = TS_LOCAL);
void Remove();
void RemoveAllChildren();
void RemoveAllComponents();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(Node);
void RemoveChildren(bool, bool, bool);
void RemoveComponent(Component);
void RemoveComponent(const String&);
void RemoveComponents(bool, bool);
void RemoveComponents(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ReorderComponent(Component, uint);
void ResetDeepEnabled();
void ResetToDefault();
void Roll(float, TransformSpace = TS_LOCAL);
void Rotate(const Quaternion&, TransformSpace = TS_LOCAL);
void Rotate2D(float, TransformSpace = TS_LOCAL);
void RotateAround(const Vector3&, const Quaternion&, TransformSpace = TS_LOCAL);
void RotateAround2D(const Vector2&, float, TransformSpace = TS_LOCAL);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(File);
bool SaveJSON(JSONValue&) const;
bool SaveJSON(VectorBuffer&);
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
void Scale(const Vector3&);
void Scale(float);
void Scale2D(const Vector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetEnabledRecursive(bool);
void SetInterceptNetworkUpdate(const String&, bool);
void SetPosition2D(float, float);
void SetScale(float);
void SetScale2D(float, float);
void SetTransform(const Matrix3x4&);
void SetTransform(const Vector3&, const Quaternion&);
void SetTransform(const Vector3&, const Quaternion&, const Vector3&);
void SetTransform(const Vector3&, const Quaternion&, float);
void SetTransform2D(const Vector2&, float);
void SetTransform2D(const Vector2&, float, const Vector2&);
void SetTransform2D(const Vector2&, float, float);
void SetWorldTransform(const Vector3&, const Quaternion&);
void SetWorldTransform(const Vector3&, const Quaternion&, const Vector3&);
void SetWorldTransform(const Vector3&, const Quaternion&, float);
void SetWorldTransform2D(const Vector2&, float);
void SetWorldTransform2D(const Vector2&, float, const Vector2&);
void SetWorldTransform2D(const Vector2&, float, float);
void Translate(const Vector3&, TransformSpace = TS_LOCAL);
void Translate2D(const Vector2&, TransformSpace = TS_LOCAL);
Vector3 WorldToLocal(const Vector3&) const;
Vector3 WorldToLocal(const Vector4&) const;
Vector2 WorldToLocal2D(const Vector2&) const;
void Yaw(float, TransformSpace = TS_LOCAL);

// Properties:
/* readonly */
Array<Node> allChildrenByName;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
/* readonly */
Array<Node> children;
/* readonly */
Array<Node> childrenByName;
/* readonly */
Array<Component> components;
Vector3 direction;
bool enabled;
/* readonly */
bool enabledSelf;
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
ObjectAnimation objectAnimation;
Connection owner;
Node parent;
Vector3 position;
Vector2 position2D;
/* readonly */
int refs;
/* readonly */
bool replicated;
/* readonly */
Vector3 right;
Quaternion rotation;
float rotation2D;
Vector3 scale;
Vector2 scale2D;
/* readonly */
Scene scene;
/* readonly */
ScriptObject scriptObject;
/* readonly */
Vector3 signedWorldScale;
/* readonly */
Array<String> tags;
bool temporary;
/* readonly */
Matrix3x4 transform;
/* readonly */
StringHash type;
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
Vector2 worldPosition2D;
/* readonly */
Vector3 worldRight;
Quaternion worldRotation;
float worldRotation2D;
Vector3 worldScale;
Vector2 worldScale2D;
/* readonly */
Matrix3x4 worldTransform;
/* readonly */
Vector3 worldUp;
};

class Object
{
public:
// Methods:
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String category;
/* readonly */
int refs;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ObjectAnimation
{
public:
ObjectAnimation();
ObjectAnimation(const String&in);
// Methods:
void AddAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
void RemoveAttributeAnimation(ValueAnimation);
void RemoveAttributeAnimation(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
Array<Variant> attributeAnimations;
/* readonly */
String category;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
/* readonly */
Array<Variant> speeds;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
/* readonly */
Array<Variant> wrapModes;
};

class Obstacle
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
void DrawDebugGeometry(bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
float height;
/* readonly */
uint id;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
/* readonly */
uint obstacleId;
float radius;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Octree
{
public:
// Methods:
void AddManualDrawable(Drawable);
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
void DrawDebugGeometry(bool) const;
Array<Drawable> GetAllDrawables(uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
Array<Drawable> GetDrawables(const BoundingBox&, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK);
Array<Drawable> GetDrawables(const Frustum&, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK);
Array<Drawable> GetDrawables(const Sphere&, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK);
Array<Drawable> GetDrawables(const Vector3&, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK);
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
Array<RayQueryResult> Raycast(const Ray&, RayQueryLevel = RAY_TRIANGLE, float = M_INFINITY, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK) const;
RayQueryResult RaycastSingle(const Ray&, RayQueryLevel = RAY_TRIANGLE, float = M_INFINITY, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK) const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveManualDrawable(Drawable);
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
void SetSize(const BoundingBox&, uint);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
};

class OffMeshConnection
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
uint areaID;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool bidirectional;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
Node endPoint;
/* readonly */
uint id;
uint mask;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
float radius;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class PackageFile
{
public:
PackageFile();
PackageFile(const String&in, uint startOffset = 0);
// Methods:
bool Exists(const String&) const;
Array<String> GetEntryNames() const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Open(const String&, uint = 0) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool compressed() const;

// Properties:
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
uint totalDataSize;
/* readonly */
uint totalSize;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ParticleEffect
{
public:
ParticleEffect();
ParticleEffect(const String&in);
// Methods:
void AddColorFrame(ColorFrame);
void AddColorTime(const Color&, float);
void AddTextureFrame(TextureFrame);
void AddTextureTime(const Rect&, float);
ParticleEffect Clone(const String& = String ( )) const;
ColorFrame GetColorFrame(uint) const;
TextureFrame GetTextureFrame(uint) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
bool Load(const XMLElement&);
void RemoveColorFrame(uint);
void RemoveTextureFrame(uint);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(XMLElement&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetColorFrame(uint, ColorFrame);
void SetTextureFrame(uint, TextureFrame);
void SortColorFrames();
void SortTextureFrames();

// Properties:
float activeTime;
float animationLodBias;
/* readonly */
String category;
Vector3 constantForce;
float dampingForce;
Vector3 emitterSize;
EmitterType emitterType;
FaceCameraMode faceCameraMode;
bool fixedScreenSize;
float inactiveTime;
Material material;
Vector3 maxDirection;
float maxEmissionRate;
Vector2 maxParticleSize;
float maxRotation;
float maxRotationSpeed;
float maxTimeToLive;
float maxVelocity;
/* readonly */
uint memoryUse;
Vector3 minDirection;
float minEmissionRate;
Vector2 minParticleSize;
float minRotation;
float minRotationSpeed;
float minTimeToLive;
float minVelocity;
String name;
uint numColorFrames;
uint numParticles;
uint numTextureFrames;
/* readonly */
int refs;
bool relative;
bool scaled;
float sizeAdd;
float sizeMul;
bool sorted;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool updateInvisible;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class ParticleEffect2D
{
public:
ParticleEffect2D();
ParticleEffect2D(const String&in);
// Methods:
ParticleEffect2D Clone(const String& = String ( )) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String category;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class ParticleEmitter
{
public:
// Methods:
void ApplyAttributes();
void ApplyEffect();
void Commit();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllParticles();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void Reset();
void ResetEmissionTimer();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
float animationLodBias;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
AutoRemoveMode autoRemoveMode;
/* readonly */
Array<Billboard> billboards;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
ParticleEffect effect;
bool emitting;
bool enabled;
/* readonly */
bool enabledEffective;
FaceCameraMode faceCameraMode;
bool fixedScreenSize;
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
uint numParticles;
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
/* readonly */
int refs;
bool relative;
/* readonly */
bool replicated;
bool scaled;
bool serializeParticles;
float shadowDistance;
uint shadowMask;
bool sorted;
bool temporary;
/* readonly */
StringHash type;
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

class ParticleEmitter2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
BlendMode blendMode;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
ParticleEffect2D effect;
bool emitting;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
bool inView;
int layer;
uint lightMask;
float lodBias;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
int orderInLayer;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
Sprite2D sprite;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
uint zoneMask;
};

class Pass
{
public:

// Properties:
bool alphaToCoverage;
BlendMode blendMode;
CullMode cullMode;
CompareMode depthTestMode;
bool depthWrite;
bool desktop;
PassLightingMode lightingMode;
String pixelShader;
String pixelShaderDefineExcludes;
String pixelShaderDefines;
/* readonly */
int refs;
String vertexShader;
String vertexShaderDefineExcludes;
String vertexShaderDefines;
/* readonly */
int weakRefs;
};

class PhysicsRaycastResult
{
public:
~PhysicsRaycastResult();
PhysicsRaycastResult();

// Properties:
/* readonly */
RigidBody body;
float distance;
float hitFraction;
Vector3 normal;
Vector3 position;
};

class PhysicsRaycastResult2D
{
public:
~PhysicsRaycastResult2D();
PhysicsRaycastResult2D();

// Properties:
/* readonly */
RigidBody2D body;
float distance;
Vector2 normal;
Vector2 position;
};

class PhysicsWorld
{
public:
// Methods:
void ApplyAttributes();
PhysicsRaycastResult ConvexCast(CollisionShape, const Vector3&, const Quaternion&, const Vector3&, const Quaternion&, uint = 0xffff);
void DrawDebugGeometry(DebugRenderer, bool);
void DrawDebugGeometry(bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
Array<RigidBody> GetCollidingBodies(RigidBody);
bool GetInterceptNetworkUpdate(const String&) const;
Array<RigidBody> GetRigidBodies(RigidBody);
Array<RigidBody> GetRigidBodies(const BoundingBox&, uint = 0xffff);
Array<RigidBody> GetRigidBodies(const Sphere&, uint = 0xffff);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
Array<PhysicsRaycastResult> Raycast(const Ray&, float, uint = 0xffff);
PhysicsRaycastResult RaycastSingle(const Ray&, float, uint = 0xffff);
PhysicsRaycastResult RaycastSingleSegmented(const Ray&, float, float, uint = 0xffff, float = 0.1f);
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveCachedGeometry(Model);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
PhysicsRaycastResult SphereCast(const Ray&, float, float, uint = 0xffff);
void Update(float);
void UpdateCollisions();

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
int maxSubSteps;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
int numIterations;
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool splitImpulse;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool updateEnabled;
/* readonly */
int weakRefs;
};

class PhysicsWorld2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry() const;
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
Array<RigidBody2D> GetRigidBodies(const Rect&, uint = 0xffff);
RigidBody2D GetRigidBody(const Vector2&, uint = 0xffff);
RigidBody2D GetRigidBody(int, int, uint = 0xffff);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
Array<PhysicsRaycastResult2D> Raycast(const Vector2&, const Vector2&, uint = 0xffff);
PhysicsRaycastResult2D RaycastSingle(const Vector2&, const Vector2&, uint = 0xffff);
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool allowSleeping;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool autoClearForces;
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
ObjectAnimation objectAnimation;
uint positionIterations;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool subStepping;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool updateEnabled;
uint velocityIterations;
bool warmStarting;
/* readonly */
int weakRefs;
};

class Plane
{
public:
Plane();
Plane(const Plane&in);
Plane(const Vector3&in, const Vector3&in, const Vector3&in);
Plane(const Vector3&in, const Vector3&in);
Plane(const Vector4&in);
// Methods:
void Define(const Vector3&, const Vector3&);
void Define(const Vector3&, const Vector3&, const Vector3&);
void Define(const Vector4&);
float Distance(const Vector3&) const;
Vector3 Project(const Vector3&) const;
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
public:
~Polyhedron();
Polyhedron();
Polyhedron(const Polyhedron&in);
Polyhedron(const BoundingBox&in);
Polyhedron(const Frustum&in);
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

class ProgressBar
{
public:
// Methods:
void ChangeValue(float);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetLoadingPercentStyle(const String&);

// Properties:
/* readonly */
String category;
/* readonly */
BorderImage knob;
Orientation orientation;
float range;
/* readonly */
int refs;
bool showPercentText;
/* readonly */
StringHash type;
/* readonly */
String typeName;
float value;
/* readonly */
int weakRefs;
};

class PropertySet2D
{
public:
// Methods:
bool HasProperty(const String&) const;
const String& GetProperty(const String&) const;

// Properties:
/* readonly */
int refs;
/* readonly */
int weakRefs;
};

class Quaternion
{
public:
Quaternion();
Quaternion(const Quaternion&in);
Quaternion(float, float, float, float);
Quaternion(float, const Vector3&in);
Quaternion(float);
Quaternion(float, float, float);
Quaternion(const Vector3&in);
Quaternion(const Vector3&in, const Vector3&in);
Quaternion(const Vector3&in, const Vector3&in, const Vector3&in);
Quaternion(const Matrix3&in);
// Methods:
Quaternion Conjugate() const;
float DotProduct(const Quaternion&) const;
bool Equals(const Quaternion&) const;
void FromAngleAxis(float, const Vector3&);
void FromAxes(const Vector3&, const Vector3&, const Vector3&);
void FromEulerAngles(float, float, float);
bool FromLookRotation(const Vector3&, const Vector3& = Vector3 ( 0.0 , 1.0 , 0.0 ));
void FromRotationMatrix(const Matrix3&);
void FromRotationTo(const Vector3&, const Vector3&);
Quaternion Inverse() const;
bool IsNaN() const;
float LengthSquared() const;
Quaternion Nlerp(const Quaternion&, float, bool) const;
void Normalize();
Quaternion Normalized() const;
Quaternion Slerp(const Quaternion&, float) const;
String ToString() const;

// Properties:
/* readonly */
float angle;
/* readonly */
Vector3 axis;
/* readonly */
Vector3 eulerAngles;
/* readonly */
float pitch;
/* readonly */
float roll;
/* readonly */
Matrix3 rotationMatrix;
float w;
float x;
float y;
/* readonly */
float yaw;
float z;
};

class Ray
{
public:
Ray();
Ray(const Ray&in);
Ray(const Vector3&in, const Vector3&in);
// Methods:
Vector3 ClosestPoint(const Ray&) const;
void Define(const Vector3&, const Vector3&);
float Distance(const Vector3&) const;
float HitDistance(const BoundingBox&) const;
float HitDistance(const Frustum&, bool = true) const;
float HitDistance(const Plane&) const;
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
public:
RayQueryResult();

// Properties:
float distance;
/* readonly */
Drawable drawable;
/* readonly */
Node node;
Vector3 normal;
Vector3 position;
uint subObject;
Vector2 textureUV;
};

class RaycastVehicle
{
public:
// Methods:
void AddWheel(Node, Vector3, Vector3, float, float, bool);
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
float GetBrake(int);
Vector3 GetContactNormal(int);
Vector3 GetContactPosition(int);
float GetEngineForce(int);
bool GetInterceptNetworkUpdate(const String&) const;
float GetMaxSuspensionTravel(int);
float GetSteeringValue(int);
Vector3 GetWheelAxle(int);
Vector3 GetWheelConnectionPoint(int);
float GetWheelDampingCompression(int);
float GetWheelDampingRelaxation(int);
Vector3 GetWheelDirection(int);
float GetWheelFrictionSlip(int);
Node GetWheelNode(int);
Vector3 GetWheelPosition(int);
float GetWheelRadius(int);
float GetWheelRestLength(int);
float GetWheelRollInfluence(int);
Vector3 GetWheelRotation(int);
float GetWheelSideSlipSpeed(int);
float GetWheelSkidInfo(int);
float GetWheelSkidInfoCumulative(int);
float GetWheelSuspensionStiffness(int);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void Init();
bool IsFrontWheel(int);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetSuspension();
void ResetToDefault();
void ResetWheels();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetBrake(int, float);
void SetEngineForce(int, float);
void SetInterceptNetworkUpdate(const String&, bool);
void SetMaxSuspensionTravel(int, float);
void SetSteeringValue(int, float);
void SetWheelAxle(int, Vector3);
void SetWheelDampingCompression(int, float);
void SetWheelDampingRelaxation(int, float);
void SetWheelDirection(int, Vector3);
void SetWheelFrictionSlip(int, float);
void SetWheelRadius(int, float);
void SetWheelRestLength(int, float);
void SetWheelRollInfluence(int, float);
void SetWheelSkidInfo(int, float);
void SetWheelSkidInfoCumulative(int, float);
void SetWheelSuspensionStiffness(int, float);
void UpdateWheelTransform(int, bool);
bool WheelIsGrounded(int);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
IntVector3 coordinateSystem;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
float inAirRPM;
float maxSideSlipSpeed;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
int numWheels;
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;

// Constants:
static const IntVector3 FORWARD_RIGHT_UP;
static const IntVector3 FORWARD_UP_RIGHT;
static const IntVector3 RIGHT_FORWARD_UP;
static const IntVector3 RIGHT_UP_FORWARD;
static const IntVector3 UP_FORWARD_RIGHT;
static const IntVector3 UP_RIGHT_FORWARD;
};

class Rect
{
public:
Rect();
Rect(const Rect&in);
Rect(float, float, float, float);
Rect(const Vector2&in, const Vector2&in);
Rect(const Vector4&in);
// Methods:
void Clear();
void Clip(const Rect&);
void Define(const Vector2&);
void Define(const Vector2&, const Vector2&);
bool Defined() const;
bool Equals(const Rect&) const;
Intersection IsInside(const Rect&) const;
Intersection IsInside(const Vector2&) const;
void Merge(const Rect&);
void Merge(const Vector2&);
Vector4 ToVector4() const;

// Properties:
float bottom;
/* readonly */
Vector2 center;
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
public:

// Properties:
/* readonly */
int refs;
/* readonly */
int weakRefs;
};

class RenderPath
{
public:
RenderPath();
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
/* readonly */
Array<bool> added;
Array<RenderPathCommand> commands;
/* readonly */
Array<bool> enabled;
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
public:
~RenderPathCommand();
RenderPathCommand();
RenderPathCommand(const RenderPathCommand&in);
// Methods:
void RemoveShaderParameter(const String&);
void SetOutput(uint, const String&, CubeMapFace = FACE_POSITIVE_X);

// Properties:
BlendMode blendMode;
Color clearColor;
float clearDepth;
uint clearFlags;
uint clearStencil;
String depthStencilName;
bool enabled;
String eventName;
bool markToStencil;
String metadata;
uint numOutputs;
Array<CubeMapFace> outputFaces;
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
public:
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
/* readonly */
bool resolveDirty;
RenderSurfaceUpdateMode updateMode;
/* readonly */
TextureUsage usage;
Array<Viewport> viewports;
/* readonly */
int width;
};

class RenderTargetInfo
{
public:
~RenderTargetInfo();
RenderTargetInfo();
RenderTargetInfo(const RenderTargetInfo&in);

// Properties:
bool autoResolve;
bool cubemap;
bool enabled;
bool filtered;
uint format;
int multiSample;
String name;
bool persistent;
bool sRGB;
Vector2 size;
RenderTargetSizeMode sizeMode;
String tag;
};

class Renderer
{
public:
// Methods:
void DrawDebugGeometry(bool) const;
Viewport GetViewportForScene(Scene, uint);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void ReloadShaders() const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetDefaultRenderPath(XMLFile);
void SetVSMShadowParameters(float, float);

// Properties:
/* readonly */
String category;
/* readonly */
Material defaultLightRamp;
/* readonly */
Material defaultLightSpot;
/* readonly */
Material defaultMaterial;
RenderPath defaultRenderPath;
Technique defaultTechnique;
/* readonly */
Zone defaultZone;
bool drawShadows;
bool dynamicInstancing;
bool hdrRendering;
int materialQuality;
int maxOccluderTriangles;
int maxShadowMaps;
int maxSortedInstances;
int minInstances;
float mobileNormalOffsetMul;
float mobileShadowBiasAdd;
float mobileShadowBiasMul;
/* readonly */
uint numBatches;
int numExtraInstancingBufferElements;
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
ShadowQuality shadowQuality;
float shadowSoftness;
bool specularLighting;
int textureAnisotropy;
TextureFilterMode textureFilterMode;
int textureQuality;
bool threadedOcclusion;
/* readonly */
StringHash type;
/* readonly */
String typeName;
Array<Viewport> viewports;
int vsmMultiSample;
Vector2 vsmShadowParameters;
/* readonly */
int weakRefs;
};

class Resource
{
public:
// Methods:
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String category;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class ResourceCache
{
public:
// Methods:
bool AddManualResource(Resource);
bool AddPackageFile(PackageFile, uint = M_MAX_UNSIGNED);
bool AddPackageFile(const String&, uint = M_MAX_UNSIGNED);
bool AddResourceDir(const String&, uint = M_MAX_UNSIGNED);
bool BackgroundLoadResource(const String&, const String&, bool = true);
bool Exists(const String&) const;
Resource GetExistingResource(StringHash, const String&);
Resource GetExistingResource(const String&, const String&);
File GetFile(const String&);
String GetPreferredResourceDir(const String&) const;
Resource GetResource(StringHash, const String&, bool = true);
Resource GetResource(const String&, const String&, bool = true);
String GetResourceFileName(const String&) const;
Array<Resource> GetResources(StringHash);
Array<Resource> GetResources(const String&);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void ReleaseAllResources(bool = false);
void ReleaseResource(const String&, const String&, bool = false);
void ReleaseResources(StringHash, bool = false);
void ReleaseResources(const String&, bool = false);
void ReleaseResources(const String&, const String&, bool = false);
bool ReloadResource(Resource);
void ReloadResourceWithDependencies(const String&);
void RemovePackageFile(PackageFile, bool = true, bool = false);
void RemovePackageFile(const String&, bool = true, bool = false);
void RemoveResourceDir(const String&);
String SanitateResourceDirName(const String&) const;
String SanitateResourceName(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
bool autoReloadResources;
/* readonly */
String category;
int finishBackgroundResourcesMs;
Array<uint64> memoryBudget;
/* readonly */
Array<uint64> memoryUse;
/* readonly */
uint numBackgroundLoadResources;
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
uint64 totalMemoryUse;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ResourceRef
{
public:
~ResourceRef();
ResourceRef();
ResourceRef(const ResourceRef&in);
ResourceRef(const String&in, const String&in);

// Properties:
String name;
StringHash type;
};

class ResourceRefList
{
public:
~ResourceRefList();
ResourceRefList();
ResourceRefList(const ResourceRefList&in);
// Methods:
void Resize(uint);

// Properties:
/* readonly */
bool empty;
/* readonly */
uint length;
Array<String> names;
StringHash type;
};

class RibbonTrail
{
public:
// Methods:
void ApplyAttributes();
void Commit();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
float animationLodBias;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
Vector3 baseVelocity;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
float drawDistance;
bool emitting;
bool enabled;
/* readonly */
bool enabledEffective;
Color endColor;
float endScale;
/* readonly */
uint id;
/* readonly */
bool inView;
float lifetime;
uint lightMask;
float lodBias;
Material material;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
bool sorted;
Color startColor;
float startScale;
uint tailColumn;
bool temporary;
TrailType trailType;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool updateInvisible;
float vertexDistance;
uint viewMask;
/* readonly */
int weakRefs;
float width;
/* readonly */
BoundingBox worldBoundingBox;
/* readonly */
Zone zone;
uint zoneMask;
};

class RigidBody
{
public:
// Methods:
void Activate();
void ApplyAttributes();
void ApplyForce(const Vector3&);
void ApplyForce(const Vector3&, const Vector3&);
void ApplyImpulse(const Vector3&);
void ApplyImpulse(const Vector3&, const Vector3&);
void ApplyTorque(const Vector3&);
void ApplyTorqueImpulse(const Vector3&);
void DisableMassUpdate();
void DrawDebugGeometry(DebugRenderer, bool);
void EnableMassUpdate();
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
Vector3 GetVelocityAtPoint(const Vector3&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void ReAddBodyToWorld();
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetForces();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetCollisionLayerAndMask(uint, uint);
void SetInterceptNetworkUpdate(const String&, bool);
void SetTransform(const Vector3&, const Quaternion&);

// Properties:
/* readonly */
bool active;
float angularDamping;
Vector3 angularFactor;
float angularRestThreshold;
Vector3 angularVelocity;
bool animationEnabled;
Vector3 anisotropicFriction;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
Vector3 position;
/* readonly */
int refs;
/* readonly */
bool replicated;
float restitution;
float rollingFriction;
Quaternion rotation;
bool temporary;
bool trigger;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useGravity;
/* readonly */
int weakRefs;
};

class RigidBody2D
{
public:
// Methods:
void ApplyAngularImpulse(float, bool);
void ApplyAttributes();
void ApplyForce(const Vector2&, const Vector2&, bool);
void ApplyForceToCenter(const Vector2&, bool);
void ApplyLinearImpulse(const Vector2&, const Vector2&, bool);
void ApplyLinearImpulseToCenter(const Vector2&, bool);
void ApplyTorque(float, bool);
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool allowSleep;
float angularDamping;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool awake;
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
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useFixtureMass;
/* readonly */
int weakRefs;
};

class Scene
{
public:
Scene();
Scene(const String&in);
// Methods:
void AddChild(Node, uint = M_MAX_UNSIGNED);
void AddRequiredPackageFile(PackageFile);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void Clear(bool = true, bool = true);
void ClearRequiredPackageFiles();
Component CloneComponent(Component, CreateMode, uint = 0);
Component CloneComponent(Component, uint = 0);
Node CreateChild(const String& = String ( ), CreateMode = REPLICATED, uint = 0, bool = false);
Component CreateComponent(const String&, CreateMode = REPLICATED, uint = 0);
ScriptObject CreateScriptObject(ScriptFile, const String&, CreateMode = REPLICATED);
ScriptObject CreateScriptObject(const String&, const String&, CreateMode = REPLICATED);
Node CreateTemporaryChild(const String& = String ( ), CreateMode = REPLICATED, uint = 0);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
Node GetChild(const String&, bool = false) const;
Array<Node> GetChildren(bool = false) const;
Array<Node> GetChildrenWithComponent(const String&, bool = false) const;
Array<Node> GetChildrenWithScript(bool = false) const;
Array<Node> GetChildrenWithScript(const String&, bool = false) const;
Array<Node> GetChildrenWithTag(const String&, bool = false) const;
Component GetComponent(const String&, bool = false) const;
Component GetComponent(uint) const;
Array<Component> GetComponents() const;
Array<Component> GetComponents(const String&, bool = false) const;
bool GetInterceptNetworkUpdate(const String&) const;
Node GetNode(uint) const;
Array<Node> GetNodesWithTag(const String&) const;
Component GetOrCreateComponent(const String&, CreateMode = REPLICATED, uint = 0);
Component GetParentComponent(const String&, bool = false) const;
ScriptObject GetScriptObject() const;
ScriptObject GetScriptObject(const String&) const;
bool HasComponent(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&);
Node Instantiate(File, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node Instantiate(VectorBuffer&, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node InstantiateJSON(File, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node InstantiateJSON(JSONFile, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node InstantiateJSON(VectorBuffer&, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node InstantiateJSON(const JSONValue&, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node InstantiateXML(File, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node InstantiateXML(VectorBuffer&, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node InstantiateXML(XMLFile, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
Node InstantiateXML(const XMLElement&, const Vector3&, const Quaternion&, CreateMode = REPLICATED);
bool IsChildOf(Node) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadAsync(File, LoadMode = LOAD_SCENE_AND_RESOURCES);
bool LoadAsyncXML(File, LoadMode = LOAD_SCENE_AND_RESOURCES);
bool LoadJSON(File);
bool LoadJSON(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(const XMLElement&);
Vector3 LocalToWorld(const Vector3&) const;
Vector3 LocalToWorld(const Vector4&) const;
Vector2 LocalToWorld2D(const Vector2&) const;
bool LookAt(const Vector3&, const Vector3& = Vector3 ( 0 , 1 , 0 ), TransformSpace = TS_WORLD);
void MarkNetworkUpdate() const;
void Pitch(float, TransformSpace = TS_LOCAL);
void RegisterVar(const String&);
void Remove();
void RemoveAllChildren();
void RemoveAllComponents();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(Node);
void RemoveChildren(bool, bool, bool);
void RemoveComponent(Component);
void RemoveComponent(const String&);
void RemoveComponents(bool, bool);
void RemoveComponents(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ReorderComponent(Component, uint);
void ResetToDefault();
void Roll(float, TransformSpace = TS_LOCAL);
void Rotate(const Quaternion&, TransformSpace = TS_LOCAL);
void Rotate2D(float, TransformSpace = TS_LOCAL);
void RotateAround(const Vector3&, const Quaternion&, TransformSpace = TS_LOCAL);
void RotateAround2D(const Vector2&, float, TransformSpace = TS_LOCAL);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(File, const String& = "\t");
bool SaveJSON(JSONValue&) const;
bool SaveJSON(VectorBuffer&, const String& = "\t");
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
void Scale(const Vector3&);
void Scale(float);
void Scale2D(const Vector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
void SetPosition2D(float, float);
void SetScale(float);
void SetScale2D(float, float);
void SetTransform(const Matrix3x4&);
void SetTransform(const Vector3&, const Quaternion&);
void SetTransform(const Vector3&, const Quaternion&, const Vector3&);
void SetTransform(const Vector3&, const Quaternion&, float);
void SetTransform2D(const Vector2&, float);
void SetTransform2D(const Vector2&, float, const Vector2&);
void SetTransform2D(const Vector2&, float, float);
void SetWorldTransform(const Vector3&, const Quaternion&);
void SetWorldTransform(const Vector3&, const Quaternion&, const Vector3&);
void SetWorldTransform(const Vector3&, const Quaternion&, float);
void SetWorldTransform2D(const Vector2&, float);
void SetWorldTransform2D(const Vector2&, float, const Vector2&);
void SetWorldTransform2D(const Vector2&, float, float);
void StopAsyncLoading();
const String& GetVarName(StringHash) const;
void Translate(const Vector3&, TransformSpace = TS_LOCAL);
void Translate2D(const Vector2&, TransformSpace = TS_LOCAL);
void UnregisterAllVars(const String&);
void UnregisterVar(const String&);
void Update(float);
Vector3 WorldToLocal(const Vector3&) const;
Vector3 WorldToLocal(const Vector4&) const;
Vector2 WorldToLocal2D(const Vector2&) const;
void Yaw(float, TransformSpace = TS_LOCAL);

// Properties:
/* readonly */
Array<Node> allChildrenByName;
bool animationEnabled;
/* readonly */
LoadMode asyncLoadMode;
/* readonly */
bool asyncLoading;
int asyncLoadingMs;
/* readonly */
float asyncProgress;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
/* readonly */
uint checksum;
/* readonly */
Array<Node> children;
/* readonly */
Array<Node> childrenByName;
/* readonly */
Array<Component> components;
/* readonly */
DebugRenderer debugRenderer;
Vector3 direction;
float elapsedTime;
/* readonly */
String fileName;
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
ObjectAnimation objectAnimation;
/* readonly */
Octree octree;
Node parent;
/* readonly */
PhysicsWorld physicsWorld;
/* readonly */
PhysicsWorld2D physicsWorld2D;
Vector3 position;
Vector2 position2D;
/* readonly */
int refs;
/* readonly */
bool replicated;
/* readonly */
Array<PackageFile> requiredPackageFiles;
/* readonly */
Vector3 right;
Quaternion rotation;
float rotation2D;
Vector3 scale;
Vector2 scale2D;
/* readonly */
ScriptObject scriptObject;
/* readonly */
Vector3 signedWorldScale;
float smoothingConstant;
float snapThreshold;
/* readonly */
Array<String> tags;
bool temporary;
float timeScale;
/* readonly */
Matrix3x4 transform;
/* readonly */
StringHash type;
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
Vector2 worldPosition2D;
/* readonly */
Vector3 worldRight;
Quaternion worldRotation;
float worldRotation2D;
Vector3 worldScale;
Vector2 worldScale2D;
/* readonly */
Matrix3x4 worldTransform;
/* readonly */
Vector3 worldUp;
};

class Script
{
public:
// Methods:
void DumpAPI(DumpMode = DOXYGEN, const String& = String ( ));
bool Execute(const String&);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String category;
Scene defaultScene;
ScriptFile defaultScriptFile;
bool executeConsoleCommands;
/* readonly */
int refs;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ScriptFile
{
public:
ScriptFile();
ScriptFile(const String&in);
// Methods:
void ClearDelayedExecute(const String& = String ( ));
void DelayedExecute(float, bool, const String&, const Array<Variant> = null);
bool Execute(const String&, const Array<Variant> = null);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
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
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class ScriptInstance
{
public:
// Methods:
void ApplyAttributes();
void ClearDelayedExecute(const String& = String ( ));
bool CreateObject(ScriptFile, const String&);
void DelayedExecute(float, bool, const String&, const Array<Variant> = null);
void DrawDebugGeometry(DebugRenderer, bool);
bool Execute(const String&, const Array<Variant> = null);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasMethod(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsA(const String&) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
ScriptFile scriptFile;
/* readonly */
ScriptObject scriptObject;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class ScriptObject
{
public:
};

class ScrollBar
{
public:
ScrollBar();
ScrollBar(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
void ChangeValue(float);
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void StepBack();
void StepForward();
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
Button backButton;
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
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
/* readonly */
float effectiveScrollStep;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
ObjectAnimation objectAnimation;
float opacity;
Orientation orientation;
UIElement parent;
Vector2 pivot;
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
/* readonly */
Array<String> tags;
bool temporary;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
float value;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class ScrollView
{
public:
ScrollView();
ScrollView(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetScrollBarsVisible(bool, bool);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void SetViewPosition(int, int);
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool autoDisableChildren;
float autoDisableThreshold;
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
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
bool horizontalScrollBarVisible;
/* readonly */
bool hovering;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
ObjectAnimation objectAnimation;
float opacity;
float pageStep;
UIElement parent;
Vector2 pivot;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool scrollBarsAutoVisible;
float scrollDeceleration;
/* readonly */
BorderImage scrollPanel;
float scrollSnapEpsilon;
float scrollStep;
bool selected;
IntVector2 size;
bool sortChildren;
String style;
/* readonly */
Array<String> tags;
bool temporary;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
/* readonly */
ScrollBar verticalScrollBar;
bool verticalScrollBarVisible;
IntVector2 viewPosition;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class Serializable
{
public:
// Methods:
void ApplyAttributes();
Variant GetAttribute(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void RemoveInstanceDefault();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetAttribute(const String&, const Variant&);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
/* readonly */
uint numAttributes;
/* readonly */
int refs;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Serializer
{
public:
// Methods:
uint Write(Array<uint8>);
bool WriteBool(bool);
bool WriteBoundingBox(const BoundingBox&);
bool WriteByte(int8);
bool WriteColor(const Color&);
bool WriteDouble(double);
bool WriteFileID(const String&);
bool WriteFloat(float);
bool WriteInt(int);
bool WriteInt64(int64);
bool WriteIntRect(const IntRect&);
bool WriteIntVector2(const IntVector2&);
bool WriteLine(const String&);
bool WriteMatrix3(const Matrix3&);
bool WriteMatrix3x4(const Matrix3x4&);
bool WriteMatrix4(const Matrix4&);
bool WriteNetID(uint);
bool WritePackedQuaternion(const Quaternion&);
bool WritePackedVector3(const Vector3&, float);
bool WriteQuaternion(const Quaternion&);
bool WriteShort(int16);
bool WriteString(const String&);
bool WriteStringHash(const StringHash&);
bool WriteUByte(uint8);
bool WriteUInt(uint);
bool WriteUInt64(uint64);
bool WriteUShort(uint16);
bool WriteVLE(uint);
bool WriteVariant(const Variant&);
bool WriteVariantMap(const VariantMap&);
bool WriteVector2(const Vector2&);
bool WriteVector3(const Vector3&);
bool WriteVector4(const Vector4&);
bool WriteVectorBuffer(const VectorBuffer&);
};

class Skeleton
{
public:
// Methods:
Bone GetBone(const String&) const;
uint GetBoneIndex(const String&) const;
Bone GetBoneParent(Bone) const;
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
public:
// Methods:
void ApplyAttributes();
void ApplyMaterialList(const String& = String ( ));
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
Array<Material> materials;
uint maxLights;
Model model;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
uint numGeometries;
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
StringHash type;
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
public:
Slider();
Slider(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
void ChangeValue(float);
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetDisabledOffset(int, int);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
IntVector2 disabledOffset;
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
IntRect imageBorder;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
/* readonly */
BorderImage knob;
IntRect layoutBorder;
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Material material;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
ObjectAnimation objectAnimation;
float opacity;
Orientation orientation;
UIElement parent;
Vector2 pivot;
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
/* readonly */
Array<String> tags;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
float value;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class SmoothedTransform
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
void Update(float, float);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
Vector3 targetPosition;
Quaternion targetRotation;
Vector3 targetWorldPosition;
Quaternion targetWorldRotation;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Sound
{
public:
Sound();
Sound(const String&in);
// Methods:
void AddMetadata(const String&, const Variant&);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
void RemoveAllMetadata();
void RemoveMetadata(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String category;
/* readonly */
bool compressed;
/* readonly */
float frequency;
/* readonly */
bool hasMetadata;
/* readonly */
float length;
bool looped;
/* readonly */
uint memoryUse;
Array<Variant> metadata;
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
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class SoundListener
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class SoundSource
{
public:
SoundSource();
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Play(Sound);
void Play(Sound, float);
void Play(Sound, float, float);
void Play(Sound, float, float, float);
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void Seek(float);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
void Stop();

// Properties:
bool animationEnabled;
/* readonly */
float attenuation;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
AutoRemoveMode autoRemoveMode;
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
ObjectAnimation objectAnimation;
float panning;
/* readonly */
bool playing;
/* readonly */
int refs;
/* readonly */
bool replicated;
/* readonly */
Sound sound;
String soundType;
bool temporary;
/* readonly */
float timePosition;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class SoundSource3D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Play(Sound);
void Play(Sound, float);
void Play(Sound, float, float);
void Play(Sound, float, float, float);
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void Seek(float);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAngleAttenuation(float, float);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDistanceAttenuation(float, float, float);
void SetInterceptNetworkUpdate(const String&, bool);
void Stop();

// Properties:
bool animationEnabled;
/* readonly */
float attenuation;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
AutoRemoveMode autoRemoveMode;
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
ObjectAnimation objectAnimation;
float outerAngle;
float panning;
/* readonly */
bool playing;
/* readonly */
int refs;
/* readonly */
bool replicated;
float rolloffFactor;
/* readonly */
Sound sound;
String soundType;
bool temporary;
/* readonly */
float timePosition;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Sphere
{
public:
Sphere();
Sphere(const Sphere&in);
Sphere(const Vector3&in, float);
Sphere(const BoundingBox&in);
Sphere(const Frustum&in);
Sphere(const Polyhedron&in);
// Methods:
void Clear();
void Define(const BoundingBox&);
void Define(const Frustum&);
void Define(const Polyhedron&);
void Define(const Sphere&);
void Define(const Vector3&, float);
bool Defined() const;
float Distance(const Vector3&) const;
Vector3 GetLocalPoint(float, float) const;
Vector3 GetPoint(float, float) const;
Intersection IsInside(const BoundingBox&) const;
Intersection IsInside(const Sphere&) const;
Intersection IsInside(const Vector3&) const;
Intersection IsInsideFast(const BoundingBox&) const;
Intersection IsInsideFast(const Sphere&) const;
void Merge(const BoundingBox&);
void Merge(const Frustum&);
void Merge(const Sphere&);
void Merge(const Vector3&);

// Properties:
Vector3 center;
float radius;
};

class Spline
{
public:
Spline();
Spline(InterpolationMode);
Spline(Variant[]@, InterpolationMode = BEZIER_CURVE);
Spline(const Spline&in);
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
public:
// Methods:
void AddControlPoint(Node, uint = M_MAX_UNSIGNED);
void ApplyAttributes();
void ClearControlPoints();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
Vector3 GetPoint(float) const;
Vector3 GetPosition() const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Move(float);
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveControlPoint(Node);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void Reset();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
void SetPosition(float);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
float length;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
float speed;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Sprite
{
public:
Sprite();
Sprite(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHotSpot(int, int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(float, float);
void SetScale(float);
void SetScale(float, float);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
BlendMode blendMode;
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
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
IntVector2 hotSpot;
/* readonly */
bool hovering;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
ObjectAnimation objectAnimation;
float opacity;
UIElement parent;
Vector2 pivot;
Vector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
float rotation;
Vector2 scale;
/* readonly */
IntVector2 screenPosition;
bool selected;
IntVector2 size;
bool sortChildren;
String style;
/* readonly */
Array<String> tags;
bool temporary;
Texture texture;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class Sprite2D
{
public:
Sprite2D();
Sprite2D(const String&in);
// Methods:
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String category;
Vector2 hotSpot;
/* readonly */
uint memoryUse;
String name;
IntVector2 offset;
IntRect rectangle;
/* readonly */
int refs;
Texture2D texture;
float textureEdgeOffset;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class SpriteSheet2D
{
public:
SpriteSheet2D();
SpriteSheet2D(const String&in);
// Methods:
void DefineSprite(const String&, const IntRect&, const Vector2& = Vector2 ( 0.5f , 0.5f ), const IntVector2& = IntVector2 :: ZERO);
Sprite2D GetSprite(const String&);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String category;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
Texture2D texture;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class StaticModel
{
public:
// Methods:
void ApplyAttributes();
void ApplyMaterialList(const String& = String ( ));
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool IsInside(const Vector3&) const;
bool IsInsideLocal(const Vector3&) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
Array<Material> materials;
uint maxLights;
Model model;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
uint numGeometries;
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
uint occlusionLodLevel;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
StringHash type;
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
public:
// Methods:
void AddInstanceNode(Node);
void ApplyAttributes();
void ApplyMaterialList(const String& = String ( ));
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllInstanceNodes();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveInstanceNode(Node);
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
uint occlusionLodLevel;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
StringHash type;
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
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetFlip(bool, bool, bool = false);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
float alpha;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
BlendMode blendMode;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
Color color;
Material customMaterial;
float drawDistance;
Rect drawRect;
bool enabled;
/* readonly */
bool enabledEffective;
bool flipX;
bool flipY;
Vector2 hotSpot;
/* readonly */
uint id;
/* readonly */
bool inView;
int layer;
uint lightMask;
float lodBias;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
int orderInLayer;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
Sprite2D sprite;
bool swapXY;
bool temporary;
Rect textureRect;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDrawRect;
bool useHotSpot;
bool useTextureRect;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
uint zoneMask;
};

class StretchableSprite2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetFlip(bool, bool, bool = false);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
float alpha;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
BlendMode blendMode;
IntRect border;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
Color color;
Material customMaterial;
float drawDistance;
Rect drawRect;
bool enabled;
/* readonly */
bool enabledEffective;
bool flipX;
bool flipY;
Vector2 hotSpot;
/* readonly */
uint id;
/* readonly */
bool inView;
int layer;
uint lightMask;
float lodBias;
uint maxLights;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
int orderInLayer;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
Sprite2D sprite;
bool swapXY;
bool temporary;
Rect textureRect;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDrawRect;
bool useHotSpot;
bool useTextureRect;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
uint zoneMask;
};

class String
{
public:
~String();
String();
String(const String&in);
String(int);
String(uint);
String(float);
String(double);
String(bool);
String(const char*);
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
Array<String> Split(uint8, bool = false) const;
bool StartsWith(const String&, bool = true) const;
String Substring(uint) const;
String Substring(uint, uint) const;
String SubstringUTF8(uint) const;
String SubstringUTF8(uint, uint) const;
bool ToBool() const;
Color ToColor() const;
double ToDouble() const;
float ToFloat() const;
int ToInt(int = 10) const;
int64 ToInt64(int = 10) const;
IntRect ToIntRect() const;
IntVector2 ToIntVector2() const;
IntVector3 ToIntVector3() const;
String ToLower() const;
Matrix3 ToMatrix3() const;
Matrix3x4 ToMatrix3x4() const;
Matrix4 ToMatrix4() const;
Quaternion ToQuaternion() const;
uint ToUInt(int = 10) const;
uint64 ToUInt64(int = 10) const;
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
public:
StringHash();
StringHash(const StringHash&in);
StringHash(const String&in);
StringHash(uint);
// Methods:
String ToString() const;

// Properties:
/* readonly */
uint value;
};

class Technique
{
public:
Technique();
Technique(const String&in);
// Methods:
Technique Clone(const String& = String ( )) const;
Pass CreatePass(const String&);
Pass GetPass(const String&);
Pass GetSupportedPass(const String&);
bool HasPass(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
void RemovePass(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String category;
bool desktop;
/* readonly */
uint memoryUse;
String name;
/* readonly */
uint numPasses;
/* readonly */
Array<String> passNames;
/* readonly */
Array<Pass> passes;
/* readonly */
int refs;
/* readonly */
bool supported;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class TechniqueEntry
{
public:
~TechniqueEntry();
TechniqueEntry();
TechniqueEntry(const TechniqueEntry&in);

// Properties:
float lodDistance;
int qualityLevel;
Technique technique;
};

class Terrain
{
public:
// Methods:
void ApplyAttributes();
void ApplyHeightMap();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
float GetHeight(const Vector3&) const;
bool GetInterceptNetworkUpdate(const String&) const;
TerrainPatch GetNeighborPatch(int, int) const;
Vector3 GetNormal(const Vector3&) const;
TerrainPatch GetPatch(int, int) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
Vector3 HeightMapToWorld(const IntVector2&) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
void SetNeighbors(Terrain, Terrain, Terrain, Terrain);
IntVector2 WorldToHeightMap(const Vector3&) const;

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool castShadows;
/* readonly */
String category;
float drawDistance;
Terrain eastNeighbor;
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
uint maxLodLevels;
/* readonly */
Node node;
Terrain northNeighbor;
/* readonly */
uint numAttributes;
/* readonly */
IntVector2 numPatches;
/* readonly */
IntVector2 numVertices;
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
uint occlusionLodLevel;
int patchSize;
/* readonly */
Array<TerrainPatch> patches;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
bool smoothing;
Terrain southNeighbor;
Vector3 spacing;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
Terrain westNeighbor;
uint zoneMask;
};

class TerrainPatch
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
StringHash type;
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
public:
Text();
Text(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
void ClearSelection();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
bool SetFont(Font, float);
bool SetFont(const String&, float);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetSelection(uint, uint = M_MAX_UNSIGNED);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool autoLocalizable;
bool bringToBack;
bool bringToFront;
/* readonly */
String category;
/* readonly */
Array<Vector2> charPositions;
/* readonly */
Array<Vector2> charSizes;
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
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
Color effectColor;
bool effectRoundStroke;
IntVector2 effectShadowOffset;
int effectStrokeThickness;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
float fontSize;
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
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
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
ObjectAnimation objectAnimation;
float opacity;
UIElement parent;
Vector2 pivot;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
float rowHeight;
float rowSpacing;
/* readonly */
Array<float> rowWidths;
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
/* readonly */
Array<String> tags;
bool temporary;
String text;
HorizontalAlignment textAlignment;
TextEffect textEffect;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
bool wordwrap;
};

class Text3D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
bool SetFont(Font, float);
bool SetFont(const String&, float);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
BoundingBox boundingBox;
bool castShadows;
/* readonly */
String category;
/* readonly */
Array<Vector2> charPositions;
/* readonly */
Array<Vector2> charSizes;
/* writeonly */
Color color;
Array<Color> colors;
float drawDistance;
Color effectColor;
float effectDepthBias;
bool effectRoundStroke;
IntVector2 effectShadowOffset;
int effectStrokeThickness;
bool enabled;
/* readonly */
bool enabledEffective;
FaceCameraMode faceCameraMode;
bool fixedScreenSize;
/* readonly */
Font font;
float fontSize;
/* readonly */
int height;
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
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
float opacity;
/* readonly */
int refs;
/* readonly */
bool replicated;
/* readonly */
float rowHeight;
float rowSpacing;
/* readonly */
Array<float> rowWidths;
float shadowDistance;
uint shadowMask;
bool temporary;
String text;
HorizontalAlignment textAlignment;
TextEffect textEffect;
/* readonly */
StringHash type;
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
public:
Texture();
Texture(const String&in);
// Methods:
void AddMetadata(const String&, const Variant&);
void ClearDataLost();
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
void RemoveAllMetadata();
void RemoveMetadata(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetNumLevels(uint);

// Properties:
Array<TextureAddressMode> addressMode;
uint anisotropy;
/* readonly */
bool autoResolve;
Texture backupTexture;
Color borderColor;
/* readonly */
String category;
/* readonly */
uint components;
/* readonly */
bool compressed;
/* readonly */
bool dataLost;
TextureFilterMode filterMode;
/* readonly */
uint format;
/* readonly */
bool hasMetadata;
/* readonly */
int height;
/* readonly */
Array<int> levelHeight;
/* readonly */
Array<int> levelWidth;
/* readonly */
uint levels;
/* readonly */
bool levelsDirty;
/* readonly */
uint memoryUse;
Array<Variant> metadata;
Array<int> mipsToSkip;
/* readonly */
int multiSample;
String name;
/* readonly */
int refs;
/* readonly */
bool resolveDirty;
bool sRGB;
/* readonly */
StringHash type;
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
public:
Texture2D();
Texture2D(const String&in);
// Methods:
void AddMetadata(const String&, const Variant&);
void ClearDataLost();
Image GetImage() const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
void RemoveAllMetadata();
void RemoveMetadata(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetData(Image, bool = false);
void SetNumLevels(uint);
bool SetSize(int, int, uint, TextureUsage = TEXTURE_STATIC, int = 1, bool = true);

// Properties:
Array<TextureAddressMode> addressMode;
uint anisotropy;
/* readonly */
bool autoResolve;
Texture backupTexture;
Color borderColor;
/* readonly */
String category;
/* readonly */
uint components;
/* readonly */
bool compressed;
/* readonly */
bool dataLost;
TextureFilterMode filterMode;
/* readonly */
uint format;
/* readonly */
bool hasMetadata;
/* readonly */
int height;
/* readonly */
Array<int> levelHeight;
/* readonly */
Array<int> levelWidth;
/* readonly */
uint levels;
/* readonly */
bool levelsDirty;
/* readonly */
uint memoryUse;
Array<Variant> metadata;
Array<int> mipsToSkip;
/* readonly */
int multiSample;
String name;
/* readonly */
int refs;
/* readonly */
RenderSurface renderSurface;
/* readonly */
bool resolveDirty;
bool sRGB;
/* readonly */
StringHash type;
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

class Texture2DArray
{
public:
Texture2DArray();
Texture2DArray(const String&in);
// Methods:
void AddMetadata(const String&, const Variant&);
void ClearDataLost();
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
void RemoveAllMetadata();
void RemoveMetadata(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetData(uint, Image, bool = false);
void SetNumLevels(uint);
bool SetSize(uint, int, int, uint, TextureUsage = TEXTURE_STATIC);

// Properties:
Array<TextureAddressMode> addressMode;
uint anisotropy;
/* readonly */
bool autoResolve;
Texture backupTexture;
Color borderColor;
/* readonly */
String category;
/* readonly */
uint components;
/* readonly */
bool compressed;
/* readonly */
bool dataLost;
TextureFilterMode filterMode;
/* readonly */
uint format;
/* readonly */
bool hasMetadata;
/* readonly */
int height;
uint layers;
/* readonly */
Array<int> levelHeight;
/* readonly */
Array<int> levelWidth;
/* readonly */
uint levels;
/* readonly */
bool levelsDirty;
/* readonly */
uint memoryUse;
Array<Variant> metadata;
Array<int> mipsToSkip;
/* readonly */
int multiSample;
String name;
/* readonly */
int refs;
/* readonly */
RenderSurface renderSurface;
/* readonly */
bool resolveDirty;
bool sRGB;
/* readonly */
StringHash type;
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
public:
Texture3D();
Texture3D(const String&in);
// Methods:
void AddMetadata(const String&, const Variant&);
void ClearDataLost();
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
void RemoveAllMetadata();
void RemoveMetadata(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetData(Image, bool = false);
void SetNumLevels(uint);
bool SetSize(int, int, int, uint, TextureUsage = TEXTURE_STATIC);

// Properties:
Array<TextureAddressMode> addressMode;
uint anisotropy;
/* readonly */
bool autoResolve;
Texture backupTexture;
Color borderColor;
/* readonly */
String category;
/* readonly */
uint components;
/* readonly */
bool compressed;
/* readonly */
bool dataLost;
TextureFilterMode filterMode;
/* readonly */
uint format;
/* readonly */
bool hasMetadata;
/* readonly */
int height;
/* readonly */
Array<int> levelHeight;
/* readonly */
Array<int> levelWidth;
/* readonly */
uint levels;
/* readonly */
bool levelsDirty;
/* readonly */
uint memoryUse;
Array<Variant> metadata;
Array<int> mipsToSkip;
/* readonly */
int multiSample;
String name;
/* readonly */
int refs;
/* readonly */
bool resolveDirty;
bool sRGB;
/* readonly */
StringHash type;
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
public:
TextureCube();
TextureCube(const String&in);
// Methods:
void AddMetadata(const String&, const Variant&);
void ClearDataLost();
Image GetImage(CubeMapFace) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
void RemoveAllMetadata();
void RemoveMetadata(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetData(CubeMapFace, Image, bool = false);
void SetNumLevels(uint);
bool SetSize(int, uint, TextureUsage = TEXTURE_STATIC, int = 1);

// Properties:
Array<TextureAddressMode> addressMode;
uint anisotropy;
/* readonly */
bool autoResolve;
Texture backupTexture;
Color borderColor;
/* readonly */
String category;
/* readonly */
uint components;
/* readonly */
bool compressed;
/* readonly */
bool dataLost;
TextureFilterMode filterMode;
/* readonly */
uint format;
/* readonly */
bool hasMetadata;
/* readonly */
int height;
/* readonly */
Array<int> levelHeight;
/* readonly */
Array<int> levelWidth;
/* readonly */
uint levels;
/* readonly */
bool levelsDirty;
/* readonly */
uint memoryUse;
Array<Variant> metadata;
Array<int> mipsToSkip;
/* readonly */
int multiSample;
String name;
/* readonly */
int refs;
/* readonly */
Array<RenderSurface> renderSurfaces;
/* readonly */
bool resolveDirty;
bool sRGB;
/* readonly */
StringHash type;
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
public:

// Properties:
float time;
Rect uv;
};

class Tile2D
{
public:
// Methods:
bool HasProperty(const String&) const;
const String& GetProperty(const String&) const;

// Properties:
/* readonly */
bool flipX;
/* readonly */
bool flipY;
/* readonly */
uint gid;
/* readonly */
int refs;
/* readonly */
Sprite2D sprite;
/* readonly */
bool swapXY;
/* readonly */
int weakRefs;
};

class TileMap2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
TileMapLayer2D GetLayer(uint) const;
Array<TileMapObject2D> GetTileCollisionShapes(uint) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
bool PositionToTileIndex(int&, int&, const Vector2&) const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
Vector2 TileIndexToPosition(int, int) const;

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
TileMapInfo2D info;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
uint numLayers;
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
TmxFile2D tmxFile;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class TileMapInfo2D
{
public:

// Properties:
int height;
/* readonly */
float mapHeight;
/* readonly */
float mapWidth;
Orientation2D orientation;
float tileHeight;
float tileWidth;
int width;
};

class TileMapLayer2D
{
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
TileMapObject2D GetObject(uint) const;
Node GetObjectNode(uint) const;
Tile2D GetTile(int, int) const;
Node GetTileNode(int, int) const;
bool HasProperty(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);
const String& GetProperty(const String&) const;

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
int drawOrder;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
int height;
/* readonly */
uint id;
/* readonly */
Node imageNode;
/* readonly */
TileMapLayerType2D layerType;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
/* readonly */
uint numObjects;
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool visible;
/* readonly */
int weakRefs;
/* readonly */
int width;
};

class TileMapObject2D
{
public:
// Methods:
bool HasProperty(const String&) const;
const String& GetProperty(const String&) const;
const Vector2& GetPoint(uint) const;

// Properties:
/* readonly */
String name;
/* readonly */
uint numPoints;
/* readonly */
TileObjectType2D objectType;
/* readonly */
Vector2 position;
/* readonly */
int refs;
/* readonly */
Vector2 size;
/* readonly */
bool tileFlipX;
/* readonly */
bool tileFlipY;
/* readonly */
uint tileGid;
/* readonly */
Sprite2D tileSprite;
/* readonly */
bool tileSwapXY;
/* readonly */
String type;
/* readonly */
int weakRefs;
};

class Time
{
public:
// Methods:
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String category;
/* readonly */
float elapsedTime;
/* readonly */
uint frameNumber;
/* readonly */
float framesPerSecond;
/* readonly */
int refs;
/* readonly */
uint systemTime;
/* readonly */
uint timeSinceEpoch;
/* readonly */
String timeStamp;
/* readonly */
float timeStep;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class Timer
{
public:
Timer();
// Methods:
uint GetMSec(bool);
void Reset();
};

class TmxFile2D
{
public:
TmxFile2D();
TmxFile2D(const String&in);
// Methods:
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));

// Properties:
/* readonly */
String category;
float edgeOffset;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class ToolTip
{
public:
ToolTip();
ToolTip(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void Reset();
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const StringHash&);
void add_altTarget(UIElement);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
ObjectAnimation objectAnimation;
float opacity;
UIElement parent;
Vector2 pivot;
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
/* readonly */
Array<String> tags;
bool temporary;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class TouchState
{
public:

// Properties:
IntVector2 delta;
IntVector2 lastPosition;
IntVector2 position;
float pressure;
int touchID;
/* readonly */
UIElement touchedElement;
};

class UI
{
public:
// Methods:
void Clear();
void DebugDraw(UIElement);
UIElement GetElementAt(const IntVector2&, bool = true);
UIElement GetElementAt(int, int, bool = true);
bool HasModalElement() const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsDragging() const;
UIElement LoadLayout(File);
UIElement LoadLayout(File, XMLFile);
UIElement LoadLayout(VectorBuffer&);
UIElement LoadLayout(VectorBuffer&, XMLFile);
UIElement LoadLayout(XMLFile);
UIElement LoadLayout(XMLFile, XMLFile);
bool SaveLayout(File, UIElement);
bool SaveLayout(VectorBuffer&, UIElement);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetCustomSize(int, int);
void SetFocusElement(UIElement, bool = false);
void SetHeight(float);
void SetWidth(float);
const Array<UIElement> GetDragElements();

// Properties:
/* readonly */
String category;
String clipBoardText;
Cursor cursor;
/* readonly */
IntVector2 cursorPosition;
IntVector2 customSize;
float defaultToolTipDelay;
float doubleClickInterval;
int dragBeginDistance;
float dragBeginInterval;
UIElement focusElement;
FontHintLevel fontHintLevel;
int fontOversampling;
float fontSubpixelThreshold;
bool forceAutoHint;
/* readonly */
UIElement frontElement;
float maxDoubleClickDistance;
int maxFontTextureSize;
/* readonly */
UIElement modalRoot;
bool nonFocusedMouseWheel;
/* readonly */
int refs;
/* readonly */
UIElement root;
float scale;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useMutableGlyphs;
bool useScreenKeyboard;
bool useSystemClipboard;
/* readonly */
int weakRefs;
};

class UIComponent
{
public:
// Methods:
void ApplyAttributes();
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
/* readonly */
String category;
bool enabled;
/* readonly */
bool enabledEffective;
/* readonly */
uint id;
/* readonly */
Material material;
/* readonly */
Node node;
/* readonly */
uint numAttributes;
ObjectAnimation objectAnimation;
/* readonly */
int refs;
/* readonly */
bool replicated;
/* readonly */
UIElement root;
bool temporary;
/* readonly */
Texture2D texture;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class UIElement
{
public:
UIElement();
UIElement(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
ObjectAnimation objectAnimation;
float opacity;
UIElement parent;
Vector2 pivot;
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
/* readonly */
Array<String> tags;
bool temporary;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class UISelectable
{
public:
UISelectable();
UISelectable(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
Color hoverColor;
/* readonly */
bool hovering;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
String name;
/* readonly */
uint numAllChildren;
/* readonly */
uint numAttributes;
/* readonly */
uint numChildren;
ObjectAnimation objectAnimation;
float opacity;
UIElement parent;
Vector2 pivot;
IntVector2 position;
int priority;
/* readonly */
int refs;
/* readonly */
UIElement root;
/* readonly */
IntVector2 screenPosition;
bool selected;
Color selectionColor;
IntVector2 size;
bool sortChildren;
String style;
/* readonly */
Array<String> tags;
bool temporary;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class ValueAnimation
{
public:
ValueAnimation();
ValueAnimation(const String&in);
// Methods:
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetEventFrame(float, const String&, const VariantMap& = VariantMap ( ));
void SetKeyFrame(float, const Variant&);

// Properties:
/* readonly */
String category;
InterpMethod interpolationMethod;
/* readonly */
uint memoryUse;
String name;
/* readonly */
int refs;
float splineTension;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
VariantType valueType;
/* readonly */
int weakRefs;
};

class Variant
{
public:
~Variant();
Variant();
Variant(const Variant&in);
Variant(int);
Variant(uint);
Variant(int64);
Variant(uint64);
Variant(const StringHash&in);
Variant(bool);
Variant(float);
Variant(double);
Variant(const Vector2&in);
Variant(const Vector3&in);
Variant(const Vector4&in);
Variant(const Quaternion&in);
Variant(const Color&in);
Variant(const String&in);
Variant(const ResourceRef&in);
Variant(const ResourceRefList&in);
Variant(const Variant[]@);
Variant(const String[]@);
Variant(const VariantMap&in);
Variant(const Rect&in);
Variant(const IntRect&in);
Variant(const IntVector2&in);
Variant(const IntVector3&in);
Variant(RefCounted@);
Variant(ScriptObject@);
Variant(const Matrix3&in);
Variant(const Matrix3x4&in);
Variant(const Matrix4&in);
Variant(const String&in, const String&in);
Variant(VariantType, const String&in);
Variant(const VectorBuffer&in);
// Methods:
void Clear();
const Color& GetColor() const;
void FromString(VariantType, const String&);
void FromString(const String&, const String&);
bool GetBool() const;
VectorBuffer GetBuffer() const;
double GetDouble() const;
float GetFloat() const;
int GetInt() const;
int GetInt64() const;
RefCounted GetPtr() const;
ScriptObject GetScriptObject() const;
StringHash GetStringHash() const;
Array<String> GetStringVector() const;
uint GetUInt() const;
uint64 GetUInt64() const;
Array<Variant> GetVariantVector() const;
const IntRect& GetIntRect() const;
const IntVector2& GetIntVector2() const;
const IntVector3& GetIntVector3() const;
const Matrix3& GetMatrix3() const;
const Matrix3x4& GetMatrix3x4() const;
const Matrix4& GetMatrix4() const;
const Quaternion& GetQuaternion() const;
const Rect& GetRect() const;
const ResourceRef& GetResourceRef() const;
const ResourceRefList& GetResourceRefList() const;
const String& GetString() const;
String ToString() const;
const VariantMap& GetVariantMap() const;
const Vector2& GetVector2() const;
const Vector3& GetVector3() const;
const Vector4& GetVector4() const;

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
public:
~VariantMap();
VariantMap();
VariantMap(const VariantMap&in);
// Methods:
void Clear();
bool Contains(StringHash) const;
bool Contains(const String&) const;
bool Erase(StringHash);
bool Erase(const String&);

// Properties:
/* readonly */
Array<StringHash> keys;
/* readonly */
uint length;
/* readonly */
Array<Variant> values;
};

class Vector2
{
public:
Vector2();
Vector2(const Vector2&in);
Vector2(const IntVector2&in);
Vector2(float, float);
Vector2(float[]&inout);
// Methods:
Vector2 Abs() const;
float AbsDotProduct(const Vector2&) const;
float Angle(const Vector2&) const;
float DotProduct(const Vector2&) const;
bool Equals(const Vector2&) const;
bool IsNaN() const;
Vector2 Lerp(const Vector2&, float) const;
void Normalize();
Vector2 Normalized() const;
float ProjectOntoAxis(const Vector2&) const;
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

// Constants:
static const Vector2 DOWN;
static const Vector2 LEFT;
static const Vector2 ONE;
static const Vector2 RIGHT;
static const Vector2 UP;
static const Vector2 ZERO;
};

class Vector3
{
public:
Vector3();
Vector3(const Vector3&in);
Vector3(const Vector2&in, float);
Vector3(const Vector2&in);
Vector3(const IntVector3&in);
Vector3(float, float, float);
Vector3(float, float);
Vector3(float[]&inout);
// Methods:
Vector3 Abs() const;
float AbsDotProduct(const Vector3&) const;
float Angle(const Vector3&) const;
Vector3 CrossProduct(const Vector3&) const;
float DistanceToPlane(const Vector3&, const Vector3&) const;
float DistanceToPoint(const Vector3&) const;
float DotProduct(const Vector3&) const;
bool Equals(const Vector3&) const;
bool IsNaN() const;
Vector3 Lerp(const Vector3&, float) const;
void Normalize();
Vector3 Normalized() const;
Vector3 Orthogonalize(const Vector3&) const;
float ProjectOntoAxis(const Vector3&) const;
Vector3 ProjectOntoLine(const Vector3&, const Vector3&, bool = false) const;
Vector3 ProjectOntoPlane(const Vector3&, const Vector3&) const;
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

// Constants:
static const Vector3 BACK;
static const Vector3 DOWN;
static const Vector3 FORWARD;
static const Vector3 LEFT;
static const Vector3 ONE;
static const Vector3 RIGHT;
static const Vector3 UP;
static const Vector3 ZERO;
};

class Vector4
{
public:
Vector4();
Vector4(const Vector4&in);
Vector4(float, float, float, float);
Vector4(const Vector3&in, float);
Vector4(float[]&inout);
// Methods:
Vector4 Abs() const;
float AbsDotProduct(const Vector4&) const;
float DotProduct(const Vector4&) const;
bool Equals(const Vector4&) const;
bool IsNaN() const;
Vector4 Lerp(const Vector4&, float) const;
float ProjectOntoAxis(const Vector3&) const;
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
public:
~VectorBuffer();
VectorBuffer();
VectorBuffer(const VectorBuffer&in);
VectorBuffer(Deserializer@, uint);
// Methods:
void Clear();
Array<uint8> Read(uint);
bool ReadBool();
BoundingBox ReadBoundingBox();
int8 ReadByte();
Color ReadColor();
double ReadDouble();
String ReadFileID();
float ReadFloat();
int ReadInt();
int64 ReadInt64();
IntRect ReadIntRect();
IntVector2 ReadIntVector2();
String ReadLine();
Matrix3 ReadMatrix3();
Matrix3x4 ReadMatrix3x4();
Matrix4 ReadMatrix4();
uint ReadNetID();
Quaternion ReadPackedQuaternion();
Vector3 ReadPackedVector3(float);
Quaternion ReadQuaternion();
int16 ReadShort();
String ReadString();
StringHash ReadStringHash();
uint8 ReadUByte();
uint ReadUInt();
uint64 ReadUInt64();
uint16 ReadUShort();
uint ReadVLE();
Variant ReadVariant();
VariantMap ReadVariantMap();
Vector2 ReadVector2();
Vector3 ReadVector3();
Vector4 ReadVector4();
VectorBuffer ReadVectorBuffer(uint);
void Resize(uint);
uint Seek(uint);
uint SeekRelative(int);
void SetData(Deserializer, uint);
uint Tell() const;
uint Write(Array<uint8>);
bool WriteBool(bool);
bool WriteBoundingBox(const BoundingBox&);
bool WriteByte(int8);
bool WriteColor(const Color&);
bool WriteDouble(double);
bool WriteFileID(const String&);
bool WriteFloat(float);
bool WriteInt(int);
bool WriteInt64(int64);
bool WriteIntRect(const IntRect&);
bool WriteIntVector2(const IntVector2&);
bool WriteLine(const String&);
bool WriteMatrix3(const Matrix3&);
bool WriteMatrix3x4(const Matrix3x4&);
bool WriteMatrix4(const Matrix4&);
bool WriteNetID(uint);
bool WritePackedQuaternion(const Quaternion&);
bool WritePackedVector3(const Vector3&, float);
bool WriteQuaternion(const Quaternion&);
bool WriteShort(int16);
bool WriteString(const String&);
bool WriteStringHash(const StringHash&);
bool WriteUByte(uint8);
bool WriteUInt(uint);
bool WriteUInt64(uint64);
bool WriteUShort(uint16);
bool WriteVLE(uint);
bool WriteVariant(const Variant&);
bool WriteVariantMap(const VariantMap&);
bool WriteVector2(const Vector2&);
bool WriteVector3(const Vector3&);
bool WriteVector4(const Vector4&);
bool WriteVectorBuffer(const VectorBuffer&);

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

class VertexBuffer
{
public:
VertexBuffer();
// Methods:
VectorBuffer GetData() const;
uint GetElementOffset(VertexElementSemantic, uint8 = 0) const;
uint GetElementOffset(VertexElementType, VertexElementSemantic, uint8 = 0) const;
bool HasElement(VertexElementSemantic, uint8 = 0) const;
bool HasElement(VertexElementType, VertexElementSemantic, uint8 = 0) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
bool SetData(VectorBuffer&);
bool SetDataRange(VectorBuffer&, uint, uint, bool = false);
void SetSize(uint, Array<VertexElement>, bool = false);
void SetSize(uint, uint, bool = false);

// Properties:
/* readonly */
String category;
/* readonly */
bool dynamic;
/* readonly */
uint elementMask;
/* readonly */
Array<VertexElement> elements;
/* readonly */
int refs;
bool shadowed;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint vertexCount;
/* readonly */
uint vertexSize;
/* readonly */
int weakRefs;
};

class VertexElement
{
public:
~VertexElement();
VertexElement();
VertexElement(const VertexElement&in);
VertexElement(VertexElementType, VertexElementSemantic, uint8 index = 0, bool perInstance = false);

// Properties:
uint8 index;
uint offset;
bool perInstance;
VertexElementSemantic semantic;
VertexElementType type;
};

class View3D
{
public:
View3D();
View3D(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void QueueUpdate();
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetDisabledOffset(int, int);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void SetView(Scene, Camera, bool = true);
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
bool autoUpdate;
BlendMode blendMode;
IntRect border;
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
IntVector2 disabledOffset;
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
IntVector2 hoverOffset;
/* readonly */
bool hovering;
IntRect imageBorder;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Material material;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
bool modal;
bool modalAutoDismiss;
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
ObjectAnimation objectAnimation;
float opacity;
UIElement parent;
Vector2 pivot;
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
/* readonly */
Array<String> tags;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
StringHash type;
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
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class Viewport
{
public:
Viewport();
Viewport(Scene&, Camera&, RenderPath& renderPath = null);
Viewport(Scene&, Camera&, const IntRect&in, RenderPath& renderPath = null);
// Methods:
Ray GetScreenRay(int, int) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
Vector3 ScreenToWorldPoint(int, int, float) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetRenderPath(XMLFile);
IntVector2 WorldToScreenPoint(const Vector3&) const;

// Properties:
Camera camera;
/* readonly */
String category;
Camera cullCamera;
bool drawDebug;
IntRect rect;
/* readonly */
int refs;
RenderPath renderPath;
Scene scene;
/* readonly */
StringHash type;
/* readonly */
String typeName;
/* readonly */
int weakRefs;
};

class WeakHandle
{
public:
~WeakHandle();
WeakHandle();
WeakHandle(const WeakHandle&in);
WeakHandle(RefCounted@);
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
public:
Window();
Window(const String&in);
// Methods:
void AddChild(UIElement);
void AddTag(const String&);
void AddTags(const String&, int8 = ';');
void ApplyAttributes();
void BringToFront();
UIElement CreateChild(const String&, const String& = String ( ), uint = M_MAX_UNSIGNED);
void DisableLayoutUpdate();
IntVector2 ElementToScreen(const IntVector2&);
void EnableLayoutUpdate();
uint FindChild(UIElement) const;
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
UIElement GetChild(const String&, bool = false) const;
UIElement GetChild(const StringHash&, const Variant& = Variant ( ), bool = false) const;
Array<UIElement> GetChildren(bool = false) const;
Array<UIElement> GetChildrenWithTag(const String&, bool = false) const;
UIElement GetElementEventSender() const;
bool GetInterceptNetworkUpdate(const String&) const;
uint GetNumChildren(bool) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool HasTag(const String&) const;
void InsertChild(uint, UIElement);
bool IsChildOf(UIElement) const;
bool IsInside(IntVector2, bool);
bool IsInsideCombined(IntVector2, bool);
bool Load(File);
bool Load(VectorBuffer&);
UIElement LoadChildXML(XMLFile, XMLFile);
UIElement LoadChildXML(const XMLElement&, XMLFile);
bool LoadJSON(const JSONValue&);
bool LoadXML(File);
bool LoadXML(VectorBuffer&);
bool LoadXML(XMLFile, XMLFile);
bool LoadXML(const XMLElement&, XMLFile);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAllChildren();
void RemoveAllTags();
void RemoveAttributeAnimation(const String&);
void RemoveChild(UIElement, uint = 0);
void RemoveChild(uint);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
bool RemoveTag(const String&);
void ResetDeepEnabled();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(File, const String& = "\t");
bool SaveXML(VectorBuffer&, const String& = "\t");
bool SaveXML(XMLElement&) const;
IntVector2 ScreenToElement(const IntVector2&);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAlignment(HorizontalAlignment, VerticalAlignment);
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetDeepEnabled(bool);
void SetDisabledOffset(int, int);
void SetEnabledRecursive(bool);
void SetFixedHeight(int);
void SetFixedSize(int, int);
void SetFixedWidth(int);
void SetFullImageRect();
void SetHoverOffset(int, int);
void SetInterceptNetworkUpdate(const String&, bool);
void SetLayout(LayoutMode, int = 0, const IntRect& = IntRect ( 0 , 0 , 0 , 0 ));
void SetMaxAnchor(float, float);
void SetMaxSize(int, int);
void SetMinAnchor(float, float);
void SetMinSize(int, int);
void SetParent(UIElement, uint = M_MAX_UNSIGNED);
void SetPivot(float, float);
void SetPosition(int, int);
void SetSize(int, int);
bool SetStyle(const String&, XMLFile = null);
bool SetStyle(const XMLElement&);
bool SetStyleAuto(XMLFile = null);
void UpdateLayout();
const Variant& GetVar(const StringHash&);

// Properties:
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
IntVector2 disabledOffset;
/* readonly */
uint dragButtonCombo;
/* readonly */
int dragButtonCount;
uint dragDropMode;
bool editable;
bool elementEventSender;
bool enableAnchor;
bool enabled;
/* readonly */
bool enabledSelf;
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
IntVector2 hoverOffset;
/* readonly */
bool hovering;
IntRect imageBorder;
IntRect imageRect;
int indent;
int indentSpacing;
/* readonly */
int indentWidth;
bool internal;
IntRect layoutBorder;
Vector2 layoutFlexScale;
LayoutMode layoutMode;
int layoutSpacing;
Material material;
Vector2 maxAnchor;
int maxHeight;
IntVector2 maxOffset;
IntVector2 maxSize;
int maxWidth;
Vector2 minAnchor;
int minHeight;
IntVector2 minOffset;
IntVector2 minSize;
int minWidth;
bool modal;
bool modalAutoDismiss;
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
ObjectAnimation objectAnimation;
float opacity;
UIElement parent;
Vector2 pivot;
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
/* readonly */
Array<String> tags;
bool temporary;
Texture texture;
bool tiled;
TraversalMode traversalMode;
/* readonly */
StringHash type;
/* readonly */
String typeName;
bool useDerivedOpacity;
/* readonly */
VariantMap vars;
VerticalAlignment verticalAlignment;
bool visible;
/* readonly */
bool visibleEffective;
/* readonly */
int weakRefs;
int width;
};

class XMLElement
{
public:
~XMLElement();
XMLElement();
XMLElement(const XMLElement&in);
// Methods:
bool AppendChild(XMLElement, bool);
XMLElement CreateChild(const String&);
String GetAttribute(const String& = String ( )) const;
String GetAttributeLower(const String&) const;
Array<String> GetAttributeNames() const;
String GetAttributeUpper(const String&) const;
bool GetBool(const String&) const;
BoundingBox GetBoundingBox() const;
XMLElement GetChild(const String& = String ( )) const;
Color GetColor(const String&) const;
double GetDouble(const String&) const;
float GetFloat(const String&) const;
int GetInt(const String&) const;
int64 GetInt64(const String&) const;
IntRect GetIntRect(const String&) const;
IntVector2 GetIntVector2(const String&) const;
IntVector3 GetIntVector3(const String&) const;
Matrix3 GetMatrix3(const String&) const;
Matrix3x4 GetMatrix3x4(const String&) const;
Matrix4 GetMatrix4(const String&) const;
XMLElement GetNext(const String& = String ( )) const;
XMLElement GetOrCreateChild(const String&);
Quaternion GetQuaternion(const String&) const;
ResourceRef GetResourceRef() const;
ResourceRefList GetResourceRefList() const;
uint GetUInt(const String&) const;
uint64 GetUInt64(const String&) const;
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
bool Remove();
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
bool SetDouble(const String&, double);
bool SetFloat(const String&, float);
bool SetInt(const String&, int);
bool SetInt64(const String&, int64);
bool SetIntRect(const String&, const IntRect&);
bool SetIntVector2(const String&, const IntVector2&);
bool SetIntVector3(const String&, const IntVector3&);
bool SetMatrix3(const String&, const Matrix3&);
bool SetMatrix3x4(const String&, const Matrix3x4&);
bool SetMatrix4(const String&, const Matrix4&);
bool SetQuaternion(const String&, const Quaternion&);
bool SetResourceRef(const String&, const ResourceRef&);
bool SetResourceRefList(const String&, const ResourceRefList&);
bool SetUInt(const String&, uint);
bool SetUInt64(const String&, uint64);
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
public:
XMLFile();
XMLFile(const String&in);
// Methods:
XMLElement CreateRoot(const String&);
bool FromString(const String&);
XMLElement GetOrCreateRoot(const String&);
XMLElement GetRoot(const String& = String ( ));
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool Load(File);
bool Load(VectorBuffer&);
bool Load(const String&);
void Patch(XMLFile);
void Patch(const XMLElement&);
bool Save(File) const;
bool Save(File, const String&) const;
bool Save(VectorBuffer&) const;
bool Save(const String&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
String ToString(const String& = String ( "\t" )) const;

// Properties:
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
StringHash type;
/* readonly */
String typeName;
/* readonly */
uint useTimer;
/* readonly */
int weakRefs;
};

class XPathQuery
{
public:
~XPathQuery();
XPathQuery();
XPathQuery(const String&in, const String&inout arg1 = String ( ));
// Methods:
void Bind();
void Clear();
XPathResultSet Evaluate(const XMLElement&);
bool EvaluateToBool(const XMLElement&);
float EvaluateToFloat(const XMLElement&);
String EvaluateToString(const XMLElement&);
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
public:
~XPathResultSet();
XPathResultSet();
XPathResultSet(const XPathResultSet&in);

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
public:
// Methods:
void ApplyAttributes();
void DrawDebugGeometry(DebugRenderer, bool);
Variant GetAttribute(const String&) const;
ValueAnimation GetAttributeAnimation(const String&) const;
float GetAttributeAnimationSpeed(const String&) const;
float GetAttributeAnimationTime(const String&) const;
WrapMode GetAttributeAnimationWrapMode(const String&) const;
Variant GetAttributeDefault(const String&) const;
bool GetInterceptNetworkUpdate(const String&) const;
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
bool IsInView(Camera) const;
bool Load(File);
bool Load(VectorBuffer&);
bool LoadJSON(const JSONValue&);
bool LoadXML(const XMLElement&);
void MarkNetworkUpdate() const;
void Remove();
void RemoveAttributeAnimation(const String&);
void RemoveInstanceDefault();
void RemoveObjectAnimation();
void ResetToDefault();
bool Save(File) const;
bool Save(VectorBuffer&) const;
bool SaveJSON(JSONValue&) const;
bool SaveXML(XMLElement&) const;
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetAnimationTime(float);
bool SetAttribute(const String&, const Variant&);
void SetAttributeAnimation(const String&, ValueAnimation, WrapMode = WM_LOOP, float = 1.0f);
void SetAttributeAnimationSpeed(const String&, float);
void SetAttributeAnimationTime(const String&, float);
void SetAttributeAnimationWrapMode(const String&, WrapMode);
void SetInterceptNetworkUpdate(const String&, bool);

// Properties:
Color ambientColor;
/* readonly */
Color ambientEndColor;
bool ambientGradient;
/* readonly */
Color ambientStartColor;
bool animationEnabled;
/* readonly */
Array<Variant> attributeDefaults;
/* readonly */
Array<AttributeInfo> attributeInfos;
Array<Variant> attributes;
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
ObjectAnimation objectAnimation;
bool occludee;
bool occluder;
bool override;
int priority;
/* readonly */
int refs;
/* readonly */
bool replicated;
float shadowDistance;
uint shadowMask;
bool temporary;
/* readonly */
StringHash type;
/* readonly */
String typeName;
uint viewMask;
/* readonly */
int weakRefs;
/* readonly */
BoundingBox worldBoundingBox;
uint zoneMask;
Texture zoneTexture;
};

// Enumerations

enum AnimationBlendMode
{
ABM_LERP,
ABM_ADDITIVE,
};

enum AnimationChannel
{
CHANNEL_POSITION,
CHANNEL_ROTATION,
CHANNEL_SCALE,
};

enum AttributeMode
{
AM_FILE,
AM_NET,
AM_DEFAULT,
AM_LATESTDATA,
AM_NOEDIT,
AM_NODEID,
AM_COMPONENTID,
AM_NODEIDVECTOR,
AM_FILEREADONLY,
};

enum AutoRemoveMode
{
REMOVE_DISABLED,
REMOVE_COMPONENT,
REMOVE_NODE,
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
BLEND_SUBTRACT,
BLEND_SUBTRACTALPHA,
};

enum BodyType2D
{
BT_STATIC,
BT_KINEMATIC,
BT_DYNAMIC,
};

enum ClearTarget
{
CLEAR_COLOR,
CLEAR_DEPTH,
CLEAR_STENCIL,
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

enum CompressedFormat
{
CF_NONE,
CF_RGBA,
CF_DXT1,
CF_DXT3,
CF_DXT5,
CF_ETC1,
CF_PVRTC_RGB_2BPP,
CF_PVRTC_RGBA_2BPP,
CF_PVRTC_RGB_4BPP,
CF_PVRTC_RGBA_4BPP,
};

enum ConstraintType
{
CONSTRAINT_POINT,
CONSTRAINT_HINGE,
CONSTRAINT_SLIDER,
CONSTRAINT_CONETWIST,
};

enum ControllerAxis
{
CONTROLLER_AXIS_LEFTX,
CONTROLLER_AXIS_LEFTY,
CONTROLLER_AXIS_RIGHTX,
CONTROLLER_AXIS_RIGHTY,
CONTROLLER_AXIS_TRIGGERLEFT,
CONTROLLER_AXIS_TRIGGERRIGHT,
};

enum ControllerButton
{
CONTROLLER_BUTTON_A,
CONTROLLER_BUTTON_B,
CONTROLLER_BUTTON_X,
CONTROLLER_BUTTON_Y,
CONTROLLER_BUTTON_BACK,
CONTROLLER_BUTTON_GUIDE,
CONTROLLER_BUTTON_START,
CONTROLLER_BUTTON_LEFTSTICK,
CONTROLLER_BUTTON_RIGHTSTICK,
CONTROLLER_BUTTON_LEFTSHOULDER,
CONTROLLER_BUTTON_RIGHTSHOULDER,
CONTROLLER_BUTTON_DPAD_UP,
CONTROLLER_BUTTON_DPAD_DOWN,
CONTROLLER_BUTTON_DPAD_LEFT,
CONTROLLER_BUTTON_DPAD_RIGHT,
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

enum CrowdAgentRequestedTarget
{
CA_REQUESTEDTARGET_NONE,
CA_REQUESTEDTARGET_POSITION,
CA_REQUESTEDTARGET_VELOCITY,
};

enum CrowdAgentState
{
CA_STATE_INVALID,
CA_STATE_WALKING,
CA_STATE_OFFMESH,
};

enum CrowdAgentTargetState
{
CA_TARGET_NONE,
CA_TARGET_FAILED,
CA_TARGET_VALID,
CA_TARGET_REQUESTING,
CA_TARGET_WAITINGFORQUEUE,
CA_TARGET_WAITINGFORPATH,
CA_TARGET_VELOCITY,
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
CS_IBEAM,
CS_CROSS,
CS_RESIZEVERTICAL,
CS_RESIZEDIAGONAL_TOPRIGHT,
CS_RESIZEHORIZONTAL,
CS_RESIZEDIAGONAL_TOPLEFT,
CS_RESIZE_ALL,
CS_ACCEPTDROP,
CS_REJECTDROP,
CS_BUSY,
CS_BUSY_ARROW,
};

enum DBAPI
{
DBAPI_SQLITE,
DBAPI_ODBC,
};

enum DragAndDropMode
{
DD_DISABLED,
DD_SOURCE,
DD_TARGET,
DD_SOURCE_AND_TARGET,
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
EMITTER_SPHEREVOLUME,
EMITTER_CYLINDER,
EMITTER_RING,
};

enum EmitterType2D
{
EMITTER_TYPE_GRAVITY,
EMITTER_TYPE_RADIAL,
};

enum FaceCameraMode
{
FC_NONE,
FC_ROTATE_XYZ,
FC_ROTATE_Y,
FC_LOOKAT_XYZ,
FC_LOOKAT_Y,
FC_LOOKAT_MIXED,
FC_DIRECTION,
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

enum FontHintLevel
{
FONT_HINT_LEVEL_NONE,
FONT_HINT_LEVEL_LIGHT,
FONT_HINT_LEVEL_NORMAL,
};

enum FontType
{
FONT_NONE,
FONT_FREETYPE,
FONT_BITMAP,
};

enum HatPosition
{
HAT_CENTER,
HAT_UP,
HAT_RIGHT,
HAT_DOWN,
HAT_LEFT,
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
HA_CUSTOM,
};

enum HttpRequestState
{
HTTP_INITIALIZING,
HTTP_ERROR,
HTTP_OPEN,
HTTP_CLOSED,
};

enum IKAlgorithm
{
ONE_BONE,
TWO_BONE,
FABRIK,
};

enum InterpMethod
{
IM_NONE,
IM_LINEAR,
IM_SPLINE,
};

enum InterpolationMode
{
BEZIER_CURVE,
CATMULL_ROM_CURVE,
LINEAR_CURVE,
CATMULL_ROM_FULL_CURVE,
};

enum Intersection
{
OUTSIDE,
INTERSECTS,
INSIDE,
};

enum JSONNumberType
{
JSONNT_NAN,
JSONNT_INT,
JSONNT_UINT,
JSONNT_FLOAT_DOUBLE,
};

enum JSONValueType
{
JSON_NULL,
JSON_BOOL,
JSON_NUMBER,
JSON_STRING,
JSON_ARRAY,
JSON_OBJECT,
};

enum Key
{
KEY_UNKNOWN,
KEY_A,
KEY_B,
KEY_C,
KEY_D,
KEY_E,
KEY_F,
KEY_G,
KEY_H,
KEY_I,
KEY_J,
KEY_K,
KEY_L,
KEY_M,
KEY_N,
KEY_O,
KEY_P,
KEY_Q,
KEY_R,
KEY_S,
KEY_T,
KEY_U,
KEY_V,
KEY_W,
KEY_X,
KEY_Y,
KEY_Z,
KEY_0,
KEY_1,
KEY_2,
KEY_3,
KEY_4,
KEY_5,
KEY_6,
KEY_7,
KEY_8,
KEY_9,
KEY_BACKSPACE,
KEY_TAB,
KEY_RETURN,
KEY_RETURN2,
KEY_KP_ENTER,
KEY_SHIFT,
KEY_CTRL,
KEY_ALT,
KEY_GUI,
KEY_PAUSE,
KEY_CAPSLOCK,
KEY_ESCAPE,
KEY_SPACE,
KEY_PAGEUP,
KEY_PAGEDOWN,
KEY_END,
KEY_HOME,
KEY_LEFT,
KEY_UP,
KEY_RIGHT,
KEY_DOWN,
KEY_SELECT,
KEY_PRINTSCREEN,
KEY_INSERT,
KEY_DELETE,
KEY_LGUI,
KEY_RGUI,
KEY_APPLICATION,
KEY_KP_0,
KEY_KP_1,
KEY_KP_2,
KEY_KP_3,
KEY_KP_4,
KEY_KP_5,
KEY_KP_6,
KEY_KP_7,
KEY_KP_8,
KEY_KP_9,
KEY_KP_MULTIPLY,
KEY_KP_PLUS,
KEY_KP_MINUS,
KEY_KP_PERIOD,
KEY_KP_DIVIDE,
KEY_F1,
KEY_F2,
KEY_F3,
KEY_F4,
KEY_F5,
KEY_F6,
KEY_F7,
KEY_F8,
KEY_F9,
KEY_F10,
KEY_F11,
KEY_F12,
KEY_F13,
KEY_F14,
KEY_F15,
KEY_F16,
KEY_F17,
KEY_F18,
KEY_F19,
KEY_F20,
KEY_F21,
KEY_F22,
KEY_F23,
KEY_F24,
KEY_NUMLOCKCLEAR,
KEY_SCROLLLOCK,
KEY_LSHIFT,
KEY_RSHIFT,
KEY_LCTRL,
KEY_RCTRL,
KEY_LALT,
KEY_RALT,
KEY_AC_BACK,
KEY_AC_BOOKMARKS,
KEY_AC_FORWARD,
KEY_AC_HOME,
KEY_AC_REFRESH,
KEY_AC_SEARCH,
KEY_AC_STOP,
KEY_AGAIN,
KEY_ALTERASE,
KEY_AMPERSAND,
KEY_ASTERISK,
KEY_AT,
KEY_AUDIOMUTE,
KEY_AUDIONEXT,
KEY_AUDIOPLAY,
KEY_AUDIOPREV,
KEY_AUDIOSTOP,
KEY_BACKQUOTE,
KEY_BACKSLASH,
KEY_BRIGHTNESSDOWN,
KEY_BRIGHTNESSUP,
KEY_CALCULATOR,
KEY_CANCEL,
KEY_CARET,
KEY_CLEAR,
KEY_CLEARAGAIN,
KEY_COLON,
KEY_COMMA,
KEY_COMPUTER,
KEY_COPY,
KEY_CRSEL,
KEY_CURRENCYSUBUNIT,
KEY_CURRENCYUNIT,
KEY_CUT,
KEY_DECIMALSEPARATOR,
KEY_DISPLAYSWITCH,
KEY_DOLLAR,
KEY_EJECT,
KEY_EQUALS,
KEY_EXCLAIM,
KEY_EXSEL,
KEY_FIND,
KEY_GREATER,
KEY_HASH,
KEY_HELP,
KEY_KBDILLUMDOWN,
KEY_KBDILLUMTOGGLE,
KEY_KBDILLUMUP,
KEY_KP_00,
KEY_KP_000,
KEY_KP_A,
KEY_KP_AMPERSAND,
KEY_KP_AT,
KEY_KP_B,
KEY_KP_BACKSPACE,
KEY_KP_BINARY,
KEY_KP_C,
KEY_KP_CLEAR,
KEY_KP_CLEARENTRY,
KEY_KP_COLON,
KEY_KP_COMMA,
KEY_KP_D,
KEY_KP_DBLAMPERSAND,
KEY_KP_DBLVERTICALBAR,
KEY_KP_DECIMAL,
KEY_KP_E,
KEY_KP_EQUALS,
KEY_KP_EQUALSAS400,
KEY_KP_EXCLAM,
KEY_KP_F,
KEY_KP_GREATER,
KEY_KP_HASH,
KEY_KP_HEXADECIMAL,
KEY_KP_LEFTBRACE,
KEY_KP_LEFTPAREN,
KEY_KP_LESS,
KEY_KP_MEMADD,
KEY_KP_MEMCLEAR,
KEY_KP_MEMDIVIDE,
KEY_KP_MEMMULTIPLY,
KEY_KP_MEMRECALL,
KEY_KP_MEMSTORE,
KEY_KP_MEMSUBTRACT,
KEY_KP_OCTAL,
KEY_KP_PERCENT,
KEY_KP_PLUSMINUS,
KEY_KP_POWER,
KEY_KP_RIGHTBRACE,
KEY_KP_RIGHTPAREN,
KEY_KP_SPACE,
KEY_KP_TAB,
KEY_KP_VERTICALBAR,
KEY_KP_XOR,
KEY_LEFTBRACKET,
KEY_LEFTPAREN,
KEY_LESS,
KEY_MAIL,
KEY_MEDIASELECT,
KEY_MENU,
KEY_MINUS,
KEY_MODE,
KEY_MUTE,
KEY_OPER,
KEY_OUT,
KEY_PASTE,
KEY_PERCENT,
KEY_PERIOD,
KEY_PLUS,
KEY_POWER,
KEY_PRIOR,
KEY_QUESTION,
KEY_QUOTE,
KEY_QUOTEDBL,
KEY_RIGHTBRACKET,
KEY_RIGHTPAREN,
KEY_SEMICOLON,
KEY_SEPARATOR,
KEY_SLASH,
KEY_SLEEP,
KEY_STOP,
KEY_SYSREQ,
KEY_THOUSANDSSEPARATOR,
KEY_UNDERSCORE,
KEY_UNDO,
KEY_VOLUMEDOWN,
KEY_VOLUMEUP,
KEY_WWW,
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

enum LoadMode
{
LOAD_RESOURCES_ONLY,
LOAD_SCENE,
LOAD_SCENE_AND_RESOURCES,
};

enum LoopMode2D
{
LM_DEFAULT,
LM_FORCE_LOOPED,
LM_FORCE_CLAMPED,
};

enum MaterialQuality
{
QUALITY_LOW,
QUALITY_MEDIUM,
QUALITY_HIGH,
QUALITY_MAX,
};

enum MouseButton
{
MOUSEB_LEFT,
MOUSEB_MIDDLE,
MOUSEB_RIGHT,
};

enum MouseMode
{
MM_ABSOLUTE,
MM_RELATIVE,
MM_WRAP,
MM_FREE,
};

enum NavigationPushiness
{
NAVIGATIONPUSHINESS_LOW,
NAVIGATIONPUSHINESS_MEDIUM,
NAVIGATIONPUSHINESS_HIGH,
NAVIGATIONPUSHINESS_NONE,
};

enum NavigationQuality
{
NAVIGATIONQUALITY_LOW,
NAVIGATIONQUALITY_MEDIUM,
NAVIGATIONQUALITY_HIGH,
};

enum NavmeshPartitionType
{
NAVMESH_PARTITION_WATERSHED,
NAVMESH_PARTITION_MONOTONE,
};

enum Orientation
{
O_HORIZONTAL,
O_VERTICAL,
};

enum Orientation2D
{
O_ORTHOGONAL,
O_ISOMETRIC,
O_STAGGERED,
O_HEXAGONAL,
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
POINT_LIST,
TRIANGLE_STRIP,
LINE_STRIP,
TRIANGLE_FAN,
};

enum Qualifier
{
QUAL_SHIFT,
QUAL_CTRL,
QUAL_ALT,
QUAL_ANY,
};

enum RayQueryLevel
{
RAY_AABB,
RAY_OBB,
RAY_TRIANGLE,
RAY_TRIANGLE_UV,
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
CMD_RENDERUI,
CMD_SENDEVENT,
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
SIZE_VIEWPORTDIVISOR,
SIZE_VIEWPORTMULTIPLIER,
};

enum Scancode
{
SCANCODE_UNKNOWN,
SCANCODE_CTRL,
SCANCODE_SHIFT,
SCANCODE_ALT,
SCANCODE_GUI,
SCANCODE_A,
SCANCODE_B,
SCANCODE_C,
SCANCODE_D,
SCANCODE_E,
SCANCODE_F,
SCANCODE_G,
SCANCODE_H,
SCANCODE_I,
SCANCODE_J,
SCANCODE_K,
SCANCODE_L,
SCANCODE_M,
SCANCODE_N,
SCANCODE_O,
SCANCODE_P,
SCANCODE_Q,
SCANCODE_R,
SCANCODE_S,
SCANCODE_T,
SCANCODE_U,
SCANCODE_V,
SCANCODE_W,
SCANCODE_X,
SCANCODE_Y,
SCANCODE_Z,
SCANCODE_1,
SCANCODE_2,
SCANCODE_3,
SCANCODE_4,
SCANCODE_5,
SCANCODE_6,
SCANCODE_7,
SCANCODE_8,
SCANCODE_9,
SCANCODE_0,
SCANCODE_RETURN,
SCANCODE_ESCAPE,
SCANCODE_BACKSPACE,
SCANCODE_TAB,
SCANCODE_SPACE,
SCANCODE_MINUS,
SCANCODE_EQUALS,
SCANCODE_LEFTBRACKET,
SCANCODE_RIGHTBRACKET,
SCANCODE_BACKSLASH,
SCANCODE_NONUSHASH,
SCANCODE_SEMICOLON,
SCANCODE_APOSTROPHE,
SCANCODE_GRAVE,
SCANCODE_COMMA,
SCANCODE_PERIOD,
SCANCODE_SLASH,
SCANCODE_CAPSLOCK,
SCANCODE_F1,
SCANCODE_F2,
SCANCODE_F3,
SCANCODE_F4,
SCANCODE_F5,
SCANCODE_F6,
SCANCODE_F7,
SCANCODE_F8,
SCANCODE_F9,
SCANCODE_F10,
SCANCODE_F11,
SCANCODE_F12,
SCANCODE_PRINTSCREEN,
SCANCODE_SCROLLLOCK,
SCANCODE_PAUSE,
SCANCODE_INSERT,
SCANCODE_HOME,
SCANCODE_PAGEUP,
SCANCODE_DELETE,
SCANCODE_END,
SCANCODE_PAGEDOWN,
SCANCODE_RIGHT,
SCANCODE_LEFT,
SCANCODE_DOWN,
SCANCODE_UP,
SCANCODE_NUMLOCKCLEAR,
SCANCODE_KP_DIVIDE,
SCANCODE_KP_MULTIPLY,
SCANCODE_KP_MINUS,
SCANCODE_KP_PLUS,
SCANCODE_KP_ENTER,
SCANCODE_KP_1,
SCANCODE_KP_2,
SCANCODE_KP_3,
SCANCODE_KP_4,
SCANCODE_KP_5,
SCANCODE_KP_6,
SCANCODE_KP_7,
SCANCODE_KP_8,
SCANCODE_KP_9,
SCANCODE_KP_0,
SCANCODE_KP_PERIOD,
SCANCODE_NONUSBACKSLASH,
SCANCODE_APPLICATION,
SCANCODE_POWER,
SCANCODE_KP_EQUALS,
SCANCODE_F13,
SCANCODE_F14,
SCANCODE_F15,
SCANCODE_F16,
SCANCODE_F17,
SCANCODE_F18,
SCANCODE_F19,
SCANCODE_F20,
SCANCODE_F21,
SCANCODE_F22,
SCANCODE_F23,
SCANCODE_F24,
SCANCODE_EXECUTE,
SCANCODE_HELP,
SCANCODE_MENU,
SCANCODE_SELECT,
SCANCODE_STOP,
SCANCODE_AGAIN,
SCANCODE_UNDO,
SCANCODE_CUT,
SCANCODE_COPY,
SCANCODE_PASTE,
SCANCODE_FIND,
SCANCODE_MUTE,
SCANCODE_VOLUMEUP,
SCANCODE_VOLUMEDOWN,
SCANCODE_KP_COMMA,
SCANCODE_KP_EQUALSAS400,
SCANCODE_INTERNATIONAL1,
SCANCODE_INTERNATIONAL2,
SCANCODE_INTERNATIONAL3,
SCANCODE_INTERNATIONAL4,
SCANCODE_INTERNATIONAL5,
SCANCODE_INTERNATIONAL6,
SCANCODE_INTERNATIONAL7,
SCANCODE_INTERNATIONAL8,
SCANCODE_INTERNATIONAL9,
SCANCODE_LANG1,
SCANCODE_LANG2,
SCANCODE_LANG3,
SCANCODE_LANG4,
SCANCODE_LANG5,
SCANCODE_LANG6,
SCANCODE_LANG7,
SCANCODE_LANG8,
SCANCODE_LANG9,
SCANCODE_ALTERASE,
SCANCODE_SYSREQ,
SCANCODE_CANCEL,
SCANCODE_CLEAR,
SCANCODE_PRIOR,
SCANCODE_RETURN2,
SCANCODE_SEPARATOR,
SCANCODE_OUT,
SCANCODE_OPER,
SCANCODE_CLEARAGAIN,
SCANCODE_CRSEL,
SCANCODE_EXSEL,
SCANCODE_KP_00,
SCANCODE_KP_000,
SCANCODE_THOUSANDSSEPARATOR,
SCANCODE_DECIMALSEPARATOR,
SCANCODE_CURRENCYUNIT,
SCANCODE_CURRENCYSUBUNIT,
SCANCODE_KP_LEFTPAREN,
SCANCODE_KP_RIGHTPAREN,
SCANCODE_KP_LEFTBRACE,
SCANCODE_KP_RIGHTBRACE,
SCANCODE_KP_TAB,
SCANCODE_KP_BACKSPACE,
SCANCODE_KP_A,
SCANCODE_KP_B,
SCANCODE_KP_C,
SCANCODE_KP_D,
SCANCODE_KP_E,
SCANCODE_KP_F,
SCANCODE_KP_XOR,
SCANCODE_KP_POWER,
SCANCODE_KP_PERCENT,
SCANCODE_KP_LESS,
SCANCODE_KP_GREATER,
SCANCODE_KP_AMPERSAND,
SCANCODE_KP_DBLAMPERSAND,
SCANCODE_KP_VERTICALBAR,
SCANCODE_KP_DBLVERTICALBAR,
SCANCODE_KP_COLON,
SCANCODE_KP_HASH,
SCANCODE_KP_SPACE,
SCANCODE_KP_AT,
SCANCODE_KP_EXCLAM,
SCANCODE_KP_MEMSTORE,
SCANCODE_KP_MEMRECALL,
SCANCODE_KP_MEMCLEAR,
SCANCODE_KP_MEMADD,
SCANCODE_KP_MEMSUBTRACT,
SCANCODE_KP_MEMMULTIPLY,
SCANCODE_KP_MEMDIVIDE,
SCANCODE_KP_PLUSMINUS,
SCANCODE_KP_CLEAR,
SCANCODE_KP_CLEARENTRY,
SCANCODE_KP_BINARY,
SCANCODE_KP_OCTAL,
SCANCODE_KP_DECIMAL,
SCANCODE_KP_HEXADECIMAL,
SCANCODE_LCTRL,
SCANCODE_LSHIFT,
SCANCODE_LALT,
SCANCODE_LGUI,
SCANCODE_RCTRL,
SCANCODE_RSHIFT,
SCANCODE_RALT,
SCANCODE_RGUI,
SCANCODE_MODE,
SCANCODE_AUDIONEXT,
SCANCODE_AUDIOPREV,
SCANCODE_AUDIOSTOP,
SCANCODE_AUDIOPLAY,
SCANCODE_AUDIOMUTE,
SCANCODE_MEDIASELECT,
SCANCODE_WWW,
SCANCODE_MAIL,
SCANCODE_CALCULATOR,
SCANCODE_COMPUTER,
SCANCODE_AC_SEARCH,
SCANCODE_AC_HOME,
SCANCODE_AC_BACK,
SCANCODE_AC_FORWARD,
SCANCODE_AC_STOP,
SCANCODE_AC_REFRESH,
SCANCODE_AC_BOOKMARKS,
SCANCODE_BRIGHTNESSDOWN,
SCANCODE_BRIGHTNESSUP,
SCANCODE_DISPLAYSWITCH,
SCANCODE_KBDILLUMTOGGLE,
SCANCODE_KBDILLUMDOWN,
SCANCODE_KBDILLUMUP,
SCANCODE_EJECT,
SCANCODE_SLEEP,
SCANCODE_APP1,
SCANCODE_APP2,
};

enum ShadowQuality
{
SHADOWQUALITY_SIMPLE_16BIT,
SHADOWQUALITY_SIMPLE_24BIT,
SHADOWQUALITY_PCF_16BIT,
SHADOWQUALITY_PCF_24BIT,
SHADOWQUALITY_VSM,
SHADOWQUALITY_BLUR_VSM,
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
FILTER_NEAREST_ANISOTROPIC,
FILTER_DEFAULT,
};

enum TextureUnit
{
TU_DIFFUSE,
TU_ALBEDOBUFFER,
TU_NORMAL,
TU_NORMALBUFFER,
TU_SPECULAR,
TU_EMISSIVE,
TU_ENVIRONMENT,
TU_LIGHTRAMP,
TU_LIGHTSHAPE,
TU_SHADOWMAP,
TU_CUSTOM1,
TU_CUSTOM2,
TU_VOLUMEMAP,
TU_FACESELECT,
TU_INDIRECTION,
TU_DEPTHBUFFER,
TU_LIGHTBUFFER,
TU_ZONE,
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

enum TileMapLayerType2D
{
LT_TILE_LAYER,
LT_OBJECT_GROUP,
LT_IMAGE_LAYER,
LT_INVALID,
};

enum TileObjectType2D
{
OT_RECTANGLE,
OT_ELLIPSE,
OT_POLYGON,
OT_POLYLINE,
OT_TILE,
OT_INVALID,
};

enum TrailType
{
TT_FACE_CAMERA,
TT_BONE,
};

enum TransformSpace
{
TS_LOCAL,
TS_PARENT,
TS_WORLD,
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
VAR_INTVECTOR3,
VAR_PTR,
VAR_MATRIX3,
VAR_MATRIX3X4,
VAR_MATRIX4,
VAR_DOUBLE,
VAR_STRINGVECTOR,
VAR_RECT,
};

enum VertexElementSemantic
{
SEM_POSITION,
SEM_NORMAL,
SEM_BINORMAL,
SEM_TANGENT,
SEM_TEXCOORD,
SEM_COLOR,
SEM_BLENDWEIGHTS,
SEM_BLENDINDICES,
SEM_OBJECTINDEX,
MAX_VERTEX_ELEMENT_SEMANTICS,
};

enum VertexElementType
{
TYPE_INT,
TYPE_FLOAT,
TYPE_VECTOR2,
TYPE_VECTOR3,
TYPE_VECTOR4,
TYPE_UBYTE4,
TYPE_UBYTE4_NORM,
MAX_VERTEX_ELEMENT_TYPES,
};

enum VertexMask
{
MASK_NONE,
MASK_POSITION,
MASK_NORMAL,
MASK_COLOR,
MASK_TEXCOORD1,
MASK_TEXCOORD2,
MASK_CUBETEXCOORD1,
MASK_CUBETEXCOORD2,
MASK_TANGENT,
MASK_BLENDWEIGHTS,
MASK_BLENDINDICES,
MASK_INSTANCEMATRIX1,
MASK_INSTANCEMATRIX2,
MASK_INSTANCEMATRIX3,
MASK_OBJECTINDEX,
};

enum VerticalAlignment
{
VA_TOP,
VA_CENTER,
VA_BOTTOM,
VA_CUSTOM,
};

enum ViewOverride
{
VO_NONE,
VO_LOW_MATERIAL_QUALITY,
VO_DISABLE_SHADOWS,
VO_DISABLE_OCCLUSION,
};

enum WrapMode
{
WM_LOOP,
WM_ONCE,
WM_CLAMP,
};

// Global functions
float Abs(float);
float Acos(float);
String AddTrailingSlash(const String&);
float Asin(float);
float Atan(float);
float Atan2(float, float);
float Ceil(float);
int CeilToInt(float);
float Clamp(float, float, float);
int Clamp(int, int, int);
void ClearDelayedExecute(const String& = String ( ));
VectorBuffer CompressVectorBuffer(VectorBuffer&);
float Cos(float);
uint CountSetBits(uint);
Object CreateObject(const String&);
VectorBuffer DecompressVectorBuffer(VectorBuffer&);
void DelayedExecute(float, bool, const String&, const Array<Variant> = null);
bool Equals(float, float);
void ErrorDialog(const String&, const String&);
float Floor(float);
int FloorToInt(float);
float Fract(float);
uint GetAlphaFormat();
Array<String> GetArguments();
String GetConsoleInput();
uint GetDepthStencilFormat();
Object GetEventSender();
String GetExtension(const String&, bool = true);
String GetFileName(const String&);
String GetFileNameAndExtension(const String&, bool = false);
String GetFileSizeString(uint64);
uint GetFloat16Format();
uint GetFloat32Format();
uint GetFormat(const String&);
Variant GetGlobalVar(const String&);
String GetHostName();
String GetInternalPath(const String&);
uint GetLinearDepthFormat();
String GetLoginName();
uint GetLuminanceAlphaFormat();
uint GetLuminanceFormat();
uint GetMaxBones();
String GetMiniDumpDir();
uint GetNumLogicalCPUs();
uint GetNumPhysicalCPUs();
String GetOSVersion();
Array<AttributeInfo> GetObjectAttributeInfos(const String&);
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
uint GetReadableDepthFormat();
String GetTextureUnitName(TextureUnit);
uint64 GetTotalMemory();
VariantType GetVariantTypeFromName(const String&);
String GetVariantTypeName(VariantType);
bool HasSubscribedToEvent(Object, const String&);
bool HasSubscribedToEvent(const String&);
float InverseLerp(float, float, float);
bool IsAbsolutePath(const String&);
bool IsAlpha(uint);
bool IsDigit(uint);
bool IsNaN(double);
bool IsNaN(float);
bool IsPowerOfTwo(uint);
bool IsReplicatedID(uint);
String Join(Array<String>&, const String&);
float Lerp(float, float, float);
float Ln(float);
uint LogBaseTwo(uint);
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
void Print(int64, bool = false);
void Print(uint, bool = false);
void Print(uint64, bool = false);
void PrintCallStack(bool = false);
float Random();
float Random(float);
float Random(float, float);
int RandomInt();
int RandomInt(int);
int RandomInt(int, int);
float RandomNormal(float, float);
void RegisterEventName(const String&);
void Remove();
String RemoveTrailingSlash(const String&);
String ReplaceExtension(const String&, const String&);
float Round(float);
int RoundToInt(float);
uint SDBMHash(uint, uint8);
void SendEvent(const String&, VariantMap& = VariantMap ( ));
void SetGlobalVar(const String&, Variant&);
void SetMiniDumpDir(const String&);
void SetRandomSeed(uint);
float Sign(float);
float Sin(float);
float SmoothStep(float, float, float);
float Sqrt(float);
float StableRandom(const Vector2&);
float StableRandom(const Vector3&);
float StableRandom(float);
const String& GetTypeName(StringHash);
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
Vector2 VectorCeil(const Vector2&);
Vector3 VectorCeil(const Vector3&);
Vector4 VectorCeil(const Vector4&);
IntVector2 VectorCeilToInt(const Vector2&);
IntVector3 VectorCeilToInt(const Vector3&);
Vector2 VectorFloor(const Vector2&);
Vector3 VectorFloor(const Vector3&);
Vector4 VectorFloor(const Vector4&);
IntVector2 VectorFloorToInt(const Vector2&);
IntVector3 VectorFloorToInt(const Vector3&);
Vector2 VectorLerp(const Vector2&, const Vector2&, const Vector2&);
Vector3 VectorLerp(const Vector3&, const Vector3&, const Vector3&);
Vector4 VectorLerp(const Vector4&, const Vector4&, const Vector4&);
IntVector2 VectorMax(const IntVector2&, const IntVector2&);
IntVector3 VectorMax(const IntVector3&, const IntVector3&);
Vector2 VectorMax(const Vector2&, const Vector2&);
Vector3 VectorMax(const Vector3&, const Vector3&);
Vector4 VectorMax(const Vector4&, const Vector4&);
IntVector2 VectorMin(const IntVector2&, const IntVector2&);
IntVector3 VectorMin(const IntVector3&, const IntVector3&);
Vector2 VectorMin(const Vector2&, const Vector2&);
Vector3 VectorMin(const Vector3&, const Vector3&);
Vector4 VectorMin(const Vector4&, const Vector4&);
Vector2 VectorRound(const Vector2&);
Vector3 VectorRound(const Vector3&);
Vector4 VectorRound(const Vector4&);
IntVector2 VectorRoundToInt(const Vector2&);
IntVector3 VectorRoundToInt(const Vector3&);
bool WriteDrawablesToOBJ(Array<Drawable>, File, bool, bool, bool = false);

// Global properties
DBAPI DBAPI;
Audio audio;
ResourceCache cache;
Console console;
Database database;
DebugHud debugHud;
DebugRenderer debugRenderer;
Engine engine;
FileSystem fileSystem;
VariantMap globalVars;
Graphics graphics;
Input input;
Localization localization;
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
Color BLACK;
Color BLUE;
Color CYAN;
uint DEBUGHUD_SHOW_ALL;
uint DEBUGHUD_SHOW_EVENTPROFILER;
uint DEBUGHUD_SHOW_MEMORY;
uint DEBUGHUD_SHOW_MODE;
uint DEBUGHUD_SHOW_NONE;
uint DEBUGHUD_SHOW_PROFILER;
uint DEBUGHUD_SHOW_STATS;
uint DEFAULT_LIGHTMASK;
uint DEFAULT_VIEWMASK;
uint DRAWABLE_ANY;
uint DRAWABLE_GEOMETRY;
uint DRAWABLE_GEOMETRY2D;
uint DRAWABLE_LIGHT;
uint DRAWABLE_ZONE;
uint FIRST_LOCAL_ID;
uint FIRST_REPLICATED_ID;
uint FLIP_ALL;
uint FLIP_DIAGONAL;
uint FLIP_HORIZONTAL;
uint FLIP_RESERVED;
uint FLIP_VERTICAL;
Color GRAY;
Color GREEN;
uint LAST_LOCAL_ID;
uint LAST_REPLICATED_ID;
int LOG_DEBUG;
int LOG_ERROR;
int LOG_INFO;
int LOG_NONE;
int LOG_TRACE;
int LOG_WARNING;
Color MAGENTA;
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
uint NPOS;
float PIXEL_SIZE;
Color RED;
uint SCAN_DIRS;
uint SCAN_FILES;
uint SCAN_HIDDEN;
String SOUND_AMBIENT;
String SOUND_EFFECT;
String SOUND_MASTER;
String SOUND_MUSIC;
String SOUND_VOICE;
Color TRANSPARENT_BLACK;
Color WHITE;
Color YELLOW;
