// DO NOT EDIT. This file is generated

// We need register default constructors before any members to allow using in Array<type>

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Generated_Includes.h"

namespace Urho3D
{

void ASRegisterGeneratedDefaultConstructors(asIScriptEngine* engine)
{
    // AllocatorBlock::AllocatorBlock() | Implicitly-declared
    engine->RegisterObjectBehaviour("AllocatorBlock", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<AllocatorBlock>), AS_CALL_CDECL_OBJFIRST);

    // AllocatorNode::AllocatorNode() | Implicitly-declared
    engine->RegisterObjectBehaviour("AllocatorNode", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<AllocatorNode>), AS_CALL_CDECL_OBJFIRST);

    // AnimationControl::AnimationControl() | File: ../Graphics/AnimationController.h
    engine->RegisterObjectBehaviour("AnimationControl", asBEHAVE_FACTORY, "AnimationControl@+ f()", asFUNCTION(ASCompatibleFactory<AnimationControl>), AS_CALL_CDECL);

    // AnimationKeyFrame::AnimationKeyFrame() | File: ../Graphics/Animation.h
    engine->RegisterObjectBehaviour("AnimationKeyFrame", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<AnimationKeyFrame>), AS_CALL_CDECL_OBJFIRST);

    // AnimationStateTrack::AnimationStateTrack() | File: ../Graphics/AnimationState.h
    engine->RegisterObjectBehaviour("AnimationStateTrack", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<AnimationStateTrack>), AS_CALL_CDECL_OBJFIRST);

    // AnimationTrack::AnimationTrack() | File: ../Graphics/Animation.h
    engine->RegisterObjectBehaviour("AnimationTrack", asBEHAVE_FACTORY, "AnimationTrack@+ f()", asFUNCTION(ASCompatibleFactory<AnimationTrack>), AS_CALL_CDECL);

    // AnimationTriggerPoint::AnimationTriggerPoint() | File: ../Graphics/Animation.h
    engine->RegisterObjectBehaviour("AnimationTriggerPoint", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<AnimationTriggerPoint>), AS_CALL_CDECL_OBJFIRST);

    // AreaAllocator::AreaAllocator() | File: ../Math/AreaAllocator.h
    engine->RegisterObjectBehaviour("AreaAllocator", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<AreaAllocator>), AS_CALL_CDECL_OBJFIRST);

    // AsyncProgress::AsyncProgress() | Implicitly-declared
    engine->RegisterObjectBehaviour("AsyncProgress", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<AsyncProgress>), AS_CALL_CDECL_OBJFIRST);

    // AttributeInfo::AttributeInfo() = default | File: ../Core/Attribute.h
    engine->RegisterObjectBehaviour("AttributeInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<AttributeInfo>), AS_CALL_CDECL_OBJFIRST);

    // BackgroundLoadItem::BackgroundLoadItem() | Implicitly-declared
    engine->RegisterObjectBehaviour("BackgroundLoadItem", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<BackgroundLoadItem>), AS_CALL_CDECL_OBJFIRST);

    // Batch::Batch() = default | File: ../Graphics/Batch.h
    engine->RegisterObjectBehaviour("Batch", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Batch>), AS_CALL_CDECL_OBJFIRST);

    // BatchGroupKey::BatchGroupKey() = default | File: ../Graphics/Batch.h
    engine->RegisterObjectBehaviour("BatchGroupKey", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<BatchGroupKey>), AS_CALL_CDECL_OBJFIRST);

    // BatchQueue::BatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("BatchQueue", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<BatchQueue>), AS_CALL_CDECL_OBJFIRST);

    // BiasParameters::BiasParameters() = default | File: ../Graphics/Light.h
    engine->RegisterObjectBehaviour("BiasParameters", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<BiasParameters>), AS_CALL_CDECL_OBJFIRST);

    // Bone::Bone() | File: ../Graphics/Skeleton.h
    engine->RegisterObjectBehaviour("Bone", asBEHAVE_FACTORY, "Bone@+ f()", asFUNCTION(ASCompatibleFactory<Bone>), AS_CALL_CDECL);

    // BoundingBox::BoundingBox() noexcept | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<BoundingBox>), AS_CALL_CDECL_OBJFIRST);

    // CascadeParameters::CascadeParameters() = default | File: ../Graphics/Light.h
    engine->RegisterObjectBehaviour("CascadeParameters", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<CascadeParameters>), AS_CALL_CDECL_OBJFIRST);

    // CharLocation::CharLocation() | Implicitly-declared
    engine->RegisterObjectBehaviour("CharLocation", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<CharLocation>), AS_CALL_CDECL_OBJFIRST);

    // Color::Color() noexcept | File: ../Math/Color.h
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Color>), AS_CALL_CDECL_OBJFIRST);

    // ColorFrame::ColorFrame() | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_FACTORY, "ColorFrame@+ f()", asFUNCTION(ASCompatibleFactory<ColorFrame>), AS_CALL_CDECL);

    // CompressedLevel::CompressedLevel() | Implicitly-declared
    engine->RegisterObjectBehaviour("CompressedLevel", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<CompressedLevel>), AS_CALL_CDECL_OBJFIRST);

    // Condition::Condition() | File: ../Core/Condition.h
    engine->RegisterObjectBehaviour("Condition", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Condition>), AS_CALL_CDECL_OBJFIRST);

    // Controls::Controls() | File: ../Input/Controls.h
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Controls>), AS_CALL_CDECL_OBJFIRST);

    // CursorShapeInfo::CursorShapeInfo() | File: ../UI/Cursor.h
    engine->RegisterObjectBehaviour("CursorShapeInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<CursorShapeInfo>), AS_CALL_CDECL_OBJFIRST);

    // DebugLine::DebugLine() = default | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectBehaviour("DebugLine", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<DebugLine>), AS_CALL_CDECL_OBJFIRST);

    // DebugTriangle::DebugTriangle() = default | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectBehaviour("DebugTriangle", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<DebugTriangle>), AS_CALL_CDECL_OBJFIRST);

    // Decal::Decal() | File: ../Graphics/DecalSet.h
    engine->RegisterObjectBehaviour("Decal", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Decal>), AS_CALL_CDECL_OBJFIRST);

    // DecalVertex::DecalVertex() = default | File: ../Graphics/DecalSet.h
    engine->RegisterObjectBehaviour("DecalVertex", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<DecalVertex>), AS_CALL_CDECL_OBJFIRST);

    // DirtyBits::DirtyBits() = default | File: ../Scene/ReplicationState.h
    engine->RegisterObjectBehaviour("DirtyBits", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<DirtyBits>), AS_CALL_CDECL_OBJFIRST);

    // FileSelectorEntry::FileSelectorEntry() | Implicitly-declared
    engine->RegisterObjectBehaviour("FileSelectorEntry", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<FileSelectorEntry>), AS_CALL_CDECL_OBJFIRST);

    // FocusParameters::FocusParameters() = default | File: ../Graphics/Light.h
    engine->RegisterObjectBehaviour("FocusParameters", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<FocusParameters>), AS_CALL_CDECL_OBJFIRST);

    // FontGlyph::FontGlyph() | Implicitly-declared
    engine->RegisterObjectBehaviour("FontGlyph", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<FontGlyph>), AS_CALL_CDECL_OBJFIRST);

    // FrameInfo::FrameInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("FrameInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<FrameInfo>), AS_CALL_CDECL_OBJFIRST);

    // Frustum::Frustum() noexcept = default | File: ../Math/Frustum.h
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Frustum>), AS_CALL_CDECL_OBJFIRST);

    // GeometryDesc::GeometryDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("GeometryDesc", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<GeometryDesc>), AS_CALL_CDECL_OBJFIRST);

    // HashBase::HashBase() | File: ../Container/HashBase.h
    engine->RegisterObjectBehaviour("HashBase", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<HashBase>), AS_CALL_CDECL_OBJFIRST);

    // HashIteratorBase::HashIteratorBase() | File: ../Container/HashBase.h
    engine->RegisterObjectBehaviour("HashIteratorBase", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<HashIteratorBase>), AS_CALL_CDECL_OBJFIRST);

    // HashNodeBase::HashNodeBase() | File: ../Container/HashBase.h
    engine->RegisterObjectBehaviour("HashNodeBase", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<HashNodeBase>), AS_CALL_CDECL_OBJFIRST);

    // HiresTimer::HiresTimer() | File: ../Core/Timer.h
    engine->RegisterObjectBehaviour("HiresTimer", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<HiresTimer>), AS_CALL_CDECL_OBJFIRST);

    // IndexBufferDesc::IndexBufferDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("IndexBufferDesc", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<IndexBufferDesc>), AS_CALL_CDECL_OBJFIRST);

    // InstanceData::InstanceData() = default | File: ../Graphics/Batch.h
    engine->RegisterObjectBehaviour("InstanceData", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<InstanceData>), AS_CALL_CDECL_OBJFIRST);

    // IntRect::IntRect() noexcept | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<IntRect>), AS_CALL_CDECL_OBJFIRST);

    // IntVector2::IntVector2() noexcept | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<IntVector2>), AS_CALL_CDECL_OBJFIRST);

    // IntVector3::IntVector3() noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<IntVector3>), AS_CALL_CDECL_OBJFIRST);

    // JSONValue::JSONValue() | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<JSONValue>), AS_CALL_CDECL_OBJFIRST);

    // LightBatchQueue::LightBatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("LightBatchQueue", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<LightBatchQueue>), AS_CALL_CDECL_OBJFIRST);

    // LightQueryResult::LightQueryResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("LightQueryResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<LightQueryResult>), AS_CALL_CDECL_OBJFIRST);

    // LinkedListNode::LinkedListNode() | File: ../Container/LinkedList.h
    engine->RegisterObjectBehaviour("LinkedListNode", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<LinkedListNode>), AS_CALL_CDECL_OBJFIRST);

    // ListBase::ListBase() | File: ../Container/ListBase.h
    engine->RegisterObjectBehaviour("ListBase", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ListBase>), AS_CALL_CDECL_OBJFIRST);

    // ListIteratorBase::ListIteratorBase() | File: ../Container/ListBase.h
    engine->RegisterObjectBehaviour("ListIteratorBase", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ListIteratorBase>), AS_CALL_CDECL_OBJFIRST);

    // ListNodeBase::ListNodeBase() | File: ../Container/ListBase.h
    engine->RegisterObjectBehaviour("ListNodeBase", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ListNodeBase>), AS_CALL_CDECL_OBJFIRST);

    // MaterialShaderParameter::MaterialShaderParameter() | Implicitly-declared
    engine->RegisterObjectBehaviour("MaterialShaderParameter", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<MaterialShaderParameter>), AS_CALL_CDECL_OBJFIRST);

    // Matrix2::Matrix2() noexcept | File: ../Math/Matrix2.h
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Matrix2>), AS_CALL_CDECL_OBJFIRST);

    // Matrix3::Matrix3() noexcept | File: ../Math/Matrix3.h
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Matrix3>), AS_CALL_CDECL_OBJFIRST);

    // Matrix3x4::Matrix3x4() noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Matrix3x4>), AS_CALL_CDECL_OBJFIRST);

    // Matrix4::Matrix4() noexcept | File: ../Math/Matrix4.h
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Matrix4>), AS_CALL_CDECL_OBJFIRST);

    // ModelMorph::ModelMorph() | Implicitly-declared
    engine->RegisterObjectBehaviour("ModelMorph", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ModelMorph>), AS_CALL_CDECL_OBJFIRST);

    // Mutex::Mutex() | File: ../Core/Mutex.h
    engine->RegisterObjectBehaviour("Mutex", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Mutex>), AS_CALL_CDECL_OBJFIRST);

    // NetworkState::NetworkState() | Implicitly-declared
    engine->RegisterObjectBehaviour("NetworkState", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<NetworkState>), AS_CALL_CDECL_OBJFIRST);

    // NodeImpl::NodeImpl() | Implicitly-declared
    engine->RegisterObjectBehaviour("NodeImpl", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<NodeImpl>), AS_CALL_CDECL_OBJFIRST);

    // OcclusionBatch::OcclusionBatch() | Implicitly-declared
    engine->RegisterObjectBehaviour("OcclusionBatch", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<OcclusionBatch>), AS_CALL_CDECL_OBJFIRST);

    // OcclusionBufferData::OcclusionBufferData() | Implicitly-declared
    engine->RegisterObjectBehaviour("OcclusionBufferData", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<OcclusionBufferData>), AS_CALL_CDECL_OBJFIRST);

    // OctreeQueryResult::OctreeQueryResult() | File: ../Graphics/OctreeQuery.h
    engine->RegisterObjectBehaviour("OctreeQueryResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<OctreeQueryResult>), AS_CALL_CDECL_OBJFIRST);

    // Particle::Particle() | Implicitly-declared
    engine->RegisterObjectBehaviour("Particle", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Particle>), AS_CALL_CDECL_OBJFIRST);

    // PerThreadSceneResult::PerThreadSceneResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("PerThreadSceneResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<PerThreadSceneResult>), AS_CALL_CDECL_OBJFIRST);

    // Plane::Plane() noexcept | File: ../Math/Plane.h
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Plane>), AS_CALL_CDECL_OBJFIRST);

    // Polyhedron::Polyhedron() noexcept = default | File: ../Math/Polyhedron.h
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Polyhedron>), AS_CALL_CDECL_OBJFIRST);

    // Quaternion::Quaternion() noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Quaternion>), AS_CALL_CDECL_OBJFIRST);

    // Ray::Ray() noexcept = default | File: ../Math/Ray.h
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Ray>), AS_CALL_CDECL_OBJFIRST);

    // RayQueryResult::RayQueryResult() | File: ../Graphics/OctreeQuery.h
    engine->RegisterObjectBehaviour("RayQueryResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<RayQueryResult>), AS_CALL_CDECL_OBJFIRST);

    // Rect::Rect() noexcept | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Rect>), AS_CALL_CDECL_OBJFIRST);

    // RefCount::RefCount() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RefCount", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<RefCount>), AS_CALL_CDECL_OBJFIRST);

    // RefCounted::RefCounted() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RefCounted", asBEHAVE_FACTORY, "RefCounted@+ f()", asFUNCTION(ASCompatibleFactory<RefCounted>), AS_CALL_CDECL);

    // RenderPathCommand::RenderPathCommand() | Implicitly-declared
    engine->RegisterObjectBehaviour("RenderPathCommand", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<RenderPathCommand>), AS_CALL_CDECL_OBJFIRST);

    // RenderTargetInfo::RenderTargetInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("RenderTargetInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<RenderTargetInfo>), AS_CALL_CDECL_OBJFIRST);

    // ReplicationState::ReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("ReplicationState", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ReplicationState>), AS_CALL_CDECL_OBJFIRST);

    // ResourceGroup::ResourceGroup() | File: ../Resource/ResourceCache.h
    engine->RegisterObjectBehaviour("ResourceGroup", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ResourceGroup>), AS_CALL_CDECL_OBJFIRST);

    // ResourceRef::ResourceRef() = default | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ResourceRef>), AS_CALL_CDECL_OBJFIRST);

    // ResourceRefList::ResourceRefList() = default | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ResourceRefList>), AS_CALL_CDECL_OBJFIRST);

    // ScenePassInfo::ScenePassInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("ScenePassInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ScenePassInfo>), AS_CALL_CDECL_OBJFIRST);

    // SceneResolver::SceneResolver() | File: ../Scene/SceneResolver.h
    engine->RegisterObjectBehaviour("SceneResolver", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<SceneResolver>), AS_CALL_CDECL_OBJFIRST);

    // ScratchBuffer::ScratchBuffer() | File: ../Graphics/Graphics.h
    engine->RegisterObjectBehaviour("ScratchBuffer", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ScratchBuffer>), AS_CALL_CDECL_OBJFIRST);

    // ScreenModeParams::ScreenModeParams() | Implicitly-declared
    engine->RegisterObjectBehaviour("ScreenModeParams", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ScreenModeParams>), AS_CALL_CDECL_OBJFIRST);

    // ShaderParameter::ShaderParameter() = default | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectBehaviour("ShaderParameter", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ShaderParameter>), AS_CALL_CDECL_OBJFIRST);

    // ShadowBatchQueue::ShadowBatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("ShadowBatchQueue", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ShadowBatchQueue>), AS_CALL_CDECL_OBJFIRST);

    // Skeleton::Skeleton() | File: ../Graphics/Skeleton.h
    engine->RegisterObjectBehaviour("Skeleton", asBEHAVE_FACTORY, "Skeleton@+ f()", asFUNCTION(ASCompatibleFactory<Skeleton>), AS_CALL_CDECL);

    // SourceBatch::SourceBatch() | File: ../Graphics/Drawable.h
    engine->RegisterObjectBehaviour("SourceBatch", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<SourceBatch>), AS_CALL_CDECL_OBJFIRST);

    // Sphere::Sphere() noexcept | File: ../Math/Sphere.h
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Sphere>), AS_CALL_CDECL_OBJFIRST);

    // Spline::Spline() | File: ../Core/Spline.h
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Spline>), AS_CALL_CDECL_OBJFIRST);

    // StaticModelGeometryData::StaticModelGeometryData() | Implicitly-declared
    engine->RegisterObjectBehaviour("StaticModelGeometryData", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<StaticModelGeometryData>), AS_CALL_CDECL_OBJFIRST);

    // StoredLogMessage::StoredLogMessage() = default | File: ../IO/Log.h
    engine->RegisterObjectBehaviour("StoredLogMessage", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<StoredLogMessage>), AS_CALL_CDECL_OBJFIRST);

    // String::String() noexcept | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<String>), AS_CALL_CDECL_OBJFIRST);

    // StringHash::StringHash() noexcept | File: ../Math/StringHash.h
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<StringHash>), AS_CALL_CDECL_OBJFIRST);

    // TechniqueEntry::TechniqueEntry() noexcept | File: ../Graphics/Material.h
    engine->RegisterObjectBehaviour("TechniqueEntry", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<TechniqueEntry>), AS_CALL_CDECL_OBJFIRST);

    // TextureFrame::TextureFrame() | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectBehaviour("TextureFrame", asBEHAVE_FACTORY, "TextureFrame@+ f()", asFUNCTION(ASCompatibleFactory<TextureFrame>), AS_CALL_CDECL);

    // Timer::Timer() | File: ../Core/Timer.h
    engine->RegisterObjectBehaviour("Timer", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Timer>), AS_CALL_CDECL_OBJFIRST);

    // TrailPoint::TrailPoint() = default | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectBehaviour("TrailPoint", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<TrailPoint>), AS_CALL_CDECL_OBJFIRST);

    // UIBatch::UIBatch() | File: ../UI/UIBatch.h
    engine->RegisterObjectBehaviour("UIBatch", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<UIBatch>), AS_CALL_CDECL_OBJFIRST);

    // VAnimEventFrame::VAnimEventFrame() | Implicitly-declared
    engine->RegisterObjectBehaviour("VAnimEventFrame", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<VAnimEventFrame>), AS_CALL_CDECL_OBJFIRST);

    // VAnimKeyFrame::VAnimKeyFrame() | Implicitly-declared
    engine->RegisterObjectBehaviour("VAnimKeyFrame", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<VAnimKeyFrame>), AS_CALL_CDECL_OBJFIRST);

    // Variant::Variant() = default | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Variant>), AS_CALL_CDECL_OBJFIRST);

    // Vector2::Vector2() noexcept | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Vector2>), AS_CALL_CDECL_OBJFIRST);

    // Vector3::Vector3() noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Vector3>), AS_CALL_CDECL_OBJFIRST);

    // Vector4::Vector4() noexcept | File: ../Math/Vector4.h
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Vector4>), AS_CALL_CDECL_OBJFIRST);

    // VectorBase::VectorBase() noexcept | File: ../Container/VectorBase.h
    engine->RegisterObjectBehaviour("VectorBase", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<VectorBase>), AS_CALL_CDECL_OBJFIRST);

    // VertexBufferDesc::VertexBufferDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("VertexBufferDesc", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<VertexBufferDesc>), AS_CALL_CDECL_OBJFIRST);

    // VertexBufferMorph::VertexBufferMorph() | Implicitly-declared
    engine->RegisterObjectBehaviour("VertexBufferMorph", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<VertexBufferMorph>), AS_CALL_CDECL_OBJFIRST);

    // VertexElement::VertexElement() noexcept | File: ../Graphics/GraphicsDefs.h
    engine->RegisterObjectBehaviour("VertexElement", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<VertexElement>), AS_CALL_CDECL_OBJFIRST);

    // WindowModeParams::WindowModeParams() | Implicitly-declared
    engine->RegisterObjectBehaviour("WindowModeParams", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<WindowModeParams>), AS_CALL_CDECL_OBJFIRST);

    // XMLElement::XMLElement() | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<XMLElement>), AS_CALL_CDECL_OBJFIRST);

    // XPathQuery::XPathQuery() | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XPathQuery", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<XPathQuery>), AS_CALL_CDECL_OBJFIRST);

    // XPathResultSet::XPathResultSet() | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XPathResultSet", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<XPathResultSet>), AS_CALL_CDECL_OBJFIRST);

#ifdef URHO3D_NAVIGATION
    // NavAreaStub::NavAreaStub() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavAreaStub", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<NavAreaStub>), AS_CALL_CDECL_OBJFIRST);

    // NavBuildData::NavBuildData() | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectBehaviour("NavBuildData", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<NavBuildData>), AS_CALL_CDECL_OBJFIRST);

    // NavigationGeometryInfo::NavigationGeometryInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavigationGeometryInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<NavigationGeometryInfo>), AS_CALL_CDECL_OBJFIRST);

    // NavigationPathPoint::NavigationPathPoint() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavigationPathPoint", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<NavigationPathPoint>), AS_CALL_CDECL_OBJFIRST);
#endif

#ifdef URHO3D_NETWORK
    // PackageDownload::PackageDownload() | File: ../Network/Connection.h
    engine->RegisterObjectBehaviour("PackageDownload", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<PackageDownload>), AS_CALL_CDECL_OBJFIRST);

    // PackageUpload::PackageUpload() | File: ../Network/Connection.h
    engine->RegisterObjectBehaviour("PackageUpload", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<PackageUpload>), AS_CALL_CDECL_OBJFIRST);

    // RemoteEvent::RemoteEvent() | Implicitly-declared
    engine->RegisterObjectBehaviour("RemoteEvent", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<RemoteEvent>), AS_CALL_CDECL_OBJFIRST);
#endif

#ifdef URHO3D_PHYSICS
    // DelayedWorldTransform::DelayedWorldTransform() | Implicitly-declared
    engine->RegisterObjectBehaviour("DelayedWorldTransform", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<DelayedWorldTransform>), AS_CALL_CDECL_OBJFIRST);

    // ManifoldPair::ManifoldPair() | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectBehaviour("ManifoldPair", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ManifoldPair>), AS_CALL_CDECL_OBJFIRST);

    // PhysicsRaycastResult::PhysicsRaycastResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("PhysicsRaycastResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<PhysicsRaycastResult>), AS_CALL_CDECL_OBJFIRST);

    // PhysicsWorldConfig::PhysicsWorldConfig() | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectBehaviour("PhysicsWorldConfig", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<PhysicsWorldConfig>), AS_CALL_CDECL_OBJFIRST);
#endif

#ifdef URHO3D_URHO2D
    // DelayedWorldTransform2D::DelayedWorldTransform2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("DelayedWorldTransform2D", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<DelayedWorldTransform2D>), AS_CALL_CDECL_OBJFIRST);

    // Particle2D::Particle2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("Particle2D", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Particle2D>), AS_CALL_CDECL_OBJFIRST);

    // PhysicsRaycastResult2D::PhysicsRaycastResult2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("PhysicsRaycastResult2D", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<PhysicsRaycastResult2D>), AS_CALL_CDECL_OBJFIRST);

    // SourceBatch2D::SourceBatch2D() | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectBehaviour("SourceBatch2D", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<SourceBatch2D>), AS_CALL_CDECL_OBJFIRST);

    // Vertex2D::Vertex2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("Vertex2D", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<Vertex2D>), AS_CALL_CDECL_OBJFIRST);
#endif

    // BatchGroup::BatchGroup() | File: ../Graphics/Batch.h
    engine->RegisterObjectBehaviour("BatchGroup", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<BatchGroup>), AS_CALL_CDECL_OBJFIRST);

    // ComponentReplicationState::ComponentReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("ComponentReplicationState", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<ComponentReplicationState>), AS_CALL_CDECL_OBJFIRST);

    // Context::Context() | File: ../Core/Context.h
    engine->RegisterObjectBehaviour("Context", asBEHAVE_FACTORY, "Context@+ f()", asFUNCTION(ASCompatibleFactory<Context>), AS_CALL_CDECL);

    // EventReceiverGroup::EventReceiverGroup() | File: ../Core/Context.h
    engine->RegisterObjectBehaviour("EventReceiverGroup", asBEHAVE_FACTORY, "EventReceiverGroup@+ f()", asFUNCTION(ASCompatibleFactory<EventReceiverGroup>), AS_CALL_CDECL);

    // NodeReplicationState::NodeReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("NodeReplicationState", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<NodeReplicationState>), AS_CALL_CDECL_OBJFIRST);

    // RenderPath::RenderPath() | File: ../Graphics/RenderPath.h
    engine->RegisterObjectBehaviour("RenderPath", asBEHAVE_FACTORY, "RenderPath@+ f()", asFUNCTION(ASCompatibleFactory<RenderPath>), AS_CALL_CDECL);

    // SceneReplicationState::SceneReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("SceneReplicationState", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<SceneReplicationState>), AS_CALL_CDECL_OBJFIRST);

#ifdef URHO3D_NAVIGATION
    // SimpleNavBuildData::SimpleNavBuildData() | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectBehaviour("SimpleNavBuildData", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<SimpleNavBuildData>), AS_CALL_CDECL_OBJFIRST);
#endif

#ifdef URHO3D_URHO2D
    // PropertySet2D::PropertySet2D() | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectBehaviour("PropertySet2D", asBEHAVE_FACTORY, "PropertySet2D@+ f()", asFUNCTION(ASCompatibleFactory<PropertySet2D>), AS_CALL_CDECL);

    // Tile2D::Tile2D() | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectBehaviour("Tile2D", asBEHAVE_FACTORY, "Tile2D@+ f()", asFUNCTION(ASCompatibleFactory<Tile2D>), AS_CALL_CDECL);

    // TileMapObject2D::TileMapObject2D() | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectBehaviour("TileMapObject2D", asBEHAVE_FACTORY, "TileMapObject2D@+ f()", asFUNCTION(ASCompatibleFactory<TileMapObject2D>), AS_CALL_CDECL);
#endif

    // BufferedSoundStream::BufferedSoundStream() | File: ../Audio/BufferedSoundStream.h
    engine->RegisterObjectBehaviour("BufferedSoundStream", asBEHAVE_FACTORY, "BufferedSoundStream@+ f()", asFUNCTION(ASCompatibleFactory<BufferedSoundStream>), AS_CALL_CDECL);

    // VectorBuffer::VectorBuffer() | File: ../IO/VectorBuffer.h
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ASCompatibleConstructor<VectorBuffer>), AS_CALL_CDECL_OBJFIRST);
}

}
