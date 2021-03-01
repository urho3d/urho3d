// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

// struct AnimationControl | File: ../Graphics/AnimationController.h
void CollectMembers_AnimationControl(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("String AnimationControl::name_", "String name", offsetof(AnimationControl, name_)));
    members.fields_.Push(RegisterObjectPropertyArgs("StringHash AnimationControl::hash_", "StringHash hash", offsetof(AnimationControl, hash_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float AnimationControl::speed_", "float speed", offsetof(AnimationControl, speed_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float AnimationControl::targetWeight_", "float targetWeight", offsetof(AnimationControl, targetWeight_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float AnimationControl::fadeTime_", "float fadeTime", offsetof(AnimationControl, fadeTime_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float AnimationControl::autoFadeTime_", "float autoFadeTime", offsetof(AnimationControl, autoFadeTime_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float AnimationControl::setTimeTtl_", "float setTimeTtl", offsetof(AnimationControl, setTimeTtl_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float AnimationControl::setWeightTtl_", "float setWeightTtl", offsetof(AnimationControl, setWeightTtl_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned short AnimationControl::setTime_", "uint16 setTime", offsetof(AnimationControl, setTime_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char AnimationControl::setWeight_", "uint8 setWeight", offsetof(AnimationControl, setWeight_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char AnimationControl::setTimeRev_", "uint8 setTimeRev", offsetof(AnimationControl, setTimeRev_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char AnimationControl::setWeightRev_", "uint8 setWeightRev", offsetof(AnimationControl, setWeightRev_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool AnimationControl::removeOnCompletion_", "bool removeOnCompletion", offsetof(AnimationControl, removeOnCompletion_)));

}

// struct AnimationKeyFrame | File: ../Graphics/Animation.h
void CollectMembers_AnimationKeyFrame(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("float AnimationKeyFrame::time_", "float time", offsetof(AnimationKeyFrame, time_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 AnimationKeyFrame::position_", "Vector3 position", offsetof(AnimationKeyFrame, position_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Quaternion AnimationKeyFrame::rotation_", "Quaternion rotation", offsetof(AnimationKeyFrame, rotation_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 AnimationKeyFrame::scale_", "Vector3 scale", offsetof(AnimationKeyFrame, scale_)));

}

// struct AnimationStateTrack | File: ../Graphics/AnimationState.h
void CollectMembers_AnimationStateTrack(MemberCollection& members)
{
    // const AnimationTrack* AnimationStateTrack::track_
    // Not registered because pointer
    // Bone* AnimationStateTrack::bone_
    // Not registered because pointer
    // WeakPtr<Node> AnimationStateTrack::node_
    // Error: type "WeakPtr<Node>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("float AnimationStateTrack::weight_", "float weight", offsetof(AnimationStateTrack, weight_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned AnimationStateTrack::keyFrame_", "uint keyFrame", offsetof(AnimationStateTrack, keyFrame_)));

}

// struct AnimationTrack | File: ../Graphics/Animation.h
void CollectMembers_AnimationTrack(MemberCollection& members)
{
    // AnimationKeyFrame* AnimationTrack::GetKeyFrame(unsigned index)
    // Error: type "AnimationKeyFrame*" can not automatically bind

    // Vector<AnimationKeyFrame> AnimationTrack::keyFrames_
    // Error: type "Vector<AnimationKeyFrame>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("String AnimationTrack::name_", "String name", offsetof(AnimationTrack, name_)));
    members.fields_.Push(RegisterObjectPropertyArgs("StringHash AnimationTrack::nameHash_", "StringHash nameHash", offsetof(AnimationTrack, nameHash_)));
    members.fields_.Push(RegisterObjectPropertyArgs("AnimationChannelFlags AnimationTrack::channelMask_", "AnimationChannelFlags channelMask", offsetof(AnimationTrack, channelMask_)));

}

// struct AnimationTriggerPoint | File: ../Graphics/Animation.h
void CollectMembers_AnimationTriggerPoint(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("float AnimationTriggerPoint::time_", "float time", offsetof(AnimationTriggerPoint, time_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Variant AnimationTriggerPoint::data_", "Variant data", offsetof(AnimationTriggerPoint, data_)));

}

// struct Batch | File: ../Graphics/Batch.h
void CollectMembers_Batch(MemberCollection& members)
{
    // Geometry* Batch::geometry_
    // Not registered because pointer
    // Material* Batch::material_
    // Not registered because pointer
    // const Matrix3x4* Batch::worldTransform_
    // Not registered because pointer
    // void* Batch::instancingData_
    // Not registered because pointer
    // Zone* Batch::zone_
    // Not registered because pointer
    // LightBatchQueue* Batch::lightQueue_
    // Not registered because pointer
    // Pass* Batch::pass_
    // Not registered because pointer
    // ShaderVariation* Batch::vertexShader_
    // Not registered because pointer
    // ShaderVariation* Batch::pixelShader_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned long long Batch::sortKey_", "uint64 sortKey", offsetof(Batch, sortKey_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Batch::distance_", "float distance", offsetof(Batch, distance_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char Batch::renderOrder_", "uint8 renderOrder", offsetof(Batch, renderOrder_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char Batch::lightMask_", "uint8 lightMask", offsetof(Batch, lightMask_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool Batch::isBase_", "bool isBase", offsetof(Batch, isBase_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned Batch::numWorldTransforms_", "uint numWorldTransforms", offsetof(Batch, numWorldTransforms_)));
    members.fields_.Push(RegisterObjectPropertyArgs("GeometryType Batch::geometryType_", "GeometryType geometryType", offsetof(Batch, geometryType_)));

}

// struct BatchGroupKey | File: ../Graphics/Batch.h
void CollectMembers_BatchGroupKey(MemberCollection& members)
{
    // bool BatchGroupKey::operator !=(const BatchGroupKey& rhs) const
    // Only operator == is needed

    // Zone* BatchGroupKey::zone_
    // Not registered because pointer
    // LightBatchQueue* BatchGroupKey::lightQueue_
    // Not registered because pointer
    // Pass* BatchGroupKey::pass_
    // Not registered because pointer
    // Material* BatchGroupKey::material_
    // Not registered because pointer
    // Geometry* BatchGroupKey::geometry_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char BatchGroupKey::renderOrder_", "uint8 renderOrder", offsetof(BatchGroupKey, renderOrder_)));

}

// struct BatchQueue | File: ../Graphics/Batch.h
void CollectMembers_BatchQueue(MemberCollection& members)
{
    // void BatchQueue::SetInstancingData(void* lockedData, unsigned stride, unsigned& freeIndex)
    // Error: type "void*" can not automatically bind
    // void BatchQueue::SortFrontToBack2Pass(PODVector<Batch*>& batches)
    // Error: type "PODVector<Batch*>&" can not automatically bind

    // HashMap<BatchGroupKey, BatchGroup> BatchQueue::batchGroups_
    // Error: type "HashMap<BatchGroupKey, BatchGroup>" can not automatically bind
    // HashMap<unsigned, unsigned> BatchQueue::shaderRemapping_
    // Error: type "HashMap<unsigned, unsigned>" can not automatically bind
    // HashMap<unsigned short, unsigned short> BatchQueue::materialRemapping_
    // Error: type "HashMap<unsigned short, unsigned short>" can not automatically bind
    // HashMap<unsigned short, unsigned short> BatchQueue::geometryRemapping_
    // Error: type "HashMap<unsigned short, unsigned short>" can not automatically bind
    // PODVector<Batch> BatchQueue::batches_
    // Error: type "PODVector<Batch>" can not automatically bind
    // PODVector<Batch*> BatchQueue::sortedBatches_
    // Error: type "PODVector<Batch*>" can not automatically bind
    // PODVector<BatchGroup*> BatchQueue::sortedBatchGroups_
    // Error: type "PODVector<BatchGroup*>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned BatchQueue::maxSortedInstances_", "uint maxSortedInstances", offsetof(BatchQueue, maxSortedInstances_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool BatchQueue::hasExtraDefines_", "bool hasExtraDefines", offsetof(BatchQueue, hasExtraDefines_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String BatchQueue::vsExtraDefines_", "String vsExtraDefines", offsetof(BatchQueue, vsExtraDefines_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String BatchQueue::psExtraDefines_", "String psExtraDefines", offsetof(BatchQueue, psExtraDefines_)));
    members.fields_.Push(RegisterObjectPropertyArgs("StringHash BatchQueue::vsExtraDefinesHash_", "StringHash vsExtraDefinesHash", offsetof(BatchQueue, vsExtraDefinesHash_)));
    members.fields_.Push(RegisterObjectPropertyArgs("StringHash BatchQueue::psExtraDefinesHash_", "StringHash psExtraDefinesHash", offsetof(BatchQueue, psExtraDefinesHash_)));

}

// struct BiasParameters | File: ../Graphics/Light.h
void CollectMembers_BiasParameters(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("float BiasParameters::constantBias_", "float constantBias", offsetof(BiasParameters, constantBias_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float BiasParameters::slopeScaledBias_", "float slopeScaledBias", offsetof(BiasParameters, slopeScaledBias_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float BiasParameters::normalOffset_", "float normalOffset", offsetof(BiasParameters, normalOffset_)));

}

// struct Billboard | File: ../Graphics/BillboardSet.h
void CollectMembers_Billboard(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 Billboard::position_", "Vector3 position", offsetof(Billboard, position_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 Billboard::size_", "Vector2 size", offsetof(Billboard, size_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Rect Billboard::uv_", "Rect uv", offsetof(Billboard, uv_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Color Billboard::color_", "Color color", offsetof(Billboard, color_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Billboard::rotation_", "float rotation", offsetof(Billboard, rotation_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 Billboard::direction_", "Vector3 direction", offsetof(Billboard, direction_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool Billboard::enabled_", "bool enabled", offsetof(Billboard, enabled_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Billboard::sortDistance_", "float sortDistance", offsetof(Billboard, sortDistance_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Billboard::screenScaleFactor_", "float screenScaleFactor", offsetof(Billboard, screenScaleFactor_)));

}

// struct Bone | File: ../Graphics/Skeleton.h
void CollectMembers_Bone(MemberCollection& members)
{
    // WeakPtr<Node> Bone::node_
    // Error: type "WeakPtr<Node>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("String Bone::name_", "String name", offsetof(Bone, name_)));
    members.fields_.Push(RegisterObjectPropertyArgs("StringHash Bone::nameHash_", "StringHash nameHash", offsetof(Bone, nameHash_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned Bone::parentIndex_", "uint parentIndex", offsetof(Bone, parentIndex_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 Bone::initialPosition_", "Vector3 initialPosition", offsetof(Bone, initialPosition_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Quaternion Bone::initialRotation_", "Quaternion initialRotation", offsetof(Bone, initialRotation_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 Bone::initialScale_", "Vector3 initialScale", offsetof(Bone, initialScale_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Matrix3x4 Bone::offsetMatrix_", "Matrix3x4 offsetMatrix", offsetof(Bone, offsetMatrix_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool Bone::animated_", "bool animated", offsetof(Bone, animated_)));
    members.fields_.Push(RegisterObjectPropertyArgs("BoneCollisionShapeFlags Bone::collisionMask_", "BoneCollisionShapeFlags collisionMask", offsetof(Bone, collisionMask_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Bone::radius_", "float radius", offsetof(Bone, radius_)));
    members.fields_.Push(RegisterObjectPropertyArgs("BoundingBox Bone::boundingBox_", "BoundingBox boundingBox", offsetof(Bone, boundingBox_)));

}

// struct CascadeParameters | File: ../Graphics/Light.h
void CollectMembers_CascadeParameters(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("Vector4 CascadeParameters::splits_", "Vector4 splits", offsetof(CascadeParameters, splits_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float CascadeParameters::fadeStart_", "float fadeStart", offsetof(CascadeParameters, fadeStart_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float CascadeParameters::biasAutoAdjust_", "float biasAutoAdjust", offsetof(CascadeParameters, biasAutoAdjust_)));

}

// struct ColorFrame | File: ../Graphics/ParticleEffect.h
void CollectMembers_ColorFrame(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("Color ColorFrame::color_", "Color color", offsetof(ColorFrame, color_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float ColorFrame::time_", "float time", offsetof(ColorFrame, time_)));

}

// struct CustomGeometryVertex | File: ../Graphics/CustomGeometry.h
void CollectMembers_CustomGeometryVertex(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 CustomGeometryVertex::position_", "Vector3 position", offsetof(CustomGeometryVertex, position_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 CustomGeometryVertex::normal_", "Vector3 normal", offsetof(CustomGeometryVertex, normal_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned CustomGeometryVertex::color_", "uint color", offsetof(CustomGeometryVertex, color_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 CustomGeometryVertex::texCoord_", "Vector2 texCoord", offsetof(CustomGeometryVertex, texCoord_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector4 CustomGeometryVertex::tangent_", "Vector4 tangent", offsetof(CustomGeometryVertex, tangent_)));

}

// struct DebugLine | File: ../Graphics/DebugRenderer.h
void CollectMembers_DebugLine(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 DebugLine::start_", "Vector3 start", offsetof(DebugLine, start_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 DebugLine::end_", "Vector3 end", offsetof(DebugLine, end_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned DebugLine::color_", "uint color", offsetof(DebugLine, color_)));

}

// struct DebugTriangle | File: ../Graphics/DebugRenderer.h
void CollectMembers_DebugTriangle(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 DebugTriangle::v1_", "Vector3 v1", offsetof(DebugTriangle, v1_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 DebugTriangle::v2_", "Vector3 v2", offsetof(DebugTriangle, v2_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 DebugTriangle::v3_", "Vector3 v3", offsetof(DebugTriangle, v3_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned DebugTriangle::color_", "uint color", offsetof(DebugTriangle, color_)));

}

// struct Decal | File: ../Graphics/DecalSet.h
void CollectMembers_Decal(MemberCollection& members)
{
    // PODVector<DecalVertex> Decal::vertices_
    // Error: type "PODVector<DecalVertex>" can not automatically bind
    // PODVector<unsigned short> Decal::indices_
    // Error: type "PODVector<unsigned short>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("float Decal::timer_", "float timer", offsetof(Decal, timer_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Decal::timeToLive_", "float timeToLive", offsetof(Decal, timeToLive_)));
    members.fields_.Push(RegisterObjectPropertyArgs("BoundingBox Decal::boundingBox_", "BoundingBox boundingBox", offsetof(Decal, boundingBox_)));

}

// struct DecalVertex | File: ../Graphics/DecalSet.h
void CollectMembers_DecalVertex(MemberCollection& members)
{
    // float DecalVertex::blendWeights_[4]
    // Not registered because array
    // unsigned char DecalVertex::blendIndices_[4]
    // Not registered because array

    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 DecalVertex::position_", "Vector3 position", offsetof(DecalVertex, position_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 DecalVertex::normal_", "Vector3 normal", offsetof(DecalVertex, normal_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 DecalVertex::texCoord_", "Vector2 texCoord", offsetof(DecalVertex, texCoord_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector4 DecalVertex::tangent_", "Vector4 tangent", offsetof(DecalVertex, tangent_)));

}

// struct DepthValue | File: ../Graphics/OcclusionBuffer.h
void CollectMembers_DepthValue(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("int DepthValue::min_", "int min", offsetof(DepthValue, min_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int DepthValue::max_", "int max", offsetof(DepthValue, max_)));

}

// struct FocusParameters | File: ../Graphics/Light.h
void CollectMembers_FocusParameters(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("bool FocusParameters::focus_", "bool focus", offsetof(FocusParameters, focus_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool FocusParameters::nonUniform_", "bool nonUniform", offsetof(FocusParameters, nonUniform_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool FocusParameters::autoSize_", "bool autoSize", offsetof(FocusParameters, autoSize_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float FocusParameters::quantize_", "float quantize", offsetof(FocusParameters, quantize_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float FocusParameters::minView_", "float minView", offsetof(FocusParameters, minView_)));

}

// struct FrameInfo | File: ../Graphics/Drawable.h
void CollectMembers_FrameInfo(MemberCollection& members)
{
    // Camera* FrameInfo::camera_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned FrameInfo::frameNumber_", "uint frameNumber", offsetof(FrameInfo, frameNumber_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float FrameInfo::timeStep_", "float timeStep", offsetof(FrameInfo, timeStep_)));
    members.fields_.Push(RegisterObjectPropertyArgs("IntVector2 FrameInfo::viewSize_", "IntVector2 viewSize", offsetof(FrameInfo, viewSize_)));

}

// class GPUObject | File: ../Graphics/GPUObject.h
void CollectMembers_GPUObject(MemberCollection& members)
{
    // void* GPUObject::GetGPUObject() const
    // Error: type "void*" can not automatically bind

}

// struct GeometryDesc | File: ../Graphics/Model.h
void CollectMembers_GeometryDesc(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("PrimitiveType GeometryDesc::type_", "PrimitiveType type", offsetof(GeometryDesc, type_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned GeometryDesc::vbRef_", "uint vbRef", offsetof(GeometryDesc, vbRef_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned GeometryDesc::ibRef_", "uint ibRef", offsetof(GeometryDesc, ibRef_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned GeometryDesc::indexStart_", "uint indexStart", offsetof(GeometryDesc, indexStart_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned GeometryDesc::indexCount_", "uint indexCount", offsetof(GeometryDesc, indexCount_)));

}

// struct IndexBufferDesc | File: ../Graphics/Model.h
void CollectMembers_IndexBufferDesc(MemberCollection& members)
{
    // SharedArrayPtr<unsigned char> IndexBufferDesc::data_
    // Error: type "SharedArrayPtr<unsigned char>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned IndexBufferDesc::indexCount_", "uint indexCount", offsetof(IndexBufferDesc, indexCount_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned IndexBufferDesc::indexSize_", "uint indexSize", offsetof(IndexBufferDesc, indexSize_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned IndexBufferDesc::dataSize_", "uint dataSize", offsetof(IndexBufferDesc, dataSize_)));

}

// struct InstanceData | File: ../Graphics/Batch.h
void CollectMembers_InstanceData(MemberCollection& members)
{
    // const Matrix3x4* InstanceData::worldTransform_
    // Not registered because pointer
    // const void* InstanceData::instancingData_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("float InstanceData::distance_", "float distance", offsetof(InstanceData, distance_)));

}

// struct LightBatchQueue | File: ../Graphics/Batch.h
void CollectMembers_LightBatchQueue(MemberCollection& members)
{
    // Light* LightBatchQueue::light_
    // Not registered because pointer
    // Texture2D* LightBatchQueue::shadowMap_
    // Not registered because pointer
    // Vector<ShadowBatchQueue> LightBatchQueue::shadowSplits_
    // Error: type "Vector<ShadowBatchQueue>" can not automatically bind
    // PODVector<Light*> LightBatchQueue::vertexLights_
    // Error: type "PODVector<Light*>" can not automatically bind
    // PODVector<Batch> LightBatchQueue::volumeBatches_
    // Error: type "PODVector<Batch>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("bool LightBatchQueue::negative_", "bool negative", offsetof(LightBatchQueue, negative_)));
    members.fields_.Push(RegisterObjectPropertyArgs("BatchQueue LightBatchQueue::litBaseBatches_", "BatchQueue litBaseBatches", offsetof(LightBatchQueue, litBaseBatches_)));
    members.fields_.Push(RegisterObjectPropertyArgs("BatchQueue LightBatchQueue::litBatches_", "BatchQueue litBatches", offsetof(LightBatchQueue, litBatches_)));

}

// struct LightQueryResult | File: ../Graphics/View.h
void CollectMembers_LightQueryResult(MemberCollection& members)
{
    // Light* LightQueryResult::light_
    // Not registered because pointer
    // PODVector<Drawable*> LightQueryResult::litGeometries_
    // Error: type "PODVector<Drawable*>" can not automatically bind
    // PODVector<Drawable*> LightQueryResult::shadowCasters_
    // Error: type "PODVector<Drawable*>" can not automatically bind
    // Camera* LightQueryResult::shadowCameras_[MAX_LIGHT_SPLITS]
    // Not registered because array
    // unsigned LightQueryResult::shadowCasterBegin_[MAX_LIGHT_SPLITS]
    // Not registered because array
    // unsigned LightQueryResult::shadowCasterEnd_[MAX_LIGHT_SPLITS]
    // Not registered because array
    // BoundingBox LightQueryResult::shadowCasterBox_[MAX_LIGHT_SPLITS]
    // Not registered because array
    // float LightQueryResult::shadowNearSplits_[MAX_LIGHT_SPLITS]
    // Not registered because array
    // float LightQueryResult::shadowFarSplits_[MAX_LIGHT_SPLITS]
    // Not registered because array

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned LightQueryResult::numSplits_", "uint numSplits", offsetof(LightQueryResult, numSplits_)));

}

// struct MaterialShaderParameter | File: ../Graphics/Material.h
void CollectMembers_MaterialShaderParameter(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("String MaterialShaderParameter::name_", "String name", offsetof(MaterialShaderParameter, name_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Variant MaterialShaderParameter::value_", "Variant value", offsetof(MaterialShaderParameter, value_)));

}

// struct ModelMorph | File: ../Graphics/Model.h
void CollectMembers_ModelMorph(MemberCollection& members)
{
    // HashMap<unsigned, VertexBufferMorph> ModelMorph::buffers_
    // Error: type "HashMap<unsigned, VertexBufferMorph>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("String ModelMorph::name_", "String name", offsetof(ModelMorph, name_)));
    members.fields_.Push(RegisterObjectPropertyArgs("StringHash ModelMorph::nameHash_", "StringHash nameHash", offsetof(ModelMorph, nameHash_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float ModelMorph::weight_", "float weight", offsetof(ModelMorph, weight_)));

}

// struct OcclusionBatch | File: ../Graphics/OcclusionBuffer.h
void CollectMembers_OcclusionBatch(MemberCollection& members)
{
    // const void* OcclusionBatch::vertexData_
    // Not registered because pointer
    // const void* OcclusionBatch::indexData_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("Matrix3x4 OcclusionBatch::model_", "Matrix3x4 model", offsetof(OcclusionBatch, model_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned OcclusionBatch::vertexSize_", "uint vertexSize", offsetof(OcclusionBatch, vertexSize_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned OcclusionBatch::indexSize_", "uint indexSize", offsetof(OcclusionBatch, indexSize_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned OcclusionBatch::drawStart_", "uint drawStart", offsetof(OcclusionBatch, drawStart_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned OcclusionBatch::drawCount_", "uint drawCount", offsetof(OcclusionBatch, drawCount_)));

}

// struct OcclusionBufferData | File: ../Graphics/OcclusionBuffer.h
void CollectMembers_OcclusionBufferData(MemberCollection& members)
{
    // SharedArrayPtr<int> OcclusionBufferData::dataWithSafety_
    // Error: type "SharedArrayPtr<int>" can not automatically bind
    // int* OcclusionBufferData::data_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("bool OcclusionBufferData::used_", "bool used", offsetof(OcclusionBufferData, used_)));

}

// class Octant | File: ../Graphics/Octree.h
void CollectMembers_Octant(MemberCollection& members)
{
    // void Octant::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
    // Not registered because have @nobind mark
    // Octant* Octant::GetOrCreateChild(unsigned index)
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Octant* Octant::GetParent() const
    // Error: type "Octant" can not automatically bind bacause have @nobind mark

}

// class OctreeQuery | File: ../Graphics/OctreeQuery.h
void CollectMembers_OctreeQuery(MemberCollection& members)
{
    // virtual void OctreeQuery::TestDrawables(Drawable** start, Drawable** end, bool inside) = 0
    // Error: type "Drawable**" can not automatically bind

    // OctreeQuery& OctreeQuery::operator =(const OctreeQuery& rhs) = delete
    // Not registered because deleted

    // PODVector<Drawable*>& OctreeQuery::result_
    // Error: type "PODVector<Drawable*>&" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char OctreeQuery::drawableFlags_", "uint8 drawableFlags", offsetof(OctreeQuery, drawableFlags_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned OctreeQuery::viewMask_", "uint viewMask", offsetof(OctreeQuery, viewMask_)));

}

// struct OctreeQueryResult | File: ../Graphics/OctreeQuery.h
void CollectMembers_OctreeQueryResult(MemberCollection& members)
{
    // bool OctreeQueryResult::operator !=(const OctreeQueryResult& rhs) const
    // Only operator == is needed

    // Drawable* OctreeQueryResult::drawable_
    // Not registered because pointer
    // Node* OctreeQueryResult::node_
    // Not registered because pointer

}

// struct Particle | File: ../Graphics/ParticleEmitter.h
void CollectMembers_Particle(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 Particle::velocity_", "Vector3 velocity", offsetof(Particle, velocity_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 Particle::size_", "Vector2 size", offsetof(Particle, size_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle::timer_", "float timer", offsetof(Particle, timer_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle::timeToLive_", "float timeToLive", offsetof(Particle, timeToLive_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle::scale_", "float scale", offsetof(Particle, scale_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle::rotationSpeed_", "float rotationSpeed", offsetof(Particle, rotationSpeed_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned Particle::colorIndex_", "uint colorIndex", offsetof(Particle, colorIndex_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned Particle::texIndex_", "uint texIndex", offsetof(Particle, texIndex_)));

}

// struct PerThreadSceneResult | File: ../Graphics/View.h
void CollectMembers_PerThreadSceneResult(MemberCollection& members)
{
    // PODVector<Drawable*> PerThreadSceneResult::geometries_
    // Error: type "PODVector<Drawable*>" can not automatically bind
    // PODVector<Light*> PerThreadSceneResult::lights_
    // Error: type "PODVector<Light*>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("float PerThreadSceneResult::minZ_", "float minZ", offsetof(PerThreadSceneResult, minZ_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float PerThreadSceneResult::maxZ_", "float maxZ", offsetof(PerThreadSceneResult, maxZ_)));

}

// class RayOctreeQuery | File: ../Graphics/OctreeQuery.h
void CollectMembers_RayOctreeQuery(MemberCollection& members)
{
    // RayOctreeQuery& RayOctreeQuery::operator =(const RayOctreeQuery& rhs) = delete
    // Not registered because deleted

    // PODVector<RayQueryResult>& RayOctreeQuery::result_
    // Error: type "PODVector<RayQueryResult>&" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("Ray RayOctreeQuery::ray_", "Ray ray", offsetof(RayOctreeQuery, ray_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char RayOctreeQuery::drawableFlags_", "uint8 drawableFlags", offsetof(RayOctreeQuery, drawableFlags_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned RayOctreeQuery::viewMask_", "uint viewMask", offsetof(RayOctreeQuery, viewMask_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float RayOctreeQuery::maxDistance_", "float maxDistance", offsetof(RayOctreeQuery, maxDistance_)));
    members.fields_.Push(RegisterObjectPropertyArgs("RayQueryLevel RayOctreeQuery::level_", "RayQueryLevel level", offsetof(RayOctreeQuery, level_)));

}

// struct RayQueryResult | File: ../Graphics/OctreeQuery.h
void CollectMembers_RayQueryResult(MemberCollection& members)
{
    // bool RayQueryResult::operator !=(const RayQueryResult& rhs) const
    // Only operator == is needed

    // Drawable* RayQueryResult::drawable_
    // Not registered because pointer
    // Node* RayQueryResult::node_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 RayQueryResult::position_", "Vector3 position", offsetof(RayQueryResult, position_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 RayQueryResult::normal_", "Vector3 normal", offsetof(RayQueryResult, normal_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 RayQueryResult::textureUV_", "Vector2 textureUV", offsetof(RayQueryResult, textureUV_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float RayQueryResult::distance_", "float distance", offsetof(RayQueryResult, distance_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned RayQueryResult::subObject_", "uint subObject", offsetof(RayQueryResult, subObject_)));

}

// struct RenderPathCommand | File: ../Graphics/RenderPath.h
void CollectMembers_RenderPathCommand(MemberCollection& members)
{
    // String RenderPathCommand::textureNames_[MAX_TEXTURE_UNITS]
    // Not registered because array
    // HashMap<StringHash, Variant> RenderPathCommand::shaderParameters_
    // Error: type "HashMap<StringHash, Variant>" can not automatically bind
    // Vector<Pair<String, CubeMapFace>> RenderPathCommand::outputs_
    // Error: type "Vector<Pair<String, CubeMapFace>>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("String RenderPathCommand::tag_", "String tag", offsetof(RenderPathCommand, tag_)));
    members.fields_.Push(RegisterObjectPropertyArgs("RenderCommandType RenderPathCommand::type_", "RenderCommandType type", offsetof(RenderPathCommand, type_)));
    members.fields_.Push(RegisterObjectPropertyArgs("RenderCommandSortMode RenderPathCommand::sortMode_", "RenderCommandSortMode sortMode", offsetof(RenderPathCommand, sortMode_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String RenderPathCommand::pass_", "String pass", offsetof(RenderPathCommand, pass_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned RenderPathCommand::passIndex_", "uint passIndex", offsetof(RenderPathCommand, passIndex_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String RenderPathCommand::metadata_", "String metadata", offsetof(RenderPathCommand, metadata_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String RenderPathCommand::vertexShaderName_", "String vertexShaderName", offsetof(RenderPathCommand, vertexShaderName_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String RenderPathCommand::pixelShaderName_", "String pixelShaderName", offsetof(RenderPathCommand, pixelShaderName_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String RenderPathCommand::vertexShaderDefines_", "String vertexShaderDefines", offsetof(RenderPathCommand, vertexShaderDefines_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String RenderPathCommand::pixelShaderDefines_", "String pixelShaderDefines", offsetof(RenderPathCommand, pixelShaderDefines_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String RenderPathCommand::depthStencilName_", "String depthStencilName", offsetof(RenderPathCommand, depthStencilName_)));
    members.fields_.Push(RegisterObjectPropertyArgs("ClearTargetFlags RenderPathCommand::clearFlags_", "ClearTargetFlags clearFlags", offsetof(RenderPathCommand, clearFlags_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Color RenderPathCommand::clearColor_", "Color clearColor", offsetof(RenderPathCommand, clearColor_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float RenderPathCommand::clearDepth_", "float clearDepth", offsetof(RenderPathCommand, clearDepth_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned RenderPathCommand::clearStencil_", "uint clearStencil", offsetof(RenderPathCommand, clearStencil_)));
    members.fields_.Push(RegisterObjectPropertyArgs("BlendMode RenderPathCommand::blendMode_", "BlendMode blendMode", offsetof(RenderPathCommand, blendMode_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool RenderPathCommand::enabled_", "bool enabled", offsetof(RenderPathCommand, enabled_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool RenderPathCommand::useFogColor_", "bool useFogColor", offsetof(RenderPathCommand, useFogColor_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool RenderPathCommand::markToStencil_", "bool markToStencil", offsetof(RenderPathCommand, markToStencil_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool RenderPathCommand::useLitBase_", "bool useLitBase", offsetof(RenderPathCommand, useLitBase_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool RenderPathCommand::vertexLights_", "bool vertexLights", offsetof(RenderPathCommand, vertexLights_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String RenderPathCommand::eventName_", "String eventName", offsetof(RenderPathCommand, eventName_)));

}

// struct RenderTargetInfo | File: ../Graphics/RenderPath.h
void CollectMembers_RenderTargetInfo(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("String RenderTargetInfo::name_", "String name", offsetof(RenderTargetInfo, name_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String RenderTargetInfo::tag_", "String tag", offsetof(RenderTargetInfo, tag_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned RenderTargetInfo::format_", "uint format", offsetof(RenderTargetInfo, format_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 RenderTargetInfo::size_", "Vector2 size", offsetof(RenderTargetInfo, size_)));
    members.fields_.Push(RegisterObjectPropertyArgs("RenderTargetSizeMode RenderTargetInfo::sizeMode_", "RenderTargetSizeMode sizeMode", offsetof(RenderTargetInfo, sizeMode_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int RenderTargetInfo::multiSample_", "int multiSample", offsetof(RenderTargetInfo, multiSample_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool RenderTargetInfo::autoResolve_", "bool autoResolve", offsetof(RenderTargetInfo, autoResolve_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool RenderTargetInfo::enabled_", "bool enabled", offsetof(RenderTargetInfo, enabled_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool RenderTargetInfo::cubemap_", "bool cubemap", offsetof(RenderTargetInfo, cubemap_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool RenderTargetInfo::filtered_", "bool filtered", offsetof(RenderTargetInfo, filtered_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool RenderTargetInfo::sRGB_", "bool sRGB", offsetof(RenderTargetInfo, sRGB_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool RenderTargetInfo::persistent_", "bool persistent", offsetof(RenderTargetInfo, persistent_)));

}

// struct ScenePassInfo | File: ../Graphics/View.h
void CollectMembers_ScenePassInfo(MemberCollection& members)
{
    // BatchQueue* ScenePassInfo::batchQueue_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ScenePassInfo::passIndex_", "uint passIndex", offsetof(ScenePassInfo, passIndex_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool ScenePassInfo::allowInstancing_", "bool allowInstancing", offsetof(ScenePassInfo, allowInstancing_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool ScenePassInfo::markToStencil_", "bool markToStencil", offsetof(ScenePassInfo, markToStencil_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool ScenePassInfo::vertexLights_", "bool vertexLights", offsetof(ScenePassInfo, vertexLights_)));

}

// struct ScratchBuffer | File: ../Graphics/Graphics.h
void CollectMembers_ScratchBuffer(MemberCollection& members)
{
    // SharedArrayPtr<unsigned char> ScratchBuffer::data_
    // Error: type "SharedArrayPtr<unsigned char>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ScratchBuffer::size_", "uint size", offsetof(ScratchBuffer, size_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool ScratchBuffer::reserved_", "bool reserved", offsetof(ScratchBuffer, reserved_)));

}

// struct ScreenModeParams | File: ../Graphics/Graphics.h
void CollectMembers_ScreenModeParams(MemberCollection& members)
{
    // bool ScreenModeParams::operator !=(const ScreenModeParams& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("bool ScreenModeParams::fullscreen_", "bool fullscreen", offsetof(ScreenModeParams, fullscreen_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool ScreenModeParams::borderless_", "bool borderless", offsetof(ScreenModeParams, borderless_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool ScreenModeParams::resizable_", "bool resizable", offsetof(ScreenModeParams, resizable_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool ScreenModeParams::highDPI_", "bool highDPI", offsetof(ScreenModeParams, highDPI_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool ScreenModeParams::vsync_", "bool vsync", offsetof(ScreenModeParams, vsync_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool ScreenModeParams::tripleBuffer_", "bool tripleBuffer", offsetof(ScreenModeParams, tripleBuffer_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int ScreenModeParams::multiSample_", "int multiSample", offsetof(ScreenModeParams, multiSample_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int ScreenModeParams::monitor_", "int monitor", offsetof(ScreenModeParams, monitor_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int ScreenModeParams::refreshRate_", "int refreshRate", offsetof(ScreenModeParams, refreshRate_)));

}

// struct ShaderParameter | File: ../Graphics/ShaderVariation.h
void CollectMembers_ShaderParameter(MemberCollection& members)
{
    // union ShaderParameter::@4 Urho3D::ShaderParameter::@5
    // Error: type "union Urho3D::ShaderParameter::@4" can not automatically bind
    // union ShaderParameter::@6 Urho3D::ShaderParameter::@7
    // Error: type "union Urho3D::ShaderParameter::@6" can not automatically bind
    // ConstantBuffer* ShaderParameter::bufferPtr_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("ShaderType ShaderParameter::type_", "ShaderType type", offsetof(ShaderParameter, type_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String ShaderParameter::name_", "String name", offsetof(ShaderParameter, name_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ShaderParameter::offset_", "uint offset", offsetof(ShaderParameter, offset_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int ShaderParameter::location_", "int location", offsetof(ShaderParameter, location_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ShaderParameter::register_", "uint register", offsetof(ShaderParameter, register_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ShaderParameter::size_", "uint size", offsetof(ShaderParameter, size_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ShaderParameter::glType_", "uint glType", offsetof(ShaderParameter, glType_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ShaderParameter::regCount_", "uint regCount", offsetof(ShaderParameter, regCount_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ShaderParameter::buffer_", "uint buffer", offsetof(ShaderParameter, buffer_)));

}

// struct ShadowBatchQueue | File: ../Graphics/Batch.h
void CollectMembers_ShadowBatchQueue(MemberCollection& members)
{
    // Camera* ShadowBatchQueue::shadowCamera_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("IntRect ShadowBatchQueue::shadowViewport_", "IntRect shadowViewport", offsetof(ShadowBatchQueue, shadowViewport_)));
    members.fields_.Push(RegisterObjectPropertyArgs("BatchQueue ShadowBatchQueue::shadowBatches_", "BatchQueue shadowBatches", offsetof(ShadowBatchQueue, shadowBatches_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float ShadowBatchQueue::nearSplit_", "float nearSplit", offsetof(ShadowBatchQueue, nearSplit_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float ShadowBatchQueue::farSplit_", "float farSplit", offsetof(ShadowBatchQueue, farSplit_)));

}

// class Skeleton | File: ../Graphics/Skeleton.h
void CollectMembers_Skeleton(MemberCollection& members)
{
    // Bone* Skeleton::GetBone(const char* name)
    // Error: type "const char*" can not automatically bind
    // const Vector<Bone>& Skeleton::GetBones() const
    // Error: type "const Vector<Bone>&" can not automatically bind
    // Vector<Bone>& Skeleton::GetModifiableBones()
    // Error: type "Vector<Bone>&" can not automatically bind

}

// struct SourceBatch | File: ../Graphics/Drawable.h
void CollectMembers_SourceBatch(MemberCollection& members)
{
    // Geometry* SourceBatch::geometry_
    // Not registered because pointer
    // SharedPtr<Material> SourceBatch::material_
    // Error: type "SharedPtr<Material>" can not automatically bind
    // const Matrix3x4* SourceBatch::worldTransform_
    // Not registered because pointer
    // void* SourceBatch::instancingData_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("float SourceBatch::distance_", "float distance", offsetof(SourceBatch, distance_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned SourceBatch::numWorldTransforms_", "uint numWorldTransforms", offsetof(SourceBatch, numWorldTransforms_)));
    members.fields_.Push(RegisterObjectPropertyArgs("GeometryType SourceBatch::geometryType_", "GeometryType geometryType", offsetof(SourceBatch, geometryType_)));

}

// struct StaticModelGeometryData | File: ../Graphics/StaticModel.h
void CollectMembers_StaticModelGeometryData(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 StaticModelGeometryData::center_", "Vector3 center", offsetof(StaticModelGeometryData, center_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned StaticModelGeometryData::lodLevel_", "uint lodLevel", offsetof(StaticModelGeometryData, lodLevel_)));

}

// struct TechniqueEntry | File: ../Graphics/Material.h
void CollectMembers_TechniqueEntry(MemberCollection& members)
{
    // SharedPtr<Technique> TechniqueEntry::technique_
    // Error: type "SharedPtr<Technique>" can not automatically bind
    // SharedPtr<Technique> TechniqueEntry::original_
    // Error: type "SharedPtr<Technique>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("MaterialQuality TechniqueEntry::qualityLevel_", "MaterialQuality qualityLevel", offsetof(TechniqueEntry, qualityLevel_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float TechniqueEntry::lodDistance_", "float lodDistance", offsetof(TechniqueEntry, lodDistance_)));

}

// struct TextureFrame | File: ../Graphics/ParticleEffect.h
void CollectMembers_TextureFrame(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("Rect TextureFrame::uv_", "Rect uv", offsetof(TextureFrame, uv_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float TextureFrame::time_", "float time", offsetof(TextureFrame, time_)));

}

// struct TrailPoint | File: ../Graphics/RibbonTrail.h
void CollectMembers_TrailPoint(MemberCollection& members)
{
    // TrailPoint* TrailPoint::next_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 TrailPoint::position_", "Vector3 position", offsetof(TrailPoint, position_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 TrailPoint::forward_", "Vector3 forward", offsetof(TrailPoint, forward_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 TrailPoint::parentPos_", "Vector3 parentPos", offsetof(TrailPoint, parentPos_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float TrailPoint::elapsedLength_", "float elapsedLength", offsetof(TrailPoint, elapsedLength_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float TrailPoint::lifetime_", "float lifetime", offsetof(TrailPoint, lifetime_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float TrailPoint::sortDistance_", "float sortDistance", offsetof(TrailPoint, sortDistance_)));

}

// struct VertexBufferDesc | File: ../Graphics/Model.h
void CollectMembers_VertexBufferDesc(MemberCollection& members)
{
    // PODVector<VertexElement> VertexBufferDesc::vertexElements_
    // Error: type "PODVector<VertexElement>" can not automatically bind
    // SharedArrayPtr<unsigned char> VertexBufferDesc::data_
    // Error: type "SharedArrayPtr<unsigned char>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned VertexBufferDesc::vertexCount_", "uint vertexCount", offsetof(VertexBufferDesc, vertexCount_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned VertexBufferDesc::dataSize_", "uint dataSize", offsetof(VertexBufferDesc, dataSize_)));

}

// struct VertexBufferMorph | File: ../Graphics/Model.h
void CollectMembers_VertexBufferMorph(MemberCollection& members)
{
    // SharedArrayPtr<unsigned char> VertexBufferMorph::morphData_
    // Error: type "SharedArrayPtr<unsigned char>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("VertexMaskFlags VertexBufferMorph::elementMask_", "VertexMaskFlags elementMask", offsetof(VertexBufferMorph, elementMask_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned VertexBufferMorph::vertexCount_", "uint vertexCount", offsetof(VertexBufferMorph, vertexCount_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned VertexBufferMorph::dataSize_", "uint dataSize", offsetof(VertexBufferMorph, dataSize_)));

}

// struct VertexElement | File: ../Graphics/GraphicsDefs.h
void CollectMembers_VertexElement(MemberCollection& members)
{
    // bool VertexElement::operator !=(const VertexElement& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("VertexElementType VertexElement::type_", "VertexElementType type", offsetof(VertexElement, type_)));
    members.fields_.Push(RegisterObjectPropertyArgs("VertexElementSemantic VertexElement::semantic_", "VertexElementSemantic semantic", offsetof(VertexElement, semantic_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char VertexElement::index_", "uint8 index", offsetof(VertexElement, index_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool VertexElement::perInstance_", "bool perInstance", offsetof(VertexElement, perInstance_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned VertexElement::offset_", "uint offset", offsetof(VertexElement, offset_)));

}

// struct WindowModeParams | File: ../Graphics/Graphics.h
void CollectMembers_WindowModeParams(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("int WindowModeParams::width_", "int width", offsetof(WindowModeParams, width_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int WindowModeParams::height_", "int height", offsetof(WindowModeParams, height_)));
    members.fields_.Push(RegisterObjectPropertyArgs("ScreenModeParams WindowModeParams::screenParams_", "ScreenModeParams screenParams", offsetof(WindowModeParams, screenParams_)));

}

// class AllContentOctreeQuery | File: ../Graphics/OctreeQuery.h
void CollectMembers_AllContentOctreeQuery(MemberCollection& members)
{
    CollectMembers_OctreeQuery(members);

    Remove(members.methods_, "virtual Intersection OctreeQuery::TestOctant(const BoundingBox& box, bool inside) = 0");
    Remove(members.methods_, "virtual void OctreeQuery::TestDrawables(Drawable** start, Drawable** end, bool inside) = 0");

}

// class AnimationState | File: ../Graphics/AnimationState.h
void CollectMembers_AnimationState(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

}

// struct BatchGroup | File: ../Graphics/Batch.h
void CollectMembers_BatchGroup(MemberCollection& members)
{
    CollectMembers_Batch(members);

    Remove(members.methods_, "void Batch::Draw(View* view, Camera* camera, bool allowDepthWrite) const");

    // void BatchGroup::SetInstancingData(void* lockedData, unsigned stride, unsigned& freeIndex)
    // Error: type "void*" can not automatically bind

    // PODVector<InstanceData> BatchGroup::instances_
    // Error: type "PODVector<InstanceData>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned BatchGroup::startIndex_", "uint startIndex", offsetof(BatchGroup, startIndex_)));

}

// class BoxOctreeQuery | File: ../Graphics/OctreeQuery.h
void CollectMembers_BoxOctreeQuery(MemberCollection& members)
{
    CollectMembers_OctreeQuery(members);

    Remove(members.methods_, "virtual Intersection OctreeQuery::TestOctant(const BoundingBox& box, bool inside) = 0");
    Remove(members.methods_, "virtual void OctreeQuery::TestDrawables(Drawable** start, Drawable** end, bool inside) = 0");

    members.fields_.Push(RegisterObjectPropertyArgs("BoundingBox BoxOctreeQuery::box_", "BoundingBox box", offsetof(BoxOctreeQuery, box_)));

}

// class FrustumOctreeQuery | File: ../Graphics/OctreeQuery.h
void CollectMembers_FrustumOctreeQuery(MemberCollection& members)
{
    CollectMembers_OctreeQuery(members);

    Remove(members.methods_, "virtual Intersection OctreeQuery::TestOctant(const BoundingBox& box, bool inside) = 0");
    Remove(members.methods_, "virtual void OctreeQuery::TestDrawables(Drawable** start, Drawable** end, bool inside) = 0");

    members.fields_.Push(RegisterObjectPropertyArgs("Frustum FrustumOctreeQuery::frustum_", "Frustum frustum", offsetof(FrustumOctreeQuery, frustum_)));

}

// class Pass | File: ../Graphics/Technique.h
void CollectMembers_Pass(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

}

// class PointOctreeQuery | File: ../Graphics/OctreeQuery.h
void CollectMembers_PointOctreeQuery(MemberCollection& members)
{
    CollectMembers_OctreeQuery(members);

    Remove(members.methods_, "virtual Intersection OctreeQuery::TestOctant(const BoundingBox& box, bool inside) = 0");
    Remove(members.methods_, "virtual void OctreeQuery::TestDrawables(Drawable** start, Drawable** end, bool inside) = 0");

    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 PointOctreeQuery::point_", "Vector3 point", offsetof(PointOctreeQuery, point_)));

}

// class RenderPath | File: ../Graphics/RenderPath.h
void CollectMembers_RenderPath(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

    // RenderPathCommand* RenderPath::GetCommand(unsigned index)
    // Error: type "RenderPathCommand*" can not automatically bind

    // Vector<RenderTargetInfo> RenderPath::renderTargets_
    // Error: type "Vector<RenderTargetInfo>" can not automatically bind
    // Vector<RenderPathCommand> RenderPath::commands_
    // Error: type "Vector<RenderPathCommand>" can not automatically bind

}

// class RenderSurface | File: ../Graphics/RenderSurface.h
void CollectMembers_RenderSurface(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

    // void* RenderSurface::GetReadOnlyView() const
    // Error: type "void*" can not automatically bind
    // void* RenderSurface::GetRenderTargetView() const
    // Error: type "void*" can not automatically bind
    // void* RenderSurface::GetSurface() const
    // Error: type "void*" can not automatically bind

    // void* RenderSurface::surface_
    // Not registered because have @nobind mark
    // void* RenderSurface::renderTargetView_
    // Not registered because have @nobind mark
    // unsigned RenderSurface::renderBuffer_
    // Not registered because have @nobind mark
    // void* RenderSurface::readOnlyView_
    // Not registered because have @nobind mark
    // unsigned RenderSurface::target_
    // Not registered because have @nobind mark

}

// class ShaderVariation | File: ../Graphics/ShaderVariation.h
void CollectMembers_ShaderVariation(MemberCollection& members)
{
    CollectMembers_RefCounted(members);
    CollectMembers_GPUObject(members);

    Remove(members.methods_, "virtual void GPUObject::OnDeviceLost()");
    Remove(members.methods_, "virtual void GPUObject::Release()");

    // const PODVector<unsigned char>& ShaderVariation::GetByteCode() const
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // const unsigned* ShaderVariation::GetConstantBufferSizes() const
    // Error: type "const unsigned*" can not automatically bind
    // const HashMap<StringHash, ShaderParameter>& ShaderVariation::GetParameters() const
    // Error: type "const HashMap<StringHash, ShaderParameter>&" can not automatically bind

    // static const char* ShaderVariation::elementSemanticNames[]
    // Error: type "const char*" can not automatically bind

}

// class SphereOctreeQuery | File: ../Graphics/OctreeQuery.h
void CollectMembers_SphereOctreeQuery(MemberCollection& members)
{
    CollectMembers_OctreeQuery(members);

    Remove(members.methods_, "virtual Intersection OctreeQuery::TestOctant(const BoundingBox& box, bool inside) = 0");
    Remove(members.methods_, "virtual void OctreeQuery::TestDrawables(Drawable** start, Drawable** end, bool inside) = 0");

    members.fields_.Push(RegisterObjectPropertyArgs("Sphere SphereOctreeQuery::sphere_", "Sphere sphere", offsetof(SphereOctreeQuery, sphere_)));

}

// class ConstantBuffer | File: ../Graphics/ConstantBuffer.h
void CollectMembers_ConstantBuffer(MemberCollection& members)
{
    CollectMembers_Object(members);
    CollectMembers_GPUObject(members);

    Remove(members.methods_, "virtual void GPUObject::OnDeviceReset()");
    Remove(members.methods_, "virtual void GPUObject::Release()");

    // void ConstantBuffer::SetParameter(unsigned offset, unsigned size, const void* data)
    // Error: type "const void*" can not automatically bind
    // void ConstantBuffer::SetVector3ArrayParameter(unsigned offset, unsigned rows, const void* data)
    // Error: type "const void*" can not automatically bind

}

// class Geometry | File: ../Graphics/Geometry.h
void CollectMembers_Geometry(MemberCollection& members)
{
    CollectMembers_Object(members);

    // float Geometry::GetHitDistance(const Ray& ray, Vector3* outNormal = nullptr, Vector2* outUV = nullptr) const
    // Error: type "Vector3*" can not automatically bind
    // void Geometry::GetRawData(const unsigned char*& vertexData, unsigned& vertexSize, const unsigned char*& indexData, unsigned& indexSize, const PODVector<VertexElement>*& elements) const
    // Error: type "const unsigned char*&" can not automatically bind
    // void Geometry::GetRawDataShared(SharedArrayPtr<unsigned char>& vertexData, unsigned& vertexSize, SharedArrayPtr<unsigned char>& indexData, unsigned& indexSize, const PODVector<VertexElement>*& elements) const
    // Error: type "SharedArrayPtr<unsigned char>&" can not automatically bind
    // void Geometry::SetRawIndexData(const SharedArrayPtr<unsigned char>& data, unsigned indexSize)
    // Error: type "const SharedArrayPtr<unsigned char>&" can not automatically bind
    // void Geometry::SetRawVertexData(const SharedArrayPtr<unsigned char>& data, const PODVector<VertexElement>& elements)
    // Error: type "const SharedArrayPtr<unsigned char>&" can not automatically bind
    // void Geometry::SetRawVertexData(const SharedArrayPtr<unsigned char>& data, unsigned elementMask)
    // Error: type "const SharedArrayPtr<unsigned char>&" can not automatically bind

}

// class Graphics | File: ../Graphics/Graphics.h
void CollectMembers_Graphics(MemberCollection& members)
{
    CollectMembers_Object(members);

    // void Graphics::AddGPUObject(GPUObject* object)
    // Error: type "GPUObject*" can not automatically bind
    // void Graphics::CleanupRenderSurface(RenderSurface* surface)
    // Not registered because have @nobind mark
    // void Graphics::FreeScratchBuffer(void* buffer)
    // Error: type "void*" can not automatically bind
    // void* Graphics::GetExternalWindow() const
    // Error: type "void*" can not automatically bind
    // GraphicsImpl* Graphics::GetImpl() const
    // Error: type "GraphicsImpl*" can not automatically bind
    // ConstantBuffer* Graphics::GetOrCreateConstantBuffer(ShaderType type, unsigned index, unsigned size)
    // Not registered because have @nobind mark
    // ShaderVariation* Graphics::GetShader(ShaderType type, const char* name, const char* defines) const
    // Error: type "const char*" can not automatically bind
    // ShaderProgram* Graphics::GetShaderProgram() const
    // Not registered because have @nobind mark
    // SDL_Window* Graphics::GetWindow() const
    // Error: type "SDL_Window*" can not automatically bind
    // void Graphics::MarkFBODirty()
    // Not registered because have @nobind mark
    // bool Graphics::NeedParameterUpdate(ShaderParameterGroup group, const void* source)
    // Error: type "const void*" can not automatically bind
    // void Graphics::RemoveGPUObject(GPUObject* object)
    // Error: type "GPUObject*" can not automatically bind
    // void* Graphics::ReserveScratchBuffer(unsigned size)
    // Error: type "void*" can not automatically bind
    // void Graphics::Restore()
    // Not registered because have @nobind mark
    // void Graphics::SetExternalWindow(void* window)
    // Error: type "void*" can not automatically bind
    // void Graphics::SetShaderParameter(StringHash param, const float* data, unsigned count)
    // Error: type "const float*" can not automatically bind
    // void Graphics::SetTextureForUpdate(Texture* texture)
    // Not registered because have @nobind mark
    // void Graphics::SetTextureParametersDirty()
    // Not registered because have @nobind mark
    // void Graphics::SetUBO(unsigned object)
    // Not registered because have @nobind mark
    // void Graphics::SetVBO(unsigned object)
    // Not registered because have @nobind mark
    // bool Graphics::SetVertexBuffers(const PODVector<VertexBuffer*>& buffers, unsigned instanceOffset = 0)
    // Not registered because have @nobind mark

}

// class IndexBuffer | File: ../Graphics/IndexBuffer.h
void CollectMembers_IndexBuffer(MemberCollection& members)
{
    CollectMembers_Object(members);
    CollectMembers_GPUObject(members);

    Remove(members.methods_, "virtual void GPUObject::OnDeviceLost()");
    Remove(members.methods_, "virtual void GPUObject::OnDeviceReset()");
    Remove(members.methods_, "virtual void GPUObject::Release()");

    // unsigned char* IndexBuffer::GetShadowData() const
    // Error: type "unsigned char*" can not automatically bind
    // SharedArrayPtr<unsigned char> IndexBuffer::GetShadowDataShared() const
    // Error: type "SharedArrayPtr<unsigned char>" can not automatically bind
    // void* IndexBuffer::Lock(unsigned start, unsigned count, bool discard = false)
    // Error: type "void*" can not automatically bind
    // bool IndexBuffer::SetData(const void* data)
    // Error: type "const void*" can not automatically bind
    // bool IndexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard = false)
    // Error: type "const void*" can not automatically bind

}

// class OcclusionBuffer | File: ../Graphics/OcclusionBuffer.h
void CollectMembers_OcclusionBuffer(MemberCollection& members)
{
    CollectMembers_Object(members);

    // bool OcclusionBuffer::AddTriangles(const Matrix3x4& model, const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount)
    // Error: type "const void*" can not automatically bind
    // bool OcclusionBuffer::AddTriangles(const Matrix3x4& model, const void* vertexData, unsigned vertexSize, unsigned vertexStart, unsigned vertexCount)
    // Error: type "const void*" can not automatically bind
    // int* OcclusionBuffer::GetBuffer() const
    // Error: type "int*" can not automatically bind

}

// class Renderer | File: ../Graphics/Renderer.h
void CollectMembers_Renderer(MemberCollection& members)
{
    CollectMembers_Object(members);

    // void Renderer::SetShadowMapFilter(Object* instance, ShadowMapFilter functionPtr)
    // Not registered because have @nobind mark

}

// class ShaderParameterAnimationInfo | File: ../Graphics/Material.h
void CollectMembers_ShaderParameterAnimationInfo(MemberCollection& members)
{
    CollectMembers_ValueAnimationInfo(members);

}

// class ShaderPrecache | File: ../Graphics/ShaderPrecache.h
void CollectMembers_ShaderPrecache(MemberCollection& members)
{
    CollectMembers_Object(members);

}

// class VertexBuffer | File: ../Graphics/VertexBuffer.h
void CollectMembers_VertexBuffer(MemberCollection& members)
{
    CollectMembers_Object(members);
    CollectMembers_GPUObject(members);

    Remove(members.methods_, "virtual void GPUObject::OnDeviceLost()");
    Remove(members.methods_, "virtual void GPUObject::OnDeviceReset()");
    Remove(members.methods_, "virtual void GPUObject::Release()");

    // const VertexElement* VertexBuffer::GetElement(VertexElementSemantic semantic, unsigned char index = 0) const
    // Error: type "const VertexElement*" can not automatically bind
    // const VertexElement* VertexBuffer::GetElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index = 0) const
    // Error: type "const VertexElement*" can not automatically bind
    // unsigned char* VertexBuffer::GetShadowData() const
    // Error: type "unsigned char*" can not automatically bind
    // SharedArrayPtr<unsigned char> VertexBuffer::GetShadowDataShared() const
    // Error: type "SharedArrayPtr<unsigned char>" can not automatically bind
    // void* VertexBuffer::Lock(unsigned start, unsigned count, bool discard = false)
    // Error: type "void*" can not automatically bind
    // bool VertexBuffer::SetData(const void* data)
    // Error: type "const void*" can not automatically bind
    // bool VertexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard = false)
    // Error: type "const void*" can not automatically bind

    // static const VertexElement* VertexBuffer::GetElement(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index = 0)
    // Error: type "const VertexElement*" can not automatically bind
    // static void VertexBuffer::UpdateOffsets(PODVector<VertexElement>& elements)
    // Error: type "PODVector<VertexElement>&" can not automatically bind

}

// class View | File: ../Graphics/View.h
void CollectMembers_View(MemberCollection& members)
{
    CollectMembers_Object(members);

    // const Vector<LightBatchQueue>& View::GetLightQueues() const
    // Error: type "const Vector<LightBatchQueue>&" can not automatically bind

}

// class Viewport | File: ../Graphics/Viewport.h
void CollectMembers_Viewport(MemberCollection& members)
{
    CollectMembers_Object(members);

}

// class Material | File: ../Graphics/Material.h
void CollectMembers_Material(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "bool Resource::Load(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::EndLoad()");
    Remove(members.methods_, "virtual bool Resource::Save(Serializer& dest) const");

    // const HashMap<StringHash, MaterialShaderParameter>& Material::GetShaderParameters() const
    // Error: type "const HashMap<StringHash, MaterialShaderParameter>&" can not automatically bind
    // const Vector<TechniqueEntry>& Material::GetTechniques() const
    // Error: type "const Vector<TechniqueEntry>&" can not automatically bind
    // const HashMap<TextureUnit, SharedPtr<Texture>>& Material::GetTextures() const
    // Error: type "const HashMap<TextureUnit, SharedPtr<Texture>>&" can not automatically bind

    // static void Material::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class ParticleEffect | File: ../Graphics/ParticleEffect.h
void CollectMembers_ParticleEffect(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "bool Resource::Load(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::EndLoad()");
    Remove(members.methods_, "virtual bool Resource::Save(Serializer& dest) const");

    // const Vector<ColorFrame>& ParticleEffect::GetColorFrames() const
    // Error: type "const Vector<ColorFrame>&" can not automatically bind
    // const Vector<TextureFrame>& ParticleEffect::GetTextureFrames() const
    // Error: type "const Vector<TextureFrame>&" can not automatically bind
    // void ParticleEffect::SetColorFrames(const Vector<ColorFrame>& colorFrames)
    // Error: type "const Vector<ColorFrame>&" can not automatically bind
    // void ParticleEffect::SetTextureFrames(const Vector<TextureFrame>& textureFrames)
    // Error: type "const Vector<TextureFrame>&" can not automatically bind

    // static void ParticleEffect::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class Shader | File: ../Graphics/Shader.h
void CollectMembers_Shader(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::EndLoad()");

    // ShaderVariation* Shader::GetVariation(ShaderType type, const char* defines)
    // Error: type "const char*" can not automatically bind

    // static void Shader::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class Technique | File: ../Graphics/Technique.h
void CollectMembers_Technique(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");

    // static void Technique::RegisterObject(Context* context)
    // Not registered because have @nobind mark

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static unsigned Technique::basePassIndex", "uint basePassIndex", (void*)&Technique::basePassIndex));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static unsigned Technique::alphaPassIndex", "uint alphaPassIndex", (void*)&Technique::alphaPassIndex));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static unsigned Technique::materialPassIndex", "uint materialPassIndex", (void*)&Technique::materialPassIndex));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static unsigned Technique::deferredPassIndex", "uint deferredPassIndex", (void*)&Technique::deferredPassIndex));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static unsigned Technique::lightPassIndex", "uint lightPassIndex", (void*)&Technique::lightPassIndex));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static unsigned Technique::litBasePassIndex", "uint litBasePassIndex", (void*)&Technique::litBasePassIndex));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static unsigned Technique::litAlphaPassIndex", "uint litAlphaPassIndex", (void*)&Technique::litAlphaPassIndex));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static unsigned Technique::shadowPassIndex", "uint shadowPassIndex", (void*)&Technique::shadowPassIndex));

}

// class Animation | File: ../Graphics/Animation.h
void CollectMembers_Animation(MemberCollection& members)
{
    CollectMembers_ResourceWithMetadata(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::Save(Serializer& dest) const");

    // const HashMap<StringHash, AnimationTrack>& Animation::GetTracks() const
    // Error: type "const HashMap<StringHash, AnimationTrack>&" can not automatically bind
    // AnimationTriggerPoint* Animation::GetTrigger(unsigned index)
    // Error: type "AnimationTriggerPoint*" can not automatically bind
    // const Vector<AnimationTriggerPoint>& Animation::GetTriggers() const
    // Error: type "const Vector<AnimationTriggerPoint>&" can not automatically bind

    // static void Animation::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class Model | File: ../Graphics/Model.h
void CollectMembers_Model(MemberCollection& members)
{
    CollectMembers_ResourceWithMetadata(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::EndLoad()");
    Remove(members.methods_, "virtual bool Resource::Save(Serializer& dest) const");

    // const Vector<Vector<SharedPtr<Geometry>>>& Model::GetGeometries() const
    // Error: type "const Vector<Vector<SharedPtr<Geometry>>>&" can not automatically bind
    // const Vector<PODVector<unsigned>>& Model::GetGeometryBoneMappings() const
    // Error: type "const Vector<PODVector<unsigned>>&" can not automatically bind
    // const ModelMorph* Model::GetMorph(StringHash nameHash) const
    // Error: type "const ModelMorph*" can not automatically bind
    // const ModelMorph* Model::GetMorph(const String& name) const
    // Error: type "const ModelMorph*" can not automatically bind
    // const ModelMorph* Model::GetMorph(unsigned index) const
    // Error: type "const ModelMorph*" can not automatically bind
    // const Vector<ModelMorph>& Model::GetMorphs() const
    // Error: type "const Vector<ModelMorph>&" can not automatically bind
    // void Model::SetGeometryBoneMappings(const Vector<PODVector<unsigned>>& geometryBoneMappings)
    // Error: type "const Vector<PODVector<unsigned>>&" can not automatically bind
    // void Model::SetMorphs(const Vector<ModelMorph>& morphs)
    // Error: type "const Vector<ModelMorph>&" can not automatically bind

    // static void Model::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class Texture | File: ../Graphics/Texture.h
void CollectMembers_Texture(MemberCollection& members)
{
    CollectMembers_ResourceWithMetadata(members);
    CollectMembers_GPUObject(members);

    // void* Texture::GetResolveTexture() const
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetSRGBFormat(unsigned format)
    // Not registered because have @nobind mark
    // void* Texture::GetSampler() const
    // Error: type "void*" can not automatically bind
    // void* Texture::GetShaderResourceView() const
    // Error: type "void*" can not automatically bind

    // static unsigned Texture::GetSRVFormat(unsigned format)
    // Not registered because have @nobind mark
    // static unsigned Texture::GetDSVFormat(unsigned format)
    // Not registered because have @nobind mark
    // static unsigned Texture::GetExternalFormat(unsigned format)
    // Not registered because have @nobind mark
    // static unsigned Texture::GetDataType(unsigned format)
    // Not registered because have @nobind mark

}

// class AnimationController | File: ../Graphics/AnimationController.h
void CollectMembers_AnimationController(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::OnSetEnabled()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // const Vector<AnimationControl>& AnimationController::GetAnimations() const
    // Error: type "const Vector<AnimationControl>&" can not automatically bind
    // VariantVector AnimationController::GetAnimationsAttr() const
    // Error: type "VariantVector" can not automatically bind
    // const PODVector<unsigned char>& AnimationController::GetNetAnimationsAttr() const
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // VariantVector AnimationController::GetNodeAnimationStatesAttr() const
    // Error: type "VariantVector" can not automatically bind
    // void AnimationController::SetAnimationsAttr(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind
    // void AnimationController::SetNetAnimationsAttr(const PODVector<unsigned char>& value)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void AnimationController::SetNodeAnimationStatesAttr(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind

}

// class Camera | File: ../Graphics/Camera.h
void CollectMembers_Camera(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

}

// class DebugRenderer | File: ../Graphics/DebugRenderer.h
void CollectMembers_DebugRenderer(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // void DebugRenderer::AddTriangleMesh(const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount, const Matrix3x4& transform, const Color& color, bool depthTest = true)
    // Error: type "const void*" can not automatically bind
    // void DebugRenderer::AddTriangleMesh(const void* vertexData, unsigned vertexSize, unsigned vertexStart, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount, const Matrix3x4& transform, const Color& color, bool depthTest = true)
    // Error: type "const void*" can not automatically bind

}

// class Drawable | File: ../Graphics/Drawable.h
void CollectMembers_Drawable(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");
    Remove(members.methods_, "virtual void Component::OnSetEnabled()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // const Vector<SourceBatch>& Drawable::GetBatches() const
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // Octant* Drawable::GetOctant() const
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark

}

// class Octree | File: ../Graphics/Octree.h
void CollectMembers_Octree(MemberCollection& members)
{
    CollectMembers_Component(members);
    CollectMembers_Octant(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");
    Remove(members.methods_, "void Octant::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // void Octree::GetDrawables(OctreeQuery& query) const
    // Not registered because have @nobind mark
    // void Octree::Raycast(RayOctreeQuery& query) const
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // void Octree::RaycastSingle(RayOctreeQuery& query) const
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark

}

// class Terrain | File: ../Graphics/Terrain.h
void CollectMembers_Terrain(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::OnSetEnabled()");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // SharedArrayPtr<float> Terrain::GetHeightData() const
    // Error: type "SharedArrayPtr<float>" can not automatically bind

}

// class Texture2D | File: ../Graphics/Texture2D.h
void CollectMembers_Texture2D(MemberCollection& members)
{
    CollectMembers_Texture(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::EndLoad()");
    Remove(members.methods_, "virtual void GPUObject::OnDeviceLost()");
    Remove(members.methods_, "virtual void GPUObject::OnDeviceReset()");
    Remove(members.methods_, "virtual void GPUObject::Release()");

    // bool Texture2D::GetData(unsigned level, void* dest) const
    // Error: type "void*" can not automatically bind
    // bool Texture2D::SetData(unsigned level, int x, int y, int width, int height, const void* data)
    // Error: type "const void*" can not automatically bind

    // static void Texture2D::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class Texture2DArray | File: ../Graphics/Texture2DArray.h
void CollectMembers_Texture2DArray(MemberCollection& members)
{
    CollectMembers_Texture(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::EndLoad()");
    Remove(members.methods_, "virtual void GPUObject::OnDeviceLost()");
    Remove(members.methods_, "virtual void GPUObject::OnDeviceReset()");
    Remove(members.methods_, "virtual void GPUObject::Release()");

    // bool Texture2DArray::GetData(unsigned layer, unsigned level, void* dest) const
    // Error: type "void*" can not automatically bind
    // bool Texture2DArray::SetData(unsigned layer, unsigned level, int x, int y, int width, int height, const void* data)
    // Error: type "const void*" can not automatically bind

    // static void Texture2DArray::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class Texture3D | File: ../Graphics/Texture3D.h
void CollectMembers_Texture3D(MemberCollection& members)
{
    CollectMembers_Texture(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::EndLoad()");
    Remove(members.methods_, "virtual void GPUObject::OnDeviceLost()");
    Remove(members.methods_, "virtual void GPUObject::OnDeviceReset()");
    Remove(members.methods_, "virtual void GPUObject::Release()");

    // bool Texture3D::GetData(unsigned level, void* dest) const
    // Error: type "void*" can not automatically bind
    // bool Texture3D::SetData(unsigned level, int x, int y, int z, int width, int height, int depth, const void* data)
    // Error: type "const void*" can not automatically bind

    // static void Texture3D::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class TextureCube | File: ../Graphics/TextureCube.h
void CollectMembers_TextureCube(MemberCollection& members)
{
    CollectMembers_Texture(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::EndLoad()");
    Remove(members.methods_, "virtual void GPUObject::OnDeviceLost()");
    Remove(members.methods_, "virtual void GPUObject::OnDeviceReset()");
    Remove(members.methods_, "virtual void GPUObject::Release()");

    // bool TextureCube::GetData(CubeMapFace face, unsigned level, void* dest) const
    // Error: type "void*" can not automatically bind
    // bool TextureCube::SetData(CubeMapFace face, unsigned level, int x, int y, int width, int height, const void* data)
    // Error: type "const void*" can not automatically bind

    // static void TextureCube::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class BillboardSet | File: ../Graphics/BillboardSet.h
void CollectMembers_BillboardSet(MemberCollection& members)
{
    CollectMembers_Drawable(members);

    Remove(members.methods_, "virtual UpdateGeometryType Drawable::GetUpdateGeometryType()");
    Remove(members.methods_, "virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)");
    Remove(members.methods_, "virtual void Drawable::UpdateBatches(const FrameInfo& frame)");
    Remove(members.methods_, "virtual void Drawable::UpdateGeometry(const FrameInfo& frame)");

    Remove(members.staticMethods_, "static void Drawable::RegisterObject(Context* context)");

    // PODVector<Billboard>& BillboardSet::GetBillboards()
    // Error: type "PODVector<Billboard>&" can not automatically bind
    // VariantVector BillboardSet::GetBillboardsAttr() const
    // Error: type "VariantVector" can not automatically bind
    // const PODVector<unsigned char>& BillboardSet::GetNetBillboardsAttr() const
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void BillboardSet::SetBillboardsAttr(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind
    // void BillboardSet::SetNetBillboardsAttr(const PODVector<unsigned char>& value)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind

}

// class CustomGeometry | File: ../Graphics/CustomGeometry.h
void CollectMembers_CustomGeometry(MemberCollection& members)
{
    CollectMembers_Drawable(members);

    Remove(members.methods_, "virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level)");
    Remove(members.methods_, "virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer)");
    Remove(members.methods_, "virtual unsigned Drawable::GetNumOccluderTriangles()");
    Remove(members.methods_, "virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)");

    Remove(members.staticMethods_, "static void Drawable::RegisterObject(Context* context)");

    // PODVector<unsigned char> CustomGeometry::GetGeometryDataAttr() const
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // Vector<PODVector<CustomGeometryVertex>>& CustomGeometry::GetVertices()
    // Error: type "Vector<PODVector<CustomGeometryVertex>>&" can not automatically bind
    // void CustomGeometry::SetGeometryDataAttr(const PODVector<unsigned char>& value)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind

}

// class DecalSet | File: ../Graphics/DecalSet.h
void CollectMembers_DecalSet(MemberCollection& members)
{
    CollectMembers_Drawable(members);

    Remove(members.methods_, "virtual UpdateGeometryType Drawable::GetUpdateGeometryType()");
    Remove(members.methods_, "virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)");
    Remove(members.methods_, "virtual void Drawable::UpdateBatches(const FrameInfo& frame)");
    Remove(members.methods_, "virtual void Drawable::UpdateGeometry(const FrameInfo& frame)");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");
    Remove(members.methods_, "void Drawable::OnSetEnabled() override");

    Remove(members.staticMethods_, "static void Drawable::RegisterObject(Context* context)");

    // PODVector<unsigned char> DecalSet::GetDecalsAttr() const
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // void DecalSet::SetDecalsAttr(const PODVector<unsigned char>& value)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind

}

// class Light | File: ../Graphics/Light.h
void CollectMembers_Light(MemberCollection& members)
{
    CollectMembers_Drawable(members);

    Remove(members.methods_, "virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)");
    Remove(members.methods_, "virtual void Drawable::UpdateBatches(const FrameInfo& frame)");
    Remove(members.methods_, "void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override");

    Remove(members.staticMethods_, "static void Drawable::RegisterObject(Context* context)");

    // LightBatchQueue* Light::GetLightQueue() const
    // Error: type "LightBatchQueue*" can not automatically bind
    // void Light::SetLightQueue(LightBatchQueue* queue)
    // Error: type "LightBatchQueue*" can not automatically bind

}

// class RibbonTrail | File: ../Graphics/RibbonTrail.h
void CollectMembers_RibbonTrail(MemberCollection& members)
{
    CollectMembers_Drawable(members);

    Remove(members.methods_, "virtual UpdateGeometryType Drawable::GetUpdateGeometryType()");
    Remove(members.methods_, "virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)");
    Remove(members.methods_, "virtual void Drawable::Update(const FrameInfo& frame)");
    Remove(members.methods_, "virtual void Drawable::UpdateBatches(const FrameInfo& frame)");
    Remove(members.methods_, "virtual void Drawable::UpdateGeometry(const FrameInfo& frame)");
    Remove(members.methods_, "void Drawable::OnSetEnabled() override");

    Remove(members.staticMethods_, "static void Drawable::RegisterObject(Context* context)");

}

// class StaticModel | File: ../Graphics/StaticModel.h
void CollectMembers_StaticModel(MemberCollection& members)
{
    CollectMembers_Drawable(members);

    Remove(members.methods_, "virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level)");
    Remove(members.methods_, "virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer)");
    Remove(members.methods_, "virtual unsigned Drawable::GetNumOccluderTriangles()");
    Remove(members.methods_, "virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)");
    Remove(members.methods_, "virtual void Drawable::UpdateBatches(const FrameInfo& frame)");

    Remove(members.staticMethods_, "static void Drawable::RegisterObject(Context* context)");

    // virtual void StaticModel::SetModel(Model* model)
    // Not registered because have @manualbind mark

}

// class TerrainPatch | File: ../Graphics/TerrainPatch.h
void CollectMembers_TerrainPatch(MemberCollection& members)
{
    CollectMembers_Drawable(members);

    Remove(members.methods_, "virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level)");
    Remove(members.methods_, "virtual UpdateGeometryType Drawable::GetUpdateGeometryType()");
    Remove(members.methods_, "virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer)");
    Remove(members.methods_, "virtual unsigned Drawable::GetNumOccluderTriangles()");
    Remove(members.methods_, "virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)");
    Remove(members.methods_, "virtual void Drawable::UpdateBatches(const FrameInfo& frame)");
    Remove(members.methods_, "virtual void Drawable::UpdateGeometry(const FrameInfo& frame)");
    Remove(members.methods_, "void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override");

    Remove(members.staticMethods_, "static void Drawable::RegisterObject(Context* context)");

    // PODVector<float>& TerrainPatch::GetLodErrors()
    // Error: type "PODVector<float>&" can not automatically bind

}

// class Zone | File: ../Graphics/Zone.h
void CollectMembers_Zone(MemberCollection& members)
{
    CollectMembers_Drawable(members);

    Remove(members.methods_, "void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override");

    Remove(members.staticMethods_, "static void Drawable::RegisterObject(Context* context)");

}

// class AnimatedModel | File: ../Graphics/AnimatedModel.h
void CollectMembers_AnimatedModel(MemberCollection& members)
{
    CollectMembers_StaticModel(members);

    Remove(members.methods_, "ResourceRef StaticModel::GetModelAttr() const");
    Remove(members.methods_, "bool Animatable::LoadJSON(const JSONValue& source) override");
    Remove(members.methods_, "bool Animatable::LoadXML(const XMLElement& source) override");
    Remove(members.methods_, "virtual UpdateGeometryType Drawable::GetUpdateGeometryType()");
    Remove(members.methods_, "virtual bool Serializable::Load(Deserializer& source)");
    Remove(members.methods_, "virtual void Drawable::Update(const FrameInfo& frame)");
    Remove(members.methods_, "virtual void Drawable::UpdateGeometry(const FrameInfo& frame)");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");
    Remove(members.methods_, "virtual void StaticModel::SetModel(Model* model)");
    Remove(members.methods_, "void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override");
    Remove(members.methods_, "void StaticModel::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override");
    Remove(members.methods_, "void StaticModel::SetModelAttr(const ResourceRef& value)");
    Remove(members.methods_, "void StaticModel::UpdateBatches(const FrameInfo& frame) override");

    Remove(members.staticMethods_, "static void StaticModel::RegisterObject(Context* context)");

    // VariantVector AnimatedModel::GetAnimationStatesAttr() const
    // Error: type "VariantVector" can not automatically bind
    // VariantVector AnimatedModel::GetBonesEnabledAttr() const
    // Error: type "VariantVector" can not automatically bind
    // const Vector<PODVector<unsigned>>& AnimatedModel::GetGeometryBoneMappings() const
    // Error: type "const Vector<PODVector<unsigned>>&" can not automatically bind
    // const Vector<PODVector<Matrix3x4>>& AnimatedModel::GetGeometrySkinMatrices() const
    // Error: type "const Vector<PODVector<Matrix3x4>>&" can not automatically bind
    // const Vector<ModelMorph>& AnimatedModel::GetMorphs() const
    // Error: type "const Vector<ModelMorph>&" can not automatically bind
    // const PODVector<unsigned char>& AnimatedModel::GetMorphsAttr() const
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void AnimatedModel::SetAnimationStatesAttr(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind
    // void AnimatedModel::SetBonesEnabledAttr(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind
    // void AnimatedModel::SetMorphsAttr(const PODVector<unsigned char>& value)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind

}

// class ParticleEmitter | File: ../Graphics/ParticleEmitter.h
void CollectMembers_ParticleEmitter(MemberCollection& members)
{
    CollectMembers_BillboardSet(members);

    Remove(members.methods_, "virtual void Drawable::Update(const FrameInfo& frame)");
    Remove(members.methods_, "void Drawable::OnSetEnabled() override");

    Remove(members.staticMethods_, "static void BillboardSet::RegisterObject(Context* context)");

    // VariantVector ParticleEmitter::GetParticleBillboardsAttr() const
    // Error: type "VariantVector" can not automatically bind
    // VariantVector ParticleEmitter::GetParticlesAttr() const
    // Error: type "VariantVector" can not automatically bind
    // void ParticleEmitter::SetParticlesAttr(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind

}

// class Skybox | File: ../Graphics/Skybox.h
void CollectMembers_Skybox(MemberCollection& members)
{
    CollectMembers_StaticModel(members);

    Remove(members.methods_, "void StaticModel::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override");
    Remove(members.methods_, "void StaticModel::UpdateBatches(const FrameInfo& frame) override");

    Remove(members.staticMethods_, "static void StaticModel::RegisterObject(Context* context)");

    // virtual void StaticModel::SetModel(Model* model)
    // Not registered because have @manualbind mark

}

// class StaticModelGroup | File: ../Graphics/StaticModelGroup.h
void CollectMembers_StaticModelGroup(MemberCollection& members)
{
    CollectMembers_StaticModel(members);

    Remove(members.methods_, "bool StaticModel::DrawOcclusion(OcclusionBuffer* buffer) override");
    Remove(members.methods_, "unsigned StaticModel::GetNumOccluderTriangles() override");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");
    Remove(members.methods_, "void StaticModel::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override");
    Remove(members.methods_, "void StaticModel::UpdateBatches(const FrameInfo& frame) override");

    Remove(members.staticMethods_, "static void StaticModel::RegisterObject(Context* context)");

    // const VariantVector& StaticModelGroup::GetNodeIDsAttr() const
    // Error: type "const VariantVector&" can not automatically bind
    // virtual void StaticModel::SetModel(Model* model)
    // Not registered because have @manualbind mark
    // void StaticModelGroup::SetNodeIDsAttr(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind

}

} // namespace Urho3D
