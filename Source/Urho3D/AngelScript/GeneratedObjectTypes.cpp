// DO NOT EDIT. This file is generated

// We need register all types before registration of any functions because functions can use any types

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"

namespace Urho3D
{

void ASRegisterGeneratedObjectTypes(asIScriptEngine* engine)
{
    // class AbstractFile | File: ../IO/AbstractFile.h
    engine->RegisterObjectType("AbstractFile", 0, asOBJ_REF);

    // class AllContentOctreeQuery | File: ../Graphics/OctreeQuery.h
    // Not registered because have @nobind mark

    // struct AllocatorBlock | File: ../Container/Allocator.h
    engine->RegisterObjectType("AllocatorBlock", sizeof(AllocatorBlock), asOBJ_VALUE | asGetTypeTraits<AllocatorBlock>());

    // struct AllocatorNode | File: ../Container/Allocator.h
    engine->RegisterObjectType("AllocatorNode", sizeof(AllocatorNode), asOBJ_VALUE | asGetTypeTraits<AllocatorNode>());

    // class Animatable | File: ../Scene/Animatable.h
    engine->RegisterObjectType("Animatable", 0, asOBJ_REF);

    // class AnimatedModel | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectType("AnimatedModel", 0, asOBJ_REF);

    // class Animation | File: ../Graphics/Animation.h
    engine->RegisterObjectType("Animation", 0, asOBJ_REF);

    // struct AnimationControl | File: ../Graphics/AnimationController.h
    engine->RegisterObjectType("AnimationControl", 0, asOBJ_REF);

    // class AnimationController | File: ../Graphics/AnimationController.h
    engine->RegisterObjectType("AnimationController", 0, asOBJ_REF);

    // struct AnimationKeyFrame | File: ../Graphics/Animation.h
    engine->RegisterObjectType("AnimationKeyFrame", sizeof(AnimationKeyFrame), asOBJ_VALUE | asGetTypeTraits<AnimationKeyFrame>());

    // class AnimationState | File: ../Graphics/AnimationState.h
    engine->RegisterObjectType("AnimationState", 0, asOBJ_REF);

    // struct AnimationStateTrack | File: ../Graphics/AnimationState.h
    engine->RegisterObjectType("AnimationStateTrack", sizeof(AnimationStateTrack), asOBJ_VALUE | asGetTypeTraits<AnimationStateTrack>());

    // struct AnimationTrack | File: ../Graphics/Animation.h
    engine->RegisterObjectType("AnimationTrack", 0, asOBJ_REF);

    // struct AnimationTriggerPoint | File: ../Graphics/Animation.h
    engine->RegisterObjectType("AnimationTriggerPoint", sizeof(AnimationTriggerPoint), asOBJ_VALUE | asGetTypeTraits<AnimationTriggerPoint>());

    // class AreaAllocator | File: ../Math/AreaAllocator.h
    engine->RegisterObjectType("AreaAllocator", sizeof(AreaAllocator), asOBJ_VALUE | asGetTypeTraits<AreaAllocator>());

    // struct AsyncProgress | File: ../Scene/Scene.h
    engine->RegisterObjectType("AsyncProgress", sizeof(AsyncProgress), asOBJ_VALUE | asGetTypeTraits<AsyncProgress>());

    // class AttributeAccessor | File: ../Core/Attribute.h
    engine->RegisterObjectType("AttributeAccessor", 0, asOBJ_REF);

    // class AttributeAnimationInfo | File: ../Scene/Animatable.h
    engine->RegisterObjectType("AttributeAnimationInfo", 0, asOBJ_REF);

    // struct AttributeHandle | File: ../Core/Attribute.h
    // Not registered because have @nobind mark

    // struct AttributeInfo | File: ../Core/Attribute.h
    engine->RegisterObjectType("AttributeInfo", sizeof(AttributeInfo), asOBJ_VALUE | asGetTypeTraits<AttributeInfo>());

    // class Audio | File: ../Audio/Audio.h
    engine->RegisterObjectType("Audio", 0, asOBJ_REF);

    // class AutoProfileBlock | File: ../Core/Profiler.h
    // Not registered because have @nobind mark

    // struct BackgroundLoadItem | File: ../Resource/BackgroundLoader.h
    engine->RegisterObjectType("BackgroundLoadItem", sizeof(BackgroundLoadItem), asOBJ_VALUE | asGetTypeTraits<BackgroundLoadItem>());

    // class BackgroundLoader | File: ../Resource/BackgroundLoader.h
    // Not registered because have @nobind mark

    // struct Batch | File: ../Graphics/Batch.h
    engine->RegisterObjectType("Batch", sizeof(Batch), asOBJ_VALUE | asGetTypeTraits<Batch>());

    // struct BatchGroup | File: ../Graphics/Batch.h
    engine->RegisterObjectType("BatchGroup", sizeof(BatchGroup), asOBJ_VALUE | asGetTypeTraits<BatchGroup>());

    // struct BatchGroupKey | File: ../Graphics/Batch.h
    engine->RegisterObjectType("BatchGroupKey", sizeof(BatchGroupKey), asOBJ_VALUE | asGetTypeTraits<BatchGroupKey>());

    // struct BatchQueue | File: ../Graphics/Batch.h
    engine->RegisterObjectType("BatchQueue", sizeof(BatchQueue), asOBJ_VALUE | asGetTypeTraits<BatchQueue>());

    // struct BiasParameters | File: ../Graphics/Light.h
    engine->RegisterObjectType("BiasParameters", sizeof(BiasParameters), asOBJ_VALUE | asGetTypeTraits<BiasParameters>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // struct Billboard | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectType("Billboard", 0, asOBJ_REF);

    // class BillboardSet | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectType("BillboardSet", 0, asOBJ_REF);

    // struct Bone | File: ../Graphics/Skeleton.h
    engine->RegisterObjectType("Bone", 0, asOBJ_REF);

    // class BorderImage | File: ../UI/BorderImage.h
    engine->RegisterObjectType("BorderImage", 0, asOBJ_REF);

    // class BoundingBox | File: ../Math/BoundingBox.h
    engine->RegisterObjectType("BoundingBox", sizeof(BoundingBox), asOBJ_VALUE | asGetTypeTraits<BoundingBox>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // class BoxOctreeQuery | File: ../Graphics/OctreeQuery.h
    // Not registered because have @nobind mark

    // class BufferedSoundStream | File: ../Audio/BufferedSoundStream.h
    engine->RegisterObjectType("BufferedSoundStream", 0, asOBJ_REF);

    // class Button | File: ../UI/Button.h
    engine->RegisterObjectType("Button", 0, asOBJ_REF);

    // class Camera | File: ../Graphics/Camera.h
    engine->RegisterObjectType("Camera", 0, asOBJ_REF);

    // struct CascadeParameters | File: ../Graphics/Light.h
    engine->RegisterObjectType("CascadeParameters", sizeof(CascadeParameters), asOBJ_VALUE | asGetTypeTraits<CascadeParameters>() | asOBJ_POD);

    // struct CharLocation | File: ../UI/Text.h
    engine->RegisterObjectType("CharLocation", sizeof(CharLocation), asOBJ_VALUE | asGetTypeTraits<CharLocation>());

    // class CheckBox | File: ../UI/CheckBox.h
    engine->RegisterObjectType("CheckBox", 0, asOBJ_REF);

    // class Color | File: ../Math/Color.h
    engine->RegisterObjectType("Color", sizeof(Color), asOBJ_VALUE | asGetTypeTraits<Color>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // struct ColorFrame | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectType("ColorFrame", 0, asOBJ_REF);

    // class Component | File: ../Scene/Component.h
    engine->RegisterObjectType("Component", 0, asOBJ_REF);

    // struct ComponentReplicationState | File: ../Scene/ReplicationState.h
    engine->RegisterObjectType("ComponentReplicationState", sizeof(ComponentReplicationState), asOBJ_VALUE | asGetTypeTraits<ComponentReplicationState>());

    // struct CompressedLevel | File: ../Resource/Image.h
    engine->RegisterObjectType("CompressedLevel", sizeof(CompressedLevel), asOBJ_VALUE | asGetTypeTraits<CompressedLevel>());

    // class Condition | File: ../Core/Condition.h
    engine->RegisterObjectType("Condition", sizeof(Condition), asOBJ_VALUE | asGetTypeTraits<Condition>());

    // class Console | File: ../Engine/Console.h
    engine->RegisterObjectType("Console", 0, asOBJ_REF);

    // class ConstantBuffer | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectType("ConstantBuffer", 0, asOBJ_REF);

    // class Context | File: ../Core/Context.h
    engine->RegisterObjectType("Context", 0, asOBJ_REF);

    // class Controls | File: ../Input/Controls.h
    engine->RegisterObjectType("Controls", sizeof(Controls), asOBJ_VALUE | asGetTypeTraits<Controls>());

    // class Cursor | File: ../UI/Cursor.h
    engine->RegisterObjectType("Cursor", 0, asOBJ_REF);

    // struct CursorShapeInfo | File: ../UI/Cursor.h
    engine->RegisterObjectType("CursorShapeInfo", sizeof(CursorShapeInfo), asOBJ_VALUE | asGetTypeTraits<CursorShapeInfo>());

    // class CustomGeometry | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectType("CustomGeometry", 0, asOBJ_REF);

    // struct CustomGeometryVertex | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectType("CustomGeometryVertex", 0, asOBJ_REF);

    // class CustomVariantValue | File: ../Core/Variant.h
    // Not registered because have @nobind mark

    // class DebugHud | File: ../Engine/DebugHud.h
    engine->RegisterObjectType("DebugHud", 0, asOBJ_REF);

    // struct DebugLine | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectType("DebugLine", sizeof(DebugLine), asOBJ_VALUE | asGetTypeTraits<DebugLine>());

    // class DebugRenderer | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectType("DebugRenderer", 0, asOBJ_REF);

    // struct DebugTriangle | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectType("DebugTriangle", sizeof(DebugTriangle), asOBJ_VALUE | asGetTypeTraits<DebugTriangle>());

    // struct Decal | File: ../Graphics/DecalSet.h
    engine->RegisterObjectType("Decal", sizeof(Decal), asOBJ_VALUE | asGetTypeTraits<Decal>());

    // class DecalSet | File: ../Graphics/DecalSet.h
    engine->RegisterObjectType("DecalSet", 0, asOBJ_REF);

    // struct DecalVertex | File: ../Graphics/DecalSet.h
    engine->RegisterObjectType("DecalVertex", sizeof(DecalVertex), asOBJ_VALUE | asGetTypeTraits<DecalVertex>());

    // struct DepthValue | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectType("DepthValue", sizeof(DepthValue), asOBJ_VALUE | asGetTypeTraits<DepthValue>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);

    // class Deserializer | File: ../IO/Deserializer.h
    engine->RegisterObjectType("Deserializer", 0, asOBJ_REF);

    // struct DirtyBits | File: ../Scene/ReplicationState.h
    engine->RegisterObjectType("DirtyBits", sizeof(DirtyBits), asOBJ_VALUE | asGetTypeTraits<DirtyBits>());

    // class Drawable | File: ../Graphics/Drawable.h
    engine->RegisterObjectType("Drawable", 0, asOBJ_REF);

    // class DropDownList | File: ../UI/DropDownList.h
    engine->RegisterObjectType("DropDownList", 0, asOBJ_REF);

    // class Engine | File: ../Engine/Engine.h
    engine->RegisterObjectType("Engine", 0, asOBJ_REF);

    // class EventHandler | File: ../Core/Object.h
    // Not registered because value types can not be abstract

    // class EventHandler11Impl | File: ../Core/Object.h
    // Not registered because have @nobind mark

    // class EventProfiler | File: ../Core/EventProfiler.h
    engine->RegisterObjectType("EventProfiler", 0, asOBJ_REF);

    // class EventProfilerBlock | File: ../Core/EventProfiler.h
    // Not registered because have @nobind mark

    // class EventReceiverGroup | File: ../Core/Context.h
    engine->RegisterObjectType("EventReceiverGroup", 0, asOBJ_REF);

    // class File | File: ../IO/File.h
    engine->RegisterObjectType("File", 0, asOBJ_REF);

    // class FileSelector | File: ../UI/FileSelector.h
    engine->RegisterObjectType("FileSelector", 0, asOBJ_REF);

    // struct FileSelectorEntry | File: ../UI/FileSelector.h
    engine->RegisterObjectType("FileSelectorEntry", sizeof(FileSelectorEntry), asOBJ_VALUE | asGetTypeTraits<FileSelectorEntry>());

    // class FileSystem | File: ../IO/FileSystem.h
    engine->RegisterObjectType("FileSystem", 0, asOBJ_REF);

    // class FileWatcher | File: ../IO/FileWatcher.h
    engine->RegisterObjectType("FileWatcher", 0, asOBJ_REF);

    // struct FocusParameters | File: ../Graphics/Light.h
    engine->RegisterObjectType("FocusParameters", sizeof(FocusParameters), asOBJ_VALUE | asGetTypeTraits<FocusParameters>() | asOBJ_POD);

    // class Font | File: ../UI/Font.h
    engine->RegisterObjectType("Font", 0, asOBJ_REF);

    // class FontFace | File: ../UI/FontFace.h
    engine->RegisterObjectType("FontFace", 0, asOBJ_REF);

    // class FontFaceBitmap | File: ../UI/FontFaceBitmap.h
    engine->RegisterObjectType("FontFaceBitmap", 0, asOBJ_REF);

    // class FontFaceFreeType | File: ../UI/FontFaceFreeType.h
    engine->RegisterObjectType("FontFaceFreeType", 0, asOBJ_REF);

    // struct FontGlyph | File: ../UI/FontFace.h
    engine->RegisterObjectType("FontGlyph", sizeof(FontGlyph), asOBJ_VALUE | asGetTypeTraits<FontGlyph>());

    // struct FrameInfo | File: ../Graphics/Drawable.h
    engine->RegisterObjectType("FrameInfo", sizeof(FrameInfo), asOBJ_VALUE | asGetTypeTraits<FrameInfo>());

    // class Frustum | File: ../Math/Frustum.h
    engine->RegisterObjectType("Frustum", sizeof(Frustum), asOBJ_VALUE | asGetTypeTraits<Frustum>());

    // class FrustumOctreeQuery | File: ../Graphics/OctreeQuery.h
    // Not registered because have @nobind mark

    // class GPUObject | File: ../Graphics/GPUObject.h
    engine->RegisterObjectType("GPUObject", sizeof(GPUObject), asOBJ_VALUE | asGetTypeTraits<GPUObject>());

    // class Geometry | File: ../Graphics/Geometry.h
    engine->RegisterObjectType("Geometry", 0, asOBJ_REF);

    // struct GeometryDesc | File: ../Graphics/Model.h
    engine->RegisterObjectType("GeometryDesc", sizeof(GeometryDesc), asOBJ_VALUE | asGetTypeTraits<GeometryDesc>());

    // struct GlyphLocation | File: ../UI/Text.h
    // Not registered because have @nobind mark

    // class Graphics | File: ../Graphics/Graphics.h
    engine->RegisterObjectType("Graphics", 0, asOBJ_REF);

    // class HashBase | File: ../Container/HashBase.h
    engine->RegisterObjectType("HashBase", sizeof(HashBase), asOBJ_VALUE | asGetTypeTraits<HashBase>());

    // struct HashIteratorBase | File: ../Container/HashBase.h
    engine->RegisterObjectType("HashIteratorBase", sizeof(HashIteratorBase), asOBJ_VALUE | asGetTypeTraits<HashIteratorBase>());

    // struct HashNodeBase | File: ../Container/HashBase.h
    engine->RegisterObjectType("HashNodeBase", sizeof(HashNodeBase), asOBJ_VALUE | asGetTypeTraits<HashNodeBase>());

    // class HiresTimer | File: ../Core/Timer.h
    engine->RegisterObjectType("HiresTimer", sizeof(HiresTimer), asOBJ_VALUE | asGetTypeTraits<HiresTimer>());

    // class Image | File: ../Resource/Image.h
    engine->RegisterObjectType("Image", 0, asOBJ_REF);

    // class IndexBuffer | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectType("IndexBuffer", 0, asOBJ_REF);

    // struct IndexBufferDesc | File: ../Graphics/Model.h
    engine->RegisterObjectType("IndexBufferDesc", sizeof(IndexBufferDesc), asOBJ_VALUE | asGetTypeTraits<IndexBufferDesc>());

    // class Input | File: ../Input/Input.h
    engine->RegisterObjectType("Input", 0, asOBJ_REF);

    // struct InstanceData | File: ../Graphics/Batch.h
    engine->RegisterObjectType("InstanceData", sizeof(InstanceData), asOBJ_VALUE | asGetTypeTraits<InstanceData>());

    // class IntRect | File: ../Math/Rect.h
    engine->RegisterObjectType("IntRect", sizeof(IntRect), asOBJ_VALUE | asGetTypeTraits<IntRect>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);

    // class IntVector2 | File: ../Math/Vector2.h
    engine->RegisterObjectType("IntVector2", sizeof(IntVector2), asOBJ_VALUE | asGetTypeTraits<IntVector2>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);

    // class IntVector3 | File: ../Math/Vector3.h
    engine->RegisterObjectType("IntVector3", sizeof(IntVector3), asOBJ_VALUE | asGetTypeTraits<IntVector3>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);

    // class JSONFile | File: ../Resource/JSONFile.h
    engine->RegisterObjectType("JSONFile", 0, asOBJ_REF);

    // class JSONValue | File: ../Resource/JSONValue.h
    engine->RegisterObjectType("JSONValue", sizeof(JSONValue), asOBJ_VALUE | asGetTypeTraits<JSONValue>());

    // struct JoystickState | File: ../Input/Input.h
    engine->RegisterObjectType("JoystickState", 0, asOBJ_REF);

    // class Light | File: ../Graphics/Light.h
    engine->RegisterObjectType("Light", 0, asOBJ_REF);

    // struct LightBatchQueue | File: ../Graphics/Batch.h
    engine->RegisterObjectType("LightBatchQueue", sizeof(LightBatchQueue), asOBJ_VALUE | asGetTypeTraits<LightBatchQueue>());

    // struct LightQueryResult | File: ../Graphics/View.h
    engine->RegisterObjectType("LightQueryResult", sizeof(LightQueryResult), asOBJ_VALUE | asGetTypeTraits<LightQueryResult>());

    // class LineEdit | File: ../UI/LineEdit.h
    engine->RegisterObjectType("LineEdit", 0, asOBJ_REF);

    // struct LinkedListNode | File: ../Container/LinkedList.h
    engine->RegisterObjectType("LinkedListNode", sizeof(LinkedListNode), asOBJ_VALUE | asGetTypeTraits<LinkedListNode>());

    // class ListBase | File: ../Container/ListBase.h
    engine->RegisterObjectType("ListBase", sizeof(ListBase), asOBJ_VALUE | asGetTypeTraits<ListBase>());

    // struct ListIteratorBase | File: ../Container/ListBase.h
    engine->RegisterObjectType("ListIteratorBase", sizeof(ListIteratorBase), asOBJ_VALUE | asGetTypeTraits<ListIteratorBase>());

    // struct ListNodeBase | File: ../Container/ListBase.h
    engine->RegisterObjectType("ListNodeBase", sizeof(ListNodeBase), asOBJ_VALUE | asGetTypeTraits<ListNodeBase>());

    // class ListView | File: ../UI/ListView.h
    engine->RegisterObjectType("ListView", 0, asOBJ_REF);

    // class Localization | File: ../Resource/Localization.h
    engine->RegisterObjectType("Localization", 0, asOBJ_REF);

    // class Log | File: ../IO/Log.h
    engine->RegisterObjectType("Log", 0, asOBJ_REF);

    // class LogicComponent | File: ../Scene/LogicComponent.h
    engine->RegisterObjectType("LogicComponent", 0, asOBJ_REF);

    // class Material | File: ../Graphics/Material.h
    engine->RegisterObjectType("Material", 0, asOBJ_REF);

    // struct MaterialShaderParameter | File: ../Graphics/Material.h
    engine->RegisterObjectType("MaterialShaderParameter", sizeof(MaterialShaderParameter), asOBJ_VALUE | asGetTypeTraits<MaterialShaderParameter>());

    // class Matrix2 | File: ../Math/Matrix2.h
    engine->RegisterObjectType("Matrix2", sizeof(Matrix2), asOBJ_VALUE | asGetTypeTraits<Matrix2>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // class Matrix3 | File: ../Math/Matrix3.h
    engine->RegisterObjectType("Matrix3", sizeof(Matrix3), asOBJ_VALUE | asGetTypeTraits<Matrix3>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // class Matrix3x4 | File: ../Math/Matrix3x4.h
    engine->RegisterObjectType("Matrix3x4", sizeof(Matrix3x4), asOBJ_VALUE | asGetTypeTraits<Matrix3x4>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // class Matrix4 | File: ../Math/Matrix4.h
    engine->RegisterObjectType("Matrix4", sizeof(Matrix4), asOBJ_VALUE | asGetTypeTraits<Matrix4>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // class MemoryBuffer | File: ../IO/MemoryBuffer.h
    // Not registered because have @nobind mark

    // class Menu | File: ../UI/Menu.h
    engine->RegisterObjectType("Menu", 0, asOBJ_REF);

    // class MessageBox | File: ../UI/MessageBox.h
    engine->RegisterObjectType("MessageBox", 0, asOBJ_REF);

    // class Model | File: ../Graphics/Model.h
    engine->RegisterObjectType("Model", 0, asOBJ_REF);

    // struct ModelMorph | File: ../Graphics/Model.h
    engine->RegisterObjectType("ModelMorph", sizeof(ModelMorph), asOBJ_VALUE | asGetTypeTraits<ModelMorph>());

    // class Mutex | File: ../Core/Mutex.h
    engine->RegisterObjectType("Mutex", sizeof(Mutex), asOBJ_VALUE | asGetTypeTraits<Mutex>());

    // class MutexLock | File: ../Core/Mutex.h
    engine->RegisterObjectType("MutexLock", sizeof(MutexLock), asOBJ_VALUE | asGetTypeTraits<MutexLock>());

    // class NamedPipe | File: ../IO/NamedPipe.h
    engine->RegisterObjectType("NamedPipe", 0, asOBJ_REF);

    // struct NetworkState | File: ../Scene/ReplicationState.h
    engine->RegisterObjectType("NetworkState", sizeof(NetworkState), asOBJ_VALUE | asGetTypeTraits<NetworkState>());

    // class Node | File: ../Scene/Node.h
    engine->RegisterObjectType("Node", 0, asOBJ_REF);

    // struct NodeImpl | File: ../Scene/Node.h
    engine->RegisterObjectType("NodeImpl", sizeof(NodeImpl), asOBJ_VALUE | asGetTypeTraits<NodeImpl>());

    // struct NodeReplicationState | File: ../Scene/ReplicationState.h
    engine->RegisterObjectType("NodeReplicationState", sizeof(NodeReplicationState), asOBJ_VALUE | asGetTypeTraits<NodeReplicationState>());

    // class Object | File: ../Core/Object.h
    engine->RegisterObjectType("Object", 0, asOBJ_REF);

    // class ObjectAnimation | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectType("ObjectAnimation", 0, asOBJ_REF);

    // class ObjectFactory | File: ../Core/Object.h
    engine->RegisterObjectType("ObjectFactory", 0, asOBJ_REF);

    // struct OcclusionBatch | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectType("OcclusionBatch", sizeof(OcclusionBatch), asOBJ_VALUE | asGetTypeTraits<OcclusionBatch>());

    // class OcclusionBuffer | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectType("OcclusionBuffer", 0, asOBJ_REF);

    // struct OcclusionBufferData | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectType("OcclusionBufferData", sizeof(OcclusionBufferData), asOBJ_VALUE | asGetTypeTraits<OcclusionBufferData>());

    // class Octant | File: ../Graphics/Octree.h
    // Not registered because have @nobind mark

    // class Octree | File: ../Graphics/Octree.h
    engine->RegisterObjectType("Octree", 0, asOBJ_REF);

    // class OctreeQuery | File: ../Graphics/OctreeQuery.h
    // Not registered because value types can not be abstract

    // struct OctreeQueryResult | File: ../Graphics/OctreeQuery.h
    engine->RegisterObjectType("OctreeQueryResult", sizeof(OctreeQueryResult), asOBJ_VALUE | asGetTypeTraits<OctreeQueryResult>());

    // class OggVorbisSoundStream | File: ../Audio/OggVorbisSoundStream.h
    engine->RegisterObjectType("OggVorbisSoundStream", 0, asOBJ_REF);

    // struct PackageEntry | File: ../IO/PackageFile.h
    engine->RegisterObjectType("PackageEntry", sizeof(PackageEntry), asOBJ_VALUE | asGetTypeTraits<PackageEntry>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);

    // class PackageFile | File: ../IO/PackageFile.h
    engine->RegisterObjectType("PackageFile", 0, asOBJ_REF);

    // struct Particle | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectType("Particle", sizeof(Particle), asOBJ_VALUE | asGetTypeTraits<Particle>());

    // class ParticleEffect | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectType("ParticleEffect", 0, asOBJ_REF);

    // class ParticleEmitter | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectType("ParticleEmitter", 0, asOBJ_REF);

    // class Pass | File: ../Graphics/Technique.h
    engine->RegisterObjectType("Pass", 0, asOBJ_REF);

    // struct PerThreadSceneResult | File: ../Graphics/View.h
    engine->RegisterObjectType("PerThreadSceneResult", sizeof(PerThreadSceneResult), asOBJ_VALUE | asGetTypeTraits<PerThreadSceneResult>());

    // class Plane | File: ../Math/Plane.h
    engine->RegisterObjectType("Plane", sizeof(Plane), asOBJ_VALUE | asGetTypeTraits<Plane>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // class PointOctreeQuery | File: ../Graphics/OctreeQuery.h
    // Not registered because have @nobind mark

    // class Polyhedron | File: ../Math/Polyhedron.h
    engine->RegisterObjectType("Polyhedron", sizeof(Polyhedron), asOBJ_VALUE | asGetTypeTraits<Polyhedron>());

    // class Profiler | File: ../Core/Profiler.h
    engine->RegisterObjectType("Profiler", 0, asOBJ_REF);

    // class ProfilerBlock | File: ../Core/Profiler.h
    // Not registered because have @nobind mark

    // class ProgressBar | File: ../UI/ProgressBar.h
    engine->RegisterObjectType("ProgressBar", 0, asOBJ_REF);

    // class Quaternion | File: ../Math/Quaternion.h
    engine->RegisterObjectType("Quaternion", sizeof(Quaternion), asOBJ_VALUE | asGetTypeTraits<Quaternion>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // class Ray | File: ../Math/Ray.h
    engine->RegisterObjectType("Ray", sizeof(Ray), asOBJ_VALUE | asGetTypeTraits<Ray>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // class RayOctreeQuery | File: ../Graphics/OctreeQuery.h
    // Not registered because have @nobind mark

    // struct RayQueryResult | File: ../Graphics/OctreeQuery.h
    engine->RegisterObjectType("RayQueryResult", sizeof(RayQueryResult), asOBJ_VALUE | asGetTypeTraits<RayQueryResult>());

    // class Rect | File: ../Math/Rect.h
    engine->RegisterObjectType("Rect", sizeof(Rect), asOBJ_VALUE | asGetTypeTraits<Rect>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // struct RefCount | File: ../Container/RefCounted.h
    engine->RegisterObjectType("RefCount", sizeof(RefCount), asOBJ_VALUE | asGetTypeTraits<RefCount>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);

    // class RefCounted | File: ../Container/RefCounted.h
    engine->RegisterObjectType("RefCounted", 0, asOBJ_REF);

    // class RenderPath | File: ../Graphics/RenderPath.h
    engine->RegisterObjectType("RenderPath", 0, asOBJ_REF);

    // struct RenderPathCommand | File: ../Graphics/RenderPath.h
    engine->RegisterObjectType("RenderPathCommand", sizeof(RenderPathCommand), asOBJ_VALUE | asGetTypeTraits<RenderPathCommand>());

    // class RenderSurface | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectType("RenderSurface", 0, asOBJ_REF);

    // struct RenderTargetInfo | File: ../Graphics/RenderPath.h
    engine->RegisterObjectType("RenderTargetInfo", sizeof(RenderTargetInfo), asOBJ_VALUE | asGetTypeTraits<RenderTargetInfo>());

    // class Renderer | File: ../Graphics/Renderer.h
    engine->RegisterObjectType("Renderer", 0, asOBJ_REF);

    // struct ReplicationState | File: ../Scene/ReplicationState.h
    engine->RegisterObjectType("ReplicationState", sizeof(ReplicationState), asOBJ_VALUE | asGetTypeTraits<ReplicationState>());

    // class Resource | File: ../Resource/Resource.h
    engine->RegisterObjectType("Resource", 0, asOBJ_REF);

    // class ResourceCache | File: ../Resource/ResourceCache.h
    engine->RegisterObjectType("ResourceCache", 0, asOBJ_REF);

    // struct ResourceGroup | File: ../Resource/ResourceCache.h
    engine->RegisterObjectType("ResourceGroup", sizeof(ResourceGroup), asOBJ_VALUE | asGetTypeTraits<ResourceGroup>());

    // struct ResourceRef | File: ../Core/Variant.h
    engine->RegisterObjectType("ResourceRef", sizeof(ResourceRef), asOBJ_VALUE | asGetTypeTraits<ResourceRef>());

    // struct ResourceRefList | File: ../Core/Variant.h
    engine->RegisterObjectType("ResourceRefList", sizeof(ResourceRefList), asOBJ_VALUE | asGetTypeTraits<ResourceRefList>());

    // class ResourceRouter | File: ../Resource/ResourceCache.h
    // Not registered because have @nobind mark

    // class ResourceWithMetadata | File: ../Resource/Resource.h
    engine->RegisterObjectType("ResourceWithMetadata", 0, asOBJ_REF);

    // class RibbonTrail | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectType("RibbonTrail", 0, asOBJ_REF);

    // class Scene | File: ../Scene/Scene.h
    engine->RegisterObjectType("Scene", 0, asOBJ_REF);

    // struct ScenePassInfo | File: ../Graphics/View.h
    engine->RegisterObjectType("ScenePassInfo", sizeof(ScenePassInfo), asOBJ_VALUE | asGetTypeTraits<ScenePassInfo>());

    // struct SceneReplicationState | File: ../Scene/ReplicationState.h
    engine->RegisterObjectType("SceneReplicationState", sizeof(SceneReplicationState), asOBJ_VALUE | asGetTypeTraits<SceneReplicationState>());

    // class SceneResolver | File: ../Scene/SceneResolver.h
    engine->RegisterObjectType("SceneResolver", sizeof(SceneResolver), asOBJ_VALUE | asGetTypeTraits<SceneResolver>());

    // struct ScratchBuffer | File: ../Graphics/Graphics.h
    engine->RegisterObjectType("ScratchBuffer", sizeof(ScratchBuffer), asOBJ_VALUE | asGetTypeTraits<ScratchBuffer>());

    // struct ScreenModeParams | File: ../Graphics/Graphics.h
    engine->RegisterObjectType("ScreenModeParams", sizeof(ScreenModeParams), asOBJ_VALUE | asGetTypeTraits<ScreenModeParams>());

    // class ScrollBar | File: ../UI/ScrollBar.h
    engine->RegisterObjectType("ScrollBar", 0, asOBJ_REF);

    // class ScrollView | File: ../UI/ScrollView.h
    engine->RegisterObjectType("ScrollView", 0, asOBJ_REF);

    // class Serializable | File: ../Scene/Serializable.h
    engine->RegisterObjectType("Serializable", 0, asOBJ_REF);

    // class Serializer | File: ../IO/Serializer.h
    engine->RegisterObjectType("Serializer", 0, asOBJ_REF);

    // class Shader | File: ../Graphics/Shader.h
    engine->RegisterObjectType("Shader", 0, asOBJ_REF);

    // struct ShaderParameter | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectType("ShaderParameter", sizeof(ShaderParameter), asOBJ_VALUE | asGetTypeTraits<ShaderParameter>());

    // class ShaderParameterAnimationInfo | File: ../Graphics/Material.h
    engine->RegisterObjectType("ShaderParameterAnimationInfo", 0, asOBJ_REF);

    // class ShaderPrecache | File: ../Graphics/ShaderPrecache.h
    engine->RegisterObjectType("ShaderPrecache", 0, asOBJ_REF);

    // class ShaderVariation | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectType("ShaderVariation", 0, asOBJ_REF);

    // struct ShadowBatchQueue | File: ../Graphics/Batch.h
    engine->RegisterObjectType("ShadowBatchQueue", sizeof(ShadowBatchQueue), asOBJ_VALUE | asGetTypeTraits<ShadowBatchQueue>());

    // class Skeleton | File: ../Graphics/Skeleton.h
    engine->RegisterObjectType("Skeleton", 0, asOBJ_REF);

    // class Skybox | File: ../Graphics/Skybox.h
    engine->RegisterObjectType("Skybox", 0, asOBJ_REF);

    // class Slider | File: ../UI/Slider.h
    engine->RegisterObjectType("Slider", 0, asOBJ_REF);

    // class SmoothedTransform | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectType("SmoothedTransform", 0, asOBJ_REF);

    // class Sound | File: ../Audio/Sound.h
    engine->RegisterObjectType("Sound", 0, asOBJ_REF);

    // class SoundListener | File: ../Audio/SoundListener.h
    engine->RegisterObjectType("SoundListener", 0, asOBJ_REF);

    // class SoundSource | File: ../Audio/SoundSource.h
    engine->RegisterObjectType("SoundSource", 0, asOBJ_REF);

    // class SoundSource3D | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectType("SoundSource3D", 0, asOBJ_REF);

    // class SoundStream | File: ../Audio/SoundStream.h
    engine->RegisterObjectType("SoundStream", 0, asOBJ_REF);

    // struct SourceBatch | File: ../Graphics/Drawable.h
    engine->RegisterObjectType("SourceBatch", sizeof(SourceBatch), asOBJ_VALUE | asGetTypeTraits<SourceBatch>());

    // class Sphere | File: ../Math/Sphere.h
    engine->RegisterObjectType("Sphere", sizeof(Sphere), asOBJ_VALUE | asGetTypeTraits<Sphere>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // class SphereOctreeQuery | File: ../Graphics/OctreeQuery.h
    // Not registered because have @nobind mark

    // class Spline | File: ../Core/Spline.h
    engine->RegisterObjectType("Spline", sizeof(Spline), asOBJ_VALUE | asGetTypeTraits<Spline>());

    // class SplinePath | File: ../Scene/SplinePath.h
    engine->RegisterObjectType("SplinePath", 0, asOBJ_REF);

    // class Sprite | File: ../UI/Sprite.h
    engine->RegisterObjectType("Sprite", 0, asOBJ_REF);

    // class StaticModel | File: ../Graphics/StaticModel.h
    engine->RegisterObjectType("StaticModel", 0, asOBJ_REF);

    // struct StaticModelGeometryData | File: ../Graphics/StaticModel.h
    engine->RegisterObjectType("StaticModelGeometryData", sizeof(StaticModelGeometryData), asOBJ_VALUE | asGetTypeTraits<StaticModelGeometryData>());

    // class StaticModelGroup | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectType("StaticModelGroup", 0, asOBJ_REF);

    // struct StoredLogMessage | File: ../IO/Log.h
    engine->RegisterObjectType("StoredLogMessage", sizeof(StoredLogMessage), asOBJ_VALUE | asGetTypeTraits<StoredLogMessage>());

    // class String | File: ../Container/Str.h
    engine->RegisterObjectType("String", sizeof(String), asOBJ_VALUE | asGetTypeTraits<String>());

    // class StringHash | File: ../Math/StringHash.h
    engine->RegisterObjectType("StringHash", sizeof(StringHash), asOBJ_VALUE | asGetTypeTraits<StringHash>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);

    // class StringHashRegister | File: ../Core/StringHashRegister.h
    engine->RegisterObjectType("StringHashRegister", sizeof(StringHashRegister), asOBJ_VALUE | asGetTypeTraits<StringHashRegister>());

    // class Technique | File: ../Graphics/Technique.h
    engine->RegisterObjectType("Technique", 0, asOBJ_REF);

    // struct TechniqueEntry | File: ../Graphics/Material.h
    engine->RegisterObjectType("TechniqueEntry", sizeof(TechniqueEntry), asOBJ_VALUE | asGetTypeTraits<TechniqueEntry>());

    // class Terrain | File: ../Graphics/Terrain.h
    engine->RegisterObjectType("Terrain", 0, asOBJ_REF);

    // class TerrainPatch | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectType("TerrainPatch", 0, asOBJ_REF);

    // class Text | File: ../UI/Text.h
    engine->RegisterObjectType("Text", 0, asOBJ_REF);

    // class Text3D | File: ../UI/Text3D.h
    engine->RegisterObjectType("Text3D", 0, asOBJ_REF);

    // class Texture | File: ../Graphics/Texture.h
    engine->RegisterObjectType("Texture", 0, asOBJ_REF);

    // class Texture2D | File: ../Graphics/Texture2D.h
    engine->RegisterObjectType("Texture2D", 0, asOBJ_REF);

    // class Texture2DArray | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectType("Texture2DArray", 0, asOBJ_REF);

    // class Texture3D | File: ../Graphics/Texture3D.h
    engine->RegisterObjectType("Texture3D", 0, asOBJ_REF);

    // class TextureCube | File: ../Graphics/TextureCube.h
    engine->RegisterObjectType("TextureCube", 0, asOBJ_REF);

    // struct TextureFrame | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectType("TextureFrame", 0, asOBJ_REF);

    // class Thread | File: ../Core/Thread.h
    // Not registered because value types can not be abstract

    // class Time | File: ../Core/Timer.h
    engine->RegisterObjectType("Time", 0, asOBJ_REF);

    // class Timer | File: ../Core/Timer.h
    engine->RegisterObjectType("Timer", sizeof(Timer), asOBJ_VALUE | asGetTypeTraits<Timer>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);

    // class ToolTip | File: ../UI/ToolTip.h
    engine->RegisterObjectType("ToolTip", 0, asOBJ_REF);

    // struct TouchState | File: ../Input/Input.h
    engine->RegisterObjectType("TouchState", 0, asOBJ_REF);

    // struct TrailPoint | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectType("TrailPoint", sizeof(TrailPoint), asOBJ_VALUE | asGetTypeTraits<TrailPoint>());

    // class TypeInfo | File: ../Core/Object.h
    // Not registered because have @nobind mark

    // class UI | File: ../UI/UI.h
    engine->RegisterObjectType("UI", 0, asOBJ_REF);

    // class UIBatch | File: ../UI/UIBatch.h
    engine->RegisterObjectType("UIBatch", sizeof(UIBatch), asOBJ_VALUE | asGetTypeTraits<UIBatch>());

    // class UIComponent | File: ../UI/UIComponent.h
    engine->RegisterObjectType("UIComponent", 0, asOBJ_REF);

    // class UIElement | File: ../UI/UIElement.h
    engine->RegisterObjectType("UIElement", 0, asOBJ_REF);

    // class UISelectable | File: ../UI/UISelectable.h
    engine->RegisterObjectType("UISelectable", 0, asOBJ_REF);

    // class UnknownComponent | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectType("UnknownComponent", 0, asOBJ_REF);

    // struct VAnimEventFrame | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectType("VAnimEventFrame", sizeof(VAnimEventFrame), asOBJ_VALUE | asGetTypeTraits<VAnimEventFrame>());

    // struct VAnimKeyFrame | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectType("VAnimKeyFrame", sizeof(VAnimKeyFrame), asOBJ_VALUE | asGetTypeTraits<VAnimKeyFrame>());

    // class ValueAnimation | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectType("ValueAnimation", 0, asOBJ_REF);

    // class ValueAnimationInfo | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectType("ValueAnimationInfo", 0, asOBJ_REF);

    // class Variant | File: ../Core/Variant.h
    engine->RegisterObjectType("Variant", sizeof(Variant), asOBJ_VALUE | asGetTypeTraits<Variant>());

    // class Vector2 | File: ../Math/Vector2.h
    engine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE | asGetTypeTraits<Vector2>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // class Vector3 | File: ../Math/Vector3.h
    engine->RegisterObjectType("Vector3", sizeof(Vector3), asOBJ_VALUE | asGetTypeTraits<Vector3>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // class Vector4 | File: ../Math/Vector4.h
    engine->RegisterObjectType("Vector4", sizeof(Vector4), asOBJ_VALUE | asGetTypeTraits<Vector4>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // class VectorBase | File: ../Container/VectorBase.h
    engine->RegisterObjectType("VectorBase", sizeof(VectorBase), asOBJ_VALUE | asGetTypeTraits<VectorBase>());

    // class VectorBuffer | File: ../IO/VectorBuffer.h
    engine->RegisterObjectType("VectorBuffer", sizeof(VectorBuffer), asOBJ_VALUE | asGetTypeTraits<VectorBuffer>());

    // class VertexBuffer | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectType("VertexBuffer", 0, asOBJ_REF);

    // struct VertexBufferDesc | File: ../Graphics/Model.h
    engine->RegisterObjectType("VertexBufferDesc", sizeof(VertexBufferDesc), asOBJ_VALUE | asGetTypeTraits<VertexBufferDesc>());

    // struct VertexBufferMorph | File: ../Graphics/Model.h
    engine->RegisterObjectType("VertexBufferMorph", sizeof(VertexBufferMorph), asOBJ_VALUE | asGetTypeTraits<VertexBufferMorph>());

    // struct VertexElement | File: ../Graphics/GraphicsDefs.h
    engine->RegisterObjectType("VertexElement", sizeof(VertexElement), asOBJ_VALUE | asGetTypeTraits<VertexElement>());

    // class View | File: ../Graphics/View.h
    engine->RegisterObjectType("View", 0, asOBJ_REF);

    // class View3D | File: ../UI/View3D.h
    engine->RegisterObjectType("View3D", 0, asOBJ_REF);

    // class Viewport | File: ../Graphics/Viewport.h
    engine->RegisterObjectType("Viewport", 0, asOBJ_REF);

    // class WString | File: ../Container/Str.h
    // Not registered because have @nobind mark

    // class Window | File: ../UI/Window.h
    engine->RegisterObjectType("Window", 0, asOBJ_REF);

    // struct WindowModeParams | File: ../Graphics/Graphics.h
    engine->RegisterObjectType("WindowModeParams", sizeof(WindowModeParams), asOBJ_VALUE | asGetTypeTraits<WindowModeParams>());

    // struct WorkItem | File: ../Core/WorkQueue.h
    // Not registered because have @nobind mark

    // class WorkQueue | File: ../Core/WorkQueue.h
    engine->RegisterObjectType("WorkQueue", 0, asOBJ_REF);

    // class XMLElement | File: ../Resource/XMLElement.h
    engine->RegisterObjectType("XMLElement", sizeof(XMLElement), asOBJ_VALUE | asGetTypeTraits<XMLElement>());

    // class XMLFile | File: ../Resource/XMLFile.h
    engine->RegisterObjectType("XMLFile", 0, asOBJ_REF);

    // class XPathQuery | File: ../Resource/XMLElement.h
    engine->RegisterObjectType("XPathQuery", sizeof(XPathQuery), asOBJ_VALUE | asGetTypeTraits<XPathQuery>());

    // class XPathResultSet | File: ../Resource/XMLElement.h
    engine->RegisterObjectType("XPathResultSet", sizeof(XPathResultSet), asOBJ_VALUE | asGetTypeTraits<XPathResultSet>());

    // class Zone | File: ../Graphics/Zone.h
    engine->RegisterObjectType("Zone", 0, asOBJ_REF);

#ifdef URHO3D_DATABASE
    // class Database | File: ../Database/Database.h
    engine->RegisterObjectType("Database", 0, asOBJ_REF);
#endif

#ifdef URHO3D_IK
    // class IKConstraint | File: ../IK/IKConstraint.h
    engine->RegisterObjectType("IKConstraint", 0, asOBJ_REF);

    // class IKEffector | File: ../IK/IKEffector.h
    engine->RegisterObjectType("IKEffector", 0, asOBJ_REF);

    // class IKSolver | File: ../IK/IKSolver.h
    engine->RegisterObjectType("IKSolver", 0, asOBJ_REF);
#endif

#ifdef URHO3D_NAVIGATION
    // class CrowdAgent | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectType("CrowdAgent", 0, asOBJ_REF);

    // class CrowdManager | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectType("CrowdManager", 0, asOBJ_REF);

    // struct CrowdObstacleAvoidanceParams | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectType("CrowdObstacleAvoidanceParams", sizeof(CrowdObstacleAvoidanceParams), asOBJ_VALUE | asGetTypeTraits<CrowdObstacleAvoidanceParams>() | asOBJ_POD);

    // struct DynamicNavBuildData | File: ../Navigation/NavBuildData.h
    // Not registered because have @nobind mark

    // class DynamicNavigationMesh | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectType("DynamicNavigationMesh", 0, asOBJ_REF);

    // class NavArea | File: ../Navigation/NavArea.h
    engine->RegisterObjectType("NavArea", 0, asOBJ_REF);

    // struct NavAreaStub | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectType("NavAreaStub", sizeof(NavAreaStub), asOBJ_VALUE | asGetTypeTraits<NavAreaStub>());

    // struct NavBuildData | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectType("NavBuildData", sizeof(NavBuildData), asOBJ_VALUE | asGetTypeTraits<NavBuildData>());

    // class Navigable | File: ../Navigation/Navigable.h
    engine->RegisterObjectType("Navigable", 0, asOBJ_REF);

    // struct NavigationGeometryInfo | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectType("NavigationGeometryInfo", sizeof(NavigationGeometryInfo), asOBJ_VALUE | asGetTypeTraits<NavigationGeometryInfo>());

    // class NavigationMesh | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectType("NavigationMesh", 0, asOBJ_REF);

    // struct NavigationPathPoint | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectType("NavigationPathPoint", sizeof(NavigationPathPoint), asOBJ_VALUE | asGetTypeTraits<NavigationPathPoint>());

    // class Obstacle | File: ../Navigation/Obstacle.h
    engine->RegisterObjectType("Obstacle", 0, asOBJ_REF);

    // class OffMeshConnection | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectType("OffMeshConnection", 0, asOBJ_REF);

    // struct SimpleNavBuildData | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectType("SimpleNavBuildData", sizeof(SimpleNavBuildData), asOBJ_VALUE | asGetTypeTraits<SimpleNavBuildData>());
#endif

#ifdef URHO3D_NETWORK
    // class Connection | File: ../Network/Connection.h
    engine->RegisterObjectType("Connection", 0, asOBJ_REF);

    // class HttpRequest | File: ../Network/HttpRequest.h
    engine->RegisterObjectType("HttpRequest", 0, asOBJ_REF);

    // class Network | File: ../Network/Network.h
    engine->RegisterObjectType("Network", 0, asOBJ_REF);

    // class NetworkPriority | File: ../Network/NetworkPriority.h
    engine->RegisterObjectType("NetworkPriority", 0, asOBJ_REF);

    // struct PackageDownload | File: ../Network/Connection.h
    engine->RegisterObjectType("PackageDownload", sizeof(PackageDownload), asOBJ_VALUE | asGetTypeTraits<PackageDownload>());

    // struct PackageUpload | File: ../Network/Connection.h
    engine->RegisterObjectType("PackageUpload", sizeof(PackageUpload), asOBJ_VALUE | asGetTypeTraits<PackageUpload>());

    // struct RemoteEvent | File: ../Network/Connection.h
    engine->RegisterObjectType("RemoteEvent", sizeof(RemoteEvent), asOBJ_VALUE | asGetTypeTraits<RemoteEvent>());
#endif

#ifdef URHO3D_PHYSICS
    // struct CollisionGeometryData | File: ../Physics/CollisionShape.h
    engine->RegisterObjectType("CollisionGeometryData", 0, asOBJ_REF);

    // class CollisionShape | File: ../Physics/CollisionShape.h
    engine->RegisterObjectType("CollisionShape", 0, asOBJ_REF);

    // class Constraint | File: ../Physics/Constraint.h
    engine->RegisterObjectType("Constraint", 0, asOBJ_REF);

    // struct ConvexData | File: ../Physics/CollisionShape.h
    engine->RegisterObjectType("ConvexData", 0, asOBJ_REF);

    // struct DelayedWorldTransform | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectType("DelayedWorldTransform", sizeof(DelayedWorldTransform), asOBJ_VALUE | asGetTypeTraits<DelayedWorldTransform>());

    // struct GImpactMeshData | File: ../Physics/CollisionShape.h
    engine->RegisterObjectType("GImpactMeshData", 0, asOBJ_REF);

    // struct HeightfieldData | File: ../Physics/CollisionShape.h
    engine->RegisterObjectType("HeightfieldData", 0, asOBJ_REF);

    // struct ManifoldPair | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectType("ManifoldPair", sizeof(ManifoldPair), asOBJ_VALUE | asGetTypeTraits<ManifoldPair>());

    // struct PhysicsRaycastResult | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectType("PhysicsRaycastResult", sizeof(PhysicsRaycastResult), asOBJ_VALUE | asGetTypeTraits<PhysicsRaycastResult>());

    // class PhysicsWorld | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectType("PhysicsWorld", 0, asOBJ_REF);

    // struct PhysicsWorldConfig | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectType("PhysicsWorldConfig", sizeof(PhysicsWorldConfig), asOBJ_VALUE | asGetTypeTraits<PhysicsWorldConfig>());

    // class RaycastVehicle | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectType("RaycastVehicle", 0, asOBJ_REF);

    // class RigidBody | File: ../Physics/RigidBody.h
    engine->RegisterObjectType("RigidBody", 0, asOBJ_REF);

    // struct TriangleMeshData | File: ../Physics/CollisionShape.h
    engine->RegisterObjectType("TriangleMeshData", 0, asOBJ_REF);
#endif

#ifdef URHO3D_URHO2D
    // class AnimatedSprite2D | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectType("AnimatedSprite2D", 0, asOBJ_REF);

    // class AnimationSet2D | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectType("AnimationSet2D", 0, asOBJ_REF);

    // class CollisionBox2D | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectType("CollisionBox2D", 0, asOBJ_REF);

    // class CollisionChain2D | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectType("CollisionChain2D", 0, asOBJ_REF);

    // class CollisionCircle2D | File: ../Urho2D/CollisionCircle2D.h
    engine->RegisterObjectType("CollisionCircle2D", 0, asOBJ_REF);

    // class CollisionEdge2D | File: ../Urho2D/CollisionEdge2D.h
    engine->RegisterObjectType("CollisionEdge2D", 0, asOBJ_REF);

    // class CollisionPolygon2D | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectType("CollisionPolygon2D", 0, asOBJ_REF);

    // class CollisionShape2D | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectType("CollisionShape2D", 0, asOBJ_REF);

    // class Constraint2D | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectType("Constraint2D", 0, asOBJ_REF);

    // class ConstraintDistance2D | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectType("ConstraintDistance2D", 0, asOBJ_REF);

    // class ConstraintFriction2D | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectType("ConstraintFriction2D", 0, asOBJ_REF);

    // class ConstraintGear2D | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectType("ConstraintGear2D", 0, asOBJ_REF);

    // class ConstraintMotor2D | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectType("ConstraintMotor2D", 0, asOBJ_REF);

    // class ConstraintMouse2D | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectType("ConstraintMouse2D", 0, asOBJ_REF);

    // class ConstraintPrismatic2D | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectType("ConstraintPrismatic2D", 0, asOBJ_REF);

    // class ConstraintPulley2D | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectType("ConstraintPulley2D", 0, asOBJ_REF);

    // class ConstraintRevolute2D | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectType("ConstraintRevolute2D", 0, asOBJ_REF);

    // class ConstraintRope2D | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectType("ConstraintRope2D", 0, asOBJ_REF);

    // class ConstraintWeld2D | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectType("ConstraintWeld2D", 0, asOBJ_REF);

    // class ConstraintWheel2D | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectType("ConstraintWheel2D", 0, asOBJ_REF);

    // struct DelayedWorldTransform2D | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectType("DelayedWorldTransform2D", sizeof(DelayedWorldTransform2D), asOBJ_VALUE | asGetTypeTraits<DelayedWorldTransform2D>());

    // class Drawable2D | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectType("Drawable2D", 0, asOBJ_REF);

    // struct Particle2D | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectType("Particle2D", sizeof(Particle2D), asOBJ_VALUE | asGetTypeTraits<Particle2D>());

    // class ParticleEffect2D | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectType("ParticleEffect2D", 0, asOBJ_REF);

    // class ParticleEmitter2D | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectType("ParticleEmitter2D", 0, asOBJ_REF);

    // struct PhysicsRaycastResult2D | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectType("PhysicsRaycastResult2D", sizeof(PhysicsRaycastResult2D), asOBJ_VALUE | asGetTypeTraits<PhysicsRaycastResult2D>());

    // class PhysicsWorld2D | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectType("PhysicsWorld2D", 0, asOBJ_REF);

    // class PropertySet2D | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectType("PropertySet2D", 0, asOBJ_REF);

    // class Renderer2D | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectType("Renderer2D", 0, asOBJ_REF);

    // class RigidBody2D | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectType("RigidBody2D", 0, asOBJ_REF);

    // struct SourceBatch2D | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectType("SourceBatch2D", sizeof(SourceBatch2D), asOBJ_VALUE | asGetTypeTraits<SourceBatch2D>());

    // class Sprite2D | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectType("Sprite2D", 0, asOBJ_REF);

    // class SpriteSheet2D | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectType("SpriteSheet2D", 0, asOBJ_REF);

    // class StaticSprite2D | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectType("StaticSprite2D", 0, asOBJ_REF);

    // class StretchableSprite2D | File: ../Urho2D/StretchableSprite2D.h
    engine->RegisterObjectType("StretchableSprite2D", 0, asOBJ_REF);

    // class Tile2D | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectType("Tile2D", 0, asOBJ_REF);

    // class TileMap2D | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectType("TileMap2D", 0, asOBJ_REF);

    // struct TileMapInfo2D | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectType("TileMapInfo2D", 0, asOBJ_REF);

    // class TileMapLayer2D | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectType("TileMapLayer2D", 0, asOBJ_REF);

    // class TileMapObject2D | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectType("TileMapObject2D", 0, asOBJ_REF);

    // class TmxFile2D | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectType("TmxFile2D", 0, asOBJ_REF);

    // class TmxImageLayer2D | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectType("TmxImageLayer2D", 0, asOBJ_REF);

    // class TmxLayer2D | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectType("TmxLayer2D", 0, asOBJ_REF);

    // class TmxObjectGroup2D | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectType("TmxObjectGroup2D", 0, asOBJ_REF);

    // class TmxTileLayer2D | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectType("TmxTileLayer2D", 0, asOBJ_REF);

    // struct Vertex2D | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectType("Vertex2D", sizeof(Vertex2D), asOBJ_VALUE | asGetTypeTraits<Vertex2D>());

    // struct ViewBatchInfo2D | File: ../Urho2D/Renderer2D.h
    // Not registered because have @nobind mark
#endif
}

}
