// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Generated_Members.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// struct AllocatorBlock | File: ../Container/Allocator.h
static void Register_AllocatorBlock(asIScriptEngine* engine)
{
    // AllocatorBlock::~AllocatorBlock() | Implicitly-declared
    engine->RegisterObjectBehaviour("AllocatorBlock", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(AllocatorBlock), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_AllocatorBlock<AllocatorBlock>(engine, "AllocatorBlock");
    CollectMembers_AllocatorBlock(members);
    RegisterMembers(engine, "AllocatorBlock", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AllocatorBlock
        REGISTER_CLASS_MANUAL_PART_AllocatorBlock();
    #endif

    // AllocatorBlock& AllocatorBlock::operator =(const AllocatorBlock&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AllocatorBlock>(engine, "AllocatorBlock");
}

// struct AllocatorNode | File: ../Container/Allocator.h
static void Register_AllocatorNode(asIScriptEngine* engine)
{
    // AllocatorNode::~AllocatorNode() | Implicitly-declared
    engine->RegisterObjectBehaviour("AllocatorNode", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(AllocatorNode), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_AllocatorNode<AllocatorNode>(engine, "AllocatorNode");
    CollectMembers_AllocatorNode(members);
    RegisterMembers(engine, "AllocatorNode", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AllocatorNode
        REGISTER_CLASS_MANUAL_PART_AllocatorNode();
    #endif

    // AllocatorNode& AllocatorNode::operator =(const AllocatorNode&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AllocatorNode>(engine, "AllocatorNode");
}

// struct AnimationControl | File: ../Graphics/AnimationController.h
static void Register_AnimationControl(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("AnimationControl", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("AnimationControl", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);

    MemberCollection members;
    RegisterMembers_AnimationControl<AnimationControl>(engine, "AnimationControl");
    CollectMembers_AnimationControl(members);
    RegisterMembers(engine, "AnimationControl", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AnimationControl
        REGISTER_CLASS_MANUAL_PART_AnimationControl();
    #endif

    // AnimationControl& AnimationControl::operator =(const AnimationControl&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AnimationControl>(engine, "AnimationControl");
}

// struct AnimationKeyFrame | File: ../Graphics/Animation.h
static void Register_AnimationKeyFrame(asIScriptEngine* engine)
{
    // AnimationKeyFrame::~AnimationKeyFrame() | Implicitly-declared
    engine->RegisterObjectBehaviour("AnimationKeyFrame", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(AnimationKeyFrame), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_AnimationKeyFrame<AnimationKeyFrame>(engine, "AnimationKeyFrame");
    CollectMembers_AnimationKeyFrame(members);
    RegisterMembers(engine, "AnimationKeyFrame", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AnimationKeyFrame
        REGISTER_CLASS_MANUAL_PART_AnimationKeyFrame();
    #endif

    // AnimationKeyFrame& AnimationKeyFrame::operator =(const AnimationKeyFrame&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AnimationKeyFrame>(engine, "AnimationKeyFrame");
}

// struct AnimationStateTrack | File: ../Graphics/AnimationState.h
static void Register_AnimationStateTrack(asIScriptEngine* engine)
{
    // AnimationStateTrack::~AnimationStateTrack()
    engine->RegisterObjectBehaviour("AnimationStateTrack", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(AnimationStateTrack), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_AnimationStateTrack<AnimationStateTrack>(engine, "AnimationStateTrack");
    CollectMembers_AnimationStateTrack(members);
    RegisterMembers(engine, "AnimationStateTrack", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AnimationStateTrack
        REGISTER_CLASS_MANUAL_PART_AnimationStateTrack();
    #endif

    // AnimationStateTrack& AnimationStateTrack::operator =(const AnimationStateTrack&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AnimationStateTrack>(engine, "AnimationStateTrack");
}

// struct AnimationTrack | File: ../Graphics/Animation.h
static void Register_AnimationTrack(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("AnimationTrack", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("AnimationTrack", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);

    MemberCollection members;
    RegisterMembers_AnimationTrack<AnimationTrack>(engine, "AnimationTrack");
    CollectMembers_AnimationTrack(members);
    RegisterMembers(engine, "AnimationTrack", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AnimationTrack
        REGISTER_CLASS_MANUAL_PART_AnimationTrack();
    #endif

    // AnimationTrack& AnimationTrack::operator =(const AnimationTrack&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AnimationTrack>(engine, "AnimationTrack");
}

// struct AnimationTriggerPoint | File: ../Graphics/Animation.h
static void Register_AnimationTriggerPoint(asIScriptEngine* engine)
{
    // AnimationTriggerPoint::~AnimationTriggerPoint() | Implicitly-declared
    engine->RegisterObjectBehaviour("AnimationTriggerPoint", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(AnimationTriggerPoint), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_AnimationTriggerPoint<AnimationTriggerPoint>(engine, "AnimationTriggerPoint");
    CollectMembers_AnimationTriggerPoint(members);
    RegisterMembers(engine, "AnimationTriggerPoint", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AnimationTriggerPoint
        REGISTER_CLASS_MANUAL_PART_AnimationTriggerPoint();
    #endif

    // AnimationTriggerPoint& AnimationTriggerPoint::operator =(const AnimationTriggerPoint&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AnimationTriggerPoint>(engine, "AnimationTriggerPoint");
}

// AreaAllocator::AreaAllocator(int width, int height, bool fastMode = true)
static void AreaAllocator__AreaAllocator_int_int_bool(AreaAllocator* _ptr, int width, int height, bool fastMode)
{
    new(_ptr) AreaAllocator(width, height, fastMode);
}

// AreaAllocator::AreaAllocator(int width, int height, int maxWidth, int maxHeight, bool fastMode = true)
static void AreaAllocator__AreaAllocator_int_int_int_int_bool(AreaAllocator* _ptr, int width, int height, int maxWidth, int maxHeight, bool fastMode)
{
    new(_ptr) AreaAllocator(width, height, maxWidth, maxHeight, fastMode);
}

// class AreaAllocator | File: ../Math/AreaAllocator.h
static void Register_AreaAllocator(asIScriptEngine* engine)
{
    // AreaAllocator::AreaAllocator(int width, int height, bool fastMode = true)
    engine->RegisterObjectBehaviour("AreaAllocator", asBEHAVE_CONSTRUCT, "void f(int, int, bool = true)", AS_FUNCTION_OBJFIRST(AreaAllocator__AreaAllocator_int_int_bool), AS_CALL_CDECL_OBJFIRST);
    // AreaAllocator::AreaAllocator(int width, int height, int maxWidth, int maxHeight, bool fastMode = true)
    engine->RegisterObjectBehaviour("AreaAllocator", asBEHAVE_CONSTRUCT, "void f(int, int, int, int, bool = true)", AS_FUNCTION_OBJFIRST(AreaAllocator__AreaAllocator_int_int_int_int_bool), AS_CALL_CDECL_OBJFIRST);

    // AreaAllocator::~AreaAllocator() | Implicitly-declared
    engine->RegisterObjectBehaviour("AreaAllocator", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(AreaAllocator), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_AreaAllocator<AreaAllocator>(engine, "AreaAllocator");
    CollectMembers_AreaAllocator(members);
    RegisterMembers(engine, "AreaAllocator", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AreaAllocator
        REGISTER_CLASS_MANUAL_PART_AreaAllocator();
    #endif

    // AreaAllocator& AreaAllocator::operator =(const AreaAllocator&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AreaAllocator>(engine, "AreaAllocator");
}

// struct AsyncProgress | File: ../Scene/Scene.h
static void Register_AsyncProgress(asIScriptEngine* engine)
{
    // AsyncProgress::~AsyncProgress() | Implicitly-declared
    engine->RegisterObjectBehaviour("AsyncProgress", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(AsyncProgress), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_AsyncProgress<AsyncProgress>(engine, "AsyncProgress");
    CollectMembers_AsyncProgress(members);
    RegisterMembers(engine, "AsyncProgress", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AsyncProgress
        REGISTER_CLASS_MANUAL_PART_AsyncProgress();
    #endif

    // AsyncProgress& AsyncProgress::operator =(const AsyncProgress&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AsyncProgress>(engine, "AsyncProgress");
}

// struct AttributeInfo | File: ../Core/Attribute.h
static void Register_AttributeInfo(asIScriptEngine* engine)
{
    // AttributeInfo::AttributeInfo(VariantType type, const char* name, const SharedPtr<AttributeAccessor>& accessor, const char** enumNames, const Variant& defaultValue, AttributeModeFlags mode)
    // Error: type "const char*" can not automatically bind

    // AttributeInfo::~AttributeInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("AttributeInfo", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(AttributeInfo), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_AttributeInfo<AttributeInfo>(engine, "AttributeInfo");
    CollectMembers_AttributeInfo(members);
    RegisterMembers(engine, "AttributeInfo", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AttributeInfo
        REGISTER_CLASS_MANUAL_PART_AttributeInfo();
    #endif

    // AttributeInfo& AttributeInfo::operator =(const AttributeInfo&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AttributeInfo>(engine, "AttributeInfo");
}

// struct BackgroundLoadItem | File: ../Resource/BackgroundLoader.h
static void Register_BackgroundLoadItem(asIScriptEngine* engine)
{
    // BackgroundLoadItem::~BackgroundLoadItem() | Implicitly-declared
    engine->RegisterObjectBehaviour("BackgroundLoadItem", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(BackgroundLoadItem), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_BackgroundLoadItem<BackgroundLoadItem>(engine, "BackgroundLoadItem");
    CollectMembers_BackgroundLoadItem(members);
    RegisterMembers(engine, "BackgroundLoadItem", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_BackgroundLoadItem
        REGISTER_CLASS_MANUAL_PART_BackgroundLoadItem();
    #endif

    // BackgroundLoadItem& BackgroundLoadItem::operator =(const BackgroundLoadItem&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<BackgroundLoadItem>(engine, "BackgroundLoadItem");
}

// explicit Batch::Batch(const SourceBatch& rhs)
static void Batch__Batch_constspSourceBatchamp(Batch* _ptr, const SourceBatch& rhs)
{
    new(_ptr) Batch(rhs);
}

// struct Batch | File: ../Graphics/Batch.h
static void Register_Batch(asIScriptEngine* engine)
{
    // explicit Batch::Batch(const SourceBatch& rhs)
    engine->RegisterObjectBehaviour("Batch", asBEHAVE_CONSTRUCT, "void f(const SourceBatch&in)", AS_FUNCTION_OBJFIRST(Batch__Batch_constspSourceBatchamp), AS_CALL_CDECL_OBJFIRST);

    // Batch::~Batch() | Implicitly-declared
    engine->RegisterObjectBehaviour("Batch", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(Batch), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Batch<Batch>(engine, "Batch");
    CollectMembers_Batch(members);
    RegisterMembers(engine, "Batch", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Batch
        REGISTER_CLASS_MANUAL_PART_Batch();
    #endif

    // Batch& Batch::operator =(const Batch&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Batch>(engine, "Batch");
}

// explicit BatchGroupKey::BatchGroupKey(const Batch& batch)
static void BatchGroupKey__BatchGroupKey_constspBatchamp(BatchGroupKey* _ptr, const Batch& batch)
{
    new(_ptr) BatchGroupKey(batch);
}

// struct BatchGroupKey | File: ../Graphics/Batch.h
static void Register_BatchGroupKey(asIScriptEngine* engine)
{
    // explicit BatchGroupKey::BatchGroupKey(const Batch& batch)
    engine->RegisterObjectBehaviour("BatchGroupKey", asBEHAVE_CONSTRUCT, "void f(const Batch&in)", AS_FUNCTION_OBJFIRST(BatchGroupKey__BatchGroupKey_constspBatchamp), AS_CALL_CDECL_OBJFIRST);

    // BatchGroupKey::~BatchGroupKey() | Implicitly-declared
    engine->RegisterObjectBehaviour("BatchGroupKey", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(BatchGroupKey), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_BatchGroupKey<BatchGroupKey>(engine, "BatchGroupKey");
    CollectMembers_BatchGroupKey(members);
    RegisterMembers(engine, "BatchGroupKey", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_BatchGroupKey
        REGISTER_CLASS_MANUAL_PART_BatchGroupKey();
    #endif

    // BatchGroupKey& BatchGroupKey::operator =(const BatchGroupKey&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<BatchGroupKey>(engine, "BatchGroupKey");
}

// struct BatchQueue | File: ../Graphics/Batch.h
static void Register_BatchQueue(asIScriptEngine* engine)
{
    // BatchQueue::~BatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("BatchQueue", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(BatchQueue), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_BatchQueue<BatchQueue>(engine, "BatchQueue");
    CollectMembers_BatchQueue(members);
    RegisterMembers(engine, "BatchQueue", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_BatchQueue
        REGISTER_CLASS_MANUAL_PART_BatchQueue();
    #endif

    // BatchQueue& BatchQueue::operator =(const BatchQueue&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<BatchQueue>(engine, "BatchQueue");
}

// BiasParameters::BiasParameters(float constantBias, float slopeScaledBias, float normalOffset = 0.0f)
static void BiasParameters__BiasParameters_float_float_float(BiasParameters* _ptr, float constantBias, float slopeScaledBias, float normalOffset)
{
    new(_ptr) BiasParameters(constantBias, slopeScaledBias, normalOffset);
}

// struct BiasParameters | File: ../Graphics/Light.h
static void Register_BiasParameters(asIScriptEngine* engine)
{
    // BiasParameters::BiasParameters(float constantBias, float slopeScaledBias, float normalOffset = 0.0f)
    engine->RegisterObjectBehaviour("BiasParameters", asBEHAVE_CONSTRUCT, "void f(float, float, float = 0.0f)", AS_FUNCTION_OBJFIRST(BiasParameters__BiasParameters_float_float_float), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_BiasParameters<BiasParameters>(engine, "BiasParameters");
    CollectMembers_BiasParameters(members);
    RegisterMembers(engine, "BiasParameters", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_BiasParameters
        REGISTER_CLASS_MANUAL_PART_BiasParameters();
    #endif

    // BiasParameters& BiasParameters::operator =(const BiasParameters&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<BiasParameters>(engine, "BiasParameters");
}

// struct Billboard | File: ../Graphics/BillboardSet.h
static void Register_Billboard(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("Billboard", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Billboard", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);

    MemberCollection members;
    RegisterMembers_Billboard<Billboard>(engine, "Billboard");
    CollectMembers_Billboard(members);
    RegisterMembers(engine, "Billboard", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Billboard
        REGISTER_CLASS_MANUAL_PART_Billboard();
    #endif

    // Billboard& Billboard::operator =(const Billboard&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Billboard>(engine, "Billboard");
}

// struct Bone | File: ../Graphics/Skeleton.h
static void Register_Bone(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("Bone", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Bone", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);

    MemberCollection members;
    RegisterMembers_Bone<Bone>(engine, "Bone");
    CollectMembers_Bone(members);
    RegisterMembers(engine, "Bone", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Bone
        REGISTER_CLASS_MANUAL_PART_Bone();
    #endif

    // Bone& Bone::operator =(const Bone&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Bone>(engine, "Bone");
}

// BoundingBox::BoundingBox(const BoundingBox& box) noexcept
static void BoundingBox__BoundingBox_constspBoundingBoxamp(BoundingBox* _ptr, const BoundingBox& box)
{
    new(_ptr) BoundingBox(box);
}

// explicit BoundingBox::BoundingBox(const Rect& rect) noexcept
static void BoundingBox__BoundingBox_constspRectamp(BoundingBox* _ptr, const Rect& rect)
{
    new(_ptr) BoundingBox(rect);
}

// BoundingBox::BoundingBox(const Vector3& min, const Vector3& max) noexcept
static void BoundingBox__BoundingBox_constspVector3amp_constspVector3amp(BoundingBox* _ptr, const Vector3& min, const Vector3& max)
{
    new(_ptr) BoundingBox(min, max);
}

// BoundingBox::BoundingBox(float min, float max) noexcept
static void BoundingBox__BoundingBox_float_float(BoundingBox* _ptr, float min, float max)
{
    new(_ptr) BoundingBox(min, max);
}

// explicit BoundingBox::BoundingBox(const Frustum& frustum)
static void BoundingBox__BoundingBox_constspFrustumamp(BoundingBox* _ptr, const Frustum& frustum)
{
    new(_ptr) BoundingBox(frustum);
}

// explicit BoundingBox::BoundingBox(const Polyhedron& poly)
static void BoundingBox__BoundingBox_constspPolyhedronamp(BoundingBox* _ptr, const Polyhedron& poly)
{
    new(_ptr) BoundingBox(poly);
}

// explicit BoundingBox::BoundingBox(const Sphere& sphere)
static void BoundingBox__BoundingBox_constspSphereamp(BoundingBox* _ptr, const Sphere& sphere)
{
    new(_ptr) BoundingBox(sphere);
}

// class BoundingBox | File: ../Math/BoundingBox.h
static void Register_BoundingBox(asIScriptEngine* engine)
{
    // BoundingBox::BoundingBox(const Vector3* vertices, unsigned count)
    // Error: type "const Vector3*" can not automatically bind

    // BoundingBox::BoundingBox(const BoundingBox& box) noexcept
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", AS_FUNCTION_OBJFIRST(BoundingBox__BoundingBox_constspBoundingBoxamp), AS_CALL_CDECL_OBJFIRST);
    // explicit BoundingBox::BoundingBox(const Rect& rect) noexcept
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Rect&in)", AS_FUNCTION_OBJFIRST(BoundingBox__BoundingBox_constspRectamp), AS_CALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(const Vector3& min, const Vector3& max) noexcept
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(BoundingBox__BoundingBox_constspVector3amp_constspVector3amp), AS_CALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(float min, float max) noexcept
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(float, float)", AS_FUNCTION_OBJFIRST(BoundingBox__BoundingBox_float_float), AS_CALL_CDECL_OBJFIRST);
    // explicit BoundingBox::BoundingBox(const Frustum& frustum)
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", AS_FUNCTION_OBJFIRST(BoundingBox__BoundingBox_constspFrustumamp), AS_CALL_CDECL_OBJFIRST);
    // explicit BoundingBox::BoundingBox(const Polyhedron& poly)
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", AS_FUNCTION_OBJFIRST(BoundingBox__BoundingBox_constspPolyhedronamp), AS_CALL_CDECL_OBJFIRST);
    // explicit BoundingBox::BoundingBox(const Sphere& sphere)
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Sphere&in)", AS_FUNCTION_OBJFIRST(BoundingBox__BoundingBox_constspSphereamp), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_BoundingBox<BoundingBox>(engine, "BoundingBox");
    CollectMembers_BoundingBox(members);
    RegisterMembers(engine, "BoundingBox", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_BoundingBox
        REGISTER_CLASS_MANUAL_PART_BoundingBox();
    #endif
}

// CascadeParameters::CascadeParameters(float split1, float split2, float split3, float split4, float fadeStart, float biasAutoAdjust = 1.0f)
static void CascadeParameters__CascadeParameters_float_float_float_float_float_float(CascadeParameters* _ptr, float split1, float split2, float split3, float split4, float fadeStart, float biasAutoAdjust)
{
    new(_ptr) CascadeParameters(split1, split2, split3, split4, fadeStart, biasAutoAdjust);
}

// struct CascadeParameters | File: ../Graphics/Light.h
static void Register_CascadeParameters(asIScriptEngine* engine)
{
    // CascadeParameters::CascadeParameters(float split1, float split2, float split3, float split4, float fadeStart, float biasAutoAdjust = 1.0f)
    engine->RegisterObjectBehaviour("CascadeParameters", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float = 1.0f)", AS_FUNCTION_OBJFIRST(CascadeParameters__CascadeParameters_float_float_float_float_float_float), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_CascadeParameters<CascadeParameters>(engine, "CascadeParameters");
    CollectMembers_CascadeParameters(members);
    RegisterMembers(engine, "CascadeParameters", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CascadeParameters
        REGISTER_CLASS_MANUAL_PART_CascadeParameters();
    #endif

    // CascadeParameters& CascadeParameters::operator =(const CascadeParameters&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<CascadeParameters>(engine, "CascadeParameters");
}

// struct CharLocation | File: ../UI/Text.h
static void Register_CharLocation(asIScriptEngine* engine)
{
    // CharLocation::~CharLocation() | Implicitly-declared
    engine->RegisterObjectBehaviour("CharLocation", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(CharLocation), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_CharLocation<CharLocation>(engine, "CharLocation");
    CollectMembers_CharLocation(members);
    RegisterMembers(engine, "CharLocation", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CharLocation
        REGISTER_CLASS_MANUAL_PART_CharLocation();
    #endif

    // CharLocation& CharLocation::operator =(const CharLocation&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<CharLocation>(engine, "CharLocation");
}

// Color::Color(const Color& color) noexcept = default
static void Color__Color_constspColoramp(Color* _ptr, const Color& color)
{
    new(_ptr) Color(color);
}

// Color::Color(const Color& color, float a) noexcept
static void Color__Color_constspColoramp_float(Color* _ptr, const Color& color, float a)
{
    new(_ptr) Color(color, a);
}

// Color::Color(float r, float g, float b) noexcept
static void Color__Color_float_float_float(Color* _ptr, float r, float g, float b)
{
    new(_ptr) Color(r, g, b);
}

// Color::Color(float r, float g, float b, float a) noexcept
static void Color__Color_float_float_float_float(Color* _ptr, float r, float g, float b, float a)
{
    new(_ptr) Color(r, g, b, a);
}

// explicit Color::Color(const Vector3& color)
static void Color__Color_constspVector3amp(Color* _ptr, const Vector3& color)
{
    new(_ptr) Color(color);
}

// explicit Color::Color(const Vector4& color)
static void Color__Color_constspVector4amp(Color* _ptr, const Vector4& color)
{
    new(_ptr) Color(color);
}

// class Color | File: ../Math/Color.h
static void Register_Color(asIScriptEngine* engine)
{
    // explicit Color::Color(const float* data) noexcept
    // Error: type "const float*" can not automatically bind
    // explicit Color::Color(unsigned color, const ChannelMask& mask = ABGR)
    // Error: type "const ChannelMask&" can not automatically bind

    // Color::Color(const Color& color) noexcept = default
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color&in)", AS_FUNCTION_OBJFIRST(Color__Color_constspColoramp), AS_CALL_CDECL_OBJFIRST);
    // Color::Color(const Color& color, float a) noexcept
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color&in, float)", AS_FUNCTION_OBJFIRST(Color__Color_constspColoramp_float), AS_CALL_CDECL_OBJFIRST);
    // Color::Color(float r, float g, float b) noexcept
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float)", AS_FUNCTION_OBJFIRST(Color__Color_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // Color::Color(float r, float g, float b, float a) noexcept
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", AS_FUNCTION_OBJFIRST(Color__Color_float_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Color::Color(const Vector3& color)
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", AS_FUNCTION_OBJFIRST(Color__Color_constspVector3amp), AS_CALL_CDECL_OBJFIRST);
    // explicit Color::Color(const Vector4& color)
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", AS_FUNCTION_OBJFIRST(Color__Color_constspVector4amp), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Color<Color>(engine, "Color");
    CollectMembers_Color(members);
    RegisterMembers(engine, "Color", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Color
        REGISTER_CLASS_MANUAL_PART_Color();
    #endif
}

// explicit ColorFrame::ColorFrame(const Color& color)
static ColorFrame* ColorFrame__ColorFrame_constspColoramp(const Color& color)
{
    return new ColorFrame(color);
}

// ColorFrame::ColorFrame(const Color& color, float time)
static ColorFrame* ColorFrame__ColorFrame_constspColoramp_float(const Color& color, float time)
{
    return new ColorFrame(color, time);
}

// struct ColorFrame | File: ../Graphics/ParticleEffect.h
static void Register_ColorFrame(asIScriptEngine* engine)
{
    // explicit ColorFrame::ColorFrame(const Color& color)
    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_FACTORY, "ColorFrame@+ f(const Color&in)", AS_FUNCTION(ColorFrame__ColorFrame_constspColoramp) , AS_CALL_CDECL);
    // ColorFrame::ColorFrame(const Color& color, float time)
    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_FACTORY, "ColorFrame@+ f(const Color&in, float)", AS_FUNCTION(ColorFrame__ColorFrame_constspColoramp_float) , AS_CALL_CDECL);

    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);

    MemberCollection members;
    RegisterMembers_ColorFrame<ColorFrame>(engine, "ColorFrame");
    CollectMembers_ColorFrame(members);
    RegisterMembers(engine, "ColorFrame", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ColorFrame
        REGISTER_CLASS_MANUAL_PART_ColorFrame();
    #endif

    // ColorFrame& ColorFrame::operator =(const ColorFrame&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ColorFrame>(engine, "ColorFrame");
}

// struct CompressedLevel | File: ../Resource/Image.h
static void Register_CompressedLevel(asIScriptEngine* engine)
{
    // CompressedLevel::~CompressedLevel() | Implicitly-declared
    engine->RegisterObjectBehaviour("CompressedLevel", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(CompressedLevel), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_CompressedLevel<CompressedLevel>(engine, "CompressedLevel");
    CollectMembers_CompressedLevel(members);
    RegisterMembers(engine, "CompressedLevel", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CompressedLevel
        REGISTER_CLASS_MANUAL_PART_CompressedLevel();
    #endif

    // CompressedLevel& CompressedLevel::operator =(const CompressedLevel&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<CompressedLevel>(engine, "CompressedLevel");
}

// class Condition | File: ../Core/Condition.h
static void Register_Condition(asIScriptEngine* engine)
{
    // Condition::~Condition()
    engine->RegisterObjectBehaviour("Condition", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(Condition), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Condition<Condition>(engine, "Condition");
    CollectMembers_Condition(members);
    RegisterMembers(engine, "Condition", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Condition
        REGISTER_CLASS_MANUAL_PART_Condition();
    #endif

    // Condition& Condition::operator =(const Condition&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Condition>(engine, "Condition");
}

// class Controls | File: ../Input/Controls.h
static void Register_Controls(asIScriptEngine* engine)
{
    // Controls::~Controls()
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(Controls), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Controls<Controls>(engine, "Controls");
    CollectMembers_Controls(members);
    RegisterMembers(engine, "Controls", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Controls
        REGISTER_CLASS_MANUAL_PART_Controls();
    #endif

    // Controls& Controls::operator =(const Controls&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Controls>(engine, "Controls");
}

// explicit CursorShapeInfo::CursorShapeInfo(int systemCursor)
static void CursorShapeInfo__CursorShapeInfo_int(CursorShapeInfo* _ptr, int systemCursor)
{
    new(_ptr) CursorShapeInfo(systemCursor);
}

// struct CursorShapeInfo | File: ../UI/Cursor.h
static void Register_CursorShapeInfo(asIScriptEngine* engine)
{
    // explicit CursorShapeInfo::CursorShapeInfo(int systemCursor)
    engine->RegisterObjectBehaviour("CursorShapeInfo", asBEHAVE_CONSTRUCT, "void f(int)", AS_FUNCTION_OBJFIRST(CursorShapeInfo__CursorShapeInfo_int), AS_CALL_CDECL_OBJFIRST);

    // CursorShapeInfo::~CursorShapeInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("CursorShapeInfo", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(CursorShapeInfo), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_CursorShapeInfo<CursorShapeInfo>(engine, "CursorShapeInfo");
    CollectMembers_CursorShapeInfo(members);
    RegisterMembers(engine, "CursorShapeInfo", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CursorShapeInfo
        REGISTER_CLASS_MANUAL_PART_CursorShapeInfo();
    #endif

    // CursorShapeInfo& CursorShapeInfo::operator =(const CursorShapeInfo&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<CursorShapeInfo>(engine, "CursorShapeInfo");
}

// struct CustomGeometryVertex | File: ../Graphics/CustomGeometry.h
static void Register_CustomGeometryVertex(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("CustomGeometryVertex", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("CustomGeometryVertex", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);

    MemberCollection members;
    RegisterMembers_CustomGeometryVertex<CustomGeometryVertex>(engine, "CustomGeometryVertex");
    CollectMembers_CustomGeometryVertex(members);
    RegisterMembers(engine, "CustomGeometryVertex", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CustomGeometryVertex
        REGISTER_CLASS_MANUAL_PART_CustomGeometryVertex();
    #endif

    // CustomGeometryVertex& CustomGeometryVertex::operator =(const CustomGeometryVertex&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<CustomGeometryVertex>(engine, "CustomGeometryVertex");
}

// DebugLine::DebugLine(const Vector3& start, const Vector3& end, unsigned color)
static void DebugLine__DebugLine_constspVector3amp_constspVector3amp_unsigned(DebugLine* _ptr, const Vector3& start, const Vector3& end, unsigned color)
{
    new(_ptr) DebugLine(start, end, color);
}

// struct DebugLine | File: ../Graphics/DebugRenderer.h
static void Register_DebugLine(asIScriptEngine* engine)
{
    // DebugLine::DebugLine(const Vector3& start, const Vector3& end, unsigned color)
    engine->RegisterObjectBehaviour("DebugLine", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, uint)", AS_FUNCTION_OBJFIRST(DebugLine__DebugLine_constspVector3amp_constspVector3amp_unsigned), AS_CALL_CDECL_OBJFIRST);

    // DebugLine::~DebugLine() | Implicitly-declared
    engine->RegisterObjectBehaviour("DebugLine", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(DebugLine), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_DebugLine<DebugLine>(engine, "DebugLine");
    CollectMembers_DebugLine(members);
    RegisterMembers(engine, "DebugLine", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_DebugLine
        REGISTER_CLASS_MANUAL_PART_DebugLine();
    #endif

    // DebugLine& DebugLine::operator =(const DebugLine&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DebugLine>(engine, "DebugLine");
}

// DebugTriangle::DebugTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, unsigned color)
static void DebugTriangle__DebugTriangle_constspVector3amp_constspVector3amp_constspVector3amp_unsigned(DebugTriangle* _ptr, const Vector3& v1, const Vector3& v2, const Vector3& v3, unsigned color)
{
    new(_ptr) DebugTriangle(v1, v2, v3, color);
}

// struct DebugTriangle | File: ../Graphics/DebugRenderer.h
static void Register_DebugTriangle(asIScriptEngine* engine)
{
    // DebugTriangle::DebugTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, unsigned color)
    engine->RegisterObjectBehaviour("DebugTriangle", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, const Vector3&in, uint)", AS_FUNCTION_OBJFIRST(DebugTriangle__DebugTriangle_constspVector3amp_constspVector3amp_constspVector3amp_unsigned), AS_CALL_CDECL_OBJFIRST);

    // DebugTriangle::~DebugTriangle() | Implicitly-declared
    engine->RegisterObjectBehaviour("DebugTriangle", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(DebugTriangle), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_DebugTriangle<DebugTriangle>(engine, "DebugTriangle");
    CollectMembers_DebugTriangle(members);
    RegisterMembers(engine, "DebugTriangle", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_DebugTriangle
        REGISTER_CLASS_MANUAL_PART_DebugTriangle();
    #endif

    // DebugTriangle& DebugTriangle::operator =(const DebugTriangle&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DebugTriangle>(engine, "DebugTriangle");
}

// struct Decal | File: ../Graphics/DecalSet.h
static void Register_Decal(asIScriptEngine* engine)
{
    // Decal::~Decal() | Implicitly-declared
    engine->RegisterObjectBehaviour("Decal", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(Decal), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Decal<Decal>(engine, "Decal");
    CollectMembers_Decal(members);
    RegisterMembers(engine, "Decal", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Decal
        REGISTER_CLASS_MANUAL_PART_Decal();
    #endif

    // Decal& Decal::operator =(const Decal&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Decal>(engine, "Decal");
}

// DecalVertex::DecalVertex(const Vector3& position, const Vector3& normal)
static void DecalVertex__DecalVertex_constspVector3amp_constspVector3amp(DecalVertex* _ptr, const Vector3& position, const Vector3& normal)
{
    new(_ptr) DecalVertex(position, normal);
}

// struct DecalVertex | File: ../Graphics/DecalSet.h
static void Register_DecalVertex(asIScriptEngine* engine)
{
    // DecalVertex::DecalVertex(const Vector3& position, const Vector3& normal, const float* blendWeights, const unsigned char* blendIndices)
    // Error: type "const float*" can not automatically bind

    // DecalVertex::DecalVertex(const Vector3& position, const Vector3& normal)
    engine->RegisterObjectBehaviour("DecalVertex", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(DecalVertex__DecalVertex_constspVector3amp_constspVector3amp), AS_CALL_CDECL_OBJFIRST);

    // DecalVertex::~DecalVertex() | Implicitly-declared
    engine->RegisterObjectBehaviour("DecalVertex", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(DecalVertex), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_DecalVertex<DecalVertex>(engine, "DecalVertex");
    CollectMembers_DecalVertex(members);
    RegisterMembers(engine, "DecalVertex", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_DecalVertex
        REGISTER_CLASS_MANUAL_PART_DecalVertex();
    #endif

    // DecalVertex& DecalVertex::operator =(const DecalVertex&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DecalVertex>(engine, "DecalVertex");
}

// struct DepthValue | File: ../Graphics/OcclusionBuffer.h
static void Register_DepthValue(asIScriptEngine* engine)
{
    MemberCollection members;
    RegisterMembers_DepthValue<DepthValue>(engine, "DepthValue");
    CollectMembers_DepthValue(members);
    RegisterMembers(engine, "DepthValue", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_DepthValue
        REGISTER_CLASS_MANUAL_PART_DepthValue();
    #endif

    // DepthValue& DepthValue::operator =(const DepthValue&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DepthValue>(engine, "DepthValue");
}

// class Deserializer | File: ../IO/Deserializer.h
static void Register_Deserializer(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("Deserializer", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Deserializer", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);

    MemberCollection members;
    RegisterMembers_Deserializer<Deserializer>(engine, "Deserializer");
    CollectMembers_Deserializer(members);
    RegisterMembers(engine, "Deserializer", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Deserializer
        REGISTER_CLASS_MANUAL_PART_Deserializer();
    #endif

    // Deserializer& Deserializer::operator =(const Deserializer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Deserializer>(engine, "Deserializer");
}

// DirtyBits::DirtyBits(const DirtyBits& bits)
static void DirtyBits__DirtyBits_constspDirtyBitsamp(DirtyBits* _ptr, const DirtyBits& bits)
{
    new(_ptr) DirtyBits(bits);
}

// struct DirtyBits | File: ../Scene/ReplicationState.h
static void Register_DirtyBits(asIScriptEngine* engine)
{
    // DirtyBits::DirtyBits(const DirtyBits& bits)
    engine->RegisterObjectBehaviour("DirtyBits", asBEHAVE_CONSTRUCT, "void f(const DirtyBits&in)", AS_FUNCTION_OBJFIRST(DirtyBits__DirtyBits_constspDirtyBitsamp), AS_CALL_CDECL_OBJFIRST);

    // DirtyBits::~DirtyBits() | Implicitly-declared
    engine->RegisterObjectBehaviour("DirtyBits", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(DirtyBits), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_DirtyBits<DirtyBits>(engine, "DirtyBits");
    CollectMembers_DirtyBits(members);
    RegisterMembers(engine, "DirtyBits", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_DirtyBits
        REGISTER_CLASS_MANUAL_PART_DirtyBits();
    #endif

    // DirtyBits& DirtyBits::operator =(const DirtyBits&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DirtyBits>(engine, "DirtyBits");
}

// struct FileSelectorEntry | File: ../UI/FileSelector.h
static void Register_FileSelectorEntry(asIScriptEngine* engine)
{
    // FileSelectorEntry::~FileSelectorEntry() | Implicitly-declared
    engine->RegisterObjectBehaviour("FileSelectorEntry", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(FileSelectorEntry), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_FileSelectorEntry<FileSelectorEntry>(engine, "FileSelectorEntry");
    CollectMembers_FileSelectorEntry(members);
    RegisterMembers(engine, "FileSelectorEntry", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_FileSelectorEntry
        REGISTER_CLASS_MANUAL_PART_FileSelectorEntry();
    #endif

    // FileSelectorEntry& FileSelectorEntry::operator =(const FileSelectorEntry&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<FileSelectorEntry>(engine, "FileSelectorEntry");
}

// FocusParameters::FocusParameters(bool focus, bool nonUniform, bool autoSize, float quantize, float minView)
static void FocusParameters__FocusParameters_bool_bool_bool_float_float(FocusParameters* _ptr, bool focus, bool nonUniform, bool autoSize, float quantize, float minView)
{
    new(_ptr) FocusParameters(focus, nonUniform, autoSize, quantize, minView);
}

// struct FocusParameters | File: ../Graphics/Light.h
static void Register_FocusParameters(asIScriptEngine* engine)
{
    // FocusParameters::FocusParameters(bool focus, bool nonUniform, bool autoSize, float quantize, float minView)
    engine->RegisterObjectBehaviour("FocusParameters", asBEHAVE_CONSTRUCT, "void f(bool, bool, bool, float, float)", AS_FUNCTION_OBJFIRST(FocusParameters__FocusParameters_bool_bool_bool_float_float), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_FocusParameters<FocusParameters>(engine, "FocusParameters");
    CollectMembers_FocusParameters(members);
    RegisterMembers(engine, "FocusParameters", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_FocusParameters
        REGISTER_CLASS_MANUAL_PART_FocusParameters();
    #endif

    // FocusParameters& FocusParameters::operator =(const FocusParameters&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<FocusParameters>(engine, "FocusParameters");
}

// struct FontGlyph | File: ../UI/FontFace.h
static void Register_FontGlyph(asIScriptEngine* engine)
{
    // FontGlyph::~FontGlyph() | Implicitly-declared
    engine->RegisterObjectBehaviour("FontGlyph", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(FontGlyph), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_FontGlyph<FontGlyph>(engine, "FontGlyph");
    CollectMembers_FontGlyph(members);
    RegisterMembers(engine, "FontGlyph", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_FontGlyph
        REGISTER_CLASS_MANUAL_PART_FontGlyph();
    #endif

    // FontGlyph& FontGlyph::operator =(const FontGlyph&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<FontGlyph>(engine, "FontGlyph");
}

// struct FrameInfo | File: ../Graphics/Drawable.h
static void Register_FrameInfo(asIScriptEngine* engine)
{
    // FrameInfo::~FrameInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("FrameInfo", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(FrameInfo), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_FrameInfo<FrameInfo>(engine, "FrameInfo");
    CollectMembers_FrameInfo(members);
    RegisterMembers(engine, "FrameInfo", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_FrameInfo
        REGISTER_CLASS_MANUAL_PART_FrameInfo();
    #endif

    // FrameInfo& FrameInfo::operator =(const FrameInfo&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<FrameInfo>(engine, "FrameInfo");
}

// Frustum::Frustum(const Frustum& frustum) noexcept
static void Frustum__Frustum_constspFrustumamp(Frustum* _ptr, const Frustum& frustum)
{
    new(_ptr) Frustum(frustum);
}

// class Frustum | File: ../Math/Frustum.h
static void Register_Frustum(asIScriptEngine* engine)
{
    // Frustum::Frustum(const Frustum& frustum) noexcept
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", AS_FUNCTION_OBJFIRST(Frustum__Frustum_constspFrustumamp), AS_CALL_CDECL_OBJFIRST);

    // Frustum::~Frustum() | Implicitly-declared
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(Frustum), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Frustum<Frustum>(engine, "Frustum");
    CollectMembers_Frustum(members);
    RegisterMembers(engine, "Frustum", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Frustum
        REGISTER_CLASS_MANUAL_PART_Frustum();
    #endif
}

// explicit GPUObject::GPUObject(Graphics* graphics)
static void GPUObject__GPUObject_Graphicsstar(GPUObject* _ptr, Graphics* graphics)
{
    new(_ptr) GPUObject(graphics);
}

// class GPUObject | File: ../Graphics/GPUObject.h
static void Register_GPUObject(asIScriptEngine* engine)
{
    // explicit GPUObject::GPUObject(Graphics* graphics)
    engine->RegisterObjectBehaviour("GPUObject", asBEHAVE_CONSTRUCT, "void f(Graphics@+)", AS_FUNCTION_OBJFIRST(GPUObject__GPUObject_Graphicsstar), AS_CALL_CDECL_OBJFIRST);

    // virtual GPUObject::~GPUObject()
    engine->RegisterObjectBehaviour("GPUObject", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(GPUObject), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_GPUObject<GPUObject>(engine, "GPUObject");
    CollectMembers_GPUObject(members);
    RegisterMembers(engine, "GPUObject", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_GPUObject
        REGISTER_CLASS_MANUAL_PART_GPUObject();
    #endif

    // GPUObject& GPUObject::operator =(const GPUObject&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<GPUObject>(engine, "GPUObject");
}

// struct GeometryDesc | File: ../Graphics/Model.h
static void Register_GeometryDesc(asIScriptEngine* engine)
{
    // GeometryDesc::~GeometryDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("GeometryDesc", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(GeometryDesc), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_GeometryDesc<GeometryDesc>(engine, "GeometryDesc");
    CollectMembers_GeometryDesc(members);
    RegisterMembers(engine, "GeometryDesc", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_GeometryDesc
        REGISTER_CLASS_MANUAL_PART_GeometryDesc();
    #endif

    // GeometryDesc& GeometryDesc::operator =(const GeometryDesc&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<GeometryDesc>(engine, "GeometryDesc");
}

// class HashBase | File: ../Container/HashBase.h
static void Register_HashBase(asIScriptEngine* engine)
{
    // HashBase::~HashBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("HashBase", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(HashBase), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_HashBase<HashBase>(engine, "HashBase");
    CollectMembers_HashBase(members);
    RegisterMembers(engine, "HashBase", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_HashBase
        REGISTER_CLASS_MANUAL_PART_HashBase();
    #endif

    // HashBase& HashBase::operator =(const HashBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<HashBase>(engine, "HashBase");
}

// struct HashIteratorBase | File: ../Container/HashBase.h
static void Register_HashIteratorBase(asIScriptEngine* engine)
{
    // explicit HashIteratorBase::HashIteratorBase(HashNodeBase* ptr)
    // Error: type "HashNodeBase*" can not automatically bind

    // HashIteratorBase::~HashIteratorBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("HashIteratorBase", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(HashIteratorBase), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_HashIteratorBase<HashIteratorBase>(engine, "HashIteratorBase");
    CollectMembers_HashIteratorBase(members);
    RegisterMembers(engine, "HashIteratorBase", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_HashIteratorBase
        REGISTER_CLASS_MANUAL_PART_HashIteratorBase();
    #endif

    // HashIteratorBase& HashIteratorBase::operator =(const HashIteratorBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<HashIteratorBase>(engine, "HashIteratorBase");
}

// struct HashNodeBase | File: ../Container/HashBase.h
static void Register_HashNodeBase(asIScriptEngine* engine)
{
    // HashNodeBase::~HashNodeBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("HashNodeBase", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(HashNodeBase), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_HashNodeBase<HashNodeBase>(engine, "HashNodeBase");
    CollectMembers_HashNodeBase(members);
    RegisterMembers(engine, "HashNodeBase", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_HashNodeBase
        REGISTER_CLASS_MANUAL_PART_HashNodeBase();
    #endif

    // HashNodeBase& HashNodeBase::operator =(const HashNodeBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<HashNodeBase>(engine, "HashNodeBase");
}

// class HiresTimer | File: ../Core/Timer.h
static void Register_HiresTimer(asIScriptEngine* engine)
{
    // HiresTimer::~HiresTimer() | Implicitly-declared
    engine->RegisterObjectBehaviour("HiresTimer", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(HiresTimer), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_HiresTimer<HiresTimer>(engine, "HiresTimer");
    CollectMembers_HiresTimer(members);
    RegisterMembers(engine, "HiresTimer", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_HiresTimer
        REGISTER_CLASS_MANUAL_PART_HiresTimer();
    #endif

    // HiresTimer& HiresTimer::operator =(const HiresTimer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<HiresTimer>(engine, "HiresTimer");
}

// struct IndexBufferDesc | File: ../Graphics/Model.h
static void Register_IndexBufferDesc(asIScriptEngine* engine)
{
    // IndexBufferDesc::~IndexBufferDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("IndexBufferDesc", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(IndexBufferDesc), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_IndexBufferDesc<IndexBufferDesc>(engine, "IndexBufferDesc");
    CollectMembers_IndexBufferDesc(members);
    RegisterMembers(engine, "IndexBufferDesc", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_IndexBufferDesc
        REGISTER_CLASS_MANUAL_PART_IndexBufferDesc();
    #endif

    // IndexBufferDesc& IndexBufferDesc::operator =(const IndexBufferDesc&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<IndexBufferDesc>(engine, "IndexBufferDesc");
}

// struct InstanceData | File: ../Graphics/Batch.h
static void Register_InstanceData(asIScriptEngine* engine)
{
    // InstanceData::InstanceData(const Matrix3x4* worldTransform, const void* instancingData, float distance)
    // Error: type "const Matrix3x4*" can not automatically bind

    // InstanceData::~InstanceData() | Implicitly-declared
    engine->RegisterObjectBehaviour("InstanceData", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(InstanceData), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_InstanceData<InstanceData>(engine, "InstanceData");
    CollectMembers_InstanceData(members);
    RegisterMembers(engine, "InstanceData", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_InstanceData
        REGISTER_CLASS_MANUAL_PART_InstanceData();
    #endif

    // InstanceData& InstanceData::operator =(const InstanceData&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<InstanceData>(engine, "InstanceData");
}

// IntRect::IntRect(const IntVector2& min, const IntVector2& max) noexcept
static void IntRect__IntRect_constspIntVector2amp_constspIntVector2amp(IntRect* _ptr, const IntVector2& min, const IntVector2& max)
{
    new(_ptr) IntRect(min, max);
}

// IntRect::IntRect(int left, int top, int right, int bottom) noexcept
static void IntRect__IntRect_int_int_int_int(IntRect* _ptr, int left, int top, int right, int bottom)
{
    new(_ptr) IntRect(left, top, right, bottom);
}

// class IntRect | File: ../Math/Rect.h
static void Register_IntRect(asIScriptEngine* engine)
{
    // explicit IntRect::IntRect(const int* data) noexcept
    // Error: type "const int*" can not automatically bind

    // IntRect::IntRect(const IntVector2& min, const IntVector2& max) noexcept
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in, const IntVector2&in)", AS_FUNCTION_OBJFIRST(IntRect__IntRect_constspIntVector2amp_constspIntVector2amp), AS_CALL_CDECL_OBJFIRST);
    // IntRect::IntRect(int left, int top, int right, int bottom) noexcept
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(int, int, int, int)", AS_FUNCTION_OBJFIRST(IntRect__IntRect_int_int_int_int), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_IntRect<IntRect>(engine, "IntRect");
    CollectMembers_IntRect(members);
    RegisterMembers(engine, "IntRect", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_IntRect
        REGISTER_CLASS_MANUAL_PART_IntRect();
    #endif

    // IntRect& IntRect::operator =(const IntRect&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<IntRect>(engine, "IntRect");
}

// IntVector2::IntVector2(int x, int y) noexcept
static void IntVector2__IntVector2_int_int(IntVector2* _ptr, int x, int y)
{
    new(_ptr) IntVector2(x, y);
}

// IntVector2::IntVector2(const IntVector2& rhs) noexcept = default
static void IntVector2__IntVector2_constspIntVector2amp(IntVector2* _ptr, const IntVector2& rhs)
{
    new(_ptr) IntVector2(rhs);
}

// class IntVector2 | File: ../Math/Vector2.h
static void Register_IntVector2(asIScriptEngine* engine)
{
    // explicit IntVector2::IntVector2(const float* data)
    // Error: type "const float*" can not automatically bind
    // explicit IntVector2::IntVector2(const int* data) noexcept
    // Error: type "const int*" can not automatically bind

    // IntVector2::IntVector2(int x, int y) noexcept
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(int, int)", AS_FUNCTION_OBJFIRST(IntVector2__IntVector2_int_int), AS_CALL_CDECL_OBJFIRST);
    // IntVector2::IntVector2(const IntVector2& rhs) noexcept = default
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", AS_FUNCTION_OBJFIRST(IntVector2__IntVector2_constspIntVector2amp), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_IntVector2<IntVector2>(engine, "IntVector2");
    CollectMembers_IntVector2(members);
    RegisterMembers(engine, "IntVector2", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_IntVector2
        REGISTER_CLASS_MANUAL_PART_IntVector2();
    #endif
}

// IntVector3::IntVector3(int x, int y, int z) noexcept
static void IntVector3__IntVector3_int_int_int(IntVector3* _ptr, int x, int y, int z)
{
    new(_ptr) IntVector3(x, y, z);
}

// IntVector3::IntVector3(const IntVector3& rhs) noexcept = default
static void IntVector3__IntVector3_constspIntVector3amp(IntVector3* _ptr, const IntVector3& rhs)
{
    new(_ptr) IntVector3(rhs);
}

// class IntVector3 | File: ../Math/Vector3.h
static void Register_IntVector3(asIScriptEngine* engine)
{
    // explicit IntVector3::IntVector3(const int* data) noexcept
    // Error: type "const int*" can not automatically bind

    // IntVector3::IntVector3(int x, int y, int z) noexcept
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f(int, int, int)", AS_FUNCTION_OBJFIRST(IntVector3__IntVector3_int_int_int), AS_CALL_CDECL_OBJFIRST);
    // IntVector3::IntVector3(const IntVector3& rhs) noexcept = default
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f(const IntVector3&in)", AS_FUNCTION_OBJFIRST(IntVector3__IntVector3_constspIntVector3amp), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_IntVector3<IntVector3>(engine, "IntVector3");
    CollectMembers_IntVector3(members);
    RegisterMembers(engine, "IntVector3", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_IntVector3
        REGISTER_CLASS_MANUAL_PART_IntVector3();
    #endif
}

// JSONValue::JSONValue(bool value)
static void JSONValue__JSONValue_bool(JSONValue* _ptr, bool value)
{
    new(_ptr) JSONValue(value);
}

// JSONValue::JSONValue(int value)
static void JSONValue__JSONValue_int(JSONValue* _ptr, int value)
{
    new(_ptr) JSONValue(value);
}

// JSONValue::JSONValue(unsigned value)
static void JSONValue__JSONValue_unsigned(JSONValue* _ptr, unsigned value)
{
    new(_ptr) JSONValue(value);
}

// JSONValue::JSONValue(float value)
static void JSONValue__JSONValue_float(JSONValue* _ptr, float value)
{
    new(_ptr) JSONValue(value);
}

// JSONValue::JSONValue(double value)
static void JSONValue__JSONValue_double(JSONValue* _ptr, double value)
{
    new(_ptr) JSONValue(value);
}

// JSONValue::JSONValue(const String& value)
static void JSONValue__JSONValue_constspStringamp(JSONValue* _ptr, const String& value)
{
    new(_ptr) JSONValue(value);
}

// JSONValue::JSONValue(const JSONValue& value)
static void JSONValue__JSONValue_constspJSONValueamp(JSONValue* _ptr, const JSONValue& value)
{
    new(_ptr) JSONValue(value);
}

// class JSONValue | File: ../Resource/JSONValue.h
static void Register_JSONValue(asIScriptEngine* engine)
{
    // JSONValue::JSONValue(const JSONArray& value)
    // Error: type "const JSONArray&" can not automatically bind
    // JSONValue::JSONValue(const JSONObject& value)
    // Error: type "const JSONObject&" can not automatically bind
    // JSONValue::JSONValue(const char* value)
    // Error: type "const char*" can not automatically bind

    // JSONValue::JSONValue(bool value)
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(bool)", AS_FUNCTION_OBJFIRST(JSONValue__JSONValue_bool), AS_CALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(int value)
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(int)", AS_FUNCTION_OBJFIRST(JSONValue__JSONValue_int), AS_CALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(unsigned value)
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(uint)", AS_FUNCTION_OBJFIRST(JSONValue__JSONValue_unsigned), AS_CALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(float value)
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(float)", AS_FUNCTION_OBJFIRST(JSONValue__JSONValue_float), AS_CALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(double value)
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(double)", AS_FUNCTION_OBJFIRST(JSONValue__JSONValue_double), AS_CALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(const String& value)
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(const String&in)", AS_FUNCTION_OBJFIRST(JSONValue__JSONValue_constspStringamp), AS_CALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(const JSONValue& value)
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(const JSONValue&in)", AS_FUNCTION_OBJFIRST(JSONValue__JSONValue_constspJSONValueamp), AS_CALL_CDECL_OBJFIRST);

    // JSONValue::~JSONValue()
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(JSONValue), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_JSONValue<JSONValue>(engine, "JSONValue");
    CollectMembers_JSONValue(members);
    RegisterMembers(engine, "JSONValue", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_JSONValue
        REGISTER_CLASS_MANUAL_PART_JSONValue();
    #endif
}

// struct JoystickState | File: ../Input/Input.h
static void Register_JoystickState(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("JoystickState", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("JoystickState", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);

    MemberCollection members;
    RegisterMembers_JoystickState<JoystickState>(engine, "JoystickState");
    CollectMembers_JoystickState(members);
    RegisterMembers(engine, "JoystickState", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_JoystickState
        REGISTER_CLASS_MANUAL_PART_JoystickState();
    #endif

    // JoystickState& JoystickState::operator =(const JoystickState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<JoystickState>(engine, "JoystickState");
}

// struct LightBatchQueue | File: ../Graphics/Batch.h
static void Register_LightBatchQueue(asIScriptEngine* engine)
{
    // LightBatchQueue::~LightBatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("LightBatchQueue", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(LightBatchQueue), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_LightBatchQueue<LightBatchQueue>(engine, "LightBatchQueue");
    CollectMembers_LightBatchQueue(members);
    RegisterMembers(engine, "LightBatchQueue", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_LightBatchQueue
        REGISTER_CLASS_MANUAL_PART_LightBatchQueue();
    #endif

    // LightBatchQueue& LightBatchQueue::operator =(const LightBatchQueue&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<LightBatchQueue>(engine, "LightBatchQueue");
}

// struct LightQueryResult | File: ../Graphics/View.h
static void Register_LightQueryResult(asIScriptEngine* engine)
{
    // LightQueryResult::~LightQueryResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("LightQueryResult", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(LightQueryResult), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_LightQueryResult<LightQueryResult>(engine, "LightQueryResult");
    CollectMembers_LightQueryResult(members);
    RegisterMembers(engine, "LightQueryResult", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_LightQueryResult
        REGISTER_CLASS_MANUAL_PART_LightQueryResult();
    #endif

    // LightQueryResult& LightQueryResult::operator =(const LightQueryResult&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<LightQueryResult>(engine, "LightQueryResult");
}

// struct LinkedListNode | File: ../Container/LinkedList.h
static void Register_LinkedListNode(asIScriptEngine* engine)
{
    // LinkedListNode::~LinkedListNode() | Implicitly-declared
    engine->RegisterObjectBehaviour("LinkedListNode", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(LinkedListNode), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_LinkedListNode<LinkedListNode>(engine, "LinkedListNode");
    CollectMembers_LinkedListNode(members);
    RegisterMembers(engine, "LinkedListNode", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_LinkedListNode
        REGISTER_CLASS_MANUAL_PART_LinkedListNode();
    #endif

    // LinkedListNode& LinkedListNode::operator =(const LinkedListNode&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<LinkedListNode>(engine, "LinkedListNode");
}

// class ListBase | File: ../Container/ListBase.h
static void Register_ListBase(asIScriptEngine* engine)
{
    // ListBase::~ListBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("ListBase", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ListBase), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ListBase<ListBase>(engine, "ListBase");
    CollectMembers_ListBase(members);
    RegisterMembers(engine, "ListBase", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ListBase
        REGISTER_CLASS_MANUAL_PART_ListBase();
    #endif

    // ListBase& ListBase::operator =(const ListBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ListBase>(engine, "ListBase");
}

// struct ListIteratorBase | File: ../Container/ListBase.h
static void Register_ListIteratorBase(asIScriptEngine* engine)
{
    // explicit ListIteratorBase::ListIteratorBase(ListNodeBase* ptr)
    // Error: type "ListNodeBase*" can not automatically bind

    // ListIteratorBase::~ListIteratorBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("ListIteratorBase", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ListIteratorBase), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ListIteratorBase<ListIteratorBase>(engine, "ListIteratorBase");
    CollectMembers_ListIteratorBase(members);
    RegisterMembers(engine, "ListIteratorBase", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ListIteratorBase
        REGISTER_CLASS_MANUAL_PART_ListIteratorBase();
    #endif

    // ListIteratorBase& ListIteratorBase::operator =(const ListIteratorBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ListIteratorBase>(engine, "ListIteratorBase");
}

// struct ListNodeBase | File: ../Container/ListBase.h
static void Register_ListNodeBase(asIScriptEngine* engine)
{
    // ListNodeBase::~ListNodeBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("ListNodeBase", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ListNodeBase), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ListNodeBase<ListNodeBase>(engine, "ListNodeBase");
    CollectMembers_ListNodeBase(members);
    RegisterMembers(engine, "ListNodeBase", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ListNodeBase
        REGISTER_CLASS_MANUAL_PART_ListNodeBase();
    #endif

    // ListNodeBase& ListNodeBase::operator =(const ListNodeBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ListNodeBase>(engine, "ListNodeBase");
}

// struct MaterialShaderParameter | File: ../Graphics/Material.h
static void Register_MaterialShaderParameter(asIScriptEngine* engine)
{
    // MaterialShaderParameter::~MaterialShaderParameter() | Implicitly-declared
    engine->RegisterObjectBehaviour("MaterialShaderParameter", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(MaterialShaderParameter), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_MaterialShaderParameter<MaterialShaderParameter>(engine, "MaterialShaderParameter");
    CollectMembers_MaterialShaderParameter(members);
    RegisterMembers(engine, "MaterialShaderParameter", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_MaterialShaderParameter
        REGISTER_CLASS_MANUAL_PART_MaterialShaderParameter();
    #endif

    // MaterialShaderParameter& MaterialShaderParameter::operator =(const MaterialShaderParameter&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<MaterialShaderParameter>(engine, "MaterialShaderParameter");
}

// Matrix2::Matrix2(const Matrix2& matrix) noexcept = default
static void Matrix2__Matrix2_constspMatrix2amp(Matrix2* _ptr, const Matrix2& matrix)
{
    new(_ptr) Matrix2(matrix);
}

// Matrix2::Matrix2(float v00, float v01, float v10, float v11) noexcept
static void Matrix2__Matrix2_float_float_float_float(Matrix2* _ptr, float v00, float v01, float v10, float v11)
{
    new(_ptr) Matrix2(v00, v01, v10, v11);
}

// class Matrix2 | File: ../Math/Matrix2.h
static void Register_Matrix2(asIScriptEngine* engine)
{
    // explicit Matrix2::Matrix2(const float* data) noexcept
    // Error: type "const float*" can not automatically bind

    // Matrix2::Matrix2(const Matrix2& matrix) noexcept = default
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f(const Matrix2&in)", AS_FUNCTION_OBJFIRST(Matrix2__Matrix2_constspMatrix2amp), AS_CALL_CDECL_OBJFIRST);
    // Matrix2::Matrix2(float v00, float v01, float v10, float v11) noexcept
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", AS_FUNCTION_OBJFIRST(Matrix2__Matrix2_float_float_float_float), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Matrix2<Matrix2>(engine, "Matrix2");
    CollectMembers_Matrix2(members);
    RegisterMembers(engine, "Matrix2", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Matrix2
        REGISTER_CLASS_MANUAL_PART_Matrix2();
    #endif
}

// Matrix3::Matrix3(const Matrix3& matrix) noexcept = default
static void Matrix3__Matrix3_constspMatrix3amp(Matrix3* _ptr, const Matrix3& matrix)
{
    new(_ptr) Matrix3(matrix);
}

// Matrix3::Matrix3(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22) noexcept
static void Matrix3__Matrix3_float_float_float_float_float_float_float_float_float(Matrix3* _ptr, float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22)
{
    new(_ptr) Matrix3(v00, v01, v02, v10, v11, v12, v20, v21, v22);
}

// class Matrix3 | File: ../Math/Matrix3.h
static void Register_Matrix3(asIScriptEngine* engine)
{
    // explicit Matrix3::Matrix3(const float* data) noexcept
    // Error: type "const float*" can not automatically bind

    // Matrix3::Matrix3(const Matrix3& matrix) noexcept = default
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", AS_FUNCTION_OBJFIRST(Matrix3__Matrix3_constspMatrix3amp), AS_CALL_CDECL_OBJFIRST);
    // Matrix3::Matrix3(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22) noexcept
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float)", AS_FUNCTION_OBJFIRST(Matrix3__Matrix3_float_float_float_float_float_float_float_float_float), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Matrix3<Matrix3>(engine, "Matrix3");
    CollectMembers_Matrix3(members);
    RegisterMembers(engine, "Matrix3", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Matrix3
        REGISTER_CLASS_MANUAL_PART_Matrix3();
    #endif
}

// Matrix3x4::Matrix3x4(const Matrix3x4& matrix) noexcept = default
static void Matrix3x4__Matrix3x4_constspMatrix3x4amp(Matrix3x4* _ptr, const Matrix3x4& matrix)
{
    new(_ptr) Matrix3x4(matrix);
}

// explicit Matrix3x4::Matrix3x4(const Matrix3& matrix) noexcept
static void Matrix3x4__Matrix3x4_constspMatrix3amp(Matrix3x4* _ptr, const Matrix3& matrix)
{
    new(_ptr) Matrix3x4(matrix);
}

// explicit Matrix3x4::Matrix3x4(const Matrix4& matrix) noexcept
static void Matrix3x4__Matrix3x4_constspMatrix4amp(Matrix3x4* _ptr, const Matrix4& matrix)
{
    new(_ptr) Matrix3x4(matrix);
}

// Matrix3x4::Matrix3x4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23) noexcept
static void Matrix3x4__Matrix3x4_float_float_float_float_float_float_float_float_float_float_float_float(Matrix3x4* _ptr, float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23)
{
    new(_ptr) Matrix3x4(v00, v01, v02, v03, v10, v11, v12, v13, v20, v21, v22, v23);
}

// Matrix3x4::Matrix3x4(const Vector3& translation, const Quaternion& rotation, float scale) noexcept
static void Matrix3x4__Matrix3x4_constspVector3amp_constspQuaternionamp_float(Matrix3x4* _ptr, const Vector3& translation, const Quaternion& rotation, float scale)
{
    new(_ptr) Matrix3x4(translation, rotation, scale);
}

// Matrix3x4::Matrix3x4(const Vector3& translation, const Quaternion& rotation, const Vector3& scale) noexcept
static void Matrix3x4__Matrix3x4_constspVector3amp_constspQuaternionamp_constspVector3amp(Matrix3x4* _ptr, const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
{
    new(_ptr) Matrix3x4(translation, rotation, scale);
}

// class Matrix3x4 | File: ../Math/Matrix3x4.h
static void Register_Matrix3x4(asIScriptEngine* engine)
{
    // explicit Matrix3x4::Matrix3x4(const float* data) noexcept
    // Error: type "const float*" can not automatically bind

    // Matrix3x4::Matrix3x4(const Matrix3x4& matrix) noexcept = default
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix3x4&in)", AS_FUNCTION_OBJFIRST(Matrix3x4__Matrix3x4_constspMatrix3x4amp), AS_CALL_CDECL_OBJFIRST);
    // explicit Matrix3x4::Matrix3x4(const Matrix3& matrix) noexcept
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", AS_FUNCTION_OBJFIRST(Matrix3x4__Matrix3x4_constspMatrix3amp), AS_CALL_CDECL_OBJFIRST);
    // explicit Matrix3x4::Matrix3x4(const Matrix4& matrix) noexcept
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", AS_FUNCTION_OBJFIRST(Matrix3x4__Matrix3x4_constspMatrix4amp), AS_CALL_CDECL_OBJFIRST);
    // Matrix3x4::Matrix3x4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23) noexcept
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float, float, float, float)", AS_FUNCTION_OBJFIRST(Matrix3x4__Matrix3x4_float_float_float_float_float_float_float_float_float_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // Matrix3x4::Matrix3x4(const Vector3& translation, const Quaternion& rotation, float scale) noexcept
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Quaternion&in, float)", AS_FUNCTION_OBJFIRST(Matrix3x4__Matrix3x4_constspVector3amp_constspQuaternionamp_float), AS_CALL_CDECL_OBJFIRST);
    // Matrix3x4::Matrix3x4(const Vector3& translation, const Quaternion& rotation, const Vector3& scale) noexcept
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Quaternion&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(Matrix3x4__Matrix3x4_constspVector3amp_constspQuaternionamp_constspVector3amp), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Matrix3x4<Matrix3x4>(engine, "Matrix3x4");
    CollectMembers_Matrix3x4(members);
    RegisterMembers(engine, "Matrix3x4", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Matrix3x4
        REGISTER_CLASS_MANUAL_PART_Matrix3x4();
    #endif
}

// Matrix4::Matrix4(const Matrix4& matrix) noexcept
static void Matrix4__Matrix4_constspMatrix4amp(Matrix4* _ptr, const Matrix4& matrix)
{
    new(_ptr) Matrix4(matrix);
}

// explicit Matrix4::Matrix4(const Matrix3& matrix) noexcept
static void Matrix4__Matrix4_constspMatrix3amp(Matrix4* _ptr, const Matrix3& matrix)
{
    new(_ptr) Matrix4(matrix);
}

// Matrix4::Matrix4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33) noexcept
static void Matrix4__Matrix4_float_float_float_float_float_float_float_float_float_float_float_float_float_float_float_float(Matrix4* _ptr, float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33)
{
    new(_ptr) Matrix4(v00, v01, v02, v03, v10, v11, v12, v13, v20, v21, v22, v23, v30, v31, v32, v33);
}

// class Matrix4 | File: ../Math/Matrix4.h
static void Register_Matrix4(asIScriptEngine* engine)
{
    // explicit Matrix4::Matrix4(const float* data) noexcept
    // Error: type "const float*" can not automatically bind

    // Matrix4::Matrix4(const Matrix4& matrix) noexcept
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", AS_FUNCTION_OBJFIRST(Matrix4__Matrix4_constspMatrix4amp), AS_CALL_CDECL_OBJFIRST);
    // explicit Matrix4::Matrix4(const Matrix3& matrix) noexcept
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", AS_FUNCTION_OBJFIRST(Matrix4__Matrix4_constspMatrix3amp), AS_CALL_CDECL_OBJFIRST);
    // Matrix4::Matrix4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33) noexcept
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float)", AS_FUNCTION_OBJFIRST(Matrix4__Matrix4_float_float_float_float_float_float_float_float_float_float_float_float_float_float_float_float), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Matrix4<Matrix4>(engine, "Matrix4");
    CollectMembers_Matrix4(members);
    RegisterMembers(engine, "Matrix4", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Matrix4
        REGISTER_CLASS_MANUAL_PART_Matrix4();
    #endif
}

// struct ModelMorph | File: ../Graphics/Model.h
static void Register_ModelMorph(asIScriptEngine* engine)
{
    // ModelMorph::~ModelMorph() | Implicitly-declared
    engine->RegisterObjectBehaviour("ModelMorph", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ModelMorph), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ModelMorph<ModelMorph>(engine, "ModelMorph");
    CollectMembers_ModelMorph(members);
    RegisterMembers(engine, "ModelMorph", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ModelMorph
        REGISTER_CLASS_MANUAL_PART_ModelMorph();
    #endif

    // ModelMorph& ModelMorph::operator =(const ModelMorph&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ModelMorph>(engine, "ModelMorph");
}

// class Mutex | File: ../Core/Mutex.h
static void Register_Mutex(asIScriptEngine* engine)
{
    // Mutex::~Mutex()
    engine->RegisterObjectBehaviour("Mutex", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(Mutex), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Mutex<Mutex>(engine, "Mutex");
    CollectMembers_Mutex(members);
    RegisterMembers(engine, "Mutex", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Mutex
        REGISTER_CLASS_MANUAL_PART_Mutex();
    #endif

    // Mutex& Mutex::operator =(const Mutex&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Mutex>(engine, "Mutex");
}

// explicit MutexLock::MutexLock(Mutex& mutex)
static void MutexLock__MutexLock_Mutexamp(MutexLock* _ptr, Mutex& mutex)
{
    new(_ptr) MutexLock(mutex);
}

// class MutexLock | File: ../Core/Mutex.h
static void Register_MutexLock(asIScriptEngine* engine)
{
    // MutexLock::MutexLock(const MutexLock& rhs) = delete
    // Not registered because deleted

    // explicit MutexLock::MutexLock(Mutex& mutex)
    engine->RegisterObjectBehaviour("MutexLock", asBEHAVE_CONSTRUCT, "void f(Mutex&)", AS_FUNCTION_OBJFIRST(MutexLock__MutexLock_Mutexamp), AS_CALL_CDECL_OBJFIRST);

    // MutexLock::~MutexLock()
    engine->RegisterObjectBehaviour("MutexLock", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(MutexLock), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_MutexLock<MutexLock>(engine, "MutexLock");
    CollectMembers_MutexLock(members);
    RegisterMembers(engine, "MutexLock", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_MutexLock
        REGISTER_CLASS_MANUAL_PART_MutexLock();
    #endif
}

// struct NetworkState | File: ../Scene/ReplicationState.h
static void Register_NetworkState(asIScriptEngine* engine)
{
    // NetworkState::~NetworkState() | Implicitly-declared
    engine->RegisterObjectBehaviour("NetworkState", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(NetworkState), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_NetworkState<NetworkState>(engine, "NetworkState");
    CollectMembers_NetworkState(members);
    RegisterMembers(engine, "NetworkState", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_NetworkState
        REGISTER_CLASS_MANUAL_PART_NetworkState();
    #endif

    // NetworkState& NetworkState::operator =(const NetworkState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<NetworkState>(engine, "NetworkState");
}

// struct NodeImpl | File: ../Scene/Node.h
static void Register_NodeImpl(asIScriptEngine* engine)
{
    // NodeImpl::~NodeImpl() | Implicitly-declared
    engine->RegisterObjectBehaviour("NodeImpl", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(NodeImpl), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_NodeImpl<NodeImpl>(engine, "NodeImpl");
    CollectMembers_NodeImpl(members);
    RegisterMembers(engine, "NodeImpl", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_NodeImpl
        REGISTER_CLASS_MANUAL_PART_NodeImpl();
    #endif

    // NodeImpl& NodeImpl::operator =(const NodeImpl&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<NodeImpl>(engine, "NodeImpl");
}

// struct OcclusionBatch | File: ../Graphics/OcclusionBuffer.h
static void Register_OcclusionBatch(asIScriptEngine* engine)
{
    // OcclusionBatch::~OcclusionBatch() | Implicitly-declared
    engine->RegisterObjectBehaviour("OcclusionBatch", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(OcclusionBatch), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_OcclusionBatch<OcclusionBatch>(engine, "OcclusionBatch");
    CollectMembers_OcclusionBatch(members);
    RegisterMembers(engine, "OcclusionBatch", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_OcclusionBatch
        REGISTER_CLASS_MANUAL_PART_OcclusionBatch();
    #endif

    // OcclusionBatch& OcclusionBatch::operator =(const OcclusionBatch&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<OcclusionBatch>(engine, "OcclusionBatch");
}

// struct OcclusionBufferData | File: ../Graphics/OcclusionBuffer.h
static void Register_OcclusionBufferData(asIScriptEngine* engine)
{
    // OcclusionBufferData::~OcclusionBufferData() | Implicitly-declared
    engine->RegisterObjectBehaviour("OcclusionBufferData", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(OcclusionBufferData), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_OcclusionBufferData<OcclusionBufferData>(engine, "OcclusionBufferData");
    CollectMembers_OcclusionBufferData(members);
    RegisterMembers(engine, "OcclusionBufferData", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_OcclusionBufferData
        REGISTER_CLASS_MANUAL_PART_OcclusionBufferData();
    #endif

    // OcclusionBufferData& OcclusionBufferData::operator =(const OcclusionBufferData&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<OcclusionBufferData>(engine, "OcclusionBufferData");
}

// struct OctreeQueryResult | File: ../Graphics/OctreeQuery.h
static void Register_OctreeQueryResult(asIScriptEngine* engine)
{
    // OctreeQueryResult::~OctreeQueryResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("OctreeQueryResult", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(OctreeQueryResult), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_OctreeQueryResult<OctreeQueryResult>(engine, "OctreeQueryResult");
    CollectMembers_OctreeQueryResult(members);
    RegisterMembers(engine, "OctreeQueryResult", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_OctreeQueryResult
        REGISTER_CLASS_MANUAL_PART_OctreeQueryResult();
    #endif

    // OctreeQueryResult& OctreeQueryResult::operator =(const OctreeQueryResult&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<OctreeQueryResult>(engine, "OctreeQueryResult");
}

// struct PackageEntry | File: ../IO/PackageFile.h
static void Register_PackageEntry(asIScriptEngine* engine)
{
    MemberCollection members;
    RegisterMembers_PackageEntry<PackageEntry>(engine, "PackageEntry");
    CollectMembers_PackageEntry(members);
    RegisterMembers(engine, "PackageEntry", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_PackageEntry
        REGISTER_CLASS_MANUAL_PART_PackageEntry();
    #endif

    // PackageEntry& PackageEntry::operator =(const PackageEntry&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<PackageEntry>(engine, "PackageEntry");
}

// struct Particle | File: ../Graphics/ParticleEmitter.h
static void Register_Particle(asIScriptEngine* engine)
{
    // Particle::~Particle() | Implicitly-declared
    engine->RegisterObjectBehaviour("Particle", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(Particle), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Particle<Particle>(engine, "Particle");
    CollectMembers_Particle(members);
    RegisterMembers(engine, "Particle", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Particle
        REGISTER_CLASS_MANUAL_PART_Particle();
    #endif

    // Particle& Particle::operator =(const Particle&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Particle>(engine, "Particle");
}

// struct PerThreadSceneResult | File: ../Graphics/View.h
static void Register_PerThreadSceneResult(asIScriptEngine* engine)
{
    // PerThreadSceneResult::~PerThreadSceneResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("PerThreadSceneResult", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(PerThreadSceneResult), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_PerThreadSceneResult<PerThreadSceneResult>(engine, "PerThreadSceneResult");
    CollectMembers_PerThreadSceneResult(members);
    RegisterMembers(engine, "PerThreadSceneResult", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_PerThreadSceneResult
        REGISTER_CLASS_MANUAL_PART_PerThreadSceneResult();
    #endif

    // PerThreadSceneResult& PerThreadSceneResult::operator =(const PerThreadSceneResult&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<PerThreadSceneResult>(engine, "PerThreadSceneResult");
}

// Plane::Plane(const Plane& plane) noexcept = default
static void Plane__Plane_constspPlaneamp(Plane* _ptr, const Plane& plane)
{
    new(_ptr) Plane(plane);
}

// Plane::Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2) noexcept
static void Plane__Plane_constspVector3amp_constspVector3amp_constspVector3amp(Plane* _ptr, const Vector3& v0, const Vector3& v1, const Vector3& v2)
{
    new(_ptr) Plane(v0, v1, v2);
}

// Plane::Plane(const Vector3& normal, const Vector3& point) noexcept
static void Plane__Plane_constspVector3amp_constspVector3amp(Plane* _ptr, const Vector3& normal, const Vector3& point)
{
    new(_ptr) Plane(normal, point);
}

// explicit Plane::Plane(const Vector4& plane) noexcept
static void Plane__Plane_constspVector4amp(Plane* _ptr, const Vector4& plane)
{
    new(_ptr) Plane(plane);
}

// class Plane | File: ../Math/Plane.h
static void Register_Plane(asIScriptEngine* engine)
{
    // Plane::Plane(const Plane& plane) noexcept = default
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Plane&in)", AS_FUNCTION_OBJFIRST(Plane__Plane_constspPlaneamp), AS_CALL_CDECL_OBJFIRST);
    // Plane::Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2) noexcept
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(Plane__Plane_constspVector3amp_constspVector3amp_constspVector3amp), AS_CALL_CDECL_OBJFIRST);
    // Plane::Plane(const Vector3& normal, const Vector3& point) noexcept
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(Plane__Plane_constspVector3amp_constspVector3amp), AS_CALL_CDECL_OBJFIRST);
    // explicit Plane::Plane(const Vector4& plane) noexcept
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", AS_FUNCTION_OBJFIRST(Plane__Plane_constspVector4amp), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Plane<Plane>(engine, "Plane");
    CollectMembers_Plane(members);
    RegisterMembers(engine, "Plane", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Plane
        REGISTER_CLASS_MANUAL_PART_Plane();
    #endif
}

// Polyhedron::Polyhedron(const Polyhedron& polyhedron)
static void Polyhedron__Polyhedron_constspPolyhedronamp(Polyhedron* _ptr, const Polyhedron& polyhedron)
{
    new(_ptr) Polyhedron(polyhedron);
}

// explicit Polyhedron::Polyhedron(const BoundingBox& box)
static void Polyhedron__Polyhedron_constspBoundingBoxamp(Polyhedron* _ptr, const BoundingBox& box)
{
    new(_ptr) Polyhedron(box);
}

// explicit Polyhedron::Polyhedron(const Frustum& frustum)
static void Polyhedron__Polyhedron_constspFrustumamp(Polyhedron* _ptr, const Frustum& frustum)
{
    new(_ptr) Polyhedron(frustum);
}

// class Polyhedron | File: ../Math/Polyhedron.h
static void Register_Polyhedron(asIScriptEngine* engine)
{
    // explicit Polyhedron::Polyhedron(const Vector<PODVector<Vector3>>& faces)
    // Error: type "const Vector<PODVector<Vector3>>&" can not automatically bind

    // Polyhedron::Polyhedron(const Polyhedron& polyhedron)
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", AS_FUNCTION_OBJFIRST(Polyhedron__Polyhedron_constspPolyhedronamp), AS_CALL_CDECL_OBJFIRST);
    // explicit Polyhedron::Polyhedron(const BoundingBox& box)
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", AS_FUNCTION_OBJFIRST(Polyhedron__Polyhedron_constspBoundingBoxamp), AS_CALL_CDECL_OBJFIRST);
    // explicit Polyhedron::Polyhedron(const Frustum& frustum)
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", AS_FUNCTION_OBJFIRST(Polyhedron__Polyhedron_constspFrustumamp), AS_CALL_CDECL_OBJFIRST);

    // Polyhedron::~Polyhedron() noexcept = default
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(Polyhedron), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Polyhedron<Polyhedron>(engine, "Polyhedron");
    CollectMembers_Polyhedron(members);
    RegisterMembers(engine, "Polyhedron", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Polyhedron
        REGISTER_CLASS_MANUAL_PART_Polyhedron();
    #endif
}

// Quaternion::Quaternion(const Quaternion& quat) noexcept
static void Quaternion__Quaternion_constspQuaternionamp(Quaternion* _ptr, const Quaternion& quat)
{
    new(_ptr) Quaternion(quat);
}

// Quaternion::Quaternion(float w, float x, float y, float z) noexcept
static void Quaternion__Quaternion_float_float_float_float(Quaternion* _ptr, float w, float x, float y, float z)
{
    new(_ptr) Quaternion(w, x, y, z);
}

// Quaternion::Quaternion(float angle, const Vector3& axis) noexcept
static void Quaternion__Quaternion_float_constspVector3amp(Quaternion* _ptr, float angle, const Vector3& axis)
{
    new(_ptr) Quaternion(angle, axis);
}

// explicit Quaternion::Quaternion(float angle) noexcept
static void Quaternion__Quaternion_float(Quaternion* _ptr, float angle)
{
    new(_ptr) Quaternion(angle);
}

// Quaternion::Quaternion(float x, float y, float z) noexcept
static void Quaternion__Quaternion_float_float_float(Quaternion* _ptr, float x, float y, float z)
{
    new(_ptr) Quaternion(x, y, z);
}

// explicit Quaternion::Quaternion(const Vector3& angles) noexcept
static void Quaternion__Quaternion_constspVector3amp(Quaternion* _ptr, const Vector3& angles)
{
    new(_ptr) Quaternion(angles);
}

// Quaternion::Quaternion(const Vector3& start, const Vector3& end) noexcept
static void Quaternion__Quaternion_constspVector3amp_constspVector3amp(Quaternion* _ptr, const Vector3& start, const Vector3& end)
{
    new(_ptr) Quaternion(start, end);
}

// Quaternion::Quaternion(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis) noexcept
static void Quaternion__Quaternion_constspVector3amp_constspVector3amp_constspVector3amp(Quaternion* _ptr, const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
{
    new(_ptr) Quaternion(xAxis, yAxis, zAxis);
}

// explicit Quaternion::Quaternion(const Matrix3& matrix) noexcept
static void Quaternion__Quaternion_constspMatrix3amp(Quaternion* _ptr, const Matrix3& matrix)
{
    new(_ptr) Quaternion(matrix);
}

// class Quaternion | File: ../Math/Quaternion.h
static void Register_Quaternion(asIScriptEngine* engine)
{
    // explicit Quaternion::Quaternion(const float* data) noexcept
    // Error: type "const float*" can not automatically bind

    // Quaternion::Quaternion(const Quaternion& quat) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Quaternion&in)", AS_FUNCTION_OBJFIRST(Quaternion__Quaternion_constspQuaternionamp), AS_CALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(float w, float x, float y, float z) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", AS_FUNCTION_OBJFIRST(Quaternion__Quaternion_float_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(float angle, const Vector3& axis) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, const Vector3&in)", AS_FUNCTION_OBJFIRST(Quaternion__Quaternion_float_constspVector3amp), AS_CALL_CDECL_OBJFIRST);
    // explicit Quaternion::Quaternion(float angle) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float)", AS_FUNCTION_OBJFIRST(Quaternion__Quaternion_float), AS_CALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(float x, float y, float z) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float)", AS_FUNCTION_OBJFIRST(Quaternion__Quaternion_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Quaternion::Quaternion(const Vector3& angles) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", AS_FUNCTION_OBJFIRST(Quaternion__Quaternion_constspVector3amp), AS_CALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(const Vector3& start, const Vector3& end) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(Quaternion__Quaternion_constspVector3amp_constspVector3amp), AS_CALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(Quaternion__Quaternion_constspVector3amp_constspVector3amp_constspVector3amp), AS_CALL_CDECL_OBJFIRST);
    // explicit Quaternion::Quaternion(const Matrix3& matrix) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", AS_FUNCTION_OBJFIRST(Quaternion__Quaternion_constspMatrix3amp), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Quaternion<Quaternion>(engine, "Quaternion");
    CollectMembers_Quaternion(members);
    RegisterMembers(engine, "Quaternion", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Quaternion
        REGISTER_CLASS_MANUAL_PART_Quaternion();
    #endif
}

// Ray::Ray(const Vector3& origin, const Vector3& direction) noexcept
static void Ray__Ray_constspVector3amp_constspVector3amp(Ray* _ptr, const Vector3& origin, const Vector3& direction)
{
    new(_ptr) Ray(origin, direction);
}

// Ray::Ray(const Ray& ray) noexcept = default
static void Ray__Ray_constspRayamp(Ray* _ptr, const Ray& ray)
{
    new(_ptr) Ray(ray);
}

// class Ray | File: ../Math/Ray.h
static void Register_Ray(asIScriptEngine* engine)
{
    // Ray::Ray(const Vector3& origin, const Vector3& direction) noexcept
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(Ray__Ray_constspVector3amp_constspVector3amp), AS_CALL_CDECL_OBJFIRST);
    // Ray::Ray(const Ray& ray) noexcept = default
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f(const Ray&in)", AS_FUNCTION_OBJFIRST(Ray__Ray_constspRayamp), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Ray<Ray>(engine, "Ray");
    CollectMembers_Ray(members);
    RegisterMembers(engine, "Ray", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Ray
        REGISTER_CLASS_MANUAL_PART_Ray();
    #endif
}

// struct RayQueryResult | File: ../Graphics/OctreeQuery.h
static void Register_RayQueryResult(asIScriptEngine* engine)
{
    // RayQueryResult::~RayQueryResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("RayQueryResult", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(RayQueryResult), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_RayQueryResult<RayQueryResult>(engine, "RayQueryResult");
    CollectMembers_RayQueryResult(members);
    RegisterMembers(engine, "RayQueryResult", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_RayQueryResult
        REGISTER_CLASS_MANUAL_PART_RayQueryResult();
    #endif

    // RayQueryResult& RayQueryResult::operator =(const RayQueryResult&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<RayQueryResult>(engine, "RayQueryResult");
}

// Rect::Rect(const Vector2& min, const Vector2& max) noexcept
static void Rect__Rect_constspVector2amp_constspVector2amp(Rect* _ptr, const Vector2& min, const Vector2& max)
{
    new(_ptr) Rect(min, max);
}

// Rect::Rect(float left, float top, float right, float bottom) noexcept
static void Rect__Rect_float_float_float_float(Rect* _ptr, float left, float top, float right, float bottom)
{
    new(_ptr) Rect(left, top, right, bottom);
}

// explicit Rect::Rect(const Vector4& vector) noexcept
static void Rect__Rect_constspVector4amp(Rect* _ptr, const Vector4& vector)
{
    new(_ptr) Rect(vector);
}

// Rect::Rect(const Rect& rect) noexcept = default
static void Rect__Rect_constspRectamp(Rect* _ptr, const Rect& rect)
{
    new(_ptr) Rect(rect);
}

// class Rect | File: ../Math/Rect.h
static void Register_Rect(asIScriptEngine* engine)
{
    // explicit Rect::Rect(const float* data) noexcept
    // Error: type "const float*" can not automatically bind

    // Rect::Rect(const Vector2& min, const Vector2& max) noexcept
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Vector2&in, const Vector2&in)", AS_FUNCTION_OBJFIRST(Rect__Rect_constspVector2amp_constspVector2amp), AS_CALL_CDECL_OBJFIRST);
    // Rect::Rect(float left, float top, float right, float bottom) noexcept
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", AS_FUNCTION_OBJFIRST(Rect__Rect_float_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Rect::Rect(const Vector4& vector) noexcept
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", AS_FUNCTION_OBJFIRST(Rect__Rect_constspVector4amp), AS_CALL_CDECL_OBJFIRST);
    // Rect::Rect(const Rect& rect) noexcept = default
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Rect&in)", AS_FUNCTION_OBJFIRST(Rect__Rect_constspRectamp), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Rect<Rect>(engine, "Rect");
    CollectMembers_Rect(members);
    RegisterMembers(engine, "Rect", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Rect
        REGISTER_CLASS_MANUAL_PART_Rect();
    #endif
}

// struct RefCount | File: ../Container/RefCounted.h
static void Register_RefCount(asIScriptEngine* engine)
{
    // RefCount::~RefCount()
    engine->RegisterObjectBehaviour("RefCount", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(RefCount), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_RefCount<RefCount>(engine, "RefCount");
    CollectMembers_RefCount(members);
    RegisterMembers(engine, "RefCount", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_RefCount
        REGISTER_CLASS_MANUAL_PART_RefCount();
    #endif

    // RefCount& RefCount::operator =(const RefCount&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<RefCount>(engine, "RefCount");
}

// class RefCounted | File: ../Container/RefCounted.h
static void Register_RefCounted(asIScriptEngine* engine)
{
    // RefCounted::RefCounted(const RefCounted& rhs) = delete
    // Not registered because deleted

    MemberCollection members;
    RegisterMembers_RefCounted<RefCounted>(engine, "RefCounted");
    CollectMembers_RefCounted(members);
    RegisterMembers(engine, "RefCounted", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_RefCounted
        REGISTER_CLASS_MANUAL_PART_RefCounted();
    #endif
}

// struct RenderPathCommand | File: ../Graphics/RenderPath.h
static void Register_RenderPathCommand(asIScriptEngine* engine)
{
    // RenderPathCommand::~RenderPathCommand() | Implicitly-declared
    engine->RegisterObjectBehaviour("RenderPathCommand", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(RenderPathCommand), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_RenderPathCommand<RenderPathCommand>(engine, "RenderPathCommand");
    CollectMembers_RenderPathCommand(members);
    RegisterMembers(engine, "RenderPathCommand", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_RenderPathCommand
        REGISTER_CLASS_MANUAL_PART_RenderPathCommand();
    #endif

    // RenderPathCommand& RenderPathCommand::operator =(const RenderPathCommand&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<RenderPathCommand>(engine, "RenderPathCommand");
}

// struct RenderTargetInfo | File: ../Graphics/RenderPath.h
static void Register_RenderTargetInfo(asIScriptEngine* engine)
{
    // RenderTargetInfo::~RenderTargetInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("RenderTargetInfo", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(RenderTargetInfo), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_RenderTargetInfo<RenderTargetInfo>(engine, "RenderTargetInfo");
    CollectMembers_RenderTargetInfo(members);
    RegisterMembers(engine, "RenderTargetInfo", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_RenderTargetInfo
        REGISTER_CLASS_MANUAL_PART_RenderTargetInfo();
    #endif

    // RenderTargetInfo& RenderTargetInfo::operator =(const RenderTargetInfo&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<RenderTargetInfo>(engine, "RenderTargetInfo");
}

// struct ReplicationState | File: ../Scene/ReplicationState.h
static void Register_ReplicationState(asIScriptEngine* engine)
{
    // ReplicationState::~ReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("ReplicationState", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ReplicationState), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ReplicationState<ReplicationState>(engine, "ReplicationState");
    CollectMembers_ReplicationState(members);
    RegisterMembers(engine, "ReplicationState", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ReplicationState
        REGISTER_CLASS_MANUAL_PART_ReplicationState();
    #endif

    // ReplicationState& ReplicationState::operator =(const ReplicationState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ReplicationState>(engine, "ReplicationState");
}

// struct ResourceGroup | File: ../Resource/ResourceCache.h
static void Register_ResourceGroup(asIScriptEngine* engine)
{
    // ResourceGroup::~ResourceGroup() | Implicitly-declared
    engine->RegisterObjectBehaviour("ResourceGroup", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ResourceGroup), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ResourceGroup<ResourceGroup>(engine, "ResourceGroup");
    CollectMembers_ResourceGroup(members);
    RegisterMembers(engine, "ResourceGroup", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ResourceGroup
        REGISTER_CLASS_MANUAL_PART_ResourceGroup();
    #endif

    // ResourceGroup& ResourceGroup::operator =(const ResourceGroup&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ResourceGroup>(engine, "ResourceGroup");
}

// explicit ResourceRef::ResourceRef(StringHash type)
static void ResourceRef__ResourceRef_StringHash(ResourceRef* _ptr, StringHash type)
{
    new(_ptr) ResourceRef(type);
}

// ResourceRef::ResourceRef(StringHash type, const String& name)
static void ResourceRef__ResourceRef_StringHash_constspStringamp(ResourceRef* _ptr, StringHash type, const String& name)
{
    new(_ptr) ResourceRef(type, name);
}

// ResourceRef::ResourceRef(const String& type, const String& name)
static void ResourceRef__ResourceRef_constspStringamp_constspStringamp(ResourceRef* _ptr, const String& type, const String& name)
{
    new(_ptr) ResourceRef(type, name);
}

// ResourceRef::ResourceRef(const ResourceRef& rhs) = default
static void ResourceRef__ResourceRef_constspResourceRefamp(ResourceRef* _ptr, const ResourceRef& rhs)
{
    new(_ptr) ResourceRef(rhs);
}

// struct ResourceRef | File: ../Core/Variant.h
static void Register_ResourceRef(asIScriptEngine* engine)
{
    // ResourceRef::ResourceRef(const char* type, const char* name)
    // Error: type "const char*" can not automatically bind

    // explicit ResourceRef::ResourceRef(StringHash type)
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f(StringHash)", AS_FUNCTION_OBJFIRST(ResourceRef__ResourceRef_StringHash), AS_CALL_CDECL_OBJFIRST);
    // ResourceRef::ResourceRef(StringHash type, const String& name)
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f(StringHash, const String&in)", AS_FUNCTION_OBJFIRST(ResourceRef__ResourceRef_StringHash_constspStringamp), AS_CALL_CDECL_OBJFIRST);
    // ResourceRef::ResourceRef(const String& type, const String& name)
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f(const String&in, const String&in)", AS_FUNCTION_OBJFIRST(ResourceRef__ResourceRef_constspStringamp_constspStringamp), AS_CALL_CDECL_OBJFIRST);
    // ResourceRef::ResourceRef(const ResourceRef& rhs) = default
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f(const ResourceRef&in)", AS_FUNCTION_OBJFIRST(ResourceRef__ResourceRef_constspResourceRefamp), AS_CALL_CDECL_OBJFIRST);

    // ResourceRef::~ResourceRef() | Implicitly-declared
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ResourceRef), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ResourceRef<ResourceRef>(engine, "ResourceRef");
    CollectMembers_ResourceRef(members);
    RegisterMembers(engine, "ResourceRef", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ResourceRef
        REGISTER_CLASS_MANUAL_PART_ResourceRef();
    #endif

    // ResourceRef& ResourceRef::operator =(const ResourceRef&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ResourceRef>(engine, "ResourceRef");
}

// explicit ResourceRefList::ResourceRefList(StringHash type)
static void ResourceRefList__ResourceRefList_StringHash(ResourceRefList* _ptr, StringHash type)
{
    new(_ptr) ResourceRefList(type);
}

// ResourceRefList::ResourceRefList(StringHash type, const StringVector& names)
static void ResourceRefList__ResourceRefList_StringHash_constspStringVectoramp(ResourceRefList* _ptr, StringHash type, CScriptArray* names_conv)
{
    StringVector names = ArrayToVector<String>(names_conv);
    new(_ptr) ResourceRefList(type, names);
}

// struct ResourceRefList | File: ../Core/Variant.h
static void Register_ResourceRefList(asIScriptEngine* engine)
{
    // explicit ResourceRefList::ResourceRefList(StringHash type)
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_CONSTRUCT, "void f(StringHash)", AS_FUNCTION_OBJFIRST(ResourceRefList__ResourceRefList_StringHash), AS_CALL_CDECL_OBJFIRST);
    // ResourceRefList::ResourceRefList(StringHash type, const StringVector& names)
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_CONSTRUCT, "void f(StringHash, Array<String>@+)", AS_FUNCTION_OBJFIRST(ResourceRefList__ResourceRefList_StringHash_constspStringVectoramp), AS_CALL_CDECL_OBJFIRST);

    // ResourceRefList::~ResourceRefList() | Implicitly-declared
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ResourceRefList), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ResourceRefList<ResourceRefList>(engine, "ResourceRefList");
    CollectMembers_ResourceRefList(members);
    RegisterMembers(engine, "ResourceRefList", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ResourceRefList
        REGISTER_CLASS_MANUAL_PART_ResourceRefList();
    #endif

    // ResourceRefList& ResourceRefList::operator =(const ResourceRefList&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ResourceRefList>(engine, "ResourceRefList");
}

// struct ScenePassInfo | File: ../Graphics/View.h
static void Register_ScenePassInfo(asIScriptEngine* engine)
{
    // ScenePassInfo::~ScenePassInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("ScenePassInfo", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ScenePassInfo), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ScenePassInfo<ScenePassInfo>(engine, "ScenePassInfo");
    CollectMembers_ScenePassInfo(members);
    RegisterMembers(engine, "ScenePassInfo", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ScenePassInfo
        REGISTER_CLASS_MANUAL_PART_ScenePassInfo();
    #endif

    // ScenePassInfo& ScenePassInfo::operator =(const ScenePassInfo&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ScenePassInfo>(engine, "ScenePassInfo");
}

// class SceneResolver | File: ../Scene/SceneResolver.h
static void Register_SceneResolver(asIScriptEngine* engine)
{
    // SceneResolver::~SceneResolver()
    engine->RegisterObjectBehaviour("SceneResolver", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(SceneResolver), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_SceneResolver<SceneResolver>(engine, "SceneResolver");
    CollectMembers_SceneResolver(members);
    RegisterMembers(engine, "SceneResolver", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_SceneResolver
        REGISTER_CLASS_MANUAL_PART_SceneResolver();
    #endif

    // SceneResolver& SceneResolver::operator =(const SceneResolver&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<SceneResolver>(engine, "SceneResolver");
}

// struct ScratchBuffer | File: ../Graphics/Graphics.h
static void Register_ScratchBuffer(asIScriptEngine* engine)
{
    // ScratchBuffer::~ScratchBuffer() | Implicitly-declared
    engine->RegisterObjectBehaviour("ScratchBuffer", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ScratchBuffer), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ScratchBuffer<ScratchBuffer>(engine, "ScratchBuffer");
    CollectMembers_ScratchBuffer(members);
    RegisterMembers(engine, "ScratchBuffer", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ScratchBuffer
        REGISTER_CLASS_MANUAL_PART_ScratchBuffer();
    #endif

    // ScratchBuffer& ScratchBuffer::operator =(const ScratchBuffer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ScratchBuffer>(engine, "ScratchBuffer");
}

// struct ScreenModeParams | File: ../Graphics/Graphics.h
static void Register_ScreenModeParams(asIScriptEngine* engine)
{
    // ScreenModeParams::~ScreenModeParams() | Implicitly-declared
    engine->RegisterObjectBehaviour("ScreenModeParams", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ScreenModeParams), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ScreenModeParams<ScreenModeParams>(engine, "ScreenModeParams");
    CollectMembers_ScreenModeParams(members);
    RegisterMembers(engine, "ScreenModeParams", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ScreenModeParams
        REGISTER_CLASS_MANUAL_PART_ScreenModeParams();
    #endif

    // ScreenModeParams& ScreenModeParams::operator =(const ScreenModeParams&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ScreenModeParams>(engine, "ScreenModeParams");
}

// class Serializer | File: ../IO/Serializer.h
static void Register_Serializer(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("Serializer", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Serializer", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);

    MemberCollection members;
    RegisterMembers_Serializer<Serializer>(engine, "Serializer");
    CollectMembers_Serializer(members);
    RegisterMembers(engine, "Serializer", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Serializer
        REGISTER_CLASS_MANUAL_PART_Serializer();
    #endif

    // Serializer& Serializer::operator =(const Serializer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Serializer>(engine, "Serializer");
}

// ShaderParameter::ShaderParameter(const String& name, unsigned glType, int location)
static void ShaderParameter__ShaderParameter_constspStringamp_unsigned_int(ShaderParameter* _ptr, const String& name, unsigned glType, int location)
{
    new(_ptr) ShaderParameter(name, glType, location);
}

// ShaderParameter::ShaderParameter(ShaderType type, const String& name, unsigned offset, unsigned size, unsigned buffer)
static void ShaderParameter__ShaderParameter_ShaderType_constspStringamp_unsigned_unsigned_unsigned(ShaderParameter* _ptr, ShaderType type, const String& name, unsigned offset, unsigned size, unsigned buffer)
{
    new(_ptr) ShaderParameter(type, name, offset, size, buffer);
}

// ShaderParameter::ShaderParameter(ShaderType type, const String& name, unsigned reg, unsigned regCount)
static void ShaderParameter__ShaderParameter_ShaderType_constspStringamp_unsigned_unsigned(ShaderParameter* _ptr, ShaderType type, const String& name, unsigned reg, unsigned regCount)
{
    new(_ptr) ShaderParameter(type, name, reg, regCount);
}

// struct ShaderParameter | File: ../Graphics/ShaderVariation.h
static void Register_ShaderParameter(asIScriptEngine* engine)
{
    // ShaderParameter::ShaderParameter(const String& name, unsigned glType, int location)
    engine->RegisterObjectBehaviour("ShaderParameter", asBEHAVE_CONSTRUCT, "void f(const String&in, uint, int)", AS_FUNCTION_OBJFIRST(ShaderParameter__ShaderParameter_constspStringamp_unsigned_int), AS_CALL_CDECL_OBJFIRST);
    // ShaderParameter::ShaderParameter(ShaderType type, const String& name, unsigned offset, unsigned size, unsigned buffer)
    engine->RegisterObjectBehaviour("ShaderParameter", asBEHAVE_CONSTRUCT, "void f(ShaderType, const String&in, uint, uint, uint)", AS_FUNCTION_OBJFIRST(ShaderParameter__ShaderParameter_ShaderType_constspStringamp_unsigned_unsigned_unsigned), AS_CALL_CDECL_OBJFIRST);
    // ShaderParameter::ShaderParameter(ShaderType type, const String& name, unsigned reg, unsigned regCount)
    engine->RegisterObjectBehaviour("ShaderParameter", asBEHAVE_CONSTRUCT, "void f(ShaderType, const String&in, uint, uint)", AS_FUNCTION_OBJFIRST(ShaderParameter__ShaderParameter_ShaderType_constspStringamp_unsigned_unsigned), AS_CALL_CDECL_OBJFIRST);

    // ShaderParameter::~ShaderParameter() | Implicitly-declared
    engine->RegisterObjectBehaviour("ShaderParameter", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ShaderParameter), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ShaderParameter<ShaderParameter>(engine, "ShaderParameter");
    CollectMembers_ShaderParameter(members);
    RegisterMembers(engine, "ShaderParameter", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ShaderParameter
        REGISTER_CLASS_MANUAL_PART_ShaderParameter();
    #endif

    // ShaderParameter& ShaderParameter::operator =(const ShaderParameter&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ShaderParameter>(engine, "ShaderParameter");
}

// struct ShadowBatchQueue | File: ../Graphics/Batch.h
static void Register_ShadowBatchQueue(asIScriptEngine* engine)
{
    // ShadowBatchQueue::~ShadowBatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("ShadowBatchQueue", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ShadowBatchQueue), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ShadowBatchQueue<ShadowBatchQueue>(engine, "ShadowBatchQueue");
    CollectMembers_ShadowBatchQueue(members);
    RegisterMembers(engine, "ShadowBatchQueue", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ShadowBatchQueue
        REGISTER_CLASS_MANUAL_PART_ShadowBatchQueue();
    #endif

    // ShadowBatchQueue& ShadowBatchQueue::operator =(const ShadowBatchQueue&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ShadowBatchQueue>(engine, "ShadowBatchQueue");
}

// class Skeleton | File: ../Graphics/Skeleton.h
static void Register_Skeleton(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("Skeleton", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Skeleton", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);

    MemberCollection members;
    RegisterMembers_Skeleton<Skeleton>(engine, "Skeleton");
    CollectMembers_Skeleton(members);
    RegisterMembers(engine, "Skeleton", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Skeleton
        REGISTER_CLASS_MANUAL_PART_Skeleton();
    #endif

    // Skeleton& Skeleton::operator =(const Skeleton&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Skeleton>(engine, "Skeleton");
}

// SourceBatch::SourceBatch(const SourceBatch& batch)
static void SourceBatch__SourceBatch_constspSourceBatchamp(SourceBatch* _ptr, const SourceBatch& batch)
{
    new(_ptr) SourceBatch(batch);
}

// struct SourceBatch | File: ../Graphics/Drawable.h
static void Register_SourceBatch(asIScriptEngine* engine)
{
    // SourceBatch::SourceBatch(const SourceBatch& batch)
    engine->RegisterObjectBehaviour("SourceBatch", asBEHAVE_CONSTRUCT, "void f(const SourceBatch&in)", AS_FUNCTION_OBJFIRST(SourceBatch__SourceBatch_constspSourceBatchamp), AS_CALL_CDECL_OBJFIRST);

    // SourceBatch::~SourceBatch()
    engine->RegisterObjectBehaviour("SourceBatch", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(SourceBatch), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_SourceBatch<SourceBatch>(engine, "SourceBatch");
    CollectMembers_SourceBatch(members);
    RegisterMembers(engine, "SourceBatch", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_SourceBatch
        REGISTER_CLASS_MANUAL_PART_SourceBatch();
    #endif
}

// Sphere::Sphere(const Sphere& sphere) noexcept = default
static void Sphere__Sphere_constspSphereamp(Sphere* _ptr, const Sphere& sphere)
{
    new(_ptr) Sphere(sphere);
}

// Sphere::Sphere(const Vector3& center, float radius) noexcept
static void Sphere__Sphere_constspVector3amp_float(Sphere* _ptr, const Vector3& center, float radius)
{
    new(_ptr) Sphere(center, radius);
}

// explicit Sphere::Sphere(const BoundingBox& box) noexcept
static void Sphere__Sphere_constspBoundingBoxamp(Sphere* _ptr, const BoundingBox& box)
{
    new(_ptr) Sphere(box);
}

// explicit Sphere::Sphere(const Frustum& frustum) noexcept
static void Sphere__Sphere_constspFrustumamp(Sphere* _ptr, const Frustum& frustum)
{
    new(_ptr) Sphere(frustum);
}

// explicit Sphere::Sphere(const Polyhedron& poly) noexcept
static void Sphere__Sphere_constspPolyhedronamp(Sphere* _ptr, const Polyhedron& poly)
{
    new(_ptr) Sphere(poly);
}

// class Sphere | File: ../Math/Sphere.h
static void Register_Sphere(asIScriptEngine* engine)
{
    // Sphere::Sphere(const Vector3* vertices, unsigned count) noexcept
    // Error: type "const Vector3*" can not automatically bind

    // Sphere::Sphere(const Sphere& sphere) noexcept = default
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Sphere&in)", AS_FUNCTION_OBJFIRST(Sphere__Sphere_constspSphereamp), AS_CALL_CDECL_OBJFIRST);
    // Sphere::Sphere(const Vector3& center, float radius) noexcept
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, float)", AS_FUNCTION_OBJFIRST(Sphere__Sphere_constspVector3amp_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Sphere::Sphere(const BoundingBox& box) noexcept
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", AS_FUNCTION_OBJFIRST(Sphere__Sphere_constspBoundingBoxamp), AS_CALL_CDECL_OBJFIRST);
    // explicit Sphere::Sphere(const Frustum& frustum) noexcept
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", AS_FUNCTION_OBJFIRST(Sphere__Sphere_constspFrustumamp), AS_CALL_CDECL_OBJFIRST);
    // explicit Sphere::Sphere(const Polyhedron& poly) noexcept
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", AS_FUNCTION_OBJFIRST(Sphere__Sphere_constspPolyhedronamp), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Sphere<Sphere>(engine, "Sphere");
    CollectMembers_Sphere(members);
    RegisterMembers(engine, "Sphere", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Sphere
        REGISTER_CLASS_MANUAL_PART_Sphere();
    #endif
}

// explicit Spline::Spline(InterpolationMode mode)
static void Spline__Spline_InterpolationMode(Spline* _ptr, InterpolationMode mode)
{
    new(_ptr) Spline(mode);
}

// Spline::Spline(const Spline& rhs) = default
static void Spline__Spline_constspSplineamp(Spline* _ptr, const Spline& rhs)
{
    new(_ptr) Spline(rhs);
}

// class Spline | File: ../Core/Spline.h
static void Register_Spline(asIScriptEngine* engine)
{
    // explicit Spline::Spline(const Vector<Variant>& knots, InterpolationMode mode = BEZIER_CURVE)
    // Error: type "const Vector<Variant>&" can not automatically bind

    // explicit Spline::Spline(InterpolationMode mode)
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f(InterpolationMode)", AS_FUNCTION_OBJFIRST(Spline__Spline_InterpolationMode), AS_CALL_CDECL_OBJFIRST);
    // Spline::Spline(const Spline& rhs) = default
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f(const Spline&in)", AS_FUNCTION_OBJFIRST(Spline__Spline_constspSplineamp), AS_CALL_CDECL_OBJFIRST);

    // Spline::~Spline() | Implicitly-declared
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(Spline), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Spline<Spline>(engine, "Spline");
    CollectMembers_Spline(members);
    RegisterMembers(engine, "Spline", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Spline
        REGISTER_CLASS_MANUAL_PART_Spline();
    #endif
}

// struct StaticModelGeometryData | File: ../Graphics/StaticModel.h
static void Register_StaticModelGeometryData(asIScriptEngine* engine)
{
    // StaticModelGeometryData::~StaticModelGeometryData() | Implicitly-declared
    engine->RegisterObjectBehaviour("StaticModelGeometryData", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(StaticModelGeometryData), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_StaticModelGeometryData<StaticModelGeometryData>(engine, "StaticModelGeometryData");
    CollectMembers_StaticModelGeometryData(members);
    RegisterMembers(engine, "StaticModelGeometryData", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_StaticModelGeometryData
        REGISTER_CLASS_MANUAL_PART_StaticModelGeometryData();
    #endif

    // StaticModelGeometryData& StaticModelGeometryData::operator =(const StaticModelGeometryData&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<StaticModelGeometryData>(engine, "StaticModelGeometryData");
}

// StoredLogMessage::StoredLogMessage(const String& message, int level, bool error)
static void StoredLogMessage__StoredLogMessage_constspStringamp_int_bool(StoredLogMessage* _ptr, const String& message, int level, bool error)
{
    new(_ptr) StoredLogMessage(message, level, error);
}

// struct StoredLogMessage | File: ../IO/Log.h
static void Register_StoredLogMessage(asIScriptEngine* engine)
{
    // StoredLogMessage::StoredLogMessage(const String& message, int level, bool error)
    engine->RegisterObjectBehaviour("StoredLogMessage", asBEHAVE_CONSTRUCT, "void f(const String&in, int, bool)", AS_FUNCTION_OBJFIRST(StoredLogMessage__StoredLogMessage_constspStringamp_int_bool), AS_CALL_CDECL_OBJFIRST);

    // StoredLogMessage::~StoredLogMessage() | Implicitly-declared
    engine->RegisterObjectBehaviour("StoredLogMessage", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(StoredLogMessage), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_StoredLogMessage<StoredLogMessage>(engine, "StoredLogMessage");
    CollectMembers_StoredLogMessage(members);
    RegisterMembers(engine, "StoredLogMessage", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_StoredLogMessage
        REGISTER_CLASS_MANUAL_PART_StoredLogMessage();
    #endif

    // StoredLogMessage& StoredLogMessage::operator =(const StoredLogMessage&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<StoredLogMessage>(engine, "StoredLogMessage");
}

// String::String(const String& str)
static void String__String_constspStringamp(String* _ptr, const String& str)
{
    new(_ptr) String(str);
}

// explicit String::String(int value)
static void String__String_int(String* _ptr, int value)
{
    new(_ptr) String(value);
}

// explicit String::String(short value)
static void String__String_short(String* _ptr, short value)
{
    new(_ptr) String(value);
}

// explicit String::String(long long value)
static void String__String_longsplong(String* _ptr, long long value)
{
    new(_ptr) String(value);
}

// explicit String::String(unsigned value)
static void String__String_unsigned(String* _ptr, unsigned value)
{
    new(_ptr) String(value);
}

// explicit String::String(unsigned short value)
static void String__String_unsignedspshort(String* _ptr, unsigned short value)
{
    new(_ptr) String(value);
}

// explicit String::String(unsigned long long value)
static void String__String_unsignedsplongsplong(String* _ptr, unsigned long long value)
{
    new(_ptr) String(value);
}

// explicit String::String(float value)
static void String__String_float(String* _ptr, float value)
{
    new(_ptr) String(value);
}

// explicit String::String(double value)
static void String__String_double(String* _ptr, double value)
{
    new(_ptr) String(value);
}

// explicit String::String(bool value)
static void String__String_bool(String* _ptr, bool value)
{
    new(_ptr) String(value);
}

// explicit String::String(char value)
static void String__String_char(String* _ptr, char value)
{
    new(_ptr) String(value);
}

// explicit String::String(char value, unsigned length)
static void String__String_char_unsigned(String* _ptr, char value, unsigned length)
{
    new(_ptr) String(value, length);
}

// class String | File: ../Container/Str.h
static void Register_String(asIScriptEngine* engine)
{
    // String::String(String&& str) noexcept
    // Error: type "String&&" can not automatically bind
    // String::String(char* str)
    // Error: type "char*" can not automatically bind
    // String::String(const char* str)
    // Error: type "const char*" can not automatically bind
    // String::String(const char* str, unsigned length)
    // Error: type "const char*" can not automatically bind
    // explicit String::String(const WString& str)
    // Error: type "WString" can not automatically bind bacause have @nobind mark
    // explicit String::String(const wchar_t* str)
    // Error: type "const wchar_t*" can not automatically bind
    // explicit String::String(long value)
    // Not registered because have @nobind mark
    // explicit String::String(unsigned long value)
    // Not registered because have @nobind mark
    // explicit String::String(wchar_t* str)
    // Error: type "wchar_t*" can not automatically bind
    // template <class T> explicit String::String(const T& value)
    // Error: type "const T&" can not automatically bind

    // String::String(const String& str)
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(const String&in)", AS_FUNCTION_OBJFIRST(String__String_constspStringamp), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(int value)
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int)", AS_FUNCTION_OBJFIRST(String__String_int), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(short value)
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int16)", AS_FUNCTION_OBJFIRST(String__String_short), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(long long value)
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int64)", AS_FUNCTION_OBJFIRST(String__String_longsplong), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(unsigned value)
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(uint)", AS_FUNCTION_OBJFIRST(String__String_unsigned), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(unsigned short value)
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(uint16)", AS_FUNCTION_OBJFIRST(String__String_unsignedspshort), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(unsigned long long value)
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(uint64)", AS_FUNCTION_OBJFIRST(String__String_unsignedsplongsplong), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(float value)
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(float)", AS_FUNCTION_OBJFIRST(String__String_float), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(double value)
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(double)", AS_FUNCTION_OBJFIRST(String__String_double), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(bool value)
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(bool)", AS_FUNCTION_OBJFIRST(String__String_bool), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(char value)
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int8)", AS_FUNCTION_OBJFIRST(String__String_char), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(char value, unsigned length)
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int8, uint)", AS_FUNCTION_OBJFIRST(String__String_char_unsigned), AS_CALL_CDECL_OBJFIRST);

    // String::~String()
    engine->RegisterObjectBehaviour("String", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(String), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_String<String>(engine, "String");
    CollectMembers_String(members);
    RegisterMembers(engine, "String", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_String
        REGISTER_CLASS_MANUAL_PART_String();
    #endif
}

// StringHash::StringHash(const StringHash& rhs) noexcept = default
static void StringHash__StringHash_constspStringHashamp(StringHash* _ptr, const StringHash& rhs)
{
    new(_ptr) StringHash(rhs);
}

// explicit StringHash::StringHash(unsigned value) noexcept
static void StringHash__StringHash_unsigned(StringHash* _ptr, unsigned value)
{
    new(_ptr) StringHash(value);
}

// StringHash::StringHash(const String& str) noexcept
static void StringHash__StringHash_constspStringamp(StringHash* _ptr, const String& str)
{
    new(_ptr) StringHash(str);
}

// class StringHash | File: ../Math/StringHash.h
static void Register_StringHash(asIScriptEngine* engine)
{
    // StringHash::StringHash(const char* str) noexcept
    // Error: type "const char*" can not automatically bind

    // StringHash::StringHash(const StringHash& rhs) noexcept = default
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(const StringHash&in)", AS_FUNCTION_OBJFIRST(StringHash__StringHash_constspStringHashamp), AS_CALL_CDECL_OBJFIRST);
    // explicit StringHash::StringHash(unsigned value) noexcept
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(uint)", AS_FUNCTION_OBJFIRST(StringHash__StringHash_unsigned), AS_CALL_CDECL_OBJFIRST);
    // StringHash::StringHash(const String& str) noexcept
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(const String&in)", AS_FUNCTION_OBJFIRST(StringHash__StringHash_constspStringamp), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_StringHash<StringHash>(engine, "StringHash");
    CollectMembers_StringHash(members);
    RegisterMembers(engine, "StringHash", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_StringHash
        REGISTER_CLASS_MANUAL_PART_StringHash();
    #endif
}

// StringHashRegister::StringHashRegister(bool threadSafe)
static void StringHashRegister__StringHashRegister_bool(StringHashRegister* _ptr, bool threadSafe)
{
    new(_ptr) StringHashRegister(threadSafe);
}

// class StringHashRegister | File: ../Core/StringHashRegister.h
static void Register_StringHashRegister(asIScriptEngine* engine)
{
    // StringHashRegister::StringHashRegister(bool threadSafe)
    engine->RegisterObjectBehaviour("StringHashRegister", asBEHAVE_CONSTRUCT, "void f(bool)", AS_FUNCTION_OBJFIRST(StringHashRegister__StringHashRegister_bool), AS_CALL_CDECL_OBJFIRST);

    // StringHashRegister::~StringHashRegister()
    engine->RegisterObjectBehaviour("StringHashRegister", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(StringHashRegister), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_StringHashRegister<StringHashRegister>(engine, "StringHashRegister");
    CollectMembers_StringHashRegister(members);
    RegisterMembers(engine, "StringHashRegister", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_StringHashRegister
        REGISTER_CLASS_MANUAL_PART_StringHashRegister();
    #endif

    // StringHashRegister& StringHashRegister::operator =(const StringHashRegister&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<StringHashRegister>(engine, "StringHashRegister");
}

// TechniqueEntry::TechniqueEntry(Technique* tech, MaterialQuality qualityLevel, float lodDistance) noexcept
static void TechniqueEntry__TechniqueEntry_Techniquestar_MaterialQuality_float(TechniqueEntry* _ptr, Technique* tech, MaterialQuality qualityLevel, float lodDistance)
{
    new(_ptr) TechniqueEntry(tech, qualityLevel, lodDistance);
}

// struct TechniqueEntry | File: ../Graphics/Material.h
static void Register_TechniqueEntry(asIScriptEngine* engine)
{
    // TechniqueEntry::TechniqueEntry(Technique* tech, MaterialQuality qualityLevel, float lodDistance) noexcept
    engine->RegisterObjectBehaviour("TechniqueEntry", asBEHAVE_CONSTRUCT, "void f(Technique@+, MaterialQuality, float)", AS_FUNCTION_OBJFIRST(TechniqueEntry__TechniqueEntry_Techniquestar_MaterialQuality_float), AS_CALL_CDECL_OBJFIRST);

    // TechniqueEntry::~TechniqueEntry() noexcept = default
    engine->RegisterObjectBehaviour("TechniqueEntry", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(TechniqueEntry), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_TechniqueEntry<TechniqueEntry>(engine, "TechniqueEntry");
    CollectMembers_TechniqueEntry(members);
    RegisterMembers(engine, "TechniqueEntry", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TechniqueEntry
        REGISTER_CLASS_MANUAL_PART_TechniqueEntry();
    #endif

    // TechniqueEntry& TechniqueEntry::operator =(const TechniqueEntry&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<TechniqueEntry>(engine, "TechniqueEntry");
}

// struct TextureFrame | File: ../Graphics/ParticleEffect.h
static void Register_TextureFrame(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("TextureFrame", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("TextureFrame", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);

    MemberCollection members;
    RegisterMembers_TextureFrame<TextureFrame>(engine, "TextureFrame");
    CollectMembers_TextureFrame(members);
    RegisterMembers(engine, "TextureFrame", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TextureFrame
        REGISTER_CLASS_MANUAL_PART_TextureFrame();
    #endif

    // TextureFrame& TextureFrame::operator =(const TextureFrame&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<TextureFrame>(engine, "TextureFrame");
}

// class Timer | File: ../Core/Timer.h
static void Register_Timer(asIScriptEngine* engine)
{
    MemberCollection members;
    RegisterMembers_Timer<Timer>(engine, "Timer");
    CollectMembers_Timer(members);
    RegisterMembers(engine, "Timer", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Timer
        REGISTER_CLASS_MANUAL_PART_Timer();
    #endif

    // Timer& Timer::operator =(const Timer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Timer>(engine, "Timer");
}

// struct TouchState | File: ../Input/Input.h
static void Register_TouchState(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("TouchState", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("TouchState", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);

    MemberCollection members;
    RegisterMembers_TouchState<TouchState>(engine, "TouchState");
    CollectMembers_TouchState(members);
    RegisterMembers(engine, "TouchState", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TouchState
        REGISTER_CLASS_MANUAL_PART_TouchState();
    #endif

    // TouchState& TouchState::operator =(const TouchState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<TouchState>(engine, "TouchState");
}

// TrailPoint::TrailPoint(const Vector3& position, const Vector3& forward)
static void TrailPoint__TrailPoint_constspVector3amp_constspVector3amp(TrailPoint* _ptr, const Vector3& position, const Vector3& forward)
{
    new(_ptr) TrailPoint(position, forward);
}

// struct TrailPoint | File: ../Graphics/RibbonTrail.h
static void Register_TrailPoint(asIScriptEngine* engine)
{
    // TrailPoint::TrailPoint(const Vector3& position, const Vector3& forward)
    engine->RegisterObjectBehaviour("TrailPoint", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(TrailPoint__TrailPoint_constspVector3amp_constspVector3amp), AS_CALL_CDECL_OBJFIRST);

    // TrailPoint::~TrailPoint() | Implicitly-declared
    engine->RegisterObjectBehaviour("TrailPoint", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(TrailPoint), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_TrailPoint<TrailPoint>(engine, "TrailPoint");
    CollectMembers_TrailPoint(members);
    RegisterMembers(engine, "TrailPoint", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TrailPoint
        REGISTER_CLASS_MANUAL_PART_TrailPoint();
    #endif

    // TrailPoint& TrailPoint::operator =(const TrailPoint&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<TrailPoint>(engine, "TrailPoint");
}

// class UIBatch | File: ../UI/UIBatch.h
static void Register_UIBatch(asIScriptEngine* engine)
{
    // UIBatch::UIBatch(UIElement* element, BlendMode blendMode, const IntRect& scissor, Texture* texture, PODVector<float>* vertexData)
    // Error: type "PODVector<float>*" can not automatically bind

    // UIBatch::~UIBatch() | Implicitly-declared
    engine->RegisterObjectBehaviour("UIBatch", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(UIBatch), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_UIBatch<UIBatch>(engine, "UIBatch");
    CollectMembers_UIBatch(members);
    RegisterMembers(engine, "UIBatch", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_UIBatch
        REGISTER_CLASS_MANUAL_PART_UIBatch();
    #endif

    // UIBatch& UIBatch::operator =(const UIBatch&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<UIBatch>(engine, "UIBatch");
}

// struct VAnimEventFrame | File: ../Scene/ValueAnimation.h
static void Register_VAnimEventFrame(asIScriptEngine* engine)
{
    // VAnimEventFrame::~VAnimEventFrame() | Implicitly-declared
    engine->RegisterObjectBehaviour("VAnimEventFrame", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(VAnimEventFrame), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_VAnimEventFrame<VAnimEventFrame>(engine, "VAnimEventFrame");
    CollectMembers_VAnimEventFrame(members);
    RegisterMembers(engine, "VAnimEventFrame", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_VAnimEventFrame
        REGISTER_CLASS_MANUAL_PART_VAnimEventFrame();
    #endif

    // VAnimEventFrame& VAnimEventFrame::operator =(const VAnimEventFrame&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VAnimEventFrame>(engine, "VAnimEventFrame");
}

// struct VAnimKeyFrame | File: ../Scene/ValueAnimation.h
static void Register_VAnimKeyFrame(asIScriptEngine* engine)
{
    // VAnimKeyFrame::~VAnimKeyFrame() | Implicitly-declared
    engine->RegisterObjectBehaviour("VAnimKeyFrame", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(VAnimKeyFrame), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_VAnimKeyFrame<VAnimKeyFrame>(engine, "VAnimKeyFrame");
    CollectMembers_VAnimKeyFrame(members);
    RegisterMembers(engine, "VAnimKeyFrame", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_VAnimKeyFrame
        REGISTER_CLASS_MANUAL_PART_VAnimKeyFrame();
    #endif

    // VAnimKeyFrame& VAnimKeyFrame::operator =(const VAnimKeyFrame&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VAnimKeyFrame>(engine, "VAnimKeyFrame");
}

// Variant::Variant(int value)
static void Variant__Variant_int(Variant* _ptr, int value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(long long value)
static void Variant__Variant_longsplong(Variant* _ptr, long long value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(unsigned value)
static void Variant__Variant_unsigned(Variant* _ptr, unsigned value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(unsigned long long value)
static void Variant__Variant_unsignedsplongsplong(Variant* _ptr, unsigned long long value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const StringHash& value)
static void Variant__Variant_constspStringHashamp(Variant* _ptr, const StringHash& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(bool value)
static void Variant__Variant_bool(Variant* _ptr, bool value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(float value)
static void Variant__Variant_float(Variant* _ptr, float value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(double value)
static void Variant__Variant_double(Variant* _ptr, double value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const Vector2& value)
static void Variant__Variant_constspVector2amp(Variant* _ptr, const Vector2& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const Vector3& value)
static void Variant__Variant_constspVector3amp(Variant* _ptr, const Vector3& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const Vector4& value)
static void Variant__Variant_constspVector4amp(Variant* _ptr, const Vector4& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const Quaternion& value)
static void Variant__Variant_constspQuaternionamp(Variant* _ptr, const Quaternion& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const Color& value)
static void Variant__Variant_constspColoramp(Variant* _ptr, const Color& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const String& value)
static void Variant__Variant_constspStringamp(Variant* _ptr, const String& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const VectorBuffer& value)
static void Variant__Variant_constspVectorBufferamp(Variant* _ptr, const VectorBuffer& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const ResourceRef& value)
static void Variant__Variant_constspResourceRefamp(Variant* _ptr, const ResourceRef& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const ResourceRefList& value)
static void Variant__Variant_constspResourceRefListamp(Variant* _ptr, const ResourceRefList& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const VariantMap& value)
static void Variant__Variant_constspVariantMapamp(Variant* _ptr, const VariantMap& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const StringVector& value)
static void Variant__Variant_constspStringVectoramp(Variant* _ptr, CScriptArray* value_conv)
{
    StringVector value = ArrayToVector<String>(value_conv);
    new(_ptr) Variant(value);
}

// Variant::Variant(const Rect& value)
static void Variant__Variant_constspRectamp(Variant* _ptr, const Rect& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const IntRect& value)
static void Variant__Variant_constspIntRectamp(Variant* _ptr, const IntRect& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const IntVector2& value)
static void Variant__Variant_constspIntVector2amp(Variant* _ptr, const IntVector2& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const IntVector3& value)
static void Variant__Variant_constspIntVector3amp(Variant* _ptr, const IntVector3& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(RefCounted* value)
static void Variant__Variant_RefCountedstar(Variant* _ptr, RefCounted* value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const Matrix3& value)
static void Variant__Variant_constspMatrix3amp(Variant* _ptr, const Matrix3& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const Matrix3x4& value)
static void Variant__Variant_constspMatrix3x4amp(Variant* _ptr, const Matrix3x4& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const Matrix4& value)
static void Variant__Variant_constspMatrix4amp(Variant* _ptr, const Matrix4& value)
{
    new(_ptr) Variant(value);
}

// Variant::Variant(const String& type, const String& value)
static void Variant__Variant_constspStringamp_constspStringamp(Variant* _ptr, const String& type, const String& value)
{
    new(_ptr) Variant(type, value);
}

// Variant::Variant(VariantType type, const String& value)
static void Variant__Variant_VariantType_constspStringamp(Variant* _ptr, VariantType type, const String& value)
{
    new(_ptr) Variant(type, value);
}

// Variant::Variant(const Variant& value)
static void Variant__Variant_constspVariantamp(Variant* _ptr, const Variant& value)
{
    new(_ptr) Variant(value);
}

// class Variant | File: ../Core/Variant.h
static void Register_Variant(asIScriptEngine* engine)
{
    // Variant::Variant(VariantType type, const char* value)
    // Error: type "const char*" can not automatically bind
    // Variant::Variant(const PODVector<unsigned char>& value)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // Variant::Variant(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind
    // Variant::Variant(const char* type, const char* value)
    // Error: type "const char*" can not automatically bind
    // Variant::Variant(const char* value)
    // Error: type "const char*" can not automatically bind
    // Variant::Variant(void* value)
    // Error: type "void*" can not automatically bind
    // template <class T> Variant::Variant(const CustomVariantValueImpl<T>& value)
    // Error: type "const CustomVariantValueImpl<T>&" can not automatically bind

    // Variant::Variant(int value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(int)", AS_FUNCTION_OBJFIRST(Variant__Variant_int), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(long long value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(int64)", AS_FUNCTION_OBJFIRST(Variant__Variant_longsplong), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(unsigned value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(uint)", AS_FUNCTION_OBJFIRST(Variant__Variant_unsigned), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(unsigned long long value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(uint64)", AS_FUNCTION_OBJFIRST(Variant__Variant_unsignedsplongsplong), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const StringHash& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const StringHash&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspStringHashamp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(bool value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(bool)", AS_FUNCTION_OBJFIRST(Variant__Variant_bool), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(float value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(float)", AS_FUNCTION_OBJFIRST(Variant__Variant_float), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(double value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(double)", AS_FUNCTION_OBJFIRST(Variant__Variant_double), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Vector2& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspVector2amp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Vector3& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspVector3amp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Vector4& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspVector4amp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Quaternion& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Quaternion&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspQuaternionamp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Color& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Color&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspColoramp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const String& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const String&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspStringamp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const VectorBuffer& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const VectorBuffer&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspVectorBufferamp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const ResourceRef& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const ResourceRef&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspResourceRefamp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const ResourceRefList& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const ResourceRefList&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspResourceRefListamp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const VariantMap& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const VariantMap&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspVariantMapamp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const StringVector& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(Array<String>@+)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspStringVectoramp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Rect& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Rect&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspRectamp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const IntRect& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const IntRect&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspIntRectamp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const IntVector2& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspIntVector2amp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const IntVector3& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const IntVector3&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspIntVector3amp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(RefCounted* value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(RefCounted@+)", AS_FUNCTION_OBJFIRST(Variant__Variant_RefCountedstar), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Matrix3& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspMatrix3amp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Matrix3x4& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Matrix3x4&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspMatrix3x4amp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Matrix4& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspMatrix4amp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const String& type, const String& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const String&in, const String&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspStringamp_constspStringamp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(VariantType type, const String& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(VariantType, const String&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_VariantType_constspStringamp), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Variant& value)
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Variant&in)", AS_FUNCTION_OBJFIRST(Variant__Variant_constspVariantamp), AS_CALL_CDECL_OBJFIRST);

    // Variant::~Variant()
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(Variant), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Variant<Variant>(engine, "Variant");
    CollectMembers_Variant(members);
    RegisterMembers(engine, "Variant", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Variant
        REGISTER_CLASS_MANUAL_PART_Variant();
    #endif
}

// Vector2::Vector2(const Vector2& vector) noexcept = default
static void Vector2__Vector2_constspVector2amp(Vector2* _ptr, const Vector2& vector)
{
    new(_ptr) Vector2(vector);
}

// explicit Vector2::Vector2(const IntVector2& vector) noexcept
static void Vector2__Vector2_constspIntVector2amp(Vector2* _ptr, const IntVector2& vector)
{
    new(_ptr) Vector2(vector);
}

// Vector2::Vector2(float x, float y) noexcept
static void Vector2__Vector2_float_float(Vector2* _ptr, float x, float y)
{
    new(_ptr) Vector2(x, y);
}

// class Vector2 | File: ../Math/Vector2.h
static void Register_Vector2(asIScriptEngine* engine)
{
    // explicit Vector2::Vector2(const float* data) noexcept
    // Error: type "const float*" can not automatically bind

    // Vector2::Vector2(const Vector2& vector) noexcept = default
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", AS_FUNCTION_OBJFIRST(Vector2__Vector2_constspVector2amp), AS_CALL_CDECL_OBJFIRST);
    // explicit Vector2::Vector2(const IntVector2& vector) noexcept
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", AS_FUNCTION_OBJFIRST(Vector2__Vector2_constspIntVector2amp), AS_CALL_CDECL_OBJFIRST);
    // Vector2::Vector2(float x, float y) noexcept
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float, float)", AS_FUNCTION_OBJFIRST(Vector2__Vector2_float_float), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Vector2<Vector2>(engine, "Vector2");
    CollectMembers_Vector2(members);
    RegisterMembers(engine, "Vector2", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Vector2
        REGISTER_CLASS_MANUAL_PART_Vector2();
    #endif
}

// Vector3::Vector3(const Vector3& vector) noexcept = default
static void Vector3__Vector3_constspVector3amp(Vector3* _ptr, const Vector3& vector)
{
    new(_ptr) Vector3(vector);
}

// Vector3::Vector3(const Vector2& vector, float z) noexcept
static void Vector3__Vector3_constspVector2amp_float(Vector3* _ptr, const Vector2& vector, float z)
{
    new(_ptr) Vector3(vector, z);
}

// explicit Vector3::Vector3(const Vector2& vector) noexcept
static void Vector3__Vector3_constspVector2amp(Vector3* _ptr, const Vector2& vector)
{
    new(_ptr) Vector3(vector);
}

// explicit Vector3::Vector3(const IntVector3& vector) noexcept
static void Vector3__Vector3_constspIntVector3amp(Vector3* _ptr, const IntVector3& vector)
{
    new(_ptr) Vector3(vector);
}

// Vector3::Vector3(float x, float y, float z) noexcept
static void Vector3__Vector3_float_float_float(Vector3* _ptr, float x, float y, float z)
{
    new(_ptr) Vector3(x, y, z);
}

// Vector3::Vector3(float x, float y) noexcept
static void Vector3__Vector3_float_float(Vector3* _ptr, float x, float y)
{
    new(_ptr) Vector3(x, y);
}

// class Vector3 | File: ../Math/Vector3.h
static void Register_Vector3(asIScriptEngine* engine)
{
    // explicit Vector3::Vector3(const float* data) noexcept
    // Error: type "const float*" can not automatically bind

    // Vector3::Vector3(const Vector3& vector) noexcept = default
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", AS_FUNCTION_OBJFIRST(Vector3__Vector3_constspVector3amp), AS_CALL_CDECL_OBJFIRST);
    // Vector3::Vector3(const Vector2& vector, float z) noexcept
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector2&in, float)", AS_FUNCTION_OBJFIRST(Vector3__Vector3_constspVector2amp_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Vector3::Vector3(const Vector2& vector) noexcept
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", AS_FUNCTION_OBJFIRST(Vector3__Vector3_constspVector2amp), AS_CALL_CDECL_OBJFIRST);
    // explicit Vector3::Vector3(const IntVector3& vector) noexcept
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const IntVector3&in)", AS_FUNCTION_OBJFIRST(Vector3__Vector3_constspIntVector3amp), AS_CALL_CDECL_OBJFIRST);
    // Vector3::Vector3(float x, float y, float z) noexcept
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", AS_FUNCTION_OBJFIRST(Vector3__Vector3_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // Vector3::Vector3(float x, float y) noexcept
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float)", AS_FUNCTION_OBJFIRST(Vector3__Vector3_float_float), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Vector3<Vector3>(engine, "Vector3");
    CollectMembers_Vector3(members);
    RegisterMembers(engine, "Vector3", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Vector3
        REGISTER_CLASS_MANUAL_PART_Vector3();
    #endif
}

// Vector4::Vector4(const Vector4& vector) noexcept = default
static void Vector4__Vector4_constspVector4amp(Vector4* _ptr, const Vector4& vector)
{
    new(_ptr) Vector4(vector);
}

// Vector4::Vector4(const Vector3& vector, float w) noexcept
static void Vector4__Vector4_constspVector3amp_float(Vector4* _ptr, const Vector3& vector, float w)
{
    new(_ptr) Vector4(vector, w);
}

// Vector4::Vector4(float x, float y, float z, float w) noexcept
static void Vector4__Vector4_float_float_float_float(Vector4* _ptr, float x, float y, float z, float w)
{
    new(_ptr) Vector4(x, y, z, w);
}

// class Vector4 | File: ../Math/Vector4.h
static void Register_Vector4(asIScriptEngine* engine)
{
    // explicit Vector4::Vector4(const float* data) noexcept
    // Error: type "const float*" can not automatically bind

    // Vector4::Vector4(const Vector4& vector) noexcept = default
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", AS_FUNCTION_OBJFIRST(Vector4__Vector4_constspVector4amp), AS_CALL_CDECL_OBJFIRST);
    // Vector4::Vector4(const Vector3& vector, float w) noexcept
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, float)", AS_FUNCTION_OBJFIRST(Vector4__Vector4_constspVector3amp_float), AS_CALL_CDECL_OBJFIRST);
    // Vector4::Vector4(float x, float y, float z, float w) noexcept
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", AS_FUNCTION_OBJFIRST(Vector4__Vector4_float_float_float_float), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Vector4<Vector4>(engine, "Vector4");
    CollectMembers_Vector4(members);
    RegisterMembers(engine, "Vector4", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Vector4
        REGISTER_CLASS_MANUAL_PART_Vector4();
    #endif
}

// class VectorBase | File: ../Container/VectorBase.h
static void Register_VectorBase(asIScriptEngine* engine)
{
    // VectorBase::~VectorBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("VectorBase", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(VectorBase), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_VectorBase<VectorBase>(engine, "VectorBase");
    CollectMembers_VectorBase(members);
    RegisterMembers(engine, "VectorBase", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_VectorBase
        REGISTER_CLASS_MANUAL_PART_VectorBase();
    #endif

    // VectorBase& VectorBase::operator =(const VectorBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VectorBase>(engine, "VectorBase");
}

// struct VertexBufferDesc | File: ../Graphics/Model.h
static void Register_VertexBufferDesc(asIScriptEngine* engine)
{
    // VertexBufferDesc::~VertexBufferDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("VertexBufferDesc", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(VertexBufferDesc), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_VertexBufferDesc<VertexBufferDesc>(engine, "VertexBufferDesc");
    CollectMembers_VertexBufferDesc(members);
    RegisterMembers(engine, "VertexBufferDesc", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_VertexBufferDesc
        REGISTER_CLASS_MANUAL_PART_VertexBufferDesc();
    #endif

    // VertexBufferDesc& VertexBufferDesc::operator =(const VertexBufferDesc&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VertexBufferDesc>(engine, "VertexBufferDesc");
}

// struct VertexBufferMorph | File: ../Graphics/Model.h
static void Register_VertexBufferMorph(asIScriptEngine* engine)
{
    // VertexBufferMorph::~VertexBufferMorph() | Implicitly-declared
    engine->RegisterObjectBehaviour("VertexBufferMorph", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(VertexBufferMorph), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_VertexBufferMorph<VertexBufferMorph>(engine, "VertexBufferMorph");
    CollectMembers_VertexBufferMorph(members);
    RegisterMembers(engine, "VertexBufferMorph", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_VertexBufferMorph
        REGISTER_CLASS_MANUAL_PART_VertexBufferMorph();
    #endif

    // VertexBufferMorph& VertexBufferMorph::operator =(const VertexBufferMorph&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VertexBufferMorph>(engine, "VertexBufferMorph");
}

// VertexElement::VertexElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index = 0, bool perInstance = false) noexcept
static void VertexElement__VertexElement_VertexElementType_VertexElementSemantic_unsignedspchar_bool(VertexElement* _ptr, VertexElementType type, VertexElementSemantic semantic, unsigned char index, bool perInstance)
{
    new(_ptr) VertexElement(type, semantic, index, perInstance);
}

// struct VertexElement | File: ../Graphics/GraphicsDefs.h
static void Register_VertexElement(asIScriptEngine* engine)
{
    // VertexElement::VertexElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index = 0, bool perInstance = false) noexcept
    engine->RegisterObjectBehaviour("VertexElement", asBEHAVE_CONSTRUCT, "void f(VertexElementType, VertexElementSemantic, uint8 = 0, bool = false)", AS_FUNCTION_OBJFIRST(VertexElement__VertexElement_VertexElementType_VertexElementSemantic_unsignedspchar_bool), AS_CALL_CDECL_OBJFIRST);

    // VertexElement::~VertexElement() | Implicitly-declared
    engine->RegisterObjectBehaviour("VertexElement", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(VertexElement), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_VertexElement<VertexElement>(engine, "VertexElement");
    CollectMembers_VertexElement(members);
    RegisterMembers(engine, "VertexElement", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_VertexElement
        REGISTER_CLASS_MANUAL_PART_VertexElement();
    #endif

    // VertexElement& VertexElement::operator =(const VertexElement&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VertexElement>(engine, "VertexElement");
}

// struct WindowModeParams | File: ../Graphics/Graphics.h
static void Register_WindowModeParams(asIScriptEngine* engine)
{
    // WindowModeParams::~WindowModeParams() | Implicitly-declared
    engine->RegisterObjectBehaviour("WindowModeParams", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(WindowModeParams), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_WindowModeParams<WindowModeParams>(engine, "WindowModeParams");
    CollectMembers_WindowModeParams(members);
    RegisterMembers(engine, "WindowModeParams", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_WindowModeParams
        REGISTER_CLASS_MANUAL_PART_WindowModeParams();
    #endif

    // WindowModeParams& WindowModeParams::operator =(const WindowModeParams&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<WindowModeParams>(engine, "WindowModeParams");
}

// XMLElement::XMLElement(const XMLElement& rhs)
static void XMLElement__XMLElement_constspXMLElementamp(XMLElement* _ptr, const XMLElement& rhs)
{
    new(_ptr) XMLElement(rhs);
}

// class XMLElement | File: ../Resource/XMLElement.h
static void Register_XMLElement(asIScriptEngine* engine)
{
    // XMLElement::XMLElement(XMLFile* file, const XPathResultSet* resultSet, const pugi::xpath_node* xpathNode, unsigned xpathResultIndex)
    // Error: type "const XPathResultSet*" can not automatically bind
    // XMLElement::XMLElement(XMLFile* file, pugi::xml_node_struct* node)
    // Error: type "pugi::xml_node_struct*" can not automatically bind

    // XMLElement::XMLElement(const XMLElement& rhs)
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_CONSTRUCT, "void f(const XMLElement&in)", AS_FUNCTION_OBJFIRST(XMLElement__XMLElement_constspXMLElementamp), AS_CALL_CDECL_OBJFIRST);

    // XMLElement::~XMLElement()
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(XMLElement), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_XMLElement<XMLElement>(engine, "XMLElement");
    CollectMembers_XMLElement(members);
    RegisterMembers(engine, "XMLElement", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_XMLElement
        REGISTER_CLASS_MANUAL_PART_XMLElement();
    #endif
}

// explicit XPathQuery::XPathQuery(const String& queryString, const String& variableString = String::EMPTY)
static void XPathQuery__XPathQuery_constspStringamp_constspStringamp(XPathQuery* _ptr, const String& queryString, const String& variableString)
{
    new(_ptr) XPathQuery(queryString, variableString);
}

// class XPathQuery | File: ../Resource/XMLElement.h
static void Register_XPathQuery(asIScriptEngine* engine)
{
    // explicit XPathQuery::XPathQuery(const String& queryString, const String& variableString = String::EMPTY)
    engine->RegisterObjectBehaviour("XPathQuery", asBEHAVE_CONSTRUCT, "void f(const String&in, const String&in = String::EMPTY)", AS_FUNCTION_OBJFIRST(XPathQuery__XPathQuery_constspStringamp_constspStringamp), AS_CALL_CDECL_OBJFIRST);

    // XPathQuery::~XPathQuery()
    engine->RegisterObjectBehaviour("XPathQuery", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(XPathQuery), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_XPathQuery<XPathQuery>(engine, "XPathQuery");
    CollectMembers_XPathQuery(members);
    RegisterMembers(engine, "XPathQuery", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_XPathQuery
        REGISTER_CLASS_MANUAL_PART_XPathQuery();
    #endif

    // XPathQuery& XPathQuery::operator =(const XPathQuery&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<XPathQuery>(engine, "XPathQuery");
}

// XPathResultSet::XPathResultSet(const XPathResultSet& rhs)
static void XPathResultSet__XPathResultSet_constspXPathResultSetamp(XPathResultSet* _ptr, const XPathResultSet& rhs)
{
    new(_ptr) XPathResultSet(rhs);
}

// class XPathResultSet | File: ../Resource/XMLElement.h
static void Register_XPathResultSet(asIScriptEngine* engine)
{
    // XPathResultSet::XPathResultSet(XMLFile* file, pugi::xpath_node_set* resultSet)
    // Error: type "pugi::xpath_node_set*" can not automatically bind

    // XPathResultSet::XPathResultSet(const XPathResultSet& rhs)
    engine->RegisterObjectBehaviour("XPathResultSet", asBEHAVE_CONSTRUCT, "void f(const XPathResultSet&in)", AS_FUNCTION_OBJFIRST(XPathResultSet__XPathResultSet_constspXPathResultSetamp), AS_CALL_CDECL_OBJFIRST);

    // XPathResultSet::~XPathResultSet()
    engine->RegisterObjectBehaviour("XPathResultSet", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(XPathResultSet), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_XPathResultSet<XPathResultSet>(engine, "XPathResultSet");
    CollectMembers_XPathResultSet(members);
    RegisterMembers(engine, "XPathResultSet", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_XPathResultSet
        REGISTER_CLASS_MANUAL_PART_XPathResultSet();
    #endif
}

#ifdef URHO3D_NAVIGATION

// struct CrowdObstacleAvoidanceParams | File: ../Navigation/CrowdManager.h
static void Register_CrowdObstacleAvoidanceParams(asIScriptEngine* engine)
{
    MemberCollection members;
    RegisterMembers_CrowdObstacleAvoidanceParams<CrowdObstacleAvoidanceParams>(engine, "CrowdObstacleAvoidanceParams");
    CollectMembers_CrowdObstacleAvoidanceParams(members);
    RegisterMembers(engine, "CrowdObstacleAvoidanceParams", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CrowdObstacleAvoidanceParams
        REGISTER_CLASS_MANUAL_PART_CrowdObstacleAvoidanceParams();
    #endif

    // CrowdObstacleAvoidanceParams& CrowdObstacleAvoidanceParams::operator =(const CrowdObstacleAvoidanceParams&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<CrowdObstacleAvoidanceParams>(engine, "CrowdObstacleAvoidanceParams");
}

// struct NavAreaStub | File: ../Navigation/NavBuildData.h
static void Register_NavAreaStub(asIScriptEngine* engine)
{
    // NavAreaStub::~NavAreaStub() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavAreaStub", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(NavAreaStub), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_NavAreaStub<NavAreaStub>(engine, "NavAreaStub");
    CollectMembers_NavAreaStub(members);
    RegisterMembers(engine, "NavAreaStub", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_NavAreaStub
        REGISTER_CLASS_MANUAL_PART_NavAreaStub();
    #endif

    // NavAreaStub& NavAreaStub::operator =(const NavAreaStub&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<NavAreaStub>(engine, "NavAreaStub");
}

// struct NavBuildData | File: ../Navigation/NavBuildData.h
static void Register_NavBuildData(asIScriptEngine* engine)
{
    // virtual NavBuildData::~NavBuildData()
    engine->RegisterObjectBehaviour("NavBuildData", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(NavBuildData), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_NavBuildData<NavBuildData>(engine, "NavBuildData");
    CollectMembers_NavBuildData(members);
    RegisterMembers(engine, "NavBuildData", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_NavBuildData
        REGISTER_CLASS_MANUAL_PART_NavBuildData();
    #endif

    // NavBuildData& NavBuildData::operator =(const NavBuildData&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<NavBuildData>(engine, "NavBuildData");
}

// struct NavigationGeometryInfo | File: ../Navigation/NavigationMesh.h
static void Register_NavigationGeometryInfo(asIScriptEngine* engine)
{
    // NavigationGeometryInfo::~NavigationGeometryInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavigationGeometryInfo", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(NavigationGeometryInfo), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_NavigationGeometryInfo<NavigationGeometryInfo>(engine, "NavigationGeometryInfo");
    CollectMembers_NavigationGeometryInfo(members);
    RegisterMembers(engine, "NavigationGeometryInfo", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_NavigationGeometryInfo
        REGISTER_CLASS_MANUAL_PART_NavigationGeometryInfo();
    #endif

    // NavigationGeometryInfo& NavigationGeometryInfo::operator =(const NavigationGeometryInfo&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<NavigationGeometryInfo>(engine, "NavigationGeometryInfo");
}

// struct NavigationPathPoint | File: ../Navigation/NavigationMesh.h
static void Register_NavigationPathPoint(asIScriptEngine* engine)
{
    // NavigationPathPoint::~NavigationPathPoint() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavigationPathPoint", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(NavigationPathPoint), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_NavigationPathPoint<NavigationPathPoint>(engine, "NavigationPathPoint");
    CollectMembers_NavigationPathPoint(members);
    RegisterMembers(engine, "NavigationPathPoint", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_NavigationPathPoint
        REGISTER_CLASS_MANUAL_PART_NavigationPathPoint();
    #endif

    // NavigationPathPoint& NavigationPathPoint::operator =(const NavigationPathPoint&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<NavigationPathPoint>(engine, "NavigationPathPoint");
}

#endif // def URHO3D_NAVIGATION

#ifdef URHO3D_NETWORK

// struct PackageDownload | File: ../Network/Connection.h
static void Register_PackageDownload(asIScriptEngine* engine)
{
    // PackageDownload::~PackageDownload() | Implicitly-declared
    engine->RegisterObjectBehaviour("PackageDownload", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(PackageDownload), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_PackageDownload<PackageDownload>(engine, "PackageDownload");
    CollectMembers_PackageDownload(members);
    RegisterMembers(engine, "PackageDownload", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_PackageDownload
        REGISTER_CLASS_MANUAL_PART_PackageDownload();
    #endif

    // PackageDownload& PackageDownload::operator =(const PackageDownload&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<PackageDownload>(engine, "PackageDownload");
}

// struct PackageUpload | File: ../Network/Connection.h
static void Register_PackageUpload(asIScriptEngine* engine)
{
    // PackageUpload::~PackageUpload() | Implicitly-declared
    engine->RegisterObjectBehaviour("PackageUpload", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(PackageUpload), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_PackageUpload<PackageUpload>(engine, "PackageUpload");
    CollectMembers_PackageUpload(members);
    RegisterMembers(engine, "PackageUpload", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_PackageUpload
        REGISTER_CLASS_MANUAL_PART_PackageUpload();
    #endif

    // PackageUpload& PackageUpload::operator =(const PackageUpload&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<PackageUpload>(engine, "PackageUpload");
}

// struct RemoteEvent | File: ../Network/Connection.h
static void Register_RemoteEvent(asIScriptEngine* engine)
{
    // RemoteEvent::~RemoteEvent() | Implicitly-declared
    engine->RegisterObjectBehaviour("RemoteEvent", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(RemoteEvent), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_RemoteEvent<RemoteEvent>(engine, "RemoteEvent");
    CollectMembers_RemoteEvent(members);
    RegisterMembers(engine, "RemoteEvent", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_RemoteEvent
        REGISTER_CLASS_MANUAL_PART_RemoteEvent();
    #endif

    // RemoteEvent& RemoteEvent::operator =(const RemoteEvent&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<RemoteEvent>(engine, "RemoteEvent");
}

#endif // def URHO3D_NETWORK

#ifdef URHO3D_PHYSICS

// struct DelayedWorldTransform | File: ../Physics/PhysicsWorld.h
static void Register_DelayedWorldTransform(asIScriptEngine* engine)
{
    // DelayedWorldTransform::~DelayedWorldTransform() | Implicitly-declared
    engine->RegisterObjectBehaviour("DelayedWorldTransform", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(DelayedWorldTransform), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_DelayedWorldTransform<DelayedWorldTransform>(engine, "DelayedWorldTransform");
    CollectMembers_DelayedWorldTransform(members);
    RegisterMembers(engine, "DelayedWorldTransform", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_DelayedWorldTransform
        REGISTER_CLASS_MANUAL_PART_DelayedWorldTransform();
    #endif

    // DelayedWorldTransform& DelayedWorldTransform::operator =(const DelayedWorldTransform&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DelayedWorldTransform>(engine, "DelayedWorldTransform");
}

// struct ManifoldPair | File: ../Physics/PhysicsWorld.h
static void Register_ManifoldPair(asIScriptEngine* engine)
{
    // ManifoldPair::~ManifoldPair() | Implicitly-declared
    engine->RegisterObjectBehaviour("ManifoldPair", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ManifoldPair), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ManifoldPair<ManifoldPair>(engine, "ManifoldPair");
    CollectMembers_ManifoldPair(members);
    RegisterMembers(engine, "ManifoldPair", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ManifoldPair
        REGISTER_CLASS_MANUAL_PART_ManifoldPair();
    #endif

    // ManifoldPair& ManifoldPair::operator =(const ManifoldPair&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ManifoldPair>(engine, "ManifoldPair");
}

// struct PhysicsRaycastResult | File: ../Physics/PhysicsWorld.h
static void Register_PhysicsRaycastResult(asIScriptEngine* engine)
{
    // PhysicsRaycastResult::~PhysicsRaycastResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("PhysicsRaycastResult", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(PhysicsRaycastResult), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_PhysicsRaycastResult<PhysicsRaycastResult>(engine, "PhysicsRaycastResult");
    CollectMembers_PhysicsRaycastResult(members);
    RegisterMembers(engine, "PhysicsRaycastResult", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_PhysicsRaycastResult
        REGISTER_CLASS_MANUAL_PART_PhysicsRaycastResult();
    #endif

    // PhysicsRaycastResult& PhysicsRaycastResult::operator =(const PhysicsRaycastResult&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<PhysicsRaycastResult>(engine, "PhysicsRaycastResult");
}

// struct PhysicsWorldConfig | File: ../Physics/PhysicsWorld.h
static void Register_PhysicsWorldConfig(asIScriptEngine* engine)
{
    // PhysicsWorldConfig::~PhysicsWorldConfig() | Implicitly-declared
    engine->RegisterObjectBehaviour("PhysicsWorldConfig", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(PhysicsWorldConfig), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_PhysicsWorldConfig<PhysicsWorldConfig>(engine, "PhysicsWorldConfig");
    CollectMembers_PhysicsWorldConfig(members);
    RegisterMembers(engine, "PhysicsWorldConfig", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_PhysicsWorldConfig
        REGISTER_CLASS_MANUAL_PART_PhysicsWorldConfig();
    #endif

    // PhysicsWorldConfig& PhysicsWorldConfig::operator =(const PhysicsWorldConfig&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<PhysicsWorldConfig>(engine, "PhysicsWorldConfig");
}

#endif // def URHO3D_PHYSICS

#ifdef URHO3D_URHO2D

// struct DelayedWorldTransform2D | File: ../Urho2D/PhysicsWorld2D.h
static void Register_DelayedWorldTransform2D(asIScriptEngine* engine)
{
    // DelayedWorldTransform2D::~DelayedWorldTransform2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("DelayedWorldTransform2D", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(DelayedWorldTransform2D), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_DelayedWorldTransform2D<DelayedWorldTransform2D>(engine, "DelayedWorldTransform2D");
    CollectMembers_DelayedWorldTransform2D(members);
    RegisterMembers(engine, "DelayedWorldTransform2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_DelayedWorldTransform2D
        REGISTER_CLASS_MANUAL_PART_DelayedWorldTransform2D();
    #endif

    // DelayedWorldTransform2D& DelayedWorldTransform2D::operator =(const DelayedWorldTransform2D&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DelayedWorldTransform2D>(engine, "DelayedWorldTransform2D");
}

// struct Particle2D | File: ../Urho2D/ParticleEmitter2D.h
static void Register_Particle2D(asIScriptEngine* engine)
{
    // Particle2D::~Particle2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("Particle2D", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(Particle2D), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Particle2D<Particle2D>(engine, "Particle2D");
    CollectMembers_Particle2D(members);
    RegisterMembers(engine, "Particle2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Particle2D
        REGISTER_CLASS_MANUAL_PART_Particle2D();
    #endif

    // Particle2D& Particle2D::operator =(const Particle2D&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Particle2D>(engine, "Particle2D");
}

// struct PhysicsRaycastResult2D | File: ../Urho2D/PhysicsWorld2D.h
static void Register_PhysicsRaycastResult2D(asIScriptEngine* engine)
{
    // PhysicsRaycastResult2D::~PhysicsRaycastResult2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("PhysicsRaycastResult2D", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(PhysicsRaycastResult2D), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_PhysicsRaycastResult2D<PhysicsRaycastResult2D>(engine, "PhysicsRaycastResult2D");
    CollectMembers_PhysicsRaycastResult2D(members);
    RegisterMembers(engine, "PhysicsRaycastResult2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_PhysicsRaycastResult2D
        REGISTER_CLASS_MANUAL_PART_PhysicsRaycastResult2D();
    #endif

    // PhysicsRaycastResult2D& PhysicsRaycastResult2D::operator =(const PhysicsRaycastResult2D&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<PhysicsRaycastResult2D>(engine, "PhysicsRaycastResult2D");
}

// struct SourceBatch2D | File: ../Urho2D/Drawable2D.h
static void Register_SourceBatch2D(asIScriptEngine* engine)
{
    // SourceBatch2D::~SourceBatch2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("SourceBatch2D", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(SourceBatch2D), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_SourceBatch2D<SourceBatch2D>(engine, "SourceBatch2D");
    CollectMembers_SourceBatch2D(members);
    RegisterMembers(engine, "SourceBatch2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_SourceBatch2D
        REGISTER_CLASS_MANUAL_PART_SourceBatch2D();
    #endif

    // SourceBatch2D& SourceBatch2D::operator =(const SourceBatch2D&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<SourceBatch2D>(engine, "SourceBatch2D");
}

// struct TileMapInfo2D | File: ../Urho2D/TileMapDefs2D.h
static void Register_TileMapInfo2D(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("TileMapInfo2D", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("TileMapInfo2D", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);

    MemberCollection members;
    RegisterMembers_TileMapInfo2D<TileMapInfo2D>(engine, "TileMapInfo2D");
    CollectMembers_TileMapInfo2D(members);
    RegisterMembers(engine, "TileMapInfo2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TileMapInfo2D
        REGISTER_CLASS_MANUAL_PART_TileMapInfo2D();
    #endif

    // TileMapInfo2D& TileMapInfo2D::operator =(const TileMapInfo2D&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<TileMapInfo2D>(engine, "TileMapInfo2D");
}

// struct Vertex2D | File: ../Urho2D/Drawable2D.h
static void Register_Vertex2D(asIScriptEngine* engine)
{
    // Vertex2D::~Vertex2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("Vertex2D", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(Vertex2D), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_Vertex2D<Vertex2D>(engine, "Vertex2D");
    CollectMembers_Vertex2D(members);
    RegisterMembers(engine, "Vertex2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Vertex2D
        REGISTER_CLASS_MANUAL_PART_Vertex2D();
    #endif

    // Vertex2D& Vertex2D::operator =(const Vertex2D&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Vertex2D>(engine, "Vertex2D");
}

#endif // def URHO3D_URHO2D

// AnimationState::AnimationState(AnimatedModel* model, Animation* animation)
static AnimationState* AnimationState__AnimationState_AnimatedModelstar_Animationstar(AnimatedModel* model, Animation* animation)
{
    return new AnimationState(model, animation);
}

// AnimationState::AnimationState(Node* node, Animation* animation)
static AnimationState* AnimationState__AnimationState_Nodestar_Animationstar(Node* node, Animation* animation)
{
    return new AnimationState(node, animation);
}

// class AnimationState | File: ../Graphics/AnimationState.h
static void Register_AnimationState(asIScriptEngine* engine)
{
    // AnimationState::AnimationState(AnimatedModel* model, Animation* animation)
    engine->RegisterObjectBehaviour("AnimationState", asBEHAVE_FACTORY, "AnimationState@+ f(AnimatedModel@+, Animation@+)", AS_FUNCTION(AnimationState__AnimationState_AnimatedModelstar_Animationstar) , AS_CALL_CDECL);
    // AnimationState::AnimationState(Node* node, Animation* animation)
    engine->RegisterObjectBehaviour("AnimationState", asBEHAVE_FACTORY, "AnimationState@+ f(Node@+, Animation@+)", AS_FUNCTION(AnimationState__AnimationState_Nodestar_Animationstar) , AS_CALL_CDECL);

    RegisterSubclass<RefCounted, AnimationState>(engine, "RefCounted", "AnimationState");

    MemberCollection members;
    RegisterMembers_AnimationState<AnimationState>(engine, "AnimationState");
    CollectMembers_AnimationState(members);
    RegisterMembers(engine, "AnimationState", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AnimationState
        REGISTER_CLASS_MANUAL_PART_AnimationState();
    #endif
}

// class AttributeAccessor | File: ../Core/Attribute.h
static void Register_AttributeAccessor(asIScriptEngine* engine)
{
    RegisterSubclass<RefCounted, AttributeAccessor>(engine, "RefCounted", "AttributeAccessor");

    MemberCollection members;
    RegisterMembers_AttributeAccessor<AttributeAccessor>(engine, "AttributeAccessor");
    CollectMembers_AttributeAccessor(members);
    RegisterMembers(engine, "AttributeAccessor", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AttributeAccessor
        REGISTER_CLASS_MANUAL_PART_AttributeAccessor();
    #endif
}

// explicit BatchGroup::BatchGroup(const Batch& batch)
static void BatchGroup__BatchGroup_constspBatchamp(BatchGroup* _ptr, const Batch& batch)
{
    new(_ptr) BatchGroup(batch);
}

// struct BatchGroup | File: ../Graphics/Batch.h
static void Register_BatchGroup(asIScriptEngine* engine)
{
    // explicit BatchGroup::BatchGroup(const Batch& batch)
    engine->RegisterObjectBehaviour("BatchGroup", asBEHAVE_CONSTRUCT, "void f(const Batch&in)", AS_FUNCTION_OBJFIRST(BatchGroup__BatchGroup_constspBatchamp), AS_CALL_CDECL_OBJFIRST);

    // BatchGroup::~BatchGroup() = default
    engine->RegisterObjectBehaviour("BatchGroup", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(BatchGroup), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_BatchGroup<BatchGroup>(engine, "BatchGroup");
    CollectMembers_BatchGroup(members);
    RegisterMembers(engine, "BatchGroup", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_BatchGroup
        REGISTER_CLASS_MANUAL_PART_BatchGroup();
    #endif

    // BatchGroup& BatchGroup::operator =(const BatchGroup&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<BatchGroup>(engine, "BatchGroup");
}

// struct ComponentReplicationState | File: ../Scene/ReplicationState.h
static void Register_ComponentReplicationState(asIScriptEngine* engine)
{
    // ComponentReplicationState::~ComponentReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("ComponentReplicationState", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(ComponentReplicationState), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_ComponentReplicationState<ComponentReplicationState>(engine, "ComponentReplicationState");
    CollectMembers_ComponentReplicationState(members);
    RegisterMembers(engine, "ComponentReplicationState", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ComponentReplicationState
        REGISTER_CLASS_MANUAL_PART_ComponentReplicationState();
    #endif

    // ComponentReplicationState& ComponentReplicationState::operator =(const ComponentReplicationState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ComponentReplicationState>(engine, "ComponentReplicationState");
}

// class Context | File: ../Core/Context.h
static void Register_Context(asIScriptEngine* engine)
{
    RegisterSubclass<RefCounted, Context>(engine, "RefCounted", "Context");

    MemberCollection members;
    RegisterMembers_Context<Context>(engine, "Context");
    CollectMembers_Context(members);
    RegisterMembers(engine, "Context", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Context
        REGISTER_CLASS_MANUAL_PART_Context();
    #endif
}

// class EventReceiverGroup | File: ../Core/Context.h
static void Register_EventReceiverGroup(asIScriptEngine* engine)
{
    RegisterSubclass<RefCounted, EventReceiverGroup>(engine, "RefCounted", "EventReceiverGroup");

    MemberCollection members;
    RegisterMembers_EventReceiverGroup<EventReceiverGroup>(engine, "EventReceiverGroup");
    CollectMembers_EventReceiverGroup(members);
    RegisterMembers(engine, "EventReceiverGroup", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_EventReceiverGroup
        REGISTER_CLASS_MANUAL_PART_EventReceiverGroup();
    #endif
}

// class FontFace | File: ../UI/FontFace.h
static void Register_FontFace(asIScriptEngine* engine)
{
    RegisterSubclass<RefCounted, FontFace>(engine, "RefCounted", "FontFace");

    MemberCollection members;
    RegisterMembers_FontFace<FontFace>(engine, "FontFace");
    CollectMembers_FontFace(members);
    RegisterMembers(engine, "FontFace", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_FontFace
        REGISTER_CLASS_MANUAL_PART_FontFace();
    #endif
}

// struct NodeReplicationState | File: ../Scene/ReplicationState.h
static void Register_NodeReplicationState(asIScriptEngine* engine)
{
    // NodeReplicationState::~NodeReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("NodeReplicationState", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(NodeReplicationState), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_NodeReplicationState<NodeReplicationState>(engine, "NodeReplicationState");
    CollectMembers_NodeReplicationState(members);
    RegisterMembers(engine, "NodeReplicationState", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_NodeReplicationState
        REGISTER_CLASS_MANUAL_PART_NodeReplicationState();
    #endif

    // NodeReplicationState& NodeReplicationState::operator =(const NodeReplicationState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<NodeReplicationState>(engine, "NodeReplicationState");
}

// class Object | File: ../Core/Object.h
static void Register_Object(asIScriptEngine* engine)
{
    RegisterSubclass<RefCounted, Object>(engine, "RefCounted", "Object");

    MemberCollection members;
    RegisterMembers_Object<Object>(engine, "Object");
    CollectMembers_Object(members);
    RegisterMembers(engine, "Object", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Object
        REGISTER_CLASS_MANUAL_PART_Object();
    #endif
}

// class ObjectFactory | File: ../Core/Object.h
static void Register_ObjectFactory(asIScriptEngine* engine)
{
    RegisterSubclass<RefCounted, ObjectFactory>(engine, "RefCounted", "ObjectFactory");

    MemberCollection members;
    RegisterMembers_ObjectFactory<ObjectFactory>(engine, "ObjectFactory");
    CollectMembers_ObjectFactory(members);
    RegisterMembers(engine, "ObjectFactory", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ObjectFactory
        REGISTER_CLASS_MANUAL_PART_ObjectFactory();
    #endif
}

// explicit Pass::Pass(const String& name)
static Pass* Pass__Pass_constspStringamp(const String& name)
{
    return new Pass(name);
}

// class Pass | File: ../Graphics/Technique.h
static void Register_Pass(asIScriptEngine* engine)
{
    // explicit Pass::Pass(const String& name)
    engine->RegisterObjectBehaviour("Pass", asBEHAVE_FACTORY, "Pass@+ f(const String&in)", AS_FUNCTION(Pass__Pass_constspStringamp) , AS_CALL_CDECL);

    RegisterSubclass<RefCounted, Pass>(engine, "RefCounted", "Pass");

    MemberCollection members;
    RegisterMembers_Pass<Pass>(engine, "Pass");
    CollectMembers_Pass(members);
    RegisterMembers(engine, "Pass", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Pass
        REGISTER_CLASS_MANUAL_PART_Pass();
    #endif
}

// class RenderPath | File: ../Graphics/RenderPath.h
static void Register_RenderPath(asIScriptEngine* engine)
{
    RegisterSubclass<RefCounted, RenderPath>(engine, "RefCounted", "RenderPath");

    MemberCollection members;
    RegisterMembers_RenderPath<RenderPath>(engine, "RenderPath");
    CollectMembers_RenderPath(members);
    RegisterMembers(engine, "RenderPath", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_RenderPath
        REGISTER_CLASS_MANUAL_PART_RenderPath();
    #endif
}

// explicit RenderSurface::RenderSurface(Texture* parentTexture)
static RenderSurface* RenderSurface__RenderSurface_Texturestar(Texture* parentTexture)
{
    return new RenderSurface(parentTexture);
}

// class RenderSurface | File: ../Graphics/RenderSurface.h
static void Register_RenderSurface(asIScriptEngine* engine)
{
    // explicit RenderSurface::RenderSurface(Texture* parentTexture)
    engine->RegisterObjectBehaviour("RenderSurface", asBEHAVE_FACTORY, "RenderSurface@+ f(Texture@+)", AS_FUNCTION(RenderSurface__RenderSurface_Texturestar) , AS_CALL_CDECL);

    RegisterSubclass<RefCounted, RenderSurface>(engine, "RefCounted", "RenderSurface");

    MemberCollection members;
    RegisterMembers_RenderSurface<RenderSurface>(engine, "RenderSurface");
    CollectMembers_RenderSurface(members);
    RegisterMembers(engine, "RenderSurface", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_RenderSurface
        REGISTER_CLASS_MANUAL_PART_RenderSurface();
    #endif
}

// struct SceneReplicationState | File: ../Scene/ReplicationState.h
static void Register_SceneReplicationState(asIScriptEngine* engine)
{
    // SceneReplicationState::~SceneReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("SceneReplicationState", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(SceneReplicationState), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_SceneReplicationState<SceneReplicationState>(engine, "SceneReplicationState");
    CollectMembers_SceneReplicationState(members);
    RegisterMembers(engine, "SceneReplicationState", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_SceneReplicationState
        REGISTER_CLASS_MANUAL_PART_SceneReplicationState();
    #endif

    // SceneReplicationState& SceneReplicationState::operator =(const SceneReplicationState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<SceneReplicationState>(engine, "SceneReplicationState");
}

// ShaderVariation::ShaderVariation(Shader* owner, ShaderType type)
static ShaderVariation* ShaderVariation__ShaderVariation_Shaderstar_ShaderType(Shader* owner, ShaderType type)
{
    return new ShaderVariation(owner, type);
}

// class ShaderVariation | File: ../Graphics/ShaderVariation.h
static void Register_ShaderVariation(asIScriptEngine* engine)
{
    // ShaderVariation::ShaderVariation(Shader* owner, ShaderType type)
    engine->RegisterObjectBehaviour("ShaderVariation", asBEHAVE_FACTORY, "ShaderVariation@+ f(Shader@+, ShaderType)", AS_FUNCTION(ShaderVariation__ShaderVariation_Shaderstar_ShaderType) , AS_CALL_CDECL);

    RegisterSubclass<RefCounted, ShaderVariation>(engine, "RefCounted", "ShaderVariation");

    MemberCollection members;
    RegisterMembers_ShaderVariation<ShaderVariation>(engine, "ShaderVariation");
    CollectMembers_ShaderVariation(members);
    RegisterMembers(engine, "ShaderVariation", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ShaderVariation
        REGISTER_CLASS_MANUAL_PART_ShaderVariation();
    #endif
}

// class SoundStream | File: ../Audio/SoundStream.h
static void Register_SoundStream(asIScriptEngine* engine)
{
    RegisterSubclass<RefCounted, SoundStream>(engine, "RefCounted", "SoundStream");

    MemberCollection members;
    RegisterMembers_SoundStream<SoundStream>(engine, "SoundStream");
    CollectMembers_SoundStream(members);
    RegisterMembers(engine, "SoundStream", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_SoundStream
        REGISTER_CLASS_MANUAL_PART_SoundStream();
    #endif
}

// ValueAnimationInfo::ValueAnimationInfo(ValueAnimation* animation, WrapMode wrapMode, float speed)
static ValueAnimationInfo* ValueAnimationInfo__ValueAnimationInfo_ValueAnimationstar_WrapMode_float(ValueAnimation* animation, WrapMode wrapMode, float speed)
{
    return new ValueAnimationInfo(animation, wrapMode, speed);
}

// ValueAnimationInfo::ValueAnimationInfo(Object* target, ValueAnimation* animation, WrapMode wrapMode, float speed)
static ValueAnimationInfo* ValueAnimationInfo__ValueAnimationInfo_Objectstar_ValueAnimationstar_WrapMode_float(Object* target, ValueAnimation* animation, WrapMode wrapMode, float speed)
{
    return new ValueAnimationInfo(target, animation, wrapMode, speed);
}

// ValueAnimationInfo::ValueAnimationInfo(const ValueAnimationInfo& other)
static ValueAnimationInfo* ValueAnimationInfo__ValueAnimationInfo_constspValueAnimationInfoamp(const ValueAnimationInfo& other)
{
    return new ValueAnimationInfo(other);
}

// class ValueAnimationInfo | File: ../Scene/ValueAnimationInfo.h
static void Register_ValueAnimationInfo(asIScriptEngine* engine)
{
    // ValueAnimationInfo::ValueAnimationInfo(ValueAnimation* animation, WrapMode wrapMode, float speed)
    engine->RegisterObjectBehaviour("ValueAnimationInfo", asBEHAVE_FACTORY, "ValueAnimationInfo@+ f(ValueAnimation@+, WrapMode, float)", AS_FUNCTION(ValueAnimationInfo__ValueAnimationInfo_ValueAnimationstar_WrapMode_float) , AS_CALL_CDECL);
    // ValueAnimationInfo::ValueAnimationInfo(Object* target, ValueAnimation* animation, WrapMode wrapMode, float speed)
    engine->RegisterObjectBehaviour("ValueAnimationInfo", asBEHAVE_FACTORY, "ValueAnimationInfo@+ f(Object@+, ValueAnimation@+, WrapMode, float)", AS_FUNCTION(ValueAnimationInfo__ValueAnimationInfo_Objectstar_ValueAnimationstar_WrapMode_float) , AS_CALL_CDECL);
    // ValueAnimationInfo::ValueAnimationInfo(const ValueAnimationInfo& other)
    engine->RegisterObjectBehaviour("ValueAnimationInfo", asBEHAVE_FACTORY, "ValueAnimationInfo@+ f(const ValueAnimationInfo&in)", AS_FUNCTION(ValueAnimationInfo__ValueAnimationInfo_constspValueAnimationInfoamp) , AS_CALL_CDECL);

    RegisterSubclass<RefCounted, ValueAnimationInfo>(engine, "RefCounted", "ValueAnimationInfo");

    MemberCollection members;
    RegisterMembers_ValueAnimationInfo<ValueAnimationInfo>(engine, "ValueAnimationInfo");
    CollectMembers_ValueAnimationInfo(members);
    RegisterMembers(engine, "ValueAnimationInfo", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ValueAnimationInfo
        REGISTER_CLASS_MANUAL_PART_ValueAnimationInfo();
    #endif
}

#ifdef URHO3D_NAVIGATION

// struct SimpleNavBuildData | File: ../Navigation/NavBuildData.h
static void Register_SimpleNavBuildData(asIScriptEngine* engine)
{
    // SimpleNavBuildData::~SimpleNavBuildData() override
    engine->RegisterObjectBehaviour("SimpleNavBuildData", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(SimpleNavBuildData), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_SimpleNavBuildData<SimpleNavBuildData>(engine, "SimpleNavBuildData");
    CollectMembers_SimpleNavBuildData(members);
    RegisterMembers(engine, "SimpleNavBuildData", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_SimpleNavBuildData
        REGISTER_CLASS_MANUAL_PART_SimpleNavBuildData();
    #endif

    // SimpleNavBuildData& SimpleNavBuildData::operator =(const SimpleNavBuildData&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<SimpleNavBuildData>(engine, "SimpleNavBuildData");
}

#endif // def URHO3D_NAVIGATION

#ifdef URHO3D_NETWORK

// HttpRequest::HttpRequest(const String& url, const String& verb, const Vector<String>& headers, const String& postData)
static HttpRequest* HttpRequest__HttpRequest_constspStringamp_constspStringamp_constspVectorlesStringgreamp_constspStringamp(const String& url, const String& verb, CScriptArray* headers_conv, const String& postData)
{
    Vector<String> headers = ArrayToVector<String>(headers_conv);
    return new HttpRequest(url, verb, headers, postData);
}

// class HttpRequest | File: ../Network/HttpRequest.h
static void Register_HttpRequest(asIScriptEngine* engine)
{
    // HttpRequest::HttpRequest(const String& url, const String& verb, const Vector<String>& headers, const String& postData)
    engine->RegisterObjectBehaviour("HttpRequest", asBEHAVE_FACTORY, "HttpRequest@+ f(const String&in, const String&in, Array<String>@+, const String&in)", AS_FUNCTION(HttpRequest__HttpRequest_constspStringamp_constspStringamp_constspVectorlesStringgreamp_constspStringamp) , AS_CALL_CDECL);

    RegisterSubclass<RefCounted, HttpRequest>(engine, "RefCounted", "HttpRequest");
    RegisterSubclass<Deserializer, HttpRequest>(engine, "Deserializer", "HttpRequest");

    MemberCollection members;
    RegisterMembers_HttpRequest<HttpRequest>(engine, "HttpRequest");
    CollectMembers_HttpRequest(members);
    RegisterMembers(engine, "HttpRequest", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_HttpRequest
        REGISTER_CLASS_MANUAL_PART_HttpRequest();
    #endif
}

#endif // def URHO3D_NETWORK

#ifdef URHO3D_PHYSICS

// struct CollisionGeometryData | File: ../Physics/CollisionShape.h
static void Register_CollisionGeometryData(asIScriptEngine* engine)
{
    RegisterSubclass<RefCounted, CollisionGeometryData>(engine, "RefCounted", "CollisionGeometryData");

    MemberCollection members;
    RegisterMembers_CollisionGeometryData<CollisionGeometryData>(engine, "CollisionGeometryData");
    CollectMembers_CollisionGeometryData(members);
    RegisterMembers(engine, "CollisionGeometryData", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CollisionGeometryData
        REGISTER_CLASS_MANUAL_PART_CollisionGeometryData();
    #endif
}

#endif // def URHO3D_PHYSICS

#ifdef URHO3D_URHO2D

// class PropertySet2D | File: ../Urho2D/TileMapDefs2D.h
static void Register_PropertySet2D(asIScriptEngine* engine)
{
    RegisterSubclass<RefCounted, PropertySet2D>(engine, "RefCounted", "PropertySet2D");

    MemberCollection members;
    RegisterMembers_PropertySet2D<PropertySet2D>(engine, "PropertySet2D");
    CollectMembers_PropertySet2D(members);
    RegisterMembers(engine, "PropertySet2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_PropertySet2D
        REGISTER_CLASS_MANUAL_PART_PropertySet2D();
    #endif
}

// class Tile2D | File: ../Urho2D/TileMapDefs2D.h
static void Register_Tile2D(asIScriptEngine* engine)
{
    RegisterSubclass<RefCounted, Tile2D>(engine, "RefCounted", "Tile2D");

    MemberCollection members;
    RegisterMembers_Tile2D<Tile2D>(engine, "Tile2D");
    CollectMembers_Tile2D(members);
    RegisterMembers(engine, "Tile2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Tile2D
        REGISTER_CLASS_MANUAL_PART_Tile2D();
    #endif
}

// class TileMapObject2D | File: ../Urho2D/TileMapDefs2D.h
static void Register_TileMapObject2D(asIScriptEngine* engine)
{
    RegisterSubclass<RefCounted, TileMapObject2D>(engine, "RefCounted", "TileMapObject2D");

    MemberCollection members;
    RegisterMembers_TileMapObject2D<TileMapObject2D>(engine, "TileMapObject2D");
    CollectMembers_TileMapObject2D(members);
    RegisterMembers(engine, "TileMapObject2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TileMapObject2D
        REGISTER_CLASS_MANUAL_PART_TileMapObject2D();
    #endif
}

// TmxLayer2D::TmxLayer2D(TmxFile2D* tmxFile, TileMapLayerType2D type)
static TmxLayer2D* TmxLayer2D__TmxLayer2D_TmxFile2Dstar_TileMapLayerType2D(TmxFile2D* tmxFile, TileMapLayerType2D type)
{
    return new TmxLayer2D(tmxFile, type);
}

// class TmxLayer2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxLayer2D(asIScriptEngine* engine)
{
    // TmxLayer2D::TmxLayer2D(TmxFile2D* tmxFile, TileMapLayerType2D type)
    engine->RegisterObjectBehaviour("TmxLayer2D", asBEHAVE_FACTORY, "TmxLayer2D@+ f(TmxFile2D@+, TileMapLayerType2D)", AS_FUNCTION(TmxLayer2D__TmxLayer2D_TmxFile2Dstar_TileMapLayerType2D) , AS_CALL_CDECL);

    RegisterSubclass<RefCounted, TmxLayer2D>(engine, "RefCounted", "TmxLayer2D");

    MemberCollection members;
    RegisterMembers_TmxLayer2D<TmxLayer2D>(engine, "TmxLayer2D");
    CollectMembers_TmxLayer2D(members);
    RegisterMembers(engine, "TmxLayer2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TmxLayer2D
        REGISTER_CLASS_MANUAL_PART_TmxLayer2D();
    #endif
}

#endif // def URHO3D_URHO2D

// AttributeAnimationInfo::AttributeAnimationInfo(Animatable* animatable, const AttributeInfo& attributeInfo, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed)
static AttributeAnimationInfo* AttributeAnimationInfo__AttributeAnimationInfo_Animatablestar_constspAttributeInfoamp_ValueAnimationstar_WrapMode_float(Animatable* animatable, const AttributeInfo& attributeInfo, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed)
{
    return new AttributeAnimationInfo(animatable, attributeInfo, attributeAnimation, wrapMode, speed);
}

// AttributeAnimationInfo::AttributeAnimationInfo(const AttributeAnimationInfo& other)
static AttributeAnimationInfo* AttributeAnimationInfo__AttributeAnimationInfo_constspAttributeAnimationInfoamp(const AttributeAnimationInfo& other)
{
    return new AttributeAnimationInfo(other);
}

// class AttributeAnimationInfo | File: ../Scene/Animatable.h
static void Register_AttributeAnimationInfo(asIScriptEngine* engine)
{
    // AttributeAnimationInfo::AttributeAnimationInfo(Animatable* animatable, const AttributeInfo& attributeInfo, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed)
    engine->RegisterObjectBehaviour("AttributeAnimationInfo", asBEHAVE_FACTORY, "AttributeAnimationInfo@+ f(Animatable@+, const AttributeInfo&in, ValueAnimation@+, WrapMode, float)", AS_FUNCTION(AttributeAnimationInfo__AttributeAnimationInfo_Animatablestar_constspAttributeInfoamp_ValueAnimationstar_WrapMode_float) , AS_CALL_CDECL);
    // AttributeAnimationInfo::AttributeAnimationInfo(const AttributeAnimationInfo& other)
    engine->RegisterObjectBehaviour("AttributeAnimationInfo", asBEHAVE_FACTORY, "AttributeAnimationInfo@+ f(const AttributeAnimationInfo&in)", AS_FUNCTION(AttributeAnimationInfo__AttributeAnimationInfo_constspAttributeAnimationInfoamp) , AS_CALL_CDECL);

    RegisterSubclass<ValueAnimationInfo, AttributeAnimationInfo>(engine, "ValueAnimationInfo", "AttributeAnimationInfo");
    RegisterSubclass<RefCounted, AttributeAnimationInfo>(engine, "RefCounted", "AttributeAnimationInfo");

    MemberCollection members;
    RegisterMembers_AttributeAnimationInfo<AttributeAnimationInfo>(engine, "AttributeAnimationInfo");
    CollectMembers_AttributeAnimationInfo(members);
    RegisterMembers(engine, "AttributeAnimationInfo", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AttributeAnimationInfo
        REGISTER_CLASS_MANUAL_PART_AttributeAnimationInfo();
    #endif
}

// explicit Audio::Audio(Context* context)
static Audio* Audio__Audio_Contextstar()
{
    Context* context = GetScriptContext();
    return new Audio(context);
}

// class Audio | File: ../Audio/Audio.h
static void Register_Audio(asIScriptEngine* engine)
{
    // explicit Audio::Audio(Context* context)
    engine->RegisterObjectBehaviour("Audio", asBEHAVE_FACTORY, "Audio@+ f()", AS_FUNCTION(Audio__Audio_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Audio>(engine, "Object", "Audio");
    RegisterSubclass<RefCounted, Audio>(engine, "RefCounted", "Audio");

    MemberCollection members;
    RegisterMembers_Audio<Audio>(engine, "Audio");
    CollectMembers_Audio(members);
    RegisterMembers(engine, "Audio", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Audio
        REGISTER_CLASS_MANUAL_PART_Audio();
    #endif
}

// class BufferedSoundStream | File: ../Audio/BufferedSoundStream.h
static void Register_BufferedSoundStream(asIScriptEngine* engine)
{
    RegisterSubclass<SoundStream, BufferedSoundStream>(engine, "SoundStream", "BufferedSoundStream");
    RegisterSubclass<RefCounted, BufferedSoundStream>(engine, "RefCounted", "BufferedSoundStream");

    MemberCollection members;
    RegisterMembers_BufferedSoundStream<BufferedSoundStream>(engine, "BufferedSoundStream");
    CollectMembers_BufferedSoundStream(members);
    RegisterMembers(engine, "BufferedSoundStream", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_BufferedSoundStream
        REGISTER_CLASS_MANUAL_PART_BufferedSoundStream();
    #endif
}

// explicit Console::Console(Context* context)
static Console* Console__Console_Contextstar()
{
    Context* context = GetScriptContext();
    return new Console(context);
}

// class Console | File: ../Engine/Console.h
static void Register_Console(asIScriptEngine* engine)
{
    // explicit Console::Console(Context* context)
    engine->RegisterObjectBehaviour("Console", asBEHAVE_FACTORY, "Console@+ f()", AS_FUNCTION(Console__Console_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Console>(engine, "Object", "Console");
    RegisterSubclass<RefCounted, Console>(engine, "RefCounted", "Console");

    MemberCollection members;
    RegisterMembers_Console<Console>(engine, "Console");
    CollectMembers_Console(members);
    RegisterMembers(engine, "Console", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Console
        REGISTER_CLASS_MANUAL_PART_Console();
    #endif
}

// explicit ConstantBuffer::ConstantBuffer(Context* context)
static ConstantBuffer* ConstantBuffer__ConstantBuffer_Contextstar()
{
    Context* context = GetScriptContext();
    return new ConstantBuffer(context);
}

// class ConstantBuffer | File: ../Graphics/ConstantBuffer.h
static void Register_ConstantBuffer(asIScriptEngine* engine)
{
    // explicit ConstantBuffer::ConstantBuffer(Context* context)
    engine->RegisterObjectBehaviour("ConstantBuffer", asBEHAVE_FACTORY, "ConstantBuffer@+ f()", AS_FUNCTION(ConstantBuffer__ConstantBuffer_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, ConstantBuffer>(engine, "Object", "ConstantBuffer");
    RegisterSubclass<RefCounted, ConstantBuffer>(engine, "RefCounted", "ConstantBuffer");

    MemberCollection members;
    RegisterMembers_ConstantBuffer<ConstantBuffer>(engine, "ConstantBuffer");
    CollectMembers_ConstantBuffer(members);
    RegisterMembers(engine, "ConstantBuffer", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ConstantBuffer
        REGISTER_CLASS_MANUAL_PART_ConstantBuffer();
    #endif
}

// explicit DebugHud::DebugHud(Context* context)
static DebugHud* DebugHud__DebugHud_Contextstar()
{
    Context* context = GetScriptContext();
    return new DebugHud(context);
}

// class DebugHud | File: ../Engine/DebugHud.h
static void Register_DebugHud(asIScriptEngine* engine)
{
    // explicit DebugHud::DebugHud(Context* context)
    engine->RegisterObjectBehaviour("DebugHud", asBEHAVE_FACTORY, "DebugHud@+ f()", AS_FUNCTION(DebugHud__DebugHud_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, DebugHud>(engine, "Object", "DebugHud");
    RegisterSubclass<RefCounted, DebugHud>(engine, "RefCounted", "DebugHud");

    MemberCollection members;
    RegisterMembers_DebugHud<DebugHud>(engine, "DebugHud");
    CollectMembers_DebugHud(members);
    RegisterMembers(engine, "DebugHud", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_DebugHud
        REGISTER_CLASS_MANUAL_PART_DebugHud();
    #endif
}

// explicit Engine::Engine(Context* context)
static Engine* Engine__Engine_Contextstar()
{
    Context* context = GetScriptContext();
    return new Engine(context);
}

// class Engine | File: ../Engine/Engine.h
static void Register_Engine(asIScriptEngine* engine)
{
    // explicit Engine::Engine(Context* context)
    engine->RegisterObjectBehaviour("Engine", asBEHAVE_FACTORY, "Engine@+ f()", AS_FUNCTION(Engine__Engine_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Engine>(engine, "Object", "Engine");
    RegisterSubclass<RefCounted, Engine>(engine, "RefCounted", "Engine");

    MemberCollection members;
    RegisterMembers_Engine<Engine>(engine, "Engine");
    CollectMembers_Engine(members);
    RegisterMembers(engine, "Engine", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Engine
        REGISTER_CLASS_MANUAL_PART_Engine();
    #endif
}

// explicit File::File(Context* context)
static File* File__File_Contextstar()
{
    Context* context = GetScriptContext();
    return new File(context);
}

// File::File(Context* context, const String& fileName, FileMode mode = FILE_READ)
static File* File__File_Contextstar_constspStringamp_FileMode(const String& fileName, FileMode mode)
{
    Context* context = GetScriptContext();
    return new File(context, fileName, mode);
}

// File::File(Context* context, PackageFile* package, const String& fileName)
static File* File__File_Contextstar_PackageFilestar_constspStringamp(PackageFile* package, const String& fileName)
{
    Context* context = GetScriptContext();
    return new File(context, package, fileName);
}

// class File | File: ../IO/File.h
static void Register_File(asIScriptEngine* engine)
{
    // explicit File::File(Context* context)
    engine->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@+ f()", AS_FUNCTION(File__File_Contextstar) , AS_CALL_CDECL);
    // File::File(Context* context, const String& fileName, FileMode mode = FILE_READ)
    engine->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@+ f(const String&in, FileMode = FILE_READ)", AS_FUNCTION(File__File_Contextstar_constspStringamp_FileMode) , AS_CALL_CDECL);
    // File::File(Context* context, PackageFile* package, const String& fileName)
    engine->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@+ f(PackageFile@+, const String&in)", AS_FUNCTION(File__File_Contextstar_PackageFilestar_constspStringamp) , AS_CALL_CDECL);

    RegisterSubclass<Object, File>(engine, "Object", "File");
    RegisterSubclass<RefCounted, File>(engine, "RefCounted", "File");
    RegisterSubclass<Deserializer, File>(engine, "Deserializer", "File");
    RegisterSubclass<Serializer, File>(engine, "Serializer", "File");

    MemberCollection members;
    RegisterMembers_File<File>(engine, "File");
    CollectMembers_File(members);
    RegisterMembers(engine, "File", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_File
        REGISTER_CLASS_MANUAL_PART_File();
    #endif
}

// explicit FileSelector::FileSelector(Context* context)
static FileSelector* FileSelector__FileSelector_Contextstar()
{
    Context* context = GetScriptContext();
    return new FileSelector(context);
}

// class FileSelector | File: ../UI/FileSelector.h
static void Register_FileSelector(asIScriptEngine* engine)
{
    // explicit FileSelector::FileSelector(Context* context)
    engine->RegisterObjectBehaviour("FileSelector", asBEHAVE_FACTORY, "FileSelector@+ f()", AS_FUNCTION(FileSelector__FileSelector_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, FileSelector>(engine, "Object", "FileSelector");
    RegisterSubclass<RefCounted, FileSelector>(engine, "RefCounted", "FileSelector");

    MemberCollection members;
    RegisterMembers_FileSelector<FileSelector>(engine, "FileSelector");
    CollectMembers_FileSelector(members);
    RegisterMembers(engine, "FileSelector", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_FileSelector
        REGISTER_CLASS_MANUAL_PART_FileSelector();
    #endif
}

// explicit FileSystem::FileSystem(Context* context)
static FileSystem* FileSystem__FileSystem_Contextstar()
{
    Context* context = GetScriptContext();
    return new FileSystem(context);
}

// class FileSystem | File: ../IO/FileSystem.h
static void Register_FileSystem(asIScriptEngine* engine)
{
    // explicit FileSystem::FileSystem(Context* context)
    engine->RegisterObjectBehaviour("FileSystem", asBEHAVE_FACTORY, "FileSystem@+ f()", AS_FUNCTION(FileSystem__FileSystem_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, FileSystem>(engine, "Object", "FileSystem");
    RegisterSubclass<RefCounted, FileSystem>(engine, "RefCounted", "FileSystem");

    MemberCollection members;
    RegisterMembers_FileSystem<FileSystem>(engine, "FileSystem");
    CollectMembers_FileSystem(members);
    RegisterMembers(engine, "FileSystem", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_FileSystem
        REGISTER_CLASS_MANUAL_PART_FileSystem();
    #endif
}

// explicit FileWatcher::FileWatcher(Context* context)
static FileWatcher* FileWatcher__FileWatcher_Contextstar()
{
    Context* context = GetScriptContext();
    return new FileWatcher(context);
}

// class FileWatcher | File: ../IO/FileWatcher.h
static void Register_FileWatcher(asIScriptEngine* engine)
{
    // explicit FileWatcher::FileWatcher(Context* context)
    engine->RegisterObjectBehaviour("FileWatcher", asBEHAVE_FACTORY, "FileWatcher@+ f()", AS_FUNCTION(FileWatcher__FileWatcher_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, FileWatcher>(engine, "Object", "FileWatcher");
    RegisterSubclass<RefCounted, FileWatcher>(engine, "RefCounted", "FileWatcher");

    MemberCollection members;
    RegisterMembers_FileWatcher<FileWatcher>(engine, "FileWatcher");
    CollectMembers_FileWatcher(members);
    RegisterMembers(engine, "FileWatcher", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_FileWatcher
        REGISTER_CLASS_MANUAL_PART_FileWatcher();
    #endif
}

// explicit FontFaceBitmap::FontFaceBitmap(Font* font)
static FontFaceBitmap* FontFaceBitmap__FontFaceBitmap_Fontstar(Font* font)
{
    return new FontFaceBitmap(font);
}

// class FontFaceBitmap | File: ../UI/FontFaceBitmap.h
static void Register_FontFaceBitmap(asIScriptEngine* engine)
{
    // explicit FontFaceBitmap::FontFaceBitmap(Font* font)
    engine->RegisterObjectBehaviour("FontFaceBitmap", asBEHAVE_FACTORY, "FontFaceBitmap@+ f(Font@+)", AS_FUNCTION(FontFaceBitmap__FontFaceBitmap_Fontstar) , AS_CALL_CDECL);

    RegisterSubclass<FontFace, FontFaceBitmap>(engine, "FontFace", "FontFaceBitmap");
    RegisterSubclass<RefCounted, FontFaceBitmap>(engine, "RefCounted", "FontFaceBitmap");

    MemberCollection members;
    RegisterMembers_FontFaceBitmap<FontFaceBitmap>(engine, "FontFaceBitmap");
    CollectMembers_FontFaceBitmap(members);
    RegisterMembers(engine, "FontFaceBitmap", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_FontFaceBitmap
        REGISTER_CLASS_MANUAL_PART_FontFaceBitmap();
    #endif
}

// explicit FontFaceFreeType::FontFaceFreeType(Font* font)
static FontFaceFreeType* FontFaceFreeType__FontFaceFreeType_Fontstar(Font* font)
{
    return new FontFaceFreeType(font);
}

// class FontFaceFreeType | File: ../UI/FontFaceFreeType.h
static void Register_FontFaceFreeType(asIScriptEngine* engine)
{
    // explicit FontFaceFreeType::FontFaceFreeType(Font* font)
    engine->RegisterObjectBehaviour("FontFaceFreeType", asBEHAVE_FACTORY, "FontFaceFreeType@+ f(Font@+)", AS_FUNCTION(FontFaceFreeType__FontFaceFreeType_Fontstar) , AS_CALL_CDECL);

    RegisterSubclass<FontFace, FontFaceFreeType>(engine, "FontFace", "FontFaceFreeType");
    RegisterSubclass<RefCounted, FontFaceFreeType>(engine, "RefCounted", "FontFaceFreeType");

    MemberCollection members;
    RegisterMembers_FontFaceFreeType<FontFaceFreeType>(engine, "FontFaceFreeType");
    CollectMembers_FontFaceFreeType(members);
    RegisterMembers(engine, "FontFaceFreeType", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_FontFaceFreeType
        REGISTER_CLASS_MANUAL_PART_FontFaceFreeType();
    #endif
}

// explicit Geometry::Geometry(Context* context)
static Geometry* Geometry__Geometry_Contextstar()
{
    Context* context = GetScriptContext();
    return new Geometry(context);
}

// class Geometry | File: ../Graphics/Geometry.h
static void Register_Geometry(asIScriptEngine* engine)
{
    // explicit Geometry::Geometry(Context* context)
    engine->RegisterObjectBehaviour("Geometry", asBEHAVE_FACTORY, "Geometry@+ f()", AS_FUNCTION(Geometry__Geometry_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Geometry>(engine, "Object", "Geometry");
    RegisterSubclass<RefCounted, Geometry>(engine, "RefCounted", "Geometry");

    MemberCollection members;
    RegisterMembers_Geometry<Geometry>(engine, "Geometry");
    CollectMembers_Geometry(members);
    RegisterMembers(engine, "Geometry", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Geometry
        REGISTER_CLASS_MANUAL_PART_Geometry();
    #endif
}

// explicit Graphics::Graphics(Context* context)
static Graphics* Graphics__Graphics_Contextstar()
{
    Context* context = GetScriptContext();
    return new Graphics(context);
}

// class Graphics | File: ../Graphics/Graphics.h
static void Register_Graphics(asIScriptEngine* engine)
{
    // explicit Graphics::Graphics(Context* context)
    engine->RegisterObjectBehaviour("Graphics", asBEHAVE_FACTORY, "Graphics@+ f()", AS_FUNCTION(Graphics__Graphics_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Graphics>(engine, "Object", "Graphics");
    RegisterSubclass<RefCounted, Graphics>(engine, "RefCounted", "Graphics");

    MemberCollection members;
    RegisterMembers_Graphics<Graphics>(engine, "Graphics");
    CollectMembers_Graphics(members);
    RegisterMembers(engine, "Graphics", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Graphics
        REGISTER_CLASS_MANUAL_PART_Graphics();
    #endif
}

// explicit IndexBuffer::IndexBuffer(Context* context, bool forceHeadless = false)
static IndexBuffer* IndexBuffer__IndexBuffer_Contextstar_bool(bool forceHeadless)
{
    Context* context = GetScriptContext();
    return new IndexBuffer(context, forceHeadless);
}

// class IndexBuffer | File: ../Graphics/IndexBuffer.h
static void Register_IndexBuffer(asIScriptEngine* engine)
{
    // explicit IndexBuffer::IndexBuffer(Context* context, bool forceHeadless = false)
    engine->RegisterObjectBehaviour("IndexBuffer", asBEHAVE_FACTORY, "IndexBuffer@+ f(bool = false)", AS_FUNCTION(IndexBuffer__IndexBuffer_Contextstar_bool) , AS_CALL_CDECL);

    RegisterSubclass<Object, IndexBuffer>(engine, "Object", "IndexBuffer");
    RegisterSubclass<RefCounted, IndexBuffer>(engine, "RefCounted", "IndexBuffer");

    MemberCollection members;
    RegisterMembers_IndexBuffer<IndexBuffer>(engine, "IndexBuffer");
    CollectMembers_IndexBuffer(members);
    RegisterMembers(engine, "IndexBuffer", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_IndexBuffer
        REGISTER_CLASS_MANUAL_PART_IndexBuffer();
    #endif
}

// explicit Input::Input(Context* context)
static Input* Input__Input_Contextstar()
{
    Context* context = GetScriptContext();
    return new Input(context);
}

// class Input | File: ../Input/Input.h
static void Register_Input(asIScriptEngine* engine)
{
    // explicit Input::Input(Context* context)
    engine->RegisterObjectBehaviour("Input", asBEHAVE_FACTORY, "Input@+ f()", AS_FUNCTION(Input__Input_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Input>(engine, "Object", "Input");
    RegisterSubclass<RefCounted, Input>(engine, "RefCounted", "Input");

    MemberCollection members;
    RegisterMembers_Input<Input>(engine, "Input");
    CollectMembers_Input(members);
    RegisterMembers(engine, "Input", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Input
        REGISTER_CLASS_MANUAL_PART_Input();
    #endif
}

// explicit Localization::Localization(Context* context)
static Localization* Localization__Localization_Contextstar()
{
    Context* context = GetScriptContext();
    return new Localization(context);
}

// class Localization | File: ../Resource/Localization.h
static void Register_Localization(asIScriptEngine* engine)
{
    // explicit Localization::Localization(Context* context)
    engine->RegisterObjectBehaviour("Localization", asBEHAVE_FACTORY, "Localization@+ f()", AS_FUNCTION(Localization__Localization_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Localization>(engine, "Object", "Localization");
    RegisterSubclass<RefCounted, Localization>(engine, "RefCounted", "Localization");

    MemberCollection members;
    RegisterMembers_Localization<Localization>(engine, "Localization");
    CollectMembers_Localization(members);
    RegisterMembers(engine, "Localization", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Localization
        REGISTER_CLASS_MANUAL_PART_Localization();
    #endif
}

// explicit Log::Log(Context* context)
static Log* Log__Log_Contextstar()
{
    Context* context = GetScriptContext();
    return new Log(context);
}

// class Log | File: ../IO/Log.h
static void Register_Log(asIScriptEngine* engine)
{
    // explicit Log::Log(Context* context)
    engine->RegisterObjectBehaviour("Log", asBEHAVE_FACTORY, "Log@+ f()", AS_FUNCTION(Log__Log_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Log>(engine, "Object", "Log");
    RegisterSubclass<RefCounted, Log>(engine, "RefCounted", "Log");

    MemberCollection members;
    RegisterMembers_Log<Log>(engine, "Log");
    CollectMembers_Log(members);
    RegisterMembers(engine, "Log", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Log
        REGISTER_CLASS_MANUAL_PART_Log();
    #endif
}

// explicit MessageBox::MessageBox(Context* context, const String& messageString = String::EMPTY, const String& titleString = String::EMPTY, XMLFile* layoutFile = nullptr, XMLFile* styleFile = nullptr)
static MessageBox* MessageBox__MessageBox_Contextstar_constspStringamp_constspStringamp_XMLFilestar_XMLFilestar(const String& messageString, const String& titleString, XMLFile* layoutFile, XMLFile* styleFile)
{
    Context* context = GetScriptContext();
    return new MessageBox(context, messageString, titleString, layoutFile, styleFile);
}

// class MessageBox | File: ../UI/MessageBox.h
static void Register_MessageBox(asIScriptEngine* engine)
{
    // explicit MessageBox::MessageBox(Context* context, const String& messageString = String::EMPTY, const String& titleString = String::EMPTY, XMLFile* layoutFile = nullptr, XMLFile* styleFile = nullptr)
    engine->RegisterObjectBehaviour("MessageBox", asBEHAVE_FACTORY, "MessageBox@+ f(const String&in = String::EMPTY, const String&in = String::EMPTY, XMLFile@+ = null, XMLFile@+ = null)", AS_FUNCTION(MessageBox__MessageBox_Contextstar_constspStringamp_constspStringamp_XMLFilestar_XMLFilestar) , AS_CALL_CDECL);

    RegisterSubclass<Object, MessageBox>(engine, "Object", "MessageBox");
    RegisterSubclass<RefCounted, MessageBox>(engine, "RefCounted", "MessageBox");

    MemberCollection members;
    RegisterMembers_MessageBox<MessageBox>(engine, "MessageBox");
    CollectMembers_MessageBox(members);
    RegisterMembers(engine, "MessageBox", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_MessageBox
        REGISTER_CLASS_MANUAL_PART_MessageBox();
    #endif
}

// explicit NamedPipe::NamedPipe(Context* context)
static NamedPipe* NamedPipe__NamedPipe_Contextstar()
{
    Context* context = GetScriptContext();
    return new NamedPipe(context);
}

// NamedPipe::NamedPipe(Context* context, const String& name, bool isServer)
static NamedPipe* NamedPipe__NamedPipe_Contextstar_constspStringamp_bool(const String& name, bool isServer)
{
    Context* context = GetScriptContext();
    return new NamedPipe(context, name, isServer);
}

// class NamedPipe | File: ../IO/NamedPipe.h
static void Register_NamedPipe(asIScriptEngine* engine)
{
    // explicit NamedPipe::NamedPipe(Context* context)
    engine->RegisterObjectBehaviour("NamedPipe", asBEHAVE_FACTORY, "NamedPipe@+ f()", AS_FUNCTION(NamedPipe__NamedPipe_Contextstar) , AS_CALL_CDECL);
    // NamedPipe::NamedPipe(Context* context, const String& name, bool isServer)
    engine->RegisterObjectBehaviour("NamedPipe", asBEHAVE_FACTORY, "NamedPipe@+ f(const String&in, bool)", AS_FUNCTION(NamedPipe__NamedPipe_Contextstar_constspStringamp_bool) , AS_CALL_CDECL);

    RegisterSubclass<Object, NamedPipe>(engine, "Object", "NamedPipe");
    RegisterSubclass<RefCounted, NamedPipe>(engine, "RefCounted", "NamedPipe");
    RegisterSubclass<Deserializer, NamedPipe>(engine, "Deserializer", "NamedPipe");
    RegisterSubclass<Serializer, NamedPipe>(engine, "Serializer", "NamedPipe");

    MemberCollection members;
    RegisterMembers_NamedPipe<NamedPipe>(engine, "NamedPipe");
    CollectMembers_NamedPipe(members);
    RegisterMembers(engine, "NamedPipe", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_NamedPipe
        REGISTER_CLASS_MANUAL_PART_NamedPipe();
    #endif
}

// explicit OcclusionBuffer::OcclusionBuffer(Context* context)
static OcclusionBuffer* OcclusionBuffer__OcclusionBuffer_Contextstar()
{
    Context* context = GetScriptContext();
    return new OcclusionBuffer(context);
}

// class OcclusionBuffer | File: ../Graphics/OcclusionBuffer.h
static void Register_OcclusionBuffer(asIScriptEngine* engine)
{
    // explicit OcclusionBuffer::OcclusionBuffer(Context* context)
    engine->RegisterObjectBehaviour("OcclusionBuffer", asBEHAVE_FACTORY, "OcclusionBuffer@+ f()", AS_FUNCTION(OcclusionBuffer__OcclusionBuffer_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, OcclusionBuffer>(engine, "Object", "OcclusionBuffer");
    RegisterSubclass<RefCounted, OcclusionBuffer>(engine, "RefCounted", "OcclusionBuffer");

    MemberCollection members;
    RegisterMembers_OcclusionBuffer<OcclusionBuffer>(engine, "OcclusionBuffer");
    CollectMembers_OcclusionBuffer(members);
    RegisterMembers(engine, "OcclusionBuffer", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_OcclusionBuffer
        REGISTER_CLASS_MANUAL_PART_OcclusionBuffer();
    #endif
}

// explicit OggVorbisSoundStream::OggVorbisSoundStream(const Sound* sound)
static OggVorbisSoundStream* OggVorbisSoundStream__OggVorbisSoundStream_constspSoundstar(const Sound* sound)
{
    return new OggVorbisSoundStream(sound);
}

// class OggVorbisSoundStream | File: ../Audio/OggVorbisSoundStream.h
static void Register_OggVorbisSoundStream(asIScriptEngine* engine)
{
    // explicit OggVorbisSoundStream::OggVorbisSoundStream(const Sound* sound)
    engine->RegisterObjectBehaviour("OggVorbisSoundStream", asBEHAVE_FACTORY, "OggVorbisSoundStream@+ f(Sound@+)", AS_FUNCTION(OggVorbisSoundStream__OggVorbisSoundStream_constspSoundstar) , AS_CALL_CDECL);

    RegisterSubclass<SoundStream, OggVorbisSoundStream>(engine, "SoundStream", "OggVorbisSoundStream");
    RegisterSubclass<RefCounted, OggVorbisSoundStream>(engine, "RefCounted", "OggVorbisSoundStream");

    MemberCollection members;
    RegisterMembers_OggVorbisSoundStream<OggVorbisSoundStream>(engine, "OggVorbisSoundStream");
    CollectMembers_OggVorbisSoundStream(members);
    RegisterMembers(engine, "OggVorbisSoundStream", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_OggVorbisSoundStream
        REGISTER_CLASS_MANUAL_PART_OggVorbisSoundStream();
    #endif
}

// explicit PackageFile::PackageFile(Context* context)
static PackageFile* PackageFile__PackageFile_Contextstar()
{
    Context* context = GetScriptContext();
    return new PackageFile(context);
}

// PackageFile::PackageFile(Context* context, const String& fileName, unsigned startOffset = 0)
static PackageFile* PackageFile__PackageFile_Contextstar_constspStringamp_unsigned(const String& fileName, unsigned startOffset)
{
    Context* context = GetScriptContext();
    return new PackageFile(context, fileName, startOffset);
}

// class PackageFile | File: ../IO/PackageFile.h
static void Register_PackageFile(asIScriptEngine* engine)
{
    // explicit PackageFile::PackageFile(Context* context)
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_FACTORY, "PackageFile@+ f()", AS_FUNCTION(PackageFile__PackageFile_Contextstar) , AS_CALL_CDECL);
    // PackageFile::PackageFile(Context* context, const String& fileName, unsigned startOffset = 0)
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_FACTORY, "PackageFile@+ f(const String&in, uint = 0)", AS_FUNCTION(PackageFile__PackageFile_Contextstar_constspStringamp_unsigned) , AS_CALL_CDECL);

    RegisterSubclass<Object, PackageFile>(engine, "Object", "PackageFile");
    RegisterSubclass<RefCounted, PackageFile>(engine, "RefCounted", "PackageFile");

    MemberCollection members;
    RegisterMembers_PackageFile<PackageFile>(engine, "PackageFile");
    CollectMembers_PackageFile(members);
    RegisterMembers(engine, "PackageFile", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_PackageFile
        REGISTER_CLASS_MANUAL_PART_PackageFile();
    #endif
}

// explicit Profiler::Profiler(Context* context)
static Profiler* Profiler__Profiler_Contextstar()
{
    Context* context = GetScriptContext();
    return new Profiler(context);
}

// class Profiler | File: ../Core/Profiler.h
static void Register_Profiler(asIScriptEngine* engine)
{
    // explicit Profiler::Profiler(Context* context)
    engine->RegisterObjectBehaviour("Profiler", asBEHAVE_FACTORY, "Profiler@+ f()", AS_FUNCTION(Profiler__Profiler_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Profiler>(engine, "Object", "Profiler");
    RegisterSubclass<RefCounted, Profiler>(engine, "RefCounted", "Profiler");

    MemberCollection members;
    RegisterMembers_Profiler<Profiler>(engine, "Profiler");
    CollectMembers_Profiler(members);
    RegisterMembers(engine, "Profiler", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Profiler
        REGISTER_CLASS_MANUAL_PART_Profiler();
    #endif
}

// explicit Renderer::Renderer(Context* context)
static Renderer* Renderer__Renderer_Contextstar()
{
    Context* context = GetScriptContext();
    return new Renderer(context);
}

// class Renderer | File: ../Graphics/Renderer.h
static void Register_Renderer(asIScriptEngine* engine)
{
    // explicit Renderer::Renderer(Context* context)
    engine->RegisterObjectBehaviour("Renderer", asBEHAVE_FACTORY, "Renderer@+ f()", AS_FUNCTION(Renderer__Renderer_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Renderer>(engine, "Object", "Renderer");
    RegisterSubclass<RefCounted, Renderer>(engine, "RefCounted", "Renderer");

    MemberCollection members;
    RegisterMembers_Renderer<Renderer>(engine, "Renderer");
    CollectMembers_Renderer(members);
    RegisterMembers(engine, "Renderer", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Renderer
        REGISTER_CLASS_MANUAL_PART_Renderer();
    #endif
}

// explicit Resource::Resource(Context* context)
static Resource* Resource__Resource_Contextstar()
{
    Context* context = GetScriptContext();
    return new Resource(context);
}

// class Resource | File: ../Resource/Resource.h
static void Register_Resource(asIScriptEngine* engine)
{
    // explicit Resource::Resource(Context* context)
    engine->RegisterObjectBehaviour("Resource", asBEHAVE_FACTORY, "Resource@+ f()", AS_FUNCTION(Resource__Resource_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Resource>(engine, "Object", "Resource");
    RegisterSubclass<RefCounted, Resource>(engine, "RefCounted", "Resource");

    MemberCollection members;
    RegisterMembers_Resource<Resource>(engine, "Resource");
    CollectMembers_Resource(members);
    RegisterMembers(engine, "Resource", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Resource
        REGISTER_CLASS_MANUAL_PART_Resource();
    #endif

    // bool Resource::Load(Deserializer& source)
    engine->RegisterObjectMethod("Resource", "bool Load(Deserializer&)", AS_METHODPR(Resource, Load, (Deserializer&), bool), AS_CALL_THISCALL);
}

// explicit ResourceCache::ResourceCache(Context* context)
static ResourceCache* ResourceCache__ResourceCache_Contextstar()
{
    Context* context = GetScriptContext();
    return new ResourceCache(context);
}

// class ResourceCache | File: ../Resource/ResourceCache.h
static void Register_ResourceCache(asIScriptEngine* engine)
{
    // explicit ResourceCache::ResourceCache(Context* context)
    engine->RegisterObjectBehaviour("ResourceCache", asBEHAVE_FACTORY, "ResourceCache@+ f()", AS_FUNCTION(ResourceCache__ResourceCache_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, ResourceCache>(engine, "Object", "ResourceCache");
    RegisterSubclass<RefCounted, ResourceCache>(engine, "RefCounted", "ResourceCache");

    MemberCollection members;
    RegisterMembers_ResourceCache<ResourceCache>(engine, "ResourceCache");
    CollectMembers_ResourceCache(members);
    RegisterMembers(engine, "ResourceCache", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ResourceCache
        REGISTER_CLASS_MANUAL_PART_ResourceCache();
    #endif
}

// explicit Serializable::Serializable(Context* context)
static Serializable* Serializable__Serializable_Contextstar()
{
    Context* context = GetScriptContext();
    return new Serializable(context);
}

// class Serializable | File: ../Scene/Serializable.h
static void Register_Serializable(asIScriptEngine* engine)
{
    // explicit Serializable::Serializable(Context* context)
    engine->RegisterObjectBehaviour("Serializable", asBEHAVE_FACTORY, "Serializable@+ f()", AS_FUNCTION(Serializable__Serializable_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Serializable>(engine, "Object", "Serializable");
    RegisterSubclass<RefCounted, Serializable>(engine, "RefCounted", "Serializable");

    MemberCollection members;
    RegisterMembers_Serializable<Serializable>(engine, "Serializable");
    CollectMembers_Serializable(members);
    RegisterMembers(engine, "Serializable", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Serializable
        REGISTER_CLASS_MANUAL_PART_Serializable();
    #endif

    // virtual bool Serializable::LoadXML(const XMLElement& source)
    engine->RegisterObjectMethod("Serializable", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Serializable, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
}

// ShaderParameterAnimationInfo::ShaderParameterAnimationInfo(Material* material, const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed)
static ShaderParameterAnimationInfo* ShaderParameterAnimationInfo__ShaderParameterAnimationInfo_Materialstar_constspStringamp_ValueAnimationstar_WrapMode_float(Material* material, const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed)
{
    return new ShaderParameterAnimationInfo(material, name, attributeAnimation, wrapMode, speed);
}

// ShaderParameterAnimationInfo::ShaderParameterAnimationInfo(const ShaderParameterAnimationInfo& other)
static ShaderParameterAnimationInfo* ShaderParameterAnimationInfo__ShaderParameterAnimationInfo_constspShaderParameterAnimationInfoamp(const ShaderParameterAnimationInfo& other)
{
    return new ShaderParameterAnimationInfo(other);
}

// class ShaderParameterAnimationInfo | File: ../Graphics/Material.h
static void Register_ShaderParameterAnimationInfo(asIScriptEngine* engine)
{
    // ShaderParameterAnimationInfo::ShaderParameterAnimationInfo(Material* material, const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed)
    engine->RegisterObjectBehaviour("ShaderParameterAnimationInfo", asBEHAVE_FACTORY, "ShaderParameterAnimationInfo@+ f(Material@+, const String&in, ValueAnimation@+, WrapMode, float)", AS_FUNCTION(ShaderParameterAnimationInfo__ShaderParameterAnimationInfo_Materialstar_constspStringamp_ValueAnimationstar_WrapMode_float) , AS_CALL_CDECL);
    // ShaderParameterAnimationInfo::ShaderParameterAnimationInfo(const ShaderParameterAnimationInfo& other)
    engine->RegisterObjectBehaviour("ShaderParameterAnimationInfo", asBEHAVE_FACTORY, "ShaderParameterAnimationInfo@+ f(const ShaderParameterAnimationInfo&in)", AS_FUNCTION(ShaderParameterAnimationInfo__ShaderParameterAnimationInfo_constspShaderParameterAnimationInfoamp) , AS_CALL_CDECL);

    RegisterSubclass<ValueAnimationInfo, ShaderParameterAnimationInfo>(engine, "ValueAnimationInfo", "ShaderParameterAnimationInfo");
    RegisterSubclass<RefCounted, ShaderParameterAnimationInfo>(engine, "RefCounted", "ShaderParameterAnimationInfo");

    MemberCollection members;
    RegisterMembers_ShaderParameterAnimationInfo<ShaderParameterAnimationInfo>(engine, "ShaderParameterAnimationInfo");
    CollectMembers_ShaderParameterAnimationInfo(members);
    RegisterMembers(engine, "ShaderParameterAnimationInfo", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ShaderParameterAnimationInfo
        REGISTER_CLASS_MANUAL_PART_ShaderParameterAnimationInfo();
    #endif
}

// ShaderPrecache::ShaderPrecache(Context* context, const String& fileName)
static ShaderPrecache* ShaderPrecache__ShaderPrecache_Contextstar_constspStringamp(const String& fileName)
{
    Context* context = GetScriptContext();
    return new ShaderPrecache(context, fileName);
}

// class ShaderPrecache | File: ../Graphics/ShaderPrecache.h
static void Register_ShaderPrecache(asIScriptEngine* engine)
{
    // ShaderPrecache::ShaderPrecache(Context* context, const String& fileName)
    engine->RegisterObjectBehaviour("ShaderPrecache", asBEHAVE_FACTORY, "ShaderPrecache@+ f(const String&in)", AS_FUNCTION(ShaderPrecache__ShaderPrecache_Contextstar_constspStringamp) , AS_CALL_CDECL);

    RegisterSubclass<Object, ShaderPrecache>(engine, "Object", "ShaderPrecache");
    RegisterSubclass<RefCounted, ShaderPrecache>(engine, "RefCounted", "ShaderPrecache");

    MemberCollection members;
    RegisterMembers_ShaderPrecache<ShaderPrecache>(engine, "ShaderPrecache");
    CollectMembers_ShaderPrecache(members);
    RegisterMembers(engine, "ShaderPrecache", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ShaderPrecache
        REGISTER_CLASS_MANUAL_PART_ShaderPrecache();
    #endif
}

// explicit Time::Time(Context* context)
static Time* Time__Time_Contextstar()
{
    Context* context = GetScriptContext();
    return new Time(context);
}

// class Time | File: ../Core/Timer.h
static void Register_Time(asIScriptEngine* engine)
{
    // explicit Time::Time(Context* context)
    engine->RegisterObjectBehaviour("Time", asBEHAVE_FACTORY, "Time@+ f()", AS_FUNCTION(Time__Time_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Time>(engine, "Object", "Time");
    RegisterSubclass<RefCounted, Time>(engine, "RefCounted", "Time");

    MemberCollection members;
    RegisterMembers_Time<Time>(engine, "Time");
    CollectMembers_Time(members);
    RegisterMembers(engine, "Time", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Time
        REGISTER_CLASS_MANUAL_PART_Time();
    #endif
}

// explicit UI::UI(Context* context)
static UI* UI__UI_Contextstar()
{
    Context* context = GetScriptContext();
    return new UI(context);
}

// class UI | File: ../UI/UI.h
static void Register_UI(asIScriptEngine* engine)
{
    // explicit UI::UI(Context* context)
    engine->RegisterObjectBehaviour("UI", asBEHAVE_FACTORY, "UI@+ f()", AS_FUNCTION(UI__UI_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, UI>(engine, "Object", "UI");
    RegisterSubclass<RefCounted, UI>(engine, "RefCounted", "UI");

    MemberCollection members;
    RegisterMembers_UI<UI>(engine, "UI");
    CollectMembers_UI(members);
    RegisterMembers(engine, "UI", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_UI
        REGISTER_CLASS_MANUAL_PART_UI();
    #endif
}

// VectorBuffer::VectorBuffer(Deserializer& source, unsigned size)
static void VectorBuffer__VectorBuffer_Deserializeramp_unsigned(VectorBuffer* _ptr, Deserializer& source, unsigned size)
{
    new(_ptr) VectorBuffer(source, size);
}

// class VectorBuffer | File: ../IO/VectorBuffer.h
static void Register_VectorBuffer(asIScriptEngine* engine)
{
    // VectorBuffer::VectorBuffer(const void* data, unsigned size)
    // Error: type "const void*" can not automatically bind
    // explicit VectorBuffer::VectorBuffer(const PODVector<unsigned char>& data)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind

    // VectorBuffer::VectorBuffer(Deserializer& source, unsigned size)
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_CONSTRUCT, "void f(Deserializer&, uint)", AS_FUNCTION_OBJFIRST(VectorBuffer__VectorBuffer_Deserializeramp_unsigned), AS_CALL_CDECL_OBJFIRST);

    // VectorBuffer::~VectorBuffer() | Implicitly-declared
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(VectorBuffer), AS_CALL_CDECL_OBJFIRST);

    MemberCollection members;
    RegisterMembers_VectorBuffer<VectorBuffer>(engine, "VectorBuffer");
    CollectMembers_VectorBuffer(members);
    RegisterMembers(engine, "VectorBuffer", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_VectorBuffer
        REGISTER_CLASS_MANUAL_PART_VectorBuffer();
    #endif

    // VectorBuffer& VectorBuffer::operator =(const VectorBuffer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VectorBuffer>(engine, "VectorBuffer");
}

// explicit VertexBuffer::VertexBuffer(Context* context, bool forceHeadless = false)
static VertexBuffer* VertexBuffer__VertexBuffer_Contextstar_bool(bool forceHeadless)
{
    Context* context = GetScriptContext();
    return new VertexBuffer(context, forceHeadless);
}

// class VertexBuffer | File: ../Graphics/VertexBuffer.h
static void Register_VertexBuffer(asIScriptEngine* engine)
{
    // explicit VertexBuffer::VertexBuffer(Context* context, bool forceHeadless = false)
    engine->RegisterObjectBehaviour("VertexBuffer", asBEHAVE_FACTORY, "VertexBuffer@+ f(bool = false)", AS_FUNCTION(VertexBuffer__VertexBuffer_Contextstar_bool) , AS_CALL_CDECL);

    RegisterSubclass<Object, VertexBuffer>(engine, "Object", "VertexBuffer");
    RegisterSubclass<RefCounted, VertexBuffer>(engine, "RefCounted", "VertexBuffer");

    MemberCollection members;
    RegisterMembers_VertexBuffer<VertexBuffer>(engine, "VertexBuffer");
    CollectMembers_VertexBuffer(members);
    RegisterMembers(engine, "VertexBuffer", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_VertexBuffer
        REGISTER_CLASS_MANUAL_PART_VertexBuffer();
    #endif
}

// explicit View::View(Context* context)
static View* View__View_Contextstar()
{
    Context* context = GetScriptContext();
    return new View(context);
}

// class View | File: ../Graphics/View.h
static void Register_View(asIScriptEngine* engine)
{
    // explicit View::View(Context* context)
    engine->RegisterObjectBehaviour("View", asBEHAVE_FACTORY, "View@+ f()", AS_FUNCTION(View__View_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, View>(engine, "Object", "View");
    RegisterSubclass<RefCounted, View>(engine, "RefCounted", "View");

    MemberCollection members;
    RegisterMembers_View<View>(engine, "View");
    CollectMembers_View(members);
    RegisterMembers(engine, "View", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_View
        REGISTER_CLASS_MANUAL_PART_View();
    #endif
}

// explicit Viewport::Viewport(Context* context)
static Viewport* Viewport__Viewport_Contextstar()
{
    Context* context = GetScriptContext();
    return new Viewport(context);
}

// Viewport::Viewport(Context* context, Scene* scene, Camera* camera, RenderPath* renderPath = nullptr)
static Viewport* Viewport__Viewport_Contextstar_Scenestar_Camerastar_RenderPathstar(Scene* scene, Camera* camera, RenderPath* renderPath)
{
    Context* context = GetScriptContext();
    return new Viewport(context, scene, camera, renderPath);
}

// Viewport::Viewport(Context* context, Scene* scene, Camera* camera, const IntRect& rect, RenderPath* renderPath = nullptr)
static Viewport* Viewport__Viewport_Contextstar_Scenestar_Camerastar_constspIntRectamp_RenderPathstar(Scene* scene, Camera* camera, const IntRect& rect, RenderPath* renderPath)
{
    Context* context = GetScriptContext();
    return new Viewport(context, scene, camera, rect, renderPath);
}

// class Viewport | File: ../Graphics/Viewport.h
static void Register_Viewport(asIScriptEngine* engine)
{
    // explicit Viewport::Viewport(Context* context)
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_FACTORY, "Viewport@+ f()", AS_FUNCTION(Viewport__Viewport_Contextstar) , AS_CALL_CDECL);
    // Viewport::Viewport(Context* context, Scene* scene, Camera* camera, RenderPath* renderPath = nullptr)
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_FACTORY, "Viewport@+ f(Scene@+, Camera@+, RenderPath@+ = null)", AS_FUNCTION(Viewport__Viewport_Contextstar_Scenestar_Camerastar_RenderPathstar) , AS_CALL_CDECL);
    // Viewport::Viewport(Context* context, Scene* scene, Camera* camera, const IntRect& rect, RenderPath* renderPath = nullptr)
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_FACTORY, "Viewport@+ f(Scene@+, Camera@+, const IntRect&in, RenderPath@+ = null)", AS_FUNCTION(Viewport__Viewport_Contextstar_Scenestar_Camerastar_constspIntRectamp_RenderPathstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Viewport>(engine, "Object", "Viewport");
    RegisterSubclass<RefCounted, Viewport>(engine, "RefCounted", "Viewport");

    MemberCollection members;
    RegisterMembers_Viewport<Viewport>(engine, "Viewport");
    CollectMembers_Viewport(members);
    RegisterMembers(engine, "Viewport", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Viewport
        REGISTER_CLASS_MANUAL_PART_Viewport();
    #endif
}

// explicit WorkQueue::WorkQueue(Context* context)
static WorkQueue* WorkQueue__WorkQueue_Contextstar()
{
    Context* context = GetScriptContext();
    return new WorkQueue(context);
}

// class WorkQueue | File: ../Core/WorkQueue.h
static void Register_WorkQueue(asIScriptEngine* engine)
{
    // explicit WorkQueue::WorkQueue(Context* context)
    engine->RegisterObjectBehaviour("WorkQueue", asBEHAVE_FACTORY, "WorkQueue@+ f()", AS_FUNCTION(WorkQueue__WorkQueue_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, WorkQueue>(engine, "Object", "WorkQueue");
    RegisterSubclass<RefCounted, WorkQueue>(engine, "RefCounted", "WorkQueue");

    MemberCollection members;
    RegisterMembers_WorkQueue<WorkQueue>(engine, "WorkQueue");
    CollectMembers_WorkQueue(members);
    RegisterMembers(engine, "WorkQueue", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_WorkQueue
        REGISTER_CLASS_MANUAL_PART_WorkQueue();
    #endif
}

#ifdef URHO3D_DATABASE

// explicit Database::Database(Context* context)
static Database* Database__Database_Contextstar()
{
    Context* context = GetScriptContext();
    return new Database(context);
}

// class Database | File: ../Database/Database.h
static void Register_Database(asIScriptEngine* engine)
{
    // explicit Database::Database(Context* context)
    engine->RegisterObjectBehaviour("Database", asBEHAVE_FACTORY, "Database@+ f()", AS_FUNCTION(Database__Database_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Database>(engine, "Object", "Database");
    RegisterSubclass<RefCounted, Database>(engine, "RefCounted", "Database");

    MemberCollection members;
    RegisterMembers_Database<Database>(engine, "Database");
    CollectMembers_Database(members);
    RegisterMembers(engine, "Database", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Database
        REGISTER_CLASS_MANUAL_PART_Database();
    #endif
}

#endif // def URHO3D_DATABASE

#ifdef URHO3D_NETWORK

// class Connection | File: ../Network/Connection.h
static void Register_Connection(asIScriptEngine* engine)
{
    // Connection::Connection(Context* context, bool isClient, const SLNet::AddressOrGUID& address, SLNet::RakPeerInterface* peer)
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind

    RegisterSubclass<Object, Connection>(engine, "Object", "Connection");
    RegisterSubclass<RefCounted, Connection>(engine, "RefCounted", "Connection");

    MemberCollection members;
    RegisterMembers_Connection<Connection>(engine, "Connection");
    CollectMembers_Connection(members);
    RegisterMembers(engine, "Connection", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Connection
        REGISTER_CLASS_MANUAL_PART_Connection();
    #endif
}

// explicit Network::Network(Context* context)
static Network* Network__Network_Contextstar()
{
    Context* context = GetScriptContext();
    return new Network(context);
}

// class Network | File: ../Network/Network.h
static void Register_Network(asIScriptEngine* engine)
{
    // explicit Network::Network(Context* context)
    engine->RegisterObjectBehaviour("Network", asBEHAVE_FACTORY, "Network@+ f()", AS_FUNCTION(Network__Network_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Object, Network>(engine, "Object", "Network");
    RegisterSubclass<RefCounted, Network>(engine, "RefCounted", "Network");

    MemberCollection members;
    RegisterMembers_Network<Network>(engine, "Network");
    CollectMembers_Network(members);
    RegisterMembers(engine, "Network", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Network
        REGISTER_CLASS_MANUAL_PART_Network();
    #endif
}

#endif // def URHO3D_NETWORK

#ifdef URHO3D_PHYSICS

// ConvexData::ConvexData(Model* model, unsigned lodLevel)
static ConvexData* ConvexData__ConvexData_Modelstar_unsigned(Model* model, unsigned lodLevel)
{
    return new ConvexData(model, lodLevel);
}

// explicit ConvexData::ConvexData(CustomGeometry* custom)
static ConvexData* ConvexData__ConvexData_CustomGeometrystar(CustomGeometry* custom)
{
    return new ConvexData(custom);
}

// struct ConvexData | File: ../Physics/CollisionShape.h
static void Register_ConvexData(asIScriptEngine* engine)
{
    // ConvexData::ConvexData(Model* model, unsigned lodLevel)
    engine->RegisterObjectBehaviour("ConvexData", asBEHAVE_FACTORY, "ConvexData@+ f(Model@+, uint)", AS_FUNCTION(ConvexData__ConvexData_Modelstar_unsigned) , AS_CALL_CDECL);
    // explicit ConvexData::ConvexData(CustomGeometry* custom)
    engine->RegisterObjectBehaviour("ConvexData", asBEHAVE_FACTORY, "ConvexData@+ f(CustomGeometry@+)", AS_FUNCTION(ConvexData__ConvexData_CustomGeometrystar) , AS_CALL_CDECL);

    RegisterSubclass<CollisionGeometryData, ConvexData>(engine, "CollisionGeometryData", "ConvexData");
    RegisterSubclass<RefCounted, ConvexData>(engine, "RefCounted", "ConvexData");

    MemberCollection members;
    RegisterMembers_ConvexData<ConvexData>(engine, "ConvexData");
    CollectMembers_ConvexData(members);
    RegisterMembers(engine, "ConvexData", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ConvexData
        REGISTER_CLASS_MANUAL_PART_ConvexData();
    #endif
}

// GImpactMeshData::GImpactMeshData(Model* model, unsigned lodLevel)
static GImpactMeshData* GImpactMeshData__GImpactMeshData_Modelstar_unsigned(Model* model, unsigned lodLevel)
{
    return new GImpactMeshData(model, lodLevel);
}

// explicit GImpactMeshData::GImpactMeshData(CustomGeometry* custom)
static GImpactMeshData* GImpactMeshData__GImpactMeshData_CustomGeometrystar(CustomGeometry* custom)
{
    return new GImpactMeshData(custom);
}

// struct GImpactMeshData | File: ../Physics/CollisionShape.h
static void Register_GImpactMeshData(asIScriptEngine* engine)
{
    // GImpactMeshData::GImpactMeshData(Model* model, unsigned lodLevel)
    engine->RegisterObjectBehaviour("GImpactMeshData", asBEHAVE_FACTORY, "GImpactMeshData@+ f(Model@+, uint)", AS_FUNCTION(GImpactMeshData__GImpactMeshData_Modelstar_unsigned) , AS_CALL_CDECL);
    // explicit GImpactMeshData::GImpactMeshData(CustomGeometry* custom)
    engine->RegisterObjectBehaviour("GImpactMeshData", asBEHAVE_FACTORY, "GImpactMeshData@+ f(CustomGeometry@+)", AS_FUNCTION(GImpactMeshData__GImpactMeshData_CustomGeometrystar) , AS_CALL_CDECL);

    RegisterSubclass<CollisionGeometryData, GImpactMeshData>(engine, "CollisionGeometryData", "GImpactMeshData");
    RegisterSubclass<RefCounted, GImpactMeshData>(engine, "RefCounted", "GImpactMeshData");

    MemberCollection members;
    RegisterMembers_GImpactMeshData<GImpactMeshData>(engine, "GImpactMeshData");
    CollectMembers_GImpactMeshData(members);
    RegisterMembers(engine, "GImpactMeshData", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_GImpactMeshData
        REGISTER_CLASS_MANUAL_PART_GImpactMeshData();
    #endif
}

// HeightfieldData::HeightfieldData(Terrain* terrain, unsigned lodLevel)
static HeightfieldData* HeightfieldData__HeightfieldData_Terrainstar_unsigned(Terrain* terrain, unsigned lodLevel)
{
    return new HeightfieldData(terrain, lodLevel);
}

// struct HeightfieldData | File: ../Physics/CollisionShape.h
static void Register_HeightfieldData(asIScriptEngine* engine)
{
    // HeightfieldData::HeightfieldData(Terrain* terrain, unsigned lodLevel)
    engine->RegisterObjectBehaviour("HeightfieldData", asBEHAVE_FACTORY, "HeightfieldData@+ f(Terrain@+, uint)", AS_FUNCTION(HeightfieldData__HeightfieldData_Terrainstar_unsigned) , AS_CALL_CDECL);

    RegisterSubclass<CollisionGeometryData, HeightfieldData>(engine, "CollisionGeometryData", "HeightfieldData");
    RegisterSubclass<RefCounted, HeightfieldData>(engine, "RefCounted", "HeightfieldData");

    MemberCollection members;
    RegisterMembers_HeightfieldData<HeightfieldData>(engine, "HeightfieldData");
    CollectMembers_HeightfieldData(members);
    RegisterMembers(engine, "HeightfieldData", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_HeightfieldData
        REGISTER_CLASS_MANUAL_PART_HeightfieldData();
    #endif
}

// TriangleMeshData::TriangleMeshData(Model* model, unsigned lodLevel)
static TriangleMeshData* TriangleMeshData__TriangleMeshData_Modelstar_unsigned(Model* model, unsigned lodLevel)
{
    return new TriangleMeshData(model, lodLevel);
}

// explicit TriangleMeshData::TriangleMeshData(CustomGeometry* custom)
static TriangleMeshData* TriangleMeshData__TriangleMeshData_CustomGeometrystar(CustomGeometry* custom)
{
    return new TriangleMeshData(custom);
}

// struct TriangleMeshData | File: ../Physics/CollisionShape.h
static void Register_TriangleMeshData(asIScriptEngine* engine)
{
    // TriangleMeshData::TriangleMeshData(Model* model, unsigned lodLevel)
    engine->RegisterObjectBehaviour("TriangleMeshData", asBEHAVE_FACTORY, "TriangleMeshData@+ f(Model@+, uint)", AS_FUNCTION(TriangleMeshData__TriangleMeshData_Modelstar_unsigned) , AS_CALL_CDECL);
    // explicit TriangleMeshData::TriangleMeshData(CustomGeometry* custom)
    engine->RegisterObjectBehaviour("TriangleMeshData", asBEHAVE_FACTORY, "TriangleMeshData@+ f(CustomGeometry@+)", AS_FUNCTION(TriangleMeshData__TriangleMeshData_CustomGeometrystar) , AS_CALL_CDECL);

    RegisterSubclass<CollisionGeometryData, TriangleMeshData>(engine, "CollisionGeometryData", "TriangleMeshData");
    RegisterSubclass<RefCounted, TriangleMeshData>(engine, "RefCounted", "TriangleMeshData");

    MemberCollection members;
    RegisterMembers_TriangleMeshData<TriangleMeshData>(engine, "TriangleMeshData");
    CollectMembers_TriangleMeshData(members);
    RegisterMembers(engine, "TriangleMeshData", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TriangleMeshData
        REGISTER_CLASS_MANUAL_PART_TriangleMeshData();
    #endif
}

#endif // def URHO3D_PHYSICS

#ifdef URHO3D_URHO2D

// explicit TmxImageLayer2D::TmxImageLayer2D(TmxFile2D* tmxFile)
static TmxImageLayer2D* TmxImageLayer2D__TmxImageLayer2D_TmxFile2Dstar(TmxFile2D* tmxFile)
{
    return new TmxImageLayer2D(tmxFile);
}

// class TmxImageLayer2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxImageLayer2D(asIScriptEngine* engine)
{
    // explicit TmxImageLayer2D::TmxImageLayer2D(TmxFile2D* tmxFile)
    engine->RegisterObjectBehaviour("TmxImageLayer2D", asBEHAVE_FACTORY, "TmxImageLayer2D@+ f(TmxFile2D@+)", AS_FUNCTION(TmxImageLayer2D__TmxImageLayer2D_TmxFile2Dstar) , AS_CALL_CDECL);

    RegisterSubclass<TmxLayer2D, TmxImageLayer2D>(engine, "TmxLayer2D", "TmxImageLayer2D");
    RegisterSubclass<RefCounted, TmxImageLayer2D>(engine, "RefCounted", "TmxImageLayer2D");

    MemberCollection members;
    RegisterMembers_TmxImageLayer2D<TmxImageLayer2D>(engine, "TmxImageLayer2D");
    CollectMembers_TmxImageLayer2D(members);
    RegisterMembers(engine, "TmxImageLayer2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TmxImageLayer2D
        REGISTER_CLASS_MANUAL_PART_TmxImageLayer2D();
    #endif
}

// explicit TmxObjectGroup2D::TmxObjectGroup2D(TmxFile2D* tmxFile)
static TmxObjectGroup2D* TmxObjectGroup2D__TmxObjectGroup2D_TmxFile2Dstar(TmxFile2D* tmxFile)
{
    return new TmxObjectGroup2D(tmxFile);
}

// class TmxObjectGroup2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxObjectGroup2D(asIScriptEngine* engine)
{
    // explicit TmxObjectGroup2D::TmxObjectGroup2D(TmxFile2D* tmxFile)
    engine->RegisterObjectBehaviour("TmxObjectGroup2D", asBEHAVE_FACTORY, "TmxObjectGroup2D@+ f(TmxFile2D@+)", AS_FUNCTION(TmxObjectGroup2D__TmxObjectGroup2D_TmxFile2Dstar) , AS_CALL_CDECL);

    RegisterSubclass<TmxLayer2D, TmxObjectGroup2D>(engine, "TmxLayer2D", "TmxObjectGroup2D");
    RegisterSubclass<RefCounted, TmxObjectGroup2D>(engine, "RefCounted", "TmxObjectGroup2D");

    MemberCollection members;
    RegisterMembers_TmxObjectGroup2D<TmxObjectGroup2D>(engine, "TmxObjectGroup2D");
    CollectMembers_TmxObjectGroup2D(members);
    RegisterMembers(engine, "TmxObjectGroup2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TmxObjectGroup2D
        REGISTER_CLASS_MANUAL_PART_TmxObjectGroup2D();
    #endif
}

// explicit TmxTileLayer2D::TmxTileLayer2D(TmxFile2D* tmxFile)
static TmxTileLayer2D* TmxTileLayer2D__TmxTileLayer2D_TmxFile2Dstar(TmxFile2D* tmxFile)
{
    return new TmxTileLayer2D(tmxFile);
}

// class TmxTileLayer2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxTileLayer2D(asIScriptEngine* engine)
{
    // explicit TmxTileLayer2D::TmxTileLayer2D(TmxFile2D* tmxFile)
    engine->RegisterObjectBehaviour("TmxTileLayer2D", asBEHAVE_FACTORY, "TmxTileLayer2D@+ f(TmxFile2D@+)", AS_FUNCTION(TmxTileLayer2D__TmxTileLayer2D_TmxFile2Dstar) , AS_CALL_CDECL);

    RegisterSubclass<TmxLayer2D, TmxTileLayer2D>(engine, "TmxLayer2D", "TmxTileLayer2D");
    RegisterSubclass<RefCounted, TmxTileLayer2D>(engine, "RefCounted", "TmxTileLayer2D");

    MemberCollection members;
    RegisterMembers_TmxTileLayer2D<TmxTileLayer2D>(engine, "TmxTileLayer2D");
    CollectMembers_TmxTileLayer2D(members);
    RegisterMembers(engine, "TmxTileLayer2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TmxTileLayer2D
        REGISTER_CLASS_MANUAL_PART_TmxTileLayer2D();
    #endif
}

#endif // def URHO3D_URHO2D

// class Animatable | File: ../Scene/Animatable.h
static void Register_Animatable(asIScriptEngine* engine)
{
    RegisterSubclass<Serializable, Animatable>(engine, "Serializable", "Animatable");
    RegisterSubclass<Object, Animatable>(engine, "Object", "Animatable");
    RegisterSubclass<RefCounted, Animatable>(engine, "RefCounted", "Animatable");

    MemberCollection members;
    RegisterMembers_Animatable<Animatable>(engine, "Animatable");
    CollectMembers_Animatable(members);
    RegisterMembers(engine, "Animatable", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Animatable
        REGISTER_CLASS_MANUAL_PART_Animatable();
    #endif

    // bool Animatable::LoadXML(const XMLElement& source) override
    engine->RegisterObjectMethod("Animatable", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Animatable, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
}

// explicit EventProfiler::EventProfiler(Context* context)
static EventProfiler* EventProfiler__EventProfiler_Contextstar()
{
    Context* context = GetScriptContext();
    return new EventProfiler(context);
}

// class EventProfiler | File: ../Core/EventProfiler.h
static void Register_EventProfiler(asIScriptEngine* engine)
{
    // explicit EventProfiler::EventProfiler(Context* context)
    engine->RegisterObjectBehaviour("EventProfiler", asBEHAVE_FACTORY, "EventProfiler@+ f()", AS_FUNCTION(EventProfiler__EventProfiler_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Profiler, EventProfiler>(engine, "Profiler", "EventProfiler");
    RegisterSubclass<Object, EventProfiler>(engine, "Object", "EventProfiler");
    RegisterSubclass<RefCounted, EventProfiler>(engine, "RefCounted", "EventProfiler");

    MemberCollection members;
    RegisterMembers_EventProfiler<EventProfiler>(engine, "EventProfiler");
    CollectMembers_EventProfiler(members);
    RegisterMembers(engine, "EventProfiler", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_EventProfiler
        REGISTER_CLASS_MANUAL_PART_EventProfiler();
    #endif
}

// explicit Font::Font(Context* context)
static Font* Font__Font_Contextstar()
{
    Context* context = GetScriptContext();
    return new Font(context);
}

// class Font | File: ../UI/Font.h
static void Register_Font(asIScriptEngine* engine)
{
    // explicit Font::Font(Context* context)
    engine->RegisterObjectBehaviour("Font", asBEHAVE_FACTORY, "Font@+ f()", AS_FUNCTION(Font__Font_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, Font>(engine, "Resource", "Font");
    RegisterSubclass<Object, Font>(engine, "Object", "Font");
    RegisterSubclass<RefCounted, Font>(engine, "RefCounted", "Font");

    MemberCollection members;
    RegisterMembers_Font<Font>(engine, "Font");
    CollectMembers_Font(members);
    RegisterMembers(engine, "Font", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Font
        REGISTER_CLASS_MANUAL_PART_Font();
    #endif
}

// explicit Image::Image(Context* context)
static Image* Image__Image_Contextstar()
{
    Context* context = GetScriptContext();
    return new Image(context);
}

// class Image | File: ../Resource/Image.h
static void Register_Image(asIScriptEngine* engine)
{
    // explicit Image::Image(Context* context)
    engine->RegisterObjectBehaviour("Image", asBEHAVE_FACTORY, "Image@+ f()", AS_FUNCTION(Image__Image_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, Image>(engine, "Resource", "Image");
    RegisterSubclass<Object, Image>(engine, "Object", "Image");
    RegisterSubclass<RefCounted, Image>(engine, "RefCounted", "Image");

    MemberCollection members;
    RegisterMembers_Image<Image>(engine, "Image");
    CollectMembers_Image(members);
    RegisterMembers(engine, "Image", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Image
        REGISTER_CLASS_MANUAL_PART_Image();
    #endif
}

// explicit JSONFile::JSONFile(Context* context)
static JSONFile* JSONFile__JSONFile_Contextstar()
{
    Context* context = GetScriptContext();
    return new JSONFile(context);
}

// class JSONFile | File: ../Resource/JSONFile.h
static void Register_JSONFile(asIScriptEngine* engine)
{
    // explicit JSONFile::JSONFile(Context* context)
    engine->RegisterObjectBehaviour("JSONFile", asBEHAVE_FACTORY, "JSONFile@+ f()", AS_FUNCTION(JSONFile__JSONFile_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, JSONFile>(engine, "Resource", "JSONFile");
    RegisterSubclass<Object, JSONFile>(engine, "Object", "JSONFile");
    RegisterSubclass<RefCounted, JSONFile>(engine, "RefCounted", "JSONFile");

    MemberCollection members;
    RegisterMembers_JSONFile<JSONFile>(engine, "JSONFile");
    CollectMembers_JSONFile(members);
    RegisterMembers(engine, "JSONFile", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_JSONFile
        REGISTER_CLASS_MANUAL_PART_JSONFile();
    #endif
}

// explicit Material::Material(Context* context)
static Material* Material__Material_Contextstar()
{
    Context* context = GetScriptContext();
    return new Material(context);
}

// class Material | File: ../Graphics/Material.h
static void Register_Material(asIScriptEngine* engine)
{
    // explicit Material::Material(Context* context)
    engine->RegisterObjectBehaviour("Material", asBEHAVE_FACTORY, "Material@+ f()", AS_FUNCTION(Material__Material_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, Material>(engine, "Resource", "Material");
    RegisterSubclass<Object, Material>(engine, "Object", "Material");
    RegisterSubclass<RefCounted, Material>(engine, "RefCounted", "Material");

    MemberCollection members;
    RegisterMembers_Material<Material>(engine, "Material");
    CollectMembers_Material(members);
    RegisterMembers(engine, "Material", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Material
        REGISTER_CLASS_MANUAL_PART_Material();
    #endif
}

// explicit ObjectAnimation::ObjectAnimation(Context* context)
static ObjectAnimation* ObjectAnimation__ObjectAnimation_Contextstar()
{
    Context* context = GetScriptContext();
    return new ObjectAnimation(context);
}

// class ObjectAnimation | File: ../Scene/ObjectAnimation.h
static void Register_ObjectAnimation(asIScriptEngine* engine)
{
    // explicit ObjectAnimation::ObjectAnimation(Context* context)
    engine->RegisterObjectBehaviour("ObjectAnimation", asBEHAVE_FACTORY, "ObjectAnimation@+ f()", AS_FUNCTION(ObjectAnimation__ObjectAnimation_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, ObjectAnimation>(engine, "Resource", "ObjectAnimation");
    RegisterSubclass<Object, ObjectAnimation>(engine, "Object", "ObjectAnimation");
    RegisterSubclass<RefCounted, ObjectAnimation>(engine, "RefCounted", "ObjectAnimation");

    MemberCollection members;
    RegisterMembers_ObjectAnimation<ObjectAnimation>(engine, "ObjectAnimation");
    CollectMembers_ObjectAnimation(members);
    RegisterMembers(engine, "ObjectAnimation", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ObjectAnimation
        REGISTER_CLASS_MANUAL_PART_ObjectAnimation();
    #endif
}

// explicit ParticleEffect::ParticleEffect(Context* context)
static ParticleEffect* ParticleEffect__ParticleEffect_Contextstar()
{
    Context* context = GetScriptContext();
    return new ParticleEffect(context);
}

// class ParticleEffect | File: ../Graphics/ParticleEffect.h
static void Register_ParticleEffect(asIScriptEngine* engine)
{
    // explicit ParticleEffect::ParticleEffect(Context* context)
    engine->RegisterObjectBehaviour("ParticleEffect", asBEHAVE_FACTORY, "ParticleEffect@+ f()", AS_FUNCTION(ParticleEffect__ParticleEffect_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, ParticleEffect>(engine, "Resource", "ParticleEffect");
    RegisterSubclass<Object, ParticleEffect>(engine, "Object", "ParticleEffect");
    RegisterSubclass<RefCounted, ParticleEffect>(engine, "RefCounted", "ParticleEffect");

    MemberCollection members;
    RegisterMembers_ParticleEffect<ParticleEffect>(engine, "ParticleEffect");
    CollectMembers_ParticleEffect(members);
    RegisterMembers(engine, "ParticleEffect", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ParticleEffect
        REGISTER_CLASS_MANUAL_PART_ParticleEffect();
    #endif
}

// explicit ResourceWithMetadata::ResourceWithMetadata(Context* context)
static ResourceWithMetadata* ResourceWithMetadata__ResourceWithMetadata_Contextstar()
{
    Context* context = GetScriptContext();
    return new ResourceWithMetadata(context);
}

// class ResourceWithMetadata | File: ../Resource/Resource.h
static void Register_ResourceWithMetadata(asIScriptEngine* engine)
{
    // explicit ResourceWithMetadata::ResourceWithMetadata(Context* context)
    engine->RegisterObjectBehaviour("ResourceWithMetadata", asBEHAVE_FACTORY, "ResourceWithMetadata@+ f()", AS_FUNCTION(ResourceWithMetadata__ResourceWithMetadata_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, ResourceWithMetadata>(engine, "Resource", "ResourceWithMetadata");
    RegisterSubclass<Object, ResourceWithMetadata>(engine, "Object", "ResourceWithMetadata");
    RegisterSubclass<RefCounted, ResourceWithMetadata>(engine, "RefCounted", "ResourceWithMetadata");

    MemberCollection members;
    RegisterMembers_ResourceWithMetadata<ResourceWithMetadata>(engine, "ResourceWithMetadata");
    CollectMembers_ResourceWithMetadata(members);
    RegisterMembers(engine, "ResourceWithMetadata", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ResourceWithMetadata
        REGISTER_CLASS_MANUAL_PART_ResourceWithMetadata();
    #endif
}

// explicit Shader::Shader(Context* context)
static Shader* Shader__Shader_Contextstar()
{
    Context* context = GetScriptContext();
    return new Shader(context);
}

// class Shader | File: ../Graphics/Shader.h
static void Register_Shader(asIScriptEngine* engine)
{
    // explicit Shader::Shader(Context* context)
    engine->RegisterObjectBehaviour("Shader", asBEHAVE_FACTORY, "Shader@+ f()", AS_FUNCTION(Shader__Shader_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, Shader>(engine, "Resource", "Shader");
    RegisterSubclass<Object, Shader>(engine, "Object", "Shader");
    RegisterSubclass<RefCounted, Shader>(engine, "RefCounted", "Shader");

    MemberCollection members;
    RegisterMembers_Shader<Shader>(engine, "Shader");
    CollectMembers_Shader(members);
    RegisterMembers(engine, "Shader", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Shader
        REGISTER_CLASS_MANUAL_PART_Shader();
    #endif
}

// explicit Technique::Technique(Context* context)
static Technique* Technique__Technique_Contextstar()
{
    Context* context = GetScriptContext();
    return new Technique(context);
}

// class Technique | File: ../Graphics/Technique.h
static void Register_Technique(asIScriptEngine* engine)
{
    // explicit Technique::Technique(Context* context)
    engine->RegisterObjectBehaviour("Technique", asBEHAVE_FACTORY, "Technique@+ f()", AS_FUNCTION(Technique__Technique_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, Technique>(engine, "Resource", "Technique");
    RegisterSubclass<Object, Technique>(engine, "Object", "Technique");
    RegisterSubclass<RefCounted, Technique>(engine, "RefCounted", "Technique");

    MemberCollection members;
    RegisterMembers_Technique<Technique>(engine, "Technique");
    CollectMembers_Technique(members);
    RegisterMembers(engine, "Technique", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Technique
        REGISTER_CLASS_MANUAL_PART_Technique();
    #endif
}

// explicit ValueAnimation::ValueAnimation(Context* context)
static ValueAnimation* ValueAnimation__ValueAnimation_Contextstar()
{
    Context* context = GetScriptContext();
    return new ValueAnimation(context);
}

// class ValueAnimation | File: ../Scene/ValueAnimation.h
static void Register_ValueAnimation(asIScriptEngine* engine)
{
    // explicit ValueAnimation::ValueAnimation(Context* context)
    engine->RegisterObjectBehaviour("ValueAnimation", asBEHAVE_FACTORY, "ValueAnimation@+ f()", AS_FUNCTION(ValueAnimation__ValueAnimation_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, ValueAnimation>(engine, "Resource", "ValueAnimation");
    RegisterSubclass<Object, ValueAnimation>(engine, "Object", "ValueAnimation");
    RegisterSubclass<RefCounted, ValueAnimation>(engine, "RefCounted", "ValueAnimation");

    MemberCollection members;
    RegisterMembers_ValueAnimation<ValueAnimation>(engine, "ValueAnimation");
    CollectMembers_ValueAnimation(members);
    RegisterMembers(engine, "ValueAnimation", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ValueAnimation
        REGISTER_CLASS_MANUAL_PART_ValueAnimation();
    #endif
}

// explicit XMLFile::XMLFile(Context* context)
static XMLFile* XMLFile__XMLFile_Contextstar()
{
    Context* context = GetScriptContext();
    return new XMLFile(context);
}

// class XMLFile | File: ../Resource/XMLFile.h
static void Register_XMLFile(asIScriptEngine* engine)
{
    // explicit XMLFile::XMLFile(Context* context)
    engine->RegisterObjectBehaviour("XMLFile", asBEHAVE_FACTORY, "XMLFile@+ f()", AS_FUNCTION(XMLFile__XMLFile_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, XMLFile>(engine, "Resource", "XMLFile");
    RegisterSubclass<Object, XMLFile>(engine, "Object", "XMLFile");
    RegisterSubclass<RefCounted, XMLFile>(engine, "RefCounted", "XMLFile");

    MemberCollection members;
    RegisterMembers_XMLFile<XMLFile>(engine, "XMLFile");
    CollectMembers_XMLFile(members);
    RegisterMembers(engine, "XMLFile", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_XMLFile
        REGISTER_CLASS_MANUAL_PART_XMLFile();
    #endif
}

#ifdef URHO3D_URHO2D

// explicit AnimationSet2D::AnimationSet2D(Context* context)
static AnimationSet2D* AnimationSet2D__AnimationSet2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new AnimationSet2D(context);
}

// class AnimationSet2D | File: ../Urho2D/AnimationSet2D.h
static void Register_AnimationSet2D(asIScriptEngine* engine)
{
    // explicit AnimationSet2D::AnimationSet2D(Context* context)
    engine->RegisterObjectBehaviour("AnimationSet2D", asBEHAVE_FACTORY, "AnimationSet2D@+ f()", AS_FUNCTION(AnimationSet2D__AnimationSet2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, AnimationSet2D>(engine, "Resource", "AnimationSet2D");
    RegisterSubclass<Object, AnimationSet2D>(engine, "Object", "AnimationSet2D");
    RegisterSubclass<RefCounted, AnimationSet2D>(engine, "RefCounted", "AnimationSet2D");

    MemberCollection members;
    RegisterMembers_AnimationSet2D<AnimationSet2D>(engine, "AnimationSet2D");
    CollectMembers_AnimationSet2D(members);
    RegisterMembers(engine, "AnimationSet2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AnimationSet2D
        REGISTER_CLASS_MANUAL_PART_AnimationSet2D();
    #endif
}

// explicit ParticleEffect2D::ParticleEffect2D(Context* context)
static ParticleEffect2D* ParticleEffect2D__ParticleEffect2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new ParticleEffect2D(context);
}

// class ParticleEffect2D | File: ../Urho2D/ParticleEffect2D.h
static void Register_ParticleEffect2D(asIScriptEngine* engine)
{
    // explicit ParticleEffect2D::ParticleEffect2D(Context* context)
    engine->RegisterObjectBehaviour("ParticleEffect2D", asBEHAVE_FACTORY, "ParticleEffect2D@+ f()", AS_FUNCTION(ParticleEffect2D__ParticleEffect2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, ParticleEffect2D>(engine, "Resource", "ParticleEffect2D");
    RegisterSubclass<Object, ParticleEffect2D>(engine, "Object", "ParticleEffect2D");
    RegisterSubclass<RefCounted, ParticleEffect2D>(engine, "RefCounted", "ParticleEffect2D");

    MemberCollection members;
    RegisterMembers_ParticleEffect2D<ParticleEffect2D>(engine, "ParticleEffect2D");
    CollectMembers_ParticleEffect2D(members);
    RegisterMembers(engine, "ParticleEffect2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ParticleEffect2D
        REGISTER_CLASS_MANUAL_PART_ParticleEffect2D();
    #endif
}

// explicit Sprite2D::Sprite2D(Context* context)
static Sprite2D* Sprite2D__Sprite2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new Sprite2D(context);
}

// class Sprite2D | File: ../Urho2D/Sprite2D.h
static void Register_Sprite2D(asIScriptEngine* engine)
{
    // explicit Sprite2D::Sprite2D(Context* context)
    engine->RegisterObjectBehaviour("Sprite2D", asBEHAVE_FACTORY, "Sprite2D@+ f()", AS_FUNCTION(Sprite2D__Sprite2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, Sprite2D>(engine, "Resource", "Sprite2D");
    RegisterSubclass<Object, Sprite2D>(engine, "Object", "Sprite2D");
    RegisterSubclass<RefCounted, Sprite2D>(engine, "RefCounted", "Sprite2D");

    MemberCollection members;
    RegisterMembers_Sprite2D<Sprite2D>(engine, "Sprite2D");
    CollectMembers_Sprite2D(members);
    RegisterMembers(engine, "Sprite2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Sprite2D
        REGISTER_CLASS_MANUAL_PART_Sprite2D();
    #endif
}

// explicit SpriteSheet2D::SpriteSheet2D(Context* context)
static SpriteSheet2D* SpriteSheet2D__SpriteSheet2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new SpriteSheet2D(context);
}

// class SpriteSheet2D | File: ../Urho2D/SpriteSheet2D.h
static void Register_SpriteSheet2D(asIScriptEngine* engine)
{
    // explicit SpriteSheet2D::SpriteSheet2D(Context* context)
    engine->RegisterObjectBehaviour("SpriteSheet2D", asBEHAVE_FACTORY, "SpriteSheet2D@+ f()", AS_FUNCTION(SpriteSheet2D__SpriteSheet2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, SpriteSheet2D>(engine, "Resource", "SpriteSheet2D");
    RegisterSubclass<Object, SpriteSheet2D>(engine, "Object", "SpriteSheet2D");
    RegisterSubclass<RefCounted, SpriteSheet2D>(engine, "RefCounted", "SpriteSheet2D");

    MemberCollection members;
    RegisterMembers_SpriteSheet2D<SpriteSheet2D>(engine, "SpriteSheet2D");
    CollectMembers_SpriteSheet2D(members);
    RegisterMembers(engine, "SpriteSheet2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_SpriteSheet2D
        REGISTER_CLASS_MANUAL_PART_SpriteSheet2D();
    #endif
}

// explicit TmxFile2D::TmxFile2D(Context* context)
static TmxFile2D* TmxFile2D__TmxFile2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new TmxFile2D(context);
}

// class TmxFile2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxFile2D(asIScriptEngine* engine)
{
    // explicit TmxFile2D::TmxFile2D(Context* context)
    engine->RegisterObjectBehaviour("TmxFile2D", asBEHAVE_FACTORY, "TmxFile2D@+ f()", AS_FUNCTION(TmxFile2D__TmxFile2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Resource, TmxFile2D>(engine, "Resource", "TmxFile2D");
    RegisterSubclass<Object, TmxFile2D>(engine, "Object", "TmxFile2D");
    RegisterSubclass<RefCounted, TmxFile2D>(engine, "RefCounted", "TmxFile2D");

    MemberCollection members;
    RegisterMembers_TmxFile2D<TmxFile2D>(engine, "TmxFile2D");
    CollectMembers_TmxFile2D(members);
    RegisterMembers(engine, "TmxFile2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TmxFile2D
        REGISTER_CLASS_MANUAL_PART_TmxFile2D();
    #endif
}

#endif // def URHO3D_URHO2D

// explicit Animation::Animation(Context* context)
static Animation* Animation__Animation_Contextstar()
{
    Context* context = GetScriptContext();
    return new Animation(context);
}

// class Animation | File: ../Graphics/Animation.h
static void Register_Animation(asIScriptEngine* engine)
{
    // explicit Animation::Animation(Context* context)
    engine->RegisterObjectBehaviour("Animation", asBEHAVE_FACTORY, "Animation@+ f()", AS_FUNCTION(Animation__Animation_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<ResourceWithMetadata, Animation>(engine, "ResourceWithMetadata", "Animation");
    RegisterSubclass<Resource, Animation>(engine, "Resource", "Animation");
    RegisterSubclass<Object, Animation>(engine, "Object", "Animation");
    RegisterSubclass<RefCounted, Animation>(engine, "RefCounted", "Animation");

    MemberCollection members;
    RegisterMembers_Animation<Animation>(engine, "Animation");
    CollectMembers_Animation(members);
    RegisterMembers(engine, "Animation", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Animation
        REGISTER_CLASS_MANUAL_PART_Animation();
    #endif
}

// explicit Component::Component(Context* context)
static Component* Component__Component_Contextstar()
{
    Context* context = GetScriptContext();
    return new Component(context);
}

// class Component | File: ../Scene/Component.h
static void Register_Component(asIScriptEngine* engine)
{
    // explicit Component::Component(Context* context)
    engine->RegisterObjectBehaviour("Component", asBEHAVE_FACTORY, "Component@+ f()", AS_FUNCTION(Component__Component_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Animatable, Component>(engine, "Animatable", "Component");
    RegisterSubclass<Serializable, Component>(engine, "Serializable", "Component");
    RegisterSubclass<Object, Component>(engine, "Object", "Component");
    RegisterSubclass<RefCounted, Component>(engine, "RefCounted", "Component");

    MemberCollection members;
    RegisterMembers_Component<Component>(engine, "Component");
    CollectMembers_Component(members);
    RegisterMembers(engine, "Component", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Component
        REGISTER_CLASS_MANUAL_PART_Component();
    #endif

    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
    engine->RegisterObjectMethod("Component", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Component, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);

    // virtual void Component::OnSetEnabled()
    engine->RegisterObjectMethod("Component", "void OnSetEnabled()", AS_METHODPR(Component, OnSetEnabled, (), void), AS_CALL_THISCALL);
}

// explicit Model::Model(Context* context)
static Model* Model__Model_Contextstar()
{
    Context* context = GetScriptContext();
    return new Model(context);
}

// class Model | File: ../Graphics/Model.h
static void Register_Model(asIScriptEngine* engine)
{
    // explicit Model::Model(Context* context)
    engine->RegisterObjectBehaviour("Model", asBEHAVE_FACTORY, "Model@+ f()", AS_FUNCTION(Model__Model_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<ResourceWithMetadata, Model>(engine, "ResourceWithMetadata", "Model");
    RegisterSubclass<Resource, Model>(engine, "Resource", "Model");
    RegisterSubclass<Object, Model>(engine, "Object", "Model");
    RegisterSubclass<RefCounted, Model>(engine, "RefCounted", "Model");

    MemberCollection members;
    RegisterMembers_Model<Model>(engine, "Model");
    CollectMembers_Model(members);
    RegisterMembers(engine, "Model", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Model
        REGISTER_CLASS_MANUAL_PART_Model();
    #endif
}

// explicit Node::Node(Context* context)
static Node* Node__Node_Contextstar()
{
    Context* context = GetScriptContext();
    return new Node(context);
}

// class Node | File: ../Scene/Node.h
static void Register_Node(asIScriptEngine* engine)
{
    // explicit Node::Node(Context* context)
    engine->RegisterObjectBehaviour("Node", asBEHAVE_FACTORY, "Node@+ f()", AS_FUNCTION(Node__Node_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Animatable, Node>(engine, "Animatable", "Node");
    RegisterSubclass<Serializable, Node>(engine, "Serializable", "Node");
    RegisterSubclass<Object, Node>(engine, "Object", "Node");
    RegisterSubclass<RefCounted, Node>(engine, "RefCounted", "Node");

    MemberCollection members;
    RegisterMembers_Node<Node>(engine, "Node");
    CollectMembers_Node(members);
    RegisterMembers(engine, "Node", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Node
        REGISTER_CLASS_MANUAL_PART_Node();
    #endif

    // bool Node::Load(Deserializer& source, SceneResolver& resolver, bool loadChildren = true, bool rewriteIDs = false, CreateMode mode = REPLICATED)
    engine->RegisterObjectMethod("Node", "bool Load(Deserializer&, SceneResolver&, bool = true, bool = false, CreateMode = REPLICATED)", AS_METHODPR(Node, Load, (Deserializer&, SceneResolver&, bool, bool, CreateMode), bool), AS_CALL_THISCALL);

    // bool Node::LoadJSON(const JSONValue& source, SceneResolver& resolver, bool loadChildren = true, bool rewriteIDs = false, CreateMode mode = REPLICATED)
    engine->RegisterObjectMethod("Node", "bool LoadJSON(const JSONValue&in, SceneResolver&, bool = true, bool = false, CreateMode = REPLICATED)", AS_METHODPR(Node, LoadJSON, (const JSONValue&, SceneResolver&, bool, bool, CreateMode), bool), AS_CALL_THISCALL);

    // bool Node::LoadXML(const XMLElement& source, SceneResolver& resolver, bool loadChildren = true, bool rewriteIDs = false, CreateMode mode = REPLICATED)
    engine->RegisterObjectMethod("Node", "bool LoadXML(const XMLElement&in, SceneResolver&, bool = true, bool = false, CreateMode = REPLICATED)", AS_METHODPR(Node, LoadXML, (const XMLElement&, SceneResolver&, bool, bool, CreateMode), bool), AS_CALL_THISCALL);

    // void Node::MarkReplicationDirty()
    engine->RegisterObjectMethod("Node", "void MarkReplicationDirty()", AS_METHODPR(Node, MarkReplicationDirty, (), void), AS_CALL_THISCALL);
}

// explicit Sound::Sound(Context* context)
static Sound* Sound__Sound_Contextstar()
{
    Context* context = GetScriptContext();
    return new Sound(context);
}

// class Sound | File: ../Audio/Sound.h
static void Register_Sound(asIScriptEngine* engine)
{
    // explicit Sound::Sound(Context* context)
    engine->RegisterObjectBehaviour("Sound", asBEHAVE_FACTORY, "Sound@+ f()", AS_FUNCTION(Sound__Sound_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<ResourceWithMetadata, Sound>(engine, "ResourceWithMetadata", "Sound");
    RegisterSubclass<Resource, Sound>(engine, "Resource", "Sound");
    RegisterSubclass<Object, Sound>(engine, "Object", "Sound");
    RegisterSubclass<RefCounted, Sound>(engine, "RefCounted", "Sound");

    MemberCollection members;
    RegisterMembers_Sound<Sound>(engine, "Sound");
    CollectMembers_Sound(members);
    RegisterMembers(engine, "Sound", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Sound
        REGISTER_CLASS_MANUAL_PART_Sound();
    #endif
}

// explicit Texture::Texture(Context* context)
static Texture* Texture__Texture_Contextstar()
{
    Context* context = GetScriptContext();
    return new Texture(context);
}

// class Texture | File: ../Graphics/Texture.h
static void Register_Texture(asIScriptEngine* engine)
{
    // explicit Texture::Texture(Context* context)
    engine->RegisterObjectBehaviour("Texture", asBEHAVE_FACTORY, "Texture@+ f()", AS_FUNCTION(Texture__Texture_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<ResourceWithMetadata, Texture>(engine, "ResourceWithMetadata", "Texture");
    RegisterSubclass<Resource, Texture>(engine, "Resource", "Texture");
    RegisterSubclass<Object, Texture>(engine, "Object", "Texture");
    RegisterSubclass<RefCounted, Texture>(engine, "RefCounted", "Texture");

    MemberCollection members;
    RegisterMembers_Texture<Texture>(engine, "Texture");
    CollectMembers_Texture(members);
    RegisterMembers(engine, "Texture", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Texture
        REGISTER_CLASS_MANUAL_PART_Texture();
    #endif
}

// explicit UIElement::UIElement(Context* context)
static UIElement* UIElement__UIElement_Contextstar()
{
    Context* context = GetScriptContext();
    return new UIElement(context);
}

// class UIElement | File: ../UI/UIElement.h
static void Register_UIElement(asIScriptEngine* engine)
{
    // explicit UIElement::UIElement(Context* context)
    engine->RegisterObjectBehaviour("UIElement", asBEHAVE_FACTORY, "UIElement@+ f()", AS_FUNCTION(UIElement__UIElement_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Animatable, UIElement>(engine, "Animatable", "UIElement");
    RegisterSubclass<Serializable, UIElement>(engine, "Serializable", "UIElement");
    RegisterSubclass<Object, UIElement>(engine, "Object", "UIElement");
    RegisterSubclass<RefCounted, UIElement>(engine, "RefCounted", "UIElement");

    MemberCollection members;
    RegisterMembers_UIElement<UIElement>(engine, "UIElement");
    CollectMembers_UIElement(members);
    RegisterMembers(engine, "UIElement", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_UIElement
        REGISTER_CLASS_MANUAL_PART_UIElement();
    #endif

    // const IntVector2& UIElement::GetPosition() const
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetPosition() const", AS_METHODPR(UIElement, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_position() const", AS_METHODPR(UIElement, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);

    // bool UIElement::IsSelected() const
    engine->RegisterObjectMethod("UIElement", "bool IsSelected() const", AS_METHODPR(UIElement, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_selected() const", AS_METHODPR(UIElement, IsSelected, () const, bool), AS_CALL_THISCALL);

    // bool UIElement::LoadXML(const XMLElement& source) override
    engine->RegisterObjectMethod("UIElement", "bool LoadXML(const XMLElement&in)", AS_METHODPR(UIElement, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);

    // bool UIElement::LoadXML(Deserializer& source)
    engine->RegisterObjectMethod("UIElement", "bool LoadXML(Deserializer&)", AS_METHODPR(UIElement, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);

    // bool UIElement::SaveXML(Serializer& dest, const String& indentation = "\t") const
    engine->RegisterObjectMethod("UIElement", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(UIElement, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);

    // void UIElement::SetPosition(const IntVector2& position)
    engine->RegisterObjectMethod("UIElement", "void SetPosition(const IntVector2&in)", AS_METHODPR(UIElement, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_position(const IntVector2&in)", AS_METHODPR(UIElement, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);

    // void UIElement::SetPosition(int x, int y)
    engine->RegisterObjectMethod("UIElement", "void SetPosition(int, int)", AS_METHODPR(UIElement, SetPosition, (int, int), void), AS_CALL_THISCALL);
}

// explicit AnimationController::AnimationController(Context* context)
static AnimationController* AnimationController__AnimationController_Contextstar()
{
    Context* context = GetScriptContext();
    return new AnimationController(context);
}

// class AnimationController | File: ../Graphics/AnimationController.h
static void Register_AnimationController(asIScriptEngine* engine)
{
    // explicit AnimationController::AnimationController(Context* context)
    engine->RegisterObjectBehaviour("AnimationController", asBEHAVE_FACTORY, "AnimationController@+ f()", AS_FUNCTION(AnimationController__AnimationController_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, AnimationController>(engine, "Component", "AnimationController");
    RegisterSubclass<Animatable, AnimationController>(engine, "Animatable", "AnimationController");
    RegisterSubclass<Serializable, AnimationController>(engine, "Serializable", "AnimationController");
    RegisterSubclass<Object, AnimationController>(engine, "Object", "AnimationController");
    RegisterSubclass<RefCounted, AnimationController>(engine, "RefCounted", "AnimationController");

    MemberCollection members;
    RegisterMembers_AnimationController<AnimationController>(engine, "AnimationController");
    CollectMembers_AnimationController(members);
    RegisterMembers(engine, "AnimationController", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AnimationController
        REGISTER_CLASS_MANUAL_PART_AnimationController();
    #endif
}

// explicit BorderImage::BorderImage(Context* context)
static BorderImage* BorderImage__BorderImage_Contextstar()
{
    Context* context = GetScriptContext();
    return new BorderImage(context);
}

// class BorderImage | File: ../UI/BorderImage.h
static void Register_BorderImage(asIScriptEngine* engine)
{
    // explicit BorderImage::BorderImage(Context* context)
    engine->RegisterObjectBehaviour("BorderImage", asBEHAVE_FACTORY, "BorderImage@+ f()", AS_FUNCTION(BorderImage__BorderImage_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<UIElement, BorderImage>(engine, "UIElement", "BorderImage");
    RegisterSubclass<Animatable, BorderImage>(engine, "Animatable", "BorderImage");
    RegisterSubclass<Serializable, BorderImage>(engine, "Serializable", "BorderImage");
    RegisterSubclass<Object, BorderImage>(engine, "Object", "BorderImage");
    RegisterSubclass<RefCounted, BorderImage>(engine, "RefCounted", "BorderImage");

    MemberCollection members;
    RegisterMembers_BorderImage<BorderImage>(engine, "BorderImage");
    CollectMembers_BorderImage(members);
    RegisterMembers(engine, "BorderImage", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_BorderImage
        REGISTER_CLASS_MANUAL_PART_BorderImage();
    #endif

    // bool UIElement::LoadXML(const XMLElement& source) override
    engine->RegisterObjectMethod("BorderImage", "bool LoadXML(const XMLElement&in)", AS_METHODPR(BorderImage, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);

    // bool UIElement::LoadXML(Deserializer& source)
    engine->RegisterObjectMethod("BorderImage", "bool LoadXML(Deserializer&)", AS_METHODPR(BorderImage, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);

    // bool UIElement::SaveXML(Serializer& dest, const String& indentation = "\t") const
    engine->RegisterObjectMethod("BorderImage", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(BorderImage, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
}

// explicit Camera::Camera(Context* context)
static Camera* Camera__Camera_Contextstar()
{
    Context* context = GetScriptContext();
    return new Camera(context);
}

// class Camera | File: ../Graphics/Camera.h
static void Register_Camera(asIScriptEngine* engine)
{
    // explicit Camera::Camera(Context* context)
    engine->RegisterObjectBehaviour("Camera", asBEHAVE_FACTORY, "Camera@+ f()", AS_FUNCTION(Camera__Camera_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, Camera>(engine, "Component", "Camera");
    RegisterSubclass<Animatable, Camera>(engine, "Animatable", "Camera");
    RegisterSubclass<Serializable, Camera>(engine, "Serializable", "Camera");
    RegisterSubclass<Object, Camera>(engine, "Object", "Camera");
    RegisterSubclass<RefCounted, Camera>(engine, "RefCounted", "Camera");

    MemberCollection members;
    RegisterMembers_Camera<Camera>(engine, "Camera");
    CollectMembers_Camera(members);
    RegisterMembers(engine, "Camera", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Camera
        REGISTER_CLASS_MANUAL_PART_Camera();
    #endif
}

// explicit DebugRenderer::DebugRenderer(Context* context)
static DebugRenderer* DebugRenderer__DebugRenderer_Contextstar()
{
    Context* context = GetScriptContext();
    return new DebugRenderer(context);
}

// class DebugRenderer | File: ../Graphics/DebugRenderer.h
static void Register_DebugRenderer(asIScriptEngine* engine)
{
    // explicit DebugRenderer::DebugRenderer(Context* context)
    engine->RegisterObjectBehaviour("DebugRenderer", asBEHAVE_FACTORY, "DebugRenderer@+ f()", AS_FUNCTION(DebugRenderer__DebugRenderer_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, DebugRenderer>(engine, "Component", "DebugRenderer");
    RegisterSubclass<Animatable, DebugRenderer>(engine, "Animatable", "DebugRenderer");
    RegisterSubclass<Serializable, DebugRenderer>(engine, "Serializable", "DebugRenderer");
    RegisterSubclass<Object, DebugRenderer>(engine, "Object", "DebugRenderer");
    RegisterSubclass<RefCounted, DebugRenderer>(engine, "RefCounted", "DebugRenderer");

    MemberCollection members;
    RegisterMembers_DebugRenderer<DebugRenderer>(engine, "DebugRenderer");
    CollectMembers_DebugRenderer(members);
    RegisterMembers(engine, "DebugRenderer", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_DebugRenderer
        REGISTER_CLASS_MANUAL_PART_DebugRenderer();
    #endif
}

// class Drawable | File: ../Graphics/Drawable.h
static void Register_Drawable(asIScriptEngine* engine)
{
    RegisterSubclass<Component, Drawable>(engine, "Component", "Drawable");
    RegisterSubclass<Animatable, Drawable>(engine, "Animatable", "Drawable");
    RegisterSubclass<Serializable, Drawable>(engine, "Serializable", "Drawable");
    RegisterSubclass<Object, Drawable>(engine, "Object", "Drawable");
    RegisterSubclass<RefCounted, Drawable>(engine, "RefCounted", "Drawable");

    MemberCollection members;
    RegisterMembers_Drawable<Drawable>(engine, "Drawable");
    CollectMembers_Drawable(members);
    RegisterMembers(engine, "Drawable", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Drawable
        REGISTER_CLASS_MANUAL_PART_Drawable();
    #endif

    // virtual void Drawable::Update(const FrameInfo& frame)
    engine->RegisterObjectMethod("Drawable", "void Update(const FrameInfo&in)", AS_METHODPR(Drawable, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
}

// class LogicComponent | File: ../Scene/LogicComponent.h
static void Register_LogicComponent(asIScriptEngine* engine)
{
    RegisterSubclass<Component, LogicComponent>(engine, "Component", "LogicComponent");
    RegisterSubclass<Animatable, LogicComponent>(engine, "Animatable", "LogicComponent");
    RegisterSubclass<Serializable, LogicComponent>(engine, "Serializable", "LogicComponent");
    RegisterSubclass<Object, LogicComponent>(engine, "Object", "LogicComponent");
    RegisterSubclass<RefCounted, LogicComponent>(engine, "RefCounted", "LogicComponent");

    MemberCollection members;
    RegisterMembers_LogicComponent<LogicComponent>(engine, "LogicComponent");
    CollectMembers_LogicComponent(members);
    RegisterMembers(engine, "LogicComponent", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_LogicComponent
        REGISTER_CLASS_MANUAL_PART_LogicComponent();
    #endif
}

// explicit Octree::Octree(Context* context)
static Octree* Octree__Octree_Contextstar()
{
    Context* context = GetScriptContext();
    return new Octree(context);
}

// class Octree | File: ../Graphics/Octree.h
static void Register_Octree(asIScriptEngine* engine)
{
    // explicit Octree::Octree(Context* context)
    engine->RegisterObjectBehaviour("Octree", asBEHAVE_FACTORY, "Octree@+ f()", AS_FUNCTION(Octree__Octree_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, Octree>(engine, "Component", "Octree");
    RegisterSubclass<Animatable, Octree>(engine, "Animatable", "Octree");
    RegisterSubclass<Serializable, Octree>(engine, "Serializable", "Octree");
    RegisterSubclass<Object, Octree>(engine, "Object", "Octree");
    RegisterSubclass<RefCounted, Octree>(engine, "RefCounted", "Octree");

    MemberCollection members;
    RegisterMembers_Octree<Octree>(engine, "Octree");
    CollectMembers_Octree(members);
    RegisterMembers(engine, "Octree", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Octree
        REGISTER_CLASS_MANUAL_PART_Octree();
    #endif
}

// explicit Scene::Scene(Context* context)
static Scene* Scene__Scene_Contextstar()
{
    Context* context = GetScriptContext();
    return new Scene(context);
}

// class Scene | File: ../Scene/Scene.h
static void Register_Scene(asIScriptEngine* engine)
{
    // explicit Scene::Scene(Context* context)
    engine->RegisterObjectBehaviour("Scene", asBEHAVE_FACTORY, "Scene@+ f()", AS_FUNCTION(Scene__Scene_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Node, Scene>(engine, "Node", "Scene");
    RegisterSubclass<Animatable, Scene>(engine, "Animatable", "Scene");
    RegisterSubclass<Serializable, Scene>(engine, "Serializable", "Scene");
    RegisterSubclass<Object, Scene>(engine, "Object", "Scene");
    RegisterSubclass<RefCounted, Scene>(engine, "RefCounted", "Scene");

    MemberCollection members;
    RegisterMembers_Scene<Scene>(engine, "Scene");
    CollectMembers_Scene(members);
    RegisterMembers(engine, "Scene", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Scene
        REGISTER_CLASS_MANUAL_PART_Scene();
    #endif
}

// explicit ScrollView::ScrollView(Context* context)
static ScrollView* ScrollView__ScrollView_Contextstar()
{
    Context* context = GetScriptContext();
    return new ScrollView(context);
}

// class ScrollView | File: ../UI/ScrollView.h
static void Register_ScrollView(asIScriptEngine* engine)
{
    // explicit ScrollView::ScrollView(Context* context)
    engine->RegisterObjectBehaviour("ScrollView", asBEHAVE_FACTORY, "ScrollView@+ f()", AS_FUNCTION(ScrollView__ScrollView_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<UIElement, ScrollView>(engine, "UIElement", "ScrollView");
    RegisterSubclass<Animatable, ScrollView>(engine, "Animatable", "ScrollView");
    RegisterSubclass<Serializable, ScrollView>(engine, "Serializable", "ScrollView");
    RegisterSubclass<Object, ScrollView>(engine, "Object", "ScrollView");
    RegisterSubclass<RefCounted, ScrollView>(engine, "RefCounted", "ScrollView");

    MemberCollection members;
    RegisterMembers_ScrollView<ScrollView>(engine, "ScrollView");
    CollectMembers_ScrollView(members);
    RegisterMembers(engine, "ScrollView", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ScrollView
        REGISTER_CLASS_MANUAL_PART_ScrollView();
    #endif

    // bool UIElement::IsSelected() const
    engine->RegisterObjectMethod("ScrollView", "bool IsSelected() const", AS_METHODPR(ScrollView, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_selected() const", AS_METHODPR(ScrollView, IsSelected, () const, bool), AS_CALL_THISCALL);
}

// explicit SmoothedTransform::SmoothedTransform(Context* context)
static SmoothedTransform* SmoothedTransform__SmoothedTransform_Contextstar()
{
    Context* context = GetScriptContext();
    return new SmoothedTransform(context);
}

// class SmoothedTransform | File: ../Scene/SmoothedTransform.h
static void Register_SmoothedTransform(asIScriptEngine* engine)
{
    // explicit SmoothedTransform::SmoothedTransform(Context* context)
    engine->RegisterObjectBehaviour("SmoothedTransform", asBEHAVE_FACTORY, "SmoothedTransform@+ f()", AS_FUNCTION(SmoothedTransform__SmoothedTransform_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, SmoothedTransform>(engine, "Component", "SmoothedTransform");
    RegisterSubclass<Animatable, SmoothedTransform>(engine, "Animatable", "SmoothedTransform");
    RegisterSubclass<Serializable, SmoothedTransform>(engine, "Serializable", "SmoothedTransform");
    RegisterSubclass<Object, SmoothedTransform>(engine, "Object", "SmoothedTransform");
    RegisterSubclass<RefCounted, SmoothedTransform>(engine, "RefCounted", "SmoothedTransform");

    MemberCollection members;
    RegisterMembers_SmoothedTransform<SmoothedTransform>(engine, "SmoothedTransform");
    CollectMembers_SmoothedTransform(members);
    RegisterMembers(engine, "SmoothedTransform", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_SmoothedTransform
        REGISTER_CLASS_MANUAL_PART_SmoothedTransform();
    #endif
}

// explicit SoundListener::SoundListener(Context* context)
static SoundListener* SoundListener__SoundListener_Contextstar()
{
    Context* context = GetScriptContext();
    return new SoundListener(context);
}

// class SoundListener | File: ../Audio/SoundListener.h
static void Register_SoundListener(asIScriptEngine* engine)
{
    // explicit SoundListener::SoundListener(Context* context)
    engine->RegisterObjectBehaviour("SoundListener", asBEHAVE_FACTORY, "SoundListener@+ f()", AS_FUNCTION(SoundListener__SoundListener_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, SoundListener>(engine, "Component", "SoundListener");
    RegisterSubclass<Animatable, SoundListener>(engine, "Animatable", "SoundListener");
    RegisterSubclass<Serializable, SoundListener>(engine, "Serializable", "SoundListener");
    RegisterSubclass<Object, SoundListener>(engine, "Object", "SoundListener");
    RegisterSubclass<RefCounted, SoundListener>(engine, "RefCounted", "SoundListener");

    MemberCollection members;
    RegisterMembers_SoundListener<SoundListener>(engine, "SoundListener");
    CollectMembers_SoundListener(members);
    RegisterMembers(engine, "SoundListener", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_SoundListener
        REGISTER_CLASS_MANUAL_PART_SoundListener();
    #endif
}

// explicit SoundSource::SoundSource(Context* context)
static SoundSource* SoundSource__SoundSource_Contextstar()
{
    Context* context = GetScriptContext();
    return new SoundSource(context);
}

// class SoundSource | File: ../Audio/SoundSource.h
static void Register_SoundSource(asIScriptEngine* engine)
{
    // explicit SoundSource::SoundSource(Context* context)
    engine->RegisterObjectBehaviour("SoundSource", asBEHAVE_FACTORY, "SoundSource@+ f()", AS_FUNCTION(SoundSource__SoundSource_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, SoundSource>(engine, "Component", "SoundSource");
    RegisterSubclass<Animatable, SoundSource>(engine, "Animatable", "SoundSource");
    RegisterSubclass<Serializable, SoundSource>(engine, "Serializable", "SoundSource");
    RegisterSubclass<Object, SoundSource>(engine, "Object", "SoundSource");
    RegisterSubclass<RefCounted, SoundSource>(engine, "RefCounted", "SoundSource");

    MemberCollection members;
    RegisterMembers_SoundSource<SoundSource>(engine, "SoundSource");
    CollectMembers_SoundSource(members);
    RegisterMembers(engine, "SoundSource", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_SoundSource
        REGISTER_CLASS_MANUAL_PART_SoundSource();
    #endif
}

// explicit SplinePath::SplinePath(Context* context)
static SplinePath* SplinePath__SplinePath_Contextstar()
{
    Context* context = GetScriptContext();
    return new SplinePath(context);
}

// class SplinePath | File: ../Scene/SplinePath.h
static void Register_SplinePath(asIScriptEngine* engine)
{
    // explicit SplinePath::SplinePath(Context* context)
    engine->RegisterObjectBehaviour("SplinePath", asBEHAVE_FACTORY, "SplinePath@+ f()", AS_FUNCTION(SplinePath__SplinePath_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, SplinePath>(engine, "Component", "SplinePath");
    RegisterSubclass<Animatable, SplinePath>(engine, "Animatable", "SplinePath");
    RegisterSubclass<Serializable, SplinePath>(engine, "Serializable", "SplinePath");
    RegisterSubclass<Object, SplinePath>(engine, "Object", "SplinePath");
    RegisterSubclass<RefCounted, SplinePath>(engine, "RefCounted", "SplinePath");

    MemberCollection members;
    RegisterMembers_SplinePath<SplinePath>(engine, "SplinePath");
    CollectMembers_SplinePath(members);
    RegisterMembers(engine, "SplinePath", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_SplinePath
        REGISTER_CLASS_MANUAL_PART_SplinePath();
    #endif
}

// explicit Sprite::Sprite(Context* context)
static Sprite* Sprite__Sprite_Contextstar()
{
    Context* context = GetScriptContext();
    return new Sprite(context);
}

// class Sprite | File: ../UI/Sprite.h
static void Register_Sprite(asIScriptEngine* engine)
{
    // explicit Sprite::Sprite(Context* context)
    engine->RegisterObjectBehaviour("Sprite", asBEHAVE_FACTORY, "Sprite@+ f()", AS_FUNCTION(Sprite__Sprite_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<UIElement, Sprite>(engine, "UIElement", "Sprite");
    RegisterSubclass<Animatable, Sprite>(engine, "Animatable", "Sprite");
    RegisterSubclass<Serializable, Sprite>(engine, "Serializable", "Sprite");
    RegisterSubclass<Object, Sprite>(engine, "Object", "Sprite");
    RegisterSubclass<RefCounted, Sprite>(engine, "RefCounted", "Sprite");

    MemberCollection members;
    RegisterMembers_Sprite<Sprite>(engine, "Sprite");
    CollectMembers_Sprite(members);
    RegisterMembers(engine, "Sprite", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Sprite
        REGISTER_CLASS_MANUAL_PART_Sprite();
    #endif
}

// explicit Terrain::Terrain(Context* context)
static Terrain* Terrain__Terrain_Contextstar()
{
    Context* context = GetScriptContext();
    return new Terrain(context);
}

// class Terrain | File: ../Graphics/Terrain.h
static void Register_Terrain(asIScriptEngine* engine)
{
    // explicit Terrain::Terrain(Context* context)
    engine->RegisterObjectBehaviour("Terrain", asBEHAVE_FACTORY, "Terrain@+ f()", AS_FUNCTION(Terrain__Terrain_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, Terrain>(engine, "Component", "Terrain");
    RegisterSubclass<Animatable, Terrain>(engine, "Animatable", "Terrain");
    RegisterSubclass<Serializable, Terrain>(engine, "Serializable", "Terrain");
    RegisterSubclass<Object, Terrain>(engine, "Object", "Terrain");
    RegisterSubclass<RefCounted, Terrain>(engine, "RefCounted", "Terrain");

    MemberCollection members;
    RegisterMembers_Terrain<Terrain>(engine, "Terrain");
    CollectMembers_Terrain(members);
    RegisterMembers(engine, "Terrain", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Terrain
        REGISTER_CLASS_MANUAL_PART_Terrain();
    #endif
}

// explicit Texture2D::Texture2D(Context* context)
static Texture2D* Texture2D__Texture2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new Texture2D(context);
}

// class Texture2D | File: ../Graphics/Texture2D.h
static void Register_Texture2D(asIScriptEngine* engine)
{
    // explicit Texture2D::Texture2D(Context* context)
    engine->RegisterObjectBehaviour("Texture2D", asBEHAVE_FACTORY, "Texture2D@+ f()", AS_FUNCTION(Texture2D__Texture2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Texture, Texture2D>(engine, "Texture", "Texture2D");
    RegisterSubclass<ResourceWithMetadata, Texture2D>(engine, "ResourceWithMetadata", "Texture2D");
    RegisterSubclass<Resource, Texture2D>(engine, "Resource", "Texture2D");
    RegisterSubclass<Object, Texture2D>(engine, "Object", "Texture2D");
    RegisterSubclass<RefCounted, Texture2D>(engine, "RefCounted", "Texture2D");

    MemberCollection members;
    RegisterMembers_Texture2D<Texture2D>(engine, "Texture2D");
    CollectMembers_Texture2D(members);
    RegisterMembers(engine, "Texture2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Texture2D
        REGISTER_CLASS_MANUAL_PART_Texture2D();
    #endif
}

// explicit Texture2DArray::Texture2DArray(Context* context)
static Texture2DArray* Texture2DArray__Texture2DArray_Contextstar()
{
    Context* context = GetScriptContext();
    return new Texture2DArray(context);
}

// class Texture2DArray | File: ../Graphics/Texture2DArray.h
static void Register_Texture2DArray(asIScriptEngine* engine)
{
    // explicit Texture2DArray::Texture2DArray(Context* context)
    engine->RegisterObjectBehaviour("Texture2DArray", asBEHAVE_FACTORY, "Texture2DArray@+ f()", AS_FUNCTION(Texture2DArray__Texture2DArray_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Texture, Texture2DArray>(engine, "Texture", "Texture2DArray");
    RegisterSubclass<ResourceWithMetadata, Texture2DArray>(engine, "ResourceWithMetadata", "Texture2DArray");
    RegisterSubclass<Resource, Texture2DArray>(engine, "Resource", "Texture2DArray");
    RegisterSubclass<Object, Texture2DArray>(engine, "Object", "Texture2DArray");
    RegisterSubclass<RefCounted, Texture2DArray>(engine, "RefCounted", "Texture2DArray");

    MemberCollection members;
    RegisterMembers_Texture2DArray<Texture2DArray>(engine, "Texture2DArray");
    CollectMembers_Texture2DArray(members);
    RegisterMembers(engine, "Texture2DArray", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Texture2DArray
        REGISTER_CLASS_MANUAL_PART_Texture2DArray();
    #endif
}

// explicit Texture3D::Texture3D(Context* context)
static Texture3D* Texture3D__Texture3D_Contextstar()
{
    Context* context = GetScriptContext();
    return new Texture3D(context);
}

// class Texture3D | File: ../Graphics/Texture3D.h
static void Register_Texture3D(asIScriptEngine* engine)
{
    // explicit Texture3D::Texture3D(Context* context)
    engine->RegisterObjectBehaviour("Texture3D", asBEHAVE_FACTORY, "Texture3D@+ f()", AS_FUNCTION(Texture3D__Texture3D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Texture, Texture3D>(engine, "Texture", "Texture3D");
    RegisterSubclass<ResourceWithMetadata, Texture3D>(engine, "ResourceWithMetadata", "Texture3D");
    RegisterSubclass<Resource, Texture3D>(engine, "Resource", "Texture3D");
    RegisterSubclass<Object, Texture3D>(engine, "Object", "Texture3D");
    RegisterSubclass<RefCounted, Texture3D>(engine, "RefCounted", "Texture3D");

    MemberCollection members;
    RegisterMembers_Texture3D<Texture3D>(engine, "Texture3D");
    CollectMembers_Texture3D(members);
    RegisterMembers(engine, "Texture3D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Texture3D
        REGISTER_CLASS_MANUAL_PART_Texture3D();
    #endif
}

// explicit TextureCube::TextureCube(Context* context)
static TextureCube* TextureCube__TextureCube_Contextstar()
{
    Context* context = GetScriptContext();
    return new TextureCube(context);
}

// class TextureCube | File: ../Graphics/TextureCube.h
static void Register_TextureCube(asIScriptEngine* engine)
{
    // explicit TextureCube::TextureCube(Context* context)
    engine->RegisterObjectBehaviour("TextureCube", asBEHAVE_FACTORY, "TextureCube@+ f()", AS_FUNCTION(TextureCube__TextureCube_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Texture, TextureCube>(engine, "Texture", "TextureCube");
    RegisterSubclass<ResourceWithMetadata, TextureCube>(engine, "ResourceWithMetadata", "TextureCube");
    RegisterSubclass<Resource, TextureCube>(engine, "Resource", "TextureCube");
    RegisterSubclass<Object, TextureCube>(engine, "Object", "TextureCube");
    RegisterSubclass<RefCounted, TextureCube>(engine, "RefCounted", "TextureCube");

    MemberCollection members;
    RegisterMembers_TextureCube<TextureCube>(engine, "TextureCube");
    CollectMembers_TextureCube(members);
    RegisterMembers(engine, "TextureCube", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TextureCube
        REGISTER_CLASS_MANUAL_PART_TextureCube();
    #endif
}

// explicit ToolTip::ToolTip(Context* context)
static ToolTip* ToolTip__ToolTip_Contextstar()
{
    Context* context = GetScriptContext();
    return new ToolTip(context);
}

// class ToolTip | File: ../UI/ToolTip.h
static void Register_ToolTip(asIScriptEngine* engine)
{
    // explicit ToolTip::ToolTip(Context* context)
    engine->RegisterObjectBehaviour("ToolTip", asBEHAVE_FACTORY, "ToolTip@+ f()", AS_FUNCTION(ToolTip__ToolTip_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<UIElement, ToolTip>(engine, "UIElement", "ToolTip");
    RegisterSubclass<Animatable, ToolTip>(engine, "Animatable", "ToolTip");
    RegisterSubclass<Serializable, ToolTip>(engine, "Serializable", "ToolTip");
    RegisterSubclass<Object, ToolTip>(engine, "Object", "ToolTip");
    RegisterSubclass<RefCounted, ToolTip>(engine, "RefCounted", "ToolTip");

    MemberCollection members;
    RegisterMembers_ToolTip<ToolTip>(engine, "ToolTip");
    CollectMembers_ToolTip(members);
    RegisterMembers(engine, "ToolTip", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ToolTip
        REGISTER_CLASS_MANUAL_PART_ToolTip();
    #endif
}

// explicit UIComponent::UIComponent(Context* context)
static UIComponent* UIComponent__UIComponent_Contextstar()
{
    Context* context = GetScriptContext();
    return new UIComponent(context);
}

// class UIComponent | File: ../UI/UIComponent.h
static void Register_UIComponent(asIScriptEngine* engine)
{
    // explicit UIComponent::UIComponent(Context* context)
    engine->RegisterObjectBehaviour("UIComponent", asBEHAVE_FACTORY, "UIComponent@+ f()", AS_FUNCTION(UIComponent__UIComponent_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, UIComponent>(engine, "Component", "UIComponent");
    RegisterSubclass<Animatable, UIComponent>(engine, "Animatable", "UIComponent");
    RegisterSubclass<Serializable, UIComponent>(engine, "Serializable", "UIComponent");
    RegisterSubclass<Object, UIComponent>(engine, "Object", "UIComponent");
    RegisterSubclass<RefCounted, UIComponent>(engine, "RefCounted", "UIComponent");

    MemberCollection members;
    RegisterMembers_UIComponent<UIComponent>(engine, "UIComponent");
    CollectMembers_UIComponent(members);
    RegisterMembers(engine, "UIComponent", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_UIComponent
        REGISTER_CLASS_MANUAL_PART_UIComponent();
    #endif
}

// class UISelectable | File: ../UI/UISelectable.h
static void Register_UISelectable(asIScriptEngine* engine)
{
    RegisterSubclass<UIElement, UISelectable>(engine, "UIElement", "UISelectable");
    RegisterSubclass<Animatable, UISelectable>(engine, "Animatable", "UISelectable");
    RegisterSubclass<Serializable, UISelectable>(engine, "Serializable", "UISelectable");
    RegisterSubclass<Object, UISelectable>(engine, "Object", "UISelectable");
    RegisterSubclass<RefCounted, UISelectable>(engine, "RefCounted", "UISelectable");

    MemberCollection members;
    RegisterMembers_UISelectable<UISelectable>(engine, "UISelectable");
    CollectMembers_UISelectable(members);
    RegisterMembers(engine, "UISelectable", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_UISelectable
        REGISTER_CLASS_MANUAL_PART_UISelectable();
    #endif
}

// class UnknownComponent | File: ../Scene/UnknownComponent.h
static void Register_UnknownComponent(asIScriptEngine* engine)
{
    RegisterSubclass<Component, UnknownComponent>(engine, "Component", "UnknownComponent");
    RegisterSubclass<Animatable, UnknownComponent>(engine, "Animatable", "UnknownComponent");
    RegisterSubclass<Serializable, UnknownComponent>(engine, "Serializable", "UnknownComponent");
    RegisterSubclass<Object, UnknownComponent>(engine, "Object", "UnknownComponent");
    RegisterSubclass<RefCounted, UnknownComponent>(engine, "RefCounted", "UnknownComponent");

    MemberCollection members;
    RegisterMembers_UnknownComponent<UnknownComponent>(engine, "UnknownComponent");
    CollectMembers_UnknownComponent(members);
    RegisterMembers(engine, "UnknownComponent", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_UnknownComponent
        REGISTER_CLASS_MANUAL_PART_UnknownComponent();
    #endif
}

#ifdef URHO3D_IK

// explicit IKConstraint::IKConstraint(Context* context)
static IKConstraint* IKConstraint__IKConstraint_Contextstar()
{
    Context* context = GetScriptContext();
    return new IKConstraint(context);
}

// class IKConstraint | File: ../IK/IKConstraint.h
static void Register_IKConstraint(asIScriptEngine* engine)
{
    // explicit IKConstraint::IKConstraint(Context* context)
    engine->RegisterObjectBehaviour("IKConstraint", asBEHAVE_FACTORY, "IKConstraint@+ f()", AS_FUNCTION(IKConstraint__IKConstraint_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, IKConstraint>(engine, "Component", "IKConstraint");
    RegisterSubclass<Animatable, IKConstraint>(engine, "Animatable", "IKConstraint");
    RegisterSubclass<Serializable, IKConstraint>(engine, "Serializable", "IKConstraint");
    RegisterSubclass<Object, IKConstraint>(engine, "Object", "IKConstraint");
    RegisterSubclass<RefCounted, IKConstraint>(engine, "RefCounted", "IKConstraint");

    MemberCollection members;
    RegisterMembers_IKConstraint<IKConstraint>(engine, "IKConstraint");
    CollectMembers_IKConstraint(members);
    RegisterMembers(engine, "IKConstraint", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_IKConstraint
        REGISTER_CLASS_MANUAL_PART_IKConstraint();
    #endif
}

// explicit IKEffector::IKEffector(Context* context)
static IKEffector* IKEffector__IKEffector_Contextstar()
{
    Context* context = GetScriptContext();
    return new IKEffector(context);
}

// class IKEffector | File: ../IK/IKEffector.h
static void Register_IKEffector(asIScriptEngine* engine)
{
    // explicit IKEffector::IKEffector(Context* context)
    engine->RegisterObjectBehaviour("IKEffector", asBEHAVE_FACTORY, "IKEffector@+ f()", AS_FUNCTION(IKEffector__IKEffector_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, IKEffector>(engine, "Component", "IKEffector");
    RegisterSubclass<Animatable, IKEffector>(engine, "Animatable", "IKEffector");
    RegisterSubclass<Serializable, IKEffector>(engine, "Serializable", "IKEffector");
    RegisterSubclass<Object, IKEffector>(engine, "Object", "IKEffector");
    RegisterSubclass<RefCounted, IKEffector>(engine, "RefCounted", "IKEffector");

    MemberCollection members;
    RegisterMembers_IKEffector<IKEffector>(engine, "IKEffector");
    CollectMembers_IKEffector(members);
    RegisterMembers(engine, "IKEffector", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_IKEffector
        REGISTER_CLASS_MANUAL_PART_IKEffector();
    #endif
}

// explicit IKSolver::IKSolver(Context* context)
static IKSolver* IKSolver__IKSolver_Contextstar()
{
    Context* context = GetScriptContext();
    return new IKSolver(context);
}

// class IKSolver | File: ../IK/IKSolver.h
static void Register_IKSolver(asIScriptEngine* engine)
{
    // explicit IKSolver::IKSolver(Context* context)
    engine->RegisterObjectBehaviour("IKSolver", asBEHAVE_FACTORY, "IKSolver@+ f()", AS_FUNCTION(IKSolver__IKSolver_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, IKSolver>(engine, "Component", "IKSolver");
    RegisterSubclass<Animatable, IKSolver>(engine, "Animatable", "IKSolver");
    RegisterSubclass<Serializable, IKSolver>(engine, "Serializable", "IKSolver");
    RegisterSubclass<Object, IKSolver>(engine, "Object", "IKSolver");
    RegisterSubclass<RefCounted, IKSolver>(engine, "RefCounted", "IKSolver");

    MemberCollection members;
    RegisterMembers_IKSolver<IKSolver>(engine, "IKSolver");
    CollectMembers_IKSolver(members);
    RegisterMembers(engine, "IKSolver", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_IKSolver
        REGISTER_CLASS_MANUAL_PART_IKSolver();
    #endif
}

#endif // def URHO3D_IK

#ifdef URHO3D_NAVIGATION

// explicit CrowdAgent::CrowdAgent(Context* context)
static CrowdAgent* CrowdAgent__CrowdAgent_Contextstar()
{
    Context* context = GetScriptContext();
    return new CrowdAgent(context);
}

// class CrowdAgent | File: ../Navigation/CrowdAgent.h
static void Register_CrowdAgent(asIScriptEngine* engine)
{
    // explicit CrowdAgent::CrowdAgent(Context* context)
    engine->RegisterObjectBehaviour("CrowdAgent", asBEHAVE_FACTORY, "CrowdAgent@+ f()", AS_FUNCTION(CrowdAgent__CrowdAgent_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, CrowdAgent>(engine, "Component", "CrowdAgent");
    RegisterSubclass<Animatable, CrowdAgent>(engine, "Animatable", "CrowdAgent");
    RegisterSubclass<Serializable, CrowdAgent>(engine, "Serializable", "CrowdAgent");
    RegisterSubclass<Object, CrowdAgent>(engine, "Object", "CrowdAgent");
    RegisterSubclass<RefCounted, CrowdAgent>(engine, "RefCounted", "CrowdAgent");

    MemberCollection members;
    RegisterMembers_CrowdAgent<CrowdAgent>(engine, "CrowdAgent");
    CollectMembers_CrowdAgent(members);
    RegisterMembers(engine, "CrowdAgent", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CrowdAgent
        REGISTER_CLASS_MANUAL_PART_CrowdAgent();
    #endif
}

// explicit CrowdManager::CrowdManager(Context* context)
static CrowdManager* CrowdManager__CrowdManager_Contextstar()
{
    Context* context = GetScriptContext();
    return new CrowdManager(context);
}

// class CrowdManager | File: ../Navigation/CrowdManager.h
static void Register_CrowdManager(asIScriptEngine* engine)
{
    // explicit CrowdManager::CrowdManager(Context* context)
    engine->RegisterObjectBehaviour("CrowdManager", asBEHAVE_FACTORY, "CrowdManager@+ f()", AS_FUNCTION(CrowdManager__CrowdManager_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, CrowdManager>(engine, "Component", "CrowdManager");
    RegisterSubclass<Animatable, CrowdManager>(engine, "Animatable", "CrowdManager");
    RegisterSubclass<Serializable, CrowdManager>(engine, "Serializable", "CrowdManager");
    RegisterSubclass<Object, CrowdManager>(engine, "Object", "CrowdManager");
    RegisterSubclass<RefCounted, CrowdManager>(engine, "RefCounted", "CrowdManager");

    MemberCollection members;
    RegisterMembers_CrowdManager<CrowdManager>(engine, "CrowdManager");
    CollectMembers_CrowdManager(members);
    RegisterMembers(engine, "CrowdManager", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CrowdManager
        REGISTER_CLASS_MANUAL_PART_CrowdManager();
    #endif
}

// explicit NavArea::NavArea(Context* context)
static NavArea* NavArea__NavArea_Contextstar()
{
    Context* context = GetScriptContext();
    return new NavArea(context);
}

// class NavArea | File: ../Navigation/NavArea.h
static void Register_NavArea(asIScriptEngine* engine)
{
    // explicit NavArea::NavArea(Context* context)
    engine->RegisterObjectBehaviour("NavArea", asBEHAVE_FACTORY, "NavArea@+ f()", AS_FUNCTION(NavArea__NavArea_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, NavArea>(engine, "Component", "NavArea");
    RegisterSubclass<Animatable, NavArea>(engine, "Animatable", "NavArea");
    RegisterSubclass<Serializable, NavArea>(engine, "Serializable", "NavArea");
    RegisterSubclass<Object, NavArea>(engine, "Object", "NavArea");
    RegisterSubclass<RefCounted, NavArea>(engine, "RefCounted", "NavArea");

    MemberCollection members;
    RegisterMembers_NavArea<NavArea>(engine, "NavArea");
    CollectMembers_NavArea(members);
    RegisterMembers(engine, "NavArea", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_NavArea
        REGISTER_CLASS_MANUAL_PART_NavArea();
    #endif
}

// explicit Navigable::Navigable(Context* context)
static Navigable* Navigable__Navigable_Contextstar()
{
    Context* context = GetScriptContext();
    return new Navigable(context);
}

// class Navigable | File: ../Navigation/Navigable.h
static void Register_Navigable(asIScriptEngine* engine)
{
    // explicit Navigable::Navigable(Context* context)
    engine->RegisterObjectBehaviour("Navigable", asBEHAVE_FACTORY, "Navigable@+ f()", AS_FUNCTION(Navigable__Navigable_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, Navigable>(engine, "Component", "Navigable");
    RegisterSubclass<Animatable, Navigable>(engine, "Animatable", "Navigable");
    RegisterSubclass<Serializable, Navigable>(engine, "Serializable", "Navigable");
    RegisterSubclass<Object, Navigable>(engine, "Object", "Navigable");
    RegisterSubclass<RefCounted, Navigable>(engine, "RefCounted", "Navigable");

    MemberCollection members;
    RegisterMembers_Navigable<Navigable>(engine, "Navigable");
    CollectMembers_Navigable(members);
    RegisterMembers(engine, "Navigable", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Navigable
        REGISTER_CLASS_MANUAL_PART_Navigable();
    #endif
}

// explicit NavigationMesh::NavigationMesh(Context* context)
static NavigationMesh* NavigationMesh__NavigationMesh_Contextstar()
{
    Context* context = GetScriptContext();
    return new NavigationMesh(context);
}

// class NavigationMesh | File: ../Navigation/NavigationMesh.h
static void Register_NavigationMesh(asIScriptEngine* engine)
{
    // explicit NavigationMesh::NavigationMesh(Context* context)
    engine->RegisterObjectBehaviour("NavigationMesh", asBEHAVE_FACTORY, "NavigationMesh@+ f()", AS_FUNCTION(NavigationMesh__NavigationMesh_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, NavigationMesh>(engine, "Component", "NavigationMesh");
    RegisterSubclass<Animatable, NavigationMesh>(engine, "Animatable", "NavigationMesh");
    RegisterSubclass<Serializable, NavigationMesh>(engine, "Serializable", "NavigationMesh");
    RegisterSubclass<Object, NavigationMesh>(engine, "Object", "NavigationMesh");
    RegisterSubclass<RefCounted, NavigationMesh>(engine, "RefCounted", "NavigationMesh");

    MemberCollection members;
    RegisterMembers_NavigationMesh<NavigationMesh>(engine, "NavigationMesh");
    CollectMembers_NavigationMesh(members);
    RegisterMembers(engine, "NavigationMesh", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_NavigationMesh
        REGISTER_CLASS_MANUAL_PART_NavigationMesh();
    #endif
}

// explicit Obstacle::Obstacle(Context* context)
static Obstacle* Obstacle__Obstacle_Contextstar()
{
    Context* context = GetScriptContext();
    return new Obstacle(context);
}

// class Obstacle | File: ../Navigation/Obstacle.h
static void Register_Obstacle(asIScriptEngine* engine)
{
    // explicit Obstacle::Obstacle(Context* context)
    engine->RegisterObjectBehaviour("Obstacle", asBEHAVE_FACTORY, "Obstacle@+ f()", AS_FUNCTION(Obstacle__Obstacle_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, Obstacle>(engine, "Component", "Obstacle");
    RegisterSubclass<Animatable, Obstacle>(engine, "Animatable", "Obstacle");
    RegisterSubclass<Serializable, Obstacle>(engine, "Serializable", "Obstacle");
    RegisterSubclass<Object, Obstacle>(engine, "Object", "Obstacle");
    RegisterSubclass<RefCounted, Obstacle>(engine, "RefCounted", "Obstacle");

    MemberCollection members;
    RegisterMembers_Obstacle<Obstacle>(engine, "Obstacle");
    CollectMembers_Obstacle(members);
    RegisterMembers(engine, "Obstacle", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Obstacle
        REGISTER_CLASS_MANUAL_PART_Obstacle();
    #endif
}

// explicit OffMeshConnection::OffMeshConnection(Context* context)
static OffMeshConnection* OffMeshConnection__OffMeshConnection_Contextstar()
{
    Context* context = GetScriptContext();
    return new OffMeshConnection(context);
}

// class OffMeshConnection | File: ../Navigation/OffMeshConnection.h
static void Register_OffMeshConnection(asIScriptEngine* engine)
{
    // explicit OffMeshConnection::OffMeshConnection(Context* context)
    engine->RegisterObjectBehaviour("OffMeshConnection", asBEHAVE_FACTORY, "OffMeshConnection@+ f()", AS_FUNCTION(OffMeshConnection__OffMeshConnection_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, OffMeshConnection>(engine, "Component", "OffMeshConnection");
    RegisterSubclass<Animatable, OffMeshConnection>(engine, "Animatable", "OffMeshConnection");
    RegisterSubclass<Serializable, OffMeshConnection>(engine, "Serializable", "OffMeshConnection");
    RegisterSubclass<Object, OffMeshConnection>(engine, "Object", "OffMeshConnection");
    RegisterSubclass<RefCounted, OffMeshConnection>(engine, "RefCounted", "OffMeshConnection");

    MemberCollection members;
    RegisterMembers_OffMeshConnection<OffMeshConnection>(engine, "OffMeshConnection");
    CollectMembers_OffMeshConnection(members);
    RegisterMembers(engine, "OffMeshConnection", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_OffMeshConnection
        REGISTER_CLASS_MANUAL_PART_OffMeshConnection();
    #endif
}

#endif // def URHO3D_NAVIGATION

#ifdef URHO3D_NETWORK

// explicit NetworkPriority::NetworkPriority(Context* context)
static NetworkPriority* NetworkPriority__NetworkPriority_Contextstar()
{
    Context* context = GetScriptContext();
    return new NetworkPriority(context);
}

// class NetworkPriority | File: ../Network/NetworkPriority.h
static void Register_NetworkPriority(asIScriptEngine* engine)
{
    // explicit NetworkPriority::NetworkPriority(Context* context)
    engine->RegisterObjectBehaviour("NetworkPriority", asBEHAVE_FACTORY, "NetworkPriority@+ f()", AS_FUNCTION(NetworkPriority__NetworkPriority_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, NetworkPriority>(engine, "Component", "NetworkPriority");
    RegisterSubclass<Animatable, NetworkPriority>(engine, "Animatable", "NetworkPriority");
    RegisterSubclass<Serializable, NetworkPriority>(engine, "Serializable", "NetworkPriority");
    RegisterSubclass<Object, NetworkPriority>(engine, "Object", "NetworkPriority");
    RegisterSubclass<RefCounted, NetworkPriority>(engine, "RefCounted", "NetworkPriority");

    MemberCollection members;
    RegisterMembers_NetworkPriority<NetworkPriority>(engine, "NetworkPriority");
    CollectMembers_NetworkPriority(members);
    RegisterMembers(engine, "NetworkPriority", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_NetworkPriority
        REGISTER_CLASS_MANUAL_PART_NetworkPriority();
    #endif
}

#endif // def URHO3D_NETWORK

#ifdef URHO3D_PHYSICS

// explicit CollisionShape::CollisionShape(Context* context)
static CollisionShape* CollisionShape__CollisionShape_Contextstar()
{
    Context* context = GetScriptContext();
    return new CollisionShape(context);
}

// class CollisionShape | File: ../Physics/CollisionShape.h
static void Register_CollisionShape(asIScriptEngine* engine)
{
    // explicit CollisionShape::CollisionShape(Context* context)
    engine->RegisterObjectBehaviour("CollisionShape", asBEHAVE_FACTORY, "CollisionShape@+ f()", AS_FUNCTION(CollisionShape__CollisionShape_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, CollisionShape>(engine, "Component", "CollisionShape");
    RegisterSubclass<Animatable, CollisionShape>(engine, "Animatable", "CollisionShape");
    RegisterSubclass<Serializable, CollisionShape>(engine, "Serializable", "CollisionShape");
    RegisterSubclass<Object, CollisionShape>(engine, "Object", "CollisionShape");
    RegisterSubclass<RefCounted, CollisionShape>(engine, "RefCounted", "CollisionShape");

    MemberCollection members;
    RegisterMembers_CollisionShape<CollisionShape>(engine, "CollisionShape");
    CollectMembers_CollisionShape(members);
    RegisterMembers(engine, "CollisionShape", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CollisionShape
        REGISTER_CLASS_MANUAL_PART_CollisionShape();
    #endif
}

// explicit Constraint::Constraint(Context* context)
static Constraint* Constraint__Constraint_Contextstar()
{
    Context* context = GetScriptContext();
    return new Constraint(context);
}

// class Constraint | File: ../Physics/Constraint.h
static void Register_Constraint(asIScriptEngine* engine)
{
    // explicit Constraint::Constraint(Context* context)
    engine->RegisterObjectBehaviour("Constraint", asBEHAVE_FACTORY, "Constraint@+ f()", AS_FUNCTION(Constraint__Constraint_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, Constraint>(engine, "Component", "Constraint");
    RegisterSubclass<Animatable, Constraint>(engine, "Animatable", "Constraint");
    RegisterSubclass<Serializable, Constraint>(engine, "Serializable", "Constraint");
    RegisterSubclass<Object, Constraint>(engine, "Object", "Constraint");
    RegisterSubclass<RefCounted, Constraint>(engine, "RefCounted", "Constraint");

    MemberCollection members;
    RegisterMembers_Constraint<Constraint>(engine, "Constraint");
    CollectMembers_Constraint(members);
    RegisterMembers(engine, "Constraint", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Constraint
        REGISTER_CLASS_MANUAL_PART_Constraint();
    #endif
}

// explicit PhysicsWorld::PhysicsWorld(Context* context)
static PhysicsWorld* PhysicsWorld__PhysicsWorld_Contextstar()
{
    Context* context = GetScriptContext();
    return new PhysicsWorld(context);
}

// class PhysicsWorld | File: ../Physics/PhysicsWorld.h
static void Register_PhysicsWorld(asIScriptEngine* engine)
{
    // explicit PhysicsWorld::PhysicsWorld(Context* context)
    engine->RegisterObjectBehaviour("PhysicsWorld", asBEHAVE_FACTORY, "PhysicsWorld@+ f()", AS_FUNCTION(PhysicsWorld__PhysicsWorld_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, PhysicsWorld>(engine, "Component", "PhysicsWorld");
    RegisterSubclass<Animatable, PhysicsWorld>(engine, "Animatable", "PhysicsWorld");
    RegisterSubclass<Serializable, PhysicsWorld>(engine, "Serializable", "PhysicsWorld");
    RegisterSubclass<Object, PhysicsWorld>(engine, "Object", "PhysicsWorld");
    RegisterSubclass<RefCounted, PhysicsWorld>(engine, "RefCounted", "PhysicsWorld");

    MemberCollection members;
    RegisterMembers_PhysicsWorld<PhysicsWorld>(engine, "PhysicsWorld");
    CollectMembers_PhysicsWorld(members);
    RegisterMembers(engine, "PhysicsWorld", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_PhysicsWorld
        REGISTER_CLASS_MANUAL_PART_PhysicsWorld();
    #endif
}

// explicit RigidBody::RigidBody(Context* context)
static RigidBody* RigidBody__RigidBody_Contextstar()
{
    Context* context = GetScriptContext();
    return new RigidBody(context);
}

// class RigidBody | File: ../Physics/RigidBody.h
static void Register_RigidBody(asIScriptEngine* engine)
{
    // explicit RigidBody::RigidBody(Context* context)
    engine->RegisterObjectBehaviour("RigidBody", asBEHAVE_FACTORY, "RigidBody@+ f()", AS_FUNCTION(RigidBody__RigidBody_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, RigidBody>(engine, "Component", "RigidBody");
    RegisterSubclass<Animatable, RigidBody>(engine, "Animatable", "RigidBody");
    RegisterSubclass<Serializable, RigidBody>(engine, "Serializable", "RigidBody");
    RegisterSubclass<Object, RigidBody>(engine, "Object", "RigidBody");
    RegisterSubclass<RefCounted, RigidBody>(engine, "RefCounted", "RigidBody");

    MemberCollection members;
    RegisterMembers_RigidBody<RigidBody>(engine, "RigidBody");
    CollectMembers_RigidBody(members);
    RegisterMembers(engine, "RigidBody", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_RigidBody
        REGISTER_CLASS_MANUAL_PART_RigidBody();
    #endif
}

#endif // def URHO3D_PHYSICS

#ifdef URHO3D_URHO2D

// class CollisionShape2D | File: ../Urho2D/CollisionShape2D.h
static void Register_CollisionShape2D(asIScriptEngine* engine)
{
    RegisterSubclass<Component, CollisionShape2D>(engine, "Component", "CollisionShape2D");
    RegisterSubclass<Animatable, CollisionShape2D>(engine, "Animatable", "CollisionShape2D");
    RegisterSubclass<Serializable, CollisionShape2D>(engine, "Serializable", "CollisionShape2D");
    RegisterSubclass<Object, CollisionShape2D>(engine, "Object", "CollisionShape2D");
    RegisterSubclass<RefCounted, CollisionShape2D>(engine, "RefCounted", "CollisionShape2D");

    MemberCollection members;
    RegisterMembers_CollisionShape2D<CollisionShape2D>(engine, "CollisionShape2D");
    CollectMembers_CollisionShape2D(members);
    RegisterMembers(engine, "CollisionShape2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CollisionShape2D
        REGISTER_CLASS_MANUAL_PART_CollisionShape2D();
    #endif
}

// explicit Constraint2D::Constraint2D(Context* context)
static Constraint2D* Constraint2D__Constraint2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new Constraint2D(context);
}

// class Constraint2D | File: ../Urho2D/Constraint2D.h
static void Register_Constraint2D(asIScriptEngine* engine)
{
    // explicit Constraint2D::Constraint2D(Context* context)
    engine->RegisterObjectBehaviour("Constraint2D", asBEHAVE_FACTORY, "Constraint2D@+ f()", AS_FUNCTION(Constraint2D__Constraint2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, Constraint2D>(engine, "Component", "Constraint2D");
    RegisterSubclass<Animatable, Constraint2D>(engine, "Animatable", "Constraint2D");
    RegisterSubclass<Serializable, Constraint2D>(engine, "Serializable", "Constraint2D");
    RegisterSubclass<Object, Constraint2D>(engine, "Object", "Constraint2D");
    RegisterSubclass<RefCounted, Constraint2D>(engine, "RefCounted", "Constraint2D");

    MemberCollection members;
    RegisterMembers_Constraint2D<Constraint2D>(engine, "Constraint2D");
    CollectMembers_Constraint2D(members);
    RegisterMembers(engine, "Constraint2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Constraint2D
        REGISTER_CLASS_MANUAL_PART_Constraint2D();
    #endif
}

// explicit PhysicsWorld2D::PhysicsWorld2D(Context* context)
static PhysicsWorld2D* PhysicsWorld2D__PhysicsWorld2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new PhysicsWorld2D(context);
}

// class PhysicsWorld2D | File: ../Urho2D/PhysicsWorld2D.h
static void Register_PhysicsWorld2D(asIScriptEngine* engine)
{
    // explicit PhysicsWorld2D::PhysicsWorld2D(Context* context)
    engine->RegisterObjectBehaviour("PhysicsWorld2D", asBEHAVE_FACTORY, "PhysicsWorld2D@+ f()", AS_FUNCTION(PhysicsWorld2D__PhysicsWorld2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, PhysicsWorld2D>(engine, "Component", "PhysicsWorld2D");
    RegisterSubclass<Animatable, PhysicsWorld2D>(engine, "Animatable", "PhysicsWorld2D");
    RegisterSubclass<Serializable, PhysicsWorld2D>(engine, "Serializable", "PhysicsWorld2D");
    RegisterSubclass<Object, PhysicsWorld2D>(engine, "Object", "PhysicsWorld2D");
    RegisterSubclass<RefCounted, PhysicsWorld2D>(engine, "RefCounted", "PhysicsWorld2D");

    MemberCollection members;
    RegisterMembers_PhysicsWorld2D<PhysicsWorld2D>(engine, "PhysicsWorld2D");
    CollectMembers_PhysicsWorld2D(members);
    RegisterMembers(engine, "PhysicsWorld2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_PhysicsWorld2D
        REGISTER_CLASS_MANUAL_PART_PhysicsWorld2D();
    #endif
}

// explicit RigidBody2D::RigidBody2D(Context* context)
static RigidBody2D* RigidBody2D__RigidBody2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new RigidBody2D(context);
}

// class RigidBody2D | File: ../Urho2D/RigidBody2D.h
static void Register_RigidBody2D(asIScriptEngine* engine)
{
    // explicit RigidBody2D::RigidBody2D(Context* context)
    engine->RegisterObjectBehaviour("RigidBody2D", asBEHAVE_FACTORY, "RigidBody2D@+ f()", AS_FUNCTION(RigidBody2D__RigidBody2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, RigidBody2D>(engine, "Component", "RigidBody2D");
    RegisterSubclass<Animatable, RigidBody2D>(engine, "Animatable", "RigidBody2D");
    RegisterSubclass<Serializable, RigidBody2D>(engine, "Serializable", "RigidBody2D");
    RegisterSubclass<Object, RigidBody2D>(engine, "Object", "RigidBody2D");
    RegisterSubclass<RefCounted, RigidBody2D>(engine, "RefCounted", "RigidBody2D");

    MemberCollection members;
    RegisterMembers_RigidBody2D<RigidBody2D>(engine, "RigidBody2D");
    CollectMembers_RigidBody2D(members);
    RegisterMembers(engine, "RigidBody2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_RigidBody2D
        REGISTER_CLASS_MANUAL_PART_RigidBody2D();
    #endif
}

// explicit TileMap2D::TileMap2D(Context* context)
static TileMap2D* TileMap2D__TileMap2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new TileMap2D(context);
}

// class TileMap2D | File: ../Urho2D/TileMap2D.h
static void Register_TileMap2D(asIScriptEngine* engine)
{
    // explicit TileMap2D::TileMap2D(Context* context)
    engine->RegisterObjectBehaviour("TileMap2D", asBEHAVE_FACTORY, "TileMap2D@+ f()", AS_FUNCTION(TileMap2D__TileMap2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, TileMap2D>(engine, "Component", "TileMap2D");
    RegisterSubclass<Animatable, TileMap2D>(engine, "Animatable", "TileMap2D");
    RegisterSubclass<Serializable, TileMap2D>(engine, "Serializable", "TileMap2D");
    RegisterSubclass<Object, TileMap2D>(engine, "Object", "TileMap2D");
    RegisterSubclass<RefCounted, TileMap2D>(engine, "RefCounted", "TileMap2D");

    MemberCollection members;
    RegisterMembers_TileMap2D<TileMap2D>(engine, "TileMap2D");
    CollectMembers_TileMap2D(members);
    RegisterMembers(engine, "TileMap2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TileMap2D
        REGISTER_CLASS_MANUAL_PART_TileMap2D();
    #endif
}

// explicit TileMapLayer2D::TileMapLayer2D(Context* context)
static TileMapLayer2D* TileMapLayer2D__TileMapLayer2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new TileMapLayer2D(context);
}

// class TileMapLayer2D | File: ../Urho2D/TileMapLayer2D.h
static void Register_TileMapLayer2D(asIScriptEngine* engine)
{
    // explicit TileMapLayer2D::TileMapLayer2D(Context* context)
    engine->RegisterObjectBehaviour("TileMapLayer2D", asBEHAVE_FACTORY, "TileMapLayer2D@+ f()", AS_FUNCTION(TileMapLayer2D__TileMapLayer2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Component, TileMapLayer2D>(engine, "Component", "TileMapLayer2D");
    RegisterSubclass<Animatable, TileMapLayer2D>(engine, "Animatable", "TileMapLayer2D");
    RegisterSubclass<Serializable, TileMapLayer2D>(engine, "Serializable", "TileMapLayer2D");
    RegisterSubclass<Object, TileMapLayer2D>(engine, "Object", "TileMapLayer2D");
    RegisterSubclass<RefCounted, TileMapLayer2D>(engine, "RefCounted", "TileMapLayer2D");

    MemberCollection members;
    RegisterMembers_TileMapLayer2D<TileMapLayer2D>(engine, "TileMapLayer2D");
    CollectMembers_TileMapLayer2D(members);
    RegisterMembers(engine, "TileMapLayer2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TileMapLayer2D
        REGISTER_CLASS_MANUAL_PART_TileMapLayer2D();
    #endif
}

#endif // def URHO3D_URHO2D

// explicit BillboardSet::BillboardSet(Context* context)
static BillboardSet* BillboardSet__BillboardSet_Contextstar()
{
    Context* context = GetScriptContext();
    return new BillboardSet(context);
}

// class BillboardSet | File: ../Graphics/BillboardSet.h
static void Register_BillboardSet(asIScriptEngine* engine)
{
    // explicit BillboardSet::BillboardSet(Context* context)
    engine->RegisterObjectBehaviour("BillboardSet", asBEHAVE_FACTORY, "BillboardSet@+ f()", AS_FUNCTION(BillboardSet__BillboardSet_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Drawable, BillboardSet>(engine, "Drawable", "BillboardSet");
    RegisterSubclass<Component, BillboardSet>(engine, "Component", "BillboardSet");
    RegisterSubclass<Animatable, BillboardSet>(engine, "Animatable", "BillboardSet");
    RegisterSubclass<Serializable, BillboardSet>(engine, "Serializable", "BillboardSet");
    RegisterSubclass<Object, BillboardSet>(engine, "Object", "BillboardSet");
    RegisterSubclass<RefCounted, BillboardSet>(engine, "RefCounted", "BillboardSet");

    MemberCollection members;
    RegisterMembers_BillboardSet<BillboardSet>(engine, "BillboardSet");
    CollectMembers_BillboardSet(members);
    RegisterMembers(engine, "BillboardSet", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_BillboardSet
        REGISTER_CLASS_MANUAL_PART_BillboardSet();
    #endif
}

// explicit Button::Button(Context* context)
static Button* Button__Button_Contextstar()
{
    Context* context = GetScriptContext();
    return new Button(context);
}

// class Button | File: ../UI/Button.h
static void Register_Button(asIScriptEngine* engine)
{
    // explicit Button::Button(Context* context)
    engine->RegisterObjectBehaviour("Button", asBEHAVE_FACTORY, "Button@+ f()", AS_FUNCTION(Button__Button_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<BorderImage, Button>(engine, "BorderImage", "Button");
    RegisterSubclass<UIElement, Button>(engine, "UIElement", "Button");
    RegisterSubclass<Animatable, Button>(engine, "Animatable", "Button");
    RegisterSubclass<Serializable, Button>(engine, "Serializable", "Button");
    RegisterSubclass<Object, Button>(engine, "Object", "Button");
    RegisterSubclass<RefCounted, Button>(engine, "RefCounted", "Button");

    MemberCollection members;
    RegisterMembers_Button<Button>(engine, "Button");
    CollectMembers_Button(members);
    RegisterMembers(engine, "Button", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Button
        REGISTER_CLASS_MANUAL_PART_Button();
    #endif

    // bool UIElement::LoadXML(const XMLElement& source) override
    engine->RegisterObjectMethod("Button", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Button, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);

    // bool UIElement::LoadXML(Deserializer& source)
    engine->RegisterObjectMethod("Button", "bool LoadXML(Deserializer&)", AS_METHODPR(Button, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);

    // bool UIElement::SaveXML(Serializer& dest, const String& indentation = "\t") const
    engine->RegisterObjectMethod("Button", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(Button, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
}

// explicit CheckBox::CheckBox(Context* context)
static CheckBox* CheckBox__CheckBox_Contextstar()
{
    Context* context = GetScriptContext();
    return new CheckBox(context);
}

// class CheckBox | File: ../UI/CheckBox.h
static void Register_CheckBox(asIScriptEngine* engine)
{
    // explicit CheckBox::CheckBox(Context* context)
    engine->RegisterObjectBehaviour("CheckBox", asBEHAVE_FACTORY, "CheckBox@+ f()", AS_FUNCTION(CheckBox__CheckBox_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<BorderImage, CheckBox>(engine, "BorderImage", "CheckBox");
    RegisterSubclass<UIElement, CheckBox>(engine, "UIElement", "CheckBox");
    RegisterSubclass<Animatable, CheckBox>(engine, "Animatable", "CheckBox");
    RegisterSubclass<Serializable, CheckBox>(engine, "Serializable", "CheckBox");
    RegisterSubclass<Object, CheckBox>(engine, "Object", "CheckBox");
    RegisterSubclass<RefCounted, CheckBox>(engine, "RefCounted", "CheckBox");

    MemberCollection members;
    RegisterMembers_CheckBox<CheckBox>(engine, "CheckBox");
    CollectMembers_CheckBox(members);
    RegisterMembers(engine, "CheckBox", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CheckBox
        REGISTER_CLASS_MANUAL_PART_CheckBox();
    #endif
}

// explicit Cursor::Cursor(Context* context)
static Cursor* Cursor__Cursor_Contextstar()
{
    Context* context = GetScriptContext();
    return new Cursor(context);
}

// class Cursor | File: ../UI/Cursor.h
static void Register_Cursor(asIScriptEngine* engine)
{
    // explicit Cursor::Cursor(Context* context)
    engine->RegisterObjectBehaviour("Cursor", asBEHAVE_FACTORY, "Cursor@+ f()", AS_FUNCTION(Cursor__Cursor_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<BorderImage, Cursor>(engine, "BorderImage", "Cursor");
    RegisterSubclass<UIElement, Cursor>(engine, "UIElement", "Cursor");
    RegisterSubclass<Animatable, Cursor>(engine, "Animatable", "Cursor");
    RegisterSubclass<Serializable, Cursor>(engine, "Serializable", "Cursor");
    RegisterSubclass<Object, Cursor>(engine, "Object", "Cursor");
    RegisterSubclass<RefCounted, Cursor>(engine, "RefCounted", "Cursor");

    MemberCollection members;
    RegisterMembers_Cursor<Cursor>(engine, "Cursor");
    CollectMembers_Cursor(members);
    RegisterMembers(engine, "Cursor", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Cursor
        REGISTER_CLASS_MANUAL_PART_Cursor();
    #endif
}

// explicit CustomGeometry::CustomGeometry(Context* context)
static CustomGeometry* CustomGeometry__CustomGeometry_Contextstar()
{
    Context* context = GetScriptContext();
    return new CustomGeometry(context);
}

// class CustomGeometry | File: ../Graphics/CustomGeometry.h
static void Register_CustomGeometry(asIScriptEngine* engine)
{
    // explicit CustomGeometry::CustomGeometry(Context* context)
    engine->RegisterObjectBehaviour("CustomGeometry", asBEHAVE_FACTORY, "CustomGeometry@+ f()", AS_FUNCTION(CustomGeometry__CustomGeometry_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Drawable, CustomGeometry>(engine, "Drawable", "CustomGeometry");
    RegisterSubclass<Component, CustomGeometry>(engine, "Component", "CustomGeometry");
    RegisterSubclass<Animatable, CustomGeometry>(engine, "Animatable", "CustomGeometry");
    RegisterSubclass<Serializable, CustomGeometry>(engine, "Serializable", "CustomGeometry");
    RegisterSubclass<Object, CustomGeometry>(engine, "Object", "CustomGeometry");
    RegisterSubclass<RefCounted, CustomGeometry>(engine, "RefCounted", "CustomGeometry");

    MemberCollection members;
    RegisterMembers_CustomGeometry<CustomGeometry>(engine, "CustomGeometry");
    CollectMembers_CustomGeometry(members);
    RegisterMembers(engine, "CustomGeometry", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CustomGeometry
        REGISTER_CLASS_MANUAL_PART_CustomGeometry();
    #endif
}

// explicit DecalSet::DecalSet(Context* context)
static DecalSet* DecalSet__DecalSet_Contextstar()
{
    Context* context = GetScriptContext();
    return new DecalSet(context);
}

// class DecalSet | File: ../Graphics/DecalSet.h
static void Register_DecalSet(asIScriptEngine* engine)
{
    // explicit DecalSet::DecalSet(Context* context)
    engine->RegisterObjectBehaviour("DecalSet", asBEHAVE_FACTORY, "DecalSet@+ f()", AS_FUNCTION(DecalSet__DecalSet_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Drawable, DecalSet>(engine, "Drawable", "DecalSet");
    RegisterSubclass<Component, DecalSet>(engine, "Component", "DecalSet");
    RegisterSubclass<Animatable, DecalSet>(engine, "Animatable", "DecalSet");
    RegisterSubclass<Serializable, DecalSet>(engine, "Serializable", "DecalSet");
    RegisterSubclass<Object, DecalSet>(engine, "Object", "DecalSet");
    RegisterSubclass<RefCounted, DecalSet>(engine, "RefCounted", "DecalSet");

    MemberCollection members;
    RegisterMembers_DecalSet<DecalSet>(engine, "DecalSet");
    CollectMembers_DecalSet(members);
    RegisterMembers(engine, "DecalSet", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_DecalSet
        REGISTER_CLASS_MANUAL_PART_DecalSet();
    #endif
}

// explicit Light::Light(Context* context)
static Light* Light__Light_Contextstar()
{
    Context* context = GetScriptContext();
    return new Light(context);
}

// class Light | File: ../Graphics/Light.h
static void Register_Light(asIScriptEngine* engine)
{
    // explicit Light::Light(Context* context)
    engine->RegisterObjectBehaviour("Light", asBEHAVE_FACTORY, "Light@+ f()", AS_FUNCTION(Light__Light_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Drawable, Light>(engine, "Drawable", "Light");
    RegisterSubclass<Component, Light>(engine, "Component", "Light");
    RegisterSubclass<Animatable, Light>(engine, "Animatable", "Light");
    RegisterSubclass<Serializable, Light>(engine, "Serializable", "Light");
    RegisterSubclass<Object, Light>(engine, "Object", "Light");
    RegisterSubclass<RefCounted, Light>(engine, "RefCounted", "Light");

    MemberCollection members;
    RegisterMembers_Light<Light>(engine, "Light");
    CollectMembers_Light(members);
    RegisterMembers(engine, "Light", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Light
        REGISTER_CLASS_MANUAL_PART_Light();
    #endif
}

// explicit LineEdit::LineEdit(Context* context)
static LineEdit* LineEdit__LineEdit_Contextstar()
{
    Context* context = GetScriptContext();
    return new LineEdit(context);
}

// class LineEdit | File: ../UI/LineEdit.h
static void Register_LineEdit(asIScriptEngine* engine)
{
    // explicit LineEdit::LineEdit(Context* context)
    engine->RegisterObjectBehaviour("LineEdit", asBEHAVE_FACTORY, "LineEdit@+ f()", AS_FUNCTION(LineEdit__LineEdit_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<BorderImage, LineEdit>(engine, "BorderImage", "LineEdit");
    RegisterSubclass<UIElement, LineEdit>(engine, "UIElement", "LineEdit");
    RegisterSubclass<Animatable, LineEdit>(engine, "Animatable", "LineEdit");
    RegisterSubclass<Serializable, LineEdit>(engine, "Serializable", "LineEdit");
    RegisterSubclass<Object, LineEdit>(engine, "Object", "LineEdit");
    RegisterSubclass<RefCounted, LineEdit>(engine, "RefCounted", "LineEdit");

    MemberCollection members;
    RegisterMembers_LineEdit<LineEdit>(engine, "LineEdit");
    CollectMembers_LineEdit(members);
    RegisterMembers(engine, "LineEdit", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_LineEdit
        REGISTER_CLASS_MANUAL_PART_LineEdit();
    #endif
}

// explicit ListView::ListView(Context* context)
static ListView* ListView__ListView_Contextstar()
{
    Context* context = GetScriptContext();
    return new ListView(context);
}

// class ListView | File: ../UI/ListView.h
static void Register_ListView(asIScriptEngine* engine)
{
    // explicit ListView::ListView(Context* context)
    engine->RegisterObjectBehaviour("ListView", asBEHAVE_FACTORY, "ListView@+ f()", AS_FUNCTION(ListView__ListView_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<ScrollView, ListView>(engine, "ScrollView", "ListView");
    RegisterSubclass<UIElement, ListView>(engine, "UIElement", "ListView");
    RegisterSubclass<Animatable, ListView>(engine, "Animatable", "ListView");
    RegisterSubclass<Serializable, ListView>(engine, "Serializable", "ListView");
    RegisterSubclass<Object, ListView>(engine, "Object", "ListView");
    RegisterSubclass<RefCounted, ListView>(engine, "RefCounted", "ListView");

    MemberCollection members;
    RegisterMembers_ListView<ListView>(engine, "ListView");
    CollectMembers_ListView(members);
    RegisterMembers(engine, "ListView", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ListView
        REGISTER_CLASS_MANUAL_PART_ListView();
    #endif
}

// explicit ProgressBar::ProgressBar(Context* context)
static ProgressBar* ProgressBar__ProgressBar_Contextstar()
{
    Context* context = GetScriptContext();
    return new ProgressBar(context);
}

// class ProgressBar | File: ../UI/ProgressBar.h
static void Register_ProgressBar(asIScriptEngine* engine)
{
    // explicit ProgressBar::ProgressBar(Context* context)
    engine->RegisterObjectBehaviour("ProgressBar", asBEHAVE_FACTORY, "ProgressBar@+ f()", AS_FUNCTION(ProgressBar__ProgressBar_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<BorderImage, ProgressBar>(engine, "BorderImage", "ProgressBar");
    RegisterSubclass<UIElement, ProgressBar>(engine, "UIElement", "ProgressBar");
    RegisterSubclass<Animatable, ProgressBar>(engine, "Animatable", "ProgressBar");
    RegisterSubclass<Serializable, ProgressBar>(engine, "Serializable", "ProgressBar");
    RegisterSubclass<Object, ProgressBar>(engine, "Object", "ProgressBar");
    RegisterSubclass<RefCounted, ProgressBar>(engine, "RefCounted", "ProgressBar");

    MemberCollection members;
    RegisterMembers_ProgressBar<ProgressBar>(engine, "ProgressBar");
    CollectMembers_ProgressBar(members);
    RegisterMembers(engine, "ProgressBar", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ProgressBar
        REGISTER_CLASS_MANUAL_PART_ProgressBar();
    #endif
}

// explicit RibbonTrail::RibbonTrail(Context* context)
static RibbonTrail* RibbonTrail__RibbonTrail_Contextstar()
{
    Context* context = GetScriptContext();
    return new RibbonTrail(context);
}

// class RibbonTrail | File: ../Graphics/RibbonTrail.h
static void Register_RibbonTrail(asIScriptEngine* engine)
{
    // explicit RibbonTrail::RibbonTrail(Context* context)
    engine->RegisterObjectBehaviour("RibbonTrail", asBEHAVE_FACTORY, "RibbonTrail@+ f()", AS_FUNCTION(RibbonTrail__RibbonTrail_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Drawable, RibbonTrail>(engine, "Drawable", "RibbonTrail");
    RegisterSubclass<Component, RibbonTrail>(engine, "Component", "RibbonTrail");
    RegisterSubclass<Animatable, RibbonTrail>(engine, "Animatable", "RibbonTrail");
    RegisterSubclass<Serializable, RibbonTrail>(engine, "Serializable", "RibbonTrail");
    RegisterSubclass<Object, RibbonTrail>(engine, "Object", "RibbonTrail");
    RegisterSubclass<RefCounted, RibbonTrail>(engine, "RefCounted", "RibbonTrail");

    MemberCollection members;
    RegisterMembers_RibbonTrail<RibbonTrail>(engine, "RibbonTrail");
    CollectMembers_RibbonTrail(members);
    RegisterMembers(engine, "RibbonTrail", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_RibbonTrail
        REGISTER_CLASS_MANUAL_PART_RibbonTrail();
    #endif
}

// explicit ScrollBar::ScrollBar(Context* context)
static ScrollBar* ScrollBar__ScrollBar_Contextstar()
{
    Context* context = GetScriptContext();
    return new ScrollBar(context);
}

// class ScrollBar | File: ../UI/ScrollBar.h
static void Register_ScrollBar(asIScriptEngine* engine)
{
    // explicit ScrollBar::ScrollBar(Context* context)
    engine->RegisterObjectBehaviour("ScrollBar", asBEHAVE_FACTORY, "ScrollBar@+ f()", AS_FUNCTION(ScrollBar__ScrollBar_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<BorderImage, ScrollBar>(engine, "BorderImage", "ScrollBar");
    RegisterSubclass<UIElement, ScrollBar>(engine, "UIElement", "ScrollBar");
    RegisterSubclass<Animatable, ScrollBar>(engine, "Animatable", "ScrollBar");
    RegisterSubclass<Serializable, ScrollBar>(engine, "Serializable", "ScrollBar");
    RegisterSubclass<Object, ScrollBar>(engine, "Object", "ScrollBar");
    RegisterSubclass<RefCounted, ScrollBar>(engine, "RefCounted", "ScrollBar");

    MemberCollection members;
    RegisterMembers_ScrollBar<ScrollBar>(engine, "ScrollBar");
    CollectMembers_ScrollBar(members);
    RegisterMembers(engine, "ScrollBar", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ScrollBar
        REGISTER_CLASS_MANUAL_PART_ScrollBar();
    #endif
}

// explicit Slider::Slider(Context* context)
static Slider* Slider__Slider_Contextstar()
{
    Context* context = GetScriptContext();
    return new Slider(context);
}

// class Slider | File: ../UI/Slider.h
static void Register_Slider(asIScriptEngine* engine)
{
    // explicit Slider::Slider(Context* context)
    engine->RegisterObjectBehaviour("Slider", asBEHAVE_FACTORY, "Slider@+ f()", AS_FUNCTION(Slider__Slider_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<BorderImage, Slider>(engine, "BorderImage", "Slider");
    RegisterSubclass<UIElement, Slider>(engine, "UIElement", "Slider");
    RegisterSubclass<Animatable, Slider>(engine, "Animatable", "Slider");
    RegisterSubclass<Serializable, Slider>(engine, "Serializable", "Slider");
    RegisterSubclass<Object, Slider>(engine, "Object", "Slider");
    RegisterSubclass<RefCounted, Slider>(engine, "RefCounted", "Slider");

    MemberCollection members;
    RegisterMembers_Slider<Slider>(engine, "Slider");
    CollectMembers_Slider(members);
    RegisterMembers(engine, "Slider", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Slider
        REGISTER_CLASS_MANUAL_PART_Slider();
    #endif
}

// explicit SoundSource3D::SoundSource3D(Context* context)
static SoundSource3D* SoundSource3D__SoundSource3D_Contextstar()
{
    Context* context = GetScriptContext();
    return new SoundSource3D(context);
}

// class SoundSource3D | File: ../Audio/SoundSource3D.h
static void Register_SoundSource3D(asIScriptEngine* engine)
{
    // explicit SoundSource3D::SoundSource3D(Context* context)
    engine->RegisterObjectBehaviour("SoundSource3D", asBEHAVE_FACTORY, "SoundSource3D@+ f()", AS_FUNCTION(SoundSource3D__SoundSource3D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<SoundSource, SoundSource3D>(engine, "SoundSource", "SoundSource3D");
    RegisterSubclass<Component, SoundSource3D>(engine, "Component", "SoundSource3D");
    RegisterSubclass<Animatable, SoundSource3D>(engine, "Animatable", "SoundSource3D");
    RegisterSubclass<Serializable, SoundSource3D>(engine, "Serializable", "SoundSource3D");
    RegisterSubclass<Object, SoundSource3D>(engine, "Object", "SoundSource3D");
    RegisterSubclass<RefCounted, SoundSource3D>(engine, "RefCounted", "SoundSource3D");

    MemberCollection members;
    RegisterMembers_SoundSource3D<SoundSource3D>(engine, "SoundSource3D");
    CollectMembers_SoundSource3D(members);
    RegisterMembers(engine, "SoundSource3D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_SoundSource3D
        REGISTER_CLASS_MANUAL_PART_SoundSource3D();
    #endif
}

// explicit StaticModel::StaticModel(Context* context)
static StaticModel* StaticModel__StaticModel_Contextstar()
{
    Context* context = GetScriptContext();
    return new StaticModel(context);
}

// class StaticModel | File: ../Graphics/StaticModel.h
static void Register_StaticModel(asIScriptEngine* engine)
{
    // explicit StaticModel::StaticModel(Context* context)
    engine->RegisterObjectBehaviour("StaticModel", asBEHAVE_FACTORY, "StaticModel@+ f()", AS_FUNCTION(StaticModel__StaticModel_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Drawable, StaticModel>(engine, "Drawable", "StaticModel");
    RegisterSubclass<Component, StaticModel>(engine, "Component", "StaticModel");
    RegisterSubclass<Animatable, StaticModel>(engine, "Animatable", "StaticModel");
    RegisterSubclass<Serializable, StaticModel>(engine, "Serializable", "StaticModel");
    RegisterSubclass<Object, StaticModel>(engine, "Object", "StaticModel");
    RegisterSubclass<RefCounted, StaticModel>(engine, "RefCounted", "StaticModel");

    MemberCollection members;
    RegisterMembers_StaticModel<StaticModel>(engine, "StaticModel");
    CollectMembers_StaticModel(members);
    RegisterMembers(engine, "StaticModel", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_StaticModel
        REGISTER_CLASS_MANUAL_PART_StaticModel();
    #endif
}

// explicit TerrainPatch::TerrainPatch(Context* context)
static TerrainPatch* TerrainPatch__TerrainPatch_Contextstar()
{
    Context* context = GetScriptContext();
    return new TerrainPatch(context);
}

// class TerrainPatch | File: ../Graphics/TerrainPatch.h
static void Register_TerrainPatch(asIScriptEngine* engine)
{
    // explicit TerrainPatch::TerrainPatch(Context* context)
    engine->RegisterObjectBehaviour("TerrainPatch", asBEHAVE_FACTORY, "TerrainPatch@+ f()", AS_FUNCTION(TerrainPatch__TerrainPatch_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Drawable, TerrainPatch>(engine, "Drawable", "TerrainPatch");
    RegisterSubclass<Component, TerrainPatch>(engine, "Component", "TerrainPatch");
    RegisterSubclass<Animatable, TerrainPatch>(engine, "Animatable", "TerrainPatch");
    RegisterSubclass<Serializable, TerrainPatch>(engine, "Serializable", "TerrainPatch");
    RegisterSubclass<Object, TerrainPatch>(engine, "Object", "TerrainPatch");
    RegisterSubclass<RefCounted, TerrainPatch>(engine, "RefCounted", "TerrainPatch");

    MemberCollection members;
    RegisterMembers_TerrainPatch<TerrainPatch>(engine, "TerrainPatch");
    CollectMembers_TerrainPatch(members);
    RegisterMembers(engine, "TerrainPatch", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_TerrainPatch
        REGISTER_CLASS_MANUAL_PART_TerrainPatch();
    #endif
}

// explicit Text::Text(Context* context)
static Text* Text__Text_Contextstar()
{
    Context* context = GetScriptContext();
    return new Text(context);
}

// class Text | File: ../UI/Text.h
static void Register_Text(asIScriptEngine* engine)
{
    // explicit Text::Text(Context* context)
    engine->RegisterObjectBehaviour("Text", asBEHAVE_FACTORY, "Text@+ f()", AS_FUNCTION(Text__Text_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<UISelectable, Text>(engine, "UISelectable", "Text");
    RegisterSubclass<UIElement, Text>(engine, "UIElement", "Text");
    RegisterSubclass<Animatable, Text>(engine, "Animatable", "Text");
    RegisterSubclass<Serializable, Text>(engine, "Serializable", "Text");
    RegisterSubclass<Object, Text>(engine, "Object", "Text");
    RegisterSubclass<RefCounted, Text>(engine, "RefCounted", "Text");

    MemberCollection members;
    RegisterMembers_Text<Text>(engine, "Text");
    CollectMembers_Text(members);
    RegisterMembers(engine, "Text", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Text
        REGISTER_CLASS_MANUAL_PART_Text();
    #endif
}

// explicit Text3D::Text3D(Context* context)
static Text3D* Text3D__Text3D_Contextstar()
{
    Context* context = GetScriptContext();
    return new Text3D(context);
}

// class Text3D | File: ../UI/Text3D.h
static void Register_Text3D(asIScriptEngine* engine)
{
    // explicit Text3D::Text3D(Context* context)
    engine->RegisterObjectBehaviour("Text3D", asBEHAVE_FACTORY, "Text3D@+ f()", AS_FUNCTION(Text3D__Text3D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Drawable, Text3D>(engine, "Drawable", "Text3D");
    RegisterSubclass<Component, Text3D>(engine, "Component", "Text3D");
    RegisterSubclass<Animatable, Text3D>(engine, "Animatable", "Text3D");
    RegisterSubclass<Serializable, Text3D>(engine, "Serializable", "Text3D");
    RegisterSubclass<Object, Text3D>(engine, "Object", "Text3D");
    RegisterSubclass<RefCounted, Text3D>(engine, "RefCounted", "Text3D");

    MemberCollection members;
    RegisterMembers_Text3D<Text3D>(engine, "Text3D");
    CollectMembers_Text3D(members);
    RegisterMembers(engine, "Text3D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Text3D
        REGISTER_CLASS_MANUAL_PART_Text3D();
    #endif
}

// explicit Window::Window(Context* context)
static Window* Window__Window_Contextstar()
{
    Context* context = GetScriptContext();
    return new Window(context);
}

// class Window | File: ../UI/Window.h
static void Register_Window(asIScriptEngine* engine)
{
    // explicit Window::Window(Context* context)
    engine->RegisterObjectBehaviour("Window", asBEHAVE_FACTORY, "Window@+ f()", AS_FUNCTION(Window__Window_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<BorderImage, Window>(engine, "BorderImage", "Window");
    RegisterSubclass<UIElement, Window>(engine, "UIElement", "Window");
    RegisterSubclass<Animatable, Window>(engine, "Animatable", "Window");
    RegisterSubclass<Serializable, Window>(engine, "Serializable", "Window");
    RegisterSubclass<Object, Window>(engine, "Object", "Window");
    RegisterSubclass<RefCounted, Window>(engine, "RefCounted", "Window");

    MemberCollection members;
    RegisterMembers_Window<Window>(engine, "Window");
    CollectMembers_Window(members);
    RegisterMembers(engine, "Window", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Window
        REGISTER_CLASS_MANUAL_PART_Window();
    #endif
}

// explicit Zone::Zone(Context* context)
static Zone* Zone__Zone_Contextstar()
{
    Context* context = GetScriptContext();
    return new Zone(context);
}

// class Zone | File: ../Graphics/Zone.h
static void Register_Zone(asIScriptEngine* engine)
{
    // explicit Zone::Zone(Context* context)
    engine->RegisterObjectBehaviour("Zone", asBEHAVE_FACTORY, "Zone@+ f()", AS_FUNCTION(Zone__Zone_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Drawable, Zone>(engine, "Drawable", "Zone");
    RegisterSubclass<Component, Zone>(engine, "Component", "Zone");
    RegisterSubclass<Animatable, Zone>(engine, "Animatable", "Zone");
    RegisterSubclass<Serializable, Zone>(engine, "Serializable", "Zone");
    RegisterSubclass<Object, Zone>(engine, "Object", "Zone");
    RegisterSubclass<RefCounted, Zone>(engine, "RefCounted", "Zone");

    MemberCollection members;
    RegisterMembers_Zone<Zone>(engine, "Zone");
    CollectMembers_Zone(members);
    RegisterMembers(engine, "Zone", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Zone
        REGISTER_CLASS_MANUAL_PART_Zone();
    #endif
}

#ifdef URHO3D_NAVIGATION

// explicit DynamicNavigationMesh::DynamicNavigationMesh(Context* context)
static DynamicNavigationMesh* DynamicNavigationMesh__DynamicNavigationMesh_Contextstar()
{
    Context* context = GetScriptContext();
    return new DynamicNavigationMesh(context);
}

// class DynamicNavigationMesh | File: ../Navigation/DynamicNavigationMesh.h
static void Register_DynamicNavigationMesh(asIScriptEngine* engine)
{
    // explicit DynamicNavigationMesh::DynamicNavigationMesh(Context* context)
    engine->RegisterObjectBehaviour("DynamicNavigationMesh", asBEHAVE_FACTORY, "DynamicNavigationMesh@+ f()", AS_FUNCTION(DynamicNavigationMesh__DynamicNavigationMesh_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<NavigationMesh, DynamicNavigationMesh>(engine, "NavigationMesh", "DynamicNavigationMesh");
    RegisterSubclass<Component, DynamicNavigationMesh>(engine, "Component", "DynamicNavigationMesh");
    RegisterSubclass<Animatable, DynamicNavigationMesh>(engine, "Animatable", "DynamicNavigationMesh");
    RegisterSubclass<Serializable, DynamicNavigationMesh>(engine, "Serializable", "DynamicNavigationMesh");
    RegisterSubclass<Object, DynamicNavigationMesh>(engine, "Object", "DynamicNavigationMesh");
    RegisterSubclass<RefCounted, DynamicNavigationMesh>(engine, "RefCounted", "DynamicNavigationMesh");

    MemberCollection members;
    RegisterMembers_DynamicNavigationMesh<DynamicNavigationMesh>(engine, "DynamicNavigationMesh");
    CollectMembers_DynamicNavigationMesh(members);
    RegisterMembers(engine, "DynamicNavigationMesh", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_DynamicNavigationMesh
        REGISTER_CLASS_MANUAL_PART_DynamicNavigationMesh();
    #endif
}

#endif // def URHO3D_NAVIGATION

#ifdef URHO3D_PHYSICS

// class RaycastVehicle | File: ../Physics/RaycastVehicle.h
static void Register_RaycastVehicle(asIScriptEngine* engine)
{
    // explicit RaycastVehicle::RaycastVehicle(Urho3D::Context* context)
    // Error: type "Urho3D::Context*" can not automatically bind

    RegisterSubclass<LogicComponent, RaycastVehicle>(engine, "LogicComponent", "RaycastVehicle");
    RegisterSubclass<Component, RaycastVehicle>(engine, "Component", "RaycastVehicle");
    RegisterSubclass<Animatable, RaycastVehicle>(engine, "Animatable", "RaycastVehicle");
    RegisterSubclass<Serializable, RaycastVehicle>(engine, "Serializable", "RaycastVehicle");
    RegisterSubclass<Object, RaycastVehicle>(engine, "Object", "RaycastVehicle");
    RegisterSubclass<RefCounted, RaycastVehicle>(engine, "RefCounted", "RaycastVehicle");

    MemberCollection members;
    RegisterMembers_RaycastVehicle<RaycastVehicle>(engine, "RaycastVehicle");
    CollectMembers_RaycastVehicle(members);
    RegisterMembers(engine, "RaycastVehicle", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_RaycastVehicle
        REGISTER_CLASS_MANUAL_PART_RaycastVehicle();
    #endif
}

#endif // def URHO3D_PHYSICS

#ifdef URHO3D_URHO2D

// explicit CollisionBox2D::CollisionBox2D(Context* context)
static CollisionBox2D* CollisionBox2D__CollisionBox2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new CollisionBox2D(context);
}

// class CollisionBox2D | File: ../Urho2D/CollisionBox2D.h
static void Register_CollisionBox2D(asIScriptEngine* engine)
{
    // explicit CollisionBox2D::CollisionBox2D(Context* context)
    engine->RegisterObjectBehaviour("CollisionBox2D", asBEHAVE_FACTORY, "CollisionBox2D@+ f()", AS_FUNCTION(CollisionBox2D__CollisionBox2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<CollisionShape2D, CollisionBox2D>(engine, "CollisionShape2D", "CollisionBox2D");
    RegisterSubclass<Component, CollisionBox2D>(engine, "Component", "CollisionBox2D");
    RegisterSubclass<Animatable, CollisionBox2D>(engine, "Animatable", "CollisionBox2D");
    RegisterSubclass<Serializable, CollisionBox2D>(engine, "Serializable", "CollisionBox2D");
    RegisterSubclass<Object, CollisionBox2D>(engine, "Object", "CollisionBox2D");
    RegisterSubclass<RefCounted, CollisionBox2D>(engine, "RefCounted", "CollisionBox2D");

    MemberCollection members;
    RegisterMembers_CollisionBox2D<CollisionBox2D>(engine, "CollisionBox2D");
    CollectMembers_CollisionBox2D(members);
    RegisterMembers(engine, "CollisionBox2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CollisionBox2D
        REGISTER_CLASS_MANUAL_PART_CollisionBox2D();
    #endif
}

// explicit CollisionChain2D::CollisionChain2D(Context* context)
static CollisionChain2D* CollisionChain2D__CollisionChain2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new CollisionChain2D(context);
}

// class CollisionChain2D | File: ../Urho2D/CollisionChain2D.h
static void Register_CollisionChain2D(asIScriptEngine* engine)
{
    // explicit CollisionChain2D::CollisionChain2D(Context* context)
    engine->RegisterObjectBehaviour("CollisionChain2D", asBEHAVE_FACTORY, "CollisionChain2D@+ f()", AS_FUNCTION(CollisionChain2D__CollisionChain2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<CollisionShape2D, CollisionChain2D>(engine, "CollisionShape2D", "CollisionChain2D");
    RegisterSubclass<Component, CollisionChain2D>(engine, "Component", "CollisionChain2D");
    RegisterSubclass<Animatable, CollisionChain2D>(engine, "Animatable", "CollisionChain2D");
    RegisterSubclass<Serializable, CollisionChain2D>(engine, "Serializable", "CollisionChain2D");
    RegisterSubclass<Object, CollisionChain2D>(engine, "Object", "CollisionChain2D");
    RegisterSubclass<RefCounted, CollisionChain2D>(engine, "RefCounted", "CollisionChain2D");

    MemberCollection members;
    RegisterMembers_CollisionChain2D<CollisionChain2D>(engine, "CollisionChain2D");
    CollectMembers_CollisionChain2D(members);
    RegisterMembers(engine, "CollisionChain2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CollisionChain2D
        REGISTER_CLASS_MANUAL_PART_CollisionChain2D();
    #endif
}

// explicit CollisionCircle2D::CollisionCircle2D(Context* context)
static CollisionCircle2D* CollisionCircle2D__CollisionCircle2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new CollisionCircle2D(context);
}

// class CollisionCircle2D | File: ../Urho2D/CollisionCircle2D.h
static void Register_CollisionCircle2D(asIScriptEngine* engine)
{
    // explicit CollisionCircle2D::CollisionCircle2D(Context* context)
    engine->RegisterObjectBehaviour("CollisionCircle2D", asBEHAVE_FACTORY, "CollisionCircle2D@+ f()", AS_FUNCTION(CollisionCircle2D__CollisionCircle2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<CollisionShape2D, CollisionCircle2D>(engine, "CollisionShape2D", "CollisionCircle2D");
    RegisterSubclass<Component, CollisionCircle2D>(engine, "Component", "CollisionCircle2D");
    RegisterSubclass<Animatable, CollisionCircle2D>(engine, "Animatable", "CollisionCircle2D");
    RegisterSubclass<Serializable, CollisionCircle2D>(engine, "Serializable", "CollisionCircle2D");
    RegisterSubclass<Object, CollisionCircle2D>(engine, "Object", "CollisionCircle2D");
    RegisterSubclass<RefCounted, CollisionCircle2D>(engine, "RefCounted", "CollisionCircle2D");

    MemberCollection members;
    RegisterMembers_CollisionCircle2D<CollisionCircle2D>(engine, "CollisionCircle2D");
    CollectMembers_CollisionCircle2D(members);
    RegisterMembers(engine, "CollisionCircle2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CollisionCircle2D
        REGISTER_CLASS_MANUAL_PART_CollisionCircle2D();
    #endif
}

// explicit CollisionEdge2D::CollisionEdge2D(Context* context)
static CollisionEdge2D* CollisionEdge2D__CollisionEdge2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new CollisionEdge2D(context);
}

// class CollisionEdge2D | File: ../Urho2D/CollisionEdge2D.h
static void Register_CollisionEdge2D(asIScriptEngine* engine)
{
    // explicit CollisionEdge2D::CollisionEdge2D(Context* context)
    engine->RegisterObjectBehaviour("CollisionEdge2D", asBEHAVE_FACTORY, "CollisionEdge2D@+ f()", AS_FUNCTION(CollisionEdge2D__CollisionEdge2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<CollisionShape2D, CollisionEdge2D>(engine, "CollisionShape2D", "CollisionEdge2D");
    RegisterSubclass<Component, CollisionEdge2D>(engine, "Component", "CollisionEdge2D");
    RegisterSubclass<Animatable, CollisionEdge2D>(engine, "Animatable", "CollisionEdge2D");
    RegisterSubclass<Serializable, CollisionEdge2D>(engine, "Serializable", "CollisionEdge2D");
    RegisterSubclass<Object, CollisionEdge2D>(engine, "Object", "CollisionEdge2D");
    RegisterSubclass<RefCounted, CollisionEdge2D>(engine, "RefCounted", "CollisionEdge2D");

    MemberCollection members;
    RegisterMembers_CollisionEdge2D<CollisionEdge2D>(engine, "CollisionEdge2D");
    CollectMembers_CollisionEdge2D(members);
    RegisterMembers(engine, "CollisionEdge2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CollisionEdge2D
        REGISTER_CLASS_MANUAL_PART_CollisionEdge2D();
    #endif
}

// explicit CollisionPolygon2D::CollisionPolygon2D(Context* context)
static CollisionPolygon2D* CollisionPolygon2D__CollisionPolygon2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new CollisionPolygon2D(context);
}

// class CollisionPolygon2D | File: ../Urho2D/CollisionPolygon2D.h
static void Register_CollisionPolygon2D(asIScriptEngine* engine)
{
    // explicit CollisionPolygon2D::CollisionPolygon2D(Context* context)
    engine->RegisterObjectBehaviour("CollisionPolygon2D", asBEHAVE_FACTORY, "CollisionPolygon2D@+ f()", AS_FUNCTION(CollisionPolygon2D__CollisionPolygon2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<CollisionShape2D, CollisionPolygon2D>(engine, "CollisionShape2D", "CollisionPolygon2D");
    RegisterSubclass<Component, CollisionPolygon2D>(engine, "Component", "CollisionPolygon2D");
    RegisterSubclass<Animatable, CollisionPolygon2D>(engine, "Animatable", "CollisionPolygon2D");
    RegisterSubclass<Serializable, CollisionPolygon2D>(engine, "Serializable", "CollisionPolygon2D");
    RegisterSubclass<Object, CollisionPolygon2D>(engine, "Object", "CollisionPolygon2D");
    RegisterSubclass<RefCounted, CollisionPolygon2D>(engine, "RefCounted", "CollisionPolygon2D");

    MemberCollection members;
    RegisterMembers_CollisionPolygon2D<CollisionPolygon2D>(engine, "CollisionPolygon2D");
    CollectMembers_CollisionPolygon2D(members);
    RegisterMembers(engine, "CollisionPolygon2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_CollisionPolygon2D
        REGISTER_CLASS_MANUAL_PART_CollisionPolygon2D();
    #endif
}

// explicit ConstraintDistance2D::ConstraintDistance2D(Context* context)
static ConstraintDistance2D* ConstraintDistance2D__ConstraintDistance2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new ConstraintDistance2D(context);
}

// class ConstraintDistance2D | File: ../Urho2D/ConstraintDistance2D.h
static void Register_ConstraintDistance2D(asIScriptEngine* engine)
{
    // explicit ConstraintDistance2D::ConstraintDistance2D(Context* context)
    engine->RegisterObjectBehaviour("ConstraintDistance2D", asBEHAVE_FACTORY, "ConstraintDistance2D@+ f()", AS_FUNCTION(ConstraintDistance2D__ConstraintDistance2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Constraint2D, ConstraintDistance2D>(engine, "Constraint2D", "ConstraintDistance2D");
    RegisterSubclass<Component, ConstraintDistance2D>(engine, "Component", "ConstraintDistance2D");
    RegisterSubclass<Animatable, ConstraintDistance2D>(engine, "Animatable", "ConstraintDistance2D");
    RegisterSubclass<Serializable, ConstraintDistance2D>(engine, "Serializable", "ConstraintDistance2D");
    RegisterSubclass<Object, ConstraintDistance2D>(engine, "Object", "ConstraintDistance2D");
    RegisterSubclass<RefCounted, ConstraintDistance2D>(engine, "RefCounted", "ConstraintDistance2D");

    MemberCollection members;
    RegisterMembers_ConstraintDistance2D<ConstraintDistance2D>(engine, "ConstraintDistance2D");
    CollectMembers_ConstraintDistance2D(members);
    RegisterMembers(engine, "ConstraintDistance2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ConstraintDistance2D
        REGISTER_CLASS_MANUAL_PART_ConstraintDistance2D();
    #endif
}

// explicit ConstraintFriction2D::ConstraintFriction2D(Context* context)
static ConstraintFriction2D* ConstraintFriction2D__ConstraintFriction2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new ConstraintFriction2D(context);
}

// class ConstraintFriction2D | File: ../Urho2D/ConstraintFriction2D.h
static void Register_ConstraintFriction2D(asIScriptEngine* engine)
{
    // explicit ConstraintFriction2D::ConstraintFriction2D(Context* context)
    engine->RegisterObjectBehaviour("ConstraintFriction2D", asBEHAVE_FACTORY, "ConstraintFriction2D@+ f()", AS_FUNCTION(ConstraintFriction2D__ConstraintFriction2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Constraint2D, ConstraintFriction2D>(engine, "Constraint2D", "ConstraintFriction2D");
    RegisterSubclass<Component, ConstraintFriction2D>(engine, "Component", "ConstraintFriction2D");
    RegisterSubclass<Animatable, ConstraintFriction2D>(engine, "Animatable", "ConstraintFriction2D");
    RegisterSubclass<Serializable, ConstraintFriction2D>(engine, "Serializable", "ConstraintFriction2D");
    RegisterSubclass<Object, ConstraintFriction2D>(engine, "Object", "ConstraintFriction2D");
    RegisterSubclass<RefCounted, ConstraintFriction2D>(engine, "RefCounted", "ConstraintFriction2D");

    MemberCollection members;
    RegisterMembers_ConstraintFriction2D<ConstraintFriction2D>(engine, "ConstraintFriction2D");
    CollectMembers_ConstraintFriction2D(members);
    RegisterMembers(engine, "ConstraintFriction2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ConstraintFriction2D
        REGISTER_CLASS_MANUAL_PART_ConstraintFriction2D();
    #endif
}

// explicit ConstraintGear2D::ConstraintGear2D(Context* context)
static ConstraintGear2D* ConstraintGear2D__ConstraintGear2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new ConstraintGear2D(context);
}

// class ConstraintGear2D | File: ../Urho2D/ConstraintGear2D.h
static void Register_ConstraintGear2D(asIScriptEngine* engine)
{
    // explicit ConstraintGear2D::ConstraintGear2D(Context* context)
    engine->RegisterObjectBehaviour("ConstraintGear2D", asBEHAVE_FACTORY, "ConstraintGear2D@+ f()", AS_FUNCTION(ConstraintGear2D__ConstraintGear2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Constraint2D, ConstraintGear2D>(engine, "Constraint2D", "ConstraintGear2D");
    RegisterSubclass<Component, ConstraintGear2D>(engine, "Component", "ConstraintGear2D");
    RegisterSubclass<Animatable, ConstraintGear2D>(engine, "Animatable", "ConstraintGear2D");
    RegisterSubclass<Serializable, ConstraintGear2D>(engine, "Serializable", "ConstraintGear2D");
    RegisterSubclass<Object, ConstraintGear2D>(engine, "Object", "ConstraintGear2D");
    RegisterSubclass<RefCounted, ConstraintGear2D>(engine, "RefCounted", "ConstraintGear2D");

    MemberCollection members;
    RegisterMembers_ConstraintGear2D<ConstraintGear2D>(engine, "ConstraintGear2D");
    CollectMembers_ConstraintGear2D(members);
    RegisterMembers(engine, "ConstraintGear2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ConstraintGear2D
        REGISTER_CLASS_MANUAL_PART_ConstraintGear2D();
    #endif
}

// explicit ConstraintMotor2D::ConstraintMotor2D(Context* context)
static ConstraintMotor2D* ConstraintMotor2D__ConstraintMotor2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new ConstraintMotor2D(context);
}

// class ConstraintMotor2D | File: ../Urho2D/ConstraintMotor2D.h
static void Register_ConstraintMotor2D(asIScriptEngine* engine)
{
    // explicit ConstraintMotor2D::ConstraintMotor2D(Context* context)
    engine->RegisterObjectBehaviour("ConstraintMotor2D", asBEHAVE_FACTORY, "ConstraintMotor2D@+ f()", AS_FUNCTION(ConstraintMotor2D__ConstraintMotor2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Constraint2D, ConstraintMotor2D>(engine, "Constraint2D", "ConstraintMotor2D");
    RegisterSubclass<Component, ConstraintMotor2D>(engine, "Component", "ConstraintMotor2D");
    RegisterSubclass<Animatable, ConstraintMotor2D>(engine, "Animatable", "ConstraintMotor2D");
    RegisterSubclass<Serializable, ConstraintMotor2D>(engine, "Serializable", "ConstraintMotor2D");
    RegisterSubclass<Object, ConstraintMotor2D>(engine, "Object", "ConstraintMotor2D");
    RegisterSubclass<RefCounted, ConstraintMotor2D>(engine, "RefCounted", "ConstraintMotor2D");

    MemberCollection members;
    RegisterMembers_ConstraintMotor2D<ConstraintMotor2D>(engine, "ConstraintMotor2D");
    CollectMembers_ConstraintMotor2D(members);
    RegisterMembers(engine, "ConstraintMotor2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ConstraintMotor2D
        REGISTER_CLASS_MANUAL_PART_ConstraintMotor2D();
    #endif
}

// explicit ConstraintMouse2D::ConstraintMouse2D(Context* context)
static ConstraintMouse2D* ConstraintMouse2D__ConstraintMouse2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new ConstraintMouse2D(context);
}

// class ConstraintMouse2D | File: ../Urho2D/ConstraintMouse2D.h
static void Register_ConstraintMouse2D(asIScriptEngine* engine)
{
    // explicit ConstraintMouse2D::ConstraintMouse2D(Context* context)
    engine->RegisterObjectBehaviour("ConstraintMouse2D", asBEHAVE_FACTORY, "ConstraintMouse2D@+ f()", AS_FUNCTION(ConstraintMouse2D__ConstraintMouse2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Constraint2D, ConstraintMouse2D>(engine, "Constraint2D", "ConstraintMouse2D");
    RegisterSubclass<Component, ConstraintMouse2D>(engine, "Component", "ConstraintMouse2D");
    RegisterSubclass<Animatable, ConstraintMouse2D>(engine, "Animatable", "ConstraintMouse2D");
    RegisterSubclass<Serializable, ConstraintMouse2D>(engine, "Serializable", "ConstraintMouse2D");
    RegisterSubclass<Object, ConstraintMouse2D>(engine, "Object", "ConstraintMouse2D");
    RegisterSubclass<RefCounted, ConstraintMouse2D>(engine, "RefCounted", "ConstraintMouse2D");

    MemberCollection members;
    RegisterMembers_ConstraintMouse2D<ConstraintMouse2D>(engine, "ConstraintMouse2D");
    CollectMembers_ConstraintMouse2D(members);
    RegisterMembers(engine, "ConstraintMouse2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ConstraintMouse2D
        REGISTER_CLASS_MANUAL_PART_ConstraintMouse2D();
    #endif
}

// explicit ConstraintPrismatic2D::ConstraintPrismatic2D(Context* context)
static ConstraintPrismatic2D* ConstraintPrismatic2D__ConstraintPrismatic2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new ConstraintPrismatic2D(context);
}

// class ConstraintPrismatic2D | File: ../Urho2D/ConstraintPrismatic2D.h
static void Register_ConstraintPrismatic2D(asIScriptEngine* engine)
{
    // explicit ConstraintPrismatic2D::ConstraintPrismatic2D(Context* context)
    engine->RegisterObjectBehaviour("ConstraintPrismatic2D", asBEHAVE_FACTORY, "ConstraintPrismatic2D@+ f()", AS_FUNCTION(ConstraintPrismatic2D__ConstraintPrismatic2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Constraint2D, ConstraintPrismatic2D>(engine, "Constraint2D", "ConstraintPrismatic2D");
    RegisterSubclass<Component, ConstraintPrismatic2D>(engine, "Component", "ConstraintPrismatic2D");
    RegisterSubclass<Animatable, ConstraintPrismatic2D>(engine, "Animatable", "ConstraintPrismatic2D");
    RegisterSubclass<Serializable, ConstraintPrismatic2D>(engine, "Serializable", "ConstraintPrismatic2D");
    RegisterSubclass<Object, ConstraintPrismatic2D>(engine, "Object", "ConstraintPrismatic2D");
    RegisterSubclass<RefCounted, ConstraintPrismatic2D>(engine, "RefCounted", "ConstraintPrismatic2D");

    MemberCollection members;
    RegisterMembers_ConstraintPrismatic2D<ConstraintPrismatic2D>(engine, "ConstraintPrismatic2D");
    CollectMembers_ConstraintPrismatic2D(members);
    RegisterMembers(engine, "ConstraintPrismatic2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ConstraintPrismatic2D
        REGISTER_CLASS_MANUAL_PART_ConstraintPrismatic2D();
    #endif
}

// explicit ConstraintPulley2D::ConstraintPulley2D(Context* context)
static ConstraintPulley2D* ConstraintPulley2D__ConstraintPulley2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new ConstraintPulley2D(context);
}

// class ConstraintPulley2D | File: ../Urho2D/ConstraintPulley2D.h
static void Register_ConstraintPulley2D(asIScriptEngine* engine)
{
    // explicit ConstraintPulley2D::ConstraintPulley2D(Context* context)
    engine->RegisterObjectBehaviour("ConstraintPulley2D", asBEHAVE_FACTORY, "ConstraintPulley2D@+ f()", AS_FUNCTION(ConstraintPulley2D__ConstraintPulley2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Constraint2D, ConstraintPulley2D>(engine, "Constraint2D", "ConstraintPulley2D");
    RegisterSubclass<Component, ConstraintPulley2D>(engine, "Component", "ConstraintPulley2D");
    RegisterSubclass<Animatable, ConstraintPulley2D>(engine, "Animatable", "ConstraintPulley2D");
    RegisterSubclass<Serializable, ConstraintPulley2D>(engine, "Serializable", "ConstraintPulley2D");
    RegisterSubclass<Object, ConstraintPulley2D>(engine, "Object", "ConstraintPulley2D");
    RegisterSubclass<RefCounted, ConstraintPulley2D>(engine, "RefCounted", "ConstraintPulley2D");

    MemberCollection members;
    RegisterMembers_ConstraintPulley2D<ConstraintPulley2D>(engine, "ConstraintPulley2D");
    CollectMembers_ConstraintPulley2D(members);
    RegisterMembers(engine, "ConstraintPulley2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ConstraintPulley2D
        REGISTER_CLASS_MANUAL_PART_ConstraintPulley2D();
    #endif
}

// explicit ConstraintRevolute2D::ConstraintRevolute2D(Context* context)
static ConstraintRevolute2D* ConstraintRevolute2D__ConstraintRevolute2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new ConstraintRevolute2D(context);
}

// class ConstraintRevolute2D | File: ../Urho2D/ConstraintRevolute2D.h
static void Register_ConstraintRevolute2D(asIScriptEngine* engine)
{
    // explicit ConstraintRevolute2D::ConstraintRevolute2D(Context* context)
    engine->RegisterObjectBehaviour("ConstraintRevolute2D", asBEHAVE_FACTORY, "ConstraintRevolute2D@+ f()", AS_FUNCTION(ConstraintRevolute2D__ConstraintRevolute2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Constraint2D, ConstraintRevolute2D>(engine, "Constraint2D", "ConstraintRevolute2D");
    RegisterSubclass<Component, ConstraintRevolute2D>(engine, "Component", "ConstraintRevolute2D");
    RegisterSubclass<Animatable, ConstraintRevolute2D>(engine, "Animatable", "ConstraintRevolute2D");
    RegisterSubclass<Serializable, ConstraintRevolute2D>(engine, "Serializable", "ConstraintRevolute2D");
    RegisterSubclass<Object, ConstraintRevolute2D>(engine, "Object", "ConstraintRevolute2D");
    RegisterSubclass<RefCounted, ConstraintRevolute2D>(engine, "RefCounted", "ConstraintRevolute2D");

    MemberCollection members;
    RegisterMembers_ConstraintRevolute2D<ConstraintRevolute2D>(engine, "ConstraintRevolute2D");
    CollectMembers_ConstraintRevolute2D(members);
    RegisterMembers(engine, "ConstraintRevolute2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ConstraintRevolute2D
        REGISTER_CLASS_MANUAL_PART_ConstraintRevolute2D();
    #endif
}

// explicit ConstraintRope2D::ConstraintRope2D(Context* context)
static ConstraintRope2D* ConstraintRope2D__ConstraintRope2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new ConstraintRope2D(context);
}

// class ConstraintRope2D | File: ../Urho2D/ConstraintRope2D.h
static void Register_ConstraintRope2D(asIScriptEngine* engine)
{
    // explicit ConstraintRope2D::ConstraintRope2D(Context* context)
    engine->RegisterObjectBehaviour("ConstraintRope2D", asBEHAVE_FACTORY, "ConstraintRope2D@+ f()", AS_FUNCTION(ConstraintRope2D__ConstraintRope2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Constraint2D, ConstraintRope2D>(engine, "Constraint2D", "ConstraintRope2D");
    RegisterSubclass<Component, ConstraintRope2D>(engine, "Component", "ConstraintRope2D");
    RegisterSubclass<Animatable, ConstraintRope2D>(engine, "Animatable", "ConstraintRope2D");
    RegisterSubclass<Serializable, ConstraintRope2D>(engine, "Serializable", "ConstraintRope2D");
    RegisterSubclass<Object, ConstraintRope2D>(engine, "Object", "ConstraintRope2D");
    RegisterSubclass<RefCounted, ConstraintRope2D>(engine, "RefCounted", "ConstraintRope2D");

    MemberCollection members;
    RegisterMembers_ConstraintRope2D<ConstraintRope2D>(engine, "ConstraintRope2D");
    CollectMembers_ConstraintRope2D(members);
    RegisterMembers(engine, "ConstraintRope2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ConstraintRope2D
        REGISTER_CLASS_MANUAL_PART_ConstraintRope2D();
    #endif
}

// explicit ConstraintWeld2D::ConstraintWeld2D(Context* context)
static ConstraintWeld2D* ConstraintWeld2D__ConstraintWeld2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new ConstraintWeld2D(context);
}

// class ConstraintWeld2D | File: ../Urho2D/ConstraintWeld2D.h
static void Register_ConstraintWeld2D(asIScriptEngine* engine)
{
    // explicit ConstraintWeld2D::ConstraintWeld2D(Context* context)
    engine->RegisterObjectBehaviour("ConstraintWeld2D", asBEHAVE_FACTORY, "ConstraintWeld2D@+ f()", AS_FUNCTION(ConstraintWeld2D__ConstraintWeld2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Constraint2D, ConstraintWeld2D>(engine, "Constraint2D", "ConstraintWeld2D");
    RegisterSubclass<Component, ConstraintWeld2D>(engine, "Component", "ConstraintWeld2D");
    RegisterSubclass<Animatable, ConstraintWeld2D>(engine, "Animatable", "ConstraintWeld2D");
    RegisterSubclass<Serializable, ConstraintWeld2D>(engine, "Serializable", "ConstraintWeld2D");
    RegisterSubclass<Object, ConstraintWeld2D>(engine, "Object", "ConstraintWeld2D");
    RegisterSubclass<RefCounted, ConstraintWeld2D>(engine, "RefCounted", "ConstraintWeld2D");

    MemberCollection members;
    RegisterMembers_ConstraintWeld2D<ConstraintWeld2D>(engine, "ConstraintWeld2D");
    CollectMembers_ConstraintWeld2D(members);
    RegisterMembers(engine, "ConstraintWeld2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ConstraintWeld2D
        REGISTER_CLASS_MANUAL_PART_ConstraintWeld2D();
    #endif
}

// explicit ConstraintWheel2D::ConstraintWheel2D(Context* context)
static ConstraintWheel2D* ConstraintWheel2D__ConstraintWheel2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new ConstraintWheel2D(context);
}

// class ConstraintWheel2D | File: ../Urho2D/ConstraintWheel2D.h
static void Register_ConstraintWheel2D(asIScriptEngine* engine)
{
    // explicit ConstraintWheel2D::ConstraintWheel2D(Context* context)
    engine->RegisterObjectBehaviour("ConstraintWheel2D", asBEHAVE_FACTORY, "ConstraintWheel2D@+ f()", AS_FUNCTION(ConstraintWheel2D__ConstraintWheel2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Constraint2D, ConstraintWheel2D>(engine, "Constraint2D", "ConstraintWheel2D");
    RegisterSubclass<Component, ConstraintWheel2D>(engine, "Component", "ConstraintWheel2D");
    RegisterSubclass<Animatable, ConstraintWheel2D>(engine, "Animatable", "ConstraintWheel2D");
    RegisterSubclass<Serializable, ConstraintWheel2D>(engine, "Serializable", "ConstraintWheel2D");
    RegisterSubclass<Object, ConstraintWheel2D>(engine, "Object", "ConstraintWheel2D");
    RegisterSubclass<RefCounted, ConstraintWheel2D>(engine, "RefCounted", "ConstraintWheel2D");

    MemberCollection members;
    RegisterMembers_ConstraintWheel2D<ConstraintWheel2D>(engine, "ConstraintWheel2D");
    CollectMembers_ConstraintWheel2D(members);
    RegisterMembers(engine, "ConstraintWheel2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ConstraintWheel2D
        REGISTER_CLASS_MANUAL_PART_ConstraintWheel2D();
    #endif
}

// class Drawable2D | File: ../Urho2D/Drawable2D.h
static void Register_Drawable2D(asIScriptEngine* engine)
{
    RegisterSubclass<Drawable, Drawable2D>(engine, "Drawable", "Drawable2D");
    RegisterSubclass<Component, Drawable2D>(engine, "Component", "Drawable2D");
    RegisterSubclass<Animatable, Drawable2D>(engine, "Animatable", "Drawable2D");
    RegisterSubclass<Serializable, Drawable2D>(engine, "Serializable", "Drawable2D");
    RegisterSubclass<Object, Drawable2D>(engine, "Object", "Drawable2D");
    RegisterSubclass<RefCounted, Drawable2D>(engine, "RefCounted", "Drawable2D");

    MemberCollection members;
    RegisterMembers_Drawable2D<Drawable2D>(engine, "Drawable2D");
    CollectMembers_Drawable2D(members);
    RegisterMembers(engine, "Drawable2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Drawable2D
        REGISTER_CLASS_MANUAL_PART_Drawable2D();
    #endif

    // virtual void Drawable::Update(const FrameInfo& frame)
    engine->RegisterObjectMethod("Drawable2D", "void Update(const FrameInfo&in)", AS_METHODPR(Drawable2D, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
}

// explicit Renderer2D::Renderer2D(Context* context)
static Renderer2D* Renderer2D__Renderer2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new Renderer2D(context);
}

// class Renderer2D | File: ../Urho2D/Renderer2D.h
static void Register_Renderer2D(asIScriptEngine* engine)
{
    // explicit Renderer2D::Renderer2D(Context* context)
    engine->RegisterObjectBehaviour("Renderer2D", asBEHAVE_FACTORY, "Renderer2D@+ f()", AS_FUNCTION(Renderer2D__Renderer2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Drawable, Renderer2D>(engine, "Drawable", "Renderer2D");
    RegisterSubclass<Component, Renderer2D>(engine, "Component", "Renderer2D");
    RegisterSubclass<Animatable, Renderer2D>(engine, "Animatable", "Renderer2D");
    RegisterSubclass<Serializable, Renderer2D>(engine, "Serializable", "Renderer2D");
    RegisterSubclass<Object, Renderer2D>(engine, "Object", "Renderer2D");
    RegisterSubclass<RefCounted, Renderer2D>(engine, "RefCounted", "Renderer2D");

    MemberCollection members;
    RegisterMembers_Renderer2D<Renderer2D>(engine, "Renderer2D");
    CollectMembers_Renderer2D(members);
    RegisterMembers(engine, "Renderer2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Renderer2D
        REGISTER_CLASS_MANUAL_PART_Renderer2D();
    #endif
}

#endif // def URHO3D_URHO2D

// explicit AnimatedModel::AnimatedModel(Context* context)
static AnimatedModel* AnimatedModel__AnimatedModel_Contextstar()
{
    Context* context = GetScriptContext();
    return new AnimatedModel(context);
}

// class AnimatedModel | File: ../Graphics/AnimatedModel.h
static void Register_AnimatedModel(asIScriptEngine* engine)
{
    // explicit AnimatedModel::AnimatedModel(Context* context)
    engine->RegisterObjectBehaviour("AnimatedModel", asBEHAVE_FACTORY, "AnimatedModel@+ f()", AS_FUNCTION(AnimatedModel__AnimatedModel_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<StaticModel, AnimatedModel>(engine, "StaticModel", "AnimatedModel");
    RegisterSubclass<Drawable, AnimatedModel>(engine, "Drawable", "AnimatedModel");
    RegisterSubclass<Component, AnimatedModel>(engine, "Component", "AnimatedModel");
    RegisterSubclass<Animatable, AnimatedModel>(engine, "Animatable", "AnimatedModel");
    RegisterSubclass<Serializable, AnimatedModel>(engine, "Serializable", "AnimatedModel");
    RegisterSubclass<Object, AnimatedModel>(engine, "Object", "AnimatedModel");
    RegisterSubclass<RefCounted, AnimatedModel>(engine, "RefCounted", "AnimatedModel");

    MemberCollection members;
    RegisterMembers_AnimatedModel<AnimatedModel>(engine, "AnimatedModel");
    CollectMembers_AnimatedModel(members);
    RegisterMembers(engine, "AnimatedModel", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AnimatedModel
        REGISTER_CLASS_MANUAL_PART_AnimatedModel();
    #endif
}

// explicit Menu::Menu(Context* context)
static Menu* Menu__Menu_Contextstar()
{
    Context* context = GetScriptContext();
    return new Menu(context);
}

// class Menu | File: ../UI/Menu.h
static void Register_Menu(asIScriptEngine* engine)
{
    // explicit Menu::Menu(Context* context)
    engine->RegisterObjectBehaviour("Menu", asBEHAVE_FACTORY, "Menu@+ f()", AS_FUNCTION(Menu__Menu_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Button, Menu>(engine, "Button", "Menu");
    RegisterSubclass<BorderImage, Menu>(engine, "BorderImage", "Menu");
    RegisterSubclass<UIElement, Menu>(engine, "UIElement", "Menu");
    RegisterSubclass<Animatable, Menu>(engine, "Animatable", "Menu");
    RegisterSubclass<Serializable, Menu>(engine, "Serializable", "Menu");
    RegisterSubclass<Object, Menu>(engine, "Object", "Menu");
    RegisterSubclass<RefCounted, Menu>(engine, "RefCounted", "Menu");

    MemberCollection members;
    RegisterMembers_Menu<Menu>(engine, "Menu");
    CollectMembers_Menu(members);
    RegisterMembers(engine, "Menu", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Menu
        REGISTER_CLASS_MANUAL_PART_Menu();
    #endif
}

// explicit ParticleEmitter::ParticleEmitter(Context* context)
static ParticleEmitter* ParticleEmitter__ParticleEmitter_Contextstar()
{
    Context* context = GetScriptContext();
    return new ParticleEmitter(context);
}

// class ParticleEmitter | File: ../Graphics/ParticleEmitter.h
static void Register_ParticleEmitter(asIScriptEngine* engine)
{
    // explicit ParticleEmitter::ParticleEmitter(Context* context)
    engine->RegisterObjectBehaviour("ParticleEmitter", asBEHAVE_FACTORY, "ParticleEmitter@+ f()", AS_FUNCTION(ParticleEmitter__ParticleEmitter_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<BillboardSet, ParticleEmitter>(engine, "BillboardSet", "ParticleEmitter");
    RegisterSubclass<Drawable, ParticleEmitter>(engine, "Drawable", "ParticleEmitter");
    RegisterSubclass<Component, ParticleEmitter>(engine, "Component", "ParticleEmitter");
    RegisterSubclass<Animatable, ParticleEmitter>(engine, "Animatable", "ParticleEmitter");
    RegisterSubclass<Serializable, ParticleEmitter>(engine, "Serializable", "ParticleEmitter");
    RegisterSubclass<Object, ParticleEmitter>(engine, "Object", "ParticleEmitter");
    RegisterSubclass<RefCounted, ParticleEmitter>(engine, "RefCounted", "ParticleEmitter");

    MemberCollection members;
    RegisterMembers_ParticleEmitter<ParticleEmitter>(engine, "ParticleEmitter");
    CollectMembers_ParticleEmitter(members);
    RegisterMembers(engine, "ParticleEmitter", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ParticleEmitter
        REGISTER_CLASS_MANUAL_PART_ParticleEmitter();
    #endif
}

// explicit Skybox::Skybox(Context* context)
static Skybox* Skybox__Skybox_Contextstar()
{
    Context* context = GetScriptContext();
    return new Skybox(context);
}

// class Skybox | File: ../Graphics/Skybox.h
static void Register_Skybox(asIScriptEngine* engine)
{
    // explicit Skybox::Skybox(Context* context)
    engine->RegisterObjectBehaviour("Skybox", asBEHAVE_FACTORY, "Skybox@+ f()", AS_FUNCTION(Skybox__Skybox_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<StaticModel, Skybox>(engine, "StaticModel", "Skybox");
    RegisterSubclass<Drawable, Skybox>(engine, "Drawable", "Skybox");
    RegisterSubclass<Component, Skybox>(engine, "Component", "Skybox");
    RegisterSubclass<Animatable, Skybox>(engine, "Animatable", "Skybox");
    RegisterSubclass<Serializable, Skybox>(engine, "Serializable", "Skybox");
    RegisterSubclass<Object, Skybox>(engine, "Object", "Skybox");
    RegisterSubclass<RefCounted, Skybox>(engine, "RefCounted", "Skybox");

    MemberCollection members;
    RegisterMembers_Skybox<Skybox>(engine, "Skybox");
    CollectMembers_Skybox(members);
    RegisterMembers(engine, "Skybox", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_Skybox
        REGISTER_CLASS_MANUAL_PART_Skybox();
    #endif
}

// explicit StaticModelGroup::StaticModelGroup(Context* context)
static StaticModelGroup* StaticModelGroup__StaticModelGroup_Contextstar()
{
    Context* context = GetScriptContext();
    return new StaticModelGroup(context);
}

// class StaticModelGroup | File: ../Graphics/StaticModelGroup.h
static void Register_StaticModelGroup(asIScriptEngine* engine)
{
    // explicit StaticModelGroup::StaticModelGroup(Context* context)
    engine->RegisterObjectBehaviour("StaticModelGroup", asBEHAVE_FACTORY, "StaticModelGroup@+ f()", AS_FUNCTION(StaticModelGroup__StaticModelGroup_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<StaticModel, StaticModelGroup>(engine, "StaticModel", "StaticModelGroup");
    RegisterSubclass<Drawable, StaticModelGroup>(engine, "Drawable", "StaticModelGroup");
    RegisterSubclass<Component, StaticModelGroup>(engine, "Component", "StaticModelGroup");
    RegisterSubclass<Animatable, StaticModelGroup>(engine, "Animatable", "StaticModelGroup");
    RegisterSubclass<Serializable, StaticModelGroup>(engine, "Serializable", "StaticModelGroup");
    RegisterSubclass<Object, StaticModelGroup>(engine, "Object", "StaticModelGroup");
    RegisterSubclass<RefCounted, StaticModelGroup>(engine, "RefCounted", "StaticModelGroup");

    MemberCollection members;
    RegisterMembers_StaticModelGroup<StaticModelGroup>(engine, "StaticModelGroup");
    CollectMembers_StaticModelGroup(members);
    RegisterMembers(engine, "StaticModelGroup", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_StaticModelGroup
        REGISTER_CLASS_MANUAL_PART_StaticModelGroup();
    #endif
}

// explicit View3D::View3D(Context* context)
static View3D* View3D__View3D_Contextstar()
{
    Context* context = GetScriptContext();
    return new View3D(context);
}

// class View3D | File: ../UI/View3D.h
static void Register_View3D(asIScriptEngine* engine)
{
    // explicit View3D::View3D(Context* context)
    engine->RegisterObjectBehaviour("View3D", asBEHAVE_FACTORY, "View3D@+ f()", AS_FUNCTION(View3D__View3D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Window, View3D>(engine, "Window", "View3D");
    RegisterSubclass<BorderImage, View3D>(engine, "BorderImage", "View3D");
    RegisterSubclass<UIElement, View3D>(engine, "UIElement", "View3D");
    RegisterSubclass<Animatable, View3D>(engine, "Animatable", "View3D");
    RegisterSubclass<Serializable, View3D>(engine, "Serializable", "View3D");
    RegisterSubclass<Object, View3D>(engine, "Object", "View3D");
    RegisterSubclass<RefCounted, View3D>(engine, "RefCounted", "View3D");

    MemberCollection members;
    RegisterMembers_View3D<View3D>(engine, "View3D");
    CollectMembers_View3D(members);
    RegisterMembers(engine, "View3D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_View3D
        REGISTER_CLASS_MANUAL_PART_View3D();
    #endif
}

#ifdef URHO3D_URHO2D

// explicit ParticleEmitter2D::ParticleEmitter2D(Context* context)
static ParticleEmitter2D* ParticleEmitter2D__ParticleEmitter2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new ParticleEmitter2D(context);
}

// class ParticleEmitter2D | File: ../Urho2D/ParticleEmitter2D.h
static void Register_ParticleEmitter2D(asIScriptEngine* engine)
{
    // explicit ParticleEmitter2D::ParticleEmitter2D(Context* context)
    engine->RegisterObjectBehaviour("ParticleEmitter2D", asBEHAVE_FACTORY, "ParticleEmitter2D@+ f()", AS_FUNCTION(ParticleEmitter2D__ParticleEmitter2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Drawable2D, ParticleEmitter2D>(engine, "Drawable2D", "ParticleEmitter2D");
    RegisterSubclass<Drawable, ParticleEmitter2D>(engine, "Drawable", "ParticleEmitter2D");
    RegisterSubclass<Component, ParticleEmitter2D>(engine, "Component", "ParticleEmitter2D");
    RegisterSubclass<Animatable, ParticleEmitter2D>(engine, "Animatable", "ParticleEmitter2D");
    RegisterSubclass<Serializable, ParticleEmitter2D>(engine, "Serializable", "ParticleEmitter2D");
    RegisterSubclass<Object, ParticleEmitter2D>(engine, "Object", "ParticleEmitter2D");
    RegisterSubclass<RefCounted, ParticleEmitter2D>(engine, "RefCounted", "ParticleEmitter2D");

    MemberCollection members;
    RegisterMembers_ParticleEmitter2D<ParticleEmitter2D>(engine, "ParticleEmitter2D");
    CollectMembers_ParticleEmitter2D(members);
    RegisterMembers(engine, "ParticleEmitter2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_ParticleEmitter2D
        REGISTER_CLASS_MANUAL_PART_ParticleEmitter2D();
    #endif
}

// explicit StaticSprite2D::StaticSprite2D(Context* context)
static StaticSprite2D* StaticSprite2D__StaticSprite2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new StaticSprite2D(context);
}

// class StaticSprite2D | File: ../Urho2D/StaticSprite2D.h
static void Register_StaticSprite2D(asIScriptEngine* engine)
{
    // explicit StaticSprite2D::StaticSprite2D(Context* context)
    engine->RegisterObjectBehaviour("StaticSprite2D", asBEHAVE_FACTORY, "StaticSprite2D@+ f()", AS_FUNCTION(StaticSprite2D__StaticSprite2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Drawable2D, StaticSprite2D>(engine, "Drawable2D", "StaticSprite2D");
    RegisterSubclass<Drawable, StaticSprite2D>(engine, "Drawable", "StaticSprite2D");
    RegisterSubclass<Component, StaticSprite2D>(engine, "Component", "StaticSprite2D");
    RegisterSubclass<Animatable, StaticSprite2D>(engine, "Animatable", "StaticSprite2D");
    RegisterSubclass<Serializable, StaticSprite2D>(engine, "Serializable", "StaticSprite2D");
    RegisterSubclass<Object, StaticSprite2D>(engine, "Object", "StaticSprite2D");
    RegisterSubclass<RefCounted, StaticSprite2D>(engine, "RefCounted", "StaticSprite2D");

    MemberCollection members;
    RegisterMembers_StaticSprite2D<StaticSprite2D>(engine, "StaticSprite2D");
    CollectMembers_StaticSprite2D(members);
    RegisterMembers(engine, "StaticSprite2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_StaticSprite2D
        REGISTER_CLASS_MANUAL_PART_StaticSprite2D();
    #endif
}

#endif // def URHO3D_URHO2D

// explicit DropDownList::DropDownList(Context* context)
static DropDownList* DropDownList__DropDownList_Contextstar()
{
    Context* context = GetScriptContext();
    return new DropDownList(context);
}

// class DropDownList | File: ../UI/DropDownList.h
static void Register_DropDownList(asIScriptEngine* engine)
{
    // explicit DropDownList::DropDownList(Context* context)
    engine->RegisterObjectBehaviour("DropDownList", asBEHAVE_FACTORY, "DropDownList@+ f()", AS_FUNCTION(DropDownList__DropDownList_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<Menu, DropDownList>(engine, "Menu", "DropDownList");
    RegisterSubclass<Button, DropDownList>(engine, "Button", "DropDownList");
    RegisterSubclass<BorderImage, DropDownList>(engine, "BorderImage", "DropDownList");
    RegisterSubclass<UIElement, DropDownList>(engine, "UIElement", "DropDownList");
    RegisterSubclass<Animatable, DropDownList>(engine, "Animatable", "DropDownList");
    RegisterSubclass<Serializable, DropDownList>(engine, "Serializable", "DropDownList");
    RegisterSubclass<Object, DropDownList>(engine, "Object", "DropDownList");
    RegisterSubclass<RefCounted, DropDownList>(engine, "RefCounted", "DropDownList");

    MemberCollection members;
    RegisterMembers_DropDownList<DropDownList>(engine, "DropDownList");
    CollectMembers_DropDownList(members);
    RegisterMembers(engine, "DropDownList", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_DropDownList
        REGISTER_CLASS_MANUAL_PART_DropDownList();
    #endif
}

#ifdef URHO3D_URHO2D

// explicit AnimatedSprite2D::AnimatedSprite2D(Context* context)
static AnimatedSprite2D* AnimatedSprite2D__AnimatedSprite2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new AnimatedSprite2D(context);
}

// class AnimatedSprite2D | File: ../Urho2D/AnimatedSprite2D.h
static void Register_AnimatedSprite2D(asIScriptEngine* engine)
{
    // explicit AnimatedSprite2D::AnimatedSprite2D(Context* context)
    engine->RegisterObjectBehaviour("AnimatedSprite2D", asBEHAVE_FACTORY, "AnimatedSprite2D@+ f()", AS_FUNCTION(AnimatedSprite2D__AnimatedSprite2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<StaticSprite2D, AnimatedSprite2D>(engine, "StaticSprite2D", "AnimatedSprite2D");
    RegisterSubclass<Drawable2D, AnimatedSprite2D>(engine, "Drawable2D", "AnimatedSprite2D");
    RegisterSubclass<Drawable, AnimatedSprite2D>(engine, "Drawable", "AnimatedSprite2D");
    RegisterSubclass<Component, AnimatedSprite2D>(engine, "Component", "AnimatedSprite2D");
    RegisterSubclass<Animatable, AnimatedSprite2D>(engine, "Animatable", "AnimatedSprite2D");
    RegisterSubclass<Serializable, AnimatedSprite2D>(engine, "Serializable", "AnimatedSprite2D");
    RegisterSubclass<Object, AnimatedSprite2D>(engine, "Object", "AnimatedSprite2D");
    RegisterSubclass<RefCounted, AnimatedSprite2D>(engine, "RefCounted", "AnimatedSprite2D");

    MemberCollection members;
    RegisterMembers_AnimatedSprite2D<AnimatedSprite2D>(engine, "AnimatedSprite2D");
    CollectMembers_AnimatedSprite2D(members);
    RegisterMembers(engine, "AnimatedSprite2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_AnimatedSprite2D
        REGISTER_CLASS_MANUAL_PART_AnimatedSprite2D();
    #endif
}

// explicit StretchableSprite2D::StretchableSprite2D(Context* context)
static StretchableSprite2D* StretchableSprite2D__StretchableSprite2D_Contextstar()
{
    Context* context = GetScriptContext();
    return new StretchableSprite2D(context);
}

// class StretchableSprite2D | File: ../Urho2D/StretchableSprite2D.h
static void Register_StretchableSprite2D(asIScriptEngine* engine)
{
    // explicit StretchableSprite2D::StretchableSprite2D(Context* context)
    engine->RegisterObjectBehaviour("StretchableSprite2D", asBEHAVE_FACTORY, "StretchableSprite2D@+ f()", AS_FUNCTION(StretchableSprite2D__StretchableSprite2D_Contextstar) , AS_CALL_CDECL);

    RegisterSubclass<StaticSprite2D, StretchableSprite2D>(engine, "StaticSprite2D", "StretchableSprite2D");
    RegisterSubclass<Drawable2D, StretchableSprite2D>(engine, "Drawable2D", "StretchableSprite2D");
    RegisterSubclass<Drawable, StretchableSprite2D>(engine, "Drawable", "StretchableSprite2D");
    RegisterSubclass<Component, StretchableSprite2D>(engine, "Component", "StretchableSprite2D");
    RegisterSubclass<Animatable, StretchableSprite2D>(engine, "Animatable", "StretchableSprite2D");
    RegisterSubclass<Serializable, StretchableSprite2D>(engine, "Serializable", "StretchableSprite2D");
    RegisterSubclass<Object, StretchableSprite2D>(engine, "Object", "StretchableSprite2D");
    RegisterSubclass<RefCounted, StretchableSprite2D>(engine, "RefCounted", "StretchableSprite2D");

    MemberCollection members;
    RegisterMembers_StretchableSprite2D<StretchableSprite2D>(engine, "StretchableSprite2D");
    CollectMembers_StretchableSprite2D(members);
    RegisterMembers(engine, "StretchableSprite2D", members);

    #ifdef REGISTER_CLASS_MANUAL_PART_StretchableSprite2D
        REGISTER_CLASS_MANUAL_PART_StretchableSprite2D();
    #endif
}

#endif // def URHO3D_URHO2D

void ASRegisterGeneratedClasses(asIScriptEngine* engine)
{
    Register_AllocatorBlock(engine);
    Register_AllocatorNode(engine);
    Register_AnimationControl(engine);
    Register_AnimationKeyFrame(engine);
    Register_AnimationStateTrack(engine);
    Register_AnimationTrack(engine);
    Register_AnimationTriggerPoint(engine);
    Register_AreaAllocator(engine);
    Register_AsyncProgress(engine);
    Register_AttributeInfo(engine);
    Register_BackgroundLoadItem(engine);
    Register_Batch(engine);
    Register_BatchGroupKey(engine);
    Register_BatchQueue(engine);
    Register_BiasParameters(engine);
    Register_Billboard(engine);
    Register_Bone(engine);
    Register_BoundingBox(engine);
    Register_CascadeParameters(engine);
    Register_CharLocation(engine);
    Register_Color(engine);
    Register_ColorFrame(engine);
    Register_CompressedLevel(engine);
    Register_Condition(engine);
    Register_Controls(engine);
    Register_CursorShapeInfo(engine);
    Register_CustomGeometryVertex(engine);
    Register_DebugLine(engine);
    Register_DebugTriangle(engine);
    Register_Decal(engine);
    Register_DecalVertex(engine);
    Register_DepthValue(engine);
    Register_Deserializer(engine);
    Register_DirtyBits(engine);
    Register_FileSelectorEntry(engine);
    Register_FocusParameters(engine);
    Register_FontGlyph(engine);
    Register_FrameInfo(engine);
    Register_Frustum(engine);
    Register_GPUObject(engine);
    Register_GeometryDesc(engine);
    Register_HashBase(engine);
    Register_HashIteratorBase(engine);
    Register_HashNodeBase(engine);
    Register_HiresTimer(engine);
    Register_IndexBufferDesc(engine);
    Register_InstanceData(engine);
    Register_IntRect(engine);
    Register_IntVector2(engine);
    Register_IntVector3(engine);
    Register_JSONValue(engine);
    Register_JoystickState(engine);
    Register_LightBatchQueue(engine);
    Register_LightQueryResult(engine);
    Register_LinkedListNode(engine);
    Register_ListBase(engine);
    Register_ListIteratorBase(engine);
    Register_ListNodeBase(engine);
    Register_MaterialShaderParameter(engine);
    Register_Matrix2(engine);
    Register_Matrix3(engine);
    Register_Matrix3x4(engine);
    Register_Matrix4(engine);
    Register_ModelMorph(engine);
    Register_Mutex(engine);
    Register_MutexLock(engine);
    Register_NetworkState(engine);
    Register_NodeImpl(engine);
    Register_OcclusionBatch(engine);
    Register_OcclusionBufferData(engine);
    Register_OctreeQueryResult(engine);
    Register_PackageEntry(engine);
    Register_Particle(engine);
    Register_PerThreadSceneResult(engine);
    Register_Plane(engine);
    Register_Polyhedron(engine);
    Register_Quaternion(engine);
    Register_Ray(engine);
    Register_RayQueryResult(engine);
    Register_Rect(engine);
    Register_RefCount(engine);
    Register_RefCounted(engine);
    Register_RenderPathCommand(engine);
    Register_RenderTargetInfo(engine);
    Register_ReplicationState(engine);
    Register_ResourceGroup(engine);
    Register_ResourceRef(engine);
    Register_ResourceRefList(engine);
    Register_ScenePassInfo(engine);
    Register_SceneResolver(engine);
    Register_ScratchBuffer(engine);
    Register_ScreenModeParams(engine);
    Register_Serializer(engine);
    Register_ShaderParameter(engine);
    Register_ShadowBatchQueue(engine);
    Register_Skeleton(engine);
    Register_SourceBatch(engine);
    Register_Sphere(engine);
    Register_Spline(engine);
    Register_StaticModelGeometryData(engine);
    Register_StoredLogMessage(engine);
    Register_String(engine);
    Register_StringHash(engine);
    Register_StringHashRegister(engine);
    Register_TechniqueEntry(engine);
    Register_TextureFrame(engine);
    Register_Timer(engine);
    Register_TouchState(engine);
    Register_TrailPoint(engine);
    Register_UIBatch(engine);
    Register_VAnimEventFrame(engine);
    Register_VAnimKeyFrame(engine);
    Register_Variant(engine);
    Register_Vector2(engine);
    Register_Vector3(engine);
    Register_Vector4(engine);
    Register_VectorBase(engine);
    Register_VertexBufferDesc(engine);
    Register_VertexBufferMorph(engine);
    Register_VertexElement(engine);
    Register_WindowModeParams(engine);
    Register_XMLElement(engine);
    Register_XPathQuery(engine);
    Register_XPathResultSet(engine);

#ifdef URHO3D_NAVIGATION
    Register_CrowdObstacleAvoidanceParams(engine);
    Register_NavAreaStub(engine);
    Register_NavBuildData(engine);
    Register_NavigationGeometryInfo(engine);
    Register_NavigationPathPoint(engine);
#endif

#ifdef URHO3D_NETWORK
    Register_PackageDownload(engine);
    Register_PackageUpload(engine);
    Register_RemoteEvent(engine);
#endif

#ifdef URHO3D_PHYSICS
    Register_DelayedWorldTransform(engine);
    Register_ManifoldPair(engine);
    Register_PhysicsRaycastResult(engine);
    Register_PhysicsWorldConfig(engine);
#endif

#ifdef URHO3D_URHO2D
    Register_DelayedWorldTransform2D(engine);
    Register_Particle2D(engine);
    Register_PhysicsRaycastResult2D(engine);
    Register_SourceBatch2D(engine);
    Register_TileMapInfo2D(engine);
    Register_Vertex2D(engine);
#endif
    Register_AnimationState(engine);
    Register_AttributeAccessor(engine);
    Register_BatchGroup(engine);
    Register_ComponentReplicationState(engine);
    Register_Context(engine);
    Register_EventReceiverGroup(engine);
    Register_FontFace(engine);
    Register_NodeReplicationState(engine);
    Register_Object(engine);
    Register_ObjectFactory(engine);
    Register_Pass(engine);
    Register_RenderPath(engine);
    Register_RenderSurface(engine);
    Register_SceneReplicationState(engine);
    Register_ShaderVariation(engine);
    Register_SoundStream(engine);
    Register_ValueAnimationInfo(engine);

#ifdef URHO3D_NAVIGATION
    Register_SimpleNavBuildData(engine);
#endif

#ifdef URHO3D_NETWORK
    Register_HttpRequest(engine);
#endif

#ifdef URHO3D_PHYSICS
    Register_CollisionGeometryData(engine);
#endif

#ifdef URHO3D_URHO2D
    Register_PropertySet2D(engine);
    Register_Tile2D(engine);
    Register_TileMapObject2D(engine);
    Register_TmxLayer2D(engine);
#endif
    Register_AttributeAnimationInfo(engine);
    Register_Audio(engine);
    Register_BufferedSoundStream(engine);
    Register_Console(engine);
    Register_ConstantBuffer(engine);
    Register_DebugHud(engine);
    Register_Engine(engine);
    Register_File(engine);
    Register_FileSelector(engine);
    Register_FileSystem(engine);
    Register_FileWatcher(engine);
    Register_FontFaceBitmap(engine);
    Register_FontFaceFreeType(engine);
    Register_Geometry(engine);
    Register_Graphics(engine);
    Register_IndexBuffer(engine);
    Register_Input(engine);
    Register_Localization(engine);
    Register_Log(engine);
    Register_MessageBox(engine);
    Register_NamedPipe(engine);
    Register_OcclusionBuffer(engine);
    Register_OggVorbisSoundStream(engine);
    Register_PackageFile(engine);
    Register_Profiler(engine);
    Register_Renderer(engine);
    Register_Resource(engine);
    Register_ResourceCache(engine);
    Register_Serializable(engine);
    Register_ShaderParameterAnimationInfo(engine);
    Register_ShaderPrecache(engine);
    Register_Time(engine);
    Register_UI(engine);
    Register_VectorBuffer(engine);
    Register_VertexBuffer(engine);
    Register_View(engine);
    Register_Viewport(engine);
    Register_WorkQueue(engine);

#ifdef URHO3D_DATABASE
    Register_Database(engine);
#endif

#ifdef URHO3D_NETWORK
    Register_Connection(engine);
    Register_Network(engine);
#endif

#ifdef URHO3D_PHYSICS
    Register_ConvexData(engine);
    Register_GImpactMeshData(engine);
    Register_HeightfieldData(engine);
    Register_TriangleMeshData(engine);
#endif

#ifdef URHO3D_URHO2D
    Register_TmxImageLayer2D(engine);
    Register_TmxObjectGroup2D(engine);
    Register_TmxTileLayer2D(engine);
#endif
    Register_Animatable(engine);
    Register_EventProfiler(engine);
    Register_Font(engine);
    Register_Image(engine);
    Register_JSONFile(engine);
    Register_Material(engine);
    Register_ObjectAnimation(engine);
    Register_ParticleEffect(engine);
    Register_ResourceWithMetadata(engine);
    Register_Shader(engine);
    Register_Technique(engine);
    Register_ValueAnimation(engine);
    Register_XMLFile(engine);

#ifdef URHO3D_URHO2D
    Register_AnimationSet2D(engine);
    Register_ParticleEffect2D(engine);
    Register_Sprite2D(engine);
    Register_SpriteSheet2D(engine);
    Register_TmxFile2D(engine);
#endif
    Register_Animation(engine);
    Register_Component(engine);
    Register_Model(engine);
    Register_Node(engine);
    Register_Sound(engine);
    Register_Texture(engine);
    Register_UIElement(engine);
    Register_AnimationController(engine);
    Register_BorderImage(engine);
    Register_Camera(engine);
    Register_DebugRenderer(engine);
    Register_Drawable(engine);
    Register_LogicComponent(engine);
    Register_Octree(engine);
    Register_Scene(engine);
    Register_ScrollView(engine);
    Register_SmoothedTransform(engine);
    Register_SoundListener(engine);
    Register_SoundSource(engine);
    Register_SplinePath(engine);
    Register_Sprite(engine);
    Register_Terrain(engine);
    Register_Texture2D(engine);
    Register_Texture2DArray(engine);
    Register_Texture3D(engine);
    Register_TextureCube(engine);
    Register_ToolTip(engine);
    Register_UIComponent(engine);
    Register_UISelectable(engine);
    Register_UnknownComponent(engine);

#ifdef URHO3D_IK
    Register_IKConstraint(engine);
    Register_IKEffector(engine);
    Register_IKSolver(engine);
#endif

#ifdef URHO3D_NAVIGATION
    Register_CrowdAgent(engine);
    Register_CrowdManager(engine);
    Register_NavArea(engine);
    Register_Navigable(engine);
    Register_NavigationMesh(engine);
    Register_Obstacle(engine);
    Register_OffMeshConnection(engine);
#endif

#ifdef URHO3D_NETWORK
    Register_NetworkPriority(engine);
#endif

#ifdef URHO3D_PHYSICS
    Register_CollisionShape(engine);
    Register_Constraint(engine);
    Register_PhysicsWorld(engine);
    Register_RigidBody(engine);
#endif

#ifdef URHO3D_URHO2D
    Register_CollisionShape2D(engine);
    Register_Constraint2D(engine);
    Register_PhysicsWorld2D(engine);
    Register_RigidBody2D(engine);
    Register_TileMap2D(engine);
    Register_TileMapLayer2D(engine);
#endif
    Register_BillboardSet(engine);
    Register_Button(engine);
    Register_CheckBox(engine);
    Register_Cursor(engine);
    Register_CustomGeometry(engine);
    Register_DecalSet(engine);
    Register_Light(engine);
    Register_LineEdit(engine);
    Register_ListView(engine);
    Register_ProgressBar(engine);
    Register_RibbonTrail(engine);
    Register_ScrollBar(engine);
    Register_Slider(engine);
    Register_SoundSource3D(engine);
    Register_StaticModel(engine);
    Register_TerrainPatch(engine);
    Register_Text(engine);
    Register_Text3D(engine);
    Register_Window(engine);
    Register_Zone(engine);

#ifdef URHO3D_NAVIGATION
    Register_DynamicNavigationMesh(engine);
#endif

#ifdef URHO3D_PHYSICS
    Register_RaycastVehicle(engine);
#endif

#ifdef URHO3D_URHO2D
    Register_CollisionBox2D(engine);
    Register_CollisionChain2D(engine);
    Register_CollisionCircle2D(engine);
    Register_CollisionEdge2D(engine);
    Register_CollisionPolygon2D(engine);
    Register_ConstraintDistance2D(engine);
    Register_ConstraintFriction2D(engine);
    Register_ConstraintGear2D(engine);
    Register_ConstraintMotor2D(engine);
    Register_ConstraintMouse2D(engine);
    Register_ConstraintPrismatic2D(engine);
    Register_ConstraintPulley2D(engine);
    Register_ConstraintRevolute2D(engine);
    Register_ConstraintRope2D(engine);
    Register_ConstraintWeld2D(engine);
    Register_ConstraintWheel2D(engine);
    Register_Drawable2D(engine);
    Register_Renderer2D(engine);
#endif
    Register_AnimatedModel(engine);
    Register_Menu(engine);
    Register_ParticleEmitter(engine);
    Register_Skybox(engine);
    Register_StaticModelGroup(engine);
    Register_View3D(engine);

#ifdef URHO3D_URHO2D
    Register_ParticleEmitter2D(engine);
    Register_StaticSprite2D(engine);
#endif
    Register_DropDownList(engine);

#ifdef URHO3D_URHO2D
    Register_AnimatedSprite2D(engine);
    Register_StretchableSprite2D(engine);
#endif
}

}
