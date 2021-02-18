// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// class AbstractFile | File: ../IO/AbstractFile.h
void CollectMembers_AbstractFile(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Deserializer(methods);
    CollectMembers_Serializer(methods);
}

// class AllContentOctreeQuery | File: ../Graphics/OctreeQuery.h
void CollectMembers_AllContentOctreeQuery(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct AllocatorBlock | File: ../Container/Allocator.h
void CollectMembers_AllocatorBlock(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct AllocatorNode | File: ../Container/Allocator.h
void CollectMembers_AllocatorNode(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Animatable | File: ../Scene/Animatable.h
void CollectMembers_Animatable(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Serializable(methods);
}

// class AnimatedModel | File: ../Graphics/AnimatedModel.h
void CollectMembers_AnimatedModel(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_StaticModel(methods);
}

// class Animation | File: ../Graphics/Animation.h
void CollectMembers_Animation(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_ResourceWithMetadata(methods);
}

// struct AnimationControl | File: ../Graphics/AnimationController.h
void CollectMembers_AnimationControl(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class AnimationController | File: ../Graphics/AnimationController.h
void CollectMembers_AnimationController(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct AnimationKeyFrame | File: ../Graphics/Animation.h
void CollectMembers_AnimationKeyFrame(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class AnimationState | File: ../Graphics/AnimationState.h
void CollectMembers_AnimationState(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// struct AnimationStateTrack | File: ../Graphics/AnimationState.h
void CollectMembers_AnimationStateTrack(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct AnimationTrack | File: ../Graphics/Animation.h
void CollectMembers_AnimationTrack(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct AnimationTriggerPoint | File: ../Graphics/Animation.h
void CollectMembers_AnimationTriggerPoint(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class AreaAllocator | File: ../Math/AreaAllocator.h
void CollectMembers_AreaAllocator(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct AsyncProgress | File: ../Scene/Scene.h
void CollectMembers_AsyncProgress(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class AttributeAccessor | File: ../Core/Attribute.h
void CollectMembers_AttributeAccessor(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// class AttributeAnimationInfo | File: ../Scene/Animatable.h
void CollectMembers_AttributeAnimationInfo(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_ValueAnimationInfo(methods);
}

// struct AttributeHandle | File: ../Core/Attribute.h
void CollectMembers_AttributeHandle(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct AttributeInfo | File: ../Core/Attribute.h
void CollectMembers_AttributeInfo(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Audio | File: ../Audio/Audio.h
void CollectMembers_Audio(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class AutoProfileBlock | File: ../Core/Profiler.h
void CollectMembers_AutoProfileBlock(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct BackgroundLoadItem | File: ../Resource/BackgroundLoader.h
void CollectMembers_BackgroundLoadItem(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class BackgroundLoader | File: ../Resource/BackgroundLoader.h
void CollectMembers_BackgroundLoader(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct Batch | File: ../Graphics/Batch.h
void CollectMembers_Batch(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct BatchGroup | File: ../Graphics/Batch.h
void CollectMembers_BatchGroup(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Batch(methods);
}

// struct BatchGroupKey | File: ../Graphics/Batch.h
void CollectMembers_BatchGroupKey(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct BatchQueue | File: ../Graphics/Batch.h
void CollectMembers_BatchQueue(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct BiasParameters | File: ../Graphics/Light.h
void CollectMembers_BiasParameters(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct Billboard | File: ../Graphics/BillboardSet.h
void CollectMembers_Billboard(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class BillboardSet | File: ../Graphics/BillboardSet.h
void CollectMembers_BillboardSet(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Drawable(methods);
}

// struct Bone | File: ../Graphics/Skeleton.h
void CollectMembers_Bone(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class BorderImage | File: ../UI/BorderImage.h
void CollectMembers_BorderImage(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_UIElement(methods);
}

// class BoundingBox | File: ../Math/BoundingBox.h
void CollectMembers_BoundingBox(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class BoxOctreeQuery | File: ../Graphics/OctreeQuery.h
void CollectMembers_BoxOctreeQuery(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class BufferedSoundStream | File: ../Audio/BufferedSoundStream.h
void CollectMembers_BufferedSoundStream(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_SoundStream(methods);
}

// class Button | File: ../UI/Button.h
void CollectMembers_Button(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_BorderImage(methods);
}

// class Camera | File: ../Graphics/Camera.h
void CollectMembers_Camera(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct CascadeParameters | File: ../Graphics/Light.h
void CollectMembers_CascadeParameters(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct CharLocation | File: ../UI/Text.h
void CollectMembers_CharLocation(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class CheckBox | File: ../UI/CheckBox.h
void CollectMembers_CheckBox(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_BorderImage(methods);
}

// class Color | File: ../Math/Color.h
void CollectMembers_Color(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct ColorFrame | File: ../Graphics/ParticleEffect.h
void CollectMembers_ColorFrame(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Component | File: ../Scene/Component.h
void CollectMembers_Component(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Animatable(methods);
}

// struct ComponentReplicationState | File: ../Scene/ReplicationState.h
void CollectMembers_ComponentReplicationState(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_ReplicationState(methods);
}

// struct CompressedLevel | File: ../Resource/Image.h
void CollectMembers_CompressedLevel(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Condition | File: ../Core/Condition.h
void CollectMembers_Condition(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Console | File: ../Engine/Console.h
void CollectMembers_Console(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class ConstantBuffer | File: ../Graphics/ConstantBuffer.h
void CollectMembers_ConstantBuffer(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
    CollectMembers_GPUObject(methods);
}

// class Context | File: ../Core/Context.h
void CollectMembers_Context(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// class Controls | File: ../Input/Controls.h
void CollectMembers_Controls(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Cursor | File: ../UI/Cursor.h
void CollectMembers_Cursor(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_BorderImage(methods);
}

// struct CursorShapeInfo | File: ../UI/Cursor.h
void CollectMembers_CursorShapeInfo(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class CustomGeometry | File: ../Graphics/CustomGeometry.h
void CollectMembers_CustomGeometry(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Drawable(methods);
}

// struct CustomGeometryVertex | File: ../Graphics/CustomGeometry.h
void CollectMembers_CustomGeometryVertex(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class CustomVariantValue | File: ../Core/Variant.h
void CollectMembers_CustomVariantValue(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class DebugHud | File: ../Engine/DebugHud.h
void CollectMembers_DebugHud(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// struct DebugLine | File: ../Graphics/DebugRenderer.h
void CollectMembers_DebugLine(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class DebugRenderer | File: ../Graphics/DebugRenderer.h
void CollectMembers_DebugRenderer(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct DebugTriangle | File: ../Graphics/DebugRenderer.h
void CollectMembers_DebugTriangle(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct Decal | File: ../Graphics/DecalSet.h
void CollectMembers_Decal(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class DecalSet | File: ../Graphics/DecalSet.h
void CollectMembers_DecalSet(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Drawable(methods);
}

// struct DecalVertex | File: ../Graphics/DecalSet.h
void CollectMembers_DecalVertex(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct DepthValue | File: ../Graphics/OcclusionBuffer.h
void CollectMembers_DepthValue(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Deserializer | File: ../IO/Deserializer.h
void CollectMembers_Deserializer(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct DirtyBits | File: ../Scene/ReplicationState.h
void CollectMembers_DirtyBits(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Drawable | File: ../Graphics/Drawable.h
void CollectMembers_Drawable(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class DropDownList | File: ../UI/DropDownList.h
void CollectMembers_DropDownList(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Menu(methods);
}

// class Engine | File: ../Engine/Engine.h
void CollectMembers_Engine(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class EventHandler | File: ../Core/Object.h
void CollectMembers_EventHandler(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class EventHandler11Impl | File: ../Core/Object.h
void CollectMembers_EventHandler11Impl(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class EventProfiler | File: ../Core/EventProfiler.h
void CollectMembers_EventProfiler(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Profiler(methods);
}

// class EventProfilerBlock | File: ../Core/EventProfiler.h
void CollectMembers_EventProfilerBlock(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class EventReceiverGroup | File: ../Core/Context.h
void CollectMembers_EventReceiverGroup(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// class File | File: ../IO/File.h
void CollectMembers_File(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
    CollectMembers_AbstractFile(methods);
}

// class FileSelector | File: ../UI/FileSelector.h
void CollectMembers_FileSelector(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// struct FileSelectorEntry | File: ../UI/FileSelector.h
void CollectMembers_FileSelectorEntry(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class FileSystem | File: ../IO/FileSystem.h
void CollectMembers_FileSystem(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class FileWatcher | File: ../IO/FileWatcher.h
void CollectMembers_FileWatcher(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
    CollectMembers_Thread(methods);
}

// struct FocusParameters | File: ../Graphics/Light.h
void CollectMembers_FocusParameters(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Font | File: ../UI/Font.h
void CollectMembers_Font(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// class FontFace | File: ../UI/FontFace.h
void CollectMembers_FontFace(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// class FontFaceBitmap | File: ../UI/FontFaceBitmap.h
void CollectMembers_FontFaceBitmap(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_FontFace(methods);
}

// class FontFaceFreeType | File: ../UI/FontFaceFreeType.h
void CollectMembers_FontFaceFreeType(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_FontFace(methods);
}

// struct FontGlyph | File: ../UI/FontFace.h
void CollectMembers_FontGlyph(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct FrameInfo | File: ../Graphics/Drawable.h
void CollectMembers_FrameInfo(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Frustum | File: ../Math/Frustum.h
void CollectMembers_Frustum(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class FrustumOctreeQuery | File: ../Graphics/OctreeQuery.h
void CollectMembers_FrustumOctreeQuery(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class GPUObject | File: ../Graphics/GPUObject.h
void CollectMembers_GPUObject(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Geometry | File: ../Graphics/Geometry.h
void CollectMembers_Geometry(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// struct GeometryDesc | File: ../Graphics/Model.h
void CollectMembers_GeometryDesc(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct GlyphLocation | File: ../UI/Text.h
void CollectMembers_GlyphLocation(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Graphics | File: ../Graphics/Graphics.h
void CollectMembers_Graphics(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class HashBase | File: ../Container/HashBase.h
void CollectMembers_HashBase(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct HashIteratorBase | File: ../Container/HashBase.h
void CollectMembers_HashIteratorBase(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct HashNodeBase | File: ../Container/HashBase.h
void CollectMembers_HashNodeBase(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class HiresTimer | File: ../Core/Timer.h
void CollectMembers_HiresTimer(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Image | File: ../Resource/Image.h
void CollectMembers_Image(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// class IndexBuffer | File: ../Graphics/IndexBuffer.h
void CollectMembers_IndexBuffer(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
    CollectMembers_GPUObject(methods);
}

// struct IndexBufferDesc | File: ../Graphics/Model.h
void CollectMembers_IndexBufferDesc(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Input | File: ../Input/Input.h
void CollectMembers_Input(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// struct InstanceData | File: ../Graphics/Batch.h
void CollectMembers_InstanceData(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class IntRect | File: ../Math/Rect.h
void CollectMembers_IntRect(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class IntVector2 | File: ../Math/Vector2.h
void CollectMembers_IntVector2(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class IntVector3 | File: ../Math/Vector3.h
void CollectMembers_IntVector3(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class JSONFile | File: ../Resource/JSONFile.h
void CollectMembers_JSONFile(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// class JSONValue | File: ../Resource/JSONValue.h
void CollectMembers_JSONValue(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct JoystickState | File: ../Input/Input.h
void CollectMembers_JoystickState(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Light | File: ../Graphics/Light.h
void CollectMembers_Light(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Drawable(methods);
}

// struct LightBatchQueue | File: ../Graphics/Batch.h
void CollectMembers_LightBatchQueue(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct LightQueryResult | File: ../Graphics/View.h
void CollectMembers_LightQueryResult(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class LineEdit | File: ../UI/LineEdit.h
void CollectMembers_LineEdit(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_BorderImage(methods);
}

// struct LinkedListNode | File: ../Container/LinkedList.h
void CollectMembers_LinkedListNode(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class ListBase | File: ../Container/ListBase.h
void CollectMembers_ListBase(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct ListIteratorBase | File: ../Container/ListBase.h
void CollectMembers_ListIteratorBase(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct ListNodeBase | File: ../Container/ListBase.h
void CollectMembers_ListNodeBase(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class ListView | File: ../UI/ListView.h
void CollectMembers_ListView(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_ScrollView(methods);
}

// class Localization | File: ../Resource/Localization.h
void CollectMembers_Localization(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class Log | File: ../IO/Log.h
void CollectMembers_Log(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class LogicComponent | File: ../Scene/LogicComponent.h
void CollectMembers_LogicComponent(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class Material | File: ../Graphics/Material.h
void CollectMembers_Material(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// struct MaterialShaderParameter | File: ../Graphics/Material.h
void CollectMembers_MaterialShaderParameter(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Matrix2 | File: ../Math/Matrix2.h
void CollectMembers_Matrix2(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Matrix3 | File: ../Math/Matrix3.h
void CollectMembers_Matrix3(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Matrix3x4 | File: ../Math/Matrix3x4.h
void CollectMembers_Matrix3x4(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Matrix4 | File: ../Math/Matrix4.h
void CollectMembers_Matrix4(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class MemoryBuffer | File: ../IO/MemoryBuffer.h
void CollectMembers_MemoryBuffer(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Menu | File: ../UI/Menu.h
void CollectMembers_Menu(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Button(methods);
}

// class MessageBox | File: ../UI/MessageBox.h
void CollectMembers_MessageBox(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class Model | File: ../Graphics/Model.h
void CollectMembers_Model(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_ResourceWithMetadata(methods);
}

// struct ModelMorph | File: ../Graphics/Model.h
void CollectMembers_ModelMorph(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Mutex | File: ../Core/Mutex.h
void CollectMembers_Mutex(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class MutexLock | File: ../Core/Mutex.h
void CollectMembers_MutexLock(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class NamedPipe | File: ../IO/NamedPipe.h
void CollectMembers_NamedPipe(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
    CollectMembers_AbstractFile(methods);
}

// struct NetworkState | File: ../Scene/ReplicationState.h
void CollectMembers_NetworkState(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Node | File: ../Scene/Node.h
void CollectMembers_Node(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Animatable(methods);
}

// struct NodeImpl | File: ../Scene/Node.h
void CollectMembers_NodeImpl(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct NodeReplicationState | File: ../Scene/ReplicationState.h
void CollectMembers_NodeReplicationState(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_ReplicationState(methods);
}

// class Object | File: ../Core/Object.h
void CollectMembers_Object(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// class ObjectAnimation | File: ../Scene/ObjectAnimation.h
void CollectMembers_ObjectAnimation(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// class ObjectFactory | File: ../Core/Object.h
void CollectMembers_ObjectFactory(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// struct OcclusionBatch | File: ../Graphics/OcclusionBuffer.h
void CollectMembers_OcclusionBatch(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class OcclusionBuffer | File: ../Graphics/OcclusionBuffer.h
void CollectMembers_OcclusionBuffer(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// struct OcclusionBufferData | File: ../Graphics/OcclusionBuffer.h
void CollectMembers_OcclusionBufferData(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Octant | File: ../Graphics/Octree.h
void CollectMembers_Octant(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Octree | File: ../Graphics/Octree.h
void CollectMembers_Octree(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
    CollectMembers_Octant(methods);
}

// class OctreeQuery | File: ../Graphics/OctreeQuery.h
void CollectMembers_OctreeQuery(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct OctreeQueryResult | File: ../Graphics/OctreeQuery.h
void CollectMembers_OctreeQueryResult(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class OggVorbisSoundStream | File: ../Audio/OggVorbisSoundStream.h
void CollectMembers_OggVorbisSoundStream(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_SoundStream(methods);
}

// struct PackageEntry | File: ../IO/PackageFile.h
void CollectMembers_PackageEntry(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class PackageFile | File: ../IO/PackageFile.h
void CollectMembers_PackageFile(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// struct Particle | File: ../Graphics/ParticleEmitter.h
void CollectMembers_Particle(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class ParticleEffect | File: ../Graphics/ParticleEffect.h
void CollectMembers_ParticleEffect(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// class ParticleEmitter | File: ../Graphics/ParticleEmitter.h
void CollectMembers_ParticleEmitter(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_BillboardSet(methods);
}

// class Pass | File: ../Graphics/Technique.h
void CollectMembers_Pass(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// struct PerThreadSceneResult | File: ../Graphics/View.h
void CollectMembers_PerThreadSceneResult(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Plane | File: ../Math/Plane.h
void CollectMembers_Plane(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class PointOctreeQuery | File: ../Graphics/OctreeQuery.h
void CollectMembers_PointOctreeQuery(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Polyhedron | File: ../Math/Polyhedron.h
void CollectMembers_Polyhedron(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Profiler | File: ../Core/Profiler.h
void CollectMembers_Profiler(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class ProfilerBlock | File: ../Core/Profiler.h
void CollectMembers_ProfilerBlock(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class ProgressBar | File: ../UI/ProgressBar.h
void CollectMembers_ProgressBar(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_BorderImage(methods);
}

// class Quaternion | File: ../Math/Quaternion.h
void CollectMembers_Quaternion(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Ray | File: ../Math/Ray.h
void CollectMembers_Ray(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class RayOctreeQuery | File: ../Graphics/OctreeQuery.h
void CollectMembers_RayOctreeQuery(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct RayQueryResult | File: ../Graphics/OctreeQuery.h
void CollectMembers_RayQueryResult(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Rect | File: ../Math/Rect.h
void CollectMembers_Rect(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct RefCount | File: ../Container/RefCounted.h
void CollectMembers_RefCount(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class RefCounted | File: ../Container/RefCounted.h
void CollectMembers_RefCounted(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class RenderPath | File: ../Graphics/RenderPath.h
void CollectMembers_RenderPath(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// struct RenderPathCommand | File: ../Graphics/RenderPath.h
void CollectMembers_RenderPathCommand(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class RenderSurface | File: ../Graphics/RenderSurface.h
void CollectMembers_RenderSurface(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// struct RenderTargetInfo | File: ../Graphics/RenderPath.h
void CollectMembers_RenderTargetInfo(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Renderer | File: ../Graphics/Renderer.h
void CollectMembers_Renderer(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// struct ReplicationState | File: ../Scene/ReplicationState.h
void CollectMembers_ReplicationState(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Resource | File: ../Resource/Resource.h
void CollectMembers_Resource(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class ResourceCache | File: ../Resource/ResourceCache.h
void CollectMembers_ResourceCache(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// struct ResourceGroup | File: ../Resource/ResourceCache.h
void CollectMembers_ResourceGroup(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct ResourceRef | File: ../Core/Variant.h
void CollectMembers_ResourceRef(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct ResourceRefList | File: ../Core/Variant.h
void CollectMembers_ResourceRefList(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class ResourceRouter | File: ../Resource/ResourceCache.h
void CollectMembers_ResourceRouter(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class ResourceWithMetadata | File: ../Resource/Resource.h
void CollectMembers_ResourceWithMetadata(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// class RibbonTrail | File: ../Graphics/RibbonTrail.h
void CollectMembers_RibbonTrail(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Drawable(methods);
}

// class Scene | File: ../Scene/Scene.h
void CollectMembers_Scene(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Node(methods);
}

// struct ScenePassInfo | File: ../Graphics/View.h
void CollectMembers_ScenePassInfo(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct SceneReplicationState | File: ../Scene/ReplicationState.h
void CollectMembers_SceneReplicationState(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_ReplicationState(methods);
}

// class SceneResolver | File: ../Scene/SceneResolver.h
void CollectMembers_SceneResolver(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct ScratchBuffer | File: ../Graphics/Graphics.h
void CollectMembers_ScratchBuffer(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct ScreenModeParams | File: ../Graphics/Graphics.h
void CollectMembers_ScreenModeParams(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class ScrollBar | File: ../UI/ScrollBar.h
void CollectMembers_ScrollBar(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_BorderImage(methods);
}

// class ScrollView | File: ../UI/ScrollView.h
void CollectMembers_ScrollView(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_UIElement(methods);
}

// class Serializable | File: ../Scene/Serializable.h
void CollectMembers_Serializable(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class Serializer | File: ../IO/Serializer.h
void CollectMembers_Serializer(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Shader | File: ../Graphics/Shader.h
void CollectMembers_Shader(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// struct ShaderParameter | File: ../Graphics/ShaderVariation.h
void CollectMembers_ShaderParameter(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class ShaderParameterAnimationInfo | File: ../Graphics/Material.h
void CollectMembers_ShaderParameterAnimationInfo(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_ValueAnimationInfo(methods);
}

// class ShaderPrecache | File: ../Graphics/ShaderPrecache.h
void CollectMembers_ShaderPrecache(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class ShaderVariation | File: ../Graphics/ShaderVariation.h
void CollectMembers_ShaderVariation(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
    CollectMembers_GPUObject(methods);
}

// struct ShadowBatchQueue | File: ../Graphics/Batch.h
void CollectMembers_ShadowBatchQueue(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Skeleton | File: ../Graphics/Skeleton.h
void CollectMembers_Skeleton(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Skybox | File: ../Graphics/Skybox.h
void CollectMembers_Skybox(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_StaticModel(methods);
}

// class Slider | File: ../UI/Slider.h
void CollectMembers_Slider(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_BorderImage(methods);
}

// class SmoothedTransform | File: ../Scene/SmoothedTransform.h
void CollectMembers_SmoothedTransform(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class Sound | File: ../Audio/Sound.h
void CollectMembers_Sound(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_ResourceWithMetadata(methods);
}

// class SoundListener | File: ../Audio/SoundListener.h
void CollectMembers_SoundListener(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class SoundSource | File: ../Audio/SoundSource.h
void CollectMembers_SoundSource(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class SoundSource3D | File: ../Audio/SoundSource3D.h
void CollectMembers_SoundSource3D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_SoundSource(methods);
}

// class SoundStream | File: ../Audio/SoundStream.h
void CollectMembers_SoundStream(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// struct SourceBatch | File: ../Graphics/Drawable.h
void CollectMembers_SourceBatch(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Sphere | File: ../Math/Sphere.h
void CollectMembers_Sphere(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class SphereOctreeQuery | File: ../Graphics/OctreeQuery.h
void CollectMembers_SphereOctreeQuery(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Spline | File: ../Core/Spline.h
void CollectMembers_Spline(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class SplinePath | File: ../Scene/SplinePath.h
void CollectMembers_SplinePath(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class Sprite | File: ../UI/Sprite.h
void CollectMembers_Sprite(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_UIElement(methods);
}

// class StaticModel | File: ../Graphics/StaticModel.h
void CollectMembers_StaticModel(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Drawable(methods);
}

// struct StaticModelGeometryData | File: ../Graphics/StaticModel.h
void CollectMembers_StaticModelGeometryData(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class StaticModelGroup | File: ../Graphics/StaticModelGroup.h
void CollectMembers_StaticModelGroup(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_StaticModel(methods);
}

// struct StoredLogMessage | File: ../IO/Log.h
void CollectMembers_StoredLogMessage(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class String | File: ../Container/Str.h
void CollectMembers_String(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class StringHash | File: ../Math/StringHash.h
void CollectMembers_StringHash(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class StringHashRegister | File: ../Core/StringHashRegister.h
void CollectMembers_StringHashRegister(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Technique | File: ../Graphics/Technique.h
void CollectMembers_Technique(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// struct TechniqueEntry | File: ../Graphics/Material.h
void CollectMembers_TechniqueEntry(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Terrain | File: ../Graphics/Terrain.h
void CollectMembers_Terrain(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class TerrainPatch | File: ../Graphics/TerrainPatch.h
void CollectMembers_TerrainPatch(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Drawable(methods);
}

// class Text | File: ../UI/Text.h
void CollectMembers_Text(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_UISelectable(methods);
}

// class Text3D | File: ../UI/Text3D.h
void CollectMembers_Text3D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Drawable(methods);
}

// class Texture | File: ../Graphics/Texture.h
void CollectMembers_Texture(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_ResourceWithMetadata(methods);
    CollectMembers_GPUObject(methods);
}

// class Texture2D | File: ../Graphics/Texture2D.h
void CollectMembers_Texture2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Texture(methods);
}

// class Texture2DArray | File: ../Graphics/Texture2DArray.h
void CollectMembers_Texture2DArray(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Texture(methods);
}

// class Texture3D | File: ../Graphics/Texture3D.h
void CollectMembers_Texture3D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Texture(methods);
}

// class TextureCube | File: ../Graphics/TextureCube.h
void CollectMembers_TextureCube(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Texture(methods);
}

// struct TextureFrame | File: ../Graphics/ParticleEffect.h
void CollectMembers_TextureFrame(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Thread | File: ../Core/Thread.h
void CollectMembers_Thread(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Time | File: ../Core/Timer.h
void CollectMembers_Time(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class Timer | File: ../Core/Timer.h
void CollectMembers_Timer(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class ToolTip | File: ../UI/ToolTip.h
void CollectMembers_ToolTip(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_UIElement(methods);
}

// struct TouchState | File: ../Input/Input.h
void CollectMembers_TouchState(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct TrailPoint | File: ../Graphics/RibbonTrail.h
void CollectMembers_TrailPoint(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class TypeInfo | File: ../Core/Object.h
void CollectMembers_TypeInfo(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class UI | File: ../UI/UI.h
void CollectMembers_UI(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class UIBatch | File: ../UI/UIBatch.h
void CollectMembers_UIBatch(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class UIComponent | File: ../UI/UIComponent.h
void CollectMembers_UIComponent(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class UIElement | File: ../UI/UIElement.h
void CollectMembers_UIElement(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Animatable(methods);
}

// class UISelectable | File: ../UI/UISelectable.h
void CollectMembers_UISelectable(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_UIElement(methods);
}

// class UnknownComponent | File: ../Scene/UnknownComponent.h
void CollectMembers_UnknownComponent(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct VAnimEventFrame | File: ../Scene/ValueAnimation.h
void CollectMembers_VAnimEventFrame(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct VAnimKeyFrame | File: ../Scene/ValueAnimation.h
void CollectMembers_VAnimKeyFrame(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class ValueAnimation | File: ../Scene/ValueAnimation.h
void CollectMembers_ValueAnimation(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// class ValueAnimationInfo | File: ../Scene/ValueAnimationInfo.h
void CollectMembers_ValueAnimationInfo(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// class Variant | File: ../Core/Variant.h
void CollectMembers_Variant(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Vector2 | File: ../Math/Vector2.h
void CollectMembers_Vector2(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Vector3 | File: ../Math/Vector3.h
void CollectMembers_Vector3(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Vector4 | File: ../Math/Vector4.h
void CollectMembers_Vector4(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class VectorBase | File: ../Container/VectorBase.h
void CollectMembers_VectorBase(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class VectorBuffer | File: ../IO/VectorBuffer.h
void CollectMembers_VectorBuffer(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_AbstractFile(methods);
}

// class VertexBuffer | File: ../Graphics/VertexBuffer.h
void CollectMembers_VertexBuffer(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
    CollectMembers_GPUObject(methods);
}

// struct VertexBufferDesc | File: ../Graphics/Model.h
void CollectMembers_VertexBufferDesc(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct VertexBufferMorph | File: ../Graphics/Model.h
void CollectMembers_VertexBufferMorph(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct VertexElement | File: ../Graphics/GraphicsDefs.h
void CollectMembers_VertexElement(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class View | File: ../Graphics/View.h
void CollectMembers_View(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class View3D | File: ../UI/View3D.h
void CollectMembers_View3D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Window(methods);
}

// class Viewport | File: ../Graphics/Viewport.h
void CollectMembers_Viewport(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class WString | File: ../Container/Str.h
void CollectMembers_WString(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Window | File: ../UI/Window.h
void CollectMembers_Window(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_BorderImage(methods);
}

// struct WindowModeParams | File: ../Graphics/Graphics.h
void CollectMembers_WindowModeParams(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct WorkItem | File: ../Core/WorkQueue.h
void CollectMembers_WorkItem(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class WorkQueue | File: ../Core/WorkQueue.h
void CollectMembers_WorkQueue(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class XMLElement | File: ../Resource/XMLElement.h
void CollectMembers_XMLElement(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class XMLFile | File: ../Resource/XMLFile.h
void CollectMembers_XMLFile(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// class XPathQuery | File: ../Resource/XMLElement.h
void CollectMembers_XPathQuery(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class XPathResultSet | File: ../Resource/XMLElement.h
void CollectMembers_XPathResultSet(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Zone | File: ../Graphics/Zone.h
void CollectMembers_Zone(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Drawable(methods);
}

#ifdef URHO3D_DATABASE

// class Database | File: ../Database/Database.h
void CollectMembers_Database(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

#endif // def URHO3D_DATABASE

#ifdef URHO3D_IK

// class IKConstraint | File: ../IK/IKConstraint.h
void CollectMembers_IKConstraint(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class IKEffector | File: ../IK/IKEffector.h
void CollectMembers_IKEffector(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class IKSolver | File: ../IK/IKSolver.h
void CollectMembers_IKSolver(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

#endif // def URHO3D_IK

#ifdef URHO3D_NAVIGATION

// class CrowdAgent | File: ../Navigation/CrowdAgent.h
void CollectMembers_CrowdAgent(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class CrowdManager | File: ../Navigation/CrowdManager.h
void CollectMembers_CrowdManager(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct CrowdObstacleAvoidanceParams | File: ../Navigation/CrowdManager.h
void CollectMembers_CrowdObstacleAvoidanceParams(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct DynamicNavBuildData | File: ../Navigation/NavBuildData.h
void CollectMembers_DynamicNavBuildData(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class DynamicNavigationMesh | File: ../Navigation/DynamicNavigationMesh.h
void CollectMembers_DynamicNavigationMesh(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_NavigationMesh(methods);
}

// class NavArea | File: ../Navigation/NavArea.h
void CollectMembers_NavArea(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct NavAreaStub | File: ../Navigation/NavBuildData.h
void CollectMembers_NavAreaStub(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct NavBuildData | File: ../Navigation/NavBuildData.h
void CollectMembers_NavBuildData(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Navigable | File: ../Navigation/Navigable.h
void CollectMembers_Navigable(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct NavigationGeometryInfo | File: ../Navigation/NavigationMesh.h
void CollectMembers_NavigationGeometryInfo(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class NavigationMesh | File: ../Navigation/NavigationMesh.h
void CollectMembers_NavigationMesh(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct NavigationPathPoint | File: ../Navigation/NavigationMesh.h
void CollectMembers_NavigationPathPoint(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Obstacle | File: ../Navigation/Obstacle.h
void CollectMembers_Obstacle(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class OffMeshConnection | File: ../Navigation/OffMeshConnection.h
void CollectMembers_OffMeshConnection(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct SimpleNavBuildData | File: ../Navigation/NavBuildData.h
void CollectMembers_SimpleNavBuildData(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_NavBuildData(methods);
}

#endif // def URHO3D_NAVIGATION

#ifdef URHO3D_NETWORK

// class Connection | File: ../Network/Connection.h
void CollectMembers_Connection(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class HttpRequest | File: ../Network/HttpRequest.h
void CollectMembers_HttpRequest(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
    CollectMembers_Deserializer(methods);
    CollectMembers_Thread(methods);
}

// class Network | File: ../Network/Network.h
void CollectMembers_Network(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Object(methods);
}

// class NetworkPriority | File: ../Network/NetworkPriority.h
void CollectMembers_NetworkPriority(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct PackageDownload | File: ../Network/Connection.h
void CollectMembers_PackageDownload(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct PackageUpload | File: ../Network/Connection.h
void CollectMembers_PackageUpload(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct RemoteEvent | File: ../Network/Connection.h
void CollectMembers_RemoteEvent(Vector<RegisterObjectMethodArgs>& methods)
{
}

#endif // def URHO3D_NETWORK

#ifdef URHO3D_PHYSICS

// struct CollisionGeometryData | File: ../Physics/CollisionShape.h
void CollectMembers_CollisionGeometryData(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// class CollisionShape | File: ../Physics/CollisionShape.h
void CollectMembers_CollisionShape(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class Constraint | File: ../Physics/Constraint.h
void CollectMembers_Constraint(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct ConvexData | File: ../Physics/CollisionShape.h
void CollectMembers_ConvexData(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_CollisionGeometryData(methods);
}

// struct DelayedWorldTransform | File: ../Physics/PhysicsWorld.h
void CollectMembers_DelayedWorldTransform(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct GImpactMeshData | File: ../Physics/CollisionShape.h
void CollectMembers_GImpactMeshData(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_CollisionGeometryData(methods);
}

// struct HeightfieldData | File: ../Physics/CollisionShape.h
void CollectMembers_HeightfieldData(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_CollisionGeometryData(methods);
}

// struct ManifoldPair | File: ../Physics/PhysicsWorld.h
void CollectMembers_ManifoldPair(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct PhysicsRaycastResult | File: ../Physics/PhysicsWorld.h
void CollectMembers_PhysicsRaycastResult(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class PhysicsWorld | File: ../Physics/PhysicsWorld.h
void CollectMembers_PhysicsWorld(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct PhysicsWorldConfig | File: ../Physics/PhysicsWorld.h
void CollectMembers_PhysicsWorldConfig(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class RaycastVehicle | File: ../Physics/RaycastVehicle.h
void CollectMembers_RaycastVehicle(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_LogicComponent(methods);
}

// class RigidBody | File: ../Physics/RigidBody.h
void CollectMembers_RigidBody(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct TriangleMeshData | File: ../Physics/CollisionShape.h
void CollectMembers_TriangleMeshData(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_CollisionGeometryData(methods);
}

#endif // def URHO3D_PHYSICS

#ifdef URHO3D_URHO2D

// class AnimatedSprite2D | File: ../Urho2D/AnimatedSprite2D.h
void CollectMembers_AnimatedSprite2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_StaticSprite2D(methods);
}

// class AnimationSet2D | File: ../Urho2D/AnimationSet2D.h
void CollectMembers_AnimationSet2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// class CollisionBox2D | File: ../Urho2D/CollisionBox2D.h
void CollectMembers_CollisionBox2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_CollisionShape2D(methods);
}

// class CollisionChain2D | File: ../Urho2D/CollisionChain2D.h
void CollectMembers_CollisionChain2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_CollisionShape2D(methods);
}

// class CollisionCircle2D | File: ../Urho2D/CollisionCircle2D.h
void CollectMembers_CollisionCircle2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_CollisionShape2D(methods);
}

// class CollisionEdge2D | File: ../Urho2D/CollisionEdge2D.h
void CollectMembers_CollisionEdge2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_CollisionShape2D(methods);
}

// class CollisionPolygon2D | File: ../Urho2D/CollisionPolygon2D.h
void CollectMembers_CollisionPolygon2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_CollisionShape2D(methods);
}

// class CollisionShape2D | File: ../Urho2D/CollisionShape2D.h
void CollectMembers_CollisionShape2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class Constraint2D | File: ../Urho2D/Constraint2D.h
void CollectMembers_Constraint2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class ConstraintDistance2D | File: ../Urho2D/ConstraintDistance2D.h
void CollectMembers_ConstraintDistance2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Constraint2D(methods);
}

// class ConstraintFriction2D | File: ../Urho2D/ConstraintFriction2D.h
void CollectMembers_ConstraintFriction2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Constraint2D(methods);
}

// class ConstraintGear2D | File: ../Urho2D/ConstraintGear2D.h
void CollectMembers_ConstraintGear2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Constraint2D(methods);
}

// class ConstraintMotor2D | File: ../Urho2D/ConstraintMotor2D.h
void CollectMembers_ConstraintMotor2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Constraint2D(methods);
}

// class ConstraintMouse2D | File: ../Urho2D/ConstraintMouse2D.h
void CollectMembers_ConstraintMouse2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Constraint2D(methods);
}

// class ConstraintPrismatic2D | File: ../Urho2D/ConstraintPrismatic2D.h
void CollectMembers_ConstraintPrismatic2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Constraint2D(methods);
}

// class ConstraintPulley2D | File: ../Urho2D/ConstraintPulley2D.h
void CollectMembers_ConstraintPulley2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Constraint2D(methods);
}

// class ConstraintRevolute2D | File: ../Urho2D/ConstraintRevolute2D.h
void CollectMembers_ConstraintRevolute2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Constraint2D(methods);
}

// class ConstraintRope2D | File: ../Urho2D/ConstraintRope2D.h
void CollectMembers_ConstraintRope2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Constraint2D(methods);
}

// class ConstraintWeld2D | File: ../Urho2D/ConstraintWeld2D.h
void CollectMembers_ConstraintWeld2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Constraint2D(methods);
}

// class ConstraintWheel2D | File: ../Urho2D/ConstraintWheel2D.h
void CollectMembers_ConstraintWheel2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Constraint2D(methods);
}

// struct DelayedWorldTransform2D | File: ../Urho2D/PhysicsWorld2D.h
void CollectMembers_DelayedWorldTransform2D(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Drawable2D | File: ../Urho2D/Drawable2D.h
void CollectMembers_Drawable2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Drawable(methods);
}

// struct Particle2D | File: ../Urho2D/ParticleEmitter2D.h
void CollectMembers_Particle2D(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class ParticleEffect2D | File: ../Urho2D/ParticleEffect2D.h
void CollectMembers_ParticleEffect2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// class ParticleEmitter2D | File: ../Urho2D/ParticleEmitter2D.h
void CollectMembers_ParticleEmitter2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Drawable2D(methods);
}

// struct PhysicsRaycastResult2D | File: ../Urho2D/PhysicsWorld2D.h
void CollectMembers_PhysicsRaycastResult2D(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class PhysicsWorld2D | File: ../Urho2D/PhysicsWorld2D.h
void CollectMembers_PhysicsWorld2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class PropertySet2D | File: ../Urho2D/TileMapDefs2D.h
void CollectMembers_PropertySet2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// class Renderer2D | File: ../Urho2D/Renderer2D.h
void CollectMembers_Renderer2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Drawable(methods);
}

// class RigidBody2D | File: ../Urho2D/RigidBody2D.h
void CollectMembers_RigidBody2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct SourceBatch2D | File: ../Urho2D/Drawable2D.h
void CollectMembers_SourceBatch2D(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class Sprite2D | File: ../Urho2D/Sprite2D.h
void CollectMembers_Sprite2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// class SpriteSheet2D | File: ../Urho2D/SpriteSheet2D.h
void CollectMembers_SpriteSheet2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// class StaticSprite2D | File: ../Urho2D/StaticSprite2D.h
void CollectMembers_StaticSprite2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Drawable2D(methods);
}

// class StretchableSprite2D | File: ../Urho2D/StretchableSprite2D.h
void CollectMembers_StretchableSprite2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_StaticSprite2D(methods);
}

// class Tile2D | File: ../Urho2D/TileMapDefs2D.h
void CollectMembers_Tile2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// class TileMap2D | File: ../Urho2D/TileMap2D.h
void CollectMembers_TileMap2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// struct TileMapInfo2D | File: ../Urho2D/TileMapDefs2D.h
void CollectMembers_TileMapInfo2D(Vector<RegisterObjectMethodArgs>& methods)
{
}

// class TileMapLayer2D | File: ../Urho2D/TileMapLayer2D.h
void CollectMembers_TileMapLayer2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Component(methods);
}

// class TileMapObject2D | File: ../Urho2D/TileMapDefs2D.h
void CollectMembers_TileMapObject2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// class TmxFile2D | File: ../Urho2D/TmxFile2D.h
void CollectMembers_TmxFile2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_Resource(methods);
}

// class TmxImageLayer2D | File: ../Urho2D/TmxFile2D.h
void CollectMembers_TmxImageLayer2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_TmxLayer2D(methods);
}

// class TmxLayer2D | File: ../Urho2D/TmxFile2D.h
void CollectMembers_TmxLayer2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_RefCounted(methods);
}

// class TmxObjectGroup2D | File: ../Urho2D/TmxFile2D.h
void CollectMembers_TmxObjectGroup2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_TmxLayer2D(methods);
}

// class TmxTileLayer2D | File: ../Urho2D/TmxFile2D.h
void CollectMembers_TmxTileLayer2D(Vector<RegisterObjectMethodArgs>& methods)
{
    CollectMembers_TmxLayer2D(methods);
}

// struct Vertex2D | File: ../Urho2D/Drawable2D.h
void CollectMembers_Vertex2D(Vector<RegisterObjectMethodArgs>& methods)
{
}

// struct ViewBatchInfo2D | File: ../Urho2D/Renderer2D.h
void CollectMembers_ViewBatchInfo2D(Vector<RegisterObjectMethodArgs>& methods)
{
}

#endif // def URHO3D_URHO2D

} // namespace Urho3D
