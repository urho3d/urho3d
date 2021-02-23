// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

#ifdef URHO3D_PHYSICS
// explicit Constraint::Constraint(Context* context) | File: ../Physics/Constraint.h
static Constraint* Constraint_Constraint_Context()
{
    return new Constraint(GetScriptContext());
}
#endif

#ifdef URHO3D_PHYSICS
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Constraint_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Constraint* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit Constraint2D::Constraint2D(Context* context) | File: ../Urho2D/Constraint2D.h
static Constraint2D* Constraint2D_Constraint2D_Context()
{
    return new Constraint2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Constraint2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Constraint2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit ConstraintDistance2D::ConstraintDistance2D(Context* context) | File: ../Urho2D/ConstraintDistance2D.h
static ConstraintDistance2D* ConstraintDistance2D_ConstraintDistance2D_Context()
{
    return new ConstraintDistance2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ConstraintDistance2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ConstraintDistance2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit ConstraintFriction2D::ConstraintFriction2D(Context* context) | File: ../Urho2D/ConstraintFriction2D.h
static ConstraintFriction2D* ConstraintFriction2D_ConstraintFriction2D_Context()
{
    return new ConstraintFriction2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ConstraintFriction2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ConstraintFriction2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit ConstraintGear2D::ConstraintGear2D(Context* context) | File: ../Urho2D/ConstraintGear2D.h
static ConstraintGear2D* ConstraintGear2D_ConstraintGear2D_Context()
{
    return new ConstraintGear2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ConstraintGear2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ConstraintGear2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit ConstraintMotor2D::ConstraintMotor2D(Context* context) | File: ../Urho2D/ConstraintMotor2D.h
static ConstraintMotor2D* ConstraintMotor2D_ConstraintMotor2D_Context()
{
    return new ConstraintMotor2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ConstraintMotor2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ConstraintMotor2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit ConstraintMouse2D::ConstraintMouse2D(Context* context) | File: ../Urho2D/ConstraintMouse2D.h
static ConstraintMouse2D* ConstraintMouse2D_ConstraintMouse2D_Context()
{
    return new ConstraintMouse2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ConstraintMouse2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ConstraintMouse2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit ConstraintPrismatic2D::ConstraintPrismatic2D(Context* context) | File: ../Urho2D/ConstraintPrismatic2D.h
static ConstraintPrismatic2D* ConstraintPrismatic2D_ConstraintPrismatic2D_Context()
{
    return new ConstraintPrismatic2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ConstraintPrismatic2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ConstraintPrismatic2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit ConstraintPulley2D::ConstraintPulley2D(Context* context) | File: ../Urho2D/ConstraintPulley2D.h
static ConstraintPulley2D* ConstraintPulley2D_ConstraintPulley2D_Context()
{
    return new ConstraintPulley2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ConstraintPulley2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ConstraintPulley2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit ConstraintRevolute2D::ConstraintRevolute2D(Context* context) | File: ../Urho2D/ConstraintRevolute2D.h
static ConstraintRevolute2D* ConstraintRevolute2D_ConstraintRevolute2D_Context()
{
    return new ConstraintRevolute2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ConstraintRevolute2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ConstraintRevolute2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit ConstraintRope2D::ConstraintRope2D(Context* context) | File: ../Urho2D/ConstraintRope2D.h
static ConstraintRope2D* ConstraintRope2D_ConstraintRope2D_Context()
{
    return new ConstraintRope2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ConstraintRope2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ConstraintRope2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit ConstraintWeld2D::ConstraintWeld2D(Context* context) | File: ../Urho2D/ConstraintWeld2D.h
static ConstraintWeld2D* ConstraintWeld2D_ConstraintWeld2D_Context()
{
    return new ConstraintWeld2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ConstraintWeld2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ConstraintWeld2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit ConstraintWheel2D::ConstraintWheel2D(Context* context) | File: ../Urho2D/ConstraintWheel2D.h
static ConstraintWheel2D* ConstraintWheel2D_ConstraintWheel2D_Context()
{
    return new ConstraintWheel2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ConstraintWheel2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ConstraintWheel2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

void ASRegisterGenerated_Members_Constraint(asIScriptEngine* engine)
{
#ifdef URHO3D_PHYSICS
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Constraint", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Constraint, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void AllocateNetworkState()", AS_METHODPR(Constraint, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Constraint::ApplyAttributes() override | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void ApplyAttributes()", AS_METHODPR(Constraint, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void Constraint::ApplyFrames() | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void ApplyFrames()", AS_METHODPR(Constraint, ApplyFrames, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit Constraint::Constraint(Context* context) | File: ../Physics/Constraint.h
    engine->RegisterObjectBehaviour("Constraint", asBEHAVE_FACTORY, "Constraint@+ f()", AS_FUNCTION(Constraint_Constraint_Context), AS_CALL_CDECL);
    // void Constraint::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Constraint, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "bool GetAnimationEnabled() const", AS_METHODPR(Constraint, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool get_animationEnabled() const", AS_METHODPR(Constraint, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "Variant GetAttribute(uint) const", AS_METHODPR(Constraint, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "Variant get_attributes(uint) const", AS_METHODPR(Constraint, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "Variant GetAttribute(const String&in) const", AS_METHODPR(Constraint, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Constraint, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Constraint, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Constraint, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Constraint, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Constraint, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Constraint, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Constraint, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "bool GetBlockEvents() const", AS_METHODPR(Constraint, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "const String& GetCategory() const", AS_METHODPR(Constraint, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const String& get_category() const", AS_METHODPR(Constraint, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // float Constraint::GetCFM() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "float GetCFM() const", AS_METHODPR(Constraint, GetCFM, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "float get_cfm() const", AS_METHODPR(Constraint, GetCFM, () const, float), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Constraint, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // btTypedConstraint* Constraint::GetConstraint() const | File: ../Physics/Constraint.h
    // Error: type "btTypedConstraint*" can not automatically bind
    // ConstraintType Constraint::GetConstraintType() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "ConstraintType GetConstraintType() const", AS_METHODPR(Constraint, GetConstraintType, () const, ConstraintType), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "ConstraintType get_constraintType() const", AS_METHODPR(Constraint, GetConstraintType, () const, ConstraintType), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // void Constraint::GetDependencyNodes(PODVector<Node*>& dest) override | File: ../Physics/Constraint.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // bool Constraint::GetDisableCollision() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "bool GetDisableCollision() const", AS_METHODPR(Constraint, GetDisableCollision, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool get_disableCollision() const", AS_METHODPR(Constraint, GetDisableCollision, () const, bool), AS_CALL_THISCALL);
    // float Constraint::GetERP() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "float GetERP() const", AS_METHODPR(Constraint, GetERP, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "float get_erp() const", AS_METHODPR(Constraint, GetERP, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "VariantMap& GetEventDataMap() const", AS_METHODPR(Constraint, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "Object@+ GetEventSender() const", AS_METHODPR(Constraint, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Constraint, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Constraint, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Constraint, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const VariantMap& get_globalVars() const", AS_METHODPR(Constraint, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const Vector2& Constraint::GetHighLimit() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "const Vector2& GetHighLimit() const", AS_METHODPR(Constraint, GetHighLimit, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Vector2& get_highLimit() const", AS_METHODPR(Constraint, GetHighLimit, () const, const Vector2&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "uint GetID() const", AS_METHODPR(Constraint, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "uint get_id() const", AS_METHODPR(Constraint, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Constraint, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const Vector2& Constraint::GetLowLimit() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "const Vector2& GetLowLimit() const", AS_METHODPR(Constraint, GetLowLimit, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Vector2& get_lowLimit() const", AS_METHODPR(Constraint, GetLowLimit, () const, const Vector2&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "Node@+ GetNode() const", AS_METHODPR(Constraint, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "Node@+ get_node() const", AS_METHODPR(Constraint, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "uint GetNumAttributes() const", AS_METHODPR(Constraint, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "uint get_numAttributes() const", AS_METHODPR(Constraint, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "uint GetNumNetworkAttributes() const", AS_METHODPR(Constraint, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Constraint, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Constraint, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Constraint, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // RigidBody* Constraint::GetOtherBody() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "RigidBody@+ GetOtherBody() const", AS_METHODPR(Constraint, GetOtherBody, () const, RigidBody*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "RigidBody@+ get_otherBody() const", AS_METHODPR(Constraint, GetOtherBody, () const, RigidBody*), AS_CALL_THISCALL);
    // const Vector3& Constraint::GetOtherPosition() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "const Vector3& GetOtherPosition() const", AS_METHODPR(Constraint, GetOtherPosition, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Vector3& get_otherPosition() const", AS_METHODPR(Constraint, GetOtherPosition, () const, const Vector3&), AS_CALL_THISCALL);
    // const Quaternion& Constraint::GetOtherRotation() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "const Quaternion& GetOtherRotation() const", AS_METHODPR(Constraint, GetOtherRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Quaternion& get_otherRotation() const", AS_METHODPR(Constraint, GetOtherRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    // RigidBody* Constraint::GetOwnBody() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "RigidBody@+ GetOwnBody() const", AS_METHODPR(Constraint, GetOwnBody, () const, RigidBody*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "RigidBody@+ get_ownBody() const", AS_METHODPR(Constraint, GetOwnBody, () const, RigidBody*), AS_CALL_THISCALL);
    // PhysicsWorld* Constraint::GetPhysicsWorld() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "PhysicsWorld@+ GetPhysicsWorld() const", AS_METHODPR(Constraint, GetPhysicsWorld, () const, PhysicsWorld*), AS_CALL_THISCALL);
    // const Vector3& Constraint::GetPosition() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "const Vector3& GetPosition() const", AS_METHODPR(Constraint, GetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Vector3& get_position() const", AS_METHODPR(Constraint, GetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    // const Quaternion& Constraint::GetRotation() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "const Quaternion& GetRotation() const", AS_METHODPR(Constraint, GetRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Quaternion& get_rotation() const", AS_METHODPR(Constraint, GetRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "Scene@+ GetScene() const", AS_METHODPR(Constraint, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Constraint, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "StringHash GetType() const", AS_METHODPR(Constraint, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "StringHash get_type() const", AS_METHODPR(Constraint, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "const String& GetTypeName() const", AS_METHODPR(Constraint, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const String& get_typeName() const", AS_METHODPR(Constraint, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // Vector3 Constraint::GetWorldPosition() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "Vector3 GetWorldPosition() const", AS_METHODPR(Constraint, GetWorldPosition, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "Vector3 get_worldPosition() const", AS_METHODPR(Constraint, GetWorldPosition, () const, Vector3), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "bool HasEventHandlers() const", AS_METHODPR(Constraint, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Constraint, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Constraint, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "bool IsEnabled() const", AS_METHODPR(Constraint, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool get_enabled() const", AS_METHODPR(Constraint, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "bool IsEnabledEffective() const", AS_METHODPR(Constraint, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool get_enabledEffective() const", AS_METHODPR(Constraint, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Constraint, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "bool IsReplicated() const", AS_METHODPR(Constraint, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool get_replicated() const", AS_METHODPR(Constraint, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool IsTemporary() const", AS_METHODPR(Constraint, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool get_temporary() const", AS_METHODPR(Constraint, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool Load(Deserializer&)", AS_METHODPR(Constraint, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Constraint, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Constraint, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "void MarkNetworkUpdate()", AS_METHODPR(Constraint, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Constraint, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Constraint, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Constraint, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Constraint::OnSetEnabled() override | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void OnSetEnabled()", AS_METHODPR(Constraint, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "void PrepareNetworkUpdate()", AS_METHODPR(Constraint, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Constraint, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Constraint, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Constraint", "int Refs() const", AS_METHODPR(Constraint, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "int get_refs() const", AS_METHODPR(Constraint, Refs, () const, int), AS_CALL_THISCALL);
    // static void Constraint::RegisterObject(Context* context) | File: ../Physics/Constraint.h
    // Not registered because have @nobind mark
    // void Constraint::ReleaseConstraint() | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void ReleaseConstraint()", AS_METHODPR(Constraint, ReleaseConstraint, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Constraint", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Constraint, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "void Remove()", AS_METHODPR(Constraint, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Constraint, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void RemoveInstanceDefault()", AS_METHODPR(Constraint, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void RemoveObjectAnimation()", AS_METHODPR(Constraint, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void ResetToDefault()", AS_METHODPR(Constraint, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "bool Save(Serializer&) const", AS_METHODPR(Constraint, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool SaveDefaultAttributes() const", AS_METHODPR(Constraint, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Constraint, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "bool SaveXML(XMLElement&) const", AS_METHODPR(Constraint, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void SendEvent(StringHash)", AS_METHODPR(Constraint, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Constraint, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetAnimationEnabled(bool)", AS_METHODPR(Constraint, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_animationEnabled(bool)", AS_METHODPR(Constraint, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetAnimationTime(float)", AS_METHODPR(Constraint, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Constraint, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Constraint, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Constraint, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Constraint, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Constraint, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Constraint, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Constraint, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Constraint::SetAxis(const Vector3& axis) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetAxis(const Vector3&in)", AS_METHODPR(Constraint, SetAxis, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_axis(const Vector3&in)", AS_METHODPR(Constraint, SetAxis, (const Vector3&), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void SetBlockEvents(bool)", AS_METHODPR(Constraint, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Constraint::SetCFM(float cfm) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetCFM(float)", AS_METHODPR(Constraint, SetCFM, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_cfm(float)", AS_METHODPR(Constraint, SetCFM, (float), void), AS_CALL_THISCALL);
    // void Constraint::SetConstraintType(ConstraintType type) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetConstraintType(ConstraintType)", AS_METHODPR(Constraint, SetConstraintType, (ConstraintType), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_constraintType(ConstraintType)", AS_METHODPR(Constraint, SetConstraintType, (ConstraintType), void), AS_CALL_THISCALL);
    // void Constraint::SetDisableCollision(bool disable) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetDisableCollision(bool)", AS_METHODPR(Constraint, SetDisableCollision, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_disableCollision(bool)", AS_METHODPR(Constraint, SetDisableCollision, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "void SetEnabled(bool)", AS_METHODPR(Constraint, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_enabled(bool)", AS_METHODPR(Constraint, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Constraint::SetERP(float erp) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetERP(float)", AS_METHODPR(Constraint, SetERP, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_erp(float)", AS_METHODPR(Constraint, SetERP, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Constraint, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Constraint, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Constraint::SetHighLimit(const Vector2& limit) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetHighLimit(const Vector2&in)", AS_METHODPR(Constraint, SetHighLimit, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_highLimit(const Vector2&in)", AS_METHODPR(Constraint, SetHighLimit, (const Vector2&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void SetInstanceDefault(bool)", AS_METHODPR(Constraint, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Constraint, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Constraint::SetLowLimit(const Vector2& limit) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetLowLimit(const Vector2&in)", AS_METHODPR(Constraint, SetLowLimit, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_lowLimit(const Vector2&in)", AS_METHODPR(Constraint, SetLowLimit, (const Vector2&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Constraint, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Constraint, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Constraint, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Constraint::SetOtherAxis(const Vector3& axis) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetOtherAxis(const Vector3&in)", AS_METHODPR(Constraint, SetOtherAxis, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_otherAxis(const Vector3&in)", AS_METHODPR(Constraint, SetOtherAxis, (const Vector3&), void), AS_CALL_THISCALL);
    // void Constraint::SetOtherBody(RigidBody* body) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetOtherBody(RigidBody@+)", AS_METHODPR(Constraint, SetOtherBody, (RigidBody*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_otherBody(RigidBody@+)", AS_METHODPR(Constraint, SetOtherBody, (RigidBody*), void), AS_CALL_THISCALL);
    // void Constraint::SetOtherPosition(const Vector3& position) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetOtherPosition(const Vector3&in)", AS_METHODPR(Constraint, SetOtherPosition, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_otherPosition(const Vector3&in)", AS_METHODPR(Constraint, SetOtherPosition, (const Vector3&), void), AS_CALL_THISCALL);
    // void Constraint::SetOtherRotation(const Quaternion& rotation) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetOtherRotation(const Quaternion&in)", AS_METHODPR(Constraint, SetOtherRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_otherRotation(const Quaternion&in)", AS_METHODPR(Constraint, SetOtherRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    // void Constraint::SetPosition(const Vector3& position) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetPosition(const Vector3&in)", AS_METHODPR(Constraint, SetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_position(const Vector3&in)", AS_METHODPR(Constraint, SetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    // void Constraint::SetRotation(const Quaternion& rotation) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetRotation(const Quaternion&in)", AS_METHODPR(Constraint, SetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_rotation(const Quaternion&in)", AS_METHODPR(Constraint, SetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void SetTemporary(bool)", AS_METHODPR(Constraint, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_temporary(bool)", AS_METHODPR(Constraint, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Constraint::SetWorldPosition(const Vector3& position) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetWorldPosition(const Vector3&in)", AS_METHODPR(Constraint, SetWorldPosition, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_worldPosition(const Vector3&in)", AS_METHODPR(Constraint, SetWorldPosition, (const Vector3&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void UnsubscribeFromAllEvents()", AS_METHODPR(Constraint, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Constraint_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Constraint, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Constraint, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Constraint, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Constraint", "int WeakRefs() const", AS_METHODPR(Constraint, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "int get_weakRefs() const", AS_METHODPR(Constraint, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Constraint, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Constraint, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Constraint, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Constraint, "Constraint")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Constraint, "Constraint")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Constraint, "Constraint")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Constraint, "Constraint")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Constraint, "Constraint")
#endif
#ifdef REGISTER_MANUAL_PART_Constraint
    REGISTER_MANUAL_PART_Constraint(Constraint, "Constraint")
#endif
    RegisterSubclass<Component, Constraint>(engine, "Component", "Constraint");
    RegisterSubclass<Animatable, Constraint>(engine, "Animatable", "Constraint");
    RegisterSubclass<Serializable, Constraint>(engine, "Serializable", "Constraint");
    RegisterSubclass<Object, Constraint>(engine, "Object", "Constraint");
    RegisterSubclass<RefCounted, Constraint>(engine, "RefCounted", "Constraint");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Constraint2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Constraint2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void AllocateNetworkState()", AS_METHODPR(Constraint2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "void ApplyAttributes()", AS_METHODPR(Constraint2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit Constraint2D::Constraint2D(Context* context) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectBehaviour("Constraint2D", asBEHAVE_FACTORY, "Constraint2D@+ f()", AS_FUNCTION(Constraint2D_Constraint2D_Context), AS_CALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "void CreateJoint()", AS_METHODPR(Constraint2D, CreateJoint, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Constraint2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "bool GetAnimationEnabled() const", AS_METHODPR(Constraint2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "bool get_animationEnabled() const", AS_METHODPR(Constraint2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "Constraint2D@+ GetAttachedConstraint() const", AS_METHODPR(Constraint2D, GetAttachedConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "Variant GetAttribute(uint) const", AS_METHODPR(Constraint2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "Variant get_attributes(uint) const", AS_METHODPR(Constraint2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(Constraint2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Constraint2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Constraint2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Constraint2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Constraint2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Constraint2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Constraint2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Constraint2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "bool GetBlockEvents() const", AS_METHODPR(Constraint2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "const String& GetCategory() const", AS_METHODPR(Constraint2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "const String& get_category() const", AS_METHODPR(Constraint2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "bool GetCollideConnected() const", AS_METHODPR(Constraint2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "bool get_collideConnected() const", AS_METHODPR(Constraint2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Constraint2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Constraint2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(Constraint2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "Object@+ GetEventSender() const", AS_METHODPR(Constraint2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Constraint2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Constraint2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Constraint2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "const VariantMap& get_globalVars() const", AS_METHODPR(Constraint2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "uint GetID() const", AS_METHODPR(Constraint2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "uint get_id() const", AS_METHODPR(Constraint2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Constraint2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "Node@+ GetNode() const", AS_METHODPR(Constraint2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "Node@+ get_node() const", AS_METHODPR(Constraint2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "uint GetNumAttributes() const", AS_METHODPR(Constraint2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "uint get_numAttributes() const", AS_METHODPR(Constraint2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(Constraint2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Constraint2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Constraint2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Constraint2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "RigidBody2D@+ GetOtherBody() const", AS_METHODPR(Constraint2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "RigidBody2D@+ get_otherBody() const", AS_METHODPR(Constraint2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "RigidBody2D@+ GetOwnerBody() const", AS_METHODPR(Constraint2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "RigidBody2D@+ get_ownerBody() const", AS_METHODPR(Constraint2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "Scene@+ GetScene() const", AS_METHODPR(Constraint2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Constraint2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "StringHash GetType() const", AS_METHODPR(Constraint2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "StringHash get_type() const", AS_METHODPR(Constraint2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "const String& GetTypeName() const", AS_METHODPR(Constraint2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "const String& get_typeName() const", AS_METHODPR(Constraint2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "bool HasEventHandlers() const", AS_METHODPR(Constraint2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Constraint2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Constraint2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "bool IsEnabled() const", AS_METHODPR(Constraint2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "bool get_enabled() const", AS_METHODPR(Constraint2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "bool IsEnabledEffective() const", AS_METHODPR(Constraint2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "bool get_enabledEffective() const", AS_METHODPR(Constraint2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Constraint2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "bool IsReplicated() const", AS_METHODPR(Constraint2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "bool get_replicated() const", AS_METHODPR(Constraint2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool IsTemporary() const", AS_METHODPR(Constraint2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "bool get_temporary() const", AS_METHODPR(Constraint2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool Load(Deserializer&)", AS_METHODPR(Constraint2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Constraint2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Constraint2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "void MarkNetworkUpdate()", AS_METHODPR(Constraint2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Constraint2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Constraint2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Constraint2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "void OnSetEnabled()", AS_METHODPR(Constraint2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "void PrepareNetworkUpdate()", AS_METHODPR(Constraint2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Constraint2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Constraint2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Constraint2D", "int Refs() const", AS_METHODPR(Constraint2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "int get_refs() const", AS_METHODPR(Constraint2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void Constraint2D::RegisterObject(Context* context) | File: ../Urho2D/Constraint2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "void ReleaseJoint()", AS_METHODPR(Constraint2D, ReleaseJoint, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Constraint2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Constraint2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "void Remove()", AS_METHODPR(Constraint2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Constraint2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void RemoveInstanceDefault()", AS_METHODPR(Constraint2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void RemoveObjectAnimation()", AS_METHODPR(Constraint2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void ResetToDefault()", AS_METHODPR(Constraint2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "bool Save(Serializer&) const", AS_METHODPR(Constraint2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool SaveDefaultAttributes() const", AS_METHODPR(Constraint2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Constraint2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(Constraint2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void SendEvent(StringHash)", AS_METHODPR(Constraint2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Constraint2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetAnimationEnabled(bool)", AS_METHODPR(Constraint2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "void set_animationEnabled(bool)", AS_METHODPR(Constraint2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetAnimationTime(float)", AS_METHODPR(Constraint2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "void SetAttachedConstraint(Constraint2D@+)", AS_METHODPR(Constraint2D, SetAttachedConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Constraint2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Constraint2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Constraint2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Constraint2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Constraint2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Constraint2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Constraint2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void SetBlockEvents(bool)", AS_METHODPR(Constraint2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "void SetCollideConnected(bool)", AS_METHODPR(Constraint2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "void set_collideConnected(bool)", AS_METHODPR(Constraint2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "void SetEnabled(bool)", AS_METHODPR(Constraint2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "void set_enabled(bool)", AS_METHODPR(Constraint2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Constraint2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Constraint2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetInstanceDefault(bool)", AS_METHODPR(Constraint2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Constraint2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Constraint2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Constraint2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Constraint2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "void SetOtherBody(RigidBody2D@+)", AS_METHODPR(Constraint2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "void set_otherBody(RigidBody2D@+)", AS_METHODPR(Constraint2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetTemporary(bool)", AS_METHODPR(Constraint2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "void set_temporary(bool)", AS_METHODPR(Constraint2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(Constraint2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Constraint2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Constraint2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Constraint2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Constraint2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Constraint2D", "int WeakRefs() const", AS_METHODPR(Constraint2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "int get_weakRefs() const", AS_METHODPR(Constraint2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Constraint2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Constraint2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Constraint2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Constraint2D, "Constraint2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Constraint2D, "Constraint2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Constraint2D, "Constraint2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Constraint2D, "Constraint2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Constraint2D, "Constraint2D")
#endif
#ifdef REGISTER_MANUAL_PART_Constraint2D
    REGISTER_MANUAL_PART_Constraint2D(Constraint2D, "Constraint2D")
#endif
    RegisterSubclass<Component, Constraint2D>(engine, "Component", "Constraint2D");
    RegisterSubclass<Animatable, Constraint2D>(engine, "Animatable", "Constraint2D");
    RegisterSubclass<Serializable, Constraint2D>(engine, "Serializable", "Constraint2D");
    RegisterSubclass<Object, Constraint2D>(engine, "Object", "Constraint2D");
    RegisterSubclass<RefCounted, Constraint2D>(engine, "RefCounted", "Constraint2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintDistance2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ConstraintDistance2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void AllocateNetworkState()", AS_METHODPR(ConstraintDistance2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void ApplyAttributes()", AS_METHODPR(ConstraintDistance2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintDistance2D::ConstraintDistance2D(Context* context) | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectBehaviour("ConstraintDistance2D", asBEHAVE_FACTORY, "ConstraintDistance2D@+ f()", AS_FUNCTION(ConstraintDistance2D_ConstraintDistance2D_Context), AS_CALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void CreateJoint()", AS_METHODPR(ConstraintDistance2D, CreateJoint, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(ConstraintDistance2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool GetAnimationEnabled() const", AS_METHODPR(ConstraintDistance2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool get_animationEnabled() const", AS_METHODPR(ConstraintDistance2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Constraint2D@+ GetAttachedConstraint() const", AS_METHODPR(ConstraintDistance2D, GetAttachedConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Variant GetAttribute(uint) const", AS_METHODPR(ConstraintDistance2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "Variant get_attributes(uint) const", AS_METHODPR(ConstraintDistance2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(ConstraintDistance2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ConstraintDistance2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ConstraintDistance2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ConstraintDistance2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ConstraintDistance2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ConstraintDistance2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ConstraintDistance2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ConstraintDistance2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool GetBlockEvents() const", AS_METHODPR(ConstraintDistance2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "const String& GetCategory() const", AS_METHODPR(ConstraintDistance2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const String& get_category() const", AS_METHODPR(ConstraintDistance2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool GetCollideConnected() const", AS_METHODPR(ConstraintDistance2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool get_collideConnected() const", AS_METHODPR(ConstraintDistance2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(ConstraintDistance2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ConstraintDistance2D::GetDampingRatio() const | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "float GetDampingRatio() const", AS_METHODPR(ConstraintDistance2D, GetDampingRatio, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "float get_dampingRatio() const", AS_METHODPR(ConstraintDistance2D, GetDampingRatio, () const, float), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(ConstraintDistance2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Object@+ GetEventSender() const", AS_METHODPR(ConstraintDistance2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // float ConstraintDistance2D::GetFrequencyHz() const | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "float GetFrequencyHz() const", AS_METHODPR(ConstraintDistance2D, GetFrequencyHz, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "float get_frequencyHz() const", AS_METHODPR(ConstraintDistance2D, GetFrequencyHz, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ConstraintDistance2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ConstraintDistance2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ConstraintDistance2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const VariantMap& get_globalVars() const", AS_METHODPR(ConstraintDistance2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "uint GetID() const", AS_METHODPR(ConstraintDistance2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "uint get_id() const", AS_METHODPR(ConstraintDistance2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ConstraintDistance2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // float ConstraintDistance2D::GetLength() const | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "float GetLength() const", AS_METHODPR(ConstraintDistance2D, GetLength, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "float get_length() const", AS_METHODPR(ConstraintDistance2D, GetLength, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Node@+ GetNode() const", AS_METHODPR(ConstraintDistance2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "Node@+ get_node() const", AS_METHODPR(ConstraintDistance2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "uint GetNumAttributes() const", AS_METHODPR(ConstraintDistance2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "uint get_numAttributes() const", AS_METHODPR(ConstraintDistance2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(ConstraintDistance2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ConstraintDistance2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ConstraintDistance2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ConstraintDistance2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "RigidBody2D@+ GetOtherBody() const", AS_METHODPR(ConstraintDistance2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "RigidBody2D@+ get_otherBody() const", AS_METHODPR(ConstraintDistance2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // const Vector2& ConstraintDistance2D::GetOtherBodyAnchor() const | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Vector2& GetOtherBodyAnchor() const", AS_METHODPR(ConstraintDistance2D, GetOtherBodyAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Vector2& get_otherBodyAnchor() const", AS_METHODPR(ConstraintDistance2D, GetOtherBodyAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "RigidBody2D@+ GetOwnerBody() const", AS_METHODPR(ConstraintDistance2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "RigidBody2D@+ get_ownerBody() const", AS_METHODPR(ConstraintDistance2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // const Vector2& ConstraintDistance2D::GetOwnerBodyAnchor() const | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Vector2& GetOwnerBodyAnchor() const", AS_METHODPR(ConstraintDistance2D, GetOwnerBodyAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Vector2& get_ownerBodyAnchor() const", AS_METHODPR(ConstraintDistance2D, GetOwnerBodyAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Scene@+ GetScene() const", AS_METHODPR(ConstraintDistance2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ConstraintDistance2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "StringHash GetType() const", AS_METHODPR(ConstraintDistance2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "StringHash get_type() const", AS_METHODPR(ConstraintDistance2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "const String& GetTypeName() const", AS_METHODPR(ConstraintDistance2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const String& get_typeName() const", AS_METHODPR(ConstraintDistance2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool HasEventHandlers() const", AS_METHODPR(ConstraintDistance2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ConstraintDistance2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ConstraintDistance2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool IsEnabled() const", AS_METHODPR(ConstraintDistance2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool get_enabled() const", AS_METHODPR(ConstraintDistance2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool IsEnabledEffective() const", AS_METHODPR(ConstraintDistance2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool get_enabledEffective() const", AS_METHODPR(ConstraintDistance2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ConstraintDistance2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool IsReplicated() const", AS_METHODPR(ConstraintDistance2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool get_replicated() const", AS_METHODPR(ConstraintDistance2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool IsTemporary() const", AS_METHODPR(ConstraintDistance2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool get_temporary() const", AS_METHODPR(ConstraintDistance2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool Load(Deserializer&)", AS_METHODPR(ConstraintDistance2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ConstraintDistance2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ConstraintDistance2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void MarkNetworkUpdate()", AS_METHODPR(ConstraintDistance2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ConstraintDistance2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ConstraintDistance2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ConstraintDistance2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void OnSetEnabled()", AS_METHODPR(ConstraintDistance2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void PrepareNetworkUpdate()", AS_METHODPR(ConstraintDistance2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ConstraintDistance2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ConstraintDistance2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "int Refs() const", AS_METHODPR(ConstraintDistance2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "int get_refs() const", AS_METHODPR(ConstraintDistance2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void ConstraintDistance2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintDistance2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void ReleaseJoint()", AS_METHODPR(ConstraintDistance2D, ReleaseJoint, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintDistance2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ConstraintDistance2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void Remove()", AS_METHODPR(ConstraintDistance2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ConstraintDistance2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void RemoveInstanceDefault()", AS_METHODPR(ConstraintDistance2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void RemoveObjectAnimation()", AS_METHODPR(ConstraintDistance2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void ResetToDefault()", AS_METHODPR(ConstraintDistance2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool Save(Serializer&) const", AS_METHODPR(ConstraintDistance2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool SaveDefaultAttributes() const", AS_METHODPR(ConstraintDistance2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ConstraintDistance2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(ConstraintDistance2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SendEvent(StringHash)", AS_METHODPR(ConstraintDistance2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ConstraintDistance2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetAnimationEnabled(bool)", AS_METHODPR(ConstraintDistance2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_animationEnabled(bool)", AS_METHODPR(ConstraintDistance2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetAnimationTime(float)", AS_METHODPR(ConstraintDistance2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetAttachedConstraint(Constraint2D@+)", AS_METHODPR(ConstraintDistance2D, SetAttachedConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ConstraintDistance2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ConstraintDistance2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ConstraintDistance2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ConstraintDistance2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ConstraintDistance2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ConstraintDistance2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ConstraintDistance2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetBlockEvents(bool)", AS_METHODPR(ConstraintDistance2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetCollideConnected(bool)", AS_METHODPR(ConstraintDistance2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_collideConnected(bool)", AS_METHODPR(ConstraintDistance2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    // void ConstraintDistance2D::SetDampingRatio(float dampingRatio) | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetDampingRatio(float)", AS_METHODPR(ConstraintDistance2D, SetDampingRatio, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_dampingRatio(float)", AS_METHODPR(ConstraintDistance2D, SetDampingRatio, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetEnabled(bool)", AS_METHODPR(ConstraintDistance2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_enabled(bool)", AS_METHODPR(ConstraintDistance2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void ConstraintDistance2D::SetFrequencyHz(float frequencyHz) | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetFrequencyHz(float)", AS_METHODPR(ConstraintDistance2D, SetFrequencyHz, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_frequencyHz(float)", AS_METHODPR(ConstraintDistance2D, SetFrequencyHz, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintDistance2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintDistance2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetInstanceDefault(bool)", AS_METHODPR(ConstraintDistance2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ConstraintDistance2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void ConstraintDistance2D::SetLength(float length) | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetLength(float)", AS_METHODPR(ConstraintDistance2D, SetLength, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_length(float)", AS_METHODPR(ConstraintDistance2D, SetLength, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintDistance2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintDistance2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ConstraintDistance2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetOtherBody(RigidBody2D@+)", AS_METHODPR(ConstraintDistance2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_otherBody(RigidBody2D@+)", AS_METHODPR(ConstraintDistance2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    // void ConstraintDistance2D::SetOtherBodyAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetOtherBodyAnchor(const Vector2&in)", AS_METHODPR(ConstraintDistance2D, SetOtherBodyAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_otherBodyAnchor(const Vector2&in)", AS_METHODPR(ConstraintDistance2D, SetOtherBodyAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void ConstraintDistance2D::SetOwnerBodyAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetOwnerBodyAnchor(const Vector2&in)", AS_METHODPR(ConstraintDistance2D, SetOwnerBodyAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_ownerBodyAnchor(const Vector2&in)", AS_METHODPR(ConstraintDistance2D, SetOwnerBodyAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetTemporary(bool)", AS_METHODPR(ConstraintDistance2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_temporary(bool)", AS_METHODPR(ConstraintDistance2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(ConstraintDistance2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ConstraintDistance2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ConstraintDistance2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ConstraintDistance2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ConstraintDistance2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "int WeakRefs() const", AS_METHODPR(ConstraintDistance2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "int get_weakRefs() const", AS_METHODPR(ConstraintDistance2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ConstraintDistance2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintDistance2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintDistance2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Constraint2D
    REGISTER_MANUAL_PART_Constraint2D(ConstraintDistance2D, "ConstraintDistance2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(ConstraintDistance2D, "ConstraintDistance2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ConstraintDistance2D, "ConstraintDistance2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ConstraintDistance2D, "ConstraintDistance2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ConstraintDistance2D, "ConstraintDistance2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ConstraintDistance2D, "ConstraintDistance2D")
#endif
#ifdef REGISTER_MANUAL_PART_ConstraintDistance2D
    REGISTER_MANUAL_PART_ConstraintDistance2D(ConstraintDistance2D, "ConstraintDistance2D")
#endif
    RegisterSubclass<Constraint2D, ConstraintDistance2D>(engine, "Constraint2D", "ConstraintDistance2D");
    RegisterSubclass<Component, ConstraintDistance2D>(engine, "Component", "ConstraintDistance2D");
    RegisterSubclass<Animatable, ConstraintDistance2D>(engine, "Animatable", "ConstraintDistance2D");
    RegisterSubclass<Serializable, ConstraintDistance2D>(engine, "Serializable", "ConstraintDistance2D");
    RegisterSubclass<Object, ConstraintDistance2D>(engine, "Object", "ConstraintDistance2D");
    RegisterSubclass<RefCounted, ConstraintDistance2D>(engine, "RefCounted", "ConstraintDistance2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintFriction2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ConstraintFriction2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void AllocateNetworkState()", AS_METHODPR(ConstraintFriction2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void ApplyAttributes()", AS_METHODPR(ConstraintFriction2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintFriction2D::ConstraintFriction2D(Context* context) | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectBehaviour("ConstraintFriction2D", asBEHAVE_FACTORY, "ConstraintFriction2D@+ f()", AS_FUNCTION(ConstraintFriction2D_ConstraintFriction2D_Context), AS_CALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void CreateJoint()", AS_METHODPR(ConstraintFriction2D, CreateJoint, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(ConstraintFriction2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // const Vector2& ConstraintFriction2D::GetAnchor() const | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "const Vector2& GetAnchor() const", AS_METHODPR(ConstraintFriction2D, GetAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "const Vector2& get_anchor() const", AS_METHODPR(ConstraintFriction2D, GetAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool GetAnimationEnabled() const", AS_METHODPR(ConstraintFriction2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool get_animationEnabled() const", AS_METHODPR(ConstraintFriction2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Constraint2D@+ GetAttachedConstraint() const", AS_METHODPR(ConstraintFriction2D, GetAttachedConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Variant GetAttribute(uint) const", AS_METHODPR(ConstraintFriction2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "Variant get_attributes(uint) const", AS_METHODPR(ConstraintFriction2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(ConstraintFriction2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ConstraintFriction2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ConstraintFriction2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ConstraintFriction2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ConstraintFriction2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ConstraintFriction2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ConstraintFriction2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ConstraintFriction2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool GetBlockEvents() const", AS_METHODPR(ConstraintFriction2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "const String& GetCategory() const", AS_METHODPR(ConstraintFriction2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "const String& get_category() const", AS_METHODPR(ConstraintFriction2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool GetCollideConnected() const", AS_METHODPR(ConstraintFriction2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool get_collideConnected() const", AS_METHODPR(ConstraintFriction2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(ConstraintFriction2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("ConstraintFriction2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(ConstraintFriction2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Object@+ GetEventSender() const", AS_METHODPR(ConstraintFriction2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ConstraintFriction2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ConstraintFriction2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ConstraintFriction2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "const VariantMap& get_globalVars() const", AS_METHODPR(ConstraintFriction2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "uint GetID() const", AS_METHODPR(ConstraintFriction2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "uint get_id() const", AS_METHODPR(ConstraintFriction2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ConstraintFriction2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // float ConstraintFriction2D::GetMaxForce() const | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "float GetMaxForce() const", AS_METHODPR(ConstraintFriction2D, GetMaxForce, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "float get_maxForce() const", AS_METHODPR(ConstraintFriction2D, GetMaxForce, () const, float), AS_CALL_THISCALL);
    // float ConstraintFriction2D::GetMaxTorque() const | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "float GetMaxTorque() const", AS_METHODPR(ConstraintFriction2D, GetMaxTorque, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "float get_maxTorque() const", AS_METHODPR(ConstraintFriction2D, GetMaxTorque, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Node@+ GetNode() const", AS_METHODPR(ConstraintFriction2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "Node@+ get_node() const", AS_METHODPR(ConstraintFriction2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "uint GetNumAttributes() const", AS_METHODPR(ConstraintFriction2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "uint get_numAttributes() const", AS_METHODPR(ConstraintFriction2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(ConstraintFriction2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ConstraintFriction2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ConstraintFriction2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ConstraintFriction2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "RigidBody2D@+ GetOtherBody() const", AS_METHODPR(ConstraintFriction2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "RigidBody2D@+ get_otherBody() const", AS_METHODPR(ConstraintFriction2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "RigidBody2D@+ GetOwnerBody() const", AS_METHODPR(ConstraintFriction2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "RigidBody2D@+ get_ownerBody() const", AS_METHODPR(ConstraintFriction2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Scene@+ GetScene() const", AS_METHODPR(ConstraintFriction2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ConstraintFriction2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "StringHash GetType() const", AS_METHODPR(ConstraintFriction2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "StringHash get_type() const", AS_METHODPR(ConstraintFriction2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "const String& GetTypeName() const", AS_METHODPR(ConstraintFriction2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "const String& get_typeName() const", AS_METHODPR(ConstraintFriction2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool HasEventHandlers() const", AS_METHODPR(ConstraintFriction2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ConstraintFriction2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ConstraintFriction2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool IsEnabled() const", AS_METHODPR(ConstraintFriction2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool get_enabled() const", AS_METHODPR(ConstraintFriction2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool IsEnabledEffective() const", AS_METHODPR(ConstraintFriction2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool get_enabledEffective() const", AS_METHODPR(ConstraintFriction2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ConstraintFriction2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool IsReplicated() const", AS_METHODPR(ConstraintFriction2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool get_replicated() const", AS_METHODPR(ConstraintFriction2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool IsTemporary() const", AS_METHODPR(ConstraintFriction2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool get_temporary() const", AS_METHODPR(ConstraintFriction2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool Load(Deserializer&)", AS_METHODPR(ConstraintFriction2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ConstraintFriction2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ConstraintFriction2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void MarkNetworkUpdate()", AS_METHODPR(ConstraintFriction2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ConstraintFriction2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ConstraintFriction2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ConstraintFriction2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void OnSetEnabled()", AS_METHODPR(ConstraintFriction2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void PrepareNetworkUpdate()", AS_METHODPR(ConstraintFriction2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ConstraintFriction2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ConstraintFriction2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "int Refs() const", AS_METHODPR(ConstraintFriction2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "int get_refs() const", AS_METHODPR(ConstraintFriction2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void ConstraintFriction2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintFriction2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void ReleaseJoint()", AS_METHODPR(ConstraintFriction2D, ReleaseJoint, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintFriction2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ConstraintFriction2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void Remove()", AS_METHODPR(ConstraintFriction2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ConstraintFriction2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void RemoveInstanceDefault()", AS_METHODPR(ConstraintFriction2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void RemoveObjectAnimation()", AS_METHODPR(ConstraintFriction2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void ResetToDefault()", AS_METHODPR(ConstraintFriction2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool Save(Serializer&) const", AS_METHODPR(ConstraintFriction2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool SaveDefaultAttributes() const", AS_METHODPR(ConstraintFriction2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ConstraintFriction2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(ConstraintFriction2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SendEvent(StringHash)", AS_METHODPR(ConstraintFriction2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ConstraintFriction2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ConstraintFriction2D::SetAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAnchor(const Vector2&in)", AS_METHODPR(ConstraintFriction2D, SetAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_anchor(const Vector2&in)", AS_METHODPR(ConstraintFriction2D, SetAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAnimationEnabled(bool)", AS_METHODPR(ConstraintFriction2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_animationEnabled(bool)", AS_METHODPR(ConstraintFriction2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAnimationTime(float)", AS_METHODPR(ConstraintFriction2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAttachedConstraint(Constraint2D@+)", AS_METHODPR(ConstraintFriction2D, SetAttachedConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ConstraintFriction2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ConstraintFriction2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ConstraintFriction2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ConstraintFriction2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ConstraintFriction2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ConstraintFriction2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ConstraintFriction2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetBlockEvents(bool)", AS_METHODPR(ConstraintFriction2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetCollideConnected(bool)", AS_METHODPR(ConstraintFriction2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_collideConnected(bool)", AS_METHODPR(ConstraintFriction2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetEnabled(bool)", AS_METHODPR(ConstraintFriction2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_enabled(bool)", AS_METHODPR(ConstraintFriction2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintFriction2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintFriction2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetInstanceDefault(bool)", AS_METHODPR(ConstraintFriction2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ConstraintFriction2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void ConstraintFriction2D::SetMaxForce(float maxForce) | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetMaxForce(float)", AS_METHODPR(ConstraintFriction2D, SetMaxForce, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_maxForce(float)", AS_METHODPR(ConstraintFriction2D, SetMaxForce, (float), void), AS_CALL_THISCALL);
    // void ConstraintFriction2D::SetMaxTorque(float maxTorque) | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetMaxTorque(float)", AS_METHODPR(ConstraintFriction2D, SetMaxTorque, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_maxTorque(float)", AS_METHODPR(ConstraintFriction2D, SetMaxTorque, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintFriction2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintFriction2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ConstraintFriction2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetOtherBody(RigidBody2D@+)", AS_METHODPR(ConstraintFriction2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_otherBody(RigidBody2D@+)", AS_METHODPR(ConstraintFriction2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetTemporary(bool)", AS_METHODPR(ConstraintFriction2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_temporary(bool)", AS_METHODPR(ConstraintFriction2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(ConstraintFriction2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ConstraintFriction2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ConstraintFriction2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ConstraintFriction2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ConstraintFriction2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "int WeakRefs() const", AS_METHODPR(ConstraintFriction2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "int get_weakRefs() const", AS_METHODPR(ConstraintFriction2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ConstraintFriction2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintFriction2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintFriction2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Constraint2D
    REGISTER_MANUAL_PART_Constraint2D(ConstraintFriction2D, "ConstraintFriction2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(ConstraintFriction2D, "ConstraintFriction2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ConstraintFriction2D, "ConstraintFriction2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ConstraintFriction2D, "ConstraintFriction2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ConstraintFriction2D, "ConstraintFriction2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ConstraintFriction2D, "ConstraintFriction2D")
#endif
#ifdef REGISTER_MANUAL_PART_ConstraintFriction2D
    REGISTER_MANUAL_PART_ConstraintFriction2D(ConstraintFriction2D, "ConstraintFriction2D")
#endif
    RegisterSubclass<Constraint2D, ConstraintFriction2D>(engine, "Constraint2D", "ConstraintFriction2D");
    RegisterSubclass<Component, ConstraintFriction2D>(engine, "Component", "ConstraintFriction2D");
    RegisterSubclass<Animatable, ConstraintFriction2D>(engine, "Animatable", "ConstraintFriction2D");
    RegisterSubclass<Serializable, ConstraintFriction2D>(engine, "Serializable", "ConstraintFriction2D");
    RegisterSubclass<Object, ConstraintFriction2D>(engine, "Object", "ConstraintFriction2D");
    RegisterSubclass<RefCounted, ConstraintFriction2D>(engine, "RefCounted", "ConstraintFriction2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintGear2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ConstraintGear2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void AllocateNetworkState()", AS_METHODPR(ConstraintGear2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void ApplyAttributes()", AS_METHODPR(ConstraintGear2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintGear2D::ConstraintGear2D(Context* context) | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectBehaviour("ConstraintGear2D", asBEHAVE_FACTORY, "ConstraintGear2D@+ f()", AS_FUNCTION(ConstraintGear2D_ConstraintGear2D_Context), AS_CALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void CreateJoint()", AS_METHODPR(ConstraintGear2D, CreateJoint, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(ConstraintGear2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool GetAnimationEnabled() const", AS_METHODPR(ConstraintGear2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "bool get_animationEnabled() const", AS_METHODPR(ConstraintGear2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Constraint2D@+ GetAttachedConstraint() const", AS_METHODPR(ConstraintGear2D, GetAttachedConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Variant GetAttribute(uint) const", AS_METHODPR(ConstraintGear2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "Variant get_attributes(uint) const", AS_METHODPR(ConstraintGear2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(ConstraintGear2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ConstraintGear2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ConstraintGear2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ConstraintGear2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ConstraintGear2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ConstraintGear2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ConstraintGear2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ConstraintGear2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool GetBlockEvents() const", AS_METHODPR(ConstraintGear2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "const String& GetCategory() const", AS_METHODPR(ConstraintGear2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "const String& get_category() const", AS_METHODPR(ConstraintGear2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool GetCollideConnected() const", AS_METHODPR(ConstraintGear2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "bool get_collideConnected() const", AS_METHODPR(ConstraintGear2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(ConstraintGear2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("ConstraintGear2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(ConstraintGear2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Object@+ GetEventSender() const", AS_METHODPR(ConstraintGear2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ConstraintGear2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ConstraintGear2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ConstraintGear2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "const VariantMap& get_globalVars() const", AS_METHODPR(ConstraintGear2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "uint GetID() const", AS_METHODPR(ConstraintGear2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "uint get_id() const", AS_METHODPR(ConstraintGear2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ConstraintGear2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Node@+ GetNode() const", AS_METHODPR(ConstraintGear2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "Node@+ get_node() const", AS_METHODPR(ConstraintGear2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "uint GetNumAttributes() const", AS_METHODPR(ConstraintGear2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "uint get_numAttributes() const", AS_METHODPR(ConstraintGear2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(ConstraintGear2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ConstraintGear2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ConstraintGear2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ConstraintGear2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "RigidBody2D@+ GetOtherBody() const", AS_METHODPR(ConstraintGear2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "RigidBody2D@+ get_otherBody() const", AS_METHODPR(ConstraintGear2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // Constraint2D* ConstraintGear2D::GetOtherConstraint() const | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Constraint2D@+ GetOtherConstraint() const", AS_METHODPR(ConstraintGear2D, GetOtherConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "Constraint2D@+ get_otherConstraint() const", AS_METHODPR(ConstraintGear2D, GetOtherConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "RigidBody2D@+ GetOwnerBody() const", AS_METHODPR(ConstraintGear2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "RigidBody2D@+ get_ownerBody() const", AS_METHODPR(ConstraintGear2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // Constraint2D* ConstraintGear2D::GetOwnerConstraint() const | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Constraint2D@+ GetOwnerConstraint() const", AS_METHODPR(ConstraintGear2D, GetOwnerConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "Constraint2D@+ get_ownerConstraint() const", AS_METHODPR(ConstraintGear2D, GetOwnerConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    // float ConstraintGear2D::GetRatio() const | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "float GetRatio() const", AS_METHODPR(ConstraintGear2D, GetRatio, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "float get_ratio() const", AS_METHODPR(ConstraintGear2D, GetRatio, () const, float), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Scene@+ GetScene() const", AS_METHODPR(ConstraintGear2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ConstraintGear2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "StringHash GetType() const", AS_METHODPR(ConstraintGear2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "StringHash get_type() const", AS_METHODPR(ConstraintGear2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "const String& GetTypeName() const", AS_METHODPR(ConstraintGear2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "const String& get_typeName() const", AS_METHODPR(ConstraintGear2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool HasEventHandlers() const", AS_METHODPR(ConstraintGear2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ConstraintGear2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ConstraintGear2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool IsEnabled() const", AS_METHODPR(ConstraintGear2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "bool get_enabled() const", AS_METHODPR(ConstraintGear2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool IsEnabledEffective() const", AS_METHODPR(ConstraintGear2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "bool get_enabledEffective() const", AS_METHODPR(ConstraintGear2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ConstraintGear2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool IsReplicated() const", AS_METHODPR(ConstraintGear2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "bool get_replicated() const", AS_METHODPR(ConstraintGear2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool IsTemporary() const", AS_METHODPR(ConstraintGear2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "bool get_temporary() const", AS_METHODPR(ConstraintGear2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool Load(Deserializer&)", AS_METHODPR(ConstraintGear2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ConstraintGear2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ConstraintGear2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void MarkNetworkUpdate()", AS_METHODPR(ConstraintGear2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ConstraintGear2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ConstraintGear2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ConstraintGear2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void OnSetEnabled()", AS_METHODPR(ConstraintGear2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void PrepareNetworkUpdate()", AS_METHODPR(ConstraintGear2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ConstraintGear2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ConstraintGear2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintGear2D", "int Refs() const", AS_METHODPR(ConstraintGear2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "int get_refs() const", AS_METHODPR(ConstraintGear2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void ConstraintGear2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintGear2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void ReleaseJoint()", AS_METHODPR(ConstraintGear2D, ReleaseJoint, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintGear2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ConstraintGear2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void Remove()", AS_METHODPR(ConstraintGear2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ConstraintGear2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void RemoveInstanceDefault()", AS_METHODPR(ConstraintGear2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void RemoveObjectAnimation()", AS_METHODPR(ConstraintGear2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void ResetToDefault()", AS_METHODPR(ConstraintGear2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool Save(Serializer&) const", AS_METHODPR(ConstraintGear2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool SaveDefaultAttributes() const", AS_METHODPR(ConstraintGear2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ConstraintGear2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(ConstraintGear2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SendEvent(StringHash)", AS_METHODPR(ConstraintGear2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ConstraintGear2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetAnimationEnabled(bool)", AS_METHODPR(ConstraintGear2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_animationEnabled(bool)", AS_METHODPR(ConstraintGear2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetAnimationTime(float)", AS_METHODPR(ConstraintGear2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetAttachedConstraint(Constraint2D@+)", AS_METHODPR(ConstraintGear2D, SetAttachedConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ConstraintGear2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ConstraintGear2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ConstraintGear2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ConstraintGear2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ConstraintGear2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ConstraintGear2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ConstraintGear2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetBlockEvents(bool)", AS_METHODPR(ConstraintGear2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetCollideConnected(bool)", AS_METHODPR(ConstraintGear2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_collideConnected(bool)", AS_METHODPR(ConstraintGear2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetEnabled(bool)", AS_METHODPR(ConstraintGear2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_enabled(bool)", AS_METHODPR(ConstraintGear2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintGear2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintGear2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetInstanceDefault(bool)", AS_METHODPR(ConstraintGear2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ConstraintGear2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintGear2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintGear2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ConstraintGear2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetOtherBody(RigidBody2D@+)", AS_METHODPR(ConstraintGear2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_otherBody(RigidBody2D@+)", AS_METHODPR(ConstraintGear2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    // void ConstraintGear2D::SetOtherConstraint(Constraint2D* constraint) | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetOtherConstraint(Constraint2D@+)", AS_METHODPR(ConstraintGear2D, SetOtherConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_otherConstraint(Constraint2D@+)", AS_METHODPR(ConstraintGear2D, SetOtherConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    // void ConstraintGear2D::SetOwnerConstraint(Constraint2D* constraint) | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetOwnerConstraint(Constraint2D@+)", AS_METHODPR(ConstraintGear2D, SetOwnerConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_ownerConstraint(Constraint2D@+)", AS_METHODPR(ConstraintGear2D, SetOwnerConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    // void ConstraintGear2D::SetRatio(float ratio) | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetRatio(float)", AS_METHODPR(ConstraintGear2D, SetRatio, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_ratio(float)", AS_METHODPR(ConstraintGear2D, SetRatio, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetTemporary(bool)", AS_METHODPR(ConstraintGear2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_temporary(bool)", AS_METHODPR(ConstraintGear2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(ConstraintGear2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ConstraintGear2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ConstraintGear2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ConstraintGear2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ConstraintGear2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintGear2D", "int WeakRefs() const", AS_METHODPR(ConstraintGear2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "int get_weakRefs() const", AS_METHODPR(ConstraintGear2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ConstraintGear2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintGear2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintGear2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Constraint2D
    REGISTER_MANUAL_PART_Constraint2D(ConstraintGear2D, "ConstraintGear2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(ConstraintGear2D, "ConstraintGear2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ConstraintGear2D, "ConstraintGear2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ConstraintGear2D, "ConstraintGear2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ConstraintGear2D, "ConstraintGear2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ConstraintGear2D, "ConstraintGear2D")
#endif
#ifdef REGISTER_MANUAL_PART_ConstraintGear2D
    REGISTER_MANUAL_PART_ConstraintGear2D(ConstraintGear2D, "ConstraintGear2D")
#endif
    RegisterSubclass<Constraint2D, ConstraintGear2D>(engine, "Constraint2D", "ConstraintGear2D");
    RegisterSubclass<Component, ConstraintGear2D>(engine, "Component", "ConstraintGear2D");
    RegisterSubclass<Animatable, ConstraintGear2D>(engine, "Animatable", "ConstraintGear2D");
    RegisterSubclass<Serializable, ConstraintGear2D>(engine, "Serializable", "ConstraintGear2D");
    RegisterSubclass<Object, ConstraintGear2D>(engine, "Object", "ConstraintGear2D");
    RegisterSubclass<RefCounted, ConstraintGear2D>(engine, "RefCounted", "ConstraintGear2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintMotor2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ConstraintMotor2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void AllocateNetworkState()", AS_METHODPR(ConstraintMotor2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void ApplyAttributes()", AS_METHODPR(ConstraintMotor2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintMotor2D::ConstraintMotor2D(Context* context) | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectBehaviour("ConstraintMotor2D", asBEHAVE_FACTORY, "ConstraintMotor2D@+ f()", AS_FUNCTION(ConstraintMotor2D_ConstraintMotor2D_Context), AS_CALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void CreateJoint()", AS_METHODPR(ConstraintMotor2D, CreateJoint, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(ConstraintMotor2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // float ConstraintMotor2D::GetAngularOffset() const | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "float GetAngularOffset() const", AS_METHODPR(ConstraintMotor2D, GetAngularOffset, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "float get_angularOffset() const", AS_METHODPR(ConstraintMotor2D, GetAngularOffset, () const, float), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool GetAnimationEnabled() const", AS_METHODPR(ConstraintMotor2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool get_animationEnabled() const", AS_METHODPR(ConstraintMotor2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Constraint2D@+ GetAttachedConstraint() const", AS_METHODPR(ConstraintMotor2D, GetAttachedConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Variant GetAttribute(uint) const", AS_METHODPR(ConstraintMotor2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "Variant get_attributes(uint) const", AS_METHODPR(ConstraintMotor2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(ConstraintMotor2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ConstraintMotor2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ConstraintMotor2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ConstraintMotor2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ConstraintMotor2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ConstraintMotor2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ConstraintMotor2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ConstraintMotor2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool GetBlockEvents() const", AS_METHODPR(ConstraintMotor2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "const String& GetCategory() const", AS_METHODPR(ConstraintMotor2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "const String& get_category() const", AS_METHODPR(ConstraintMotor2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool GetCollideConnected() const", AS_METHODPR(ConstraintMotor2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool get_collideConnected() const", AS_METHODPR(ConstraintMotor2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(ConstraintMotor2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ConstraintMotor2D::GetCorrectionFactor() const | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "float GetCorrectionFactor() const", AS_METHODPR(ConstraintMotor2D, GetCorrectionFactor, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "float get_correctionFactor() const", AS_METHODPR(ConstraintMotor2D, GetCorrectionFactor, () const, float), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(ConstraintMotor2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Object@+ GetEventSender() const", AS_METHODPR(ConstraintMotor2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ConstraintMotor2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ConstraintMotor2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ConstraintMotor2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "const VariantMap& get_globalVars() const", AS_METHODPR(ConstraintMotor2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "uint GetID() const", AS_METHODPR(ConstraintMotor2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "uint get_id() const", AS_METHODPR(ConstraintMotor2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ConstraintMotor2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // const Vector2& ConstraintMotor2D::GetLinearOffset() const | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "const Vector2& GetLinearOffset() const", AS_METHODPR(ConstraintMotor2D, GetLinearOffset, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "const Vector2& get_linearOffset() const", AS_METHODPR(ConstraintMotor2D, GetLinearOffset, () const, const Vector2&), AS_CALL_THISCALL);
    // float ConstraintMotor2D::GetMaxForce() const | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "float GetMaxForce() const", AS_METHODPR(ConstraintMotor2D, GetMaxForce, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "float get_maxForce() const", AS_METHODPR(ConstraintMotor2D, GetMaxForce, () const, float), AS_CALL_THISCALL);
    // float ConstraintMotor2D::GetMaxTorque() const | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "float GetMaxTorque() const", AS_METHODPR(ConstraintMotor2D, GetMaxTorque, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "float get_maxTorque() const", AS_METHODPR(ConstraintMotor2D, GetMaxTorque, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Node@+ GetNode() const", AS_METHODPR(ConstraintMotor2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "Node@+ get_node() const", AS_METHODPR(ConstraintMotor2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "uint GetNumAttributes() const", AS_METHODPR(ConstraintMotor2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "uint get_numAttributes() const", AS_METHODPR(ConstraintMotor2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(ConstraintMotor2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ConstraintMotor2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ConstraintMotor2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ConstraintMotor2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "RigidBody2D@+ GetOtherBody() const", AS_METHODPR(ConstraintMotor2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "RigidBody2D@+ get_otherBody() const", AS_METHODPR(ConstraintMotor2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "RigidBody2D@+ GetOwnerBody() const", AS_METHODPR(ConstraintMotor2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "RigidBody2D@+ get_ownerBody() const", AS_METHODPR(ConstraintMotor2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Scene@+ GetScene() const", AS_METHODPR(ConstraintMotor2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ConstraintMotor2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "StringHash GetType() const", AS_METHODPR(ConstraintMotor2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "StringHash get_type() const", AS_METHODPR(ConstraintMotor2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "const String& GetTypeName() const", AS_METHODPR(ConstraintMotor2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "const String& get_typeName() const", AS_METHODPR(ConstraintMotor2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool HasEventHandlers() const", AS_METHODPR(ConstraintMotor2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ConstraintMotor2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ConstraintMotor2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool IsEnabled() const", AS_METHODPR(ConstraintMotor2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool get_enabled() const", AS_METHODPR(ConstraintMotor2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool IsEnabledEffective() const", AS_METHODPR(ConstraintMotor2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool get_enabledEffective() const", AS_METHODPR(ConstraintMotor2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ConstraintMotor2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool IsReplicated() const", AS_METHODPR(ConstraintMotor2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool get_replicated() const", AS_METHODPR(ConstraintMotor2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool IsTemporary() const", AS_METHODPR(ConstraintMotor2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool get_temporary() const", AS_METHODPR(ConstraintMotor2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool Load(Deserializer&)", AS_METHODPR(ConstraintMotor2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ConstraintMotor2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ConstraintMotor2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void MarkNetworkUpdate()", AS_METHODPR(ConstraintMotor2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ConstraintMotor2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ConstraintMotor2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ConstraintMotor2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void OnSetEnabled()", AS_METHODPR(ConstraintMotor2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void PrepareNetworkUpdate()", AS_METHODPR(ConstraintMotor2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ConstraintMotor2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ConstraintMotor2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "int Refs() const", AS_METHODPR(ConstraintMotor2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "int get_refs() const", AS_METHODPR(ConstraintMotor2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void ConstraintMotor2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintMotor2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void ReleaseJoint()", AS_METHODPR(ConstraintMotor2D, ReleaseJoint, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintMotor2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ConstraintMotor2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void Remove()", AS_METHODPR(ConstraintMotor2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ConstraintMotor2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void RemoveInstanceDefault()", AS_METHODPR(ConstraintMotor2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void RemoveObjectAnimation()", AS_METHODPR(ConstraintMotor2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void ResetToDefault()", AS_METHODPR(ConstraintMotor2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool Save(Serializer&) const", AS_METHODPR(ConstraintMotor2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool SaveDefaultAttributes() const", AS_METHODPR(ConstraintMotor2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ConstraintMotor2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(ConstraintMotor2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SendEvent(StringHash)", AS_METHODPR(ConstraintMotor2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ConstraintMotor2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ConstraintMotor2D::SetAngularOffset(float angularOffset) | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAngularOffset(float)", AS_METHODPR(ConstraintMotor2D, SetAngularOffset, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_angularOffset(float)", AS_METHODPR(ConstraintMotor2D, SetAngularOffset, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAnimationEnabled(bool)", AS_METHODPR(ConstraintMotor2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_animationEnabled(bool)", AS_METHODPR(ConstraintMotor2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAnimationTime(float)", AS_METHODPR(ConstraintMotor2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAttachedConstraint(Constraint2D@+)", AS_METHODPR(ConstraintMotor2D, SetAttachedConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ConstraintMotor2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ConstraintMotor2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ConstraintMotor2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ConstraintMotor2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ConstraintMotor2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ConstraintMotor2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ConstraintMotor2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetBlockEvents(bool)", AS_METHODPR(ConstraintMotor2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetCollideConnected(bool)", AS_METHODPR(ConstraintMotor2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_collideConnected(bool)", AS_METHODPR(ConstraintMotor2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    // void ConstraintMotor2D::SetCorrectionFactor(float correctionFactor) | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetCorrectionFactor(float)", AS_METHODPR(ConstraintMotor2D, SetCorrectionFactor, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_correctionFactor(float)", AS_METHODPR(ConstraintMotor2D, SetCorrectionFactor, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetEnabled(bool)", AS_METHODPR(ConstraintMotor2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_enabled(bool)", AS_METHODPR(ConstraintMotor2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintMotor2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintMotor2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetInstanceDefault(bool)", AS_METHODPR(ConstraintMotor2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ConstraintMotor2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void ConstraintMotor2D::SetLinearOffset(const Vector2& linearOffset) | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetLinearOffset(const Vector2&in)", AS_METHODPR(ConstraintMotor2D, SetLinearOffset, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_linearOffset(const Vector2&in)", AS_METHODPR(ConstraintMotor2D, SetLinearOffset, (const Vector2&), void), AS_CALL_THISCALL);
    // void ConstraintMotor2D::SetMaxForce(float maxForce) | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetMaxForce(float)", AS_METHODPR(ConstraintMotor2D, SetMaxForce, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_maxForce(float)", AS_METHODPR(ConstraintMotor2D, SetMaxForce, (float), void), AS_CALL_THISCALL);
    // void ConstraintMotor2D::SetMaxTorque(float maxTorque) | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetMaxTorque(float)", AS_METHODPR(ConstraintMotor2D, SetMaxTorque, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_maxTorque(float)", AS_METHODPR(ConstraintMotor2D, SetMaxTorque, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintMotor2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintMotor2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ConstraintMotor2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetOtherBody(RigidBody2D@+)", AS_METHODPR(ConstraintMotor2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_otherBody(RigidBody2D@+)", AS_METHODPR(ConstraintMotor2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetTemporary(bool)", AS_METHODPR(ConstraintMotor2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_temporary(bool)", AS_METHODPR(ConstraintMotor2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(ConstraintMotor2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ConstraintMotor2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ConstraintMotor2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ConstraintMotor2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ConstraintMotor2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "int WeakRefs() const", AS_METHODPR(ConstraintMotor2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "int get_weakRefs() const", AS_METHODPR(ConstraintMotor2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ConstraintMotor2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintMotor2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintMotor2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Constraint2D
    REGISTER_MANUAL_PART_Constraint2D(ConstraintMotor2D, "ConstraintMotor2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(ConstraintMotor2D, "ConstraintMotor2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ConstraintMotor2D, "ConstraintMotor2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ConstraintMotor2D, "ConstraintMotor2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ConstraintMotor2D, "ConstraintMotor2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ConstraintMotor2D, "ConstraintMotor2D")
#endif
#ifdef REGISTER_MANUAL_PART_ConstraintMotor2D
    REGISTER_MANUAL_PART_ConstraintMotor2D(ConstraintMotor2D, "ConstraintMotor2D")
#endif
    RegisterSubclass<Constraint2D, ConstraintMotor2D>(engine, "Constraint2D", "ConstraintMotor2D");
    RegisterSubclass<Component, ConstraintMotor2D>(engine, "Component", "ConstraintMotor2D");
    RegisterSubclass<Animatable, ConstraintMotor2D>(engine, "Animatable", "ConstraintMotor2D");
    RegisterSubclass<Serializable, ConstraintMotor2D>(engine, "Serializable", "ConstraintMotor2D");
    RegisterSubclass<Object, ConstraintMotor2D>(engine, "Object", "ConstraintMotor2D");
    RegisterSubclass<RefCounted, ConstraintMotor2D>(engine, "RefCounted", "ConstraintMotor2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintMouse2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ConstraintMouse2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void AllocateNetworkState()", AS_METHODPR(ConstraintMouse2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void ApplyAttributes()", AS_METHODPR(ConstraintMouse2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintMouse2D::ConstraintMouse2D(Context* context) | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectBehaviour("ConstraintMouse2D", asBEHAVE_FACTORY, "ConstraintMouse2D@+ f()", AS_FUNCTION(ConstraintMouse2D_ConstraintMouse2D_Context), AS_CALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void CreateJoint()", AS_METHODPR(ConstraintMouse2D, CreateJoint, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(ConstraintMouse2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool GetAnimationEnabled() const", AS_METHODPR(ConstraintMouse2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool get_animationEnabled() const", AS_METHODPR(ConstraintMouse2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Constraint2D@+ GetAttachedConstraint() const", AS_METHODPR(ConstraintMouse2D, GetAttachedConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Variant GetAttribute(uint) const", AS_METHODPR(ConstraintMouse2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "Variant get_attributes(uint) const", AS_METHODPR(ConstraintMouse2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(ConstraintMouse2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ConstraintMouse2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ConstraintMouse2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ConstraintMouse2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ConstraintMouse2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ConstraintMouse2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ConstraintMouse2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ConstraintMouse2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool GetBlockEvents() const", AS_METHODPR(ConstraintMouse2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "const String& GetCategory() const", AS_METHODPR(ConstraintMouse2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "const String& get_category() const", AS_METHODPR(ConstraintMouse2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool GetCollideConnected() const", AS_METHODPR(ConstraintMouse2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool get_collideConnected() const", AS_METHODPR(ConstraintMouse2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(ConstraintMouse2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ConstraintMouse2D::GetDampingRatio() const | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "float GetDampingRatio() const", AS_METHODPR(ConstraintMouse2D, GetDampingRatio, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "float get_dampingRatio() const", AS_METHODPR(ConstraintMouse2D, GetDampingRatio, () const, float), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(ConstraintMouse2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Object@+ GetEventSender() const", AS_METHODPR(ConstraintMouse2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // float ConstraintMouse2D::GetFrequencyHz() const | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "float GetFrequencyHz() const", AS_METHODPR(ConstraintMouse2D, GetFrequencyHz, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "float get_frequencyHz() const", AS_METHODPR(ConstraintMouse2D, GetFrequencyHz, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ConstraintMouse2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ConstraintMouse2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ConstraintMouse2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "const VariantMap& get_globalVars() const", AS_METHODPR(ConstraintMouse2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "uint GetID() const", AS_METHODPR(ConstraintMouse2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "uint get_id() const", AS_METHODPR(ConstraintMouse2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ConstraintMouse2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // float ConstraintMouse2D::GetMaxForce() const | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "float GetMaxForce() const", AS_METHODPR(ConstraintMouse2D, GetMaxForce, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "float get_maxForce() const", AS_METHODPR(ConstraintMouse2D, GetMaxForce, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Node@+ GetNode() const", AS_METHODPR(ConstraintMouse2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "Node@+ get_node() const", AS_METHODPR(ConstraintMouse2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "uint GetNumAttributes() const", AS_METHODPR(ConstraintMouse2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "uint get_numAttributes() const", AS_METHODPR(ConstraintMouse2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(ConstraintMouse2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ConstraintMouse2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ConstraintMouse2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ConstraintMouse2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "RigidBody2D@+ GetOtherBody() const", AS_METHODPR(ConstraintMouse2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "RigidBody2D@+ get_otherBody() const", AS_METHODPR(ConstraintMouse2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "RigidBody2D@+ GetOwnerBody() const", AS_METHODPR(ConstraintMouse2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "RigidBody2D@+ get_ownerBody() const", AS_METHODPR(ConstraintMouse2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Scene@+ GetScene() const", AS_METHODPR(ConstraintMouse2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ConstraintMouse2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const Vector2& ConstraintMouse2D::GetTarget() const | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "const Vector2& GetTarget() const", AS_METHODPR(ConstraintMouse2D, GetTarget, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "const Vector2& get_target() const", AS_METHODPR(ConstraintMouse2D, GetTarget, () const, const Vector2&), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "StringHash GetType() const", AS_METHODPR(ConstraintMouse2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "StringHash get_type() const", AS_METHODPR(ConstraintMouse2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "const String& GetTypeName() const", AS_METHODPR(ConstraintMouse2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "const String& get_typeName() const", AS_METHODPR(ConstraintMouse2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool HasEventHandlers() const", AS_METHODPR(ConstraintMouse2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ConstraintMouse2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ConstraintMouse2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool IsEnabled() const", AS_METHODPR(ConstraintMouse2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool get_enabled() const", AS_METHODPR(ConstraintMouse2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool IsEnabledEffective() const", AS_METHODPR(ConstraintMouse2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool get_enabledEffective() const", AS_METHODPR(ConstraintMouse2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ConstraintMouse2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool IsReplicated() const", AS_METHODPR(ConstraintMouse2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool get_replicated() const", AS_METHODPR(ConstraintMouse2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool IsTemporary() const", AS_METHODPR(ConstraintMouse2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool get_temporary() const", AS_METHODPR(ConstraintMouse2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool Load(Deserializer&)", AS_METHODPR(ConstraintMouse2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ConstraintMouse2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ConstraintMouse2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void MarkNetworkUpdate()", AS_METHODPR(ConstraintMouse2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ConstraintMouse2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ConstraintMouse2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ConstraintMouse2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void OnSetEnabled()", AS_METHODPR(ConstraintMouse2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void PrepareNetworkUpdate()", AS_METHODPR(ConstraintMouse2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ConstraintMouse2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ConstraintMouse2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "int Refs() const", AS_METHODPR(ConstraintMouse2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "int get_refs() const", AS_METHODPR(ConstraintMouse2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void ConstraintMouse2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintMouse2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void ReleaseJoint()", AS_METHODPR(ConstraintMouse2D, ReleaseJoint, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintMouse2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ConstraintMouse2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void Remove()", AS_METHODPR(ConstraintMouse2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ConstraintMouse2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void RemoveInstanceDefault()", AS_METHODPR(ConstraintMouse2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void RemoveObjectAnimation()", AS_METHODPR(ConstraintMouse2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void ResetToDefault()", AS_METHODPR(ConstraintMouse2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool Save(Serializer&) const", AS_METHODPR(ConstraintMouse2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool SaveDefaultAttributes() const", AS_METHODPR(ConstraintMouse2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ConstraintMouse2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(ConstraintMouse2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SendEvent(StringHash)", AS_METHODPR(ConstraintMouse2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ConstraintMouse2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetAnimationEnabled(bool)", AS_METHODPR(ConstraintMouse2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_animationEnabled(bool)", AS_METHODPR(ConstraintMouse2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetAnimationTime(float)", AS_METHODPR(ConstraintMouse2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetAttachedConstraint(Constraint2D@+)", AS_METHODPR(ConstraintMouse2D, SetAttachedConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ConstraintMouse2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ConstraintMouse2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ConstraintMouse2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ConstraintMouse2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ConstraintMouse2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ConstraintMouse2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ConstraintMouse2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetBlockEvents(bool)", AS_METHODPR(ConstraintMouse2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetCollideConnected(bool)", AS_METHODPR(ConstraintMouse2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_collideConnected(bool)", AS_METHODPR(ConstraintMouse2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    // void ConstraintMouse2D::SetDampingRatio(float dampingRatio) | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetDampingRatio(float)", AS_METHODPR(ConstraintMouse2D, SetDampingRatio, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_dampingRatio(float)", AS_METHODPR(ConstraintMouse2D, SetDampingRatio, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetEnabled(bool)", AS_METHODPR(ConstraintMouse2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_enabled(bool)", AS_METHODPR(ConstraintMouse2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void ConstraintMouse2D::SetFrequencyHz(float frequencyHz) | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetFrequencyHz(float)", AS_METHODPR(ConstraintMouse2D, SetFrequencyHz, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_frequencyHz(float)", AS_METHODPR(ConstraintMouse2D, SetFrequencyHz, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintMouse2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintMouse2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetInstanceDefault(bool)", AS_METHODPR(ConstraintMouse2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ConstraintMouse2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void ConstraintMouse2D::SetMaxForce(float maxForce) | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetMaxForce(float)", AS_METHODPR(ConstraintMouse2D, SetMaxForce, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_maxForce(float)", AS_METHODPR(ConstraintMouse2D, SetMaxForce, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintMouse2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintMouse2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ConstraintMouse2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetOtherBody(RigidBody2D@+)", AS_METHODPR(ConstraintMouse2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_otherBody(RigidBody2D@+)", AS_METHODPR(ConstraintMouse2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    // void ConstraintMouse2D::SetTarget(const Vector2& target) | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetTarget(const Vector2&in)", AS_METHODPR(ConstraintMouse2D, SetTarget, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_target(const Vector2&in)", AS_METHODPR(ConstraintMouse2D, SetTarget, (const Vector2&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetTemporary(bool)", AS_METHODPR(ConstraintMouse2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_temporary(bool)", AS_METHODPR(ConstraintMouse2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(ConstraintMouse2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ConstraintMouse2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ConstraintMouse2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ConstraintMouse2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ConstraintMouse2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "int WeakRefs() const", AS_METHODPR(ConstraintMouse2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "int get_weakRefs() const", AS_METHODPR(ConstraintMouse2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ConstraintMouse2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintMouse2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintMouse2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Constraint2D
    REGISTER_MANUAL_PART_Constraint2D(ConstraintMouse2D, "ConstraintMouse2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(ConstraintMouse2D, "ConstraintMouse2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ConstraintMouse2D, "ConstraintMouse2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ConstraintMouse2D, "ConstraintMouse2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ConstraintMouse2D, "ConstraintMouse2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ConstraintMouse2D, "ConstraintMouse2D")
#endif
#ifdef REGISTER_MANUAL_PART_ConstraintMouse2D
    REGISTER_MANUAL_PART_ConstraintMouse2D(ConstraintMouse2D, "ConstraintMouse2D")
#endif
    RegisterSubclass<Constraint2D, ConstraintMouse2D>(engine, "Constraint2D", "ConstraintMouse2D");
    RegisterSubclass<Component, ConstraintMouse2D>(engine, "Component", "ConstraintMouse2D");
    RegisterSubclass<Animatable, ConstraintMouse2D>(engine, "Animatable", "ConstraintMouse2D");
    RegisterSubclass<Serializable, ConstraintMouse2D>(engine, "Serializable", "ConstraintMouse2D");
    RegisterSubclass<Object, ConstraintMouse2D>(engine, "Object", "ConstraintMouse2D");
    RegisterSubclass<RefCounted, ConstraintMouse2D>(engine, "RefCounted", "ConstraintMouse2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintPrismatic2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ConstraintPrismatic2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void AllocateNetworkState()", AS_METHODPR(ConstraintPrismatic2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void ApplyAttributes()", AS_METHODPR(ConstraintPrismatic2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintPrismatic2D::ConstraintPrismatic2D(Context* context) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectBehaviour("ConstraintPrismatic2D", asBEHAVE_FACTORY, "ConstraintPrismatic2D@+ f()", AS_FUNCTION(ConstraintPrismatic2D_ConstraintPrismatic2D_Context), AS_CALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void CreateJoint()", AS_METHODPR(ConstraintPrismatic2D, CreateJoint, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(ConstraintPrismatic2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // const Vector2& ConstraintPrismatic2D::GetAnchor() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Vector2& GetAnchor() const", AS_METHODPR(ConstraintPrismatic2D, GetAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Vector2& get_anchor() const", AS_METHODPR(ConstraintPrismatic2D, GetAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool GetAnimationEnabled() const", AS_METHODPR(ConstraintPrismatic2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_animationEnabled() const", AS_METHODPR(ConstraintPrismatic2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Constraint2D@+ GetAttachedConstraint() const", AS_METHODPR(ConstraintPrismatic2D, GetAttachedConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Variant GetAttribute(uint) const", AS_METHODPR(ConstraintPrismatic2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Variant get_attributes(uint) const", AS_METHODPR(ConstraintPrismatic2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(ConstraintPrismatic2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ConstraintPrismatic2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ConstraintPrismatic2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ConstraintPrismatic2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ConstraintPrismatic2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ConstraintPrismatic2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ConstraintPrismatic2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ConstraintPrismatic2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector2& ConstraintPrismatic2D::GetAxis() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Vector2& GetAxis() const", AS_METHODPR(ConstraintPrismatic2D, GetAxis, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Vector2& get_axis() const", AS_METHODPR(ConstraintPrismatic2D, GetAxis, () const, const Vector2&), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool GetBlockEvents() const", AS_METHODPR(ConstraintPrismatic2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const String& GetCategory() const", AS_METHODPR(ConstraintPrismatic2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const String& get_category() const", AS_METHODPR(ConstraintPrismatic2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool GetCollideConnected() const", AS_METHODPR(ConstraintPrismatic2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_collideConnected() const", AS_METHODPR(ConstraintPrismatic2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(ConstraintPrismatic2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    // bool ConstraintPrismatic2D::GetEnableLimit() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool GetEnableLimit() const", AS_METHODPR(ConstraintPrismatic2D, GetEnableLimit, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_enableLimit() const", AS_METHODPR(ConstraintPrismatic2D, GetEnableLimit, () const, bool), AS_CALL_THISCALL);
    // bool ConstraintPrismatic2D::GetEnableMotor() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool GetEnableMotor() const", AS_METHODPR(ConstraintPrismatic2D, GetEnableMotor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_enableMotor() const", AS_METHODPR(ConstraintPrismatic2D, GetEnableMotor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(ConstraintPrismatic2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Object@+ GetEventSender() const", AS_METHODPR(ConstraintPrismatic2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ConstraintPrismatic2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ConstraintPrismatic2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ConstraintPrismatic2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const VariantMap& get_globalVars() const", AS_METHODPR(ConstraintPrismatic2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "uint GetID() const", AS_METHODPR(ConstraintPrismatic2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "uint get_id() const", AS_METHODPR(ConstraintPrismatic2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ConstraintPrismatic2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // float ConstraintPrismatic2D::GetLowerTranslation() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float GetLowerTranslation() const", AS_METHODPR(ConstraintPrismatic2D, GetLowerTranslation, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_lowerTranslation() const", AS_METHODPR(ConstraintPrismatic2D, GetLowerTranslation, () const, float), AS_CALL_THISCALL);
    // float ConstraintPrismatic2D::GetMaxMotorForce() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float GetMaxMotorForce() const", AS_METHODPR(ConstraintPrismatic2D, GetMaxMotorForce, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_maxMotorForce() const", AS_METHODPR(ConstraintPrismatic2D, GetMaxMotorForce, () const, float), AS_CALL_THISCALL);
    // float ConstraintPrismatic2D::GetMotorSpeed() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float GetMotorSpeed() const", AS_METHODPR(ConstraintPrismatic2D, GetMotorSpeed, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_motorSpeed() const", AS_METHODPR(ConstraintPrismatic2D, GetMotorSpeed, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Node@+ GetNode() const", AS_METHODPR(ConstraintPrismatic2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Node@+ get_node() const", AS_METHODPR(ConstraintPrismatic2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "uint GetNumAttributes() const", AS_METHODPR(ConstraintPrismatic2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "uint get_numAttributes() const", AS_METHODPR(ConstraintPrismatic2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(ConstraintPrismatic2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ConstraintPrismatic2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ConstraintPrismatic2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ConstraintPrismatic2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "RigidBody2D@+ GetOtherBody() const", AS_METHODPR(ConstraintPrismatic2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "RigidBody2D@+ get_otherBody() const", AS_METHODPR(ConstraintPrismatic2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "RigidBody2D@+ GetOwnerBody() const", AS_METHODPR(ConstraintPrismatic2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "RigidBody2D@+ get_ownerBody() const", AS_METHODPR(ConstraintPrismatic2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Scene@+ GetScene() const", AS_METHODPR(ConstraintPrismatic2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ConstraintPrismatic2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "StringHash GetType() const", AS_METHODPR(ConstraintPrismatic2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "StringHash get_type() const", AS_METHODPR(ConstraintPrismatic2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const String& GetTypeName() const", AS_METHODPR(ConstraintPrismatic2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const String& get_typeName() const", AS_METHODPR(ConstraintPrismatic2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // float ConstraintPrismatic2D::GetUpperTranslation() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float GetUpperTranslation() const", AS_METHODPR(ConstraintPrismatic2D, GetUpperTranslation, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_upperTranslation() const", AS_METHODPR(ConstraintPrismatic2D, GetUpperTranslation, () const, float), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool HasEventHandlers() const", AS_METHODPR(ConstraintPrismatic2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ConstraintPrismatic2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ConstraintPrismatic2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool IsEnabled() const", AS_METHODPR(ConstraintPrismatic2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_enabled() const", AS_METHODPR(ConstraintPrismatic2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool IsEnabledEffective() const", AS_METHODPR(ConstraintPrismatic2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_enabledEffective() const", AS_METHODPR(ConstraintPrismatic2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ConstraintPrismatic2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool IsReplicated() const", AS_METHODPR(ConstraintPrismatic2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_replicated() const", AS_METHODPR(ConstraintPrismatic2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool IsTemporary() const", AS_METHODPR(ConstraintPrismatic2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_temporary() const", AS_METHODPR(ConstraintPrismatic2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool Load(Deserializer&)", AS_METHODPR(ConstraintPrismatic2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ConstraintPrismatic2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ConstraintPrismatic2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void MarkNetworkUpdate()", AS_METHODPR(ConstraintPrismatic2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ConstraintPrismatic2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ConstraintPrismatic2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ConstraintPrismatic2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void OnSetEnabled()", AS_METHODPR(ConstraintPrismatic2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void PrepareNetworkUpdate()", AS_METHODPR(ConstraintPrismatic2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ConstraintPrismatic2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ConstraintPrismatic2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "int Refs() const", AS_METHODPR(ConstraintPrismatic2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "int get_refs() const", AS_METHODPR(ConstraintPrismatic2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void ConstraintPrismatic2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintPrismatic2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void ReleaseJoint()", AS_METHODPR(ConstraintPrismatic2D, ReleaseJoint, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintPrismatic2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ConstraintPrismatic2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void Remove()", AS_METHODPR(ConstraintPrismatic2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ConstraintPrismatic2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void RemoveInstanceDefault()", AS_METHODPR(ConstraintPrismatic2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void RemoveObjectAnimation()", AS_METHODPR(ConstraintPrismatic2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void ResetToDefault()", AS_METHODPR(ConstraintPrismatic2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool Save(Serializer&) const", AS_METHODPR(ConstraintPrismatic2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool SaveDefaultAttributes() const", AS_METHODPR(ConstraintPrismatic2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ConstraintPrismatic2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(ConstraintPrismatic2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SendEvent(StringHash)", AS_METHODPR(ConstraintPrismatic2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ConstraintPrismatic2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ConstraintPrismatic2D::SetAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAnchor(const Vector2&in)", AS_METHODPR(ConstraintPrismatic2D, SetAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_anchor(const Vector2&in)", AS_METHODPR(ConstraintPrismatic2D, SetAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAnimationEnabled(bool)", AS_METHODPR(ConstraintPrismatic2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_animationEnabled(bool)", AS_METHODPR(ConstraintPrismatic2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAnimationTime(float)", AS_METHODPR(ConstraintPrismatic2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAttachedConstraint(Constraint2D@+)", AS_METHODPR(ConstraintPrismatic2D, SetAttachedConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ConstraintPrismatic2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ConstraintPrismatic2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ConstraintPrismatic2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ConstraintPrismatic2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ConstraintPrismatic2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ConstraintPrismatic2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ConstraintPrismatic2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void ConstraintPrismatic2D::SetAxis(const Vector2& axis) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAxis(const Vector2&in)", AS_METHODPR(ConstraintPrismatic2D, SetAxis, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_axis(const Vector2&in)", AS_METHODPR(ConstraintPrismatic2D, SetAxis, (const Vector2&), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetBlockEvents(bool)", AS_METHODPR(ConstraintPrismatic2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetCollideConnected(bool)", AS_METHODPR(ConstraintPrismatic2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_collideConnected(bool)", AS_METHODPR(ConstraintPrismatic2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetEnabled(bool)", AS_METHODPR(ConstraintPrismatic2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_enabled(bool)", AS_METHODPR(ConstraintPrismatic2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void ConstraintPrismatic2D::SetEnableLimit(bool enableLimit) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetEnableLimit(bool)", AS_METHODPR(ConstraintPrismatic2D, SetEnableLimit, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_enableLimit(bool)", AS_METHODPR(ConstraintPrismatic2D, SetEnableLimit, (bool), void), AS_CALL_THISCALL);
    // void ConstraintPrismatic2D::SetEnableMotor(bool enableMotor) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetEnableMotor(bool)", AS_METHODPR(ConstraintPrismatic2D, SetEnableMotor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_enableMotor(bool)", AS_METHODPR(ConstraintPrismatic2D, SetEnableMotor, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintPrismatic2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintPrismatic2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetInstanceDefault(bool)", AS_METHODPR(ConstraintPrismatic2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ConstraintPrismatic2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void ConstraintPrismatic2D::SetLowerTranslation(float lowerTranslation) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetLowerTranslation(float)", AS_METHODPR(ConstraintPrismatic2D, SetLowerTranslation, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_lowerTranslation(float)", AS_METHODPR(ConstraintPrismatic2D, SetLowerTranslation, (float), void), AS_CALL_THISCALL);
    // void ConstraintPrismatic2D::SetMaxMotorForce(float maxMotorForce) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetMaxMotorForce(float)", AS_METHODPR(ConstraintPrismatic2D, SetMaxMotorForce, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_maxMotorForce(float)", AS_METHODPR(ConstraintPrismatic2D, SetMaxMotorForce, (float), void), AS_CALL_THISCALL);
    // void ConstraintPrismatic2D::SetMotorSpeed(float motorSpeed) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetMotorSpeed(float)", AS_METHODPR(ConstraintPrismatic2D, SetMotorSpeed, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_motorSpeed(float)", AS_METHODPR(ConstraintPrismatic2D, SetMotorSpeed, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintPrismatic2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintPrismatic2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ConstraintPrismatic2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetOtherBody(RigidBody2D@+)", AS_METHODPR(ConstraintPrismatic2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_otherBody(RigidBody2D@+)", AS_METHODPR(ConstraintPrismatic2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetTemporary(bool)", AS_METHODPR(ConstraintPrismatic2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_temporary(bool)", AS_METHODPR(ConstraintPrismatic2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void ConstraintPrismatic2D::SetUpperTranslation(float upperTranslation) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetUpperTranslation(float)", AS_METHODPR(ConstraintPrismatic2D, SetUpperTranslation, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_upperTranslation(float)", AS_METHODPR(ConstraintPrismatic2D, SetUpperTranslation, (float), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(ConstraintPrismatic2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ConstraintPrismatic2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ConstraintPrismatic2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ConstraintPrismatic2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ConstraintPrismatic2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "int WeakRefs() const", AS_METHODPR(ConstraintPrismatic2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "int get_weakRefs() const", AS_METHODPR(ConstraintPrismatic2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ConstraintPrismatic2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintPrismatic2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintPrismatic2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Constraint2D
    REGISTER_MANUAL_PART_Constraint2D(ConstraintPrismatic2D, "ConstraintPrismatic2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(ConstraintPrismatic2D, "ConstraintPrismatic2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ConstraintPrismatic2D, "ConstraintPrismatic2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ConstraintPrismatic2D, "ConstraintPrismatic2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ConstraintPrismatic2D, "ConstraintPrismatic2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ConstraintPrismatic2D, "ConstraintPrismatic2D")
#endif
#ifdef REGISTER_MANUAL_PART_ConstraintPrismatic2D
    REGISTER_MANUAL_PART_ConstraintPrismatic2D(ConstraintPrismatic2D, "ConstraintPrismatic2D")
#endif
    RegisterSubclass<Constraint2D, ConstraintPrismatic2D>(engine, "Constraint2D", "ConstraintPrismatic2D");
    RegisterSubclass<Component, ConstraintPrismatic2D>(engine, "Component", "ConstraintPrismatic2D");
    RegisterSubclass<Animatable, ConstraintPrismatic2D>(engine, "Animatable", "ConstraintPrismatic2D");
    RegisterSubclass<Serializable, ConstraintPrismatic2D>(engine, "Serializable", "ConstraintPrismatic2D");
    RegisterSubclass<Object, ConstraintPrismatic2D>(engine, "Object", "ConstraintPrismatic2D");
    RegisterSubclass<RefCounted, ConstraintPrismatic2D>(engine, "RefCounted", "ConstraintPrismatic2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintPulley2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ConstraintPulley2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void AllocateNetworkState()", AS_METHODPR(ConstraintPulley2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void ApplyAttributes()", AS_METHODPR(ConstraintPulley2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintPulley2D::ConstraintPulley2D(Context* context) | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectBehaviour("ConstraintPulley2D", asBEHAVE_FACTORY, "ConstraintPulley2D@+ f()", AS_FUNCTION(ConstraintPulley2D_ConstraintPulley2D_Context), AS_CALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void CreateJoint()", AS_METHODPR(ConstraintPulley2D, CreateJoint, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(ConstraintPulley2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool GetAnimationEnabled() const", AS_METHODPR(ConstraintPulley2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool get_animationEnabled() const", AS_METHODPR(ConstraintPulley2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Constraint2D@+ GetAttachedConstraint() const", AS_METHODPR(ConstraintPulley2D, GetAttachedConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Variant GetAttribute(uint) const", AS_METHODPR(ConstraintPulley2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "Variant get_attributes(uint) const", AS_METHODPR(ConstraintPulley2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(ConstraintPulley2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ConstraintPulley2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ConstraintPulley2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ConstraintPulley2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ConstraintPulley2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ConstraintPulley2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ConstraintPulley2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ConstraintPulley2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool GetBlockEvents() const", AS_METHODPR(ConstraintPulley2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const String& GetCategory() const", AS_METHODPR(ConstraintPulley2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const String& get_category() const", AS_METHODPR(ConstraintPulley2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool GetCollideConnected() const", AS_METHODPR(ConstraintPulley2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool get_collideConnected() const", AS_METHODPR(ConstraintPulley2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(ConstraintPulley2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("ConstraintPulley2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(ConstraintPulley2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Object@+ GetEventSender() const", AS_METHODPR(ConstraintPulley2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ConstraintPulley2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ConstraintPulley2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ConstraintPulley2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const VariantMap& get_globalVars() const", AS_METHODPR(ConstraintPulley2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "uint GetID() const", AS_METHODPR(ConstraintPulley2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "uint get_id() const", AS_METHODPR(ConstraintPulley2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ConstraintPulley2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Node@+ GetNode() const", AS_METHODPR(ConstraintPulley2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "Node@+ get_node() const", AS_METHODPR(ConstraintPulley2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "uint GetNumAttributes() const", AS_METHODPR(ConstraintPulley2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "uint get_numAttributes() const", AS_METHODPR(ConstraintPulley2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(ConstraintPulley2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ConstraintPulley2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ConstraintPulley2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ConstraintPulley2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "RigidBody2D@+ GetOtherBody() const", AS_METHODPR(ConstraintPulley2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "RigidBody2D@+ get_otherBody() const", AS_METHODPR(ConstraintPulley2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // const Vector2& ConstraintPulley2D::GetOtherBodyAnchor() const | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& GetOtherBodyAnchor() const", AS_METHODPR(ConstraintPulley2D, GetOtherBodyAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_otherBodyAnchor() const", AS_METHODPR(ConstraintPulley2D, GetOtherBodyAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // const Vector2& ConstraintPulley2D::GetOtherBodyGroundAnchor() const | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& GetOtherBodyGroundAnchor() const", AS_METHODPR(ConstraintPulley2D, GetOtherBodyGroundAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_otherBodyGroundAnchor() const", AS_METHODPR(ConstraintPulley2D, GetOtherBodyGroundAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "RigidBody2D@+ GetOwnerBody() const", AS_METHODPR(ConstraintPulley2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "RigidBody2D@+ get_ownerBody() const", AS_METHODPR(ConstraintPulley2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // const Vector2& ConstraintPulley2D::GetOwnerBodyAnchor() const | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& GetOwnerBodyAnchor() const", AS_METHODPR(ConstraintPulley2D, GetOwnerBodyAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_ownerBodyAnchor() const", AS_METHODPR(ConstraintPulley2D, GetOwnerBodyAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // const Vector2& ConstraintPulley2D::GetOwnerBodyGroundAnchor() const | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& GetOwnerBodyGroundAnchor() const", AS_METHODPR(ConstraintPulley2D, GetOwnerBodyGroundAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_ownerBodyGroundAnchor() const", AS_METHODPR(ConstraintPulley2D, GetOwnerBodyGroundAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // float ConstraintPulley2D::GetRatio() const | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "float GetRatio() const", AS_METHODPR(ConstraintPulley2D, GetRatio, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "float get_ratio() const", AS_METHODPR(ConstraintPulley2D, GetRatio, () const, float), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Scene@+ GetScene() const", AS_METHODPR(ConstraintPulley2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ConstraintPulley2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "StringHash GetType() const", AS_METHODPR(ConstraintPulley2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "StringHash get_type() const", AS_METHODPR(ConstraintPulley2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const String& GetTypeName() const", AS_METHODPR(ConstraintPulley2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const String& get_typeName() const", AS_METHODPR(ConstraintPulley2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool HasEventHandlers() const", AS_METHODPR(ConstraintPulley2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ConstraintPulley2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ConstraintPulley2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool IsEnabled() const", AS_METHODPR(ConstraintPulley2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool get_enabled() const", AS_METHODPR(ConstraintPulley2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool IsEnabledEffective() const", AS_METHODPR(ConstraintPulley2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool get_enabledEffective() const", AS_METHODPR(ConstraintPulley2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ConstraintPulley2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool IsReplicated() const", AS_METHODPR(ConstraintPulley2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool get_replicated() const", AS_METHODPR(ConstraintPulley2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool IsTemporary() const", AS_METHODPR(ConstraintPulley2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool get_temporary() const", AS_METHODPR(ConstraintPulley2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool Load(Deserializer&)", AS_METHODPR(ConstraintPulley2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ConstraintPulley2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ConstraintPulley2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void MarkNetworkUpdate()", AS_METHODPR(ConstraintPulley2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ConstraintPulley2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ConstraintPulley2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ConstraintPulley2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void OnSetEnabled()", AS_METHODPR(ConstraintPulley2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void PrepareNetworkUpdate()", AS_METHODPR(ConstraintPulley2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ConstraintPulley2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ConstraintPulley2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "int Refs() const", AS_METHODPR(ConstraintPulley2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "int get_refs() const", AS_METHODPR(ConstraintPulley2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void ConstraintPulley2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintPulley2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void ReleaseJoint()", AS_METHODPR(ConstraintPulley2D, ReleaseJoint, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintPulley2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ConstraintPulley2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void Remove()", AS_METHODPR(ConstraintPulley2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ConstraintPulley2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void RemoveInstanceDefault()", AS_METHODPR(ConstraintPulley2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void RemoveObjectAnimation()", AS_METHODPR(ConstraintPulley2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void ResetToDefault()", AS_METHODPR(ConstraintPulley2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool Save(Serializer&) const", AS_METHODPR(ConstraintPulley2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool SaveDefaultAttributes() const", AS_METHODPR(ConstraintPulley2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ConstraintPulley2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(ConstraintPulley2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SendEvent(StringHash)", AS_METHODPR(ConstraintPulley2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ConstraintPulley2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetAnimationEnabled(bool)", AS_METHODPR(ConstraintPulley2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_animationEnabled(bool)", AS_METHODPR(ConstraintPulley2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetAnimationTime(float)", AS_METHODPR(ConstraintPulley2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetAttachedConstraint(Constraint2D@+)", AS_METHODPR(ConstraintPulley2D, SetAttachedConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ConstraintPulley2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ConstraintPulley2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ConstraintPulley2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ConstraintPulley2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ConstraintPulley2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ConstraintPulley2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ConstraintPulley2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetBlockEvents(bool)", AS_METHODPR(ConstraintPulley2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetCollideConnected(bool)", AS_METHODPR(ConstraintPulley2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_collideConnected(bool)", AS_METHODPR(ConstraintPulley2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetEnabled(bool)", AS_METHODPR(ConstraintPulley2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_enabled(bool)", AS_METHODPR(ConstraintPulley2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintPulley2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintPulley2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetInstanceDefault(bool)", AS_METHODPR(ConstraintPulley2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ConstraintPulley2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintPulley2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintPulley2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ConstraintPulley2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetOtherBody(RigidBody2D@+)", AS_METHODPR(ConstraintPulley2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_otherBody(RigidBody2D@+)", AS_METHODPR(ConstraintPulley2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    // void ConstraintPulley2D::SetOtherBodyAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetOtherBodyAnchor(const Vector2&in)", AS_METHODPR(ConstraintPulley2D, SetOtherBodyAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_otherBodyAnchor(const Vector2&in)", AS_METHODPR(ConstraintPulley2D, SetOtherBodyAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void ConstraintPulley2D::SetOtherBodyGroundAnchor(const Vector2& groundAnchor) | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetOtherBodyGroundAnchor(const Vector2&in)", AS_METHODPR(ConstraintPulley2D, SetOtherBodyGroundAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_otherBodyGroundAnchor(const Vector2&in)", AS_METHODPR(ConstraintPulley2D, SetOtherBodyGroundAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void ConstraintPulley2D::SetOwnerBodyAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetOwnerBodyAnchor(const Vector2&in)", AS_METHODPR(ConstraintPulley2D, SetOwnerBodyAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_ownerBodyAnchor(const Vector2&in)", AS_METHODPR(ConstraintPulley2D, SetOwnerBodyAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void ConstraintPulley2D::SetOwnerBodyGroundAnchor(const Vector2& groundAnchor) | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetOwnerBodyGroundAnchor(const Vector2&in)", AS_METHODPR(ConstraintPulley2D, SetOwnerBodyGroundAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_ownerBodyGroundAnchor(const Vector2&in)", AS_METHODPR(ConstraintPulley2D, SetOwnerBodyGroundAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void ConstraintPulley2D::SetRatio(float ratio) | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetRatio(float)", AS_METHODPR(ConstraintPulley2D, SetRatio, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_ratio(float)", AS_METHODPR(ConstraintPulley2D, SetRatio, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetTemporary(bool)", AS_METHODPR(ConstraintPulley2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_temporary(bool)", AS_METHODPR(ConstraintPulley2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(ConstraintPulley2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ConstraintPulley2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ConstraintPulley2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ConstraintPulley2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ConstraintPulley2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "int WeakRefs() const", AS_METHODPR(ConstraintPulley2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "int get_weakRefs() const", AS_METHODPR(ConstraintPulley2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ConstraintPulley2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintPulley2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintPulley2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Constraint2D
    REGISTER_MANUAL_PART_Constraint2D(ConstraintPulley2D, "ConstraintPulley2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(ConstraintPulley2D, "ConstraintPulley2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ConstraintPulley2D, "ConstraintPulley2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ConstraintPulley2D, "ConstraintPulley2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ConstraintPulley2D, "ConstraintPulley2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ConstraintPulley2D, "ConstraintPulley2D")
#endif
#ifdef REGISTER_MANUAL_PART_ConstraintPulley2D
    REGISTER_MANUAL_PART_ConstraintPulley2D(ConstraintPulley2D, "ConstraintPulley2D")
#endif
    RegisterSubclass<Constraint2D, ConstraintPulley2D>(engine, "Constraint2D", "ConstraintPulley2D");
    RegisterSubclass<Component, ConstraintPulley2D>(engine, "Component", "ConstraintPulley2D");
    RegisterSubclass<Animatable, ConstraintPulley2D>(engine, "Animatable", "ConstraintPulley2D");
    RegisterSubclass<Serializable, ConstraintPulley2D>(engine, "Serializable", "ConstraintPulley2D");
    RegisterSubclass<Object, ConstraintPulley2D>(engine, "Object", "ConstraintPulley2D");
    RegisterSubclass<RefCounted, ConstraintPulley2D>(engine, "RefCounted", "ConstraintPulley2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintRevolute2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ConstraintRevolute2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void AllocateNetworkState()", AS_METHODPR(ConstraintRevolute2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void ApplyAttributes()", AS_METHODPR(ConstraintRevolute2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintRevolute2D::ConstraintRevolute2D(Context* context) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectBehaviour("ConstraintRevolute2D", asBEHAVE_FACTORY, "ConstraintRevolute2D@+ f()", AS_FUNCTION(ConstraintRevolute2D_ConstraintRevolute2D_Context), AS_CALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void CreateJoint()", AS_METHODPR(ConstraintRevolute2D, CreateJoint, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(ConstraintRevolute2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // const Vector2& ConstraintRevolute2D::GetAnchor() const | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const Vector2& GetAnchor() const", AS_METHODPR(ConstraintRevolute2D, GetAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const Vector2& get_anchor() const", AS_METHODPR(ConstraintRevolute2D, GetAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool GetAnimationEnabled() const", AS_METHODPR(ConstraintRevolute2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_animationEnabled() const", AS_METHODPR(ConstraintRevolute2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Constraint2D@+ GetAttachedConstraint() const", AS_METHODPR(ConstraintRevolute2D, GetAttachedConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Variant GetAttribute(uint) const", AS_METHODPR(ConstraintRevolute2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Variant get_attributes(uint) const", AS_METHODPR(ConstraintRevolute2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(ConstraintRevolute2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ConstraintRevolute2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ConstraintRevolute2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ConstraintRevolute2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ConstraintRevolute2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ConstraintRevolute2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ConstraintRevolute2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ConstraintRevolute2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool GetBlockEvents() const", AS_METHODPR(ConstraintRevolute2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const String& GetCategory() const", AS_METHODPR(ConstraintRevolute2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const String& get_category() const", AS_METHODPR(ConstraintRevolute2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool GetCollideConnected() const", AS_METHODPR(ConstraintRevolute2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_collideConnected() const", AS_METHODPR(ConstraintRevolute2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(ConstraintRevolute2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    // bool ConstraintRevolute2D::GetEnableLimit() const | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool GetEnableLimit() const", AS_METHODPR(ConstraintRevolute2D, GetEnableLimit, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_enableLimit() const", AS_METHODPR(ConstraintRevolute2D, GetEnableLimit, () const, bool), AS_CALL_THISCALL);
    // bool ConstraintRevolute2D::GetEnableMotor() const | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool GetEnableMotor() const", AS_METHODPR(ConstraintRevolute2D, GetEnableMotor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_enableMotor() const", AS_METHODPR(ConstraintRevolute2D, GetEnableMotor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(ConstraintRevolute2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Object@+ GetEventSender() const", AS_METHODPR(ConstraintRevolute2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ConstraintRevolute2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ConstraintRevolute2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ConstraintRevolute2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const VariantMap& get_globalVars() const", AS_METHODPR(ConstraintRevolute2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "uint GetID() const", AS_METHODPR(ConstraintRevolute2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "uint get_id() const", AS_METHODPR(ConstraintRevolute2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ConstraintRevolute2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // float ConstraintRevolute2D::GetLowerAngle() const | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float GetLowerAngle() const", AS_METHODPR(ConstraintRevolute2D, GetLowerAngle, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_lowerAngle() const", AS_METHODPR(ConstraintRevolute2D, GetLowerAngle, () const, float), AS_CALL_THISCALL);
    // float ConstraintRevolute2D::GetMaxMotorTorque() const | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float GetMaxMotorTorque() const", AS_METHODPR(ConstraintRevolute2D, GetMaxMotorTorque, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_maxMotorTorque() const", AS_METHODPR(ConstraintRevolute2D, GetMaxMotorTorque, () const, float), AS_CALL_THISCALL);
    // float ConstraintRevolute2D::GetMotorSpeed() const | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float GetMotorSpeed() const", AS_METHODPR(ConstraintRevolute2D, GetMotorSpeed, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_motorSpeed() const", AS_METHODPR(ConstraintRevolute2D, GetMotorSpeed, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Node@+ GetNode() const", AS_METHODPR(ConstraintRevolute2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Node@+ get_node() const", AS_METHODPR(ConstraintRevolute2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "uint GetNumAttributes() const", AS_METHODPR(ConstraintRevolute2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "uint get_numAttributes() const", AS_METHODPR(ConstraintRevolute2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(ConstraintRevolute2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ConstraintRevolute2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ConstraintRevolute2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ConstraintRevolute2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "RigidBody2D@+ GetOtherBody() const", AS_METHODPR(ConstraintRevolute2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "RigidBody2D@+ get_otherBody() const", AS_METHODPR(ConstraintRevolute2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "RigidBody2D@+ GetOwnerBody() const", AS_METHODPR(ConstraintRevolute2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "RigidBody2D@+ get_ownerBody() const", AS_METHODPR(ConstraintRevolute2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Scene@+ GetScene() const", AS_METHODPR(ConstraintRevolute2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ConstraintRevolute2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "StringHash GetType() const", AS_METHODPR(ConstraintRevolute2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "StringHash get_type() const", AS_METHODPR(ConstraintRevolute2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const String& GetTypeName() const", AS_METHODPR(ConstraintRevolute2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const String& get_typeName() const", AS_METHODPR(ConstraintRevolute2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // float ConstraintRevolute2D::GetUpperAngle() const | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float GetUpperAngle() const", AS_METHODPR(ConstraintRevolute2D, GetUpperAngle, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_upperAngle() const", AS_METHODPR(ConstraintRevolute2D, GetUpperAngle, () const, float), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool HasEventHandlers() const", AS_METHODPR(ConstraintRevolute2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ConstraintRevolute2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ConstraintRevolute2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool IsEnabled() const", AS_METHODPR(ConstraintRevolute2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_enabled() const", AS_METHODPR(ConstraintRevolute2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool IsEnabledEffective() const", AS_METHODPR(ConstraintRevolute2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_enabledEffective() const", AS_METHODPR(ConstraintRevolute2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ConstraintRevolute2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool IsReplicated() const", AS_METHODPR(ConstraintRevolute2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_replicated() const", AS_METHODPR(ConstraintRevolute2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool IsTemporary() const", AS_METHODPR(ConstraintRevolute2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_temporary() const", AS_METHODPR(ConstraintRevolute2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool Load(Deserializer&)", AS_METHODPR(ConstraintRevolute2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ConstraintRevolute2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ConstraintRevolute2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void MarkNetworkUpdate()", AS_METHODPR(ConstraintRevolute2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ConstraintRevolute2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ConstraintRevolute2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ConstraintRevolute2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void OnSetEnabled()", AS_METHODPR(ConstraintRevolute2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void PrepareNetworkUpdate()", AS_METHODPR(ConstraintRevolute2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ConstraintRevolute2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ConstraintRevolute2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "int Refs() const", AS_METHODPR(ConstraintRevolute2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "int get_refs() const", AS_METHODPR(ConstraintRevolute2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void ConstraintRevolute2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintRevolute2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void ReleaseJoint()", AS_METHODPR(ConstraintRevolute2D, ReleaseJoint, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintRevolute2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ConstraintRevolute2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void Remove()", AS_METHODPR(ConstraintRevolute2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ConstraintRevolute2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void RemoveInstanceDefault()", AS_METHODPR(ConstraintRevolute2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void RemoveObjectAnimation()", AS_METHODPR(ConstraintRevolute2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void ResetToDefault()", AS_METHODPR(ConstraintRevolute2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool Save(Serializer&) const", AS_METHODPR(ConstraintRevolute2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool SaveDefaultAttributes() const", AS_METHODPR(ConstraintRevolute2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ConstraintRevolute2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(ConstraintRevolute2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SendEvent(StringHash)", AS_METHODPR(ConstraintRevolute2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ConstraintRevolute2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ConstraintRevolute2D::SetAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAnchor(const Vector2&in)", AS_METHODPR(ConstraintRevolute2D, SetAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_anchor(const Vector2&in)", AS_METHODPR(ConstraintRevolute2D, SetAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAnimationEnabled(bool)", AS_METHODPR(ConstraintRevolute2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_animationEnabled(bool)", AS_METHODPR(ConstraintRevolute2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAnimationTime(float)", AS_METHODPR(ConstraintRevolute2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAttachedConstraint(Constraint2D@+)", AS_METHODPR(ConstraintRevolute2D, SetAttachedConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ConstraintRevolute2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ConstraintRevolute2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ConstraintRevolute2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ConstraintRevolute2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ConstraintRevolute2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ConstraintRevolute2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ConstraintRevolute2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetBlockEvents(bool)", AS_METHODPR(ConstraintRevolute2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetCollideConnected(bool)", AS_METHODPR(ConstraintRevolute2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_collideConnected(bool)", AS_METHODPR(ConstraintRevolute2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetEnabled(bool)", AS_METHODPR(ConstraintRevolute2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_enabled(bool)", AS_METHODPR(ConstraintRevolute2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void ConstraintRevolute2D::SetEnableLimit(bool enableLimit) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetEnableLimit(bool)", AS_METHODPR(ConstraintRevolute2D, SetEnableLimit, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_enableLimit(bool)", AS_METHODPR(ConstraintRevolute2D, SetEnableLimit, (bool), void), AS_CALL_THISCALL);
    // void ConstraintRevolute2D::SetEnableMotor(bool enableMotor) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetEnableMotor(bool)", AS_METHODPR(ConstraintRevolute2D, SetEnableMotor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_enableMotor(bool)", AS_METHODPR(ConstraintRevolute2D, SetEnableMotor, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintRevolute2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintRevolute2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetInstanceDefault(bool)", AS_METHODPR(ConstraintRevolute2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ConstraintRevolute2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void ConstraintRevolute2D::SetLowerAngle(float lowerAngle) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetLowerAngle(float)", AS_METHODPR(ConstraintRevolute2D, SetLowerAngle, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_lowerAngle(float)", AS_METHODPR(ConstraintRevolute2D, SetLowerAngle, (float), void), AS_CALL_THISCALL);
    // void ConstraintRevolute2D::SetMaxMotorTorque(float maxMotorTorque) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetMaxMotorTorque(float)", AS_METHODPR(ConstraintRevolute2D, SetMaxMotorTorque, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_maxMotorTorque(float)", AS_METHODPR(ConstraintRevolute2D, SetMaxMotorTorque, (float), void), AS_CALL_THISCALL);
    // void ConstraintRevolute2D::SetMotorSpeed(float motorSpeed) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetMotorSpeed(float)", AS_METHODPR(ConstraintRevolute2D, SetMotorSpeed, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_motorSpeed(float)", AS_METHODPR(ConstraintRevolute2D, SetMotorSpeed, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintRevolute2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintRevolute2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ConstraintRevolute2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetOtherBody(RigidBody2D@+)", AS_METHODPR(ConstraintRevolute2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_otherBody(RigidBody2D@+)", AS_METHODPR(ConstraintRevolute2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetTemporary(bool)", AS_METHODPR(ConstraintRevolute2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_temporary(bool)", AS_METHODPR(ConstraintRevolute2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void ConstraintRevolute2D::SetUpperAngle(float upperAngle) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetUpperAngle(float)", AS_METHODPR(ConstraintRevolute2D, SetUpperAngle, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_upperAngle(float)", AS_METHODPR(ConstraintRevolute2D, SetUpperAngle, (float), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(ConstraintRevolute2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ConstraintRevolute2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ConstraintRevolute2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ConstraintRevolute2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ConstraintRevolute2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "int WeakRefs() const", AS_METHODPR(ConstraintRevolute2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "int get_weakRefs() const", AS_METHODPR(ConstraintRevolute2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ConstraintRevolute2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintRevolute2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintRevolute2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Constraint2D
    REGISTER_MANUAL_PART_Constraint2D(ConstraintRevolute2D, "ConstraintRevolute2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(ConstraintRevolute2D, "ConstraintRevolute2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ConstraintRevolute2D, "ConstraintRevolute2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ConstraintRevolute2D, "ConstraintRevolute2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ConstraintRevolute2D, "ConstraintRevolute2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ConstraintRevolute2D, "ConstraintRevolute2D")
#endif
#ifdef REGISTER_MANUAL_PART_ConstraintRevolute2D
    REGISTER_MANUAL_PART_ConstraintRevolute2D(ConstraintRevolute2D, "ConstraintRevolute2D")
#endif
    RegisterSubclass<Constraint2D, ConstraintRevolute2D>(engine, "Constraint2D", "ConstraintRevolute2D");
    RegisterSubclass<Component, ConstraintRevolute2D>(engine, "Component", "ConstraintRevolute2D");
    RegisterSubclass<Animatable, ConstraintRevolute2D>(engine, "Animatable", "ConstraintRevolute2D");
    RegisterSubclass<Serializable, ConstraintRevolute2D>(engine, "Serializable", "ConstraintRevolute2D");
    RegisterSubclass<Object, ConstraintRevolute2D>(engine, "Object", "ConstraintRevolute2D");
    RegisterSubclass<RefCounted, ConstraintRevolute2D>(engine, "RefCounted", "ConstraintRevolute2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintRope2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ConstraintRope2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void AllocateNetworkState()", AS_METHODPR(ConstraintRope2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void ApplyAttributes()", AS_METHODPR(ConstraintRope2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintRope2D::ConstraintRope2D(Context* context) | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectBehaviour("ConstraintRope2D", asBEHAVE_FACTORY, "ConstraintRope2D@+ f()", AS_FUNCTION(ConstraintRope2D_ConstraintRope2D_Context), AS_CALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void CreateJoint()", AS_METHODPR(ConstraintRope2D, CreateJoint, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(ConstraintRope2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool GetAnimationEnabled() const", AS_METHODPR(ConstraintRope2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "bool get_animationEnabled() const", AS_METHODPR(ConstraintRope2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Constraint2D@+ GetAttachedConstraint() const", AS_METHODPR(ConstraintRope2D, GetAttachedConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Variant GetAttribute(uint) const", AS_METHODPR(ConstraintRope2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "Variant get_attributes(uint) const", AS_METHODPR(ConstraintRope2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(ConstraintRope2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ConstraintRope2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ConstraintRope2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ConstraintRope2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ConstraintRope2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ConstraintRope2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ConstraintRope2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ConstraintRope2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool GetBlockEvents() const", AS_METHODPR(ConstraintRope2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "const String& GetCategory() const", AS_METHODPR(ConstraintRope2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const String& get_category() const", AS_METHODPR(ConstraintRope2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool GetCollideConnected() const", AS_METHODPR(ConstraintRope2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "bool get_collideConnected() const", AS_METHODPR(ConstraintRope2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(ConstraintRope2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("ConstraintRope2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(ConstraintRope2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Object@+ GetEventSender() const", AS_METHODPR(ConstraintRope2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ConstraintRope2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ConstraintRope2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ConstraintRope2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const VariantMap& get_globalVars() const", AS_METHODPR(ConstraintRope2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "uint GetID() const", AS_METHODPR(ConstraintRope2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "uint get_id() const", AS_METHODPR(ConstraintRope2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ConstraintRope2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // float ConstraintRope2D::GetMaxLength() const | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "float GetMaxLength() const", AS_METHODPR(ConstraintRope2D, GetMaxLength, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "float get_maxLength() const", AS_METHODPR(ConstraintRope2D, GetMaxLength, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Node@+ GetNode() const", AS_METHODPR(ConstraintRope2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "Node@+ get_node() const", AS_METHODPR(ConstraintRope2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "uint GetNumAttributes() const", AS_METHODPR(ConstraintRope2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "uint get_numAttributes() const", AS_METHODPR(ConstraintRope2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(ConstraintRope2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ConstraintRope2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ConstraintRope2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ConstraintRope2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "RigidBody2D@+ GetOtherBody() const", AS_METHODPR(ConstraintRope2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "RigidBody2D@+ get_otherBody() const", AS_METHODPR(ConstraintRope2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // const Vector2& ConstraintRope2D::GetOtherBodyAnchor() const | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "const Vector2& GetOtherBodyAnchor() const", AS_METHODPR(ConstraintRope2D, GetOtherBodyAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const Vector2& get_otherBodyAnchor() const", AS_METHODPR(ConstraintRope2D, GetOtherBodyAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "RigidBody2D@+ GetOwnerBody() const", AS_METHODPR(ConstraintRope2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "RigidBody2D@+ get_ownerBody() const", AS_METHODPR(ConstraintRope2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // const Vector2& ConstraintRope2D::GetOwnerBodyAnchor() const | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "const Vector2& GetOwnerBodyAnchor() const", AS_METHODPR(ConstraintRope2D, GetOwnerBodyAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const Vector2& get_ownerBodyAnchor() const", AS_METHODPR(ConstraintRope2D, GetOwnerBodyAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Scene@+ GetScene() const", AS_METHODPR(ConstraintRope2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ConstraintRope2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "StringHash GetType() const", AS_METHODPR(ConstraintRope2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "StringHash get_type() const", AS_METHODPR(ConstraintRope2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "const String& GetTypeName() const", AS_METHODPR(ConstraintRope2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const String& get_typeName() const", AS_METHODPR(ConstraintRope2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool HasEventHandlers() const", AS_METHODPR(ConstraintRope2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ConstraintRope2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ConstraintRope2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool IsEnabled() const", AS_METHODPR(ConstraintRope2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "bool get_enabled() const", AS_METHODPR(ConstraintRope2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool IsEnabledEffective() const", AS_METHODPR(ConstraintRope2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "bool get_enabledEffective() const", AS_METHODPR(ConstraintRope2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ConstraintRope2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool IsReplicated() const", AS_METHODPR(ConstraintRope2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "bool get_replicated() const", AS_METHODPR(ConstraintRope2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool IsTemporary() const", AS_METHODPR(ConstraintRope2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "bool get_temporary() const", AS_METHODPR(ConstraintRope2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool Load(Deserializer&)", AS_METHODPR(ConstraintRope2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ConstraintRope2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ConstraintRope2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void MarkNetworkUpdate()", AS_METHODPR(ConstraintRope2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ConstraintRope2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ConstraintRope2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ConstraintRope2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void OnSetEnabled()", AS_METHODPR(ConstraintRope2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void PrepareNetworkUpdate()", AS_METHODPR(ConstraintRope2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ConstraintRope2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ConstraintRope2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintRope2D", "int Refs() const", AS_METHODPR(ConstraintRope2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "int get_refs() const", AS_METHODPR(ConstraintRope2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void ConstraintRope2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintRope2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void ReleaseJoint()", AS_METHODPR(ConstraintRope2D, ReleaseJoint, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintRope2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ConstraintRope2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void Remove()", AS_METHODPR(ConstraintRope2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ConstraintRope2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void RemoveInstanceDefault()", AS_METHODPR(ConstraintRope2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void RemoveObjectAnimation()", AS_METHODPR(ConstraintRope2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void ResetToDefault()", AS_METHODPR(ConstraintRope2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool Save(Serializer&) const", AS_METHODPR(ConstraintRope2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool SaveDefaultAttributes() const", AS_METHODPR(ConstraintRope2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ConstraintRope2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(ConstraintRope2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SendEvent(StringHash)", AS_METHODPR(ConstraintRope2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ConstraintRope2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetAnimationEnabled(bool)", AS_METHODPR(ConstraintRope2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_animationEnabled(bool)", AS_METHODPR(ConstraintRope2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetAnimationTime(float)", AS_METHODPR(ConstraintRope2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetAttachedConstraint(Constraint2D@+)", AS_METHODPR(ConstraintRope2D, SetAttachedConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ConstraintRope2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ConstraintRope2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ConstraintRope2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ConstraintRope2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ConstraintRope2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ConstraintRope2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ConstraintRope2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetBlockEvents(bool)", AS_METHODPR(ConstraintRope2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetCollideConnected(bool)", AS_METHODPR(ConstraintRope2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_collideConnected(bool)", AS_METHODPR(ConstraintRope2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetEnabled(bool)", AS_METHODPR(ConstraintRope2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_enabled(bool)", AS_METHODPR(ConstraintRope2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintRope2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintRope2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetInstanceDefault(bool)", AS_METHODPR(ConstraintRope2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ConstraintRope2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void ConstraintRope2D::SetMaxLength(float maxLength) | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetMaxLength(float)", AS_METHODPR(ConstraintRope2D, SetMaxLength, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_maxLength(float)", AS_METHODPR(ConstraintRope2D, SetMaxLength, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintRope2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintRope2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ConstraintRope2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetOtherBody(RigidBody2D@+)", AS_METHODPR(ConstraintRope2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_otherBody(RigidBody2D@+)", AS_METHODPR(ConstraintRope2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    // void ConstraintRope2D::SetOtherBodyAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetOtherBodyAnchor(const Vector2&in)", AS_METHODPR(ConstraintRope2D, SetOtherBodyAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_otherBodyAnchor(const Vector2&in)", AS_METHODPR(ConstraintRope2D, SetOtherBodyAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void ConstraintRope2D::SetOwnerBodyAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetOwnerBodyAnchor(const Vector2&in)", AS_METHODPR(ConstraintRope2D, SetOwnerBodyAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_ownerBodyAnchor(const Vector2&in)", AS_METHODPR(ConstraintRope2D, SetOwnerBodyAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetTemporary(bool)", AS_METHODPR(ConstraintRope2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_temporary(bool)", AS_METHODPR(ConstraintRope2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(ConstraintRope2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ConstraintRope2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ConstraintRope2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ConstraintRope2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ConstraintRope2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintRope2D", "int WeakRefs() const", AS_METHODPR(ConstraintRope2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "int get_weakRefs() const", AS_METHODPR(ConstraintRope2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ConstraintRope2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintRope2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintRope2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Constraint2D
    REGISTER_MANUAL_PART_Constraint2D(ConstraintRope2D, "ConstraintRope2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(ConstraintRope2D, "ConstraintRope2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ConstraintRope2D, "ConstraintRope2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ConstraintRope2D, "ConstraintRope2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ConstraintRope2D, "ConstraintRope2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ConstraintRope2D, "ConstraintRope2D")
#endif
#ifdef REGISTER_MANUAL_PART_ConstraintRope2D
    REGISTER_MANUAL_PART_ConstraintRope2D(ConstraintRope2D, "ConstraintRope2D")
#endif
    RegisterSubclass<Constraint2D, ConstraintRope2D>(engine, "Constraint2D", "ConstraintRope2D");
    RegisterSubclass<Component, ConstraintRope2D>(engine, "Component", "ConstraintRope2D");
    RegisterSubclass<Animatable, ConstraintRope2D>(engine, "Animatable", "ConstraintRope2D");
    RegisterSubclass<Serializable, ConstraintRope2D>(engine, "Serializable", "ConstraintRope2D");
    RegisterSubclass<Object, ConstraintRope2D>(engine, "Object", "ConstraintRope2D");
    RegisterSubclass<RefCounted, ConstraintRope2D>(engine, "RefCounted", "ConstraintRope2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintWeld2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ConstraintWeld2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void AllocateNetworkState()", AS_METHODPR(ConstraintWeld2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void ApplyAttributes()", AS_METHODPR(ConstraintWeld2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintWeld2D::ConstraintWeld2D(Context* context) | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectBehaviour("ConstraintWeld2D", asBEHAVE_FACTORY, "ConstraintWeld2D@+ f()", AS_FUNCTION(ConstraintWeld2D_ConstraintWeld2D_Context), AS_CALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void CreateJoint()", AS_METHODPR(ConstraintWeld2D, CreateJoint, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(ConstraintWeld2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // const Vector2& ConstraintWeld2D::GetAnchor() const | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "const Vector2& GetAnchor() const", AS_METHODPR(ConstraintWeld2D, GetAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "const Vector2& get_anchor() const", AS_METHODPR(ConstraintWeld2D, GetAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool GetAnimationEnabled() const", AS_METHODPR(ConstraintWeld2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool get_animationEnabled() const", AS_METHODPR(ConstraintWeld2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Constraint2D@+ GetAttachedConstraint() const", AS_METHODPR(ConstraintWeld2D, GetAttachedConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Variant GetAttribute(uint) const", AS_METHODPR(ConstraintWeld2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "Variant get_attributes(uint) const", AS_METHODPR(ConstraintWeld2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(ConstraintWeld2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ConstraintWeld2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ConstraintWeld2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ConstraintWeld2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ConstraintWeld2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ConstraintWeld2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ConstraintWeld2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ConstraintWeld2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool GetBlockEvents() const", AS_METHODPR(ConstraintWeld2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "const String& GetCategory() const", AS_METHODPR(ConstraintWeld2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "const String& get_category() const", AS_METHODPR(ConstraintWeld2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool GetCollideConnected() const", AS_METHODPR(ConstraintWeld2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool get_collideConnected() const", AS_METHODPR(ConstraintWeld2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(ConstraintWeld2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ConstraintWeld2D::GetDampingRatio() const | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "float GetDampingRatio() const", AS_METHODPR(ConstraintWeld2D, GetDampingRatio, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "float get_dampingRatio() const", AS_METHODPR(ConstraintWeld2D, GetDampingRatio, () const, float), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(ConstraintWeld2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Object@+ GetEventSender() const", AS_METHODPR(ConstraintWeld2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // float ConstraintWeld2D::GetFrequencyHz() const | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "float GetFrequencyHz() const", AS_METHODPR(ConstraintWeld2D, GetFrequencyHz, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "float get_frequencyHz() const", AS_METHODPR(ConstraintWeld2D, GetFrequencyHz, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ConstraintWeld2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ConstraintWeld2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ConstraintWeld2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "const VariantMap& get_globalVars() const", AS_METHODPR(ConstraintWeld2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "uint GetID() const", AS_METHODPR(ConstraintWeld2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "uint get_id() const", AS_METHODPR(ConstraintWeld2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ConstraintWeld2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Node@+ GetNode() const", AS_METHODPR(ConstraintWeld2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "Node@+ get_node() const", AS_METHODPR(ConstraintWeld2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "uint GetNumAttributes() const", AS_METHODPR(ConstraintWeld2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "uint get_numAttributes() const", AS_METHODPR(ConstraintWeld2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(ConstraintWeld2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ConstraintWeld2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ConstraintWeld2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ConstraintWeld2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "RigidBody2D@+ GetOtherBody() const", AS_METHODPR(ConstraintWeld2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "RigidBody2D@+ get_otherBody() const", AS_METHODPR(ConstraintWeld2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "RigidBody2D@+ GetOwnerBody() const", AS_METHODPR(ConstraintWeld2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "RigidBody2D@+ get_ownerBody() const", AS_METHODPR(ConstraintWeld2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Scene@+ GetScene() const", AS_METHODPR(ConstraintWeld2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ConstraintWeld2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "StringHash GetType() const", AS_METHODPR(ConstraintWeld2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "StringHash get_type() const", AS_METHODPR(ConstraintWeld2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "const String& GetTypeName() const", AS_METHODPR(ConstraintWeld2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "const String& get_typeName() const", AS_METHODPR(ConstraintWeld2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool HasEventHandlers() const", AS_METHODPR(ConstraintWeld2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ConstraintWeld2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ConstraintWeld2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool IsEnabled() const", AS_METHODPR(ConstraintWeld2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool get_enabled() const", AS_METHODPR(ConstraintWeld2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool IsEnabledEffective() const", AS_METHODPR(ConstraintWeld2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool get_enabledEffective() const", AS_METHODPR(ConstraintWeld2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ConstraintWeld2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool IsReplicated() const", AS_METHODPR(ConstraintWeld2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool get_replicated() const", AS_METHODPR(ConstraintWeld2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool IsTemporary() const", AS_METHODPR(ConstraintWeld2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool get_temporary() const", AS_METHODPR(ConstraintWeld2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool Load(Deserializer&)", AS_METHODPR(ConstraintWeld2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ConstraintWeld2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ConstraintWeld2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void MarkNetworkUpdate()", AS_METHODPR(ConstraintWeld2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ConstraintWeld2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ConstraintWeld2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ConstraintWeld2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void OnSetEnabled()", AS_METHODPR(ConstraintWeld2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void PrepareNetworkUpdate()", AS_METHODPR(ConstraintWeld2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ConstraintWeld2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ConstraintWeld2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "int Refs() const", AS_METHODPR(ConstraintWeld2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "int get_refs() const", AS_METHODPR(ConstraintWeld2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void ConstraintWeld2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintWeld2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void ReleaseJoint()", AS_METHODPR(ConstraintWeld2D, ReleaseJoint, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintWeld2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ConstraintWeld2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void Remove()", AS_METHODPR(ConstraintWeld2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ConstraintWeld2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void RemoveInstanceDefault()", AS_METHODPR(ConstraintWeld2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void RemoveObjectAnimation()", AS_METHODPR(ConstraintWeld2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void ResetToDefault()", AS_METHODPR(ConstraintWeld2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool Save(Serializer&) const", AS_METHODPR(ConstraintWeld2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool SaveDefaultAttributes() const", AS_METHODPR(ConstraintWeld2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ConstraintWeld2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(ConstraintWeld2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SendEvent(StringHash)", AS_METHODPR(ConstraintWeld2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ConstraintWeld2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ConstraintWeld2D::SetAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAnchor(const Vector2&in)", AS_METHODPR(ConstraintWeld2D, SetAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_anchor(const Vector2&in)", AS_METHODPR(ConstraintWeld2D, SetAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAnimationEnabled(bool)", AS_METHODPR(ConstraintWeld2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_animationEnabled(bool)", AS_METHODPR(ConstraintWeld2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAnimationTime(float)", AS_METHODPR(ConstraintWeld2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAttachedConstraint(Constraint2D@+)", AS_METHODPR(ConstraintWeld2D, SetAttachedConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ConstraintWeld2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ConstraintWeld2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ConstraintWeld2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ConstraintWeld2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ConstraintWeld2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ConstraintWeld2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ConstraintWeld2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetBlockEvents(bool)", AS_METHODPR(ConstraintWeld2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetCollideConnected(bool)", AS_METHODPR(ConstraintWeld2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_collideConnected(bool)", AS_METHODPR(ConstraintWeld2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    // void ConstraintWeld2D::SetDampingRatio(float dampingRatio) | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetDampingRatio(float)", AS_METHODPR(ConstraintWeld2D, SetDampingRatio, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_dampingRatio(float)", AS_METHODPR(ConstraintWeld2D, SetDampingRatio, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetEnabled(bool)", AS_METHODPR(ConstraintWeld2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_enabled(bool)", AS_METHODPR(ConstraintWeld2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void ConstraintWeld2D::SetFrequencyHz(float frequencyHz) | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetFrequencyHz(float)", AS_METHODPR(ConstraintWeld2D, SetFrequencyHz, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_frequencyHz(float)", AS_METHODPR(ConstraintWeld2D, SetFrequencyHz, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintWeld2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintWeld2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetInstanceDefault(bool)", AS_METHODPR(ConstraintWeld2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ConstraintWeld2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintWeld2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintWeld2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ConstraintWeld2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetOtherBody(RigidBody2D@+)", AS_METHODPR(ConstraintWeld2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_otherBody(RigidBody2D@+)", AS_METHODPR(ConstraintWeld2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetTemporary(bool)", AS_METHODPR(ConstraintWeld2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_temporary(bool)", AS_METHODPR(ConstraintWeld2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(ConstraintWeld2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ConstraintWeld2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ConstraintWeld2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ConstraintWeld2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ConstraintWeld2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "int WeakRefs() const", AS_METHODPR(ConstraintWeld2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "int get_weakRefs() const", AS_METHODPR(ConstraintWeld2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ConstraintWeld2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintWeld2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintWeld2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Constraint2D
    REGISTER_MANUAL_PART_Constraint2D(ConstraintWeld2D, "ConstraintWeld2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(ConstraintWeld2D, "ConstraintWeld2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ConstraintWeld2D, "ConstraintWeld2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ConstraintWeld2D, "ConstraintWeld2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ConstraintWeld2D, "ConstraintWeld2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ConstraintWeld2D, "ConstraintWeld2D")
#endif
#ifdef REGISTER_MANUAL_PART_ConstraintWeld2D
    REGISTER_MANUAL_PART_ConstraintWeld2D(ConstraintWeld2D, "ConstraintWeld2D")
#endif
    RegisterSubclass<Constraint2D, ConstraintWeld2D>(engine, "Constraint2D", "ConstraintWeld2D");
    RegisterSubclass<Component, ConstraintWeld2D>(engine, "Component", "ConstraintWeld2D");
    RegisterSubclass<Animatable, ConstraintWeld2D>(engine, "Animatable", "ConstraintWeld2D");
    RegisterSubclass<Serializable, ConstraintWeld2D>(engine, "Serializable", "ConstraintWeld2D");
    RegisterSubclass<Object, ConstraintWeld2D>(engine, "Object", "ConstraintWeld2D");
    RegisterSubclass<RefCounted, ConstraintWeld2D>(engine, "RefCounted", "ConstraintWeld2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintWheel2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ConstraintWheel2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void AllocateNetworkState()", AS_METHODPR(ConstraintWheel2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void ApplyAttributes()", AS_METHODPR(ConstraintWheel2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintWheel2D::ConstraintWheel2D(Context* context) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectBehaviour("ConstraintWheel2D", asBEHAVE_FACTORY, "ConstraintWheel2D@+ f()", AS_FUNCTION(ConstraintWheel2D_ConstraintWheel2D_Context), AS_CALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void CreateJoint()", AS_METHODPR(ConstraintWheel2D, CreateJoint, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(ConstraintWheel2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // const Vector2& ConstraintWheel2D::GetAnchor() const | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Vector2& GetAnchor() const", AS_METHODPR(ConstraintWheel2D, GetAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Vector2& get_anchor() const", AS_METHODPR(ConstraintWheel2D, GetAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool GetAnimationEnabled() const", AS_METHODPR(ConstraintWheel2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_animationEnabled() const", AS_METHODPR(ConstraintWheel2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Constraint2D@+ GetAttachedConstraint() const", AS_METHODPR(ConstraintWheel2D, GetAttachedConstraint, () const, Constraint2D*), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Variant GetAttribute(uint) const", AS_METHODPR(ConstraintWheel2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "Variant get_attributes(uint) const", AS_METHODPR(ConstraintWheel2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(ConstraintWheel2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ConstraintWheel2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ConstraintWheel2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ConstraintWheel2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ConstraintWheel2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ConstraintWheel2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ConstraintWheel2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ConstraintWheel2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector2& ConstraintWheel2D::GetAxis() const | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Vector2& GetAxis() const", AS_METHODPR(ConstraintWheel2D, GetAxis, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Vector2& get_axis() const", AS_METHODPR(ConstraintWheel2D, GetAxis, () const, const Vector2&), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool GetBlockEvents() const", AS_METHODPR(ConstraintWheel2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "const String& GetCategory() const", AS_METHODPR(ConstraintWheel2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const String& get_category() const", AS_METHODPR(ConstraintWheel2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool GetCollideConnected() const", AS_METHODPR(ConstraintWheel2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_collideConnected() const", AS_METHODPR(ConstraintWheel2D, GetCollideConnected, () const, bool), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(ConstraintWheel2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ConstraintWheel2D::GetDampingRatio() const | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "float GetDampingRatio() const", AS_METHODPR(ConstraintWheel2D, GetDampingRatio, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_dampingRatio() const", AS_METHODPR(ConstraintWheel2D, GetDampingRatio, () const, float), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // bool ConstraintWheel2D::GetEnableMotor() const | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool GetEnableMotor() const", AS_METHODPR(ConstraintWheel2D, GetEnableMotor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_enableMotor() const", AS_METHODPR(ConstraintWheel2D, GetEnableMotor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(ConstraintWheel2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Object@+ GetEventSender() const", AS_METHODPR(ConstraintWheel2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // float ConstraintWheel2D::GetFrequencyHz() const | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "float GetFrequencyHz() const", AS_METHODPR(ConstraintWheel2D, GetFrequencyHz, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_frequencyHz() const", AS_METHODPR(ConstraintWheel2D, GetFrequencyHz, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ConstraintWheel2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ConstraintWheel2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ConstraintWheel2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const VariantMap& get_globalVars() const", AS_METHODPR(ConstraintWheel2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "uint GetID() const", AS_METHODPR(ConstraintWheel2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "uint get_id() const", AS_METHODPR(ConstraintWheel2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ConstraintWheel2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // float ConstraintWheel2D::GetMaxMotorTorque() const | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "float GetMaxMotorTorque() const", AS_METHODPR(ConstraintWheel2D, GetMaxMotorTorque, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_maxMotorTorque() const", AS_METHODPR(ConstraintWheel2D, GetMaxMotorTorque, () const, float), AS_CALL_THISCALL);
    // float ConstraintWheel2D::GetMotorSpeed() const | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "float GetMotorSpeed() const", AS_METHODPR(ConstraintWheel2D, GetMotorSpeed, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_motorSpeed() const", AS_METHODPR(ConstraintWheel2D, GetMotorSpeed, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Node@+ GetNode() const", AS_METHODPR(ConstraintWheel2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "Node@+ get_node() const", AS_METHODPR(ConstraintWheel2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "uint GetNumAttributes() const", AS_METHODPR(ConstraintWheel2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "uint get_numAttributes() const", AS_METHODPR(ConstraintWheel2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(ConstraintWheel2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ConstraintWheel2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ConstraintWheel2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ConstraintWheel2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "RigidBody2D@+ GetOtherBody() const", AS_METHODPR(ConstraintWheel2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "RigidBody2D@+ get_otherBody() const", AS_METHODPR(ConstraintWheel2D, GetOtherBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "RigidBody2D@+ GetOwnerBody() const", AS_METHODPR(ConstraintWheel2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "RigidBody2D@+ get_ownerBody() const", AS_METHODPR(ConstraintWheel2D, GetOwnerBody, () const, RigidBody2D*), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Scene@+ GetScene() const", AS_METHODPR(ConstraintWheel2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ConstraintWheel2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "StringHash GetType() const", AS_METHODPR(ConstraintWheel2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "StringHash get_type() const", AS_METHODPR(ConstraintWheel2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "const String& GetTypeName() const", AS_METHODPR(ConstraintWheel2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const String& get_typeName() const", AS_METHODPR(ConstraintWheel2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool HasEventHandlers() const", AS_METHODPR(ConstraintWheel2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ConstraintWheel2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ConstraintWheel2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool IsEnabled() const", AS_METHODPR(ConstraintWheel2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_enabled() const", AS_METHODPR(ConstraintWheel2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool IsEnabledEffective() const", AS_METHODPR(ConstraintWheel2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_enabledEffective() const", AS_METHODPR(ConstraintWheel2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ConstraintWheel2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool IsReplicated() const", AS_METHODPR(ConstraintWheel2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_replicated() const", AS_METHODPR(ConstraintWheel2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool IsTemporary() const", AS_METHODPR(ConstraintWheel2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_temporary() const", AS_METHODPR(ConstraintWheel2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool Load(Deserializer&)", AS_METHODPR(ConstraintWheel2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ConstraintWheel2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ConstraintWheel2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void MarkNetworkUpdate()", AS_METHODPR(ConstraintWheel2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ConstraintWheel2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ConstraintWheel2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ConstraintWheel2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void OnSetEnabled()", AS_METHODPR(ConstraintWheel2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void PrepareNetworkUpdate()", AS_METHODPR(ConstraintWheel2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ConstraintWheel2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ConstraintWheel2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "int Refs() const", AS_METHODPR(ConstraintWheel2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "int get_refs() const", AS_METHODPR(ConstraintWheel2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void ConstraintWheel2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintWheel2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void ReleaseJoint()", AS_METHODPR(ConstraintWheel2D, ReleaseJoint, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintWheel2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ConstraintWheel2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void Remove()", AS_METHODPR(ConstraintWheel2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ConstraintWheel2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void RemoveInstanceDefault()", AS_METHODPR(ConstraintWheel2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void RemoveObjectAnimation()", AS_METHODPR(ConstraintWheel2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void ResetToDefault()", AS_METHODPR(ConstraintWheel2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool Save(Serializer&) const", AS_METHODPR(ConstraintWheel2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool SaveDefaultAttributes() const", AS_METHODPR(ConstraintWheel2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ConstraintWheel2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(ConstraintWheel2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SendEvent(StringHash)", AS_METHODPR(ConstraintWheel2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ConstraintWheel2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ConstraintWheel2D::SetAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAnchor(const Vector2&in)", AS_METHODPR(ConstraintWheel2D, SetAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_anchor(const Vector2&in)", AS_METHODPR(ConstraintWheel2D, SetAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAnimationEnabled(bool)", AS_METHODPR(ConstraintWheel2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_animationEnabled(bool)", AS_METHODPR(ConstraintWheel2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAnimationTime(float)", AS_METHODPR(ConstraintWheel2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAttachedConstraint(Constraint2D@+)", AS_METHODPR(ConstraintWheel2D, SetAttachedConstraint, (Constraint2D*), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ConstraintWheel2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ConstraintWheel2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ConstraintWheel2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ConstraintWheel2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ConstraintWheel2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ConstraintWheel2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ConstraintWheel2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void ConstraintWheel2D::SetAxis(const Vector2& axis) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAxis(const Vector2&in)", AS_METHODPR(ConstraintWheel2D, SetAxis, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_axis(const Vector2&in)", AS_METHODPR(ConstraintWheel2D, SetAxis, (const Vector2&), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetBlockEvents(bool)", AS_METHODPR(ConstraintWheel2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetCollideConnected(bool)", AS_METHODPR(ConstraintWheel2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_collideConnected(bool)", AS_METHODPR(ConstraintWheel2D, SetCollideConnected, (bool), void), AS_CALL_THISCALL);
    // void ConstraintWheel2D::SetDampingRatio(float dampingRatio) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetDampingRatio(float)", AS_METHODPR(ConstraintWheel2D, SetDampingRatio, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_dampingRatio(float)", AS_METHODPR(ConstraintWheel2D, SetDampingRatio, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetEnabled(bool)", AS_METHODPR(ConstraintWheel2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_enabled(bool)", AS_METHODPR(ConstraintWheel2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void ConstraintWheel2D::SetEnableMotor(bool enableMotor) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetEnableMotor(bool)", AS_METHODPR(ConstraintWheel2D, SetEnableMotor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_enableMotor(bool)", AS_METHODPR(ConstraintWheel2D, SetEnableMotor, (bool), void), AS_CALL_THISCALL);
    // void ConstraintWheel2D::SetFrequencyHz(float frequencyHz) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetFrequencyHz(float)", AS_METHODPR(ConstraintWheel2D, SetFrequencyHz, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_frequencyHz(float)", AS_METHODPR(ConstraintWheel2D, SetFrequencyHz, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintWheel2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ConstraintWheel2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetInstanceDefault(bool)", AS_METHODPR(ConstraintWheel2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ConstraintWheel2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void ConstraintWheel2D::SetMaxMotorTorque(float maxMotorTorque) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetMaxMotorTorque(float)", AS_METHODPR(ConstraintWheel2D, SetMaxMotorTorque, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_maxMotorTorque(float)", AS_METHODPR(ConstraintWheel2D, SetMaxMotorTorque, (float), void), AS_CALL_THISCALL);
    // void ConstraintWheel2D::SetMotorSpeed(float motorSpeed) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetMotorSpeed(float)", AS_METHODPR(ConstraintWheel2D, SetMotorSpeed, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_motorSpeed(float)", AS_METHODPR(ConstraintWheel2D, SetMotorSpeed, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintWheel2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ConstraintWheel2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ConstraintWheel2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetOtherBody(RigidBody2D@+)", AS_METHODPR(ConstraintWheel2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_otherBody(RigidBody2D@+)", AS_METHODPR(ConstraintWheel2D, SetOtherBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetTemporary(bool)", AS_METHODPR(ConstraintWheel2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_temporary(bool)", AS_METHODPR(ConstraintWheel2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(ConstraintWheel2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ConstraintWheel2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ConstraintWheel2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ConstraintWheel2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ConstraintWheel2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "int WeakRefs() const", AS_METHODPR(ConstraintWheel2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "int get_weakRefs() const", AS_METHODPR(ConstraintWheel2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ConstraintWheel2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintWheel2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ConstraintWheel2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Constraint2D
    REGISTER_MANUAL_PART_Constraint2D(ConstraintWheel2D, "ConstraintWheel2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(ConstraintWheel2D, "ConstraintWheel2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ConstraintWheel2D, "ConstraintWheel2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ConstraintWheel2D, "ConstraintWheel2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ConstraintWheel2D, "ConstraintWheel2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ConstraintWheel2D, "ConstraintWheel2D")
#endif
#ifdef REGISTER_MANUAL_PART_ConstraintWheel2D
    REGISTER_MANUAL_PART_ConstraintWheel2D(ConstraintWheel2D, "ConstraintWheel2D")
#endif
    RegisterSubclass<Constraint2D, ConstraintWheel2D>(engine, "Constraint2D", "ConstraintWheel2D");
    RegisterSubclass<Component, ConstraintWheel2D>(engine, "Component", "ConstraintWheel2D");
    RegisterSubclass<Animatable, ConstraintWheel2D>(engine, "Animatable", "ConstraintWheel2D");
    RegisterSubclass<Serializable, ConstraintWheel2D>(engine, "Serializable", "ConstraintWheel2D");
    RegisterSubclass<Object, ConstraintWheel2D>(engine, "Object", "ConstraintWheel2D");
    RegisterSubclass<RefCounted, ConstraintWheel2D>(engine, "RefCounted", "ConstraintWheel2D");
#endif

}

}
