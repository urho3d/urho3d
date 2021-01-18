// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

static void RegisterAbstractFile(asIScriptEngine* engine)
{
}

static void RegisterAllContentOctreeQuery(asIScriptEngine* engine)
{
}

// AllocatorBlock::~AllocatorBlock() | Implicitly-declared
static void AllocatorBlock_Destructor(AllocatorBlock* ptr)
{
    ptr->~AllocatorBlock();
}

static void RegisterAllocatorBlock(asIScriptEngine* engine)
{
    // AllocatorBlock::~AllocatorBlock() | Implicitly-declared
    engine->RegisterObjectBehaviour("AllocatorBlock", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AllocatorBlock_Destructor), asCALL_CDECL_OBJFIRST);
}

// AllocatorNode::~AllocatorNode() | Implicitly-declared
static void AllocatorNode_Destructor(AllocatorNode* ptr)
{
    ptr->~AllocatorNode();
}

static void RegisterAllocatorNode(asIScriptEngine* engine)
{
    // AllocatorNode::~AllocatorNode() | Implicitly-declared
    engine->RegisterObjectBehaviour("AllocatorNode", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AllocatorNode_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterAnimatable(asIScriptEngine* engine)
{
}

static void RegisterAnimatedModel(asIScriptEngine* engine)
{
}

static void RegisterAnimation(asIScriptEngine* engine)
{
}

static void RegisterAnimationControl(asIScriptEngine* engine)
{
}

static void RegisterAnimationController(asIScriptEngine* engine)
{
}

// AnimationKeyFrame::~AnimationKeyFrame() | Implicitly-declared
static void AnimationKeyFrame_Destructor(AnimationKeyFrame* ptr)
{
    ptr->~AnimationKeyFrame();
}

static void RegisterAnimationKeyFrame(asIScriptEngine* engine)
{
    // AnimationKeyFrame::~AnimationKeyFrame() | Implicitly-declared
    engine->RegisterObjectBehaviour("AnimationKeyFrame", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AnimationKeyFrame_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterAnimationState(asIScriptEngine* engine)
{
}

// AnimationStateTrack::~AnimationStateTrack() | File: ../Graphics/AnimationState.h
static void AnimationStateTrack_Destructor(AnimationStateTrack* ptr)
{
    ptr->~AnimationStateTrack();
}

static void RegisterAnimationStateTrack(asIScriptEngine* engine)
{
    // AnimationStateTrack::~AnimationStateTrack() | File: ../Graphics/AnimationState.h
    engine->RegisterObjectBehaviour("AnimationStateTrack", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AnimationStateTrack_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterAnimationTrack(asIScriptEngine* engine)
{
}

// AnimationTriggerPoint::~AnimationTriggerPoint() | Implicitly-declared
static void AnimationTriggerPoint_Destructor(AnimationTriggerPoint* ptr)
{
    ptr->~AnimationTriggerPoint();
}

static void RegisterAnimationTriggerPoint(asIScriptEngine* engine)
{
    // AnimationTriggerPoint::~AnimationTriggerPoint() | Implicitly-declared
    engine->RegisterObjectBehaviour("AnimationTriggerPoint", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AnimationTriggerPoint_Destructor), asCALL_CDECL_OBJFIRST);
}

// AreaAllocator::~AreaAllocator() | Implicitly-declared
static void AreaAllocator_Destructor(AreaAllocator* ptr)
{
    ptr->~AreaAllocator();
}

static void RegisterAreaAllocator(asIScriptEngine* engine)
{
    // AreaAllocator::~AreaAllocator() | Implicitly-declared
    engine->RegisterObjectBehaviour("AreaAllocator", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AreaAllocator_Destructor), asCALL_CDECL_OBJFIRST);
}

// AsyncProgress::~AsyncProgress() | Implicitly-declared
static void AsyncProgress_Destructor(AsyncProgress* ptr)
{
    ptr->~AsyncProgress();
}

static void RegisterAsyncProgress(asIScriptEngine* engine)
{
    // AsyncProgress::~AsyncProgress() | Implicitly-declared
    engine->RegisterObjectBehaviour("AsyncProgress", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AsyncProgress_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterAttributeAccessor(asIScriptEngine* engine)
{
}

static void RegisterAttributeAnimationInfo(asIScriptEngine* engine)
{
}

static void RegisterAttributeHandle(asIScriptEngine* engine)
{
}

// AttributeInfo::~AttributeInfo() | Implicitly-declared
static void AttributeInfo_Destructor(AttributeInfo* ptr)
{
    ptr->~AttributeInfo();
}

static void RegisterAttributeInfo(asIScriptEngine* engine)
{
    // AttributeInfo::~AttributeInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("AttributeInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AttributeInfo_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterAudio(asIScriptEngine* engine)
{
}

static void RegisterAutoProfileBlock(asIScriptEngine* engine)
{
}

// BackgroundLoadItem::~BackgroundLoadItem() | Implicitly-declared
static void BackgroundLoadItem_Destructor(BackgroundLoadItem* ptr)
{
    ptr->~BackgroundLoadItem();
}

static void RegisterBackgroundLoadItem(asIScriptEngine* engine)
{
    // BackgroundLoadItem::~BackgroundLoadItem() | Implicitly-declared
    engine->RegisterObjectBehaviour("BackgroundLoadItem", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(BackgroundLoadItem_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterBackgroundLoader(asIScriptEngine* engine)
{
}

// Batch::~Batch() | Implicitly-declared
static void Batch_Destructor(Batch* ptr)
{
    ptr->~Batch();
}

static void RegisterBatch(asIScriptEngine* engine)
{
    // Batch::~Batch() | Implicitly-declared
    engine->RegisterObjectBehaviour("Batch", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Batch_Destructor), asCALL_CDECL_OBJFIRST);
}

// BatchGroup::~BatchGroup()=default | File: ../Graphics/Batch.h
static void BatchGroup_Destructor(BatchGroup* ptr)
{
    ptr->~BatchGroup();
}

static void RegisterBatchGroup(asIScriptEngine* engine)
{
    // BatchGroup::~BatchGroup()=default | File: ../Graphics/Batch.h
    engine->RegisterObjectBehaviour("BatchGroup", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(BatchGroup_Destructor), asCALL_CDECL_OBJFIRST);
}

// BatchGroupKey::~BatchGroupKey() | Implicitly-declared
static void BatchGroupKey_Destructor(BatchGroupKey* ptr)
{
    ptr->~BatchGroupKey();
}

static void RegisterBatchGroupKey(asIScriptEngine* engine)
{
    // BatchGroupKey::~BatchGroupKey() | Implicitly-declared
    engine->RegisterObjectBehaviour("BatchGroupKey", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(BatchGroupKey_Destructor), asCALL_CDECL_OBJFIRST);
}

// BatchQueue::~BatchQueue() | Implicitly-declared
static void BatchQueue_Destructor(BatchQueue* ptr)
{
    ptr->~BatchQueue();
}

static void RegisterBatchQueue(asIScriptEngine* engine)
{
    // BatchQueue::~BatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("BatchQueue", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(BatchQueue_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterBiasParameters(asIScriptEngine* engine)
{
}

static void RegisterBillboard(asIScriptEngine* engine)
{
}

static void RegisterBillboardSet(asIScriptEngine* engine)
{
}

static void RegisterBone(asIScriptEngine* engine)
{
}

static void RegisterBorderImage(asIScriptEngine* engine)
{
}

static void RegisterBoundingBox(asIScriptEngine* engine)
{
}

static void RegisterBoxOctreeQuery(asIScriptEngine* engine)
{
}

static void RegisterBufferedSoundStream(asIScriptEngine* engine)
{
}

static void RegisterButton(asIScriptEngine* engine)
{
}

static void RegisterCamera(asIScriptEngine* engine)
{
}

static void RegisterCascadeParameters(asIScriptEngine* engine)
{
}

// CharLocation::~CharLocation() | Implicitly-declared
static void CharLocation_Destructor(CharLocation* ptr)
{
    ptr->~CharLocation();
}

static void RegisterCharLocation(asIScriptEngine* engine)
{
    // CharLocation::~CharLocation() | Implicitly-declared
    engine->RegisterObjectBehaviour("CharLocation", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(CharLocation_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterCheckBox(asIScriptEngine* engine)
{
}

static void RegisterColor(asIScriptEngine* engine)
{
}

static void RegisterColorFrame(asIScriptEngine* engine)
{
}

static void RegisterComponent(asIScriptEngine* engine)
{
}

// ComponentReplicationState::~ComponentReplicationState() | Implicitly-declared
static void ComponentReplicationState_Destructor(ComponentReplicationState* ptr)
{
    ptr->~ComponentReplicationState();
}

static void RegisterComponentReplicationState(asIScriptEngine* engine)
{
    // ComponentReplicationState::~ComponentReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("ComponentReplicationState", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ComponentReplicationState_Destructor), asCALL_CDECL_OBJFIRST);
}

// CompressedLevel::~CompressedLevel() | Implicitly-declared
static void CompressedLevel_Destructor(CompressedLevel* ptr)
{
    ptr->~CompressedLevel();
}

static void RegisterCompressedLevel(asIScriptEngine* engine)
{
    // CompressedLevel::~CompressedLevel() | Implicitly-declared
    engine->RegisterObjectBehaviour("CompressedLevel", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(CompressedLevel_Destructor), asCALL_CDECL_OBJFIRST);
}

// Condition::~Condition() | File: ../Core/Condition.h
static void Condition_Destructor(Condition* ptr)
{
    ptr->~Condition();
}

static void RegisterCondition(asIScriptEngine* engine)
{
    // Condition::~Condition() | File: ../Core/Condition.h
    engine->RegisterObjectBehaviour("Condition", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Condition_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterConsole(asIScriptEngine* engine)
{
}

static void RegisterConstantBuffer(asIScriptEngine* engine)
{
}

static void RegisterContext(asIScriptEngine* engine)
{
}

// Controls::~Controls() | File: ../Input/Controls.h
static void Controls_Destructor(Controls* ptr)
{
    ptr->~Controls();
}

static void RegisterControls(asIScriptEngine* engine)
{
    // Controls::~Controls() | File: ../Input/Controls.h
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Controls_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterCursor(asIScriptEngine* engine)
{
}

// CursorShapeInfo::~CursorShapeInfo() | Implicitly-declared
static void CursorShapeInfo_Destructor(CursorShapeInfo* ptr)
{
    ptr->~CursorShapeInfo();
}

static void RegisterCursorShapeInfo(asIScriptEngine* engine)
{
    // CursorShapeInfo::~CursorShapeInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("CursorShapeInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(CursorShapeInfo_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterCustomGeometry(asIScriptEngine* engine)
{
}

static void RegisterCustomGeometryVertex(asIScriptEngine* engine)
{
}

static void RegisterCustomVariantValue(asIScriptEngine* engine)
{
}

static void RegisterDebugHud(asIScriptEngine* engine)
{
}

// DebugLine::~DebugLine() | Implicitly-declared
static void DebugLine_Destructor(DebugLine* ptr)
{
    ptr->~DebugLine();
}

static void RegisterDebugLine(asIScriptEngine* engine)
{
    // DebugLine::~DebugLine() | Implicitly-declared
    engine->RegisterObjectBehaviour("DebugLine", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DebugLine_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterDebugRenderer(asIScriptEngine* engine)
{
}

// DebugTriangle::~DebugTriangle() | Implicitly-declared
static void DebugTriangle_Destructor(DebugTriangle* ptr)
{
    ptr->~DebugTriangle();
}

static void RegisterDebugTriangle(asIScriptEngine* engine)
{
    // DebugTriangle::~DebugTriangle() | Implicitly-declared
    engine->RegisterObjectBehaviour("DebugTriangle", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DebugTriangle_Destructor), asCALL_CDECL_OBJFIRST);
}

// Decal::~Decal() | Implicitly-declared
static void Decal_Destructor(Decal* ptr)
{
    ptr->~Decal();
}

static void RegisterDecal(asIScriptEngine* engine)
{
    // Decal::~Decal() | Implicitly-declared
    engine->RegisterObjectBehaviour("Decal", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Decal_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterDecalSet(asIScriptEngine* engine)
{
}

// DecalVertex::~DecalVertex() | Implicitly-declared
static void DecalVertex_Destructor(DecalVertex* ptr)
{
    ptr->~DecalVertex();
}

static void RegisterDecalVertex(asIScriptEngine* engine)
{
    // DecalVertex::~DecalVertex() | Implicitly-declared
    engine->RegisterObjectBehaviour("DecalVertex", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DecalVertex_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterDepthValue(asIScriptEngine* engine)
{
}

static void RegisterDeserializer(asIScriptEngine* engine)
{
}

// DirtyBits::~DirtyBits() | Implicitly-declared
static void DirtyBits_Destructor(DirtyBits* ptr)
{
    ptr->~DirtyBits();
}

static void RegisterDirtyBits(asIScriptEngine* engine)
{
    // DirtyBits::~DirtyBits() | Implicitly-declared
    engine->RegisterObjectBehaviour("DirtyBits", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DirtyBits_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterDrawable(asIScriptEngine* engine)
{
}

static void RegisterDropDownList(asIScriptEngine* engine)
{
}

static void RegisterEngine(asIScriptEngine* engine)
{
}

static void RegisterEventHandler11Impl(asIScriptEngine* engine)
{
}

static void RegisterEventProfiler(asIScriptEngine* engine)
{
}

static void RegisterEventProfilerBlock(asIScriptEngine* engine)
{
}

static void RegisterEventReceiverGroup(asIScriptEngine* engine)
{
}

static void RegisterFile(asIScriptEngine* engine)
{
}

static void RegisterFileSelector(asIScriptEngine* engine)
{
}

// FileSelectorEntry::~FileSelectorEntry() | Implicitly-declared
static void FileSelectorEntry_Destructor(FileSelectorEntry* ptr)
{
    ptr->~FileSelectorEntry();
}

static void RegisterFileSelectorEntry(asIScriptEngine* engine)
{
    // FileSelectorEntry::~FileSelectorEntry() | Implicitly-declared
    engine->RegisterObjectBehaviour("FileSelectorEntry", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(FileSelectorEntry_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterFileSystem(asIScriptEngine* engine)
{
}

static void RegisterFileWatcher(asIScriptEngine* engine)
{
}

static void RegisterFocusParameters(asIScriptEngine* engine)
{
}

static void RegisterFont(asIScriptEngine* engine)
{
}

static void RegisterFontFace(asIScriptEngine* engine)
{
}

static void RegisterFontFaceBitmap(asIScriptEngine* engine)
{
}

static void RegisterFontFaceFreeType(asIScriptEngine* engine)
{
}

// FontGlyph::~FontGlyph() | Implicitly-declared
static void FontGlyph_Destructor(FontGlyph* ptr)
{
    ptr->~FontGlyph();
}

static void RegisterFontGlyph(asIScriptEngine* engine)
{
    // FontGlyph::~FontGlyph() | Implicitly-declared
    engine->RegisterObjectBehaviour("FontGlyph", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(FontGlyph_Destructor), asCALL_CDECL_OBJFIRST);
}

// FrameInfo::~FrameInfo() | Implicitly-declared
static void FrameInfo_Destructor(FrameInfo* ptr)
{
    ptr->~FrameInfo();
}

static void RegisterFrameInfo(asIScriptEngine* engine)
{
    // FrameInfo::~FrameInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("FrameInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(FrameInfo_Destructor), asCALL_CDECL_OBJFIRST);
}

// Frustum::~Frustum() | Implicitly-declared
static void Frustum_Destructor(Frustum* ptr)
{
    ptr->~Frustum();
}

static void RegisterFrustum(asIScriptEngine* engine)
{
    // Frustum::~Frustum() | Implicitly-declared
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Frustum_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterFrustumOctreeQuery(asIScriptEngine* engine)
{
}

// virtual GPUObject::~GPUObject() | File: ../Graphics/GPUObject.h
static void GPUObject_Destructor(GPUObject* ptr)
{
    ptr->~GPUObject();
}

static void RegisterGPUObject(asIScriptEngine* engine)
{
    // virtual GPUObject::~GPUObject() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectBehaviour("GPUObject", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(GPUObject_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterGeometry(asIScriptEngine* engine)
{
}

// GeometryDesc::~GeometryDesc() | Implicitly-declared
static void GeometryDesc_Destructor(GeometryDesc* ptr)
{
    ptr->~GeometryDesc();
}

static void RegisterGeometryDesc(asIScriptEngine* engine)
{
    // GeometryDesc::~GeometryDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("GeometryDesc", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(GeometryDesc_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterGlyphLocation(asIScriptEngine* engine)
{
}

static void RegisterGraphics(asIScriptEngine* engine)
{
}

// HashBase::~HashBase() | Implicitly-declared
static void HashBase_Destructor(HashBase* ptr)
{
    ptr->~HashBase();
}

static void RegisterHashBase(asIScriptEngine* engine)
{
    // HashBase::~HashBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("HashBase", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(HashBase_Destructor), asCALL_CDECL_OBJFIRST);
}

// HashIteratorBase::~HashIteratorBase() | Implicitly-declared
static void HashIteratorBase_Destructor(HashIteratorBase* ptr)
{
    ptr->~HashIteratorBase();
}

static void RegisterHashIteratorBase(asIScriptEngine* engine)
{
    // HashIteratorBase::~HashIteratorBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("HashIteratorBase", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(HashIteratorBase_Destructor), asCALL_CDECL_OBJFIRST);
}

// HashNodeBase::~HashNodeBase() | Implicitly-declared
static void HashNodeBase_Destructor(HashNodeBase* ptr)
{
    ptr->~HashNodeBase();
}

static void RegisterHashNodeBase(asIScriptEngine* engine)
{
    // HashNodeBase::~HashNodeBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("HashNodeBase", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(HashNodeBase_Destructor), asCALL_CDECL_OBJFIRST);
}

// HiresTimer::~HiresTimer() | Implicitly-declared
static void HiresTimer_Destructor(HiresTimer* ptr)
{
    ptr->~HiresTimer();
}

static void RegisterHiresTimer(asIScriptEngine* engine)
{
    // HiresTimer::~HiresTimer() | Implicitly-declared
    engine->RegisterObjectBehaviour("HiresTimer", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(HiresTimer_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterImage(asIScriptEngine* engine)
{
}

static void RegisterIndexBuffer(asIScriptEngine* engine)
{
}

// IndexBufferDesc::~IndexBufferDesc() | Implicitly-declared
static void IndexBufferDesc_Destructor(IndexBufferDesc* ptr)
{
    ptr->~IndexBufferDesc();
}

static void RegisterIndexBufferDesc(asIScriptEngine* engine)
{
    // IndexBufferDesc::~IndexBufferDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("IndexBufferDesc", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(IndexBufferDesc_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterInput(asIScriptEngine* engine)
{
}

// InstanceData::~InstanceData() | Implicitly-declared
static void InstanceData_Destructor(InstanceData* ptr)
{
    ptr->~InstanceData();
}

static void RegisterInstanceData(asIScriptEngine* engine)
{
    // InstanceData::~InstanceData() | Implicitly-declared
    engine->RegisterObjectBehaviour("InstanceData", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(InstanceData_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterIntRect(asIScriptEngine* engine)
{
}

static void RegisterIntVector2(asIScriptEngine* engine)
{
}

static void RegisterIntVector3(asIScriptEngine* engine)
{
}

static void RegisterJSONFile(asIScriptEngine* engine)
{
}

// JSONValue::~JSONValue() | File: ../Resource/JSONValue.h
static void JSONValue_Destructor(JSONValue* ptr)
{
    ptr->~JSONValue();
}

static void RegisterJSONValue(asIScriptEngine* engine)
{
    // JSONValue::~JSONValue() | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(JSONValue_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterJoystickState(asIScriptEngine* engine)
{
}

static void RegisterLight(asIScriptEngine* engine)
{
}

// LightBatchQueue::~LightBatchQueue() | Implicitly-declared
static void LightBatchQueue_Destructor(LightBatchQueue* ptr)
{
    ptr->~LightBatchQueue();
}

static void RegisterLightBatchQueue(asIScriptEngine* engine)
{
    // LightBatchQueue::~LightBatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("LightBatchQueue", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(LightBatchQueue_Destructor), asCALL_CDECL_OBJFIRST);
}

// LightQueryResult::~LightQueryResult() | Implicitly-declared
static void LightQueryResult_Destructor(LightQueryResult* ptr)
{
    ptr->~LightQueryResult();
}

static void RegisterLightQueryResult(asIScriptEngine* engine)
{
    // LightQueryResult::~LightQueryResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("LightQueryResult", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(LightQueryResult_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterLineEdit(asIScriptEngine* engine)
{
}

// LinkedListNode::~LinkedListNode() | Implicitly-declared
static void LinkedListNode_Destructor(LinkedListNode* ptr)
{
    ptr->~LinkedListNode();
}

static void RegisterLinkedListNode(asIScriptEngine* engine)
{
    // LinkedListNode::~LinkedListNode() | Implicitly-declared
    engine->RegisterObjectBehaviour("LinkedListNode", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(LinkedListNode_Destructor), asCALL_CDECL_OBJFIRST);
}

// ListBase::~ListBase() | Implicitly-declared
static void ListBase_Destructor(ListBase* ptr)
{
    ptr->~ListBase();
}

static void RegisterListBase(asIScriptEngine* engine)
{
    // ListBase::~ListBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("ListBase", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ListBase_Destructor), asCALL_CDECL_OBJFIRST);
}

// ListIteratorBase::~ListIteratorBase() | Implicitly-declared
static void ListIteratorBase_Destructor(ListIteratorBase* ptr)
{
    ptr->~ListIteratorBase();
}

static void RegisterListIteratorBase(asIScriptEngine* engine)
{
    // ListIteratorBase::~ListIteratorBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("ListIteratorBase", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ListIteratorBase_Destructor), asCALL_CDECL_OBJFIRST);
}

// ListNodeBase::~ListNodeBase() | Implicitly-declared
static void ListNodeBase_Destructor(ListNodeBase* ptr)
{
    ptr->~ListNodeBase();
}

static void RegisterListNodeBase(asIScriptEngine* engine)
{
    // ListNodeBase::~ListNodeBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("ListNodeBase", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ListNodeBase_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterListView(asIScriptEngine* engine)
{
}

static void RegisterLocalization(asIScriptEngine* engine)
{
}

static void RegisterLog(asIScriptEngine* engine)
{
}

static void RegisterLogicComponent(asIScriptEngine* engine)
{
}

static void RegisterMaterial(asIScriptEngine* engine)
{
}

// MaterialShaderParameter::~MaterialShaderParameter() | Implicitly-declared
static void MaterialShaderParameter_Destructor(MaterialShaderParameter* ptr)
{
    ptr->~MaterialShaderParameter();
}

static void RegisterMaterialShaderParameter(asIScriptEngine* engine)
{
    // MaterialShaderParameter::~MaterialShaderParameter() | Implicitly-declared
    engine->RegisterObjectBehaviour("MaterialShaderParameter", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(MaterialShaderParameter_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterMatrix2(asIScriptEngine* engine)
{
}

static void RegisterMatrix3(asIScriptEngine* engine)
{
}

static void RegisterMatrix3x4(asIScriptEngine* engine)
{
}

static void RegisterMatrix4(asIScriptEngine* engine)
{
}

static void RegisterMemoryBuffer(asIScriptEngine* engine)
{
}

static void RegisterMenu(asIScriptEngine* engine)
{
}

static void RegisterMessageBox(asIScriptEngine* engine)
{
}

static void RegisterModel(asIScriptEngine* engine)
{
}

// ModelMorph::~ModelMorph() | Implicitly-declared
static void ModelMorph_Destructor(ModelMorph* ptr)
{
    ptr->~ModelMorph();
}

static void RegisterModelMorph(asIScriptEngine* engine)
{
    // ModelMorph::~ModelMorph() | Implicitly-declared
    engine->RegisterObjectBehaviour("ModelMorph", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ModelMorph_Destructor), asCALL_CDECL_OBJFIRST);
}

// Mutex::~Mutex() | File: ../Core/Mutex.h
static void Mutex_Destructor(Mutex* ptr)
{
    ptr->~Mutex();
}

static void RegisterMutex(asIScriptEngine* engine)
{
    // Mutex::~Mutex() | File: ../Core/Mutex.h
    engine->RegisterObjectBehaviour("Mutex", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Mutex_Destructor), asCALL_CDECL_OBJFIRST);
}

// MutexLock::~MutexLock() | File: ../Core/Mutex.h
static void MutexLock_Destructor(MutexLock* ptr)
{
    ptr->~MutexLock();
}

static void RegisterMutexLock(asIScriptEngine* engine)
{
    // MutexLock::~MutexLock() | File: ../Core/Mutex.h
    engine->RegisterObjectBehaviour("MutexLock", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(MutexLock_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterNamedPipe(asIScriptEngine* engine)
{
}

// NetworkState::~NetworkState() | Implicitly-declared
static void NetworkState_Destructor(NetworkState* ptr)
{
    ptr->~NetworkState();
}

static void RegisterNetworkState(asIScriptEngine* engine)
{
    // NetworkState::~NetworkState() | Implicitly-declared
    engine->RegisterObjectBehaviour("NetworkState", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(NetworkState_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterNode(asIScriptEngine* engine)
{
}

// NodeImpl::~NodeImpl() | Implicitly-declared
static void NodeImpl_Destructor(NodeImpl* ptr)
{
    ptr->~NodeImpl();
}

static void RegisterNodeImpl(asIScriptEngine* engine)
{
    // NodeImpl::~NodeImpl() | Implicitly-declared
    engine->RegisterObjectBehaviour("NodeImpl", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(NodeImpl_Destructor), asCALL_CDECL_OBJFIRST);
}

// NodeReplicationState::~NodeReplicationState() | Implicitly-declared
static void NodeReplicationState_Destructor(NodeReplicationState* ptr)
{
    ptr->~NodeReplicationState();
}

static void RegisterNodeReplicationState(asIScriptEngine* engine)
{
    // NodeReplicationState::~NodeReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("NodeReplicationState", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(NodeReplicationState_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterObject(asIScriptEngine* engine)
{
}

static void RegisterObjectAnimation(asIScriptEngine* engine)
{
}

static void RegisterObjectFactory(asIScriptEngine* engine)
{
}

// OcclusionBatch::~OcclusionBatch() | Implicitly-declared
static void OcclusionBatch_Destructor(OcclusionBatch* ptr)
{
    ptr->~OcclusionBatch();
}

static void RegisterOcclusionBatch(asIScriptEngine* engine)
{
    // OcclusionBatch::~OcclusionBatch() | Implicitly-declared
    engine->RegisterObjectBehaviour("OcclusionBatch", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(OcclusionBatch_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterOcclusionBuffer(asIScriptEngine* engine)
{
}

// OcclusionBufferData::~OcclusionBufferData() | Implicitly-declared
static void OcclusionBufferData_Destructor(OcclusionBufferData* ptr)
{
    ptr->~OcclusionBufferData();
}

static void RegisterOcclusionBufferData(asIScriptEngine* engine)
{
    // OcclusionBufferData::~OcclusionBufferData() | Implicitly-declared
    engine->RegisterObjectBehaviour("OcclusionBufferData", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(OcclusionBufferData_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterOctant(asIScriptEngine* engine)
{
}

static void RegisterOctree(asIScriptEngine* engine)
{
}

// OctreeQueryResult::~OctreeQueryResult() | Implicitly-declared
static void OctreeQueryResult_Destructor(OctreeQueryResult* ptr)
{
    ptr->~OctreeQueryResult();
}

static void RegisterOctreeQueryResult(asIScriptEngine* engine)
{
    // OctreeQueryResult::~OctreeQueryResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("OctreeQueryResult", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(OctreeQueryResult_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterOggVorbisSoundStream(asIScriptEngine* engine)
{
}

static void RegisterPackageEntry(asIScriptEngine* engine)
{
}

static void RegisterPackageFile(asIScriptEngine* engine)
{
}

// Particle::~Particle() | Implicitly-declared
static void Particle_Destructor(Particle* ptr)
{
    ptr->~Particle();
}

static void RegisterParticle(asIScriptEngine* engine)
{
    // Particle::~Particle() | Implicitly-declared
    engine->RegisterObjectBehaviour("Particle", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Particle_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterParticleEffect(asIScriptEngine* engine)
{
}

static void RegisterParticleEmitter(asIScriptEngine* engine)
{
}

static void RegisterPass(asIScriptEngine* engine)
{
}

// PerThreadSceneResult::~PerThreadSceneResult() | Implicitly-declared
static void PerThreadSceneResult_Destructor(PerThreadSceneResult* ptr)
{
    ptr->~PerThreadSceneResult();
}

static void RegisterPerThreadSceneResult(asIScriptEngine* engine)
{
    // PerThreadSceneResult::~PerThreadSceneResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("PerThreadSceneResult", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(PerThreadSceneResult_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterPlane(asIScriptEngine* engine)
{
}

static void RegisterPointOctreeQuery(asIScriptEngine* engine)
{
}

// Polyhedron::~Polyhedron() noexcept=default | File: ../Math/Polyhedron.h
static void Polyhedron_Destructor(Polyhedron* ptr)
{
    ptr->~Polyhedron();
}

static void RegisterPolyhedron(asIScriptEngine* engine)
{
    // Polyhedron::~Polyhedron() noexcept=default | File: ../Math/Polyhedron.h
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Polyhedron_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterProfiler(asIScriptEngine* engine)
{
}

static void RegisterProfilerBlock(asIScriptEngine* engine)
{
}

static void RegisterProgressBar(asIScriptEngine* engine)
{
}

static void RegisterQuaternion(asIScriptEngine* engine)
{
}

static void RegisterRay(asIScriptEngine* engine)
{
}

static void RegisterRayOctreeQuery(asIScriptEngine* engine)
{
}

// RayQueryResult::~RayQueryResult() | Implicitly-declared
static void RayQueryResult_Destructor(RayQueryResult* ptr)
{
    ptr->~RayQueryResult();
}

static void RegisterRayQueryResult(asIScriptEngine* engine)
{
    // RayQueryResult::~RayQueryResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("RayQueryResult", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(RayQueryResult_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterRect(asIScriptEngine* engine)
{
}

// RefCount::~RefCount() | File: ../Container/RefCounted.h
static void RefCount_Destructor(RefCount* ptr)
{
    ptr->~RefCount();
}

static void RegisterRefCount(asIScriptEngine* engine)
{
    // RefCount::~RefCount() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RefCount", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(RefCount_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterRefCounted(asIScriptEngine* engine)
{
}

static void RegisterRenderPath(asIScriptEngine* engine)
{
}

// RenderPathCommand::~RenderPathCommand() | Implicitly-declared
static void RenderPathCommand_Destructor(RenderPathCommand* ptr)
{
    ptr->~RenderPathCommand();
}

static void RegisterRenderPathCommand(asIScriptEngine* engine)
{
    // RenderPathCommand::~RenderPathCommand() | Implicitly-declared
    engine->RegisterObjectBehaviour("RenderPathCommand", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(RenderPathCommand_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterRenderSurface(asIScriptEngine* engine)
{
}

// RenderTargetInfo::~RenderTargetInfo() | Implicitly-declared
static void RenderTargetInfo_Destructor(RenderTargetInfo* ptr)
{
    ptr->~RenderTargetInfo();
}

static void RegisterRenderTargetInfo(asIScriptEngine* engine)
{
    // RenderTargetInfo::~RenderTargetInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("RenderTargetInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(RenderTargetInfo_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterRenderer(asIScriptEngine* engine)
{
}

// ReplicationState::~ReplicationState() | Implicitly-declared
static void ReplicationState_Destructor(ReplicationState* ptr)
{
    ptr->~ReplicationState();
}

static void RegisterReplicationState(asIScriptEngine* engine)
{
    // ReplicationState::~ReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("ReplicationState", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ReplicationState_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterResource(asIScriptEngine* engine)
{
}

static void RegisterResourceCache(asIScriptEngine* engine)
{
}

// ResourceGroup::~ResourceGroup() | Implicitly-declared
static void ResourceGroup_Destructor(ResourceGroup* ptr)
{
    ptr->~ResourceGroup();
}

static void RegisterResourceGroup(asIScriptEngine* engine)
{
    // ResourceGroup::~ResourceGroup() | Implicitly-declared
    engine->RegisterObjectBehaviour("ResourceGroup", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ResourceGroup_Destructor), asCALL_CDECL_OBJFIRST);
}

// ResourceRef::~ResourceRef() | Implicitly-declared
static void ResourceRef_Destructor(ResourceRef* ptr)
{
    ptr->~ResourceRef();
}

static void RegisterResourceRef(asIScriptEngine* engine)
{
    // ResourceRef::~ResourceRef() | Implicitly-declared
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ResourceRef_Destructor), asCALL_CDECL_OBJFIRST);
}

// ResourceRefList::~ResourceRefList() | Implicitly-declared
static void ResourceRefList_Destructor(ResourceRefList* ptr)
{
    ptr->~ResourceRefList();
}

static void RegisterResourceRefList(asIScriptEngine* engine)
{
    // ResourceRefList::~ResourceRefList() | Implicitly-declared
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ResourceRefList_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterResourceRouter(asIScriptEngine* engine)
{
}

static void RegisterResourceWithMetadata(asIScriptEngine* engine)
{
}

static void RegisterRibbonTrail(asIScriptEngine* engine)
{
}

static void RegisterScene(asIScriptEngine* engine)
{
}

// ScenePassInfo::~ScenePassInfo() | Implicitly-declared
static void ScenePassInfo_Destructor(ScenePassInfo* ptr)
{
    ptr->~ScenePassInfo();
}

static void RegisterScenePassInfo(asIScriptEngine* engine)
{
    // ScenePassInfo::~ScenePassInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("ScenePassInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ScenePassInfo_Destructor), asCALL_CDECL_OBJFIRST);
}

// SceneReplicationState::~SceneReplicationState() | Implicitly-declared
static void SceneReplicationState_Destructor(SceneReplicationState* ptr)
{
    ptr->~SceneReplicationState();
}

static void RegisterSceneReplicationState(asIScriptEngine* engine)
{
    // SceneReplicationState::~SceneReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("SceneReplicationState", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(SceneReplicationState_Destructor), asCALL_CDECL_OBJFIRST);
}

// SceneResolver::~SceneResolver() | File: ../Scene/SceneResolver.h
static void SceneResolver_Destructor(SceneResolver* ptr)
{
    ptr->~SceneResolver();
}

static void RegisterSceneResolver(asIScriptEngine* engine)
{
    // SceneResolver::~SceneResolver() | File: ../Scene/SceneResolver.h
    engine->RegisterObjectBehaviour("SceneResolver", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(SceneResolver_Destructor), asCALL_CDECL_OBJFIRST);
}

// ScratchBuffer::~ScratchBuffer() | Implicitly-declared
static void ScratchBuffer_Destructor(ScratchBuffer* ptr)
{
    ptr->~ScratchBuffer();
}

static void RegisterScratchBuffer(asIScriptEngine* engine)
{
    // ScratchBuffer::~ScratchBuffer() | Implicitly-declared
    engine->RegisterObjectBehaviour("ScratchBuffer", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ScratchBuffer_Destructor), asCALL_CDECL_OBJFIRST);
}

// ScreenModeParams::~ScreenModeParams() | Implicitly-declared
static void ScreenModeParams_Destructor(ScreenModeParams* ptr)
{
    ptr->~ScreenModeParams();
}

static void RegisterScreenModeParams(asIScriptEngine* engine)
{
    // ScreenModeParams::~ScreenModeParams() | Implicitly-declared
    engine->RegisterObjectBehaviour("ScreenModeParams", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ScreenModeParams_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterScrollBar(asIScriptEngine* engine)
{
}

static void RegisterScrollView(asIScriptEngine* engine)
{
}

static void RegisterSerializable(asIScriptEngine* engine)
{
}

static void RegisterSerializer(asIScriptEngine* engine)
{
}

static void RegisterShader(asIScriptEngine* engine)
{
}

// ShaderParameter::~ShaderParameter() | Implicitly-declared
static void ShaderParameter_Destructor(ShaderParameter* ptr)
{
    ptr->~ShaderParameter();
}

static void RegisterShaderParameter(asIScriptEngine* engine)
{
    // ShaderParameter::~ShaderParameter() | Implicitly-declared
    engine->RegisterObjectBehaviour("ShaderParameter", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ShaderParameter_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterShaderParameterAnimationInfo(asIScriptEngine* engine)
{
}

static void RegisterShaderPrecache(asIScriptEngine* engine)
{
}

static void RegisterShaderVariation(asIScriptEngine* engine)
{
}

// ShadowBatchQueue::~ShadowBatchQueue() | Implicitly-declared
static void ShadowBatchQueue_Destructor(ShadowBatchQueue* ptr)
{
    ptr->~ShadowBatchQueue();
}

static void RegisterShadowBatchQueue(asIScriptEngine* engine)
{
    // ShadowBatchQueue::~ShadowBatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("ShadowBatchQueue", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ShadowBatchQueue_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterSkeleton(asIScriptEngine* engine)
{
}

static void RegisterSkybox(asIScriptEngine* engine)
{
}

static void RegisterSlider(asIScriptEngine* engine)
{
}

static void RegisterSmoothedTransform(asIScriptEngine* engine)
{
}

static void RegisterSound(asIScriptEngine* engine)
{
}

static void RegisterSoundListener(asIScriptEngine* engine)
{
}

static void RegisterSoundSource(asIScriptEngine* engine)
{
}

static void RegisterSoundSource3D(asIScriptEngine* engine)
{
}

static void RegisterSoundStream(asIScriptEngine* engine)
{
}

// SourceBatch::~SourceBatch() | File: ../Graphics/Drawable.h
static void SourceBatch_Destructor(SourceBatch* ptr)
{
    ptr->~SourceBatch();
}

static void RegisterSourceBatch(asIScriptEngine* engine)
{
    // SourceBatch::~SourceBatch() | File: ../Graphics/Drawable.h
    engine->RegisterObjectBehaviour("SourceBatch", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(SourceBatch_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterSphere(asIScriptEngine* engine)
{
}

static void RegisterSphereOctreeQuery(asIScriptEngine* engine)
{
}

// Spline::~Spline() | Implicitly-declared
static void Spline_Destructor(Spline* ptr)
{
    ptr->~Spline();
}

static void RegisterSpline(asIScriptEngine* engine)
{
    // Spline::~Spline() | Implicitly-declared
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Spline_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterSplinePath(asIScriptEngine* engine)
{
}

static void RegisterSprite(asIScriptEngine* engine)
{
}

static void RegisterStaticModel(asIScriptEngine* engine)
{
}

// StaticModelGeometryData::~StaticModelGeometryData() | Implicitly-declared
static void StaticModelGeometryData_Destructor(StaticModelGeometryData* ptr)
{
    ptr->~StaticModelGeometryData();
}

static void RegisterStaticModelGeometryData(asIScriptEngine* engine)
{
    // StaticModelGeometryData::~StaticModelGeometryData() | Implicitly-declared
    engine->RegisterObjectBehaviour("StaticModelGeometryData", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(StaticModelGeometryData_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterStaticModelGroup(asIScriptEngine* engine)
{
}

// StoredLogMessage::~StoredLogMessage() | Implicitly-declared
static void StoredLogMessage_Destructor(StoredLogMessage* ptr)
{
    ptr->~StoredLogMessage();
}

static void RegisterStoredLogMessage(asIScriptEngine* engine)
{
    // StoredLogMessage::~StoredLogMessage() | Implicitly-declared
    engine->RegisterObjectBehaviour("StoredLogMessage", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(StoredLogMessage_Destructor), asCALL_CDECL_OBJFIRST);
}

// String::~String() | File: ../Container/Str.h
static void String_Destructor(String* ptr)
{
    ptr->~String();
}

static void RegisterString(asIScriptEngine* engine)
{
    // String::~String() | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(String_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterStringHash(asIScriptEngine* engine)
{
}

// StringHashRegister::~StringHashRegister() | File: ../Core/StringHashRegister.h
static void StringHashRegister_Destructor(StringHashRegister* ptr)
{
    ptr->~StringHashRegister();
}

static void RegisterStringHashRegister(asIScriptEngine* engine)
{
    // StringHashRegister::~StringHashRegister() | File: ../Core/StringHashRegister.h
    engine->RegisterObjectBehaviour("StringHashRegister", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(StringHashRegister_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterTechnique(asIScriptEngine* engine)
{
}

// TechniqueEntry::~TechniqueEntry() noexcept=default | File: ../Graphics/Material.h
static void TechniqueEntry_Destructor(TechniqueEntry* ptr)
{
    ptr->~TechniqueEntry();
}

static void RegisterTechniqueEntry(asIScriptEngine* engine)
{
    // TechniqueEntry::~TechniqueEntry() noexcept=default | File: ../Graphics/Material.h
    engine->RegisterObjectBehaviour("TechniqueEntry", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(TechniqueEntry_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterTerrain(asIScriptEngine* engine)
{
}

static void RegisterTerrainPatch(asIScriptEngine* engine)
{
}

static void RegisterText(asIScriptEngine* engine)
{
}

static void RegisterText3D(asIScriptEngine* engine)
{
}

static void RegisterTexture(asIScriptEngine* engine)
{
}

static void RegisterTexture2D(asIScriptEngine* engine)
{
}

static void RegisterTexture2DArray(asIScriptEngine* engine)
{
}

static void RegisterTexture3D(asIScriptEngine* engine)
{
}

static void RegisterTextureCube(asIScriptEngine* engine)
{
}

static void RegisterTextureFrame(asIScriptEngine* engine)
{
}

static void RegisterTime(asIScriptEngine* engine)
{
}

static void RegisterTimer(asIScriptEngine* engine)
{
}

static void RegisterToolTip(asIScriptEngine* engine)
{
}

static void RegisterTouchState(asIScriptEngine* engine)
{
}

// TrailPoint::~TrailPoint() | Implicitly-declared
static void TrailPoint_Destructor(TrailPoint* ptr)
{
    ptr->~TrailPoint();
}

static void RegisterTrailPoint(asIScriptEngine* engine)
{
    // TrailPoint::~TrailPoint() | Implicitly-declared
    engine->RegisterObjectBehaviour("TrailPoint", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(TrailPoint_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterTypeInfo(asIScriptEngine* engine)
{
}

static void RegisterUI(asIScriptEngine* engine)
{
}

// UIBatch::~UIBatch() | Implicitly-declared
static void UIBatch_Destructor(UIBatch* ptr)
{
    ptr->~UIBatch();
}

static void RegisterUIBatch(asIScriptEngine* engine)
{
    // UIBatch::~UIBatch() | Implicitly-declared
    engine->RegisterObjectBehaviour("UIBatch", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(UIBatch_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterUIComponent(asIScriptEngine* engine)
{
}

static void RegisterUIElement(asIScriptEngine* engine)
{
}

static void RegisterUISelectable(asIScriptEngine* engine)
{
}

static void RegisterUnknownComponent(asIScriptEngine* engine)
{
}

// VAnimEventFrame::~VAnimEventFrame() | Implicitly-declared
static void VAnimEventFrame_Destructor(VAnimEventFrame* ptr)
{
    ptr->~VAnimEventFrame();
}

static void RegisterVAnimEventFrame(asIScriptEngine* engine)
{
    // VAnimEventFrame::~VAnimEventFrame() | Implicitly-declared
    engine->RegisterObjectBehaviour("VAnimEventFrame", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VAnimEventFrame_Destructor), asCALL_CDECL_OBJFIRST);
}

// VAnimKeyFrame::~VAnimKeyFrame() | Implicitly-declared
static void VAnimKeyFrame_Destructor(VAnimKeyFrame* ptr)
{
    ptr->~VAnimKeyFrame();
}

static void RegisterVAnimKeyFrame(asIScriptEngine* engine)
{
    // VAnimKeyFrame::~VAnimKeyFrame() | Implicitly-declared
    engine->RegisterObjectBehaviour("VAnimKeyFrame", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VAnimKeyFrame_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterValueAnimation(asIScriptEngine* engine)
{
}

static void RegisterValueAnimationInfo(asIScriptEngine* engine)
{
}

// Variant::~Variant() | File: ../Core/Variant.h
static void Variant_Destructor(Variant* ptr)
{
    ptr->~Variant();
}

static void RegisterVariant(asIScriptEngine* engine)
{
    // Variant::~Variant() | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Variant_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterVector2(asIScriptEngine* engine)
{
}

static void RegisterVector3(asIScriptEngine* engine)
{
}

static void RegisterVector4(asIScriptEngine* engine)
{
}

// VectorBase::~VectorBase() | Implicitly-declared
static void VectorBase_Destructor(VectorBase* ptr)
{
    ptr->~VectorBase();
}

static void RegisterVectorBase(asIScriptEngine* engine)
{
    // VectorBase::~VectorBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("VectorBase", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VectorBase_Destructor), asCALL_CDECL_OBJFIRST);
}

// VectorBuffer::~VectorBuffer() | Implicitly-declared
static void VectorBuffer_Destructor(VectorBuffer* ptr)
{
    ptr->~VectorBuffer();
}

static void RegisterVectorBuffer(asIScriptEngine* engine)
{
    // VectorBuffer::~VectorBuffer() | Implicitly-declared
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VectorBuffer_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterVertexBuffer(asIScriptEngine* engine)
{
}

// VertexBufferDesc::~VertexBufferDesc() | Implicitly-declared
static void VertexBufferDesc_Destructor(VertexBufferDesc* ptr)
{
    ptr->~VertexBufferDesc();
}

static void RegisterVertexBufferDesc(asIScriptEngine* engine)
{
    // VertexBufferDesc::~VertexBufferDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("VertexBufferDesc", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VertexBufferDesc_Destructor), asCALL_CDECL_OBJFIRST);
}

// VertexBufferMorph::~VertexBufferMorph() | Implicitly-declared
static void VertexBufferMorph_Destructor(VertexBufferMorph* ptr)
{
    ptr->~VertexBufferMorph();
}

static void RegisterVertexBufferMorph(asIScriptEngine* engine)
{
    // VertexBufferMorph::~VertexBufferMorph() | Implicitly-declared
    engine->RegisterObjectBehaviour("VertexBufferMorph", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VertexBufferMorph_Destructor), asCALL_CDECL_OBJFIRST);
}

// VertexElement::~VertexElement() | Implicitly-declared
static void VertexElement_Destructor(VertexElement* ptr)
{
    ptr->~VertexElement();
}

static void RegisterVertexElement(asIScriptEngine* engine)
{
    // VertexElement::~VertexElement() | Implicitly-declared
    engine->RegisterObjectBehaviour("VertexElement", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VertexElement_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterView(asIScriptEngine* engine)
{
}

static void RegisterView3D(asIScriptEngine* engine)
{
}

static void RegisterViewport(asIScriptEngine* engine)
{
}

static void RegisterWString(asIScriptEngine* engine)
{
}

static void RegisterWindow(asIScriptEngine* engine)
{
}

// WindowModeParams::~WindowModeParams() | Implicitly-declared
static void WindowModeParams_Destructor(WindowModeParams* ptr)
{
    ptr->~WindowModeParams();
}

static void RegisterWindowModeParams(asIScriptEngine* engine)
{
    // WindowModeParams::~WindowModeParams() | Implicitly-declared
    engine->RegisterObjectBehaviour("WindowModeParams", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(WindowModeParams_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterWorkItem(asIScriptEngine* engine)
{
}

static void RegisterWorkQueue(asIScriptEngine* engine)
{
}

// XMLElement::~XMLElement() | File: ../Resource/XMLElement.h
static void XMLElement_Destructor(XMLElement* ptr)
{
    ptr->~XMLElement();
}

static void RegisterXMLElement(asIScriptEngine* engine)
{
    // XMLElement::~XMLElement() | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(XMLElement_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterXMLFile(asIScriptEngine* engine)
{
}

// XPathQuery::~XPathQuery() | File: ../Resource/XMLElement.h
static void XPathQuery_Destructor(XPathQuery* ptr)
{
    ptr->~XPathQuery();
}

static void RegisterXPathQuery(asIScriptEngine* engine)
{
    // XPathQuery::~XPathQuery() | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XPathQuery", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(XPathQuery_Destructor), asCALL_CDECL_OBJFIRST);
}

// XPathResultSet::~XPathResultSet() | File: ../Resource/XMLElement.h
static void XPathResultSet_Destructor(XPathResultSet* ptr)
{
    ptr->~XPathResultSet();
}

static void RegisterXPathResultSet(asIScriptEngine* engine)
{
    // XPathResultSet::~XPathResultSet() | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XPathResultSet", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(XPathResultSet_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterZone(asIScriptEngine* engine)
{
}

#ifdef URHO3D_DATABASE

static void RegisterDatabase(asIScriptEngine* engine)
{
}

#endif // def URHO3D_DATABASE

#ifdef URHO3D_IK

static void RegisterIKConstraint(asIScriptEngine* engine)
{
}

static void RegisterIKEffector(asIScriptEngine* engine)
{
}

static void RegisterIKSolver(asIScriptEngine* engine)
{
}

#endif // def URHO3D_IK

#ifdef URHO3D_NAVIGATION

static void RegisterCrowdAgent(asIScriptEngine* engine)
{
}

static void RegisterCrowdManager(asIScriptEngine* engine)
{
}

static void RegisterCrowdObstacleAvoidanceParams(asIScriptEngine* engine)
{
}

static void RegisterDynamicNavBuildData(asIScriptEngine* engine)
{
}

static void RegisterDynamicNavigationMesh(asIScriptEngine* engine)
{
}

static void RegisterNavArea(asIScriptEngine* engine)
{
}

// NavAreaStub::~NavAreaStub() | Implicitly-declared
static void NavAreaStub_Destructor(NavAreaStub* ptr)
{
    ptr->~NavAreaStub();
}

static void RegisterNavAreaStub(asIScriptEngine* engine)
{
    // NavAreaStub::~NavAreaStub() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavAreaStub", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(NavAreaStub_Destructor), asCALL_CDECL_OBJFIRST);
}

// virtual NavBuildData::~NavBuildData() | File: ../Navigation/NavBuildData.h
static void NavBuildData_Destructor(NavBuildData* ptr)
{
    ptr->~NavBuildData();
}

static void RegisterNavBuildData(asIScriptEngine* engine)
{
    // virtual NavBuildData::~NavBuildData() | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectBehaviour("NavBuildData", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(NavBuildData_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterNavigable(asIScriptEngine* engine)
{
}

// NavigationGeometryInfo::~NavigationGeometryInfo() | Implicitly-declared
static void NavigationGeometryInfo_Destructor(NavigationGeometryInfo* ptr)
{
    ptr->~NavigationGeometryInfo();
}

static void RegisterNavigationGeometryInfo(asIScriptEngine* engine)
{
    // NavigationGeometryInfo::~NavigationGeometryInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavigationGeometryInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(NavigationGeometryInfo_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterNavigationMesh(asIScriptEngine* engine)
{
}

// NavigationPathPoint::~NavigationPathPoint() | Implicitly-declared
static void NavigationPathPoint_Destructor(NavigationPathPoint* ptr)
{
    ptr->~NavigationPathPoint();
}

static void RegisterNavigationPathPoint(asIScriptEngine* engine)
{
    // NavigationPathPoint::~NavigationPathPoint() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavigationPathPoint", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(NavigationPathPoint_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterObstacle(asIScriptEngine* engine)
{
}

static void RegisterOffMeshConnection(asIScriptEngine* engine)
{
}

// SimpleNavBuildData::~SimpleNavBuildData() override | File: ../Navigation/NavBuildData.h
static void SimpleNavBuildData_Destructor(SimpleNavBuildData* ptr)
{
    ptr->~SimpleNavBuildData();
}

static void RegisterSimpleNavBuildData(asIScriptEngine* engine)
{
    // SimpleNavBuildData::~SimpleNavBuildData() override | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectBehaviour("SimpleNavBuildData", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(SimpleNavBuildData_Destructor), asCALL_CDECL_OBJFIRST);
}

#endif // def URHO3D_NAVIGATION

#ifdef URHO3D_NETWORK

static void RegisterConnection(asIScriptEngine* engine)
{
}

static void RegisterHttpRequest(asIScriptEngine* engine)
{
}

static void RegisterNetwork(asIScriptEngine* engine)
{
}

static void RegisterNetworkPriority(asIScriptEngine* engine)
{
}

// PackageDownload::~PackageDownload() | Implicitly-declared
static void PackageDownload_Destructor(PackageDownload* ptr)
{
    ptr->~PackageDownload();
}

static void RegisterPackageDownload(asIScriptEngine* engine)
{
    // PackageDownload::~PackageDownload() | Implicitly-declared
    engine->RegisterObjectBehaviour("PackageDownload", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(PackageDownload_Destructor), asCALL_CDECL_OBJFIRST);
}

// PackageUpload::~PackageUpload() | Implicitly-declared
static void PackageUpload_Destructor(PackageUpload* ptr)
{
    ptr->~PackageUpload();
}

static void RegisterPackageUpload(asIScriptEngine* engine)
{
    // PackageUpload::~PackageUpload() | Implicitly-declared
    engine->RegisterObjectBehaviour("PackageUpload", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(PackageUpload_Destructor), asCALL_CDECL_OBJFIRST);
}

// RemoteEvent::~RemoteEvent() | Implicitly-declared
static void RemoteEvent_Destructor(RemoteEvent* ptr)
{
    ptr->~RemoteEvent();
}

static void RegisterRemoteEvent(asIScriptEngine* engine)
{
    // RemoteEvent::~RemoteEvent() | Implicitly-declared
    engine->RegisterObjectBehaviour("RemoteEvent", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(RemoteEvent_Destructor), asCALL_CDECL_OBJFIRST);
}

#endif // def URHO3D_NETWORK

#ifdef URHO3D_PHYSICS

static void RegisterCollisionGeometryData(asIScriptEngine* engine)
{
}

static void RegisterCollisionShape(asIScriptEngine* engine)
{
}

static void RegisterConstraint(asIScriptEngine* engine)
{
}

static void RegisterConvexData(asIScriptEngine* engine)
{
}

// DelayedWorldTransform::~DelayedWorldTransform() | Implicitly-declared
static void DelayedWorldTransform_Destructor(DelayedWorldTransform* ptr)
{
    ptr->~DelayedWorldTransform();
}

static void RegisterDelayedWorldTransform(asIScriptEngine* engine)
{
    // DelayedWorldTransform::~DelayedWorldTransform() | Implicitly-declared
    engine->RegisterObjectBehaviour("DelayedWorldTransform", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DelayedWorldTransform_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterGImpactMeshData(asIScriptEngine* engine)
{
}

static void RegisterHeightfieldData(asIScriptEngine* engine)
{
}

// ManifoldPair::~ManifoldPair() | Implicitly-declared
static void ManifoldPair_Destructor(ManifoldPair* ptr)
{
    ptr->~ManifoldPair();
}

static void RegisterManifoldPair(asIScriptEngine* engine)
{
    // ManifoldPair::~ManifoldPair() | Implicitly-declared
    engine->RegisterObjectBehaviour("ManifoldPair", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ManifoldPair_Destructor), asCALL_CDECL_OBJFIRST);
}

// PhysicsRaycastResult::~PhysicsRaycastResult() | Implicitly-declared
static void PhysicsRaycastResult_Destructor(PhysicsRaycastResult* ptr)
{
    ptr->~PhysicsRaycastResult();
}

static void RegisterPhysicsRaycastResult(asIScriptEngine* engine)
{
    // PhysicsRaycastResult::~PhysicsRaycastResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("PhysicsRaycastResult", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(PhysicsRaycastResult_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterPhysicsWorld(asIScriptEngine* engine)
{
}

// PhysicsWorldConfig::~PhysicsWorldConfig() | Implicitly-declared
static void PhysicsWorldConfig_Destructor(PhysicsWorldConfig* ptr)
{
    ptr->~PhysicsWorldConfig();
}

static void RegisterPhysicsWorldConfig(asIScriptEngine* engine)
{
    // PhysicsWorldConfig::~PhysicsWorldConfig() | Implicitly-declared
    engine->RegisterObjectBehaviour("PhysicsWorldConfig", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(PhysicsWorldConfig_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterRaycastVehicle(asIScriptEngine* engine)
{
}

static void RegisterRigidBody(asIScriptEngine* engine)
{
}

static void RegisterTriangleMeshData(asIScriptEngine* engine)
{
}

#endif // def URHO3D_PHYSICS

#ifdef URHO3D_URHO2D

static void RegisterAnimatedSprite2D(asIScriptEngine* engine)
{
}

static void RegisterAnimationSet2D(asIScriptEngine* engine)
{
}

static void RegisterCollisionBox2D(asIScriptEngine* engine)
{
}

static void RegisterCollisionChain2D(asIScriptEngine* engine)
{
}

static void RegisterCollisionCircle2D(asIScriptEngine* engine)
{
}

static void RegisterCollisionEdge2D(asIScriptEngine* engine)
{
}

static void RegisterCollisionPolygon2D(asIScriptEngine* engine)
{
}

static void RegisterCollisionShape2D(asIScriptEngine* engine)
{
}

static void RegisterConstraint2D(asIScriptEngine* engine)
{
}

static void RegisterConstraintDistance2D(asIScriptEngine* engine)
{
}

static void RegisterConstraintFriction2D(asIScriptEngine* engine)
{
}

static void RegisterConstraintGear2D(asIScriptEngine* engine)
{
}

static void RegisterConstraintMotor2D(asIScriptEngine* engine)
{
}

static void RegisterConstraintMouse2D(asIScriptEngine* engine)
{
}

static void RegisterConstraintPrismatic2D(asIScriptEngine* engine)
{
}

static void RegisterConstraintPulley2D(asIScriptEngine* engine)
{
}

static void RegisterConstraintRevolute2D(asIScriptEngine* engine)
{
}

static void RegisterConstraintRope2D(asIScriptEngine* engine)
{
}

static void RegisterConstraintWeld2D(asIScriptEngine* engine)
{
}

static void RegisterConstraintWheel2D(asIScriptEngine* engine)
{
}

// DelayedWorldTransform2D::~DelayedWorldTransform2D() | Implicitly-declared
static void DelayedWorldTransform2D_Destructor(DelayedWorldTransform2D* ptr)
{
    ptr->~DelayedWorldTransform2D();
}

static void RegisterDelayedWorldTransform2D(asIScriptEngine* engine)
{
    // DelayedWorldTransform2D::~DelayedWorldTransform2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("DelayedWorldTransform2D", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DelayedWorldTransform2D_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterDrawable2D(asIScriptEngine* engine)
{
}

// Particle2D::~Particle2D() | Implicitly-declared
static void Particle2D_Destructor(Particle2D* ptr)
{
    ptr->~Particle2D();
}

static void RegisterParticle2D(asIScriptEngine* engine)
{
    // Particle2D::~Particle2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("Particle2D", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Particle2D_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterParticleEffect2D(asIScriptEngine* engine)
{
}

static void RegisterParticleEmitter2D(asIScriptEngine* engine)
{
}

// PhysicsRaycastResult2D::~PhysicsRaycastResult2D() | Implicitly-declared
static void PhysicsRaycastResult2D_Destructor(PhysicsRaycastResult2D* ptr)
{
    ptr->~PhysicsRaycastResult2D();
}

static void RegisterPhysicsRaycastResult2D(asIScriptEngine* engine)
{
    // PhysicsRaycastResult2D::~PhysicsRaycastResult2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("PhysicsRaycastResult2D", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(PhysicsRaycastResult2D_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterPhysicsWorld2D(asIScriptEngine* engine)
{
}

static void RegisterPropertySet2D(asIScriptEngine* engine)
{
}

static void RegisterRenderer2D(asIScriptEngine* engine)
{
}

static void RegisterRigidBody2D(asIScriptEngine* engine)
{
}

// SourceBatch2D::~SourceBatch2D() | Implicitly-declared
static void SourceBatch2D_Destructor(SourceBatch2D* ptr)
{
    ptr->~SourceBatch2D();
}

static void RegisterSourceBatch2D(asIScriptEngine* engine)
{
    // SourceBatch2D::~SourceBatch2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("SourceBatch2D", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(SourceBatch2D_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterSprite2D(asIScriptEngine* engine)
{
}

static void RegisterSpriteSheet2D(asIScriptEngine* engine)
{
}

static void RegisterStaticSprite2D(asIScriptEngine* engine)
{
}

static void RegisterStretchableSprite2D(asIScriptEngine* engine)
{
}

static void RegisterTile2D(asIScriptEngine* engine)
{
}

static void RegisterTileMap2D(asIScriptEngine* engine)
{
}

static void RegisterTileMapInfo2D(asIScriptEngine* engine)
{
}

static void RegisterTileMapLayer2D(asIScriptEngine* engine)
{
}

static void RegisterTileMapObject2D(asIScriptEngine* engine)
{
}

static void RegisterTmxFile2D(asIScriptEngine* engine)
{
}

static void RegisterTmxImageLayer2D(asIScriptEngine* engine)
{
}

static void RegisterTmxLayer2D(asIScriptEngine* engine)
{
}

static void RegisterTmxObjectGroup2D(asIScriptEngine* engine)
{
}

static void RegisterTmxTileLayer2D(asIScriptEngine* engine)
{
}

// Vertex2D::~Vertex2D() | Implicitly-declared
static void Vertex2D_Destructor(Vertex2D* ptr)
{
    ptr->~Vertex2D();
}

static void RegisterVertex2D(asIScriptEngine* engine)
{
    // Vertex2D::~Vertex2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("Vertex2D", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Vertex2D_Destructor), asCALL_CDECL_OBJFIRST);
}

static void RegisterViewBatchInfo2D(asIScriptEngine* engine)
{
}

#endif // def URHO3D_URHO2D

void ASRegisterGeneratedClasses(asIScriptEngine* engine)
{
    RegisterAbstractFile(engine);
    RegisterAllContentOctreeQuery(engine);
    RegisterAllocatorBlock(engine);
    RegisterAllocatorNode(engine);
    RegisterAnimatable(engine);
    RegisterAnimatedModel(engine);
    RegisterAnimation(engine);
    RegisterAnimationControl(engine);
    RegisterAnimationController(engine);
    RegisterAnimationKeyFrame(engine);
    RegisterAnimationState(engine);
    RegisterAnimationStateTrack(engine);
    RegisterAnimationTrack(engine);
    RegisterAnimationTriggerPoint(engine);
    RegisterAreaAllocator(engine);
    RegisterAsyncProgress(engine);
    RegisterAttributeAccessor(engine);
    RegisterAttributeAnimationInfo(engine);
    RegisterAttributeHandle(engine);
    RegisterAttributeInfo(engine);
    RegisterAudio(engine);
    RegisterAutoProfileBlock(engine);
    RegisterBackgroundLoadItem(engine);
    RegisterBackgroundLoader(engine);
    RegisterBatch(engine);
    RegisterBatchGroup(engine);
    RegisterBatchGroupKey(engine);
    RegisterBatchQueue(engine);
    RegisterBiasParameters(engine);
    RegisterBillboard(engine);
    RegisterBillboardSet(engine);
    RegisterBone(engine);
    RegisterBorderImage(engine);
    RegisterBoundingBox(engine);
    RegisterBoxOctreeQuery(engine);
    RegisterBufferedSoundStream(engine);
    RegisterButton(engine);
    RegisterCamera(engine);
    RegisterCascadeParameters(engine);
    RegisterCharLocation(engine);
    RegisterCheckBox(engine);
    RegisterColor(engine);
    RegisterColorFrame(engine);
    RegisterComponent(engine);
    RegisterComponentReplicationState(engine);
    RegisterCompressedLevel(engine);
    RegisterCondition(engine);
    RegisterConsole(engine);
    RegisterConstantBuffer(engine);
    RegisterContext(engine);
    RegisterControls(engine);
    RegisterCursor(engine);
    RegisterCursorShapeInfo(engine);
    RegisterCustomGeometry(engine);
    RegisterCustomGeometryVertex(engine);
    RegisterCustomVariantValue(engine);
    RegisterDebugHud(engine);
    RegisterDebugLine(engine);
    RegisterDebugRenderer(engine);
    RegisterDebugTriangle(engine);
    RegisterDecal(engine);
    RegisterDecalSet(engine);
    RegisterDecalVertex(engine);
    RegisterDepthValue(engine);
    RegisterDeserializer(engine);
    RegisterDirtyBits(engine);
    RegisterDrawable(engine);
    RegisterDropDownList(engine);
    RegisterEngine(engine);
    RegisterEventHandler11Impl(engine);
    RegisterEventProfiler(engine);
    RegisterEventProfilerBlock(engine);
    RegisterEventReceiverGroup(engine);
    RegisterFile(engine);
    RegisterFileSelector(engine);
    RegisterFileSelectorEntry(engine);
    RegisterFileSystem(engine);
    RegisterFileWatcher(engine);
    RegisterFocusParameters(engine);
    RegisterFont(engine);
    RegisterFontFace(engine);
    RegisterFontFaceBitmap(engine);
    RegisterFontFaceFreeType(engine);
    RegisterFontGlyph(engine);
    RegisterFrameInfo(engine);
    RegisterFrustum(engine);
    RegisterFrustumOctreeQuery(engine);
    RegisterGPUObject(engine);
    RegisterGeometry(engine);
    RegisterGeometryDesc(engine);
    RegisterGlyphLocation(engine);
    RegisterGraphics(engine);
    RegisterHashBase(engine);
    RegisterHashIteratorBase(engine);
    RegisterHashNodeBase(engine);
    RegisterHiresTimer(engine);
    RegisterImage(engine);
    RegisterIndexBuffer(engine);
    RegisterIndexBufferDesc(engine);
    RegisterInput(engine);
    RegisterInstanceData(engine);
    RegisterIntRect(engine);
    RegisterIntVector2(engine);
    RegisterIntVector3(engine);
    RegisterJSONFile(engine);
    RegisterJSONValue(engine);
    RegisterJoystickState(engine);
    RegisterLight(engine);
    RegisterLightBatchQueue(engine);
    RegisterLightQueryResult(engine);
    RegisterLineEdit(engine);
    RegisterLinkedListNode(engine);
    RegisterListBase(engine);
    RegisterListIteratorBase(engine);
    RegisterListNodeBase(engine);
    RegisterListView(engine);
    RegisterLocalization(engine);
    RegisterLog(engine);
    RegisterLogicComponent(engine);
    RegisterMaterial(engine);
    RegisterMaterialShaderParameter(engine);
    RegisterMatrix2(engine);
    RegisterMatrix3(engine);
    RegisterMatrix3x4(engine);
    RegisterMatrix4(engine);
    RegisterMemoryBuffer(engine);
    RegisterMenu(engine);
    RegisterMessageBox(engine);
    RegisterModel(engine);
    RegisterModelMorph(engine);
    RegisterMutex(engine);
    RegisterMutexLock(engine);
    RegisterNamedPipe(engine);
    RegisterNetworkState(engine);
    RegisterNode(engine);
    RegisterNodeImpl(engine);
    RegisterNodeReplicationState(engine);
    RegisterObject(engine);
    RegisterObjectAnimation(engine);
    RegisterObjectFactory(engine);
    RegisterOcclusionBatch(engine);
    RegisterOcclusionBuffer(engine);
    RegisterOcclusionBufferData(engine);
    RegisterOctant(engine);
    RegisterOctree(engine);
    RegisterOctreeQueryResult(engine);
    RegisterOggVorbisSoundStream(engine);
    RegisterPackageEntry(engine);
    RegisterPackageFile(engine);
    RegisterParticle(engine);
    RegisterParticleEffect(engine);
    RegisterParticleEmitter(engine);
    RegisterPass(engine);
    RegisterPerThreadSceneResult(engine);
    RegisterPlane(engine);
    RegisterPointOctreeQuery(engine);
    RegisterPolyhedron(engine);
    RegisterProfiler(engine);
    RegisterProfilerBlock(engine);
    RegisterProgressBar(engine);
    RegisterQuaternion(engine);
    RegisterRay(engine);
    RegisterRayOctreeQuery(engine);
    RegisterRayQueryResult(engine);
    RegisterRect(engine);
    RegisterRefCount(engine);
    RegisterRefCounted(engine);
    RegisterRenderPath(engine);
    RegisterRenderPathCommand(engine);
    RegisterRenderSurface(engine);
    RegisterRenderTargetInfo(engine);
    RegisterRenderer(engine);
    RegisterReplicationState(engine);
    RegisterResource(engine);
    RegisterResourceCache(engine);
    RegisterResourceGroup(engine);
    RegisterResourceRef(engine);
    RegisterResourceRefList(engine);
    RegisterResourceRouter(engine);
    RegisterResourceWithMetadata(engine);
    RegisterRibbonTrail(engine);
    RegisterScene(engine);
    RegisterScenePassInfo(engine);
    RegisterSceneReplicationState(engine);
    RegisterSceneResolver(engine);
    RegisterScratchBuffer(engine);
    RegisterScreenModeParams(engine);
    RegisterScrollBar(engine);
    RegisterScrollView(engine);
    RegisterSerializable(engine);
    RegisterSerializer(engine);
    RegisterShader(engine);
    RegisterShaderParameter(engine);
    RegisterShaderParameterAnimationInfo(engine);
    RegisterShaderPrecache(engine);
    RegisterShaderVariation(engine);
    RegisterShadowBatchQueue(engine);
    RegisterSkeleton(engine);
    RegisterSkybox(engine);
    RegisterSlider(engine);
    RegisterSmoothedTransform(engine);
    RegisterSound(engine);
    RegisterSoundListener(engine);
    RegisterSoundSource(engine);
    RegisterSoundSource3D(engine);
    RegisterSoundStream(engine);
    RegisterSourceBatch(engine);
    RegisterSphere(engine);
    RegisterSphereOctreeQuery(engine);
    RegisterSpline(engine);
    RegisterSplinePath(engine);
    RegisterSprite(engine);
    RegisterStaticModel(engine);
    RegisterStaticModelGeometryData(engine);
    RegisterStaticModelGroup(engine);
    RegisterStoredLogMessage(engine);
    RegisterString(engine);
    RegisterStringHash(engine);
    RegisterStringHashRegister(engine);
    RegisterTechnique(engine);
    RegisterTechniqueEntry(engine);
    RegisterTerrain(engine);
    RegisterTerrainPatch(engine);
    RegisterText(engine);
    RegisterText3D(engine);
    RegisterTexture(engine);
    RegisterTexture2D(engine);
    RegisterTexture2DArray(engine);
    RegisterTexture3D(engine);
    RegisterTextureCube(engine);
    RegisterTextureFrame(engine);
    RegisterTime(engine);
    RegisterTimer(engine);
    RegisterToolTip(engine);
    RegisterTouchState(engine);
    RegisterTrailPoint(engine);
    RegisterTypeInfo(engine);
    RegisterUI(engine);
    RegisterUIBatch(engine);
    RegisterUIComponent(engine);
    RegisterUIElement(engine);
    RegisterUISelectable(engine);
    RegisterUnknownComponent(engine);
    RegisterVAnimEventFrame(engine);
    RegisterVAnimKeyFrame(engine);
    RegisterValueAnimation(engine);
    RegisterValueAnimationInfo(engine);
    RegisterVariant(engine);
    RegisterVector2(engine);
    RegisterVector3(engine);
    RegisterVector4(engine);
    RegisterVectorBase(engine);
    RegisterVectorBuffer(engine);
    RegisterVertexBuffer(engine);
    RegisterVertexBufferDesc(engine);
    RegisterVertexBufferMorph(engine);
    RegisterVertexElement(engine);
    RegisterView(engine);
    RegisterView3D(engine);
    RegisterViewport(engine);
    RegisterWString(engine);
    RegisterWindow(engine);
    RegisterWindowModeParams(engine);
    RegisterWorkItem(engine);
    RegisterWorkQueue(engine);
    RegisterXMLElement(engine);
    RegisterXMLFile(engine);
    RegisterXPathQuery(engine);
    RegisterXPathResultSet(engine);
    RegisterZone(engine);

#ifdef URHO3D_DATABASE
    RegisterDatabase(engine);
#endif

#ifdef URHO3D_IK
    RegisterIKConstraint(engine);
    RegisterIKEffector(engine);
    RegisterIKSolver(engine);
#endif

#ifdef URHO3D_NAVIGATION
    RegisterCrowdAgent(engine);
    RegisterCrowdManager(engine);
    RegisterCrowdObstacleAvoidanceParams(engine);
    RegisterDynamicNavBuildData(engine);
    RegisterDynamicNavigationMesh(engine);
    RegisterNavArea(engine);
    RegisterNavAreaStub(engine);
    RegisterNavBuildData(engine);
    RegisterNavigable(engine);
    RegisterNavigationGeometryInfo(engine);
    RegisterNavigationMesh(engine);
    RegisterNavigationPathPoint(engine);
    RegisterObstacle(engine);
    RegisterOffMeshConnection(engine);
    RegisterSimpleNavBuildData(engine);
#endif

#ifdef URHO3D_NETWORK
    RegisterConnection(engine);
    RegisterHttpRequest(engine);
    RegisterNetwork(engine);
    RegisterNetworkPriority(engine);
    RegisterPackageDownload(engine);
    RegisterPackageUpload(engine);
    RegisterRemoteEvent(engine);
#endif

#ifdef URHO3D_PHYSICS
    RegisterCollisionGeometryData(engine);
    RegisterCollisionShape(engine);
    RegisterConstraint(engine);
    RegisterConvexData(engine);
    RegisterDelayedWorldTransform(engine);
    RegisterGImpactMeshData(engine);
    RegisterHeightfieldData(engine);
    RegisterManifoldPair(engine);
    RegisterPhysicsRaycastResult(engine);
    RegisterPhysicsWorld(engine);
    RegisterPhysicsWorldConfig(engine);
    RegisterRaycastVehicle(engine);
    RegisterRigidBody(engine);
    RegisterTriangleMeshData(engine);
#endif

#ifdef URHO3D_URHO2D
    RegisterAnimatedSprite2D(engine);
    RegisterAnimationSet2D(engine);
    RegisterCollisionBox2D(engine);
    RegisterCollisionChain2D(engine);
    RegisterCollisionCircle2D(engine);
    RegisterCollisionEdge2D(engine);
    RegisterCollisionPolygon2D(engine);
    RegisterCollisionShape2D(engine);
    RegisterConstraint2D(engine);
    RegisterConstraintDistance2D(engine);
    RegisterConstraintFriction2D(engine);
    RegisterConstraintGear2D(engine);
    RegisterConstraintMotor2D(engine);
    RegisterConstraintMouse2D(engine);
    RegisterConstraintPrismatic2D(engine);
    RegisterConstraintPulley2D(engine);
    RegisterConstraintRevolute2D(engine);
    RegisterConstraintRope2D(engine);
    RegisterConstraintWeld2D(engine);
    RegisterConstraintWheel2D(engine);
    RegisterDelayedWorldTransform2D(engine);
    RegisterDrawable2D(engine);
    RegisterParticle2D(engine);
    RegisterParticleEffect2D(engine);
    RegisterParticleEmitter2D(engine);
    RegisterPhysicsRaycastResult2D(engine);
    RegisterPhysicsWorld2D(engine);
    RegisterPropertySet2D(engine);
    RegisterRenderer2D(engine);
    RegisterRigidBody2D(engine);
    RegisterSourceBatch2D(engine);
    RegisterSprite2D(engine);
    RegisterSpriteSheet2D(engine);
    RegisterStaticSprite2D(engine);
    RegisterStretchableSprite2D(engine);
    RegisterTile2D(engine);
    RegisterTileMap2D(engine);
    RegisterTileMapInfo2D(engine);
    RegisterTileMapLayer2D(engine);
    RegisterTileMapObject2D(engine);
    RegisterTmxFile2D(engine);
    RegisterTmxImageLayer2D(engine);
    RegisterTmxLayer2D(engine);
    RegisterTmxObjectGroup2D(engine);
    RegisterTmxTileLayer2D(engine);
    RegisterVertex2D(engine);
    RegisterViewBatchInfo2D(engine);
#endif
}

}
