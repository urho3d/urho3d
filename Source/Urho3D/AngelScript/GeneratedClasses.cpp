// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// class AbstractFile | File: ../IO/AbstractFile.h
static void Register_AbstractFile(asIScriptEngine* engine)
{
}

// class AllContentOctreeQuery | File: ../Graphics/OctreeQuery.h
static void Register_AllContentOctreeQuery(asIScriptEngine* engine)
{
}

// AllocatorBlock::~AllocatorBlock() | Implicitly-declared
static void AllocatorBlock_Destructor(AllocatorBlock* ptr)
{
    ptr->~AllocatorBlock();
}

// struct AllocatorBlock | File: ../Container/Allocator.h
static void Register_AllocatorBlock(asIScriptEngine* engine)
{
    // AllocatorBlock::~AllocatorBlock() | Implicitly-declared
    engine->RegisterObjectBehaviour("AllocatorBlock", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AllocatorBlock_Destructor), asCALL_CDECL_OBJFIRST);
}

// AllocatorNode::~AllocatorNode() | Implicitly-declared
static void AllocatorNode_Destructor(AllocatorNode* ptr)
{
    ptr->~AllocatorNode();
}

// struct AllocatorNode | File: ../Container/Allocator.h
static void Register_AllocatorNode(asIScriptEngine* engine)
{
    // AllocatorNode::~AllocatorNode() | Implicitly-declared
    engine->RegisterObjectBehaviour("AllocatorNode", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AllocatorNode_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Animatable | File: ../Scene/Animatable.h
static void Register_Animatable(asIScriptEngine* engine)
{
}

// class AnimatedModel | File: ../Graphics/AnimatedModel.h
static void Register_AnimatedModel(asIScriptEngine* engine)
{
}

// class Animation | File: ../Graphics/Animation.h
static void Register_Animation(asIScriptEngine* engine)
{
}

// struct AnimationControl | File: ../Graphics/AnimationController.h
static void Register_AnimationControl(asIScriptEngine* engine)
{
}

// class AnimationController | File: ../Graphics/AnimationController.h
static void Register_AnimationController(asIScriptEngine* engine)
{
}

// AnimationKeyFrame::~AnimationKeyFrame() | Implicitly-declared
static void AnimationKeyFrame_Destructor(AnimationKeyFrame* ptr)
{
    ptr->~AnimationKeyFrame();
}

// struct AnimationKeyFrame | File: ../Graphics/Animation.h
static void Register_AnimationKeyFrame(asIScriptEngine* engine)
{
    // AnimationKeyFrame::~AnimationKeyFrame() | Implicitly-declared
    engine->RegisterObjectBehaviour("AnimationKeyFrame", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AnimationKeyFrame_Destructor), asCALL_CDECL_OBJFIRST);
}

// class AnimationState | File: ../Graphics/AnimationState.h
static void Register_AnimationState(asIScriptEngine* engine)
{
}

// AnimationStateTrack::~AnimationStateTrack()
static void AnimationStateTrack_Destructor(AnimationStateTrack* ptr)
{
    ptr->~AnimationStateTrack();
}

// struct AnimationStateTrack | File: ../Graphics/AnimationState.h
static void Register_AnimationStateTrack(asIScriptEngine* engine)
{
    // AnimationStateTrack::~AnimationStateTrack()
    engine->RegisterObjectBehaviour("AnimationStateTrack", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AnimationStateTrack_Destructor), asCALL_CDECL_OBJFIRST);
}

// struct AnimationTrack | File: ../Graphics/Animation.h
static void Register_AnimationTrack(asIScriptEngine* engine)
{
}

// AnimationTriggerPoint::~AnimationTriggerPoint() | Implicitly-declared
static void AnimationTriggerPoint_Destructor(AnimationTriggerPoint* ptr)
{
    ptr->~AnimationTriggerPoint();
}

// struct AnimationTriggerPoint | File: ../Graphics/Animation.h
static void Register_AnimationTriggerPoint(asIScriptEngine* engine)
{
    // AnimationTriggerPoint::~AnimationTriggerPoint() | Implicitly-declared
    engine->RegisterObjectBehaviour("AnimationTriggerPoint", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AnimationTriggerPoint_Destructor), asCALL_CDECL_OBJFIRST);
}

// AreaAllocator::~AreaAllocator() | Implicitly-declared
static void AreaAllocator_Destructor(AreaAllocator* ptr)
{
    ptr->~AreaAllocator();
}

// class AreaAllocator | File: ../Math/AreaAllocator.h
static void Register_AreaAllocator(asIScriptEngine* engine)
{
    // AreaAllocator::~AreaAllocator() | Implicitly-declared
    engine->RegisterObjectBehaviour("AreaAllocator", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AreaAllocator_Destructor), asCALL_CDECL_OBJFIRST);
}

// AsyncProgress::~AsyncProgress() | Implicitly-declared
static void AsyncProgress_Destructor(AsyncProgress* ptr)
{
    ptr->~AsyncProgress();
}

// struct AsyncProgress | File: ../Scene/Scene.h
static void Register_AsyncProgress(asIScriptEngine* engine)
{
    // AsyncProgress::~AsyncProgress() | Implicitly-declared
    engine->RegisterObjectBehaviour("AsyncProgress", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AsyncProgress_Destructor), asCALL_CDECL_OBJFIRST);
}

// class AttributeAccessor | File: ../Core/Attribute.h
static void Register_AttributeAccessor(asIScriptEngine* engine)
{
}

// class AttributeAnimationInfo | File: ../Scene/Animatable.h
static void Register_AttributeAnimationInfo(asIScriptEngine* engine)
{
}

// struct AttributeHandle | File: ../Core/Attribute.h
static void Register_AttributeHandle(asIScriptEngine* engine)
{
}

// AttributeInfo::~AttributeInfo() | Implicitly-declared
static void AttributeInfo_Destructor(AttributeInfo* ptr)
{
    ptr->~AttributeInfo();
}

// struct AttributeInfo | File: ../Core/Attribute.h
static void Register_AttributeInfo(asIScriptEngine* engine)
{
    // AttributeInfo::~AttributeInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("AttributeInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(AttributeInfo_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Audio | File: ../Audio/Audio.h
static void Register_Audio(asIScriptEngine* engine)
{
}

// class AutoProfileBlock | File: ../Core/Profiler.h
static void Register_AutoProfileBlock(asIScriptEngine* engine)
{
}

// BackgroundLoadItem::~BackgroundLoadItem() | Implicitly-declared
static void BackgroundLoadItem_Destructor(BackgroundLoadItem* ptr)
{
    ptr->~BackgroundLoadItem();
}

// struct BackgroundLoadItem | File: ../Resource/BackgroundLoader.h
static void Register_BackgroundLoadItem(asIScriptEngine* engine)
{
    // BackgroundLoadItem::~BackgroundLoadItem() | Implicitly-declared
    engine->RegisterObjectBehaviour("BackgroundLoadItem", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(BackgroundLoadItem_Destructor), asCALL_CDECL_OBJFIRST);
}

// class BackgroundLoader | File: ../Resource/BackgroundLoader.h
static void Register_BackgroundLoader(asIScriptEngine* engine)
{
}

// Batch::~Batch() | Implicitly-declared
static void Batch_Destructor(Batch* ptr)
{
    ptr->~Batch();
}

// struct Batch | File: ../Graphics/Batch.h
static void Register_Batch(asIScriptEngine* engine)
{
    // Batch::~Batch() | Implicitly-declared
    engine->RegisterObjectBehaviour("Batch", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Batch_Destructor), asCALL_CDECL_OBJFIRST);
}

// BatchGroup::~BatchGroup()=default
static void BatchGroup_Destructor(BatchGroup* ptr)
{
    ptr->~BatchGroup();
}

// struct BatchGroup | File: ../Graphics/Batch.h
static void Register_BatchGroup(asIScriptEngine* engine)
{
    // BatchGroup::~BatchGroup()=default
    engine->RegisterObjectBehaviour("BatchGroup", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(BatchGroup_Destructor), asCALL_CDECL_OBJFIRST);
}

// BatchGroupKey::~BatchGroupKey() | Implicitly-declared
static void BatchGroupKey_Destructor(BatchGroupKey* ptr)
{
    ptr->~BatchGroupKey();
}

// struct BatchGroupKey | File: ../Graphics/Batch.h
static void Register_BatchGroupKey(asIScriptEngine* engine)
{
    // BatchGroupKey::~BatchGroupKey() | Implicitly-declared
    engine->RegisterObjectBehaviour("BatchGroupKey", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(BatchGroupKey_Destructor), asCALL_CDECL_OBJFIRST);
}

// BatchQueue::~BatchQueue() | Implicitly-declared
static void BatchQueue_Destructor(BatchQueue* ptr)
{
    ptr->~BatchQueue();
}

// struct BatchQueue | File: ../Graphics/Batch.h
static void Register_BatchQueue(asIScriptEngine* engine)
{
    // BatchQueue::~BatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("BatchQueue", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(BatchQueue_Destructor), asCALL_CDECL_OBJFIRST);
}

// struct BiasParameters | File: ../Graphics/Light.h
static void Register_BiasParameters(asIScriptEngine* engine)
{
}

// struct Billboard | File: ../Graphics/BillboardSet.h
static void Register_Billboard(asIScriptEngine* engine)
{
}

// class BillboardSet | File: ../Graphics/BillboardSet.h
static void Register_BillboardSet(asIScriptEngine* engine)
{
}

// struct Bone | File: ../Graphics/Skeleton.h
static void Register_Bone(asIScriptEngine* engine)
{
}

// class BorderImage | File: ../UI/BorderImage.h
static void Register_BorderImage(asIScriptEngine* engine)
{
}

// class BoundingBox | File: ../Math/BoundingBox.h
static void Register_BoundingBox(asIScriptEngine* engine)
{
}

// class BoxOctreeQuery | File: ../Graphics/OctreeQuery.h
static void Register_BoxOctreeQuery(asIScriptEngine* engine)
{
}

// class BufferedSoundStream | File: ../Audio/BufferedSoundStream.h
static void Register_BufferedSoundStream(asIScriptEngine* engine)
{
}

// class Button | File: ../UI/Button.h
static void Register_Button(asIScriptEngine* engine)
{
}

// class Camera | File: ../Graphics/Camera.h
static void Register_Camera(asIScriptEngine* engine)
{
}

// struct CascadeParameters | File: ../Graphics/Light.h
static void Register_CascadeParameters(asIScriptEngine* engine)
{
}

// CharLocation::~CharLocation() | Implicitly-declared
static void CharLocation_Destructor(CharLocation* ptr)
{
    ptr->~CharLocation();
}

// struct CharLocation | File: ../UI/Text.h
static void Register_CharLocation(asIScriptEngine* engine)
{
    // CharLocation::~CharLocation() | Implicitly-declared
    engine->RegisterObjectBehaviour("CharLocation", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(CharLocation_Destructor), asCALL_CDECL_OBJFIRST);
}

// class CheckBox | File: ../UI/CheckBox.h
static void Register_CheckBox(asIScriptEngine* engine)
{
}

// class Color | File: ../Math/Color.h
static void Register_Color(asIScriptEngine* engine)
{
}

// struct ColorFrame | File: ../Graphics/ParticleEffect.h
static void Register_ColorFrame(asIScriptEngine* engine)
{
}

// class Component | File: ../Scene/Component.h
static void Register_Component(asIScriptEngine* engine)
{
}

// ComponentReplicationState::~ComponentReplicationState() | Implicitly-declared
static void ComponentReplicationState_Destructor(ComponentReplicationState* ptr)
{
    ptr->~ComponentReplicationState();
}

// struct ComponentReplicationState | File: ../Scene/ReplicationState.h
static void Register_ComponentReplicationState(asIScriptEngine* engine)
{
    // ComponentReplicationState::~ComponentReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("ComponentReplicationState", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ComponentReplicationState_Destructor), asCALL_CDECL_OBJFIRST);
}

// CompressedLevel::~CompressedLevel() | Implicitly-declared
static void CompressedLevel_Destructor(CompressedLevel* ptr)
{
    ptr->~CompressedLevel();
}

// struct CompressedLevel | File: ../Resource/Image.h
static void Register_CompressedLevel(asIScriptEngine* engine)
{
    // CompressedLevel::~CompressedLevel() | Implicitly-declared
    engine->RegisterObjectBehaviour("CompressedLevel", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(CompressedLevel_Destructor), asCALL_CDECL_OBJFIRST);
}

// Condition::~Condition()
static void Condition_Destructor(Condition* ptr)
{
    ptr->~Condition();
}

// class Condition | File: ../Core/Condition.h
static void Register_Condition(asIScriptEngine* engine)
{
    // Condition::~Condition()
    engine->RegisterObjectBehaviour("Condition", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Condition_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Console | File: ../Engine/Console.h
static void Register_Console(asIScriptEngine* engine)
{
}

// class ConstantBuffer | File: ../Graphics/ConstantBuffer.h
static void Register_ConstantBuffer(asIScriptEngine* engine)
{
}

// class Context | File: ../Core/Context.h
static void Register_Context(asIScriptEngine* engine)
{
}

// Controls::~Controls()
static void Controls_Destructor(Controls* ptr)
{
    ptr->~Controls();
}

// class Controls | File: ../Input/Controls.h
static void Register_Controls(asIScriptEngine* engine)
{
    // Controls::~Controls()
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Controls_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Cursor | File: ../UI/Cursor.h
static void Register_Cursor(asIScriptEngine* engine)
{
}

// CursorShapeInfo::~CursorShapeInfo() | Implicitly-declared
static void CursorShapeInfo_Destructor(CursorShapeInfo* ptr)
{
    ptr->~CursorShapeInfo();
}

// struct CursorShapeInfo | File: ../UI/Cursor.h
static void Register_CursorShapeInfo(asIScriptEngine* engine)
{
    // CursorShapeInfo::~CursorShapeInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("CursorShapeInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(CursorShapeInfo_Destructor), asCALL_CDECL_OBJFIRST);
}

// class CustomGeometry | File: ../Graphics/CustomGeometry.h
static void Register_CustomGeometry(asIScriptEngine* engine)
{
}

// struct CustomGeometryVertex | File: ../Graphics/CustomGeometry.h
static void Register_CustomGeometryVertex(asIScriptEngine* engine)
{
}

// class CustomVariantValue | File: ../Core/Variant.h
static void Register_CustomVariantValue(asIScriptEngine* engine)
{
}

// class DebugHud | File: ../Engine/DebugHud.h
static void Register_DebugHud(asIScriptEngine* engine)
{
}

// DebugLine::~DebugLine() | Implicitly-declared
static void DebugLine_Destructor(DebugLine* ptr)
{
    ptr->~DebugLine();
}

// struct DebugLine | File: ../Graphics/DebugRenderer.h
static void Register_DebugLine(asIScriptEngine* engine)
{
    // DebugLine::~DebugLine() | Implicitly-declared
    engine->RegisterObjectBehaviour("DebugLine", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DebugLine_Destructor), asCALL_CDECL_OBJFIRST);
}

// class DebugRenderer | File: ../Graphics/DebugRenderer.h
static void Register_DebugRenderer(asIScriptEngine* engine)
{
}

// DebugTriangle::~DebugTriangle() | Implicitly-declared
static void DebugTriangle_Destructor(DebugTriangle* ptr)
{
    ptr->~DebugTriangle();
}

// struct DebugTriangle | File: ../Graphics/DebugRenderer.h
static void Register_DebugTriangle(asIScriptEngine* engine)
{
    // DebugTriangle::~DebugTriangle() | Implicitly-declared
    engine->RegisterObjectBehaviour("DebugTriangle", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DebugTriangle_Destructor), asCALL_CDECL_OBJFIRST);
}

// Decal::~Decal() | Implicitly-declared
static void Decal_Destructor(Decal* ptr)
{
    ptr->~Decal();
}

// struct Decal | File: ../Graphics/DecalSet.h
static void Register_Decal(asIScriptEngine* engine)
{
    // Decal::~Decal() | Implicitly-declared
    engine->RegisterObjectBehaviour("Decal", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Decal_Destructor), asCALL_CDECL_OBJFIRST);
}

// class DecalSet | File: ../Graphics/DecalSet.h
static void Register_DecalSet(asIScriptEngine* engine)
{
}

// DecalVertex::~DecalVertex() | Implicitly-declared
static void DecalVertex_Destructor(DecalVertex* ptr)
{
    ptr->~DecalVertex();
}

// struct DecalVertex | File: ../Graphics/DecalSet.h
static void Register_DecalVertex(asIScriptEngine* engine)
{
    // DecalVertex::~DecalVertex() | Implicitly-declared
    engine->RegisterObjectBehaviour("DecalVertex", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DecalVertex_Destructor), asCALL_CDECL_OBJFIRST);
}

// struct DepthValue | File: ../Graphics/OcclusionBuffer.h
static void Register_DepthValue(asIScriptEngine* engine)
{
}

// class Deserializer | File: ../IO/Deserializer.h
static void Register_Deserializer(asIScriptEngine* engine)
{
}

// DirtyBits::~DirtyBits() | Implicitly-declared
static void DirtyBits_Destructor(DirtyBits* ptr)
{
    ptr->~DirtyBits();
}

// struct DirtyBits | File: ../Scene/ReplicationState.h
static void Register_DirtyBits(asIScriptEngine* engine)
{
    // DirtyBits::~DirtyBits() | Implicitly-declared
    engine->RegisterObjectBehaviour("DirtyBits", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DirtyBits_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Drawable | File: ../Graphics/Drawable.h
static void Register_Drawable(asIScriptEngine* engine)
{
}

// class DropDownList | File: ../UI/DropDownList.h
static void Register_DropDownList(asIScriptEngine* engine)
{
}

// class Engine | File: ../Engine/Engine.h
static void Register_Engine(asIScriptEngine* engine)
{
}

// class EventHandler11Impl | File: ../Core/Object.h
static void Register_EventHandler11Impl(asIScriptEngine* engine)
{
}

// class EventProfiler | File: ../Core/EventProfiler.h
static void Register_EventProfiler(asIScriptEngine* engine)
{
}

// class EventProfilerBlock | File: ../Core/EventProfiler.h
static void Register_EventProfilerBlock(asIScriptEngine* engine)
{
}

// class EventReceiverGroup | File: ../Core/Context.h
static void Register_EventReceiverGroup(asIScriptEngine* engine)
{
}

// class File | File: ../IO/File.h
static void Register_File(asIScriptEngine* engine)
{
}

// class FileSelector | File: ../UI/FileSelector.h
static void Register_FileSelector(asIScriptEngine* engine)
{
}

// FileSelectorEntry::~FileSelectorEntry() | Implicitly-declared
static void FileSelectorEntry_Destructor(FileSelectorEntry* ptr)
{
    ptr->~FileSelectorEntry();
}

// struct FileSelectorEntry | File: ../UI/FileSelector.h
static void Register_FileSelectorEntry(asIScriptEngine* engine)
{
    // FileSelectorEntry::~FileSelectorEntry() | Implicitly-declared
    engine->RegisterObjectBehaviour("FileSelectorEntry", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(FileSelectorEntry_Destructor), asCALL_CDECL_OBJFIRST);
}

// class FileSystem | File: ../IO/FileSystem.h
static void Register_FileSystem(asIScriptEngine* engine)
{
}

// class FileWatcher | File: ../IO/FileWatcher.h
static void Register_FileWatcher(asIScriptEngine* engine)
{
}

// struct FocusParameters | File: ../Graphics/Light.h
static void Register_FocusParameters(asIScriptEngine* engine)
{
}

// class Font | File: ../UI/Font.h
static void Register_Font(asIScriptEngine* engine)
{
}

// class FontFace | File: ../UI/FontFace.h
static void Register_FontFace(asIScriptEngine* engine)
{
}

// class FontFaceBitmap | File: ../UI/FontFaceBitmap.h
static void Register_FontFaceBitmap(asIScriptEngine* engine)
{
}

// class FontFaceFreeType | File: ../UI/FontFaceFreeType.h
static void Register_FontFaceFreeType(asIScriptEngine* engine)
{
}

// FontGlyph::~FontGlyph() | Implicitly-declared
static void FontGlyph_Destructor(FontGlyph* ptr)
{
    ptr->~FontGlyph();
}

// struct FontGlyph | File: ../UI/FontFace.h
static void Register_FontGlyph(asIScriptEngine* engine)
{
    // FontGlyph::~FontGlyph() | Implicitly-declared
    engine->RegisterObjectBehaviour("FontGlyph", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(FontGlyph_Destructor), asCALL_CDECL_OBJFIRST);
}

// FrameInfo::~FrameInfo() | Implicitly-declared
static void FrameInfo_Destructor(FrameInfo* ptr)
{
    ptr->~FrameInfo();
}

// struct FrameInfo | File: ../Graphics/Drawable.h
static void Register_FrameInfo(asIScriptEngine* engine)
{
    // FrameInfo::~FrameInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("FrameInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(FrameInfo_Destructor), asCALL_CDECL_OBJFIRST);
}

// Frustum::~Frustum() | Implicitly-declared
static void Frustum_Destructor(Frustum* ptr)
{
    ptr->~Frustum();
}

// class Frustum | File: ../Math/Frustum.h
static void Register_Frustum(asIScriptEngine* engine)
{
    // Frustum::~Frustum() | Implicitly-declared
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Frustum_Destructor), asCALL_CDECL_OBJFIRST);
}

// class FrustumOctreeQuery | File: ../Graphics/OctreeQuery.h
static void Register_FrustumOctreeQuery(asIScriptEngine* engine)
{
}

// virtual GPUObject::~GPUObject()
static void GPUObject_Destructor(GPUObject* ptr)
{
    ptr->~GPUObject();
}

// class GPUObject | File: ../Graphics/GPUObject.h
static void Register_GPUObject(asIScriptEngine* engine)
{
    // virtual GPUObject::~GPUObject()
    engine->RegisterObjectBehaviour("GPUObject", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(GPUObject_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Geometry | File: ../Graphics/Geometry.h
static void Register_Geometry(asIScriptEngine* engine)
{
}

// GeometryDesc::~GeometryDesc() | Implicitly-declared
static void GeometryDesc_Destructor(GeometryDesc* ptr)
{
    ptr->~GeometryDesc();
}

// struct GeometryDesc | File: ../Graphics/Model.h
static void Register_GeometryDesc(asIScriptEngine* engine)
{
    // GeometryDesc::~GeometryDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("GeometryDesc", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(GeometryDesc_Destructor), asCALL_CDECL_OBJFIRST);
}

// struct GlyphLocation | File: ../UI/Text.h
static void Register_GlyphLocation(asIScriptEngine* engine)
{
}

// class Graphics | File: ../Graphics/Graphics.h
static void Register_Graphics(asIScriptEngine* engine)
{
}

// HashBase::~HashBase() | Implicitly-declared
static void HashBase_Destructor(HashBase* ptr)
{
    ptr->~HashBase();
}

// class HashBase | File: ../Container/HashBase.h
static void Register_HashBase(asIScriptEngine* engine)
{
    // HashBase::~HashBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("HashBase", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(HashBase_Destructor), asCALL_CDECL_OBJFIRST);
}

// HashIteratorBase::~HashIteratorBase() | Implicitly-declared
static void HashIteratorBase_Destructor(HashIteratorBase* ptr)
{
    ptr->~HashIteratorBase();
}

// struct HashIteratorBase | File: ../Container/HashBase.h
static void Register_HashIteratorBase(asIScriptEngine* engine)
{
    // HashIteratorBase::~HashIteratorBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("HashIteratorBase", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(HashIteratorBase_Destructor), asCALL_CDECL_OBJFIRST);
}

// HashNodeBase::~HashNodeBase() | Implicitly-declared
static void HashNodeBase_Destructor(HashNodeBase* ptr)
{
    ptr->~HashNodeBase();
}

// struct HashNodeBase | File: ../Container/HashBase.h
static void Register_HashNodeBase(asIScriptEngine* engine)
{
    // HashNodeBase::~HashNodeBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("HashNodeBase", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(HashNodeBase_Destructor), asCALL_CDECL_OBJFIRST);
}

// HiresTimer::~HiresTimer() | Implicitly-declared
static void HiresTimer_Destructor(HiresTimer* ptr)
{
    ptr->~HiresTimer();
}

// class HiresTimer | File: ../Core/Timer.h
static void Register_HiresTimer(asIScriptEngine* engine)
{
    // HiresTimer::~HiresTimer() | Implicitly-declared
    engine->RegisterObjectBehaviour("HiresTimer", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(HiresTimer_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Image | File: ../Resource/Image.h
static void Register_Image(asIScriptEngine* engine)
{
}

// class IndexBuffer | File: ../Graphics/IndexBuffer.h
static void Register_IndexBuffer(asIScriptEngine* engine)
{
}

// IndexBufferDesc::~IndexBufferDesc() | Implicitly-declared
static void IndexBufferDesc_Destructor(IndexBufferDesc* ptr)
{
    ptr->~IndexBufferDesc();
}

// struct IndexBufferDesc | File: ../Graphics/Model.h
static void Register_IndexBufferDesc(asIScriptEngine* engine)
{
    // IndexBufferDesc::~IndexBufferDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("IndexBufferDesc", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(IndexBufferDesc_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Input | File: ../Input/Input.h
static void Register_Input(asIScriptEngine* engine)
{
}

// InstanceData::~InstanceData() | Implicitly-declared
static void InstanceData_Destructor(InstanceData* ptr)
{
    ptr->~InstanceData();
}

// struct InstanceData | File: ../Graphics/Batch.h
static void Register_InstanceData(asIScriptEngine* engine)
{
    // InstanceData::~InstanceData() | Implicitly-declared
    engine->RegisterObjectBehaviour("InstanceData", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(InstanceData_Destructor), asCALL_CDECL_OBJFIRST);
}

// class IntRect | File: ../Math/Rect.h
static void Register_IntRect(asIScriptEngine* engine)
{
}

// class IntVector2 | File: ../Math/Vector2.h
static void Register_IntVector2(asIScriptEngine* engine)
{
}

// class IntVector3 | File: ../Math/Vector3.h
static void Register_IntVector3(asIScriptEngine* engine)
{
}

// class JSONFile | File: ../Resource/JSONFile.h
static void Register_JSONFile(asIScriptEngine* engine)
{
}

// JSONValue::~JSONValue()
static void JSONValue_Destructor(JSONValue* ptr)
{
    ptr->~JSONValue();
}

// class JSONValue | File: ../Resource/JSONValue.h
static void Register_JSONValue(asIScriptEngine* engine)
{
    // JSONValue::~JSONValue()
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(JSONValue_Destructor), asCALL_CDECL_OBJFIRST);
}

// struct JoystickState | File: ../Input/Input.h
static void Register_JoystickState(asIScriptEngine* engine)
{
}

// class Light | File: ../Graphics/Light.h
static void Register_Light(asIScriptEngine* engine)
{
}

// LightBatchQueue::~LightBatchQueue() | Implicitly-declared
static void LightBatchQueue_Destructor(LightBatchQueue* ptr)
{
    ptr->~LightBatchQueue();
}

// struct LightBatchQueue | File: ../Graphics/Batch.h
static void Register_LightBatchQueue(asIScriptEngine* engine)
{
    // LightBatchQueue::~LightBatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("LightBatchQueue", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(LightBatchQueue_Destructor), asCALL_CDECL_OBJFIRST);
}

// LightQueryResult::~LightQueryResult() | Implicitly-declared
static void LightQueryResult_Destructor(LightQueryResult* ptr)
{
    ptr->~LightQueryResult();
}

// struct LightQueryResult | File: ../Graphics/View.h
static void Register_LightQueryResult(asIScriptEngine* engine)
{
    // LightQueryResult::~LightQueryResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("LightQueryResult", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(LightQueryResult_Destructor), asCALL_CDECL_OBJFIRST);
}

// class LineEdit | File: ../UI/LineEdit.h
static void Register_LineEdit(asIScriptEngine* engine)
{
}

// LinkedListNode::~LinkedListNode() | Implicitly-declared
static void LinkedListNode_Destructor(LinkedListNode* ptr)
{
    ptr->~LinkedListNode();
}

// struct LinkedListNode | File: ../Container/LinkedList.h
static void Register_LinkedListNode(asIScriptEngine* engine)
{
    // LinkedListNode::~LinkedListNode() | Implicitly-declared
    engine->RegisterObjectBehaviour("LinkedListNode", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(LinkedListNode_Destructor), asCALL_CDECL_OBJFIRST);
}

// ListBase::~ListBase() | Implicitly-declared
static void ListBase_Destructor(ListBase* ptr)
{
    ptr->~ListBase();
}

// class ListBase | File: ../Container/ListBase.h
static void Register_ListBase(asIScriptEngine* engine)
{
    // ListBase::~ListBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("ListBase", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ListBase_Destructor), asCALL_CDECL_OBJFIRST);
}

// ListIteratorBase::~ListIteratorBase() | Implicitly-declared
static void ListIteratorBase_Destructor(ListIteratorBase* ptr)
{
    ptr->~ListIteratorBase();
}

// struct ListIteratorBase | File: ../Container/ListBase.h
static void Register_ListIteratorBase(asIScriptEngine* engine)
{
    // ListIteratorBase::~ListIteratorBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("ListIteratorBase", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ListIteratorBase_Destructor), asCALL_CDECL_OBJFIRST);
}

// ListNodeBase::~ListNodeBase() | Implicitly-declared
static void ListNodeBase_Destructor(ListNodeBase* ptr)
{
    ptr->~ListNodeBase();
}

// struct ListNodeBase | File: ../Container/ListBase.h
static void Register_ListNodeBase(asIScriptEngine* engine)
{
    // ListNodeBase::~ListNodeBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("ListNodeBase", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ListNodeBase_Destructor), asCALL_CDECL_OBJFIRST);
}

// class ListView | File: ../UI/ListView.h
static void Register_ListView(asIScriptEngine* engine)
{
}

// class Localization | File: ../Resource/Localization.h
static void Register_Localization(asIScriptEngine* engine)
{
}

// class Log | File: ../IO/Log.h
static void Register_Log(asIScriptEngine* engine)
{
}

// class LogicComponent | File: ../Scene/LogicComponent.h
static void Register_LogicComponent(asIScriptEngine* engine)
{
}

// class Material | File: ../Graphics/Material.h
static void Register_Material(asIScriptEngine* engine)
{
}

// MaterialShaderParameter::~MaterialShaderParameter() | Implicitly-declared
static void MaterialShaderParameter_Destructor(MaterialShaderParameter* ptr)
{
    ptr->~MaterialShaderParameter();
}

// struct MaterialShaderParameter | File: ../Graphics/Material.h
static void Register_MaterialShaderParameter(asIScriptEngine* engine)
{
    // MaterialShaderParameter::~MaterialShaderParameter() | Implicitly-declared
    engine->RegisterObjectBehaviour("MaterialShaderParameter", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(MaterialShaderParameter_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Matrix2 | File: ../Math/Matrix2.h
static void Register_Matrix2(asIScriptEngine* engine)
{
}

// class Matrix3 | File: ../Math/Matrix3.h
static void Register_Matrix3(asIScriptEngine* engine)
{
}

// class Matrix3x4 | File: ../Math/Matrix3x4.h
static void Register_Matrix3x4(asIScriptEngine* engine)
{
}

// class Matrix4 | File: ../Math/Matrix4.h
static void Register_Matrix4(asIScriptEngine* engine)
{
}

// class MemoryBuffer | File: ../IO/MemoryBuffer.h
static void Register_MemoryBuffer(asIScriptEngine* engine)
{
}

// class Menu | File: ../UI/Menu.h
static void Register_Menu(asIScriptEngine* engine)
{
}

// class MessageBox | File: ../UI/MessageBox.h
static void Register_MessageBox(asIScriptEngine* engine)
{
}

// class Model | File: ../Graphics/Model.h
static void Register_Model(asIScriptEngine* engine)
{
}

// ModelMorph::~ModelMorph() | Implicitly-declared
static void ModelMorph_Destructor(ModelMorph* ptr)
{
    ptr->~ModelMorph();
}

// struct ModelMorph | File: ../Graphics/Model.h
static void Register_ModelMorph(asIScriptEngine* engine)
{
    // ModelMorph::~ModelMorph() | Implicitly-declared
    engine->RegisterObjectBehaviour("ModelMorph", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ModelMorph_Destructor), asCALL_CDECL_OBJFIRST);
}

// Mutex::~Mutex()
static void Mutex_Destructor(Mutex* ptr)
{
    ptr->~Mutex();
}

// class Mutex | File: ../Core/Mutex.h
static void Register_Mutex(asIScriptEngine* engine)
{
    // Mutex::~Mutex()
    engine->RegisterObjectBehaviour("Mutex", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Mutex_Destructor), asCALL_CDECL_OBJFIRST);
}

// MutexLock::~MutexLock()
static void MutexLock_Destructor(MutexLock* ptr)
{
    ptr->~MutexLock();
}

// class MutexLock | File: ../Core/Mutex.h
static void Register_MutexLock(asIScriptEngine* engine)
{
    // MutexLock::~MutexLock()
    engine->RegisterObjectBehaviour("MutexLock", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(MutexLock_Destructor), asCALL_CDECL_OBJFIRST);
}

// class NamedPipe | File: ../IO/NamedPipe.h
static void Register_NamedPipe(asIScriptEngine* engine)
{
}

// NetworkState::~NetworkState() | Implicitly-declared
static void NetworkState_Destructor(NetworkState* ptr)
{
    ptr->~NetworkState();
}

// struct NetworkState | File: ../Scene/ReplicationState.h
static void Register_NetworkState(asIScriptEngine* engine)
{
    // NetworkState::~NetworkState() | Implicitly-declared
    engine->RegisterObjectBehaviour("NetworkState", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(NetworkState_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Node | File: ../Scene/Node.h
static void Register_Node(asIScriptEngine* engine)
{
}

// NodeImpl::~NodeImpl() | Implicitly-declared
static void NodeImpl_Destructor(NodeImpl* ptr)
{
    ptr->~NodeImpl();
}

// struct NodeImpl | File: ../Scene/Node.h
static void Register_NodeImpl(asIScriptEngine* engine)
{
    // NodeImpl::~NodeImpl() | Implicitly-declared
    engine->RegisterObjectBehaviour("NodeImpl", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(NodeImpl_Destructor), asCALL_CDECL_OBJFIRST);
}

// NodeReplicationState::~NodeReplicationState() | Implicitly-declared
static void NodeReplicationState_Destructor(NodeReplicationState* ptr)
{
    ptr->~NodeReplicationState();
}

// struct NodeReplicationState | File: ../Scene/ReplicationState.h
static void Register_NodeReplicationState(asIScriptEngine* engine)
{
    // NodeReplicationState::~NodeReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("NodeReplicationState", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(NodeReplicationState_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Object | File: ../Core/Object.h
static void Register_Object(asIScriptEngine* engine)
{
}

// class ObjectAnimation | File: ../Scene/ObjectAnimation.h
static void Register_ObjectAnimation(asIScriptEngine* engine)
{
}

// class ObjectFactory | File: ../Core/Object.h
static void Register_ObjectFactory(asIScriptEngine* engine)
{
}

// OcclusionBatch::~OcclusionBatch() | Implicitly-declared
static void OcclusionBatch_Destructor(OcclusionBatch* ptr)
{
    ptr->~OcclusionBatch();
}

// struct OcclusionBatch | File: ../Graphics/OcclusionBuffer.h
static void Register_OcclusionBatch(asIScriptEngine* engine)
{
    // OcclusionBatch::~OcclusionBatch() | Implicitly-declared
    engine->RegisterObjectBehaviour("OcclusionBatch", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(OcclusionBatch_Destructor), asCALL_CDECL_OBJFIRST);
}

// class OcclusionBuffer | File: ../Graphics/OcclusionBuffer.h
static void Register_OcclusionBuffer(asIScriptEngine* engine)
{
}

// OcclusionBufferData::~OcclusionBufferData() | Implicitly-declared
static void OcclusionBufferData_Destructor(OcclusionBufferData* ptr)
{
    ptr->~OcclusionBufferData();
}

// struct OcclusionBufferData | File: ../Graphics/OcclusionBuffer.h
static void Register_OcclusionBufferData(asIScriptEngine* engine)
{
    // OcclusionBufferData::~OcclusionBufferData() | Implicitly-declared
    engine->RegisterObjectBehaviour("OcclusionBufferData", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(OcclusionBufferData_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Octant | File: ../Graphics/Octree.h
static void Register_Octant(asIScriptEngine* engine)
{
}

// class Octree | File: ../Graphics/Octree.h
static void Register_Octree(asIScriptEngine* engine)
{
}

// OctreeQueryResult::~OctreeQueryResult() | Implicitly-declared
static void OctreeQueryResult_Destructor(OctreeQueryResult* ptr)
{
    ptr->~OctreeQueryResult();
}

// struct OctreeQueryResult | File: ../Graphics/OctreeQuery.h
static void Register_OctreeQueryResult(asIScriptEngine* engine)
{
    // OctreeQueryResult::~OctreeQueryResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("OctreeQueryResult", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(OctreeQueryResult_Destructor), asCALL_CDECL_OBJFIRST);
}

// class OggVorbisSoundStream | File: ../Audio/OggVorbisSoundStream.h
static void Register_OggVorbisSoundStream(asIScriptEngine* engine)
{
}

// struct PackageEntry | File: ../IO/PackageFile.h
static void Register_PackageEntry(asIScriptEngine* engine)
{
}

// class PackageFile | File: ../IO/PackageFile.h
static void Register_PackageFile(asIScriptEngine* engine)
{
}

// Particle::~Particle() | Implicitly-declared
static void Particle_Destructor(Particle* ptr)
{
    ptr->~Particle();
}

// struct Particle | File: ../Graphics/ParticleEmitter.h
static void Register_Particle(asIScriptEngine* engine)
{
    // Particle::~Particle() | Implicitly-declared
    engine->RegisterObjectBehaviour("Particle", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Particle_Destructor), asCALL_CDECL_OBJFIRST);
}

// class ParticleEffect | File: ../Graphics/ParticleEffect.h
static void Register_ParticleEffect(asIScriptEngine* engine)
{
}

// class ParticleEmitter | File: ../Graphics/ParticleEmitter.h
static void Register_ParticleEmitter(asIScriptEngine* engine)
{
}

// class Pass | File: ../Graphics/Technique.h
static void Register_Pass(asIScriptEngine* engine)
{
}

// PerThreadSceneResult::~PerThreadSceneResult() | Implicitly-declared
static void PerThreadSceneResult_Destructor(PerThreadSceneResult* ptr)
{
    ptr->~PerThreadSceneResult();
}

// struct PerThreadSceneResult | File: ../Graphics/View.h
static void Register_PerThreadSceneResult(asIScriptEngine* engine)
{
    // PerThreadSceneResult::~PerThreadSceneResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("PerThreadSceneResult", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(PerThreadSceneResult_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Plane | File: ../Math/Plane.h
static void Register_Plane(asIScriptEngine* engine)
{
}

// class PointOctreeQuery | File: ../Graphics/OctreeQuery.h
static void Register_PointOctreeQuery(asIScriptEngine* engine)
{
}

// Polyhedron::~Polyhedron() noexcept=default
static void Polyhedron_Destructor(Polyhedron* ptr)
{
    ptr->~Polyhedron();
}

// class Polyhedron | File: ../Math/Polyhedron.h
static void Register_Polyhedron(asIScriptEngine* engine)
{
    // Polyhedron::~Polyhedron() noexcept=default
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Polyhedron_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Profiler | File: ../Core/Profiler.h
static void Register_Profiler(asIScriptEngine* engine)
{
}

// class ProfilerBlock | File: ../Core/Profiler.h
static void Register_ProfilerBlock(asIScriptEngine* engine)
{
}

// class ProgressBar | File: ../UI/ProgressBar.h
static void Register_ProgressBar(asIScriptEngine* engine)
{
}

// class Quaternion | File: ../Math/Quaternion.h
static void Register_Quaternion(asIScriptEngine* engine)
{
}

// class Ray | File: ../Math/Ray.h
static void Register_Ray(asIScriptEngine* engine)
{
}

// class RayOctreeQuery | File: ../Graphics/OctreeQuery.h
static void Register_RayOctreeQuery(asIScriptEngine* engine)
{
}

// RayQueryResult::~RayQueryResult() | Implicitly-declared
static void RayQueryResult_Destructor(RayQueryResult* ptr)
{
    ptr->~RayQueryResult();
}

// struct RayQueryResult | File: ../Graphics/OctreeQuery.h
static void Register_RayQueryResult(asIScriptEngine* engine)
{
    // RayQueryResult::~RayQueryResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("RayQueryResult", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(RayQueryResult_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Rect | File: ../Math/Rect.h
static void Register_Rect(asIScriptEngine* engine)
{
}

// RefCount::~RefCount()
static void RefCount_Destructor(RefCount* ptr)
{
    ptr->~RefCount();
}

// struct RefCount | File: ../Container/RefCounted.h
static void Register_RefCount(asIScriptEngine* engine)
{
    // RefCount::~RefCount()
    engine->RegisterObjectBehaviour("RefCount", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(RefCount_Destructor), asCALL_CDECL_OBJFIRST);
}

// class RefCounted | File: ../Container/RefCounted.h
static void Register_RefCounted(asIScriptEngine* engine)
{
}

// class RenderPath | File: ../Graphics/RenderPath.h
static void Register_RenderPath(asIScriptEngine* engine)
{
}

// RenderPathCommand::~RenderPathCommand() | Implicitly-declared
static void RenderPathCommand_Destructor(RenderPathCommand* ptr)
{
    ptr->~RenderPathCommand();
}

// struct RenderPathCommand | File: ../Graphics/RenderPath.h
static void Register_RenderPathCommand(asIScriptEngine* engine)
{
    // RenderPathCommand::~RenderPathCommand() | Implicitly-declared
    engine->RegisterObjectBehaviour("RenderPathCommand", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(RenderPathCommand_Destructor), asCALL_CDECL_OBJFIRST);
}

// class RenderSurface | File: ../Graphics/RenderSurface.h
static void Register_RenderSurface(asIScriptEngine* engine)
{
}

// RenderTargetInfo::~RenderTargetInfo() | Implicitly-declared
static void RenderTargetInfo_Destructor(RenderTargetInfo* ptr)
{
    ptr->~RenderTargetInfo();
}

// struct RenderTargetInfo | File: ../Graphics/RenderPath.h
static void Register_RenderTargetInfo(asIScriptEngine* engine)
{
    // RenderTargetInfo::~RenderTargetInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("RenderTargetInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(RenderTargetInfo_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Renderer | File: ../Graphics/Renderer.h
static void Register_Renderer(asIScriptEngine* engine)
{
}

// ReplicationState::~ReplicationState() | Implicitly-declared
static void ReplicationState_Destructor(ReplicationState* ptr)
{
    ptr->~ReplicationState();
}

// struct ReplicationState | File: ../Scene/ReplicationState.h
static void Register_ReplicationState(asIScriptEngine* engine)
{
    // ReplicationState::~ReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("ReplicationState", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ReplicationState_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Resource | File: ../Resource/Resource.h
static void Register_Resource(asIScriptEngine* engine)
{
}

// class ResourceCache | File: ../Resource/ResourceCache.h
static void Register_ResourceCache(asIScriptEngine* engine)
{
}

// ResourceGroup::~ResourceGroup() | Implicitly-declared
static void ResourceGroup_Destructor(ResourceGroup* ptr)
{
    ptr->~ResourceGroup();
}

// struct ResourceGroup | File: ../Resource/ResourceCache.h
static void Register_ResourceGroup(asIScriptEngine* engine)
{
    // ResourceGroup::~ResourceGroup() | Implicitly-declared
    engine->RegisterObjectBehaviour("ResourceGroup", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ResourceGroup_Destructor), asCALL_CDECL_OBJFIRST);
}

// ResourceRef::~ResourceRef() | Implicitly-declared
static void ResourceRef_Destructor(ResourceRef* ptr)
{
    ptr->~ResourceRef();
}

// struct ResourceRef | File: ../Core/Variant.h
static void Register_ResourceRef(asIScriptEngine* engine)
{
    // ResourceRef::~ResourceRef() | Implicitly-declared
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ResourceRef_Destructor), asCALL_CDECL_OBJFIRST);
}

// ResourceRefList::~ResourceRefList() | Implicitly-declared
static void ResourceRefList_Destructor(ResourceRefList* ptr)
{
    ptr->~ResourceRefList();
}

// struct ResourceRefList | File: ../Core/Variant.h
static void Register_ResourceRefList(asIScriptEngine* engine)
{
    // ResourceRefList::~ResourceRefList() | Implicitly-declared
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ResourceRefList_Destructor), asCALL_CDECL_OBJFIRST);
}

// class ResourceRouter | File: ../Resource/ResourceCache.h
static void Register_ResourceRouter(asIScriptEngine* engine)
{
}

// class ResourceWithMetadata | File: ../Resource/Resource.h
static void Register_ResourceWithMetadata(asIScriptEngine* engine)
{
}

// class RibbonTrail | File: ../Graphics/RibbonTrail.h
static void Register_RibbonTrail(asIScriptEngine* engine)
{
}

// class Scene | File: ../Scene/Scene.h
static void Register_Scene(asIScriptEngine* engine)
{
}

// ScenePassInfo::~ScenePassInfo() | Implicitly-declared
static void ScenePassInfo_Destructor(ScenePassInfo* ptr)
{
    ptr->~ScenePassInfo();
}

// struct ScenePassInfo | File: ../Graphics/View.h
static void Register_ScenePassInfo(asIScriptEngine* engine)
{
    // ScenePassInfo::~ScenePassInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("ScenePassInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ScenePassInfo_Destructor), asCALL_CDECL_OBJFIRST);
}

// SceneReplicationState::~SceneReplicationState() | Implicitly-declared
static void SceneReplicationState_Destructor(SceneReplicationState* ptr)
{
    ptr->~SceneReplicationState();
}

// struct SceneReplicationState | File: ../Scene/ReplicationState.h
static void Register_SceneReplicationState(asIScriptEngine* engine)
{
    // SceneReplicationState::~SceneReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("SceneReplicationState", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(SceneReplicationState_Destructor), asCALL_CDECL_OBJFIRST);
}

// SceneResolver::~SceneResolver()
static void SceneResolver_Destructor(SceneResolver* ptr)
{
    ptr->~SceneResolver();
}

// class SceneResolver | File: ../Scene/SceneResolver.h
static void Register_SceneResolver(asIScriptEngine* engine)
{
    // SceneResolver::~SceneResolver()
    engine->RegisterObjectBehaviour("SceneResolver", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(SceneResolver_Destructor), asCALL_CDECL_OBJFIRST);
}

// ScratchBuffer::~ScratchBuffer() | Implicitly-declared
static void ScratchBuffer_Destructor(ScratchBuffer* ptr)
{
    ptr->~ScratchBuffer();
}

// struct ScratchBuffer | File: ../Graphics/Graphics.h
static void Register_ScratchBuffer(asIScriptEngine* engine)
{
    // ScratchBuffer::~ScratchBuffer() | Implicitly-declared
    engine->RegisterObjectBehaviour("ScratchBuffer", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ScratchBuffer_Destructor), asCALL_CDECL_OBJFIRST);
}

// ScreenModeParams::~ScreenModeParams() | Implicitly-declared
static void ScreenModeParams_Destructor(ScreenModeParams* ptr)
{
    ptr->~ScreenModeParams();
}

// struct ScreenModeParams | File: ../Graphics/Graphics.h
static void Register_ScreenModeParams(asIScriptEngine* engine)
{
    // ScreenModeParams::~ScreenModeParams() | Implicitly-declared
    engine->RegisterObjectBehaviour("ScreenModeParams", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ScreenModeParams_Destructor), asCALL_CDECL_OBJFIRST);
}

// class ScrollBar | File: ../UI/ScrollBar.h
static void Register_ScrollBar(asIScriptEngine* engine)
{
}

// class ScrollView | File: ../UI/ScrollView.h
static void Register_ScrollView(asIScriptEngine* engine)
{
}

// class Serializable | File: ../Scene/Serializable.h
static void Register_Serializable(asIScriptEngine* engine)
{
}

// class Serializer | File: ../IO/Serializer.h
static void Register_Serializer(asIScriptEngine* engine)
{
}

// class Shader | File: ../Graphics/Shader.h
static void Register_Shader(asIScriptEngine* engine)
{
}

// ShaderParameter::~ShaderParameter() | Implicitly-declared
static void ShaderParameter_Destructor(ShaderParameter* ptr)
{
    ptr->~ShaderParameter();
}

// struct ShaderParameter | File: ../Graphics/ShaderVariation.h
static void Register_ShaderParameter(asIScriptEngine* engine)
{
    // ShaderParameter::~ShaderParameter() | Implicitly-declared
    engine->RegisterObjectBehaviour("ShaderParameter", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ShaderParameter_Destructor), asCALL_CDECL_OBJFIRST);
}

// class ShaderParameterAnimationInfo | File: ../Graphics/Material.h
static void Register_ShaderParameterAnimationInfo(asIScriptEngine* engine)
{
}

// class ShaderPrecache | File: ../Graphics/ShaderPrecache.h
static void Register_ShaderPrecache(asIScriptEngine* engine)
{
}

// class ShaderVariation | File: ../Graphics/ShaderVariation.h
static void Register_ShaderVariation(asIScriptEngine* engine)
{
}

// ShadowBatchQueue::~ShadowBatchQueue() | Implicitly-declared
static void ShadowBatchQueue_Destructor(ShadowBatchQueue* ptr)
{
    ptr->~ShadowBatchQueue();
}

// struct ShadowBatchQueue | File: ../Graphics/Batch.h
static void Register_ShadowBatchQueue(asIScriptEngine* engine)
{
    // ShadowBatchQueue::~ShadowBatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("ShadowBatchQueue", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ShadowBatchQueue_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Skeleton | File: ../Graphics/Skeleton.h
static void Register_Skeleton(asIScriptEngine* engine)
{
}

// class Skybox | File: ../Graphics/Skybox.h
static void Register_Skybox(asIScriptEngine* engine)
{
}

// class Slider | File: ../UI/Slider.h
static void Register_Slider(asIScriptEngine* engine)
{
}

// class SmoothedTransform | File: ../Scene/SmoothedTransform.h
static void Register_SmoothedTransform(asIScriptEngine* engine)
{
}

// class Sound | File: ../Audio/Sound.h
static void Register_Sound(asIScriptEngine* engine)
{
}

// class SoundListener | File: ../Audio/SoundListener.h
static void Register_SoundListener(asIScriptEngine* engine)
{
}

// class SoundSource | File: ../Audio/SoundSource.h
static void Register_SoundSource(asIScriptEngine* engine)
{
}

// class SoundSource3D | File: ../Audio/SoundSource3D.h
static void Register_SoundSource3D(asIScriptEngine* engine)
{
}

// class SoundStream | File: ../Audio/SoundStream.h
static void Register_SoundStream(asIScriptEngine* engine)
{
}

// SourceBatch::~SourceBatch()
static void SourceBatch_Destructor(SourceBatch* ptr)
{
    ptr->~SourceBatch();
}

// struct SourceBatch | File: ../Graphics/Drawable.h
static void Register_SourceBatch(asIScriptEngine* engine)
{
    // SourceBatch::~SourceBatch()
    engine->RegisterObjectBehaviour("SourceBatch", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(SourceBatch_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Sphere | File: ../Math/Sphere.h
static void Register_Sphere(asIScriptEngine* engine)
{
}

// class SphereOctreeQuery | File: ../Graphics/OctreeQuery.h
static void Register_SphereOctreeQuery(asIScriptEngine* engine)
{
}

// Spline::~Spline() | Implicitly-declared
static void Spline_Destructor(Spline* ptr)
{
    ptr->~Spline();
}

// class Spline | File: ../Core/Spline.h
static void Register_Spline(asIScriptEngine* engine)
{
    // Spline::~Spline() | Implicitly-declared
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Spline_Destructor), asCALL_CDECL_OBJFIRST);
}

// class SplinePath | File: ../Scene/SplinePath.h
static void Register_SplinePath(asIScriptEngine* engine)
{
}

// class Sprite | File: ../UI/Sprite.h
static void Register_Sprite(asIScriptEngine* engine)
{
}

// class StaticModel | File: ../Graphics/StaticModel.h
static void Register_StaticModel(asIScriptEngine* engine)
{
}

// StaticModelGeometryData::~StaticModelGeometryData() | Implicitly-declared
static void StaticModelGeometryData_Destructor(StaticModelGeometryData* ptr)
{
    ptr->~StaticModelGeometryData();
}

// struct StaticModelGeometryData | File: ../Graphics/StaticModel.h
static void Register_StaticModelGeometryData(asIScriptEngine* engine)
{
    // StaticModelGeometryData::~StaticModelGeometryData() | Implicitly-declared
    engine->RegisterObjectBehaviour("StaticModelGeometryData", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(StaticModelGeometryData_Destructor), asCALL_CDECL_OBJFIRST);
}

// class StaticModelGroup | File: ../Graphics/StaticModelGroup.h
static void Register_StaticModelGroup(asIScriptEngine* engine)
{
}

// StoredLogMessage::~StoredLogMessage() | Implicitly-declared
static void StoredLogMessage_Destructor(StoredLogMessage* ptr)
{
    ptr->~StoredLogMessage();
}

// struct StoredLogMessage | File: ../IO/Log.h
static void Register_StoredLogMessage(asIScriptEngine* engine)
{
    // StoredLogMessage::~StoredLogMessage() | Implicitly-declared
    engine->RegisterObjectBehaviour("StoredLogMessage", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(StoredLogMessage_Destructor), asCALL_CDECL_OBJFIRST);
}

// String::~String()
static void String_Destructor(String* ptr)
{
    ptr->~String();
}

// class String | File: ../Container/Str.h
static void Register_String(asIScriptEngine* engine)
{
    // String::~String()
    engine->RegisterObjectBehaviour("String", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(String_Destructor), asCALL_CDECL_OBJFIRST);
}

// class StringHash | File: ../Math/StringHash.h
static void Register_StringHash(asIScriptEngine* engine)
{
}

// StringHashRegister::~StringHashRegister()
static void StringHashRegister_Destructor(StringHashRegister* ptr)
{
    ptr->~StringHashRegister();
}

// class StringHashRegister | File: ../Core/StringHashRegister.h
static void Register_StringHashRegister(asIScriptEngine* engine)
{
    // StringHashRegister::~StringHashRegister()
    engine->RegisterObjectBehaviour("StringHashRegister", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(StringHashRegister_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Technique | File: ../Graphics/Technique.h
static void Register_Technique(asIScriptEngine* engine)
{
}

// TechniqueEntry::~TechniqueEntry() noexcept=default
static void TechniqueEntry_Destructor(TechniqueEntry* ptr)
{
    ptr->~TechniqueEntry();
}

// struct TechniqueEntry | File: ../Graphics/Material.h
static void Register_TechniqueEntry(asIScriptEngine* engine)
{
    // TechniqueEntry::~TechniqueEntry() noexcept=default
    engine->RegisterObjectBehaviour("TechniqueEntry", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(TechniqueEntry_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Terrain | File: ../Graphics/Terrain.h
static void Register_Terrain(asIScriptEngine* engine)
{
}

// class TerrainPatch | File: ../Graphics/TerrainPatch.h
static void Register_TerrainPatch(asIScriptEngine* engine)
{
}

// class Text | File: ../UI/Text.h
static void Register_Text(asIScriptEngine* engine)
{
}

// class Text3D | File: ../UI/Text3D.h
static void Register_Text3D(asIScriptEngine* engine)
{
}

// class Texture | File: ../Graphics/Texture.h
static void Register_Texture(asIScriptEngine* engine)
{
}

// class Texture2D | File: ../Graphics/Texture2D.h
static void Register_Texture2D(asIScriptEngine* engine)
{
}

// class Texture2DArray | File: ../Graphics/Texture2DArray.h
static void Register_Texture2DArray(asIScriptEngine* engine)
{
}

// class Texture3D | File: ../Graphics/Texture3D.h
static void Register_Texture3D(asIScriptEngine* engine)
{
}

// class TextureCube | File: ../Graphics/TextureCube.h
static void Register_TextureCube(asIScriptEngine* engine)
{
}

// struct TextureFrame | File: ../Graphics/ParticleEffect.h
static void Register_TextureFrame(asIScriptEngine* engine)
{
}

// class Time | File: ../Core/Timer.h
static void Register_Time(asIScriptEngine* engine)
{
}

// class Timer | File: ../Core/Timer.h
static void Register_Timer(asIScriptEngine* engine)
{
}

// class ToolTip | File: ../UI/ToolTip.h
static void Register_ToolTip(asIScriptEngine* engine)
{
}

// struct TouchState | File: ../Input/Input.h
static void Register_TouchState(asIScriptEngine* engine)
{
}

// TrailPoint::~TrailPoint() | Implicitly-declared
static void TrailPoint_Destructor(TrailPoint* ptr)
{
    ptr->~TrailPoint();
}

// struct TrailPoint | File: ../Graphics/RibbonTrail.h
static void Register_TrailPoint(asIScriptEngine* engine)
{
    // TrailPoint::~TrailPoint() | Implicitly-declared
    engine->RegisterObjectBehaviour("TrailPoint", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(TrailPoint_Destructor), asCALL_CDECL_OBJFIRST);
}

// class TypeInfo | File: ../Core/Object.h
static void Register_TypeInfo(asIScriptEngine* engine)
{
}

// class UI | File: ../UI/UI.h
static void Register_UI(asIScriptEngine* engine)
{
}

// UIBatch::~UIBatch() | Implicitly-declared
static void UIBatch_Destructor(UIBatch* ptr)
{
    ptr->~UIBatch();
}

// class UIBatch | File: ../UI/UIBatch.h
static void Register_UIBatch(asIScriptEngine* engine)
{
    // UIBatch::~UIBatch() | Implicitly-declared
    engine->RegisterObjectBehaviour("UIBatch", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(UIBatch_Destructor), asCALL_CDECL_OBJFIRST);
}

// class UIComponent | File: ../UI/UIComponent.h
static void Register_UIComponent(asIScriptEngine* engine)
{
}

// class UIElement | File: ../UI/UIElement.h
static void Register_UIElement(asIScriptEngine* engine)
{
}

// class UISelectable | File: ../UI/UISelectable.h
static void Register_UISelectable(asIScriptEngine* engine)
{
}

// class UnknownComponent | File: ../Scene/UnknownComponent.h
static void Register_UnknownComponent(asIScriptEngine* engine)
{
}

// VAnimEventFrame::~VAnimEventFrame() | Implicitly-declared
static void VAnimEventFrame_Destructor(VAnimEventFrame* ptr)
{
    ptr->~VAnimEventFrame();
}

// struct VAnimEventFrame | File: ../Scene/ValueAnimation.h
static void Register_VAnimEventFrame(asIScriptEngine* engine)
{
    // VAnimEventFrame::~VAnimEventFrame() | Implicitly-declared
    engine->RegisterObjectBehaviour("VAnimEventFrame", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VAnimEventFrame_Destructor), asCALL_CDECL_OBJFIRST);
}

// VAnimKeyFrame::~VAnimKeyFrame() | Implicitly-declared
static void VAnimKeyFrame_Destructor(VAnimKeyFrame* ptr)
{
    ptr->~VAnimKeyFrame();
}

// struct VAnimKeyFrame | File: ../Scene/ValueAnimation.h
static void Register_VAnimKeyFrame(asIScriptEngine* engine)
{
    // VAnimKeyFrame::~VAnimKeyFrame() | Implicitly-declared
    engine->RegisterObjectBehaviour("VAnimKeyFrame", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VAnimKeyFrame_Destructor), asCALL_CDECL_OBJFIRST);
}

// class ValueAnimation | File: ../Scene/ValueAnimation.h
static void Register_ValueAnimation(asIScriptEngine* engine)
{
}

// class ValueAnimationInfo | File: ../Scene/ValueAnimationInfo.h
static void Register_ValueAnimationInfo(asIScriptEngine* engine)
{
}

// Variant::~Variant()
static void Variant_Destructor(Variant* ptr)
{
    ptr->~Variant();
}

// class Variant | File: ../Core/Variant.h
static void Register_Variant(asIScriptEngine* engine)
{
    // Variant::~Variant()
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Variant_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Vector2 | File: ../Math/Vector2.h
static void Register_Vector2(asIScriptEngine* engine)
{
}

// class Vector3 | File: ../Math/Vector3.h
static void Register_Vector3(asIScriptEngine* engine)
{
}

// class Vector4 | File: ../Math/Vector4.h
static void Register_Vector4(asIScriptEngine* engine)
{
}

// VectorBase::~VectorBase() | Implicitly-declared
static void VectorBase_Destructor(VectorBase* ptr)
{
    ptr->~VectorBase();
}

// class VectorBase | File: ../Container/VectorBase.h
static void Register_VectorBase(asIScriptEngine* engine)
{
    // VectorBase::~VectorBase() | Implicitly-declared
    engine->RegisterObjectBehaviour("VectorBase", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VectorBase_Destructor), asCALL_CDECL_OBJFIRST);
}

// VectorBuffer::~VectorBuffer() | Implicitly-declared
static void VectorBuffer_Destructor(VectorBuffer* ptr)
{
    ptr->~VectorBuffer();
}

// class VectorBuffer | File: ../IO/VectorBuffer.h
static void Register_VectorBuffer(asIScriptEngine* engine)
{
    // VectorBuffer::~VectorBuffer() | Implicitly-declared
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VectorBuffer_Destructor), asCALL_CDECL_OBJFIRST);
}

// class VertexBuffer | File: ../Graphics/VertexBuffer.h
static void Register_VertexBuffer(asIScriptEngine* engine)
{
}

// VertexBufferDesc::~VertexBufferDesc() | Implicitly-declared
static void VertexBufferDesc_Destructor(VertexBufferDesc* ptr)
{
    ptr->~VertexBufferDesc();
}

// struct VertexBufferDesc | File: ../Graphics/Model.h
static void Register_VertexBufferDesc(asIScriptEngine* engine)
{
    // VertexBufferDesc::~VertexBufferDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("VertexBufferDesc", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VertexBufferDesc_Destructor), asCALL_CDECL_OBJFIRST);
}

// VertexBufferMorph::~VertexBufferMorph() | Implicitly-declared
static void VertexBufferMorph_Destructor(VertexBufferMorph* ptr)
{
    ptr->~VertexBufferMorph();
}

// struct VertexBufferMorph | File: ../Graphics/Model.h
static void Register_VertexBufferMorph(asIScriptEngine* engine)
{
    // VertexBufferMorph::~VertexBufferMorph() | Implicitly-declared
    engine->RegisterObjectBehaviour("VertexBufferMorph", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VertexBufferMorph_Destructor), asCALL_CDECL_OBJFIRST);
}

// VertexElement::~VertexElement() | Implicitly-declared
static void VertexElement_Destructor(VertexElement* ptr)
{
    ptr->~VertexElement();
}

// struct VertexElement | File: ../Graphics/GraphicsDefs.h
static void Register_VertexElement(asIScriptEngine* engine)
{
    // VertexElement::~VertexElement() | Implicitly-declared
    engine->RegisterObjectBehaviour("VertexElement", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VertexElement_Destructor), asCALL_CDECL_OBJFIRST);
}

// class View | File: ../Graphics/View.h
static void Register_View(asIScriptEngine* engine)
{
}

// class View3D | File: ../UI/View3D.h
static void Register_View3D(asIScriptEngine* engine)
{
}

// class Viewport | File: ../Graphics/Viewport.h
static void Register_Viewport(asIScriptEngine* engine)
{
}

// class WString | File: ../Container/Str.h
static void Register_WString(asIScriptEngine* engine)
{
}

// class Window | File: ../UI/Window.h
static void Register_Window(asIScriptEngine* engine)
{
}

// WindowModeParams::~WindowModeParams() | Implicitly-declared
static void WindowModeParams_Destructor(WindowModeParams* ptr)
{
    ptr->~WindowModeParams();
}

// struct WindowModeParams | File: ../Graphics/Graphics.h
static void Register_WindowModeParams(asIScriptEngine* engine)
{
    // WindowModeParams::~WindowModeParams() | Implicitly-declared
    engine->RegisterObjectBehaviour("WindowModeParams", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(WindowModeParams_Destructor), asCALL_CDECL_OBJFIRST);
}

// struct WorkItem | File: ../Core/WorkQueue.h
static void Register_WorkItem(asIScriptEngine* engine)
{
}

// class WorkQueue | File: ../Core/WorkQueue.h
static void Register_WorkQueue(asIScriptEngine* engine)
{
}

// XMLElement::~XMLElement()
static void XMLElement_Destructor(XMLElement* ptr)
{
    ptr->~XMLElement();
}

// class XMLElement | File: ../Resource/XMLElement.h
static void Register_XMLElement(asIScriptEngine* engine)
{
    // XMLElement::~XMLElement()
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(XMLElement_Destructor), asCALL_CDECL_OBJFIRST);
}

// class XMLFile | File: ../Resource/XMLFile.h
static void Register_XMLFile(asIScriptEngine* engine)
{
}

// XPathQuery::~XPathQuery()
static void XPathQuery_Destructor(XPathQuery* ptr)
{
    ptr->~XPathQuery();
}

// class XPathQuery | File: ../Resource/XMLElement.h
static void Register_XPathQuery(asIScriptEngine* engine)
{
    // XPathQuery::~XPathQuery()
    engine->RegisterObjectBehaviour("XPathQuery", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(XPathQuery_Destructor), asCALL_CDECL_OBJFIRST);
}

// XPathResultSet::~XPathResultSet()
static void XPathResultSet_Destructor(XPathResultSet* ptr)
{
    ptr->~XPathResultSet();
}

// class XPathResultSet | File: ../Resource/XMLElement.h
static void Register_XPathResultSet(asIScriptEngine* engine)
{
    // XPathResultSet::~XPathResultSet()
    engine->RegisterObjectBehaviour("XPathResultSet", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(XPathResultSet_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Zone | File: ../Graphics/Zone.h
static void Register_Zone(asIScriptEngine* engine)
{
}

#ifdef URHO3D_DATABASE

// class Database | File: ../Database/Database.h
static void Register_Database(asIScriptEngine* engine)
{
}

#endif // def URHO3D_DATABASE

#ifdef URHO3D_IK

// class IKConstraint | File: ../IK/IKConstraint.h
static void Register_IKConstraint(asIScriptEngine* engine)
{
}

// class IKEffector | File: ../IK/IKEffector.h
static void Register_IKEffector(asIScriptEngine* engine)
{
}

// class IKSolver | File: ../IK/IKSolver.h
static void Register_IKSolver(asIScriptEngine* engine)
{
}

#endif // def URHO3D_IK

#ifdef URHO3D_NAVIGATION

// class CrowdAgent | File: ../Navigation/CrowdAgent.h
static void Register_CrowdAgent(asIScriptEngine* engine)
{
}

// class CrowdManager | File: ../Navigation/CrowdManager.h
static void Register_CrowdManager(asIScriptEngine* engine)
{
}

// struct CrowdObstacleAvoidanceParams | File: ../Navigation/CrowdManager.h
static void Register_CrowdObstacleAvoidanceParams(asIScriptEngine* engine)
{
}

// struct DynamicNavBuildData | File: ../Navigation/NavBuildData.h
static void Register_DynamicNavBuildData(asIScriptEngine* engine)
{
}

// class DynamicNavigationMesh | File: ../Navigation/DynamicNavigationMesh.h
static void Register_DynamicNavigationMesh(asIScriptEngine* engine)
{
}

// class NavArea | File: ../Navigation/NavArea.h
static void Register_NavArea(asIScriptEngine* engine)
{
}

// NavAreaStub::~NavAreaStub() | Implicitly-declared
static void NavAreaStub_Destructor(NavAreaStub* ptr)
{
    ptr->~NavAreaStub();
}

// struct NavAreaStub | File: ../Navigation/NavBuildData.h
static void Register_NavAreaStub(asIScriptEngine* engine)
{
    // NavAreaStub::~NavAreaStub() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavAreaStub", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(NavAreaStub_Destructor), asCALL_CDECL_OBJFIRST);
}

// virtual NavBuildData::~NavBuildData()
static void NavBuildData_Destructor(NavBuildData* ptr)
{
    ptr->~NavBuildData();
}

// struct NavBuildData | File: ../Navigation/NavBuildData.h
static void Register_NavBuildData(asIScriptEngine* engine)
{
    // virtual NavBuildData::~NavBuildData()
    engine->RegisterObjectBehaviour("NavBuildData", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(NavBuildData_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Navigable | File: ../Navigation/Navigable.h
static void Register_Navigable(asIScriptEngine* engine)
{
}

// NavigationGeometryInfo::~NavigationGeometryInfo() | Implicitly-declared
static void NavigationGeometryInfo_Destructor(NavigationGeometryInfo* ptr)
{
    ptr->~NavigationGeometryInfo();
}

// struct NavigationGeometryInfo | File: ../Navigation/NavigationMesh.h
static void Register_NavigationGeometryInfo(asIScriptEngine* engine)
{
    // NavigationGeometryInfo::~NavigationGeometryInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavigationGeometryInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(NavigationGeometryInfo_Destructor), asCALL_CDECL_OBJFIRST);
}

// class NavigationMesh | File: ../Navigation/NavigationMesh.h
static void Register_NavigationMesh(asIScriptEngine* engine)
{
}

// NavigationPathPoint::~NavigationPathPoint() | Implicitly-declared
static void NavigationPathPoint_Destructor(NavigationPathPoint* ptr)
{
    ptr->~NavigationPathPoint();
}

// struct NavigationPathPoint | File: ../Navigation/NavigationMesh.h
static void Register_NavigationPathPoint(asIScriptEngine* engine)
{
    // NavigationPathPoint::~NavigationPathPoint() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavigationPathPoint", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(NavigationPathPoint_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Obstacle | File: ../Navigation/Obstacle.h
static void Register_Obstacle(asIScriptEngine* engine)
{
}

// class OffMeshConnection | File: ../Navigation/OffMeshConnection.h
static void Register_OffMeshConnection(asIScriptEngine* engine)
{
}

// SimpleNavBuildData::~SimpleNavBuildData() override
static void SimpleNavBuildData_Destructor(SimpleNavBuildData* ptr)
{
    ptr->~SimpleNavBuildData();
}

// struct SimpleNavBuildData | File: ../Navigation/NavBuildData.h
static void Register_SimpleNavBuildData(asIScriptEngine* engine)
{
    // SimpleNavBuildData::~SimpleNavBuildData() override
    engine->RegisterObjectBehaviour("SimpleNavBuildData", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(SimpleNavBuildData_Destructor), asCALL_CDECL_OBJFIRST);
}

#endif // def URHO3D_NAVIGATION

#ifdef URHO3D_NETWORK

// class Connection | File: ../Network/Connection.h
static void Register_Connection(asIScriptEngine* engine)
{
}

// class HttpRequest | File: ../Network/HttpRequest.h
static void Register_HttpRequest(asIScriptEngine* engine)
{
}

// class Network | File: ../Network/Network.h
static void Register_Network(asIScriptEngine* engine)
{
}

// class NetworkPriority | File: ../Network/NetworkPriority.h
static void Register_NetworkPriority(asIScriptEngine* engine)
{
}

// PackageDownload::~PackageDownload() | Implicitly-declared
static void PackageDownload_Destructor(PackageDownload* ptr)
{
    ptr->~PackageDownload();
}

// struct PackageDownload | File: ../Network/Connection.h
static void Register_PackageDownload(asIScriptEngine* engine)
{
    // PackageDownload::~PackageDownload() | Implicitly-declared
    engine->RegisterObjectBehaviour("PackageDownload", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(PackageDownload_Destructor), asCALL_CDECL_OBJFIRST);
}

// PackageUpload::~PackageUpload() | Implicitly-declared
static void PackageUpload_Destructor(PackageUpload* ptr)
{
    ptr->~PackageUpload();
}

// struct PackageUpload | File: ../Network/Connection.h
static void Register_PackageUpload(asIScriptEngine* engine)
{
    // PackageUpload::~PackageUpload() | Implicitly-declared
    engine->RegisterObjectBehaviour("PackageUpload", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(PackageUpload_Destructor), asCALL_CDECL_OBJFIRST);
}

// RemoteEvent::~RemoteEvent() | Implicitly-declared
static void RemoteEvent_Destructor(RemoteEvent* ptr)
{
    ptr->~RemoteEvent();
}

// struct RemoteEvent | File: ../Network/Connection.h
static void Register_RemoteEvent(asIScriptEngine* engine)
{
    // RemoteEvent::~RemoteEvent() | Implicitly-declared
    engine->RegisterObjectBehaviour("RemoteEvent", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(RemoteEvent_Destructor), asCALL_CDECL_OBJFIRST);
}

#endif // def URHO3D_NETWORK

#ifdef URHO3D_PHYSICS

// struct CollisionGeometryData | File: ../Physics/CollisionShape.h
static void Register_CollisionGeometryData(asIScriptEngine* engine)
{
}

// class CollisionShape | File: ../Physics/CollisionShape.h
static void Register_CollisionShape(asIScriptEngine* engine)
{
}

// class Constraint | File: ../Physics/Constraint.h
static void Register_Constraint(asIScriptEngine* engine)
{
}

// struct ConvexData | File: ../Physics/CollisionShape.h
static void Register_ConvexData(asIScriptEngine* engine)
{
}

// DelayedWorldTransform::~DelayedWorldTransform() | Implicitly-declared
static void DelayedWorldTransform_Destructor(DelayedWorldTransform* ptr)
{
    ptr->~DelayedWorldTransform();
}

// struct DelayedWorldTransform | File: ../Physics/PhysicsWorld.h
static void Register_DelayedWorldTransform(asIScriptEngine* engine)
{
    // DelayedWorldTransform::~DelayedWorldTransform() | Implicitly-declared
    engine->RegisterObjectBehaviour("DelayedWorldTransform", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DelayedWorldTransform_Destructor), asCALL_CDECL_OBJFIRST);
}

// struct GImpactMeshData | File: ../Physics/CollisionShape.h
static void Register_GImpactMeshData(asIScriptEngine* engine)
{
}

// struct HeightfieldData | File: ../Physics/CollisionShape.h
static void Register_HeightfieldData(asIScriptEngine* engine)
{
}

// ManifoldPair::~ManifoldPair() | Implicitly-declared
static void ManifoldPair_Destructor(ManifoldPair* ptr)
{
    ptr->~ManifoldPair();
}

// struct ManifoldPair | File: ../Physics/PhysicsWorld.h
static void Register_ManifoldPair(asIScriptEngine* engine)
{
    // ManifoldPair::~ManifoldPair() | Implicitly-declared
    engine->RegisterObjectBehaviour("ManifoldPair", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ManifoldPair_Destructor), asCALL_CDECL_OBJFIRST);
}

// PhysicsRaycastResult::~PhysicsRaycastResult() | Implicitly-declared
static void PhysicsRaycastResult_Destructor(PhysicsRaycastResult* ptr)
{
    ptr->~PhysicsRaycastResult();
}

// struct PhysicsRaycastResult | File: ../Physics/PhysicsWorld.h
static void Register_PhysicsRaycastResult(asIScriptEngine* engine)
{
    // PhysicsRaycastResult::~PhysicsRaycastResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("PhysicsRaycastResult", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(PhysicsRaycastResult_Destructor), asCALL_CDECL_OBJFIRST);
}

// class PhysicsWorld | File: ../Physics/PhysicsWorld.h
static void Register_PhysicsWorld(asIScriptEngine* engine)
{
}

// PhysicsWorldConfig::~PhysicsWorldConfig() | Implicitly-declared
static void PhysicsWorldConfig_Destructor(PhysicsWorldConfig* ptr)
{
    ptr->~PhysicsWorldConfig();
}

// struct PhysicsWorldConfig | File: ../Physics/PhysicsWorld.h
static void Register_PhysicsWorldConfig(asIScriptEngine* engine)
{
    // PhysicsWorldConfig::~PhysicsWorldConfig() | Implicitly-declared
    engine->RegisterObjectBehaviour("PhysicsWorldConfig", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(PhysicsWorldConfig_Destructor), asCALL_CDECL_OBJFIRST);
}

// class RaycastVehicle | File: ../Physics/RaycastVehicle.h
static void Register_RaycastVehicle(asIScriptEngine* engine)
{
}

// class RigidBody | File: ../Physics/RigidBody.h
static void Register_RigidBody(asIScriptEngine* engine)
{
}

// struct TriangleMeshData | File: ../Physics/CollisionShape.h
static void Register_TriangleMeshData(asIScriptEngine* engine)
{
}

#endif // def URHO3D_PHYSICS

#ifdef URHO3D_URHO2D

// class AnimatedSprite2D | File: ../Urho2D/AnimatedSprite2D.h
static void Register_AnimatedSprite2D(asIScriptEngine* engine)
{
}

// class AnimationSet2D | File: ../Urho2D/AnimationSet2D.h
static void Register_AnimationSet2D(asIScriptEngine* engine)
{
}

// class CollisionBox2D | File: ../Urho2D/CollisionBox2D.h
static void Register_CollisionBox2D(asIScriptEngine* engine)
{
}

// class CollisionChain2D | File: ../Urho2D/CollisionChain2D.h
static void Register_CollisionChain2D(asIScriptEngine* engine)
{
}

// class CollisionCircle2D | File: ../Urho2D/CollisionCircle2D.h
static void Register_CollisionCircle2D(asIScriptEngine* engine)
{
}

// class CollisionEdge2D | File: ../Urho2D/CollisionEdge2D.h
static void Register_CollisionEdge2D(asIScriptEngine* engine)
{
}

// class CollisionPolygon2D | File: ../Urho2D/CollisionPolygon2D.h
static void Register_CollisionPolygon2D(asIScriptEngine* engine)
{
}

// class CollisionShape2D | File: ../Urho2D/CollisionShape2D.h
static void Register_CollisionShape2D(asIScriptEngine* engine)
{
}

// class Constraint2D | File: ../Urho2D/Constraint2D.h
static void Register_Constraint2D(asIScriptEngine* engine)
{
}

// class ConstraintDistance2D | File: ../Urho2D/ConstraintDistance2D.h
static void Register_ConstraintDistance2D(asIScriptEngine* engine)
{
}

// class ConstraintFriction2D | File: ../Urho2D/ConstraintFriction2D.h
static void Register_ConstraintFriction2D(asIScriptEngine* engine)
{
}

// class ConstraintGear2D | File: ../Urho2D/ConstraintGear2D.h
static void Register_ConstraintGear2D(asIScriptEngine* engine)
{
}

// class ConstraintMotor2D | File: ../Urho2D/ConstraintMotor2D.h
static void Register_ConstraintMotor2D(asIScriptEngine* engine)
{
}

// class ConstraintMouse2D | File: ../Urho2D/ConstraintMouse2D.h
static void Register_ConstraintMouse2D(asIScriptEngine* engine)
{
}

// class ConstraintPrismatic2D | File: ../Urho2D/ConstraintPrismatic2D.h
static void Register_ConstraintPrismatic2D(asIScriptEngine* engine)
{
}

// class ConstraintPulley2D | File: ../Urho2D/ConstraintPulley2D.h
static void Register_ConstraintPulley2D(asIScriptEngine* engine)
{
}

// class ConstraintRevolute2D | File: ../Urho2D/ConstraintRevolute2D.h
static void Register_ConstraintRevolute2D(asIScriptEngine* engine)
{
}

// class ConstraintRope2D | File: ../Urho2D/ConstraintRope2D.h
static void Register_ConstraintRope2D(asIScriptEngine* engine)
{
}

// class ConstraintWeld2D | File: ../Urho2D/ConstraintWeld2D.h
static void Register_ConstraintWeld2D(asIScriptEngine* engine)
{
}

// class ConstraintWheel2D | File: ../Urho2D/ConstraintWheel2D.h
static void Register_ConstraintWheel2D(asIScriptEngine* engine)
{
}

// DelayedWorldTransform2D::~DelayedWorldTransform2D() | Implicitly-declared
static void DelayedWorldTransform2D_Destructor(DelayedWorldTransform2D* ptr)
{
    ptr->~DelayedWorldTransform2D();
}

// struct DelayedWorldTransform2D | File: ../Urho2D/PhysicsWorld2D.h
static void Register_DelayedWorldTransform2D(asIScriptEngine* engine)
{
    // DelayedWorldTransform2D::~DelayedWorldTransform2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("DelayedWorldTransform2D", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DelayedWorldTransform2D_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Drawable2D | File: ../Urho2D/Drawable2D.h
static void Register_Drawable2D(asIScriptEngine* engine)
{
}

// Particle2D::~Particle2D() | Implicitly-declared
static void Particle2D_Destructor(Particle2D* ptr)
{
    ptr->~Particle2D();
}

// struct Particle2D | File: ../Urho2D/ParticleEmitter2D.h
static void Register_Particle2D(asIScriptEngine* engine)
{
    // Particle2D::~Particle2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("Particle2D", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Particle2D_Destructor), asCALL_CDECL_OBJFIRST);
}

// class ParticleEffect2D | File: ../Urho2D/ParticleEffect2D.h
static void Register_ParticleEffect2D(asIScriptEngine* engine)
{
}

// class ParticleEmitter2D | File: ../Urho2D/ParticleEmitter2D.h
static void Register_ParticleEmitter2D(asIScriptEngine* engine)
{
}

// PhysicsRaycastResult2D::~PhysicsRaycastResult2D() | Implicitly-declared
static void PhysicsRaycastResult2D_Destructor(PhysicsRaycastResult2D* ptr)
{
    ptr->~PhysicsRaycastResult2D();
}

// struct PhysicsRaycastResult2D | File: ../Urho2D/PhysicsWorld2D.h
static void Register_PhysicsRaycastResult2D(asIScriptEngine* engine)
{
    // PhysicsRaycastResult2D::~PhysicsRaycastResult2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("PhysicsRaycastResult2D", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(PhysicsRaycastResult2D_Destructor), asCALL_CDECL_OBJFIRST);
}

// class PhysicsWorld2D | File: ../Urho2D/PhysicsWorld2D.h
static void Register_PhysicsWorld2D(asIScriptEngine* engine)
{
}

// class PropertySet2D | File: ../Urho2D/TileMapDefs2D.h
static void Register_PropertySet2D(asIScriptEngine* engine)
{
}

// class Renderer2D | File: ../Urho2D/Renderer2D.h
static void Register_Renderer2D(asIScriptEngine* engine)
{
}

// class RigidBody2D | File: ../Urho2D/RigidBody2D.h
static void Register_RigidBody2D(asIScriptEngine* engine)
{
}

// SourceBatch2D::~SourceBatch2D() | Implicitly-declared
static void SourceBatch2D_Destructor(SourceBatch2D* ptr)
{
    ptr->~SourceBatch2D();
}

// struct SourceBatch2D | File: ../Urho2D/Drawable2D.h
static void Register_SourceBatch2D(asIScriptEngine* engine)
{
    // SourceBatch2D::~SourceBatch2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("SourceBatch2D", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(SourceBatch2D_Destructor), asCALL_CDECL_OBJFIRST);
}

// class Sprite2D | File: ../Urho2D/Sprite2D.h
static void Register_Sprite2D(asIScriptEngine* engine)
{
}

// class SpriteSheet2D | File: ../Urho2D/SpriteSheet2D.h
static void Register_SpriteSheet2D(asIScriptEngine* engine)
{
}

// class StaticSprite2D | File: ../Urho2D/StaticSprite2D.h
static void Register_StaticSprite2D(asIScriptEngine* engine)
{
}

// class StretchableSprite2D | File: ../Urho2D/StretchableSprite2D.h
static void Register_StretchableSprite2D(asIScriptEngine* engine)
{
}

// class Tile2D | File: ../Urho2D/TileMapDefs2D.h
static void Register_Tile2D(asIScriptEngine* engine)
{
}

// class TileMap2D | File: ../Urho2D/TileMap2D.h
static void Register_TileMap2D(asIScriptEngine* engine)
{
}

// struct TileMapInfo2D | File: ../Urho2D/TileMapDefs2D.h
static void Register_TileMapInfo2D(asIScriptEngine* engine)
{
}

// class TileMapLayer2D | File: ../Urho2D/TileMapLayer2D.h
static void Register_TileMapLayer2D(asIScriptEngine* engine)
{
}

// class TileMapObject2D | File: ../Urho2D/TileMapDefs2D.h
static void Register_TileMapObject2D(asIScriptEngine* engine)
{
}

// class TmxFile2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxFile2D(asIScriptEngine* engine)
{
}

// class TmxImageLayer2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxImageLayer2D(asIScriptEngine* engine)
{
}

// class TmxLayer2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxLayer2D(asIScriptEngine* engine)
{
}

// class TmxObjectGroup2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxObjectGroup2D(asIScriptEngine* engine)
{
}

// class TmxTileLayer2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxTileLayer2D(asIScriptEngine* engine)
{
}

// Vertex2D::~Vertex2D() | Implicitly-declared
static void Vertex2D_Destructor(Vertex2D* ptr)
{
    ptr->~Vertex2D();
}

// struct Vertex2D | File: ../Urho2D/Drawable2D.h
static void Register_Vertex2D(asIScriptEngine* engine)
{
    // Vertex2D::~Vertex2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("Vertex2D", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Vertex2D_Destructor), asCALL_CDECL_OBJFIRST);
}

// struct ViewBatchInfo2D | File: ../Urho2D/Renderer2D.h
static void Register_ViewBatchInfo2D(asIScriptEngine* engine)
{
}

#endif // def URHO3D_URHO2D

void ASRegisterGeneratedClasses(asIScriptEngine* engine)
{
    Register_AbstractFile(engine);
    Register_AllContentOctreeQuery(engine);
    Register_AllocatorBlock(engine);
    Register_AllocatorNode(engine);
    Register_Animatable(engine);
    Register_AnimatedModel(engine);
    Register_Animation(engine);
    Register_AnimationControl(engine);
    Register_AnimationController(engine);
    Register_AnimationKeyFrame(engine);
    Register_AnimationState(engine);
    Register_AnimationStateTrack(engine);
    Register_AnimationTrack(engine);
    Register_AnimationTriggerPoint(engine);
    Register_AreaAllocator(engine);
    Register_AsyncProgress(engine);
    Register_AttributeAccessor(engine);
    Register_AttributeAnimationInfo(engine);
    Register_AttributeHandle(engine);
    Register_AttributeInfo(engine);
    Register_Audio(engine);
    Register_AutoProfileBlock(engine);
    Register_BackgroundLoadItem(engine);
    Register_BackgroundLoader(engine);
    Register_Batch(engine);
    Register_BatchGroup(engine);
    Register_BatchGroupKey(engine);
    Register_BatchQueue(engine);
    Register_BiasParameters(engine);
    Register_Billboard(engine);
    Register_BillboardSet(engine);
    Register_Bone(engine);
    Register_BorderImage(engine);
    Register_BoundingBox(engine);
    Register_BoxOctreeQuery(engine);
    Register_BufferedSoundStream(engine);
    Register_Button(engine);
    Register_Camera(engine);
    Register_CascadeParameters(engine);
    Register_CharLocation(engine);
    Register_CheckBox(engine);
    Register_Color(engine);
    Register_ColorFrame(engine);
    Register_Component(engine);
    Register_ComponentReplicationState(engine);
    Register_CompressedLevel(engine);
    Register_Condition(engine);
    Register_Console(engine);
    Register_ConstantBuffer(engine);
    Register_Context(engine);
    Register_Controls(engine);
    Register_Cursor(engine);
    Register_CursorShapeInfo(engine);
    Register_CustomGeometry(engine);
    Register_CustomGeometryVertex(engine);
    Register_CustomVariantValue(engine);
    Register_DebugHud(engine);
    Register_DebugLine(engine);
    Register_DebugRenderer(engine);
    Register_DebugTriangle(engine);
    Register_Decal(engine);
    Register_DecalSet(engine);
    Register_DecalVertex(engine);
    Register_DepthValue(engine);
    Register_Deserializer(engine);
    Register_DirtyBits(engine);
    Register_Drawable(engine);
    Register_DropDownList(engine);
    Register_Engine(engine);
    Register_EventHandler11Impl(engine);
    Register_EventProfiler(engine);
    Register_EventProfilerBlock(engine);
    Register_EventReceiverGroup(engine);
    Register_File(engine);
    Register_FileSelector(engine);
    Register_FileSelectorEntry(engine);
    Register_FileSystem(engine);
    Register_FileWatcher(engine);
    Register_FocusParameters(engine);
    Register_Font(engine);
    Register_FontFace(engine);
    Register_FontFaceBitmap(engine);
    Register_FontFaceFreeType(engine);
    Register_FontGlyph(engine);
    Register_FrameInfo(engine);
    Register_Frustum(engine);
    Register_FrustumOctreeQuery(engine);
    Register_GPUObject(engine);
    Register_Geometry(engine);
    Register_GeometryDesc(engine);
    Register_GlyphLocation(engine);
    Register_Graphics(engine);
    Register_HashBase(engine);
    Register_HashIteratorBase(engine);
    Register_HashNodeBase(engine);
    Register_HiresTimer(engine);
    Register_Image(engine);
    Register_IndexBuffer(engine);
    Register_IndexBufferDesc(engine);
    Register_Input(engine);
    Register_InstanceData(engine);
    Register_IntRect(engine);
    Register_IntVector2(engine);
    Register_IntVector3(engine);
    Register_JSONFile(engine);
    Register_JSONValue(engine);
    Register_JoystickState(engine);
    Register_Light(engine);
    Register_LightBatchQueue(engine);
    Register_LightQueryResult(engine);
    Register_LineEdit(engine);
    Register_LinkedListNode(engine);
    Register_ListBase(engine);
    Register_ListIteratorBase(engine);
    Register_ListNodeBase(engine);
    Register_ListView(engine);
    Register_Localization(engine);
    Register_Log(engine);
    Register_LogicComponent(engine);
    Register_Material(engine);
    Register_MaterialShaderParameter(engine);
    Register_Matrix2(engine);
    Register_Matrix3(engine);
    Register_Matrix3x4(engine);
    Register_Matrix4(engine);
    Register_MemoryBuffer(engine);
    Register_Menu(engine);
    Register_MessageBox(engine);
    Register_Model(engine);
    Register_ModelMorph(engine);
    Register_Mutex(engine);
    Register_MutexLock(engine);
    Register_NamedPipe(engine);
    Register_NetworkState(engine);
    Register_Node(engine);
    Register_NodeImpl(engine);
    Register_NodeReplicationState(engine);
    Register_Object(engine);
    Register_ObjectAnimation(engine);
    Register_ObjectFactory(engine);
    Register_OcclusionBatch(engine);
    Register_OcclusionBuffer(engine);
    Register_OcclusionBufferData(engine);
    Register_Octant(engine);
    Register_Octree(engine);
    Register_OctreeQueryResult(engine);
    Register_OggVorbisSoundStream(engine);
    Register_PackageEntry(engine);
    Register_PackageFile(engine);
    Register_Particle(engine);
    Register_ParticleEffect(engine);
    Register_ParticleEmitter(engine);
    Register_Pass(engine);
    Register_PerThreadSceneResult(engine);
    Register_Plane(engine);
    Register_PointOctreeQuery(engine);
    Register_Polyhedron(engine);
    Register_Profiler(engine);
    Register_ProfilerBlock(engine);
    Register_ProgressBar(engine);
    Register_Quaternion(engine);
    Register_Ray(engine);
    Register_RayOctreeQuery(engine);
    Register_RayQueryResult(engine);
    Register_Rect(engine);
    Register_RefCount(engine);
    Register_RefCounted(engine);
    Register_RenderPath(engine);
    Register_RenderPathCommand(engine);
    Register_RenderSurface(engine);
    Register_RenderTargetInfo(engine);
    Register_Renderer(engine);
    Register_ReplicationState(engine);
    Register_Resource(engine);
    Register_ResourceCache(engine);
    Register_ResourceGroup(engine);
    Register_ResourceRef(engine);
    Register_ResourceRefList(engine);
    Register_ResourceRouter(engine);
    Register_ResourceWithMetadata(engine);
    Register_RibbonTrail(engine);
    Register_Scene(engine);
    Register_ScenePassInfo(engine);
    Register_SceneReplicationState(engine);
    Register_SceneResolver(engine);
    Register_ScratchBuffer(engine);
    Register_ScreenModeParams(engine);
    Register_ScrollBar(engine);
    Register_ScrollView(engine);
    Register_Serializable(engine);
    Register_Serializer(engine);
    Register_Shader(engine);
    Register_ShaderParameter(engine);
    Register_ShaderParameterAnimationInfo(engine);
    Register_ShaderPrecache(engine);
    Register_ShaderVariation(engine);
    Register_ShadowBatchQueue(engine);
    Register_Skeleton(engine);
    Register_Skybox(engine);
    Register_Slider(engine);
    Register_SmoothedTransform(engine);
    Register_Sound(engine);
    Register_SoundListener(engine);
    Register_SoundSource(engine);
    Register_SoundSource3D(engine);
    Register_SoundStream(engine);
    Register_SourceBatch(engine);
    Register_Sphere(engine);
    Register_SphereOctreeQuery(engine);
    Register_Spline(engine);
    Register_SplinePath(engine);
    Register_Sprite(engine);
    Register_StaticModel(engine);
    Register_StaticModelGeometryData(engine);
    Register_StaticModelGroup(engine);
    Register_StoredLogMessage(engine);
    Register_String(engine);
    Register_StringHash(engine);
    Register_StringHashRegister(engine);
    Register_Technique(engine);
    Register_TechniqueEntry(engine);
    Register_Terrain(engine);
    Register_TerrainPatch(engine);
    Register_Text(engine);
    Register_Text3D(engine);
    Register_Texture(engine);
    Register_Texture2D(engine);
    Register_Texture2DArray(engine);
    Register_Texture3D(engine);
    Register_TextureCube(engine);
    Register_TextureFrame(engine);
    Register_Time(engine);
    Register_Timer(engine);
    Register_ToolTip(engine);
    Register_TouchState(engine);
    Register_TrailPoint(engine);
    Register_TypeInfo(engine);
    Register_UI(engine);
    Register_UIBatch(engine);
    Register_UIComponent(engine);
    Register_UIElement(engine);
    Register_UISelectable(engine);
    Register_UnknownComponent(engine);
    Register_VAnimEventFrame(engine);
    Register_VAnimKeyFrame(engine);
    Register_ValueAnimation(engine);
    Register_ValueAnimationInfo(engine);
    Register_Variant(engine);
    Register_Vector2(engine);
    Register_Vector3(engine);
    Register_Vector4(engine);
    Register_VectorBase(engine);
    Register_VectorBuffer(engine);
    Register_VertexBuffer(engine);
    Register_VertexBufferDesc(engine);
    Register_VertexBufferMorph(engine);
    Register_VertexElement(engine);
    Register_View(engine);
    Register_View3D(engine);
    Register_Viewport(engine);
    Register_WString(engine);
    Register_Window(engine);
    Register_WindowModeParams(engine);
    Register_WorkItem(engine);
    Register_WorkQueue(engine);
    Register_XMLElement(engine);
    Register_XMLFile(engine);
    Register_XPathQuery(engine);
    Register_XPathResultSet(engine);
    Register_Zone(engine);

#ifdef URHO3D_DATABASE
    Register_Database(engine);
#endif

#ifdef URHO3D_IK
    Register_IKConstraint(engine);
    Register_IKEffector(engine);
    Register_IKSolver(engine);
#endif

#ifdef URHO3D_NAVIGATION
    Register_CrowdAgent(engine);
    Register_CrowdManager(engine);
    Register_CrowdObstacleAvoidanceParams(engine);
    Register_DynamicNavBuildData(engine);
    Register_DynamicNavigationMesh(engine);
    Register_NavArea(engine);
    Register_NavAreaStub(engine);
    Register_NavBuildData(engine);
    Register_Navigable(engine);
    Register_NavigationGeometryInfo(engine);
    Register_NavigationMesh(engine);
    Register_NavigationPathPoint(engine);
    Register_Obstacle(engine);
    Register_OffMeshConnection(engine);
    Register_SimpleNavBuildData(engine);
#endif

#ifdef URHO3D_NETWORK
    Register_Connection(engine);
    Register_HttpRequest(engine);
    Register_Network(engine);
    Register_NetworkPriority(engine);
    Register_PackageDownload(engine);
    Register_PackageUpload(engine);
    Register_RemoteEvent(engine);
#endif

#ifdef URHO3D_PHYSICS
    Register_CollisionGeometryData(engine);
    Register_CollisionShape(engine);
    Register_Constraint(engine);
    Register_ConvexData(engine);
    Register_DelayedWorldTransform(engine);
    Register_GImpactMeshData(engine);
    Register_HeightfieldData(engine);
    Register_ManifoldPair(engine);
    Register_PhysicsRaycastResult(engine);
    Register_PhysicsWorld(engine);
    Register_PhysicsWorldConfig(engine);
    Register_RaycastVehicle(engine);
    Register_RigidBody(engine);
    Register_TriangleMeshData(engine);
#endif

#ifdef URHO3D_URHO2D
    Register_AnimatedSprite2D(engine);
    Register_AnimationSet2D(engine);
    Register_CollisionBox2D(engine);
    Register_CollisionChain2D(engine);
    Register_CollisionCircle2D(engine);
    Register_CollisionEdge2D(engine);
    Register_CollisionPolygon2D(engine);
    Register_CollisionShape2D(engine);
    Register_Constraint2D(engine);
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
    Register_DelayedWorldTransform2D(engine);
    Register_Drawable2D(engine);
    Register_Particle2D(engine);
    Register_ParticleEffect2D(engine);
    Register_ParticleEmitter2D(engine);
    Register_PhysicsRaycastResult2D(engine);
    Register_PhysicsWorld2D(engine);
    Register_PropertySet2D(engine);
    Register_Renderer2D(engine);
    Register_RigidBody2D(engine);
    Register_SourceBatch2D(engine);
    Register_Sprite2D(engine);
    Register_SpriteSheet2D(engine);
    Register_StaticSprite2D(engine);
    Register_StretchableSprite2D(engine);
    Register_Tile2D(engine);
    Register_TileMap2D(engine);
    Register_TileMapInfo2D(engine);
    Register_TileMapLayer2D(engine);
    Register_TileMapObject2D(engine);
    Register_TmxFile2D(engine);
    Register_TmxImageLayer2D(engine);
    Register_TmxLayer2D(engine);
    Register_TmxObjectGroup2D(engine);
    Register_TmxTileLayer2D(engine);
    Register_Vertex2D(engine);
    Register_ViewBatchInfo2D(engine);
#endif
}

}
