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
static void Register_AbstractFile(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AbstractFile(methods);
    const char* asClassName = "AbstractFile";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AllocatorBlock(methods);
    const char* asClassName = "AllocatorBlock";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AllocatorNode(methods);
    const char* asClassName = "AllocatorNode";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Animatable | File: ../Scene/Animatable.h
static void Register_Animatable(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Animatable(methods);
    const char* asClassName = "Animatable";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class AnimatedModel | File: ../Graphics/AnimatedModel.h
static void Register_AnimatedModel(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AnimatedModel(methods);
    const char* asClassName = "AnimatedModel";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Animation | File: ../Graphics/Animation.h
static void Register_Animation(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Animation(methods);
    const char* asClassName = "Animation";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct AnimationControl | File: ../Graphics/AnimationController.h
static void Register_AnimationControl(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AnimationControl(methods);
    const char* asClassName = "AnimationControl";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class AnimationController | File: ../Graphics/AnimationController.h
static void Register_AnimationController(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AnimationController(methods);
    const char* asClassName = "AnimationController";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AnimationKeyFrame(methods);
    const char* asClassName = "AnimationKeyFrame";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class AnimationState | File: ../Graphics/AnimationState.h
static void Register_AnimationState(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AnimationState(methods);
    const char* asClassName = "AnimationState";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AnimationStateTrack(methods);
    const char* asClassName = "AnimationStateTrack";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct AnimationTrack | File: ../Graphics/Animation.h
static void Register_AnimationTrack(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AnimationTrack(methods);
    const char* asClassName = "AnimationTrack";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AnimationTriggerPoint(methods);
    const char* asClassName = "AnimationTriggerPoint";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AreaAllocator(methods);
    const char* asClassName = "AreaAllocator";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AsyncProgress(methods);
    const char* asClassName = "AsyncProgress";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class AttributeAccessor | File: ../Core/Attribute.h
static void Register_AttributeAccessor(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AttributeAccessor(methods);
    const char* asClassName = "AttributeAccessor";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class AttributeAnimationInfo | File: ../Scene/Animatable.h
static void Register_AttributeAnimationInfo(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AttributeAnimationInfo(methods);
    const char* asClassName = "AttributeAnimationInfo";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AttributeInfo(methods);
    const char* asClassName = "AttributeInfo";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Audio | File: ../Audio/Audio.h
static void Register_Audio(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Audio(methods);
    const char* asClassName = "Audio";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_BackgroundLoadItem(methods);
    const char* asClassName = "BackgroundLoadItem";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Batch(methods);
    const char* asClassName = "Batch";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_BatchGroup(methods);
    const char* asClassName = "BatchGroup";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_BatchGroupKey(methods);
    const char* asClassName = "BatchGroupKey";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_BatchQueue(methods);
    const char* asClassName = "BatchQueue";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct BiasParameters | File: ../Graphics/Light.h
static void Register_BiasParameters(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_BiasParameters(methods);
    const char* asClassName = "BiasParameters";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct Billboard | File: ../Graphics/BillboardSet.h
static void Register_Billboard(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Billboard(methods);
    const char* asClassName = "Billboard";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class BillboardSet | File: ../Graphics/BillboardSet.h
static void Register_BillboardSet(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_BillboardSet(methods);
    const char* asClassName = "BillboardSet";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct Bone | File: ../Graphics/Skeleton.h
static void Register_Bone(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Bone(methods);
    const char* asClassName = "Bone";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class BorderImage | File: ../UI/BorderImage.h
static void Register_BorderImage(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_BorderImage(methods);
    const char* asClassName = "BorderImage";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class BoundingBox | File: ../Math/BoundingBox.h
static void Register_BoundingBox(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_BoundingBox(methods);
    const char* asClassName = "BoundingBox";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class BufferedSoundStream | File: ../Audio/BufferedSoundStream.h
static void Register_BufferedSoundStream(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_BufferedSoundStream(methods);
    const char* asClassName = "BufferedSoundStream";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Button | File: ../UI/Button.h
static void Register_Button(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Button(methods);
    const char* asClassName = "Button";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Camera | File: ../Graphics/Camera.h
static void Register_Camera(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Camera(methods);
    const char* asClassName = "Camera";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct CascadeParameters | File: ../Graphics/Light.h
static void Register_CascadeParameters(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CascadeParameters(methods);
    const char* asClassName = "CascadeParameters";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CharLocation(methods);
    const char* asClassName = "CharLocation";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class CheckBox | File: ../UI/CheckBox.h
static void Register_CheckBox(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CheckBox(methods);
    const char* asClassName = "CheckBox";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Color | File: ../Math/Color.h
static void Register_Color(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Color(methods);
    const char* asClassName = "Color";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct ColorFrame | File: ../Graphics/ParticleEffect.h
static void Register_ColorFrame(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ColorFrame(methods);
    const char* asClassName = "ColorFrame";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Component | File: ../Scene/Component.h
static void Register_Component(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Component(methods);
    const char* asClassName = "Component";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ComponentReplicationState(methods);
    const char* asClassName = "ComponentReplicationState";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CompressedLevel(methods);
    const char* asClassName = "CompressedLevel";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Condition(methods);
    const char* asClassName = "Condition";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Console | File: ../Engine/Console.h
static void Register_Console(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Console(methods);
    const char* asClassName = "Console";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ConstantBuffer | File: ../Graphics/ConstantBuffer.h
static void Register_ConstantBuffer(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ConstantBuffer(methods);
    const char* asClassName = "ConstantBuffer";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Context | File: ../Core/Context.h
static void Register_Context(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Context(methods);
    const char* asClassName = "Context";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Controls(methods);
    const char* asClassName = "Controls";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Cursor | File: ../UI/Cursor.h
static void Register_Cursor(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Cursor(methods);
    const char* asClassName = "Cursor";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CursorShapeInfo(methods);
    const char* asClassName = "CursorShapeInfo";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class CustomGeometry | File: ../Graphics/CustomGeometry.h
static void Register_CustomGeometry(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CustomGeometry(methods);
    const char* asClassName = "CustomGeometry";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct CustomGeometryVertex | File: ../Graphics/CustomGeometry.h
static void Register_CustomGeometryVertex(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CustomGeometryVertex(methods);
    const char* asClassName = "CustomGeometryVertex";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class DebugHud | File: ../Engine/DebugHud.h
static void Register_DebugHud(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_DebugHud(methods);
    const char* asClassName = "DebugHud";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_DebugLine(methods);
    const char* asClassName = "DebugLine";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class DebugRenderer | File: ../Graphics/DebugRenderer.h
static void Register_DebugRenderer(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_DebugRenderer(methods);
    const char* asClassName = "DebugRenderer";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_DebugTriangle(methods);
    const char* asClassName = "DebugTriangle";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Decal(methods);
    const char* asClassName = "Decal";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class DecalSet | File: ../Graphics/DecalSet.h
static void Register_DecalSet(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_DecalSet(methods);
    const char* asClassName = "DecalSet";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_DecalVertex(methods);
    const char* asClassName = "DecalVertex";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct DepthValue | File: ../Graphics/OcclusionBuffer.h
static void Register_DepthValue(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_DepthValue(methods);
    const char* asClassName = "DepthValue";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Deserializer | File: ../IO/Deserializer.h
static void Register_Deserializer(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Deserializer(methods);
    const char* asClassName = "Deserializer";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_DirtyBits(methods);
    const char* asClassName = "DirtyBits";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Drawable | File: ../Graphics/Drawable.h
static void Register_Drawable(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Drawable(methods);
    const char* asClassName = "Drawable";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class DropDownList | File: ../UI/DropDownList.h
static void Register_DropDownList(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_DropDownList(methods);
    const char* asClassName = "DropDownList";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Engine | File: ../Engine/Engine.h
static void Register_Engine(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Engine(methods);
    const char* asClassName = "Engine";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class EventProfiler | File: ../Core/EventProfiler.h
static void Register_EventProfiler(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_EventProfiler(methods);
    const char* asClassName = "EventProfiler";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class EventReceiverGroup | File: ../Core/Context.h
static void Register_EventReceiverGroup(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_EventReceiverGroup(methods);
    const char* asClassName = "EventReceiverGroup";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class File | File: ../IO/File.h
static void Register_File(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_File(methods);
    const char* asClassName = "File";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class FileSelector | File: ../UI/FileSelector.h
static void Register_FileSelector(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_FileSelector(methods);
    const char* asClassName = "FileSelector";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_FileSelectorEntry(methods);
    const char* asClassName = "FileSelectorEntry";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class FileSystem | File: ../IO/FileSystem.h
static void Register_FileSystem(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_FileSystem(methods);
    const char* asClassName = "FileSystem";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class FileWatcher | File: ../IO/FileWatcher.h
static void Register_FileWatcher(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_FileWatcher(methods);
    const char* asClassName = "FileWatcher";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct FocusParameters | File: ../Graphics/Light.h
static void Register_FocusParameters(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_FocusParameters(methods);
    const char* asClassName = "FocusParameters";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Font | File: ../UI/Font.h
static void Register_Font(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Font(methods);
    const char* asClassName = "Font";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class FontFace | File: ../UI/FontFace.h
static void Register_FontFace(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_FontFace(methods);
    const char* asClassName = "FontFace";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class FontFaceBitmap | File: ../UI/FontFaceBitmap.h
static void Register_FontFaceBitmap(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_FontFaceBitmap(methods);
    const char* asClassName = "FontFaceBitmap";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class FontFaceFreeType | File: ../UI/FontFaceFreeType.h
static void Register_FontFaceFreeType(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_FontFaceFreeType(methods);
    const char* asClassName = "FontFaceFreeType";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_FontGlyph(methods);
    const char* asClassName = "FontGlyph";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_FrameInfo(methods);
    const char* asClassName = "FrameInfo";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Frustum(methods);
    const char* asClassName = "Frustum";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_GPUObject(methods);
    const char* asClassName = "GPUObject";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Geometry | File: ../Graphics/Geometry.h
static void Register_Geometry(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Geometry(methods);
    const char* asClassName = "Geometry";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_GeometryDesc(methods);
    const char* asClassName = "GeometryDesc";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Graphics | File: ../Graphics/Graphics.h
static void Register_Graphics(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Graphics(methods);
    const char* asClassName = "Graphics";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_HashBase(methods);
    const char* asClassName = "HashBase";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_HashIteratorBase(methods);
    const char* asClassName = "HashIteratorBase";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_HashNodeBase(methods);
    const char* asClassName = "HashNodeBase";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_HiresTimer(methods);
    const char* asClassName = "HiresTimer";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Image | File: ../Resource/Image.h
static void Register_Image(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Image(methods);
    const char* asClassName = "Image";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class IndexBuffer | File: ../Graphics/IndexBuffer.h
static void Register_IndexBuffer(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_IndexBuffer(methods);
    const char* asClassName = "IndexBuffer";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_IndexBufferDesc(methods);
    const char* asClassName = "IndexBufferDesc";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Input | File: ../Input/Input.h
static void Register_Input(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Input(methods);
    const char* asClassName = "Input";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_InstanceData(methods);
    const char* asClassName = "InstanceData";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class IntRect | File: ../Math/Rect.h
static void Register_IntRect(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_IntRect(methods);
    const char* asClassName = "IntRect";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class IntVector2 | File: ../Math/Vector2.h
static void Register_IntVector2(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_IntVector2(methods);
    const char* asClassName = "IntVector2";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class IntVector3 | File: ../Math/Vector3.h
static void Register_IntVector3(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_IntVector3(methods);
    const char* asClassName = "IntVector3";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class JSONFile | File: ../Resource/JSONFile.h
static void Register_JSONFile(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_JSONFile(methods);
    const char* asClassName = "JSONFile";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_JSONValue(methods);
    const char* asClassName = "JSONValue";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct JoystickState | File: ../Input/Input.h
static void Register_JoystickState(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_JoystickState(methods);
    const char* asClassName = "JoystickState";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Light | File: ../Graphics/Light.h
static void Register_Light(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Light(methods);
    const char* asClassName = "Light";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_LightBatchQueue(methods);
    const char* asClassName = "LightBatchQueue";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_LightQueryResult(methods);
    const char* asClassName = "LightQueryResult";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class LineEdit | File: ../UI/LineEdit.h
static void Register_LineEdit(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_LineEdit(methods);
    const char* asClassName = "LineEdit";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_LinkedListNode(methods);
    const char* asClassName = "LinkedListNode";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ListBase(methods);
    const char* asClassName = "ListBase";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ListIteratorBase(methods);
    const char* asClassName = "ListIteratorBase";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ListNodeBase(methods);
    const char* asClassName = "ListNodeBase";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ListView | File: ../UI/ListView.h
static void Register_ListView(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ListView(methods);
    const char* asClassName = "ListView";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Localization | File: ../Resource/Localization.h
static void Register_Localization(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Localization(methods);
    const char* asClassName = "Localization";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Log | File: ../IO/Log.h
static void Register_Log(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Log(methods);
    const char* asClassName = "Log";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class LogicComponent | File: ../Scene/LogicComponent.h
static void Register_LogicComponent(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_LogicComponent(methods);
    const char* asClassName = "LogicComponent";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Material | File: ../Graphics/Material.h
static void Register_Material(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Material(methods);
    const char* asClassName = "Material";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_MaterialShaderParameter(methods);
    const char* asClassName = "MaterialShaderParameter";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Matrix2 | File: ../Math/Matrix2.h
static void Register_Matrix2(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Matrix2(methods);
    const char* asClassName = "Matrix2";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Matrix3 | File: ../Math/Matrix3.h
static void Register_Matrix3(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Matrix3(methods);
    const char* asClassName = "Matrix3";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Matrix3x4 | File: ../Math/Matrix3x4.h
static void Register_Matrix3x4(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Matrix3x4(methods);
    const char* asClassName = "Matrix3x4";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Matrix4 | File: ../Math/Matrix4.h
static void Register_Matrix4(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Matrix4(methods);
    const char* asClassName = "Matrix4";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Menu | File: ../UI/Menu.h
static void Register_Menu(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Menu(methods);
    const char* asClassName = "Menu";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class MessageBox | File: ../UI/MessageBox.h
static void Register_MessageBox(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_MessageBox(methods);
    const char* asClassName = "MessageBox";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Model | File: ../Graphics/Model.h
static void Register_Model(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Model(methods);
    const char* asClassName = "Model";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ModelMorph(methods);
    const char* asClassName = "ModelMorph";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Mutex(methods);
    const char* asClassName = "Mutex";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_MutexLock(methods);
    const char* asClassName = "MutexLock";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class NamedPipe | File: ../IO/NamedPipe.h
static void Register_NamedPipe(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_NamedPipe(methods);
    const char* asClassName = "NamedPipe";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_NetworkState(methods);
    const char* asClassName = "NetworkState";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Node | File: ../Scene/Node.h
static void Register_Node(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Node(methods);
    const char* asClassName = "Node";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_NodeImpl(methods);
    const char* asClassName = "NodeImpl";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_NodeReplicationState(methods);
    const char* asClassName = "NodeReplicationState";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Object | File: ../Core/Object.h
static void Register_Object(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Object(methods);
    const char* asClassName = "Object";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ObjectAnimation | File: ../Scene/ObjectAnimation.h
static void Register_ObjectAnimation(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ObjectAnimation(methods);
    const char* asClassName = "ObjectAnimation";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ObjectFactory | File: ../Core/Object.h
static void Register_ObjectFactory(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ObjectFactory(methods);
    const char* asClassName = "ObjectFactory";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_OcclusionBatch(methods);
    const char* asClassName = "OcclusionBatch";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class OcclusionBuffer | File: ../Graphics/OcclusionBuffer.h
static void Register_OcclusionBuffer(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_OcclusionBuffer(methods);
    const char* asClassName = "OcclusionBuffer";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_OcclusionBufferData(methods);
    const char* asClassName = "OcclusionBufferData";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Octree | File: ../Graphics/Octree.h
static void Register_Octree(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Octree(methods);
    const char* asClassName = "Octree";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_OctreeQueryResult(methods);
    const char* asClassName = "OctreeQueryResult";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class OggVorbisSoundStream | File: ../Audio/OggVorbisSoundStream.h
static void Register_OggVorbisSoundStream(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_OggVorbisSoundStream(methods);
    const char* asClassName = "OggVorbisSoundStream";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct PackageEntry | File: ../IO/PackageFile.h
static void Register_PackageEntry(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_PackageEntry(methods);
    const char* asClassName = "PackageEntry";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class PackageFile | File: ../IO/PackageFile.h
static void Register_PackageFile(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_PackageFile(methods);
    const char* asClassName = "PackageFile";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Particle(methods);
    const char* asClassName = "Particle";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ParticleEffect | File: ../Graphics/ParticleEffect.h
static void Register_ParticleEffect(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ParticleEffect(methods);
    const char* asClassName = "ParticleEffect";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ParticleEmitter | File: ../Graphics/ParticleEmitter.h
static void Register_ParticleEmitter(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ParticleEmitter(methods);
    const char* asClassName = "ParticleEmitter";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Pass | File: ../Graphics/Technique.h
static void Register_Pass(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Pass(methods);
    const char* asClassName = "Pass";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_PerThreadSceneResult(methods);
    const char* asClassName = "PerThreadSceneResult";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Plane | File: ../Math/Plane.h
static void Register_Plane(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Plane(methods);
    const char* asClassName = "Plane";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Polyhedron(methods);
    const char* asClassName = "Polyhedron";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Profiler | File: ../Core/Profiler.h
static void Register_Profiler(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Profiler(methods);
    const char* asClassName = "Profiler";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ProgressBar | File: ../UI/ProgressBar.h
static void Register_ProgressBar(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ProgressBar(methods);
    const char* asClassName = "ProgressBar";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Quaternion | File: ../Math/Quaternion.h
static void Register_Quaternion(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Quaternion(methods);
    const char* asClassName = "Quaternion";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Ray | File: ../Math/Ray.h
static void Register_Ray(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Ray(methods);
    const char* asClassName = "Ray";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_RayQueryResult(methods);
    const char* asClassName = "RayQueryResult";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Rect | File: ../Math/Rect.h
static void Register_Rect(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Rect(methods);
    const char* asClassName = "Rect";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_RefCount(methods);
    const char* asClassName = "RefCount";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class RefCounted | File: ../Container/RefCounted.h
static void Register_RefCounted(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_RefCounted(methods);
    const char* asClassName = "RefCounted";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class RenderPath | File: ../Graphics/RenderPath.h
static void Register_RenderPath(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_RenderPath(methods);
    const char* asClassName = "RenderPath";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_RenderPathCommand(methods);
    const char* asClassName = "RenderPathCommand";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class RenderSurface | File: ../Graphics/RenderSurface.h
static void Register_RenderSurface(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_RenderSurface(methods);
    const char* asClassName = "RenderSurface";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_RenderTargetInfo(methods);
    const char* asClassName = "RenderTargetInfo";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Renderer | File: ../Graphics/Renderer.h
static void Register_Renderer(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Renderer(methods);
    const char* asClassName = "Renderer";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ReplicationState(methods);
    const char* asClassName = "ReplicationState";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Resource | File: ../Resource/Resource.h
static void Register_Resource(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Resource(methods);
    const char* asClassName = "Resource";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ResourceCache | File: ../Resource/ResourceCache.h
static void Register_ResourceCache(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ResourceCache(methods);
    const char* asClassName = "ResourceCache";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ResourceGroup(methods);
    const char* asClassName = "ResourceGroup";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ResourceRef(methods);
    const char* asClassName = "ResourceRef";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ResourceRefList(methods);
    const char* asClassName = "ResourceRefList";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ResourceWithMetadata | File: ../Resource/Resource.h
static void Register_ResourceWithMetadata(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ResourceWithMetadata(methods);
    const char* asClassName = "ResourceWithMetadata";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class RibbonTrail | File: ../Graphics/RibbonTrail.h
static void Register_RibbonTrail(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_RibbonTrail(methods);
    const char* asClassName = "RibbonTrail";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Scene | File: ../Scene/Scene.h
static void Register_Scene(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Scene(methods);
    const char* asClassName = "Scene";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ScenePassInfo(methods);
    const char* asClassName = "ScenePassInfo";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_SceneReplicationState(methods);
    const char* asClassName = "SceneReplicationState";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_SceneResolver(methods);
    const char* asClassName = "SceneResolver";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ScratchBuffer(methods);
    const char* asClassName = "ScratchBuffer";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ScreenModeParams(methods);
    const char* asClassName = "ScreenModeParams";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ScrollBar | File: ../UI/ScrollBar.h
static void Register_ScrollBar(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ScrollBar(methods);
    const char* asClassName = "ScrollBar";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ScrollView | File: ../UI/ScrollView.h
static void Register_ScrollView(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ScrollView(methods);
    const char* asClassName = "ScrollView";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Serializable | File: ../Scene/Serializable.h
static void Register_Serializable(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Serializable(methods);
    const char* asClassName = "Serializable";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Serializer | File: ../IO/Serializer.h
static void Register_Serializer(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Serializer(methods);
    const char* asClassName = "Serializer";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Shader | File: ../Graphics/Shader.h
static void Register_Shader(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Shader(methods);
    const char* asClassName = "Shader";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ShaderParameter(methods);
    const char* asClassName = "ShaderParameter";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ShaderParameterAnimationInfo | File: ../Graphics/Material.h
static void Register_ShaderParameterAnimationInfo(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ShaderParameterAnimationInfo(methods);
    const char* asClassName = "ShaderParameterAnimationInfo";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ShaderPrecache | File: ../Graphics/ShaderPrecache.h
static void Register_ShaderPrecache(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ShaderPrecache(methods);
    const char* asClassName = "ShaderPrecache";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ShaderVariation | File: ../Graphics/ShaderVariation.h
static void Register_ShaderVariation(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ShaderVariation(methods);
    const char* asClassName = "ShaderVariation";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ShadowBatchQueue(methods);
    const char* asClassName = "ShadowBatchQueue";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Skeleton | File: ../Graphics/Skeleton.h
static void Register_Skeleton(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Skeleton(methods);
    const char* asClassName = "Skeleton";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Skybox | File: ../Graphics/Skybox.h
static void Register_Skybox(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Skybox(methods);
    const char* asClassName = "Skybox";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Slider | File: ../UI/Slider.h
static void Register_Slider(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Slider(methods);
    const char* asClassName = "Slider";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class SmoothedTransform | File: ../Scene/SmoothedTransform.h
static void Register_SmoothedTransform(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_SmoothedTransform(methods);
    const char* asClassName = "SmoothedTransform";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Sound | File: ../Audio/Sound.h
static void Register_Sound(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Sound(methods);
    const char* asClassName = "Sound";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class SoundListener | File: ../Audio/SoundListener.h
static void Register_SoundListener(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_SoundListener(methods);
    const char* asClassName = "SoundListener";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class SoundSource | File: ../Audio/SoundSource.h
static void Register_SoundSource(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_SoundSource(methods);
    const char* asClassName = "SoundSource";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class SoundSource3D | File: ../Audio/SoundSource3D.h
static void Register_SoundSource3D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_SoundSource3D(methods);
    const char* asClassName = "SoundSource3D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class SoundStream | File: ../Audio/SoundStream.h
static void Register_SoundStream(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_SoundStream(methods);
    const char* asClassName = "SoundStream";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_SourceBatch(methods);
    const char* asClassName = "SourceBatch";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Sphere | File: ../Math/Sphere.h
static void Register_Sphere(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Sphere(methods);
    const char* asClassName = "Sphere";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Spline(methods);
    const char* asClassName = "Spline";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class SplinePath | File: ../Scene/SplinePath.h
static void Register_SplinePath(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_SplinePath(methods);
    const char* asClassName = "SplinePath";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Sprite | File: ../UI/Sprite.h
static void Register_Sprite(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Sprite(methods);
    const char* asClassName = "Sprite";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class StaticModel | File: ../Graphics/StaticModel.h
static void Register_StaticModel(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_StaticModel(methods);
    const char* asClassName = "StaticModel";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_StaticModelGeometryData(methods);
    const char* asClassName = "StaticModelGeometryData";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class StaticModelGroup | File: ../Graphics/StaticModelGroup.h
static void Register_StaticModelGroup(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_StaticModelGroup(methods);
    const char* asClassName = "StaticModelGroup";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_StoredLogMessage(methods);
    const char* asClassName = "StoredLogMessage";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_String(methods);
    const char* asClassName = "String";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class StringHash | File: ../Math/StringHash.h
static void Register_StringHash(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_StringHash(methods);
    const char* asClassName = "StringHash";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_StringHashRegister(methods);
    const char* asClassName = "StringHashRegister";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Technique | File: ../Graphics/Technique.h
static void Register_Technique(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Technique(methods);
    const char* asClassName = "Technique";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TechniqueEntry(methods);
    const char* asClassName = "TechniqueEntry";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Terrain | File: ../Graphics/Terrain.h
static void Register_Terrain(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Terrain(methods);
    const char* asClassName = "Terrain";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class TerrainPatch | File: ../Graphics/TerrainPatch.h
static void Register_TerrainPatch(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TerrainPatch(methods);
    const char* asClassName = "TerrainPatch";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Text | File: ../UI/Text.h
static void Register_Text(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Text(methods);
    const char* asClassName = "Text";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Text3D | File: ../UI/Text3D.h
static void Register_Text3D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Text3D(methods);
    const char* asClassName = "Text3D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Texture | File: ../Graphics/Texture.h
static void Register_Texture(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Texture(methods);
    const char* asClassName = "Texture";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Texture2D | File: ../Graphics/Texture2D.h
static void Register_Texture2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Texture2D(methods);
    const char* asClassName = "Texture2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Texture2DArray | File: ../Graphics/Texture2DArray.h
static void Register_Texture2DArray(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Texture2DArray(methods);
    const char* asClassName = "Texture2DArray";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Texture3D | File: ../Graphics/Texture3D.h
static void Register_Texture3D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Texture3D(methods);
    const char* asClassName = "Texture3D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class TextureCube | File: ../Graphics/TextureCube.h
static void Register_TextureCube(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TextureCube(methods);
    const char* asClassName = "TextureCube";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct TextureFrame | File: ../Graphics/ParticleEffect.h
static void Register_TextureFrame(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TextureFrame(methods);
    const char* asClassName = "TextureFrame";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Time | File: ../Core/Timer.h
static void Register_Time(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Time(methods);
    const char* asClassName = "Time";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Timer | File: ../Core/Timer.h
static void Register_Timer(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Timer(methods);
    const char* asClassName = "Timer";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ToolTip | File: ../UI/ToolTip.h
static void Register_ToolTip(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ToolTip(methods);
    const char* asClassName = "ToolTip";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct TouchState | File: ../Input/Input.h
static void Register_TouchState(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TouchState(methods);
    const char* asClassName = "TouchState";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TrailPoint(methods);
    const char* asClassName = "TrailPoint";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class UI | File: ../UI/UI.h
static void Register_UI(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_UI(methods);
    const char* asClassName = "UI";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_UIBatch(methods);
    const char* asClassName = "UIBatch";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class UIComponent | File: ../UI/UIComponent.h
static void Register_UIComponent(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_UIComponent(methods);
    const char* asClassName = "UIComponent";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class UIElement | File: ../UI/UIElement.h
static void Register_UIElement(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_UIElement(methods);
    const char* asClassName = "UIElement";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class UISelectable | File: ../UI/UISelectable.h
static void Register_UISelectable(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_UISelectable(methods);
    const char* asClassName = "UISelectable";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class UnknownComponent | File: ../Scene/UnknownComponent.h
static void Register_UnknownComponent(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_UnknownComponent(methods);
    const char* asClassName = "UnknownComponent";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_VAnimEventFrame(methods);
    const char* asClassName = "VAnimEventFrame";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_VAnimKeyFrame(methods);
    const char* asClassName = "VAnimKeyFrame";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ValueAnimation | File: ../Scene/ValueAnimation.h
static void Register_ValueAnimation(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ValueAnimation(methods);
    const char* asClassName = "ValueAnimation";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ValueAnimationInfo | File: ../Scene/ValueAnimationInfo.h
static void Register_ValueAnimationInfo(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ValueAnimationInfo(methods);
    const char* asClassName = "ValueAnimationInfo";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Variant(methods);
    const char* asClassName = "Variant";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Vector2 | File: ../Math/Vector2.h
static void Register_Vector2(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Vector2(methods);
    const char* asClassName = "Vector2";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Vector3 | File: ../Math/Vector3.h
static void Register_Vector3(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Vector3(methods);
    const char* asClassName = "Vector3";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Vector4 | File: ../Math/Vector4.h
static void Register_Vector4(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Vector4(methods);
    const char* asClassName = "Vector4";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_VectorBase(methods);
    const char* asClassName = "VectorBase";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_VectorBuffer(methods);
    const char* asClassName = "VectorBuffer";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class VertexBuffer | File: ../Graphics/VertexBuffer.h
static void Register_VertexBuffer(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_VertexBuffer(methods);
    const char* asClassName = "VertexBuffer";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_VertexBufferDesc(methods);
    const char* asClassName = "VertexBufferDesc";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_VertexBufferMorph(methods);
    const char* asClassName = "VertexBufferMorph";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_VertexElement(methods);
    const char* asClassName = "VertexElement";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class View | File: ../Graphics/View.h
static void Register_View(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_View(methods);
    const char* asClassName = "View";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class View3D | File: ../UI/View3D.h
static void Register_View3D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_View3D(methods);
    const char* asClassName = "View3D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Viewport | File: ../Graphics/Viewport.h
static void Register_Viewport(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Viewport(methods);
    const char* asClassName = "Viewport";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Window | File: ../UI/Window.h
static void Register_Window(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Window(methods);
    const char* asClassName = "Window";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_WindowModeParams(methods);
    const char* asClassName = "WindowModeParams";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class WorkQueue | File: ../Core/WorkQueue.h
static void Register_WorkQueue(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_WorkQueue(methods);
    const char* asClassName = "WorkQueue";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_XMLElement(methods);
    const char* asClassName = "XMLElement";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class XMLFile | File: ../Resource/XMLFile.h
static void Register_XMLFile(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_XMLFile(methods);
    const char* asClassName = "XMLFile";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_XPathQuery(methods);
    const char* asClassName = "XPathQuery";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_XPathResultSet(methods);
    const char* asClassName = "XPathResultSet";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Zone | File: ../Graphics/Zone.h
static void Register_Zone(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Zone(methods);
    const char* asClassName = "Zone";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

#ifdef URHO3D_DATABASE

// class Database | File: ../Database/Database.h
static void Register_Database(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Database(methods);
    const char* asClassName = "Database";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

#endif // def URHO3D_DATABASE

#ifdef URHO3D_IK

// class IKConstraint | File: ../IK/IKConstraint.h
static void Register_IKConstraint(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_IKConstraint(methods);
    const char* asClassName = "IKConstraint";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class IKEffector | File: ../IK/IKEffector.h
static void Register_IKEffector(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_IKEffector(methods);
    const char* asClassName = "IKEffector";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class IKSolver | File: ../IK/IKSolver.h
static void Register_IKSolver(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_IKSolver(methods);
    const char* asClassName = "IKSolver";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

#endif // def URHO3D_IK

#ifdef URHO3D_NAVIGATION

// class CrowdAgent | File: ../Navigation/CrowdAgent.h
static void Register_CrowdAgent(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CrowdAgent(methods);
    const char* asClassName = "CrowdAgent";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class CrowdManager | File: ../Navigation/CrowdManager.h
static void Register_CrowdManager(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CrowdManager(methods);
    const char* asClassName = "CrowdManager";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct CrowdObstacleAvoidanceParams | File: ../Navigation/CrowdManager.h
static void Register_CrowdObstacleAvoidanceParams(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CrowdObstacleAvoidanceParams(methods);
    const char* asClassName = "CrowdObstacleAvoidanceParams";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class DynamicNavigationMesh | File: ../Navigation/DynamicNavigationMesh.h
static void Register_DynamicNavigationMesh(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_DynamicNavigationMesh(methods);
    const char* asClassName = "DynamicNavigationMesh";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class NavArea | File: ../Navigation/NavArea.h
static void Register_NavArea(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_NavArea(methods);
    const char* asClassName = "NavArea";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_NavAreaStub(methods);
    const char* asClassName = "NavAreaStub";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_NavBuildData(methods);
    const char* asClassName = "NavBuildData";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Navigable | File: ../Navigation/Navigable.h
static void Register_Navigable(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Navigable(methods);
    const char* asClassName = "Navigable";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_NavigationGeometryInfo(methods);
    const char* asClassName = "NavigationGeometryInfo";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class NavigationMesh | File: ../Navigation/NavigationMesh.h
static void Register_NavigationMesh(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_NavigationMesh(methods);
    const char* asClassName = "NavigationMesh";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_NavigationPathPoint(methods);
    const char* asClassName = "NavigationPathPoint";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Obstacle | File: ../Navigation/Obstacle.h
static void Register_Obstacle(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Obstacle(methods);
    const char* asClassName = "Obstacle";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class OffMeshConnection | File: ../Navigation/OffMeshConnection.h
static void Register_OffMeshConnection(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_OffMeshConnection(methods);
    const char* asClassName = "OffMeshConnection";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_SimpleNavBuildData(methods);
    const char* asClassName = "SimpleNavBuildData";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

#endif // def URHO3D_NAVIGATION

#ifdef URHO3D_NETWORK

// class Connection | File: ../Network/Connection.h
static void Register_Connection(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Connection(methods);
    const char* asClassName = "Connection";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class HttpRequest | File: ../Network/HttpRequest.h
static void Register_HttpRequest(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_HttpRequest(methods);
    const char* asClassName = "HttpRequest";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Network | File: ../Network/Network.h
static void Register_Network(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Network(methods);
    const char* asClassName = "Network";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class NetworkPriority | File: ../Network/NetworkPriority.h
static void Register_NetworkPriority(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_NetworkPriority(methods);
    const char* asClassName = "NetworkPriority";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_PackageDownload(methods);
    const char* asClassName = "PackageDownload";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_PackageUpload(methods);
    const char* asClassName = "PackageUpload";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_RemoteEvent(methods);
    const char* asClassName = "RemoteEvent";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

#endif // def URHO3D_NETWORK

#ifdef URHO3D_PHYSICS

// struct CollisionGeometryData | File: ../Physics/CollisionShape.h
static void Register_CollisionGeometryData(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CollisionGeometryData(methods);
    const char* asClassName = "CollisionGeometryData";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class CollisionShape | File: ../Physics/CollisionShape.h
static void Register_CollisionShape(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CollisionShape(methods);
    const char* asClassName = "CollisionShape";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Constraint | File: ../Physics/Constraint.h
static void Register_Constraint(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Constraint(methods);
    const char* asClassName = "Constraint";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct ConvexData | File: ../Physics/CollisionShape.h
static void Register_ConvexData(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ConvexData(methods);
    const char* asClassName = "ConvexData";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_DelayedWorldTransform(methods);
    const char* asClassName = "DelayedWorldTransform";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct GImpactMeshData | File: ../Physics/CollisionShape.h
static void Register_GImpactMeshData(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_GImpactMeshData(methods);
    const char* asClassName = "GImpactMeshData";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct HeightfieldData | File: ../Physics/CollisionShape.h
static void Register_HeightfieldData(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_HeightfieldData(methods);
    const char* asClassName = "HeightfieldData";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ManifoldPair(methods);
    const char* asClassName = "ManifoldPair";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_PhysicsRaycastResult(methods);
    const char* asClassName = "PhysicsRaycastResult";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class PhysicsWorld | File: ../Physics/PhysicsWorld.h
static void Register_PhysicsWorld(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_PhysicsWorld(methods);
    const char* asClassName = "PhysicsWorld";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_PhysicsWorldConfig(methods);
    const char* asClassName = "PhysicsWorldConfig";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class RaycastVehicle | File: ../Physics/RaycastVehicle.h
static void Register_RaycastVehicle(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_RaycastVehicle(methods);
    const char* asClassName = "RaycastVehicle";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class RigidBody | File: ../Physics/RigidBody.h
static void Register_RigidBody(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_RigidBody(methods);
    const char* asClassName = "RigidBody";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct TriangleMeshData | File: ../Physics/CollisionShape.h
static void Register_TriangleMeshData(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TriangleMeshData(methods);
    const char* asClassName = "TriangleMeshData";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

#endif // def URHO3D_PHYSICS

#ifdef URHO3D_URHO2D

// class AnimatedSprite2D | File: ../Urho2D/AnimatedSprite2D.h
static void Register_AnimatedSprite2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AnimatedSprite2D(methods);
    const char* asClassName = "AnimatedSprite2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class AnimationSet2D | File: ../Urho2D/AnimationSet2D.h
static void Register_AnimationSet2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_AnimationSet2D(methods);
    const char* asClassName = "AnimationSet2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class CollisionBox2D | File: ../Urho2D/CollisionBox2D.h
static void Register_CollisionBox2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CollisionBox2D(methods);
    const char* asClassName = "CollisionBox2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class CollisionChain2D | File: ../Urho2D/CollisionChain2D.h
static void Register_CollisionChain2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CollisionChain2D(methods);
    const char* asClassName = "CollisionChain2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class CollisionCircle2D | File: ../Urho2D/CollisionCircle2D.h
static void Register_CollisionCircle2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CollisionCircle2D(methods);
    const char* asClassName = "CollisionCircle2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class CollisionEdge2D | File: ../Urho2D/CollisionEdge2D.h
static void Register_CollisionEdge2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CollisionEdge2D(methods);
    const char* asClassName = "CollisionEdge2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class CollisionPolygon2D | File: ../Urho2D/CollisionPolygon2D.h
static void Register_CollisionPolygon2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CollisionPolygon2D(methods);
    const char* asClassName = "CollisionPolygon2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class CollisionShape2D | File: ../Urho2D/CollisionShape2D.h
static void Register_CollisionShape2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_CollisionShape2D(methods);
    const char* asClassName = "CollisionShape2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Constraint2D | File: ../Urho2D/Constraint2D.h
static void Register_Constraint2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Constraint2D(methods);
    const char* asClassName = "Constraint2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ConstraintDistance2D | File: ../Urho2D/ConstraintDistance2D.h
static void Register_ConstraintDistance2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ConstraintDistance2D(methods);
    const char* asClassName = "ConstraintDistance2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ConstraintFriction2D | File: ../Urho2D/ConstraintFriction2D.h
static void Register_ConstraintFriction2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ConstraintFriction2D(methods);
    const char* asClassName = "ConstraintFriction2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ConstraintGear2D | File: ../Urho2D/ConstraintGear2D.h
static void Register_ConstraintGear2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ConstraintGear2D(methods);
    const char* asClassName = "ConstraintGear2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ConstraintMotor2D | File: ../Urho2D/ConstraintMotor2D.h
static void Register_ConstraintMotor2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ConstraintMotor2D(methods);
    const char* asClassName = "ConstraintMotor2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ConstraintMouse2D | File: ../Urho2D/ConstraintMouse2D.h
static void Register_ConstraintMouse2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ConstraintMouse2D(methods);
    const char* asClassName = "ConstraintMouse2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ConstraintPrismatic2D | File: ../Urho2D/ConstraintPrismatic2D.h
static void Register_ConstraintPrismatic2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ConstraintPrismatic2D(methods);
    const char* asClassName = "ConstraintPrismatic2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ConstraintPulley2D | File: ../Urho2D/ConstraintPulley2D.h
static void Register_ConstraintPulley2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ConstraintPulley2D(methods);
    const char* asClassName = "ConstraintPulley2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ConstraintRevolute2D | File: ../Urho2D/ConstraintRevolute2D.h
static void Register_ConstraintRevolute2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ConstraintRevolute2D(methods);
    const char* asClassName = "ConstraintRevolute2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ConstraintRope2D | File: ../Urho2D/ConstraintRope2D.h
static void Register_ConstraintRope2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ConstraintRope2D(methods);
    const char* asClassName = "ConstraintRope2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ConstraintWeld2D | File: ../Urho2D/ConstraintWeld2D.h
static void Register_ConstraintWeld2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ConstraintWeld2D(methods);
    const char* asClassName = "ConstraintWeld2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ConstraintWheel2D | File: ../Urho2D/ConstraintWheel2D.h
static void Register_ConstraintWheel2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ConstraintWheel2D(methods);
    const char* asClassName = "ConstraintWheel2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_DelayedWorldTransform2D(methods);
    const char* asClassName = "DelayedWorldTransform2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Drawable2D | File: ../Urho2D/Drawable2D.h
static void Register_Drawable2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Drawable2D(methods);
    const char* asClassName = "Drawable2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Particle2D(methods);
    const char* asClassName = "Particle2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ParticleEffect2D | File: ../Urho2D/ParticleEffect2D.h
static void Register_ParticleEffect2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ParticleEffect2D(methods);
    const char* asClassName = "ParticleEffect2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class ParticleEmitter2D | File: ../Urho2D/ParticleEmitter2D.h
static void Register_ParticleEmitter2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_ParticleEmitter2D(methods);
    const char* asClassName = "ParticleEmitter2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_PhysicsRaycastResult2D(methods);
    const char* asClassName = "PhysicsRaycastResult2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class PhysicsWorld2D | File: ../Urho2D/PhysicsWorld2D.h
static void Register_PhysicsWorld2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_PhysicsWorld2D(methods);
    const char* asClassName = "PhysicsWorld2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class PropertySet2D | File: ../Urho2D/TileMapDefs2D.h
static void Register_PropertySet2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_PropertySet2D(methods);
    const char* asClassName = "PropertySet2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Renderer2D | File: ../Urho2D/Renderer2D.h
static void Register_Renderer2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Renderer2D(methods);
    const char* asClassName = "Renderer2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class RigidBody2D | File: ../Urho2D/RigidBody2D.h
static void Register_RigidBody2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_RigidBody2D(methods);
    const char* asClassName = "RigidBody2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_SourceBatch2D(methods);
    const char* asClassName = "SourceBatch2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Sprite2D | File: ../Urho2D/Sprite2D.h
static void Register_Sprite2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Sprite2D(methods);
    const char* asClassName = "Sprite2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class SpriteSheet2D | File: ../Urho2D/SpriteSheet2D.h
static void Register_SpriteSheet2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_SpriteSheet2D(methods);
    const char* asClassName = "SpriteSheet2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class StaticSprite2D | File: ../Urho2D/StaticSprite2D.h
static void Register_StaticSprite2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_StaticSprite2D(methods);
    const char* asClassName = "StaticSprite2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class StretchableSprite2D | File: ../Urho2D/StretchableSprite2D.h
static void Register_StretchableSprite2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_StretchableSprite2D(methods);
    const char* asClassName = "StretchableSprite2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class Tile2D | File: ../Urho2D/TileMapDefs2D.h
static void Register_Tile2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Tile2D(methods);
    const char* asClassName = "Tile2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class TileMap2D | File: ../Urho2D/TileMap2D.h
static void Register_TileMap2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TileMap2D(methods);
    const char* asClassName = "TileMap2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// struct TileMapInfo2D | File: ../Urho2D/TileMapDefs2D.h
static void Register_TileMapInfo2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TileMapInfo2D(methods);
    const char* asClassName = "TileMapInfo2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class TileMapLayer2D | File: ../Urho2D/TileMapLayer2D.h
static void Register_TileMapLayer2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TileMapLayer2D(methods);
    const char* asClassName = "TileMapLayer2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class TileMapObject2D | File: ../Urho2D/TileMapDefs2D.h
static void Register_TileMapObject2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TileMapObject2D(methods);
    const char* asClassName = "TileMapObject2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class TmxFile2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxFile2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TmxFile2D(methods);
    const char* asClassName = "TmxFile2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class TmxImageLayer2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxImageLayer2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TmxImageLayer2D(methods);
    const char* asClassName = "TmxImageLayer2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class TmxLayer2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxLayer2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TmxLayer2D(methods);
    const char* asClassName = "TmxLayer2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class TmxObjectGroup2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxObjectGroup2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TmxObjectGroup2D(methods);
    const char* asClassName = "TmxObjectGroup2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

// class TmxTileLayer2D | File: ../Urho2D/TmxFile2D.h
static void Register_TmxTileLayer2D(asIScriptEngine* engine)
{
    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_TmxTileLayer2D(methods);
    const char* asClassName = "TmxTileLayer2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
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

    Vector<RegisterObjectMethodArgs> methods;
    CollectMembers_Vertex2D(methods);
    const char* asClassName = "Vertex2D";
    //for (const RegisterObjectMethodArgs& method : methods)
    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);
}

#endif // def URHO3D_URHO2D

void ASRegisterGeneratedClasses(asIScriptEngine* engine)
{
    Register_AbstractFile(engine);
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
    Register_AttributeInfo(engine);
    Register_Audio(engine);
    Register_BackgroundLoadItem(engine);
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
    Register_EventProfiler(engine);
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
    Register_GPUObject(engine);
    Register_Geometry(engine);
    Register_GeometryDesc(engine);
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
    Register_Polyhedron(engine);
    Register_Profiler(engine);
    Register_ProgressBar(engine);
    Register_Quaternion(engine);
    Register_Ray(engine);
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
    Register_Window(engine);
    Register_WindowModeParams(engine);
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
#endif
}

}
