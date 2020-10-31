// DO NOT EDIT. This file is generated

// We need register all types before registration of any members because members can use any types

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

// Ignored headers
//#include "../Database/ODBC/ODBCConnection.h"
//#include "../Database/ODBC/ODBCResult.h"
//#include "../Graphics/Direct3D11/D3D11GraphicsImpl.h"
//#include "../Graphics/Direct3D11/D3D11ShaderProgram.h"
//#include "../Graphics/Direct3D11/D3D11VertexDeclaration.h"
//#include "../Graphics/Direct3D9/D3D9VertexDeclaration.h"
//#include "../Graphics/OpenGL/OGLGraphicsImpl.h"
//#include "../Resource/PListFile.h"

#include "../Audio/Audio.h"
#include "../Audio/BufferedSoundStream.h"
#include "../Audio/OggVorbisSoundStream.h"
#include "../Audio/Sound.h"
#include "../Audio/SoundListener.h"
#include "../Audio/SoundSource.h"
#include "../Audio/SoundSource3D.h"
#include "../Audio/SoundStream.h"
#include "../Container/Allocator.h"
#include "../Container/HashBase.h"
#include "../Container/LinkedList.h"
#include "../Container/ListBase.h"
#include "../Container/RefCounted.h"
#include "../Container/Str.h"
#include "../Container/VectorBase.h"
#include "../Core/Attribute.h"
#include "../Core/Condition.h"
#include "../Core/Context.h"
#include "../Core/EventProfiler.h"
#include "../Core/Mutex.h"
#include "../Core/Object.h"
#include "../Core/Profiler.h"
#include "../Core/Spline.h"
#include "../Core/StringHashRegister.h"
#include "../Core/Timer.h"
#include "../Core/Variant.h"
#include "../Core/WorkQueue.h"
#ifdef URHO3D_DATABASE
#include "../Database/Database.h"
#endif
#include "../Engine/Application.h"
#include "../Engine/Console.h"
#include "../Engine/DebugHud.h"
#include "../Engine/Engine.h"
#include "../Graphics/AnimatedModel.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationController.h"
#include "../Graphics/AnimationState.h"
#include "../Graphics/Batch.h"
#include "../Graphics/BillboardSet.h"
#include "../Graphics/Camera.h"
#include "../Graphics/ConstantBuffer.h"
#include "../Graphics/CustomGeometry.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/DecalSet.h"
#include "../Graphics/Drawable.h"
#include "../Graphics/GPUObject.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicsDefs.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Light.h"
#include "../Graphics/Material.h"
#include "../Graphics/Model.h"
#include "../Graphics/OcclusionBuffer.h"
#include "../Graphics/Octree.h"
#include "../Graphics/OctreeQuery.h"
#include "../Graphics/ParticleEffect.h"
#include "../Graphics/ParticleEmitter.h"
#include "../Graphics/RenderPath.h"
#include "../Graphics/RenderSurface.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/RibbonTrail.h"
#include "../Graphics/Shader.h"
#include "../Graphics/ShaderPrecache.h"
#include "../Graphics/ShaderVariation.h"
#include "../Graphics/Skeleton.h"
#include "../Graphics/Skybox.h"
#include "../Graphics/StaticModel.h"
#include "../Graphics/StaticModelGroup.h"
#include "../Graphics/Technique.h"
#include "../Graphics/Terrain.h"
#include "../Graphics/TerrainPatch.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/Texture2DArray.h"
#include "../Graphics/Texture3D.h"
#include "../Graphics/TextureCube.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/View.h"
#include "../Graphics/Viewport.h"
#include "../Graphics/Zone.h"
#ifdef URHO3D_IK
#include "../IK/IKConstraint.h"
#endif
#ifdef URHO3D_IK
#include "../IK/IKEffector.h"
#endif
#ifdef URHO3D_IK
#include "../IK/IKSolver.h"
#endif
#include "../IO/AbstractFile.h"
#include "../IO/Deserializer.h"
#include "../IO/File.h"
#include "../IO/FileSystem.h"
#include "../IO/FileWatcher.h"
#include "../IO/Log.h"
#include "../IO/NamedPipe.h"
#include "../IO/PackageFile.h"
#include "../IO/Serializer.h"
#include "../IO/VectorBuffer.h"
#include "../Input/Controls.h"
#include "../Input/Input.h"
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
#include "../Navigation/CrowdAgent.h"
#endif
#ifdef URHO3D_NAVIGATION
#include "../Navigation/CrowdManager.h"
#endif
#ifdef URHO3D_NAVIGATION
#include "../Navigation/DynamicNavigationMesh.h"
#endif
#ifdef URHO3D_NAVIGATION
#include "../Navigation/NavArea.h"
#endif
#ifdef URHO3D_NAVIGATION
#include "../Navigation/NavBuildData.h"
#endif
#ifdef URHO3D_NAVIGATION
#include "../Navigation/Navigable.h"
#endif
#ifdef URHO3D_NAVIGATION
#include "../Navigation/NavigationMesh.h"
#endif
#ifdef URHO3D_NAVIGATION
#include "../Navigation/Obstacle.h"
#endif
#ifdef URHO3D_NAVIGATION
#include "../Navigation/OffMeshConnection.h"
#endif
#ifdef URHO3D_NETWORK
#include "../Network/Connection.h"
#endif
#ifdef URHO3D_NETWORK
#include "../Network/HttpRequest.h"
#endif
#ifdef URHO3D_NETWORK
#include "../Network/Network.h"
#endif
#ifdef URHO3D_NETWORK
#include "../Network/NetworkPriority.h"
#endif
#ifdef URHO3D_PHYSICS
#include "../Physics/CollisionShape.h"
#endif
#ifdef URHO3D_PHYSICS
#include "../Physics/Constraint.h"
#endif
#ifdef URHO3D_PHYSICS
#include "../Physics/PhysicsWorld.h"
#endif
#ifdef URHO3D_PHYSICS
#include "../Physics/RaycastVehicle.h"
#endif
#ifdef URHO3D_PHYSICS
#include "../Physics/RigidBody.h"
#endif
#include "../Resource/BackgroundLoader.h"
#include "../Resource/Image.h"
#include "../Resource/JSONFile.h"
#include "../Resource/JSONValue.h"
#include "../Resource/Localization.h"
#include "../Resource/Resource.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/XMLElement.h"
#include "../Resource/XMLFile.h"
#include "../Scene/Animatable.h"
#include "../Scene/Component.h"
#include "../Scene/LogicComponent.h"
#include "../Scene/Node.h"
#include "../Scene/ObjectAnimation.h"
#include "../Scene/ReplicationState.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResolver.h"
#include "../Scene/Serializable.h"
#include "../Scene/SmoothedTransform.h"
#include "../Scene/SplinePath.h"
#include "../Scene/UnknownComponent.h"
#include "../Scene/ValueAnimation.h"
#include "../Scene/ValueAnimationInfo.h"
#include "../UI/BorderImage.h"
#include "../UI/Button.h"
#include "../UI/CheckBox.h"
#include "../UI/Cursor.h"
#include "../UI/DropDownList.h"
#include "../UI/FileSelector.h"
#include "../UI/Font.h"
#include "../UI/FontFace.h"
#include "../UI/FontFaceBitmap.h"
#include "../UI/FontFaceFreeType.h"
#include "../UI/LineEdit.h"
#include "../UI/ListView.h"
#include "../UI/Menu.h"
#include "../UI/MessageBox.h"
#include "../UI/ProgressBar.h"
#include "../UI/ScrollBar.h"
#include "../UI/ScrollView.h"
#include "../UI/Slider.h"
#include "../UI/Sprite.h"
#include "../UI/Text.h"
#include "../UI/Text3D.h"
#include "../UI/ToolTip.h"
#include "../UI/UI.h"
#include "../UI/UIBatch.h"
#include "../UI/UIComponent.h"
#include "../UI/UIElement.h"
#include "../UI/UISelectable.h"
#include "../UI/View3D.h"
#include "../UI/Window.h"
#ifdef URHO3D_URHO2D
#include "../Urho2D/AnimatedSprite2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/AnimationSet2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/CollisionBox2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/CollisionChain2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/CollisionCircle2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/CollisionEdge2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/CollisionPolygon2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/CollisionShape2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/Constraint2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ConstraintDistance2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ConstraintFriction2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ConstraintGear2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ConstraintMotor2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ConstraintMouse2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ConstraintPrismatic2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ConstraintPulley2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ConstraintRevolute2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ConstraintRope2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ConstraintWeld2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ConstraintWheel2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/Drawable2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ParticleEffect2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ParticleEmitter2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/PhysicsWorld2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/Renderer2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/RigidBody2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/Sprite2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/SpriteSheet2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/StaticSprite2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/StretchableSprite2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/TileMap2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/TileMapDefs2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/TileMapLayer2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/TmxFile2D.h"
#endif

namespace Urho3D
{

void ASRegisterGenerated_Classes(asIScriptEngine* engine)
{
    // class AbstractFile | File: ../IO/AbstractFile.h
    engine->RegisterObjectType("AbstractFile", 0, asOBJ_REF);
    // class AllContentOctreeQuery | File: ../Graphics/OctreeQuery.h
    // Not registered because have @nobind mark
    // class Animatable | File: ../Scene/Animatable.h
    engine->RegisterObjectType("Animatable", 0, asOBJ_REF);
    // class AnimatedModel | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectType("AnimatedModel", 0, asOBJ_REF);
#ifdef URHO3D_URHO2D
    // class AnimatedSprite2D | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectType("AnimatedSprite2D", 0, asOBJ_REF);
#endif
    // class Animation | File: ../Graphics/Animation.h
    engine->RegisterObjectType("Animation", 0, asOBJ_REF);
    // class AnimationController | File: ../Graphics/AnimationController.h
    engine->RegisterObjectType("AnimationController", 0, asOBJ_REF);
#ifdef URHO3D_URHO2D
    // class AnimationSet2D | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectType("AnimationSet2D", 0, asOBJ_REF);
#endif
    // class AnimationState | File: ../Graphics/AnimationState.h
    engine->RegisterObjectType("AnimationState", 0, asOBJ_REF);
    // class Application | File: ../Engine/Application.h
    engine->RegisterObjectType("Application", 0, asOBJ_REF);
    // class AreaAllocator | File: ../Math/AreaAllocator.h
    engine->RegisterObjectType("AreaAllocator", sizeof(AreaAllocator), asOBJ_VALUE | asGetTypeTraits<AreaAllocator>());
    // class AttributeAccessor | File: ../Core/Attribute.h
    engine->RegisterObjectType("AttributeAccessor", 0, asOBJ_REF);
    // class AttributeAnimationInfo | File: ../Scene/Animatable.h
    engine->RegisterObjectType("AttributeAnimationInfo", 0, asOBJ_REF);
    // class Audio | File: ../Audio/Audio.h
    engine->RegisterObjectType("Audio", 0, asOBJ_REF);
    // class AutoProfileBlock | File: ../Core/Profiler.h
    // Not registered because have @nobind mark
    // class BackgroundLoader | File: ../Resource/BackgroundLoader.h
    // Not registered because have @nobind mark
    // class BillboardSet | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectType("BillboardSet", 0, asOBJ_REF);
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
    // class CheckBox | File: ../UI/CheckBox.h
    engine->RegisterObjectType("CheckBox", 0, asOBJ_REF);
#ifdef URHO3D_URHO2D
    // class CollisionBox2D | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectType("CollisionBox2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class CollisionChain2D | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectType("CollisionChain2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class CollisionCircle2D | File: ../Urho2D/CollisionCircle2D.h
    engine->RegisterObjectType("CollisionCircle2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class CollisionEdge2D | File: ../Urho2D/CollisionEdge2D.h
    engine->RegisterObjectType("CollisionEdge2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class CollisionPolygon2D | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectType("CollisionPolygon2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_PHYSICS
    // class CollisionShape | File: ../Physics/CollisionShape.h
    engine->RegisterObjectType("CollisionShape", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class CollisionShape2D | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectType("CollisionShape2D", 0, asOBJ_REF);
#endif
    // class Color | File: ../Math/Color.h
    engine->RegisterObjectType("Color", sizeof(Color), asOBJ_VALUE | asGetTypeTraits<Color>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Component | File: ../Scene/Component.h
    engine->RegisterObjectType("Component", 0, asOBJ_REF);
    // class Condition | File: ../Core/Condition.h
    engine->RegisterObjectType("Condition", sizeof(Condition), asOBJ_VALUE | asGetTypeTraits<Condition>());
#ifdef URHO3D_NETWORK
    // class Connection | File: ../Network/Connection.h
    engine->RegisterObjectType("Connection", 0, asOBJ_REF);
#endif
    // class Console | File: ../Engine/Console.h
    engine->RegisterObjectType("Console", 0, asOBJ_REF);
    // class ConstantBuffer | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectType("ConstantBuffer", 0, asOBJ_REF);
#ifdef URHO3D_PHYSICS
    // class Constraint | File: ../Physics/Constraint.h
    engine->RegisterObjectType("Constraint", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class Constraint2D | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectType("Constraint2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class ConstraintDistance2D | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectType("ConstraintDistance2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class ConstraintFriction2D | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectType("ConstraintFriction2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class ConstraintGear2D | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectType("ConstraintGear2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class ConstraintMotor2D | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectType("ConstraintMotor2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class ConstraintMouse2D | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectType("ConstraintMouse2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class ConstraintPrismatic2D | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectType("ConstraintPrismatic2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class ConstraintPulley2D | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectType("ConstraintPulley2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class ConstraintRevolute2D | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectType("ConstraintRevolute2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class ConstraintRope2D | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectType("ConstraintRope2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class ConstraintWeld2D | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectType("ConstraintWeld2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class ConstraintWheel2D | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectType("ConstraintWheel2D", 0, asOBJ_REF);
#endif
    // class Context | File: ../Core/Context.h
    engine->RegisterObjectType("Context", 0, asOBJ_REF);
    // class Controls | File: ../Input/Controls.h
    engine->RegisterObjectType("Controls", sizeof(Controls), asOBJ_VALUE | asGetTypeTraits<Controls>());
#ifdef URHO3D_NAVIGATION
    // class CrowdAgent | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectType("CrowdAgent", 0, asOBJ_REF);
#endif
#ifdef URHO3D_NAVIGATION
    // class CrowdManager | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectType("CrowdManager", 0, asOBJ_REF);
#endif
    // class Cursor | File: ../UI/Cursor.h
    engine->RegisterObjectType("Cursor", 0, asOBJ_REF);
    // class CustomGeometry | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectType("CustomGeometry", 0, asOBJ_REF);
    // class CustomVariantValue | File: ../Core/Variant.h
    // Not registered because have @nobind mark
#ifdef URHO3D_DATABASE
    // class Database | File: ../Database/Database.h
    engine->RegisterObjectType("Database", 0, asOBJ_REF);
#endif
    // class DebugHud | File: ../Engine/DebugHud.h
    engine->RegisterObjectType("DebugHud", 0, asOBJ_REF);
    // class DebugRenderer | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectType("DebugRenderer", 0, asOBJ_REF);
    // class DecalSet | File: ../Graphics/DecalSet.h
    engine->RegisterObjectType("DecalSet", 0, asOBJ_REF);
    // class Deserializer | File: ../IO/Deserializer.h
    engine->RegisterObjectType("Deserializer", 0, asOBJ_REF);
    // class Drawable | File: ../Graphics/Drawable.h
    engine->RegisterObjectType("Drawable", 0, asOBJ_REF);
#ifdef URHO3D_URHO2D
    // class Drawable2D | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectType("Drawable2D", 0, asOBJ_REF);
#endif
    // class DropDownList | File: ../UI/DropDownList.h
    engine->RegisterObjectType("DropDownList", 0, asOBJ_REF);
#ifdef URHO3D_NAVIGATION
    // class DynamicNavigationMesh | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectType("DynamicNavigationMesh", 0, asOBJ_REF);
#endif
    // class Engine | File: ../Engine/Engine.h
    engine->RegisterObjectType("Engine", 0, asOBJ_REF);
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
    // class FileSystem | File: ../IO/FileSystem.h
    engine->RegisterObjectType("FileSystem", 0, asOBJ_REF);
    // class FileWatcher | File: ../IO/FileWatcher.h
    engine->RegisterObjectType("FileWatcher", 0, asOBJ_REF);
    // class Font | File: ../UI/Font.h
    engine->RegisterObjectType("Font", 0, asOBJ_REF);
    // class FontFace | File: ../UI/FontFace.h
    engine->RegisterObjectType("FontFace", 0, asOBJ_REF);
    // class FontFaceBitmap | File: ../UI/FontFaceBitmap.h
    engine->RegisterObjectType("FontFaceBitmap", 0, asOBJ_REF);
    // class FontFaceFreeType | File: ../UI/FontFaceFreeType.h
    engine->RegisterObjectType("FontFaceFreeType", 0, asOBJ_REF);
    // class Frustum | File: ../Math/Frustum.h
    engine->RegisterObjectType("Frustum", sizeof(Frustum), asOBJ_VALUE | asGetTypeTraits<Frustum>());
    // class FrustumOctreeQuery | File: ../Graphics/OctreeQuery.h
    // Not registered because have @nobind mark
    // class GPUObject | File: ../Graphics/GPUObject.h
    engine->RegisterObjectType("GPUObject", sizeof(GPUObject), asOBJ_VALUE | asGetTypeTraits<GPUObject>());
    // class Geometry | File: ../Graphics/Geometry.h
    engine->RegisterObjectType("Geometry", 0, asOBJ_REF);
    // class Graphics | File: ../Graphics/Graphics.h
    engine->RegisterObjectType("Graphics", 0, asOBJ_REF);
    // class HashBase | File: ../Container/HashBase.h
    engine->RegisterObjectType("HashBase", sizeof(HashBase), asOBJ_VALUE | asGetTypeTraits<HashBase>());
    // class HiresTimer | File: ../Core/Timer.h
    engine->RegisterObjectType("HiresTimer", sizeof(HiresTimer), asOBJ_VALUE | asGetTypeTraits<HiresTimer>());
#ifdef URHO3D_NETWORK
    // class HttpRequest | File: ../Network/HttpRequest.h
    engine->RegisterObjectType("HttpRequest", 0, asOBJ_REF);
#endif
#ifdef URHO3D_IK
    // class IKConstraint | File: ../IK/IKConstraint.h
    engine->RegisterObjectType("IKConstraint", 0, asOBJ_REF);
#endif
#ifdef URHO3D_IK
    // class IKEffector | File: ../IK/IKEffector.h
    engine->RegisterObjectType("IKEffector", 0, asOBJ_REF);
#endif
#ifdef URHO3D_IK
    // class IKSolver | File: ../IK/IKSolver.h
    engine->RegisterObjectType("IKSolver", 0, asOBJ_REF);
#endif
    // class Image | File: ../Resource/Image.h
    engine->RegisterObjectType("Image", 0, asOBJ_REF);
    // class IndexBuffer | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectType("IndexBuffer", 0, asOBJ_REF);
    // class Input | File: ../Input/Input.h
    engine->RegisterObjectType("Input", 0, asOBJ_REF);
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
    // class Light | File: ../Graphics/Light.h
    engine->RegisterObjectType("Light", 0, asOBJ_REF);
    // class LineEdit | File: ../UI/LineEdit.h
    engine->RegisterObjectType("LineEdit", 0, asOBJ_REF);
    // class ListBase | File: ../Container/ListBase.h
    engine->RegisterObjectType("ListBase", sizeof(ListBase), asOBJ_VALUE | asGetTypeTraits<ListBase>());
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
    // class Mutex | File: ../Core/Mutex.h
    engine->RegisterObjectType("Mutex", sizeof(Mutex), asOBJ_VALUE | asGetTypeTraits<Mutex>());
    // class MutexLock | File: ../Core/Mutex.h
    engine->RegisterObjectType("MutexLock", sizeof(MutexLock), asOBJ_VALUE | asGetTypeTraits<MutexLock>());
    // class NamedPipe | File: ../IO/NamedPipe.h
    engine->RegisterObjectType("NamedPipe", 0, asOBJ_REF);
#ifdef URHO3D_NAVIGATION
    // class NavArea | File: ../Navigation/NavArea.h
    engine->RegisterObjectType("NavArea", 0, asOBJ_REF);
#endif
#ifdef URHO3D_NAVIGATION
    // class Navigable | File: ../Navigation/Navigable.h
    engine->RegisterObjectType("Navigable", 0, asOBJ_REF);
#endif
#ifdef URHO3D_NAVIGATION
    // class NavigationMesh | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectType("NavigationMesh", 0, asOBJ_REF);
#endif
#ifdef URHO3D_NETWORK
    // class Network | File: ../Network/Network.h
    engine->RegisterObjectType("Network", 0, asOBJ_REF);
#endif
#ifdef URHO3D_NETWORK
    // class NetworkPriority | File: ../Network/NetworkPriority.h
    engine->RegisterObjectType("NetworkPriority", 0, asOBJ_REF);
#endif
    // class Node | File: ../Scene/Node.h
    engine->RegisterObjectType("Node", 0, asOBJ_REF);
    // class Object | File: ../Core/Object.h
    engine->RegisterObjectType("Object", 0, asOBJ_REF);
    // class ObjectAnimation | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectType("ObjectAnimation", 0, asOBJ_REF);
    // class ObjectFactory | File: ../Core/Object.h
    engine->RegisterObjectType("ObjectFactory", 0, asOBJ_REF);
#ifdef URHO3D_NAVIGATION
    // class Obstacle | File: ../Navigation/Obstacle.h
    engine->RegisterObjectType("Obstacle", 0, asOBJ_REF);
#endif
    // class OcclusionBuffer | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectType("OcclusionBuffer", 0, asOBJ_REF);
    // class Octant | File: ../Graphics/Octree.h
    // Not registered because have @nobind mark
    // class Octree | File: ../Graphics/Octree.h
    engine->RegisterObjectType("Octree", 0, asOBJ_REF);
#ifdef URHO3D_NAVIGATION
    // class OffMeshConnection | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectType("OffMeshConnection", 0, asOBJ_REF);
#endif
    // class OggVorbisSoundStream | File: ../Audio/OggVorbisSoundStream.h
    engine->RegisterObjectType("OggVorbisSoundStream", 0, asOBJ_REF);
    // class PackageFile | File: ../IO/PackageFile.h
    engine->RegisterObjectType("PackageFile", 0, asOBJ_REF);
    // class ParticleEffect | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectType("ParticleEffect", 0, asOBJ_REF);
#ifdef URHO3D_URHO2D
    // class ParticleEffect2D | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectType("ParticleEffect2D", 0, asOBJ_REF);
#endif
    // class ParticleEmitter | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectType("ParticleEmitter", 0, asOBJ_REF);
#ifdef URHO3D_URHO2D
    // class ParticleEmitter2D | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectType("ParticleEmitter2D", 0, asOBJ_REF);
#endif
    // class Pass | File: ../Graphics/Technique.h
    engine->RegisterObjectType("Pass", 0, asOBJ_REF);
#ifdef URHO3D_PHYSICS
    // class PhysicsWorld | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectType("PhysicsWorld", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class PhysicsWorld2D | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectType("PhysicsWorld2D", 0, asOBJ_REF);
#endif
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
#ifdef URHO3D_URHO2D
    // class PropertySet2D | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectType("PropertySet2D", 0, asOBJ_REF);
#endif
    // class Quaternion | File: ../Math/Quaternion.h
    engine->RegisterObjectType("Quaternion", sizeof(Quaternion), asOBJ_VALUE | asGetTypeTraits<Quaternion>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Ray | File: ../Math/Ray.h
    engine->RegisterObjectType("Ray", sizeof(Ray), asOBJ_VALUE | asGetTypeTraits<Ray>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class RayOctreeQuery | File: ../Graphics/OctreeQuery.h
    // Not registered because have @nobind mark
#ifdef URHO3D_PHYSICS
    // class RaycastVehicle | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectType("RaycastVehicle", 0, asOBJ_REF);
#endif
    // class Rect | File: ../Math/Rect.h
    engine->RegisterObjectType("Rect", sizeof(Rect), asOBJ_VALUE | asGetTypeTraits<Rect>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class RefCounted | File: ../Container/RefCounted.h
    engine->RegisterObjectType("RefCounted", 0, asOBJ_REF);
    // class RenderPath | File: ../Graphics/RenderPath.h
    engine->RegisterObjectType("RenderPath", 0, asOBJ_REF);
    // class RenderSurface | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectType("RenderSurface", 0, asOBJ_REF);
    // class Renderer | File: ../Graphics/Renderer.h
    engine->RegisterObjectType("Renderer", 0, asOBJ_REF);
#ifdef URHO3D_URHO2D
    // class Renderer2D | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectType("Renderer2D", 0, asOBJ_REF);
#endif
    // class Resource | File: ../Resource/Resource.h
    engine->RegisterObjectType("Resource", 0, asOBJ_REF);
    // class ResourceCache | File: ../Resource/ResourceCache.h
    engine->RegisterObjectType("ResourceCache", 0, asOBJ_REF);
    // class ResourceRouter | File: ../Resource/ResourceCache.h
    // Not registered because have @nobind mark
    // class ResourceWithMetadata | File: ../Resource/Resource.h
    engine->RegisterObjectType("ResourceWithMetadata", 0, asOBJ_REF);
    // class RibbonTrail | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectType("RibbonTrail", 0, asOBJ_REF);
#ifdef URHO3D_PHYSICS
    // class RigidBody | File: ../Physics/RigidBody.h
    engine->RegisterObjectType("RigidBody", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class RigidBody2D | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectType("RigidBody2D", 0, asOBJ_REF);
#endif
    // class Scene | File: ../Scene/Scene.h
    engine->RegisterObjectType("Scene", 0, asOBJ_REF);
    // class SceneResolver | File: ../Scene/SceneResolver.h
    engine->RegisterObjectType("SceneResolver", sizeof(SceneResolver), asOBJ_VALUE | asGetTypeTraits<SceneResolver>());
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
    // class ShaderParameterAnimationInfo | File: ../Graphics/Material.h
    engine->RegisterObjectType("ShaderParameterAnimationInfo", 0, asOBJ_REF);
    // class ShaderPrecache | File: ../Graphics/ShaderPrecache.h
    engine->RegisterObjectType("ShaderPrecache", 0, asOBJ_REF);
    // class ShaderVariation | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectType("ShaderVariation", 0, asOBJ_REF);
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
#ifdef URHO3D_URHO2D
    // class Sprite2D | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectType("Sprite2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class SpriteSheet2D | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectType("SpriteSheet2D", 0, asOBJ_REF);
#endif
    // class StaticModel | File: ../Graphics/StaticModel.h
    engine->RegisterObjectType("StaticModel", 0, asOBJ_REF);
    // class StaticModelGroup | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectType("StaticModelGroup", 0, asOBJ_REF);
#ifdef URHO3D_URHO2D
    // class StaticSprite2D | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectType("StaticSprite2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class StretchableSprite2D | File: ../Urho2D/StretchableSprite2D.h
    engine->RegisterObjectType("StretchableSprite2D", 0, asOBJ_REF);
#endif
    // class String | File: ../Container/Str.h
    engine->RegisterObjectType("String", sizeof(String), asOBJ_VALUE | asGetTypeTraits<String>());
    // class StringHash | File: ../Math/StringHash.h
    engine->RegisterObjectType("StringHash", sizeof(StringHash), asOBJ_VALUE | asGetTypeTraits<StringHash>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);
    // class StringHashRegister | File: ../Core/StringHashRegister.h
    engine->RegisterObjectType("StringHashRegister", sizeof(StringHashRegister), asOBJ_VALUE | asGetTypeTraits<StringHashRegister>());
    // class Technique | File: ../Graphics/Technique.h
    engine->RegisterObjectType("Technique", 0, asOBJ_REF);
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
#ifdef URHO3D_URHO2D
    // class Tile2D | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectType("Tile2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class TileMap2D | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectType("TileMap2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class TileMapLayer2D | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectType("TileMapLayer2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class TileMapObject2D | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectType("TileMapObject2D", 0, asOBJ_REF);
#endif
    // class Time | File: ../Core/Timer.h
    engine->RegisterObjectType("Time", 0, asOBJ_REF);
    // class Timer | File: ../Core/Timer.h
    engine->RegisterObjectType("Timer", sizeof(Timer), asOBJ_VALUE | asGetTypeTraits<Timer>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);
#ifdef URHO3D_URHO2D
    // class TmxFile2D | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectType("TmxFile2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class TmxImageLayer2D | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectType("TmxImageLayer2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class TmxLayer2D | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectType("TmxLayer2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class TmxObjectGroup2D | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectType("TmxObjectGroup2D", 0, asOBJ_REF);
#endif
#ifdef URHO3D_URHO2D
    // class TmxTileLayer2D | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectType("TmxTileLayer2D", 0, asOBJ_REF);
#endif
    // class ToolTip | File: ../UI/ToolTip.h
    engine->RegisterObjectType("ToolTip", 0, asOBJ_REF);
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
    // struct AllocatorBlock | File: ../Container/Allocator.h
    engine->RegisterObjectType("AllocatorBlock", sizeof(AllocatorBlock), asOBJ_VALUE | asGetTypeTraits<AllocatorBlock>());
    // struct AllocatorNode | File: ../Container/Allocator.h
    engine->RegisterObjectType("AllocatorNode", sizeof(AllocatorNode), asOBJ_VALUE | asGetTypeTraits<AllocatorNode>());
    // struct AnimationControl | File: ../Graphics/AnimationController.h
    engine->RegisterObjectType("AnimationControl", 0, asOBJ_REF);
    // struct AnimationKeyFrame | File: ../Graphics/Animation.h
    engine->RegisterObjectType("AnimationKeyFrame", sizeof(AnimationKeyFrame), asOBJ_VALUE | asGetTypeTraits<AnimationKeyFrame>());
    // struct AnimationStateTrack | File: ../Graphics/AnimationState.h
    engine->RegisterObjectType("AnimationStateTrack", sizeof(AnimationStateTrack), asOBJ_VALUE | asGetTypeTraits<AnimationStateTrack>());
    // struct AnimationTrack | File: ../Graphics/Animation.h
    engine->RegisterObjectType("AnimationTrack", 0, asOBJ_REF);
    // struct AnimationTriggerPoint | File: ../Graphics/Animation.h
    engine->RegisterObjectType("AnimationTriggerPoint", sizeof(AnimationTriggerPoint), asOBJ_VALUE | asGetTypeTraits<AnimationTriggerPoint>());
    // struct AsyncProgress | File: ../Scene/Scene.h
    engine->RegisterObjectType("AsyncProgress", sizeof(AsyncProgress), asOBJ_VALUE | asGetTypeTraits<AsyncProgress>());
    // struct AttributeHandle | File: ../Core/Attribute.h
    // Not registered because have @nobind mark
    // struct AttributeInfo | File: ../Core/Attribute.h
    engine->RegisterObjectType("AttributeInfo", sizeof(AttributeInfo), asOBJ_VALUE | asGetTypeTraits<AttributeInfo>());
    // struct BackgroundLoadItem | File: ../Resource/BackgroundLoader.h
    engine->RegisterObjectType("BackgroundLoadItem", sizeof(BackgroundLoadItem), asOBJ_VALUE | asGetTypeTraits<BackgroundLoadItem>());
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
    // struct Bone | File: ../Graphics/Skeleton.h
    engine->RegisterObjectType("Bone", 0, asOBJ_REF);
    // struct CascadeParameters | File: ../Graphics/Light.h
    engine->RegisterObjectType("CascadeParameters", sizeof(CascadeParameters), asOBJ_VALUE | asGetTypeTraits<CascadeParameters>() | asOBJ_POD);
    // struct CharLocation | File: ../UI/Text.h
    engine->RegisterObjectType("CharLocation", sizeof(CharLocation), asOBJ_VALUE | asGetTypeTraits<CharLocation>());
#ifdef URHO3D_PHYSICS
    // struct CollisionGeometryData | File: ../Physics/CollisionShape.h
    engine->RegisterObjectType("CollisionGeometryData", 0, asOBJ_REF);
#endif
    // struct ColorFrame | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectType("ColorFrame", 0, asOBJ_REF);
    // struct ComponentReplicationState | File: ../Scene/ReplicationState.h
    engine->RegisterObjectType("ComponentReplicationState", sizeof(ComponentReplicationState), asOBJ_VALUE | asGetTypeTraits<ComponentReplicationState>());
    // struct CompressedLevel | File: ../Resource/Image.h
    engine->RegisterObjectType("CompressedLevel", sizeof(CompressedLevel), asOBJ_VALUE | asGetTypeTraits<CompressedLevel>());
#ifdef URHO3D_PHYSICS
    // struct ConvexData | File: ../Physics/CollisionShape.h
    engine->RegisterObjectType("ConvexData", 0, asOBJ_REF);
#endif
#ifdef URHO3D_NAVIGATION
    // struct CrowdObstacleAvoidanceParams | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectType("CrowdObstacleAvoidanceParams", sizeof(CrowdObstacleAvoidanceParams), asOBJ_VALUE | asGetTypeTraits<CrowdObstacleAvoidanceParams>() | asOBJ_POD);
#endif
    // struct CursorShapeInfo | File: ../UI/Cursor.h
    engine->RegisterObjectType("CursorShapeInfo", sizeof(CursorShapeInfo), asOBJ_VALUE | asGetTypeTraits<CursorShapeInfo>());
    // struct CustomGeometryVertex | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectType("CustomGeometryVertex", 0, asOBJ_REF);
    // struct DebugLine | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectType("DebugLine", sizeof(DebugLine), asOBJ_VALUE | asGetTypeTraits<DebugLine>());
    // struct DebugTriangle | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectType("DebugTriangle", sizeof(DebugTriangle), asOBJ_VALUE | asGetTypeTraits<DebugTriangle>());
    // struct Decal | File: ../Graphics/DecalSet.h
    engine->RegisterObjectType("Decal", sizeof(Decal), asOBJ_VALUE | asGetTypeTraits<Decal>());
    // struct DecalVertex | File: ../Graphics/DecalSet.h
    engine->RegisterObjectType("DecalVertex", sizeof(DecalVertex), asOBJ_VALUE | asGetTypeTraits<DecalVertex>());
#ifdef URHO3D_PHYSICS
    // struct DelayedWorldTransform | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectType("DelayedWorldTransform", sizeof(DelayedWorldTransform), asOBJ_VALUE | asGetTypeTraits<DelayedWorldTransform>());
#endif
#ifdef URHO3D_URHO2D
    // struct DelayedWorldTransform2D | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectType("DelayedWorldTransform2D", sizeof(DelayedWorldTransform2D), asOBJ_VALUE | asGetTypeTraits<DelayedWorldTransform2D>());
#endif
    // struct DepthValue | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectType("DepthValue", sizeof(DepthValue), asOBJ_VALUE | asGetTypeTraits<DepthValue>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);
    // struct DirtyBits | File: ../Scene/ReplicationState.h
    engine->RegisterObjectType("DirtyBits", sizeof(DirtyBits), asOBJ_VALUE | asGetTypeTraits<DirtyBits>());
    // struct DynamicNavBuildData | File: ../Navigation/NavBuildData.h
    // Not registered because have @nobind mark
    // struct FileSelectorEntry | File: ../UI/FileSelector.h
    engine->RegisterObjectType("FileSelectorEntry", sizeof(FileSelectorEntry), asOBJ_VALUE | asGetTypeTraits<FileSelectorEntry>());
    // struct FocusParameters | File: ../Graphics/Light.h
    engine->RegisterObjectType("FocusParameters", sizeof(FocusParameters), asOBJ_VALUE | asGetTypeTraits<FocusParameters>() | asOBJ_POD);
    // struct FontGlyph | File: ../UI/FontFace.h
    engine->RegisterObjectType("FontGlyph", sizeof(FontGlyph), asOBJ_VALUE | asGetTypeTraits<FontGlyph>());
    // struct FrameInfo | File: ../Graphics/Drawable.h
    engine->RegisterObjectType("FrameInfo", sizeof(FrameInfo), asOBJ_VALUE | asGetTypeTraits<FrameInfo>());
#ifdef URHO3D_PHYSICS
    // struct GImpactMeshData | File: ../Physics/CollisionShape.h
    engine->RegisterObjectType("GImpactMeshData", 0, asOBJ_REF);
#endif
    // struct GeometryDesc | File: ../Graphics/Model.h
    engine->RegisterObjectType("GeometryDesc", sizeof(GeometryDesc), asOBJ_VALUE | asGetTypeTraits<GeometryDesc>());
    // struct GlyphLocation | File: ../UI/Text.h
    // Not registered because have @nobind mark
    // struct HashIteratorBase | File: ../Container/HashBase.h
    engine->RegisterObjectType("HashIteratorBase", sizeof(HashIteratorBase), asOBJ_VALUE | asGetTypeTraits<HashIteratorBase>());
    // struct HashNodeBase | File: ../Container/HashBase.h
    engine->RegisterObjectType("HashNodeBase", sizeof(HashNodeBase), asOBJ_VALUE | asGetTypeTraits<HashNodeBase>());
#ifdef URHO3D_PHYSICS
    // struct HeightfieldData | File: ../Physics/CollisionShape.h
    engine->RegisterObjectType("HeightfieldData", 0, asOBJ_REF);
#endif
    // struct IndexBufferDesc | File: ../Graphics/Model.h
    engine->RegisterObjectType("IndexBufferDesc", sizeof(IndexBufferDesc), asOBJ_VALUE | asGetTypeTraits<IndexBufferDesc>());
    // struct InstanceData | File: ../Graphics/Batch.h
    engine->RegisterObjectType("InstanceData", sizeof(InstanceData), asOBJ_VALUE | asGetTypeTraits<InstanceData>());
    // struct JoystickState | File: ../Input/Input.h
    engine->RegisterObjectType("JoystickState", 0, asOBJ_REF);
    // struct LightBatchQueue | File: ../Graphics/Batch.h
    engine->RegisterObjectType("LightBatchQueue", sizeof(LightBatchQueue), asOBJ_VALUE | asGetTypeTraits<LightBatchQueue>());
    // struct LightQueryResult | File: ../Graphics/View.h
    engine->RegisterObjectType("LightQueryResult", sizeof(LightQueryResult), asOBJ_VALUE | asGetTypeTraits<LightQueryResult>());
    // struct LinkedListNode | File: ../Container/LinkedList.h
    engine->RegisterObjectType("LinkedListNode", sizeof(LinkedListNode), asOBJ_VALUE | asGetTypeTraits<LinkedListNode>());
    // struct ListIteratorBase | File: ../Container/ListBase.h
    engine->RegisterObjectType("ListIteratorBase", sizeof(ListIteratorBase), asOBJ_VALUE | asGetTypeTraits<ListIteratorBase>());
    // struct ListNodeBase | File: ../Container/ListBase.h
    engine->RegisterObjectType("ListNodeBase", sizeof(ListNodeBase), asOBJ_VALUE | asGetTypeTraits<ListNodeBase>());
#ifdef URHO3D_PHYSICS
    // struct ManifoldPair | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectType("ManifoldPair", sizeof(ManifoldPair), asOBJ_VALUE | asGetTypeTraits<ManifoldPair>());
#endif
    // struct MaterialShaderParameter | File: ../Graphics/Material.h
    engine->RegisterObjectType("MaterialShaderParameter", sizeof(MaterialShaderParameter), asOBJ_VALUE | asGetTypeTraits<MaterialShaderParameter>());
    // struct ModelMorph | File: ../Graphics/Model.h
    engine->RegisterObjectType("ModelMorph", sizeof(ModelMorph), asOBJ_VALUE | asGetTypeTraits<ModelMorph>());
#ifdef URHO3D_NAVIGATION
    // struct NavAreaStub | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectType("NavAreaStub", sizeof(NavAreaStub), asOBJ_VALUE | asGetTypeTraits<NavAreaStub>());
#endif
#ifdef URHO3D_NAVIGATION
    // struct NavBuildData | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectType("NavBuildData", sizeof(NavBuildData), asOBJ_VALUE | asGetTypeTraits<NavBuildData>());
#endif
#ifdef URHO3D_NAVIGATION
    // struct NavigationGeometryInfo | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectType("NavigationGeometryInfo", sizeof(NavigationGeometryInfo), asOBJ_VALUE | asGetTypeTraits<NavigationGeometryInfo>());
#endif
#ifdef URHO3D_NAVIGATION
    // struct NavigationPathPoint | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectType("NavigationPathPoint", sizeof(NavigationPathPoint), asOBJ_VALUE | asGetTypeTraits<NavigationPathPoint>());
#endif
    // struct NetworkState | File: ../Scene/ReplicationState.h
    engine->RegisterObjectType("NetworkState", sizeof(NetworkState), asOBJ_VALUE | asGetTypeTraits<NetworkState>());
    // struct NodeImpl | File: ../Scene/Node.h
    engine->RegisterObjectType("NodeImpl", sizeof(NodeImpl), asOBJ_VALUE | asGetTypeTraits<NodeImpl>());
    // struct NodeReplicationState | File: ../Scene/ReplicationState.h
    engine->RegisterObjectType("NodeReplicationState", sizeof(NodeReplicationState), asOBJ_VALUE | asGetTypeTraits<NodeReplicationState>());
    // struct OcclusionBatch | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectType("OcclusionBatch", sizeof(OcclusionBatch), asOBJ_VALUE | asGetTypeTraits<OcclusionBatch>());
    // struct OcclusionBufferData | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectType("OcclusionBufferData", sizeof(OcclusionBufferData), asOBJ_VALUE | asGetTypeTraits<OcclusionBufferData>());
    // struct OctreeQueryResult | File: ../Graphics/OctreeQuery.h
    engine->RegisterObjectType("OctreeQueryResult", sizeof(OctreeQueryResult), asOBJ_VALUE | asGetTypeTraits<OctreeQueryResult>());
#ifdef URHO3D_NETWORK
    // struct PackageDownload | File: ../Network/Connection.h
    engine->RegisterObjectType("PackageDownload", sizeof(PackageDownload), asOBJ_VALUE | asGetTypeTraits<PackageDownload>());
#endif
    // struct PackageEntry | File: ../IO/PackageFile.h
    engine->RegisterObjectType("PackageEntry", sizeof(PackageEntry), asOBJ_VALUE | asGetTypeTraits<PackageEntry>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);
#ifdef URHO3D_NETWORK
    // struct PackageUpload | File: ../Network/Connection.h
    engine->RegisterObjectType("PackageUpload", sizeof(PackageUpload), asOBJ_VALUE | asGetTypeTraits<PackageUpload>());
#endif
    // struct Particle | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectType("Particle", sizeof(Particle), asOBJ_VALUE | asGetTypeTraits<Particle>());
#ifdef URHO3D_URHO2D
    // struct Particle2D | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectType("Particle2D", sizeof(Particle2D), asOBJ_VALUE | asGetTypeTraits<Particle2D>());
#endif
    // struct PerThreadSceneResult | File: ../Graphics/View.h
    engine->RegisterObjectType("PerThreadSceneResult", sizeof(PerThreadSceneResult), asOBJ_VALUE | asGetTypeTraits<PerThreadSceneResult>());
#ifdef URHO3D_PHYSICS
    // struct PhysicsRaycastResult | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectType("PhysicsRaycastResult", sizeof(PhysicsRaycastResult), asOBJ_VALUE | asGetTypeTraits<PhysicsRaycastResult>());
#endif
#ifdef URHO3D_URHO2D
    // struct PhysicsRaycastResult2D | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectType("PhysicsRaycastResult2D", sizeof(PhysicsRaycastResult2D), asOBJ_VALUE | asGetTypeTraits<PhysicsRaycastResult2D>());
#endif
#ifdef URHO3D_PHYSICS
    // struct PhysicsWorldConfig | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectType("PhysicsWorldConfig", sizeof(PhysicsWorldConfig), asOBJ_VALUE | asGetTypeTraits<PhysicsWorldConfig>());
#endif
    // struct RayQueryResult | File: ../Graphics/OctreeQuery.h
    engine->RegisterObjectType("RayQueryResult", sizeof(RayQueryResult), asOBJ_VALUE | asGetTypeTraits<RayQueryResult>());
    // struct RefCount | File: ../Container/RefCounted.h
    engine->RegisterObjectType("RefCount", sizeof(RefCount), asOBJ_VALUE | asGetTypeTraits<RefCount>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);
#ifdef URHO3D_NETWORK
    // struct RemoteEvent | File: ../Network/Connection.h
    engine->RegisterObjectType("RemoteEvent", sizeof(RemoteEvent), asOBJ_VALUE | asGetTypeTraits<RemoteEvent>());
#endif
    // struct RenderPathCommand | File: ../Graphics/RenderPath.h
    engine->RegisterObjectType("RenderPathCommand", sizeof(RenderPathCommand), asOBJ_VALUE | asGetTypeTraits<RenderPathCommand>());
    // struct RenderTargetInfo | File: ../Graphics/RenderPath.h
    engine->RegisterObjectType("RenderTargetInfo", sizeof(RenderTargetInfo), asOBJ_VALUE | asGetTypeTraits<RenderTargetInfo>());
    // struct ReplicationState | File: ../Scene/ReplicationState.h
    engine->RegisterObjectType("ReplicationState", sizeof(ReplicationState), asOBJ_VALUE | asGetTypeTraits<ReplicationState>());
    // struct ResourceGroup | File: ../Resource/ResourceCache.h
    engine->RegisterObjectType("ResourceGroup", sizeof(ResourceGroup), asOBJ_VALUE | asGetTypeTraits<ResourceGroup>());
    // struct ResourceRef | File: ../Core/Variant.h
    engine->RegisterObjectType("ResourceRef", sizeof(ResourceRef), asOBJ_VALUE | asGetTypeTraits<ResourceRef>());
    // struct ResourceRefList | File: ../Core/Variant.h
    engine->RegisterObjectType("ResourceRefList", sizeof(ResourceRefList), asOBJ_VALUE | asGetTypeTraits<ResourceRefList>());
    // struct ScenePassInfo | File: ../Graphics/View.h
    engine->RegisterObjectType("ScenePassInfo", sizeof(ScenePassInfo), asOBJ_VALUE | asGetTypeTraits<ScenePassInfo>());
    // struct SceneReplicationState | File: ../Scene/ReplicationState.h
    engine->RegisterObjectType("SceneReplicationState", sizeof(SceneReplicationState), asOBJ_VALUE | asGetTypeTraits<SceneReplicationState>());
    // struct ScratchBuffer | File: ../Graphics/Graphics.h
    engine->RegisterObjectType("ScratchBuffer", sizeof(ScratchBuffer), asOBJ_VALUE | asGetTypeTraits<ScratchBuffer>());
    // struct ScreenModeParams | File: ../Graphics/Graphics.h
    engine->RegisterObjectType("ScreenModeParams", sizeof(ScreenModeParams), asOBJ_VALUE | asGetTypeTraits<ScreenModeParams>());
    // struct ShaderParameter | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectType("ShaderParameter", sizeof(ShaderParameter), asOBJ_VALUE | asGetTypeTraits<ShaderParameter>());
    // struct ShadowBatchQueue | File: ../Graphics/Batch.h
    engine->RegisterObjectType("ShadowBatchQueue", sizeof(ShadowBatchQueue), asOBJ_VALUE | asGetTypeTraits<ShadowBatchQueue>());
#ifdef URHO3D_NAVIGATION
    // struct SimpleNavBuildData | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectType("SimpleNavBuildData", sizeof(SimpleNavBuildData), asOBJ_VALUE | asGetTypeTraits<SimpleNavBuildData>());
#endif
    // struct SourceBatch | File: ../Graphics/Drawable.h
    engine->RegisterObjectType("SourceBatch", sizeof(SourceBatch), asOBJ_VALUE | asGetTypeTraits<SourceBatch>());
#ifdef URHO3D_URHO2D
    // struct SourceBatch2D | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectType("SourceBatch2D", sizeof(SourceBatch2D), asOBJ_VALUE | asGetTypeTraits<SourceBatch2D>());
#endif
    // struct StaticModelGeometryData | File: ../Graphics/StaticModel.h
    engine->RegisterObjectType("StaticModelGeometryData", sizeof(StaticModelGeometryData), asOBJ_VALUE | asGetTypeTraits<StaticModelGeometryData>());
    // struct StoredLogMessage | File: ../IO/Log.h
    engine->RegisterObjectType("StoredLogMessage", sizeof(StoredLogMessage), asOBJ_VALUE | asGetTypeTraits<StoredLogMessage>());
    // struct TechniqueEntry | File: ../Graphics/Material.h
    engine->RegisterObjectType("TechniqueEntry", sizeof(TechniqueEntry), asOBJ_VALUE | asGetTypeTraits<TechniqueEntry>());
    // struct TextureFrame | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectType("TextureFrame", 0, asOBJ_REF);
#ifdef URHO3D_URHO2D
    // struct TileMapInfo2D | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectType("TileMapInfo2D", 0, asOBJ_REF);
#endif
    // struct TouchState | File: ../Input/Input.h
    engine->RegisterObjectType("TouchState", 0, asOBJ_REF);
    // struct TrailPoint | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectType("TrailPoint", sizeof(TrailPoint), asOBJ_VALUE | asGetTypeTraits<TrailPoint>());
#ifdef URHO3D_PHYSICS
    // struct TriangleMeshData | File: ../Physics/CollisionShape.h
    engine->RegisterObjectType("TriangleMeshData", 0, asOBJ_REF);
#endif
    // struct VAnimEventFrame | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectType("VAnimEventFrame", sizeof(VAnimEventFrame), asOBJ_VALUE | asGetTypeTraits<VAnimEventFrame>());
    // struct VAnimKeyFrame | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectType("VAnimKeyFrame", sizeof(VAnimKeyFrame), asOBJ_VALUE | asGetTypeTraits<VAnimKeyFrame>());
#ifdef URHO3D_URHO2D
    // struct Vertex2D | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectType("Vertex2D", sizeof(Vertex2D), asOBJ_VALUE | asGetTypeTraits<Vertex2D>());
#endif
    // struct VertexBufferDesc | File: ../Graphics/Model.h
    engine->RegisterObjectType("VertexBufferDesc", sizeof(VertexBufferDesc), asOBJ_VALUE | asGetTypeTraits<VertexBufferDesc>());
    // struct VertexBufferMorph | File: ../Graphics/Model.h
    engine->RegisterObjectType("VertexBufferMorph", sizeof(VertexBufferMorph), asOBJ_VALUE | asGetTypeTraits<VertexBufferMorph>());
    // struct VertexElement | File: ../Graphics/GraphicsDefs.h
    engine->RegisterObjectType("VertexElement", sizeof(VertexElement), asOBJ_VALUE | asGetTypeTraits<VertexElement>());
    // struct ViewBatchInfo2D | File: ../Urho2D/Renderer2D.h
    // Not registered because have @nobind mark
    // struct WindowModeParams | File: ../Graphics/Graphics.h
    engine->RegisterObjectType("WindowModeParams", sizeof(WindowModeParams), asOBJ_VALUE | asGetTypeTraits<WindowModeParams>());
    // struct WorkItem | File: ../Core/WorkQueue.h
    // Not registered because have @nobind mark
}

}
