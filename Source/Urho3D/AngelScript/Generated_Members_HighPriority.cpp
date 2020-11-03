// DO NOT EDIT. This file is generated

// We need register default constructors before any members to allow using in Array<type>

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../Container/Allocator.h"
#include "../Container/HashBase.h"
#include "../Container/LinkedList.h"
#include "../Container/ListBase.h"
#include "../Container/RefCounted.h"
#include "../Container/Str.h"
#include "../Container/VectorBase.h"
#include "../Core/Attribute.h"
#include "../Core/Condition.h"
#include "../Core/Mutex.h"
#include "../Core/Spline.h"
#include "../Core/Timer.h"
#include "../Core/Variant.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationState.h"
#include "../Graphics/Batch.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/DecalSet.h"
#include "../Graphics/Drawable.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicsDefs.h"
#include "../Graphics/Light.h"
#include "../Graphics/Material.h"
#include "../Graphics/Model.h"
#include "../Graphics/OcclusionBuffer.h"
#include "../Graphics/OctreeQuery.h"
#include "../Graphics/ParticleEmitter.h"
#include "../Graphics/RenderPath.h"
#include "../Graphics/RibbonTrail.h"
#include "../Graphics/ShaderVariation.h"
#include "../Graphics/StaticModel.h"
#include "../Graphics/View.h"
#include "../IO/Log.h"
#include "../IO/VectorBuffer.h"
#include "../Input/Controls.h"
#include "../Math/AreaAllocator.h"
#include "../Math/BoundingBox.h"
#include "../Math/Color.h"
#include "../Math/Frustum.h"
#include "../Math/Matrix2.h"
#include "../Math/Matrix3.h"
#include "../Math/Matrix3x4.h"
#include "../Math/Matrix4.h"
#include "../Math/Plane.h"
#include "../Math/Polyhedron.h"
#include "../Math/Quaternion.h"
#include "../Math/Ray.h"
#include "../Math/Rect.h"
#include "../Math/Sphere.h"
#include "../Math/StringHash.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#ifdef URHO3D_NAVIGATION
#include "../Navigation/NavBuildData.h"
#endif
#ifdef URHO3D_NAVIGATION
#include "../Navigation/NavigationMesh.h"
#endif
#ifdef URHO3D_NETWORK
#include "../Network/Connection.h"
#endif
#ifdef URHO3D_PHYSICS
#include "../Physics/PhysicsWorld.h"
#endif
#include "../Resource/BackgroundLoader.h"
#include "../Resource/Image.h"
#include "../Resource/JSONValue.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/XMLElement.h"
#include "../Scene/Node.h"
#include "../Scene/ReplicationState.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResolver.h"
#include "../Scene/ValueAnimation.h"
#include "../UI/Cursor.h"
#include "../UI/FileSelector.h"
#include "../UI/FontFace.h"
#include "../UI/Text.h"
#include "../UI/UIBatch.h"
#ifdef URHO3D_URHO2D
#include "../Urho2D/Drawable2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ParticleEmitter2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/PhysicsWorld2D.h"
#endif

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// AreaAllocator::AreaAllocator() | File: ../Math/AreaAllocator.h
static void AreaAllocator_AreaAllocator_void(AreaAllocator* ptr)
{
    new(ptr) AreaAllocator();
}

// BoundingBox::BoundingBox() noexcept | File: ../Math/BoundingBox.h
static void BoundingBox_BoundingBox_void(BoundingBox* ptr)
{
    new(ptr) BoundingBox();
}

// Color::Color() noexcept | File: ../Math/Color.h
static void Color_Color_void(Color* ptr)
{
    new(ptr) Color();
}

// Condition::Condition() | File: ../Core/Condition.h
static void Condition_Condition_void(Condition* ptr)
{
    new(ptr) Condition();
}

// Controls::Controls() | File: ../Input/Controls.h
static void Controls_Controls_void(Controls* ptr)
{
    new(ptr) Controls();
}

// Frustum::Frustum() noexcept=default | File: ../Math/Frustum.h
static void Frustum_Frustum_void(Frustum* ptr)
{
    new(ptr) Frustum();
}

// HashBase::HashBase() | File: ../Container/HashBase.h
static void HashBase_HashBase_void(HashBase* ptr)
{
    new(ptr) HashBase();
}

// HiresTimer::HiresTimer() | File: ../Core/Timer.h
static void HiresTimer_HiresTimer_void(HiresTimer* ptr)
{
    new(ptr) HiresTimer();
}

// IntRect::IntRect() noexcept | File: ../Math/Rect.h
static void IntRect_IntRect_void(IntRect* ptr)
{
    new(ptr) IntRect();
}

// IntVector2::IntVector2() noexcept | File: ../Math/Vector2.h
static void IntVector2_IntVector2_void(IntVector2* ptr)
{
    new(ptr) IntVector2();
}

// IntVector3::IntVector3() noexcept | File: ../Math/Vector3.h
static void IntVector3_IntVector3_void(IntVector3* ptr)
{
    new(ptr) IntVector3();
}

// JSONValue::JSONValue() | File: ../Resource/JSONValue.h
static void JSONValue_JSONValue_void(JSONValue* ptr)
{
    new(ptr) JSONValue();
}

// ListBase::ListBase() | File: ../Container/ListBase.h
static void ListBase_ListBase_void(ListBase* ptr)
{
    new(ptr) ListBase();
}

// Matrix2::Matrix2() noexcept | File: ../Math/Matrix2.h
static void Matrix2_Matrix2_void(Matrix2* ptr)
{
    new(ptr) Matrix2();
}

// Matrix3::Matrix3() noexcept | File: ../Math/Matrix3.h
static void Matrix3_Matrix3_void(Matrix3* ptr)
{
    new(ptr) Matrix3();
}

// Matrix3x4::Matrix3x4() noexcept | File: ../Math/Matrix3x4.h
static void Matrix3x4_Matrix3x4_void(Matrix3x4* ptr)
{
    new(ptr) Matrix3x4();
}

// Matrix4::Matrix4() noexcept | File: ../Math/Matrix4.h
static void Matrix4_Matrix4_void(Matrix4* ptr)
{
    new(ptr) Matrix4();
}

// Mutex::Mutex() | File: ../Core/Mutex.h
static void Mutex_Mutex_void(Mutex* ptr)
{
    new(ptr) Mutex();
}

// Plane::Plane() noexcept | File: ../Math/Plane.h
static void Plane_Plane_void(Plane* ptr)
{
    new(ptr) Plane();
}

// Polyhedron::Polyhedron() noexcept=default | File: ../Math/Polyhedron.h
static void Polyhedron_Polyhedron_void(Polyhedron* ptr)
{
    new(ptr) Polyhedron();
}

// Quaternion::Quaternion() noexcept | File: ../Math/Quaternion.h
static void Quaternion_Quaternion_void(Quaternion* ptr)
{
    new(ptr) Quaternion();
}

// Ray::Ray() noexcept=default | File: ../Math/Ray.h
static void Ray_Ray_void(Ray* ptr)
{
    new(ptr) Ray();
}

// Rect::Rect() noexcept | File: ../Math/Rect.h
static void Rect_Rect_void(Rect* ptr)
{
    new(ptr) Rect();
}

// SceneResolver::SceneResolver() | File: ../Scene/SceneResolver.h
static void SceneResolver_SceneResolver_void(SceneResolver* ptr)
{
    new(ptr) SceneResolver();
}

// Sphere::Sphere() noexcept | File: ../Math/Sphere.h
static void Sphere_Sphere_void(Sphere* ptr)
{
    new(ptr) Sphere();
}

// Spline::Spline() | File: ../Core/Spline.h
static void Spline_Spline_void(Spline* ptr)
{
    new(ptr) Spline();
}

// String::String() noexcept | File: ../Container/Str.h
static void String_String_void(String* ptr)
{
    new(ptr) String();
}

// StringHash::StringHash() noexcept | File: ../Math/StringHash.h
static void StringHash_StringHash_void(StringHash* ptr)
{
    new(ptr) StringHash();
}

// Timer::Timer() | File: ../Core/Timer.h
static void Timer_Timer_void(Timer* ptr)
{
    new(ptr) Timer();
}

// UIBatch::UIBatch() | File: ../UI/UIBatch.h
static void UIBatch_UIBatch_void(UIBatch* ptr)
{
    new(ptr) UIBatch();
}

// Variant::Variant()=default | File: ../Core/Variant.h
static void Variant_Variant_void(Variant* ptr)
{
    new(ptr) Variant();
}

// Vector2::Vector2() noexcept | File: ../Math/Vector2.h
static void Vector2_Vector2_void(Vector2* ptr)
{
    new(ptr) Vector2();
}

// Vector3::Vector3() noexcept | File: ../Math/Vector3.h
static void Vector3_Vector3_void(Vector3* ptr)
{
    new(ptr) Vector3();
}

// Vector4::Vector4() noexcept | File: ../Math/Vector4.h
static void Vector4_Vector4_void(Vector4* ptr)
{
    new(ptr) Vector4();
}

// VectorBase::VectorBase() noexcept | File: ../Container/VectorBase.h
static void VectorBase_VectorBase_void(VectorBase* ptr)
{
    new(ptr) VectorBase();
}

// VectorBuffer::VectorBuffer() | File: ../IO/VectorBuffer.h
static void VectorBuffer_VectorBuffer_void(VectorBuffer* ptr)
{
    new(ptr) VectorBuffer();
}

// XMLElement::XMLElement() | File: ../Resource/XMLElement.h
static void XMLElement_XMLElement_void(XMLElement* ptr)
{
    new(ptr) XMLElement();
}

// XPathQuery::XPathQuery() | File: ../Resource/XMLElement.h
static void XPathQuery_XPathQuery_void(XPathQuery* ptr)
{
    new(ptr) XPathQuery();
}

// XPathResultSet::XPathResultSet() | File: ../Resource/XMLElement.h
static void XPathResultSet_XPathResultSet_void(XPathResultSet* ptr)
{
    new(ptr) XPathResultSet();
}

// AllocatorBlock::AllocatorBlock() | Implicitly-declared
static void AllocatorBlock_Constructor(AllocatorBlock* ptr)
{
    new(ptr) AllocatorBlock();
}

// AllocatorNode::AllocatorNode() | Implicitly-declared
static void AllocatorNode_Constructor(AllocatorNode* ptr)
{
    new(ptr) AllocatorNode();
}

// AnimationKeyFrame::AnimationKeyFrame() | File: ../Graphics/Animation.h
static void AnimationKeyFrame_AnimationKeyFrame_void(AnimationKeyFrame* ptr)
{
    new(ptr) AnimationKeyFrame();
}

// AnimationStateTrack::AnimationStateTrack() | File: ../Graphics/AnimationState.h
static void AnimationStateTrack_AnimationStateTrack_void(AnimationStateTrack* ptr)
{
    new(ptr) AnimationStateTrack();
}

// AnimationTriggerPoint::AnimationTriggerPoint() | File: ../Graphics/Animation.h
static void AnimationTriggerPoint_AnimationTriggerPoint_void(AnimationTriggerPoint* ptr)
{
    new(ptr) AnimationTriggerPoint();
}

// AsyncProgress::AsyncProgress() | Implicitly-declared
static void AsyncProgress_Constructor(AsyncProgress* ptr)
{
    new(ptr) AsyncProgress();
}

// AttributeInfo::AttributeInfo()=default | File: ../Core/Attribute.h
static void AttributeInfo_AttributeInfo_void(AttributeInfo* ptr)
{
    new(ptr) AttributeInfo();
}

// BackgroundLoadItem::BackgroundLoadItem() | Implicitly-declared
static void BackgroundLoadItem_Constructor(BackgroundLoadItem* ptr)
{
    new(ptr) BackgroundLoadItem();
}

// Batch::Batch()=default | File: ../Graphics/Batch.h
static void Batch_Batch_void(Batch* ptr)
{
    new(ptr) Batch();
}

// BatchGroup::BatchGroup() | File: ../Graphics/Batch.h
static void BatchGroup_BatchGroup_void(BatchGroup* ptr)
{
    new(ptr) BatchGroup();
}

// BatchGroupKey::BatchGroupKey()=default | File: ../Graphics/Batch.h
static void BatchGroupKey_BatchGroupKey_void(BatchGroupKey* ptr)
{
    new(ptr) BatchGroupKey();
}

// BatchQueue::BatchQueue() | Implicitly-declared
static void BatchQueue_Constructor(BatchQueue* ptr)
{
    new(ptr) BatchQueue();
}

// BiasParameters::BiasParameters()=default | File: ../Graphics/Light.h
static void BiasParameters_BiasParameters_void(BiasParameters* ptr)
{
    new(ptr) BiasParameters();
}

// CascadeParameters::CascadeParameters()=default | File: ../Graphics/Light.h
static void CascadeParameters_CascadeParameters_void(CascadeParameters* ptr)
{
    new(ptr) CascadeParameters();
}

// CharLocation::CharLocation() | Implicitly-declared
static void CharLocation_Constructor(CharLocation* ptr)
{
    new(ptr) CharLocation();
}

// ComponentReplicationState::ComponentReplicationState() | Implicitly-declared
static void ComponentReplicationState_Constructor(ComponentReplicationState* ptr)
{
    new(ptr) ComponentReplicationState();
}

// CompressedLevel::CompressedLevel() | Implicitly-declared
static void CompressedLevel_Constructor(CompressedLevel* ptr)
{
    new(ptr) CompressedLevel();
}

// CursorShapeInfo::CursorShapeInfo() | File: ../UI/Cursor.h
static void CursorShapeInfo_CursorShapeInfo_void(CursorShapeInfo* ptr)
{
    new(ptr) CursorShapeInfo();
}

// DebugLine::DebugLine()=default | File: ../Graphics/DebugRenderer.h
static void DebugLine_DebugLine_void(DebugLine* ptr)
{
    new(ptr) DebugLine();
}

// DebugTriangle::DebugTriangle()=default | File: ../Graphics/DebugRenderer.h
static void DebugTriangle_DebugTriangle_void(DebugTriangle* ptr)
{
    new(ptr) DebugTriangle();
}

// Decal::Decal() | File: ../Graphics/DecalSet.h
static void Decal_Decal_void(Decal* ptr)
{
    new(ptr) Decal();
}

// DecalVertex::DecalVertex()=default | File: ../Graphics/DecalSet.h
static void DecalVertex_DecalVertex_void(DecalVertex* ptr)
{
    new(ptr) DecalVertex();
}

#ifdef URHO3D_PHYSICS
// DelayedWorldTransform::DelayedWorldTransform() | Implicitly-declared
static void DelayedWorldTransform_Constructor(DelayedWorldTransform* ptr)
{
    new(ptr) DelayedWorldTransform();
}
#endif

#ifdef URHO3D_URHO2D
// DelayedWorldTransform2D::DelayedWorldTransform2D() | Implicitly-declared
static void DelayedWorldTransform2D_Constructor(DelayedWorldTransform2D* ptr)
{
    new(ptr) DelayedWorldTransform2D();
}
#endif

// DirtyBits::DirtyBits()=default | File: ../Scene/ReplicationState.h
static void DirtyBits_DirtyBits_void(DirtyBits* ptr)
{
    new(ptr) DirtyBits();
}

// FileSelectorEntry::FileSelectorEntry() | Implicitly-declared
static void FileSelectorEntry_Constructor(FileSelectorEntry* ptr)
{
    new(ptr) FileSelectorEntry();
}

// FocusParameters::FocusParameters()=default | File: ../Graphics/Light.h
static void FocusParameters_FocusParameters_void(FocusParameters* ptr)
{
    new(ptr) FocusParameters();
}

// FontGlyph::FontGlyph() | Implicitly-declared
static void FontGlyph_Constructor(FontGlyph* ptr)
{
    new(ptr) FontGlyph();
}

// FrameInfo::FrameInfo() | Implicitly-declared
static void FrameInfo_Constructor(FrameInfo* ptr)
{
    new(ptr) FrameInfo();
}

// GeometryDesc::GeometryDesc() | Implicitly-declared
static void GeometryDesc_Constructor(GeometryDesc* ptr)
{
    new(ptr) GeometryDesc();
}

// HashIteratorBase::HashIteratorBase() | File: ../Container/HashBase.h
static void HashIteratorBase_HashIteratorBase_void(HashIteratorBase* ptr)
{
    new(ptr) HashIteratorBase();
}

// HashNodeBase::HashNodeBase() | File: ../Container/HashBase.h
static void HashNodeBase_HashNodeBase_void(HashNodeBase* ptr)
{
    new(ptr) HashNodeBase();
}

// IndexBufferDesc::IndexBufferDesc() | Implicitly-declared
static void IndexBufferDesc_Constructor(IndexBufferDesc* ptr)
{
    new(ptr) IndexBufferDesc();
}

// InstanceData::InstanceData()=default | File: ../Graphics/Batch.h
static void InstanceData_InstanceData_void(InstanceData* ptr)
{
    new(ptr) InstanceData();
}

// LightBatchQueue::LightBatchQueue() | Implicitly-declared
static void LightBatchQueue_Constructor(LightBatchQueue* ptr)
{
    new(ptr) LightBatchQueue();
}

// LightQueryResult::LightQueryResult() | Implicitly-declared
static void LightQueryResult_Constructor(LightQueryResult* ptr)
{
    new(ptr) LightQueryResult();
}

// LinkedListNode::LinkedListNode() | File: ../Container/LinkedList.h
static void LinkedListNode_LinkedListNode_void(LinkedListNode* ptr)
{
    new(ptr) LinkedListNode();
}

// ListIteratorBase::ListIteratorBase() | File: ../Container/ListBase.h
static void ListIteratorBase_ListIteratorBase_void(ListIteratorBase* ptr)
{
    new(ptr) ListIteratorBase();
}

// ListNodeBase::ListNodeBase() | File: ../Container/ListBase.h
static void ListNodeBase_ListNodeBase_void(ListNodeBase* ptr)
{
    new(ptr) ListNodeBase();
}

#ifdef URHO3D_PHYSICS
// ManifoldPair::ManifoldPair() | File: ../Physics/PhysicsWorld.h
static void ManifoldPair_ManifoldPair_void(ManifoldPair* ptr)
{
    new(ptr) ManifoldPair();
}
#endif

// MaterialShaderParameter::MaterialShaderParameter() | Implicitly-declared
static void MaterialShaderParameter_Constructor(MaterialShaderParameter* ptr)
{
    new(ptr) MaterialShaderParameter();
}

// ModelMorph::ModelMorph() | Implicitly-declared
static void ModelMorph_Constructor(ModelMorph* ptr)
{
    new(ptr) ModelMorph();
}

#ifdef URHO3D_NAVIGATION
// NavAreaStub::NavAreaStub() | Implicitly-declared
static void NavAreaStub_Constructor(NavAreaStub* ptr)
{
    new(ptr) NavAreaStub();
}
#endif

#ifdef URHO3D_NAVIGATION
// NavBuildData::NavBuildData() | File: ../Navigation/NavBuildData.h
static void NavBuildData_NavBuildData_void(NavBuildData* ptr)
{
    new(ptr) NavBuildData();
}
#endif

#ifdef URHO3D_NAVIGATION
// NavigationGeometryInfo::NavigationGeometryInfo() | Implicitly-declared
static void NavigationGeometryInfo_Constructor(NavigationGeometryInfo* ptr)
{
    new(ptr) NavigationGeometryInfo();
}
#endif

#ifdef URHO3D_NAVIGATION
// NavigationPathPoint::NavigationPathPoint() | Implicitly-declared
static void NavigationPathPoint_Constructor(NavigationPathPoint* ptr)
{
    new(ptr) NavigationPathPoint();
}
#endif

// NetworkState::NetworkState() | Implicitly-declared
static void NetworkState_Constructor(NetworkState* ptr)
{
    new(ptr) NetworkState();
}

// NodeImpl::NodeImpl() | Implicitly-declared
static void NodeImpl_Constructor(NodeImpl* ptr)
{
    new(ptr) NodeImpl();
}

// NodeReplicationState::NodeReplicationState() | Implicitly-declared
static void NodeReplicationState_Constructor(NodeReplicationState* ptr)
{
    new(ptr) NodeReplicationState();
}

// OcclusionBatch::OcclusionBatch() | Implicitly-declared
static void OcclusionBatch_Constructor(OcclusionBatch* ptr)
{
    new(ptr) OcclusionBatch();
}

// OcclusionBufferData::OcclusionBufferData() | Implicitly-declared
static void OcclusionBufferData_Constructor(OcclusionBufferData* ptr)
{
    new(ptr) OcclusionBufferData();
}

// OctreeQueryResult::OctreeQueryResult() | File: ../Graphics/OctreeQuery.h
static void OctreeQueryResult_OctreeQueryResult_void(OctreeQueryResult* ptr)
{
    new(ptr) OctreeQueryResult();
}

#ifdef URHO3D_NETWORK
// PackageDownload::PackageDownload() | File: ../Network/Connection.h
static void PackageDownload_PackageDownload_void(PackageDownload* ptr)
{
    new(ptr) PackageDownload();
}
#endif

#ifdef URHO3D_NETWORK
// PackageUpload::PackageUpload() | File: ../Network/Connection.h
static void PackageUpload_PackageUpload_void(PackageUpload* ptr)
{
    new(ptr) PackageUpload();
}
#endif

// Particle::Particle() | Implicitly-declared
static void Particle_Constructor(Particle* ptr)
{
    new(ptr) Particle();
}

#ifdef URHO3D_URHO2D
// Particle2D::Particle2D() | Implicitly-declared
static void Particle2D_Constructor(Particle2D* ptr)
{
    new(ptr) Particle2D();
}
#endif

// PerThreadSceneResult::PerThreadSceneResult() | Implicitly-declared
static void PerThreadSceneResult_Constructor(PerThreadSceneResult* ptr)
{
    new(ptr) PerThreadSceneResult();
}

#ifdef URHO3D_PHYSICS
// PhysicsRaycastResult::PhysicsRaycastResult() | Implicitly-declared
static void PhysicsRaycastResult_Constructor(PhysicsRaycastResult* ptr)
{
    new(ptr) PhysicsRaycastResult();
}
#endif

#ifdef URHO3D_URHO2D
// PhysicsRaycastResult2D::PhysicsRaycastResult2D() | Implicitly-declared
static void PhysicsRaycastResult2D_Constructor(PhysicsRaycastResult2D* ptr)
{
    new(ptr) PhysicsRaycastResult2D();
}
#endif

#ifdef URHO3D_PHYSICS
// PhysicsWorldConfig::PhysicsWorldConfig() | File: ../Physics/PhysicsWorld.h
static void PhysicsWorldConfig_PhysicsWorldConfig_void(PhysicsWorldConfig* ptr)
{
    new(ptr) PhysicsWorldConfig();
}
#endif

// RayQueryResult::RayQueryResult() | File: ../Graphics/OctreeQuery.h
static void RayQueryResult_RayQueryResult_void(RayQueryResult* ptr)
{
    new(ptr) RayQueryResult();
}

// RefCount::RefCount() | File: ../Container/RefCounted.h
static void RefCount_RefCount_void(RefCount* ptr)
{
    new(ptr) RefCount();
}

#ifdef URHO3D_NETWORK
// RemoteEvent::RemoteEvent() | Implicitly-declared
static void RemoteEvent_Constructor(RemoteEvent* ptr)
{
    new(ptr) RemoteEvent();
}
#endif

// RenderPathCommand::RenderPathCommand() | Implicitly-declared
static void RenderPathCommand_Constructor(RenderPathCommand* ptr)
{
    new(ptr) RenderPathCommand();
}

// RenderTargetInfo::RenderTargetInfo() | Implicitly-declared
static void RenderTargetInfo_Constructor(RenderTargetInfo* ptr)
{
    new(ptr) RenderTargetInfo();
}

// ReplicationState::ReplicationState() | Implicitly-declared
static void ReplicationState_Constructor(ReplicationState* ptr)
{
    new(ptr) ReplicationState();
}

// ResourceGroup::ResourceGroup() | File: ../Resource/ResourceCache.h
static void ResourceGroup_ResourceGroup_void(ResourceGroup* ptr)
{
    new(ptr) ResourceGroup();
}

// ResourceRef::ResourceRef()=default | File: ../Core/Variant.h
static void ResourceRef_ResourceRef_void(ResourceRef* ptr)
{
    new(ptr) ResourceRef();
}

// ResourceRefList::ResourceRefList()=default | File: ../Core/Variant.h
static void ResourceRefList_ResourceRefList_void(ResourceRefList* ptr)
{
    new(ptr) ResourceRefList();
}

// ScenePassInfo::ScenePassInfo() | Implicitly-declared
static void ScenePassInfo_Constructor(ScenePassInfo* ptr)
{
    new(ptr) ScenePassInfo();
}

// SceneReplicationState::SceneReplicationState() | Implicitly-declared
static void SceneReplicationState_Constructor(SceneReplicationState* ptr)
{
    new(ptr) SceneReplicationState();
}

// ScratchBuffer::ScratchBuffer() | File: ../Graphics/Graphics.h
static void ScratchBuffer_ScratchBuffer_void(ScratchBuffer* ptr)
{
    new(ptr) ScratchBuffer();
}

// ScreenModeParams::ScreenModeParams() | Implicitly-declared
static void ScreenModeParams_Constructor(ScreenModeParams* ptr)
{
    new(ptr) ScreenModeParams();
}

// ShaderParameter::ShaderParameter()=default | File: ../Graphics/ShaderVariation.h
static void ShaderParameter_ShaderParameter_void(ShaderParameter* ptr)
{
    new(ptr) ShaderParameter();
}

// ShadowBatchQueue::ShadowBatchQueue() | Implicitly-declared
static void ShadowBatchQueue_Constructor(ShadowBatchQueue* ptr)
{
    new(ptr) ShadowBatchQueue();
}

#ifdef URHO3D_NAVIGATION
// SimpleNavBuildData::SimpleNavBuildData() | File: ../Navigation/NavBuildData.h
static void SimpleNavBuildData_SimpleNavBuildData_void(SimpleNavBuildData* ptr)
{
    new(ptr) SimpleNavBuildData();
}
#endif

// SourceBatch::SourceBatch() | File: ../Graphics/Drawable.h
static void SourceBatch_SourceBatch_void(SourceBatch* ptr)
{
    new(ptr) SourceBatch();
}

#ifdef URHO3D_URHO2D
// SourceBatch2D::SourceBatch2D() | File: ../Urho2D/Drawable2D.h
static void SourceBatch2D_SourceBatch2D_void(SourceBatch2D* ptr)
{
    new(ptr) SourceBatch2D();
}
#endif

// StaticModelGeometryData::StaticModelGeometryData() | Implicitly-declared
static void StaticModelGeometryData_Constructor(StaticModelGeometryData* ptr)
{
    new(ptr) StaticModelGeometryData();
}

// StoredLogMessage::StoredLogMessage()=default | File: ../IO/Log.h
static void StoredLogMessage_StoredLogMessage_void(StoredLogMessage* ptr)
{
    new(ptr) StoredLogMessage();
}

// TechniqueEntry::TechniqueEntry() noexcept | File: ../Graphics/Material.h
static void TechniqueEntry_TechniqueEntry_void(TechniqueEntry* ptr)
{
    new(ptr) TechniqueEntry();
}

// TrailPoint::TrailPoint()=default | File: ../Graphics/RibbonTrail.h
static void TrailPoint_TrailPoint_void(TrailPoint* ptr)
{
    new(ptr) TrailPoint();
}

// VAnimEventFrame::VAnimEventFrame() | Implicitly-declared
static void VAnimEventFrame_Constructor(VAnimEventFrame* ptr)
{
    new(ptr) VAnimEventFrame();
}

// VAnimKeyFrame::VAnimKeyFrame() | Implicitly-declared
static void VAnimKeyFrame_Constructor(VAnimKeyFrame* ptr)
{
    new(ptr) VAnimKeyFrame();
}

#ifdef URHO3D_URHO2D
// Vertex2D::Vertex2D() | Implicitly-declared
static void Vertex2D_Constructor(Vertex2D* ptr)
{
    new(ptr) Vertex2D();
}
#endif

// VertexBufferDesc::VertexBufferDesc() | Implicitly-declared
static void VertexBufferDesc_Constructor(VertexBufferDesc* ptr)
{
    new(ptr) VertexBufferDesc();
}

// VertexBufferMorph::VertexBufferMorph() | Implicitly-declared
static void VertexBufferMorph_Constructor(VertexBufferMorph* ptr)
{
    new(ptr) VertexBufferMorph();
}

// VertexElement::VertexElement() noexcept | File: ../Graphics/GraphicsDefs.h
static void VertexElement_VertexElement_void(VertexElement* ptr)
{
    new(ptr) VertexElement();
}

// WindowModeParams::WindowModeParams() | Implicitly-declared
static void WindowModeParams_Constructor(WindowModeParams* ptr)
{
    new(ptr) WindowModeParams();
}

void ASRegisterGenerated_Members_HighPriority(asIScriptEngine* engine)
{
    // AreaAllocator::AreaAllocator() | File: ../Math/AreaAllocator.h
    engine->RegisterObjectBehaviour("AreaAllocator", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(AreaAllocator_AreaAllocator_void), asCALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox() noexcept | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(BoundingBox_BoundingBox_void), asCALL_CDECL_OBJFIRST);
    // Color::Color() noexcept | File: ../Math/Color.h
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Color_Color_void), asCALL_CDECL_OBJFIRST);
    // Condition::Condition() | File: ../Core/Condition.h
    engine->RegisterObjectBehaviour("Condition", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Condition_Condition_void), asCALL_CDECL_OBJFIRST);
    // Controls::Controls() | File: ../Input/Controls.h
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Controls_Controls_void), asCALL_CDECL_OBJFIRST);
    // Frustum::Frustum() noexcept=default | File: ../Math/Frustum.h
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Frustum_Frustum_void), asCALL_CDECL_OBJFIRST);
    // HashBase::HashBase() | File: ../Container/HashBase.h
    engine->RegisterObjectBehaviour("HashBase", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(HashBase_HashBase_void), asCALL_CDECL_OBJFIRST);
    // HiresTimer::HiresTimer() | File: ../Core/Timer.h
    engine->RegisterObjectBehaviour("HiresTimer", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(HiresTimer_HiresTimer_void), asCALL_CDECL_OBJFIRST);
    // IntRect::IntRect() noexcept | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(IntRect_IntRect_void), asCALL_CDECL_OBJFIRST);
    // IntVector2::IntVector2() noexcept | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(IntVector2_IntVector2_void), asCALL_CDECL_OBJFIRST);
    // IntVector3::IntVector3() noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(IntVector3_IntVector3_void), asCALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue() | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(JSONValue_JSONValue_void), asCALL_CDECL_OBJFIRST);
    // ListBase::ListBase() | File: ../Container/ListBase.h
    engine->RegisterObjectBehaviour("ListBase", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ListBase_ListBase_void), asCALL_CDECL_OBJFIRST);
    // Matrix2::Matrix2() noexcept | File: ../Math/Matrix2.h
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Matrix2_Matrix2_void), asCALL_CDECL_OBJFIRST);
    // Matrix3::Matrix3() noexcept | File: ../Math/Matrix3.h
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Matrix3_Matrix3_void), asCALL_CDECL_OBJFIRST);
    // Matrix3x4::Matrix3x4() noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Matrix3x4_Matrix3x4_void), asCALL_CDECL_OBJFIRST);
    // Matrix4::Matrix4() noexcept | File: ../Math/Matrix4.h
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Matrix4_Matrix4_void), asCALL_CDECL_OBJFIRST);
    // Mutex::Mutex() | File: ../Core/Mutex.h
    engine->RegisterObjectBehaviour("Mutex", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Mutex_Mutex_void), asCALL_CDECL_OBJFIRST);
    // Plane::Plane() noexcept | File: ../Math/Plane.h
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Plane_Plane_void), asCALL_CDECL_OBJFIRST);
    // Polyhedron::Polyhedron() noexcept=default | File: ../Math/Polyhedron.h
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Polyhedron_Polyhedron_void), asCALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion() noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Quaternion_Quaternion_void), asCALL_CDECL_OBJFIRST);
    // Ray::Ray() noexcept=default | File: ../Math/Ray.h
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Ray_Ray_void), asCALL_CDECL_OBJFIRST);
    // Rect::Rect() noexcept | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Rect_Rect_void), asCALL_CDECL_OBJFIRST);
    // SceneResolver::SceneResolver() | File: ../Scene/SceneResolver.h
    engine->RegisterObjectBehaviour("SceneResolver", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(SceneResolver_SceneResolver_void), asCALL_CDECL_OBJFIRST);
    // Sphere::Sphere() noexcept | File: ../Math/Sphere.h
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Sphere_Sphere_void), asCALL_CDECL_OBJFIRST);
    // Spline::Spline() | File: ../Core/Spline.h
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Spline_Spline_void), asCALL_CDECL_OBJFIRST);
    // String::String() noexcept | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(String_String_void), asCALL_CDECL_OBJFIRST);
    // StringHash::StringHash() noexcept | File: ../Math/StringHash.h
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(StringHash_StringHash_void), asCALL_CDECL_OBJFIRST);
    // Timer::Timer() | File: ../Core/Timer.h
    engine->RegisterObjectBehaviour("Timer", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Timer_Timer_void), asCALL_CDECL_OBJFIRST);
    // UIBatch::UIBatch() | File: ../UI/UIBatch.h
    engine->RegisterObjectBehaviour("UIBatch", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(UIBatch_UIBatch_void), asCALL_CDECL_OBJFIRST);
    // Variant::Variant()=default | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Variant_Variant_void), asCALL_CDECL_OBJFIRST);
    // Vector2::Vector2() noexcept | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vector2_Vector2_void), asCALL_CDECL_OBJFIRST);
    // Vector3::Vector3() noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vector3_Vector3_void), asCALL_CDECL_OBJFIRST);
    // Vector4::Vector4() noexcept | File: ../Math/Vector4.h
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vector4_Vector4_void), asCALL_CDECL_OBJFIRST);
    // VectorBase::VectorBase() noexcept | File: ../Container/VectorBase.h
    engine->RegisterObjectBehaviour("VectorBase", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(VectorBase_VectorBase_void), asCALL_CDECL_OBJFIRST);
    // VectorBuffer::VectorBuffer() | File: ../IO/VectorBuffer.h
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(VectorBuffer_VectorBuffer_void), asCALL_CDECL_OBJFIRST);
    // XMLElement::XMLElement() | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(XMLElement_XMLElement_void), asCALL_CDECL_OBJFIRST);
    // XPathQuery::XPathQuery() | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XPathQuery", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(XPathQuery_XPathQuery_void), asCALL_CDECL_OBJFIRST);
    // XPathResultSet::XPathResultSet() | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XPathResultSet", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(XPathResultSet_XPathResultSet_void), asCALL_CDECL_OBJFIRST);
    // AllocatorBlock::AllocatorBlock() | Implicitly-declared
    engine->RegisterObjectBehaviour("AllocatorBlock", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(AllocatorBlock_Constructor), asCALL_CDECL_OBJFIRST);
    // AllocatorNode::AllocatorNode() | Implicitly-declared
    engine->RegisterObjectBehaviour("AllocatorNode", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(AllocatorNode_Constructor), asCALL_CDECL_OBJFIRST);
    // AnimationKeyFrame::AnimationKeyFrame() | File: ../Graphics/Animation.h
    engine->RegisterObjectBehaviour("AnimationKeyFrame", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(AnimationKeyFrame_AnimationKeyFrame_void), asCALL_CDECL_OBJFIRST);
    // AnimationStateTrack::AnimationStateTrack() | File: ../Graphics/AnimationState.h
    engine->RegisterObjectBehaviour("AnimationStateTrack", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(AnimationStateTrack_AnimationStateTrack_void), asCALL_CDECL_OBJFIRST);
    // AnimationTriggerPoint::AnimationTriggerPoint() | File: ../Graphics/Animation.h
    engine->RegisterObjectBehaviour("AnimationTriggerPoint", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(AnimationTriggerPoint_AnimationTriggerPoint_void), asCALL_CDECL_OBJFIRST);
    // AsyncProgress::AsyncProgress() | Implicitly-declared
    engine->RegisterObjectBehaviour("AsyncProgress", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(AsyncProgress_Constructor), asCALL_CDECL_OBJFIRST);
    // AttributeInfo::AttributeInfo()=default | File: ../Core/Attribute.h
    engine->RegisterObjectBehaviour("AttributeInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(AttributeInfo_AttributeInfo_void), asCALL_CDECL_OBJFIRST);
    // BackgroundLoadItem::BackgroundLoadItem() | Implicitly-declared
    engine->RegisterObjectBehaviour("BackgroundLoadItem", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(BackgroundLoadItem_Constructor), asCALL_CDECL_OBJFIRST);
    // Batch::Batch()=default | File: ../Graphics/Batch.h
    engine->RegisterObjectBehaviour("Batch", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Batch_Batch_void), asCALL_CDECL_OBJFIRST);
    // BatchGroup::BatchGroup() | File: ../Graphics/Batch.h
    engine->RegisterObjectBehaviour("BatchGroup", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(BatchGroup_BatchGroup_void), asCALL_CDECL_OBJFIRST);
    // BatchGroupKey::BatchGroupKey()=default | File: ../Graphics/Batch.h
    engine->RegisterObjectBehaviour("BatchGroupKey", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(BatchGroupKey_BatchGroupKey_void), asCALL_CDECL_OBJFIRST);
    // BatchQueue::BatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("BatchQueue", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(BatchQueue_Constructor), asCALL_CDECL_OBJFIRST);
    // BiasParameters::BiasParameters()=default | File: ../Graphics/Light.h
    engine->RegisterObjectBehaviour("BiasParameters", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(BiasParameters_BiasParameters_void), asCALL_CDECL_OBJFIRST);
    // CascadeParameters::CascadeParameters()=default | File: ../Graphics/Light.h
    engine->RegisterObjectBehaviour("CascadeParameters", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(CascadeParameters_CascadeParameters_void), asCALL_CDECL_OBJFIRST);
    // CharLocation::CharLocation() | Implicitly-declared
    engine->RegisterObjectBehaviour("CharLocation", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(CharLocation_Constructor), asCALL_CDECL_OBJFIRST);
    // ComponentReplicationState::ComponentReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("ComponentReplicationState", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ComponentReplicationState_Constructor), asCALL_CDECL_OBJFIRST);
    // CompressedLevel::CompressedLevel() | Implicitly-declared
    engine->RegisterObjectBehaviour("CompressedLevel", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(CompressedLevel_Constructor), asCALL_CDECL_OBJFIRST);
    // CursorShapeInfo::CursorShapeInfo() | File: ../UI/Cursor.h
    engine->RegisterObjectBehaviour("CursorShapeInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(CursorShapeInfo_CursorShapeInfo_void), asCALL_CDECL_OBJFIRST);
    // DebugLine::DebugLine()=default | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectBehaviour("DebugLine", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DebugLine_DebugLine_void), asCALL_CDECL_OBJFIRST);
    // DebugTriangle::DebugTriangle()=default | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectBehaviour("DebugTriangle", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DebugTriangle_DebugTriangle_void), asCALL_CDECL_OBJFIRST);
    // Decal::Decal() | File: ../Graphics/DecalSet.h
    engine->RegisterObjectBehaviour("Decal", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Decal_Decal_void), asCALL_CDECL_OBJFIRST);
    // DecalVertex::DecalVertex()=default | File: ../Graphics/DecalSet.h
    engine->RegisterObjectBehaviour("DecalVertex", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DecalVertex_DecalVertex_void), asCALL_CDECL_OBJFIRST);
#ifdef URHO3D_PHYSICS
    // DelayedWorldTransform::DelayedWorldTransform() | Implicitly-declared
    engine->RegisterObjectBehaviour("DelayedWorldTransform", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DelayedWorldTransform_Constructor), asCALL_CDECL_OBJFIRST);
#endif
#ifdef URHO3D_URHO2D
    // DelayedWorldTransform2D::DelayedWorldTransform2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("DelayedWorldTransform2D", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DelayedWorldTransform2D_Constructor), asCALL_CDECL_OBJFIRST);
#endif
    // DirtyBits::DirtyBits()=default | File: ../Scene/ReplicationState.h
    engine->RegisterObjectBehaviour("DirtyBits", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DirtyBits_DirtyBits_void), asCALL_CDECL_OBJFIRST);
    // FileSelectorEntry::FileSelectorEntry() | Implicitly-declared
    engine->RegisterObjectBehaviour("FileSelectorEntry", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(FileSelectorEntry_Constructor), asCALL_CDECL_OBJFIRST);
    // FocusParameters::FocusParameters()=default | File: ../Graphics/Light.h
    engine->RegisterObjectBehaviour("FocusParameters", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(FocusParameters_FocusParameters_void), asCALL_CDECL_OBJFIRST);
    // FontGlyph::FontGlyph() | Implicitly-declared
    engine->RegisterObjectBehaviour("FontGlyph", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(FontGlyph_Constructor), asCALL_CDECL_OBJFIRST);
    // FrameInfo::FrameInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("FrameInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(FrameInfo_Constructor), asCALL_CDECL_OBJFIRST);
    // GeometryDesc::GeometryDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("GeometryDesc", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(GeometryDesc_Constructor), asCALL_CDECL_OBJFIRST);
    // HashIteratorBase::HashIteratorBase() | File: ../Container/HashBase.h
    engine->RegisterObjectBehaviour("HashIteratorBase", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(HashIteratorBase_HashIteratorBase_void), asCALL_CDECL_OBJFIRST);
    // HashNodeBase::HashNodeBase() | File: ../Container/HashBase.h
    engine->RegisterObjectBehaviour("HashNodeBase", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(HashNodeBase_HashNodeBase_void), asCALL_CDECL_OBJFIRST);
    // IndexBufferDesc::IndexBufferDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("IndexBufferDesc", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(IndexBufferDesc_Constructor), asCALL_CDECL_OBJFIRST);
    // InstanceData::InstanceData()=default | File: ../Graphics/Batch.h
    engine->RegisterObjectBehaviour("InstanceData", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(InstanceData_InstanceData_void), asCALL_CDECL_OBJFIRST);
    // LightBatchQueue::LightBatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("LightBatchQueue", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(LightBatchQueue_Constructor), asCALL_CDECL_OBJFIRST);
    // LightQueryResult::LightQueryResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("LightQueryResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(LightQueryResult_Constructor), asCALL_CDECL_OBJFIRST);
    // LinkedListNode::LinkedListNode() | File: ../Container/LinkedList.h
    engine->RegisterObjectBehaviour("LinkedListNode", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(LinkedListNode_LinkedListNode_void), asCALL_CDECL_OBJFIRST);
    // ListIteratorBase::ListIteratorBase() | File: ../Container/ListBase.h
    engine->RegisterObjectBehaviour("ListIteratorBase", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ListIteratorBase_ListIteratorBase_void), asCALL_CDECL_OBJFIRST);
    // ListNodeBase::ListNodeBase() | File: ../Container/ListBase.h
    engine->RegisterObjectBehaviour("ListNodeBase", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ListNodeBase_ListNodeBase_void), asCALL_CDECL_OBJFIRST);
#ifdef URHO3D_PHYSICS
    // ManifoldPair::ManifoldPair() | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectBehaviour("ManifoldPair", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ManifoldPair_ManifoldPair_void), asCALL_CDECL_OBJFIRST);
#endif
    // MaterialShaderParameter::MaterialShaderParameter() | Implicitly-declared
    engine->RegisterObjectBehaviour("MaterialShaderParameter", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(MaterialShaderParameter_Constructor), asCALL_CDECL_OBJFIRST);
    // ModelMorph::ModelMorph() | Implicitly-declared
    engine->RegisterObjectBehaviour("ModelMorph", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ModelMorph_Constructor), asCALL_CDECL_OBJFIRST);
#ifdef URHO3D_NAVIGATION
    // NavAreaStub::NavAreaStub() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavAreaStub", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(NavAreaStub_Constructor), asCALL_CDECL_OBJFIRST);
#endif
#ifdef URHO3D_NAVIGATION
    // NavBuildData::NavBuildData() | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectBehaviour("NavBuildData", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(NavBuildData_NavBuildData_void), asCALL_CDECL_OBJFIRST);
#endif
#ifdef URHO3D_NAVIGATION
    // NavigationGeometryInfo::NavigationGeometryInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavigationGeometryInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(NavigationGeometryInfo_Constructor), asCALL_CDECL_OBJFIRST);
#endif
#ifdef URHO3D_NAVIGATION
    // NavigationPathPoint::NavigationPathPoint() | Implicitly-declared
    engine->RegisterObjectBehaviour("NavigationPathPoint", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(NavigationPathPoint_Constructor), asCALL_CDECL_OBJFIRST);
#endif
    // NetworkState::NetworkState() | Implicitly-declared
    engine->RegisterObjectBehaviour("NetworkState", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(NetworkState_Constructor), asCALL_CDECL_OBJFIRST);
    // NodeImpl::NodeImpl() | Implicitly-declared
    engine->RegisterObjectBehaviour("NodeImpl", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(NodeImpl_Constructor), asCALL_CDECL_OBJFIRST);
    // NodeReplicationState::NodeReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("NodeReplicationState", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(NodeReplicationState_Constructor), asCALL_CDECL_OBJFIRST);
    // OcclusionBatch::OcclusionBatch() | Implicitly-declared
    engine->RegisterObjectBehaviour("OcclusionBatch", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(OcclusionBatch_Constructor), asCALL_CDECL_OBJFIRST);
    // OcclusionBufferData::OcclusionBufferData() | Implicitly-declared
    engine->RegisterObjectBehaviour("OcclusionBufferData", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(OcclusionBufferData_Constructor), asCALL_CDECL_OBJFIRST);
    // OctreeQueryResult::OctreeQueryResult() | File: ../Graphics/OctreeQuery.h
    engine->RegisterObjectBehaviour("OctreeQueryResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(OctreeQueryResult_OctreeQueryResult_void), asCALL_CDECL_OBJFIRST);
#ifdef URHO3D_NETWORK
    // PackageDownload::PackageDownload() | File: ../Network/Connection.h
    engine->RegisterObjectBehaviour("PackageDownload", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(PackageDownload_PackageDownload_void), asCALL_CDECL_OBJFIRST);
#endif
#ifdef URHO3D_NETWORK
    // PackageUpload::PackageUpload() | File: ../Network/Connection.h
    engine->RegisterObjectBehaviour("PackageUpload", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(PackageUpload_PackageUpload_void), asCALL_CDECL_OBJFIRST);
#endif
    // Particle::Particle() | Implicitly-declared
    engine->RegisterObjectBehaviour("Particle", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Particle_Constructor), asCALL_CDECL_OBJFIRST);
#ifdef URHO3D_URHO2D
    // Particle2D::Particle2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("Particle2D", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Particle2D_Constructor), asCALL_CDECL_OBJFIRST);
#endif
    // PerThreadSceneResult::PerThreadSceneResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("PerThreadSceneResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(PerThreadSceneResult_Constructor), asCALL_CDECL_OBJFIRST);
#ifdef URHO3D_PHYSICS
    // PhysicsRaycastResult::PhysicsRaycastResult() | Implicitly-declared
    engine->RegisterObjectBehaviour("PhysicsRaycastResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(PhysicsRaycastResult_Constructor), asCALL_CDECL_OBJFIRST);
#endif
#ifdef URHO3D_URHO2D
    // PhysicsRaycastResult2D::PhysicsRaycastResult2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("PhysicsRaycastResult2D", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(PhysicsRaycastResult2D_Constructor), asCALL_CDECL_OBJFIRST);
#endif
#ifdef URHO3D_PHYSICS
    // PhysicsWorldConfig::PhysicsWorldConfig() | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectBehaviour("PhysicsWorldConfig", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(PhysicsWorldConfig_PhysicsWorldConfig_void), asCALL_CDECL_OBJFIRST);
#endif
    // RayQueryResult::RayQueryResult() | File: ../Graphics/OctreeQuery.h
    engine->RegisterObjectBehaviour("RayQueryResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(RayQueryResult_RayQueryResult_void), asCALL_CDECL_OBJFIRST);
    // RefCount::RefCount() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RefCount", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(RefCount_RefCount_void), asCALL_CDECL_OBJFIRST);
#ifdef URHO3D_NETWORK
    // RemoteEvent::RemoteEvent() | Implicitly-declared
    engine->RegisterObjectBehaviour("RemoteEvent", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(RemoteEvent_Constructor), asCALL_CDECL_OBJFIRST);
#endif
    // RenderPathCommand::RenderPathCommand() | Implicitly-declared
    engine->RegisterObjectBehaviour("RenderPathCommand", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(RenderPathCommand_Constructor), asCALL_CDECL_OBJFIRST);
    // RenderTargetInfo::RenderTargetInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("RenderTargetInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(RenderTargetInfo_Constructor), asCALL_CDECL_OBJFIRST);
    // ReplicationState::ReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("ReplicationState", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ReplicationState_Constructor), asCALL_CDECL_OBJFIRST);
    // ResourceGroup::ResourceGroup() | File: ../Resource/ResourceCache.h
    engine->RegisterObjectBehaviour("ResourceGroup", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ResourceGroup_ResourceGroup_void), asCALL_CDECL_OBJFIRST);
    // ResourceRef::ResourceRef()=default | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ResourceRef_ResourceRef_void), asCALL_CDECL_OBJFIRST);
    // ResourceRefList::ResourceRefList()=default | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ResourceRefList_ResourceRefList_void), asCALL_CDECL_OBJFIRST);
    // ScenePassInfo::ScenePassInfo() | Implicitly-declared
    engine->RegisterObjectBehaviour("ScenePassInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ScenePassInfo_Constructor), asCALL_CDECL_OBJFIRST);
    // SceneReplicationState::SceneReplicationState() | Implicitly-declared
    engine->RegisterObjectBehaviour("SceneReplicationState", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(SceneReplicationState_Constructor), asCALL_CDECL_OBJFIRST);
    // ScratchBuffer::ScratchBuffer() | File: ../Graphics/Graphics.h
    engine->RegisterObjectBehaviour("ScratchBuffer", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ScratchBuffer_ScratchBuffer_void), asCALL_CDECL_OBJFIRST);
    // ScreenModeParams::ScreenModeParams() | Implicitly-declared
    engine->RegisterObjectBehaviour("ScreenModeParams", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ScreenModeParams_Constructor), asCALL_CDECL_OBJFIRST);
    // ShaderParameter::ShaderParameter()=default | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectBehaviour("ShaderParameter", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ShaderParameter_ShaderParameter_void), asCALL_CDECL_OBJFIRST);
    // ShadowBatchQueue::ShadowBatchQueue() | Implicitly-declared
    engine->RegisterObjectBehaviour("ShadowBatchQueue", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ShadowBatchQueue_Constructor), asCALL_CDECL_OBJFIRST);
#ifdef URHO3D_NAVIGATION
    // SimpleNavBuildData::SimpleNavBuildData() | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectBehaviour("SimpleNavBuildData", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(SimpleNavBuildData_SimpleNavBuildData_void), asCALL_CDECL_OBJFIRST);
#endif
    // SourceBatch::SourceBatch() | File: ../Graphics/Drawable.h
    engine->RegisterObjectBehaviour("SourceBatch", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(SourceBatch_SourceBatch_void), asCALL_CDECL_OBJFIRST);
#ifdef URHO3D_URHO2D
    // SourceBatch2D::SourceBatch2D() | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectBehaviour("SourceBatch2D", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(SourceBatch2D_SourceBatch2D_void), asCALL_CDECL_OBJFIRST);
#endif
    // StaticModelGeometryData::StaticModelGeometryData() | Implicitly-declared
    engine->RegisterObjectBehaviour("StaticModelGeometryData", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(StaticModelGeometryData_Constructor), asCALL_CDECL_OBJFIRST);
    // StoredLogMessage::StoredLogMessage()=default | File: ../IO/Log.h
    engine->RegisterObjectBehaviour("StoredLogMessage", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(StoredLogMessage_StoredLogMessage_void), asCALL_CDECL_OBJFIRST);
    // TechniqueEntry::TechniqueEntry() noexcept | File: ../Graphics/Material.h
    engine->RegisterObjectBehaviour("TechniqueEntry", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(TechniqueEntry_TechniqueEntry_void), asCALL_CDECL_OBJFIRST);
    // TrailPoint::TrailPoint()=default | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectBehaviour("TrailPoint", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(TrailPoint_TrailPoint_void), asCALL_CDECL_OBJFIRST);
    // VAnimEventFrame::VAnimEventFrame() | Implicitly-declared
    engine->RegisterObjectBehaviour("VAnimEventFrame", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(VAnimEventFrame_Constructor), asCALL_CDECL_OBJFIRST);
    // VAnimKeyFrame::VAnimKeyFrame() | Implicitly-declared
    engine->RegisterObjectBehaviour("VAnimKeyFrame", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(VAnimKeyFrame_Constructor), asCALL_CDECL_OBJFIRST);
#ifdef URHO3D_URHO2D
    // Vertex2D::Vertex2D() | Implicitly-declared
    engine->RegisterObjectBehaviour("Vertex2D", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vertex2D_Constructor), asCALL_CDECL_OBJFIRST);
#endif
    // VertexBufferDesc::VertexBufferDesc() | Implicitly-declared
    engine->RegisterObjectBehaviour("VertexBufferDesc", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(VertexBufferDesc_Constructor), asCALL_CDECL_OBJFIRST);
    // VertexBufferMorph::VertexBufferMorph() | Implicitly-declared
    engine->RegisterObjectBehaviour("VertexBufferMorph", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(VertexBufferMorph_Constructor), asCALL_CDECL_OBJFIRST);
    // VertexElement::VertexElement() noexcept | File: ../Graphics/GraphicsDefs.h
    engine->RegisterObjectBehaviour("VertexElement", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(VertexElement_VertexElement_void), asCALL_CDECL_OBJFIRST);
    // WindowModeParams::WindowModeParams() | Implicitly-declared
    engine->RegisterObjectBehaviour("WindowModeParams", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(WindowModeParams_Constructor), asCALL_CDECL_OBJFIRST);
}

}
