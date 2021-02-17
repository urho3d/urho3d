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
    engine->RegisterObjectBehaviour("Constraint", asBEHAVE_ADDREF, "void f()", asMETHODPR(Constraint, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void AllocateNetworkState()", asMETHODPR(Constraint, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Constraint::ApplyAttributes() override | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void ApplyAttributes()", asMETHODPR(Constraint, ApplyAttributes, (), void), asCALL_THISCALL);
    // void Constraint::ApplyFrames() | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void ApplyFrames()", asMETHODPR(Constraint, ApplyFrames, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit Constraint::Constraint(Context* context) | File: ../Physics/Constraint.h
    engine->RegisterObjectBehaviour("Constraint", asBEHAVE_FACTORY, "Constraint@+ f()", asFUNCTION(Constraint_Constraint_Context), asCALL_CDECL);
    // void Constraint::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Constraint, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "bool GetAnimationEnabled() const", asMETHODPR(Constraint, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool get_animationEnabled() const", asMETHODPR(Constraint, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "Variant GetAttribute(uint) const", asMETHODPR(Constraint, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "Variant get_attributes(uint) const", asMETHODPR(Constraint, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "Variant GetAttribute(const String&in) const", asMETHODPR(Constraint, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Constraint, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Constraint, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Constraint, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Constraint, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "Variant GetAttributeDefault(uint) const", asMETHODPR(Constraint, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "Variant get_attributeDefaults(uint) const", asMETHODPR(Constraint, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Constraint, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "bool GetBlockEvents() const", asMETHODPR(Constraint, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "const String& GetCategory() const", asMETHODPR(Constraint, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const String& get_category() const", asMETHODPR(Constraint, GetCategory, () const, const String&), asCALL_THISCALL);
    // float Constraint::GetCFM() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "float GetCFM() const", asMETHODPR(Constraint, GetCFM, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "float get_cfm() const", asMETHODPR(Constraint, GetCFM, () const, float), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "Component@+ GetComponent(StringHash) const", asMETHODPR(Constraint, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // btTypedConstraint* Constraint::GetConstraint() const | File: ../Physics/Constraint.h
    // Error: type "btTypedConstraint*" can not automatically bind
    // ConstraintType Constraint::GetConstraintType() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "ConstraintType GetConstraintType() const", asMETHODPR(Constraint, GetConstraintType, () const, ConstraintType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "ConstraintType get_constraintType() const", asMETHODPR(Constraint, GetConstraintType, () const, ConstraintType), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // void Constraint::GetDependencyNodes(PODVector<Node*>& dest) override | File: ../Physics/Constraint.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // bool Constraint::GetDisableCollision() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "bool GetDisableCollision() const", asMETHODPR(Constraint, GetDisableCollision, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool get_disableCollision() const", asMETHODPR(Constraint, GetDisableCollision, () const, bool), asCALL_THISCALL);
    // float Constraint::GetERP() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "float GetERP() const", asMETHODPR(Constraint, GetERP, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "float get_erp() const", asMETHODPR(Constraint, GetERP, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "VariantMap& GetEventDataMap() const", asMETHODPR(Constraint, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "Object@+ GetEventSender() const", asMETHODPR(Constraint, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Constraint, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Constraint, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "const VariantMap& GetGlobalVars() const", asMETHODPR(Constraint, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const VariantMap& get_globalVars() const", asMETHODPR(Constraint, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const Vector2& Constraint::GetHighLimit() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "const Vector2& GetHighLimit() const", asMETHODPR(Constraint, GetHighLimit, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Vector2& get_highLimit() const", asMETHODPR(Constraint, GetHighLimit, () const, const Vector2&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "uint GetID() const", asMETHODPR(Constraint, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "uint get_id() const", asMETHODPR(Constraint, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Constraint, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const Vector2& Constraint::GetLowLimit() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "const Vector2& GetLowLimit() const", asMETHODPR(Constraint, GetLowLimit, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Vector2& get_lowLimit() const", asMETHODPR(Constraint, GetLowLimit, () const, const Vector2&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "Node@+ GetNode() const", asMETHODPR(Constraint, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "Node@+ get_node() const", asMETHODPR(Constraint, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "uint GetNumAttributes() const", asMETHODPR(Constraint, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "uint get_numAttributes() const", asMETHODPR(Constraint, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "uint GetNumNetworkAttributes() const", asMETHODPR(Constraint, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Constraint, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Constraint, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Constraint, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // RigidBody* Constraint::GetOtherBody() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "RigidBody@+ GetOtherBody() const", asMETHODPR(Constraint, GetOtherBody, () const, RigidBody*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "RigidBody@+ get_otherBody() const", asMETHODPR(Constraint, GetOtherBody, () const, RigidBody*), asCALL_THISCALL);
    // const Vector3& Constraint::GetOtherPosition() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "const Vector3& GetOtherPosition() const", asMETHODPR(Constraint, GetOtherPosition, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Vector3& get_otherPosition() const", asMETHODPR(Constraint, GetOtherPosition, () const, const Vector3&), asCALL_THISCALL);
    // const Quaternion& Constraint::GetOtherRotation() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "const Quaternion& GetOtherRotation() const", asMETHODPR(Constraint, GetOtherRotation, () const, const Quaternion&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Quaternion& get_otherRotation() const", asMETHODPR(Constraint, GetOtherRotation, () const, const Quaternion&), asCALL_THISCALL);
    // RigidBody* Constraint::GetOwnBody() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "RigidBody@+ GetOwnBody() const", asMETHODPR(Constraint, GetOwnBody, () const, RigidBody*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "RigidBody@+ get_ownBody() const", asMETHODPR(Constraint, GetOwnBody, () const, RigidBody*), asCALL_THISCALL);
    // PhysicsWorld* Constraint::GetPhysicsWorld() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "PhysicsWorld@+ GetPhysicsWorld() const", asMETHODPR(Constraint, GetPhysicsWorld, () const, PhysicsWorld*), asCALL_THISCALL);
    // const Vector3& Constraint::GetPosition() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "const Vector3& GetPosition() const", asMETHODPR(Constraint, GetPosition, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Vector3& get_position() const", asMETHODPR(Constraint, GetPosition, () const, const Vector3&), asCALL_THISCALL);
    // const Quaternion& Constraint::GetRotation() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "const Quaternion& GetRotation() const", asMETHODPR(Constraint, GetRotation, () const, const Quaternion&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Quaternion& get_rotation() const", asMETHODPR(Constraint, GetRotation, () const, const Quaternion&), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "Scene@+ GetScene() const", asMETHODPR(Constraint, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Constraint, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "StringHash GetType() const", asMETHODPR(Constraint, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "StringHash get_type() const", asMETHODPR(Constraint, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "const String& GetTypeName() const", asMETHODPR(Constraint, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const String& get_typeName() const", asMETHODPR(Constraint, GetTypeName, () const, const String&), asCALL_THISCALL);
    // Vector3 Constraint::GetWorldPosition() const | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "Vector3 GetWorldPosition() const", asMETHODPR(Constraint, GetWorldPosition, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "Vector3 get_worldPosition() const", asMETHODPR(Constraint, GetWorldPosition, () const, Vector3), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "bool HasEventHandlers() const", asMETHODPR(Constraint, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Constraint, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Constraint, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "bool IsEnabled() const", asMETHODPR(Constraint, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool get_enabled() const", asMETHODPR(Constraint, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "bool IsEnabledEffective() const", asMETHODPR(Constraint, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool get_enabledEffective() const", asMETHODPR(Constraint, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "bool IsInstanceOf(StringHash) const", asMETHODPR(Constraint, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "bool IsReplicated() const", asMETHODPR(Constraint, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool get_replicated() const", asMETHODPR(Constraint, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool IsTemporary() const", asMETHODPR(Constraint, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool get_temporary() const", asMETHODPR(Constraint, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool Load(Deserializer&)", asMETHODPR(Constraint, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Constraint, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "bool LoadXML(const XMLElement&in)", asMETHODPR(Constraint, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "void MarkNetworkUpdate()", asMETHODPR(Constraint, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Constraint, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Constraint, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Constraint, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Constraint::OnSetEnabled() override | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void OnSetEnabled()", asMETHODPR(Constraint, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "void PrepareNetworkUpdate()", asMETHODPR(Constraint, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Constraint, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Constraint, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Constraint", "int Refs() const", asMETHODPR(Constraint, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "int get_refs() const", asMETHODPR(Constraint, Refs, () const, int), asCALL_THISCALL);
    // static void Constraint::RegisterObject(Context* context) | File: ../Physics/Constraint.h
    // Not registered because have @nobind mark
    // void Constraint::ReleaseConstraint() | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void ReleaseConstraint()", asMETHODPR(Constraint, ReleaseConstraint, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Constraint", asBEHAVE_RELEASE, "void f()", asMETHODPR(Constraint, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "void Remove()", asMETHODPR(Constraint, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Constraint, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void RemoveInstanceDefault()", asMETHODPR(Constraint, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void RemoveObjectAnimation()", asMETHODPR(Constraint, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void ResetToDefault()", asMETHODPR(Constraint, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "bool Save(Serializer&) const", asMETHODPR(Constraint, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool SaveDefaultAttributes() const", asMETHODPR(Constraint, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "bool SaveJSON(JSONValue&) const", asMETHODPR(Constraint, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "bool SaveXML(XMLElement&) const", asMETHODPR(Constraint, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void SendEvent(StringHash)", asMETHODPR(Constraint, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Constraint, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetAnimationEnabled(bool)", asMETHODPR(Constraint, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_animationEnabled(bool)", asMETHODPR(Constraint, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetAnimationTime(float)", asMETHODPR(Constraint, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Constraint, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Constraint, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Constraint, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Constraint, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Constraint, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Constraint, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Constraint, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Constraint::SetAxis(const Vector3& axis) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetAxis(const Vector3&in)", asMETHODPR(Constraint, SetAxis, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_axis(const Vector3&in)", asMETHODPR(Constraint, SetAxis, (const Vector3&), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void SetBlockEvents(bool)", asMETHODPR(Constraint, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Constraint::SetCFM(float cfm) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetCFM(float)", asMETHODPR(Constraint, SetCFM, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_cfm(float)", asMETHODPR(Constraint, SetCFM, (float), void), asCALL_THISCALL);
    // void Constraint::SetConstraintType(ConstraintType type) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetConstraintType(ConstraintType)", asMETHODPR(Constraint, SetConstraintType, (ConstraintType), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_constraintType(ConstraintType)", asMETHODPR(Constraint, SetConstraintType, (ConstraintType), void), asCALL_THISCALL);
    // void Constraint::SetDisableCollision(bool disable) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetDisableCollision(bool)", asMETHODPR(Constraint, SetDisableCollision, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_disableCollision(bool)", asMETHODPR(Constraint, SetDisableCollision, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint", "void SetEnabled(bool)", asMETHODPR(Constraint, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_enabled(bool)", asMETHODPR(Constraint, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Constraint::SetERP(float erp) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetERP(float)", asMETHODPR(Constraint, SetERP, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_erp(float)", asMETHODPR(Constraint, SetERP, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Constraint, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Constraint, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Constraint::SetHighLimit(const Vector2& limit) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetHighLimit(const Vector2&in)", asMETHODPR(Constraint, SetHighLimit, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_highLimit(const Vector2&in)", asMETHODPR(Constraint, SetHighLimit, (const Vector2&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void SetInstanceDefault(bool)", asMETHODPR(Constraint, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Constraint, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Constraint::SetLowLimit(const Vector2& limit) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetLowLimit(const Vector2&in)", asMETHODPR(Constraint, SetLowLimit, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_lowLimit(const Vector2&in)", asMETHODPR(Constraint, SetLowLimit, (const Vector2&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Constraint, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Constraint, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Constraint, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Constraint::SetOtherAxis(const Vector3& axis) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetOtherAxis(const Vector3&in)", asMETHODPR(Constraint, SetOtherAxis, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_otherAxis(const Vector3&in)", asMETHODPR(Constraint, SetOtherAxis, (const Vector3&), void), asCALL_THISCALL);
    // void Constraint::SetOtherBody(RigidBody* body) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetOtherBody(RigidBody@+)", asMETHODPR(Constraint, SetOtherBody, (RigidBody*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_otherBody(RigidBody@+)", asMETHODPR(Constraint, SetOtherBody, (RigidBody*), void), asCALL_THISCALL);
    // void Constraint::SetOtherPosition(const Vector3& position) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetOtherPosition(const Vector3&in)", asMETHODPR(Constraint, SetOtherPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_otherPosition(const Vector3&in)", asMETHODPR(Constraint, SetOtherPosition, (const Vector3&), void), asCALL_THISCALL);
    // void Constraint::SetOtherRotation(const Quaternion& rotation) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetOtherRotation(const Quaternion&in)", asMETHODPR(Constraint, SetOtherRotation, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_otherRotation(const Quaternion&in)", asMETHODPR(Constraint, SetOtherRotation, (const Quaternion&), void), asCALL_THISCALL);
    // void Constraint::SetPosition(const Vector3& position) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetPosition(const Vector3&in)", asMETHODPR(Constraint, SetPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_position(const Vector3&in)", asMETHODPR(Constraint, SetPosition, (const Vector3&), void), asCALL_THISCALL);
    // void Constraint::SetRotation(const Quaternion& rotation) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetRotation(const Quaternion&in)", asMETHODPR(Constraint, SetRotation, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_rotation(const Quaternion&in)", asMETHODPR(Constraint, SetRotation, (const Quaternion&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void SetTemporary(bool)", asMETHODPR(Constraint, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_temporary(bool)", asMETHODPR(Constraint, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Constraint::SetWorldPosition(const Vector3& position) | File: ../Physics/Constraint.h
    engine->RegisterObjectMethod("Constraint", "void SetWorldPosition(const Vector3&in)", asMETHODPR(Constraint, SetWorldPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_worldPosition(const Vector3&in)", asMETHODPR(Constraint, SetWorldPosition, (const Vector3&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void UnsubscribeFromAllEvents()", asMETHODPR(Constraint, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Constraint_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Constraint, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Constraint, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Constraint, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Constraint", "int WeakRefs() const", asMETHODPR(Constraint, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "int get_weakRefs() const", asMETHODPR(Constraint, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Constraint, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Constraint, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Constraint, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Constraint2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(Constraint2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void AllocateNetworkState()", asMETHODPR(Constraint2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "void ApplyAttributes()", asMETHODPR(Constraint2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit Constraint2D::Constraint2D(Context* context) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectBehaviour("Constraint2D", asBEHAVE_FACTORY, "Constraint2D@+ f()", asFUNCTION(Constraint2D_Constraint2D_Context), asCALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "void CreateJoint()", asMETHODPR(Constraint2D, CreateJoint, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Constraint2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "bool GetAnimationEnabled() const", asMETHODPR(Constraint2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "bool get_animationEnabled() const", asMETHODPR(Constraint2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "Constraint2D@+ GetAttachedConstraint() const", asMETHODPR(Constraint2D, GetAttachedConstraint, () const, Constraint2D*), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "Variant GetAttribute(uint) const", asMETHODPR(Constraint2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "Variant get_attributes(uint) const", asMETHODPR(Constraint2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "Variant GetAttribute(const String&in) const", asMETHODPR(Constraint2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Constraint2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Constraint2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Constraint2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Constraint2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(Constraint2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(Constraint2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Constraint2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "bool GetBlockEvents() const", asMETHODPR(Constraint2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "const String& GetCategory() const", asMETHODPR(Constraint2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "const String& get_category() const", asMETHODPR(Constraint2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "bool GetCollideConnected() const", asMETHODPR(Constraint2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "bool get_collideConnected() const", asMETHODPR(Constraint2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(Constraint2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Constraint2D", "VariantMap& GetEventDataMap() const", asMETHODPR(Constraint2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "Object@+ GetEventSender() const", asMETHODPR(Constraint2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Constraint2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Constraint2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(Constraint2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "const VariantMap& get_globalVars() const", asMETHODPR(Constraint2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "uint GetID() const", asMETHODPR(Constraint2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "uint get_id() const", asMETHODPR(Constraint2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Constraint2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "Node@+ GetNode() const", asMETHODPR(Constraint2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "Node@+ get_node() const", asMETHODPR(Constraint2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "uint GetNumAttributes() const", asMETHODPR(Constraint2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "uint get_numAttributes() const", asMETHODPR(Constraint2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "uint GetNumNetworkAttributes() const", asMETHODPR(Constraint2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Constraint2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Constraint2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Constraint2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "RigidBody2D@+ GetOtherBody() const", asMETHODPR(Constraint2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "RigidBody2D@+ get_otherBody() const", asMETHODPR(Constraint2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "RigidBody2D@+ GetOwnerBody() const", asMETHODPR(Constraint2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "RigidBody2D@+ get_ownerBody() const", asMETHODPR(Constraint2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "Scene@+ GetScene() const", asMETHODPR(Constraint2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Constraint2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "StringHash GetType() const", asMETHODPR(Constraint2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "StringHash get_type() const", asMETHODPR(Constraint2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "const String& GetTypeName() const", asMETHODPR(Constraint2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "const String& get_typeName() const", asMETHODPR(Constraint2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "bool HasEventHandlers() const", asMETHODPR(Constraint2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Constraint2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Constraint2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "bool IsEnabled() const", asMETHODPR(Constraint2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "bool get_enabled() const", asMETHODPR(Constraint2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "bool IsEnabledEffective() const", asMETHODPR(Constraint2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "bool get_enabledEffective() const", asMETHODPR(Constraint2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(Constraint2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "bool IsReplicated() const", asMETHODPR(Constraint2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "bool get_replicated() const", asMETHODPR(Constraint2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool IsTemporary() const", asMETHODPR(Constraint2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "bool get_temporary() const", asMETHODPR(Constraint2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool Load(Deserializer&)", asMETHODPR(Constraint2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Constraint2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(Constraint2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "void MarkNetworkUpdate()", asMETHODPR(Constraint2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Constraint2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Constraint2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Constraint2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "void OnSetEnabled()", asMETHODPR(Constraint2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "void PrepareNetworkUpdate()", asMETHODPR(Constraint2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Constraint2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Constraint2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Constraint2D", "int Refs() const", asMETHODPR(Constraint2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "int get_refs() const", asMETHODPR(Constraint2D, Refs, () const, int), asCALL_THISCALL);
    // static void Constraint2D::RegisterObject(Context* context) | File: ../Urho2D/Constraint2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "void ReleaseJoint()", asMETHODPR(Constraint2D, ReleaseJoint, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Constraint2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(Constraint2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "void Remove()", asMETHODPR(Constraint2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Constraint2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void RemoveInstanceDefault()", asMETHODPR(Constraint2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void RemoveObjectAnimation()", asMETHODPR(Constraint2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void ResetToDefault()", asMETHODPR(Constraint2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "bool Save(Serializer&) const", asMETHODPR(Constraint2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool SaveDefaultAttributes() const", asMETHODPR(Constraint2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(Constraint2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "bool SaveXML(XMLElement&) const", asMETHODPR(Constraint2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void SendEvent(StringHash)", asMETHODPR(Constraint2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Constraint2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetAnimationEnabled(bool)", asMETHODPR(Constraint2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "void set_animationEnabled(bool)", asMETHODPR(Constraint2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetAnimationTime(float)", asMETHODPR(Constraint2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "void SetAttachedConstraint(Constraint2D@+)", asMETHODPR(Constraint2D, SetAttachedConstraint, (Constraint2D*), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Constraint2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Constraint2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Constraint2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Constraint2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Constraint2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Constraint2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Constraint2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void SetBlockEvents(bool)", asMETHODPR(Constraint2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "void SetCollideConnected(bool)", asMETHODPR(Constraint2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "void set_collideConnected(bool)", asMETHODPR(Constraint2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Constraint2D", "void SetEnabled(bool)", asMETHODPR(Constraint2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "void set_enabled(bool)", asMETHODPR(Constraint2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Constraint2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Constraint2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetInstanceDefault(bool)", asMETHODPR(Constraint2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Constraint2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Constraint2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Constraint2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Constraint2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("Constraint2D", "void SetOtherBody(RigidBody2D@+)", asMETHODPR(Constraint2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "void set_otherBody(RigidBody2D@+)", asMETHODPR(Constraint2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void SetTemporary(bool)", asMETHODPR(Constraint2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "void set_temporary(bool)", asMETHODPR(Constraint2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void UnsubscribeFromAllEvents()", asMETHODPR(Constraint2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Constraint2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Constraint2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Constraint2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Constraint2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Constraint2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Constraint2D", "int WeakRefs() const", asMETHODPR(Constraint2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint2D", "int get_weakRefs() const", asMETHODPR(Constraint2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Constraint2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Constraint2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Constraint2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Constraint2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ConstraintDistance2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(ConstraintDistance2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void AllocateNetworkState()", asMETHODPR(ConstraintDistance2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void ApplyAttributes()", asMETHODPR(ConstraintDistance2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintDistance2D::ConstraintDistance2D(Context* context) | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectBehaviour("ConstraintDistance2D", asBEHAVE_FACTORY, "ConstraintDistance2D@+ f()", asFUNCTION(ConstraintDistance2D_ConstraintDistance2D_Context), asCALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void CreateJoint()", asMETHODPR(ConstraintDistance2D, CreateJoint, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(ConstraintDistance2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool GetAnimationEnabled() const", asMETHODPR(ConstraintDistance2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool get_animationEnabled() const", asMETHODPR(ConstraintDistance2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Constraint2D@+ GetAttachedConstraint() const", asMETHODPR(ConstraintDistance2D, GetAttachedConstraint, () const, Constraint2D*), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Variant GetAttribute(uint) const", asMETHODPR(ConstraintDistance2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "Variant get_attributes(uint) const", asMETHODPR(ConstraintDistance2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Variant GetAttribute(const String&in) const", asMETHODPR(ConstraintDistance2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ConstraintDistance2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ConstraintDistance2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ConstraintDistance2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ConstraintDistance2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(ConstraintDistance2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(ConstraintDistance2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ConstraintDistance2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool GetBlockEvents() const", asMETHODPR(ConstraintDistance2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "const String& GetCategory() const", asMETHODPR(ConstraintDistance2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const String& get_category() const", asMETHODPR(ConstraintDistance2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool GetCollideConnected() const", asMETHODPR(ConstraintDistance2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool get_collideConnected() const", asMETHODPR(ConstraintDistance2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(ConstraintDistance2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ConstraintDistance2D::GetDampingRatio() const | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "float GetDampingRatio() const", asMETHODPR(ConstraintDistance2D, GetDampingRatio, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "float get_dampingRatio() const", asMETHODPR(ConstraintDistance2D, GetDampingRatio, () const, float), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "VariantMap& GetEventDataMap() const", asMETHODPR(ConstraintDistance2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Object@+ GetEventSender() const", asMETHODPR(ConstraintDistance2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // float ConstraintDistance2D::GetFrequencyHz() const | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "float GetFrequencyHz() const", asMETHODPR(ConstraintDistance2D, GetFrequencyHz, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "float get_frequencyHz() const", asMETHODPR(ConstraintDistance2D, GetFrequencyHz, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ConstraintDistance2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ConstraintDistance2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(ConstraintDistance2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const VariantMap& get_globalVars() const", asMETHODPR(ConstraintDistance2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "uint GetID() const", asMETHODPR(ConstraintDistance2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "uint get_id() const", asMETHODPR(ConstraintDistance2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ConstraintDistance2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // float ConstraintDistance2D::GetLength() const | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "float GetLength() const", asMETHODPR(ConstraintDistance2D, GetLength, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "float get_length() const", asMETHODPR(ConstraintDistance2D, GetLength, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Node@+ GetNode() const", asMETHODPR(ConstraintDistance2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "Node@+ get_node() const", asMETHODPR(ConstraintDistance2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "uint GetNumAttributes() const", asMETHODPR(ConstraintDistance2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "uint get_numAttributes() const", asMETHODPR(ConstraintDistance2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "uint GetNumNetworkAttributes() const", asMETHODPR(ConstraintDistance2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ConstraintDistance2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ConstraintDistance2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ConstraintDistance2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "RigidBody2D@+ GetOtherBody() const", asMETHODPR(ConstraintDistance2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "RigidBody2D@+ get_otherBody() const", asMETHODPR(ConstraintDistance2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    // const Vector2& ConstraintDistance2D::GetOtherBodyAnchor() const | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Vector2& GetOtherBodyAnchor() const", asMETHODPR(ConstraintDistance2D, GetOtherBodyAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Vector2& get_otherBodyAnchor() const", asMETHODPR(ConstraintDistance2D, GetOtherBodyAnchor, () const, const Vector2&), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "RigidBody2D@+ GetOwnerBody() const", asMETHODPR(ConstraintDistance2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "RigidBody2D@+ get_ownerBody() const", asMETHODPR(ConstraintDistance2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    // const Vector2& ConstraintDistance2D::GetOwnerBodyAnchor() const | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Vector2& GetOwnerBodyAnchor() const", asMETHODPR(ConstraintDistance2D, GetOwnerBodyAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Vector2& get_ownerBodyAnchor() const", asMETHODPR(ConstraintDistance2D, GetOwnerBodyAnchor, () const, const Vector2&), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Scene@+ GetScene() const", asMETHODPR(ConstraintDistance2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ConstraintDistance2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "StringHash GetType() const", asMETHODPR(ConstraintDistance2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "StringHash get_type() const", asMETHODPR(ConstraintDistance2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "const String& GetTypeName() const", asMETHODPR(ConstraintDistance2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const String& get_typeName() const", asMETHODPR(ConstraintDistance2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool HasEventHandlers() const", asMETHODPR(ConstraintDistance2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ConstraintDistance2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ConstraintDistance2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool IsEnabled() const", asMETHODPR(ConstraintDistance2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool get_enabled() const", asMETHODPR(ConstraintDistance2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool IsEnabledEffective() const", asMETHODPR(ConstraintDistance2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool get_enabledEffective() const", asMETHODPR(ConstraintDistance2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(ConstraintDistance2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool IsReplicated() const", asMETHODPR(ConstraintDistance2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool get_replicated() const", asMETHODPR(ConstraintDistance2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool IsTemporary() const", asMETHODPR(ConstraintDistance2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool get_temporary() const", asMETHODPR(ConstraintDistance2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool Load(Deserializer&)", asMETHODPR(ConstraintDistance2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ConstraintDistance2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(ConstraintDistance2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void MarkNetworkUpdate()", asMETHODPR(ConstraintDistance2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ConstraintDistance2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ConstraintDistance2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ConstraintDistance2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void OnSetEnabled()", asMETHODPR(ConstraintDistance2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void PrepareNetworkUpdate()", asMETHODPR(ConstraintDistance2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ConstraintDistance2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ConstraintDistance2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "int Refs() const", asMETHODPR(ConstraintDistance2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "int get_refs() const", asMETHODPR(ConstraintDistance2D, Refs, () const, int), asCALL_THISCALL);
    // static void ConstraintDistance2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintDistance2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void ReleaseJoint()", asMETHODPR(ConstraintDistance2D, ReleaseJoint, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintDistance2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(ConstraintDistance2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void Remove()", asMETHODPR(ConstraintDistance2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ConstraintDistance2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void RemoveInstanceDefault()", asMETHODPR(ConstraintDistance2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void RemoveObjectAnimation()", asMETHODPR(ConstraintDistance2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void ResetToDefault()", asMETHODPR(ConstraintDistance2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool Save(Serializer&) const", asMETHODPR(ConstraintDistance2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool SaveDefaultAttributes() const", asMETHODPR(ConstraintDistance2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(ConstraintDistance2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool SaveXML(XMLElement&) const", asMETHODPR(ConstraintDistance2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SendEvent(StringHash)", asMETHODPR(ConstraintDistance2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ConstraintDistance2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetAnimationEnabled(bool)", asMETHODPR(ConstraintDistance2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_animationEnabled(bool)", asMETHODPR(ConstraintDistance2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetAnimationTime(float)", asMETHODPR(ConstraintDistance2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetAttachedConstraint(Constraint2D@+)", asMETHODPR(ConstraintDistance2D, SetAttachedConstraint, (Constraint2D*), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ConstraintDistance2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ConstraintDistance2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ConstraintDistance2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ConstraintDistance2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ConstraintDistance2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ConstraintDistance2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ConstraintDistance2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetBlockEvents(bool)", asMETHODPR(ConstraintDistance2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetCollideConnected(bool)", asMETHODPR(ConstraintDistance2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_collideConnected(bool)", asMETHODPR(ConstraintDistance2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    // void ConstraintDistance2D::SetDampingRatio(float dampingRatio) | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetDampingRatio(float)", asMETHODPR(ConstraintDistance2D, SetDampingRatio, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_dampingRatio(float)", asMETHODPR(ConstraintDistance2D, SetDampingRatio, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetEnabled(bool)", asMETHODPR(ConstraintDistance2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_enabled(bool)", asMETHODPR(ConstraintDistance2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void ConstraintDistance2D::SetFrequencyHz(float frequencyHz) | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetFrequencyHz(float)", asMETHODPR(ConstraintDistance2D, SetFrequencyHz, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_frequencyHz(float)", asMETHODPR(ConstraintDistance2D, SetFrequencyHz, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintDistance2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintDistance2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetInstanceDefault(bool)", asMETHODPR(ConstraintDistance2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ConstraintDistance2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void ConstraintDistance2D::SetLength(float length) | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetLength(float)", asMETHODPR(ConstraintDistance2D, SetLength, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_length(float)", asMETHODPR(ConstraintDistance2D, SetLength, (float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintDistance2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintDistance2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ConstraintDistance2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetOtherBody(RigidBody2D@+)", asMETHODPR(ConstraintDistance2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_otherBody(RigidBody2D@+)", asMETHODPR(ConstraintDistance2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    // void ConstraintDistance2D::SetOtherBodyAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetOtherBodyAnchor(const Vector2&in)", asMETHODPR(ConstraintDistance2D, SetOtherBodyAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_otherBodyAnchor(const Vector2&in)", asMETHODPR(ConstraintDistance2D, SetOtherBodyAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void ConstraintDistance2D::SetOwnerBodyAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintDistance2D.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetOwnerBodyAnchor(const Vector2&in)", asMETHODPR(ConstraintDistance2D, SetOwnerBodyAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_ownerBodyAnchor(const Vector2&in)", asMETHODPR(ConstraintDistance2D, SetOwnerBodyAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void SetTemporary(bool)", asMETHODPR(ConstraintDistance2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_temporary(bool)", asMETHODPR(ConstraintDistance2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void UnsubscribeFromAllEvents()", asMETHODPR(ConstraintDistance2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ConstraintDistance2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ConstraintDistance2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ConstraintDistance2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ConstraintDistance2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "int WeakRefs() const", asMETHODPR(ConstraintDistance2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "int get_weakRefs() const", asMETHODPR(ConstraintDistance2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ConstraintDistance2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ConstraintDistance2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintDistance2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ConstraintDistance2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ConstraintFriction2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(ConstraintFriction2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void AllocateNetworkState()", asMETHODPR(ConstraintFriction2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void ApplyAttributes()", asMETHODPR(ConstraintFriction2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintFriction2D::ConstraintFriction2D(Context* context) | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectBehaviour("ConstraintFriction2D", asBEHAVE_FACTORY, "ConstraintFriction2D@+ f()", asFUNCTION(ConstraintFriction2D_ConstraintFriction2D_Context), asCALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void CreateJoint()", asMETHODPR(ConstraintFriction2D, CreateJoint, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(ConstraintFriction2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // const Vector2& ConstraintFriction2D::GetAnchor() const | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "const Vector2& GetAnchor() const", asMETHODPR(ConstraintFriction2D, GetAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "const Vector2& get_anchor() const", asMETHODPR(ConstraintFriction2D, GetAnchor, () const, const Vector2&), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool GetAnimationEnabled() const", asMETHODPR(ConstraintFriction2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool get_animationEnabled() const", asMETHODPR(ConstraintFriction2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Constraint2D@+ GetAttachedConstraint() const", asMETHODPR(ConstraintFriction2D, GetAttachedConstraint, () const, Constraint2D*), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Variant GetAttribute(uint) const", asMETHODPR(ConstraintFriction2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "Variant get_attributes(uint) const", asMETHODPR(ConstraintFriction2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Variant GetAttribute(const String&in) const", asMETHODPR(ConstraintFriction2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ConstraintFriction2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ConstraintFriction2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ConstraintFriction2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ConstraintFriction2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(ConstraintFriction2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(ConstraintFriction2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ConstraintFriction2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool GetBlockEvents() const", asMETHODPR(ConstraintFriction2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "const String& GetCategory() const", asMETHODPR(ConstraintFriction2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "const String& get_category() const", asMETHODPR(ConstraintFriction2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool GetCollideConnected() const", asMETHODPR(ConstraintFriction2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool get_collideConnected() const", asMETHODPR(ConstraintFriction2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(ConstraintFriction2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ConstraintFriction2D", "VariantMap& GetEventDataMap() const", asMETHODPR(ConstraintFriction2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Object@+ GetEventSender() const", asMETHODPR(ConstraintFriction2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ConstraintFriction2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ConstraintFriction2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(ConstraintFriction2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "const VariantMap& get_globalVars() const", asMETHODPR(ConstraintFriction2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "uint GetID() const", asMETHODPR(ConstraintFriction2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "uint get_id() const", asMETHODPR(ConstraintFriction2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ConstraintFriction2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // float ConstraintFriction2D::GetMaxForce() const | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "float GetMaxForce() const", asMETHODPR(ConstraintFriction2D, GetMaxForce, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "float get_maxForce() const", asMETHODPR(ConstraintFriction2D, GetMaxForce, () const, float), asCALL_THISCALL);
    // float ConstraintFriction2D::GetMaxTorque() const | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "float GetMaxTorque() const", asMETHODPR(ConstraintFriction2D, GetMaxTorque, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "float get_maxTorque() const", asMETHODPR(ConstraintFriction2D, GetMaxTorque, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Node@+ GetNode() const", asMETHODPR(ConstraintFriction2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "Node@+ get_node() const", asMETHODPR(ConstraintFriction2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "uint GetNumAttributes() const", asMETHODPR(ConstraintFriction2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "uint get_numAttributes() const", asMETHODPR(ConstraintFriction2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "uint GetNumNetworkAttributes() const", asMETHODPR(ConstraintFriction2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ConstraintFriction2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ConstraintFriction2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ConstraintFriction2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "RigidBody2D@+ GetOtherBody() const", asMETHODPR(ConstraintFriction2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "RigidBody2D@+ get_otherBody() const", asMETHODPR(ConstraintFriction2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "RigidBody2D@+ GetOwnerBody() const", asMETHODPR(ConstraintFriction2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "RigidBody2D@+ get_ownerBody() const", asMETHODPR(ConstraintFriction2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Scene@+ GetScene() const", asMETHODPR(ConstraintFriction2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ConstraintFriction2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "StringHash GetType() const", asMETHODPR(ConstraintFriction2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "StringHash get_type() const", asMETHODPR(ConstraintFriction2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "const String& GetTypeName() const", asMETHODPR(ConstraintFriction2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "const String& get_typeName() const", asMETHODPR(ConstraintFriction2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool HasEventHandlers() const", asMETHODPR(ConstraintFriction2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ConstraintFriction2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ConstraintFriction2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool IsEnabled() const", asMETHODPR(ConstraintFriction2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool get_enabled() const", asMETHODPR(ConstraintFriction2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool IsEnabledEffective() const", asMETHODPR(ConstraintFriction2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool get_enabledEffective() const", asMETHODPR(ConstraintFriction2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(ConstraintFriction2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool IsReplicated() const", asMETHODPR(ConstraintFriction2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool get_replicated() const", asMETHODPR(ConstraintFriction2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool IsTemporary() const", asMETHODPR(ConstraintFriction2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool get_temporary() const", asMETHODPR(ConstraintFriction2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool Load(Deserializer&)", asMETHODPR(ConstraintFriction2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ConstraintFriction2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(ConstraintFriction2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void MarkNetworkUpdate()", asMETHODPR(ConstraintFriction2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ConstraintFriction2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ConstraintFriction2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ConstraintFriction2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void OnSetEnabled()", asMETHODPR(ConstraintFriction2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void PrepareNetworkUpdate()", asMETHODPR(ConstraintFriction2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ConstraintFriction2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ConstraintFriction2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "int Refs() const", asMETHODPR(ConstraintFriction2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "int get_refs() const", asMETHODPR(ConstraintFriction2D, Refs, () const, int), asCALL_THISCALL);
    // static void ConstraintFriction2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintFriction2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void ReleaseJoint()", asMETHODPR(ConstraintFriction2D, ReleaseJoint, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintFriction2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(ConstraintFriction2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void Remove()", asMETHODPR(ConstraintFriction2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ConstraintFriction2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void RemoveInstanceDefault()", asMETHODPR(ConstraintFriction2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void RemoveObjectAnimation()", asMETHODPR(ConstraintFriction2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void ResetToDefault()", asMETHODPR(ConstraintFriction2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool Save(Serializer&) const", asMETHODPR(ConstraintFriction2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool SaveDefaultAttributes() const", asMETHODPR(ConstraintFriction2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(ConstraintFriction2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool SaveXML(XMLElement&) const", asMETHODPR(ConstraintFriction2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SendEvent(StringHash)", asMETHODPR(ConstraintFriction2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ConstraintFriction2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ConstraintFriction2D::SetAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAnchor(const Vector2&in)", asMETHODPR(ConstraintFriction2D, SetAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_anchor(const Vector2&in)", asMETHODPR(ConstraintFriction2D, SetAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAnimationEnabled(bool)", asMETHODPR(ConstraintFriction2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_animationEnabled(bool)", asMETHODPR(ConstraintFriction2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAnimationTime(float)", asMETHODPR(ConstraintFriction2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAttachedConstraint(Constraint2D@+)", asMETHODPR(ConstraintFriction2D, SetAttachedConstraint, (Constraint2D*), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ConstraintFriction2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ConstraintFriction2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ConstraintFriction2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ConstraintFriction2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ConstraintFriction2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ConstraintFriction2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ConstraintFriction2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetBlockEvents(bool)", asMETHODPR(ConstraintFriction2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetCollideConnected(bool)", asMETHODPR(ConstraintFriction2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_collideConnected(bool)", asMETHODPR(ConstraintFriction2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetEnabled(bool)", asMETHODPR(ConstraintFriction2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_enabled(bool)", asMETHODPR(ConstraintFriction2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintFriction2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintFriction2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetInstanceDefault(bool)", asMETHODPR(ConstraintFriction2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ConstraintFriction2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void ConstraintFriction2D::SetMaxForce(float maxForce) | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetMaxForce(float)", asMETHODPR(ConstraintFriction2D, SetMaxForce, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_maxForce(float)", asMETHODPR(ConstraintFriction2D, SetMaxForce, (float), void), asCALL_THISCALL);
    // void ConstraintFriction2D::SetMaxTorque(float maxTorque) | File: ../Urho2D/ConstraintFriction2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetMaxTorque(float)", asMETHODPR(ConstraintFriction2D, SetMaxTorque, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_maxTorque(float)", asMETHODPR(ConstraintFriction2D, SetMaxTorque, (float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintFriction2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintFriction2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ConstraintFriction2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetOtherBody(RigidBody2D@+)", asMETHODPR(ConstraintFriction2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_otherBody(RigidBody2D@+)", asMETHODPR(ConstraintFriction2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void SetTemporary(bool)", asMETHODPR(ConstraintFriction2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_temporary(bool)", asMETHODPR(ConstraintFriction2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void UnsubscribeFromAllEvents()", asMETHODPR(ConstraintFriction2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ConstraintFriction2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ConstraintFriction2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ConstraintFriction2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ConstraintFriction2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "int WeakRefs() const", asMETHODPR(ConstraintFriction2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "int get_weakRefs() const", asMETHODPR(ConstraintFriction2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ConstraintFriction2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ConstraintFriction2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintFriction2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ConstraintFriction2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ConstraintGear2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(ConstraintGear2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void AllocateNetworkState()", asMETHODPR(ConstraintGear2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void ApplyAttributes()", asMETHODPR(ConstraintGear2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintGear2D::ConstraintGear2D(Context* context) | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectBehaviour("ConstraintGear2D", asBEHAVE_FACTORY, "ConstraintGear2D@+ f()", asFUNCTION(ConstraintGear2D_ConstraintGear2D_Context), asCALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void CreateJoint()", asMETHODPR(ConstraintGear2D, CreateJoint, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(ConstraintGear2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool GetAnimationEnabled() const", asMETHODPR(ConstraintGear2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "bool get_animationEnabled() const", asMETHODPR(ConstraintGear2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Constraint2D@+ GetAttachedConstraint() const", asMETHODPR(ConstraintGear2D, GetAttachedConstraint, () const, Constraint2D*), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Variant GetAttribute(uint) const", asMETHODPR(ConstraintGear2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "Variant get_attributes(uint) const", asMETHODPR(ConstraintGear2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Variant GetAttribute(const String&in) const", asMETHODPR(ConstraintGear2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ConstraintGear2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ConstraintGear2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ConstraintGear2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ConstraintGear2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(ConstraintGear2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(ConstraintGear2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ConstraintGear2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool GetBlockEvents() const", asMETHODPR(ConstraintGear2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "const String& GetCategory() const", asMETHODPR(ConstraintGear2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "const String& get_category() const", asMETHODPR(ConstraintGear2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool GetCollideConnected() const", asMETHODPR(ConstraintGear2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "bool get_collideConnected() const", asMETHODPR(ConstraintGear2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(ConstraintGear2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ConstraintGear2D", "VariantMap& GetEventDataMap() const", asMETHODPR(ConstraintGear2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Object@+ GetEventSender() const", asMETHODPR(ConstraintGear2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ConstraintGear2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ConstraintGear2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(ConstraintGear2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "const VariantMap& get_globalVars() const", asMETHODPR(ConstraintGear2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "uint GetID() const", asMETHODPR(ConstraintGear2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "uint get_id() const", asMETHODPR(ConstraintGear2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ConstraintGear2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Node@+ GetNode() const", asMETHODPR(ConstraintGear2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "Node@+ get_node() const", asMETHODPR(ConstraintGear2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "uint GetNumAttributes() const", asMETHODPR(ConstraintGear2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "uint get_numAttributes() const", asMETHODPR(ConstraintGear2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "uint GetNumNetworkAttributes() const", asMETHODPR(ConstraintGear2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ConstraintGear2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ConstraintGear2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ConstraintGear2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "RigidBody2D@+ GetOtherBody() const", asMETHODPR(ConstraintGear2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "RigidBody2D@+ get_otherBody() const", asMETHODPR(ConstraintGear2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    // Constraint2D* ConstraintGear2D::GetOtherConstraint() const | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Constraint2D@+ GetOtherConstraint() const", asMETHODPR(ConstraintGear2D, GetOtherConstraint, () const, Constraint2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "Constraint2D@+ get_otherConstraint() const", asMETHODPR(ConstraintGear2D, GetOtherConstraint, () const, Constraint2D*), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "RigidBody2D@+ GetOwnerBody() const", asMETHODPR(ConstraintGear2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "RigidBody2D@+ get_ownerBody() const", asMETHODPR(ConstraintGear2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    // Constraint2D* ConstraintGear2D::GetOwnerConstraint() const | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Constraint2D@+ GetOwnerConstraint() const", asMETHODPR(ConstraintGear2D, GetOwnerConstraint, () const, Constraint2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "Constraint2D@+ get_ownerConstraint() const", asMETHODPR(ConstraintGear2D, GetOwnerConstraint, () const, Constraint2D*), asCALL_THISCALL);
    // float ConstraintGear2D::GetRatio() const | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "float GetRatio() const", asMETHODPR(ConstraintGear2D, GetRatio, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "float get_ratio() const", asMETHODPR(ConstraintGear2D, GetRatio, () const, float), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Scene@+ GetScene() const", asMETHODPR(ConstraintGear2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ConstraintGear2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "StringHash GetType() const", asMETHODPR(ConstraintGear2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "StringHash get_type() const", asMETHODPR(ConstraintGear2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "const String& GetTypeName() const", asMETHODPR(ConstraintGear2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "const String& get_typeName() const", asMETHODPR(ConstraintGear2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool HasEventHandlers() const", asMETHODPR(ConstraintGear2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ConstraintGear2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ConstraintGear2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool IsEnabled() const", asMETHODPR(ConstraintGear2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "bool get_enabled() const", asMETHODPR(ConstraintGear2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool IsEnabledEffective() const", asMETHODPR(ConstraintGear2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "bool get_enabledEffective() const", asMETHODPR(ConstraintGear2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(ConstraintGear2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool IsReplicated() const", asMETHODPR(ConstraintGear2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "bool get_replicated() const", asMETHODPR(ConstraintGear2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool IsTemporary() const", asMETHODPR(ConstraintGear2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "bool get_temporary() const", asMETHODPR(ConstraintGear2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool Load(Deserializer&)", asMETHODPR(ConstraintGear2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ConstraintGear2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(ConstraintGear2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void MarkNetworkUpdate()", asMETHODPR(ConstraintGear2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ConstraintGear2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ConstraintGear2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ConstraintGear2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void OnSetEnabled()", asMETHODPR(ConstraintGear2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void PrepareNetworkUpdate()", asMETHODPR(ConstraintGear2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ConstraintGear2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ConstraintGear2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintGear2D", "int Refs() const", asMETHODPR(ConstraintGear2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "int get_refs() const", asMETHODPR(ConstraintGear2D, Refs, () const, int), asCALL_THISCALL);
    // static void ConstraintGear2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintGear2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void ReleaseJoint()", asMETHODPR(ConstraintGear2D, ReleaseJoint, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintGear2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(ConstraintGear2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void Remove()", asMETHODPR(ConstraintGear2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ConstraintGear2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void RemoveInstanceDefault()", asMETHODPR(ConstraintGear2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void RemoveObjectAnimation()", asMETHODPR(ConstraintGear2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void ResetToDefault()", asMETHODPR(ConstraintGear2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool Save(Serializer&) const", asMETHODPR(ConstraintGear2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool SaveDefaultAttributes() const", asMETHODPR(ConstraintGear2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(ConstraintGear2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool SaveXML(XMLElement&) const", asMETHODPR(ConstraintGear2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SendEvent(StringHash)", asMETHODPR(ConstraintGear2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ConstraintGear2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetAnimationEnabled(bool)", asMETHODPR(ConstraintGear2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_animationEnabled(bool)", asMETHODPR(ConstraintGear2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetAnimationTime(float)", asMETHODPR(ConstraintGear2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetAttachedConstraint(Constraint2D@+)", asMETHODPR(ConstraintGear2D, SetAttachedConstraint, (Constraint2D*), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ConstraintGear2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ConstraintGear2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ConstraintGear2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ConstraintGear2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ConstraintGear2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ConstraintGear2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ConstraintGear2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetBlockEvents(bool)", asMETHODPR(ConstraintGear2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetCollideConnected(bool)", asMETHODPR(ConstraintGear2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_collideConnected(bool)", asMETHODPR(ConstraintGear2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetEnabled(bool)", asMETHODPR(ConstraintGear2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_enabled(bool)", asMETHODPR(ConstraintGear2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintGear2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintGear2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetInstanceDefault(bool)", asMETHODPR(ConstraintGear2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ConstraintGear2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintGear2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintGear2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ConstraintGear2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetOtherBody(RigidBody2D@+)", asMETHODPR(ConstraintGear2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_otherBody(RigidBody2D@+)", asMETHODPR(ConstraintGear2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    // void ConstraintGear2D::SetOtherConstraint(Constraint2D* constraint) | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetOtherConstraint(Constraint2D@+)", asMETHODPR(ConstraintGear2D, SetOtherConstraint, (Constraint2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_otherConstraint(Constraint2D@+)", asMETHODPR(ConstraintGear2D, SetOtherConstraint, (Constraint2D*), void), asCALL_THISCALL);
    // void ConstraintGear2D::SetOwnerConstraint(Constraint2D* constraint) | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetOwnerConstraint(Constraint2D@+)", asMETHODPR(ConstraintGear2D, SetOwnerConstraint, (Constraint2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_ownerConstraint(Constraint2D@+)", asMETHODPR(ConstraintGear2D, SetOwnerConstraint, (Constraint2D*), void), asCALL_THISCALL);
    // void ConstraintGear2D::SetRatio(float ratio) | File: ../Urho2D/ConstraintGear2D.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetRatio(float)", asMETHODPR(ConstraintGear2D, SetRatio, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_ratio(float)", asMETHODPR(ConstraintGear2D, SetRatio, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void SetTemporary(bool)", asMETHODPR(ConstraintGear2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_temporary(bool)", asMETHODPR(ConstraintGear2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void UnsubscribeFromAllEvents()", asMETHODPR(ConstraintGear2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ConstraintGear2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ConstraintGear2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ConstraintGear2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ConstraintGear2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintGear2D", "int WeakRefs() const", asMETHODPR(ConstraintGear2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "int get_weakRefs() const", asMETHODPR(ConstraintGear2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ConstraintGear2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ConstraintGear2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintGear2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ConstraintGear2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ConstraintMotor2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(ConstraintMotor2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void AllocateNetworkState()", asMETHODPR(ConstraintMotor2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void ApplyAttributes()", asMETHODPR(ConstraintMotor2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintMotor2D::ConstraintMotor2D(Context* context) | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectBehaviour("ConstraintMotor2D", asBEHAVE_FACTORY, "ConstraintMotor2D@+ f()", asFUNCTION(ConstraintMotor2D_ConstraintMotor2D_Context), asCALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void CreateJoint()", asMETHODPR(ConstraintMotor2D, CreateJoint, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(ConstraintMotor2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // float ConstraintMotor2D::GetAngularOffset() const | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "float GetAngularOffset() const", asMETHODPR(ConstraintMotor2D, GetAngularOffset, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "float get_angularOffset() const", asMETHODPR(ConstraintMotor2D, GetAngularOffset, () const, float), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool GetAnimationEnabled() const", asMETHODPR(ConstraintMotor2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool get_animationEnabled() const", asMETHODPR(ConstraintMotor2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Constraint2D@+ GetAttachedConstraint() const", asMETHODPR(ConstraintMotor2D, GetAttachedConstraint, () const, Constraint2D*), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Variant GetAttribute(uint) const", asMETHODPR(ConstraintMotor2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "Variant get_attributes(uint) const", asMETHODPR(ConstraintMotor2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Variant GetAttribute(const String&in) const", asMETHODPR(ConstraintMotor2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ConstraintMotor2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ConstraintMotor2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ConstraintMotor2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ConstraintMotor2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(ConstraintMotor2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(ConstraintMotor2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ConstraintMotor2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool GetBlockEvents() const", asMETHODPR(ConstraintMotor2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "const String& GetCategory() const", asMETHODPR(ConstraintMotor2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "const String& get_category() const", asMETHODPR(ConstraintMotor2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool GetCollideConnected() const", asMETHODPR(ConstraintMotor2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool get_collideConnected() const", asMETHODPR(ConstraintMotor2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(ConstraintMotor2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ConstraintMotor2D::GetCorrectionFactor() const | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "float GetCorrectionFactor() const", asMETHODPR(ConstraintMotor2D, GetCorrectionFactor, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "float get_correctionFactor() const", asMETHODPR(ConstraintMotor2D, GetCorrectionFactor, () const, float), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "VariantMap& GetEventDataMap() const", asMETHODPR(ConstraintMotor2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Object@+ GetEventSender() const", asMETHODPR(ConstraintMotor2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ConstraintMotor2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ConstraintMotor2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(ConstraintMotor2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "const VariantMap& get_globalVars() const", asMETHODPR(ConstraintMotor2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "uint GetID() const", asMETHODPR(ConstraintMotor2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "uint get_id() const", asMETHODPR(ConstraintMotor2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ConstraintMotor2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // const Vector2& ConstraintMotor2D::GetLinearOffset() const | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "const Vector2& GetLinearOffset() const", asMETHODPR(ConstraintMotor2D, GetLinearOffset, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "const Vector2& get_linearOffset() const", asMETHODPR(ConstraintMotor2D, GetLinearOffset, () const, const Vector2&), asCALL_THISCALL);
    // float ConstraintMotor2D::GetMaxForce() const | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "float GetMaxForce() const", asMETHODPR(ConstraintMotor2D, GetMaxForce, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "float get_maxForce() const", asMETHODPR(ConstraintMotor2D, GetMaxForce, () const, float), asCALL_THISCALL);
    // float ConstraintMotor2D::GetMaxTorque() const | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "float GetMaxTorque() const", asMETHODPR(ConstraintMotor2D, GetMaxTorque, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "float get_maxTorque() const", asMETHODPR(ConstraintMotor2D, GetMaxTorque, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Node@+ GetNode() const", asMETHODPR(ConstraintMotor2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "Node@+ get_node() const", asMETHODPR(ConstraintMotor2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "uint GetNumAttributes() const", asMETHODPR(ConstraintMotor2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "uint get_numAttributes() const", asMETHODPR(ConstraintMotor2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "uint GetNumNetworkAttributes() const", asMETHODPR(ConstraintMotor2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ConstraintMotor2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ConstraintMotor2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ConstraintMotor2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "RigidBody2D@+ GetOtherBody() const", asMETHODPR(ConstraintMotor2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "RigidBody2D@+ get_otherBody() const", asMETHODPR(ConstraintMotor2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "RigidBody2D@+ GetOwnerBody() const", asMETHODPR(ConstraintMotor2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "RigidBody2D@+ get_ownerBody() const", asMETHODPR(ConstraintMotor2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Scene@+ GetScene() const", asMETHODPR(ConstraintMotor2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ConstraintMotor2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "StringHash GetType() const", asMETHODPR(ConstraintMotor2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "StringHash get_type() const", asMETHODPR(ConstraintMotor2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "const String& GetTypeName() const", asMETHODPR(ConstraintMotor2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "const String& get_typeName() const", asMETHODPR(ConstraintMotor2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool HasEventHandlers() const", asMETHODPR(ConstraintMotor2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ConstraintMotor2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ConstraintMotor2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool IsEnabled() const", asMETHODPR(ConstraintMotor2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool get_enabled() const", asMETHODPR(ConstraintMotor2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool IsEnabledEffective() const", asMETHODPR(ConstraintMotor2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool get_enabledEffective() const", asMETHODPR(ConstraintMotor2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(ConstraintMotor2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool IsReplicated() const", asMETHODPR(ConstraintMotor2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool get_replicated() const", asMETHODPR(ConstraintMotor2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool IsTemporary() const", asMETHODPR(ConstraintMotor2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool get_temporary() const", asMETHODPR(ConstraintMotor2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool Load(Deserializer&)", asMETHODPR(ConstraintMotor2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ConstraintMotor2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(ConstraintMotor2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void MarkNetworkUpdate()", asMETHODPR(ConstraintMotor2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ConstraintMotor2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ConstraintMotor2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ConstraintMotor2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void OnSetEnabled()", asMETHODPR(ConstraintMotor2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void PrepareNetworkUpdate()", asMETHODPR(ConstraintMotor2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ConstraintMotor2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ConstraintMotor2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "int Refs() const", asMETHODPR(ConstraintMotor2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "int get_refs() const", asMETHODPR(ConstraintMotor2D, Refs, () const, int), asCALL_THISCALL);
    // static void ConstraintMotor2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintMotor2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void ReleaseJoint()", asMETHODPR(ConstraintMotor2D, ReleaseJoint, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintMotor2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(ConstraintMotor2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void Remove()", asMETHODPR(ConstraintMotor2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ConstraintMotor2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void RemoveInstanceDefault()", asMETHODPR(ConstraintMotor2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void RemoveObjectAnimation()", asMETHODPR(ConstraintMotor2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void ResetToDefault()", asMETHODPR(ConstraintMotor2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool Save(Serializer&) const", asMETHODPR(ConstraintMotor2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool SaveDefaultAttributes() const", asMETHODPR(ConstraintMotor2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(ConstraintMotor2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool SaveXML(XMLElement&) const", asMETHODPR(ConstraintMotor2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SendEvent(StringHash)", asMETHODPR(ConstraintMotor2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ConstraintMotor2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ConstraintMotor2D::SetAngularOffset(float angularOffset) | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAngularOffset(float)", asMETHODPR(ConstraintMotor2D, SetAngularOffset, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_angularOffset(float)", asMETHODPR(ConstraintMotor2D, SetAngularOffset, (float), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAnimationEnabled(bool)", asMETHODPR(ConstraintMotor2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_animationEnabled(bool)", asMETHODPR(ConstraintMotor2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAnimationTime(float)", asMETHODPR(ConstraintMotor2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAttachedConstraint(Constraint2D@+)", asMETHODPR(ConstraintMotor2D, SetAttachedConstraint, (Constraint2D*), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ConstraintMotor2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ConstraintMotor2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ConstraintMotor2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ConstraintMotor2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ConstraintMotor2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ConstraintMotor2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ConstraintMotor2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetBlockEvents(bool)", asMETHODPR(ConstraintMotor2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetCollideConnected(bool)", asMETHODPR(ConstraintMotor2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_collideConnected(bool)", asMETHODPR(ConstraintMotor2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    // void ConstraintMotor2D::SetCorrectionFactor(float correctionFactor) | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetCorrectionFactor(float)", asMETHODPR(ConstraintMotor2D, SetCorrectionFactor, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_correctionFactor(float)", asMETHODPR(ConstraintMotor2D, SetCorrectionFactor, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetEnabled(bool)", asMETHODPR(ConstraintMotor2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_enabled(bool)", asMETHODPR(ConstraintMotor2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintMotor2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintMotor2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetInstanceDefault(bool)", asMETHODPR(ConstraintMotor2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ConstraintMotor2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void ConstraintMotor2D::SetLinearOffset(const Vector2& linearOffset) | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetLinearOffset(const Vector2&in)", asMETHODPR(ConstraintMotor2D, SetLinearOffset, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_linearOffset(const Vector2&in)", asMETHODPR(ConstraintMotor2D, SetLinearOffset, (const Vector2&), void), asCALL_THISCALL);
    // void ConstraintMotor2D::SetMaxForce(float maxForce) | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetMaxForce(float)", asMETHODPR(ConstraintMotor2D, SetMaxForce, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_maxForce(float)", asMETHODPR(ConstraintMotor2D, SetMaxForce, (float), void), asCALL_THISCALL);
    // void ConstraintMotor2D::SetMaxTorque(float maxTorque) | File: ../Urho2D/ConstraintMotor2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetMaxTorque(float)", asMETHODPR(ConstraintMotor2D, SetMaxTorque, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_maxTorque(float)", asMETHODPR(ConstraintMotor2D, SetMaxTorque, (float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintMotor2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintMotor2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ConstraintMotor2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetOtherBody(RigidBody2D@+)", asMETHODPR(ConstraintMotor2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_otherBody(RigidBody2D@+)", asMETHODPR(ConstraintMotor2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void SetTemporary(bool)", asMETHODPR(ConstraintMotor2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_temporary(bool)", asMETHODPR(ConstraintMotor2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void UnsubscribeFromAllEvents()", asMETHODPR(ConstraintMotor2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ConstraintMotor2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ConstraintMotor2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ConstraintMotor2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ConstraintMotor2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "int WeakRefs() const", asMETHODPR(ConstraintMotor2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "int get_weakRefs() const", asMETHODPR(ConstraintMotor2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ConstraintMotor2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ConstraintMotor2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMotor2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ConstraintMotor2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ConstraintMouse2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(ConstraintMouse2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void AllocateNetworkState()", asMETHODPR(ConstraintMouse2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void ApplyAttributes()", asMETHODPR(ConstraintMouse2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintMouse2D::ConstraintMouse2D(Context* context) | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectBehaviour("ConstraintMouse2D", asBEHAVE_FACTORY, "ConstraintMouse2D@+ f()", asFUNCTION(ConstraintMouse2D_ConstraintMouse2D_Context), asCALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void CreateJoint()", asMETHODPR(ConstraintMouse2D, CreateJoint, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(ConstraintMouse2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool GetAnimationEnabled() const", asMETHODPR(ConstraintMouse2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool get_animationEnabled() const", asMETHODPR(ConstraintMouse2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Constraint2D@+ GetAttachedConstraint() const", asMETHODPR(ConstraintMouse2D, GetAttachedConstraint, () const, Constraint2D*), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Variant GetAttribute(uint) const", asMETHODPR(ConstraintMouse2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "Variant get_attributes(uint) const", asMETHODPR(ConstraintMouse2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Variant GetAttribute(const String&in) const", asMETHODPR(ConstraintMouse2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ConstraintMouse2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ConstraintMouse2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ConstraintMouse2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ConstraintMouse2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(ConstraintMouse2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(ConstraintMouse2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ConstraintMouse2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool GetBlockEvents() const", asMETHODPR(ConstraintMouse2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "const String& GetCategory() const", asMETHODPR(ConstraintMouse2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "const String& get_category() const", asMETHODPR(ConstraintMouse2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool GetCollideConnected() const", asMETHODPR(ConstraintMouse2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool get_collideConnected() const", asMETHODPR(ConstraintMouse2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(ConstraintMouse2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ConstraintMouse2D::GetDampingRatio() const | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "float GetDampingRatio() const", asMETHODPR(ConstraintMouse2D, GetDampingRatio, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "float get_dampingRatio() const", asMETHODPR(ConstraintMouse2D, GetDampingRatio, () const, float), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "VariantMap& GetEventDataMap() const", asMETHODPR(ConstraintMouse2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Object@+ GetEventSender() const", asMETHODPR(ConstraintMouse2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // float ConstraintMouse2D::GetFrequencyHz() const | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "float GetFrequencyHz() const", asMETHODPR(ConstraintMouse2D, GetFrequencyHz, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "float get_frequencyHz() const", asMETHODPR(ConstraintMouse2D, GetFrequencyHz, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ConstraintMouse2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ConstraintMouse2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(ConstraintMouse2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "const VariantMap& get_globalVars() const", asMETHODPR(ConstraintMouse2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "uint GetID() const", asMETHODPR(ConstraintMouse2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "uint get_id() const", asMETHODPR(ConstraintMouse2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ConstraintMouse2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // float ConstraintMouse2D::GetMaxForce() const | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "float GetMaxForce() const", asMETHODPR(ConstraintMouse2D, GetMaxForce, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "float get_maxForce() const", asMETHODPR(ConstraintMouse2D, GetMaxForce, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Node@+ GetNode() const", asMETHODPR(ConstraintMouse2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "Node@+ get_node() const", asMETHODPR(ConstraintMouse2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "uint GetNumAttributes() const", asMETHODPR(ConstraintMouse2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "uint get_numAttributes() const", asMETHODPR(ConstraintMouse2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "uint GetNumNetworkAttributes() const", asMETHODPR(ConstraintMouse2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ConstraintMouse2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ConstraintMouse2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ConstraintMouse2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "RigidBody2D@+ GetOtherBody() const", asMETHODPR(ConstraintMouse2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "RigidBody2D@+ get_otherBody() const", asMETHODPR(ConstraintMouse2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "RigidBody2D@+ GetOwnerBody() const", asMETHODPR(ConstraintMouse2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "RigidBody2D@+ get_ownerBody() const", asMETHODPR(ConstraintMouse2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Scene@+ GetScene() const", asMETHODPR(ConstraintMouse2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ConstraintMouse2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const Vector2& ConstraintMouse2D::GetTarget() const | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "const Vector2& GetTarget() const", asMETHODPR(ConstraintMouse2D, GetTarget, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "const Vector2& get_target() const", asMETHODPR(ConstraintMouse2D, GetTarget, () const, const Vector2&), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "StringHash GetType() const", asMETHODPR(ConstraintMouse2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "StringHash get_type() const", asMETHODPR(ConstraintMouse2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "const String& GetTypeName() const", asMETHODPR(ConstraintMouse2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "const String& get_typeName() const", asMETHODPR(ConstraintMouse2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool HasEventHandlers() const", asMETHODPR(ConstraintMouse2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ConstraintMouse2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ConstraintMouse2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool IsEnabled() const", asMETHODPR(ConstraintMouse2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool get_enabled() const", asMETHODPR(ConstraintMouse2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool IsEnabledEffective() const", asMETHODPR(ConstraintMouse2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool get_enabledEffective() const", asMETHODPR(ConstraintMouse2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(ConstraintMouse2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool IsReplicated() const", asMETHODPR(ConstraintMouse2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool get_replicated() const", asMETHODPR(ConstraintMouse2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool IsTemporary() const", asMETHODPR(ConstraintMouse2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool get_temporary() const", asMETHODPR(ConstraintMouse2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool Load(Deserializer&)", asMETHODPR(ConstraintMouse2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ConstraintMouse2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(ConstraintMouse2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void MarkNetworkUpdate()", asMETHODPR(ConstraintMouse2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ConstraintMouse2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ConstraintMouse2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ConstraintMouse2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void OnSetEnabled()", asMETHODPR(ConstraintMouse2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void PrepareNetworkUpdate()", asMETHODPR(ConstraintMouse2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ConstraintMouse2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ConstraintMouse2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "int Refs() const", asMETHODPR(ConstraintMouse2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "int get_refs() const", asMETHODPR(ConstraintMouse2D, Refs, () const, int), asCALL_THISCALL);
    // static void ConstraintMouse2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintMouse2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void ReleaseJoint()", asMETHODPR(ConstraintMouse2D, ReleaseJoint, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintMouse2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(ConstraintMouse2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void Remove()", asMETHODPR(ConstraintMouse2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ConstraintMouse2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void RemoveInstanceDefault()", asMETHODPR(ConstraintMouse2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void RemoveObjectAnimation()", asMETHODPR(ConstraintMouse2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void ResetToDefault()", asMETHODPR(ConstraintMouse2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool Save(Serializer&) const", asMETHODPR(ConstraintMouse2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool SaveDefaultAttributes() const", asMETHODPR(ConstraintMouse2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(ConstraintMouse2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool SaveXML(XMLElement&) const", asMETHODPR(ConstraintMouse2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SendEvent(StringHash)", asMETHODPR(ConstraintMouse2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ConstraintMouse2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetAnimationEnabled(bool)", asMETHODPR(ConstraintMouse2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_animationEnabled(bool)", asMETHODPR(ConstraintMouse2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetAnimationTime(float)", asMETHODPR(ConstraintMouse2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetAttachedConstraint(Constraint2D@+)", asMETHODPR(ConstraintMouse2D, SetAttachedConstraint, (Constraint2D*), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ConstraintMouse2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ConstraintMouse2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ConstraintMouse2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ConstraintMouse2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ConstraintMouse2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ConstraintMouse2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ConstraintMouse2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetBlockEvents(bool)", asMETHODPR(ConstraintMouse2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetCollideConnected(bool)", asMETHODPR(ConstraintMouse2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_collideConnected(bool)", asMETHODPR(ConstraintMouse2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    // void ConstraintMouse2D::SetDampingRatio(float dampingRatio) | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetDampingRatio(float)", asMETHODPR(ConstraintMouse2D, SetDampingRatio, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_dampingRatio(float)", asMETHODPR(ConstraintMouse2D, SetDampingRatio, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetEnabled(bool)", asMETHODPR(ConstraintMouse2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_enabled(bool)", asMETHODPR(ConstraintMouse2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void ConstraintMouse2D::SetFrequencyHz(float frequencyHz) | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetFrequencyHz(float)", asMETHODPR(ConstraintMouse2D, SetFrequencyHz, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_frequencyHz(float)", asMETHODPR(ConstraintMouse2D, SetFrequencyHz, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintMouse2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintMouse2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetInstanceDefault(bool)", asMETHODPR(ConstraintMouse2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ConstraintMouse2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void ConstraintMouse2D::SetMaxForce(float maxForce) | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetMaxForce(float)", asMETHODPR(ConstraintMouse2D, SetMaxForce, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_maxForce(float)", asMETHODPR(ConstraintMouse2D, SetMaxForce, (float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintMouse2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintMouse2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ConstraintMouse2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetOtherBody(RigidBody2D@+)", asMETHODPR(ConstraintMouse2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_otherBody(RigidBody2D@+)", asMETHODPR(ConstraintMouse2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    // void ConstraintMouse2D::SetTarget(const Vector2& target) | File: ../Urho2D/ConstraintMouse2D.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetTarget(const Vector2&in)", asMETHODPR(ConstraintMouse2D, SetTarget, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_target(const Vector2&in)", asMETHODPR(ConstraintMouse2D, SetTarget, (const Vector2&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void SetTemporary(bool)", asMETHODPR(ConstraintMouse2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_temporary(bool)", asMETHODPR(ConstraintMouse2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void UnsubscribeFromAllEvents()", asMETHODPR(ConstraintMouse2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ConstraintMouse2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ConstraintMouse2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ConstraintMouse2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ConstraintMouse2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "int WeakRefs() const", asMETHODPR(ConstraintMouse2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "int get_weakRefs() const", asMETHODPR(ConstraintMouse2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ConstraintMouse2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ConstraintMouse2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintMouse2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ConstraintMouse2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ConstraintPrismatic2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(ConstraintPrismatic2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void AllocateNetworkState()", asMETHODPR(ConstraintPrismatic2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void ApplyAttributes()", asMETHODPR(ConstraintPrismatic2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintPrismatic2D::ConstraintPrismatic2D(Context* context) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectBehaviour("ConstraintPrismatic2D", asBEHAVE_FACTORY, "ConstraintPrismatic2D@+ f()", asFUNCTION(ConstraintPrismatic2D_ConstraintPrismatic2D_Context), asCALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void CreateJoint()", asMETHODPR(ConstraintPrismatic2D, CreateJoint, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(ConstraintPrismatic2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // const Vector2& ConstraintPrismatic2D::GetAnchor() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Vector2& GetAnchor() const", asMETHODPR(ConstraintPrismatic2D, GetAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Vector2& get_anchor() const", asMETHODPR(ConstraintPrismatic2D, GetAnchor, () const, const Vector2&), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool GetAnimationEnabled() const", asMETHODPR(ConstraintPrismatic2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_animationEnabled() const", asMETHODPR(ConstraintPrismatic2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Constraint2D@+ GetAttachedConstraint() const", asMETHODPR(ConstraintPrismatic2D, GetAttachedConstraint, () const, Constraint2D*), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Variant GetAttribute(uint) const", asMETHODPR(ConstraintPrismatic2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Variant get_attributes(uint) const", asMETHODPR(ConstraintPrismatic2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Variant GetAttribute(const String&in) const", asMETHODPR(ConstraintPrismatic2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ConstraintPrismatic2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ConstraintPrismatic2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ConstraintPrismatic2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ConstraintPrismatic2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(ConstraintPrismatic2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(ConstraintPrismatic2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ConstraintPrismatic2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector2& ConstraintPrismatic2D::GetAxis() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Vector2& GetAxis() const", asMETHODPR(ConstraintPrismatic2D, GetAxis, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Vector2& get_axis() const", asMETHODPR(ConstraintPrismatic2D, GetAxis, () const, const Vector2&), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool GetBlockEvents() const", asMETHODPR(ConstraintPrismatic2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const String& GetCategory() const", asMETHODPR(ConstraintPrismatic2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const String& get_category() const", asMETHODPR(ConstraintPrismatic2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool GetCollideConnected() const", asMETHODPR(ConstraintPrismatic2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_collideConnected() const", asMETHODPR(ConstraintPrismatic2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(ConstraintPrismatic2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool GetEnableLimit() const", asMETHODPR(ConstraintPrismatic2D, GetEnableLimit, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_enableLimit() const", asMETHODPR(ConstraintPrismatic2D, GetEnableLimit, () const, bool), asCALL_THISCALL);
    // bool ConstraintPrismatic2D::GetEnableMotor() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool GetEnableMotor() const", asMETHODPR(ConstraintPrismatic2D, GetEnableMotor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_enableMotor() const", asMETHODPR(ConstraintPrismatic2D, GetEnableMotor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "VariantMap& GetEventDataMap() const", asMETHODPR(ConstraintPrismatic2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Object@+ GetEventSender() const", asMETHODPR(ConstraintPrismatic2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ConstraintPrismatic2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ConstraintPrismatic2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(ConstraintPrismatic2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const VariantMap& get_globalVars() const", asMETHODPR(ConstraintPrismatic2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "uint GetID() const", asMETHODPR(ConstraintPrismatic2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "uint get_id() const", asMETHODPR(ConstraintPrismatic2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ConstraintPrismatic2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // float ConstraintPrismatic2D::GetLowerTranslation() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float GetLowerTranslation() const", asMETHODPR(ConstraintPrismatic2D, GetLowerTranslation, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_lowerTranslation() const", asMETHODPR(ConstraintPrismatic2D, GetLowerTranslation, () const, float), asCALL_THISCALL);
    // float ConstraintPrismatic2D::GetMaxMotorForce() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float GetMaxMotorForce() const", asMETHODPR(ConstraintPrismatic2D, GetMaxMotorForce, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_maxMotorForce() const", asMETHODPR(ConstraintPrismatic2D, GetMaxMotorForce, () const, float), asCALL_THISCALL);
    // float ConstraintPrismatic2D::GetMotorSpeed() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float GetMotorSpeed() const", asMETHODPR(ConstraintPrismatic2D, GetMotorSpeed, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_motorSpeed() const", asMETHODPR(ConstraintPrismatic2D, GetMotorSpeed, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Node@+ GetNode() const", asMETHODPR(ConstraintPrismatic2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Node@+ get_node() const", asMETHODPR(ConstraintPrismatic2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "uint GetNumAttributes() const", asMETHODPR(ConstraintPrismatic2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "uint get_numAttributes() const", asMETHODPR(ConstraintPrismatic2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "uint GetNumNetworkAttributes() const", asMETHODPR(ConstraintPrismatic2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ConstraintPrismatic2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ConstraintPrismatic2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ConstraintPrismatic2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "RigidBody2D@+ GetOtherBody() const", asMETHODPR(ConstraintPrismatic2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "RigidBody2D@+ get_otherBody() const", asMETHODPR(ConstraintPrismatic2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "RigidBody2D@+ GetOwnerBody() const", asMETHODPR(ConstraintPrismatic2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "RigidBody2D@+ get_ownerBody() const", asMETHODPR(ConstraintPrismatic2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Scene@+ GetScene() const", asMETHODPR(ConstraintPrismatic2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ConstraintPrismatic2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "StringHash GetType() const", asMETHODPR(ConstraintPrismatic2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "StringHash get_type() const", asMETHODPR(ConstraintPrismatic2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const String& GetTypeName() const", asMETHODPR(ConstraintPrismatic2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const String& get_typeName() const", asMETHODPR(ConstraintPrismatic2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // float ConstraintPrismatic2D::GetUpperTranslation() const | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float GetUpperTranslation() const", asMETHODPR(ConstraintPrismatic2D, GetUpperTranslation, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_upperTranslation() const", asMETHODPR(ConstraintPrismatic2D, GetUpperTranslation, () const, float), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool HasEventHandlers() const", asMETHODPR(ConstraintPrismatic2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ConstraintPrismatic2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ConstraintPrismatic2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool IsEnabled() const", asMETHODPR(ConstraintPrismatic2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_enabled() const", asMETHODPR(ConstraintPrismatic2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool IsEnabledEffective() const", asMETHODPR(ConstraintPrismatic2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_enabledEffective() const", asMETHODPR(ConstraintPrismatic2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(ConstraintPrismatic2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool IsReplicated() const", asMETHODPR(ConstraintPrismatic2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_replicated() const", asMETHODPR(ConstraintPrismatic2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool IsTemporary() const", asMETHODPR(ConstraintPrismatic2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_temporary() const", asMETHODPR(ConstraintPrismatic2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool Load(Deserializer&)", asMETHODPR(ConstraintPrismatic2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ConstraintPrismatic2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(ConstraintPrismatic2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void MarkNetworkUpdate()", asMETHODPR(ConstraintPrismatic2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ConstraintPrismatic2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ConstraintPrismatic2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ConstraintPrismatic2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void OnSetEnabled()", asMETHODPR(ConstraintPrismatic2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void PrepareNetworkUpdate()", asMETHODPR(ConstraintPrismatic2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ConstraintPrismatic2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ConstraintPrismatic2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "int Refs() const", asMETHODPR(ConstraintPrismatic2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "int get_refs() const", asMETHODPR(ConstraintPrismatic2D, Refs, () const, int), asCALL_THISCALL);
    // static void ConstraintPrismatic2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintPrismatic2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void ReleaseJoint()", asMETHODPR(ConstraintPrismatic2D, ReleaseJoint, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintPrismatic2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(ConstraintPrismatic2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void Remove()", asMETHODPR(ConstraintPrismatic2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ConstraintPrismatic2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void RemoveInstanceDefault()", asMETHODPR(ConstraintPrismatic2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void RemoveObjectAnimation()", asMETHODPR(ConstraintPrismatic2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void ResetToDefault()", asMETHODPR(ConstraintPrismatic2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool Save(Serializer&) const", asMETHODPR(ConstraintPrismatic2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool SaveDefaultAttributes() const", asMETHODPR(ConstraintPrismatic2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(ConstraintPrismatic2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool SaveXML(XMLElement&) const", asMETHODPR(ConstraintPrismatic2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SendEvent(StringHash)", asMETHODPR(ConstraintPrismatic2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ConstraintPrismatic2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ConstraintPrismatic2D::SetAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAnchor(const Vector2&in)", asMETHODPR(ConstraintPrismatic2D, SetAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_anchor(const Vector2&in)", asMETHODPR(ConstraintPrismatic2D, SetAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAnimationEnabled(bool)", asMETHODPR(ConstraintPrismatic2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_animationEnabled(bool)", asMETHODPR(ConstraintPrismatic2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAnimationTime(float)", asMETHODPR(ConstraintPrismatic2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAttachedConstraint(Constraint2D@+)", asMETHODPR(ConstraintPrismatic2D, SetAttachedConstraint, (Constraint2D*), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ConstraintPrismatic2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ConstraintPrismatic2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ConstraintPrismatic2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ConstraintPrismatic2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ConstraintPrismatic2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ConstraintPrismatic2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ConstraintPrismatic2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void ConstraintPrismatic2D::SetAxis(const Vector2& axis) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetAxis(const Vector2&in)", asMETHODPR(ConstraintPrismatic2D, SetAxis, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_axis(const Vector2&in)", asMETHODPR(ConstraintPrismatic2D, SetAxis, (const Vector2&), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetBlockEvents(bool)", asMETHODPR(ConstraintPrismatic2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetCollideConnected(bool)", asMETHODPR(ConstraintPrismatic2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_collideConnected(bool)", asMETHODPR(ConstraintPrismatic2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetEnabled(bool)", asMETHODPR(ConstraintPrismatic2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_enabled(bool)", asMETHODPR(ConstraintPrismatic2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void ConstraintPrismatic2D::SetEnableLimit(bool enableLimit) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetEnableLimit(bool)", asMETHODPR(ConstraintPrismatic2D, SetEnableLimit, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_enableLimit(bool)", asMETHODPR(ConstraintPrismatic2D, SetEnableLimit, (bool), void), asCALL_THISCALL);
    // void ConstraintPrismatic2D::SetEnableMotor(bool enableMotor) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetEnableMotor(bool)", asMETHODPR(ConstraintPrismatic2D, SetEnableMotor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_enableMotor(bool)", asMETHODPR(ConstraintPrismatic2D, SetEnableMotor, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintPrismatic2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintPrismatic2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetInstanceDefault(bool)", asMETHODPR(ConstraintPrismatic2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ConstraintPrismatic2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void ConstraintPrismatic2D::SetLowerTranslation(float lowerTranslation) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetLowerTranslation(float)", asMETHODPR(ConstraintPrismatic2D, SetLowerTranslation, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_lowerTranslation(float)", asMETHODPR(ConstraintPrismatic2D, SetLowerTranslation, (float), void), asCALL_THISCALL);
    // void ConstraintPrismatic2D::SetMaxMotorForce(float maxMotorForce) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetMaxMotorForce(float)", asMETHODPR(ConstraintPrismatic2D, SetMaxMotorForce, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_maxMotorForce(float)", asMETHODPR(ConstraintPrismatic2D, SetMaxMotorForce, (float), void), asCALL_THISCALL);
    // void ConstraintPrismatic2D::SetMotorSpeed(float motorSpeed) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetMotorSpeed(float)", asMETHODPR(ConstraintPrismatic2D, SetMotorSpeed, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_motorSpeed(float)", asMETHODPR(ConstraintPrismatic2D, SetMotorSpeed, (float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintPrismatic2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintPrismatic2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ConstraintPrismatic2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetOtherBody(RigidBody2D@+)", asMETHODPR(ConstraintPrismatic2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_otherBody(RigidBody2D@+)", asMETHODPR(ConstraintPrismatic2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetTemporary(bool)", asMETHODPR(ConstraintPrismatic2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_temporary(bool)", asMETHODPR(ConstraintPrismatic2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void ConstraintPrismatic2D::SetUpperTranslation(float upperTranslation) | File: ../Urho2D/ConstraintPrismatic2D.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void SetUpperTranslation(float)", asMETHODPR(ConstraintPrismatic2D, SetUpperTranslation, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_upperTranslation(float)", asMETHODPR(ConstraintPrismatic2D, SetUpperTranslation, (float), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void UnsubscribeFromAllEvents()", asMETHODPR(ConstraintPrismatic2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ConstraintPrismatic2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ConstraintPrismatic2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ConstraintPrismatic2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ConstraintPrismatic2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "int WeakRefs() const", asMETHODPR(ConstraintPrismatic2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "int get_weakRefs() const", asMETHODPR(ConstraintPrismatic2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ConstraintPrismatic2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ConstraintPrismatic2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ConstraintPrismatic2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ConstraintPulley2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(ConstraintPulley2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void AllocateNetworkState()", asMETHODPR(ConstraintPulley2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void ApplyAttributes()", asMETHODPR(ConstraintPulley2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintPulley2D::ConstraintPulley2D(Context* context) | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectBehaviour("ConstraintPulley2D", asBEHAVE_FACTORY, "ConstraintPulley2D@+ f()", asFUNCTION(ConstraintPulley2D_ConstraintPulley2D_Context), asCALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void CreateJoint()", asMETHODPR(ConstraintPulley2D, CreateJoint, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(ConstraintPulley2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool GetAnimationEnabled() const", asMETHODPR(ConstraintPulley2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool get_animationEnabled() const", asMETHODPR(ConstraintPulley2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Constraint2D@+ GetAttachedConstraint() const", asMETHODPR(ConstraintPulley2D, GetAttachedConstraint, () const, Constraint2D*), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Variant GetAttribute(uint) const", asMETHODPR(ConstraintPulley2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "Variant get_attributes(uint) const", asMETHODPR(ConstraintPulley2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Variant GetAttribute(const String&in) const", asMETHODPR(ConstraintPulley2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ConstraintPulley2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ConstraintPulley2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ConstraintPulley2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ConstraintPulley2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(ConstraintPulley2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(ConstraintPulley2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ConstraintPulley2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool GetBlockEvents() const", asMETHODPR(ConstraintPulley2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const String& GetCategory() const", asMETHODPR(ConstraintPulley2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const String& get_category() const", asMETHODPR(ConstraintPulley2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool GetCollideConnected() const", asMETHODPR(ConstraintPulley2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool get_collideConnected() const", asMETHODPR(ConstraintPulley2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(ConstraintPulley2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ConstraintPulley2D", "VariantMap& GetEventDataMap() const", asMETHODPR(ConstraintPulley2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Object@+ GetEventSender() const", asMETHODPR(ConstraintPulley2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ConstraintPulley2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ConstraintPulley2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(ConstraintPulley2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const VariantMap& get_globalVars() const", asMETHODPR(ConstraintPulley2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "uint GetID() const", asMETHODPR(ConstraintPulley2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "uint get_id() const", asMETHODPR(ConstraintPulley2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ConstraintPulley2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Node@+ GetNode() const", asMETHODPR(ConstraintPulley2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "Node@+ get_node() const", asMETHODPR(ConstraintPulley2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "uint GetNumAttributes() const", asMETHODPR(ConstraintPulley2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "uint get_numAttributes() const", asMETHODPR(ConstraintPulley2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "uint GetNumNetworkAttributes() const", asMETHODPR(ConstraintPulley2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ConstraintPulley2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ConstraintPulley2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ConstraintPulley2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "RigidBody2D@+ GetOtherBody() const", asMETHODPR(ConstraintPulley2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "RigidBody2D@+ get_otherBody() const", asMETHODPR(ConstraintPulley2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    // const Vector2& ConstraintPulley2D::GetOtherBodyAnchor() const | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& GetOtherBodyAnchor() const", asMETHODPR(ConstraintPulley2D, GetOtherBodyAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_otherBodyAnchor() const", asMETHODPR(ConstraintPulley2D, GetOtherBodyAnchor, () const, const Vector2&), asCALL_THISCALL);
    // const Vector2& ConstraintPulley2D::GetOtherBodyGroundAnchor() const | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& GetOtherBodyGroundAnchor() const", asMETHODPR(ConstraintPulley2D, GetOtherBodyGroundAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_otherBodyGroundAnchor() const", asMETHODPR(ConstraintPulley2D, GetOtherBodyGroundAnchor, () const, const Vector2&), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "RigidBody2D@+ GetOwnerBody() const", asMETHODPR(ConstraintPulley2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "RigidBody2D@+ get_ownerBody() const", asMETHODPR(ConstraintPulley2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    // const Vector2& ConstraintPulley2D::GetOwnerBodyAnchor() const | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& GetOwnerBodyAnchor() const", asMETHODPR(ConstraintPulley2D, GetOwnerBodyAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_ownerBodyAnchor() const", asMETHODPR(ConstraintPulley2D, GetOwnerBodyAnchor, () const, const Vector2&), asCALL_THISCALL);
    // const Vector2& ConstraintPulley2D::GetOwnerBodyGroundAnchor() const | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& GetOwnerBodyGroundAnchor() const", asMETHODPR(ConstraintPulley2D, GetOwnerBodyGroundAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_ownerBodyGroundAnchor() const", asMETHODPR(ConstraintPulley2D, GetOwnerBodyGroundAnchor, () const, const Vector2&), asCALL_THISCALL);
    // float ConstraintPulley2D::GetRatio() const | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "float GetRatio() const", asMETHODPR(ConstraintPulley2D, GetRatio, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "float get_ratio() const", asMETHODPR(ConstraintPulley2D, GetRatio, () const, float), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Scene@+ GetScene() const", asMETHODPR(ConstraintPulley2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ConstraintPulley2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "StringHash GetType() const", asMETHODPR(ConstraintPulley2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "StringHash get_type() const", asMETHODPR(ConstraintPulley2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "const String& GetTypeName() const", asMETHODPR(ConstraintPulley2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const String& get_typeName() const", asMETHODPR(ConstraintPulley2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool HasEventHandlers() const", asMETHODPR(ConstraintPulley2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ConstraintPulley2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ConstraintPulley2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool IsEnabled() const", asMETHODPR(ConstraintPulley2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool get_enabled() const", asMETHODPR(ConstraintPulley2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool IsEnabledEffective() const", asMETHODPR(ConstraintPulley2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool get_enabledEffective() const", asMETHODPR(ConstraintPulley2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(ConstraintPulley2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool IsReplicated() const", asMETHODPR(ConstraintPulley2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool get_replicated() const", asMETHODPR(ConstraintPulley2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool IsTemporary() const", asMETHODPR(ConstraintPulley2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool get_temporary() const", asMETHODPR(ConstraintPulley2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool Load(Deserializer&)", asMETHODPR(ConstraintPulley2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ConstraintPulley2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(ConstraintPulley2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void MarkNetworkUpdate()", asMETHODPR(ConstraintPulley2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ConstraintPulley2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ConstraintPulley2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ConstraintPulley2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void OnSetEnabled()", asMETHODPR(ConstraintPulley2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void PrepareNetworkUpdate()", asMETHODPR(ConstraintPulley2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ConstraintPulley2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ConstraintPulley2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "int Refs() const", asMETHODPR(ConstraintPulley2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "int get_refs() const", asMETHODPR(ConstraintPulley2D, Refs, () const, int), asCALL_THISCALL);
    // static void ConstraintPulley2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintPulley2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void ReleaseJoint()", asMETHODPR(ConstraintPulley2D, ReleaseJoint, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintPulley2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(ConstraintPulley2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void Remove()", asMETHODPR(ConstraintPulley2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ConstraintPulley2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void RemoveInstanceDefault()", asMETHODPR(ConstraintPulley2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void RemoveObjectAnimation()", asMETHODPR(ConstraintPulley2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void ResetToDefault()", asMETHODPR(ConstraintPulley2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool Save(Serializer&) const", asMETHODPR(ConstraintPulley2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool SaveDefaultAttributes() const", asMETHODPR(ConstraintPulley2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(ConstraintPulley2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool SaveXML(XMLElement&) const", asMETHODPR(ConstraintPulley2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SendEvent(StringHash)", asMETHODPR(ConstraintPulley2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ConstraintPulley2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetAnimationEnabled(bool)", asMETHODPR(ConstraintPulley2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_animationEnabled(bool)", asMETHODPR(ConstraintPulley2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetAnimationTime(float)", asMETHODPR(ConstraintPulley2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetAttachedConstraint(Constraint2D@+)", asMETHODPR(ConstraintPulley2D, SetAttachedConstraint, (Constraint2D*), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ConstraintPulley2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ConstraintPulley2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ConstraintPulley2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ConstraintPulley2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ConstraintPulley2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ConstraintPulley2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ConstraintPulley2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetBlockEvents(bool)", asMETHODPR(ConstraintPulley2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetCollideConnected(bool)", asMETHODPR(ConstraintPulley2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_collideConnected(bool)", asMETHODPR(ConstraintPulley2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetEnabled(bool)", asMETHODPR(ConstraintPulley2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_enabled(bool)", asMETHODPR(ConstraintPulley2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintPulley2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintPulley2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetInstanceDefault(bool)", asMETHODPR(ConstraintPulley2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ConstraintPulley2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintPulley2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintPulley2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ConstraintPulley2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetOtherBody(RigidBody2D@+)", asMETHODPR(ConstraintPulley2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_otherBody(RigidBody2D@+)", asMETHODPR(ConstraintPulley2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    // void ConstraintPulley2D::SetOtherBodyAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetOtherBodyAnchor(const Vector2&in)", asMETHODPR(ConstraintPulley2D, SetOtherBodyAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_otherBodyAnchor(const Vector2&in)", asMETHODPR(ConstraintPulley2D, SetOtherBodyAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void ConstraintPulley2D::SetOtherBodyGroundAnchor(const Vector2& groundAnchor) | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetOtherBodyGroundAnchor(const Vector2&in)", asMETHODPR(ConstraintPulley2D, SetOtherBodyGroundAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_otherBodyGroundAnchor(const Vector2&in)", asMETHODPR(ConstraintPulley2D, SetOtherBodyGroundAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void ConstraintPulley2D::SetOwnerBodyAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetOwnerBodyAnchor(const Vector2&in)", asMETHODPR(ConstraintPulley2D, SetOwnerBodyAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_ownerBodyAnchor(const Vector2&in)", asMETHODPR(ConstraintPulley2D, SetOwnerBodyAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void ConstraintPulley2D::SetOwnerBodyGroundAnchor(const Vector2& groundAnchor) | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetOwnerBodyGroundAnchor(const Vector2&in)", asMETHODPR(ConstraintPulley2D, SetOwnerBodyGroundAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_ownerBodyGroundAnchor(const Vector2&in)", asMETHODPR(ConstraintPulley2D, SetOwnerBodyGroundAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void ConstraintPulley2D::SetRatio(float ratio) | File: ../Urho2D/ConstraintPulley2D.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetRatio(float)", asMETHODPR(ConstraintPulley2D, SetRatio, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_ratio(float)", asMETHODPR(ConstraintPulley2D, SetRatio, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void SetTemporary(bool)", asMETHODPR(ConstraintPulley2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_temporary(bool)", asMETHODPR(ConstraintPulley2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void UnsubscribeFromAllEvents()", asMETHODPR(ConstraintPulley2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ConstraintPulley2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ConstraintPulley2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ConstraintPulley2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ConstraintPulley2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "int WeakRefs() const", asMETHODPR(ConstraintPulley2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "int get_weakRefs() const", asMETHODPR(ConstraintPulley2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ConstraintPulley2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ConstraintPulley2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintPulley2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ConstraintPulley2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ConstraintRevolute2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(ConstraintRevolute2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void AllocateNetworkState()", asMETHODPR(ConstraintRevolute2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void ApplyAttributes()", asMETHODPR(ConstraintRevolute2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintRevolute2D::ConstraintRevolute2D(Context* context) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectBehaviour("ConstraintRevolute2D", asBEHAVE_FACTORY, "ConstraintRevolute2D@+ f()", asFUNCTION(ConstraintRevolute2D_ConstraintRevolute2D_Context), asCALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void CreateJoint()", asMETHODPR(ConstraintRevolute2D, CreateJoint, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(ConstraintRevolute2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // const Vector2& ConstraintRevolute2D::GetAnchor() const | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const Vector2& GetAnchor() const", asMETHODPR(ConstraintRevolute2D, GetAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const Vector2& get_anchor() const", asMETHODPR(ConstraintRevolute2D, GetAnchor, () const, const Vector2&), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool GetAnimationEnabled() const", asMETHODPR(ConstraintRevolute2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_animationEnabled() const", asMETHODPR(ConstraintRevolute2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Constraint2D@+ GetAttachedConstraint() const", asMETHODPR(ConstraintRevolute2D, GetAttachedConstraint, () const, Constraint2D*), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Variant GetAttribute(uint) const", asMETHODPR(ConstraintRevolute2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Variant get_attributes(uint) const", asMETHODPR(ConstraintRevolute2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Variant GetAttribute(const String&in) const", asMETHODPR(ConstraintRevolute2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ConstraintRevolute2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ConstraintRevolute2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ConstraintRevolute2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ConstraintRevolute2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(ConstraintRevolute2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(ConstraintRevolute2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ConstraintRevolute2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool GetBlockEvents() const", asMETHODPR(ConstraintRevolute2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const String& GetCategory() const", asMETHODPR(ConstraintRevolute2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const String& get_category() const", asMETHODPR(ConstraintRevolute2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool GetCollideConnected() const", asMETHODPR(ConstraintRevolute2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_collideConnected() const", asMETHODPR(ConstraintRevolute2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(ConstraintRevolute2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool GetEnableLimit() const", asMETHODPR(ConstraintRevolute2D, GetEnableLimit, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_enableLimit() const", asMETHODPR(ConstraintRevolute2D, GetEnableLimit, () const, bool), asCALL_THISCALL);
    // bool ConstraintRevolute2D::GetEnableMotor() const | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool GetEnableMotor() const", asMETHODPR(ConstraintRevolute2D, GetEnableMotor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_enableMotor() const", asMETHODPR(ConstraintRevolute2D, GetEnableMotor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "VariantMap& GetEventDataMap() const", asMETHODPR(ConstraintRevolute2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Object@+ GetEventSender() const", asMETHODPR(ConstraintRevolute2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ConstraintRevolute2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ConstraintRevolute2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(ConstraintRevolute2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const VariantMap& get_globalVars() const", asMETHODPR(ConstraintRevolute2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "uint GetID() const", asMETHODPR(ConstraintRevolute2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "uint get_id() const", asMETHODPR(ConstraintRevolute2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ConstraintRevolute2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // float ConstraintRevolute2D::GetLowerAngle() const | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float GetLowerAngle() const", asMETHODPR(ConstraintRevolute2D, GetLowerAngle, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_lowerAngle() const", asMETHODPR(ConstraintRevolute2D, GetLowerAngle, () const, float), asCALL_THISCALL);
    // float ConstraintRevolute2D::GetMaxMotorTorque() const | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float GetMaxMotorTorque() const", asMETHODPR(ConstraintRevolute2D, GetMaxMotorTorque, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_maxMotorTorque() const", asMETHODPR(ConstraintRevolute2D, GetMaxMotorTorque, () const, float), asCALL_THISCALL);
    // float ConstraintRevolute2D::GetMotorSpeed() const | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float GetMotorSpeed() const", asMETHODPR(ConstraintRevolute2D, GetMotorSpeed, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_motorSpeed() const", asMETHODPR(ConstraintRevolute2D, GetMotorSpeed, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Node@+ GetNode() const", asMETHODPR(ConstraintRevolute2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Node@+ get_node() const", asMETHODPR(ConstraintRevolute2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "uint GetNumAttributes() const", asMETHODPR(ConstraintRevolute2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "uint get_numAttributes() const", asMETHODPR(ConstraintRevolute2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "uint GetNumNetworkAttributes() const", asMETHODPR(ConstraintRevolute2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ConstraintRevolute2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ConstraintRevolute2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ConstraintRevolute2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "RigidBody2D@+ GetOtherBody() const", asMETHODPR(ConstraintRevolute2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "RigidBody2D@+ get_otherBody() const", asMETHODPR(ConstraintRevolute2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "RigidBody2D@+ GetOwnerBody() const", asMETHODPR(ConstraintRevolute2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "RigidBody2D@+ get_ownerBody() const", asMETHODPR(ConstraintRevolute2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Scene@+ GetScene() const", asMETHODPR(ConstraintRevolute2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ConstraintRevolute2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "StringHash GetType() const", asMETHODPR(ConstraintRevolute2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "StringHash get_type() const", asMETHODPR(ConstraintRevolute2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const String& GetTypeName() const", asMETHODPR(ConstraintRevolute2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const String& get_typeName() const", asMETHODPR(ConstraintRevolute2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // float ConstraintRevolute2D::GetUpperAngle() const | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float GetUpperAngle() const", asMETHODPR(ConstraintRevolute2D, GetUpperAngle, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_upperAngle() const", asMETHODPR(ConstraintRevolute2D, GetUpperAngle, () const, float), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool HasEventHandlers() const", asMETHODPR(ConstraintRevolute2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ConstraintRevolute2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ConstraintRevolute2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool IsEnabled() const", asMETHODPR(ConstraintRevolute2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_enabled() const", asMETHODPR(ConstraintRevolute2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool IsEnabledEffective() const", asMETHODPR(ConstraintRevolute2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_enabledEffective() const", asMETHODPR(ConstraintRevolute2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(ConstraintRevolute2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool IsReplicated() const", asMETHODPR(ConstraintRevolute2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_replicated() const", asMETHODPR(ConstraintRevolute2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool IsTemporary() const", asMETHODPR(ConstraintRevolute2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_temporary() const", asMETHODPR(ConstraintRevolute2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool Load(Deserializer&)", asMETHODPR(ConstraintRevolute2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ConstraintRevolute2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(ConstraintRevolute2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void MarkNetworkUpdate()", asMETHODPR(ConstraintRevolute2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ConstraintRevolute2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ConstraintRevolute2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ConstraintRevolute2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void OnSetEnabled()", asMETHODPR(ConstraintRevolute2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void PrepareNetworkUpdate()", asMETHODPR(ConstraintRevolute2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ConstraintRevolute2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ConstraintRevolute2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "int Refs() const", asMETHODPR(ConstraintRevolute2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "int get_refs() const", asMETHODPR(ConstraintRevolute2D, Refs, () const, int), asCALL_THISCALL);
    // static void ConstraintRevolute2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintRevolute2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void ReleaseJoint()", asMETHODPR(ConstraintRevolute2D, ReleaseJoint, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintRevolute2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(ConstraintRevolute2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void Remove()", asMETHODPR(ConstraintRevolute2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ConstraintRevolute2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void RemoveInstanceDefault()", asMETHODPR(ConstraintRevolute2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void RemoveObjectAnimation()", asMETHODPR(ConstraintRevolute2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void ResetToDefault()", asMETHODPR(ConstraintRevolute2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool Save(Serializer&) const", asMETHODPR(ConstraintRevolute2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool SaveDefaultAttributes() const", asMETHODPR(ConstraintRevolute2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(ConstraintRevolute2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool SaveXML(XMLElement&) const", asMETHODPR(ConstraintRevolute2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SendEvent(StringHash)", asMETHODPR(ConstraintRevolute2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ConstraintRevolute2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ConstraintRevolute2D::SetAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAnchor(const Vector2&in)", asMETHODPR(ConstraintRevolute2D, SetAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_anchor(const Vector2&in)", asMETHODPR(ConstraintRevolute2D, SetAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAnimationEnabled(bool)", asMETHODPR(ConstraintRevolute2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_animationEnabled(bool)", asMETHODPR(ConstraintRevolute2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAnimationTime(float)", asMETHODPR(ConstraintRevolute2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAttachedConstraint(Constraint2D@+)", asMETHODPR(ConstraintRevolute2D, SetAttachedConstraint, (Constraint2D*), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ConstraintRevolute2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ConstraintRevolute2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ConstraintRevolute2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ConstraintRevolute2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ConstraintRevolute2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ConstraintRevolute2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ConstraintRevolute2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetBlockEvents(bool)", asMETHODPR(ConstraintRevolute2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetCollideConnected(bool)", asMETHODPR(ConstraintRevolute2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_collideConnected(bool)", asMETHODPR(ConstraintRevolute2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetEnabled(bool)", asMETHODPR(ConstraintRevolute2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_enabled(bool)", asMETHODPR(ConstraintRevolute2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void ConstraintRevolute2D::SetEnableLimit(bool enableLimit) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetEnableLimit(bool)", asMETHODPR(ConstraintRevolute2D, SetEnableLimit, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_enableLimit(bool)", asMETHODPR(ConstraintRevolute2D, SetEnableLimit, (bool), void), asCALL_THISCALL);
    // void ConstraintRevolute2D::SetEnableMotor(bool enableMotor) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetEnableMotor(bool)", asMETHODPR(ConstraintRevolute2D, SetEnableMotor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_enableMotor(bool)", asMETHODPR(ConstraintRevolute2D, SetEnableMotor, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintRevolute2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintRevolute2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetInstanceDefault(bool)", asMETHODPR(ConstraintRevolute2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ConstraintRevolute2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void ConstraintRevolute2D::SetLowerAngle(float lowerAngle) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetLowerAngle(float)", asMETHODPR(ConstraintRevolute2D, SetLowerAngle, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_lowerAngle(float)", asMETHODPR(ConstraintRevolute2D, SetLowerAngle, (float), void), asCALL_THISCALL);
    // void ConstraintRevolute2D::SetMaxMotorTorque(float maxMotorTorque) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetMaxMotorTorque(float)", asMETHODPR(ConstraintRevolute2D, SetMaxMotorTorque, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_maxMotorTorque(float)", asMETHODPR(ConstraintRevolute2D, SetMaxMotorTorque, (float), void), asCALL_THISCALL);
    // void ConstraintRevolute2D::SetMotorSpeed(float motorSpeed) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetMotorSpeed(float)", asMETHODPR(ConstraintRevolute2D, SetMotorSpeed, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_motorSpeed(float)", asMETHODPR(ConstraintRevolute2D, SetMotorSpeed, (float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintRevolute2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintRevolute2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ConstraintRevolute2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetOtherBody(RigidBody2D@+)", asMETHODPR(ConstraintRevolute2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_otherBody(RigidBody2D@+)", asMETHODPR(ConstraintRevolute2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetTemporary(bool)", asMETHODPR(ConstraintRevolute2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_temporary(bool)", asMETHODPR(ConstraintRevolute2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void ConstraintRevolute2D::SetUpperAngle(float upperAngle) | File: ../Urho2D/ConstraintRevolute2D.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void SetUpperAngle(float)", asMETHODPR(ConstraintRevolute2D, SetUpperAngle, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_upperAngle(float)", asMETHODPR(ConstraintRevolute2D, SetUpperAngle, (float), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void UnsubscribeFromAllEvents()", asMETHODPR(ConstraintRevolute2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ConstraintRevolute2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ConstraintRevolute2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ConstraintRevolute2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ConstraintRevolute2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "int WeakRefs() const", asMETHODPR(ConstraintRevolute2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "int get_weakRefs() const", asMETHODPR(ConstraintRevolute2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ConstraintRevolute2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ConstraintRevolute2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ConstraintRevolute2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ConstraintRope2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(ConstraintRope2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void AllocateNetworkState()", asMETHODPR(ConstraintRope2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void ApplyAttributes()", asMETHODPR(ConstraintRope2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintRope2D::ConstraintRope2D(Context* context) | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectBehaviour("ConstraintRope2D", asBEHAVE_FACTORY, "ConstraintRope2D@+ f()", asFUNCTION(ConstraintRope2D_ConstraintRope2D_Context), asCALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void CreateJoint()", asMETHODPR(ConstraintRope2D, CreateJoint, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(ConstraintRope2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool GetAnimationEnabled() const", asMETHODPR(ConstraintRope2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "bool get_animationEnabled() const", asMETHODPR(ConstraintRope2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Constraint2D@+ GetAttachedConstraint() const", asMETHODPR(ConstraintRope2D, GetAttachedConstraint, () const, Constraint2D*), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Variant GetAttribute(uint) const", asMETHODPR(ConstraintRope2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "Variant get_attributes(uint) const", asMETHODPR(ConstraintRope2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Variant GetAttribute(const String&in) const", asMETHODPR(ConstraintRope2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ConstraintRope2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ConstraintRope2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ConstraintRope2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ConstraintRope2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(ConstraintRope2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(ConstraintRope2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ConstraintRope2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool GetBlockEvents() const", asMETHODPR(ConstraintRope2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "const String& GetCategory() const", asMETHODPR(ConstraintRope2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const String& get_category() const", asMETHODPR(ConstraintRope2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool GetCollideConnected() const", asMETHODPR(ConstraintRope2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "bool get_collideConnected() const", asMETHODPR(ConstraintRope2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(ConstraintRope2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ConstraintRope2D", "VariantMap& GetEventDataMap() const", asMETHODPR(ConstraintRope2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Object@+ GetEventSender() const", asMETHODPR(ConstraintRope2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ConstraintRope2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ConstraintRope2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(ConstraintRope2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const VariantMap& get_globalVars() const", asMETHODPR(ConstraintRope2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "uint GetID() const", asMETHODPR(ConstraintRope2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "uint get_id() const", asMETHODPR(ConstraintRope2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ConstraintRope2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // float ConstraintRope2D::GetMaxLength() const | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "float GetMaxLength() const", asMETHODPR(ConstraintRope2D, GetMaxLength, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "float get_maxLength() const", asMETHODPR(ConstraintRope2D, GetMaxLength, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Node@+ GetNode() const", asMETHODPR(ConstraintRope2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "Node@+ get_node() const", asMETHODPR(ConstraintRope2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "uint GetNumAttributes() const", asMETHODPR(ConstraintRope2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "uint get_numAttributes() const", asMETHODPR(ConstraintRope2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "uint GetNumNetworkAttributes() const", asMETHODPR(ConstraintRope2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ConstraintRope2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ConstraintRope2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ConstraintRope2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "RigidBody2D@+ GetOtherBody() const", asMETHODPR(ConstraintRope2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "RigidBody2D@+ get_otherBody() const", asMETHODPR(ConstraintRope2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    // const Vector2& ConstraintRope2D::GetOtherBodyAnchor() const | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "const Vector2& GetOtherBodyAnchor() const", asMETHODPR(ConstraintRope2D, GetOtherBodyAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const Vector2& get_otherBodyAnchor() const", asMETHODPR(ConstraintRope2D, GetOtherBodyAnchor, () const, const Vector2&), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "RigidBody2D@+ GetOwnerBody() const", asMETHODPR(ConstraintRope2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "RigidBody2D@+ get_ownerBody() const", asMETHODPR(ConstraintRope2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    // const Vector2& ConstraintRope2D::GetOwnerBodyAnchor() const | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "const Vector2& GetOwnerBodyAnchor() const", asMETHODPR(ConstraintRope2D, GetOwnerBodyAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const Vector2& get_ownerBodyAnchor() const", asMETHODPR(ConstraintRope2D, GetOwnerBodyAnchor, () const, const Vector2&), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Scene@+ GetScene() const", asMETHODPR(ConstraintRope2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ConstraintRope2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "StringHash GetType() const", asMETHODPR(ConstraintRope2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "StringHash get_type() const", asMETHODPR(ConstraintRope2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "const String& GetTypeName() const", asMETHODPR(ConstraintRope2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const String& get_typeName() const", asMETHODPR(ConstraintRope2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool HasEventHandlers() const", asMETHODPR(ConstraintRope2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ConstraintRope2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ConstraintRope2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool IsEnabled() const", asMETHODPR(ConstraintRope2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "bool get_enabled() const", asMETHODPR(ConstraintRope2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool IsEnabledEffective() const", asMETHODPR(ConstraintRope2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "bool get_enabledEffective() const", asMETHODPR(ConstraintRope2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(ConstraintRope2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool IsReplicated() const", asMETHODPR(ConstraintRope2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "bool get_replicated() const", asMETHODPR(ConstraintRope2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool IsTemporary() const", asMETHODPR(ConstraintRope2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "bool get_temporary() const", asMETHODPR(ConstraintRope2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool Load(Deserializer&)", asMETHODPR(ConstraintRope2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ConstraintRope2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(ConstraintRope2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void MarkNetworkUpdate()", asMETHODPR(ConstraintRope2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ConstraintRope2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ConstraintRope2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ConstraintRope2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void OnSetEnabled()", asMETHODPR(ConstraintRope2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void PrepareNetworkUpdate()", asMETHODPR(ConstraintRope2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ConstraintRope2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ConstraintRope2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintRope2D", "int Refs() const", asMETHODPR(ConstraintRope2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "int get_refs() const", asMETHODPR(ConstraintRope2D, Refs, () const, int), asCALL_THISCALL);
    // static void ConstraintRope2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintRope2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void ReleaseJoint()", asMETHODPR(ConstraintRope2D, ReleaseJoint, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintRope2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(ConstraintRope2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void Remove()", asMETHODPR(ConstraintRope2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ConstraintRope2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void RemoveInstanceDefault()", asMETHODPR(ConstraintRope2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void RemoveObjectAnimation()", asMETHODPR(ConstraintRope2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void ResetToDefault()", asMETHODPR(ConstraintRope2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool Save(Serializer&) const", asMETHODPR(ConstraintRope2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool SaveDefaultAttributes() const", asMETHODPR(ConstraintRope2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(ConstraintRope2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool SaveXML(XMLElement&) const", asMETHODPR(ConstraintRope2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SendEvent(StringHash)", asMETHODPR(ConstraintRope2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ConstraintRope2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetAnimationEnabled(bool)", asMETHODPR(ConstraintRope2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_animationEnabled(bool)", asMETHODPR(ConstraintRope2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetAnimationTime(float)", asMETHODPR(ConstraintRope2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetAttachedConstraint(Constraint2D@+)", asMETHODPR(ConstraintRope2D, SetAttachedConstraint, (Constraint2D*), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ConstraintRope2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ConstraintRope2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ConstraintRope2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ConstraintRope2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ConstraintRope2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ConstraintRope2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ConstraintRope2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetBlockEvents(bool)", asMETHODPR(ConstraintRope2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetCollideConnected(bool)", asMETHODPR(ConstraintRope2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_collideConnected(bool)", asMETHODPR(ConstraintRope2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetEnabled(bool)", asMETHODPR(ConstraintRope2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_enabled(bool)", asMETHODPR(ConstraintRope2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintRope2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintRope2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetInstanceDefault(bool)", asMETHODPR(ConstraintRope2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ConstraintRope2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void ConstraintRope2D::SetMaxLength(float maxLength) | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetMaxLength(float)", asMETHODPR(ConstraintRope2D, SetMaxLength, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_maxLength(float)", asMETHODPR(ConstraintRope2D, SetMaxLength, (float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintRope2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintRope2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ConstraintRope2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetOtherBody(RigidBody2D@+)", asMETHODPR(ConstraintRope2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_otherBody(RigidBody2D@+)", asMETHODPR(ConstraintRope2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    // void ConstraintRope2D::SetOtherBodyAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetOtherBodyAnchor(const Vector2&in)", asMETHODPR(ConstraintRope2D, SetOtherBodyAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_otherBodyAnchor(const Vector2&in)", asMETHODPR(ConstraintRope2D, SetOtherBodyAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void ConstraintRope2D::SetOwnerBodyAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintRope2D.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetOwnerBodyAnchor(const Vector2&in)", asMETHODPR(ConstraintRope2D, SetOwnerBodyAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_ownerBodyAnchor(const Vector2&in)", asMETHODPR(ConstraintRope2D, SetOwnerBodyAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void SetTemporary(bool)", asMETHODPR(ConstraintRope2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_temporary(bool)", asMETHODPR(ConstraintRope2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void UnsubscribeFromAllEvents()", asMETHODPR(ConstraintRope2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ConstraintRope2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ConstraintRope2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ConstraintRope2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ConstraintRope2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintRope2D", "int WeakRefs() const", asMETHODPR(ConstraintRope2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "int get_weakRefs() const", asMETHODPR(ConstraintRope2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ConstraintRope2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ConstraintRope2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintRope2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ConstraintRope2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ConstraintWeld2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(ConstraintWeld2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void AllocateNetworkState()", asMETHODPR(ConstraintWeld2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void ApplyAttributes()", asMETHODPR(ConstraintWeld2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintWeld2D::ConstraintWeld2D(Context* context) | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectBehaviour("ConstraintWeld2D", asBEHAVE_FACTORY, "ConstraintWeld2D@+ f()", asFUNCTION(ConstraintWeld2D_ConstraintWeld2D_Context), asCALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void CreateJoint()", asMETHODPR(ConstraintWeld2D, CreateJoint, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(ConstraintWeld2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // const Vector2& ConstraintWeld2D::GetAnchor() const | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "const Vector2& GetAnchor() const", asMETHODPR(ConstraintWeld2D, GetAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "const Vector2& get_anchor() const", asMETHODPR(ConstraintWeld2D, GetAnchor, () const, const Vector2&), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool GetAnimationEnabled() const", asMETHODPR(ConstraintWeld2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool get_animationEnabled() const", asMETHODPR(ConstraintWeld2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Constraint2D@+ GetAttachedConstraint() const", asMETHODPR(ConstraintWeld2D, GetAttachedConstraint, () const, Constraint2D*), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Variant GetAttribute(uint) const", asMETHODPR(ConstraintWeld2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "Variant get_attributes(uint) const", asMETHODPR(ConstraintWeld2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Variant GetAttribute(const String&in) const", asMETHODPR(ConstraintWeld2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ConstraintWeld2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ConstraintWeld2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ConstraintWeld2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ConstraintWeld2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(ConstraintWeld2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(ConstraintWeld2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ConstraintWeld2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool GetBlockEvents() const", asMETHODPR(ConstraintWeld2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "const String& GetCategory() const", asMETHODPR(ConstraintWeld2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "const String& get_category() const", asMETHODPR(ConstraintWeld2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool GetCollideConnected() const", asMETHODPR(ConstraintWeld2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool get_collideConnected() const", asMETHODPR(ConstraintWeld2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(ConstraintWeld2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ConstraintWeld2D::GetDampingRatio() const | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "float GetDampingRatio() const", asMETHODPR(ConstraintWeld2D, GetDampingRatio, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "float get_dampingRatio() const", asMETHODPR(ConstraintWeld2D, GetDampingRatio, () const, float), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "VariantMap& GetEventDataMap() const", asMETHODPR(ConstraintWeld2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Object@+ GetEventSender() const", asMETHODPR(ConstraintWeld2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // float ConstraintWeld2D::GetFrequencyHz() const | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "float GetFrequencyHz() const", asMETHODPR(ConstraintWeld2D, GetFrequencyHz, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "float get_frequencyHz() const", asMETHODPR(ConstraintWeld2D, GetFrequencyHz, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ConstraintWeld2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ConstraintWeld2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(ConstraintWeld2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "const VariantMap& get_globalVars() const", asMETHODPR(ConstraintWeld2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "uint GetID() const", asMETHODPR(ConstraintWeld2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "uint get_id() const", asMETHODPR(ConstraintWeld2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ConstraintWeld2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Node@+ GetNode() const", asMETHODPR(ConstraintWeld2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "Node@+ get_node() const", asMETHODPR(ConstraintWeld2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "uint GetNumAttributes() const", asMETHODPR(ConstraintWeld2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "uint get_numAttributes() const", asMETHODPR(ConstraintWeld2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "uint GetNumNetworkAttributes() const", asMETHODPR(ConstraintWeld2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ConstraintWeld2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ConstraintWeld2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ConstraintWeld2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "RigidBody2D@+ GetOtherBody() const", asMETHODPR(ConstraintWeld2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "RigidBody2D@+ get_otherBody() const", asMETHODPR(ConstraintWeld2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "RigidBody2D@+ GetOwnerBody() const", asMETHODPR(ConstraintWeld2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "RigidBody2D@+ get_ownerBody() const", asMETHODPR(ConstraintWeld2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Scene@+ GetScene() const", asMETHODPR(ConstraintWeld2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ConstraintWeld2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "StringHash GetType() const", asMETHODPR(ConstraintWeld2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "StringHash get_type() const", asMETHODPR(ConstraintWeld2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "const String& GetTypeName() const", asMETHODPR(ConstraintWeld2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "const String& get_typeName() const", asMETHODPR(ConstraintWeld2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool HasEventHandlers() const", asMETHODPR(ConstraintWeld2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ConstraintWeld2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ConstraintWeld2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool IsEnabled() const", asMETHODPR(ConstraintWeld2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool get_enabled() const", asMETHODPR(ConstraintWeld2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool IsEnabledEffective() const", asMETHODPR(ConstraintWeld2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool get_enabledEffective() const", asMETHODPR(ConstraintWeld2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(ConstraintWeld2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool IsReplicated() const", asMETHODPR(ConstraintWeld2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool get_replicated() const", asMETHODPR(ConstraintWeld2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool IsTemporary() const", asMETHODPR(ConstraintWeld2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool get_temporary() const", asMETHODPR(ConstraintWeld2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool Load(Deserializer&)", asMETHODPR(ConstraintWeld2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ConstraintWeld2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(ConstraintWeld2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void MarkNetworkUpdate()", asMETHODPR(ConstraintWeld2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ConstraintWeld2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ConstraintWeld2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ConstraintWeld2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void OnSetEnabled()", asMETHODPR(ConstraintWeld2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void PrepareNetworkUpdate()", asMETHODPR(ConstraintWeld2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ConstraintWeld2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ConstraintWeld2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "int Refs() const", asMETHODPR(ConstraintWeld2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "int get_refs() const", asMETHODPR(ConstraintWeld2D, Refs, () const, int), asCALL_THISCALL);
    // static void ConstraintWeld2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintWeld2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void ReleaseJoint()", asMETHODPR(ConstraintWeld2D, ReleaseJoint, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintWeld2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(ConstraintWeld2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void Remove()", asMETHODPR(ConstraintWeld2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ConstraintWeld2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void RemoveInstanceDefault()", asMETHODPR(ConstraintWeld2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void RemoveObjectAnimation()", asMETHODPR(ConstraintWeld2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void ResetToDefault()", asMETHODPR(ConstraintWeld2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool Save(Serializer&) const", asMETHODPR(ConstraintWeld2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool SaveDefaultAttributes() const", asMETHODPR(ConstraintWeld2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(ConstraintWeld2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool SaveXML(XMLElement&) const", asMETHODPR(ConstraintWeld2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SendEvent(StringHash)", asMETHODPR(ConstraintWeld2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ConstraintWeld2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ConstraintWeld2D::SetAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAnchor(const Vector2&in)", asMETHODPR(ConstraintWeld2D, SetAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_anchor(const Vector2&in)", asMETHODPR(ConstraintWeld2D, SetAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAnimationEnabled(bool)", asMETHODPR(ConstraintWeld2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_animationEnabled(bool)", asMETHODPR(ConstraintWeld2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAnimationTime(float)", asMETHODPR(ConstraintWeld2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAttachedConstraint(Constraint2D@+)", asMETHODPR(ConstraintWeld2D, SetAttachedConstraint, (Constraint2D*), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ConstraintWeld2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ConstraintWeld2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ConstraintWeld2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ConstraintWeld2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ConstraintWeld2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ConstraintWeld2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ConstraintWeld2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetBlockEvents(bool)", asMETHODPR(ConstraintWeld2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetCollideConnected(bool)", asMETHODPR(ConstraintWeld2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_collideConnected(bool)", asMETHODPR(ConstraintWeld2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    // void ConstraintWeld2D::SetDampingRatio(float dampingRatio) | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetDampingRatio(float)", asMETHODPR(ConstraintWeld2D, SetDampingRatio, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_dampingRatio(float)", asMETHODPR(ConstraintWeld2D, SetDampingRatio, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetEnabled(bool)", asMETHODPR(ConstraintWeld2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_enabled(bool)", asMETHODPR(ConstraintWeld2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void ConstraintWeld2D::SetFrequencyHz(float frequencyHz) | File: ../Urho2D/ConstraintWeld2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetFrequencyHz(float)", asMETHODPR(ConstraintWeld2D, SetFrequencyHz, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_frequencyHz(float)", asMETHODPR(ConstraintWeld2D, SetFrequencyHz, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintWeld2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintWeld2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetInstanceDefault(bool)", asMETHODPR(ConstraintWeld2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ConstraintWeld2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintWeld2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintWeld2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ConstraintWeld2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetOtherBody(RigidBody2D@+)", asMETHODPR(ConstraintWeld2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_otherBody(RigidBody2D@+)", asMETHODPR(ConstraintWeld2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void SetTemporary(bool)", asMETHODPR(ConstraintWeld2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_temporary(bool)", asMETHODPR(ConstraintWeld2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void UnsubscribeFromAllEvents()", asMETHODPR(ConstraintWeld2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ConstraintWeld2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ConstraintWeld2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ConstraintWeld2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ConstraintWeld2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "int WeakRefs() const", asMETHODPR(ConstraintWeld2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "int get_weakRefs() const", asMETHODPR(ConstraintWeld2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ConstraintWeld2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ConstraintWeld2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWeld2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ConstraintWeld2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ConstraintWheel2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(ConstraintWheel2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void AllocateNetworkState()", asMETHODPR(ConstraintWheel2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Constraint2D::ApplyAttributes() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void ApplyAttributes()", asMETHODPR(ConstraintWheel2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit ConstraintWheel2D::ConstraintWheel2D(Context* context) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectBehaviour("ConstraintWheel2D", asBEHAVE_FACTORY, "ConstraintWheel2D@+ f()", asFUNCTION(ConstraintWheel2D_ConstraintWheel2D_Context), asCALL_CDECL);
    // void Constraint2D::CreateJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void CreateJoint()", asMETHODPR(ConstraintWheel2D, CreateJoint, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(ConstraintWheel2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // const Vector2& ConstraintWheel2D::GetAnchor() const | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Vector2& GetAnchor() const", asMETHODPR(ConstraintWheel2D, GetAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Vector2& get_anchor() const", asMETHODPR(ConstraintWheel2D, GetAnchor, () const, const Vector2&), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool GetAnimationEnabled() const", asMETHODPR(ConstraintWheel2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_animationEnabled() const", asMETHODPR(ConstraintWheel2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Constraint2D* Constraint2D::GetAttachedConstraint() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Constraint2D@+ GetAttachedConstraint() const", asMETHODPR(ConstraintWheel2D, GetAttachedConstraint, () const, Constraint2D*), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Variant GetAttribute(uint) const", asMETHODPR(ConstraintWheel2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "Variant get_attributes(uint) const", asMETHODPR(ConstraintWheel2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Variant GetAttribute(const String&in) const", asMETHODPR(ConstraintWheel2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ConstraintWheel2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ConstraintWheel2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ConstraintWheel2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ConstraintWheel2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(ConstraintWheel2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(ConstraintWheel2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ConstraintWheel2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector2& ConstraintWheel2D::GetAxis() const | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Vector2& GetAxis() const", asMETHODPR(ConstraintWheel2D, GetAxis, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Vector2& get_axis() const", asMETHODPR(ConstraintWheel2D, GetAxis, () const, const Vector2&), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool GetBlockEvents() const", asMETHODPR(ConstraintWheel2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "const String& GetCategory() const", asMETHODPR(ConstraintWheel2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const String& get_category() const", asMETHODPR(ConstraintWheel2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // bool Constraint2D::GetCollideConnected() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool GetCollideConnected() const", asMETHODPR(ConstraintWheel2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_collideConnected() const", asMETHODPR(ConstraintWheel2D, GetCollideConnected, () const, bool), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(ConstraintWheel2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ConstraintWheel2D::GetDampingRatio() const | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "float GetDampingRatio() const", asMETHODPR(ConstraintWheel2D, GetDampingRatio, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_dampingRatio() const", asMETHODPR(ConstraintWheel2D, GetDampingRatio, () const, float), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // bool ConstraintWheel2D::GetEnableMotor() const | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool GetEnableMotor() const", asMETHODPR(ConstraintWheel2D, GetEnableMotor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_enableMotor() const", asMETHODPR(ConstraintWheel2D, GetEnableMotor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "VariantMap& GetEventDataMap() const", asMETHODPR(ConstraintWheel2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Object@+ GetEventSender() const", asMETHODPR(ConstraintWheel2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // float ConstraintWheel2D::GetFrequencyHz() const | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "float GetFrequencyHz() const", asMETHODPR(ConstraintWheel2D, GetFrequencyHz, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_frequencyHz() const", asMETHODPR(ConstraintWheel2D, GetFrequencyHz, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ConstraintWheel2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ConstraintWheel2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(ConstraintWheel2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const VariantMap& get_globalVars() const", asMETHODPR(ConstraintWheel2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "uint GetID() const", asMETHODPR(ConstraintWheel2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "uint get_id() const", asMETHODPR(ConstraintWheel2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ConstraintWheel2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // b2Joint* Constraint2D::GetJoint() const | File: ../Urho2D/Constraint2D.h
    // Error: type "b2Joint*" can not automatically bind
    // float ConstraintWheel2D::GetMaxMotorTorque() const | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "float GetMaxMotorTorque() const", asMETHODPR(ConstraintWheel2D, GetMaxMotorTorque, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_maxMotorTorque() const", asMETHODPR(ConstraintWheel2D, GetMaxMotorTorque, () const, float), asCALL_THISCALL);
    // float ConstraintWheel2D::GetMotorSpeed() const | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "float GetMotorSpeed() const", asMETHODPR(ConstraintWheel2D, GetMotorSpeed, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_motorSpeed() const", asMETHODPR(ConstraintWheel2D, GetMotorSpeed, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Node@+ GetNode() const", asMETHODPR(ConstraintWheel2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "Node@+ get_node() const", asMETHODPR(ConstraintWheel2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "uint GetNumAttributes() const", asMETHODPR(ConstraintWheel2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "uint get_numAttributes() const", asMETHODPR(ConstraintWheel2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "uint GetNumNetworkAttributes() const", asMETHODPR(ConstraintWheel2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ConstraintWheel2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ConstraintWheel2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ConstraintWheel2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOtherBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "RigidBody2D@+ GetOtherBody() const", asMETHODPR(ConstraintWheel2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "RigidBody2D@+ get_otherBody() const", asMETHODPR(ConstraintWheel2D, GetOtherBody, () const, RigidBody2D*), asCALL_THISCALL);
    // RigidBody2D* Constraint2D::GetOwnerBody() const | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "RigidBody2D@+ GetOwnerBody() const", asMETHODPR(ConstraintWheel2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "RigidBody2D@+ get_ownerBody() const", asMETHODPR(ConstraintWheel2D, GetOwnerBody, () const, RigidBody2D*), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Scene@+ GetScene() const", asMETHODPR(ConstraintWheel2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ConstraintWheel2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "StringHash GetType() const", asMETHODPR(ConstraintWheel2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "StringHash get_type() const", asMETHODPR(ConstraintWheel2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "const String& GetTypeName() const", asMETHODPR(ConstraintWheel2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const String& get_typeName() const", asMETHODPR(ConstraintWheel2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool HasEventHandlers() const", asMETHODPR(ConstraintWheel2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ConstraintWheel2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ConstraintWheel2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool IsEnabled() const", asMETHODPR(ConstraintWheel2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_enabled() const", asMETHODPR(ConstraintWheel2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool IsEnabledEffective() const", asMETHODPR(ConstraintWheel2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_enabledEffective() const", asMETHODPR(ConstraintWheel2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(ConstraintWheel2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool IsReplicated() const", asMETHODPR(ConstraintWheel2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_replicated() const", asMETHODPR(ConstraintWheel2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool IsTemporary() const", asMETHODPR(ConstraintWheel2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_temporary() const", asMETHODPR(ConstraintWheel2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool Load(Deserializer&)", asMETHODPR(ConstraintWheel2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ConstraintWheel2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(ConstraintWheel2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void MarkNetworkUpdate()", asMETHODPR(ConstraintWheel2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ConstraintWheel2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ConstraintWheel2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ConstraintWheel2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Constraint2D::OnSetEnabled() override | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void OnSetEnabled()", asMETHODPR(ConstraintWheel2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void PrepareNetworkUpdate()", asMETHODPR(ConstraintWheel2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ConstraintWheel2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ConstraintWheel2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "int Refs() const", asMETHODPR(ConstraintWheel2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "int get_refs() const", asMETHODPR(ConstraintWheel2D, Refs, () const, int), asCALL_THISCALL);
    // static void ConstraintWheel2D::RegisterObject(Context* context) | File: ../Urho2D/ConstraintWheel2D.h
    // Not registered because have @nobind mark
    // void Constraint2D::ReleaseJoint() | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void ReleaseJoint()", asMETHODPR(ConstraintWheel2D, ReleaseJoint, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstraintWheel2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(ConstraintWheel2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void Remove()", asMETHODPR(ConstraintWheel2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ConstraintWheel2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void RemoveInstanceDefault()", asMETHODPR(ConstraintWheel2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void RemoveObjectAnimation()", asMETHODPR(ConstraintWheel2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void ResetToDefault()", asMETHODPR(ConstraintWheel2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool Save(Serializer&) const", asMETHODPR(ConstraintWheel2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool SaveDefaultAttributes() const", asMETHODPR(ConstraintWheel2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(ConstraintWheel2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool SaveXML(XMLElement&) const", asMETHODPR(ConstraintWheel2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SendEvent(StringHash)", asMETHODPR(ConstraintWheel2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ConstraintWheel2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ConstraintWheel2D::SetAnchor(const Vector2& anchor) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAnchor(const Vector2&in)", asMETHODPR(ConstraintWheel2D, SetAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_anchor(const Vector2&in)", asMETHODPR(ConstraintWheel2D, SetAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAnimationEnabled(bool)", asMETHODPR(ConstraintWheel2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_animationEnabled(bool)", asMETHODPR(ConstraintWheel2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAnimationTime(float)", asMETHODPR(ConstraintWheel2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Constraint2D::SetAttachedConstraint(Constraint2D* constraint) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAttachedConstraint(Constraint2D@+)", asMETHODPR(ConstraintWheel2D, SetAttachedConstraint, (Constraint2D*), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ConstraintWheel2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ConstraintWheel2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ConstraintWheel2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ConstraintWheel2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ConstraintWheel2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ConstraintWheel2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ConstraintWheel2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void ConstraintWheel2D::SetAxis(const Vector2& axis) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetAxis(const Vector2&in)", asMETHODPR(ConstraintWheel2D, SetAxis, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_axis(const Vector2&in)", asMETHODPR(ConstraintWheel2D, SetAxis, (const Vector2&), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetBlockEvents(bool)", asMETHODPR(ConstraintWheel2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Constraint2D::SetCollideConnected(bool collideConnected) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetCollideConnected(bool)", asMETHODPR(ConstraintWheel2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_collideConnected(bool)", asMETHODPR(ConstraintWheel2D, SetCollideConnected, (bool), void), asCALL_THISCALL);
    // void ConstraintWheel2D::SetDampingRatio(float dampingRatio) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetDampingRatio(float)", asMETHODPR(ConstraintWheel2D, SetDampingRatio, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_dampingRatio(float)", asMETHODPR(ConstraintWheel2D, SetDampingRatio, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetEnabled(bool)", asMETHODPR(ConstraintWheel2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_enabled(bool)", asMETHODPR(ConstraintWheel2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void ConstraintWheel2D::SetEnableMotor(bool enableMotor) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetEnableMotor(bool)", asMETHODPR(ConstraintWheel2D, SetEnableMotor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_enableMotor(bool)", asMETHODPR(ConstraintWheel2D, SetEnableMotor, (bool), void), asCALL_THISCALL);
    // void ConstraintWheel2D::SetFrequencyHz(float frequencyHz) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetFrequencyHz(float)", asMETHODPR(ConstraintWheel2D, SetFrequencyHz, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_frequencyHz(float)", asMETHODPR(ConstraintWheel2D, SetFrequencyHz, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintWheel2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ConstraintWheel2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetInstanceDefault(bool)", asMETHODPR(ConstraintWheel2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ConstraintWheel2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void ConstraintWheel2D::SetMaxMotorTorque(float maxMotorTorque) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetMaxMotorTorque(float)", asMETHODPR(ConstraintWheel2D, SetMaxMotorTorque, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_maxMotorTorque(float)", asMETHODPR(ConstraintWheel2D, SetMaxMotorTorque, (float), void), asCALL_THISCALL);
    // void ConstraintWheel2D::SetMotorSpeed(float motorSpeed) | File: ../Urho2D/ConstraintWheel2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetMotorSpeed(float)", asMETHODPR(ConstraintWheel2D, SetMotorSpeed, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_motorSpeed(float)", asMETHODPR(ConstraintWheel2D, SetMotorSpeed, (float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintWheel2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ConstraintWheel2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ConstraintWheel2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Constraint2D::SetOtherBody(RigidBody2D* body) | File: ../Urho2D/Constraint2D.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetOtherBody(RigidBody2D@+)", asMETHODPR(ConstraintWheel2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_otherBody(RigidBody2D@+)", asMETHODPR(ConstraintWheel2D, SetOtherBody, (RigidBody2D*), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void SetTemporary(bool)", asMETHODPR(ConstraintWheel2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_temporary(bool)", asMETHODPR(ConstraintWheel2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void UnsubscribeFromAllEvents()", asMETHODPR(ConstraintWheel2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ConstraintWheel2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ConstraintWheel2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ConstraintWheel2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ConstraintWheel2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "int WeakRefs() const", asMETHODPR(ConstraintWheel2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "int get_weakRefs() const", asMETHODPR(ConstraintWheel2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ConstraintWheel2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ConstraintWheel2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ConstraintWheel2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ConstraintWheel2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
