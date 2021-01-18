// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

#ifdef URHO3D_IK
// explicit IKConstraint::IKConstraint(Context* context) | File: ../IK/IKConstraint.h
static IKConstraint* IKConstraint_IKConstraint_Context()
{
    return new IKConstraint(GetScriptContext());
}
#endif

#ifdef URHO3D_IK
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void IKConstraint_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(IKConstraint* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}
#endif

#ifdef URHO3D_IK
// explicit IKEffector::IKEffector(Context* context) | File: ../IK/IKEffector.h
static IKEffector* IKEffector_IKEffector_Context()
{
    return new IKEffector(GetScriptContext());
}
#endif

#ifdef URHO3D_IK
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void IKEffector_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(IKEffector* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}
#endif

#ifdef URHO3D_IK
// explicit IKSolver::IKSolver(Context* context) | File: ../IK/IKSolver.h
static IKSolver* IKSolver_IKSolver_Context()
{
    return new IKSolver(GetScriptContext());
}
#endif

#ifdef URHO3D_IK
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void IKSolver_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(IKSolver* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}
#endif

// SharedPtr<Image> Image::ConvertToRGBA() const | File: ../Resource/Image.h
static Image* Image_ConvertToRGBA_void(Image* ptr)
{
    SharedPtr<Image> result = ptr->ConvertToRGBA();
    return result.Detach();
}

// SharedPtr<Image> Image::GetDecompressedImage() const | File: ../Resource/Image.h
static Image* Image_GetDecompressedImage_void(Image* ptr)
{
    SharedPtr<Image> result = ptr->GetDecompressedImage();
    return result.Detach();
}

// SharedPtr<Image> Image::GetNextLevel() const | File: ../Resource/Image.h
static Image* Image_GetNextLevel_void(Image* ptr)
{
    SharedPtr<Image> result = ptr->GetNextLevel();
    return result.Detach();
}

// SharedPtr<Image> Image::GetNextSibling() const | File: ../Resource/Image.h
static Image* Image_GetNextSibling_void(Image* ptr)
{
    SharedPtr<Image> result = ptr->GetNextSibling();
    return result.Detach();
}

// explicit Image::Image(Context* context) | File: ../Resource/Image.h
static Image* Image_Image_Context()
{
    return new Image(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Image_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Image* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// explicit IndexBuffer::IndexBuffer(Context* context, bool forceHeadless=false) | File: ../Graphics/IndexBuffer.h
static IndexBuffer* IndexBuffer_IndexBuffer_Context_bool(bool forceHeadless=false)
{
    return new IndexBuffer(GetScriptContext(), forceHeadless);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void IndexBuffer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(IndexBuffer* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// explicit Input::Input(Context* context) | File: ../Input/Input.h
static Input* Input_Input_Context()
{
    return new Input(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Input_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Input* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// IntRect::IntRect(const IntVector2& min, const IntVector2& max) noexcept | File: ../Math/Rect.h
static void IntRect_IntRect_IntVector2_IntVector2(IntRect* ptr, const IntVector2 &min, const IntVector2 &max)
{
    new(ptr) IntRect(min, max);
}

// IntRect::IntRect(int left, int top, int right, int bottom) noexcept | File: ../Math/Rect.h
static void IntRect_IntRect_int_int_int_int(IntRect* ptr, int left, int top, int right, int bottom)
{
    new(ptr) IntRect(left, top, right, bottom);
}

// IntVector2::IntVector2(int x, int y) noexcept | File: ../Math/Vector2.h
static void IntVector2_IntVector2_int_int(IntVector2* ptr, int x, int y)
{
    new(ptr) IntVector2(x, y);
}

// IntVector2::IntVector2(const IntVector2& rhs) noexcept=default | File: ../Math/Vector2.h
static void IntVector2_IntVector2_IntVector2(IntVector2* ptr, const IntVector2 &rhs)
{
    new(ptr) IntVector2(rhs);
}

// IntVector3::IntVector3(int x, int y, int z) noexcept | File: ../Math/Vector3.h
static void IntVector3_IntVector3_int_int_int(IntVector3* ptr, int x, int y, int z)
{
    new(ptr) IntVector3(x, y, z);
}

// IntVector3::IntVector3(const IntVector3& rhs) noexcept=default | File: ../Math/Vector3.h
static void IntVector3_IntVector3_IntVector3(IntVector3* ptr, const IntVector3 &rhs)
{
    new(ptr) IntVector3(rhs);
}

void ASRegisterGenerated_Members_I(asIScriptEngine* engine)
{
#ifdef URHO3D_IK
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("IKConstraint", asBEHAVE_ADDREF, "void f()", asMETHODPR(IKConstraint, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void AllocateNetworkState()", asMETHODPR(IKConstraint, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void ApplyAttributes()", asMETHODPR(IKConstraint, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(IKConstraint, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "bool GetAnimationEnabled() const", asMETHODPR(IKConstraint, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "bool get_animationEnabled() const", asMETHODPR(IKConstraint, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "Variant GetAttribute(uint) const", asMETHODPR(IKConstraint, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "Variant get_attributes(uint) const", asMETHODPR(IKConstraint, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "Variant GetAttribute(const String&in) const", asMETHODPR(IKConstraint, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(IKConstraint, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(IKConstraint, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(IKConstraint, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(IKConstraint, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "Variant GetAttributeDefault(uint) const", asMETHODPR(IKConstraint, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "Variant get_attributeDefaults(uint) const", asMETHODPR(IKConstraint, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(IKConstraint, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "bool GetBlockEvents() const", asMETHODPR(IKConstraint, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "const String& GetCategory() const", asMETHODPR(IKConstraint, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "const String& get_category() const", asMETHODPR(IKConstraint, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "Component@+ GetComponent(StringHash) const", asMETHODPR(IKConstraint, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "VariantMap& GetEventDataMap() const", asMETHODPR(IKConstraint, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "Object@+ GetEventSender() const", asMETHODPR(IKConstraint, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(IKConstraint, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "const Variant& get_globalVar(StringHash) const", asMETHODPR(IKConstraint, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "const VariantMap& GetGlobalVars() const", asMETHODPR(IKConstraint, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "const VariantMap& get_globalVars() const", asMETHODPR(IKConstraint, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "uint GetID() const", asMETHODPR(IKConstraint, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "uint get_id() const", asMETHODPR(IKConstraint, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(IKConstraint, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const Vector2& IKConstraint::GetLengthConstraints() const | File: ../IK/IKConstraint.h
    engine->RegisterObjectMethod("IKConstraint", "const Vector2& GetLengthConstraints() const", asMETHODPR(IKConstraint, GetLengthConstraints, () const, const Vector2&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "Node@+ GetNode() const", asMETHODPR(IKConstraint, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "Node@+ get_node() const", asMETHODPR(IKConstraint, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "uint GetNumAttributes() const", asMETHODPR(IKConstraint, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "uint get_numAttributes() const", asMETHODPR(IKConstraint, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "uint GetNumNetworkAttributes() const", asMETHODPR(IKConstraint, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(IKConstraint, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(IKConstraint, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(IKConstraint, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "Scene@+ GetScene() const", asMETHODPR(IKConstraint, GetScene, () const, Scene*), asCALL_THISCALL);
    // float IKConstraint::GetStiffness() const | File: ../IK/IKConstraint.h
    engine->RegisterObjectMethod("IKConstraint", "float GetStiffness() const", asMETHODPR(IKConstraint, GetStiffness, () const, float), asCALL_THISCALL);
    // float IKConstraint::GetStretchiness() const | File: ../IK/IKConstraint.h
    engine->RegisterObjectMethod("IKConstraint", "float GetStretchiness() const", asMETHODPR(IKConstraint, GetStretchiness, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(IKConstraint, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "StringHash GetType() const", asMETHODPR(IKConstraint, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "StringHash get_type() const", asMETHODPR(IKConstraint, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "const String& GetTypeName() const", asMETHODPR(IKConstraint, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "const String& get_typeName() const", asMETHODPR(IKConstraint, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "bool HasEventHandlers() const", asMETHODPR(IKConstraint, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(IKConstraint, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(IKConstraint, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // explicit IKConstraint::IKConstraint(Context* context) | File: ../IK/IKConstraint.h
    engine->RegisterObjectBehaviour("IKConstraint", asBEHAVE_FACTORY, "IKConstraint@+ f()", asFUNCTION(IKConstraint_IKConstraint_Context), asCALL_CDECL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "bool IsEnabled() const", asMETHODPR(IKConstraint, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "bool get_enabled() const", asMETHODPR(IKConstraint, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "bool IsEnabledEffective() const", asMETHODPR(IKConstraint, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "bool get_enabledEffective() const", asMETHODPR(IKConstraint, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "bool IsInstanceOf(StringHash) const", asMETHODPR(IKConstraint, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "bool IsReplicated() const", asMETHODPR(IKConstraint, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "bool get_replicated() const", asMETHODPR(IKConstraint, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool IsTemporary() const", asMETHODPR(IKConstraint, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "bool get_temporary() const", asMETHODPR(IKConstraint, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool Load(Deserializer&)", asMETHODPR(IKConstraint, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "bool LoadJSON(const JSONValue&in)", asMETHODPR(IKConstraint, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "bool LoadXML(const XMLElement&in)", asMETHODPR(IKConstraint, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "void MarkNetworkUpdate()", asMETHODPR(IKConstraint, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(IKConstraint, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(IKConstraint, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(IKConstraint, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "void OnSetEnabled()", asMETHODPR(IKConstraint, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "void PrepareNetworkUpdate()", asMETHODPR(IKConstraint, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(IKConstraint, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(IKConstraint, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IKConstraint", "int Refs() const", asMETHODPR(IKConstraint, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "int get_refs() const", asMETHODPR(IKConstraint, Refs, () const, int), asCALL_THISCALL);
    // static void IKConstraint::RegisterObject(Context* context) | File: ../IK/IKConstraint.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("IKConstraint", asBEHAVE_RELEASE, "void f()", asMETHODPR(IKConstraint, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "void Remove()", asMETHODPR(IKConstraint, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(IKConstraint, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void RemoveInstanceDefault()", asMETHODPR(IKConstraint, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void RemoveObjectAnimation()", asMETHODPR(IKConstraint, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void ResetToDefault()", asMETHODPR(IKConstraint, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "bool Save(Serializer&) const", asMETHODPR(IKConstraint, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool SaveDefaultAttributes() const", asMETHODPR(IKConstraint, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "bool SaveJSON(JSONValue&) const", asMETHODPR(IKConstraint, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "bool SaveXML(XMLElement&) const", asMETHODPR(IKConstraint, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void SendEvent(StringHash)", asMETHODPR(IKConstraint, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(IKConstraint, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetAnimationEnabled(bool)", asMETHODPR(IKConstraint, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "void set_animationEnabled(bool)", asMETHODPR(IKConstraint, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetAnimationTime(float)", asMETHODPR(IKConstraint, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(IKConstraint, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "bool set_attributes(uint, const Variant&in)", asMETHODPR(IKConstraint, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(IKConstraint, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(IKConstraint, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(IKConstraint, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(IKConstraint, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(IKConstraint, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void SetBlockEvents(bool)", asMETHODPR(IKConstraint, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "void SetEnabled(bool)", asMETHODPR(IKConstraint, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "void set_enabled(bool)", asMETHODPR(IKConstraint, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(IKConstraint, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(IKConstraint, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetInstanceDefault(bool)", asMETHODPR(IKConstraint, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(IKConstraint, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void IKConstraint::SetLengthConstraints(const Vector2& lengthConstraints) | File: ../IK/IKConstraint.h
    engine->RegisterObjectMethod("IKConstraint", "void SetLengthConstraints(const Vector2&in)", asMETHODPR(IKConstraint, SetLengthConstraints, (const Vector2&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(IKConstraint, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(IKConstraint, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(IKConstraint, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void IKConstraint::SetStiffness(float stiffness) | File: ../IK/IKConstraint.h
    engine->RegisterObjectMethod("IKConstraint", "void SetStiffness(float)", asMETHODPR(IKConstraint, SetStiffness, (float), void), asCALL_THISCALL);
    // void IKConstraint::SetStretchiness(float stretchiness) | File: ../IK/IKConstraint.h
    engine->RegisterObjectMethod("IKConstraint", "void SetStretchiness(float)", asMETHODPR(IKConstraint, SetStretchiness, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetTemporary(bool)", asMETHODPR(IKConstraint, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "void set_temporary(bool)", asMETHODPR(IKConstraint, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void UnsubscribeFromAllEvents()", asMETHODPR(IKConstraint, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(IKConstraint_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(IKConstraint, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(IKConstraint, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(IKConstraint, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IKConstraint", "int WeakRefs() const", asMETHODPR(IKConstraint, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "int get_weakRefs() const", asMETHODPR(IKConstraint, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(IKConstraint, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(IKConstraint, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(IKConstraint, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(IKConstraint, "IKConstraint")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(IKConstraint, "IKConstraint")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(IKConstraint, "IKConstraint")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(IKConstraint, "IKConstraint")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(IKConstraint, "IKConstraint")
#endif
#ifdef REGISTER_MANUAL_PART_IKConstraint
    REGISTER_MANUAL_PART_IKConstraint(IKConstraint, "IKConstraint")
#endif
    RegisterSubclass<Component, IKConstraint>(engine, "Component", "IKConstraint");
    RegisterSubclass<Animatable, IKConstraint>(engine, "Animatable", "IKConstraint");
    RegisterSubclass<Serializable, IKConstraint>(engine, "Serializable", "IKConstraint");
    RegisterSubclass<Object, IKConstraint>(engine, "Object", "IKConstraint");
    RegisterSubclass<RefCounted, IKConstraint>(engine, "RefCounted", "IKConstraint");
#endif

#ifdef URHO3D_IK
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("IKEffector", asBEHAVE_ADDREF, "void f()", asMETHODPR(IKEffector, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void AllocateNetworkState()", asMETHODPR(IKEffector, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void ApplyAttributes()", asMETHODPR(IKEffector, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void IKEffector::DrawDebugGeometry(bool depthTest) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void DrawDebugGeometry(bool)", asMETHODPR(IKEffector, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
    // void IKEffector::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(IKEffector, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "bool GetAnimationEnabled() const", asMETHODPR(IKEffector, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "bool get_animationEnabled() const", asMETHODPR(IKEffector, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "Variant GetAttribute(uint) const", asMETHODPR(IKEffector, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "Variant get_attributes(uint) const", asMETHODPR(IKEffector, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "Variant GetAttribute(const String&in) const", asMETHODPR(IKEffector, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(IKEffector, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(IKEffector, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(IKEffector, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(IKEffector, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "Variant GetAttributeDefault(uint) const", asMETHODPR(IKEffector, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "Variant get_attributeDefaults(uint) const", asMETHODPR(IKEffector, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(IKEffector, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "bool GetBlockEvents() const", asMETHODPR(IKEffector, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "const String& GetCategory() const", asMETHODPR(IKEffector, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "const String& get_category() const", asMETHODPR(IKEffector, GetCategory, () const, const String&), asCALL_THISCALL);
    // unsigned IKEffector::GetChainLength() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "uint GetChainLength() const", asMETHODPR(IKEffector, GetChainLength, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "uint get_chainLength() const", asMETHODPR(IKEffector, GetChainLength, () const, unsigned), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "Component@+ GetComponent(StringHash) const", asMETHODPR(IKEffector, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "VariantMap& GetEventDataMap() const", asMETHODPR(IKEffector, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "Object@+ GetEventSender() const", asMETHODPR(IKEffector, GetEventSender, () const, Object*), asCALL_THISCALL);
    // bool IKEffector::GetFeature(Feature feature) const | File: ../IK/IKEffector.h
    // Not registered because have @nobind mark
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(IKEffector, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "const Variant& get_globalVar(StringHash) const", asMETHODPR(IKEffector, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "const VariantMap& GetGlobalVars() const", asMETHODPR(IKEffector, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "const VariantMap& get_globalVars() const", asMETHODPR(IKEffector, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "uint GetID() const", asMETHODPR(IKEffector, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "uint get_id() const", asMETHODPR(IKEffector, GetID, () const, unsigned), asCALL_THISCALL);
    // bool IKEffector::GetINHERIT_PARENT_ROTATION() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "bool GetINHERIT_PARENT_ROTATION() const", asMETHODPR(IKEffector, GetINHERIT_PARENT_ROTATION, () const, bool), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(IKEffector, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "Node@+ GetNode() const", asMETHODPR(IKEffector, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "Node@+ get_node() const", asMETHODPR(IKEffector, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "uint GetNumAttributes() const", asMETHODPR(IKEffector, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "uint get_numAttributes() const", asMETHODPR(IKEffector, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "uint GetNumNetworkAttributes() const", asMETHODPR(IKEffector, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(IKEffector, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(IKEffector, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(IKEffector, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float IKEffector::GetRotationDecay() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "float GetRotationDecay() const", asMETHODPR(IKEffector, GetRotationDecay, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "float get_rotationDecay() const", asMETHODPR(IKEffector, GetRotationDecay, () const, float), asCALL_THISCALL);
    // float IKEffector::GetRotationWeight() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "float GetRotationWeight() const", asMETHODPR(IKEffector, GetRotationWeight, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "float get_rotationWeight() const", asMETHODPR(IKEffector, GetRotationWeight, () const, float), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "Scene@+ GetScene() const", asMETHODPR(IKEffector, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(IKEffector, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const String& IKEffector::GetTargetName() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "const String& GetTargetName() const", asMETHODPR(IKEffector, GetTargetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "const String& get_targetName() const", asMETHODPR(IKEffector, GetTargetName, () const, const String&), asCALL_THISCALL);
    // Node* IKEffector::GetTargetNode() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "Node@+ GetTargetNode() const", asMETHODPR(IKEffector, GetTargetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "Node@+ get_targetNode() const", asMETHODPR(IKEffector, GetTargetNode, () const, Node*), asCALL_THISCALL);
    // const Vector3& IKEffector::GetTargetPosition() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "const Vector3& GetTargetPosition() const", asMETHODPR(IKEffector, GetTargetPosition, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "const Vector3& get_targetPosition() const", asMETHODPR(IKEffector, GetTargetPosition, () const, const Vector3&), asCALL_THISCALL);
    // const Quaternion& IKEffector::GetTargetRotation() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "const Quaternion& GetTargetRotation() const", asMETHODPR(IKEffector, GetTargetRotation, () const, const Quaternion&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "const Quaternion& get_targetRotation() const", asMETHODPR(IKEffector, GetTargetRotation, () const, const Quaternion&), asCALL_THISCALL);
    // Vector3 IKEffector::GetTargetRotationEuler() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "Vector3 GetTargetRotationEuler() const", asMETHODPR(IKEffector, GetTargetRotationEuler, () const, Vector3), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "StringHash GetType() const", asMETHODPR(IKEffector, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "StringHash get_type() const", asMETHODPR(IKEffector, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "const String& GetTypeName() const", asMETHODPR(IKEffector, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "const String& get_typeName() const", asMETHODPR(IKEffector, GetTypeName, () const, const String&), asCALL_THISCALL);
    // float IKEffector::GetWeight() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "float GetWeight() const", asMETHODPR(IKEffector, GetWeight, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "float get_weight() const", asMETHODPR(IKEffector, GetWeight, () const, float), asCALL_THISCALL);
    // bool IKEffector::GetWEIGHT_NLERP() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "bool GetWEIGHT_NLERP() const", asMETHODPR(IKEffector, GetWEIGHT_NLERP, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "bool HasEventHandlers() const", asMETHODPR(IKEffector, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(IKEffector, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(IKEffector, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // explicit IKEffector::IKEffector(Context* context) | File: ../IK/IKEffector.h
    engine->RegisterObjectBehaviour("IKEffector", asBEHAVE_FACTORY, "IKEffector@+ f()", asFUNCTION(IKEffector_IKEffector_Context), asCALL_CDECL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "bool IsEnabled() const", asMETHODPR(IKEffector, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "bool get_enabled() const", asMETHODPR(IKEffector, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "bool IsEnabledEffective() const", asMETHODPR(IKEffector, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "bool get_enabledEffective() const", asMETHODPR(IKEffector, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "bool IsInstanceOf(StringHash) const", asMETHODPR(IKEffector, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "bool IsReplicated() const", asMETHODPR(IKEffector, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "bool get_replicated() const", asMETHODPR(IKEffector, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool IsTemporary() const", asMETHODPR(IKEffector, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "bool get_temporary() const", asMETHODPR(IKEffector, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool Load(Deserializer&)", asMETHODPR(IKEffector, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "bool LoadJSON(const JSONValue&in)", asMETHODPR(IKEffector, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "bool LoadXML(const XMLElement&in)", asMETHODPR(IKEffector, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "void MarkNetworkUpdate()", asMETHODPR(IKEffector, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(IKEffector, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(IKEffector, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(IKEffector, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "void OnSetEnabled()", asMETHODPR(IKEffector, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "void PrepareNetworkUpdate()", asMETHODPR(IKEffector, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(IKEffector, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(IKEffector, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IKEffector", "int Refs() const", asMETHODPR(IKEffector, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "int get_refs() const", asMETHODPR(IKEffector, Refs, () const, int), asCALL_THISCALL);
    // static void IKEffector::RegisterObject(Context* context) | File: ../IK/IKEffector.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("IKEffector", asBEHAVE_RELEASE, "void f()", asMETHODPR(IKEffector, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "void Remove()", asMETHODPR(IKEffector, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(IKEffector, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void RemoveInstanceDefault()", asMETHODPR(IKEffector, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void RemoveObjectAnimation()", asMETHODPR(IKEffector, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void ResetToDefault()", asMETHODPR(IKEffector, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "bool Save(Serializer&) const", asMETHODPR(IKEffector, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool SaveDefaultAttributes() const", asMETHODPR(IKEffector, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "bool SaveJSON(JSONValue&) const", asMETHODPR(IKEffector, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "bool SaveXML(XMLElement&) const", asMETHODPR(IKEffector, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void SendEvent(StringHash)", asMETHODPR(IKEffector, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(IKEffector, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetAnimationEnabled(bool)", asMETHODPR(IKEffector, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_animationEnabled(bool)", asMETHODPR(IKEffector, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetAnimationTime(float)", asMETHODPR(IKEffector, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(IKEffector, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "bool set_attributes(uint, const Variant&in)", asMETHODPR(IKEffector, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(IKEffector, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(IKEffector, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(IKEffector, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(IKEffector, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(IKEffector, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void SetBlockEvents(bool)", asMETHODPR(IKEffector, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void IKEffector::SetChainLength(unsigned chainLength) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetChainLength(uint)", asMETHODPR(IKEffector, SetChainLength, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_chainLength(uint)", asMETHODPR(IKEffector, SetChainLength, (unsigned), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "void SetEnabled(bool)", asMETHODPR(IKEffector, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_enabled(bool)", asMETHODPR(IKEffector, SetEnabled, (bool), void), asCALL_THISCALL);
    // void IKEffector::SetFeature(Feature feature, bool enable) | File: ../IK/IKEffector.h
    // Not registered because have @nobind mark
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(IKEffector, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(IKEffector, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void IKEffector::SetINHERIT_PARENT_ROTATION(bool enable) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetINHERIT_PARENT_ROTATION(bool)", asMETHODPR(IKEffector, SetINHERIT_PARENT_ROTATION, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void SetInstanceDefault(bool)", asMETHODPR(IKEffector, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(IKEffector, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(IKEffector, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(IKEffector, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(IKEffector, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void IKEffector::SetRotationDecay(float decay) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetRotationDecay(float)", asMETHODPR(IKEffector, SetRotationDecay, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_rotationDecay(float)", asMETHODPR(IKEffector, SetRotationDecay, (float), void), asCALL_THISCALL);
    // void IKEffector::SetRotationWeight(float weight) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetRotationWeight(float)", asMETHODPR(IKEffector, SetRotationWeight, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_rotationWeight(float)", asMETHODPR(IKEffector, SetRotationWeight, (float), void), asCALL_THISCALL);
    // void IKEffector::SetTargetName(const String& nodeName) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetTargetName(const String&in)", asMETHODPR(IKEffector, SetTargetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_targetName(const String&in)", asMETHODPR(IKEffector, SetTargetName, (const String&), void), asCALL_THISCALL);
    // void IKEffector::SetTargetNode(Node* targetNode) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetTargetNode(Node@+)", asMETHODPR(IKEffector, SetTargetNode, (Node*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_targetNode(Node@+)", asMETHODPR(IKEffector, SetTargetNode, (Node*), void), asCALL_THISCALL);
    // void IKEffector::SetTargetPosition(const Vector3& targetPosition) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetTargetPosition(const Vector3&in)", asMETHODPR(IKEffector, SetTargetPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_targetPosition(const Vector3&in)", asMETHODPR(IKEffector, SetTargetPosition, (const Vector3&), void), asCALL_THISCALL);
    // void IKEffector::SetTargetRotation(const Quaternion& targetRotation) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetTargetRotation(const Quaternion&in)", asMETHODPR(IKEffector, SetTargetRotation, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_targetRotation(const Quaternion&in)", asMETHODPR(IKEffector, SetTargetRotation, (const Quaternion&), void), asCALL_THISCALL);
    // void IKEffector::SetTargetRotationEuler(const Vector3& targetRotation) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetTargetRotationEuler(const Vector3&in)", asMETHODPR(IKEffector, SetTargetRotationEuler, (const Vector3&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void SetTemporary(bool)", asMETHODPR(IKEffector, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_temporary(bool)", asMETHODPR(IKEffector, SetTemporary, (bool), void), asCALL_THISCALL);
    // void IKEffector::SetWeight(float weight) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetWeight(float)", asMETHODPR(IKEffector, SetWeight, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_weight(float)", asMETHODPR(IKEffector, SetWeight, (float), void), asCALL_THISCALL);
    // void IKEffector::SetWEIGHT_NLERP(bool enable) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetWEIGHT_NLERP(bool)", asMETHODPR(IKEffector, SetWEIGHT_NLERP, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void UnsubscribeFromAllEvents()", asMETHODPR(IKEffector, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(IKEffector_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(IKEffector, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(IKEffector, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(IKEffector, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IKEffector", "int WeakRefs() const", asMETHODPR(IKEffector, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "int get_weakRefs() const", asMETHODPR(IKEffector, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(IKEffector, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(IKEffector, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(IKEffector, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(IKEffector, "IKEffector")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(IKEffector, "IKEffector")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(IKEffector, "IKEffector")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(IKEffector, "IKEffector")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(IKEffector, "IKEffector")
#endif
#ifdef REGISTER_MANUAL_PART_IKEffector
    REGISTER_MANUAL_PART_IKEffector(IKEffector, "IKEffector")
#endif
    RegisterSubclass<Component, IKEffector>(engine, "Component", "IKEffector");
    RegisterSubclass<Animatable, IKEffector>(engine, "Animatable", "IKEffector");
    RegisterSubclass<Serializable, IKEffector>(engine, "Serializable", "IKEffector");
    RegisterSubclass<Object, IKEffector>(engine, "Object", "IKEffector");
    RegisterSubclass<RefCounted, IKEffector>(engine, "RefCounted", "IKEffector");
#endif

#ifdef URHO3D_IK
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("IKSolver", asBEHAVE_ADDREF, "void f()", asMETHODPR(IKSolver, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void AllocateNetworkState()", asMETHODPR(IKSolver, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void IKSolver::ApplyActivePoseToScene() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void ApplyActivePoseToScene()", asMETHODPR(IKSolver, ApplyActivePoseToScene, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void ApplyAttributes()", asMETHODPR(IKSolver, ApplyAttributes, (), void), asCALL_THISCALL);
    // void IKSolver::ApplyOriginalPoseToActivePose() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void ApplyOriginalPoseToActivePose()", asMETHODPR(IKSolver, ApplyOriginalPoseToActivePose, (), void), asCALL_THISCALL);
    // void IKSolver::ApplyOriginalPoseToScene() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void ApplyOriginalPoseToScene()", asMETHODPR(IKSolver, ApplyOriginalPoseToScene, (), void), asCALL_THISCALL);
    // void IKSolver::ApplySceneToActivePose() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void ApplySceneToActivePose()", asMETHODPR(IKSolver, ApplySceneToActivePose, (), void), asCALL_THISCALL);
    // void IKSolver::ApplySceneToOriginalPose() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void ApplySceneToOriginalPose()", asMETHODPR(IKSolver, ApplySceneToOriginalPose, (), void), asCALL_THISCALL);
    // void IKSolver::CalculateJointRotations() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void CalculateJointRotations()", asMETHODPR(IKSolver, CalculateJointRotations, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void IKSolver::DrawDebugGeometry(bool depthTest) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void DrawDebugGeometry(bool)", asMETHODPR(IKSolver, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
    // void IKSolver::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(IKSolver, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // Algorithm IKSolver::GetAlgorithm() const | File: ../IK/IKSolver.h
    // Not registered because have @manualbind mark
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "bool GetAnimationEnabled() const", asMETHODPR(IKSolver, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_animationEnabled() const", asMETHODPR(IKSolver, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "Variant GetAttribute(uint) const", asMETHODPR(IKSolver, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "Variant get_attributes(uint) const", asMETHODPR(IKSolver, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "Variant GetAttribute(const String&in) const", asMETHODPR(IKSolver, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(IKSolver, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(IKSolver, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(IKSolver, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(IKSolver, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "Variant GetAttributeDefault(uint) const", asMETHODPR(IKSolver, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "Variant get_attributeDefaults(uint) const", asMETHODPR(IKSolver, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(IKSolver, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool IKSolver::GetAUTO_SOLVE() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "bool GetAUTO_SOLVE() const", asMETHODPR(IKSolver, GetAUTO_SOLVE, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_AUTO_SOLVE() const", asMETHODPR(IKSolver, GetAUTO_SOLVE, () const, bool), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "bool GetBlockEvents() const", asMETHODPR(IKSolver, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "const String& GetCategory() const", asMETHODPR(IKSolver, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "const String& get_category() const", asMETHODPR(IKSolver, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "Component@+ GetComponent(StringHash) const", asMETHODPR(IKSolver, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // bool IKSolver::GetCONSTRAINTS() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "bool GetCONSTRAINTS() const", asMETHODPR(IKSolver, GetCONSTRAINTS, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_CONSTRAINTS() const", asMETHODPR(IKSolver, GetCONSTRAINTS, () const, bool), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "VariantMap& GetEventDataMap() const", asMETHODPR(IKSolver, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "Object@+ GetEventSender() const", asMETHODPR(IKSolver, GetEventSender, () const, Object*), asCALL_THISCALL);
    // bool IKSolver::GetFeature(Feature feature) const | File: ../IK/IKSolver.h
    // Not registered because have @nobind mark
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(IKSolver, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "const Variant& get_globalVar(StringHash) const", asMETHODPR(IKSolver, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "const VariantMap& GetGlobalVars() const", asMETHODPR(IKSolver, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "const VariantMap& get_globalVars() const", asMETHODPR(IKSolver, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "uint GetID() const", asMETHODPR(IKSolver, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "uint get_id() const", asMETHODPR(IKSolver, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(IKSolver, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // bool IKSolver::GetJOINT_ROTATIONS() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "bool GetJOINT_ROTATIONS() const", asMETHODPR(IKSolver, GetJOINT_ROTATIONS, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_JOINT_ROTATIONS() const", asMETHODPR(IKSolver, GetJOINT_ROTATIONS, () const, bool), asCALL_THISCALL);
    // unsigned IKSolver::GetMaximumIterations() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "uint GetMaximumIterations() const", asMETHODPR(IKSolver, GetMaximumIterations, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "uint get_maximumIterations() const", asMETHODPR(IKSolver, GetMaximumIterations, () const, unsigned), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "Node@+ GetNode() const", asMETHODPR(IKSolver, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "Node@+ get_node() const", asMETHODPR(IKSolver, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "uint GetNumAttributes() const", asMETHODPR(IKSolver, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "uint get_numAttributes() const", asMETHODPR(IKSolver, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "uint GetNumNetworkAttributes() const", asMETHODPR(IKSolver, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(IKSolver, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(IKSolver, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(IKSolver, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "Scene@+ GetScene() const", asMETHODPR(IKSolver, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(IKSolver, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // bool IKSolver::GetTARGET_ROTATIONS() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "bool GetTARGET_ROTATIONS() const", asMETHODPR(IKSolver, GetTARGET_ROTATIONS, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_TARGET_ROTATIONS() const", asMETHODPR(IKSolver, GetTARGET_ROTATIONS, () const, bool), asCALL_THISCALL);
    // float IKSolver::GetTolerance() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "float GetTolerance() const", asMETHODPR(IKSolver, GetTolerance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "float get_tolerance() const", asMETHODPR(IKSolver, GetTolerance, () const, float), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "StringHash GetType() const", asMETHODPR(IKSolver, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "StringHash get_type() const", asMETHODPR(IKSolver, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "const String& GetTypeName() const", asMETHODPR(IKSolver, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "const String& get_typeName() const", asMETHODPR(IKSolver, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool IKSolver::GetUPDATE_ACTIVE_POSE() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "bool GetUPDATE_ACTIVE_POSE() const", asMETHODPR(IKSolver, GetUPDATE_ACTIVE_POSE, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_UPDATE_ACTIVE_POSE() const", asMETHODPR(IKSolver, GetUPDATE_ACTIVE_POSE, () const, bool), asCALL_THISCALL);
    // bool IKSolver::GetUPDATE_ORIGINAL_POSE() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "bool GetUPDATE_ORIGINAL_POSE() const", asMETHODPR(IKSolver, GetUPDATE_ORIGINAL_POSE, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_UPDATE_ORIGINAL_POSE() const", asMETHODPR(IKSolver, GetUPDATE_ORIGINAL_POSE, () const, bool), asCALL_THISCALL);
    // bool IKSolver::GetUSE_ORIGINAL_POSE() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "bool GetUSE_ORIGINAL_POSE() const", asMETHODPR(IKSolver, GetUSE_ORIGINAL_POSE, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_USE_ORIGINAL_POSE() const", asMETHODPR(IKSolver, GetUSE_ORIGINAL_POSE, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "bool HasEventHandlers() const", asMETHODPR(IKSolver, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(IKSolver, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(IKSolver, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // explicit IKSolver::IKSolver(Context* context) | File: ../IK/IKSolver.h
    engine->RegisterObjectBehaviour("IKSolver", asBEHAVE_FACTORY, "IKSolver@+ f()", asFUNCTION(IKSolver_IKSolver_Context), asCALL_CDECL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "bool IsEnabled() const", asMETHODPR(IKSolver, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_enabled() const", asMETHODPR(IKSolver, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "bool IsEnabledEffective() const", asMETHODPR(IKSolver, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_enabledEffective() const", asMETHODPR(IKSolver, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "bool IsInstanceOf(StringHash) const", asMETHODPR(IKSolver, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "bool IsReplicated() const", asMETHODPR(IKSolver, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_replicated() const", asMETHODPR(IKSolver, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool IsTemporary() const", asMETHODPR(IKSolver, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_temporary() const", asMETHODPR(IKSolver, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool Load(Deserializer&)", asMETHODPR(IKSolver, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "bool LoadJSON(const JSONValue&in)", asMETHODPR(IKSolver, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "bool LoadXML(const XMLElement&in)", asMETHODPR(IKSolver, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "void MarkNetworkUpdate()", asMETHODPR(IKSolver, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(IKSolver, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(IKSolver, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(IKSolver, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "void OnSetEnabled()", asMETHODPR(IKSolver, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "void PrepareNetworkUpdate()", asMETHODPR(IKSolver, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(IKSolver, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(IKSolver, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // void IKSolver::RebuildChainTrees() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void RebuildChainTrees()", asMETHODPR(IKSolver, RebuildChainTrees, (), void), asCALL_THISCALL);
    // void IKSolver::RecalculateSegmentLengths() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void RecalculateSegmentLengths()", asMETHODPR(IKSolver, RecalculateSegmentLengths, (), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IKSolver", "int Refs() const", asMETHODPR(IKSolver, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "int get_refs() const", asMETHODPR(IKSolver, Refs, () const, int), asCALL_THISCALL);
    // static void IKSolver::RegisterObject(Context* context) | File: ../IK/IKSolver.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("IKSolver", asBEHAVE_RELEASE, "void f()", asMETHODPR(IKSolver, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "void Remove()", asMETHODPR(IKSolver, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(IKSolver, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void RemoveInstanceDefault()", asMETHODPR(IKSolver, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void RemoveObjectAnimation()", asMETHODPR(IKSolver, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void ResetToDefault()", asMETHODPR(IKSolver, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "bool Save(Serializer&) const", asMETHODPR(IKSolver, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool SaveDefaultAttributes() const", asMETHODPR(IKSolver, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "bool SaveJSON(JSONValue&) const", asMETHODPR(IKSolver, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "bool SaveXML(XMLElement&) const", asMETHODPR(IKSolver, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void SendEvent(StringHash)", asMETHODPR(IKSolver, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(IKSolver, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void IKSolver::SetAlgorithm(Algorithm algorithm) | File: ../IK/IKSolver.h
    // Not registered because have @manualbind mark
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetAnimationEnabled(bool)", asMETHODPR(IKSolver, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_animationEnabled(bool)", asMETHODPR(IKSolver, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetAnimationTime(float)", asMETHODPR(IKSolver, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(IKSolver, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool set_attributes(uint, const Variant&in)", asMETHODPR(IKSolver, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(IKSolver, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(IKSolver, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(IKSolver, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(IKSolver, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(IKSolver, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void IKSolver::SetAUTO_SOLVE(bool enable) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetAUTO_SOLVE(bool)", asMETHODPR(IKSolver, SetAUTO_SOLVE, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_AUTO_SOLVE(bool)", asMETHODPR(IKSolver, SetAUTO_SOLVE, (bool), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void SetBlockEvents(bool)", asMETHODPR(IKSolver, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void IKSolver::SetCONSTRAINTS(bool enable) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetCONSTRAINTS(bool)", asMETHODPR(IKSolver, SetCONSTRAINTS, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_CONSTRAINTS(bool)", asMETHODPR(IKSolver, SetCONSTRAINTS, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "void SetEnabled(bool)", asMETHODPR(IKSolver, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_enabled(bool)", asMETHODPR(IKSolver, SetEnabled, (bool), void), asCALL_THISCALL);
    // void IKSolver::SetFeature(Feature feature, bool enable) | File: ../IK/IKSolver.h
    // Not registered because have @nobind mark
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(IKSolver, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(IKSolver, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void SetInstanceDefault(bool)", asMETHODPR(IKSolver, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(IKSolver, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void IKSolver::SetJOINT_ROTATIONS(bool enable) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetJOINT_ROTATIONS(bool)", asMETHODPR(IKSolver, SetJOINT_ROTATIONS, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_JOINT_ROTATIONS(bool)", asMETHODPR(IKSolver, SetJOINT_ROTATIONS, (bool), void), asCALL_THISCALL);
    // void IKSolver::SetMaximumIterations(unsigned iterations) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetMaximumIterations(uint)", asMETHODPR(IKSolver, SetMaximumIterations, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_maximumIterations(uint)", asMETHODPR(IKSolver, SetMaximumIterations, (unsigned), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(IKSolver, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(IKSolver, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(IKSolver, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void IKSolver::SetTARGET_ROTATIONS(bool enable) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetTARGET_ROTATIONS(bool)", asMETHODPR(IKSolver, SetTARGET_ROTATIONS, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_TARGET_ROTATIONS(bool)", asMETHODPR(IKSolver, SetTARGET_ROTATIONS, (bool), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void SetTemporary(bool)", asMETHODPR(IKSolver, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_temporary(bool)", asMETHODPR(IKSolver, SetTemporary, (bool), void), asCALL_THISCALL);
    // void IKSolver::SetTolerance(float tolerance) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetTolerance(float)", asMETHODPR(IKSolver, SetTolerance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_tolerance(float)", asMETHODPR(IKSolver, SetTolerance, (float), void), asCALL_THISCALL);
    // void IKSolver::SetUPDATE_ACTIVE_POSE(bool enable) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetUPDATE_ACTIVE_POSE(bool)", asMETHODPR(IKSolver, SetUPDATE_ACTIVE_POSE, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_UPDATE_ACTIVE_POSE(bool)", asMETHODPR(IKSolver, SetUPDATE_ACTIVE_POSE, (bool), void), asCALL_THISCALL);
    // void IKSolver::SetUPDATE_ORIGINAL_POSE(bool enable) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetUPDATE_ORIGINAL_POSE(bool)", asMETHODPR(IKSolver, SetUPDATE_ORIGINAL_POSE, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_UPDATE_ORIGINAL_POSE(bool)", asMETHODPR(IKSolver, SetUPDATE_ORIGINAL_POSE, (bool), void), asCALL_THISCALL);
    // void IKSolver::SetUSE_ORIGINAL_POSE(bool enable) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetUSE_ORIGINAL_POSE(bool)", asMETHODPR(IKSolver, SetUSE_ORIGINAL_POSE, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_USE_ORIGINAL_POSE(bool)", asMETHODPR(IKSolver, SetUSE_ORIGINAL_POSE, (bool), void), asCALL_THISCALL);
    // void IKSolver::Solve() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void Solve()", asMETHODPR(IKSolver, Solve, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void UnsubscribeFromAllEvents()", asMETHODPR(IKSolver, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(IKSolver_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(IKSolver, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(IKSolver, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(IKSolver, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IKSolver", "int WeakRefs() const", asMETHODPR(IKSolver, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "int get_weakRefs() const", asMETHODPR(IKSolver, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(IKSolver, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(IKSolver, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(IKSolver, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(IKSolver, "IKSolver")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(IKSolver, "IKSolver")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(IKSolver, "IKSolver")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(IKSolver, "IKSolver")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(IKSolver, "IKSolver")
#endif
#ifdef REGISTER_MANUAL_PART_IKSolver
    REGISTER_MANUAL_PART_IKSolver(IKSolver, "IKSolver")
#endif
    RegisterSubclass<Component, IKSolver>(engine, "Component", "IKSolver");
    RegisterSubclass<Animatable, IKSolver>(engine, "Animatable", "IKSolver");
    RegisterSubclass<Serializable, IKSolver>(engine, "Serializable", "IKSolver");
    RegisterSubclass<Object, IKSolver>(engine, "Object", "IKSolver");
    RegisterSubclass<RefCounted, IKSolver>(engine, "RefCounted", "IKSolver");
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Image", asBEHAVE_ADDREF, "void f()", asMETHODPR(Image, AddRef, (), void), asCALL_THISCALL);
    // bool Image::BeginLoad(Deserializer& source) override | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool BeginLoad(Deserializer&)", asMETHODPR(Image, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Image::CleanupLevels() | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void CleanupLevels()", asMETHODPR(Image, CleanupLevels, (), void), asCALL_THISCALL);
    // void Image::Clear(const Color& color) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void Clear(const Color&in)", asMETHODPR(Image, Clear, (const Color&), void), asCALL_THISCALL);
    // void Image::ClearInt(unsigned uintColor) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void ClearInt(uint)", asMETHODPR(Image, ClearInt, (unsigned), void), asCALL_THISCALL);
    // SharedPtr<Image> Image::ConvertToRGBA() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Image@+ ConvertToRGBA() const", asFUNCTION(Image_ConvertToRGBA_void), asCALL_CDECL_OBJFIRST);
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "bool EndLoad()", asMETHODPR(Image, EndLoad, (), bool), asCALL_THISCALL);
    // bool Image::FlipHorizontal() | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool FlipHorizontal()", asMETHODPR(Image, FlipHorizontal, (), bool), asCALL_THISCALL);
    // bool Image::FlipVertical() | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool FlipVertical()", asMETHODPR(Image, FlipVertical, (), bool), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(Image, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "bool GetBlockEvents() const", asMETHODPR(Image, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "const String& GetCategory() const", asMETHODPR(Image, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "const String& get_category() const", asMETHODPR(Image, GetCategory, () const, const String&), asCALL_THISCALL);
    // unsigned Image::GetComponents() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "uint GetComponents() const", asMETHODPR(Image, GetComponents, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "uint get_components() const", asMETHODPR(Image, GetComponents, () const, unsigned), asCALL_THISCALL);
    // CompressedFormat Image::GetCompressedFormat() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "CompressedFormat GetCompressedFormat() const", asMETHODPR(Image, GetCompressedFormat, () const, CompressedFormat), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "CompressedFormat get_compressedFormat() const", asMETHODPR(Image, GetCompressedFormat, () const, CompressedFormat), asCALL_THISCALL);
    // CompressedLevel Image::GetCompressedLevel(unsigned index) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "CompressedLevel GetCompressedLevel(uint) const", asMETHODPR(Image, GetCompressedLevel, (unsigned) const, CompressedLevel), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // unsigned char* Image::GetData() const | File: ../Resource/Image.h
    // Error: type "unsigned char*" can not automatically bind
    // SharedPtr<Image> Image::GetDecompressedImage() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Image@+ GetDecompressedImage() const", asFUNCTION(Image_GetDecompressedImage_void), asCALL_CDECL_OBJFIRST);
    // int Image::GetDepth() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "int GetDepth() const", asMETHODPR(Image, GetDepth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_depth() const", asMETHODPR(Image, GetDepth, () const, int), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "VariantMap& GetEventDataMap() const", asMETHODPR(Image, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "Object@+ GetEventSender() const", asMETHODPR(Image, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Image, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Image, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "const VariantMap& GetGlobalVars() const", asMETHODPR(Image, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "const VariantMap& get_globalVars() const", asMETHODPR(Image, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int Image::GetHeight() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "int GetHeight() const", asMETHODPR(Image, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_height() const", asMETHODPR(Image, GetHeight, () const, int), asCALL_THISCALL);
    // void Image::GetLevels(PODVector<Image*>& levels) | File: ../Resource/Image.h
    // Error: type "PODVector<Image*>&" can not automatically bind
    // void Image::GetLevels(PODVector<const Image*>& levels) const | File: ../Resource/Image.h
    // Error: type "PODVector<const Image*>&" can not automatically bind
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "uint GetMemoryUse() const", asMETHODPR(Image, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "uint get_memoryUse() const", asMETHODPR(Image, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "const String& GetName() const", asMETHODPR(Image, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "const String& get_name() const", asMETHODPR(Image, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "StringHash GetNameHash() const", asMETHODPR(Image, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // SharedPtr<Image> Image::GetNextLevel() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Image@+ GetNextLevel() const", asFUNCTION(Image_GetNextLevel_void), asCALL_CDECL_OBJFIRST);
    // SharedPtr<Image> Image::GetNextSibling() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Image@+ GetNextSibling() const", asFUNCTION(Image_GetNextSibling_void), asCALL_CDECL_OBJFIRST);
    // unsigned Image::GetNumCompressedLevels() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "uint GetNumCompressedLevels() const", asMETHODPR(Image, GetNumCompressedLevels, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "uint get_numCompressedLevels() const", asMETHODPR(Image, GetNumCompressedLevels, () const, unsigned), asCALL_THISCALL);
    // Color Image::GetPixel(int x, int y) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Color GetPixel(int, int) const", asMETHODPR(Image, GetPixel, (int, int) const, Color), asCALL_THISCALL);
    // Color Image::GetPixel(int x, int y, int z) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Color GetPixel(int, int, int) const", asMETHODPR(Image, GetPixel, (int, int, int) const, Color), asCALL_THISCALL);
    // Color Image::GetPixelBilinear(float x, float y) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Color GetPixelBilinear(float, float) const", asMETHODPR(Image, GetPixelBilinear, (float, float) const, Color), asCALL_THISCALL);
    // unsigned Image::GetPixelInt(int x, int y) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "uint GetPixelInt(int, int) const", asMETHODPR(Image, GetPixelInt, (int, int) const, unsigned), asCALL_THISCALL);
    // unsigned Image::GetPixelInt(int x, int y, int z) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "uint GetPixelInt(int, int, int) const", asMETHODPR(Image, GetPixelInt, (int, int, int) const, unsigned), asCALL_THISCALL);
    // Color Image::GetPixelTrilinear(float x, float y, float z) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Color GetPixelTrilinear(float, float, float) const", asMETHODPR(Image, GetPixelTrilinear, (float, float, float) const, Color), asCALL_THISCALL);
    // SDL_Surface* Image::GetSDLSurface(const IntRect& rect=IntRect::ZERO) const | File: ../Resource/Image.h
    // Error: type "SDL_Surface*" can not automatically bind
    // Image* Image::GetSubimage(const IntRect& rect) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Image@+ GetSubimage(const IntRect&in) const", asMETHODPR(Image, GetSubimage, (const IntRect&) const, Image*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Image, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "StringHash GetType() const", asMETHODPR(Image, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "StringHash get_type() const", asMETHODPR(Image, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "const String& GetTypeName() const", asMETHODPR(Image, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "const String& get_typeName() const", asMETHODPR(Image, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "uint GetUseTimer()", asMETHODPR(Image, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "uint get_useTimer()", asMETHODPR(Image, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // int Image::GetWidth() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "int GetWidth() const", asMETHODPR(Image, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_width() const", asMETHODPR(Image, GetWidth, () const, int), asCALL_THISCALL);
    // bool Image::HasAlphaChannel() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool HasAlphaChannel() const", asMETHODPR(Image, HasAlphaChannel, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_hasAlphaChannel() const", asMETHODPR(Image, HasAlphaChannel, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "bool HasEventHandlers() const", asMETHODPR(Image, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Image, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Image, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // explicit Image::Image(Context* context) | File: ../Resource/Image.h
    engine->RegisterObjectBehaviour("Image", asBEHAVE_FACTORY, "Image@+ f()", asFUNCTION(Image_Image_Context), asCALL_CDECL);
    // bool Image::IsArray() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool IsArray() const", asMETHODPR(Image, IsArray, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_array() const", asMETHODPR(Image, IsArray, () const, bool), asCALL_THISCALL);
    // bool Image::IsCompressed() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool IsCompressed() const", asMETHODPR(Image, IsCompressed, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_compressed() const", asMETHODPR(Image, IsCompressed, () const, bool), asCALL_THISCALL);
    // bool Image::IsCubemap() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool IsCubemap() const", asMETHODPR(Image, IsCubemap, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_cubemap() const", asMETHODPR(Image, IsCubemap, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "bool IsInstanceOf(StringHash) const", asMETHODPR(Image, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Image::IsSRGB() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool IsSRGB() const", asMETHODPR(Image, IsSRGB, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_sRGB() const", asMETHODPR(Image, IsSRGB, () const, bool), asCALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "bool Load(Deserializer&)", asMETHODPR(Image, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Image::LoadColorLUT(Deserializer& source) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool LoadColorLUT(Deserializer&)", asMETHODPR(Image, LoadColorLUT, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "bool LoadFile(const String&in)", asMETHODPR(Image, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool Load(const String&in)", asMETHODPR(Image, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Image, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // void Image::PrecalculateLevels() | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void PrecalculateLevels()", asMETHODPR(Image, PrecalculateLevels, (), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Image", "int Refs() const", asMETHODPR(Image, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_refs() const", asMETHODPR(Image, Refs, () const, int), asCALL_THISCALL);
    // static void Image::RegisterObject(Context* context) | File: ../Resource/Image.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Image", asBEHAVE_RELEASE, "void f()", asMETHODPR(Image, ReleaseRef, (), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "void ResetUseTimer()", asMETHODPR(Image, ResetUseTimer, (), void), asCALL_THISCALL);
    // bool Image::Resize(int width, int height) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool Resize(int, int)", asMETHODPR(Image, Resize, (int, int), bool), asCALL_THISCALL);
    // bool Image::Save(Serializer& dest) const override | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool Save(Serializer&) const", asMETHODPR(Image, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // bool Image::SaveBMP(const String& fileName) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SaveBMP(const String&in) const", asMETHODPR(Image, SaveBMP, (const String&) const, bool), asCALL_THISCALL);
    // bool Image::SaveDDS(const String& fileName) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SaveDDS(const String&in) const", asMETHODPR(Image, SaveDDS, (const String&) const, bool), asCALL_THISCALL);
    // bool Image::SaveFile(const String& fileName) const override | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SaveFile(const String&in) const", asMETHODPR(Image, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool Save(const String&in) const", asMETHODPR(Image, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // bool Image::SaveJPG(const String& fileName, int quality) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SaveJPG(const String&in, int) const", asMETHODPR(Image, SaveJPG, (const String&, int) const, bool), asCALL_THISCALL);
    // bool Image::SavePNG(const String& fileName) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SavePNG(const String&in) const", asMETHODPR(Image, SavePNG, (const String&) const, bool), asCALL_THISCALL);
    // bool Image::SaveTGA(const String& fileName) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SaveTGA(const String&in) const", asMETHODPR(Image, SaveTGA, (const String&) const, bool), asCALL_THISCALL);
    // bool Image::SaveWEBP(const String& fileName, float compression=0.0f) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SaveWEBP(const String&in, float = 0.0f) const", asMETHODPR(Image, SaveWEBP, (const String&, float) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void SendEvent(StringHash)", asMETHODPR(Image, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Image, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(Image, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void SetBlockEvents(bool)", asMETHODPR(Image, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Image::SetData(const unsigned char* pixelData) | File: ../Resource/Image.h
    // Error: type "const unsigned char*" can not automatically bind
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Image, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Image, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "void SetMemoryUse(uint)", asMETHODPR(Image, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "void SetName(const String&in)", asMETHODPR(Image, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void set_name(const String&in)", asMETHODPR(Image, SetName, (const String&), void), asCALL_THISCALL);
    // void Image::SetPixel(int x, int y, const Color& color) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void SetPixel(int, int, const Color&in)", asMETHODPR(Image, SetPixel, (int, int, const Color&), void), asCALL_THISCALL);
    // void Image::SetPixel(int x, int y, int z, const Color& color) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void SetPixel(int, int, int, const Color&in)", asMETHODPR(Image, SetPixel, (int, int, int, const Color&), void), asCALL_THISCALL);
    // void Image::SetPixelInt(int x, int y, unsigned uintColor) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void SetPixelInt(int, int, uint)", asMETHODPR(Image, SetPixelInt, (int, int, unsigned), void), asCALL_THISCALL);
    // void Image::SetPixelInt(int x, int y, int z, unsigned uintColor) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void SetPixelInt(int, int, int, uint)", asMETHODPR(Image, SetPixelInt, (int, int, int, unsigned), void), asCALL_THISCALL);
    // bool Image::SetSize(int width, int height, unsigned components) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SetSize(int, int, uint)", asMETHODPR(Image, SetSize, (int, int, unsigned), bool), asCALL_THISCALL);
    // bool Image::SetSize(int width, int height, int depth, unsigned components) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SetSize(int, int, int, uint)", asMETHODPR(Image, SetSize, (int, int, int, unsigned), bool), asCALL_THISCALL);
    // bool Image::SetSubimage(const Image* image, const IntRect& rect) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SetSubimage(Image@+, const IntRect&in)", asMETHODPR(Image, SetSubimage, (const Image*, const IntRect&), bool), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void UnsubscribeFromAllEvents()", asMETHODPR(Image, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Image_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Image, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Image, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Image, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Image", "int WeakRefs() const", asMETHODPR(Image, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_weakRefs() const", asMETHODPR(Image, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(Image, "Image")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Image, "Image")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Image, "Image")
#endif
#ifdef REGISTER_MANUAL_PART_Image
    REGISTER_MANUAL_PART_Image(Image, "Image")
#endif
    RegisterSubclass<Resource, Image>(engine, "Resource", "Image");
    RegisterSubclass<Object, Image>(engine, "Object", "Image");
    RegisterSubclass<RefCounted, Image>(engine, "RefCounted", "Image");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("IndexBuffer", asBEHAVE_ADDREF, "void f()", asMETHODPR(IndexBuffer, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("IndexBuffer", "void ClearDataLost()", asMETHODPR(IndexBuffer, ClearDataLost, (), void), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "bool GetBlockEvents() const", asMETHODPR(IndexBuffer, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "const String& GetCategory() const", asMETHODPR(IndexBuffer, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "const String& get_category() const", asMETHODPR(IndexBuffer, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "VariantMap& GetEventDataMap() const", asMETHODPR(IndexBuffer, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "Object@+ GetEventSender() const", asMETHODPR(IndexBuffer, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(IndexBuffer, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "const Variant& get_globalVar(StringHash) const", asMETHODPR(IndexBuffer, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "const VariantMap& GetGlobalVars() const", asMETHODPR(IndexBuffer, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "const VariantMap& get_globalVars() const", asMETHODPR(IndexBuffer, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("IndexBuffer", "uint GetGPUObjectName() const", asMETHODPR(IndexBuffer, GetGPUObjectName, () const, unsigned), asCALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("IndexBuffer", "Graphics@+ GetGraphics() const", asMETHODPR(IndexBuffer, GetGraphics, () const, Graphics*), asCALL_THISCALL);
    // unsigned IndexBuffer::GetIndexCount() const | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "uint GetIndexCount() const", asMETHODPR(IndexBuffer, GetIndexCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "uint get_indexCount() const", asMETHODPR(IndexBuffer, GetIndexCount, () const, unsigned), asCALL_THISCALL);
    // unsigned IndexBuffer::GetIndexSize() const | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "uint GetIndexSize() const", asMETHODPR(IndexBuffer, GetIndexSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "uint get_indexSize() const", asMETHODPR(IndexBuffer, GetIndexSize, () const, unsigned), asCALL_THISCALL);
    // unsigned char* IndexBuffer::GetShadowData() const | File: ../Graphics/IndexBuffer.h
    // Error: type "unsigned char*" can not automatically bind
    // SharedArrayPtr<unsigned char> IndexBuffer::GetShadowDataShared() const | File: ../Graphics/IndexBuffer.h
    // Error: type "SharedArrayPtr<unsigned char>" can not automatically bind
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(IndexBuffer, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "StringHash GetType() const", asMETHODPR(IndexBuffer, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "StringHash get_type() const", asMETHODPR(IndexBuffer, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "const String& GetTypeName() const", asMETHODPR(IndexBuffer, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "const String& get_typeName() const", asMETHODPR(IndexBuffer, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool IndexBuffer::GetUsedVertexRange(unsigned start, unsigned count, unsigned& minVertex, unsigned& vertexCount) | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "bool GetUsedVertexRange(uint, uint, uint&, uint&)", asMETHODPR(IndexBuffer, GetUsedVertexRange, (unsigned, unsigned, unsigned&, unsigned&), bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "bool HasEventHandlers() const", asMETHODPR(IndexBuffer, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("IndexBuffer", "bool HasPendingData() const", asMETHODPR(IndexBuffer, HasPendingData, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(IndexBuffer, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(IndexBuffer, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // explicit IndexBuffer::IndexBuffer(Context* context, bool forceHeadless=false) | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectBehaviour("IndexBuffer", asBEHAVE_FACTORY, "IndexBuffer@+ f(bool = false)", asFUNCTION(IndexBuffer_IndexBuffer_Context_bool), asCALL_CDECL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("IndexBuffer", "bool IsDataLost() const", asMETHODPR(IndexBuffer, IsDataLost, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "bool get_dataLost() const", asMETHODPR(IndexBuffer, IsDataLost, () const, bool), asCALL_THISCALL);
    // bool IndexBuffer::IsDynamic() const | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "bool IsDynamic() const", asMETHODPR(IndexBuffer, IsDynamic, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "bool get_dynamic() const", asMETHODPR(IndexBuffer, IsDynamic, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "bool IsInstanceOf(StringHash) const", asMETHODPR(IndexBuffer, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool IndexBuffer::IsLocked() const | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "bool IsLocked() const", asMETHODPR(IndexBuffer, IsLocked, () const, bool), asCALL_THISCALL);
    // bool IndexBuffer::IsShadowed() const | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "bool IsShadowed() const", asMETHODPR(IndexBuffer, IsShadowed, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "bool get_shadowed() const", asMETHODPR(IndexBuffer, IsShadowed, () const, bool), asCALL_THISCALL);
    // void* IndexBuffer::Lock(unsigned start, unsigned count, bool discard=false) | File: ../Graphics/IndexBuffer.h
    // Error: type "void*" can not automatically bind
    // void IndexBuffer::OnDeviceLost() override | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "void OnDeviceLost()", asMETHODPR(IndexBuffer, OnDeviceLost, (), void), asCALL_THISCALL);
    // void IndexBuffer::OnDeviceReset() override | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "void OnDeviceReset()", asMETHODPR(IndexBuffer, OnDeviceReset, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(IndexBuffer, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IndexBuffer", "int Refs() const", asMETHODPR(IndexBuffer, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "int get_refs() const", asMETHODPR(IndexBuffer, Refs, () const, int), asCALL_THISCALL);
    // void IndexBuffer::Release() override | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "void Release()", asMETHODPR(IndexBuffer, Release, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("IndexBuffer", asBEHAVE_RELEASE, "void f()", asMETHODPR(IndexBuffer, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void SendEvent(StringHash)", asMETHODPR(IndexBuffer, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(IndexBuffer, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void SetBlockEvents(bool)", asMETHODPR(IndexBuffer, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // bool IndexBuffer::SetData(const void* data) | File: ../Graphics/IndexBuffer.h
    // Error: type "void*" can not automatically bind
    // bool IndexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard=false) | File: ../Graphics/IndexBuffer.h
    // Error: type "void*" can not automatically bind
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(IndexBuffer, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(IndexBuffer, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void IndexBuffer::SetShadowed(bool enable) | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "void SetShadowed(bool)", asMETHODPR(IndexBuffer, SetShadowed, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "void set_shadowed(bool)", asMETHODPR(IndexBuffer, SetShadowed, (bool), void), asCALL_THISCALL);
    // bool IndexBuffer::SetSize(unsigned indexCount, bool largeIndices, bool dynamic=false) | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "bool SetSize(uint, bool, bool = false)", asMETHODPR(IndexBuffer, SetSize, (unsigned, bool, bool), bool), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void IndexBuffer::Unlock() | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "void Unlock()", asMETHODPR(IndexBuffer, Unlock, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void UnsubscribeFromAllEvents()", asMETHODPR(IndexBuffer, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(IndexBuffer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(IndexBuffer, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(IndexBuffer, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(IndexBuffer, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IndexBuffer", "int WeakRefs() const", asMETHODPR(IndexBuffer, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "int get_weakRefs() const", asMETHODPR(IndexBuffer, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(IndexBuffer, "IndexBuffer")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(IndexBuffer, "IndexBuffer")
#endif
#ifdef REGISTER_MANUAL_PART_GPUObject
    REGISTER_MANUAL_PART_GPUObject(IndexBuffer, "IndexBuffer")
#endif
#ifdef REGISTER_MANUAL_PART_IndexBuffer
    REGISTER_MANUAL_PART_IndexBuffer(IndexBuffer, "IndexBuffer")
#endif
    RegisterSubclass<Object, IndexBuffer>(engine, "Object", "IndexBuffer");
    RegisterSubclass<RefCounted, IndexBuffer>(engine, "RefCounted", "IndexBuffer");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Input", asBEHAVE_ADDREF, "void f()", asMETHODPR(Input, AddRef, (), void), asCALL_THISCALL);
    // SDL_JoystickID Input::AddScreenJoystick(XMLFile* layoutFile=nullptr, XMLFile* styleFile=nullptr) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "SDL_JoystickID AddScreenJoystick(XMLFile@+ = null, XMLFile@+ = null)", asMETHODPR(Input, AddScreenJoystick, (XMLFile*, XMLFile*), SDL_JoystickID), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Input::CenterMousePosition() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void CenterMousePosition()", asMETHODPR(Input, CenterMousePosition, (), void), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "bool GetBlockEvents() const", asMETHODPR(Input, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "const String& GetCategory() const", asMETHODPR(Input, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "const String& get_category() const", asMETHODPR(Input, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "VariantMap& GetEventDataMap() const", asMETHODPR(Input, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "Object@+ GetEventSender() const", asMETHODPR(Input, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Input, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Input, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "const VariantMap& GetGlobalVars() const", asMETHODPR(Input, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "const VariantMap& get_globalVars() const", asMETHODPR(Input, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // Vector2 Input::GetInputScale() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "Vector2 GetInputScale() const", asMETHODPR(Input, GetInputScale, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "Vector2 get_inputScale() const", asMETHODPR(Input, GetInputScale, () const, Vector2), asCALL_THISCALL);
    // JoystickState* Input::GetJoystick(SDL_JoystickID id) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "JoystickState@+ GetJoystick(SDL_JoystickID)", asMETHODPR(Input, GetJoystick, (SDL_JoystickID), JoystickState*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "JoystickState@+ get_joysticks(SDL_JoystickID)", asMETHODPR(Input, GetJoystick, (SDL_JoystickID), JoystickState*), asCALL_THISCALL);
    // JoystickState* Input::GetJoystickByIndex(unsigned index) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "JoystickState@+ GetJoystickByIndex(uint)", asMETHODPR(Input, GetJoystickByIndex, (unsigned), JoystickState*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "JoystickState@+ get_joysticksByIndex(uint)", asMETHODPR(Input, GetJoystickByIndex, (unsigned), JoystickState*), asCALL_THISCALL);
    // JoystickState* Input::GetJoystickByName(const String& name) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "JoystickState@+ GetJoystickByName(const String&in)", asMETHODPR(Input, GetJoystickByName, (const String&), JoystickState*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "JoystickState@+ get_joysticksByName(const String&in)", asMETHODPR(Input, GetJoystickByName, (const String&), JoystickState*), asCALL_THISCALL);
    // bool Input::GetKeyDown(Key key) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetKeyDown(Key) const", asMETHODPR(Input, GetKeyDown, (Key) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_keyDown(Key) const", asMETHODPR(Input, GetKeyDown, (Key) const, bool), asCALL_THISCALL);
    // Key Input::GetKeyFromName(const String& name) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "Key GetKeyFromName(const String&in) const", asMETHODPR(Input, GetKeyFromName, (const String&) const, Key), asCALL_THISCALL);
    // Key Input::GetKeyFromScancode(Scancode scancode) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "Key GetKeyFromScancode(Scancode) const", asMETHODPR(Input, GetKeyFromScancode, (Scancode) const, Key), asCALL_THISCALL);
    // String Input::GetKeyName(Key key) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "String GetKeyName(Key) const", asMETHODPR(Input, GetKeyName, (Key) const, String), asCALL_THISCALL);
    // bool Input::GetKeyPress(Key key) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetKeyPress(Key) const", asMETHODPR(Input, GetKeyPress, (Key) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_keyPress(Key) const", asMETHODPR(Input, GetKeyPress, (Key) const, bool), asCALL_THISCALL);
    // bool Input::GetMouseButtonDown(MouseButtonFlags button) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetMouseButtonDown(MouseButtonFlags) const", asMETHODPR(Input, GetMouseButtonDown, (MouseButtonFlags) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseButtonDown(MouseButtonFlags) const", asMETHODPR(Input, GetMouseButtonDown, (MouseButtonFlags) const, bool), asCALL_THISCALL);
    // bool Input::GetMouseButtonPress(MouseButtonFlags button) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetMouseButtonPress(MouseButtonFlags) const", asMETHODPR(Input, GetMouseButtonPress, (MouseButtonFlags) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseButtonPress(MouseButtonFlags) const", asMETHODPR(Input, GetMouseButtonPress, (MouseButtonFlags) const, bool), asCALL_THISCALL);
    // MouseMode Input::GetMouseMode() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "MouseMode GetMouseMode() const", asMETHODPR(Input, GetMouseMode, () const, MouseMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "MouseMode get_mouseMode() const", asMETHODPR(Input, GetMouseMode, () const, MouseMode), asCALL_THISCALL);
    // IntVector2 Input::GetMouseMove() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "IntVector2 GetMouseMove() const", asMETHODPR(Input, GetMouseMove, () const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "IntVector2 get_mouseMove() const", asMETHODPR(Input, GetMouseMove, () const, IntVector2), asCALL_THISCALL);
    // int Input::GetMouseMoveWheel() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "int GetMouseMoveWheel() const", asMETHODPR(Input, GetMouseMoveWheel, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_mouseMoveWheel() const", asMETHODPR(Input, GetMouseMoveWheel, () const, int), asCALL_THISCALL);
    // int Input::GetMouseMoveX() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "int GetMouseMoveX() const", asMETHODPR(Input, GetMouseMoveX, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_mouseMoveX() const", asMETHODPR(Input, GetMouseMoveX, () const, int), asCALL_THISCALL);
    // int Input::GetMouseMoveY() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "int GetMouseMoveY() const", asMETHODPR(Input, GetMouseMoveY, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_mouseMoveY() const", asMETHODPR(Input, GetMouseMoveY, () const, int), asCALL_THISCALL);
    // IntVector2 Input::GetMousePosition() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "IntVector2 GetMousePosition() const", asMETHODPR(Input, GetMousePosition, () const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "IntVector2 get_mousePosition() const", asMETHODPR(Input, GetMousePosition, () const, IntVector2), asCALL_THISCALL);
    // unsigned Input::GetNumJoysticks() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "uint GetNumJoysticks() const", asMETHODPR(Input, GetNumJoysticks, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "uint get_numJoysticks() const", asMETHODPR(Input, GetNumJoysticks, () const, unsigned), asCALL_THISCALL);
    // unsigned Input::GetNumTouches() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "uint GetNumTouches() const", asMETHODPR(Input, GetNumTouches, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "uint get_numTouches() const", asMETHODPR(Input, GetNumTouches, () const, unsigned), asCALL_THISCALL);
    // bool Input::GetQualifierDown(Qualifier qualifier) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetQualifierDown(Qualifier) const", asMETHODPR(Input, GetQualifierDown, (Qualifier) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_qualifierDown(Qualifier) const", asMETHODPR(Input, GetQualifierDown, (Qualifier) const, bool), asCALL_THISCALL);
    // bool Input::GetQualifierPress(Qualifier qualifier) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetQualifierPress(Qualifier) const", asMETHODPR(Input, GetQualifierPress, (Qualifier) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_qualifierPress(Qualifier) const", asMETHODPR(Input, GetQualifierPress, (Qualifier) const, bool), asCALL_THISCALL);
    // QualifierFlags Input::GetQualifiers() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "QualifierFlags GetQualifiers() const", asMETHODPR(Input, GetQualifiers, () const, QualifierFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "QualifierFlags get_qualifiers() const", asMETHODPR(Input, GetQualifiers, () const, QualifierFlags), asCALL_THISCALL);
    // bool Input::GetScancodeDown(Scancode scancode) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetScancodeDown(Scancode) const", asMETHODPR(Input, GetScancodeDown, (Scancode) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_scancodeDown(Scancode) const", asMETHODPR(Input, GetScancodeDown, (Scancode) const, bool), asCALL_THISCALL);
    // Scancode Input::GetScancodeFromKey(Key key) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "Scancode GetScancodeFromKey(Key) const", asMETHODPR(Input, GetScancodeFromKey, (Key) const, Scancode), asCALL_THISCALL);
    // Scancode Input::GetScancodeFromName(const String& name) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "Scancode GetScancodeFromName(const String&in) const", asMETHODPR(Input, GetScancodeFromName, (const String&) const, Scancode), asCALL_THISCALL);
    // String Input::GetScancodeName(Scancode scancode) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "String GetScancodeName(Scancode) const", asMETHODPR(Input, GetScancodeName, (Scancode) const, String), asCALL_THISCALL);
    // bool Input::GetScancodePress(Scancode scancode) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetScancodePress(Scancode) const", asMETHODPR(Input, GetScancodePress, (Scancode) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_scancodePress(Scancode) const", asMETHODPR(Input, GetScancodePress, (Scancode) const, bool), asCALL_THISCALL);
    // bool Input::GetScreenKeyboardSupport() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetScreenKeyboardSupport() const", asMETHODPR(Input, GetScreenKeyboardSupport, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_screenKeyboardSupport() const", asMETHODPR(Input, GetScreenKeyboardSupport, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Input, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // bool Input::GetToggleFullscreen() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetToggleFullscreen() const", asMETHODPR(Input, GetToggleFullscreen, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_toggleFullscreen() const", asMETHODPR(Input, GetToggleFullscreen, () const, bool), asCALL_THISCALL);
    // TouchState* Input::GetTouch(unsigned index) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "TouchState@+ GetTouch(uint) const", asMETHODPR(Input, GetTouch, (unsigned) const, TouchState*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "TouchState@+ get_touches(uint) const", asMETHODPR(Input, GetTouch, (unsigned) const, TouchState*), asCALL_THISCALL);
    // bool Input::GetTouchEmulation() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetTouchEmulation() const", asMETHODPR(Input, GetTouchEmulation, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_touchEmulation() const", asMETHODPR(Input, GetTouchEmulation, () const, bool), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "StringHash GetType() const", asMETHODPR(Input, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "StringHash get_type() const", asMETHODPR(Input, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "const String& GetTypeName() const", asMETHODPR(Input, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "const String& get_typeName() const", asMETHODPR(Input, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "bool HasEventHandlers() const", asMETHODPR(Input, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Input::HasFocus() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool HasFocus()", asMETHODPR(Input, HasFocus, (), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_focus()", asMETHODPR(Input, HasFocus, (), bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Input, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Input, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // explicit Input::Input(Context* context) | File: ../Input/Input.h
    engine->RegisterObjectBehaviour("Input", asBEHAVE_FACTORY, "Input@+ f()", asFUNCTION(Input_Input_Context), asCALL_CDECL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "bool IsInstanceOf(StringHash) const", asMETHODPR(Input, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Input::IsMinimized() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool IsMinimized() const", asMETHODPR(Input, IsMinimized, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_minimized() const", asMETHODPR(Input, IsMinimized, () const, bool), asCALL_THISCALL);
    // bool Input::IsMouseGrabbed() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool IsMouseGrabbed() const", asMETHODPR(Input, IsMouseGrabbed, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseGrabbed() const", asMETHODPR(Input, IsMouseGrabbed, () const, bool), asCALL_THISCALL);
    // bool Input::IsMouseLocked() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool IsMouseLocked() const", asMETHODPR(Input, IsMouseLocked, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseLocked() const", asMETHODPR(Input, IsMouseLocked, () const, bool), asCALL_THISCALL);
    // bool Input::IsMouseVisible() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool IsMouseVisible() const", asMETHODPR(Input, IsMouseVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseVisible() const", asMETHODPR(Input, IsMouseVisible, () const, bool), asCALL_THISCALL);
    // bool Input::IsScreenJoystickVisible(SDL_JoystickID id) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool IsScreenJoystickVisible(SDL_JoystickID) const", asMETHODPR(Input, IsScreenJoystickVisible, (SDL_JoystickID) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_screenJoystickVisible(SDL_JoystickID) const", asMETHODPR(Input, IsScreenJoystickVisible, (SDL_JoystickID) const, bool), asCALL_THISCALL);
    // bool Input::IsScreenKeyboardVisible() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool IsScreenKeyboardVisible() const", asMETHODPR(Input, IsScreenKeyboardVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_screenKeyboardVisible() const", asMETHODPR(Input, IsScreenKeyboardVisible, () const, bool), asCALL_THISCALL);
    // unsigned Input::LoadGestures(Deserializer& source) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "uint LoadGestures(Deserializer&)", asMETHODPR(Input, LoadGestures, (Deserializer&), unsigned), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Input, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // bool Input::RecordGesture() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool RecordGesture()", asMETHODPR(Input, RecordGesture, (), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Input", "int Refs() const", asMETHODPR(Input, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_refs() const", asMETHODPR(Input, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Input", asBEHAVE_RELEASE, "void f()", asMETHODPR(Input, ReleaseRef, (), void), asCALL_THISCALL);
    // void Input::RemoveAllGestures() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void RemoveAllGestures()", asMETHODPR(Input, RemoveAllGestures, (), void), asCALL_THISCALL);
    // bool Input::RemoveGesture(unsigned gestureID) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool RemoveGesture(uint)", asMETHODPR(Input, RemoveGesture, (unsigned), bool), asCALL_THISCALL);
    // bool Input::RemoveScreenJoystick(SDL_JoystickID id) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool RemoveScreenJoystick(SDL_JoystickID)", asMETHODPR(Input, RemoveScreenJoystick, (SDL_JoystickID), bool), asCALL_THISCALL);
    // void Input::ResetMouseGrabbed() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void ResetMouseGrabbed()", asMETHODPR(Input, ResetMouseGrabbed, (), void), asCALL_THISCALL);
    // void Input::ResetMouseMode() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void ResetMouseMode()", asMETHODPR(Input, ResetMouseMode, (), void), asCALL_THISCALL);
    // void Input::ResetMouseVisible() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void ResetMouseVisible()", asMETHODPR(Input, ResetMouseVisible, (), void), asCALL_THISCALL);
    // bool Input::SaveGesture(Serializer& dest, unsigned gestureID) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool SaveGesture(Serializer&, uint)", asMETHODPR(Input, SaveGesture, (Serializer&, unsigned), bool), asCALL_THISCALL);
    // bool Input::SaveGestures(Serializer& dest) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool SaveGestures(Serializer&)", asMETHODPR(Input, SaveGestures, (Serializer&), bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void SendEvent(StringHash)", asMETHODPR(Input, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Input, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void SetBlockEvents(bool)", asMETHODPR(Input, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Input, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Input, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Input::SetMouseGrabbed(bool grab, bool suppressEvent=false) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetMouseGrabbed(bool, bool = false)", asMETHODPR(Input, SetMouseGrabbed, (bool, bool), void), asCALL_THISCALL);
    // void Input::SetMouseMode(MouseMode mode, bool suppressEvent=false) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetMouseMode(MouseMode, bool = false)", asMETHODPR(Input, SetMouseMode, (MouseMode, bool), void), asCALL_THISCALL);
    // void Input::SetMousePosition(const IntVector2& position) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetMousePosition(const IntVector2&in)", asMETHODPR(Input, SetMousePosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_mousePosition(const IntVector2&in)", asMETHODPR(Input, SetMousePosition, (const IntVector2&), void), asCALL_THISCALL);
    // void Input::SetMouseVisible(bool enable, bool suppressEvent=false) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetMouseVisible(bool, bool = false)", asMETHODPR(Input, SetMouseVisible, (bool, bool), void), asCALL_THISCALL);
    // void Input::SetScreenJoystickVisible(SDL_JoystickID id, bool enable) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetScreenJoystickVisible(SDL_JoystickID, bool)", asMETHODPR(Input, SetScreenJoystickVisible, (SDL_JoystickID, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_screenJoystickVisible(SDL_JoystickID, bool)", asMETHODPR(Input, SetScreenJoystickVisible, (SDL_JoystickID, bool), void), asCALL_THISCALL);
    // void Input::SetScreenKeyboardVisible(bool enable) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetScreenKeyboardVisible(bool)", asMETHODPR(Input, SetScreenKeyboardVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_screenKeyboardVisible(bool)", asMETHODPR(Input, SetScreenKeyboardVisible, (bool), void), asCALL_THISCALL);
    // void Input::SetToggleFullscreen(bool enable) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetToggleFullscreen(bool)", asMETHODPR(Input, SetToggleFullscreen, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_toggleFullscreen(bool)", asMETHODPR(Input, SetToggleFullscreen, (bool), void), asCALL_THISCALL);
    // void Input::SetTouchEmulation(bool enable) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetTouchEmulation(bool)", asMETHODPR(Input, SetTouchEmulation, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_touchEmulation(bool)", asMETHODPR(Input, SetTouchEmulation, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void UnsubscribeFromAllEvents()", asMETHODPR(Input, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Input_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Input, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Input, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Input, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Input::Update() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void Update()", asMETHODPR(Input, Update, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Input", "int WeakRefs() const", asMETHODPR(Input, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_weakRefs() const", asMETHODPR(Input, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Input, "Input")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Input, "Input")
#endif
#ifdef REGISTER_MANUAL_PART_Input
    REGISTER_MANUAL_PART_Input(Input, "Input")
#endif
    RegisterSubclass<Object, Input>(engine, "Object", "Input");
    RegisterSubclass<RefCounted, Input>(engine, "RefCounted", "Input");

    // int IntRect::bottom_ | File: ../Math/Rect.h
    engine->RegisterObjectProperty("IntRect", "int bottom", offsetof(IntRect, bottom_));
    // int IntRect::left_ | File: ../Math/Rect.h
    engine->RegisterObjectProperty("IntRect", "int left", offsetof(IntRect, left_));
    // int IntRect::right_ | File: ../Math/Rect.h
    engine->RegisterObjectProperty("IntRect", "int right", offsetof(IntRect, right_));
    // int IntRect::top_ | File: ../Math/Rect.h
    engine->RegisterObjectProperty("IntRect", "int top", offsetof(IntRect, top_));
    // const IntRect IntRect::ZERO | File: ../Math/Rect.h
    engine->SetDefaultNamespace("IntRect");
    engine->RegisterGlobalProperty("const IntRect ZERO", (void*)&IntRect::ZERO);
    engine->SetDefaultNamespace("");
    // int IntRect::Bottom() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "int Bottom() const", asMETHODPR(IntRect, Bottom, () const, int), asCALL_THISCALL);
    // void IntRect::Clip(const IntRect& rect) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "void Clip(const IntRect&in)", asMETHODPR(IntRect, Clip, (const IntRect&), void), asCALL_THISCALL);
    // const int* IntRect::Data() const | File: ../Math/Rect.h
    // Error: type "const int*" can not automatically bind
    // int IntRect::Height() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "int Height() const", asMETHODPR(IntRect, Height, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "int get_height() const", asMETHODPR(IntRect, Height, () const, int), asCALL_THISCALL);
    // IntRect::IntRect(const IntVector2& min, const IntVector2& max) noexcept | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in, const IntVector2&in)", asFUNCTION(IntRect_IntRect_IntVector2_IntVector2), asCALL_CDECL_OBJFIRST);
    // IntRect::IntRect(int left, int top, int right, int bottom) noexcept | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(int, int, int, int)", asFUNCTION(IntRect_IntRect_int_int_int_int), asCALL_CDECL_OBJFIRST);
    // explicit IntRect::IntRect(const int* data) noexcept | File: ../Math/Rect.h
    // Error: type "const int*" can not automatically bind
    // Intersection IntRect::IsInside(const IntVector2& point) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "Intersection IsInside(const IntVector2&in) const", asMETHODPR(IntRect, IsInside, (const IntVector2&) const, Intersection), asCALL_THISCALL);
    // Intersection IntRect::IsInside(const IntRect& rect) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "Intersection IsInside(const IntRect&in) const", asMETHODPR(IntRect, IsInside, (const IntRect&) const, Intersection), asCALL_THISCALL);
    // int IntRect::Left() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "int Left() const", asMETHODPR(IntRect, Left, () const, int), asCALL_THISCALL);
    // IntVector2 IntRect::Max() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntVector2 Max() const", asMETHODPR(IntRect, Max, () const, IntVector2), asCALL_THISCALL);
    // void IntRect::Merge(const IntRect& rect) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "void Merge(const IntRect&in)", asMETHODPR(IntRect, Merge, (const IntRect&), void), asCALL_THISCALL);
    // IntVector2 IntRect::Min() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntVector2 Min() const", asMETHODPR(IntRect, Min, () const, IntVector2), asCALL_THISCALL);
    // IntRect IntRect::operator*(float value) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect opMul(float) const", asMETHODPR(IntRect, operator*, (float) const, IntRect), asCALL_THISCALL);
    // IntRect& IntRect::operator*=(float value) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect& opMulAssign(float)", asMETHODPR(IntRect, operator*=, (float), IntRect&), asCALL_THISCALL);
    // IntRect IntRect::operator+(const IntRect& rhs) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect opAdd(const IntRect&in) const", asMETHODPR(IntRect, operator+, (const IntRect&) const, IntRect), asCALL_THISCALL);
    // IntRect& IntRect::operator+=(const IntRect& rhs) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect& opAddAssign(const IntRect&in)", asMETHODPR(IntRect, operator+=, (const IntRect&), IntRect&), asCALL_THISCALL);
    // IntRect IntRect::operator-(const IntRect& rhs) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect opSub(const IntRect&in) const", asMETHODPR(IntRect, operator-, (const IntRect&) const, IntRect), asCALL_THISCALL);
    // IntRect& IntRect::operator-=(const IntRect& rhs) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect& opSubAssign(const IntRect&in)", asMETHODPR(IntRect, operator-=, (const IntRect&), IntRect&), asCALL_THISCALL);
    // IntRect IntRect::operator/(float value) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect opDiv(float) const", asMETHODPR(IntRect, operator/, (float) const, IntRect), asCALL_THISCALL);
    // IntRect& IntRect::operator/=(float value) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect& opDivAssign(float)", asMETHODPR(IntRect, operator/=, (float), IntRect&), asCALL_THISCALL);
    // bool IntRect::operator==(const IntRect& rhs) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "bool opEquals(const IntRect&in) const", asMETHODPR(IntRect, operator==, (const IntRect&) const, bool), asCALL_THISCALL);
    // int IntRect::Right() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "int Right() const", asMETHODPR(IntRect, Right, () const, int), asCALL_THISCALL);
    // IntVector2 IntRect::Size() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntVector2 Size() const", asMETHODPR(IntRect, Size, () const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "IntVector2 get_size() const", asMETHODPR(IntRect, Size, () const, IntVector2), asCALL_THISCALL);
    // int IntRect::Top() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "int Top() const", asMETHODPR(IntRect, Top, () const, int), asCALL_THISCALL);
    // String IntRect::ToString() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "String ToString() const", asMETHODPR(IntRect, ToString, () const, String), asCALL_THISCALL);
    // int IntRect::Width() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "int Width() const", asMETHODPR(IntRect, Width, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "int get_width() const", asMETHODPR(IntRect, Width, () const, int), asCALL_THISCALL);
    // IntRect& IntRect::operator=(const IntRect&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<IntRect>(engine, "IntRect");
#ifdef REGISTER_MANUAL_PART_IntRect
    REGISTER_MANUAL_PART_IntRect(IntRect, "IntRect")
#endif

    // const IntVector2 IntVector2::DOWN | File: ../Math/Vector2.h
    engine->SetDefaultNamespace("IntVector2");
    engine->RegisterGlobalProperty("const IntVector2 DOWN", (void*)&IntVector2::DOWN);
    engine->SetDefaultNamespace("");
    // const IntVector2 IntVector2::LEFT | File: ../Math/Vector2.h
    engine->SetDefaultNamespace("IntVector2");
    engine->RegisterGlobalProperty("const IntVector2 LEFT", (void*)&IntVector2::LEFT);
    engine->SetDefaultNamespace("");
    // const IntVector2 IntVector2::ONE | File: ../Math/Vector2.h
    engine->SetDefaultNamespace("IntVector2");
    engine->RegisterGlobalProperty("const IntVector2 ONE", (void*)&IntVector2::ONE);
    engine->SetDefaultNamespace("");
    // const IntVector2 IntVector2::RIGHT | File: ../Math/Vector2.h
    engine->SetDefaultNamespace("IntVector2");
    engine->RegisterGlobalProperty("const IntVector2 RIGHT", (void*)&IntVector2::RIGHT);
    engine->SetDefaultNamespace("");
    // const IntVector2 IntVector2::UP | File: ../Math/Vector2.h
    engine->SetDefaultNamespace("IntVector2");
    engine->RegisterGlobalProperty("const IntVector2 UP", (void*)&IntVector2::UP);
    engine->SetDefaultNamespace("");
    // int IntVector2::x_ | File: ../Math/Vector2.h
    engine->RegisterObjectProperty("IntVector2", "int x", offsetof(IntVector2, x_));
    // int IntVector2::y_ | File: ../Math/Vector2.h
    engine->RegisterObjectProperty("IntVector2", "int y", offsetof(IntVector2, y_));
    // const IntVector2 IntVector2::ZERO | File: ../Math/Vector2.h
    engine->SetDefaultNamespace("IntVector2");
    engine->RegisterGlobalProperty("const IntVector2 ZERO", (void*)&IntVector2::ZERO);
    engine->SetDefaultNamespace("");
    // const int* IntVector2::Data() const | File: ../Math/Vector2.h
    // Error: type "const int*" can not automatically bind
    // IntVector2::IntVector2(int x, int y) noexcept | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(int, int)", asFUNCTION(IntVector2_IntVector2_int_int), asCALL_CDECL_OBJFIRST);
    // explicit IntVector2::IntVector2(const int* data) noexcept | File: ../Math/Vector2.h
    // Error: type "const int*" can not automatically bind
    // explicit IntVector2::IntVector2(const float* data) | File: ../Math/Vector2.h
    // Error: type "const float*" can not automatically bind
    // IntVector2::IntVector2(const IntVector2& rhs) noexcept=default | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", asFUNCTION(IntVector2_IntVector2_IntVector2), asCALL_CDECL_OBJFIRST);
    // float IntVector2::Length() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "float Length() const", asMETHODPR(IntVector2, Length, () const, float), asCALL_THISCALL);
    // IntVector2 IntVector2::operator*(int rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opMul(int) const", asMETHODPR(IntVector2, operator*, (int) const, IntVector2), asCALL_THISCALL);
    // IntVector2 IntVector2::operator*(const IntVector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opMul(const IntVector2&in) const", asMETHODPR(IntVector2, operator*, (const IntVector2&) const, IntVector2), asCALL_THISCALL);
    // IntVector2& IntVector2::operator*=(int rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opMulAssign(int)", asMETHODPR(IntVector2, operator*=, (int), IntVector2&), asCALL_THISCALL);
    // IntVector2& IntVector2::operator*=(const IntVector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opMulAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator*=, (const IntVector2&), IntVector2&), asCALL_THISCALL);
    // IntVector2 IntVector2::operator+(const IntVector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opAdd(const IntVector2&in) const", asMETHODPR(IntVector2, operator+, (const IntVector2&) const, IntVector2), asCALL_THISCALL);
    // IntVector2& IntVector2::operator+=(const IntVector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opAddAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator+=, (const IntVector2&), IntVector2&), asCALL_THISCALL);
    // IntVector2 IntVector2::operator-() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opNeg() const", asMETHODPR(IntVector2, operator-, () const, IntVector2), asCALL_THISCALL);
    // IntVector2 IntVector2::operator-(const IntVector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opSub(const IntVector2&in) const", asMETHODPR(IntVector2, operator-, (const IntVector2&) const, IntVector2), asCALL_THISCALL);
    // IntVector2& IntVector2::operator-=(const IntVector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opSubAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator-=, (const IntVector2&), IntVector2&), asCALL_THISCALL);
    // IntVector2 IntVector2::operator/(int rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opDiv(int) const", asMETHODPR(IntVector2, operator/, (int) const, IntVector2), asCALL_THISCALL);
    // IntVector2 IntVector2::operator/(const IntVector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opDiv(const IntVector2&in) const", asMETHODPR(IntVector2, operator/, (const IntVector2&) const, IntVector2), asCALL_THISCALL);
    // IntVector2& IntVector2::operator/=(int rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opDivAssign(int)", asMETHODPR(IntVector2, operator/=, (int), IntVector2&), asCALL_THISCALL);
    // IntVector2& IntVector2::operator/=(const IntVector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opDivAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator/=, (const IntVector2&), IntVector2&), asCALL_THISCALL);
    // IntVector2& IntVector2::operator=(const IntVector2& rhs) noexcept=default | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator=, (const IntVector2&), IntVector2&), asCALL_THISCALL);
    // bool IntVector2::operator==(const IntVector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "bool opEquals(const IntVector2&in) const", asMETHODPR(IntVector2, operator==, (const IntVector2&) const, bool), asCALL_THISCALL);
    // unsigned IntVector2::ToHash() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "uint ToHash() const", asMETHODPR(IntVector2, ToHash, () const, unsigned), asCALL_THISCALL);
    // String IntVector2::ToString() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "String ToString() const", asMETHODPR(IntVector2, ToString, () const, String), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_IntVector2
    REGISTER_MANUAL_PART_IntVector2(IntVector2, "IntVector2")
#endif

    // const IntVector3 IntVector3::BACK | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("IntVector3");
    engine->RegisterGlobalProperty("const IntVector3 BACK", (void*)&IntVector3::BACK);
    engine->SetDefaultNamespace("");
    // const IntVector3 IntVector3::DOWN | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("IntVector3");
    engine->RegisterGlobalProperty("const IntVector3 DOWN", (void*)&IntVector3::DOWN);
    engine->SetDefaultNamespace("");
    // const IntVector3 IntVector3::FORWARD | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("IntVector3");
    engine->RegisterGlobalProperty("const IntVector3 FORWARD", (void*)&IntVector3::FORWARD);
    engine->SetDefaultNamespace("");
    // const IntVector3 IntVector3::LEFT | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("IntVector3");
    engine->RegisterGlobalProperty("const IntVector3 LEFT", (void*)&IntVector3::LEFT);
    engine->SetDefaultNamespace("");
    // const IntVector3 IntVector3::ONE | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("IntVector3");
    engine->RegisterGlobalProperty("const IntVector3 ONE", (void*)&IntVector3::ONE);
    engine->SetDefaultNamespace("");
    // const IntVector3 IntVector3::RIGHT | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("IntVector3");
    engine->RegisterGlobalProperty("const IntVector3 RIGHT", (void*)&IntVector3::RIGHT);
    engine->SetDefaultNamespace("");
    // const IntVector3 IntVector3::UP | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("IntVector3");
    engine->RegisterGlobalProperty("const IntVector3 UP", (void*)&IntVector3::UP);
    engine->SetDefaultNamespace("");
    // int IntVector3::x_ | File: ../Math/Vector3.h
    engine->RegisterObjectProperty("IntVector3", "int x", offsetof(IntVector3, x_));
    // int IntVector3::y_ | File: ../Math/Vector3.h
    engine->RegisterObjectProperty("IntVector3", "int y", offsetof(IntVector3, y_));
    // int IntVector3::z_ | File: ../Math/Vector3.h
    engine->RegisterObjectProperty("IntVector3", "int z", offsetof(IntVector3, z_));
    // const IntVector3 IntVector3::ZERO | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("IntVector3");
    engine->RegisterGlobalProperty("const IntVector3 ZERO", (void*)&IntVector3::ZERO);
    engine->SetDefaultNamespace("");
    // const int* IntVector3::Data() const | File: ../Math/Vector3.h
    // Error: type "const int*" can not automatically bind
    // IntVector3::IntVector3(int x, int y, int z) noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f(int, int, int)", asFUNCTION(IntVector3_IntVector3_int_int_int), asCALL_CDECL_OBJFIRST);
    // explicit IntVector3::IntVector3(const int* data) noexcept | File: ../Math/Vector3.h
    // Error: type "const int*" can not automatically bind
    // IntVector3::IntVector3(const IntVector3& rhs) noexcept=default | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f(const IntVector3&in)", asFUNCTION(IntVector3_IntVector3_IntVector3), asCALL_CDECL_OBJFIRST);
    // float IntVector3::Length() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "float Length() const", asMETHODPR(IntVector3, Length, () const, float), asCALL_THISCALL);
    // IntVector3 IntVector3::operator*(int rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opMul(int) const", asMETHODPR(IntVector3, operator*, (int) const, IntVector3), asCALL_THISCALL);
    // IntVector3 IntVector3::operator*(const IntVector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opMul(const IntVector3&in) const", asMETHODPR(IntVector3, operator*, (const IntVector3&) const, IntVector3), asCALL_THISCALL);
    // IntVector3& IntVector3::operator*=(int rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opMulAssign(int)", asMETHODPR(IntVector3, operator*=, (int), IntVector3&), asCALL_THISCALL);
    // IntVector3& IntVector3::operator*=(const IntVector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opMulAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator*=, (const IntVector3&), IntVector3&), asCALL_THISCALL);
    // IntVector3 IntVector3::operator+(const IntVector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opAdd(const IntVector3&in) const", asMETHODPR(IntVector3, operator+, (const IntVector3&) const, IntVector3), asCALL_THISCALL);
    // IntVector3& IntVector3::operator+=(const IntVector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opAddAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator+=, (const IntVector3&), IntVector3&), asCALL_THISCALL);
    // IntVector3 IntVector3::operator-() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opNeg() const", asMETHODPR(IntVector3, operator-, () const, IntVector3), asCALL_THISCALL);
    // IntVector3 IntVector3::operator-(const IntVector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opSub(const IntVector3&in) const", asMETHODPR(IntVector3, operator-, (const IntVector3&) const, IntVector3), asCALL_THISCALL);
    // IntVector3& IntVector3::operator-=(const IntVector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opSubAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator-=, (const IntVector3&), IntVector3&), asCALL_THISCALL);
    // IntVector3 IntVector3::operator/(int rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opDiv(int) const", asMETHODPR(IntVector3, operator/, (int) const, IntVector3), asCALL_THISCALL);
    // IntVector3 IntVector3::operator/(const IntVector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opDiv(const IntVector3&in) const", asMETHODPR(IntVector3, operator/, (const IntVector3&) const, IntVector3), asCALL_THISCALL);
    // IntVector3& IntVector3::operator/=(int rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opDivAssign(int)", asMETHODPR(IntVector3, operator/=, (int), IntVector3&), asCALL_THISCALL);
    // IntVector3& IntVector3::operator/=(const IntVector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opDivAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator/=, (const IntVector3&), IntVector3&), asCALL_THISCALL);
    // IntVector3& IntVector3::operator=(const IntVector3& rhs) noexcept=default | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator=, (const IntVector3&), IntVector3&), asCALL_THISCALL);
    // bool IntVector3::operator==(const IntVector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "bool opEquals(const IntVector3&in) const", asMETHODPR(IntVector3, operator==, (const IntVector3&) const, bool), asCALL_THISCALL);
    // unsigned IntVector3::ToHash() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "uint ToHash() const", asMETHODPR(IntVector3, ToHash, () const, unsigned), asCALL_THISCALL);
    // String IntVector3::ToString() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "String ToString() const", asMETHODPR(IntVector3, ToString, () const, String), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_IntVector3
    REGISTER_MANUAL_PART_IntVector3(IntVector3, "IntVector3")
#endif

    // SharedArrayPtr<unsigned char> IndexBufferDesc::data_ | File: ../Graphics/Model.h
    // Error: type "SharedArrayPtr<unsigned char>" can not automatically bind
    // unsigned IndexBufferDesc::dataSize_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("IndexBufferDesc", "uint dataSize", offsetof(IndexBufferDesc, dataSize_));
    // unsigned IndexBufferDesc::indexCount_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("IndexBufferDesc", "uint indexCount", offsetof(IndexBufferDesc, indexCount_));
    // unsigned IndexBufferDesc::indexSize_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("IndexBufferDesc", "uint indexSize", offsetof(IndexBufferDesc, indexSize_));
    // IndexBufferDesc& IndexBufferDesc::operator=(const IndexBufferDesc&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<IndexBufferDesc>(engine, "IndexBufferDesc");
#ifdef REGISTER_MANUAL_PART_IndexBufferDesc
    REGISTER_MANUAL_PART_IndexBufferDesc(IndexBufferDesc, "IndexBufferDesc")
#endif

    // float InstanceData::distance_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("InstanceData", "float distance", offsetof(InstanceData, distance_));
    // const void* InstanceData::instancingData_ | File: ../Graphics/Batch.h
    // const void* can not be registered
    // const Matrix3x4* InstanceData::worldTransform_ | File: ../Graphics/Batch.h
    // const Matrix3x4* can not be registered
    // InstanceData::InstanceData(const Matrix3x4* worldTransform, const void* instancingData, float distance) | File: ../Graphics/Batch.h
    // Error: type "const Matrix3x4*" can not automatically bind
    // InstanceData& InstanceData::operator=(const InstanceData&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<InstanceData>(engine, "InstanceData");
#ifdef REGISTER_MANUAL_PART_InstanceData
    REGISTER_MANUAL_PART_InstanceData(InstanceData, "InstanceData")
#endif

}

}
