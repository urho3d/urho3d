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
static void IKConstraint_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(IKConstraint* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
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
static void IKEffector_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(IKEffector* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
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
static void IKSolver_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(IKSolver* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
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
static void Image_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Image* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit IndexBuffer::IndexBuffer(Context* context, bool forceHeadless=false) | File: ../Graphics/IndexBuffer.h
static IndexBuffer* IndexBuffer_IndexBuffer_Context_bool(bool forceHeadless=false)
{
    return new IndexBuffer(GetScriptContext(), forceHeadless);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void IndexBuffer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(IndexBuffer* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit Input::Input(Context* context) | File: ../Input/Input.h
static Input* Input_Input_Context()
{
    return new Input(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Input_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Input* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
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
    engine->RegisterObjectBehaviour("IKConstraint", asBEHAVE_ADDREF, "void f()", AS_METHODPR(IKConstraint, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void AllocateNetworkState()", AS_METHODPR(IKConstraint, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void ApplyAttributes()", AS_METHODPR(IKConstraint, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(IKConstraint, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "bool GetAnimationEnabled() const", AS_METHODPR(IKConstraint, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "bool get_animationEnabled() const", AS_METHODPR(IKConstraint, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "Variant GetAttribute(uint) const", AS_METHODPR(IKConstraint, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "Variant get_attributes(uint) const", AS_METHODPR(IKConstraint, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "Variant GetAttribute(const String&in) const", AS_METHODPR(IKConstraint, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(IKConstraint, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(IKConstraint, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(IKConstraint, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(IKConstraint, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "Variant GetAttributeDefault(uint) const", AS_METHODPR(IKConstraint, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "Variant get_attributeDefaults(uint) const", AS_METHODPR(IKConstraint, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(IKConstraint, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "bool GetBlockEvents() const", AS_METHODPR(IKConstraint, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "const String& GetCategory() const", AS_METHODPR(IKConstraint, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "const String& get_category() const", AS_METHODPR(IKConstraint, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "Component@+ GetComponent(StringHash) const", AS_METHODPR(IKConstraint, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "VariantMap& GetEventDataMap() const", AS_METHODPR(IKConstraint, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "Object@+ GetEventSender() const", AS_METHODPR(IKConstraint, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(IKConstraint, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(IKConstraint, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "const VariantMap& GetGlobalVars() const", AS_METHODPR(IKConstraint, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "const VariantMap& get_globalVars() const", AS_METHODPR(IKConstraint, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "uint GetID() const", AS_METHODPR(IKConstraint, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "uint get_id() const", AS_METHODPR(IKConstraint, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(IKConstraint, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const Vector2& IKConstraint::GetLengthConstraints() const | File: ../IK/IKConstraint.h
    engine->RegisterObjectMethod("IKConstraint", "const Vector2& GetLengthConstraints() const", AS_METHODPR(IKConstraint, GetLengthConstraints, () const, const Vector2&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "Node@+ GetNode() const", AS_METHODPR(IKConstraint, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "Node@+ get_node() const", AS_METHODPR(IKConstraint, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "uint GetNumAttributes() const", AS_METHODPR(IKConstraint, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "uint get_numAttributes() const", AS_METHODPR(IKConstraint, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "uint GetNumNetworkAttributes() const", AS_METHODPR(IKConstraint, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(IKConstraint, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(IKConstraint, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(IKConstraint, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "Scene@+ GetScene() const", AS_METHODPR(IKConstraint, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float IKConstraint::GetStiffness() const | File: ../IK/IKConstraint.h
    engine->RegisterObjectMethod("IKConstraint", "float GetStiffness() const", AS_METHODPR(IKConstraint, GetStiffness, () const, float), AS_CALL_THISCALL);
    // float IKConstraint::GetStretchiness() const | File: ../IK/IKConstraint.h
    engine->RegisterObjectMethod("IKConstraint", "float GetStretchiness() const", AS_METHODPR(IKConstraint, GetStretchiness, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(IKConstraint, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "StringHash GetType() const", AS_METHODPR(IKConstraint, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "StringHash get_type() const", AS_METHODPR(IKConstraint, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "const String& GetTypeName() const", AS_METHODPR(IKConstraint, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "const String& get_typeName() const", AS_METHODPR(IKConstraint, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "bool HasEventHandlers() const", AS_METHODPR(IKConstraint, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(IKConstraint, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(IKConstraint, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // explicit IKConstraint::IKConstraint(Context* context) | File: ../IK/IKConstraint.h
    engine->RegisterObjectBehaviour("IKConstraint", asBEHAVE_FACTORY, "IKConstraint@+ f()", AS_FUNCTION(IKConstraint_IKConstraint_Context), AS_CALL_CDECL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "bool IsEnabled() const", AS_METHODPR(IKConstraint, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "bool get_enabled() const", AS_METHODPR(IKConstraint, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "bool IsEnabledEffective() const", AS_METHODPR(IKConstraint, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "bool get_enabledEffective() const", AS_METHODPR(IKConstraint, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "bool IsInstanceOf(StringHash) const", AS_METHODPR(IKConstraint, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "bool IsReplicated() const", AS_METHODPR(IKConstraint, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "bool get_replicated() const", AS_METHODPR(IKConstraint, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool IsTemporary() const", AS_METHODPR(IKConstraint, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "bool get_temporary() const", AS_METHODPR(IKConstraint, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool Load(Deserializer&)", AS_METHODPR(IKConstraint, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(IKConstraint, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "bool LoadXML(const XMLElement&in)", AS_METHODPR(IKConstraint, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "void MarkNetworkUpdate()", AS_METHODPR(IKConstraint, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(IKConstraint, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(IKConstraint, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(IKConstraint, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "void OnSetEnabled()", AS_METHODPR(IKConstraint, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "void PrepareNetworkUpdate()", AS_METHODPR(IKConstraint, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(IKConstraint, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(IKConstraint, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IKConstraint", "int Refs() const", AS_METHODPR(IKConstraint, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "int get_refs() const", AS_METHODPR(IKConstraint, Refs, () const, int), AS_CALL_THISCALL);
    // static void IKConstraint::RegisterObject(Context* context) | File: ../IK/IKConstraint.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("IKConstraint", asBEHAVE_RELEASE, "void f()", AS_METHODPR(IKConstraint, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "void Remove()", AS_METHODPR(IKConstraint, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(IKConstraint, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void RemoveInstanceDefault()", AS_METHODPR(IKConstraint, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void RemoveObjectAnimation()", AS_METHODPR(IKConstraint, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void ResetToDefault()", AS_METHODPR(IKConstraint, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "bool Save(Serializer&) const", AS_METHODPR(IKConstraint, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool SaveDefaultAttributes() const", AS_METHODPR(IKConstraint, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "bool SaveJSON(JSONValue&) const", AS_METHODPR(IKConstraint, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "bool SaveXML(XMLElement&) const", AS_METHODPR(IKConstraint, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void SendEvent(StringHash)", AS_METHODPR(IKConstraint, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(IKConstraint, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetAnimationEnabled(bool)", AS_METHODPR(IKConstraint, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "void set_animationEnabled(bool)", AS_METHODPR(IKConstraint, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetAnimationTime(float)", AS_METHODPR(IKConstraint, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(IKConstraint, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(IKConstraint, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(IKConstraint, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(IKConstraint, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(IKConstraint, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(IKConstraint, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(IKConstraint, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void SetBlockEvents(bool)", AS_METHODPR(IKConstraint, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKConstraint", "void SetEnabled(bool)", AS_METHODPR(IKConstraint, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "void set_enabled(bool)", AS_METHODPR(IKConstraint, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(IKConstraint, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(IKConstraint, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetInstanceDefault(bool)", AS_METHODPR(IKConstraint, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(IKConstraint, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void IKConstraint::SetLengthConstraints(const Vector2& lengthConstraints) | File: ../IK/IKConstraint.h
    engine->RegisterObjectMethod("IKConstraint", "void SetLengthConstraints(const Vector2&in)", AS_METHODPR(IKConstraint, SetLengthConstraints, (const Vector2&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(IKConstraint, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(IKConstraint, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(IKConstraint, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void IKConstraint::SetStiffness(float stiffness) | File: ../IK/IKConstraint.h
    engine->RegisterObjectMethod("IKConstraint", "void SetStiffness(float)", AS_METHODPR(IKConstraint, SetStiffness, (float), void), AS_CALL_THISCALL);
    // void IKConstraint::SetStretchiness(float stretchiness) | File: ../IK/IKConstraint.h
    engine->RegisterObjectMethod("IKConstraint", "void SetStretchiness(float)", AS_METHODPR(IKConstraint, SetStretchiness, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void SetTemporary(bool)", AS_METHODPR(IKConstraint, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "void set_temporary(bool)", AS_METHODPR(IKConstraint, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void UnsubscribeFromAllEvents()", AS_METHODPR(IKConstraint, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(IKConstraint_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(IKConstraint, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(IKConstraint, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKConstraint", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(IKConstraint, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IKConstraint", "int WeakRefs() const", AS_METHODPR(IKConstraint, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKConstraint", "int get_weakRefs() const", AS_METHODPR(IKConstraint, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(IKConstraint, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(IKConstraint, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKConstraint", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(IKConstraint, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("IKEffector", asBEHAVE_ADDREF, "void f()", AS_METHODPR(IKEffector, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void AllocateNetworkState()", AS_METHODPR(IKEffector, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void ApplyAttributes()", AS_METHODPR(IKEffector, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void IKEffector::DrawDebugGeometry(bool depthTest) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void DrawDebugGeometry(bool)", AS_METHODPR(IKEffector, DrawDebugGeometry, (bool), void), AS_CALL_THISCALL);
    // void IKEffector::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(IKEffector, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "bool GetAnimationEnabled() const", AS_METHODPR(IKEffector, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "bool get_animationEnabled() const", AS_METHODPR(IKEffector, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "Variant GetAttribute(uint) const", AS_METHODPR(IKEffector, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "Variant get_attributes(uint) const", AS_METHODPR(IKEffector, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "Variant GetAttribute(const String&in) const", AS_METHODPR(IKEffector, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(IKEffector, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(IKEffector, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(IKEffector, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(IKEffector, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "Variant GetAttributeDefault(uint) const", AS_METHODPR(IKEffector, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "Variant get_attributeDefaults(uint) const", AS_METHODPR(IKEffector, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(IKEffector, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "bool GetBlockEvents() const", AS_METHODPR(IKEffector, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "const String& GetCategory() const", AS_METHODPR(IKEffector, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "const String& get_category() const", AS_METHODPR(IKEffector, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // unsigned IKEffector::GetChainLength() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "uint GetChainLength() const", AS_METHODPR(IKEffector, GetChainLength, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "uint get_chainLength() const", AS_METHODPR(IKEffector, GetChainLength, () const, unsigned), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "Component@+ GetComponent(StringHash) const", AS_METHODPR(IKEffector, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "VariantMap& GetEventDataMap() const", AS_METHODPR(IKEffector, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "Object@+ GetEventSender() const", AS_METHODPR(IKEffector, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // bool IKEffector::GetFeature(Feature feature) const | File: ../IK/IKEffector.h
    // Not registered because have @nobind mark
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(IKEffector, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(IKEffector, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "const VariantMap& GetGlobalVars() const", AS_METHODPR(IKEffector, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "const VariantMap& get_globalVars() const", AS_METHODPR(IKEffector, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "uint GetID() const", AS_METHODPR(IKEffector, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "uint get_id() const", AS_METHODPR(IKEffector, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool IKEffector::GetINHERIT_PARENT_ROTATION() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "bool GetINHERIT_PARENT_ROTATION() const", AS_METHODPR(IKEffector, GetINHERIT_PARENT_ROTATION, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(IKEffector, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "Node@+ GetNode() const", AS_METHODPR(IKEffector, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "Node@+ get_node() const", AS_METHODPR(IKEffector, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "uint GetNumAttributes() const", AS_METHODPR(IKEffector, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "uint get_numAttributes() const", AS_METHODPR(IKEffector, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "uint GetNumNetworkAttributes() const", AS_METHODPR(IKEffector, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(IKEffector, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(IKEffector, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(IKEffector, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float IKEffector::GetRotationDecay() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "float GetRotationDecay() const", AS_METHODPR(IKEffector, GetRotationDecay, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "float get_rotationDecay() const", AS_METHODPR(IKEffector, GetRotationDecay, () const, float), AS_CALL_THISCALL);
    // float IKEffector::GetRotationWeight() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "float GetRotationWeight() const", AS_METHODPR(IKEffector, GetRotationWeight, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "float get_rotationWeight() const", AS_METHODPR(IKEffector, GetRotationWeight, () const, float), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "Scene@+ GetScene() const", AS_METHODPR(IKEffector, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(IKEffector, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const String& IKEffector::GetTargetName() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "const String& GetTargetName() const", AS_METHODPR(IKEffector, GetTargetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "const String& get_targetName() const", AS_METHODPR(IKEffector, GetTargetName, () const, const String&), AS_CALL_THISCALL);
    // Node* IKEffector::GetTargetNode() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "Node@+ GetTargetNode() const", AS_METHODPR(IKEffector, GetTargetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "Node@+ get_targetNode() const", AS_METHODPR(IKEffector, GetTargetNode, () const, Node*), AS_CALL_THISCALL);
    // const Vector3& IKEffector::GetTargetPosition() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "const Vector3& GetTargetPosition() const", AS_METHODPR(IKEffector, GetTargetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "const Vector3& get_targetPosition() const", AS_METHODPR(IKEffector, GetTargetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    // const Quaternion& IKEffector::GetTargetRotation() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "const Quaternion& GetTargetRotation() const", AS_METHODPR(IKEffector, GetTargetRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "const Quaternion& get_targetRotation() const", AS_METHODPR(IKEffector, GetTargetRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    // Vector3 IKEffector::GetTargetRotationEuler() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "Vector3 GetTargetRotationEuler() const", AS_METHODPR(IKEffector, GetTargetRotationEuler, () const, Vector3), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "StringHash GetType() const", AS_METHODPR(IKEffector, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "StringHash get_type() const", AS_METHODPR(IKEffector, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "const String& GetTypeName() const", AS_METHODPR(IKEffector, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "const String& get_typeName() const", AS_METHODPR(IKEffector, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // float IKEffector::GetWeight() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "float GetWeight() const", AS_METHODPR(IKEffector, GetWeight, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "float get_weight() const", AS_METHODPR(IKEffector, GetWeight, () const, float), AS_CALL_THISCALL);
    // bool IKEffector::GetWEIGHT_NLERP() const | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "bool GetWEIGHT_NLERP() const", AS_METHODPR(IKEffector, GetWEIGHT_NLERP, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "bool HasEventHandlers() const", AS_METHODPR(IKEffector, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(IKEffector, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(IKEffector, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // explicit IKEffector::IKEffector(Context* context) | File: ../IK/IKEffector.h
    engine->RegisterObjectBehaviour("IKEffector", asBEHAVE_FACTORY, "IKEffector@+ f()", AS_FUNCTION(IKEffector_IKEffector_Context), AS_CALL_CDECL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "bool IsEnabled() const", AS_METHODPR(IKEffector, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "bool get_enabled() const", AS_METHODPR(IKEffector, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "bool IsEnabledEffective() const", AS_METHODPR(IKEffector, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "bool get_enabledEffective() const", AS_METHODPR(IKEffector, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "bool IsInstanceOf(StringHash) const", AS_METHODPR(IKEffector, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "bool IsReplicated() const", AS_METHODPR(IKEffector, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "bool get_replicated() const", AS_METHODPR(IKEffector, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool IsTemporary() const", AS_METHODPR(IKEffector, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "bool get_temporary() const", AS_METHODPR(IKEffector, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool Load(Deserializer&)", AS_METHODPR(IKEffector, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(IKEffector, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "bool LoadXML(const XMLElement&in)", AS_METHODPR(IKEffector, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "void MarkNetworkUpdate()", AS_METHODPR(IKEffector, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(IKEffector, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(IKEffector, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(IKEffector, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "void OnSetEnabled()", AS_METHODPR(IKEffector, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "void PrepareNetworkUpdate()", AS_METHODPR(IKEffector, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(IKEffector, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(IKEffector, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IKEffector", "int Refs() const", AS_METHODPR(IKEffector, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "int get_refs() const", AS_METHODPR(IKEffector, Refs, () const, int), AS_CALL_THISCALL);
    // static void IKEffector::RegisterObject(Context* context) | File: ../IK/IKEffector.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("IKEffector", asBEHAVE_RELEASE, "void f()", AS_METHODPR(IKEffector, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "void Remove()", AS_METHODPR(IKEffector, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(IKEffector, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void RemoveInstanceDefault()", AS_METHODPR(IKEffector, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void RemoveObjectAnimation()", AS_METHODPR(IKEffector, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void ResetToDefault()", AS_METHODPR(IKEffector, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "bool Save(Serializer&) const", AS_METHODPR(IKEffector, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool SaveDefaultAttributes() const", AS_METHODPR(IKEffector, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "bool SaveJSON(JSONValue&) const", AS_METHODPR(IKEffector, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "bool SaveXML(XMLElement&) const", AS_METHODPR(IKEffector, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void SendEvent(StringHash)", AS_METHODPR(IKEffector, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(IKEffector, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetAnimationEnabled(bool)", AS_METHODPR(IKEffector, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_animationEnabled(bool)", AS_METHODPR(IKEffector, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetAnimationTime(float)", AS_METHODPR(IKEffector, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(IKEffector, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(IKEffector, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(IKEffector, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(IKEffector, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(IKEffector, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(IKEffector, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(IKEffector, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void SetBlockEvents(bool)", AS_METHODPR(IKEffector, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void IKEffector::SetChainLength(unsigned chainLength) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetChainLength(uint)", AS_METHODPR(IKEffector, SetChainLength, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_chainLength(uint)", AS_METHODPR(IKEffector, SetChainLength, (unsigned), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKEffector", "void SetEnabled(bool)", AS_METHODPR(IKEffector, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_enabled(bool)", AS_METHODPR(IKEffector, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void IKEffector::SetFeature(Feature feature, bool enable) | File: ../IK/IKEffector.h
    // Not registered because have @nobind mark
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(IKEffector, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(IKEffector, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void IKEffector::SetINHERIT_PARENT_ROTATION(bool enable) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetINHERIT_PARENT_ROTATION(bool)", AS_METHODPR(IKEffector, SetINHERIT_PARENT_ROTATION, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void SetInstanceDefault(bool)", AS_METHODPR(IKEffector, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(IKEffector, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(IKEffector, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(IKEffector, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKEffector", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(IKEffector, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void IKEffector::SetRotationDecay(float decay) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetRotationDecay(float)", AS_METHODPR(IKEffector, SetRotationDecay, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_rotationDecay(float)", AS_METHODPR(IKEffector, SetRotationDecay, (float), void), AS_CALL_THISCALL);
    // void IKEffector::SetRotationWeight(float weight) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetRotationWeight(float)", AS_METHODPR(IKEffector, SetRotationWeight, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_rotationWeight(float)", AS_METHODPR(IKEffector, SetRotationWeight, (float), void), AS_CALL_THISCALL);
    // void IKEffector::SetTargetName(const String& nodeName) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetTargetName(const String&in)", AS_METHODPR(IKEffector, SetTargetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_targetName(const String&in)", AS_METHODPR(IKEffector, SetTargetName, (const String&), void), AS_CALL_THISCALL);
    // void IKEffector::SetTargetNode(Node* targetNode) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetTargetNode(Node@+)", AS_METHODPR(IKEffector, SetTargetNode, (Node*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_targetNode(Node@+)", AS_METHODPR(IKEffector, SetTargetNode, (Node*), void), AS_CALL_THISCALL);
    // void IKEffector::SetTargetPosition(const Vector3& targetPosition) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetTargetPosition(const Vector3&in)", AS_METHODPR(IKEffector, SetTargetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_targetPosition(const Vector3&in)", AS_METHODPR(IKEffector, SetTargetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    // void IKEffector::SetTargetRotation(const Quaternion& targetRotation) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetTargetRotation(const Quaternion&in)", AS_METHODPR(IKEffector, SetTargetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_targetRotation(const Quaternion&in)", AS_METHODPR(IKEffector, SetTargetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    // void IKEffector::SetTargetRotationEuler(const Vector3& targetRotation) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetTargetRotationEuler(const Vector3&in)", AS_METHODPR(IKEffector, SetTargetRotationEuler, (const Vector3&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void SetTemporary(bool)", AS_METHODPR(IKEffector, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_temporary(bool)", AS_METHODPR(IKEffector, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void IKEffector::SetWeight(float weight) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetWeight(float)", AS_METHODPR(IKEffector, SetWeight, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_weight(float)", AS_METHODPR(IKEffector, SetWeight, (float), void), AS_CALL_THISCALL);
    // void IKEffector::SetWEIGHT_NLERP(bool enable) | File: ../IK/IKEffector.h
    engine->RegisterObjectMethod("IKEffector", "void SetWEIGHT_NLERP(bool)", AS_METHODPR(IKEffector, SetWEIGHT_NLERP, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void UnsubscribeFromAllEvents()", AS_METHODPR(IKEffector, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(IKEffector_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(IKEffector, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(IKEffector, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKEffector", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(IKEffector, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IKEffector", "int WeakRefs() const", AS_METHODPR(IKEffector, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "int get_weakRefs() const", AS_METHODPR(IKEffector, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(IKEffector, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(IKEffector, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKEffector", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(IKEffector, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("IKSolver", asBEHAVE_ADDREF, "void f()", AS_METHODPR(IKSolver, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void AllocateNetworkState()", AS_METHODPR(IKSolver, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void IKSolver::ApplyActivePoseToScene() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void ApplyActivePoseToScene()", AS_METHODPR(IKSolver, ApplyActivePoseToScene, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void ApplyAttributes()", AS_METHODPR(IKSolver, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void IKSolver::ApplyOriginalPoseToActivePose() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void ApplyOriginalPoseToActivePose()", AS_METHODPR(IKSolver, ApplyOriginalPoseToActivePose, (), void), AS_CALL_THISCALL);
    // void IKSolver::ApplyOriginalPoseToScene() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void ApplyOriginalPoseToScene()", AS_METHODPR(IKSolver, ApplyOriginalPoseToScene, (), void), AS_CALL_THISCALL);
    // void IKSolver::ApplySceneToActivePose() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void ApplySceneToActivePose()", AS_METHODPR(IKSolver, ApplySceneToActivePose, (), void), AS_CALL_THISCALL);
    // void IKSolver::ApplySceneToOriginalPose() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void ApplySceneToOriginalPose()", AS_METHODPR(IKSolver, ApplySceneToOriginalPose, (), void), AS_CALL_THISCALL);
    // void IKSolver::CalculateJointRotations() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void CalculateJointRotations()", AS_METHODPR(IKSolver, CalculateJointRotations, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void IKSolver::DrawDebugGeometry(bool depthTest) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void DrawDebugGeometry(bool)", AS_METHODPR(IKSolver, DrawDebugGeometry, (bool), void), AS_CALL_THISCALL);
    // void IKSolver::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(IKSolver, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // Algorithm IKSolver::GetAlgorithm() const | File: ../IK/IKSolver.h
    // Not registered because have @manualbind mark
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "bool GetAnimationEnabled() const", AS_METHODPR(IKSolver, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_animationEnabled() const", AS_METHODPR(IKSolver, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "Variant GetAttribute(uint) const", AS_METHODPR(IKSolver, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "Variant get_attributes(uint) const", AS_METHODPR(IKSolver, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "Variant GetAttribute(const String&in) const", AS_METHODPR(IKSolver, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(IKSolver, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(IKSolver, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(IKSolver, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(IKSolver, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "Variant GetAttributeDefault(uint) const", AS_METHODPR(IKSolver, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "Variant get_attributeDefaults(uint) const", AS_METHODPR(IKSolver, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(IKSolver, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool IKSolver::GetAUTO_SOLVE() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "bool GetAUTO_SOLVE() const", AS_METHODPR(IKSolver, GetAUTO_SOLVE, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_AUTO_SOLVE() const", AS_METHODPR(IKSolver, GetAUTO_SOLVE, () const, bool), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "bool GetBlockEvents() const", AS_METHODPR(IKSolver, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "const String& GetCategory() const", AS_METHODPR(IKSolver, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "const String& get_category() const", AS_METHODPR(IKSolver, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "Component@+ GetComponent(StringHash) const", AS_METHODPR(IKSolver, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // bool IKSolver::GetCONSTRAINTS() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "bool GetCONSTRAINTS() const", AS_METHODPR(IKSolver, GetCONSTRAINTS, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_CONSTRAINTS() const", AS_METHODPR(IKSolver, GetCONSTRAINTS, () const, bool), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "VariantMap& GetEventDataMap() const", AS_METHODPR(IKSolver, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "Object@+ GetEventSender() const", AS_METHODPR(IKSolver, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // bool IKSolver::GetFeature(Feature feature) const | File: ../IK/IKSolver.h
    // Not registered because have @nobind mark
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(IKSolver, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(IKSolver, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "const VariantMap& GetGlobalVars() const", AS_METHODPR(IKSolver, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "const VariantMap& get_globalVars() const", AS_METHODPR(IKSolver, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "uint GetID() const", AS_METHODPR(IKSolver, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "uint get_id() const", AS_METHODPR(IKSolver, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(IKSolver, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // bool IKSolver::GetJOINT_ROTATIONS() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "bool GetJOINT_ROTATIONS() const", AS_METHODPR(IKSolver, GetJOINT_ROTATIONS, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_JOINT_ROTATIONS() const", AS_METHODPR(IKSolver, GetJOINT_ROTATIONS, () const, bool), AS_CALL_THISCALL);
    // unsigned IKSolver::GetMaximumIterations() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "uint GetMaximumIterations() const", AS_METHODPR(IKSolver, GetMaximumIterations, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "uint get_maximumIterations() const", AS_METHODPR(IKSolver, GetMaximumIterations, () const, unsigned), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "Node@+ GetNode() const", AS_METHODPR(IKSolver, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "Node@+ get_node() const", AS_METHODPR(IKSolver, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "uint GetNumAttributes() const", AS_METHODPR(IKSolver, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "uint get_numAttributes() const", AS_METHODPR(IKSolver, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "uint GetNumNetworkAttributes() const", AS_METHODPR(IKSolver, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(IKSolver, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(IKSolver, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(IKSolver, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "Scene@+ GetScene() const", AS_METHODPR(IKSolver, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(IKSolver, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // bool IKSolver::GetTARGET_ROTATIONS() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "bool GetTARGET_ROTATIONS() const", AS_METHODPR(IKSolver, GetTARGET_ROTATIONS, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_TARGET_ROTATIONS() const", AS_METHODPR(IKSolver, GetTARGET_ROTATIONS, () const, bool), AS_CALL_THISCALL);
    // float IKSolver::GetTolerance() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "float GetTolerance() const", AS_METHODPR(IKSolver, GetTolerance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "float get_tolerance() const", AS_METHODPR(IKSolver, GetTolerance, () const, float), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "StringHash GetType() const", AS_METHODPR(IKSolver, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "StringHash get_type() const", AS_METHODPR(IKSolver, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "const String& GetTypeName() const", AS_METHODPR(IKSolver, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "const String& get_typeName() const", AS_METHODPR(IKSolver, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool IKSolver::GetUPDATE_ACTIVE_POSE() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "bool GetUPDATE_ACTIVE_POSE() const", AS_METHODPR(IKSolver, GetUPDATE_ACTIVE_POSE, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_UPDATE_ACTIVE_POSE() const", AS_METHODPR(IKSolver, GetUPDATE_ACTIVE_POSE, () const, bool), AS_CALL_THISCALL);
    // bool IKSolver::GetUPDATE_ORIGINAL_POSE() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "bool GetUPDATE_ORIGINAL_POSE() const", AS_METHODPR(IKSolver, GetUPDATE_ORIGINAL_POSE, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_UPDATE_ORIGINAL_POSE() const", AS_METHODPR(IKSolver, GetUPDATE_ORIGINAL_POSE, () const, bool), AS_CALL_THISCALL);
    // bool IKSolver::GetUSE_ORIGINAL_POSE() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "bool GetUSE_ORIGINAL_POSE() const", AS_METHODPR(IKSolver, GetUSE_ORIGINAL_POSE, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_USE_ORIGINAL_POSE() const", AS_METHODPR(IKSolver, GetUSE_ORIGINAL_POSE, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "bool HasEventHandlers() const", AS_METHODPR(IKSolver, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(IKSolver, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(IKSolver, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // explicit IKSolver::IKSolver(Context* context) | File: ../IK/IKSolver.h
    engine->RegisterObjectBehaviour("IKSolver", asBEHAVE_FACTORY, "IKSolver@+ f()", AS_FUNCTION(IKSolver_IKSolver_Context), AS_CALL_CDECL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "bool IsEnabled() const", AS_METHODPR(IKSolver, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_enabled() const", AS_METHODPR(IKSolver, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "bool IsEnabledEffective() const", AS_METHODPR(IKSolver, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_enabledEffective() const", AS_METHODPR(IKSolver, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "bool IsInstanceOf(StringHash) const", AS_METHODPR(IKSolver, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "bool IsReplicated() const", AS_METHODPR(IKSolver, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_replicated() const", AS_METHODPR(IKSolver, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool IsTemporary() const", AS_METHODPR(IKSolver, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_temporary() const", AS_METHODPR(IKSolver, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool Load(Deserializer&)", AS_METHODPR(IKSolver, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(IKSolver, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "bool LoadXML(const XMLElement&in)", AS_METHODPR(IKSolver, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "void MarkNetworkUpdate()", AS_METHODPR(IKSolver, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(IKSolver, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(IKSolver, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(IKSolver, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "void OnSetEnabled()", AS_METHODPR(IKSolver, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "void PrepareNetworkUpdate()", AS_METHODPR(IKSolver, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(IKSolver, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(IKSolver, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // void IKSolver::RebuildChainTrees() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void RebuildChainTrees()", AS_METHODPR(IKSolver, RebuildChainTrees, (), void), AS_CALL_THISCALL);
    // void IKSolver::RecalculateSegmentLengths() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void RecalculateSegmentLengths()", AS_METHODPR(IKSolver, RecalculateSegmentLengths, (), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IKSolver", "int Refs() const", AS_METHODPR(IKSolver, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "int get_refs() const", AS_METHODPR(IKSolver, Refs, () const, int), AS_CALL_THISCALL);
    // static void IKSolver::RegisterObject(Context* context) | File: ../IK/IKSolver.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("IKSolver", asBEHAVE_RELEASE, "void f()", AS_METHODPR(IKSolver, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "void Remove()", AS_METHODPR(IKSolver, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(IKSolver, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void RemoveInstanceDefault()", AS_METHODPR(IKSolver, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void RemoveObjectAnimation()", AS_METHODPR(IKSolver, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void ResetToDefault()", AS_METHODPR(IKSolver, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "bool Save(Serializer&) const", AS_METHODPR(IKSolver, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool SaveDefaultAttributes() const", AS_METHODPR(IKSolver, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "bool SaveJSON(JSONValue&) const", AS_METHODPR(IKSolver, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "bool SaveXML(XMLElement&) const", AS_METHODPR(IKSolver, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void SendEvent(StringHash)", AS_METHODPR(IKSolver, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(IKSolver, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void IKSolver::SetAlgorithm(Algorithm algorithm) | File: ../IK/IKSolver.h
    // Not registered because have @manualbind mark
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetAnimationEnabled(bool)", AS_METHODPR(IKSolver, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_animationEnabled(bool)", AS_METHODPR(IKSolver, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetAnimationTime(float)", AS_METHODPR(IKSolver, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(IKSolver, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(IKSolver, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(IKSolver, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(IKSolver, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(IKSolver, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(IKSolver, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(IKSolver, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void IKSolver::SetAUTO_SOLVE(bool enable) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetAUTO_SOLVE(bool)", AS_METHODPR(IKSolver, SetAUTO_SOLVE, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_AUTO_SOLVE(bool)", AS_METHODPR(IKSolver, SetAUTO_SOLVE, (bool), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void SetBlockEvents(bool)", AS_METHODPR(IKSolver, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void IKSolver::SetCONSTRAINTS(bool enable) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetCONSTRAINTS(bool)", AS_METHODPR(IKSolver, SetCONSTRAINTS, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_CONSTRAINTS(bool)", AS_METHODPR(IKSolver, SetCONSTRAINTS, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("IKSolver", "void SetEnabled(bool)", AS_METHODPR(IKSolver, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_enabled(bool)", AS_METHODPR(IKSolver, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void IKSolver::SetFeature(Feature feature, bool enable) | File: ../IK/IKSolver.h
    // Not registered because have @nobind mark
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(IKSolver, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(IKSolver, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void SetInstanceDefault(bool)", AS_METHODPR(IKSolver, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(IKSolver, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void IKSolver::SetJOINT_ROTATIONS(bool enable) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetJOINT_ROTATIONS(bool)", AS_METHODPR(IKSolver, SetJOINT_ROTATIONS, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_JOINT_ROTATIONS(bool)", AS_METHODPR(IKSolver, SetJOINT_ROTATIONS, (bool), void), AS_CALL_THISCALL);
    // void IKSolver::SetMaximumIterations(unsigned iterations) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetMaximumIterations(uint)", AS_METHODPR(IKSolver, SetMaximumIterations, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_maximumIterations(uint)", AS_METHODPR(IKSolver, SetMaximumIterations, (unsigned), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(IKSolver, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(IKSolver, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("IKSolver", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(IKSolver, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void IKSolver::SetTARGET_ROTATIONS(bool enable) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetTARGET_ROTATIONS(bool)", AS_METHODPR(IKSolver, SetTARGET_ROTATIONS, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_TARGET_ROTATIONS(bool)", AS_METHODPR(IKSolver, SetTARGET_ROTATIONS, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void SetTemporary(bool)", AS_METHODPR(IKSolver, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_temporary(bool)", AS_METHODPR(IKSolver, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void IKSolver::SetTolerance(float tolerance) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetTolerance(float)", AS_METHODPR(IKSolver, SetTolerance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_tolerance(float)", AS_METHODPR(IKSolver, SetTolerance, (float), void), AS_CALL_THISCALL);
    // void IKSolver::SetUPDATE_ACTIVE_POSE(bool enable) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetUPDATE_ACTIVE_POSE(bool)", AS_METHODPR(IKSolver, SetUPDATE_ACTIVE_POSE, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_UPDATE_ACTIVE_POSE(bool)", AS_METHODPR(IKSolver, SetUPDATE_ACTIVE_POSE, (bool), void), AS_CALL_THISCALL);
    // void IKSolver::SetUPDATE_ORIGINAL_POSE(bool enable) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetUPDATE_ORIGINAL_POSE(bool)", AS_METHODPR(IKSolver, SetUPDATE_ORIGINAL_POSE, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_UPDATE_ORIGINAL_POSE(bool)", AS_METHODPR(IKSolver, SetUPDATE_ORIGINAL_POSE, (bool), void), AS_CALL_THISCALL);
    // void IKSolver::SetUSE_ORIGINAL_POSE(bool enable) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void SetUSE_ORIGINAL_POSE(bool)", AS_METHODPR(IKSolver, SetUSE_ORIGINAL_POSE, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_USE_ORIGINAL_POSE(bool)", AS_METHODPR(IKSolver, SetUSE_ORIGINAL_POSE, (bool), void), AS_CALL_THISCALL);
    // void IKSolver::Solve() | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void Solve()", AS_METHODPR(IKSolver, Solve, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void UnsubscribeFromAllEvents()", AS_METHODPR(IKSolver, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(IKSolver_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(IKSolver, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(IKSolver, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IKSolver", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(IKSolver, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IKSolver", "int WeakRefs() const", AS_METHODPR(IKSolver, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "int get_weakRefs() const", AS_METHODPR(IKSolver, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(IKSolver, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(IKSolver, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("IKSolver", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(IKSolver, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Image", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Image, AddRef, (), void), AS_CALL_THISCALL);
    // bool Image::BeginLoad(Deserializer& source) override | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool BeginLoad(Deserializer&)", AS_METHODPR(Image, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Image::CleanupLevels() | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void CleanupLevels()", AS_METHODPR(Image, CleanupLevels, (), void), AS_CALL_THISCALL);
    // void Image::Clear(const Color& color) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void Clear(const Color&in)", AS_METHODPR(Image, Clear, (const Color&), void), AS_CALL_THISCALL);
    // void Image::ClearInt(unsigned uintColor) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void ClearInt(uint)", AS_METHODPR(Image, ClearInt, (unsigned), void), AS_CALL_THISCALL);
    // SharedPtr<Image> Image::ConvertToRGBA() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Image@+ ConvertToRGBA() const", AS_FUNCTION_OBJFIRST(Image_ConvertToRGBA_void), AS_CALL_CDECL_OBJFIRST);
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "bool EndLoad()", AS_METHODPR(Image, EndLoad, (), bool), AS_CALL_THISCALL);
    // bool Image::FlipHorizontal() | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool FlipHorizontal()", AS_METHODPR(Image, FlipHorizontal, (), bool), AS_CALL_THISCALL);
    // bool Image::FlipVertical() | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool FlipVertical()", AS_METHODPR(Image, FlipVertical, (), bool), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(Image, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "bool GetBlockEvents() const", AS_METHODPR(Image, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "const String& GetCategory() const", AS_METHODPR(Image, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "const String& get_category() const", AS_METHODPR(Image, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // unsigned Image::GetComponents() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "uint GetComponents() const", AS_METHODPR(Image, GetComponents, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "uint get_components() const", AS_METHODPR(Image, GetComponents, () const, unsigned), AS_CALL_THISCALL);
    // CompressedFormat Image::GetCompressedFormat() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "CompressedFormat GetCompressedFormat() const", AS_METHODPR(Image, GetCompressedFormat, () const, CompressedFormat), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "CompressedFormat get_compressedFormat() const", AS_METHODPR(Image, GetCompressedFormat, () const, CompressedFormat), AS_CALL_THISCALL);
    // CompressedLevel Image::GetCompressedLevel(unsigned index) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "CompressedLevel GetCompressedLevel(uint) const", AS_METHODPR(Image, GetCompressedLevel, (unsigned) const, CompressedLevel), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // unsigned char* Image::GetData() const | File: ../Resource/Image.h
    // Error: type "unsigned char*" can not automatically bind
    // SharedPtr<Image> Image::GetDecompressedImage() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Image@+ GetDecompressedImage() const", AS_FUNCTION_OBJFIRST(Image_GetDecompressedImage_void), AS_CALL_CDECL_OBJFIRST);
    // int Image::GetDepth() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "int GetDepth() const", AS_METHODPR(Image, GetDepth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_depth() const", AS_METHODPR(Image, GetDepth, () const, int), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "VariantMap& GetEventDataMap() const", AS_METHODPR(Image, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "Object@+ GetEventSender() const", AS_METHODPR(Image, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Image, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Image, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Image, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "const VariantMap& get_globalVars() const", AS_METHODPR(Image, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int Image::GetHeight() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "int GetHeight() const", AS_METHODPR(Image, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_height() const", AS_METHODPR(Image, GetHeight, () const, int), AS_CALL_THISCALL);
    // void Image::GetLevels(PODVector<Image*>& levels) | File: ../Resource/Image.h
    // Error: type "PODVector<Image*>&" can not automatically bind
    // void Image::GetLevels(PODVector<const Image*>& levels) const | File: ../Resource/Image.h
    // Error: type "PODVector<const Image*>&" can not automatically bind
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "uint GetMemoryUse() const", AS_METHODPR(Image, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "uint get_memoryUse() const", AS_METHODPR(Image, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "const String& GetName() const", AS_METHODPR(Image, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "const String& get_name() const", AS_METHODPR(Image, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "StringHash GetNameHash() const", AS_METHODPR(Image, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // SharedPtr<Image> Image::GetNextLevel() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Image@+ GetNextLevel() const", AS_FUNCTION_OBJFIRST(Image_GetNextLevel_void), AS_CALL_CDECL_OBJFIRST);
    // SharedPtr<Image> Image::GetNextSibling() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Image@+ GetNextSibling() const", AS_FUNCTION_OBJFIRST(Image_GetNextSibling_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Image::GetNumCompressedLevels() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "uint GetNumCompressedLevels() const", AS_METHODPR(Image, GetNumCompressedLevels, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "uint get_numCompressedLevels() const", AS_METHODPR(Image, GetNumCompressedLevels, () const, unsigned), AS_CALL_THISCALL);
    // Color Image::GetPixel(int x, int y) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Color GetPixel(int, int) const", AS_METHODPR(Image, GetPixel, (int, int) const, Color), AS_CALL_THISCALL);
    // Color Image::GetPixel(int x, int y, int z) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Color GetPixel(int, int, int) const", AS_METHODPR(Image, GetPixel, (int, int, int) const, Color), AS_CALL_THISCALL);
    // Color Image::GetPixelBilinear(float x, float y) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Color GetPixelBilinear(float, float) const", AS_METHODPR(Image, GetPixelBilinear, (float, float) const, Color), AS_CALL_THISCALL);
    // unsigned Image::GetPixelInt(int x, int y) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "uint GetPixelInt(int, int) const", AS_METHODPR(Image, GetPixelInt, (int, int) const, unsigned), AS_CALL_THISCALL);
    // unsigned Image::GetPixelInt(int x, int y, int z) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "uint GetPixelInt(int, int, int) const", AS_METHODPR(Image, GetPixelInt, (int, int, int) const, unsigned), AS_CALL_THISCALL);
    // Color Image::GetPixelTrilinear(float x, float y, float z) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Color GetPixelTrilinear(float, float, float) const", AS_METHODPR(Image, GetPixelTrilinear, (float, float, float) const, Color), AS_CALL_THISCALL);
    // SDL_Surface* Image::GetSDLSurface(const IntRect& rect=IntRect::ZERO) const | File: ../Resource/Image.h
    // Error: type "SDL_Surface*" can not automatically bind
    // Image* Image::GetSubimage(const IntRect& rect) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "Image@+ GetSubimage(const IntRect&in) const", AS_METHODPR(Image, GetSubimage, (const IntRect&) const, Image*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Image, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "StringHash GetType() const", AS_METHODPR(Image, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "StringHash get_type() const", AS_METHODPR(Image, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "const String& GetTypeName() const", AS_METHODPR(Image, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "const String& get_typeName() const", AS_METHODPR(Image, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "uint GetUseTimer()", AS_METHODPR(Image, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "uint get_useTimer()", AS_METHODPR(Image, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // int Image::GetWidth() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "int GetWidth() const", AS_METHODPR(Image, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_width() const", AS_METHODPR(Image, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool Image::HasAlphaChannel() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool HasAlphaChannel() const", AS_METHODPR(Image, HasAlphaChannel, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_hasAlphaChannel() const", AS_METHODPR(Image, HasAlphaChannel, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "bool HasEventHandlers() const", AS_METHODPR(Image, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Image, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Image, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // explicit Image::Image(Context* context) | File: ../Resource/Image.h
    engine->RegisterObjectBehaviour("Image", asBEHAVE_FACTORY, "Image@+ f()", AS_FUNCTION(Image_Image_Context), AS_CALL_CDECL);
    // bool Image::IsArray() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool IsArray() const", AS_METHODPR(Image, IsArray, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_array() const", AS_METHODPR(Image, IsArray, () const, bool), AS_CALL_THISCALL);
    // bool Image::IsCompressed() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool IsCompressed() const", AS_METHODPR(Image, IsCompressed, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_compressed() const", AS_METHODPR(Image, IsCompressed, () const, bool), AS_CALL_THISCALL);
    // bool Image::IsCubemap() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool IsCubemap() const", AS_METHODPR(Image, IsCubemap, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_cubemap() const", AS_METHODPR(Image, IsCubemap, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Image, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Image::IsSRGB() const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool IsSRGB() const", AS_METHODPR(Image, IsSRGB, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_sRGB() const", AS_METHODPR(Image, IsSRGB, () const, bool), AS_CALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "bool Load(Deserializer&)", AS_METHODPR(Image, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Image::LoadColorLUT(Deserializer& source) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool LoadColorLUT(Deserializer&)", AS_METHODPR(Image, LoadColorLUT, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "bool LoadFile(const String&in)", AS_METHODPR(Image, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool Load(const String&in)", AS_METHODPR(Image, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Image, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // void Image::PrecalculateLevels() | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void PrecalculateLevels()", AS_METHODPR(Image, PrecalculateLevels, (), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Image", "int Refs() const", AS_METHODPR(Image, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_refs() const", AS_METHODPR(Image, Refs, () const, int), AS_CALL_THISCALL);
    // static void Image::RegisterObject(Context* context) | File: ../Resource/Image.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Image", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Image, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "void ResetUseTimer()", AS_METHODPR(Image, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // bool Image::Resize(int width, int height) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool Resize(int, int)", AS_METHODPR(Image, Resize, (int, int), bool), AS_CALL_THISCALL);
    // bool Image::Save(Serializer& dest) const override | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool Save(Serializer&) const", AS_METHODPR(Image, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // bool Image::SaveBMP(const String& fileName) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SaveBMP(const String&in) const", AS_METHODPR(Image, SaveBMP, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Image::SaveDDS(const String& fileName) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SaveDDS(const String&in) const", AS_METHODPR(Image, SaveDDS, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Image::SaveFile(const String& fileName) const override | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SaveFile(const String&in) const", AS_METHODPR(Image, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool Save(const String&in) const", AS_METHODPR(Image, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Image::SaveJPG(const String& fileName, int quality) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SaveJPG(const String&in, int) const", AS_METHODPR(Image, SaveJPG, (const String&, int) const, bool), AS_CALL_THISCALL);
    // bool Image::SavePNG(const String& fileName) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SavePNG(const String&in) const", AS_METHODPR(Image, SavePNG, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Image::SaveTGA(const String& fileName) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SaveTGA(const String&in) const", AS_METHODPR(Image, SaveTGA, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Image::SaveWEBP(const String& fileName, float compression=0.0f) const | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SaveWEBP(const String&in, float = 0.0f) const", AS_METHODPR(Image, SaveWEBP, (const String&, float) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void SendEvent(StringHash)", AS_METHODPR(Image, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Image, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(Image, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void SetBlockEvents(bool)", AS_METHODPR(Image, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Image::SetData(const unsigned char* pixelData) | File: ../Resource/Image.h
    // Error: type "const unsigned char*" can not automatically bind
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Image, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Image, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "void SetMemoryUse(uint)", AS_METHODPR(Image, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Image", "void SetName(const String&in)", AS_METHODPR(Image, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void set_name(const String&in)", AS_METHODPR(Image, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Image::SetPixel(int x, int y, const Color& color) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void SetPixel(int, int, const Color&in)", AS_METHODPR(Image, SetPixel, (int, int, const Color&), void), AS_CALL_THISCALL);
    // void Image::SetPixel(int x, int y, int z, const Color& color) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void SetPixel(int, int, int, const Color&in)", AS_METHODPR(Image, SetPixel, (int, int, int, const Color&), void), AS_CALL_THISCALL);
    // void Image::SetPixelInt(int x, int y, unsigned uintColor) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void SetPixelInt(int, int, uint)", AS_METHODPR(Image, SetPixelInt, (int, int, unsigned), void), AS_CALL_THISCALL);
    // void Image::SetPixelInt(int x, int y, int z, unsigned uintColor) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "void SetPixelInt(int, int, int, uint)", AS_METHODPR(Image, SetPixelInt, (int, int, int, unsigned), void), AS_CALL_THISCALL);
    // bool Image::SetSize(int width, int height, unsigned components) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SetSize(int, int, uint)", AS_METHODPR(Image, SetSize, (int, int, unsigned), bool), AS_CALL_THISCALL);
    // bool Image::SetSize(int width, int height, int depth, unsigned components) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SetSize(int, int, int, uint)", AS_METHODPR(Image, SetSize, (int, int, int, unsigned), bool), AS_CALL_THISCALL);
    // bool Image::SetSubimage(const Image* image, const IntRect& rect) | File: ../Resource/Image.h
    engine->RegisterObjectMethod("Image", "bool SetSubimage(Image@+, const IntRect&in)", AS_METHODPR(Image, SetSubimage, (const Image*, const IntRect&), bool), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void UnsubscribeFromAllEvents()", AS_METHODPR(Image, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Image_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Image, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Image, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Image", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Image, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Image", "int WeakRefs() const", AS_METHODPR(Image, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_weakRefs() const", AS_METHODPR(Image, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("IndexBuffer", asBEHAVE_ADDREF, "void f()", AS_METHODPR(IndexBuffer, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("IndexBuffer", "void ClearDataLost()", AS_METHODPR(IndexBuffer, ClearDataLost, (), void), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "bool GetBlockEvents() const", AS_METHODPR(IndexBuffer, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "const String& GetCategory() const", AS_METHODPR(IndexBuffer, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "const String& get_category() const", AS_METHODPR(IndexBuffer, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "VariantMap& GetEventDataMap() const", AS_METHODPR(IndexBuffer, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "Object@+ GetEventSender() const", AS_METHODPR(IndexBuffer, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(IndexBuffer, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(IndexBuffer, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "const VariantMap& GetGlobalVars() const", AS_METHODPR(IndexBuffer, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "const VariantMap& get_globalVars() const", AS_METHODPR(IndexBuffer, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("IndexBuffer", "uint GetGPUObjectName() const", AS_METHODPR(IndexBuffer, GetGPUObjectName, () const, unsigned), AS_CALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("IndexBuffer", "Graphics@+ GetGraphics() const", AS_METHODPR(IndexBuffer, GetGraphics, () const, Graphics*), AS_CALL_THISCALL);
    // unsigned IndexBuffer::GetIndexCount() const | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "uint GetIndexCount() const", AS_METHODPR(IndexBuffer, GetIndexCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "uint get_indexCount() const", AS_METHODPR(IndexBuffer, GetIndexCount, () const, unsigned), AS_CALL_THISCALL);
    // unsigned IndexBuffer::GetIndexSize() const | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "uint GetIndexSize() const", AS_METHODPR(IndexBuffer, GetIndexSize, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "uint get_indexSize() const", AS_METHODPR(IndexBuffer, GetIndexSize, () const, unsigned), AS_CALL_THISCALL);
    // unsigned char* IndexBuffer::GetShadowData() const | File: ../Graphics/IndexBuffer.h
    // Error: type "unsigned char*" can not automatically bind
    // SharedArrayPtr<unsigned char> IndexBuffer::GetShadowDataShared() const | File: ../Graphics/IndexBuffer.h
    // Error: type "SharedArrayPtr<unsigned char>" can not automatically bind
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(IndexBuffer, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "StringHash GetType() const", AS_METHODPR(IndexBuffer, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "StringHash get_type() const", AS_METHODPR(IndexBuffer, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "const String& GetTypeName() const", AS_METHODPR(IndexBuffer, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "const String& get_typeName() const", AS_METHODPR(IndexBuffer, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool IndexBuffer::GetUsedVertexRange(unsigned start, unsigned count, unsigned& minVertex, unsigned& vertexCount) | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "bool GetUsedVertexRange(uint, uint, uint&, uint&)", AS_METHODPR(IndexBuffer, GetUsedVertexRange, (unsigned, unsigned, unsigned&, unsigned&), bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "bool HasEventHandlers() const", AS_METHODPR(IndexBuffer, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("IndexBuffer", "bool HasPendingData() const", AS_METHODPR(IndexBuffer, HasPendingData, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(IndexBuffer, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(IndexBuffer, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // explicit IndexBuffer::IndexBuffer(Context* context, bool forceHeadless=false) | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectBehaviour("IndexBuffer", asBEHAVE_FACTORY, "IndexBuffer@+ f(bool = false)", AS_FUNCTION(IndexBuffer_IndexBuffer_Context_bool), AS_CALL_CDECL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("IndexBuffer", "bool IsDataLost() const", AS_METHODPR(IndexBuffer, IsDataLost, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "bool get_dataLost() const", AS_METHODPR(IndexBuffer, IsDataLost, () const, bool), AS_CALL_THISCALL);
    // bool IndexBuffer::IsDynamic() const | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "bool IsDynamic() const", AS_METHODPR(IndexBuffer, IsDynamic, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "bool get_dynamic() const", AS_METHODPR(IndexBuffer, IsDynamic, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "bool IsInstanceOf(StringHash) const", AS_METHODPR(IndexBuffer, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool IndexBuffer::IsLocked() const | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "bool IsLocked() const", AS_METHODPR(IndexBuffer, IsLocked, () const, bool), AS_CALL_THISCALL);
    // bool IndexBuffer::IsShadowed() const | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "bool IsShadowed() const", AS_METHODPR(IndexBuffer, IsShadowed, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "bool get_shadowed() const", AS_METHODPR(IndexBuffer, IsShadowed, () const, bool), AS_CALL_THISCALL);
    // void* IndexBuffer::Lock(unsigned start, unsigned count, bool discard=false) | File: ../Graphics/IndexBuffer.h
    // Error: type "void*" can not automatically bind
    // void IndexBuffer::OnDeviceLost() override | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "void OnDeviceLost()", AS_METHODPR(IndexBuffer, OnDeviceLost, (), void), AS_CALL_THISCALL);
    // void IndexBuffer::OnDeviceReset() override | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "void OnDeviceReset()", AS_METHODPR(IndexBuffer, OnDeviceReset, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(IndexBuffer, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IndexBuffer", "int Refs() const", AS_METHODPR(IndexBuffer, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "int get_refs() const", AS_METHODPR(IndexBuffer, Refs, () const, int), AS_CALL_THISCALL);
    // void IndexBuffer::Release() override | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "void Release()", AS_METHODPR(IndexBuffer, Release, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("IndexBuffer", asBEHAVE_RELEASE, "void f()", AS_METHODPR(IndexBuffer, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void SendEvent(StringHash)", AS_METHODPR(IndexBuffer, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(IndexBuffer, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void SetBlockEvents(bool)", AS_METHODPR(IndexBuffer, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // bool IndexBuffer::SetData(const void* data) | File: ../Graphics/IndexBuffer.h
    // Error: type "const void*" can not automatically bind
    // bool IndexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard=false) | File: ../Graphics/IndexBuffer.h
    // Error: type "const void*" can not automatically bind
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(IndexBuffer, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(IndexBuffer, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void IndexBuffer::SetShadowed(bool enable) | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "void SetShadowed(bool)", AS_METHODPR(IndexBuffer, SetShadowed, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "void set_shadowed(bool)", AS_METHODPR(IndexBuffer, SetShadowed, (bool), void), AS_CALL_THISCALL);
    // bool IndexBuffer::SetSize(unsigned indexCount, bool largeIndices, bool dynamic=false) | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "bool SetSize(uint, bool, bool = false)", AS_METHODPR(IndexBuffer, SetSize, (unsigned, bool, bool), bool), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void IndexBuffer::Unlock() | File: ../Graphics/IndexBuffer.h
    engine->RegisterObjectMethod("IndexBuffer", "void Unlock()", AS_METHODPR(IndexBuffer, Unlock, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void UnsubscribeFromAllEvents()", AS_METHODPR(IndexBuffer, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(IndexBuffer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(IndexBuffer, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(IndexBuffer, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("IndexBuffer", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(IndexBuffer, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("IndexBuffer", "int WeakRefs() const", AS_METHODPR(IndexBuffer, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IndexBuffer", "int get_weakRefs() const", AS_METHODPR(IndexBuffer, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Input", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Input, AddRef, (), void), AS_CALL_THISCALL);
    // SDL_JoystickID Input::AddScreenJoystick(XMLFile* layoutFile=nullptr, XMLFile* styleFile=nullptr) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "SDL_JoystickID AddScreenJoystick(XMLFile@+ = null, XMLFile@+ = null)", AS_METHODPR(Input, AddScreenJoystick, (XMLFile*, XMLFile*), SDL_JoystickID), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Input::CenterMousePosition() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void CenterMousePosition()", AS_METHODPR(Input, CenterMousePosition, (), void), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "bool GetBlockEvents() const", AS_METHODPR(Input, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "const String& GetCategory() const", AS_METHODPR(Input, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "const String& get_category() const", AS_METHODPR(Input, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "VariantMap& GetEventDataMap() const", AS_METHODPR(Input, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "Object@+ GetEventSender() const", AS_METHODPR(Input, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Input, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Input, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Input, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "const VariantMap& get_globalVars() const", AS_METHODPR(Input, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // Vector2 Input::GetInputScale() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "Vector2 GetInputScale() const", AS_METHODPR(Input, GetInputScale, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "Vector2 get_inputScale() const", AS_METHODPR(Input, GetInputScale, () const, Vector2), AS_CALL_THISCALL);
    // JoystickState* Input::GetJoystick(SDL_JoystickID id) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "JoystickState@+ GetJoystick(SDL_JoystickID)", AS_METHODPR(Input, GetJoystick, (SDL_JoystickID), JoystickState*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "JoystickState@+ get_joysticks(SDL_JoystickID)", AS_METHODPR(Input, GetJoystick, (SDL_JoystickID), JoystickState*), AS_CALL_THISCALL);
    // JoystickState* Input::GetJoystickByIndex(unsigned index) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "JoystickState@+ GetJoystickByIndex(uint)", AS_METHODPR(Input, GetJoystickByIndex, (unsigned), JoystickState*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "JoystickState@+ get_joysticksByIndex(uint)", AS_METHODPR(Input, GetJoystickByIndex, (unsigned), JoystickState*), AS_CALL_THISCALL);
    // JoystickState* Input::GetJoystickByName(const String& name) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "JoystickState@+ GetJoystickByName(const String&in)", AS_METHODPR(Input, GetJoystickByName, (const String&), JoystickState*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "JoystickState@+ get_joysticksByName(const String&in)", AS_METHODPR(Input, GetJoystickByName, (const String&), JoystickState*), AS_CALL_THISCALL);
    // bool Input::GetKeyDown(Key key) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetKeyDown(Key) const", AS_METHODPR(Input, GetKeyDown, (Key) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_keyDown(Key) const", AS_METHODPR(Input, GetKeyDown, (Key) const, bool), AS_CALL_THISCALL);
    // Key Input::GetKeyFromName(const String& name) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "Key GetKeyFromName(const String&in) const", AS_METHODPR(Input, GetKeyFromName, (const String&) const, Key), AS_CALL_THISCALL);
    // Key Input::GetKeyFromScancode(Scancode scancode) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "Key GetKeyFromScancode(Scancode) const", AS_METHODPR(Input, GetKeyFromScancode, (Scancode) const, Key), AS_CALL_THISCALL);
    // String Input::GetKeyName(Key key) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "String GetKeyName(Key) const", AS_METHODPR(Input, GetKeyName, (Key) const, String), AS_CALL_THISCALL);
    // bool Input::GetKeyPress(Key key) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetKeyPress(Key) const", AS_METHODPR(Input, GetKeyPress, (Key) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_keyPress(Key) const", AS_METHODPR(Input, GetKeyPress, (Key) const, bool), AS_CALL_THISCALL);
    // bool Input::GetMouseButtonDown(MouseButtonFlags button) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetMouseButtonDown(MouseButtonFlags) const", AS_METHODPR(Input, GetMouseButtonDown, (MouseButtonFlags) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseButtonDown(MouseButtonFlags) const", AS_METHODPR(Input, GetMouseButtonDown, (MouseButtonFlags) const, bool), AS_CALL_THISCALL);
    // bool Input::GetMouseButtonPress(MouseButtonFlags button) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetMouseButtonPress(MouseButtonFlags) const", AS_METHODPR(Input, GetMouseButtonPress, (MouseButtonFlags) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseButtonPress(MouseButtonFlags) const", AS_METHODPR(Input, GetMouseButtonPress, (MouseButtonFlags) const, bool), AS_CALL_THISCALL);
    // MouseMode Input::GetMouseMode() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "MouseMode GetMouseMode() const", AS_METHODPR(Input, GetMouseMode, () const, MouseMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "MouseMode get_mouseMode() const", AS_METHODPR(Input, GetMouseMode, () const, MouseMode), AS_CALL_THISCALL);
    // IntVector2 Input::GetMouseMove() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "IntVector2 GetMouseMove() const", AS_METHODPR(Input, GetMouseMove, () const, IntVector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "IntVector2 get_mouseMove() const", AS_METHODPR(Input, GetMouseMove, () const, IntVector2), AS_CALL_THISCALL);
    // int Input::GetMouseMoveWheel() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "int GetMouseMoveWheel() const", AS_METHODPR(Input, GetMouseMoveWheel, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_mouseMoveWheel() const", AS_METHODPR(Input, GetMouseMoveWheel, () const, int), AS_CALL_THISCALL);
    // int Input::GetMouseMoveX() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "int GetMouseMoveX() const", AS_METHODPR(Input, GetMouseMoveX, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_mouseMoveX() const", AS_METHODPR(Input, GetMouseMoveX, () const, int), AS_CALL_THISCALL);
    // int Input::GetMouseMoveY() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "int GetMouseMoveY() const", AS_METHODPR(Input, GetMouseMoveY, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_mouseMoveY() const", AS_METHODPR(Input, GetMouseMoveY, () const, int), AS_CALL_THISCALL);
    // IntVector2 Input::GetMousePosition() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "IntVector2 GetMousePosition() const", AS_METHODPR(Input, GetMousePosition, () const, IntVector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "IntVector2 get_mousePosition() const", AS_METHODPR(Input, GetMousePosition, () const, IntVector2), AS_CALL_THISCALL);
    // unsigned Input::GetNumJoysticks() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "uint GetNumJoysticks() const", AS_METHODPR(Input, GetNumJoysticks, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "uint get_numJoysticks() const", AS_METHODPR(Input, GetNumJoysticks, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Input::GetNumTouches() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "uint GetNumTouches() const", AS_METHODPR(Input, GetNumTouches, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "uint get_numTouches() const", AS_METHODPR(Input, GetNumTouches, () const, unsigned), AS_CALL_THISCALL);
    // bool Input::GetQualifierDown(Qualifier qualifier) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetQualifierDown(Qualifier) const", AS_METHODPR(Input, GetQualifierDown, (Qualifier) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_qualifierDown(Qualifier) const", AS_METHODPR(Input, GetQualifierDown, (Qualifier) const, bool), AS_CALL_THISCALL);
    // bool Input::GetQualifierPress(Qualifier qualifier) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetQualifierPress(Qualifier) const", AS_METHODPR(Input, GetQualifierPress, (Qualifier) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_qualifierPress(Qualifier) const", AS_METHODPR(Input, GetQualifierPress, (Qualifier) const, bool), AS_CALL_THISCALL);
    // QualifierFlags Input::GetQualifiers() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "QualifierFlags GetQualifiers() const", AS_METHODPR(Input, GetQualifiers, () const, QualifierFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "QualifierFlags get_qualifiers() const", AS_METHODPR(Input, GetQualifiers, () const, QualifierFlags), AS_CALL_THISCALL);
    // bool Input::GetScancodeDown(Scancode scancode) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetScancodeDown(Scancode) const", AS_METHODPR(Input, GetScancodeDown, (Scancode) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_scancodeDown(Scancode) const", AS_METHODPR(Input, GetScancodeDown, (Scancode) const, bool), AS_CALL_THISCALL);
    // Scancode Input::GetScancodeFromKey(Key key) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "Scancode GetScancodeFromKey(Key) const", AS_METHODPR(Input, GetScancodeFromKey, (Key) const, Scancode), AS_CALL_THISCALL);
    // Scancode Input::GetScancodeFromName(const String& name) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "Scancode GetScancodeFromName(const String&in) const", AS_METHODPR(Input, GetScancodeFromName, (const String&) const, Scancode), AS_CALL_THISCALL);
    // String Input::GetScancodeName(Scancode scancode) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "String GetScancodeName(Scancode) const", AS_METHODPR(Input, GetScancodeName, (Scancode) const, String), AS_CALL_THISCALL);
    // bool Input::GetScancodePress(Scancode scancode) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetScancodePress(Scancode) const", AS_METHODPR(Input, GetScancodePress, (Scancode) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_scancodePress(Scancode) const", AS_METHODPR(Input, GetScancodePress, (Scancode) const, bool), AS_CALL_THISCALL);
    // bool Input::GetScreenKeyboardSupport() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetScreenKeyboardSupport() const", AS_METHODPR(Input, GetScreenKeyboardSupport, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_screenKeyboardSupport() const", AS_METHODPR(Input, GetScreenKeyboardSupport, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Input, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // bool Input::GetToggleFullscreen() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetToggleFullscreen() const", AS_METHODPR(Input, GetToggleFullscreen, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_toggleFullscreen() const", AS_METHODPR(Input, GetToggleFullscreen, () const, bool), AS_CALL_THISCALL);
    // TouchState* Input::GetTouch(unsigned index) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "TouchState@+ GetTouch(uint) const", AS_METHODPR(Input, GetTouch, (unsigned) const, TouchState*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "TouchState@+ get_touches(uint) const", AS_METHODPR(Input, GetTouch, (unsigned) const, TouchState*), AS_CALL_THISCALL);
    // bool Input::GetTouchEmulation() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool GetTouchEmulation() const", AS_METHODPR(Input, GetTouchEmulation, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_touchEmulation() const", AS_METHODPR(Input, GetTouchEmulation, () const, bool), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "StringHash GetType() const", AS_METHODPR(Input, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "StringHash get_type() const", AS_METHODPR(Input, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "const String& GetTypeName() const", AS_METHODPR(Input, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "const String& get_typeName() const", AS_METHODPR(Input, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "bool HasEventHandlers() const", AS_METHODPR(Input, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Input::HasFocus() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool HasFocus()", AS_METHODPR(Input, HasFocus, (), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_focus()", AS_METHODPR(Input, HasFocus, (), bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Input, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Input, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // explicit Input::Input(Context* context) | File: ../Input/Input.h
    engine->RegisterObjectBehaviour("Input", asBEHAVE_FACTORY, "Input@+ f()", AS_FUNCTION(Input_Input_Context), AS_CALL_CDECL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Input, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Input::IsMinimized() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool IsMinimized() const", AS_METHODPR(Input, IsMinimized, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_minimized() const", AS_METHODPR(Input, IsMinimized, () const, bool), AS_CALL_THISCALL);
    // bool Input::IsMouseGrabbed() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool IsMouseGrabbed() const", AS_METHODPR(Input, IsMouseGrabbed, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseGrabbed() const", AS_METHODPR(Input, IsMouseGrabbed, () const, bool), AS_CALL_THISCALL);
    // bool Input::IsMouseLocked() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool IsMouseLocked() const", AS_METHODPR(Input, IsMouseLocked, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseLocked() const", AS_METHODPR(Input, IsMouseLocked, () const, bool), AS_CALL_THISCALL);
    // bool Input::IsMouseVisible() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool IsMouseVisible() const", AS_METHODPR(Input, IsMouseVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseVisible() const", AS_METHODPR(Input, IsMouseVisible, () const, bool), AS_CALL_THISCALL);
    // bool Input::IsScreenJoystickVisible(SDL_JoystickID id) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool IsScreenJoystickVisible(SDL_JoystickID) const", AS_METHODPR(Input, IsScreenJoystickVisible, (SDL_JoystickID) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_screenJoystickVisible(SDL_JoystickID) const", AS_METHODPR(Input, IsScreenJoystickVisible, (SDL_JoystickID) const, bool), AS_CALL_THISCALL);
    // bool Input::IsScreenKeyboardVisible() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool IsScreenKeyboardVisible() const", AS_METHODPR(Input, IsScreenKeyboardVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_screenKeyboardVisible() const", AS_METHODPR(Input, IsScreenKeyboardVisible, () const, bool), AS_CALL_THISCALL);
    // unsigned Input::LoadGestures(Deserializer& source) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "uint LoadGestures(Deserializer&)", AS_METHODPR(Input, LoadGestures, (Deserializer&), unsigned), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Input, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // bool Input::RecordGesture() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool RecordGesture()", AS_METHODPR(Input, RecordGesture, (), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Input", "int Refs() const", AS_METHODPR(Input, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_refs() const", AS_METHODPR(Input, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Input", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Input, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Input::RemoveAllGestures() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void RemoveAllGestures()", AS_METHODPR(Input, RemoveAllGestures, (), void), AS_CALL_THISCALL);
    // bool Input::RemoveGesture(unsigned gestureID) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool RemoveGesture(uint)", AS_METHODPR(Input, RemoveGesture, (unsigned), bool), AS_CALL_THISCALL);
    // bool Input::RemoveScreenJoystick(SDL_JoystickID id) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool RemoveScreenJoystick(SDL_JoystickID)", AS_METHODPR(Input, RemoveScreenJoystick, (SDL_JoystickID), bool), AS_CALL_THISCALL);
    // void Input::ResetMouseGrabbed() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void ResetMouseGrabbed()", AS_METHODPR(Input, ResetMouseGrabbed, (), void), AS_CALL_THISCALL);
    // void Input::ResetMouseMode() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void ResetMouseMode()", AS_METHODPR(Input, ResetMouseMode, (), void), AS_CALL_THISCALL);
    // void Input::ResetMouseVisible() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void ResetMouseVisible()", AS_METHODPR(Input, ResetMouseVisible, (), void), AS_CALL_THISCALL);
    // bool Input::SaveGesture(Serializer& dest, unsigned gestureID) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool SaveGesture(Serializer&, uint)", AS_METHODPR(Input, SaveGesture, (Serializer&, unsigned), bool), AS_CALL_THISCALL);
    // bool Input::SaveGestures(Serializer& dest) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "bool SaveGestures(Serializer&)", AS_METHODPR(Input, SaveGestures, (Serializer&), bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void SendEvent(StringHash)", AS_METHODPR(Input, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Input, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void SetBlockEvents(bool)", AS_METHODPR(Input, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Input, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Input, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Input::SetMouseGrabbed(bool grab, bool suppressEvent=false) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetMouseGrabbed(bool, bool = false)", AS_METHODPR(Input, SetMouseGrabbed, (bool, bool), void), AS_CALL_THISCALL);
    // void Input::SetMouseMode(MouseMode mode, bool suppressEvent=false) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetMouseMode(MouseMode, bool = false)", AS_METHODPR(Input, SetMouseMode, (MouseMode, bool), void), AS_CALL_THISCALL);
    // void Input::SetMousePosition(const IntVector2& position) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetMousePosition(const IntVector2&in)", AS_METHODPR(Input, SetMousePosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_mousePosition(const IntVector2&in)", AS_METHODPR(Input, SetMousePosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Input::SetMouseVisible(bool enable, bool suppressEvent=false) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetMouseVisible(bool, bool = false)", AS_METHODPR(Input, SetMouseVisible, (bool, bool), void), AS_CALL_THISCALL);
    // void Input::SetScreenJoystickVisible(SDL_JoystickID id, bool enable) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetScreenJoystickVisible(SDL_JoystickID, bool)", AS_METHODPR(Input, SetScreenJoystickVisible, (SDL_JoystickID, bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_screenJoystickVisible(SDL_JoystickID, bool)", AS_METHODPR(Input, SetScreenJoystickVisible, (SDL_JoystickID, bool), void), AS_CALL_THISCALL);
    // void Input::SetScreenKeyboardVisible(bool enable) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetScreenKeyboardVisible(bool)", AS_METHODPR(Input, SetScreenKeyboardVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_screenKeyboardVisible(bool)", AS_METHODPR(Input, SetScreenKeyboardVisible, (bool), void), AS_CALL_THISCALL);
    // void Input::SetToggleFullscreen(bool enable) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetToggleFullscreen(bool)", AS_METHODPR(Input, SetToggleFullscreen, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_toggleFullscreen(bool)", AS_METHODPR(Input, SetToggleFullscreen, (bool), void), AS_CALL_THISCALL);
    // void Input::SetTouchEmulation(bool enable) | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void SetTouchEmulation(bool)", AS_METHODPR(Input, SetTouchEmulation, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_touchEmulation(bool)", AS_METHODPR(Input, SetTouchEmulation, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void UnsubscribeFromAllEvents()", AS_METHODPR(Input, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Input_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Input, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Input, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Input", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Input, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Input::Update() | File: ../Input/Input.h
    engine->RegisterObjectMethod("Input", "void Update()", AS_METHODPR(Input, Update, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Input", "int WeakRefs() const", AS_METHODPR(Input, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_weakRefs() const", AS_METHODPR(Input, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("IntRect", "int Bottom() const", AS_METHODPR(IntRect, Bottom, () const, int), AS_CALL_THISCALL);
    // void IntRect::Clip(const IntRect& rect) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "void Clip(const IntRect&in)", AS_METHODPR(IntRect, Clip, (const IntRect&), void), AS_CALL_THISCALL);
    // const int* IntRect::Data() const | File: ../Math/Rect.h
    // Error: type "const int*" can not automatically bind
    // int IntRect::Height() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "int Height() const", AS_METHODPR(IntRect, Height, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "int get_height() const", AS_METHODPR(IntRect, Height, () const, int), AS_CALL_THISCALL);
    // IntRect::IntRect(const IntVector2& min, const IntVector2& max) noexcept | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in, const IntVector2&in)", AS_FUNCTION_OBJFIRST(IntRect_IntRect_IntVector2_IntVector2), AS_CALL_CDECL_OBJFIRST);
    // IntRect::IntRect(int left, int top, int right, int bottom) noexcept | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(int, int, int, int)", AS_FUNCTION_OBJFIRST(IntRect_IntRect_int_int_int_int), AS_CALL_CDECL_OBJFIRST);
    // explicit IntRect::IntRect(const int* data) noexcept | File: ../Math/Rect.h
    // Error: type "const int*" can not automatically bind
    // Intersection IntRect::IsInside(const IntVector2& point) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "Intersection IsInside(const IntVector2&in) const", AS_METHODPR(IntRect, IsInside, (const IntVector2&) const, Intersection), AS_CALL_THISCALL);
    // Intersection IntRect::IsInside(const IntRect& rect) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "Intersection IsInside(const IntRect&in) const", AS_METHODPR(IntRect, IsInside, (const IntRect&) const, Intersection), AS_CALL_THISCALL);
    // int IntRect::Left() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "int Left() const", AS_METHODPR(IntRect, Left, () const, int), AS_CALL_THISCALL);
    // IntVector2 IntRect::Max() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntVector2 Max() const", AS_METHODPR(IntRect, Max, () const, IntVector2), AS_CALL_THISCALL);
    // void IntRect::Merge(const IntRect& rect) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "void Merge(const IntRect&in)", AS_METHODPR(IntRect, Merge, (const IntRect&), void), AS_CALL_THISCALL);
    // IntVector2 IntRect::Min() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntVector2 Min() const", AS_METHODPR(IntRect, Min, () const, IntVector2), AS_CALL_THISCALL);
    // IntRect IntRect::operator*(float value) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect opMul(float) const", AS_METHODPR(IntRect, operator*, (float) const, IntRect), AS_CALL_THISCALL);
    // IntRect& IntRect::operator*=(float value) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect& opMulAssign(float)", AS_METHODPR(IntRect, operator*=, (float), IntRect&), AS_CALL_THISCALL);
    // IntRect IntRect::operator+(const IntRect& rhs) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect opAdd(const IntRect&in) const", AS_METHODPR(IntRect, operator+, (const IntRect&) const, IntRect), AS_CALL_THISCALL);
    // IntRect& IntRect::operator+=(const IntRect& rhs) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect& opAddAssign(const IntRect&in)", AS_METHODPR(IntRect, operator+=, (const IntRect&), IntRect&), AS_CALL_THISCALL);
    // IntRect IntRect::operator-(const IntRect& rhs) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect opSub(const IntRect&in) const", AS_METHODPR(IntRect, operator-, (const IntRect&) const, IntRect), AS_CALL_THISCALL);
    // IntRect& IntRect::operator-=(const IntRect& rhs) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect& opSubAssign(const IntRect&in)", AS_METHODPR(IntRect, operator-=, (const IntRect&), IntRect&), AS_CALL_THISCALL);
    // IntRect IntRect::operator/(float value) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect opDiv(float) const", AS_METHODPR(IntRect, operator/, (float) const, IntRect), AS_CALL_THISCALL);
    // IntRect& IntRect::operator/=(float value) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntRect& opDivAssign(float)", AS_METHODPR(IntRect, operator/=, (float), IntRect&), AS_CALL_THISCALL);
    // bool IntRect::operator==(const IntRect& rhs) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "bool opEquals(const IntRect&in) const", AS_METHODPR(IntRect, operator==, (const IntRect&) const, bool), AS_CALL_THISCALL);
    // int IntRect::Right() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "int Right() const", AS_METHODPR(IntRect, Right, () const, int), AS_CALL_THISCALL);
    // IntVector2 IntRect::Size() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "IntVector2 Size() const", AS_METHODPR(IntRect, Size, () const, IntVector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "IntVector2 get_size() const", AS_METHODPR(IntRect, Size, () const, IntVector2), AS_CALL_THISCALL);
    // int IntRect::Top() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "int Top() const", AS_METHODPR(IntRect, Top, () const, int), AS_CALL_THISCALL);
    // String IntRect::ToString() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "String ToString() const", AS_METHODPR(IntRect, ToString, () const, String), AS_CALL_THISCALL);
    // int IntRect::Width() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("IntRect", "int Width() const", AS_METHODPR(IntRect, Width, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "int get_width() const", AS_METHODPR(IntRect, Width, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(int, int)", AS_FUNCTION_OBJFIRST(IntVector2_IntVector2_int_int), AS_CALL_CDECL_OBJFIRST);
    // explicit IntVector2::IntVector2(const int* data) noexcept | File: ../Math/Vector2.h
    // Error: type "const int*" can not automatically bind
    // explicit IntVector2::IntVector2(const float* data) | File: ../Math/Vector2.h
    // Error: type "const float*" can not automatically bind
    // IntVector2::IntVector2(const IntVector2& rhs) noexcept=default | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", AS_FUNCTION_OBJFIRST(IntVector2_IntVector2_IntVector2), AS_CALL_CDECL_OBJFIRST);
    // float IntVector2::Length() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "float Length() const", AS_METHODPR(IntVector2, Length, () const, float), AS_CALL_THISCALL);
    // IntVector2 IntVector2::operator*(int rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opMul(int) const", AS_METHODPR(IntVector2, operator*, (int) const, IntVector2), AS_CALL_THISCALL);
    // IntVector2 IntVector2::operator*(const IntVector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opMul(const IntVector2&in) const", AS_METHODPR(IntVector2, operator*, (const IntVector2&) const, IntVector2), AS_CALL_THISCALL);
    // IntVector2& IntVector2::operator*=(int rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opMulAssign(int)", AS_METHODPR(IntVector2, operator*=, (int), IntVector2&), AS_CALL_THISCALL);
    // IntVector2& IntVector2::operator*=(const IntVector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opMulAssign(const IntVector2&in)", AS_METHODPR(IntVector2, operator*=, (const IntVector2&), IntVector2&), AS_CALL_THISCALL);
    // IntVector2 IntVector2::operator+(const IntVector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opAdd(const IntVector2&in) const", AS_METHODPR(IntVector2, operator+, (const IntVector2&) const, IntVector2), AS_CALL_THISCALL);
    // IntVector2& IntVector2::operator+=(const IntVector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opAddAssign(const IntVector2&in)", AS_METHODPR(IntVector2, operator+=, (const IntVector2&), IntVector2&), AS_CALL_THISCALL);
    // IntVector2 IntVector2::operator-() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opNeg() const", AS_METHODPR(IntVector2, operator-, () const, IntVector2), AS_CALL_THISCALL);
    // IntVector2 IntVector2::operator-(const IntVector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opSub(const IntVector2&in) const", AS_METHODPR(IntVector2, operator-, (const IntVector2&) const, IntVector2), AS_CALL_THISCALL);
    // IntVector2& IntVector2::operator-=(const IntVector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opSubAssign(const IntVector2&in)", AS_METHODPR(IntVector2, operator-=, (const IntVector2&), IntVector2&), AS_CALL_THISCALL);
    // IntVector2 IntVector2::operator/(int rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opDiv(int) const", AS_METHODPR(IntVector2, operator/, (int) const, IntVector2), AS_CALL_THISCALL);
    // IntVector2 IntVector2::operator/(const IntVector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opDiv(const IntVector2&in) const", AS_METHODPR(IntVector2, operator/, (const IntVector2&) const, IntVector2), AS_CALL_THISCALL);
    // IntVector2& IntVector2::operator/=(int rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opDivAssign(int)", AS_METHODPR(IntVector2, operator/=, (int), IntVector2&), AS_CALL_THISCALL);
    // IntVector2& IntVector2::operator/=(const IntVector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opDivAssign(const IntVector2&in)", AS_METHODPR(IntVector2, operator/=, (const IntVector2&), IntVector2&), AS_CALL_THISCALL);
    // IntVector2& IntVector2::operator=(const IntVector2& rhs) noexcept=default | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opAssign(const IntVector2&in)", AS_METHODPR(IntVector2, operator=, (const IntVector2&), IntVector2&), AS_CALL_THISCALL);
    // bool IntVector2::operator==(const IntVector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "bool opEquals(const IntVector2&in) const", AS_METHODPR(IntVector2, operator==, (const IntVector2&) const, bool), AS_CALL_THISCALL);
    // unsigned IntVector2::ToHash() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "uint ToHash() const", AS_METHODPR(IntVector2, ToHash, () const, unsigned), AS_CALL_THISCALL);
    // String IntVector2::ToString() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "String ToString() const", AS_METHODPR(IntVector2, ToString, () const, String), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f(int, int, int)", AS_FUNCTION_OBJFIRST(IntVector3_IntVector3_int_int_int), AS_CALL_CDECL_OBJFIRST);
    // explicit IntVector3::IntVector3(const int* data) noexcept | File: ../Math/Vector3.h
    // Error: type "const int*" can not automatically bind
    // IntVector3::IntVector3(const IntVector3& rhs) noexcept=default | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f(const IntVector3&in)", AS_FUNCTION_OBJFIRST(IntVector3_IntVector3_IntVector3), AS_CALL_CDECL_OBJFIRST);
    // float IntVector3::Length() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "float Length() const", AS_METHODPR(IntVector3, Length, () const, float), AS_CALL_THISCALL);
    // IntVector3 IntVector3::operator*(int rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opMul(int) const", AS_METHODPR(IntVector3, operator*, (int) const, IntVector3), AS_CALL_THISCALL);
    // IntVector3 IntVector3::operator*(const IntVector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opMul(const IntVector3&in) const", AS_METHODPR(IntVector3, operator*, (const IntVector3&) const, IntVector3), AS_CALL_THISCALL);
    // IntVector3& IntVector3::operator*=(int rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opMulAssign(int)", AS_METHODPR(IntVector3, operator*=, (int), IntVector3&), AS_CALL_THISCALL);
    // IntVector3& IntVector3::operator*=(const IntVector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opMulAssign(const IntVector3&in)", AS_METHODPR(IntVector3, operator*=, (const IntVector3&), IntVector3&), AS_CALL_THISCALL);
    // IntVector3 IntVector3::operator+(const IntVector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opAdd(const IntVector3&in) const", AS_METHODPR(IntVector3, operator+, (const IntVector3&) const, IntVector3), AS_CALL_THISCALL);
    // IntVector3& IntVector3::operator+=(const IntVector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opAddAssign(const IntVector3&in)", AS_METHODPR(IntVector3, operator+=, (const IntVector3&), IntVector3&), AS_CALL_THISCALL);
    // IntVector3 IntVector3::operator-() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opNeg() const", AS_METHODPR(IntVector3, operator-, () const, IntVector3), AS_CALL_THISCALL);
    // IntVector3 IntVector3::operator-(const IntVector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opSub(const IntVector3&in) const", AS_METHODPR(IntVector3, operator-, (const IntVector3&) const, IntVector3), AS_CALL_THISCALL);
    // IntVector3& IntVector3::operator-=(const IntVector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opSubAssign(const IntVector3&in)", AS_METHODPR(IntVector3, operator-=, (const IntVector3&), IntVector3&), AS_CALL_THISCALL);
    // IntVector3 IntVector3::operator/(int rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opDiv(int) const", AS_METHODPR(IntVector3, operator/, (int) const, IntVector3), AS_CALL_THISCALL);
    // IntVector3 IntVector3::operator/(const IntVector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opDiv(const IntVector3&in) const", AS_METHODPR(IntVector3, operator/, (const IntVector3&) const, IntVector3), AS_CALL_THISCALL);
    // IntVector3& IntVector3::operator/=(int rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opDivAssign(int)", AS_METHODPR(IntVector3, operator/=, (int), IntVector3&), AS_CALL_THISCALL);
    // IntVector3& IntVector3::operator/=(const IntVector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opDivAssign(const IntVector3&in)", AS_METHODPR(IntVector3, operator/=, (const IntVector3&), IntVector3&), AS_CALL_THISCALL);
    // IntVector3& IntVector3::operator=(const IntVector3& rhs) noexcept=default | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opAssign(const IntVector3&in)", AS_METHODPR(IntVector3, operator=, (const IntVector3&), IntVector3&), AS_CALL_THISCALL);
    // bool IntVector3::operator==(const IntVector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "bool opEquals(const IntVector3&in) const", AS_METHODPR(IntVector3, operator==, (const IntVector3&) const, bool), AS_CALL_THISCALL);
    // unsigned IntVector3::ToHash() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "uint ToHash() const", AS_METHODPR(IntVector3, ToHash, () const, unsigned), AS_CALL_THISCALL);
    // String IntVector3::ToString() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "String ToString() const", AS_METHODPR(IntVector3, ToString, () const, String), AS_CALL_THISCALL);
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
